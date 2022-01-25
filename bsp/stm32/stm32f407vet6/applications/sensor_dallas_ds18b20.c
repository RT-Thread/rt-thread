/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2019-07-15     WillianChan     the first version.
 * 2020-07-28     WillianChan     add ds18b20 init error message
 */

#include "sensor_dallas_ds18b20.h"
#include "sensor.h"
#include "board.h"
#include <rtdbg.h>
#include <stdint.h>
#define DBG_TAG "sensor.dallas.ds18b20"
#define DBG_LVL DBG_INFO

#define SENSOR_TEMP_RANGE_MAX (125)
#define SENSOR_TEMP_RANGE_MIN (-55)

RT_WEAK void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t delta;

    us = us * (SysTick->LOAD / (1000000 / RT_TICK_PER_SECOND));
    delta = SysTick->VAL;

    while (delta - SysTick->VAL < us) continue;
}

static void ds18b20_reset(rt_base_t pin)
{
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, PIN_LOW);
    rt_hw_us_delay(780);               /* 480us - 960us */
    rt_pin_write(pin, PIN_HIGH);
    rt_hw_us_delay(40);                /* 15us - 60us*/
}

static uint8_t ds18b20_connect(rt_base_t pin)
{
    uint8_t retry = 0;
    rt_pin_mode(pin, PIN_MODE_INPUT);

    while (rt_pin_read(pin) && retry < 200)
    {
        retry++;
        rt_hw_us_delay(1);
    };

    if(retry >= 200)
        return CONNECT_FAILED;
    else
        retry = 0;

    while (!rt_pin_read(pin) && retry < 240)
    {
        retry++;
        rt_hw_us_delay(1);
    };

    if(retry >= 240)
        return CONNECT_FAILED;

    return CONNECT_SUCCESS;
}

static uint8_t ds18b20_read_bit(rt_base_t pin)
{
    uint8_t data;

    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, PIN_LOW);
    rt_hw_us_delay(2);
    rt_pin_write(pin, PIN_HIGH);
    rt_pin_mode(pin, PIN_MODE_INPUT);
    /* maybe 12us, maybe 5us, whatever...I have no idea */
    rt_hw_us_delay(5);

    if(rt_pin_read(pin))
        data = 1;
    else
        data = 0;

    rt_hw_us_delay(50);

    return data;
}

static uint8_t ds18b20_read_byte(rt_base_t pin)
{
    uint8_t i, j, dat;
    dat = 0;

    for (i = 1; i <= 8; i++)
    {
        j = ds18b20_read_bit(pin);
        dat = (j << 7) | (dat >> 1);
    }

    return dat;
}

static void ds18b20_write_byte(rt_base_t pin, uint8_t dat)
{
    uint8_t j;
    uint8_t testb;
    rt_pin_mode(pin, PIN_MODE_OUTPUT);

    for (j = 1; j <= 8; j++)
    {
        testb = dat & 0x01;
        dat = dat >> 1;

        if(testb)
        {
            rt_pin_write(pin, PIN_LOW);
            rt_hw_us_delay(2);
            rt_pin_write(pin, PIN_HIGH);
            rt_hw_us_delay(60);
        }
        else
        {
            rt_pin_write(pin, PIN_LOW);
            rt_hw_us_delay(60);
            rt_pin_write(pin, PIN_HIGH);
            rt_hw_us_delay(2);
        }
    }
}

void ds18b20_start(rt_base_t pin)
{
    ds18b20_reset(pin);
    ds18b20_connect(pin);
    ds18b20_write_byte(pin, 0xcc);  /* skip rom */
    ds18b20_write_byte(pin, 0x44);  /* convert */
}

uint8_t ds18b20_init(rt_base_t pin)
{
    uint8_t ret = 0;

    ds18b20_reset(pin);
    ret = ds18b20_connect(pin);

    return ret;
}

int32_t ds18b20_get_temperature(rt_base_t pin)
{
    uint8_t TL, TH;
    int32_t tem;
    
    ds18b20_start(pin);
    ds18b20_init(pin);
    ds18b20_write_byte(pin, 0xcc);
    ds18b20_write_byte(pin, 0xbe);
    TL = ds18b20_read_byte(pin);    /* LSB first */
    TH = ds18b20_read_byte(pin);
    if (TH > 7)
    {
        TH =~ TH;
        TL =~ TL;
        tem = TH;
        tem <<= 8;
        tem += TL;
        tem = (int32_t)(tem * 0.0625 * 10 + 0.5);
        return -tem;
    }
    else
    {
        tem = TH;
        tem <<= 8;
        tem += TL;
        tem = (int32_t)(tem * 0.0625 * 10 + 0.5);
        return tem;
    }
}

static rt_size_t _ds18b20_polling_get_data(rt_sensor_t sensor, struct rt_sensor_data *data)
{
    rt_int32_t temperature_x10;
    if (sensor->info.type == RT_SENSOR_CLASS_TEMP)
    {
        temperature_x10 = ds18b20_get_temperature((rt_base_t)sensor->config.intf.user_data);
        data->data.temp = temperature_x10;
        data->timestamp = rt_sensor_get_ts();
    }    
    return 1;
}

static rt_size_t ds18b20_fetch_data(struct rt_sensor_device *sensor, void *buf, rt_size_t len)
{
    RT_ASSERT(buf);

    if (sensor->config.mode == RT_SENSOR_MODE_POLLING)
    {
        return _ds18b20_polling_get_data(sensor, buf);
    }
    else
        return 0;
}

static rt_err_t ds18b20_control(struct rt_sensor_device *sensor, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    return result;
}

static struct rt_sensor_ops sensor_ops =
{
    ds18b20_fetch_data,
    ds18b20_control
};

int rt_hw_ds18b20_init(const char *name, struct rt_sensor_config *cfg)
{
    rt_int8_t result;
    rt_sensor_t sensor_temp = RT_NULL; 
    
    if (!ds18b20_init((rt_base_t)cfg->intf.user_data))
    {
        /* temperature sensor register */
        sensor_temp = rt_calloc(1, sizeof(struct rt_sensor_device));
        if (sensor_temp == RT_NULL)
            return -1;

        sensor_temp->info.type       = RT_SENSOR_CLASS_TEMP;
        sensor_temp->info.vendor     = RT_SENSOR_VENDOR_DALLAS;
        sensor_temp->info.model      = "ds18b20";
        sensor_temp->info.unit       = RT_SENSOR_UNIT_DCELSIUS;
        sensor_temp->info.intf_type  = RT_SENSOR_INTF_ONEWIRE;
        sensor_temp->info.range_max  = SENSOR_TEMP_RANGE_MAX;
        sensor_temp->info.range_min  = SENSOR_TEMP_RANGE_MIN;
        sensor_temp->info.period_min = 5;

        rt_memcpy(&sensor_temp->config, cfg, sizeof(struct rt_sensor_config));
        sensor_temp->ops = &sensor_ops;

        result = rt_hw_sensor_register(sensor_temp, name, RT_DEVICE_FLAG_RDONLY, RT_NULL);
        if (result != RT_EOK)
        {
            LOG_E("device register err code: %d", result);
            goto __exit;
        }

    }
    else
    {
        LOG_E("DS18B20 init failed! Please check the connection!");
        goto __exit;
    }
    
    return RT_EOK;
    
__exit:
    if (sensor_temp)
        rt_free(sensor_temp);
    return -RT_ERROR;     
}
