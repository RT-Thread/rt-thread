/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-05-13     Meco Man      First version
 */

#include <rtconfig.h>
#include <lvgl.h>

void lv_user_gui_init(void)
{
#ifdef PKG_USING_GUI_GUIDER_DEMO
    extern void gui_guider_setup(void);
    gui_guider_setup();
#endif
}
