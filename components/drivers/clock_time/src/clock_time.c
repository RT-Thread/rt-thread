/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-01     RT-Thread    Unified clock_time subsystem implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/clock_time.h>

#define DBG_TAG "clock_time"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* Default system clock time device */
static rt_clock_time_t _default_device = RT_NULL;

/**
 * @brief Register a clock time device
 */
rt_err_t rt_clock_time_device_register(struct rt_clock_time_device *dev,
                                        const char *name,
                                        rt_uint8_t caps)
{
    rt_err_t result;
    
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(name != RT_NULL);
    RT_ASSERT(dev->ops != RT_NULL);
    
    /* Initialize parent device structure */
    dev->parent.type = RT_Device_Class_Timer;
    dev->parent.rx_indicate = RT_NULL;
    dev->parent.tx_complete = RT_NULL;
    
    dev->parent.init = RT_NULL;
    dev->parent.open = RT_NULL;
    dev->parent.close = RT_NULL;
    dev->parent.read = RT_NULL;
    dev->parent.write = RT_NULL;
    dev->parent.control = RT_NULL;
    
    dev->caps = caps;
    
    /* Calculate resolution scale factor */
    if (dev->ops->get_freq)
    {
        rt_uint64_t freq = dev->ops->get_freq();
        if (freq > 0)
        {
            /* res_scale = (1e9 * RT_CLOCK_TIME_RESMUL) / freq 
             * To avoid overflow, we check if freq is very small.
             * For freq >= 1000, this calculation is safe on 64-bit.
             * For very small frequencies, limit the scale factor.
             */
            if (freq >= 1000)
            {
                dev->res_scale = ((1000000000ULL * RT_CLOCK_TIME_RESMUL) / freq);
            }
            else
            {
                /* For very low frequencies, calculate more carefully */
                dev->res_scale = (1000000ULL * RT_CLOCK_TIME_RESMUL) / freq * 1000;
            }
        }
        else
        {
            dev->res_scale = RT_CLOCK_TIME_RESMUL;
        }
    }
    else
    {
        dev->res_scale = RT_CLOCK_TIME_RESMUL;
    }
    
    /* Register device */
    result = rt_device_register(&dev->parent, name, RT_DEVICE_FLAG_RDWR);
    if (result != RT_EOK)
    {
        LOG_E("Failed to register clock_time device: %s", name);
        return result;
    }
    
    /* Set as default if none exists */
    if (_default_device == RT_NULL)
    {
        _default_device = dev;
        LOG_D("Set %s as default clock_time device", name);
    }
    
    LOG_I("Registered clock_time device: %s (caps: 0x%02x)", name, caps);
    
    return RT_EOK;
}

/**
 * @brief Get the default system clock time device
 */
rt_clock_time_t rt_clock_time_default(void)
{
    return _default_device;
}

/**
 * @brief Set the default system clock time device
 */
rt_err_t rt_clock_time_set_default(rt_clock_time_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    
    _default_device = dev;
    LOG_D("Changed default clock_time device to: %s", dev->parent.parent.name);
    
    return RT_EOK;
}
