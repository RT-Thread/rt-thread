/*
 * Copyright (c) 2020-2022, CQ 100ask Development Team
 *
 * Change Logs:
 *   Date           Author          Notes
 * 2022-05-29        Alen       first version
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <board.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SOC_SERIES_MM32F3277)
#include "mm32f3277g8p/dma_config.h"
#include "mm32f3277g8p/uart_config.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
