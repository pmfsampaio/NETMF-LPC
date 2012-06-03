//-----------------------------------------------------------------------------
// Software that is described herein is for illustrative purposes only  
// which provides customers with programming information regarding the  
// products. This software is supplied "AS IS" without any warranties.  
// NXP Semiconductors assumes no responsibility or liability for the 
// use of the software, conveys no license or title under any patent, 
// copyright, or mask work right to the product. NXP Semiconductors 
// reserves the right to make changes in the software without 
// notification. NXP Semiconductors also make no representation or 
// warranty that such application will be suitable for the specified 
// use without further testing or modification. 
//-----------------------------------------------------------------------------

#include <tinyhal.h>
#include "..\LPC1788_Devices.h"

//--//
// TEMP FOR COMPILE success purpose

#define SET_BITS(Var,Shift,Mask,fieldsMask) {Var = setFieldValue(Var,Shift,Mask,fieldsMask);}

FORCEINLINE UINT32 setFieldValue(volatile UINT32 oldVal, UINT32 shift,
		UINT32 mask, UINT32 val) {
	volatile UINT32 temp = oldVal;

	temp &= ~mask;
	temp |= val << shift;
	return temp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_LPC178X_USART_Driver"
#endif

LPC178X_USART_Driver g_LPC178X_USART_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

//--//

BOOL CPU_USART_Initialize(int ComPortNum, int BaudRate, int Parity,
		int DataBits, int StopBits, int FlowValue) {
	return LPC178X_USART_Driver::Initialize(ComPortNum, BaudRate, Parity,
			DataBits, StopBits, FlowValue);
}

BOOL CPU_USART_Uninitialize(int ComPortNum) {
	return LPC178X_USART_Driver::Uninitialize(ComPortNum);
}

BOOL CPU_USART_TxBufferEmpty(int ComPortNum) {
	return LPC178X_USART_Driver::TxBufferEmpty(ComPortNum);
}

BOOL CPU_USART_TxShiftRegisterEmpty(int ComPortNum) {
	return LPC178X_USART_Driver::TxShiftRegisterEmpty(ComPortNum);
}

void CPU_USART_WriteCharToTxBuffer(int ComPortNum, UINT8 c) {
	LPC178X_USART_Driver::WriteCharToTxBuffer(ComPortNum, c);
}

void CPU_USART_TxBufferEmptyInterruptEnable(int ComPortNum, BOOL Enable) {
	LPC178X_USART_Driver::TxBufferEmptyInterruptEnable(ComPortNum, Enable);
}

BOOL CPU_USART_TxBufferEmptyInterruptState(int ComPortNum) {
	return LPC178X_USART_Driver::TxBufferEmptyInterruptState(ComPortNum);
}

void CPU_USART_RxBufferFullInterruptEnable(int ComPortNum, BOOL Enable) {
	LPC178X_USART_Driver::RxBufferFullInterruptEnable(ComPortNum, Enable);
}

BOOL CPU_USART_RxBufferFullInterruptState(int ComPortNum) {
	return LPC178X_USART_Driver::RxBufferFullInterruptState(ComPortNum);
}

BOOL CPU_USART_TxHandshakeEnabledState(int comPort) {
	return LPC178X_USART_Driver::TxHandshakeEnabledState(comPort);
}

void CPU_USART_ProtectPins(int ComPortNum, BOOL On) {
	LPC178X_USART_Driver::ProtectPins(ComPortNum, On);
}

UINT32 CPU_USART_PortsCount() {
	return TOTAL_USART_PORT;
}

void CPU_USART_GetPins(int ComPortNum, GPIO_PIN& rxPin, GPIO_PIN& txPin,
		GPIO_PIN& ctsPin, GPIO_PIN& rtsPin) {
	return LPC178X_USART_Driver::GetPins(ComPortNum, rxPin, txPin, ctsPin,
			rtsPin);
}

BOOL CPU_USART_SupportNonStandardBaudRate(int ComPortNum) {
	return TRUE;
}

void CPU_USART_GetBaudrateBoundary(int ComPortNum, UINT32& maxBaudrateHz,
		UINT32& minBaudrateHz) {
	return LPC178X_USART_Driver::BaudrateBoundary(ComPortNum, maxBaudrateHz,
			minBaudrateHz);
}

BOOL CPU_USART_IsBaudrateSupported(int ComPortNum, UINT32& BaudrateHz) {
	return LPC178X_USART_Driver::IsBaudrateSupported(ComPortNum, BaudrateHz);
}

//--//

BOOL LPC178X_USART_Driver::IsValidPortNum(int ComPortNum) {
	if ((ComPortNum >= (int) 0) || (ComPortNum <= (int) TOTAL_USART_PORT))
		return TRUE;
	return FALSE;
}

//--//

#define UART_TX_FIFO_SIZE 16

void LPC178X_USART_Driver::IntTransmit(int ComPortNum)
{
	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);
	volatile register UINT32 * regTHR = &(USARTC.SEL1.RBR.UART_THR);
	volatile register UINT32 * regLSR = &(USARTC.UART_LSR);
	int fifo_cnt;

    // Disable THRE interrupt
	USARTC.SEL2.IER.UART_IER &= ~(LPC178X_USART::UART_IER_THREIE);
	/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
	 * of data or break whenever ring buffers are empty */
	/* Wait until THR empty */
    //while (UART_CheckBusy(_LPC_UART) == SET);

	while (!(USART_BytesInBuffer(ComNum,FALSE)==0)) //;__BUF_IS_EMPTY(rb.tx_head,rb.tx_tail))
    {
		if (!(*regLSR & UART_LSR_THRE)) {
			break;
		}
		fifo_cnt = UART_TX_FIFO_SIZE;
		while (fifo_cnt) {
			USART_RemoveCharFromTxBuffer(ComNum, c)) {
			*regTHR = c;
		}
    }

    /* If there is no more data to send, disable the transmit
       interrupt - else enable it or keep it enabled */
	if ((USART_BytesInBuffer(ComNum,FALSE)==0)) {
    	// Reset Tx Interrupt state
    	TxIntStat = RESET;
		USARTC.SEL2.IER.UART_IER &= ~(LPC178X_USART::UART_IER_THREIE);
    }
    else{
      	// Set Tx Interrupt state
		TxIntStat = SET;
		USARTC.SEL2.IER.UART_IER |= ~(LPC178X_USART::UART_IER_THREIE);
    }
}

void LPC178X_USART_Driver::UART_IntHandler(void *param) {
	GLOBAL_LOCK(irq);

	ASSERT(LPC178X_USART_Driver::IsValidPortNum((UINT32)param));

	int fifo_cnt;
	char c;
	UINT32 ComNum = (UINT32) param;
	LPC178X_USART& USARTC = LPC178X::UART(ComNum);
	volatile UINT32 IIR_Value;
	volatile UINT32 LSR_Value;

	volatile register UINT32 * regRBR = &(USARTC.SEL1.RBR.UART_RBR);
	volatile register UINT32 * regTHR = &(USARTC.SEL1.RBR.UART_THR);
	volatile register UINT32 * regLSR = &(USARTC.UART_LSR);

	/* Determine the interrupt source */
	IIR_Value = USARTC.SEL3.IIR.UART_IIR & LPC178X_USART::UART_IIR_IID_mask;

	// Receive Line Status
	if (IIR_Value == LPC178X_USART::UART_IIR_IID_Irpt_RLS) { //UART_IIR_INTID_RLS){
		// Check line status
		LSR_Value = USARTC.UART_LSR;
		Events_Set( USART_EVENT_ERROR_OVERRUN );
	}

	// Receive Data Available or Character time-out
	if ((IIR_Value == LPC178X_USART::UART_IIR_IID_Irpt_RDA) ||
			(IIR_Value == LPC178X_USART::UART_IIR_IID_Irpt_TOUT)) {//UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
		while(1){
			// Call UART read function in UART driver
			if (!(*regLSR & LPC178X_USART::UART_LSR_RFDR)) {
				break;
			}
			else {
				USART_AddCharToRxBuffer(ComNum, (UINT8) *regRBR);
			}
		}
	}

	// Transmit Holding Empty
	if (IIR_Value == LPC178X_USART::UART_IIR_IID_Irpt_TOUT) {// UART_IIR_INTID_THRE){
	    // Disable THRE interrupt
		USARTC.SEL2.IER.UART_IER &= ~(LPC178X_USART::UART_IER_THREIE);
		/* Wait for FIFO buffer empty, transfer UART_TX_FIFO_SIZE bytes
		 * of data or break whenever ring buffers are empty */
		/* Wait until THR empty */
	    //while (UART_CheckBusy(_LPC_UART) == SET);

		while (!(USART_BytesInBuffer(ComNum,FALSE)==0)) //;__BUF_IS_EMPTY(rb.tx_head,rb.tx_tail))
	    {
			if (!(*regLSR & UART_LSR_THRE)) {
				break;
			}
			fifo_cnt = UART_TX_FIFO_SIZE;
			while (fifo_cnt) {
				USART_RemoveCharFromTxBuffer(ComNum, c)) {
				*regTHR = c;
			}
	    }

	    /* If there is no more data to send, disable the transmit
	       interrupt - else enable it or keep it enabled */
		if ((USART_BytesInBuffer(ComNum,FALSE)==0)) {
	    	// Reset Tx Interrupt state
	    	TxIntStat = RESET;
			USARTC.SEL2.IER.UART_IER &= ~(LPC178X_USART::UART_IER_THREIE);
	    }
	    else{
	      	// Set Tx Interrupt state
			TxIntStat = SET;
			USARTC.SEL2.IER.UART_IER |= ~(LPC178X_USART::UART_IER_THREIE);
	    }
	}
}

//--//

BOOL LPC178X_USART_Driver::Initialize(int ComPortNum, int BaudRate, int Parity,
		int DataBits, int StopBits, int FlowValue) {

	GLOBAL_LOCK(irq);
	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);
	UINT32 divisor;
	BOOL fRet = TRUE;

	ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	//calculate the divisor that's required.
	divisor = ((LPC178X_USART::c_ClockRate / (BaudRate * 16)));

	// CWS: Disable interrupts
	USARTC.UART_LCR = 0; // prepare to Init UART
	USARTC.SEL2.IER.UART_IER &= ~(LPC178X_USART::UART_IER_INTR_ALL_SET); // Disable all UART interrupts
	/* CWS: Set baud rate to baudRate bps */
	USARTC.UART_LCR |= LPC178X_USART::UART_LCR_DLAB; // prepare to access Divisor
	USARTC.SEL1.DLL.UART_DLL = divisor & 0xFF;      //GET_LSB(divisor);                                                      // Set baudrate.
	USARTC.SEL2.DLM.UART_DLM = (divisor>>8) & 0xFF; // GET_MSB(divisor);
	USARTC.UART_FDR = 0x75;
	USARTC.UART_LCR &= ~LPC178X_USART::UART_LCR_DLAB; // prepare to access RBR, THR, IER
	// CWS: Set port for 8 bit, 1 stop, no parity

	// DataBit range 5-8
	if (5 <= DataBits && DataBits <= 8) {
		SET_BITS(USARTC.UART_LCR, LPC178X_USART::UART_LCR_WLS_shift,
				LPC178X_USART::UART_LCR_WLS_mask, DataBits-5);
	} else { // not supported
		fRet = FALSE;

		// set up 8 data bits incase return value is ignored
		SET_BITS(USARTC.UART_LCR, LPC178X_USART::UART_LCR_WLS_shift,
				LPC178X_USART::UART_LCR_WLS_mask,
				LPC178X_USART::UART_LCR_WLS_8_BITS);
	}

	switch (StopBits) {
	case USART_STOP_BITS_ONE:
		USARTC.UART_LCR |= LPC178X_USART::UART_LCR_NSB_1_STOPBITS;
		break;
	case USART_STOP_BITS_ONEPOINTFIVE:
		USARTC.UART_LCR |= LPC178X_USART::UART_LCR_NSB_15_STOPBITS;
		break;

		// not supported
	case USART_STOP_BITS_NONE:
	default:
		fRet = FALSE;
		break;
	}

	switch (Parity) {
	case USART_PARITY_SPACE:
		USARTC.UART_LCR |= LPC178X_USART::UART_LCR_SPE;
	case USART_PARITY_EVEN:
		USARTC.UART_LCR |= (LPC178X_USART::UART_LCR_EPE
				| LPC178X_USART::UART_LCR_PBE);
		break;

	case USART_PARITY_MARK:
		USARTC.UART_LCR |= LPC178X_USART::UART_LCR_SPE;
	case USART_PARITY_ODD:
		USARTC.UART_LCR |= LPC178X_USART::UART_LCR_PBE;
		break;

		// not supported
	case USART_PARITY_NONE:
	default:
		fRet = FALSE;
		break;
	}

	divisor = USARTC.UART_LSR;
	// CWS: Set the RX FIFO trigger level (to 8 bytes), reset RX, TX FIFO
	USARTC.SEL3.FCR.UART_FCR = (LPC178X_USART::UART_FCR_RFITL_08
			<< LPC178X_USART::UART_FCR_RFITL_shift)
			| LPC178X_USART::UART_FCR_TFR | LPC178X_USART::UART_FCR_RFR
			| LPC178X_USART::UART_FCR_FME;

	/*
	 * Do not enable transmit interrupt here, since it is handled by
	 * UART_Send() function, just to reset Tx Interrupt state for the
	 * first time
	 */
	TxIntStat = RESET;

	CPU_INTC_ActivateInterrupt(LPC178X_USART::getIntNo(ComPortNum),
			UART_IntHandler, (void *) ComPortNum);

	USARTC.SEL2.IER.UART_IER |= LPC178X_USART::UART_IER_THRE ||
			LPC178X_USART::UART_IER_RBRE || LPC178X_USART::UART_IER_RLSIE;

	/* preemption = 1, sub-priority = 1 */
//	NVIC_SetPriority(_UART_IRQ, ((0x01 << 3) | 0x01));

//	ProtectPins(ComPortNum, FALSE);

	return fRet;
}

BOOL LPC178X_USART_Driver::Uninitialize(int ComPortNum) {

	GLOBAL_LOCK(irq);
	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);

	ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	USARTC.SEL2.IER.UART_IER &= ~(LPC178X_USART::UART_IER_INTR_ALL_SET); // Disable all UART interrupt

	// CWS: Disable interrupts
	USARTC.SEL3.FCR.UART_FCR = 0;
	USARTC.UART_LCR = 0; // prepare to Init UART
	ProtectPins(ComPortNum, TRUE);

	return TRUE;
}

BOOL LPC178X_USART_Driver::TxBufferEmpty(int ComPortNum) {
	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);

    ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	if (USARTC.UART_LSR & LPC178X_USART::UART_LSR_THRE)
		return TRUE;
	return FALSE;
}

BOOL LPC178X_USART_Driver::TxShiftRegisterEmpty(int ComPortNum) {
	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);

    ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	if (USARTC.UART_LSR & LPC178X_USART::UART_LSR_TE)
		return TRUE;
	return FALSE;
}

void LPC178X_USART_Driver::WriteCharToTxBuffer(int ComPortNum, UINT8 c) {

	ASSERT(0);

	UINT32 ui32Char = (UINT32) c;
	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);

	ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	while (FALSE == TxBufferEmpty(ComPortNum))
		; //wait till ready.

	//transmit the character.
	USARTC.SEL1.THR.UART_THR = ui32Char;
}

void LPC178X_USART_Driver::TxBufferEmptyInterruptEnable(int ComPortNum,
		BOOL Enable) {
	GLOBAL_LOCK(irq);

    ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);

	if (Enable) {
		/*
		 * Check if current Tx interrupt enable is reset,
		 * that means the Tx interrupt must be re-enabled
		 * due to call UART_IntTransmit() function to trigger
		 * this interrupt type
		 */
		if (TxIntStat == RESET) {
			IntTransmit(ComPortNum);
		}
		else {
			USARTC.SEL2.IER.UART_IER |= (LPC178X_USART::UART_IER_THREIE);
		}
	} else {
		USARTC.SEL2.IER.UART_IER &= ~(LPC178X_USART::UART_IER_THREIE);
	}

}

BOOL LPC178X_USART_Driver::TxBufferEmptyInterruptState(int ComPortNum) {
	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);

    ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	if (USARTC.SEL2.IER.UART_IER & (LPC178X_USART::UART_IER_THREIE))
		return TRUE;
	return FALSE;
}

void LPC178X_USART_Driver::RxBufferFullInterruptEnable(int ComPortNum,
		BOOL Enable) {

	GLOBAL_LOCK(irq);

	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);

    ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	if (Enable) {
		USARTC.SEL2.IER.UART_IER |= (LPC178X_USART::UART_IER_RDAIE);
	} else {
		hal_printf("RxBufferFull - should pull HW handshake\n");
		ASSERT(0);
		USARTC.SEL2.IER.UART_IER &= ~(LPC178X_USART::UART_IER_RDAIE);
	}
}

BOOL LPC178X_USART_Driver::RxBufferFullInterruptState(int ComPortNum) {
	LPC178X_USART& USARTC = LPC178X::UART(ComPortNum);

	ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	if (USARTC.SEL2.IER.UART_IER & (LPC178X_USART::UART_IER_RDAIE))
		return TRUE;
	return FALSE;
}

BOOL LPC178X_USART_Driver::TxHandshakeEnabledState(int ComPortNum) {
	// TODO: Add handshake code
	return TRUE;
}

void LPC178X_USART_Driver::ProtectPins(int ComPortNum, BOOL On) {
	ASSERT(LPC178X_USART_Driver::IsValidPortNum(ComPortNum));

	static BOOL COM1_PinsProtected = TRUE; // start out doing work on first unprotect
	static BOOL COM2_PinsProtected = TRUE; // start out doing work on first unprotect
	static BOOL COM3_PinsProtected = TRUE; // start out doing work on first unprotect
	static BOOL COM4_PinsProtected = TRUE; // start out doing work on first unprotect

	GLOBAL_LOCK(irq);

	UINT32 SER_TXD;
	UINT32 SER_RXD;
	BOOL* PinsProtected;

	switch (ComPortNum) {
	case c_COM1:
		SER_TXD = LPC178X_USART::c_SER1_TXD;
		SER_RXD = LPC178X_USART::c_SER1_RXD;
		PinsProtected = &COM1_PinsProtected;
		break;
	case c_COM2:
		SER_TXD = LPC178X_USART::c_SER2_TXD;
		SER_RXD = LPC178X_USART::c_SER2_RXD;
		PinsProtected = &COM2_PinsProtected;
		break;
	case c_COM3:
		SER_TXD = LPC178X_USART::c_SER3_TXD;
		SER_RXD = LPC178X_USART::c_SER3_RXD;
		PinsProtected = &COM3_PinsProtected;
		break;
	case c_COM4:
		SER_TXD = LPC178X_USART::c_SER4_TXD;
		SER_RXD = LPC178X_USART::c_SER4_RXD;
		PinsProtected = &COM4_PinsProtected;
		break;
	default:
		return;
	}

	if (On) {

		if (!*PinsProtected) {
			*PinsProtected = TRUE;

			TxBufferEmptyInterruptEnable(ComPortNum, FALSE);
			// TODO Add config for uart pin protected state
//			CPU_GPIO_EnableOutputPin(SER_TXD, RESISTOR_DISABLED);

			RxBufferFullInterruptEnable(ComPortNum, FALSE);
			// TODO Add config for uart pin protected state
//			CPU_GPIO_EnableOutputPin(SER_RXD, RESISTOR_DISABLED);
		}
	} else {
		if (*PinsProtected) {
			*PinsProtected = FALSE;

			// Connect pin to UART
//            CPU_GPIO_DisablePin( SER_TXD, RESISTOR_DISABLED, GPIO_ATTRIBUTE_NONE, GPIO_ALT_MODE_1 );

			// Connect pin to UART
//            CPU_GPIO_DisablePin( SER_RXD, RESISTOR_DISABLED, GPIO_ATTRIBUTE_NONE, GPIO_ALT_MODE_1 );

			TxBufferEmptyInterruptEnable(ComPortNum, FALSE); //TRUE );

			RxBufferFullInterruptEnable(ComPortNum, TRUE);

		}
	}

}

void LPC178X_USART_Driver::GetPins(int comPort, GPIO_PIN& rxPin,
		GPIO_PIN& txPin, GPIO_PIN& ctsPin, GPIO_PIN& rtsPin) {
	switch (comPort) {
	case c_COM1:
		txPin = LPC178X_USART::c_SER1_TXD;
		rxPin = LPC178X_USART::c_SER1_RXD;
		ctsPin = GPIO_PIN_NONE;
		rtsPin = GPIO_PIN_NONE;
		break;
	case c_COM2:
		txPin = LPC178X_USART::c_SER2_TXD;
		rxPin = LPC178X_USART::c_SER2_RXD;
		ctsPin = GPIO_PIN_NONE;
		rtsPin = GPIO_PIN_NONE;

		break;

	default:
		return;
	}
}

void LPC178X_USART_Driver::BaudrateBoundary(int ComPortNum,
		UINT32& maxBaudrateHz, UINT32& minBaudrateHz) {
	// same for both UART
	maxBaudrateHz = LPC178X_USART::c_MAX_BAUDRATE;
	minBaudrateHz = LPC178X_USART::c_MIN_BAUDRATE;

}

BOOL LPC178X_USART_Driver::IsBaudrateSupported(int ComPortNum,
		UINT32 & BaudrateHz) {

	if (BaudrateHz <= LPC178X_USART::c_MAX_BAUDRATE) {
		return true;
	} else {

		BaudrateHz = LPC178X_USART::c_MAX_BAUDRATE;
		return false;
	}
}

#if 0
{
	UINT32 divisor;
	UINT32 newBR = LPC178X_USART::c_MAX_BAUDRATE;

	// same for both UART
	if (BaudrateHz <= LPC178X_USART::c_MAX_BAUDRATE)
	{

		divisor = ((LPC178X_USART::c_ClockRate / (BaudrateHz * 16)));
		newBR = ((LPC178X_USART::c_ClockRate / (divisor * 16)));

		if (newBR == BaudrateHz)
		{
			debug_printf( "TTTsupport br %d \r\n", BaudrateHz );
			return true;
		}
	}
	BaudrateHz = newBR;
	debug_printf( "FFFsupport br %d \r\n", BaudrateHz );
	return false;

}
#endif
