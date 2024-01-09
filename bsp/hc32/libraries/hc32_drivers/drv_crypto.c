/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-10     CDT          first version
 */
#include "board.h"

#if defined(BSP_USING_HWCRYPTO)

// #define DRV_DEBUG
#define LOG_TAG             "drv_crypto"
#include <drv_log.h>

struct hc32_hwcrypto_device
{
    struct rt_hwcrypto_device dev;
    struct rt_mutex mutex;
};

#if defined(BSP_USING_CRC)

#define DEFAULT_CRC16_CCITT_POLY    (0x1021)       /*!<  X^16 + X^12 + X^5 + 1 */
#define DEFAULT_CRC32_POLY          (0x04C11DB7)   /*!<  X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 +X^8 + X^7 + X^5 + X^4 + X^2+ X + 1 */

static rt_uint32_t _crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_uint32_t result = 0;
    stc_crc_init_t stcCrcInit;
    static struct hwcrypto_crc_cfg crc_cfgbk = {0};
    struct hc32_hwcrypto_device *hc32_hw_dev = (struct hc32_hwcrypto_device *)ctx->parent.device->user_data;

    rt_mutex_take(&hc32_hw_dev->mutex, RT_WAITING_FOREVER);

    if (ctx->crc_cfg.poly != DEFAULT_CRC16_CCITT_POLY && ctx->crc_cfg.poly != DEFAULT_CRC32_POLY)
    {
        LOG_E("CRC polynomial only support 0x1021/0x04C11DB7U.");
        goto _exit;
    }

    /* if crc_cfg change we need init crc again */
    if (rt_memcmp(&crc_cfgbk, &ctx->crc_cfg, sizeof(struct hwcrypto_crc_cfg)))
    {
#if defined(HC32F460)
        switch (ctx->crc_cfg.flags)
        {
        case 0:
            stcCrcInit.u32RefIn = CRC_REFIN_DISABLE;
            stcCrcInit.u32RefOut = CRC_REFOUT_DISABLE;
            break;
        case CRC_FLAG_REFIN:
            stcCrcInit.u32RefIn = CRC_REFIN_ENABLE;
            stcCrcInit.u32RefOut = CRC_REFOUT_DISABLE;
            break;
        case CRC_FLAG_REFOUT:
            stcCrcInit.u32RefIn = CRC_REFIN_DISABLE;
            stcCrcInit.u32RefOut = CRC_REFOUT_ENABLE;
            break;
        case CRC_FLAG_REFIN | CRC_FLAG_REFOUT:
            stcCrcInit.u32RefIn = CRC_REFIN_ENABLE;
            stcCrcInit.u32RefOut = CRC_REFOUT_ENABLE;
            break;
        default :
            LOG_E("crc flag parameter error.");
            goto _exit;
        }

        if (ctx->crc_cfg.xorout)
        {
            stcCrcInit.u32XorOut = CRC_XOROUT_ENABLE;
        }
        else
        {
            stcCrcInit.u32XorOut = CRC_XOROUT_DISABLE;
        }
#endif

        switch (ctx->crc_cfg.width)
        {
        case 16U:
            stcCrcInit.u32Protocol = CRC_CRC16;
            break;
        case 32U:
            stcCrcInit.u32Protocol = CRC_CRC32;
            break;
        default :
            LOG_E("crc width only support 16/32.");
            goto _exit;
        }

        stcCrcInit.u32InitValue = ctx->crc_cfg.last_val;

        if (CRC_Init(&stcCrcInit) != LL_OK)
        {
            LOG_E("crc init error.");
            goto _exit;
        }
        LOG_D("CRC_Init.");
        rt_memcpy(&crc_cfgbk, &ctx->crc_cfg, sizeof(struct hwcrypto_crc_cfg));
    }
    if (16U  == ctx->crc_cfg.width)
    {
        result = CRC_CRC16_Calculate(ctx->crc_cfg.last_val, CRC_DATA_WIDTH_8BIT, in, length);
    }
    else        /* CRC32 */
    {
        result = CRC_CRC32_Calculate(ctx->crc_cfg.last_val, CRC_DATA_WIDTH_8BIT, in, length);
    }

_exit:
    rt_mutex_release(&hc32_hw_dev->mutex);

    return result;
}

static const struct hwcrypto_crc_ops crc_ops =
{
    .update = _crc_update,
};
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_RNG)
static rt_uint32_t _rng_rand(struct hwcrypto_rng *ctx)
{
    rt_uint32_t gen_random = 0;

    if (TRNG_GenerateRandom(&gen_random, 1U) != LL_OK)
    {
        return 0;
    }

    return gen_random;
}

static const struct hwcrypto_rng_ops rng_ops =
{
    .update = _rng_rand,
};
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_HASH)

#define HASH_SHA256_MSG_DIGEST_SIZE        (32U)

static const rt_uint8_t *hash_in = RT_NULL;
static rt_size_t hash_length = 0;

static rt_err_t _hash_update(struct hwcrypto_hash *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_uint32_t result = RT_EOK;

    struct hc32_hwcrypto_device *hc32_hw_dev = (struct hc32_hwcrypto_device *)ctx->parent.device->user_data;
    rt_mutex_take(&hc32_hw_dev->mutex, RT_WAITING_FOREVER);

    /* Start HASH computation transfer */
    switch (ctx->parent.type)
    {
    case HWCRYPTO_TYPE_SHA256:
        hash_in = in;
        hash_length = length;
        break;
    default :
        LOG_E("not support hash type: %x", ctx->parent.type);
        result = -RT_ERROR;
        break;
    }

    rt_mutex_release(&hc32_hw_dev->mutex);

    return  result;
}

static rt_err_t _hash_finish(struct hwcrypto_hash *ctx, rt_uint8_t *out, rt_size_t length)
{
    rt_uint32_t result = RT_EOK;

    struct hc32_hwcrypto_device *hc32_hw_dev = (struct hc32_hwcrypto_device *)ctx->parent.device->user_data;
    rt_mutex_take(&hc32_hw_dev->mutex, RT_WAITING_FOREVER);

    if (hash_in == RT_NULL || hash_length == 0)
    {
        LOG_E("no data input.");
        result = -RT_ERROR;
        goto _exit;
    }

    /* Get the hash Subtype */
    switch (ctx->parent.type)
    {
    case HWCRYPTO_TYPE_SHA256:
        /* SHA256 = 32*8 Bits */
        if (length == HASH_SHA256_MSG_DIGEST_SIZE)
        {
            result = HASH_Calculate(hash_in, hash_length, out);
        }
        else
        {
            LOG_E("The out size must be 32 bytes");
        }
        break;

    default :
        LOG_E("not support hash type: %x", ctx->parent.type);
        result = -RT_ERROR;
        break;
    }

_exit:
    rt_mutex_release(&hc32_hw_dev->mutex);

    return result;
}

static const struct hwcrypto_hash_ops hash_ops =
{
    .update = _hash_update,
    .finish  = _hash_finish
};

#endif /* BSP_USING_HASH */

#if defined(BSP_USING_AES)
static rt_err_t _cryp_crypt(struct hwcrypto_symmetric *ctx, struct hwcrypto_symmetric_info *info)
{
    rt_uint32_t result = RT_EOK;
    struct hc32_hwcrypto_device *hc32_hw_dev = (struct hc32_hwcrypto_device *)ctx->parent.device->user_data;
    rt_mutex_take(&hc32_hw_dev->mutex, RT_WAITING_FOREVER);

    switch (ctx->parent.type)
    {
    case HWCRYPTO_TYPE_AES_ECB:
        LOG_D("AES type is ECB.");
        break;
    case HWCRYPTO_TYPE_AES_CBC:
    case HWCRYPTO_TYPE_AES_CTR:
    case HWCRYPTO_TYPE_DES_ECB:
    case HWCRYPTO_TYPE_DES_CBC:
    default :
        LOG_E("not support cryp type: %x", ctx->parent.type);
        break;
    }

#if defined (HC32F460)
    if (ctx->key_bitlen != (AES_KEY_SIZE_16BYTE * 8U))
    {
        LOG_E("not support key bitlen: %d", ctx->key_bitlen);
        result = -RT_ERROR;
        goto _exit;
    }
#elif defined (HC32F4A0)
    if (ctx->key_bitlen != (AES_KEY_SIZE_16BYTE * 8U) && ctx->key_bitlen != (AES_KEY_SIZE_24BYTE * 8U) && \
            ctx->key_bitlen != (AES_KEY_SIZE_32BYTE * 8U))
    {
        LOG_E("not support key bitlen: %d", ctx->key_bitlen);
        result = -RT_ERROR;
        goto _exit;
    }
#endif

    if ((info->length % 16U) != 0U)
    {
        LOG_E("aes supports only an integer multiple of 16 in length");
        result = -RT_ERROR;
        goto _exit;
    }

    if (info->mode == HWCRYPTO_MODE_ENCRYPT)
    {
        /* AES encryption. */
        result = AES_Encrypt(info->in, info->length, ctx->key, (ctx->key_bitlen / 8U), info->out);
    }
    else if (info->mode == HWCRYPTO_MODE_DECRYPT)
    {
        /* AES decryption */
        result = AES_Decrypt(info->in, info->length, ctx->key, (ctx->key_bitlen / 8U), info->out);
    }
    else
    {
        rt_kprintf("error cryp mode : %02x!\n", info->mode);
        result = -RT_ERROR;
        goto _exit;
    }

_exit:
    rt_mutex_release(&hc32_hw_dev->mutex);

    return result;
}

static const struct hwcrypto_symmetric_ops cryp_ops =
{
    .crypt = _cryp_crypt
};
#endif

static rt_err_t _crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
    {
        /* Enable TRNG. */
        FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_TRNG, ENABLE);
        /* TRNG initialization configuration. */
        TRNG_Init(TRNG_SHIFT_CNT64, TRNG_RELOAD_INIT_VAL_ENABLE);

        ((struct hwcrypto_rng *)ctx)->ops = &rng_ops;

        break;
    }
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        /* Enable CRC module clock. */
        FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_CRC, ENABLE);
        /* do not Initialize CRC because crc_update will do it */
        ((struct hwcrypto_crc *)ctx)->ops = &crc_ops;

        break;
    }
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_HASH)
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
    {
        if (ctx->type == HWCRYPTO_TYPE_SHA256)
        {
            /* Enable HASH. */
            FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_HASH, ENABLE);
            ((struct hwcrypto_hash *)ctx)->ops = &hash_ops;
        }
        else
        {
            LOG_E("not support hash type.");
            res = -RT_ERROR;
        }
        break;
    }
#endif /* BSP_USING_HASH */

#if defined(BSP_USING_AES)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
    {
        /* Enable AES peripheral clock. */
        FCG_Fcg0PeriphClockCmd(PWC_FCG0_AES, ENABLE);

        ((struct hwcrypto_symmetric *)ctx)->ops = &cryp_ops;

        break;
    }
#endif  /* BSP_USING_AES */

    default:
        res = -RT_ERROR;
        break;
    }
    return res;
}

static void _crypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
        TRNG_DeInit();
        FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_TRNG, DISABLE);
        break;
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        CRC_DeInit();
        FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_CRC, DISABLE);
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_HASH)
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
        HASH_DeInit();
        FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_HASH, DISABLE);
        break;
#endif /* BSP_USING_HASH */

#if defined(BSP_USING_AES)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
        AES_DeInit();
        FCG_Fcg0PeriphClockCmd(PWC_FCG0_AES, DISABLE);
        break;
#endif /* BSP_USING_AES */

    default:
        break;
    }
}

static rt_err_t _crypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t res = RT_EOK;

    switch (src->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
        break;
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_HASH)
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
        break;
#endif /* BSP_USING_HASH */

#if defined(BSP_USING_AES)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
        break;
#endif /* BSP_USING_AES */

    default:
        res = -RT_ERROR;
        break;
    }
    return res;
}

static void _crypto_reset(struct rt_hwcrypto_ctx *ctx)
{
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
        break;
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
        break;
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_HASH)
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
        break;
#endif /* BSP_USING_HASH*/

#if defined(BSP_USING_AES)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
        break;
#endif /* BSP_USING_AES */

    default:
        break;
    }
}

static const struct rt_hwcrypto_ops _ops =
{
    .create = _crypto_create,
    .destroy = _crypto_destroy,
    .copy = _crypto_clone,
    .reset = _crypto_reset,
};

static int rt_hw_crypto_device_init(void)
{
    static struct hc32_hwcrypto_device _crypto_dev;

#if defined(BSP_USING_UQID)
    stc_efm_unique_id_t pstcUID;
    rt_uint32_t cpuid[3] = {0};

    EFM_GetUID(&pstcUID);
    cpuid[0] = pstcUID.u32UniqueID0;
    cpuid[1] = pstcUID.u32UniqueID1;
    cpuid[2] = pstcUID.u32UniqueID2;
    /* we only used 2 words to as the UQID */
    rt_memcpy(&_crypto_dev.dev.id, cpuid, 8);
    LOG_D("UQID = %x%x", cpuid[0], cpuid[1]);
#endif /* BSP_USING_UQID */

    _crypto_dev.dev.ops = &_ops;
    _crypto_dev.dev.user_data = &_crypto_dev;

    if (rt_hwcrypto_register(&_crypto_dev.dev, RT_HWCRYPTO_DEFAULT_NAME) != RT_EOK)
    {
        return -RT_ERROR;
    }

    rt_mutex_init(&_crypto_dev.mutex, RT_HWCRYPTO_DEFAULT_NAME, RT_IPC_FLAG_PRIO);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_crypto_device_init);

#endif
