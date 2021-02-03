/**
 * \file IfxScu_reg.h
 * \brief
 * \copyright Copyright (c) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC26XB_UM_V1.2.R0
 * Specification: tc26xB_um_v1.2_MCSFR.xml (Revision: UM_V1.2)
 * MAY BE CHANGED BY USER [yes/no]: No
 *
 *                                 IMPORTANT NOTICE
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Scu_Cfg Scu address
 * \ingroup IfxLld_Scu
 * 
 * \defgroup IfxLld_Scu_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Scu_Cfg
 * 
 * \defgroup IfxLld_Scu_Cfg_Scu 2-SCU
 * \ingroup IfxLld_Scu_Cfg
 * 
 */
#ifndef IFXSCU_REG_H
#define IFXSCU_REG_H 1
/******************************************************************************/
#include "IfxScu_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Scu_Cfg_BaseAddress
 * \{  */

/** \brief  SCU object */
#define MODULE_SCU /*lint --e(923)*/ (*(Ifx_SCU*)0xF0036000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Scu_Cfg_Scu
 * \{  */

/** \brief  3FC, Access Enable Register 0 */
#define SCU_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_SCU_ACCEN0*)0xF00363FCu)

/** \brief  3F8, Access Enable Register 1 */
#define SCU_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_SCU_ACCEN1*)0xF00363F8u)

/** \brief  5C, Application Reset Disable Register */
#define SCU_ARSTDIS /*lint --e(923)*/ (*(volatile Ifx_SCU_ARSTDIS*)0xF003605Cu)

/** \brief  30, CCU Clock Control Register 0 */
#define SCU_CCUCON0 /*lint --e(923)*/ (*(volatile Ifx_SCU_CCUCON0*)0xF0036030u)

/** \brief  34, CCU Clock Control Register 1 */
#define SCU_CCUCON1 /*lint --e(923)*/ (*(volatile Ifx_SCU_CCUCON1*)0xF0036034u)

/** \brief  40, CCU Clock Control Register 2 */
#define SCU_CCUCON2 /*lint --e(923)*/ (*(volatile Ifx_SCU_CCUCON2*)0xF0036040u)

/** \brief  44, CCU Clock Control Register 3 */
#define SCU_CCUCON3 /*lint --e(923)*/ (*(volatile Ifx_SCU_CCUCON3*)0xF0036044u)

/** \brief  48, CCU Clock Control Register 4 */
#define SCU_CCUCON4 /*lint --e(923)*/ (*(volatile Ifx_SCU_CCUCON4*)0xF0036048u)

/** \brief  4C, CCU Clock Control Register 5 */
#define SCU_CCUCON5 /*lint --e(923)*/ (*(volatile Ifx_SCU_CCUCON5*)0xF003604Cu)

/** \brief  80, CCU Clock Control Register 6 */
#define SCU_CCUCON6 /*lint --e(923)*/ (*(volatile Ifx_SCU_CCUCON6*)0xF0036080u)

/** \brief  84, CCU Clock Control Register 7 */
#define SCU_CCUCON7 /*lint --e(923)*/ (*(volatile Ifx_SCU_CCUCON7*)0xF0036084u)

/** \brief  140, Chip Identification Register */
#define SCU_CHIPID /*lint --e(923)*/ (*(volatile Ifx_SCU_CHIPID*)0xF0036140u)

/** \brief  E4, Die Temperature Sensor Control Register */
#define SCU_DTSCON /*lint --e(923)*/ (*(volatile Ifx_SCU_DTSCON*)0xF00360E4u)

/** \brief  240, Die Temperature Sensor Limit Register */
#define SCU_DTSLIM /*lint --e(923)*/ (*(volatile Ifx_SCU_DTSLIM*)0xF0036240u)

/** \brief  E0, Die Temperature Sensor Status Register */
#define SCU_DTSSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_DTSSTAT*)0xF00360E0u)

/** \brief  210, External Input Channel Register */
#define SCU_EICR0 /*lint --e(923)*/ (*(volatile Ifx_SCU_EICR*)0xF0036210u)

/** \brief  214, External Input Channel Register */
#define SCU_EICR1 /*lint --e(923)*/ (*(volatile Ifx_SCU_EICR*)0xF0036214u)

/** \brief  218, External Input Channel Register */
#define SCU_EICR2 /*lint --e(923)*/ (*(volatile Ifx_SCU_EICR*)0xF0036218u)

/** \brief  21C, External Input Channel Register */
#define SCU_EICR3 /*lint --e(923)*/ (*(volatile Ifx_SCU_EICR*)0xF003621Cu)

/** \brief  220, External Input Flag Register */
#define SCU_EIFR /*lint --e(923)*/ (*(volatile Ifx_SCU_EIFR*)0xF0036220u)

/** \brief  FC, Emergency Stop Register */
#define SCU_EMSR /*lint --e(923)*/ (*(volatile Ifx_SCU_EMSR*)0xF00360FCu)

/** \brief  70, ESR Input Configuration Register */
#define SCU_ESRCFG0 /*lint --e(923)*/ (*(volatile Ifx_SCU_ESRCFG*)0xF0036070u)

/** \brief  74, ESR Input Configuration Register */
#define SCU_ESRCFG1 /*lint --e(923)*/ (*(volatile Ifx_SCU_ESRCFG*)0xF0036074u)

/** \brief  78, ESR Output Configuration Register */
#define SCU_ESROCFG /*lint --e(923)*/ (*(volatile Ifx_SCU_ESROCFG*)0xF0036078u)

/** \brief  B8, EVR13 Control Register */
#define SCU_EVR13CON /*lint --e(923)*/ (*(volatile Ifx_SCU_EVR13CON*)0xF00360B8u)

/** \brief  BC, EVR33 Control Register */
#define SCU_EVR33CON /*lint --e(923)*/ (*(volatile Ifx_SCU_EVR33CON*)0xF00360BCu)

/** \brief  19C, EVR ADC Status Register */
#define SCU_EVRADCSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRADCSTAT*)0xF003619Cu)

/** \brief  B4, EVR Status Register for Voltage Scaling */
#define SCU_EVRDVSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRDVSTAT*)0xF00360B4u)

/** \brief  1A8, EVR Monitor Control Register */
#define SCU_EVRMONCTRL /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRMONCTRL*)0xF00361A8u)

/** \brief  1D8, EVR Oscillator & Bandgap Register */
#define SCU_EVROSCCTRL /*lint --e(923)*/ (*(volatile Ifx_SCU_EVROSCCTRL*)0xF00361D8u)

/** \brief  1A4, EVR Over-voltage Configuration Register */
#define SCU_EVROVMON /*lint --e(923)*/ (*(volatile Ifx_SCU_EVROVMON*)0xF00361A4u)

/** \brief  6C, EVR Reset Control Register */
#define SCU_EVRRSTCON /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRRSTCON*)0xF003606Cu)

/** \brief  1C0, EVR13 SD Coefficient Register 1 */
#define SCU_EVRSDCOEFF1 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCOEFF1*)0xF00361C0u)

/** \brief  1C4, EVR13 SD Coefficient Register 2 */
#define SCU_EVRSDCOEFF2 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCOEFF2*)0xF00361C4u)

/** \brief  1C8, EVR13 SD Coefficient Register 3 */
#define SCU_EVRSDCOEFF3 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCOEFF3*)0xF00361C8u)

/** \brief  1CC, EVR13 SD Coefficient Register 4 */
#define SCU_EVRSDCOEFF4 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCOEFF4*)0xF00361CCu)

/** \brief  1D0, EVR13 SD Coefficient Register 5 */
#define SCU_EVRSDCOEFF5 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCOEFF5*)0xF00361D0u)

/** \brief  1D4, EVR13 SD Coefficient Register 6 */
#define SCU_EVRSDCOEFF6 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCOEFF6*)0xF00361D4u)

/** \brief  1B0, EVR13 SD Control Register 1 */
#define SCU_EVRSDCTRL1 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCTRL1*)0xF00361B0u)

/** \brief  1B4, EVR13 SD Control Register 2 */
#define SCU_EVRSDCTRL2 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCTRL2*)0xF00361B4u)

/** \brief  1B8, EVR13 SD Control Register 3 */
#define SCU_EVRSDCTRL3 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCTRL3*)0xF00361B8u)

/** \brief  1BC, EVR13 SD Control Register 4 */
#define SCU_EVRSDCTRL4 /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSDCTRL4*)0xF00361BCu)

/** \brief  B0, EVR Status Register */
#define SCU_EVRSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRSTAT*)0xF00360B0u)

/** \brief  198, EVR Trim Register */
#define SCU_EVRTRIM /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRTRIM*)0xF0036198u)

/** \brief  1A0, EVR Under-voltage Configuration Register */
#define SCU_EVRUVMON /*lint --e(923)*/ (*(volatile Ifx_SCU_EVRUVMON*)0xF00361A0u)

/** \brief  3C, External Clock Control Register */
#define SCU_EXTCON /*lint --e(923)*/ (*(volatile Ifx_SCU_EXTCON*)0xF003603Cu)

/** \brief  38, Fractional Divider Register */
#define SCU_FDR /*lint --e(923)*/ (*(volatile Ifx_SCU_FDR*)0xF0036038u)

/** \brief  224, Flag Modification Register */
#define SCU_FMR /*lint --e(923)*/ (*(volatile Ifx_SCU_FMR*)0xF0036224u)

/** \brief  8, Identification Register */
#define SCU_ID /*lint --e(923)*/ (*(volatile Ifx_SCU_ID*)0xF0036008u)

/** \brief  22C, Flag Gating Register */
#define SCU_IGCR0 /*lint --e(923)*/ (*(volatile Ifx_SCU_IGCR*)0xF003622Cu)

/** \brief  230, Flag Gating Register */
#define SCU_IGCR1 /*lint --e(923)*/ (*(volatile Ifx_SCU_IGCR*)0xF0036230u)

/** \brief  234, Flag Gating Register */
#define SCU_IGCR2 /*lint --e(923)*/ (*(volatile Ifx_SCU_IGCR*)0xF0036234u)

/** \brief  238, Flag Gating Register */
#define SCU_IGCR3 /*lint --e(923)*/ (*(volatile Ifx_SCU_IGCR*)0xF0036238u)

/** \brief  AC, ESR Input Register */
#define SCU_IN /*lint --e(923)*/ (*(volatile Ifx_SCU_IN*)0xF00360ACu)

/** \brief  A0, Input/Output Control Register */
#define SCU_IOCR /*lint --e(923)*/ (*(volatile Ifx_SCU_IOCR*)0xF00360A0u)

/** \brief  164, Logic BIST Control 0 Register */
#define SCU_LBISTCTRL0 /*lint --e(923)*/ (*(volatile Ifx_SCU_LBISTCTRL0*)0xF0036164u)

/** \brief  168, Logic BIST Control 1 Register */
#define SCU_LBISTCTRL1 /*lint --e(923)*/ (*(volatile Ifx_SCU_LBISTCTRL1*)0xF0036168u)

/** \brief  16C, Logic BIST Control 2 Register */
#define SCU_LBISTCTRL2 /*lint --e(923)*/ (*(volatile Ifx_SCU_LBISTCTRL2*)0xF003616Cu)

/** \brief  138, LCL CPU1 Control Register */
#define SCU_LCLCON1 /*lint --e(923)*/ (*(volatile Ifx_SCU_LCLCON*)0xF0036138u)

/** \brief  13C, LCL Test Register */
#define SCU_LCLTEST /*lint --e(923)*/ (*(volatile Ifx_SCU_LCLTEST*)0xF003613Cu)

/** \brief  144, Manufacturer Identification Register */
#define SCU_MANID /*lint --e(923)*/ (*(volatile Ifx_SCU_MANID*)0xF0036144u)

/** \brief  A8, ESR Output Modification Register */
#define SCU_OMR /*lint --e(923)*/ (*(volatile Ifx_SCU_OMR*)0xF00360A8u)

/** \brief  10, OSC Control Register */
#define SCU_OSCCON /*lint --e(923)*/ (*(volatile Ifx_SCU_OSCCON*)0xF0036010u)

/** \brief  A4, ESR Output Register */
#define SCU_OUT /*lint --e(923)*/ (*(volatile Ifx_SCU_OUT*)0xF00360A4u)

/** \brief  1E4, Overlay Control Register */
#define SCU_OVCCON /*lint --e(923)*/ (*(volatile Ifx_SCU_OVCCON*)0xF00361E4u)

/** \brief  1E0, Overlay Enable Register */
#define SCU_OVCENABLE /*lint --e(923)*/ (*(volatile Ifx_SCU_OVCENABLE*)0xF00361E0u)

/** \brief  18C, Pad Disable Control Register */
#define SCU_PDISC /*lint --e(923)*/ (*(volatile Ifx_SCU_PDISC*)0xF003618Cu)

/** \brief  9C, ESR Pad Driver Mode Register */
#define SCU_PDR /*lint --e(923)*/ (*(volatile Ifx_SCU_PDR*)0xF003609Cu)

/** \brief  228, Pattern Detection Result Register */
#define SCU_PDRR /*lint --e(923)*/ (*(volatile Ifx_SCU_PDRR*)0xF0036228u)

/** \brief  18, PLL Configuration 0 Register */
#define SCU_PLLCON0 /*lint --e(923)*/ (*(volatile Ifx_SCU_PLLCON0*)0xF0036018u)

/** \brief  1C, PLL Configuration 1 Register */
#define SCU_PLLCON1 /*lint --e(923)*/ (*(volatile Ifx_SCU_PLLCON1*)0xF003601Cu)

/** \brief  20, PLL Configuration 2 Register */
#define SCU_PLLCON2 /*lint --e(923)*/ (*(volatile Ifx_SCU_PLLCON2*)0xF0036020u)

/** \brief  28, PLL_ERAY Configuration 0 Register */
#define SCU_PLLERAYCON0 /*lint --e(923)*/ (*(volatile Ifx_SCU_PLLERAYCON0*)0xF0036028u)

/** \brief  2C, PLL_ERAY Configuration 1 Register */
#define SCU_PLLERAYCON1 /*lint --e(923)*/ (*(volatile Ifx_SCU_PLLERAYCON1*)0xF003602Cu)

/** \brief  24, PLL_ERAY Status Register */
#define SCU_PLLERAYSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_PLLERAYSTAT*)0xF0036024u)

/** \brief  14, PLL Status Register */
#define SCU_PLLSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_PLLSTAT*)0xF0036014u)

/** \brief  D4, Power Management Control and Status Register */
#define SCU_PMCSR0 /*lint --e(923)*/ (*(volatile Ifx_SCU_PMCSR*)0xF00360D4u)

/** \brief  D8, Power Management Control and Status Register */
#define SCU_PMCSR1 /*lint --e(923)*/ (*(volatile Ifx_SCU_PMCSR*)0xF00360D8u)

/** \brief  C8, Standby and Wake-up Control Register 0 */
#define SCU_PMSWCR0 /*lint --e(923)*/ (*(volatile Ifx_SCU_PMSWCR0*)0xF00360C8u)

/** \brief  E8, Standby and Wake-up Control Register 1 */
#define SCU_PMSWCR1 /*lint --e(923)*/ (*(volatile Ifx_SCU_PMSWCR1*)0xF00360E8u)

/** \brief  EC, Standby and Wake-up Control Register 2 */
#define SCU_PMSWCR2 /*lint --e(923)*/ (*(volatile Ifx_SCU_PMSWCR2*)0xF00360ECu)

/** \brief  CC, Standby and Wake-up Status Flag Register */
#define SCU_PMSWSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_PMSWSTAT*)0xF00360CCu)

/** \brief  D0, Standby and Wake-up Status Clear Register */
#define SCU_PMSWSTATCLR /*lint --e(923)*/ (*(volatile Ifx_SCU_PMSWSTATCLR*)0xF00360D0u)

/** \brief  58, Reset Configuration Register */
#define SCU_RSTCON /*lint --e(923)*/ (*(volatile Ifx_SCU_RSTCON*)0xF0036058u)

/** \brief  64, Additional Reset Control Register */
#define SCU_RSTCON2 /*lint --e(923)*/ (*(volatile Ifx_SCU_RSTCON2*)0xF0036064u)

/** \brief  50, Reset Status Register */
#define SCU_RSTSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_RSTSTAT*)0xF0036050u)

/** \brief  150, Safety Heartbeat Register */
#define SCU_SAFECON /*lint --e(923)*/ (*(volatile Ifx_SCU_SAFECON*)0xF0036150u)

/** \brief  C0, Start-up Status Register */
#define SCU_STSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_STSTAT*)0xF00360C0u)

/** \brief  60, Software Reset Configuration Register */
#define SCU_SWRSTCON /*lint --e(923)*/ (*(volatile Ifx_SCU_SWRSTCON*)0xF0036060u)

/** \brief  7C, System Control Register */
#define SCU_SYSCON /*lint --e(923)*/ (*(volatile Ifx_SCU_SYSCON*)0xF003607Cu)

/** \brief  12C, Trap Clear Register */
#define SCU_TRAPCLR /*lint --e(923)*/ (*(volatile Ifx_SCU_TRAPCLR*)0xF003612Cu)

/** \brief  130, Trap Disable Register */
#define SCU_TRAPDIS /*lint --e(923)*/ (*(volatile Ifx_SCU_TRAPDIS*)0xF0036130u)

/** \brief  128, Trap Set Register */
#define SCU_TRAPSET /*lint --e(923)*/ (*(volatile Ifx_SCU_TRAPSET*)0xF0036128u)

/** \brief  124, Trap Status Register */
#define SCU_TRAPSTAT /*lint --e(923)*/ (*(volatile Ifx_SCU_TRAPSTAT*)0xF0036124u)

/** \brief  100, CPU WDT Control Register 0 */
#define SCU_WDTCPU0_CON0 /*lint --e(923)*/ (*(volatile Ifx_SCU_WDTCPU_CON0*)0xF0036100u)

/** Alias (User Manual Name) for SCU_WDTCPU0_CON0.
* To use register names with standard convension, please use SCU_WDTCPU0_CON0.
*/
#define	SCU_WDTCPU0CON0	(SCU_WDTCPU0_CON0)

/** \brief  104, CPU WDT Control Register 1 */
#define SCU_WDTCPU0_CON1 /*lint --e(923)*/ (*(volatile Ifx_SCU_WDTCPU_CON1*)0xF0036104u)

/** Alias (User Manual Name) for SCU_WDTCPU0_CON1.
* To use register names with standard convension, please use SCU_WDTCPU0_CON1.
*/
#define	SCU_WDTCPU0CON1	(SCU_WDTCPU0_CON1)

/** \brief  108, CPU WDT Status Register */
#define SCU_WDTCPU0_SR /*lint --e(923)*/ (*(volatile Ifx_SCU_WDTCPU_SR*)0xF0036108u)

/** Alias (User Manual Name) for SCU_WDTCPU0_SR.
* To use register names with standard convension, please use SCU_WDTCPU0_SR.
*/
#define	SCU_WDTCPU0SR	(SCU_WDTCPU0_SR)

/** \brief  10C, CPU WDT Control Register 0 */
#define SCU_WDTCPU1_CON0 /*lint --e(923)*/ (*(volatile Ifx_SCU_WDTCPU_CON0*)0xF003610Cu)

/** Alias (User Manual Name) for SCU_WDTCPU1_CON0.
* To use register names with standard convension, please use SCU_WDTCPU1_CON0.
*/
#define	SCU_WDTCPU1CON0	(SCU_WDTCPU1_CON0)

/** \brief  110, CPU WDT Control Register 1 */
#define SCU_WDTCPU1_CON1 /*lint --e(923)*/ (*(volatile Ifx_SCU_WDTCPU_CON1*)0xF0036110u)

/** Alias (User Manual Name) for SCU_WDTCPU1_CON1.
* To use register names with standard convension, please use SCU_WDTCPU1_CON1.
*/
#define	SCU_WDTCPU1CON1	(SCU_WDTCPU1_CON1)

/** \brief  114, CPU WDT Status Register */
#define SCU_WDTCPU1_SR /*lint --e(923)*/ (*(volatile Ifx_SCU_WDTCPU_SR*)0xF0036114u)

/** Alias (User Manual Name) for SCU_WDTCPU1_SR.
* To use register names with standard convension, please use SCU_WDTCPU1_SR.
*/
#define	SCU_WDTCPU1SR	(SCU_WDTCPU1_SR)

/** \brief  F0, Safety WDT Control Register 0 */
#define SCU_WDTS_CON0 /*lint --e(923)*/ (*(volatile Ifx_SCU_WDTS_CON0*)0xF00360F0u)

/** Alias (User Manual Name) for SCU_WDTS_CON0.
* To use register names with standard convension, please use SCU_WDTS_CON0.
*/
#define	SCU_WDTSCON0	(SCU_WDTS_CON0)

/** \brief  F4, Safety WDT Control Register 1 */
#define SCU_WDTS_CON1 /*lint --e(923)*/ (*(volatile Ifx_SCU_WDTS_CON1*)0xF00360F4u)

/** Alias (User Manual Name) for SCU_WDTS_CON1.
* To use register names with standard convension, please use SCU_WDTS_CON1.
*/
#define	SCU_WDTSCON1	(SCU_WDTS_CON1)

/** \brief  F8, Safety WDT Status Register */
#define SCU_WDTS_SR /*lint --e(923)*/ (*(volatile Ifx_SCU_WDTS_SR*)0xF00360F8u)

/** Alias (User Manual Name) for SCU_WDTS_SR.
* To use register names with standard convension, please use SCU_WDTS_SR.
*/
#define	SCU_WDTSSR	(SCU_WDTS_SR)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSCU_REG_H */
