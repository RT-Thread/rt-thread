/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <stdio.h>

int main(void)
{
    rt_kprintf("Hello RISC-V\n");

#ifdef BSP_USING_LCD
    extern int rt_hw_lcd_init(void);
    rt_hw_lcd_init();
#endif // BSP_USING_LCD

    return 0;
}
