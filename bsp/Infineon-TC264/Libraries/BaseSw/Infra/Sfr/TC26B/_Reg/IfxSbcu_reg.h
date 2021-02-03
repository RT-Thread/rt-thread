/**
 * \file IfxSbcu_reg.h
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
 * \defgroup IfxLld_Sbcu_Cfg Sbcu address
 * \ingroup IfxLld_Sbcu
 * 
 * \defgroup IfxLld_Sbcu_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Sbcu_Cfg
 * 
 * \defgroup IfxLld_Sbcu_Cfg_Sbcu0 2-SBCU0
 * \ingroup IfxLld_Sbcu_Cfg
 * 
 */
#ifndef IFXSBCU_REG_H
#define IFXSBCU_REG_H 1
/******************************************************************************/
#include "IfxSbcu_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Sbcu_Cfg_BaseAddress
 * \{  */

/** \brief  SBCU object */
#define MODULE_SBCU0 /*lint --e(923)*/ (*(Ifx_SBCU*)0xF0030000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Sbcu_Cfg_Sbcu0
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define SBCU0_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_SBCU_ACCEN0*)0xF00300FCu)

/** Alias (User Manual Name) for SBCU0_ACCEN0.
* To use register names with standard convension, please use SBCU0_ACCEN0.
*/
#define	SBCU_ACCEN0	(SBCU0_ACCEN0)

/** \brief  F8, Access Enable Register 1 */
#define SBCU0_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_SBCU_ACCEN1*)0xF00300F8u)

/** Alias (User Manual Name) for SBCU0_ACCEN1.
* To use register names with standard convension, please use SBCU0_ACCEN1.
*/
#define	SBCU_ACCEN1	(SBCU0_ACCEN1)

/** \brief  10, SBCU Control Register */
#define SBCU0_CON /*lint --e(923)*/ (*(volatile Ifx_SBCU_CON*)0xF0030010u)

/** Alias (User Manual Name) for SBCU0_CON.
* To use register names with standard convension, please use SBCU0_CON.
*/
#define	SBCU_CON	(SBCU0_CON)

/** \brief  38, SBCU Debug Address 1 Register */
#define SBCU0_DBADR1 /*lint --e(923)*/ (*(volatile Ifx_SBCU_DBADR1*)0xF0030038u)

/** Alias (User Manual Name) for SBCU0_DBADR1.
* To use register names with standard convension, please use SBCU0_DBADR1.
*/
#define	SBCU_DBADR1	(SBCU0_DBADR1)

/** \brief  3C, SBCU Debug Address 2 Register */
#define SBCU0_DBADR2 /*lint --e(923)*/ (*(volatile Ifx_SBCU_DBADR2*)0xF003003Cu)

/** Alias (User Manual Name) for SBCU0_DBADR2.
* To use register names with standard convension, please use SBCU0_DBADR2.
*/
#define	SBCU_DBADR2	(SBCU0_DBADR2)

/** \brief  48, SBCU Debug Trapped Address Register */
#define SBCU0_DBADRT /*lint --e(923)*/ (*(volatile Ifx_SBCU_DBADRT*)0xF0030048u)

/** Alias (User Manual Name) for SBCU0_DBADRT.
* To use register names with standard convension, please use SBCU0_DBADRT.
*/
#define	SBCU_DBADRT	(SBCU0_DBADRT)

/** \brief  40, SBCU Debug Bus Operation Signals Register */
#define SBCU0_DBBOS /*lint --e(923)*/ (*(volatile Ifx_SBCU_DBBOS*)0xF0030040u)

/** Alias (User Manual Name) for SBCU0_DBBOS.
* To use register names with standard convension, please use SBCU0_DBBOS.
*/
#define	SBCU_DBBOS	(SBCU0_DBBOS)

/** \brief  4C, SBCU Debug Trapped Bus Operation Signals Register */
#define SBCU0_DBBOST /*lint --e(923)*/ (*(volatile Ifx_SBCU_DBBOST*)0xF003004Cu)

/** Alias (User Manual Name) for SBCU0_DBBOST.
* To use register names with standard convension, please use SBCU0_DBBOST.
*/
#define	SBCU_DBBOST	(SBCU0_DBBOST)

/** \brief  30, SBCU Debug Control Register */
#define SBCU0_DBCNTL /*lint --e(923)*/ (*(volatile Ifx_SBCU_DBCNTL*)0xF0030030u)

/** Alias (User Manual Name) for SBCU0_DBCNTL.
* To use register names with standard convension, please use SBCU0_DBCNTL.
*/
#define	SBCU_DBCNTL	(SBCU0_DBCNTL)

/** \brief  50, SBCU Debug Data Status Register */
#define SBCU0_DBDAT /*lint --e(923)*/ (*(volatile Ifx_SBCU_DBDAT*)0xF0030050u)

/** Alias (User Manual Name) for SBCU0_DBDAT.
* To use register names with standard convension, please use SBCU0_DBDAT.
*/
#define	SBCU_DBDAT	(SBCU0_DBDAT)

/** \brief  44, SBCU Debug Trapped Master Register */
#define SBCU0_DBGNTT /*lint --e(923)*/ (*(volatile Ifx_SBCU_DBGNTT*)0xF0030044u)

/** Alias (User Manual Name) for SBCU0_DBGNTT.
* To use register names with standard convension, please use SBCU0_DBGNTT.
*/
#define	SBCU_DBGNTT	(SBCU0_DBGNTT)

/** \brief  34, SBCU Debug Grant Mask Register */
#define SBCU0_DBGRNT /*lint --e(923)*/ (*(volatile Ifx_SBCU_DBGRNT*)0xF0030034u)

/** Alias (User Manual Name) for SBCU0_DBGRNT.
* To use register names with standard convension, please use SBCU0_DBGRNT.
*/
#define	SBCU_DBGRNT	(SBCU0_DBGRNT)

/** \brief  24, SBCU Error Address Capture Register */
#define SBCU0_EADD /*lint --e(923)*/ (*(volatile Ifx_SBCU_EADD*)0xF0030024u)

/** Alias (User Manual Name) for SBCU0_EADD.
* To use register names with standard convension, please use SBCU0_EADD.
*/
#define	SBCU_EADD	(SBCU0_EADD)

/** \brief  20, SBCU Error Control Capture Register */
#define SBCU0_ECON /*lint --e(923)*/ (*(volatile Ifx_SBCU_ECON*)0xF0030020u)

/** Alias (User Manual Name) for SBCU0_ECON.
* To use register names with standard convension, please use SBCU0_ECON.
*/
#define	SBCU_ECON	(SBCU0_ECON)

/** \brief  28, SBCU Error Data Capture Register */
#define SBCU0_EDAT /*lint --e(923)*/ (*(volatile Ifx_SBCU_EDAT*)0xF0030028u)

/** Alias (User Manual Name) for SBCU0_EDAT.
* To use register names with standard convension, please use SBCU0_EDAT.
*/
#define	SBCU_EDAT	(SBCU0_EDAT)

/** \brief  8, Module Identification Register */
#define SBCU0_ID /*lint --e(923)*/ (*(volatile Ifx_SBCU_ID*)0xF0030008u)

/** Alias (User Manual Name) for SBCU0_ID.
* To use register names with standard convension, please use SBCU0_ID.
*/
#define	SBCU_ID	(SBCU0_ID)

/** \brief  14, Arbiter Priority Register High */
#define SBCU0_PRIOH /*lint --e(923)*/ (*(volatile Ifx_SBCU_PRIOH*)0xF0030014u)

/** Alias (User Manual Name) for SBCU0_PRIOH.
* To use register names with standard convension, please use SBCU0_PRIOH.
*/
#define	SBCU_PRIOH	(SBCU0_PRIOH)

/** \brief  18, Arbiter Priority Register Low */
#define SBCU0_PRIOL /*lint --e(923)*/ (*(volatile Ifx_SBCU_PRIOL*)0xF0030018u)

/** Alias (User Manual Name) for SBCU0_PRIOL.
* To use register names with standard convension, please use SBCU0_PRIOL.
*/
#define	SBCU_PRIOL	(SBCU0_PRIOL)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSBCU_REG_H */
