/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-17     tyx          1st version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>
#include <string.h>
#include "drv_crypto.h"
#include "wm_crypto_hard.h"

// #define WM_HWCRYPTO_NOT_LOCK
// #define WM_HWCRYPTO_NOT_ALIGN_CHECK

extern u32 tls_crypto_crc_update_adv(u32 crc_val, CRYPTO_CRC_TYPE type, u8 mode, const unsigned char *in, u32 len);
extern int tls_crypto_des_encrypt_decrypt_adv(unsigned char *key, unsigned char *IV, const unsigned char *in, unsigned char *out, u32 len, CRYPTO_MODE cbc, CRYPTO_WAY dec);
extern int tls_crypto_3des_encrypt_decrypt_adv(unsigned char *key, unsigned char *IV, const unsigned char *in, unsigned char *out, u32 len, CRYPTO_MODE cbc, CRYPTO_WAY dec);
extern int tls_crypto_aes_encrypt_decrypt_adv(unsigned char *key, unsigned char *IV, const unsigned char *in, unsigned char *out, u32 len, CRYPTO_MODE cbc, CRYPTO_WAY dec);
extern int tls_crypto_rc4_adv(unsigned char *key, u32 keylen, const unsigned char *in, unsigned char *out, u32 len);

struct wm_hwcrypto_device
{
    struct rt_hwcrypto_device dev;
    struct rt_mutex mutex;
};

struct hash_ctx_des
{
    psDigestContext_t contex;
};

static rt_uint32_t _rng_rand(struct hwcrypto_rng *ctx)
{
    rt_uint32_t rand_num;
    struct wm_hwcrypto_device *_hwcrypto = (struct wm_hwcrypto_device *)ctx->parent.device;

#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_take(&_hwcrypto->mutex, RT_WAITING_FOREVER);
#endif
    tls_crypto_random_init((u32)rt_tick_get(), CRYPTO_RNG_SWITCH_32);
    tls_crypto_random_bytes((unsigned char *)&rand_num, sizeof(rand_num));
    tls_crypto_random_stop();
#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_release(&_hwcrypto->mutex);
#endif

    return rand_num;
}

static rt_uint32_t _crc_update(struct hwcrypto_crc *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_uint32_t crc_result;
    CRYPTO_CRC_TYPE type;
    u8 mode = 0;
    struct wm_hwcrypto_device *_hwcrypto = (struct wm_hwcrypto_device *)ctx->parent.device;
    unsigned char align_flag = 0;

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (((rt_uint32_t)in % 4) != 0)
    {
        void *temp;
        temp = rt_malloc(length);
        if (temp)
        {
            memcpy(temp, in, length);
            in = temp;
            align_flag = 1;
        }
        else
        {
            return 0;
        }
    }
#endif

    switch (ctx->crc_cfg.poly)
    {
    case 0x04C11DB7:
        type = CRYPTO_CRC_TYPE_32;
        break;
    case 0x00001021:
        type = CRYPTO_CRC_TYPE_16_CCITT;
        break;
    case 0x00008005:
        type = CRYPTO_CRC_TYPE_16_MODBUS;
        break;
    case 0x00000007:
    case 0x00000207:
        type = CRYPTO_CRC_TYPE_8;
        break;
    default:
        return 0;
    }

    mode |= ctx->crc_cfg.flags & CRC_FLAG_REFOUT ? OUTPUT_REFLECT : 0;
    mode |= ctx->crc_cfg.flags & CRC_FLAG_REFIN ? INPUT_REFLECT : 0;

#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_take(&_hwcrypto->mutex, RT_WAITING_FOREVER);
#endif
    crc_result = tls_crypto_crc_update_adv(ctx->crc_cfg.last_val, type, mode, in, length);
#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_release(&_hwcrypto->mutex);
#endif

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (align_flag)
    {
        rt_free((rt_uint8_t *)in);
    }
#endif

    ctx->crc_cfg.last_val = crc_result;
    return crc_result ^ 0x00 ^ ctx->crc_cfg.xorout;
}

static rt_err_t _hash_update(struct hwcrypto_hash *ctx, const rt_uint8_t *in, rt_size_t length)
{
    rt_err_t err = RT_EOK;
    struct wm_hwcrypto_device *_hwcrypto = (struct wm_hwcrypto_device *)ctx->parent.device;
    unsigned char align_flag = 0;

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (((rt_uint32_t)in % 4) != 0)
    {
        void *temp;
        temp = rt_malloc(length);
        if (temp)
        {
            memcpy(temp, in, length);
            in = temp;
            align_flag = 1;
        }
        else
        {
            return -RT_ENOMEM;
        }
    }
#endif

#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_take(&_hwcrypto->mutex, RT_WAITING_FOREVER);
#endif
    switch (ctx->parent.type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_MD5:
        tls_crypto_md5_update(&((struct hash_ctx_des *)(ctx->parent.contex))->contex, in, length);
        break;
    case HWCRYPTO_TYPE_SHA1:
        tls_crypto_sha1_update(&((struct hash_ctx_des *)(ctx->parent.contex))->contex, in, length);
        break;
    default:
        err = -RT_ERROR;
        break;
    }
#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_release(&_hwcrypto->mutex);
#endif

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (align_flag)
    {
        rt_free((rt_uint8_t *)in);
    }
#endif

    return err;
}

static rt_err_t _hash_finish(struct hwcrypto_hash *ctx, rt_uint8_t *out, rt_size_t length)
{
    rt_err_t err = RT_EOK;
    struct wm_hwcrypto_device *_hwcrypto = (struct wm_hwcrypto_device *)ctx->parent.device;

#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_take(&_hwcrypto->mutex, RT_WAITING_FOREVER);
#endif
    switch (ctx->parent.type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_MD5:
        tls_crypto_md5_final(&((struct hash_ctx_des *)(ctx->parent.contex))->contex, out);
        break;
    case HWCRYPTO_TYPE_SHA1:
        tls_crypto_sha1_final(&((struct hash_ctx_des *)(ctx->parent.contex))->contex, out);
        break;
    default:
        err = -RT_ERROR;
        break;
    }
#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_release(&_hwcrypto->mutex);
#endif

    return err;
}

static rt_err_t _des_crypt(struct hwcrypto_symmetric *symmetric_ctx, struct hwcrypto_symmetric_info *symmetric_info)
{
    CRYPTO_WAY mode;
    CRYPTO_MODE cbc;
    struct wm_hwcrypto_device *_hwcrypto = (struct wm_hwcrypto_device *)symmetric_ctx->parent.device;
    unsigned char *in, *out, align_flag = 0;

    if ((symmetric_ctx->key_bitlen >> 3) != 8
            || (symmetric_info->length % 8) != 0)
    {
        return -RT_EINVAL;
    }

    in = (unsigned char *)symmetric_info->in;
    out = (unsigned char *)symmetric_info->out;

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (((rt_uint32_t)in % 4) != 0 || ((rt_uint32_t)out % 4) != 0)
    {
        in = rt_malloc(symmetric_info->length);
        if (in)
        {
            memcpy(in, symmetric_info->in, symmetric_info->length);
            out = in;
            align_flag = 1;
        }
        else
        {
            return -RT_ENOMEM;
        }
    }
#endif

    mode = symmetric_info->mode == HWCRYPTO_MODE_ENCRYPT ? CRYPTO_WAY_ENCRYPT : CRYPTO_WAY_DECRYPT;

    switch (symmetric_ctx->parent.type & (HWCRYPTO_MAIN_TYPE_MASK | HWCRYPTO_SUB_TYPE_MASK))
    {
    case HWCRYPTO_TYPE_DES_ECB:
        cbc = CRYPTO_MODE_ECB;
        break;
    case HWCRYPTO_TYPE_DES_CBC:
        cbc = CRYPTO_MODE_CBC;
        break;
    default :
        return -RT_ERROR;
    }

#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_take(&_hwcrypto->mutex, RT_WAITING_FOREVER);
#endif
    tls_crypto_des_encrypt_decrypt_adv(symmetric_ctx->key, symmetric_ctx->iv,
                                       symmetric_info->in, symmetric_info->out,
                                       symmetric_info->length, cbc, mode);
#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_release(&_hwcrypto->mutex);
#endif

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (align_flag)
    {
        memcpy(symmetric_info->out, out, symmetric_info->length);
        rt_free(in);
    }
#endif

    return RT_EOK;
}

static rt_err_t _des3_crypt(struct hwcrypto_symmetric *symmetric_ctx, struct hwcrypto_symmetric_info *symmetric_info)
{
    CRYPTO_WAY mode;
    CRYPTO_MODE cbc;
    struct wm_hwcrypto_device *_hwcrypto = (struct wm_hwcrypto_device *)symmetric_ctx->parent.device;
    unsigned char *in, *out, align_flag = 0;

    if ((symmetric_ctx->key_bitlen >> 3) != 24
            || (symmetric_info->length % 8) != 0)
    {
        return -RT_EINVAL;
    }

    in = (unsigned char *)symmetric_info->in;
    out = (unsigned char *)symmetric_info->out;

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (((rt_uint32_t)in % 4) != 0 || ((rt_uint32_t)out % 4) != 0)
    {
        in = rt_malloc(symmetric_info->length);
        if (in)
        {
            memcpy(in, symmetric_info->in, symmetric_info->length);
            out = in;
            align_flag = 1;
        }
        else
        {
            return -RT_ENOMEM;
        }
    }
#endif

    mode = symmetric_info->mode == HWCRYPTO_MODE_ENCRYPT ? CRYPTO_WAY_ENCRYPT : CRYPTO_WAY_DECRYPT;

    switch (symmetric_ctx->parent.type & (HWCRYPTO_MAIN_TYPE_MASK | HWCRYPTO_SUB_TYPE_MASK))
    {
    case HWCRYPTO_TYPE_3DES_ECB:
        cbc = CRYPTO_MODE_ECB;
        break;
    case HWCRYPTO_TYPE_3DES_CBC:
        cbc = CRYPTO_MODE_CBC;
        break;
    default :
        return -RT_ERROR;
    }

#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_take(&_hwcrypto->mutex, RT_WAITING_FOREVER);
#endif
    tls_crypto_3des_encrypt_decrypt_adv(symmetric_ctx->key, symmetric_ctx->iv,
                                        symmetric_info->in, symmetric_info->out,
                                        symmetric_info->length, cbc, mode);
#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_release(&_hwcrypto->mutex);
#endif

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (align_flag)
    {
        memcpy(symmetric_info->out, out, symmetric_info->length);
        rt_free(in);
    }
#endif

    return RT_EOK;
}

static rt_err_t _rc4_crypt(struct hwcrypto_symmetric *symmetric_ctx, struct hwcrypto_symmetric_info *symmetric_info)
{
    struct wm_hwcrypto_device *_hwcrypto = (struct wm_hwcrypto_device *)symmetric_ctx->parent.device;
    unsigned char *in, *out, align_flag = 0;

    if ((symmetric_ctx->key_bitlen >> 3) != 16)
    {
        return -RT_EINVAL;
    }

    in = (unsigned char *)symmetric_info->in;
    out = (unsigned char *)symmetric_info->out;

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (((rt_uint32_t)in % 4) != 0 || ((rt_uint32_t)out % 4) != 0)
    {
        in = rt_malloc(symmetric_info->length);
        if (in)
        {
            memcpy(in, symmetric_info->in, symmetric_info->length);
            out = in;
            align_flag = 1;
        }
        else
        {
            return -RT_ENOMEM;
        }
    }
#endif

#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_take(&_hwcrypto->mutex, RT_WAITING_FOREVER);
#endif
    tls_crypto_rc4_adv(symmetric_ctx->key, symmetric_ctx->key_bitlen >> 3,
                       (unsigned char *)symmetric_info->in,
                       symmetric_info->out,
                       symmetric_info->length);
#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_release(&_hwcrypto->mutex);
#endif

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (align_flag)
    {
        memcpy(symmetric_info->out, out, symmetric_info->length);
        rt_free(in);
    }
#endif

    return RT_EOK;
}

static rt_err_t _aes_crypt(struct hwcrypto_symmetric *symmetric_ctx, struct hwcrypto_symmetric_info *symmetric_info)
{
    CRYPTO_WAY mode;
    CRYPTO_MODE cbc;
    struct wm_hwcrypto_device *_hwcrypto = (struct wm_hwcrypto_device *)symmetric_ctx->parent.device;
    unsigned char *in, *out, align_flag = 0;

    if ((symmetric_ctx->key_bitlen >> 3) != 16
            || (symmetric_info->length % 16) != 0)
    {
        return -RT_EINVAL;
    }

    in = (unsigned char *)symmetric_info->in;
    out = (unsigned char *)symmetric_info->out;

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (((rt_uint32_t)in % 4) != 0 || ((rt_uint32_t)out % 4) != 0)
    {
        in = rt_malloc(symmetric_info->length);
        if (in)
        {
            memcpy(in, symmetric_info->in, symmetric_info->length);
            out = in;
            align_flag = 1;
        }
        else
        {
            return -RT_ENOMEM;
        }
    }
#endif

    mode = symmetric_info->mode == HWCRYPTO_MODE_ENCRYPT ? CRYPTO_WAY_ENCRYPT : CRYPTO_WAY_DECRYPT;

    switch (symmetric_ctx->parent.type & (HWCRYPTO_MAIN_TYPE_MASK | HWCRYPTO_SUB_TYPE_MASK))
    {
    case HWCRYPTO_TYPE_AES_ECB:
        cbc = CRYPTO_MODE_ECB;
        break;
    case HWCRYPTO_TYPE_AES_CBC:
        cbc = CRYPTO_MODE_CBC;
        break;
    case HWCRYPTO_TYPE_AES_CTR:
        cbc = CRYPTO_MODE_CTR;
        break;
    default :
        return -RT_ERROR;
    }

#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_take(&_hwcrypto->mutex, RT_WAITING_FOREVER);
#endif
    tls_crypto_aes_encrypt_decrypt_adv(symmetric_ctx->key, symmetric_ctx->iv,
                                       in, out, symmetric_info->length, cbc, mode);
#if !defined(WM_HWCRYPTO_NOT_LOCK)
    rt_mutex_release(&_hwcrypto->mutex);
#endif

#if !defined(WM_HWCRYPTO_NOT_ALIGN_CHECK)
    if (align_flag)
    {
        memcpy(symmetric_info->out, out, symmetric_info->length);
        rt_free(in);
    }
#endif

    return RT_EOK;
}

/**< a = b ^ c (mod d) */
static rt_err_t _bignum_exptmod(struct hwcrypto_bignum *bignum_ctx,
                    struct hw_bignum_mpi *x,
                    const struct hw_bignum_mpi *a,
                    const struct hw_bignum_mpi *b,
                    const struct hw_bignum_mpi *c)
{
	pstm_int pa, pb, pm, pres;
    u32 * buff_a = NULL;
	u32 * buff_b = NULL;
	u32 * buff_m = NULL;
	int err = -1;
    void *buff;
    int buff_len;

    pstm_init(NULL, &pres);

    buff_a = tls_mem_alloc(a->total);
	if(buff_a == NULL)
		goto out;
	buff_b = tls_mem_alloc(b->total);
	if(buff_b == NULL)
		goto out;
	buff_m = tls_mem_alloc(c->total);
	if(buff_m == NULL)
		goto out;

    memset(buff_a, 0, a->total);
    memset(buff_b, 0, b->total);
    memset(buff_m, 0, c->total);

    memcpy(buff_a, a->p, a->total);
    memcpy(buff_b, b->p, b->total);
    memcpy(buff_m, c->p, c->total);

    pstm_reverse((unsigned char *)buff_a, a->total);
	pstm_reverse((unsigned char *)buff_b, b->total);
	pstm_reverse((unsigned char *)buff_m, c->total);

//    *((volatile unsigned int *)0x40000710) = *((volatile unsigned int *)0x40000710) | (0x1 << 28);

	if ((err = pstm_init_for_read_unsigned_bin(NULL, &pa, a->total)) != PS_SUCCESS){
		goto out;
	}
	if ((err = pstm_read_unsigned_bin(&pa, (unsigned char *)buff_a, a->total)) != PS_SUCCESS) {
		goto out;
	}
	if ((err = pstm_init_for_read_unsigned_bin(NULL, &pb, b->total)) != PS_SUCCESS){
		goto out;
	}
	if ((err = pstm_read_unsigned_bin(&pb, (unsigned char *)buff_b, b->total)) != PS_SUCCESS) {
		goto out;
	}
	if ((err = pstm_init_for_read_unsigned_bin(NULL, &pm, c->total)) != PS_SUCCESS){
		goto out;
	}
	if ((err = pstm_read_unsigned_bin(&pm, (unsigned char *)buff_m, c->total)) != PS_SUCCESS) {
		goto out;
	}

    tls_crypto_exptmod(&pa, &pb, &pm, &pres);
    buff_len = pstm_unsigned_bin_size(&pres);
    buff = rt_malloc(buff_len);
    pstm_to_unsigned_bin_nr(NULL, &pres, buff);
    x->sign = pres.sign;
    x->p = buff;
    x->total = buff_len;

out:
    if(buff_a)
		tls_mem_free(buff_a);
	if(buff_b)
		tls_mem_free(buff_b);
	if(buff_m)
		tls_mem_free(buff_m);

	pstm_clear(&pa);
	pstm_clear(&pb);
	pstm_clear(&pm);
	pstm_clear(&pres);

    if (a->sign < 0)
    {
        rt_kprintf("a->sign < 0\n");
    }

    return err == PS_SUCCESS ? RT_EOK : -RT_ERROR;
}

static const struct hwcrypto_symmetric_ops aes_ops =
{
    .crypt = _aes_crypt,
};

static const struct hwcrypto_symmetric_ops rc4_ops =
{
    .crypt = _rc4_crypt,
};

static const struct hwcrypto_symmetric_ops des_ops =
{
    .crypt = _des_crypt,
};

static const struct hwcrypto_symmetric_ops des3_ops =
{
    .crypt = _des3_crypt,
};

static const struct hwcrypto_hash_ops hash_ops =
{
    .update = _hash_update,
    .finish = _hash_finish,
};

static const struct hwcrypto_rng_ops rng_ops =
{
    .update = _rng_rand,
};

static const struct hwcrypto_crc_ops crc_ops =
{
    .update = _crc_update,
};

static const struct hwcrypto_bignum_ops bignum_ops = 
{
    .add = RT_NULL,
    .sub = RT_NULL,
    .mul = RT_NULL,
    .mulmod = RT_NULL,
    .exptmod = _bignum_exptmod,
};

static rt_err_t _crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    rt_err_t res = RT_EOK;
    void *contex;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES :
        ctx->contex = RT_NULL;
        ((struct hwcrypto_symmetric *)ctx)->ops = &aes_ops;
        break;
    case HWCRYPTO_TYPE_RC4 :
        ctx->contex = RT_NULL;
        ((struct hwcrypto_symmetric *)ctx)->ops = &rc4_ops;
        break;
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
        contex = rt_malloc(sizeof(struct hash_ctx_des));
        if (contex == RT_NULL)
        {
            return -RT_ENOMEM;
        }
        memset(contex, 0, sizeof(struct hash_ctx_des));
        ctx->contex = contex;
        ((struct hwcrypto_hash *)ctx)->ops = &hash_ops;
        if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_MD5)
        {
            tls_crypto_md5_init(&((struct hash_ctx_des *)contex)->contex);
        }
        else
        {
            tls_crypto_sha1_init(&((struct hash_ctx_des *)contex)->contex);
        }
        break;
    case HWCRYPTO_TYPE_DES:
        ctx->contex = RT_NULL;
        ((struct hwcrypto_symmetric *)ctx)->ops = &des_ops;
        break;
    case HWCRYPTO_TYPE_3DES:
        ctx->contex = RT_NULL;
        ((struct hwcrypto_symmetric *)ctx)->ops = &des3_ops;
        break;
    case HWCRYPTO_TYPE_RNG:
        ctx->contex = RT_NULL;
        ((struct hwcrypto_rng *)ctx)->ops = &rng_ops;
        ctx->contex = RT_NULL;
        break;
    case HWCRYPTO_TYPE_CRC:
        ctx->contex = RT_NULL;
        ((struct hwcrypto_crc *)ctx)->ops = &crc_ops;
        break;
    case HWCRYPTO_TYPE_BIGNUM:
        ((struct hwcrypto_bignum *)ctx)->ops = &bignum_ops;
        break;
    default:
        res = -RT_ERROR;
        break;
    }

    return res;
}

static void _crypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    rt_free(ctx->contex);
}

static rt_err_t _crypto_clone(struct rt_hwcrypto_ctx *des, const struct rt_hwcrypto_ctx *src)
{
    rt_err_t res = RT_EOK;

    switch (src->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_RNG:
    case HWCRYPTO_TYPE_CRC:
    case HWCRYPTO_TYPE_BIGNUM:
        break;
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
        if (des->contex && src->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(struct hash_ctx_des));
        }
        break;
    default:
        res = -RT_ERROR;
        break;
    }

    return res;
}

static void _crypto_reset(struct rt_hwcrypto_ctx *ctx)
{
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_RC4:
    case HWCRYPTO_TYPE_RNG:
    case HWCRYPTO_TYPE_CRC:
        break;
    case HWCRYPTO_TYPE_MD5:
        tls_crypto_md5_init(&((struct hash_ctx_des *)(ctx->contex))->contex);
        break;
    case HWCRYPTO_TYPE_SHA1:
        tls_crypto_sha1_init(&((struct hash_ctx_des *)(ctx->contex))->contex);
        break;
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

extern u8 *wpa_supplicant_get_mac(void);

int wm_hw_crypto_device_init(void)
{
    static struct wm_hwcrypto_device _crypto_dev;

    _crypto_dev.dev.ops = &_ops;
    _crypto_dev.dev.id = 0;
    rt_memcpy(&_crypto_dev.dev.id, wpa_supplicant_get_mac(), 
        sizeof(_crypto_dev.dev.id) > 6 ?
        6 : sizeof(_crypto_dev.dev.id));
    _crypto_dev.dev.user_data = &_crypto_dev;

    if (rt_hwcrypto_register(&_crypto_dev.dev,
                             RT_HWCRYPTO_DEFAULT_NAME) != RT_EOK)
    {
        return -1;
    }
    rt_mutex_init(&_crypto_dev.mutex, RT_HWCRYPTO_DEFAULT_NAME, RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_DEVICE_EXPORT(wm_hw_crypto_device_init);
