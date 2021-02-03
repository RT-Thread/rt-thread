/**
 * \file IfxGpt12_reg.h
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
 * \defgroup IfxLld_Gpt12_Cfg Gpt12 address
 * \ingroup IfxLld_Gpt12
 * 
 * \defgroup IfxLld_Gpt12_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Gpt12_Cfg
 * 
 * \defgroup IfxLld_Gpt12_Cfg_Gpt120 2-GPT120
 * \ingroup IfxLld_Gpt12_Cfg
 * 
 */
#ifndef IFXGPT12_REG_H
#define IFXGPT12_REG_H 1
/******************************************************************************/
#include "IfxGpt12_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Gpt12_Cfg_BaseAddress
 * \{  */

/** \brief  GPT12 object */
#define MODULE_GPT120 /*lint --e(923)*/ (*(Ifx_GPT12*)0xF0002E00u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Gpt12_Cfg_Gpt120
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define GPT120_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_GPT12_ACCEN0*)0xF0002EFCu)

/** \brief  F8, Access Enable Register 1 */
#define GPT120_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_GPT12_ACCEN1*)0xF0002EF8u)

/** \brief  30, Capture and Reload Register */
#define GPT120_CAPREL /*lint --e(923)*/ (*(volatile Ifx_GPT12_CAPREL*)0xF0002E30u)

/** \brief  0, Clock Control Register */
#define GPT120_CLC /*lint --e(923)*/ (*(volatile Ifx_GPT12_CLC*)0xF0002E00u)

/** \brief  8, Identification Register */
#define GPT120_ID /*lint --e(923)*/ (*(volatile Ifx_GPT12_ID*)0xF0002E08u)

/** \brief  F4, Kernel Reset Register 0 */
#define GPT120_KRST0 /*lint --e(923)*/ (*(volatile Ifx_GPT12_KRST0*)0xF0002EF4u)

/** \brief  F0, Kernel Reset Register 1 */
#define GPT120_KRST1 /*lint --e(923)*/ (*(volatile Ifx_GPT12_KRST1*)0xF0002EF0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define GPT120_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_GPT12_KRSTCLR*)0xF0002EECu)

/** \brief  E8, OCDS Control and Status Register */
#define GPT120_OCS /*lint --e(923)*/ (*(volatile Ifx_GPT12_OCS*)0xF0002EE8u)

/** \brief  4, Port Input Select Register */
#define GPT120_PISEL /*lint --e(923)*/ (*(volatile Ifx_GPT12_PISEL*)0xF0002E04u)

/** \brief  34, Timer T2 Register */
#define GPT120_T2 /*lint --e(923)*/ (*(volatile Ifx_GPT12_T2*)0xF0002E34u)

/** \brief  10, Timer T2 Control Register */
#define GPT120_T2CON /*lint --e(923)*/ (*(volatile Ifx_GPT12_T2CON*)0xF0002E10u)

/** \brief  38, Timer T3 Register */
#define GPT120_T3 /*lint --e(923)*/ (*(volatile Ifx_GPT12_T3*)0xF0002E38u)

/** \brief  14, Timer T3 Control Register */
#define GPT120_T3CON /*lint --e(923)*/ (*(volatile Ifx_GPT12_T3CON*)0xF0002E14u)

/** \brief  3C, Timer T4 Register */
#define GPT120_T4 /*lint --e(923)*/ (*(volatile Ifx_GPT12_T4*)0xF0002E3Cu)

/** \brief  18, Timer T4 Control Register */
#define GPT120_T4CON /*lint --e(923)*/ (*(volatile Ifx_GPT12_T4CON*)0xF0002E18u)

/** \brief  40, Timer T5 Register */
#define GPT120_T5 /*lint --e(923)*/ (*(volatile Ifx_GPT12_T5*)0xF0002E40u)

/** \brief  1C, Timer T5 Control Register */
#define GPT120_T5CON /*lint --e(923)*/ (*(volatile Ifx_GPT12_T5CON*)0xF0002E1Cu)

/** \brief  44, Timer T6 Register */
#define GPT120_T6 /*lint --e(923)*/ (*(volatile Ifx_GPT12_T6*)0xF0002E44u)

/** \brief  20, Timer T6 Control Register */
#define GPT120_T6CON /*lint --e(923)*/ (*(volatile Ifx_GPT12_T6CON*)0xF0002E20u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXGPT12_REG_H */
