/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     ck_eflash.c
 * @brief    CSI Source File for Embedded Flash Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include <stdio.h>
#include "drv_eflash.h"
#include "ck_eflash.h"


#define ERR_EFLASH(errno) (CSI_DRV_ERRNO_EFLASH_BASE | errno)
#define EFLASH_NULL_PARAM_CHK(para)                         \
        do {                                        \
            if (para == NULL) {                     \
                return ERR_EFLASH(EDRV_PARAMETER);   \
            }                                       \
        } while (0)

typedef struct {
    uint32_t base;
    eflash_info eflashinfo;
    eflash_event_cb_t cb;
    eflash_status_t status;
} ck_eflash_priv_t;

static ck_eflash_priv_t eflash_handle[CONFIG_EFLASH_NUM];
/* Driver Capabilities */
static const eflash_capabilities_t driver_capabilities = {
    .event_ready = 1, /* event_ready */
    .data_width = 2, /* data_width = 0:8-bit, 1:16-bit, 2:32-bit */
    .erase_chip = 0  /* erase_chip */
};

//
// Functions
//

static int32_t eflash_program_word(eflash_handle_t handle, uint32_t dstaddr, uint32_t *srcbuf, uint32_t len)
{
    ck_eflash_priv_t *eflash_priv = handle;
    uint32_t fbase = eflash_priv->base;
    uint32_t i;

    for (i = 0; i < len; i++) {
        *(volatile uint32_t *)(fbase + 0x04) = dstaddr;
        *(volatile uint32_t *)(fbase + 0x1c) = *srcbuf;
        *(volatile uint32_t *)(fbase + 0x18) = 1;
        srcbuf++;
        dstaddr += 4;
    }

    return (i << 2);
}

int32_t __attribute__((weak)) target_get_eflash_count(void)
{
    return 0;
}

int32_t __attribute__((weak)) target_get_eflash(int32_t idx, uint32_t *base, eflash_info *info)
{
    return NULL;
}
/**
  \brief       get eflash handle count.
  \return      eflash handle count
*/
int32_t csi_eflash_get_instance_count(void)
{
    return target_get_eflash_count();
}

/**
  \brief       Initialize EFLASH Interface. 1. Initializes the resources needed for the EFLASH interface 2.registers event callback function
  \param[in]   idx  must not exceed return value of csi_eflash_get_instance_count()
  \param[in]   cb_event  Pointer to \ref eflash_event_cb_t
  \return      pointer to eflash handle
*/
eflash_handle_t csi_eflash_initialize(int32_t idx, eflash_event_cb_t cb_event)
{
    if (idx < 0 || idx >= CONFIG_EFLASH_NUM) {
        return NULL;
    }

    /* obtain the eflash information */
    uint32_t base = 0u;
    eflash_info info;
    int32_t real_idx = target_get_eflash(idx, &base, &info);

    if (real_idx != idx) {
        return NULL;
    }

    ck_eflash_priv_t *eflash_priv = &eflash_handle[idx];

    eflash_priv->base = base;
    eflash_priv->eflashinfo.start = info.start;
    eflash_priv->eflashinfo.end = info.end;
    eflash_priv->eflashinfo.sector_count = info.sector_count;

    /* initialize the eflash context */
    eflash_priv->cb = cb_event;
    eflash_priv->status.busy = 0;
    eflash_priv->status.error = 0U;
    eflash_priv->eflashinfo.sector_size = EFLASH_SECTOR_SIZE;
    eflash_priv->eflashinfo.page_size = EFLASH_PAGE_SIZE;
    eflash_priv->eflashinfo.program_unit = EFLASH_PROGRAM_UINT;
    eflash_priv->eflashinfo.erased_value = EFLASH_ERASED_VALUE;

    return (eflash_handle_t)eflash_priv;
}

/**
  \brief       De-initialize EFLASH Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  eflash handle to operate.
  \return      error code
*/
int32_t csi_eflash_uninitialize(eflash_handle_t handle)
{
    EFLASH_NULL_PARAM_CHK(handle);

    ck_eflash_priv_t *eflash_priv = handle;
    eflash_priv->cb = NULL;

    return 0;
}

/**
  \brief       Get driver capabilities.
  \param[in]   eflash handle to operate.
  \return      \ref eflash_capabilities_t
*/
eflash_capabilities_t csi_eflash_get_capabilities(eflash_handle_t handle)
{
    return driver_capabilities;
}

/**
  \brief       Read data from Flash.
  \param[in]   handle  eflash handle to operate.
  \param[in]   addr  Data address.
  \param[out]  data  Pointer to a buffer storing the data read from Flash.
  \param[in]   cnt   Number of data items to read.
  \return      number of data items read or error code
*/
int32_t csi_eflash_read(eflash_handle_t handle, uint32_t addr, void *data, uint32_t cnt)
{
    EFLASH_NULL_PARAM_CHK(handle);
    EFLASH_NULL_PARAM_CHK(data);
    EFLASH_NULL_PARAM_CHK(cnt);
    if (!IS_EFLASH_ADDR(addr) || !(IS_EFLASH_ADDR(addr + cnt -1))) {
        return ERR_EFLASH(EDRV_PARAMETER);
    }

    volatile uint8_t *src_addr = (uint8_t *)addr;
    ck_eflash_priv_t *eflash_priv = handle;

    if (eflash_priv->status.busy) {
        return ERR_EFLASH(EDRV_BUSY);
    }

    eflash_priv->status.error = 0U;

    int i;
    for (i = 0; i < cnt; i++) {
        *((uint8_t *)data + i) = *(src_addr + i);
    }

    return i;
}

/**
  \brief       Program data to Flash.
  \param[in]   handle  eflash handle to operate.
  \param[in]   addr  Data address.
  \param[in]   data  Pointer to a buffer containing the data to be programmed to Flash..
  \param[in]   cnt   Number of data items to program.
  \return      number of data items programmed or error code
*/
int32_t csi_eflash_program(eflash_handle_t handle, uint32_t addr, const void *data, uint32_t cnt)
{
    EFLASH_NULL_PARAM_CHK(handle);
    EFLASH_NULL_PARAM_CHK(data);
    EFLASH_NULL_PARAM_CHK(cnt);
    if (!IS_EFLASH_ADDR(addr) || !(IS_EFLASH_ADDR(addr + cnt -1))) {
        return ERR_EFLASH(EDRV_PARAMETER);
    }

    ck_eflash_priv_t *eflash_priv = handle;

    if ((addr & 0x3) || ((uint32_t)data & 0x3) || (cnt & 0x3)) {
        return ERR_EFLASH(EDRV_PARAMETER);
    }

    if (eflash_priv->status.busy) {
        return ERR_EFLASH(EDRV_BUSY);
    }

    eflash_priv->status.busy = 1U;
    eflash_priv->status.error = 0U;
    uint32_t ret = eflash_program_word(handle, addr, (uint32_t *)data, cnt >> 2);
    eflash_priv->status.busy = 0U;

    return ret;
}

/**
  \brief       Erase Flash Sector.
  \param[in]   handle  eflash handle to operate.
  \param[in]   addr  Sector address
  \return      error code
*/
int32_t csi_eflash_erase_sector(eflash_handle_t handle, uint32_t addr)
{
    EFLASH_NULL_PARAM_CHK(handle);
    if (!IS_EFLASH_ADDR(addr)) {
        return ERR_EFLASH(EDRV_PARAMETER);
    }

    addr = addr & ~(EFLASH_SECTOR_SIZE - 1);
    ck_eflash_priv_t *eflash_priv = handle;
    uint32_t fbase = eflash_priv->base;

    if (eflash_priv->status.busy) {
        return ERR_EFLASH(EDRV_BUSY);
    }

    eflash_priv->status.busy = 1U;
    eflash_priv->status.error = 0U;
    *(volatile uint32_t *)(fbase + 0x4) = addr;
    *(volatile uint32_t *)(fbase + 0x10) = 0x1;
    eflash_priv->status.busy = 0U;

    return 0;
}

/**
  \brief       Erase complete Flash.
  \param[in]   handle  eflash handle to operate.
  \return      error code
*/
int32_t csi_eflash_erase_chip(eflash_handle_t handle)
{
    EFLASH_NULL_PARAM_CHK(handle);

    return ERR_EFLASH(EDRV_UNSUPPORTED);
}

/**
  \brief       Get Flash information.
  \param[in]   handle  eflash handle to operate.
  \return      Pointer to Flash information \ref eflash_info
*/
eflash_info *csi_eflash_get_info(eflash_handle_t handle)
{
    ck_eflash_priv_t *eflash_priv = handle;
    eflash_info *eflash_info = &(eflash_priv->eflashinfo);

    return eflash_info;
}

/**
  \brief       Get EFLASH status.
  \param[in]   handle  eflash handle to operate.
  \return      EFLASH status \ref eflash_status_t
*/
eflash_status_t csi_eflash_get_status(eflash_handle_t handle)
{
    ck_eflash_priv_t *eflash_priv = handle;

    return eflash_priv->status;
}
