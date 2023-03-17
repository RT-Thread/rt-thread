#include "bflb_auadc.h"
#include "hardware/auadc_reg.h"

int bflb_auadc_init(struct bflb_device_s *dev, const struct bflb_auadc_init_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + AUADC_AUDPDM_TOP_OFFSET);
    /* enable clk */
    regval |= AUADC_AUDIO_CKG_EN;
    /* sampling rate */
    regval &= ~AUADC_ADC_RATE_MASK;
    regval |= config->sampling_rate << AUADC_ADC_RATE_SHIFT;
    putreg32(regval, reg_base + AUADC_AUDPDM_TOP_OFFSET);

    /* disable ch0 and enable dma interface */
    regval = getreg32(reg_base + AUADC_AUDPDM_ITF_OFFSET);
    regval &= ~AUADC_ADC_0_EN;
    regval |= AUADC_ADC_ITF_EN;
    putreg32(regval, reg_base + AUADC_AUDPDM_ITF_OFFSET);

    /* pdm or adc input */
    regval = getreg32(reg_base + AUADC_PDM_DAC_0_OFFSET);
    if (config->input_mode == AUADC_INPUT_MODE_ADC) {
        regval &= ~AUADC_ADC_0_SRC;
    } else {
        regval |= AUADC_ADC_0_SRC;
    }
    putreg32(regval, reg_base + AUADC_PDM_DAC_0_OFFSET);

    /* pdm cfg */
    regval = getreg32(reg_base + AUADC_PDM_PDM_0_OFFSET);
    if (config->input_mode == AUADC_INPUT_MODE_PDM_L || config->input_mode == AUADC_INPUT_MODE_PDM_R) {
        /* enable pdm */
        regval |= AUADC_PDM_0_EN;
        /* pdm_l or pdm_r input */
        regval &= ~AUADC_ADC_0_PDM_SEL_MASK;
        if (config->input_mode == AUADC_INPUT_MODE_PDM_L) {
            regval |= 0 << AUADC_ADC_0_PDM_SEL_SHIFT;
        } else if (config->input_mode == AUADC_INPUT_MODE_PDM_R) {
            regval |= 1 << AUADC_ADC_0_PDM_SEL_SHIFT;
        }
    } else {
        /* disable pdm */
        regval &= ~AUADC_PDM_0_EN;
    }
    putreg32(regval, reg_base + AUADC_PDM_PDM_0_OFFSET);

    regval = getreg32(reg_base + AUADC_AUDADC_CMD_OFFSET);
    /* audio osr configuration */
    if (config->input_mode != AUADC_INPUT_MODE_ADC && (config->sampling_rate == AUADC_SAMPLING_RATE_32K || config->sampling_rate == AUADC_SAMPLING_RATE_48K)) {
        /* osr 64 */
        regval |= AUADC_AUDADC_AUDIO_OSR_SEL;
    } else {
        /* osr 128 */
        regval &= ~AUADC_AUDADC_AUDIO_OSR_SEL;
    }
    putreg32(regval, reg_base + AUADC_AUDADC_CMD_OFFSET);

    /* fifo configuration */
    regval = getreg32(reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
    /* data format */
    regval &= ~AUADC_RX_DATA_MODE_MASK;
    regval |= config->data_format << AUADC_RX_DATA_MODE_SHIFT;

    /* fifo threshold */
    regval &= ~AUADC_RX_TRG_LEVEL_MASK;
    regval |= config->fifo_threshold << AUADC_RX_TRG_LEVEL_SHIFT;
    regval &= ~AUADC_RX_DRQ_CNT_MASK;

    /* disable record */
    regval &= ~AUADC_RX_CH_EN;

    /* 24bit sample */
    regval &= ~AUADC_RX_DATA_RES_MASK;
    regval |= 2 << AUADC_RX_DATA_RES_SHIFT;

    /* disable fifo dma and int */
    regval &= ~AUADC_RX_DRQ_EN;
    regval &= ~AUADC_RXA_INT_EN;
    regval &= ~AUADC_RXU_INT_EN;
    regval &= ~AUADC_RXO_INT_EN;

    /* clear fifo */
    regval |= AUADC_RX_FIFO_FLUSH;
    putreg32(regval, reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);

    /* enable ch0 */
    regval = getreg32(reg_base + AUADC_AUDPDM_ITF_OFFSET);
    regval |= AUADC_ADC_0_EN;
    putreg32(regval, reg_base + AUADC_AUDPDM_ITF_OFFSET);

    return 0;
}

int bflb_auadc_adc_init(struct bflb_device_s *dev, const struct bflb_auadc_adc_init_config_s *adc_analog_cfg)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    if (adc_analog_cfg->auadc_analog_en == false) {
        /* disable analog and channel */
        regval = getreg32(reg_base + AUADC_AUDADC_CMD_OFFSET);
        regval &= ~AUADC_AUDADC_PGA_PU;
        regval &= ~AUADC_AUDADC_SDM_PU;
        regval &= ~AUADC_AUDADC_CHANNEL_EN_MASK;
        putreg32(regval, reg_base + AUADC_AUDADC_CMD_OFFSET);
        return 0;
    }

    /* power up, and SDM reset */
    regval = getreg32(reg_base + AUADC_AUDADC_CMD_OFFSET);
    regval |= AUADC_AUDADC_PGA_PU;
    regval |= AUADC_AUDADC_SDM_PU;
    regval &= ~AUADC_AUDADC_CONV;
    putreg32(regval, reg_base + AUADC_AUDADC_CMD_OFFSET);

    /* select analog channel */
    regval &= ~AUADC_AUDADC_CHANNEL_SELP_MASK;
    regval &= ~AUADC_AUDADC_CHANNEL_SELN_MASK;
    regval |= adc_analog_cfg->adc_pga_posi_ch << AUADC_AUDADC_CHANNEL_SELP_SHIFT;
    regval |= adc_analog_cfg->adc_pga_nega_ch << AUADC_AUDADC_CHANNEL_SELN_SHIFT;

    /* PGA mode */
    regval &= ~AUADC_AUDADC_PGA_MODE_MASK;
    regval |= adc_analog_cfg->adc_pga_mode << AUADC_AUDADC_PGA_MODE_SHIFT;

    /* PGA gain */
    regval &= ~AUADC_AUDADC_PGA_GAIN_MASK;
    regval |= (adc_analog_cfg->adc_pga_gain / 3) << AUADC_AUDADC_PGA_GAIN_SHIFT;

    /* adc mode */
    if (adc_analog_cfg->adc_mode == AUADC_ADC_MODE_AUDIO) {
        regval &= ~AUADC_AUDADC_MEAS_FILTER_EN;
    } else {
        regval |= AUADC_AUDADC_MEAS_FILTER_EN;
    }

    /* measuring mode rate */
    regval &= ~AUADC_AUDADC_MEAS_ODR_SEL_MASK;
    regval |= adc_analog_cfg->adc_measure_rate << AUADC_AUDADC_MEAS_ODR_SEL_SHIFT;

    /* enable analog channel */
    regval &= ~AUADC_AUDADC_CHANNEL_EN_MASK;
    if (adc_analog_cfg->adc_pga_mode == AUADC_ADC_PGA_MODE_AC_DIFFER || adc_analog_cfg->adc_pga_mode == AUADC_ADC_PGA_MODE_DC_DIFFER) {
        regval |= 0x03 << AUADC_AUDADC_CHANNEL_EN_SHIFT;
    } else {
        regval |= 0x02 << AUADC_AUDADC_CHANNEL_EN_SHIFT;
    }
    putreg32(regval, reg_base + AUADC_AUDADC_CMD_OFFSET);

    /* SDM conversion start */
    regval |= AUADC_AUDADC_CONV;
    putreg32(regval, reg_base + AUADC_AUDADC_CMD_OFFSET);

    return 0;
}

int bflb_auadc_link_rxdma(struct bflb_device_s *dev, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
    if (enable) {
        regval |= AUADC_RX_DRQ_EN;
    } else {
        regval &= ~AUADC_RX_DRQ_EN;
    }
    putreg32(regval, reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);

    return 0;
}

int bflb_auadc_int_mask(struct bflb_device_s *dev, uint32_t int_sts)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    /* fifo int */
    regval = getreg32(reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
    regval &= ~int_sts;
    putreg32(regval, reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);

    return 0;
}

int bflb_auadc_int_unmask(struct bflb_device_s *dev, uint32_t int_sts)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    /* fifo int */
    regval = getreg32(reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
    regval |= int_sts;
    putreg32(regval, reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);

    return 0;
}

int bflb_auadc_get_intstatus(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;
    int32_t int_sts;

    reg_base = dev->reg_base;
    int_sts = 0;

    regval = getreg32(reg_base + AUADC_AUDADC_RX_FIFO_STATUS_OFFSET);
    if (regval & AUADC_RXO_INT) {
        int_sts |= AUADC_INTSTS_FIFO_OVER;
    }
    if (regval & AUADC_RXU_INT) {
        int_sts |= AUADC_INTSTS_FIFO_UNDER;
    }
    if (regval & AUADC_RXA_INT) {
        int_sts |= AUADC_INTSTS_FIFO_AVAILABLE;
    }

    return int_sts;
}

int bflb_auadc_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t reg_base;
    uint32_t regval;
    int16_t volume_val;

    reg_base = dev->reg_base;

    switch (cmd) {
        case AUADC_CMD_RECORD_START:
            /* record start */
            regval = getreg32(reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
            regval |= AUADC_RX_CH_EN;
            putreg32(regval, reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
            break;

        case AUADC_CMD_RECORD_STOP:
            /* record stop */
            regval = getreg32(reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
            regval &= ~AUADC_RX_CH_EN;
            putreg32(regval, reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
            break;

        case AUADC_CMD_SET_VOLUME_VAL:
            /* set volume value dB, arg range -191 to + 36, 0.5dB step, range -95.5dB to +18dB*/
            volume_val = (uint16_t)((int16_t)arg * 2);
            regval = getreg32(reg_base + AUADC_PDM_ADC_S0_OFFSET);
            regval &= ~AUADC_ADC_S0_VOLUME_MASK;
            regval |= (volume_val << AUADC_ADC_S0_VOLUME_SHIFT) & AUADC_ADC_S0_VOLUME_MASK;
            putreg32(regval, reg_base + AUADC_PDM_ADC_S0_OFFSET);
            break;

        case AUADC_CMD_SET_PGA_GAIN_VAL:
            /* set adc pga gain, range 6dB ~ 42dB, step by 3db */
            volume_val = arg / 3;
            regval = getreg32(reg_base + AUADC_AUDADC_CMD_OFFSET);
            regval &= ~AUADC_AUDADC_PGA_GAIN_MASK;
            regval |= (volume_val << AUADC_AUDADC_PGA_GAIN_SHIFT) & AUADC_AUDADC_PGA_GAIN_MASK;
            putreg32(regval, reg_base + AUADC_AUDADC_CMD_OFFSET);
            break;

        case AUADC_CMD_CLEAR_RX_FIFO:
            /* get rx fifo cnt */
            regval = getreg32(reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
            regval |= AUADC_RX_FIFO_FLUSH;
            putreg32(regval, reg_base + AUADC_AUDADC_RX_FIFO_CTRL_OFFSET);
            break;

        case AUADC_CMD_GET_RX_FIFO_CNT:
            /* get rx fifo cnt */
            regval = getreg32(reg_base + AUADC_AUDADC_RX_FIFO_STATUS_OFFSET);
            ret = (regval & AUADC_RXA_CNT_MASK) >> AUADC_RXA_CNT_SHIFT;
    }

    return ret;
}