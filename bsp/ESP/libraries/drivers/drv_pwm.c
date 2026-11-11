/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author           Notes
 * 2023-11-26       ChuShicheng      first version
 */

#include <rtdevice.h>
#include "drv_pwm.h"
#include "driver/ledc.h"


#ifdef BSP_USING_PWM

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.PWM"

#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_DEFAULT           (4095) // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY_DEFAULT      (5000) // Frequency in Hertz. Set frequency at 5 kHz

struct esp_pwm
{
    struct rt_device_pwm pwm_device;
    rt_uint8_t timer_num;
    char *name;
};

static struct esp_pwm esp_pwm_obj[] =
{
#ifdef BSP_USING_PWM0
    {
        .name = "pwm0",
        .timer_num = 0,
    }
#endif /* BSP_USING_PWM0 */
};

static rt_err_t _pwm_set(struct esp_pwm *obj, struct rt_pwm_configuration *configuration)
{
    float period = configuration->period;
    float pulse = configuration->pulse;
    float duty = 8191 * (pulse / period); // ((2 ** 13) - 1) * (pulse / period_hz)
    float period_hz = 1000000000 / configuration->period;

    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = obj->timer_num,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .freq_hz          = (uint32_t)period_hz,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, configuration->channel, (uint32_t)duty));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, configuration->channel));

    return RT_EOK;
}

static rt_err_t _pwm_get(struct esp_pwm *obj, struct rt_pwm_configuration *configuration)
{
    uint32_t period_hz = ledc_get_freq(LEDC_MODE, obj->timer_num);
    LOG_W("period_hz:%d", period_hz);
    uint32_t duty = ledc_get_duty(LEDC_MODE, configuration->channel);
    LOG_W("duty:%d", duty);

    configuration->period = 1000000000 / period_hz;
    configuration->pulse = duty * configuration->period / 8191;
    LOG_W("pulse:%d", configuration->pulse);

    return RT_EOK;
}

static void pwm_enabled(struct esp_pwm *obj, struct rt_pwm_configuration *configuration, rt_uint8_t enable)
{
    if(enable)
    {
        ledc_timer_config_t ledc_timer = {
            .speed_mode       = LEDC_MODE,
            .timer_num        = obj->timer_num,
            .duty_resolution  = LEDC_TIMER_13_BIT,
            .freq_hz          = LEDC_FREQUENCY_DEFAULT,  // Set output frequency at 5 kHz
            .clk_cfg          = LEDC_AUTO_CLK
        };
        ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

        // Prepare and then apply the LEDC PWM channel configuration
        ledc_channel_config_t ledc_channel = {
            .speed_mode     = LEDC_MODE,
            .channel        = configuration->channel,
            .timer_sel      = obj->timer_num,
            .intr_type      = LEDC_INTR_DISABLE,
            .duty           = LEDC_DUTY_DEFAULT, // ((2 ** 13) - 1) * (pulse / period_hz)
            .hpoint         = 0
        };
        switch (configuration->channel)
        {
        case LEDC_CHANNEL_0:
            ledc_channel.gpio_num = BSP_LEDC_CH0_GPIO;
            break;
        case LEDC_CHANNEL_1:
            ledc_channel.gpio_num = BSP_LEDC_CH1_GPIO;
            break;
        case LEDC_CHANNEL_2:
            ledc_channel.gpio_num = BSP_LEDC_CH2_GPIO;
            break;
        case LEDC_CHANNEL_3:
            ledc_channel.gpio_num = BSP_LEDC_CH3_GPIO;
            break;
        case LEDC_CHANNEL_4:
            ledc_channel.gpio_num = BSP_LEDC_CH4_GPIO;
            break;
        case LEDC_CHANNEL_5:
            ledc_channel.gpio_num = BSP_LEDC_CH5_GPIO;
            break;
        default:
            break;
        }
        ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    }
    else
    {
        ESP_ERROR_CHECK(ledc_stop(LEDC_MODE, configuration->channel, 0));
    }
}

static rt_err_t _pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct esp_pwm *_pwm = rt_container_of(device, struct esp_pwm, pwm_device);
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        pwm_enabled(_pwm, configuration, RT_TRUE);
        return RT_EOK;
    case PWM_CMD_DISABLE:
        pwm_enabled(_pwm, configuration, RT_FALSE);
        return RT_EOK;
    case PWM_CMD_SET:
        return _pwm_set(_pwm, configuration);
    case PWM_CMD_GET:
        return _pwm_get(_pwm, configuration);
    default:
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops _pwm_ops =
{
    _pwm_control
};

int rt_hw_pwm_init(void)
{
    int result = RT_EOK;

    for (int i = 0; i < sizeof(esp_pwm_obj) / sizeof(esp_pwm_obj[0]); i++)
    {
        esp_pwm_obj[i].timer_num = i;
        result = rt_device_pwm_register(&esp_pwm_obj[i].pwm_device, esp_pwm_obj[i].name, &_pwm_ops, 0);
        if(result != RT_EOK)
        {
            LOG_E("%s register fail.", esp_pwm_obj[i].name);
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /* BSP_USING_PWM */
