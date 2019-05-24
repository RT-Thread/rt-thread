/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-25     tyx          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <hw_bignum.h>

static struct rt_hwcrypto_ctx *bignum_default;

rt_inline rt_err_t rt_hwcrypto_bignum_init(void)
{
    struct rt_hwcrypto_device *dev;

    if (bignum_default)
    {
        return RT_EOK;
    }
    dev = rt_hwcrypto_dev_dufault();
    if (dev == RT_NULL)
    {
        return -RT_ERROR;
    }
    return rt_hwcrypto_bignum_default(dev);
}

/**
 * @brief           Setting bignum default devices
 *
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_default(struct rt_hwcrypto_device *device)
{
    if (bignum_default)
    {
        rt_hwcrypto_ctx_destroy(bignum_default);
        bignum_default = RT_NULL;
    }
    if (device == RT_NULL)
    {
        return RT_EOK;
    }
    bignum_default = rt_hwcrypto_ctx_create(device, HWCRYPTO_TYPE_BIGNUM, sizeof(struct hwcrypto_bignum));
    if (bignum_default == RT_NULL)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

/**
 * @brief           Allocate memory for bignum
 *
 * @return          Pointer to allocated bignum obj
 */
struct hw_bignum_mpi *rt_hwcrypto_bignum_alloc(void)
{
    struct hw_bignum_mpi *n;

    n = rt_malloc(sizeof(struct hw_bignum_mpi));
    if (n)
    {
        rt_memset(n, 0, sizeof(struct hw_bignum_mpi));
    }
    return n;
}

/**
 * @brief           free a bignum obj
 *
 * @param           Pointer to bignum obj
 */
void rt_hwcrypto_bignum_free(struct hw_bignum_mpi *n)
{
    if (n)
    {
        rt_free(n->p);
        rt_free(n);
    }
}

/**
 * @brief           Get length of bignum as an unsigned binary buffer
 * 
 * @param n         bignum obj
 * 
 * @return          binary buffer Length
 */
int rt_hwcrypto_bignum_get_len(const struct hw_bignum_mpi *n)
{
    int tmp_len, total;

    if (n == RT_NULL || n->p == RT_NULL)
    {
        return 0;
    }
    tmp_len = 0;
    total = n->total;
    while ((total > 0) && (n->p[total - 1] == 0))
    {
        tmp_len++;
        total--;
    }
    return n->total - tmp_len;
}

/**
 * @brief           Get length of bignum as an unsigned binary buffer
 * 
 * @param n         bignum obj
 * @param buf       Buffer for the binary number
 * @param len       Length of the buffer
 * 
 * @return          binary buffer Length
 */
int rt_hwcrypto_bignum_get_bin(struct hw_bignum_mpi *n, rt_uint8_t *buf, int len)
{
    int cp_len;

    if (n == RT_NULL || n->p == RT_NULL || buf == RT_NULL)
    {
        return 0;
    }
    cp_len = n->total > len ? len : n->total;
    rt_memcpy(n->p, buf, cp_len);
    return cp_len;
}

/**
 * @brief           Set binary buffer to unsigned bignum
 * 
 * @param n         bignum obj
 * @param buf       Buffer for the binary number
 * @param len       Length of the buffer
 * 
 * @return          RT_EOK on success.
 */
rt_err_t rt_hwcrypto_bignum_set_bin(struct hw_bignum_mpi *n, rt_uint8_t *buf, int len)
{
    void *temp_p;

    if (n == RT_NULL)
    {
        return -RT_EINVAL;
    }
    if (n->p && n->total >= len)
    {
        rt_memcpy(n->p, buf, len);
        return RT_EOK;
    }
    temp_p = rt_malloc(len);
    if (temp_p == RT_NULL)
    {
        return -RT_ENOMEM;
    }
    if (n->p)
    {
        rt_free(n->p);
        n->p = temp_p;
        n->total = 0;
    }
    rt_memcpy(n->p, buf, len);
    n->total = len;
    return RT_EOK;
}

/**
 * @brief           Unsigned comparison
 * 
 * @param a         bignum obj
 * @param b         bignum obj
 * 
 * @return          0 is equal
 */
int rt_hwcrypto_bignum_cmp(const struct hw_bignum_mpi *a,
                           const struct hw_bignum_mpi *b)
{
    int a_len, b_len;

    if (a == RT_NULL || a->p == RT_NULL
            || b == RT_NULL || b->p == RT_NULL)
    {
        return -1;
    }
    a_len = rt_hwcrypto_bignum_get_len(a);
    b_len = rt_hwcrypto_bignum_get_len(b);
    if (a_len != b_len)
    {
        return a_len - b_len;
    }
    return rt_memcmp(a->p, b->p, a_len);
}

/**
 * @brief           Compare bignum to standard Unsigned integer
 * 
 * @param a         bignum obj
 * @param b         Unsigned integer
 * 
 * @return          0 is equal
 */
int rt_hwcrypto_bignum_cmp_d(const struct hw_bignum_mpi *a, unsigned long b)
{
    struct hw_bignum_mpi tmp_b;

    b = b <= 0 ? -b : b;
    tmp_b.total = sizeof(unsigned long);
    tmp_b.p = &b;
    return rt_hwcrypto_bignum_cmp(a, &tmp_b);
}

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
                                const struct hw_bignum_mpi *c)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (rt_hwcrypto_bignum_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->add)
    {
        return bignum_ctx->ops->add(bignum_ctx, a, b, c);
    }
    return -RT_ERROR;
}

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
                                const struct hw_bignum_mpi *c)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (rt_hwcrypto_bignum_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->sub)
    {
        return bignum_ctx->ops->sub(bignum_ctx, a, b, c);
    }
    return -RT_ERROR;
}

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
                                const struct hw_bignum_mpi *c)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (rt_hwcrypto_bignum_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->mul)
    {
        return bignum_ctx->ops->mul(bignum_ctx, a, b, c);
    }
    return -RT_ERROR;
}

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
                                   const struct hw_bignum_mpi *d)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (rt_hwcrypto_bignum_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->mulmod)
    {
        return bignum_ctx->ops->mulmod(bignum_ctx, a, b, c, d);
    }
    return -RT_ERROR;
}

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
                        const struct hw_bignum_mpi *d)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (rt_hwcrypto_bignum_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->exptmod)
    {
        return bignum_ctx->ops->exptmod(bignum_ctx, a, b, c, d);
    }
    return -RT_ERROR;
}
