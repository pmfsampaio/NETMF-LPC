////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Implementation for LPC178X: Copyright (c) Oberon microsystems, Inc.
//
//  CPU classes in Microsoft.SPOT.Hardware.LPC178X namespace
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections;
using System.Threading;
using System.Runtime.CompilerServices;
using Microsoft.SPOT.Hardware;
using System.IO.Ports;

namespace Microsoft.SPOT.Hardware.LPC178X
{

    /// <summary>
    /// Specifies identifiers for hardware I/O pins.
    /// </summary>
    public static class Pins
    {
        /// <summary>
        /// GPIO port 0 bit 0
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_00 = (Cpu.Pin)0;
        /// <summary>
        /// GPIO port 0 bit 1
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_01 = (Cpu.Pin)1;
        /// <summary>
        /// GPIO port 0 bit 2
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_02 = (Cpu.Pin)2;
        /// <summary>
        /// GPIO port 0 bit 3
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_03 = (Cpu.Pin)3;
        /// <summary>
        /// GPIO port 0 bit 4
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_04 = (Cpu.Pin)4;
        /// <summary>
        /// GPIO port 0 bit 5
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_05  = (Cpu.Pin)5;
        /// <summary>
        /// GPIO port 0 bit 6
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_06 = (Cpu.Pin)6;
        /// <summary>
        /// GPIO port 0 bit 7
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_07 = (Cpu.Pin)7;
        /// <summary>
        /// GPIO port 0 bit 8
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_08 = (Cpu.Pin)8;
        /// <summary>
        /// GPIO port 0 bit 9
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_09  = (Cpu.Pin)9;
        /// <summary>
        /// GPIO port 0 bit 10
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_10 = (Cpu.Pin)10;
        /// <summary>
        /// GPIO port 0 bit 11
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_11 = (Cpu.Pin)11;
        /// <summary>
        /// GPIO port 0 bit 12
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_12 = (Cpu.Pin)12;
        /// <summary>
        /// GPIO port 0 bit 13
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_13 = (Cpu.Pin)13;
        /// <summary>
        /// GPIO port 0 bit 14
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_14 = (Cpu.Pin)14;
        /// <summary>
        /// GPIO port 0 bit 15
        /// </summary>
        public const Cpu.Pin GPIO_PORT_0_15  = (Cpu.Pin)15;
        /// <summary>
        /// GPIO port 1 bit 0
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_00 = (Cpu.Pin)16;
        /// <summary>
        /// GPIO port 1 bit 1
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_01 = (Cpu.Pin)17;
        /// <summary>
        /// GPIO port 1 bit 2
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_02 = (Cpu.Pin)18;
        /// <summary>
        /// GPIO port 1 bit 3
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_03 = (Cpu.Pin)19;
        /// <summary>
        /// GPIO port 1 bit 4
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_04 = (Cpu.Pin)20;
        /// <summary>
        /// GPIO port 1 bit 5
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_05 = (Cpu.Pin)21;
        /// <summary>
        /// GPIO port 1 bit 6
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_06 = (Cpu.Pin)22;
        /// <summary>
        /// GPIO port 1 bit 7
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_07 = (Cpu.Pin)23;
        /// <summary>
        /// GPIO port 1 bit 8
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_08 = (Cpu.Pin)24;
        /// <summary>
        /// GPIO port 1 bit 9
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_09 = (Cpu.Pin)25;
        /// <summary>
        /// GPIO port 1 bit 10
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_10 = (Cpu.Pin)26;
        /// <summary>
        /// GPIO port 1 bit 11
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_11 = (Cpu.Pin)27;
        /// <summary>
        /// GPIO port 1 bit 12
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_12 = (Cpu.Pin)28;
        /// <summary>
        /// GPIO port 1 bit 13
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_13 = (Cpu.Pin)29;
        /// <summary>
        /// GPIO port 1 bit 14
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_14 = (Cpu.Pin)30;
        /// <summary>
        /// GPIO port 1 bit 15
        /// </summary>
        public const Cpu.Pin GPIO_PORT_1_15 = (Cpu.Pin)31;
        /// <summary>
        /// GPIO port 2 bit 0
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_00 = (Cpu.Pin)32;
        /// <summary>
        /// GPIO port 2 bit 1
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_01 = (Cpu.Pin)33;
        /// <summary>
        /// GPIO port 2 bit 2
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_02 = (Cpu.Pin)34;
        /// <summary>
        /// GPIO port 2 bit 3
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_03 = (Cpu.Pin)35;
        /// <summary>
        /// GPIO port 2 bit 4
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_04 = (Cpu.Pin)36;
        /// <summary>
        /// GPIO port 2 bit 5
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_05 = (Cpu.Pin)37;
        /// <summary>
        /// GPIO port 2 bit 6
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_06 = (Cpu.Pin)38;
        /// <summary>
        /// GPIO port 2 bit 7
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_07 = (Cpu.Pin)39;
        /// <summary>
        /// GPIO port 2 bit 8
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_08 = (Cpu.Pin)40;
        /// <summary>
        /// GPIO port 2 bit 9
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_09 = (Cpu.Pin)41;
        /// <summary>
        /// GPIO port 2 bit 10
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_10 = (Cpu.Pin)42;
        /// <summary>
        /// GPIO port 2 bit 11
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_11 = (Cpu.Pin)43;
        /// <summary>
        /// GPIO port 2 bit 12
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_12 = (Cpu.Pin)44;
        /// <summary>
        /// GPIO port 2 bit 13
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_13 = (Cpu.Pin)45;
        /// <summary>
        /// GPIO port 2 bit 14
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_14 = (Cpu.Pin)46;
        /// <summary>
        /// GPIO port 2 bit 15
        /// </summary>
        public const Cpu.Pin GPIO_PORT_2_15 = (Cpu.Pin)47;
        /// <summary>
        /// GPIO port 3 bit 0
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_00 = (Cpu.Pin)48;
        /// <summary>
        /// GPIO port 3 bit 1
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_01 = (Cpu.Pin)49;
        /// <summary>
        /// GPIO port 3 bit 2
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_02 = (Cpu.Pin)50;
        /// <summary>
        /// GPIO port 3 bit 3
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_03 = (Cpu.Pin)51;
        /// <summary>
        /// GPIO port 3 bit 4
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_04 = (Cpu.Pin)52;
        /// <summary>
        /// GPIO port 3 bit 5
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_05 = (Cpu.Pin)53;
        /// <summary>
        /// GPIO port 3 bit 6
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_06 = (Cpu.Pin)54;
        /// <summary>
        /// GPIO port 3 bit 7
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_07 = (Cpu.Pin)55;
        /// <summary>
        /// GPIO port 3 bit 8
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_08 = (Cpu.Pin)56;
        /// <summary>
        /// GPIO port 3 bit 9
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_09 = (Cpu.Pin)57;
        /// <summary>
        /// GPIO port 3 bit 10
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_10 = (Cpu.Pin)58;
        /// <summary>
        /// GPIO port 3 bit 11
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_11 = (Cpu.Pin)59;
        /// <summary>
        /// GPIO port 3 bit 12
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_12 = (Cpu.Pin)60;
        /// <summary>
        /// GPIO port 3 bit 13
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_13 = (Cpu.Pin)61;
        /// <summary>
        /// GPIO port 3 bit 14
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_14 = (Cpu.Pin)62;
        /// <summary>
        /// GPIO port 3 bit 15
        /// </summary>
        public const Cpu.Pin GPIO_PORT_3_15 = (Cpu.Pin)63;
        /// <summary>
        /// GPIO port 4 bit 0
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_00 = (Cpu.Pin)64;
        /// <summary>
        /// GPIO port 4 bit 1
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_01 = (Cpu.Pin)65;
        /// <summary>
        /// GPIO port 4 bit 2
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_02 = (Cpu.Pin)66;
        /// <summary>
        /// GPIO port 4 bit 3
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_03 = (Cpu.Pin)67;
        /// <summary>
        /// GPIO port 4 bit 4
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_04 = (Cpu.Pin)68;
        /// <summary>
        /// GPIO port 4 bit 5
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_05 = (Cpu.Pin)69;
        /// <summary>
        /// GPIO port 4 bit 6
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_06 = (Cpu.Pin)70;
        /// <summary>
        /// GPIO port 4 bit 7
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_07 = (Cpu.Pin)71;
        /// <summary>
        /// GPIO port 4 bit 8
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_08 = (Cpu.Pin)72;
        /// <summary>
        /// GPIO port 4 bit 9
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_09 = (Cpu.Pin)73;
        /// <summary>
        /// GPIO port 4 bit 10
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_10 = (Cpu.Pin)74;
        /// <summary>
        /// GPIO port 4 bit 11
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_11 = (Cpu.Pin)75;
        /// <summary>
        /// GPIO port 4 bit 12
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_12 = (Cpu.Pin)76;
        /// <summary>
        /// GPIO port 4 bit 13
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_13 = (Cpu.Pin)77;
        /// <summary>
        /// GPIO port 4 bit 14
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_14 = (Cpu.Pin)78;
        /// <summary>
        /// GPIO port 4 bit 15
        /// </summary>
        public const Cpu.Pin GPIO_PORT_4_15 = (Cpu.Pin)79;
        
        public const Cpu.Pin GPIO_NONE = Cpu.Pin.GPIO_NONE;
    }

    public static class SerialPorts
    {
        public const string COM1 = "COM1";
        public const string COM2 = "COM2";
        public const string COM3 = "COM3";
    }
    
    public static class BaudRates
    {
        public const BaudRate Baud9600   = BaudRate.Baudrate9600;
        public const BaudRate Baud19200  = BaudRate.Baudrate19200;
        public const BaudRate Baud38400  = BaudRate.Baudrate38400;
        public const BaudRate Baud57600  = BaudRate.Baudrate57600;
        public const BaudRate Baud115200 = BaudRate.Baudrate115200;
        public const BaudRate Baud230400 = BaudRate.Baudrate230400;
    }

    public static class ResistorModes
    {
        public const Port.ResistorMode PullUp   = Port.ResistorMode.PullUp;
        public const Port.ResistorMode PullDown = Port.ResistorMode.PullDown;
        public const Port.ResistorMode Disabled = Port.ResistorMode.Disabled;
    }

    public static class InterruptModes
    {
        public const Port.InterruptMode InterruptEdgeLow       = Port.InterruptMode.InterruptEdgeLow;
        public const Port.InterruptMode InterruptEdgeHigh      = Port.InterruptMode.InterruptEdgeHigh;
        public const Port.InterruptMode InterruptEdgeBoth      = Port.InterruptMode.InterruptEdgeBoth;
        public const Port.InterruptMode InterruptEdgeLevelHigh = Port.InterruptMode.InterruptEdgeLevelHigh;
        public const Port.InterruptMode InterruptEdgeLevelLow  = Port.InterruptMode.InterruptEdgeLevelLow;
        public const Port.InterruptMode InterruptNone          = Port.InterruptMode.InterruptNone;
    }

    public static class SPI_Devices
    {
        public const Microsoft.SPOT.Hardware.SPI.SPI_module SPI1 = Microsoft.SPOT.Hardware.SPI.SPI_module.SPI1;
        public const Microsoft.SPOT.Hardware.SPI.SPI_module SPI2 = Microsoft.SPOT.Hardware.SPI.SPI_module.SPI2;
        public const Microsoft.SPOT.Hardware.SPI.SPI_module SPI3 = Microsoft.SPOT.Hardware.SPI.SPI_module.SPI3;
    }
    
}
