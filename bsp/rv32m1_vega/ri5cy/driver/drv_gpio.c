/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-13     Liuguang     the first version.
 * 2018-03-19     Liuguang     add GPIO interrupt mode support.
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "drv_gpio.h"

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#ifdef RT_USING_PIN

struct vega_pin
{
    rt_uint16_t   pin;
    GPIO_Type    *gpio;
    rt_uint32_t   gpio_pin;
};

struct vega_irq
{
    rt_uint16_t           enable;
    struct rt_pin_irq_hdr irq_info;
};

#define __ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))
#define __VEGA_PIN_DEFAULT {0, 0, 0}
#define __VEGA_PIN(INDEX, PORT, PIN) {INDEX, PORT, PIN}

static const struct vega_pin vega_pin_map[] =
{
    __VEGA_PIN_DEFAULT,

    /* GPIOA */
    __VEGA_PIN(1, GPIOA, 0),
    __VEGA_PIN(2, GPIOA, 1),
    __VEGA_PIN(3, GPIOA, 2),
    __VEGA_PIN(4, GPIOA, 3),
    __VEGA_PIN(5, GPIOA, 4),
    __VEGA_PIN(6, GPIOA, 5),
    __VEGA_PIN(7, GPIOA, 6),
    __VEGA_PIN(8, GPIOA, 7),
    __VEGA_PIN(9, GPIOA, 8),
    __VEGA_PIN(10, GPIOA, 9),
    __VEGA_PIN(11, GPIOA, 10),
    __VEGA_PIN(12, GPIOA, 11),
    __VEGA_PIN(13, GPIOA, 12),
    __VEGA_PIN(14, GPIOA, 13),
    __VEGA_PIN(15, GPIOA, 14),
    __VEGA_PIN(16, GPIOA, 15),
    __VEGA_PIN(17, GPIOA, 16),
    __VEGA_PIN(18, GPIOA, 17),
    __VEGA_PIN(19, GPIOA, 18),
    __VEGA_PIN(20, GPIOA, 19),
    __VEGA_PIN(21, GPIOA, 20),
    __VEGA_PIN(22, GPIOA, 21),
    __VEGA_PIN(23, GPIOA, 22),
    __VEGA_PIN(24, GPIOA, 23),
    __VEGA_PIN(25, GPIOA, 24),
    __VEGA_PIN(26, GPIOA, 25),
    __VEGA_PIN(27, GPIOA, 26),
    __VEGA_PIN(28, GPIOA, 27),
    __VEGA_PIN(29, GPIOA, 28),
    __VEGA_PIN(30, GPIOA, 29),
    __VEGA_PIN(31, GPIOA, 30),
    __VEGA_PIN(32, GPIOA, 31),

    /* GPIOB */
    __VEGA_PIN(33, GPIOB, 0),
    __VEGA_PIN(34, GPIOB, 1),
    __VEGA_PIN(35, GPIOB, 2),
    __VEGA_PIN(36, GPIOB, 3),
    __VEGA_PIN(37, GPIOB, 4),
    __VEGA_PIN(38, GPIOB, 5),
    __VEGA_PIN(39, GPIOB, 6),
    __VEGA_PIN(40, GPIOB, 7),
    __VEGA_PIN(41, GPIOB, 8),
    __VEGA_PIN(42, GPIOB, 9),
    __VEGA_PIN(43, GPIOB, 10),
    __VEGA_PIN(44, GPIOB, 11),
    __VEGA_PIN(45, GPIOB, 12),
    __VEGA_PIN(46, GPIOB, 13),
    __VEGA_PIN(47, GPIOB, 14),
    __VEGA_PIN(48, GPIOB, 15),
    __VEGA_PIN(49, GPIOB, 16),
    __VEGA_PIN(50, GPIOB, 17),
    __VEGA_PIN(51, GPIOB, 18),
    __VEGA_PIN(52, GPIOB, 19),
    __VEGA_PIN(53, GPIOB, 20),
    __VEGA_PIN(54, GPIOB, 21),
    __VEGA_PIN(55, GPIOB, 22),
    __VEGA_PIN(56, GPIOB, 23),
    __VEGA_PIN(57, GPIOB, 24),
    __VEGA_PIN(58, GPIOB, 25),
    __VEGA_PIN(59, GPIOB, 26),
    __VEGA_PIN(60, GPIOB, 27),
    __VEGA_PIN(61, GPIOB, 28),
    __VEGA_PIN(62, GPIOB, 29),
    __VEGA_PIN(63, GPIOB, 30),
    __VEGA_PIN(64, GPIOB, 31),

    /* GPIOC */
    __VEGA_PIN(65, GPIOC, 0),
    __VEGA_PIN(66, GPIOC, 1),
    __VEGA_PIN(67, GPIOC, 2),
    __VEGA_PIN(68, GPIOC, 3),
    __VEGA_PIN(69, GPIOC, 4),
    __VEGA_PIN(70, GPIOC, 5),
    __VEGA_PIN(71, GPIOC, 6),
    __VEGA_PIN(72, GPIOC, 7),
    __VEGA_PIN(73, GPIOC, 8),
    __VEGA_PIN(74, GPIOC, 9),
    __VEGA_PIN(75, GPIOC, 10),
    __VEGA_PIN(76, GPIOC, 11),
    __VEGA_PIN(77, GPIOC, 12),
    __VEGA_PIN(78, GPIOC, 13),
    __VEGA_PIN(79, GPIOC, 14),
    __VEGA_PIN(80, GPIOC, 15),
    __VEGA_PIN(81, GPIOC, 16),
    __VEGA_PIN(82, GPIOC, 17),
    __VEGA_PIN(83, GPIOC, 18),
    __VEGA_PIN(84, GPIOC, 19),
    __VEGA_PIN(85, GPIOC, 20),
    __VEGA_PIN(86, GPIOC, 21),
    __VEGA_PIN(87, GPIOC, 22),
    __VEGA_PIN(88, GPIOC, 23),
    __VEGA_PIN(89, GPIOC, 24),
    __VEGA_PIN(90, GPIOC, 25),
    __VEGA_PIN(91, GPIOC, 26),
    __VEGA_PIN(92, GPIOC, 27),
    __VEGA_PIN(93, GPIOC, 28),
    __VEGA_PIN(94, GPIOC, 29),
    __VEGA_PIN(95, GPIOC, 30),
    __VEGA_PIN(96, GPIOC, 31),

    /* GPIOD */
    __VEGA_PIN(97, GPIOD, 0),
    __VEGA_PIN(98, GPIOD, 1),
    __VEGA_PIN(99, GPIOD, 2),
    __VEGA_PIN(100, GPIOD, 3),
    __VEGA_PIN(101, GPIOD, 4),
    __VEGA_PIN(102, GPIOD, 5),
    __VEGA_PIN(103, GPIOD, 6),
    __VEGA_PIN(104, GPIOD, 7),
    __VEGA_PIN(105, GPIOD, 8),
    __VEGA_PIN(106, GPIOD, 9),
    __VEGA_PIN(107, GPIOD, 10),
    __VEGA_PIN(108, GPIOD, 11),
    __VEGA_PIN(109, GPIOD, 12),
    __VEGA_PIN(110, GPIOD, 13),
    __VEGA_PIN(111, GPIOD, 14),
    __VEGA_PIN(112, GPIOD, 15),
    __VEGA_PIN(113, GPIOD, 16),
    __VEGA_PIN(114, GPIOD, 17),
    __VEGA_PIN(115, GPIOD, 18),
    __VEGA_PIN(116, GPIOD, 19),
    __VEGA_PIN(117, GPIOD, 20),
    __VEGA_PIN(118, GPIOD, 21),
    __VEGA_PIN(119, GPIOD, 22),
    __VEGA_PIN(120, GPIOD, 23),
    __VEGA_PIN(121, GPIOD, 24),
    __VEGA_PIN(122, GPIOD, 25),
    __VEGA_PIN(123, GPIOD, 26),
    __VEGA_PIN(124, GPIOD, 27),
    __VEGA_PIN(125, GPIOD, 28),
    __VEGA_PIN(126, GPIOD, 29),
    __VEGA_PIN(127, GPIOD, 30),
    __VEGA_PIN(128, GPIOD, 31),

    /* GPIOE */
    __VEGA_PIN(129, GPIOE, 0),
    __VEGA_PIN(130, GPIOE, 1),
    __VEGA_PIN(131, GPIOE, 2),
    __VEGA_PIN(132, GPIOE, 3),
    __VEGA_PIN(133, GPIOE, 4),
    __VEGA_PIN(134, GPIOE, 5),
    __VEGA_PIN(135, GPIOE, 6),
    __VEGA_PIN(136, GPIOE, 7),
    __VEGA_PIN(137, GPIOE, 8),
    __VEGA_PIN(138, GPIOE, 9),
    __VEGA_PIN(139, GPIOE, 10),
    __VEGA_PIN(140, GPIOE, 11),
    __VEGA_PIN(141, GPIOE, 12),
    __VEGA_PIN(142, GPIOE, 13),
    __VEGA_PIN(143, GPIOE, 14),
    __VEGA_PIN(144, GPIOE, 15),
    __VEGA_PIN(145, GPIOE, 16),
    __VEGA_PIN(146, GPIOE, 17),
    __VEGA_PIN(147, GPIOE, 18),
    __VEGA_PIN(148, GPIOE, 19),
    __VEGA_PIN(149, GPIOE, 20),
    __VEGA_PIN(150, GPIOE, 21),
    __VEGA_PIN(151, GPIOE, 22),
    __VEGA_PIN(152, GPIOE, 23),
    __VEGA_PIN(153, GPIOE, 24),
    __VEGA_PIN(154, GPIOE, 25),
    __VEGA_PIN(155, GPIOE, 26),
    __VEGA_PIN(156, GPIOE, 27),
    __VEGA_PIN(157, GPIOE, 28),
    __VEGA_PIN(158, GPIOE, 29),
    __VEGA_PIN(159, GPIOE, 30),
    __VEGA_PIN(160, GPIOE, 31),
};

static struct vega_irq vega_irq_map[] =
{
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} },
    {PIN_IRQ_DISABLE, {PIN_IRQ_PIN_NONE, PIN_IRQ_MODE_RISING, RT_NULL, RT_NULL} }
};

void gpio_isr(GPIO_Type* base, rt_uint32_t gpio_pin)
{
    if((GPIO_GetPinsInterruptFlags(base) & (1 << gpio_pin)) != 0)
    {
        GPIO_ClearPinsInterruptFlags(base, gpio_pin);

        if(vega_irq_map[gpio_pin].irq_info.hdr != RT_NULL)
        {
            vega_irq_map[gpio_pin].irq_info.hdr(vega_irq_map[gpio_pin].irq_info.args);
        }
    }
}

static IRQn_Type vega_get_irqnum(GPIO_Type *gpio, rt_uint32_t gpio_pin)
{
    IRQn_Type irq_num = NotAvail_IRQn;  /* Invalid interrupt number */

    if(gpio == GPIOA)
    {
        irq_num = PORTA_IRQn;
    }
    else if(gpio == GPIOB)
    {
        irq_num = PORTB_IRQn;
    }
    else if(gpio == GPIOC)
    {
        irq_num = PORTC_IRQn;
    }
    else if(gpio == GPIOD)
    {
        irq_num = PORTD_IRQn;
    }
    else if(gpio == GPIOE)
    {
        irq_num = PORTE_IRQn;
    }

    return irq_num;
}

static void vega_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    clock_ip_name_t clock;
    gpio_pin_config_t gpio;
    rt_uint32_t config_value = 0;

    if((pin > __ARRAY_LEN(vega_pin_map)) || (pin == 0))
    {
        return;
    }

    if (vega_pin_map[pin].gpio == GPIOA)
        clock = kCLOCK_PortA;
    if (vega_pin_map[pin].gpio == GPIOB)
        clock = kCLOCK_PortB;
    if (vega_pin_map[pin].gpio == GPIOC)
        clock = kCLOCK_PortC;
    if (vega_pin_map[pin].gpio == GPIOD)
        clock = kCLOCK_PortD;
    if (vega_pin_map[pin].gpio == GPIOE)
        clock = kCLOCK_PortE;

    CLOCK_EnableClock(clock);

    gpio.outputLogic = 0;

    switch(mode)
    {
        case PIN_MODE_OUTPUT:
        {
            config_value = 0x1030U;
            gpio.pinDirection = kGPIO_DigitalOutput;
        }
        break;

        case PIN_MODE_INPUT:
        {
            config_value = 0x1030U;
            gpio.pinDirection = kGPIO_DigitalInput;
        }
        break;

        case PIN_MODE_INPUT_PULLDOWN:
        {
            config_value = 0x1030U;
            gpio.pinDirection = kGPIO_DigitalInput;
        }
        break;

        case PIN_MODE_INPUT_PULLUP:
        {
            config_value = 0x5030U;
            gpio.pinDirection = kGPIO_DigitalInput;
        }
        break;

        case PIN_MODE_OUTPUT_OD:
        {
            config_value = 0x1830U;
            gpio.pinDirection = kGPIO_DigitalOutput;
        }
        break;
    }

    GPIO_PinInit(vega_pin_map[pin].gpio, vega_pin_map[pin].gpio_pin, &gpio);
}

static rt_ssize_t vega_pin_read(rt_device_t dev, rt_base_t pin)
{
    uint32_t value;

    value = GPIO_ReadPinInput(vega_pin_map[pin].gpio, vega_pin_map[pin].gpio_pin);
    if (value) return PIN_HIGH;

    return PIN_LOW;
}

static void vega_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    if (value == PIN_HIGH)
        GPIO_SetPinsOutput(vega_pin_map[pin].gpio, 1U << vega_pin_map[pin].gpio_pin);
    else
        GPIO_ClearPinsOutput(vega_pin_map[pin].gpio, 1U << vega_pin_map[pin].gpio_pin);
}

static rt_err_t vega_pin_attach_irq(struct rt_device *device, rt_base_t pin,
    rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    const struct vega_pin* pin_map = RT_NULL;
    struct vega_irq* irq_map = RT_NULL;

    pin_map = &vega_pin_map[pin];
    irq_map = &vega_irq_map[vega_pin_map[pin].gpio_pin];

    if(pin_map == RT_NULL || irq_map == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    if(irq_map->enable == PIN_IRQ_ENABLE)
    {
        return -RT_EBUSY;
    }

    irq_map->irq_info.pin  = pin;
    irq_map->irq_info.hdr  = hdr;
    irq_map->irq_info.mode = mode;
    irq_map->irq_info.args = args;

    return RT_EOK;
}

static rt_err_t vega_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    const struct vega_pin* pin_map = RT_NULL;
    struct vega_irq* irq_map = RT_NULL;

    pin_map = &vega_pin_map[pin];
    irq_map = &vega_irq_map[vega_pin_map[pin].gpio_pin];

    if(pin_map == RT_NULL || irq_map == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    if(irq_map->enable == PIN_IRQ_DISABLE)
    {
        return RT_EOK;
    }

    irq_map->irq_info.pin  = PIN_IRQ_PIN_NONE;
    irq_map->irq_info.hdr  = RT_NULL;
    irq_map->irq_info.mode = PIN_IRQ_MODE_RISING;
    irq_map->irq_info.args = RT_NULL;

    return RT_EOK;
}

static rt_err_t vega_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    gpio_pin_config_t gpio;
    IRQn_Type irq_num;
    rt_uint32_t config_value = 0x1b0a0;

    const struct vega_pin* pin_map = RT_NULL;
    struct vega_irq* irq_map = RT_NULL;

    pin_map = &vega_pin_map[pin];
    irq_map = &vega_irq_map[vega_pin_map[pin].gpio_pin];

    if(pin_map == RT_NULL || irq_map == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    if(enabled == PIN_IRQ_ENABLE)
    {
        if(irq_map->enable == PIN_IRQ_ENABLE)
        {
            return -RT_EBUSY;
        }

        if(irq_map->irq_info.pin != pin)
        {
            return -RT_EIO;
        }

        irq_map->enable = PIN_IRQ_ENABLE;

        gpio.pinDirection     = kGPIO_DigitalInput;
        gpio.outputLogic   = 0;

        irq_num = vega_get_irqnum(vega_pin_map[pin].gpio, vega_pin_map[pin].gpio_pin);

        /* TODOL enable port */
        EnableIRQ(irq_num);

        GPIO_PinInit(vega_pin_map[pin].gpio, vega_pin_map[pin].gpio_pin, &gpio);
        // GPIO_EnablePinsInterruptFlags(vega_pin_map[pin].gpio, 1U << vega_pin_map[pin].gpio_pin);
    }
    else if(enabled == PIN_IRQ_DISABLE)
    {
        if(irq_map->enable == PIN_IRQ_DISABLE)
        {
            return RT_EOK;
        }

        irq_map->enable = PIN_IRQ_DISABLE;
        irq_num = vega_get_irqnum(vega_pin_map[pin].gpio, vega_pin_map[pin].gpio_pin);

        DisableIRQ(irq_num);
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static const struct rt_pin_ops vega_pin_ops =
{
    vega_pin_mode,
    vega_pin_write,
    vega_pin_read,

    vega_pin_attach_irq,
    vega_pin_detach_irq,
    vega_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    int ret = RT_EOK;

    ret = rt_device_pin_register("pin", &vega_pin_ops, RT_NULL);
    return ret;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /*RT_USING_PIN */
