/*
 * File      : gpio.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-05     Bernard      the first version
 */
#ifndef GPIO_H__
#define GPIO_H__

struct stm32_gpio_dsc {
	GPIO_TypeDef *	port;
	uint32_t	pin;
  uint8_t pin_source;
};

int stm32_hw_pin_init(void);

#endif
