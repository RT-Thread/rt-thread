/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-31     RT-Thread    first implementation
 */

#ifndef __DRV_OSPI_H__
#define __DRV_OSPI_H__

#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

rt_err_t rt_hw_ospi_device_attach(const char *bus_name,
                                  const char *device_name,
                                  rt_uint8_t data_line_width,
                                  void (*enter_ospi_mode)(struct rt_qspi_device *device),
                                  void (*exit_ospi_mode)(struct rt_qspi_device *device));

#ifdef __cplusplus
}
#endif

#endif /* __DRV_OSPI_H__ */
