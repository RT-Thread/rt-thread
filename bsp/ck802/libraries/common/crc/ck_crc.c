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
 * @file     ck_crc.c
 * @brief    CSI Source File for CRC Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include <stdio.h>
#include "drv_crc.h"
#include "ck_crc.h"

#define ERR_CRC(errno) (CSI_DRV_ERRNO_CRC_BASE | errno)
#define CRC_NULL_PARAM_CHK(para)                         \
        do {                                        \
            if (para == NULL) {                     \
                return ERR_CRC(EDRV_PARAMETER);   \
            }                                       \
        } while (0)

typedef struct {
    uint32_t base;
    crc_event_cb_t cb;
    crc_status_t status;
} ck_crc_priv_t;


static ck_crc_priv_t crc_handle[CONFIG_CRC_NUM];
/* Driver Capabilities */
static const crc_capabilities_t driver_capabilities = {
    .ROHC = 1, /* ROHC mode */
    .MAXIM = 1, /* MAXIM mode */
    .X25 = 1, /* X25 mode */
    .CCITT = 1, /* CCITT mode */
    .USB = 1, /* USB mode */
    .IBM = 1, /* IBM mode */
    .MODBUS = 1  /* MODBUS mode */
};

//
// Functions
//

static ck_crc_reg_t *crc_reg = NULL;

static int32_t crc_set_mode(crc_mode_e mode, crc_standard_crc_e standard)
{
    if (mode == CRC_MODE_CRC16) {
        switch (standard) {
            case CRC_STANDARD_CRC_MODBUS:
                crc_reg->CRC_SEL = 0x0;
                crc_reg->CRC_INIT = 0xffff;
                break;

            case CRC_STANDARD_CRC_IBM:
                crc_reg->CRC_SEL = 0x0;
                crc_reg->CRC_INIT = 0x0;
                break;

            case CRC_STANDARD_CRC_MAXIM:
                crc_reg->CRC_SEL = 0x4;
                crc_reg->CRC_INIT = 0x0;
                break;

            case CRC_STANDARD_CRC_USB:
                crc_reg->CRC_SEL = 0x4;
                crc_reg->CRC_INIT = 0xffff;
                break;

            case CRC_STANDARD_CRC_CCITT:
                crc_reg->CRC_SEL = 0x1;
                crc_reg->CRC_INIT = 0x0;
                break;

            case CRC_STANDARD_CRC_X25:
                crc_reg->CRC_SEL = 0x5;
                crc_reg->CRC_INIT = 0xffff;
                break;

            default:
                return ERR_CRC(EDRV_PARAMETER);
        }
    } else if (mode == CRC_MODE_CRC8) {
        switch (standard) {
            case CRC_STANDARD_CRC_MAXIM:
                crc_reg->CRC_SEL = 0x2;
                crc_reg->CRC_INIT = 0x0;
                break;

            case CRC_STANDARD_CRC_ROHC:
                crc_reg->CRC_SEL = 0x3;
                crc_reg->CRC_INIT = 0xff;
                break;

            default:
                return ERR_CRC(EDRV_PARAMETER);
        }
    } else {
        return ERR_CRC(EDRV_PARAMETER);
    }

    return 0;
}

static int32_t crc_set_data(uint32_t data)
{
    crc_reg->CRC_DATA = data;
    return 0;
}

static int32_t crc_get_data(uint32_t *data)
{
    *data = crc_reg->CRC_DATA;
    return 0;
}

int32_t __attribute__((weak)) target_get_crc_count(void)
{
    return 0;
}

int32_t __attribute__((weak)) target_get_crc(int32_t idx, uint32_t *base)
{
    return NULL;
}

/**
  \brief       get crc handle count.
  \return      crc handle count
*/
int32_t csi_crc_get_instance_count(void)
{
    return target_get_crc_count();
}

/**
  \brief       Initialize CRC Interface. 1. Initializes the resources needed for the CRC interface 2.registers event callback function
  \param[in]   idx must not exceed return value of csi_crc_get_handle_count()
  \param[in]   cb_event  Pointer to \ref crc_event_cb_t
  \return      return crc handle if success
*/
crc_handle_t csi_crc_initialize(int32_t idx, crc_event_cb_t cb_event)
{
    if (idx < 0 || idx >= CONFIG_CRC_NUM) {
        return NULL;
    }

    /* obtain the crc information */
    uint32_t base = 0u;
    int32_t real_idx = target_get_crc(idx, &base);

    if (real_idx != idx) {
        return NULL;
    }

    ck_crc_priv_t *crc_priv = &crc_handle[idx];
    crc_reg = (ck_crc_reg_t *)(crc_priv->base);

    crc_priv->base = base;
    crc_priv->cb = cb_event;
    crc_priv->status.busy = 0;

    return (crc_handle_t)crc_priv;
}

/**
  \brief       De-initialize CRC Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  crc handle to operate.
  \return      error code
*/
int32_t csi_crc_uninitialize(crc_handle_t handle)
{
    CRC_NULL_PARAM_CHK(handle);

    ck_crc_priv_t *crc_priv = handle;
    crc_priv->cb = NULL;

    return 0;
}

/**
  \brief       Get driver capabilities.
  \param[in]   handle crc handle to operate.
  \return      \ref crc_capabilities_t
*/
crc_capabilities_t csi_crc_get_capabilities(crc_handle_t handle)
{
    return driver_capabilities;
}

/**
  \brief       config crc mode.
  \param[in]   handle  crc handle to operate.
  \param[in]   mode      \ref crc_mode_e
  \param[in]   standard  \ref crc_standard_crc_e
  \return      error code
*/
int32_t csi_crc_config(crc_handle_t handle, crc_mode_e mode, crc_standard_crc_e standard)
{
    CRC_NULL_PARAM_CHK(handle);

    /* set the crc mode */
    uint32_t ret = crc_set_mode(mode, standard);

    return ret;
}

/**
  \brief       calculate crc.
  \param[in]   handle  crc handle to operate.
  \param[in]   in      Pointer to the input data
  \param[out]  out     Pointer to the result.
  \param[in]   len     intpu data len.
  \return      error code
*/
int32_t csi_crc_calculate(crc_handle_t handle, const void *in, void *out, uint32_t len)
{
    CRC_NULL_PARAM_CHK(handle);
    CRC_NULL_PARAM_CHK(in);
    CRC_NULL_PARAM_CHK(out);
    if (len <= 0) {
        return ERR_CRC(EDRV_PARAMETER);
    }

    ck_crc_priv_t *crc_priv = handle;
    crc_reg = (ck_crc_reg_t *)(crc_priv->base);

    crc_priv->status.busy = 1;

    /* put the data int the register */
    uint8_t cur;
    uint8_t *p = (uint8_t *)in;
    for (cur=0; cur<len - 3; cur += 4, p+=4) {
        crc_set_data(p[0]
                    | (p[1] << 8)
                    | (p[2] << 16)
                    | (p[3] << 24));
    }
    uint32_t data = 0;
    uint8_t i;
    if (cur < len) {
        for (i=0; i<len-cur; i++) {
            data |= (p[cur + i] << (i*8));
        }
        crc_set_data(data);
    }

    crc_get_data((uint32_t *)out);
    crc_priv->status.busy = 0;

    return 0;
}

/**
  \brief       Get CRC status.
  \param[in]   handle  crc handle to operate.
  \return      CRC status \ref crc_status_t
*/
crc_status_t csi_crc_get_status(crc_handle_t handle)
{
    ck_crc_priv_t *crc_priv = handle;
    return crc_priv->status;
}
