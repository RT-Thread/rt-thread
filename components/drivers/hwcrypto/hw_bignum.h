/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
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
    rt_size_t total;            /**< Total length of data  */
    rt_ubase_t *p;              /**< pointer to data  */
};

struct hwcrypto_bignum_ops
{
    rt_err_t (*add)(struct hwcrypto_bignum *bignum_ctx,
                    struct hw_bignum_mpi *a,
                    const struct hw_bignum_mpi *b,
                    const struct hw_bignum_mpi *c);             /**< a = b + c */
    rt_err_t (*sub)(struct hwcrypto_bignum *bignum_ctx,
                    struct hw_bignum_mpi *a,
                    const struct hw_bignum_mpi *b,
                    const struct hw_bignum_mpi *c);             /**< a = b - c */
    rt_err_t (*mul)(struct hwcrypto_bignum *bignum_ctx,
                    struct hw_bignum_mpi *a,
                    const struct hw_bignum_mpi *b,
                    const struct hw_bignum_mpi *c);             /**< a = b * c */
    rt_err_t (*mulmod)(struct hwcrypto_bignum *bignum_ctx,
                       struct hw_bignum_mpi *a,
                       const struct hw_bignum_mpi *b,
                       const struct hw_bignum_mpi *c,
                       const struct hw_bignum_mpi *d);          /**< a = b * c (mod d) */
    rt_err_t (*exptmod)(struct hwcrypto_bignum *bignum_ctx,
                        struct hw_bignum_mpi *a,
                        const struct hw_bignum_mpi *b,
                        const struct hw_bignum_mpi *c,
                        const struct hw_bignum_mpi *d);         /**< a = b ^ c (mod d) */
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
 * @brief           Allocate memory for bignum
 *
 * @return          Pointer to allocated bignum obj
 */
struct hw_bignum_mpi *rt_hwcrypto_bignum_alloc(void);

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
 * @brief           Get length of bignum as an unsigned binary buffer
 * 
 * @param n         bignum obj
 * @param buf       Buffer for the binary number
 * @param len       Length of the buffer
 * 
 * @return          binary buffer Length
 */
int rt_hwcrypto_bignum_get_bin(struct hw_bignum_mpi *n, rt_uint8_t *buf, int len);

/**
 * @brief           Set binary buffer to unsigned bignum
 * 
 * @param n         bignum obj
 * @param buf       Buffer for the binary number
 * @param len       Length of the buffer
 * 
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_set_bin(struct hw_bignum_mpi *n, rt_uint8_t *buf, int len);

/**
 * @brief           Unsigned comparison
 * 
 * @param a         bignum obj
 * @param b         bignum obj
 * 
 * @return          0 is equal
 */
int rt_hwcrypto_bignum_cmp(const struct hw_bignum_mpi *a,
                           const struct hw_bignum_mpi *b);

/**
 * @brief           Compare bignum to standard Unsigned integer
 * 
 * @param a         bignum obj
 * @param b         Unsigned integer
 * 
 * @return          0 is equal
 */
int rt_hwcrypto_bignum_cmp_d(const struct hw_bignum_mpi *a, unsigned long b);

/**
 * @brief           a = b + c
 * 
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 * 
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_add(struct hw_bignum_mpi *a,
                                const struct hw_bignum_mpi *b,
                                const struct hw_bignum_mpi *c);

/**
 * @brief           a = b - c
 * 
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 * 
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_sub(struct hw_bignum_mpi *a,
                                const struct hw_bignum_mpi *b,
                                const struct hw_bignum_mpi *c);

/**
 * @brief           a = b * c
 * 
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 * 
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_mul(struct hw_bignum_mpi *a,
                                const struct hw_bignum_mpi *b,
                                const struct hw_bignum_mpi *c);

/**
 * @brief           a = b * c (mod d)
 * 
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 * 
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_mulmod(struct hw_bignum_mpi *a,
                                   const struct hw_bignum_mpi *b,
                                   const struct hw_bignum_mpi *c,
                                   const struct hw_bignum_mpi *d);

/**
 * @brief           a = b ^ c (mod d)
 * 
 * @param a         bignum obj
 * @param b         bignum obj
 * @param c         bignum obj
 * 
 * @return          RT_EOK on success.
 */
rt_err_t bignum_exptmod(struct hw_bignum_mpi *a,
                        const struct hw_bignum_mpi *b,
                        const struct hw_bignum_mpi *c,
                        const struct hw_bignum_mpi *d);

#ifdef __cplusplus
}
#endif

#endif
