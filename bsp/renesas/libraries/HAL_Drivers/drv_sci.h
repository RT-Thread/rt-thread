/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-24     Vandoul      first version
 */

#ifndef __DRV_SCI_H__
#define __DRV_SCI_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "hal_data.h"
#include "board.h"
#include <rthw.h>
#include <drv_common.h>
#include <drv_config.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_SCIn_SPI
rt_err_t rt_hw_sci_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin);
#endif

#ifdef __cplusplus
}
#endif

#endif /*__DRV_SCI_H__ */
