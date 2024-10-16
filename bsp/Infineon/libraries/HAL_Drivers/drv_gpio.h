/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-1      Rbb666            first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rthw.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "cyhal_irq_impl.h"

#define GPIO_INTERRUPT_PRIORITY (7u)

#define GET_PIN(PORTx,PIN)      ((((uint8_t)(PORTx)) << 3U) + ((uint8_t)(PIN)))

struct pin_irq_map
{
    rt_uint16_t port;
#if defined(SOC_SERIES_IFX_XMC)
    rt_uint32_t irqno;
#else
    IRQn_Type irqno;
#endif
};

int rt_hw_pin_init(void);

#endif /* __DRV_GPIO_H__ */
