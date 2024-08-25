/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-28     tyustli      first version
 *
 */

#include <rtthread.h>

#ifdef RT_USING_PWM

#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

#include <rtdevice.h>
#include <ioremap.h>

#include "fsl_pwm.h"
#include "drv_pwm.h"
#include <drv_common.h>
#include <drivers/dev_pwm.h>

#define PWM_SRC_CLK_FREQ              CLOCK_GetFreq(kCLOCK_IpgClk)
/* PWMPR register value of 0xffff has the same effect as 0xfffe */
#define IMX_PWMPR_MAX           0xfffe
#define NSEC_PER_MSEC           1000000
#define NSEC_PER_SEC            1000

#define MX3_PWMCR_SWR           BIT(3)
#define MX3_PWM_SWR_LOOP        5

#define MX3_PWMSR_FIFOAV_EMPTY      0
#define MX3_PWMSR_FIFOAV_1WORD      1
#define MX3_PWMSR_FIFOAV_2WORDS     2
#define MX3_PWMSR_FIFOAV_3WORDS     3
#define MX3_PWMSR_FIFOAV_4WORDS     4

#define MX3_PWMCR_STOPEN        BIT(25)
#define MX3_PWMCR_DOZEN         BIT(24)
#define MX3_PWMCR_WAITEN        BIT(23)
#define MX3_PWMCR_DBGEN         BIT(22)
#define MX3_PWMCR_BCTR          BIT(21)
#define MX3_PWMCR_HCTR          BIT(20)
#define MX3_PWMCR_CLKSRC        BIT(17)

#define MX3_PWMCR_EN            BIT(0)

static rt_err_t imx6ull_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);

static struct rt_pwm_ops imxrt_drv_ops =
{
    .control = imx6ull_drv_pwm_control
};

static void imx6ull_pwm_reset(PWM_Type *base)
{
    int wait_count = 0;
    uint32_t cr = 0;

    base->PWMCR = MX3_PWMCR_SWR;
    do {
        rt_thread_mdelay(1);
        cr = base->PWMCR;
    } while ((cr & MX3_PWMCR_SWR) &&
         (wait_count++ < MX3_PWM_SWR_LOOP));

    if (cr & MX3_PWMCR_SWR)
    {
        LOG_E("software reset timeout\n");
    }
}
static void imx6ull_pwm_wait_fifo_slot(PWM_Type *base, struct rt_pwm_configuration *configuration)
{
    unsigned int period_ms = 0;
    int fifoav = 0;
    uint32_t sr = 0;

    sr = base->PWMSR;
    fifoav = sr & 0x7;
    if (fifoav == MX3_PWMSR_FIFOAV_4WORDS) {
        period_ms = configuration->period / NSEC_PER_MSEC;
        rt_thread_mdelay(period_ms);

        sr = base->PWMSR;
        if (fifoav == (sr & 0x7))
        {
            LOG_E("there is no free FIFO slot\n");
        }
    }
}

static rt_err_t imx6ull_pwm_enable(struct rt_device_pwm *device, rt_bool_t enable)
{
    PWM_Type *base = (PWM_Type *)device->parent.user_data;

    if (!enable)
    {
        pwm_stop_timer(base);
    }
    else
    {
        pwm_start_timer(base);
    }

    return RT_EOK;
}

static rt_err_t imx6ull_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    uint32_t period = 0, prescaler = 0, val = 0;
    uint64_t tmp = 0;
    PWM_Type *base = (PWM_Type *)device->parent.user_data;
    uint32_t pwm_src_clk;

    pwm_src_clk = PWM_SRC_CLK_FREQ / 1000000;

    val = base->PWMCR;
    prescaler = ((val >> 4) & 0xfff)+1;
    val = base->PWMPR;
    period = val >= IMX_PWMPR_MAX ? IMX_PWMPR_MAX : val;

    tmp = NSEC_PER_SEC * (uint64_t)(period + 2) * prescaler;

    configuration->period = (tmp) / pwm_src_clk;

    val = base->PWMSAR;

    tmp = NSEC_PER_SEC * (uint64_t)(val) * prescaler;

    configuration->pulse = (tmp) / pwm_src_clk;

    return RT_EOK;
}

static rt_err_t imx6ull_pwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    RT_ASSERT(configuration->period > 0);
    RT_ASSERT(configuration->pulse <= configuration->period);

    PWM_Type *base = (PWM_Type *)device->parent.user_data;
    uint32_t period_cycles = 0, duty_cycles = 0, prescale = 0;
    uint32_t cr = 0;
    uint32_t pwm_src_clk = 0;

    pwm_src_clk = PWM_SRC_CLK_FREQ / 1000000;
    period_cycles = pwm_src_clk * configuration->period / NSEC_PER_SEC;
    prescale = period_cycles / 0x10000 + 1;
    period_cycles /= prescale;

    duty_cycles = configuration->pulse * pwm_src_clk / NSEC_PER_SEC ;
    duty_cycles /= prescale;

    /*
     * according to imx pwm RM, the real period value should be PERIOD
     * value in PWMPR plus 2.
     */
    if (period_cycles > 2)
    {
        period_cycles -= 2;
    }
    else
    {
        period_cycles = 0;
    }

    if (((base->PWMCR) & 0x1) == 1)
    {
        imx6ull_pwm_wait_fifo_slot(base, configuration);
    }
    else
    {
        pwm_start_timer(base);
        imx6ull_pwm_reset(base);
    }

    base->PWMSAR = duty_cycles;
    base->PWMPR = period_cycles;

    cr = ((prescale -1 ) << 4) |
         MX3_PWMCR_STOPEN | MX3_PWMCR_DOZEN | MX3_PWMCR_WAITEN | MX3_PWMCR_CLKSRC | MX3_PWMCR_DBGEN;

    cr |= MX3_PWMCR_EN;

    base->PWMCR = cr;
    return RT_EOK;
}

static rt_err_t imx6ull_drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return imx6ull_pwm_enable(device, RT_TRUE);
    case PWM_CMD_DISABLE:
        return imx6ull_pwm_enable(device, RT_FALSE);
    case PWM_CMD_SET:
        return imx6ull_pwm_set(device, configuration);
    case PWM_CMD_GET:
        return imx6ull_pwm_get(device, configuration);
    default:
        return RT_EINVAL;
    }
}

static rt_err_t imx6ull_drv_pwm_init(PWM_Type *base)
{
    pwm_config_t PwmConfig;

    pwm_get_default_config(&PwmConfig);

    if (pwm_init(base, &PwmConfig) == kStatus_Fail)
    {
        LOG_E("init pwm failed \n");
        return RT_ERROR;
    }

    return RT_EOK;
}

int imx6ull_pwm_gpio_init(void)
{
#ifdef BSP_USING_PWM1
    struct imx6ull_iomuxc gpio;

    gpio.muxRegister = 0x020E007C;
    gpio.muxMode = 0x0;
    gpio.inputRegister = 0x00000000;
    gpio.inputDaisy = 0x0;
    gpio.configRegister = 0x020E0308;
    gpio.inputOnfield = 0;
    gpio.configValue = IOMUXC_SW_PAD_CTL_PAD_DSE(2U) | IOMUXC_SW_PAD_CTL_PAD_SPEED(2U);

    imx6ull_gpio_init(&gpio);
#endif
    return 0;
}

int rt_hw_pwm_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_PWM1

    static struct rt_device_pwm pwm1_device;
    PWM_Type *pwm1_base;

    imx6ull_pwm_gpio_init();
    pwm1_base = (PWM_Type *)rt_ioremap((void*)PWM1, 0x1000);
    if (imx6ull_drv_pwm_init(pwm1_base) != RT_EOK)
    {
        LOG_E("init pwm1 failed\n");
    }

    ret = rt_device_pwm_register(&pwm1_device, "pwm1", &imxrt_drv_ops, pwm1_base);

    if (ret != RT_EOK)
    {
        LOG_E("%s register failed", "pwm1");
    }

#endif /* BSP_USING_PWM1 */

#ifdef BSP_USING_PWM2

    static struct rt_device_pwm pwm2_device;

    imx6ull_pwm_gpio_init();
    if (imx6ull_drv_pwm_init(PWM2) != RT_EOK)
    {
        LOG_E("init pwm2 failed\n");
    }

    ret = rt_device_pwm_register(&pwm2_device, "pwm2", &imxrt_drv_ops, PWM2);

    if (ret != RT_EOK)
    {
        LOG_E("%s register failed", "pwm2");
    }
#endif /* BSP_USING_PWM2 */

#ifdef BSP_USING_PWM3

    static struct rt_device_pwm pwm3_device;

    imx6ull_pwm_gpio_init();
    if (imx6ull_drv_pwm_init(PWM3) != RT_EOK)
    {
        LOG_E("init pwm3 failed\n");
    }

    ret = rt_device_pwm_register(&pwm3_device, "pwm3", &imxrt_drv_ops, PWM3);

    if (ret != RT_EOK)
    {
        LOG_E("%s register failed", "pwm3");
    }

#endif /* BSP_USING_PWM3 */

#ifdef BSP_USING_PWM4

    static struct rt_device_pwm pwm4_device;

    imx6ull_pwm_gpio_init();
    if (imx6ull_drv_pwm_init(PWM4) != RT_EOK)
    {
        LOG_E("init pwm4 failed\n");
    }

    ret = rt_device_pwm_register(&pwm4_device, "pwm4", &imxrt_drv_ops, PWM4);

    if (ret != RT_EOK)
    {
        LOG_E("%s register failed", "pwm4");
    }
#endif /* BSP_USING_PWM4 */

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_pwm_init);
int set_pwm_default(void)
{
    int result = 0;
    struct rt_device_pwm *device = RT_NULL;

    device = (struct rt_device_pwm *)rt_device_find("pwm1");
    if (!device)
    {
        result = -RT_EIO;
        goto _exit;
    }

    result = rt_pwm_set(device, 1, 1000000, 500000);
    result = rt_pwm_enable(device, 1);
_exit:
    return result;

}
INIT_APP_EXPORT(set_pwm_default);
#endif /* BSP_USING_PWM */
