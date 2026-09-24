/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-23     Chushicheng  first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_adc.h"
#include "hal/adc_types.h"

#ifdef SOC_ESP32_C6
#include "soc/apb_saradc_struct.h"
#include "soc/pcr_struct.h"
#include "soc/adc_channel.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "esp_rom_sys.h"
#include "esp_private/periph_ctrl.h"
#include "esp_private/sar_periph_ctrl.h"
#else
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#endif

#ifdef BSP_USING_ADC
#define DBG_TAG              "drv.adc"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#define EXAMPLE_READ_LEN   256
#define GET_UNIT(x)        ((x>>3) & 0x1)

/* esp i2c dirver class */
struct esp_adc
{
    struct rt_adc_ops ops;
    struct rt_adc_device adc_device;
    rt_uint8_t adc_id;
#ifndef SOC_ESP32_C6
    adc_oneshot_unit_handle_t handle;
    adc_cali_handle_t cali_handle;
    rt_uint8_t do_calibration1;
#endif
};

static struct esp_adc_config adc_config[] =
{
#ifdef BSP_USING_ADC1
    {
        .adc_id = ADC_UNIT_1,
        .device_name = "adc1",
    },
#endif
};

static struct esp_adc esp_adc_obj[sizeof(adc_config) / sizeof(adc_config[0])];

static rt_err_t _adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
#ifdef SOC_ESP32_C6
    int gpio;

    if (channel < 0 || channel > 6)
    {
        return -RT_EINVAL;
    }
    gpio = channel;
    if (!enabled)
    {
        return RT_EOK;
    }

    periph_module_enable(PERIPH_SARADC_MODULE);
    sar_periph_ctrl_adc_oneshot_power_acquire();

    PCR.saradc_conf.saradc_clk_en = 1;
    PCR.saradc_conf.saradc_rst_en = 0;
    PCR.saradc_clkm_conf.saradc_clkm_en = 1;
    PCR.saradc_clkm_conf.saradc_clkm_sel = 0;
    PCR.saradc_clkm_conf.saradc_clkm_div_num = 15;
    PCR.saradc_clkm_conf.saradc_clkm_div_a = 0;
    PCR.saradc_clkm_conf.saradc_clkm_div_b = 1;

    APB_SARADC.saradc_ctrl.saradc_saradc_sar_clk_gated = 1;
    APB_SARADC.saradc_ctrl.saradc_saradc_sar_clk_div = 1;
    APB_SARADC.saradc_ctrl.saradc_saradc_xpd_sar_force = 3;

    gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << gpio,
        .mode = GPIO_MODE_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&cfg);
    rtc_gpio_init(gpio);
    rtc_gpio_set_direction(gpio, RTC_GPIO_MODE_DISABLED);
    rtc_gpio_pulldown_dis(gpio);
    rtc_gpio_pullup_dis(gpio);

    APB_SARADC.saradc_onetime_sample.saradc_saradc_onetime_atten = 3;
    APB_SARADC.saradc_onetime_sample.saradc_saradc_onetime_channel = channel;
    return RT_EOK;
#else
    struct esp_adc *_adc = rt_container_of(device, struct esp_adc, adc_device);

    if(enabled)
    {
        //-------------ADC Init---------------//
        adc_oneshot_unit_init_cfg_t init_config = {
            .unit_id = _adc->adc_id,
        };
        ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &_adc->handle));
        //-------------ADC Config---------------//
        adc_oneshot_chan_cfg_t config = {
            .bitwidth = ADC_BITWIDTH_DEFAULT,
            .atten = ADC_ATTEN_DB_11,
        };
        ESP_ERROR_CHECK(adc_oneshot_config_channel(_adc->handle, channel, &config));

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = _adc->adc_id,
            .atten = ADC_ATTEN_DB_11,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        if (adc_cali_create_scheme_curve_fitting(&cali_config, &_adc->cali_handle) == ESP_OK)
        {
            _adc->do_calibration1 = 1;
        }
        else
#endif
        {
            _adc->do_calibration1 = 0;
        }
        // _adc->do_calibration1 = example_adc_calibration_init(_adc->adc_id, ADC_ATTEN_DB_11, &_adc->cali_handle);
    }
    else
    {
        ESP_ERROR_CHECK(adc_oneshot_del_unit(_adc->handle));
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
        if (_adc->do_calibration1)
        {
            ESP_ERROR_CHECK(adc_cali_delete_scheme_curve_fitting(_adc->cali_handle));
        }
#endif
    }

    return RT_EOK;
#endif
}

static rt_err_t _adc_get_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

#ifdef SOC_ESP32_C6
    int i;
    uint32_t raw_pin;

    APB_SARADC.saradc_onetime_sample.saradc_saradc_onetime_channel = channel;
    APB_SARADC.saradc_int_clr.saradc_apb_saradc1_done_int_clr = 1;
    APB_SARADC.saradc_onetime_sample.saradc_saradc1_onetime_sample = 0;
    APB_SARADC.saradc_onetime_sample.saradc_saradc2_onetime_sample = 0;
    APB_SARADC.saradc_onetime_sample.saradc_saradc1_onetime_sample = 1;
    APB_SARADC.saradc_onetime_sample.saradc_saradc_onetime_start = 0;
    esp_rom_delay_us(5);
    APB_SARADC.saradc_onetime_sample.saradc_saradc_onetime_start = 1;
    for (i = 0; i < 1000; i++)
    {
        if (APB_SARADC.saradc_int_raw.saradc_apb_saradc1_done_int_raw)
        {
            break;
        }
        esp_rom_delay_us(2);
    }
    raw_pin = APB_SARADC.saradc_sar1data_status.saradc_apb_saradc1_data & 0xfff;
    APB_SARADC.saradc_onetime_sample.saradc_saradc1_onetime_sample = 0;
    APB_SARADC.saradc_onetime_sample.saradc_saradc_onetime_start = 0;
    *value = raw_pin;
    return RT_EOK;
#else
    rt_uint32_t adc_raw = 0;
    struct esp_adc *_adc = rt_container_of(device, struct esp_adc, adc_device);
    ESP_ERROR_CHECK(adc_oneshot_read(_adc->handle, channel, &adc_raw));

    if (_adc->do_calibration1)
    {
        ESP_ERROR_CHECK(adc_cali_raw_to_voltage(_adc->cali_handle, adc_raw, value));
    }
    else
    {
        *value = adc_raw;
    }

    return RT_EOK;
#endif
}

static const struct rt_adc_ops esp_adc_ops =
{
    .enabled = _adc_enabled,
    .convert = _adc_get_value,
    .get_resolution = RT_NULL,
    .get_vref = RT_NULL,
};

int rt_hw_adc_init(void)
{
    int result = RT_EOK;

    for (rt_size_t i = 0; i < sizeof(esp_adc_obj) / sizeof(struct esp_adc); i++)
    {
        esp_adc_obj[i].adc_id = adc_config[i].adc_id;
        /* register ADC device */
        if (rt_hw_adc_register(&esp_adc_obj[i].adc_device, adc_config[i].device_name, &esp_adc_ops, &adc_config[i]) == RT_EOK)
        {
            LOG_D("%s init success", adc_config[i].device_name);
        }
        else
        {
            LOG_E("%s register failed", adc_config[i].device_name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
