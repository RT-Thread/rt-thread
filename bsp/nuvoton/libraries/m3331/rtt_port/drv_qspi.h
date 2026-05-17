/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_QSPI_H__
#define __DRV_QSPI_H__
#include "rtdevice.h"

rt_err_t nu_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)());
#endif /* __DRV_QSPI_H__ */