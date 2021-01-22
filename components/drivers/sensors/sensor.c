/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-31     flybreak     first version
 * 2020-02-22     luhuadong    support custom commands
 */

#include "sensor.h"

#define DBG_TAG  "sensor"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <string.h>

static char *const sensor_name_str[] =
{
    "none",
    "acce_",     /* Accelerometer     */
    "gyro_",     /* Gyroscope         */
    "mag_",      /* Magnetometer      */
    "temp_",     /* Temperature       */
    "humi_",     /* Relative Humidity */
    "baro_",     /* Barometer         */
    "li_",       /* Ambient light     */
    "pr_",       /* Proximity         */
    "hr_",       /* Heart Rate        */
    "tvoc_",     /* TVOC Level        */
    "noi_",      /* Noise Loudness    */
    "step_",     /* Step sensor       */
    "forc_",     /* Force sensor      */
    "dust_",     /* Dust sensor       */
    "eco2_",     /* eCO2 sensor       */
    "gnss_",     /* GPS/GNSS sensor   */
    "tof_"       /* TOF sensor        */
};

/* Sensor interrupt correlation function */
/*
 * Sensor interrupt handler function
 */
void rt_sensor_cb(rt_sensor_t sen)
{
    if (sen->parent.rx_indicate == RT_NULL)
    {
        return;
    }

    if (sen->irq_handle != RT_NULL)
    {
        sen->irq_handle(sen);
    }

    /* The buffer is not empty. Read the data in the buffer first */
    if (sen->data_len > 0)
    {
        sen->parent.rx_indicate(&sen->parent, sen->data_len / sizeof(struct rt_sensor_data));
    }
    else if (sen->config.mode == RT_SENSOR_MODE_INT)
    {
        /* The interrupt mode only produces one data at a time */
        sen->parent.rx_indicate(&sen->parent, 1);
    }
    else if (sen->config.mode == RT_SENSOR_MODE_FIFO)
    {
        sen->parent.rx_indicate(&sen->parent, sen->info.fifo_max);
    }
}

/* ISR for sensor interrupt */
static void irq_callback(void *args)
{
    rt_sensor_t sensor = (rt_sensor_t)args;
    rt_uint8_t i;

    if (sensor->module)
    {
        /* Invoke a callback for all sensors in the module */
        for (i = 0; i < sensor->module->sen_num; i++)
        {
            rt_sensor_cb(sensor->module->sen[i]);
        }
    }
    else
    {
        rt_sensor_cb(sensor);
    }
}

/* Sensor interrupt initialization function */
static rt_err_t rt_sensor_irq_init(rt_sensor_t sensor)
{
    if (sensor->config.irq_pin.pin == RT_PIN_NONE)
    {
        return -RT_EINVAL;
    }

    rt_pin_mode(sensor->config.irq_pin.pin, sensor->config.irq_pin.mode);

    if (sensor->config.irq_pin.mode == PIN_MODE_INPUT_PULLDOWN)
    {
        rt_pin_attach_irq(sensor->config.irq_pin.pin, PIN_IRQ_MODE_RISING, irq_callback, (void *)sensor);
    }
    else if (sensor->config.irq_pin.mode == PIN_MODE_INPUT_PULLUP)
    {
        rt_pin_attach_irq(sensor->config.irq_pin.pin, PIN_IRQ_MODE_FALLING, irq_callback, (void *)sensor);
    }
    else if (sensor->config.irq_pin.mode == PIN_MODE_INPUT)
    {
        rt_pin_attach_irq(sensor->config.irq_pin.pin, PIN_IRQ_MODE_RISING_FALLING, irq_callback, (void *)sensor);
    }

    rt_pin_irq_enable(sensor->config.irq_pin.pin, RT_TRUE);

    LOG_I("interrupt init success");

    return 0;
}

/* RT-Thread Device Interface */
static rt_err_t rt_sensor_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_sensor_t sensor = (rt_sensor_t)dev;
    RT_ASSERT(dev != RT_NULL);
    rt_err_t res = RT_EOK;

    if (sensor->module)
    {
        /* take the module mutex */
        rt_mutex_take(sensor->module->lock, RT_WAITING_FOREVER);
    }

    if (sensor->module != RT_NULL && sensor->info.fifo_max > 0 && sensor->data_buf == RT_NULL)
    {
        /* Allocate memory for the sensor buffer */
        sensor->data_buf = rt_malloc(sizeof(struct rt_sensor_data) * sensor->info.fifo_max);
        if (sensor->data_buf == RT_NULL)
        {
            res = -RT_ENOMEM;
            goto __exit;
        }
    }

    if (oflag & RT_DEVICE_FLAG_RDONLY && dev->flag & RT_DEVICE_FLAG_RDONLY)
    {
        if (sensor->ops->control != RT_NULL)
        {
            /* If polling mode is supported, configure it to polling mode */
            sensor->ops->control(sensor, RT_SENSOR_CTRL_SET_MODE, (void *)RT_SENSOR_MODE_POLLING);
        }
        sensor->config.mode = RT_SENSOR_MODE_POLLING;
    }
    else if (oflag & RT_DEVICE_FLAG_INT_RX && dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        if (sensor->ops->control != RT_NULL)
        {
            /* If interrupt mode is supported, configure it to interrupt mode */
            sensor->ops->control(sensor, RT_SENSOR_CTRL_SET_MODE, (void *)RT_SENSOR_MODE_INT);
        }
        /* Initialization sensor interrupt */
        rt_sensor_irq_init(sensor);
        sensor->config.mode = RT_SENSOR_MODE_INT;
    }
    else if (oflag & RT_DEVICE_FLAG_FIFO_RX && dev->flag & RT_DEVICE_FLAG_FIFO_RX)
    {
        if (sensor->ops->control != RT_NULL)
        {
            /* If fifo mode is supported, configure it to fifo mode */
            sensor->ops->control(sensor, RT_SENSOR_CTRL_SET_MODE, (void *)RT_SENSOR_MODE_FIFO);
        }
        /* Initialization sensor interrupt */
        rt_sensor_irq_init(sensor);
        sensor->config.mode = RT_SENSOR_MODE_FIFO;
    }
    else
    {
        res = -RT_EINVAL;
        goto __exit;
    }

    /* Configure power mode to normal mode */
    if (sensor->ops->control(sensor, RT_SENSOR_CTRL_SET_POWER, (void *)RT_SENSOR_POWER_NORMAL) == RT_EOK)
    {
        sensor->config.power = RT_SENSOR_POWER_NORMAL;
    }

__exit:
    if (sensor->module)
    {
        /* release the module mutex */
        rt_mutex_release(sensor->module->lock);
    }

    return res;
}

static rt_err_t rt_sensor_close(rt_device_t dev)
{
    rt_sensor_t sensor = (rt_sensor_t)dev;
    int i;

    RT_ASSERT(dev != RT_NULL);

    if (sensor->module)
    {
        rt_mutex_take(sensor->module->lock, RT_WAITING_FOREVER);
    }

    /* Configure power mode to power down mode */
    if (sensor->ops->control(sensor, RT_SENSOR_CTRL_SET_POWER, (void *)RT_SENSOR_POWER_DOWN) == RT_EOK)
    {
        sensor->config.power = RT_SENSOR_POWER_DOWN;
    }

    if (sensor->module != RT_NULL && sensor->info.fifo_max > 0 && sensor->data_buf != RT_NULL)
    {
        for (i = 0; i < sensor->module->sen_num; i ++)
        {
            if (sensor->module->sen[i]->parent.ref_count > 0)
                goto __exit;
        }

        /* Free memory for the sensor buffer */
        for (i = 0; i < sensor->module->sen_num; i ++)
        {
            if (sensor->module->sen[i]->data_buf != RT_NULL)
            {
                rt_free(sensor->module->sen[i]->data_buf);
                sensor->module->sen[i]->data_buf = RT_NULL;
            }
        }
    }
    /* Sensor disable interrupt */
    if (sensor->config.irq_pin.pin != RT_PIN_NONE)
    {
        rt_pin_irq_enable(sensor->config.irq_pin.pin, RT_FALSE);
    }

__exit:
    if (sensor->module)
    {
        rt_mutex_release(sensor->module->lock);
    }

    return RT_EOK;
}

static rt_size_t rt_sensor_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t len)
{
    rt_sensor_t sensor = (rt_sensor_t)dev;
    rt_size_t result = 0;
    RT_ASSERT(dev != RT_NULL);

    if (buf == NULL || len == 0)
    {
        return 0;
    }

    if (sensor->module)
    {
        rt_mutex_take(sensor->module->lock, RT_WAITING_FOREVER);
    }

    /* The buffer is not empty. Read the data in the buffer first */
    if (sensor->data_len > 0)
    {
        if (len > sensor->data_len / sizeof(struct rt_sensor_data))
        {
            len = sensor->data_len / sizeof(struct rt_sensor_data);
        }

        rt_memcpy(buf, sensor->data_buf, len * sizeof(struct rt_sensor_data));

        /* Clear the buffer */
        sensor->data_len = 0;
        result = len;
    }
    else
    {
        /* If the buffer is empty read the data */
        result = sensor->ops->fetch_data(sensor, buf, len);
    }

    if (sensor->module)
    {
        rt_mutex_release(sensor->module->lock);
    }

    return result;
}

static rt_err_t rt_sensor_control(rt_device_t dev, int cmd, void *args)
{
    rt_sensor_t sensor = (rt_sensor_t)dev;
    rt_err_t result = RT_EOK;
    RT_ASSERT(dev != RT_NULL);

    if (sensor->module)
    {
        rt_mutex_take(sensor->module->lock, RT_WAITING_FOREVER);
    }

    switch (cmd)
    {
    case RT_SENSOR_CTRL_GET_ID:
        if (args)
        {
            result = sensor->ops->control(sensor, RT_SENSOR_CTRL_GET_ID, args);
        }
        break;
    case RT_SENSOR_CTRL_GET_INFO:
        if (args)
        {
            rt_memcpy(args, &sensor->info, sizeof(struct rt_sensor_info));
        }
        break;
    case RT_SENSOR_CTRL_SET_RANGE:

        /* Configuration measurement range */
        result = sensor->ops->control(sensor, RT_SENSOR_CTRL_SET_RANGE, args);
        if (result == RT_EOK)
        {
            sensor->config.range = (rt_int32_t)args;
            LOG_D("set range %d", sensor->config.range);
        }
        break;
    case RT_SENSOR_CTRL_SET_ODR:

        /* Configuration data output rate */
        result = sensor->ops->control(sensor, RT_SENSOR_CTRL_SET_ODR, args);
        if (result == RT_EOK)
        {
            sensor->config.odr = (rt_uint32_t)args & 0xFFFF;
            LOG_D("set odr %d", sensor->config.odr);
        }
        break;
    case RT_SENSOR_CTRL_SET_POWER:

        /* Configuration sensor power mode */
        result = sensor->ops->control(sensor, RT_SENSOR_CTRL_SET_POWER, args);
        if (result == RT_EOK)
        {
            sensor->config.power = (rt_uint32_t)args & 0xFF;
            LOG_D("set power mode code:", sensor->config.power);
        }
        break;
    case RT_SENSOR_CTRL_SELF_TEST:

        /* Device self-test */
        result = sensor->ops->control(sensor, RT_SENSOR_CTRL_SELF_TEST, args);
        break;
    default:

        if (cmd > RT_SENSOR_CTRL_USER_CMD_START)
        {
            /* Custom commands */
            result = sensor->ops->control(sensor, cmd, args);
        }
        else
        {
            result = -RT_ERROR;
        }
        break;
    }

    if (sensor->module)
    {
        rt_mutex_release(sensor->module->lock);
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rt_sensor_ops =
{
    RT_NULL,
    rt_sensor_open,
    rt_sensor_close,
    rt_sensor_read,
    RT_NULL,
    rt_sensor_control
};
#endif

/*
 * sensor register
 */
int rt_hw_sensor_register(rt_sensor_t sensor,
                          const char              *name,
                          rt_uint32_t              flag,
                          void                    *data)
{
    rt_int8_t result;
    rt_device_t device;
    RT_ASSERT(sensor != RT_NULL);

    char *sensor_name = RT_NULL, *device_name = RT_NULL;

    /* Add a type name for the sensor device */
    sensor_name = sensor_name_str[sensor->info.type];
    device_name = (char *)rt_calloc(1, rt_strlen(sensor_name) + 1 + rt_strlen(name));
    if (device_name == RT_NULL)
    {
        LOG_E("device_name calloc failed!");
        return -RT_ERROR;
    }

    rt_memcpy(device_name, sensor_name, rt_strlen(sensor_name) + 1);
    strcat(device_name, name);

    if (sensor->module != RT_NULL && sensor->module->lock == RT_NULL)
    {
        /* Create a mutex lock for the module */
        sensor->module->lock = rt_mutex_create(name, RT_IPC_FLAG_FIFO);
        if (sensor->module->lock == RT_NULL)
        {
            rt_free(device_name);
            return -RT_ERROR;
        }
    }

    device = &sensor->parent;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rt_sensor_ops;
#else
    device->init        = RT_NULL;
    device->open        = rt_sensor_open;
    device->close       = rt_sensor_close;
    device->read        = rt_sensor_read;
    device->write       = RT_NULL;
    device->control     = rt_sensor_control;
#endif
    device->type        = RT_Device_Class_Sensor;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = data;

    result = rt_device_register(device, device_name, flag | RT_DEVICE_FLAG_STANDALONE);
    if (result != RT_EOK)
    {
        rt_free(device_name);
        LOG_E("rt_sensor register err code: %d", result);
        return result;
    }

    rt_free(device_name);
    LOG_I("rt_sensor init success");
    return RT_EOK;
}
