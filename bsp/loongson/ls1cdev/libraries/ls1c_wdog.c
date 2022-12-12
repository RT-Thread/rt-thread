/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     sundm75       first version
 */

#include "ls1c.h"
#include "ls1c_wdog.h"

/*
系统先配置看门狗使能位 WDT_EN;
然后配置看门狗计数器的初始值 WDT_TIMER;
当设置 WDT_SET 后，计数器开始减计数;
当还没有减到 0 时，重置看门狗计数器，系统不会重启;
当看门狗计数器减到 0 时，则系统重启。
*/

static unsigned int WDT_timer = 0;

/* 暂时为空 */
unsigned int Wdog_Init(void)              
{
    return 0;
}

/* 配置看门狗使能寄存器(WDT_EN) */
unsigned int Wdog_Enable(void)       
{
    unsigned int ctrl;
    ctrl = (WDT_EN);
    ctrl |= 0x01;

    WDT_EN = ctrl;
    return 0;
}

/* 配置看门狗失能寄存器(WDT_EN) */
unsigned int Wdog_Disable(void)           
{
    unsigned int ctrl;
    ctrl = (WDT_EN);
    ctrl &= ~0x01;
    WDT_EN = ctrl;
    return 0;
}

/* 配置看门狗设置寄存器 (WDT_SET) */
unsigned int Wdog_Set(void)               
{
    unsigned int ctrl;
    ctrl = (WDT_SET);
    ctrl |= 0x01;
    WDT_SET = ctrl;
    return 0;
}

/* 配置看门狗设置寄存器 (WDT_SET) */
unsigned int Wdog_Reset(void)             
{
    unsigned int ctrl;
    ctrl = (WDT_SET);
    ctrl &= ~0x01;
    WDT_SET = ctrl;
    return 0;
}

/* 获得看门狗计数器(WDT_timer) 的值*/
unsigned int Wdog_GetValue(void)          
{
    unsigned int cnt;
    cnt = (WDT_TIMER);
    return cnt;
}

/* 配置看门狗计数器(WDT_timer)的值*/
unsigned int Wdog_LoadValue(unsigned int cnt)    
{
    WDT_TIMER = cnt;
    WDT_timer = cnt;
    return 0;
}

/* 获得看门狗计数器设定值 */
unsigned int Wdog_GetPreValue(void)    
{
    return WDT_timer;
}
