/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-25     tyx          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <hw_crc.h>

/**
 * @brief           Creating CRC Context
 *
 * @param device    Hardware crypto device
 * @param mode      Setting default mode or custom mode
 *
 * @return          CRC context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_crc_create(struct rt_hwcrypto_device *device,
                                               hwcrypto_crc_mode mode)
{
    struct hwcrypto_crc *crc_ctx;

    crc_ctx = (struct hwcrypto_crc *)rt_hwcrypto_ctx_create(device, HWCRYPTO_TYPE_CRC, sizeof(struct hwcrypto_crc));
    if (crc_ctx == RT_NULL)
    {
        return RT_NULL;
    }

    switch (mode)
    {
    case HWCRYPTO_CRC_CRC8:
    {
        struct hwcrypto_crc_cfg temp = HWCRYPTO_CRC8_CFG;
        crc_ctx->crc_cfg = temp;
        break;
    }
    case HWCRYPTO_CRC_CRC16:
    {
        struct hwcrypto_crc_cfg temp = HWCRYPTO_CRC16_CFG;
        crc_ctx->crc_cfg = temp;
        break;
    }
    case HWCRYPTO_CRC_CRC32:
    {
        struct hwcrypto_crc_cfg temp = HWCRYPTO_CRC32_CFG;
        crc_ctx->crc_cfg = temp;
        break;
    }
    case HWCRYPTO_CRC_CCITT:
    {
        struct hwcrypto_crc_cfg temp = HWCRYPTO_CRC_CCITT_CFG;
        crc_ctx->crc_cfg = temp;
        break;
    }
    case HWCRYPTO_CRC_DNP:
    {
        struct hwcrypto_crc_cfg temp = HWCRYPTO_CRC_DNP_CFG;
        crc_ctx->crc_cfg = temp;
        break;
    }
    default:
        break;
    }

    return &crc_ctx->parent;
}

/**
 * @brief           Destroy CRC Context
 *
 * @param ctx       CRC context
 */
void rt_hwcrypto_crc_destroy(struct rt_hwcrypto_ctx *ctx)
{
    rt_hwcrypto_ctx_destroy(ctx);
}

/**
 * @brief           Processing a packet of data
 *
 * @param ctx       CRC context
 * @param input     Data buffer to be Processed
 * @param length    Data Buffer length
 *
 * @return          CRC value
 */
rt_uint32_t rt_hwcrypto_crc_update(struct rt_hwcrypto_ctx *ctx,
                                             const rt_uint8_t *input,
                                             rt_size_t length)
{
    struct hwcrypto_crc *crc_ctx = (struct hwcrypto_crc *)ctx;
    if (ctx && crc_ctx->ops->update)
    {
        return crc_ctx->ops->update(crc_ctx, input, length);
    }
    return 0;
}

/**
 * @brief           CRC context configuration
 *
 * @param ctx       CRC context
 * @param cfg       CRC config
 */
void rt_hwcrypto_crc_cfg(struct rt_hwcrypto_ctx *ctx,
                                   struct hwcrypto_crc_cfg *cfg)
{
    if (cfg)
    {
        ((struct hwcrypto_crc *)ctx)->crc_cfg = *cfg;
    }
}
