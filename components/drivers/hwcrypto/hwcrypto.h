/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-23     tyx          the first version
 */

#ifndef __HWCRYPTO_H__
#define __HWCRYPTO_H__

#include <rtthread.h>

#ifndef RT_HWCRYPTO_DEFAULT_NAME
#define RT_HWCRYPTO_DEFAULT_NAME    ("hwcryto")
#endif

#define HWCRYPTO_MAIN_TYPE_MASK     (0xffffUL << 16)
#define HWCRYPTO_SUB_TYPE_MASK      (0xffUL << 8)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    HWCRYPTO_TYPE_NULL = 0x00000000,

    /* Main Type */
    /* symmetric Type */
    HWCRYPTO_TYPE_HEAD    = __LINE__,
    HWCRYPTO_TYPE_AES     = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< AES */
    HWCRYPTO_TYPE_DES     = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< DES */
    HWCRYPTO_TYPE_3DES    = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< 3DES */
    HWCRYPTO_TYPE_RC4     = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< RC4 */
    HWCRYPTO_TYPE_GCM     = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< GCM */
    /* HASH Type */
    HWCRYPTO_TYPE_MD5     = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< MD5 */
    HWCRYPTO_TYPE_SHA1    = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< SHA1 */
    HWCRYPTO_TYPE_SHA2    = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< SHA2 */
    /* Other Type */
    HWCRYPTO_TYPE_RNG     = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< RNG */
    HWCRYPTO_TYPE_CRC     = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< CRC */
    HWCRYPTO_TYPE_BIGNUM  = ((__LINE__ - HWCRYPTO_TYPE_HEAD) & 0xffff) << 16,  /**< BIGNUM */

    /* AES Subtype */
    HWCRYPTO_TYPE_AES_ECB = HWCRYPTO_TYPE_AES | (0x01 << 8),
    HWCRYPTO_TYPE_AES_CBC = HWCRYPTO_TYPE_AES | (0x02 << 8),
    HWCRYPTO_TYPE_AES_CFB = HWCRYPTO_TYPE_AES | (0x03 << 8),
    HWCRYPTO_TYPE_AES_CTR = HWCRYPTO_TYPE_AES | (0x04 << 8),
    HWCRYPTO_TYPE_AES_OFB = HWCRYPTO_TYPE_AES | (0x05 << 8),

    /* DES Subtype */
    HWCRYPTO_TYPE_DES_ECB = HWCRYPTO_TYPE_DES | (0x01 << 8),
    HWCRYPTO_TYPE_DES_CBC = HWCRYPTO_TYPE_DES | (0x02 << 8),

    /* 3DES Subtype */
    HWCRYPTO_TYPE_3DES_ECB = HWCRYPTO_TYPE_3DES | (0x01 << 8),
    HWCRYPTO_TYPE_3DES_CBC = HWCRYPTO_TYPE_3DES | (0x02 << 8),

    /* SHA2 Subtype */
    HWCRYPTO_TYPE_SHA224 = HWCRYPTO_TYPE_SHA2 | (0x01 << 8),
    HWCRYPTO_TYPE_SHA256 = HWCRYPTO_TYPE_SHA2 | (0x02 << 8),
    HWCRYPTO_TYPE_SHA384 = HWCRYPTO_TYPE_SHA2 | (0x03 << 8),
    HWCRYPTO_TYPE_SHA512 = HWCRYPTO_TYPE_SHA2 | (0x04 << 8),
} hwcrypto_type;

typedef enum
{
    HWCRYPTO_MODE_ENCRYPT = 0x1,        /**< Encryption operations */
    HWCRYPTO_MODE_DECRYPT = 0x2,        /**< Decryption operations */
    HWCRYPTO_MODE_UNKNOWN = 0x7fffffff, /**< Unknown */
} hwcrypto_mode;

struct rt_hwcrypto_ctx;

struct rt_hwcrypto_ops
{
    rt_err_t (*create)(struct rt_hwcrypto_ctx *ctx);        /**< Creating hardware context */
    void (*destroy)(struct rt_hwcrypto_ctx *ctx);           /**< Delete hardware context */
    rt_err_t (*copy)(struct rt_hwcrypto_ctx *des,
                     const struct rt_hwcrypto_ctx *src);    /**< Cpoy hardware context */
    void (*reset)(struct rt_hwcrypto_ctx *ctx);             /**< Reset hardware context */
};

struct rt_hwcrypto_device
{
    struct rt_device parent;                            /**< Inherited from the standard device */
    const struct rt_hwcrypto_ops *ops;                  /**< Hardware crypto ops */
    rt_uint64_t id;                                     /**< Unique id */
    void *user_data;                                    /**< Device user data */
};

struct rt_hwcrypto_ctx
{
    struct rt_hwcrypto_device *device;  /**< Binding device */
    hwcrypto_type type;                 /**< Encryption and decryption types */
    void *contex;                       /**< Hardware context */
};

/**
 * @brief           Setting context type (Direct calls are not recommended)
 *
 * @param ctx       Crypto context
 * @param type      Types of settings
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_set_type(struct rt_hwcrypto_ctx *ctx, hwcrypto_type type);

/**
 * @brief           Reset context type (Direct calls are not recommended)
 *
 * @param ctx       Crypto context
 */
void rt_hwcrypto_ctx_reset(struct rt_hwcrypto_ctx *ctx);

/**
 * @brief           Init crypto context (Direct calls are not recommended)
 *
 * @param ctx       The context to initialize
 * @param device    Hardware crypto device
 * @param type      Type of context
 * @param obj_size  Size of context object
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_ctx_init(struct rt_hwcrypto_ctx *ctx,
                              struct rt_hwcrypto_device *device, hwcrypto_type type);

/**
 * @brief           Create crypto context (Direct calls are not recommended)
 *
 * @param device    Hardware crypto device
 * @param type      Type of context
 * @param obj_size  Size of context object
 *
 * @return          Crypto context
 */
struct rt_hwcrypto_ctx *rt_hwcrypto_ctx_create(struct rt_hwcrypto_device *device,
                                               hwcrypto_type type, rt_uint32_t obj_size);

/**
 * @brief           Destroy crypto context (Direct calls are not recommended)
 *
 * @param device    Crypto context
 */
void rt_hwcrypto_ctx_destroy(struct rt_hwcrypto_ctx *ctx);

/**
 * @brief           Copy crypto context (Direct calls are not recommended)
 *
 * @param des       The destination context
 * @param src       The context to be copy
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_ctx_cpy(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src);

/**
 * @brief           Register hardware crypto device
 *
 * @param device    Hardware crypto device
 * @param name      Name of device
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_register(struct rt_hwcrypto_device *device, const char *name);

/**
 * @brief           Get the default hardware crypto device
 *
 * @return          Hardware crypto device
 *
 */
struct rt_hwcrypto_device *rt_hwcrypto_dev_default(void);

/**
 * @brief           Get the unique ID of the device
 *
 * @param device    Device object
 *
 * @return          Device unique ID
 */
rt_uint64_t rt_hwcrypto_id(struct rt_hwcrypto_device *device);

#ifdef __cplusplus
}
#endif

#endif
