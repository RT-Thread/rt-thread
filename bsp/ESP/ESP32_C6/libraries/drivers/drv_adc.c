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

/* ESP-IDF v6.1 removed the C6 register-level ADC path this driver used on
 * 5.1 (PERIPH_SARADC_MODULE, the PCR/APB_SARADC register structs).  The
 * esp_adc component's adc_oneshot API is available for the C6 in 6.1, so
 * route both SoCs through it there and keep the legacy path only for a
 * pre-6.1 C6 build. */
#include "esp_idf_version.h"
#if defined(SOC_ESP32_C6) && (ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(6, 0, 0))
#define ADC_C6_LEGACY_REGACCESS 1
#endif

#ifdef ADC_C6_LEGACY_REGACCESS
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
#endif

/* ESP-IDF v6.1 renamed the maximum attenuation for the ESP32-C3 from
 * 11 dB to 12 dB (ADC_ATTEN_DB_11 -> ADC_ATTEN_DB_12).  Both are enum
 * constants, so the preprocessor cannot tell them apart with #ifdef; use the
 * IDF version macro to keep 5.1 builds working. */
#include "esp_idf_version.h"
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(6, 0, 0)
#define ADC_DEV_ATTEN ADC_ATTEN_DB_12
#else
#define ADC_DEV_ATTEN ADC_ATTEN_DB_11
#endif

#ifdef BSP_USING_ADC
#define DBG_TAG "drv.adc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define EXAMPLE_READ_LEN 256
#define GET_UNIT(x)      ((x >> 3) & 0x1)

/* esp i2c dirver class */
struct esp_adc
{
    struct rt_adc_ops ops;
    struct rt_adc_device adc_device;
    rt_uint8_t adc_id;
#ifndef ADC_C6_LEGACY_REGACCESS
    adc_oneshot_unit_handle_t handle;
    /* Bit mask of the channels rt_adc_enable() has opened.  IDF allows one
     * handle per hardware unit, so the unit is created with the first
     * channel and released again with the last one. */
    rt_uint8_t channel_enabled;
#endif
};

static struct esp_adc_config adc_config[] = {
#ifdef BSP_USING_ADC1
    {
        .adc_id = ADC_UNIT_1,
        .device_name = "adc1",
    },
#endif
};

static struct esp_adc esp_adc_obj[sizeof(adc_config) / sizeof(adc_config[0])];

static struct rt_mutex adc_lock;

static rt_err_t _adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
#ifdef ADC_C6_LEGACY_REGACCESS
    static int adc_on;
    int gpio;

    if (channel < 0 || channel > 6)
    {
        return -RT_EINVAL;
    }
    if (rt_mutex_take(&adc_lock, RT_WAITING_FOREVER) != RT_EOK)
    {
        return -RT_ERROR;
    }
    gpio = channel;
    if (!enabled)
    {
        if (adc_on > 0)
        {
            adc_on--;
            sar_periph_ctrl_adc_oneshot_power_release();
            periph_module_disable(PERIPH_SARADC_MODULE);
        }
        rt_mutex_release(&adc_lock);
        return RT_EOK;
    }

    periph_module_enable(PERIPH_SARADC_MODULE);
    sar_periph_ctrl_adc_oneshot_power_acquire();
    adc_on++;

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
    rt_mutex_release(&adc_lock);
    return RT_EOK;
#else
    struct esp_adc *_adc = rt_container_of(device, struct esp_adc, adc_device);

    if (channel < 0 || channel > 6)
    {
        return -RT_EINVAL;
    }
    if (rt_mutex_take(&adc_lock, RT_WAITING_FOREVER) != RT_EOK)
    {
        return -RT_ERROR;
    }

    if (enabled)
    {
        //-------------ADC Init---------------//
        /* One handle per hardware unit: a second adc_oneshot_new_unit() for a
         * unit that already exists fails with ESP_ERR_NOT_FOUND, so the unit
         * is opened with the first channel and shared by the ones after it. */
        if (_adc->channel_enabled == 0)
        {
            adc_oneshot_unit_init_cfg_t init_config = {
                .unit_id = _adc->adc_id,
            };
            ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &_adc->handle));
        }
        //-------------ADC Config---------------//
        adc_oneshot_chan_cfg_t config = {
            .bitwidth = ADC_BITWIDTH_DEFAULT,
            .atten = ADC_DEV_ATTEN,
        };
        ESP_ERROR_CHECK(adc_oneshot_config_channel(_adc->handle, channel, &config));
        _adc->channel_enabled |= (rt_uint8_t)(1u << channel);
    }
    else
    {
        _adc->channel_enabled &= (rt_uint8_t) ~(1u << channel);
        if (_adc->channel_enabled == 0)
        {
            ESP_ERROR_CHECK(adc_oneshot_del_unit(_adc->handle));
        }
    }

    rt_mutex_release(&adc_lock);
    return RT_EOK;
#endif
}

static rt_err_t _adc_get_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

#ifdef ADC_C6_LEGACY_REGACCESS
    int i;
    int done = 0;
    uint32_t raw_pin = 0;
    rt_err_t result;

    if (rt_mutex_take(&adc_lock, RT_WAITING_FOREVER) != RT_EOK)
    {
        return -RT_ERROR;
    }
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
            done = 1;
            break;
        }
        esp_rom_delay_us(2);
    }
    if (done)
    {
        raw_pin = APB_SARADC.saradc_sar1data_status.saradc_apb_saradc1_data & 0xfff;
    }
    APB_SARADC.saradc_onetime_sample.saradc_saradc1_onetime_sample = 0;
    APB_SARADC.saradc_onetime_sample.saradc_saradc_onetime_start = 0;
    if (!done)
    {
        result = -RT_ETIMEOUT;
    }
    else
    {
        *value = raw_pin;
        result = RT_EOK;
    }
    rt_mutex_release(&adc_lock);
    return result;
#else
    rt_uint32_t adc_raw = 0;
    struct esp_adc *_adc = rt_container_of(device, struct esp_adc, adc_device);

    if (rt_mutex_take(&adc_lock, RT_WAITING_FOREVER) != RT_EOK)
    {
        return -RT_ERROR;
    }
    ESP_ERROR_CHECK(adc_oneshot_read(_adc->handle, channel, &adc_raw));
    rt_mutex_release(&adc_lock);

    /* Raw counts, the unit rt_adc_read() has always returned on this BSP:
     * documentation/6.components/device-driver/adc/adc.md shows the caller
     * converting them to a voltage itself. */
    *value = adc_raw;

    return RT_EOK;
#endif
}

static const struct rt_adc_ops esp_adc_ops = {
    .enabled = _adc_enabled,
    .convert = _adc_get_value,
    .get_resolution = RT_NULL,
    .get_vref = RT_NULL,
};

int rt_hw_adc_init(void)
{
    int result = RT_EOK;

    if (rt_mutex_init(&adc_lock, "adc", RT_IPC_FLAG_PRIO) != RT_EOK)
    {
        return -RT_ERROR;
    }

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
