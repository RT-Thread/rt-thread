/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/10/19     xiunian      first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "drv_ioremap.h"

#ifdef RT_USING_PIN
#include "drv_gpio.h"

#define GPIO_SWPORTA_DR     0x00
#define GPIO_SWPORTA_DDR    0x04

#define GPIO_INTEN          0x30
#define GPIO_INTTYPE_LEVEL  0x38
#define GPIO_INT_POLARITY   0x3c
#define GPIO_INTSTATUS      0x40
#define GPIO_PORTA_EOI      0x4c

#define GPIO_EXT_PORTA      0x50

#define DWAPB_GPIOA_BASE    0x03020000
#define DWAPB_GPIOE_BASE    0x05021000

#define DWAPB_GPIO_SIZE     0x1000

#define DWAPB_GPIO_PORT_NR  5
#define DWAPB_GPIO_NR       32

#define PIN_NUM(port, no)   (((((port) & 0xFu) << 8) | ((no) & 0xFFu)))
#define PIN_PORT(pin)       ((uint8_t)(((pin) >> 8) & 0xFu))
#define PIN_NO(pin)         ((uint8_t)((pin) & 0xFFu))

#define BIT(x)              (1UL << (x))

rt_inline rt_uint32_t dwapb_read32(rt_ubase_t addr)
{
    return HWREG32(addr);
}

rt_inline void dwapb_write32(rt_ubase_t addr, rt_uint32_t value)
{
    HWREG32(addr) = value;
}

static rt_ubase_t dwapb_gpio_base = DWAPB_GPIOA_BASE;
static rt_ubase_t dwapb_gpio_base_e = DWAPB_GPIOE_BASE;

static struct dwapb_event
{
    void (*(hdr[DWAPB_GPIO_NR]))(void *args);
    void *args[DWAPB_GPIO_NR];
    rt_uint8_t is_both_edge[DWAPB_GPIO_NR];
} _dwapb_events[DWAPB_GPIO_PORT_NR];

static void dwapb_toggle_trigger(rt_uint8_t port, rt_uint8_t bit)
{
    rt_uint8_t val;
    rt_ubase_t base_addr;
    rt_uint32_t pol;

    base_addr = (port == 4 ? dwapb_gpio_base_e : (dwapb_gpio_base + DWAPB_GPIO_SIZE * port));

    pol = dwapb_read32(base_addr + GPIO_INT_POLARITY);
    /* Just read the current value right out of the data register */
    val = (rt_uint8_t)((dwapb_read32(base_addr + GPIO_EXT_PORTA) >> (bit)) & 1);

    if (val)
        pol &= ~BIT(bit);
    else
        pol |= BIT(bit);

    dwapb_write32(base_addr + GPIO_INT_POLARITY, pol);
}

static void dwapb_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_uint8_t bit, port;
    rt_ubase_t base_addr;
    rt_uint32_t reg_val;

    bit = PIN_NO(pin);
    port = PIN_PORT(pin);
    base_addr = (port == 4 ? dwapb_gpio_base_e : (dwapb_gpio_base + DWAPB_GPIO_SIZE * port));

    reg_val = dwapb_read32(base_addr + GPIO_SWPORTA_DDR);
    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        reg_val |= BIT(bit);
        break;
    case PIN_MODE_INPUT:
        reg_val &= ~BIT(bit);
        break;
    }

    dwapb_write32(base_addr + GPIO_SWPORTA_DDR, reg_val);
}

static void dwapb_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    rt_uint8_t bit, port;
    rt_ubase_t base_addr;
    rt_uint32_t reg_val;

    bit = PIN_NO(pin);
    port = PIN_PORT(pin);
    base_addr = (port == 4 ? dwapb_gpio_base_e : (dwapb_gpio_base + DWAPB_GPIO_SIZE * port));

    reg_val = dwapb_read32(base_addr + GPIO_SWPORTA_DR);
    reg_val = (value ? (reg_val | BIT(bit)) : (reg_val & (~BIT(bit))));
    dwapb_write32(base_addr + GPIO_SWPORTA_DR, reg_val);
}

static rt_ssize_t dwapb_pin_read(struct rt_device *device, rt_base_t pin)
{
    rt_uint8_t bit, port;
    rt_ubase_t base_addr;

    bit = PIN_NO(pin);
    port = PIN_PORT(pin);
    base_addr = (port == 4 ? dwapb_gpio_base_e : (dwapb_gpio_base + DWAPB_GPIO_SIZE * port));

    rt_uint32_t reg_val = dwapb_read32(GPIO_EXT_PORTA + base_addr);
    return ((reg_val >> (bit)) & 1);
}

static rt_base_t dwapb_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int port_num, pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 2) || (name_len > 3))
    {
        goto out;
    }

    if ((name[0] >= 'A') && (name[0] <= 'E'))
    {
        port_num = (int)(name[0] - 'A');
    }
    else
    {
        goto out;
    }

    for (i = 1; i < name_len; i++)
    {
        pin_num *= 10;
        pin_num += name[i] - '0';
    }

    pin = PIN_NUM(port_num, pin_num);

    return pin;
out:
    rt_kprintf("xy   x:A~E  y:0~31, e.g. C24\n");
    return -RT_EINVAL;
}

static rt_err_t dwapb_pin_attach_irq(struct rt_device *device, rt_base_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_uint8_t bit, port;
    rt_ubase_t base_addr;
    rt_uint32_t it_val, ip_val;

    bit = PIN_NO(pin);
    port = PIN_PORT(pin);

    base_addr = (port == 4 ? dwapb_gpio_base_e : (dwapb_gpio_base + DWAPB_GPIO_SIZE * port));

    it_val = dwapb_read32(base_addr + GPIO_INTTYPE_LEVEL);
    ip_val = dwapb_read32(base_addr + GPIO_INT_POLARITY);

    if (mode == PIN_IRQ_MODE_HIGH_LEVEL || mode == PIN_IRQ_MODE_LOW_LEVEL)
    {
        rt_bool_t polarity = (mode == PIN_IRQ_MODE_HIGH_LEVEL);

        /* Enable level detection */
        it_val = (it_val & (~BIT(bit)));
        /* Select polarity */
        ip_val = (polarity ? (ip_val | BIT(bit)) : (ip_val & (~BIT(bit))));
    }
    else if (mode == PIN_IRQ_MODE_RISING_FALLING)
    {
        /* Disable level detection */
        it_val = (it_val | BIT(bit));
        /* Select both edges */
        dwapb_toggle_trigger(port, bit);
    }
    else if (mode == PIN_IRQ_MODE_RISING || mode == PIN_IRQ_MODE_FALLING)
    {
        rt_bool_t rising = (mode == PIN_IRQ_MODE_RISING);

        /* Disable level detection */
        it_val = (it_val | BIT(bit));
        /* Select edge */
        ip_val = (rising ? (ip_val | BIT(bit)) : (ip_val & (~BIT(bit))));
    }
    else
    {
        /* No trigger: disable everything */
        it_val = (it_val & (~BIT(bit)));
        ip_val = (ip_val & (~BIT(bit)));
    }

    dwapb_write32(base_addr + GPIO_INTTYPE_LEVEL, it_val);
    if (mode != PIN_IRQ_MODE_RISING_FALLING)
        dwapb_write32(base_addr + GPIO_INT_POLARITY, ip_val);

    _dwapb_events[PIN_PORT(pin)].hdr[PIN_NO(pin)] = hdr;
    _dwapb_events[PIN_PORT(pin)].args[PIN_NO(pin)] = args;
    _dwapb_events[PIN_PORT(pin)].is_both_edge[PIN_NO(pin)] = (mode == PIN_IRQ_MODE_RISING_FALLING);

    return RT_EOK;
}

static rt_err_t dwapb_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    _dwapb_events[PIN_PORT(pin)].hdr[PIN_NO(pin)] = RT_NULL;
    _dwapb_events[PIN_PORT(pin)].args[PIN_NO(pin)] = RT_NULL;
    _dwapb_events[PIN_PORT(pin)].is_both_edge[PIN_NO(pin)] = 0;

    return RT_EOK;
}

static rt_err_t dwapb_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_uint8_t bit, port;
    rt_ubase_t base_addr;

    bit = PIN_NO(pin);
    port = PIN_PORT(pin);
    base_addr = (port == 4 ? dwapb_gpio_base_e : (dwapb_gpio_base + DWAPB_GPIO_SIZE * port));

    rt_uint32_t reg_val = dwapb_read32(base_addr + GPIO_INTEN);
    reg_val = (enabled ? (reg_val | BIT(bit)) : (reg_val & (~BIT(bit))));
    dwapb_write32(base_addr + GPIO_INTEN, reg_val);

    return RT_EOK;
}

static const struct rt_pin_ops _dwapb_ops =
{
    dwapb_pin_mode,
    dwapb_pin_write,
    dwapb_pin_read,
    dwapb_pin_attach_irq,
    dwapb_pin_detach_irq,
    dwapb_pin_irq_enable,
    dwapb_pin_get,
};

static void rt_hw_gpio_isr(int irqno, void *param)
{
    rt_uint8_t port;
    rt_ubase_t base_addr;
    rt_uint32_t pending, mask;

    mask = 0;
    port = (irqno == BSP_SYS_GPIO_IRQ_BASE ? 4 : (irqno - BSP_GPIO_IRQ_BASE));

    base_addr = (port == 4 ? dwapb_gpio_base_e : (dwapb_gpio_base + DWAPB_GPIO_SIZE * port));
    pending = dwapb_read32(base_addr + GPIO_INTSTATUS);

    if (pending)
    {
        rt_base_t bit;

        for (bit = 0; bit < DWAPB_GPIO_NR; ++bit)
        {
            if (pending & BIT(bit))
            {
                mask = (mask | (BIT(bit)));

                if (_dwapb_events[port].hdr[bit] != RT_NULL)
                {
                    _dwapb_events[port].hdr[bit](_dwapb_events[port].args[bit]);
                }

                if (_dwapb_events[port].is_both_edge[bit]) {
                    dwapb_toggle_trigger(port, bit);
                }
            }
        }
    }

    dwapb_write32(base_addr + GPIO_PORTA_EOI, mask);
}

int rt_hw_gpio_init(void)
{
    dwapb_gpio_base = (rt_ubase_t)DRV_IOREMAP((void *)dwapb_gpio_base, 0x1000);
    dwapb_gpio_base_e = (rt_ubase_t)DRV_IOREMAP((void *)dwapb_gpio_base_e, 0x1000);

    rt_device_pin_register("gpio", &_dwapb_ops, RT_NULL);

#define INT_INSTALL_GPIO_DEVICE(no)     \
    rt_hw_interrupt_install(BSP_GPIO_IRQ_BASE + (no), rt_hw_gpio_isr, RT_NULL, "gpio");    \
    rt_hw_interrupt_umask(BSP_GPIO_IRQ_BASE + (no));

    INT_INSTALL_GPIO_DEVICE(0);
    INT_INSTALL_GPIO_DEVICE(1);
    INT_INSTALL_GPIO_DEVICE(2);
    INT_INSTALL_GPIO_DEVICE(3);

    rt_hw_interrupt_install(BSP_SYS_GPIO_IRQ_BASE, rt_hw_gpio_isr, RT_NULL, "gpio");
    rt_hw_interrupt_umask(BSP_SYS_GPIO_IRQ_BASE);
    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_gpio_init);

#endif /* RT_USING_PIN */
