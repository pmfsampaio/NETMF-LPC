////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections;
using System.Threading;
using System.Runtime.CompilerServices;
using Microsoft.SPOT.Hardware;
using System.IO.Ports;

namespace Microsoft.SPOT.Hardware.K60
{

    /// <summary>
    /// Specifies identifiers for hardware I/O pins.
    /// </summary>
    public static class Pins
    {
        /// <summary>
        /// GPIO PIN 0 pin 0.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A0  = (Cpu.Pin)0;
        /// <summary>
        /// GPIO PIN 0 pin 1.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A1  = (Cpu.Pin)1;
        /// <summary>
        /// GPIO PIN 0 pin 2.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A2  = (Cpu.Pin)2;
        /// <summary>
        /// GPIO PIN 0 pin 3.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A3  = (Cpu.Pin)3;
        /// <summary>
        /// GPIO PIN 0 pin 4.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A4  = (Cpu.Pin)4;
        /// <summary>
        /// GPIO PIN 0 pin 5.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A5 = (Cpu.Pin)5;
        /// <summary>
        /// GPIO PIN 0 pin 6.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A6 = (Cpu.Pin)6;
        /// <summary>
        /// GPIO PIN 0 pin 7.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A7 = (Cpu.Pin)7;
        /// <summary>
        /// GPIO PIN 0 pin 8.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A8 = (Cpu.Pin)8;
        /// <summary>
        /// GPIO PIN 0 pin 9.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A9 = (Cpu.Pin)9;
        /// <summary>
        /// GPIO PIN 0 pin 10.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A10 = (Cpu.Pin)10;
        /// <summary>
        /// GPIO PIN 0 pin 11.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A11 = (Cpu.Pin)11;
        /// <summary>
        /// GPIO PIN 0 pin 12.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A12 = (Cpu.Pin)12;
        /// <summary>
        /// GPIO PIN 0 pin 13.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A13 = (Cpu.Pin)13;
        /// <summary>
        /// GPIO PIN 0 pin 14.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A14 = (Cpu.Pin)14;
        /// <summary>
        /// GPIO PIN 0 pin 15.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A15 = (Cpu.Pin)15;
        /// <summary>
        /// GPIO PIN 0 pin 16.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A16 = (Cpu.Pin)16;
        /// <summary>
        /// GPIO PIN 0 pin 17.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A17 = (Cpu.Pin)17;
        /// <summary>
        /// GPIO PIN 0 pin 18.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A18 = (Cpu.Pin)18;
        /// <summary>
        /// GPIO PIN 0 pin 19.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A19 = (Cpu.Pin)19;
        /// <summary>
        /// GPIO PIN 0 pin 20.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A20 = (Cpu.Pin)20;
        /// <summary>
        /// GPIO PIN 0 pin 21.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A21 = (Cpu.Pin)21;
        /// <summary>
        /// GPIO PIN 0 pin 22.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A22 = (Cpu.Pin)22;
        /// <summary>
        /// GPIO PIN 0 pin 23.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A23 = (Cpu.Pin)23;
        /// <summary>
        /// GPIO PIN 0 pin 24.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A24 = (Cpu.Pin)24;
        /// <summary>
        /// GPIO PIN 0 pin 25.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A25 = (Cpu.Pin)25;
        /// <summary>
        /// GPIO PIN 0 pin 26.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A26 = (Cpu.Pin)26;
        /// <summary>
        /// GPIO PIN 0 pin 27.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A27 = (Cpu.Pin)27;
        /// <summary>
        /// GPIO PIN 0 pin 28.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A28 = (Cpu.Pin)28;
        /// <summary>
        /// GPIO PIN 0 pin 29.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A29 = (Cpu.Pin)29;
        /// <summary>
        /// GPIO PIN 0 pin 30.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A30 = (Cpu.Pin)30;
        /// <summary>
        /// GPIO PIN 0 pin 31.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_A31 = (Cpu.Pin)31;

	/// <summary>
        /// GPIO PIN 0 pin 0.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B0  = (Cpu.Pin)32;
        /// <summary>
        /// GPIO PIN 0 pin 1.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B1  = (Cpu.Pin)33;
        /// <summary>
        /// GPIO PIN 0 pin 2.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B2  = (Cpu.Pin)34;
        /// <summary>
        /// GPIO PIN 0 pin 3.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B3  = (Cpu.Pin)35;
        /// <summary>
        /// GPIO PIN 0 pin 4.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B4  = (Cpu.Pin)36;
        /// <summary>
        /// GPIO PIN 0 pin 5.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B5 = (Cpu.Pin)37;
        /// <summary>
        /// GPIO PIN 0 pin 6.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B6 = (Cpu.Pin)38;
        /// <summary>
        /// GPIO PIN 0 pin 7.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B7 = (Cpu.Pin)39;
        /// <summary>
        /// GPIO PIN 0 pin 8.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B8 = (Cpu.Pin)40;
        /// <summary>
        /// GPIO PIN 0 pin 9.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B9 = (Cpu.Pin)41;
        /// <summary>
        /// GPIO PIN 0 pin 10.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B10 = (Cpu.Pin)42;
        /// <summary>
        /// GPIO PIN 0 pin 11.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B11 = (Cpu.Pin)43;
        /// <summary>
        /// GPIO PIN 0 pin 12.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B12 = (Cpu.Pin)44;
        /// <summary>
        /// GPIO PIN 0 pin 13.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B13 = (Cpu.Pin)45;
        /// <summary>
        /// GPIO PIN 0 pin 14.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B14 = (Cpu.Pin)46;
        /// <summary>
        /// GPIO PIN 0 pin 15.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B15 = (Cpu.Pin)47;
        /// <summary>
        /// GPIO PIN 0 pin 16.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B16 = (Cpu.Pin)48;
        /// <summary>
        /// GPIO PIN 0 pin 17.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B17 = (Cpu.Pin)49;
        /// <summary>
        /// GPIO PIN 0 pin 18.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B18 = (Cpu.Pin)50;
        /// <summary>
        /// GPIO PIN 0 pin 19.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B19 = (Cpu.Pin)51;
        /// <summary>
        /// GPIO PIN 0 pin 20.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B20 = (Cpu.Pin)52;
        /// <summary>
        /// GPIO PIN 0 pin 21.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B21 = (Cpu.Pin)53;

        /// <summary>
        /// GPIO PIN 0 pin 22.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B22 = (Cpu.Pin)54;
        /// <summary>
        /// GPIO PIN 0 pin 23.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B23 = (Cpu.Pin)55;
        /// <summary>
        /// GPIO PIN 0 pin 24.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B24 = (Cpu.Pin)56;
        /// <summary>
        /// GPIO PIN 0 pin 25.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B25 = (Cpu.Pin)57;
        /// <summary>
        /// GPIO PIN 0 pin 26.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B26 = (Cpu.Pin)58;
        /// <summary>
        /// GPIO PIN 0 pin 27.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B27 = (Cpu.Pin)59;
        /// <summary>
        /// GPIO PIN 0 pin 28.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B28 = (Cpu.Pin)60;
        /// <summary>
        /// GPIO PIN 0 pin 29.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B29 = (Cpu.Pin)61;
        /// <summary>
        /// GPIO PIN 0 pin 30.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B30 = (Cpu.Pin)62;
        /// <summary>
        /// GPIO PIN 0 pin 31.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_B31 = (Cpu.Pin)63;
        		
		/// <summary>
        /// GPIO PIN 0 pin 0.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C0  = (Cpu.Pin)64;
        /// <summary>
        /// GPIO PIN 0 pin 1.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C1  = (Cpu.Pin)65;
        /// <summary>
        /// GPIO PIN 0 pin 2.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C2  = (Cpu.Pin)66;
        /// <summary>
        /// GPIO PIN 0 pin 3.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C3  = (Cpu.Pin)67;
        /// <summary>
        /// GPIO PIN 0 pin 4.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C4  = (Cpu.Pin)68;
        /// <summary>
        /// GPIO PIN 0 pin 5.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C5 = (Cpu.Pin)69;
        /// <summary>
        /// GPIO PIN 0 pin 6.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C6 = (Cpu.Pin)70;
        /// <summary>
        /// GPIO PIN 0 pin 7.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C7 = (Cpu.Pin)71;
        /// <summary>
        /// GPIO PIN 0 pin 8.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C8 = (Cpu.Pin)72;
        /// <summary>
        /// GPIO PIN 0 pin 9.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C9 = (Cpu.Pin)73;
        /// <summary>
        /// GPIO PIN 0 pin 10.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C10 = (Cpu.Pin)74;
        /// <summary>
        /// GPIO PIN 0 pin 11.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C11 = (Cpu.Pin)75;
        /// <summary>
        /// GPIO PIN 0 pin 12.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C12 = (Cpu.Pin)76;
        /// <summary>
        /// GPIO PIN 0 pin 13.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C13 = (Cpu.Pin)77;
        /// <summary>
        /// GPIO PIN 0 pin 14.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C14 = (Cpu.Pin)78;
        /// <summary>
        /// GPIO PIN 0 pin 15.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C15 = (Cpu.Pin)79;
        /// <summary>
        /// GPIO PIN 0 pin 16.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C16 = (Cpu.Pin)80;
        /// <summary>
        /// GPIO PIN 0 pin 17.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C17 = (Cpu.Pin)81;
        /// <summary>
        /// GPIO PIN 0 pin 18.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C18 = (Cpu.Pin)82;
        /// <summary>
        /// GPIO PIN 0 pin 19.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C19 = (Cpu.Pin)83;
        /// <summary>
        /// GPIO PIN 0 pin 20.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C20 = (Cpu.Pin)84;
        /// <summary>
        /// GPIO PIN 0 pin 21.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C21 = (Cpu.Pin)85;
        /// <summary>
        /// GPIO PIN 0 pin 22.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C22 = (Cpu.Pin)86;
        /// <summary>
        /// GPIO PIN 0 pin 23.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C23 = (Cpu.Pin)87;
        /// <summary>
        /// GPIO PIN 0 pin 24.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C24 = (Cpu.Pin)88;
        /// <summary>
        /// GPIO PIN 0 pin 25.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C25 = (Cpu.Pin)89;
        /// <summary>
        /// GPIO PIN 0 pin 26.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C26 = (Cpu.Pin)90;
        /// <summary>
        /// GPIO PIN 0 pin 27.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C27 = (Cpu.Pin)91;
        /// <summary>
        /// GPIO PIN 0 pin 28.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C28 = (Cpu.Pin)92;
        /// <summary>
        /// GPIO PIN 0 pin 29.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C29 = (Cpu.Pin)93;
        /// <summary>
        /// GPIO PIN 0 pin 30.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C30 = (Cpu.Pin)94;
        /// <summary>
        /// GPIO PIN 0 pin 31.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_C31 = (Cpu.Pin)95;
        
		/// <summary>
        /// GPIO PIN 0 pin 0.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D0  = (Cpu.Pin)96;
        /// <summary>
        /// GPIO PIN 0 pin 1.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D1  = (Cpu.Pin)97;
        /// <summary>
        /// GPIO PIN 0 pin 2.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D2  = (Cpu.Pin)98;
        /// <summary>
        /// GPIO PIN 0 pin 3.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D3  = (Cpu.Pin)99;
        /// <summary>
        /// GPIO PIN 0 pin 4.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D4  = (Cpu.Pin)100;
        /// <summary>
        /// GPIO PIN 0 pin 5.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D5 = (Cpu.Pin)101;
        /// <summary>
        /// GPIO PIN 0 pin 6.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D6 = (Cpu.Pin)102;
        /// <summary>
        /// GPIO PIN 0 pin 7.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D7 = (Cpu.Pin)103;
        /// <summary>
        /// GPIO PIN 0 pin 8.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D8 = (Cpu.Pin)104;
        /// <summary>
        /// GPIO PIN 0 pin 9.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D9 = (Cpu.Pin)105;
        /// <summary>
        /// GPIO PIN 0 pin 10.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D10 = (Cpu.Pin)106;
        /// <summary>
        /// GPIO PIN 0 pin 11.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D11 = (Cpu.Pin)107;
        /// <summary>
        /// GPIO PIN 0 pin 12.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D12 = (Cpu.Pin)108;
        /// <summary>
        /// GPIO PIN 0 pin 13.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D13 = (Cpu.Pin)109;
        /// <summary>
        /// GPIO PIN 0 pin 14.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D14 = (Cpu.Pin)110;
        /// <summary>
        /// GPIO PIN 0 pin 15.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D15 = (Cpu.Pin)111;
        /// <summary>
        /// GPIO PIN 0 pin 16.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D16 = (Cpu.Pin)112;
        /// <summary>
        /// GPIO PIN 0 pin 17.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D17 = (Cpu.Pin)113;
        /// <summary>
        /// GPIO PIN 0 pin 18.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D18 = (Cpu.Pin)114;
        /// <summary>
        /// GPIO PIN 0 pin 19.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D19 = (Cpu.Pin)115;
        /// <summary>
        /// GPIO PIN 0 pin 20.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D20 = (Cpu.Pin)116;
        /// <summary>
        /// GPIO PIN 0 pin 21.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D21 = (Cpu.Pin)117;
        /// <summary>
        /// GPIO PIN 0 pin 22.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D22 = (Cpu.Pin)118;
        /// <summary>
        /// GPIO PIN 0 pin 23.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D23 = (Cpu.Pin)119;
        /// <summary>
        /// GPIO PIN 0 pin 24.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D24 = (Cpu.Pin)120;
        /// <summary>
        /// GPIO PIN 0 pin 25.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D25 = (Cpu.Pin)121;
        /// <summary>
        /// GPIO PIN 0 pin 26.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D26 = (Cpu.Pin)122;
        /// <summary>
        /// GPIO PIN 0 pin 27.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D27 = (Cpu.Pin)123;
        /// <summary>
        /// GPIO PIN 0 pin 28.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D28 = (Cpu.Pin)124;
        /// <summary>
        /// GPIO PIN 0 pin 29.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D29 = (Cpu.Pin)125;
        /// <summary>
        /// GPIO PIN 0 pin 30.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D30 = (Cpu.Pin)126;
        /// <summary>
        /// GPIO PIN 0 pin 31.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_D31 = (Cpu.Pin)127;
        
		/// <summary>
        /// GPIO PIN 0 pin 0.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E0  = (Cpu.Pin)128;
        /// <summary>
        /// GPIO PIN 0 pin 1.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E1  = (Cpu.Pin)129;
        /// <summary>
        /// GPIO PIN 0 pin 2.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E2  = (Cpu.Pin)130;
        /// <summary>
        /// GPIO PIN 0 pin 3.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E3  = (Cpu.Pin)131;
        /// <summary>
        /// GPIO PIN 0 pin 4.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E4  = (Cpu.Pin)132;
        /// <summary>
        /// GPIO PIN 0 pin 5.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E5 = (Cpu.Pin)133;
        /// <summary>
        /// GPIO PIN 0 pin 6.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E6 = (Cpu.Pin)134;
        /// <summary>
        /// GPIO PIN 0 pin 7.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E7 = (Cpu.Pin)135;
        /// <summary>
        /// GPIO PIN 0 pin 8.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E8 = (Cpu.Pin)136;
        /// <summary>
        /// GPIO PIN 0 pin 9.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E9 = (Cpu.Pin)137;
        /// <summary>
        /// GPIO PIN 0 pin 10.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E10 = (Cpu.Pin)138;
        /// <summary>
        /// GPIO PIN 0 pin 11.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E11 = (Cpu.Pin)139;
        /// <summary>
        /// GPIO PIN 0 pin 12.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E12 = (Cpu.Pin)140;
        /// <summary>
        /// GPIO PIN 0 pin 13.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E13 = (Cpu.Pin)141;
        /// <summary>
        /// GPIO PIN 0 pin 14.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E14 = (Cpu.Pin)142;
        /// <summary>
        /// GPIO PIN 0 pin 15.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E15 = (Cpu.Pin)143;
        /// <summary>
        /// GPIO PIN 0 pin 16.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E16 = (Cpu.Pin)144;
        /// <summary>
        /// GPIO PIN 0 pin 17.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E17 = (Cpu.Pin)145;
        /// <summary>
        /// GPIO PIN 0 pin 18.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E18 = (Cpu.Pin)146;
        /// <summary>
        /// GPIO PIN 0 pin 19.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E19 = (Cpu.Pin)147;
        /// <summary>
        /// GPIO PIN 0 pin 20.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E20 = (Cpu.Pin)148;
        /// <summary>
        /// GPIO PIN 0 pin 21.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E21 = (Cpu.Pin)149;
        /// <summary>
        /// GPIO PIN 0 pin 22.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E22 = (Cpu.Pin)150;
        /// <summary>
        /// GPIO PIN 0 pin 23.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E23 = (Cpu.Pin)151;
        /// <summary>
        /// GPIO PIN 0 pin 24.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E24 = (Cpu.Pin)152;
        /// <summary>
        /// GPIO PIN 0 pin 25.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E25 = (Cpu.Pin)153;
        /// <summary>
        /// GPIO PIN 0 pin 26.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E26 = (Cpu.Pin)154;
        /// <summary>
        /// GPIO PIN 0 pin 27.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E27 = (Cpu.Pin)155;
        /// <summary>
        /// GPIO PIN 0 pin 28.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E28 = (Cpu.Pin)156;
        /// <summary>
        /// GPIO PIN 0 pin 29.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E29 = (Cpu.Pin)157;
        /// <summary>
        /// GPIO PIN 0 pin 30.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E30 = (Cpu.Pin)158;
        /// <summary>
        /// GPIO PIN 0 pin 31.
        /// </summary>
        public const Cpu.Pin GPIO_PIN_E31 = (Cpu.Pin)159;
        		
        public const Cpu.Pin GPIO_NONE = Cpu.Pin.GPIO_NONE;
    }

    public static class SerialPorts
    {
        public const string COM1 = "COM1";
        public const string COM2 = "COM2";
        public const string COM3 = "COM3";
        public const string COM4 = "COM4";
    }
    
    public static class BaudRates
    {
        public const BaudRate Baud19200  = BaudRate.Baudrate19200;
        public const BaudRate Baud38400  = BaudRate.Baudrate38400;
        public const BaudRate Baud57600  = BaudRate.Baudrate57600;
        public const BaudRate Baud115200 = BaudRate.Baudrate115200;
        public const BaudRate Baud230400 = BaudRate.Baudrate230400;
    }

    public static class ResistorModes
    {
        public const Port.ResistorMode PullUp   = Port.ResistorMode.PullUp;
        public const Port.ResistorMode Disabled = Port.ResistorMode.Disabled;
    }

    public static class InterruptModes
    {
        public const Port.InterruptMode InterruptEdgeLow       = Port.InterruptMode.InterruptEdgeLow ;
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
