/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-17     CliffLL      first version
 */

#ifndef __DRV_OSPI_H__
#define __DRV_OSPI_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rt_ospi_device;
rt_err_t rt_hw_ospi_device_attach(const char *bus_name, const char *device_name, rt_err_t (*enter_ospi_str_mode)(struct rt_ospi_device *device), rt_err_t (*enter_ospi_dtr_mode)(struct rt_ospi_device *device), rt_err_t (*exit_ospi_mode)(struct rt_ospi_device *device));

#ifdef __cplusplus
}
#endif

#endif /* __DRV_OSPI_H__ */
