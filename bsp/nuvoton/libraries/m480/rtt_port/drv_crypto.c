/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author         Notes
* 2020-3-3        CHChen         First version
* 2020-5-3        YCHuang12      Add TDES and SHA
*
******************************************************************************/

#include <rtconfig.h>

#if ((defined(BSP_USING_CRYPTO) || defined(BSP_USING_TRNG) || defined(BSP_USING_CRC)) && defined(RT_USING_HWCRYPTO))

#include <string.h>

#include <rtdevice.h>
#include <rtdbg.h>
#include "NuMicro.h"
#include <nu_bitutil.h>

#if defined(BSP_USING_TRNG)
    #include "drv_trng.h"
#endif

#if defined(BSP_USING_CRC)
    #include "drv_crc.h"
#endif

/* Private typedef --------------------------------------------------------------*/

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_hwcrypto_create(struct rt_hwcrypto_ctx *ctx);
static void nu_hwcrypto_destroy(struct rt_hwcrypto_ctx *ctx);
static rt_err_t nu_hwcrypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src);
static void nu_hwcrypto_reset(struct rt_hwcrypto_ctx *ctx);

/* Private variables ------------------------------------------------------------*/
static const struct rt_hwcrypto_ops nu_hwcrypto_ops =
{
    .create = nu_hwcrypto_create,
    .destroy = nu_hwcrypto_destroy,
    .copy = nu_hwcrypto_clone,
    .reset = nu_hwcrypto_reset,
};

/* Crypto engine operation ------------------------------------------------------------*/
#if defined(BSP_USING_CRYPTO)

//define NU_HWCRYPTO_NOT_ALIGN_CHECK to disable plain/cipher buffer address alignment checking
//#define NU_HWCRYPTO_NOT_ALIGN_CHECK

#define NU_HWCRYPTO_DES_3KEYS    1
#define NU_HWCRYPTO_DES_NO3KEYS  0
#define NU_HWCRYPTO_AES_NAME    "nu_AES"
#define NU_HWCRYPTO_TDES_NAME   "nu_TDES"
#define NU_HWCRYPTO_SHA_NAME    "nu_SHA"
#if !defined(BSP_USING_TRNG)
    #define NU_HWCRYPTO_PRNG_NAME   "nu_PRNG"
#endif

static struct rt_mutex s_AES_mutex;
static struct rt_mutex s_TDES_mutex;
static struct rt_mutex s_SHA_mutex;

#if !defined(BSP_USING_TRNG)
    static struct rt_mutex s_PRNG_mutex;
    static volatile int s_PRNG_done;
#endif

static volatile int s_AES_done;
static volatile int s_TDES_done;
static volatile int s_SHA_done;

static rt_err_t nu_crypto_init(void)
{
    /* Enable Crypto engine interrupt */
    NVIC_EnableIRQ(CRPT_IRQn);

    AES_ENABLE_INT(CRPT);
    TDES_ENABLE_INT(CRPT);
    SHA_ENABLE_INT(CRPT);

    //init cipher mutex
    rt_mutex_init(&s_AES_mutex, NU_HWCRYPTO_AES_NAME, RT_IPC_FLAG_FIFO);
    rt_mutex_init(&s_TDES_mutex, NU_HWCRYPTO_TDES_NAME, RT_IPC_FLAG_FIFO);
    rt_mutex_init(&s_SHA_mutex, NU_HWCRYPTO_SHA_NAME, RT_IPC_FLAG_FIFO);
#if !defined(BSP_USING_TRNG)
    PRNG_ENABLE_INT(CRPT);
    rt_mutex_init(&s_PRNG_mutex, NU_HWCRYPTO_PRNG_NAME, RT_IPC_FLAG_FIFO);
#endif

    return RT_EOK;
}

//Crypto engine IRQ handler

void CRYPTO_IRQHandler()
{
    if (AES_GET_INT_FLAG(CRPT))
    {
        s_AES_done = 1;
        AES_CLR_INT_FLAG(CRPT);
    }

    if (TDES_GET_INT_FLAG(CRPT))
    {
        s_TDES_done = 1;
        TDES_CLR_INT_FLAG(CRPT);
    }

    if (SHA_GET_INT_FLAG(CRPT))
    {
        s_SHA_done = 1;
        SHA_CLR_INT_FLAG(CRPT);
    }

#if !defined(BSP_USING_TRNG)
    if (PRNG_GET_INT_FLAG(CRPT))
    {
        s_PRNG_done = 1;
        PRNG_CLR_INT_FLAG(CRPT);
    }
#endif
}

static rt_err_t nu_aes_crypt_run(
    rt_bool_t bEncrypt,
    uint32_t u32OpMode,
    uint8_t *pu8Key,
    uint32_t u32KeySize,
    uint8_t *pu8IV,
    uint8_t *pu8InData,
    uint8_t *pu8OutData,
    uint32_t u32DataLen
)
{
    uint32_t au32SwapKey[8];
    uint32_t au32SwapIV[4];

    au32SwapKey[0] = nu_get32_be(&pu8Key[0]);
    au32SwapKey[1] = nu_get32_be(&pu8Key[4]);
    au32SwapKey[2] = nu_get32_be(&pu8Key[8]);
    au32SwapKey[3] = nu_get32_be(&pu8Key[12]);

    if ((u32KeySize == AES_KEY_SIZE_192) || (u32KeySize == AES_KEY_SIZE_256))
    {
        au32SwapKey[4] = nu_get32_be(&pu8Key[16]);
        au32SwapKey[5] = nu_get32_be(&pu8Key[20]);
    }

    if (u32KeySize == AES_KEY_SIZE_256)
    {
        au32SwapKey[6] = nu_get32_be(&pu8Key[24]);
        au32SwapKey[7] = nu_get32_be(&pu8Key[28]);
    }

    au32SwapIV[0] = nu_get32_be(&pu8IV[0]);
    au32SwapIV[1] = nu_get32_be(&pu8IV[4]);
    au32SwapIV[2] = nu_get32_be(&pu8IV[8]);
    au32SwapIV[3] = nu_get32_be(&pu8IV[12]);

    rt_mutex_take(&s_AES_mutex, RT_WAITING_FOREVER);

    //Using Channel 0
    AES_Open(CRPT, 0, bEncrypt, u32OpMode, u32KeySize, AES_IN_OUT_SWAP);
    AES_SetKey(CRPT, 0, (uint32_t *)au32SwapKey, u32KeySize);
    AES_SetInitVect(CRPT, 0, (uint32_t *)au32SwapIV);

    //Setup AES DMA
    AES_SetDMATransfer(CRPT, 0, (uint32_t)pu8InData, (uint32_t)pu8OutData, u32DataLen);
    AES_CLR_INT_FLAG(CRPT);
    //Start AES encryption/decryption
    s_AES_done = 0;
    AES_Start(CRPT, 0, CRYPTO_DMA_ONE_SHOT);
    while (!s_AES_done) {};

    rt_mutex_release(&s_AES_mutex);

    return RT_EOK;
}

#if !defined(BSP_USING_TRNG)
//Using PRNG instead of TRNG
static void nu_prng_open(uint32_t u32Seed)
{
    rt_mutex_take(&s_PRNG_mutex, RT_WAITING_FOREVER);

    //Open PRNG 64 bits. But always return 32 bits
    PRNG_Open(CRPT, PRNG_KEY_SIZE_64, PRNG_SEED_RELOAD, u32Seed);

    rt_mutex_release(&s_PRNG_mutex);
}

static rt_uint32_t nu_prng_run(void)
{
    uint32_t au32RNGValue[2];

    rt_mutex_take(&s_PRNG_mutex, RT_WAITING_FOREVER);

    s_PRNG_done = 0;
    PRNG_Start(CRPT);
    while (!s_PRNG_done) {};

    PRNG_Read(CRPT, au32RNGValue);

    rt_mutex_release(&s_PRNG_mutex);
    return au32RNGValue[0];
}

#endif

static rt_err_t nu_aes_crypt(struct hwcrypto_symmetric *symmetric_ctx, struct hwcrypto_symmetric_info *symmetric_info)
{
    uint32_t u32AESOpMode;
    uint32_t u32AESKeySize;
    unsigned char *in, *out;

    if ((symmetric_info->length % 16) != 0)
    {
        return -RT_EINVAL;
    }

    //Checking key length
    if (symmetric_ctx->key_bitlen == 128)
    {
        u32AESKeySize = AES_KEY_SIZE_128;
    }
    else if (symmetric_ctx->key_bitlen == 192)
    {
        u32AESKeySize = AES_KEY_SIZE_192;
    }
    else if (symmetric_ctx->key_bitlen == 256)
    {
        u32AESKeySize = AES_KEY_SIZE_256;
    }
    else
    {
        return -RT_EINVAL;
    }

    //Select AES operation mode
    switch (symmetric_ctx->parent.type & (HWCRYPTO_MAIN_TYPE_MASK | HWCRYPTO_SUB_TYPE_MASK))
    {
    case HWCRYPTO_TYPE_AES_ECB:
        u32AESOpMode = AES_MODE_ECB;
        break;
    case HWCRYPTO_TYPE_AES_CBC:
        u32AESOpMode = AES_MODE_CBC;
        break;
    case HWCRYPTO_TYPE_AES_CFB:
        u32AESOpMode = AES_MODE_CFB;
        break;
    case HWCRYPTO_TYPE_AES_OFB:
        u32AESOpMode = AES_MODE_OFB;
        break;
    case HWCRYPTO_TYPE_AES_CTR:
        u32AESOpMode = AES_MODE_CTR;
        break;
    default :
        return -RT_ERROR;
    }

    in = (unsigned char *)symmetric_info->in;
    out = (unsigned char *)symmetric_info->out;

#if !defined(NU_HWCRYPTO_NOT_ALIGN_CHECK)
    unsigned char in_align_flag = 0;
    unsigned char out_align_flag = 0;

    //Checking in/out data buffer address alignment or not
    if (((rt_uint32_t)in % 4) != 0)
    {
        in = rt_malloc(symmetric_info->length);
        if (in == RT_NULL)
        {
            LOG_E("fun[%s] memory allocate %d bytes failed!", __FUNCTION__, symmetric_info->length);
            return -RT_ENOMEM;
        }

        memcpy(in, symmetric_info->in, symmetric_info->length);
        in_align_flag = 1;
    }

    if (((rt_uint32_t)out % 4) != 0)
    {
        out = rt_malloc(symmetric_info->length);
        if (out == RT_NULL)
        {
            if (in_align_flag)
                rt_free(in);
            LOG_E("fun[%s] memory allocate %d bytes failed!", __FUNCTION__, symmetric_info->length);
            return -RT_ENOMEM;
        }

        out_align_flag = 1;
    }
#endif

    nu_aes_crypt_run(symmetric_info->mode == HWCRYPTO_MODE_ENCRYPT ? TRUE : FALSE, u32AESOpMode, symmetric_ctx->key, u32AESKeySize, symmetric_ctx->iv, in, out, symmetric_info->length);

#if !defined(NU_HWCRYPTO_NOT_ALIGN_CHECK)
    if (out_align_flag)
    {
        memcpy(symmetric_info->out, out, symmetric_info->length);
        rt_free(out);
    }

    if (in_align_flag)
    {
        rt_free(in);
    }
#endif

    return RT_EOK;
}

static rt_err_t nu_des_crypt_run(
    rt_bool_t bEncrypt,
    uint32_t u32OpMode,
    uint8_t *pu8Key,
    uint32_t u32KeySize,
    uint8_t *pu8IV,
    uint8_t *pu8InData,
    uint8_t *pu8OutData,
    uint32_t u32DataLen
)
{
    uint32_t au32SwapKey[3][2];
    uint32_t au32SwapIV[2];

    au32SwapKey[0][0] = nu_get32_be(&pu8Key[0]);
    au32SwapKey[0][1] = nu_get32_be(&pu8Key[4]);
    au32SwapKey[1][0] = nu_get32_be(&pu8Key[8]);
    au32SwapKey[1][1] = nu_get32_be(&pu8Key[12]);

    if (u32KeySize == NU_HWCRYPTO_DES_3KEYS)
    {
        au32SwapKey[2][0] = nu_get32_be(&pu8Key[16]);
        au32SwapKey[2][1] = nu_get32_be(&pu8Key[20]);
    }

    au32SwapIV[0] = nu_get32_be(&pu8IV[0]);
    au32SwapIV[1] = nu_get32_be(&pu8IV[4]);

    rt_mutex_take(&s_TDES_mutex, RT_WAITING_FOREVER);

    //Using Channel 0
    TDES_Open(CRPT, 0, bEncrypt, (u32OpMode & CRPT_TDES_CTL_TMODE_Msk), u32KeySize, u32OpMode, TDES_IN_OUT_WHL_SWAP);
    TDES_SetKey(CRPT, 0, au32SwapKey);
    TDES_SetInitVect(CRPT, 0, au32SwapIV[0], au32SwapIV[1]);

    //Setup TDES DMA
    TDES_SetDMATransfer(CRPT, 0, (uint32_t)pu8InData, (uint32_t)pu8OutData, u32DataLen);
    TDES_CLR_INT_FLAG(CRPT);
    //Start TDES encryption/decryption
    s_TDES_done = 0;
    TDES_Start(CRPT, 0, CRYPTO_DMA_ONE_SHOT);
    while (!s_TDES_done) {};

    rt_mutex_release(&s_TDES_mutex);

    return RT_EOK;
}

static rt_err_t nu_des_crypt(struct hwcrypto_symmetric *symmetric_ctx, struct hwcrypto_symmetric_info *symmetric_info)
{
    uint32_t u32DESOpMode;
    uint32_t u32DESKeySize;
    unsigned char *in, *out;

    if ((symmetric_info->length % 8) != 0)
    {
        return -RT_EINVAL;
    }

    //Checking key length
    if (symmetric_ctx->key_bitlen == 128 || symmetric_ctx->key_bitlen == 64)
    {
        u32DESKeySize = NU_HWCRYPTO_DES_NO3KEYS;
    }
    else if (symmetric_ctx->key_bitlen == 192)
    {
        u32DESKeySize = NU_HWCRYPTO_DES_3KEYS;
    }
    else
    {
        return -RT_EINVAL;
    }

    //Select DES operation mode
    switch (symmetric_ctx->parent.type & (HWCRYPTO_MAIN_TYPE_MASK | HWCRYPTO_SUB_TYPE_MASK))
    {
    case HWCRYPTO_TYPE_DES_ECB:
        u32DESOpMode = DES_MODE_ECB;
        break;
    case HWCRYPTO_TYPE_DES_CBC:
        u32DESOpMode = DES_MODE_CBC;
        break;
    case HWCRYPTO_TYPE_3DES_ECB:
        u32DESOpMode = TDES_MODE_ECB;
        break;
    case HWCRYPTO_TYPE_3DES_CBC:
        u32DESOpMode = TDES_MODE_CBC;
        break;
    default :
        return -RT_ERROR;
    }

    in = (unsigned char *)symmetric_info->in;
    out = (unsigned char *)symmetric_info->out;

#if !defined(NU_HWCRYPTO_NOT_ALIGN_CHECK)
    unsigned char in_align_flag = 0;
    unsigned char out_align_flag = 0;

    //Checking in/out data buffer address alignment or not
    if (((rt_uint32_t)in % 4) != 0)
    {
        in = rt_malloc(symmetric_info->length);
        if (in == RT_NULL)
        {
            LOG_E("fun[%s] memory allocate %d bytes failed!", __FUNCTION__, symmetric_info->length);
            return -RT_ENOMEM;
        }

        memcpy(in, symmetric_info->in, symmetric_info->length);
        in_align_flag = 1;
    }

    if (((rt_uint32_t)out % 4) != 0)
    {
        out = rt_malloc(symmetric_info->length);
        if (out == RT_NULL)
        {
            if (in_align_flag)
                rt_free(in);
            LOG_E("fun[%s] memory allocate %d bytes failed!", __FUNCTION__, symmetric_info->length);
            return -RT_ENOMEM;
        }

        out_align_flag = 1;
    }
#endif

    nu_des_crypt_run(symmetric_info->mode == HWCRYPTO_MODE_ENCRYPT ? TRUE : FALSE, u32DESOpMode, symmetric_ctx->key, u32DESKeySize, symmetric_ctx->iv, in, out, symmetric_info->length);

#if !defined(NU_HWCRYPTO_NOT_ALIGN_CHECK)
    if (out_align_flag)
    {
        memcpy(symmetric_info->out, out, symmetric_info->length);
        rt_free(out);
    }

    if (in_align_flag)
    {
        rt_free(in);
    }
#endif

    return RT_EOK;
}

static rt_err_t nu_sha_hash_run(
    uint32_t u32OpMode,
    uint8_t *pu8InData,
    uint32_t u32DataLen
)
{
    rt_mutex_take(&s_SHA_mutex, RT_WAITING_FOREVER);

    //Using SHA
    SHA_Open(CRPT, u32OpMode, SHA_IN_OUT_SWAP, 0);

    //Setup SHA DMA
    SHA_SetDMATransfer(CRPT, (uint32_t)pu8InData, u32DataLen);
    SHA_CLR_INT_FLAG(CRPT);
    //Start SHA
    s_SHA_done = 0;
    SHA_Start(CRPT, CRYPTO_DMA_ONE_SHOT);
    while (!s_SHA_done) {};

    rt_mutex_release(&s_SHA_mutex);

    return RT_EOK;
}

static rt_err_t nu_sha_update(struct hwcrypto_hash *hash_ctx, const rt_uint8_t *in, rt_size_t length)
{
    uint32_t u32SHAOpMode;
    unsigned char *nu_in;

    //Select SHA operation mode
    switch (hash_ctx->parent.type & (HWCRYPTO_MAIN_TYPE_MASK | HWCRYPTO_SUB_TYPE_MASK))
    {
    case HWCRYPTO_TYPE_SHA1:
        u32SHAOpMode = SHA_MODE_SHA1;
        break;
    case HWCRYPTO_TYPE_SHA224:
        u32SHAOpMode = SHA_MODE_SHA224;
        break;
    case HWCRYPTO_TYPE_SHA256:
        u32SHAOpMode = SHA_MODE_SHA256;
        break;
    case HWCRYPTO_TYPE_SHA384:
        u32SHAOpMode = SHA_MODE_SHA384;
        break;
    case HWCRYPTO_TYPE_SHA512:
        u32SHAOpMode = SHA_MODE_SHA512;
        break;
    default :
        return -RT_ERROR;
    }

    nu_in = (unsigned char *)in;

#if !defined(NU_HWCRYPTO_NOT_ALIGN_CHECK)
    unsigned char in_align_flag = 0;

    //Checking in data buffer address alignment or not
    if (((rt_uint32_t)nu_in % 4) != 0)
    {
        nu_in = rt_malloc(length);
        if (nu_in == RT_NULL)
        {
            LOG_E("fun[%s] memory allocate %d bytes failed!", __FUNCTION__, length);
            return -RT_ENOMEM;
        }

        memcpy(nu_in, in, length);
        in_align_flag = 1;
    }
#endif

    nu_sha_hash_run(u32SHAOpMode, nu_in, length);

#if !defined(NU_HWCRYPTO_NOT_ALIGN_CHECK)
    if (in_align_flag)
    {
        rt_free(nu_in);
    }
#endif

    return RT_EOK;
}

static rt_err_t nu_sha_finish(struct hwcrypto_hash *hash_ctx, rt_uint8_t *out, rt_size_t length)
{
    unsigned char *nu_out;

    //Check SHA Hash value buffer length
    switch (hash_ctx->parent.type & (HWCRYPTO_MAIN_TYPE_MASK | HWCRYPTO_SUB_TYPE_MASK))
    {
    case HWCRYPTO_TYPE_SHA1:
        if (length < 5UL)
        {
            return -RT_EINVAL;
        }
        break;
    case HWCRYPTO_TYPE_SHA224:
        if (length < 7UL)
        {
            return -RT_EINVAL;
        }
        break;
    case HWCRYPTO_TYPE_SHA256:
        if (length < 8UL)
        {
            return -RT_EINVAL;
        }
        break;
    case HWCRYPTO_TYPE_SHA384:
        if (length < 12UL)
        {
            return -RT_EINVAL;
        }
        break;
    case HWCRYPTO_TYPE_SHA512:
        if (length < 16UL)
        {
            return -RT_EINVAL;
        }
        break;
    default :
        return -RT_ERROR;
    }

    nu_out = (unsigned char *)out;

#if !defined(NU_HWCRYPTO_NOT_ALIGN_CHECK)
    unsigned char out_align_flag = 0;

    //Checking out data buffer address alignment or not
    if (((rt_uint32_t)nu_out % 4) != 0)
    {
        nu_out = rt_malloc(length);
        if (nu_out == RT_NULL)
        {
            LOG_E("fun[%s] memory allocate %d bytes failed!", __FUNCTION__, length);
            return -RT_ENOMEM;
        }

        out_align_flag = 1;
    }
#endif

    SHA_Read(CRPT, (uint32_t *)nu_out);

#if !defined(NU_HWCRYPTO_NOT_ALIGN_CHECK)
    if (out_align_flag)
    {
        memcpy(out, out, length);
        rt_free(out);
    }
#endif

    return RT_EOK;
}

#if !defined(BSP_USING_TRNG)
static rt_uint32_t nu_prng_rand(struct hwcrypto_rng *ctx)
{
    return nu_prng_run();
}

#endif

static const struct hwcrypto_symmetric_ops nu_aes_ops =
{
    .crypt = nu_aes_crypt,
};

static const struct hwcrypto_symmetric_ops nu_des_ops =
{
    .crypt = nu_des_crypt,
};

static const struct hwcrypto_hash_ops nu_sha_ops =
{
    .update = nu_sha_update,
    .finish = nu_sha_finish,
};

#endif

/* CRC operation ------------------------------------------------------------*/
#if defined(BSP_USING_CRC)

static const struct hwcrypto_crc_ops nu_crc_ops =
{
    .update = nu_crc_update,
};

#endif

/* TRNG operation ------------------------------------------------------------*/
#if defined(BSP_USING_TRNG)

static const struct hwcrypto_rng_ops nu_rng_ops =
{
    .update = nu_trng_rand,
};

#elif defined(BSP_USING_CRYPTO)

static const struct hwcrypto_rng_ops nu_rng_ops =
{
    .update = nu_prng_rand,
};

#endif

/* Register crypto interface ----------------------------------------------------------*/
static rt_err_t nu_hwcrypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_TRNG)
    case HWCRYPTO_TYPE_RNG:
    {
        ctx->contex = RT_NULL;
        //Setup RNG operation
        ((struct hwcrypto_rng *)ctx)->ops = &nu_rng_ops;
        break;
    }
#endif /* BSP_USING_TRNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        ctx->contex = RT_NULL;
        //Setup CRC operation
        ((struct hwcrypto_crc *)ctx)->ops = &nu_crc_ops;
        break;
    }
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_CRYPTO)
    case HWCRYPTO_TYPE_AES:
    {
        ctx->contex = RT_NULL;
        //Setup AES operation
        ((struct hwcrypto_symmetric *)ctx)->ops = &nu_aes_ops;
        break;
    }

    case HWCRYPTO_TYPE_DES:
    {
        ctx->contex = RT_NULL;
        //Setup DES operation
        ((struct hwcrypto_symmetric *)ctx)->ops = &nu_des_ops;
        break;
    }

    case HWCRYPTO_TYPE_3DES:
    {
        ctx->contex = RT_NULL;
        //Setup 3DES operation
        ((struct hwcrypto_symmetric *)ctx)->ops = &nu_des_ops;
        break;
    }


    case HWCRYPTO_TYPE_SHA1:
    {
        ctx->contex = RT_NULL;
        //Setup SHA1 operation
        ((struct hwcrypto_hash *)ctx)->ops = &nu_sha_ops;
        break;
    }

    case HWCRYPTO_TYPE_SHA2:
    {
        ctx->contex = RT_NULL;
        //Setup SHA2 operation
        ((struct hwcrypto_hash *)ctx)->ops = &nu_sha_ops;
        break;
    }

#if !defined(BSP_USING_TRNG)
    case HWCRYPTO_TYPE_RNG:
    {
        ctx->contex = RT_NULL;
        ((struct hwcrypto_rng *)ctx)->ops = &nu_rng_ops;
#if defined(NU_PRNG_USE_SEED)
        nu_prng_open(NU_PRNG_SEED_VALUE);
#else
        nu_prng_open(rt_tick_get());
#endif
        break;
    }
#endif /* !BSP_USING_TRNG */

#endif /* BSP_USING_CRYPTO */


    default:
        res = -RT_ERROR;
        break;
    }

    return res;
}

static void nu_hwcrypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    if (ctx->contex)
        rt_free(ctx->contex);
}

static rt_err_t nu_hwcrypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t res = RT_EOK;

    if (des->contex && src->contex)
    {
        rt_memcpy(des->contex, src->contex, sizeof(struct rt_hwcrypto_ctx));
    }
    else
        return -RT_EINVAL;
    return res;
}

static void nu_hwcrypto_reset(struct rt_hwcrypto_ctx *ctx)
{
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if !defined(BSP_USING_TRNG)
    case HWCRYPTO_TYPE_RNG:
    {
#if defined(NU_PRNG_USE_SEED)
        nu_prng_open(NU_PRNG_SEED_VALUE);
#else
        nu_prng_open(rt_tick_get());
#endif
        break;
    }
#endif /* !BSP_USING_TRNG */

    default:
        break;
    }
}

/* Init and register nu_hwcrypto_dev */

int nu_hwcrypto_device_init(void)
{
    static struct rt_hwcrypto_device nu_hwcrypto_dev;

    nu_hwcrypto_dev.ops = &nu_hwcrypto_ops;
    nu_hwcrypto_dev.id = 0;
    nu_hwcrypto_dev.user_data = &nu_hwcrypto_dev;

#if defined(BSP_USING_CRYPTO)
    nu_crypto_init();
#endif

#if defined(BSP_USING_CRC)
    nu_crc_init();
#endif

#if defined(BSP_USING_TRNG)
    nu_trng_init();
#endif

    // register hwcrypto operation
    if (rt_hwcrypto_register(&nu_hwcrypto_dev, RT_HWCRYPTO_DEFAULT_NAME) != RT_EOK)
    {
        return -1;
    }

    return 0;
}
INIT_DEVICE_EXPORT(nu_hwcrypto_device_init);

#endif //#if ((defined(BSP_USING_CRYPTO) || defined(BSP_USING_TRNG) || defined(BSP_USING_CRC)) && defined(RT_USING_HWCRYPTO))
