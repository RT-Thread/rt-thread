#include "bflb_dma.h"
#include "bflb_l1c.h"
#include "hardware/dma_reg.h"

struct bflb_dma_irq_callback {
    void (*handler)(void *arg);
    void *arg;
};

#if defined(BL702) || defined(BL602) || defined(BL702L)
const uint32_t dma_base[] = { 0x4000C000 };
struct bflb_dma_irq_callback dma_callback[1][8];
#elif defined(BL616)
const uint32_t dma_base[] = { 0x2000C000 };
struct bflb_dma_irq_callback dma_callback[1][4];
#elif defined(BL606P) || defined(BL808)
const uint32_t dma_base[] = { 0x2000C000, 0x20071000, 0x30001000 };
struct bflb_dma_irq_callback dma_callback[3][8];
#elif defined(BL628)
const uint32_t dma_base[] = { 0x20081000 };
struct bflb_dma_irq_callback dma_callback[1][8];
#endif

void dma0_isr(int irq, void *arg)
{
    uint32_t regval;

    regval = getreg32(dma_base[0] + DMA_INTTCSTATUS_OFFSET);
    putreg32(regval, dma_base[0] + DMA_INTTCCLEAR_OFFSET);

    for (uint8_t i = 0; i < 8; i++) {
        if (regval & (1 << i)) {
            dma_callback[0][i].handler(dma_callback[0][i].arg);
        }
    }
}

#if defined(BL606P) || defined(BL808)
void dma1_isr(int irq, void *arg)
{
    uint32_t regval;

    regval = getreg32(dma_base[1] + DMA_INTTCSTATUS_OFFSET);
    putreg32(regval, dma_base[1] + DMA_INTTCCLEAR_OFFSET);

    for (uint8_t i = 0; i < 8; i++) {
        if (regval & (1 << i)) {
            dma_callback[1][i].handler(dma_callback[1][i].arg);
        }
    }
}

void dma2_isr(int irq, void *arg)
{
    uint32_t regval;

    regval = getreg32(dma_base[2] + DMA_INTTCSTATUS_OFFSET);
    putreg32(regval, dma_base[2] + DMA_INTTCCLEAR_OFFSET);

    for (uint8_t i = 0; i < 8; i++) {
        if (regval & (1 << i)) {
            dma_callback[1][i].handler(dma_callback[2][i].arg);
        }
    }
}
#endif

void bflb_dma_channel_init(struct bflb_device_s *dev, const struct bflb_dma_channel_config_s *config)
{
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    /* dma global enable */
    regval = getreg32(dma_base[dev->idx] + DMA_TOP_CONFIG_OFFSET);
    regval |= DMA_E;
    putreg32(regval, dma_base[dev->idx] + DMA_TOP_CONFIG_OFFSET);

    /* dma channel disable */
    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval &= ~DMA_E;
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);

#if defined(BL602)
    regval = 0;
#else
    regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
    regval &= DMA_DST_ADD_MODE | DMA_DST_MIN_MODE | DMA_FIX_CNT_MASK;
#endif

    if (config->src_addr_inc) {
        regval |= DMA_SI;
    }
    if (config->dst_addr_inc) {
        regval |= DMA_DI;
    }

    regval |= (config->src_width << DMA_SWIDTH_SHIFT);
    regval |= (config->dst_width << DMA_DWIDTH_SHIFT);
    regval |= (config->src_burst_count << DMA_SBSIZE_SHIFT);
    regval |= (config->dst_burst_count << DMA_DBSIZE_SHIFT);
    putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);

    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval &= ~DMA_SRCPERIPHERAL_MASK;
    regval &= ~DMA_DSTPERIPHERAL_MASK;
    regval &= ~DMA_FLOWCNTRL_MASK;
    regval &= ~DMA_LLICOUNTER_MASK;
    regval |= (config->src_req << DMA_SRCPERIPHERAL_SHIFT);
    regval |= (config->dst_req << DMA_DSTPERIPHERAL_SHIFT);
    regval |= (config->direction << DMA_FLOWCNTRL_SHIFT);
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);

    /* enable dma error and tc interrupt */
    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval |= (DMA_ITC | DMA_IE);
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);

    regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
    regval &= ~DMA_I;
    putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);

    /* clear irq status */
    putreg32(1 << dev->sub_idx, dma_base[dev->idx] + DMA_INTTCCLEAR_OFFSET);
    putreg32(1 << dev->sub_idx, dma_base[dev->idx] + DMA_INTERRCLR_OFFSET);

#if (defined(BL606P) || defined(BL808)) && (defined(CPU_M0) || defined(CPU_LP))
    bflb_irq_attach(31, dma0_isr, NULL);
    bflb_irq_attach(32, dma1_isr, NULL);
    bflb_irq_enable(31);
    bflb_irq_enable(32);
#elif (defined(BL606P) || defined(BL808)) && defined(CPU_D0)
    bflb_irq_attach(40, dma2_isr, NULL);
    bflb_irq_attach(41, dma2_isr, NULL);
    bflb_irq_attach(42, dma2_isr, NULL);
    bflb_irq_attach(43, dma2_isr, NULL);
    bflb_irq_attach(44, dma2_isr, NULL);
    bflb_irq_attach(45, dma2_isr, NULL);
    bflb_irq_attach(46, dma2_isr, NULL);
    bflb_irq_attach(47, dma2_isr, NULL);
    bflb_irq_enable(40);
    bflb_irq_enable(41);
    bflb_irq_enable(42);
    bflb_irq_enable(43);
    bflb_irq_enable(44);
    bflb_irq_enable(45);
    bflb_irq_enable(46);
    bflb_irq_enable(47);
#else
    bflb_irq_attach(dev->irq_num, dma0_isr, NULL);
    bflb_irq_enable(dev->irq_num);
#endif
}

void bflb_dma_lli_config(struct bflb_device_s *dev, struct bflb_dma_channel_lli_pool_s *lli_pool, uint32_t lli_count, uint32_t src_addr, uint32_t dst_addr, uint32_t transfer_offset, uint32_t last_transfer_len)
{
    uint32_t channel_base;
    union bflb_dma_lli_control_s dma_ctrl_cfg;

    channel_base = dev->reg_base;

    dma_ctrl_cfg = (union bflb_dma_lli_control_s)getreg32(channel_base + DMA_CxCONTROL_OFFSET);

    dma_ctrl_cfg.bits.TransferSize = 4064;
    dma_ctrl_cfg.bits.I = 0;

    /* nbytes will be integer multiple of 4064*n or 4064*2*n or 4064*4*n,(n>0) */
    for (uint32_t i = 0; i < lli_count; i++) {
        lli_pool[i].src_addr = src_addr;
        lli_pool[i].dst_addr = dst_addr;
        lli_pool[i].nextlli = 0;

        if (dma_ctrl_cfg.bits.SI) {
            src_addr += transfer_offset;
        }

        if (dma_ctrl_cfg.bits.DI) {
            dst_addr += transfer_offset;
        }

        if (i == lli_count - 1) {
            dma_ctrl_cfg.bits.TransferSize = last_transfer_len;
            dma_ctrl_cfg.bits.I = 1;
        }

        if (i) {
            lli_pool[i - 1].nextlli = (uint32_t)(uintptr_t)&lli_pool[i];
        }

        lli_pool[i].control = dma_ctrl_cfg;
    }
}

int bflb_dma_channel_lli_reload(struct bflb_device_s *dev, struct bflb_dma_channel_lli_pool_s *lli_pool, uint32_t max_lli_count, struct bflb_dma_channel_lli_transfer_s *transfer, uint32_t count)
{
    uint32_t channel_base;
    uint32_t actual_transfer_offset = 0;
    uint32_t actual_transfer_len = 0;
    uint32_t last_transfer_len = 0;
    uint32_t current_lli_count = 0;
    uint32_t lli_count_used_offset = 0;
    union bflb_dma_lli_control_s dma_ctrl_cfg;

    channel_base = dev->reg_base;

    dma_ctrl_cfg = (union bflb_dma_lli_control_s)getreg32(channel_base + DMA_CxCONTROL_OFFSET);

    switch (dma_ctrl_cfg.bits.SWidth) {
        case DMA_DATA_WIDTH_8BIT:
            actual_transfer_offset = 4064;
            break;
        case DMA_DATA_WIDTH_16BIT:
            actual_transfer_offset = 4064 << 1;
            break;
        case DMA_DATA_WIDTH_32BIT:
            actual_transfer_offset = 4064 << 2;
            break;
        default:
            break;
    }

    for (size_t i = 0; i < count; i++) {
        switch (dma_ctrl_cfg.bits.SWidth) {
            case DMA_DATA_WIDTH_8BIT:
                actual_transfer_len = transfer[i].nbytes;
                break;
            case DMA_DATA_WIDTH_16BIT:
                if (transfer[i].nbytes % 2) {
                    return -1;
                }
                actual_transfer_len = transfer[i].nbytes >> 1;
                break;
            case DMA_DATA_WIDTH_32BIT:
                if (transfer[i].nbytes % 4) {
                    return -1;
                }
                actual_transfer_len = transfer[i].nbytes >> 2;
                break;

            default:
                break;
        }

        current_lli_count = actual_transfer_len / 4064 + 1;
        last_transfer_len = actual_transfer_len % 4064;

        /* The maximum transfer capacity of the last node is 4095 */
        if (current_lli_count > 1 && last_transfer_len < (4095 - 4064)) {
            current_lli_count--;
            last_transfer_len += 4064;
        }

        bflb_dma_lli_config(dev, &lli_pool[lli_count_used_offset], current_lli_count, transfer[i].src_addr, transfer[i].dst_addr, actual_transfer_offset, last_transfer_len);
        if (i) {
            lli_pool[lli_count_used_offset - 1].nextlli = (uint32_t)(uintptr_t)&lli_pool[lli_count_used_offset];
        }
        lli_count_used_offset += current_lli_count;

        if (lli_count_used_offset > max_lli_count) {
            return -ENOMEM;
        }
    }

    putreg32(lli_pool[0].src_addr, channel_base + DMA_CxSRCADDR_OFFSET);
    putreg32(lli_pool[0].dst_addr, channel_base + DMA_CxDSTADDR_OFFSET);
    putreg32(lli_pool[0].nextlli, channel_base + DMA_CxLLI_OFFSET);
    putreg32(lli_pool[0].control.WORD, channel_base + DMA_CxCONTROL_OFFSET);
#if defined(BL616) || defined(BL606P) || defined(BL808)
    /* clean cache, DMA does not pass through the cache */
    bflb_l1c_dcache_clean_range((uint32_t *)(uintptr_t)lli_pool, sizeof(struct bflb_dma_channel_lli_pool_s) * lli_count_used_offset);
#endif
    return lli_count_used_offset;
}

void bflb_dma_channel_lli_link_head(struct bflb_device_s *dev,
                                    struct bflb_dma_channel_lli_pool_s *lli_pool,
                                    uint32_t used_lli_count)
{
    uint32_t channel_base;

    channel_base = dev->reg_base;

    lli_pool[used_lli_count - 1].nextlli = (uint32_t)(uintptr_t)&lli_pool[0];

    putreg32(lli_pool[0].nextlli, channel_base + DMA_CxLLI_OFFSET);
#if defined(BL616) || defined(BL606P) || defined(BL808)
    /* clean cache, DMA does not pass through the cache */
    bflb_l1c_dcache_clean_range((uint32_t *)lli_pool, sizeof(struct bflb_dma_channel_lli_pool_s) * used_lli_count);
#endif
}

void bflb_dma_channel_start(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    /* dma channel enable */
    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval |= DMA_E;
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);
}

void bflb_dma_channel_stop(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    /* dma channel disable */
    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval &= ~DMA_E;
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);
}

bool bflb_dma_channel_isbusy(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    if (regval & (1 << 0)) {
        return true;
    } else {
        return false;
    }
}

void bflb_dma_channel_tcint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    if (mask) {
        regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
        regval |= DMA_ITC;
        putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);

        regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
        regval &= ~DMA_I;
        putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
    } else {
        regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
        regval &= ~DMA_ITC;
        putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);

        regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
        regval |= DMA_I;
        putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
    }
}

void bflb_dma_channel_irq_attach(struct bflb_device_s *dev, void (*callback)(void *arg), void *arg)
{
    dma_callback[dev->idx][dev->sub_idx].handler = callback;
    dma_callback[dev->idx][dev->sub_idx].arg = arg;

    bflb_dma_channel_tcint_mask(dev, false);
}

void bflb_dma_channel_irq_detach(struct bflb_device_s *dev)
{
    dma_callback[dev->idx][dev->sub_idx].handler = NULL;
    dma_callback[dev->idx][dev->sub_idx].arg = NULL;

    bflb_dma_channel_tcint_mask(dev, true);
}

bool bflb_dma_channel_get_tcint_status(struct bflb_device_s *dev)
{
    uint32_t regval;

    regval = getreg32(dma_base[dev->idx] + DMA_INTTCSTATUS_OFFSET);
    if (regval & (1 << dev->sub_idx)) {
        return true;
    } else {
        return false;
    }
}

void bflb_dma_channel_tcint_clear(struct bflb_device_s *dev)
{
    putreg32(1 << dev->sub_idx, dma_base[dev->idx] + DMA_INTTCCLEAR_OFFSET);
}

int bflb_dma_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    switch (cmd) {
        case DMA_CMD_SET_SRCADDR_INCREMENT:
            regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
            if (arg) {
                regval |= DMA_SI;
            } else {
                regval &= ~DMA_SI;
            }
            putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
            break;

        case DMA_CMD_SET_DSTADDR_INCREMENT:
            regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
            if (arg) {
                regval |= DMA_DI;
            } else {
                regval &= ~DMA_DI;
            }
            putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
            break;

#if !defined(BL602)
        case DMA_CMD_SET_ADD_MODE:
            regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
            if (arg) {
                regval |= DMA_DST_ADD_MODE;
            } else {
                regval &= ~DMA_DST_ADD_MODE;
            }
            putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
            break;

        case DMA_CMD_SET_REDUCE_MODE:
            regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
            if (arg) {
                regval |= DMA_DST_MIN_MODE;
                regval &= ~DMA_FIX_CNT_MASK;
                regval |= (arg & 0x7) << DMA_FIX_CNT_SHIFT;
            } else {
                regval &= ~DMA_DST_MIN_MODE;
            }
            putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
            break;
#endif
        case DMA_CMD_SET_LLI_CONFIG:
            arch_memcpy4((uint32_t *)(channel_base + DMA_CxSRCADDR_OFFSET), (uint32_t *)arg, 4);
            break;
        case DMA_CMD_GET_LLI_CONTROL:
            return getreg32(channel_base + DMA_CxCONTROL_OFFSET);
        default:
            ret = -EPERM;
            break;
    }
    return ret;
}