/***************************************************************************//**
* \file cy_syspm_ppu.h
* \version 5.91
*
* This file provides header for ARM PPU Power Domain Platform Dependant
* specific driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2021 Cypress Semiconductor Corporation
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
* \addtogroup group_syspm_ppu              PPU (Power Policy Unit)
* \{
* Power Domain PPU driver is a platform dependent driver on top of ARM PPU Driver
*
* The functions and other declarations used in this driver are in cy_syspm_ppu.h.
*
* \note  PD PPU API's are used by the Syspm driver and BTSS API's, there is no
* need to call them directly in Application code.
*
* You can use this driver to implement the platform dependent code to
* control power domain using PPU.
*
* \section group_syspm_ppu_more_information More Information
*
* For more information on the PD PPU, refer to
* the technical reference manual (TRM).
*
* \section group_syspm_ppu_MISRA MISRA-C Compliance
* The PD PPU driver does not has any specific deviations.
*
* \section group_syspm_ppu_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_syspm_ppu_macros Macros
* \defgroup group_syspm_ppu_functions Functions
* \defgroup group_syspm_ppu_data_structures Data Structures
* \defgroup group_syspm_ppu_enums Enumerated Types
*/


#ifndef CY_PD_PPU_H
#define CY_PD_PPU_H

#include "cy_device.h"

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS)

#include <stdint.h>
#include "ppu_v1.h"
#include "cy_syspm.h"


/**
* \addtogroup group_syspm_ppu_macros
* \{
*/

/** Driver major version */
#define CY_PD_PPU_DRV_VERSION_MAJOR       5
/** Driver minor version */
#define CY_PD_PPU_DRV_VERSION_MINOR       91

/** PPU Device Sleep Deny Status Mask */
#define CY_PD_PPU_DEVDENY_STATUS_MASK    (0x00000001U)

/** \} group_syspm_ppu_macros */

/**
* \addtogroup group_syspm_ppu_enums
* \{
*/

/** Defines the Device interface channels for all the PPU's */
typedef enum
{
    CY_PD_PPU_DEVICE_0            = (CY_PD_PPU_DEVDENY_STATUS_MASK),         /**< Device 0 */
    CY_PD_PPU_DEVICE_1            = (CY_PD_PPU_DEVDENY_STATUS_MASK << 0x1),  /**< Device 1 */
    CY_PD_PPU_DEVICE_2            = (CY_PD_PPU_DEVDENY_STATUS_MASK << 0x2),  /**< Device 2 */
    CY_PD_PPU_DEVICE_3            = (CY_PD_PPU_DEVDENY_STATUS_MASK << 0x3),  /**< Device 3 */
    CY_PD_PPU_DEVICE_4            = (CY_PD_PPU_DEVDENY_STATUS_MASK << 0x4),  /**< Device 4 */
    CY_PD_PPU_DEVICE_5            = (CY_PD_PPU_DEVDENY_STATUS_MASK << 0x5),  /**< Device 5 */
    CY_PD_PPU_DEVICE_6            = (CY_PD_PPU_DEVDENY_STATUS_MASK << 0x6),  /**< Device 6 */
    CY_PD_PPU_DEVICE_7            = (CY_PD_PPU_DEVDENY_STATUS_MASK << 0x7),  /**< Device 7 */
} cy_pd_ppu_device_status_t;

/** \} group_syspm_ppu_enums */

/**
* \addtogroup group_syspm_ppu_functions
* \{
*/
cy_en_syspm_status_t cy_pd_ppu_init(struct ppu_v1_reg *ppu);
enum ppu_v1_mode cy_pd_ppu_get_power_mode(struct ppu_v1_reg *ppu);
enum ppu_v1_mode cy_pd_ppu_get_programmed_power_mode(struct ppu_v1_reg *ppu);
cy_en_syspm_status_t cy_pd_ppu_set_power_mode(struct ppu_v1_reg *ppu, uint32_t mode);
cy_en_syspm_status_t cy_pd_ppu_reset(struct ppu_v1_reg *ppu);
cy_pd_ppu_device_status_t cy_pd_ppu_get_ds_fail_device(struct ppu_v1_reg *ppu);

/** \} group_syspm_ppu_functions */

#endif /* CY_IP_MXS28SRSS, CY_IP_MXS40SSRSS */

#endif /* CY_PD_PPU_H */

/** \} group_syspm_ppu */


/* [] END OF FILE */
