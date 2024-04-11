/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-07-29     KyleChan          first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <board.h>
#include <rthw.h>
#include <rtdbg.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drv_common.h>
#include <hal_data.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOC_SERIES_R9A07G0
#define RA_MIN_PIN_VALUE    BSP_IO_PORT_00_PIN_0
#define RA_MAX_PIN_VALUE    BSP_IO_PORT_24_PIN_7
#else
#define RA_MIN_PIN_VALUE    BSP_IO_PORT_00_PIN_00
#define RA_MAX_PIN_VALUE    BSP_IO_PORT_11_PIN_15
#endif

#ifdef R_ICU_H
struct ra_pin_irq_map
{
    const icu_instance_ctrl_t     *irq_ctrl;
    const external_irq_cfg_t      *irq_cfg;
};
#endif

int rt_hw_pin_init(void);
#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

