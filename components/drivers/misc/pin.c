/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-20     Bernard      the first version
 * 2021-02-06     Meco Man     fix RT_ENOSYS code in negative
 * 2022-04-29     WangQiang    add pin operate command in MSH
 */

#include <drivers/pin.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

static struct rt_device_pin _hw_pin;
static rt_size_t _pin_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct rt_device_pin_status *status;
    struct rt_device_pin *pin = (struct rt_device_pin *)dev;

    /* check parameters */
    RT_ASSERT(pin != RT_NULL);

    status = (struct rt_device_pin_status *)buffer;
    if (status == RT_NULL || size != sizeof(*status))
        return 0;

    status->status = pin->ops->pin_read(dev, status->pin);
    return size;
}

static rt_size_t _pin_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct rt_device_pin_status *status;
    struct rt_device_pin *pin = (struct rt_device_pin *)dev;

    /* check parameters */
    RT_ASSERT(pin != RT_NULL);

    status = (struct rt_device_pin_status *)buffer;
    if (status == RT_NULL || size != sizeof(*status))
        return 0;

    pin->ops->pin_write(dev, (rt_base_t)status->pin, (rt_base_t)status->status);

    return size;
}

static rt_err_t _pin_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_device_pin_mode *mode;
    struct rt_device_pin *pin = (struct rt_device_pin *)dev;

    /* check parameters */
    RT_ASSERT(pin != RT_NULL);

    mode = (struct rt_device_pin_mode *)args;
    if (mode == RT_NULL)
        return -RT_ERROR;

    pin->ops->pin_mode(dev, (rt_base_t)mode->pin, (rt_base_t)mode->mode);

    return 0;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pin_ops =
    {
        RT_NULL,
        RT_NULL,
        RT_NULL,
        _pin_read,
        _pin_write,
        _pin_control};
#endif

int rt_device_pin_register(const char *name, const struct rt_pin_ops *ops, void *user_data)
{
    _hw_pin.parent.type = RT_Device_Class_Miscellaneous;
    _hw_pin.parent.rx_indicate = RT_NULL;
    _hw_pin.parent.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    _hw_pin.parent.ops = &pin_ops;
#else
    _hw_pin.parent.init = RT_NULL;
    _hw_pin.parent.open = RT_NULL;
    _hw_pin.parent.close = RT_NULL;
    _hw_pin.parent.read = _pin_read;
    _hw_pin.parent.write = _pin_write;
    _hw_pin.parent.control = _pin_control;
#endif

    _hw_pin.ops = ops;
    _hw_pin.parent.user_data = user_data;

    /* register a character device */
    rt_device_register(&_hw_pin.parent, name, RT_DEVICE_FLAG_RDWR);

    return 0;
}

rt_err_t rt_pin_attach_irq(rt_int32_t pin, rt_uint32_t mode,
                           void (*hdr)(void *args), void *args)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    if (_hw_pin.ops->pin_attach_irq)
    {
        return _hw_pin.ops->pin_attach_irq(&_hw_pin.parent, pin, mode, hdr, args);
    }
    return -RT_ENOSYS;
}

rt_err_t rt_pin_detach_irq(rt_int32_t pin)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    if (_hw_pin.ops->pin_detach_irq)
    {
        return _hw_pin.ops->pin_detach_irq(&_hw_pin.parent, pin);
    }
    return -RT_ENOSYS;
}

rt_err_t rt_pin_irq_enable(rt_base_t pin, rt_uint32_t enabled)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    if (_hw_pin.ops->pin_irq_enable)
    {
        return _hw_pin.ops->pin_irq_enable(&_hw_pin.parent, pin, enabled);
    }
    return -RT_ENOSYS;
}

/* RT-Thread Hardware PIN APIs */
void rt_pin_mode(rt_base_t pin, rt_base_t mode)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    _hw_pin.ops->pin_mode(&_hw_pin.parent, pin, mode);
}
#ifdef FINSH_USING_MSH
#define PINMODE_USAGE "\r\npinMode pin_xxx mode_xxx\r\n\tpin_xxx : 1\r\n\tmode_xxx : output or input\r\n"
static void pinMode(int argc, char *argv[])
{
    rt_base_t pin;
    rt_base_t mode;
    if (argc < 3)
    {
        rt_kprintf(PINMODE_USAGE);
        return;
    }
    if (!rt_isint(argv[1]))
    {
        rt_kprintf(PINMODE_USAGE);
        return;
    }
    pin = rt_strtoint(argv[1]);
    if (0 == rt_strcmp("output", argv[2]))
    {
        mode = PIN_MODE_OUTPUT;
    }
    else if (0 == rt_strcmp("input", argv[2]))
    {
        mode = PIN_MODE_INPUT;
    }
    else
    {
        rt_kprintf(PINMODE_USAGE);
        return;
    }

    rt_pin_mode(pin, mode);
}
MSH_CMD_EXPORT(pinMode, set hardware pin mode);
#else
FINSH_FUNCTION_EXPORT_ALIAS(rt_pin_mode, pinMode, set hardware pin mode);
#endif

void rt_pin_write(rt_base_t pin, rt_base_t value)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    _hw_pin.ops->pin_write(&_hw_pin.parent, pin, value);
}
#ifdef FINSH_USING_MSH
#define PINWRITE_USAGE "\r\npinWrite pin_xxx state_xxx\r\n\tpin_xxx : 1\r\n\tstate_xxx : high or low\r\n\tstate_xxx : on or off\r\n"
static void pinWrite(int argc, char *argv[])
{
    rt_base_t pin;
    rt_base_t value;
    if (argc < 3)
    {
        rt_kprintf(PINWRITE_USAGE);
        return;
    }
    if (!rt_isint(argv[1]))
    {
        rt_kprintf(PINWRITE_USAGE);
        return;
    }
    pin = rt_strtoint(argv[1]);
    if ((0 == rt_strcmp("high", argv[2])) || (0 == rt_strcmp("on", argv[2])))
    {
        value = PIN_HIGH;
    }
    else if ((0 == rt_strcmp("low", argv[2])) || (0 == rt_strcmp("off", argv[2])))
    {
        value = PIN_LOW;
    }
    else
    {
        rt_kprintf(PINMODE_USAGE);
        return;
    }
    rt_pin_write(pin, value);
}
MSH_CMD_EXPORT(pinWrite, write value to hardware pin);
#else
FINSH_FUNCTION_EXPORT_ALIAS(rt_pin_write, pinWrite, write value to hardware pin);
#endif

int rt_pin_read(rt_base_t pin)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    return _hw_pin.ops->pin_read(&_hw_pin.parent, pin);
}
#ifdef FINSH_USING_MSH
#define PINREAD_USAGE "\r\npinRead pin_xxx\r\n\tpin_xxx : 1\r\n"
static void pinRead(int argc, char *argv[])
{
    rt_base_t pin;
    rt_base_t value;
    if (argc < 2)
    {
        rt_kprintf(PINREAD_USAGE);
        return;
    }
    if (!rt_isint(argv[1]))
    {
        rt_kprintf(PINREAD_USAGE);
        return;
    }
    pin = rt_strtoint(argv[1]);
    value = rt_pin_read(pin);
    if (value == PIN_HIGH)
    {
        rt_kprintf("pin[%d] = on\r\n", pin);
    }
    else
    {
        rt_kprintf("pin[%d] = off\r\n", pin);
    }
}
MSH_CMD_EXPORT(pinRead, read status from hardware pin);
#else
FINSH_FUNCTION_EXPORT_ALIAS(rt_pin_read, pinRead, read status from hardware pin);
#endif

rt_base_t rt_pin_get(const char *name)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    RT_ASSERT(name[0] == 'P');

    if (_hw_pin.ops->pin_get == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    return _hw_pin.ops->pin_get(name);
}
#ifdef FINSH_USING_MSH
#define PINGET_USAGE "\r\npinGet PortString\r\n\tPortString : PA0\r\n"
static void pinGet(int argc, char *argv[])
{
    rt_base_t pin;
    if (argc < 2)
    {
        rt_kprintf(PINGET_USAGE);
        return;
    }
    pin = rt_pin_get(argv[1]);
    rt_kprintf("%s : %d\r\n", argv[1], pin);
}
MSH_CMD_EXPORT(pinGet, get pin number from hardware pin);
#else
FINSH_FUNCTION_EXPORT_ALIAS(rt_pin_get, pinGet, get pin number from hardware pin);
#endif
