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
 * @file     eflash.h
 * @brief    header file for eflash driver
 * @version  V1.0
 * @date     02. June 2017
 * @model    eflash
 ******************************************************************************/
#ifndef _DRV_EFLASH_H_
#define _DRV_EFLASH_H_

#include <stdint.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
\brief Flash information
*/
typedef struct {
    uint32_t          flash_size;         ///< Chip End address (start+size-1)
    uint32_t          sector_size;        ///< Uniform sector size in bytes
    uint32_t          erased_value;       ///< erased value
} csi_eflash_info_t;

/**
\brief Flash Status
*/
typedef struct {
    uint32_t busy  : 1;                   ///< Flash busy flag
    uint32_t error : 1;                   ///< Read/Program/Erase error flag (cleared on start of next operation)
} eflash_status_t;

/// definition for eflash handle.
typedef struct {
    csi_dev_t           dev;
    void                *arg;
    csi_eflash_info_t   eflashinfo;
    uint16_t            prog;
    uint16_t            erase;
    void                *priv;
} csi_eflash_t;

// Function documentation

/**
  \brief       Initialize EFLASH Interface. 1. Initializes the resources needed for the EFLASH interface 2.registers event callback function
  \param[in]   eflash  eflash handle to operate.
  \param[in]   idx  device id
  \param[in]   arg  User can define it by himself as callback's param
  \return      error code
*/
csi_error_t csi_eflash_init(csi_eflash_t *eflash, int32_t idx, void *arg);

/**
  \brief       De-initialize EFLASH Interface. stops operation and releases the software resources used by the interface
  \param[in]   eflash  eflash handle to operate.
  \return      error code
*/
csi_error_t csi_eflash_uninit(csi_eflash_t *eflash);

/**
  \brief       Read data from Flash.
  \param[in]   eflash  eflash handle to operate.
  \param[in]   offset  Data address.
  \param[out]  data  Pointer to a buffer storing the data read from Flash.
  \param[in]   size   Number of data items to read.
  \return      error code
*/
csi_error_t csi_eflash_read(csi_eflash_t *eflash, uint32_t offset, void *data, uint32_t size);

/**
  \brief       Program data to Flash.
  \param[in]   eflash  eflash handle to operate.
  \param[in]   offset  Data address.
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash.
  \param[in]   size   Number of data items to program.
  \return      error code
*/
csi_error_t csi_eflash_program(csi_eflash_t *eflash, uint32_t offset, const void *data, uint32_t size);

/**
  \brief       Erase Flash Sector.
  \param[in]   eflash  eflash handle to operate.
  \param[in]   offset  flash address, flash address need sector size aligned
  \param[in]   size  erase size
  \return      error code
*/
csi_error_t csi_eflash_erase(csi_eflash_t *eflash, uint32_t offset,uint32_t size);

/**
  \brief       Erase whole flash
  \param[in]   eflash  eflash handle to operate.
  \return      error code
*/
csi_error_t csi_eflash_erase_chip(csi_eflash_t *eflash);

/**
  \brief       Get Flash information.
  \param[in]   eflash  eflash handle to operate.
*/
void csi_eflash_dev_info(csi_eflash_t *eflash,csi_eflash_info_t *eflash_info);

/**
  \brief       enable eflash power manage
  \param[in]   eflash  eflash handle to operate.
  \return      error code
*/
csi_error_t csi_eflash_enable_pm(csi_eflash_t *eflash);

/**
  \brief       disable eflash power manage
  \param[in]   eflash  eflash handle to operate.
*/
void csi_eflash_disable_pm(csi_eflash_t *eflash);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_EFLASH_H_ */
