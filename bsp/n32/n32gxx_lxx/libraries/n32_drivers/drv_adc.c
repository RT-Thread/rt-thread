/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */
#include "drv_adc.h"

#ifdef RT_USING_ADC

#if defined(BSP_USING_ADC)  || defined(BSP_USING_ADC1) || \
    defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || \
        defined(BSP_USING_ADC4)

static struct n32_adc_config adc_config[] =
{
#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#ifdef BSP_USING_ADC
    {
            "adc",
            ADC,
    },
#endif
#endif

#ifdef BSP_USING_ADC1
    {
            "adc1",
            ADC1,
    },
#endif

#ifdef BSP_USING_ADC2
    {
            "adc2",
            ADC2,
    },
#endif

#ifdef BSP_USING_ADC3
    {
            "adc3",
            ADC3,
    },
#endif

#ifdef BSP_USING_ADC4
    {
            "adc4",
            ADC4,
    },
#endif
};

static struct n32_adc adc_obj[sizeof(adc_config) / sizeof(adc_config[0])] = {0};

static void n32_adc_init(struct n32_adc_config *config)
{
    ADC_InitType ADC_InitStructure;

    ADC_DeInit((ADC_Module*)config->adc_periph);

    /* ADC configuration */
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    ADC_InitStructure.WorkMode       = ADC_WORKMODE_INDEPENDENT;
#endif

    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init((ADC_Module*)config->adc_periph, &ADC_InitStructure);

    /* Enable ADC */
    ADC_Enable((ADC_Module*)config->adc_periph, ENABLE);

    /* Check ADC Ready */
    while (ADC_GetFlagStatusNew((ADC_Module*)config->adc_periph, ADC_FLAG_RDY) == RESET);

    /* Start ADC calibration */
    ADC_StartCalibration((ADC_Module*)config->adc_periph);

    /* Check the end of ADC calibration */
    while (ADC_GetCalibrationStatus((ADC_Module*)config->adc_periph));
}

static rt_err_t n32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    if (channel > ADC_CH_18)
    {
        return -RT_EINVAL;
    }
    return RT_EOK;
}

static rt_err_t n32_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    struct n32_adc_config *config;
    RT_ASSERT(device != RT_NULL);

    if (channel > ADC_CH_18)
    {
        return -RT_EINVAL;
    }
    config = (struct n32_adc_config *)(device->parent.user_data);

    ADC_ConfigRegularChannel((ADC_Module*)config->adc_periph, channel, 1, ADC_SAMP_TIME_239CYCLES5);

    /* Start ADC Software Conversion */
    ADC_EnableSoftwareStartConv((ADC_Module*)config->adc_periph, ENABLE);

    while (ADC_GetFlagStatus((ADC_Module*)config->adc_periph, ADC_FLAG_ENDC)==0)
    {
    }

    ADC_ClearFlag((ADC_Module*)config->adc_periph, ADC_FLAG_ENDC);
    ADC_ClearFlag((ADC_Module*)config->adc_periph, ADC_FLAG_STR);
    *value = ADC_GetDat((ADC_Module*)config->adc_periph);

    return RT_EOK;
}

static struct rt_adc_ops n32_adc_ops =
{
    .enabled = n32_adc_enabled,
    .convert = n32_adc_convert,
};

int rt_hw_adc_init(void)
{
    GPIO_InitType GPIO_InitStructure;

    int i = 0;
    int result = RT_EOK;

#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X) || defined(SOC_N32G4FR)
#ifdef BSP_USING_ADC
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure PA.01 PA.02 as analog input */
    GPIO_InitStructure.Pin       = GPIO_PIN_1 | GPIO_PIN_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
#endif
#endif

#ifdef BSP_USING_ADC1
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC1, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure PA.01 PA.03 as analog input */
    GPIO_InitStructure.Pin        = GPIO_PIN_1 | GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
#endif /* BSP_USING_ADC1 */

#ifdef BSP_USING_ADC2
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC2, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure PA.04 PA.05 as analog input */
    GPIO_InitStructure.Pin        = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
#endif /* BSP_USING_ADC2 */

#ifdef BSP_USING_ADC3
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC3, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure PB.11 PB.13 as analog input */
    GPIO_InitStructure.Pin        = GPIO_PIN_11 | GPIO_PIN_13;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#endif /* BSP_USING_ADC3 */

#ifdef BSP_USING_ADC4
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC4, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure PB.14 PB.15 as analog input */
    GPIO_InitStructure.Pin        = GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#endif /* BSP_USING_ADC4 */

    /* RCC_ADCHCLK_DIV16*/
    ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV16);
    /* Selsect HSE as RCC ADC1M CLK Source */
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8);

    for (i = 0; i < sizeof(adc_obj) / sizeof(adc_obj[0]); i++)
    {
        adc_obj[i].config = &adc_config[i];
        n32_adc_init(&adc_config[i]);
        rt_hw_adc_register(&adc_obj[i].adc_device, \
                           adc_obj[i].config->name, &n32_adc_ops, adc_obj[i].config);
    }
    return result;
}
INIT_DEVICE_EXPORT(rt_hw_adc_init);

#endif  /* defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || defined(BSP_USING_ADC4) */
#endif /* RT_USING_ADC */

