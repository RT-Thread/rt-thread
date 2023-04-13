/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 * 2023-01-31     shelton      add support f421/f425
 * 2023-04-08     shelton      add support f423
 */

#include "drv_common.h"
#include "drv_adc.h"

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || \
    defined(BSP_USING_ADC3)

//#define DRV_DEBUG
#define LOG_TAG             "drv.adc"
#include <drv_log.h>

struct at32_adc
{
    struct rt_adc_device at32_adc_device;
    adc_type *adc_x;
    char *name;
};

static struct at32_adc at32_adc_obj[] =
{
#ifdef BSP_USING_ADC1
    ADC1_CONFIG,
#endif

#ifdef BSP_USING_ADC2
    ADC2_CONFIG,
#endif

#ifdef BSP_USING_ADC3
    ADC3_CONFIG,
#endif
};

static rt_err_t at32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    adc_type *adc_x;
    adc_base_config_type adc_config_struct;
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F423)
    adc_common_config_type adc_common_struct;
    adc_common_default_para_init(&adc_common_struct);
#endif

    RT_ASSERT(device != RT_NULL);
    adc_x = device->parent.user_data;

    at32_msp_adc_init(adc_x);

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437)
    /* config combine mode */
    adc_common_struct.combine_mode = ADC_INDEPENDENT_MODE;
    /* config division, adcclk is division by hclk */
    adc_common_struct.div = ADC_HCLK_DIV_4;
    /* config common dma mode,it's not useful in independent mode */
    adc_common_struct.common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;
    /* config common dma request repeat */
    adc_common_struct.common_dma_request_repeat_state = FALSE;
    /* config adjacent adc sampling interval,it's useful for ordinary shifting mode */
    adc_common_struct.sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;
    /* config inner temperature sensor and vintrv */
    adc_common_struct.tempervintrv_state = FALSE;
    /* config voltage battery */
    adc_common_struct.vbat_state = FALSE;
    adc_common_config(&adc_common_struct);
#elif defined (SOC_SERIES_AT32F423)
    /* config division, adcclk is division by hclk */
    adc_common_struct.div = ADC_HCLK_DIV_4;
    /* config inner temperature sensor and vintrv */
    adc_common_struct.tempervintrv_state = FALSE;
    adc_common_config(&adc_common_struct);
#else
#if !defined (SOC_SERIES_AT32F415) && !defined (SOC_SERIES_AT32F421) && \
    !defined (SOC_SERIES_AT32F425)
    adc_combine_mode_select(ADC_INDEPENDENT_MODE);
#endif
    adc_ordinary_conversion_trigger_set(adc_x, ADC12_ORDINARY_TRIG_SOFTWARE, TRUE);
#endif

    /* adc_x configuration */
    adc_base_default_para_init(&adc_config_struct);
    adc_config_struct.data_align = ADC_RIGHT_ALIGNMENT;
    adc_config_struct.ordinary_channel_length = 1;
    adc_config_struct.repeat_mode = FALSE;
    adc_config_struct.sequence_mode = FALSE;
    adc_base_config(adc_x, &adc_config_struct);

    if (!enabled)
    {
        /* disable adc_x */
        adc_enable(adc_x, FALSE);
    }
    else
    {
        /* enable adc_x */
        adc_enable(adc_x, TRUE);

        /* enable adc_x calibration */
        adc_calibration_init(adc_x);
        /* check the end of adc_x reset calibration register */
        while(adc_calibration_init_status_get(adc_x) == SET)
        {
        }
        /* start adc_x calibration */
         adc_calibration_start(adc_x);
        /* check the end of adc_x calibration */
        while(adc_calibration_status_get(adc_x) == SET)
        {
        }
    }

    return RT_EOK;
}

static rt_err_t at32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    adc_type *adc_x;
    rt_uint32_t timeout = 0;

    RT_ASSERT(device != RT_NULL);
    adc_x = device->parent.user_data;

    /* adc_x regular channels configuration */
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F423)
    adc_ordinary_channel_set(adc_x, (adc_channel_select_type)channel, 1, ADC_SAMPLETIME_247_5);
#else
    adc_ordinary_channel_set(adc_x, (adc_channel_select_type)channel, 1, ADC_SAMPLETIME_239_5);
#endif

    /* start adc_x software conversion */
    adc_ordinary_software_trigger_enable(adc_x, TRUE);

    /* wait for the adc to convert */
#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F423)
    while((adc_flag_get(adc_x, ADC_OCCE_FLAG) == RESET) && timeout < 0xFFFF)
#else
    while((adc_flag_get(adc_x, ADC_CCE_FLAG) == RESET) && timeout < 0xFFFF)
#endif
    {
        timeout ++;
    }

    if(timeout >= 0xFFFF)
    {
        LOG_D("channel%d converts timeout, please confirm adc_x enabled or not", channel);
    }

    /* get adc value */
    *value = adc_ordinary_conversion_data_get(adc_x);

    return RT_EOK;
}

static const struct rt_adc_ops at_adc_ops =
{
    .enabled = at32_adc_enabled,
    .convert = at32_get_adc_value,
};

static int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    int i = 0;

    for (i = 0; i < sizeof(at32_adc_obj) / sizeof(at32_adc_obj[0]); i++)
    {
        /* register ADC device */
        if (rt_hw_adc_register(&at32_adc_obj[i].at32_adc_device, at32_adc_obj[i].name, &at_adc_ops, at32_adc_obj[i].adc_x) == RT_EOK)
        {
            LOG_D("%s register success", at32_adc_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", at32_adc_obj[i].name);
            result = -RT_ERROR;
        }

    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
