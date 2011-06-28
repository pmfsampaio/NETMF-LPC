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
#include <DeviceCode\LPC24XX.h>
	
#pragma arm section code = "SectionForBootstrapOperations"

#if defined(COMPILE_ARM) || defined(COMPILE_THUMB)
FORCEINLINE void __section(SectionForBootstrapOperations) Bootstrap_Delay( INT32 count )
{
#ifdef __GNUC__
    asm("1: subs %0, %0, #4\nbgt 1b" :: "r" (count));
#else
    __asm
    {
Loop:
        subs    count, count, #4
        bgt     Loop
    }
#endif
}
#elif defined(COMPILE_THUMB2)
FORCEINLINE void __section(SectionForBootstrapOperations) Bootstrap_Delay( INT32 count )
{
    // TODO: WRITE THUMB2 code
}
#endif


void __section(SectionForBootstrapOperations) delayMs(UINT32 timer_num, UINT32 delayInMs)
{

  LPC24XX_TIMER& TIMER = LPC24XX::TIMER( timer_num );

	TIMER.TCR = 0x02;		/* reset timer */
	TIMER.PR  = 0x00;		/* set prescaler to zero */
	TIMER.MR0 = delayInMs * (SYSTEM_CLOCK_HZ / 1000-1);
	TIMER.IR  = 0xff;		/* reset all interrrupts */
	TIMER.MCR = 0x04;		/* stop timer on match */
	TIMER.TCR = LPC24XX_TIMER::TCR_TEN;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (TIMER.TCR & LPC24XX_TIMER::TCR_TEN)
  {
  }
	TIMER.TCR = 0x02;		/* reset timer */
	TIMER.MCR = 0x00;		/* Clear MCR */
  return;
}

#define XTALFREQ	12000000
UINT32 __section(SectionForBootstrapOperations) GetFsclk(void) {
	UINT32 mul, div, fsclk;

	mul = (LPC24XX::SYSCON().PLLSTAT & 0x00007FFF)+1;
	div = ((LPC24XX::SYSCON().PLLSTAT & 0x00FF0000) >> 16)+1;
	// Calculate system frequency
	fsclk = XTALFREQ * mul * 2;
	fsclk /= div * (LPC24XX::SYSCON().CCLKCFG + 1);
	return fsclk;
}

UINT32 __section(SectionForBootstrapOperations) GetFpclk(unsigned int periphery)
{
	UINT32 fpclk;

	UINT32 vreg = (periphery < 32) ? LPC24XX::SYSCON().PCLKSEL0
			: LPC24XX::SYSCON().PCLKSEL1;

	periphery &= 0x1F;
	fpclk = GetFsclk();
	// find peripheral appropriate periphery divider
	switch ((vreg >> periphery) & 3) {
	case 0:
		fpclk /= 4;
		break;
	case 1:
		break;
	case 2:
		fpclk /= 2;
		break;
	default:
		fpclk /= 8;
	}
	return fpclk;
}


void __section(SectionForBootstrapOperations) BootstrapCode_Clocks()
{
    
    // Disconnect the PLL if already connected
    if ((LPC24XX::SYSCON().PLLSTAT & LPC24XX_SYSCON::CNCTD ))
    {
        LPC24XX::SYSCON().PLLCON  = LPC24XX_SYSCON::PLLE;
        LPC24XX::SYSCON().PLLFEED = 0xAA;
        LPC24XX::SYSCON().PLLFEED = 0x55;
    }
    
    // Disable the PLL
    LPC24XX::SYSCON().PLLCON  = 0x0;
    LPC24XX::SYSCON().PLLFEED = 0xAA;
    LPC24XX::SYSCON().PLLFEED = 0x55;
    
    // Enable the Oscillator and wait for it to be stable
    LPC24XX::SYSCON().SCS = (LPC24XX::SYSCON().SCS | LPC24XX_SYSCON::OSCEN);
    while ( ((LPC24XX::SYSCON().SCS & LPC24XX_SYSCON::READY) == 0) )
    {
    }
    
    // Select Main Oscillator as the PLL clock source
    LPC24XX::SYSCON().CLKSRCSEL = LPC24XX_SYSCON::OSC;
    
    // See platform_plak1a_LPC2478_selector.h
    LPC24XX::SYSCON().PLLCFG  = (((PLL_NVAL-1) << 16) | (PLL_MVAL-1));
    LPC24XX::SYSCON().PLLCON  = LPC24XX_SYSCON::PLLE;
    LPC24XX::SYSCON().PLLFEED = 0xAA;
    LPC24XX::SYSCON().PLLFEED = 0x55;
   
    // Wait while PLL locks
    while ( (LPC24XX::SYSCON().PLLSTAT & LPC24XX_SYSCON::LOCKD) == 0x0 )
    {
    }
    
    // Enable MAM
    LPC24XX::SYSCON().MAMTIM = 3;
    LPC24XX::SYSCON().MAMCR = 2;

    // Set CCLK and USB clock divider
    LPC24XX::SYSCON().CCLKCFG = (CCLK_DIVIDER-1);
    LPC24XX::SYSCON().USBCLKCFG = (USB_DIVIDER-1);
    
    // PLL locked now connect it
    LPC24XX::SYSCON().PLLCON = (LPC24XX_SYSCON::PLLC | LPC24XX_SYSCON::PLLE);
    LPC24XX::SYSCON().PLLFEED = 0xAA;
    LPC24XX::SYSCON().PLLFEED = 0x55;
    
    // Enable UART2
    LPC24XX::SYSCON().PCONP |= (1<<24);

    LPC24XX::SYSCON().PCLKSEL0 = 0;
    LPC24XX::SYSCON().PCLKSEL1 = (0x1 << 16);



}

//should be unused in the LPC24XX, I'm leaving it here as a possible reference
void __section(SectionForBootstrapOperations) BootstrapCode_Ext_SRAM()
{

// BCFG1 Register Configuration Value:  0x20000C21
// IDCY   :  1  ->  2 idle cycles
// WST1   :  1  ->  4 CCLK cycles
// RBLE   :  1  ->  Memory Bank composed of two 16 bit devices
// WST2   :  1  ->  4 CCLK cycles
// BUSERR :  0  ->  not relevant
// WPERR  :  0  ->  no write protection error
// WP     :  0  ->  bank not write protected
// BM     :  0  ->  no burst rom bank
// MW     :  2  ->  32-bit wide bus
// AT     :  0  ->  always write 0 to this field

//THIS WAS THE ONLY UNCOMMENTED LINE IN LPC22XX function:   LPC22XX::EMC().BCFG1=0x20000C21;   

}

void __section(SectionForBootstrapOperations) BootstrapCode_Ext_Flash()
{
    // NOR Flash
    LPC24XX::EMC().SWAITWEN0 = 0;//0x2; // 0x2
    LPC24XX::EMC().SWAITOEN0 = 0;//0x2; // 0x2
    LPC24XX::EMC().SWAITRD0 = 5;//0x6;  // 0x1f
    LPC24XX::EMC().SWAITPAGE0 = 0x1f;//0x7;
    LPC24XX::EMC().SWAITWR0 = 4;//0x6; //0x1f
    LPC24XX::EMC().SWAITTURN0 = 1;//0x3;//0xf
    LPC24XX::EMC().SCONFIG0 = (0x1 << 7 ) | 0x1; //0x00000081;

    // NAND Flash
//    LPC24XX::EMC().SWAITWEN1 = 0x2;
//    LPC24XX::EMC().SWAITOEN1 = 0x2;
//    LPC24XX::EMC().SWAITRD1 = 0x8;
//    LPC24XX::EMC().SWAITPAGE1 = 0x1f;
//    LPC24XX::EMC().SWAITWR1 = 0x8;
//    LPC24XX::EMC().SWAITTURN1 = 0xf;
//    LPC24XX::EMC().SCONFIG1 = 0x00000080;
}

void __section(SectionForBootstrapOperations) BootstrapCode_Pins()
{
    // Connect SDRAM and Flash memory pins
    
    // CS3 and CS4 
//    LPC24XX::PCB().Regs[5].PINSEL = 0x55010115;//0x50000000;
    
    // CAS, RAS, CLKOUT0, DYCS0. CKEOUT0 and DQMOUT0/1/2/3
    LPC24XX::PCB().Regs[5].PINSEL = 0x55010115;
    LPC24XX::PCB().Regsm[5].PINMODE = 0xAA02022A;
    
    // D0 - D15
    LPC24XX::PCB().Regs[6].PINSEL = 0x55555555;
    LPC24XX::PCB().Regsm[6].PINMODE = 0xAAAAAAAA;
    
    // D16 - D31
    LPC24XX::PCB().Regs[7].PINSEL = 0x55555555;
    LPC24XX::PCB().Regsm[7].PINMODE = 0xAAAAAAAA;

    
    // A0 - A15
    LPC24XX::PCB().Regs[8].PINSEL = 0x55555555;
    LPC24XX::PCB().Regsm[8].PINMODE = 0xAAAAAAAA;

//    LPC24XX::PCB().Regs[8].PINSEL &= 0xC0000000;//0x50555555;
//    LPC24XX::PCB().Regs[8].PINSEL |= 0x15555555;//0x50555555;

//    LPC24XX::PCB().Regsm[8].PINMODE &= 0xC0000000;
//    LPC24XX::PCB().Regsm[8].PINMODE = 0x2AAAAAAA;


    // A16 - A23, OE, WE, BLS1/2 and CS0/1
    // CS1 CS0 BS3 BS2 BS1 BS0 WE OE A23 A22 A21 A20 A19 A18 A17 A16
    // 01  01  10  10  00  00  01 01 00  01  01  01  01  01  01  01
    //    5       a      0       5      1       5       5      5

    LPC24XX::PCB().Regs[9].PINSEL = 0x5a051555;//0x40051400;//0x50555555;
    LPC24XX::PCB().Regsm[9].PINMODE = 0xAAAAAAAA;//0x800A2800;

//    LPC24XX::PCB().Regs[9].PINSEL &= 0x3FF0C3FF;//0x50555555;
//    LPC24XX::PCB().Regs[9].PINSEL |= 0x40051400;//0x50555555;

//    LPC24XX::PCB().Regsm[9].PINMODE &= 0x3FF0C3FF;
//    LPC24XX::PCB().Regsm[9].PINMODE |= 0x800A2800;

}

#define EMC_PERIOD          13.8  // 72MHz
#define P2C(Period)     (((Period<EMC_PERIOD)?0:(unsigned int)((float)Period/EMC_PERIOD))+1)

#define SDRAM_REFRESH         7813	//max 64ms
#define SDRAM_TRP             20	 //
#define SDRAM_TRAS            45
#define SDRAM_TAPR            1+1
#define SDRAM_TDAL  		 2+P2C(SDRAM_TRP)
#define SDRAM_TWR             2
#define SDRAM_TRC             65 //samsung 65 micron 66
#define SDRAM_TRFC            66
#define SDRAM_TXSR            1
#define SDRAM_TRRD            15
#define SDRAM_TMRD            2
void __section(SectionForBootstrapOperations) BootstrapCode_Ext_SDRAM()
{
    volatile UINT32 dummy;
    UINT32 i;
    
    LPC24XX::EMC().CONTROL = 0x00000001;
    // Enable EMC Clock
    LPC24XX::SYSCON().PCONP |= 0x00000800;

	// 32 Bit SDRAM Init
    LPC24XX::EMC().DRP = P2C(SDRAM_TRP);//1;
    LPC24XX::EMC().DRAS = P2C(SDRAM_TRAS);//3;
    LPC24XX::EMC().DSREX = SDRAM_TXSR; //5;
    LPC24XX::EMC().DAPR = SDRAM_TAPR; //1;
    LPC24XX::EMC().DDAL = SDRAM_TDAL; //5;
    LPC24XX::EMC().DWR = SDRAM_TWR; //1;
    LPC24XX::EMC().DRC = P2C(SDRAM_TRC); //5;
    LPC24XX::EMC().DRFC = P2C(SDRAM_TRFC); //5;
    LPC24XX::EMC().DXSR = SDRAM_TXSR; //5;
    LPC24XX::EMC().DRRD = P2C(SDRAM_TRRD); //1;
    LPC24XX::EMC().DMRD = SDRAM_TMRD; //1;
    LPC24XX::EMC().DREADCONFIG = 1;
    LPC24XX::EMC().DRASCAS0 = 0x00000303;
    LPC24XX::EMC().DCONFIG0 = (1u << 14) | (0u << 12) | (4u << 9) | (1u << 7); //0x00005480;

    // Delay 100 ms
//    delayMs(LPC24XX_TIMER::c_Timer_0,100);
    Bootstrap_Delay(5000);
    Bootstrap_Delay(5000);
    
    //NOP command
    LPC24XX::EMC().DCONTROL = 0x00000183;

    // Delay 200 ms
    //delayMs(LPC24XX_TIMER::c_Timer_0,200);
    Bootstrap_Delay(5000);

    
    //PRECHARGE-ALL command
    //LPC24XX::EMC().DCONTROL = 0x00000103;
    //LPC24XX::EMC().DREFRESH = 0x00000002;
    LPC24XX::EMC().DCONTROL |= 0x00000100;
    LPC24XX::EMC().DCONTROL &= 0xFFFFFF7F;
    LPC24XX::EMC().DREFRESH = 0x00000001;
    
    //wait for precharge
    for(i = 0; i < 0x40; i++)	// wait 128 AHB clock cycles
    {
    }
    
    //Set refresh period
    LPC24XX::EMC().DREFRESH = P2C(SDRAM_REFRESH) >> 4;//28;
     
    //Set Mode
    //LPC24XX::EMC().DCONTROL = 0x00000083;
    LPC24XX::EMC().DCONTROL |= 0x00000080;
    LPC24XX::EMC().DCONTROL &= 0xFFFFFEFF;

    dummy = *((volatile unsigned int*)(SRAM1_MEMORY_Base | (0x32 << 14)));

    //Set NORMAL mode
    LPC24XX::EMC().DCONTROL = 0x00000000;

    //Enable buffer
    LPC24XX::EMC().DCONFIG0 |= 0x00080000;

    // 1 ms delay
    //delayMs(LPC24XX_TIMER::c_Timer_0,1);
    Bootstrap_Delay(5000);
}

// map the InternalRAM  to address 0
void __section(SectionForBootstrapOperations) Initialize_SyncOn()
{
    LPC24XX::SYSCON().MEMMAP=0x2;
}

extern "C"
{
void __section(SectionForBootstrapOperations) platform_prestackinit()
{
    BootstrapCode_Clocks();
    BootstrapCode_Pins();
#if !defined(TARGETLOCATION_RAM)
    
    BootstrapCode_Ext_SDRAM();
#endif

    BootstrapCode_Ext_SRAM();
    BootstrapCode_Ext_Flash();
}
}

#pragma arm section code
