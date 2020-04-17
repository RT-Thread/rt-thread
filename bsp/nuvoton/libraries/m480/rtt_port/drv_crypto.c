/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of Nuvoton Technology Corp. nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Change Logs:
* Date            Author           Notes
* 2020-3-3        CHChen               First version
*
* Reference w60x/drivers/drv_crypto.c implementation
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_CRYPTO) || defined(BSP_USING_TRNG) || defined(BSP_USING_CRC)
#include <string.h>

#include <rtdevice.h>
#include <rtdbg.h>
#include "NuMicro.h"

#if defined(BSP_USING_TRNG)
    #include "drv_trng.h"
#endif

#if defined(BSP_USING_CRC)
    #include "drv_crc.h"
#endif

/* Private typedef --------------------------------------------------------------*/
struct nu_hwcrypto_dev
{
    struct rt_hwcrypto_device dev;
};


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

#define NU_HWCRYPTO_AES_NAME    "nu_AES"
#define NU_HWCRYPTO_TDES_NAME   "nu_TDES"
#define NU_HWCRYPTO_SHA_NAME    "nu_SHA"
#if !defined(BSP_USING_TRNG)
    #define NU_HWCRYPTO_PRNG_NAME   "nu_SHA"
#endif

static struct rt_mutex s_AES_mutex;
static struct rt_mutex s_TDES_mutex;
static struct rt_mutex s_SHA_mutex;

#if !defined(BSP_USING_TRNG)
    static struct rt_mutex s_PRNG_mutex;
#endif

static struct rt_semaphore s_AES_Sem;
static struct rt_semaphore s_TDES_Sem;
static struct rt_semaphore s_SHA_Sem;

#if !defined(BSP_USING_TRNG)
    static struct rt_semaphore s_PRNG_Sem;
#endif

static rt_err_t nu_crypto_init(void)
{

    /* Enable Crypto engine interrupt */
    NVIC_EnableIRQ(CRPT_IRQn);

    //init cipher mutex
    rt_mutex_init(&s_AES_mutex, NU_HWCRYPTO_AES_NAME, RT_IPC_FLAG_FIFO);
    rt_mutex_init(&s_TDES_mutex, NU_HWCRYPTO_TDES_NAME, RT_IPC_FLAG_FIFO);
    rt_mutex_init(&s_SHA_mutex, NU_HWCRYPTO_SHA_NAME, RT_IPC_FLAG_FIFO);
#if !defined(BSP_USING_TRNG)
    rt_mutex_init(&s_PRNG_mutex, NU_HWCRYPTO_PRNG_NAME, RT_IPC_FLAG_FIFO);
#endif

    //init cipher semphore
    rt_sem_init(&s_AES_Sem, NU_HWCRYPTO_AES_NAME, 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&s_TDES_Sem, NU_HWCRYPTO_TDES_NAME, 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&s_SHA_Sem, NU_HWCRYPTO_SHA_NAME, 0, RT_IPC_FLAG_FIFO);
#if !defined(BSP_USING_TRNG)
    rt_sem_init(&s_PRNG_Sem,    NU_HWCRYPTO_PRNG_NAME, 0, RT_IPC_FLAG_FIFO);
#endif
    return RT_EOK;
}

//Crypto engine IRQ handler

void CRYPTO_IRQHandler()
{
    if (AES_GET_INT_FLAG(CRPT))
    {
        //Wake up AES semphore
        rt_sem_release(&s_AES_Sem);
        AES_CLR_INT_FLAG(CRPT);
    }

    if (TDES_GET_INT_FLAG(CRPT))
    {
        TDES_CLR_INT_FLAG(CRPT);
    }

    if (SHA_GET_INT_FLAG(CRPT))
    {
        SHA_CLR_INT_FLAG(CRPT);
    }

#if !defined(BSP_USING_TRNG)
    if (PRNG_GET_INT_FLAG(CRPT))
    {
        //Wakeup PRNG semphore
        rt_sem_release(&s_PRNG_Sem);
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

    au32SwapKey[0] = pu8Key[0] << 24 | pu8Key[1] << 16 | pu8Key[2] << 8 | pu8Key[3];
    au32SwapKey[1] = pu8Key[4] << 24 | pu8Key[5] << 16 | pu8Key[6] << 8 | pu8Key[7];
    au32SwapKey[2] = pu8Key[8] << 24 | pu8Key[9] << 16 | pu8Key[10] << 8 | pu8Key[11];
    au32SwapKey[3] = pu8Key[12] << 24 | pu8Key[13] << 16 | pu8Key[14] << 8 | pu8Key[15];

    if ((u32KeySize == AES_KEY_SIZE_192) || (u32KeySize == AES_KEY_SIZE_256))
    {
        au32SwapKey[4] = pu8Key[16] << 24 | pu8Key[17] << 16 | pu8Key[18] << 8 | pu8Key[19];
        au32SwapKey[5] = pu8Key[20] << 24 | pu8Key[21] << 16 | pu8Key[22] << 8 | pu8Key[23];
    }

    if (u32KeySize == AES_KEY_SIZE_256)
    {
        au32SwapKey[6] = pu8Key[24] << 24 | pu8Key[25] << 16 | pu8Key[26] << 8 | pu8Key[27];
        au32SwapKey[7] = pu8Key[28] << 24 | pu8Key[29] << 16 | pu8Key[30] << 8 | pu8Key[31];
    }

    au32SwapIV[0] = pu8IV[0] << 24 | pu8IV[1] << 16 | pu8IV[2] << 8 | pu8IV[3];
    au32SwapIV[1] = pu8IV[4] << 24 | pu8IV[5] << 16 | pu8IV[6] << 8 | pu8IV[7];
    au32SwapIV[2] = pu8IV[8] << 24 | pu8IV[9] << 16 | pu8IV[10] << 8 | pu8IV[11];
    au32SwapIV[3] = pu8IV[12] << 24 | pu8IV[13] << 16 | pu8IV[14] << 8 | pu8IV[15];


    rt_mutex_take(&s_AES_mutex, RT_WAITING_FOREVER);
    AES_ENABLE_INT(CRPT);

    //Using Channel 0
    AES_Open(CRPT, 0, bEncrypt, u32OpMode, u32KeySize, AES_IN_OUT_SWAP);
    AES_SetKey(CRPT, 0, (uint32_t *)au32SwapKey, u32KeySize);
    AES_SetInitVect(CRPT, 0, (uint32_t *)au32SwapIV);

    //Setup AES DMA
    AES_SetDMATransfer(CRPT, 0, (uint32_t)pu8InData, (uint32_t)pu8OutData, u32DataLen);
    AES_CLR_INT_FLAG(CRPT);
    //Start AES encryption/decryption
    AES_Start(CRPT, 0, CRYPTO_DMA_ONE_SHOT);

    //Wait semphore wake up
    rt_sem_take(&s_AES_Sem, RT_WAITING_FOREVER);
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
    PRNG_ENABLE_INT(CRPT);

    PRNG_Start(CRPT);

    //Wait semphore wake up
    rt_sem_take(&s_PRNG_Sem, RT_WAITING_FOREVER);
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
    unsigned char in_align_flag = 0;
    unsigned char out_align_flag = 0;

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

    if (symmetric_info->mode == HWCRYPTO_MODE_ENCRYPT)
    {
        nu_aes_crypt_run(TRUE, u32AESOpMode, symmetric_ctx->key, u32AESKeySize, symmetric_ctx->iv, in, out, symmetric_info->length);
    }
    else
    {
        nu_aes_crypt_run(FALSE, u32AESOpMode, symmetric_ctx->key, u32AESKeySize, symmetric_ctx->iv, in, out, symmetric_info->length);
    }

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
        /* TODO
        */
        break;
    }

    case HWCRYPTO_TYPE_3DES:
    {
        /* TODO
        */
        break;
    }


    case HWCRYPTO_TYPE_SHA1:
    {
        /* TODO
        */
        break;
    }

    case HWCRYPTO_TYPE_SHA2:
    {
        /* TODO
        */
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
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_TRNG)
    case HWCRYPTO_TYPE_RNG:
    {
        break;
    }
#endif /* BSP_USING_TRNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        break;
    }
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_CRYPTO)
    case HWCRYPTO_TYPE_AES:
    {
        break;
    }

    case HWCRYPTO_TYPE_DES:
    {
        /* TODO
        */
        break;
    }

    case HWCRYPTO_TYPE_3DES:
    {
        /* TODO
        */
        break;
    }


    case HWCRYPTO_TYPE_SHA1:
    {
        /* TODO
        */
        break;
    }

    case HWCRYPTO_TYPE_SHA2:
    {
        /* TODO
        */
        break;
    }

#if !defined(BSP_USING_TRNG)
    case HWCRYPTO_TYPE_RNG:
    {
        break;
    }
#endif /* !BSP_USING_TRNG */

#endif /* BSP_USING_CRYPTO */

    default:
        break;
    }

    if (ctx->contex)
        rt_free(ctx->contex);
}

static rt_err_t nu_hwcrypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t res = RT_EOK;

    switch (src->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_TRNG)
    case HWCRYPTO_TYPE_RNG:
    {
        break;
    }
#endif /* BSP_USING_TRNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        break;
    }
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_CRYPTO)
    case HWCRYPTO_TYPE_AES:
    {
        break;
    }

    case HWCRYPTO_TYPE_DES:
    {
        /* TODO
        */
        break;
    }

    case HWCRYPTO_TYPE_3DES:
    {
        /* TODO
        */
        break;
    }

    case HWCRYPTO_TYPE_SHA1:
    {
        /* TODO
        */
        break;
    }

    case HWCRYPTO_TYPE_SHA2:
    {
        /* TODO
        */
        break;
    }

#if !defined(BSP_USING_TRNG)
    case HWCRYPTO_TYPE_RNG:
    {
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

static void nu_hwcrypto_reset(struct rt_hwcrypto_ctx *ctx)
{
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_TRNG)
    case HWCRYPTO_TYPE_RNG:
    {
        break;
    }
#endif /* BSP_USING_TRNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        break;
    }
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRYPTO)
    case HWCRYPTO_TYPE_AES:
    {
        break;
    }

    case HWCRYPTO_TYPE_DES:
    {
        /* TODO
        */
        break;
    }

    case HWCRYPTO_TYPE_3DES:
    {
        /* TODO
        */
        break;
    }


    case HWCRYPTO_TYPE_SHA1:
    {
        /* TODO
        */
        break;
    }

    case HWCRYPTO_TYPE_SHA2:
    {
        /* TODO
        */
        break;
    }

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

#endif /* BSP_USING_CRYPTO */

    default:
        break;
    }
}


/* Init and register nu_crypto_dev */

int nu_hwcrypto_device_init(void)
{
    static struct nu_hwcrypto_dev nu_hwcrypto_dev;

    nu_hwcrypto_dev.dev.ops = &nu_hwcrypto_ops;
    nu_hwcrypto_dev.dev.id = 0;
    nu_hwcrypto_dev.dev.user_data = &nu_hwcrypto_dev;

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
    if (rt_hwcrypto_register(&nu_hwcrypto_dev.dev, RT_HWCRYPTO_DEFAULT_NAME) != RT_EOK)
    {
        return -1;
    }

    return 0;
}
INIT_DEVICE_EXPORT(nu_hwcrypto_device_init);

#endif //#if defined(BSP_USING_CRYPTO) || defined(BSP_USING_TRNG) || defined(BSP_USING_CRC) 
