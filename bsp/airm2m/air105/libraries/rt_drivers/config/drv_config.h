/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */


#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOC_AIR105
#include "air105/spi_config.h"
#include "air105/uart_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif/* __DRV_CONFIG_H__ */
