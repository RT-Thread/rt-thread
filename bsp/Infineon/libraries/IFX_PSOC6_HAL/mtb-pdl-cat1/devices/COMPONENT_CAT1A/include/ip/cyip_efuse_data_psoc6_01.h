/***************************************************************************//**
* \file cyip_efuse_data_psoc6_01.h
*
* \brief
* EFUSE_DATA IP definitions
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
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

#ifndef _CYIP_EFUSE_DATA_PSOC6_01_H_
#define _CYIP_EFUSE_DATA_PSOC6_01_H_

#include "cyip_headers.h"

/**
  * \brief DEAD access restrictions (DEAD_ACCESS_RESTRICT0)
  */
typedef struct {
    uint8_t CM0_DISABLE;
    uint8_t CM4_DISABLE;
    uint8_t SYS_DISABLE;
    uint8_t SYS_AP_MPU_ENABLE;
    uint8_t SFLASH_ALLOWED[2];
    uint8_t MMIO_ALLOWED[2];
} cy_stc_dead_access_restrict0_t;

/**
  * \brief DEAD access restrictions (DEAD_ACCESS_RESTRICT1)
  */
typedef struct {
    uint8_t FLASH_ALLOWED[3];
    uint8_t SRAM_ALLOWED[3];
    uint8_t UNUSED;
    uint8_t DIRECT_EXECUTE_DISABLE;
} cy_stc_dead_access_restrict1_t;

/**
  * \brief SECURE access restrictions (SECURE_ACCESS_RESTRICT0)
  */
typedef struct {
    uint8_t CM0_DISABLE;
    uint8_t CM4_DISABLE;
    uint8_t SYS_DISABLE;
    uint8_t SYS_AP_MPU_ENABLE;
    uint8_t SFLASH_ALLOWED[2];
    uint8_t MMIO_ALLOWED[2];
} cy_stc_secure_access_restrict0_t;

/**
  * \brief SECURE access restrictions (SECURE_ACCESS_RESTRICT1)
  */
typedef struct {
    uint8_t FLASH_ALLOWED[3];
    uint8_t SRAM_ALLOWED[3];
    uint8_t SMIF_XIP_ALLOWED;
    uint8_t DIRECT_EXECUTE_DISABLE;
} cy_stc_secure_access_restrict1_t;

/**
  * \brief NORMAL, SECURE_WITH_DEBUG, and SECURE fuse bits (LIFECYCLE_STAGE)
  */
typedef struct {
    uint8_t NORMAL;
    uint8_t SECURE_WITH_DEBUG;
    uint8_t SECURE;
    uint8_t RMA;
    uint8_t RESERVED[4];
} cy_stc_lifecycle_stage_t;

/**
  * \brief Customer data (CUSTOMER_DATA)
  */
typedef struct {
    uint8_t CUSTOMER_USE[8];
} cy_stc_customer_data_t;


/**
  * \brief eFUSE memory (EFUSE_DATA)
  */
typedef struct {
    uint8_t RESERVED[312];
    cy_stc_dead_access_restrict0_t DEAD_ACCESS_RESTRICT0;
    cy_stc_dead_access_restrict1_t DEAD_ACCESS_RESTRICT1;
    cy_stc_secure_access_restrict0_t SECURE_ACCESS_RESTRICT0;
    cy_stc_secure_access_restrict1_t SECURE_ACCESS_RESTRICT1;
    cy_stc_lifecycle_stage_t LIFECYCLE_STAGE;
    uint8_t RESERVED1[160];
    cy_stc_customer_data_t CUSTOMER_DATA[64];
} cy_stc_efuse_data_t;


#endif /* _CYIP_EFUSE_DATA_PSOC6_01_H_ */


/* [] END OF FILE */
