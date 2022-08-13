/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-07-15     Aligagago         add apm32F4 serie MCU support
 */

#include <board.h>

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3)

//#define DRV_DEBUG
#define LOG_TAG               "drv.adc"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#define DRV_ADC_CHANNEL_MAX_NUM  14
#define DRV_ADC_TIME_OUT         0xFFF

#define _ADC_GET_PORT(pin_num) ((GPIO_T *)(GPIOA_BASE + (0x400u * (((pin_num) >> 4) & 0xFu))))
#define _ADC_GET_PIN(pin_num)  ((uint16_t)(1u << ((pin_num) & 0xFu)))

struct apm32_adc
{
    const char *name;
    ADC_T *adc;
    ADC_Config_T adc_config;
    rt_base_t channel_pin[DRV_ADC_CHANNEL_MAX_NUM];
    struct rt_adc_device adc_dev;
};
#ifdef APM32F10X_HD
static struct apm32_adc adc_config[] =
{
#ifdef BSP_USING_ADC1
    {
        "adc1",
        ADC1,
        {
            ADC_MODE_INDEPENDENT,
            DISABLE,
            DISABLE,
            ADC_EXT_TRIG_CONV_None,
            ADC_DATA_ALIGN_RIGHT,
            1
        },
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3), GET_PIN(A, 4),
            GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7), GET_PIN(B, 0), GET_PIN(B, 1),
            GET_PIN(C, 0), GET_PIN(C, 1), GET_PIN(C, 2), GET_PIN(C, 3)
        },
        RT_NULL
    },
#endif
#ifdef BSP_USING_ADC2
    {
        "adc2",
        ADC2,
        {
            ADC_MODE_INDEPENDENT,
            DISABLE,
            DISABLE,
            ADC_EXT_TRIG_CONV_None,
            ADC_DATA_ALIGN_RIGHT,
            1
        },
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3), GET_PIN(A, 4),
            GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7), GET_PIN(B, 0), GET_PIN(B, 1),
            GET_PIN(C, 0), GET_PIN(C, 1), GET_PIN(C, 2), GET_PIN(C, 3)
        },
        RT_NULL
    },
#endif
#ifdef BSP_USING_ADC3
    {
        "adc3",
        ADC3,
        {
            ADC_MODE_INDEPENDENT,
            DISABLE,
            DISABLE,
            ADC_EXT_TRIG_CONV_None,
            ADC_DATA_ALIGN_RIGHT,
            1
        },
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3), GET_PIN(F, 6),
            GET_PIN(F, 7), GET_PIN(F, 8), GET_PIN(F, 9), GET_PIN(F, 10)
        },
        RT_NULL
    },
#endif
};
#elif APM32F40X
static struct apm32_adc adc_config[] =
{
#ifdef BSP_USING_ADC1
    {
        "adc1",
        ADC1,
        {
            ADC_RESOLUTION_12BIT,
            DISABLE,
            DISABLE,
            ADC_EXT_TRIG_EDGE_NONE,
            ADC_EXT_TRIG_CONV_TMR1_CC1,
            ADC_DATA_ALIGN_RIGHT,
            1
        },
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3), GET_PIN(A, 4),
            GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7), GET_PIN(B, 0), GET_PIN(B, 1),
            GET_PIN(C, 0), GET_PIN(C, 1), GET_PIN(C, 2), GET_PIN(C, 3)
        },
        RT_NULL
    },
#endif
#ifdef BSP_USING_ADC2
    {
        "adc2",
        ADC2,
        {
            ADC_RESOLUTION_12BIT,
            DISABLE,
            DISABLE,
            ADC_EXT_TRIG_EDGE_NONE,
            ADC_EXT_TRIG_CONV_TMR1_CC1,
            ADC_DATA_ALIGN_RIGHT,
            1
        },
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3), GET_PIN(A, 4),
            GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7), GET_PIN(B, 0), GET_PIN(B, 1),
            GET_PIN(C, 0), GET_PIN(C, 1), GET_PIN(C, 2), GET_PIN(C, 3)
        },
        RT_NULL
    },
#endif
#ifdef BSP_USING_ADC3
    {
        "adc3",
        ADC3,
        {
            ADC_RESOLUTION_12BIT,
            DISABLE,
            DISABLE,
            ADC_EXT_TRIG_EDGE_NONE,
            ADC_EXT_TRIG_CONV_TMR1_CC1,
            ADC_DATA_ALIGN_RIGHT,
            1
        },
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3), GET_PIN(F, 6),
            GET_PIN(F, 7), GET_PIN(F, 8), GET_PIN(F, 9), GET_PIN(F, 10), GET_PIN(F, 3),
            GET_PIN(C, 0), GET_PIN(C, 1), GET_PIN(C, 2), GET_PIN(C, 3)
        },
        RT_NULL
    },
#endif
};
#endif
static rt_err_t _adc_channel_check(struct rt_adc_device *device, rt_uint32_t channel)
{
    struct apm32_adc *adc_cfg = ((struct apm32_adc *)device->parent.user_data);
#ifdef APM32F10X_HD
    if (adc_cfg->adc == ADC3)
    {
        if (channel <= 8)
        {
            return RT_EOK;
        }
    }
    else
    {
        if (channel <= 13)
        {
            return RT_EOK;
        }
    }
#elif APM32F40X
    if (channel <= 13)
    {
        return RT_EOK;
    }
#endif
    LOG_E("channel %d of %s is not supported.", channel, adc_cfg->name);
    return -RT_ERROR;
}

static rt_err_t _adc_gpio_init(struct rt_adc_device *device, rt_uint32_t channel)
{
    struct apm32_adc *adc_cfg = ((struct apm32_adc *)device->parent.user_data);
    GPIO_Config_T hw_gpio_config;

    if (_adc_channel_check(device, channel) != RT_EOK)
    {
        return -RT_ERROR;
    }
#ifdef APM32F10X_HD
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA << ((adc_cfg->channel_pin[channel] >> 4) & 0xFu));
    hw_gpio_config.mode = GPIO_MODE_ANALOG;
#elif APM32F40X
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA << ((adc_cfg->channel_pin[channel] >> 4) & 0xFu));
    hw_gpio_config.mode = GPIO_MODE_AN;
#endif
    hw_gpio_config.pin = _ADC_GET_PIN(adc_cfg->channel_pin[channel]);
    GPIO_Config(_ADC_GET_PORT(adc_cfg->channel_pin[channel]), &hw_gpio_config);

    return RT_EOK;
}

/**
 * @brief    This function will control the adc to enable or disable.
 *
 * @param    device is a pointer to adc device.
 *
 * @param    channel is the adc channel.
 *
 * @param    enabled is the status to indicate enable or disable.
 *
 * @return   RT_EOK indicates successful enable or disable adc, other value indicates failed.
 */
static rt_err_t _adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    struct apm32_adc *adc_cfg = ((struct apm32_adc *)device->parent.user_data);

    RT_ASSERT(device != RT_NULL);

    if (enabled)
    {
        if (adc_cfg->adc == ADC1)
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC1);
        }
        else if (adc_cfg->adc == ADC2)
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC2);
        }
        else
        {
            RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_ADC3);
        }
        if (_adc_gpio_init(device, channel) != RT_EOK)
        {
            return -RT_ERROR;
        }

        ADC_Config(adc_cfg->adc, &adc_cfg->adc_config);

        ADC_Enable(adc_cfg->adc);
    }
    else
    {
        ADC_Disable(adc_cfg->adc);
    }

    return RT_EOK;
}

/**
 * @brief    This function will get the adc conversion value.
 *
 * @param    device is a pointer to adc device.
 *
 * @param    channel is the adc channel.
 *
 * @param    value is a pointer to the adc conversion value.
 *
 * @return   RT_EOK indicates successful get adc value, other value indicates failed.
 */
static rt_err_t _adc_get_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    struct apm32_adc *adc_cfg = ((struct apm32_adc *)device->parent.user_data);
    volatile rt_uint32_t counter = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    if (_adc_channel_check(device, channel) != RT_EOK)
    {
        return -RT_ERROR;
    }
#ifdef APM32F10X_HD
    ADC_ConfigRegularChannel(adc_cfg->adc, channel, 1, ADC_SAMPLETIME_13CYCLES5);

    ADC_StartCalibration(adc_cfg->adc);
    /* Check the end of ADC calibration */
    while (ADC_ReadCalibrationStartFlag(adc_cfg->adc))
    {
        if (++counter > DRV_ADC_TIME_OUT)
        {
            return RT_ETIMEOUT;
        }
    }

    ADC_EnableSoftwareStartConv(adc_cfg->adc);
#elif APM32F40X
    ADC_ConfigRegularChannel(adc_cfg->adc, channel, 1, ADC_SAMPLETIME_15CYCLES);
    ADC_SoftwareStartConv(adc_cfg->adc);
#endif
    counter = 0;
    while (!ADC_ReadStatusFlag(adc_cfg->adc, ADC_FLAG_EOC))
    {
        if (++counter > DRV_ADC_TIME_OUT)
        {
            return RT_ETIMEOUT;
        }
    }

    *value = ADC_ReadConversionValue(adc_cfg->adc);

    return RT_EOK;
}

static const struct rt_adc_ops _adc_ops =
{
    .enabled = _adc_enabled,
    .convert = _adc_get_value,
};

/**
 * @brief    ADC initialization function.
 *
 * @return   RT_EOK indicates successful initialization, other value indicates failed;
 */
static int rt_hw_adc_init(void)
{
    rt_err_t result = RT_EOK;
    rt_size_t obj_num = sizeof(adc_config) / sizeof(struct apm32_adc);
    rt_uint32_t i = 0;

    for (i = 0; i < obj_num; i++)
    {
        /* register ADC device */
        if (rt_hw_adc_register(&adc_config[i].adc_dev, adc_config[i].name, &_adc_ops, adc_config))
        {
            LOG_D("%s init success", adc_config[i].name);
        }
        else
        {
            LOG_D("%s init failed", adc_config[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADCX */
