#include "bflb_audac.h"
#include "hardware/audac_reg.h"
#include "hardware/dac_reg.h"

#if defined(BL616) || defined(BL606P) || defined(BL808) || defined(BL628)
#define GLB_BASE ((uint32_t)0x20000000)
#endif

static volatile uint32_t g_audac_channel_mode = 0;

int bflb_audac_init(struct bflb_device_s *dev, const struct bflb_audac_init_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    /* enable clk, enable dma interface, disable ch0 */
    regval = getreg32(reg_base + AUDAC_0_OFFSET);
    regval |= AUDAC_CKG_ENA;
    regval |= AUDAC_DAC_ITF_EN;
    regval |= AUDAC_DAC_0_EN;

    /* set output mode and sampling rate */
    regval &= ~AUDAC_AU_PWM_MODE_MASK;
    if (config->output_mode != AUDAC_OUTPUT_MODE_PWM) {
        regval |= (config->sampling_rate + 8) << AUDAC_AU_PWM_MODE_SHIFT;
    } else {
        regval |= config->sampling_rate << AUDAC_AU_PWM_MODE_SHIFT;
    }
    putreg32(regval, reg_base + AUDAC_0_OFFSET);

    regval = getreg32(reg_base + AUDAC_1_OFFSET);
    /* set dsm dither, scaling, and order */
    regval &= ~AUDAC_DAC_DSM_SCALING_MODE_MASK;
    regval |= 3 << AUDAC_DAC_DSM_SCALING_MODE_SHIFT;
    regval &= ~AUDAC_DAC_DSM_ORDER_MASK;
    regval |= 1 << AUDAC_DAC_DSM_ORDER_SHIFT;

    /* set mixer */
    regval &= ~AUDAC_DAC_MIX_SEL_MASK;
    if (config->source_channels_num == AUDAC_SOURCE_CHANNEL_DUAL) {
        regval |= config->mixer_mode << AUDAC_DAC_MIX_SEL_SHIFT;
    }
    putreg32(regval, reg_base + AUDAC_1_OFFSET);

    regval = getreg32(reg_base + AUDAC_FIFO_CTRL_OFFSET);
    /* data format */
    regval &= ~AUDAC_TX_DATA_MODE_MASK;
    regval |= config->data_format;

    /* fifo threshold */
    regval &= ~AUDAC_TX_TRG_LEVEL_MASK;
    regval |= (config->fifo_threshold << AUDAC_TX_TRG_LEVEL_SHIFT) & AUDAC_TX_TRG_LEVEL_MASK;
    regval &= ~AUDAC_TX_DRQ_CNT_MASK;

    /* dma disable */
    regval &= ~AUDAC_TX_DRQ_EN;

    /* source channels num */
    regval &= ~AUDAC_TX_CH_EN_MASK;
    g_audac_channel_mode = config->source_channels_num;

    /* disable fifo int */
    regval &= ~AUDAC_TXO_INT_EN;
    regval &= ~AUDAC_TXU_INT_EN;
    regval &= ~AUDAC_TXA_INT_EN;

    /* clear fifo */
    regval &= ~AUDAC_TX_FIFO_FLUSH;
    putreg32(regval, reg_base + AUDAC_FIFO_CTRL_OFFSET);

    /* enable zero delete */
    regval = getreg32(reg_base + AUDAC_ZD_0_OFFSET);
    regval |= AUDAC_ZD_EN;
    regval &= ~AUDAC_ZD_TIME_MASK;
    regval |= 512 << AUDAC_ZD_TIME_SHIFT;
    putreg32(regval, reg_base + AUDAC_ZD_0_OFFSET);

    /* disable volume interrupt */
    regval = getreg32(reg_base + AUDAC_STATUS_OFFSET);
    regval |= AUDAC_DAC_S0_INT_CLR;
    putreg32(regval, reg_base + AUDAC_STATUS_OFFSET);

    /* gpdac config */
    reg_base = GLB_BASE;
    if (config->output_mode != AUDAC_OUTPUT_MODE_PWM) {
        /* Select Internal reference */
        regval = getreg32(reg_base + GLB_GPDAC_CTRL_OFFSET);
        regval |= (GLB_GPDACA_RSTN_ANA | GLB_GPDACB_RSTN_ANA);
        regval = getreg32(reg_base + GLB_GPDAC_CTRL_OFFSET);
        regval &= ~GLB_GPDAC_REF_SEL;

        /* Select the clock and data from aupdac */
        regval |= GLB_GPDAC_ANA_CLK_SEL;
        if (config->output_mode & AUDAC_OUTPUT_MODE_GPDAC_CH_A) {
            regval |= GLB_GPDAC_DAT_CHA_SEL;
        }
        if (config->output_mode & AUDAC_OUTPUT_MODE_GPDAC_CH_B) {
            regval |= GLB_GPDAC_DAT_CHB_SEL;
        }
        putreg32(regval, reg_base + GLB_GPDAC_CTRL_OFFSET);

        if (config->output_mode & AUDAC_OUTPUT_MODE_GPDAC_CH_A) {
            /* gpdac enable ch-A */
            regval = getreg32(reg_base + GLB_GPDAC_ACTRL_OFFSET);
            regval |= (GLB_GPDAC_A_EN | GLB_GPDAC_IOA_EN);
            putreg32(regval, reg_base + GLB_GPDAC_ACTRL_OFFSET);
        }

        if (config->output_mode & AUDAC_OUTPUT_MODE_GPDAC_CH_B) {
            /* gpdac enable ch-A */
            regval = getreg32(reg_base + GLB_GPDAC_BCTRL_OFFSET);
            regval |= (GLB_GPDAC_B_EN | GLB_GPDAC_IOB_EN);
            putreg32(regval, reg_base + GLB_GPDAC_BCTRL_OFFSET);
        }
    }

    return 0;
}

int bflb_audac_volume_init(struct bflb_device_s *dev, const struct bflb_audac_volume_config_s *vol_cfg)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    /* enable volume update */
    regval = getreg32(reg_base + AUDAC_S0_OFFSET);
    regval |= AUDAC_DAC_S0_VOLUME_UPDATE;

    if (vol_cfg->mute_ramp_en) {
        /* mute ramp mode */
        regval |= AUDAC_DAC_S0_MUTE_SOFTMODE;
        regval &= ~AUDAC_DAC_S0_MUTE_RMPDN_RATE_MASK;
        regval |= vol_cfg->mute_down_ramp_rate << AUDAC_DAC_S0_MUTE_RMPDN_RATE_SHIFT;
        regval &= ~AUDAC_DAC_S0_MUTE_RMPUP_RATE_MASK;
        regval |= vol_cfg->mute_up_ramp_rate << AUDAC_DAC_S0_MUTE_RMPUP_RATE_SHIFT;

    } else {
        /* mute directly mode */
        regval &= ~AUDAC_DAC_S0_MUTE_SOFTMODE;
    }

    regval &= ~AUDAC_DAC_S0_CTRL_MODE_MASK;
    if (vol_cfg->volume_update_mode == AUDAC_VOLUME_UPDATE_MODE_RAMP) {
        /* ramp mode */
        regval |= 2 << AUDAC_DAC_S0_CTRL_MODE_SHIFT;
        regval &= ~AUDAC_DAC_S0_CTRL_RMP_RATE_MASK;
        regval |= vol_cfg->volume_ramp_rate << AUDAC_DAC_S0_CTRL_RMP_RATE_SHIFT;
    } else if (vol_cfg->volume_update_mode == AUDAC_VOLUME_UPDATE_MODE_RAMP_ZERO_CROSSING) {
        /* ramp and zero crossing mode */
        regval |= 1 << AUDAC_DAC_S0_CTRL_MODE_SHIFT;
        regval &= ~AUDAC_DAC_S0_CTRL_ZCD_RATE_MASK;
        regval |= vol_cfg->volume_ramp_rate << AUDAC_DAC_S0_CTRL_ZCD_RATE_SHIFT;
    }
    putreg32(regval, reg_base + AUDAC_S0_OFFSET);

    return 0;
}

int bflb_audac_link_rxdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + AUDAC_FIFO_CTRL_OFFSET);
    if (enable) {
        regval |= AUDAC_TX_DRQ_EN;
    } else {
        regval &= ~AUDAC_TX_DRQ_EN;
    }
    putreg32(regval, reg_base + AUDAC_FIFO_CTRL_OFFSET);

    return 0;
}

int bflb_audac_int_mask(struct bflb_device_s *dev, uint32_t int_sts)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    if (int_sts & AUDAC_INTSTS_VOLUME_RAMP) {
        /* volume ramp done int */
        regval = getreg32(reg_base + AUDAC_0_OFFSET);
        regval &= ~(0x01 << 17);
        putreg32(regval, reg_base + AUDAC_0_OFFSET);

        int_sts &= ~AUDAC_INTSTS_VOLUME_RAMP;
    }

    if (int_sts) {
        /* fifo int */
        regval = getreg32(reg_base + AUDAC_FIFO_CTRL_OFFSET);
        regval &= ~int_sts;
        putreg32(regval, reg_base + AUDAC_FIFO_CTRL_OFFSET);
    }

    return 0;
}

int bflb_audac_int_unmask(struct bflb_device_s *dev, uint32_t int_sts)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    if (int_sts & AUDAC_INTSTS_VOLUME_RAMP) {
        /* volume ramp done int */
        regval = getreg32(reg_base + AUDAC_0_OFFSET);
        regval |= (0x01 << 17);
        putreg32(regval, reg_base + AUDAC_0_OFFSET);

        int_sts &= ~AUDAC_INTSTS_VOLUME_RAMP;
    }

    if (int_sts) {
        /* fifo int */
        regval = getreg32(reg_base + AUDAC_FIFO_CTRL_OFFSET);
        regval |= int_sts;
        putreg32(regval, reg_base + AUDAC_FIFO_CTRL_OFFSET);
    }

    return 0;
}

int bflb_audac_get_intstatus(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;
    int32_t int_sts;

    reg_base = dev->reg_base;
    int_sts = 0;

    /* volume ramp done int */
    regval = getreg32(reg_base + AUDAC_0_OFFSET);
    if (regval & (0x01 << 17)) {
        int_sts |= AUDAC_INTSTS_VOLUME_RAMP;
    }

    /* fifo int */
    regval = getreg32(reg_base + AUDAC_FIFO_STATUS_OFFSET);
    if (regval & AUDAC_TXO_INT) {
        int_sts |= AUDAC_INTSTS_FIFO_OVER;
    }
    if (regval & AUDAC_TXU_INT) {
        int_sts |= AUDAC_INTSTS_FIFO_UNDER;
    }
    if (regval & AUDAC_TXA_INT) {
        int_sts |= AUDAC_INTSTS_FIFO_AVAILABLE;
    }

    return int_sts;
}

int bflb_audac_int_clear(struct bflb_device_s *dev, uint32_t int_clear)
{
    uint32_t reg_base;
    uint32_t regval;
    uint8_t ramp_int_en;

    reg_base = dev->reg_base;

    if (int_clear & AUDAC_INTSTS_VOLUME_RAMP) {
        /* volume ramp done int */
        regval = getreg32(reg_base + AUDAC_0_OFFSET);

        if (regval & (0x01 << 17)) {
            ramp_int_en = 0;
        } else {
            ramp_int_en = 1;
        }

        regval |= (0x01 << 17);
        putreg32(regval, reg_base + AUDAC_0_OFFSET);

        if (ramp_int_en) {
            regval &= ~(0x01 << 17);
        }
        putreg32(regval, reg_base + AUDAC_0_OFFSET);
    }

    return 0;
}

int bflb_audac_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t reg_base;
    uint32_t regval;
    int16_t volume_val;

    reg_base = dev->reg_base;

    switch (cmd) {
        case AUDAC_CMD_PLAY_START:
            /* play start */
            regval = getreg32(reg_base + AUDAC_FIFO_CTRL_OFFSET);
            regval &= ~AUDAC_TX_CH_EN_MASK;
            regval |= g_audac_channel_mode << AUDAC_TX_CH_EN_SHIFT;
            putreg32(regval, reg_base + AUDAC_FIFO_CTRL_OFFSET);
            g_audac_channel_mode = 0;
            break;

        case AUDAC_CMD_PLAY_STOP:
            /* play stop */
            regval = getreg32(reg_base + AUDAC_FIFO_CTRL_OFFSET);
            if (g_audac_channel_mode == 0) {
                g_audac_channel_mode = (regval & AUDAC_TX_CH_EN_MASK) >> AUDAC_TX_CH_EN_SHIFT;
            }
            regval &= ~AUDAC_TX_CH_EN_MASK;
            putreg32(regval, reg_base + AUDAC_FIFO_CTRL_OFFSET);
            break;

        case AUDAC_CMD_SET_MUTE:
            /* set mute, arg use true or false */
            regval = getreg32(reg_base + AUDAC_S0_OFFSET);
            if (arg) {
                regval |= AUDAC_DAC_S0_MUTE;
            } else {
                regval &= ~AUDAC_DAC_S0_MUTE;
            }
            putreg32(regval, reg_base + AUDAC_S0_OFFSET);
            break;

        case AUDAC_CMD_SET_VOLUME_VAL:
            /* set volume value dB, arg range -191 to + 36, 0.5dB step, range -95.5dB to +18dB*/
            volume_val = (uint16_t)((int16_t)arg * 2);
            regval = getreg32(reg_base + AUDAC_S0_OFFSET);
            regval &= ~AUDAC_DAC_S0_VOLUME_MASK;
            regval |= (volume_val << AUDAC_DAC_S0_VOLUME_SHIFT) & AUDAC_DAC_S0_VOLUME_MASK;
            putreg32(regval, reg_base + AUDAC_S0_OFFSET);
            break;

        case AUDAC_CMD_CLEAR_TX_FIFO:
            /* get tx fifo cnt */
            regval = getreg32(reg_base + AUDAC_FIFO_CTRL_OFFSET);
            regval |= AUDAC_TX_FIFO_FLUSH;
            putreg32(regval, reg_base + AUDAC_FIFO_CTRL_OFFSET);
            break;

        case AUDAC_CMD_GET_TX_FIFO_CNT:
            /* get tx fifo cnt */
            regval = getreg32(reg_base + AUDAC_FIFO_STATUS_OFFSET);
            ret = (regval & AUDAC_TXA_CNT_MASK) >> AUDAC_TXA_CNT_SHIFT;
            break;

        default:
            break;
    }

    return ret;
}