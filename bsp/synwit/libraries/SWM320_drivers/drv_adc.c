/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
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

#if !defined(BSP_USING_ADC0) && !defined(BSP_USING_ADC1)
#error "Please define at least one BSP_USING_ADCx"
/* this driver can be disabled at menuconfig ? RT-Thread Components ? Device Drivers */
#endif

#ifdef BSP_USING_ADC0
#ifndef ADC0_CFG
#define ADC0_CFG                                        \
    {                                                   \
        .name = "adc0",                                 \
        .ADCx = ADC0,                                   \
        .adc_initstruct.clk_src = ADC_CLKSRC_VCO_DIV64, \
        .adc_initstruct.clk_div = 25,                   \
        .adc_initstruct.pga_ref = PGA_REF_INTERNAL,     \
        .adc_initstruct.channels = 0,                   \
        .adc_initstruct.samplAvg = ADC_AVG_SAMPLE1,     \
        .adc_initstruct.trig_src = ADC_TRIGSRC_SW,      \
        .adc_initstruct.Continue = 0,                   \
        .adc_initstruct.EOC_IEn = 0,                    \
        .adc_initstruct.OVF_IEn = 0,                    \
        .adc_initstruct.HFULL_IEn = 0,                  \
        .adc_initstruct.FULL_IEn = 0,                   \
    }
#endif /* ADC0_CFG */
#endif /* BSP_USING_ADC0 */

#ifdef BSP_USING_ADC1
#ifndef ADC1_CFG
#define ADC1_CFG                                        \
    {                                                   \
        .name = "adc1",                                 \
        .ADCx = ADC1,                                   \
        .adc_initstruct.clk_src = ADC_CLKSRC_VCO_DIV64, \
        .adc_initstruct.clk_div = 25,                   \
        .adc_initstruct.pga_ref = PGA_REF_INTERNAL,     \
        .adc_initstruct.channels = 0,                   \
        .adc_initstruct.samplAvg = ADC_AVG_SAMPLE1,     \
        .adc_initstruct.trig_src = ADC_TRIGSRC_SW,      \
        .adc_initstruct.Continue = 0,                   \
        .adc_initstruct.EOC_IEn = 0,                    \
        .adc_initstruct.OVF_IEn = 0,                    \
        .adc_initstruct.HFULL_IEn = 0,                  \
        .adc_initstruct.FULL_IEn = 0,                   \
    }
#endif /* ADC1_CFG */
#endif /* BSP_USING_ADC1 */

struct swm_adc_cfg
{
    const char *name;
    ADC_TypeDef *ADCx;
    ADC_InitStructure adc_initstruct;
};

struct swm_adc_device
{
    struct swm_adc_cfg *adc_cfg;
    struct rt_adc_device adc_device;
};

static struct swm_adc_cfg swm_adc_cfg[] =
    {
#ifdef BSP_USING_ADC0
        ADC0_CFG,
#endif
#ifdef BSP_USING_ADC1
        ADC1_CFG,
#endif

};

static struct swm_adc_device adc_obj[sizeof(swm_adc_cfg) / sizeof(swm_adc_cfg[0])];

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

static rt_err_t swm_adc_enabled(struct rt_adc_device *adc_device, rt_uint32_t channel, rt_bool_t enabled)
{
    uint32_t adc_chn;
    struct swm_adc_cfg *adc_cfg;
    RT_ASSERT(adc_device != RT_NULL);
    adc_cfg = adc_device->parent.user_data;

    if (channel < 8)
    {
        /* set swm ADC channel */
        adc_chn = swm_adc_get_channel(channel);
    }
    else
    {
        LOG_E("ADC channel must be between 0 and 7.");
        return -RT_ERROR;
    }

    if (enabled)
    {
        adc_cfg->ADCx->CTRL |= (adc_chn << ADC_CTRL_CH0_Pos);
    }
    else
    {
        adc_cfg->ADCx->CTRL &= ~(adc_chn << ADC_CTRL_CH0_Pos);
    }

    return RT_EOK;
}

static rt_err_t swm_adc_convert(struct rt_adc_device *adc_device, rt_uint32_t channel, rt_uint32_t *value)
{
    uint32_t adc_chn;
    struct swm_adc_cfg *adc_cfg;
    RT_ASSERT(adc_device != RT_NULL);
    RT_ASSERT(value != RT_NULL);
    adc_cfg = adc_device->parent.user_data;

    if (channel < 8)
    {
        /* set swm ADC channel */
        adc_chn = swm_adc_get_channel(channel);
    }
    else
    {
        LOG_E("ADC channel must be between 0 and 7.");
        return -RT_ERROR;
    }

    /* start ADC */
    ADC_Start(adc_cfg->ADCx);
    /* Wait for the ADC to convert */
    while ((adc_cfg->ADCx->CH[channel].STAT & 0x01) == 0)
        ;

    /* get ADC value */
    *value = (rt_uint32_t)ADC_Read(adc_cfg->ADCx, adc_chn);

    return RT_EOK;
}

static const struct rt_adc_ops swm_adc_ops =
    {
        .enabled = swm_adc_enabled,
        .convert = swm_adc_convert,
};

static int swm_adc_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(swm_adc_cfg) / sizeof(swm_adc_cfg[0]); i++)
    {
        /* ADC init */
        adc_obj[i].adc_cfg = &swm_adc_cfg[i];

        if (adc_obj[i].adc_cfg->ADCx == ADC0)
        {
#ifdef BSP_USING_ADC0_CHN0
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH0;
#endif
#ifdef BSP_USING_ADC0_CHN1
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH1;
#endif
#ifdef BSP_USING_ADC0_CHN2
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH2;
#endif
#ifdef BSP_USING_ADC0_CHN3
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH3;
#endif
#ifdef BSP_USING_ADC0_CHN4
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH4;
            PORT_Init(PORTA, PIN12, PORTA_PIN12_ADC0_IN4, 0); //PA.12 => ADC0.CH4
#endif
#ifdef BSP_USING_ADC0_CHN5
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH5;
            PORT_Init(PORTA, PIN11, PORTA_PIN11_ADC0_IN5, 0); //PA.11 => ADC0.CH5
#endif
#ifdef BSP_USING_ADC0_CHN6
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH6;
            PORT_Init(PORTA, PIN10, PORTA_PIN10_ADC0_IN6, 0); //PA.10 => ADC0.CH6
#endif
#ifdef BSP_USING_ADC0_CHN7
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH7;
            PORT_Init(PORTA, PIN9, PORTA_PIN9_ADC0_IN7, 0); //PA.9  => ADC0.CH7
#endif
        }
        else if (adc_obj[i].adc_cfg->ADCx == ADC1)
        {
#ifdef BSP_USING_ADC1_CHN0
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH0;
            PORT_Init(PORTC, PIN7, PORTC_PIN7_ADC1_IN0, 0); //PC.7 => ADC1.CH0
#endif
#ifdef BSP_USING_ADC1_CHN1
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH1;
            PORT_Init(PORTC, PIN6, PORTC_PIN6_ADC1_IN1, 0); //PC.6 => ADC1.CH1
#endif
#ifdef BSP_USING_ADC1_CHN2
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH2;
            PORT_Init(PORTC, PIN5, PORTC_PIN5_ADC1_IN2, 0); //PC.5 => ADC1.CH2
#endif
#ifdef BSP_USING_ADC1_CHN3
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH3;
            PORT_Init(PORTC, PIN4, PORTC_PIN4_ADC1_IN3, 0); //PC.4 => ADC1.CH3
#endif
#ifdef BSP_USING_ADC1_CHN4
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH4;
            PORT_Init(PORTN, PIN0, PORTN_PIN0_ADC1_IN4, 0); //PN.0 => ADC1.CH4
#endif
#ifdef BSP_USING_ADC1_CHN5
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH5;
            PORT_Init(PORTN, PIN1, PORTN_PIN1_ADC1_IN5, 0); //PN.1 => ADC1.CH5
#endif
#ifdef BSP_USING_ADC1_CHN6
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH6;
            PORT_Init(PORTN, PIN2, PORTN_PIN2_ADC1_IN6, 0); //PN.2 => ADC1.CH6
#endif
#ifdef BSP_USING_ADC1_CHN7
            adc_obj[i].adc_cfg->adc_initstruct.channels |= ADC_CH7;
#endif
        }

        ADC_Init(adc_obj[i].adc_cfg->ADCx, &(adc_obj[i].adc_cfg->adc_initstruct));
        ADC_Open(adc_obj[i].adc_cfg->ADCx);
        /* register ADC device */
        result = rt_hw_adc_register(&adc_obj[i].adc_device, adc_obj[i].adc_cfg->name, &swm_adc_ops, adc_obj[i].adc_cfg);
        if(result != RT_EOK)
        {
            LOG_E("%s register fail.", adc_obj[i].adc_cfg->name);
        }
        else
        {
            LOG_D("%s register success.", adc_obj[i].adc_cfg->name);
        }
    }

    return result;
}
INIT_BOARD_EXPORT(swm_adc_init);
#endif /* BSP_USING_ADC */
#endif /* RT_USING_ADC */
