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
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "hal/adc_types.h"

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
    adc_oneshot_unit_handle_t handle;
    adc_cali_handle_t cali_handle;
    rt_uint8_t do_calibration1;
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

        //-------------ADC Calibration Init---------------//
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
        {
            _adc->do_calibration1 = 0;
        }
        // _adc->do_calibration1 = example_adc_calibration_init(_adc->adc_id, ADC_ATTEN_DB_11, &_adc->cali_handle);
    }
    else
    {
        ESP_ERROR_CHECK(adc_oneshot_del_unit(_adc->handle));
        ESP_ERROR_CHECK(adc_cali_delete_scheme_curve_fitting(_adc->cali_handle));
    }

    return RT_EOK;
}

static rt_err_t _adc_get_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

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
