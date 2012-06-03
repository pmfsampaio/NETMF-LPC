////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _K60_H_
#define _K60_H_ 1

#include ".\Platform\MK60N512MD100.h"
#include ".\Platform\core_cm4.h"


//////////////////////////////////////////////////////////////////////////////
// Block driver
//

struct K60_BS_Driver
{
	static const UINT32 c_FLASH_PAGE_SIZE = 2048;
	static const UINT32 c_COMMAND_ERASE_SECTOR = 0x09;
	static const UINT32 c_COMMAND_PROGRAM_LONGWORD = 0x06;

	static BOOL ChipInitialize(void* context);

	static BOOL ChipUnInitialize(void* context);

	static const BlockDeviceInfo* GetDeviceInfo(void* context);

	static BOOL Read(void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff);

	static BOOL Write(void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff, BOOL ReadModifyWrite);

	static BOOL Memset(void* context, ByteAddress Address, UINT8 Data, UINT32 NumBytes);

	static BOOL GetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata);

	static BOOL SetSectorMetadata(void* context, ByteAddress SectorStart, SectorMetadata* pSectorMetadata);

	static BOOL IsBlockErased(void* context, ByteAddress Sector, UINT32 BlockLength);

	static BOOL EraseBlock(void* context, ByteAddress Sector);

	static void SetPowerState(void* context, UINT32 State);

	static UINT32 MaxSectorWrite_uSec(void* context);

	static UINT32 MaxBlockErase_uSec(void* context);

	static BOOL ChipReadOnly(void* context, BOOL On, UINT32 ProtectionKey);

private:
	static BOOL WriteX(void* context, ByteAddress Address, UINT32 NumBytes, BYTE * pSectorBuff, BOOL ReadModifyWrite,
			BOOL fIncrementDataPtr);
};

//////////////////////////////////////////////////////////////////////////////
// UART driver
//

struct K60_USART_Driver
{

	static const UINT32 c_COM1 = 0;
	static const UINT32 c_COM2 = 1;
	static const UINT32 c_COM3 = 2;
	static const UINT32 c_COM4 = 3;

	static const UINT32 c_COM_COUNT = 4;

	static const UINT32 c_MAX_BAUDRATE = 115200;
	static const UINT32 c_MIN_BAUDRATE = 300;

	static BOOL Initialize(int ComPortNum, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue);
	static BOOL Uninitialize(int ComPortNum);
	static BOOL TxBufferEmpty(int ComPortNum);
	static BOOL TxShiftRegisterEmpty(int ComPortNum);
	static void WriteCharToTxBuffer(int ComPortNum, UINT8 c);
	static void TxBufferEmptyInterruptEnable(int ComPortNum, BOOL Enable);
	static BOOL TxBufferEmptyInterruptState(int ComPortNum);
	static void RxBufferFullInterruptEnable(int ComPortNum, BOOL Enable);
	static BOOL RxBufferFullInterruptState(int ComPortNum);
	static BOOL TxHandshakeEnabledState(int comPortNum);
	static void ProtectPins(int ComPortNum, BOOL On);
	static void GetPins(int comPort, GPIO_PIN& rxPin, GPIO_PIN& txPin, GPIO_PIN& ctsPin, GPIO_PIN& rtsPin);
	static void GetBaudrateBoundary(int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz);
	static BOOL IsBaudrateSupported(int ComPortNum, UINT32 & BaudrateHz);

	//functions.
	static UINT32 inline GetIntNo(int ComPortNum)
	{
		switch (ComPortNum)
		{
		case c_COM1:
			return UART0_RX_TX_IRQn + 16;
			break;
		case c_COM2:
			return UART1_RX_TX_IRQn + 16;
			break;
		case c_COM3:
			return UART2_RX_TX_IRQn + 16;
			break;
		case c_COM4:
			return UART3_RX_TX_IRQn + 16;
			break;
		default:
			ASSERT( TRUE);
			return (ComPortNum);
			break;
		}
	}

private:
	static void UARTn_IntHandler(void *param);
	static UART_Type* GetUARTFromPort(int ComPortNum);
};

extern K60_USART_Driver g_K60_USART_Driver;

//////////////////////////////////////////////////////////////////////////////
// NVIC driver
//

// gets the address of the given vector index
#define GET_VECTOR(irqn) *((uint32_t *) &ARM_Vectors + irqn)

// cortex interupts are between -16 and n
#define INTC_TO_NVIC(x) ( (IRQn_Type) (x - 16) )
#define NVIC_TO_INTC(x) ( (UINT32)((int)x + 16) )

struct K60_NVIC_Driver
{
	// pointers for the vectors
	HAL_CALLBACK_FPN intVector[119];

	// pointers for the vector params
	void* intParam[119];

	//static void GlobalNVICISR();
	static void Initialize();
	static BOOL ActivateInterrupt(UINT32 Irq_Index, HAL_CALLBACK_FPN ISR, void* ISR_Param);
	static BOOL DeactivateInterrupt(UINT32 Irq_Index);
	static BOOL InterruptEnable(UINT32 Irq_Index);
	static BOOL InterruptDisable(UINT32 Irq_Index);
	static BOOL InterruptEnableState(UINT32 Irq_Index);
	static BOOL InterruptState(UINT32 Irq_Index);
};

extern K60_NVIC_Driver g_K60_NVIC_Driver;

//////////////////////////////////////////////////////////////////////////////
// GPIO driver
//

#define GPIO_PIN_MASK            0x1Fu
#define GPIO_PIN_BIT(x)              (((1)<<(x & GPIO_PIN_MASK)))

struct K60_GPIO_Driver
{
	struct PIN_ISR_DESCRIPTOR
	{
		static const UINT32 c_DebounceCount = 3;
		GPIO_INTERRUPT_SERVICE_ROUTINE m_isr;
		void* m_param;
		GPIO_PIN m_pin;
		GPIO_INT_EDGE m_intEdge;
		UINT8 m_flags;
		UINT8 m_status;

		//--//

		static const UINT8 c_Flags_Debounce = 0x01;
		static const UINT8 c_Flags_RequireLowEdge = 0x02;
		static const UINT8 c_Flags_RequireHighEdge = 0x04;

		static const UINT8 c_Status_AllowLowEdge = 0x01;
		static const UINT8 c_Status_AllowHighEdge = 0x02;

		//--//

		static void Fire(void* arg);

		void HandleDebounce(BOOL edge);
	};

	enum GPIO_NAMES
	{
		PA0,
		PA1,
		PA2,
		PA3,
		PA4,
		PA5,
		PA6,
		PA7,
		PA8,
		PA9,
		PA10,
		PA11,
		PA12,
		PA13,
		PA14,
		PA15,
		PA16,
		PA17,
		PA18,
		PA19,
		PA20,
		PA21,
		PA22,
		PA23,
		PA24,
		PA25,
		PA26,
		PA27,
		PA28,
		PA29,
		PA30,
		PA31,

		PB0,
		PB1,
		PB2,
		PB3,
		PB4,
		PB5,
		PB6,
		PB7,
		PB8,
		PB9,
		PB10,
		PB11,
		PB12,
		PB13,
		PB14,
		PB15,
		PB16,
		PB17,
		PB18,
		PB19,
		PB20,
		PB21,
		PB22,
		PB23,
		PB24,
		PB25,
		PB26,
		PB27,
		PB28,
		PB29,
		PB30,
		PB31,

		PC0,
		PC1,
		PC2,
		PC3,
		PC4,
		PC5,
		PC6,
		PC7,
		PC8,
		PC9,
		PC10,
		PC11,
		PC12,
		PC13,
		PC14,
		PC15,
		PC16,
		PC17,
		PC18,
		PC19,
		PC20,
		PC21,
		PC22,
		PC23,
		PC24,
		PC25,
		PC26,
		PC27,
		PC28,
		PC29,
		PC30,
		PC31,

		PD0,
		PD1,
		PD2,
		PD3,
		PD4,
		PD5,
		PD6,
		PD7,
		PD8,
		PD9,
		PD10,
		PD11,
		PD12,
		PD13,
		PD14,
		PD15,
		PD16,
		PD17,
		PD18,
		PD19,
		PD20,
		PD21,
		PD22,
		PD23,
		PD24,
		PD25,
		PD26,
		PD27,
		PD28,
		PD29,
		PD30,
		PD31,

		PE0,
		PE1,
		PE2,
		PE3,
		PE4,
		PE5,
		PE6,
		PE7,
		PE8,
		PE9,
		PE10,
		PE11,
		PE12,
		PE13,
		PE14,
		PE15,
		PE16,
		PE17,
		PE18,
		PE19,
		PE20,
		PE21,
		PE22,
		PE23,
		PE24,
		PE25,
		PE26,
		PE27,
		PE28,
		PE29,
		PE30,
		PE31
	};

	static const UINT32 c_MaxPins = 160;
	static const UINT32 c_MaxPorts = 5;
	static const UINT32 c_PinsPerPort = 32;

	static const INT32 c_MinDebounceTimeMs = 1; // 1 ms
	static const INT32 c_MaxDebounceTimeMs = 5000; // 5  s

	//--//

	static const UINT8 c_Gpio_Attributes[c_MaxPins];

	// applies to all GPIO
	static const UINT8 c_NumberofResistorMode = 3;
	static const UINT8 c_GPIO_ResistorMode = (1 << RESISTOR_DISABLED) | (1 << RESISTOR_PULLDOWN) | (1
			<< RESISTOR_PULLUP);

	static const UINT8 c_NumberofInterruptMode = 5;
	static const UINT8 c_GPIO_InterruptMode = (1 << GPIO_INT_EDGE_LOW) | (1 << GPIO_INT_EDGE_HIGH) | (1
			<< GPIO_INT_EDGE_BOTH) | (1 << GPIO_INT_LEVEL_HIGH) | (1 << GPIO_INT_LEVEL_LOW);

	PIN_ISR_DESCRIPTOR m_PinIsr[c_MaxPins];
	UINT32 m_PinReservationInfo[c_MaxPins];
	UINT32 m_DebounceTicks;

	//--//

	static BOOL Initialize();

	static BOOL Uninitialize();

	static UINT32 Attributes(GPIO_PIN Pin);

	static void DisablePin(GPIO_PIN Pin, GPIO_RESISTOR ResistorState, UINT32 Direction, GPIO_ALT_MODE AltFunction);

	static void EnableOutputPin(GPIO_PIN Pin, BOOL InitialState);

	static BOOL EnableInputPin(GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR,
			void* ISR_Param, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState);

	static BOOL GetPinState(GPIO_PIN Pin);

	static void SetPinState(GPIO_PIN Pin, BOOL PinState);

	static void ISR(void* Param);

	static void SetResistor(GPIO_PIN Pin, GPIO_RESISTOR ResistorState);

	static BOOL PinIsBusy(GPIO_PIN Pin);

	static BOOL ReservePin(GPIO_PIN Pin, BOOL fReserve);

	static UINT32 GetDebounce();

	static BOOL SetDebounce(INT64 debounceTimeMilliseconds);

	static INT32 GetPinCount();

	static void GetPinsMap(UINT8* pins, size_t size);

private:

	static UINT32 PinToPort(GPIO_PIN pin)
	{
		ASSERT(pin < c_MaxPins);

		return pin / c_PinsPerPort;
	}

	static UINT32 PinToBit(GPIO_PIN pin)
	{
		ASSERT(pin < c_MaxPins);

		return pin % c_PinsPerPort;
	}

	static UINT32 BitToPin(UINT32 bit, UINT32 port)
	{
		ASSERT(bit < c_PinsPerPort);
		ASSERT(port < c_MaxPorts);

		return bit + (port * c_PinsPerPort);
	}

	static PORT_Type* PortToPortReg(UINT32 port)
	{
		switch (port)
		{
		case 0:
			return PORTA;
		case 1:
			return PORTB;
		case 2:
			return PORTC;
		case 3:
			return PORTD;
		case 4:
			return PORTE;
		default:
			ASSERT( FALSE);
			return NULL;
		}
	}

	static GPIO_Type* PortToGPIOReg(UINT32 port)
	{
		switch (port)
		{
		case 0:
			return PTA;
		case 1:
			return PTB;
		case 2:
			return PTC;
		case 3:
			return PTD;
		case 4:
			return PTE;
		default:
			ASSERT( FALSE);
			return NULL;
		}
	}

	static void STUB_ISRVector(GPIO_PIN Pin, BOOL PinState, void* Param);

	static void PORTn_ISR(void* param);
};

extern K60_GPIO_Driver g_K60_GPIO_Driver;

//////////////////////////////////////////////////////////////////////////////
// TIME Driver
//
struct K60_TIME_Driver
{
	static const UINT32 c_MaxTimerValue = 0xFFFFFF;

	UINT64 m_Tick;
	UINT64 m_nextCompare;

	static BOOL Initialize();
	static BOOL Uninitialize();
	static UINT64 CounterValue();
	static void SetCompareValue(UINT64 CompareValue);
	static INT64 TicksToTime(UINT64 Ticks);
	static INT64 CurrentTime();
	static void Sleep_uSec(UINT32 uSec);
	static void Sleep_uSec_Loop(UINT32 uSec);
	static void ISR(void*);
};

extern K60_TIME_Driver g_K60_TIME_Driver;

///////////////////////////////////////////////////////////////////////////////
// USB SECTION
//

struct K60_USB_CONFIG
{
	HAL_DRIVER_CONFIG_HEADER Header;

	//--//

	static LPCSTR GetDriverName()
	{
		return "K60_USB";
	}
};

extern K60_USB_CONFIG* const g_pK60_USB_Config;

//////////////////////////////////////////////////////////////////////////////
// USB driver
//

#include <..\pal\com\usb\USB.h>

// helpers to convert endpoint to BDT index
#define EPIN_BDT_INDEX(ep) 		((ep * 4) + 2)
#define EPOUT_BDT_INDEX(ep) 	(ep * 4)

struct K60_USB_Driver
{
	// who owns the BDT entry
	static const UINT8 c_MCU = 0x00;
	static const UINT8 c_SIE = 0x80;

	// data toggle
	static const UINT8 c_DATA0 = 0x00;
	static const UINT8 c_DATA1 = 0x40;

	// data toggle sync
	static const UINT8 c_DTS = 0x08;

	static const UINT8 c_UDATA0 = c_SIE | c_DATA0 | c_DTS;
	static const UINT8 c_UDATA1 = c_SIE | c_DATA1 | c_DTS;

	// USB Fractional Divider Value
	static const UINT8 c_USB_FRACTIONAL_VALUE = 0x02;

	static const UINT32 c_max_packet_size = 64;
	static const UINT32 c_Used_Endpoints = 7;
	static const UINT32 c_default_ctrl_packet_size = 32;
	static const UINT32 c_MaxBuffers = 16;

	// endpoint buffers
	UINT8 Buffers[c_MaxBuffers][c_max_packet_size];

	USB_CONTROLLER_STATE* pUsbControllerState;

	UINT16 EndpointStatus[c_Used_Endpoints];
	BOOL EndpointDisabled[c_Used_Endpoints];
	BOOL TxRunning[USB_MAX_QUEUES];
	BOOL TxNeedZLPS[USB_MAX_QUEUES];

	UINT8 PreviousDeviceState;
	UINT8 ExpectedToggle[USB_MAX_QUEUES];
	BOOL PinsProtected;
	BOOL FirstDescriptorPacket;

	//--//

	static USB_CONTROLLER_STATE * GetState(int Controller);

	static HRESULT Initialize(int Controller);

	static HRESULT Uninitialize(int Controller);

	static BOOL StartOutput(USB_CONTROLLER_STATE* State, int endpoint);

	static BOOL RxEnable(USB_CONTROLLER_STATE* State, int endpoint);

	static BOOL GetInterruptState();

	static BOOL ProtectPins(int Controller, BOOL On);

private:
	static void StartHardware();
	static void StopHardware();
	static void ClearTxQueue(USB_CONTROLLER_STATE* State, int endpoint);
	static void TxPacket(USB_CONTROLLER_STATE* State, int endpoint);
	static void ControlNext();
	static void ResetEvent();

	static void EndpointInTransfer(UINT8 ep, UINT8 *data, UINT8 size);
	static UINT8 EndpointOutTransfer(UINT8 ep, UINT8 *data, BOOL DisableRx);
	static void SetupEndpoints(void);

	static void Global_ISR(void* Param);
	static void EP0_ISR();
	static void EP_TxISR(int endpoint);
	static void EP_RxISR(int endpoint);
};

extern K60_USB_Driver g_K60_USB_Driver;

//////////////////////////////////////////////////////////////////////////////
// USB Client port
// 
struct K60_USB
{
	union EndpointConfiguration
	{
		struct
		{
			unsigned EE :1; // Endpoint enable (1 = enable)
			unsigned DE :1; // Double buffer enable (1 = double buffered)
			unsigned MPS :10; // Maximum packet size (iso=1-1023, blk=8,16,32,64, int=1-64
			unsigned ED :1; // Endpoint direction (1 = IN)
			unsigned ET :2; // Endpoint type (1=iso, 2=blk, 3=int)
			unsigned EN :4; // Endpoint number (1-15)
			unsigned AISN :3; // Alternate Interface number
			unsigned IN :3; // Interface number
			unsigned CN :2; // Configuration number
		} bits;
		UINT32 word;
	};
};

#pragma pack(1)
typedef union _tBDT_STAT
{
	UINT8 _byte;
	struct
	{
		UINT8 :1;
		UINT8 :1;
		UINT8 BSTALL :1; //Buffer Stall Enable
		UINT8 DTS :1; //Data Toggle Synch Enable
		UINT8 NINC :1; //Address Increment Disable
		UINT8 KEEP :1; //BD Keep Enable
		UINT8 DATA :1; //Data Toggle Synch Value
		UINT8 UOWN :1; //USB Ownership
	} McuCtlBit;

	struct
	{
		UINT8 :2;
		UINT8 PID :4; //Packet Identifier
		UINT8 :1;
		UINT8 UOWN :1;
	} RecPid;
} tBDT_STAT; //Buffer Descriptor Status Register

typedef struct _tBDT
{
	tBDT_STAT Stat;
	UINT8 dummy;
	UINT16 Cnt;
	UINT32 Addr;
} tBDT;
#pragma pack()


//--//


//////////////////////////////////////////////////////////////////////////////
// K60_I2C_DRIVER
//

#define K60_TWI_SDA        K60_GPIO_Driver::PD9
#define K60_TWI_SCL        K60_GPIO_Driver::PD8

struct K60_I2C_Driver
{
    I2C_HAL_XACTION*       m_currentXAction;
    I2C_HAL_XACTION_UNIT*  m_currentXActionUnit;
    BOOL                   m_initialized;

    //--//

    static const UINT8 c_DirectionWrite = 0x00;
    static const UINT8 c_DirectionRead  = 0x01;

    static UINT16 s_Divider[64];

    static BOOL Initialize();
    static BOOL Uninitialize();
    static void MasterXAction_Start( I2C_HAL_XACTION* xAction, bool repeatedStart );
    static void MasterXAction_Stop();
    static void GetClockRate( UINT32 rateKhz, UINT8& clockRate, UINT8& clockRate2 );

    static void WriteToSubordinate( I2C_HAL_XACTION_UNIT* unit );
    static void ReadFromSubordinate( I2C_HAL_XACTION_UNIT* unit );
    static void GetPins(GPIO_PIN& scl, GPIO_PIN& sda);

private:
    static void ISR( void* arg );

};

extern K60_I2C_Driver g_K60_I2C_Driver;

//////////////////////////////////////////////////////////////////////////////
// K60_SPI_DRIVER
//
struct K60_SPI_Driver
{
    static const int SPI_0 = 0;
    static const int SPI_1 = 1;
    static const int c_MAX_SPI = 3;

    BOOL      m_initialized[c_MAX_SPI];
    BOOL      m_Enabled    [c_MAX_SPI];

    static UINT16 s_Divider[16];

    static BOOL Initialize  ();
    static void Uninitialize();
    static void GetPins( UINT32 spi_mod, GPIO_PIN& msk, GPIO_PIN& miso, GPIO_PIN& mosi );

    static BOOL nWrite16_nRead16( const SPI_CONFIGURATION& Configuration, UINT16* Write16, INT32 WriteCount, UINT16* Read16, INT32 ReadCount, INT32 ReadStartOffset );
    static BOOL nWrite8_nRead8  ( const SPI_CONFIGURATION& Configuration, UINT8*  Write8 , INT32 WriteCount, UINT8*  Read8 , INT32 ReadCount, INT32 ReadStartOffset );

    static BOOL Xaction_Start( const SPI_CONFIGURATION& Configuration );
    static BOOL Xaction_Stop ( const SPI_CONFIGURATION& Configuration );

    static BOOL Xaction_nWrite16_nRead16( SPI_XACTION_16& Transaction );
    static BOOL Xaction_nWrite8_nRead8  ( SPI_XACTION_8&  Transaction );

private:
    static void ISR( void* Param );
    static SPI_Type* GetSPI(int spiNum);

};

//--//

extern K60_SPI_Driver g_K60_SPI_Driver;

#endif // _K60_H_

