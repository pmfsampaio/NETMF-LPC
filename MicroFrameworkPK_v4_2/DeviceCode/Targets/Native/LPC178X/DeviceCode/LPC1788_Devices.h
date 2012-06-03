/**********************************************************************
* $Id: LPC177x_8x.h 7485 2011-06-03 07:57:16Z sgg06786 $		LPC177x_8x.h			2011-06-02
*//**
* @file		LPC177x_8x.h
* @brief	Cortex-M3 Core Peripheral Access Layer Header File for
*			NXP LPC177x_8x Series.
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

#ifndef __LPC1788_DEVICES_H__
#define __LPC1788_DEVICES_H__

#include "./CMSIS/include/LPC177x_8x.h"
#include "./CMSIS/include/core_cm3.h"

//////////////////////////////////////////////////////////////////////////////
// TIMERS
//
struct LPC178X_TIMER
{

    static const UINT32 c_Timer_0 = 0;
    static const UINT32 c_Timer_1 = 1;
    static const UINT32 c_Timer_2 = 2;
    static const UINT32 c_Timer_3 = 3;
    static const UINT32 c_MaxTimer_no = 3;

    static const UINT32 c_TimerBase_0 = LPC_TIM0_BASE;
    static const UINT32 c_TimerBase_1 = LPC_TIM1_BASE;
    static const UINT32 c_TimerBase_2 = LPC_TIM2_BASE;
    static const UINT32 c_TimerBase_3 = LPC_TIM3_BASE;


    /****/ volatile UINT32 IR;     // Interrupt register
           static const    UINT32 MR0_COMP                   = 0x00000001;
           static const    UINT32 MR0_RESET                  = 0x00000001;

    /****/ volatile UINT32 TCR;    // Timer control register
           static const    UINT32 TCR_TEN                    = 0x00000001;

    /****/ volatile UINT32 TC;     // Timer counter
    /****/ volatile UINT32 PR;     // Pre scale register
    /****/ volatile UINT32 PC;     // Pre scale counter register
    /****/ volatile UINT32 MCR;    // Match control register
    /****/ volatile UINT32 MR0;    // Match 0 register
           static const    UINT32 MR0_IRQEN                  = 0x00000001;

    /****/ volatile UINT32 MR1;    // Match 1 register
    /****/ volatile UINT32 MR2;    // Match 2 register
    /****/ volatile UINT32 MR3;    // Match 3 register
    /****/ volatile UINT32 CCR;    // Capture control register
    /****/ volatile UINT32 CR0;    // Capture 0 register
    /****/ volatile UINT32 CR1;    // Capture 1 register
    /****/ volatile UINT32 CR2;    // Capture 2 register
    /****/ volatile UINT32 CR3;    // Capture 3 register
    /****/ volatile UINT32 EMR;    // External match register
    //functions.
    static UINT32 inline getIntNo(int Timer)
    {
        switch (Timer)
        {
        case  c_Timer_0:
            return TIMER0_IRQn;//LPC178X_VIC::c_IRQ_INDEX_TIMER0;
            break;
        case  c_Timer_1:
            return TIMER1_IRQn;//LPC178X_VIC::c_IRQ_INDEX_TIMER1;
            break;
        case  c_Timer_2:
            return TIMER2_IRQn;//LPC178X_VIC::c_IRQ_INDEX_TIMER2;
            break;
        case  c_Timer_3:
            return TIMER3_IRQn;//LPC178X_VIC::c_IRQ_INDEX_TIMER3;
            break;
        default:
            ASSERT(TRUE);
            return(Timer);
            break;
        }
    }
};
//
// TIMER
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// GP I/O
//
struct LPC178X_GPIO
{
    // Use FAST IO for all ports
    static const UINT32 c_GPIO_Base = LPC_GPIO0_BASE;//  0x3FFFC000;
    static const UINT32 c_GPIO_Irq = GPIO_IRQn;


    //--//

    static const UINT32 c_Pin_None  = 0xFFFFFFFF;
// Controlled by PINSEL0
    static const UINT32 c_P0_00 =   0; // RD1          / TXD3         / SDA1
    static const UINT32 c_P0_01 =   1; // TD1          / RXD3         / SCL1
    static const UINT32 c_P0_02 =   2; // TXD0         / Reserved     / Reserved
    static const UINT32 c_P0_03 =   3; // RXD0         / Reserved     / Reserved
    static const UINT32 c_P0_04 =   4; // I2SRX_CLK    / RD2          / CAP2[0]
                                        // LCDVD[0]
    static const UINT32 c_P0_05 =   5; // I2SRX_WS     / TD2          / CAP2[1]
                                        // LCDVD[1]
    static const UINT32 c_P0_06 =   6; // I2SRX_SDA    / SSEL1        / MAT2[0]
                                        // LCDVD[8]
    static const UINT32 c_P0_07 =   7; // I2STX_CLK    / SCK1         / MAT2[1]
                                        // LCDVD[9]
    static const UINT32 c_P0_08 =   8; // I2STX_WS     / MISO1        / MAT2[2]
                                        // LCDVD[16]
    static const UINT32 c_P0_09 =   9; // I2STX_SDA    / MOSI1        / MAT2[3]
                                        // LCDVD[17]
    static const UINT32 c_P0_10 =  10; // TXD2         / SDA2         / MAT3[0]
    static const UINT32 c_P0_11 =  11; // RXD2         / SCL2         / MAT3[1]
    static const UINT32 c_P0_12 =  12; // USB_PPWR2    / MISO1        / AD0[6]
    static const UINT32 c_P0_13 =  13; // USB_UP_LED2  / MOSI1        / AD0[7]
    static const UINT32 c_P0_14 =  14; // USB_HSTEN2   / USB_CONNECT2 / SSEL1
    static const UINT32 c_P0_15 =  15; // TXD1         / SCK0         / SCK
// Controlled by PINSEL1
    static const UINT32 c_P0_16 =  16; // RXD1         / SSEL0        / SSEL
    static const UINT32 c_P0_17 =  17; // CTS1         / MISO0        / MISO
    static const UINT32 c_P0_18 =  18; // DCD1         / MOSI0        / MOSI
    static const UINT32 c_P0_19 =  19; // DSR1         / MCICLK       / SDA1
    static const UINT32 c_P0_20 =  20; // DTR1         / MCICMD       / SCL1
    static const UINT32 c_P0_21 =  21; // RI1          / MCIPWR       / RD1
    static const UINT32 c_P0_22 =  22; // RTS1         / MCIDAT0      / TD1
    static const UINT32 c_P0_23 =  23; // AD0[0]       / I2SRX_CLK    / CAP3[0]
    static const UINT32 c_P0_24 =  24; // AD0[1]       / I2SRX_WS     / CAP3[1]
    static const UINT32 c_P0_25 =  25; // AD0[2]       / I2SRX_SDA    / TXD3
    static const UINT32 c_P0_26 =  26; // AD0[3]       / AOUT         / RXD3
    static const UINT32 c_P0_27 =  27; // SDA0         / Reserved     / Reserved
    static const UINT32 c_P0_28 =  28; // SCL0         / Reserved     / Reserved
    static const UINT32 c_P0_29 =  29; // USB_D+1      / Reserved     / Reserved
    static const UINT32 c_P0_30 =  30; // USB_D-1      / Reserved     / Reserved
    static const UINT32 c_P0_31 =  31; // USB_D+2      / Reserved     / Reserved
// Controlled by PINSEL2
    static const UINT32 c_P1_00 =  32; // ENET_TXD0    / Reserved     / Reserved
    static const UINT32 c_P1_01 =  33; // ENET_TXD1    / Reserved     / Reserved
    static const UINT32 c_P1_02 =  34; // ENET_TXD2    / MCICLK       / PWM0[1]
    static const UINT32 c_P1_03 =  35; // ENET_TXD3    / MCICMD       / PWM0[2]
    static const UINT32 c_P1_04 =  36; // ENET_TX_EN   / Reserved     / Reserved
    static const UINT32 c_P1_05 =  37; // ENET_TX_ER   / MCIPWR       / PWM0[3]
    static const UINT32 c_P1_06 =  38; // ENET_TX_CLK  / MCIDAT0      / PWM0[4]
    static const UINT32 c_P1_07 =  39; // ENET_COL     / MCIDAT1      / PWM0[5]
    static const UINT32 c_P1_08 =  40; // ENET_CRS_DV  / Reserved     / Reserved
                                        // ENET_CRS
    static const UINT32 c_P1_09 =  41; // ENET_RXD0    / Reserved     / Reserved
    static const UINT32 c_P1_10 =  42; // ENET_RXD1    / Reserved     / Reserved
    static const UINT32 c_P1_11 =  43; // ENET_RXD2    / MCIDAT2      / PWM0[6]
    static const UINT32 c_P1_12 =  44; // ENET_RXD3    / MCIDAT3      / PCAP0[0]
    static const UINT32 c_P1_13 =  45; // ENET_RX_DV   / Reserved     / Reserved
    static const UINT32 c_P1_14 =  46; // ENET_RX_ER   / Reserved     / Reserved
    static const UINT32 c_P1_15 =  47; // ENET_REF_CLK / Reserved     / Reserved
                                        // ENET_CRS
// Controlled by PINSEL3
    static const UINT32 c_P1_16 =  48; // ENET_MDC     / Reserved     / Reserved
    static const UINT32 c_P1_17 =  49; // ENET_MDIO    / Reserved     / Reserved
    static const UINT32 c_P1_18 =  50; // USB_UP_LED1  / PWM1[1]      / CAP1[0]
    static const UINT32 c_P1_19 =  51; // USB_TX_E1    / USB_PPWR1    / CAP1[1]
    static const UINT32 c_P1_20 =  52; // USB_TX_DP1   / PWM1[2]      / SCK0
                                        // LCDVD[6]
                                        // LCDVD[10]
    static const UINT32 c_P1_21 =  53; // USB_TX_DM1   / PWM1[3]      / SSEL0
                                        // LCDVD[7]
                                        // LCDVD[11]
    static const UINT32 c_P1_22 =  54; // USB_RCV1     / USB_PWRD1    / MAT1[0]
                                        // LCDVD[8]
                                        // LCDVD[12]
    static const UINT32 c_P1_23 =  55; // USB_RX_DP1   / PWM1[4]      / MISO0
                                        // LCDVD[9]
                                        // LCDVD[13]
    static const UINT32 c_P1_24 =  56; // USB_RX_DM1   / PWM1[5]      / MOSI0
                                        // LCDVD[10]
                                        // LCDVD[14]
    static const UINT32 c_P1_25 =  57; // USB_LS1      / USB_HSTEN1   / MAT1[1]
                                        // LCDVD[11]
                                        // LCDVD[15]
    static const UINT32 c_P1_26 =  58; // USB_SSPND1   / PWM1[6]      / CAP0[0]
                                        // LCDVD[12]
                                        // LCDVD[20]
    static const UINT32 c_P1_27 =  59; // USB_INT1     / USB_OVRCR1   / CAP0[1]
                                        // LCDVD[13]
                                        // LCDVD[21]
    static const UINT32 c_P1_28 =  60; // USB_SCL1     / PCAP1[0]     / MAT0[0]
                                        // LCDVD[14]
                                        // LCDVD[22]
    static const UINT32 c_P1_29 =  61; // USB_SDA1     / PCAP1[1]     / MAT0[1]
                                        // LCDVD[15]
                                        // LCDVD[23]
    static const UINT32 c_P1_30 =  62; // USB_PWRD2    / VBUS         / AD0[4]
    static const UINT32 c_P1_31 =  63; // USB_OVRCR2   / SCK1         / AD0[5]
// Controlled by PINSEL4
    static const UINT32 c_P2_00 =  64; // PWM1[1]      / TXD1         / TRACECLK
                                        //                             / LCDPWR
    static const UINT32 c_P2_01 =  65; // PWM1[2]      / RXD1         / PIPESTAT0
                                        //                             / LCDLE
    static const UINT32 c_P2_02 =  66; // PWM1[3]      / CTS1         / PIPESTAT1
                                        //                             / LCDDCLK
    static const UINT32 c_P2_03 =  67; // PWM1[4]      / DCD1         / PIPESTAT2
                                        //                             / LCDFP
    static const UINT32 c_P2_04 =  68; // PWM1[5]      / DSR11        / TRACESYNC
                                        //                             / LCDENAB
                                        //                             / LCDM
    static const UINT32 c_P2_05 =  69; // PWM1[6]      / DTR1         / TRACEPKT0
                                        //                             / LCDLP
    static const UINT32 c_P2_06 =  70; // PCAP1[0]     / RI1          / TRACEPKT1
                                        //                             / LCDVD[0]
                                        //                             / LCDVD[4]
    static const UINT32 c_P2_07 =  71; // RD2          / RTS1         / TRACEPKT2
                                        //                             / LCDVD[1]
                                        //                             / LCDVD[5]
    static const UINT32 c_P2_08 =  72; // TD2          / TXD2         / TRACEPKT3
                                        //                             / LCDVD[2]
                                        //                             / LCDVD[6]
    static const UINT32 c_P2_09 =  73; // USB_CONNECT1 / RXD2         / EXTIN0
                                        //                             / LCDVD[3]
                                        //                             / LCDVD[7]
    static const UINT32 c_P2_10 =  74; // EINT0        / Reserved     / Reserved
    static const UINT32 c_P2_11 =  75; // EINT1        / MCIDAT1      / I2STX_CLK
    static const UINT32 c_P2_12 =  76; // EINT2        / MCIDAT2      / I2STX_WS
                                        // LCDVD[4]
                                        // LCDVD[3]
                                        // LCDVD[8]
                                        // LCDVD[18]
    static const UINT32 c_P2_13 =  77; // EINT3        / MCIDAT3      / I2STX_SDA
                                        // LCDVD[5]
                                        // LCDVD[9]
                                        // LCDVD[19]
    static const UINT32 c_P2_14 =  78; // CS2          / CAP2[0]      / SDA1
    static const UINT32 c_P2_15 =  79; // CS3          / CAP2[1]      / SCL1
// Controlled by PINSEL5
    static const UINT32 c_P2_16 =  80; // CAS          / Reserved     / Reserved
    static const UINT32 c_P2_17 =  81; // RAS          / Reserved     / Reserved
    static const UINT32 c_P2_18 =  82; // CLKOUT0      / Reserved     / Reserved
    static const UINT32 c_P2_19 =  83; // CLKOUT1      / Reserved     / Reserved
    static const UINT32 c_P2_20 =  84; // DYCS0        / Reserved     / Reserved
    static const UINT32 c_P2_21 =  85; // DYCS1        / Reserved     / Reserved
    static const UINT32 c_P2_22 =  86; // DYCS2        / CAP3[0]      / SCK0
    static const UINT32 c_P2_23 =  87; // DYCS3        / CAP3[1]      / SSEL0
    static const UINT32 c_P2_24 =  88; // CKEOUT0      / Reserved     / Reserved
    static const UINT32 c_P2_25 =  89; // CKEOUT1      / Reserved     / Reserved
    static const UINT32 c_P2_26 =  90; // CKEOUT2      / MAT3[0]      / MISO0
    static const UINT32 c_P2_27 =  91; // CKEOUT3      / MAT3[1]      / MOSI0
    static const UINT32 c_P2_28 =  92; // DQMOUT0      / Reserved     / Reserved
    static const UINT32 c_P2_29 =  93; // DQMOUT1      / Reserved     / Reserved
    static const UINT32 c_P2_30 =  94; // DQMOUT2      / MAT3[2]      / SDA2
    static const UINT32 c_P2_31 =  95; // DQMOUT3      / MAT3[3]      / SCL2
// Controlled by PINSEL6
    static const UINT32 c_P3_00 =  96; // D0           / Reserved     / Reserved
    static const UINT32 c_P3_01 =  97; // D1           / Reserved     / Reserved
    static const UINT32 c_P3_02 =  98; // D2           / Reserved     / Reserved
    static const UINT32 c_P3_03 =  99; // D3           / Reserved     / Reserved
    static const UINT32 c_P3_04 = 100; // D4           / Reserved     / Reserved
    static const UINT32 c_P3_05 = 101; // D5           / Reserved     / Reserved
    static const UINT32 c_P3_06 = 102; // D6           / Reserved     / Reserved
    static const UINT32 c_P3_07 = 103; // D7           / Reserved     / Reserved
    static const UINT32 c_P3_08 = 104; // D8           / Reserved     / Reserved
    static const UINT32 c_P3_09 = 105; // D9           / Reserved     / Reserved
    static const UINT32 c_P3_10 = 106; // D10          / Reserved     / Reserved
    static const UINT32 c_P3_11 = 107; // D11          / Reserved     / Reserved
    static const UINT32 c_P3_12 = 108; // D12          / Reserved     / Reserved
    static const UINT32 c_P3_13 = 109; // D13          / Reserved     / Reserved
    static const UINT32 c_P3_14 = 110; // D14          / Reserved     / Reserved
    static const UINT32 c_P3_15 = 111; // D15          / Reserved     / Reserved
// Controlled by PINSEL7
    static const UINT32 c_P3_16 = 112; // D16          / PWM0[1]      / TXD1
    static const UINT32 c_P3_17 = 113; // D17          / PWM0[2]      / RXD1
    static const UINT32 c_P3_18 = 114; // D18          / PWM0[3]      / CTS1
    static const UINT32 c_P3_19 = 115; // D19          / PWM0[4]      / DCD1
    static const UINT32 c_P3_20 = 116; // D20          / PWM0[5]      / DSR1
    static const UINT32 c_P3_21 = 117; // D21          / PWM0[6]      / DR1
    static const UINT32 c_P3_22 = 118; // D22          / PCAP0[0]     / RI1
    static const UINT32 c_P3_23 = 119; // D23          / CAP0[0]      / PCAP1[0]
    static const UINT32 c_P3_24 = 120; // D24          / CAP0[1]      / PWM1[1]
    static const UINT32 c_P3_25 = 121; // D25          / MAT0[0]      / PWM1[2]
    static const UINT32 c_P3_26 = 122; // D26          / MAT0[1]      / PWM1[3]
    static const UINT32 c_P3_27 = 123; // D27          / CAP1[0]      / PWM1[4]
    static const UINT32 c_P3_28 = 124; // D28          / CAP1[1]      / PWM1[5]
    static const UINT32 c_P3_29 = 125; // D29          / MAT1[0]      / PWM1[6]
    static const UINT32 c_P3_30 = 126; // D30          / MAT1[1]      / RTS1
    static const UINT32 c_P3_31 = 127; // D31          / MAT1[2]      / Reserved
// Controlled by PINSEL8
    static const UINT32 c_P4_00 = 128; // A0           / Reserved     / Reserved
    static const UINT32 c_P4_01 = 129; // A1           / Reserved     / Reserved
    static const UINT32 c_P4_02 = 130; // A2           / Reserved     / Reserved
    static const UINT32 c_P4_03 = 131; // A3           / Reserved     / Reserved
    static const UINT32 c_P4_04 = 132; // A4           / Reserved     / Reserved
    static const UINT32 c_P4_05 = 133; // A5           / Reserved     / Reserved
    static const UINT32 c_P4_06 = 134; // A6           / Reserved     / Reserved
    static const UINT32 c_P4_07 = 135; // A7           / Reserved     / Reserved
    static const UINT32 c_P4_08 = 136; // A8           / Reserved     / Reserved
    static const UINT32 c_P4_09 = 137; // A9           / Reserved     / Reserved
    static const UINT32 c_P4_10 = 138; // A10          / Reserved     / Reserved
    static const UINT32 c_P4_11 = 139; // A11          / Reserved     / Reserved
    static const UINT32 c_P4_12 = 140; // A12          / Reserved     / Reserved
    static const UINT32 c_P4_13 = 141; // A13          / Reserved     / Reserved
    static const UINT32 c_P4_14 = 142; // A14          / Reserved     / Reserved
    static const UINT32 c_P4_15 = 143; // A15          / Reserved     / Reserved
// Controlled by PINSEL9
    static const UINT32 c_P4_16 = 144; // A16          / Reserved     / Reserved
    static const UINT32 c_P4_17 = 145; // A17          / Reserved     / Reserved
    static const UINT32 c_P4_18 = 146; // A18          / Reserved     / Reserved
    static const UINT32 c_P4_19 = 147; // A19          / Reserved     / Reserved
    static const UINT32 c_P4_20 = 148; // A20          / SDA2         / SCK1
    static const UINT32 c_P4_21 = 149; // A21          / SCL2         / SSEL1
    static const UINT32 c_P4_22 = 150; // A22          / TXD2         / MISO1
    static const UINT32 c_P4_23 = 151; // A23          / RXD2         / MOSI1
    static const UINT32 c_P4_24 = 152; // OE           / Reserved     / Reserved
    static const UINT32 c_P4_25 = 153; // WE           / Reserved     / Reserved
    static const UINT32 c_P4_26 = 154; // BLS0         / Reserved     / Reserved
    static const UINT32 c_P4_27 = 155; // BLS1         / Reserved     / Reserved
    static const UINT32 c_P4_28 = 156; // BLS2         / MAT2[0]      / TXD3 00
                                        //                             / LCDVD[6]
                                        //                             / LCDVD[10]
                                        //                             / LCDVD[2]
    static const UINT32 c_P4_29 = 157; // BLS3         / MAT2[1]      / RXD3
                                        //                             / LCDVD[7]
                                        //                             / LCDVD[11]
                                        //                             / LCDVD[3]
    static const UINT32 c_P4_30 = 158; // CS0          / Reserved     / Reserved
    static const UINT32 c_P4_31 = 159; // CS1          / Reserved     / Reserved

    //--//

    struct
    {
        /****/ volatile UINT32 FIODIR_PX;            // Direction Control
        /****/ volatile UINT32 dummy1;               // filler to align address
        /****/ volatile UINT32 dummy2;               // filler to align address
        /****/ volatile UINT32 dummy3;               // filler to align address
        /****/ volatile UINT32 FIOMASK_PX;           // Pin Mask Register
        /****/ volatile UINT32 FIOPIN_PX;            // Pin Value Register
        /****/ volatile UINT32 FIOSET_PX;            // Data Output Set Register
        /****/ volatile UINT32 FIOCLR_PX;            // Data Output Clear Register
    } Regs[5];

};
    //--//

struct LPC178X_GPIOIRQ
{

    // GPIO IRQ registers for P0 & P2

    static const UINT32 c_GPIOIRQ_Base = LPC_GPIOINT_BASE;

    //GPIO Interrupt registers (port 0 & 2 only can generate IRQs)

    //IRQ Overall Status
    UINT32 volatile IOIntStatus;    // 0x40028080

    ////////////
    // PORT 0 //
    ////////////

    //IRQ Status
    UINT32 volatile IO0IntStatR;    // 0x40028084
    UINT32 volatile IO0IntStatF;    // 0x40028088

    //IRQ Clear
    UINT32 volatile IO0IntClr;        // 0x4002808C

    //IRQ Enable
    UINT32 volatile IO0IntEnR;        // 0x40028090
    UINT32 volatile IO0IntEnF;        // 0x40028094

    //////////////////
    // DUMMY PORT 1 //
    //////////////////

    UINT32 P1_generates_no_irqs[3]; // 0x400280{98-9C-A0} (why did they leave just 3 empty regs?)

    ////////////
    // PORT 2 //
    ////////////

    //IRQ Status
    UINT32 volatile IO2IntStatR;    // 0x400280A4
    UINT32 volatile IO2IntStatF;    // 0x400280A8

    //IRQ Clear
    UINT32 volatile IO2IntClr;        // 0x400280AC

    //IRQ Enable
    UINT32 volatile IO2IntEnR;        // 0x400280B0
    UINT32 volatile IO2IntEnF;        // 0x400280B4


};
//
// GP I/O
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// UART
//

struct LPC178X_USART
{
    static const UINT32 c_Uart_0        = 0;
    static const UINT32 c_Uart_1        = 1;
    static const UINT32 c_Uart_2        = 2;
    static const UINT32 c_Uart_3        = 3;
    static const UINT32 c_MaxUart_no     = 3;

    static const UINT32 c_UartBase_0    = LPC_UART0_BASE;
    static const UINT32 c_UartBase_1    = LPC_UART1_BASE;
    static const UINT32 c_UartBase_2    = LPC_UART2_BASE;
    static const UINT32 c_UartBase_3    = LPC_UART3_BASE;

    // UART0 pins
    static const UINT32 c_SER1_TXD = LPC178X_GPIO::c_P0_02;
    static const UINT32 c_SER1_RXD = LPC178X_GPIO::c_P0_03;

    // Add more pins if UART1 is used in full mode
    static const UINT32 c_SER2_TXD = LPC178X_GPIO::c_P3_16;
    static const UINT32 c_SER2_RXD = LPC178X_GPIO::c_P3_17;

    // UART2 pins
    static const UINT32 c_SER3_TXD = LPC178X_GPIO::c_P0_10;
    static const UINT32 c_SER3_RXD = LPC178X_GPIO::c_P0_11;

    // UART3 pins
    static const UINT32 c_SER4_TXD = LPC178X_GPIO::c_P0_00;
    static const UINT32 c_SER4_RXD = LPC178X_GPIO::c_P0_01;


    static const UINT32 c_ClockRate     = LPC178X_UART_PCLK;

    static const UINT32 c_MAX_BAUDRATE = c_ClockRate/16;
    static const UINT32 c_MIN_BAUDRATE = 0;

    //IER
    static const UINT32 UART_IER_RLSIE               = 0x00000004;   //Receive line status interrupt enable.
    static const UINT32 UART_IER_THREIE              = 0x00000002;   //transmit hold register empty interrupt enable.
    static const UINT32 UART_IER_RDAIE               = 0x00000001;   //Receive data available interrupt enable.

    static const UINT32 UART_IER_INTR_ALL_SET        = UART_IER_RLSIE | UART_IER_THREIE | UART_IER_RDAIE;

    //IID
    static const UINT32 UART_IIR_FMES                = 0x00000080;   //FIFO MODE Enable status.
    static const UINT32 UART_IIR_RFTLS_mask          = 0x00000060;   //RX FIFO threshold level status.
    static const UINT32 UART_IIR_RFTLS_shift         =          5;
    static const UINT32 UART_IIR_IID_mask            = 0x0000000F;   //Interrupt identification.
    // values.
    static const UINT32 UART_IIR_IID_Irpt_RLS        = 0x00000006;   // Receiver line status interrupt (e.g. overrun error) .
    static const UINT32 UART_IIR_IID_Irpt_RDA        = 0x00000004;   // Receive data ready interrupt.
    static const UINT32 UART_IIR_IID_Irpt_TOUT       = 0x0000000C;   // Receive FIFO timeout interrupt.
    static const UINT32 UART_IIR_IID_Irpt_THRE       = 0x00000002;   // Transmitter holding register empty.

    static const UINT32 UART_IIR_NIP                 = 0x00000001;   //There is no pending interrupt.

    //FCR
    static const UINT32 UART_FCR_RFITL_mask       = 0x000000C0;     // Rx FIFO trigger level
    static const UINT32 UART_FCR_RFITL_shift      =          6;

    static const UINT32 UART_FCR_RFITL_01         = 0x00000000;
    static const UINT32 UART_FCR_RFITL_04         = 0x00000001;
    static const UINT32 UART_FCR_RFITL_08         = 0x00000002;
    static const UINT32 UART_FCR_RFITL_14         = 0x00000003;

    static const UINT32 UART_FCR_TFR              = 0x00000004;     // Tx FIFO reset
    static const UINT32 UART_FCR_RFR              = 0x00000002;     // Rx FIFO reset
    static const UINT32 UART_FCR_FME              = 0x00000001;     // FIFO Mode enable


    union
    {
        struct
        {
            /****/ volatile UINT32 UART_RBR;                             //receive data register
        } RBR;
        struct
        {
            /****/ volatile UINT32 UART_THR;                            //transmit data register.

        } THR;
        struct
        {
            /****/ volatile UINT32 UART_DLL;                            //Divisor Latch register. (LSB)
        } DLL;

    } SEL1;

    union
    {
        struct
        {
            /****/ volatile UINT32 UART_IER;                                //Interrupt enable register
        } IER;
        struct
        {
            /****/ volatile UINT32 UART_DLM;                               //Divisor Latch register.  (MSB)
        } DLM;
    } SEL2;

    union
    {
        struct
        {
          /****/ volatile UINT32  UART_IIR;                                        //Interrupt identification register.
        } IIR;
        struct
        {
          /****/ volatile UINT32  UART_FCR;
        } FCR;
    } SEL3;

    /****/ volatile UINT32 UART_LCR;                                       // line control register.
    //--//
    static const UINT32 UART_LCR_DLAB                   = 0x00000080;     // Dividor Latch Access bit.
    static const UINT32 UART_LCR_BCB                    = 0x00000040;     // Break control bit.
    static const UINT32 UART_LCR_SPE                    = 0x00000020;     // Stick parity enable.
    static const UINT32 UART_LCR_EPE                    = 0x00000010;     // Even  parity enable.
    static const UINT32 UART_LCR_PBE                    = 0x00000008;     // Parity bit enable.
    static const UINT32 UART_LCR_NSB_1_STOPBITS         = 0x00000000;     // Number of stop bits (0 - 1 stop bit; 1 - 1.5 stop bits).
    static const UINT32 UART_LCR_NSB_15_STOPBITS        = 0x00000004;     // Number of stop bits (0 - 1 stop bit; 1 - 1.5 stop bits).
    static const UINT32 UART_LCR_WLS_mask               = 0x00000003;     // Word length select.
    static const UINT32 UART_LCR_WLS_shift              =          0;
    static const UINT32 UART_LCR_WLS_5_BITS             = 0x00000000;
    static const UINT32 UART_LCR_WLS_6_BITS             = 0x00000001;
    static const UINT32 UART_LCR_WLS_7_BITS             = 0x00000002;
    static const UINT32 UART_LCR_WLS_8_BITS             = 0x00000003;

    /****/ volatile UINT32 UART_MCR;                                       // modem control register.

    /****/ volatile UINT32 UART_LSR;                                       //line status register.
    static const UINT32 UART_LSR_ERR_RX                 = 0x00000080;     //Rx FIFO error
    static const UINT32 UART_LSR_TE                     = 0x00000040;     //Transmitter Empty.
    static const UINT32 UART_LSR_THRE                   = 0x00000020;     //Transmitter Holding register Empty.
    static const UINT32 UART_LSR_BII                    = 0x00000010;     //Break interrupt indicator.
    static const UINT32 UART_LSR_FEI                    = 0x00000008;     //Framing Error indicator.
    static const UINT32 UART_LSR_PEI                    = 0x00000004;     //Parity Error indicator.
    static const UINT32 UART_LSR_OEI                    = 0x00000002;     //Overrun Error indicator.
    static const UINT32 UART_LSR_RFDR                   = 0x00000001;     //RX FIFO data ready.

    /****/ volatile UINT32 UART_MSR;                                   //Modem status register.
    /****/ volatile UINT32 dummy1[3];
    /****/ volatile UINT32 UART_FDR;

    //functions.
    static UINT32 inline getIntNo(int ComPortNum)
    {
        switch (ComPortNum)
        {
        case c_Uart_0:
            return UART0_IRQn+16;//LPC178X_VIC::c_IRQ_INDEX_UART0;
            break;
        case c_Uart_1:
            return UART1_IRQn+16;//LPC178X_VIC::c_IRQ_INDEX_UART1;
            break;
        case c_Uart_2:
            return UART2_IRQn+16;//LPC178X_VIC::c_IRQ_INDEX_UART2;
            break;
        case c_Uart_3:
            return UART3_IRQn+16;//LPC178X_VIC::c_IRQ_INDEX_UART3;
            break;
        default:
            ASSERT(TRUE);
            return(ComPortNum);
            break;
        }
    }
};
//
// UART
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// SPI
//
struct LPC178X_SPI
{
    static const UINT32 c_SPI0_Base     = LPC_SSP0_BASE; // 0xE0020000;
    static const UINT32 c_SPI_Clk_KHz   = 0;//LPC178X_SPI_PCLK_KHZ;

    static const UINT32 c_SPI0 = 0;
    static const UINT32 c_MAX_SPI = 1;

    static const UINT32 c_SPI0_SCLK = LPC178X_GPIO::c_P0_15;
    static const UINT32 c_SPI0_MISO = LPC178X_GPIO::c_P0_17;
    static const UINT32 c_SPI0_MOSI = LPC178X_GPIO::c_P0_18;

    /****/ volatile UINT32 SPCR0;
    /****/ volatile UINT32 SPCR1;

//  MSB first always. SPI config structure does not contain a field for the bit order
    static const UINT32 CONTROLREG_BitEnable     = 0x00000004;
    static const UINT32 CONTROLREG_MODE_Master   = 0x00000000;
    static const UINT32 CONTROLREG_Frame_SPI     = 0x00000010;
    static const UINT32 CONTROLREG_PHA_1         = 0x00000000;
    static const UINT32 CONTROLREG_POL_1         = 0x00000000;

    /****/ volatile UINT32 SPDR;

    /****/ volatile UINT32 SPSR;

    static const    UINT32 SPIF_Mask     = 0x00000080;

    /****/ volatile UINT32 SPCPSR;

    /****/ volatile UINT32 SPIMSC;

    static UINT32 ConfigurationToMode( const SPI_CONFIGURATION& Configuration )
    {
        UINT32 Mode;


        Mode = CONTROLREG_MODE_Master | CONTROLREG_Frame_SPI;

        if(Configuration.MSK_IDLE)
        {
           // Idle is Active high, set 1,
            Mode |= CONTROLREG_POL_1;

            if(Configuration.MSK_SampleEdge)
            {
                Mode |= CONTROLREG_PHA_1;        // sample on rising edge
            }
            // else phase set to 0
        }
        else
        {
            if(!Configuration.MSK_SampleEdge)
            {
                Mode |= CONTROLREG_PHA_1;        // sample on rising edge
            }
            // else phase set to 0;
        }

        return Mode;
    }
};
//
// SPI
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// I2C
//
struct LPC178X_I2C
{
    static const UINT32 c_I2C_Base     = LPC_I2C0_BASE;//0xE001C000;
    static const UINT32 c_I2C_Clk_KHz  = 96000;//LPC178X_I2C_PCLK_KHZ;

    static const UINT32 c_I2C_SDA = LPC178X_GPIO::c_P0_27;
    static const UINT32 c_I2C_SCL = LPC178X_GPIO::c_P0_28;

    /****/ volatile UINT32 I2CONSET;
    static const    UINT32 I2EN  = 0x00000040;
    static const    UINT32 STA   = 0x00000020;
    static const    UINT32 STO   = 0x00000010;
    static const    UINT32 SI    = 0x00000008;
    static const    UINT32 AA    = 0x00000004;

    /****/ volatile UINT32 I2STAT;

    /****/ volatile UINT32 I2DAT;

    /****/ volatile UINT32 I2ADR;

    /****/ volatile UINT32 I2SCLH;

    /****/ volatile UINT32 I2SCLL;

    /****/ volatile UINT32 I2CONCLR;
};
//
// I2C
//////////////////////////////////////////////////////////////////////////////

struct LPC178X
{
//    static LPC178X_VIC    & VIC    (         ) { return *(LPC178X_VIC*     )(size_t)( LPC178X_VIC     ::c_VIC_Base      ); }
    static LPC178X_GPIO   & GPIO   (         ) { return *(LPC178X_GPIO*    )(size_t)( LPC178X_GPIO    ::c_GPIO_Base     ); }
    static LPC178X_GPIOIRQ& GPIOIRQ(         ) { return *(LPC178X_GPIOIRQ* )(size_t)( LPC178X_GPIOIRQ ::c_GPIOIRQ_Base  ); }
//    static LPC178X_PCB    & PCB    (         ) { return *(LPC178X_PCB*     )(size_t)( LPC178X_PCB     ::c_PCB_Base      ); }
//    static LPC178X_SYSCON & SYSCON (         ) { return *(LPC178X_SYSCON*  )(size_t)( LPC178X_SYSCON  ::c_SYSCON_Base   ); }
//    static LPC178X_EMC    & EMC    (         ) { return *(LPC178X_EMC*     )(size_t)( LPC178X_EMC     ::c_EMC_Base      ); }
    static LPC178X_SPI    & SPI    ( int sel ) { return *(LPC178X_SPI*     )(size_t)( LPC178X_SPI     ::c_SPI0_Base     ); }
    static LPC178X_I2C    & I2C    (         ) { return *(LPC178X_I2C*     )(size_t)( LPC178X_I2C     ::c_I2C_Base      ); }
//    static LPC178X_WATCHDOG & WTDG (         ) { return *(LPC178X_WATCHDOG*)(size_t)( LPC178X_WATCHDOG::c_WATCHDOG_Base ); }
//    static LPC178X_DAC      & DAC  (         ) { return *(LPC178X_DAC*     )(size_t)( LPC178X_DAC     ::c_DAC_Base      ); }
//    static LPC178X_PWM      & PWM  ( int sel ) { return *(LPC178X_PWM*     )(size_t)( sel == PWM_CHANNEL_0 ? LPC178X_PWM::c_PWM_Base_0 : LPC178X_PWM::c_PWM_Base_1); }


    static LPC178X_TIMER  & TIMER( int sel )
    {
        ASSERT(sel <=LPC178X_TIMER::c_MaxTimer_no)

        if (sel == LPC178X_TIMER::c_Timer_0)
             return *(LPC178X_TIMER  *)(size_t)LPC178X_TIMER::c_TimerBase_0;
        else if (sel == LPC178X_TIMER::c_Timer_1)
             return *(LPC178X_TIMER  *)(size_t)LPC178X_TIMER::c_TimerBase_1;
        else if (sel == LPC178X_TIMER::c_Timer_2)
             return *(LPC178X_TIMER  *)(size_t)LPC178X_TIMER::c_TimerBase_2;
        else
            return *(LPC178X_TIMER  *)(size_t)LPC178X_TIMER::c_TimerBase_3;
    }


    static LPC178X_USART  & UART( int sel )
    {
        ASSERT(sel <=LPC178X_USART::c_MaxUart_no)
        if (sel == LPC178X_USART::c_Uart_0)
             return *(LPC178X_USART  *)(size_t)LPC178X_USART::c_UartBase_0;
        else if (sel == LPC178X_USART::c_Uart_1)
             return *(LPC178X_USART  *)(size_t)LPC178X_USART::c_UartBase_1;
        else if (sel == LPC178X_USART::c_Uart_2)
             return *(LPC178X_USART  *)(size_t)LPC178X_USART::c_UartBase_2;
        else
             return *(LPC178X_USART  *)(size_t)LPC178X_USART::c_UartBase_3;
    }
//--//
};

//////////////////////////////////////////////////////////////////////////////

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// SPI  driver
//

struct LPC178X_SPI_Driver
{
    BOOL m_Enabled[LPC178X_SPI::c_MAX_SPI];

    static BOOL Initialize  ();
    static void Uninitialize();

    static void GetPins         ( UINT32 spi_mod, GPIO_PIN& msk, GPIO_PIN& miso, GPIO_PIN& mosi );

    static BOOL nWrite16_nRead16( const SPI_CONFIGURATION& Configuration, UINT16* Write16, INT32 WriteCount, UINT16* Read16, INT32 ReadCount, INT32 ReadStartOffset );
    static BOOL nWrite8_nRead8  ( const SPI_CONFIGURATION& Configuration, UINT8*  Write8 , INT32 WriteCount, UINT8*  Read8 , INT32 ReadCount, INT32 ReadStartOffset );

    static BOOL Xaction_Start( const SPI_CONFIGURATION& Configuration );
    static BOOL Xaction_Stop ( const SPI_CONFIGURATION& Configuration );

    static BOOL Xaction_nWrite16_nRead16( SPI_XACTION_16& Transaction );
    static BOOL Xaction_nWrite8_nRead8  ( SPI_XACTION_8&  Transaction );

private:
    static void ISR( void* Param );
    static void SetClock(LPC178X_SPI &spi, UINT32 clock);
};

extern LPC178X_SPI_Driver g_LPC178X_SPI_Driver;

//
// SPI driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// I2C driver
//

struct I2C_HAL_XACTION_UNIT;
struct I2C_HAL_XACTION;
struct I2C_CONFIGURATION;

struct LPC178X_I2C_Driver
{
    I2C_HAL_XACTION*       m_currentXAction;
    I2C_HAL_XACTION_UNIT*  m_currentXActionUnit;

    //--//

    static const UINT8 c_DirectionWrite = 0x00;
    static const UINT8 c_DirectionRead  = 0x01;

    //--//

    static BOOL  Initialize         (                                              );
    static BOOL  Uninitialize       (                                              );
    static void  MasterXAction_Start( I2C_HAL_XACTION* xAction, bool repeatedStart );
    static void  MasterXAction_Stop (                                              );
    static UINT8 GetClockRate       ( UINT32 rateKhz                               );
    static void  GetPins            ( GPIO_PIN& scl, GPIO_PIN& sda                 );

private:
    static void WriteToSubordinate ( I2C_HAL_XACTION_UNIT* xAction );
    static void ReadFromSubordinate( I2C_HAL_XACTION_UNIT* xAction );
    static void ISR                ( void*            arg          );

    static I2C_CONFIGURATION& GetConfig();
};

extern LPC178X_I2C_Driver g_LPC178X_I2C_Driver;

//
// I2C driver
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// TIMER driver
//

struct LPC178X_TIMER_Driver
{
    const static UINT32 c_MaxTimers = 4;

    //--//

    BOOL m_configured[c_MaxTimers];

    static BOOL   Initialize   ( UINT32 Timer, HAL_CALLBACK_FPN ISR, void* ISR_Param );
    static BOOL   Uninitialize ( UINT32 Timer                                                                                              );
    static UINT32 ReadCounter  ( UINT32 Timer                                                                                              );

    static void EnableCompareInterrupt( UINT32 Timer )
    {
        ASSERT(Timer < c_MaxTimers);

        LPC178X_TIMER& TIMER = LPC178X::TIMER( Timer );

        TIMER.MCR |= LPC178X_TIMER::MR0_IRQEN;
    }

    static void DisableCompareInterrupt( UINT32 Timer )
    {
        ASSERT(Timer < c_MaxTimers);

        LPC178X_TIMER& TIMER = LPC178X::TIMER( Timer );

        TIMER.MCR &= ~LPC178X_TIMER::MR0_IRQEN;
    }

    static void ForceInterrupt( UINT32 Timer )
    {
        ASSERT(Timer < c_MaxTimers);

        NVIC->STIR = LPC178X_TIMER::getIntNo(Timer);
//        LPC178X::VIC().ForceInterrupt( LPC178X_TIMER::getIntNo(Timer) );
    }

    static void SetCompare( UINT32 Timer, UINT32 Compare )
    {
        ASSERT(Timer < c_MaxTimers);

        LPC178X_TIMER& TIMER = LPC178X::TIMER( Timer );

        TIMER.MR0 = Compare;
    }

    static BOOL DidCompareHit( UINT32 Timer )
    {
        ASSERT(Timer < c_MaxTimers);

        LPC178X_TIMER& TIMER = LPC178X::TIMER( Timer );

        return (TIMER.IR & LPC178X_TIMER::MR0_COMP) != 0;
    }

    static void ResetCompareHit( UINT32 Timer )
    {
        ASSERT(Timer < c_MaxTimers);

        LPC178X_TIMER& TIMER = LPC178X::TIMER( Timer );

        TIMER.IR = LPC178X_TIMER::MR0_RESET;
    }
};

extern LPC178X_TIMER_Driver g_LPC178X_TIMER_Driver;

//
// TIMER driver
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// GPIO driver
//

struct LPC178X_GPIO_Driver
{

    struct PIN_ISR_DESCRIPTOR
    {
        HAL_COMPLETION                 m_completion;
        GPIO_INTERRUPT_SERVICE_ROUTINE m_isr;
        void*                          m_param;
        GPIO_PIN                       m_pin;
        GPIO_INT_EDGE                  m_intEdge;
        UINT8                          m_flags;
        UINT8                          m_status;
        UINT32                        m_lastExecTicks;

        //--//

        static const UINT8 c_Flags_Debounce        = 0x01;

        // we are not using these

        /*static const UINT8 c_Flags_RequireLowEdge  = 0x02;
        static const UINT8 c_Flags_RequireHighEdge = 0x04;

        static const UINT8 c_Status_AllowLowEdge   = 0x01;
        static const UINT8 c_Status_AllowHighEdge  = 0x02;*/

        //--//

        static void Fire( void* arg );

        void HandleDebounce( BOOL edge );
    };

    //--//

    static const UINT32 c_MaxPins           =  160;
    static const UINT32 c_MaxPorts          =   5;
    static const UINT32 c_PinsPerPort       =  32;
    static const UINT32 c_PinsPerPCBReg     =  16;

    static const INT32  c_MinDebounceTimeMs =    1; // 1 ms
    static const INT32  c_MaxDebounceTimeMs = 5000; // 5  s

    //--//

    static const UINT8 c_Gpio_Attributes[c_MaxPins];

    // applies to all GPIO
    static const UINT8 c_NumberofResistorMode = 3;
    static const UINT8 c_GPIO_ResistorMode  = (1<<RESISTOR_DISABLED) |(1<<RESISTOR_PULLDOWN) | (1<<RESISTOR_PULLUP) ;

    static const UINT8 c_NumberofInterruptMode = 5;
    static const UINT8 c_GPIO_InterruptMode = (1<<GPIO_INT_EDGE_LOW) | (1<<GPIO_INT_EDGE_HIGH ) | (1<<GPIO_INT_EDGE_BOTH) | (1<<GPIO_INT_LEVEL_HIGH) | (1<<GPIO_INT_LEVEL_LOW);



    PIN_ISR_DESCRIPTOR m_PinIsr            [c_MaxPins ];
    UINT32             m_PinReservationInfo[c_MaxPins];
    UINT32             m_DebounceTicks;

    //--//

    static BOOL Initialize  ();

    static BOOL Uninitialize();

    static UINT32 Attributes( GPIO_PIN Pin );

    static void DisablePin( GPIO_PIN Pin, GPIO_RESISTOR ResistorState, UINT32 Direction, GPIO_ALT_MODE AltFunction);

    static void EnableOutputPin( GPIO_PIN Pin, BOOL InitialState );

    static BOOL EnableInputPin( GPIO_PIN Pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, void* ISR_Param, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState );

    static BOOL GetPinState( GPIO_PIN Pin );

    static void SetPinState( GPIO_PIN Pin, BOOL PinState );

    static void ISR( void* Param );

    static void SetResistor( GPIO_PIN Pin, GPIO_RESISTOR ResistorState );

    static BOOL PinIsBusy( GPIO_PIN Pin );

    static BOOL ReservePin( GPIO_PIN Pin, BOOL fReserve );

    static UINT32 GetDebounce();

    static BOOL SetDebounce( INT64 debounceTimeMilliseconds );

    static INT32 GetPinCount();

    static void GetPinsMap( UINT8* pins, size_t size );

    static UINT8 GetSupportedResistorModes( GPIO_PIN pin );

    static UINT8 GetSupportedInterruptModes( GPIO_PIN pin );

    static void GPIO_ISR( void* Param );

/*    static void PortConfiguration( UINT32 Port, UINT32 ConfigValue );

    static void PortDirection( UINT32 Port, UINT32 DirValue );

    static UINT32 GetPinBynIRQ( UINT32 nIRQ );

    static UINT32 GetnIRQByPin( UINT32 Pin );

    static BOOL   SetnIRQISR  ( GPIO_PIN pin, HAL_CALLBACK_FPN ISR, GPIO_INT_EDGE intEdge, GPIO_RESISTOR resistorState ) ;*/

private:

    static UINT32 PinToPort( GPIO_PIN pin )
    {
        ASSERT(pin < c_MaxPins);

        return pin / c_PinsPerPort;
    }

    static UINT32 PinToBit( GPIO_PIN pin )
    {
        ASSERT(pin < c_MaxPins);

        return pin % c_PinsPerPort;
    }

    static UINT32 PinToPCBReg( GPIO_PIN pin )
    {
        ASSERT(pin < c_MaxPins);

        return pin / c_PinsPerPCBReg;
    }

    static UINT32 PinToPCBRegBit( GPIO_PIN pin )
    {
        ASSERT(pin < c_MaxPins);

        return ((pin % c_PinsPerPCBReg) * 2);
    }

    static void STUB_ISRVector( GPIO_PIN Pin, BOOL PinState, void* Param );

    //static void nIRQ_ISR( void* Param );
};

extern LPC178X_GPIO_Driver g_LPC178X_GPIO_Driver;

//
// GP I/O driver
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// NVIC driver
//

// gets the address of the given vector index
#define GET_VECTOR(irqn) *((uint32_t *) &ARM_Vectors + irqn)

// cortex interupts are between -16 and n
#define INTC_TO_NVIC(x) ( (IRQn_Type) (x - 16) )
#define NVIC_TO_INTC(x) ( (UINT32)((int)x + 16) )

struct LPC178X_NVIC_Driver
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

extern LPC178X_NVIC_Driver g_LPC178X_NVIC_Driver;

//
// NVIC driver
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// UART driver
//

struct LPC178X_USART_Driver
{
    static const UINT32 c_RefFlagRx = 0x01;
    static const UINT32 c_RefFlagTx = 0x02;

    static const UINT32 c_COM1      = 0;
    static const UINT32 c_COM2      = 1;
    static const UINT32 c_COM3      = 2;
    static const UINT32 c_COM4      = 3;


    INT8 m_RefFlags[2];


    static BOOL Initialize                        ( int ComPortNum, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue );
    static BOOL Uninitialize                      ( int ComPortNum               );
    static BOOL TxBufferEmpty                     ( int ComPortNum               );
    static BOOL TxShiftRegisterEmpty              ( int ComPortNum               );
    static void WriteCharToTxBuffer               ( int ComPortNum, UINT8 c      );
    static void TxBufferEmptyInterruptEnable      ( int ComPortNum, BOOL Enable  );
    static BOOL TxBufferEmptyInterruptState       ( int ComPortNum               );
    static void RxBufferFullInterruptEnable       ( int ComPortNum, BOOL Enable  );
    static BOOL RxBufferFullInterruptState        ( int ComPortNum               );
    static BOOL TxHandshakeEnabledState           ( int comPortNum               );
    static void ProtectPins                       ( int ComPortNum, BOOL On      );
    static void GetPins                           (int comPort,  GPIO_PIN& rxPin, GPIO_PIN& txPin,GPIO_PIN& ctsPin, GPIO_PIN& rtsPin );
    static void BaudrateBoundary                  (int ComPortNum, UINT32& maxBaudrateHz, UINT32& minBaudrateHz);
    static BOOL IsBaudrateSupported               (int ComPortNum, UINT32 & BaudrateHz);

private:
    static void UART_IntHandler                   ( void *     Param             );
    static BOOL IsValidPortNum                    ( int ComPortNum               );
};

extern LPC178X_USART_Driver g_LPC178X_USART_Driver;

//
// UART driver
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// System Time driver
//

struct LPC178X_TIME_Driver
{
    static const UINT32 c_OverflowCheck = 0x80000000;

    UINT64 m_lastRead;
    UINT64 m_nextCompare;

    static BOOL Initialize  ();
    static BOOL Uninitialize();

    static UINT64 CounterValue();

    static void SetCompareValue( UINT64 CompareValue );

    static INT64 TicksToTime( UINT64 Ticks );

    static INT64 CurrentTime();

    static void Sleep_uSec( UINT32 uSec );

    static void Sleep_uSec_Loop( UINT32 uSec );

private:
    static void ISR( void* Param );
};

extern LPC178X_TIME_Driver g_LPC178X_TIME_Driver;

//
// System Time driver
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// LPC178X driver
//

struct LPC178X_Driver
{
    static const UINT32 c_SystemTime_Timer         = LPC178X_TIMER::c_Timer_0;

    BOOL             m_PowerOnReset;

    //--//

    static BOOL Initialize();

    static void Pause();

    static void Sleep();

    static void Halt();

    static void Reset();

    static void Shutdown();

    static void Hibernate();

    static BOOL PowerOnReset();

    static BOOL PowerOnReset_STUB();

    static void DisplayProcessorInformation();
};

extern LPC178X_Driver g_LPC178X_Driver;

//
// LPC178X driver
//////////////////////////////////////////////////////////////////////////////


#endif  // __LPC1788_DEVICES_H__
