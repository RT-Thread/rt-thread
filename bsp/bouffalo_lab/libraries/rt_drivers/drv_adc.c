/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-29     rose_man     first version
 */
#include "board.h"
#include "drv_adc.h"

#if defined BSP_USING_ADC

#define DBG_TAG              "drv.adc"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#if defined(BSP_USING_BL70X) || defined(BSP_USING_BL60X)
#define ADC_GPIP_BASE ((uint32_t)0x40002000)
#elif defined(BSP_USING_BL61X) || defined(BSP_USING_BL808)
#define ADC_GPIP_BASE ((uint32_t)0x20002000)
#endif

static struct bflb_dma_channel_lli_pool_s lli[1];
static volatile uint32_t raw_data[16 + 10];
static struct bflb_adc_result_s adc_value[10];

static struct bflb_adc_config_s adc_config =
{
    .clk_div = ADC_CLK_DIV_32,
    .scan_conv_mode = false,
    .continuous_conv_mode = true,
    .differential_mode = false,
    .resolution = ADC_RESOLUTION_16B,
    .vref = ADC_VREF_3P2V,
};

struct bl_adc
{
    struct rt_adc_device bl_adc_device;
    struct bflb_device_s *adc;
    struct bflb_device_s *dma;
    rt_sem_t sem;
};

static struct bl_adc bl_adc_obj;

struct _adc_channel_cfg
{
    struct bflb_adc_channel_s chan;
    uint16_t chan_gpio;
};

static struct _adc_channel_cfg chan[] = {
#ifdef BSP_USING_ADC_CH0
    { .chan.pos_chan = ADC_CHANNEL_0,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH0_PIN,},
#endif
#ifdef BSP_USING_ADC_CH1
    { .chan.pos_chan = ADC_CHANNEL_1,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH1_PIN,},
#endif
#ifdef BSP_USING_ADC_CH2
    { .chan.pos_chan = ADC_CHANNEL_2,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH2_PIN,},
#endif
#ifdef BSP_USING_ADC_CH3
    { .chan.pos_chan = ADC_CHANNEL_3,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH3_PIN,},
#endif
#ifdef BSP_USING_ADC_CH4
    { .chan.pos_chan = ADC_CHANNEL_4,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH4_PIN,},
#endif
#ifdef BSP_USING_ADC_CH5
    { .chan.pos_chan = ADC_CHANNEL_5,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH5_PIN,},
#endif
#ifdef BSP_USING_ADC_CH6
    { .chan.pos_chan = ADC_CHANNEL_6,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH6_PIN,},
#endif
#ifdef BSP_USING_ADC_CH7
    { .chan.pos_chan = ADC_CHANNEL_7,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH7_PIN,},
#endif
#ifdef BSP_USING_ADC_CH8
    { .chan.pos_chan = ADC_CHANNEL_8,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH8_PIN,},
#endif
#ifdef BSP_USING_ADC_CH9
    { .chan.pos_chan = ADC_CHANNEL_9,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH9_PIN,},
#endif
#ifdef BSP_USING_ADC_CH10
    { .chan.pos_chan = ADC_CHANNEL_10,
      .chan.neg_chan = ADC_CHANNEL_GND,
      .chan_gpio = BSP_ADC_CH10_PIN,},
#endif
};

static void bl_adc_pin_init(void)
{
    struct bflb_device_s *gpio;

    gpio = bflb_device_get_by_name("gpio");
    for (uint8_t i = 0; i < sizeof(chan) / sizeof(chan[0]); i++)
    {
        bflb_gpio_init(gpio, chan[i].chan_gpio, GPIO_ANALOG | GPIO_SMT_EN | GPIO_DRV_0);
    }
}

static rt_err_t bl_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    RT_ASSERT(device != RT_NULL);
    struct bl_adc *_adc;
    struct bflb_dma_channel_lli_transfer_s transfers[1];
    _adc = (struct bl_adc *)device->parent.user_data;
    struct bflb_adc_channel_s chan;
    chan.pos_chan = channel;
    chan.neg_chan = ADC_CHANNEL_GND;

    bflb_adc_channel_config(_adc->adc, &chan, channel);

    transfers[0].src_addr = (uint32_t)DMA_ADDR_ADC_RDR;
    transfers[0].dst_addr = (uint32_t)raw_data;
    transfers[0].nbytes = sizeof(raw_data);

    bflb_dma_channel_lli_reload(_adc->dma, lli, 1, transfers, 1);
    bflb_dma_channel_start(_adc->dma);

    if (enabled)
    {
        bflb_adc_start_conversion(_adc->adc);
    }
    else
    {
        bflb_adc_stop_conversion(_adc->adc);
    }

    return RT_EOK;
}

static rt_err_t bl_adc_get_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    struct bl_adc *_adc;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    _adc = device->parent.user_data;

    rt_sem_take(_adc->sem, RT_WAITING_FOREVER);
    /* get ADC value */
    *value = (rt_uint32_t)raw_data[10 + channel];

    return RT_EOK;
}

static const struct rt_adc_ops bl_adc_ops =
{
    .enabled = bl_adc_enabled,
    .convert = bl_adc_get_value,
};

static void bl_adc_dma_isr(void *arg)
{
    struct bl_adc *_adc = (struct bl_adc *)arg;
    LOG_D("adc dma done ");

    // bflb_adc_parse_result(_adc->adc, raw_data, adc_value, 10);

    rt_sem_release(_adc->sem);
}

int rt_hw_adc_init(void)
{
    int result = RT_EOK;

    bl_adc_pin_init();
    bl_adc_obj.adc = bflb_device_get_by_name("adc");
    bl_adc_obj.dma = bflb_device_get_by_name(BSP_ADC_DMA_CHANNEL);

    if(bl_adc_obj.adc == RT_NULL || bl_adc_obj.dma == RT_NULL)
    {
        LOG_E("adc dma device not found");
        return -RT_ERROR;
    }

    bl_adc_obj.sem = rt_sem_create("adc_sem", 0, RT_IPC_FLAG_PRIO);
    if(bl_adc_obj.sem == RT_NULL)
    {
        LOG_E("rt_sem_create adc_dma_sem error");
        return -RT_ENOMEM;
    }

    bflb_adc_init(bl_adc_obj.adc, &adc_config);
    bflb_adc_link_rxdma(bl_adc_obj.adc, true);

    struct bflb_dma_channel_config_s config;
    config.direction = DMA_PERIPH_TO_MEMORY;
    config.src_req = DMA_REQUEST_ADC;
    config.dst_req = DMA_REQUEST_NONE;
    config.src_addr_inc = DMA_ADDR_INCREMENT_DISABLE;
    config.dst_addr_inc = DMA_ADDR_INCREMENT_ENABLE;
    config.src_burst_count = DMA_BURST_INCR1;
    config.dst_burst_count = DMA_BURST_INCR1;
    config.src_width = DMA_DATA_WIDTH_32BIT;
    config.dst_width = DMA_DATA_WIDTH_32BIT;
    bflb_dma_channel_init(bl_adc_obj.dma, &config);
    bflb_dma_channel_irq_attach(bl_adc_obj.dma, bl_adc_dma_isr, (void *)&bl_adc_obj);

    /* register ADC device */
    if (rt_hw_adc_register(&bl_adc_obj.bl_adc_device, "adc", &bl_adc_ops, &bl_adc_obj) == RT_EOK)
    {
        LOG_D("adc init success");
    }
    else
    {
        LOG_E("adc register failed");
        result = -RT_ERROR;
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
