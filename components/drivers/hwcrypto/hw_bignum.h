/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-25     tyx          the first version
 */

#ifndef __HW_BIGNUM_H__
#define __HW_BIGNUM_H__

#include <hwcrypto.h>

#ifdef __cplusplus
extern "C" {
#endif

struct hwcrypto_bignum;

/* bignum obj */
struct hw_bignum_mpi
{
    int sign;                   /**< integer sign */
    rt_size_t total;            /**< total of limbs */
    rt_uint8_t *p;              /**< pointer to limbs */
};

struct hwcrypto_bignum_ops
{
    rt_err_t (*add)(struct hwcrypto_bignum *bignum_ctx,
                    struct hw_bignum_mpi *x,
                    const struct hw_bignum_mpi *a,
                    const struct hw_bignum_mpi *b);             /**< x = a + b */
    rt_err_t (*sub)(struct hwcrypto_bignum *bignum_ctx,
                    struct hw_bignum_mpi *x,
                    const struct hw_bignum_mpi *a,
                    const struct hw_bignum_mpi *b);             /**< x = a - b */
    rt_err_t (*mul)(struct hwcrypto_bignum *bignum_ctx,
                    struct hw_bignum_mpi *x,
                    const struct hw_bignum_mpi *a,
                    const struct hw_bignum_mpi *b);             /**< x = a * b */
    rt_err_t (*mulmod)(struct hwcrypto_bignum *bignum_ctx,
                       struct hw_bignum_mpi *x,
                       const struct hw_bignum_mpi *a,
                       const struct hw_bignum_mpi *b,
                       const struct hw_bignum_mpi *c);          /**< x = a * b (mod c) */
    rt_err_t (*exptmod)(struct hwcrypto_bignum *bignum_ctx,
                        struct hw_bignum_mpi *x,
                        const struct hw_bignum_mpi *a,
                        const struct hw_bignum_mpi *b,
                        const struct hw_bignum_mpi *c);         /**< x = a ^ b (mod c) */
};

/**
 * @brief           bignum context. Hardware driver usage
 */
struct hwcrypto_bignum
{
    struct rt_hwcrypto_ctx parent;              /**< Inheritance from hardware crypto context */
    const struct hwcrypto_bignum_ops *ops;      /**< !! Hardware initializes this value when creating context !! */
};

/**
 * @brief           Setting bignum default devices
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_default(struct rt_hwcrypto_device *device);

/**
 * @brief           Init bignum obj
 */
void rt_hwcrypto_bignum_init(struct hw_bignum_mpi *n);

/**
 * @brief           free a bignum obj
 *
 * @param           Pointer to bignum obj
 */
void rt_hwcrypto_bignum_free(struct hw_bignum_mpi *n);

/**
 * @brief           Get length of bignum as an unsigned binary buffer
 *
 * @param n         bignum obj
 *
 * @return          binary buffer Length
 */
int rt_hwcrypto_bignum_get_len(const struct hw_bignum_mpi *n);

/**
 * @brief           Export n into unsigned binary data, big endian
 *
 * @param n         bignum obj
 * @param buf       Buffer for the binary number
 * @param len       Length of the buffer
 *
 * @return          export bin length
 */
int rt_hwcrypto_bignum_export_bin(struct hw_bignum_mpi *n, rt_uint8_t *buf, int len);

/**
 * @brief           Import n from unsigned binary data, big endian
 *
 * @param n         bignum obj
 * @param buf       Buffer for the binary number
 * @param len       Length of the buffer
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_import_bin(struct hw_bignum_mpi *n, rt_uint8_t *buf, int len);

/**
 * @brief           x = a + b
 *
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_add(struct hw_bignum_mpi *x,
                                const struct hw_bignum_mpi *a,
                                const struct hw_bignum_mpi *b);

/**
 * @brief           x = a - b
 *
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_sub(struct hw_bignum_mpi *x,
                                const struct hw_bignum_mpi *a,
                                const struct hw_bignum_mpi *b);

/**
 * @brief           x = a * b
 *
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_mul(struct hw_bignum_mpi *x,
                                const struct hw_bignum_mpi *a,
                                const struct hw_bignum_mpi *b);

/**
 * @brief           x = a * b (mod c)
 *
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_mulmod(struct hw_bignum_mpi *x,
                                   const struct hw_bignum_mpi *a,
                                   const struct hw_bignum_mpi *b,
                                   const struct hw_bignum_mpi *c);

/**
 * @brief           x = a ^ b (mod c)
 *
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_exptmod(struct hw_bignum_mpi *x,
                                    const struct hw_bignum_mpi *a,
                                    const struct hw_bignum_mpi *b,
                                    const struct hw_bignum_mpi *c);

#ifdef __cplusplus
}
#endif

#endif
