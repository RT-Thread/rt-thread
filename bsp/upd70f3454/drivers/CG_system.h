/*
*******************************************************************************
* Copyright(C) NEC Electronics Corporation 2010
* All rights reserved by NEC Electronics Corporation.
* This program should be used on your own responsibility.
* NEC Electronics Corporation assumes no responsibility for any losses
* incurred by customers or third parties arising from the use of this file.
*
* This device driver was created by Applilet3 for V850ES/Jx3
* 32-Bit Single-Chip Microcontrollers
* Filename:	CG_system.h
* Abstract:	This file implements device driver for System module.
* APIlib:	Applilet3 for V850ES/Jx3 V2.01 [20 Apr 2010]
* Device:	uPD70F3746
* Compiler:	IAR Systems ICCV850
* Creation date:	6/26/2010
*******************************************************************************
*/

#ifndef _MDSYSTEM_
#define _MDSYSTEM_
/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*
	Processor clock control register (PCC)
*/
#define	_03_CG_PCC_INITIALVALUE		0x03U
/* Use of subclock on-chip feedback resistor (FRC) */
#define	_00_CG_SUBCLK_FEEDBACK_USE	0x00U	/* subclock on-chip feedback resistor connected */
#define	_08_CG_SUBCLK_FEEDBACK_UNUSE	0x80U	/* subclock on-chip feedback resistor not connected */
/* Main clock osillator control (MCK) */
#define	_00_CG_MAINCLK_ENABLE		0x00U	/* main clock oscillation enabled */
#define	_04_CG_MAINCLK_STOP		0x40U	/* main clock oscillation stopped */
/* Use of main clock on-chip feedback resistor (MFRC) */
#define	_00_CG_MAINCLK_FEEDBACK_USE	0x00U	/* main clock feedback resistor connected */
#define	_20_CG_MAINCLK_FEEDBACK_UNUSE	0x20U	/* main clock feedback resistor not connected */
/* Status of CPU clock fCPU (CLS) */
#define	_00_CG_CPUCLK_MAINCLK		0x00U	/* main clock operation */
#define	_10_CG_CPUCLK_SUBCLK		0x10U	/* subclock operation */
/* Clock(fCLK/fCPU) selection (CK3 - CK0) */
#define	_0F_CG_CPUCLK			0x0FU
#define	_00_CG_CPUCLK_MAIN0		0x00U	/* fCPU = fXX */
#define	_01_CG_CPUCLK_MAIN1		0x01U	/* fCPU = fXX/2 */
#define	_02_CG_CPUCLK_MAIN2		0x02U	/* fCPU = fXX/2^2 */
#define	_03_CG_CPUCLK_MAIN3		0x03U	/* fCPU = fXX/2^3 */
#define	_04_CG_CPUCLK_MAIN4		0x04U	/* fCPU = fXX/2^4 */
#define	_05_CG_CPUCLK_MAIN5		0x05U	/* fCPU = fXX/2^5 */
#define	_0B_CG_CPUCLK_SUB		0x0BU	/* fXT */

/*
	Internal oscillator mode register (RCM)
*/
/* Oscillation/stop of internal oscillator (RSTOP) */
#define	_00_CG_INTER_OSC_ON		0x00U	/* internal oscillator oscillation */
#define	_01_CG_INTER_OSC_OFF		0x01U	/* internal oscillator stopped */

/*
	CPU operation clock status register (CCLS)
*/
/* CPU operation clock status (CCLSF) */
#define	_00_CG_CPUCLK_STATUS_MAINORSUB	0x00U	/* operating on main clock(fX) or subclock(fXT) */
#define	_01_CG_CPUCLK_STATUS_INTEROSC	0x01U	/* operating on internal oscillation clock(fR) */

/*
	Lock register (LOCKR)
*/
/* PLL lock status check (LOCK) */
#define	_00_CG_PLLSTATUS_LOCK		0x00U	/* locked status */
#define	_01_CG_PLLSTATUS_UNLOCK		0x01U	/* unlocked status */

/*
	PLL control register (PLLCTL)
*/
#define	_01_CG_PLLCTL_INITIALVALUE	0x01U
/* CPU operation clock selection register (SELPLL) */
#define	_00_CG_CPUCLK_CLKTHROUGH	0x00U	/* clock-through mode */
#define	_02_CG_CPUCLK_PLL		0x02U	/* PLL mode */
/* PLL operation stop register (PLLON) */
#define	_00_CG_CPUCLK_PLLOFF		0x00U	/* PLL stopped */
#define	_01_CG_CPUCLK_PLLON		0x01U	/* PLL operating */

/*
	Clock control register (CKC)
*/
#define	_0A_CG_CKC_INITIALVALUE		0x0AU
/* Internal system clock(fXX) in PLL mode */
#define	_00_CG_CPUCLK_4PLL		0x00U	/* fXX = 4* fX (fX = 2.5 to 5.0 MHz) */
#define	_01_CG_CPUCLK_8PLL		0x01U	/* fXX = 8* fX (fX = 2.5 to 4.0 MHz) */

/*
	PLL lockup time specification register (PLLS)
*/
#define	_03_CG_PLLS_INITIALVALUE	0x03U
/* PLL lockup time selection (PLLS2 - PLLS0) */
#define	_00_CG_PLLLOCKUP_SEL0		0x00U	/* 2^10/fX */
#define	_01_CG_PLLLOCKUP_SEL1		0x01U	/* 2^11/fX*/
#define	_02_CG_PLLLOCKUP_SEL2		0x02U	/* 2^12/fX */
#define	_03_CG_PLLLOCKUP_SEL3		0x03U	/* 2^13/fX (default value) */

/*
	Power save control register (PSC)
*/
/* Stand-by mode release control by occurrence of INTWDT2 signal (NMI1M) */
#define	_00_CG_STANDBY_INTWDT2EN	0x00U	/* enable releasing stand-by mode by INTWDT2 signal */
#define	_40_CG_STANDBY_INTWDT2DIS	0x40U	/* disable releasing stand-by mode by INTWDT2 signal */
/* Stand-by mode release control by NMI pin input (NMI0M) */
#define	_00_CG_STANDBY_NMIEN		0x00U	/* enable releasing stand-by mode by NMI pin input */
#define	_20_CG_STANDBY_NMIDIS		0x20U	/* disable releasing stand-by mode by NMI pin input */
/* Stand-by mode release control by maskable interrupt request signal (NMI0M) */
#define	_00_CG_STANDBY_MASKIEN		0x00U	/* enable releasing stand-by mode by maskable interrupt request signal */
#define	_10_CG_STANDBY_MASKIDIS		0x10U	/* disable releasing stand-by mode by maskable interrupt request signal */
/* Setting of stand-by mode (STP) */
#define	_00_CG_STANDBY_UNUSE		0x00U	/* normal mode */
#define	_02_CG_STANDBY_USE		0x02U	/* stand-by mode */

/*
	Power save mode control register (PSMR)
*/
/* Specification of operation in software stand-by mode (PSM1,PSM0) */
#define	_00_CG_POWERSAVE_IDLE1		0x00U	/* IDLE1, sub-IDLE modes */
#define	_01_CG_POWERSAVE_STOP1		0x01U	/* STOP, sub-IDLE modes */
#define	_02_CG_POWERSAVE_IDLE2		0x02U	/* IDLE2, sub-IDLE modes */
#define	_03_CG_POWERSAVE_STOP2		0x03U	/* STOP mode */

/*
	Clock monitor mode register (CLM)
*/
/* Clock monitor operation enable or disable (CLME) */
#define	_01_CG_MONITOR_ENABLE		0x01U	/* enable clock monitor operation */
#define	_00_CG_MONITOR_DISABLE		0x00U	/* disable clock monitor operation */

/*
	Watchdog Timer 2 mode register (WDTM2)
*/
/* Selection of operation mode (WDM21, WDM20) */
#define	_00_WDT2_OPERMODE_STOP		0x00U	/* stops operation */
#define	_20_WDT2_OPERMODE_NONMASK	0x20U	/* non-maskable interrupt request mode (generation of INTWDT2) */
#define	_40_WDT2_OPERMODE_RESET		0x40U	/* reset mode (generation of RESWDT2) */
/* Selection of clock mode (WDCS24,WDCS23) */
#define	_00_WDT2_CLKMODE_INTEROSC	0x00U	/* use internal oscillator */
#define	_08_WDT2_CLKMODE_MAINCLK	0x08U	/* use Main clock */
#define	_10_WDT2_CLKMODE_SUBCLK		0x10U	/* use subclock */
/* Watchdog Timer 2 clock Selection (WDCS22 - WDCS20) */
#define	_00_WDT2_CLOCK_SEL0		0x00U	/* 2^12/fR or 2^18/fXX or 2^9/fXT */
#define	_01_WDT2_CLOCK_SEL1		0x01U	/* 2^13/fR or 2^19/fXX or 2^10/fXT */
#define	_02_WDT2_CLOCK_SEL2		0x02U	/* 2^14/fR or 2^20/fXX or 2^11/fXT */
#define	_03_WDT2_CLOCK_SEL3		0x03U	/* 2^15/fR or 2^21/fXX or 2^12/fXT */
#define	_04_WDT2_CLOCK_SEL4		0x04U	/* 2^16/fR or 2^22/fXX or 2^13/fXT */
#define	_05_WDT2_CLOCK_SEL5		0x05U	/* 2^17/fR or 2^23/fXX or 2^14/fXT */
#define	_06_WDT2_CLOCK_SEL6		0x06U	/* 2^18/fR or 2^24/fXX or 2^15/fXT */
#define	_07_WDT2_CLOCK_SEL7		0x07U	/* 2^19/fR or 2^25/fXX or 2^16/fXT */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define	_00_CG_VSWC_VALUE		0x00U
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void CLOCK_Init(void);
void WDT2_Restart(void);
void CG_ReadResetSource(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
