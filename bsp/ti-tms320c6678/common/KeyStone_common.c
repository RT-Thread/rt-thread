/******************************************************************************

  Copyright (C), 2001-2012, Texas Instrument.

 ******************************************************************************
  File Name     : KeyStone_common.c
  Version       : Initial Draft
  Author        : Brighton Feng
  Created       : 2010-12-12
  Last Modified : 
  Description   : KeyStone common miscellaneous functions and definitions
  History       :
  1.Date        : 2010-12-12
    Author      : Brighton Feng
    Modification: Created file

  2.Date         : 2012-10-6
    Author       : Brighton Feng
    Modification : Add memory protection and EDC configuration

  3.Date         : 2014-12-8
    Author       : Brighton Feng
    Modification : Add common device, CPU, interrupt initialization functions.
                   Print device information including device type, speed grade, 
                   boot mode, required voltage, ID��
                   Add EDMA enable/disable functions.
                   To support square wave generation by timer.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tistdtypes.h>
#include <csl_bootcfgAux.h>
#include <csl_pscAux.h>
#include <cslr_chip.h>
#include <csl_edma3.h>
#include "CSL_msmc.h"
#include "CSL_msmcAux.h"
#include "KeyStone_common.h"

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/
CSL_XmcRegs * gpXMC_regs = (CSL_XmcRegs *) CSL_XMC_CONFIG_REGS;
CSL_CgemRegs * gpCGEM_regs = (CSL_CgemRegs *)CSL_CGEM0_5_REG_BASE_ADDRESS_REGS;
CSL_BootcfgRegs * gpBootCfgRegs = (CSL_BootcfgRegs *)CSL_BOOT_CFG_REGS;
CSL_PllcRegs * gpPLLC_regs = (CSL_PllcRegs * )CSL_PLL_CONTROLLER_REGS;
CSL_PscRegs *  gpPSC_regs =   (CSL_PscRegs *)CSL_PSC_REGS;
CSL_MsmcRegs * gpMSMC_regs = (CSL_MsmcRegs *)CSL_MSMC_CONFIG_REGS;
CSL_GpioRegs * gpGPIO_regs= (CSL_GpioRegs * )CSL_GPIO_REGS;

CSL_CPINTCRegs* gpCIC0_regs = (CSL_CPINTCRegs*)CSL_CP_INTC_0_REGS;
CSL_CPINTCRegs* gpCIC1_regs = (CSL_CPINTCRegs*)CSL_CP_INTC_1_REGS;
/*The register pointer for the CIC routing events DSP core.
By default, it is CIC0; but for core 4~7 of C6678, it is CIC1*/
CSL_CPINTCRegs* gpCIC_regs= (CSL_CPINTCRegs*)CSL_CP_INTC_0_REGS;

CSL_TpccRegs*  gpEDMA_CC0_regs  = (CSL_TpccRegs*)CSL_EDMA0CC_REGS;
CSL_TpccRegs*  gpEDMA_CC1_regs  = (CSL_TpccRegs*)CSL_EDMA1CC_REGS;
CSL_TpccRegs*  gpEDMA_CC2_regs  = (CSL_TpccRegs*)CSL_EDMA2CC_REGS;
CSL_TpccRegs*  gpEDMA_CC_regs[3]  = {
	(CSL_TpccRegs*)CSL_EDMA0CC_REGS,
	(CSL_TpccRegs*)CSL_EDMA1CC_REGS,
	(CSL_TpccRegs*)CSL_EDMA2CC_REGS
};

CSL_TptcRegs * gpEDMA_TC_0_0_regs=(CSL_TptcRegs *) CSL_EDMA0TC0_REGS;
CSL_TptcRegs * gpEDMA_TC_0_1_regs=(CSL_TptcRegs *) CSL_EDMA0TC1_REGS;
CSL_TptcRegs * gpEDMA_TC_1_0_regs=(CSL_TptcRegs *) CSL_EDMA1TC0_REGS;
CSL_TptcRegs * gpEDMA_TC_1_1_regs=(CSL_TptcRegs *) CSL_EDMA1TC1_REGS;
CSL_TptcRegs * gpEDMA_TC_1_2_regs=(CSL_TptcRegs *) CSL_EDMA1TC2_REGS;
CSL_TptcRegs * gpEDMA_TC_1_3_regs=(CSL_TptcRegs *) CSL_EDMA1TC3_REGS;
CSL_TptcRegs * gpEDMA_TC_2_0_regs=(CSL_TptcRegs *) CSL_EDMA2TC0_REGS;
CSL_TptcRegs * gpEDMA_TC_2_1_regs=(CSL_TptcRegs *) CSL_EDMA2TC1_REGS;
CSL_TptcRegs * gpEDMA_TC_2_2_regs=(CSL_TptcRegs *) CSL_EDMA2TC2_REGS;
CSL_TptcRegs * gpEDMA_TC_2_3_regs=(CSL_TptcRegs *) CSL_EDMA2TC3_REGS;

CSL_TptcRegs * gpEDMA_TC_regs[10]= {
	(CSL_TptcRegs *) CSL_EDMA0TC0_REGS,
	(CSL_TptcRegs *) CSL_EDMA0TC1_REGS,
	(CSL_TptcRegs *) CSL_EDMA1TC0_REGS,
	(CSL_TptcRegs *) CSL_EDMA1TC1_REGS,
	(CSL_TptcRegs *) CSL_EDMA1TC2_REGS,
	(CSL_TptcRegs *) CSL_EDMA1TC3_REGS,
	(CSL_TptcRegs *) CSL_EDMA2TC0_REGS,
	(CSL_TptcRegs *) CSL_EDMA2TC1_REGS,
	(CSL_TptcRegs *) CSL_EDMA2TC2_REGS,
	(CSL_TptcRegs *) CSL_EDMA2TC3_REGS
};

CSL_TmrPlusRegs * gpTimer0Regs = (CSL_TmrPlusRegs *)CSL_TIMER_0_REGS;
CSL_TmrPlusRegs * gpTimer1Regs = (CSL_TmrPlusRegs *)CSL_TIMER_1_REGS;
CSL_TmrPlusRegs * gpTimer2Regs = (CSL_TmrPlusRegs *)CSL_TIMER_2_REGS;
CSL_TmrPlusRegs * gpTimer3Regs = (CSL_TmrPlusRegs *)CSL_TIMER_3_REGS;
CSL_TmrPlusRegs * gpTimer4Regs = (CSL_TmrPlusRegs *)CSL_TIMER_4_REGS;
CSL_TmrPlusRegs * gpTimer5Regs = (CSL_TmrPlusRegs *)CSL_TIMER_5_REGS;
CSL_TmrPlusRegs * gpTimer6Regs = (CSL_TmrPlusRegs *)CSL_TIMER_6_REGS;
CSL_TmrPlusRegs * gpTimer7Regs = (CSL_TmrPlusRegs *)CSL_TIMER_7_REGS;
CSL_TmrPlusRegs * gpTimer8Regs = (CSL_TmrPlusRegs *)(CSL_TIMER_7_REGS+(CSL_TIMER_7_REGS-CSL_TIMER_6_REGS));
CSL_TmrPlusRegs * gpTimerRegs[9] = {
	(CSL_TmrPlusRegs *)CSL_TIMER_0_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_1_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_2_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_3_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_4_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_5_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_6_REGS,
	(CSL_TmrPlusRegs *)CSL_TIMER_7_REGS,
	(CSL_TmrPlusRegs *)(CSL_TIMER_7_REGS+(CSL_TIMER_7_REGS-CSL_TIMER_6_REGS))
};

/*MPU for peripherals registers and data space*/
CSL_MpuRegs * gpMPU0_regs= (CSL_MpuRegs *)CSL_MPU_0_REGS;
CSL_MpuRegs * gpMPU1_regs= (CSL_MpuRegs *)CSL_MPU_1_REGS;
CSL_MpuRegs * gpMPU2_regs= (CSL_MpuRegs *)CSL_MPU_2_REGS;
CSL_MpuRegs * gpMPU3_regs= (CSL_MpuRegs *)CSL_MPU_3_REGS;

CSL_Emif4fRegs * gpDDR_regs= (CSL_Emif4fRegs *)CSL_DDR3_EMIF_CONFIG_REGS;
unsigned int gDSP_Core_Speed_Hz= 1000000000; 	//DSP core clock speed in Hz
TDSP_Board_Type gDSP_board_type= UNKNOWN;

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

/*****************************************************************************
 Prototype    : KeyStone_main_PLL_init
 Description  : DSP core PLL configuration
  	DSP core will be configured to run at ref_clock_MHz*multiplier/divisor
 Input        : float ref_clock_MHz     
                unsigned int multiplier: 1~4096  
                unsigned int divisor: 1~64  
 Output       : 
 Return Value : 
 
  History        :
  1.Date         : 2010-12-12
    Author       : Brighton Feng
    Modification : Created function
  2.Date         : May 19, 2013
    Author       : Brighton Feng
    Modification : update parameter check; replace constant with macro

*****************************************************************************/
void KeyStone_main_PLL_init (float ref_clock_MHz,
	unsigned int multiplier, unsigned int divisor)
{
	unsigned int i;

	if(0==divisor)
	{
		puts("Error: PLL input divider = 0");
		return;
	}

	if(64<divisor)
	{
		puts("Error: PLL input divider too large");
		return;
	}

	if(0==multiplier)
	{
		puts("Error: PLL multiplier = 0");
		return;
	}

	if(4096<multiplier)
	{
		puts("Error: PLL multiplier too large");
		return;
	}

	CSL_BootCfgUnlockKicker();

	gDSP_Core_Speed_Hz= ref_clock_MHz*1000000/divisor*multiplier;

	printf("Initialize DSP main clock = %.2fMHz/%dx%d = %dMHz\n", 
		ref_clock_MHz, divisor, multiplier, gDSP_Core_Speed_Hz/1000000);

	/*1. If executing this sequence immediately after device power-up, you must allow for*/
	/*the PLL to become stable. PLL stabilization time is 100 ��s.                       */
	for(i=0; i< 20000; i++)
		asm(" nop 5");

	/*2. Check the status of BYPASS bit in SECCTL register, execute following steps if   */
	/*BYPASS == 1 (if bypass enabled):                         */
	if(gpPLLC_regs->SECCTL & PLLCTL_BYPASS_MASK)
	{		
		/*a. In MAINPLLCTL1, write ENSAT = 1 (for optimal PLL operation)                     */
		gpBootCfgRegs->CORE_PLL_CTL1 |= PLLCTL1_ENSAT_MASK;      /*Set ENSAT bit = 1*/

		/*b. In PLLCTL, write PLLEN = 0 (bypass enabled in PLL controller mux)               */
		gpPLLC_regs->PLLCTL &= ~CSL_PLLC_PLLCTL_PLLEN_MASK;

		/*c. In PLLCTL, write PLLENSRC = 0 (enable PLLEN to control PLL controller mux       */
		gpPLLC_regs->PLLCTL &= ~CSL_PLLC_PLLCTL_PLLENSRC_MASK;

		/*d. Wait 4 cycles of the reference clock CLKIN (to make sure the PLL controller     */
		/*mux switches properly to the bypass)                                               */
		for(i=0; i< 4; i++)
			asm(" nop 5");

		/*e. In SECCTL, write BYPASS = 1 (bypass enabled in PLL mux)                         */
		gpPLLC_regs->SECCTL |= PLLCTL_BYPASS_MASK;

		/*f. In PLLCTL, write PLLPWRDN = 1 (power down the PLL)                              */
		gpPLLC_regs->PLLCTL |= CSL_PLLC_PLLCTL_PLLPWRDN_MASK;	//Power down the PLL

		/*g. Wait for at least 5 ��s based on the reference clock CLKIN (PLL power down      */
		/*toggling time)                                                                     */
		for(i=0; i< 1000; i++)
			asm(" nop 5");

		/*h. In PLLCTL, write PLLPWRDN = 0 (power up the PLL)                                */
		gpPLLC_regs->PLLCTL &= ~CSL_PLLC_PLLCTL_PLLPWRDN_MASK;         // Power up PLL
	}
	else
	{
		/*a. In PLLCTL, write PLLEN = 0 (bypass enabled in PLL controller mux)               */
		gpPLLC_regs->PLLCTL &= (~CSL_PLLC_PLLCTL_PLLEN_MASK);

		/*b. In PLLCTL, write PLLENSRC = 0 (enable PLLEN to control PLL controller mux       */
		gpPLLC_regs->PLLCTL &= (~CSL_PLLC_PLLCTL_PLLENSRC_MASK);

		/*c. Wait 4 cycles of the reference clock CLKIN (to make sure the PLL controller     */
		/*mux switches properly to the bypass)                                               */
		for(i=0; i< 4*multiplier/divisor; i++)
			asm(" nop 5");
	}

	/*4. PLLM is split in two different registers. Program PLLM[5:0] in PLL multiplier   */
	/*control register (PLLM) and PLLM[12:6] in MAINPLLCTL0 register                     */
	/*5. BWADJ is split in two different registers. Program BWADJ[7:0] in                */
	/*MAINPLLCTL0 and BWADJ[11:8] in MAINPLLCTL1 register. BWADJ value                   */
	/*must be set to ((PLLM + 1) >> 1) - 1)                                              */
	/*6. Program PLLD in MAINPLLCTL0 register                                            */
	gpBootCfgRegs->CORE_PLL_CTL0 = ((multiplier-1)<<PLLCTL0_BWADJ_SHIFT)|
		(((multiplier*2-1)&0x1FC0)<<PLLCTL0_PLLM_SHIFT)|(divisor-1);
	
	gpPLLC_regs->PLLM= (multiplier*2-1)&0x3F;
	gpBootCfgRegs->CORE_PLL_CTL1 &= ~PLLCTL1_BWADJ_MASK; 
	gpBootCfgRegs->CORE_PLL_CTL1 |= (multiplier-1)>>8;	/*BWADJ[11:8]*/

	/*7. In SECCTL, write OD (Output Divide) = 1 (that is divide-by-2)                   */
	gpPLLC_regs->SECCTL &= ~PLLCTL_OD_MASK;
	gpPLLC_regs->SECCTL |= 1<<PLLCTL_OD_SHIFT;
	
#if 0
	/*8. If necessary, program PLLDIVn. Note that you must apply the GO operation to     */
	/*change these dividers to a new ratios (see Section 3.2 ����Divider n (D1 to Dn) and*/
	/*GO Operation ���� on page 3-3).                                                    */
	/* Step 8a: Check that the GOSTAT bit in PLLSTAT is cleared to show that no GO
	operation is currently in progress*/
	while((gpPLLC_regs->PLLSTAT) & CSL_PLLC_PLLSTAT_GOSTAT_MASK);

	/* Step 8b: Program the RATIO field in PLLDIVn to the desired new divide-down rate.
	If RATIO field is changed, the PLL controller will flag the change in the
	corresponding bit of DCHANGE*/
	gpPLLC_regs->PLLDIV1_3[3-1] = (3-1) | CSL_PLLC_PLLDIV1_3_DNEN_MASK;  //Set PLLDIV3
	gpPLLC_regs->PLLDIV4_16[4-4] = (5-1) | CSL_PLLC_PLLDIV4_16_DNEN_MASK;  //Set PLLDIV4
	gpPLLC_regs->PLLDIV4_16[7-4] = (6-1) | CSL_PLLC_PLLDIV4_16_DNEN_MASK;  //Set PLLDIV7

	/* Step 8c: Set GOSET bit in PLLCMD to initiate the GO operation to change the divide
	values and align the SYSCLKs as programmed */
	gpPLLC_regs->PLLCMD |= CSL_PLLC_PLLCMD_GOSET_MASK;

	/*Step 8d/e: Read the GOSTAT bit in PLLSTAT to make sure the bit returns to 0 to
	indicate that the GO operation has completed */
	while((gpPLLC_regs->PLLSTAT) & CSL_PLLC_PLLSTAT_GOSTAT_MASK);
#endif

	/*9. In PLLCTL , write PLLRST = 1 (PLL reset is asserted)*/
	gpPLLC_regs->PLLCTL |= CSL_PLLC_PLLCTL_PLLRST_MASK;
	
	/*10. Wait for at least 7 ��s based on the reference clock CLKIN (PLL reset time)     */
	for(i=0; i< 2000; i++)
		asm(" nop 5");

	/*11. In PLLCTL, write PLLRST = 0 (PLL reset is released)                            */
	gpPLLC_regs->PLLCTL &= ~CSL_PLLC_PLLCTL_PLLRST_MASK;

	/*12. Wait for at least 2000 �� CLKIN cycles �� (PLLD + 1) (PLL lock time)            */
	for(i=0; i< 400*multiplier; i++)
		asm(" nop 5");

	/*13. In SECCTL, write BYPASS = 0 (enable PLL mux to switch to PLL mode)             */
	gpPLLC_regs->SECCTL &= ~PLLCTL_BYPASS_MASK;
	
	/*14. Set the PLLEN bit in PLLCTL to 1 to enable PLL mode*/
	gpPLLC_regs->PLLCTL |= CSL_PLLC_PLLCTL_PLLEN_MASK;

}
/*****************************************************************************
 Prototype    : KeyStone_PLL_init
 Description  : Config the PLL of PA and DDR
 	target clock speed will be ref_clock_MHz/inputDivisor*multiplier/outputDivisor
 Input        : unsigned int inputDivisor  
                unsigned int multiplier  
                unsigned int outputDivisor  
 Output       : None
 Return Value : 0 for success, other value for error
 
  History        :
  1.Date         : May 18, 2013
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
int KeyStone_PLL_init (PLL_ControlRegs * PLL_Regs, unsigned int inputDivisor, 
	unsigned int multiplier, unsigned int outputDivisor)
{
	if(0==inputDivisor)
	{
		puts("Error: PLL input divider = 0");
		return 1;
	}

	if(64<inputDivisor)
	{
		puts("Error: PLL input divider too large");
		return 2;
	}

	if(0==multiplier)
	{
		puts("Error: PLL multiplier = 0");
		return 3;
	}

	if(8192<multiplier)
	{
		puts("Error: PLL multiplier too large");
		return 4;
	}

	if(0==outputDivisor)
	{
		puts("Error: PLL output divider = 0");
		return 5;
	}

	if(16<outputDivisor)
	{
		puts("Error: PLL output divider too larger");
		return 6;
	}

	CSL_BootCfgUnlockKicker();

	/*1. In PLLCTL1, write ENSAT = 1 (for optimal PLL operation)*/
	PLL_Regs->PLL_CTL1 = PLLCTL1_ENSAT_MASK;

	/*2. In PLLCTL0, write BYPASS = 1 (set the PLL in Bypass)*/
	PLL_Regs->PLL_CTL0 |= PLLCTL_BYPASS_MASK;

	/*3. Program PLLM and PLLD in PLLCTL0 register*/
	/*4. Program BWADJ[7:0] in PLLCTL0 and BWADJ[11:8] in PLLCTL1 register. 
	BWADJ value must be set to ((PLLM + 1) >> 1) �C 1)*/
	PLL_Regs->PLL_CTL0 = ((multiplier/2-1)<<PLLCTL0_BWADJ_SHIFT)
		|((outputDivisor-1)<<PLLCTL_OD_SHIFT)
		|((multiplier-1)<<PLLCTL0_PLLM_SHIFT)
		|(inputDivisor-1);

	PLL_Regs->PLL_CTL1 &= ~PLLCTL1_BWADJ_MASK;
	PLL_Regs->PLL_CTL1 |= (multiplier/2-1)>>8; /*BWADJ[11:8]*/

	/*5. In PLLCTL1, write PLLRST = 1 (PLL is reset)*/
	PLL_Regs->PLL_CTL1 |= PLLCTL1_PLLRESET_MASK;      //Set RESET bit = 1

	/*6. Wait for at least 7 us based on the reference clock (PLL reset time)*/
	TSC_delay_us(7);

	/*For PASS, In PASSPLLCTL1, write PLLSELECT = 1 
	(for selecting the output of PA PLL as the input to PASS)*/
	if(PLL_Regs==(PLL_ControlRegs *)gpBootCfgRegs->PA_PLL_CTL0)
		PLL_Regs->PLL_CTL1 |= PLLCTL1_PAPLL_MASK;

	/*7. In PLLCTL1, write PLLRST = 0 (PLL reset is released)*/
	PLL_Regs->PLL_CTL1 &= ~PLLCTL1_PLLRESET_MASK;   //Clear RESET bit

	/*8. Wait for at least 500 * REFCLK cycles * (PLLD + 1) (PLL lock time)*/
	TSC_delay_us(500);

	/*9. In PLLCTL0, write BYPASS = 0 (switch to PLL mode)*/
	PLL_Regs->PLL_CTL0 &= ~PLLCTL_BYPASS_MASK ;

	return 0;
}
/*****************************************************************************
 Prototype    : KeyStone_PASS_PLL_init
 Description  : Config the PASS PLL
 	target clock speed will be ref_clock_MHz/divisor*multiplier
 Input        : float ref_clock_MHz
                unsigned int multiplier: 1~4096
                unsigned int divisor: 1~64
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2013-2-14
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_PASS_PLL_init (float ref_clock_MHz,
	unsigned int multiplier, unsigned int divisor)
{
	//output divisor for PASS PLL should be 2
	if(0==KeyStone_PLL_init((PLL_ControlRegs *)&gpBootCfgRegs->PA_PLL_CTL0, 
		divisor, multiplier*2, 2))
	{
		printf("Initialize PASS PLL clock = %.2fMHz/%dx%d = %.3fMHz\n", 
			ref_clock_MHz, divisor, multiplier, 
			ref_clock_MHz*multiplier/divisor);
	}
}

/*****************************************************************************
 Prototype    : KeyStone_DDR_PLL_init
 Description  : Config the DDR PLL
 	target clock speed will be ref_clock_MHz/divisor*multiplier
 Input        : float ref_clock_MHz
                unsigned int multiplier: 1~4096
                unsigned int divisor: 1~64
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2013-8-18
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_DDR_PLL_init (float ref_clock_MHz,
	unsigned int multiplier, unsigned int divisor)
{
	//output divisor for DDR PLL should be 2
	if(0==KeyStone_PLL_init((PLL_ControlRegs *)&gpBootCfgRegs->DDR3_PLL_CTL0, 
		divisor, multiplier, 2))
	{
		printf("Initialize DDR speed = %.2fMHzx/%dx%d = %.3fMTS\n", 
			ref_clock_MHz, divisor, multiplier, 
			ref_clock_MHz*multiplier/divisor);
	}
}

/*===============================TSC===================================*/
unsigned int cycle_measure_overhead=50;
/*****************************************************************************
 Prototype    : calc_cycle_measure_overhead
 Description  : calclucate the cycles measurement overhead
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void calc_cycle_measure_overhead()
{
	unsigned int cycle_cold, cycle_warm;
	cycle_cold= TSCL;
	cycle_cold = TSC_getDelay(cycle_cold);
	cycle_warm= TSCL;
	cycle_warm = TSC_getDelay(cycle_warm);
	cycle_measure_overhead = (cycle_cold + cycle_warm)/2;
}

/*****************************************************************************
 Prototype    : TSC_init
 Description  : Initialize Time stamp counter to measure cycles
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void TSC_init()
{
	TSCL = 0; 	/* Enable the TSC */
	calc_cycle_measure_overhead();
}

/*****************************************************************************
 Prototype    : TSC_delay_ms
 Description  : Implement the delay function in millisecond
 Input        : Uint32 ms  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void TSC_delay_ms(Uint32 ms)
{
	volatile unsigned long long startTSC, currentTSC;
	unsigned long long delay_cycles;
	Uint32 tscl, tsch;

	tscl= TSCL;
	tsch= TSCH;
	startTSC= _itoll(tsch,tscl); 
	
	delay_cycles= ((unsigned long long)ms*gDSP_Core_Speed_Hz/1000);

	do
	{
		tscl= TSCL;
		tsch= TSCH;
		currentTSC= _itoll(tsch,tscl); 
	}
	while((currentTSC-startTSC)<delay_cycles);
}

/*****************************************************************************
 Prototype    : TSC_delay_us
 Description  : Implement the delay function in microsecond
 Input        : Uint32 us  
 Output       : None
 Return Value : 
*****************************************************************************/
void TSC_delay_us(Uint32 us)
{
	volatile unsigned long long startTSC, currentTSC;
	unsigned long long delay_cycles;
	Uint32 tscl, tsch;

	tscl= TSCL;
	tsch= TSCH;
	startTSC= _itoll(tsch,tscl); 
	
	delay_cycles= ((unsigned long long)us*gDSP_Core_Speed_Hz/1000000);

	do
	{
		tscl= TSCL;
		tsch= TSCH;
		currentTSC= _itoll(tsch,tscl); 
	}
	while((currentTSC-startTSC)<delay_cycles);
}

/*===============================Timer=================================*/
/*****************************************************************************
 Prototype    : Reset_Timer
 Description  : Reset the general timer value
 Input        : int timer_num  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void Reset_Timer(int timer_num)
{
	if(gpTimerRegs[timer_num]->TGCR)
	{
		gpTimerRegs[timer_num]->TGCR= 0;
		gpTimerRegs[timer_num]->TCR= 0;
	}
}

 /*****************************************************************************
 Prototype    : Timer64_Init
 Description  : Initialize a 64-bit timer
 Input        : Timer64_Config * tmrCfg  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void Timer64_Init(Timer64_Config * tmrCfg)
{
	Reset_Timer(tmrCfg->timer_num);

	gpTimerRegs[tmrCfg->timer_num]->CNTLO= 0;
	gpTimerRegs[tmrCfg->timer_num]->CNTHI= 0;

	/*please note, in clock mode, two timer periods generate a clock, 
	one timer period output high voltage level, the other timer period 
	output low voltage level, so, the timer period should be half to the 
	desired output clock period*/
	if(TIMER_PERIODIC_CLOCK==tmrCfg->timerMode)
		tmrCfg->period= tmrCfg->period/2;

	/*the value written into period register is the expected value minus one*/
	gpTimerRegs[tmrCfg->timer_num]->PRDLO= _loll(tmrCfg->period-1);
	gpTimerRegs[tmrCfg->timer_num]->PRDHI= _hill(tmrCfg->period-1);
	if(tmrCfg->reload_period>1)
	{
		gpTimerRegs[tmrCfg->timer_num]->RELLO= _loll(tmrCfg->reload_period-1);
		gpTimerRegs[tmrCfg->timer_num]->RELHI= _hill(tmrCfg->reload_period-1);
	}
	
	if(TIMER_WATCH_DOG==tmrCfg->timerMode)
	{
		gpTimerRegs[tmrCfg->timer_num]->TGCR= 
			/*Select watch-dog mode*/
			(CSL_TMR_TIMMODE_WDT<<CSL_TMR_TGCR_TIMMODE_SHIFT)
			/*Remove the timer from reset*/
			|(CSL_TMR_TGCR_TIMLORS_MASK)
			|(CSL_TMR_TGCR_TIMHIRS_MASK);
	}
	else if(TIMER_PERIODIC_WAVE==tmrCfg->timerMode)
	{
		gpTimerRegs[tmrCfg->timer_num]->TGCR= TMR_TGCR_PLUSEN_MASK
			/*for plus featuers, dual 32-bit unchained timer mode should be used*/
			|(CSL_TMR_TIMMODE_DUAL_UNCHAINED<<CSL_TMR_TGCR_TIMMODE_SHIFT)
			/*Remove the timer from reset*/
			|(CSL_TMR_TGCR_TIMLORS_MASK);

		//in plus mode, interrupt/event must be enabled manually
		gpTimerRegs[tmrCfg->timer_num]->INTCTL_STAT= TMR_INTCTLSTAT_EN_ALL_CLR_ALL;
	}
	else
	{
		gpTimerRegs[tmrCfg->timer_num]->TGCR= 
			/*Select 64-bit general timer mode*/
			(CSL_TMR_TIMMODE_GPT<<CSL_TMR_TGCR_TIMMODE_SHIFT)
			/*Remove the timer from reset*/
			|(CSL_TMR_TGCR_TIMLORS_MASK)
			|(CSL_TMR_TGCR_TIMHIRS_MASK);
	}

	/*make timer stop with emulation*/
	gpTimerRegs[tmrCfg->timer_num]->EMUMGT_CLKSPD = (gpTimerRegs[tmrCfg->timer_num]->EMUMGT_CLKSPD&
		~(CSL_TMR_EMUMGT_CLKSPD_FREE_MASK|CSL_TMR_EMUMGT_CLKSPD_SOFT_MASK));

	if(TIMER_WATCH_DOG==tmrCfg->timerMode)
	{
		/*enable watchdog timer*/
		gpTimerRegs[tmrCfg->timer_num]->WDTCR = CSL_TMR_WDTCR_WDEN_MASK
			|(CSL_TMR_WDTCR_WDKEY_CMD1<<CSL_TMR_WDTCR_WDKEY_SHIFT);

		gpTimerRegs[tmrCfg->timer_num]->TCR= 
			(CSL_TMR_CLOCK_INP_NOGATE<<CSL_TMR_TCR_TIEN_LO_SHIFT   ) 
			|(CSL_TMR_CLKSRC_INTERNAL<<CSL_TMR_TCR_CLKSRC_LO_SHIFT ) 
			/*The timer is enabled continuously*/
			|(CSL_TMR_ENAMODE_CONT<<CSL_TMR_TCR_ENAMODE_LO_SHIFT) 
			|((tmrCfg->pulseWidth<<CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK) 
			/*select pulse mode*/
			|(CSL_TMR_CP_PULSE<<CSL_TMR_TCR_CP_LO_SHIFT     ) 
			|(CSL_TMR_INVINP_UNINVERTED<<CSL_TMR_TCR_INVINP_LO_SHIFT ) 
			|(CSL_TMR_INVOUTP_UNINVERTED<<CSL_TMR_TCR_INVOUTP_LO_SHIFT) 
			|(0<<CSL_TMR_TCR_TSTAT_LO_SHIFT  );

		/*active watchdog timer*/
		gpTimerRegs[tmrCfg->timer_num]->WDTCR = CSL_TMR_WDTCR_WDEN_MASK
			|(CSL_TMR_WDTCR_WDKEY_CMD2<<CSL_TMR_WDTCR_WDKEY_SHIFT);
	}
	else if(TIMER_ONE_SHOT_PULSE==tmrCfg->timerMode)
	{
		gpTimerRegs[tmrCfg->timer_num]->TCR= 
			(CSL_TMR_CLOCK_INP_NOGATE<<CSL_TMR_TCR_TIEN_LO_SHIFT   ) 
			|(CSL_TMR_CLKSRC_INTERNAL<<CSL_TMR_TCR_CLKSRC_LO_SHIFT ) 
			/*The timer is enabled one-shot*/
			|(CSL_TMR_ENAMODE_ENABLE<<CSL_TMR_TCR_ENAMODE_LO_SHIFT) 
			|((tmrCfg->pulseWidth<<CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK) 
			/*select pulse mode*/
			|(CSL_TMR_CP_PULSE<<CSL_TMR_TCR_CP_LO_SHIFT     ) 
			|(CSL_TMR_INVINP_UNINVERTED<<CSL_TMR_TCR_INVINP_LO_SHIFT ) 
			|(CSL_TMR_INVOUTP_UNINVERTED<<CSL_TMR_TCR_INVOUTP_LO_SHIFT) 
			|(0<<CSL_TMR_TCR_TSTAT_LO_SHIFT  );
	}
	else if(TIMER_PERIODIC_CLOCK==tmrCfg->timerMode)
	{
		gpTimerRegs[tmrCfg->timer_num]->TCR= 
			(CSL_TMR_CLOCK_INP_NOGATE<<CSL_TMR_TCR_TIEN_LO_SHIFT   ) 
			|(CSL_TMR_CLKSRC_INTERNAL<<CSL_TMR_TCR_CLKSRC_LO_SHIFT ) 
			/*The timer is enabled continuously*/
			|(CSL_TMR_ENAMODE_CONT<<CSL_TMR_TCR_ENAMODE_LO_SHIFT) 
			|((tmrCfg->pulseWidth<<CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK) 
			/*select clock mode*/
			|(CSL_TMR_CP_CLOCK<<CSL_TMR_TCR_CP_LO_SHIFT     ) 
			|(CSL_TMR_INVINP_UNINVERTED<<CSL_TMR_TCR_INVINP_LO_SHIFT ) 
			|(CSL_TMR_INVOUTP_UNINVERTED<<CSL_TMR_TCR_INVOUTP_LO_SHIFT) 
			|(0<<CSL_TMR_TCR_TSTAT_LO_SHIFT  );
	}
	else if(TIMER_PERIODIC_WAVE==tmrCfg->timerMode)
	{
		gpTimerRegs[tmrCfg->timer_num]->TCR= 
			(CSL_TMR_CLOCK_INP_NOGATE<<CSL_TMR_TCR_TIEN_LO_SHIFT   ) 
			|(CSL_TMR_CLKSRC_INTERNAL<<CSL_TMR_TCR_CLKSRC_LO_SHIFT ) 
			/*The timer is enabled continuously with period reload*/
			|(CSL_TMR_ENAMODE_CONT_RELOAD<<CSL_TMR_TCR_ENAMODE_LO_SHIFT) 
			|((tmrCfg->pulseWidth<<CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK) 
			/*select clock mode*/
			|(CSL_TMR_CP_CLOCK<<CSL_TMR_TCR_CP_LO_SHIFT     ) 
			|(CSL_TMR_INVINP_UNINVERTED<<CSL_TMR_TCR_INVINP_LO_SHIFT ) 
			|(CSL_TMR_INVOUTP_UNINVERTED<<CSL_TMR_TCR_INVOUTP_LO_SHIFT) 
			|(0<<CSL_TMR_TCR_TSTAT_LO_SHIFT  );
	}
	else 	/*TIMER_PERIODIC_PULSE*/
	{
		gpTimerRegs[tmrCfg->timer_num]->TCR= 
			(CSL_TMR_CLOCK_INP_NOGATE<<CSL_TMR_TCR_TIEN_LO_SHIFT   ) 
			|(CSL_TMR_CLKSRC_INTERNAL<<CSL_TMR_TCR_CLKSRC_LO_SHIFT ) 
			/*The timer is enabled continuously*/
			|(CSL_TMR_ENAMODE_CONT<<CSL_TMR_TCR_ENAMODE_LO_SHIFT) 
			|((tmrCfg->pulseWidth<<CSL_TMR_TCR_PWID_LO_SHIFT)&CSL_TMR_TCR_PWID_LO_MASK) 
			/*select clock mode*/
			|(CSL_TMR_CP_PULSE<<CSL_TMR_TCR_CP_LO_SHIFT     ) 
			|(CSL_TMR_INVINP_UNINVERTED<<CSL_TMR_TCR_INVINP_LO_SHIFT ) 
			|(CSL_TMR_INVOUTP_UNINVERTED<<CSL_TMR_TCR_INVOUTP_LO_SHIFT) 
			|(0<<CSL_TMR_TCR_TSTAT_LO_SHIFT  );
	}
}


/*****************************************************************************
 Prototype    : Service_Watchdog
 Description  : Implement the watch dog service
 Input        : int timer_num  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void Service_Watchdog(int timer_num)
{
    /*write sequence of a A5C6h followed by a DA7Eh 
    to services the watchdog timer.*/
    
	gpTimerRegs[timer_num]->WDTCR =
		(CSL_TMR_WDTCR_WDKEY_CMD1<<CSL_TMR_WDTCR_WDKEY_SHIFT);
	gpTimerRegs[timer_num]->WDTCR =
		(CSL_TMR_WDTCR_WDKEY_CMD2<<CSL_TMR_WDTCR_WDKEY_SHIFT);
}

/*===============================PSC===================================*/
/*****************************************************************************
 Prototype    : KeyStone_enable_PSC_module
 Description  : Enable the PSC module in KeyStone device
 Input        : Uint32 pwrDmnNum  
                Uint32 moduleNum  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
Int32 KeyStone_enable_PSC_module (Uint32 pwrDmnNum, Uint32 moduleNum)
{
	Uint32 uiStartTSC= TSCL;

    if (CSL_PSC_getPowerDomainState(pwrDmnNum) != PSC_PDSTATE_ON)
    {
	    /* Set Power domain to ON */
	    CSL_PSC_enablePowerDomain (pwrDmnNum);

	    /* Start the state transition */
	    CSL_PSC_startStateTransition (pwrDmnNum);

	    /* Wait until the state transition process is completed. */
	    while (!CSL_PSC_isStateTransitionDone (pwrDmnNum))
		{
			if(TSC_count_cycle_from(uiStartTSC)>0x3FFFFFFF)
			{
				printf("Enable power domain %d timeout!\n", pwrDmnNum);
				return -2;
			}
		}
	}

    /* Enable the clocks too*/
    CSL_PSC_setModuleNextState (moduleNum, PSC_MODSTATE_ENABLE);

    /* Start the state transition */
    CSL_PSC_startStateTransition (pwrDmnNum);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (pwrDmnNum))
	{
		if(TSC_count_cycle_from(uiStartTSC)>0x3FFFFFFF)
		{
			printf("Enable clock domain %d timeout!\n", moduleNum);
			return -2;
		}
	}

    /* Return PSC status */
    if ((CSL_PSC_getPowerDomainState(pwrDmnNum) == PSC_PDSTATE_ON) &&
        (CSL_PSC_getModuleState (moduleNum) == PSC_MODSTATE_ENABLE))
    {
        /*Ready for use */
        return 0;
    }
    else
    {
        /*Return error */
        return -1;
    }
}
/*****************************************************************************
 Prototype    : KeyStone_disable_PSC_module
 Description  : Disable the PSC module in KeyStone device
 Input        : Uint32 pwrDmnNum  
                Uint32 moduleNum  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/2/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
Int32 KeyStone_disable_PSC_module (Uint32 pwrDmnNum, Uint32 moduleNum)
{
	Uint32 uiStartTSC= TSCL;
	
    /* disable the clocks*/
    CSL_PSC_setModuleNextState (moduleNum, PSC_MODSTATE_SWRSTDISABLE);

    /* Start the state transition */
    CSL_PSC_startStateTransition (pwrDmnNum);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (pwrDmnNum))
	{
		if(TSC_count_cycle_from(uiStartTSC)>0x3FFFFFFF)
		{
			printf("Disable clock domain %d timeout!\n", moduleNum);
			return -2;
		}
	}

    /* Return PSC status */
    if (CSL_PSC_getModuleState (moduleNum) == PSC_MODSTATE_SWRSTDISABLE)
    {
        /*Ready for use */
        return 0;
    }
    else
    {
        /*Return error */
        return -1;
    }

}
/*****************************************************************************
 Prototype    : KeyStone_disable_PSC_Power_Domain
 Description  : Disable the PSC power domain
 Input        : Uint32 pwrDmnNum  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
Int32 KeyStone_disable_PSC_Power_Domain (Uint32 pwrDmnNum)
{
	Uint32 uiStartTSC= TSCL;

    /* Set Power domain to OFF */
    CSL_PSC_disablePowerDomain (pwrDmnNum);

    /* Start the state transition */
    CSL_PSC_startStateTransition (pwrDmnNum);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (pwrDmnNum))
	{
		if(TSC_count_cycle_from(uiStartTSC)>0x3FFFFFFF)
		{
			printf("Disable power domain %d timeout!\n", pwrDmnNum);
			return -2;
		}
	}

    /* Return PSC status */
    if (CSL_PSC_getPowerDomainState(pwrDmnNum) == PSC_PDSTATE_OFF)
    {
        /*Ready for use */
        return 0;
    }
    else
    {
        /*Return error */
        return -1;
    }

}

/*============================EDMA=====================================*/
 /*****************************************************************************
 Prototype    : EDMA_channel_TC_cfg
 Description  : Setup uiChannel of an EDMA to use uiTC
 Input        : Uint32 uiCC  
                Uint32 uiChannel            
                Uint32 uiTC                 
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EDMA_channel_TC_cfg (Uint32 uiCC, 
	Uint32 uiChannel, Uint32 uiTC)
{
	gpEDMA_CC_regs[uiCC]->TPCC_DMAQNUM[uiChannel/8] = 
		(gpEDMA_CC_regs[uiCC]->TPCC_DMAQNUM[uiChannel/8]&(~(0xF<<((uiChannel&7)*4))))
		|(uiTC<<((uiChannel&7)*4));
}
/*****************************************************************************
 Prototype    : EDMA_TC_priority_cfg
 Description  : Setup uiChannel of an EDMA TC priority
 Input        : Uint32 uiCC  
                Uint32 uiPri                
                Uint32 uiTC                 
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EDMA_TC_priority_cfg(Uint32 uiCC, 
	Uint32 uiPri, Uint32 uiTC)
{
	gpEDMA_CC_regs[uiCC]->TPCC_QUEPRI= 
		(gpEDMA_CC_regs[uiCC]->TPCC_QUEPRI&(~(0xF<<((uiTC&3)*4))))
		|(uiPri<<((uiTC&3)*4));
}
/*****************************************************************************
 Prototype    : EDMA_init
 Description  : Initialize all EDMA registers and clear the event
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EDMA_init ()
{
	int i;
	unsigned int * uipPaRAM;

	/*clear PaRAM*/
	uipPaRAM= (unsigned int *)&(gpEDMA_CC0_regs->PARAMSET[0]);
	for(i=0; i<8*CSL_EDMA3_TPCC0_NUM_PARAMSETS; i++) 	
		*uipPaRAM++=0;

	uipPaRAM= (unsigned int *)&(gpEDMA_CC1_regs->PARAMSET[0]);
	for(i=0; i<8*CSL_EDMA3_TPCC1_NUM_PARAMSETS; i++) 	
		*uipPaRAM++=0;

	uipPaRAM= (unsigned int *)&(gpEDMA_CC2_regs->PARAMSET[0]);
	for(i=0; i<8*CSL_EDMA3_TPCC2_NUM_PARAMSETS; i++) 	
		*uipPaRAM++=0;
		
	/*Assign PaRAM for different channels*/
	for(i=0; i<CSL_EDMA3_TPCC0_NUM_DMACH; i++) 	
		gpEDMA_CC0_regs->TPCC_DCHMAP[i] = i<< CSL_TPCC_TPCC_DCHMAP0_PAENTRY_SHIFT;

	for(i=0; i<CSL_EDMA3_TPCC1_NUM_DMACH; i++) 	
		gpEDMA_CC1_regs->TPCC_DCHMAP[i] = i<< CSL_TPCC_TPCC_DCHMAP0_PAENTRY_SHIFT;

	for(i=0; i<CSL_EDMA3_TPCC2_NUM_DMACH; i++) 	
		gpEDMA_CC2_regs->TPCC_DCHMAP[i] = i<< CSL_TPCC_TPCC_DCHMAP0_PAENTRY_SHIFT;

	/*Assign TC/Queue for different channels*/
	gpEDMA_CC0_regs->TPCC_DMAQNUM[0]= 0x10101010;
	gpEDMA_CC0_regs->TPCC_DMAQNUM[1]= 0x10101010;

	gpEDMA_CC1_regs->TPCC_DMAQNUM[0]= 0x32103210;
	gpEDMA_CC1_regs->TPCC_DMAQNUM[1]= 0x32103210;
	gpEDMA_CC1_regs->TPCC_DMAQNUM[2]= 0x32103210;
	gpEDMA_CC1_regs->TPCC_DMAQNUM[3]= 0x32103210;
	gpEDMA_CC1_regs->TPCC_DMAQNUM[4]= 0x32103210;
	gpEDMA_CC1_regs->TPCC_DMAQNUM[5]= 0x32103210;
	gpEDMA_CC1_regs->TPCC_DMAQNUM[6]= 0x32103210;
	gpEDMA_CC1_regs->TPCC_DMAQNUM[7]= 0x32103210;

	gpEDMA_CC2_regs->TPCC_DMAQNUM[0]= 0x32103210;
	gpEDMA_CC2_regs->TPCC_DMAQNUM[1]= 0x32103210;
	gpEDMA_CC2_regs->TPCC_DMAQNUM[2]= 0x32103210;
	gpEDMA_CC2_regs->TPCC_DMAQNUM[3]= 0x32103210;
	gpEDMA_CC2_regs->TPCC_DMAQNUM[4]= 0x32103210;
	gpEDMA_CC2_regs->TPCC_DMAQNUM[5]= 0x32103210;
	gpEDMA_CC2_regs->TPCC_DMAQNUM[6]= 0x32103210;
	gpEDMA_CC2_regs->TPCC_DMAQNUM[7]= 0x32103210;

	/*clear any events and status*/
	gpEDMA_CC0_regs->TPCC_ECR=  0xFFFF;
	gpEDMA_CC0_regs->TPCC_EECR= 0xFFFF;
	gpEDMA_CC0_regs->TPCC_ICR=  0xFFFF;
	gpEDMA_CC0_regs->TPCC_IECR= 0xFFFF;
	gpEDMA_CC0_regs->TPCC_EMCR= 0xFFFF;
	gpEDMA_CC0_regs->TPCC_QEMCR= 0xFFFF;
    gpEDMA_CC0_regs->TPCC_CCERRCLR= 0xFFFF;
	gpEDMA_CC0_regs->TPCC_SECR= 0xFFFF;

	gpEDMA_CC1_regs->TPCC_ECR= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_ECRH= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_EECR= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_EECRH= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_ICR= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_ICRH= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_IECR= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_IECRH= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_EMCR= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_EMCRH= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_QEMCR= 0xFFFFFFFF;
    gpEDMA_CC1_regs->TPCC_CCERRCLR= 0xFFFF;
	gpEDMA_CC1_regs->TPCC_SECR= 0xFFFFFFFF;
	gpEDMA_CC1_regs->TPCC_SECRH= 0xFFFFFFFF;

	gpEDMA_CC2_regs->TPCC_ECR= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_ECRH= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_EECR= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_EECRH= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_ICR= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_ICRH= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_IECR= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_IECRH= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_EMCR= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_EMCRH= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_QEMCR= 0xFFFFFFFF;
    gpEDMA_CC2_regs->TPCC_CCERRCLR= 0xFFFF;
	gpEDMA_CC2_regs->TPCC_SECR= 0xFFFFFFFF;
	gpEDMA_CC2_regs->TPCC_SECRH= 0xFFFFFFFF;

	for(i=0; i<NUM_EDMA_TC; i++)
	{
		//Clear TC error
		gpEDMA_TC_regs[i]->TPTC_ERRCLR= 0xF;

		//enable error interrupt
		gpEDMA_TC_regs[i]->TPTC_ERREN= 
			(1<<CSL_TPTC_TPTC_ERREN_MMRAERR_SHIFT)
			|(1<<CSL_TPTC_TPTC_ERREN_TRERR_SHIFT)
			|(1<<CSL_TPTC_TPTC_ERREN_BUSERR_SHIFT);
	}
}


void EDMA_event_enable(Uint32 uiCC, Uint32 uiChannel)
{
	if(uiChannel<32)
	{
		//enable the EDMA channel
		gpEDMA_CC_regs[uiCC]->TPCC_EESR= 1<<(uiChannel);
	}
	else
	{
		//enable the EDMA channel
		gpEDMA_CC_regs[uiCC]->TPCC_EESRH= 1<<(uiChannel-32);
	}	
}

void EDMA_event_disable(Uint32 uiCC, Uint32 uiChannel)
{
	if(uiChannel<32)
	{
		//disable the EDMA channel
		gpEDMA_CC_regs[uiCC]->TPCC_EECR= 1<<(uiChannel);
	}
	else
	{
		//disable the EDMA channel
		gpEDMA_CC_regs[uiCC]->TPCC_EECRH= 1<<(uiChannel-32);
	}	
}

void EDMA_interrupt_enable(Uint32 uiCC, Uint32 uiIntNum)
{
	if(uiIntNum<32)
	{
		//enable the EDMA channel interrupt
		gpEDMA_CC_regs[uiCC]->TPCC_IESR= 1<<(uiIntNum);
	}
	else
	{
		//enable the EDMA channel interrupt
		gpEDMA_CC_regs[uiCC]->TPCC_IESRH= 1<<(uiIntNum-32);
	}	
}

void EDMA_interrupt_disable(Uint32 uiCC, Uint32 uiIntNum)
{
	if(uiIntNum<32)
	{
		//disable the EDMA channel interrupt
		gpEDMA_CC_regs[uiCC]->TPCC_IECR= 1<<(uiIntNum);
	}
	else
	{
		//disable the EDMA channel interrupt
		gpEDMA_CC_regs[uiCC]->TPCC_IECRH= 1<<(uiIntNum-32);
	}	
}

/*****************************************************************************
 Prototype    : EDMA_wait
 Description  : wait the pending EDMA complete
 Input        : EDMA_CC_Channel_Num CC_channel
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/30
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EDMA_wait(EDMA_CC_Channel_Num CC_channel)
{
	CSL_TpccRegs*  EDMACCRegs;
	unsigned int uiChannel;
    volatile Uint32 * TPCC_IPR;
    volatile Uint32 * TPCC_ICR;

	EDMACCRegs= gpEDMA_CC_regs[CC_channel>>16];
	uiChannel = CC_channel&0xFF;

	if(uiChannel<32)
	{
		TPCC_IPR= &EDMACCRegs->TPCC_IPR;
		TPCC_ICR= &EDMACCRegs->TPCC_ICR;
	}
	else
	{
		TPCC_IPR= &EDMACCRegs->TPCC_IPRH;
		TPCC_ICR= &EDMACCRegs->TPCC_ICRH;
		uiChannel -= 32;
	}
	
	/*wait for completion*/
	while(0==((*TPCC_IPR)&(1<<(uiChannel))));

	/*clear completion flag*/
	(*TPCC_ICR)= 1<<(uiChannel);
}

/*****************************************************************************
 Prototype    : EDMA_Copy
 Description  : EDMA copy function with manual trigger
 Input        : unsigned int srcAddr     
                unsigned int dstAddr     
                unsigned int byteCount, <64KB   
                EDMA_CC_Channel_Num CC_channel  
                DMA_Wait wait
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/30
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EDMA_copy(unsigned int srcAddr, unsigned int dstAddr, 
	unsigned int byteCount, EDMA_CC_Channel_Num CC_channel, DMA_Wait wait)
{
	CSL_TpccRegs*  EDMACCRegs;
	unsigned int uiChannel;
    volatile Uint32 * TPCC_ESR;
    volatile Uint32 * TPCC_IPR;
    volatile Uint32 * TPCC_ICR;

	EDMACCRegs= gpEDMA_CC_regs[CC_channel>>16];
	uiChannel = CC_channel&0xFF;

	EDMACCRegs->PARAMSET[uiChannel].OPT= 
		CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, 
			CSL_EDMA3_TCCH_DIS, 
			CSL_EDMA3_ITCINT_DIS, 
			CSL_EDMA3_TCINT_EN,
			uiChannel,
			CSL_EDMA3_TCC_NORMAL,
			CSL_EDMA3_FIFOWIDTH_NONE, 
			CSL_EDMA3_STATIC_DIS, 
			CSL_EDMA3_SYNC_A, 
			CSL_EDMA3_ADDRMODE_INCR, 
			CSL_EDMA3_ADDRMODE_INCR);
	EDMACCRegs->PARAMSET[uiChannel].SRC= GLOBAL_ADDR(srcAddr);
	EDMACCRegs->PARAMSET[uiChannel].A_B_CNT=CSL_EDMA3_CNT_MAKE(byteCount&0xFFFF, 1);
	EDMACCRegs->PARAMSET[uiChannel].DST= GLOBAL_ADDR(dstAddr);
	EDMACCRegs->PARAMSET[uiChannel].SRC_DST_BIDX= 0;
	EDMACCRegs->PARAMSET[uiChannel].LINK_BCNTRLD= CSL_EDMA3_LINKBCNTRLD_MAKE(0xFFFF, 1);
	EDMACCRegs->PARAMSET[uiChannel].SRC_DST_CIDX= 0;
	EDMACCRegs->PARAMSET[uiChannel].CCNT= 1;

	if(uiChannel<32)
	{
		TPCC_ESR= &EDMACCRegs->TPCC_ESR;
		TPCC_IPR= &EDMACCRegs->TPCC_IPR;
		TPCC_ICR= &EDMACCRegs->TPCC_ICR;
	}
	else
	{
		TPCC_ESR= &EDMACCRegs->TPCC_ESRH;
		TPCC_IPR= &EDMACCRegs->TPCC_IPRH;
		TPCC_ICR= &EDMACCRegs->TPCC_ICRH;
		uiChannel -= 32;
	}
	
	/*Manually trigger the EDMA*/
	(*TPCC_ESR)= 1<<(uiChannel);
 
	if(wait)
	{
		/*wait for completion*/
		while(0==((*TPCC_IPR)&(1<<(uiChannel))));

		/*clear completion flag*/
		(*TPCC_ICR)= 1<<(uiChannel);
	}
}

/*****************************************************************************
 Prototype    : EDMA_fill
 Description  : EDMA fill function with manual trigger
 Input        : unsigned int address, must align to 8 bytes boundary     
                unsigned long long data     
                unsigned int byteCount, must be multiple of 8   
                EDMA_CC_Channel_Num CC_channel  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2013/8/11
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EDMA_fill(unsigned int address, unsigned long long data, 
	unsigned int byteCount, EDMA_CC_Channel_Num CC_channel)
{
	int i;
	CSL_TpccRegs*  EDMACCRegs;
	unsigned int uiChannel, uiChannelShift, uiBCNT;
    volatile Uint32 * TPCC_ESR;
    volatile Uint32 * TPCC_IPR;
    volatile Uint32 * TPCC_ICR;
    unsigned long long tempBuf[128/8];
    Uint32 tempBufSize=128, headerSize, tailSize;

	if(tempBufSize>byteCount)
		tempBufSize=byteCount;

	for(i=0; i< tempBufSize/8; i++)
		tempBuf[i]= data;

	/*split the transfer into 3 sections at 128 byte boundary*/
	if(address&127)	//header address not start on 128 byte boundary
	{
		headerSize= 128- (address&127);
		if(headerSize>byteCount)
			headerSize=byteCount;
		EDMA_copy((Uint32)tempBuf, address, headerSize, CC_channel, DMA_WAIT);
		address+= headerSize;
		byteCount-= headerSize;
	}

	if(byteCount&&((address+byteCount)&127))//tail address not start on 128 byte boundary
	{
		tailSize= (address+byteCount)&127;
		EDMA_copy((Uint32)tempBuf, address+byteCount-tailSize, tailSize, CC_channel, DMA_WAIT);
		byteCount-= tailSize;
	}
	
	EDMACCRegs= gpEDMA_CC_regs[CC_channel>>16];
	uiChannel = CC_channel&0xFF;
	if(uiChannel<32)
	{
		TPCC_ESR= &EDMACCRegs->TPCC_ESR;
		TPCC_IPR= &EDMACCRegs->TPCC_IPR;
		TPCC_ICR= &EDMACCRegs->TPCC_ICR;
		uiChannelShift= uiChannel;
	}
	else
	{
		TPCC_ESR= &EDMACCRegs->TPCC_ESRH;
		TPCC_IPR= &EDMACCRegs->TPCC_IPRH;
		TPCC_ICR= &EDMACCRegs->TPCC_ICRH;
		uiChannelShift= uiChannel - 32;
	}	

	EDMACCRegs->PARAMSET[uiChannel].OPT= 
		CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, 
			CSL_EDMA3_TCCH_DIS, 
			CSL_EDMA3_ITCINT_DIS, 
			CSL_EDMA3_TCINT_EN,
			uiChannel,
			CSL_EDMA3_TCC_NORMAL,
			CSL_EDMA3_FIFOWIDTH_NONE, 
			CSL_EDMA3_STATIC_EN, //keep PARAM unchanged
			CSL_EDMA3_SYNC_AB, 
			CSL_EDMA3_ADDRMODE_INCR, 
			CSL_EDMA3_ADDRMODE_INCR);
	EDMACCRegs->PARAMSET[uiChannel].SRC= GLOBAL_ADDR(tempBuf);
	EDMACCRegs->PARAMSET[uiChannel].SRC_DST_BIDX= CSL_EDMA3_BIDX_MAKE(0, 128);
	EDMACCRegs->PARAMSET[uiChannel].LINK_BCNTRLD= CSL_EDMA3_LINKBCNTRLD_MAKE(0xFFFF, 0);
	EDMACCRegs->PARAMSET[uiChannel].SRC_DST_CIDX= 0;
	EDMACCRegs->PARAMSET[uiChannel].CCNT= 1;

	while(byteCount) 	//the reminding must be multiple of 128 bytes
	{
		uiBCNT= byteCount/128;
		if(uiBCNT>65535)
			uiBCNT= 65535;
	
		EDMACCRegs->PARAMSET[uiChannel].A_B_CNT= CSL_EDMA3_CNT_MAKE(128, uiBCNT);
		EDMACCRegs->PARAMSET[uiChannel].DST= GLOBAL_ADDR(address);
		
		/*Manually trigger the EDMA*/
		(*TPCC_ESR)= 1<<(uiChannelShift);
	 
		/*wait for completion*/
		while(0==((*TPCC_IPR)&(1<<(uiChannelShift))));

		/*clear completion flag*/
		(*TPCC_ICR)= 1<<(uiChannelShift);

		byteCount -= uiBCNT*128;
		address += uiBCNT*128;
	}
}

/*****************************************************************************
 Prototype    : IDMA_wait
 Description  : wait the pending IDMA complete
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void IDMA_wait()
{
	/* Wait until copying is completed */
	while (gpCGEM_regs->IDMA1_STAT); 
}
/*****************************************************************************
 Prototype    : IDMA_copy
 Description  : implement the data copy via IDMA
 Input        : unsigned int srcAddr    
                unsigned int dstAddr    
                unsigned int byteCount, <64KB  
                IDMA_Wait wait          
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/28
    Author       : Brigthon
    Modification : Created function

*****************************************************************************/
void IDMA_copy(unsigned int srcAddr, unsigned int dstAddr, 
	unsigned int byteCount, DMA_Wait wait)
{
	gpCGEM_regs->IDMA1_SOURCE= srcAddr;
	gpCGEM_regs->IDMA1_DEST= dstAddr;
	gpCGEM_regs->IDMA1_COUNT= byteCount&0xFFFC;

	if(wait)
	{
		/* Wait until copying is completed */
		while (gpCGEM_regs->IDMA1_STAT); 
	}
}
/*****************************************************************************
 Prototype    : EDMA_CC_error_handler
 Description  : Edma channel controller error processing
 Input        : Uint32 edmaNum, EDMA module number (0~2)  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/11/7
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EDMA_CC_error_handler(Uint32 edmaNum)
{
	int i;
	CSL_TpccRegs*  EDMACCRegs= gpEDMA_CC_regs[edmaNum];
	Uint32 EMR, EMRH= 0, QEMR, CCERR;

	//read error status
	EMR= EDMACCRegs->TPCC_EMR;
	QEMR= EDMACCRegs->TPCC_QEMR;
	CCERR= EDMACCRegs->TPCC_CCERR;
	exception_record.status.ext_sts.info.edma.CC_info.EMR= EMR;
	exception_record.status.ext_sts.info.edma.CC_info.QEMR= QEMR;
	exception_record.status.ext_sts.info.edma.CC_info.CCERR= CCERR;

	//clear error status
	EDMACCRegs->TPCC_EMCR= EMR;
	EDMACCRegs->TPCC_QEMCR= QEMR;
	EDMACCRegs->TPCC_CCERRCLR= CCERR;

	//channel 32~63 for EDMA CC1 and CC2
	if(0<edmaNum)
	{
		//read error status
		EMRH= EDMACCRegs->TPCC_EMRH;
		exception_record.status.ext_sts.info.edma.CC_info.EMRH= EMRH;

		//clear error status
		EDMACCRegs->TPCC_EMCRH= EMRH;
	}

	for(i=0; i<32; i++)
	{
		if((EMR>>i)&1)
			printf("    EDMA Channel %d event missed.\n", i);
		if((EMRH>>i)&1)
			printf("    EDMA Channel %d event missed.\n", i+32);
	}

	for(i=0; i<8; i++)
	{
		if((QEMR>>i)&1)
			printf("    QDMA Channel %d event missed.\n", i);
	}

	for(i=0; i<4; i++)
	{
		if((CCERR>>i)&1)
			printf("    Queue %d Watermark/threshold has been exceeded.\n", i);
	}

	if(CCERR&CSL_TPCC_TPCC_CCERR_TCCERR_MASK)
		puts("    Total number of allowed TCCs has been reached.");
	
}
/*****************************************************************************
 Prototype    : EDMA_TC_error_handler
 Description  : Edma transfer controller error processing
 Input        : CSL_TptcRegs * edmaTCRegs  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/11/7
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EDMA_TC_error_handler(CSL_TptcRegs * edmaTCRegs)
{
	Uint32 ERRSTAT, ERRDET, STAT;

	//read error status
	ERRSTAT= edmaTCRegs->TPTC_ERRSTAT;
	ERRDET= edmaTCRegs->TPTC_ERRDET;
	exception_record.status.ext_sts.info.edma.TC_info.ERRSTAT=ERRSTAT ;
	exception_record.status.ext_sts.info.edma.TC_info.ERRDET= ERRDET;

	//clear error
	edmaTCRegs->TPTC_ERRCLR= ERRSTAT;

	if(ERRSTAT&CSL_TPTC_TPTC_ERRSTAT_MMRAERR_MASK)
		puts("      User attempted to read or write to an invalid address in configuration memory map.");
	if(ERRSTAT&CSL_TPTC_TPTC_ERRSTAT_TRERR_MASK)
		puts("      TR detected that violates constant addressing mode transfer (SAM or DAM is set) alignment rules or has ACNT or BCNT== 0.");
	if(ERRSTAT&CSL_TPTC_TPTC_ERRSTAT_BUSERR_MASK)
	{
		puts("      EDMA3TC has detected an error at source or destination address.");

		STAT= ERRDET&CSL_TPTC_TPTC_ERRDET_STAT_MASK;

		if(STAT>=8)
			printf("      write error (%d). ",STAT);
		else if(STAT>=1)
			printf("      read error (%d). ",STAT);
		else
			printf("      no error!?");

		printf("TCC= %d. TCINTEN= %d. TCCHEN= %d\n",
			(ERRDET&CSL_TPTC_TPTC_ERRDET_TCC_MASK)>>CSL_TPTC_TPTC_ERRDET_TCC_SHIFT,
			(ERRDET&CSL_TPTC_TPTC_ERRDET_TCINTEN_MASK)>>CSL_TPTC_TPTC_ERRDET_TCINTEN_SHIFT,
			(ERRDET&CSL_TPTC_TPTC_ERRDET_TCCHEN_MASK)>>CSL_TPTC_TPTC_ERRDET_TCCHEN_SHIFT);
	}
		
}
/*****************************************************************************
 Prototype    : EDMA_error_handler
 Description  : EDMA error processing function
 Input        : Uint32 edmaNum    
                Uint32 errorFlag  
					error flag bit fields are defined as below 
					(follow the sequence in CIC)
					0 EDMACC_ERRINT EDMA3CC error interrupt          
					2 EDMATC_ERRINT0 EDMA3TC0 error interrupt
					3 EDMATC_ERRINT1 EDMA3TC1 error interrupt
					4 EDMATC_ERRINT2 EDMA3TC2 error interrupt
					5 EDMATC_ERRINT3 EDMA3TC3 error interrupt
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EDMA_error_handler(Uint32 edmaNum, Uint32 errorFlag)
{
	int i;
	
	printf("  EDMA module %d error\n", edmaNum);
	if(errorFlag&1)
		EDMA_CC_error_handler(edmaNum);

	errorFlag >>= 2;

	for(i=0; i<4; i++)
	{
		if(errorFlag&(1<<i))
		{
			printf("    TC %d error happened\n", i);
			if(0==edmaNum)
				EDMA_TC_error_handler(gpEDMA_TC_regs[i]);
			else if(1==edmaNum)
				EDMA_TC_error_handler(gpEDMA_TC_regs[2+i]);
			else if(2==edmaNum)
				EDMA_TC_error_handler(gpEDMA_TC_regs[6+i]);
		}
	}
}

/*======================memory protection==============================*/
/*code and data related to CorePac MPAX configuration should be allocated in LL2*/
#pragma DATA_SECTION(mem_prot_key,".far:Core_MPAX")
unsigned int mem_prot_key[4] = {0xBFBFBFBF, 0xFE29, 3, 4};
/*****************************************************************************
 Prototype    : lock_mem_prot_regs
 Description  : lock memory protection registers
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
#pragma CODE_SECTION (lock_mem_prot_regs, ".text:Core_MPAX")
void lock_mem_prot_regs()
{
	int i;
	
	/*1. Write a 1 to the KEYR field of the MPLKCMD register. This resets some internal
	status for the MPLK0 through MPLK3 registers.*/
	gpCGEM_regs->MPLKCMD = (1<<CSL_CGEM_MPLKCMD_KEYR_SHIFT);
	
	/*2. Write the key to MPLK0 through MPLK3. All four registers must be written
	exactly once. They may be written in any order.*/
	for(i=0; i<4; i++)
	{
		gpCGEM_regs->MPLK[i] = mem_prot_key[i];
	}

	/*3. Write a 1 to the LOCK field of the MPLKCMD register. This engages the lock.*/
	gpCGEM_regs->MPLKCMD = (1<<CSL_CGEM_MPLKCMD_LOCK_SHIFT);

	/*wait to make sure it is locked*/
	while(0==(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK));
}

/*****************************************************************************
 Prototype    : unlock_mem_prot_regs
 Description  : unlock memory protection registers
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
#pragma CODE_SECTION (unlock_mem_prot_regs, ".text:Core_MPAX")
void unlock_mem_prot_regs()
{
	int i;
	
	/*1. Write a 1 to the KEYR field in the MPLKCMD register. This resets some internal
	status for the MPLK0 through the MPLK3 registers.*/
	gpCGEM_regs->MPLKCMD = (1<<CSL_CGEM_MPLKCMD_KEYR_SHIFT);

	/*2. Write the unlock key to MPLK0 through the MPLK3 registers. The hardware
	compares the written value with the stored key value. Software must write to all
	four registers exactly once. The writes can arrive in any order.*/
	for(i=0; i<4; i++)
	{
		gpCGEM_regs->MPLK[i] = mem_prot_key[i];
	}

	/*3. Write a 1 to the UNLOCK field in the MPLKCMD register. If the key written in
	step 2 matches the stored key, the hardware disengages the lock. If the key written
	in step 2 does not match, the hardware signals an exception. The hardware
	reports the fault address as the address of the MPLKCMD register.*/
	gpCGEM_regs->MPLKCMD = (1<<CSL_CGEM_MPLKCMD_UNLOCK_SHIFT);

	/*wait to make sure it is unlocked*/
	while(1==(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK));
}

/*****************************************************************************
 Prototype    : L1_MPPA_setup
 Description  : setup the memory protection for local L1 memory
 Input        : volatile Uint32 MPPA_regs[], Uint32 MPPA[]  
 Output       : None
 Return Value : 

usage example:
 Uint32 MPPA[16]=
 {
	MP_LOCAL|MP_SR|MP_UR, 			//page 0 for read only
	MP_LOCAL|MP_SR|MP_SW|MP_UR|MP_UW, 	//page 1 for read/write
	......
 }
 ......
	L1_MPPA_setup(gpCGEM_regs->L1PMPPA, MPPA);

  History        :
  1.Date         : 2012/12/6
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void L1_MPPA_setup(volatile Uint32 MPPA_regs[], Uint32 MPPA[])
{
	int i;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();
		
	/*clear any memory protection fault*/
	gpCGEM_regs->L1PMPFCR = 1;
	gpCGEM_regs->L1DMPFCR = 1;

	/*setup the memory protection attributes for 32 pages*/
	for(i=0; i<16; i++)
	{
		MPPA_regs[i] = MPPA[i];
	}

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : L1P_memory_protection_cfg
 Description  : config "AccessPermisionMask" for L1P
 Input        : Uint32 AccessPermisionMask  
 Output       : None
 Return Value : 
*****************************************************************************/
void L1P_memory_protection_cfg(Uint32 AccessPermisionMask)
{
	int i;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	/*clear any memory protection fault*/
	gpCGEM_regs->L1PMPFCR = 1;

	/*set L1P only for cacheable local execution, disable all external access*/
	for(i=0; i<16; i++)
	{
		gpCGEM_regs->L1PMPPA[i] = AccessPermisionMask;
	}

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : L1D_memory_protection_cfg
 Description  : config "AccessPermisionMask" for L1P
 Input        : Uint32 AccessPermisionMask  
 Output       : None
 Return Value : 
*****************************************************************************/
void L1D_memory_protection_cfg(Uint32 AccessPermisionMask)
{
	int i;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	/*clear any memory protection fault*/
	gpCGEM_regs->L1DMPFCR = 1;

	/*set L1P only for cacheable local execution, disable all external access*/
	for(i=0; i<16; i++)
	{
		gpCGEM_regs->L1DMPPA[i] = AccessPermisionMask;
	}

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : L1_cache_protection
 Description  : protect L1 as cache
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void L1_cache_protection()
{
	/*set L1P only for cacheable local execution, disable all external access*/
	L1P_memory_protection_cfg(0);
	
	/*set L1D only for cacheable local read/write, disable all external access*/
	L1D_memory_protection_cfg(0);
}


/*****************************************************************************
 Prototype    : LL2_MPPA_setup
 Description  : setup the memory protection for local L2 memory
 Input        : Uint32 MPPA[]  
 Output       : None
 Return Value : 
usage example:
 Uint32 MPPA[32]=
 {
	MP_LOCAL|MP_SX|MP_UX, 			//page 0 for local code only
	MP_LOCAL|MP_SR|MP_SW|MP_UR|MP_UW, 	//page 1 for local data only
	......
 }
 ......
	LL2_MPPA_setup(MPPA);

  History        :
  1.Date         : 2012/10/5
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void LL2_MPPA_setup(Uint32 MPPA[])
{
	int i;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();
		
	/*clear any memory protection fault*/
	gpCGEM_regs->L2MPFCR = 1;

	/*setup the memory protection attributes for 32 pages*/
	for(i=0; i<32; i++)
	{
		gpCGEM_regs->L2MPPA[i] = MPPA[i];
	}

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : LL2_Memory_Protection_cfg
 Description  : config "AccessPermisionMask" for local L2 memory section from 
				"startAddress" with "byteCount" size
 Input        : Uint32 startAddress         
                Uint32 byteCount            
                Uint32 AccessPermisionMask  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/5
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void LL2_Memory_Protection_cfg(Uint32 startAddress,
	Uint32 byteCount, Uint32 AccessPermisionMask)
{
	int i;
	Uint32 uiEndAddress;
	Uint32 uiPageIndex, uiNumPages, uiPageSize, uiPageAddressMask, uiPageShift;
	TDSP_Board_Type DSP_Board_Type;

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	DSP_Board_Type = KeyStone_Get_dsp_board_type();

	/*L2 memory protection size is 32KB for TCI6614, C6670,
	it is 16KB for C6678*/
	uiPageSize= 32*1024;
	uiPageAddressMask= 32*1024-1;
	uiPageShift= 15;
	if(C6678_EVM == DSP_Board_Type)
	{
		uiPageSize= 16*1024;
		uiPageAddressMask= 16*1024-1;
		uiPageShift= 14;
	}

	if(startAddress>=0x10800000)
	{
		printf("LL2 memory protection start Address 0x%x is not a local address\n",
			startAddress);
		startAddress &= 0xFFFFFF;	 /*convert to local address*/
	}
	uiEndAddress= startAddress+ byteCount;

	if(startAddress&uiPageAddressMask)
	{
		printf("LL2 memory protection start Address 0x%x does not align to page boundary\n",
			startAddress);
		startAddress &= (~uiPageAddressMask);
	}
	uiPageIndex= (startAddress-0x800000)>>uiPageShift;

	byteCount= uiEndAddress- startAddress;
	if(byteCount&uiPageAddressMask)
	{
		printf("LL2 memory protection section size 0x%x is not multiple of page size\n",
			byteCount);
		byteCount = (byteCount+uiPageSize)&(~uiPageAddressMask);
	}
	uiNumPages= byteCount>>uiPageShift;

	for(i= 0; i<uiNumPages; i++)
		gpCGEM_regs->L2MPPA[uiPageIndex+i] = AccessPermisionMask;

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : KeyStone_CorePac_AID_map
 Description  : map CorePac AID to PrivID:
        map_table[0] assign the PrivID for AID0,
        map_table[1] assign the PrivID for AID1
        ......
        map_table[5] assign the PrivID for AID5
 Input        : Uint8 map_table[]  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/5
    Author       : Zhan
    Modification : Created function

*****************************************************************************/
void KeyStone_CorePac_AID_map(Uint8 map_table[])
{
	int i;
	Uint32 *PAMAP= (Uint32 *)&(gpCGEM_regs->PAMAP0);

	/*map all PrivID to AIDx by default*/
	for(i=0; i<16; i++)
		PAMAP[i]= CSL_CGEM_PAMAP0_AID_MASK;

	/*map AID0~AID5*/
	for(i=0; i<6; i++)
	{
		if(map_table[i]<16) /*PrivID must be less than 16*/
			PAMAP[map_table[i]]= i;
	}
}

/*****************************************************************************
 Prototype    : KeyStone_PrivID_Remap
 Description  : privilege ID remap to AID
 Input        : int privID  
                int AID     
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/5
    Author       : Zhan
    Modification : Created function

*****************************************************************************/
void KeyStone_PrivID_Remap(int privID, int AID)
{
	volatile unsigned int * pamapReg = NULL;
	unsigned int val = 0;

	pamapReg = (volatile unsigned int *)(&gpCGEM_regs->PAMAP0 + privID);

	if(AID >= MAX_AID_NUM)
		AID = 0;
	val = *pamapReg;

	val &= (~CSL_CGEM_PAMAP0_AID_MASK);

	val |= ((AID<<CSL_CGEM_PAMAP0_AID_SHIFT) & CSL_CGEM_PAMAP0_AID_MASK);

	*pamapReg = val;

	return;
}

/*****************************************************************************
 Prototype    : KeyStone_MPAX_seg_setup
 Description  : configure one MPAX segment
 Input        : MPAX_Regs * MPAX_regs       
                Uint32 BADDR                
                Uint32 RADDR                
                Uint32 SegementSize         
                Uint32 AccessPermisionMask  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
#pragma CODE_SECTION (KeyStone_MPAX_seg_setup, ".text:Core_MPAX")
void KeyStone_MPAX_seg_setup(MPAX_Regs * MPAX_regs, Uint32 BADDR, 
	Uint32 RADDR, Uint32 SegementSize, Uint32 AccessPermisionMask)
{
	Uint32 SegSizeMask, SegSizeBits;

	if(SegementSize<4*1024)
	{
		printf("Segment size %d is less than 4KB. ", SegementSize);
		SegementSize = 4*1024;
		printf("Extended segment size to 4KB.\n");
	}
	
	SegSizeBits= 31 - _lmbd(1, SegementSize);
	SegSizeMask= (1<<SegSizeBits)-1;
	if(SegementSize&SegSizeMask)
	{
		printf("Segment size 0x%x is not power of 2. ", SegementSize);
		SegSizeBits += 1;
		SegementSize= (1<<SegSizeBits);
		SegSizeMask= (1<<SegSizeBits)-1;
		printf("Extended segment size to 0x%x.\n", SegementSize);
	}

	if(BADDR&SegSizeMask)
	{
		printf("Segment base address 0x%x does not start from power-of-2 boundary corresponds to segment size 0x%x.\n", 
			BADDR, SegementSize);
		BADDR &= (~SegSizeMask);
		printf("Extended base address to 0x%x.\n", BADDR);
	}
	if(RADDR&(SegSizeMask>>4))
	{
		printf("Segment replacement address 0x%x does not start from power-of-2 boundary corresponds to segment size 0x%x.\n", 
			RADDR, SegementSize);
		RADDR &= (~(SegSizeMask>>4));
		printf("Extended replacement address to 0x%x.\n", RADDR);
	}
	
	MPAX_regs->MPAXH= BADDR|(SegSizeBits-1); 
	MPAX_regs->MPAXL= RADDR|AccessPermisionMask; 

}

/*****************************************************************************
 Prototype    : KeyStone_XMC_MPAX_setup
 Description  : configure multiple MPAX segments in XMC with a configuration
                table.
	Please note, the code of this function or the data used by this function
	(stack, parameters...) can not be put in the segment that will be modified
	by this function. Normally, to put this function and its related data in 
	LL2 is a good idea.
 Input        : MPAX_Config MPAX_cfg[]  
                Uint32 firstSeg         
                Uint32 numSegs          
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
#pragma CODE_SECTION (KeyStone_XMC_MPAX_setup, ".text:Core_MPAX")
void KeyStone_XMC_MPAX_setup(MPAX_Config MPAX_cfg[], 
	Uint32 firstSeg, Uint32 numSegs)
{
	int i;

    if(firstSeg >= 16)
    {
        printf("The XMC MPAX segment number %d >= 16, not supported.\n ", firstSeg);
        return;
    }

	if(gpCGEM_regs->MPLKSTAT&CSL_CGEM_MPLKSTAT_LK_MASK)
		unlock_mem_prot_regs();

	/*CAUTION:
	A MPAX segment can only be modified when there is no access to the space 
	of this segment. Any data in cache or prefetch buffer from the space of this 
	segment must be writeback and invalidated before the segment modification.	
	It is recommended to configure the MPAX at the very beginning of application
	software before any shared memory is used. Code and data for CorePac MPAX 
	configuration should be allocated in LL2.
	If a MPAX segment must be modified on-the-fly, the safer way is, to write 
	the new configuration to a unused higher segment, and then clear the old 
	segment. This is based on the fact that higher numbered segments take 
	precedence over lower numbered segments.	*/
	CACHE_wbInvAllL2(CACHE_WAIT);
	CSL_XMC_invalidatePrefetchBuffer();
	_mfence();
	_mfence(); 	//ensure all writeback invalidate have completed.

	for(i=numSegs-1; i>=0 ; i--)
    {   
		KeyStone_MPAX_seg_setup((MPAX_Regs *)&gpXMC_regs->XMPAX[firstSeg+i], 
			MPAX_cfg[i].BADDR, MPAX_cfg[i].RADDR, 
			MPAX_cfg[i].SegementSize, MPAX_cfg[i].AccessPermisionMask);
    }

	lock_mem_prot_regs();
}

/*****************************************************************************
 Prototype    : KeyStone_SMS_MPAX_setup
 Description  : configure multiple MPAX segments in SMS of MSMC with a conf-
                iguration table
 Input        : MPAX_Config MPAX_cfg[]  
                Uint32 firstSeg         
                Uint32 numSegs          
                Uint32 PrivID           
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_SMS_MPAX_setup(MPAX_Config MPAX_cfg[], 
	Uint32 firstSeg, Uint32 numSegs, Uint32 PrivID)
{
	int i;

	if(	gpMSMC_regs->SMS_MPAX_LCKSTAT&(1<<PrivID))
		CSL_MSMC_unlockSMS(PrivID);

	/*CAUTION:
	A MPAX segment can only be modified when there is no access to this segment. 
	It is recommended to configure the MPAX at the very beginning of application
	software before any shared memory is used. 
	If a MPAX segment must be modified on-the-fly, the safer way is, to write 
	the new configuration to a unused higher segment, and then clear the old 
	segment. This is based on the fact that higher numbered segments take 
	precedence over lower numbered segments.	*/
	for(i=numSegs-1; i>=0 ; i--)
		KeyStone_MPAX_seg_setup(
			(MPAX_Regs *)&gpMSMC_regs->SMS_MPAX_PER_PRIVID[PrivID].SMS[firstSeg+i], 
			MPAX_cfg[i].BADDR, MPAX_cfg[i].RADDR, 
			MPAX_cfg[i].SegementSize, MPAX_cfg[i].AccessPermisionMask);

	CSL_MSMC_lockSMS(PrivID);
}

/*****************************************************************************
 Prototype    : KeyStone_SES_MPAX_setup
 Description  : configure multiple MPAX segments in SES of MSMC with a conf-
                iguration table
 Input        : MPAX_Config MPAX_cfg[]  
                Uint32 firstSeg         
                Uint32 numSegs          
                Uint32 PrivID           
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_SES_MPAX_setup(MPAX_Config MPAX_cfg[], 
	Uint32 firstSeg, Uint32 numSegs, Uint32 PrivID)
{
	int i;

	if(	gpMSMC_regs->SES_MPAX_LCKSTAT&(1<<PrivID))
		CSL_MSMC_unlockSES(PrivID);

	/*CAUTION:
	A MPAX segment can only be modified when there is no access to this segment. 
	It is recommended to configure the MPAX at the very beginning of application
	software before any shared memory is used. 
	If a MPAX segment must be modified on-the-fly, the safer way is, to write 
	the new configuration to a unused higher segment, and then clear the old 
	segment. This is based on the fact that higher numbered segments take 
	precedence over lower numbered segments.	*/
	for(i=numSegs-1; i>=0 ; i--)
		KeyStone_MPAX_seg_setup(
			(MPAX_Regs *)&gpMSMC_regs->SES_MPAX_PER_PRIVID[PrivID].SES[firstSeg+i], 
			MPAX_cfg[i].BADDR, MPAX_cfg[i].RADDR, 
			MPAX_cfg[i].SegementSize, MPAX_cfg[i].AccessPermisionMask);

	CSL_MSMC_lockSES(PrivID);
}

/*****************************************************************************
 Prototype    : KeyStone_MSMC_MP_interrupt_en
 Description  : Enable MSMC Memory protection error interrupt for PrivIDs
                indicated by "PRIVID_MASK"
 Input        : Uint32 PRIVID_MASK  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/15
    Author       : Zhan
    Modification : Created function

*****************************************************************************/
void KeyStone_MSMC_MP_interrupt_en(Uint32 PRIVID_MASK)
{
	if(gpMSMC_regs->CFGLCKSTAT&CSL_MSMC_CFGLCKSTAT_WSTAT_MASK)
		CSL_MSMC_unlockNonMPAX();

    /*clear MP fault record*/
    gpMSMC_regs->SMPFCR = 1;

    /*clear interrupt error status flag*/
	gpMSMC_regs->SMIRC  = (PRIVID_MASK)<<CSL_MSMC_SMIRC_PFIC_SHIFT;

	//enable the interrupt
	gpMSMC_regs->SMIESTAT |= (PRIVID_MASK<<CSL_MSMC_SMIESTAT_PFIESTAT_SHIFT);

	CSL_MSMC_lockNonMPAX();
}
/*****************************************************************************
 Prototype    : memory_protection_exception_handler
 Description  : memory protection processing
 Input        : unsigned int MPFAR  
                unsigned int MPFSR  
 Output       : None
 Return Value : 
*****************************************************************************/
void memory_protection_exception_handler(unsigned int MPFAR, 
	unsigned int MPFSR)
{
	unsigned int master_id;

	if(0 == MPFSR)
		return;

	exception_record.status.ext_sts.info.memory.fault_address= MPFAR;
	exception_record.status.ext_sts.info.memory.fault_status.MPFSR= MPFSR;

	if (MPFSR & CSL_CGEM_L2MPFSR_LOCAL_MASK) {
		printf("  memory protection exception caused by local access at 0x%x\n", 
			MPFAR);
	}
	else
	{
		master_id = (MPFSR&CSL_CGEM_L2MPFSR_FID_MASK)>>
			CSL_CGEM_L2MPFSR_FID_SHIFT;

		printf("  memory protection exception caused by master with ID %d at 0x%x\n", 
			master_id, MPFAR);
	}
	
	if (MPFSR & CSL_CGEM_L2MPFSR_UX_MASK) {
		puts("  User Execute violation");
	}
	if (MPFSR & CSL_CGEM_L2MPFSR_UW_MASK) {
		puts("  User Write violation");
	}
	if (MPFSR & CSL_CGEM_L2MPFSR_UR_MASK) {
		puts("  User Read violation");
	}
	if (MPFSR & CSL_CGEM_L2MPFSR_SX_MASK) {
		puts("  Supervisor Execute violation");
	}
	if (MPFSR & CSL_CGEM_L2MPFSR_SW_MASK) {
		puts("  Supervisor Write violation");
	}
	if (MPFSR & CSL_CGEM_L2MPFSR_SR_MASK) {
		puts("  Supervisor Read violation");
	}
	
}

/*****************************************************************************
 Prototype    : KeyStone_MSMC_protection_exception_handler
 Description  : MSMC memory protection processing
 Input        : None
 Output       : None
 Return Value : 
*****************************************************************************/
void KeyStone_MSMC_protection_exception_handler()
{
	unsigned int master_id;
    unsigned int priv_id;
    unsigned int address;
    unsigned int NM;

	address = gpMSMC_regs->SMPFAR;
	
	master_id = (gpMSMC_regs->SMPFR&CSL_MSMC_SMPFR_FMSTID_MASK)>>
		CSL_MSMC_SMPFR_FMSTID_SHIFT;
    priv_id = (gpMSMC_regs->SMPFR&CSL_MSMC_SMPFR_FPID_MASK)>>
		CSL_MSMC_SMPFR_FPID_SHIFT;

	exception_record.status.ext_sts.info.memory.fault_address= address;
	exception_record.status.ext_sts.info.memory.fault_status.SMPFR= gpMSMC_regs->SMPFR;

    NM = (gpMSMC_regs->SMPFXR & CSL_MSMC_SMPFXR_NM_MASK) >> CSL_MSMC_SMPFXR_NM_SHIFT;

	printf("  memory protection exception caused by master %d (PrivID= %d) at address 0x%x\n", 
		master_id, priv_id, address);

    if(1 == NM)
    {
        printf("  Fault is caused by the address not matching any of the segment BADDR\n");        
    }

	if(gpMSMC_regs->CFGLCKSTAT&CSL_MSMC_CFGLCKSTAT_WSTAT_MASK)
	    CSL_MSMC_unlockNonMPAX();
    /*clear fault record*/
    gpMSMC_regs->SMPFCR = 1;
    /*clear interrupt error status flag*/
	gpMSMC_regs->SMIRC  = (1<<priv_id)<<CSL_MSMC_SMIRC_PFIC_SHIFT;
    CSL_MSMC_lockNonMPAX();            
}

/*==========Peripherals registers and internal data buffer MPU=============*/
CSL_MpuRegs * gpMPU_regs[8]= {
	(CSL_MpuRegs *)CSL_MPU_0_REGS,
	(CSL_MpuRegs *)CSL_MPU_1_REGS,
	(CSL_MpuRegs *)CSL_MPU_2_REGS,
	(CSL_MpuRegs *)CSL_MPU_3_REGS,

	//for C6670, TCI6614
	(CSL_MpuRegs *)(CSL_MPU_3_REGS+ 1*(CSL_MPU_1_REGS- CSL_MPU_0_REGS)),

	//for TCI6614 only
	(CSL_MpuRegs *)(CSL_MPU_3_REGS+ 2*(CSL_MPU_1_REGS- CSL_MPU_0_REGS)),
	(CSL_MpuRegs *)(CSL_MPU_3_REGS+ 3*(CSL_MPU_1_REGS- CSL_MPU_0_REGS)),
	(CSL_MpuRegs *)(CSL_MPU_3_REGS+ 4*(CSL_MPU_1_REGS- CSL_MPU_0_REGS))
};	

/*number of used MPU ranges*/
unsigned int gUsed_MPPA_ranges [8] = {0,0,0,0,0,0,0,0};

MPU_Addr gstruMpuAddrRange[] = 
{
        {0x01D00000, 0x026203FF},
        {0x34000000, 0x340BFFFF},
        {0x02A00000, 0x02ABFFFF},
        {0x02640000, 0x026407FF},
		//for C6670, TCI6614
        {0x01F80000, 0x0215FFFF},
		//for TCI6614
        {0x33600000, 0x337FFFFF},
        {0x00000000, 0xFFFFFFFF},
        {0x70000000, 0x7FFFFFFF}
};

/*****************************************************************************
 Prototype    : TN_MPU5_constant
 Description  : special intial constant for MPU5 on Turbo Nyquist
 Input        : None
 Output       : None
 Return Value : 
*****************************************************************************/
void TN_MPU5_constant()
{
	TDSP_Board_Type DSP_Board_Type = KeyStone_Get_dsp_board_type();

	/*For Turbo Nyquist, add following code to modify initial value,
	Or user can modify the initail values directly*/
	if(C6670_EVM== DSP_Board_Type)
	{
		gpMPU_regs[5]= (CSL_MpuRegs *)0x35000000;
		gstruMpuAddrRange[5].StartAddr= 0x35020000;
		gstruMpuAddrRange[5].EndAddr= 0x3521FFFF;
	}
}

/*****************************************************************************
 Prototype    : KeyStone_MPU_range_setup
 Description  : configure one range in peripheral MPU
 Input        : CSL_MpuProg_regionRegs *MPPA_regs  
                Uint32 uiStartAddress              
                Uint32 uiEndAddress                
                Uint32 AccessPermisionMask         
 Output       : None
 Return Value : 
*****************************************************************************/
void KeyStone_MPU_range_setup(CSL_MpuProg_regionRegs *MPPA_regs, 
	Uint32 uiStartAddress, Uint32 uiEndAddress, Uint32 AccessPermisionMask)
{
    unsigned int boundaryMask; 

	//the address must align to 1KB boundary on KeyStone DSPs
	boundaryMask= 0x3FF; 
	
    if(0 != (uiStartAddress&boundaryMask))
    {
    	printf("aligned start address 0x%x to 0x%x\n",
    		uiStartAddress,	uiStartAddress&(~boundaryMask));
    	uiStartAddress= uiStartAddress&(~boundaryMask);
    }

    MPPA_regs->PROG_START_ADDRESS = uiStartAddress;
    MPPA_regs->PROG_END_ADDRESS = uiEndAddress;   
    MPPA_regs->PROG_MPPA = AccessPermisionMask;
}

/*****************************************************************************
 Prototype    : KeyStone_MPU_setup
 Description  : peripherals MPU ranges configuration
 Input        : Uint32 uiMPU_num: number of the MPU to be setup
                MPU_Range_Config MPU_cfg[]: MPU ranges configuration table
                Uint32 numRangeCfg: number of ranges to be configured          
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/12/15
    Author       : Brighton Feng
    Modification : Created function
*****************************************************************************/
void KeyStone_MPU_setup(Uint32 uiMPU_num, 
	MPU_Range_Config MPU_cfg[], Uint32 numRangeCfg)
{
    int i;
    unsigned int mpuNumProgmableRange;
    CSL_MpuRegs * mpuRegs;

	/*For Turbo Nyquist, add following code to modify initial value,
	Or user can modify the initail values directly*/
	if(5==uiMPU_num)
		TN_MPU5_constant();

	mpuRegs= gpMPU_regs[uiMPU_num];

    mpuNumProgmableRange = (mpuRegs->CONFIG & CSL_MPU_CONFIG_NUM_PROG_MASK)>>CSL_MPU_CONFIG_NUM_PROG_SHIFT;
    if(mpuNumProgmableRange == 0)
    {   
        mpuNumProgmableRange = 16;
    }

	if(numRangeCfg>mpuNumProgmableRange)
    {
        printf("MPU %d programmable ranges %d < %d.\n", 
        	uiMPU_num, mpuNumProgmableRange, numRangeCfg);
        numRangeCfg=mpuNumProgmableRange;            
    }
    else if(numRangeCfg<mpuNumProgmableRange)
    {
        printf("MPU %d setup %d of %d ranges.\n", 
        	uiMPU_num, numRangeCfg, mpuNumProgmableRange);
    }

    for(i=0; i<numRangeCfg; i++)
    {
	    if((MPU_cfg[i].StartAddr < gstruMpuAddrRange[uiMPU_num].StartAddr) 
	      ||(MPU_cfg[i].EndAddr > gstruMpuAddrRange[uiMPU_num].EndAddr) )
	    {
	        printf("The configuration address is out of MPU %d protection range\n", 
	        	uiMPU_num);
	        continue;
	    }

        KeyStone_MPU_range_setup(&mpuRegs->PROG_REGION[i], 
            MPU_cfg[i].StartAddr, MPU_cfg[i].EndAddr, 
            MPU_cfg[i].AccessPermisionMask); 

    }

    //clear unused ranges
	for( ;i<mpuNumProgmableRange; i++)
	{
		mpuRegs->PROG_REGION[i].PROG_MPPA = 0;
	}

	//clear status
	mpuRegs->FAULT_CLEAR = 1;
	mpuRegs->INT_ENABLED_STATUS_CLEAR = 
		CSL_MPU_INT_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MASK
		|CSL_MPU_INT_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MASK;

	/* enable the interrupt */
	mpuRegs->INT_ENABLE = CSL_MPU_INT_ENABLE_ADDR_ERR_EN_MASK 
		| CSL_MPU_INT_ENABLE_PROT_ERR_EN_MASK;                

    return;
}

/*****************************************************************************
 Prototype    : KeyStone_MPU_MPPA_modify
 Description  : search the range which match a address and then modify
                the access permission of that range.
 Input        : Uint32 uiMPU_num: number of the MPU to be modifed  
                Uint32 uiAddress: address which need modify permision              
                Uint32 AccessPermisionMask: permission mask for that range         
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/12/13
    Author       : Brighton Feng
    Modification : Created function
*****************************************************************************/
void KeyStone_MPU_MPPA_modify(Uint32 uiMPU_num, 
	Uint32 uiAddress, Uint32 AccessPermisionMask)
{
    int i;
    unsigned int mpuNumProgmableRange;
    CSL_MpuRegs * mpuRegs;

	/*For Turbo Nyquist, add following code to modify initial value,
	Or user can modify the initail values directly*/
	if(5==uiMPU_num)
		TN_MPU5_constant();

	mpuRegs= gpMPU_regs[uiMPU_num];

    mpuNumProgmableRange = (mpuRegs->CONFIG & CSL_MPU_CONFIG_NUM_PROG_MASK)>>CSL_MPU_CONFIG_NUM_PROG_SHIFT;
    if(mpuNumProgmableRange == 0)
    {   
        mpuNumProgmableRange = 16;
    }

	/*search through all ranges*/
	for(i=0; i< mpuNumProgmableRange; i++)
	{
		/*match with one range*/
		if((uiAddress >= mpuRegs->PROG_REGION[i].PROG_START_ADDRESS) 
      		&&(uiAddress <= mpuRegs->PROG_REGION[i].PROG_END_ADDRESS))
      	{
      		mpuRegs->PROG_REGION[i].PROG_MPPA = AccessPermisionMask;
      		return;
      	}
	}

	printf("address 0x%08x does not match any range in MPU %d\n", 
		uiAddress, uiMPU_num);
    
    return;
}

/*****************************************************************************
 Prototype    : KeyStone_MPU_interrupts_enable
 Description  : enable the all MPU interrupts
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_MPU_interrupt_enable(Uint32 uiMPU_num)
{
	if((gpMPU_regs[uiMPU_num]->REVISION&0xFFFF0000)!=
		(CSL_MPU_REVISION_RESETVAL&0xFFFF0000))
	{	
		printf("Can't read MPU%d ID register, make sure corresponding power domain is enabled.", uiMPU_num);
		return;
	}
	
    gpMPU_regs[uiMPU_num]->FAULT_CLEAR = 1;
    gpMPU_regs[uiMPU_num]->INT_ENABLED_STATUS_CLEAR = 
    	CSL_MPU_INT_ENABLED_STATUS_CLEAR_ENABLED_ADDR_ERR_MASK
    	|CSL_MPU_INT_ENABLED_STATUS_CLEAR_ENABLED_PROT_ERR_MASK;
	gpMPU_regs[uiMPU_num]->INT_ENABLE = CSL_MPU_INT_ENABLE_ADDR_ERR_EN_MASK 
    	|CSL_MPU_INT_ENABLE_PROT_ERR_EN_MASK;                

}
void KeyStone_MPU_interrupts_enable()
{
	int i;
	TDSP_Board_Type DSP_Board_Type = KeyStone_Get_dsp_board_type();

	TN_MPU5_constant();
	
	for(i=0; i<4; i++)
	{
		KeyStone_MPU_interrupt_enable(i);
	}
	
	if((C6670_EVM== DSP_Board_Type)
		||(TCI6614_EVM== DSP_Board_Type))
	{
		for(i=4; i<6; i++)
		{
	    	/*MPU5 (for BCP) of TCI6614 is only accessible 
	    	when BCP is enabled through PSC*/
	    	if((5==i)&&(TCI6614_EVM== DSP_Board_Type)&&
		    	((CSL_PSC_getPowerDomainState(5) != PSC_PDSTATE_ON) ||
		        (CSL_PSC_getModuleState (12) != PSC_MODSTATE_ENABLE)))
			{
				puts("Enable power domain for MPU5 before configure it.");
		        continue;
		    }

			KeyStone_MPU_interrupt_enable(i);
		}
    }

	if(TCI6614_EVM== DSP_Board_Type)
	{
		for(i=6; i<8; i++)
		{
			KeyStone_MPU_interrupt_enable(i);
		}
	}
	
    return;
}

char * Peri_MPU_err_type_str[]=
{
    "User execution fault!",
    "User write fault!",
    "User read fault!",
    "Supervisor execution fault!",
    "Supervisor write fault!",
    "Supervisor read fault!"
};

char * Ns_str[]=
{
    "secure",
    "non-secure"
};
/*****************************************************************************
 Prototype    : KeyStone_peripherals_MPU_fault_status
 Description  : Print the MPU error information
 Input        : unsigned int uwFltStatus  
                unsigned int uwFltAddr    
 Output       : None
 Return Value : 
*****************************************************************************/
void KeyStone_peripherals_MPU_fault_status(unsigned int uwFltStatus, 
    unsigned int uwFltAddr)
{
    unsigned int MSTID;
    unsigned int PRIVID;
    unsigned int NS;
    unsigned int FaultType;
    unsigned int BitsCnt;
    
    MSTID = (uwFltStatus & CSL_MPU_FAULT_STATUS_MSTID_MASK)>>CSL_MPU_FAULT_STATUS_MSTID_SHIFT;
    PRIVID = (uwFltStatus & CSL_MPU_FAULT_STATUS_PRIVID_MASK)>>CSL_MPU_FAULT_STATUS_PRIVID_SHIFT;
    NS = (uwFltStatus & CSL_MPU_FAULT_STATUS_NS_MASK)>>CSL_MPU_FAULT_STATUS_NS_SHIFT;        
    printf("  The MSTID %d (PRIVID %d) triggered MPU error at 0x%x with %s access\n", 
    	MSTID, PRIVID, uwFltAddr, Ns_str[NS]);  

    FaultType = (uwFltStatus & CSL_MPU_FAULT_STATUS_FAULT_TYPE_MASK) >> CSL_MPU_FAULT_STATUS_FAULT_TYPE_SHIFT;
    if(1==(_dotpu4(_bitc4(FaultType), 0x01010101)))
    {
    	BitsCnt= 31 - _lmbd(1, FaultType);
        printf("  %s\n",Peri_MPU_err_type_str[BitsCnt]);
    }
    else if(0x3F == FaultType)
    {
        puts("  Relaxed cache line fill fault!");            
    }
    else if(0x12 == FaultType)
    {
        puts("  Relaxed cache write back fault!");                
    }    
}
/*****************************************************************************
 Prototype    : KeyStone_peripherals_MPU_excepiton_handler
 Description  : peripheral MPU processing
 Input        : Uint32 uwMpuNum  
 Output       : None
 Return Value : 
*****************************************************************************/
void KeyStone_peripherals_MPU_excepiton_handler(Uint32 uwMpuNum)
{
    Uint32 uwStatus;
    Uint32 uwFltAddr;
    Uint32 uwFltStatus;
	CSL_MpuRegs *pstruMpuRegs= gpMPU_regs[uwMpuNum];
	
    uwStatus = pstruMpuRegs->INT_ENABLED_STATUS_CLEAR;
    if(uwStatus & 0x2)
    {   
        printf("  MPU %d address violation error\n", uwMpuNum);
        pstruMpuRegs->INT_ENABLED_STATUS_CLEAR = 2;
    }        

    if(uwStatus & 0x1)
    {   
        printf("  MPU %d protection violation error\n", uwMpuNum);
        pstruMpuRegs->INT_ENABLED_STATUS_CLEAR = 1;
    }
      
    uwFltAddr = pstruMpuRegs->FAULT_ADDRESS;
    uwFltStatus = pstruMpuRegs->FAULT_STATUS;
	exception_record.status.ext_sts.info.memory.fault_address= uwFltAddr;
	exception_record.status.ext_sts.info.memory.fault_status.MPU_FAULT_STATUS= uwFltStatus;
    
    KeyStone_peripherals_MPU_fault_status(uwFltStatus,uwFltAddr);        
    pstruMpuRegs->FAULT_CLEAR = 1;

    pstruMpuRegs->EOI = 0;     
}


/*======================memory EDC=====================================*/
/*****************************************************************************
 Prototype    : KeyStone_SL2_EDC_enable
 Description  : Enable MSMC EDC
 Input        : scrubCnt, number of MSMC clock cycles between scrubbing
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_SL2_EDC_enable(Uint32 scrubCnt)
{
	if(gpMSMC_regs->CFGLCKSTAT&CSL_MSMC_CFGLCKSTAT_WSTAT_MASK)
		CSL_MSMC_unlockNonMPAX();

	/*Software must wait for the PRR (Parity RAM Ready) bit before making 
	the first read access to MSMC RAM after reset.*/
	while(0==(gpMSMC_regs->SMEDCC&CSL_MSMC_SMEDCC_PRR_MASK));

	/* set scrubbing period value */
	if(scrubCnt>255)
		scrubCnt= 255;
	CSL_MSMC_setCounterBankRefreshRead(scrubCnt); //the scrubbing engine works every scrubCnt*1024 cycle*/

	/* clear EDC errors and enable EDC event*/
	gpMSMC_regs->SMIRC = 0xf;
	gpMSMC_regs->SMIESTAT |= (CSL_MSMC_SMIESTAT_NCSIE_MASK
			           | CSL_MSMC_SMIESTAT_CSIE_MASK
			           | CSL_MSMC_SMIESTAT_NCEIE_MASK
			           | CSL_MSMC_SMIESTAT_CEIE_MASK);

	//enable SL2 EDC
	CSL_MSMC_setECM(1);

	CSL_MSMC_lockNonMPAX();
}

/*****************************************************************************
 Prototype    : KeyStone_SL2_EDC_interrupt_en
 Description  : Enable MSMC EDC error interrupt
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/15
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_SL2_EDC_interrupt_en()
{
	if(gpMSMC_regs->CFGLCKSTAT&CSL_MSMC_CFGLCKSTAT_WSTAT_MASK)
		CSL_MSMC_unlockNonMPAX();

	/* clear EDC errors*/
	gpMSMC_regs->SMIRC = 0xf;

	/* Enable EDC error interrupt */
	gpMSMC_regs->SMIESTAT |= (CSL_MSMC_SMIESTAT_NCSIE_MASK
			           | CSL_MSMC_SMIESTAT_CSIE_MASK
			           | CSL_MSMC_SMIESTAT_NCEIE_MASK
			           | CSL_MSMC_SMIESTAT_CEIE_MASK);

	CSL_MSMC_lockNonMPAX();
}

/*****************************************************************************
 Prototype    : LL2_EDC_setup
 Description  : Eenable LL2 EDC and scrub whole LL2
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/10
    Author       : Jane
    Modification : Created function

  2.Date         : 2012/10/20
    Author       : Brighton Feng

*****************************************************************************/
void LL2_EDC_setup()
{
	int i;
	unsigned int uiByteCnt= 512*1024;
	TDSP_Board_Type DSP_Board_Type;
	
	/* 1. Disable the EDC */
	CSL_CGEM_disableL2EDC();

	/* 2. Clear any EDC errors */
	CSL_CGEM_clearL2EDCErrorStatus(1, 1, 1, 1);

	/* 3. Memory Scrubbing with IDMA, generate the parity bits*/
	DSP_Board_Type = KeyStone_Get_dsp_board_type();
	if((DUAL_NYQUIST_EVM == DSP_Board_Type)
		||(C6670_EVM == DSP_Board_Type)
		||(TCI6614_EVM == DSP_Board_Type))
	{
		uiByteCnt= 1024*1024;
	}

	/*Each IDMA can transfer up to 65532 bytes,
	here we transfer 32KB each time*/
	for(i=0; i< (uiByteCnt>>15); i++)
	{
		IDMA_copy((0x00800000 + i*(1<<15)), (0x00800000 + i*(1<<15)), 
			(1<<15), DMA_WAIT);
	}

	/* 4. Enable the EDC*/
	CSL_CGEM_enableL2EDC();
	gpCGEM_regs->L2EDCEN= (1<<CSL_CGEM_L2EDCEN_DL2CEN_SHIFT)
		|(1<<CSL_CGEM_L2EDCEN_DL2SEN_SHIFT)
		|(1<<CSL_CGEM_L2EDCEN_PL2CEN_SHIFT)
		|(1<<CSL_CGEM_L2EDCEN_PL2SEN_SHIFT)
		|(1<<CSL_CGEM_L2EDCEN_SDMAEN_SHIFT);
	
}

Uint32 uiLL2_scrub_addr=0x800000;
/*****************************************************************************
 Prototype    : LL2_EDC_scrub
 Description  : scrub a block in LL2 for EDC. 

    Number of bytes must be multiple of 128 bits and less than 64KB.
This function should be called periodically, for example, 
if every 1 minute, call it with:	LL2_EDC_scrub(1024);
For 1MB LL2, the whole space will be scrubbed in 1024 minutes(17 hours)

 Input        : Uint32 uiByteCnt  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/20
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void LL2_EDC_scrub(Uint32 uiByteCnt)
{
	Uint32	uiLL2EndAddress= 0x00880000;
	TDSP_Board_Type DSP_Board_Type;

	uiByteCnt &= 0xFFF0;	//size must be multiple of 128 bits and less than 64KB

#if 1
	int i;
	volatile Uint32 * uipAddress= (volatile Uint32 *)uiLL2_scrub_addr;
	for(i=0; i< uiByteCnt/64; i++)
	{
		/*read one word to fetch a cache line, write to make it dirty*/
		*uipAddress= *uipAddress;
		uipAddress+= 16; 	//skip to the next cach line
	}
	CACHE_wbInvL1d((void *)uiLL2_scrub_addr, uiByteCnt, CACHE_NOWAIT);
#else 	//use IDMA ONLY for read ONLY space
	/*if IDMA scrub memory which is modifying by other masters at the same time, 
	there may be race condtion that the new value is overwritter by the IDMA 
	with old value.*/
	IDMA_copy(uiLL2_scrub_addr, uiLL2_scrub_addr, uiByteCnt, DMA_NO_WAIT);
#endif

	uiLL2_scrub_addr+= uiByteCnt;

	DSP_Board_Type = KeyStone_Get_dsp_board_type();
	if((DUAL_NYQUIST_EVM == DSP_Board_Type)
		||(C6670_EVM == DSP_Board_Type)
		||(TCI6614_EVM == DSP_Board_Type))
	{
		uiLL2EndAddress= 0x00900000;
	}

	//wrap back
	if(uiLL2_scrub_addr >= uiLL2EndAddress)
		uiLL2_scrub_addr=0x800000;
		
}

/*****************************************************************************
 Prototype    : L1P_EDC_setup
 Description  : enable L1P ED and scrub whole L1P
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/10
    Author       : Jane
    Modification : Created function

  2.Date         : 2012/10/30
    Author       : Brighton Feng
*****************************************************************************/
void L1P_EDC_setup()
{
	Uint32 preL1PMPPA[16];

	/* 1. Disable the EDC */
	CSL_CGEM_disablePMCErrorDetection();

	/* 2. Clear any EDC errors */
	CSL_CGEM_clearPMCErrorDetectionStatus(1, 1);

	/* 3. Memory Scrubbing with IDMA, generate the parity bits*/
	memcpy(preL1PMPPA, (void *)gpCGEM_regs->L1PMPPA, 64);//save protection attributes
	L1P_memory_protection_cfg(0xFFFF); //enable IDMA access to L1P
	IDMA_copy(0x00E00000, 0x00E00000, 32*1024, DMA_WAIT);
	L1_MPPA_setup(gpCGEM_regs->L1PMPPA, preL1PMPPA);//restore protection for L1

	/* 4. Enable the EDC*/
	CSL_CGEM_enablePMCErrorDetection();
}

char * LL2_EDC_victim_err_str="LL2 victims";
char * LL2_EDC_DMA_err_str=	"DMA access";
char * LL2_EDC_L1D_err_str=	"L1D access";
char * LL2_EDC_L1P_err_str=	"L1P access";

/*****************************************************************************
 Prototype    : LL2_EDC_handler
 Description  : LL2 EDC exception/interrupt handler
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void LL2_EDC_handler(Bool bCorrected)
{
	/* EDC error during the L1D access */
    Uint8  derr;
    /* EDC error during the L1P access */
    Uint8  perr;
    /* EDC error during the DMA access*/
    Uint8  dmaerr;
    /* EDC error during the L2 victim occurred */
    Uint8  verr;
    /* single bit or dual bit EDC error */
    Uint8  nerr;

    char *errStr;
    Uint32 errAddr;

	/* Get the all LL2 error status */
	CSL_CGEM_getL2EDCErrorStatus(&derr, &perr, &dmaerr, &verr, &nerr);

	if(derr|perr|dmaerr|verr)
	{
		errAddr= gpCGEM_regs->L2EDADDR&CSL_CGEM_L2EDADDR_ADDR_MASK;
		
		exception_record.status.ext_sts.info.memory.fault_address= errAddr;
		exception_record.status.ext_sts.info.memory.fault_status.L2EDSTAT= 
			gpCGEM_regs->L2EDSTAT;

		if(bCorrected)
		{
			printf("  LL2 EDC (correctable) at bit %d of ",(gpCGEM_regs->L2EDSTAT&
				CSL_CGEM_L2EDSTAT_BITPOS_MASK)>>CSL_CGEM_L2EDSTAT_BITPOS_SHIFT);

			//scrub 64 bytes including the error address to correct the error
			if(perr) //by L1P access
				IDMA_copy(errAddr&0xFFFFFFC0, errAddr&0xFFFFFFC0, 64, DMA_WAIT);
			else
			{
				volatile Uint32 * uipAddress= (volatile Uint32 *)(errAddr&0xFFFFFFC0);
				/*read one word into a cache line, and write to make it dirty, 
				which will be automatically written back sooner or later*/
				*uipAddress= *uipAddress;
			}
		}
		else
		{      
			printf("  LL2 EDC error (non-correctable) at ");
		}
		errStr = (char *)(perr * (Uint32)LL2_EDC_L1P_err_str
			+ derr * (Uint32)LL2_EDC_L1D_err_str
			+ verr * (Uint32)LL2_EDC_victim_err_str
			+ dmaerr * (Uint32)LL2_EDC_DMA_err_str);

		printf("address 0x%x caused by %s.\n",
			errAddr,
			errStr);        

		if(0==(gpCGEM_regs->L2EDADDR&CSL_CGEM_L2EDADDR_RAM_MASK))
		{      
			printf("  Error detected in Way %d of L2 cache\n",
				(gpCGEM_regs->L2EDADDR&CSL_CGEM_L2EDADDR_WAY_MASK)>>CSL_CGEM_L2EDADDR_WAY_SHIFT);
		}    
			
		printf("  total non-correctable error number= %d, total correctable error number= %d.\n",
			gpCGEM_regs->L2EDCNEC, gpCGEM_regs->L2EDCPEC);

		CSL_CGEM_clearL2EDCErrorStatus(derr, perr, dmaerr, verr);
	}
	else
	{   
		puts("  Enter LL2 EDC handler, but no error flag is set!");
	}
}
/*****************************************************************************
 Prototype    : L1P_ED_handler
 Description  : L1P EDC processing
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void L1P_ED_handler()
{
	Uint32 errAddr;
	Uint8 errRAM;

	/* EDC error during DMA access */
    Uint8  dmaerr;
    /* EDC error during program fetch access */
    Uint8  perr;

	/* Read PMC EDC status*/
	CSL_CGEM_getPMCErrorDetectionStatus(&dmaerr, &perr);

	if(perr|dmaerr)
	{
		CSL_CGEM_getPMCErrorInfo(&errAddr, &errRAM);

		exception_record.status.ext_sts.info.memory.fault_address= errAddr*32;
		exception_record.status.ext_sts.info.memory.fault_status.L1PEDSTAT= 
			gpCGEM_regs->L1PEDSTAT;
			
		if(errRAM)
			printf("  L1P RAM ");
		else
			printf("  L1P Cache ");

		printf("parity check error caused by ");

		if(perr == 1)
		{
			printf("program fetch ");

			/*flush wrong code in L1P. Code will be refetched from L2*/
			CACHE_invL1p((void *)NRP, 64, CACHE_WAIT);
		}
		else if(dmaerr == 1)
		{
			printf("DMA ");
		}
		printf("at address 0x%x\n", errAddr*32);

		CSL_CGEM_clearPMCErrorDetectionStatus(dmaerr,perr);
	}
}


/*****************************************************************************
 Prototype    : KeyStone_SL2_EDC_handler
 Description  : SL2 EDC Processing
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void KeyStone_SL2_EDC_handler()
{
	/* EDC correctable error during scrubbing cycle */
    Uint8  cses;
	/* EDC non-correctable error during scrubbing cycle */
    Uint8  ncses;
    /* EDC correctable error during SRAM access*/
    Uint8  cees;
    /* EDC non-correctable error during SRAM access*/
    Uint8  ncees;
    /* protection fault status*/
    Uint16  pfeStat;

    /*  error address  */
    Uint32 errAddr, bitPos, PrivID;

	if(gpMSMC_regs->CFGLCKSTAT&CSL_MSMC_CFGLCKSTAT_WSTAT_MASK)
		CSL_MSMC_unlockNonMPAX();

    CSL_MSMC_getPendingInterrupts(&pfeStat, &cees, &ncees, &cses, &ncses);

	exception_record.status.ext_sts.info.memory.fault_status.SMESTAT= 
		gpMSMC_regs->SMESTAT;
		
	if((cses == 1)||(ncses == 1))
	{
		if(cses == 1)
		{
			/*scrubbing engine report address offset from 0*/
			errAddr = (gpMSMC_regs->SMCEA&0xFFFFFF)+0xc000000;
			exception_record.status.ext_sts.info.memory.fault_address= errAddr;
			
			bitPos = (gpMSMC_regs->SMCEA&CSL_MSMC_SMCEA_ESYN_MASK)
				>>CSL_MSMC_SMCEA_ESYN_SHIFT;
			printf("SL2 Correctable error occurred at bit %d of address 0x%x by scrubbing\n", 
				bitPos, errAddr);
		}
		 if(ncses == 1)
		{
			/*scrubbing engine report address offset from 0*/
			errAddr = gpMSMC_regs->SMNCEA+0xc000000;
			exception_record.status.ext_sts.info.memory.fault_address= errAddr;
			
			printf("SL2 Non-correctable error occurred at address 0x%x by scrubbing\n", errAddr);
		}
		printf("%d correctable errors, %d non-correctable errors occurred during scrubbing.\n",
			(gpMSMC_regs->SMSECC&CSL_MSMC_SMSECC_SCEC_MASK)
				>>CSL_MSMC_SMSECC_SCEC_SHIFT,
			(gpMSMC_regs->SMSECC&CSL_MSMC_SMSECC_SNCEC_MASK)
				>>CSL_MSMC_SMSECC_SNCEC_SHIFT);
	}
	if(cees == 1)
	{
		volatile Uint32 scrubValue;
		
		errAddr =  gpMSMC_regs->SMCERRAR;
		exception_record.status.ext_sts.info.memory.fault_address= errAddr;

		//scrub the address to correct the error
		scrubValue= *(volatile Uint32 *)errAddr; //touch to cach
		*(volatile Uint32 *)errAddr= scrubValue; //make cache dirty
		CACHE_wbInvL2((void *)errAddr, 32, CACHE_WAIT);
		
		bitPos = (gpMSMC_regs->SMCERRXR&CSL_MSMC_SMCERRXR_ESYN_MASK)
			>>CSL_MSMC_SMCERRXR_ESYN_SHIFT;
		PrivID = (gpMSMC_regs->SMCERRXR&CSL_MSMC_SMCERRXR_SEPID_MASK)
			>>CSL_MSMC_SMCERRXR_SEPID_SHIFT;
		printf("SL2 Correctable error occurred at bit %d of address 0x%x by PrivID %d ", 
			bitPos, errAddr, PrivID);
		if(gpMSMC_regs->SMCERRXR&CSL_MSMC_SMCERRXR_SER_MASK)
			printf("(not from C66x CorePacs)\n");
		else
			printf("(from C66x CorePacs)\n");
	}
	if(ncees ==1)
	{
		errAddr =  gpMSMC_regs->SMNCERRAR;
		exception_record.status.ext_sts.info.memory.fault_address= errAddr;
		
		PrivID = (gpMSMC_regs->SMNCERRXR&CSL_MSMC_SMNCERRXR_SEPID_MASK)
			>>CSL_MSMC_SMNCERRXR_SEPID_SHIFT;
		printf("SL2 Non-correctable error occurred at address 0x%x by PrivID %d ", 
			errAddr, PrivID);
		if(gpMSMC_regs->SMNCERRXR&CSL_MSMC_SMNCERRXR_SER_MASK)
			printf("(not from C66x CorePacs)\n");
		else
			printf("(from C66x CorePacs)\n");
	}

	/* clear EDC error status  */
	CSL_MSMC_clearRawInterruptStatus(0, cees,ncees, cses, ncses);

	CSL_MSMC_lockNonMPAX();
}

/*===============================Exception=============================*/
//data structure to save exception info
Exception_Record exception_record;

/*some exception events routed from CIC to INTC and then to exception moduel,
all these events are routed to one input of INTC*/
Uint32 guwIntcCICExcEvtIdx= 95; /*INTC event number mapping to CIC exception events*/
Uint32 gCIC_EXC_out_num = 15; 	//CIC output event number
Uint32 gCIC_EXC_EN_MASK[8]= {0,0,0,0,0,0,0,0};
/*****************************************************************************
 Prototype    : KeyStone_CIC_exception_events_mapping
 Description  : CIC exception event mapping to the NMI external exception
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/5
    Author       : Brighton Feng
    Modification : Created function

  2.Date         : 2012/10/20
    Author       : Zhan
    Modification : Add event for TCI6614

  3.Date         : 2012/10/28
    Author       : Brighton Feng
*****************************************************************************/
void KeyStone_CIC_exception_events_mapping(void)
{
	TDSP_Board_Type DSP_Board_Type= KeyStone_Get_dsp_board_type();

#if 1
	if(C6670_EVM==DSP_Board_Type
		||DUAL_NYQUIST_EVM==DSP_Board_Type
		||TCI6614_EVM==DSP_Board_Type)
	{	
		gCIC_EXC_out_num= 15+16*DNUM;
	}
	else if(C6678_EVM==DSP_Board_Type)
	{	
		if(DNUM<4)
			gCIC_EXC_out_num= 7+8*DNUM;
		else
		{
			gCIC_EXC_out_num= 7+8*(DNUM-4);
			gpCIC_regs= gpCIC1_regs;
		}
	}
	else
	{
		puts("Unknown DSP board type!");
		return;
	}	
#endif

	/*-----------------------CP_INTC configuration---------------------*/
	/* Disable Global host interrupts. */
	gpCIC_regs->GLOBAL_ENABLE_HINT_REG= 0;

	/* route following system events to CIC out (event 22 of INTC), and then to exception
	TCI6614, C6670, C6678:
	CIC: 0 EDMA3CC1 EDMACC_ERRINT EDMA3CC1 error interrupt
	CIC: 2 EDMA3CC1 EDMATC_ERRINT0 EDMA3CC1 EDMA3TC0 error interrupt
	CIC: 3 EDMA3CC1 EDMATC_ERRINT1 EDMA3CC1 EDMA3TC1 error interrupt
	CIC: 4 EDMA3CC1 EDMATC_ERRINT2 EDMA3CC1 EDMA3TC2 error interrupt
	CIC: 5 EDMA3CC1 EDMATC_ERRINT3 EDMA3CC1 EDMA3TC3 error interrupt
	CIC: 16 EDMA3CC2 EDMACC_ERRINT EDMA3CC2 error interrupt
	CIC: 18 EDMA3CC2 EDMATC_ERRINT0 EDMA3CC2 EDMA3TC0 error interrupt
	CIC: 19 EDMA3CC2 EDMATC_ERRINT1 EDMA3CC2 EDMA3TC1 error interrupt
	CIC: 20 EDMA3CC2 EDMATC_ERRINT2 EDMA3CC2 EDMA3TC2 error interrupt
	CIC: 21 EDMA3CC2 EDMATC_ERRINT3 EDMA3CC2 EDMA3TC3 error interrupt
	CIC: 32 EDMA3CC0 EDMACC_ERRINT EDMA3CC0 error interrupt
	CIC: 34 EDMA3CC0 EDMATC_ERRINT0 EDMA3CC0 EDMA3TC0 error interrupt
	CIC: 35 EDMA3CC0 EDMATC_ERRINT1 EDMA3CC0 EDMA3TC1 error interrupt
	CIC: 99 MSMC_dedc_nc_error Non-correctable soft error detected on SRAM read
	CIC: 100 MSMC_scrub_nc_error Non-correctable soft error detected during scrub cycle
	CIC: 102 MSMC_mpf_error8 Memory protection fault indicators for each system master PrivID
	CIC: 103 MSMC_mpf_error9 Memory protection fault indicators for each system master PrivID
	CIC: 104 MSMC_mpf_error10 Memory protection fault indicators for each system master PrivID
	CIC: 105 MSMC_mpf_error11 Memory protection fault indicators for each system master PrivID
	CIC: 106 MSMC_mpf_error12 Memory protection fault indicators for each system master PrivID
	CIC: 107 MSMC_mpf_error13 Memory protection fault indicators for each system master PrivID
	CIC: 108 MSMC_mpf_error14 Memory protection fault indicators for each system master PrivID
	CIC: 109 MSMC_mpf_error15 Memory protection fault indicators for each system master PrivID
	CIC: 110 DDR3_ERR DDR3 ECC Error Interrupt
	TCI6614, C6670:
	CIC: 170 MSMC_mpf_error4 Memory protection fault indicators for each system master PrivID
	CIC: 171 MSMC_mpf_error5 Memory protection fault indicators for each system master PrivID
	CIC: 172 MSMC_mpf_error6 Memory protection fault indicators for each system master PrivID
	CIC: 173 MSMC_mpf_error7 Memory protection fault indicators for each system master PrivID
	*/
	KeyStone_CIC_event_map(gpCIC_regs, 0 , gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 2 , gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 3 , gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 4 , gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 5 , gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 16, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 18, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 19, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 20, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 21, gCIC_EXC_out_num);
	gCIC_EXC_EN_MASK[0] |=  
                 (1<<0 )
                |(1<<2 )
                |(1<<3 )
                |(1<<4 )
                |(1<<5 )
                |(1<<16)
                |(1<<18)
                |(1<<19)
                |(1<<20)
                |(1<<21);
		
	KeyStone_CIC_event_map(gpCIC_regs, 32, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 34, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 35, gCIC_EXC_out_num);
	gCIC_EXC_EN_MASK[1] |=  
                 (1<<(32-32))
                |(1<<(34-32))
                |(1<<(35-32));

	KeyStone_CIC_event_map(gpCIC_regs, 99, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 100, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 102, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 103, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 104, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 105, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 106, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 107, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 108, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 109, gCIC_EXC_out_num);
	KeyStone_CIC_event_map(gpCIC_regs, 110, gCIC_EXC_out_num);
	gCIC_EXC_EN_MASK[3] |=  
                 (1<<(99 -32*3))
                |(1<<(100-32*3))
                |(1<<(102-32*3))
                |(1<<(103-32*3))
                |(1<<(104-32*3))
                |(1<<(105-32*3))
                |(1<<(106-32*3))
                |(1<<(107-32*3))
                |(1<<(108-32*3))
                |(1<<(109-32*3))
                |(1<<(110-32*3));

	if(C6670_EVM==DSP_Board_Type
		||DUAL_NYQUIST_EVM==DSP_Board_Type
		||TCI6614_EVM==DSP_Board_Type)
	{	
		KeyStone_CIC_event_map(gpCIC_regs, 170, gCIC_EXC_out_num);
		KeyStone_CIC_event_map(gpCIC_regs, 171, gCIC_EXC_out_num);
		KeyStone_CIC_event_map(gpCIC_regs, 172, gCIC_EXC_out_num);
		KeyStone_CIC_event_map(gpCIC_regs, 173, gCIC_EXC_out_num);
		gCIC_EXC_EN_MASK[5] |=  
	                 (1<<(170-32*5))
	                |(1<<(171-32*5))
	                |(1<<(172-32*5))
	                |(1<<(173-32*5)); 
	}
    
    /* ----------- Mapping MPU interrupt for different chips start -----------------------*/
    if(C6670_EVM==DSP_Board_Type
		||DUAL_NYQUIST_EVM==DSP_Board_Type
		||C6678_EVM==DSP_Board_Type)
    {
    /*  route the following system events to CIC out
        CIC: 90 MPU0 addressing violation interrupt and protection violation interrupt 
    	CIC: 92 MPU1 addressing violation interrupt and protection violation interrupt
    	CIC: 94 MPU2 addressing violation interrupt and protection violation interrupt
    	CIC: 96 MPU3 addressing violation interrupt and protection violation interrupt     	
    */
        KeyStone_CIC_event_map(gpCIC_regs, 90, gCIC_EXC_out_num);
		KeyStone_CIC_event_map(gpCIC_regs, 92, gCIC_EXC_out_num);
		KeyStone_CIC_event_map(gpCIC_regs, 94, gCIC_EXC_out_num);
		KeyStone_CIC_event_map(gpCIC_regs, 96, gCIC_EXC_out_num);
		gCIC_EXC_EN_MASK[2] |=  
	                  (1<<(90 -32*2))
	                 |(1<<(92 -32*2))
	                 |(1<<(94 -32*2));
		gCIC_EXC_EN_MASK[3] |=  
	                 (1<<(96 -32*3));

        /* 6618_6670 only */
        if(C6670_EVM==DSP_Board_Type
		||DUAL_NYQUIST_EVM==DSP_Board_Type)
        {
        /*
            CIC: 174 MPU4 addressing violation interrupt and protection violation interrupt 
            CIC: 180 MPU5 addressing violation interrupt and protection violation interrupt
        */        
            KeyStone_CIC_event_map(gpCIC_regs, 174, gCIC_EXC_out_num);
		    KeyStone_CIC_event_map(gpCIC_regs, 180, gCIC_EXC_out_num);
			gCIC_EXC_EN_MASK[5] |=  
		                 (1<<(174-32*5))
		                |(1<<(180-32*5)); 
        }
    }

    if(TCI6614_EVM==DSP_Board_Type)
    {
    /*  route the following system events to CIC out
        CIC: 23 MPU0~7 addressing violation interrupt combine output 
    	CIC: 37 MPU0~7 protection violation interrupt combine output    	
    */
        KeyStone_CIC_event_map(gpCIC_regs, 23, gCIC_EXC_out_num);
	    KeyStone_CIC_event_map(gpCIC_regs, 37, gCIC_EXC_out_num);
		gCIC_EXC_EN_MASK[0] |=  
	                  (1<<23);
		gCIC_EXC_EN_MASK[1] |=  
	                  (1<<(37 -32));
        
    }
    /* ----------- Mapping MPU interrupt for different chips end -----------------------*/

	/* Enable Global host interrupts. */
	gpCIC_regs->GLOBAL_ENABLE_HINT_REG= 1;

}
/*****************************************************************************
 Prototype    : KeyStone_Exception_cfg
 Description  : Config the system  err and external exception to generate the NMI.
                Call this function as last step after all 
                configuration/initialization complete
 Input        : Bool bGlobalExceptionMaster. If TRUE, the global exception events 
                from CIC will be routed to exception model of this CPU core.
 Output       : None
 Return Value : 
*****************************************************************************/
void KeyStone_Exception_cfg(Bool bGlobalExceptionMaster)
{

	puts("Enable Exception handling...");

	TSCL = 0; 	/* Enable the TSC */

	memset(&exception_record, 0, sizeof(exception_record));
#if 0
	 /*Clear all CPU events*/
	gpCGEM_regs->EVTCLR[0]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[1]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[2]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[3]= 	0xFFFFFFFF;
#endif
	/*clear memory fault*/
	gpCGEM_regs->L1PMPFCR = 1;
	gpCGEM_regs->L1DMPFCR = 1;
	gpCGEM_regs->L2MPFCR = 1;
	gpXMC_regs->XMPFCR = 1;

	/*clear configuration bus error*/
	gpCGEM_regs->ICFGMPFCR= 1;
	gpCGEM_regs->ECFGERRCLR= 1;

	/* clear the MDMAERR */
	gpCGEM_regs->MDMAERRCLR = 1;

	/*clear interrupt drop staus*/
	gpCGEM_regs->INTXCLR = 1;

	gpCGEM_regs->INTDMASK= ~IER; /*only monitor drop of enabled interrupts*/

	/*enable events:
	10 MSMC_mpf_error_n MSMC Memory protection fault  caused by local CorePac
	96 INTERR Dropped CPU interrupt event
	97 EMC_IDMAERR Invalid IDMA parameters
	110 MDMAERREVT XMC VBUSM error event
	113 PMC_ED Single bit error detected during DMA accesses L1P
	117 UMC_ED2 Uncorrected bit error detected LL2
	119 SYS_CMPA CPU Memory Protection Fault for local configuration of INTC and power control
	120 PMC_CMPA CPU memory protection fault for L1P
	121 PMC_DMPA DMA memory protection fault for L1P
	122 DMC_CMPA CPU memory protection fault for L1D (and other memory read finally goes through the L1D controller)
	123 DMC_DMPA DMA memory protection fault for L1D
	124 UMC_CMPA CPU memory protection fault for LL2
	125 UMC_DMPA DMA memory protection fault for LL2
	126 EMC_CMPA CPU memory protection fault for other local configuration space between 0x01000000 - 0x01BFFFFF 
	127 EMC_BUSERR Bus Error Interrupt for global configuration space between 0x01C00000 - 0x07FFFFFF 
	*/
	gpCGEM_regs->EXPMASK[0]= ~(1<<CSL_GEM_MSMC_MPF_ERRORN);
	gpCGEM_regs->EXPMASK[1]= 0xFFFFFFFF;
	gpCGEM_regs->EXPMASK[2]= 0xFFFFFFFF;
	gpCGEM_regs->EXPMASK[3]= ~((1<<(CSL_GEM_INTERR - 96))|
		(1<<(CSL_GEM_EMC_IDMAERR-96))|
		(1<<(CSL_GEM_MDMAERREVT-96))|
		(1<<(CSL_GEM_PMC_ED-96))|
		(1<<(CSL_GEM_UMC_ED2-96))|
		(1<<(CSL_GEM_SYS_CMPA-96))|
		(1<<(CSL_GEM_PMC_CMPA-96))|
		(1<<(CSL_GEM_PMC_DMPA-96))|
		(1<<(CSL_GEM_DMC_CMPA-96))|
		(1<<(CSL_GEM_DMC_DMPA-96))|
		(1<<(CSL_GEM_UMC_CMPA-96))|
		(1<<(CSL_GEM_UMC_DMPA-96))|
		(1<<(CSL_GEM_EMC_CMPA-96))|
		(1<<(CSL_GEM_EMC_BUSERR-96)));


	if(bGlobalExceptionMaster)
	{
		/*enable exception events routed from CIC,
		please note, this should be only configured for one CPU*/
		KeyStone_CIC_exception_events_mapping();
		gpCGEM_regs->EXPMASK[guwIntcCICExcEvtIdx>>5] &= (~(1<<(guwIntcCICExcEvtIdx&0x1F)));        
	}

	/*clear exception flag*/
	ECR = EFR;
	IERR = 0; 
    
	/*Eanble external exception, global exception enable*/
	TSR = TSR|
		(1<<CSL_CHIP_TSR_XEN_SHIFT)|
		(1<<CSL_CHIP_TSR_GEE_SHIFT)|
		(1<<CSL_CHIP_TSR_GIE_SHIFT);

	/*enable NMI exception*/
	IER = IER|(1<<CSL_CHIP_IER_NMI_SHIFT);
	
}

char * bus_err_stat_str[]=
{
	"unrecognized RID/WID (should cause error to be latched)",
	"Addressing error",
	"Privilege error",
	"Timeout error",
	"Data error",
	"Reserved error",
	"Reserved error",
	"Exclusive - operation failure"
};
/*****************************************************************************
 Prototype    : Bus_error_handler
 Description  : System bus error processing
 Input        : unsigned int ERR_REG  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2012/10/25
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void Bus_error_handler(unsigned int ERR_REG)
{
	unsigned int err, stat;

	if(0 == ERR_REG)
		return;

	exception_record.status.ext_sts.info.memory.BUS_ERROR= ERR_REG;

	err= (ERR_REG & CSL_CGEM_MDMAERR_ERR_MASK)>>CSL_CGEM_MDMAERR_ERR_SHIFT;
	if (1==err) {
		puts("  MDMA read status error detected");
	}
	else if (2==err) {
		puts("  MDMA write status error detected");
	}
	else if (3==err) {
		puts("  CFG read status error detected");
	}
	else if (4==err) {
		puts("  CFG write status error detected");
	}

	printf("  XID (Transaction ID)= %d\n", 
		(ERR_REG & CSL_CGEM_MDMAERR_XID_MASK)>>CSL_CGEM_MDMAERR_XID_SHIFT);	

	stat= (ERR_REG & CSL_CGEM_MDMAERR_STAT_MASK)>>CSL_CGEM_MDMAERR_STAT_SHIFT;
	printf("  %s\n", bus_err_stat_str[stat]);
}

/*****************************************************************************
 Prototype    : KeyStone_CIC_EXC_handler
 Description  : This function handle the exception events from CIC
 Input        : void
 Output       : None
 Return Value : void
 
  History        :
  1.Date         : 2012/10/18
    Author       : Zhan
    Modification : Created function

  2.Date         : 2012/10/28
    Author       : Brighton Feng
    Modification : Add EDMA error processing

*****************************************************************************/
void KeyStone_CIC_EXC_handler()
{
    int i;
    Uint32 status[4], status5 = 0;
    
	TDSP_Board_Type DSP_Board_Type;

	DSP_Board_Type= KeyStone_Get_dsp_board_type();

    /*Step1: Disable CIC host interrupt*/
    KeyStone_CIC_disable_host_int(gpCIC_regs, gCIC_EXC_out_num);

	status[0]= gpCIC_regs->ENA_STATUS_REG[0]&gCIC_EXC_EN_MASK[0];
	status[1]= gpCIC_regs->ENA_STATUS_REG[1]&gCIC_EXC_EN_MASK[1];
	status[2]= gpCIC_regs->ENA_STATUS_REG[2]&gCIC_EXC_EN_MASK[2];
	status[3]= gpCIC_regs->ENA_STATUS_REG[3]&gCIC_EXC_EN_MASK[3];
	exception_record.status.ext_sts.CIC_STATUS[0]= status[0];
	exception_record.status.ext_sts.CIC_STATUS[1]= status[1];
	exception_record.status.ext_sts.CIC_STATUS[2]= status[2];
	exception_record.status.ext_sts.CIC_STATUS[3]= status[3];

	/*Step2: clear system events*/
	gpCIC_regs->ENA_STATUS_REG[0]= status[0];
	gpCIC_regs->ENA_STATUS_REG[1]= status[1];
	gpCIC_regs->ENA_STATUS_REG[2]= status[2];
	gpCIC_regs->ENA_STATUS_REG[3]= status[3];

    /* The different device INTC number is different, if read the non-exist space will 
        trigger the L1D memory protection error.
    */
	if((C6670_EVM == DSP_Board_Type)
		||(DUAL_NYQUIST_EVM == DSP_Board_Type)
		||(TCI6614_EVM == DSP_Board_Type))
	{
		status5  = gpCIC_regs->ENA_STATUS_REG[5]&gCIC_EXC_EN_MASK[5];
		exception_record.status.ext_sts.CIC_STATUS[5]= status5;

		/*Step2: clear system events*/
		gpCIC_regs->ENA_STATUS_REG[5]= status5  ;
	}

	/*----------------------------EDMA error-----------------------------*/
	/*
	CIC: 0 EDMA3CC1 EDMACC_ERRINT EDMA3CC1 error interrupt
	CIC: 2 EDMA3CC1 EDMATC_ERRINT0 EDMA3CC1 EDMA3TC0 error interrupt
	CIC: 3 EDMA3CC1 EDMATC_ERRINT1 EDMA3CC1 EDMA3TC1 error interrupt
	CIC: 4 EDMA3CC1 EDMATC_ERRINT2 EDMA3CC1 EDMA3TC2 error interrupt
	CIC: 5 EDMA3CC1 EDMATC_ERRINT3 EDMA3CC1 EDMA3TC3 error interrupt*/
	if(status[0]&0x3D)
		EDMA_error_handler(1, status[0]&0x3D);

    /*
	CIC: 16 EDMA3CC2 EDMACC_ERRINT EDMA3CC2 error interrupt
	CIC: 18 EDMA3CC2 EDMATC_ERRINT0 EDMA3CC2 EDMA3TC0 error interrupt
	CIC: 19 EDMA3CC2 EDMATC_ERRINT1 EDMA3CC2 EDMA3TC1 error interrupt
	CIC: 20 EDMA3CC2 EDMATC_ERRINT2 EDMA3CC2 EDMA3TC2 error interrupt
	CIC: 21 EDMA3CC2 EDMATC_ERRINT3 EDMA3CC2 EDMA3TC3 error interrupt*/
	if((status[0]>>16)&0x3D)
		EDMA_error_handler(2, (status[0]>>16)&0x3D);
    
	/*
	CIC: 32 EDMA3CC0 EDMACC_ERRINT EDMA3CC0 error interrupt
	CIC: 34 EDMA3CC0 EDMATC_ERRINT0 EDMA3CC0 EDMA3TC0 error interrupt
	CIC: 35 EDMA3CC0 EDMATC_ERRINT1 EDMA3CC0 EDMA3TC1 error interrupt*/
	if(status[1]&0xD)
		EDMA_error_handler(0, status[1]&0xD);

	/*----------------------------MPU error-----------------------------*/
	if(TCI6614_EVM == DSP_Board_Type)
	{
        //CIC: 23 MPU0~7 addressing violation interrupt combine output 
    	//CIC: 37 MPU0~7 protection violation interrupt combine output    	
		if((status[0]&(1<<23))||(status[1]&(1<<(37-32))))
		{
		    for(i=0; i<8; i++)
		    {
		    	/*MPU5 (for BCP) of TCI6614 is only accessible 
		    	when BCP is enabled through PSC*/
		    	if((5==i)&&
			    	((CSL_PSC_getPowerDomainState(5) != PSC_PDSTATE_ON) ||
			        (CSL_PSC_getModuleState (12) != PSC_MODSTATE_ENABLE)))
			        continue;
			        
		        if(gpMPU_regs[i]->INT_RAW_STATUS_SET & 0x3)
		        {   
		            KeyStone_peripherals_MPU_excepiton_handler(i);
		        }
		    }

		    /*The MPU events in TCI6614 are different from other KeyStone 
		    devices. All the MPU0~7 events are combined into single event 
		    and connected to the CIC0 as one system event.
			We have to clear the MPU event flag at the source level first 
			and then are able to clear the CIC flags because the INTD for the 
			MPU events is for the combination purpose but do not convert 
			the level interrupt to pulse.*/
			/*clear system events*/
			gpCIC_regs->ENA_STATUS_REG[0]= status[0];
			gpCIC_regs->ENA_STATUS_REG[1]= status[1];
		}
	}
	else
	{
        //CIC: 90 MPU0 addressing violation interrupt and protection violation interrupt 
		if(status[2]&(1<<(90-64)))
		{
			KeyStone_peripherals_MPU_excepiton_handler(0);
		}
    	//CIC: 92 MPU1 addressing violation interrupt and protection violation interrupt
		if(status[2]&(1<<(92-64)))
		{
			KeyStone_peripherals_MPU_excepiton_handler(1);
		}
    	//CIC: 94 MPU2 addressing violation interrupt and protection violation interrupt
		if(status[2]&(1<<(94-64)))
		{
			KeyStone_peripherals_MPU_excepiton_handler(2);
		}
    	//CIC: 96 MPU3 addressing violation interrupt and protection violation interrupt     	
		if(status[3]&(1<<(96-96)))
		{
			KeyStone_peripherals_MPU_excepiton_handler(3);
		}

		if((C6670_EVM == DSP_Board_Type)
			||(DUAL_NYQUIST_EVM == DSP_Board_Type))
		{
            //CIC: 174 MPU4 addressing violation interrupt and protection violation interrupt 
            //CIC: 180 MPU5 addressing violation interrupt and protection violation interrupt
			if(status5&(1<<(174-160)))
			{
				KeyStone_peripherals_MPU_excepiton_handler(4);
			}
			if(status5&(1<<(180-160)))
			{
				KeyStone_peripherals_MPU_excepiton_handler(5);
			}
		}
	}
    
	/*----------------------------MSMC error-----------------------------*/
	//CIC: 99 MSMC_dedc_nc_error Non-correctable (2-bit) soft error detected on SRAM read
	if(status[3]&(1<<(99-96)))
	{
		KeyStone_SL2_EDC_handler();
	}
	//CIC: 100 MSMC_scrub_nc_error Non-correctable (2-bit) soft error detected during scrub cycle
	if(status[3]&(1<<(100-96)))
	{
		KeyStone_SL2_EDC_handler();
	}

	/*
	CIC: 102 MSMC_mpf_error8 Memory protection fault indicators for each system master PrivID
	CIC: 103 MSMC_mpf_error9 Memory protection fault indicators for each system master PrivID
	CIC: 104 MSMC_mpf_error10 Memory protection fault indicators for each system master PrivID
	CIC: 105 MSMC_mpf_error11 Memory protection fault indicators for each system master PrivID
	CIC: 106 MSMC_mpf_error12 Memory protection fault indicators for each system master PrivID
	CIC: 107 MSMC_mpf_error13 Memory protection fault indicators for each system master PrivID
	CIC: 108 MSMC_mpf_error14 Memory protection fault indicators for each system master PrivID
	CIC: 109 MSMC_mpf_error15 Memory protection fault indicators for each system master PrivID*/
	if((status[3]>>(102-96))&0xFF)
		KeyStone_MSMC_protection_exception_handler();

	if((C6670_EVM == DSP_Board_Type)
		||(DUAL_NYQUIST_EVM == DSP_Board_Type)
		||(TCI6614_EVM == DSP_Board_Type))
	{
		/*
		CIC: 170 MSMC_mpf_error4 Memory protection fault indicators for each system master PrivID
		CIC: 171 MSMC_mpf_error5 Memory protection fault indicators for each system master PrivID
		CIC: 172 MSMC_mpf_error6 Memory protection fault indicators for each system master PrivID
		CIC: 173 MSMC_mpf_error7 Memory protection fault indicators for each system master PrivID*/
		if((status5>>(170-160))&0xF)
			KeyStone_MSMC_protection_exception_handler();
	
	}

	/*----------------------------DDR ECC error-------------------------*/
	//CIC: 110 DDR3_ERR DDR3_EMIF Error Interrupt
	if(status[3]&(1<<(110-96)))
	{
		printf("  DDR ECC error happened during ");

		exception_record.status.ext_sts.info.memory.fault_status.DDR_IRQSTATUS_SYS= 
			gpDDR_regs->IRQSTATUS_SYS;

		if(gpDDR_regs->IRQSTATUS_SYS&CSL_EMIF4F_IRQSTATUS_SYS_REG_RD_ECC_ERR_SYS_MASK)
			printf("read ");
		if(gpDDR_regs->IRQSTATUS_SYS&CSL_EMIF4F_IRQSTATUS_SYS_REG_WR_ECC_ERR_SYS_MASK)
			printf("write ");
		printf(".\n");

		//clear the status
		gpDDR_regs->IRQSTATUS_SYS= CSL_EMIF4F_IRQSTATUS_SYS_REG_RD_ECC_ERR_SYS_MASK
			|CSL_EMIF4F_IRQSTATUS_SYS_REG_WR_ECC_ERR_SYS_MASK;
	}

    /*Step3: Enable the CIC host interrupt */
    KeyStone_CIC_enable_host_int(gpCIC_regs, gCIC_EXC_out_num);    

}

/*****************************************************************************
 Prototype    : KeyStone_EXC_external
 Description  : external exception processing
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function
*****************************************************************************/
void KeyStone_EXC_external(void)
{
	int i;
	unsigned int INTXSTAT, flag[4];

	for(i= 0; i<4; i++)
	{
		flag[i] = gpCGEM_regs->MEXPFLAG[i];
		if(flag[i])
		{
			exception_record.status.ext_sts.MEXPFLAG[i]= flag[i];
			printf("External exception happened. MEXPFLAG[%d]=0x%x.\n", 
				i, flag[i]);
			gpCGEM_regs->EVTCLR[i] = flag[i];
		}
	}

	if(0 == (flag[0]|flag[1]|flag[2]|flag[3]))	
	{
		puts("Enter external Exception service routine, but external excpetion flage is 0!");
		return;
	}

    /*Exception events routed from CIC*/
    if(flag[guwIntcCICExcEvtIdx>>5] & (1<<(guwIntcCICExcEvtIdx&0x1F)))
    {
		KeyStone_CIC_EXC_handler();
	}

	/*MSMC memory protection exception*/
	if(flag[0]&(1<<CSL_GEM_MSMC_MPF_ERRORN))
	{
		puts("  Event 10 : MSMC_mpf_error_n MSMC Memory protection fault indicators for local CorePac");

         KeyStone_MSMC_protection_exception_handler();

 	}

	/*96 INTERR Dropped CPU interrupt event   */
	if(flag[3]&(1<<(CSL_GEM_INTERR-96)))
	{
		INTXSTAT= gpCGEM_regs->INTXSTAT;
		exception_record.status.ext_sts.info.INTXSTAT= INTXSTAT;

		if(INTXSTAT&CSL_CGEM_INTXSTAT_DROP_MASK)
			printf("  Event 96: DSP Interrupt %d (INTC input Event %d) dropped\n",
				(INTXSTAT&CSL_CGEM_INTXSTAT_CPUINT_MASK)>>CSL_CGEM_INTXSTAT_CPUINT_SHIFT,
				(INTXSTAT&CSL_CGEM_INTXSTAT_SYSINT_MASK)>>CSL_CGEM_INTXSTAT_SYSINT_SHIFT);
	}

	if(flag[3]&(1<<(CSL_GEM_EMC_IDMAERR-96)))
		puts("  Event 97: EMC_IDMAERR Invalid IDMA parameters");

	/*MDMA XMC VBUSM error*/
	if(flag[3]&(1<<(CSL_GEM_MDMAERREVT-96)))
	{
		puts("  Event 110: MDMAERREVT XMC VBUSM error event");
		if(gpXMC_regs->XMPFSR)
		{
			/*XMC protection error*/
			memory_protection_exception_handler(gpXMC_regs->XMPFAR, gpXMC_regs->XMPFSR);
			gpXMC_regs->XMPFCR = 1;
		}
		else
		{
			/*other VBUSM error*/
			Bus_error_handler(gpCGEM_regs->MDMAERR);
		}
		/* clear the MDMAERR */
		gpCGEM_regs->MDMAERRCLR = 1;
	}

	/*L1P Single bit error detected during DMA read*/
	if(flag[3]&(1<<(CSL_GEM_PMC_ED-96)))
	{
		puts("  Event 113: PMC_ED Single bit error detected during DMA read");
		L1P_ED_handler();
	}

	/*LL2 Uncorrected bit error detected*/
	if(flag[3]&(1<<(CSL_GEM_UMC_ED2-96)))
	{
		puts("  Event 117: UMC_ED2 Uncorrected bit error detected");
		LL2_EDC_handler(FALSE);
	}

	/*local register memory protection exception*/
	if(flag[3]&(1<<(CSL_GEM_SYS_CMPA-96)))
	{
		puts("  Event 119: SYS_CMPA CPU Memory Protection Fault for local configuration of INTC and power control");
	}

	/*L1P memory protection exception*/
	if(flag[3]&(3<<(CSL_GEM_PMC_CMPA-96)))
	{
		if(flag[3]&(1<<(CSL_GEM_PMC_CMPA-96)))
			puts("  Event 120: PMC_CMPA CPU memory protection fault for L1P");
		if(flag[3]&(1<<(CSL_GEM_PMC_DMPA-96)))
			puts("  Event 121: PMC_DMPA DMA memory protection fault for L1P");
		memory_protection_exception_handler(gpCGEM_regs->L1PMPFAR, gpCGEM_regs->L1PMPFSR);
		gpCGEM_regs->L1PMPFCR = 1;
	}

	/*L1D memory protection exception*/
	if(flag[3]&(3<<(CSL_GEM_DMC_CMPA-96)))
	{
		if(flag[3]&(1<<(CSL_GEM_DMC_CMPA-96)))
			puts("  Event 122: DMC_CMPA CPU memory protection fault for L1D (and other memory read finally goes through the L1D controller)");
		if(flag[3]&(1<<(CSL_GEM_DMC_DMPA-96)))
			puts("  Event 123: DMC_DMPA DMA memory protection fault for L1D");
		memory_protection_exception_handler(gpCGEM_regs->L1DMPFAR, gpCGEM_regs->L1DMPFSR);
		gpCGEM_regs->L1DMPFCR = 1;
	}

	/*LL2 memory protection exception*/
	if(flag[3]&(3<<(CSL_GEM_UMC_CMPA-96)))
	{
		if(flag[3]&(1<<(CSL_GEM_UMC_CMPA-96)))
			puts("  Event 124: UMC_CMPA CPU memory protection fault for L2 ");
		if(flag[3]&(1<<(CSL_GEM_UMC_DMPA-96)))
			puts("  Event 125: UMC_DMPA DMA memory protection fault for L2 ");
		memory_protection_exception_handler(gpCGEM_regs->L2MPFAR, gpCGEM_regs->L2MPFSR);
		gpCGEM_regs->L2MPFCR = 1;
	}

	/*local registers protection exception*/
	if(flag[3]&(1<<(CSL_GEM_EMC_CMPA-96)))
	{
		puts("  Event 126: EMC_CMPA CPU memory protection fault for local configuration space between 0x01000000-0x01BFFFFF");
		memory_protection_exception_handler(gpCGEM_regs->ICFGMPFAR, gpCGEM_regs->ICFGMPFSR);
		gpCGEM_regs->ICFGMPFCR= 1;
	}

	/*external configuration bus error*/
	if(flag[3]&(Uint32)(1<<(CSL_GEM_EMC_BUSERR-96)))
	{
		puts("  Event 127: EMC_BUSERR Bus Error Interrupt for global configuration space between 0x01C00000 - 0x07FFFFFF");
		Bus_error_handler(gpCGEM_regs->ECFGERR);
		gpCGEM_regs->ECFGERRCLR= 1;
	}
}

char * internal_exception_str[]=
{
	"Instruction fetch exception",
	"Fetch packet exception",
	"Execute packet exception",
	"Opcode exception",
	"Resource conflict exception",
	"Resource access exception",
	"Privilege exception",
	"SPLOOP buffer exception",
	"Missed stall exception"
};

/*****************************************************************************
 Prototype    : EXC_internal
 Description  : internal exception handler
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
/*internal exception handler*/
void EXC_internal(void)
{
	int i;
	unsigned int ierr;

	/*record IERR */    
	ierr = IERR;
	exception_record.status.IERR= ierr;

	if(ierr)
	{
		/*Clear internal excpeiton flag*/
		IERR= 0;

		printf("internal excpetion happened. IERR=0x%x.\n", ierr);
		for(i=0; i<9; i++)
		{
			if((ierr>>i)&1)
				printf("  %s\n", internal_exception_str[i]);
		}
		if (ierr & CSL_CHIP_IERR_IFX_MASK) {
			/* L1P EDC Processing*/
			L1P_ED_handler();
		}
	}
	else
		puts("Enter Internal Exception service routine, but internal excpetion flage is 0!");
	
}
/*****************************************************************************
 Prototype    : EXC_nmi
 Description  : NMI processing
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
void EXC_NMI(void)
{
	puts("NMI exception happened, normally you should reset the DSP to recover from the problem!");
}

/*****************************************************************************
 Prototype    : EXC_swgen
 Description  : software generated exception handler
 Input        : void  
 Output       : None
 Return Value : 
*****************************************************************************/
void EXC_swgen(void)
{	
	puts("Software generated exception happened.");
}

/*****************************************************************************
 Prototype    : Exception_service_routine
 Description  : Exception service routine
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
#pragma NMI_INTERRUPT( Exception_service_routine );
void Exception_service_routine(void)
{
	unsigned int efr, nrp, ntsr, tscl, tsch, irp, itsr;

	/*record timestamp*/
	tscl = TSCL;
	exception_record.TSCL= tscl;
	tsch = TSCH;
	exception_record.TSCH= tsch;
	
	nrp = NRP;   /*record NRP */
	exception_record.NRP= nrp;
	ntsr = NTSR; /*record NTSR */
	exception_record.NTSR= ntsr;
	efr = EFR;   /*record EFR */
	exception_record.EFR= efr;

	irp = IRP;   /*record IRP */
	itsr = ITSR; /*record ITSR */
	exception_record.IRP= irp;
	exception_record.ITSR= itsr;

	if(efr)
	{
		/*Clear excpeiton flag*/
		ECR = efr;

		/*check all possible exceptions*/
		if (efr & CSL_CHIP_EFR_OXF_MASK) {
			/* S/W generated exception */
			EXC_swgen();		
		}
		if (efr & CSL_CHIP_EFR_IXF_MASK) {
			/* internal exception */
			EXC_internal();		
		}
		if (efr & CSL_CHIP_EFR_EXF_MASK) {
			/* external exception */
			KeyStone_EXC_external();		
		}
		if (efr & CSL_CHIP_EFR_NXF_MASK) {
			/* legacy NMI exception */
			EXC_NMI();		
		}
	}
	else
		puts("Enter Exception service routine, but excpetion flage is 0!");
		
	printf("NRP=0x%x, NTSR=0x%x, IRP=0x%x, ITSR=0x%x, TSCH= 0x%x, TSCL= 0x%x\n", 
		nrp, ntsr, irp, itsr, tsch, tscl);

	printf(" B3=0x%x, A4=0x%x, B4= 0x%x, B14= 0x%x, B15= 0x%x\n", 
		exception_record.B3, exception_record.A4,
		exception_record.B4, exception_record.B14,
		exception_record.B15);

	/*
	It is not always possible to safely exit the exception handling routine. Conditions that
	can prevent a safe return from exceptions include:
	1. SPLOOPs that are terminated by an exception cannot be resumed correctly. The
	SPLX bit in NTSR should be verified to be 0 before returning.
	2. Exceptions that occur when interrupts are blocked cannot be resumed correctly.
	The IB bit in NTSR should be verified to be 0 before returning.
	3. Exceptions that occur at any point in the code that cannot be interrupted safely
	(for example, a tight loop containing multiple assignments) cannot be safely
	returned to. The compiler will normally disable interrupts at these points in the
	program; check the GIE bit in NTSR to be 1 to verify that this condition is met.
	4. NRP is not in valid address space*/
	if((ntsr&CSL_CHIP_TSR_SPLX_MASK)
		||(ntsr&CSL_CHIP_TSR_IB_MASK)
		||(0==(ntsr&CSL_CHIP_TSR_GIE_MASK))
		||(0x800000>NRP))
	{
		puts("Exception happened at a place can not safely return!");
		//while(1);		//trap
		exit(0);
	}

}

/*****************************************************************************
 Prototype    : Nested_Exception_service_routine
 Description  : Nested Exception service routine
  	When a non-maskable exception happens in the first exception service routine,
  	then the reset vector is used when redirecting program execution to service the second
	exception. In this case, NTSR and NRP are left unchanged. TSR is copied to ITSR and
	the current PC is copied to IRP. TSR is set to the default exception processing value and
	the NMIE bit in IER is cleared in this case preventing any further external exceptions.
 Input        : void  
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/29
    Author       : Brighton Feng
    Modification : Created function

*****************************************************************************/
interrupt void Nested_Exception_service_routine(void)
{
	unsigned int tscl, tsch;

	/*record timestamp*/
	tscl = TSCL;
	tsch = TSCH;

	if(0==exception_record.TSCL)
		exception_record.TSCL= tscl;
	if(0==exception_record.TSCH)
		exception_record.TSCH= tsch;
	if(0==exception_record.NRP)
		exception_record.NRP= NRP;
	if(0==exception_record.NTSR)
		exception_record.NTSR= NTSR;
	if(0==exception_record.EFR)
		exception_record.EFR= EFR;
	if(0==exception_record.status.IERR)
		exception_record.status.IERR= IERR;

	exception_record.IRP= IRP;
	exception_record.ITSR= ITSR;

	printf("Nested exception happened! IRP=0x%x, ITSR=0x%x\n",
		IRP, ITSR);
		
	printf("NRP=0x%x, NTSR=0x%x, EFR=0x%x, IERR=0x%x, TSCH= 0x%x, TSCL= 0x%x\n", 
		NRP, NTSR, EFR, IERR, tsch, tscl);

	while(1);		//trap
//	exit(0);
}

/*=========================other utility functions==========================*/
/*clear all interrupt flag/status, setup ISTP to begining of LL2*/
void CPU_interrupt_init()
{
	//clear interrupt and excpetion events
	ICR = IFR;
	ECR = EFR;
	IER= 3; 	//disable all interrupts
    
	/* disable event combine */
	gpCGEM_regs->EVTMASK[0] = 0xffffffff;
	gpCGEM_regs->EVTMASK[1] = 0xffffffff;
	gpCGEM_regs->EVTMASK[2] = 0xffffffff;
	gpCGEM_regs->EVTMASK[3] = 0xffffffff;

	 /*Clear all CPU events*/
	gpCGEM_regs->EVTCLR[0]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[1]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[2]= 	0xFFFFFFFF;
	gpCGEM_regs->EVTCLR[3]= 	0xFFFFFFFF;

	/*Interrupt Service Table Pointer to begining of LL2 memory*/
	ISTP= 0x800000;
}

/*enable interrupt to CPU: IER |= uiIER_en_mask; GIE=1*/
void CPU_interrupt_enable(Uint32 uiIER_en_mask)
{
	ICR= uiIER_en_mask;
	IER |= uiIER_en_mask;

	//enable GIE
	TSR = TSR|1;
}

/*****************************************************************************
 Prototype    : KeyStone_get_device_info
 Description  : Get device information
 Input        : None
 Output       : None
 Return Value : 
 
  History        :
  1.Date         : 2010/12/12
    Author       : Brighton Feng
    Modification : Created function
  2.Date         : 2014/12/2
    Author       : Brighton Feng
    Modification : Update to parser device type, boot mode, endian information,
                   speed grade, required CVDD

*****************************************************************************/
//get device speed grade from the EFUSE register
void KeyStone_get_device_speed_grade()
{
	Uint32 uiDevSpeed, uiSpeedCode;

	uiSpeedCode= (DEVSPEED&DEVSPEED_DSP_SPEED_MASK)>>DEVSPEED_DSP_SPEED_SHIFT;

	if(uiSpeedCode&DEVSPEED_800_MHZ_MASK_H)       uiDevSpeed= 800;
	else if(uiSpeedCode&DEVSPEED_1000_MHZ_MASK_H) uiDevSpeed= 1000;
	else if(uiSpeedCode&DEVSPEED_1200_MHZ_MASK_H) uiDevSpeed= 1200;
	else if(uiSpeedCode&DEVSPEED_1250_MHZ_MASK_H) uiDevSpeed= 1250;
	else if(uiSpeedCode&DEVSPEED_1400_MHZ_MASK_H) uiDevSpeed= 1400;
	else if(uiSpeedCode&DEVSPEED_1400_MHZ_MASK_L) uiDevSpeed= 1400;
	else if(uiSpeedCode&DEVSPEED_1250_MHZ_MASK_L) uiDevSpeed= 1250;
	else if(uiSpeedCode&DEVSPEED_1200_MHZ_MASK_L) uiDevSpeed= 1200;
	else if(uiSpeedCode&DEVSPEED_1000_MHZ_MASK_L) uiDevSpeed= 1000;
	else                                          uiDevSpeed= 800;

	printf("Device speed grade = %dMHz.\n", uiDevSpeed);
}

char * device_type_str[]=
{
	"TCI6616",
	"C6670/TCI6618",
	"C6678/TCI6608",
	"TCI6614",
	"unknown"
};
char * endian_str[]=
{
	"big",
	"little"
};
char * boot_mode_str[]=
{
	"No boot or EMIF16(NOR FLASH) or UART",
	"Serial Rapid I/O",
	"Ethernet (SGMII)",
	"Ethernet (SGMII) or NAND FLASH",
	"PCIE",
	"I2C",
	"SPI",
	"HyperLink"
 };
char * input_clk_str[]=
{
	"50MHz",
	"66.67MHz",
	"80MHz",
	"100MHz",
	"156.25MHz",
	"250MHz",
	"312.5MHz",
	"122.88MHz",
	"bypassed"
};
void KeyStone_get_device_info()
{
	char * boot_mode;
	Uint8 ucBootMode, ucBootMaster;
	Uint32 uiVID;
	Uint8 ucPLL_cfg= 8; //8 means bypassed
	Uint32 * DieID= (Uint32 *)&gpBootCfgRegs->DIE_ID_REG0;
	Uint32 uiJTAG_ID = gpBootCfgRegs->DEVICE_ID_REG0;
	Uint32 uiDevStat = gpBootCfgRegs->BOOT_REG0;

	gDSP_board_type=KeyStone_Get_dsp_board_type();

	ucBootMode= (uiDevStat&DEVSTAT_BOOTMODE_MASK)>>DEVSTAT_BOOTMODE_SHIFT; 
	ucBootMaster= (uiDevStat&DEVSTAT_BOOTMASTER_MASK)>>DEVSTAT_BOOTMASTER_SHIFT;

	if((TCI6614_EVM==gDSP_board_type)&&(1==ucBootMaster))
	{
		boot_mode= "ARM";	//ARM boot
	}
	else
		boot_mode= boot_mode_str[ucBootMode];

	//PLL is not configured with SPI and I2C master boot mode
	if((5!=ucBootMode)&&(6!=ucBootMode)) 	
		ucPLL_cfg= (uiDevStat&DEVSTAT_SYSPLL_MASK)>>DEVSTAT_SYSPLL_SHIFT;

	printf("JTAG ID= 0x%08x. This is %s device, version variant = %d.\n", uiJTAG_ID, 
		device_type_str[gDSP_board_type], uiJTAG_ID>>28);

	printf("DEVSTAT= 0x%08x. %s endian, %s boot, PLL configuration implies the input clock for core is %s.\n", 
		uiDevStat, endian_str[uiDevStat&DEVSTAT_LENDIAN_MASK], boot_mode, 
		 input_clk_str[ucPLL_cfg]);

	uiVID= (gpPSC_regs->VCNTLID&CSL_PSC_VCNTLID_VCNTL_MASK)>>CSL_PSC_VCNTLID_VCNTL_SHIFT;
	printf("SmartReflex VID= %d, required core voltage= %.3fV.\n", uiVID, 0.7+(float)uiVID*0.41/64.f);
	
	printf("Die ID= 0x%08x, 0x%08x, 0x%08x, 0x%08x\n", DieID[0], DieID[1], DieID[2], DieID[3]);

	KeyStone_get_device_speed_grade();
}
/*****************************************************************************
 Prototype    : KeyStone_common_device_init
 Description  : common initialization for internal modules in K2 device 
 enable memory protection interrupts, EDC for MSMC RAM 
  History        :
  1.Date         : July 11, 2014
    Author       : Brighton Feng
    Modification : Created function
*****************************************************************************/
void KeyStone_common_device_init()
{
	int i;
	KeyStone_get_device_info();

	/* enable common MPU interrupts */
	for(i=0; i<4; i++)
	{
		KeyStone_MPU_interrupt_enable(i);
	}

	/*Enable MSMC EDC and setup scrubbing cycle counter= 255*1024*/
	KeyStone_SL2_EDC_enable(255);
}

/*****************************************************************************
 Prototype    : KeyStone_common_CPU_init
 Description  : common initialization for internal modules in K2 device 
 enable TSC, EDC for local RAM; clear cache; protect L1 as cache 
  History        :
  1.Date         : September 1, 2014
    Author       : Brighton Feng
    Modification : Created function
*****************************************************************************/
void KeyStone_common_CPU_init()
{
    TSC_init();	//initialize TSC to measure cycle

	/*clear all interrupt flag/status, setup ISTP to begining of LL2*/
	CPU_interrupt_init();

	/*clean cache from previous run, not required from power on or cold reset*/
	CACHE_wbInvAllL2(CACHE_WAIT);
	CSL_XMC_invalidatePrefetchBuffer();
	_mfence();
	_mfence();

	/* protect L1 as cache */
   	L1_cache_protection();
   	
	//Enable MSMC Memory protection error interrupt for local core, refer to MSMC user guide section3.8
	KeyStone_MSMC_MP_interrupt_en(1<<DNUM);
    
	/*enable L1P ED and scrub whole L1P*/
	L1P_EDC_setup();

   	/*enable LL2 EDC and scrub whole LL2*/
	LL2_EDC_setup();

}


