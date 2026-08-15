/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "crypto.rockchip.v2"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <hwcrypto.h>
#include <hw_symmetric.h>
#include <hw_hash.h>
#include <hw_gcm.h>
#include <hw_bignum.h>

#include <drivers/reset.h>
#include <drivers/clk.h>

#include "rockchip.h"
#include "hw-crypto-rockchip-v2.h"

#define RK_CRYPTO_TIMEOUT_US            500000
#define RK_CRYPTO_DATA_ALIGN            8
#define RK_CRYPTO_AES_BLOCK             16
#define RK_CRYPTO_HASH_BLOCK            64
#define RK_CRYPTO_DES_BLOCK             8
#define RK_CRYPTO_SM4_KEYLEN            16
#define RK_CRYPTO_HMAC_KEY_MAX          64
#define RK_CRYPTO_HASH_CTX_MAGIC        0x1A1A1A1A

struct rk_crypto_lli
{
    rt_uint32_t src_addr;
    rt_uint32_t src_len;
    rt_uint32_t dst_addr;
    rt_uint32_t dst_len;
    rt_uint32_t user_define;
    rt_uint32_t reserve;
    rt_uint32_t dma_ctrl;
    rt_uint32_t next_addr;
};

struct rk_crypto_hash_ctx
{
    rt_uint32_t magic;
    rt_uint32_t digest_size;
    rt_bool_t started;
    rt_bool_t is_hmac;
    rt_uint8_t hmac_key[RK_CRYPTO_HMAC_KEY_MAX];
    rt_size_t hmac_key_len;
    rt_uint8_t leftover[RK_CRYPTO_HASH_BLOCK];
    rt_size_t leftover_len;
    struct rk_crypto_lli lli;
};

struct rk_crypto_gcm_ctx
{
    rt_uint8_t *aad;
    rt_size_t aad_len;
    rt_size_t tag_len;
    rt_bool_t started;
    rt_bool_t aad_done;
    hwcrypto_mode mode;
};

rt_inline struct rockchip_crypto *rk_crypto_from_hwdev(
        struct rt_hwcrypto_device *hwdev)
{
    return rt_container_of(hwdev, struct rockchip_crypto, parent);
}

static rt_uint32_t rk_crypto_readl(struct rockchip_crypto *rc, rt_uint32_t off)
{
    return HWREG32((rt_uint8_t *)rc->regs + off);
}

static void rk_crypto_writel(struct rockchip_crypto *rc, rt_uint32_t val, rt_uint32_t off)
{
    HWREG32((rt_uint8_t *)rc->regs + off) = val;
}

static void rk_crypto_write_masked(struct rockchip_crypto *rc, rt_uint32_t off, rt_uint32_t val)
{
    rk_crypto_writel(rc, val | (val << CRYPTO_WRITE_MASK_SHIFT), off);
}

static rt_uint32_t rk_crypto_virt_to_phys(const void *addr)
{
    return (rt_uint32_t)(rt_ubase_t)addr;
}

static rt_err_t rk_crypto_poll_reg(struct rockchip_crypto *rc, rt_uint32_t off,
        rt_uint32_t mask, rt_uint32_t expect, rt_uint32_t timeout_us)
{
    while ((rk_crypto_readl(rc, off) & mask) != expect)
    {
        if (timeout_us == 0)
        {
            return -RT_ETIMEOUT;
        }

        rt_hw_us_delay(1);
        timeout_us--;
    }

    return RT_EOK;
}

static rt_err_t rk_crypto_wait_reg_clear(struct rockchip_crypto *rc, rt_uint32_t off)
{
    return rk_crypto_poll_reg(rc, off, 0xffffffffu, 0, RK_CRYPTO_TIMEOUT_US);
}

static void rk_crypto_dcache_clean(const void *addr, rt_size_t size)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)addr, size);
}

static void rk_crypto_dcache_invalidate(void *addr, rt_size_t size)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, addr, size);
}

static rt_uint32_t rk_crypto_byte2word_be(const rt_uint8_t *ch)
{
    return ((rt_uint32_t)ch[0] << 24) | ((rt_uint32_t)ch[1] << 16) |
           ((rt_uint32_t)ch[2] << 8) | ch[3];
}

static void rk_crypto_word2byte_be(rt_uint32_t word, rt_uint8_t *ch)
{
    ch[0] = (word >> 24) & 0xff;
    ch[1] = (word >> 16) & 0xff;
    ch[2] = (word >> 8) & 0xff;
    ch[3] = word & 0xff;
}

static void rk_crypto_write_regs(struct rockchip_crypto *rc, rt_uint32_t base,
        const rt_uint8_t *data, rt_size_t len)
{
    rt_uint8_t tmp[4];
    rt_size_t i;

    for (i = 0; i + 4 <= len; i += 4)
    {
        rk_crypto_writel(rc, rk_crypto_byte2word_be(data + i), base + i);
    }

    if (len % 4)
    {
        rt_memset(tmp, 0, sizeof(tmp));
        rt_memcpy(tmp, data + i, len % 4);
        rk_crypto_writel(rc, rk_crypto_byte2word_be(tmp), base + i);
    }
}

static void rk_crypto_read_regs(struct rockchip_crypto *rc, rt_uint32_t base,
        rt_uint8_t *data, rt_size_t len)
{
    rt_uint8_t tmp[4];
    rt_size_t i;

    for (i = 0; i + 4 <= len; i += 4)
    {
        rk_crypto_word2byte_be(rk_crypto_readl(rc, base + i), data + i);
    }

    if (len % 4)
    {
        rk_crypto_word2byte_be(rk_crypto_readl(rc, base + i), tmp);
        rt_memcpy(data + i, tmp, len % 4);
    }
}

static void rk_crypto_clear_regs(struct rockchip_crypto *rc, rt_uint32_t base, rt_uint32_t words)
{
    rt_uint32_t i;

    for (i = 0; i < words; i++)
    {
        rk_crypto_writel(rc, 0, base + i * 4);
    }
}

static rt_err_t rk_crypto_hw_reset(struct rockchip_crypto *rc)
{
    rt_uint32_t val = CRYPTO_SW_CC_RESET;

    rk_crypto_writel(rc, val | (val << CRYPTO_WRITE_MASK_SHIFT), CRYPTO_RST_CTL);

    return rk_crypto_wait_reg_clear(rc, CRYPTO_RST_CTL);
}

static rt_err_t rk_crypto_wait_dma(struct rockchip_crypto *rc, rt_uint32_t expect)
{
    rt_uint32_t st;
    rt_err_t err;

    err = rk_crypto_poll_reg(rc, CRYPTO_DMA_INT_ST, expect, expect, RK_CRYPTO_TIMEOUT_US);
    if (err)
    {
        return err;
    }

    st = rk_crypto_readl(rc, CRYPTO_DMA_INT_ST);
    rk_crypto_writel(rc, st, CRYPTO_DMA_INT_ST);

    if (st & (CRYPTO_LIST_ERR_INT_ST | CRYPTO_SRC_ERR_INT_ST | CRYPTO_DST_ERR_INT_ST))
    {
        return -RT_EIO;
    }

    if ((st & expect) == 0)
    {
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_err_t rk_crypto_hash_feed(struct rockchip_crypto *rc,
        struct rk_crypto_hash_ctx *hctx, const rt_uint8_t *data,
        rt_size_t len, rt_bool_t is_last)
{
    struct rk_crypto_lli *lli = &hctx->lli;
    rt_uint32_t dma_ctl;
    rt_err_t err;

    if (!is_last && (len % RK_CRYPTO_HASH_BLOCK))
    {
        return -RT_EINVAL;
    }

    rt_memset(lli, 0, sizeof(*lli));
    lli->src_addr = rk_crypto_virt_to_phys(data);
    lli->src_len = len;
    lli->dma_ctrl = LLI_DMA_CTRL_SRC_DONE;

    if (is_last)
    {
        lli->user_define |= LLI_USER_STRING_LAST;
        lli->dma_ctrl |= LLI_DMA_CTRL_LAST;
    }
    else
    {
        lli->next_addr = rk_crypto_virt_to_phys(lli);
        lli->dma_ctrl |= LLI_DMA_CTRL_PAUSE;
    }

    if (!hctx->started)
    {
        lli->user_define |= LLI_USER_STRING_START | LLI_USER_CIPHER_START;
        rk_crypto_writel(rc, rk_crypto_virt_to_phys(lli), CRYPTO_DMA_LLI_ADDR);
        rk_crypto_write_masked(rc, CRYPTO_HASH_CTL, CRYPTO_HASH_ENABLE);
        dma_ctl = CRYPTO_DMA_START;
        hctx->started = RT_TRUE;
    }
    else
    {
        dma_ctl = CRYPTO_DMA_RESTART;
    }

    rk_crypto_dcache_clean(lli, sizeof(*lli));
    rk_crypto_dcache_clean(data, len);

    rk_crypto_write_masked(rc, CRYPTO_DMA_CTL, dma_ctl);

    err = rk_crypto_wait_dma(rc, CRYPTO_SRC_ITEM_DONE_INT_ST | CRYPTO_ZERO_LEN_INT_ST);

    return err;
}

static rt_err_t rk_crypto_hash_hw_init(struct rockchip_crypto *rc,
        struct rk_crypto_hash_ctx *hctx, hwcrypto_type type)
{
    rt_uint32_t reg_ctrl = 0;
    rt_err_t err;

    err = rk_crypto_hw_reset(rc);
    if (err)
    {
        return err;
    }

    switch (type)
    {
    case HWCRYPTO_TYPE_SHA1:
        reg_ctrl |= CRYPTO_SHA1;
        hctx->digest_size = 20;
        break;
    case HWCRYPTO_TYPE_SHA224:
        reg_ctrl |= CRYPTO_SHA224;
        hctx->digest_size = 28;
        break;
    case HWCRYPTO_TYPE_SHA256:
        reg_ctrl |= CRYPTO_SHA256;
        hctx->digest_size = 32;
        break;
    case HWCRYPTO_TYPE_SHA384:
        reg_ctrl |= CRYPTO_SHA384;
        hctx->digest_size = 48;
        break;
    case HWCRYPTO_TYPE_SHA512:
        reg_ctrl |= CRYPTO_SHA512;
        hctx->digest_size = 64;
        break;
    case HWCRYPTO_TYPE_MD5:
        reg_ctrl |= CRYPTO_MD5;
        hctx->digest_size = 16;
        break;
    default:
        return -RT_ENOSYS;
    }

    if (hctx->is_hmac && hctx->hmac_key_len == 0)
    {
        return -RT_EINVAL;
    }

    rk_crypto_clear_regs(rc, CRYPTO_HASH_DOUT_0, 16);

    reg_ctrl |= CRYPTO_HW_PAD_ENABLE;
    if (hctx->is_hmac)
    {
        reg_ctrl |= CRYPTO_HMAC_ENABLE;
    }
    rk_crypto_write_masked(rc, CRYPTO_HASH_CTL, reg_ctrl);

    if (hctx->is_hmac)
    {
        rk_crypto_clear_regs(rc, CRYPTO_CH0_KEY_0, 8);
        rk_crypto_write_regs(rc, CRYPTO_CH0_KEY_0, hctx->hmac_key, hctx->hmac_key_len);
    }
    rk_crypto_write_masked(rc, CRYPTO_FIFO_CTL,
            CRYPTO_DOUT_BYTESWAP | CRYPTO_DOIN_BYTESWAP);
    rk_crypto_writel(rc, 0, CRYPTO_DMA_INT_EN);

    hctx->magic = RK_CRYPTO_HASH_CTX_MAGIC;
    hctx->started = RT_FALSE;
    hctx->leftover_len = 0;

    return RT_EOK;
}

static rt_err_t rk_crypto_hash_update(struct hwcrypto_hash *ctx,
        const rt_uint8_t *in, rt_size_t length)
{
    struct rockchip_crypto *rc = rk_crypto_from_hwdev(ctx->parent.device);
    struct rk_crypto_hash_ctx *hctx = ctx->parent.contex;
    rt_uint8_t *buf = RT_NULL;
    rt_size_t buf_len = 0;
    rt_size_t offset = 0;
    rt_err_t err = RT_EOK;

    if (!hctx)
    {
        return -RT_EINVAL;
    }

    if (hctx->magic && hctx->magic != RK_CRYPTO_HASH_CTX_MAGIC)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&rc->mutex, RT_WAITING_FOREVER);

    if (hctx->digest_size == 0)
    {
        err = rk_crypto_hash_hw_init(rc, hctx, ctx->parent.type);
        if (err)
        {
            goto _out;
        }
    }

    if (hctx->leftover_len)
    {
        buf_len = hctx->leftover_len + length;
        buf = rt_malloc(buf_len);
        if (!buf)
        {
            err = -RT_ENOMEM;
            goto _out;
        }

        rt_memcpy(buf, hctx->leftover, hctx->leftover_len);
        rt_memcpy(buf + hctx->leftover_len, in, length);
        hctx->leftover_len = 0;
        in = buf;
        length = buf_len;
    }

    while (offset + RK_CRYPTO_HASH_BLOCK <= length)
    {
        err = rk_crypto_hash_feed(rc, hctx, in + offset,
                RK_CRYPTO_HASH_BLOCK, RT_FALSE);
        if (err)
        {
            goto _out;
        }
        offset += RK_CRYPTO_HASH_BLOCK;
    }

    if (offset < length)
    {
        hctx->leftover_len = length - offset;
        rt_memcpy(hctx->leftover, in + offset, hctx->leftover_len);
    }

_out:
    if (buf)
    {
        rt_free(buf);
    }
    rt_mutex_release(&rc->mutex);

    return err;
}

static rt_err_t rk_crypto_hash_finish(struct hwcrypto_hash *ctx,
        rt_uint8_t *out, rt_size_t length)
{
    struct rockchip_crypto *rc = rk_crypto_from_hwdev(ctx->parent.device);
    struct rk_crypto_hash_ctx *hctx = ctx->parent.contex;
    rt_err_t err;

    if (!out || !hctx)
    {
        return -RT_EINVAL;
    }

    if (hctx->magic && hctx->magic != RK_CRYPTO_HASH_CTX_MAGIC)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&rc->mutex, RT_WAITING_FOREVER);

    if (hctx->digest_size == 0)
    {
        err = rk_crypto_hash_hw_init(rc, hctx, ctx->parent.type);
        if (err)
        {
            goto _out;
        }
    }

    if (length < hctx->digest_size)
    {
        err = -RT_EINVAL;
        goto _out;
    }

    err = rk_crypto_hash_feed(rc, hctx, hctx->leftover, hctx->leftover_len, RT_TRUE);
    if (err)
    {
        goto _out;
    }

    err = rk_crypto_poll_reg(rc, CRYPTO_HASH_VALID,
            CRYPTO_HASH_IS_VALID, CRYPTO_HASH_IS_VALID, RK_CRYPTO_TIMEOUT_US);
    if (err)
    {
        goto _out;
    }

    rk_crypto_read_regs(rc, CRYPTO_HASH_DOUT_0, out, hctx->digest_size);
    rk_crypto_writel(rc, CRYPTO_HASH_IS_VALID, CRYPTO_HASH_VALID);
    rk_crypto_write_masked(rc, CRYPTO_HASH_CTL, 0);

    hctx->digest_size = 0;
    hctx->magic = 0;

_out:
    rt_mutex_release(&rc->mutex);

    return err;
}

static rt_err_t rk_crypto_set_pc_len(struct rockchip_crypto *rc, rt_uint32_t chn, rt_uint64_t len)
{
    rt_uint32_t base = CRYPTO_CH0_PC_LEN_0 + chn * 8;

    rk_crypto_writel(rc, (rt_uint32_t)len, base);
    rk_crypto_writel(rc, (rt_uint32_t)(len >> 32), base + 4);

    return RT_EOK;
}

static rt_err_t rk_crypto_set_aad_len(struct rockchip_crypto *rc, rt_uint32_t chn, rt_uint64_t len)
{
    rt_uint32_t base = CRYPTO_CH0_AAD_LEN_0 + chn * 8;

    rk_crypto_writel(rc, (rt_uint32_t)len, base);
    rk_crypto_writel(rc, (rt_uint32_t)(len >> 32), base + 4);

    return RT_EOK;
}

static rt_err_t rk_crypto_read_tag(struct rockchip_crypto *rc, rt_uint32_t chn,
        rt_uint8_t *tag, rt_size_t tag_len)
{
    rt_uint32_t base = CRYPTO_CH0_TAG_0 + chn * 0x10;

    rk_crypto_read_regs(rc, base, tag, tag_len);
    return RT_EOK;
}

static rt_err_t rk_crypto_wait_tag_valid(struct rockchip_crypto *rc, rt_uint32_t chn)
{
    rt_uint32_t mask = CRYPTO_CH0_TAG_VALID << chn;

    return rk_crypto_poll_reg(rc, CRYPTO_TAG_VALID, mask, mask, RK_CRYPTO_TIMEOUT_US);
}

static rt_err_t rk_crypto_decode_sym_type(hwcrypto_type type, rt_uint32_t *bc_alg,
        rt_uint32_t *bc_mode, rt_size_t *block_size, rt_bool_t *need_iv, rt_bool_t *ctr_mode)
{
    rt_uint32_t sub = (type >> 8) & 0xff;

    *ctr_mode = RT_FALSE;
    *need_iv = RT_TRUE;

    switch (type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
        *bc_alg = CRYPTO_BC_AES;
        *block_size = RK_CRYPTO_AES_BLOCK;
        break;
    case HWCRYPTO_TYPE_DES:
        *bc_alg = CRYPTO_BC_DES;
        *block_size = RK_CRYPTO_DES_BLOCK;
        break;
    case HWCRYPTO_TYPE_3DES:
        *bc_alg = CRYPTO_BC_TDES;
        *block_size = RK_CRYPTO_DES_BLOCK;
        break;
    default:
        return -RT_ENOSYS;
    }

    switch (sub)
    {
    case 0x01:
        *bc_mode = CRYPTO_BC_ECB;
        *need_iv = RT_FALSE;
        break;
    case 0x02:
        *bc_mode = CRYPTO_BC_CBC;
        break;
    case 0x03:
        *bc_mode = CRYPTO_BC_CFB;
        break;
    case 0x04:
        *bc_mode = CRYPTO_BC_CTR;
        *ctr_mode = RT_TRUE;
        break;
    case 0x05:
        *bc_mode = CRYPTO_BC_OFB;
        break;
    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t rk_crypto_decode_gcm_alg(hwcrypto_type crypt_type, rt_uint32_t *bc_alg)
{
    switch (crypt_type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
        *bc_alg = CRYPTO_BC_AES;
        return RT_EOK;
    default:
        return -RT_ENOSYS;
    }
}

static rt_err_t rk_crypto_cipher_setup(struct rockchip_crypto *rc,
        struct hwcrypto_symmetric *sym, hwcrypto_type effective_type,
        hwcrypto_mode mode, rt_bool_t gcm_mode)
{
    rt_uint32_t bc_alg, bc_mode;
    rt_size_t block_size;
    rt_bool_t need_iv, ctr_mode;
    rt_uint32_t reg_ctrl = 0;
    rt_uint32_t key_len = sym->key_bitlen >> 3;
    rt_err_t err;

    if (gcm_mode)
    {
        err = rk_crypto_decode_gcm_alg(effective_type, &bc_alg);
        if (err)
        {
            return err;
        }
        bc_mode = CRYPTO_BC_GCM;
        block_size = RK_CRYPTO_AES_BLOCK;
        need_iv = RT_TRUE;
        ctr_mode = RT_FALSE;
    }
    else
    {
        err = rk_crypto_decode_sym_type(effective_type, &bc_alg, &bc_mode,
                &block_size, &need_iv, &ctr_mode);
        if (err)
        {
            return err;
        }
    }

    reg_ctrl |= bc_alg | bc_mode;

    if (bc_alg == CRYPTO_BC_AES)
    {
        switch (key_len)
        {
        case 16:
            reg_ctrl |= CRYPTO_BC_128_bit_key;
            break;
        case 24:
            reg_ctrl |= CRYPTO_BC_192_bit_key;
            break;
        case 32:
            reg_ctrl |= CRYPTO_BC_256_bit_key;
            break;
        default:
            return -RT_EINVAL;
        }
    }
    else if (bc_alg == CRYPTO_BC_DES)
    {
        if (key_len != RK_CRYPTO_DES_BLOCK)
        {
            return -RT_EINVAL;
        }
    }
    else if (bc_alg == CRYPTO_BC_TDES)
    {
        if (key_len != 16 && key_len != 24)
        {
            return -RT_EINVAL;
        }
    }

    if (mode == HWCRYPTO_MODE_DECRYPT)
    {
        reg_ctrl |= CRYPTO_BC_DECRYPT;
    }

    rk_crypto_clear_regs(rc, CRYPTO_CH0_KEY_0, 8);
    rk_crypto_write_regs(rc, CRYPTO_CH0_KEY_0, sym->key, key_len);

    if (need_iv || gcm_mode)
    {
        if (!sym->iv_len || sym->iv_len > RK_CRYPTO_AES_BLOCK)
        {
            return -RT_EINVAL;
        }
        rk_crypto_clear_regs(rc, CRYPTO_CH0_IV_0, 4);
        rk_crypto_write_regs(rc, CRYPTO_CH0_IV_0, sym->iv, sym->iv_len);
        rk_crypto_writel(rc, sym->iv_len, CRYPTO_CH0_IV_LEN_0);
    }

    rk_crypto_write_masked(rc, CRYPTO_FIFO_CTL,
            CRYPTO_DOUT_BYTESWAP | CRYPTO_DOIN_BYTESWAP);
    rk_crypto_writel(rc, 0, CRYPTO_DMA_INT_EN);
    rk_crypto_write_masked(rc, CRYPTO_BC_CTL, reg_ctrl);

    return RT_EOK;
}

static rt_err_t rk_crypto_cipher_dma(struct rockchip_crypto *rc,
        const rt_uint8_t *in, rt_uint8_t *out, rt_size_t in_len, rt_size_t out_len,
        struct rk_crypto_lli *aad_lli, rt_size_t aad_len)
{
    struct rk_crypto_lli lli;
    rt_uint8_t *dma_in = RT_NULL;
    rt_uint8_t *dma_out = RT_NULL;
    rt_err_t err;

    if (((rt_ubase_t)in % RK_CRYPTO_DATA_ALIGN) == 0)
    {
        dma_in = (rt_uint8_t *)in;
    }
    else
    {
        dma_in = rt_malloc_align(in_len, RK_CRYPTO_DATA_ALIGN);
        if (!dma_in)
        {
            return -RT_ENOMEM;
        }
        rt_memcpy(dma_in, in, in_len);
    }

    if (out)
    {
        if (((rt_ubase_t)out % RK_CRYPTO_DATA_ALIGN) == 0)
        {
            dma_out = out;
        }
        else
        {
            dma_out = rt_malloc_align(out_len, RK_CRYPTO_DATA_ALIGN);
            if (!dma_out)
            {
                err = -RT_ENOMEM;
                goto _out;
            }
        }
    }

    rt_memset(&lli, 0, sizeof(lli));
    lli.src_addr = rk_crypto_virt_to_phys(dma_in);
    lli.src_len = in_len;
    if (dma_out)
    {
        lli.dst_addr = rk_crypto_virt_to_phys(dma_out);
        lli.dst_len = out_len;
    }
    lli.dma_ctrl = LLI_DMA_CTRL_LAST | LLI_DMA_CTRL_DST_DONE;
    lli.user_define = LLI_USER_CIPHER_START | LLI_USER_STRING_START | LLI_USER_STRING_LAST;

    if (aad_lli && aad_len)
    {
        aad_lli->next_addr = rk_crypto_virt_to_phys(&lli);
        aad_lli->user_define = LLI_USER_CIPHER_START | LLI_USER_STRING_START |
                LLI_USER_STRING_LAST | LLI_USER_STRING_AAD;
        rk_crypto_dcache_clean(aad_lli, sizeof(*aad_lli));
        rk_crypto_writel(rc, rk_crypto_virt_to_phys(aad_lli), CRYPTO_DMA_LLI_ADDR);
        lli.user_define = LLI_USER_STRING_START | LLI_USER_STRING_LAST;
    }
    else
    {
        rk_crypto_writel(rc, rk_crypto_virt_to_phys(&lli), CRYPTO_DMA_LLI_ADDR);
    }

    rk_crypto_dcache_clean(&lli, sizeof(lli));
    rk_crypto_dcache_clean(dma_in, in_len);
    if (dma_out)
    {
        rk_crypto_dcache_invalidate(dma_out, out_len);
    }

    rk_crypto_write_masked(rc, CRYPTO_BC_CTL,
            rk_crypto_readl(rc, CRYPTO_BC_CTL) | CRYPTO_BC_ENABLE);
    rk_crypto_write_masked(rc, CRYPTO_DMA_CTL, CRYPTO_DMA_START);

    err = rk_crypto_wait_dma(rc, CRYPTO_DST_ITEM_DONE_INT_ST);
    if (err)
    {
        goto _out;
    }

    if (dma_out)
    {
        rk_crypto_dcache_invalidate(dma_out, out_len);
        if (dma_out != out)
        {
            rt_memcpy(out, dma_out, out_len);
        }
    }

_out:
    if (dma_in && dma_in != in)
    {
        rt_free_align(dma_in);
    }
    if (dma_out && dma_out != out)
    {
        rt_free_align(dma_out);
    }

    return err;
}

static rt_err_t rk_crypto_cipher_crypt(struct hwcrypto_symmetric *sym,
        struct hwcrypto_symmetric_info *info)
{
    struct rockchip_crypto *rc = rk_crypto_from_hwdev(sym->parent.device);
    hwcrypto_type effective_type = sym->parent.type;
    rt_size_t block_size = RK_CRYPTO_AES_BLOCK;
    const rt_uint8_t *in_buf = info->in;
    rt_uint8_t *out_buf = info->out;
    rt_uint8_t *tmp_in = RT_NULL;
    rt_uint8_t *tmp_out = RT_NULL;
    rt_bool_t need_iv, ctr_mode;
    rt_uint32_t bc_alg, bc_mode;
    rt_size_t tmp_len;
    rt_err_t err;

    if (!info->length)
    {
        return -RT_EINVAL;
    }

    if ((effective_type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_GCM)
    {
        struct hwcrypto_gcm *gcm = (struct hwcrypto_gcm *)sym;
        effective_type = gcm->crypt_type;
    }

    err = rk_crypto_decode_sym_type(effective_type, &bc_alg, &bc_mode,
            &block_size, &need_iv, &ctr_mode);
    if (err)
    {
        return err;
    }

    if (ctr_mode)
    {
        tmp_len = (info->length + block_size - 1) / block_size * block_size;
    }
    else if (info->length % block_size)
    {
        return -RT_EINVAL;
    }
    else
    {
        tmp_len = info->length;
    }

    if (ctr_mode && tmp_len != info->length)
    {
        tmp_in = rt_calloc(1, tmp_len);
        tmp_out = rt_malloc(tmp_len);
        if (!tmp_in || !tmp_out)
        {
            err = -RT_ENOMEM;
            goto _cleanup;
        }

        rt_memcpy(tmp_in, info->in, info->length);
        in_buf = tmp_in;
        out_buf = tmp_out;
    }

    rt_mutex_take(&rc->mutex, RT_WAITING_FOREVER);

    err = rk_crypto_cipher_setup(rc, sym, effective_type, info->mode, RT_FALSE);
    if (err)
    {
        goto _out;
    }

    err = rk_crypto_cipher_dma(rc, in_buf, out_buf, tmp_len, tmp_len, RT_NULL, 0);

_out:
    rt_mutex_release(&rc->mutex);

_cleanup:
    if (!err && tmp_out)
    {
        rt_memcpy(info->out, tmp_out, info->length);
    }
    if (tmp_in)
    {
        rt_free(tmp_in);
    }
    if (tmp_out)
    {
        rt_free(tmp_out);
    }

    return err;
}

static rt_err_t rk_crypto_gcm_start(struct hwcrypto_gcm *gcm,
        const rt_uint8_t *add, rt_size_t add_len)
{
    struct rockchip_crypto *rc = rk_crypto_from_hwdev(gcm->parent.parent.device);
    struct rk_crypto_gcm_ctx *gctx = gcm->parent.parent.contex;
    rt_err_t err;

    if (!gctx || (add_len && !add))
    {
        return -RT_EINVAL;
    }

    if (gctx->aad)
    {
        rt_free(gctx->aad);
        gctx->aad = RT_NULL;
    }

    gctx->aad_len = add_len;
    gctx->started = RT_FALSE;
    gctx->aad_done = RT_FALSE;
    gctx->mode = HWCRYPTO_MODE_ENCRYPT;

    if (add_len)
    {
        gctx->aad = rt_malloc(add_len);
        if (!gctx->aad)
        {
            return -RT_ENOMEM;
        }
        rt_memcpy(gctx->aad, add, add_len);
    }

    rt_mutex_take(&rc->mutex, RT_WAITING_FOREVER);
    err = rk_crypto_hw_reset(rc);
    rt_mutex_release(&rc->mutex);

    return err;
}

static rt_err_t rk_crypto_gcm_finish(struct hwcrypto_gcm *gcm,
        const rt_uint8_t *tag, rt_size_t tag_len)
{
    struct rockchip_crypto *rc = rk_crypto_from_hwdev(gcm->parent.parent.device);
    struct rk_crypto_gcm_ctx *gctx = gcm->parent.parent.contex;
    rt_uint8_t hw_tag[RK_CRYPTO_AES_BLOCK];
    rt_err_t err;

    if (!gctx || !tag || !tag_len || tag_len > RK_CRYPTO_AES_BLOCK)
    {
        return -RT_EINVAL;
    }

    gctx->tag_len = tag_len;

    rt_mutex_take(&rc->mutex, RT_WAITING_FOREVER);

    err = rk_crypto_wait_tag_valid(rc, 0);
    if (err)
    {
        goto _out;
    }

    rk_crypto_read_tag(rc, 0, hw_tag, tag_len);

    if (gctx->mode == HWCRYPTO_MODE_DECRYPT)
    {
        if (rt_memcmp(hw_tag, tag, tag_len) != 0)
        {
            err = -RT_EINVAL;
        }
    }
    else
    {
        rt_memcpy((rt_uint8_t *)tag, hw_tag, tag_len);
    }

_out:
    rt_mutex_release(&rc->mutex);

    return err;
}

static rt_err_t rk_crypto_gcm_crypt_locked(struct hwcrypto_gcm *gcm,
        hwcrypto_mode mode, rt_size_t length, const rt_uint8_t *in, rt_uint8_t *out)
{
    struct rockchip_crypto *rc = rk_crypto_from_hwdev(gcm->parent.parent.device);
    struct rk_crypto_gcm_ctx *gctx = gcm->parent.parent.contex;
    struct rk_crypto_lli aad_lli;
    rt_uint8_t *aad_dma = RT_NULL;
    rt_err_t err;

    if (!gctx)
    {
        return -RT_EINVAL;
    }

    gctx->mode = mode;

    if (!gctx->started)
    {
        err = rk_crypto_cipher_setup(rc, &gcm->parent, gcm->crypt_type, mode, RT_TRUE);
        if (err)
        {
            return err;
        }

        if (gctx->aad_len)
        {
            rk_crypto_set_aad_len(rc, 0, gctx->aad_len);
            rk_crypto_set_pc_len(rc, 0, length);

            if (((rt_ubase_t)gctx->aad % RK_CRYPTO_DATA_ALIGN) == 0)
            {
                aad_dma = gctx->aad;
            }
            else
            {
                aad_dma = rt_malloc_align(gctx->aad_len, RK_CRYPTO_DATA_ALIGN);
                if (!aad_dma)
                {
                    return -RT_ENOMEM;
                }
                rt_memcpy(aad_dma, gctx->aad, gctx->aad_len);
            }

            rt_memset(&aad_lli, 0, sizeof(aad_lli));
            aad_lli.src_addr = rk_crypto_virt_to_phys(aad_dma);
            aad_lli.src_len = gctx->aad_len;
            rk_crypto_dcache_clean(aad_dma, gctx->aad_len);
        }

        gctx->started = RT_TRUE;
    }
    else
    {
        rk_crypto_set_pc_len(rc, 0, length);
    }

    err = rk_crypto_cipher_dma(rc, in, out, length, length,
            gctx->aad_len ? &aad_lli : RT_NULL, gctx->aad_len);

    if (aad_dma && aad_dma != gctx->aad)
    {
        rt_free_align(aad_dma);
    }

    return err;
}

static rt_err_t rk_crypto_gcm_crypt_wrapper(struct hwcrypto_symmetric *sym,
        struct hwcrypto_symmetric_info *info)
{
    struct hwcrypto_gcm *gcm = (struct hwcrypto_gcm *)sym;
    struct rockchip_crypto *rc = rk_crypto_from_hwdev(sym->parent.device);
    rt_err_t err;

    rt_mutex_take(&rc->mutex, RT_WAITING_FOREVER);
    err = rk_crypto_gcm_crypt_locked(gcm, info->mode, info->length, info->in, info->out);
    rt_mutex_release(&rc->mutex);

    return err;
}

static const struct hwcrypto_hash_ops rk_crypto_hash_ops =
{
    .update = rk_crypto_hash_update,
    .finish = rk_crypto_hash_finish,
};

static const struct hwcrypto_symmetric_ops rk_crypto_gcm_sym_ops =
{
    .crypt = rk_crypto_gcm_crypt_wrapper,
};

static const struct hwcrypto_symmetric_ops rk_crypto_sym_ops =
{
    .crypt = rk_crypto_cipher_crypt,
};

static const struct hwcrypto_gcm_ops rk_crypto_gcm_ops =
{
    .start = rk_crypto_gcm_start,
    .finish = rk_crypto_gcm_finish,
};

static rt_bool_t rk_crypto_is_hash_type(hwcrypto_type type)
{
    switch (type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
        return RT_TRUE;
    default:
        return RT_FALSE;
    }
}

static rt_err_t rockchip_crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
        ((struct hwcrypto_symmetric *)ctx)->ops = &rk_crypto_sym_ops;
        break;
    case HWCRYPTO_TYPE_GCM:
        ctx->contex = rt_calloc(1, sizeof(struct rk_crypto_gcm_ctx));
        if (!ctx->contex)
        {
            return -RT_ENOMEM;
        }
        ((struct hwcrypto_gcm *)ctx)->ops = &rk_crypto_gcm_ops;
        ((struct hwcrypto_gcm *)ctx)->parent.ops = &rk_crypto_gcm_sym_ops;
        break;
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
        ctx->contex = rt_calloc(1, sizeof(struct rk_crypto_hash_ctx));
        if (!ctx->contex)
        {
            return -RT_ENOMEM;
        }
        ((struct hwcrypto_hash *)ctx)->ops = &rk_crypto_hash_ops;
        break;
    case HWCRYPTO_TYPE_BIGNUM:
        ((struct hwcrypto_bignum *)ctx)->ops = rk_crypto_bignum_ops_get();
        if (!((struct hwcrypto_bignum *)ctx)->ops)
        {
            return -RT_ENOSYS;
        }
        break;
    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static void rockchip_crypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_GCM)
    {
        struct rk_crypto_gcm_ctx *gctx = ctx->contex;

        if (gctx)
        {
            rt_free(gctx->aad);
        }
    }

    rt_free(ctx->contex);
    ctx->contex = RT_NULL;
}

static rt_err_t rockchip_crypto_copy(struct rt_hwcrypto_ctx *des,
        const struct rt_hwcrypto_ctx *src)
{
    if ((des->type & HWCRYPTO_MAIN_TYPE_MASK) != (src->type & HWCRYPTO_MAIN_TYPE_MASK))
    {
        return -RT_EINVAL;
    }

    switch (des->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
        return RT_EOK;
    case HWCRYPTO_TYPE_GCM:
        if (src->contex && des->contex)
        {
            struct rk_crypto_gcm_ctx *dctx = des->contex;
            struct rk_crypto_gcm_ctx *sctx = src->contex;

            rt_free(dctx->aad);
            dctx->aad = RT_NULL;
            if (sctx->aad_len)
            {
                dctx->aad = rt_malloc(sctx->aad_len);
                if (!dctx->aad)
                {
                    return -RT_ENOMEM;
                }
                rt_memcpy(dctx->aad, sctx->aad, sctx->aad_len);
            }
            dctx->aad_len = sctx->aad_len;
            dctx->tag_len = sctx->tag_len;
            dctx->started = sctx->started;
            dctx->aad_done = sctx->aad_done;
            dctx->mode = sctx->mode;
            ((struct hwcrypto_gcm *)des)->crypt_type = ((struct hwcrypto_gcm *)src)->crypt_type;
            return RT_EOK;
        }
        return -RT_EINVAL;
    case HWCRYPTO_TYPE_MD5:
    case HWCRYPTO_TYPE_SHA1:
    case HWCRYPTO_TYPE_SHA2:
        if (src->contex && des->contex)
        {
            rt_memcpy(des->contex, src->contex, sizeof(struct rk_crypto_hash_ctx));
            return RT_EOK;
        }
        return -RT_EINVAL;
    case HWCRYPTO_TYPE_BIGNUM:
        return RT_EOK;
    default:
        return -RT_ENOSYS;
    }
}

static void rockchip_crypto_reset(struct rt_hwcrypto_ctx *ctx)
{
    struct rk_crypto_hash_ctx *hctx = ctx->contex;

    if (rk_crypto_is_hash_type(ctx->type) && hctx)
    {
        rt_memset(hctx, 0, sizeof(*hctx));
    }
    else if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_GCM && ctx->contex)
    {
        struct rk_crypto_gcm_ctx *gctx = ctx->contex;

        rt_free(gctx->aad);
        rt_memset(gctx, 0, sizeof(*gctx));
    }
}

static const struct rt_hwcrypto_ops rockchip_crypto_ops =
{
    .create = rockchip_crypto_create,
    .destroy = rockchip_crypto_destroy,
    .copy = rockchip_crypto_copy,
    .reset = rockchip_crypto_reset,
};

static void rockchip_crypto_free(struct rockchip_crypto *rc)
{
    if (rc->regs)
    {
        rt_iounmap(rc->regs);
    }

    if (!rt_is_err_or_null(rc->rstc))
    {
        rt_reset_control_assert(rc->rstc);
        rt_reset_control_put(rc->rstc);
    }

    if (!rt_is_err_or_null(rc->clk_arr))
    {
        rt_clk_array_disable_unprepare(rc->clk_arr);
        rt_clk_array_put(rc->clk_arr);
    }

    rt_mutex_delete(&rc->mutex);
    rt_free(rc);
}

static rt_err_t rockchip_crypto_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_crypto *rc = rt_calloc(1, sizeof(*rc));

    if (!rc)
    {
        return -RT_ENOMEM;
    }

    rt_mutex_init(&rc->mutex, "rk-crypto", RT_IPC_FLAG_PRIO);

    rc->regs = rt_dm_dev_iomap(dev, 0);
    if (!rc->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rc->rstc = rt_reset_control_get_by_name(dev, "crypto-rst");
    if (!rt_is_err(rc->rstc))
    {
        rt_reset_control_assert(rc->rstc);
        rt_hw_us_delay(10);
        rt_reset_control_deassert(rc->rstc);
    }

    rc->clk_arr = rt_clk_get_array(dev);
    if (rt_is_err(rc->clk_arr))
    {
        err = rt_ptr_err(rc->clk_arr);
        goto _fail;
    }

    err = rt_clk_array_prepare_enable(rc->clk_arr);
    if (err)
    {
        goto _fail;
    }

    dev->user_data = rc;
    rc->parent.user_data = rc;
    rc->parent.ops = &rockchip_crypto_ops;

    err = rt_hwcrypto_register(&rc->parent, RT_HWCRYPTO_DEFAULT_NAME);
    if (err)
    {
        goto _fail;
    }

    rk_crypto_pka_init(rc);
    rk_crypto_ecc_init(rc);
#ifdef RT_HWCRYPTO_USING_BIGNUM
    rt_hwcrypto_bignum_default(&rc->parent);
#endif

    return RT_EOK;

_fail:
    rockchip_crypto_free(rc);

    return err;
}

static rt_err_t rockchip_crypto_remove(struct rt_platform_device *pdev)
{
    struct rockchip_crypto *rc = pdev->parent.user_data;

    if (!rc)
    {
        return RT_EOK;
    }

    pdev->parent.user_data = RT_NULL;
    rt_device_unregister(&rc->parent.parent);
    rockchip_crypto_free(rc);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_crypto_ids[] =
{
    { .compatible = "rockchip,rk3568-crypto" },
    { .compatible = "rockchip,rk3588-crypto" },
    { /* sentinel */ },
};

static struct rt_platform_driver rockchip_crypto_driver =
{
    .name = "rockchip-crypto-v2",
    .ids = rockchip_crypto_ids,

    .probe = rockchip_crypto_probe,
    .remove = rockchip_crypto_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_crypto_driver);

#ifdef RT_HWCRYPTO_USING_BIGNUM

#define CRYPTO_TRACE(...)
#define RK_BN_DEFAULT_ENDIAN        RK_BG_LITTILE_ENDIAN
#define RK_BN_BYTES2WORDS(bytes)    (((bytes) + sizeof(rt_uint32_t) - 1) / sizeof(rt_uint32_t))
#define RK_BN_WORDS2BYTES(words)    ((words) * sizeof(rt_uint32_t))
#define RK_BN_WORD_SIZE             32

static void rk_reverse_memcpy(void *dst, const void *src, rt_uint32_t size)
{
    char *_dst = (char *)dst;
    char *_src = (char *)src;
    rt_uint32_t i;

    if (!dst || !src || !size)
    {
        return;
    }

    for (i = 0; i < size; ++i)
    {
        _dst[size - i - 1] = _src[i];
    }
}

struct rk_bignum *rk_bn_alloc(rt_uint32_t max_size)
{
    struct rk_bignum *bn;
    rt_uint32_t words = RK_BN_BYTES2WORDS(max_size);

    bn = rt_calloc(1, sizeof(*bn));
    if (!bn)
    {
        return RT_NULL;
    }

    bn->data = rt_calloc(words, sizeof(rt_uint32_t));
    if (!bn->data)
    {
        rt_free(bn);
        return RT_NULL;
    }

    bn->n_words = words;

    return bn;
}

void rk_bn_free(struct rk_bignum *bn)
{
    if (!bn)
    {
        return;
    }

    if (bn->data)
    {
        rt_memset(bn->data, 0, RK_BN_WORDS2BYTES(bn->n_words));
        rt_free(bn->data);
    }

    rt_free(bn);
}

rt_err_t rk_bn_set_data(struct rk_bignum *bn, const rt_uint8_t *data,
        rt_uint32_t size, enum rk_bignum_endian endian)
{
    if (!bn || !data)
    {
        return -RT_EINVAL;
    }

    if (RK_BN_BYTES2WORDS(size) > bn->n_words)
    {
        return -RT_EINVAL;
    }

    if (endian == RK_BN_DEFAULT_ENDIAN)
    {
        rt_memcpy(bn->data, data, size);
    }
    else
    {
        rk_reverse_memcpy(bn->data, data, size);
    }

    return RT_EOK;
}

rt_err_t rk_bn_get_data(const struct rk_bignum *bn, rt_uint8_t *data,
        rt_uint32_t size, enum rk_bignum_endian endian)
{
    if (!bn || !data)
    {
        return -RT_EINVAL;
    }

    if (size < RK_BN_WORDS2BYTES(bn->n_words))
    {
        return -RT_EINVAL;
    }

    rt_memset(data, 0, size);

    if (endian == RK_BN_DEFAULT_ENDIAN)
    {
        rt_memcpy(data + size - RK_BN_WORDS2BYTES(bn->n_words),
                bn->data, RK_BN_WORDS2BYTES(bn->n_words));
    }
    else
    {
        rk_reverse_memcpy(data + size - RK_BN_WORDS2BYTES(bn->n_words),
                bn->data, RK_BN_WORDS2BYTES(bn->n_words));
    }

    return RT_EOK;
}

rt_uint32_t rk_bn_get_size(const struct rk_bignum *bn)
{
    if (!bn)
    {
        return 0;
    }

    return RK_BN_WORDS2BYTES(bn->n_words);
}

int rk_bn_highest_bit(const struct rk_bignum *bn)
{
    rt_uint32_t w;
    rt_uint32_t b;

    if (!bn || !bn->data || !bn->n_words)
    {
        return -1;
    }

    w = bn->data[bn->n_words - 1];

    for (b = 0; b < RK_BN_WORD_SIZE; b++)
    {
        w >>= 1;
        if (w == 0)
        {
            break;
        }
    }

    return (int)(bn->n_words - 1) * RK_BN_WORD_SIZE + b;
}

void rk_ecc_free_point(struct rk_ecp_point *point)
{
    if (!point)
    {
        return;
    }

    rk_bn_free(point->x);
    rk_bn_free(point->y);
    rt_free(point);
}

struct rk_ecp_point *rk_ecc_alloc_point_zero(rt_uint32_t max_size)
{
    struct rk_ecp_point *point = rt_calloc(1, sizeof(*point));

    if (!point)
    {
        return RT_NULL;
    }

    point->x = rk_bn_alloc(max_size);
    if (!point->x)
    {
        goto error;
    }

    point->y = rk_bn_alloc(max_size);
    if (!point->y)
    {
        goto error;
    }

    return point;

error:
    rk_ecc_free_point(point);

    return RT_NULL;
}

struct rk_ecp_point *rk_ecc_alloc_point(const rt_uint8_t *x, rt_uint32_t x_len,
        const rt_uint8_t *y, rt_uint32_t y_len,
        enum rk_bignum_endian endian, rt_uint32_t max_size)
{
    struct rk_ecp_point *point = rt_calloc(1, sizeof(*point));

    if (!point)
    {
        return RT_NULL;
    }

    point->x = rk_bn_alloc(max_size);
    if (!point->x)
    {
        goto error;
    }

    if (rk_bn_set_data(point->x, x, x_len, endian) != RT_EOK)
    {
        goto error;
    }

    point->y = rk_bn_alloc(max_size);
    if (!point->y)
    {
        goto error;
    }

    if (rk_bn_set_data(point->y, y, y_len, endian) != RT_EOK)
    {
        goto error;
    }

    return point;

error:
    rk_ecc_free_point(point);

    return RT_NULL;
}

rt_bool_t rk_ecp_point_is_zero(struct rk_ecp_point *point)
{
    rt_uint32_t i;
    rt_bool_t ret = RT_TRUE;

    if (!point || !point->x || !point->y)
    {
        return RT_FALSE;
    }

    for (i = 0; i < point->x->n_words; i++)
    {
        if (point->x->data[i] != 0)
        {
            ret = RT_FALSE;
        }
    }

    for (i = 0; i < point->y->n_words; i++)
    {
        if (point->y->data[i] != 0)
        {
            ret = RT_FALSE;
        }
    }

    return ret;
}

int rk_pka_expt_mod(struct rk_bignum *in, struct rk_bignum *e,
        struct rk_bignum *n, struct rk_bignum *out);

#define PKA_WORDS2BITS(words)           ((words) * 32)
#define PKA_BITS2WORDS(bits)            (((bits) + 31) / 32)
#define PKA_WORDS2BYTES(words)          ((words) * 4)
#define PKA_BYTES2BITS(bytes)           ((bytes) * 8)

enum
{
    PKA_EXACT_LEN_ID = 0,
    PKA_CALC_LEN_ID,
    PKA_USED_LEN_MAX,
};

#define PKA_POLL_PERIOD_US              1000
#define PKA_POLL_TIMEOUT_US             50000
#define PKA_MAX_POLL_PERIOD_US          20000
#define PKA_MAX_POLL_TIMEOUT_US         2000000
#define PKA_MAX_CALC_BITS               4096
#define PKA_MAX_CALC_WORDS              PKA_BITS2WORDS(PKA_MAX_CALC_BITS)

#define PKA_N                           0UL
#define PKA_NP                          1UL
#define PKA_T0                          30UL
#define PKA_T1                          31UL
#define PKA_TMP_REG_CNT                 2

#define PKA_N_NP_T0_T1_REG_DEFAULT \
                (PKA_N  << CRYPTO_N_VIRTUAL_ADDR_SHIFT  | \
                 PKA_NP << CRYPTO_NP_VIRTUAL_ADDR_SHIFT | \
                 PKA_T0 << CRYPTO_T0_VIRTUAL_ADDR_SHIFT | \
                 PKA_T1 << CRYPTO_T1_VIRTUAL_ADDR_SHIFT)

#define RES_DISCARD                     0x3F
#define PKA_ADDR_NOT_USED               0xFFC

enum pka_opcode
{
    PKA_OPCODE_ADD = 0x04,
    PKA_OPCODE_SUB,
    PKA_OPCODE_MOD_ADD,
    PKA_OPCODE_MOD_SUB,
    PKA_OPCODE_AND,
    PKA_OPCODE_OR,
    PKA_OPCODE_XOR,
    PKA_OPCODE_SHR0 = 0x0C,
    PKA_OPCODE_SHR1,
    PKA_OPCODE_SHL0,
    PKA_OPCODE_SHL1,
    PKA_OPCODE_LMUL,
    PKA_OPCODE_MOD_MUL,
    PKA_OPCODE_MOD_MUL_NR,
    PKA_OPCODE_MOD_EXP,
    PKA_OPCODE_DIV,
    PKA_OPCODE_MOD_INV,
    PKA_OPCODE_MOD_DIV,
    PKA_OPCODE_HMUL,
    PKA_OPCODE_TERMINATE,
};

#define PKA_CLK_ENABLE()
#define PKA_CLK_DISABLE()

#define PKA_READ(offset)                HWREG32((rt_uint8_t *)pka_base + (offset))
#define PKA_WRITE(val, offset)          HWREG32((rt_uint8_t *)pka_base + (offset)) = (val)
#define PKA_BIGNUM_WORDS(x)             (rk_bn_get_size(x) / sizeof(rt_uint32_t))

#define PKA_RAM_FOR_PKA()               PKA_WRITE(CRYPTO_RAM_CTL_SEL_MASK | CRYPTO_RAM_CTL_PKA, \
                                                  CRYPTO_RAM_CTL)

#define PKA_RAM_FOR_CPU()               do { \
        PKA_WRITE(CRYPTO_RAM_CTL_SEL_MASK | CRYPTO_RAM_CTL_CPU, CRYPTO_RAM_CTL); \
        while ((PKA_READ(CRYPTO_RAM_ST) & 0x01) != CRYPTO_CLK_RAM_RDY) \
            rt_hw_us_delay(1); \
    } while (0)

#define PKA_GET_SRAM_ADDR(addr)         ((rt_uint32_t *)((rt_uint8_t *)pka_base + CRYPTO_SRAM_BASE + (addr)))
#define PKA_MIN(a, b)                   ((a) < (b) ? (a) : (b))

#define RK_PKA_ADD(op_a, op_b, res)     pka_exec_op(PKA_OPCODE_ADD, PKA_CALC_LEN_ID, \
                                                    0, (op_a), 0, (op_b), 0, (res), 0)
#define RK_PKA_CLR(op_a)                pka_exec_op(PKA_OPCODE_AND, PKA_CALC_LEN_ID, \
                                                    0, (op_a), 1, 0x00, 0, (op_a), 0)
#define RK_PKA_COPY(op_dest, op_src)    pka_exec_op(PKA_OPCODE_OR, PKA_CALC_LEN_ID, \
                                                    0, (op_src), 1, 0x00, 0, (op_dest), 0)
#define RK_PKA_SET_0(op_a, res)         pka_exec_op(PKA_OPCODE_OR, PKA_CALC_LEN_ID, \
                                                    0, (op_a), 1, 0x01, 0, (res), 0)
#define RK_PKA_SHL0(op_a, s, res)       pka_exec_op(PKA_OPCODE_SHL0, PKA_CALC_LEN_ID, \
                                                    0, (op_a), 0, (s), 0, (res), 0)
#define RK_PKA_SHL1(op_a, s, res)       pka_exec_op(PKA_OPCODE_SHL1, PKA_CALC_LEN_ID, \
                                                    0, (op_a), 0, (s), 0, (res), 0)
#define RK_PKA_MOD_EXP(op_a, op_b, res) pka_exec_op(PKA_OPCODE_MOD_EXP, PKA_EXACT_LEN_ID, \
                                                    0, (op_a), 0, (op_b), 0, (res), 0)
#define RK_PKA_DIV(op_a, op_b, res)     pka_exec_op(PKA_OPCODE_DIV, PKA_CALC_LEN_ID, \
                                                    0, (op_a), 0, (op_b), 0, (res), 0)
#define RK_PKA_TERMINATE()              pka_exec_op(PKA_OPCODE_TERMINATE, 0, 0, 0, 0, 0, 0, 0, 0)

static rt_uint8_t *pka_base;
static struct rockchip_crypto *pka_owner;

static rt_err_t rk_pka_poll_reg(rt_uint32_t off, rt_uint32_t expect,
        rt_uint32_t period_us, rt_uint32_t timeout_us)
{
    rt_uint32_t elapsed = 0;

    while (RT_TRUE)
    {
        if ((PKA_READ(off) & 1) == expect)
        {
            return RT_EOK;
        }

        if (elapsed >= timeout_us)
        {
            break;
        }

        rt_hw_us_delay(period_us);
        elapsed += period_us;
    }

    return -RT_ETIMEOUT;
}

static void pka_word_memcpy(rt_uint32_t *dst, rt_uint32_t *src, rt_uint32_t size)
{
    rt_uint32_t i;

    for (i = 0; i < size; i++)
    {
        HWREG32((rt_uint8_t *)dst + i * 4) = src[i];
    }
}

static void pka_word_memset(rt_uint32_t *buff, rt_uint32_t val, rt_uint32_t size)
{
    rt_uint32_t i;

    for (i = 0; i < size; i++)
    {
        HWREG32((rt_uint8_t *)buff + i * 4) = val;
    }
}

static int pka_wait_pipe_rdy(void)
{
    return rk_pka_poll_reg(CRYPTO_PKA_PIPE_RDY, 1, PKA_POLL_PERIOD_US, PKA_POLL_TIMEOUT_US);
}

static int pka_wait_done(void)
{
    return rk_pka_poll_reg(CRYPTO_PKA_DONE, 1, PKA_POLL_PERIOD_US, PKA_POLL_TIMEOUT_US);
}

static int pka_max_wait_done(void)
{
    return rk_pka_poll_reg(CRYPTO_PKA_DONE, 1, PKA_MAX_POLL_PERIOD_US, PKA_MAX_POLL_TIMEOUT_US);
}

static rt_uint32_t pka_check_status(rt_uint32_t mask)
{
    rt_uint32_t status;

    pka_wait_done();
    status = PKA_READ(CRYPTO_PKA_STATUS);
    status = status & mask;

    return !!status;
}

static void pka_set_len_words(rt_uint32_t words, rt_uint32_t index)
{
    PKA_WRITE(PKA_WORDS2BITS(words), CRYPTO_PKA_L0 + index * sizeof(rt_uint32_t));
}

static rt_uint32_t pka_get_len_words(rt_uint32_t index)
{
    pka_wait_done();
    return PKA_BITS2WORDS(PKA_READ(CRYPTO_PKA_L0 + index * sizeof(rt_uint32_t)));
}

static void pka_set_map_addr(rt_uint32_t addr, rt_uint32_t index)
{
    PKA_WRITE(addr, CRYPTO_MEMORY_MAP0 + sizeof(rt_uint32_t) * index);
}

static rt_uint32_t pka_get_map_addr(rt_uint32_t index)
{
    pka_wait_done();
    return PKA_READ(CRYPTO_MEMORY_MAP0 + sizeof(rt_uint32_t) * index);
}

static rt_uint32_t pka_make_full_opcode(rt_uint32_t opcode, rt_uint32_t len_id,
        rt_uint32_t is_a_immed, rt_uint32_t op_a,
        rt_uint32_t is_b_immed, rt_uint32_t op_b,
        rt_uint32_t res_discard, rt_uint32_t res,
        rt_uint32_t tag)
{
    rt_uint32_t full_opcode;

    full_opcode = ((opcode & 31)     << CRYPTO_OPCODE_CODE_SHIFT  |
                   (len_id & 7)      << CRYPTO_OPCODE_LEN_SHIFT   |
                   (is_a_immed & 1)  << CRYPTO_OPCODE_A_IMMED_SHIFT |
                   (op_a & 31)       << CRYPTO_OPCODE_A_SHIFT     |
                   (is_b_immed & 1)  << CRYPTO_OPCODE_B_IMMED_SHIFT |
                   (op_b & 31)       << CRYPTO_OPCODE_B_SHIFT     |
                   (res_discard & 1) << CRYPTO_OPCODE_R_DIS_SHIFT |
                   (res & 31)        << CRYPTO_OPCODE_R_SHIFT     |
                   (tag & 31)        << CRYPTO_OPCODE_TAG_SHIFT);

    return full_opcode;
}

static void pka_load_data(rt_uint32_t addr, rt_uint32_t *data, rt_uint32_t size_words)
{
    pka_wait_done();

    PKA_RAM_FOR_CPU();
    pka_word_memcpy(PKA_GET_SRAM_ADDR(addr), data, size_words);
    PKA_RAM_FOR_PKA();
}

static void pka_clr_mem(rt_uint32_t addr, rt_uint32_t size_words)
{
    pka_wait_done();

    PKA_RAM_FOR_CPU();
    pka_word_memset(PKA_GET_SRAM_ADDR(addr), 0x00, size_words);
    PKA_RAM_FOR_PKA();
}

static void pka_read_data(rt_uint32_t addr, rt_uint32_t *data, rt_uint32_t size_words)
{
    pka_wait_done();

    PKA_RAM_FOR_CPU();
    pka_word_memcpy(data, PKA_GET_SRAM_ADDR(addr), size_words);
    PKA_RAM_FOR_PKA();
}

static int pka_exec_op(enum pka_opcode opcode, rt_uint8_t len_id,
        rt_uint8_t is_a_immed, rt_uint8_t op_a, rt_uint8_t is_b_immed, rt_uint8_t op_b,
        rt_uint8_t res_discard, rt_uint8_t res, rt_uint8_t tag)
{
    int ret = 0;
    rt_uint32_t full_opcode;

    if (res == RES_DISCARD)
    {
        res_discard = 1;
        res = 0;
    }

    full_opcode = pka_make_full_opcode(opcode, len_id,
            is_a_immed, op_a,
            is_b_immed, op_b,
            res_discard, res, tag);

    PKA_WRITE(full_opcode, CRYPTO_OPCODE);

    switch (opcode)
    {
    case PKA_OPCODE_DIV:
        if (pka_check_status(CRYPTO_PKA_DIV_BY_ZERO))
        {
            goto end;
        }
        break;
    case PKA_OPCODE_TERMINATE:
        ret = pka_wait_done();
        break;
    default:
        ret = pka_wait_pipe_rdy();
    }
end:
    return ret;
}

static int pk_int_len_tbl(rt_uint32_t exact_size_words, rt_uint32_t calc_size_words)
{
    rt_uint32_t i;

    for (i = 0; i < CRYPTO_LEN_REG_NUM; i++)
    {
        pka_set_len_words(0, i);
    }

    pka_set_len_words(exact_size_words, PKA_EXACT_LEN_ID);
    pka_set_len_words(calc_size_words, PKA_CALC_LEN_ID);

    return 0;
}

static int pka_int_map_tbl(rt_uint32_t *regs_cnt, rt_uint32_t max_size_words)
{
    rt_uint32_t i;
    rt_uint32_t cur_addr = 0;
    rt_uint32_t max_size_bytes, default_regs_cnt;

    max_size_bytes = PKA_WORDS2BYTES(max_size_words);
    default_regs_cnt = PKA_MIN(CRYPTO_MAP_REG_NUM, CRYPTO_SRAM_SIZE / max_size_bytes);

    for (i = 0; i < CRYPTO_MAP_REG_NUM; i++)
    {
        pka_set_map_addr(PKA_ADDR_NOT_USED, i);
    }

    for (i = 0; i < default_regs_cnt - PKA_TMP_REG_CNT; i++, cur_addr += max_size_bytes)
    {
        pka_set_map_addr(cur_addr, i);
    }

    pka_set_map_addr(cur_addr, PKA_T0);
    cur_addr += max_size_bytes;
    pka_set_map_addr(cur_addr, PKA_T1);

    *regs_cnt = default_regs_cnt;

    PKA_WRITE((rt_uint32_t)PKA_N_NP_T0_T1_REG_DEFAULT, CRYPTO_N_NP_T0_T1_ADDR);

    return 0;
}

static int pka_clear_regs_block(rt_uint8_t first_reg, rt_uint8_t regs_cnt)
{
    rt_uint32_t i;
    rt_uint32_t size_words;
    int cnt_tmps = 0;
    rt_uint32_t user_reg_num = CRYPTO_MAP_REG_NUM - PKA_TMP_REG_CNT;

    size_words = pka_get_len_words(PKA_CALC_LEN_ID);

    if (first_reg + regs_cnt > user_reg_num)
    {
        cnt_tmps = PKA_MIN(regs_cnt + first_reg - user_reg_num, PKA_TMP_REG_CNT);
        regs_cnt = user_reg_num;
    }
    else
    {
        cnt_tmps = PKA_TMP_REG_CNT;
    }

    for (i = first_reg; i < regs_cnt; i++)
    {
        RK_PKA_CLR(i);
    }

    pka_wait_done();

    if (cnt_tmps > 0)
    {
        pka_clr_mem(pka_get_map_addr(PKA_T0), size_words);
        if (cnt_tmps > 1)
        {
            pka_clr_mem(pka_get_map_addr(PKA_T1), size_words);
        }
    }

    return 0;
}

static int pka_init(rt_uint32_t exact_size_words)
{
    int ret;
    rt_uint32_t regs_cnt = 0;
    rt_uint32_t calc_size_words = exact_size_words + 1;

    PKA_CLK_ENABLE();
    PKA_RAM_FOR_PKA();

    if (exact_size_words > PKA_MAX_CALC_WORDS)
    {
        return -1;
    }

    ret = pk_int_len_tbl(exact_size_words, calc_size_words);
    if (ret)
    {
        goto exit;
    }

    ret = pka_int_map_tbl(&regs_cnt, calc_size_words);
    if (ret)
    {
        goto exit;
    }

    pka_clear_regs_block(0, regs_cnt - PKA_TMP_REG_CNT);
    pka_clr_mem(pka_get_map_addr(PKA_T0), calc_size_words);
    pka_clr_mem(pka_get_map_addr(PKA_T1), calc_size_words);

exit:
    return ret;
}

static void pka_finish(void)
{
    RK_PKA_TERMINATE();
    PKA_RAM_FOR_CPU();
    PKA_CLK_DISABLE();
}

static void pka_copy_bn_into_reg(rt_uint8_t dst_reg, struct rk_bignum *bn)
{
    rt_uint32_t cur_addr;
    rt_uint32_t size_words, bn_words;

    RK_PKA_TERMINATE();

    bn_words = PKA_BIGNUM_WORDS(bn);
    size_words = pka_get_len_words(PKA_CALC_LEN_ID);
    cur_addr = pka_get_map_addr(dst_reg);

    pka_load_data(cur_addr, bn->data, bn_words);
    cur_addr += PKA_WORDS2BYTES(bn_words);

    pka_clr_mem(cur_addr, size_words - bn_words);
}

static int pka_copy_bn_from_reg(struct rk_bignum *bn, rt_uint32_t size_words,
        rt_uint8_t src_reg, rt_bool_t is_max_poll)
{
    int ret;

    PKA_WRITE(0, CRYPTO_OPCODE);

    ret = is_max_poll ? pka_max_wait_done() : pka_wait_done();
    if (ret)
    {
        return ret;
    }

    pka_read_data(pka_get_map_addr(src_reg), bn->data, size_words);

    return 0;
}

static int pka_div_bignum(rt_uint8_t op_a, rt_uint32_t s, rt_uint8_t op_b,
        rt_uint8_t res, rt_uint8_t r_t1, rt_uint8_t r_t2)
{
    rt_uint8_t s1;
    rt_uint32_t i;
    rt_uint32_t n_bits, n_words;

    n_words = ((rt_uint32_t)s + 31) / 32;
    n_bits = (rt_uint32_t)s % 32;

    RK_PKA_COPY(r_t1, op_a);
    RK_PKA_CLR(res);

    for (i = 0; i < n_words; i++)
    {
        s1 = i > 0 ? 32 : n_bits;

        if (s1 > 0)
        {
            RK_PKA_SHL0(r_t1, s1 - 1, r_t1);
        }

        RK_PKA_DIV(r_t1, op_b, r_t2);

        if (s1 > 0)
        {
            RK_PKA_SHL0(res, s1 - 1, res);
        }

        RK_PKA_ADD(res, r_t2, res);
    }

    pka_wait_done();

    return 0;
}

static rt_uint32_t pka_calc_and_init_np(struct rk_bignum *bn,
        rt_uint8_t r_t0, rt_uint8_t r_t1, rt_uint8_t r_t2)
{
    int ret;
    rt_uint32_t i;
    rt_uint32_t s;
    rt_uint32_t mod_size_bits;
    rt_uint32_t num_bits, num_words;

    s = 132;
    mod_size_bits = PKA_BYTES2BITS(rk_bn_get_size(bn));

    CRYPTO_TRACE("size_bits = %u", mod_size_bits);

    pka_copy_bn_into_reg(PKA_N, bn);

    RK_PKA_CLR(r_t0);

    num_bits = mod_size_bits % 32;
    num_words = mod_size_bits / 32;

    CRYPTO_TRACE("num_bits = %u, num_words = %u, size_bits = %u",
            num_bits, num_words, mod_size_bits);

    RK_PKA_SET_0(r_t0, r_t0);

    if (num_bits > 0)
    {
        RK_PKA_SHL0(r_t0, num_bits - 1, r_t0);
    }

    for (i = 0; i < num_words; i++)
    {
        RK_PKA_SHL0(r_t0, 31, r_t0);
    }

    ret = pka_div_bignum(r_t0, s, PKA_N, PKA_NP, r_t1, r_t2);

    return ret;
}

void rk_crypto_pka_init(struct rockchip_crypto *rc)
{
    pka_owner = rc;
    pka_base = rc->regs + CRYPTO_PKA_BASE_OFFSET;
}

static struct rk_bignum *rk_crypto_mpi_to_bn(const struct hw_bignum_mpi *mpi)
{
    struct rk_bignum *bn;
    rt_uint32_t len;

    if (!mpi || !mpi->p)
    {
        return RT_NULL;
    }

    len = rt_hwcrypto_bignum_get_len(mpi);
    if (!len)
    {
        return RT_NULL;
    }

    bn = rk_bn_alloc(len);
    if (!bn)
    {
        return RT_NULL;
    }

    if (rk_bn_set_data(bn, mpi->p, len, RK_BG_BIG_ENDIAN) != RT_EOK)
    {
        rk_bn_free(bn);
        return RT_NULL;
    }

    return bn;
}

static rt_err_t rk_crypto_bn_to_mpi(struct hw_bignum_mpi *mpi, struct rk_bignum *bn)
{
    rt_uint32_t len = rk_bn_get_size(bn);
    rt_uint8_t *buf;
    rt_err_t err;

    buf = rt_malloc(len);
    if (!buf)
    {
        return -RT_ENOMEM;
    }

    err = rk_bn_get_data(bn, buf, len, RK_BG_BIG_ENDIAN);
    if (err == RT_EOK)
    {
        err = rt_hwcrypto_bignum_import_bin(mpi, buf, len) > 0 ? RT_EOK : -RT_ERROR;
    }

    rt_free(buf);

    return err;
}

static rt_err_t rk_crypto_bignum_exptmod(struct hwcrypto_bignum *bignum_ctx,
        struct hw_bignum_mpi *x, const struct hw_bignum_mpi *a,
        const struct hw_bignum_mpi *b, const struct hw_bignum_mpi *c)
{
    struct rk_bignum *in, *e, *n, *out;
    rt_err_t err = -RT_ERROR;

    RT_UNUSED(bignum_ctx);

    if (!pka_owner)
    {
        return -RT_EINVAL;
    }

    in = rk_crypto_mpi_to_bn(a);
    e = rk_crypto_mpi_to_bn(b);
    n = rk_crypto_mpi_to_bn(c);
    out = rk_bn_alloc(rt_hwcrypto_bignum_get_len(c));
    if (!in || !e || !n || !out)
    {
        goto _out;
    }

    rt_mutex_take(&pka_owner->mutex, RT_WAITING_FOREVER);
    if (rk_pka_expt_mod(in, e, n, out) == 0)
    {
        err = rk_crypto_bn_to_mpi(x, out);
    }
    rt_mutex_release(&pka_owner->mutex);

_out:
    rk_bn_free(in);
    rk_bn_free(e);
    rk_bn_free(n);
    rk_bn_free(out);

    return err;
}

static const struct hwcrypto_bignum_ops rk_crypto_bignum_ops =
{
    .exptmod = rk_crypto_bignum_exptmod,
};

const struct hwcrypto_bignum_ops *rk_crypto_bignum_ops_get(void)
{
    return &rk_crypto_bignum_ops;
}

int rk_pka_expt_mod(struct rk_bignum *in,
        struct rk_bignum *e,
        struct rk_bignum *n,
        struct rk_bignum *out)
{
    int ret = -1;
    rt_uint32_t max_word_size;
    rt_bool_t is_max_poll;
    rt_uint8_t r_in = 2, r_e = 3, r_out = 4;
    rt_uint8_t r_t0 = 2, r_t1 = 3, r_t2 = 4;

    if (!in || !e || !n || !out || PKA_BIGNUM_WORDS(n) == 0)
    {
        return -1;
    }

    max_word_size = PKA_BIGNUM_WORDS(n);

    ret = pka_init(max_word_size);
    if (ret)
    {
        CRYPTO_TRACE("pka_init error\n");
        goto exit;
    }

    ret = pka_calc_and_init_np(n, r_t0, r_t1, r_t2);
    if (ret)
    {
        CRYPTO_TRACE("pka_calc_and_init_np error\n");
        goto exit;
    }

    pka_clear_regs_block(r_in, 3);

    pka_copy_bn_into_reg(r_in, in);
    pka_copy_bn_into_reg(r_e, e);
    pka_copy_bn_into_reg(PKA_N, n);

    ret = RK_PKA_MOD_EXP(r_in, r_e, r_out);
    if (ret)
    {
        CRYPTO_TRACE("RK_PKA_MOD_EXP error\n");
        goto exit;
    }

    is_max_poll = rk_bn_highest_bit(e) * 2 > rk_bn_highest_bit(n) ? RT_TRUE : RT_FALSE;

    ret = pka_copy_bn_from_reg(out, max_word_size, r_out, is_max_poll);

exit:
    pka_clear_regs_block(0, 5);
    pka_clear_regs_block(30, 2);
    pka_finish();

    return ret;
}

#define RK_ECP_WORDS2BYTES(words)       ((words) * sizeof(rt_uint32_t))
#define RK_ECP_POLL_PERIOD_US           10000
#define RK_ECP_POLL_TIMEOUT_US          500000

#define RK_ECP_WRITE_REG(offset, val)   HWREG32(ecc_base + (offset)) = (val)
#define RK_ECP_READ_REG(offset)         HWREG32(ecc_base + (offset))

#define RK_ECP_RAM_FOR_ECC()            RK_ECP_WRITE_REG(RK_ECC_RAM_CTL, \
                                             RK_ECC_RAM_CTL_SEL_MASK | RK_ECC_RAM_CTL_ECC)
#define RK_ECP_RAM_FOR_CPU()            RK_ECP_WRITE_REG(RK_ECC_RAM_CTL, \
                                             RK_ECC_RAM_CTL_SEL_MASK | RK_ECC_RAM_CTL_CPU)

#define RK_ECP_LOAD_DATA(dst, big_src)  do { \
        ecc_word_memset((dst), 0, RK_ECP_MAX_WORDS); \
        ecc_word_memcpy((dst), (big_src->data), (big_src->n_words)); \
    } while (0)

#define RK_ECP_LOAD_DATA_EXT(dst, src, n_bytes) do { \
        ecc_word_memset((void *)(dst), 0, RK_ECP_MAX_WORDS); \
        ecc_word_memcpy((void *)(dst), (void *)(src), (n_bytes) / 4); \
    } while (0)

#define RK_ECP_IS_BIGNUM_INVALID(b)     (!b || !b->data || b->n_words < RK_ECP_MAX_WORDS)
#define RK_ECP_IS_POINT_INVALID(p)      (RK_ECP_IS_BIGNUM_INVALID((p)->x) && \
                                         RK_ECP_IS_BIGNUM_INVALID((p)->y))

#define RK_LOAD_GROUP_A(G)              do { \
        grp->curve_name = #G; \
        grp->wide   = G ## _wide; \
        grp->p      = G ## _p; \
        grp->p_len  = sizeof(G ## _p); \
        grp->a      = G ## _a; \
        grp->a_len  = sizeof(G ## _a); \
        grp->n      = G ## _n; \
        grp->n_len  = sizeof(G ## _n); \
        grp->gx     = G ## _gx; \
        grp->gx_len = sizeof(G ## _gx); \
        grp->gy     = G ## _gy; \
        grp->gy_len = sizeof(G ## _gy); \
    } while (0)

static rt_uint8_t *ecc_base;
static rt_uint8_t *ecc_sram;

static const rt_uint32_t secp192r1_wide = RK_ECC_CURVE_WIDE_192;
static const rt_uint8_t secp192r1_p[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};
static const rt_uint8_t secp192r1_a[] =
{
    0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};
static const rt_uint8_t secp192r1_gx[] =
{
    0x12, 0x10, 0xFF, 0x82, 0xFD, 0x0A, 0xFF, 0xF4,
    0x00, 0x88, 0xA1, 0x43, 0xEB, 0x20, 0xBF, 0x7C,
    0xF6, 0x90, 0x30, 0xB0, 0x0E, 0xA8, 0x8D, 0x18,
};
static const rt_uint8_t secp192r1_gy[] =
{
    0x11, 0x48, 0x79, 0x1E, 0xA1, 0x77, 0xF9, 0x73,
    0xD5, 0xCD, 0x24, 0x6B, 0xED, 0x11, 0x10, 0x63,
    0x78, 0xDA, 0xC8, 0xFF, 0x95, 0x2B, 0x19, 0x07,
};
static const rt_uint8_t secp192r1_n[] =
{
    0x31, 0x28, 0xD2, 0xB4, 0xB1, 0xC9, 0x6B, 0x14,
    0x36, 0xF8, 0xDE, 0x99, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

static const rt_uint32_t secp224r1_wide = RK_ECC_CURVE_WIDE_224;
static const rt_uint8_t secp224r1_p[] =
{
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
};
static const rt_uint8_t secp224r1_a[] =
{
    0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
};
static const rt_uint8_t secp224r1_gx[] =
{
    0x21, 0x1D, 0x5C, 0x11, 0xD6, 0x80, 0x32, 0x34,
    0x22, 0x11, 0xC2, 0x56, 0xD3, 0xC1, 0x03, 0x4A,
    0xB9, 0x90, 0x13, 0x32, 0x7F, 0xBF, 0xB4, 0x6B,
    0xBD, 0x0C, 0x0E, 0xB7,
};
static const rt_uint8_t secp224r1_gy[] =
{
    0x34, 0x7E, 0x00, 0x85, 0x99, 0x81, 0xD5, 0x44,
    0x64, 0x47, 0x07, 0x5A, 0xA0, 0x75, 0x43, 0xCD,
    0xE6, 0xDF, 0x22, 0x4C, 0xFB, 0x23, 0xF7, 0xB5,
    0x88, 0x63, 0x37, 0xBD,
};
static const rt_uint8_t secp224r1_n[] =
{
    0x3D, 0x2A, 0x5C, 0x5C, 0x45, 0x29, 0xDD, 0x13,
    0x3E, 0xF0, 0xB8, 0xE0, 0xA2, 0x16, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
};

static const rt_uint32_t secp256r1_wide = RK_ECC_CURVE_WIDE_256;
static const rt_uint8_t secp256r1_p[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
};
static const rt_uint8_t secp256r1_a[] =
{
    0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
};
static const rt_uint8_t secp256r1_gx[] =
{
    0x96, 0xC2, 0x98, 0xD8, 0x45, 0x39, 0xA1, 0xF4,
    0xA0, 0x33, 0xEB, 0x2D, 0x81, 0x7D, 0x03, 0x77,
    0xF2, 0x40, 0xA4, 0x63, 0xE5, 0xE6, 0xBC, 0xF8,
    0x47, 0x42, 0x2C, 0xE1, 0xF2, 0xD1, 0x17, 0x6B,
};
static const rt_uint8_t secp256r1_gy[] =
{
    0xF5, 0x51, 0xBF, 0x37, 0x68, 0x40, 0xB6, 0xCB,
    0xCE, 0x5E, 0x31, 0x6B, 0x57, 0x33, 0xCE, 0x2B,
    0x16, 0x9E, 0x0F, 0x7C, 0x4A, 0xEB, 0xE7, 0x8E,
    0x9B, 0x7F, 0x1A, 0xFE, 0xE2, 0x42, 0xE3, 0x4F,
};
static const rt_uint8_t secp256r1_n[] =
{
    0x51, 0x25, 0x63, 0xFC, 0xC2, 0xCA, 0xB9, 0xF3,
    0x84, 0x9E, 0x17, 0xA7, 0xAD, 0xFA, 0xE6, 0xBC,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
};

static const rt_uint32_t sm2p256v1_wide = RK_ECC_CURVE_WIDE_256;
static const rt_uint8_t sm2p256v1_p[] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF,
};
static const rt_uint8_t sm2p256v1_a[] =
{
    0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF,
};
static const rt_uint8_t sm2p256v1_gx[] =
{
    0xC7, 0x74, 0x4C, 0x33, 0x89, 0x45, 0x5A, 0x71,
    0xE1, 0x0B, 0x66, 0xF2, 0xBF, 0x0B, 0xE3, 0x8F,
    0x94, 0xC9, 0x39, 0x6A, 0x46, 0x04, 0x99, 0x5F,
    0x19, 0x81, 0x19, 0x1F, 0x2C, 0xAE, 0xC4, 0x32,
};
static const rt_uint8_t sm2p256v1_gy[] =
{
    0xA0, 0xF0, 0x39, 0x21, 0xE5, 0x32, 0xDF, 0x02,
    0x40, 0x47, 0x2A, 0xC6, 0x7C, 0x87, 0xA9, 0xD0,
    0x53, 0x21, 0x69, 0x6B, 0xE3, 0xCE, 0xBD, 0x59,
    0x9C, 0x77, 0xF6, 0xF4, 0xA2, 0x36, 0x37, 0xBC,
};
static const rt_uint8_t sm2p256v1_n[] =
{
    0x23, 0x41, 0xD5, 0x39, 0x09, 0xF4, 0xBB, 0x53,
    0x2B, 0x05, 0xC6, 0x21, 0x6B, 0xDF, 0x03, 0x72,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF,
};

static void dump_ecc_sram(void)
{
}

static void ecc_word_memcpy(rt_uint32_t *dst, rt_uint32_t *src, rt_uint32_t size)
{
    rt_uint32_t i;

    for (i = 0; i < size; i++)
    {
        HWREG32((rt_uint8_t *)dst + i * 4) = src[i];
    }
}

static void ecc_word_memset(rt_uint32_t *buff, rt_uint32_t val, rt_uint32_t size)
{
    rt_uint32_t i;

    for (i = 0; i < size; i++)
    {
        HWREG32((rt_uint8_t *)buff + i * 4) = val;
    }
}

static void rk_reverse_buf(rt_uint8_t *buff, rt_uint32_t size)
{
    rt_uint8_t *buf_h_swap, *buf_l_swap;
    rt_uint32_t i;
    rt_uint32_t temp;

    buf_h_swap = buff + size - 1;
    buf_l_swap = buff;

    for (i = 0; i < (size / 2); i++)
    {
        temp = *buf_h_swap;
        *(buf_h_swap--) = *buf_l_swap;
        *(buf_l_swap++) = temp;
    }
}

static int rk_word_cmp_zero(rt_uint32_t *buf1, rt_uint32_t n_words)
{
    int ret = 0;
    rt_uint32_t i;

    for (i = 0; i < n_words; i++)
    {
        if (buf1[i] != 0)
        {
            ret = -RT_EINVAL;
        }
    }

    return ret;
}

static int rk_load_hash_bn(struct rk_ecp_group *grp, struct rk_bignum *bn,
        rt_uint8_t *hash, rt_uint32_t hash_len)
{
    if (grp == RT_NULL || RK_ECP_IS_BIGNUM_INVALID(bn))
    {
        return -RT_EINVAL;
    }

    hash_len = hash_len > grp->p_len ? grp->p_len : hash_len;

    rt_memset(bn->data, 0x00, RK_ECP_WORDS2BYTES(bn->n_words));
    rt_memcpy(bn->data, hash, hash_len);

    rk_reverse_buf((void *)bn->data, hash_len);

    return 0;
}

static int rk_ecp_group_load(struct rk_ecp_group *grp, enum rk_ecp_group_id id)
{
    rt_memset(grp, 0x00, sizeof(*grp));

    grp->id = id;
    grp->endian = RK_BG_LITTILE_ENDIAN;

    switch (id)
    {
    case RK_ECP_DP_SECP192R1:
        RK_LOAD_GROUP_A(secp192r1);
        return 0;
    case RK_ECP_DP_SECP224R1:
        RK_LOAD_GROUP_A(secp224r1);
        return 0;
    case RK_ECP_DP_SECP256R1:
        RK_LOAD_GROUP_A(secp256r1);
        return 0;
    case RK_ECP_DP_SM2P256V1:
        RK_LOAD_GROUP_A(sm2p256v1);
        return 0;
    default:
        return -RT_EINVAL;
    }
}

static int rockchip_ecc_request_set(rt_uint32_t ecc_ctl, rt_uint32_t wide)
{
    RK_ECP_WRITE_REG(RK_ECC_CURVE_WIDE, wide);
    RK_ECP_WRITE_REG(RK_ECC_INT_EN, 0);
    RK_ECP_WRITE_REG(RK_ECC_INT_ST, RK_ECP_READ_REG(RK_ECC_INT_ST));
    RK_ECP_WRITE_REG(RK_ECC_CTL, ecc_ctl);

    return 0;
}

static rt_err_t rockchip_ecc_request_wait_done(void)
{
    rt_uint32_t reg_val = 0;
    rt_uint32_t elapsed = 0;
    rt_err_t err = RT_EOK;

    while (RT_TRUE)
    {
        reg_val = RK_ECP_READ_REG(RK_ECC_INT_ST);
        if (reg_val)
        {
            break;
        }

        if (elapsed >= RK_ECP_POLL_TIMEOUT_US)
        {
            err = -RT_ETIMEOUT;
            goto out;
        }

        rt_hw_us_delay(RK_ECP_POLL_PERIOD_US);
        elapsed += RK_ECP_POLL_PERIOD_US;
    }

    if (RK_ECP_READ_REG(RK_ECC_ABN_ST))
    {
        err = -RT_ERROR;
    }

out:
    RK_ECP_WRITE_REG(RK_ECC_CTL, 0);
    RK_ECP_RAM_FOR_CPU();

    return err;
}

static int rockchip_ecc_request_trigger(void)
{
    rt_uint32_t ecc_ctl = RK_ECP_READ_REG(RK_ECC_CTL);

    RK_ECP_RAM_FOR_ECC();
    RK_ECP_WRITE_REG(RK_ECC_CTL, ecc_ctl | RK_ECC_CTL_REQ_ECC);

    return rockchip_ecc_request_wait_done();
}

int rockchip_ecc_verify(int group_id, rt_uint8_t *hash, rt_uint32_t hash_len,
        struct rk_ecp_point *point_P, struct rk_ecp_point *point_sign)
{
    int ret;
    rt_uint32_t curve_sel = 0;
    struct rk_bignum *bn_hash = RT_NULL;
    struct rk_ecp_group grp;
    struct rk_ecc_verify *ecc_st = (struct rk_ecc_verify *)ecc_sram;

    CRYPTO_TRACE("ecc_st = %p, ecc_base = %p\n", ecc_st, ecc_base);

    if (!hash ||
        RK_ECP_IS_POINT_INVALID(point_P) ||
        RK_ECP_IS_POINT_INVALID(point_sign))
    {
        ret = -RT_EINVAL;
        goto exit;
    }

    ret = rk_ecp_group_load(&grp, group_id);
    if (ret)
    {
        goto exit;
    }

    bn_hash = rk_bn_alloc(RK_ECP_MAX_BYTES);
    if (!bn_hash)
    {
        ret = -RT_ENOMEM;
        goto exit;
    }

    curve_sel = group_id == RK_ECP_DP_SM2P256V1 ?
            RK_ECC_CTL_FUNC_SM2_CURVER : RK_ECC_CTL_FUNC_ECC_CURVER;

    rk_load_hash_bn(&grp, bn_hash, hash, hash_len);

    RK_ECP_LOAD_DATA(ecc_st->e, bn_hash);
    RK_ECP_LOAD_DATA(ecc_st->r_, point_sign->x);
    RK_ECP_LOAD_DATA(ecc_st->s_, point_sign->y);
    RK_ECP_LOAD_DATA(ecc_st->p_x, point_P->x);
    RK_ECP_LOAD_DATA(ecc_st->p_y, point_P->y);
    RK_ECP_LOAD_DATA_EXT(ecc_st->A, grp.a, grp.a_len);
    RK_ECP_LOAD_DATA_EXT(ecc_st->P, grp.p, grp.p_len);
    RK_ECP_LOAD_DATA_EXT(ecc_st->N, grp.n, grp.n_len);
    RK_ECP_LOAD_DATA_EXT(ecc_st->G_x, grp.gx, grp.gx_len);
    RK_ECP_LOAD_DATA_EXT(ecc_st->G_y, grp.gy, grp.gy_len);

    rockchip_ecc_request_set(curve_sel | RK_ECC_CTL_FUNC_SEL_VERIFY, grp.wide);
    ret = rockchip_ecc_request_trigger();

exit:
    if (ret ||
        rk_word_cmp_zero(ecc_st->v, RK_ECP_MAX_WORDS) ||
        rk_word_cmp_zero(ecc_st->r_, RK_ECP_MAX_WORDS) == 0)
    {
        ret = -RT_EINVAL;
        dump_ecc_sram();
    }

    rk_bn_free(bn_hash);

    return ret;
}

void rk_crypto_ecc_init(struct rockchip_crypto *rc)
{
    ecc_base = rc->regs + RK_ECC_BASE_OFFSET;
    ecc_sram = ecc_base + SM2_RAM_BASE_OFFSET;

    RK_ECP_WRITE_REG(RK_ECC_DATA_ENDIAN, RK_ECC_DATA_ENDIAN_LITTLE);
}

rt_err_t rk_crypto_ecc_verify(int group_id, rt_uint8_t *hash, rt_uint32_t hash_len,
        struct rk_ecp_point *point_p, struct rk_ecp_point *point_sign)
{
    int ret = rockchip_ecc_verify(group_id, hash, hash_len, point_p, point_sign);

    return ret == 0 ? RT_EOK : ret;
}

rt_uint32_t rk_crypto_ecc_get_max_size(void)
{
    return RK_ECP_MAX_BYTES;
}

rt_uint32_t rk_crypto_ecc_get_curve_nbits(rt_uint32_t group_id)
{
    switch (group_id)
    {
    case RK_ECP_DP_SECP192R1:
        return 192;
    case RK_ECP_DP_SECP224R1:
        return 224;
    case RK_ECP_DP_SECP256R1:
    case RK_ECP_DP_SM2P256V1:
        return 256;
    default:
        return 0;
    }
}

#endif /* RT_HWCRYPTO_USING_BIGNUM */
