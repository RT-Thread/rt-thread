/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-06     whik         first version
 */
#include "config.h"

/* hardware initialization */
void boardInit(void)
{
    /* disable watchdog timer */
    SYSREG->WDOG_CR = 0;
}
INIT_BOARD_EXPORT(boardInit);

/* custom finish command */
extern uint32_t SystemCoreClock;
void sayHello(void)
{
     rt_kprintf("Hello RT-Thread! By Microsemi SmartFusion2 Family FPGA-M2S010.\r\n");
     rt_kprintf("MSS System Core Clock: %d Hz.\r\n", SystemCoreClock);
}
MSH_CMD_EXPORT(sayHello, "say hello to console");
