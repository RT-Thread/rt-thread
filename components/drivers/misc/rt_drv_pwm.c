/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-07     aozima       the first version
 */

#include <string.h>

#include <drivers/rt_drv_pwm.h>

static rt_err_t _pwm_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    struct rt_device_pwm *pwm = (struct rt_device_pwm *)dev;

    if (pwm->ops->control)
    {
        result = pwm->ops->control(pwm, cmd, args);
    }

    return result;
}


/*
pos: channel
void *buffer: rt_uint32_t pulse[size]
size : number of pulse, only set to sizeof(rt_uint32_t).
*/
static rt_size_t _pwm_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    rt_err_t result = RT_EOK;
    struct rt_device_pwm *pwm = (struct rt_device_pwm *)dev;
    rt_uint32_t *pulse = (rt_uint32_t *)buffer;
    struct rt_pwm_configuration configuration = {0};

    configuration.channel = pos;

    if (pwm->ops->control)
    {
        result = pwm->ops->control(pwm, PWM_CMD_GET,  &configuration);
        if (result != RT_EOK)
        {
            return 0;
        }

        *pulse = configuration.pulse;
    }

    return size;
}

/*
pos: channel
void *buffer: rt_uint32_t pulse[size]
size : number of pulse, only set to sizeof(rt_uint32_t).
*/
static rt_size_t _pwm_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    rt_err_t result = RT_EOK;
    struct rt_device_pwm *pwm = (struct rt_device_pwm *)dev;
    rt_uint32_t *pulse = (rt_uint32_t *)buffer;
    struct rt_pwm_configuration configuration = {0};

    configuration.channel = pos;

    if (pwm->ops->control)
    {
        result = pwm->ops->control(pwm, PWM_CMD_GET, &configuration);
        if (result != RT_EOK)
        {
            return 0;
        }

        configuration.pulse = *pulse;

        result = pwm->ops->control(pwm, PWM_CMD_SET, &configuration);
        if (result != RT_EOK)
        {
            return 0;
        }
    }

    return size;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops pwm_device_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _pwm_read,
    _pwm_write,
    _pwm_control
};
#endif /* RT_USING_DEVICE_OPS */

rt_err_t rt_device_pwm_register(struct rt_device_pwm *device, const char *name, const struct rt_pwm_ops *ops, const void *user_data)
{
    rt_err_t result = RT_EOK;

    memset(device, 0, sizeof(struct rt_device_pwm));

#ifdef RT_USING_DEVICE_OPS
    device->parent.ops = &pwm_device_ops;
#else
    device->parent.init = RT_NULL;
    device->parent.open = RT_NULL;
    device->parent.close = RT_NULL;
    device->parent.read  = _pwm_read;
    device->parent.write = _pwm_write;
    device->parent.control = _pwm_control;
#endif /* RT_USING_DEVICE_OPS */

    device->parent.type         = RT_Device_Class_Miscellaneous;
    device->ops                 = ops;
    device->parent.user_data    = (void *)user_data;

    result = rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDWR);

    return result;
}

rt_err_t rt_pwm_enable(struct rt_device_pwm *device, int channel)
{
    rt_err_t result = RT_EOK;
    struct rt_pwm_configuration configuration = {0};

    if (!device)
    {
        return -RT_EIO;
    }

    configuration.channel = (channel > 0) ? (channel) : (-channel);         /* Make it is positive num forever */
    configuration.complementary = (channel > 0) ? (RT_FALSE) : (RT_TRUE);   /* If nagetive, it's complementary */
    result = rt_device_control(&device->parent, PWM_CMD_ENABLE, &configuration);

    return result;
}

rt_err_t rt_pwm_disable(struct rt_device_pwm *device, int channel)
{
    rt_err_t result = RT_EOK;
    struct rt_pwm_configuration configuration = {0};

    if (!device)
    {
        return -RT_EIO;
    }

    configuration.channel = (channel > 0) ? (channel) : (-channel);         /* Make it is positive num forever */
    configuration.complementary = (channel > 0) ? (RT_FALSE) : (RT_TRUE);   /* If nagetive, it's complementary */
    result = rt_device_control(&device->parent, PWM_CMD_DISABLE, &configuration);

    return result;
}

rt_err_t rt_pwm_set(struct rt_device_pwm *device, int channel, rt_uint32_t period, rt_uint32_t pulse)
{
    rt_err_t result = RT_EOK;
    struct rt_pwm_configuration configuration = {0};

    if (!device)
    {
        return -RT_EIO;
    }

    configuration.channel = channel;
    configuration.period = period;
    configuration.pulse = pulse;
    result = rt_device_control(&device->parent, PWM_CMD_SET, &configuration);

    return result;
}

rt_err_t rt_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *cfg)
{
    rt_err_t result = RT_EOK;

    if (!device)
    {
        return -RT_EIO;
    }

    result = rt_device_control(&device->parent, PWM_CMD_GET, cfg);

    return result;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

FINSH_FUNCTION_EXPORT_ALIAS(rt_pwm_enable, pwm_enable, enable pwm by channel.);
FINSH_FUNCTION_EXPORT_ALIAS(rt_pwm_set, pwm_set, set pwm.);

#ifdef FINSH_USING_MSH
static int pwm_enable(int argc, char **argv)
{
    int result = 0;
    struct rt_device_pwm *device = RT_NULL;

    if (argc != 3)
    {
        rt_kprintf("Usage: pwm_enable pwm1 1\n");
        rt_kprintf("       pwm_enable <pwm_dev> <channel/-channel>\n");
        result = -RT_ERROR;
        goto _exit;
    }

    device = (struct rt_device_pwm *)rt_device_find(argv[1]);
    if (!device)
    {
        result = -RT_EIO;
        goto _exit;
    }

    /* If channel is complementary(1), make the channel number to nagetive */
    result = rt_pwm_enable(device, atoi(argv[2]));

_exit:
    return result;
}
MSH_CMD_EXPORT(pwm_enable, pwm_enable <pwm_dev> <channel/-channel>);

static int pwm_disable(int argc, char **argv)
{
    int result = 0;
    struct rt_device_pwm *device = RT_NULL;

    if (argc != 3)
    {
        rt_kprintf("Usage: pwm_disable pwm1 1\n");
        rt_kprintf("       pwm_disable <pwm_dev> <channel/-channel> \n");
        result = -RT_ERROR;
        goto _exit;
    }

    device = (struct rt_device_pwm *)rt_device_find(argv[1]);
    if (!device)
    {
        result = -RT_EIO;
        goto _exit;
    }

    /* If channel is complementary(1), make the channel number to nagetive */
    result = rt_pwm_disable(device, atoi(argv[2]));

_exit:
    return result;
}
MSH_CMD_EXPORT(pwm_disable, pwm_disable <pwm_dev> <channel/-channel>);

static int pwm_set(int argc, char **argv)
{
    int result = 0;
    struct rt_device_pwm *device = RT_NULL;

    if (argc != 5)
    {
        rt_kprintf("Usage: pwm_set pwm1 1 100 50\n");
        rt_kprintf("Usage: pwm_set <pwm_dev> <channel> <period> <pulse>\n");
        result = -RT_ERROR;
        goto _exit;
    }

    device = (struct rt_device_pwm *)rt_device_find(argv[1]);
    if (!device)
    {
        result = -RT_EIO;
        goto _exit;
    }

    result = rt_pwm_set(device, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));

_exit:
    return result;
}
MSH_CMD_EXPORT(pwm_set, pwm_set <pwm_dev> <channel> <period> <pulse>);


static int pwm_get(int argc, char **argv)
{
    int result = 0;
    struct rt_device_pwm *device = RT_NULL;
    struct rt_pwm_configuration cfg = {0};

    if (argc != 3)
    {
        rt_kprintf("Usage: pwm_get pwm1 1\n");
        rt_kprintf("       pwm_get <pwm_dev> <channel>\n");
        result = -RT_ERROR;
        goto _exit;
    }

    device = (struct rt_device_pwm *)rt_device_find(argv[1]);
    if (!device)
    {
        result = -RT_EIO;
        goto _exit;
    }

    cfg.channel = atoi(argv[2]);
    result = rt_pwm_get(device, &cfg);
    if (result != RT_EOK)
    {
        rt_kprintf("Get info of device: [%s] error.\n", argv[1]);
    }
    else
    {
        rt_kprintf("Get info of device: [%s]:\n", argv[1]);
        rt_kprintf("period     : %d\n", cfg.period);
        rt_kprintf("pulse      : %d\n", cfg.pulse);
        rt_kprintf("Duty cycle : %d%%\n", (int)(((double)(cfg.pulse)/(cfg.period)) * 100));
    }

_exit:
    return result;
}
MSH_CMD_EXPORT(pwm_get, pwm_get <pwm_dev> <channel>);

#endif /* FINSH_USING_MSH */
#endif /* RT_USING_FINSH */
