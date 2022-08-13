/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     The first version
 */
#include <lvgl.h>
#include <win32drv.h>

#define DBG_TAG    "LVGL.port"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

void lv_port_disp_init(void)
{
    /* initialize win32 driver */
    if (!lv_win32_init(GetModuleHandleW(NULL), SW_SHOW, BSP_LCD_WIDTH, BSP_LCD_HEIGHT, NULL))
    {
        LOG_E("lv_win32_init is failure!");
        return;
    }
    lv_win32_add_all_input_devices_to_group(NULL);
}
