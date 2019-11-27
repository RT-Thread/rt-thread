/*
 * Copyright (c) 2012-2019, Mobvoi BSP Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-27     fanming      first version
 */

#ifndef __DRV_OSPI_H_
#define __DRV_OSPI_H_
#include <rtthread.h>

rt_err_t stm32_ospi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin, rt_uint8_t data_line_width,  void (*enter_qspi_mode)(),  void (*exit_qspi_mode)());

#endif
