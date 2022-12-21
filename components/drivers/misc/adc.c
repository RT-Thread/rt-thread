/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-07     aozima       the first version
 * 2018-11-16     Ernest Chen  add finsh command and update adc function
 * 2022-05-11     Stanley Lwin add finsh voltage conversion command
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <string.h>
#include <stdlib.h>

#define DBG_TAG "adc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_size_t _adc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_err_t result = RT_EOK;
    rt_size_t i;
    struct rt_adc_device *adc = (struct rt_adc_device *)dev;
    rt_uint32_t *value = (rt_uint32_t *)buffer;

    for (i = 0; i < size; i += sizeof(int))
    {
        result = adc->ops->convert(adc, pos + i, value);
        if (result != RT_EOK)
        {
            return 0;
        }
        value++;
    }

    return i;
}

static rt_err_t _adc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = -RT_EINVAL;
    rt_adc_device_t adc = (struct rt_adc_device *)dev;

    if (cmd == RT_ADC_CMD_ENABLE && adc->ops->enabled)
    {
        result = adc->ops->enabled(adc, (rt_uint32_t)args, RT_TRUE);
    }
    else if (cmd == RT_ADC_CMD_DISABLE && adc->ops->enabled)
    {
        result = adc->ops->enabled(adc, (rt_uint32_t)args, RT_FALSE);
    }
    else if (cmd == RT_ADC_CMD_GET_RESOLUTION && adc->ops->get_resolution && args)
    {
        rt_uint8_t resolution = adc->ops->get_resolution(adc);
        if(resolution != 0)
        {
            *((rt_uint8_t*)args) = resolution;
            LOG_D("resolution: %d bits", resolution);
            result = RT_EOK;
        }
    }
    else if (cmd == RT_ADC_CMD_GET_VREF && adc->ops->get_vref && args)
    {
        rt_int16_t value = adc->ops->get_vref(adc);
        if(value != 0)
        {
            *((rt_int16_t *) args) = value;
            result = RT_EOK;
        }
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops adc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _adc_read,
    RT_NULL,
    _adc_control,
};
#endif

rt_err_t rt_hw_adc_register(rt_adc_device_t device, const char *name, const struct rt_adc_ops *ops, const void *user_data)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(ops != RT_NULL && ops->convert != RT_NULL);

    device->parent.type = RT_Device_Class_ADC;
    device->parent.rx_indicate = RT_NULL;
    device->parent.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->parent.ops         = &adc_ops;
#else
    device->parent.init        = RT_NULL;
    device->parent.open        = RT_NULL;
    device->parent.close       = RT_NULL;
    device->parent.read        = _adc_read;
    device->parent.write       = RT_NULL;
    device->parent.control     = _adc_control;
#endif
    device->ops = ops;
    device->parent.user_data = (void *)user_data;

    result = rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDWR);

    return result;
}

rt_uint32_t rt_adc_read(rt_adc_device_t dev, rt_uint32_t channel)
{
    rt_uint32_t value;

    RT_ASSERT(dev);

    dev->ops->convert(dev, channel, &value);

    return value;
}

rt_err_t rt_adc_enable(rt_adc_device_t dev, rt_uint32_t channel)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev);

    if (dev->ops->enabled != RT_NULL)
    {
        result = dev->ops->enabled(dev, channel, RT_TRUE);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

rt_err_t rt_adc_disable(rt_adc_device_t dev, rt_uint32_t channel)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev);

    if (dev->ops->enabled != RT_NULL)
    {
        result = dev->ops->enabled(dev, channel, RT_FALSE);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

rt_int16_t rt_adc_voltage(rt_adc_device_t dev, rt_uint32_t channel)
{
    rt_uint32_t value = 0;
    rt_int16_t vref = 0, voltage = 0;
    rt_uint8_t resolution = 0;

    RT_ASSERT(dev);

    /*get the resolution in bits*/
    if (_adc_control((rt_device_t) dev, RT_ADC_CMD_GET_RESOLUTION, &resolution) != RT_EOK)
    {
        goto _voltage_exit;
    }

    /*get the reference voltage*/
    if (_adc_control((rt_device_t) dev, RT_ADC_CMD_GET_VREF, &vref) != RT_EOK)
    {
        goto _voltage_exit;
    }

    /*read the value and convert to voltage*/
    dev->ops->convert(dev, channel, &value);
    voltage = value * vref / (1 << resolution);

_voltage_exit:
    return voltage;
}

#ifdef RT_USING_FINSH

static int adc(int argc, char **argv)
{
    int value = 0;
    rt_int16_t voltage = 0;
    rt_err_t result = -RT_ERROR;
    static rt_adc_device_t adc_device = RT_NULL;
    char *result_str;

    if (argc > 1)
    {
        if (!strcmp(argv[1], "probe"))
        {
            if (argc == 3)
            {
                adc_device = (rt_adc_device_t)rt_device_find(argv[2]);
                result_str = (adc_device == RT_NULL) ? "failure" : "success";
                rt_kprintf("probe %s %s \n", argv[2], result_str);
            }
            else
            {
                rt_kprintf("adc probe <device name>   - probe adc by name\n");
            }
        }
        else
        {
            if (adc_device == RT_NULL)
            {
                rt_kprintf("Please using 'adc probe <device name>' first\n");
                return -RT_ERROR;
            }
            if (!strcmp(argv[1], "enable"))
            {
                if (argc == 3)
                {
                    result = rt_adc_enable(adc_device, atoi(argv[2]));
                    result_str = (result == RT_EOK) ? "success" : "failure";
                    rt_kprintf("%s channel %d enables %s \n", adc_device->parent.parent.name, (rt_base_t)atoi(argv[2]), result_str);
                }
                else
                {
                    rt_kprintf("adc enable <channel>   - enable adc channel\n");
                }
            }
            else if (!strcmp(argv[1], "read"))
            {
                if (argc == 3)
                {
                    value = rt_adc_read(adc_device, atoi(argv[2]));
                    rt_kprintf("%s channel %d  read value is 0x%08X \n", adc_device->parent.parent.name, (rt_base_t)atoi(argv[2]), value);
                }
                else
                {
                    rt_kprintf("adc read <channel>     - read adc value on the channel\n");
                }
            }
            else if (!strcmp(argv[1], "disable"))
            {
                if (argc == 3)
                {
                    result = rt_adc_disable(adc_device, atoi(argv[2]));
                    result_str = (result == RT_EOK) ? "success" : "failure";
                    rt_kprintf("%s channel %d disable %s \n", adc_device->parent.parent.name, (rt_base_t)atoi(argv[2]), result_str);
                }
                else
                {
                    rt_kprintf("adc disable <channel>  - disable adc channel\n");
                }
            }
            else if (!strcmp(argv[1], "voltage"))
            {
                if(argc == 3)
                {
                    voltage = rt_adc_voltage(adc_device, atoi(argv[2]));
                    result_str = (result == RT_EOK) ? "success" : "failure";
                    rt_kprintf("%s channel %d voltage is %d.%03dV \n", adc_device->parent.parent.name, (rt_base_t)atoi(argv[2]), voltage / 1000, voltage % 1000);
                }
                else
                {
                    rt_kprintf("adc convert voltage <channel> \n");
                }
            }
            else
            {
                rt_kprintf("Unknown command. Please enter 'adc' for help\n");
            }
        }
    }
    else
    {
        rt_kprintf("Usage: \n");
        rt_kprintf("adc probe <device name> - probe adc by name\n");
        rt_kprintf("adc read <channel>      - read adc value on the channel\n");
        rt_kprintf("adc disable <channel>   - disable adc channel\n");
        rt_kprintf("adc enable <channel>    - enable adc channel\n");

        result = -RT_ERROR;
    }
    return RT_EOK;
}
MSH_CMD_EXPORT(adc, adc [option]);

#endif /* RT_USING_FINSH */
