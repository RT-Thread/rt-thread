/*
 * File      : drv_gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */
#include <rtthread.h>
#include <rthw.h>

#include "drv_gpio.h"
#include "interrupt.h"

#define DBG_TAG  "GPIO"
#define DBG_LVL  DBG_WARNING
#include <rtdbg.h>

#define readl(addr)           (*(volatile unsigned int *)(addr))
#define writel(value,addr)    (*(volatile unsigned int *)(addr) = (value))

// Todo: add RT_ASSERT.

/*********************************************************
**   IO
*********************************************************/
int gpio_set_func(enum gpio_port port, enum gpio_pin pin, rt_uint8_t func)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    if (func & 0x8)
    {
        LOG_W("[line]:%d There is a warning with parameter input", __LINE__);
        return RT_EINVAL;
    }

    addr = GPIOn_CFG_ADDR(port) + (pin / 8) * 4;
    offset = (pin % 8) * 4;

    data = readl(addr);
    data &= ~(0x7 << offset);
    data |= func << offset;
    writel(data, addr);

    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return RT_EOK;
}

int gpio_set_value(enum gpio_port port, enum gpio_pin pin, rt_uint8_t value)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    if (value & 0xE)
    {
        LOG_W("[line]:%d There is a warning with parameter input", __LINE__);
        return RT_EINVAL;
    }

    addr = GPIOn_DATA_ADDR(port);
    offset = pin;

    data = readl(addr);
    data &= ~(0x1 << offset);
    data |= value << offset;
    writel(data, addr);

    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return RT_EOK;
}

int gpio_get_value(enum gpio_port port, enum gpio_pin pin)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    addr = GPIOn_DATA_ADDR(port);
    offset = pin;

    data = readl(addr);

    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return (data >> offset) & 0x01;
}

int gpio_set_pull_mode(enum gpio_port port,  enum gpio_pin pin, enum gpio_pull pull)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    if (pull & 0xC)
    {
        LOG_W("[line]:%d There is a warning with parameter input", __LINE__);
        return RT_EINVAL;
    }

    addr = GPIOn_PUL_ADDR(port);
    addr += pin > GPIO_PIN_15 ? 0x4 : 0x0;
    offset = (pin & 0xf) << 1;

    data = readl(addr);
    data &= ~(0x3 << offset);
    data |= pull << offset;
    writel(data, addr);

    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return RT_EOK;
}

int gpio_set_drive_level(enum gpio_port port, enum gpio_pin pin, enum gpio_drv_level level)
{
    volatile rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    if (level & 0xC)
    {
        LOG_W("[line]:%d There is a warning with parameter input", __LINE__);
        return RT_EINVAL;
    }

    addr = GPIOn_DRV_ADDR(port);
    addr += pin > GPIO_PIN_15 ? 0x4 : 0x0;
    offset = (pin & 0xf) << 1;

    data = readl(addr);
    data &= ~(0x3 << offset);
    data |= level << offset;
    writel(data, addr);

    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
    return RT_EOK;
}

void gpio_direction_input(enum gpio_port port,  enum gpio_pin pin)
{
    volatile rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    addr = GPIOn_CFG_ADDR(port) + (pin / 8) * 4;
    offset = (pin % 8) * 4;

    data = readl(addr);
    data &= ~(0x7 << offset);
    data |= IO_INPUT << offset;
    writel(data, addr);

    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}

void gpio_direction_output(enum gpio_port port, enum gpio_pin pin, int value)
{
    volatile rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_A <= port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    gpio_set_value(port, pin, value);
    addr = GPIOn_CFG_ADDR(port) + (pin / 8) * 4;
    offset = (pin % 8) * 4;

    data = readl(addr);
    data &= ~(0x7 << offset);
    data |= IO_OUTPUT << offset;
    writel(data, addr);

    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}
/*********************************************************
**   IRQ
*********************************************************/
static void gpio_ack_irq(enum gpio_port port,  enum gpio_pin pin)
{
    rt_uint32_t addr;
    rt_uint32_t data;

    addr = GPIOn_INT_STA_ADDR(port);
    data = readl(addr);
    data |= 0x1 << pin;
    writel(data, addr);
}

void gpio_select_irq_clock(enum gpio_port port, enum gpio_irq_clock clock)
{
    rt_uint32_t addr;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));

    addr = GPIOn_INT_DEB_ADDR(port - GPIO_PORT_D);

    data = readl(addr);
    data &= ~0x01;
    data |= clock;
    writel(data, addr);
    LOG_D("[line]:%d addr:%08x data:%08x", __LINE__, addr, *((rt_uint32_t *)addr));
}

void gpio_set_debounce(enum gpio_port port, enum gpio_direction_type prescaler)
{
    rt_uint32_t addr;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));

    addr = GPIOn_INT_DEB_ADDR(port - GPIO_PORT_D);

    data = readl(addr);
    data &= ~(0x07 << 4);
    data |= prescaler << 4;
    writel(data, addr);
    LOG_D("[line]:%d addr:%08x data:%08x", __LINE__, addr, *((rt_uint32_t *)addr));
}

void gpio_irq_enable(enum gpio_port port,  enum gpio_pin pin)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    addr = GPIOn_INT_CTRL_ADDR(port - GPIO_PORT_D);
    offset = pin;

    data = readl(addr);
    data |= 0x1 << offset;
    writel(data, addr);
    gpio_select_irq_clock(port, GPIO_IRQ_HOSC_24MHZ);
    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}

void gpio_irq_disable(enum gpio_port port,  enum gpio_pin pin)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    gpio_ack_irq(port - GPIO_PORT_D, pin);
    addr = GPIOn_INT_CTRL_ADDR(port - GPIO_PORT_D);
    offset = pin;

    data = readl(addr);
    data &= ~(0x1 << offset);

    writel(data, addr);
    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}

void gpio_set_irq_type(enum gpio_port port,  enum gpio_pin pin, enum gpio_irq_type irq_type)
{
    rt_uint32_t addr;
    rt_uint32_t offset;
    rt_uint32_t data;

    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    addr = GPIOn_INT_CFG_ADDR(port - GPIO_PORT_D) + (pin / 8) * 4;
    offset = (pin % 8) * 4;

    data = readl(addr);
    data &= ~(0x7 << offset);
    data |= irq_type << offset;
    writel(data, addr);

    LOG_D("[line]:%d offset:%d addr:%08x data:%08x", __LINE__, offset, addr, *((rt_uint32_t *)addr));
}

static struct gpio_irq_def _g_gpio_irq_tbl[GPIO_PORT_NUM];

void gpio_set_irq_callback(enum gpio_port port, enum gpio_pin pin, void (*irq_cb)(void *), void *irq_arg)
{
    RT_ASSERT((GPIO_PORT_C < port) && (port < GPIO_PORT_NUM));
    RT_ASSERT((GPIO_PIN_0 <= pin) && (pin < GPIO_PIN_NUM));

    _g_gpio_irq_tbl[port].irq_cb[pin]    = irq_cb;
    _g_gpio_irq_tbl[port].irq_arg[pin]   = irq_arg;
}

void gpio_clear_irq_callback(enum gpio_port port, enum gpio_pin pin)
{
    gpio_irq_disable(port, pin);

    _g_gpio_irq_tbl[port].irq_cb[pin]    = RT_NULL;
    _g_gpio_irq_tbl[port].irq_arg[pin]   = RT_NULL;
}

static void gpio_irq_handler(int irq, void *param)
{
    struct gpio_irq_def *irq_def = (struct gpio_irq_def *)param;
    rt_uint32_t pend, enable;
    int port, pin;
    rt_uint32_t addr;

    pin = 0;
    port = irq - PIOD_INTERRUPT;
    addr = GPIOn_INT_STA_ADDR(port);
    pend = readl(addr);
    addr = GPIOn_INT_CTRL_ADDR(port);
    enable = readl(addr);
    pend &= enable;

    while (pend)
    {
        if ((pend & 0x1) && (irq_def->irq_cb[pin] != RT_NULL))
        {
            LOG_D("do irq callback...", port, pin);
            irq_def->irq_cb[pin](irq_def->irq_arg[pin]);
        }
        pin++;
        pend = pend >> 1;
        gpio_ack_irq(port, pin);
    }
}


#ifdef RT_USING_PIN
#include <rtdevice.h>

#define PIN_MAGIC    (0x5A)
#define PIN_NUM(_N)      (sizeof(_N) / sizeof(_N[0]))

struct _pin_index
{
    rt_uint8_t id;
    rt_uint8_t pin_port;
    rt_uint8_t pin;
    rt_uint8_t magic;
};

static struct _pin_index pin_index[] =
{
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {2, 0, 0, 0},
    {3, 0, 0, 0},
    {4, 0, 0, 0},
    {5, 0, 0, 0},
    {6, GPIO_PORT_D, GPIO_PIN_0,  PIN_MAGIC},
    {7, GPIO_PORT_D, GPIO_PIN_1,  PIN_MAGIC},
    {8, GPIO_PORT_D, GPIO_PIN_2,  PIN_MAGIC},
    {9, GPIO_PORT_D, GPIO_PIN_3,  PIN_MAGIC},
    {10, GPIO_PORT_D, GPIO_PIN_4,  PIN_MAGIC},
    {11, GPIO_PORT_D, GPIO_PIN_5,  PIN_MAGIC},
    {12, GPIO_PORT_D, GPIO_PIN_6,  PIN_MAGIC},
    {13, GPIO_PORT_D, GPIO_PIN_7,  PIN_MAGIC},
    {14, GPIO_PORT_D, GPIO_PIN_8,  PIN_MAGIC},
    {15, GPIO_PORT_D, GPIO_PIN_9,  PIN_MAGIC},
    {16, GPIO_PORT_D, GPIO_PIN_10, PIN_MAGIC},
    {17, GPIO_PORT_D, GPIO_PIN_11, PIN_MAGIC},
    {18, GPIO_PORT_D, GPIO_PIN_12, PIN_MAGIC},
    {19, GPIO_PORT_D, GPIO_PIN_13, PIN_MAGIC},
    {20, 0, 0, 0},
    {21, GPIO_PORT_D, GPIO_PIN_14, PIN_MAGIC},
    {22, 0, 0, 0},
    {23, GPIO_PORT_D, GPIO_PIN_15, PIN_MAGIC},
    {24, GPIO_PORT_D, GPIO_PIN_16, PIN_MAGIC},
    {25, GPIO_PORT_D, GPIO_PIN_17, PIN_MAGIC},
    {26, GPIO_PORT_D, GPIO_PIN_18, PIN_MAGIC},
    {27, GPIO_PORT_D, GPIO_PIN_19, PIN_MAGIC},
    {28, GPIO_PORT_D, GPIO_PIN_20, PIN_MAGIC},
    {29, GPIO_PORT_D, GPIO_PIN_21, PIN_MAGIC},
    {30, 0, 0, 0},
    {31, 0, 0, 0},
    {32, 0, 0, 0},
    {33, 0, 0, 0},
    {34, 0, 0, 0},
    {35, 0, 0, 0},
    {36, 0, 0, 0},
    {37, GPIO_PORT_E, GPIO_PIN_12, PIN_MAGIC},
    {38, GPIO_PORT_E, GPIO_PIN_11, PIN_MAGIC},
    {39, GPIO_PORT_E, GPIO_PIN_10, PIN_MAGIC},
    {40, GPIO_PORT_E, GPIO_PIN_9,  PIN_MAGIC},
    {41, GPIO_PORT_E, GPIO_PIN_8,  PIN_MAGIC},
    {42, GPIO_PORT_E, GPIO_PIN_7,  PIN_MAGIC},
    {43, GPIO_PORT_E, GPIO_PIN_6,  PIN_MAGIC},
    {44, GPIO_PORT_E, GPIO_PIN_5,  PIN_MAGIC},
    {45, GPIO_PORT_E, GPIO_PIN_4,  PIN_MAGIC},
    {46, GPIO_PORT_E, GPIO_PIN_3,  PIN_MAGIC},
    {47, GPIO_PORT_E, GPIO_PIN_2,  PIN_MAGIC},
    {48, GPIO_PORT_E, GPIO_PIN_1,  PIN_MAGIC},
    {49, GPIO_PORT_E, GPIO_PIN_0,  PIN_MAGIC},
    {50, 0, 0, 0},
    {51, 0, 0, 0},
    {52, 0, 0, 0},
    {53, GPIO_PORT_F, GPIO_PIN_5, PIN_MAGIC},
    {54, GPIO_PORT_F, GPIO_PIN_4, PIN_MAGIC},
    {55, GPIO_PORT_F, GPIO_PIN_3, PIN_MAGIC},
    {56, GPIO_PORT_F, GPIO_PIN_2, PIN_MAGIC},
    {57, GPIO_PORT_F, GPIO_PIN_1, PIN_MAGIC},
    {58, GPIO_PORT_F, GPIO_PIN_0, PIN_MAGIC},
    {59, GPIO_PORT_C, GPIO_PIN_0, PIN_MAGIC},
    {60, GPIO_PORT_C, GPIO_PIN_1, PIN_MAGIC},
    {61, GPIO_PORT_C, GPIO_PIN_2, PIN_MAGIC},
    {62, GPIO_PORT_C, GPIO_PIN_3, PIN_MAGIC},
    {63, GPIO_PORT_A, GPIO_PIN_3, PIN_MAGIC},
    {64, GPIO_PORT_A, GPIO_PIN_2, PIN_MAGIC},
    {65, GPIO_PORT_A, GPIO_PIN_1, PIN_MAGIC},
    {66, GPIO_PORT_A, GPIO_PIN_0, PIN_MAGIC},
};

static void pin_mode(struct rt_device *dev, rt_base_t pin, rt_base_t mode)
{
    if ((pin > PIN_NUM(pin_index)) || (pin_index[pin].magic != PIN_MAGIC))
    {
        LOG_E("pin:%d value wrongful", pin);
        return;
    }

    gpio_set_func(pin_index[pin].pin_port, pin_index[pin].pin, mode);
}

static void pin_write(struct rt_device *dev, rt_base_t pin, rt_base_t value)
{
    if ((pin > PIN_NUM(pin_index)) || (pin_index[pin].magic != PIN_MAGIC))
    {
        LOG_E("pin:%d value wrongful", pin);
        return;
    }

    gpio_set_value(pin_index[pin].pin_port, pin_index[pin].pin, value);
}

static int pin_read(struct rt_device *device, rt_base_t pin)
{
    if ((pin > PIN_NUM(pin_index)) || (pin_index[pin].magic != PIN_MAGIC))
    {
        LOG_E("pin:%d value wrongful", pin);
        return 0;
    }

    return gpio_get_value(pin_index[pin].pin_port, pin_index[pin].pin);
}

static rt_err_t pin_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    if ((pin > PIN_NUM(pin_index)) || (pin_index[pin].magic != PIN_MAGIC))
    {
        LOG_E("pin:%d value wrongful", pin);
        return RT_ERROR;
    }

    gpio_set_irq_callback(pin_index[pin].pin_port, pin_index[pin].pin, hdr, args);
    gpio_set_irq_type(pin_index[pin].pin_port, pin_index[pin].pin, mode);
    return RT_EOK;
}
static rt_err_t pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    if ((pin > PIN_NUM(pin_index)) || (pin_index[pin].magic != PIN_MAGIC))
    {
        LOG_E("pin:%d value wrongful", pin);
        return RT_ERROR;
    }

    gpio_clear_irq_callback(pin_index[pin].pin_port, pin_index[pin].pin);

    return RT_EOK;
}

rt_err_t pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    if ((pin > PIN_NUM(pin_index)) || (pin_index[pin].magic != PIN_MAGIC))
    {
        LOG_E("pin:%d value wrongful", pin);
        return RT_ERROR;
    }

    if (enabled)
        gpio_irq_enable(pin_index[pin].pin_port, pin_index[pin].pin);
    else
        gpio_irq_disable(pin_index[pin].pin_port, pin_index[pin].pin);

    return RT_EOK;
}

/*
ID GPIO   ID GPIO    ID GPIO    ID GPIO    ID GPIO   ID GPIO   ID GPIO
6  PD0    13 PD7     21 PD14    29 PD21    43 PE6    53 PF5    60 PC1
7  PD1    14 PD8     23 PD15    37 PE12    44 PE5    54 PF4    61 PC2
8  PD2    15 PD9     24 PD16    38 PE11    45 PE4    55 PF3    62 PC3
9  PD3    16 PD10    25 PD17    39 PE10    46 PE3    56 PF2    63 PA3
10 PD4    17 PD11    26 PD18    40 PE9     47 PE2    57 PF1    64 PA2
11 PD5    18 PD12    27 PD19    41 PE8     48 PE1    58 PF0    65 PA1
12 PD6    19 PD13    28 PD20    42 PE7     49 PE0    59 PC0    66 PA0
*/

static const struct rt_pin_ops ops =
{
    pin_mode,
    pin_write,
    pin_read,
    pin_attach_irq,
    pin_detach_irq,
    pin_irq_enable,
    RT_NULL,
};
#endif

int rt_hw_gpio_init(void)
{
#ifdef RT_USING_PIN
    rt_device_pin_register("gpio", &ops, RT_NULL);
#endif
    /* install ISR */
    rt_hw_interrupt_install(PIOD_INTERRUPT, gpio_irq_handler, &_g_gpio_irq_tbl[GPIO_PORT_D], "gpiod_irq");
    rt_hw_interrupt_umask(PIOD_INTERRUPT);

    rt_hw_interrupt_install(PIOE_INTERRUPT, gpio_irq_handler, &_g_gpio_irq_tbl[GPIO_PORT_E], "gpioe_irq");
    rt_hw_interrupt_umask(PIOE_INTERRUPT);

    rt_hw_interrupt_install(PIOF_INTERRUPT, gpio_irq_handler, &_g_gpio_irq_tbl[GPIO_PORT_F], "gpiof_irq");
    rt_hw_interrupt_umask(PIOF_INTERRUPT);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_gpio_init);
