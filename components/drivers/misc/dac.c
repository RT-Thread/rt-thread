/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-19     thread-liu   the first version
 */

#include <rtdevice.h>

#include <string.h>
#include <stdlib.h>

#define DBG_TAG "dac"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_size_t _dac_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_err_t result = RT_EOK;
    rt_size_t i;
    struct rt_dac_device *dac = (struct rt_dac_device *)dev;
    rt_uint32_t *value = (rt_uint32_t *)buffer;

    for (i = 0; i < size; i += sizeof(int))
    {
        result = dac->ops->convert(dac, pos + i, value);
        if (result != RT_EOK)
        {
            return 0;
        }
        value++;
    }

    return i;
}

static rt_err_t _dac_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = -RT_EINVAL;
    rt_dac_device_t dac = (struct rt_dac_device *)dev;

    if (cmd == RT_DAC_CMD_ENABLE && dac->ops->enabled)
    {
        result = dac->ops->enabled(dac, (rt_uint32_t)args);
    }
    else if (cmd == RT_DAC_CMD_DISABLE && dac->ops->enabled)
    {
        result = dac->ops->disabled(dac, (rt_uint32_t)args);
    }
    else if (cmd == RT_DAC_CMD_GET_RESOLUTION && dac->ops->get_resolution)
    {
        rt_uint8_t resolution = dac->ops->get_resolution(dac);
        if(resolution != 0)
        {
            *((rt_uint8_t*)args) = resolution;
            LOG_D("resolution: %d bits", resolution);
            result = RT_EOK;
        }
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops dac_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _dac_write,
    _dac_control,
};
#endif

rt_err_t rt_hw_dac_register(rt_dac_device_t device, const char *name, const struct rt_dac_ops *ops, const void *user_data)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(ops != RT_NULL && ops->convert != RT_NULL);

    device->parent.type = RT_Device_Class_DAC;
    device->parent.rx_indicate = RT_NULL;
    device->parent.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->parent.ops         = &dac_ops;
#else
    device->parent.init        = RT_NULL;
    device->parent.open        = RT_NULL;
    device->parent.close       = RT_NULL;
    device->parent.read        = RT_NULL;
    device->parent.write       = _dac_write;
    device->parent.control     = _dac_control;
#endif
    device->ops = ops;
    device->parent.user_data = (void *)user_data;

    result = rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDWR);

    return result;
}

rt_err_t rt_dac_write(rt_dac_device_t dev, rt_uint32_t channel, rt_uint32_t value)
{
    RT_ASSERT(dev);

    return dev->ops->convert(dev, channel, &value);
}

rt_err_t rt_dac_enable(rt_dac_device_t dev, rt_uint32_t channel)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev);
    if (dev->ops->enabled != RT_NULL)
    {
        result = dev->ops->enabled(dev, channel);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

rt_err_t rt_dac_disable(rt_dac_device_t dev, rt_uint32_t channel)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev);
    if (dev->ops->disabled != RT_NULL)
    {
        result = dev->ops->disabled(dev, channel);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

#ifdef RT_USING_FINSH

static int dac(int argc, char **argv)
{
    int result = RT_EOK;
    static rt_dac_device_t dac_device = RT_NULL;
    char *result_str;

    if (argc > 1)
    {
        if (!strcmp(argv[1], "probe"))
        {
            if (argc == 3)
            {
                dac_device = (rt_dac_device_t)rt_device_find(argv[2]);
                result_str = (dac_device == RT_NULL) ? "failure" : "success";
                rt_kprintf("probe %s %s \n", argv[2], result_str);
            }
            else
            {
                rt_kprintf("dac probe <dac_name>   - probe dac by name\n");
            }
        }
        else
        {
            if (dac_device == RT_NULL)
            {
                rt_kprintf("Please using 'dac probe <dac_name>' first\n");
                return -RT_ERROR;
            }
            if (!strcmp(argv[1], "enable"))
            {
                if (argc == 3)
                {
                    result = rt_dac_enable(dac_device, atoi(argv[2]));
                    result_str = (result == RT_EOK) ? "success" : "failure";
                    rt_kprintf("%s channel %d enables %s \n", dac_device->parent.parent.name, atoi(argv[2]), result_str);
                }
                else
                {
                    rt_kprintf("dac enable <channel>   - enable dac channel\n");
                }
            }
            else if (!strcmp(argv[1], "write"))
            {
                if (argc == 4)
                {
                    rt_dac_write(dac_device, atoi(argv[2]), atoi(argv[3]));
                    rt_kprintf("%s channel %d write value is %d \n", dac_device->parent.parent.name, atoi(argv[2]), atoi(argv[3]));
                }
                else
                {
                    rt_kprintf("dac write <channel> <value>     - write dac value on the channel\n");
                }
            }
            else if (!strcmp(argv[1], "disable"))
            {
                if (argc == 3)
                {
                    result = rt_dac_disable(dac_device, atoi(argv[2]));
                    result_str = (result == RT_EOK) ? "success" : "failure";
                    rt_kprintf("%s channel %d disable %s \n", dac_device->parent.parent.name, atoi(argv[2]), result_str);
                }
                else
                {
                    rt_kprintf("dac disable <channel>  - disable dac channel\n");
                }
            }
            else
            {
                rt_kprintf("Unknown command. Please enter 'dac' for help\n");
            }
        }
    }
    else
    {
        rt_kprintf("Usage: \n");
        rt_kprintf("dac probe <dac_name>           - probe dac by name\n");
        rt_kprintf("dac write <channel> <value>    - write dac value on the channel\n");
        rt_kprintf("dac disable <channel>          - disable dac channel\n");
        rt_kprintf("dac enable <channel>           - enable dac channel\n");
        result = -RT_ERROR;
    }
    return RT_EOK;
}
MSH_CMD_EXPORT(dac, dac function);

#endif /* RT_USING_FINSH */
