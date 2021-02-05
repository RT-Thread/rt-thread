/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-03     iysheng           first version
 */

#include <board.h>
#include <drivers/drv_comm.h>
#include <drivers/adc.h>

#define DBG_TAG             "drv.adc"
#define DBG_LVL             DBG_INFO

#include <rtdbg.h>

#ifdef RT_USING_ADC

#define MAX_EXTERN_ADC_CHANNEL    16

typedef struct {
    struct rt_adc_device adc_dev;
    char name[8];
    rt_base_t adc_pins[16];
    void *private_data;
} gd32_adc_device;

static gd32_adc_device g_gd32_devs[] = {
#ifdef BSP_USING_ADC0
    {
        {},
        "adc0",
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3),
            GET_PIN(A, 4), GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7),
            GET_PIN(B, 0), GET_PIN(B, 1), GET_PIN(C, 0), GET_PIN(C, 1),
            GET_PIN(C, 2), GET_PIN(C, 3), GET_PIN(C, 4), GET_PIN(C, 5),
        },
        ADC0,
    },
#endif

#ifdef BSP_USING_ADC1
    {
        {},
        "adc1",
        {
            GET_PIN(A, 0), GET_PIN(A, 1), GET_PIN(A, 2), GET_PIN(A, 3),
            GET_PIN(A, 4), GET_PIN(A, 5), GET_PIN(A, 6), GET_PIN(A, 7),
            GET_PIN(B, 0), GET_PIN(B, 1), GET_PIN(C, 0), GET_PIN(C, 1),
            GET_PIN(C, 2), GET_PIN(C, 3), GET_PIN(C, 4), GET_PIN(C, 5),
        },
        ADC1,
    },
#endif
};

/*
 * static void init_pin4adc
 *
 * 初始化指定的管腳爲 analog 模式
 * @ rt_uint32_t pin: pin information
 * return: N/A
 */
static void init_pin4adc(rt_base_t pin)
{
    GPIO_InitPara GPIO_InitStruct = {0};

    GPIO_InitStruct.GPIO_Pin  = PIN_GDPIN(pin);
    GPIO_InitStruct.GPIO_Speed = GPIO_SPEED_50MHZ;
    GPIO_InitStruct.GPIO_Mode = GPIO_MODE_AIN;
    GPIO_Init(PIN_GDPORT(pin), &GPIO_InitStruct);
}

static rt_err_t gd32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    ADC_TypeDef *ADCx;
    ADC_InitPara ADC_InitParaStruct = {0};
    gd32_adc_device * gd32_adc = (gd32_adc_device *)device;

    if (channel >= MAX_EXTERN_ADC_CHANNEL)
    {
        LOG_E("invalid channel");
        return -E2BIG;
    }

    ADCx = (ADC_TypeDef *)(device->parent.user_data);

    if (enabled == ENABLE)
    {
        init_pin4adc(gd32_adc->adc_pins[channel]);
        ADC_InitParaStruct.ADC_Trig_External = ADC_EXTERNAL_TRIGGER_MODE_NONE;
        /* Fix the channel number to fit the firmware library */
        ADC_InitParaStruct.ADC_Channel_Number = 1 + channel;
        ADC_InitParaStruct.ADC_Data_Align = ADC_DATAALIGN_RIGHT;
        ADC_InitParaStruct.ADC_Mode_Scan = DISABLE;
        ADC_InitParaStruct.ADC_Mode = ADC_MODE_INDEPENDENT;
        ADC_InitParaStruct.ADC_Mode_Continuous = ENABLE;
        ADC_Init(ADCx, &ADC_InitParaStruct);

        ADC_RegularChannel_Config(ADCx, channel, 1, ADC_SAMPLETIME_13POINT5);
        ADC_Enable(ADCx, ENABLE);
        ADC_SoftwareStartConv_Enable(ADCx, ENABLE);
    }
    else
    {
        ADC_Enable(ADCx, DISABLE);
    }

    return 0;
}

static rt_err_t gd32_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    ADC_TypeDef *ADCx;

    if (!value)
    {
        LOG_E("invalid param");
        return -EINVAL;
    }

    ADCx = (ADC_TypeDef *)(device->parent.user_data);
    *value = ADC_GetConversionValue(ADCx);

    return 0;
}

static struct rt_adc_ops g_gd32_adc_ops = {
    gd32_adc_enabled,
    gd32_adc_convert,
};



static int rt_hw_adc_init(void)
{
    int ret, i = 0;

#ifdef BSP_USING_ADC0
    rcu_periph_clock_enable(RCU_ADC0);
#endif

#ifdef BSP_USING_ADC1
    rcu_periph_clock_enable(RCU_ADC1);
#endif

    for (; i < ARRAY_SIZE(g_gd32_devs); i++)
    {
        ret = rt_hw_adc_register(&g_gd32_devs[i].adc_dev, \
            (const char *)g_gd32_devs[i].name, \
            &g_gd32_adc_ops, g_gd32_devs[i].private_data);
        if (ret != RT_EOK)
        {
            /* TODO err handler */
            LOG_E("failed register %s, err=%d", g_gd32_devs[i].name, ret);
        }
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);
#endif
