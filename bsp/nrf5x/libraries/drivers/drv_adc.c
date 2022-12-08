/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-18     guohp1128    the first version
 */

#include "drv_adc.h"

#ifdef RT_USING_ADC

struct rt_adc_device nrf5x_adc_device;

drv_nrfx_saadc_result_t results;
nrf_saadc_value_t       result_buff_cache[8];

static void nrf5x_saadc_event_hdr(nrfx_saadc_evt_t const * p_event)
{
    uint8_t i,j;
    if(p_event->type == NRFX_SAADC_EVT_DONE)
    {
        j = 0;
        for(i = 0; i < 8; i++)
        {
            if(results.channels[i].channel_index == i)
            {
                results.result_buffer[i] = result_buff_cache[j];
                j ++;
            }
        }
        results.done = 1;
    }
}

static uint32_t get_channels_mask(void)
{
    uint8_t i;
    uint32_t mask = 0;
    for(i = 0; i < 8; i++)
    {
        if(results.channels[i].channel_index != 0xff)
        {
            mask |= (1 << results.channels[i].channel_index);
        }
    }
    return mask;
}

static void set_channels(drv_nrfx_saadc_channel_t * channel)
{
    uint8_t i;
    if(channel -> mode == NRF_SAADC_MODE_SINGLE_ENDED)
    {
        results.channels[channel->channel_num] = (nrfx_saadc_channel_t)NRFX_SAADC_DEFAULT_CHANNEL_SE(channel -> pin_p + 1, channel -> channel_num);
    }
    else if(channel -> mode == NRF_SAADC_MODE_DIFFERENTIAL)
    {
        results.channels[channel->channel_num] = (nrfx_saadc_channel_t)NRFX_SAADC_DEFAULT_CHANNEL_DIFFERENTIAL(channel -> pin_p + 1, channel -> pin_n + 1, channel -> channel_num);
    }
    results.channel_count = 0;
    for(i = 0; i < 8; i++)
    {
        if(results.channels[i].channel_index != 0xff)
        {
            results.channel_count ++;
        }
    }
}

/* channel: 0-7 */
static rt_err_t nrf5x_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    nrfx_err_t err_code = NRFX_SUCCESS;
    uint8_t i,j;

    if (enabled)
    {
        RT_ASSERT(device != RT_NULL);
        RT_ASSERT(device->parent.user_data != RT_NULL);

        drv_nrfx_saadc_channel_t * drv_channel_config = NULL;
        drv_channel_config = (drv_nrfx_saadc_channel_t *)device->parent.user_data;

        set_channels(drv_channel_config);

        nrfx_saadc_channel_t channels_cache[results.channel_count];

        j = 0;
        for(i = 0; i < 8; i++)
        {
            if(results.channels[i].channel_index != 0xff)
            {
                channels_cache[j] = results.channels[i];
                j ++;
            }
        }

        err_code = nrfx_saadc_channels_config(channels_cache,results.channel_count);

        err_code = nrfx_saadc_simple_mode_set(get_channels_mask(),
                                      NRF_SAADC_RESOLUTION_12BIT,
                                      NRF_SAADC_OVERSAMPLE_DISABLED,
                                      nrf5x_saadc_event_hdr);

        err_code = nrfx_saadc_buffer_set(result_buff_cache, results.channel_count);
    }
    else
    {
        results.channels[channel].channel_index = 0xff;

        results.channel_count = 0;
        for(i = 0; i < 8; i++)
        {
            if(results.channels[i].channel_index != 0xff)
            {
                results.channel_count ++;
            }
        }

        if(results.channel_count == 0)
        {
            nrfx_saadc_channel_t channels_cache[1];
            err_code = nrfx_saadc_channels_config(channels_cache, 0);
            return err_code;
        }
        else
        {
            nrfx_saadc_channel_t channels_cache[results.channel_count];

            j = 0;
            for(i = 0; i < 8; i++)
            {
                if(results.channels[i].channel_index != 0xff)
                {
                    channels_cache[j] = results.channels[i];
                    j ++;
                }
            }

            err_code = nrfx_saadc_channels_config(channels_cache,results.channel_count);

            err_code = nrfx_saadc_simple_mode_set(get_channels_mask(),
                                          NRF_SAADC_RESOLUTION_12BIT,
                                          NRF_SAADC_OVERSAMPLE_DISABLED,
                                          nrf5x_saadc_event_hdr);

            err_code = nrfx_saadc_buffer_set(result_buff_cache, results.channel_count);
        }
    }

    return err_code;
}

static rt_err_t nrf5x_get_adc_value(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    nrfx_err_t err_code = NRFX_SUCCESS;

    if (results.channels[channel].channel_index != 0xff)
    {
        results.done = 0;
        err_code = nrfx_saadc_mode_trigger();
        while(results.done == 0)
        {
            ;
        }
        * value = results.result_buffer[channel];
        results.done = 0;
    }

    return err_code;
}

static const struct rt_adc_ops nrf5x_adc_ops =
{
    .enabled = nrf5x_adc_enabled,
    .convert = nrf5x_get_adc_value,
};

int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    uint8_t i;
    char name_buf[6] = ADC_NAME;

    for(i = 0; i < 8; i++)
    {
        results.channels[i].channel_index = 0xff;
        results.result_buffer[i] = 0;
        results.channel_count = 0;
        results.done = 0;
    }

    /* initializing SAADC interrupt priority */
    if (nrfx_saadc_init(NRFX_SAADC_CONFIG_IRQ_PRIORITY) != NRFX_SUCCESS)
    {
        rt_kprintf("%s init failed", name_buf);
        rt_kprintf("The driver is already initialized.");
        result = -RT_ERROR;
    }
    else
    {
        /* register ADC device */
        if (rt_hw_adc_register(&nrf5x_adc_device, name_buf, &nrf5x_adc_ops, nrf5x_adc_device.parent.user_data) == RT_EOK)
        {
            rt_kprintf("%s init success", name_buf);
        }
        else
        {
            rt_kprintf("%s register failed", name_buf);
            result = -RT_ERROR;
        }
    }
    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);


/*test saadc*/
#include <drv_adc.h>

#define SAMPLE_ADC_MODE_SINGLE_ENDED    0   //single-ended mode
#define SAMPLE_ADC_MODE_DIFFERENTIAL    1   //differential mode

#define SAMPLE_ADC_AIN1     1
#define SAMPLE_ADC_AIN2     2
#define SAMPLE_ADC_AIN7     7
#define SAMPLE_ADC_AIN_NC   0   //disable input of AINx

#define SAMPLE_ADC_CHANNEL_0   0
#define SAMPLE_ADC_CHANNEL_1   1
#define SAMPLE_ADC_CHANNEL_5   5

void saadc_sample(void)
{
    drv_nrfx_saadc_channel_t channel_config;
    rt_uint32_t result;

    rt_adc_device_t adc_dev;
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_NAME);
    adc_dev->parent.user_data = &channel_config;

    channel_config = (drv_nrfx_saadc_channel_t){.mode = SAMPLE_ADC_MODE_SINGLE_ENDED,
                                                .pin_p = SAMPLE_ADC_AIN1,
                                                .pin_n = SAMPLE_ADC_AIN_NC,
                                                .channel_num = SAMPLE_ADC_CHANNEL_0};
    rt_adc_enable(adc_dev, channel_config.channel_num);

    channel_config = (drv_nrfx_saadc_channel_t){.mode = SAMPLE_ADC_MODE_SINGLE_ENDED,
                                                .pin_p = SAMPLE_ADC_AIN2,
                                                .pin_n = SAMPLE_ADC_AIN_NC,
                                                .channel_num = SAMPLE_ADC_CHANNEL_1};
    rt_adc_enable(adc_dev, channel_config.channel_num);

    channel_config = (drv_nrfx_saadc_channel_t){.mode = SAMPLE_ADC_MODE_SINGLE_ENDED,
                                                .pin_p = SAMPLE_ADC_AIN7,
                                                .pin_n = SAMPLE_ADC_AIN_NC,
                                                .channel_num = SAMPLE_ADC_CHANNEL_5};
    rt_adc_enable(adc_dev, channel_config.channel_num);

    int count = 1;
    while(count++)
    {
        result = rt_adc_read(adc_dev, 0);
        rt_kprintf("saadc channel 0 value = %d, ",result);

        result = rt_adc_read(adc_dev, 1);
        rt_kprintf("saadc channel 1 value = %d, ",result);

        result = rt_adc_read(adc_dev, 5);
        rt_kprintf("saadc channel 5 value = %d",result);

        rt_kprintf("\r\n");
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(saadc_sample, saadc sample);

#endif /* RT_USING_ADC */

