#include "bflb_pwm_v2.h"
#include "bflb_clock.h"
#include "hardware/pwm_v2_reg.h"

void bflb_pwm_v2_init(struct bflb_device_s *dev, const struct bflb_pwm_v2_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;
    uint64_t start_time;

    reg_base = dev->reg_base;
    /* stop pwm */
    regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
    regval |= PWM_STOP_EN;
    putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);

    start_time = bflb_mtimer_get_time_ms();
    do {
        regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
        regval &= PWM_STS_STOP;
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return;
        }
    } while (regval == 0);

    /* config clock source and dividor */
    regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
    regval &= ~PWM_REG_CLK_SEL_MASK;
    if (config->clk_source == BFLB_SYSTEM_XCLK) {
        regval |= (0 << PWM_REG_CLK_SEL_SHIFT);
    } else if (config->clk_source == BFLB_SYSTEM_PBCLK) {
        regval |= (1 << PWM_REG_CLK_SEL_SHIFT);
    } else if (config->clk_source == BFLB_SYSTEM_32K_CLK) {
        regval |= (2 << PWM_REG_CLK_SEL_SHIFT);
    } else {
    }
    regval &= ~PWM_CLK_DIV_MASK;
    regval |= (uint32_t)config->clk_div << PWM_CLK_DIV_SHIFT;
    putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);

    /* config pwm period */
    regval = getreg32(reg_base + PWM_MC0_PERIOD_OFFSET);
    regval &= ~PWM_PERIOD_MASK;
    regval |= (uint32_t)config->period << PWM_PERIOD_SHIFT;
    putreg32(regval, reg_base + PWM_MC0_PERIOD_OFFSET);
}

void bflb_pwm_v2_deinit(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;
    uint64_t start_time;

    reg_base = dev->reg_base;
    /* stop pwm */
    regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
    regval |= PWM_STOP_EN;
    putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);

    start_time = bflb_mtimer_get_time_ms();
    do {
        regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
        regval &= PWM_STS_STOP;
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return;
        }
    } while (regval == 0);

    /* restore pwm_mc0_config0 register with default value */
    regval = PWM_STS_STOP | PWM_STOP_MODE | PWM_STOP_EN | PWM_ADC_TRG_SRC_MASK;
    putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);

    /* restore pwm_mc0_config1 register with default value */
    regval = PWM_CH3_NPL | PWM_CH3_PPL | PWM_CH2_NPL | PWM_CH2_PPL;
    regval |= PWM_CH1_NPL | PWM_CH1_PPL | PWM_CH0_NPL | PWM_CH0_PPL;
    regval |= PWM_CH3_NSI | PWM_CH2_NSI | PWM_CH1_NSI | PWM_CH0_NSI;
    putreg32(regval, reg_base + PWM_MC0_CONFIG1_OFFSET);

    /* restore pwm_mc0_period register with default value */
    putreg32(0, reg_base + PWM_MC0_PERIOD_OFFSET);

    /* restore pwm_mc0_dead_time register with default value */
    putreg32(0, reg_base + PWM_MC0_DEAD_TIME_OFFSET);

    /* restore pwm_mc0_chx_thre(x=0...3) register with default value */
    putreg32(0, reg_base + PWM_MC0_CH0_THRE_OFFSET);
    putreg32(1, reg_base + PWM_MC0_CH1_THRE_OFFSET);
    putreg32(2, reg_base + PWM_MC0_CH2_THRE_OFFSET);
    putreg32(3, reg_base + PWM_MC0_CH3_THRE_OFFSET);

    /* restore pwm_mc0_int_mask register with default value */
    putreg32(0xFFFFFFFF, reg_base + PWM_MC0_INT_MASK_OFFSET);
    /* clear all interrupt */
    putreg32(0xFFFFFFFF, reg_base + PWM_MC0_INT_CLEAR_OFFSET);
    /* restore pwm_mc0_int_en register with default value */
    putreg32(0xFFFFFFFF, reg_base + PWM_MC0_INT_EN_OFFSET);
}

void bflb_pwm_v2_set_period(struct bflb_device_s *dev, uint16_t period)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_MC0_PERIOD_OFFSET);
    regval &= ~PWM_PERIOD_MASK;
    regval |= (uint32_t)period << PWM_PERIOD_SHIFT;
    putreg32(regval, reg_base + PWM_MC0_PERIOD_OFFSET);
}

void bflb_pwm_v2_start(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;
    uint64_t start_time;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
    regval &= ~PWM_STOP_EN;
    putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);

    start_time = bflb_mtimer_get_time_ms();
    do {
        regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
        regval &= PWM_STS_STOP;
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return;
        }
    } while (regval != 0);
}

void bflb_pwm_v2_stop(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;
    uint64_t start_time;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
    regval |= PWM_STOP_EN;
    putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);

    start_time = bflb_mtimer_get_time_ms();
    do {
        regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
        regval &= PWM_STS_STOP;
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return;
        }
    } while (regval == 0);
}

float bflb_pwm_v2_get_frequency(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t tmp;
    float src, div, period;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
    /* get clock source frequency */
    tmp = (regval & PWM_REG_CLK_SEL_MASK) >> PWM_REG_CLK_SEL_SHIFT;
    switch (tmp) {
        case 0:
            src = (float)bflb_clk_get_system_clock(0); /* TODO: because this function has not been implemented */
            break;
        case 1:
            src = (float)bflb_clk_get_system_clock(1); /* TODO: because this function has not been implemented */
            break;
        case 2:
            src = (float)bflb_clk_get_system_clock(2); /* TODO: because this function has not been implemented */
            break;
        default:
            src = 0.0f;
            break;
    }
    /* get clock dividor */
    tmp = (regval & PWM_CLK_DIV_MASK) >> PWM_CLK_DIV_SHIFT;
    div = tmp ? (float)tmp : 1.0f;
    /* get pwm period count */
    regval = getreg32(reg_base + PWM_MC0_PERIOD_OFFSET);
    tmp = (regval & PWM_PERIOD_MASK) >> PWM_PERIOD_SHIFT;
    period = (float)tmp;
    /* calculate freaueny */
    return (src / div / period);
}

void bflb_pwm_v2_channel_init(struct bflb_device_s *dev, uint8_t ch, struct bflb_pwm_v2_channel_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_MC0_CONFIG1_OFFSET);
    if (config->positive_polarity == PWM_POLARITY_ACTIVE_LOW) {
        regval &= ~(PWM_CH0_PPL << ch * 2);
    } else {
        regval |= (PWM_CH0_PPL << ch * 2);
    }
    if (config->negative_polarity == PWM_POLARITY_ACTIVE_LOW) {
        regval &= ~(PWM_CH0_NPL << ch * 2);
    } else {
        regval |= (PWM_CH0_NPL << ch * 2);
    }
    if (config->positive_stop_state == PWM_STATE_ACTIVE) {
        regval |= (PWM_CH0_PSI << ch * 4);
    } else {
        regval &= ~(PWM_CH0_PSI << ch * 4);
    }
    if (config->negative_stop_state == PWM_STATE_INACTIVE) {
        regval &= ~(PWM_CH0_NSI << ch * 4);
    } else {
        regval |= (PWM_CH0_NSI << ch * 4);
    }
    if (config->positive_brake_state == PWM_STATE_ACTIVE) {
        regval |= (PWM_CH0_PBS << ch * 2);
    } else {
        regval &= ~(PWM_CH0_PBS << ch * 2);
    }
    if (config->negative_brake_state == PWM_STATE_ACTIVE) {
        regval |= (PWM_CH0_NBS << ch * 2);
    } else {
        regval &= ~(PWM_CH0_NBS << ch * 2);
    }
    putreg32(regval, reg_base + PWM_MC0_CONFIG1_OFFSET);
    regval = getreg32(reg_base + PWM_MC0_DEAD_TIME_OFFSET);
    regval &= ~(PWM_CH0_DTG_MASK << ch * 8);
    regval |= ((uint32_t)config->dead_time << ch * 8);
    putreg32(regval, reg_base + PWM_MC0_DEAD_TIME_OFFSET);
}

void bflb_pwm_v2_channel_set_threshold(struct bflb_device_s *dev, uint8_t ch, uint16_t low_threhold, uint16_t high_threhold)
{
    uint32_t regval;

    regval = ((uint32_t)high_threhold << 16) | low_threhold;
    putreg32(regval, dev->reg_base + PWM_MC0_CH0_THRE_OFFSET + ch * 4);
}

void bflb_pwm_v2_channel_positive_start(struct bflb_device_s *dev, uint8_t ch)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_MC0_CONFIG1_OFFSET);
    regval |= (PWM_CH0_PEN << 4 * ch);
    putreg32(regval, reg_base + PWM_MC0_CONFIG1_OFFSET);
}

void bflb_pwm_v2_channel_negative_start(struct bflb_device_s *dev, uint8_t ch)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_MC0_CONFIG1_OFFSET);
    regval |= (PWM_CH0_NEN << 4 * ch);
    putreg32(regval, reg_base + PWM_MC0_CONFIG1_OFFSET);
}

void bflb_pwm_v2_channel_positive_stop(struct bflb_device_s *dev, uint8_t ch)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_MC0_CONFIG1_OFFSET);
    regval &= ~(PWM_CH0_PEN << 4 * ch);
    putreg32(regval, reg_base + PWM_MC0_CONFIG1_OFFSET);
}

void bflb_pwm_v2_channel_negative_stop(struct bflb_device_s *dev, uint8_t ch)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_MC0_CONFIG1_OFFSET);
    regval &= ~(PWM_CH0_NEN << 4 * ch);
    putreg32(regval, reg_base + PWM_MC0_CONFIG1_OFFSET);
}

void bflb_pwm_v2_int_enable(struct bflb_device_s *dev, uint32_t int_en, bool enable)
{
    uint32_t reg_base;
    uint32_t regval_mask, regval_en;

    reg_base = dev->reg_base;
    regval_mask = getreg32(reg_base + PWM_MC0_INT_MASK_OFFSET);
    regval_en = getreg32(reg_base + PWM_MC0_INT_EN_OFFSET);
    if (enable) {
        regval_mask &= ~int_en;
        regval_en |= int_en;
    } else {
        regval_mask |= int_en;
        regval_en &= ~int_en;
    }
    putreg32(regval_mask, reg_base + PWM_MC0_INT_MASK_OFFSET);
    putreg32(regval_en, reg_base + PWM_MC0_INT_EN_OFFSET);
}

void bflb_pwm_v2_int_clear(struct bflb_device_s *dev, uint32_t int_clear)
{
    putreg32(int_clear, dev->reg_base + PWM_MC0_INT_CLEAR_OFFSET);
}

uint32_t bflb_pwm_v2_get_intstatus(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval_sts, regval_mask, regval_en;

    reg_base = dev->reg_base;
    regval_sts = getreg32(reg_base + PWM_MC0_INT_STS_OFFSET);
    regval_mask = getreg32(reg_base + PWM_MC0_INT_MASK_OFFSET);
    regval_en = getreg32(reg_base + PWM_MC0_INT_EN_OFFSET);
    return (regval_sts & ~regval_mask & regval_en);
}

int bflb_pwm_v2_feature_control(struct bflb_device_s *dev, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    switch (cmd) {
        case PWM_CMD_SET_EXT_BRAKE_POLARITY:
            regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
            if (arg == PWM_POLARITY_ACTIVE_HIGH) {
                regval |= PWM_EXT_BREAK_PL;
            } else {
                regval &= ~PWM_EXT_BREAK_PL;
            }
            putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);
            break;

        case PWM_CMD_SET_EXT_BRAKE_ENABLE:
            regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
            if (arg == true) {
                regval |= PWM_EXT_BREAK_EN;
            } else {
                regval &= ~PWM_EXT_BREAK_EN;
            }
            putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);
            break;

        case PWM_CMD_SET_SW_BRAKE_ENABLE:
            regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
            if (arg == true) {
                regval |= PWM_SW_BREAK_EN;
            } else {
                regval &= ~PWM_SW_BREAK_EN;
            }
            putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);
            break;

        case PWM_CMD_SET_STOP_ON_REPT:
            regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
            if (arg == true) {
                regval |= PWM_STOP_ON_REPT;
            } else {
                regval &= ~PWM_STOP_ON_REPT;
            }
            putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);
            break;

        case PWM_CMD_SET_REPT_COUNT:
            regval = getreg32(reg_base + PWM_MC0_PERIOD_OFFSET);
            regval &= ~(PWM_INT_PERIOD_CNT_MASK);
            regval |= (arg << PWM_INT_PERIOD_CNT_SHIFT);
            putreg32(regval, reg_base + PWM_MC0_PERIOD_OFFSET);
            break;

        case PWM_CMD_SET_TRIG_ADC_SRC:
            regval = getreg32(reg_base + PWM_MC0_CONFIG0_OFFSET);
            regval &= ~(PWM_ADC_TRG_SRC_MASK);
            regval |= (arg << PWM_ADC_TRG_SRC_SHIFT);
            putreg32(regval, reg_base + PWM_MC0_CONFIG0_OFFSET);
            break;

        default:
            ret = -EPERM;
            break;
    }
    return ret;
}
