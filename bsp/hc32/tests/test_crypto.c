/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>

#if defined(BSP_USING_HWCRYPTO)

#define ARR_SIZE(arr)               (sizeof(arr)/sizeof(*arr))
#define PRINT_DIGIT_ARR(arr)        do {                                       \
                                        rt_kprintf("%s: ", #arr);              \
                                        for(int i = 0; i < ARR_SIZE(arr); i++) \
                                            rt_kprintf("%d ", arr[i]);         \
                                            rt_kprintf("\n");                  \
                                    } while(0)

#define WDT_DEVICE_NAME    "crypto"

static void _crypto_cmd_print_usage(void)
{
#if defined(BSP_USING_RNG)
    rt_kprintf("crypto_sample [option] \n");
    rt_kprintf("  rang: get random number from rang module. \n");
    rt_kprintf("    e.g. msh >crypto_sample rang get \n");
#endif

#if defined(BSP_USING_CRC)
    rt_kprintf("crypto_sample [option] \n");
    rt_kprintf("  crc: test crc module. \n");
    rt_kprintf("    e.g. msh >crypto_sample crc 16/32 \n");
#endif

#if defined(BSP_USING_AES)
    rt_kprintf("crypto_sample [option] \n");
    rt_kprintf("  aes: test aes module. \n");
#if defined(HC32F460)
    rt_kprintf("    e.g. msh >crypto_sample aes 128 \n");
#elif defined (HC32F4A0) || defined (HC32F448) || defined (HC32F472)
    rt_kprintf("    e.g. msh >crypto_sample aes 128/192/256 \n");
#endif
#endif

#if defined(BSP_USING_HASH)
    rt_kprintf("crypto_sample [option] \n");
    rt_kprintf("  hash: test hash module. \n");
    rt_kprintf("    e.g. msh >crypto_sample hash test \n");
#endif
}

#if defined(BSP_USING_CRC)
#define CRC16_WIDTH    16U
#define CRC32_WIDTH    32U
static void crc_test(rt_uint32_t width)
{
    rt_uint8_t temp_in[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    struct rt_hwcrypto_ctx *ctx;
    rt_uint32_t result = 0;
    /* CRC16_X25 */
    struct hwcrypto_crc_cfg cfg =
    {
        .last_val = 0xFFFFU,
        .poly = 0x1021U,
        .width = CRC16_WIDTH,
        .xorout = 0xFFFFU,
        .flags = CRC_FLAG_REFIN | CRC_FLAG_REFOUT,
    };
    /* CRC32 */
    if (width == CRC32_WIDTH)
    {
        cfg.last_val = 0xFFFFFFFFUL;
        cfg.poly = 0x04C11DB7UL;
        cfg.width = CRC32_WIDTH;
        cfg.xorout = 0xFFFFFFFFUL;
        cfg.flags = CRC_FLAG_REFIN | CRC_FLAG_REFOUT;
        ctx = rt_hwcrypto_crc_create(rt_hwcrypto_dev_default(), HWCRYPTO_CRC_CRC32);
    }
    else if (width == CRC16_WIDTH)
    {
        ctx = rt_hwcrypto_crc_create(rt_hwcrypto_dev_default(), HWCRYPTO_CRC_CRC16);
    }
    else
    {
        rt_kprintf("crc%d not support! \n", width);
        return;
    }

    rt_hwcrypto_crc_cfg(ctx, &cfg);

    rt_kprintf("temp_in: ");
    for (int i = 0; i < sizeof(temp_in) / 2U; i++)
    {
        rt_kprintf("%d ", temp_in[i]);
    }
    rt_kprintf("\n");
    result = rt_hwcrypto_crc_update(ctx, temp_in, sizeof(temp_in) / 2U);
    rt_kprintf("crc%d result: 0x%x \n", width, result);

    /* Accumulate test */
    PRINT_DIGIT_ARR(temp_in);
    result = rt_hwcrypto_crc_update(ctx, &temp_in[sizeof(temp_in) / 2U], sizeof(temp_in) / 2U);
    rt_kprintf("crc%d result: 0x%x \n", width, result);

    rt_hwcrypto_crc_destroy(ctx);
}
#endif

#if defined(BSP_USING_AES)
#define AES_DATA_LEN    32U      /* data of length must be a multiple of 16(128 Bit) */
static void aes_test(rt_uint16_t key_bitlen)
{
    rt_uint32_t result = RT_EOK;
    struct rt_hwcrypto_ctx *ctx;
    rt_uint8_t enc_out[AES_DATA_LEN];
    rt_uint8_t dec_out[AES_DATA_LEN];
    const char *enc_in = "abcdefghijksdwpa123456789asdfghj";
    const char *key128 = "1234567890abcdef";
    const char *key192 = "1234567890abcdefghijklmn";
    const char *key256 = "1234567890abcdefghijklmnopqrstuv";
    const char *key;

    ctx = rt_hwcrypto_symmetric_create(rt_hwcrypto_dev_default(), HWCRYPTO_TYPE_AES_ECB);
    if (ctx == RT_NULL)
    {
        rt_kprintf("create AES-CBC context err!");
        return;
    }
    switch (key_bitlen)
    {
    case 128:
        key = key128;
        break;
    case 192:
        key = key192;
        break;
    case 256:
        key = key256;
        break;
    default:
        key = key128;
        break;
    }
    result = rt_hwcrypto_symmetric_setkey(ctx, (rt_uint8_t *)key, key_bitlen);
    if (result == RT_EOK)
    {
        result = rt_hwcrypto_symmetric_crypt(ctx, HWCRYPTO_MODE_ENCRYPT, AES_DATA_LEN, (rt_uint8_t *)enc_in, enc_out);
        if (result != RT_EOK)
        {
            goto _exit;
        }

        rt_kprintf("aes src data:");
        for (int i = 0; i < AES_DATA_LEN; i++)
        {
            rt_kprintf("%c", enc_in[i]);
        }
        rt_kprintf("\n");

        rt_kprintf("aes enc data:");
        for (int i = 0; i < AES_DATA_LEN; i++)
        {
            rt_kprintf("%x ", enc_out[i]);
        }
        rt_kprintf("\n");

        result = rt_hwcrypto_symmetric_crypt(ctx, HWCRYPTO_MODE_DECRYPT, AES_DATA_LEN, (rt_uint8_t *)enc_out, dec_out);
        if (result != RT_EOK)
        {
            goto _exit;
        }
        rt_kprintf("aes dec data:");
        for (int i = 0; i < AES_DATA_LEN; i++)
        {
            rt_kprintf("%c", dec_out[i]);
        }
        rt_kprintf("\n");

_exit:
        rt_hwcrypto_symmetric_destroy(ctx);
    }
}
#endif

#if defined(BSP_USING_HASH)
#define HASH_SHA256_MSG_DIGEST_SIZE        (32U)
static void hash_sha256_test(void)
{
    const char *in = "0123456789abcdefghijklmnopqrstuvwxyz";
    uint8_t out[HASH_SHA256_MSG_DIGEST_SIZE];
    struct rt_hwcrypto_ctx *ctx;

    ctx = rt_hwcrypto_hash_create(rt_hwcrypto_dev_default(), HWCRYPTO_TYPE_SHA256);
    if (ctx != RT_NULL)
    {
        rt_hwcrypto_hash_update(ctx, (rt_uint8_t *)in, rt_strlen(in));
        rt_kprintf("hash in data:");
        for (int i = 0; i < rt_strlen(in); i++)
        {
            rt_kprintf("%c", in[i]);
        }
        rt_kprintf("\n");

        rt_hwcrypto_hash_finish(ctx, out, HASH_SHA256_MSG_DIGEST_SIZE);
        rt_kprintf("hash out data:");
        for (int i = 0; i < HASH_SHA256_MSG_DIGEST_SIZE; i++)
        {
            rt_kprintf("%x ", out[i]);
        }
        rt_kprintf("\n");
        rt_hwcrypto_hash_destroy(ctx);
    }
}
#endif

static int crypto_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;

    if (argc != 3)
    {
        goto _exit;
    }

#if defined(BSP_USING_RNG)
    if (!rt_strcmp("rang", argv[1]))
    {
        if (!rt_strcmp("get", argv[2]))
        {
            rt_uint32_t result = rt_hwcrypto_rng_update();
            rt_kprintf("random number = %x \n", result);
        }
        else
        {
            goto _exit;
        }
    }
#endif
#if defined(BSP_USING_CRC)
    else if (!rt_strcmp("crc", argv[1]))
    {
        rt_uint32_t width = atoi(argv[2]);
        if (width == CRC16_WIDTH || width == CRC32_WIDTH)
        {
            crc_test(width);
        }
        else
        {
            goto _exit;
        }
    }
#endif
#if defined(BSP_USING_AES)
    else if (!rt_strcmp("aes", argv[1]))
    {
        rt_uint32_t key_bitlen = atoi(argv[2]);
        if (key_bitlen == 128 || key_bitlen == 192 || key_bitlen == 256)
        {
            aes_test(key_bitlen);
        }
        else
        {
            goto _exit;
        }
    }
#endif
#if defined(BSP_USING_HASH)
    else if (!rt_strcmp("hash", argv[1]))
    {
        if (!rt_strcmp("test", argv[2]))
        {
            hash_sha256_test();
        }
        else
        {
            goto _exit;
        }
    }
#endif
    else
    {
        goto _exit;
    }

    return ret;

_exit:
    _crypto_cmd_print_usage();
    return -RT_ERROR;
}

MSH_CMD_EXPORT(crypto_sample, crypto [option]);

#endif
