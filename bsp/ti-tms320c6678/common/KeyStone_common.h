/******************************************************************************

  Copyright (C), 2001-2012, Texas Instrument.

 ******************************************************************************
  File Name     : KeyStone_common.h
  Version       : Initial Draft
  Author        : Zhan
  Created       : 2012/10/30
  Last Modified :
  Description   : KeyStone_common.c header file, KeyStone common miscellaneous functions and definitions
  Function List :
  History       :
  1.Date        : 2010-12-12
    Author      : Brighton Feng
    Modification: Created file

  2.Date         : 2012/10/6
    Author       : Brighton Feng
    Modification : For memory protection configuration

  3.Date         : 2014-12-8
    Author       : Brighton Feng
    Modification : Add common device, CPU, interrupt initialization functions.
                   Print device information including device type, speed grade, 
                   boot mode, required voltage, ID��
                   Add EDMA enable/disable functions.
                   To support square wave generation by timer.
******************************************************************************/
#ifndef _KEYSTONE_COMMON_H_
#define _KEYSTONE_COMMON_H_

#include <c6x.h>
#include <tistdtypes.h>
#include <cslr_pllc.h>
#include <cslr_xmc.h>
#include <cslr_cgem.h>
#include <csl_cgemAux.h>
#include <cslr_bootcfg.h>
#include <cslr_tpcc.h>
#include <cslr_tptc.h>
#include <cslr_device.h>
#include <cslr_cpintc.h>
#include <cslr_tmr.h>
#include <cslr_srio.h>
#include <cslr_vusr.h>
#include <csl_psc.h>
#include <csl_tmr.h>
#include <csl_cache.h>
#include <csl_cacheAux.h>
#include <csl_xmcAux.h>
#include <cslr_msmc.h>
#include <csl_idma.h>
#include <cslr_mpu.h>
#include <cslr_gpio.h>
#include <cslr_emif4f.h>
#include <stdio.h>

/*----------------------PLL registers definition----------------*/
#define PLLCTL0_PLLD_SHIFT   (0)
#define PLLCTL0_PLLD_MASK    (0x3F<<PLLCTL0_PLLD_SHIFT)
#define PLLCTL0_PLLM_SHIFT   (6)
#define PLLCTL0_PLLM_MASK    (0x1FFF<<PLLCTL0_PLLM_SHIFT)
#define PLLCTL_OD_SHIFT      (19)
#define PLLCTL_OD_MASK       (0xF<<PLLCTL_OD_SHIFT)
#define PLLCTL_BYPASS_SHIFT  (23)
#define PLLCTL_BYPASS_MASK   (0x1<<PLLCTL_BYPASS_SHIFT)
#define PLLCTL0_BWADJ_SHIFT  (24)
#define PLLCTL0_BWADJ_MASK   (0xFF<<PLLCTL0_BWADJ_SHIFT)

#define PLLCTL1_BWADJ_SHIFT    (0)
#define PLLCTL1_BWADJ_MASK     (0xF<<PLLCTL1_BWADJ_SHIFT)
#define PLLCTL1_ENSAT_SHIFT    (6)
#define PLLCTL1_ENSAT_MASK     (0x1<<PLLCTL1_ENSAT_SHIFT)
#define PLLCTL1_PAPLL_SHIFT    (13)
#define PLLCTL1_PAPLL_MASK     (0x1<<PLLCTL1_PAPLL_SHIFT)
#define PLLCTL1_PLLRESET_SHIFT (14)
#define PLLCTL1_PLLRESET_MASK  (0x1<<PLLCTL1_PLLRESET_SHIFT)

/*----------------------Boot Config registers definition----------------*/
#define DEVSPEED (*(unsigned int *)0x026203F8u)

#define DEVSPEED_1000_MHZ_MASK_L  (1<<0)
#define DEVSPEED_1200_MHZ_MASK_L  (1<<1)
#define DEVSPEED_1250_MHZ_MASK_L  (1<<2)
#define DEVSPEED_1400_MHZ_MASK_L  (1<<3)
#define DEVSPEED_1400_MHZ_MASK_H  (1<<4)
#define DEVSPEED_1250_MHZ_MASK_H  (1<<5)
#define DEVSPEED_1200_MHZ_MASK_H  (1<<6)
#define DEVSPEED_1000_MHZ_MASK_H  (1<<7)
#define DEVSPEED_800_MHZ_MASK_H   (1<<8)

#define DEVSPEED_DSP_SPEED_MASK  (0x1FFu<<23u)
#define DEVSPEED_DSP_SPEED_SHIFT  (23u)

#define DEVSTAT_LENDIAN_SHIFT     (0)
#define DEVSTAT_BOOTMODE_SHIFT    (1)
#define DEVSTAT_SYSPLL_SHIFT      (11)
#define DEVSTAT_BOOTMASTER_SHIFT  (14)

#define DEVSTAT_LENDIAN_MASK     (1<<0)
#define DEVSTAT_BOOTMODE_MASK    (7<<1)
#define DEVSTAT_SYSPLL_MASK      (7<<11)
#define DEVSTAT_BOOTMASTER_MASK  (1<<14)
/*----------------------Timer plus registers definition----------------*/
typedef struct {
    volatile Uint32 PID12;
    volatile Uint32 EMUMGT_CLKSPD;
    volatile Uint32 GPINT_EN;
    volatile Uint32 GPDIR_DAT;
    volatile Uint32 CNTLO;
    volatile Uint32 CNTHI;
    volatile Uint32 PRDLO;
    volatile Uint32 PRDHI;
    volatile Uint32 TCR;
    volatile Uint32 TGCR;
    volatile Uint32 WDTCR;
    volatile Uint32 TLGC;
    volatile Uint32 TLMR;
    volatile Uint32 RELLO;
    volatile Uint32 RELHI;
    volatile Uint32 CAPLO;
    volatile Uint32 CAPHI;
    volatile Uint32 INTCTL_STAT;
    volatile Uint8  RSVD0[24];
    volatile Uint32 TIMERLO_COMPARE_REG[8];
    volatile Uint8  RSVD1[32];
} CSL_TmrPlusRegs;

#define TMR_TCR_READRSTMODE_HI_SHIFT    (26)
#define TMR_TCR_CAPEVTMODE_LO_SHIFT     (12)
#define TMR_TCR_CAPMODE_LO_SHIFT        (11)
#define TMR_TCR_READRSTMODE_LO_SHIFT    (10)

#define TMR_TCR_READRSTMODE_HI_MASK    (1<<26)
#define TMR_TCR_CAPEVTMODE_LO_MASK     (3<<12)
#define TMR_TCR_CAPMODE_LO_MASK        (1<<11)
#define TMR_TCR_READRSTMODE_LO_MASK    (1<<10)

#define TMR_TGCR_PLUSEN_SHIFT 	       4
#define TMR_TGCR_PLUSEN_MASK 	       (1<<4)

#define TMR_INTCTLSTAT_EN_ALL_CLR_ALL   0x000F000F

#define CSL_TMR_WDTCR_WDKEY_CMD1         (0x0000A5C6u)
#define CSL_TMR_WDTCR_WDKEY_CMD2         (0x0000DA7Eu)

#define CSL_TMR_ENAMODE_CONT_RELOAD 	3

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/
/*convert local address to global address for DMA on multi-core DSP*/
#define GLOBAL_ADDR(addr) ((Uint32)addr<0x1000000?\
						(Uint32)addr+(0x10000000+DNUM*0x1000000):\
						(Uint32)addr)

/*according to default mapping, convert DDR3 logic address to 
32-bit physical address (36-bit physical address right shift by 4)*/
#define DDR_PHY_ADDR(addr) ((((Uint32)addr & 0x7FFFFFFF)>>4) | 0x80000000)

/*max number in two numbers*/
#define MAX(a, b) (a>b?a:b)
/*min number in two numbers*/
#define MIN(a, b) (a<b?a:b)

extern CSL_XmcRegs * gpXMC_regs;
extern CSL_CgemRegs * gpCGEM_regs;
extern CSL_BootcfgRegs * gpBootCfgRegs;
extern CSL_PllcRegs * gpPLLC_regs;
extern CSL_PscRegs *  gpPSC_regs;
extern CSL_MsmcRegs * gpMSMC_regs;
extern CSL_GpioRegs * gpGPIO_regs;

extern CSL_CPINTCRegs* gpCIC0_regs;
extern CSL_CPINTCRegs* gpCIC1_regs;
/*The register pointer for the CIC routing events DSP core.
By default, it is CIC0; but for core 4~7 of C6678, it is CIC1*/
extern CSL_CPINTCRegs* gpCIC_regs; 	

extern CSL_TpccRegs*  gpEDMA_CC0_regs;
extern CSL_TpccRegs*  gpEDMA_CC1_regs;
extern CSL_TpccRegs*  gpEDMA_CC2_regs;
extern CSL_TpccRegs*  gpEDMA_CC_regs[];
extern CSL_TptcRegs * gpEDMA_TC_0_0_regs;
extern CSL_TptcRegs * gpEDMA_TC_0_1_regs;
extern CSL_TptcRegs * gpEDMA_TC_1_0_regs;
extern CSL_TptcRegs * gpEDMA_TC_1_1_regs;
extern CSL_TptcRegs * gpEDMA_TC_1_2_regs;
extern CSL_TptcRegs * gpEDMA_TC_1_3_regs;
extern CSL_TptcRegs * gpEDMA_TC_2_0_regs;
extern CSL_TptcRegs * gpEDMA_TC_2_1_regs;
extern CSL_TptcRegs * gpEDMA_TC_2_2_regs;
extern CSL_TptcRegs * gpEDMA_TC_2_3_regs;
extern CSL_TptcRegs * gpEDMA_TC_regs[];
extern CSL_TmrPlusRegs * gpTimer0Regs;
extern CSL_TmrPlusRegs * gpTimer1Regs;
extern CSL_TmrPlusRegs * gpTimer2Regs;
extern CSL_TmrPlusRegs * gpTimer3Regs;
extern CSL_TmrPlusRegs * gpTimer4Regs;
extern CSL_TmrPlusRegs * gpTimer5Regs;
extern CSL_TmrPlusRegs * gpTimer6Regs;
extern CSL_TmrPlusRegs * gpTimer7Regs;
extern CSL_TmrPlusRegs * gpTimer8Regs;
extern CSL_TmrPlusRegs * gpTimerRegs[];

/*MPU for peripherals registers and data space*/
extern CSL_MpuRegs * gpMPU0_regs;
extern CSL_MpuRegs * gpMPU1_regs;
extern CSL_MpuRegs * gpMPU2_regs;
extern CSL_MpuRegs * gpMPU_regs[];
extern CSL_Emif4fRegs * gpDDR_regs;
extern CSL_MpuRegs * gpMPU3_regs;

extern unsigned int gDSP_Core_Speed_Hz; //DSP core clock speed in Hz

/*DSP core PLL configuration
DSP core will be configured to run at ref_clock_MHz*multiplier/divisor
 Input        : float ref_clock_MHz     
                unsigned int main_PLLM: 1~4096  
                unsigned int multiplier: 1~64  
*/
extern void KeyStone_main_PLL_init (float ref_clock_MHz,
	unsigned int multiplier, unsigned int divisor);


typedef struct  {
    volatile Uint32 PLL_CTL0;
    volatile Uint32 PLL_CTL1;
}PLL_ControlRegs;

 /*****************************************************************************
 Prototype    : KeyStone_PLL_init
 Description  : Config the PLL of ARM, PA and DDR
 	target clock speed will be ref_clock_MHz/inputDivisor*multiplier/outputDivisor
 Input        : unsigned int inputDivisor  
                unsigned int multiplier  
                unsigned int outputDivisor  
  Return Value : 0 for success, other value for error
 *****************************************************************************/
extern int KeyStone_PLL_init (PLL_ControlRegs * PLL_Regs, unsigned int inputDivisor, 
	unsigned int multiplier, unsigned int outputDivisor);

/*****************************************************************************
 Prototype    : KeyStone_PASS_PLL_init
 Description  : Config the PASS PLL
 	target clock speed will be ref_clock_MHz/divisor*multiplier
 Input        : float ref_clock_MHz
                unsigned int multiplier: 1~4096
                unsigned int divisor: 1~64
*****************************************************************************/
extern void KeyStone_PASS_PLL_init (float ref_clock_MHz,
	unsigned int multiplier, unsigned int divisor);

/*****************************************************************************
 Prototype    : KeyStone_DDR_PLL_init
 Description  : Config the DDR PLL
 	target clock speed will be ref_clock_MHz/divisor*multiplier
 Input        : float ref_clock_MHz
                unsigned int multiplier: 1~4096
                unsigned int divisor: 1~64
*****************************************************************************/
extern void KeyStone_DDR_PLL_init (float ref_clock_MHz,
	unsigned int multiplier, unsigned int divisor);

/*===============================TSC===================================*/
extern unsigned int cycle_measure_overhead;
/*get the delay between current and prvious TSC
The delay must be less than 32 bit
enable the TSC with "TSCL= 0;" before use this macro*/
#define TSC_getDelay(startTSC) 	((unsigned int)((0xFFFFFFFFl+TSCL)- (unsigned long long)startTSC)+ 1)
#define TSC_count_cycle_from(startTSC) 	(TSC_getDelay(startTSC)- cycle_measure_overhead)

/* Initialize Time stamp counter to measure cycles*/
extern void TSC_init();

/*delay in millisecond*/
extern void TSC_delay_ms(Uint32 ms);

/*delay in microsecond*/
extern void TSC_delay_us(Uint32 us);

/*===============================Timer=================================*/
typedef enum
{
	TIMER_ONE_SHOT_PULSE = 0, 	/*generate one shot pulse with timer*/
	TIMER_PERIODIC_PULSE, 	/*generate periodic pulse with timer*/
	TIMER_PERIODIC_CLOCK, 	/*generate periodic clock with timer*/
	/*generate periodic square wave with period reload feature, the difference 
	between wave and clock is the duty cycle of clock is always 50%*/
	TIMER_PERIODIC_WAVE, 	
	TIMER_WATCH_DOG 		/*configure timer as watch dog*/
}TTimerMode;

typedef struct  {
	int timer_num; 				/*select one timer*/
	TTimerMode timerMode; 		/*select function of the timer*/
	unsigned long long period; 	/*in the unit of DSP core clock/6*/
	unsigned long long reload_period; 	/*the reload value of period*/
	int pulseWidth; 			/*pulse width between 0~3*/	
}Timer64_Config;

extern void	Reset_Timer(int timer_num);

/*Initailize a 64-bit timer*/
extern void Timer64_Init(Timer64_Config * tmrCfg);

typedef enum
{
	WD_OUT_NONE = 0,
	WD_RESET_LOCAL = 2,
	WD_TRIGGER_NMI = 3,
	WD_TRIGGER_NMI_RESET_LOCAL = 4,
	WD_RESET_DEVICE = 5
}TWatchdogOutputMode;

/*write sequence of a A5C6h followed by a DA7Eh 
to services the watchdog timer.*/
extern void Service_Watchdog(int timer_num);

/*===============================PSC===================================*/
extern Int32 KeyStone_enable_PSC_module (Uint32 pwrDmnNum, Uint32 moduleNum);
extern Int32 KeyStone_disable_PSC_module (Uint32 pwrDmnNum, Uint32 moduleNum);
extern Int32 KeyStone_disable_PSC_Power_Domain (Uint32 pwrDmnNum);

/*============================EDMA=====================================*/
#define NUM_EDMA_TC 	10
#define NUM_EDMA_CC 	3

//enum to indicate the EDMA CC number, and channel number
typedef enum
{
	EDMA_CC0_CH0 = ((0<<16)|0 ),
	EDMA_CC0_CH1 = ((0<<16)|1 ),
	EDMA_CC0_CH2 = ((0<<16)|2 ),
	EDMA_CC0_CH3 = ((0<<16)|3 ),
	EDMA_CC0_CH4 = ((0<<16)|4 ),
	EDMA_CC0_CH5 = ((0<<16)|5 ),
	EDMA_CC0_CH6 = ((0<<16)|6 ),
	EDMA_CC0_CH7 = ((0<<16)|7 ),
	EDMA_CC0_CH8 = ((0<<16)|8 ),
	EDMA_CC0_CH9 = ((0<<16)|9 ),
	EDMA_CC0_CH10= ((0<<16)|10),
	EDMA_CC0_CH11= ((0<<16)|11),
	EDMA_CC0_CH12= ((0<<16)|12),
	EDMA_CC0_CH13= ((0<<16)|13),
	EDMA_CC0_CH14= ((0<<16)|14),
	EDMA_CC0_CH15= ((0<<16)|15),

	EDMA_CC1_CH0 = ((1<<16)|0 ),
	EDMA_CC1_CH1 = ((1<<16)|1 ),
	EDMA_CC1_CH2 = ((1<<16)|2 ),
	EDMA_CC1_CH3 = ((1<<16)|3 ),
	EDMA_CC1_CH4 = ((1<<16)|4 ),
	EDMA_CC1_CH5 = ((1<<16)|5 ),
	EDMA_CC1_CH6 = ((1<<16)|6 ),
	EDMA_CC1_CH7 = ((1<<16)|7 ),
	EDMA_CC1_CH8 = ((1<<16)|8 ),
	EDMA_CC1_CH9 = ((1<<16)|9 ),
	EDMA_CC1_CH10= ((1<<16)|10),
	EDMA_CC1_CH11= ((1<<16)|11),
	EDMA_CC1_CH12= ((1<<16)|12),
	EDMA_CC1_CH13= ((1<<16)|13),
	EDMA_CC1_CH14= ((1<<16)|14),
	EDMA_CC1_CH15= ((1<<16)|15),
	EDMA_CC1_CH16= ((1<<16)|16),
	EDMA_CC1_CH17= ((1<<16)|17),
	EDMA_CC1_CH18= ((1<<16)|18),
	EDMA_CC1_CH19= ((1<<16)|19),
	EDMA_CC1_CH20= ((1<<16)|20),
	EDMA_CC1_CH21= ((1<<16)|21),
	EDMA_CC1_CH22= ((1<<16)|22),
	EDMA_CC1_CH23= ((1<<16)|23),
	EDMA_CC1_CH24= ((1<<16)|24),
	EDMA_CC1_CH25= ((1<<16)|25),
	EDMA_CC1_CH26= ((1<<16)|26),
	EDMA_CC1_CH27= ((1<<16)|27),
	EDMA_CC1_CH28= ((1<<16)|28),
	EDMA_CC1_CH29= ((1<<16)|29),
	EDMA_CC1_CH30= ((1<<16)|30),
	EDMA_CC1_CH31= ((1<<16)|31),
	EDMA_CC1_CH32= ((1<<16)|32),
	EDMA_CC1_CH33= ((1<<16)|33),
	EDMA_CC1_CH34= ((1<<16)|34),
	EDMA_CC1_CH35= ((1<<16)|35),
	EDMA_CC1_CH36= ((1<<16)|36),
	EDMA_CC1_CH37= ((1<<16)|37),
	EDMA_CC1_CH38= ((1<<16)|38),
	EDMA_CC1_CH39= ((1<<16)|39),
	EDMA_CC1_CH40= ((1<<16)|40),
	EDMA_CC1_CH41= ((1<<16)|41),
	EDMA_CC1_CH42= ((1<<16)|42),
	EDMA_CC1_CH43= ((1<<16)|43),
	EDMA_CC1_CH44= ((1<<16)|44),
	EDMA_CC1_CH45= ((1<<16)|45),
	EDMA_CC1_CH46= ((1<<16)|46),
	EDMA_CC1_CH47= ((1<<16)|47),
	EDMA_CC1_CH48= ((1<<16)|48),
	EDMA_CC1_CH49= ((1<<16)|49),
	EDMA_CC1_CH50= ((1<<16)|50),
	EDMA_CC1_CH51= ((1<<16)|51),
	EDMA_CC1_CH52= ((1<<16)|52),
	EDMA_CC1_CH53= ((1<<16)|53),
	EDMA_CC1_CH54= ((1<<16)|54),
	EDMA_CC1_CH55= ((1<<16)|55),
	EDMA_CC1_CH56= ((1<<16)|56),
	EDMA_CC1_CH57= ((1<<16)|57),
	EDMA_CC1_CH58= ((1<<16)|58),
	EDMA_CC1_CH59= ((1<<16)|59),
	EDMA_CC1_CH60= ((1<<16)|60),
	EDMA_CC1_CH61= ((1<<16)|61),
	EDMA_CC1_CH62= ((1<<16)|62),
	EDMA_CC1_CH63= ((1<<16)|63),

	EDMA_CC2_CH0 = ((2<<16)|0 ),
	EDMA_CC2_CH1 = ((2<<16)|1 ),
	EDMA_CC2_CH2 = ((2<<16)|2 ),
	EDMA_CC2_CH3 = ((2<<16)|3 ),
	EDMA_CC2_CH4 = ((2<<16)|4 ),
	EDMA_CC2_CH5 = ((2<<16)|5 ),
	EDMA_CC2_CH6 = ((2<<16)|6 ),
	EDMA_CC2_CH7 = ((2<<16)|7 ),
	EDMA_CC2_CH8 = ((2<<16)|8 ),
	EDMA_CC2_CH9 = ((2<<16)|9 ),
	EDMA_CC2_CH10= ((2<<16)|10),
	EDMA_CC2_CH11= ((2<<16)|11),
	EDMA_CC2_CH12= ((2<<16)|12),
	EDMA_CC2_CH13= ((2<<16)|13),
	EDMA_CC2_CH14= ((2<<16)|14),
	EDMA_CC2_CH15= ((2<<16)|15),
	EDMA_CC2_CH16= ((2<<16)|16),
	EDMA_CC2_CH17= ((2<<16)|17),
	EDMA_CC2_CH18= ((2<<16)|18),
	EDMA_CC2_CH19= ((2<<16)|19),
	EDMA_CC2_CH20= ((2<<16)|20),
	EDMA_CC2_CH21= ((2<<16)|21),
	EDMA_CC2_CH22= ((2<<16)|22),
	EDMA_CC2_CH23= ((2<<16)|23),
	EDMA_CC2_CH24= ((2<<16)|24),
	EDMA_CC2_CH25= ((2<<16)|25),
	EDMA_CC2_CH26= ((2<<16)|26),
	EDMA_CC2_CH27= ((2<<16)|27),
	EDMA_CC2_CH28= ((2<<16)|28),
	EDMA_CC2_CH29= ((2<<16)|29),
	EDMA_CC2_CH30= ((2<<16)|30),
	EDMA_CC2_CH31= ((2<<16)|31),
	EDMA_CC2_CH32= ((2<<16)|32),
	EDMA_CC2_CH33= ((2<<16)|33),
	EDMA_CC2_CH34= ((2<<16)|34),
	EDMA_CC2_CH35= ((2<<16)|35),
	EDMA_CC2_CH36= ((2<<16)|36),
	EDMA_CC2_CH37= ((2<<16)|37),
	EDMA_CC2_CH38= ((2<<16)|38),
	EDMA_CC2_CH39= ((2<<16)|39),
	EDMA_CC2_CH40= ((2<<16)|40),
	EDMA_CC2_CH41= ((2<<16)|41),
	EDMA_CC2_CH42= ((2<<16)|42),
	EDMA_CC2_CH43= ((2<<16)|43),
	EDMA_CC2_CH44= ((2<<16)|44),
	EDMA_CC2_CH45= ((2<<16)|45),
	EDMA_CC2_CH46= ((2<<16)|46),
	EDMA_CC2_CH47= ((2<<16)|47),
	EDMA_CC2_CH48= ((2<<16)|48),
	EDMA_CC2_CH49= ((2<<16)|49),
	EDMA_CC2_CH50= ((2<<16)|50),
	EDMA_CC2_CH51= ((2<<16)|51),
	EDMA_CC2_CH52= ((2<<16)|52),
	EDMA_CC2_CH53= ((2<<16)|53),
	EDMA_CC2_CH54= ((2<<16)|54),
	EDMA_CC2_CH55= ((2<<16)|55),
	EDMA_CC2_CH56= ((2<<16)|56),
	EDMA_CC2_CH57= ((2<<16)|57),
	EDMA_CC2_CH58= ((2<<16)|58),
	EDMA_CC2_CH59= ((2<<16)|59),
	EDMA_CC2_CH60= ((2<<16)|60),
	EDMA_CC2_CH61= ((2<<16)|61),
	EDMA_CC2_CH62= ((2<<16)|62),
	EDMA_CC2_CH63= ((2<<16)|63)
}EDMA_CC_Channel_Num;

typedef enum
{
	DMA_NO_WAIT= 0,	/*do not wait DMA complete*/
	DMA_WAIT 			/*wait DMA complete*/
}DMA_Wait;

/*a structure to define a EDMA channel*/
typedef struct
{
	Uint8 CC_num; 		//number of the CC for the channel
	Uint8 channel_num;
	Uint8 TC_num; 		//number of the TC used for the channel
}EDMA_CC_Chanel_TC;

/*setup uiChannel of an EDMA to use uiTC*/
extern void EDMA_channel_TC_cfg (Uint32 uiCC, 
	Uint32 uiChannel, Uint32 uiTC);
extern void EDMA_TC_priority_cfg(Uint32 uiCC, 
	Uint32 uiPri, Uint32 uiTC);
extern void EDMA_init();

extern void EDMA_event_enable(Uint32 uiCC, Uint32 uiChannel);
extern void EDMA_event_disable(Uint32 uiCC, Uint32 uiChannel);
extern void EDMA_interrupt_enable(Uint32 uiCC, Uint32 uiIntNum);
extern void EDMA_interrupt_disable(Uint32 uiCC, Uint32 uiIntNum);

/*wait the pending EDMA complete*/
extern void EDMA_wait(EDMA_CC_Channel_Num CC_channel);
extern void EDMA_copy(unsigned int srcAddr, unsigned int dstAddr, 
	unsigned int byteCount, EDMA_CC_Channel_Num CC_channel, DMA_Wait wait);
extern void EDMA_fill(unsigned int address, unsigned long long data, 
	unsigned int byteCount, EDMA_CC_Channel_Num CC_channel);

/*wait the pending IDMA complete*/
extern void IDMA_wait();
extern void IDMA_copy(unsigned int srcAddr, unsigned int dstAddr, 
	unsigned int byteCount, DMA_Wait wait);

/*======================memory protection==============================*/
/*Memory Protection access permision mask*/
#define MP_NONE 0
#define MP_UX 	(1<<0) 
#define MP_UW 	(1<<1) 
#define MP_UR 	(1<<2) 
#define MP_SX 	(1<<3) 
#define MP_SW 	(1<<4) 
#define MP_SR 	(1<<5) 

/*for peripheral MPU only*/
#define MP_NS   (1<<7)
#define MP_EMU  (1<<6)

/*Memory Protection mask for enabling AIDs*/
#define MP_LOCAL    (1<<8)
#define MP_AIDX     (1<<9)
#define MP_AID0     (1<<10)
#define MP_AID1     (1<<11)
#define MP_AID2     (1<<12)
#define MP_AID3     (1<<13)
#define MP_AID4     (1<<14)
#define MP_AID5     (1<<15)
#define MP_AID0_5   0xFC00

/*for peripheral MPU only*/
#define MP_AID6     (1<<16)
#define MP_AID7     (1<<17)
#define MP_AID8     (1<<18)
#define MP_AID9     (1<<19)
#define MP_AID10    (1<<20)
#define MP_AID11    (1<<21)
#define MP_AID12    (1<<22)
#define MP_AID13    (1<<23)
#define MP_AID14    (1<<24)
#define MP_AID15    (1<<25)
#define MP_AID0_15  0x03FFFC00
#define MP_AID0_7   0x0003FC00
#define MP_AID8_15  0x03FC0000
#define MPU_DENY_ALL 	(MP_AID0_15|MP_NONE)

#define MAX_AID_NUM 	16

typedef enum
{
	PRIVID_COREPAC0 = 0,
	PRIVID_COREPAC1 = 1,
	PRIVID_COREPAC2 = 2,
	PRIVID_COREPAC3 = 3,

	PRIVID_COREPAC4 = 4, 	/*C6678 ONLY*/
	PRIVID_COREPAC5 = 5, 	/*C6678 ONLY*/
	PRIVID_COREPAC6 = 6, 	/*C6678 ONLY*/
	PRIVID_COREPAC7 = 7, 	/*C6678 ONLY*/

	PRIVID_AIF2 = 4,	/*TCI6614/8 ONLY*/
	PRIVID_TAC = 5,		/*TCI6614/8 ONLY*/
	PRIVID_RAC = 6,		/*TCI6614/8 ONLY*/
	PRIVID_ARM = 7, 	/*TCI6614 ONLY*/

	PRIVID_PCIE= 11,
	PRIVID_DEBUG_SS = 12,
	PRIVID_HYPERLINK_FIRST_ID = 13,
	PRIVID_HYPERLINK_SECOND_ID = 14,

	/*--------FOR C6678/4/2----------*/
	PRIVID_NETCP_C6678 = 8,
	PRIVID_SRIO_C6678 = 9,
	PRIVID_QMSS_C6678 = 10,
	PRIVID_TSIP = 15, 	

	/*--------FOR C6670----------*/
	PRIVID_FFTC_C6670 = 7,
	PRIVID_QMSS_SECOND_C6670 = 8,
	PRIVID_SRIO_C6670 = 9,
	PRIVID_QMSSPKTDMA_NETCP_C6670= 10,
	PRIVID_TE_SCR_3M_C6670 = 15, /*BCP, TCP3D_C, FFTC_C*/

	/*--------FOR TCI6614/2----------*/
	PRIVID_PASS_FFTC_BCPPKTDMA_SRIOPKTDMA_QMSSPKTDMA_TCI6614 = 8, 
	PRIVID_SRIODIO_TCI6614 = 9,
	PRIVID_QMSS_SECOND_TCI6614 = 10,
	PRIVID_BCP_DIO_TCI6614 = 15,
	
	PRIVID_ERROR = 16
}KeyStone_PrivID;

extern unsigned int mem_prot_key[4];
extern void lock_mem_prot_regs();
extern void unlock_mem_prot_regs();
/*setup the memory protection for local L1 memory*/
extern void L1_MPPA_setup(volatile Uint32 MPPA_regs[], Uint32 MPPA[]);
/*config "AccessPermisionMask" for L1P*/
extern void L1P_memory_protection_cfg(Uint32 AccessPermisionMask);
/*config "AccessPermisionMask" for L1D*/
extern void L1D_memory_protection_cfg(Uint32 AccessPermisionMask);
/*----	protect L1 as cache ----*/
extern void L1_cache_protection();
/*----setup the memory protection for local L2 memory----
usage example:
Uint32 MPPA[32]=
{
	MP_LOCAL|MP_SX|MP_UX, 	//page 0 for local code only
	MP_LOCAL|MP_SR|MP_SW|MP_UR|MP_UW, 	//page 1 for local data only
	......
}
......
	LL2_MPPA_setup(MPPA);
*/
extern void LL2_MPPA_setup(Uint32 MPPA[]);
/*config "AccessPermisionMask" for local L2 memory section from 
"startAddress" with "byteCount" size*/
extern void LL2_Memory_Protection_cfg(Uint32 startAddress,
	Uint32 byteCount, Uint32 AccessPermisionMask);

/*map CorePac AID to PrivID:
map_table[0] assign the PrivID for AID0,
map_table[1] assign the PrivID for AID1
......
map_table[5] assign the PrivID for AID5*/
extern void KeyStone_CorePac_AID_map(Uint8 map_table[]);

/* privilege ID remap to AID */
extern void KeyStone_PrivID_Remap(int privID, int AID);

/* Register Overlay Structure MPAX*/
typedef struct
{
    volatile Uint32 MPAXL;
    volatile Uint32 MPAXH;
}MPAX_Regs;

/*memory protection and address extension configuration*/
typedef struct
{
    Uint32 BADDR; 	/*32-bit virtual base address*/
    /*36-bit physical replace address, right shift by 4 to get the value here)*/
    Uint32 RADDR; 
    Uint32 SegementSize; 	/*Segment size in byte, must be power of 2*/
    Uint32 AccessPermisionMask; 	/*Access types allowed in this address range.*/
}MPAX_Config;

/*configure one MPAX segment*/
extern void KeyStone_MPAX_seg_setup(MPAX_Regs * MPAX_regs, Uint32 BADDR, 
	Uint32 RADDR, Uint32 SegementSize, Uint32 AccessPermisionMask);

/*configure multiple MPAX segments in XMC with a configuration table*/
extern void KeyStone_XMC_MPAX_setup(MPAX_Config MPAX_cfg[], 
	Uint32 firstSeg, Uint32 numSegs);

/*configure multiple MPAX segments in SMS of MSMC with a configuration table*/
extern void KeyStone_SMS_MPAX_setup(MPAX_Config MPAX_cfg[], 
	Uint32 firstSeg, Uint32 numSegs, Uint32 PrivID);
	
/*configure multiple MPAX segments in SES of MSMC with a configuration table*/
extern void KeyStone_SES_MPAX_setup(MPAX_Config MPAX_cfg[], 
	Uint32 firstSeg, Uint32 numSegs, Uint32 PrivID);
	
/*Enable MSMC Memory protection error interrupt for PrivIDs indicated by "PRIVID_MASK"*/
extern void KeyStone_MSMC_MP_interrupt_en(Uint32 PRIVID_MASK);

/*==========Peripherals registers and internal data buffer MPU=============*/
/*peripherals memory protection unit configuration*/
typedef struct
{
    Uint32 StartAddr; 	            /*32-bit start address*/
    Uint32 EndAddr;                 /*32-bit end address*/
    Uint32 AccessPermisionMask; 	/*Access types allowed in this address range.*/
}MPU_Range_Config;

typedef struct
{
    Uint32 StartAddr; 	            /*32-bit start address*/
    Uint32 EndAddr;                 /*32-bit end address*/
}MPU_Addr;

extern CSL_MpuRegs * gpMPU_regs[];

/*configure one range in peripheral MPU*/
extern void KeyStone_MPU_range_setup(CSL_MpuProg_regionRegs *MPPA_regs, 
	Uint32 uiStartAddress, Uint32 uiEndAddress, Uint32 AccessPermisionMask);

/*peripherals MPU ranges configuration*/
extern void KeyStone_MPU_setup(Uint32 uiMPU_num, 
	MPU_Range_Config MPU_cfg[], Uint32 numRangeCfg);

/*search the range which match a address and then modify
the access permission of that range.*/
extern void KeyStone_MPU_MPPA_modify(Uint32 uiMPU_num, 
	Uint32 uiAddress, Uint32 AccessPermisionMask);

/* enable one MPU interrupt */
extern void KeyStone_MPU_interrupt_enable(Uint32 uiMPU_num);
/* enable all MPU interrupts */
extern void KeyStone_MPU_interrupts_enable();

/*======================memory EDC=====================================*/
/*Enable MSMC EDC and setup scrubbing cycle counter*/
extern void KeyStone_SL2_EDC_enable(Uint32 scrubCnt);

/*Enable MSMC EDC error interrupt*/
extern void KeyStone_SL2_EDC_interrupt_en();

/*enable LL2 EDC and scrub whole LL2*/
extern void LL2_EDC_setup();

/*----	L1P EDC setup ----*/
extern void L1P_EDC_setup();

/*scrub a block in LL2 for EDC. 
Number of bytes must be multiple of 128 bits and less than 64KB.
This function should be called periodically, for example, 
if every 1 minute, call it with:	LL2_EDC_scrub(1024);
For 1MB LL2, the whole space will be scrubbed in 1024 minutes(17 hours)*/
extern void LL2_EDC_scrub(Uint32 uiByteCnt);

/*LL2 EDC exception/interrupt handler*/
extern void LL2_EDC_handler(Bool bCorrected);

/*SL2 EDC handler*/
extern void KeyStone_SL2_EDC_handler();
/*===============================Exception=============================*/
typedef	union	{
	volatile Uint32 MPFSR; /*copy of MPFSR register for L1P, L1D or LL2*/
	volatile Uint32 SMPFR; /*copy of SMPFR register for MSMC*/
	volatile Uint32 MPU_FAULT_STATUS; /*copy of FAULT_STATUS register for MPU*/
	volatile Uint32 L1PEDSTAT; /*copy of L1PEDSTAT register*/
	volatile Uint32 L2EDSTAT; /*copy of L2EDSTAT register*/
	volatile Uint32 SMESTAT; /*copy of SMESTAT register for SL2 EDC*/
	volatile Uint32 DDR_IRQSTATUS_SYS; /*copy of IRQSTATUS_SYS for DDR ECC*/
} Memory_Fault_Info;

typedef	struct{
	Uint32 fault_address;
	Memory_Fault_Info fault_status; 	
	volatile Uint32 BUS_ERROR; /*copy of MDMAERR or ECFGERR register*/
} Memory_Exception_Info;

typedef	struct{
	volatile Uint32 EMR; /*copy of TPTC_EMR register*/
	volatile Uint32 EMRH; /*copy of TPTC_EMRH register*/
	volatile Uint32 QEMR; /*copy of TPTC_QEMR register*/
	volatile Uint32 CCERR; /*copy of TPTC_CCERR register*/
} EDMA_CC_Exception_Info;

typedef	struct{
	volatile Uint32 ERRSTAT; /*copy of TPTC_ERRSTAT register*/
	volatile Uint32 ERRDET; /*copy of TPTC_ERRDET register*/
} EDMA_TC_Exception_Info;

typedef	union{
	EDMA_CC_Exception_Info CC_info;
	EDMA_TC_Exception_Info TC_info;
} EDMA_Exception_Info;

typedef	union	{
	volatile Uint32 INTXSTAT; /*copy of INTXSTAT register*/
	Memory_Exception_Info memory;
	EDMA_Exception_Info edma;
} Exception_Info;

typedef	struct{
	volatile Uint32 MEXPFLAG[4];  /*copy of the MEXPFLAG0..3 registers */
	volatile Uint32 CIC_STATUS[7];  /*copy of the CIC status registers */
	Exception_Info info;
} External_Exception_Status;

typedef	union	{
	volatile Uint32 IERR; /*copy of the IERR register */
	External_Exception_Status ext_sts;
} Exception_Status;
/**
This structure is used to record exception information during 
exception processing. 
Please note, if multiple exceptions happens at the same time,
only the last excpetion are record.
Multiple unions are used in the structure to save space.
 * */
typedef struct {
	volatile Uint32 B3; /*copy of B3 register (return pointer of caller) */
	volatile Uint32 A4; /*copy of the A4 register (first input parameter of caller)*/
	volatile Uint32 B4; /*copy of the B4 register (second input parameter of caller)*/
	volatile Uint32 B14; /*copy of the B14 register (data pointer)*/
	volatile Uint32 B15; /*copy of the B15 register (stack pointer)*/
	volatile Uint32 TSCL; /*copy of the TSCL register (time stamp)*/
	volatile Uint32 TSCH; /*copy of the TSCH register (time stamp)*/
	volatile Uint32 NTSR; /*copy of the NTSR register */
	volatile Uint32 NRP; /*copy of the NRP register */
	volatile Uint32 EFR; /*copy of the EFR register */
	volatile Uint32 ITSR; /*copy of the ITSR register */
	volatile Uint32 IRP; /*copy of the IRP register */
	Exception_Status status;
} Exception_Record;

//data structure to save exception info
extern Exception_Record exception_record;

/*some exception events routed from CIC to INTC and then to exception moduel,
all these events are routed to one input of INTC*/
extern Uint32 guwIntcCICExcEvtIdx; /*INTC event number mapping to CIC exception events*/
extern Uint32 gCIC_EXC_out_num; 	//CIC output event number

/* Config the system error and exception to generate the NMI.
If bGlobalExceptionMaster==TRUE, the global exception events 
from CIC will be routed to exception model of this CPU core.
Call this function as last step after all configuration/initialization complete*/
extern void KeyStone_Exception_cfg(Bool bGlobalExceptionMaster);

extern void Bus_error_handler(unsigned int ERR_REG);

/*===============================Cache=================================*/
/*enable workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices.
Check your device errata to see if this is needed*/
#define CACHE_DISABLE_INT 	1
static inline void InvalidCache(void * blockPtr, Uint32 byteCnt)
{
#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	Uint32 uiOldGIE= _disable_interrupts();
#endif

	if(byteCnt>0xFFFF*4)
		byteCnt= 0xFFFF*4;
	if((Uint32)blockPtr>=0x0C000000&&(Uint32)blockPtr<0x0D000000)	//SL2
	{
		CACHE_invL1d((void *)blockPtr, byteCnt, CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	else if((Uint32)blockPtr>=0x10000000) 	//DDR or other cores
	{
		CACHE_invL2((void *)blockPtr, byteCnt, CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	_mfence();
	_mfence();

#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	asm(" nop 8");
	asm(" nop 8");
	_restore_interrupts(uiOldGIE); 	//restore interrupt
#endif
}

static inline void WritebackCache(void * blockPtr, Uint32 byteCnt)
{
	if(byteCnt>0xFFFF*4)
		byteCnt= 0xFFFF*4;
	if((Uint32)blockPtr>=0x0C000000&&(Uint32)blockPtr<0x0D000000)	//SL2
	{
		CACHE_wbL1d((void *)blockPtr, byteCnt, CACHE_WAIT);
	}
	else if((Uint32)blockPtr>=0x10000000) 	//DDR or other cores
	{
		CACHE_wbL2((void *)blockPtr, byteCnt, CACHE_WAIT);
	}
	_mfence();
	_mfence();
}
 
static inline void WritebackAllCache(void * blockPtr)
{
	if((Uint32)blockPtr>=0x0C000000&&(Uint32)blockPtr<0x0D000000)	//SL2
	{
		CACHE_wbAllL1d(CACHE_WAIT);;
	}
	else if((Uint32)blockPtr>=0x10000000) 	//DDR or other cores
	{
		CACHE_wbAllL2(CACHE_WAIT);
	}
	_mfence();
	_mfence();
}

static inline void WritebackInvalidCache(void * blockPtr, Uint32 byteCnt)
{
#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	Uint32 uiOldGIE= _disable_interrupts();
#endif

	if(byteCnt>0xFFFF*4)
		byteCnt= 0xFFFF*4;
	if((Uint32)blockPtr>=0x0C000000&&(Uint32)blockPtr<0x0D000000)	//SL2
	{
		CACHE_wbInvL1d((void *)blockPtr, byteCnt, CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	else if((Uint32)blockPtr>=0x10000000) 	//DDR or other cores
	{
		CACHE_wbInvL2((void *)blockPtr, byteCnt, CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	_mfence();
	_mfence();

#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	asm(" nop 8");
	asm(" nop 8");
	_restore_interrupts(uiOldGIE); 	//restore interrupt
#endif
}
 
static inline void WritebackInvalidAllCache(void * blockPtr)
{
#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	Uint32 uiOldGIE= _disable_interrupts();
#endif

	if((Uint32)blockPtr>=0x0C000000&&(Uint32)blockPtr<0x0D000000)	//SL2
	{
		CACHE_wbInvAllL1d(CACHE_WAIT);//CACHE_invL1d((void *)blockPtr, byteCnt, CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	else if((Uint32)blockPtr>=0x10000000) 	//DDR or other cores
	{
		//CACHE_invL2((void *)blockPtr, byteCnt, CACHE_WAIT);
		CACHE_wbInvAllL2(CACHE_WAIT);
		CSL_XMC_invalidatePrefetchBuffer();
	}
	_mfence();
	_mfence();

#if CACHE_DISABLE_INT
/*workaround for the "L2 Cache Corruption During Block and Global Coherence Operations
Issue" described in errata of some devices*/
	asm(" nop 8");
	asm(" nop 8");
	_restore_interrupts(uiOldGIE); 	//restore interrupt
#endif
}

static inline unsigned int SWAP_ENDIAN(unsigned int byte_index)
{
#ifdef _BIG_ENDIAN
	return ((byte_index&0xFFFFFFFC)+(3-byte_index&3));
#else
	return byte_index;
#endif
}

static inline void KeyStone_CIC_clear_system_event(CSL_CPINTCRegs* cpIntcRegs,
	int input_event_num)
{
	volatile Uint32 dummy_value;

	/*clear input interrupts events*/
	cpIntcRegs->STATUS_CLR_INDEX_REG= input_event_num;

	/*dummy read to make sure the previous write data land into the register*/
	dummy_value= cpIntcRegs->STATUS_CLR_INDEX_REG;
}

static inline void KeyStone_CIC_disable_host_int(CSL_CPINTCRegs* cpIntcRegs,
	int host_int_num)
{
	volatile Uint32 dummy_value;

	/* Disable the host interrupt */
	cpIntcRegs->HINT_ENABLE_CLR_INDEX_REG = host_int_num;

	/*dummy read to make sure the previous write data land into the register*/
	dummy_value= cpIntcRegs->HINT_ENABLE_CLR_INDEX_REG;
}

static inline void KeyStone_CIC_enable_host_int(CSL_CPINTCRegs* cpIntcRegs,
	int host_int_num)
{
	volatile Uint32 dummy_value;

	/* Enable the host interrupt */
	cpIntcRegs->HINT_ENABLE_SET_INDEX_REG = host_int_num;

	/*dummy read to make sure the previous write data land into the register*/
	dummy_value= cpIntcRegs->HINT_ENABLE_SET_INDEX_REG;
}

static inline void KeyStone_CIC_event_map(CSL_CPINTCRegs* cpIntcRegs,
	int input_event_num, int out_num)
{
	/*Map input event to output*/
	cpIntcRegs->CH_MAP[SWAP_ENDIAN(input_event_num)]= out_num;

	/*clear input interrupts events*/
	cpIntcRegs->STATUS_CLR_INDEX_REG= input_event_num; 

	/*enable input interrupts events*/
	cpIntcRegs->ENABLE_SET_INDEX_REG= input_event_num;

	/*enable output*/
	cpIntcRegs->HINT_ENABLE_SET_INDEX_REG= out_num;
}


typedef enum
{
	DUAL_NYQUIST_EVM = 0, 						
	C6670_EVM, 						
	C6678_EVM,
	TCI6614_EVM,
	C6657_EVM,
	UNKNOWN
}TDSP_Board_Type;

extern TDSP_Board_Type gDSP_board_type;

static inline TDSP_Board_Type KeyStone_Get_dsp_board_type()
{	
	Uint32 deviceID= gpBootCfgRegs->DEVICE_ID_REG0&0x0FFFFFFF;

	gDSP_board_type= UNKNOWN;
	if(0x0009D02F == deviceID)
		gDSP_board_type= DUAL_NYQUIST_EVM;
	if(0x0B94102F == deviceID)
	{
		gDSP_board_type= C6670_EVM;
		//DSP_Board_Type= DUAL_NYQUIST_EVM;
	}
	if(0x0009E02F == deviceID)
		gDSP_board_type= C6678_EVM;
	if(0x0B96202F == deviceID)
		gDSP_board_type= TCI6614_EVM;
	if(0x0B97A02F == deviceID)
		gDSP_board_type= C6657_EVM;

	return gDSP_board_type;
}

static inline Uint32 KeyStone_Get_DSP_Number()
{
	TDSP_Board_Type DSP_Board_Type= KeyStone_Get_dsp_board_type();

	if(DUAL_NYQUIST_EVM==DSP_Board_Type)
	{
		/*Nyquist EVM use boot configure pin 4 and 5 to identify DSPs*/
		return (( gpBootCfgRegs->BOOT_REG0 >> (3+1) ) & 0x03);
	}

	/*if use DNUM to differentiate DSPs for two DSPs test,
	the program must be run on core 0 of DSP 0 and core 1 of DSP1*/
	return DNUM;
}

/*clear all interrupt flag/status, setup ISTP to begining of LL2*/
extern void CPU_interrupt_init();
/*enable interrupt to CPU: IER |= uiIER_en_mask; GIE=1*/
extern void CPU_interrupt_enable(Uint32 uiIER_en_mask);

//get device speed grade from the EFUSE register
extern void KeyStone_get_device_speed_grade();

/*Get device information including device type, boot mode, endian information,
speed grade, required voltage...*/
extern void KeyStone_get_device_info();

/*common initialization for internal modules in K2 device.
enable memory protection interrupts, EDC for MSMC RAM*/
extern void KeyStone_common_device_init();

/* enable TSC, EDC for local RAM; clear cache; protect L1 as cache */
extern void KeyStone_common_CPU_init();


#endif
