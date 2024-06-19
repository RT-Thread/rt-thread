/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-05-17     QT-one       first version
 */

#include <rtdbg.h>
#include "drv_adc.h"


#ifdef RT_USING_ADC
#if !defined(BSP_USING_ADC0) && !defined(BSP_USING_ADC1)
    #error "Please define at least one BSP_USING_ADCx"
    /* this driver can be disabled at menuconfig RT-Thread Components Device Drivers */
#endif

struct ht32_adc
{
    struct rt_adc_device ht32_adc_device;
    HT_ADC_TypeDef *adc_x;
    char *name;
};

/* ADC Peripheral List */
static struct ht32_adc ht32_adc_obj[] =
{
#ifdef BSP_USING_ADC0
    {
        .adc_x        = HT_ADC0,
        .name         = BSP_USING_ADC0_NAME,
    },
#endif

#ifdef BSP_USING_ADC1
    {
        .adc_x        = HT_ADC1,
        .name         = BSP_USING_ADC1_NAME,
    },
#endif
};

static rt_err_t ht32_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    HT_ADC_TypeDef *adc_x;
    RT_ASSERT(device != RT_NULL);
    adc_x = (HT_ADC_TypeDef*)device->parent.user_data;

    if(enabled)
    {
        ht32_adc_gpio_init(adc_x,channel);
        /* Configure the CK_ADCn prescaler */
#ifdef BSP_USING_ADC0
        if(HT_ADC0 == adc_x)
        {
            CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC0,CKCU_ADCPRE_DIV64);
        }
#endif
#ifdef BSP_USING_ADC1
        if(HT_ADC1 == adc_x)
        {
            CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC1,CKCU_ADCPRE_DIV64);
        }
#endif
        /* Configure conversion mode and sequence length (number of conversion channels) */
        ADC_RegularGroupConfig(adc_x,ONE_SHOT_MODE,1,0);

#ifdef SOC_SERIES_HT32F5
        /* Configuring the Sampling Time */
        ADC_SamplingTimeConfig(adc_x,0);
        /* Configuring Channel Priority */
        ADC_RegularChannelConfig(adc_x,channel,0);
#endif
#ifdef SOC_SERIES_HT32F1
        /* Configuring Channel Priority */
        ADC_RegularChannelConfig(adc_x,channel,0,0);
#endif
        /* Configuring the Trigger Source */
        ADC_RegularTrigConfig(adc_x,ADC_TRIG_SOFTWARE);
        /* Enable ADC */
        ADC_Cmd(adc_x,ENABLE);
    }
    else
    {
        /* Disable ADC */
        ADC_Cmd(adc_x,DISABLE);
    }
    return RT_EOK;
}

static rt_err_t ht32_adc_convert(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    HT_ADC_TypeDef *adc_x;
    rt_uint32_t timeout = 0;
    FlagStatus adc_writ_flag = RESET;
    RT_ASSERT(device != RT_NULL);
    adc_x = (HT_ADC_TypeDef*)device->parent.user_data;

    /* Toggle the acquisition channel */
#ifdef SOC_SERIES_HT32F5
    ADC_RegularChannelConfig(adc_x,channel,0);
#endif
#ifdef SOC_SERIES_HT32F1
    ADC_RegularChannelConfig(adc_x,channel,0,0);
#endif

    /* enable Software triggered */
    ADC_SoftwareStartConvCmd(adc_x,ENABLE);
    while((!adc_writ_flag) && (timeout < 0xFFFF))
    {
        /* Wait for the conversion to complete */
        adc_writ_flag = ADC_GetFlagStatus(adc_x,ADC_FLAG_SINGLE_EOC);
        timeout++;
    }
    if(timeout >= 0xFFFF)
    {
        LOG_D("channel%d converts timeout, please confirm adc_x enabled or not", channel);
        /* disable Software triggered */
        ADC_SoftwareStartConvCmd(adc_x,DISABLE);
        return -RT_ERROR;
    }
    /* clear ADC_FLAG_SINGLE_EOC flag */
    ADC_ClearIntPendingBit(adc_x,ADC_FLAG_SINGLE_EOC);
    /* get adc value */
    *value = ADC_GetConversionData(adc_x,ADC_REGULAR_DATA0);
    /* disable Software triggered */
    ADC_SoftwareStartConvCmd(adc_x,DISABLE);
    return RT_EOK;
}

static rt_uint8_t ht32_adc_get_resolution(struct rt_adc_device *device)
{
    return 0;
}

static rt_int16_t ht32_adc_get_vref(struct rt_adc_device *device)
{
    return 0;
}

/* ADC Device Operation Function Interface */
static const struct rt_adc_ops ht32_adc_ops =
{
    .enabled = ht32_adc_enabled,
    .convert = ht32_adc_convert,
    .get_resolution = ht32_adc_get_resolution,
    .get_vref = ht32_adc_get_vref,
};

static int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    int i = 0;
    for (i = 0; i < sizeof(ht32_adc_obj) / sizeof(ht32_adc_obj[0]); i++)
    {
        /* register ADC device */
        if (rt_hw_adc_register(&ht32_adc_obj[i].ht32_adc_device, ht32_adc_obj[i].name, &ht32_adc_ops, ht32_adc_obj[i].adc_x) == RT_EOK)
        {
            LOG_D("%s register success", ht32_adc_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", ht32_adc_obj[i].name);
            result = -RT_ERROR;
        }
    }
    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* RT_USING_ADC */
