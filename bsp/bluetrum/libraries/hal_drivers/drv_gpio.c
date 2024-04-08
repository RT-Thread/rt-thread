/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-19     greedyhao         first version
 */

#include "drv_gpio.h"

#ifdef RT_USING_PIN

// #define DRV_DEBUG
#define LOG_TAG             "drv.gpio"
#include <drv_log.h>

struct port_info
{
    rt_uint8_t start_pin;
    rt_uint8_t delta_pin;
    rt_uint8_t total_pin;
};

/* It needs to be adjusted to the hardware. */
static const struct port_info port_table[] =
{
    {0, 8, 0},      /* PA0-PA7 */
    {0, 5, 8},      /* PB0-PB4 */
    {0, 8, 13},     /* PE0-PE7 */
    {0, 6, 21},     /* PF0-PF5 */
};

static const hal_sfr_t port_sfr[] =
{
    GPIOA_BASE,
    GPIOB_BASE,
    GPIOE_BASE,
    GPIOF_BASE,
};

static rt_uint8_t _pin_port(rt_uint32_t pin)
{
    rt_uint8_t port = 0;
    for (port = 0; port < 3; port++) {
        if (pin < (port_table[port].total_pin + port_table[port].delta_pin)) {
            break;
        }
    }
    return port;
}

#define PIN_NUM(port, no)       ((rt_uint8_t)(port_table[port].total_pin + no - port_table[port].start_pin))
#define PIN_PORT(pin)           _pin_port(pin)
#define PORT_SFR(port)          (port_sfr[(port)])
#define PIN_NO(pin)             (rt_uint8_t)((pin) & 0xFu)

static rt_base_t ab32_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 4) || (name_len >= 6))
    {
        return -RT_EINVAL;
    }
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        return -RT_EINVAL;
    }

    if ((name[1] >= 'A') && (name[1] <= 'B'))
    {
        hw_port_num = (int)(name[1] - 'A');
    }
    else if ((name[1] >= 'E') && (name[1] <= 'G'))
    {
        hw_port_num = (int)(name[1] - 'A') - 2;  /* Without 'C' and 'D'. */
    }
    else
    {
        return -RT_EINVAL;
    }

    for (i = 3; i < name_len; i++)
    {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    pin = PIN_NUM(hw_port_num, hw_pin_num);
    LOG_D("name=%s", name);
    LOG_D("hw_port_num=%d hw_pin_num=%d pin=%d", hw_port_num, hw_pin_num, pin);

    return pin;
}

static void ab32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    rt_uint8_t port = PIN_PORT(pin);
    rt_uint8_t gpio_pin  = pin - port_table[port].total_pin;
    hal_gpio_write(PORT_SFR(port), gpio_pin, (rt_uint8_t)value);
}

static rt_ssize_t ab32_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_uint8_t port = PIN_PORT(pin);
    rt_uint8_t gpio_pin  = pin - port_table[port].total_pin;
    return hal_gpio_read(PORT_SFR(port), gpio_pin);
}

static void ab32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    struct gpio_init gpio_init;
    rt_uint8_t port = PIN_PORT(pin);

    gpio_init.pin = BIT(pin - port_table[port].total_pin);
    gpio_init.de  = GPIO_DIGITAL;
    gpio_init.af_con = GPIO_AFDIS;
    LOG_D("port=%d pin=%d", port, gpio_init.pin);

    switch (mode)
    {
    case PIN_MODE_INPUT:
        gpio_init.pull = GPIO_NOPULL;
        gpio_init.dir = GPIO_DIR_INPUT;
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_init.pull = GPIO_PULLUP;
        gpio_init.dir = GPIO_DIR_INPUT;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio_init.pull = GPIO_PULLDOWN;
        gpio_init.dir = GPIO_DIR_INPUT;
        break;
    case PIN_MODE_OUTPUT:
    case PIN_MODE_OUTPUT_OD:
    default:
        gpio_init.pull = GPIO_NOPULL;
        gpio_init.dir = GPIO_DIR_OUTPUT;
        break;
    }
    hal_gpio_init(PORT_SFR(port), &gpio_init);
}

static rt_err_t ab32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    return -RT_ERROR;
}

static rt_err_t ab32_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    return -RT_ERROR;
}

static rt_err_t ab32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    return -RT_ERROR;
}

const static struct rt_pin_ops _ab32_pin_ops =
{
    ab32_pin_mode,
    ab32_pin_write,
    ab32_pin_read,
    ab32_pin_attach_irq,
    ab32_pin_dettach_irq,
    ab32_pin_irq_enable,
    ab32_pin_get,
};

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &_ab32_pin_ops, RT_NULL);
}

#endif
