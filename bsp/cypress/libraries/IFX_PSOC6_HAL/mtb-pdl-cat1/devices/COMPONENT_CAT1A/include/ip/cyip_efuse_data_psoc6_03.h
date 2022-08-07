/***************************************************************************//**
* \file cyip_efuse_data_psoc6_03.h
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

#ifndef _CYIP_EFUSE_DATA_PSOC6_03_H_
#define _CYIP_EFUSE_DATA_PSOC6_03_H_

#include "cyip_headers.h"

/**
  * \brief Access restrictions for DEAD life cycle stage (DEAD_ACCESS_RESTRICT0)
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
  * \brief Access restrictions for DEAD life cycle stage (DEAD_ACCESS_RESTRICT1)
  */
typedef struct {
    uint8_t FLASH_ALLOWED[3];
    uint8_t SRAM_ALLOWED[3];
    uint8_t UNUSED;
    uint8_t DIRECT_EXECUTE_DISABLE;
} cy_stc_dead_access_restrict1_t;

/**
  * \brief Access restrictions for SECURE life cycle stage (SECURE_ACCESS_RESTRICT0)
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
  * \brief Access restrictions for SECURE life cycle stage (SECURE_ACCESS_RESTRICT1)
  */
typedef struct {
    uint8_t FLASH_ALLOWED[3];
    uint8_t SRAM_ALLOWED[3];
    uint8_t UNUSED;
    uint8_t DIRECT_EXECUTE_DISABLE;
} cy_stc_secure_access_restrict1_t;

/**
  * \brief NORMAL, SECURE_WITH_DEBUG, SECURE, and RMA fuse bits (LIFECYCLE_STAGE)
  */
typedef struct {
    uint8_t NORMAL;
    uint8_t SECURE_WITH_DEBUG;
    uint8_t SECURE;
    uint8_t RMA;
    uint8_t RESERVED[4];
} cy_stc_lifecycle_stage_t;

/**
  * \brief Cypress asset hash byte 0 (CY_ASSET_HASH0)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash0_t;

/**
  * \brief Cypress asset hash byte 1 (CY_ASSET_HASH1)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash1_t;

/**
  * \brief Cypress asset hash byte 2 (CY_ASSET_HASH2)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash2_t;

/**
  * \brief Cypress asset hash byte 3 (CY_ASSET_HASH3)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash3_t;

/**
  * \brief Cypress asset hash byte 4 (CY_ASSET_HASH4)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash4_t;

/**
  * \brief Cypress asset hash byte 5 (CY_ASSET_HASH5)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash5_t;

/**
  * \brief Cypress asset hash byte 6 (CY_ASSET_HASH6)
  */
typedef struct {
    uint8_t CY_ASSET_HASH[8];
} cy_stc_cy_asset_hash6_t;

/**
  * \brief Cypress asset hash byte 7 (CY_ASSET_HASH7)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash7_t;

/**
  * \brief Cypress asset hash byte 8 (CY_ASSET_HASH8)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash8_t;

/**
  * \brief Cypress asset hash byte 9 (CY_ASSET_HASH9)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash9_t;

/**
  * \brief Cypress asset hash byte 10 (CY_ASSET_HASH10)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash10_t;

/**
  * \brief Cypress asset hash byte 11 (CY_ASSET_HASH11)
  */
typedef struct {
    uint8_t CY_ASSET_HASH[8];
} cy_stc_cy_asset_hash11_t;

/**
  * \brief Cypress asset hash byte 12 (CY_ASSET_HASH12)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash12_t;

/**
  * \brief Cypress asset hash byte 13 (CY_ASSET_HASH13)
  */
typedef struct {
    uint8_t CY_ASSET_HASH[8];
} cy_stc_cy_asset_hash13_t;

/**
  * \brief Cypress asset hash byte 14 (CY_ASSET_HASH14)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash14_t;

/**
  * \brief Cypress asset hash byte 15 (CY_ASSET_HASH15)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash15_t;

/**
  * \brief Number of zeros in Cypress asset hash (CY_ASSET_HASH_ZEROS)
  */
typedef struct {
    uint8_t HASH_BYTE[8];
} cy_stc_cy_asset_hash_zeros_t;

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
    cy_stc_cy_asset_hash0_t CY_ASSET_HASH0;
    cy_stc_cy_asset_hash1_t CY_ASSET_HASH1;
    cy_stc_cy_asset_hash2_t CY_ASSET_HASH2;
    cy_stc_cy_asset_hash3_t CY_ASSET_HASH3;
    cy_stc_cy_asset_hash4_t CY_ASSET_HASH4;
    cy_stc_cy_asset_hash5_t CY_ASSET_HASH5;
    cy_stc_cy_asset_hash6_t CY_ASSET_HASH6;
    cy_stc_cy_asset_hash7_t CY_ASSET_HASH7;
    cy_stc_cy_asset_hash8_t CY_ASSET_HASH8;
    cy_stc_cy_asset_hash9_t CY_ASSET_HASH9;
    cy_stc_cy_asset_hash10_t CY_ASSET_HASH10;
    cy_stc_cy_asset_hash11_t CY_ASSET_HASH11;
    cy_stc_cy_asset_hash12_t CY_ASSET_HASH12;
    cy_stc_cy_asset_hash13_t CY_ASSET_HASH13;
    cy_stc_cy_asset_hash14_t CY_ASSET_HASH14;
    cy_stc_cy_asset_hash15_t CY_ASSET_HASH15;
    cy_stc_cy_asset_hash_zeros_t CY_ASSET_HASH_ZEROS;
    cy_stc_customer_data_t CUSTOMER_DATA[47];
} cy_stc_efuse_data_t;


#endif /* _CYIP_EFUSE_DATA_PSOC6_03_H_ */


/* [] END OF FILE */
