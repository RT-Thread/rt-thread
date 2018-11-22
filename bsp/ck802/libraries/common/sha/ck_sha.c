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
 * @file     ck_sha.c
 * @brief    CSI Source File for SHA Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "csi_core.h"
#include "drv_sha.h"
#include "ck_sha.h"


typedef struct {
    uint32_t base;
    uint32_t irq;
    sha_event_cb_t cb;
    sha_status_t status;
    sha_mode_e mode;
    sha_endian_mode_e endian;
} ck_sha_priv_t;

static ck_sha_priv_t sha_handle[CONFIG_SHA_NUM];
bool finish_flag = 0;

/* Driver Capabilities */
static const sha_capabilities_t driver_capabilities = {
    .sha1 = 1, /* sha1 mode */
    .sha224 = 1, /* sha224 mode */
    .sha256 = 1, /* sha256 mode */
    .sha384 = 1, /* sha384 mode */
    .sha512 = 1, /* sha512 mode */
    .sha512_224 = 1, /* sha512_224 mode */
    .sha512_256 = 1, /* sha512_256 mode */
    .endianmode = 1, /* endian mode */
    .interruptmode = 1  /* interrupt mode */
};

#define ERR_SHA(errno) (CSI_DRV_ERRNO_SHA_BASE | errno)
#define SHA_NULL_PARAM_CHK(para)                         \
        do {                                        \
            if (para == NULL) {                     \
                return ERR_SHA(EDRV_PARAMETER);   \
            }                                       \
        } while (0)
//
// Functions
//

ck_sha_reg_t *sha_reg = NULL;
volatile static uint8_t sha_int_flag = 1;

static int32_t sha_set_mode(sha_mode_e mode)
{
    sha_reg->SHA_CON = mode;
    return 0;
}

static int32_t sha_enable_interrupt(void)
{
    sha_reg->SHA_CON |= 1 << SHA_INT_ENABLE_OFFSET;
    return 0;
}

static int32_t sha_disable_interrupt(void)
{
    sha_reg->SHA_CON &= ~(1 << SHA_INT_ENABLE_OFFSET);
    return 0;
}

static void sha_clear_interrupt(void)
{
    sha_reg->SHA_INTSTATE = 0;
}

static int32_t sha_enable_initial(void)
{
    sha_reg->SHA_CON |= 1 << SHA_INIT_OFFSET;
    return 0;
}

static int32_t sha_enable_calculate(void)
{
    sha_reg->SHA_CON |= 1 << SHA_CAL_OFFSET;
    return 0;
}

static int32_t sha_select_endian_mode(sha_endian_mode_e mode)
{
    sha_reg->SHA_CON |= mode << SHA_ENDIAN_OFFSET;
    return 0;
}

static int32_t sha_input_data(uint32_t *data, uint32_t length)
{
    uint8_t i;
    uint32_t *input_data = (uint32_t *) & (sha_reg->SHA_DATA1);

    for (i = 0; i < length; i++) {
        *(input_data + i) = *(data + i);
    }

    return 0;
}

static int32_t sha_get_data(sha_handle_t handle, uint32_t *data)
{
    ck_sha_priv_t *sha_priv = handle;

    uint8_t len;
    uint8_t i;
    uint32_t *result = (uint32_t *)&sha_reg->SHA_H0L;
    /* according to different mode to obtain the hash result */
    if (sha_priv->mode == SHA_MODE_1 || sha_priv->mode == SHA_MODE_224 || sha_priv->mode == SHA_MODE_256) {
        if (sha_priv->mode == SHA_MODE_1) {
            len = 5;
        } else if (sha_priv->mode == SHA_MODE_224) {
            len = 7;
        } else if (sha_priv->mode == SHA_MODE_256) {
            len = 8;
        }

        for (i = 0; i < len; i++) {
            data[i] = *(result + i);
        }
    } else {
        if (sha_priv->mode == SHA_MODE_384) {
            len = 6;
        } else if (sha_priv->mode == SHA_MODE_512) {
            len = 8;
        }

        uint32_t *resulth = (uint32_t *)&sha_reg->SHA_H0H;
        for (i = 0; i < len; i++) {
            data[i << 1] = *(resulth + i);
            data[(i << 1) + 1] = *(result + i);
        }
    }

    return 0;
}

static inline void sha_reverse_order(uint8_t *pdata, int32_t length)
{
    uint8_t input_data[length];
    uint8_t result[length];
    uint32_t tmp = 0;
    int32_t i = 0;
    memcpy((void *)input_data, (void *)pdata, length);

    for (i = 0; i < length; i++) {
        tmp = i >> 2;
        tmp = tmp << 3;
        result[i] = input_data[tmp + 3 - i];
    }

    memcpy((void *)pdata, (void *)result, length);
}

void ck_sha_irqhandler(int32_t idx)
{
    sha_int_flag = 0;
    sha_clear_interrupt();      //clear sha interrupt

    ck_sha_priv_t *sha_priv = &sha_handle[idx];
    if (finish_flag != 0) {
        if (sha_priv->cb != NULL) {
            sha_priv->cb(SHA_EVENT_COMPLETE);       //execute the callback function
        }
    }
}

int32_t __attribute__((weak)) target_get_sha_count(void)
{
    return 0;
}

int32_t __attribute__((weak)) target_get_sha(int32_t idx, uint32_t *base, uint32_t *irq)
{
    return NULL;
}

/**
  \brief       get sha handle count.
  \return      sha handle count
*/
int32_t csi_sha_get_instance_count(void)
{
    return target_get_sha_count();
}

/**
  \brief       Initialize SHA Interface. 1. Initializes the resources needed for the SHA interface 2.registers event callback function
  \param[in]   idx must not exceed return value of csi_sha_get_instance_count()
  \param[in]   cb_event  Pointer to \ref sha_event_cb_t
  \return      return sha handle if success
*/
sha_handle_t csi_sha_initialize(int32_t idx, sha_event_cb_t cb_event)
{

    if (idx < 0 || idx >= CONFIG_SHA_NUM) {
        return NULL;
    }

    uint32_t base = 0u;
    uint32_t irq;
    /* obtain the sha information */
    int32_t real_idx = target_get_sha(idx, &base, &irq);

    if (real_idx != idx) {
        return NULL;
    }

    ck_sha_priv_t *sha_priv = &sha_handle[idx];

    sha_priv->base = base;
    sha_priv->irq  = irq;

    /* initialize the sha context */
    sha_priv->cb = cb_event;
    sha_priv->status.busy = 0;

    drv_nvic_enable_irq(sha_priv->irq);

    return (sha_handle_t)sha_priv;
}

/**
  \brief       De-initialize SHA Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  sha handle to operate.
  \return      error code
*/
int32_t csi_sha_uninitialize(sha_handle_t handle)
{
    SHA_NULL_PARAM_CHK(handle);

    ck_sha_priv_t *sha_priv = handle;
    sha_priv->cb = NULL;

    sha_disable_interrupt();
    drv_nvic_disable_irq(sha_priv->irq);

    return 0;
}

/**
  \brief       Get driver capabilities.
  \param[in]   handle sha handle to operate.
  \return      \ref sha_capabilities_t
*/
sha_capabilities_t csi_sha_get_capabilities(sha_handle_t handle)
{
    return driver_capabilities;
}

/**
  \brief       config sha mode.
  \param[in]   handle  sha handle to operate.
  \param[in]   mode      \ref sha_mode_e
  \param[in]   endian    \ref sha_endian_mode_e
  \return      error code
*/
int32_t csi_sha_config(sha_handle_t handle, sha_mode_e mode, sha_endian_mode_e endian_mode)
{
    SHA_NULL_PARAM_CHK(handle);

    ck_sha_priv_t *sha_priv = handle;
    sha_reg = (ck_sha_reg_t *)(sha_priv->base);

    /* config the sha mode */
    switch (mode) {
        case SHA_MODE_512_256:
        case SHA_MODE_512_224:
            return ERR_SHA(EDRV_UNSUPPORTED);

        case SHA_MODE_1:
        case SHA_MODE_224:
        case SHA_MODE_256:
        case SHA_MODE_384:
        case SHA_MODE_512:
            sha_priv->mode = mode;
            break;

        default:
            return ERR_SHA(EDRV_PARAMETER);
    }

    sha_set_mode(mode);

    /*config the sha endian mode */
    if (endian_mode == SHA_ENDIAN_MODE_LITTLE) {
        sha_priv->endian = endian_mode;
        sha_select_endian_mode(endian_mode);
    } else if (endian_mode == SHA_ENDIAN_MODE_BIG) {
        sha_priv->endian = endian_mode;
        sha_select_endian_mode(endian_mode);
    } else {
        return ERR_SHA(EDRV_PARAMETER);
    }

    sha_enable_interrupt();

    return 0;
}

/**
  \brief       start the engine
  \param[in]   handle  sha handle to operate.
  \param[in]   context  Pointer to the sha context.
  \return      error code
*/
int32_t csi_sha_starts(sha_handle_t handle, void *context)
{
    SHA_NULL_PARAM_CHK(handle);

    ck_sha_priv_t *sha_priv = handle;
    sha_enable_initial();
    sha_priv->status.busy = 1;

    return 0;
}

/**
  \brief       updata the engine
  \param[in]   handle  sha handle to operate.
  \param[in]   context  Pointer to the sha context.
  \param[in]   input   Pointer to the Source data
  \param[in]   len    the data len
  \return      error code
*/
static uint8_t sha_buffer[128];
static uint32_t total[2] = {0x0};
static uint32_t last_left = 0;
int32_t csi_sha_update(sha_handle_t handle, void *context, const void *input, uint32_t len)
{
    SHA_NULL_PARAM_CHK(handle);
    SHA_NULL_PARAM_CHK(input);
    if (len <= 0) {
        return ERR_SHA(EDRV_PARAMETER);
    }

    ck_sha_priv_t *sha_priv = handle;
    sha_reg = (ck_sha_reg_t *)(sha_priv->base);

    uint32_t block_size;
    uint32_t left_len = 0;
    if (sha_priv->mode < 4) {
        block_size = 64;
        left_len = len & 0x3f;
    } else {
        block_size = 128;
        left_len = len & 0x7f;
    }

    uint32_t left = total[0] & (block_size - 1);
    uint32_t fill = block_size - left;

    total[0] += len;
    total[0] &= 0xffffffff;
    uint32_t word_left = total[0] & 0x3;

    uint8_t *p = (uint8_t *)input;
    /* when the text is not aligned by block and len > fill */
    if (left && len >= fill) {
        if (last_left && sha_priv->endian == SHA_ENDIAN_MODE_LITTLE) {
            uint32_t i;
            for (i = 0; i < 4 - last_left; i++) {
                if (finish_flag) {
                    *(sha_buffer + 3 - last_left - i) = *((uint8_t *)p + 3 - last_left - i);
                } else {
                    *(sha_buffer + left + 3 - last_left - i) = *((uint8_t *)p + 3 - last_left - i);
                }
            }

            fill = fill - 4 + last_left;
            p = (p + 4 - last_left);
        }

        if (last_left) {
            memcpy((void *)(sha_buffer + left + 4 - last_left), p, fill);
        } else {
            memcpy((void *)(sha_buffer + left), p, fill);
        }

        /* set the input data */
        sha_input_data((uint32_t *)sha_buffer, block_size >> 2);
        sha_enable_calculate();

        while (sha_int_flag);

        sha_int_flag = 1;
        p += fill;
        len -= fill;
        left = 0;
    }

    /* calculate the hash by block */
    while (len >= block_size) {
        sha_input_data((uint32_t *)p, block_size >> 2);
        sha_enable_calculate();

        while (sha_int_flag);

        sha_int_flag = 1;
        p += block_size;
        len -= block_size;
    }

    /* when the text is not aligned by block and len < fill */
    if (len > 0) {
        if (sha_priv->endian == SHA_ENDIAN_MODE_BIG || word_left == 0) {
            memcpy((void *)(sha_buffer + left), p, len);
        } else {
            memcpy((void *)(sha_buffer + left), p, len + 4 - word_left);
            last_left = word_left;
        }
    }

    sha_priv->status.busy = 0;

    return 0;
}

static unsigned char sha_padding[128] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/**
  \brief       finish the engine
  \param[in]   handle  sha handle to operate.
  \param[in]   context  Pointer to the sha context.
  \param[out]  output   Pointer to the dest data
  \return      error code
*/
static uint32_t total_length;
int32_t csi_sha_finish(sha_handle_t handle, void *context, void *output)
{
    SHA_NULL_PARAM_CHK(handle);
    SHA_NULL_PARAM_CHK(output);

    ck_sha_priv_t *sha_priv = handle;
    uint32_t block_size;
    if (sha_priv->mode < 4) {
        block_size = 64;
    } else {
        block_size = 128;
    }

    total_length = total[0] << 3;
    uint32_t last = total[0] & (block_size - 1);
    uint32_t padn = (last < block_size) ? (block_size - last) : (block_size + block_size - last);

    uint32_t left = total[0] & 0x3;

    uint8_t temp_data[4];
    uint32_t j;
    /*calculate the final word*/
    for (j = 0; j < 4; j++) {
        temp_data[j] = (total_length >> (8 * j)) & 0xff;
    }

    /* group the final package according to the endian mode */
    if (sha_priv->endian == SHA_ENDIAN_MODE_BIG) {
        memset(sha_padding, 0x0, sizeof(sha_padding));
        sha_padding[0] = 0x80;

        for (j = 0; j < 4; j++) {
            sha_padding[padn - 4 + j] = temp_data[3 - j];
        }
    } else {
        memset(sha_padding, 0x0, sizeof(sha_padding));
        sha_padding[3 - left] = 0x80;

        for (j = 0; j < 4; j++) {
            sha_padding[padn - 4 + j] = temp_data[j];
        }
    }

    finish_flag = 1;

    csi_sha_update(handle, NULL, sha_padding, padn);

    /* get the hash result */
    sha_get_data(handle, (uint32_t *)output);

    uint8_t *p = output;
    /* convert the data endian according the sha mode */
    if (sha_priv->mode == SHA_MODE_1) {
        sha_reverse_order(p, 20);
    } else if (sha_priv->mode == SHA_MODE_224) {
        sha_reverse_order(p, 28);
    } else if (sha_priv->mode == SHA_MODE_256) {
        sha_reverse_order(p, 32);
    } else if (sha_priv->mode == SHA_MODE_512) {
        sha_reverse_order(p, 64);
    } else if (sha_priv->mode == SHA_MODE_384) {
        sha_reverse_order(p, 48);
    }

    total[0] = 0;
    memset(sha_buffer, 0, sizeof(sha_buffer));
    memset(sha_padding, 0, sizeof(sha_padding));
    last_left = 0;
    finish_flag = 0;

    return 0;
}

/**
  \brief       Get SHA status.
  \param[in]   handle  sha handle to operate.
  \return      SHA status \ref sha_status_t
*/
sha_status_t csi_sha_get_status(sha_handle_t handle)
{
    ck_sha_priv_t *sha_priv = handle;
    return sha_priv->status;
}
