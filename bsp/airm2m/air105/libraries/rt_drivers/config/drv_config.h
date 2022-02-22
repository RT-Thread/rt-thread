/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-07-29     KyleChan          first version
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __AIR105_BSP__
#include "air105/spi_config.h"
#include "air105/uart_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif/* __DRV_CONFIG_H__ */
