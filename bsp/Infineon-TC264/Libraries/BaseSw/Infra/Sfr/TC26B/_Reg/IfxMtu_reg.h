/**
 * \file IfxMtu_reg.h
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
 * \defgroup IfxLld_Mtu_Cfg Mtu address
 * \ingroup IfxLld_Mtu
 * 
 * \defgroup IfxLld_Mtu_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Mtu_Cfg
 * 
 * \defgroup IfxLld_Mtu_Cfg_Mtu 2-MTU
 * \ingroup IfxLld_Mtu_Cfg
 * 
 */
#ifndef IFXMTU_REG_H
#define IFXMTU_REG_H 1
/******************************************************************************/
#include "IfxMtu_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Mtu_Cfg_BaseAddress
 * \{  */

/** \brief  MTU object */
#define MODULE_MTU /*lint --e(923)*/ (*(Ifx_MTU*)0xF0060000u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Mtu_Cfg_Mtu
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define MTU_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_MTU_ACCEN0*)0xF00600FCu)

/** \brief  F8, Access Enable Register 1 */
#define MTU_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_MTU_ACCEN1*)0xF00600F8u)

/** \brief  0, Identification Register */
#define MTU_CLC /*lint --e(923)*/ (*(volatile Ifx_MTU_CLC*)0xF0060000u)

/** \brief  8, Identification Register */
#define MTU_ID /*lint --e(923)*/ (*(volatile Ifx_MTU_ID*)0xF0060008u)

/** \brief  1C, Memory Mapping Enable Register */
#define MTU_MEMMAP /*lint --e(923)*/ (*(volatile Ifx_MTU_MEMMAP*)0xF006001Cu)

/** \brief  38, Memory Status Register 0 */
#define MTU_MEMSTAT0 /*lint --e(923)*/ (*(volatile Ifx_MTU_MEMSTAT0*)0xF0060038u)

/** \brief  3C, Memory Status Register 1 */
#define MTU_MEMSTAT1 /*lint --e(923)*/ (*(volatile Ifx_MTU_MEMSTAT1*)0xF006003Cu)

/** \brief  40, Memory Status Register 2 */
#define MTU_MEMSTAT2 /*lint --e(923)*/ (*(volatile Ifx_MTU_MEMSTAT2*)0xF0060040u)

/** \brief  10, Memory MBISTEnable Register 0 */
#define MTU_MEMTEST0 /*lint --e(923)*/ (*(volatile Ifx_MTU_MEMTEST0*)0xF0060010u)

/** \brief  14, Memory MBISTEnable Register 1 */
#define MTU_MEMTEST1 /*lint --e(923)*/ (*(volatile Ifx_MTU_MEMTEST1*)0xF0060014u)

/** \brief  18, Memory MBISTEnable Register 2 */
#define MTU_MEMTEST2 /*lint --e(923)*/ (*(volatile Ifx_MTU_MEMTEST2*)0xF0060018u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXMTU_REG_H */
