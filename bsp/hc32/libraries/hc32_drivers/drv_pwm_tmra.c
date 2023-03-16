/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-06-27     lianghongquan     first version
 */

#include <board.h>

#if (defined RT_USING_PWM) && (defined BSP_USING_PWM_TMRA)
#include "drv_config.h"
#include <drivers/rt_drv_pwm.h>

//#define DRV_DEBUG
#define LOG_TAG             "drv.pwm.tmra"
#include <drv_log.h>

#if (!(defined(BSP_USING_PWM_TMRA_1) || defined(BSP_USING_PWM_TMRA_2) || \
       defined(BSP_USING_PWM_TMRA_3) || defined(BSP_USING_PWM_TMRA_4) || \
       defined(BSP_USING_PWM_TMRA_5) || defined(BSP_USING_PWM_TMRA_6)))
    #error "Please define at least one BSP_USING_PWM_TMRA_x"
#endif

enum
{
#ifdef BSP_USING_PWM_TMRA_1
    PWM_TMRA_1_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_2
    PWM_TMRA_2_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_3
    PWM_TMRA_3_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_4
    PWM_TMRA_4_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_5
    PWM_TMRA_5_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_6
    PWM_TMRA_6_INDEX,
#endif
};

struct hc32_pwm_tmra
{
    struct rt_device_pwm pwm_device;
    CM_TMRA_TypeDef *instance;
    stc_tmra_init_t stcTmraInit;
    stc_tmra_pwm_init_t stcPwmInit;
    rt_uint8_t channel;
    char *name;
};

static struct hc32_pwm_tmra g_pwm_dev_array[] =
{
#ifdef BSP_USING_PWM_TMRA_1
    PWM_TMRA_1_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_2
    PWM_TMRA_2_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_3
    PWM_TMRA_3_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_4
    PWM_TMRA_4_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_5
    PWM_TMRA_5_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_6
    PWM_TMRA_6_CONFIG,
#endif
};

static rt_uint32_t get_tmra_clk_freq_not_div(CM_TMRA_TypeDef *TMRAx)
{
    stc_clock_freq_t stcClockFreq;
    CLK_GetClockFreq(&stcClockFreq);
    return stcClockFreq.u32Pclk1Freq;
}

static rt_uint32_t get_tmra_clk_freq(CM_TMRA_TypeDef *TMRAx)
{
    rt_uint32_t u32clkFreq;
    uint16_t u16Div;
    //
    u32clkFreq = get_tmra_clk_freq_not_div(TMRAx);
    u16Div = READ_REG16(TMRAx->BCSTR) & TMRA_BCSTR_CKDIV;
    switch (u16Div)
    {
        case (TMRA_CLK_DIV2):
            u32clkFreq /= 2;
            break;
        case (TMRA_CLK_DIV4):
            u32clkFreq /= 4;
            break;
        case (TMRA_CLK_DIV8):
            u32clkFreq /= 8;
            break;
        case (TMRA_CLK_DIV16):
            u32clkFreq /= 16;
            break;
        case (TMRA_CLK_DIV32):
            u32clkFreq /= 32;
            break;
        case (TMRA_CLK_DIV64):
            u32clkFreq /= 64;
            break;
        case (TMRA_CLK_DIV128):
            u32clkFreq /= 128;
            break;
        case (TMRA_CLK_DIV256):
            u32clkFreq /= 256;
            break;
        case (TMRA_CLK_DIV512):
            u32clkFreq /= 512;
            break;
        case (TMRA_CLK_DIV1024):
            u32clkFreq /= 1024;
            break;
        case (TMRA_CLK_DIV1):
        default:
            break;
    }
    return u32clkFreq;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static rt_err_t drv_pwm_enable(CM_TMRA_TypeDef *TMRAx, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    if (RT_TRUE == enable) {TMRA_PWM_OutputCmd(TMRAx, configuration->channel, ENABLE);}
    else {TMRA_PWM_OutputCmd(TMRAx, configuration->channel, DISABLE);}
    return RT_EOK;
}

static rt_err_t drv_pwm_get(CM_TMRA_TypeDef *TMRAx, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    rt_uint64_t u64clk_ns;
    u32clkFreq = get_tmra_clk_freq(TMRAx);
    u64clk_ns = (rt_uint64_t)1000000000ul / u32clkFreq;
    configuration->period = u64clk_ns * TMRA_GetPeriodValue(TMRAx);
    configuration->pulse = u64clk_ns * TMRA_GetCompareValue(TMRAx, configuration->channel);
    return RT_EOK;
}

static rt_err_t drv_pwm_set(CM_TMRA_TypeDef *TMRAx, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    rt_uint64_t u64clk_ns;
    rt_uint64_t u64val;
    //
    u32clkFreq = get_tmra_clk_freq(TMRAx);
    u64clk_ns = (rt_uint64_t)1000000000ul / u32clkFreq;
    u64val = (rt_uint64_t)configuration->period / u64clk_ns;
    if ((configuration->period <= u64clk_ns) || (u64val > 0xFFFF))
    {
        // clk not match, need change div
        uint32_t div_bit;
        u32clkFreq = get_tmra_clk_freq_not_div(TMRAx);
        u64clk_ns = (rt_uint64_t)1000000000ul / u32clkFreq;
        u64val = (rt_uint64_t)configuration->period / u64clk_ns;
        for (div_bit=0; div_bit<= 10; div_bit++)
        {
            if (u64val < 0xFFFF) break;
            u64val /= 2;
        }
        if (div_bit > 10) return RT_ERROR;
        //
        TMRA_SetClockDiv(TMRAx, div_bit << TMRA_BCSTR_CKDIV_POS);
        u32clkFreq = get_tmra_clk_freq(TMRAx);
        u64clk_ns = (rt_uint64_t)1000000000ul / u32clkFreq;
    }
    TMRA_SetPeriodValue(TMRAx, configuration->period / u64clk_ns);
    TMRA_SetCompareValue(TMRAx, configuration->channel, configuration->pulse / u64clk_ns);
    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    struct hc32_pwm_tmra *pwm;
    pwm = rt_container_of(device, struct hc32_pwm_tmra, pwm_device);
    CM_TMRA_TypeDef *TMRAx = pwm->instance;

    switch (cmd)
    {
    case PWMN_CMD_ENABLE:
        configuration->complementary = RT_TRUE;
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(TMRAx, configuration, RT_TRUE);
    case PWMN_CMD_DISABLE:
        configuration->complementary = RT_FALSE;
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(TMRAx, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(TMRAx, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(TMRAx, configuration);
    default:
        return -RT_EINVAL;
    }
}

static rt_err_t _pwm_tmra_init(struct hc32_pwm_tmra *device)
{
    CM_TMRA_TypeDef *TMRAx;
    uint32_t i;
    //
    RT_ASSERT(device != RT_NULL);
    TMRAx = device->instance;
    TMRA_Init(TMRAx, &device->stcTmraInit);
    for (i=0; i<8; i++)
    {
        if ((device->channel >> i) & 0x01)
        {
            TMRA_PWM_Init(TMRAx, i, &device->stcPwmInit);
        }
    }
    TMRA_Start(TMRAx);
    return RT_EOK;
}

static void pwm_get_channel(void)
{
#ifdef BSP_USING_PWM_TMRA_1
    #ifdef BSP_USING_PWM_TMRA_1_CH1
        g_pwm_dev_array[PWM_TMRA_1_INDEX].channel |= 1 << 0;
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH2
        g_pwm_dev_array[PWM_TMRA_1_INDEX].channel |= 1 << 1;
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH3
        g_pwm_dev_array[PWM_TMRA_1_INDEX].channel |= 1 << 2;
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH4
        g_pwm_dev_array[PWM_TMRA_1_INDEX].channel |= 1 << 3;
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH5
        g_pwm_dev_array[PWM_TMRA_1_INDEX].channel |= 1 << 4;
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH6
        g_pwm_dev_array[PWM_TMRA_1_INDEX].channel |= 1 << 5;
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH7
        g_pwm_dev_array[PWM_TMRA_1_INDEX].channel |= 1 << 6;
    #endif
    #ifdef BSP_USING_PWM_TMRA_1_CH8
        g_pwm_dev_array[PWM_TMRA_1_INDEX].channel |= 1 << 7;
    #endif
#endif
#ifdef BSP_USING_PWM_TMRA_2
    #ifdef BSP_USING_PWM_TMRA_2_CH1
        g_pwm_dev_array[PWM_TMRA_2_INDEX].channel |= 1 << 0;
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH2
        g_pwm_dev_array[PWM_TMRA_2_INDEX].channel |= 1 << 1;
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH3
        g_pwm_dev_array[PWM_TMRA_2_INDEX].channel |= 1 << 2;
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH4
        g_pwm_dev_array[PWM_TMRA_2_INDEX].channel |= 1 << 3;
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH5
        g_pwm_dev_array[PWM_TMRA_2_INDEX].channel |= 1 << 4;
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH6
        g_pwm_dev_array[PWM_TMRA_2_INDEX].channel |= 1 << 5;
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH7
        g_pwm_dev_array[PWM_TMRA_2_INDEX].channel |= 1 << 6;
    #endif
    #ifdef BSP_USING_PWM_TMRA_2_CH8
        g_pwm_dev_array[PWM_TMRA_2_INDEX].channel |= 1 << 7;
    #endif
#endif
#ifdef BSP_USING_PWM_TMRA_3
    #ifdef BSP_USING_PWM_TMRA_3_CH1
        g_pwm_dev_array[PWM_TMRA_3_INDEX].channel |= 1 << 0;
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH2
        g_pwm_dev_array[PWM_TMRA_3_INDEX].channel |= 1 << 1;
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH3
        g_pwm_dev_array[PWM_TMRA_3_INDEX].channel |= 1 << 2;
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH4
        g_pwm_dev_array[PWM_TMRA_3_INDEX].channel |= 1 << 3;
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH5
        g_pwm_dev_array[PWM_TMRA_3_INDEX].channel |= 1 << 4;
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH6
        g_pwm_dev_array[PWM_TMRA_3_INDEX].channel |= 1 << 5;
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH7
        g_pwm_dev_array[PWM_TMRA_3_INDEX].channel |= 1 << 6;
    #endif
    #ifdef BSP_USING_PWM_TMRA_3_CH8
        g_pwm_dev_array[PWM_TMRA_3_INDEX].channel |= 1 << 7;
    #endif
#endif
#ifdef BSP_USING_PWM_TMRA_4
    #ifdef BSP_USING_PWM_TMRA_4_CH1
        g_pwm_dev_array[PWM_TMRA_4_INDEX].channel |= 1 << 0;
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH2
        g_pwm_dev_array[PWM_TMRA_4_INDEX].channel |= 1 << 1;
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH3
        g_pwm_dev_array[PWM_TMRA_4_INDEX].channel |= 1 << 2;
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH4
        g_pwm_dev_array[PWM_TMRA_4_INDEX].channel |= 1 << 3;
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH5
        g_pwm_dev_array[PWM_TMRA_4_INDEX].channel |= 1 << 4;
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH6
        g_pwm_dev_array[PWM_TMRA_4_INDEX].channel |= 1 << 5;
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH7
        g_pwm_dev_array[PWM_TMRA_4_INDEX].channel |= 1 << 6;
    #endif
    #ifdef BSP_USING_PWM_TMRA_4_CH8
        g_pwm_dev_array[PWM_TMRA_4_INDEX].channel |= 1 << 7;
    #endif
#endif
#ifdef BSP_USING_PWM_TMRA_5
    #ifdef BSP_USING_PWM_TMRA_5_CH1
        g_pwm_dev_array[PWM_TMRA_5_INDEX].channel |= 1 << 0;
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH2
        g_pwm_dev_array[PWM_TMRA_5_INDEX].channel |= 1 << 1;
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH3
        g_pwm_dev_array[PWM_TMRA_5_INDEX].channel |= 1 << 2;
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH4
        g_pwm_dev_array[PWM_TMRA_5_INDEX].channel |= 1 << 3;
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH5
        g_pwm_dev_array[PWM_TMRA_5_INDEX].channel |= 1 << 4;
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH6
        g_pwm_dev_array[PWM_TMRA_5_INDEX].channel |= 1 << 5;
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH7
        g_pwm_dev_array[PWM_TMRA_5_INDEX].channel |= 1 << 6;
    #endif
    #ifdef BSP_USING_PWM_TMRA_5_CH8
        g_pwm_dev_array[PWM_TMRA_5_INDEX].channel |= 1 << 7;
    #endif
#endif
#ifdef BSP_USING_PWM_TMRA_6
    #ifdef BSP_USING_PWM_TMRA_6_CH1
        g_pwm_dev_array[PWM_TMRA_6_INDEX].channel |= 1 << 0;
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH2
        g_pwm_dev_array[PWM_TMRA_6_INDEX].channel |= 1 << 1;
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH3
        g_pwm_dev_array[PWM_TMRA_6_INDEX].channel |= 1 << 2;
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH4
        g_pwm_dev_array[PWM_TMRA_6_INDEX].channel |= 1 << 3;
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH5
        g_pwm_dev_array[PWM_TMRA_6_INDEX].channel |= 1 << 4;
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH6
        g_pwm_dev_array[PWM_TMRA_6_INDEX].channel |= 1 << 5;
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH7
        g_pwm_dev_array[PWM_TMRA_6_INDEX].channel |= 1 << 6;
    #endif
    #ifdef BSP_USING_PWM_TMRA_6_CH8
        g_pwm_dev_array[PWM_TMRA_6_INDEX].channel |= 1 << 7;
    #endif
#endif
}

static void _enable_periph_clk(void)
{
#ifdef BSP_USING_PWM_TMRA_1
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_1, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_2
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_2, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_3
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_3, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_4
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_4, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_5
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_5, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_6
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_6, ENABLE);
#endif
}

extern rt_err_t rt_hw_board_pwm_tmra_init(CM_TMRA_TypeDef *TMRAx);
static int rt_hw_pwm_tmra_init(void)
{
    int i = 0;
    rt_err_t result = RT_EOK;

    pwm_get_channel();
    _enable_periph_clk();
    for (i = 0; i < sizeof(g_pwm_dev_array) / sizeof(g_pwm_dev_array[0]); i++)
    {
        /* pwm init */
        _pwm_tmra_init(&g_pwm_dev_array[i]);
        rt_hw_board_pwm_tmra_init(g_pwm_dev_array[i].instance);
        /* register UART device */
        result = rt_device_pwm_register(&g_pwm_dev_array[i].pwm_device, g_pwm_dev_array[i].name, &drv_ops, &g_pwm_dev_array[i].instance);
        RT_ASSERT(result == RT_EOK);
    }
    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_tmra_init);
#endif /* RT_USING_PWM */
