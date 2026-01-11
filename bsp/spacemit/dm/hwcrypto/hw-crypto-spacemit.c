/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "spacemit.h"

#define SPACEMIT_AES_BUFFER_LEN         (1024 * 256)

#define WORK_BUF_SIZE                   2048
#define CTR_COUNTER_LITTLE_ENDIAN       0x0000
#define CTR_COUNTER_BIG_ENDIAN          0x1000
#define BYTES_TO_BITS                   8
#define SPACEMIT_SECENG_SIZE            0x3000

#define ENGINE_DMA_ADDR_HIGH_OFFSET     0x14c
#define SW_RESETN                       RT_BIT(0)
#define MASTER_CLK_EN                   RT_BIT(1)
#define SLAVE_CLK_EN                    RT_BIT(2)
#define WADDR_BIT32                     RT_BIT(4)
#define RADDR_BIT32                     RT_BIT(5)

#define CE_BIU_REG_OFFSET               0x00000000L
#define CE_ADEC_REG_OFFSET              0x00000400L
#define CE_DMA_REG_OFFSET               0x00000800L
#define CE_ABUS_REG_OFFSET              0x00000c00L
#define CE_CRYPTO_REG_OFFSET            0x00001000L
#define CE_HASH_REG_OFFSET              0x00001800L

#define CE_ADEC_CTRL                    0x0000
#define CE_ADEC_CTRL2                   0x0004
#define CE_AXI_SL_CTRL                  0x0008
#define CE_ADEC_INT                     0x000c
#define CE_ADEC_INT_MSK                 0x0010
#define CE_ADEC_ACC_ERR_ADR             0x0014
#define CE_ADEC_MP_FIFO_ERR_ADR         0x0018

#define CE_ABUS_BUS_CTRL                0x0000

#define SP_HST_INTERRUPT_MASK           0x0cc
#define SP_INTERRUPT_RST                0x218
#define SP_INTERRUPT_MASK               0x21c
#define SP_CONTROL                      0x220

#define CE_HASH_CONFIG_REG              0x0000
#define CE_HASH_CONTROL_REG             0x0004
#define CE_HASH_COMMAND_REG             0x0008
#define CE_HASH_STATUS_REG              0x000c
#define CE_HASH_INCOME_SEG_SZ_REG       0x0010
#define CE_HASH_TOTAL_MSG_SZ_L_REG      0x0018
#define CE_HASH_TOTAL_MSG_SZ_H_REG      0x001c
#define CE_HASH_DIGEST_BASE             0x0020
#define CE_HASH_DIGEST_REG(a)           (CE_HASH_DIGEST_BASE + (a << 2))
#define CE_HASH_DIGEST_H_BASE           0x0040
#define CE_HASH_DIGEST_H_REG(a)         (CE_HASH_DIGEST_H_BASE + (a << 2))
#define CE_HASH_CONTEXTO_BASE           0x0064
#define CE_HASH_CONTEXTO_REG(a)         (CE_HASH_CONTEXTO_BASE + (a << 2))
#define CE_HASH_CONTEXTO_H_BASE         0x0080
#define CE_HASH_CONTEXTO_H_REG(a)       (CE_HASH_CONTEXTO_H_BASE + (a << 2))
#define CE_HASH_KEY_BASE                0x00a4
#define CE_HASH_KEY_REG(a)              (CE_HASH_KEY_BASE + (a << 2))

#define CE_DMA_IN_CTRL                  0x0000
#define CE_DMA_IN_STATUS                0x0004
#define CE_DMA_IN_SRC_ADR               0x0008
#define CE_DMA_IN_XFER_CNTR             0x000c
#define CE_DMA_IN_NX_LL_ADR             0x0010
#define CE_DMA_IN_INT                   0x0014
#define CE_DMA_IN_INT_MASK              0x0018
#define CE_DMA_OUT_CTRL                 0x001c
#define CE_DMA_OUT_STATUS               0x0020
#define CE_DMA_OUT_DEST_ADR             0x0024
#define CE_DMA_OUT_XFER_CNTR            0x0028
#define CE_DMA_OUT_NX_LL_ADR            0x002c
#define CE_DMA_OUT_INT                  0x0030
#define CE_DMA_OUT_INT_MASK             0x0034
#define CE_DMA_AXI_CTRL                 0x0038
#define CE_DMA_IF_RCOUNT                0x003c
#define CE_DMA_IF_RD_PTR_ERR            0x0040
#define CE_DMA_OF_SPACE                 0x0044
#define CE_DMA_OF_RD_PTR_ERR            0x0048
#define CE_DMA_IF_RAM_BASE              0x0100
#define CE_DMA_IF_RAM_REG(a)            (CE_DMA_IF_RAM_BASE + a*0x4)
#define CE_DMA_OF_RAM_BASE              0x0300
#define CE_DMA_OF_RAM_REG(a)            (CE_DMA_OF_RAM_BASE + a*0x4)

#define CE_BIU_HST_INTERRUPT_MASK       0x00cc
#define CE_BIU_SP_INTERRUPT_MASK        0x021c
#define CE_BIU_SP_CONTROL               0x0220

#define CE_CRYPTO_AES_CONFIG_REG        0x0000
#define CE_CRYPTO_AES_CONTROL_REG       0x0004
#define CE_CRYPTO_AES_COMMAND_REG       0x0008
#define CE_CRYPTO_AES_STATUS_REG        0x000c
#define CE_CRYPTO_AES_INTRPT_SRC_REG    0x0010
#define CE_CRYPTO_AES_INTRPT_SRC_EN_REG 0x0014
#define CE_CRYPTO_AES_STREAM_SIZE_REG   0x0018
#define CE_CRYPTO_ENGINE_SEL_REG        0x00a8

#define CE_CRYPTO_K2_BASE               0x0058
#define CE_CRYPTO_K2_W_REG(a)           (CE_CRYPTO_K2_BASE + a * 0x4)
#define CE_CRYPTO_K1_BASE               0x0078
#define CE_CRYPTO_K1_W_REG(a)           (CE_CRYPTO_K1_BASE + a*0x4)
#define CE_CRYPTO_IV_BASE               0x0098
#define CE_CRYPTO_IV_REG(a)             (CE_CRYPTO_IV_BASE + a*0x4)

#define AES_INTERRUPT_FLAG              RT_BIT(0)
#define AES_ERR1_INTERRUPT_FLAG         RT_BIT(1)
#define AES_ERR2_INTERRUPT_FLAG         RT_BIT(2)
#define AES_INTERRUPT_MASK              (AES_INTERRUPT_FLAG | AES_ERR1_INTERRUPT_FLAG | \
                                        AES_ERR2_INTERRUPT_FLAG)

#define BIT_DMA_INOUT_DONE              RT_BIT(0)
#define BIT_DMA_INOUT_BUS_ERR           RT_BIT(1)
#define BIT_DMA_INOUT_LL_ERR            RT_BIT(2)
#define BIT_DMA_INOUT_PAR_ERR           RT_BIT(3)
#define BIT_DMA_INOUT_PAUSE_CMPL_ERR    RT_BIT(4)
#define BIT_DMA_INOUT_DATA_PAR_ERR      RT_BIT(5)
#define DMA_INTERRUPT_MASK              (BIT_DMA_INOUT_DONE | BIT_DMA_INOUT_BUS_ERR | \
                                        BIT_DMA_INOUT_LL_ERR | BIT_DMA_INOUT_PAR_ERR | \
                                        BIT_DMA_INOUT_PAUSE_CMPL_ERR | BIT_DMA_INOUT_DATA_PAR_ERR)

#define BIU_MASK                        RT_BIT(0)
#define ADEC_MASK                       (RT_BIT(1) | RT_BIT(5))

#define AES_BLOCK_SIZE                  16

#define ENGINE_MAX                      2

enum adec_acc_eng
{
    /* Reset bit */
    E_ACC_ENG_DMA = 1,
    E_ACC_ENG_HASH = 5,
    E_ACC_ENG_CRYPTO = 3,
    E_ACC_ENG_ALL,
};

enum abus_grp_a
{
    E_ABUS_GRP_A_HASH = 0x0,
};

enum abus_grp_b
{
    E_ABUS_GRP_B_AES = 0x0,
    E_ABUS_GRP_B_BYPASS = 0x2,
};

enum abus_cross_bar
{
    E_ABUS_STRAIGHT = 0,
    E_ABUS_CROSS,
};

enum crypto_eng_sel
{
    E_ENG_AES = 0,
};

enum crypto_aes_status
{
    AES_INVALID,
    AES_DONE,
    AES_ERROR
};

enum crypto_dma_status
{
    DMA_INVALID,
    DMA_INOUT_DONE,
    DMA_INOUT_ERROR
};

struct spacemit_crypto;

struct spacemit_crypto_engine
{
    struct rt_hwcrypto_device parent;

    struct spacemit_crypto *crypto;

    int irq;
    void *base;

    void *in_buffer, *out_buffer;
    rt_ubase_t in_buffer_dma, out_buffer_dma;

    enum crypto_aes_status aes_status;
    enum crypto_dma_status dma_in_status;
    enum crypto_dma_status dma_out_status;

    struct rt_completion aes_done;
    struct rt_completion dma_output_done;
    struct rt_completion dma_input_done;

    struct rt_mutex lock;

    rt_uint8_t internal_working_buffer[WORK_BUF_SIZE * 2] rt_align(32);
};

struct spacemit_crypto
{
    struct rt_clk *clk;
    struct rt_reset_control *rstc;
    struct rt_syscon *ciu_regmap;

    rt_uint32_t engine_nr;
    struct spacemit_crypto_engine engine[ENGINE_MAX];
};

#define raw_to_spacemit_crypto_engine(raw) rt_container_of((raw)->parent.device, struct spacemit_crypto_engine, parent)

static void dma_write32(struct spacemit_crypto_engine *ce, int offset, rt_uint32_t value)
{
    tcm_override_writel(ce->base + CE_DMA_REG_OFFSET + offset, value);
}

static rt_uint32_t dma_read32(struct spacemit_crypto_engine *ce, int offset)
{
    return tcm_override_readl(ce->base + CE_DMA_REG_OFFSET + offset);
}

static void biu_write32(struct spacemit_crypto_engine *ce, int offset, rt_uint32_t value)
{
    tcm_override_writel(ce->base + CE_BIU_REG_OFFSET + offset, value);
}

static rt_uint32_t biu_read32(struct spacemit_crypto_engine *ce, int offset)
{
    return tcm_override_readl(ce->base + CE_BIU_REG_OFFSET + offset);
}

static void adec_write32(struct spacemit_crypto_engine *ce, int offset, rt_uint32_t value)
{
    tcm_override_writel(ce->base + CE_ADEC_REG_OFFSET + offset, value);
}

static rt_uint32_t adec_read32(struct spacemit_crypto_engine *ce, int offset)
{
    return tcm_override_readl(ce->base + CE_ADEC_REG_OFFSET + offset);
}

static void abus_write32(struct spacemit_crypto_engine *ce, int offset, rt_uint32_t value)
{
    tcm_override_writel(ce->base + CE_ABUS_REG_OFFSET + offset, value);
}

static rt_uint32_t abus_read32(struct spacemit_crypto_engine *ce, int offset)
{
    return tcm_override_readl(ce->base + CE_ABUS_REG_OFFSET + offset);
}

static void crypto_write32(struct spacemit_crypto_engine *ce, int offset, rt_uint32_t value)
{
    tcm_override_writel(ce->base + CE_CRYPTO_REG_OFFSET + offset, value);
}

static rt_uint32_t crypto_read32(struct spacemit_crypto_engine *ce, int offset)
{
    return tcm_override_readl(ce->base + CE_CRYPTO_REG_OFFSET + offset);
}

static void dma_output_config(struct spacemit_crypto_engine *ce, int wid_ext, int wid)
{
    rt_uint32_t val;

    val = dma_read32(ce, CE_DMA_OUT_CTRL);
    val &= 0x0f0f0000;
    val |= (0x7 << 28) |                /* Dis error check */
            ((wid_ext & 0xf) << 20) |   /* Rid ext */
            (0x1 << 18) |               /* Dis out-of-order */
            (0x1 << 17) |               /* Data 64 Byte aligned */
            (0x1 << 15) |               /* FIFO bus size 64bit */
            (0x1 << 13) |               /* Burst type: Inc */
            (0x8 << 8) |                /* Burst len */
            ((wid & 0xf) << 4);

    dma_write32(ce, CE_DMA_OUT_CTRL, val);
}

static void dma_output_address(struct spacemit_crypto_engine *ce,
        rt_uint32_t dst_addr, rt_uint32_t dst_size, rt_bool_t chained)
{
    if (chained)
    {
        dma_write32(ce, CE_DMA_OUT_NX_LL_ADR, dst_addr);
        dma_write32(ce, CE_DMA_OUT_DEST_ADR, 0x0);
        dma_write32(ce, CE_DMA_OUT_XFER_CNTR, 0x0);
    }
    else
    {
        dma_write32(ce, CE_DMA_OUT_NX_LL_ADR, 0x0);
        dma_write32(ce, CE_DMA_OUT_DEST_ADR, dst_addr);
        dma_write32(ce, CE_DMA_OUT_XFER_CNTR, dst_size);
    }
}

static void dma_output_start(struct spacemit_crypto_engine *ce)
{
    rt_uint32_t val;

    val = dma_read32(ce, CE_DMA_OUT_INT);
    dma_write32(ce, CE_DMA_OUT_INT, val);

    val = dma_read32(ce, CE_DMA_OUT_CTRL);
    val |= 0x1;
    dma_write32(ce, CE_DMA_OUT_CTRL, val);
}

static void dma_output_stop(struct spacemit_crypto_engine *ce)
{
    rt_uint32_t val;

    val = dma_read32(ce, CE_DMA_OUT_CTRL);
    val &= ~0x1;
    dma_write32(ce, CE_DMA_OUT_CTRL, val);
}

static void dma_input_config(struct spacemit_crypto_engine *ce, int rid_ext, int rid)
{
    rt_uint32_t val;

    val = dma_read32(ce, CE_DMA_IN_CTRL);
    val &= 0x0f0f0000;
    val |= (0x7 << 28) |                /* Dis error check */
            ((rid_ext & 0xf) << 20) |   /* Rid ext */
            (0x1 << 18) |               /* Dis out-of-order */
            (0x1 << 17) |               /* Data 64 Byte aligned */
            (0x1 << 15) |               /* FIFO bus size 64bit */
            (0x1 << 13) |               /* Burst type: Inc */
            (0x8 << 8) |                /* Burst len */
            ((rid & 0xf) << 4);

    dma_write32(ce, CE_DMA_IN_CTRL, val);
}

static void dma_input_address(struct spacemit_crypto_engine *ce,
        rt_uint32_t src_addr, rt_uint32_t src_size, rt_bool_t chained)
{
    if (chained)
    {
        dma_write32(ce, CE_DMA_IN_NX_LL_ADR, src_addr);
        dma_write32(ce, CE_DMA_IN_SRC_ADR, 0x0);
        dma_write32(ce, CE_DMA_IN_XFER_CNTR, 0x0);
    }
    else
    {
        dma_write32(ce, CE_DMA_IN_NX_LL_ADR, 0x0);
        dma_write32(ce, CE_DMA_IN_SRC_ADR, src_addr);
        dma_write32(ce, CE_DMA_IN_XFER_CNTR, src_size);
    }
}

static void dma_input_start(struct spacemit_crypto_engine *ce)
{
    rt_uint32_t val;

    val = dma_read32(ce, CE_DMA_IN_INT);
    dma_write32(ce, CE_DMA_IN_INT, val);

    val = dma_read32(ce, CE_DMA_IN_CTRL);
    val |= 0x1;
    dma_write32(ce, CE_DMA_IN_CTRL, val);
}

static void dma_input_stop(struct spacemit_crypto_engine *ce)
{
    rt_uint32_t val;

    val = dma_read32(ce, CE_DMA_IN_CTRL);
    val &= ~0x1;
    dma_write32(ce, CE_DMA_IN_CTRL, val);
}

static rt_err_t dma_wait_int_input_finish(struct spacemit_crypto_engine *ce)
{
    rt_completion_wait(&ce->dma_input_done, RT_WAITING_FOREVER);

    if (ce->dma_in_status != DMA_INOUT_DONE)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t dma_wait_int_output_finish(struct spacemit_crypto_engine *ce)
{
    rt_completion_wait(&ce->dma_output_done, RT_WAITING_FOREVER);

    if (ce->dma_out_status != DMA_INOUT_DONE)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static void adec_biu_clear_int_flag(struct spacemit_crypto_engine *ce)
{
    volatile rt_uint32_t val;

    val = adec_read32(ce, CE_ADEC_INT);
    adec_write32(ce, CE_ADEC_INT, val);

    val = biu_read32(ce, SP_INTERRUPT_RST);
    biu_write32(ce, SP_INTERRUPT_RST, val);
}

static rt_err_t adec_engine_hw_reset(struct spacemit_crypto_engine *ce, enum adec_acc_eng engine)
{
    rt_uint32_t val, tmp;

    if (engine == E_ACC_ENG_ALL)
    {
        tmp = 0xffff;
    }
    else
    {
        tmp = 1 << engine;
    }

    val = adec_read32(ce, CE_ADEC_CTRL);
    val |= tmp;
    adec_write32(ce, CE_ADEC_CTRL, val);
    val &= ~tmp;
    adec_write32(ce, CE_ADEC_CTRL, val);

    if (engine == E_ACC_ENG_DMA)
    {
        rt_syscon_update_bits(ce->crypto->ciu_regmap,
                ENGINE_DMA_ADDR_HIGH_OFFSET, WADDR_BIT32 | RADDR_BIT32, 0);
    }

    return RT_EOK;
}

static rt_err_t abus_set_mode(struct spacemit_crypto_engine *ce,
        enum abus_grp_a grp_a_mode, enum abus_grp_b grp_b_mode,
        enum abus_cross_bar input_bar, enum abus_cross_bar output_bar)
{
    uint32_t val;

    val = abus_read32(ce, CE_ABUS_BUS_CTRL);

    val &= ~(0x77 << 0x4);
    val |= (grp_a_mode << 0x4) | (grp_b_mode << 0x8);

    if (input_bar == E_ABUS_STRAIGHT)
    {
        val &= ~(0x1 << 0x0);
    }
    else if (input_bar == E_ABUS_CROSS)
    {
        val |= 0x1 << 0x0;
    }
    else
    {
        return -RT_EINVAL;
    }

    if (output_bar == E_ABUS_STRAIGHT)
    {
        val &= ~(0x1 << 0x2);
    }
    else if (output_bar == E_ABUS_CROSS)
    {
        val |= 0x1 << 0x2;
    }
    else
    {
        return -RT_EINVAL;
    }

    abus_write32(ce, CE_ABUS_BUS_CTRL, val);

    return RT_EOK;
}

static void enable_biu_mask(struct spacemit_crypto_engine *ce)
{
    rt_uint32_t val;
    val = biu_read32(ce, SP_INTERRUPT_MASK);
    val &=~BIU_MASK;
    biu_write32(ce, SP_INTERRUPT_MASK, val);
}

static void enable_adec_mask(struct spacemit_crypto_engine *ce)
{
    rt_uint32_t val;
    val = adec_read32(ce, CE_ADEC_INT_MSK);
    val &=~ADEC_MASK;
    adec_write32(ce, CE_ADEC_INT_MSK, val);
}

static void enable_engine_irq(struct spacemit_crypto_engine *ce)
{
    rt_uint32_t val;

    /* Clear aes INT */
    val = crypto_read32(ce, CE_CRYPTO_AES_INTRPT_SRC_REG);
    crypto_write32(ce, CE_CRYPTO_AES_INTRPT_SRC_REG, val);

    val = crypto_read32(ce, CE_CRYPTO_AES_INTRPT_SRC_EN_REG);
    val |= AES_INTERRUPT_MASK;
    crypto_write32(ce, CE_CRYPTO_AES_INTRPT_SRC_EN_REG, val);

    val = dma_read32(ce, CE_DMA_OUT_INT_MASK);
    val &= ~DMA_INTERRUPT_MASK;
    dma_write32(ce, CE_DMA_OUT_INT_MASK, val);

    val = dma_read32(ce, CE_DMA_IN_INT_MASK);
    val &= ~DMA_INTERRUPT_MASK;
    dma_write32(ce, CE_DMA_IN_INT_MASK, val);
}

static rt_err_t select_engine_crypto(struct spacemit_crypto_engine *ce,
        enum crypto_eng_sel engine)
{
    rt_uint32_t val;

    val = crypto_read32(ce, CE_CRYPTO_ENGINE_SEL_REG);
    val &= ~0x3;

    switch (engine)
    {
    case E_ENG_AES: val |= 0x1; break;
    default:
        return -RT_EINVAL;
    }

    crypto_write32(ce, CE_CRYPTO_ENGINE_SEL_REG, val);

    return RT_EOK;
}

static void crypto_aes_sw_reset(struct spacemit_crypto_engine *ce)
{
    crypto_write32(ce, CE_CRYPTO_AES_CONTROL_REG, 0x1);
    crypto_write32(ce, CE_CRYPTO_AES_CONTROL_REG, 0x0);
}

static void crypto_aes_start(struct spacemit_crypto_engine *ce)
{
    crypto_write32(ce, CE_CRYPTO_AES_COMMAND_REG, 0x1);
}

static rt_err_t crypto_aes_wait(struct spacemit_crypto_engine *ce)
{
    rt_completion_wait(&ce->aes_done, RT_WAITING_FOREVER);

    if (ce->aes_status != AES_DONE)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t crypto_aes_set_mode(struct spacemit_crypto_engine *ce,
        struct hwcrypto_symmetric *symmetric_ctx,
        struct hwcrypto_symmetric_info *symmetric_info,
        rt_bool_t use_rkey)
{
    rt_uint32_t val;

    select_engine_crypto(ce, E_ENG_AES);

    val = crypto_read32(ce, CE_CRYPTO_AES_CONFIG_REG);
    val &= ~(0x7 << 0x3);

    switch (symmetric_ctx->parent.type)
    {
    case HWCRYPTO_TYPE_AES_ECB: val |= 0x0 << 0x3; break;
    case HWCRYPTO_TYPE_AES_CBC: val |= 0x1 << 0x3; break;
    default:
        break;
    }

    val &= ~(0x3 << 0x1);

    switch (symmetric_ctx->key_bitlen)
    {
    case 128: val |= 0x0 << 0x1; break;
    case 192: val |= 0x2 << 0x1; break;
    case 256: val |= 0x1 << 0x1; break;
    default:
        return -RT_EINVAL;
    }

    val &= ~(0x1 << 0x0);

    if (symmetric_info->mode == HWCRYPTO_MODE_DECRYPT)
    {
        val |= 0x1 << 0x0;
    }
    else
    {
        val |= 0x0 << 0x0;
    }

    val &= ~(0x1 << 0x6);

    if (!use_rkey)
    {
        val |= 0x0 << 0x6;
    }
    else
    {
        val |= 0x1 << 0x6;
    }

    crypto_write32(ce, CE_CRYPTO_AES_CONFIG_REG, val);

    return RT_EOK;
}

static rt_err_t crypto_aes_set_key1(struct spacemit_crypto_engine *ce,
        const rt_uint8_t *key, rt_uint16_t keylen)
{
    rt_uint32_t val, key_end;

    if (!key)
    {
        return RT_EOK;
    }

    switch (keylen)
    {
    case 128: key_end = 4; break;
    case 192: key_end = 6; break;
    case 256: key_end = 8; break;
    default:
        return -RT_EINVAL;
    }

    for (int reg_index = 0; reg_index < 8; ++reg_index)
    {
        if (reg_index < key_end)
        {
            val = ((key[0 + (reg_index << 2)] & 0xff) << 0) |
                  ((key[1 + (reg_index << 2)] & 0xff) << 8) |
                  ((key[2 + (reg_index << 2)] & 0xff) << 16) |
                  ((key[3 + (reg_index << 2)] & 0xff) << 24);
        }
        else
        {
            val = 0;
        }

        crypto_write32(ce, CE_CRYPTO_K1_W_REG(reg_index), val);
    }

    return RT_EOK;
}


static void crypto_aes_set_iv(struct spacemit_crypto_engine *ce, const rt_uint8_t *iv)
{
    rt_uint32_t val;

    for (int reg_index = 0; reg_index < 4; ++reg_index)
    {
        val = ((iv[(reg_index << 2) + 0] & 0xff) << 0) |
              ((iv[(reg_index << 2) + 1] & 0xff) << 8) |
              ((iv[(reg_index << 2) + 2] & 0xff) << 16) |
              ((iv[(reg_index << 2) + 3] & 0xff) << 24);

        crypto_write32(ce, CE_CRYPTO_IV_REG(reg_index), val);
    }
}

static rt_err_t aes_process(struct spacemit_crypto_engine *ce,
        struct hwcrypto_symmetric *symmetric_ctx,
        struct hwcrypto_symmetric_info *symmetric_info,
        rt_uint8_t *buf_in, rt_uint8_t *buf_out, rt_size_t blocks)
{
    rt_err_t err;
    rt_uint32_t val;
    rt_ubase_t dma_addr_in_low, dma_addr_in_high;
    rt_ubase_t dma_addr_out_low, dma_addr_out_high;
    struct spacemit_crypto *crypto = ce->crypto;

    rt_memcpy(ce->in_buffer, buf_in, blocks << 4);

    dma_addr_in_high = rt_upper_32_bits(ce->in_buffer_dma);
    dma_addr_in_low = rt_lower_32_bits(ce->in_buffer_dma);
    dma_addr_out_high = rt_upper_32_bits(ce->out_buffer_dma);
    dma_addr_out_low = rt_lower_32_bits(ce->out_buffer_dma);

    /* Reset the HW before using it */
    adec_engine_hw_reset(ce, E_ACC_ENG_DMA);
    adec_engine_hw_reset(ce, E_ACC_ENG_CRYPTO);
    abus_set_mode(ce, E_ABUS_GRP_A_HASH, E_ABUS_GRP_B_AES, E_ABUS_STRAIGHT, E_ABUS_STRAIGHT);
    crypto_aes_sw_reset(ce);

    rt_syscon_read(crypto->ciu_regmap, ENGINE_DMA_ADDR_HIGH_OFFSET, &val);
    switch (ce - ce->crypto->engine)
    {
    case 0:
        val &= ~(WADDR_BIT32 | RADDR_BIT32);
        val |= ((dma_addr_out_high & 0x1) << 4 | (dma_addr_in_high & 0x1) << 5);
        break;

    case 1:
        val &= ~0xff00;
        val |= ((dma_addr_out_high & 0xf) << 8 | (dma_addr_in_high & 0xf) << 12);;
        break;

    default:
        return -RT_EINVAL;
    }
    rt_syscon_write(crypto->ciu_regmap, ENGINE_DMA_ADDR_HIGH_OFFSET, val);

    if (ce->in_buffer_dma & 0x3 || ce->out_buffer_dma & 0x3)
    {
        return -RT_EINVAL;
    }

    enable_biu_mask(ce);
    enable_adec_mask(ce);
    enable_engine_irq(ce);

    dma_input_config(ce, 0, 0);
    dma_output_config(ce, 0, 1);

    dma_input_address(ce, dma_addr_in_low, blocks << 2, RT_FALSE);
    dma_output_address(ce, dma_addr_out_low, blocks << 2, RT_FALSE);

    /* Process KEY */
    if ((err = crypto_aes_set_mode(ce, symmetric_ctx, symmetric_info, RT_FALSE)))
    {
        return err;
    }

    if ((err = crypto_aes_set_key1(ce, symmetric_ctx->key, symmetric_ctx->key_bitlen)))
    {
        return err;
    }

    /* Process IV */
    switch (symmetric_ctx->parent.type)
    {
    case HWCRYPTO_TYPE_AES_CBC:
        crypto_aes_set_iv(ce, symmetric_ctx->iv);
        break;

    default:
        break;
    }

    crypto_write32(ce, CE_CRYPTO_AES_STREAM_SIZE_REG, blocks << 4);

    dma_input_start(ce);
    dma_output_start(ce);
    crypto_aes_start(ce);

    if ((err = dma_wait_int_input_finish(ce)))
    {
        return err;
    }

    if ((err = crypto_aes_wait(ce)))
    {
        return err;
    }

    if ((err = dma_wait_int_output_finish(ce)))
    {
        return err;
    }

    /* Readback IV after operation */
    switch (symmetric_ctx->parent.type)
    {
    case HWCRYPTO_TYPE_AES_CBC:
        crypto_aes_set_iv(ce, symmetric_ctx->iv);
        break;

    default:
        break;
    }

    rt_memcpy(buf_out, ce->out_buffer, blocks << 4);

    return RT_EOK;
}

static rt_err_t spacemit_crypto_symmetric_crypt(
        struct hwcrypto_symmetric *symmetric_ctx,
        struct hwcrypto_symmetric_info *symmetric_info)
{
    rt_err_t err;
    rt_uint32_t blocks;
    rt_uint8_t *buf_in, *buf_out;
    struct spacemit_crypto_engine *ce = raw_to_spacemit_crypto_engine(symmetric_ctx);

    if (!symmetric_ctx->iv_len)
    {
        symmetric_ctx->iv_len = sizeof(symmetric_ctx->iv);
        rt_memset(symmetric_ctx->iv, 0, symmetric_ctx->iv_len);
    }

    switch (symmetric_ctx->parent.type)
    {
    case HWCRYPTO_TYPE_AES_ECB:
    case HWCRYPTO_TYPE_AES_CBC:
        break;
    default:
        return -RT_ENOSYS;
    }

    if (symmetric_info->mode != HWCRYPTO_MODE_ENCRYPT &&
        symmetric_info->mode != HWCRYPTO_MODE_DECRYPT)
    {
        return -RT_ENOSYS;
    }

    buf_in = (void *)symmetric_info->in;
    buf_out = symmetric_info->out;
    blocks = symmetric_info->length / AES_BLOCK_SIZE;

    rt_mutex_take(&ce->lock, RT_WAITING_FOREVER);

    if ((rt_ubase_t)buf_in & 0x3 || (rt_ubase_t)buf_out & 0x3)
    {
        int len_bytes = 0, step_bytes = 0;
        rt_uint8_t *in_cpy, *out_cpy, *in_work, *out_work;
        rt_uint8_t *aligned_buf_1 = &ce->internal_working_buffer[0];
        rt_uint8_t *aligned_buf_2 = &ce->internal_working_buffer[WORK_BUF_SIZE];

        len_bytes = blocks << 4;
        in_cpy = (rt_uint8_t *)buf_in;
        out_cpy = (rt_uint8_t *)buf_out;

        while (len_bytes)
        {
            step_bytes = len_bytes > WORK_BUF_SIZE ? WORK_BUF_SIZE : len_bytes;

            if ((rt_ubase_t)buf_in & 0x3)
            {
                rt_memcpy(aligned_buf_1, in_cpy, step_bytes);
                in_work = aligned_buf_1;
            }
            else
            {
                in_work = in_cpy;
            }

            len_bytes -= step_bytes;
            in_cpy += step_bytes;

            if ((rt_ubase_t)buf_out & 0x3)
            {
                rt_memset(aligned_buf_2, 0x0, WORK_BUF_SIZE);
                out_work = aligned_buf_2;
            }
            else
            {
                out_work = out_cpy;
            }

            if ((err = aes_process(ce, symmetric_ctx, symmetric_info, in_work, out_work, step_bytes >> 4)))
            {
                goto _out_lock;
            }

            if ((rt_ubase_t)buf_out & 0x3)
            {
                rt_memcpy(out_cpy, aligned_buf_2, step_bytes);
            }

            out_cpy += step_bytes;
        }
    }
    else
    {
        err = aes_process(ce, symmetric_ctx, symmetric_info, buf_in, buf_out, blocks);
    }

_out_lock:
    rt_mutex_release(&ce->lock);

    return err;
}

static const struct hwcrypto_symmetric_ops spacemit_crypto_symmetric_ops =
{
    .crypt = spacemit_crypto_symmetric_crypt,
};

static rt_err_t spacemit_crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    struct hwcrypto_symmetric *crypto_symmetric;

    if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) != HWCRYPTO_TYPE_AES)
    {
        return -RT_ENOSYS;
    }

    crypto_symmetric = rt_container_of(ctx, struct hwcrypto_symmetric, parent);

    crypto_symmetric->ops = &spacemit_crypto_symmetric_ops;

    return RT_EOK;
}

static void spacemit_crypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    if (!ctx->contex)
    {
        return;
    }

    if ((ctx->type & HWCRYPTO_MAIN_TYPE_MASK) == HWCRYPTO_TYPE_AES)
    {
        rt_free(ctx->contex);
    }
}

static rt_err_t spacemit_crypto_copy(struct rt_hwcrypto_ctx *des,
        const struct rt_hwcrypto_ctx *src)
{
    if ((src->type & HWCRYPTO_MAIN_TYPE_MASK) != HWCRYPTO_TYPE_AES)
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static void spacemit_crypto_reset(struct rt_hwcrypto_ctx *ctx)
{
}

static const struct rt_hwcrypto_ops spacemit_crypto_ops =
{
    .create = spacemit_crypto_create,
    .destroy = spacemit_crypto_destroy,
    .copy = spacemit_crypto_copy,
    .reset = spacemit_crypto_reset,
};

static void spacemit_crypto_isr(int irq, void *param)
{
    volatile rt_uint32_t val_aes;
    struct spacemit_crypto_engine *ce = param;

    /* AES */
    val_aes = crypto_read32(ce, CE_CRYPTO_AES_INTRPT_SRC_REG);

    if (val_aes & AES_INTERRUPT_MASK)
    {
        crypto_write32(ce, CE_CRYPTO_AES_INTRPT_SRC_REG, val_aes);
        adec_biu_clear_int_flag(ce);

        ce->aes_status = (val_aes & AES_INTERRUPT_FLAG) ? AES_DONE : AES_ERROR;
        rt_completion_done(&ce->aes_done);

        return;
    }

    /* DMA output */
    val_aes = dma_read32(ce, CE_DMA_OUT_INT);

    if (val_aes & DMA_INTERRUPT_MASK)
    {
        dma_output_stop(ce);
        dma_write32(ce, CE_DMA_OUT_INT, val_aes);
        adec_biu_clear_int_flag(ce);

        ce->dma_out_status = (val_aes & BIT_DMA_INOUT_DONE) ? DMA_INOUT_DONE : DMA_INOUT_ERROR;
        rt_completion_done(&ce->dma_output_done);

        return;
    }

    /* DMA input */
    val_aes = dma_read32(ce, CE_DMA_IN_INT);

    if (val_aes & DMA_INTERRUPT_MASK)
    {
        dma_input_stop(ce);
        dma_write32(ce, CE_DMA_IN_INT, val_aes);
        adec_biu_clear_int_flag(ce);

        ce->dma_in_status = (val_aes & BIT_DMA_INOUT_DONE) ? DMA_INOUT_DONE : DMA_INOUT_ERROR;
        rt_completion_done(&ce->dma_input_done);

        return;
    }
}

static void spacemit_crypto_free(struct spacemit_crypto *crypto, struct rt_device *dev)
{
    if (!rt_is_err_or_null(crypto->clk))
    {
        rt_clk_disable_unprepare(crypto->clk);
        rt_clk_put(crypto->clk);
    }

    if (!rt_is_err_or_null(crypto->rstc))
    {
        rt_reset_control_assert(crypto->rstc);
        rt_reset_control_put(crypto->rstc);
    }

    for (int i = 0; i < crypto->engine_nr; ++i)
    {
        struct spacemit_crypto_engine *ce = &crypto->engine[i];

        if (ce->base)
        {
            rt_iounmap(ce->base);
        }

        if (ce->in_buffer)
        {
            rt_dma_free_coherent(dev, SPACEMIT_AES_BUFFER_LEN, ce->in_buffer, ce->in_buffer_dma);
        }

        if (ce->out_buffer)
        {
            rt_dma_free_coherent(dev, SPACEMIT_AES_BUFFER_LEN, ce->out_buffer, ce->out_buffer_dma);
        }

        if (ce->crypto)
        {
            rt_mutex_detach(&ce->lock);

            if (rt_device_find(rt_dm_dev_get_name(&ce->parent.parent)))
            {
                rt_hw_interrupt_mask(ce->irq);
                rt_pic_detach_irq(ce->irq, ce);

                rt_device_unregister(&ce->parent.parent);
            }
        }
    }

    rt_free(crypto);
}

static rt_err_t spacemit_crypto_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    char name[32];
    struct rt_device *dev = &pdev->parent;
    struct spacemit_crypto *crypto = rt_calloc(1, sizeof(*crypto));

    if (!crypto)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "num-engines", &crypto->engine_nr)))
    {
        goto _fail;
    }

    if (!(crypto->ciu_regmap = rt_syscon_find_by_ofw_compatible("spacemit,ciu")))
    {
        err = -RT_EIO;
        goto _fail;
    }

    crypto->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(crypto->clk))
    {
        err = rt_ptr_err(crypto->clk);
        goto _fail;
    }
    rt_clk_prepare_enable(crypto->clk);

    crypto->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(crypto->rstc))
    {
        err = rt_ptr_err(crypto->rstc);
        goto _fail;
    }
    rt_reset_control_deassert(crypto->rstc);

    for (int i = 0; i < crypto->engine_nr; ++i)
    {
        rt_uint32_t addr_range[2];
        struct spacemit_crypto_engine *ce = &crypto->engine[i];

        rt_snprintf(name, sizeof(name), "spacemit-crypto-engine-%d", i);

        if ((err = rt_dm_dev_prop_read_u32_array_index(dev, name, 0, 2, &addr_range[0])) <= 0)
        {
            goto _fail;
        }

        if (!(ce->base = rt_ioremap((void *)(rt_ubase_t)addr_range[0], addr_range[1])))
        {
            err = -RT_EIO;
            goto _fail;
        }

        if ((ce->irq = rt_dm_dev_get_irq(dev, i)) < 0)
        {
            err = ce->irq;
            goto _fail;
        }

        ce->in_buffer = rt_dma_alloc_coherent(dev, SPACEMIT_AES_BUFFER_LEN, &ce->in_buffer_dma);
        if (!ce->in_buffer)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }

        ce->out_buffer = rt_dma_alloc_coherent(dev, SPACEMIT_AES_BUFFER_LEN, &ce->out_buffer_dma);
        if (!ce->out_buffer)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }

        ce->crypto = crypto;

        rt_completion_init(&ce->aes_done);
        rt_completion_init(&ce->dma_output_done);
        rt_completion_init(&ce->dma_input_done);

        rt_snprintf(name, sizeof(name), "%s%d", RT_HWCRYPTO_DEFAULT_NAME, i);
        rt_mutex_init(&ce->lock, name, RT_IPC_FLAG_PRIO);

        ce->parent.ops = &spacemit_crypto_ops;
        ce->parent.id = __LINE__;

        if ((err = rt_hwcrypto_register(&ce->parent, name)))
        {
            goto _fail;
        }

        rt_hw_interrupt_install(ce->irq, spacemit_crypto_isr, ce, name);
        rt_hw_interrupt_umask(ce->irq);
    }

    rt_syscon_update_bits(crypto->ciu_regmap, ENGINE_DMA_ADDR_HIGH_OFFSET,
            SW_RESETN | MASTER_CLK_EN | SLAVE_CLK_EN,
            SW_RESETN | MASTER_CLK_EN | SLAVE_CLK_EN);

    dev->user_data = crypto;

    return RT_EOK;

_fail:
    spacemit_crypto_free(crypto, dev);

    return err;
}

static rt_err_t spacemit_crypto_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct spacemit_crypto *crypto = dev->user_data;

    spacemit_crypto_free(crypto, dev);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_crypto_ofw_ids[] =
{
    { .compatible = "spacemit,crypto_engine" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_crypto_driver =
{
    .name = "hwcrypto-spacemit",
    .ids = spacemit_crypto_ofw_ids,

    .probe = spacemit_crypto_probe,
    .remove = spacemit_crypto_remove,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_crypto_driver);
