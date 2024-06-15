/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-20     zhangyan     first version
 *
 */

#ifndef __DRV_QSPI_H__
#define __DRV_QSPI_H__

#include "rtdef.h"
#ifdef __cplusplus
extern "C"
{
#endif

rt_err_t phytium_qspi_bus_attach_device(const char *bus_name, const char *device_name);

int rt_hw_qspi_init(void);

#ifdef __cplusplus
}
#endif
#endif // !DRT_QSPI_H

