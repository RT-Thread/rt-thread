/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2010-02-04     Magicoe      add board.h to LPC176x bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "LPC177x_8x.h"

// <RDTConfigurator URL="http://www.rt-thread.com/eclipse">

// <integer name="LPC_EXT_SDRAM" description="Enable External SDRAM memory" default="0" />
#define LPC_EXT_SDRAM          1
// <integer name="LPC_EXT_SDRAM" description="Begin Address of External SDRAM" default="0xA0000000" />
#define LPC_EXT_SDRAM_BEGIN    0xA0000000
// <integer name="LPC_EXT_SDRAM_END" description="End Address of External SDRAM" default="0xA4000000" />
#define LPC_EXT_SDRAM_END      0xA4000000

// <bool name="RT_USING_UART0" description="Using UART0" default="true" />
#define RT_USING_UART0
// <bool name="RT_USING_UART1" description="Using UART1" default="true" />
//#define RT_USING_UART1
// <bool name="RT_USING_UART2" description="Using UART2" default="true" />
//#define RT_USING_UART2

// <string name="RT_CONSOLE_DEVICE_NAME" description="The device name for console" default="uart" />
#define RT_CONSOLE_DEVICE_NAME  "uart0"

// </RDTConfigurator>

#define FINSH_DEVICE_NAME   RT_CONSOLE_DEVICE_NAME
void rt_hw_board_init(void);

#endif
