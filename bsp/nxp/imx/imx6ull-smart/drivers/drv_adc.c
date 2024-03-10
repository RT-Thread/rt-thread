/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-28     tyustli      first version
 *
 */

#include <rtthread.h>
#define RT_USING_ADC
#ifdef RT_USING_ADC

#define LOG_TAG             "drv.adc"
#include <drv_log.h>

#include <rtdevice.h>
#include <ioremap.h>

#include "fsl_adc.h"
#include "drv_adc.h"
#include <drv_common.h>
#include <drivers/adc.h>

static rt_err_t imx6ull_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    return RT_EOK;
}

static rt_err_t imx6ull_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    adc_channel_config_t adc_channel;
    ADC_Type *base;
    base = (ADC_Type *)(device->parent.user_data);

    adc_channel.channelNumber = channel;
    adc_channel.enableInterruptOnConversionCompleted = 0;

    ADC_SetChannelConfig(base, 0, &adc_channel);

    while (0U == ADC_GetChannelStatusFlags(base, 0))
    {
        continue;
    }

    *value = ADC_GetChannelConversionValue(base, 0);

    return RT_EOK;
}

#if defined(BSP_USING_ADC1_1) || defined(BSP_USING_ADC1_2) || defined(BSP_USING_ADC1_3) || defined(BSP_USING_ADC1_4)
static struct rt_adc_ops imx6ull_adc_ops =
{
    .enabled = imx6ull_adc_enabled,
    .convert = imx6ull_adc_convert,
};
#endif

int imx6ull_adc_gpio_init(void)
{
#ifdef BSP_USING_ADC1_1
    do {
        struct imx6ull_iomuxc gpio;
        uint32_t pin_fun_id[5]={IOMUXC_GPIO1_IO01_GPIO1_IO01};

        gpio.muxRegister = pin_fun_id[0];
        gpio.muxMode = pin_fun_id[1];
        gpio.inputRegister = pin_fun_id[2];
        gpio.inputDaisy = pin_fun_id[3];
        gpio.configRegister = pin_fun_id[4];
        gpio.inputOnfield = 0;
        gpio.configValue = IOMUXC_SW_PAD_CTL_PAD_DSE(2U) | IOMUXC_SW_PAD_CTL_PAD_SPEED(2U);

        imx6ull_gpio_init(&gpio);
    }while(0);
#endif

#ifdef BSP_USING_ADC1_2
    do {
        struct imx6ull_iomuxc gpio;
        uint32_t pin_fun_id[5]={IOMUXC_GPIO1_IO02_GPIO1_IO02};

        gpio.muxRegister = pin_fun_id[0];
        gpio.muxMode = pin_fun_id[1];
        gpio.inputRegister = pin_fun_id[2];
        gpio.inputDaisy = pin_fun_id[3];
        gpio.configRegister = pin_fun_id[4];
        gpio.inputOnfield = 0;
        gpio.configValue = IOMUXC_SW_PAD_CTL_PAD_DSE(2U) | IOMUXC_SW_PAD_CTL_PAD_SPEED(2U);

        imx6ull_gpio_init(&gpio);
    }while(0);
#endif

#ifdef BSP_USING_ADC1_3
    do {
        struct imx6ull_iomuxc gpio;
        uint32_t pin_fun_id[5]={IOMUXC_GPIO1_IO03_GPIO1_IO03};

        gpio.muxRegister = pin_fun_id[0];
        gpio.muxMode = pin_fun_id[1];
        gpio.inputRegister = pin_fun_id[2];
        gpio.inputDaisy = pin_fun_id[3];
        gpio.configRegister = pin_fun_id[4];
        gpio.inputOnfield = 0;
        gpio.configValue = IOMUXC_SW_PAD_CTL_PAD_DSE(2U) | IOMUXC_SW_PAD_CTL_PAD_SPEED(2U);

        imx6ull_gpio_init(&gpio);
    }while(0);
#endif

#ifdef BSP_USING_ADC1_4
    do {
        struct imx6ull_iomuxc gpio;
        uint32_t pin_fun_id[5]={IOMUXC_GPIO1_IO04_GPIO1_IO04};

        gpio.muxRegister = pin_fun_id[0];
        gpio.muxMode = pin_fun_id[1];
        gpio.inputRegister = pin_fun_id[2];
        gpio.inputDaisy = pin_fun_id[3];
        gpio.configRegister = pin_fun_id[4];
        gpio.inputOnfield = 0;
        gpio.configValue = IOMUXC_SW_PAD_CTL_PAD_DSE(2U) | IOMUXC_SW_PAD_CTL_PAD_SPEED(2U);

        imx6ull_gpio_init(&gpio);
    }while(0);
#endif

    return 0;
}

int rt_hw_adc_init(void)
{
    rt_err_t ret = RT_EOK;
    imx6ull_adc_gpio_init();

#if defined(BSP_USING_ADC1_1) || defined(BSP_USING_ADC1_2) || defined(BSP_USING_ADC1_3) || defined(BSP_USING_ADC1_4)
    static adc_config_t ADC1_config_value;
    static struct rt_adc_device adc1_device;
    ADC_Type *adc1_base;

    adc1_base = (ADC_Type *)rt_ioremap((void*)ADC1, 0x1000);

    ADC_GetDefaultConfig(&ADC1_config_value);
    ADC_Init(adc1_base, &ADC1_config_value);

    ADC_DoAutoCalibration(adc1_base);

    ret = rt_hw_adc_register(&adc1_device, "adc1", &imx6ull_adc_ops, adc1_base);

    if (ret != RT_EOK)
    {
        LOG_E("register adc1 device failed error code = %d\n", ret);
    }

#endif

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_adc_init);

void set_adc_default(void *parameter)
{
    int result = 0;

    result = result;
#ifdef BSP_USING_ADC1_1
    do {
        struct rt_adc_device *device = RT_NULL;
        device = (struct rt_adc_device *)rt_device_find("adc1");
        if (!device)
        {
            result = -RT_EIO;
            return;
        }

        result = rt_adc_enable(device, 1);
        result = rt_adc_read(device, 1);
        rt_kprintf("adc ch1 read result is %d\n",result);
    } while(0);

#endif

#ifdef BSP_USING_ADC1_2
    do {
        struct rt_adc_device *device = RT_NULL;
        device = (struct rt_adc_device *)rt_device_find("adc1");
        if (!device)
        {
            result = -RT_EIO;
            return;
        }

        result = rt_adc_enable(device, 2);
        result = rt_adc_read(device, 2);
        rt_kprintf("adc ch2 read result is %d\n",result);
    } while(0);
#endif

#ifdef BSP_USING_ADC1_3
    do {
        struct rt_adc_device *device = RT_NULL;
        device = (struct rt_adc_device *)rt_device_find("adc1");
        if (!device)
        {
            result = -RT_EIO;
            return;
        }

        result = rt_adc_enable(device, 3);
        result = rt_adc_read(device, 3);
        rt_kprintf("adc ch3 read result is %d\n",result);
    } while(0);
#endif

#ifdef BSP_USING_ADC1_4
    do {
        struct rt_adc_device *device = RT_NULL;
        device = (struct rt_adc_device *)rt_device_find("adc1");
        if (!device)
        {
            result = -RT_EIO;
            return;
        }

        result = rt_adc_enable(device, 4);
        result = rt_adc_read(device, 4);
        rt_kprintf("adc ch4 read result is %d\n",result);
    } while(0);
#endif
}

static int set_adc_init(void)
{
    rt_thread_t tid = rt_thread_create("adc_loop", set_adc_default, RT_NULL, 1024, 16, 20);
    RT_ASSERT(tid != RT_NULL);
    rt_thread_startup(tid);
    return(RT_EOK);
}
INIT_APP_EXPORT(set_adc_init);
#endif /* BSP_USING_ADC */
