/*
 * File      : drv_gpio.h
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
 * 2017-11-35     ZYH            update to 3.0.0
 */
#ifndef GPIO_H__
#define GPIO_H__
struct stm32_hw_pin_userdata
{
    int pin;
    uint32_t mode;
};
#define PIN_USERDATA_END {-1,0}
extern struct stm32_hw_pin_userdata stm32_pins[];
int rt_hw_pin_init(void);
#endif
