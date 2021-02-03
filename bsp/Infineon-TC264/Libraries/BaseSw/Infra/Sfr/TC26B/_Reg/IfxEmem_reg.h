/**
 * \file IfxEmem_reg.h
 * \brief
 * \copyright Copyright (c) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Version: TC2XXED_TS_V1.0.R2
 * Specification: AurixED_TS_V1.0_CPU_VIEW_SFR.xml (Revision: V1.0)
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
 * \defgroup IfxLld_Emem_Cfg Emem address
 * \ingroup IfxLld_Emem
 * 
 * \defgroup IfxLld_Emem_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Emem_Cfg
 * 
 * \defgroup IfxLld_Emem_Cfg_Emem 2-EMEM
 * \ingroup IfxLld_Emem_Cfg
 * 
 */
#ifndef IFXEMEM_REG_H
#define IFXEMEM_REG_H 1
/******************************************************************************/
#include "IfxEmem_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Emem_Cfg_BaseAddress
 * \{  */

/** \brief  EMEM object */
#define MODULE_EMEM /*lint --e(923)*/ (*(Ifx_EMEM*)0xF90E6000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Emem_Cfg_Emem
 * \{  */

/** \brief  0, Clock Control Register */
#define EMEM_CLC /*lint --e(923)*/ (*(volatile Ifx_EMEM_CLC*)0xF90E6000u)

/** \brief  8, Module Identification Register */
#define EMEM_ID /*lint --e(923)*/ (*(volatile Ifx_EMEM_ID*)0xF90E6008u)

/** \brief  34, Standby RAM Control Register */
#define EMEM_SBRCTR /*lint --e(923)*/ (*(volatile Ifx_EMEM_SBRCTR*)0xF90E6034u)

/** \brief  24, Calibration Tile Control Register */
#define EMEM_TILECC /*lint --e(923)*/ (*(volatile Ifx_EMEM_TILECC*)0xF90E6024u)

/** \brief  20, Tile Configuration Register */
#define EMEM_TILECONFIG /*lint --e(923)*/ (*(volatile Ifx_EMEM_TILECONFIG*)0xF90E6020u)

/** \brief  40, Extended Tile Configuration Register */
#define EMEM_TILECONFIGXM /*lint --e(923)*/ (*(volatile Ifx_EMEM_TILECONFIGXM*)0xF90E6040u)

/** \brief  28, Trace Tile Control Register */
#define EMEM_TILECT /*lint --e(923)*/ (*(volatile Ifx_EMEM_TILECT*)0xF90E6028u)

/** \brief  2C, Tile Status Register */
#define EMEM_TILESTATE /*lint --e(923)*/ (*(volatile Ifx_EMEM_TILESTATE*)0xF90E602Cu)

/** \brief  4C, Extended Tile Status Register */
#define EMEM_TILESTATEXM /*lint --e(923)*/ (*(volatile Ifx_EMEM_TILESTATEXM*)0xF90E604Cu)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXEMEM_REG_H */
