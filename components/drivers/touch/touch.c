/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-20     tyustli      the first version
 */

#include "touch.h"
#include <string.h>

#define DBG_TAG  "touch"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* ISR for touch interrupt */
void rt_hw_touch_isr(rt_touch_t touch)
{
    RT_ASSERT(touch);
    if (touch->parent.rx_indicate == RT_NULL)
    {
        return;
    }

    if (touch->irq_handle != RT_NULL)
    {
        touch->irq_handle(touch);
    }

    touch->parent.rx_indicate(&touch->parent, 1);
}

#ifdef RT_TOUCH_PIN_IRQ
static void touch_irq_callback(void *param)
{
    rt_hw_touch_isr((rt_touch_t)param);
}
#endif

/* touch interrupt initialization function */
static rt_err_t rt_touch_irq_init(rt_touch_t touch)
{
#ifdef RT_TOUCH_PIN_IRQ
    if (touch->config.irq_pin.pin == RT_PIN_NONE)
    {
        return -RT_EINVAL;
    }

    rt_pin_mode(touch->config.irq_pin.pin, touch->config.irq_pin.mode);

    if (touch->config.irq_pin.mode == PIN_MODE_INPUT_PULLDOWN)
    {
        rt_pin_attach_irq(touch->config.irq_pin.pin, PIN_IRQ_MODE_RISING, touch_irq_callback, (void *)touch);
    }
    else if (touch->config.irq_pin.mode == PIN_MODE_INPUT_PULLUP)
    {
        rt_pin_attach_irq(touch->config.irq_pin.pin, PIN_IRQ_MODE_FALLING, touch_irq_callback, (void *)touch);
    }
    else if (touch->config.irq_pin.mode == PIN_MODE_INPUT)
    {
        rt_pin_attach_irq(touch->config.irq_pin.pin, PIN_IRQ_MODE_RISING_FALLING, touch_irq_callback, (void *)touch);
    }

    rt_pin_irq_enable(touch->config.irq_pin.pin, PIN_IRQ_ENABLE);
#endif

    return RT_EOK;
}

/* touch interrupt enable */
static void rt_touch_irq_enable(rt_touch_t touch)
{
#ifdef RT_TOUCH_PIN_IRQ
    if (touch->config.irq_pin.pin != RT_PIN_NONE)
    {
        rt_pin_irq_enable(touch->config.irq_pin.pin, RT_TRUE);
    }
#endif
}

/* touch interrupt disable */
static void rt_touch_irq_disable(rt_touch_t touch)
{
#ifdef RT_TOUCH_PIN_IRQ
    if (touch->config.irq_pin.pin != RT_PIN_NONE)
    {
        rt_pin_irq_enable(touch->config.irq_pin.pin, RT_FALSE);
    }
#endif
}

static rt_err_t rt_touch_open(rt_device_t dev, rt_uint16_t oflag)
{
    rt_touch_t touch;
    RT_ASSERT(dev != RT_NULL);
    touch = (rt_touch_t)dev;

    if (oflag & RT_DEVICE_FLAG_INT_RX && dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Initialization touch interrupt */
        rt_touch_irq_init(touch);
    }

    return RT_EOK;
}

static rt_err_t rt_touch_close(rt_device_t dev)
{
    rt_touch_t touch;
    RT_ASSERT(dev != RT_NULL);
    touch = (rt_touch_t)dev;

    /* touch disable interrupt */
    rt_touch_irq_disable(touch);

    return RT_EOK;
}

static rt_size_t rt_touch_read(rt_device_t dev, rt_off_t pos, void *buf, rt_size_t len)
{
    rt_touch_t touch;
    rt_size_t result = 0;
    RT_ASSERT(dev != RT_NULL);
    touch = (rt_touch_t)dev;

    if (buf == NULL || len == 0)
    {
        return 0;
    }

    result = touch->ops->touch_readpoint(touch, buf, len);

    return result;
}

static rt_err_t rt_touch_control(rt_device_t dev, int cmd, void *args)
{
    rt_touch_t touch;
    rt_err_t result = RT_EOK;
    RT_ASSERT(dev != RT_NULL);
    touch = (rt_touch_t)dev;

    switch (cmd)
    {
    case RT_TOUCH_CTRL_GET_ID:
        if (args)
        {
            result = touch->ops->touch_control(touch, RT_TOUCH_CTRL_GET_ID, args);
        }
        else
        {
            result = -RT_ERROR;
        }

        break;
    case RT_TOUCH_CTRL_GET_INFO:
        if (args)
        {
            result = touch->ops->touch_control(touch, RT_TOUCH_CTRL_GET_INFO, args);
        }
        else
        {
            result = -RT_ERROR;
        }

        break;
    case RT_TOUCH_CTRL_SET_MODE:
        result = touch->ops->touch_control(touch, RT_TOUCH_CTRL_SET_MODE, args);

        if (result == RT_EOK)
        {
            rt_uint16_t mode;
            mode  = *(rt_uint16_t*)args;
            if (mode == RT_DEVICE_FLAG_INT_RX)
            {
                rt_touch_irq_enable(touch);  /* enable interrupt */
            }
        }

        break;
    case RT_TOUCH_CTRL_SET_X_RANGE:
        result = touch->ops->touch_control(touch, RT_TOUCH_CTRL_SET_X_RANGE, args);

        if (result == RT_EOK)
        {
            touch->info.range_x = *(rt_int32_t *)args;
            LOG_D("set x coordinate range :%d\n", touch->info.range_x);
        }

        break;
    case RT_TOUCH_CTRL_SET_Y_RANGE:
        result = touch->ops->touch_control(touch, RT_TOUCH_CTRL_SET_Y_RANGE, args);

        if (result == RT_EOK)
        {
            touch->info.range_y = *(rt_uint32_t *)args;
            LOG_D("set y coordinate range :%d \n", touch->info.range_x);
        }

        break;
    case RT_TOUCH_CTRL_DISABLE_INT:
        rt_touch_irq_disable(touch);
        break;
    case RT_TOUCH_CTRL_ENABLE_INT:
        rt_touch_irq_enable(touch);
        break;
    default:
        return -RT_ERROR;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rt_touch_ops =
{
    RT_NULL,
    rt_touch_open,
    rt_touch_close,
    rt_touch_read,
    RT_NULL,
    rt_touch_control
};
#endif

/*
 * touch register
 */
int rt_hw_touch_register(rt_touch_t touch,
                         const char              *name,
                         rt_uint32_t              flag,
                         void                    *data)
{
    rt_int8_t result;
    rt_device_t device;
    RT_ASSERT(touch != RT_NULL);

    device = &touch->parent;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rt_touch_ops;
#else
    device->init        = RT_NULL;
    device->open        = rt_touch_open;
    device->close       = rt_touch_close;
    device->read        = rt_touch_read;
    device->write       = RT_NULL;
    device->control     = rt_touch_control;
#endif
    device->type        = RT_Device_Class_Touch;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = data;

    result = rt_device_register(device, name, flag | RT_DEVICE_FLAG_STANDALONE);

    if (result != RT_EOK)
    {
        LOG_E("rt_touch register err code: %d", result);
        return result;
    }

    LOG_I("rt_touch init success");

    return RT_EOK;
}
