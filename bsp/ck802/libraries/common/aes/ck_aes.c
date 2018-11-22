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
 * @file     ck_aes.c
 * @brief    CSI Source File for aes driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include "csi_core.h"
#include "drv_aes.h"
#include "ck_aes.h"

#define ERR_AES(errno) (CSI_DRV_ERRNO_AES_BASE | errno)
#define AES_NULL_PARA_CHK(para)                         \
        do {                                        \
            if (para == NULL) {                     \
                return ERR_AES(EDRV_PARAMETER);   \
            }                                       \
        } while (0)
static ck_aes_reg_t *aes_reg = NULL;

typedef struct {
    uint32_t base;
    uint32_t irq;
    void *iv;
    uint8_t *result_out;
    uint32_t len;
    aes_event_cb_t cb;
    aes_mode_e mode;
    aes_key_len_bits_e keylen;
    aes_endian_mode_e endian;
    aes_status_t status;
} ck_aes_priv_t;

static ck_aes_priv_t aes_handle[CONFIG_AES_NUM];

/* Driver Capabilities */
static const aes_capabilities_t driver_capabilities = {
    .ecb_mode = 1, /* ECB mode */
    .cbc_mode = 1, /* CBC mode */
    .cfb_mode = 0, /* CFB mode */
    .ofb_mode = 0, /* OFB mode */
    .ctr_mode = 0, /* CTR mode */
    .bits_128 = 1, /* 128bits key length mode */
    .bits_192 = 1, /* 192bits key lenght mode */
    .bits_256 = 1  /* 256bits key length mode */
};

//
// Functions
//

static inline void aes_set_opcode(aes_crypto_mode_e opcode)
{
    aes_reg->ctrl &= ~(3 << AES_OPCODE_OFFSET);          //clear bit[7:6]
    aes_reg->ctrl |= (opcode << AES_OPCODE_OFFSET);    //set opcode
}

static inline void aes_set_endian(aes_endian_mode_e endian)
{
    if (endian == AES_ENDIAN_LITTLE) {
        aes_reg->ctrl &= ~AES_LITTLE_ENDIAN;
    } else {
        aes_reg->ctrl |= AES_LITTLE_ENDIAN;
    }
}

static inline uint32_t aes_set_keylen(aes_key_len_bits_e keylength)
{
    aes_reg->ctrl &= ~(3 << AES_KEY_LEN_OFFSET);        //clear bit[5:4]
    aes_reg->ctrl |= (keylength << AES_KEY_LEN_OFFSET);// Set key length

    return 0;
}

static inline void aes_set_mode(aes_mode_e mode)
{
    aes_reg->ctrl &= ~(1 << AES_MODE_OFFSET);      //clear bit 3
    aes_reg->ctrl |= (mode << AES_MODE_OFFSET);  //set mode
}

static inline void aes_enable(void)
{
    aes_reg->ctrl |= (1 << AES_WORK_ENABLE_OFFSET);
}

static inline void aes_disable(void)
{
    aes_reg->ctrl &= ~(1 << AES_WORK_ENABLE_OFFSET);
}

static inline void aes_enable_interrupt(void)
{
    aes_reg->ctrl |= (1 << AES_INT_ENABLE_OFFSET);
}

static inline void aes_disable_interrupt(void)
{
    aes_reg->ctrl &= ~(1 << AES_INT_ENABLE_OFFSET);
}

static inline void aes_clear_interrupt(void)
{
    aes_reg->state = 0x0;
}

static inline uint32_t aes_get_intstatus(uint32_t AES_IT)
{
    return (aes_reg->state & AES_IT) ? 1 : 0;
}

static void aes_set_key(void *context, uint8_t *key, uint32_t keylen, uint32_t enc, uint32_t endian)
{
    uint8_t keynum = 0;

    if (keylen == AES_KEY_LEN_BITS_128) {
        keynum = 4;
    } else if (keylen == AES_KEY_LEN_BITS_192) {
        keynum = 6;
    } else if (keylen == AES_KEY_LEN_BITS_256) {
        keynum = 8;
    }

    uint32_t i;
    /* set key according to the endian mode */
    if (endian == AES_ENDIAN_LITTLE) {
        for (i = 0; i < keynum; i++) {
            aes_reg->key[keynum - 1 - i] = *(uint32_t *)key;
            key += 4;
        }
    } else if (endian == AES_ENDIAN_BIG) {
        for (i = 0; i < keynum; i++) {
            aes_reg->key[i] = *(uint32_t *)key;
            key += 4;
        }
    }

    if (enc == AES_CRYPTO_MODE_DECRYPT) {
        aes_set_opcode(AES_CRYPTO_KEYEXP);      /* if the mode is decrypt before decrypt you have to keyexpand */
        aes_enable();

        while (aes_get_intstatus(AES_IT_KEYINT));

        aes_set_opcode(AES_CRYPTO_MODE_DECRYPT);
    } else if (enc == AES_CRYPTO_MODE_ENCRYPT) {
        aes_set_opcode(AES_CRYPTO_MODE_ENCRYPT);
    }

    aes_disable();
}

static int aes_crypto(void *context, uint8_t *in, uint8_t *out,
               uint32_t len, uint8_t *iv, uint32_t mode, uint32_t endian)
{
    uint32_t i = 0;

    /* set iv if the mode is CBC */
    if (mode == AES_MODE_CBC) {
        if (endian == AES_ENDIAN_BIG) {
            for (i = 0; i < 4; i++) {
                aes_reg->iv[i] = *(uint32_t *)iv;
                iv += 4;
            }
        } else if (endian == AES_ENDIAN_LITTLE) {
            for (i = 0; i < 4; i++) {
                aes_reg->iv[3 - i] = *(uint32_t *)iv;
                iv += 4;
            }
        }
    }

    uint32_t j = 0;
    /* set the text before aes calculating */
    for (i = 0; i < len; i = i + 16) {
        for (j = 0; j < 4; j++) {
            if (endian == AES_ENDIAN_BIG) {
                aes_reg->datain[j] = *(uint32_t *)in;
            } else if (endian == AES_ENDIAN_LITTLE) {
                aes_reg->datain[3 - j] = *(uint32_t *)in;
            }

            in += 4;
        }

        aes_enable();
    }

    return 0;
}

void ck_aes_irqhandler(int32_t idx)
{
    ck_aes_priv_t *aes_priv = &aes_handle[idx];

    volatile uint32_t j;
    uint32_t tmp = 0;
    /* get the result after aes calculating*/
    if (aes_priv->result_out != NULL) {
        for (j = 0; j < 4; j++) {
            if (aes_priv->endian == AES_ENDIAN_BIG) {
                tmp = aes_reg->dataout[j];
            } else if (aes_priv->endian == AES_ENDIAN_LITTLE) {
                tmp = aes_reg->dataout[3 - j];
            }

            *(uint32_t *)aes_priv->result_out = tmp;
            aes_priv->result_out += 4;
            aes_priv->len -= 4;
        }
    }

    /* disable aes and clear the aes interrupt */
    aes_disable();
    aes_clear_interrupt();

    /* execute the callback function */
    if (aes_priv->len == 0) {
        if (aes_priv->cb) {
            aes_priv->cb(AES_EVENT_CRYPTO_COMPLETE);
        }
    }
}


int32_t __attribute__((weak)) target_get_aes_count(void)
{
    return 0;
}

int32_t __attribute__((weak)) target_get_aes(int32_t idx, uint32_t *base, uint32_t *irq)
{
    return NULL;
}

/**
  \brief       get aes instance count.
  \return      aes handle count
*/
int32_t csi_aes_get_instance_count(void)
{
    return target_get_aes_count();
}

/**
  \brief       Initialize AES Interface. 1. Initializes the resources needed for the AES interface 2.registers event callback function
  \param[in]   idx must not exceed return value of csi_aes_get_instance_count().
  \param[in]   cb_event  Pointer to \ref aes_event_cb_t
  \return      return aes handle if success
*/
aes_handle_t csi_aes_initialize(int32_t idx, aes_event_cb_t cb_event)
{

    if (idx < 0 || idx >= CONFIG_AES_NUM) {
        return NULL;
    }

    uint32_t irq = 0u;
    uint32_t base = 0u;
    /* obtain the aes information */
    int32_t real_idx = target_get_aes(idx, &base, &irq);

    if (real_idx != idx) {
        return NULL;
    }

    ck_aes_priv_t *aes_priv = &aes_handle[idx];

    aes_priv->base = base;
    aes_priv->irq  = irq;

    /* initialize the aes context */
    aes_reg = (ck_aes_reg_t *)(aes_priv->base);
    aes_priv->cb = cb_event;
    aes_priv->iv = NULL;
    aes_priv->len = 16;
    aes_priv->result_out = NULL;
    aes_priv->mode = AES_MODE_CBC;
    aes_priv->keylen = AES_KEY_LEN_BITS_128;
    aes_priv->endian = AES_ENDIAN_LITTLE;
    aes_priv->status.busy = 0;

    aes_enable_interrupt();             /* enable the aes interrupt */

    drv_nvic_enable_irq(aes_priv->irq); /* enable the aes bit in nvic */

    return (aes_handle_t)aes_priv;
}

/**
  \brief       De-initialize AES Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  aes handle to operate.
  \return      error code
*/
int32_t csi_aes_uninitialize(aes_handle_t handle)
{
    AES_NULL_PARA_CHK(handle);

    ck_aes_priv_t *aes_priv = handle;
    aes_priv->cb = NULL;

    aes_disable_interrupt();            /* disable the aes interrupt */

    drv_nvic_disable_irq(aes_priv->irq);

    return 0;
}

/**
  \brief       Get driver capabilities.
  \param[in]   handle  aes handle to operate.
  \return      \ref aes_capabilities_t
*/
aes_capabilities_t csi_aes_get_capabilities(aes_handle_t handle)
{
    return driver_capabilities;
}

/**
  \brief       config aes mode.
  \param[in]   handle  aes handle to operate.
  \param[in]   mode      \ref aes_mode_e
  \param[in]   keylen_bits \ref aes_key_len_bits_e
  \param[in]   endian    \ref aes_endian_mode_e
  \param[in]   arg       Pointer to the iv address when mode is cbc_mode
  \return      error code
*/
int32_t csi_aes_config(aes_handle_t handle, aes_mode_e mode, aes_key_len_bits_e keylen_bits, aes_endian_mode_e endian, uint32_t arg)
{
    AES_NULL_PARA_CHK(handle);

    ck_aes_priv_t *aes_priv = handle;
    aes_reg = (ck_aes_reg_t *)(aes_priv->base);

    /* config the aes mode */
    switch (mode) {
        case AES_MODE_CBC:
            aes_priv->iv = (void *)arg;
            aes_priv->mode = mode;
            aes_set_mode(mode);
            break;

        case AES_MODE_ECB:
            aes_priv->mode = mode;
            aes_set_mode(mode);
            break;

        case AES_MODE_CFB:
        case AES_MODE_OFB:
        case AES_MODE_CTR:
            return ERR_AES(EDRV_UNSUPPORTED);

        default:
            return ERR_AES(EDRV_PARAMETER);
    }

    /* config the key length */
    switch (keylen_bits) {
        case AES_KEY_LEN_BITS_128:
        case AES_KEY_LEN_BITS_192:
        case AES_KEY_LEN_BITS_256:
            aes_priv->keylen = keylen_bits;
            aes_set_keylen(keylen_bits);
            break;

        default:
            return ERR_AES(EDRV_PARAMETER);
    }

    /* config the endian mode */
    switch (endian) {
        case AES_ENDIAN_LITTLE:
            aes_priv->endian = endian;
            aes_set_endian(endian);
            break;

        case AES_ENDIAN_BIG:
            aes_priv->endian = endian;
            aes_set_endian(endian);
            break;

        default:
            return ERR_AES(EDRV_PARAMETER);
    }

    return 0;
}

/**
  \brief       set crypto key.
  \param[in]   handle    aes handle to operate.
  \param[in]   context   aes information context(NULL when hardware implementation)
  \param[in]   key       Pointer to the key buf
  \param[in]   key_len    the key len
  \param[in]   enc       \ref aes_crypto_mode_e
  \return      error code
*/
int32_t csi_aes_set_key(aes_handle_t handle, void *context, void *key, uint32_t key_len, aes_crypto_mode_e enc)
{
    AES_NULL_PARA_CHK(handle);
    AES_NULL_PARA_CHK(key);
    if ((key_len != AES_KEY_LEN_BITS_128 &&
        key_len != AES_KEY_LEN_BITS_192 &&
        key_len != AES_KEY_LEN_BITS_256) ||
        (enc != AES_CRYPTO_MODE_ENCRYPT &&
        enc != AES_CRYPTO_MODE_DECRYPT)) {
        return ERR_AES(EDRV_PARAMETER);
    }

    ck_aes_priv_t *aes_priv = handle;
    aes_set_key(context, key, key_len, enc, aes_priv->endian);

    return 0;
}

/**
  \brief       encrypt or decrypt
  \param[in]   handle  aes handle to operate.
  \param[in]   context aes information context(NULL when hardware implementation)
  \param[in]   in   Pointer to the Source data
  \param[out]  out  Pointer to the Result data.
  \param[in]   len  the Source data len.
  \param[in]   padding \ref aes_padding_mode_e.
  \return      error code
*/
int32_t csi_aes_crypto(aes_handle_t handle, void *context, void *in, void *out, uint32_t len, aes_padding_mode_e padding)
{
    AES_NULL_PARA_CHK(handle);
    AES_NULL_PARA_CHK(in);
    AES_NULL_PARA_CHK(out);
    AES_NULL_PARA_CHK(len);

    ck_aes_priv_t *aes_priv = handle;

    aes_priv->status.busy = 1;

    uint8_t left_len = len & 0xf;
    switch (padding) {
        case AES_PADDING_MODE_NO:
            if (left_len) {
                return ERR_AES(EDRV_PARAMETER);
            }

            /* crypto in padding no mode */
            aes_priv->result_out = out;
            aes_priv->len = len;
            aes_crypto(context, in, out, len, aes_priv->iv, aes_priv->mode, aes_priv->endian);
            break;

        case AES_PADDING_MODE_ZERO:
            if (left_len == 0) {
                return ERR_AES(EDRV_PARAMETER);
            }

            uint8_t i = 0;
            for (i = 0; i < (16 - left_len); i++) {
                *((uint8_t *)in + len + i) = 0x0;
            }

            /* crypto in padding zero mode */
            aes_priv->result_out = out;
            aes_priv->len = len + 16 -left_len;
            aes_crypto(context, in, out, len + 16 - left_len, aes_priv->iv, aes_priv->mode, aes_priv->endian);
            break;

        case AES_PADDING_MODE_PKCS5:
            return ERR_AES(EDRV_UNSUPPORTED);

        default:
            return ERR_AES(EDRV_PARAMETER);
    }

    aes_priv->status.busy = 0;
    return 0;
}

/**
  \brief       Get AES status.
  \param[in]   handle  aes handle to operate.
  \return      AES status \ref aes_status_t
*/
aes_status_t csi_aes_get_status(aes_handle_t handle)
{
    ck_aes_priv_t *aes_priv = handle;
    return aes_priv->status;
}
