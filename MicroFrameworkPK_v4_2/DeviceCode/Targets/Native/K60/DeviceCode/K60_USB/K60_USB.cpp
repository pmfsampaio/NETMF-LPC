////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <tinyhal.h>
#include "..\K60.h"

// Pointer to BDT Map Structure 

#if defined(__GNUC__)
__attribute__ ((aligned (512)))
#else
__align(512)
#endif
tBDT tBDTtable[K60_USB_Driver::c_MaxBuffers];

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_K60_USB_Driver"
#endif

K60_USB_Driver g_K60_USB_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "UsbBusState"
#endif

USB_CONTROLLER_STATE UsbControllerState[1]; // Only 1 USB Controller for this device

Hal_Queue_KnownSize<USB_PACKET64, USB_QUEUE_PACKET_COUNT> QueueBuffers[K60_USB_Driver::c_Used_Endpoints - 1];

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

//--//
//#if defined(DRIVER_K60_USB)


/***************************************************************************/

// Corresponds to endpoint configuration RAM at K60_USB::UDCCRx
static K60_USB::EndpointConfiguration EndpointInit[K60_USB_Driver::c_Used_Endpoints];

//--//

USB_CONTROLLER_STATE * K60_USB_Driver::GetState(int Controller)
{
    if (Controller != 0) // There is only one controller for this device
        return NULL;
    return &UsbControllerState[0];
}

HRESULT K60_USB_Driver::Initialize(int Controller)
{
    int endpointsUsed = 0;
    const USB_ENDPOINT_DESCRIPTOR *ep = NULL;
    const USB_INTERFACE_DESCRIPTOR *itfc = NULL;
    USB_CONTROLLER_STATE &State = UsbControllerState[0];

    GLOBAL_LOCK( irq);

    //USART_Initialize( ConvertCOM_ComPort(USART_DEFAULT_PORT), HalSystemConfig.USART_DefaultBaudRate, USART_PARITY_NONE, 8, USART_STOP_BITS_ONE, USART_FLOW_NONE );

    for (int i = 0; i < c_Used_Endpoints; i++)
    {
        EndpointInit[i].word = 0; // All endpoints initialise to unused
    }

    // For all endpoints in the USB configuration
    while (USB_NextEndpoint(&State, ep, itfc))
    {
        UINT8 endpointNum = ep->bEndpointAddress & 0x7F;
        UINT16 endpointSize = ep->wMaxPacketSize;

        // Check interface and endpoint numbers against hardware capability
        if (endpointNum >= c_Used_Endpoints || itfc->bInterfaceNumber > 7)
            return S_FALSE;

        EndpointInit[endpointNum].bits.EN = endpointNum;
        EndpointInit[endpointNum].bits.ED = (ep->bEndpointAddress & 0x80) ? 1 : 0;
        EndpointInit[endpointNum].bits.IN = itfc->bInterfaceNumber;
        EndpointInit[endpointNum].bits.ET = ep->bmAttributes & 0x03;
        EndpointInit[endpointNum].bits.CN = 1; // Always only 1 configuration = 1
        EndpointInit[endpointNum].bits.AISN = 0; // No alternate interfaces
        EndpointInit[endpointNum].bits.EE = 1; // Enable this endpoint

        // Set the maximum size of the endpoint hardware FIFO
        if ((ep->bmAttributes & 0x03) == USB_ENDPOINT_ATTRIBUTE_BULK)
        {
            // If the endpoint maximum size in the configuration list is bogus
            if (endpointSize != 8 && endpointSize != 16 && endpointSize != 32 && endpointSize != 64)
                return S_FALSE;
            EndpointInit[endpointNum].bits.MPS = endpointSize;
            State.MaxPacketSize[endpointNum] = endpointSize;
        }
        else if ((ep->bmAttributes & 0x03) == USB_ENDPOINT_ATTRIBUTE_INTERRUPT)
        {
            if (endpointSize == 0 || endpointSize > 64)
                return S_FALSE;
            EndpointInit[endpointNum].bits.MPS = endpointSize;
            State.MaxPacketSize[endpointNum] = endpointSize;
        }
        else // Isochronous endpoint
        {
            if (endpointSize > 64)
                endpointSize = 64;
            EndpointInit[endpointNum].bits.MPS = endpointSize;
            State.MaxPacketSize[endpointNum] = endpointSize;
        }

        // Since endpoint 0 is only used for control, there is never a need to allocate a buffer for it
        // In fact State.Queues[0] is always NULL - it is a cheap placeholder to make the queueIndex = endpointIndex
        QueueBuffers[endpointNum - 1].Initialize(); // Clear queue before use
        State.Queues[endpointNum] = &QueueBuffers[endpointNum - 1]; // Attach queue to endpoint

        // Set up direction information
        if (EndpointInit[endpointNum].bits.ED) // If transmit endpoint
        {
            EndpointInit[endpointNum].bits.DE = 1; // Only transmit is double buffered
            State.IsTxQueue[endpointNum] = TRUE;
        }
        else // If receive endpoint
        {
            EndpointInit[endpointNum].bits.DE = 0;
            State.IsTxQueue[endpointNum] = FALSE;
        }
        endpointsUsed++;
    }

    // If no endpoints were initialised, something is seriously wrong with the configuration list
    if (0 == endpointsUsed)
    {
        CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(USB0_IRQn));
        return S_FALSE;
    }

    g_K60_USB_Driver.pUsbControllerState = &State;
    g_K60_USB_Driver.PinsProtected = TRUE;

    State.EndpointStatus = &g_K60_USB_Driver.EndpointStatus[0];
    State.EndpointCount = c_Used_Endpoints;
    //State->DeviceStatus   = USB_STATUS_DEVICE_SELF_POWERED;
    State.PacketSize = c_default_ctrl_packet_size;

    State.FirstGetDescriptor = TRUE;

    ProtectPins(Controller, FALSE);

    return S_OK;
}

HRESULT K60_USB_Driver::Uninitialize(int Controller)
{
    ASSERT( 0 == Controller );

    GLOBAL_LOCK( irq);

    ProtectPins(Controller, TRUE);

    g_K60_USB_Driver.pUsbControllerState = NULL;

    return S_OK;
}

void K60_USB_Driver::StartHardware()
{
    // MPU is disabled
    MPU->CESR = 0x00;

    // Select PLL output & PLL/FLL selected as CLK source
    SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
    SIM->SOPT2 |= SIM_SOPT2_USBSRC_MASK;

    // USB Freq Divider
    SIM->CLKDIV2 |= c_USB_FRACTIONAL_VALUE;

    // USB Clock Gating
    SIM->SCGC4 |= SIM_SCGC4_USBOTG_MASK;

    // make sure usb is disabled
    USB0->CTL = 0x00;

    // make sure pullup is disabled
    USB0->CONTROL &= ~USB_CONTROL_DPPULLUPNONOTG_MASK;

    // disable weak pull downs
    USB0->USBCTRL = 0x00;

    // Reset USB Module
    USB0->USBTRC0 |= USB_USBTRC0_USBRESET_MASK;
    while (USB0->USBTRC0 & USB_USBTRC0_USBRESET_MASK)
    {
    };

    // Clear USB Reset flag
    USB0->ISTAT |= USB_ISTAT_USBRST_MASK;

    // Set BDT Base Register
    USB0->BDTPAGE1 = (UINT8) ((UINT32) tBDTtable >> 8);
    USB0->BDTPAGE2 = (UINT8) ((UINT32) tBDTtable >> 16);
    USB0->BDTPAGE3 = (UINT8) ((UINT32) tBDTtable >> 24);

    // clear enabled interrupts
    USB0->INTEN = 0x00;

    // enable USB reset interrupt
    USB0->INTEN |= USB_INTEN_USBRSTEN_MASK;

    // disable suspend
    USB0->USBCTRL = 0x0;

    // datasheet says this bit must be set ...
    USB0->USBTRC0 |= 0x40;

    // enable pull up
    USB0->CONTROL |= USB_CONTROL_DPPULLUPNONOTG_MASK;

    // enable the usb interrupt
    CPU_INTC_ActivateInterrupt(NVIC_TO_INTC(USB0_IRQn), Global_ISR, NULL);

    // enable the USB module
    USB0->CTL = USB_CTL_USBENSOFEN_MASK;
}

void K60_USB_Driver::StopHardware()
{
    // disable usb
    USB0->CTL &= ~USB_CTL_USBENSOFEN_MASK;

    // deativate interupt and vector
    CPU_INTC_DeactivateInterrupt(NVIC_TO_INTC(USB0_IRQn));

    // disable pullup
    USB0->CONTROL &= ~USB_CONTROL_DPPULLUPNONOTG_MASK;

    // unset the bit that the datasheet says this bit must be set ...
    USB0->USBTRC0 &= ~0x40;

    // disable usb interrupts
    USB0->INTEN = 0x00;

    // Deselect PLL output & PLL/FLL selected as CLK source
    SIM->SOPT2 &= ~(SIM_SOPT2_PLLFLLSEL_MASK | SIM_SOPT2_USBSRC_MASK);

    // disable USB Freq Divider
    SIM->CLKDIV2 &= ~c_USB_FRACTIONAL_VALUE;

    // disable USB Clock Gating
    SIM->SCGC4 &= ~SIM_SCGC4_USBOTG_MASK;

    // give it a bit
    HAL_Time_Sleep_MicroSeconds_InterruptEnabled(500);
}

BOOL K60_USB_Driver::StartOutput(USB_CONTROLLER_STATE* State, int endpoint)
{
    ASSERT( State );
    ASSERT(endpoint < c_Used_Endpoints);

    GLOBAL_LOCK( irq);

    // If endpoint is not an output
    if (State->Queues[endpoint] == NULL || !State->IsTxQueue[endpoint])
        return FALSE;

    // if the halt feature for this endpoint is set, then just
    //   clear all the characters
    if (State->EndpointStatus[endpoint] & USB_STATUS_ENDPOINT_HALT)
    {
        ClearTxQueue(State, endpoint);
        return TRUE;
    }

    // If TxRunning, interrupts will drain the queue
    if (!g_K60_USB_Driver.TxRunning[endpoint])
    {
        g_K60_USB_Driver.TxRunning[endpoint] = TRUE;

        // Calling both TxPacket & EP_TxISR in this routine could cause a TX FIFO overflow
        TxPacket(State, endpoint);
    }
    else if (irq.WasDisabled())
    {
        if (USB0->ISTAT)
        {
            Global_ISR(0);
        }
    }

    return TRUE;
}

BOOL K60_USB_Driver::GetInterruptState()
{
    GLOBAL_LOCK( irq);

    return (0 != USB0->ISTAT);
}

//--//

void K60_USB_Driver::ClearTxQueue(USB_CONTROLLER_STATE* State, int endpoint)
{
    ASSERT(State);

    State->Queues[endpoint]->Initialize();
}

void K60_USB_Driver::TxPacket(USB_CONTROLLER_STATE* State, int endpoint)
{
    ASSERT( endpoint < c_Used_Endpoints );
    ASSERT( State );

    GLOBAL_LOCK( irq);

    // transmit a packet on UsbPortNum, if there are no more packets to transmit, then die
    USB_PACKET64* Packet64;

    // If this is not a legal transmit endpoint, there is nothing to do
    if (State->Queues[endpoint] == NULL || !State->IsTxQueue[endpoint])
        return;

    for (;;)
    {
        Packet64 = USB_TxDequeue(State, endpoint, TRUE);

        if (Packet64 == NULL || Packet64->Size > 0)
            break;
    }

    if (Packet64)
    {
        EndpointInTransfer(endpoint, Packet64->Buffer, Packet64->Size);

        g_K60_USB_Driver.TxNeedZLPS[endpoint] = (Packet64->Size == State->MaxPacketSize[endpoint]);
    }
    else
    {
        // send the zero length packet since we landed on the FIFO boundary before
        // (and we queued a zero length packet to transmit)
        if (g_K60_USB_Driver.TxNeedZLPS[endpoint])
        {
            EndpointInTransfer(endpoint, 0, 0);
            g_K60_USB_Driver.TxNeedZLPS[endpoint] = FALSE;
        }

        // no more data
        g_K60_USB_Driver.TxRunning[endpoint] = FALSE;
    }
}

void K60_USB_Driver::ControlNext()
{
    ASSERT(g_K60_USB_Driver.pUsbControllerState);

    USB_CONTROLLER_STATE *State = g_K60_USB_Driver.pUsbControllerState;

    if (State->DataCallback)
    {
        State->DataCallback(State);

        if (State->DataSize == 0)
        {
            EndpointInTransfer(0, 0, 0);

            State->DataCallback = NULL; // Stop sending stuff if we're done
        }
        else
        {
            EndpointInTransfer(0, State->Data, State->DataSize);

            // special handling the USB driver set address test, cannot use the first descriptor as the ADDRESS state is handle in the hardware
            if (g_K60_USB_Driver.FirstDescriptorPacket)
            {
                State->DataCallback = NULL;
            }
        }
    }
}

void K60_USB_Driver::EndpointInTransfer(UINT8 ep, UINT8 *data, UINT8 size)
{
    UINT8 *bdtBuffer;

    // wait till ready
    while (tBDTtable[EPIN_BDT_INDEX(ep)].Stat.RecPid.UOWN)
        ;

    // get the bdt buffer
    bdtBuffer = (UINT8*) tBDTtable[EPIN_BDT_INDEX(ep)].Addr;

    // setup size
    tBDTtable[EPIN_BDT_INDEX(ep)].Cnt = size;

    // copy data from user buffer to bdt buffer
    while (size--)
    {
        *bdtBuffer++ = *data++;
    }

    // toggle data flag ?
    if (g_K60_USB_Driver.ExpectedToggle[ep])
    {
        tBDTtable[EPIN_BDT_INDEX(ep)].Stat._byte = c_UDATA0;
        g_K60_USB_Driver.ExpectedToggle[ep] = FALSE;
    }
    else
    {
        tBDTtable[EPIN_BDT_INDEX(ep)].Stat._byte = c_UDATA1;
        g_K60_USB_Driver.ExpectedToggle[ep] = TRUE;
    }
}

/**********************************************************/

UINT8 K60_USB_Driver::EndpointOutTransfer(UINT8 ep, UINT8 *data, BOOL DisableRx)
{
    UINT8 *bdtBuffer;

    // wait till empty
    while (tBDTtable[EPOUT_BDT_INDEX(ep)].Stat.RecPid.UOWN)
        ;

    // get bdt buffer
    bdtBuffer = (UINT8*) tBDTtable[EPOUT_BDT_INDEX(ep)].Addr;

    // get packet size
    UINT8 size = tBDTtable[EPOUT_BDT_INDEX(ep)].Cnt;

    // copy size to countdown
    UINT8 countDown = size;

    // copy data from user buffer to bdt buffer
    while (countDown--)
    {
        *data++ = *bdtBuffer++;
    }

    // reset size for next packet
    tBDTtable[EPOUT_BDT_INDEX(ep)].Cnt = EndpointInit[ep].bits.MPS;

    // toggle data flag
    if (!DisableRx)
    {
        if (g_K60_USB_Driver.ExpectedToggle[ep])
        {
            tBDTtable[EPOUT_BDT_INDEX(ep)].Stat._byte = c_UDATA0;
            g_K60_USB_Driver.ExpectedToggle[ep] = FALSE;
        }
        else
        {
            tBDTtable[EPOUT_BDT_INDEX(ep)].Stat._byte = c_UDATA1;
            g_K60_USB_Driver.ExpectedToggle[ep] = TRUE;
        }
    }

    // return size of packet read
    return size;
}

void K60_USB_Driver::SetupEndpoints(void)
{
    // setup end points
    for (int ep = 1; ep < c_Used_Endpoints; ep++)
    {
        if (ep < g_K60_USB_Driver.c_Used_Endpoints && EndpointInit[ep].bits.EE) // If this endpoint is enabled
        {
            if (EndpointInit[ep].bits.ED) // If transmit endpoint
            {
                // tx (in) endpoint
                USB0->ENDPOINT[ep].ENDPT = USB_ENDPT_EPTXEN_MASK | USB_ENDPT_EPHSHK_MASK;

                tBDTtable[EPIN_BDT_INDEX(ep)].Stat._byte = c_MCU;
                tBDTtable[EPIN_BDT_INDEX(ep)].Cnt = EndpointInit[ep].bits.MPS;
                tBDTtable[EPIN_BDT_INDEX(ep)].Addr = (UINT32) &(g_K60_USB_Driver.Buffers[EPIN_BDT_INDEX(ep)][0]);

                g_K60_USB_Driver.ExpectedToggle[ep] = FALSE;
            }
            else
            {
                // rx (out) endpoint
                USB0->ENDPOINT[ep].ENDPT = USB_ENDPT_EPRXEN_MASK | USB_ENDPT_EPHSHK_MASK;

                tBDTtable[EPOUT_BDT_INDEX(ep)].Stat._byte = c_SIE;
                tBDTtable[EPOUT_BDT_INDEX(ep)].Cnt = EndpointInit[ep].bits.MPS;
                tBDTtable[EPOUT_BDT_INDEX(ep)].Addr = (UINT32) &(g_K60_USB_Driver.Buffers[EPOUT_BDT_INDEX(ep)][0]);
            }
        }
        else
        {
            // niether tx or rx
            USB0->ENDPOINT[ep].ENDPT = USB_ENDPT_EPHSHK_MASK;
        }
    }
}

void K60_USB_Driver::Global_ISR(void* Param)
{
    UINT8 u8EndPoint;
    UINT8 u8IN;

    // reset USB interrupt
    if (USB0->ISTAT & USB_ISTAT_USBRST_MASK)
    {
        ResetEvent();
        return;
    }

    // stall interrupt
    if (USB0->ISTAT & USB_ISTAT_STALL_MASK)
    {
        // automatically un-stall control endpoint
        if (USB0->ENDPOINT[0].ENDPT & USB_ENDPT_EPSTALL_MASK)
            USB0->ENDPOINT[0].ENDPT &= ~USB_ENDPT_EPSTALL_MASK;
    }

    // token received interrupt
    if (USB0->ISTAT & USB_ISTAT_TOKDNE_MASK)
    {
        // clr requires irq to be disabled, otherwise it asserts
        GLOBAL_LOCK(irq);

        // stops the buffer ping/pong
        USB0->CTL |= USB_CTL_ODDRST_MASK;

        // get target endpoint
        u8EndPoint = USB0->STAT >> 4;

        // control or data endpoint ?
        if (u8EndPoint)
        {
            if (!(USB0->STAT & 0x08))
            {
                // data to read
                EP_RxISR(u8EndPoint);
            }
            else
            {
                // data to send
                EP_TxISR(u8EndPoint);
            }
        }
        else
        {
            EP0_ISR();
        }

        USB0->ISTAT |= USB_ISTAT_TOKDNE_MASK;
    }

    // sleep mode interrupt
    if (USB0->ISTAT & USB_ISTAT_SLEEP_MASK)
    {
        USB0->ISTAT |= USB_ISTAT_SLEEP_MASK;
    }

    // error interrupt
    if (USB0->ISTAT & USB_ISTAT_ERROR_MASK)
    {
        USB0->ISTAT |= USB_ISTAT_ERROR_MASK;
    }
}

void K60_USB_Driver::EP0_ISR()
{
    USB_CONTROLLER_STATE *State = g_K60_USB_Driver.pUsbControllerState;

    // set up packet receive
    if (!(USB0->STAT & 0x08))
    {
        UINT8* packetBuffer = (UINT8*) tBDTtable[EPOUT_BDT_INDEX(0)].Addr;
        UINT8 len = tBDTtable[EPOUT_BDT_INDEX(0)].Cnt;

        g_K60_USB_Driver.ExpectedToggle[0] = FALSE;

        // special handling for the very first SETUP command - Getdescriptor[DeviceType], the host looks for 8 bytes data only
        USB_SETUP_PACKET* Setup = (USB_SETUP_PACKET*) packetBuffer;
        if ((Setup->bRequest == USB_GET_DESCRIPTOR) && (((Setup->wValue & 0xFF00) >> 8) == USB_DEVICE_DESCRIPTOR_TYPE)
                && (Setup->wLength != 0x12))
            g_K60_USB_Driver.FirstDescriptorPacket = TRUE;
        else
            g_K60_USB_Driver.FirstDescriptorPacket = FALSE;

        // send it to the upper layer
        State->Data = packetBuffer;
        State->DataSize = len;

        UINT8 result = USB_ControlCallback(State);

        switch (result)
        {
        case USB_STATE_DATA:
            // setup packet was handled and the upper layer has data to send
            break;

        case USB_STATE_ADDRESS:
            // upper layer needs us to change the address
            // address stage handles in hardware
            break;

        case USB_STATE_DONE:
            State->DataCallback = NULL;
            break;

        case USB_STATE_STALL:
            // since the setup command all handled in the hardware, should not have this state
            //
            // setup packet failed to process successfully
            // set stall condition on the default control
            // endpoint
            //
            break;

        case USB_STATE_STATUS:
            // handle by hardware
            break;
        case USB_STATE_CONFIGURATION:
            SetupEndpoints();

            // handle partly by hardware and the GLOBAL_ISR will take care.
            // USB spec 9.4.5 SET_CONFIGURATION resets halt conditions, resets toggle bits
            break;

        case USB_STATE_REMOTE_WAKEUP:
            // It is not using currently as the device side won't go into SUSPEND mode unless
            // the PC is purposely to select it to SUSPEND, as there is always SOF in the bus
            // to keeping the device from SUSPEND.
            break;

        default:
            ASSERT(0)
            ;
            break;
            // the status change is only seen and taken care in hardware
        }

        if (result != USB_STATE_STALL)
        {
            ControlNext();

            // If the port is configured, then output any possible withheld data
            if (result == USB_STATE_CONFIGURATION)
            {
                for (int ep = 1; ep < c_Used_Endpoints; ep++)
                {
                    if (State->Queues[ep] && State->IsTxQueue[ep])
                        StartOutput(State, ep);
                }
            }
        }

        tBDTtable[EPOUT_BDT_INDEX(0)].Stat._byte = c_UDATA0;

        USB0->CTL &= ~USB_CTL_TXSUSPENDTOKENBUSY_MASK;
    }
    else
    {
        if (!USB0->ADDR && State->Address)
        {
            USB0->ADDR = State->Address;
        }

        ControlNext();
    }
}

void K60_USB_Driver::EP_TxISR(int endpoint)
{
    ASSERT_IRQ_MUST_BE_OFF();

    // successfully transmitted packet, time to send the next one
    TxPacket(g_K60_USB_Driver.pUsbControllerState, endpoint);
}

void K60_USB_Driver::EP_RxISR(int endpoint)
{
    UINT32 EP_INTR;

    BOOL DisableRx;
    USB_PACKET64* Packet64 = USB_RxEnqueue(g_K60_USB_Driver.pUsbControllerState, endpoint, DisableRx);

    // copy packet in, making sure that Packet64->Buffer is never overflowed
    if (Packet64)
    {
        UINT8 len = EndpointOutTransfer(endpoint, Packet64->Buffer, DisableRx);
        Packet64->Size = len;

        g_K60_USB_Driver.EndpointDisabled[endpoint] = DisableRx;
    }
    else
    {
        ASSERT(0);
    }
}

void K60_USB_Driver::ResetEvent()
{
    USB_CONTROLLER_STATE *State = g_K60_USB_Driver.pUsbControllerState;

    // The hardware handles most of the reset procedure.
    ASSERT( State );

    g_K60_USB_Driver.ExpectedToggle[0] = FALSE;

    // Disable all data EP registers
    USB0->ENDPOINT[1].ENDPT = 0x00;
    USB0->ENDPOINT[2].ENDPT = 0x00;
    USB0->ENDPOINT[3].ENDPT = 0x00;
    USB0->ENDPOINT[4].ENDPT = 0x00;
    USB0->ENDPOINT[5].ENDPT = 0x00;
    USB0->ENDPOINT[6].ENDPT = 0x00;

    // EP0 OUT BDT Settings ---------------------
    tBDTtable[EPOUT_BDT_INDEX(0)].Cnt = K60_USB_Driver::c_default_ctrl_packet_size;
    tBDTtable[EPOUT_BDT_INDEX(0)].Addr = (UINT32) &(g_K60_USB_Driver.Buffers[EPOUT_BDT_INDEX(0)][0]);
    tBDTtable[EPOUT_BDT_INDEX(0)].Stat._byte = c_UDATA1;

    // EP0 IN BDT Settings ---------------------
    tBDTtable[EPIN_BDT_INDEX(0)].Cnt = K60_USB_Driver::c_default_ctrl_packet_size;
    tBDTtable[EPIN_BDT_INDEX(0)].Addr = (UINT32) &(g_K60_USB_Driver.Buffers[EPIN_BDT_INDEX(0)][0]);
    tBDTtable[EPIN_BDT_INDEX(0)].Stat._byte = c_MCU;

    // setup other endpoints on hardware
    //SetupEndpoints();

    // Enable EP0
    USB0->ENDPOINT[0].ENDPT = 0x0D;

    // Clear all Error flags
    USB0->ERRSTAT = 0xFF;

    // CLear all USB ISR flags
    USB0->ISTAT = 0xFF;

    // Set default Address
    USB0->ADDR = 0x00;

    // Enable all error sources
    USB0->ERREN = 0xFF;

    // enable interrupts
    USB0->INTEN |= USB_INTEN_TOKDNEEN_MASK;
    USB0->INTEN |= USB_INTEN_ERROREN_MASK;
    USB0->INTEN |= USB_INTEN_USBRSTEN_MASK;
    USB0->INTEN |= USB_INTEN_SLEEPEN_MASK;
    USB0->INTEN |= USB_INTEN_STALLEN_MASK;

    // clear all flags
    USB_ClearEvent(0, USB_EVENT_ALL);

    // reset endpoint state
    for (int ep = 0; ep < c_Used_Endpoints; ep++)
    {
        g_K60_USB_Driver.TxRunning[ep] = FALSE;
        g_K60_USB_Driver.TxNeedZLPS[ep] = FALSE;
    }

    State->DeviceState = USB_DEVICE_STATE_DEFAULT;
    State->Address = 0;

    USB_StateCallback(State);
}

//--//

BOOL K60_USB_Driver::RxEnable(USB_CONTROLLER_STATE *State, int endpoint)
{
    if (NULL == State || endpoint >= c_Used_Endpoints)
        return FALSE;

    GLOBAL_LOCK( irq);

    if (!EndpointInit[endpoint].bits.ED && g_K60_USB_Driver.EndpointDisabled[endpoint]) // If receive endpoint
    {
        g_K60_USB_Driver.EndpointDisabled[endpoint] = FALSE;

        if (g_K60_USB_Driver.ExpectedToggle[endpoint])
        {
            tBDTtable[EPOUT_BDT_INDEX(endpoint)].Stat._byte = c_UDATA0;
            g_K60_USB_Driver.ExpectedToggle[endpoint] = FALSE;
        }
        else
        {
            tBDTtable[EPOUT_BDT_INDEX(endpoint)].Stat._byte = c_UDATA1;
            g_K60_USB_Driver.ExpectedToggle[endpoint] = TRUE;
        }
    }

    return TRUE;
}

BOOL K60_USB_Driver::ProtectPins(int Controller, BOOL On)
{
    ASSERT( 0 == Controller );
    USB_CONTROLLER_STATE *State = g_K60_USB_Driver.pUsbControllerState;

    GLOBAL_LOCK( irq);

    // initialized yet?
    if (State)
    {
        if (On)
        {
            if (!g_K60_USB_Driver.PinsProtected)
            {
                // Disable the USB com, state change from Not protected to Protected

                g_K60_USB_Driver.PinsProtected = TRUE;

                // clear USB Txbuffer
                for (int ep = 0; ep < c_Used_Endpoints; ep++)
                {
                    if (State->IsTxQueue[ep])
                        State->Queues[ep]->Initialize();
                }

                State->DeviceState = USB_DEVICE_STATE_DETACHED;
                USB_StateCallback(State);

                StopHardware();
            }
        }
        else
        {
            if (g_K60_USB_Driver.PinsProtected)
            {
                // Ready for USB to enable, state change from Protected to Not protected
                g_K60_USB_Driver.PinsProtected = FALSE;

                // enable the clock,
                // set USB to attached/powered
                // set the device to a known state- Attached before it is set to the powered state (USB specf 9.1.1)
                State->DeviceState = USB_DEVICE_STATE_ATTACHED;

                USB_StateCallback(State);

                StartHardware();
            }
        }

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
