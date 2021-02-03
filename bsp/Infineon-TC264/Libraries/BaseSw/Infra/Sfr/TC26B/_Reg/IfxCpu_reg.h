/**
 * \file IfxCpu_reg.h
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
 * \defgroup IfxLld_Cpu_Cfg Cpu address
 * \ingroup IfxLld_Cpu
 * 
 * \defgroup IfxLld_Cpu_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Cpu_Cfg
 * 
 * \defgroup IfxLld_Cpu_Cfg_Cpu0 2-CPU0
 * \ingroup IfxLld_Cpu_Cfg
 * 
 * \defgroup IfxLld_Cpu_Cfg_Cpu1 2-CPU1
 * \ingroup IfxLld_Cpu_Cfg
 * 
 * \defgroup IfxLld_Cpu_Cfg_Cpu 2-CPU
 * \ingroup IfxLld_Cpu_Cfg
 * 
 * \defgroup IfxLld_Cpu_Cfg_Cpu0_sprot 2-CPU0_SPROT
 * \ingroup IfxLld_Cpu_Cfg
 * 
 * \defgroup IfxLld_Cpu_Cfg_Cpu1_sprot 2-CPU1_SPROT
 * \ingroup IfxLld_Cpu_Cfg
 * 
 */
#ifndef IFXCPU_REG_H
#define IFXCPU_REG_H 1
/******************************************************************************/
#include "IfxCpu_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_Cfg_BaseAddress
 * \{  */

/** \brief  CPU object */
#define MODULE_CPU0 /*lint --e(923)*/ (*(Ifx_CPU*)0xF8810000u)

/** \brief  CPU SPROT object */
#define MODULE_CPU0_SPROT /*lint --e(923)*/ (*(Ifx_CPU_SPROT*)0xF8800000u)

/** \brief  CPU object */
#define MODULE_CPU1 /*lint --e(923)*/ (*(Ifx_CPU*)0xF8830000u)

/** \brief  CPU SPROT object */
#define MODULE_CPU1_SPROT /*lint --e(923)*/ (*(Ifx_CPU_SPROT*)0xF8820000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_Cfg_Cpu0
 * \{  */

/** \brief  FF80, Address General Purpose Register */
#define CPU0_A0 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FF80u)

/** \brief  FF84, Address General Purpose Register */
#define CPU0_A1 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FF84u)

/** \brief  FFA8, Address General Purpose Register */
#define CPU0_A10 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FFA8u)

/** \brief  FFAC, Address General Purpose Register */
#define CPU0_A11 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FFACu)

/** \brief  FFB0, Address General Purpose Register */
#define CPU0_A12 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FFB0u)

/** \brief  FFB4, Address General Purpose Register */
#define CPU0_A13 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FFB4u)

/** \brief  FFB8, Address General Purpose Register */
#define CPU0_A14 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FFB8u)

/** \brief  FFBC, Address General Purpose Register */
#define CPU0_A15 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FFBCu)

/** \brief  FF88, Address General Purpose Register */
#define CPU0_A2 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FF88u)

/** \brief  FF8C, Address General Purpose Register */
#define CPU0_A3 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FF8Cu)

/** \brief  FF90, Address General Purpose Register */
#define CPU0_A4 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FF90u)

/** \brief  FF94, Address General Purpose Register */
#define CPU0_A5 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FF94u)

/** \brief  FF98, Address General Purpose Register */
#define CPU0_A6 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FF98u)

/** \brief  FF9C, Address General Purpose Register */
#define CPU0_A7 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FF9Cu)

/** \brief  FFA0, Address General Purpose Register */
#define CPU0_A8 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FFA0u)

/** \brief  FFA4, Address General Purpose Register */
#define CPU0_A9 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF881FFA4u)

/** \brief  FE20, Base Interrupt Vector Table Pointer */
#define CPU0_BIV /*lint --e(923)*/ (*(volatile Ifx_CPU_BIV*)0xF881FE20u)

/** \brief  FE24, Base Trap Vector Table Pointer */
#define CPU0_BTV /*lint --e(923)*/ (*(volatile Ifx_CPU_BTV*)0xF881FE24u)

/** \brief  FC04, CPU Clock Cycle Count */
#define CPU0_CCNT /*lint --e(923)*/ (*(volatile Ifx_CPU_CCNT*)0xF881FC04u)

/** \brief  FC00, Counter Control */
#define CPU0_CCTRL /*lint --e(923)*/ (*(volatile Ifx_CPU_CCTRL*)0xF881FC00u)

/** \brief  9400, Compatibility Control Register */
#define CPU0_COMPAT /*lint --e(923)*/ (*(volatile Ifx_CPU_COMPAT*)0xF8819400u)

/** \brief  FE1C, CPU Core Identification Register */
#define CPU0_CORE_ID /*lint --e(923)*/ (*(volatile Ifx_CPU_CORE_ID*)0xF881FE1Cu)

/** \brief  D000, CPU Code Protection Range Lower Bound Register */
#define CPU0_CPR0_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF881D000u)

/** \brief  D004, CPU Code Protection Range Upper Bound Register */
#define CPU0_CPR0_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF881D004u)

/** \brief  D008, CPU Code Protection Range Lower Bound Register */
#define CPU0_CPR1_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF881D008u)

/** \brief  D00C, CPU Code Protection Range Upper Bound Register */
#define CPU0_CPR1_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF881D00Cu)

/** \brief  D010, CPU Code Protection Range Lower Bound Register */
#define CPU0_CPR2_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF881D010u)

/** \brief  D014, CPU Code Protection Range Upper Bound Register */
#define CPU0_CPR2_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF881D014u)

/** \brief  D018, CPU Code Protection Range Lower Bound Register */
#define CPU0_CPR3_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF881D018u)

/** \brief  D01C, CPU Code Protection Range Upper Bound Register */
#define CPU0_CPR3_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF881D01Cu)

/** \brief  D020, CPU Code Protection Range Lower Bound Register */
#define CPU0_CPR4_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF881D020u)

/** \brief  D024, CPU Code Protection Range Upper Bound Register */
#define CPU0_CPR4_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF881D024u)

/** \brief  D028, CPU Code Protection Range Lower Bound Register */
#define CPU0_CPR5_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF881D028u)

/** \brief  D02C, CPU Code Protection Range Upper Bound Register */
#define CPU0_CPR5_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF881D02Cu)

/** \brief  D030, CPU Code Protection Range Lower Bound Register */
#define CPU0_CPR6_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF881D030u)

/** \brief  D034, CPU Code Protection Range Upper Bound Register */
#define CPU0_CPR6_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF881D034u)

/** \brief  D038, CPU Code Protection Range Lower Bound Register */
#define CPU0_CPR7_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF881D038u)

/** \brief  D03C, CPU Code Protection Range Upper Bound Register */
#define CPU0_CPR7_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF881D03Cu)

/** \brief  FE18, CPU Identification Register TC1.6P */
#define CPU0_CPU_ID /*lint --e(923)*/ (*(volatile Ifx_CPU_CPU_ID*)0xF881FE18u)

/** \brief  E000, CPU Code Protection Execute Enable Register Set */
#define CPU0_CPXE0 /*lint --e(923)*/ (*(volatile Ifx_CPU_CPXE*)0xF881E000u)

/** Alias (User Manual Name) for CPU0_CPXE0.
* To use register names with standard convension, please use CPU0_CPXE0.
*/
#define	CPU0_CPXE_0	(CPU0_CPXE0)

/** \brief  E004, CPU Code Protection Execute Enable Register Set */
#define CPU0_CPXE1 /*lint --e(923)*/ (*(volatile Ifx_CPU_CPXE*)0xF881E004u)

/** Alias (User Manual Name) for CPU0_CPXE1.
* To use register names with standard convension, please use CPU0_CPXE1.
*/
#define	CPU0_CPXE_1	(CPU0_CPXE1)

/** \brief  E008, CPU Code Protection Execute Enable Register Set */
#define CPU0_CPXE2 /*lint --e(923)*/ (*(volatile Ifx_CPU_CPXE*)0xF881E008u)

/** Alias (User Manual Name) for CPU0_CPXE2.
* To use register names with standard convension, please use CPU0_CPXE2.
*/
#define	CPU0_CPXE_2	(CPU0_CPXE2)

/** \brief  E00C, CPU Code Protection Execute Enable Register Set */
#define CPU0_CPXE3 /*lint --e(923)*/ (*(volatile Ifx_CPU_CPXE*)0xF881E00Cu)

/** Alias (User Manual Name) for CPU0_CPXE3.
* To use register names with standard convension, please use CPU0_CPXE3.
*/
#define	CPU0_CPXE_3	(CPU0_CPXE3)

/** \brief  FD0C, Core Register Access Event */
#define CPU0_CREVT /*lint --e(923)*/ (*(volatile Ifx_CPU_CREVT*)0xF881FD0Cu)

/** \brief  FE50, CPU Customer ID register */
#define CPU0_CUS_ID /*lint --e(923)*/ (*(volatile Ifx_CPU_CUS_ID*)0xF881FE50u)

/** \brief  FF00, Data General Purpose Register */
#define CPU0_D0 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF00u)

/** \brief  FF04, Data General Purpose Register */
#define CPU0_D1 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF04u)

/** \brief  FF28, Data General Purpose Register */
#define CPU0_D10 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF28u)

/** \brief  FF2C, Data General Purpose Register */
#define CPU0_D11 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF2Cu)

/** \brief  FF30, Data General Purpose Register */
#define CPU0_D12 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF30u)

/** \brief  FF34, Data General Purpose Register */
#define CPU0_D13 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF34u)

/** \brief  FF38, Data General Purpose Register */
#define CPU0_D14 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF38u)

/** \brief  FF3C, Data General Purpose Register */
#define CPU0_D15 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF3Cu)

/** \brief  FF08, Data General Purpose Register */
#define CPU0_D2 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF08u)

/** \brief  FF0C, Data General Purpose Register */
#define CPU0_D3 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF0Cu)

/** \brief  FF10, Data General Purpose Register */
#define CPU0_D4 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF10u)

/** \brief  FF14, Data General Purpose Register */
#define CPU0_D5 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF14u)

/** \brief  FF18, Data General Purpose Register */
#define CPU0_D6 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF18u)

/** \brief  FF1C, Data General Purpose Register */
#define CPU0_D7 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF1Cu)

/** \brief  FF20, Data General Purpose Register */
#define CPU0_D8 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF20u)

/** \brief  FF24, Data General Purpose Register */
#define CPU0_D9 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF881FF24u)

/** \brief  9018, Data Asynchronous Trap Register */
#define CPU0_DATR /*lint --e(923)*/ (*(volatile Ifx_CPU_DATR*)0xF8819018u)

/** \brief  FD00, Debug Status Register */
#define CPU0_DBGSR /*lint --e(923)*/ (*(volatile Ifx_CPU_DBGSR*)0xF881FD00u)

/** \brief  FD48, Debug Trap Control Register */
#define CPU0_DBGTCR /*lint --e(923)*/ (*(volatile Ifx_CPU_DBGTCR*)0xF881FD48u)

/** \brief  9040, Data Memory Control Register */
#define CPU0_DCON0 /*lint --e(923)*/ (*(volatile Ifx_CPU_DCON0*)0xF8819040u)

/** \brief  9000, Data Control Register 2 */
#define CPU0_DCON2 /*lint --e(923)*/ (*(volatile Ifx_CPU_DCON2*)0xF8819000u)

/** \brief  FD44, CPU Debug Context Save Area Pointer */
#define CPU0_DCX /*lint --e(923)*/ (*(volatile Ifx_CPU_DCX*)0xF881FD44u)

/** \brief  901C, Data Error Address Register */
#define CPU0_DEADD /*lint --e(923)*/ (*(volatile Ifx_CPU_DEADD*)0xF881901Cu)

/** \brief  9020, Data Integrity Error Address Register */
#define CPU0_DIEAR /*lint --e(923)*/ (*(volatile Ifx_CPU_DIEAR*)0xF8819020u)

/** \brief  9024, Data Integrity Error Trap Register */
#define CPU0_DIETR /*lint --e(923)*/ (*(volatile Ifx_CPU_DIETR*)0xF8819024u)

/** \brief  FD40, CPU Debug Monitor Start Address */
#define CPU0_DMS /*lint --e(923)*/ (*(volatile Ifx_CPU_DMS*)0xF881FD40u)

/** \brief  C000, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR0_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C000u)

/** \brief  C004, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR0_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C004u)

/** \brief  C050, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR10_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C050u)

/** \brief  C054, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR10_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C054u)

/** \brief  C058, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR11_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C058u)

/** \brief  C05C, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR11_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C05Cu)

/** \brief  C060, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR12_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C060u)

/** \brief  C064, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR12_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C064u)

/** \brief  C068, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR13_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C068u)

/** \brief  C06C, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR13_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C06Cu)

/** \brief  C070, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR14_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C070u)

/** \brief  C074, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR14_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C074u)

/** \brief  C078, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR15_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C078u)

/** \brief  C07C, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR15_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C07Cu)

/** \brief  C008, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR1_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C008u)

/** \brief  C00C, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR1_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C00Cu)

/** \brief  C010, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR2_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C010u)

/** \brief  C014, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR2_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C014u)

/** \brief  C018, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR3_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C018u)

/** \brief  C01C, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR3_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C01Cu)

/** \brief  C020, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR4_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C020u)

/** \brief  C024, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR4_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C024u)

/** \brief  C028, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR5_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C028u)

/** \brief  C02C, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR5_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C02Cu)

/** \brief  C030, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR6_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C030u)

/** \brief  C034, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR6_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C034u)

/** \brief  C038, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR7_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C038u)

/** \brief  C03C, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR7_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C03Cu)

/** \brief  C040, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR8_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C040u)

/** \brief  C044, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR8_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C044u)

/** \brief  C048, CPU Data Protection Range, Lower Bound Register */
#define CPU0_DPR9_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF881C048u)

/** \brief  C04C, CPU Data Protection Range, Upper Bound Register */
#define CPU0_DPR9_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF881C04Cu)

/** \brief  E010, CPU Data Protection Read Enable Register Set */
#define CPU0_DPRE0 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPRE*)0xF881E010u)

/** Alias (User Manual Name) for CPU0_DPRE0.
* To use register names with standard convension, please use CPU0_DPRE0.
*/
#define	CPU0_DPRE_0	(CPU0_DPRE0)

/** \brief  E014, CPU Data Protection Read Enable Register Set */
#define CPU0_DPRE1 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPRE*)0xF881E014u)

/** Alias (User Manual Name) for CPU0_DPRE1.
* To use register names with standard convension, please use CPU0_DPRE1.
*/
#define	CPU0_DPRE_1	(CPU0_DPRE1)

/** \brief  E018, CPU Data Protection Read Enable Register Set */
#define CPU0_DPRE2 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPRE*)0xF881E018u)

/** Alias (User Manual Name) for CPU0_DPRE2.
* To use register names with standard convension, please use CPU0_DPRE2.
*/
#define	CPU0_DPRE_2	(CPU0_DPRE2)

/** \brief  E01C, CPU Data Protection Read Enable Register Set */
#define CPU0_DPRE3 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPRE*)0xF881E01Cu)

/** Alias (User Manual Name) for CPU0_DPRE3.
* To use register names with standard convension, please use CPU0_DPRE3.
*/
#define	CPU0_DPRE_3	(CPU0_DPRE3)

/** \brief  E020, CPU Data Protection Write Enable Register Set */
#define CPU0_DPWE0 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPWE*)0xF881E020u)

/** Alias (User Manual Name) for CPU0_DPWE0.
* To use register names with standard convension, please use CPU0_DPWE0.
*/
#define	CPU0_DPWE_0	(CPU0_DPWE0)

/** \brief  E024, CPU Data Protection Write Enable Register Set */
#define CPU0_DPWE1 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPWE*)0xF881E024u)

/** Alias (User Manual Name) for CPU0_DPWE1.
* To use register names with standard convension, please use CPU0_DPWE1.
*/
#define	CPU0_DPWE_1	(CPU0_DPWE1)

/** \brief  E028, CPU Data Protection Write Enable Register Set */
#define CPU0_DPWE2 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPWE*)0xF881E028u)

/** Alias (User Manual Name) for CPU0_DPWE2.
* To use register names with standard convension, please use CPU0_DPWE2.
*/
#define	CPU0_DPWE_2	(CPU0_DPWE2)

/** \brief  E02C, CPU Data Protection Write Enable Register Set */
#define CPU0_DPWE3 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPWE*)0xF881E02Cu)

/** Alias (User Manual Name) for CPU0_DPWE3.
* To use register names with standard convension, please use CPU0_DPWE3.
*/
#define	CPU0_DPWE_3	(CPU0_DPWE3)

/** \brief  9010, Data Synchronous Trap Register */
#define CPU0_DSTR /*lint --e(923)*/ (*(volatile Ifx_CPU_DSTR*)0xF8819010u)

/** \brief  FD08, External Event Register */
#define CPU0_EXEVT /*lint --e(923)*/ (*(volatile Ifx_CPU_EXEVT*)0xF881FD08u)

/** \brief  FE38, Free CSA List Head Pointer */
#define CPU0_FCX /*lint --e(923)*/ (*(volatile Ifx_CPU_FCX*)0xF881FE38u)

/** \brief  A000, CPU Trap Control Register */
#define CPU0_FPU_TRAP_CON /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_CON*)0xF881A000u)

/** \brief  A008, CPU Trapping Instruction Opcode Register */
#define CPU0_FPU_TRAP_OPC /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_OPC*)0xF881A008u)

/** \brief  A004, CPU Trapping Instruction Program Counter Register */
#define CPU0_FPU_TRAP_PC /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_PC*)0xF881A004u)

/** \brief  A010, CPU Trapping Instruction Operand Register */
#define CPU0_FPU_TRAP_SRC1 /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_SRC1*)0xF881A010u)

/** \brief  A014, CPU Trapping Instruction Operand Register */
#define CPU0_FPU_TRAP_SRC2 /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_SRC2*)0xF881A014u)

/** \brief  A018, Trapping Instruction Operand Register */
#define CPU0_FPU_TRAP_SRC3 /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_SRC3*)0xF881A018u)

/** \brief  FC08, Instruction Count */
#define CPU0_ICNT /*lint --e(923)*/ (*(volatile Ifx_CPU_ICNT*)0xF881FC08u)

/** \brief  FE2C, Interrupt Control Register */
#define CPU0_ICR /*lint --e(923)*/ (*(volatile Ifx_CPU_ICR*)0xF881FE2Cu)

/** \brief  FE28, Interrupt Stack Pointer */
#define CPU0_ISP /*lint --e(923)*/ (*(volatile Ifx_CPU_ISP*)0xF881FE28u)

/** \brief  FE3C, Free CSA List Limit Pointer */
#define CPU0_LCX /*lint --e(923)*/ (*(volatile Ifx_CPU_LCX*)0xF881FE3Cu)

/** \brief  FC0C, Multi-Count Register 1 */
#define CPU0_M1CNT /*lint --e(923)*/ (*(volatile Ifx_CPU_M1CNT*)0xF881FC0Cu)

/** \brief  FC10, Multi-Count Register 2 */
#define CPU0_M2CNT /*lint --e(923)*/ (*(volatile Ifx_CPU_M2CNT*)0xF881FC10u)

/** \brief  FC14, Multi-Count Register 3 */
#define CPU0_M3CNT /*lint --e(923)*/ (*(volatile Ifx_CPU_M3CNT*)0xF881FC14u)

/** \brief  FE08, Program Counter */
#define CPU0_PC /*lint --e(923)*/ (*(volatile Ifx_CPU_PC*)0xF881FE08u)

/** \brief  920C, Program Control 0 */
#define CPU0_PCON0 /*lint --e(923)*/ (*(volatile Ifx_CPU_PCON0*)0xF881920Cu)

/** \brief  9204, Program Control 1 */
#define CPU0_PCON1 /*lint --e(923)*/ (*(volatile Ifx_CPU_PCON1*)0xF8819204u)

/** \brief  9208, Program Control 2 */
#define CPU0_PCON2 /*lint --e(923)*/ (*(volatile Ifx_CPU_PCON2*)0xF8819208u)

/** \brief  FE00, Previous Context Information Register */
#define CPU0_PCXI /*lint --e(923)*/ (*(volatile Ifx_CPU_PCXI*)0xF881FE00u)

/** \brief  9210, Program Integrity Error Address Register */
#define CPU0_PIEAR /*lint --e(923)*/ (*(volatile Ifx_CPU_PIEAR*)0xF8819210u)

/** \brief  9214, Program Integrity Error Trap Register */
#define CPU0_PIETR /*lint --e(923)*/ (*(volatile Ifx_CPU_PIETR*)0xF8819214u)

/** \brief  8100, Data Access CacheabilityRegister */
#define CPU0_PMA0 /*lint --e(923)*/ (*(volatile Ifx_CPU_PMA0*)0xF8818100u)

/** \brief  8104, Code Access CacheabilityRegister */
#define CPU0_PMA1 /*lint --e(923)*/ (*(volatile Ifx_CPU_PMA1*)0xF8818104u)

/** \brief  8108, Peripheral Space Identifier register */
#define CPU0_PMA2 /*lint --e(923)*/ (*(volatile Ifx_CPU_PMA2*)0xF8818108u)

/** \brief  9200, Program Synchronous Trap Register */
#define CPU0_PSTR /*lint --e(923)*/ (*(volatile Ifx_CPU_PSTR*)0xF8819200u)

/** \brief  FE04, Program Status Word */
#define CPU0_PSW /*lint --e(923)*/ (*(volatile Ifx_CPU_PSW*)0xF881FE04u)

/** \brief  1030, SRI Error Generation Register */
#define CPU0_SEGEN /*lint --e(923)*/ (*(volatile Ifx_CPU_SEGEN*)0xF8811030u)

/** \brief  900C, SIST Mode Access Control Register */
#define CPU0_SMACON /*lint --e(923)*/ (*(volatile Ifx_CPU_SMACON*)0xF881900Cu)

/** \brief  FD10, Software Debug Event */
#define CPU0_SWEVT /*lint --e(923)*/ (*(volatile Ifx_CPU_SWEVT*)0xF881FD10u)

/** \brief  FE14, System Configuration Register */
#define CPU0_SYSCON /*lint --e(923)*/ (*(volatile Ifx_CPU_SYSCON*)0xF881FE14u)

/** \brief  8004, CPU Task Address Space Identifier Register */
#define CPU0_TASK_ASI /*lint --e(923)*/ (*(volatile Ifx_CPU_TASK_ASI*)0xF8818004u)

/** \brief  E400, CPU Temporal Protection System Control Register */
#define CPU0_TPS_CON /*lint --e(923)*/ (*(volatile Ifx_CPU_TPS_CON*)0xF881E400u)

/** \brief  E404, CPU Temporal Protection System Timer Register */
#define CPU0_TPS_TIMER0 /*lint --e(923)*/ (*(volatile Ifx_CPU_TPS_TIMER*)0xF881E404u)

/** \brief  E408, CPU Temporal Protection System Timer Register */
#define CPU0_TPS_TIMER1 /*lint --e(923)*/ (*(volatile Ifx_CPU_TPS_TIMER*)0xF881E408u)

/** \brief  E40C, CPU Temporal Protection System Timer Register */
#define CPU0_TPS_TIMER2 /*lint --e(923)*/ (*(volatile Ifx_CPU_TPS_TIMER*)0xF881E40Cu)

/** \brief  F004, Trigger Address */
#define CPU0_TR0_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF881F004u)

/** Alias (User Manual Name) for CPU0_TR0_ADR.
* To use register names with standard convension, please use CPU0_TR0_ADR.
*/
#define	CPU0_TR0ADR	(CPU0_TR0_ADR)

/** \brief  F000, Trigger Event */
#define CPU0_TR0_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF881F000u)

/** Alias (User Manual Name) for CPU0_TR0_EVT.
* To use register names with standard convension, please use CPU0_TR0_EVT.
*/
#define	CPU0_TR0EVT	(CPU0_TR0_EVT)

/** \brief  F00C, Trigger Address */
#define CPU0_TR1_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF881F00Cu)

/** Alias (User Manual Name) for CPU0_TR1_ADR.
* To use register names with standard convension, please use CPU0_TR1_ADR.
*/
#define	CPU0_TR1ADR	(CPU0_TR1_ADR)

/** \brief  F008, Trigger Event */
#define CPU0_TR1_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF881F008u)

/** Alias (User Manual Name) for CPU0_TR1_EVT.
* To use register names with standard convension, please use CPU0_TR1_EVT.
*/
#define	CPU0_TR1EVT	(CPU0_TR1_EVT)

/** \brief  F014, Trigger Address */
#define CPU0_TR2_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF881F014u)

/** Alias (User Manual Name) for CPU0_TR2_ADR.
* To use register names with standard convension, please use CPU0_TR2_ADR.
*/
#define	CPU0_TR2ADR	(CPU0_TR2_ADR)

/** \brief  F010, Trigger Event */
#define CPU0_TR2_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF881F010u)

/** Alias (User Manual Name) for CPU0_TR2_EVT.
* To use register names with standard convension, please use CPU0_TR2_EVT.
*/
#define	CPU0_TR2EVT	(CPU0_TR2_EVT)

/** \brief  F01C, Trigger Address */
#define CPU0_TR3_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF881F01Cu)

/** Alias (User Manual Name) for CPU0_TR3_ADR.
* To use register names with standard convension, please use CPU0_TR3_ADR.
*/
#define	CPU0_TR3ADR	(CPU0_TR3_ADR)

/** \brief  F018, Trigger Event */
#define CPU0_TR3_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF881F018u)

/** Alias (User Manual Name) for CPU0_TR3_EVT.
* To use register names with standard convension, please use CPU0_TR3_EVT.
*/
#define	CPU0_TR3EVT	(CPU0_TR3_EVT)

/** \brief  F024, Trigger Address */
#define CPU0_TR4_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF881F024u)

/** Alias (User Manual Name) for CPU0_TR4_ADR.
* To use register names with standard convension, please use CPU0_TR4_ADR.
*/
#define	CPU0_TR4ADR	(CPU0_TR4_ADR)

/** \brief  F020, Trigger Event */
#define CPU0_TR4_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF881F020u)

/** Alias (User Manual Name) for CPU0_TR4_EVT.
* To use register names with standard convension, please use CPU0_TR4_EVT.
*/
#define	CPU0_TR4EVT	(CPU0_TR4_EVT)

/** \brief  F02C, Trigger Address */
#define CPU0_TR5_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF881F02Cu)

/** Alias (User Manual Name) for CPU0_TR5_ADR.
* To use register names with standard convension, please use CPU0_TR5_ADR.
*/
#define	CPU0_TR5ADR	(CPU0_TR5_ADR)

/** \brief  F028, Trigger Event */
#define CPU0_TR5_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF881F028u)

/** Alias (User Manual Name) for CPU0_TR5_EVT.
* To use register names with standard convension, please use CPU0_TR5_EVT.
*/
#define	CPU0_TR5EVT	(CPU0_TR5_EVT)

/** \brief  F034, Trigger Address */
#define CPU0_TR6_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF881F034u)

/** Alias (User Manual Name) for CPU0_TR6_ADR.
* To use register names with standard convension, please use CPU0_TR6_ADR.
*/
#define	CPU0_TR6ADR	(CPU0_TR6_ADR)

/** \brief  F030, Trigger Event */
#define CPU0_TR6_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF881F030u)

/** Alias (User Manual Name) for CPU0_TR6_EVT.
* To use register names with standard convension, please use CPU0_TR6_EVT.
*/
#define	CPU0_TR6EVT	(CPU0_TR6_EVT)

/** \brief  F03C, Trigger Address */
#define CPU0_TR7_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF881F03Cu)

/** Alias (User Manual Name) for CPU0_TR7_ADR.
* To use register names with standard convension, please use CPU0_TR7_ADR.
*/
#define	CPU0_TR7ADR	(CPU0_TR7_ADR)

/** \brief  F038, Trigger Event */
#define CPU0_TR7_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF881F038u)

/** Alias (User Manual Name) for CPU0_TR7_EVT.
* To use register names with standard convension, please use CPU0_TR7_EVT.
*/
#define	CPU0_TR7EVT	(CPU0_TR7_EVT)

/** \brief  FD30, CPU Trigger Address x */
#define CPU0_TRIG_ACC /*lint --e(923)*/ (*(volatile Ifx_CPU_TRIG_ACC*)0xF881FD30u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_Cfg_Cpu1
 * \{  */

/** \brief  FF80, Address General Purpose Register */
#define CPU1_A0 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FF80u)

/** \brief  FF84, Address General Purpose Register */
#define CPU1_A1 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FF84u)

/** \brief  FFA8, Address General Purpose Register */
#define CPU1_A10 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FFA8u)

/** \brief  FFAC, Address General Purpose Register */
#define CPU1_A11 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FFACu)

/** \brief  FFB0, Address General Purpose Register */
#define CPU1_A12 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FFB0u)

/** \brief  FFB4, Address General Purpose Register */
#define CPU1_A13 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FFB4u)

/** \brief  FFB8, Address General Purpose Register */
#define CPU1_A14 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FFB8u)

/** \brief  FFBC, Address General Purpose Register */
#define CPU1_A15 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FFBCu)

/** \brief  FF88, Address General Purpose Register */
#define CPU1_A2 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FF88u)

/** \brief  FF8C, Address General Purpose Register */
#define CPU1_A3 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FF8Cu)

/** \brief  FF90, Address General Purpose Register */
#define CPU1_A4 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FF90u)

/** \brief  FF94, Address General Purpose Register */
#define CPU1_A5 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FF94u)

/** \brief  FF98, Address General Purpose Register */
#define CPU1_A6 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FF98u)

/** \brief  FF9C, Address General Purpose Register */
#define CPU1_A7 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FF9Cu)

/** \brief  FFA0, Address General Purpose Register */
#define CPU1_A8 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FFA0u)

/** \brief  FFA4, Address General Purpose Register */
#define CPU1_A9 /*lint --e(923)*/ (*(volatile Ifx_CPU_A*)0xF883FFA4u)

/** \brief  FE20, Base Interrupt Vector Table Pointer */
#define CPU1_BIV /*lint --e(923)*/ (*(volatile Ifx_CPU_BIV*)0xF883FE20u)

/** \brief  FE24, Base Trap Vector Table Pointer */
#define CPU1_BTV /*lint --e(923)*/ (*(volatile Ifx_CPU_BTV*)0xF883FE24u)

/** \brief  FC04, CPU Clock Cycle Count */
#define CPU1_CCNT /*lint --e(923)*/ (*(volatile Ifx_CPU_CCNT*)0xF883FC04u)

/** \brief  FC00, Counter Control */
#define CPU1_CCTRL /*lint --e(923)*/ (*(volatile Ifx_CPU_CCTRL*)0xF883FC00u)

/** \brief  9400, Compatibility Control Register */
#define CPU1_COMPAT /*lint --e(923)*/ (*(volatile Ifx_CPU_COMPAT*)0xF8839400u)

/** \brief  FE1C, CPU Core Identification Register */
#define CPU1_CORE_ID /*lint --e(923)*/ (*(volatile Ifx_CPU_CORE_ID*)0xF883FE1Cu)

/** \brief  D000, CPU Code Protection Range Lower Bound Register */
#define CPU1_CPR0_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF883D000u)

/** \brief  D004, CPU Code Protection Range Upper Bound Register */
#define CPU1_CPR0_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF883D004u)

/** \brief  D008, CPU Code Protection Range Lower Bound Register */
#define CPU1_CPR1_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF883D008u)

/** \brief  D00C, CPU Code Protection Range Upper Bound Register */
#define CPU1_CPR1_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF883D00Cu)

/** \brief  D010, CPU Code Protection Range Lower Bound Register */
#define CPU1_CPR2_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF883D010u)

/** \brief  D014, CPU Code Protection Range Upper Bound Register */
#define CPU1_CPR2_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF883D014u)

/** \brief  D018, CPU Code Protection Range Lower Bound Register */
#define CPU1_CPR3_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF883D018u)

/** \brief  D01C, CPU Code Protection Range Upper Bound Register */
#define CPU1_CPR3_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF883D01Cu)

/** \brief  D020, CPU Code Protection Range Lower Bound Register */
#define CPU1_CPR4_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF883D020u)

/** \brief  D024, CPU Code Protection Range Upper Bound Register */
#define CPU1_CPR4_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF883D024u)

/** \brief  D028, CPU Code Protection Range Lower Bound Register */
#define CPU1_CPR5_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF883D028u)

/** \brief  D02C, CPU Code Protection Range Upper Bound Register */
#define CPU1_CPR5_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF883D02Cu)

/** \brief  D030, CPU Code Protection Range Lower Bound Register */
#define CPU1_CPR6_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF883D030u)

/** \brief  D034, CPU Code Protection Range Upper Bound Register */
#define CPU1_CPR6_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF883D034u)

/** \brief  D038, CPU Code Protection Range Lower Bound Register */
#define CPU1_CPR7_L /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_L*)0xF883D038u)

/** \brief  D03C, CPU Code Protection Range Upper Bound Register */
#define CPU1_CPR7_U /*lint --e(923)*/ (*(volatile Ifx_CPU_CPR_U*)0xF883D03Cu)

/** \brief  FE18, CPU Identification Register TC1.6P */
#define CPU1_CPU_ID /*lint --e(923)*/ (*(volatile Ifx_CPU_CPU_ID*)0xF883FE18u)

/** \brief  E000, CPU Code Protection Execute Enable Register Set */
#define CPU1_CPXE0 /*lint --e(923)*/ (*(volatile Ifx_CPU_CPXE*)0xF883E000u)

/** Alias (User Manual Name) for CPU1_CPXE0.
* To use register names with standard convension, please use CPU1_CPXE0.
*/
#define	CPU1_CPXE_0	(CPU1_CPXE0)

/** \brief  E004, CPU Code Protection Execute Enable Register Set */
#define CPU1_CPXE1 /*lint --e(923)*/ (*(volatile Ifx_CPU_CPXE*)0xF883E004u)

/** Alias (User Manual Name) for CPU1_CPXE1.
* To use register names with standard convension, please use CPU1_CPXE1.
*/
#define	CPU1_CPXE_1	(CPU1_CPXE1)

/** \brief  E008, CPU Code Protection Execute Enable Register Set */
#define CPU1_CPXE2 /*lint --e(923)*/ (*(volatile Ifx_CPU_CPXE*)0xF883E008u)

/** Alias (User Manual Name) for CPU1_CPXE2.
* To use register names with standard convension, please use CPU1_CPXE2.
*/
#define	CPU1_CPXE_2	(CPU1_CPXE2)

/** \brief  E00C, CPU Code Protection Execute Enable Register Set */
#define CPU1_CPXE3 /*lint --e(923)*/ (*(volatile Ifx_CPU_CPXE*)0xF883E00Cu)

/** Alias (User Manual Name) for CPU1_CPXE3.
* To use register names with standard convension, please use CPU1_CPXE3.
*/
#define	CPU1_CPXE_3	(CPU1_CPXE3)

/** \brief  FD0C, Core Register Access Event */
#define CPU1_CREVT /*lint --e(923)*/ (*(volatile Ifx_CPU_CREVT*)0xF883FD0Cu)

/** \brief  FE50, CPU Customer ID register */
#define CPU1_CUS_ID /*lint --e(923)*/ (*(volatile Ifx_CPU_CUS_ID*)0xF883FE50u)

/** \brief  FF00, Data General Purpose Register */
#define CPU1_D0 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF00u)

/** \brief  FF04, Data General Purpose Register */
#define CPU1_D1 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF04u)

/** \brief  FF28, Data General Purpose Register */
#define CPU1_D10 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF28u)

/** \brief  FF2C, Data General Purpose Register */
#define CPU1_D11 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF2Cu)

/** \brief  FF30, Data General Purpose Register */
#define CPU1_D12 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF30u)

/** \brief  FF34, Data General Purpose Register */
#define CPU1_D13 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF34u)

/** \brief  FF38, Data General Purpose Register */
#define CPU1_D14 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF38u)

/** \brief  FF3C, Data General Purpose Register */
#define CPU1_D15 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF3Cu)

/** \brief  FF08, Data General Purpose Register */
#define CPU1_D2 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF08u)

/** \brief  FF0C, Data General Purpose Register */
#define CPU1_D3 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF0Cu)

/** \brief  FF10, Data General Purpose Register */
#define CPU1_D4 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF10u)

/** \brief  FF14, Data General Purpose Register */
#define CPU1_D5 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF14u)

/** \brief  FF18, Data General Purpose Register */
#define CPU1_D6 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF18u)

/** \brief  FF1C, Data General Purpose Register */
#define CPU1_D7 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF1Cu)

/** \brief  FF20, Data General Purpose Register */
#define CPU1_D8 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF20u)

/** \brief  FF24, Data General Purpose Register */
#define CPU1_D9 /*lint --e(923)*/ (*(volatile Ifx_CPU_D*)0xF883FF24u)

/** \brief  9018, Data Asynchronous Trap Register */
#define CPU1_DATR /*lint --e(923)*/ (*(volatile Ifx_CPU_DATR*)0xF8839018u)

/** \brief  FD00, Debug Status Register */
#define CPU1_DBGSR /*lint --e(923)*/ (*(volatile Ifx_CPU_DBGSR*)0xF883FD00u)

/** \brief  FD48, Debug Trap Control Register */
#define CPU1_DBGTCR /*lint --e(923)*/ (*(volatile Ifx_CPU_DBGTCR*)0xF883FD48u)

/** \brief  9040, Data Memory Control Register */
#define CPU1_DCON0 /*lint --e(923)*/ (*(volatile Ifx_CPU_DCON0*)0xF8839040u)

/** \brief  9000, Data Control Register 2 */
#define CPU1_DCON2 /*lint --e(923)*/ (*(volatile Ifx_CPU_DCON2*)0xF8839000u)

/** \brief  FD44, CPU Debug Context Save Area Pointer */
#define CPU1_DCX /*lint --e(923)*/ (*(volatile Ifx_CPU_DCX*)0xF883FD44u)

/** \brief  901C, Data Error Address Register */
#define CPU1_DEADD /*lint --e(923)*/ (*(volatile Ifx_CPU_DEADD*)0xF883901Cu)

/** \brief  9020, Data Integrity Error Address Register */
#define CPU1_DIEAR /*lint --e(923)*/ (*(volatile Ifx_CPU_DIEAR*)0xF8839020u)

/** \brief  9024, Data Integrity Error Trap Register */
#define CPU1_DIETR /*lint --e(923)*/ (*(volatile Ifx_CPU_DIETR*)0xF8839024u)

/** \brief  FD40, CPU Debug Monitor Start Address */
#define CPU1_DMS /*lint --e(923)*/ (*(volatile Ifx_CPU_DMS*)0xF883FD40u)

/** \brief  C000, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR0_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C000u)

/** \brief  C004, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR0_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C004u)

/** \brief  C050, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR10_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C050u)

/** \brief  C054, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR10_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C054u)

/** \brief  C058, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR11_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C058u)

/** \brief  C05C, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR11_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C05Cu)

/** \brief  C060, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR12_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C060u)

/** \brief  C064, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR12_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C064u)

/** \brief  C068, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR13_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C068u)

/** \brief  C06C, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR13_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C06Cu)

/** \brief  C070, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR14_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C070u)

/** \brief  C074, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR14_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C074u)

/** \brief  C078, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR15_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C078u)

/** \brief  C07C, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR15_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C07Cu)

/** \brief  C008, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR1_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C008u)

/** \brief  C00C, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR1_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C00Cu)

/** \brief  C010, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR2_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C010u)

/** \brief  C014, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR2_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C014u)

/** \brief  C018, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR3_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C018u)

/** \brief  C01C, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR3_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C01Cu)

/** \brief  C020, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR4_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C020u)

/** \brief  C024, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR4_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C024u)

/** \brief  C028, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR5_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C028u)

/** \brief  C02C, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR5_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C02Cu)

/** \brief  C030, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR6_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C030u)

/** \brief  C034, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR6_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C034u)

/** \brief  C038, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR7_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C038u)

/** \brief  C03C, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR7_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C03Cu)

/** \brief  C040, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR8_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C040u)

/** \brief  C044, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR8_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C044u)

/** \brief  C048, CPU Data Protection Range, Lower Bound Register */
#define CPU1_DPR9_L /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_L*)0xF883C048u)

/** \brief  C04C, CPU Data Protection Range, Upper Bound Register */
#define CPU1_DPR9_U /*lint --e(923)*/ (*(volatile Ifx_CPU_DPR_U*)0xF883C04Cu)

/** \brief  E010, CPU Data Protection Read Enable Register Set */
#define CPU1_DPRE0 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPRE*)0xF883E010u)

/** Alias (User Manual Name) for CPU1_DPRE0.
* To use register names with standard convension, please use CPU1_DPRE0.
*/
#define	CPU1_DPRE_0	(CPU1_DPRE0)

/** \brief  E014, CPU Data Protection Read Enable Register Set */
#define CPU1_DPRE1 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPRE*)0xF883E014u)

/** Alias (User Manual Name) for CPU1_DPRE1.
* To use register names with standard convension, please use CPU1_DPRE1.
*/
#define	CPU1_DPRE_1	(CPU1_DPRE1)

/** \brief  E018, CPU Data Protection Read Enable Register Set */
#define CPU1_DPRE2 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPRE*)0xF883E018u)

/** Alias (User Manual Name) for CPU1_DPRE2.
* To use register names with standard convension, please use CPU1_DPRE2.
*/
#define	CPU1_DPRE_2	(CPU1_DPRE2)

/** \brief  E01C, CPU Data Protection Read Enable Register Set */
#define CPU1_DPRE3 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPRE*)0xF883E01Cu)

/** Alias (User Manual Name) for CPU1_DPRE3.
* To use register names with standard convension, please use CPU1_DPRE3.
*/
#define	CPU1_DPRE_3	(CPU1_DPRE3)

/** \brief  E020, CPU Data Protection Write Enable Register Set */
#define CPU1_DPWE0 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPWE*)0xF883E020u)

/** Alias (User Manual Name) for CPU1_DPWE0.
* To use register names with standard convension, please use CPU1_DPWE0.
*/
#define	CPU1_DPWE_0	(CPU1_DPWE0)

/** \brief  E024, CPU Data Protection Write Enable Register Set */
#define CPU1_DPWE1 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPWE*)0xF883E024u)

/** Alias (User Manual Name) for CPU1_DPWE1.
* To use register names with standard convension, please use CPU1_DPWE1.
*/
#define	CPU1_DPWE_1	(CPU1_DPWE1)

/** \brief  E028, CPU Data Protection Write Enable Register Set */
#define CPU1_DPWE2 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPWE*)0xF883E028u)

/** Alias (User Manual Name) for CPU1_DPWE2.
* To use register names with standard convension, please use CPU1_DPWE2.
*/
#define	CPU1_DPWE_2	(CPU1_DPWE2)

/** \brief  E02C, CPU Data Protection Write Enable Register Set */
#define CPU1_DPWE3 /*lint --e(923)*/ (*(volatile Ifx_CPU_DPWE*)0xF883E02Cu)

/** Alias (User Manual Name) for CPU1_DPWE3.
* To use register names with standard convension, please use CPU1_DPWE3.
*/
#define	CPU1_DPWE_3	(CPU1_DPWE3)

/** \brief  9010, Data Synchronous Trap Register */
#define CPU1_DSTR /*lint --e(923)*/ (*(volatile Ifx_CPU_DSTR*)0xF8839010u)

/** \brief  FD08, External Event Register */
#define CPU1_EXEVT /*lint --e(923)*/ (*(volatile Ifx_CPU_EXEVT*)0xF883FD08u)

/** \brief  FE38, Free CSA List Head Pointer */
#define CPU1_FCX /*lint --e(923)*/ (*(volatile Ifx_CPU_FCX*)0xF883FE38u)

/** \brief  A000, CPU Trap Control Register */
#define CPU1_FPU_TRAP_CON /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_CON*)0xF883A000u)

/** \brief  A008, CPU Trapping Instruction Opcode Register */
#define CPU1_FPU_TRAP_OPC /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_OPC*)0xF883A008u)

/** \brief  A004, CPU Trapping Instruction Program Counter Register */
#define CPU1_FPU_TRAP_PC /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_PC*)0xF883A004u)

/** \brief  A010, CPU Trapping Instruction Operand Register */
#define CPU1_FPU_TRAP_SRC1 /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_SRC1*)0xF883A010u)

/** \brief  A014, CPU Trapping Instruction Operand Register */
#define CPU1_FPU_TRAP_SRC2 /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_SRC2*)0xF883A014u)

/** \brief  A018, Trapping Instruction Operand Register */
#define CPU1_FPU_TRAP_SRC3 /*lint --e(923)*/ (*(volatile Ifx_CPU_FPU_TRAP_SRC3*)0xF883A018u)

/** \brief  FC08, Instruction Count */
#define CPU1_ICNT /*lint --e(923)*/ (*(volatile Ifx_CPU_ICNT*)0xF883FC08u)

/** \brief  FE2C, Interrupt Control Register */
#define CPU1_ICR /*lint --e(923)*/ (*(volatile Ifx_CPU_ICR*)0xF883FE2Cu)

/** \brief  FE28, Interrupt Stack Pointer */
#define CPU1_ISP /*lint --e(923)*/ (*(volatile Ifx_CPU_ISP*)0xF883FE28u)

/** \brief  FE3C, Free CSA List Limit Pointer */
#define CPU1_LCX /*lint --e(923)*/ (*(volatile Ifx_CPU_LCX*)0xF883FE3Cu)

/** \brief  FC0C, Multi-Count Register 1 */
#define CPU1_M1CNT /*lint --e(923)*/ (*(volatile Ifx_CPU_M1CNT*)0xF883FC0Cu)

/** \brief  FC10, Multi-Count Register 2 */
#define CPU1_M2CNT /*lint --e(923)*/ (*(volatile Ifx_CPU_M2CNT*)0xF883FC10u)

/** \brief  FC14, Multi-Count Register 3 */
#define CPU1_M3CNT /*lint --e(923)*/ (*(volatile Ifx_CPU_M3CNT*)0xF883FC14u)

/** \brief  FE08, Program Counter */
#define CPU1_PC /*lint --e(923)*/ (*(volatile Ifx_CPU_PC*)0xF883FE08u)

/** \brief  920C, Program Control 0 */
#define CPU1_PCON0 /*lint --e(923)*/ (*(volatile Ifx_CPU_PCON0*)0xF883920Cu)

/** \brief  9204, Program Control 1 */
#define CPU1_PCON1 /*lint --e(923)*/ (*(volatile Ifx_CPU_PCON1*)0xF8839204u)

/** \brief  9208, Program Control 2 */
#define CPU1_PCON2 /*lint --e(923)*/ (*(volatile Ifx_CPU_PCON2*)0xF8839208u)

/** \brief  FE00, Previous Context Information Register */
#define CPU1_PCXI /*lint --e(923)*/ (*(volatile Ifx_CPU_PCXI*)0xF883FE00u)

/** \brief  9210, Program Integrity Error Address Register */
#define CPU1_PIEAR /*lint --e(923)*/ (*(volatile Ifx_CPU_PIEAR*)0xF8839210u)

/** \brief  9214, Program Integrity Error Trap Register */
#define CPU1_PIETR /*lint --e(923)*/ (*(volatile Ifx_CPU_PIETR*)0xF8839214u)

/** \brief  8100, Data Access CacheabilityRegister */
#define CPU1_PMA0 /*lint --e(923)*/ (*(volatile Ifx_CPU_PMA0*)0xF8838100u)

/** \brief  8104, Code Access CacheabilityRegister */
#define CPU1_PMA1 /*lint --e(923)*/ (*(volatile Ifx_CPU_PMA1*)0xF8838104u)

/** \brief  8108, Peripheral Space Identifier register */
#define CPU1_PMA2 /*lint --e(923)*/ (*(volatile Ifx_CPU_PMA2*)0xF8838108u)

/** \brief  9200, Program Synchronous Trap Register */
#define CPU1_PSTR /*lint --e(923)*/ (*(volatile Ifx_CPU_PSTR*)0xF8839200u)

/** \brief  FE04, Program Status Word */
#define CPU1_PSW /*lint --e(923)*/ (*(volatile Ifx_CPU_PSW*)0xF883FE04u)

/** \brief  1030, SRI Error Generation Register */
#define CPU1_SEGEN /*lint --e(923)*/ (*(volatile Ifx_CPU_SEGEN*)0xF8831030u)

/** \brief  900C, SIST Mode Access Control Register */
#define CPU1_SMACON /*lint --e(923)*/ (*(volatile Ifx_CPU_SMACON*)0xF883900Cu)

/** \brief  FD10, Software Debug Event */
#define CPU1_SWEVT /*lint --e(923)*/ (*(volatile Ifx_CPU_SWEVT*)0xF883FD10u)

/** \brief  FE14, System Configuration Register */
#define CPU1_SYSCON /*lint --e(923)*/ (*(volatile Ifx_CPU_SYSCON*)0xF883FE14u)

/** \brief  8004, CPU Task Address Space Identifier Register */
#define CPU1_TASK_ASI /*lint --e(923)*/ (*(volatile Ifx_CPU_TASK_ASI*)0xF8838004u)

/** \brief  E400, CPU Temporal Protection System Control Register */
#define CPU1_TPS_CON /*lint --e(923)*/ (*(volatile Ifx_CPU_TPS_CON*)0xF883E400u)

/** \brief  E404, CPU Temporal Protection System Timer Register */
#define CPU1_TPS_TIMER0 /*lint --e(923)*/ (*(volatile Ifx_CPU_TPS_TIMER*)0xF883E404u)

/** \brief  E408, CPU Temporal Protection System Timer Register */
#define CPU1_TPS_TIMER1 /*lint --e(923)*/ (*(volatile Ifx_CPU_TPS_TIMER*)0xF883E408u)

/** \brief  E40C, CPU Temporal Protection System Timer Register */
#define CPU1_TPS_TIMER2 /*lint --e(923)*/ (*(volatile Ifx_CPU_TPS_TIMER*)0xF883E40Cu)

/** \brief  F004, Trigger Address */
#define CPU1_TR0_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF883F004u)

/** Alias (User Manual Name) for CPU1_TR0_ADR.
* To use register names with standard convension, please use CPU1_TR0_ADR.
*/
#define	CPU1_TR0ADR	(CPU1_TR0_ADR)

/** \brief  F000, Trigger Event */
#define CPU1_TR0_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF883F000u)

/** Alias (User Manual Name) for CPU1_TR0_EVT.
* To use register names with standard convension, please use CPU1_TR0_EVT.
*/
#define	CPU1_TR0EVT	(CPU1_TR0_EVT)

/** \brief  F00C, Trigger Address */
#define CPU1_TR1_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF883F00Cu)

/** Alias (User Manual Name) for CPU1_TR1_ADR.
* To use register names with standard convension, please use CPU1_TR1_ADR.
*/
#define	CPU1_TR1ADR	(CPU1_TR1_ADR)

/** \brief  F008, Trigger Event */
#define CPU1_TR1_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF883F008u)

/** Alias (User Manual Name) for CPU1_TR1_EVT.
* To use register names with standard convension, please use CPU1_TR1_EVT.
*/
#define	CPU1_TR1EVT	(CPU1_TR1_EVT)

/** \brief  F014, Trigger Address */
#define CPU1_TR2_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF883F014u)

/** Alias (User Manual Name) for CPU1_TR2_ADR.
* To use register names with standard convension, please use CPU1_TR2_ADR.
*/
#define	CPU1_TR2ADR	(CPU1_TR2_ADR)

/** \brief  F010, Trigger Event */
#define CPU1_TR2_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF883F010u)

/** Alias (User Manual Name) for CPU1_TR2_EVT.
* To use register names with standard convension, please use CPU1_TR2_EVT.
*/
#define	CPU1_TR2EVT	(CPU1_TR2_EVT)

/** \brief  F01C, Trigger Address */
#define CPU1_TR3_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF883F01Cu)

/** Alias (User Manual Name) for CPU1_TR3_ADR.
* To use register names with standard convension, please use CPU1_TR3_ADR.
*/
#define	CPU1_TR3ADR	(CPU1_TR3_ADR)

/** \brief  F018, Trigger Event */
#define CPU1_TR3_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF883F018u)

/** Alias (User Manual Name) for CPU1_TR3_EVT.
* To use register names with standard convension, please use CPU1_TR3_EVT.
*/
#define	CPU1_TR3EVT	(CPU1_TR3_EVT)

/** \brief  F024, Trigger Address */
#define CPU1_TR4_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF883F024u)

/** Alias (User Manual Name) for CPU1_TR4_ADR.
* To use register names with standard convension, please use CPU1_TR4_ADR.
*/
#define	CPU1_TR4ADR	(CPU1_TR4_ADR)

/** \brief  F020, Trigger Event */
#define CPU1_TR4_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF883F020u)

/** Alias (User Manual Name) for CPU1_TR4_EVT.
* To use register names with standard convension, please use CPU1_TR4_EVT.
*/
#define	CPU1_TR4EVT	(CPU1_TR4_EVT)

/** \brief  F02C, Trigger Address */
#define CPU1_TR5_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF883F02Cu)

/** Alias (User Manual Name) for CPU1_TR5_ADR.
* To use register names with standard convension, please use CPU1_TR5_ADR.
*/
#define	CPU1_TR5ADR	(CPU1_TR5_ADR)

/** \brief  F028, Trigger Event */
#define CPU1_TR5_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF883F028u)

/** Alias (User Manual Name) for CPU1_TR5_EVT.
* To use register names with standard convension, please use CPU1_TR5_EVT.
*/
#define	CPU1_TR5EVT	(CPU1_TR5_EVT)

/** \brief  F034, Trigger Address */
#define CPU1_TR6_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF883F034u)

/** Alias (User Manual Name) for CPU1_TR6_ADR.
* To use register names with standard convension, please use CPU1_TR6_ADR.
*/
#define	CPU1_TR6ADR	(CPU1_TR6_ADR)

/** \brief  F030, Trigger Event */
#define CPU1_TR6_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF883F030u)

/** Alias (User Manual Name) for CPU1_TR6_EVT.
* To use register names with standard convension, please use CPU1_TR6_EVT.
*/
#define	CPU1_TR6EVT	(CPU1_TR6_EVT)

/** \brief  F03C, Trigger Address */
#define CPU1_TR7_ADR /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_ADR*)0xF883F03Cu)

/** Alias (User Manual Name) for CPU1_TR7_ADR.
* To use register names with standard convension, please use CPU1_TR7_ADR.
*/
#define	CPU1_TR7ADR	(CPU1_TR7_ADR)

/** \brief  F038, Trigger Event */
#define CPU1_TR7_EVT /*lint --e(923)*/ (*(volatile Ifx_CPU_TR_EVT*)0xF883F038u)

/** Alias (User Manual Name) for CPU1_TR7_EVT.
* To use register names with standard convension, please use CPU1_TR7_EVT.
*/
#define	CPU1_TR7EVT	(CPU1_TR7_EVT)

/** \brief  FD30, CPU Trigger Address x */
#define CPU1_TRIG_ACC /*lint --e(923)*/ (*(volatile Ifx_CPU_TRIG_ACC*)0xF883FD30u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_Cfg_Cpu
 * \{  */

/** \brief  FF80, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A0 0xFF80

/** \brief  FF84, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A1 0xFF84

/** \brief  FFA8, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A10 0xFFA8

/** \brief  FFAC, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A11 0xFFAC

/** \brief  FFB0, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A12 0xFFB0

/** \brief  FFB4, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A13 0xFFB4

/** \brief  FFB8, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A14 0xFFB8

/** \brief  FFBC, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A15 0xFFBC

/** \brief  FF88, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A2 0xFF88

/** \brief  FF8C, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A3 0xFF8C

/** \brief  FF90, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A4 0xFF90

/** \brief  FF94, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A5 0xFF94

/** \brief  FF98, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A6 0xFF98

/** \brief  FF9C, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A7 0xFF9C

/** \brief  FFA0, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A8 0xFFA0

/** \brief  FFA4, , type: Ifx_CPU_A, Address General Purpose Register */
#define CPU_A9 0xFFA4

/** \brief  FE20, , type: Ifx_CPU_BIV, Base Interrupt Vector Table Pointer */
#define CPU_BIV 0xFE20

/** \brief  FE24, , type: Ifx_CPU_BTV, Base Trap Vector Table Pointer */
#define CPU_BTV 0xFE24

/** \brief  FC04, , type: Ifx_CPU_CCNT, CPU Clock Cycle Count */
#define CPU_CCNT 0xFC04

/** \brief  FC00, , type: Ifx_CPU_CCTRL, Counter Control */
#define CPU_CCTRL 0xFC00

/** \brief  9400, , type: Ifx_CPU_COMPAT, Compatibility Control Register */
#define CPU_COMPAT 0x9400

/** \brief  FE1C, , type: Ifx_CPU_CORE_ID, CPU Core Identification Register */
#define CPU_CORE_ID 0xFE1C

/** \brief  D000, , type: Ifx_CPU_CPR_L, CPU Code Protection Range Lower Bound
 * Register */
#define CPU_CPR0_L 0xD000

/** \brief  D004, , type: Ifx_CPU_CPR_U, CPU Code Protection Range Upper Bound
 * Register */
#define CPU_CPR0_U 0xD004

/** \brief  D008, , type: Ifx_CPU_CPR_L, CPU Code Protection Range Lower Bound
 * Register */
#define CPU_CPR1_L 0xD008

/** \brief  D00C, , type: Ifx_CPU_CPR_U, CPU Code Protection Range Upper Bound
 * Register */
#define CPU_CPR1_U 0xD00C

/** \brief  D010, , type: Ifx_CPU_CPR_L, CPU Code Protection Range Lower Bound
 * Register */
#define CPU_CPR2_L 0xD010

/** \brief  D014, , type: Ifx_CPU_CPR_U, CPU Code Protection Range Upper Bound
 * Register */
#define CPU_CPR2_U 0xD014

/** \brief  D018, , type: Ifx_CPU_CPR_L, CPU Code Protection Range Lower Bound
 * Register */
#define CPU_CPR3_L 0xD018

/** \brief  D01C, , type: Ifx_CPU_CPR_U, CPU Code Protection Range Upper Bound
 * Register */
#define CPU_CPR3_U 0xD01C

/** \brief  D020, , type: Ifx_CPU_CPR_L, CPU Code Protection Range Lower Bound
 * Register */
#define CPU_CPR4_L 0xD020

/** \brief  D024, , type: Ifx_CPU_CPR_U, CPU Code Protection Range Upper Bound
 * Register */
#define CPU_CPR4_U 0xD024

/** \brief  D028, , type: Ifx_CPU_CPR_L, CPU Code Protection Range Lower Bound
 * Register */
#define CPU_CPR5_L 0xD028

/** \brief  D02C, , type: Ifx_CPU_CPR_U, CPU Code Protection Range Upper Bound
 * Register */
#define CPU_CPR5_U 0xD02C

/** \brief  D030, , type: Ifx_CPU_CPR_L, CPU Code Protection Range Lower Bound
 * Register */
#define CPU_CPR6_L 0xD030

/** \brief  D034, , type: Ifx_CPU_CPR_U, CPU Code Protection Range Upper Bound
 * Register */
#define CPU_CPR6_U 0xD034

/** \brief  D038, , type: Ifx_CPU_CPR_L, CPU Code Protection Range Lower Bound
 * Register */
#define CPU_CPR7_L 0xD038

/** \brief  D03C, , type: Ifx_CPU_CPR_U, CPU Code Protection Range Upper Bound
 * Register */
#define CPU_CPR7_U 0xD03C

/** \brief  FE18, , type: Ifx_CPU_CPU_ID, CPU Identification Register TC1.6P */
#define CPU_CPU_ID 0xFE18

/** \brief  E000, , type: Ifx_CPU_CPXE, CPU Code Protection Execute Enable
 * Register Set */
#define CPU_CPXE0 0xE000

/** \brief  E004, , type: Ifx_CPU_CPXE, CPU Code Protection Execute Enable
 * Register Set */
#define CPU_CPXE1 0xE004

/** \brief  E008, , type: Ifx_CPU_CPXE, CPU Code Protection Execute Enable
 * Register Set */
#define CPU_CPXE2 0xE008

/** \brief  E00C, , type: Ifx_CPU_CPXE, CPU Code Protection Execute Enable
 * Register Set */
#define CPU_CPXE3 0xE00C

/** \brief  FD0C, , type: Ifx_CPU_CREVT, Core Register Access Event */
#define CPU_CREVT 0xFD0C

/** \brief  FE50, , type: Ifx_CPU_CUS_ID, CPU Customer ID register */
#define CPU_CUS_ID 0xFE50

/** \brief  FF00, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D0 0xFF00

/** \brief  FF04, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D1 0xFF04

/** \brief  FF28, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D10 0xFF28

/** \brief  FF2C, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D11 0xFF2C

/** \brief  FF30, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D12 0xFF30

/** \brief  FF34, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D13 0xFF34

/** \brief  FF38, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D14 0xFF38

/** \brief  FF3C, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D15 0xFF3C

/** \brief  FF08, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D2 0xFF08

/** \brief  FF0C, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D3 0xFF0C

/** \brief  FF10, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D4 0xFF10

/** \brief  FF14, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D5 0xFF14

/** \brief  FF18, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D6 0xFF18

/** \brief  FF1C, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D7 0xFF1C

/** \brief  FF20, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D8 0xFF20

/** \brief  FF24, , type: Ifx_CPU_D, Data General Purpose Register */
#define CPU_D9 0xFF24

/** \brief  9018, , type: Ifx_CPU_DATR, Data Asynchronous Trap Register */
#define CPU_DATR 0x9018

/** \brief  FD00, , type: Ifx_CPU_DBGSR, Debug Status Register */
#define CPU_DBGSR 0xFD00

/** \brief  FD48, , type: Ifx_CPU_DBGTCR, Debug Trap Control Register */
#define CPU_DBGTCR 0xFD48

/** \brief  9040, , type: Ifx_CPU_DCON0, Data Memory Control Register */
#define CPU_DCON0 0x9040

/** \brief  9000, , type: Ifx_CPU_DCON2, Data Control Register 2 */
#define CPU_DCON2 0x9000

/** \brief  FD44, , type: Ifx_CPU_DCX, CPU Debug Context Save Area Pointer */
#define CPU_DCX 0xFD44

/** \brief  901C, , type: Ifx_CPU_DEADD, Data Error Address Register */
#define CPU_DEADD 0x901C

/** \brief  9020, , type: Ifx_CPU_DIEAR, Data Integrity Error Address Register */
#define CPU_DIEAR 0x9020

/** \brief  9024, , type: Ifx_CPU_DIETR, Data Integrity Error Trap Register */
#define CPU_DIETR 0x9024

/** \brief  FD40, , type: Ifx_CPU_DMS, CPU Debug Monitor Start Address */
#define CPU_DMS 0xFD40

/** \brief  C000, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR0_L 0xC000

/** \brief  C004, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR0_U 0xC004

/** \brief  C050, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR10_L 0xC050

/** \brief  C054, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR10_U 0xC054

/** \brief  C058, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR11_L 0xC058

/** \brief  C05C, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR11_U 0xC05C

/** \brief  C060, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR12_L 0xC060

/** \brief  C064, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR12_U 0xC064

/** \brief  C068, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR13_L 0xC068

/** \brief  C06C, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR13_U 0xC06C

/** \brief  C070, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR14_L 0xC070

/** \brief  C074, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR14_U 0xC074

/** \brief  C078, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR15_L 0xC078

/** \brief  C07C, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR15_U 0xC07C

/** \brief  C008, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR1_L 0xC008

/** \brief  C00C, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR1_U 0xC00C

/** \brief  C010, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR2_L 0xC010

/** \brief  C014, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR2_U 0xC014

/** \brief  C018, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR3_L 0xC018

/** \brief  C01C, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR3_U 0xC01C

/** \brief  C020, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR4_L 0xC020

/** \brief  C024, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR4_U 0xC024

/** \brief  C028, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR5_L 0xC028

/** \brief  C02C, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR5_U 0xC02C

/** \brief  C030, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR6_L 0xC030

/** \brief  C034, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR6_U 0xC034

/** \brief  C038, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR7_L 0xC038

/** \brief  C03C, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR7_U 0xC03C

/** \brief  C040, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR8_L 0xC040

/** \brief  C044, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR8_U 0xC044

/** \brief  C048, , type: Ifx_CPU_DPR_L, CPU Data Protection Range, Lower Bound
 * Register */
#define CPU_DPR9_L 0xC048

/** \brief  C04C, , type: Ifx_CPU_DPR_U, CPU Data Protection Range, Upper Bound
 * Register */
#define CPU_DPR9_U 0xC04C

/** \brief  E010, , type: Ifx_CPU_DPRE, CPU Data Protection Read Enable Register
 * Set */
#define CPU_DPRE0 0xE010

/** \brief  E014, , type: Ifx_CPU_DPRE, CPU Data Protection Read Enable Register
 * Set */
#define CPU_DPRE1 0xE014

/** \brief  E018, , type: Ifx_CPU_DPRE, CPU Data Protection Read Enable Register
 * Set */
#define CPU_DPRE2 0xE018

/** \brief  E01C, , type: Ifx_CPU_DPRE, CPU Data Protection Read Enable Register
 * Set */
#define CPU_DPRE3 0xE01C

/** \brief  E020, , type: Ifx_CPU_DPWE, CPU Data Protection Write Enable
 * Register Set */
#define CPU_DPWE0 0xE020

/** \brief  E024, , type: Ifx_CPU_DPWE, CPU Data Protection Write Enable
 * Register Set */
#define CPU_DPWE1 0xE024

/** \brief  E028, , type: Ifx_CPU_DPWE, CPU Data Protection Write Enable
 * Register Set */
#define CPU_DPWE2 0xE028

/** \brief  E02C, , type: Ifx_CPU_DPWE, CPU Data Protection Write Enable
 * Register Set */
#define CPU_DPWE3 0xE02C

/** \brief  9010, , type: Ifx_CPU_DSTR, Data Synchronous Trap Register */
#define CPU_DSTR 0x9010

/** \brief  FD08, , type: Ifx_CPU_EXEVT, External Event Register */
#define CPU_EXEVT 0xFD08

/** \brief  FE38, , type: Ifx_CPU_FCX, Free CSA List Head Pointer */
#define CPU_FCX 0xFE38

/** \brief  A000, , type: Ifx_CPU_FPU_TRAP_CON, CPU Trap Control Register */
#define CPU_FPU_TRAP_CON 0xA000

/** \brief  A008, , type: Ifx_CPU_FPU_TRAP_OPC, CPU Trapping Instruction Opcode
 * Register */
#define CPU_FPU_TRAP_OPC 0xA008

/** \brief  A004, , type: Ifx_CPU_FPU_TRAP_PC, CPU Trapping Instruction Program
 * Counter Register */
#define CPU_FPU_TRAP_PC 0xA004

/** \brief  A010, , type: Ifx_CPU_FPU_TRAP_SRC1, CPU Trapping Instruction
 * Operand Register */
#define CPU_FPU_TRAP_SRC1 0xA010

/** \brief  A014, , type: Ifx_CPU_FPU_TRAP_SRC2, CPU Trapping Instruction
 * Operand Register */
#define CPU_FPU_TRAP_SRC2 0xA014

/** \brief  A018, , type: Ifx_CPU_FPU_TRAP_SRC3, Trapping Instruction Operand
 * Register */
#define CPU_FPU_TRAP_SRC3 0xA018

/** \brief  FC08, , type: Ifx_CPU_ICNT, Instruction Count */
#define CPU_ICNT 0xFC08

/** \brief  FE2C, , type: Ifx_CPU_ICR, Interrupt Control Register */
#define CPU_ICR 0xFE2C

/** \brief  FE28, , type: Ifx_CPU_ISP, Interrupt Stack Pointer */
#define CPU_ISP 0xFE28

/** \brief  FE3C, , type: Ifx_CPU_LCX, Free CSA List Limit Pointer */
#define CPU_LCX 0xFE3C

/** \brief  FC0C, , type: Ifx_CPU_M1CNT, Multi-Count Register 1 */
#define CPU_M1CNT 0xFC0C

/** \brief  FC10, , type: Ifx_CPU_M2CNT, Multi-Count Register 2 */
#define CPU_M2CNT 0xFC10

/** \brief  FC14, , type: Ifx_CPU_M3CNT, Multi-Count Register 3 */
#define CPU_M3CNT 0xFC14

/** \brief  FE08, , type: Ifx_CPU_PC, Program Counter */
#define CPU_PC 0xFE08

/** \brief  920C, , type: Ifx_CPU_PCON0, Program Control 0 */
#define CPU_PCON0 0x920C

/** \brief  9204, , type: Ifx_CPU_PCON1, Program Control 1 */
#define CPU_PCON1 0x9204

/** \brief  9208, , type: Ifx_CPU_PCON2, Program Control 2 */
#define CPU_PCON2 0x9208

/** \brief  FE00, , type: Ifx_CPU_PCXI, Previous Context Information Register */
#define CPU_PCXI 0xFE00

/** \brief  9210, , type: Ifx_CPU_PIEAR, Program Integrity Error Address
 * Register */
#define CPU_PIEAR 0x9210

/** \brief  9214, , type: Ifx_CPU_PIETR, Program Integrity Error Trap Register */
#define CPU_PIETR 0x9214

/** \brief  8100, , type: Ifx_CPU_PMA0, Data Access CacheabilityRegister */
#define CPU_PMA0 0x8100

/** \brief  8104, , type: Ifx_CPU_PMA1, Code Access CacheabilityRegister */
#define CPU_PMA1 0x8104

/** \brief  8108, , type: Ifx_CPU_PMA2, Peripheral Space Identifier register */
#define CPU_PMA2 0x8108

/** \brief  9200, , type: Ifx_CPU_PSTR, Program Synchronous Trap Register */
#define CPU_PSTR 0x9200

/** \brief  FE04, , type: Ifx_CPU_PSW, Program Status Word */
#define CPU_PSW 0xFE04

/** \brief  1030, , type: Ifx_CPU_SEGEN, SRI Error Generation Register */
#define CPU_SEGEN 0x1030

/** \brief  900C, , type: Ifx_CPU_SMACON, SIST Mode Access Control Register */
#define CPU_SMACON 0x900C

/** \brief  FD10, , type: Ifx_CPU_SWEVT, Software Debug Event */
#define CPU_SWEVT 0xFD10

/** \brief  FE14, , type: Ifx_CPU_SYSCON, System Configuration Register */
#define CPU_SYSCON 0xFE14

/** \brief  8004, , type: Ifx_CPU_TASK_ASI, CPU Task Address Space Identifier
 * Register */
#define CPU_TASK_ASI 0x8004

/** \brief  E400, , type: Ifx_CPU_TPS_CON, CPU Temporal Protection System
 * Control Register */
#define CPU_TPS_CON 0xE400

/** \brief  E404, , type: Ifx_CPU_TPS_TIMER, CPU Temporal Protection System
 * Timer Register */
#define CPU_TPS_TIMER0 0xE404

/** \brief  E408, , type: Ifx_CPU_TPS_TIMER, CPU Temporal Protection System
 * Timer Register */
#define CPU_TPS_TIMER1 0xE408

/** \brief  E40C, , type: Ifx_CPU_TPS_TIMER, CPU Temporal Protection System
 * Timer Register */
#define CPU_TPS_TIMER2 0xE40C

/** \brief  F004, , type: Ifx_CPU_TR_ADR, Trigger Address */
#define CPU_TR0_ADR 0xF004

/** \brief  F000, , type: Ifx_CPU_TR_EVT, Trigger Event */
#define CPU_TR0_EVT 0xF000

/** \brief  F00C, , type: Ifx_CPU_TR_ADR, Trigger Address */
#define CPU_TR1_ADR 0xF00C

/** \brief  F008, , type: Ifx_CPU_TR_EVT, Trigger Event */
#define CPU_TR1_EVT 0xF008

/** \brief  F014, , type: Ifx_CPU_TR_ADR, Trigger Address */
#define CPU_TR2_ADR 0xF014

/** \brief  F010, , type: Ifx_CPU_TR_EVT, Trigger Event */
#define CPU_TR2_EVT 0xF010

/** \brief  F01C, , type: Ifx_CPU_TR_ADR, Trigger Address */
#define CPU_TR3_ADR 0xF01C

/** \brief  F018, , type: Ifx_CPU_TR_EVT, Trigger Event */
#define CPU_TR3_EVT 0xF018

/** \brief  F024, , type: Ifx_CPU_TR_ADR, Trigger Address */
#define CPU_TR4_ADR 0xF024

/** \brief  F020, , type: Ifx_CPU_TR_EVT, Trigger Event */
#define CPU_TR4_EVT 0xF020

/** \brief  F02C, , type: Ifx_CPU_TR_ADR, Trigger Address */
#define CPU_TR5_ADR 0xF02C

/** \brief  F028, , type: Ifx_CPU_TR_EVT, Trigger Event */
#define CPU_TR5_EVT 0xF028

/** \brief  F034, , type: Ifx_CPU_TR_ADR, Trigger Address */
#define CPU_TR6_ADR 0xF034

/** \brief  F030, , type: Ifx_CPU_TR_EVT, Trigger Event */
#define CPU_TR6_EVT 0xF030

/** \brief  F03C, , type: Ifx_CPU_TR_ADR, Trigger Address */
#define CPU_TR7_ADR 0xF03C

/** \brief  F038, , type: Ifx_CPU_TR_EVT, Trigger Event */
#define CPU_TR7_EVT 0xF038

/** \brief  FD30, , type: Ifx_CPU_TRIG_ACC, CPU Trigger Address x */
#define CPU_TRIG_ACC 0xFD30
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_Cfg_Cpu0_sprot
 * \{  */

/** \brief  E100, CPU Safety Protection Register Access Enable Register A */
#define CPU0_SPROT_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_ACCENA*)0xF880E100u)

/** \brief  E104, CPU Safety Protection Region Access Enable Register B */
#define CPU0_SPROT_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_ACCENB*)0xF880E104u)

/** \brief  E008, CPU Safety Protection Region Access Enable Register A */
#define CPU0_SPROT_RGN0_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF880E008u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN0_ACCENA.
* To use register names with standard convension, please use CPU0_SPROT_RGN0_ACCENA.
*/
#define	CPU0_SPROT_RGNACCENA0	(CPU0_SPROT_RGN0_ACCENA)

/** \brief  E00C, CPU Safety Protection Region Access Enable Register B */
#define CPU0_SPROT_RGN0_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF880E00Cu)

/** Alias (User Manual Name) for CPU0_SPROT_RGN0_ACCENB.
* To use register names with standard convension, please use CPU0_SPROT_RGN0_ACCENB.
*/
#define	CPU0_SPROT_RGNACCENB0	(CPU0_SPROT_RGN0_ACCENB)

/** \brief  E000, CPU Safety Protection Region Lower Address Register */
#define CPU0_SPROT_RGN0_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF880E000u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN0_LA.
* To use register names with standard convension, please use CPU0_SPROT_RGN0_LA.
*/
#define	CPU0_SPROT_RGNLA0	(CPU0_SPROT_RGN0_LA)

/** \brief  E004, CPU Safety protection Region Upper Address Register */
#define CPU0_SPROT_RGN0_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF880E004u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN0_UA.
* To use register names with standard convension, please use CPU0_SPROT_RGN0_UA.
*/
#define	CPU0_SPROT_RGNUA0	(CPU0_SPROT_RGN0_UA)

/** \brief  E018, CPU Safety Protection Region Access Enable Register A */
#define CPU0_SPROT_RGN1_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF880E018u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN1_ACCENA.
* To use register names with standard convension, please use CPU0_SPROT_RGN1_ACCENA.
*/
#define	CPU0_SPROT_RGNACCENA1	(CPU0_SPROT_RGN1_ACCENA)

/** \brief  E01C, CPU Safety Protection Region Access Enable Register B */
#define CPU0_SPROT_RGN1_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF880E01Cu)

/** Alias (User Manual Name) for CPU0_SPROT_RGN1_ACCENB.
* To use register names with standard convension, please use CPU0_SPROT_RGN1_ACCENB.
*/
#define	CPU0_SPROT_RGNACCENB1	(CPU0_SPROT_RGN1_ACCENB)

/** \brief  E010, CPU Safety Protection Region Lower Address Register */
#define CPU0_SPROT_RGN1_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF880E010u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN1_LA.
* To use register names with standard convension, please use CPU0_SPROT_RGN1_LA.
*/
#define	CPU0_SPROT_RGNLA1	(CPU0_SPROT_RGN1_LA)

/** \brief  E014, CPU Safety protection Region Upper Address Register */
#define CPU0_SPROT_RGN1_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF880E014u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN1_UA.
* To use register names with standard convension, please use CPU0_SPROT_RGN1_UA.
*/
#define	CPU0_SPROT_RGNUA1	(CPU0_SPROT_RGN1_UA)

/** \brief  E028, CPU Safety Protection Region Access Enable Register A */
#define CPU0_SPROT_RGN2_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF880E028u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN2_ACCENA.
* To use register names with standard convension, please use CPU0_SPROT_RGN2_ACCENA.
*/
#define	CPU0_SPROT_RGNACCENA2	(CPU0_SPROT_RGN2_ACCENA)

/** \brief  E02C, CPU Safety Protection Region Access Enable Register B */
#define CPU0_SPROT_RGN2_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF880E02Cu)

/** Alias (User Manual Name) for CPU0_SPROT_RGN2_ACCENB.
* To use register names with standard convension, please use CPU0_SPROT_RGN2_ACCENB.
*/
#define	CPU0_SPROT_RGNACCENB2	(CPU0_SPROT_RGN2_ACCENB)

/** \brief  E020, CPU Safety Protection Region Lower Address Register */
#define CPU0_SPROT_RGN2_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF880E020u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN2_LA.
* To use register names with standard convension, please use CPU0_SPROT_RGN2_LA.
*/
#define	CPU0_SPROT_RGNLA2	(CPU0_SPROT_RGN2_LA)

/** \brief  E024, CPU Safety protection Region Upper Address Register */
#define CPU0_SPROT_RGN2_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF880E024u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN2_UA.
* To use register names with standard convension, please use CPU0_SPROT_RGN2_UA.
*/
#define	CPU0_SPROT_RGNUA2	(CPU0_SPROT_RGN2_UA)

/** \brief  E038, CPU Safety Protection Region Access Enable Register A */
#define CPU0_SPROT_RGN3_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF880E038u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN3_ACCENA.
* To use register names with standard convension, please use CPU0_SPROT_RGN3_ACCENA.
*/
#define	CPU0_SPROT_RGNACCENA3	(CPU0_SPROT_RGN3_ACCENA)

/** \brief  E03C, CPU Safety Protection Region Access Enable Register B */
#define CPU0_SPROT_RGN3_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF880E03Cu)

/** Alias (User Manual Name) for CPU0_SPROT_RGN3_ACCENB.
* To use register names with standard convension, please use CPU0_SPROT_RGN3_ACCENB.
*/
#define	CPU0_SPROT_RGNACCENB3	(CPU0_SPROT_RGN3_ACCENB)

/** \brief  E030, CPU Safety Protection Region Lower Address Register */
#define CPU0_SPROT_RGN3_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF880E030u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN3_LA.
* To use register names with standard convension, please use CPU0_SPROT_RGN3_LA.
*/
#define	CPU0_SPROT_RGNLA3	(CPU0_SPROT_RGN3_LA)

/** \brief  E034, CPU Safety protection Region Upper Address Register */
#define CPU0_SPROT_RGN3_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF880E034u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN3_UA.
* To use register names with standard convension, please use CPU0_SPROT_RGN3_UA.
*/
#define	CPU0_SPROT_RGNUA3	(CPU0_SPROT_RGN3_UA)

/** \brief  E048, CPU Safety Protection Region Access Enable Register A */
#define CPU0_SPROT_RGN4_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF880E048u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN4_ACCENA.
* To use register names with standard convension, please use CPU0_SPROT_RGN4_ACCENA.
*/
#define	CPU0_SPROT_RGNACCENA4	(CPU0_SPROT_RGN4_ACCENA)

/** \brief  E04C, CPU Safety Protection Region Access Enable Register B */
#define CPU0_SPROT_RGN4_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF880E04Cu)

/** Alias (User Manual Name) for CPU0_SPROT_RGN4_ACCENB.
* To use register names with standard convension, please use CPU0_SPROT_RGN4_ACCENB.
*/
#define	CPU0_SPROT_RGNACCENB4	(CPU0_SPROT_RGN4_ACCENB)

/** \brief  E040, CPU Safety Protection Region Lower Address Register */
#define CPU0_SPROT_RGN4_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF880E040u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN4_LA.
* To use register names with standard convension, please use CPU0_SPROT_RGN4_LA.
*/
#define	CPU0_SPROT_RGNLA4	(CPU0_SPROT_RGN4_LA)

/** \brief  E044, CPU Safety protection Region Upper Address Register */
#define CPU0_SPROT_RGN4_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF880E044u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN4_UA.
* To use register names with standard convension, please use CPU0_SPROT_RGN4_UA.
*/
#define	CPU0_SPROT_RGNUA4	(CPU0_SPROT_RGN4_UA)

/** \brief  E058, CPU Safety Protection Region Access Enable Register A */
#define CPU0_SPROT_RGN5_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF880E058u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN5_ACCENA.
* To use register names with standard convension, please use CPU0_SPROT_RGN5_ACCENA.
*/
#define	CPU0_SPROT_RGNACCENA5	(CPU0_SPROT_RGN5_ACCENA)

/** \brief  E05C, CPU Safety Protection Region Access Enable Register B */
#define CPU0_SPROT_RGN5_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF880E05Cu)

/** Alias (User Manual Name) for CPU0_SPROT_RGN5_ACCENB.
* To use register names with standard convension, please use CPU0_SPROT_RGN5_ACCENB.
*/
#define	CPU0_SPROT_RGNACCENB5	(CPU0_SPROT_RGN5_ACCENB)

/** \brief  E050, CPU Safety Protection Region Lower Address Register */
#define CPU0_SPROT_RGN5_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF880E050u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN5_LA.
* To use register names with standard convension, please use CPU0_SPROT_RGN5_LA.
*/
#define	CPU0_SPROT_RGNLA5	(CPU0_SPROT_RGN5_LA)

/** \brief  E054, CPU Safety protection Region Upper Address Register */
#define CPU0_SPROT_RGN5_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF880E054u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN5_UA.
* To use register names with standard convension, please use CPU0_SPROT_RGN5_UA.
*/
#define	CPU0_SPROT_RGNUA5	(CPU0_SPROT_RGN5_UA)

/** \brief  E068, CPU Safety Protection Region Access Enable Register A */
#define CPU0_SPROT_RGN6_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF880E068u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN6_ACCENA.
* To use register names with standard convension, please use CPU0_SPROT_RGN6_ACCENA.
*/
#define	CPU0_SPROT_RGNACCENA6	(CPU0_SPROT_RGN6_ACCENA)

/** \brief  E06C, CPU Safety Protection Region Access Enable Register B */
#define CPU0_SPROT_RGN6_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF880E06Cu)

/** Alias (User Manual Name) for CPU0_SPROT_RGN6_ACCENB.
* To use register names with standard convension, please use CPU0_SPROT_RGN6_ACCENB.
*/
#define	CPU0_SPROT_RGNACCENB6	(CPU0_SPROT_RGN6_ACCENB)

/** \brief  E060, CPU Safety Protection Region Lower Address Register */
#define CPU0_SPROT_RGN6_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF880E060u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN6_LA.
* To use register names with standard convension, please use CPU0_SPROT_RGN6_LA.
*/
#define	CPU0_SPROT_RGNLA6	(CPU0_SPROT_RGN6_LA)

/** \brief  E064, CPU Safety protection Region Upper Address Register */
#define CPU0_SPROT_RGN6_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF880E064u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN6_UA.
* To use register names with standard convension, please use CPU0_SPROT_RGN6_UA.
*/
#define	CPU0_SPROT_RGNUA6	(CPU0_SPROT_RGN6_UA)

/** \brief  E078, CPU Safety Protection Region Access Enable Register A */
#define CPU0_SPROT_RGN7_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF880E078u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN7_ACCENA.
* To use register names with standard convension, please use CPU0_SPROT_RGN7_ACCENA.
*/
#define	CPU0_SPROT_RGNACCENA7	(CPU0_SPROT_RGN7_ACCENA)

/** \brief  E07C, CPU Safety Protection Region Access Enable Register B */
#define CPU0_SPROT_RGN7_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF880E07Cu)

/** Alias (User Manual Name) for CPU0_SPROT_RGN7_ACCENB.
* To use register names with standard convension, please use CPU0_SPROT_RGN7_ACCENB.
*/
#define	CPU0_SPROT_RGNACCENB7	(CPU0_SPROT_RGN7_ACCENB)

/** \brief  E070, CPU Safety Protection Region Lower Address Register */
#define CPU0_SPROT_RGN7_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF880E070u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN7_LA.
* To use register names with standard convension, please use CPU0_SPROT_RGN7_LA.
*/
#define	CPU0_SPROT_RGNLA7	(CPU0_SPROT_RGN7_LA)

/** \brief  E074, CPU Safety protection Region Upper Address Register */
#define CPU0_SPROT_RGN7_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF880E074u)

/** Alias (User Manual Name) for CPU0_SPROT_RGN7_UA.
* To use register names with standard convension, please use CPU0_SPROT_RGN7_UA.
*/
#define	CPU0_SPROT_RGNUA7	(CPU0_SPROT_RGN7_UA)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_Cfg_Cpu1_sprot
 * \{  */

/** \brief  E100, CPU Safety Protection Register Access Enable Register A */
#define CPU1_SPROT_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_ACCENA*)0xF882E100u)

/** \brief  E104, CPU Safety Protection Region Access Enable Register B */
#define CPU1_SPROT_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_ACCENB*)0xF882E104u)

/** \brief  E008, CPU Safety Protection Region Access Enable Register A */
#define CPU1_SPROT_RGN0_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF882E008u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN0_ACCENA.
* To use register names with standard convension, please use CPU1_SPROT_RGN0_ACCENA.
*/
#define	CPU1_SPROT_RGNACCENA0	(CPU1_SPROT_RGN0_ACCENA)

/** \brief  E00C, CPU Safety Protection Region Access Enable Register B */
#define CPU1_SPROT_RGN0_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF882E00Cu)

/** Alias (User Manual Name) for CPU1_SPROT_RGN0_ACCENB.
* To use register names with standard convension, please use CPU1_SPROT_RGN0_ACCENB.
*/
#define	CPU1_SPROT_RGNACCENB0	(CPU1_SPROT_RGN0_ACCENB)

/** \brief  E000, CPU Safety Protection Region Lower Address Register */
#define CPU1_SPROT_RGN0_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF882E000u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN0_LA.
* To use register names with standard convension, please use CPU1_SPROT_RGN0_LA.
*/
#define	CPU1_SPROT_RGNLA0	(CPU1_SPROT_RGN0_LA)

/** \brief  E004, CPU Safety protection Region Upper Address Register */
#define CPU1_SPROT_RGN0_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF882E004u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN0_UA.
* To use register names with standard convension, please use CPU1_SPROT_RGN0_UA.
*/
#define	CPU1_SPROT_RGNUA0	(CPU1_SPROT_RGN0_UA)

/** \brief  E018, CPU Safety Protection Region Access Enable Register A */
#define CPU1_SPROT_RGN1_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF882E018u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN1_ACCENA.
* To use register names with standard convension, please use CPU1_SPROT_RGN1_ACCENA.
*/
#define	CPU1_SPROT_RGNACCENA1	(CPU1_SPROT_RGN1_ACCENA)

/** \brief  E01C, CPU Safety Protection Region Access Enable Register B */
#define CPU1_SPROT_RGN1_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF882E01Cu)

/** Alias (User Manual Name) for CPU1_SPROT_RGN1_ACCENB.
* To use register names with standard convension, please use CPU1_SPROT_RGN1_ACCENB.
*/
#define	CPU1_SPROT_RGNACCENB1	(CPU1_SPROT_RGN1_ACCENB)

/** \brief  E010, CPU Safety Protection Region Lower Address Register */
#define CPU1_SPROT_RGN1_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF882E010u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN1_LA.
* To use register names with standard convension, please use CPU1_SPROT_RGN1_LA.
*/
#define	CPU1_SPROT_RGNLA1	(CPU1_SPROT_RGN1_LA)

/** \brief  E014, CPU Safety protection Region Upper Address Register */
#define CPU1_SPROT_RGN1_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF882E014u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN1_UA.
* To use register names with standard convension, please use CPU1_SPROT_RGN1_UA.
*/
#define	CPU1_SPROT_RGNUA1	(CPU1_SPROT_RGN1_UA)

/** \brief  E028, CPU Safety Protection Region Access Enable Register A */
#define CPU1_SPROT_RGN2_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF882E028u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN2_ACCENA.
* To use register names with standard convension, please use CPU1_SPROT_RGN2_ACCENA.
*/
#define	CPU1_SPROT_RGNACCENA2	(CPU1_SPROT_RGN2_ACCENA)

/** \brief  E02C, CPU Safety Protection Region Access Enable Register B */
#define CPU1_SPROT_RGN2_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF882E02Cu)

/** Alias (User Manual Name) for CPU1_SPROT_RGN2_ACCENB.
* To use register names with standard convension, please use CPU1_SPROT_RGN2_ACCENB.
*/
#define	CPU1_SPROT_RGNACCENB2	(CPU1_SPROT_RGN2_ACCENB)

/** \brief  E020, CPU Safety Protection Region Lower Address Register */
#define CPU1_SPROT_RGN2_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF882E020u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN2_LA.
* To use register names with standard convension, please use CPU1_SPROT_RGN2_LA.
*/
#define	CPU1_SPROT_RGNLA2	(CPU1_SPROT_RGN2_LA)

/** \brief  E024, CPU Safety protection Region Upper Address Register */
#define CPU1_SPROT_RGN2_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF882E024u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN2_UA.
* To use register names with standard convension, please use CPU1_SPROT_RGN2_UA.
*/
#define	CPU1_SPROT_RGNUA2	(CPU1_SPROT_RGN2_UA)

/** \brief  E038, CPU Safety Protection Region Access Enable Register A */
#define CPU1_SPROT_RGN3_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF882E038u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN3_ACCENA.
* To use register names with standard convension, please use CPU1_SPROT_RGN3_ACCENA.
*/
#define	CPU1_SPROT_RGNACCENA3	(CPU1_SPROT_RGN3_ACCENA)

/** \brief  E03C, CPU Safety Protection Region Access Enable Register B */
#define CPU1_SPROT_RGN3_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF882E03Cu)

/** Alias (User Manual Name) for CPU1_SPROT_RGN3_ACCENB.
* To use register names with standard convension, please use CPU1_SPROT_RGN3_ACCENB.
*/
#define	CPU1_SPROT_RGNACCENB3	(CPU1_SPROT_RGN3_ACCENB)

/** \brief  E030, CPU Safety Protection Region Lower Address Register */
#define CPU1_SPROT_RGN3_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF882E030u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN3_LA.
* To use register names with standard convension, please use CPU1_SPROT_RGN3_LA.
*/
#define	CPU1_SPROT_RGNLA3	(CPU1_SPROT_RGN3_LA)

/** \brief  E034, CPU Safety protection Region Upper Address Register */
#define CPU1_SPROT_RGN3_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF882E034u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN3_UA.
* To use register names with standard convension, please use CPU1_SPROT_RGN3_UA.
*/
#define	CPU1_SPROT_RGNUA3	(CPU1_SPROT_RGN3_UA)

/** \brief  E048, CPU Safety Protection Region Access Enable Register A */
#define CPU1_SPROT_RGN4_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF882E048u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN4_ACCENA.
* To use register names with standard convension, please use CPU1_SPROT_RGN4_ACCENA.
*/
#define	CPU1_SPROT_RGNACCENA4	(CPU1_SPROT_RGN4_ACCENA)

/** \brief  E04C, CPU Safety Protection Region Access Enable Register B */
#define CPU1_SPROT_RGN4_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF882E04Cu)

/** Alias (User Manual Name) for CPU1_SPROT_RGN4_ACCENB.
* To use register names with standard convension, please use CPU1_SPROT_RGN4_ACCENB.
*/
#define	CPU1_SPROT_RGNACCENB4	(CPU1_SPROT_RGN4_ACCENB)

/** \brief  E040, CPU Safety Protection Region Lower Address Register */
#define CPU1_SPROT_RGN4_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF882E040u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN4_LA.
* To use register names with standard convension, please use CPU1_SPROT_RGN4_LA.
*/
#define	CPU1_SPROT_RGNLA4	(CPU1_SPROT_RGN4_LA)

/** \brief  E044, CPU Safety protection Region Upper Address Register */
#define CPU1_SPROT_RGN4_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF882E044u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN4_UA.
* To use register names with standard convension, please use CPU1_SPROT_RGN4_UA.
*/
#define	CPU1_SPROT_RGNUA4	(CPU1_SPROT_RGN4_UA)

/** \brief  E058, CPU Safety Protection Region Access Enable Register A */
#define CPU1_SPROT_RGN5_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF882E058u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN5_ACCENA.
* To use register names with standard convension, please use CPU1_SPROT_RGN5_ACCENA.
*/
#define	CPU1_SPROT_RGNACCENA5	(CPU1_SPROT_RGN5_ACCENA)

/** \brief  E05C, CPU Safety Protection Region Access Enable Register B */
#define CPU1_SPROT_RGN5_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF882E05Cu)

/** Alias (User Manual Name) for CPU1_SPROT_RGN5_ACCENB.
* To use register names with standard convension, please use CPU1_SPROT_RGN5_ACCENB.
*/
#define	CPU1_SPROT_RGNACCENB5	(CPU1_SPROT_RGN5_ACCENB)

/** \brief  E050, CPU Safety Protection Region Lower Address Register */
#define CPU1_SPROT_RGN5_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF882E050u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN5_LA.
* To use register names with standard convension, please use CPU1_SPROT_RGN5_LA.
*/
#define	CPU1_SPROT_RGNLA5	(CPU1_SPROT_RGN5_LA)

/** \brief  E054, CPU Safety protection Region Upper Address Register */
#define CPU1_SPROT_RGN5_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF882E054u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN5_UA.
* To use register names with standard convension, please use CPU1_SPROT_RGN5_UA.
*/
#define	CPU1_SPROT_RGNUA5	(CPU1_SPROT_RGN5_UA)

/** \brief  E068, CPU Safety Protection Region Access Enable Register A */
#define CPU1_SPROT_RGN6_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF882E068u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN6_ACCENA.
* To use register names with standard convension, please use CPU1_SPROT_RGN6_ACCENA.
*/
#define	CPU1_SPROT_RGNACCENA6	(CPU1_SPROT_RGN6_ACCENA)

/** \brief  E06C, CPU Safety Protection Region Access Enable Register B */
#define CPU1_SPROT_RGN6_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF882E06Cu)

/** Alias (User Manual Name) for CPU1_SPROT_RGN6_ACCENB.
* To use register names with standard convension, please use CPU1_SPROT_RGN6_ACCENB.
*/
#define	CPU1_SPROT_RGNACCENB6	(CPU1_SPROT_RGN6_ACCENB)

/** \brief  E060, CPU Safety Protection Region Lower Address Register */
#define CPU1_SPROT_RGN6_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF882E060u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN6_LA.
* To use register names with standard convension, please use CPU1_SPROT_RGN6_LA.
*/
#define	CPU1_SPROT_RGNLA6	(CPU1_SPROT_RGN6_LA)

/** \brief  E064, CPU Safety protection Region Upper Address Register */
#define CPU1_SPROT_RGN6_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF882E064u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN6_UA.
* To use register names with standard convension, please use CPU1_SPROT_RGN6_UA.
*/
#define	CPU1_SPROT_RGNUA6	(CPU1_SPROT_RGN6_UA)

/** \brief  E078, CPU Safety Protection Region Access Enable Register A */
#define CPU1_SPROT_RGN7_ACCENA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENA*)0xF882E078u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN7_ACCENA.
* To use register names with standard convension, please use CPU1_SPROT_RGN7_ACCENA.
*/
#define	CPU1_SPROT_RGNACCENA7	(CPU1_SPROT_RGN7_ACCENA)

/** \brief  E07C, CPU Safety Protection Region Access Enable Register B */
#define CPU1_SPROT_RGN7_ACCENB /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_ACCENB*)0xF882E07Cu)

/** Alias (User Manual Name) for CPU1_SPROT_RGN7_ACCENB.
* To use register names with standard convension, please use CPU1_SPROT_RGN7_ACCENB.
*/
#define	CPU1_SPROT_RGNACCENB7	(CPU1_SPROT_RGN7_ACCENB)

/** \brief  E070, CPU Safety Protection Region Lower Address Register */
#define CPU1_SPROT_RGN7_LA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_LA*)0xF882E070u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN7_LA.
* To use register names with standard convension, please use CPU1_SPROT_RGN7_LA.
*/
#define	CPU1_SPROT_RGNLA7	(CPU1_SPROT_RGN7_LA)

/** \brief  E074, CPU Safety protection Region Upper Address Register */
#define CPU1_SPROT_RGN7_UA /*lint --e(923)*/ (*(volatile Ifx_CPU_SPROT_RGN_UA*)0xF882E074u)

/** Alias (User Manual Name) for CPU1_SPROT_RGN7_UA.
* To use register names with standard convension, please use CPU1_SPROT_RGN7_UA.
*/
#define	CPU1_SPROT_RGNUA7	(CPU1_SPROT_RGN7_UA)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXCPU_REG_H */
