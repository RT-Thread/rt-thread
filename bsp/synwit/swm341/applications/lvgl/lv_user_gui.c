/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-01-28     Rudy Lo       The first version
 */

#include <lvgl.h>

void lv_user_gui_init(void)
{
extern void lv_demo_widgets(void);
    lv_demo_widgets();
}
