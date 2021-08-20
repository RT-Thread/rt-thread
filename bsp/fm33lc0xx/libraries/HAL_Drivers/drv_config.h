/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018-10-30     SummerGift        first version
 * 2020-10-14     Dozingfiretruck   Porting for stm32wbxx
 */
 
#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include <board.h>
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "dma_config.h"
#include "uart_config.h"
#include "spi_config.h"
#include "tim_config.h"
#include "pwm_config.h"
#include "adc_config.h"

#ifdef __cplusplus
}
#endif

#endif
