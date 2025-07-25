/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _DRV_PINCTRL_H_
#define _DRV_PINCTRL_H_

#include <rtthread.h>

#define IOMUX_FUNC1 (rt_uint32_t)0
#define IOMUX_FUNC2 (rt_uint32_t)1
#define IOMUX_FUNC3 (rt_uint32_t)2
#define IOMUX_FUNC4 (rt_uint32_t)3
#define IOMUX_FUNC5 (rt_uint32_t)4
void k230_pinctrl_set_function(rt_uint32_t pin, rt_uint32_t func);
void k230_pinctrl_set_ie(rt_uint32_t pin, rt_uint32_t ie);
void k230_pinctrl_set_oe(rt_uint32_t pin, rt_uint32_t oe);
void k230_pinctrl_set_pu(rt_uint32_t pin, rt_uint32_t pu);
void k230_pinctrl_set_pd(rt_uint32_t pin, rt_uint32_t pd);
void k230_pinctrl_set_drv(rt_uint32_t pin, rt_uint32_t drv);
void k230_pinctrl_set_st(rt_uint32_t pin, rt_uint32_t st);
rt_uint32_t k230_pinctrl_get_regval(rt_uint32_t pin);

#endif /* _DRV_PINCTRL_H_ */
