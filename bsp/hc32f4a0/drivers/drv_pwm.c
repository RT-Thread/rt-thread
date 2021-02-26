/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */

#include <board.h>
#include <rtdbg.h>

#ifdef RT_USING_PWM

#if !defined(BSP_USING_PWM1)  && !defined(BSP_USING_PWM2)  && !defined(BSP_USING_PWM3) && \
    !defined(BSP_USING_PWM4)  && !defined(BSP_USING_PWM5)  && !defined(BSP_USING_PWM6) && \
    !defined(BSP_USING_PWM7)  && !defined(BSP_USING_PWM8)  && !defined(BSP_USING_PWM9) && \
    !defined(BSP_USING_PWM10) && !defined(BSP_USING_PWM11) && !defined(BSP_USING_PWM12)
#error "Please define at least one BSP_USING_PWMx"
/* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable PWM */
#endif

#define PWM_MAX_PERIOD                  (65535U)
#define PWM_MIN_PERIOD                  (1U)
#define PWM_MIN_PULSE                   (1U)

#define PWM_MAX_CHANNEL                 (TMRA_CH_4)

enum
{
#ifdef BSP_USING_PWM1
    PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    PWM3_INDEX,
#endif
#ifdef BSP_USING_PWM4
    PWM4_INDEX,
#endif
#ifdef BSP_USING_PWM5
    PWM5_INDEX,
#endif
#ifdef BSP_USING_PWM6
    PWM6_INDEX,
#endif
#ifdef BSP_USING_PWM7
    PWM7_INDEX,
#endif
#ifdef BSP_USING_PWM8
    PWM8_INDEX,
#endif
#ifdef BSP_USING_PWM9
    PWM9_INDEX,
#endif
#ifdef BSP_USING_PWM10
    PWM10_INDEX,
#endif
#ifdef BSP_USING_PWM11
    PWM11_INDEX,
#endif
#ifdef BSP_USING_PWM12
    PWM12_INDEX,
#endif
};

struct hc32_pwm_config
{
    struct rt_device_pwm pwm_device;
    M4_TMRA_TypeDef      *timer_periph;
    rt_uint8_t           channel;
    char                 *name;
};

#ifndef HC32_PWM_CONFIG
#define HC32_PWM_CONFIG(periph, ch, label)      \
    {                                           \
        .timer_periph   = periph,               \
        .channel        = ch,                   \
        .name           = label                 \
    }
#endif /* HC32_PWM_CONFIG */

static struct hc32_pwm_config pwm_obj[] =
{
#ifdef BSP_USING_PWM1
    HC32_PWM_CONFIG(M4_TMRA_1 , 0, "pwm1"),
#endif
#ifdef BSP_USING_PWM2
    HC32_PWM_CONFIG(M4_TMRA_2 , 0, "pwm2"),
#endif
#ifdef BSP_USING_PWM3
    HC32_PWM_CONFIG(M4_TMRA_3 , 0, "pwm3"),
#endif
#ifdef BSP_USING_PWM4
    HC32_PWM_CONFIG(M4_TMRA_4 , 0, "pwm4"),
#endif
#ifdef BSP_USING_PWM5
    HC32_PWM_CONFIG(M4_TMRA_5 , 0, "pwm5"),
#endif
#ifdef BSP_USING_PWM6
    HC32_PWM_CONFIG(M4_TMRA_6 , 0, "pwm6"),
#endif
#ifdef BSP_USING_PWM7
    HC32_PWM_CONFIG(M4_TMRA_7 , 0, "pwm7"),
#endif
#ifdef BSP_USING_PWM8
    HC32_PWM_CONFIG(M4_TMRA_8 , 0, "pwm8"),
#endif
#ifdef BSP_USING_PWM9
    HC32_PWM_CONFIG(M4_TMRA_9 , 0, "pwm9"),
#endif
#ifdef BSP_USING_PWM10
    HC32_PWM_CONFIG(M4_TMRA_10 , 0, "pwm10"),
#endif
#ifdef BSP_USING_PWM11
    HC32_PWM_CONFIG(M4_TMRA_11 , 0, "pwm11"),
#endif
#ifdef BSP_USING_PWM12
    HC32_PWM_CONFIG(M4_TMRA_12 , 0, "pwm12"),
#endif
};

static rt_uint16_t hc32_pwm_get_unit_number(M4_TMRA_TypeDef *TMRAx)
{
    rt_uint16_t unit_num;
    const rt_uint32_t unit_step = 0x400U;

    if (((rt_uint32_t)TMRAx) >= ((rt_uint32_t)M4_TMRA_1))
    {
        unit_num = (((rt_uint32_t)TMRAx) - ((rt_uint32_t)M4_TMRA_1)) / unit_step;
    }
    else
    {
        unit_num = (((rt_uint32_t)TMRAx) - ((rt_uint32_t)M4_TMRA_5)) / unit_step + 4;
    }

    return unit_num;
}

static void hc32_pwm_clock_config(M4_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    rt_uint32_t timer_periph;
    rt_uint16_t unit_num;

    unit_num     = hc32_pwm_get_unit_number(TMRAx);
    timer_periph = PWC_FCG2_TMRA_1 << unit_num;
    PWC_Fcg2PeriphClockCmd(timer_periph, enNewState);
}

static rt_err_t hc32_pwm_enable(M4_TMRA_TypeDef *TMRAx, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    if (configuration->channel > PWM_MAX_CHANNEL)
    {
        return RT_EINVAL;
    }

    if (!enable)
    {
        TMRA_PWM_Cmd(TMRAx, configuration->channel, Disable);
    }
    else
    {
        TMRA_PWM_Cmd(TMRAx, configuration->channel, Enable);
    }

    return RT_EOK;
}

static rt_err_t hc32_pwm_get(M4_TMRA_TypeDef *TMRAx, struct rt_pwm_configuration *configuration)
{
    stc_clk_freq_t stcClkFreq;
    rt_uint32_t clk_freq;
    rt_uint16_t unit_num;
    rt_uint16_t div_val;

    CLK_GetClockFreq(&stcClkFreq);
    unit_num = hc32_pwm_get_unit_number(TMRAx);
    if (unit_num >= 4)
    {
        clk_freq = stcClkFreq.pclk1Freq;
    }
    else
    {
        clk_freq = stcClkFreq.pclk0Freq;
    }

    /* Convert nanosecond to frequency and duty cycle */
    div_val = 0x01 << (READ_REG32_BIT(TMRAx->BCSTR, TMRA_BCSTR_CKDIV) >> TMRA_BCSTR_CKDIV_POS);
    clk_freq /= 1000000UL;
    configuration->period = (TMRA_GetPeriodVal(TMRAx) + 1) * div_val * 1000UL / clk_freq;
    configuration->pulse = (TMRA_GetCmpVal(TMRAx, configuration->channel) + 1) * div_val * 1000UL / clk_freq;

    return RT_EOK;
}

static rt_err_t hc32_pwm_set(M4_TMRA_TypeDef *TMRAx, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    rt_uint64_t clk_div;
    stc_clk_freq_t stcClkFreq;
    rt_uint32_t clk_freq;
    rt_uint16_t unit_num;
    rt_uint16_t div_val;

    CLK_GetClockFreq(&stcClkFreq);
    unit_num = hc32_pwm_get_unit_number(TMRAx);
    if (unit_num >= 4)
    {
        clk_freq = stcClkFreq.pclk1Freq;
    }
    else
    {
        clk_freq = stcClkFreq.pclk0Freq;
    }
    /* Convert nanosecond to frequency and duty cycle */
    clk_freq /= 1000000UL;
    period = (unsigned long long)configuration->period * clk_freq / 1000UL;
    clk_div = period / PWM_MAX_PERIOD + 1;

    if (clk_div > 1024)
    {
        return RT_EINVAL;
    }
    else if (clk_div != 1)
    {
        for (div_val=512; div_val>1; div_val>>=1)
        {
            if (clk_div > div_val)
            {
                clk_div = div_val << 1;
                break;
            }
        }
    }
    period = period / clk_div;
    TMRA_SetPCLKDiv(TMRAx, ((__CLZ(__RBIT(clk_div))) << TMRA_BCSTR_CKDIV_POS));

    if (period < PWM_MIN_PERIOD)
    {
        period = PWM_MIN_PERIOD;
    }
    TMRA_SetPeriodVal(TMRAx, period - 1);

    pulse = (unsigned long long)configuration->pulse * clk_freq / clk_div / 1000UL;
    if (pulse < PWM_MIN_PULSE)
    {
        pulse = PWM_MIN_PULSE;
    }
    else if (pulse > period)
    {
        pulse = period;
    }
    TMRA_SetCmpVal(TMRAx, configuration->channel, pulse - 1);
    TMRA_SetCntVal(TMRAx, 0);

    return RT_EOK;
}

static rt_err_t hc32_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    M4_TMRA_TypeDef *timer_periph = (M4_TMRA_TypeDef *)device->parent.user_data;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return hc32_pwm_enable(timer_periph, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return hc32_pwm_enable(timer_periph, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return hc32_pwm_set(timer_periph, configuration);
    case PWM_CMD_GET:
        return hc32_pwm_get(timer_periph, configuration);
    default:
        return RT_EINVAL;
    }
}

extern rt_err_t rt_hw_board_pwm_init(M4_TMRA_TypeDef *TMRAx);

static rt_err_t hc32_pwm_init(struct hc32_pwm_config *device)
{
    rt_err_t result = RT_EOK;
    stc_tmra_init_t stcTmraInit;
    stc_tmra_pwm_cfg_t stcPwmCfg;

    RT_ASSERT(device != RT_NULL);

    /* Enable Timer peripheral clock. */
    hc32_pwm_clock_config(device->timer_periph, Enable);
    /* pwm pin configuration */
    result = rt_hw_board_pwm_init(device->timer_periph);
    if (RT_EOK == result)
    {
        TMRA_DeInit(device->timer_periph);
        TMRA_StructInit(&stcTmraInit);
        stcTmraInit.u32PCLKDiv   = TMRA_PCLK_DIV1;
        stcTmraInit.u32CntOvfOp  = TMRA_OVF_CNT_CONTINUE;
        stcTmraInit.u32PeriodVal = 0xFFFF;
        stcTmraInit.u32CntVal    = 0;
        TMRA_Init(device->timer_periph, &stcTmraInit);

        /* Set the comparison reference value */
        TMRA_PWM_StructInit(&stcPwmCfg);
        stcPwmCfg.u32StartPolarity  = TMRA_PWM_START_HIGH;
        stcPwmCfg.u32StopPolarity   = TMRA_PWM_STOP_LOW;
        stcPwmCfg.u32CmpPolarity    = TMRA_PWM_CMP_LOW;
        stcPwmCfg.u32PeriodPolarity = TMRA_PWM_PERIOD_HIGH;

        /* config pwm channel */
        if (0 != (device->channel & 0x01))
        {
            TMRA_PWM_Config(device->timer_periph, TMRA_CH_1, &stcPwmCfg);
            TMRA_SetCmpVal(device->timer_periph, TMRA_CH_1, 0x7FFF);
        }
        if (0 != (device->channel & 0x02))
        {
            TMRA_PWM_Config(device->timer_periph, TMRA_CH_2, &stcPwmCfg);
            TMRA_SetCmpVal(device->timer_periph, TMRA_CH_2, 0x7FFF);
        }
        if (0 != (device->channel & 0x04))
        {
            TMRA_PWM_Config(device->timer_periph, TMRA_CH_3, &stcPwmCfg);
            TMRA_SetCmpVal(device->timer_periph, TMRA_CH_3, 0x7FFF);
        }
        if (0 != (device->channel & 0x08))
        {
            TMRA_PWM_Config(device->timer_periph, TMRA_CH_4, &stcPwmCfg);
            TMRA_SetCmpVal(device->timer_periph, TMRA_CH_4, 0x7FFF);
        }
        /* start timer */
        TMRA_Start(device->timer_periph);
    }

    return result;
}

static void hc32_pwm_get_channel(void)
{
#ifdef BSP_USING_PWM1_CH1
    pwm_obj[PWM1_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM1_CH2
    pwm_obj[PWM1_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM1_CH3
    pwm_obj[PWM1_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM1_CH4
    pwm_obj[PWM1_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM2_CH1
    pwm_obj[PWM2_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM2_CH2
    pwm_obj[PWM2_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM2_CH3
    pwm_obj[PWM2_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM2_CH4
    pwm_obj[PWM2_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM3_CH1
    pwm_obj[PWM3_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM3_CH2
    pwm_obj[PWM3_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM3_CH3
    pwm_obj[PWM3_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM3_CH4
    pwm_obj[PWM3_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM4_CH1
    pwm_obj[PWM4_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM4_CH2
    pwm_obj[PWM4_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM4_CH3
    pwm_obj[PWM4_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM4_CH4
    pwm_obj[PWM4_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM5_CH1
    pwm_obj[PWM5_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM5_CH2
    pwm_obj[PWM5_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM5_CH3
    pwm_obj[PWM5_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM5_CH4
    pwm_obj[PWM5_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM6_CH1
    pwm_obj[PWM6_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM6_CH2
    pwm_obj[PWM6_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM6_CH3
    pwm_obj[PWM6_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM6_CH4
    pwm_obj[PWM6_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM7_CH1
    pwm_obj[PWM7_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM7_CH2
    pwm_obj[PWM7_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM7_CH3
    pwm_obj[PWM7_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM7_CH4
    pwm_obj[PWM7_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM8_CH1
    pwm_obj[PWM8_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM8_CH2
    pwm_obj[PWM8_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM8_CH3
    pwm_obj[PWM8_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM8_CH4
    pwm_obj[PWM8_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM9_CH1
    pwm_obj[PWM9_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM9_CH2
    pwm_obj[PWM9_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM9_CH3
    pwm_obj[PWM9_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM9_CH4
    pwm_obj[PWM9_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM10_CH1
    pwm_obj[PWM10_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM10_CH2
    pwm_obj[PWM10_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM10_CH3
    pwm_obj[PWM10_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM10_CH4
    pwm_obj[PWM10_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM11_CH1
    pwm_obj[PWM11_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM11_CH2
    pwm_obj[PWM11_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM11_CH3
    pwm_obj[PWM11_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM11_CH4
    pwm_obj[PWM11_INDEX].channel |= (0x01 << 3);
#endif
#ifdef BSP_USING_PWM12_CH1
    pwm_obj[PWM12_INDEX].channel |= (0x01 << 0);
#endif
#ifdef BSP_USING_PWM12_CH2
    pwm_obj[PWM12_INDEX].channel |= (0x01 << 1);
#endif
#ifdef BSP_USING_PWM12_CH3
    pwm_obj[PWM12_INDEX].channel |= (0x01 << 2);
#endif
#ifdef BSP_USING_PWM12_CH4
    pwm_obj[PWM12_INDEX].channel |= (0x01 << 3);
#endif
}

static struct rt_pwm_ops pwm_ops =
{
    .control = hc32_pwm_control
};

static int rt_hw_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    hc32_pwm_get_channel();
    for (i = 0; i < sizeof(pwm_obj) / sizeof(pwm_obj[0]); i++)
    {
        if (hc32_pwm_init(&pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", pwm_obj[i].name);
            result = -RT_ERROR;
        }
        else
        {
            LOG_D("%s init success", pwm_obj[i].name);
            /* register pwm device */
            if (rt_device_pwm_register(&pwm_obj[i].pwm_device, pwm_obj[i].name, &pwm_ops, pwm_obj[i].timer_periph) == RT_EOK)
            {
                LOG_D("%s register success", pwm_obj[i].name);
            }
            else
            {
                LOG_E("%s register failed", pwm_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /* RT_USING_PWM */
