/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-31     flybreak     first version
 * 2020-02-22     luhuadong    support custom commands
 * 2022-12-17     Meco Man     re-implement sensor framework
 */

#include <drivers/sensor_v2.h>

#define DBG_TAG  "sensor_v2"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <string.h>

static char *const sensor_name_str[] =
{
    "None",
    "ac-",       /* Accelerometer     */
    "gy-",       /* Gyroscope         */
    "ma-",       /* Magnetometer      */
    "tm-",       /* Temperature       */
    "hm-",       /* Relative Humidity */
    "br-",       /* Barometer         */
    "li-",       /* Ambient light     */
    "pr-",       /* Proximity         */
    "hr-",       /* Heart Rate        */
    "tv-",       /* TVOC Level        */
    "ni-",       /* Noise Loudness    */
    "st-",       /* Step sensor       */
    "fr-",       /* Force sensor      */
    "du-",       /* Dust sensor       */
    "ec-",       /* eCO2 sensor       */
    "gn-",       /* GPS/GNSS sensor   */
    "tf-",       /* TOF sensor        */
    "sp-",       /* SpO2 sensor       */
    "ia-",       /* IAQ sensor        */
    "et-",       /* EtOH sensor       */
    "bp-",       /* Blood Pressure    */
    RT_NULL
};

/* sensor interrupt handler function */
static void _sensor_cb(rt_sensor_t sen)
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
    else if (RT_SENSOR_MODE_GET_FETCH(sen->info.mode) == RT_SENSOR_MODE_FETCH_INT)
    {
        /* The interrupt mode only produces one data at a time */
        sen->parent.rx_indicate(&sen->parent, 1);
    }
    else if (RT_SENSOR_MODE_GET_FETCH(sen->info.mode) == RT_SENSOR_MODE_FETCH_FIFO)
    {
        sen->parent.rx_indicate(&sen->parent, sen->info.fifo_max);
    }
}

/* ISR for sensor interrupt */
static void _irq_callback(void *args)
{
    rt_sensor_t sensor = (rt_sensor_t)args;
    rt_uint8_t i;

    if (sensor->module)
    {
        /* Invoke a callback for all sensors in the module */
        for (i = 0; i < sensor->module->sen_num; i++)
        {
            _sensor_cb(sensor->module->sen[i]);
        }
    }
    else
    {
        _sensor_cb(sensor);
    }
}

/* Sensor interrupt initialization function */
static rt_err_t _sensor_irq_init(rt_sensor_t sensor)
{
    if (sensor->config.irq_pin.pin == PIN_IRQ_PIN_NONE)
    {
        return -RT_EINVAL;
    }

    rt_pin_mode(sensor->config.irq_pin.pin, sensor->config.irq_pin.mode);

    if (sensor->config.irq_pin.mode == PIN_MODE_INPUT_PULLDOWN)
    {
        rt_pin_attach_irq(sensor->config.irq_pin.pin, PIN_IRQ_MODE_RISING, _irq_callback, (void *)sensor);
    }
    else if (sensor->config.irq_pin.mode == PIN_MODE_INPUT_PULLUP)
    {
        rt_pin_attach_irq(sensor->config.irq_pin.pin, PIN_IRQ_MODE_FALLING, _irq_callback, (void *)sensor);
    }
    else if (sensor->config.irq_pin.mode == PIN_MODE_INPUT)
    {
        rt_pin_attach_irq(sensor->config.irq_pin.pin, PIN_IRQ_MODE_RISING_FALLING, _irq_callback, (void *)sensor);
    }

    rt_pin_irq_enable(sensor->config.irq_pin.pin, RT_TRUE);

    LOG_I("interrupt init success");

    return 0;
}

/* sensor local ops */
static rt_ssize_t _local_fetch_data(rt_sensor_t sensor, rt_sensor_data_t buf, rt_size_t len)
{
    LOG_D("Undefined fetch_data");
    return -RT_EINVAL;
}
static rt_err_t _local_control(rt_sensor_t sensor, int cmd, void *arg)
{
    LOG_D("Undefined control");
    return -RT_EINVAL;
}
static struct rt_sensor_ops local_ops =
{
    .fetch_data = _local_fetch_data,
    .control = _local_control
};

/* RT-Thread Device Interface */
static rt_err_t _sensor_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_sensor_t sensor = (rt_sensor_t)dev;
    RT_ASSERT(dev != RT_NULL);
    rt_err_t res = RT_EOK;
    rt_err_t (*local_ctrl)(rt_sensor_t sensor, int cmd, void *arg) =  _local_control;

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
    if (sensor->ops->control != RT_NULL)
    {
        local_ctrl = sensor->ops->control;
    }

    if (oflag & RT_DEVICE_FLAG_RDONLY && dev->flag & RT_DEVICE_FLAG_RDONLY)
    {
        /* If polling mode is supported, configure it to polling mode */
        if (local_ctrl(sensor, RT_SENSOR_CTRL_SET_FETCH_MODE, (void *)RT_SENSOR_MODE_FETCH_POLLING) == RT_EOK)
        {
            RT_SENSOR_MODE_SET_FETCH(sensor->info.mode, RT_SENSOR_MODE_FETCH_POLLING);
        }
    }
    else if (oflag & RT_DEVICE_FLAG_INT_RX && dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* If interrupt mode is supported, configure it to interrupt mode */
        if (local_ctrl(sensor, RT_SENSOR_CTRL_SET_FETCH_MODE, (void *)RT_SENSOR_MODE_FETCH_INT) == RT_EOK)
        {
            /* Initialization sensor interrupt */
            _sensor_irq_init(sensor);
            RT_SENSOR_MODE_SET_FETCH(sensor->info.mode, RT_SENSOR_MODE_FETCH_INT);
        }
    }
    else if (oflag & RT_DEVICE_FLAG_FIFO_RX && dev->flag & RT_DEVICE_FLAG_FIFO_RX)
    {
        /* If fifo mode is supported, configure it to fifo mode */
        if (local_ctrl(sensor, RT_SENSOR_CTRL_SET_FETCH_MODE, (void *)RT_SENSOR_MODE_FETCH_FIFO) == RT_EOK)
        {
            /* Initialization sensor interrupt */
            _sensor_irq_init(sensor);
            RT_SENSOR_MODE_SET_FETCH(sensor->info.mode, RT_SENSOR_MODE_FETCH_FIFO);
        }
    }
    else
    {
        res = -RT_EINVAL;
        goto __exit;
    }

    /* Configure power mode to highest mode */
    if (local_ctrl(sensor, RT_SENSOR_CTRL_SET_POWER_MODE, (void *)RT_SENSOR_MODE_POWER_HIGHEST) == RT_EOK)
    {
        RT_SENSOR_MODE_SET_POWER(sensor->info.mode, RT_SENSOR_MODE_POWER_HIGHEST);
    }

    /* Configure accuracy mode to highest mode */
    if (local_ctrl(sensor, RT_SENSOR_CTRL_SET_ACCURACY_MODE, (void *)RT_SENSOR_MODE_ACCURACY_HIGHEST) == RT_EOK)
    {
        RT_SENSOR_MODE_SET_ACCURACY(sensor->info.mode, RT_SENSOR_MODE_ACCURACY_HIGHEST);
    }

__exit:
    if (sensor->module)
    {
        /* release the module mutex */
        rt_mutex_release(sensor->module->lock);
    }

    return res;
}

static rt_err_t _sensor_close(rt_device_t dev)
{
    rt_sensor_t sensor = (rt_sensor_t)dev;
    rt_err_t (*local_ctrl)(rt_sensor_t sensor, int cmd, void *arg) = _local_control;
    int i;

    RT_ASSERT(dev != RT_NULL);

    if (sensor->module)
    {
        rt_mutex_take(sensor->module->lock, RT_WAITING_FOREVER);
    }
    if (sensor->ops->control != RT_NULL)
    {
        local_ctrl = sensor->ops->control;
    }

    /* Configure power mode to power down mode */
    if (local_ctrl(sensor, RT_SENSOR_CTRL_SET_POWER_MODE, (void *)RT_SENSOR_MODE_POWER_DOWN) == RT_EOK)
    {
        RT_SENSOR_MODE_SET_POWER(sensor->info.mode, RT_SENSOR_MODE_POWER_DOWN);
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
            if (sensor->module->sen[i]->data_buf)
            {
                rt_free(sensor->module->sen[i]->data_buf);
                sensor->module->sen[i]->data_buf = RT_NULL;
            }
        }
    }
    if (RT_SENSOR_MODE_GET_FETCH(sensor->info.mode) != RT_SENSOR_MODE_FETCH_POLLING)
    {
        /* Sensor disable interrupt */
        if (sensor->config.irq_pin.pin != PIN_IRQ_PIN_NONE)
        {
            rt_pin_irq_enable(sensor->config.irq_pin.pin, RT_FALSE);
        }
    }

__exit:
    if (sensor->module)
    {
        rt_mutex_release(sensor->module->lock);
    }

    return RT_EOK;
}

static rt_ssize_t _sensor_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t len)
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
        /* If the buffer is empty, read the data */
        if (sensor->ops->fetch_data)
        {
            result = sensor->ops->fetch_data(sensor, buf, len);
        }
    }

    if (sensor->module)
    {
        rt_mutex_release(sensor->module->lock);
    }

    return result;
}

static rt_err_t _sensor_control(rt_device_t dev, int cmd, void *args)
{
    rt_sensor_t sensor = (rt_sensor_t)dev;
    rt_err_t result = RT_EOK;
    RT_ASSERT(dev != RT_NULL);
    rt_err_t (*local_ctrl)(rt_sensor_t sensor, int cmd, void *arg) = _local_control;
    rt_uint8_t mode;

    if (sensor->module)
    {
        rt_mutex_take(sensor->module->lock, RT_WAITING_FOREVER);
    }
    if (sensor->ops->control != RT_NULL)
    {
        local_ctrl = sensor->ops->control;
    }

    switch (cmd)
    {
        case RT_SENSOR_CTRL_GET_ID:
            if (args)
            {
                result = local_ctrl(sensor, RT_SENSOR_CTRL_GET_ID, args);
            }
            break;
        case RT_SENSOR_CTRL_SET_ACCURACY_MODE:
            /* Configuration sensor power mode */
            mode = (rt_uint32_t)args & 0x000F;
            if (!(mode == RT_SENSOR_MODE_ACCURACY_HIGHEST || mode == RT_SENSOR_MODE_ACCURACY_HIGH ||\
                  mode == RT_SENSOR_MODE_ACCURACY_MEDIUM  || mode == RT_SENSOR_MODE_ACCURACY_LOW  ||\
                  mode == RT_SENSOR_MODE_ACCURACY_LOWEST  || mode == RT_SENSOR_MODE_ACCURACY_NOTRUST))
            {
                LOG_E("sensor accuracy mode illegal: %d", mode);
                return -RT_EINVAL;
            }
            result = local_ctrl(sensor, RT_SENSOR_CTRL_SET_ACCURACY_MODE, args);
            if (result == RT_EOK)
            {
                RT_SENSOR_MODE_SET_ACCURACY(sensor->info.mode, mode);
                LOG_D("set accuracy mode code: %d", RT_SENSOR_MODE_GET_ACCURACY(sensor->info.mode));
            }
            break;
        case RT_SENSOR_CTRL_SET_POWER_MODE:
            /* Configuration sensor power mode */
            mode = (rt_uint32_t)args & 0x000F;
            if (!(mode == RT_SENSOR_MODE_POWER_HIGHEST || mode == RT_SENSOR_MODE_POWER_HIGH ||\
                  mode == RT_SENSOR_MODE_POWER_MEDIUM  || mode == RT_SENSOR_MODE_POWER_LOW  ||\
                  mode == RT_SENSOR_MODE_POWER_LOWEST  || mode == RT_SENSOR_MODE_POWER_DOWN))
            {
                LOG_E("sensor power mode illegal: %d", mode);
                return -RT_EINVAL;
            }
            result = local_ctrl(sensor, RT_SENSOR_CTRL_SET_POWER_MODE, args);
            if (result == RT_EOK)
            {
                RT_SENSOR_MODE_SET_POWER(sensor->info.mode, mode);
                LOG_D("set power mode code: %d", RT_SENSOR_MODE_GET_POWER(sensor->info.mode));
            }
            break;
        case RT_SENSOR_CTRL_SET_FETCH_MODE:
            /* Configuration sensor power mode */
            mode = (rt_uint32_t)args & 0x000F;
            if (!(mode == RT_SENSOR_MODE_FETCH_POLLING || mode == RT_SENSOR_MODE_FETCH_INT ||\
                  mode == RT_SENSOR_MODE_FETCH_FIFO))
            {
                LOG_E("sensor fetch data mode illegal: %d", mode);
                return -RT_EINVAL;
            }
            result = local_ctrl(sensor, RT_SENSOR_CTRL_SET_FETCH_MODE, args);
            if (result == RT_EOK)
            {
                RT_SENSOR_MODE_SET_FETCH(sensor->info.mode, mode);
                LOG_D("set fetch mode code: %d", RT_SENSOR_MODE_GET_FETCH(sensor->info.mode));
            }
            break;
        case RT_SENSOR_CTRL_SELF_TEST:
            /* device self test */
            result = local_ctrl(sensor, RT_SENSOR_CTRL_SELF_TEST, args);
            break;
        case RT_SENSOR_CTRL_SOFT_RESET:
            /* device soft reset */
            result = local_ctrl(sensor, RT_SENSOR_CTRL_SOFT_RESET, args);
            break;
        default:
            if (cmd > RT_SENSOR_CTRL_USER_CMD_START)
            {
                /* Custom commands */
                result = local_ctrl(sensor, cmd, args);
            }
            else
            {
                result = -RT_EINVAL;
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
    _sensor_open,
    _sensor_close,
    _sensor_read,
    RT_NULL,
    _sensor_control
};
#endif

/*
 * sensor register
 */
int rt_hw_sensor_register(rt_sensor_t    sensor,
                          const char    *name,
                          rt_uint32_t    flag,
                          void          *data)
{
    rt_int8_t result;
    rt_device_t device;
    RT_ASSERT(sensor != RT_NULL);

    char *sensor_name = RT_NULL, *device_name = RT_NULL;

    if (sensor->ops == RT_NULL)
    {
        sensor->ops = &local_ops;
    }

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
        sensor->module->lock = rt_mutex_create(name, RT_IPC_FLAG_PRIO);
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
    device->open        = _sensor_open;
    device->close       = _sensor_close;
    device->read        = _sensor_read;
    device->write       = RT_NULL;
    device->control     = _sensor_control;
#endif
    device->type        = RT_Device_Class_Sensor;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = data;

    result = rt_device_register(device, device_name, flag | RT_DEVICE_FLAG_STANDALONE);
    if (result != RT_EOK)
    {
        LOG_E("sensor[%s] register err code: %d", device_name, result);
        rt_free(device_name);
        return result;
    }

    LOG_I("sensor[%s] init success", device_name);
    rt_free(device_name);

    return RT_EOK;
}

rt_sensor_t rt_sensor_device_find(const char *name)
{
    rt_uint8_t index;
    char device_name[RT_NAME_MAX];
    rt_device_t device;

    for (index = 0; sensor_name_str[index] != RT_NULL; index++)
    {
        rt_memset(device_name, 0, sizeof(device_name));
        rt_snprintf(device_name, sizeof(device_name), "%s%s", sensor_name_str[index], name);
        device = rt_device_find(device_name);
        if (device != RT_NULL)
        {
            return (rt_sensor_t)device;
        }
    }

    return RT_NULL;
}
