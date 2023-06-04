/*
 * Copyright (c) 2006-2023
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       		Notes
 * 2022-07-07     zengjianwei       first version
 */

/*
 *采用DMA的方式，只支持ADC0和ADC1，只使用DMA0-DMA_CH0，不支持在两路 ADC 上转换相同的通道
 */

#include <adc_config.h>
#include <board.h>
#include <gd32f30x.h>
#include <rtdevice.h>
#include <rtthread.h>

#if defined(RT_USING_ADC1) || defined(RT_USING_ADC2) || defined(RT_USING_ADC3)

#define LOG_TAG "drv.adc"
#include <rtdbg.h>

static rt_uint32_t adc_periph_config[] = {
#ifdef RT_USING_ADC1
    ADC0,
#endif

#ifdef RT_USING_ADC2
    ADC1,
#endif

#ifdef RT_USING_ADC3
    ADC2,
#endif
};

struct gd32_adc
{
    rt_uint32_t ADC_Handler; // adc periph ADC0~ADC2
    struct rt_adc_device gd32_adc_device;
};

typedef struct
{
    rt_uint32_t Port[7];
    rt_int8_t ADCindex[3];
} PERIPH_LIST_S;

ADC_PORT_CHANNEL_MAP_S adc_port_channel_def[] = ADC_PORT_CHANNEL_MAP_TABLE;

static struct gd32_adc gd32_adc_obj[sizeof(adc_periph_config) / sizeof(adc_periph_config[0])];
static rt_uint32_t adc_value[sizeof(adc_port_channel_def) / sizeof(adc_port_channel_def[0])];
static PERIPH_LIST_S gd32_periph_list = {
    .Port = {0, 0, 0, 0, 0, 0, 0},
    .ADCindex = {-1, -1, -1},
};

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    /* 获得延时经过的 tick 数 */
    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    /* 获得当前时间 */
    told = SysTick->VAL;
    while (1)
    {
        /* 循环获得当前时间，直到达到指定的时间后退出循环 */
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

static rt_err_t find_periph(void)
{
    rt_int16_t i, j, k;

    /* find gpio port of defined table */
    for (i = 0; i < sizeof(adc_port_channel_def) / sizeof(adc_port_channel_def[0]); ++i)
    {
        /* find -1 of gd32_periph_list's member of Port */
        for (j = 0; j < sizeof(gd32_periph_list.Port) / sizeof(gd32_periph_list.Port[0]); ++j)
        {
            if (0 == gd32_periph_list.Port[j])
            {
                break;
            }
        }

        if (j >= sizeof(gd32_periph_list.Port) / sizeof(gd32_periph_list.Port[0]))
        {
            LOG_E("Can not find -1 of gd32_periph_list's member of Port!\n");
            break;
        }

        /* find the different of Port */
        for (k = 0; k < j; ++k)
        {
            if (adc_port_channel_def[i].Port == gd32_periph_list.Port[k])
            {
                break;
            }
        }

        /* if can not find the same Port */
        if (k == j)
        {
            gd32_periph_list.Port[j] = adc_port_channel_def[i].Port;
        }
    }

    /* find adc periph of defined table */
    for (i = 0; i < sizeof(adc_port_channel_def) / sizeof(adc_port_channel_def[0]); ++i)
    {
        /* find -1 of gd32_periph_list's member of ADCindex */
        for (j = 0; j < sizeof(gd32_periph_list.ADCindex) / sizeof(gd32_periph_list.ADCindex[0]); ++j)
        {
            if (-1 == gd32_periph_list.ADCindex[j])
            {
                break;
            }
        }

        if (j >= sizeof(gd32_periph_list.ADCindex) / sizeof(gd32_periph_list.ADCindex[0]))
        {
            LOG_E("Can not find -1 of gd32_periph_list's member of ADCindex!\n");
            break;
        }

        /* find the different of ADCindex */
        for (k = 0; k < j; ++k)
        {
            if (adc_port_channel_def[i].ADCindex == gd32_periph_list.ADCindex[k])
            {
                break;
            }
        }

        /* if can not find the same ADCindex */
        if (k == j)
        {
            gd32_periph_list.ADCindex[j] = adc_port_channel_def[i].ADCindex;
        }
    }

    return RT_EOK;
}

static void gpio_clock_enable(rt_uint32_t Port)
{
    switch (Port)
    {
    case GPIOA:
        rcu_periph_clock_enable(RCU_GPIOA);
        break;
    case GPIOB:
        rcu_periph_clock_enable(RCU_GPIOB);
        break;
    case GPIOC:
        rcu_periph_clock_enable(RCU_GPIOC);
        break;
    case GPIOD:
        rcu_periph_clock_enable(RCU_GPIOD);
        break;
    case GPIOE:
        rcu_periph_clock_enable(RCU_GPIOE);
        break;
    case GPIOF:
        rcu_periph_clock_enable(RCU_GPIOF);
        break;
    case GPIOG:
        rcu_periph_clock_enable(RCU_GPIOG);
        break;

    default:
        LOG_E("Unsport gpio port!\n");
    }
}

static void adc_clock_enable(rt_int8_t ADCindex)
{
    switch (ADCindex)
    {
    case 0:
        rcu_periph_clock_enable(RCU_ADC0);
        break;
    case 1:
        rcu_periph_clock_enable(RCU_ADC1);
        break;
    case 2:
        rcu_periph_clock_enable(RCU_ADC2);
        break;

    default:
        LOG_E("Unsport adc periph!\n");
    }
}

static void rcu_config(void)
{
    rt_int16_t i;

    for (i = 0; i < sizeof(gd32_periph_list.Port) / sizeof(gd32_periph_list.Port[0]); ++i)
    {
        if (0 == gd32_periph_list.Port[i])
        {
            break;
        }

        /* enable GPIOA clock */
        gpio_clock_enable(gd32_periph_list.Port[i]);
    }

    for (i = 0; i < sizeof(gd32_periph_list.ADCindex) / sizeof(gd32_periph_list.ADCindex[0]); ++i)
    {
        if (-1 == gd32_periph_list.ADCindex[i])
        {
            break;
        }

        /* enable ADC clock */
        adc_clock_enable(gd32_periph_list.ADCindex[i]);
    }

    /* enable DMA0 clock */
    rcu_periph_clock_enable(RCU_DMA0);
    /* config ADC clock */
    rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV6);
}

static void gpio_config(void)
{
    rt_int16_t i;

    /* config the GPIO as analog mode */
    for (i = 0; i < sizeof(adc_port_channel_def) / sizeof(adc_port_channel_def[0]); ++i)
    {
        gpio_init(adc_port_channel_def[i].Port, GPIO_MODE_AIN, GPIO_OSPEED_10MHZ, adc_port_channel_def[i].pin);
    }
}

static void dma_config(void)
{
    /* ADC_DMA_channel configuration */
    dma_parameter_struct dma_data_parameter;

    /* ADC DMA_channel configuration */
    dma_deinit(DMA0, DMA_CH0);

    /* initialize DMA single data mode */
    dma_data_parameter.periph_addr = (rt_uint32_t)(&ADC_RDATA(ADC0));
    dma_data_parameter.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_data_parameter.memory_addr = (rt_uint32_t)(&adc_value);
    dma_data_parameter.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_data_parameter.periph_width = DMA_PERIPHERAL_WIDTH_32BIT;
    dma_data_parameter.memory_width = DMA_MEMORY_WIDTH_32BIT;
    dma_data_parameter.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_data_parameter.number = (sizeof(adc_port_channel_def) / sizeof(adc_port_channel_def[0]));
    dma_data_parameter.priority = DMA_PRIORITY_HIGH;
    dma_init(DMA0, DMA_CH0, dma_data_parameter);

    dma_circulation_enable(DMA0, DMA_CH0);

    /* enable DMA channel */
    dma_channel_enable(DMA0, DMA_CH0);
}

static void adc_function_config(rt_uint32_t adc_periph)
{
    /* ADC continuous function enable */
    adc_special_function_config(adc_periph, ADC_CONTINUOUS_MODE, ENABLE);
    /* ADC scan function enable */
    adc_special_function_config(adc_periph, ADC_SCAN_MODE, ENABLE);
    /* ADC data alignment config */
    adc_data_alignment_config(adc_periph, ADC_DATAALIGN_RIGHT);

    /* ADC channel length config */
    adc_channel_length_config(adc_periph, ADC_REGULAR_CHANNEL,
                              (sizeof(adc_port_channel_def) / sizeof(adc_port_channel_def[0])));
}

static void adc_function_enable(rt_int8_t ADCindex)
{
    switch (ADCindex)
    {
    case 0:
        adc_function_config(ADC0);
        break;
    case 1:
        adc_function_config(ADC1);
        break;

    default:
        LOG_E("Unsport adc periph!\n");
    }
}

static void regular_channel_config(rt_uint8_t index)
{
    switch (adc_port_channel_def[index].ADCindex)
    {
    case 0:
        adc_regular_channel_config(ADC0, adc_port_channel_def[index].rank, adc_port_channel_def[index].channel,
                                   ADC_SAMPLETIME_55POINT5);
        break;
    case 1:
        adc_regular_channel_config(ADC1, adc_port_channel_def[index].rank, adc_port_channel_def[index].channel,
                                   ADC_SAMPLETIME_55POINT5);
        break;
    default:
        LOG_E("Unsport adc periph!\n");
    }
}

static void adc_trigger_calibration_config_(rt_uint32_t adc_periph)
{
    /* ADC trigger config */
    adc_external_trigger_source_config(adc_periph, ADC_REGULAR_CHANNEL, ADC0_1_2_EXTTRIG_REGULAR_NONE);
    adc_external_trigger_config(adc_periph, ADC_REGULAR_CHANNEL, ENABLE);
    /* enable ADC interface */
    adc_enable(adc_periph);
    rt_hw_us_delay(5000);
    /* ADC calibration and reset calibration */
    adc_calibration_enable(adc_periph);
}

static void adc_trigger_calibration_config(rt_uint8_t index)
{
    switch (adc_port_channel_def[index].ADCindex)
    {
    case 0:
        adc_trigger_calibration_config_(ADC0);
        break;
    case 1:
        adc_trigger_calibration_config_(ADC1);
        break;
    default:
        LOG_E("Unsport adc periph!\n");
    }
}

static void adc_config(void)
{
    rt_int16_t i;

    /* ADC mode config,使用规则同步模式,ADC0是主,ADC1是从, 同时转换两个通道(同时转换的通道不能相同) */
    adc_mode_config(ADC_DAUL_REGULAL_PARALLEL);

    for (i = 0; i < sizeof(gd32_periph_list.ADCindex) / sizeof(gd32_periph_list.ADCindex[0]); ++i)
    {
        if (-1 == gd32_periph_list.ADCindex[i])
        {
            break;
        }

        /* enable ADC clock */
        adc_function_enable(gd32_periph_list.ADCindex[i]);
    }

    /* ADC regular channel config */
    for (i = 0; i < sizeof(adc_port_channel_def) / sizeof(adc_port_channel_def[0]); ++i)
    {
        regular_channel_config(i);
    }

    for (i = 0; i < sizeof(gd32_periph_list.ADCindex) / sizeof(gd32_periph_list.ADCindex[0]); ++i)
    {
        if (-1 == gd32_periph_list.ADCindex[i])
        {
            break;
        }

        /* enable ADC clock */
        adc_trigger_calibration_config(gd32_periph_list.ADCindex[i]);
    }

    /* ADC DMA function enable */
    adc_dma_mode_enable(ADC0);
    /* ADC software trigger enable */
    adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);
}
static rt_err_t gd32_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    uint32_t *gd32_adc_handler;
    RT_ASSERT(device != RT_NULL);
    gd32_adc_handler = (uint32_t *)device->parent.user_data;

    if (enabled)
    {
        adc_enable(*gd32_adc_handler);
    }
    else
    {
        adc_disable(*gd32_adc_handler);
    }

    return RT_EOK;
}

static rt_int8_t find_index_channel(rt_int8_t channel)
{
    rt_int16_t i;

    /* find index of channel in table */
    for (i = 0; i < sizeof(adc_port_channel_def) / sizeof(adc_port_channel_def[0]); ++i)
    {
        if (adc_port_channel_def[i].channel == channel)
        {
            break;
        }
    }

    if (i >= sizeof(adc_port_channel_def) / sizeof(adc_port_channel_def[0]))
    {
        return -1;
    }

    return i;
}

static rt_err_t gd32_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    if (channel >= 16)
    {
        LOG_E("ADC channel must less than 16.");
        return -RT_ERROR;
    }

    rt_int16_t chan_index, value_index;

    chan_index = find_index_channel(channel);
    if (-1 == chan_index)
    {
        LOG_E("Can not find regular index of channel !\n");
        return -RT_ERROR;
    }

    value_index = adc_port_channel_def[chan_index].rank;

    if (0 == adc_port_channel_def[chan_index].ADCindex)
    {
        /* ADC0 */
        *value = (adc_value[value_index] & 0xFFFF);
    }
    else
    {
        /* ADC1 */
        *value = (adc_value[value_index] >> 16);
    }

    return RT_EOK;
}

static const struct rt_adc_ops gd_adc_ops = {
    .enabled = gd32_adc_enabled,
    .convert = gd32_get_adc_value,
};

static int gd32_adc_init(void)
{
    rt_int16_t result = RT_EOK;
    /* save adc name */
    char name_buf[5] = {'a', 'd', 'c', '0', 0};
    rt_int16_t i = 0;

    find_periph();
    /* clocks configuration */
    rcu_config();
    /* systick configuration */
    // systick_config();
    /* GPIO configuration */
    gpio_config();
    /* DMA configuration */
    dma_config();
    /* ADC configuration */
    adc_config();

    for (i = 0; i < sizeof(adc_periph_config) / sizeof(adc_periph_config[0]); i++)
    {
        /* ADC init */
        name_buf[3] = '0';
        gd32_adc_obj[i].ADC_Handler = adc_periph_config[i];
#if defined(ADC1)
        if (gd32_adc_obj[i].ADC_Handler == ADC1)
        {
            name_buf[3] = '1';
        }
#endif
#if defined(ADC2)
        if (gd32_adc_obj[i].ADC_Handler == ADC2)
        {
            name_buf[3] = '2';
        }
#endif

        /* register ADC device */
        if (rt_hw_adc_register(&gd32_adc_obj[i].gd32_adc_device, name_buf, &gd_adc_ops, &gd32_adc_obj[i].ADC_Handler) ==
            RT_EOK)
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
INIT_BOARD_EXPORT(gd32_adc_init);

#endif /* BSP_USING_ADC */
