/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-11     RiceChen     the first version
 *
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <board.h>

struct imx6ull_iomuxc
{
    rt_uint32_t muxRegister;
    rt_uint32_t muxMode;
    rt_uint32_t inputRegister;
    rt_uint32_t inputDaisy;
    rt_uint32_t configRegister;

    rt_uint32_t inputOnfield;

    rt_uint32_t configValue;
};

void *imx6ull_get_periph_vaddr(rt_uint32_t paddr);
void *imx6ull_get_periph_paddr(rt_uint32_t vaddr);

void imx6ull_gpio_init(const struct imx6ull_iomuxc *gpio);

#endif
