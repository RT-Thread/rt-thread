/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-08-04     Emuzit            first version
 */
#include <rthw.h>
#include <drivers/dev_pwm.h>
#include <drivers/dev_pin.h>
#include "ch56x_pwm.h"
#include "ch56x_sys.h"

#define PWM_CYCLE_MAX   255     // must be 255 for 0%~100% duty cycle

struct pwm_device
{
    struct rt_device_pwm parent;
    volatile struct pwm_registers *reg_base;
    uint32_t period;
};
static struct pwm_device pwmx_device;

static const uint8_t pwmx_pin[] = {PWM0_PIN, PWM1_PIN, PWM2_PIN, PWM3_PIN};

/**
 * @brief   Enable or disable PWM channel output.
 *          Make sure PWM clock is ON for writing registers.
 *
 * @param   device is pointer to the rt_device_pwm device.
 *
 * @param   channel is the PWM channel (0~3) to operate on.
 *
 * @param   enable is to enable PWM when RT_TRUE, or disable when RT_FALSE.
 *
 * @return  None.
 */
static void pwm_channel_enable(struct rt_device_pwm *device,
                               uint32_t channel, rt_bool_t enable)
{
    struct pwm_device *pwm_device = (struct pwm_device *)device;
    volatile struct pwm_registers *pxreg = pwm_device->reg_base;

    uint8_t ctrl_mod, polar;

    if (enable)
    {
        /* set pwm_out_en to allow pwm output */
        ctrl_mod = pxreg->CTRL_MOD.reg;
        pxreg->CTRL_MOD.reg = ctrl_mod | (RB_PWM0_OUT_EN << channel);
    }
    else
    {
        /* ch56x has no disable bit, set pin out to quiesce */
        ctrl_mod = pxreg->CTRL_MOD.reg;
        polar = ctrl_mod & (RB_PWM0_POLAR << channel);
        rt_pin_write(pwmx_pin[channel], polar ? PIN_HIGH : PIN_LOW);
        ctrl_mod &= ~(RB_PWM0_OUT_EN << channel);
        pxreg->CTRL_MOD.reg = ctrl_mod;
    }
}

/**
 * @brief   Set period of the PWM channel.
 *          Make sure PWM clock is ON for writing registers.
 *
 * @param   device is pointer to the rt_device_pwm device.
 *
 * @param   channel is the PWM channel (0~3) to operate on.
 *
 * @param   period is PWM period in nanoseconds.
 *
 * @return  RT_EOK if successful.
 */
static rt_err_t pwm_channel_period(struct rt_device_pwm *device,
                                   uint32_t channel, uint32_t period)
{
    struct pwm_device *pwm_device = (struct pwm_device *)device;

    uint32_t clock_div;

    /* All ch56x PWMX channels share the same period, channel ignored.
     *
     * Max allowed period is when Fsys@2MHz and CLOCK_DIV is 0 (256) :
     *     (1 / 2MHz) * 256 * PWM_CYCLE_MAX => 32640000 ns
     * Note that `period * F_MHz` won't overflow in calculation below.
    */
    if (period > (256 * PWM_CYCLE_MAX * 1000 / 2))
        return -RT_EINVAL;

    if (period != pwm_device->period)
    {
        uint32_t Fsys = sys_hclk_get();
        uint32_t F_MHz = Fsys / 1000000;
        uint32_t F_mod = Fsys % 1000000;

        /* period = (clock_div / Fsys) * 10^9 * PWM_CYCLE_MAX */
        clock_div = period * F_MHz + (1000 * PWM_CYCLE_MAX / 2);
        /* Fsys is mostly in integer MHz, likely to be skipped */
        if (F_mod != 0)
        {
            uint64_t u64v = ((uint64_t)period * F_mod) / 1000000;
            clock_div += (uint32_t)u64v;
        }
        clock_div = clock_div / (1000 * PWM_CYCLE_MAX);
        if (clock_div > 256)
            return -RT_EINVAL;
        /* CLOCK_DIV will be 0 if `clock_div` is 256 */
        pwm_device->reg_base->CLOCK_DIV = (uint8_t)clock_div;
        /* cycle_sel set to PWM_CYCLE_SEL_255 for 0%~100% duty cycle */
        pwmx_device.reg_base->CTRL_CFG.cycle_sel = PWM_CYCLE_SEL_255;
        pwm_device->period = period;
    }

    return RT_EOK;
}

/**
 * @brief   Set pulse duration of the PWM channel.
 *          Make sure PWM clock is ON for writing registers.
 *
 * @param   device is pointer to the rt_device_pwm device.
 *
 * @param   channel is the PWM channel (0~3) to operate on.
 *
 * @param   pulse is PWM pulse duration in nanoseconds.
 *
 * @return  RT_EOK if successful.
 */
static rt_err_t pwm_channel_pulse(struct rt_device_pwm *device,
                                  uint32_t channel, uint32_t pulse)
{
    struct pwm_device *pwm_device = (struct pwm_device *)device;

    uint32_t pdata, period;

    /* duty cycle is calculated with "raw" period setting */
    period = pwm_device->period;
    if (!period || pulse > period)
        return -RT_EINVAL;

    pdata = (pulse * PWM_CYCLE_MAX + (period >> 1)) / period;
    pwm_device->reg_base->PWM_DATA[channel] = pdata;

    return RT_EOK;
}

/**
 * @brief   Set period & pulse of the PWM channel, remain disabled.
 *          Make sure PWM clock is ON for writing registers.
 *
 * @param   device is pointer to the rt_device_pwm device.
 *
 * @param   configuration is the channel/period/pulse specification.
 *          ch56x PWM has no complementary pin, complementary ignored.
 *          FIXME: can we specify PWM output polarity somehow ?
 *
 * @return  RT_EOK if successful.
 */
static rt_err_t pwm_device_set(struct rt_device_pwm *device,
                               struct rt_pwm_configuration *configuration)
{
    struct pwm_device *pwm_device = (struct pwm_device *)device;

    uint32_t channel = configuration->channel;

    rt_err_t res;

    res = pwm_channel_period(device, channel, configuration->period);
    if (res == RT_EOK)
    {
        res = pwm_channel_pulse(device, channel, configuration->pulse);
        if (res == RT_EOK)
        {
            rt_pin_mode(pwmx_pin[channel], PIN_MODE_OUTPUT);
            /* seems to be kept disabled according to sample code */
            pwm_channel_enable(device, channel, RT_FALSE);
        }
    }

    return res;
}

/**
 * @brief   Get period & pulse of the PWM channel.
 *          The returned information is calculated with h/w setting.
 *
 * @param   device is pointer to the rt_device_pwm device.
 *
 * @param   configuration->channel specify the PWM channel (0~3).
 *          configuration->period & pulse return the calculated result.
 *
 * @return  RT_EOK if successful.
 */
static rt_err_t pwm_device_get(struct rt_device_pwm *device,
                               struct rt_pwm_configuration *configuration)
{
    struct pwm_device *pwm_device = (struct pwm_device *)device;
    volatile struct pwm_registers *pxreg = pwm_device->reg_base;

    uint32_t channel = configuration->channel;

    uint32_t Fsys = sys_hclk_get();

    uint32_t clock_div;
    uint32_t pdata;
    uint64_t u64v;

    /* clock_div is actually 256 when CLOCK_DIV is 0 */
    clock_div = pxreg->CLOCK_DIV;
    if (clock_div == 0)
        clock_div = 256;

    u64v = clock_div;
    u64v = (u64v * 1000*1000*1000 * PWM_CYCLE_MAX + (Fsys >> 1)) / Fsys;
    configuration->period = (uint32_t)u64v;

    /* `pdata` <= PWM_CYCLE_MAX, calculated pulse won't exceed period */
    pdata = pxreg->PWM_DATA[channel];
    u64v = clock_div;
    u64v = (u64v * 1000*1000*1000 * pdata + (Fsys >> 1)) / Fsys;
    configuration->pulse = (uint32_t)u64v;

    return RT_EOK;
}

static rt_err_t pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct pwm_device *pwm_device = (struct pwm_device *)device;

    struct rt_pwm_configuration *configuration = arg;
    uint32_t channel = configuration->channel;

    rt_err_t res = RT_EOK;

    RT_ASSERT(device != RT_NULL);

    if (channel >= PWM_CHANNELS)
        return -RT_EINVAL;

    /* PWM clock needs to be ON to write PWM registers */
    sys_slp_clk_off0(RB_SLP_CLK_PWMX, SYS_SLP_CLK_ON);

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        pwm_channel_enable(device, channel, RT_TRUE);
        break;
    case PWM_CMD_DISABLE:
        pwm_channel_enable(device, channel, RT_FALSE);
        break;
    case PWM_CMD_SET:
        return pwm_device_set(device, configuration);
    case PWM_CMD_GET:
        return pwm_device_get(device, configuration);
    case PWM_CMD_SET_PERIOD:
        return pwm_channel_period(device, channel, configuration->period);
    case PWM_CMD_SET_PULSE:
        return pwm_channel_pulse(device, channel, configuration->pulse);
    default:
        res = -RT_EINVAL;
    }

    /* disable PWMX clocking, if all channels are disabled */
    if ((pwm_device->reg_base->CTRL_MOD.reg & PWM_OUT_EN_MASK) == 0)
        sys_slp_clk_off0(RB_SLP_CLK_PWMX, SYS_SLP_CLK_OFF);

    return res;
}

static struct rt_pwm_ops pwm_ops =
{
    .control = pwm_control
};

static int rt_hw_pwm_init(void)
{
    /* init pwmx_device with code to save some flash space */
    pwmx_device.reg_base = (struct pwm_registers *)PWMX_REG_BASE;
    /* Note: PWM clock OFF here => PWM registers not writable */

    return rt_device_pwm_register(
           &pwmx_device.parent, PWM_DEVICE_NAME, &pwm_ops, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);
