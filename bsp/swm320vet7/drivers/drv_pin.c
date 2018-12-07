/*
 * File      : drv_pin.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018-05-31     ZYH          first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <SWM320_port.h>
#include <SWM320_gpio.h>
#include <SWM320_exti.h>
#include <rthw.h>
typedef void (*pin_callback_t)(void *args);
struct pin
{
    uint32_t package_index;
    const char *name;
    GPIO_TypeDef *port;
    uint32_t group_index;
    IRQn_Type irq;
    rt_uint32_t irq_mode;
    pin_callback_t callback;
    void *callback_args;
};
typedef struct pin pin_t;

#define SWM32_PIN(a, b, c, d, ...)                 \
    {                                              \
        a, #b, GPIO##c, d, GPIO##c##_IRQn, 0, 0, 0 \
    }
#define GPIO0 ((GPIO_TypeDef *)(0))
#define GPIO0_IRQn (GPIOA0_IRQn)

static pin_t swm32_pin_map[] =
    {
        SWM32_PIN(0, None, 0, 0, NO_FUNC, None, None, None),
        SWM32_PIN(1, ADC0 CH3, 0, 0, NO_FUNC, None, None, ADC0 CH3),
        SWM32_PIN(2, ADC0 REFP, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(3, Cap0, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(4, B12, B, 12, NO_FUNC, None, None, GPIO),
        SWM32_PIN(5, RTC VDD, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(6, N14, N, 14, FUNC_A, LCD D14, None, GPIO),
        SWM32_PIN(7, N13, N, 13, FUNC_B, LCD D13, None, GPIO),
        SWM32_PIN(8, N12, N, 12, FUNC_A, LCD D12, None, GPIO),
        SWM32_PIN(9, N11, N, 11, FUNC_B, LCD D11, None, GPIO),
        SWM32_PIN(10, VDD 3.3V, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(11, VSS 3.3V, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(12, Cap 2, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(13, N9, N, 9, FUNC_B, LCD D9, None, GPIO),
        SWM32_PIN(14, N10, N, 10, FUNC_A, LCD D10, None, GPIO),
        SWM32_PIN(15, Cap 1, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(16, AVSS, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(17, AVDD, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(18, N2, N, 2, FUNC_A, LCD D2, None, GPIO),
        SWM32_PIN(19, N1, N, 1, FUNC_B, LCD D1, None, GPIO),
        SWM32_PIN(20, N0, N, 0, FUNC_A, LCD D0, None, GPIO),
        SWM32_PIN(21, C4, C, 4, FUNC_A, None, ADC1 CH3, GPIO),
        SWM32_PIN(22, C5, C, 5, FUNC_B, None, ADC1 CH2, GPIO),
        SWM32_PIN(23, C6, C, 6, FUNC_A, None, ADC1 CH1, GPIO),
        SWM32_PIN(24, C7, C, 7, FUNC_B, None, ADC1 CH0, GPIO),
        SWM32_PIN(25, C2, C, 2, FUNC_A, None, None, GPIO),
        SWM32_PIN(26, C3, C, 3, FUNC_B, None, None, GPIO),
        SWM32_PIN(27, XHIN, 0, 0, NO_FUNC, None, None, XHIN),
        SWM32_PIN(28, XHOUT, 0, 0, NO_FUNC, None, None, XHOUT),
        SWM32_PIN(29, RESET, 0, 0, NO_FUNC, None, None, RESET),
        SWM32_PIN(30, M2, M, 2, FUNC_A, NFLASH / SRAM / SDRAM D13, None, GPIO),
        SWM32_PIN(31, M3, M, 3, FUNC_B, NFLASH / SRAM / SDRAM D12, None, GPIO),
        SWM32_PIN(32, M4, M, 4, FUNC_A, NFLASH / SRAM / SDRAM D11, None, GPIO),
        SWM32_PIN(33, M5, M, 5, FUNC_B, NFLASH / SRAM / SDRAM D10, None, GPIO),
        SWM32_PIN(34, M6, M, 6, FUNC_A, NFLASH / SRAM / SDRAM D9, None, GPIO),
        SWM32_PIN(35, M7, M, 7, FUNC_B, NFLASH / SRAM / SDRAM D8, None, GPIO),
        SWM32_PIN(36, M8, M, 8, FUNC_A, NFLASH / SRAM / SDRAM D7, None, GPIO),
        SWM32_PIN(37, M9, M, 9, FUNC_B, NFLASH / SRAM / SDRAM D6, None, GPIO),
        SWM32_PIN(38, M10, M, 10, FUNC_A, NFLASH / SRAM / SDRAM D5, None, GPIO),
        SWM32_PIN(39, M11, M, 11, FUNC_B, NFLASH / SRAM / SDRAM D4, None, GPIO),
        SWM32_PIN(40, M12, M, 12, FUNC_A, NFLASH / SRAM / SDRAM D3, None, GPIO),
        SWM32_PIN(41, M13, M, 13, FUNC_B, NFLASH / SRAM / SDRAM D2, None, GPIO),
        SWM32_PIN(42, M14, M, 14, FUNC_A, NFLASH / SRAM / SDRAM D1, None, GPIO),
        SWM32_PIN(43, M15, M, 15, FUNC_B, NFLASH / SRAM / SDRAM D0, None, GPIO),
        SWM32_PIN(44, M16, M, 16, FUNC_A, NFLASH / SRAM / SDRAM OEN, None, GPIO),
        SWM32_PIN(45, M17, M, 17, FUNC_B, NFLASH / SRAM / SDRAM WEN, None, GPIO),
        SWM32_PIN(46, M18, M, 18, FUNC_A, NFLASH CEN, None, GPIO),
        SWM32_PIN(47, M19, M, 19, FUNC_B, SDRAM CSN, None, GPIO),
        SWM32_PIN(48, M20, M, 20, FUNC_A, SRAM CSN, None, GPIO),
        SWM32_PIN(49, M21, M, 21, FUNC_B, SDRAM CKE, None, GPIO),
        SWM32_PIN(50, VDDIO, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(51, M1, M, 1, FUNC_B, NFLASH / SRAM / SDRAM D14, None, GPIO),
        SWM32_PIN(52, M0, M, 0, FUNC_A, NFLASH / SRAM / SDRAM D15, None, GPIO),
        SWM32_PIN(53, P0, P, 0, FUNC_A, NFLASH / SRAM / SDRAM A0, None, GPIO),
        SWM32_PIN(54, P1, P, 1, FUNC_B, NFLASH / SRAM / SDRAM A1, None, GPIO),
        SWM32_PIN(55, P2, P, 2, FUNC_A, NFLASH / SRAM / SDRAM A2, SD D7, GPIO),
        SWM32_PIN(56, P3, P, 3, FUNC_B, NFLASH / SRAM / SDRAM A3, SD D6, GPIO),
        SWM32_PIN(57, P4, P, 4, FUNC_A, NFLASH / SRAM / SDRAM A4, SD D5, GPIO),
        SWM32_PIN(58, P5, P, 5, FUNC_B, NFLASH / SRAM / SDRAM A5, SD D4, GPIO),
        SWM32_PIN(59, P6, P, 6, FUNC_A, NFLASH / SRAM / SDRAM A6, SD D3, GPIO),
        SWM32_PIN(60, P7, P, 7, FUNC_B, NFLASH / SRAM / SDRAM A7, SD D2, GPIO),
        SWM32_PIN(61, P8, P, 8, FUNC_A, NFLASH / SRAM / SDRAM A8, SD D1, GPIO),
        SWM32_PIN(62, P9, P, 9, FUNC_B, NFLASH / SRAM / SDRAM A9, SD D0, GPIO),
        SWM32_PIN(63, P10, P, 10, FUNC_A, NFLASH / SRAM / SDRAM A10, SD CMD, GPIO),
        SWM32_PIN(64, P11, P, 11, FUNC_B, NFLASH / SRAM / SDRAM A11, SD CLK, GPIO),
        SWM32_PIN(65, P12, P, 12, FUNC_A, NFLASH / SRAM / SDRAM A12, SD DETECT, GPIO),
        SWM32_PIN(66, P13, P, 13, FUNC_B, NFLASH / SRAM A13 / SDRAM CLK, None, GPIO),
        SWM32_PIN(67, P14, P, 14, FUNC_A, NFLASH / SRAM A14 / SDRAM CAS, None, GPIO),
        SWM32_PIN(68, P15, P, 15, FUNC_B, NFLASH / SRAM A15 / SDRAM RAS, None, GPIO),
        SWM32_PIN(69, P16, P, 16, FUNC_A, NFLASH / SRAM A16 / SDRAM LDQ, None, GPIO),
        SWM32_PIN(70, P17, P, 17, FUNC_B, NFLASH / SRAM A17 / SDRAM UDQ, None, GPIO),
        SWM32_PIN(71, P18, P, 18, FUNC_A, NFLASH / SRAM A18, None, GPIO),
        SWM32_PIN(72, P19, P, 19, FUNC_B, NFLASH / SRAM A19, None, GPIO),
        SWM32_PIN(73, P20, P, 20, FUNC_A, NFLASH / SRAM A20 / SDRAM BA0, None, GPIO),
        SWM32_PIN(74, P21, P, 21, FUNC_B, NFLASH / SRAM A21 / SDRAM BA1, None, GPIO),
        SWM32_PIN(75, P22, P, 22, FUNC_A, NFLASH / SRAM A22 / LB, None, GPIO),
        SWM32_PIN(76, P23, P, 23, FUNC_B, NFLASH / SRAM A23 / HB, None, GPIO),
        SWM32_PIN(77, B0, B, 0, FUNC_A, SD DETECT, None, GPIO),
        SWM32_PIN(78, A0, A, 0, FUNC_A, SWCLK, None, GPIO),
        SWM32_PIN(79, A1, A, 1, FUNC_B, SWIO, None, GPIO),
        SWM32_PIN(80, A2, A, 2, FUNC_A, None, None, GPIO),
        SWM32_PIN(81, A3, A, 3, FUNC_B, None, None, GPIO),
        SWM32_PIN(82, A4, A, 4, FUNC_A, None, None, GPIO),
        SWM32_PIN(83, A5, A, 5, FUNC_B, None, None, GPIO),
        SWM32_PIN(84, VSSIO, 0, 0, NO_FUNC, None, None, Power),
        SWM32_PIN(85, C1, C, 1, FUNC_B, None, None, GPIO),
        SWM32_PIN(86, N19, N, 19, NO_FUNC, LCD WNR, None, GPIO),
        SWM32_PIN(87, N18, N, 18, NO_FUNC, LCD RS, None, GPIO),
        SWM32_PIN(88, N17, N, 17, FUNC_B, LCD CSN, None, GPIO),
        SWM32_PIN(89, N16, N, 16, FUNC_A, LCD RD, None, GPIO),
        SWM32_PIN(90, N15, N, 15, FUNC_B, LCD D15, None, GPIO),
        SWM32_PIN(91, N8, N, 8, FUNC_A, LCD D8, None, GPIO),
        SWM32_PIN(92, N7, N, 7, FUNC_B, LCD D7, None, GPIO),
        SWM32_PIN(93, N6, N, 6, FUNC_A, LCD D6, None, GPIO),
        SWM32_PIN(94, N5, N, 5, FUNC_B, LCD D5, None, GPIO),
        SWM32_PIN(95, N4, N, 4, FUNC_A, LCD D4, None, GPIO),
        SWM32_PIN(96, N3, N, 3, FUNC_B, LCD D3, None, GPIO),
        SWM32_PIN(97, A9, A, 9, FUNC_B, None, ADC0 CH7, GPIO),
        SWM32_PIN(98, A10, A, 10, FUNC_A, None, ADC0 CH6, GPIO),
        SWM32_PIN(99, A11, A, 11, FUNC_B, None, ADC0 CH5, GPIO),
        SWM32_PIN(100, A12, A, 12, NO_FUNC, None, ADC0 CH4, GPIO)};
#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
static pin_t *get_pin(uint8_t pin)
{
    pin_t *index;
    if (pin < ITEM_NUM(swm32_pin_map))
    {
        index = &swm32_pin_map[pin];
        if (index->port == GPIO0)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }
    return index;
};

static void pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    pin_t *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    if (value)
    {
        GPIO_SetBit(index->port, index->group_index);
    }
    else
    {
        GPIO_ClrBit(index->port, index->group_index);
    }
}
static int pin_read(rt_device_t dev, rt_base_t pin)
{
    pin_t *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return PIN_LOW;
    }
    return GPIO_GetBit(index->port, index->group_index);
}

static void pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    pin_t *index;
    int dir = 0;
    int pull_up = 0;
    int pull_down = 0;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    /* Configure GPIO_InitStructure */
    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        dir = 1;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        dir = 0;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        dir = 0;
        pull_up = 1;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        dir = 0;
        pull_down = 1;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        pull_up = 1;
    }
    GPIO_Init(index->port, index->group_index, dir, pull_up, pull_down);
}

static rt_err_t pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                               rt_uint32_t mode, pin_callback_t cb, void *args)
{
    pin_t *index;
    rt_base_t level;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_EINVAL;
    }
    level = rt_hw_interrupt_disable();
    index->callback = cb;
    index->callback_args = args;
    index->irq_mode = mode;

    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    pin_t *index;
    rt_base_t level;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_EINVAL;
    }
    level = rt_hw_interrupt_disable();
    index->callback = 0;
    index->callback_args = 0;
    index->irq_mode = 0;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t pin_irq_enable(struct rt_device *device, rt_base_t pin,
                               rt_uint32_t enabled)
{
    pin_t *index;
    rt_base_t level = 0;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_EINVAL;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {

        switch (index->irq_mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_Init(index->port, index->group_index, 0, 0, 1);
            EXTI_Init(index->port, index->group_index, EXTI_RISE_EDGE);
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_Init(index->port, index->group_index, 0, 1, 0);
            EXTI_Init(index->port, index->group_index, EXTI_FALL_EDGE);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_Init(index->port, index->group_index, 0, 1, 1);
            EXTI_Init(index->port, index->group_index, EXTI_BOTH_EDGE);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            GPIO_Init(index->port, index->group_index, 0, 0, 1);
            EXTI_Init(index->port, index->group_index, EXTI_HIGH_LEVEL);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            GPIO_Init(index->port, index->group_index, 0, 1, 0);
            EXTI_Init(index->port, index->group_index, EXTI_LOW_LEVEL);
            break;
        default:
            rt_hw_interrupt_enable(level);
            return RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();
        NVIC_EnableIRQ(index->irq);
        EXTI_Open(index->port, index->group_index);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        NVIC_DisableIRQ(index->irq);
        EXTI_Close(index->port, index->group_index);
    }
    else
    {
        return RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops pin_ops =
    {
        pin_mode,
        pin_write,
        pin_read,
        pin_attach_irq,
        pin_dettach_irq,
        pin_irq_enable,
};
int rt_hw_pin_init(void)
{
    int result;
    result = rt_device_pin_register("pin", &pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);
void GPIOA_Handler(void)
{
    static int gpio[24];
    int index = 0;
    static int init = 0;
    pin_t *pin;
    /* enter interrupt */
    rt_interrupt_enter();
    if (init == 0)
    {
        init = 1;
        for (pin = &swm32_pin_map[1]; pin->package_index < ITEM_NUM(swm32_pin_map); pin++)
        {
            if (pin->port == GPIOA)
            {
                gpio[index] = pin->package_index;
                index++;
                RT_ASSERT(index >= 24)
            }
        }
    }
    for (index = 0; index < 24; index++)
    {
        pin = get_pin(gpio[index]);
        if (index != RT_NULL)
        {
            if (EXTI_State(pin->port, pin->group_index))
            {
                EXTI_Clear(pin->port, pin->group_index);
                if (pin->callback)
                {
                    pin->callback(pin->callback_args);
                }
            }
        }
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
void GPIOB_Handler(void)
{
    static int gpio[24];
    int index = 0;
    static int init = 0;
    pin_t *pin;
    /* enter interrupt */
    rt_interrupt_enter();
    if (init == 0)
    {
        init = 1;
        for (pin = &swm32_pin_map[1]; pin->package_index < ITEM_NUM(swm32_pin_map); pin++)
        {
            if (pin->port == GPIOB)
            {
                gpio[index] = pin->package_index;
                index++;
                RT_ASSERT(index >= 24)
            }
        }
    }
    for (index = 0; index < 24; index++)
    {
        pin = get_pin(gpio[index]);
        if (index != RT_NULL)
        {
            if (EXTI_State(pin->port, pin->group_index))
            {
                EXTI_Clear(pin->port, pin->group_index);
                if (pin->callback)
                {
                    pin->callback(pin->callback_args);
                }
            }
        }
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
void GPIOC_Handler(void)
{
    static int gpio[24];
    int index = 0;
    static int init = 0;
    pin_t *pin;
    /* enter interrupt */
    rt_interrupt_enter();
    if (init == 0)
    {
        init = 1;
        for (pin = &swm32_pin_map[1]; pin->package_index < ITEM_NUM(swm32_pin_map); pin++)
        {
            if (pin->port == GPIOC)
            {
                gpio[index] = pin->package_index;
                index++;
                RT_ASSERT(index >= 24)
            }
        }
    }
    for (index = 0; index < 24; index++)
    {
        pin = get_pin(gpio[index]);
        if (index != RT_NULL)
        {
            if (EXTI_State(pin->port, pin->group_index))
            {
                EXTI_Clear(pin->port, pin->group_index);
                if (pin->callback)
                {
                    pin->callback(pin->callback_args);
                }
            }
        }
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
void GPIOM_Handler(void)
{
    static int gpio[24];
    int index = 0;
    static int init = 0;
    pin_t *pin;
    /* enter interrupt */
    rt_interrupt_enter();
    if (init == 0)
    {
        init = 1;
        for (pin = &swm32_pin_map[1]; pin->package_index < ITEM_NUM(swm32_pin_map); pin++)
        {
            if (pin->port == GPIOM)
            {
                gpio[index] = pin->package_index;
                index++;
                RT_ASSERT(index >= 24)
            }
        }
    }
    for (index = 0; index < 24; index++)
    {
        pin = get_pin(gpio[index]);
        if (index != RT_NULL)
        {
            if (EXTI_State(pin->port, pin->group_index))
            {
                EXTI_Clear(pin->port, pin->group_index);
                if (pin->callback)
                {
                    pin->callback(pin->callback_args);
                }
            }
        }
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
void GPION_Handler(void)
{
    static int gpio[24];
    int index = 0;
    static int init = 0;
    pin_t *pin;
    /* enter interrupt */
    rt_interrupt_enter();
    if (init == 0)
    {
        init = 1;
        for (pin = &swm32_pin_map[1]; pin->package_index < ITEM_NUM(swm32_pin_map); pin++)
        {
            if (pin->port == GPION)
            {
                gpio[index] = pin->package_index;
                index++;
                RT_ASSERT(index >= 24)
            }
        }
    }
    for (index = 0; index < 24; index++)
    {
        pin = get_pin(gpio[index]);
        if (index != RT_NULL)
        {
            if (EXTI_State(pin->port, pin->group_index))
            {
                EXTI_Clear(pin->port, pin->group_index);
                if (pin->callback)
                {
                    pin->callback(pin->callback_args);
                }
            }
        }
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
void GPIOP_Handler(void)
{
    static int gpio[24];
    int index = 0;
    static int init = 0;
    pin_t *pin;
    /* enter interrupt */
    rt_interrupt_enter();
    if (init == 0)
    {
        init = 1;
        for (pin = &swm32_pin_map[1]; pin->package_index < ITEM_NUM(swm32_pin_map); pin++)
        {
            if (pin->port == GPIOP)
            {
                gpio[index] = pin->package_index;
                index++;
                RT_ASSERT(index >= 24)
            }
        }
    }
    for (index = 0; index < 24; index++)
    {
        pin = get_pin(gpio[index]);
        if (index != RT_NULL)
        {
            if (EXTI_State(pin->port, pin->group_index))
            {
                EXTI_Clear(pin->port, pin->group_index);
                if (pin->callback)
                {
                    pin->callback(pin->callback_args);
                }
            }
        }
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
