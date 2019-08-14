/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-13     balanceTWK   the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

static rt_err_t rt_capture_init(struct rt_device *dev)
{
    rt_err_t ret;
    struct rt_capture_device *capture;

    RT_ASSERT(dev != RT_NULL);

    ret = RT_EOK;
    capture = (struct rt_capture_device *)dev;
    capture->watermark = RT_CAPTURE_RB_SIZE / 2;
    if (capture->ops->init)
    {
        ret = capture->ops->init(capture);
    }

    return ret;
}

static rt_err_t rt_capture_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_err_t ret;
    struct rt_capture_device *capture;

    RT_ASSERT(dev != RT_NULL);

    ret = RT_EOK;
    capture = (struct rt_capture_device *)dev;
    if (capture->ringbuff == RT_NULL)
    {
        capture->ringbuff = rt_ringbuffer_create(sizeof(struct capture_data) * RT_CAPTURE_RB_SIZE);
    }
    if (capture->ops->open)
    {
        ret = capture->ops->open(capture);
    }

    return ret;
}

static rt_err_t rt_capture_close(struct rt_device *dev)
{
    rt_err_t ret;
    struct rt_capture_device *capture;

    RT_ASSERT(dev != RT_NULL);

    ret = -RT_ERROR;
    capture = (struct rt_capture_device *)dev;

    if (capture->ops->close)
    {
        ret = capture->ops->close(capture);
    }

    if (ret != RT_EOK)
    {
        return ret;
    }

    if (capture->ringbuff)
    {
        rt_ringbuffer_destroy(capture->ringbuff);
        capture->ringbuff = RT_NULL;
    }
    return ret;
}

static rt_size_t rt_capture_read(struct rt_device *dev,
                                 rt_off_t          pos,
                                 void             *buffer,
                                 rt_size_t         size)
{
    rt_size_t receive_size;
    struct rt_capture_device *capture;

    RT_ASSERT(dev != RT_NULL);

    capture = (struct rt_capture_device *)dev;
    receive_size = rt_ringbuffer_get(capture->ringbuff, (rt_uint8_t *)buffer, sizeof(struct capture_data) * size);

    return receive_size / sizeof(struct capture_data);
}

static rt_err_t rt_capture_control(struct rt_device *dev, int cmd, void *args)
{
    rt_err_t result;
    struct rt_capture_device *capture;

    RT_ASSERT(dev != RT_NULL);

    result = RT_EOK;
    capture = (struct rt_capture_device *)dev;
    switch (cmd)
    {
    case CAPTURE_CMD_CLEAR_BUF:
        if (capture->ringbuff)
        {
            rt_ringbuffer_reset(capture->ringbuff);
        }
        break;
    case CAPTURE_CMD_SET_WATERMARK:
        capture->watermark = *(rt_size_t *)args;
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops capture_ops =
{
    rt_capture_init,
    rt_capture_open,
    rt_capture_close,
    rt_capture_read,
    RT_NULL,
    rt_capture_control
};
#endif

rt_err_t rt_device_capture_register(struct rt_capture_device *capture, const char *name, void *user_data)
{
    struct rt_device *device;

    RT_ASSERT(capture != RT_NULL);
    RT_ASSERT(capture->ops != RT_NULL);
    RT_ASSERT(capture->ops->get_pulsewidth != RT_NULL);

    device = &(capture->parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    capture->ringbuff = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &capture_ops;
#else
    device->init        = rt_capture_init;
    device->open        = rt_capture_open;
    device->close       = rt_capture_close;
    device->read        = rt_capture_read;
    device->write       = RT_NULL;
    device->control     = rt_capture_control;
#endif
    device->user_data   = user_data;

    return rt_device_register(device, name, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_STANDALONE);
}

/**
 * This function is ISR for capture interrupt.
 * level: RT_TRUE denotes high level pulse, and RT_FALSE denotes low level pulse.
 */
void rt_hw_capture_isr(struct rt_capture_device *capture, rt_bool_t level)
{
    struct capture_data data;
    rt_size_t receive_size;
    if (capture->ops->get_pulsewidth(capture, &data.pulsewidth_us) != RT_EOK)
    {
        return;
    }

    data.is_high = level;
    if (rt_ringbuffer_put(capture->ringbuff, (rt_uint8_t *)&data, sizeof(struct capture_data)) == 0)
    {
        LOG_W("capture ringbuffer doesn't have enough space.");
    }

    receive_size =  rt_ringbuffer_data_len(capture->ringbuff) / sizeof(struct capture_data);

    if (receive_size >= capture->watermark)
    {
        /* indicate to upper layer application */
        if (capture->parent.rx_indicate != RT_NULL)
            capture->parent.rx_indicate(&capture->parent, receive_size);
    }
}
