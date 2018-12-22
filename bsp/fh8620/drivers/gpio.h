/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
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
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef GPIO_H_
#define GPIO_H_

#include <rtdef.h>

/**
 * GPIO interrupt trigger type macro,
 * each represent an interrupt trigger mode
 *
 * @see gpio_set_irq_type();
 */
enum
{
    IRQ_TYPE_NONE       = 0x00000000,                                       /**< none*/
    IRQ_TYPE_EDGE_RISING    = 0x00000001,                                   /**< rising edge*/
    IRQ_TYPE_EDGE_FALLING   = 0x00000002,                                   /**< falling edge*/
    IRQ_TYPE_EDGE_BOTH  = (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING),
    IRQ_TYPE_LEVEL_HIGH = 0x00000004,                                       /**< high level*/
    IRQ_TYPE_LEVEL_LOW  = 0x00000008,                                       /**< low level*/
    IRQ_TYPE_LEVEL_MASK = (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH),
    IRQ_TYPE_TRIGGER_MASK   = (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW | \
            IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING),
};

/**
 * GPIO direction macro,
 * each represent a direction
 *
 * @see gpio_get_direction();
 * @see gpio_set_direction();
 */
#define GPIO_DIR_OUTPUT 1       /**< output*/
#define GPIO_DIR_INPUT  0       /**< input*/

/**
 * convert GPIO number to IRQ number
 * @param gpio GPIO number to be converted
 * @return IRQ number
 */
rt_uint32_t gpio_to_irq(rt_uint32_t gpio);

/**
 * disable GPIO's debounce mode
 * controls whether an external signal that is the source
 * of an interrupt needs to be debounced to remove any
 * spurious glitches.
 * @param gpio GPIO number
 */
void gpio_disable_debounce(rt_uint32_t gpio);

/**
 * enable GPIO's debounce mode
 * controls whether an external signal that is the source
 * of an interrupt needs to be debounced to remove any
 * spurious glitches.
 * @param gpio GPIO number
 */
void gpio_enable_debounce(rt_uint32_t gpio);

/**
 * allows each GPIO to be configured for interrupts
 * it configures the corresponding GPIO to become an interrupt
 * @param gpio GPIO number
 */
void gpio_irq_enable(rt_uint32_t irq);

/**
 * GPIO operates as a normal GPIO signal
 * interrupts are disabled
 * @param gpio GPIO number
 */
void gpio_irq_disable(rt_uint32_t irq);

/**
 * it configures the interrupt type to be
 * falling-edge or active-low sensitive
 * rising-edge or active-high sensitive.
 * @param gpio GPIO number
 * @param type interrupt type
 * @return 0 if OK
 */
int gpio_set_irq_type(rt_uint32_t gpio, rt_uint32_t type);

/**
 * mask the interrupt
 * @param gpio GPIO number
 * @return 0 if OK
 */
int gpio_irq_mask(rt_uint32_t irq);

/**
 * unmask the interrupt
 * @param gpio GPIO number
 * @return 0 if OK
 */
int gpio_irq_unmask(rt_uint32_t irq);

/**
 * get corresponding GPIO's direction
 * @param gpio GPIO number
 * @return 0 - input
 *         1 - output
 */
int gpio_get_direction(rt_uint32_t gpio);

/**
 * set corresponding GPIO's direction
 * @param gpio GPIO number
 * @return 0 - input
 *         1 - output
 */
void gpio_set_direction(rt_uint32_t gpio, rt_uint32_t direction);

/**
 * get corresponding GPIO's value
 * @param gpio GPIO number
 * @return GPIO value
 */
int gpio_get_value(rt_uint32_t gpio);

/**
 * set corresponding GPIO's value
 * @param gpio GPIO number
 * @param val GPIO value
 */
void gpio_set_value(rt_uint32_t gpio, int val);

/**
 * set corresponding GPIO's direction to input
 * @param gpio GPIO number
 * @return 0 if OK
 */
int gpio_direction_input(rt_uint32_t gpio);

/**
 * set corresponding GPIO's value and set direction to output
 * @param gpio GPIO number
 * @param val GPIO value
 * @return 0 if OK
 */
int gpio_direction_output(rt_uint32_t gpio, rt_uint32_t val);

/**
 * request a GPIO
 * @param gpio GPIO number
 * @return 0 if OK
 */
int gpio_request(rt_uint32_t gpio);

/**
 * release a GPIO
 * @param gpio GPIO number
 * @return 0 if OK
 */
int gpio_release(rt_uint32_t gpio);

/**
 * initialize GPIO driver
 */
void rt_hw_gpio_init(void);

#endif /* GPIO_H_ */
