////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
// Portions Copyright (c) David Dunscombe
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal_types.h>
#include "..\Platform\MK60N512MD100.h"
#include "..\Platform\core_cm4.h"

enum clk_option
{
    PLL50, PLL100, PLL96, PLL48
};

#define CORE_CLK_MHZ       PLL96 

int core_clk_mhz;

#pragma arm section code = "SectionForFlashOperations"

#if defined(__GNUC__)
#define __section(x) __attribute__((section(#x)))
#else
#define __section(x)
#endif

void __section(SectionForFlashOperations) set_sys_dividers(UINT32 outdiv1, UINT32 outdiv2, UINT32 outdiv3,
        UINT32 outdiv4)
{
    UINT32 temp_reg;
    UINT8 i;

    // get bus faults if we don't do this...
    FMC->PFB0CR &= ~(FMC_PFB0CR_B0IPE_MASK | FMC_PFB0CR_B0ICE_MASK | FMC_PFB0CR_B0DCE_MASK);
    FMC->PFB1CR &= ~(FMC_PFB1CR_B1IPE_MASK | FMC_PFB1CR_B1ICE_MASK | FMC_PFB1CR_B1DCE_MASK);

    // we need to disable prefetch while clock is setup - see errata E2448
    temp_reg = FMC->PFAPR;

    // set M0PFD through M7PFD to 1 to disable prefetch
    FMC->PFAPR |= FMC_PFAPR_M7PFD_MASK | FMC_PFAPR_M6PFD_MASK | FMC_PFAPR_M5PFD_MASK | FMC_PFAPR_M4PFD_MASK
            | FMC_PFAPR_M3PFD_MASK | FMC_PFAPR_M2PFD_MASK | FMC_PFAPR_M1PFD_MASK | FMC_PFAPR_M0PFD_MASK;

    // set clock dividers to desired value
    SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(outdiv1) | SIM_CLKDIV1_OUTDIV2(outdiv2) | SIM_CLKDIV1_OUTDIV3(outdiv3)
            | SIM_CLKDIV1_OUTDIV4(outdiv4);

    // wait for dividers to change
    for (i = 0; i < outdiv4; i++)
    {
    }

    // re-store original value of FMC_PFAPR
    FMC->PFAPR = temp_reg;

    return;
} //

unsigned char __section(SectionForFlashOperations) pll_init(unsigned char clk_option)
{
    unsigned char pll_freq;

    // return 0 if one of the available options is not selected
    if (clk_option > 3)
    {
        return 0;
    }

    // This assumes that the MCG is in default FEI mode out of reset.
    // First move to FBE mode
    MCG->C2 = 0;

    // after initialization of oscillator release latched state of oscillator and GPIO
    SIM->SCGC4 |= SIM_SCGC4_LLWU_MASK;
    LLWU->CS |= LLWU_CS_ACKISO_MASK;

    // Select external oscilator and Reference Divider and clear IREFS to start ext osc
    // CLKS=2, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
    MCG->C1 = MCG_C1_CLKS(2) | MCG_C1_FRDIV(3);

    while (MCG->S & MCG_S_IREFST_MASK)
    {
    }; // wait for Reference clock Status bit to clear

    while (((MCG->S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x2)
    {
    }; // Wait for clock status bits to show clock source is ext ref clk

    // Now in FBE
    MCG->C5 = MCG_C5_PRDIV(0x18);

    // Ensure MCG_C6 is at the reset default of 0. LOLIE disabled, PLL disabled, clk monitor disabled, PLL VCO divider is clear
    MCG->C6 = 0x0;

    // Select the PLL VCO divider and system clock dividers depending on clocking option
    switch (clk_option)
    {
    case 0:
        // Set system options dividers
        // MCG=PLL, core = MCG, bus = MCG, FlexBus = MCG, Flash clock= MCG/2
        set_sys_dividers(0, 0, 0, 1);
        // Set the VCO divider and enable the PLL for 50MHz, LOLIE=0, PLLS=1, CME=0, VDIV=1
        // VDIV = 1 (x25)
        MCG->C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(1);
        pll_freq = 50;
        break;
    case 1:
        // Set system options dividers
        // MCG=PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/4
        set_sys_dividers(0, 1, 1, 3);
        // Set the VCO divider and enable the PLL for 100MHz, LOLIE=0, PLLS=1, CME=0, VDIV=26
        // VDIV = 26 (x50)
        MCG->C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(26);
        pll_freq = 100;
        break;
    case 2:
        // Set system options dividers
        // MCG=PLL, core = MCG, bus = MCG/2, FlexBus = MCG/2, Flash clock= MCG/4
        set_sys_dividers(0, 1, 1, 3);
        // Set the VCO divider and enable the PLL for 96MHz, LOLIE=0, PLLS=1, CME=0, VDIV=24
        // VDIV = 24 (x48)
        MCG->C6 = MCG_C6_PLLS_MASK | MCG_C6_VDIV(24);
        pll_freq = 96;
        break;
    case 3:
        // Set system options dividers
        // MCG=PLL, core = MCG, bus = MCG, FlexBus = MCG, Flash clock= MCG/2
        set_sys_dividers(0, 0, 0, 1);
        // Set the VCO divider and enable the PLL for 48MHz, LOLIE=0, PLLS=1, CME=0, VDIV=0
        // VDIV = 0 (x24)
        MCG->C6 = MCG_C6_PLLS_MASK;
        pll_freq = 48;
        break;
    }

    // wait for PLL status bit to set
    while (!(MCG->S & MCG_S_PLLST_MASK))
    {
    };

    // Wait for LOCK bit to set
    while (!(MCG->S & MCG_S_LOCK_MASK))
    {
    };

    // Now running PBE Mode

    // Transition into PEE by setting CLKS to 0
    // CLKS=0, FRDIV=3, IREFS=0, IRCLKEN=0, IREFSTEN=0
    MCG->C1 &= ~MCG_C1_CLKS_MASK;

    // Wait for clock status bits to update
    while (((MCG->S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) != 0x3)
    {
    };

    // Now running PEE Mode

    return pll_freq;
}

void __section(SectionForFlashOperations) SystemInit(void)
{
    // initialise clock
    core_clk_mhz = pll_init(CORE_CLK_MHZ);

    // enable the port clocks
    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK
            | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_TSI_MASK);

    // make sure jtag is enabled
    PORTA->PCR[0] = ((PORTA->PCR[0] & ~PORT_PCR_ISF_MASK) | PORT_PCR_MUX_MASK);
    PORTA->PCR[1] = ((PORTA->PCR[1] & ~PORT_PCR_ISF_MASK) | PORT_PCR_MUX_MASK);
    PORTA->PCR[2] = ((PORTA->PCR[2] & ~PORT_PCR_ISF_MASK) | PORT_PCR_MUX_MASK);
    PORTA->PCR[3] = ((PORTA->PCR[3] & ~PORT_PCR_ISF_MASK) | PORT_PCR_MUX_MASK);
    PORTA->PCR[4] = ((PORTA->PCR[4] & ~PORT_PCR_ISF_MASK) | PORT_PCR_MUX_MASK);
    PORTA->PCR[5] = ((PORTA->PCR[5] & ~PORT_PCR_ISF_MASK) | PORT_PCR_MUX_MASK);

    // Set reset pin filter
    SIM->SOPT6 = 0x00UL;

    // do a reset when voltage low
    PMC->LVDSC1 = ((PMC->LVDSC1 & ~(PMC_LVDSC1_LVDIE_MASK | PMC_LVDSC1_LVDV_MASK)) | PMC_LVDSC1_LVDACK_MASK
            | PMC_LVDSC1_LVDRE_MASK);

    // clear any existing errors
    PMC->LVDSC2 = (UINT8) ((PMC->LVDSC2 & ~(PMC_LVDSC2_LVWIE_MASK | PMC_LVDSC2_LVWV_MASK)) | PMC_LVDSC2_LVWACK_MASK);
}

#pragma arm section code 

#pragma arm section code = "SectionForBootstrapOperations"

void __section(SectionForBootstrapOperations) DisableWatchdog()
{
    // Write 0xC520 to the unlock register
    WDOG->UNLOCK = 0xC520;
    // Followed by 0xD928 to complete the unlock
    WDOG->UNLOCK = 0xD928;
    // Clear the WDOGEN bit to disable the watchdog
    WDOG->STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
}

void __section(SectionForBootstrapOperations) BootstrapCode()
{
    // disable the watchdog
    DisableWatchdog();

    // init RAM constants
    PrepareImageRegions();

    // init clocks
    SystemInit();
}

#pragma arm section code 

