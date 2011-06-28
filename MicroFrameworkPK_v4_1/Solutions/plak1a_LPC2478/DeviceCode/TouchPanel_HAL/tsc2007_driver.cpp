////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tsc2007_driver.h>

struct TOUCH_I2C_CONFIGURATION {
	GPIO_PIN InterruptPin;
	UINT32 clk;
	UINT8 address;
};

extern TOUCH_I2C_CONFIGURATION g_TSC2007_Config;
extern TOUCH_PANEL_SamplingSettings g_TouchPanel_Sampling_Settings;

#define TSC2007_MEASURE_TEMP0		(0x0 << 4)
#define TSC2007_MEASURE_AUX		(0x2 << 4)
#define TSC2007_MEASURE_TEMP1		(0x4 << 4)
#define TSC2007_ACTIVATE_XN		(0x8 << 4)
#define TSC2007_ACTIVATE_YN		(0x9 << 4)
#define TSC2007_ACTIVATE_YP_XN		(0xa << 4)
#define TSC2007_SETUP			(0xb << 4)
#define TSC2007_MEASURE_X		(0xc << 4)
#define TSC2007_MEASURE_Y		(0xd << 4)
#define TSC2007_MEASURE_Z1		(0xe << 4)
#define TSC2007_MEASURE_Z2		(0xf << 4)

#define TSC2007_POWER_OFF_IRQ_EN	(0x0 << 2)
#define TSC2007_ADC_ON_IRQ_DIS0		(0x1 << 2)
#define TSC2007_ADC_OFF_IRQ_EN		(0x2 << 2)
#define TSC2007_ADC_ON_IRQ_DIS1		(0x3 << 2)

#define TSC2007_12BIT			(0x0 << 1)
#define TSC2007_8BIT			(0x1 << 1)

#define	MAX_12BIT			((1 << 12) - 1)

#define ADC_ON_12BIT	(TSC2007_12BIT | TSC2007_ADC_ON_IRQ_DIS0)

#define READ_Y		(ADC_ON_12BIT | TSC2007_MEASURE_Y)
#define READ_Z1		(ADC_ON_12BIT | TSC2007_MEASURE_Z1)
#define READ_Z2		(ADC_ON_12BIT | TSC2007_MEASURE_Z2)
#define READ_X		(ADC_ON_12BIT | TSC2007_MEASURE_X)
#define PWRDOWN		(TSC2007_12BIT | TSC2007_POWER_OFF_IRQ_EN)

BOOL TSC2007_Driver::Enable(GPIO_INTERRUPT_SERVICE_ROUTINE touchIsrProc) {
	CPU_GPIO_SetDebounce(3);

	if (!::CPU_GPIO_EnableInputPin2(g_TSC2007_Config.InterruptPin, TRUE,
			touchIsrProc, NULL, GPIO_INT_EDGE_BOTH, RESISTOR_PULLUP)) {
		return FALSE;
	}

	LPC24XX_I2C& I2C = LPC24XX::I2C();

	CPU_GPIO_DisablePin(LPC24XX_I2C::c_I2C_SDA, RESISTOR_DISABLED, 0,
			GPIO_ALT_MODE_1);
	CPU_GPIO_DisablePin(LPC24XX_I2C::c_I2C_SCL, RESISTOR_DISABLED, 0,
			GPIO_ALT_MODE_1);

	// enable the I2c module
	I2C.I2CONSET = LPC24XX_I2C::I2EN;
	I2C.I2SCLH = 16;//g_TSC2007_Config.clk;
	I2C.I2SCLL = 15;//g_TSC2007_Config.clk;

	return TRUE;
}

BOOL TSC2007_Driver::Disable() {
	CPU_GPIO_DisablePin(g_TSC2007_Config.InterruptPin, RESISTOR_DISABLED, 0,
			GPIO_ALT_PRIMARY);

	LPC24XX_I2C& I2C = LPC24XX::I2C();
	I2C.I2CONCLR = (LPC24XX_I2C::AA | LPC24XX_I2C::SI | LPC24XX_I2C::STO
			| LPC24XX_I2C::STA | LPC24XX_I2C::I2EN);

	return true;
}

int TSC2007_Driver::Transfer(I2C_WORD *txBuffer, int txBufferLen,
		I2C_WORD *rxBuffer, int rxBufferLen) {
	unsigned char code;
	int i2c_rxcharRemaining = rxBufferLen;
	unsigned char transferComplete = 0;
	unsigned char i2c_RdnWr = 0;
	int i2c_pos = 0;
	int i2c_rxWrPos = 0;
	int i2c_charRemaining = txBufferLen;
	int i2c_rxComplete = 0;

	LPC24XX_I2C& I2C = LPC24XX::I2C();

	I2C.I2CONSET |= (0x1 << 5);
	while (!transferComplete) {
		code = I2C.I2STAT;
		switch (code) {
		/***** MASTER TX MODE *****/
		case 0x08: // First Start Transmitted
		case 0x10: // Repeated Start
			// Write address and tell if it is read or write
			I2C.I2DAT = 0x90 | i2c_RdnWr;
			I2C.I2CONCLR = (0x1 << 3); // Clear SI
			break;
		case 0x18: // Start + Wr sent, ACK received
		case 0x20: // Start + Wr sent, Not ACK received
		case 0x28: // Data unsigned char sent, ACK recieved
		case 0x30: // Data unsigned char sent, Not Ack received
			if (i2c_charRemaining > 0) {
				I2C.I2DAT = txBuffer[i2c_pos++];
				i2c_charRemaining--;
				I2C.I2CONCLR = (0x1 << 5);
			} else if (i2c_rxcharRemaining == 0) {
				I2C.I2CONSET = (0x1 << 4); // Send Stop
				I2C.I2CONCLR = (0x1 << 5);
				transferComplete = 1;
			} else { // Change from master_tx to master_rx
				i2c_RdnWr = (~i2c_RdnWr) & 0x1;
				i2c_pos = 0;
				i2c_rxWrPos = 0;
				i2c_rxComplete = 0;
				I2C.I2CONSET |= (0x1 << 5);
			}
			I2C.I2CONCLR = (0x1 << 3); // ClearTC_CR_Y SI
			break;
		case 0x38: // Arbitration Lost, try again
			I2C.I2CONSET |= (0x1 << 5);
			I2C.I2CONCLR = (0x1 << 3); // Clear SI
			break;
			/***** MASTER RX MODE *****/
		case 0x40: // SLA+R HAS BEEN SENT; ACK RECEIVED
			if (i2c_rxcharRemaining != 0)
				I2C.I2CONSET |= (0x1 << 2);
			else
				I2C.I2CONCLR = (0x1 << 2);
			I2C.I2CONCLR = (0x1 << 3) | (0x1 << 5); // Clear SI and START
			break;
		case 0x48: // SLA+R has been send; not ack received
			// Try again
			I2C.I2CONSET |= (0x1 << 5);
			I2C.I2CONCLR = (0x1 << 3);
			break;
		case 0x50: // DATA unsigned char RECEIVED, ACK RETURNED
			rxBuffer[i2c_rxWrPos] = I2C.I2DAT;
			i2c_rxWrPos++;
			i2c_rxcharRemaining--;
			if (i2c_rxcharRemaining != 0)
				I2C.I2CONSET |= (0x1 << 2);
			else
				I2C.I2CONCLR = (0x1 << 2);
			I2C.I2CONCLR = (0x1 << 3) | (0x1 << 5); // Clear SI and START
			break;
		case 0x58: // DATA unsigned char RECEIVED; NOT ACT RETURNED
			i2c_rxComplete = 1; // Done receiving all requested data
			transferComplete = 1;
			I2C.I2CONCLR = (0x1 << 5);
			I2C.I2CONSET = (0x1 << 4);
			I2C.I2CONCLR = (0x1 << 3);
			break;
		}
	}
	return 0;
}

void TSC2007_Driver::GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState,
		int* pSource, int* pUnCalX, int* pUnCalY) {

	UINT16 x, y, z1, z2;
	UINT32 rt;
	I2C_WORD readY[1] = { READ_Y };
	I2C_WORD readX[1] = { READ_X };
	I2C_WORD readZ1[1] = { READ_Z1 };
	I2C_WORD readZ2[1] = { READ_Z2 };
	I2C_WORD powerDown[1] = { PWRDOWN };
	I2C_WORD event[2] = { 0, 0 };
	INT32 validReadCount = 0;
	UINT16 i = 0;
	UINT16 totalReads = g_TouchPanel_Sampling_Settings.ReadsToIgnore
			+ g_TouchPanel_Sampling_Settings.ReadsPerSample;

	*pTipState = 0;
	*pUnCalX = 0;
	*pUnCalY = 0;
	*pSource = 0;

	static bool stylusDown = false;

	for (i = 0; i < totalReads; i++) {
		// y- still on; turn on only y+ (and ADC) //
		Transfer(readY, 1, event, 2);
		y = ((event[0] << 8) | event[1]) >> 4; //tsc2007_xfer(tsc, READ_Y);

		// turn y- off, x+ on, then leave in lowpower //
		Transfer(readX, 1, event, 2);
		x = ((event[0] << 8) | event[1]) >> 4; //tsc2007_xfer(tsc, READ_X);

		// turn y+ off, x- on; we'll use formula #1 //
		Transfer(readZ1, 1, event, 2);
		z1 = ((event[0] << 8) | event[1]) >> 4; //tsc2007_xfer(tsc, READ_Z1);
		Transfer(readZ2, 1, event, 2);
		z2 = ((event[0] << 8) | event[1]) >> 4; //tsc2007_xfer(tsc, READ_Z2);

		/* power down */
		Transfer(powerDown, 1, event, 2); //tsc2007_xfer(tsc, PWRDOWN);

		/* range filtering */
		if (x == MAX_12BIT)
			x = 0;

		if ((x != 0) && (z1 != 0)) {
			/* compute touch pressure resistance using equation #1 */
			rt = z2;
			rt -= z1;
			rt *= x;
			rt *= 180;
			rt /= z1;
			rt = (rt + 2047) >> 12;
		} else {
			rt = 0;
		}
		/* Sample found inconsistent by debouncing or pressure is beyond
		 * the maximum. Don't report it to user space, repeat at least
		 * once more the measurement
		 */
		if (rt <= MAX_12BIT) {
			break;
		}

	}

	if (rt == 0) {
		validReadCount = 0;
	} else {
		validReadCount = 1;
	}

	if (stylusDown) {
		*pTipState |= TouchSamplePreviousDownFlag;
	}

	if (validReadCount > 0) {
		*pTipState |= TouchSampleValidFlag;
		*pUnCalX = x;
		*pUnCalY = y;
		*pTipState |= TouchSampleDownFlag;
		stylusDown = true;
	} else {
		*pUnCalX = -1;
		*pUnCalY = -1;
		stylusDown = false;
	}
}

#if 0
void TSC2007_Driver::GetPoint(TOUCH_PANEL_SAMPLE_FLAGS* pTipState,
		int* pSource, int* pUnCalX, int* pUnCalY) {
	*pTipState = 0;
	*pUnCalX = 0;
	*pUnCalY = 0;
	*pSource = 0;

	static bool stylusDown = false;

	/// Apparently there's a lot of noise from the touch hardware. We will take several
	/// independent measures to compensate for them:
	/// 1. Settle down time (instead of reading right away, wait few moments) --> ReadsToIgnore
	/// 2. Read multiple samples (read a number of them, and then take average) --> ReadsPerSample.
	///

	UINT16 i = 0;
	UINT16 totalReads = g_TouchPanel_Sampling_Settings.ReadsToIgnore
	+ g_TouchPanel_Sampling_Settings.ReadsPerSample;

	int x = -1;
	int y = -1;

	INT32 validReadCount = 0;

	UINT32 d1 = 0xFFFF;
	UINT32 d2 = 0;

	I2C_WORD writeBufferY[1] = {0xc8};
	I2C_WORD readBufferY[2] = {0, 0};
	I2C_WORD writeBufferX[1] = {0xd8};
	I2C_WORD readBufferX[2] = {0, 0};

	for (i = 0; i < totalReads; i++) {
		Transfer(writeBufferY, 1, readBufferY, 2);
		d2 = d1;

		d1 = readBufferY[0];
		d1 <<= 8;
		d1 |= readBufferY[1];
		d1 >>= 4;

		if (d1 == d2)
		break;
	}

	y = d1;

	d1 = 0xFFFF;
	d2 = 0;
	for (i = 0; i < g_TouchPanel_Sampling_Settings.ReadsPerSample; i++) {
		Transfer(writeBufferX, 1, readBufferX, 2);

		d2 = d1;

		d1 = readBufferX[0];
		d1 <<= 8;
		d1 |= readBufferX[1];
		d1 >>= 4;

		if (d1 == d2)
		break;
	}

	x = d1;

	if (x >= 3700) {
		validReadCount = 0;
	} else {
		validReadCount = 1;
	}

	if (stylusDown) {
		*pTipState |= TouchSamplePreviousDownFlag;
	}

	if (validReadCount > 0) {
		*pTipState |= TouchSampleValidFlag;
		*pUnCalX = x;
		*pUnCalY = y;
		*pTipState |= TouchSampleDownFlag;
		stylusDown = true;
	} else {
		*pUnCalX = -1;
		*pUnCalY = -1;
		stylusDown = false;
	}
}
#endif

BOOL TSC2007_Driver::CalibrationPointGet(TOUCH_PANEL_CALIBRATION_POINT *pTCP) {

	INT32 cDisplayWidth = pTCP->cDisplayWidth;
	INT32 cDisplayHeight = pTCP->cDisplayHeight;

	int CalibrationRadiusX = cDisplayWidth / 20;
	int CalibrationRadiusY = cDisplayHeight / 20;

	switch (pTCP -> PointNumber) {
	case 0:
		pTCP->CalibrationX = cDisplayWidth / 2;
		pTCP->CalibrationY = cDisplayHeight / 2;
		break;

	case 1:
		pTCP->CalibrationX = CalibrationRadiusX * 2;
		pTCP->CalibrationY = CalibrationRadiusY * 2;
		break;

	case 2:
		pTCP->CalibrationX = CalibrationRadiusX * 2;
		pTCP->CalibrationY = cDisplayHeight - CalibrationRadiusY * 2;
		break;

	case 3:
		pTCP->CalibrationX = cDisplayWidth - CalibrationRadiusX * 2;
		pTCP->CalibrationY = cDisplayHeight - CalibrationRadiusY * 2;
		break;

	case 4:
		pTCP->CalibrationX = cDisplayWidth - CalibrationRadiusX * 2;
		pTCP->CalibrationY = CalibrationRadiusY * 2;
		break;

	default:
		pTCP->CalibrationX = cDisplayWidth / 2;
		pTCP->CalibrationY = cDisplayHeight / 2;

		return FALSE;
	}

	return TRUE;
}

HRESULT TSC2007_Driver::GetDeviceCaps(unsigned int iIndex, void* lpOutput) {
	if (lpOutput == NULL) {
		return FALSE;
	}

	switch (iIndex) {
	case TOUCH_PANEL_SAMPLE_RATE_ID: {
		TOUCH_PANEL_SAMPLE_RATE *pTSR = (TOUCH_PANEL_SAMPLE_RATE*) lpOutput;

		pTSR->SamplesPerSecondLow
				= g_TouchPanel_Sampling_Settings.SampleRate.SamplesPerSecondLow;
		pTSR->SamplesPerSecondHigh
				= g_TouchPanel_Sampling_Settings.SampleRate.SamplesPerSecondHigh;
		pTSR->CurrentSampleRateSetting
				= g_TouchPanel_Sampling_Settings.SampleRate.CurrentSampleRateSetting;
		pTSR->MaxTimeForMoveEvent_ticks
				= g_TouchPanel_Sampling_Settings.SampleRate.MaxTimeForMoveEvent_ticks;
	}
		break;

	case TOUCH_PANEL_CALIBRATION_POINT_COUNT_ID: {
		TOUCH_PANEL_CALIBRATION_POINT_COUNT *pTCPC =
				(TOUCH_PANEL_CALIBRATION_POINT_COUNT*) lpOutput;

		pTCPC->flags = 0;
		pTCPC->cCalibrationPoints = 5;
	}
		break;

	case TOUCH_PANEL_CALIBRATION_POINT_ID:
		return (CalibrationPointGet((TOUCH_PANEL_CALIBRATION_POINT*) lpOutput));

	default:
		return FALSE;
	}

	return TRUE;
}

