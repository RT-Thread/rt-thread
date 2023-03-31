/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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

static struct rt_device_pin _hw_pin;
static rt_ssize_t _pin_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct rt_device_pin_value *value;
    struct rt_device_pin *pin = (struct rt_device_pin *)dev;

    /* check parameters */
    RT_ASSERT(pin != RT_NULL);

    value = (struct rt_device_pin_value *)buffer;
    if (value == RT_NULL || size != sizeof(*value))
        return 0;

    value->value = pin->ops->pin_read(dev, value->pin);
    return size;
}

static rt_ssize_t _pin_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct rt_device_pin_value *value;
    struct rt_device_pin *pin = (struct rt_device_pin *)dev;

    /* check parameters */
    RT_ASSERT(pin != RT_NULL);

    value = (struct rt_device_pin_value *)buffer;
    if (value == RT_NULL || size != sizeof(*value))
        return 0;

    pin->ops->pin_write(dev, (rt_base_t)value->pin, (rt_base_t)value->value);

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
    _pin_control
};
#endif

int rt_device_pin_register(const char *name, const struct rt_pin_ops *ops, void *user_data)
{
    _hw_pin.parent.type         = RT_Device_Class_Pin;
    _hw_pin.parent.rx_indicate  = RT_NULL;
    _hw_pin.parent.tx_complete  = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    _hw_pin.parent.ops          = &pin_ops;
#else
    _hw_pin.parent.init         = RT_NULL;
    _hw_pin.parent.open         = RT_NULL;
    _hw_pin.parent.close        = RT_NULL;
    _hw_pin.parent.read         = _pin_read;
    _hw_pin.parent.write        = _pin_write;
    _hw_pin.parent.control      = _pin_control;
#endif

    _hw_pin.ops                 = ops;
    _hw_pin.parent.user_data    = user_data;

    /* register a character device */
    rt_device_register(&_hw_pin.parent, name, RT_DEVICE_FLAG_RDWR);

    return 0;
}

rt_err_t rt_pin_attach_irq(rt_base_t pin, rt_uint8_t mode,
                           void (*hdr)(void *args), void *args)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    if (_hw_pin.ops->pin_attach_irq)
    {
        return _hw_pin.ops->pin_attach_irq(&_hw_pin.parent, pin, mode, hdr, args);
    }
    return -RT_ENOSYS;
}

rt_err_t rt_pin_detach_irq(rt_base_t pin)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    if (_hw_pin.ops->pin_detach_irq)
    {
        return _hw_pin.ops->pin_detach_irq(&_hw_pin.parent, pin);
    }
    return -RT_ENOSYS;
}

rt_err_t rt_pin_irq_enable(rt_base_t pin, rt_uint8_t enabled)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    if (_hw_pin.ops->pin_irq_enable)
    {
        return _hw_pin.ops->pin_irq_enable(&_hw_pin.parent, pin, enabled);
    }
    return -RT_ENOSYS;
}

/* RT-Thread Hardware PIN APIs */
void rt_pin_mode(rt_base_t pin, rt_uint8_t mode)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    _hw_pin.ops->pin_mode(&_hw_pin.parent, pin, mode);
}

void rt_pin_write(rt_base_t pin, rt_uint8_t value)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    _hw_pin.ops->pin_write(&_hw_pin.parent, pin, value);
}

rt_int8_t rt_pin_read(rt_base_t pin)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);
    return _hw_pin.ops->pin_read(&_hw_pin.parent, pin);
}

/* Get pin number by name, such as PA.0, P0.12 */
rt_base_t rt_pin_get(const char *name)
{
    RT_ASSERT(_hw_pin.ops != RT_NULL);

    if (name[0] != 'P' && name[0] != 'p')
    {
        return -RT_EINVAL;
    }
    if (_hw_pin.ops->pin_get == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    return _hw_pin.ops->pin_get(name);
}

#ifdef RT_USING_FINSH
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <finsh.h>
#include <msh_parse.h>

/*
 * convert function for port name
 * support PE02, PE2, PE.02, PE.2, pe02, pe2, pe.02, pe.2
 */
static rt_base_t _pin_cmd_conv(const char *name)
{
    int size = 0;
    char format_name[6] = { 0 };
    format_name[0] = toupper(name[0]);
    format_name[1] = toupper(name[1]);

    size = rt_strlen(name);
    size = (size > 5) ? 5 : size;
    size -= 2;
    if (name[2] != '.')
    {
        format_name[2] = '.';
    }
    strncat(format_name, name + 2, size);
    return rt_pin_get(format_name);
}

static void _pin_cmd_print_usage(void)
{
    rt_kprintf("pin [option]\n");
    rt_kprintf("  num: get pin number from hardware pin\n");
    rt_kprintf("    num can be PE02, PE2, PE.02, PE.2, pe02, pe2, pe.02, pe.2\n");
    rt_kprintf("    e.g. MSH >pin num PA.16\n");
    rt_kprintf("  mode: set pin mode to output/input/input_pullup/input_pulldown/output_od\n    e.g. MSH >pin mode PA.16 output\n");
    rt_kprintf("  read: read pin level of hardware pin\n    e.g. MSH >pin read PA.16\n");
    rt_kprintf("  write: write pin level(high/low or on/off) to hardware pin\n    e.g. MSH >pin write PA.16 high\n");
    rt_kprintf("  help: this help list\n");
}

/* e.g. MSH >pin num PA.16 */
static void _pin_cmd_get(int argc, char *argv[])
{
    rt_base_t pin;
    if (argc < 3)
    {
        _pin_cmd_print_usage();
        return;
    }
    pin = _pin_cmd_conv(argv[2]);
    if (pin < 0)
    {
        rt_kprintf("Parameter invalid : %s!\n", argv[2]);
        _pin_cmd_print_usage();
        return ;
    }
    rt_kprintf("%s : %d\n", argv[2], pin);
}

/* e.g. MSH >pin mode PA.16 output */
static void _pin_cmd_mode(int argc, char *argv[])
{
    rt_base_t pin;
    rt_base_t mode;
    if (argc < 4)
    {
        _pin_cmd_print_usage();
        return;
    }
    if (!msh_isint(argv[2]))
    {
        pin = _pin_cmd_conv(argv[2]);
        if (pin < 0)
        {
            rt_kprintf("Parameter invalid : %s!\n", argv[2]);
            _pin_cmd_print_usage();
            return;
        }
    }
    else
    {
        pin = atoi(argv[2]);
    }
    if (0 == rt_strcmp("output", argv[3]))
    {
        mode = PIN_MODE_OUTPUT;
    }
    else if (0 == rt_strcmp("input", argv[3]))
    {
        mode = PIN_MODE_INPUT;
    }
    else if (0 == rt_strcmp("input_pullup", argv[3]))
    {
        mode = PIN_MODE_INPUT_PULLUP;
    }
    else if (0 == rt_strcmp("input_pulldown", argv[3]))
    {
        mode = PIN_MODE_INPUT_PULLDOWN;
    }
    else if (0 == rt_strcmp("output_od", argv[3]))
    {
        mode = PIN_MODE_OUTPUT_OD;
    }
    else
    {
        _pin_cmd_print_usage();
        return;
    }

    rt_pin_mode(pin, mode);
}

/* e.g. MSH >pin read PA.16 */
static void _pin_cmd_read(int argc, char *argv[])
{
    rt_base_t pin;
    rt_uint8_t value;
    if (argc < 3)
    {
        _pin_cmd_print_usage();
        return;
    }
    if (!msh_isint(argv[2]))
    {
        pin = _pin_cmd_conv(argv[2]);
        if (pin < 0)
        {
            rt_kprintf("Parameter invalid : %s!\n", argv[2]);
            _pin_cmd_print_usage();
            return;
        }
    }
    else
    {
        pin = atoi(argv[2]);
    }
    value = rt_pin_read(pin);
    if (value == PIN_HIGH)
    {
        rt_kprintf("pin[%d] = on\n", pin);
    }
    else
    {
        rt_kprintf("pin[%d] = off\n", pin);
    }
}

/* e.g. MSH >pin write PA.16 high */
static void _pin_cmd_write(int argc, char *argv[])
{
    rt_base_t pin;
    rt_uint8_t value;
    if (argc < 4)
    {
        _pin_cmd_print_usage();
        return;
    }
    if (!msh_isint(argv[2]))
    {
        pin = _pin_cmd_conv(argv[2]);
        if (pin < 0)
        {
            rt_kprintf("Parameter invalid : %s!\n", argv[2]);
            _pin_cmd_print_usage();
            return;
        }
    }
    else
    {
        pin = atoi(argv[2]);
    }
    if ((0 == rt_strcmp("high", argv[3])) || (0 == rt_strcmp("on", argv[3])))
    {
        value = PIN_HIGH;
    }
    else if ((0 == rt_strcmp("low", argv[3])) || (0 == rt_strcmp("off", argv[3])))
    {
        value = PIN_LOW;
    }
    else
    {
        _pin_cmd_print_usage();
        return;
    }
    rt_pin_write(pin, value);
}

static void _pin_cmd(int argc, char *argv[])
{
    if (argc < 3)
    {
        _pin_cmd_print_usage();
        return ;
    }
    if (0 == rt_strcmp("num", argv[1]))
    {
        _pin_cmd_get(argc, argv);
    }
    else if (0 == rt_strcmp("mode", argv[1]))
    {
        _pin_cmd_mode(argc, argv);
    }
    else if (0 == rt_strcmp("read", argv[1]))
    {
        _pin_cmd_read(argc, argv);
    }
    else if (0 == rt_strcmp("write", argv[1]))
    {
        _pin_cmd_write(argc, argv);
    }
    else
    {
        _pin_cmd_print_usage();
        return;
    }
}
MSH_CMD_EXPORT_ALIAS(_pin_cmd, pin, pin [option]);
#endif /* RT_USING_FINSH */
