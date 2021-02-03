/**
 * \file IfxVadc_reg.h
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
 * \defgroup IfxLld_Vadc_Cfg Vadc address
 * \ingroup IfxLld_Vadc
 * 
 * \defgroup IfxLld_Vadc_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Vadc_Cfg
 * 
 * \defgroup IfxLld_Vadc_Cfg_Vadc 2-VADC
 * \ingroup IfxLld_Vadc_Cfg
 * 
 */
#ifndef IFXVADC_REG_H
#define IFXVADC_REG_H 1
/******************************************************************************/
#include "IfxVadc_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Vadc_Cfg_BaseAddress
 * \{  */

/** \brief  VADC object */
#define MODULE_VADC /*lint --e(923)*/ (*(Ifx_VADC*)0xF0020000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Vadc_Cfg_Vadc
 * \{  */

/** \brief  3C, Access Enable Register 0 */
#define VADC_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_VADC_ACCEN0*)0xF002003Cu)

/** \brief  88, Access Protection Register */
#define VADC_ACCPROT0 /*lint --e(923)*/ (*(volatile Ifx_VADC_ACCPROT0*)0xF0020088u)

/** \brief  8C, Access Protection Register */
#define VADC_ACCPROT1 /*lint --e(923)*/ (*(volatile Ifx_VADC_ACCPROT1*)0xF002008Cu)

/** \brief  200, Background Request Source Control Register */
#define VADC_BRSCTRL /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSCTRL*)0xF0020200u)

/** \brief  204, Background Request Source Mode Register */
#define VADC_BRSMR /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSMR*)0xF0020204u)

/** \brief  1C0, Background Request Source Pending Register, Group */
#define VADC_BRSPND0 /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSPND*)0xF00201C0u)

/** \brief  1C4, Background Request Source Pending Register, Group */
#define VADC_BRSPND1 /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSPND*)0xF00201C4u)

/** \brief  1C8, Background Request Source Pending Register, Group */
#define VADC_BRSPND2 /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSPND*)0xF00201C8u)

/** \brief  1CC, Background Request Source Pending Register, Group */
#define VADC_BRSPND3 /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSPND*)0xF00201CCu)

/** \brief  180, Background Request Source Channel Select Register, Group */
#define VADC_BRSSEL0 /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSSEL*)0xF0020180u)

/** \brief  184, Background Request Source Channel Select Register, Group */
#define VADC_BRSSEL1 /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSSEL*)0xF0020184u)

/** \brief  188, Background Request Source Channel Select Register, Group */
#define VADC_BRSSEL2 /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSSEL*)0xF0020188u)

/** \brief  18C, Background Request Source Channel Select Register, Group */
#define VADC_BRSSEL3 /*lint --e(923)*/ (*(volatile Ifx_VADC_BRSSEL*)0xF002018Cu)

/** \brief  0, Clock Control Register */
#define VADC_CLC /*lint --e(923)*/ (*(volatile Ifx_VADC_CLC*)0xF0020000u)

/** \brief  3F0, External Multiplexer Select Register */
#define VADC_EMUXSEL /*lint --e(923)*/ (*(volatile Ifx_VADC_EMUXSEL*)0xF00203F0u)

/** \brief  4B0, Alias Register, Group */
#define VADC_G0_ALIAS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ALIAS*)0xF00204B0u)

/** Alias (User Manual Name) for VADC_G0_ALIAS.
* To use register names with standard convension, please use VADC_G0_ALIAS.
*/
#define	VADC_G0ALIAS	(VADC_G0_ALIAS)

/** \brief  480, Arbitration Configuration Register, Group */
#define VADC_G0_ARBCFG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ARBCFG*)0xF0020480u)

/** Alias (User Manual Name) for VADC_G0_ARBCFG.
* To use register names with standard convension, please use VADC_G0_ARBCFG.
*/
#define	VADC_G0ARBCFG	(VADC_G0_ARBCFG)

/** \brief  484, Arbitration Priority Register, Group */
#define VADC_G0_ARBPR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ARBPR*)0xF0020484u)

/** Alias (User Manual Name) for VADC_G0_ARBPR.
* To use register names with standard convension, please use VADC_G0_ARBPR.
*/
#define	VADC_G0ARBPR	(VADC_G0_ARBPR)

/** \brief  520, Autoscan Source Control Register, Group */
#define VADC_G0_ASCTRL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASCTRL*)0xF0020520u)

/** Alias (User Manual Name) for VADC_G0_ASCTRL.
* To use register names with standard convension, please use VADC_G0_ASCTRL.
*/
#define	VADC_G0ASCTRL	(VADC_G0_ASCTRL)

/** \brief  524, Autoscan Source Mode Register, Group */
#define VADC_G0_ASMR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASMR*)0xF0020524u)

/** Alias (User Manual Name) for VADC_G0_ASMR.
* To use register names with standard convension, please use VADC_G0_ASMR.
*/
#define	VADC_G0ASMR	(VADC_G0_ASMR)

/** \brief  52C, Autoscan Source Pending Register, Group */
#define VADC_G0_ASPND /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASPND*)0xF002052Cu)

/** Alias (User Manual Name) for VADC_G0_ASPND.
* To use register names with standard convension, please use VADC_G0_ASPND.
*/
#define	VADC_G0ASPND	(VADC_G0_ASPND)

/** \brief  528, Autoscan Source Channel Select Register, Group */
#define VADC_G0_ASSEL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASSEL*)0xF0020528u)

/** Alias (User Manual Name) for VADC_G0_ASSEL.
* To use register names with standard convension, please use VADC_G0_ASSEL.
*/
#define	VADC_G0ASSEL	(VADC_G0_ASSEL)

/** \brief  4C8, Boundary Flag Register, Group */
#define VADC_G0_BFL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFL*)0xF00204C8u)

/** Alias (User Manual Name) for VADC_G0_BFL.
* To use register names with standard convension, please use VADC_G0_BFL.
*/
#define	VADC_G0BFL	(VADC_G0_BFL)

/** \brief  4D0, Boundary Flag Control Register, Group */
#define VADC_G0_BFLC /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLC*)0xF00204D0u)

/** Alias (User Manual Name) for VADC_G0_BFLC.
* To use register names with standard convension, please use VADC_G0_BFLC.
*/
#define	VADC_G0BFLC	(VADC_G0_BFLC)

/** \brief  4D4, Boundary Flag Node Pointer Register, Group */
#define VADC_G0_BFLNP /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLNP*)0xF00204D4u)

/** Alias (User Manual Name) for VADC_G0_BFLNP.
* To use register names with standard convension, please use VADC_G0_BFLNP.
*/
#define	VADC_G0BFLNP	(VADC_G0_BFLNP)

/** \brief  4CC, Boundary Flag Software Register, Group */
#define VADC_G0_BFLS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLS*)0xF00204CCu)

/** Alias (User Manual Name) for VADC_G0_BFLS.
* To use register names with standard convension, please use VADC_G0_BFLS.
*/
#define	VADC_G0BFLS	(VADC_G0_BFLS)

/** \brief  4B8, Boundary Select Register, Group */
#define VADC_G0_BOUND /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BOUND*)0xF00204B8u)

/** Alias (User Manual Name) for VADC_G0_BOUND.
* To use register names with standard convension, please use VADC_G0_BOUND.
*/
#define	VADC_G0BOUND	(VADC_G0_BOUND)

/** \brief  590, Channel Event Flag Clear Register, Group */
#define VADC_G0_CEFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEFCLR*)0xF0020590u)

/** Alias (User Manual Name) for VADC_G0_CEFCLR.
* To use register names with standard convension, please use VADC_G0_CEFCLR.
*/
#define	VADC_G0CEFCLR	(VADC_G0_CEFCLR)

/** \brief  580, Channel Event Flag Register, Group */
#define VADC_G0_CEFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEFLAG*)0xF0020580u)

/** Alias (User Manual Name) for VADC_G0_CEFLAG.
* To use register names with standard convension, please use VADC_G0_CEFLAG.
*/
#define	VADC_G0CEFLAG	(VADC_G0_CEFLAG)

/** \brief  5A0, Channel Event Node Pointer Register 0, Group */
#define VADC_G0_CEVNP0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEVNP0*)0xF00205A0u)

/** Alias (User Manual Name) for VADC_G0_CEVNP0.
* To use register names with standard convension, please use VADC_G0_CEVNP0.
*/
#define	VADC_G0CEVNP0	(VADC_G0_CEVNP0)

/** \brief  5A4, Channel Event Node Pointer Register 1, Group */
#define VADC_G0_CEVNP1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEVNP1*)0xF00205A4u)

/** Alias (User Manual Name) for VADC_G0_CEVNP1.
* To use register names with standard convension, please use VADC_G0_CEVNP1.
*/
#define	VADC_G0CEVNP1	(VADC_G0_CEVNP1)

/** \brief  488, Channel Assignment Register, Group */
#define VADC_G0_CHASS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHASS*)0xF0020488u)

/** Alias (User Manual Name) for VADC_G0_CHASS.
* To use register names with standard convension, please use VADC_G0_CHASS.
*/
#define	VADC_G0CHASS	(VADC_G0_CHASS)

/** \brief  600, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020600u)

/** Alias (User Manual Name) for VADC_G0_CHCTR0.
* To use register names with standard convension, please use VADC_G0_CHCTR0.
*/
#define	VADC_G0CHCTR0	(VADC_G0_CHCTR0)

/** \brief  604, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020604u)

/** Alias (User Manual Name) for VADC_G0_CHCTR1.
* To use register names with standard convension, please use VADC_G0_CHCTR1.
*/
#define	VADC_G0CHCTR1	(VADC_G0_CHCTR1)

/** \brief  628, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020628u)

/** Alias (User Manual Name) for VADC_G0_CHCTR10.
* To use register names with standard convension, please use VADC_G0_CHCTR10.
*/
#define	VADC_G0CHCTR10	(VADC_G0_CHCTR10)

/** \brief  62C, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF002062Cu)

/** Alias (User Manual Name) for VADC_G0_CHCTR11.
* To use register names with standard convension, please use VADC_G0_CHCTR11.
*/
#define	VADC_G0CHCTR11	(VADC_G0_CHCTR11)

/** \brief  630, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020630u)

/** Alias (User Manual Name) for VADC_G0_CHCTR12.
* To use register names with standard convension, please use VADC_G0_CHCTR12.
*/
#define	VADC_G0CHCTR12	(VADC_G0_CHCTR12)

/** \brief  634, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020634u)

/** Alias (User Manual Name) for VADC_G0_CHCTR13.
* To use register names with standard convension, please use VADC_G0_CHCTR13.
*/
#define	VADC_G0CHCTR13	(VADC_G0_CHCTR13)

/** \brief  638, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020638u)

/** Alias (User Manual Name) for VADC_G0_CHCTR14.
* To use register names with standard convension, please use VADC_G0_CHCTR14.
*/
#define	VADC_G0CHCTR14	(VADC_G0_CHCTR14)

/** \brief  63C, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF002063Cu)

/** Alias (User Manual Name) for VADC_G0_CHCTR15.
* To use register names with standard convension, please use VADC_G0_CHCTR15.
*/
#define	VADC_G0CHCTR15	(VADC_G0_CHCTR15)

/** \brief  608, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020608u)

/** Alias (User Manual Name) for VADC_G0_CHCTR2.
* To use register names with standard convension, please use VADC_G0_CHCTR2.
*/
#define	VADC_G0CHCTR2	(VADC_G0_CHCTR2)

/** \brief  60C, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF002060Cu)

/** Alias (User Manual Name) for VADC_G0_CHCTR3.
* To use register names with standard convension, please use VADC_G0_CHCTR3.
*/
#define	VADC_G0CHCTR3	(VADC_G0_CHCTR3)

/** \brief  610, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020610u)

/** Alias (User Manual Name) for VADC_G0_CHCTR4.
* To use register names with standard convension, please use VADC_G0_CHCTR4.
*/
#define	VADC_G0CHCTR4	(VADC_G0_CHCTR4)

/** \brief  614, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020614u)

/** Alias (User Manual Name) for VADC_G0_CHCTR5.
* To use register names with standard convension, please use VADC_G0_CHCTR5.
*/
#define	VADC_G0CHCTR5	(VADC_G0_CHCTR5)

/** \brief  618, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020618u)

/** Alias (User Manual Name) for VADC_G0_CHCTR6.
* To use register names with standard convension, please use VADC_G0_CHCTR6.
*/
#define	VADC_G0CHCTR6	(VADC_G0_CHCTR6)

/** \brief  61C, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF002061Cu)

/** Alias (User Manual Name) for VADC_G0_CHCTR7.
* To use register names with standard convension, please use VADC_G0_CHCTR7.
*/
#define	VADC_G0CHCTR7	(VADC_G0_CHCTR7)

/** \brief  620, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020620u)

/** Alias (User Manual Name) for VADC_G0_CHCTR8.
* To use register names with standard convension, please use VADC_G0_CHCTR8.
*/
#define	VADC_G0CHCTR8	(VADC_G0_CHCTR8)

/** \brief  624, Group, Channel Ctrl. Reg. */
#define VADC_G0_CHCTR9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020624u)

/** Alias (User Manual Name) for VADC_G0_CHCTR9.
* To use register names with standard convension, please use VADC_G0_CHCTR9.
*/
#define	VADC_G0CHCTR9	(VADC_G0_CHCTR9)

/** \brief  5F0, External Multiplexer Control Register, Group x */
#define VADC_G0_EMUXCTR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_EMUXCTR*)0xF00205F0u)

/** Alias (User Manual Name) for VADC_G0_EMUXCTR.
* To use register names with standard convension, please use VADC_G0_EMUXCTR.
*/
#define	VADC_G0EMUXCTR	(VADC_G0_EMUXCTR)

/** \brief  4A0, Input Class Register */
#define VADC_G0_ICLASS0 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF00204A0u)

/** Alias (User Manual Name) for VADC_G0_ICLASS0.
* To use register names with standard convension, please use VADC_G0_ICLASS0.
*/
#define	VADC_G0ICLASS0	(VADC_G0_ICLASS0)

/** \brief  4A4, Input Class Register */
#define VADC_G0_ICLASS1 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF00204A4u)

/** Alias (User Manual Name) for VADC_G0_ICLASS1.
* To use register names with standard convension, please use VADC_G0_ICLASS1.
*/
#define	VADC_G0ICLASS1	(VADC_G0_ICLASS1)

/** \brief  50C, Queue 0 Register 0, Group */
#define VADC_G0_Q0R0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_Q0R0*)0xF002050Cu)

/** Alias (User Manual Name) for VADC_G0_Q0R0.
* To use register names with standard convension, please use VADC_G0_Q0R0.
*/
#define	VADC_G0Q0R0	(VADC_G0_Q0R0)

/** \brief  510, Queue 0 Input Register, Group */
#define VADC_G0_QBUR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QBUR0*)0xF0020510u)

/** Alias (User Manual Name) for VADC_G0_QBUR0.
* To use register names with standard convension, please use VADC_G0_QBUR0.
*/
#define	VADC_G0QBUR0	(VADC_G0_QBUR0)

/** \brief  500, Queue 0 Source Control Register, Group */
#define VADC_G0_QCTRL0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QCTRL0*)0xF0020500u)

/** Alias (User Manual Name) for VADC_G0_QCTRL0.
* To use register names with standard convension, please use VADC_G0_QCTRL0.
*/
#define	VADC_G0QCTRL0	(VADC_G0_QCTRL0)

/** \brief  510, Queue 0 Input Register, Group */
#define VADC_G0_QINR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QINR0*)0xF0020510u)

/** Alias (User Manual Name) for VADC_G0_QINR0.
* To use register names with standard convension, please use VADC_G0_QINR0.
*/
#define	VADC_G0QINR0	(VADC_G0_QINR0)

/** \brief  504, Queue 0 Mode Register, Group */
#define VADC_G0_QMR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QMR0*)0xF0020504u)

/** Alias (User Manual Name) for VADC_G0_QMR0.
* To use register names with standard convension, please use VADC_G0_QMR0.
*/
#define	VADC_G0QMR0	(VADC_G0_QMR0)

/** \brief  508, Queue 0 Status Register, Group */
#define VADC_G0_QSR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QSR0*)0xF0020508u)

/** Alias (User Manual Name) for VADC_G0_QSR0.
* To use register names with standard convension, please use VADC_G0_QSR0.
*/
#define	VADC_G0QSR0	(VADC_G0_QSR0)

/** \brief  680, Group Result Control Reg. */
#define VADC_G0_RCR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020680u)

/** Alias (User Manual Name) for VADC_G0_RCR0.
* To use register names with standard convension, please use VADC_G0_RCR0.
*/
#define	VADC_G0RCR0	(VADC_G0_RCR0)

/** \brief  684, Group Result Control Reg. */
#define VADC_G0_RCR1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020684u)

/** Alias (User Manual Name) for VADC_G0_RCR1.
* To use register names with standard convension, please use VADC_G0_RCR1.
*/
#define	VADC_G0RCR1	(VADC_G0_RCR1)

/** \brief  6A8, Group Result Control Reg. */
#define VADC_G0_RCR10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00206A8u)

/** Alias (User Manual Name) for VADC_G0_RCR10.
* To use register names with standard convension, please use VADC_G0_RCR10.
*/
#define	VADC_G0RCR10	(VADC_G0_RCR10)

/** \brief  6AC, Group Result Control Reg. */
#define VADC_G0_RCR11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00206ACu)

/** Alias (User Manual Name) for VADC_G0_RCR11.
* To use register names with standard convension, please use VADC_G0_RCR11.
*/
#define	VADC_G0RCR11	(VADC_G0_RCR11)

/** \brief  6B0, Group Result Control Reg. */
#define VADC_G0_RCR12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00206B0u)

/** Alias (User Manual Name) for VADC_G0_RCR12.
* To use register names with standard convension, please use VADC_G0_RCR12.
*/
#define	VADC_G0RCR12	(VADC_G0_RCR12)

/** \brief  6B4, Group Result Control Reg. */
#define VADC_G0_RCR13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00206B4u)

/** Alias (User Manual Name) for VADC_G0_RCR13.
* To use register names with standard convension, please use VADC_G0_RCR13.
*/
#define	VADC_G0RCR13	(VADC_G0_RCR13)

/** \brief  6B8, Group Result Control Reg. */
#define VADC_G0_RCR14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00206B8u)

/** Alias (User Manual Name) for VADC_G0_RCR14.
* To use register names with standard convension, please use VADC_G0_RCR14.
*/
#define	VADC_G0RCR14	(VADC_G0_RCR14)

/** \brief  6BC, Group Result Control Reg. */
#define VADC_G0_RCR15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00206BCu)

/** Alias (User Manual Name) for VADC_G0_RCR15.
* To use register names with standard convension, please use VADC_G0_RCR15.
*/
#define	VADC_G0RCR15	(VADC_G0_RCR15)

/** \brief  688, Group Result Control Reg. */
#define VADC_G0_RCR2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020688u)

/** Alias (User Manual Name) for VADC_G0_RCR2.
* To use register names with standard convension, please use VADC_G0_RCR2.
*/
#define	VADC_G0RCR2	(VADC_G0_RCR2)

/** \brief  68C, Group Result Control Reg. */
#define VADC_G0_RCR3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF002068Cu)

/** Alias (User Manual Name) for VADC_G0_RCR3.
* To use register names with standard convension, please use VADC_G0_RCR3.
*/
#define	VADC_G0RCR3	(VADC_G0_RCR3)

/** \brief  690, Group Result Control Reg. */
#define VADC_G0_RCR4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020690u)

/** Alias (User Manual Name) for VADC_G0_RCR4.
* To use register names with standard convension, please use VADC_G0_RCR4.
*/
#define	VADC_G0RCR4	(VADC_G0_RCR4)

/** \brief  694, Group Result Control Reg. */
#define VADC_G0_RCR5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020694u)

/** Alias (User Manual Name) for VADC_G0_RCR5.
* To use register names with standard convension, please use VADC_G0_RCR5.
*/
#define	VADC_G0RCR5	(VADC_G0_RCR5)

/** \brief  698, Group Result Control Reg. */
#define VADC_G0_RCR6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020698u)

/** Alias (User Manual Name) for VADC_G0_RCR6.
* To use register names with standard convension, please use VADC_G0_RCR6.
*/
#define	VADC_G0RCR6	(VADC_G0_RCR6)

/** \brief  69C, Group Result Control Reg. */
#define VADC_G0_RCR7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF002069Cu)

/** Alias (User Manual Name) for VADC_G0_RCR7.
* To use register names with standard convension, please use VADC_G0_RCR7.
*/
#define	VADC_G0RCR7	(VADC_G0_RCR7)

/** \brief  6A0, Group Result Control Reg. */
#define VADC_G0_RCR8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00206A0u)

/** Alias (User Manual Name) for VADC_G0_RCR8.
* To use register names with standard convension, please use VADC_G0_RCR8.
*/
#define	VADC_G0RCR8	(VADC_G0_RCR8)

/** \brief  6A4, Group Result Control Reg. */
#define VADC_G0_RCR9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00206A4u)

/** Alias (User Manual Name) for VADC_G0_RCR9.
* To use register names with standard convension, please use VADC_G0_RCR9.
*/
#define	VADC_G0RCR9	(VADC_G0_RCR9)

/** \brief  594, Result Event Flag Clear Register, Group */
#define VADC_G0_REFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REFCLR*)0xF0020594u)

/** Alias (User Manual Name) for VADC_G0_REFCLR.
* To use register names with standard convension, please use VADC_G0_REFCLR.
*/
#define	VADC_G0REFCLR	(VADC_G0_REFCLR)

/** \brief  584, Result Event Flag Register, Group */
#define VADC_G0_REFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REFLAG*)0xF0020584u)

/** Alias (User Manual Name) for VADC_G0_REFLAG.
* To use register names with standard convension, please use VADC_G0_REFLAG.
*/
#define	VADC_G0REFLAG	(VADC_G0_REFLAG)

/** \brief  700, Group Result Register */
#define VADC_G0_RES0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020700u)

/** Alias (User Manual Name) for VADC_G0_RES0.
* To use register names with standard convension, please use VADC_G0_RES0.
*/
#define	VADC_G0RES0	(VADC_G0_RES0)

/** \brief  704, Group Result Register */
#define VADC_G0_RES1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020704u)

/** Alias (User Manual Name) for VADC_G0_RES1.
* To use register names with standard convension, please use VADC_G0_RES1.
*/
#define	VADC_G0RES1	(VADC_G0_RES1)

/** \brief  728, Group Result Register */
#define VADC_G0_RES10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020728u)

/** Alias (User Manual Name) for VADC_G0_RES10.
* To use register names with standard convension, please use VADC_G0_RES10.
*/
#define	VADC_G0RES10	(VADC_G0_RES10)

/** \brief  72C, Group Result Register */
#define VADC_G0_RES11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF002072Cu)

/** Alias (User Manual Name) for VADC_G0_RES11.
* To use register names with standard convension, please use VADC_G0_RES11.
*/
#define	VADC_G0RES11	(VADC_G0_RES11)

/** \brief  730, Group Result Register */
#define VADC_G0_RES12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020730u)

/** Alias (User Manual Name) for VADC_G0_RES12.
* To use register names with standard convension, please use VADC_G0_RES12.
*/
#define	VADC_G0RES12	(VADC_G0_RES12)

/** \brief  734, Group Result Register */
#define VADC_G0_RES13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020734u)

/** Alias (User Manual Name) for VADC_G0_RES13.
* To use register names with standard convension, please use VADC_G0_RES13.
*/
#define	VADC_G0RES13	(VADC_G0_RES13)

/** \brief  738, Group Result Register */
#define VADC_G0_RES14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020738u)

/** Alias (User Manual Name) for VADC_G0_RES14.
* To use register names with standard convension, please use VADC_G0_RES14.
*/
#define	VADC_G0RES14	(VADC_G0_RES14)

/** \brief  73C, Group Result Register */
#define VADC_G0_RES15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF002073Cu)

/** Alias (User Manual Name) for VADC_G0_RES15.
* To use register names with standard convension, please use VADC_G0_RES15.
*/
#define	VADC_G0RES15	(VADC_G0_RES15)

/** \brief  708, Group Result Register */
#define VADC_G0_RES2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020708u)

/** Alias (User Manual Name) for VADC_G0_RES2.
* To use register names with standard convension, please use VADC_G0_RES2.
*/
#define	VADC_G0RES2	(VADC_G0_RES2)

/** \brief  70C, Group Result Register */
#define VADC_G0_RES3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF002070Cu)

/** Alias (User Manual Name) for VADC_G0_RES3.
* To use register names with standard convension, please use VADC_G0_RES3.
*/
#define	VADC_G0RES3	(VADC_G0_RES3)

/** \brief  710, Group Result Register */
#define VADC_G0_RES4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020710u)

/** Alias (User Manual Name) for VADC_G0_RES4.
* To use register names with standard convension, please use VADC_G0_RES4.
*/
#define	VADC_G0RES4	(VADC_G0_RES4)

/** \brief  714, Group Result Register */
#define VADC_G0_RES5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020714u)

/** Alias (User Manual Name) for VADC_G0_RES5.
* To use register names with standard convension, please use VADC_G0_RES5.
*/
#define	VADC_G0RES5	(VADC_G0_RES5)

/** \brief  718, Group Result Register */
#define VADC_G0_RES6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020718u)

/** Alias (User Manual Name) for VADC_G0_RES6.
* To use register names with standard convension, please use VADC_G0_RES6.
*/
#define	VADC_G0RES6	(VADC_G0_RES6)

/** \brief  71C, Group Result Register */
#define VADC_G0_RES7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF002071Cu)

/** Alias (User Manual Name) for VADC_G0_RES7.
* To use register names with standard convension, please use VADC_G0_RES7.
*/
#define	VADC_G0RES7	(VADC_G0_RES7)

/** \brief  720, Group Result Register */
#define VADC_G0_RES8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020720u)

/** Alias (User Manual Name) for VADC_G0_RES8.
* To use register names with standard convension, please use VADC_G0_RES8.
*/
#define	VADC_G0RES8	(VADC_G0_RES8)

/** \brief  724, Group Result Register */
#define VADC_G0_RES9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020724u)

/** Alias (User Manual Name) for VADC_G0_RES9.
* To use register names with standard convension, please use VADC_G0_RES9.
*/
#define	VADC_G0RES9	(VADC_G0_RES9)

/** \brief  780, Group Result Reg., Debug */
#define VADC_G0_RESD0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020780u)

/** Alias (User Manual Name) for VADC_G0_RESD0.
* To use register names with standard convension, please use VADC_G0_RESD0.
*/
#define	VADC_G0RESD0	(VADC_G0_RESD0)

/** \brief  784, Group Result Reg., Debug */
#define VADC_G0_RESD1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020784u)

/** Alias (User Manual Name) for VADC_G0_RESD1.
* To use register names with standard convension, please use VADC_G0_RESD1.
*/
#define	VADC_G0RESD1	(VADC_G0_RESD1)

/** \brief  7A8, Group Result Reg., Debug */
#define VADC_G0_RESD10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00207A8u)

/** Alias (User Manual Name) for VADC_G0_RESD10.
* To use register names with standard convension, please use VADC_G0_RESD10.
*/
#define	VADC_G0RESD10	(VADC_G0_RESD10)

/** \brief  7AC, Group Result Reg., Debug */
#define VADC_G0_RESD11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00207ACu)

/** Alias (User Manual Name) for VADC_G0_RESD11.
* To use register names with standard convension, please use VADC_G0_RESD11.
*/
#define	VADC_G0RESD11	(VADC_G0_RESD11)

/** \brief  7B0, Group Result Reg., Debug */
#define VADC_G0_RESD12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00207B0u)

/** Alias (User Manual Name) for VADC_G0_RESD12.
* To use register names with standard convension, please use VADC_G0_RESD12.
*/
#define	VADC_G0RESD12	(VADC_G0_RESD12)

/** \brief  7B4, Group Result Reg., Debug */
#define VADC_G0_RESD13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00207B4u)

/** Alias (User Manual Name) for VADC_G0_RESD13.
* To use register names with standard convension, please use VADC_G0_RESD13.
*/
#define	VADC_G0RESD13	(VADC_G0_RESD13)

/** \brief  7B8, Group Result Reg., Debug */
#define VADC_G0_RESD14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00207B8u)

/** Alias (User Manual Name) for VADC_G0_RESD14.
* To use register names with standard convension, please use VADC_G0_RESD14.
*/
#define	VADC_G0RESD14	(VADC_G0_RESD14)

/** \brief  7BC, Group Result Reg., Debug */
#define VADC_G0_RESD15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00207BCu)

/** Alias (User Manual Name) for VADC_G0_RESD15.
* To use register names with standard convension, please use VADC_G0_RESD15.
*/
#define	VADC_G0RESD15	(VADC_G0_RESD15)

/** \brief  788, Group Result Reg., Debug */
#define VADC_G0_RESD2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020788u)

/** Alias (User Manual Name) for VADC_G0_RESD2.
* To use register names with standard convension, please use VADC_G0_RESD2.
*/
#define	VADC_G0RESD2	(VADC_G0_RESD2)

/** \brief  78C, Group Result Reg., Debug */
#define VADC_G0_RESD3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF002078Cu)

/** Alias (User Manual Name) for VADC_G0_RESD3.
* To use register names with standard convension, please use VADC_G0_RESD3.
*/
#define	VADC_G0RESD3	(VADC_G0_RESD3)

/** \brief  790, Group Result Reg., Debug */
#define VADC_G0_RESD4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020790u)

/** Alias (User Manual Name) for VADC_G0_RESD4.
* To use register names with standard convension, please use VADC_G0_RESD4.
*/
#define	VADC_G0RESD4	(VADC_G0_RESD4)

/** \brief  794, Group Result Reg., Debug */
#define VADC_G0_RESD5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020794u)

/** Alias (User Manual Name) for VADC_G0_RESD5.
* To use register names with standard convension, please use VADC_G0_RESD5.
*/
#define	VADC_G0RESD5	(VADC_G0_RESD5)

/** \brief  798, Group Result Reg., Debug */
#define VADC_G0_RESD6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020798u)

/** Alias (User Manual Name) for VADC_G0_RESD6.
* To use register names with standard convension, please use VADC_G0_RESD6.
*/
#define	VADC_G0RESD6	(VADC_G0_RESD6)

/** \brief  79C, Group Result Reg., Debug */
#define VADC_G0_RESD7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF002079Cu)

/** Alias (User Manual Name) for VADC_G0_RESD7.
* To use register names with standard convension, please use VADC_G0_RESD7.
*/
#define	VADC_G0RESD7	(VADC_G0_RESD7)

/** \brief  7A0, Group Result Reg., Debug */
#define VADC_G0_RESD8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00207A0u)

/** Alias (User Manual Name) for VADC_G0_RESD8.
* To use register names with standard convension, please use VADC_G0_RESD8.
*/
#define	VADC_G0RESD8	(VADC_G0_RESD8)

/** \brief  7A4, Group Result Reg., Debug */
#define VADC_G0_RESD9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00207A4u)

/** Alias (User Manual Name) for VADC_G0_RESD9.
* To use register names with standard convension, please use VADC_G0_RESD9.
*/
#define	VADC_G0RESD9	(VADC_G0_RESD9)

/** \brief  5B0, Result Event Node Pointer Register 0, Group */
#define VADC_G0_REVNP0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REVNP0*)0xF00205B0u)

/** Alias (User Manual Name) for VADC_G0_REVNP0.
* To use register names with standard convension, please use VADC_G0_REVNP0.
*/
#define	VADC_G0REVNP0	(VADC_G0_REVNP0)

/** \brief  5B4, Result Event Node Pointer Register 1, Group */
#define VADC_G0_REVNP1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REVNP1*)0xF00205B4u)

/** Alias (User Manual Name) for VADC_G0_REVNP1.
* To use register names with standard convension, please use VADC_G0_REVNP1.
*/
#define	VADC_G0REVNP1	(VADC_G0_REVNP1)

/** \brief  48C, Result Assignment Register, Group */
#define VADC_G0_RRASS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RRASS*)0xF002048Cu)

/** Alias (User Manual Name) for VADC_G0_RRASS.
* To use register names with standard convension, please use VADC_G0_RRASS.
*/
#define	VADC_G0RRASS	(VADC_G0_RRASS)

/** \brief  598, Source Event Flag Clear Register, Group */
#define VADC_G0_SEFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEFCLR*)0xF0020598u)

/** Alias (User Manual Name) for VADC_G0_SEFCLR.
* To use register names with standard convension, please use VADC_G0_SEFCLR.
*/
#define	VADC_G0SEFCLR	(VADC_G0_SEFCLR)

/** \brief  588, Source Event Flag Register, Group */
#define VADC_G0_SEFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEFLAG*)0xF0020588u)

/** Alias (User Manual Name) for VADC_G0_SEFLAG.
* To use register names with standard convension, please use VADC_G0_SEFLAG.
*/
#define	VADC_G0SEFLAG	(VADC_G0_SEFLAG)

/** \brief  5C0, Source Event Node Pointer Register, Group */
#define VADC_G0_SEVNP /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEVNP*)0xF00205C0u)

/** Alias (User Manual Name) for VADC_G0_SEVNP.
* To use register names with standard convension, please use VADC_G0_SEVNP.
*/
#define	VADC_G0SEVNP	(VADC_G0_SEVNP)

/** \brief  5C8, Service Request Software Activation Trigger, Group */
#define VADC_G0_SRACT /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SRACT*)0xF00205C8u)

/** Alias (User Manual Name) for VADC_G0_SRACT.
* To use register names with standard convension, please use VADC_G0_SRACT.
*/
#define	VADC_G0SRACT	(VADC_G0_SRACT)

/** \brief  4C0, Synchronization Control Register, Group */
#define VADC_G0_SYNCTR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SYNCTR*)0xF00204C0u)

/** Alias (User Manual Name) for VADC_G0_SYNCTR.
* To use register names with standard convension, please use VADC_G0_SYNCTR.
*/
#define	VADC_G0SYNCTR	(VADC_G0_SYNCTR)

/** \brief  5F8, Valid Flag Register, Group */
#define VADC_G0_VFR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_VFR*)0xF00205F8u)

/** Alias (User Manual Name) for VADC_G0_VFR.
* To use register names with standard convension, please use VADC_G0_VFR.
*/
#define	VADC_G0VFR	(VADC_G0_VFR)

/** \brief  8B0, Alias Register, Group */
#define VADC_G1_ALIAS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ALIAS*)0xF00208B0u)

/** Alias (User Manual Name) for VADC_G1_ALIAS.
* To use register names with standard convension, please use VADC_G1_ALIAS.
*/
#define	VADC_G1ALIAS	(VADC_G1_ALIAS)

/** \brief  880, Arbitration Configuration Register, Group */
#define VADC_G1_ARBCFG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ARBCFG*)0xF0020880u)

/** Alias (User Manual Name) for VADC_G1_ARBCFG.
* To use register names with standard convension, please use VADC_G1_ARBCFG.
*/
#define	VADC_G1ARBCFG	(VADC_G1_ARBCFG)

/** \brief  884, Arbitration Priority Register, Group */
#define VADC_G1_ARBPR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ARBPR*)0xF0020884u)

/** Alias (User Manual Name) for VADC_G1_ARBPR.
* To use register names with standard convension, please use VADC_G1_ARBPR.
*/
#define	VADC_G1ARBPR	(VADC_G1_ARBPR)

/** \brief  920, Autoscan Source Control Register, Group */
#define VADC_G1_ASCTRL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASCTRL*)0xF0020920u)

/** Alias (User Manual Name) for VADC_G1_ASCTRL.
* To use register names with standard convension, please use VADC_G1_ASCTRL.
*/
#define	VADC_G1ASCTRL	(VADC_G1_ASCTRL)

/** \brief  924, Autoscan Source Mode Register, Group */
#define VADC_G1_ASMR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASMR*)0xF0020924u)

/** Alias (User Manual Name) for VADC_G1_ASMR.
* To use register names with standard convension, please use VADC_G1_ASMR.
*/
#define	VADC_G1ASMR	(VADC_G1_ASMR)

/** \brief  92C, Autoscan Source Pending Register, Group */
#define VADC_G1_ASPND /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASPND*)0xF002092Cu)

/** Alias (User Manual Name) for VADC_G1_ASPND.
* To use register names with standard convension, please use VADC_G1_ASPND.
*/
#define	VADC_G1ASPND	(VADC_G1_ASPND)

/** \brief  928, Autoscan Source Channel Select Register, Group */
#define VADC_G1_ASSEL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASSEL*)0xF0020928u)

/** Alias (User Manual Name) for VADC_G1_ASSEL.
* To use register names with standard convension, please use VADC_G1_ASSEL.
*/
#define	VADC_G1ASSEL	(VADC_G1_ASSEL)

/** \brief  8C8, Boundary Flag Register, Group */
#define VADC_G1_BFL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFL*)0xF00208C8u)

/** Alias (User Manual Name) for VADC_G1_BFL.
* To use register names with standard convension, please use VADC_G1_BFL.
*/
#define	VADC_G1BFL	(VADC_G1_BFL)

/** \brief  8D0, Boundary Flag Control Register, Group */
#define VADC_G1_BFLC /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLC*)0xF00208D0u)

/** Alias (User Manual Name) for VADC_G1_BFLC.
* To use register names with standard convension, please use VADC_G1_BFLC.
*/
#define	VADC_G1BFLC	(VADC_G1_BFLC)

/** \brief  8D4, Boundary Flag Node Pointer Register, Group */
#define VADC_G1_BFLNP /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLNP*)0xF00208D4u)

/** Alias (User Manual Name) for VADC_G1_BFLNP.
* To use register names with standard convension, please use VADC_G1_BFLNP.
*/
#define	VADC_G1BFLNP	(VADC_G1_BFLNP)

/** \brief  8CC, Boundary Flag Software Register, Group */
#define VADC_G1_BFLS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLS*)0xF00208CCu)

/** Alias (User Manual Name) for VADC_G1_BFLS.
* To use register names with standard convension, please use VADC_G1_BFLS.
*/
#define	VADC_G1BFLS	(VADC_G1_BFLS)

/** \brief  8B8, Boundary Select Register, Group */
#define VADC_G1_BOUND /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BOUND*)0xF00208B8u)

/** Alias (User Manual Name) for VADC_G1_BOUND.
* To use register names with standard convension, please use VADC_G1_BOUND.
*/
#define	VADC_G1BOUND	(VADC_G1_BOUND)

/** \brief  990, Channel Event Flag Clear Register, Group */
#define VADC_G1_CEFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEFCLR*)0xF0020990u)

/** Alias (User Manual Name) for VADC_G1_CEFCLR.
* To use register names with standard convension, please use VADC_G1_CEFCLR.
*/
#define	VADC_G1CEFCLR	(VADC_G1_CEFCLR)

/** \brief  980, Channel Event Flag Register, Group */
#define VADC_G1_CEFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEFLAG*)0xF0020980u)

/** Alias (User Manual Name) for VADC_G1_CEFLAG.
* To use register names with standard convension, please use VADC_G1_CEFLAG.
*/
#define	VADC_G1CEFLAG	(VADC_G1_CEFLAG)

/** \brief  9A0, Channel Event Node Pointer Register 0, Group */
#define VADC_G1_CEVNP0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEVNP0*)0xF00209A0u)

/** Alias (User Manual Name) for VADC_G1_CEVNP0.
* To use register names with standard convension, please use VADC_G1_CEVNP0.
*/
#define	VADC_G1CEVNP0	(VADC_G1_CEVNP0)

/** \brief  9A4, Channel Event Node Pointer Register 1, Group */
#define VADC_G1_CEVNP1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEVNP1*)0xF00209A4u)

/** Alias (User Manual Name) for VADC_G1_CEVNP1.
* To use register names with standard convension, please use VADC_G1_CEVNP1.
*/
#define	VADC_G1CEVNP1	(VADC_G1_CEVNP1)

/** \brief  888, Channel Assignment Register, Group */
#define VADC_G1_CHASS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHASS*)0xF0020888u)

/** Alias (User Manual Name) for VADC_G1_CHASS.
* To use register names with standard convension, please use VADC_G1_CHASS.
*/
#define	VADC_G1CHASS	(VADC_G1_CHASS)

/** \brief  A00, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A00u)

/** Alias (User Manual Name) for VADC_G1_CHCTR0.
* To use register names with standard convension, please use VADC_G1_CHCTR0.
*/
#define	VADC_G1CHCTR0	(VADC_G1_CHCTR0)

/** \brief  A04, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A04u)

/** Alias (User Manual Name) for VADC_G1_CHCTR1.
* To use register names with standard convension, please use VADC_G1_CHCTR1.
*/
#define	VADC_G1CHCTR1	(VADC_G1_CHCTR1)

/** \brief  A28, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A28u)

/** Alias (User Manual Name) for VADC_G1_CHCTR10.
* To use register names with standard convension, please use VADC_G1_CHCTR10.
*/
#define	VADC_G1CHCTR10	(VADC_G1_CHCTR10)

/** \brief  A2C, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A2Cu)

/** Alias (User Manual Name) for VADC_G1_CHCTR11.
* To use register names with standard convension, please use VADC_G1_CHCTR11.
*/
#define	VADC_G1CHCTR11	(VADC_G1_CHCTR11)

/** \brief  A30, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A30u)

/** Alias (User Manual Name) for VADC_G1_CHCTR12.
* To use register names with standard convension, please use VADC_G1_CHCTR12.
*/
#define	VADC_G1CHCTR12	(VADC_G1_CHCTR12)

/** \brief  A34, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A34u)

/** Alias (User Manual Name) for VADC_G1_CHCTR13.
* To use register names with standard convension, please use VADC_G1_CHCTR13.
*/
#define	VADC_G1CHCTR13	(VADC_G1_CHCTR13)

/** \brief  A38, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A38u)

/** Alias (User Manual Name) for VADC_G1_CHCTR14.
* To use register names with standard convension, please use VADC_G1_CHCTR14.
*/
#define	VADC_G1CHCTR14	(VADC_G1_CHCTR14)

/** \brief  A3C, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A3Cu)

/** Alias (User Manual Name) for VADC_G1_CHCTR15.
* To use register names with standard convension, please use VADC_G1_CHCTR15.
*/
#define	VADC_G1CHCTR15	(VADC_G1_CHCTR15)

/** \brief  A08, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A08u)

/** Alias (User Manual Name) for VADC_G1_CHCTR2.
* To use register names with standard convension, please use VADC_G1_CHCTR2.
*/
#define	VADC_G1CHCTR2	(VADC_G1_CHCTR2)

/** \brief  A0C, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A0Cu)

/** Alias (User Manual Name) for VADC_G1_CHCTR3.
* To use register names with standard convension, please use VADC_G1_CHCTR3.
*/
#define	VADC_G1CHCTR3	(VADC_G1_CHCTR3)

/** \brief  A10, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A10u)

/** Alias (User Manual Name) for VADC_G1_CHCTR4.
* To use register names with standard convension, please use VADC_G1_CHCTR4.
*/
#define	VADC_G1CHCTR4	(VADC_G1_CHCTR4)

/** \brief  A14, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A14u)

/** Alias (User Manual Name) for VADC_G1_CHCTR5.
* To use register names with standard convension, please use VADC_G1_CHCTR5.
*/
#define	VADC_G1CHCTR5	(VADC_G1_CHCTR5)

/** \brief  A18, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A18u)

/** Alias (User Manual Name) for VADC_G1_CHCTR6.
* To use register names with standard convension, please use VADC_G1_CHCTR6.
*/
#define	VADC_G1CHCTR6	(VADC_G1_CHCTR6)

/** \brief  A1C, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A1Cu)

/** Alias (User Manual Name) for VADC_G1_CHCTR7.
* To use register names with standard convension, please use VADC_G1_CHCTR7.
*/
#define	VADC_G1CHCTR7	(VADC_G1_CHCTR7)

/** \brief  A20, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A20u)

/** Alias (User Manual Name) for VADC_G1_CHCTR8.
* To use register names with standard convension, please use VADC_G1_CHCTR8.
*/
#define	VADC_G1CHCTR8	(VADC_G1_CHCTR8)

/** \brief  A24, Group, Channel Ctrl. Reg. */
#define VADC_G1_CHCTR9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020A24u)

/** Alias (User Manual Name) for VADC_G1_CHCTR9.
* To use register names with standard convension, please use VADC_G1_CHCTR9.
*/
#define	VADC_G1CHCTR9	(VADC_G1_CHCTR9)

/** \brief  9F0, External Multiplexer Control Register, Group x */
#define VADC_G1_EMUXCTR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_EMUXCTR*)0xF00209F0u)

/** Alias (User Manual Name) for VADC_G1_EMUXCTR.
* To use register names with standard convension, please use VADC_G1_EMUXCTR.
*/
#define	VADC_G1EMUXCTR	(VADC_G1_EMUXCTR)

/** \brief  8A0, Input Class Register */
#define VADC_G1_ICLASS0 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF00208A0u)

/** Alias (User Manual Name) for VADC_G1_ICLASS0.
* To use register names with standard convension, please use VADC_G1_ICLASS0.
*/
#define	VADC_G1ICLASS0	(VADC_G1_ICLASS0)

/** \brief  8A4, Input Class Register */
#define VADC_G1_ICLASS1 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF00208A4u)

/** Alias (User Manual Name) for VADC_G1_ICLASS1.
* To use register names with standard convension, please use VADC_G1_ICLASS1.
*/
#define	VADC_G1ICLASS1	(VADC_G1_ICLASS1)

/** \brief  90C, Queue 0 Register 0, Group */
#define VADC_G1_Q0R0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_Q0R0*)0xF002090Cu)

/** Alias (User Manual Name) for VADC_G1_Q0R0.
* To use register names with standard convension, please use VADC_G1_Q0R0.
*/
#define	VADC_G1Q0R0	(VADC_G1_Q0R0)

/** \brief  910, Queue 0 Input Register, Group */
#define VADC_G1_QBUR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QBUR0*)0xF0020910u)

/** Alias (User Manual Name) for VADC_G1_QBUR0.
* To use register names with standard convension, please use VADC_G1_QBUR0.
*/
#define	VADC_G1QBUR0	(VADC_G1_QBUR0)

/** \brief  900, Queue 0 Source Control Register, Group */
#define VADC_G1_QCTRL0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QCTRL0*)0xF0020900u)

/** Alias (User Manual Name) for VADC_G1_QCTRL0.
* To use register names with standard convension, please use VADC_G1_QCTRL0.
*/
#define	VADC_G1QCTRL0	(VADC_G1_QCTRL0)

/** \brief  910, Queue 0 Input Register, Group */
#define VADC_G1_QINR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QINR0*)0xF0020910u)

/** Alias (User Manual Name) for VADC_G1_QINR0.
* To use register names with standard convension, please use VADC_G1_QINR0.
*/
#define	VADC_G1QINR0	(VADC_G1_QINR0)

/** \brief  904, Queue 0 Mode Register, Group */
#define VADC_G1_QMR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QMR0*)0xF0020904u)

/** Alias (User Manual Name) for VADC_G1_QMR0.
* To use register names with standard convension, please use VADC_G1_QMR0.
*/
#define	VADC_G1QMR0	(VADC_G1_QMR0)

/** \brief  908, Queue 0 Status Register, Group */
#define VADC_G1_QSR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QSR0*)0xF0020908u)

/** Alias (User Manual Name) for VADC_G1_QSR0.
* To use register names with standard convension, please use VADC_G1_QSR0.
*/
#define	VADC_G1QSR0	(VADC_G1_QSR0)

/** \brief  A80, Group Result Control Reg. */
#define VADC_G1_RCR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020A80u)

/** Alias (User Manual Name) for VADC_G1_RCR0.
* To use register names with standard convension, please use VADC_G1_RCR0.
*/
#define	VADC_G1RCR0	(VADC_G1_RCR0)

/** \brief  A84, Group Result Control Reg. */
#define VADC_G1_RCR1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020A84u)

/** Alias (User Manual Name) for VADC_G1_RCR1.
* To use register names with standard convension, please use VADC_G1_RCR1.
*/
#define	VADC_G1RCR1	(VADC_G1_RCR1)

/** \brief  AA8, Group Result Control Reg. */
#define VADC_G1_RCR10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020AA8u)

/** Alias (User Manual Name) for VADC_G1_RCR10.
* To use register names with standard convension, please use VADC_G1_RCR10.
*/
#define	VADC_G1RCR10	(VADC_G1_RCR10)

/** \brief  AAC, Group Result Control Reg. */
#define VADC_G1_RCR11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020AACu)

/** Alias (User Manual Name) for VADC_G1_RCR11.
* To use register names with standard convension, please use VADC_G1_RCR11.
*/
#define	VADC_G1RCR11	(VADC_G1_RCR11)

/** \brief  AB0, Group Result Control Reg. */
#define VADC_G1_RCR12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020AB0u)

/** Alias (User Manual Name) for VADC_G1_RCR12.
* To use register names with standard convension, please use VADC_G1_RCR12.
*/
#define	VADC_G1RCR12	(VADC_G1_RCR12)

/** \brief  AB4, Group Result Control Reg. */
#define VADC_G1_RCR13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020AB4u)

/** Alias (User Manual Name) for VADC_G1_RCR13.
* To use register names with standard convension, please use VADC_G1_RCR13.
*/
#define	VADC_G1RCR13	(VADC_G1_RCR13)

/** \brief  AB8, Group Result Control Reg. */
#define VADC_G1_RCR14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020AB8u)

/** Alias (User Manual Name) for VADC_G1_RCR14.
* To use register names with standard convension, please use VADC_G1_RCR14.
*/
#define	VADC_G1RCR14	(VADC_G1_RCR14)

/** \brief  ABC, Group Result Control Reg. */
#define VADC_G1_RCR15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020ABCu)

/** Alias (User Manual Name) for VADC_G1_RCR15.
* To use register names with standard convension, please use VADC_G1_RCR15.
*/
#define	VADC_G1RCR15	(VADC_G1_RCR15)

/** \brief  A88, Group Result Control Reg. */
#define VADC_G1_RCR2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020A88u)

/** Alias (User Manual Name) for VADC_G1_RCR2.
* To use register names with standard convension, please use VADC_G1_RCR2.
*/
#define	VADC_G1RCR2	(VADC_G1_RCR2)

/** \brief  A8C, Group Result Control Reg. */
#define VADC_G1_RCR3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020A8Cu)

/** Alias (User Manual Name) for VADC_G1_RCR3.
* To use register names with standard convension, please use VADC_G1_RCR3.
*/
#define	VADC_G1RCR3	(VADC_G1_RCR3)

/** \brief  A90, Group Result Control Reg. */
#define VADC_G1_RCR4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020A90u)

/** Alias (User Manual Name) for VADC_G1_RCR4.
* To use register names with standard convension, please use VADC_G1_RCR4.
*/
#define	VADC_G1RCR4	(VADC_G1_RCR4)

/** \brief  A94, Group Result Control Reg. */
#define VADC_G1_RCR5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020A94u)

/** Alias (User Manual Name) for VADC_G1_RCR5.
* To use register names with standard convension, please use VADC_G1_RCR5.
*/
#define	VADC_G1RCR5	(VADC_G1_RCR5)

/** \brief  A98, Group Result Control Reg. */
#define VADC_G1_RCR6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020A98u)

/** Alias (User Manual Name) for VADC_G1_RCR6.
* To use register names with standard convension, please use VADC_G1_RCR6.
*/
#define	VADC_G1RCR6	(VADC_G1_RCR6)

/** \brief  A9C, Group Result Control Reg. */
#define VADC_G1_RCR7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020A9Cu)

/** Alias (User Manual Name) for VADC_G1_RCR7.
* To use register names with standard convension, please use VADC_G1_RCR7.
*/
#define	VADC_G1RCR7	(VADC_G1_RCR7)

/** \brief  AA0, Group Result Control Reg. */
#define VADC_G1_RCR8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020AA0u)

/** Alias (User Manual Name) for VADC_G1_RCR8.
* To use register names with standard convension, please use VADC_G1_RCR8.
*/
#define	VADC_G1RCR8	(VADC_G1_RCR8)

/** \brief  AA4, Group Result Control Reg. */
#define VADC_G1_RCR9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020AA4u)

/** Alias (User Manual Name) for VADC_G1_RCR9.
* To use register names with standard convension, please use VADC_G1_RCR9.
*/
#define	VADC_G1RCR9	(VADC_G1_RCR9)

/** \brief  994, Result Event Flag Clear Register, Group */
#define VADC_G1_REFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REFCLR*)0xF0020994u)

/** Alias (User Manual Name) for VADC_G1_REFCLR.
* To use register names with standard convension, please use VADC_G1_REFCLR.
*/
#define	VADC_G1REFCLR	(VADC_G1_REFCLR)

/** \brief  984, Result Event Flag Register, Group */
#define VADC_G1_REFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REFLAG*)0xF0020984u)

/** Alias (User Manual Name) for VADC_G1_REFLAG.
* To use register names with standard convension, please use VADC_G1_REFLAG.
*/
#define	VADC_G1REFLAG	(VADC_G1_REFLAG)

/** \brief  B00, Group Result Register */
#define VADC_G1_RES0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B00u)

/** Alias (User Manual Name) for VADC_G1_RES0.
* To use register names with standard convension, please use VADC_G1_RES0.
*/
#define	VADC_G1RES0	(VADC_G1_RES0)

/** \brief  B04, Group Result Register */
#define VADC_G1_RES1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B04u)

/** Alias (User Manual Name) for VADC_G1_RES1.
* To use register names with standard convension, please use VADC_G1_RES1.
*/
#define	VADC_G1RES1	(VADC_G1_RES1)

/** \brief  B28, Group Result Register */
#define VADC_G1_RES10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B28u)

/** Alias (User Manual Name) for VADC_G1_RES10.
* To use register names with standard convension, please use VADC_G1_RES10.
*/
#define	VADC_G1RES10	(VADC_G1_RES10)

/** \brief  B2C, Group Result Register */
#define VADC_G1_RES11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B2Cu)

/** Alias (User Manual Name) for VADC_G1_RES11.
* To use register names with standard convension, please use VADC_G1_RES11.
*/
#define	VADC_G1RES11	(VADC_G1_RES11)

/** \brief  B30, Group Result Register */
#define VADC_G1_RES12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B30u)

/** Alias (User Manual Name) for VADC_G1_RES12.
* To use register names with standard convension, please use VADC_G1_RES12.
*/
#define	VADC_G1RES12	(VADC_G1_RES12)

/** \brief  B34, Group Result Register */
#define VADC_G1_RES13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B34u)

/** Alias (User Manual Name) for VADC_G1_RES13.
* To use register names with standard convension, please use VADC_G1_RES13.
*/
#define	VADC_G1RES13	(VADC_G1_RES13)

/** \brief  B38, Group Result Register */
#define VADC_G1_RES14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B38u)

/** Alias (User Manual Name) for VADC_G1_RES14.
* To use register names with standard convension, please use VADC_G1_RES14.
*/
#define	VADC_G1RES14	(VADC_G1_RES14)

/** \brief  B3C, Group Result Register */
#define VADC_G1_RES15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B3Cu)

/** Alias (User Manual Name) for VADC_G1_RES15.
* To use register names with standard convension, please use VADC_G1_RES15.
*/
#define	VADC_G1RES15	(VADC_G1_RES15)

/** \brief  B08, Group Result Register */
#define VADC_G1_RES2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B08u)

/** Alias (User Manual Name) for VADC_G1_RES2.
* To use register names with standard convension, please use VADC_G1_RES2.
*/
#define	VADC_G1RES2	(VADC_G1_RES2)

/** \brief  B0C, Group Result Register */
#define VADC_G1_RES3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B0Cu)

/** Alias (User Manual Name) for VADC_G1_RES3.
* To use register names with standard convension, please use VADC_G1_RES3.
*/
#define	VADC_G1RES3	(VADC_G1_RES3)

/** \brief  B10, Group Result Register */
#define VADC_G1_RES4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B10u)

/** Alias (User Manual Name) for VADC_G1_RES4.
* To use register names with standard convension, please use VADC_G1_RES4.
*/
#define	VADC_G1RES4	(VADC_G1_RES4)

/** \brief  B14, Group Result Register */
#define VADC_G1_RES5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B14u)

/** Alias (User Manual Name) for VADC_G1_RES5.
* To use register names with standard convension, please use VADC_G1_RES5.
*/
#define	VADC_G1RES5	(VADC_G1_RES5)

/** \brief  B18, Group Result Register */
#define VADC_G1_RES6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B18u)

/** Alias (User Manual Name) for VADC_G1_RES6.
* To use register names with standard convension, please use VADC_G1_RES6.
*/
#define	VADC_G1RES6	(VADC_G1_RES6)

/** \brief  B1C, Group Result Register */
#define VADC_G1_RES7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B1Cu)

/** Alias (User Manual Name) for VADC_G1_RES7.
* To use register names with standard convension, please use VADC_G1_RES7.
*/
#define	VADC_G1RES7	(VADC_G1_RES7)

/** \brief  B20, Group Result Register */
#define VADC_G1_RES8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B20u)

/** Alias (User Manual Name) for VADC_G1_RES8.
* To use register names with standard convension, please use VADC_G1_RES8.
*/
#define	VADC_G1RES8	(VADC_G1_RES8)

/** \brief  B24, Group Result Register */
#define VADC_G1_RES9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020B24u)

/** Alias (User Manual Name) for VADC_G1_RES9.
* To use register names with standard convension, please use VADC_G1_RES9.
*/
#define	VADC_G1RES9	(VADC_G1_RES9)

/** \brief  B80, Group Result Reg., Debug */
#define VADC_G1_RESD0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020B80u)

/** Alias (User Manual Name) for VADC_G1_RESD0.
* To use register names with standard convension, please use VADC_G1_RESD0.
*/
#define	VADC_G1RESD0	(VADC_G1_RESD0)

/** \brief  B84, Group Result Reg., Debug */
#define VADC_G1_RESD1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020B84u)

/** Alias (User Manual Name) for VADC_G1_RESD1.
* To use register names with standard convension, please use VADC_G1_RESD1.
*/
#define	VADC_G1RESD1	(VADC_G1_RESD1)

/** \brief  BA8, Group Result Reg., Debug */
#define VADC_G1_RESD10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020BA8u)

/** Alias (User Manual Name) for VADC_G1_RESD10.
* To use register names with standard convension, please use VADC_G1_RESD10.
*/
#define	VADC_G1RESD10	(VADC_G1_RESD10)

/** \brief  BAC, Group Result Reg., Debug */
#define VADC_G1_RESD11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020BACu)

/** Alias (User Manual Name) for VADC_G1_RESD11.
* To use register names with standard convension, please use VADC_G1_RESD11.
*/
#define	VADC_G1RESD11	(VADC_G1_RESD11)

/** \brief  BB0, Group Result Reg., Debug */
#define VADC_G1_RESD12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020BB0u)

/** Alias (User Manual Name) for VADC_G1_RESD12.
* To use register names with standard convension, please use VADC_G1_RESD12.
*/
#define	VADC_G1RESD12	(VADC_G1_RESD12)

/** \brief  BB4, Group Result Reg., Debug */
#define VADC_G1_RESD13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020BB4u)

/** Alias (User Manual Name) for VADC_G1_RESD13.
* To use register names with standard convension, please use VADC_G1_RESD13.
*/
#define	VADC_G1RESD13	(VADC_G1_RESD13)

/** \brief  BB8, Group Result Reg., Debug */
#define VADC_G1_RESD14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020BB8u)

/** Alias (User Manual Name) for VADC_G1_RESD14.
* To use register names with standard convension, please use VADC_G1_RESD14.
*/
#define	VADC_G1RESD14	(VADC_G1_RESD14)

/** \brief  BBC, Group Result Reg., Debug */
#define VADC_G1_RESD15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020BBCu)

/** Alias (User Manual Name) for VADC_G1_RESD15.
* To use register names with standard convension, please use VADC_G1_RESD15.
*/
#define	VADC_G1RESD15	(VADC_G1_RESD15)

/** \brief  B88, Group Result Reg., Debug */
#define VADC_G1_RESD2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020B88u)

/** Alias (User Manual Name) for VADC_G1_RESD2.
* To use register names with standard convension, please use VADC_G1_RESD2.
*/
#define	VADC_G1RESD2	(VADC_G1_RESD2)

/** \brief  B8C, Group Result Reg., Debug */
#define VADC_G1_RESD3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020B8Cu)

/** Alias (User Manual Name) for VADC_G1_RESD3.
* To use register names with standard convension, please use VADC_G1_RESD3.
*/
#define	VADC_G1RESD3	(VADC_G1_RESD3)

/** \brief  B90, Group Result Reg., Debug */
#define VADC_G1_RESD4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020B90u)

/** Alias (User Manual Name) for VADC_G1_RESD4.
* To use register names with standard convension, please use VADC_G1_RESD4.
*/
#define	VADC_G1RESD4	(VADC_G1_RESD4)

/** \brief  B94, Group Result Reg., Debug */
#define VADC_G1_RESD5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020B94u)

/** Alias (User Manual Name) for VADC_G1_RESD5.
* To use register names with standard convension, please use VADC_G1_RESD5.
*/
#define	VADC_G1RESD5	(VADC_G1_RESD5)

/** \brief  B98, Group Result Reg., Debug */
#define VADC_G1_RESD6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020B98u)

/** Alias (User Manual Name) for VADC_G1_RESD6.
* To use register names with standard convension, please use VADC_G1_RESD6.
*/
#define	VADC_G1RESD6	(VADC_G1_RESD6)

/** \brief  B9C, Group Result Reg., Debug */
#define VADC_G1_RESD7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020B9Cu)

/** Alias (User Manual Name) for VADC_G1_RESD7.
* To use register names with standard convension, please use VADC_G1_RESD7.
*/
#define	VADC_G1RESD7	(VADC_G1_RESD7)

/** \brief  BA0, Group Result Reg., Debug */
#define VADC_G1_RESD8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020BA0u)

/** Alias (User Manual Name) for VADC_G1_RESD8.
* To use register names with standard convension, please use VADC_G1_RESD8.
*/
#define	VADC_G1RESD8	(VADC_G1_RESD8)

/** \brief  BA4, Group Result Reg., Debug */
#define VADC_G1_RESD9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020BA4u)

/** Alias (User Manual Name) for VADC_G1_RESD9.
* To use register names with standard convension, please use VADC_G1_RESD9.
*/
#define	VADC_G1RESD9	(VADC_G1_RESD9)

/** \brief  9B0, Result Event Node Pointer Register 0, Group */
#define VADC_G1_REVNP0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REVNP0*)0xF00209B0u)

/** Alias (User Manual Name) for VADC_G1_REVNP0.
* To use register names with standard convension, please use VADC_G1_REVNP0.
*/
#define	VADC_G1REVNP0	(VADC_G1_REVNP0)

/** \brief  9B4, Result Event Node Pointer Register 1, Group */
#define VADC_G1_REVNP1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REVNP1*)0xF00209B4u)

/** Alias (User Manual Name) for VADC_G1_REVNP1.
* To use register names with standard convension, please use VADC_G1_REVNP1.
*/
#define	VADC_G1REVNP1	(VADC_G1_REVNP1)

/** \brief  88C, Result Assignment Register, Group */
#define VADC_G1_RRASS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RRASS*)0xF002088Cu)

/** Alias (User Manual Name) for VADC_G1_RRASS.
* To use register names with standard convension, please use VADC_G1_RRASS.
*/
#define	VADC_G1RRASS	(VADC_G1_RRASS)

/** \brief  998, Source Event Flag Clear Register, Group */
#define VADC_G1_SEFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEFCLR*)0xF0020998u)

/** Alias (User Manual Name) for VADC_G1_SEFCLR.
* To use register names with standard convension, please use VADC_G1_SEFCLR.
*/
#define	VADC_G1SEFCLR	(VADC_G1_SEFCLR)

/** \brief  988, Source Event Flag Register, Group */
#define VADC_G1_SEFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEFLAG*)0xF0020988u)

/** Alias (User Manual Name) for VADC_G1_SEFLAG.
* To use register names with standard convension, please use VADC_G1_SEFLAG.
*/
#define	VADC_G1SEFLAG	(VADC_G1_SEFLAG)

/** \brief  9C0, Source Event Node Pointer Register, Group */
#define VADC_G1_SEVNP /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEVNP*)0xF00209C0u)

/** Alias (User Manual Name) for VADC_G1_SEVNP.
* To use register names with standard convension, please use VADC_G1_SEVNP.
*/
#define	VADC_G1SEVNP	(VADC_G1_SEVNP)

/** \brief  9C8, Service Request Software Activation Trigger, Group */
#define VADC_G1_SRACT /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SRACT*)0xF00209C8u)

/** Alias (User Manual Name) for VADC_G1_SRACT.
* To use register names with standard convension, please use VADC_G1_SRACT.
*/
#define	VADC_G1SRACT	(VADC_G1_SRACT)

/** \brief  8C0, Synchronization Control Register, Group */
#define VADC_G1_SYNCTR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SYNCTR*)0xF00208C0u)

/** Alias (User Manual Name) for VADC_G1_SYNCTR.
* To use register names with standard convension, please use VADC_G1_SYNCTR.
*/
#define	VADC_G1SYNCTR	(VADC_G1_SYNCTR)

/** \brief  9F8, Valid Flag Register, Group */
#define VADC_G1_VFR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_VFR*)0xF00209F8u)

/** Alias (User Manual Name) for VADC_G1_VFR.
* To use register names with standard convension, please use VADC_G1_VFR.
*/
#define	VADC_G1VFR	(VADC_G1_VFR)

/** \brief  CB0, Alias Register, Group */
#define VADC_G2_ALIAS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ALIAS*)0xF0020CB0u)

/** Alias (User Manual Name) for VADC_G2_ALIAS.
* To use register names with standard convension, please use VADC_G2_ALIAS.
*/
#define	VADC_G2ALIAS	(VADC_G2_ALIAS)

/** \brief  C80, Arbitration Configuration Register, Group */
#define VADC_G2_ARBCFG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ARBCFG*)0xF0020C80u)

/** Alias (User Manual Name) for VADC_G2_ARBCFG.
* To use register names with standard convension, please use VADC_G2_ARBCFG.
*/
#define	VADC_G2ARBCFG	(VADC_G2_ARBCFG)

/** \brief  C84, Arbitration Priority Register, Group */
#define VADC_G2_ARBPR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ARBPR*)0xF0020C84u)

/** Alias (User Manual Name) for VADC_G2_ARBPR.
* To use register names with standard convension, please use VADC_G2_ARBPR.
*/
#define	VADC_G2ARBPR	(VADC_G2_ARBPR)

/** \brief  D20, Autoscan Source Control Register, Group */
#define VADC_G2_ASCTRL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASCTRL*)0xF0020D20u)

/** Alias (User Manual Name) for VADC_G2_ASCTRL.
* To use register names with standard convension, please use VADC_G2_ASCTRL.
*/
#define	VADC_G2ASCTRL	(VADC_G2_ASCTRL)

/** \brief  D24, Autoscan Source Mode Register, Group */
#define VADC_G2_ASMR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASMR*)0xF0020D24u)

/** Alias (User Manual Name) for VADC_G2_ASMR.
* To use register names with standard convension, please use VADC_G2_ASMR.
*/
#define	VADC_G2ASMR	(VADC_G2_ASMR)

/** \brief  D2C, Autoscan Source Pending Register, Group */
#define VADC_G2_ASPND /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASPND*)0xF0020D2Cu)

/** Alias (User Manual Name) for VADC_G2_ASPND.
* To use register names with standard convension, please use VADC_G2_ASPND.
*/
#define	VADC_G2ASPND	(VADC_G2_ASPND)

/** \brief  D28, Autoscan Source Channel Select Register, Group */
#define VADC_G2_ASSEL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASSEL*)0xF0020D28u)

/** Alias (User Manual Name) for VADC_G2_ASSEL.
* To use register names with standard convension, please use VADC_G2_ASSEL.
*/
#define	VADC_G2ASSEL	(VADC_G2_ASSEL)

/** \brief  CC8, Boundary Flag Register, Group */
#define VADC_G2_BFL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFL*)0xF0020CC8u)

/** Alias (User Manual Name) for VADC_G2_BFL.
* To use register names with standard convension, please use VADC_G2_BFL.
*/
#define	VADC_G2BFL	(VADC_G2_BFL)

/** \brief  CD0, Boundary Flag Control Register, Group */
#define VADC_G2_BFLC /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLC*)0xF0020CD0u)

/** Alias (User Manual Name) for VADC_G2_BFLC.
* To use register names with standard convension, please use VADC_G2_BFLC.
*/
#define	VADC_G2BFLC	(VADC_G2_BFLC)

/** \brief  CD4, Boundary Flag Node Pointer Register, Group */
#define VADC_G2_BFLNP /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLNP*)0xF0020CD4u)

/** Alias (User Manual Name) for VADC_G2_BFLNP.
* To use register names with standard convension, please use VADC_G2_BFLNP.
*/
#define	VADC_G2BFLNP	(VADC_G2_BFLNP)

/** \brief  CCC, Boundary Flag Software Register, Group */
#define VADC_G2_BFLS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLS*)0xF0020CCCu)

/** Alias (User Manual Name) for VADC_G2_BFLS.
* To use register names with standard convension, please use VADC_G2_BFLS.
*/
#define	VADC_G2BFLS	(VADC_G2_BFLS)

/** \brief  CB8, Boundary Select Register, Group */
#define VADC_G2_BOUND /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BOUND*)0xF0020CB8u)

/** Alias (User Manual Name) for VADC_G2_BOUND.
* To use register names with standard convension, please use VADC_G2_BOUND.
*/
#define	VADC_G2BOUND	(VADC_G2_BOUND)

/** \brief  D90, Channel Event Flag Clear Register, Group */
#define VADC_G2_CEFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEFCLR*)0xF0020D90u)

/** Alias (User Manual Name) for VADC_G2_CEFCLR.
* To use register names with standard convension, please use VADC_G2_CEFCLR.
*/
#define	VADC_G2CEFCLR	(VADC_G2_CEFCLR)

/** \brief  D80, Channel Event Flag Register, Group */
#define VADC_G2_CEFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEFLAG*)0xF0020D80u)

/** Alias (User Manual Name) for VADC_G2_CEFLAG.
* To use register names with standard convension, please use VADC_G2_CEFLAG.
*/
#define	VADC_G2CEFLAG	(VADC_G2_CEFLAG)

/** \brief  DA0, Channel Event Node Pointer Register 0, Group */
#define VADC_G2_CEVNP0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEVNP0*)0xF0020DA0u)

/** Alias (User Manual Name) for VADC_G2_CEVNP0.
* To use register names with standard convension, please use VADC_G2_CEVNP0.
*/
#define	VADC_G2CEVNP0	(VADC_G2_CEVNP0)

/** \brief  DA4, Channel Event Node Pointer Register 1, Group */
#define VADC_G2_CEVNP1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEVNP1*)0xF0020DA4u)

/** Alias (User Manual Name) for VADC_G2_CEVNP1.
* To use register names with standard convension, please use VADC_G2_CEVNP1.
*/
#define	VADC_G2CEVNP1	(VADC_G2_CEVNP1)

/** \brief  C88, Channel Assignment Register, Group */
#define VADC_G2_CHASS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHASS*)0xF0020C88u)

/** Alias (User Manual Name) for VADC_G2_CHASS.
* To use register names with standard convension, please use VADC_G2_CHASS.
*/
#define	VADC_G2CHASS	(VADC_G2_CHASS)

/** \brief  E00, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E00u)

/** Alias (User Manual Name) for VADC_G2_CHCTR0.
* To use register names with standard convension, please use VADC_G2_CHCTR0.
*/
#define	VADC_G2CHCTR0	(VADC_G2_CHCTR0)

/** \brief  E04, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E04u)

/** Alias (User Manual Name) for VADC_G2_CHCTR1.
* To use register names with standard convension, please use VADC_G2_CHCTR1.
*/
#define	VADC_G2CHCTR1	(VADC_G2_CHCTR1)

/** \brief  E28, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E28u)

/** Alias (User Manual Name) for VADC_G2_CHCTR10.
* To use register names with standard convension, please use VADC_G2_CHCTR10.
*/
#define	VADC_G2CHCTR10	(VADC_G2_CHCTR10)

/** \brief  E2C, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E2Cu)

/** Alias (User Manual Name) for VADC_G2_CHCTR11.
* To use register names with standard convension, please use VADC_G2_CHCTR11.
*/
#define	VADC_G2CHCTR11	(VADC_G2_CHCTR11)

/** \brief  E30, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E30u)

/** Alias (User Manual Name) for VADC_G2_CHCTR12.
* To use register names with standard convension, please use VADC_G2_CHCTR12.
*/
#define	VADC_G2CHCTR12	(VADC_G2_CHCTR12)

/** \brief  E34, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E34u)

/** Alias (User Manual Name) for VADC_G2_CHCTR13.
* To use register names with standard convension, please use VADC_G2_CHCTR13.
*/
#define	VADC_G2CHCTR13	(VADC_G2_CHCTR13)

/** \brief  E38, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E38u)

/** Alias (User Manual Name) for VADC_G2_CHCTR14.
* To use register names with standard convension, please use VADC_G2_CHCTR14.
*/
#define	VADC_G2CHCTR14	(VADC_G2_CHCTR14)

/** \brief  E3C, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E3Cu)

/** Alias (User Manual Name) for VADC_G2_CHCTR15.
* To use register names with standard convension, please use VADC_G2_CHCTR15.
*/
#define	VADC_G2CHCTR15	(VADC_G2_CHCTR15)

/** \brief  E08, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E08u)

/** Alias (User Manual Name) for VADC_G2_CHCTR2.
* To use register names with standard convension, please use VADC_G2_CHCTR2.
*/
#define	VADC_G2CHCTR2	(VADC_G2_CHCTR2)

/** \brief  E0C, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E0Cu)

/** Alias (User Manual Name) for VADC_G2_CHCTR3.
* To use register names with standard convension, please use VADC_G2_CHCTR3.
*/
#define	VADC_G2CHCTR3	(VADC_G2_CHCTR3)

/** \brief  E10, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E10u)

/** Alias (User Manual Name) for VADC_G2_CHCTR4.
* To use register names with standard convension, please use VADC_G2_CHCTR4.
*/
#define	VADC_G2CHCTR4	(VADC_G2_CHCTR4)

/** \brief  E14, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E14u)

/** Alias (User Manual Name) for VADC_G2_CHCTR5.
* To use register names with standard convension, please use VADC_G2_CHCTR5.
*/
#define	VADC_G2CHCTR5	(VADC_G2_CHCTR5)

/** \brief  E18, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E18u)

/** Alias (User Manual Name) for VADC_G2_CHCTR6.
* To use register names with standard convension, please use VADC_G2_CHCTR6.
*/
#define	VADC_G2CHCTR6	(VADC_G2_CHCTR6)

/** \brief  E1C, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E1Cu)

/** Alias (User Manual Name) for VADC_G2_CHCTR7.
* To use register names with standard convension, please use VADC_G2_CHCTR7.
*/
#define	VADC_G2CHCTR7	(VADC_G2_CHCTR7)

/** \brief  E20, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E20u)

/** Alias (User Manual Name) for VADC_G2_CHCTR8.
* To use register names with standard convension, please use VADC_G2_CHCTR8.
*/
#define	VADC_G2CHCTR8	(VADC_G2_CHCTR8)

/** \brief  E24, Group, Channel Ctrl. Reg. */
#define VADC_G2_CHCTR9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0020E24u)

/** Alias (User Manual Name) for VADC_G2_CHCTR9.
* To use register names with standard convension, please use VADC_G2_CHCTR9.
*/
#define	VADC_G2CHCTR9	(VADC_G2_CHCTR9)

/** \brief  DF0, External Multiplexer Control Register, Group x */
#define VADC_G2_EMUXCTR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_EMUXCTR*)0xF0020DF0u)

/** Alias (User Manual Name) for VADC_G2_EMUXCTR.
* To use register names with standard convension, please use VADC_G2_EMUXCTR.
*/
#define	VADC_G2EMUXCTR	(VADC_G2_EMUXCTR)

/** \brief  CA0, Input Class Register */
#define VADC_G2_ICLASS0 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF0020CA0u)

/** Alias (User Manual Name) for VADC_G2_ICLASS0.
* To use register names with standard convension, please use VADC_G2_ICLASS0.
*/
#define	VADC_G2ICLASS0	(VADC_G2_ICLASS0)

/** \brief  CA4, Input Class Register */
#define VADC_G2_ICLASS1 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF0020CA4u)

/** Alias (User Manual Name) for VADC_G2_ICLASS1.
* To use register names with standard convension, please use VADC_G2_ICLASS1.
*/
#define	VADC_G2ICLASS1	(VADC_G2_ICLASS1)

/** \brief  D0C, Queue 0 Register 0, Group */
#define VADC_G2_Q0R0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_Q0R0*)0xF0020D0Cu)

/** Alias (User Manual Name) for VADC_G2_Q0R0.
* To use register names with standard convension, please use VADC_G2_Q0R0.
*/
#define	VADC_G2Q0R0	(VADC_G2_Q0R0)

/** \brief  D10, Queue 0 Input Register, Group */
#define VADC_G2_QBUR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QBUR0*)0xF0020D10u)

/** Alias (User Manual Name) for VADC_G2_QBUR0.
* To use register names with standard convension, please use VADC_G2_QBUR0.
*/
#define	VADC_G2QBUR0	(VADC_G2_QBUR0)

/** \brief  D00, Queue 0 Source Control Register, Group */
#define VADC_G2_QCTRL0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QCTRL0*)0xF0020D00u)

/** Alias (User Manual Name) for VADC_G2_QCTRL0.
* To use register names with standard convension, please use VADC_G2_QCTRL0.
*/
#define	VADC_G2QCTRL0	(VADC_G2_QCTRL0)

/** \brief  D10, Queue 0 Input Register, Group */
#define VADC_G2_QINR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QINR0*)0xF0020D10u)

/** Alias (User Manual Name) for VADC_G2_QINR0.
* To use register names with standard convension, please use VADC_G2_QINR0.
*/
#define	VADC_G2QINR0	(VADC_G2_QINR0)

/** \brief  D04, Queue 0 Mode Register, Group */
#define VADC_G2_QMR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QMR0*)0xF0020D04u)

/** Alias (User Manual Name) for VADC_G2_QMR0.
* To use register names with standard convension, please use VADC_G2_QMR0.
*/
#define	VADC_G2QMR0	(VADC_G2_QMR0)

/** \brief  D08, Queue 0 Status Register, Group */
#define VADC_G2_QSR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QSR0*)0xF0020D08u)

/** Alias (User Manual Name) for VADC_G2_QSR0.
* To use register names with standard convension, please use VADC_G2_QSR0.
*/
#define	VADC_G2QSR0	(VADC_G2_QSR0)

/** \brief  E80, Group Result Control Reg. */
#define VADC_G2_RCR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020E80u)

/** Alias (User Manual Name) for VADC_G2_RCR0.
* To use register names with standard convension, please use VADC_G2_RCR0.
*/
#define	VADC_G2RCR0	(VADC_G2_RCR0)

/** \brief  E84, Group Result Control Reg. */
#define VADC_G2_RCR1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020E84u)

/** Alias (User Manual Name) for VADC_G2_RCR1.
* To use register names with standard convension, please use VADC_G2_RCR1.
*/
#define	VADC_G2RCR1	(VADC_G2_RCR1)

/** \brief  EA8, Group Result Control Reg. */
#define VADC_G2_RCR10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020EA8u)

/** Alias (User Manual Name) for VADC_G2_RCR10.
* To use register names with standard convension, please use VADC_G2_RCR10.
*/
#define	VADC_G2RCR10	(VADC_G2_RCR10)

/** \brief  EAC, Group Result Control Reg. */
#define VADC_G2_RCR11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020EACu)

/** Alias (User Manual Name) for VADC_G2_RCR11.
* To use register names with standard convension, please use VADC_G2_RCR11.
*/
#define	VADC_G2RCR11	(VADC_G2_RCR11)

/** \brief  EB0, Group Result Control Reg. */
#define VADC_G2_RCR12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020EB0u)

/** Alias (User Manual Name) for VADC_G2_RCR12.
* To use register names with standard convension, please use VADC_G2_RCR12.
*/
#define	VADC_G2RCR12	(VADC_G2_RCR12)

/** \brief  EB4, Group Result Control Reg. */
#define VADC_G2_RCR13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020EB4u)

/** Alias (User Manual Name) for VADC_G2_RCR13.
* To use register names with standard convension, please use VADC_G2_RCR13.
*/
#define	VADC_G2RCR13	(VADC_G2_RCR13)

/** \brief  EB8, Group Result Control Reg. */
#define VADC_G2_RCR14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020EB8u)

/** Alias (User Manual Name) for VADC_G2_RCR14.
* To use register names with standard convension, please use VADC_G2_RCR14.
*/
#define	VADC_G2RCR14	(VADC_G2_RCR14)

/** \brief  EBC, Group Result Control Reg. */
#define VADC_G2_RCR15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020EBCu)

/** Alias (User Manual Name) for VADC_G2_RCR15.
* To use register names with standard convension, please use VADC_G2_RCR15.
*/
#define	VADC_G2RCR15	(VADC_G2_RCR15)

/** \brief  E88, Group Result Control Reg. */
#define VADC_G2_RCR2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020E88u)

/** Alias (User Manual Name) for VADC_G2_RCR2.
* To use register names with standard convension, please use VADC_G2_RCR2.
*/
#define	VADC_G2RCR2	(VADC_G2_RCR2)

/** \brief  E8C, Group Result Control Reg. */
#define VADC_G2_RCR3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020E8Cu)

/** Alias (User Manual Name) for VADC_G2_RCR3.
* To use register names with standard convension, please use VADC_G2_RCR3.
*/
#define	VADC_G2RCR3	(VADC_G2_RCR3)

/** \brief  E90, Group Result Control Reg. */
#define VADC_G2_RCR4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020E90u)

/** Alias (User Manual Name) for VADC_G2_RCR4.
* To use register names with standard convension, please use VADC_G2_RCR4.
*/
#define	VADC_G2RCR4	(VADC_G2_RCR4)

/** \brief  E94, Group Result Control Reg. */
#define VADC_G2_RCR5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020E94u)

/** Alias (User Manual Name) for VADC_G2_RCR5.
* To use register names with standard convension, please use VADC_G2_RCR5.
*/
#define	VADC_G2RCR5	(VADC_G2_RCR5)

/** \brief  E98, Group Result Control Reg. */
#define VADC_G2_RCR6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020E98u)

/** Alias (User Manual Name) for VADC_G2_RCR6.
* To use register names with standard convension, please use VADC_G2_RCR6.
*/
#define	VADC_G2RCR6	(VADC_G2_RCR6)

/** \brief  E9C, Group Result Control Reg. */
#define VADC_G2_RCR7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020E9Cu)

/** Alias (User Manual Name) for VADC_G2_RCR7.
* To use register names with standard convension, please use VADC_G2_RCR7.
*/
#define	VADC_G2RCR7	(VADC_G2_RCR7)

/** \brief  EA0, Group Result Control Reg. */
#define VADC_G2_RCR8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020EA0u)

/** Alias (User Manual Name) for VADC_G2_RCR8.
* To use register names with standard convension, please use VADC_G2_RCR8.
*/
#define	VADC_G2RCR8	(VADC_G2_RCR8)

/** \brief  EA4, Group Result Control Reg. */
#define VADC_G2_RCR9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0020EA4u)

/** Alias (User Manual Name) for VADC_G2_RCR9.
* To use register names with standard convension, please use VADC_G2_RCR9.
*/
#define	VADC_G2RCR9	(VADC_G2_RCR9)

/** \brief  D94, Result Event Flag Clear Register, Group */
#define VADC_G2_REFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REFCLR*)0xF0020D94u)

/** Alias (User Manual Name) for VADC_G2_REFCLR.
* To use register names with standard convension, please use VADC_G2_REFCLR.
*/
#define	VADC_G2REFCLR	(VADC_G2_REFCLR)

/** \brief  D84, Result Event Flag Register, Group */
#define VADC_G2_REFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REFLAG*)0xF0020D84u)

/** Alias (User Manual Name) for VADC_G2_REFLAG.
* To use register names with standard convension, please use VADC_G2_REFLAG.
*/
#define	VADC_G2REFLAG	(VADC_G2_REFLAG)

/** \brief  F00, Group Result Register */
#define VADC_G2_RES0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F00u)

/** Alias (User Manual Name) for VADC_G2_RES0.
* To use register names with standard convension, please use VADC_G2_RES0.
*/
#define	VADC_G2RES0	(VADC_G2_RES0)

/** \brief  F04, Group Result Register */
#define VADC_G2_RES1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F04u)

/** Alias (User Manual Name) for VADC_G2_RES1.
* To use register names with standard convension, please use VADC_G2_RES1.
*/
#define	VADC_G2RES1	(VADC_G2_RES1)

/** \brief  F28, Group Result Register */
#define VADC_G2_RES10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F28u)

/** Alias (User Manual Name) for VADC_G2_RES10.
* To use register names with standard convension, please use VADC_G2_RES10.
*/
#define	VADC_G2RES10	(VADC_G2_RES10)

/** \brief  F2C, Group Result Register */
#define VADC_G2_RES11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F2Cu)

/** Alias (User Manual Name) for VADC_G2_RES11.
* To use register names with standard convension, please use VADC_G2_RES11.
*/
#define	VADC_G2RES11	(VADC_G2_RES11)

/** \brief  F30, Group Result Register */
#define VADC_G2_RES12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F30u)

/** Alias (User Manual Name) for VADC_G2_RES12.
* To use register names with standard convension, please use VADC_G2_RES12.
*/
#define	VADC_G2RES12	(VADC_G2_RES12)

/** \brief  F34, Group Result Register */
#define VADC_G2_RES13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F34u)

/** Alias (User Manual Name) for VADC_G2_RES13.
* To use register names with standard convension, please use VADC_G2_RES13.
*/
#define	VADC_G2RES13	(VADC_G2_RES13)

/** \brief  F38, Group Result Register */
#define VADC_G2_RES14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F38u)

/** Alias (User Manual Name) for VADC_G2_RES14.
* To use register names with standard convension, please use VADC_G2_RES14.
*/
#define	VADC_G2RES14	(VADC_G2_RES14)

/** \brief  F3C, Group Result Register */
#define VADC_G2_RES15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F3Cu)

/** Alias (User Manual Name) for VADC_G2_RES15.
* To use register names with standard convension, please use VADC_G2_RES15.
*/
#define	VADC_G2RES15	(VADC_G2_RES15)

/** \brief  F08, Group Result Register */
#define VADC_G2_RES2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F08u)

/** Alias (User Manual Name) for VADC_G2_RES2.
* To use register names with standard convension, please use VADC_G2_RES2.
*/
#define	VADC_G2RES2	(VADC_G2_RES2)

/** \brief  F0C, Group Result Register */
#define VADC_G2_RES3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F0Cu)

/** Alias (User Manual Name) for VADC_G2_RES3.
* To use register names with standard convension, please use VADC_G2_RES3.
*/
#define	VADC_G2RES3	(VADC_G2_RES3)

/** \brief  F10, Group Result Register */
#define VADC_G2_RES4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F10u)

/** Alias (User Manual Name) for VADC_G2_RES4.
* To use register names with standard convension, please use VADC_G2_RES4.
*/
#define	VADC_G2RES4	(VADC_G2_RES4)

/** \brief  F14, Group Result Register */
#define VADC_G2_RES5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F14u)

/** Alias (User Manual Name) for VADC_G2_RES5.
* To use register names with standard convension, please use VADC_G2_RES5.
*/
#define	VADC_G2RES5	(VADC_G2_RES5)

/** \brief  F18, Group Result Register */
#define VADC_G2_RES6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F18u)

/** Alias (User Manual Name) for VADC_G2_RES6.
* To use register names with standard convension, please use VADC_G2_RES6.
*/
#define	VADC_G2RES6	(VADC_G2_RES6)

/** \brief  F1C, Group Result Register */
#define VADC_G2_RES7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F1Cu)

/** Alias (User Manual Name) for VADC_G2_RES7.
* To use register names with standard convension, please use VADC_G2_RES7.
*/
#define	VADC_G2RES7	(VADC_G2_RES7)

/** \brief  F20, Group Result Register */
#define VADC_G2_RES8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F20u)

/** Alias (User Manual Name) for VADC_G2_RES8.
* To use register names with standard convension, please use VADC_G2_RES8.
*/
#define	VADC_G2RES8	(VADC_G2_RES8)

/** \brief  F24, Group Result Register */
#define VADC_G2_RES9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0020F24u)

/** Alias (User Manual Name) for VADC_G2_RES9.
* To use register names with standard convension, please use VADC_G2_RES9.
*/
#define	VADC_G2RES9	(VADC_G2_RES9)

/** \brief  F80, Group Result Reg., Debug */
#define VADC_G2_RESD0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020F80u)

/** Alias (User Manual Name) for VADC_G2_RESD0.
* To use register names with standard convension, please use VADC_G2_RESD0.
*/
#define	VADC_G2RESD0	(VADC_G2_RESD0)

/** \brief  F84, Group Result Reg., Debug */
#define VADC_G2_RESD1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020F84u)

/** Alias (User Manual Name) for VADC_G2_RESD1.
* To use register names with standard convension, please use VADC_G2_RESD1.
*/
#define	VADC_G2RESD1	(VADC_G2_RESD1)

/** \brief  FA8, Group Result Reg., Debug */
#define VADC_G2_RESD10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020FA8u)

/** Alias (User Manual Name) for VADC_G2_RESD10.
* To use register names with standard convension, please use VADC_G2_RESD10.
*/
#define	VADC_G2RESD10	(VADC_G2_RESD10)

/** \brief  FAC, Group Result Reg., Debug */
#define VADC_G2_RESD11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020FACu)

/** Alias (User Manual Name) for VADC_G2_RESD11.
* To use register names with standard convension, please use VADC_G2_RESD11.
*/
#define	VADC_G2RESD11	(VADC_G2_RESD11)

/** \brief  FB0, Group Result Reg., Debug */
#define VADC_G2_RESD12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020FB0u)

/** Alias (User Manual Name) for VADC_G2_RESD12.
* To use register names with standard convension, please use VADC_G2_RESD12.
*/
#define	VADC_G2RESD12	(VADC_G2_RESD12)

/** \brief  FB4, Group Result Reg., Debug */
#define VADC_G2_RESD13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020FB4u)

/** Alias (User Manual Name) for VADC_G2_RESD13.
* To use register names with standard convension, please use VADC_G2_RESD13.
*/
#define	VADC_G2RESD13	(VADC_G2_RESD13)

/** \brief  FB8, Group Result Reg., Debug */
#define VADC_G2_RESD14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020FB8u)

/** Alias (User Manual Name) for VADC_G2_RESD14.
* To use register names with standard convension, please use VADC_G2_RESD14.
*/
#define	VADC_G2RESD14	(VADC_G2_RESD14)

/** \brief  FBC, Group Result Reg., Debug */
#define VADC_G2_RESD15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020FBCu)

/** Alias (User Manual Name) for VADC_G2_RESD15.
* To use register names with standard convension, please use VADC_G2_RESD15.
*/
#define	VADC_G2RESD15	(VADC_G2_RESD15)

/** \brief  F88, Group Result Reg., Debug */
#define VADC_G2_RESD2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020F88u)

/** Alias (User Manual Name) for VADC_G2_RESD2.
* To use register names with standard convension, please use VADC_G2_RESD2.
*/
#define	VADC_G2RESD2	(VADC_G2_RESD2)

/** \brief  F8C, Group Result Reg., Debug */
#define VADC_G2_RESD3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020F8Cu)

/** Alias (User Manual Name) for VADC_G2_RESD3.
* To use register names with standard convension, please use VADC_G2_RESD3.
*/
#define	VADC_G2RESD3	(VADC_G2_RESD3)

/** \brief  F90, Group Result Reg., Debug */
#define VADC_G2_RESD4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020F90u)

/** Alias (User Manual Name) for VADC_G2_RESD4.
* To use register names with standard convension, please use VADC_G2_RESD4.
*/
#define	VADC_G2RESD4	(VADC_G2_RESD4)

/** \brief  F94, Group Result Reg., Debug */
#define VADC_G2_RESD5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020F94u)

/** Alias (User Manual Name) for VADC_G2_RESD5.
* To use register names with standard convension, please use VADC_G2_RESD5.
*/
#define	VADC_G2RESD5	(VADC_G2_RESD5)

/** \brief  F98, Group Result Reg., Debug */
#define VADC_G2_RESD6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020F98u)

/** Alias (User Manual Name) for VADC_G2_RESD6.
* To use register names with standard convension, please use VADC_G2_RESD6.
*/
#define	VADC_G2RESD6	(VADC_G2_RESD6)

/** \brief  F9C, Group Result Reg., Debug */
#define VADC_G2_RESD7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020F9Cu)

/** Alias (User Manual Name) for VADC_G2_RESD7.
* To use register names with standard convension, please use VADC_G2_RESD7.
*/
#define	VADC_G2RESD7	(VADC_G2_RESD7)

/** \brief  FA0, Group Result Reg., Debug */
#define VADC_G2_RESD8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020FA0u)

/** Alias (User Manual Name) for VADC_G2_RESD8.
* To use register names with standard convension, please use VADC_G2_RESD8.
*/
#define	VADC_G2RESD8	(VADC_G2_RESD8)

/** \brief  FA4, Group Result Reg., Debug */
#define VADC_G2_RESD9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0020FA4u)

/** Alias (User Manual Name) for VADC_G2_RESD9.
* To use register names with standard convension, please use VADC_G2_RESD9.
*/
#define	VADC_G2RESD9	(VADC_G2_RESD9)

/** \brief  DB0, Result Event Node Pointer Register 0, Group */
#define VADC_G2_REVNP0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REVNP0*)0xF0020DB0u)

/** Alias (User Manual Name) for VADC_G2_REVNP0.
* To use register names with standard convension, please use VADC_G2_REVNP0.
*/
#define	VADC_G2REVNP0	(VADC_G2_REVNP0)

/** \brief  DB4, Result Event Node Pointer Register 1, Group */
#define VADC_G2_REVNP1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REVNP1*)0xF0020DB4u)

/** Alias (User Manual Name) for VADC_G2_REVNP1.
* To use register names with standard convension, please use VADC_G2_REVNP1.
*/
#define	VADC_G2REVNP1	(VADC_G2_REVNP1)

/** \brief  C8C, Result Assignment Register, Group */
#define VADC_G2_RRASS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RRASS*)0xF0020C8Cu)

/** Alias (User Manual Name) for VADC_G2_RRASS.
* To use register names with standard convension, please use VADC_G2_RRASS.
*/
#define	VADC_G2RRASS	(VADC_G2_RRASS)

/** \brief  D98, Source Event Flag Clear Register, Group */
#define VADC_G2_SEFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEFCLR*)0xF0020D98u)

/** Alias (User Manual Name) for VADC_G2_SEFCLR.
* To use register names with standard convension, please use VADC_G2_SEFCLR.
*/
#define	VADC_G2SEFCLR	(VADC_G2_SEFCLR)

/** \brief  D88, Source Event Flag Register, Group */
#define VADC_G2_SEFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEFLAG*)0xF0020D88u)

/** Alias (User Manual Name) for VADC_G2_SEFLAG.
* To use register names with standard convension, please use VADC_G2_SEFLAG.
*/
#define	VADC_G2SEFLAG	(VADC_G2_SEFLAG)

/** \brief  DC0, Source Event Node Pointer Register, Group */
#define VADC_G2_SEVNP /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEVNP*)0xF0020DC0u)

/** Alias (User Manual Name) for VADC_G2_SEVNP.
* To use register names with standard convension, please use VADC_G2_SEVNP.
*/
#define	VADC_G2SEVNP	(VADC_G2_SEVNP)

/** \brief  DC8, Service Request Software Activation Trigger, Group */
#define VADC_G2_SRACT /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SRACT*)0xF0020DC8u)

/** Alias (User Manual Name) for VADC_G2_SRACT.
* To use register names with standard convension, please use VADC_G2_SRACT.
*/
#define	VADC_G2SRACT	(VADC_G2_SRACT)

/** \brief  CC0, Synchronization Control Register, Group */
#define VADC_G2_SYNCTR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SYNCTR*)0xF0020CC0u)

/** Alias (User Manual Name) for VADC_G2_SYNCTR.
* To use register names with standard convension, please use VADC_G2_SYNCTR.
*/
#define	VADC_G2SYNCTR	(VADC_G2_SYNCTR)

/** \brief  DF8, Valid Flag Register, Group */
#define VADC_G2_VFR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_VFR*)0xF0020DF8u)

/** Alias (User Manual Name) for VADC_G2_VFR.
* To use register names with standard convension, please use VADC_G2_VFR.
*/
#define	VADC_G2VFR	(VADC_G2_VFR)

/** \brief  10B0, Alias Register, Group */
#define VADC_G3_ALIAS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ALIAS*)0xF00210B0u)

/** Alias (User Manual Name) for VADC_G3_ALIAS.
* To use register names with standard convension, please use VADC_G3_ALIAS.
*/
#define	VADC_G3ALIAS	(VADC_G3_ALIAS)

/** \brief  1080, Arbitration Configuration Register, Group */
#define VADC_G3_ARBCFG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ARBCFG*)0xF0021080u)

/** Alias (User Manual Name) for VADC_G3_ARBCFG.
* To use register names with standard convension, please use VADC_G3_ARBCFG.
*/
#define	VADC_G3ARBCFG	(VADC_G3_ARBCFG)

/** \brief  1084, Arbitration Priority Register, Group */
#define VADC_G3_ARBPR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ARBPR*)0xF0021084u)

/** Alias (User Manual Name) for VADC_G3_ARBPR.
* To use register names with standard convension, please use VADC_G3_ARBPR.
*/
#define	VADC_G3ARBPR	(VADC_G3_ARBPR)

/** \brief  1120, Autoscan Source Control Register, Group */
#define VADC_G3_ASCTRL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASCTRL*)0xF0021120u)

/** Alias (User Manual Name) for VADC_G3_ASCTRL.
* To use register names with standard convension, please use VADC_G3_ASCTRL.
*/
#define	VADC_G3ASCTRL	(VADC_G3_ASCTRL)

/** \brief  1124, Autoscan Source Mode Register, Group */
#define VADC_G3_ASMR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASMR*)0xF0021124u)

/** Alias (User Manual Name) for VADC_G3_ASMR.
* To use register names with standard convension, please use VADC_G3_ASMR.
*/
#define	VADC_G3ASMR	(VADC_G3_ASMR)

/** \brief  112C, Autoscan Source Pending Register, Group */
#define VADC_G3_ASPND /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASPND*)0xF002112Cu)

/** Alias (User Manual Name) for VADC_G3_ASPND.
* To use register names with standard convension, please use VADC_G3_ASPND.
*/
#define	VADC_G3ASPND	(VADC_G3_ASPND)

/** \brief  1128, Autoscan Source Channel Select Register, Group */
#define VADC_G3_ASSEL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_ASSEL*)0xF0021128u)

/** Alias (User Manual Name) for VADC_G3_ASSEL.
* To use register names with standard convension, please use VADC_G3_ASSEL.
*/
#define	VADC_G3ASSEL	(VADC_G3_ASSEL)

/** \brief  10C8, Boundary Flag Register, Group */
#define VADC_G3_BFL /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFL*)0xF00210C8u)

/** Alias (User Manual Name) for VADC_G3_BFL.
* To use register names with standard convension, please use VADC_G3_BFL.
*/
#define	VADC_G3BFL	(VADC_G3_BFL)

/** \brief  10D0, Boundary Flag Control Register, Group */
#define VADC_G3_BFLC /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLC*)0xF00210D0u)

/** Alias (User Manual Name) for VADC_G3_BFLC.
* To use register names with standard convension, please use VADC_G3_BFLC.
*/
#define	VADC_G3BFLC	(VADC_G3_BFLC)

/** \brief  10D4, Boundary Flag Node Pointer Register, Group */
#define VADC_G3_BFLNP /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLNP*)0xF00210D4u)

/** Alias (User Manual Name) for VADC_G3_BFLNP.
* To use register names with standard convension, please use VADC_G3_BFLNP.
*/
#define	VADC_G3BFLNP	(VADC_G3_BFLNP)

/** \brief  10CC, Boundary Flag Software Register, Group */
#define VADC_G3_BFLS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BFLS*)0xF00210CCu)

/** Alias (User Manual Name) for VADC_G3_BFLS.
* To use register names with standard convension, please use VADC_G3_BFLS.
*/
#define	VADC_G3BFLS	(VADC_G3_BFLS)

/** \brief  10B8, Boundary Select Register, Group */
#define VADC_G3_BOUND /*lint --e(923)*/ (*(volatile Ifx_VADC_G_BOUND*)0xF00210B8u)

/** Alias (User Manual Name) for VADC_G3_BOUND.
* To use register names with standard convension, please use VADC_G3_BOUND.
*/
#define	VADC_G3BOUND	(VADC_G3_BOUND)

/** \brief  1190, Channel Event Flag Clear Register, Group */
#define VADC_G3_CEFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEFCLR*)0xF0021190u)

/** Alias (User Manual Name) for VADC_G3_CEFCLR.
* To use register names with standard convension, please use VADC_G3_CEFCLR.
*/
#define	VADC_G3CEFCLR	(VADC_G3_CEFCLR)

/** \brief  1180, Channel Event Flag Register, Group */
#define VADC_G3_CEFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEFLAG*)0xF0021180u)

/** Alias (User Manual Name) for VADC_G3_CEFLAG.
* To use register names with standard convension, please use VADC_G3_CEFLAG.
*/
#define	VADC_G3CEFLAG	(VADC_G3_CEFLAG)

/** \brief  11A0, Channel Event Node Pointer Register 0, Group */
#define VADC_G3_CEVNP0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEVNP0*)0xF00211A0u)

/** Alias (User Manual Name) for VADC_G3_CEVNP0.
* To use register names with standard convension, please use VADC_G3_CEVNP0.
*/
#define	VADC_G3CEVNP0	(VADC_G3_CEVNP0)

/** \brief  11A4, Channel Event Node Pointer Register 1, Group */
#define VADC_G3_CEVNP1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CEVNP1*)0xF00211A4u)

/** Alias (User Manual Name) for VADC_G3_CEVNP1.
* To use register names with standard convension, please use VADC_G3_CEVNP1.
*/
#define	VADC_G3CEVNP1	(VADC_G3_CEVNP1)

/** \brief  1088, Channel Assignment Register, Group */
#define VADC_G3_CHASS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHASS*)0xF0021088u)

/** Alias (User Manual Name) for VADC_G3_CHASS.
* To use register names with standard convension, please use VADC_G3_CHASS.
*/
#define	VADC_G3CHASS	(VADC_G3_CHASS)

/** \brief  1200, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0021200u)

/** Alias (User Manual Name) for VADC_G3_CHCTR0.
* To use register names with standard convension, please use VADC_G3_CHCTR0.
*/
#define	VADC_G3CHCTR0	(VADC_G3_CHCTR0)

/** \brief  1204, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0021204u)

/** Alias (User Manual Name) for VADC_G3_CHCTR1.
* To use register names with standard convension, please use VADC_G3_CHCTR1.
*/
#define	VADC_G3CHCTR1	(VADC_G3_CHCTR1)

/** \brief  1228, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0021228u)

/** Alias (User Manual Name) for VADC_G3_CHCTR10.
* To use register names with standard convension, please use VADC_G3_CHCTR10.
*/
#define	VADC_G3CHCTR10	(VADC_G3_CHCTR10)

/** \brief  122C, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF002122Cu)

/** Alias (User Manual Name) for VADC_G3_CHCTR11.
* To use register names with standard convension, please use VADC_G3_CHCTR11.
*/
#define	VADC_G3CHCTR11	(VADC_G3_CHCTR11)

/** \brief  1208, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0021208u)

/** Alias (User Manual Name) for VADC_G3_CHCTR2.
* To use register names with standard convension, please use VADC_G3_CHCTR2.
*/
#define	VADC_G3CHCTR2	(VADC_G3_CHCTR2)

/** \brief  120C, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF002120Cu)

/** Alias (User Manual Name) for VADC_G3_CHCTR3.
* To use register names with standard convension, please use VADC_G3_CHCTR3.
*/
#define	VADC_G3CHCTR3	(VADC_G3_CHCTR3)

/** \brief  1210, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0021210u)

/** Alias (User Manual Name) for VADC_G3_CHCTR4.
* To use register names with standard convension, please use VADC_G3_CHCTR4.
*/
#define	VADC_G3CHCTR4	(VADC_G3_CHCTR4)

/** \brief  1214, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0021214u)

/** Alias (User Manual Name) for VADC_G3_CHCTR5.
* To use register names with standard convension, please use VADC_G3_CHCTR5.
*/
#define	VADC_G3CHCTR5	(VADC_G3_CHCTR5)

/** \brief  1218, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0021218u)

/** Alias (User Manual Name) for VADC_G3_CHCTR6.
* To use register names with standard convension, please use VADC_G3_CHCTR6.
*/
#define	VADC_G3CHCTR6	(VADC_G3_CHCTR6)

/** \brief  121C, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF002121Cu)

/** Alias (User Manual Name) for VADC_G3_CHCTR7.
* To use register names with standard convension, please use VADC_G3_CHCTR7.
*/
#define	VADC_G3CHCTR7	(VADC_G3_CHCTR7)

/** \brief  1220, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0021220u)

/** Alias (User Manual Name) for VADC_G3_CHCTR8.
* To use register names with standard convension, please use VADC_G3_CHCTR8.
*/
#define	VADC_G3CHCTR8	(VADC_G3_CHCTR8)

/** \brief  1224, Group, Channel Ctrl. Reg. */
#define VADC_G3_CHCTR9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_CHCTR*)0xF0021224u)

/** Alias (User Manual Name) for VADC_G3_CHCTR9.
* To use register names with standard convension, please use VADC_G3_CHCTR9.
*/
#define	VADC_G3CHCTR9	(VADC_G3_CHCTR9)

/** \brief  11F0, External Multiplexer Control Register, Group x */
#define VADC_G3_EMUXCTR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_EMUXCTR*)0xF00211F0u)

/** Alias (User Manual Name) for VADC_G3_EMUXCTR.
* To use register names with standard convension, please use VADC_G3_EMUXCTR.
*/
#define	VADC_G3EMUXCTR	(VADC_G3_EMUXCTR)

/** \brief  10A0, Input Class Register */
#define VADC_G3_ICLASS0 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF00210A0u)

/** Alias (User Manual Name) for VADC_G3_ICLASS0.
* To use register names with standard convension, please use VADC_G3_ICLASS0.
*/
#define	VADC_G3ICLASS0	(VADC_G3_ICLASS0)

/** \brief  10A4, Input Class Register */
#define VADC_G3_ICLASS1 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF00210A4u)

/** Alias (User Manual Name) for VADC_G3_ICLASS1.
* To use register names with standard convension, please use VADC_G3_ICLASS1.
*/
#define	VADC_G3ICLASS1	(VADC_G3_ICLASS1)

/** \brief  110C, Queue 0 Register 0, Group */
#define VADC_G3_Q0R0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_Q0R0*)0xF002110Cu)

/** Alias (User Manual Name) for VADC_G3_Q0R0.
* To use register names with standard convension, please use VADC_G3_Q0R0.
*/
#define	VADC_G3Q0R0	(VADC_G3_Q0R0)

/** \brief  1110, Queue 0 Input Register, Group */
#define VADC_G3_QBUR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QBUR0*)0xF0021110u)

/** Alias (User Manual Name) for VADC_G3_QBUR0.
* To use register names with standard convension, please use VADC_G3_QBUR0.
*/
#define	VADC_G3QBUR0	(VADC_G3_QBUR0)

/** \brief  1100, Queue 0 Source Control Register, Group */
#define VADC_G3_QCTRL0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QCTRL0*)0xF0021100u)

/** Alias (User Manual Name) for VADC_G3_QCTRL0.
* To use register names with standard convension, please use VADC_G3_QCTRL0.
*/
#define	VADC_G3QCTRL0	(VADC_G3_QCTRL0)

/** \brief  1110, Queue 0 Input Register, Group */
#define VADC_G3_QINR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QINR0*)0xF0021110u)

/** Alias (User Manual Name) for VADC_G3_QINR0.
* To use register names with standard convension, please use VADC_G3_QINR0.
*/
#define	VADC_G3QINR0	(VADC_G3_QINR0)

/** \brief  1104, Queue 0 Mode Register, Group */
#define VADC_G3_QMR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QMR0*)0xF0021104u)

/** Alias (User Manual Name) for VADC_G3_QMR0.
* To use register names with standard convension, please use VADC_G3_QMR0.
*/
#define	VADC_G3QMR0	(VADC_G3_QMR0)

/** \brief  1108, Queue 0 Status Register, Group */
#define VADC_G3_QSR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_QSR0*)0xF0021108u)

/** Alias (User Manual Name) for VADC_G3_QSR0.
* To use register names with standard convension, please use VADC_G3_QSR0.
*/
#define	VADC_G3QSR0	(VADC_G3_QSR0)

/** \brief  1280, Group Result Control Reg. */
#define VADC_G3_RCR0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0021280u)

/** Alias (User Manual Name) for VADC_G3_RCR0.
* To use register names with standard convension, please use VADC_G3_RCR0.
*/
#define	VADC_G3RCR0	(VADC_G3_RCR0)

/** \brief  1284, Group Result Control Reg. */
#define VADC_G3_RCR1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0021284u)

/** Alias (User Manual Name) for VADC_G3_RCR1.
* To use register names with standard convension, please use VADC_G3_RCR1.
*/
#define	VADC_G3RCR1	(VADC_G3_RCR1)

/** \brief  12A8, Group Result Control Reg. */
#define VADC_G3_RCR10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00212A8u)

/** Alias (User Manual Name) for VADC_G3_RCR10.
* To use register names with standard convension, please use VADC_G3_RCR10.
*/
#define	VADC_G3RCR10	(VADC_G3_RCR10)

/** \brief  12AC, Group Result Control Reg. */
#define VADC_G3_RCR11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00212ACu)

/** Alias (User Manual Name) for VADC_G3_RCR11.
* To use register names with standard convension, please use VADC_G3_RCR11.
*/
#define	VADC_G3RCR11	(VADC_G3_RCR11)

/** \brief  12B0, Group Result Control Reg. */
#define VADC_G3_RCR12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00212B0u)

/** Alias (User Manual Name) for VADC_G3_RCR12.
* To use register names with standard convension, please use VADC_G3_RCR12.
*/
#define	VADC_G3RCR12	(VADC_G3_RCR12)

/** \brief  12B4, Group Result Control Reg. */
#define VADC_G3_RCR13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00212B4u)

/** Alias (User Manual Name) for VADC_G3_RCR13.
* To use register names with standard convension, please use VADC_G3_RCR13.
*/
#define	VADC_G3RCR13	(VADC_G3_RCR13)

/** \brief  12B8, Group Result Control Reg. */
#define VADC_G3_RCR14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00212B8u)

/** Alias (User Manual Name) for VADC_G3_RCR14.
* To use register names with standard convension, please use VADC_G3_RCR14.
*/
#define	VADC_G3RCR14	(VADC_G3_RCR14)

/** \brief  12BC, Group Result Control Reg. */
#define VADC_G3_RCR15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00212BCu)

/** Alias (User Manual Name) for VADC_G3_RCR15.
* To use register names with standard convension, please use VADC_G3_RCR15.
*/
#define	VADC_G3RCR15	(VADC_G3_RCR15)

/** \brief  1288, Group Result Control Reg. */
#define VADC_G3_RCR2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0021288u)

/** Alias (User Manual Name) for VADC_G3_RCR2.
* To use register names with standard convension, please use VADC_G3_RCR2.
*/
#define	VADC_G3RCR2	(VADC_G3_RCR2)

/** \brief  128C, Group Result Control Reg. */
#define VADC_G3_RCR3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF002128Cu)

/** Alias (User Manual Name) for VADC_G3_RCR3.
* To use register names with standard convension, please use VADC_G3_RCR3.
*/
#define	VADC_G3RCR3	(VADC_G3_RCR3)

/** \brief  1290, Group Result Control Reg. */
#define VADC_G3_RCR4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0021290u)

/** Alias (User Manual Name) for VADC_G3_RCR4.
* To use register names with standard convension, please use VADC_G3_RCR4.
*/
#define	VADC_G3RCR4	(VADC_G3_RCR4)

/** \brief  1294, Group Result Control Reg. */
#define VADC_G3_RCR5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0021294u)

/** Alias (User Manual Name) for VADC_G3_RCR5.
* To use register names with standard convension, please use VADC_G3_RCR5.
*/
#define	VADC_G3RCR5	(VADC_G3_RCR5)

/** \brief  1298, Group Result Control Reg. */
#define VADC_G3_RCR6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF0021298u)

/** Alias (User Manual Name) for VADC_G3_RCR6.
* To use register names with standard convension, please use VADC_G3_RCR6.
*/
#define	VADC_G3RCR6	(VADC_G3_RCR6)

/** \brief  129C, Group Result Control Reg. */
#define VADC_G3_RCR7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF002129Cu)

/** Alias (User Manual Name) for VADC_G3_RCR7.
* To use register names with standard convension, please use VADC_G3_RCR7.
*/
#define	VADC_G3RCR7	(VADC_G3_RCR7)

/** \brief  12A0, Group Result Control Reg. */
#define VADC_G3_RCR8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00212A0u)

/** Alias (User Manual Name) for VADC_G3_RCR8.
* To use register names with standard convension, please use VADC_G3_RCR8.
*/
#define	VADC_G3RCR8	(VADC_G3_RCR8)

/** \brief  12A4, Group Result Control Reg. */
#define VADC_G3_RCR9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RCR*)0xF00212A4u)

/** Alias (User Manual Name) for VADC_G3_RCR9.
* To use register names with standard convension, please use VADC_G3_RCR9.
*/
#define	VADC_G3RCR9	(VADC_G3_RCR9)

/** \brief  1194, Result Event Flag Clear Register, Group */
#define VADC_G3_REFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REFCLR*)0xF0021194u)

/** Alias (User Manual Name) for VADC_G3_REFCLR.
* To use register names with standard convension, please use VADC_G3_REFCLR.
*/
#define	VADC_G3REFCLR	(VADC_G3_REFCLR)

/** \brief  1184, Result Event Flag Register, Group */
#define VADC_G3_REFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REFLAG*)0xF0021184u)

/** Alias (User Manual Name) for VADC_G3_REFLAG.
* To use register names with standard convension, please use VADC_G3_REFLAG.
*/
#define	VADC_G3REFLAG	(VADC_G3_REFLAG)

/** \brief  1300, Group Result Register */
#define VADC_G3_RES0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021300u)

/** Alias (User Manual Name) for VADC_G3_RES0.
* To use register names with standard convension, please use VADC_G3_RES0.
*/
#define	VADC_G3RES0	(VADC_G3_RES0)

/** \brief  1304, Group Result Register */
#define VADC_G3_RES1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021304u)

/** Alias (User Manual Name) for VADC_G3_RES1.
* To use register names with standard convension, please use VADC_G3_RES1.
*/
#define	VADC_G3RES1	(VADC_G3_RES1)

/** \brief  1328, Group Result Register */
#define VADC_G3_RES10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021328u)

/** Alias (User Manual Name) for VADC_G3_RES10.
* To use register names with standard convension, please use VADC_G3_RES10.
*/
#define	VADC_G3RES10	(VADC_G3_RES10)

/** \brief  132C, Group Result Register */
#define VADC_G3_RES11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF002132Cu)

/** Alias (User Manual Name) for VADC_G3_RES11.
* To use register names with standard convension, please use VADC_G3_RES11.
*/
#define	VADC_G3RES11	(VADC_G3_RES11)

/** \brief  1330, Group Result Register */
#define VADC_G3_RES12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021330u)

/** Alias (User Manual Name) for VADC_G3_RES12.
* To use register names with standard convension, please use VADC_G3_RES12.
*/
#define	VADC_G3RES12	(VADC_G3_RES12)

/** \brief  1334, Group Result Register */
#define VADC_G3_RES13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021334u)

/** Alias (User Manual Name) for VADC_G3_RES13.
* To use register names with standard convension, please use VADC_G3_RES13.
*/
#define	VADC_G3RES13	(VADC_G3_RES13)

/** \brief  1338, Group Result Register */
#define VADC_G3_RES14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021338u)

/** Alias (User Manual Name) for VADC_G3_RES14.
* To use register names with standard convension, please use VADC_G3_RES14.
*/
#define	VADC_G3RES14	(VADC_G3_RES14)

/** \brief  133C, Group Result Register */
#define VADC_G3_RES15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF002133Cu)

/** Alias (User Manual Name) for VADC_G3_RES15.
* To use register names with standard convension, please use VADC_G3_RES15.
*/
#define	VADC_G3RES15	(VADC_G3_RES15)

/** \brief  1308, Group Result Register */
#define VADC_G3_RES2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021308u)

/** Alias (User Manual Name) for VADC_G3_RES2.
* To use register names with standard convension, please use VADC_G3_RES2.
*/
#define	VADC_G3RES2	(VADC_G3_RES2)

/** \brief  130C, Group Result Register */
#define VADC_G3_RES3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF002130Cu)

/** Alias (User Manual Name) for VADC_G3_RES3.
* To use register names with standard convension, please use VADC_G3_RES3.
*/
#define	VADC_G3RES3	(VADC_G3_RES3)

/** \brief  1310, Group Result Register */
#define VADC_G3_RES4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021310u)

/** Alias (User Manual Name) for VADC_G3_RES4.
* To use register names with standard convension, please use VADC_G3_RES4.
*/
#define	VADC_G3RES4	(VADC_G3_RES4)

/** \brief  1314, Group Result Register */
#define VADC_G3_RES5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021314u)

/** Alias (User Manual Name) for VADC_G3_RES5.
* To use register names with standard convension, please use VADC_G3_RES5.
*/
#define	VADC_G3RES5	(VADC_G3_RES5)

/** \brief  1318, Group Result Register */
#define VADC_G3_RES6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021318u)

/** Alias (User Manual Name) for VADC_G3_RES6.
* To use register names with standard convension, please use VADC_G3_RES6.
*/
#define	VADC_G3RES6	(VADC_G3_RES6)

/** \brief  131C, Group Result Register */
#define VADC_G3_RES7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF002131Cu)

/** Alias (User Manual Name) for VADC_G3_RES7.
* To use register names with standard convension, please use VADC_G3_RES7.
*/
#define	VADC_G3RES7	(VADC_G3_RES7)

/** \brief  1320, Group Result Register */
#define VADC_G3_RES8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021320u)

/** Alias (User Manual Name) for VADC_G3_RES8.
* To use register names with standard convension, please use VADC_G3_RES8.
*/
#define	VADC_G3RES8	(VADC_G3_RES8)

/** \brief  1324, Group Result Register */
#define VADC_G3_RES9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RES*)0xF0021324u)

/** Alias (User Manual Name) for VADC_G3_RES9.
* To use register names with standard convension, please use VADC_G3_RES9.
*/
#define	VADC_G3RES9	(VADC_G3_RES9)

/** \brief  1380, Group Result Reg., Debug */
#define VADC_G3_RESD0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0021380u)

/** Alias (User Manual Name) for VADC_G3_RESD0.
* To use register names with standard convension, please use VADC_G3_RESD0.
*/
#define	VADC_G3RESD0	(VADC_G3_RESD0)

/** \brief  1384, Group Result Reg., Debug */
#define VADC_G3_RESD1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0021384u)

/** Alias (User Manual Name) for VADC_G3_RESD1.
* To use register names with standard convension, please use VADC_G3_RESD1.
*/
#define	VADC_G3RESD1	(VADC_G3_RESD1)

/** \brief  13A8, Group Result Reg., Debug */
#define VADC_G3_RESD10 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00213A8u)

/** Alias (User Manual Name) for VADC_G3_RESD10.
* To use register names with standard convension, please use VADC_G3_RESD10.
*/
#define	VADC_G3RESD10	(VADC_G3_RESD10)

/** \brief  13AC, Group Result Reg., Debug */
#define VADC_G3_RESD11 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00213ACu)

/** Alias (User Manual Name) for VADC_G3_RESD11.
* To use register names with standard convension, please use VADC_G3_RESD11.
*/
#define	VADC_G3RESD11	(VADC_G3_RESD11)

/** \brief  13B0, Group Result Reg., Debug */
#define VADC_G3_RESD12 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00213B0u)

/** Alias (User Manual Name) for VADC_G3_RESD12.
* To use register names with standard convension, please use VADC_G3_RESD12.
*/
#define	VADC_G3RESD12	(VADC_G3_RESD12)

/** \brief  13B4, Group Result Reg., Debug */
#define VADC_G3_RESD13 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00213B4u)

/** Alias (User Manual Name) for VADC_G3_RESD13.
* To use register names with standard convension, please use VADC_G3_RESD13.
*/
#define	VADC_G3RESD13	(VADC_G3_RESD13)

/** \brief  13B8, Group Result Reg., Debug */
#define VADC_G3_RESD14 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00213B8u)

/** Alias (User Manual Name) for VADC_G3_RESD14.
* To use register names with standard convension, please use VADC_G3_RESD14.
*/
#define	VADC_G3RESD14	(VADC_G3_RESD14)

/** \brief  13BC, Group Result Reg., Debug */
#define VADC_G3_RESD15 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00213BCu)

/** Alias (User Manual Name) for VADC_G3_RESD15.
* To use register names with standard convension, please use VADC_G3_RESD15.
*/
#define	VADC_G3RESD15	(VADC_G3_RESD15)

/** \brief  1388, Group Result Reg., Debug */
#define VADC_G3_RESD2 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0021388u)

/** Alias (User Manual Name) for VADC_G3_RESD2.
* To use register names with standard convension, please use VADC_G3_RESD2.
*/
#define	VADC_G3RESD2	(VADC_G3_RESD2)

/** \brief  138C, Group Result Reg., Debug */
#define VADC_G3_RESD3 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF002138Cu)

/** Alias (User Manual Name) for VADC_G3_RESD3.
* To use register names with standard convension, please use VADC_G3_RESD3.
*/
#define	VADC_G3RESD3	(VADC_G3_RESD3)

/** \brief  1390, Group Result Reg., Debug */
#define VADC_G3_RESD4 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0021390u)

/** Alias (User Manual Name) for VADC_G3_RESD4.
* To use register names with standard convension, please use VADC_G3_RESD4.
*/
#define	VADC_G3RESD4	(VADC_G3_RESD4)

/** \brief  1394, Group Result Reg., Debug */
#define VADC_G3_RESD5 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0021394u)

/** Alias (User Manual Name) for VADC_G3_RESD5.
* To use register names with standard convension, please use VADC_G3_RESD5.
*/
#define	VADC_G3RESD5	(VADC_G3_RESD5)

/** \brief  1398, Group Result Reg., Debug */
#define VADC_G3_RESD6 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF0021398u)

/** Alias (User Manual Name) for VADC_G3_RESD6.
* To use register names with standard convension, please use VADC_G3_RESD6.
*/
#define	VADC_G3RESD6	(VADC_G3_RESD6)

/** \brief  139C, Group Result Reg., Debug */
#define VADC_G3_RESD7 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF002139Cu)

/** Alias (User Manual Name) for VADC_G3_RESD7.
* To use register names with standard convension, please use VADC_G3_RESD7.
*/
#define	VADC_G3RESD7	(VADC_G3_RESD7)

/** \brief  13A0, Group Result Reg., Debug */
#define VADC_G3_RESD8 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00213A0u)

/** Alias (User Manual Name) for VADC_G3_RESD8.
* To use register names with standard convension, please use VADC_G3_RESD8.
*/
#define	VADC_G3RESD8	(VADC_G3_RESD8)

/** \brief  13A4, Group Result Reg., Debug */
#define VADC_G3_RESD9 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RESD*)0xF00213A4u)

/** Alias (User Manual Name) for VADC_G3_RESD9.
* To use register names with standard convension, please use VADC_G3_RESD9.
*/
#define	VADC_G3RESD9	(VADC_G3_RESD9)

/** \brief  11B0, Result Event Node Pointer Register 0, Group */
#define VADC_G3_REVNP0 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REVNP0*)0xF00211B0u)

/** Alias (User Manual Name) for VADC_G3_REVNP0.
* To use register names with standard convension, please use VADC_G3_REVNP0.
*/
#define	VADC_G3REVNP0	(VADC_G3_REVNP0)

/** \brief  11B4, Result Event Node Pointer Register 1, Group */
#define VADC_G3_REVNP1 /*lint --e(923)*/ (*(volatile Ifx_VADC_G_REVNP1*)0xF00211B4u)

/** Alias (User Manual Name) for VADC_G3_REVNP1.
* To use register names with standard convension, please use VADC_G3_REVNP1.
*/
#define	VADC_G3REVNP1	(VADC_G3_REVNP1)

/** \brief  108C, Result Assignment Register, Group */
#define VADC_G3_RRASS /*lint --e(923)*/ (*(volatile Ifx_VADC_G_RRASS*)0xF002108Cu)

/** Alias (User Manual Name) for VADC_G3_RRASS.
* To use register names with standard convension, please use VADC_G3_RRASS.
*/
#define	VADC_G3RRASS	(VADC_G3_RRASS)

/** \brief  1198, Source Event Flag Clear Register, Group */
#define VADC_G3_SEFCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEFCLR*)0xF0021198u)

/** Alias (User Manual Name) for VADC_G3_SEFCLR.
* To use register names with standard convension, please use VADC_G3_SEFCLR.
*/
#define	VADC_G3SEFCLR	(VADC_G3_SEFCLR)

/** \brief  1188, Source Event Flag Register, Group */
#define VADC_G3_SEFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEFLAG*)0xF0021188u)

/** Alias (User Manual Name) for VADC_G3_SEFLAG.
* To use register names with standard convension, please use VADC_G3_SEFLAG.
*/
#define	VADC_G3SEFLAG	(VADC_G3_SEFLAG)

/** \brief  11C0, Source Event Node Pointer Register, Group */
#define VADC_G3_SEVNP /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SEVNP*)0xF00211C0u)

/** Alias (User Manual Name) for VADC_G3_SEVNP.
* To use register names with standard convension, please use VADC_G3_SEVNP.
*/
#define	VADC_G3SEVNP	(VADC_G3_SEVNP)

/** \brief  11C8, Service Request Software Activation Trigger, Group */
#define VADC_G3_SRACT /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SRACT*)0xF00211C8u)

/** Alias (User Manual Name) for VADC_G3_SRACT.
* To use register names with standard convension, please use VADC_G3_SRACT.
*/
#define	VADC_G3SRACT	(VADC_G3_SRACT)

/** \brief  10C0, Synchronization Control Register, Group */
#define VADC_G3_SYNCTR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_SYNCTR*)0xF00210C0u)

/** Alias (User Manual Name) for VADC_G3_SYNCTR.
* To use register names with standard convension, please use VADC_G3_SYNCTR.
*/
#define	VADC_G3SYNCTR	(VADC_G3_SYNCTR)

/** \brief  11F8, Valid Flag Register, Group */
#define VADC_G3_VFR /*lint --e(923)*/ (*(volatile Ifx_VADC_G_VFR*)0xF00211F8u)

/** Alias (User Manual Name) for VADC_G3_VFR.
* To use register names with standard convension, please use VADC_G3_VFR.
*/
#define	VADC_G3VFR	(VADC_G3_VFR)

/** \brief  B8, Global Boundary Select Register */
#define VADC_GLOBBOUND /*lint --e(923)*/ (*(volatile Ifx_VADC_GLOBBOUND*)0xF00200B8u)

/** \brief  80, Global Configuration Register */
#define VADC_GLOBCFG /*lint --e(923)*/ (*(volatile Ifx_VADC_GLOBCFG*)0xF0020080u)

/** \brief  E0, Global Event Flag Register */
#define VADC_GLOBEFLAG /*lint --e(923)*/ (*(volatile Ifx_VADC_GLOBEFLAG*)0xF00200E0u)

/** \brief  140, Global Event Node Pointer Register */
#define VADC_GLOBEVNP /*lint --e(923)*/ (*(volatile Ifx_VADC_GLOBEVNP*)0xF0020140u)

/** \brief  A0, Input Class Register */
#define VADC_GLOBICLASS0 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF00200A0u)

/** \brief  A4, Input Class Register */
#define VADC_GLOBICLASS1 /*lint --e(923)*/ (*(volatile Ifx_VADC_ICLASS*)0xF00200A4u)

/** \brief  280, Global Result Control Register */
#define VADC_GLOBRCR /*lint --e(923)*/ (*(volatile Ifx_VADC_GLOBRCR*)0xF0020280u)

/** \brief  300, Global Result Register */
#define VADC_GLOBRES /*lint --e(923)*/ (*(volatile Ifx_VADC_GLOBRES*)0xF0020300u)

/** \brief  380, Global Result Register, Debug */
#define VADC_GLOBRESD /*lint --e(923)*/ (*(volatile Ifx_VADC_GLOBRESD*)0xF0020380u)

/** \brief  160, Global Test Functions Register */
#define VADC_GLOBTF /*lint --e(923)*/ (*(volatile Ifx_VADC_GLOBTF*)0xF0020160u)

/** \brief  8, Module Identification Register */
#define VADC_ID /*lint --e(923)*/ (*(volatile Ifx_VADC_ID*)0xF0020008u)

/** \brief  34, Kernel Reset Register 0 */
#define VADC_KRST0 /*lint --e(923)*/ (*(volatile Ifx_VADC_KRST0*)0xF0020034u)

/** \brief  30, Kernel Reset Register 1 */
#define VADC_KRST1 /*lint --e(923)*/ (*(volatile Ifx_VADC_KRST1*)0xF0020030u)

/** \brief  2C, Kernel Reset Status Clear Register */
#define VADC_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_VADC_KRSTCLR*)0xF002002Cu)

/** \brief  28, OCDS Control and Status Register */
#define VADC_OCS /*lint --e(923)*/ (*(volatile Ifx_VADC_OCS*)0xF0020028u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXVADC_REG_H */
