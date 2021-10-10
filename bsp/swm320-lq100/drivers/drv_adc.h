/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-5-26      lik          first version
 */

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include "board.h"

struct swm_adc_cfg
{
    const char *name;
    ADC_TypeDef *ADCx;
    ADC_InitStructure adc_initstruct;
};

struct swm_adc
{
    struct swm_adc_cfg *cfg;
    struct rt_adc_device adc_device;
};

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

#endif /* __DRV_ADC_H__ */
