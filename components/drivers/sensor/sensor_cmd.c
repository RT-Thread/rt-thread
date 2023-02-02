/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-01-31     flybreak       first version
 * 2019-07-16     WillianChan    Increase the output of sensor information
 * 2020-02-22     luhuadong      Add vendor info and sensor types for cmd
 * 2022-12-17     Meco Man       re-implement sensor framework
 */

#include <drivers/sensor.h>

#define DBG_TAG  "sensor.cmd"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stdlib.h>
#include <string.h>

static rt_sem_t sensor_rx_sem = RT_NULL;

static const char *sensor_get_type_name(rt_sensor_info_t info)
{
    switch(info->type)
    {
        case RT_SENSOR_TYPE_ACCE:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_ACCE);
        case RT_SENSOR_TYPE_GYRO:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_GYRO);
        case RT_SENSOR_TYPE_MAG:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_MAG);
        case RT_SENSOR_TYPE_TEMP:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_TEMP);
        case RT_SENSOR_TYPE_HUMI:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_HUMI);
        case RT_SENSOR_TYPE_BARO:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_BARO);
        case RT_SENSOR_TYPE_LIGHT:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_LIGHT);
        case RT_SENSOR_TYPE_PROXIMITY:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_PROXIMITY);
        case RT_SENSOR_TYPE_HR:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_HR);
        case RT_SENSOR_TYPE_TVOC:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_TVOC);
        case RT_SENSOR_TYPE_NOISE:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_NOISE);
        case RT_SENSOR_TYPE_STEP:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_STEP);
        case RT_SENSOR_TYPE_FORCE:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_FORCE);
        case RT_SENSOR_TYPE_DUST:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_DUST);
        case RT_SENSOR_TYPE_ECO2:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_ECO2);
        case RT_SENSOR_TYPE_GNSS:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_GNSS);
        case RT_SENSOR_TYPE_TOF:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_TOF);
        case RT_SENSOR_TYPE_SPO2:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_SPO2);
        case RT_SENSOR_TYPE_IAQ:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_IAQ);
        case RT_SENSOR_TYPE_ETOH:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_ETOH);
        case RT_SENSOR_TYPE_BP:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_BP);
        case RT_SENSOR_TYPE_VOLTAGE:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_VOLTAGE);
        case RT_SENSOR_TYPE_CURRENT:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_CURRENT);
        case RT_SENSOR_TYPE_NONE:
        default:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_TYPE_NONE);
    }
}

static const char *sensor_get_vendor_name(rt_sensor_info_t info)
{
    switch(info->vendor)
    {
        case RT_SENSOR_VENDOR_VIRTUAL:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_VIRTUAL);
        case RT_SENSOR_VENDOR_ONCHIP:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_ONCHIP);
        case RT_SENSOR_VENDOR_STM:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_STM);
        case RT_SENSOR_VENDOR_BOSCH:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_BOSCH);
        case RT_SENSOR_VENDOR_INVENSENSE:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_INVENSENSE);
        case RT_SENSOR_VENDOR_SEMTECH:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_SEMTECH);
        case RT_SENSOR_VENDOR_GOERTEK:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_GOERTEK);
        case RT_SENSOR_VENDOR_MIRAMEMS:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_MIRAMEMS);
        case RT_SENSOR_VENDOR_DALLAS:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_DALLAS);
        case RT_SENSOR_VENDOR_ASAIR:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_ASAIR);
        case RT_SENSOR_VENDOR_SHARP:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_SHARP);
        case RT_SENSOR_VENDOR_SENSIRION:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_SENSIRION);
        case RT_SENSOR_VENDOR_TI:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_TI);
        case RT_SENSOR_VENDOR_PLANTOWER:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_PLANTOWER);
        case RT_SENSOR_VENDOR_AMS:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_AMS);
        case RT_SENSOR_VENDOR_MAXIM:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_MAXIM);
        case RT_SENSOR_VENDOR_MELEXIS:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_MELEXIS);
        case RT_SENSOR_VENDOR_LSC:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_LSC);
        case RT_SENSOR_VENDOR_UNKNOWN:
        default:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_VENDOR_UNKNOWN);
    }
}

static const char *sensor_get_unit_name(rt_sensor_info_t info)
{
    switch(info->unit)
    {
        case RT_SENSOR_UNIT_MG:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_MG);
        case RT_SENSOR_UNIT_MDPS:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_MDPS);
        case RT_SENSOR_UNIT_MGAUSS:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_MGAUSS);
        case RT_SENSOR_UNIT_LUX:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_LUX);
        case RT_SENSOR_UNIT_M:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_M);
        case RT_SENSOR_UNIT_CM:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_CM);
        case RT_SENSOR_UNIT_MM:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_MM);
        case RT_SENSOR_UNIT_PA:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_PA);
        case RT_SENSOR_UNIT_MMHG:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_MMHG);
        case RT_SENSOR_UNIT_PERCENTAGE:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_PERCENTAGE);
        case RT_SENSOR_UNIT_PERMILLAGE:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_PERMILLAGE);
        case RT_SENSOR_UNIT_CELSIUS:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_CELSIUS);
        case RT_SENSOR_UNIT_FAHRENHEIT:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_FAHRENHEIT);
        case RT_SENSOR_UNIT_KELVIN:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_KELVIN);
        case RT_SENSOR_UNIT_HZ:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_HZ);
        case RT_SENSOR_UNIT_V:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_V);
        case RT_SENSOR_UNIT_MV:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_MV);
        case RT_SENSOR_UNIT_A:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_A);
        case RT_SENSOR_UNIT_MA:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_MA);
        case RT_SENSOR_UNIT_N:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_N);
        case RT_SENSOR_UNIT_MN:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_MN);
        case RT_SENSOR_UNIT_BPM:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_BPM);
        case RT_SENSOR_UNIT_PPM:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_PPM);
        case RT_SENSOR_UNIT_PPB:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_PPB);
        case RT_SENSOR_UNIT_DMS:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_DMS);
        case RT_SENSOR_UNIT_DD:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_DD);
        case RT_SENSOR_UNIT_MGM3:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_MGM3);
        case RT_SENSOR_UNIT_NONE:
        default:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_UNIT_NONE);
    }
}

static const char* sensor_get_accuracy_mode_name(rt_sensor_info_t info)
{
    switch(RT_SENSOR_MODE_GET_ACCURACY(info->mode))
    {
        case RT_SENSOR_MODE_ACCURACY_HIGHEST:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_ACCURACY_HIGHEST);
        case RT_SENSOR_MODE_ACCURACY_HIGH:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_ACCURACY_HIGH);
        case RT_SENSOR_MODE_ACCURACY_MEDIUM:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_ACCURACY_MEDIUM);
        case RT_SENSOR_MODE_ACCURACY_LOW:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_ACCURACY_LOW);
        case RT_SENSOR_MODE_ACCURACY_LOWEST:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_ACCURACY_LOWEST);
        case RT_SENSOR_MODE_ACCURACY_NOTRUST:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_ACCURACY_NOTRUST);
        default:
            rt_kprintf("accuracy mode illegal!\n");
            return "";
    }
}

static const char* sensor_get_power_mode_name(rt_sensor_info_t info)
{
    switch(RT_SENSOR_MODE_GET_POWER(info->mode))
    {
        case RT_SENSOR_MODE_POWER_HIGHEST:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_POWER_HIGHEST);
        case RT_SENSOR_MODE_POWER_HIGH:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_POWER_HIGH);
        case RT_SENSOR_MODE_POWER_MEDIUM:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_POWER_MEDIUM);
        case RT_SENSOR_MODE_POWER_LOW:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_POWER_LOW);
        case RT_SENSOR_MODE_POWER_LOWEST:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_POWER_LOWEST);
        case RT_SENSOR_MODE_POWER_DOWN:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_POWER_DOWN);
        default:
            rt_kprintf("power mode illegal!\n");
            return "";
    }
}

static const char* sensor_get_fetch_mode_name(rt_sensor_info_t info)
{
    switch(RT_SENSOR_MODE_GET_FETCH(info->mode))
    {
        case RT_SENSOR_MODE_FETCH_POLLING:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_FETCH_POLLING);
        case RT_SENSOR_MODE_FETCH_INT:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_FETCH_INT);
        case RT_SENSOR_MODE_FETCH_FIFO:
            return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_MODE_FETCH_FIFO);
        default:
            rt_kprintf("fetch data mode illegal!\n");
            return "";
    }
}

static void sensor_show_data(rt_size_t num, rt_sensor_t sensor, struct rt_sensor_data *sensor_data)
{
    const char *unit_name = sensor_get_unit_name(&sensor->info);
    switch (sensor->info.type)
    {
    case RT_SENSOR_TYPE_ACCE:
        rt_kprintf("num:%d, x:%f, y:%f, z:%f %s, timestamp:%u\n", num, sensor_data->data.acce.x, sensor_data->data.acce.y, sensor_data->data.acce.z, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_GYRO:
        rt_kprintf("num:%d, x:%f, y:%f, z:%f %s, timestamp:%u\n", num, sensor_data->data.gyro.x, sensor_data->data.gyro.y, sensor_data->data.gyro.z, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_MAG:
        rt_kprintf("num:%d, x:%f, y:%f, z:%f %s, timestamp:%u\n", num, sensor_data->data.mag.x, sensor_data->data.mag.y, sensor_data->data.mag.z, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_GNSS:
        rt_kprintf("num:%d, lon:%f, lat:%f %s, timestamp:%u\n", num, sensor_data->data.coord.longitude, sensor_data->data.coord.latitude, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_TEMP:
        rt_kprintf("num:%d, temp:%f%s, timestamp:%u\n", num, sensor_data->data.temp, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_HUMI:
        rt_kprintf("num:%d, humi:%f%s, timestamp:%u\n", num, sensor_data->data.humi, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_BARO:
        rt_kprintf("num:%d, press:%f%s, timestamp:%u\n", num, sensor_data->data.baro, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_LIGHT:
        rt_kprintf("num:%d, light:%f%s, timestamp:%u\n", num, sensor_data->data.light, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_PROXIMITY:
    case RT_SENSOR_TYPE_TOF:
        rt_kprintf("num:%d, distance:%f%s, timestamp:%u\n", num, sensor_data->data.proximity, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_HR:
        rt_kprintf("num:%d, heart rate:%f%s, timestamp:%u\n", num, sensor_data->data.hr, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_TVOC:
        rt_kprintf("num:%d, tvoc:%f%s, timestamp:%u\n", num, sensor_data->data.tvoc, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_NOISE:
        rt_kprintf("num:%d, noise:%f%s, timestamp:%u\n", num, sensor_data->data.noise, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_STEP:
        rt_kprintf("num:%d, step:%f%s, timestamp:%u\n", num, sensor_data->data.step, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_FORCE:
        rt_kprintf("num:%d, force:%f%s, timestamp:%u\n", num, sensor_data->data.force, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_DUST:
        rt_kprintf("num:%d, dust:%f%s, timestamp:%u\n", num, sensor_data->data.dust, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_ECO2:
        rt_kprintf("num:%d, eco2:%f%s, timestamp:%u\n", num, sensor_data->data.eco2, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_IAQ:
        rt_kprintf("num:%d, IAQ:%f%s, timestamp:%u\n", num, sensor_data->data.iaq, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_ETOH:
        rt_kprintf("num:%d, EtOH:%f%s, timestamp:%u\n", num, sensor_data->data.etoh, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_BP:
        rt_kprintf("num:%d, bp.sbp:%f, bp.dbp:%f %s, timestamp:%u\n", num, sensor_data->data.bp.sbp, sensor_data->data.bp.dbp, unit_name, sensor_data->timestamp);
        break;
    case RT_SENSOR_TYPE_NONE:
    default:
        rt_kprintf("Unknown type of sensor!\n");
        break;
    }
}

static const char* sensor_get_intf_name(rt_sensor_t sensor)
{
    rt_uint8_t type = sensor->config.intf.type;

    if (type | RT_SENSOR_INTF_I2C)
    {
        return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_INTF_I2C);
    }
    else if (type | RT_SENSOR_INTF_SPI)
    {
        return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_INTF_SPI);
    }
    else if (type | RT_SENSOR_INTF_UART)
    {
        return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_INTF_UART);
    }
    else if (type | RT_SENSOR_INTF_ONEWIRE)
    {
        return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_INTF_ONEWIRE);
    }
    else if (type | RT_SENSOR_INTF_CAN)
    {
        return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_INTF_CAN);
    }
    else if (type | RT_SENSOR_INTF_MODBUS)
    {
        return RT_SENSOR_MACRO_GET_NAME(RT_SENSOR_INTF_MODBUS);
    }
    else
    {
        return "";
    }
}

static rt_err_t rx_callback(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(sensor_rx_sem);
    return 0;
}

static void sensor_fifo_rx_entry(void *parameter)
{
    rt_sensor_t sensor = (rt_sensor_t)parameter;
    struct rt_sensor_data *data = RT_NULL;
    rt_size_t res, i;

    data = (struct rt_sensor_data *)rt_calloc(sensor->info.fifo_max, sizeof(struct rt_sensor_data));
    if (data == RT_NULL)
    {
        LOG_E("Memory allocation failed!");
    }

    while (1)
    {
        rt_sem_take(sensor_rx_sem, RT_WAITING_FOREVER);

        res = rt_device_read((rt_device_t)sensor, 0, data, sensor->info.fifo_max);
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
}
MSH_CMD_EXPORT(sensor_fifo, Sensor fifo mode test function);

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
}
MSH_CMD_EXPORT(sensor_int, Sensor interrupt mode test function);

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
    delay  = sensor->info.acquire_min > 100 ? sensor->info.acquire_min : 100;

    result = rt_device_open(dev, RT_DEVICE_FLAG_RDONLY);
    if (result != RT_EOK)
    {
        LOG_E("open device failed! error code : %d", result);
        return;
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
            sensor_show_data(i, sensor, &data);
        }
        rt_thread_mdelay(delay);
    }
    rt_device_close(dev);
}
MSH_CMD_EXPORT(sensor_polling, Sensor polling mode test function);

static void sensor_cmd_warning_unknown(void)
{
    LOG_W("Unknown command, please enter 'sensor' get help information!");
    rt_kprintf("sensor  [OPTION] [PARAM]\n");
    rt_kprintf("         list                  list all sensor devices\n");
    rt_kprintf("         probe <dev_name>      probe sensor by given name\n");
    rt_kprintf("         info                  get sensor information\n");
    rt_kprintf("         read [num]            read [num] times sensor (default 5)\n");
    rt_kprintf("         power [mode]          set or get power mode\n");
    rt_kprintf("         accuracy [mode]       set or get accuracy mode\n");
    rt_kprintf("         fetch [mode]          set or get fetch data mode\n");
    rt_kprintf("         reset                 reset sensor chip\n");
}

static void sensor_cmd_warning_probe(void)
{
    LOG_W("Please probe sensor device first!");
}

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
        sensor_cmd_warning_unknown();
        return;
    }
    else if (!rt_strcmp(argv[1], "info"))
    {
        if (dev == RT_NULL)
        {
            sensor_cmd_warning_probe();
            return ;
        }
        sensor = (rt_sensor_t)dev;
        rt_kprintf("name      :%s\n", sensor->info.name);
        rt_kprintf("type:     :%s\n", sensor_get_type_name(&sensor->info));
        rt_kprintf("vendor    :%s\n", sensor_get_vendor_name(&sensor->info));
        rt_kprintf("unit      :%s\n", sensor_get_unit_name(&sensor->info));
        rt_kprintf("fetch data:%s\n", sensor_get_fetch_mode_name(&sensor->info));
        rt_kprintf("power     :%s\n", sensor_get_power_mode_name(&sensor->info));
        rt_kprintf("accuracy  :%s\n", sensor_get_accuracy_mode_name(&sensor->info));
        rt_kprintf("range max :%f\n", sensor->info.scale.range_max);
        rt_kprintf("range min :%f\n", sensor->info.scale.range_min);
        rt_kprintf("resolution:%f\n", sensor->info.accuracy.resolution);
        rt_kprintf("error     :%f\n", sensor->info.accuracy.error);
        rt_kprintf("acquire min:%fms\n", sensor->info.acquire_min);
        rt_kprintf("fifo max  :%d\n", sensor->info.fifo_max);
        rt_kprintf("interface type   :%s\n", sensor_get_intf_name(sensor));
        rt_kprintf("interface device :%s\n", sensor->config.intf.dev_name);
    }
    else if (!rt_strcmp(argv[1], "read"))
    {
        rt_uint16_t num = 5;

        if (dev == RT_NULL)
        {
            sensor_cmd_warning_probe();
            return;
        }
        if (argc == 3)
        {
            num = atoi(argv[2]);
        }

        sensor = (rt_sensor_t)dev;
        delay  = sensor->info.acquire_min > 100 ? sensor->info.acquire_min : 100;

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
    else if (!rt_strcmp(argv[1], "list"))
    {
        struct rt_object *object;
        struct rt_list_node *node;
        struct rt_object_information *information;
        rt_sensor_t sensor_dev;

        information = rt_object_get_information(RT_Object_Class_Device);
        if(information == RT_NULL)
            return;

        rt_kprintf("device name sensor name      sensor type     mode resolution range\n");
        rt_kprintf("----------- ------------- ------------------ ---- ---------- ----------\n");
        for (node  = information->object_list.next;
             node != &(information->object_list);
             node  = node->next)
        {
            object = rt_list_entry(node, struct rt_object, list);
            sensor_dev   = (rt_sensor_t)object;
            if (sensor_dev->parent.type != RT_Device_Class_Sensor)
                continue;

            rt_kprintf("%-*.*s %-*s %-*s %u%u%u  %-*f %.*f - %.*f%-*s\n",
            RT_NAME_MAX+3, RT_NAME_MAX, sensor_dev->parent.parent.name,
            13, sensor_dev->info.name,
            18, sensor_get_type_name(&sensor_dev->info),
            RT_SENSOR_MODE_GET_ACCURACY(sensor_dev->info.mode), RT_SENSOR_MODE_GET_POWER(sensor_dev->info.mode), RT_SENSOR_MODE_GET_FETCH(sensor_dev->info.mode),
            10, sensor_dev->info.accuracy.resolution,
            2, sensor_dev->info.scale.range_min, 2, sensor_dev->info.scale.range_max, 5, sensor_get_unit_name(&sensor_dev->info));
        }
    }
    else if (!rt_strcmp(argv[1], "reset"))
    {
        if (dev == RT_NULL)
        {
            sensor_cmd_warning_probe();
            return;
        }

        if (rt_device_control(dev, RT_SENSOR_CTRL_SOFT_RESET, RT_NULL) != RT_EOK)
        {
            LOG_E("This sensor doesn't support this command!");
        }
    }
    else if (!rt_strcmp(argv[1], "probe"))
    {
        rt_uint8_t reg = 0xFF;
        rt_device_t new_dev;

        if (argc < 3)
        {
            sensor_cmd_warning_unknown();
            return;
        }

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
        if (rt_device_control(new_dev, RT_SENSOR_CTRL_GET_ID, &reg) == RT_EOK)
        {
            rt_kprintf("Sensor Chip ID: %#x\n", reg);
        }
        if (dev)
        {
            rt_device_close(dev);
        }
        dev = new_dev;
    }
    else if (!rt_strcmp(argv[1], "power"))
    {
        rt_uint32_t mode;

        if (dev == RT_NULL)
        {
            sensor_cmd_warning_probe();
            return;
        }

        sensor = (rt_sensor_t)dev;
        if (argc == 2)
        {
            rt_kprintf("current power mode: %s\n", sensor_get_power_mode_name(&sensor->info));
        }
        else if (argc == 3)
        {
            mode = atoi(argv[2]);
            if (rt_device_control(dev, RT_SENSOR_CTRL_SET_POWER_MODE, (void *)mode) == RT_EOK)
            {
                rt_kprintf("set new power mode as: %s\n", sensor_get_power_mode_name(&sensor->info));
            }
            else
            {
                LOG_E("Don't support! Set new power mode error!");
            }
        }
        else
        {
            sensor_cmd_warning_unknown();
        }
    }
    else if (!rt_strcmp(argv[1], "accuracy"))
    {
        rt_uint32_t mode;

        if (dev == RT_NULL)
        {
            sensor_cmd_warning_probe();
            return;
        }

        sensor = (rt_sensor_t)dev;
        if (argc == 2)
        {
            rt_kprintf("current accuracy mode: %s\n", sensor_get_accuracy_mode_name(&sensor->info));
        }
        else if (argc == 3)
        {
            mode = atoi(argv[2]);
            if (rt_device_control(dev, RT_SENSOR_CTRL_SET_ACCURACY_MODE, (void *)mode) == RT_EOK)
            {
                rt_kprintf("set new accuracy mode as: %s\n", sensor_get_accuracy_mode_name(&sensor->info));
            }
            else
            {
                LOG_E("Don't support! Set new accuracy mode error!");
            }
        }
        else
        {
            sensor_cmd_warning_unknown();
        }
    }
    else if (!rt_strcmp(argv[1], "fetch"))
    {
        rt_uint32_t mode;

        if (dev == RT_NULL)
        {
            sensor_cmd_warning_probe();
            return;
        }

        sensor = (rt_sensor_t)dev;
        if (argc == 2)
        {
            rt_kprintf("current fetch data mode: %s\n", sensor_get_fetch_mode_name(&sensor->info));
        }
        else if (argc == 3)
        {
            mode = atoi(argv[2]);
            if (rt_device_control(dev, RT_SENSOR_CTRL_SET_FETCH_MODE, (void *)mode) == RT_EOK)
            {
                rt_kprintf("set new fetch data mode as: %s\n", sensor_get_fetch_mode_name(&sensor->info));
            }
            else
            {
                LOG_E("Don't support! Set new fetch data mode error!");
            }
        }
        else
        {
            sensor_cmd_warning_unknown();
        }
    }
    else
    {
        sensor_cmd_warning_unknown();
    }
}
MSH_CMD_EXPORT(sensor, sensor test function);
