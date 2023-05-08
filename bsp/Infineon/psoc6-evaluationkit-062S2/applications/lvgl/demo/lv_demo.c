/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-17     Meco Man      First version
 * 2022-05-10     Meco Man      improve rt-thread initialization process
 */

void lv_user_gui_init(void)
{
    /* display demo; you may replace with your LVGL application at here */
    extern void lv_demo_music(void);
    lv_demo_music();
}
