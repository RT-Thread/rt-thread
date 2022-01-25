/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-11     Carl      the first version
 */

#ifndef __DRT_QSPI_H__
#define __DRT_QSPI_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define FT2004_QSPI_NAME "qspi"

    rt_err_t ft2004_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)());

#ifdef __cplusplus
}
#endif

#endif // !DRT_QSPI_H
