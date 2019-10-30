/***************************************************************************//**
* \file cyip_efuse_data_psoc6_01.h
*
* \brief
* EFUSE_DATA IP definitions
*
* \note
* Generator version: 1.3.0.23
* Database revision: 8f38ca6
*
********************************************************************************
* \copyright
* Copyright 2016-2018, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
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
