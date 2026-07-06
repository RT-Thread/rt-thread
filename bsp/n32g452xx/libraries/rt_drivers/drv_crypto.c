/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-04-21     wolfJane          first version
 */

#include <board.h>
#include "drv_crypto.h"

#ifdef RT_USING_HWCRYPTO

#define DRV_DEBUG
#define LOG_TAG              "drv.crypto"
#include <drv_log.h>

#ifdef RT_HWCRYPTO_USING_CRC
    #define BSP_USING_CRC
#endif

static uint16_t _reverse_16bit(uint16_t x)
{
    x = (((x & 0xaaaa) >> 1) | ((x & 0x5555) << 1));
    x = (((x & 0xcccc) >> 2) | ((x & 0x3333) << 2));
    x = (((x & 0xf0f0) >> 4) | ((x & 0x0f0f) << 4));
    return ((x >> 8) | (x << 8));
}


static uint16_t _get_crc16(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    uint16_t temp = 0;

    if (ctx ->crc_cfg.poly != CRC16_PLOY)
    {
        LOG_E("n32g45x crc16 is available only use poly 0x%04X", CRC16_PLOY);
        return 0;
    }

    if (ctx ->crc_cfg.flags & CRC_FLAG_REFIN)
    {
        CRC->CRC16CTRL |= CRC16_CTRL_LITTLE;
    }
    else
    {
        CRC->CRC16CTRL &= (~CRC16_CTRL_LITTLE);
    }

    CRC->CRC16CTRL |= CRC16_CTRL_RESET;
    CRC->CRC16D = ctx ->crc_cfg.last_val;
    CRC->LRC = 0;

    while (length--)
    {
        CRC->CRC16DAT = *in++;
    }
    temp = CRC->CRC16D;

    if (ctx ->crc_cfg.flags & CRC_FLAG_REFOUT)
    {
        temp = _reverse_16bit(temp);
    }

    return temp;
}

static uint32_t _get_crc32(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    uint32_t result = 0;
    int length_4 = length >> 2;
    uint8_t *xdat = (uint8_t *)in;

    if (ctx ->crc_cfg.poly != CRC32_PLOY)
    {
        LOG_E("n32g45x crc32 is available only use poly 0x%08X", CRC32_PLOY);
        return 0;
    }

    switch (ctx ->crc_cfg.flags & 0x03)
    {
    case 0:
    {
        while (length_4--)
        {
            result = ((uint32_t)xdat[0] << 24) | ((uint32_t)xdat[1] << 16)
                     | ((uint32_t)xdat[2] << 8) | xdat[3];
            CRC->CRC32DAT = result;
            xdat += 4;
        }

        result = CRC->CRC32DAT;
        length_4 = length & 0x03;

        if (length_4 < 1)
        {
            break;
        }

        uint8_t i = 0;
        while (length_4--)
        {
            result ^= (*xdat++) << 24;

            for (i = 0; i < 8; i++)
            {
                if (result & 0x80000000)
                {
                    result = (result << 1) ^ CRC32_PLOY;
                }
                else
                {
                    result <<= 1;
                }
            }
        }
    }
    break;
    case CRC_FLAG_REFIN:
    /* TODO: add control command handle */
    case CRC_FLAG_REFOUT:
    /* TODO: add control command handle */
    case (CRC_FLAG_REFIN|CRC_FLAG_REFOUT):
    /* TODO: add control command handle */
    default:
        break;
    }

    return result;
}

static rt_uint32_t _crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_uint32_t result = 0;
    struct n32_hwcrypto_device *n32_hw_dev = (struct n32_hwcrypto_device *)ctx->parent.device->user_data;

    rt_mutex_take(&n32_hw_dev->mutex, RT_WAITING_FOREVER);

    if (ctx ->crc_cfg.flags >> 2)
    {
        LOG_E("flags out range 0x%08X", ctx ->crc_cfg.flags);
        goto _exit;
    }

    if (ctx ->crc_cfg.width == 16)
    {
        result = _get_crc16(ctx, in, length);
    }
    else if (ctx ->crc_cfg.width == 32)
    {
        result = _get_crc32(ctx, in, length);
    }

_exit:
    rt_mutex_release(&n32_hw_dev->mutex);

    return result;
}

static const struct hwcrypto_crc_ops crc_ops =
{
    .update = _crc_update,
};


static rt_err_t _crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
#if defined(BSP_USING_RNG)
    case HWCRYPTO_TYPE_RNG:
    {
        break;
    }
#endif /* BSP_USING_RNG */

#if defined(BSP_USING_CRC)
    case HWCRYPTO_TYPE_CRC:
    {
        RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_CRC, ENABLE);
        ((struct hwcrypto_crc *)ctx)->ops = &crc_ops;
        break;
    }
#endif /* BSP_USING_CRC */

#if defined(BSP_USING_HASH)
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
    {
        break;
    }
#endif /* BSP_USING_HASH */

#if defined(BSP_USING_CRYP)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
    {
        break;
    }
#endif  /* BSP_USING_CRYP */

    default:
        res = -RT_ERROR;
        break;
    }
    return res;
}

static void _crypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    /* TODO: add control command handle */
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
#endif /* BSP_USING_HASH */

#if defined(BSP_USING_CRYP)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
        break;
#endif /* BSP_USING_CRYP */

    default:
        break;
    }

    if (ctx->contex)
        rt_free(ctx->contex);
}

static rt_err_t _crypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t res = RT_EOK;
    /* TODO: add control command handle */
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

#if defined(BSP_USING_CRYP)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
        break;
#endif /* BSP_USING_CRYP */

    default:
        res = -RT_ERROR;
        break;
    }
    return res;
}

static void _crypto_reset(struct rt_hwcrypto_ctx *ctx)
{
    /* TODO: add control command handle */
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

#if defined(BSP_USING_CRYP)
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_GCM:
        break;
#endif /* BSP_USING_CRYP */
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

int n32_hw_crypto_device_init(void)
{
    static struct n32_hwcrypto_device _crypto_dev;
    rt_uint32_t cpuid[3] = {0};

    _crypto_dev.dev.ops = &_ops;
#if defined(BSP_USING_UDID)
    /* TODO: add control command handle */

#endif /* BSP_USING_UDID */

    _crypto_dev.dev.id = 0;
    rt_memcpy(&_crypto_dev.dev.id, cpuid, 8);

    _crypto_dev.dev.user_data = &_crypto_dev;

    if (rt_hwcrypto_register(&_crypto_dev.dev, RT_HWCRYPTO_DEFAULT_NAME) != RT_EOK)
    {
        return -1;
    }
    rt_mutex_init(&_crypto_dev.mutex, RT_HWCRYPTO_DEFAULT_NAME, RT_IPC_FLAG_PRIO);
    return 0;
}
INIT_DEVICE_EXPORT(n32_hw_crypto_device_init);

static void crc_demo(uint8_t argc, char **argv)
{
    struct hwcrypto_crc_cfg modbus_cfg =
    {
        .last_val = 0xFFFF,
        .poly = 0x8005,
        .width = 16,
        .xorout = 0x0000,
        .flags = CRC_FLAG_REFIN | CRC_FLAG_REFOUT,
    };
    struct hwcrypto_crc_cfg crc32mpeg2_cfg =
    {
        .last_val = 0xFFFFFFFF,
        .poly = 0x04C11DB7,
        .width = 32,
        .xorout = 0x00000000,
        .flags = 0,
    };

    struct rt_hwcrypto_ctx *ctx;
    rt_uint32_t result = 0;
    rt_uint8_t temp[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    rt_uint8_t i = 0;
        rt_uint8_t len = sizeof(temp);

    ctx = rt_hwcrypto_crc_create(rt_hwcrypto_dev_default(), HWCRYPTO_CRC_CRC32);

    rt_kprintf("crc dat:\n");
    for (i = 0; i < len; i++)
    {
        rt_kprintf("%02X ", temp[i]);
    }
    rt_kprintf("\n");

    rt_hwcrypto_crc_cfg(ctx, &crc32mpeg2_cfg);
    result = rt_hwcrypto_crc_update(ctx, temp, len);
    rt_kprintf("crc32mpeg2: %x \n", result);

    rt_hwcrypto_crc_cfg(ctx, &modbus_cfg);
    result = rt_hwcrypto_crc_update(ctx, temp, len);
    rt_kprintf("crc16modbus: %x \n", result);

    /*chang to msb*/
    modbus_cfg.flags = 0;
    rt_hwcrypto_crc_cfg(ctx, &modbus_cfg);
    result = rt_hwcrypto_crc_update(ctx, temp, len);
    rt_kprintf("crc16 msb: %x \n", result);

    rt_hwcrypto_crc_destroy(ctx);
}

MSH_CMD_EXPORT(crc_demo, demo for hardwave crc.);

#endif
