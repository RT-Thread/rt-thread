/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-24     Rbb666       The first version
 */
#include <lvgl.h>
#include "hal_data.h"

#if LV_USE_GPU_RA6M3_G2D
#include "lv_gpu_d2_ra6m3.h"
#endif

#include <ra6m3/lcd_config.h>

#if LVGL_VERSION_MAJOR < 9
/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;
/*Descriptor of a display driver*/
static lv_disp_drv_t disp_drv;
#endif

static rt_sem_t _SemaphoreVsync = RT_NULL;
static uint8_t lvgl_init_flag = 0;

void DisplayVsyncCallback(display_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (DISPLAY_EVENT_LINE_DETECTION == p_args->event)
    {
        if (lvgl_init_flag != 0)
            rt_sem_release(_SemaphoreVsync);
    }
    rt_interrupt_leave();
}

#if LVGL_VERSION_MAJOR < 9
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    rt_sem_take(_SemaphoreVsync, RT_WAITING_FOREVER);

    R_GLCDC_BufferChange(&g_display0_ctrl,
                         (uint8_t *) color_p,
                         (display_frame_layer_t) DISPLAY_FRAME_LAYER_1);
    lv_disp_flush_ready(disp_drv);
}
#else
static void vsync_wait_cb(lv_display_t *display)
{
    if (!lv_display_flush_is_last(display)) return;

    //
    // If Vsync semaphore has already been set, clear it then wait to avoid tearing
    //
    rt_sem_take(_SemaphoreVsync, RT_WAITING_FOREVER);
}

static void disp_flush(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    if (!lv_display_flush_is_last(display)) return;

    R_GLCDC_BufferChange(&g_display0_ctrl,
                         (uint8_t *) px_map,
                         (display_frame_layer_t) DISPLAY_FRAME_LAYER_1);
}
#endif /* LVGL_VERSION_MAJOR < 9 */

void lv_port_disp_init(void)
{
    _SemaphoreVsync = rt_sem_create("lvgl_sem", 1, RT_IPC_FLAG_PRIO);

    if (RT_NULL == _SemaphoreVsync)
    {
        rt_kprintf("lvgl semaphore create failed\r\n");
        RT_ASSERT(0);
    }
#if LVGL_VERSION_MAJOR < 9
    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, &fb_background[0][0], &fb_background[1][0], sizeof(fb_background[0]));

    /*Basic initialization*/
    lv_disp_drv_init(&disp_drv);

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
#else
    /*------------------------------------
     * Create a display and set a flush_cb
     * -----------------------------------*/
    lv_display_t *disp = lv_display_create(LV_HOR_RES_MAX, LV_VER_RES_MAX);
    lv_display_set_flush_cb(disp, disp_flush);
    lv_display_set_flush_wait_cb(disp, vsync_wait_cb);
    lv_display_set_buffers(disp, &fb_background[0][0], &fb_background[1][0], sizeof(fb_background[0]), LV_DISPLAY_RENDER_MODE_DIRECT);
#endif
    lvgl_init_flag = 1;
}
