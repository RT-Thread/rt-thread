/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-01-31     flybreak       first version
 * 2019-07-16     WillianChan    Increase the output of sensor information
 * 2020-02-22     luhuadong      Add vendor info and sensor types for cmd
 */

#include "sensor.h"

#define DBG_TAG  "sensor.cmd"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stdlib.h>
#include <string.h>

static rt_sem_t sensor_rx_sem = RT_NULL;

static void sensor_show_data(rt_size_t num, rt_sensor_t sensor, struct rt_sensor_data *sensor_data)
{
    switch (sensor->info.type)
    {
    case RT_SENSOR_CLASS_ACCE:
        LOG_I("num:%3d, x:%5d, y:%5d, z:%5d mg, timestamp:%5d", num, sensor_data->data.acce.x, sensor_data->data.acce.y, sensor_data->data.acce.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_GYRO:
        LOG_I("num:%3d, x:%8d, y:%8d, z:%8d dps, timestamp:%5d", num, sensor_data->data.gyro.x / 1000, sensor_data->data.gyro.y / 1000, sensor_data->data.gyro.z / 1000, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_MAG:
        LOG_I("num:%3d, x:%5d, y:%5d, z:%5d mGauss, timestamp:%5d", num, sensor_data->data.mag.x, sensor_data->data.mag.y, sensor_data->data.mag.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_TEMP:
        LOG_I("num:%3d, temp:%3d.%d C, timestamp:%5d", num, sensor_data->data.temp / 10, sensor_data->data.temp % 10, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_HUMI:
        LOG_I("num:%3d, humi:%3d.%d%%, timestamp:%5d", num, sensor_data->data.humi / 10, sensor_data->data.humi % 10, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_BARO:
        LOG_I("num:%3d, press:%5d pa, timestamp:%5d", num, sensor_data->data.baro, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_LIGHT:
        LOG_I("num:%3d, light:%5d lux, timestamp:%5d", num, sensor_data->data.light, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_PROXIMITY:
        LOG_I("num:%3d, distance:%5d, timestamp:%5d", num, sensor_data->data.proximity, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_HR:
        LOG_I("num:%3d, heart rate:%5d bpm, timestamp:%5d", num, sensor_data->data.hr, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_TVOC:
        LOG_I("num:%3d, tvoc:%5d ppb, timestamp:%5d", num, sensor_data->data.tvoc, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_NOISE:
        LOG_I("num:%3d, noise:%5d, timestamp:%5d", num, sensor_data->data.noise, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_STEP:
        LOG_I("num:%3d, step:%5d, timestamp:%5d", num, sensor_data->data.step, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_FORCE:
        LOG_I("num:%3d, force:%5d, timestamp:%5d", num, sensor_data->data.force, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_DUST:
        LOG_I("num:%3d, dust:%5d ug/m3, timestamp:%5d", num, sensor_data->data.dust, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_ECO2:
        LOG_I("num:%3d, eco2:%5d ppm, timestamp:%5d", num, sensor_data->data.eco2, sensor_data->timestamp);
        break;
    default:
        break;
    }
}

static rt_err_t rx_callback(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(sensor_rx_sem);
    return 0;
}

static void sensor_fifo_rx_entry(void *parameter)
{
    rt_device_t dev = (rt_device_t)parameter;
    rt_sensor_t sensor = (rt_sensor_t)parameter;
    struct rt_sensor_data *data = RT_NULL;
    struct rt_sensor_info info;
    rt_size_t res, i;
    
    rt_device_control(dev, RT_SENSOR_CTRL_GET_INFO, &info);

    data = (struct rt_sensor_data *)rt_malloc(sizeof(struct rt_sensor_data) * info.fifo_max);
    if (data == RT_NULL)
    {
        LOG_E("Memory allocation failed!");
    }

    while (1)
    {
        rt_sem_take(sensor_rx_sem, RT_WAITING_FOREVER);

        res = rt_device_read(dev, 0, data, info.fifo_max);
        for (i = 0; i < res; i++)
        {
            sensor_show_data(i, sensor, &data[i]);
        }
    }
}

static void sensor_fifo(int argc, char **argv)
{
    static rt_thread_t tid1 = RT_NULL;
    rt_device_t dev = RT_NULL;
    rt_sensor_t sensor;

    dev = rt_device_find(argv[1]);
    if (dev == RT_NULL)
    {
        LOG_E("Can't find device:%s", argv[1]);
        return;
    }
    sensor = (rt_sensor_t)dev;
    
    if (rt_device_open(dev, RT_DEVICE_FLAG_FIFO_RX) != RT_EOK)
    {
        LOG_E("open device failed!");
        return;
    }

    if (sensor_rx_sem == RT_NULL)
    {
        sensor_rx_sem = rt_sem_create("sen_rx_sem", 0, RT_IPC_FLAG_FIFO);
    }
    else
    {
        LOG_E("The thread is running, please reboot and try again");
        return;
    }

    tid1 = rt_thread_create("sen_rx_thread",
                            sensor_fifo_rx_entry, sensor,
                            1024,
                            15, 5);

    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    rt_device_set_rx_indicate(dev, rx_callback);

    rt_device_control(dev, RT_SENSOR_CTRL_SET_ODR, (void *)20);
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(sensor_fifo, Sensor fifo mode test function);
#endif

static void sensor_irq_rx_entry(void *parameter)
{
    rt_device_t dev = (rt_device_t)parameter;
    rt_sensor_t sensor = (rt_sensor_t)parameter;
    struct rt_sensor_data data;
    rt_size_t res, i = 0;

    while (1)
    {
        rt_sem_take(sensor_rx_sem, RT_WAITING_FOREVER);

        res = rt_device_read(dev, 0, &data, 1);
        if (res == 1)
        {
            sensor_show_data(i++, sensor, &data);
        }
    }
}

static void sensor_int(int argc, char **argv)
{
    static rt_thread_t tid1 = RT_NULL;
    rt_device_t dev = RT_NULL;
    rt_sensor_t sensor;

    dev = rt_device_find(argv[1]);
    if (dev == RT_NULL)
    {
        LOG_E("Can't find device:%s", argv[1]);
        return;
    }
    sensor = (rt_sensor_t)dev;

    if (sensor_rx_sem == RT_NULL)
    {
        sensor_rx_sem = rt_sem_create("sen_rx_sem", 0, RT_IPC_FLAG_FIFO);
    }
    else
    {
        LOG_E("The thread is running, please reboot and try again");
        return;
    }

    tid1 = rt_thread_create("sen_rx_thread",
                            sensor_irq_rx_entry, sensor,
                            1024,
                            15, 5);

    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    rt_device_set_rx_indicate(dev, rx_callback);

    if (rt_device_open(dev, RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        LOG_E("open device failed!");
        return;
    }
    rt_device_control(dev, RT_SENSOR_CTRL_SET_ODR, (void *)20);
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(sensor_int, Sensor interrupt mode test function);
#endif

static void sensor_polling(int argc, char **argv)
{
    uint16_t num = 10;
    rt_device_t dev = RT_NULL;
    rt_sensor_t sensor;
    struct rt_sensor_data data;
    rt_size_t res, i;

    dev = rt_device_find(argv[1]);
    if (dev == RT_NULL)
    {
        LOG_E("Can't find device:%s", argv[1]);
        return;
    }
    if (argc > 2)
        num = atoi(argv[2]);

    sensor = (rt_sensor_t)dev;

    if (rt_device_open(dev, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        LOG_E("open device failed!");
        return;
    }
    rt_device_control(dev, RT_SENSOR_CTRL_SET_ODR, (void *)100);

    for (i = 0; i < num; i++)
    {
        res = rt_device_read(dev, 0, &data, 1);
        if (res != 1)
        {
            LOG_E("read data failed!size is %d", res);
        }
        else
        {
            sensor_show_data(i, sensor, &data);
        }
        rt_thread_mdelay(100);
    }
    rt_device_close(dev);
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(sensor_polling, Sensor polling mode test function);
#endif

static void sensor(int argc, char **argv)
{
    static rt_device_t dev = RT_NULL;
    struct rt_sensor_data data;
    rt_size_t res, i;

    /* If the number of arguments less than 2 */
    if (argc < 2)
    {
        rt_kprintf("\n");
        rt_kprintf("sensor  [OPTION] [PARAM]\n");
        rt_kprintf("         probe <dev_name>      Probe sensor by given name\n");
        rt_kprintf("         info                  Get sensor info\n");
        rt_kprintf("         sr <var>              Set range to var\n");
        rt_kprintf("         sm <var>              Set work mode to var\n");
        rt_kprintf("         sp <var>              Set power mode to var\n");
        rt_kprintf("         sodr <var>            Set output date rate to var\n");
        rt_kprintf("         read [num]            Read [num] times sensor\n");
        rt_kprintf("                               num default 5\n");
        return ;
    }
    else if (!strcmp(argv[1], "info"))
    {
        struct rt_sensor_info info;
        if (dev == RT_NULL)
        {
            LOG_W("Please probe sensor device first!");
            return ;
        }
        rt_device_control(dev, RT_SENSOR_CTRL_GET_INFO, &info);
        switch (info.vendor)
        {
            case RT_SENSOR_VENDOR_UNKNOWN:
                rt_kprintf("vendor    :unknown vendor\n");
                break;
            case RT_SENSOR_VENDOR_STM:
                rt_kprintf("vendor    :STMicroelectronics\n");
                break;
            case RT_SENSOR_VENDOR_BOSCH:
                rt_kprintf("vendor    :Bosch\n");
                break;
            case RT_SENSOR_VENDOR_INVENSENSE:
                rt_kprintf("vendor    :Invensense\n");
                break;
            case RT_SENSOR_VENDOR_SEMTECH:
                rt_kprintf("vendor    :Semtech\n");
                break;
            case RT_SENSOR_VENDOR_GOERTEK:
                rt_kprintf("vendor    :Goertek\n");
                break;
            case RT_SENSOR_VENDOR_MIRAMEMS:
                rt_kprintf("vendor    :MiraMEMS\n");
                break;
            case RT_SENSOR_VENDOR_DALLAS:
                rt_kprintf("vendor    :Dallas\n");
                break;
            case RT_SENSOR_VENDOR_ASAIR:
                rt_kprintf("vendor    :Asair\n");
                break;
            case RT_SENSOR_VENDOR_SHARP:
                rt_kprintf("vendor    :Sharp\n");
                break;
            case RT_SENSOR_VENDOR_SENSIRION:
                rt_kprintf("vendor    :Sensirion\n");
                break;
        }
        rt_kprintf("model     :%s\n", info.model);
        switch (info.unit)
        {
            case RT_SENSOR_UNIT_NONE:
                rt_kprintf("unit      :none\n");
                break;
            case RT_SENSOR_UNIT_MG:
                rt_kprintf("unit      :mG\n");
                break;
            case RT_SENSOR_UNIT_MDPS:
                rt_kprintf("unit      :mdps\n");
                break;
            case RT_SENSOR_UNIT_MGAUSS:
                rt_kprintf("unit      :mGauss\n");
                break;
            case RT_SENSOR_UNIT_LUX:
                rt_kprintf("unit      :lux\n");
                break;
            case RT_SENSOR_UNIT_CM:
                rt_kprintf("unit      :cm\n");
                break;
            case RT_SENSOR_UNIT_PA:
                rt_kprintf("unit      :pa\n");
                break;
            case RT_SENSOR_UNIT_PERMILLAGE:
                rt_kprintf("unit      :permillage\n");
                break;
            case RT_SENSOR_UNIT_DCELSIUS:
                rt_kprintf("unit      :Celsius\n");
                break;
            case RT_SENSOR_UNIT_HZ:
                rt_kprintf("unit      :HZ\n");
                break;
            case RT_SENSOR_UNIT_ONE:
                rt_kprintf("unit      :1\n");
                break;
            case RT_SENSOR_UNIT_BPM:
                rt_kprintf("unit      :bpm\n");
                break;
            case RT_SENSOR_UNIT_MM:
                rt_kprintf("unit      :mm\n");
                break;
            case RT_SENSOR_UNIT_MN:
                rt_kprintf("unit      :mN\n");
                break;
        }
        rt_kprintf("range_max :%d\n", info.range_max);
        rt_kprintf("range_min :%d\n", info.range_min);
        rt_kprintf("period_min:%dms\n", info.period_min);
        rt_kprintf("fifo_max  :%d\n", info.fifo_max);
    }
    else if (!strcmp(argv[1], "read"))
    {
        uint16_t num = 5;

        if (dev == RT_NULL)
        {
            LOG_W("Please probe sensor device first!");
            return ;
        }
        if (argc == 3)
        {
            num = atoi(argv[2]);
        }

        for (i = 0; i < num; i++)
        {
            res = rt_device_read(dev, 0, &data, 1);
            if (res != 1)
            {
                LOG_E("read data failed!size is %d", res);
            }
            else
            {
                sensor_show_data(i, (rt_sensor_t)dev, &data);
            }
            rt_thread_mdelay(100);
        }
    }
    else if (argc == 3)
    {
        if (!strcmp(argv[1], "probe"))
        {
            rt_uint8_t reg = 0xFF;
            if (dev)
            {
                rt_device_close(dev);
            }

            dev = rt_device_find(argv[2]);
            if (dev == RT_NULL)
            {
                LOG_E("Can't find device:%s", argv[1]);
                return;
            }
            if (rt_device_open(dev, RT_DEVICE_FLAG_RDWR) != RT_EOK)
            {
                LOG_E("open device failed!");
                return;
            }
            rt_device_control(dev, RT_SENSOR_CTRL_GET_ID, &reg);
            LOG_I("device id: 0x%x!", reg);

        }
        else if (dev == RT_NULL)
        {
            LOG_W("Please probe sensor first!");
            return ;
        }
        else if (!strcmp(argv[1], "sr"))
        {
            rt_device_control(dev, RT_SENSOR_CTRL_SET_RANGE, (void *)atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "sm"))
        {
            rt_device_control(dev, RT_SENSOR_CTRL_SET_MODE, (void *)atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "sp"))
        {
            rt_device_control(dev, RT_SENSOR_CTRL_SET_POWER, (void *)atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "sodr"))
        {
            rt_device_control(dev, RT_SENSOR_CTRL_SET_ODR, (void *)atoi(argv[2]));
        }
        else
        {
            LOG_W("Unknown command, please enter 'sensor' get help information!");
        }
    }
    else
    {
        LOG_W("Unknown command, please enter 'sensor' get help information!");
    }
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(sensor, sensor test function);
#endif
