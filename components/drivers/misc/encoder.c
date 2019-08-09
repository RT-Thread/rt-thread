/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-08     balanceTWK   the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

static rt_err_t rt_encoder_init(struct rt_device *dev)
{
    rt_encoder_t *encoder;

    encoder = (rt_encoder_t *)dev;
    if (encoder->ops->init)
    {
        return encoder->ops->init(encoder);
    }
    else
    {
        return -RT_ENOSYS;
    }
}

static rt_err_t rt_encoder_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_encoder_t *encoder;

    encoder = (rt_encoder_t *)dev;
    if (encoder->ops->control)
    {
        return encoder->ops->control(encoder, ENCODER_SWITCH_ON, RT_NULL);
    }
    else
    {
        return -RT_ENOSYS;
    }
}

static rt_err_t rt_encoder_close(struct rt_device *dev)
{
    rt_encoder_t *encoder;

    encoder = (rt_encoder_t *)dev;
    if (encoder->ops->control)
    {
        return encoder->ops->control(encoder, ENCODER_SWITCH_OFF, RT_NULL);
    }
    else
    {
        return -RT_ENOSYS;
    }
}

static rt_size_t rt_encoder_read(struct rt_device *dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_encoder_t *encoder;

    encoder = (rt_encoder_t *)dev;
    if (encoder->ops->get_count)
    {
        *(rt_int32_t *)buffer = encoder->ops->get_count(encoder);
    }
    return 1;
}

static rt_err_t rt_encoder_control(struct rt_device *dev, int cmd, void *args)
{
    rt_err_t result;
    rt_encoder_t *encoder;

    result = RT_EOK;
    encoder = (rt_encoder_t *)dev;
    switch (cmd)
    {
    case ENCODER_INFO_GET:
        *(struct rt_encoder_info *)args = *encoder->info;
        break;
    case ENCODER_SWITCH_ON:
    case ENCODER_SWITCH_OFF:
    case ENCODER_COUNT_CLEAR:
        result = encoder->ops->control(encoder, cmd, args);
        break;
    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops encoder_ops =
{
    rt_encoder_init,
    rt_encoder_open,
    rt_encoder_close,
    rt_encoder_read,
    RT_NULL,
    rt_encoder_control
};
#endif

rt_err_t rt_device_encoder_register(rt_encoder_t *encoder, const char *name, void *user_data)
{
    struct rt_device *device;

    RT_ASSERT(encoder != RT_NULL);
    RT_ASSERT(encoder->ops != RT_NULL);
    RT_ASSERT(encoder->info != RT_NULL);

    device = &(encoder->parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &encoder_ops;
#else
    device->init        = rt_encoder_init;
    device->open        = rt_encoder_open;
    device->close       = rt_encoder_close;
    device->read        = rt_encoder_read;
    device->write       = RT_NULL;
    device->control     = rt_encoder_control;
#endif
    device->user_data   = user_data;

    return rt_device_register(device, name, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_STANDALONE);
}
