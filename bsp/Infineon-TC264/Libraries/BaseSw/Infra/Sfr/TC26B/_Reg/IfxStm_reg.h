/**
 * \file IfxStm_reg.h
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
 * \defgroup IfxLld_Stm_Cfg Stm address
 * \ingroup IfxLld_Stm
 * 
 * \defgroup IfxLld_Stm_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Stm_Cfg
 * 
 * \defgroup IfxLld_Stm_Cfg_Stm0 2-STM0
 * \ingroup IfxLld_Stm_Cfg
 * 
 * \defgroup IfxLld_Stm_Cfg_Stm1 2-STM1
 * \ingroup IfxLld_Stm_Cfg
 * 
 */
#ifndef IFXSTM_REG_H
#define IFXSTM_REG_H 1
/******************************************************************************/
#include "IfxStm_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Stm_Cfg_BaseAddress
 * \{  */

/** \brief  STM object */
#define MODULE_STM0 /*lint --e(923)*/ (*(Ifx_STM*)0xF0000000u)

/** \brief  STM object */
#define MODULE_STM1 /*lint --e(923)*/ (*(Ifx_STM*)0xF0000100u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Stm_Cfg_Stm0
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define STM0_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_STM_ACCEN0*)0xF00000FCu)

/** \brief  F8, Access Enable Register 1 */
#define STM0_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_STM_ACCEN1*)0xF00000F8u)

/** \brief  2C, Timer Capture Register */
#define STM0_CAP /*lint --e(923)*/ (*(volatile Ifx_STM_CAP*)0xF000002Cu)

/** \brief  54, Timer Capture Register Second View */
#define STM0_CAPSV /*lint --e(923)*/ (*(volatile Ifx_STM_CAPSV*)0xF0000054u)

/** \brief  0, Clock Control Register */
#define STM0_CLC /*lint --e(923)*/ (*(volatile Ifx_STM_CLC*)0xF0000000u)

/** \brief  38, Compare Match Control Register */
#define STM0_CMCON /*lint --e(923)*/ (*(volatile Ifx_STM_CMCON*)0xF0000038u)

/** \brief  30, Compare Register */
#define STM0_CMP0 /*lint --e(923)*/ (*(volatile Ifx_STM_CMP*)0xF0000030u)

/** \brief  34, Compare Register */
#define STM0_CMP1 /*lint --e(923)*/ (*(volatile Ifx_STM_CMP*)0xF0000034u)

/** \brief  3C, Interrupt Control Register */
#define STM0_ICR /*lint --e(923)*/ (*(volatile Ifx_STM_ICR*)0xF000003Cu)

/** \brief  8, Module Identification Register */
#define STM0_ID /*lint --e(923)*/ (*(volatile Ifx_STM_ID*)0xF0000008u)

/** \brief  40, Interrupt Set/Clear Register */
#define STM0_ISCR /*lint --e(923)*/ (*(volatile Ifx_STM_ISCR*)0xF0000040u)

/** \brief  F4, Kernel Reset Register 0 */
#define STM0_KRST0 /*lint --e(923)*/ (*(volatile Ifx_STM_KRST0*)0xF00000F4u)

/** \brief  F0, Kernel Reset Register 1 */
#define STM0_KRST1 /*lint --e(923)*/ (*(volatile Ifx_STM_KRST1*)0xF00000F0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define STM0_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_STM_KRSTCLR*)0xF00000ECu)

/** \brief  E8, OCDS Control and Status */
#define STM0_OCS /*lint --e(923)*/ (*(volatile Ifx_STM_OCS*)0xF00000E8u)

/** \brief  10, Timer Register 0 */
#define STM0_TIM0 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM0*)0xF0000010u)

/** \brief  50, Timer Register 0 Second View */
#define STM0_TIM0SV /*lint --e(923)*/ (*(volatile Ifx_STM_TIM0SV*)0xF0000050u)

/** \brief  14, Timer Register 1 */
#define STM0_TIM1 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM1*)0xF0000014u)

/** \brief  18, Timer Register 2 */
#define STM0_TIM2 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM2*)0xF0000018u)

/** \brief  1C, Timer Register 3 */
#define STM0_TIM3 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM3*)0xF000001Cu)

/** \brief  20, Timer Register 4 */
#define STM0_TIM4 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM4*)0xF0000020u)

/** \brief  24, Timer Register 5 */
#define STM0_TIM5 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM5*)0xF0000024u)

/** \brief  28, Timer Register 6 */
#define STM0_TIM6 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM6*)0xF0000028u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Stm_Cfg_Stm1
 * \{  */

/** \brief  FC, Access Enable Register 0 */
#define STM1_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_STM_ACCEN0*)0xF00001FCu)

/** \brief  F8, Access Enable Register 1 */
#define STM1_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_STM_ACCEN1*)0xF00001F8u)

/** \brief  2C, Timer Capture Register */
#define STM1_CAP /*lint --e(923)*/ (*(volatile Ifx_STM_CAP*)0xF000012Cu)

/** \brief  54, Timer Capture Register Second View */
#define STM1_CAPSV /*lint --e(923)*/ (*(volatile Ifx_STM_CAPSV*)0xF0000154u)

/** \brief  0, Clock Control Register */
#define STM1_CLC /*lint --e(923)*/ (*(volatile Ifx_STM_CLC*)0xF0000100u)

/** \brief  38, Compare Match Control Register */
#define STM1_CMCON /*lint --e(923)*/ (*(volatile Ifx_STM_CMCON*)0xF0000138u)

/** \brief  30, Compare Register */
#define STM1_CMP0 /*lint --e(923)*/ (*(volatile Ifx_STM_CMP*)0xF0000130u)

/** \brief  34, Compare Register */
#define STM1_CMP1 /*lint --e(923)*/ (*(volatile Ifx_STM_CMP*)0xF0000134u)

/** \brief  3C, Interrupt Control Register */
#define STM1_ICR /*lint --e(923)*/ (*(volatile Ifx_STM_ICR*)0xF000013Cu)

/** \brief  8, Module Identification Register */
#define STM1_ID /*lint --e(923)*/ (*(volatile Ifx_STM_ID*)0xF0000108u)

/** \brief  40, Interrupt Set/Clear Register */
#define STM1_ISCR /*lint --e(923)*/ (*(volatile Ifx_STM_ISCR*)0xF0000140u)

/** \brief  F4, Kernel Reset Register 0 */
#define STM1_KRST0 /*lint --e(923)*/ (*(volatile Ifx_STM_KRST0*)0xF00001F4u)

/** \brief  F0, Kernel Reset Register 1 */
#define STM1_KRST1 /*lint --e(923)*/ (*(volatile Ifx_STM_KRST1*)0xF00001F0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define STM1_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_STM_KRSTCLR*)0xF00001ECu)

/** \brief  E8, OCDS Control and Status */
#define STM1_OCS /*lint --e(923)*/ (*(volatile Ifx_STM_OCS*)0xF00001E8u)

/** \brief  10, Timer Register 0 */
#define STM1_TIM0 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM0*)0xF0000110u)

/** \brief  50, Timer Register 0 Second View */
#define STM1_TIM0SV /*lint --e(923)*/ (*(volatile Ifx_STM_TIM0SV*)0xF0000150u)

/** \brief  14, Timer Register 1 */
#define STM1_TIM1 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM1*)0xF0000114u)

/** \brief  18, Timer Register 2 */
#define STM1_TIM2 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM2*)0xF0000118u)

/** \brief  1C, Timer Register 3 */
#define STM1_TIM3 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM3*)0xF000011Cu)

/** \brief  20, Timer Register 4 */
#define STM1_TIM4 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM4*)0xF0000120u)

/** \brief  24, Timer Register 5 */
#define STM1_TIM5 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM5*)0xF0000124u)

/** \brief  28, Timer Register 6 */
#define STM1_TIM6 /*lint --e(923)*/ (*(volatile Ifx_STM_TIM6*)0xF0000128u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXSTM_REG_H */
