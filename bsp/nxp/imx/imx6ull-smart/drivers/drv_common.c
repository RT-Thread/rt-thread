/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-11     RiceChen     the first version
 *
 */

#include <rthw.h>
#include <rtdevice.h>
#include "board.h"

#include "mmu.h"
#include "ioremap.h"
#include "fsl_iomuxc.h"
#include "drv_common.h"

void *imx6ull_get_periph_vaddr(rt_uint32_t paddr)
{
    return rt_ioremap((void *)paddr, sizeof(sizeof(rt_uint32_t)));
}

void *imx6ull_get_periph_paddr(rt_uint32_t vaddr)
{
    return rt_kmem_v2p((void *)vaddr);
}

void imx6ull_gpio_init(const struct imx6ull_iomuxc *gpio)
{
    rt_uint32_t mux_reg_vaddr    = 0;
    rt_uint32_t input_reg_vaddr  = 0;
    rt_uint32_t config_reg_vaddr = 0;

    mux_reg_vaddr    = (rt_uint32_t)(gpio->muxRegister    ? (rt_uint32_t)imx6ull_get_periph_vaddr(gpio->muxRegister) : gpio->muxRegister);
    input_reg_vaddr  = (rt_uint32_t)(gpio->inputRegister  ? (rt_uint32_t)imx6ull_get_periph_vaddr(gpio->inputRegister) : gpio->inputRegister);
    config_reg_vaddr = (rt_uint32_t)(gpio->configRegister ? (rt_uint32_t)imx6ull_get_periph_vaddr(gpio->configRegister) : gpio->configRegister);

    IOMUXC_SetPinMux(mux_reg_vaddr, gpio->muxMode, input_reg_vaddr, gpio->inputDaisy, config_reg_vaddr, gpio->inputOnfield);
    IOMUXC_SetPinConfig(mux_reg_vaddr, gpio->muxMode, input_reg_vaddr, gpio->inputDaisy, config_reg_vaddr, gpio->configValue);
}
