/**
 * \file IfxMsc_reg.h
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
 * \defgroup IfxLld_Msc_Cfg Msc address
 * \ingroup IfxLld_Msc
 * 
 * \defgroup IfxLld_Msc_Cfg_BaseAddress Base address
 * \ingroup IfxLld_Msc_Cfg
 * 
 * \defgroup IfxLld_Msc_Cfg_Msc0 2-MSC0
 * \ingroup IfxLld_Msc_Cfg
 * 
 * \defgroup IfxLld_Msc_Cfg_Msc1 2-MSC1
 * \ingroup IfxLld_Msc_Cfg
 * 
 */
#ifndef IFXMSC_REG_H
#define IFXMSC_REG_H 1
/******************************************************************************/
#include "IfxMsc_regdef.h"
/******************************************************************************/
/** \addtogroup IfxLld_Msc_Cfg_BaseAddress
 * \{  */

/** \brief  MSC object */
#define MODULE_MSC0 /*lint --e(923)*/ (*(Ifx_MSC*)0xF0002600u)

/** \brief  MSC object */
#define MODULE_MSC1 /*lint --e(923)*/ (*(Ifx_MSC*)0xF0002700u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Msc_Cfg_Msc0
 * \{  */

/** \brief  80, Asynchronous Block Configuration Register */
#define MSC0_ABC /*lint --e(923)*/ (*(volatile Ifx_MSC_ABC*)0xF0002680u)

/** \brief  FC, Access Enable Register 0 */
#define MSC0_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_MSC_ACCEN0*)0xF00026FCu)

/** \brief  F8, Access Enable Register 1 */
#define MSC0_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_MSC_ACCEN1*)0xF00026F8u)

/** \brief  0, Clock Control Register */
#define MSC0_CLC /*lint --e(923)*/ (*(volatile Ifx_MSC_CLC*)0xF0002600u)

/** \brief  20, Downstream Command Register */
#define MSC0_DC /*lint --e(923)*/ (*(volatile Ifx_MSC_DC*)0xF0002620u)

/** \brief  1C, Downstream Data Register */
#define MSC0_DD /*lint --e(923)*/ (*(volatile Ifx_MSC_DD*)0xF000261Cu)

/** \brief  6C, Downstream Data Extension Register */
#define MSC0_DDE /*lint --e(923)*/ (*(volatile Ifx_MSC_DDE*)0xF000266Cu)

/** \brief  70, Downstream Data Mirror Register */
#define MSC0_DDM /*lint --e(923)*/ (*(volatile Ifx_MSC_DDM*)0xF0002670u)

/** \brief  14, Downstream Control Register */
#define MSC0_DSC /*lint --e(923)*/ (*(volatile Ifx_MSC_DSC*)0xF0002614u)

/** \brief  58, Downstream Control Enhanced Register 1 */
#define MSC0_DSCE /*lint --e(923)*/ (*(volatile Ifx_MSC_DSCE*)0xF0002658u)

/** \brief  28, Downstream Select Data Source High Register */
#define MSC0_DSDSH /*lint --e(923)*/ (*(volatile Ifx_MSC_DSDSH*)0xF0002628u)

/** \brief  64, Downstream Select Data Source High Register */
#define MSC0_DSDSHE /*lint --e(923)*/ (*(volatile Ifx_MSC_DSDSHE*)0xF0002664u)

/** \brief  24, Downstream Select Data Source Low Register */
#define MSC0_DSDSL /*lint --e(923)*/ (*(volatile Ifx_MSC_DSDSL*)0xF0002624u)

/** \brief  60, Downstream Select Data Source Low Extension Register */
#define MSC0_DSDSLE /*lint --e(923)*/ (*(volatile Ifx_MSC_DSDSLE*)0xF0002660u)

/** \brief  18, Downstream Status Register */
#define MSC0_DSS /*lint --e(923)*/ (*(volatile Ifx_MSC_DSS*)0xF0002618u)

/** \brief  74, Downstream Timing Extension Register */
#define MSC0_DSTE /*lint --e(923)*/ (*(volatile Ifx_MSC_DSTE*)0xF0002674u)

/** \brief  2C, Emergency Stop Register */
#define MSC0_ESR /*lint --e(923)*/ (*(volatile Ifx_MSC_ESR*)0xF000262Cu)

/** \brief  68, Emergency Stop Extension Register */
#define MSC0_ESRE /*lint --e(923)*/ (*(volatile Ifx_MSC_ESRE*)0xF0002668u)

/** \brief  C, Fractional Divider Register */
#define MSC0_FDR /*lint --e(923)*/ (*(volatile Ifx_MSC_FDR*)0xF000260Cu)

/** \brief  40, Interrupt Control Register */
#define MSC0_ICR /*lint --e(923)*/ (*(volatile Ifx_MSC_ICR*)0xF0002640u)

/** \brief  8, Module Identification Register */
#define MSC0_ID /*lint --e(923)*/ (*(volatile Ifx_MSC_ID*)0xF0002608u)

/** \brief  48, Interrupt Set Clear Register */
#define MSC0_ISC /*lint --e(923)*/ (*(volatile Ifx_MSC_ISC*)0xF0002648u)

/** \brief  44, Interrupt Status Register */
#define MSC0_ISR /*lint --e(923)*/ (*(volatile Ifx_MSC_ISR*)0xF0002644u)

/** \brief  F4, Kernel Reset Register 0 */
#define MSC0_KRST0 /*lint --e(923)*/ (*(volatile Ifx_MSC_KRST0*)0xF00026F4u)

/** \brief  F0, Kernel Reset Register 1 */
#define MSC0_KRST1 /*lint --e(923)*/ (*(volatile Ifx_MSC_KRST1*)0xF00026F0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define MSC0_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_MSC_KRSTCLR*)0xF00026ECu)

/** \brief  4C, Output Control Register */
#define MSC0_OCR /*lint --e(923)*/ (*(volatile Ifx_MSC_OCR*)0xF000264Cu)

/** \brief  E8, OCDS Control and Status */
#define MSC0_OCS /*lint --e(923)*/ (*(volatile Ifx_MSC_OCS*)0xF00026E8u)

/** \brief  30, Upstream Data Register */
#define MSC0_UD0 /*lint --e(923)*/ (*(volatile Ifx_MSC_UD*)0xF0002630u)

/** \brief  34, Upstream Data Register */
#define MSC0_UD1 /*lint --e(923)*/ (*(volatile Ifx_MSC_UD*)0xF0002634u)

/** \brief  38, Upstream Data Register */
#define MSC0_UD2 /*lint --e(923)*/ (*(volatile Ifx_MSC_UD*)0xF0002638u)

/** \brief  3C, Upstream Data Register */
#define MSC0_UD3 /*lint --e(923)*/ (*(volatile Ifx_MSC_UD*)0xF000263Cu)

/** \brief  5C, Upstream Control Enhanced Register 1 */
#define MSC0_USCE /*lint --e(923)*/ (*(volatile Ifx_MSC_USCE*)0xF000265Cu)

/** \brief  10, Upstream Status Register */
#define MSC0_USR /*lint --e(923)*/ (*(volatile Ifx_MSC_USR*)0xF0002610u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Msc_Cfg_Msc1
 * \{  */

/** \brief  80, Asynchronous Block Configuration Register */
#define MSC1_ABC /*lint --e(923)*/ (*(volatile Ifx_MSC_ABC*)0xF0002780u)

/** \brief  FC, Access Enable Register 0 */
#define MSC1_ACCEN0 /*lint --e(923)*/ (*(volatile Ifx_MSC_ACCEN0*)0xF00027FCu)

/** \brief  F8, Access Enable Register 1 */
#define MSC1_ACCEN1 /*lint --e(923)*/ (*(volatile Ifx_MSC_ACCEN1*)0xF00027F8u)

/** \brief  0, Clock Control Register */
#define MSC1_CLC /*lint --e(923)*/ (*(volatile Ifx_MSC_CLC*)0xF0002700u)

/** \brief  20, Downstream Command Register */
#define MSC1_DC /*lint --e(923)*/ (*(volatile Ifx_MSC_DC*)0xF0002720u)

/** \brief  1C, Downstream Data Register */
#define MSC1_DD /*lint --e(923)*/ (*(volatile Ifx_MSC_DD*)0xF000271Cu)

/** \brief  6C, Downstream Data Extension Register */
#define MSC1_DDE /*lint --e(923)*/ (*(volatile Ifx_MSC_DDE*)0xF000276Cu)

/** \brief  70, Downstream Data Mirror Register */
#define MSC1_DDM /*lint --e(923)*/ (*(volatile Ifx_MSC_DDM*)0xF0002770u)

/** \brief  14, Downstream Control Register */
#define MSC1_DSC /*lint --e(923)*/ (*(volatile Ifx_MSC_DSC*)0xF0002714u)

/** \brief  58, Downstream Control Enhanced Register 1 */
#define MSC1_DSCE /*lint --e(923)*/ (*(volatile Ifx_MSC_DSCE*)0xF0002758u)

/** \brief  28, Downstream Select Data Source High Register */
#define MSC1_DSDSH /*lint --e(923)*/ (*(volatile Ifx_MSC_DSDSH*)0xF0002728u)

/** \brief  64, Downstream Select Data Source High Register */
#define MSC1_DSDSHE /*lint --e(923)*/ (*(volatile Ifx_MSC_DSDSHE*)0xF0002764u)

/** \brief  24, Downstream Select Data Source Low Register */
#define MSC1_DSDSL /*lint --e(923)*/ (*(volatile Ifx_MSC_DSDSL*)0xF0002724u)

/** \brief  60, Downstream Select Data Source Low Extension Register */
#define MSC1_DSDSLE /*lint --e(923)*/ (*(volatile Ifx_MSC_DSDSLE*)0xF0002760u)

/** \brief  18, Downstream Status Register */
#define MSC1_DSS /*lint --e(923)*/ (*(volatile Ifx_MSC_DSS*)0xF0002718u)

/** \brief  74, Downstream Timing Extension Register */
#define MSC1_DSTE /*lint --e(923)*/ (*(volatile Ifx_MSC_DSTE*)0xF0002774u)

/** \brief  2C, Emergency Stop Register */
#define MSC1_ESR /*lint --e(923)*/ (*(volatile Ifx_MSC_ESR*)0xF000272Cu)

/** \brief  68, Emergency Stop Extension Register */
#define MSC1_ESRE /*lint --e(923)*/ (*(volatile Ifx_MSC_ESRE*)0xF0002768u)

/** \brief  C, Fractional Divider Register */
#define MSC1_FDR /*lint --e(923)*/ (*(volatile Ifx_MSC_FDR*)0xF000270Cu)

/** \brief  40, Interrupt Control Register */
#define MSC1_ICR /*lint --e(923)*/ (*(volatile Ifx_MSC_ICR*)0xF0002740u)

/** \brief  8, Module Identification Register */
#define MSC1_ID /*lint --e(923)*/ (*(volatile Ifx_MSC_ID*)0xF0002708u)

/** \brief  48, Interrupt Set Clear Register */
#define MSC1_ISC /*lint --e(923)*/ (*(volatile Ifx_MSC_ISC*)0xF0002748u)

/** \brief  44, Interrupt Status Register */
#define MSC1_ISR /*lint --e(923)*/ (*(volatile Ifx_MSC_ISR*)0xF0002744u)

/** \brief  F4, Kernel Reset Register 0 */
#define MSC1_KRST0 /*lint --e(923)*/ (*(volatile Ifx_MSC_KRST0*)0xF00027F4u)

/** \brief  F0, Kernel Reset Register 1 */
#define MSC1_KRST1 /*lint --e(923)*/ (*(volatile Ifx_MSC_KRST1*)0xF00027F0u)

/** \brief  EC, Kernel Reset Status Clear Register */
#define MSC1_KRSTCLR /*lint --e(923)*/ (*(volatile Ifx_MSC_KRSTCLR*)0xF00027ECu)

/** \brief  4C, Output Control Register */
#define MSC1_OCR /*lint --e(923)*/ (*(volatile Ifx_MSC_OCR*)0xF000274Cu)

/** \brief  E8, OCDS Control and Status */
#define MSC1_OCS /*lint --e(923)*/ (*(volatile Ifx_MSC_OCS*)0xF00027E8u)

/** \brief  30, Upstream Data Register */
#define MSC1_UD0 /*lint --e(923)*/ (*(volatile Ifx_MSC_UD*)0xF0002730u)

/** \brief  34, Upstream Data Register */
#define MSC1_UD1 /*lint --e(923)*/ (*(volatile Ifx_MSC_UD*)0xF0002734u)

/** \brief  38, Upstream Data Register */
#define MSC1_UD2 /*lint --e(923)*/ (*(volatile Ifx_MSC_UD*)0xF0002738u)

/** \brief  3C, Upstream Data Register */
#define MSC1_UD3 /*lint --e(923)*/ (*(volatile Ifx_MSC_UD*)0xF000273Cu)

/** \brief  5C, Upstream Control Enhanced Register 1 */
#define MSC1_USCE /*lint --e(923)*/ (*(volatile Ifx_MSC_USCE*)0xF000275Cu)

/** \brief  10, Upstream Status Register */
#define MSC1_USR /*lint --e(923)*/ (*(volatile Ifx_MSC_USR*)0xF0002710u)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXMSC_REG_H */
