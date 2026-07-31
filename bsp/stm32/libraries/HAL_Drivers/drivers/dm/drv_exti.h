/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_EXTI_H__
#define __DRV_EXTI_H__

#include <rtthread.h>
#include <board.h>
#include <drivers/ofw.h>

struct stm32_exti;

struct stm32_exti *stm32_exti_get(struct rt_ofw_node *np);
int stm32_exti_acquire(struct stm32_exti *exti, GPIO_TypeDef *gpio,
                       rt_base_t pin, rt_uint32_t irq_mode);
rt_err_t stm32_exti_release(struct stm32_exti *exti, GPIO_TypeDef *gpio,
                            rt_base_t pin);

#endif /* __DRV_EXTI_H__ */
