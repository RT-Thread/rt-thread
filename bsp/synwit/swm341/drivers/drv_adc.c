/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-01     lik          first version
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
#define ADC0_CFG                                          \
    {                                                     \
        .name = "adc0",                                   \
        .ADCx = ADC0,                                     \
        .ADC_initstruct.clk_src = ADC_CLKSRC_HRC_DIV8,    \
        .ADC_initstruct.samplAvg = ADC_AVG_SAMPLE1,       \
        .ADC_initstruct.EOC_IEn = 0,                      \
        .ADC_initstruct.HalfIEn = 0,                      \
        .ADC_SEQ_initstruct.trig_src = ADC_TRIGGER_SW,    \
        .ADC_SEQ_initstruct.conv_cnt = 1,                 \
        .ADC_SEQ_initstruct.samp_tim = ADC_SAMPLE_1CLOCK, \
    }
#endif /* ADC0_CFG */
#endif /* BSP_USING_ADC0 */

#ifdef BSP_USING_ADC1
#ifndef ADC1_CFG
#define ADC1_CFG                                          \
    {                                                     \
        .name = "adc1",                                   \
        .ADCx = ADC1,                                     \
        .ADC_initstruct.clk_src = ADC_CLKSRC_HRC_DIV8,    \
        .ADC_initstruct.samplAvg = ADC_AVG_SAMPLE1,       \
        .ADC_initstruct.EOC_IEn = 0,                      \
        .ADC_initstruct.HalfIEn = 0,                      \
        .ADC_SEQ_initstruct.trig_src = ADC_TRIGGER_SW,    \
        .ADC_SEQ_initstruct.conv_cnt = 1,                 \
        .ADC_SEQ_initstruct.samp_tim = ADC_SAMPLE_1CLOCK, \
    }
#endif /* ADC1_CFG */
#endif /* BSP_USING_ADC1 */

struct swm_adc_cfg
{
    const char *name;
    ADC_TypeDef *ADCx;
    ADC_InitStructure ADC_initstruct;
    ADC_SEQ_InitStructure ADC_SEQ_initstruct;
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
    case 8:
        swm_channel = ADC_CH8;
        break;
    case 9:
        swm_channel = ADC_CH9;
        break;
    case 10:
        swm_channel = ADC_CH10;
        break;
    case 11:
        swm_channel = ADC_CH11;
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

    if (channel < 12)
    {
        /* set swm ADC channel */
        adc_chn = swm_adc_get_channel(channel);
    }
    else
    {
        LOG_E("ADC channel must be between 0 and 11.");
        return -RT_ERROR;
    }

    if (enabled)
    {
        adc_cfg->ADCx->SEQCHN0 |= adc_chn;
    }
    else
    {
        adc_cfg->ADCx->SEQCHN0 &= ~adc_chn;
    }

    return RT_EOK;
}

static rt_err_t swm_adc_convert(struct rt_adc_device *adc_device, rt_uint32_t channel, rt_uint32_t *value)
{
    uint32_t chn, val, adc_chn;
    struct swm_adc_cfg *adc_cfg;
    RT_ASSERT(adc_device != RT_NULL);
    RT_ASSERT(value != RT_NULL);
    adc_cfg = adc_device->parent.user_data;

    if (channel < 12)
    {
        /* set swm ADC channel */
        adc_chn = swm_adc_get_channel(channel);
    }
    else
    {
        LOG_E("ADC channel must be between 0 and 11.");
        return -RT_ERROR;
    }

    *value = 0xFFFFFFFF;

    /* start ADC */
    ADC_Start(adc_cfg->ADCx, ADC_SEQ0);

    /* Wait for the ADC to convert */
    while (adc_cfg->ADCx->GO & ADC_GO_BUSY_Msk)
        __NOP();
    while ((adc_cfg->ADCx->SEQ[0].SR & ADC_SR_EMPTY_Msk) == 0)
    {
        val = ADC_Read(adc_cfg->ADCx, ADC_SEQ0, &chn);
        if (chn == adc_chn)
        {
            *value = val;
        }
    }

    if (*value == 0xFFFFFFFF)
    {
        LOG_E("ADC channel can not find.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static const struct rt_adc_ops swm_adc_ops =
    {
        .enabled = swm_adc_enabled,
        .convert = swm_adc_convert,
};

int swm_adc_init(void)
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
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH0;
            PORT_Init(PORTC, PIN6, PORTC_PIN6_ADC0_CH0, 0); //PC.6  => ADC.CH0
#endif
#ifdef BSP_USING_ADC0_CHN1
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH1;
            PORT_Init(PORTC, PIN5, PORTC_PIN5_ADC0_CH1, 0); //PC.5  => ADC.CH1
#endif
#ifdef BSP_USING_ADC0_CHN2
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH2;
            PORT_Init(PORTC, PIN4, PORTC_PIN4_ADC0_CH2, 0); //PC.4  => ADC.CH2
#endif
#ifdef BSP_USING_ADC0_CHN3
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH3;
            PORT_Init(PORTC, PIN3, PORTC_PIN3_ADC0_CH3, 0); //PC.3  => ADC.CH3
#endif
#ifdef BSP_USING_ADC0_CHN4
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH4;
            PORT_Init(PORTC, PIN2, PORTC_PIN2_ADC0_CH4, 0); //PC.2  => ADC.CH4
#endif
#ifdef BSP_USING_ADC0_CHN5
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH5;
            PORT_Init(PORTC, PIN1, PORTC_PIN1_ADC0_CH5, 0); //PC.1  => ADC.CH5
#endif
#ifdef BSP_USING_ADC0_CHN6
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH6;
            PORT_Init(PORTC, PIN0, PORTC_PIN0_ADC0_CH6, 0); //PC.0  => ADC.CH6
#endif
#ifdef BSP_USING_ADC0_CHN7
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH7;
            PORT_Init(PORTA, PIN15, PORTA_PIN15_ADC0_CH7, 0); //PA.15 => ADC.CH7
#endif
#ifdef BSP_USING_ADC0_CHN8
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH8;
            PORT_Init(PORTA, PIN14, PORTA_PIN14_ADC0_CH8, 0); //PA.14 => ADC.CH8
#endif
#ifdef BSP_USING_ADC0_CHN9
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH9;
            PORT_Init(PORTA, PIN13, PORTA_PIN13_ADC0_CH9, 0); //PA.13 => ADC.CH9
#endif
#ifdef BSP_USING_ADC0_CHN10
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH10;
            PORT_Init(PORTA, PIN12, PORTA_PIN12_ADC0_CH10, 0); //PA.12 => ADC.CH10
#endif
#ifdef BSP_USING_ADC0_CHN11
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH11;
            PORT_Init(PORTA, PIN10, PORTA_PIN10_ADC0_CH11, 0); //PA.10 => ADC.CH11
#endif
        }
        else if (adc_obj[i].adc_cfg->ADCx == ADC1)
        {
#ifdef BSP_USING_ADC1_CHN0
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH0;
            PORT_Init(PORTD, PIN1, PORTD_PIN1_ADC1_CH0, 0); //PD.1  => ADC1.CH0
#endif
#ifdef BSP_USING_ADC1_CHN1
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH1;
            PORT_Init(PORTD, PIN0, PORTD_PIN0_ADC1_CH1, 0); //PD.0  => ADC1.CH1
#endif
#ifdef BSP_USING_ADC1_CHN2
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH2;
            PORT_Init(PORTC, PIN13, PORTC_PIN13_ADC1_CH2, 0); //PC.13 => ADC1.CH2
#endif
#ifdef BSP_USING_ADC1_CHN3
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH3;
            PORT_Init(PORTC, PIN12, PORTC_PIN12_ADC1_CH3, 0); //PC.12 => ADC1.CH3
#endif
#ifdef BSP_USING_ADC1_CHN4
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH4;
            PORT_Init(PORTC, PIN11, PORTC_PIN11_ADC1_CH4, 0); //PC.11 => ADC1.CH4
#endif
#ifdef BSP_USING_ADC1_CHN5
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH5;
            PORT_Init(PORTC, PIN10, PORTC_PIN10_ADC1_CH5, 0); //PC.10 => ADC1.CH5
#endif
#ifdef BSP_USING_ADC1_CHN6
            adc_obj[i].adc_cfg->ADC_SEQ_initstruct.channels |= ADC_CH6;
            PORT_Init(PORTC, PIN9, PORTC_PIN9_ADC1_CH6, 0); //PC.9  => ADC1.CH6
#endif
        }

        ADC_Init(adc_obj[i].adc_cfg->ADCx, &(adc_obj[i].adc_cfg->ADC_initstruct));
        ADC_SEQ_Init(adc_obj[i].adc_cfg->ADCx, ADC_SEQ0, &(adc_obj[i].adc_cfg->ADC_SEQ_initstruct));
        ADC_Open(adc_obj[i].adc_cfg->ADCx);
        ADC_Calibrate(adc_obj[i].adc_cfg->ADCx);

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
