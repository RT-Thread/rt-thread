/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-09-24     iysheng           the first version
 */

#ifndef __GD32_PINMUX_H__
#define __GD32_PINMUX_H__

#include <rtconfig.h>
#include <rtdef.h>
#include <stdint.h>
#ifdef SOC_SERIES_GD32F2
#include "gd32f20x.h"
#include "gd32f20x_exti.h"
#include "gd32f20x_rcu.h"
#elif defined(SOC_SERIES_GD32F4)
#include "gd32f4xx.h"
#if 0
#include "gd32f4xx_exti.h"
#endif
#endif

#define PINMUX_DEFAULT        0xff
#define PINAFIO_DEFAULT       0xff

#define MAX_PORT_COUNTS        9
#define MAX_PIN_COUNTS_1PORT   16

enum port_clk_state_E {
    PORT_CLK_STATE_DISABLE,
    PORT_CLK_STATE_ENABLE,
};

struct _gd32_port4pinmux {
    uint8_t pin_mode[MAX_PIN_COUNTS_1PORT];
#if defined(SOC_SERIES_GD32F4)
    uint8_t pin_afio[MAX_PIN_COUNTS_1PORT];
#endif
    uint32_t port_base;
    rcu_periph_enum port_clk;
};

struct _gd32_pinmux_map {
    struct _gd32_port4pinmux port[MAX_PORT_COUNTS];
    uint8_t port_clk_state[MAX_PORT_COUNTS];
};

#endif /* ifndef __GD32_PINMUX_H__ */
