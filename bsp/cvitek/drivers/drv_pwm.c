/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/02/19     flyingcys    first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_pwm.h"
#include "drv_pinmux.h"
#include "drv_ioremap.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.PWM"

struct cvi_pwm_dev
{
    struct rt_device_pwm device;
    const char *name;
    rt_ubase_t reg_base;
};

static const uint64_t count_unit = 100000000;  // 100M count per second
static const uint64_t NSEC_COUNT = 1000000000;  // ns

static void cvi_pwm_set_config(rt_ubase_t reg_base, struct rt_pwm_configuration *cfg)
{
    unsigned long long duty_clk, period_clk;

    cvi_pwm_set_polarity_high_ch(reg_base, (cfg->channel & PWM_MAX_CH));

    duty_clk = (cfg->pulse * count_unit) / NSEC_COUNT;
    cvi_pwm_set_high_period_ch(reg_base, (cfg->channel & PWM_MAX_CH), duty_clk);

    period_clk = (cfg->period * count_unit) / NSEC_COUNT;
    cvi_pwm_set_period_ch(reg_base, (cfg->channel & PWM_MAX_CH), period_clk);

    cvi_pwm_output_en_ch(reg_base, cfg->channel & PWM_MAX_CH);
}

static void cvi_pwm_get_config(rt_ubase_t reg_base, struct rt_pwm_configuration *cfg)
{
    unsigned long long duty_clk, period_clk;

    duty_clk = cvi_pwm_get_high_period_ch(reg_base, (cfg->channel & PWM_MAX_CH));
    cfg->pulse = duty_clk * NSEC_COUNT / count_unit;

    period_clk = cvi_pwm_get_period_ch(reg_base, (cfg->channel & PWM_MAX_CH));
    cfg->period = period_clk * NSEC_COUNT / count_unit;
}

static rt_err_t _pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *cfg = (struct rt_pwm_configuration *)arg;
    struct cvi_pwm_dev *pwm_dev = (struct cvi_pwm_dev *)device->parent.user_data;
    unsigned long long duty_clk, period_clk;
    const uint64_t count_unit = 100000000;  // 100M count per second
    const uint64_t NSEC_COUNT = 1000000000;  // ns

    if (cfg->channel >= PWM_CHANNEL_NUM)
        return -RT_EINVAL;

    switch (cmd)
    {
        case PWM_CMD_ENABLE:
            cvi_pwm_start_en_ch(pwm_dev->reg_base, cfg->channel & PWM_MAX_CH);
        break;

        case PWM_CMD_DISABLE:
            cvi_pwm_start_dis_ch(pwm_dev->reg_base, cfg->channel & PWM_MAX_CH);
        break;

        case PWM_CMD_SET:
            cvi_pwm_set_config(pwm_dev->reg_base, cfg);
        break;

        case PWM_CMD_GET:
            cvi_pwm_get_config(pwm_dev->reg_base, cfg);
        break;

        case PWM_CMD_SET_PERIOD:
            period_clk = (cfg->period * count_unit) / NSEC_COUNT;
            cvi_pwm_set_period_ch(pwm_dev->reg_base, (cfg->channel & PWM_MAX_CH), period_clk);
        break;

        case PWM_CMD_SET_PULSE:
            duty_clk = (cfg->pulse * count_unit) / NSEC_COUNT;
            cvi_pwm_set_high_period_ch(pwm_dev->reg_base, (cfg->channel & PWM_MAX_CH), duty_clk);
        break;

        default:
        LOG_D("cmd: %x channel: %d period: %d pulse: %d", cmd, cfg->channel, cfg->period, cfg->pulse);
        break;
    }

    return RT_EOK;
}

const static struct rt_pwm_ops cvi_pwm_ops =
{
    .control = &_pwm_control
};

static struct cvi_pwm_dev cvi_pwm[] =
{
#ifdef BSP_USING_PWM0
    {
        .name = "pwm0",
        .reg_base = CVI_PWM0_BASE,
    },
#endif

#ifdef BSP_USING_PWM1
    {
        .name = "pwm1",
        .reg_base = CVI_PWM1_BASE,
    },
#endif

#ifdef BSP_USING_PWM2
    {
        .name = "pwm2",
        .reg_base = CVI_PWM2_BASE,
    },
#endif

#ifdef BSP_USING_PWM3
    {
        .name = "pwm3",
        .reg_base = CVI_PWM3_BASE,
    },
#endif
};


#if defined(BOARD_TYPE_MILKV_DUO) || defined(BOARD_TYPE_MILKV_DUO_SPINOR)

#ifdef BSP_USING_PWM0
static const char *pinname_whitelist_pwm0[] = {
    NULL,
};
static const char *pinname_whitelist_pwm1[] = {
    NULL,
};
static const char *pinname_whitelist_pwm2[] = {
    NULL,
};
static const char *pinname_whitelist_pwm3[] = {
    NULL,
};
#endif

#ifdef BSP_USING_PWM1
static const char *pinname_whitelist_pwm4[] = {
    "SD1_D3",
    "UART0_TX",
    NULL,
};
static const char *pinname_whitelist_pwm5[] = {
    "SD1_D2",
    "UART0_RX",
    NULL,
};
static const char *pinname_whitelist_pwm6[] = {
    "SD1_D1",
    NULL,
};
static const char *pinname_whitelist_pwm7[] = {
    "SD1_D0",
    NULL,
};
#endif

#ifdef BSP_USING_PWM2
static const char *pinname_whitelist_pwm8[] = {
    "SD1_CMD",
    NULL,
};
static const char *pinname_whitelist_pwm9[] = {
    "SD1_CLK",
    NULL,
};
static const char *pinname_whitelist_pwm10[] = {
    "SD1_GPIO1",
    NULL,
};
static const char *pinname_whitelist_pwm11[] = {
    "SD1_GPIO0",
    NULL,
};
#endif

#ifdef BSP_USING_PWM3
static const char *pinname_whitelist_pwm12[] = {
    NULL,
};
static const char *pinname_whitelist_pwm13[] = {
    NULL,
};
static const char *pinname_whitelist_pwm14[] = {
    NULL,
};
static const char *pinname_whitelist_pwm15[] = {
    NULL,
};
#endif

#elif defined(BOARD_TYPE_MILKV_DUO256M) || defined(BOARD_TYPE_MILKV_DUO256M_SPINOR)

#ifdef BSP_USING_PWM0
static const char *pinname_whitelist_pwm0[] = {
    NULL,
};
static const char *pinname_whitelist_pwm1[] = {
    NULL,
};
static const char *pinname_whitelist_pwm2[] = {
    NULL,
};
static const char *pinname_whitelist_pwm3[] = {
    NULL,
};
#endif

#ifdef BSP_USING_PWM1
static const char *pinname_whitelist_pwm4[] = {
    "SD1_D3",
    "UART0_TX",
    NULL,
};
static const char *pinname_whitelist_pwm5[] = {
    "SD1_D2",
    "UART0_RX",
    NULL,
};
static const char *pinname_whitelist_pwm6[] = {
    "JTAG_CPU_TCK",
    "SD1_D1",
    NULL,
};
static const char *pinname_whitelist_pwm7[] = {
    "JTAG_CPU_TMS",
    "SD1_D0",
    NULL,
};
#endif

#ifdef BSP_USING_PWM2
static const char *pinname_whitelist_pwm8[] = {
    "SD1_CMD",
    NULL,
};
static const char *pinname_whitelist_pwm9[] = {
    "SD1_CLK",
    NULL,
};
static const char *pinname_whitelist_pwm10[] = {
    "PAD_MIPI_TXM1",
    NULL,
};
static const char *pinname_whitelist_pwm11[] = {
    "PAD_MIPI_TXP1",
    NULL,
};
#endif

#ifdef BSP_USING_PWM3
static const char *pinname_whitelist_pwm12[] = {
    NULL,
};
static const char *pinname_whitelist_pwm13[] = {
    NULL,
};
static const char *pinname_whitelist_pwm14[] = {
    NULL,
};
static const char *pinname_whitelist_pwm15[] = {
    NULL,
};
#endif

#else
    #error "Unsupported board type!"
#endif

static void rt_hw_pwm_pinmux_config()
{
#ifdef BSP_USING_PWM0
    pinmux_config(BSP_PWM0_0_PINNAME, PWM_0, pinname_whitelist_pwm0);
    pinmux_config(BSP_PWM0_1_PINNAME, PWM_1, pinname_whitelist_pwm1);
    pinmux_config(BSP_PWM0_2_PINNAME, PWM_2, pinname_whitelist_pwm2);
    pinmux_config(BSP_PWM0_3_PINNAME, PWM_3, pinname_whitelist_pwm3);
#endif /* BSP_USING_PWM0 */

#ifdef BSP_USING_PWM1
    pinmux_config(BSP_PWM1_4_PINNAME, PWM_4, pinname_whitelist_pwm4);
    pinmux_config(BSP_PWM1_5_PINNAME, PWM_5, pinname_whitelist_pwm5);
    pinmux_config(BSP_PWM1_6_PINNAME, PWM_6, pinname_whitelist_pwm6);
    pinmux_config(BSP_PWM1_7_PINNAME, PWM_7, pinname_whitelist_pwm7);
#endif /* BSP_USING_PWM1 */

#ifdef BSP_USING_PWM2
    pinmux_config(BSP_PWM2_8_PINNAME, PWM_8, pinname_whitelist_pwm8);
    pinmux_config(BSP_PWM2_9_PINNAME, PWM_9, pinname_whitelist_pwm9);
    pinmux_config(BSP_PWM2_10_PINNAME, PWM_10, pinname_whitelist_pwm10);
    pinmux_config(BSP_PWM2_11_PINNAME, PWM_11, pinname_whitelist_pwm11);
#endif /* BSP_USING_PWM2 */

#ifdef BSP_USING_PWM3
    pinmux_config(BSP_PWM3_12_PINNAME, PWM_12, pinname_whitelist_pwm12);
    pinmux_config(BSP_PWM3_13_PINNAME, PWM_13, pinname_whitelist_pwm13);
    pinmux_config(BSP_PWM3_14_PINNAME, PWM_14, pinname_whitelist_pwm14);
    pinmux_config(BSP_PWM3_15_PINNAME, PWM_15, pinname_whitelist_pwm15);
#endif /* BSP_USING_PWM3 */
}

int rt_hw_pwm_init(void)
{
    int result = RT_EOK;
    uint8_t i;

    rt_hw_pwm_pinmux_config();

    for (i = 0; i < sizeof(cvi_pwm) / sizeof(cvi_pwm[0]); i++)
    {
        cvi_pwm[i].device.base = (rt_ubase_t)DRV_IOREMAP((void *)cvi_pwm[i].device.base, 0x1000);

        result = rt_device_pwm_register(&cvi_pwm[i].device, cvi_pwm[i].name, &cvi_pwm_ops, &cvi_pwm[i]);
        if (result != RT_EOK)
        {
            LOG_E("device %s register failed", cvi_pwm[i].name);
            return -RT_ERROR;
        }
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);
