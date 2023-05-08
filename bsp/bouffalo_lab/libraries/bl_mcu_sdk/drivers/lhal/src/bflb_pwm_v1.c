#include "bflb_pwm_v1.h"
#include "bflb_clock.h"
#include "hardware/pwm_v1_reg.h"

void bflb_pwm_v1_channel_init(struct bflb_device_s *dev, uint8_t ch, const struct bflb_pwm_v1_channel_config_s *config)
{
    uint32_t reg_base;
    uint32_t regval;
    uint64_t start_time;

    reg_base = dev->reg_base;
    /* stop pwm */
    regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
    regval |= PWM_STOP_EN;
    putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);

    start_time = bflb_mtimer_get_time_ms();
    do {
        regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
        regval &= PWM_STS_TOP;
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return;
        }
    } while (regval == 0);

    /* config clock source and dividor */
    regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
    regval &= ~PWM_REG_CLK_SEL_MASK;
    if (config->clk_source == BFLB_SYSTEM_XCLK) {
        regval |= (0 << PWM_REG_CLK_SEL_SHIFT);
    } else if (config->clk_source == BFLB_SYSTEM_PBCLK) {
        regval |= (1 << PWM_REG_CLK_SEL_SHIFT);
    } else if (config->clk_source == BFLB_SYSTEM_32K_CLK) {
        regval |= (2 << PWM_REG_CLK_SEL_SHIFT);
    } else {
    }
    putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);

    regval = getreg32(reg_base + PWM0_CLKDIV_OFFSET + ch * 0x20);
    regval &= ~PWM_CLK_DIV_MASK;
    regval |= (uint32_t)config->clk_div << PWM_CLK_DIV_SHIFT;
    putreg32(regval, reg_base + PWM0_CLKDIV_OFFSET + ch * 0x20);

    /* config pwm period */
    regval = getreg32(reg_base + PWM0_PERIOD_OFFSET + ch * 0x20);
    regval &= ~PWM_PERIOD_MASK;
    regval |= (uint32_t)config->period << PWM_PERIOD_SHIFT;
    putreg32(regval, reg_base + PWM0_PERIOD_OFFSET + ch * 0x20);
}

void bflb_pwm_v1_channel_deinit(struct bflb_device_s *dev, uint8_t ch)
{
    uint32_t reg_base;
    uint32_t regval;
    uint64_t start_time;

    reg_base = dev->reg_base;
    /* stop pwmx */
    regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
    regval |= PWM_STOP_EN;
    putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);

    start_time = bflb_mtimer_get_time_ms();
    do {
        regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
        regval &= PWM_STS_TOP;
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return;
        }
    } while (regval == 0);

    /* restore pwmx_clkdiv register with default value */
    putreg32(0, reg_base + PWM0_CLKDIV_OFFSET + ch * 0x20);

    /* restore pwmx_thre1 register with default value */
    putreg32(0, reg_base + PWM0_THRE1_OFFSET + ch * 0x20);

    /* restore pwmx_thre2 register with default value */
    putreg32(0, reg_base + PWM0_THRE2_OFFSET + ch * 0x20);

    /* restore pwmx_period register with default value */
    putreg32(0, reg_base + PWM0_PERIOD_OFFSET + ch * 0x20);

    /* restore pwmx_config register with default value */
    regval = PWM_STOP_MODE;
    putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);

    /* restore pwmx_interrupt register with default value */
    putreg32(0, reg_base + PWM0_INTERRUPT_OFFSET + ch * 0x20);

    /* clear all interrupt */
    putreg32(0xFFFFFFFF, reg_base + PWM_INT_CONFIG_OFFSET);
}

void bflb_pwm_v1_start(struct bflb_device_s *dev, uint8_t ch)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t start_time;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
    regval &= ~PWM_STOP_EN;
    putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);

    start_time = bflb_mtimer_get_time_ms();
    do {
        regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
        regval &= PWM_STS_TOP;
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return;
        }
    } while (regval != 0);
}

void bflb_pwm_v1_stop(struct bflb_device_s *dev, uint8_t ch)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t start_time;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
    regval |= PWM_STOP_EN;
    putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);

    start_time = bflb_mtimer_get_time_ms();
    do {
        regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
        regval &= PWM_STS_TOP;
        if ((bflb_mtimer_get_time_ms() - start_time) > 100) {
            return;
        }
    } while (regval == 0);
}

void bflb_pwm_v1_set_period(struct bflb_device_s *dev, uint8_t ch, uint16_t period)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + PWM0_PERIOD_OFFSET + ch * 0x20);
    regval &= ~PWM_PERIOD_MASK;
    regval |= (uint32_t)period << PWM_PERIOD_SHIFT;
    putreg32(regval, reg_base + PWM0_PERIOD_OFFSET + ch * 0x20);
}

void bflb_pwm_v1_channel_set_threshold(struct bflb_device_s *dev, uint8_t ch, uint16_t low_threhold, uint16_t high_threhold)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + PWM0_THRE1_OFFSET + ch * 0x20);
    regval &= ~PWM_THRE1_MASK;
    regval |= low_threhold;
    putreg32(regval, reg_base + PWM0_THRE1_OFFSET + ch * 0x20);

    regval = getreg32(reg_base + PWM0_THRE2_OFFSET + ch * 0x20);
    regval &= ~PWM_THRE2_MASK;
    regval |= high_threhold;
    putreg32(regval, reg_base + PWM0_THRE2_OFFSET + ch * 0x20);
}

void bflb_pwm_v1_int_enable(struct bflb_device_s *dev, uint8_t ch, bool enable)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM0_INTERRUPT_OFFSET + ch * 0x20);
    if (enable) {
        regval |= PWM_INT_ENABLE;
    } else {
        regval &= ~PWM_INT_ENABLE;
    }
    putreg32(regval, reg_base + PWM0_INTERRUPT_OFFSET + ch * 0x20);
}

uint32_t bflb_pwm_v1_get_intstatus(struct bflb_device_s *dev)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;

    regval = getreg32(reg_base + PWM_INT_CONFIG_OFFSET);
    return (regval);
}

void bflb_pwm_v1_int_clear(struct bflb_device_s *dev, uint32_t int_clear)
{
    uint32_t reg_base;
    uint32_t regval;
    uint32_t timeout_count = 160 * 1000;

    reg_base = dev->reg_base;
    regval = getreg32(reg_base + PWM_INT_CONFIG_OFFSET);
    regval |= int_clear;
    putreg32(regval, dev->reg_base + PWM_INT_CONFIG_OFFSET);
    do {
        regval = getreg32(reg_base + PWM_INT_CONFIG_OFFSET);
        timeout_count--;
        if (timeout_count == 0) {
            break;
        }
    } while (regval & (int_clear >> PWM_INT_CLEAR_SHIFT));

    regval &= ~int_clear;
    putreg32(regval, dev->reg_base + PWM_INT_CONFIG_OFFSET);
}

int bflb_pwm_v1_feature_control(struct bflb_device_s *dev, uint8_t ch, int cmd, size_t arg)
{
    int ret = 0;
    uint32_t reg_base;
    uint32_t regval;

    reg_base = dev->reg_base;
    switch (cmd) {
        case PWM_CMD_SET_STOP_MODE:
            regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
            if (arg == PWM_STOP_MODE_ABRUPT) {
                regval &= ~PWM_STOP_MODE;
            } else {
                regval |= PWM_STOP_MODE;
            }
            putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
            break;

        case PWM_CMD_SET_OUT_INVERT:
            regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
            if (arg) {
                regval |= PWM_OUT_INV;
            } else {
                regval &= ~PWM_OUT_INV;
            }
            putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
            break;

        case PWM_CMD_SET_SW_MODE:
            regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
            if (arg) {
                regval |= PWM_SW_MODE;
            } else {
                regval &= ~PWM_SW_MODE;
            }
            putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
            break;

        case PWM_CMD_SET_SW_FORCE_VALUE:
            regval = getreg32(reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
            if (arg) {
                regval |= PWM_SW_FORCE_VAL;
            } else {
                regval &= ~PWM_SW_FORCE_VAL;
            }
            putreg32(regval, reg_base + PWM0_CONFIG_OFFSET + ch * 0x20);
            break;

        case PWM_CMD_SET_REPT_COUNT:
            regval = getreg32(reg_base + PWM0_INTERRUPT_OFFSET + ch * 0x20);
            regval &= ~(PWM_INT_PERIOD_CNT_MASK);
            regval |= (arg << PWM_INT_PERIOD_CNT_SHIFT);
            putreg32(regval, reg_base + PWM0_INTERRUPT_OFFSET + ch * 0x20);
            break;

        default:
            ret = -EPERM;
            break;
    }
    return ret;
}