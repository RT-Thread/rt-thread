/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-31     Bernard      first implementation
 * 2018-09-02     xuzhuoyi     modify for TMS320F28379D version
 * 2022-08-21     yuqi         modify the entry function
 */

#include <stdint.h>
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
void assert_failed(uint16_t* file, uint32_t line)
{
    rt_kprintf("\n\r Wrong parameter value detected on\r\n");
    rt_kprintf("       file  %s\r\n", file);
    rt_kprintf("       line  %d\r\n", line);

    while (1) ;
}

int main(void)
{
    extern int rtthread_startup();

    /* startup RT-Thread RTOS */
    rtthread_startup();
    /* never reach here*/
    return 0;
}

int rt_main(void)
{
//#ifdef RT_USING_FINSH
//    /* init finsh */
//    extern int finsh_system_init(void);
//    finsh_system_init();
//#endif

    while(1)
    {

    }
}

/*@}*/
