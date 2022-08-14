/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-5-26      lik          first version
 */

#include "drv_adc.h"

#ifdef RT_USING_ADC
#ifdef BSP_USING_ADC

//#define DRV_DEBUG
#define LOG_TAG "drv.adc"
#include <drv_log.h>

static struct swm_adc_cfg adc_cfg[] =
    {
#ifdef BSP_USING_ADC0
        ADC0_CFG,
#endif
#ifdef BSP_USING_ADC1
        ADC1_CFG,
#endif

};

static struct swm_adc adc_drv[sizeof(adc_cfg) / sizeof(adc_cfg[0])];

static rt_err_t swm_adc_enabled(struct rt_adc_device *adc_device, rt_uint32_t channel, rt_bool_t enabled)
{
    struct swm_adc_cfg *cfg = RT_NULL;
    RT_ASSERT(adc_device != RT_NULL);
    cfg = adc_device->parent.user_data;

    if (enabled)
    {
        ADC_Open(cfg->ADCx);
    }
    else
    {
        ADC_Close(cfg->ADCx);
    }

    return RT_EOK;
}

static rt_uint32_t swm_adc_get_channel(rt_uint32_t channel)
{
    rt_uint32_t swm_channel = 0;

    switch (channel)
    {
    case 0:
        swm_channel = ADC_CH0;
        break;
    case 1:
        swm_channel = ADC_CH1;
        break;
    case 2:
        swm_channel = ADC_CH2;
        break;
    case 3:
        swm_channel = ADC_CH3;
        break;
    case 4:
        swm_channel = ADC_CH4;
        break;
    case 5:
        swm_channel = ADC_CH5;
        break;
    case 6:
        swm_channel = ADC_CH6;
        break;
    case 7:
        swm_channel = ADC_CH7;
        break;
    }

    return swm_channel;
}

static rt_err_t swm_get_adc_value(struct rt_adc_device *adc_device, rt_uint32_t channel, rt_uint32_t *value)
{
    uint32_t adc_chn;
    struct swm_adc_cfg *cfg = RT_NULL;
    RT_ASSERT(adc_device != RT_NULL);
    RT_ASSERT(value != RT_NULL);
    cfg = adc_device->parent.user_data;

    if (channel < 8)
    {
        /* set stm32 ADC channel */
        adc_chn = swm_adc_get_channel(channel);
    }
    else
    {
        LOG_E("ADC channel must be between 0 and 7.");
        return -RT_ERROR;
    }

    /* start ADC */
    ADC_Start(cfg->ADCx);
    /* Wait for the ADC to convert */
    while ((cfg->ADCx->CH[channel].STAT & 0x01) == 0)
        ;

    /* get ADC value */
    *value = (rt_uint32_t)ADC_Read(cfg->ADCx, adc_chn);

    return RT_EOK;
}

static const struct rt_adc_ops swm_adc_ops =
    {
        .enabled = swm_adc_enabled,
        .convert = swm_get_adc_value,
};

static int rt_hw_adc_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(adc_cfg) / sizeof(adc_cfg[0]); i++)
    {
        /* ADC init */
        adc_drv[i].cfg = &adc_cfg[i];

        if (adc_drv[i].cfg->ADCx == ADC0)
        {
#ifdef BSP_USING_ADC0_CHN0
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH0;
#endif
#ifdef BSP_USING_ADC0_CHN1
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH1;
#endif
#ifdef BSP_USING_ADC0_CHN2
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH2;
#endif
#ifdef BSP_USING_ADC0_CHN3
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH3;
#endif
#ifdef BSP_USING_ADC0_CHN4
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH4;
            PORT_Init(PORTA, PIN12, PORTA_PIN12_ADC0_IN4, 0); //PA.12 => ADC0.CH4
#endif
#ifdef BSP_USING_ADC0_CHN5
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH5;
            PORT_Init(PORTA, PIN11, PORTA_PIN11_ADC0_IN5, 0); //PA.11 => ADC0.CH5
#endif
#ifdef BSP_USING_ADC0_CHN6
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH6;
            PORT_Init(PORTA, PIN10, PORTA_PIN10_ADC0_IN6, 0); //PA.10 => ADC0.CH6
#endif
#ifdef BSP_USING_ADC0_CHN7
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH7;
            PORT_Init(PORTA, PIN9, PORTA_PIN9_ADC0_IN7, 0); //PA.9  => ADC0.CH7
#endif
        }
        else if (adc_drv[i].cfg->ADCx == ADC1)
        {
#ifdef BSP_USING_ADC1_CHN0
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH0;
            PORT_Init(PORTC, PIN7, PORTC_PIN7_ADC1_IN0, 0); //PC.7 => ADC1.CH0
#endif
#ifdef BSP_USING_ADC1_CHN1
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH1;
            PORT_Init(PORTC, PIN6, PORTC_PIN6_ADC1_IN1, 0); //PC.6 => ADC1.CH1
#endif
#ifdef BSP_USING_ADC1_CHN2
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH2;
            PORT_Init(PORTC, PIN5, PORTC_PIN5_ADC1_IN2, 0); //PC.5 => ADC1.CH2
#endif
#ifdef BSP_USING_ADC1_CHN3
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH3;
            PORT_Init(PORTC, PIN4, PORTC_PIN4_ADC1_IN3, 0); //PC.4 => ADC1.CH3
#endif
#ifdef BSP_USING_ADC1_CHN4
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH4;
            PORT_Init(PORTN, PIN0, PORTN_PIN0_ADC1_IN4, 0); //PN.0 => ADC1.CH4
#endif
#ifdef BSP_USING_ADC1_CHN5
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH5;
            PORT_Init(PORTN, PIN1, PORTN_PIN1_ADC1_IN5, 0); //PN.1 => ADC1.CH5
#endif
#ifdef BSP_USING_ADC1_CHN6
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH6;
            PORT_Init(PORTN, PIN2, PORTN_PIN2_ADC1_IN6, 0); //PN.2 => ADC1.CH6
#endif
#ifdef BSP_USING_ADC1_CHN7
            adc_drv[i].cfg->adc_initstruct.channels |= ADC_CH7;
#endif
        }

        ADC_Init(adc_drv[i].cfg->ADCx, &(adc_drv[i].cfg->adc_initstruct));
        ADC_Open(adc_drv[i].cfg->ADCx);
        /* register ADC device */
        if (rt_hw_adc_register(&adc_drv[i].adc_device, adc_drv[i].cfg->name, &swm_adc_ops, adc_drv[i].cfg) == RT_EOK)
        {
            LOG_D("%s init success", adc_drv[i].cfg->name);
        }
        else
        {
            LOG_E("%s register failed", adc_drv[i].cfg->name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);
#endif /* BSP_USING_ADC */
#endif /* RT_USING_ADC */
