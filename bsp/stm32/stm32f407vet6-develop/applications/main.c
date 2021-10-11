/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "board_def_map.h"

#define DBG_TAG     "MAIN"
#define DBG_LVL     DBG_LOG
#include <rtdbg.h>


int main(void)
{
	//  int main_ret = 0;

	  LOG_D("BUILD=%s\n", BUILD);
    while (1)
    {
			//	LOG_D("hello rt-thread!\n");
			
    }
 //   return main_ret;
}
