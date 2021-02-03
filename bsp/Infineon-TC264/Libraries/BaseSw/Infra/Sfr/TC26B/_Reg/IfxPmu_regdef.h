/**
 * \file IfxPmu_regdef.h
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
 * \defgroup IfxLld_Pmu Pmu
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Pmu_Bitfields Bitfields
 * \ingroup IfxLld_Pmu
 * 
 * \defgroup IfxLld_Pmu_union Union
 * \ingroup IfxLld_Pmu
 * 
 * \defgroup IfxLld_Pmu_struct Struct
 * \ingroup IfxLld_Pmu
 * 
 */
#ifndef IFXPMU_REGDEF_H
#define IFXPMU_REGDEF_H 1
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Pmu_Bitfields
 * \{  */

/** \brief  PMU0 Identification Register */
typedef struct _Ifx_PMU_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_PMU_ID_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Pmu_union
 * \{  */

/** \brief  PMU0 Identification Register */
typedef union
{
    unsigned int U;                         /**< \brief Unsigned access */
    signed int I;                           /**< \brief Signed access */
    Ifx_PMU_ID_Bits B;                      /**< \brief Bitfield access */
} Ifx_PMU_ID;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Pmu_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \brief  PMU object */
typedef volatile struct _Ifx_PMU
{
    unsigned char reserved_0[8];            /**< \brief 0, \internal Reserved */
    Ifx_PMU_ID ID;                          /**< \brief 8, PMU0 Identification Register */
    unsigned char reserved_C[245];          /**< \brief C, \internal Reserved */
} Ifx_PMU;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXPMU_REGDEF_H */
