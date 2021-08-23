/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-23     AisinoChip   the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"

/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/

void assert_failed(uint8_t *file, uint32_t line)
{
    rt_kprintf("\n\r Wrong parameter value detected on\r\n");
    rt_kprintf("       file  %s\r\n", file);
    rt_kprintf("       line  %d\r\n", line);

    while (1) ;
}

int main(void)
{
    rt_hw_led_init();
    while(1)
    {
        rt_hw_led_on(0);
        rt_thread_delay(RT_TICK_PER_SECOND/2);
        rt_hw_led_off(0);
        rt_thread_delay(RT_TICK_PER_SECOND/2);
    }
}

