/*
 * Copyright (C) Cvitek Co., Ltd. 2019-2020. All rights reserved.
 *
 * File Name: pinctrl.h
 * Description:
 */

#ifndef __PINCTRL_CV181X_H__
#define __PINCTRL_CV181X_H__

#include "cv181x_pinlist_swconfig.h"
#include "cv181x_reg_fmux_gpio.h"
#include "drv_ioremap.h"

#define  PAD_MIPI_TXM4__MIPI_TXM4 0
#define  PAD_MIPI_TXP4__MIPI_TXP4 0
#define  PAD_MIPI_TXM3__MIPI_TXM3 0
#define  PAD_MIPI_TXP3__MIPI_TXP3 0
#define  PAD_MIPI_TXM2__MIPI_TXM2 0
#define  PAD_MIPI_TXP2__MIPI_TXP2 0
#define  PAD_MIPI_TXM1__MIPI_TXM1 0
#define  PAD_MIPI_TXP1__MIPI_TXP1 0
#define  PAD_MIPI_TXM0__MIPI_TXM0 0
#define  PAD_MIPI_TXP0__MIPI_TXP0 0

#define PINMUX_BASE (uintptr_t)DRV_IOREMAP((void *)0x3001000, 0x1000)

#define PINMUX_MASK(PIN_NAME) FMUX_GPIO_FUNCSEL_##PIN_NAME##_MASK
#define PINMUX_OFFSET(PIN_NAME) FMUX_GPIO_FUNCSEL_##PIN_NAME##_OFFSET
#define PINMUX_VALUE(PIN_NAME, FUNC_NAME) PIN_NAME##__##FUNC_NAME
#define PINMUX_CONFIG(PIN_NAME, FUNC_NAME) \
        mmio_clrsetbits_32(PINMUX_BASE + FMUX_GPIO_FUNCSEL_##PIN_NAME, \
        PINMUX_MASK(PIN_NAME) << PINMUX_OFFSET(PIN_NAME), \
        PINMUX_VALUE(PIN_NAME, FUNC_NAME))

#endif /* __PINCTRL_CV181X_H__ */
