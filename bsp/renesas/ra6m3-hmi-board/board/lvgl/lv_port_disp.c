/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-24     Rbb666       The first version
 */
#include <lvgl.h>
#include "hal_data.h"

#if DLG_LVGL_USE_GPU_RA6M3
    #include "drv_g2d.h"
#endif

#ifdef PKG_USING_ILI9341
    #include "lcd_ili9341.h"
#else
    #include <ra6m3/lcd_config.h>
#endif

#if LVGL_VERSION_MAJOR < 9
#define COLOR_BUFFER  (LV_HOR_RES_MAX * LV_VER_RES_MAX / 4)
/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;
/*Descriptor of a display driver*/
static lv_disp_drv_t disp_drv;
#endif

static rt_sem_t _SemaphoreVsync = RT_NULL;
static uint8_t lvgl_init_flag = 0;

#if LVGL_VERSION_MAJOR < 9
/*Static or global buffer(s). The second buffer is optional*/
// 0x1FFE0000    0x20040000
lv_color_t buf_1[COLOR_BUFFER];

#if !DLG_LVGL_USE_GPU_RA6M3
static void color_to16_maybe(lv_color16_t *dst, lv_color_t *src)
{
#if (LV_COLOR_DEPTH == 16)
    dst->full = src->full;
#else
    dst->ch.blue = src->ch.blue;
    dst->ch.green = src->ch.green;
    dst->ch.red = src->ch.red;
#endif
}
#endif
#endif

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
#ifdef PKG_USING_ILI9341
    lcd_fill_array_spi(area->x1, area->y1, area->x2, area->y2, color_p);
#elif DLG_LVGL_USE_GPU_RA6M3
    lv_port_gpu_blit(area->x1, area->y1, color_p, area);
#else
    int x1, x2, y1, y2;

    x1 = area->x1;
    x2 = area->x2;
    y1 = area->y1;
    y2 = area->y2;

    /*Return if the area is out the screen*/
    if (x2 < 0)
        return;
    if (y2 < 0)
        return;
    if (x1 > info.width - 1)
        return;
    if (y1 > info.height - 1)
        return;

    /*Truncate the area to the screen*/
    int32_t act_x1 = x1 < 0 ? 0 : x1;
    int32_t act_y1 = y1 < 0 ? 0 : y1;
    int32_t act_x2 = x2 > info.width - 1 ? info.width - 1 : x2;
    int32_t act_y2 = y2 > info.height - 1 ? info.height - 1 : y2;

    uint32_t x;
    uint32_t y;
    long int location = 0;

    /* color_p is a buffer pointer; the buffer is provided by LVGL */
    lv_color16_t *fbp16 = (lv_color16_t *)info.framebuffer;

    for (y = act_y1; y <= act_y2; y++)
    {
        for (x = act_x1; x <= act_x2; x++)
        {
            location = (x) + (y) * info.width;
            color_to16_maybe(&fbp16[location], color_p);
            color_p++;
        }

        color_p += x2 - act_x2;
    }
#endif
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
                         (display_frame_layer_t) 0);
}
#endif

void lv_port_disp_init(void)
{
    _SemaphoreVsync = rt_sem_create("lvgl_sem", 1, RT_IPC_FLAG_PRIO);

    if (RT_NULL == _SemaphoreVsync)
    {
        rt_kprintf("lvgl semaphore create failed\r\n");
        RT_ASSERT(0);
    }
#ifdef PKG_USING_ILI9341
    spi_lcd_init(20);
#endif
#if LVGL_VERSION_MAJOR < 9
    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, COLOR_BUFFER);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

#if DLG_LVGL_USE_GPU_RA6M3
    /* Initialize GPU module */
    G2d_Drv_HWInit();
#endif /* LV_PORT_DISP_GPU_EN */

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

    lvgl_init_flag = 1;
#endif
}
