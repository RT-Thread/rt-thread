 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
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
 */

/******************************************************************************
 * @file     drv/sasc.h
 * @brief    Header File for SASC driver
 * @version  V1.0
 * @date     02. June 2020
 * @model    sasc
 ******************************************************************************/
#ifndef _DRV_SASC_H_
#define _DRV_SASC_H_


#include <stdint.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
    SASC_RW = 0,
    SASC_RO = 1,
    SASC_WO = 2,
    SASC_AP_DENY = 3
} csi_sasc_ap_t;

typedef enum {
    SASC_DI = 0,
    SASC_DO = 1,
    SASC_IO = 2,
    SASC_DI_DENY = 3
} csi_sasc_di_t;

typedef enum {
    SASC_RAM_4B = 5,
    SASC_RAM_8B = 6,
    SASC_RAM_16B = 7,
    SASC_RAM_32B = 8,
    SASC_RAM_64B = 9,
    SASC_RAM_128B = 10,
    SASC_RAM_256B = 11,
    SASC_RAM_512B = 12,
    SASC_RAM_1KB = 13,
    SASC_RAM_2KB = 14,
    SASC_RAM_4KB = 15,
    SASC_RAM_8KB = 16,
    SASC_RAM_16KB = 17,
    SASC_RAM_32KB = 18,
    SASC_RAM_64KB = 19,
    SASC_RAM_128KB = 20,
} csi_sasc_ram_size_t;

typedef enum {
    SASC_FLASH_1S = 0,
    SASC_FLASH_2S,
    SASC_FLASH_4S,
    SASC_FLASH_8S,
    SASC_FLASH_16S,
    SASC_FLASH_32S,
    SASC_FLASH_64S,
    SASC_FLASH_128S,
    SASC_FLASH_256S,
    SASC_FLASH_512S,
    SASC_FLASH_1024S,
    SASC_FLASH_2048S
} csi_sasc_flash_size_t;

typedef struct {
    csi_sasc_ap_t   super_ap;
    csi_sasc_ap_t   user_ap;
    csi_sasc_di_t   super_di;
    csi_sasc_di_t   user_di;
    bool            is_secure;
} csi_sasc_attr_t;

/**
  \brief       Config the sasc ram region attribute.
  \param[in]   region_id  Config region index
  \param[in]   base_addr  Config region base address.
  \param[in]   size  config region size.
  \param[in]   attr  Region attr.
  \return      Error code
*/
csi_error_t csi_sasc_ram_config(uint8_t region_id, uint32_t base_addr, csi_sasc_ram_size_t size, csi_sasc_attr_t attr);

/**
  \brief       Config the sasc flash region attribute.
  \param[in]   region_id  Config region index
  \param[in]   base_addr  Config region base address.
  \param[in]   size  Config region size.
  \param[in]   attr  Region attr.
  \return      Error code
*/
csi_error_t csi_sasc_flash_config(uint8_t region_id, uint32_t base_addr, csi_sasc_flash_size_t size, csi_sasc_attr_t attr);

/**
  \brief       Enable sasc ram config.
  \param[in]   region_id  Region index
  \return      error code
*/
csi_error_t csi_sasc_ram_enable(uint8_t region_id);

/**
  \brief       Enable sasc flash config
  \param[in]   region_id  Config region index
  \return      error code
*/
csi_error_t csi_sasc_flash_enable(uint8_t region_id);

/**
  \brief       Disable sasc ram config.
  \param[in]   region_id  Region index
  \return      error code
*/
csi_error_t csi_sasc_ram_disable(uint8_t region_id);

/**
  \brief       Disable sasc flash config
  \param[in]   region_id  Region index
  \return      error code
*/
csi_error_t csi_sasc_flash_disable(uint8_t region_id);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_SASC_H_ */
