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
#include "fqspi_flash.h"
#include "fqspi_hw.h"
#ifdef __cplusplus
extern "C"
{
#endif
typedef struct
{
    rt_uint32_t fqspi_id;
    const char *name;
    rt_uint32_t init; /* 0 is init already */
    FQspiCtrl fqspi;
    struct rt_spi_bus qspi_bus;
} phytium_qspi_bus;

rt_err_t phytium_qspi_bus_attach_device(const char *bus_name, const char *device_name);

int rt_hw_qspi_init(void);

#ifdef __cplusplus
}
#endif
#endif // !DRT_QSPI_H

