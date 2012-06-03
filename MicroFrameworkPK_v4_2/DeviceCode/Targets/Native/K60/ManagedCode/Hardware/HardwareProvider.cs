////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using System;
using System.Threading;
using System.Runtime.CompilerServices;
using Microsoft.SPOT.Hardware;

namespace Microsoft.SPOT.Hardware.K60
{
    internal class K60HardwareProvider : HardwareProvider
    {
        static K60HardwareProvider()
        {
            Microsoft.SPOT.Hardware.HardwareProvider.Register(new K60HardwareProvider());
        }


        override public void GetSerialPins(string comPort, out Cpu.Pin rxPin, out Cpu.Pin txPin, out Cpu.Pin ctsPin, out Cpu.Pin rtsPin)
        {
            switch (comPort)
            {
                case "COM1":
                    rxPin  = Pins.GPIO_PIN_B16;
                    txPin  = Pins.GPIO_PIN_B17;
                    ctsPin = Pins.GPIO_NONE;
                    rtsPin = Pins.GPIO_NONE;
                    break;
                case "COM2":
                    rxPin  = Pins.GPIO_PIN_C3;
                    txPin  = Pins.GPIO_PIN_C4;
                    ctsPin = Pins.GPIO_NONE;
                    rtsPin = Pins.GPIO_NONE;
                    break;
                case "COM3":
                    rxPin  = Pins.GPIO_PIN_D2;
                    txPin  = Pins.GPIO_PIN_D3;
                    ctsPin = Pins.GPIO_NONE;
                    rtsPin = Pins.GPIO_NONE;
                    break;
                case "COM4":
                    rxPin  = Pins.GPIO_PIN_C16;
                    txPin  = Pins.GPIO_PIN_C17;
                    ctsPin = Pins.GPIO_NONE;
                    rtsPin = Pins.GPIO_NONE;
                    break;
                default:
                    throw new NotSupportedException();                    
            }
        }

        override public void GetI2CPins( out Cpu.Pin scl, out Cpu.Pin sda )
        {
	        scl = Pins.GPIO_PIN_D8;
            sda = Pins.GPIO_PIN_D9;
        }

        override public void GetSpiPins( SPI.SPI_module spi_mod, out Cpu.Pin msk, out Cpu.Pin miso, out Cpu.Pin mosi )
        {
            switch (spi_mod)
            {
          	    case SPI.SPI_module.SPI1:
                    msk  = Pins.GPIO_PIN_A15;
                    miso = Pins.GPIO_PIN_A14;
                    mosi = Pins.GPIO_PIN_A16;
                    break;
                case SPI.SPI_module.SPI2:
                    msk = Pins.GPIO_PIN_E2;
                    miso = Pins.GPIO_PIN_E3;
                    mosi = Pins.GPIO_PIN_E1;
                    break;
                case SPI.SPI_module.SPI3:
                    msk = Pins.GPIO_PIN_D12;
                    miso = Pins.GPIO_PIN_D14;
                    mosi = Pins.GPIO_PIN_D13;
                    break;   
                default:
                    throw new NotSupportedException();                    
            }
        }        
    }
}
