/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __RESOURCE_MAP_H__
#define __RESOURCE_MAP_H__
#include "io_map.h"
#define CORE_TICK_TIM 7
#define CORE_TICK_IRQ TIM0_7_IRQn
#define CORE_TICK_1US   (48)
#define CORE_TICK_1MS   (48000)
#define CORE_TICK_1S        (48000000)
#define CORE_TICK_IRQ_LEVEL 1
#define HWTIMER_IRQ_LEVEL   0

#define SYS_TIMER_TIM 6
#define SYS_TIMER_IRQ TIM0_6_IRQn
#define SYS_TIMER_1US   (48)
#define SYS_TIMER_1MS   (48000)
#define SYS_TIMER_1S    (48000000)
#define SYS_TIMER_IRQ_LEVEL 6

#define DBG_UART_ID UART_ID0
#define DBG_UART_BR 1500000
#define BL_UART_BR 3000000
#define DBG_UART_IRQ_LEVEL 6
#define DBG_UART_TX_DMA_STREAM  DMA1_STREAM_2
#define DBG_UART_RX_DMA_STREAM  DMA1_STREAM_2
#define DBG_UART_TX_DMA_CHANNEL SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART0_TX
#define DBG_UART_RX_DMA_CHANNEL SYSCTRL_PHER_CTRL_DMA_CHx_IF_UART0_RX

#define EFLASH_QSPI_TX_DMA_STREAM DMA1_STREAM_1
#define DAC_TX_DMA_STREAM       DMA1_STREAM_0
#define DCMI_RX_DMA_STREAM      DMA1_STREAM_3
#define FLASH_SPI_TX_DMA_STREAM DMA1_STREAM_4
#define FLASH_SPI_RX_DMA_STREAM DMA1_STREAM_5
#define LCD_SPI_TX_DMA_STREAM   DMA1_STREAM_6
#define LCD_SPI_RX_DMA_STREAM   DMA1_STREAM_7

#define LUATOS_TASK_PRO     (configMAX_PRIORITIES - 2)
#define HW_TASK_PRO     (configMAX_PRIORITIES - 1)
#define SERVICE_TASK_PRO        (configMAX_PRIORITIES - 4)
#endif
