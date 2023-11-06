/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author              Notes
 * 2023-10-25     Raman Gopalan       Initial version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtconfig.h>

#ifdef RT_USING_PIN
int rt_hw_gpio_init(void);
#endif

#endif /* __DRV_GPIO_H__ */
