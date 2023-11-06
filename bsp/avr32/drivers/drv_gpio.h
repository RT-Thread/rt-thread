/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author              Notes
 * 2023-10-25     Raman Gopalan       Initial version
 * 2023-11-06     Raman Gopalan       Abstraction for GPIO driver boilerplate
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtconfig.h>

#ifdef RT_USING_PIN

#ifndef BSP_BOARD_MIZAR32B
#define AVR32_BSP_GPIO_PMIN AVR32_PIN_PA03
#define AVR32_BSP_GPIO_PMAX AVR32_PIN_PB11
#else
#define AVR32_BSP_GPIO_PMIN AVR32_PIN_PA00
#define AVR32_BSP_GPIO_PMAX AVR32_PIN_PX11
#endif

int rt_hw_gpio_init(void);

#endif /* #ifdef RT_USING_PIN */

#endif /* __DRV_GPIO_H__ */
