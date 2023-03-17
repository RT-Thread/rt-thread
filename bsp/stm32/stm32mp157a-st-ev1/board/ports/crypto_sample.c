/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     thread-liu   first version
 */

#include <board.h>

#include "drv_crypto.h"
#include <hwcrypto.h>
#include <string.h>
#include <stdlib.h>

#if defined(BSP_USING_RNG)
static rt_err_t hw_rng_sample(int random_num)
{
    rt_err_t result = RT_EOK;
    int i = 0, num0 = 0, num1 = 0;

    if (random_num == 0)
    {
        return -RT_ERROR;
    }

    for (i = 0; i< random_num; i++)
    {
        result = rt_hwcrypto_rng_update();
        rt_kprintf("%d ", result);
        result%2 ? num1++ : num0++;
    }
    rt_kprintf("\neven numbers : %d, odd numbers: %d\n",num1, num0);

    return RT_EOK;
}
#endif

#if defined(BSP_USING_CRC)
static void hw_crc_sample(uint8_t *temp, int size)
{
    struct rt_hwcrypto_ctx *ctx;
    rt_uint32_t result = 0;

    struct hwcrypto_crc_cfg cfg =
    {
        .last_val = 0xFFFFFFFF,
        .poly     = 0x04C11DB7,
        .width    = 32,
        .xorout   = 0x00000000,
        .flags    = 0,
    };

    ctx = rt_hwcrypto_crc_create(rt_hwcrypto_dev_default(), HWCRYPTO_CRC_CRC32);
    rt_hwcrypto_crc_cfg(ctx, &cfg);

    result = rt_hwcrypto_crc_update(ctx, temp, size);

    rt_kprintf("crc result: %x \n", result);

    rt_hwcrypto_crc_destroy(ctx);
}
#endif

#if defined(BSP_USING_HASH)
static void hw_hash_sample()
{
    int i = 0;
    struct rt_hwcrypto_ctx *ctx = RT_NULL;
    const uint8_t hash_input[] = "RT-Thread was born in 2006, it is an open source, neutral, and community-based real-time operating system (RTOS).";

    static uint8_t sha1_output[20];
    static uint8_t sha1_except[20] = {0xff, 0x3c, 0x95, 0x54, 0x95, 0xf0, 0xad,
                                    0x02, 0x1b, 0xa8, 0xbc, 0xa2, 0x2e, 0xa5,
                                    0xb0, 0x62, 0x1b, 0xdf, 0x7f, 0xec};

    static uint8_t md5_output[16];
    static uint8_t md5_except[16] = {0x40, 0x86, 0x03, 0x80, 0x0d, 0x8c, 0xb9,
                                   0x4c, 0xd6, 0x7d, 0x28, 0xfc, 0xf6, 0xc3,
                                   0xac, 0x8b};

    static uint8_t sha224_output[28];
    static uint8_t sha224_except[28] = {0x6f, 0x62, 0x52, 0x7d, 0x80, 0xe6,
                                        0x9f, 0x82, 0x78, 0x7a, 0x46, 0x91,
                                        0xb0, 0xe9, 0x64, 0x89, 0xe6, 0xc3,
                                        0x6b, 0x7e, 0xcf, 0xca, 0x11, 0x42,
                                        0xc8, 0x77, 0x13, 0x79};
    static uint8_t sha256_output[32];
    static uint8_t sha256_except[32] = {0x74, 0x19, 0xb9, 0x0e, 0xd1, 0x46,
                                        0x37, 0x0a, 0x55, 0x18, 0x26, 0x6c,
                                        0x50, 0xd8, 0x71, 0x34, 0xfa, 0x1f,
                                        0x5f, 0x5f, 0xe4, 0x9a, 0xe9, 0x40,
                                        0x0a, 0x7d, 0xa0, 0x26, 0x1b, 0x86,
                                        0x67, 0x45};
    rt_kprintf("Hash Test start: \n");
    rt_kprintf("Hash Test string: \n");
    for (i = 0; i < sizeof(hash_input); i++)
    {
        rt_kprintf("%c", hash_input[i]);
    }
    rt_kprintf("\n");

    /* sh1 test*/
    ctx = rt_hwcrypto_hash_create(rt_hwcrypto_dev_default(), HWCRYPTO_TYPE_SHA1);
    if (ctx == RT_NULL)
    {
        rt_kprintf("create hash[%08x] context err!\n", HWCRYPTO_TYPE_SHA1);
        return ;
    }
    rt_kprintf("Create sha1 type success!\n");
    rt_kprintf("Except sha1 result: \n");
    for (i = 0; i < sizeof(sha1_except); i++)
    {
        rt_kprintf("%x ", sha1_except[i]);
    }
    rt_kprintf("\n");
    /* start sha1 */
    rt_hwcrypto_hash_update(ctx, hash_input, rt_strlen((char const *)hash_input));
    /* get sha1 result */
    rt_hwcrypto_hash_finish(ctx, sha1_output, rt_strlen((char const *)sha1_output));

    rt_kprintf("Actual sha1 result: \n");
    for (i = 0; i < sizeof(sha1_output); i++)
    {
        rt_kprintf("%x ", sha1_output[i]);
    }
    rt_kprintf("\n");
    if(rt_memcmp(sha1_output, sha1_except, sizeof(sha1_except)/sizeof(sha1_except[0])) != 0)
    {
        rt_kprintf("Hash type sha1 Test error, The actual result is not equal to the except result\n");
    }
    else
    {
        rt_kprintf("Hash type sha1 Test success, The actual result is equal to the except result\n");
    }
    /* deinit hash*/
    rt_hwcrypto_hash_destroy(ctx);

    /* md5 test*/
    ctx = rt_hwcrypto_hash_create(rt_hwcrypto_dev_default(), HWCRYPTO_TYPE_MD5);
    if (ctx == RT_NULL)
    {
        rt_kprintf("create hash[%08x] context err!\n", HWCRYPTO_TYPE_MD5);
        return ;
    }
    rt_kprintf("Create md5 type success!\n");
    rt_kprintf("Except md5 result: \n");
    for (i = 0; i < sizeof(md5_except); i++)
    {
        rt_kprintf("%x ", md5_except[i]);
    }
    rt_kprintf("\n");
    /* start md5 */
    rt_hwcrypto_hash_update(ctx, hash_input, rt_strlen((char const *)hash_input));
    /* get md5 result */
    rt_hwcrypto_hash_finish(ctx, md5_output, rt_strlen((char const *)md5_output));

    rt_kprintf("Actual md5 result: \n");
    for (i = 0; i < sizeof(md5_output); i++)
    {
        rt_kprintf("%x ", md5_output[i]);
    }
    rt_kprintf("\n");
    if(rt_memcmp(md5_output, md5_except, sizeof(md5_except)/sizeof(md5_except[0])) != 0)
    {
        rt_kprintf("Hash type md5 Test error, The actual result is not equal to the except result\n");
    }
    else
    {
        rt_kprintf("Hash type md5 Test success, The actual result is equal to the except result\n");
    }
    /* deinit hash*/
    rt_hwcrypto_hash_destroy(ctx);

    /* sha224 test */
    ctx = rt_hwcrypto_hash_create(rt_hwcrypto_dev_default(), HWCRYPTO_TYPE_SHA224);
    if (ctx == RT_NULL)
    {
        rt_kprintf("create hash[%08x] context err!\n", HWCRYPTO_TYPE_SHA224);
        return ;
    }
    rt_kprintf("Create sha224 type success!\n");
    rt_kprintf("Except sha224 result: \n");
    for (i = 0; i < sizeof(sha224_except); i++)
    {
        rt_kprintf("%x ", sha224_except[i]);
    }
    rt_kprintf("\n");
    /* start sha224 */
    rt_hwcrypto_hash_update(ctx, hash_input, rt_strlen((char const *)hash_input));
    /* get sha224 result */
    rt_hwcrypto_hash_finish(ctx, sha224_output, rt_strlen((char const *)sha224_output));

    rt_kprintf("Actual sha224 result: \n");
    for (i = 0; i < sizeof(sha224_output); i++)
    {
        rt_kprintf("%x ", sha224_output[i]);
    }
    rt_kprintf("\n");
    if(rt_memcmp(sha224_output, sha224_except, sizeof(sha224_except)/sizeof(sha224_except[0])) != 0)
    {
        rt_kprintf("Hash type sha224 Test error, The actual result is not equal to the except result\n");
    }
    else
    {
        rt_kprintf("Hash type sha224 Test success, The actual result is equal to the except result\n");
    }
    rt_hwcrypto_hash_destroy(ctx);

    /* sha256 test*/
    ctx = rt_hwcrypto_hash_create(rt_hwcrypto_dev_default(), HWCRYPTO_TYPE_SHA256);
    if (ctx == RT_NULL)
    {
        rt_kprintf("create hash[%08x] context err!\n", HWCRYPTO_TYPE_SHA256);
        return ;
    }

    rt_kprintf("Create sha256 type success!\n");
    rt_kprintf("Except sha256 result: \n");
    for (i = 0; i < sizeof(sha256_except); i++)
    {
        rt_kprintf("%x ", sha256_except[i]);
    }
    rt_kprintf("\n");
    /* start sha256 */
    rt_hwcrypto_hash_update(ctx, hash_input, rt_strlen((char const *)hash_input));
    /* get sha256 result */
    rt_hwcrypto_hash_finish(ctx, sha256_output, rt_strlen((char const *)sha256_output));

    rt_kprintf("Actual sha256 result: \n");
    for (i = 0; i < sizeof(sha256_output); i++)
    {
        rt_kprintf("%x ", sha256_output[i]);
    }
    rt_kprintf("\n");

    if(rt_memcmp(sha256_output, sha256_except, sizeof(sha256_except)/sizeof(sha256_except[0])) != 0)
    {
        rt_kprintf("Hash type sha256 Test error, The actual result is not equal to the except result\n");
    }
    else
    {
        rt_kprintf("Hash type sha256 Test success, The actual result is equal to the except result\n");
    }
    rt_hwcrypto_hash_destroy(ctx);
    rt_kprintf("Hash Test over!\n");
}
#endif

static int crypto(int argc, char **argv)
{
    int result = RT_EOK;
    static rt_device_t device = RT_NULL;
    char *result_str;

    if (argc > 1)
    {
        if (!strcmp(argv[1], "probe"))
        {
            if (argc == 3)
            {
                char *dev_name = argv[2];
                device = rt_device_find(dev_name);
                result_str = (device == RT_NULL) ? "failure" : "success";
                rt_kprintf("probe %s %s \n", argv[2], result_str);
            }
            else
            {
                rt_kprintf("crypto probe <crypto_name>   - probe crypto by name\n");
            }
        }
        else
        {
            if (device == RT_NULL)
            {
                rt_kprintf("Please using 'crypto probe <crypto_name>' first\n");
                return -RT_ERROR;
            }
            if (!strcmp(argv[1], "rng"))
            {
#if defined (BSP_USING_RNG)
                if (argc == 3)
                {
                    result = hw_rng_sample(atoi(argv[2]));
                    if(result != RT_EOK)
                    {
                        rt_kprintf("please input a  legal number, not <%d>\n", atoi(argv[2]));
                    }
                }
                else
                {
                    rt_kprintf("rng <number>        - generate <number> digital\n");
                }

#else
                rt_kprintf("please enable RNG first!\n");
#endif
            }
            else if (!strcmp(argv[1], "crc"))
            {
#if defined (BSP_USING_CRC)
                int size = 0, i = 0;
                if (argc > 3)
                {
                    size = argc - 2;
                    uint8_t *data = rt_malloc(size);
                    if (data)
                    {
                        for (i = 0; i < size; i++)
                        {
                            data[i] = strtol(argv[2 + i], NULL, 0);
                        }
                        hw_crc_sample(data, size);
                        rt_free(data);
                    }
                    else
                    {
                        rt_kprintf("Low memory!\n");
                    }
                }
                else
                {
                    rt_kprintf("crypto crc data1 ... dataN          - calculate data1 ... dataN crc\n");
                }
#else
                rt_kprintf("please enable CRC first!\n");
#endif
            }
            else if (!strcmp(argv[1], "hash"))
            {
#if defined (BSP_USING_HASH)
                if (argc == 3)
                {
                    hw_hash_sample();
                }
                else
                {
                    rt_kprintf("crypto hash sample          - hash use sample\n");
                }
#else
         rt_kprintf("please enable CRC first!\n");
#endif

            }
            else
            {
                rt_kprintf("Unknown command. Please enter 'crypto' for help\n");
            }
        }
    }
    else
    {
        rt_kprintf("Usage: \n");
        rt_kprintf("crypto probe <crypto_name>                  - probe crypto by name\n");
        rt_kprintf("crypto rng number                           - generate numbers digital\n");
        rt_kprintf("crypto crc data1 ... dataN                  - calculate data1 ... dataN crc\n");
        rt_kprintf("crypto hash sample                          - hash use sample\n");
        result = -RT_ERROR;
    }

    return result;
}
MSH_CMD_EXPORT(crypto, crypto function);
