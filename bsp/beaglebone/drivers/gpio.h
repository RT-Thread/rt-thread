/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#define GET_PIN(gpiox, pinNumber) (rt_base_t)(gpiox << 5 | pinNumber)

int rt_hw_gpio_init(void);

#endif
