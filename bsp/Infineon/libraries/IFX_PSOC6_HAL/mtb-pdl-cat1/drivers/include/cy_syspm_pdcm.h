/***************************************************************************//**
* \file cy_syspm_pdcm.h
* \version 5.91
*
* This file provides the header for PDCM driver, where the APIs are used
* by Syspm driver and BTSS driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_syspm_pdcm             PDCM (Power Dependency Control Matrix)
* \{
* PDCM driver provides APIs for controlling the Power Dependency Control Matrix
* across Power Domains
*
* The functions and other declarations used in this driver are in cy_syspm_pdcm.h.
*
* \section group_syspm_pdcm_more_information More Information
*
* For more information on the PDCM, refer to
* the technical reference manual (TRM).
*
* \section group_syspm_pdcm_MISRA MISRA-C Compliance
* The PDCM driver does not have any specific deviations.
*
* \section group_syspm_pdcm_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_syspm_pdcm_macros Macros
* \defgroup group_syspm_pdcm_functions Functions
* \defgroup group_syspm_pdcm_data_structures Data Structures
* \defgroup group_syspm_pdcm_enums Enumerated Types
*/
/** \} group_syspm_pdcm */

#ifndef CY_PD_PDCM_H
#define CY_PD_PDCM_H

#include "cy_device.h"

#if defined (CY_IP_MXS40SSRSS)

#include <stdint.h>
#include "cy_syslib.h"
#include "cy_syspm.h"

/*******************************************************************************
*       Enumerated Types
*******************************************************************************/

/**
* \addtogroup group_syspm_pdcm_enums
* \{
*/

/** Defines ID's for each of the PDCM's */
typedef enum
{
    CY_PD_PDCM_MAIN      = 0x00UL, /**< For MAIN Power domain */
    CY_PD_PDCM_CPUSS     = 0x01UL, /**< For CPUSS Power domain */
    CY_PD_PDCM_SRAM      = 0x02UL, /**< For SRAM Power domain */
    CY_PD_PDCM_BTSS      = 0x03UL, /**< For BTSS Power domain */
} cy_pd_pdcm_id_t;

/** Defines Dependency Matrix for PD's */
typedef enum
{
    CY_PD_PDCM_DEP_NONE         = 0x00UL, /**< No Direct Dependency */
    CY_PD_PDCM_DEP_DIRECT       = 0x01UL, /**< Direct Dependency */
    CY_PD_PDCM_DEP_CONFIG       = 0x02UL, /**< Configurable Dependency */
} cy_pd_pdcm_dep_t;

/** \} group_syspm_pdcm_enums */

/**
* \addtogroup group_syspm_pdcm_macros
* \{
*/

/** Driver major version */
#define CY_PD_PDCM_DRV_VERSION_MAJOR       5
/** Driver minor version */
#define CY_PD_PDCM_DRV_VERSION_MINOR       91

/** Macro to validate the SDR number in Cy_Syspm_LdoSdrConfigure() function */
#define CY_SYSPM_IS_PDCM_ID_VALID(id)    (((id) == CY_PD_PDCM_MAIN)     || \
                                           ((id) == CY_PD_PDCM_SRAM)   || \
                                           ((id) == CY_PD_PDCM_CPUSS)   || \
                                           ((id) == CY_PD_PDCM_BTSS))
/** \} group_syspm_pdcm_macros */

/**
* \addtogroup group_syspm_pdcm_functions
* \{
*/
cy_pd_pdcm_dep_t cy_pd_pdcm_get_dependency(cy_pd_pdcm_id_t host_pd,cy_pd_pdcm_id_t dest_pd);
cy_en_syspm_status_t cy_pd_pdcm_set_dependency(cy_pd_pdcm_id_t host_pd,cy_pd_pdcm_id_t dest_pd);
cy_en_syspm_status_t cy_pd_pdcm_clear_dependency(cy_pd_pdcm_id_t host_pd,cy_pd_pdcm_id_t dest_pd);
/** \} group_syspm_pdcm_functions */

#endif /* CY_IP_MXS40SSRSS */

#endif /* CY_PD_PDCM_H */
