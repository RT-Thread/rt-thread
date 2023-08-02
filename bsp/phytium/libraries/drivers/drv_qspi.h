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

#ifndef __DRT_QSPI_H__
#define __DRT_QSPI_H__

#include "rtconfig.h"

#ifdef RT_USING_QSPI
#include <rtthread.h>
#include "rtdevice.h"
#include "fqspi_flash.h"
#define PHYTIUM_QSPI_NAME "qspi"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    rt_uint32_t fqspi_id;
    rt_uint32_t init; /* 0 is init already */
    FQspiCtrl fqspi;
    struct rt_spi_bus qspi_bus;
} phytium_qspi_bus;

rt_err_t phytium_qspi_bus_attach_device(const char *bus_name, const char *device_name);

#ifdef __cplusplus
}
#endif
#endif
#endif // !DRT_QSPI_H

