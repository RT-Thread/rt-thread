/**
 * \file IfxXbar_reg.h
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
 * \defgroup IfxLld_Xbar_Cfg Xbar address
 * \ingroup IfxLld_Xbar
 * 
 * \defgroup IfxLld_Xbar_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Xbar_Cfg
 * 
 * \defgroup IfxLld_Xbar_Cfg_Xbar 2-XBAR
 * \ingroup IfxLld_Xbar_Cfg
 * 
 */
#ifndef IFXXBAR_REG_H
#define IFXXBAR_REG_H 1
/******************************************************************************/
#include "IfxXbar_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Xbar_Cfg_BaseAddress
 * \{  */

/** \brief  XBAR object */
#define MODULE_XBAR /*lint --e(923)*/ (*(Ifx_XBAR*)0xF8700000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Xbar_Cfg_Xbar
 * \{  */

/** \brief  4FC, Access Enable Register 0 */
#define XBAR_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_XBAR_ACCEN0*)0xF87004FCu)

/** \brief  4F8, Access Enable Register 1 */
#define XBAR_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_XBAR_ACCEN1*)0xF87004F8u)

/** \brief  44, Arbiter Control Register */
#define XBAR_ARBITER0_ARBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBCON*)0xF8700044u)

/** Alias (User Manual Name) for XBAR_ARBITER0_ARBCON.
* To use register names with standard convension, please use XBAR_ARBITER0_ARBCON.
*/
#define	XBAR_ARBCON0	(XBAR_ARBITER0_ARBCON)

/** \brief  5C, Debug Address Register */
#define XBAR_ARBITER0_DBADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER0_DBADD*)0xF870005Cu)

/** Alias (User Manual Name) for XBAR_ARBITER0_DBADD.
* To use register names with standard convension, please use XBAR_ARBITER0_DBADD.
*/
#define	XBAR_DBADD0	(XBAR_ARBITER0_DBADD)

/** \brief  58, Debug Control Register */
#define XBAR_ARBITER0_DBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_DBCON*)0xF8700058u)

/** Alias (User Manual Name) for XBAR_ARBITER0_DBCON.
* To use register names with standard convension, please use XBAR_ARBITER0_DBCON.
*/
#define	XBAR_DBCON0	(XBAR_ARBITER0_DBCON)

/** \brief  60, Debug Mask Address Register */
#define XBAR_ARBITER0_DBMADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER0_DBMADD*)0xF8700060u)

/** Alias (User Manual Name) for XBAR_ARBITER0_DBMADD.
* To use register names with standard convension, please use XBAR_ARBITER0_DBMADD.
*/
#define	XBAR_DBMADD0	(XBAR_ARBITER0_DBMADD)

/** \brief  54, Error/Debug Capture Register */
#define XBAR_ARBITER0_ERR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERR*)0xF8700054u)

/** Alias (User Manual Name) for XBAR_ARBITER0_ERR.
* To use register names with standard convension, please use XBAR_ARBITER0_ERR.
*/
#define	XBAR_ERR0	(XBAR_ARBITER0_ERR)

/** \brief  50, Error/Debug Address Capture Register */
#define XBAR_ARBITER0_ERRADDR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERRADDR*)0xF8700050u)

/** Alias (User Manual Name) for XBAR_ARBITER0_ERRADDR.
* To use register names with standard convension, please use XBAR_ARBITER0_ERRADDR.
*/
#define	XBAR_ERRADDR0	(XBAR_ARBITER0_ERRADDR)

/** \brief  48, Arbiter Priority Register */
#define XBAR_ARBITER0_PRIOH /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOH*)0xF8700048u)

/** Alias (User Manual Name) for XBAR_ARBITER0_PRIOH.
* To use register names with standard convension, please use XBAR_ARBITER0_PRIOH.
*/
#define	XBAR_PRIOH0	(XBAR_ARBITER0_PRIOH)

/** \brief  4C, Arbiter Priority Register */
#define XBAR_ARBITER0_PRIOL /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOL*)0xF870004Cu)

/** Alias (User Manual Name) for XBAR_ARBITER0_PRIOL.
* To use register names with standard convension, please use XBAR_ARBITER0_PRIOL.
*/
#define	XBAR_PRIOL0	(XBAR_ARBITER0_PRIOL)

/** \brief  84, Arbiter Control Register */
#define XBAR_ARBITER1_ARBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBCON*)0xF8700084u)

/** Alias (User Manual Name) for XBAR_ARBITER1_ARBCON.
* To use register names with standard convension, please use XBAR_ARBITER1_ARBCON.
*/
#define	XBAR_ARBCON1	(XBAR_ARBITER1_ARBCON)

/** \brief  9C, Debug Address Register */
#define XBAR_ARBITER1_DBADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER1_DBADD*)0xF870009Cu)

/** Alias (User Manual Name) for XBAR_ARBITER1_DBADD.
* To use register names with standard convension, please use XBAR_ARBITER1_DBADD.
*/
#define	XBAR_DBADD1	(XBAR_ARBITER1_DBADD)

/** \brief  98, Debug Control Register */
#define XBAR_ARBITER1_DBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_DBCON*)0xF8700098u)

/** Alias (User Manual Name) for XBAR_ARBITER1_DBCON.
* To use register names with standard convension, please use XBAR_ARBITER1_DBCON.
*/
#define	XBAR_DBCON1	(XBAR_ARBITER1_DBCON)

/** \brief  A0, Debug Mask Address Register */
#define XBAR_ARBITER1_DBMADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER1_DBMADD*)0xF87000A0u)

/** Alias (User Manual Name) for XBAR_ARBITER1_DBMADD.
* To use register names with standard convension, please use XBAR_ARBITER1_DBMADD.
*/
#define	XBAR_DBMADD1	(XBAR_ARBITER1_DBMADD)

/** \brief  94, Error/Debug Capture Register */
#define XBAR_ARBITER1_ERR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERR*)0xF8700094u)

/** Alias (User Manual Name) for XBAR_ARBITER1_ERR.
* To use register names with standard convension, please use XBAR_ARBITER1_ERR.
*/
#define	XBAR_ERR1	(XBAR_ARBITER1_ERR)

/** \brief  90, Error/Debug Address Capture Register */
#define XBAR_ARBITER1_ERRADDR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERRADDR*)0xF8700090u)

/** Alias (User Manual Name) for XBAR_ARBITER1_ERRADDR.
* To use register names with standard convension, please use XBAR_ARBITER1_ERRADDR.
*/
#define	XBAR_ERRADDR1	(XBAR_ARBITER1_ERRADDR)

/** \brief  88, Arbiter Priority Register */
#define XBAR_ARBITER1_PRIOH /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOH*)0xF8700088u)

/** Alias (User Manual Name) for XBAR_ARBITER1_PRIOH.
* To use register names with standard convension, please use XBAR_ARBITER1_PRIOH.
*/
#define	XBAR_PRIOH1	(XBAR_ARBITER1_PRIOH)

/** \brief  8C, Arbiter Priority Register */
#define XBAR_ARBITER1_PRIOL /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOL*)0xF870008Cu)

/** Alias (User Manual Name) for XBAR_ARBITER1_PRIOL.
* To use register names with standard convension, please use XBAR_ARBITER1_PRIOL.
*/
#define	XBAR_PRIOL1	(XBAR_ARBITER1_PRIOL)

/** \brief  144, Arbiter Control Register */
#define XBAR_ARBITER4_ARBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBCON*)0xF8700144u)

/** Alias (User Manual Name) for XBAR_ARBITER4_ARBCON.
* To use register names with standard convension, please use XBAR_ARBITER4_ARBCON.
*/
#define	XBAR_ARBCON4	(XBAR_ARBITER4_ARBCON)

/** \brief  15C, Debug Address Register */
#define XBAR_ARBITER4_DBADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER4_DBADD*)0xF870015Cu)

/** Alias (User Manual Name) for XBAR_ARBITER4_DBADD.
* To use register names with standard convension, please use XBAR_ARBITER4_DBADD.
*/
#define	XBAR_DBADD4	(XBAR_ARBITER4_DBADD)

/** \brief  158, Debug Control Register */
#define XBAR_ARBITER4_DBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_DBCON*)0xF8700158u)

/** Alias (User Manual Name) for XBAR_ARBITER4_DBCON.
* To use register names with standard convension, please use XBAR_ARBITER4_DBCON.
*/
#define	XBAR_DBCON4	(XBAR_ARBITER4_DBCON)

/** \brief  160, Debug Mask Address Register */
#define XBAR_ARBITER4_DBMADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER4_DBMADD*)0xF8700160u)

/** Alias (User Manual Name) for XBAR_ARBITER4_DBMADD.
* To use register names with standard convension, please use XBAR_ARBITER4_DBMADD.
*/
#define	XBAR_DBMADD4	(XBAR_ARBITER4_DBMADD)

/** \brief  154, Error/Debug Capture Register */
#define XBAR_ARBITER4_ERR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERR*)0xF8700154u)

/** Alias (User Manual Name) for XBAR_ARBITER4_ERR.
* To use register names with standard convension, please use XBAR_ARBITER4_ERR.
*/
#define	XBAR_ERR4	(XBAR_ARBITER4_ERR)

/** \brief  150, Error/Debug Address Capture Register */
#define XBAR_ARBITER4_ERRADDR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERRADDR*)0xF8700150u)

/** Alias (User Manual Name) for XBAR_ARBITER4_ERRADDR.
* To use register names with standard convension, please use XBAR_ARBITER4_ERRADDR.
*/
#define	XBAR_ERRADDR4	(XBAR_ARBITER4_ERRADDR)

/** \brief  148, Arbiter Priority Register */
#define XBAR_ARBITER4_PRIOH /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOH*)0xF8700148u)

/** Alias (User Manual Name) for XBAR_ARBITER4_PRIOH.
* To use register names with standard convension, please use XBAR_ARBITER4_PRIOH.
*/
#define	XBAR_PRIOH4	(XBAR_ARBITER4_PRIOH)

/** \brief  14C, Arbiter Priority Register */
#define XBAR_ARBITER4_PRIOL /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOL*)0xF870014Cu)

/** Alias (User Manual Name) for XBAR_ARBITER4_PRIOL.
* To use register names with standard convension, please use XBAR_ARBITER4_PRIOL.
*/
#define	XBAR_PRIOL4	(XBAR_ARBITER4_PRIOL)

/** \brief  1C4, Arbiter Control Register */
#define XBAR_ARBITER6_ARBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBCON*)0xF87001C4u)

/** Alias (User Manual Name) for XBAR_ARBITER6_ARBCON.
* To use register names with standard convension, please use XBAR_ARBITER6_ARBCON.
*/
#define	XBAR_ARBCON6	(XBAR_ARBITER6_ARBCON)

/** \brief  1DC, Debug Address Register */
#define XBAR_ARBITER6_DBADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER6_DBADD*)0xF87001DCu)

/** Alias (User Manual Name) for XBAR_ARBITER6_DBADD.
* To use register names with standard convension, please use XBAR_ARBITER6_DBADD.
*/
#define	XBAR_DBADD6	(XBAR_ARBITER6_DBADD)

/** \brief  1D8, Debug Control Register */
#define XBAR_ARBITER6_DBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_DBCON*)0xF87001D8u)

/** Alias (User Manual Name) for XBAR_ARBITER6_DBCON.
* To use register names with standard convension, please use XBAR_ARBITER6_DBCON.
*/
#define	XBAR_DBCON6	(XBAR_ARBITER6_DBCON)

/** \brief  1E0, Debug Mask Address Register */
#define XBAR_ARBITER6_DBMADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER6_DBMADD*)0xF87001E0u)

/** Alias (User Manual Name) for XBAR_ARBITER6_DBMADD.
* To use register names with standard convension, please use XBAR_ARBITER6_DBMADD.
*/
#define	XBAR_DBMADD6	(XBAR_ARBITER6_DBMADD)

/** \brief  1D4, Error/Debug Capture Register */
#define XBAR_ARBITER6_ERR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERR*)0xF87001D4u)

/** Alias (User Manual Name) for XBAR_ARBITER6_ERR.
* To use register names with standard convension, please use XBAR_ARBITER6_ERR.
*/
#define	XBAR_ERR6	(XBAR_ARBITER6_ERR)

/** \brief  1D0, Error/Debug Address Capture Register */
#define XBAR_ARBITER6_ERRADDR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERRADDR*)0xF87001D0u)

/** Alias (User Manual Name) for XBAR_ARBITER6_ERRADDR.
* To use register names with standard convension, please use XBAR_ARBITER6_ERRADDR.
*/
#define	XBAR_ERRADDR6	(XBAR_ARBITER6_ERRADDR)

/** \brief  1C8, Arbiter Priority Register */
#define XBAR_ARBITER6_PRIOH /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOH*)0xF87001C8u)

/** Alias (User Manual Name) for XBAR_ARBITER6_PRIOH.
* To use register names with standard convension, please use XBAR_ARBITER6_PRIOH.
*/
#define	XBAR_PRIOH6	(XBAR_ARBITER6_PRIOH)

/** \brief  1CC, Arbiter Priority Register */
#define XBAR_ARBITER6_PRIOL /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOL*)0xF87001CCu)

/** Alias (User Manual Name) for XBAR_ARBITER6_PRIOL.
* To use register names with standard convension, please use XBAR_ARBITER6_PRIOL.
*/
#define	XBAR_PRIOL6	(XBAR_ARBITER6_PRIOL)

/** \brief  204, Arbiter Control Register */
#define XBAR_ARBITER7_ARBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBCON*)0xF8700204u)

/** Alias (User Manual Name) for XBAR_ARBITER7_ARBCON.
* To use register names with standard convension, please use XBAR_ARBITER7_ARBCON.
*/
#define	XBAR_ARBCON7	(XBAR_ARBITER7_ARBCON)

/** \brief  21C, Debug Address Register */
#define XBAR_ARBITER7_DBADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER7_DBADD*)0xF870021Cu)

/** Alias (User Manual Name) for XBAR_ARBITER7_DBADD.
* To use register names with standard convension, please use XBAR_ARBITER7_DBADD.
*/
#define	XBAR_DBADD7	(XBAR_ARBITER7_DBADD)

/** \brief  218, Debug Control Register */
#define XBAR_ARBITER7_DBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_DBCON*)0xF8700218u)

/** Alias (User Manual Name) for XBAR_ARBITER7_DBCON.
* To use register names with standard convension, please use XBAR_ARBITER7_DBCON.
*/
#define	XBAR_DBCON7	(XBAR_ARBITER7_DBCON)

/** \brief  220, Debug Mask Address Register */
#define XBAR_ARBITER7_DBMADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER7_DBMADD*)0xF8700220u)

/** Alias (User Manual Name) for XBAR_ARBITER7_DBMADD.
* To use register names with standard convension, please use XBAR_ARBITER7_DBMADD.
*/
#define	XBAR_DBMADD7	(XBAR_ARBITER7_DBMADD)

/** \brief  214, Error/Debug Capture Register */
#define XBAR_ARBITER7_ERR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERR*)0xF8700214u)

/** Alias (User Manual Name) for XBAR_ARBITER7_ERR.
* To use register names with standard convension, please use XBAR_ARBITER7_ERR.
*/
#define	XBAR_ERR7	(XBAR_ARBITER7_ERR)

/** \brief  210, Error/Debug Address Capture Register */
#define XBAR_ARBITER7_ERRADDR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERRADDR*)0xF8700210u)

/** Alias (User Manual Name) for XBAR_ARBITER7_ERRADDR.
* To use register names with standard convension, please use XBAR_ARBITER7_ERRADDR.
*/
#define	XBAR_ERRADDR7	(XBAR_ARBITER7_ERRADDR)

/** \brief  208, Arbiter Priority Register */
#define XBAR_ARBITER7_PRIOH /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOH*)0xF8700208u)

/** Alias (User Manual Name) for XBAR_ARBITER7_PRIOH.
* To use register names with standard convension, please use XBAR_ARBITER7_PRIOH.
*/
#define	XBAR_PRIOH7	(XBAR_ARBITER7_PRIOH)

/** \brief  20C, Arbiter Priority Register */
#define XBAR_ARBITER7_PRIOL /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOL*)0xF870020Cu)

/** Alias (User Manual Name) for XBAR_ARBITER7_PRIOL.
* To use register names with standard convension, please use XBAR_ARBITER7_PRIOL.
*/
#define	XBAR_PRIOL7	(XBAR_ARBITER7_PRIOL)

/** \brief  244, Arbiter Control Register */
#define XBAR_ARBITER8_ARBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBCON*)0xF8700244u)

/** Alias (User Manual Name) for XBAR_ARBITER8_ARBCON.
* To use register names with standard convension, please use XBAR_ARBITER8_ARBCON.
*/
#define	XBAR_ARBCON8	(XBAR_ARBITER8_ARBCON)

/** \brief  25C, Debug Address Register */
#define XBAR_ARBITER8_DBADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER8_DBADD*)0xF870025Cu)

/** Alias (User Manual Name) for XBAR_ARBITER8_DBADD.
* To use register names with standard convension, please use XBAR_ARBITER8_DBADD.
*/
#define	XBAR_DBADD8	(XBAR_ARBITER8_DBADD)

/** \brief  258, Debug Control Register */
#define XBAR_ARBITER8_DBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_DBCON*)0xF8700258u)

/** Alias (User Manual Name) for XBAR_ARBITER8_DBCON.
* To use register names with standard convension, please use XBAR_ARBITER8_DBCON.
*/
#define	XBAR_DBCON8	(XBAR_ARBITER8_DBCON)

/** \brief  260, Debug Mask Address Register */
#define XBAR_ARBITER8_DBMADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITER8_DBMADD*)0xF8700260u)

/** Alias (User Manual Name) for XBAR_ARBITER8_DBMADD.
* To use register names with standard convension, please use XBAR_ARBITER8_DBMADD.
*/
#define	XBAR_DBMADD8	(XBAR_ARBITER8_DBMADD)

/** \brief  254, Error/Debug Capture Register */
#define XBAR_ARBITER8_ERR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERR*)0xF8700254u)

/** Alias (User Manual Name) for XBAR_ARBITER8_ERR.
* To use register names with standard convension, please use XBAR_ARBITER8_ERR.
*/
#define	XBAR_ERR8	(XBAR_ARBITER8_ERR)

/** \brief  250, Error/Debug Address Capture Register */
#define XBAR_ARBITER8_ERRADDR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERRADDR*)0xF8700250u)

/** Alias (User Manual Name) for XBAR_ARBITER8_ERRADDR.
* To use register names with standard convension, please use XBAR_ARBITER8_ERRADDR.
*/
#define	XBAR_ERRADDR8	(XBAR_ARBITER8_ERRADDR)

/** \brief  248, Arbiter Priority Register */
#define XBAR_ARBITER8_PRIOH /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOH*)0xF8700248u)

/** Alias (User Manual Name) for XBAR_ARBITER8_PRIOH.
* To use register names with standard convension, please use XBAR_ARBITER8_PRIOH.
*/
#define	XBAR_PRIOH8	(XBAR_ARBITER8_PRIOH)

/** \brief  24C, Arbiter Priority Register */
#define XBAR_ARBITER8_PRIOL /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOL*)0xF870024Cu)

/** Alias (User Manual Name) for XBAR_ARBITER8_PRIOL.
* To use register names with standard convension, please use XBAR_ARBITER8_PRIOL.
*/
#define	XBAR_PRIOL8	(XBAR_ARBITER8_PRIOL)

/** \brief  4, Arbiter Control Register */
#define XBAR_ARBITERD_ARBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBCON*)0xF8700004u)

/** Alias (User Manual Name) for XBAR_ARBITERD_ARBCON.
* To use register names with standard convension, please use XBAR_ARBITERD_ARBCON.
*/
#define	XBAR_ARBCOND	(XBAR_ARBITERD_ARBCON)

/** \brief  1C, Debug Address Register */
#define XBAR_ARBITERD_DBADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITERD_DBADD*)0xF870001Cu)

/** Alias (User Manual Name) for XBAR_ARBITERD_DBADD.
* To use register names with standard convension, please use XBAR_ARBITERD_DBADD.
*/
#define	XBAR_DBADDD	(XBAR_ARBITERD_DBADD)

/** \brief  18, Debug Control Register */
#define XBAR_ARBITERD_DBCON /*lint --e(923)*/ (*(volatile Ifx_XBAR_DBCON*)0xF8700018u)

/** Alias (User Manual Name) for XBAR_ARBITERD_DBCON.
* To use register names with standard convension, please use XBAR_ARBITERD_DBCON.
*/
#define	XBAR_DBCOND	(XBAR_ARBITERD_DBCON)

/** \brief  20, Debug Mask Address Register */
#define XBAR_ARBITERD_DBMADD /*lint --e(923)*/ (*(volatile Ifx_XBAR_ARBITERD_DBMADD*)0xF8700020u)

/** Alias (User Manual Name) for XBAR_ARBITERD_DBMADD.
* To use register names with standard convension, please use XBAR_ARBITERD_DBMADD.
*/
#define	XBAR_DBMADDD	(XBAR_ARBITERD_DBMADD)

/** \brief  14, Error/Debug Capture Register */
#define XBAR_ARBITERD_ERR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERR*)0xF8700014u)

/** Alias (User Manual Name) for XBAR_ARBITERD_ERR.
* To use register names with standard convension, please use XBAR_ARBITERD_ERR.
*/
#define	XBAR_ERRD	(XBAR_ARBITERD_ERR)

/** \brief  10, Error/Debug Address Capture Register */
#define XBAR_ARBITERD_ERRADDR /*lint --e(923)*/ (*(volatile Ifx_XBAR_ERRADDR*)0xF8700010u)

/** Alias (User Manual Name) for XBAR_ARBITERD_ERRADDR.
* To use register names with standard convension, please use XBAR_ARBITERD_ERRADDR.
*/
#define	XBAR_ERRADDRD	(XBAR_ARBITERD_ERRADDR)

/** \brief  8, Arbiter Priority Register */
#define XBAR_ARBITERD_PRIOH /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOH*)0xF8700008u)

/** Alias (User Manual Name) for XBAR_ARBITERD_PRIOH.
* To use register names with standard convension, please use XBAR_ARBITERD_PRIOH.
*/
#define	XBAR_PRIOHD	(XBAR_ARBITERD_PRIOH)

/** \brief  C, Arbiter Priority Register */
#define XBAR_ARBITERD_PRIOL /*lint --e(923)*/ (*(volatile Ifx_XBAR_PRIOL*)0xF870000Cu)

/** Alias (User Manual Name) for XBAR_ARBITERD_PRIOL.
* To use register names with standard convension, please use XBAR_ARBITERD_PRIOL.
*/
#define	XBAR_PRIOLD	(XBAR_ARBITERD_PRIOL)

/** \brief  40C, Debug Trigger Event Status Register */
#define XBAR_DBSAT /*lint --e(923)*/ (*(volatile Ifx_XBAR_DBSAT*)0xF870040Cu)

/** \brief  0, External Control Register D */
#define XBAR_EXTCOND /*lint --e(923)*/ (*(volatile Ifx_XBAR_EXTCOND*)0xF8700000u)

/** \brief  408, Module Identification Register */
#define XBAR_ID /*lint --e(923)*/ (*(volatile Ifx_XBAR_ID*)0xF8700408u)

/** \brief  418, Transaction ID Interrupt Enable Register */
#define XBAR_IDINTEN /*lint --e(923)*/ (*(volatile Ifx_XBAR_IDINTEN*)0xF8700418u)

/** \brief  414, Transaction ID Interrupt Status Register */
#define XBAR_IDINTSAT /*lint --e(923)*/ (*(volatile Ifx_XBAR_IDINTSAT*)0xF8700414u)

/** \brief  410, Arbiter Interrupt Status Register */
#define XBAR_INTSAT /*lint --e(923)*/ (*(volatile Ifx_XBAR_INTSAT*)0xF8700410u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXXBAR_REG_H */
