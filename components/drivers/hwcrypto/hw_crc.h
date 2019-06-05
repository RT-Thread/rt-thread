/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-25     tyx          the first version
 */

#ifndef __HW_CRC_H__
#define __HW_CRC_H__

#include <hwcrypto.h>

#define CRC_FLAG_REFIN    (0x1 << 0)
#define CRC_FLAG_REFOUT   (0x1 << 1)

#define HWCRYPTO_CRC8_CFG       \
{                               \
    .last_val = 0x00,           \
    .poly = 0x07,               \
    .width = 8,                 \
    .xorout = 0x00,             \
    .flags = 0,                 \
}

#define HWCRYPTO_CRC16_CFG      \
{                               \
    .last_val = 0x0000,           \
    .poly = 0x8005,               \
    .width = 16,                 \
    .xorout = 0x0000,             \
    .flags = 0,                 \
}

#define HWCRYPTO_CRC32_CFG   \
{                           \
    .last_val = 0x00000000, \
    .poly = 0x04C11DB7,              \
    .width = 32,             \
    .xorout = 0x00000000,            \
    .flags = 0,             \
}

#define HWCRYPTO_CRC_CCITT_CFG   \
{                           \
    .last_val = 0x0000,          \
    .poly = 0x1021,              \
    .width = 16,             \
    .xorout = 0x0000,            \
    .flags = CRC_FLAG_REFIN | CRC_FLAG_REFOUT, \
}

#define HWCRYPTO_CRC_DNP_CFG   \
{                           \
    .last_val = 0x0000,          \
    .poly = 0x3D65,              \
    .width = 16,             \
    .xorout = 0xffff,            \
    .flags = CRC_FLAG_REFIN | CRC_FLAG_REFOUT, \
}

#ifdef __cplusplus
extern "C" {
#endif

struct hwcrypto_crc;

typedef enum
{
    HWCRYPTO_CRC_CUSTOM,        /**< Custom CRC mode */
    HWCRYPTO_CRC_CRC8,          /**< poly : 0x07 */
    HWCRYPTO_CRC_CRC16,         /**< poly : 0x8005 */
    HWCRYPTO_CRC_CRC32,         /**< poly : 0x04C11DB7 */
    HWCRYPTO_CRC_CCITT,         /**< poly : 0x1021 */
    HWCRYPTO_CRC_DNP,           /**< poly : 0x3D65 */
} hwcrypto_crc_mode;

struct hwcrypto_crc_cfg
{
    rt_uint32_t last_val;       /**< Last CRC value cache */
    rt_uint32_t poly;           /**< CRC polynomial */
    rt_uint16_t width;          /**< CRC value width */
    rt_uint32_t xorout;         /**< Result XOR Value */
    rt_uint16_t flags;          /**< Input or output data reverse. CRC_FLAG_REFIN or CRC_FLAG_REFOUT */
};

struct hwcrypto_crc_ops
{
    rt_uint32_t (*update)(struct hwcrypto_crc *ctx,
                          const rt_uint8_t *in, rt_size_t length);  /**< Perform a CRC calculation. return CRC value */
};

/**
 * @brief           CRC context. Hardware driver usage
 */
struct hwcrypto_crc
{
    struct rt_hwcrypto_ctx parent;          /**< Inherited from the standard device */
    struct hwcrypto_crc_cfg crc_cfg;        /**< CRC configure */
    const struct hwcrypto_crc_ops *ops;     /**< !! Hardware initializes this value when creating context !! */
};

/**
 * @brief           Creating CRC Context
 *
 * @param device    Hardware crypto device
 * @param mode      Setting default mode or custom mode
 *
 * @return          CRC context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_crc_create(struct rt_hwcrypto_device *device,
                                               hwcrypto_crc_mode mode);

/**
 * @brief           Destroy CRC Context
 *
 * @param ctx       CRC context
 */
void rt_hwcrypto_crc_destroy(struct rt_hwcrypto_ctx *ctx);

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
                                   const rt_uint8_t *input, rt_size_t length);

/**
 * @brief           CRC context configuration
 *
 * @param ctx       CRC context
 * @param cfg       CRC config
 */
void rt_hwcrypto_crc_cfg(struct rt_hwcrypto_ctx *ctx, 
                         struct hwcrypto_crc_cfg *cfg);

#ifdef __cplusplus
}
#endif

#endif
