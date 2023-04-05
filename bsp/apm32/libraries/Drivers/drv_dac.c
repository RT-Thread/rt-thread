/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-07-15     Aligagago         add APM32F4 series MCU support
 * 2022-12-26     luobeihai         add APM32F0 series MCU support
 * 2023-03-27     luobeihai         add APM32E1 series MCU support
 */

#include <board.h>

#if defined(BSP_USING_DAC1)

#define DBG_TAG               "drv.dac"
#define DBG_LVL               DBG_LOG
#include <rtdbg.h>

struct apm32_dac
{
    const char *name;
    DAC_T *dac;
    DAC_Config_T dac_conf;
    struct rt_dac_device dac_dev;
};

static struct apm32_dac dac_config[] =
{

#if defined (BSP_USING_DAC1)
    {
#if defined (SOC_SERIES_APM32F0)
        "dac1",
        DAC,
        {
            DAC_TRIGGER_SOFTWARE,
            DAC_OUTPUTBUFF_DISABLE,
            DAC_WAVE_GENERATION_NONE,
            DAC_TRIANGLEAMPLITUDE_4095,
        },
#elif  defined (SOC_SERIES_APM32F1) || defined (SOC_SERIES_APM32E1) || defined (SOC_SERIES_APM32F4)
        "dac1",
        DAC,
        {
            DAC_TRIGGER_SOFT,
            DAC_OUTPUT_BUFFER_DISABLE,
            DAC_WAVE_GENERATION_NONE,
            DAC_TRIANGLE_AMPLITUDE_4095,
        },
#endif
    }
#endif
};

/**
 * @brief    This function will enable dac.
 *
 * @param    device is a pointer to dac device.
 *
 * @param    channel is the dac channel.
 *
 * @return   RT_EOK indicates successful enable dac, other value indicates failed.
 */
static rt_err_t apm32_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    GPIO_Config_T GPIO_ConfigStruct;
    struct apm32_dac *cfg = (struct apm32_dac *)device->parent.user_data;
#if defined (SOC_SERIES_APM32F1) || defined (SOC_SERIES_APM32E1)
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    GPIO_ConfigStruct.mode = GPIO_MODE_ANALOG;
#elif defined (SOC_SERIES_APM32F4)
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);
    GPIO_ConfigStruct.mode = GPIO_MODE_AN;
#elif defined (SOC_SERIES_APM32F0)
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    GPIO_ConfigStruct.mode = GPIO_MODE_AN;
#endif
    if (channel == 1)
    {
        GPIO_ConfigStruct.pin = GPIO_PIN_4;
        GPIO_Config(GPIOA, &GPIO_ConfigStruct);

        DAC_Config(DAC_CHANNEL_1, &cfg->dac_conf);
        DAC_Enable(DAC_CHANNEL_1);
    }
    else if (channel == 2)
    {
        GPIO_ConfigStruct.pin = GPIO_PIN_5;
        GPIO_Config(GPIOA, &GPIO_ConfigStruct);

        DAC_Config(DAC_CHANNEL_2, &cfg->dac_conf);
        DAC_Enable(DAC_CHANNEL_2);
    }
    else
    {
        LOG_E("dac channel must be 1 or 2.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief    This function will disable dac.
 *
 * @param    device is a pointer to dac device.
 *
 * @param    channel is the dac channel.
 *
 * @return   RT_EOK indicates successful disable dac, other value indicates failed.
 */
static rt_err_t apm32_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    if (channel == 1)
    {
        DAC_Disable(DAC_CHANNEL_1);
    }
    else if (channel == 2)
    {
        DAC_Disable(DAC_CHANNEL_2);
    }
    else
    {
        LOG_E("dac channel must be 1 or 2.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief    This function will set the vaule of dac.
 *
 * @param    device is a pointer to dac device.
 *
 * @param    channel is the dac channel.
 *
 * @param    value is a pointer to dac value to be convert.
 *
 * @return   RT_EOK indicates successful set dac value, other value indicates failed.
 */
static rt_err_t apm32_dac_set_value(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
#if defined (SOC_SERIES_APM32F0)
    if (channel == 1)
    {
        DAC_ConfigChannel1Data(DAC_ALIGN_12B_R, *value);
        DAC_EnableSoftwareTrigger(DAC_CHANNEL_1);
    }
    else if (channel == 2)
    {
        DAC_ConfigChannel2Data(DAC_ALIGN_12B_R, *value);
        DAC_EnableSoftwareTrigger(DAC_CHANNEL_2);
    }
    else
    {
        LOG_E("dac channel must be 1 or 2.");
        return -RT_ERROR;
    }
#elif defined (SOC_SERIES_APM32F1) || defined (SOC_SERIES_APM32E1) || defined (SOC_SERIES_APM32F4)
    if (channel == 1)
    {
        DAC_ConfigChannel1Data(DAC_ALIGN_12BIT_R, *value);
        DAC_EnableSoftwareTrigger(DAC_CHANNEL_1);
    }
    else if (channel == 2)
    {
        DAC_ConfigChannel2Data(DAC_ALIGN_12BIT_R, *value);
        DAC_EnableSoftwareTrigger(DAC_CHANNEL_2);
    }
    else
    {
        LOG_E("dac channel must be 1 or 2.");
        return -RT_ERROR;
    }
#endif
    return RT_EOK;
}

static const struct rt_dac_ops apm32_dac_ops =
{
    .disabled = apm32_dac_disabled,
    .enabled  = apm32_dac_enabled,
    .convert  = apm32_dac_set_value,
};

/**
 * @brief    DAC initialization function.
 *
 * @return   RT_EOK indicates successful initialization, other value indicates failed;
 */
static int rt_hw_dac_init(void)
{
    rt_err_t result = RT_EOK;
    rt_size_t obj_num = sizeof(dac_config) / sizeof(struct apm32_dac);
    rt_uint32_t i = 0;

    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_DAC);

    for (i = 0; i < obj_num; i++)
    {
        /* register dac device */
        if (rt_hw_dac_register(&dac_config[i].dac_dev, dac_config[i].name, &apm32_dac_ops, dac_config) == RT_EOK)
        {
            LOG_D("%s init success", dac_config[i].name);
        }
        else
        {
            LOG_E("%s init failed", dac_config[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_dac_init);

#endif /* BSP_USING_DACX */
