/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-15     yby          the first version
 */

#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define _MSP432_PIN(index, gpioport, gpio_index)                         \
        {                                                                \
             index, GPIO_PORT##gpioport##_BASE, GPIO_PIN_##gpio_index    \
        }

static const struct pin_index _msp432_pins[] =
{
    /* GPIOA 0~7 */
    _MSP432_PIN(0, A, 0),
    _MSP432_PIN(1, A, 1),
    _MSP432_PIN(2, A, 2),
    _MSP432_PIN(3, A, 3),
    _MSP432_PIN(4, A, 4),
    _MSP432_PIN(5, A, 5),
    _MSP432_PIN(6, A, 6),
    _MSP432_PIN(7, A, 7),
    /* GPIOB 0~5 */
    _MSP432_PIN(8, B, 0),
    _MSP432_PIN(9, B, 1),
    _MSP432_PIN(10, B, 2),
    _MSP432_PIN(11, B, 3),
    _MSP432_PIN(12, B, 4),
    _MSP432_PIN(13, B, 5),
    /* GPIOC 0~7 */
    _MSP432_PIN(14, C, 0),
    _MSP432_PIN(15, C, 1),
    _MSP432_PIN(16, C, 2),
    _MSP432_PIN(17, C, 3),
    _MSP432_PIN(18, C, 4),
    _MSP432_PIN(19, C, 5),
    _MSP432_PIN(20, C, 6),
    _MSP432_PIN(21, C, 7),
    /* GPIOD 0~7 */
    _MSP432_PIN(22, D, 0),
    _MSP432_PIN(23, D, 1),
    _MSP432_PIN(24, D, 2),
    _MSP432_PIN(25, D, 3),
    _MSP432_PIN(26, D, 4),
    _MSP432_PIN(27, D, 5),
    _MSP432_PIN(28, D, 6),
    _MSP432_PIN(29, D, 7),
    /* GPIOE 0~5 */
    _MSP432_PIN(30, E, 0),
    _MSP432_PIN(31, E, 1),
    _MSP432_PIN(32, E, 2),
    _MSP432_PIN(33, E, 3),
    _MSP432_PIN(34, E, 4),
    _MSP432_PIN(35, E, 5),
    /* GPIOF 0~4 */
    _MSP432_PIN(36, F, 0),
    _MSP432_PIN(37, F, 1),
    _MSP432_PIN(38, F, 2),
    _MSP432_PIN(39, F, 3),
    _MSP432_PIN(40, F, 4),
    /* GPIOG 0~1 */
    _MSP432_PIN(41, G, 0),
    _MSP432_PIN(42, G, 1),
    /* GPIOH 0~3 */
    _MSP432_PIN(43, H, 0),
    _MSP432_PIN(44, H, 1),
    _MSP432_PIN(45, H, 0),
    _MSP432_PIN(46, H, 1),
    /* GPIOJ 0~1 */
    _MSP432_PIN(47, J, 0),
    _MSP432_PIN(48, J, 1),
    /* GPIOK 0~7 */
    _MSP432_PIN(49, K, 0),
    _MSP432_PIN(50, K, 1),
    _MSP432_PIN(51, K, 2),
    _MSP432_PIN(52, K, 3),
    _MSP432_PIN(53, K, 4),
    _MSP432_PIN(54, K, 5),
    _MSP432_PIN(55, K, 6),
    _MSP432_PIN(56, K, 7),
    /* GPIOL 0~7 */
    _MSP432_PIN(57, L, 0),
    _MSP432_PIN(58, L, 1),
    _MSP432_PIN(59, L, 2),
    _MSP432_PIN(60, L, 3),
    _MSP432_PIN(61, L, 4),
    _MSP432_PIN(62, L, 5),
    _MSP432_PIN(63, L, 6),
    _MSP432_PIN(64, L, 7),
    /* GPIOM 0~7 */
    _MSP432_PIN(65, M, 0),
    _MSP432_PIN(66, M, 1),
    _MSP432_PIN(67, M, 2),
    _MSP432_PIN(68, M, 3),
    _MSP432_PIN(69, M, 4),
    _MSP432_PIN(70, M, 5),
    _MSP432_PIN(71, M, 6),
    _MSP432_PIN(72, M, 7),
    /* GPION 0~5 */
    _MSP432_PIN(73, N, 0),
    _MSP432_PIN(74, N, 1),
    _MSP432_PIN(75, N, 2),
    _MSP432_PIN(76, N, 3),
    _MSP432_PIN(77, N, 4),
    _MSP432_PIN(78, N, 5),
    /* GPIOP 0~5 */
    _MSP432_PIN(79, P, 0),
    _MSP432_PIN(80, P, 1),
    _MSP432_PIN(81, P, 2),
    _MSP432_PIN(82, P, 3),
    _MSP432_PIN(83, P, 4),
    _MSP432_PIN(84, P, 5),
    /* GPIOQ 0~4 */
    _MSP432_PIN(85, Q, 0),
    _MSP432_PIN(86, Q, 1),
    _MSP432_PIN(87, Q, 2),
    _MSP432_PIN(88, Q, 3),
    _MSP432_PIN(89, Q, 4)
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

static const struct pin_index *_get_pin(rt_base_t pin)
{
    const struct pin_index *index = RT_NULL;

    if (pin < ITEM_NUM(_msp432_pins))
    {
        index = &_msp432_pins[pin];
    }

    return index;
}

static rt_base_t msp432_pin_get(const char *name)
{
    rt_base_t pin = -1;

    if ((name[0] == 'P') || (name[2] == '.'))
    {
        if (name[1] == 'A')
        {
            pin = name[3] - '0';
        }
        else if (name[1] == 'B')
        {
            pin = 8 + name[3] - '0';
        }
        else if (name[1] == 'C')
        {
            pin = 14 + name[3] - '0';
        }
        else if (name[1] == 'D')
        {
            pin = 22 + name[3] - '0';
        }
        else if (name[1] == 'E')
        {
            pin = 30 + name[3] - '0';
        }
        else if (name[1] == 'F')
        {
            pin = 36 + name[3] - '0';
        }
        else if (name[1] == 'G')
        {
            pin = 41 + name[3] - '0';
        }
        else if (name[1] == 'H')
        {
            pin = 43 + name[3] - '0';
        }
        else if (name[1] == 'J')
        {
            pin = 47 + name[3] - '0';
        }
        else if (name[1] == 'K')
        {
            pin = 49 + name[3] - '0';
        }
        else if (name[1] == 'L')
        {
            pin = 57 + name[3] - '0';
        }
        else if (name[1] == 'M')
        {
            pin = 65 + name[3] - '0';
        }
        else if (name[1] == 'N')
        {
            pin = 73 + name[3] - '0';
        }
        else if (name[1] == 'P')
        {
            pin = 79 + name[3] - '0';
        }
        else if (name[1] == 'Q')
        {
            pin = 85 + name[3] - '0';
        }
        else {}
    }

    return pin;
}

static void msp432_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index = RT_NULL;

    index = _get_pin(pin);
    if (index != RT_NULL)
    {
        if (mode == PIN_MODE_INPUT)
        {
            GPIOPinTypeGPIOInput(index->gpioBaseAddress, index->pin);
        }
        else if (mode == PIN_MODE_OUTPUT)
        {
            GPIOPinTypeGPIOOutput(index->gpioBaseAddress, index->pin);
        }
        else if (mode == PIN_MODE_INPUT_PULLUP)
        {
            GPIODirModeSet(index->gpioBaseAddress, index->pin, GPIO_DIR_MODE_IN);
            GPIOPadConfigSet(index->gpioBaseAddress, index->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
        }
        else if (mode == PIN_MODE_INPUT_PULLDOWN)
        {
            GPIODirModeSet(index->gpioBaseAddress, index->pin, GPIO_DIR_MODE_IN);
            GPIOPadConfigSet(index->gpioBaseAddress, index->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
        }
        else if (mode == PIN_MODE_OUTPUT_OD)
        {
            GPIOPadConfigSet(index->gpioBaseAddress, index->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD);
            GPIODirModeSet(index->gpioBaseAddress, index->pin, GPIO_DIR_MODE_OUT);
        }
        else {}
    }
}

static void msp432_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    const struct pin_index *index = RT_NULL;

    index = _get_pin(pin);
    if (index != RT_NULL)
    {
        if (value == PIN_HIGH)
        {
            GPIOPinWrite(index->gpioBaseAddress, index->pin, index->pin);
        }
        else
        {
            GPIOPinWrite(index->gpioBaseAddress, index->pin, 0);
        }
    }
}

static rt_ssize_t msp432_pin_read(struct rt_device *device, rt_base_t pin)
{
    const struct pin_index *index = RT_NULL;
    rt_ssize_t value = -1;

    index = _get_pin(pin);
    if (index != RT_NULL)
    {
        value = (rt_ssize_t)GPIOPinRead(index->gpioBaseAddress, index->pin);
    }
    else
    {
        value = -RT_EINVAL;
    }

    return value;
}

static rt_err_t msp432_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                      rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    /* this is interface for pin_irq, reserved for update. */
    return RT_EOK;
}

static rt_err_t msp432_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    /* this is interface for pin_irq, reserved for update. */
    return RT_EOK;
}

static rt_err_t msp432_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    /* this is interface for pin_irq_enable, reserved for update. */
    return RT_EOK;
}


const static struct rt_pin_ops _msp432_pin_ops =
{
    msp432_pin_mode,
    msp432_pin_write,
    msp432_pin_read,
    msp432_pin_attach_irq,
    msp432_pin_dettach_irq,
    msp432_pin_irq_enable,
    msp432_pin_get,
};

int rt_hw_pin_init(void)
{
    int ret = -1;

#if defined(SYSCTL_PERIPH_GPIOA)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
#endif

#if defined(SYSCTL_PERIPH_GPIOB)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
#endif

#if defined(SYSCTL_PERIPH_GPIOC)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
#endif

#if defined(SYSCTL_PERIPH_GPIOD)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
#endif

#if defined(SYSCTL_PERIPH_GPIOE)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
#endif

#if defined(SYSCTL_PERIPH_GPIOF)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
#endif

#if defined(SYSCTL_PERIPH_GPIOG)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
#endif

#if defined(SYSCTL_PERIPH_GPIOH)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
#endif

#if defined(SYSCTL_PERIPH_GPIOJ)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
#endif

#if defined(SYSCTL_PERIPH_GPIOK)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
#endif

#if defined(SYSCTL_PERIPH_GPIOL)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
#endif

#if defined(SYSCTL_PERIPH_GPIOM)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
#endif

#if defined(SYSCTL_PERIPH_GPION)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
#endif

#if defined(SYSCTL_PERIPH_GPIOP)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
#endif

#if defined(SYSCTL_PERIPH_GPIOQ)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
#endif

    ret = rt_device_pin_register("pin", &_msp432_pin_ops, RT_NULL);

    return ret;
}

#endif   /*RT_USING_PIN*/

/************************** end of file ******************/
