/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2015-06-19     ItsEddy           add gpio driver support
 * 2022-09-14     YangZhongQing     full gpio driver support
 *                                  I referred AM335X_StarterWare_02_00_01_01
 */

#include <ctype.h>
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <am33xx.h>
#include <interrupt.h>
#include "gpio.h"

#ifdef RT_USING_PIN

#define reg(base)         *(int*)(base)

#define GPIO_PIN_LOW              (0x0)
#define GPIO_PIN_HIGH             (0x1)

/* Values denoting the Interrupt Line number to be used. */
#define GPIO_INT_LINE_1                  (0x0)
#define GPIO_INT_LINE_2                  (0x1)

#define GPIO_REVISION   (0x0)
#define GPIO_SYSCONFIG   (0x10)
#define GPIO_IRQSTATUS_RAW(n)   (0x24 + (n * 4))
#define GPIO_IRQSTATUS(n)   (0x2C + (n * 4))
#define GPIO_IRQSTATUS_SET(n)   (0x34 + (n * 4))
#define GPIO_IRQSTATUS_CLR(n)   (0x3C + (n * 4))
#define GPIO_IRQWAKEN(n)   (0x44 + (n * 4))
#define GPIO_SYSSTATUS   (0x114)
#define GPIO_CTRL   (0x130)
#define GPIO_OE   (0x134)
#define GPIO_DATAIN   (0x138)
#define GPIO_DATAOUT   (0x13C)
#define GPIO_LEVELDETECT(n)   (0x140 + (n * 4))
#define GPIO_RISINGDETECT   (0x148)
#define GPIO_FALLINGDETECT   (0x14C)
#define GPIO_DEBOUNCENABLE   (0x150)
#define GPIO_DEBOUNCINGTIME   (0x154)
#define GPIO_CLEARDATAOUT   (0x190)
#define GPIO_SETDATAOUT   (0x194)

static const rt_base_t GPIO_BASE[] =
{
    AM33XX_GPIO_0_REGS,
    AM33XX_GPIO_1_REGS,
    AM33XX_GPIO_2_REGS,
    AM33XX_GPIO_3_REGS
};

#define GPIO_INT0x GPIO_INT0A
#define GPIO_INT1x GPIO_INT1A
#define GPIO_INT2x GPIO_INT2A
#define GPIO_INT3x GPIO_INT3A
static const rt_uint8_t GPIO_INTx[] = {GPIO_INT0x, GPIO_INT1x, GPIO_INT2x, GPIO_INT3x};

// auto determine which int line
#define GPIO_INT0_LINE ((GPIO_INT0x == GPIO_INT0A) ? GPIO_INT_LINE_1 : GPIO_INT_LINE_2)
#define GPIO_INT1_LINE ((GPIO_INT1x == GPIO_INT1A) ? GPIO_INT_LINE_1 : GPIO_INT_LINE_2)
#define GPIO_INT2_LINE ((GPIO_INT2x == GPIO_INT2A) ? GPIO_INT_LINE_1 : GPIO_INT_LINE_2)
#define GPIO_INT3_LINE ((GPIO_INT3x == GPIO_INT3A) ? GPIO_INT_LINE_1 : GPIO_INT_LINE_2)
static const rt_uint8_t GPIO_INT_LINEx[] = {GPIO_INT0_LINE, GPIO_INT1_LINE, GPIO_INT2_LINE, GPIO_INT3_LINE};

struct am33xx_pin_irq_hdr
{
    void (*hdr)(void *args);
    void             *args;
};

struct am33xx_gpio_irq_param
{
    struct am33xx_pin_irq_hdr hdr_tab[32];
};

static struct am33xx_gpio_irq_param GPIO_PARAMx[sizeof(GPIO_BASE) / sizeof(GPIO_BASE[0])];

rt_inline void am33xx_gpio_hdr(rt_base_t base, rt_base_t int_line, void *param)
{
    struct am33xx_gpio_irq_param *irq_param = param;
    struct am33xx_pin_irq_hdr *irq_hdr;
    int pinNumber;
    rt_ubase_t irqstatus;

    irqstatus = REG32(base + GPIO_IRQSTATUS(int_line));
    REG32(base + GPIO_IRQSTATUS(int_line)) = irqstatus;

    for (pinNumber = 0; pinNumber < sizeof(irq_param->hdr_tab); pinNumber++)
    {
        if (irqstatus & 0x1)
        {
            irq_hdr = &irq_param->hdr_tab[pinNumber];
            if (irq_hdr->hdr)
                irq_hdr->hdr(irq_hdr->args);
            // if the last one, exit immediately
            if (irqstatus == 0x1)
                break;
        }
        irqstatus >>= 1;
    }
}

static void am33xx_gpio0_isr(int vector, void *param)
{
    am33xx_gpio_hdr(AM33XX_GPIO_0_REGS, GPIO_INT0_LINE, param);
}

static void am33xx_gpio1_isr(int vector, void *param)
{
    am33xx_gpio_hdr(AM33XX_GPIO_1_REGS, GPIO_INT1_LINE, param);
}

static void am33xx_gpio2_isr(int vector, void *param)
{
    am33xx_gpio_hdr(AM33XX_GPIO_2_REGS, GPIO_INT2_LINE, param);
}

static void am33xx_gpio3_isr(int vector, void *param)
{
    am33xx_gpio_hdr(AM33XX_GPIO_3_REGS, GPIO_INT3_LINE, param);
}

static const rt_isr_handler_t GPIO_ISRx[] =
{
    am33xx_gpio0_isr,
    am33xx_gpio1_isr,
    am33xx_gpio2_isr,
    am33xx_gpio3_isr,
};

static void am33xx_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    RT_ASSERT(pin >= 0 && pin < 128);
    RT_ASSERT(mode != PIN_MODE_INPUT_PULLUP); /* Mode not supported */
    rt_base_t gpiox     = pin >> 5;
    rt_base_t pinNumber = pin & 0x1F;

    if (PIN_MODE_OUTPUT == mode)
    {
        reg(GPIO_BASE[gpiox] + GPIO_OE) &= ~(1 << pinNumber);
    }
    else if (PIN_MODE_INPUT == mode)
    {
        reg(GPIO_BASE[gpiox] + GPIO_OE) |= (1 << pinNumber);
    }
}

static void am33xx_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    RT_ASSERT(pin >= 0 && pin < 128);
    rt_base_t gpiox     = pin >> 5;
    rt_base_t pinNumber = pin & 0x1F;

    if (GPIO_PIN_HIGH == value)
    {
        reg(GPIO_BASE[gpiox] + GPIO_SETDATAOUT) = (1 << pinNumber);
    }
    else /* GPIO_PIN_LOW */
    {
        reg(GPIO_BASE[gpiox] + GPIO_CLEARDATAOUT) = (1 << pinNumber);
    }
}

static rt_ssize_t am33xx_pin_read(struct rt_device *device, rt_base_t pin)
{
    RT_ASSERT(pin >= 0 && pin < 128);
    rt_base_t gpiox     = pin >> 5;
    rt_base_t pinNumber = pin & 0x1F;

    return reg(GPIO_BASE[gpiox] + GPIO_DATAIN) & (1 << pinNumber) ? 1 : 0;
}

static rt_err_t am33xx_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                      rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    RT_ASSERT(pin >= 0 && pin < 128);
    rt_base_t gpiox     = pin >> 5;
    rt_base_t pinNumber = pin & 0x1F;
    rt_base_t baseAdd = GPIO_BASE[gpiox];
    struct am33xx_pin_irq_hdr *irq_hdr = &GPIO_PARAMx[gpiox].hdr_tab[pinNumber];
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    if (irq_hdr->hdr != RT_NULL)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    irq_hdr->hdr = hdr;
    irq_hdr->args = args;

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        /* Enabling rising edge detect interrupt generation. */
        REG32(baseAdd + GPIO_RISINGDETECT) |= (1 << pinNumber);

        /* Disabling falling edge detect interrupt generation. */
        REG32(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);

        /* Disabling logic LOW level detect interrupt generation. */
        REG32(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

        /* Disabling logic HIGH level detect interrupt generation. */
        REG32(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);
        break;
    case PIN_IRQ_MODE_FALLING:
        /* Disabling rising edge detect interrupt generation. */
        REG32(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

        /* Enabling falling edge detect interrupt generation. */
        REG32(baseAdd + GPIO_FALLINGDETECT) |= (1 << pinNumber);

        /* Disabling logic LOW level detect interrupt generation. */
        REG32(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

        /* Disabling logic HIGH level detect interrupt generation. */
        REG32(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        /* Enabling rising edge detect interrupt generation. */
        REG32(baseAdd + GPIO_RISINGDETECT) |= (1 << pinNumber);

        /* Enabling falling edge detect interrupt generation. */
        REG32(baseAdd + GPIO_FALLINGDETECT) |= (1 << pinNumber);

        /* Disabling logic LOW level detect interrupt generation. */
        REG32(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

        /* Disabling logic HIGH level detect interrupt generation. */
        REG32(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        /* Disabling logic LOW level detect interrupt generation. */
        REG32(baseAdd + GPIO_LEVELDETECT(0)) &= ~(1 << pinNumber);

        /* Enabling logic HIGH level detect interrupt generation. */
        REG32(baseAdd + GPIO_LEVELDETECT(1)) |= (1 << pinNumber);

        /* Disabling rising edge detect interrupt generation. */
        REG32(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

        /* Disabling falling edge detect interrupt generation. */
        REG32(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);
        break;
    case PIN_IRQ_MODE_LOW_LEVEL:
        /* Enabling logic LOW level detect interrupt geenration. */
        REG32(baseAdd + GPIO_LEVELDETECT(0)) |= (1 << pinNumber);

        /* Disabling logic HIGH level detect interrupt generation. */
        REG32(baseAdd + GPIO_LEVELDETECT(1)) &= ~(1 << pinNumber);

        /* Disabling rising edge detect interrupt generation. */
        REG32(baseAdd + GPIO_RISINGDETECT) &= ~(1 << pinNumber);

        /* Disabling falling edge detect interrupt generation. */
        REG32(baseAdd + GPIO_FALLINGDETECT) &= ~(1 << pinNumber);
        break;
    }

    rt_hw_interrupt_enable(level);
    return 0;
}

static rt_err_t am33xx_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    RT_ASSERT(pin >= 0 && pin < 128);
    rt_base_t gpiox     = pin >> 5;
    rt_base_t pinNumber = pin & 0x1F;
    struct am33xx_pin_irq_hdr *irq_hdr = &GPIO_PARAMx[gpiox].hdr_tab[pinNumber];
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    irq_hdr->hdr = RT_NULL;
    irq_hdr->args = RT_NULL;

    rt_hw_interrupt_enable(level);
    return 0;
}

static rt_err_t am33xx_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    RT_ASSERT(pin >= 0 && pin < 128);
    rt_base_t gpiox     = pin >> 5;
    rt_base_t pinNumber = pin & 0x1F;
    rt_base_t baseAdd = GPIO_BASE[gpiox];
    rt_base_t intLine = GPIO_INT_LINEx[gpiox];

    if (enabled == PIN_IRQ_ENABLE)
        REG32(baseAdd + GPIO_IRQSTATUS_SET(intLine)) = (1 << pinNumber);
    else
        REG32(baseAdd + GPIO_IRQSTATUS_CLR(intLine)) = (1 << pinNumber);

    return 0;
}

// name format: P0.0, range: GPIO0_[31:0] ... GPIO5_[31:0]
static rt_base_t am33xx_pin_get(const char *name)
{
    rt_base_t gpiox;
    rt_base_t pinNumber;

    if (!isdigit((int)name[1]))
        return -RT_EINVAL;
    gpiox = name[1] - '0';

    if (name[2] != '.')
        return -RT_EINVAL;

    if (!isdigit((int)name[3]))
        return -RT_EINVAL;
    pinNumber = name[3] - '0';

    if (name[4] == '\0')
        goto done;
    else if (!isdigit((int)name[4]))
        return -RT_EINVAL;

    pinNumber *= 10;
    pinNumber += name[4] - '0';

    if (name[5] != '\0')
        return -RT_EINVAL;

done:
    if (pinNumber > 0x1F)
        return -RT_EINVAL;

    return GET_PIN(gpiox, pinNumber);
}

static const struct rt_pin_ops am33xx_pin_ops =
{
    am33xx_pin_mode,
    am33xx_pin_write,
    am33xx_pin_read,
    am33xx_pin_attach_irq,
    am33xx_pin_detach_irq,
    am33xx_pin_irq_enable,
    am33xx_pin_get,
};

int rt_hw_gpio_init(void)
{
    int vector;
    rt_base_t gpiox;
    char name[RT_NAME_MAX];

    for (gpiox = 0; gpiox < 4; gpiox++)
    {
        rt_snprintf(name, sizeof(name), "%s%d", "gpio", gpiox);
        vector = GPIO_INTx[gpiox];

        rt_hw_interrupt_install(vector, GPIO_ISRx[gpiox], &GPIO_PARAMx[gpiox], name);
        rt_hw_interrupt_control(vector, 0, 0);
        rt_hw_interrupt_umask(vector);
    }

    rt_device_pin_register("gpio", &am33xx_pin_ops, RT_NULL);
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_gpio_init);
#endif
