#include "bflb_i2s.h"
#include "bflb_clock.h"
#include "hardware/i2s_reg.h"

void bflb_i2s_init(struct bflb_device_s *dev, const struct bflb_i2s_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t div;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + I2S_CONFIG_OFFSET);
    /* disable I2S */
    regval &= ~I2S_CR_I2S_M_EN;
    regval &= ~I2S_CR_I2S_S_EN;
    regval &= ~I2S_CR_I2S_TXD_EN;
    regval &= ~I2S_CR_I2S_TXD_EN;
    putreg32(regval, reg_base + I2S_CONFIG_OFFSET);

    if (config->channel_mode == I2S_CHANNEL_MODE_NUM_1) {
        /* Mono mode */
        regval |= I2S_CR_MONO_MODE;
        regval &= ~I2S_CR_FS_CH_CNT_MASK;
    } else {
        regval &= ~I2S_CR_MONO_MODE;
        regval &= ~I2S_CR_FS_CH_CNT_MASK;
        regval |= (config->channel_mode - 1) << I2S_CR_FS_CH_CNT_SHIFT;
    }

    /* disable mute */
    regval &= ~I2S_CR_MUTE_MODE;

    if (config->format_mode == I2S_MODE_DSP_SHORT_FRAME_SYNC) {
        /* dsp modeA/B short frame sync, there is only one bclk cycle */
        regval |= I2S_CR_FS_1T_MODE;
    } else {
        regval &= ~I2S_CR_FS_1T_MODE;
    }

    /* frame/data width */
    regval &= ~I2S_CR_FRAME_SIZE_MASK;
    regval &= ~I2S_CR_DATA_SIZE_MASK;
    regval |= config->frame_width << I2S_CR_FRAME_SIZE_SHIFT;
    regval |= config->data_width << I2S_CR_DATA_SIZE_SHIFT;

    if (config->format_mode == I2S_MODE_LEFT_JUSTIFIED) {
        /* left justified*/
        regval &= ~I2S_CR_I2S_MODE_MASK;
    } else if (config->format_mode == I2S_MODE_RIGHT_JUSTIFIED) {
        /* right justified*/
        regval &= ~I2S_CR_I2S_MODE_MASK;
        regval |= 1 << I2S_CR_I2S_MODE_SHIFT;
    } else {
        /* dsp mode */
        regval &= ~I2S_CR_I2S_MODE_MASK;
        regval |= 2 << I2S_CR_I2S_MODE_SHIFT;
    }

    /* fs_offset_cycle */
    if (config->fs_offset_cycle) {
        regval |= I2S_CR_OFS_EN;
        regval &= ~I2S_CR_OFS_CNT_MASK;
        regval |= ((config->fs_offset_cycle - 1) << I2S_CR_OFS_CNT_SHIFT) & I2S_CR_OFS_CNT_MASK;
    } else {
        regval &= ~I2S_CR_OFS_EN;
    }

    /* rx mono mode L-channel */
    regval &= ~I2S_CR_MONO_RX_CH;
    /* MSB */
    regval &= ~I2S_CR_ENDIAN;

    putreg32(regval, reg_base + I2S_CONFIG_OFFSET);

    /* integer frequency segmentation by rounding */
    div = (bflb_clk_get_peripheral_clock(BFLB_DEVICE_TYPE_I2S, dev->idx) / 2 * 10 / config->bclk_freq_hz + 5) / 10;
    div = (div) ? (div - 1) : 0;
    div = (div > 0xfff) ? 0xfff : div;

    /* bclk timing config */
    regval = getreg32(reg_base + I2S_BCLK_CONFIG_OFFSET);
    regval &= ~I2S_CR_BCLK_DIV_L_MASK;
    regval &= ~I2S_CR_BCLK_DIV_H_MASK;
    regval |= div << I2S_CR_BCLK_DIV_L_SHIFT;
    regval |= div << I2S_CR_BCLK_DIV_H_SHIFT;
    putreg32(regval, reg_base + I2S_BCLK_CONFIG_OFFSET);

    /* fifo threshold config */
    regval = getreg32(reg_base + I2S_FIFO_CONFIG_1_OFFSET);
    regval &= ~I2S_TX_FIFO_TH_MASK;
    regval &= ~I2S_RX_FIFO_TH_MASK;
    regval |= (config->tx_fifo_threshold << I2S_TX_FIFO_TH_SHIFT) & I2S_TX_FIFO_TH_MASK;
    regval |= (config->tx_fifo_threshold << I2S_RX_FIFO_TH_SHIFT) & I2S_RX_FIFO_TH_MASK;
    putreg32(regval, reg_base + I2S_FIFO_CONFIG_1_OFFSET);

    regval = getreg32(reg_base + I2S_FIFO_CONFIG_0_OFFSET);
    /* 32bit to 24bit */
    regval &= ~I2S_CR_FIFO_24B_LJ;
    /* Exchange L/R channel data */
    regval &= ~I2S_CR_FIFO_LR_EXCHG;
    /* Each FIFO entry contains both L/R channel data */
    regval &= ~I2S_CR_FIFO_LR_MERGE;
    /* disable dma */
    regval &= ~I2S_DMA_TX_EN;
    regval &= ~I2S_DMA_RX_EN;
    /* clean fifo */
    regval |= I2S_TX_FIFO_CLR;
    regval |= I2S_RX_FIFO_CLR;
    putreg32(regval, reg_base + I2S_FIFO_CONFIG_0_OFFSET);

    regval = getreg32(reg_base + I2S_IO_CONFIG_OFFSET);
    /* disable deglitch */
    regval &= ~I2S_CR_DEG_EN;
    /* disable inverse signal */
    regval &= ~I2S_CR_I2S_BCLK_INV;
    regval &= ~I2S_CR_I2S_FS_INV;
    regval &= ~I2S_CR_I2S_RXD_INV;
    regval &= ~I2S_CR_I2S_TXD_INV;
    putreg32(regval, reg_base + I2S_IO_CONFIG_OFFSET);

    /* enable I2S, but disable tx and rx */
    regval = getreg32(reg_base + I2S_CONFIG_OFFSET);
    if (config->role == I2S_ROLE_MASTER) {
        regval |= I2S_CR_I2S_M_EN;
    } else {
        regval |= I2S_CR_I2S_S_EN;
    }
    putreg32(regval, reg_base + I2S_CONFIG_OFFSET);
}

void bflb_i2s_deinit(struct bflb_device_s *dev)
{
    uint32_t regval;
    uint32_t reg_base;

    reg_base = dev->reg_base;

    /* disable I2S */
    regval = getreg32(reg_base + I2S_CONFIG_OFFSET);
    regval &= ~I2S_CR_I2S_S_EN;
    regval &= ~I2S_CR_I2S_M_EN;
    putreg32(regval, reg_base + I2S_CONFIG_OFFSET);
}

void bflb_i2s_link_txdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + I2S_FIFO_CONFIG_0_OFFSET);
    if (enable) {
        regval |= I2S_DMA_TX_EN;
    } else {
        regval &= ~I2S_DMA_TX_EN;
    }
    putreg32(regval, reg_base + I2S_FIFO_CONFIG_0_OFFSET);
}

void bflb_i2s_link_rxdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + I2S_FIFO_CONFIG_0_OFFSET);
    if (enable) {
        regval |= I2S_DMA_RX_EN;
    } else {
        regval &= ~I2S_DMA_RX_EN;
    }
    putreg32(regval, reg_base + I2S_FIFO_CONFIG_0_OFFSET);
}

void bflb_i2s_txint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;
    uint32_t reg_base = dev->reg_base;

    regval = getreg32(reg_base + I2S_INT_STS_OFFSET);
    if (mask) {
        regval |= I2S_CR_I2S_TXF_MASK;
    } else {
        regval &= ~I2S_CR_I2S_TXF_MASK;
    }
    putreg32(regval, reg_base + I2S_INT_STS_OFFSET);
}

void bflb_i2s_rxint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;
    uint32_t reg_base = dev->reg_base;

    regval = getreg32(reg_base + I2S_INT_STS_OFFSET);
    if (mask) {
        regval |= I2S_CR_I2S_RXF_MASK;
    } else {
        regval &= ~I2S_CR_I2S_RXF_MASK;
    }
    putreg32(regval, reg_base + I2S_INT_STS_OFFSET);
}

void bflb_i2s_errint_mask(struct bflb_device_s *dev, bool mask)
{
    uint32_t regval;
    uint32_t reg_base = dev->reg_base;

    regval = getreg32(reg_base + I2S_INT_STS_OFFSET);
    if (mask) {
        regval |= I2S_CR_I2S_FER_MASK;
    } else {
        regval &= ~I2S_CR_I2S_FER_MASK;
    }
    putreg32(regval, reg_base + I2S_INT_STS_OFFSET);
}

uint32_t bflb_i2s_get_intstatus(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t int_status;
    uint32_t int_mask;

    reg_base = dev->reg_base;

    int_status = getreg32(reg_base + I2S_INT_STS_OFFSET) & 0x1f;

    int_mask = (getreg32(reg_base + I2S_INT_STS_OFFSET) >> 8) & 0x1f;

    return (int_status & ~int_mask);
}

int bflb_i2s_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    switch (cmd) {
        case I2S_CMD_CLEAR_TX_FIFO:
            /* clear tx fifo */
            regval = getreg32(reg_base + I2S_FIFO_CONFIG_0_OFFSET);
            regval |= I2S_TX_FIFO_CLR;
            putreg32(regval, reg_base + I2S_FIFO_CONFIG_0_OFFSET);
            break;

        case I2S_CMD_CLEAR_RX_FIFO:
            /* clear rx fifo */
            regval = getreg32(reg_base + I2S_FIFO_CONFIG_0_OFFSET);
            regval |= I2S_RX_FIFO_CLR;
            putreg32(regval, reg_base + I2S_FIFO_CONFIG_0_OFFSET);
            break;

        case I2S_CMD_RX_DEGLITCH:
            /* set rx deglitch, arg: deglitch cycle count (unit: cycle of I2S kernel clock) */
            regval = getreg32(reg_base + I2S_IO_CONFIG_OFFSET);
            if (arg) {
                regval |= I2S_CR_DEG_EN;
                regval &= ~I2S_CR_DEG_CNT_MASK;
                regval |= (arg << I2S_CR_DEG_CNT_SHIFT) & I2S_CR_DEG_CNT_MASK;
            } else {
                regval &= ~I2S_CR_DEG_EN;
            }
            putreg32(regval, reg_base + I2S_IO_CONFIG_OFFSET);
            break;

        case I2S_CMD_DATA_ENABLE:
            /* data enable, arg: use @ref I2S_CMD_DATA_ENABLE_TYPE */
            regval = getreg32(reg_base + I2S_CONFIG_OFFSET);
            /* enable tx data signal */
            if (arg & I2S_CMD_DATA_ENABLE_TX) {
                regval |= I2S_CR_I2S_TXD_EN;
            } else {
                regval &= ~I2S_CR_I2S_TXD_EN;
            }
            /* enable rx data signal */
            if (arg & I2S_CMD_DATA_ENABLE_RX) {
                regval |= I2S_CR_I2S_RXD_EN;
            } else {
                regval &= ~I2S_CR_I2S_RXD_EN;
            }
            putreg32(regval, reg_base + I2S_CONFIG_OFFSET);
            break;

        case I2S_CMD_CHANNEL_LR_MERGE:
            /* Each FIFO entry contains both L/R channel data ,
            can only be enabled if data size is 8 or 16 bits,
            arg use true or false */
            regval = getreg32(reg_base + I2S_FIFO_CONFIG_0_OFFSET);
            if (arg) {
                regval |= I2S_CR_FIFO_LR_MERGE;
            } else {
                regval &= ~I2S_CR_FIFO_LR_MERGE;
            }
            putreg32(regval, reg_base + I2S_FIFO_CONFIG_0_OFFSET);
            break;

        case I2S_CMD_CHANNEL_LR_EXCHG:
            /* The position of L/R channel data within each entry is exchanged,
            can only be enabled if data size is 8 or 16 bits and I2S_CMD_CHANNEL_LR_MERGE is enabled,
            arg use true or false */
            regval = getreg32(reg_base + I2S_FIFO_CONFIG_0_OFFSET);
            if (arg) {
                regval |= I2S_CR_FIFO_LR_EXCHG;
            } else {
                regval &= ~I2S_CR_FIFO_LR_EXCHG;
            }
            putreg32(regval, reg_base + I2S_FIFO_CONFIG_0_OFFSET);
            break;

        case I2S_CMD_MUTE:
            /* Enable mute, arg use true or false */
            regval = getreg32(reg_base + I2S_CONFIG_OFFSET);
            if (arg) {
                regval |= I2S_CR_MUTE_MODE;
            } else {
                regval &= ~I2S_CR_MUTE_MODE;
            }
            putreg32(regval, reg_base + I2S_CONFIG_OFFSET);
            break;

        case I2S_CMD_BIT_REVERSE:
            /* Data endian (bit reverse), arg use true or false, true: MSB goes out first, false: LSB goes out first*/
            regval = getreg32(reg_base + I2S_CONFIG_OFFSET);
            if (arg) {
                regval |= I2S_CR_MUTE_MODE;
            } else {
                regval &= ~I2S_CR_MUTE_MODE;
            }
            putreg32(regval, reg_base + I2S_CONFIG_OFFSET);
            break;

        default:
            ret = -EPERM;
            break;
    }

    return ret;
}