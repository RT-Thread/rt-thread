/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#include <rtdbg.h>
#include "drv_dac.h"

#ifdef RT_USING_DAC

#if defined(BSP_USING_DAC) || defined(BSP_USING_DAC1) || defined(BSP_USING_DAC2)

static struct n32_dac_config dac_config[] =
{
#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#ifdef BSP_USING_DAC
    {
        "dac",
    },
#endif
#endif

#ifdef BSP_USING_DAC1
    {
        "dac1",
        DAC_CHANNEL_1,
    },
#endif

#ifdef BSP_USING_DAC2
    {
        "dac2",
        DAC_CHANNEL_2,
    },
#endif
};


static struct n32_dac dac_obj[sizeof(dac_config) / sizeof(dac_config[0])];

static void n32_dac_init(struct n32_dac_config *config)
{
    DAC_InitType DAC_InitStructure;

    /* DAC Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC, ENABLE);

    /* DAC channel Configuration */
    DAC_InitStructure.Trigger          = DAC_TRG_SOFTWARE;
    DAC_InitStructure.WaveGen          = DAC_WAVEGEN_NOISE;
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_UNMASK_LFSRBIT0;
    DAC_InitStructure.BufferOutput     = DAC_BUFFOUTPUT_ENABLE;

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    DAC_Init(config->dac_periph, &DAC_InitStructure);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    DAC_Init(&DAC_InitStructure);

    /* Enable DAC */
    DAC_Enable(ENABLE);

    /* Set DAC Channel DR12CH register */
    DAC_SetChData(DAC_ALIGN_R_12BIT, 4094);
#endif
}

static rt_err_t n32_dac_enabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    RT_ASSERT(device != RT_NULL);

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    DAC_Enable(channel, ENABLE);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    DAC_Enable(ENABLE);
#endif

    return RT_EOK;
}

static rt_err_t n32_dac_disabled(struct rt_dac_device *device, rt_uint32_t channel)
{
    RT_ASSERT(device != RT_NULL);

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    DAC_Enable(channel, DISABLE);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    DAC_Enable(DISABLE);
#endif

    return RT_EOK;
}


static rt_err_t n32_set_dac_value(struct rt_dac_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    rt_uint16_t set_value = 0;
    set_value = (rt_uint16_t)*value;

#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    /* Start DAC Channel conversion by software */
    DAC_SoftTrgEnable(ENABLE);
#endif
    if (set_value > 4096)
    {
        set_value = 4096;
    }

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    /* Start DAC Channel conversion by software */
    if (channel == DAC_CHANNEL_1)
    {
        DAC_SetCh1Data(DAC_ALIGN_R_12BIT, set_value);
        DAC_SoftTrgEnable(DAC_CHANNEL_1, ENABLE);
    }
    else
    {
        DAC_SetCh2Data(DAC_ALIGN_R_12BIT, set_value);
        DAC_SoftTrgEnable(DAC_CHANNEL_2, ENABLE);
    }
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    DAC_SetChData(DAC_ALIGN_R_12BIT, set_value);
#endif
    return RT_EOK;
}

static const struct rt_dac_ops n32_dac_ops =
{
    .disabled = n32_dac_disabled,
    .enabled  = n32_dac_enabled,
    .convert  = n32_set_dac_value,
};


int rt_hw_dac_init(void)
{
    GPIO_InitType GPIO_InitStructure;

    int result = RT_EOK;
    /* save dac name */
    char name_buf[5] = {'d', 'a', 'c', '0', 0};
    int i = 0;

    for (i = 0; i < sizeof(dac_config) / sizeof(dac_config[0]); i++)
    {
        /* dac init */
        dac_obj[i].config = &dac_config[i];

#if defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#if defined(BSP_USING_DAC)
        name_buf[3] = '\0';

        /* Enable GPIO clock */
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

        GPIO_InitStruct(&GPIO_InitStructure);

        /* Config DAC chennel */
        GPIO_InitStructure.Pin       = GPIO_PIN_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
#endif
#endif

#ifdef BSP_USING_DAC1
        if (dac_obj[i].config->dac_periph == DAC_CHANNEL_1)
        {
            name_buf[3] = '1';

            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

            GPIO_InitStruct(&GPIO_InitStructure);
            /* Configure PA4 DAC1 */
            GPIO_InitStructure.Pin        = GPIO_PIN_4;
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
        }

#endif

#ifdef BSP_USING_DAC2
        if (dac_obj[i].config->dac_periph == DAC_CHANNEL_2)
        {
            name_buf[3] = '2';

            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

            GPIO_InitStruct(&GPIO_InitStructure);
            /* Configure PA5 DAC1 */
            GPIO_InitStructure.Pin        = GPIO_PIN_5;
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
        }
#endif

        /* register dac device */
        n32_dac_init(&dac_config[i]);
        if (rt_hw_dac_register(&dac_obj[i].dac_device, name_buf, &n32_dac_ops, &dac_obj[i].config->dac_periph) == RT_EOK)
        {
            LOG_D("%s init success", name_buf);
        }
        else
        {
            LOG_E("%s register failed", name_buf);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_dac_init);

#endif /* defined(BSP_USING_DAC1) || defined(BSP_USING_DAC2) */
#endif /* RT_USING_DAC */
