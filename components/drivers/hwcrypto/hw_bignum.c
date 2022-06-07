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
#include <hw_bignum.h>

static struct rt_hwcrypto_ctx *bignum_default;

rt_inline rt_err_t hwcrypto_bignum_dev_is_init(void)
{
    struct rt_hwcrypto_device *dev;

    if (bignum_default)
    {
        return RT_EOK;
    }
    dev = rt_hwcrypto_dev_default();
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
 * @brief           Init bignum obj
 *
 * @param n         bignum obj
 */
void rt_hwcrypto_bignum_init(struct hw_bignum_mpi *n)
{
    if(n == RT_NULL)
        return;

    n->sign = 1;
    n->total = 0;
    n->p = RT_NULL;
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
        rt_memset(n->p, 0xFF, n->total);
        rt_free(n->p);
        n->sign = 0;
        n->total = 0;
        n->p = RT_NULL;
    }
}

/**
 * @brief           Get length of bignum as an unsigned binary buffer
 *
 * @param n         bignum obj
 *
 * @return          binary buffer length
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
 * @brief           Export n into unsigned binary data, big endian
 *
 * @param n         bignum obj
 * @param buf       Buffer for the binary number
 * @param len       Length of the buffer
 *
 * @return          export bin length
 */
int rt_hwcrypto_bignum_export_bin(struct hw_bignum_mpi *n, rt_uint8_t *buf, int len)
{
    int cp_len, i, j;

    if (n == RT_NULL || buf == RT_NULL)
    {
        return 0;
    }
    rt_memset(buf, 0, len);
    cp_len = (int)n->total > len ? len : (int)n->total;
    for(i = cp_len, j = 0; i > 0; i--, j++)
    {
        buf[i - 1] = n->p[j];
    }

    return cp_len;
}

/**
 * @brief           Import n from unsigned binary data, big endian
 *
 * @param n         bignum obj
 * @param buf       Buffer for the binary number
 * @param len       Length of the buffer
 *
 * @return          import length.
 */
int rt_hwcrypto_bignum_import_bin(struct hw_bignum_mpi *n, rt_uint8_t *buf, int len)
{
    int cp_len, i, j;
    void *temp_p;

    if (n == RT_NULL || buf == RT_NULL)
    {
        return 0;
    }
    if ((int)n->total < len)
    {
        temp_p = rt_malloc(len);
        if (temp_p == RT_NULL)
        {
            return 0;
        }
        rt_free(n->p);
        n->p = temp_p;
        n->total = len;
    }

    n->sign = 1;
    rt_memset(n->p, 0, n->total);
    cp_len = (int)n->total > len ? len : n->total;

    for(i = cp_len, j = 0; i > 0; i--, j++)
    {
        n->p[j] = buf[i - 1];
    }

    return cp_len;
}

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
                                const struct hw_bignum_mpi *b)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (hwcrypto_bignum_dev_is_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->add)
    {
        return bignum_ctx->ops->add(bignum_ctx, x, a, b);
    }
    return -RT_ERROR;
}

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
                                const struct hw_bignum_mpi *b)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (hwcrypto_bignum_dev_is_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->sub)
    {
        return bignum_ctx->ops->sub(bignum_ctx, x, a, b);
    }
    return -RT_ERROR;
}

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
                                const struct hw_bignum_mpi *b)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (hwcrypto_bignum_dev_is_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->mul)
    {
        return bignum_ctx->ops->mul(bignum_ctx, x, a, b);
    }
    return -RT_ERROR;
}

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
                                   const struct hw_bignum_mpi *c)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (hwcrypto_bignum_dev_is_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->mulmod)
    {
        return bignum_ctx->ops->mulmod(bignum_ctx, x, a, b, c);
    }
    return -RT_ERROR;
}

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
                                    const struct hw_bignum_mpi *c)
{
    struct hwcrypto_bignum *bignum_ctx;

    if (hwcrypto_bignum_dev_is_init() != RT_EOK)
    {
        return -RT_ERROR;
    }
    bignum_ctx = (struct hwcrypto_bignum *)bignum_default;
    if (bignum_ctx->ops->exptmod)
    {
        return bignum_ctx->ops->exptmod(bignum_ctx, x, a, b, c);
    }
    return -RT_ERROR;
}
