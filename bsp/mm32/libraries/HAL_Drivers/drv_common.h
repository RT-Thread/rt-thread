/*
 * Copyright (c) 2020-2022, CQ 100ask Development Team
 *
 * Change Logs:
 *   Date           Author          Notes
 * 2022-05-29        Alen       first version
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <rtthread.h>
#include <rthw.h>

#include <board.h>

#include <hal_common.h>
#include <hal_dma.h>
#include <hal_rcc.h>

#ifdef RT_USING_PIN
#include <hal_exti.h>
#include <hal_syscfg.h>
#include <hal_gpio.h>
#endif

#ifdef RT_USING_SERIAL
#include <hal_uart.h>
#endif

#ifdef RT_USING_SPI
#include <hal_spi.h>
#endif

#ifdef RT_USING_DEVICE
#include <rtdevice.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void _Error_Handler(char *s, int num);

#ifndef Error_Handler
#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#endif

#define DMA_NOT_AVAILABLE ((DMA_INSTANCE_TYPE *)0xFFFFFFFFU)

#ifdef __cplusplus
}
#endif

#endif
