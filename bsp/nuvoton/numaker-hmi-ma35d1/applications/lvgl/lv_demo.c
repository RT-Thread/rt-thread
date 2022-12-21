/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-6-1       Wayne         First version
 */

#include <lvgl.h>

void lv_user_gui_init(void)
{
    /* display demo; you may replace with your LVGL application at here and disable related definitions. */

#if LV_USE_DEMO_BENCHMARK
    extern void lv_demo_benchmark(void);
    lv_demo_benchmark();
#endif

#if LV_USE_DEMO_WIDGETS
    extern void lv_demo_widgets(void);
    lv_demo_widgets();
#endif

#if LV_USE_DEMO_MUSIC || LV_USE_DEMO_RTT_MUSIC
    extern void lv_demo_music(void);
    lv_demo_music();
#endif

}
