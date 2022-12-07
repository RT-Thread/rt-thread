/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-01-31     flybreak       first version
 * 2019-07-16     WillianChan    Increase the output of sensor information
 * 2020-02-22     luhuadong      Add vendor info and sensor types for cmd
 */

#include <drivers/sensor.h>

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
        LOG_I("num:%d, x:%f, y:%f, z:%f mg, timestamp:%u", num, sensor_data->data.acce.x, sensor_data->data.acce.y, sensor_data->data.acce.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_GYRO:
        LOG_I("num:%d, x:%f, y:%f, z:%f dps, timestamp:%u", num, sensor_data->data.gyro.x, sensor_data->data.gyro.y, sensor_data->data.gyro.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_MAG:
        LOG_I("num:%d, x:%f, y:%f, z:%f mGauss, timestamp:%u", num, sensor_data->data.mag.x, sensor_data->data.mag.y, sensor_data->data.mag.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_GNSS:
        LOG_I("num:%d, lon:%f, lat:%f, timestamp:%u", num, sensor_data->data.coord.longitude, sensor_data->data.coord.latitude, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_TEMP:
        LOG_I("num:%d, temp:%f C, timestamp:%u", num, sensor_data->data.temp, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_HUMI:
        LOG_I("num:%d, humi:%f%%, timestamp:%u", num, sensor_data->data.humi, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_BARO:
        LOG_I("num:%d, press:%f pa, timestamp:%u", num, sensor_data->data.baro, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_LIGHT:
        LOG_I("num:%d, light:%f lux, timestamp:%u", num, sensor_data->data.light, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_PROXIMITY:
    case RT_SENSOR_CLASS_TOF:
        LOG_I("num:%d, distance:%f, timestamp:%u", num, sensor_data->data.proximity, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_HR:
        LOG_I("num:%d, heart rate:%f bpm, timestamp:%u", num, sensor_data->data.hr, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_TVOC:
        LOG_I("num:%d, tvoc:%f ppb, timestamp:%u", num, sensor_data->data.tvoc, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_NOISE:
        LOG_I("num:%d, noise:%f, timestamp:%u", num, sensor_data->data.noise, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_STEP:
        LOG_I("num:%d, step:%f, timestamp:%u", num, sensor_data->data.step, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_FORCE:
        LOG_I("num:%d, force:%f, timestamp:%u", num, sensor_data->data.force, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_DUST:
        LOG_I("num:%d, dust:%f ug/m3, timestamp:%u", num, sensor_data->data.dust, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_ECO2:
        LOG_I("num:%d, eco2:%f ppm, timestamp:%u", num, sensor_data->data.eco2, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_IAQ:
        LOG_I("num:%d, IAQ:%f, timestamp:%u", num, sensor_data->data.iaq, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_ETOH:
        LOG_I("num:%d, EtOH:%f ppm, timestamp:%u", num, sensor_data->data.etoh, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_BP:
        LOG_I("num:%d, bp.sbp:%f mmHg, bp.dbp:%f mmHg, timestamp:%u", num, sensor_data->data.bp.sbp, sensor_data->data.bp.dbp, sensor_data->timestamp);
        break;
    default:
        LOG_E("Unknown type of sensor!");
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
#ifdef RT_USING_FINSH
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
#ifdef RT_USING_FINSH
    MSH_CMD_EXPORT(sensor_int, Sensor interrupt mode test function);
#endif

static void sensor_polling(int argc, char **argv)
{
    rt_uint16_t num = 10;
    rt_device_t dev = RT_NULL;
    rt_sensor_t sensor;
    struct rt_sensor_data data;
    rt_size_t res, i;
    rt_int32_t delay;
    rt_err_t result;

    dev = rt_device_find(argv[1]);
    if (dev == RT_NULL)
    {
        LOG_E("Can't find device:%s", argv[1]);
        return;
    }
    if (argc > 2)
        num = atoi(argv[2]);

    sensor = (rt_sensor_t)dev;
    delay  = sensor->info.period_min > 100 ? sensor->info.period_min : 100;

    result = rt_device_open(dev, RT_DEVICE_FLAG_RDONLY);
    if (result != RT_EOK)
    {
        LOG_E("open device failed! error code : %d", result);
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
        rt_thread_mdelay(delay);
    }
    rt_device_close(dev);
}
#ifdef RT_USING_FINSH
    MSH_CMD_EXPORT(sensor_polling, Sensor polling mode test function);
#endif

static void sensor(int argc, char **argv)
{
    static rt_device_t dev = RT_NULL;
    struct rt_sensor_data data;
    rt_sensor_t sensor;
    rt_size_t res, i;
    rt_int32_t delay;

    /* If the number of arguments less than 2 */
    if (argc < 2)
    {
        rt_kprintf("\n");
        rt_kprintf("sensor  [OPTION] [PARAM]\n");
        rt_kprintf("         probe <dev_name>      Probe sensor by given name\n");
        rt_kprintf("         info                  Get sensor info\n");
        rt_kprintf("         range <var>           Set range to var\n");
        rt_kprintf("         mode <var>            Set work mode to var\n");
        rt_kprintf("         power <var>           Set power mode to var\n");
        rt_kprintf("         rate <var>            Set output date rate to var\n");
        rt_kprintf("         read [num]            Read [num] times sensor (default 5)\n");
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
        case RT_SENSOR_VENDOR_TI:
            rt_kprintf("vendor    :Texas Instruments\n");
            break;
        case RT_SENSOR_VENDOR_PLANTOWER:
            rt_kprintf("vendor    :Plantower\n");
            break;
        case RT_SENSOR_VENDOR_AMS:
            rt_kprintf("vendor    :AMS\n");
            break;
        case RT_SENSOR_VENDOR_MAXIM:
            rt_kprintf("vendor    :Maxim Integrated\n");
            break;
        case RT_SENSOR_VENDOR_MELEXIS:
            rt_kprintf("vendor    :Melexis\n");
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
        case RT_SENSOR_UNIT_PPM:
            rt_kprintf("unit      :ppm\n");
            break;
        case RT_SENSOR_UNIT_PPB:
            rt_kprintf("unit      :ppb\n");
            break;
        case RT_SENSOR_UNIT_MMHG:
            rt_kprintf("unit      :mmHg\n");
            break;
        }
        rt_kprintf("range_max :%d\n", info.range_max);
        rt_kprintf("range_min :%d\n", info.range_min);
        rt_kprintf("period_min:%dms\n", info.period_min);
        rt_kprintf("fifo_max  :%d\n", info.fifo_max);
    }
    else if (!strcmp(argv[1], "read"))
    {
        rt_uint16_t num = 5;

        if (dev == RT_NULL)
        {
            LOG_W("Please probe sensor device first!");
            return ;
        }
        if (argc == 3)
        {
            num = atoi(argv[2]);
        }

        sensor = (rt_sensor_t)dev;
        delay  = sensor->info.period_min > 100 ? sensor->info.period_min : 100;

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
            rt_thread_mdelay(delay);
        }
    }
    else if (argc == 3)
    {
        if (!strcmp(argv[1], "probe"))
        {
            rt_uint8_t reg = 0xFF;
            rt_device_t new_dev;

            new_dev = rt_device_find(argv[2]);
            if (new_dev == RT_NULL)
            {
                LOG_E("Can't find device:%s", argv[2]);
                return;
            }
            if (rt_device_open(new_dev, RT_DEVICE_FLAG_RDWR) != RT_EOK)
            {
                LOG_E("open device failed!");
                return;
            }
            rt_device_control(new_dev, RT_SENSOR_CTRL_GET_ID, &reg);
            LOG_I("device id: 0x%x!", reg);
            if (dev)
            {
                rt_device_close(dev);
            }
            dev = new_dev;
        }
        else if (dev == RT_NULL)
        {
            LOG_W("Please probe sensor first!");
            return ;
        }
        else if (!strcmp(argv[1], "range"))
        {
            rt_device_control(dev, RT_SENSOR_CTRL_SET_RANGE, (void *)atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "mode"))
        {
            rt_device_control(dev, RT_SENSOR_CTRL_SET_MODE, (void *)atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "power"))
        {
            rt_device_control(dev, RT_SENSOR_CTRL_SET_POWER, (void *)atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "rate"))
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
#ifdef RT_USING_FINSH
    MSH_CMD_EXPORT(sensor, sensor test function);
#endif
