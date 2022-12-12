/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2011-03-04     lgnq         add board.h to FM3 bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#if   defined MB9B610S
#   include <mb9b610s.h>
#elif defined MB9B610T
#   include <mb9b610t.h>
#else
#   warning "you must define CPU type. e.g: MB9B610S or MB9B610T"
#   warning "define MB9B610S default"
#   define MB9B610S /* default: MB9B610S */
#   include <mb9b610s.h>
#endif

#include "serial.h"

//Internal SRAM memory size[Kbytes] <8-64>
//product  MB9BFx16S/T  MB9BFx17S/T  MB9BFx18S/T
//FLASH  :    512           768          1024
//SRAM0  :    32            48           64
//SRAM1  :    32            48           64
#define FM3_SRAM_SIZE         128
#define FM3_SRAM_END          (0x1FFF0000 + FM3_SRAM_SIZE * 1024)

/* RT_USING_UART */
#define RT_USING_UART0
//#define RT_USING_UART2
//#define RT_USING_UART4
#define RT_UART_RX_BUFFER_SIZE        64

void rt_hw_board_init(void);
rt_uint32_t rt_hw_tick_get_millisecond(void);
rt_uint32_t rt_hw_tick_get_microsecond(void);

#endif
