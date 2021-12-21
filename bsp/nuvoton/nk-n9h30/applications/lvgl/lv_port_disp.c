/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-17     Wayne        The first version
 */
#include <lvgl.h>

#define LOG_TAG             "lvgl.disp"
#define DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;
static rt_device_t lcd_device = 0;
static struct rt_device_graphic_info info;
static lv_disp_drv_t disp_drv;  /*Descriptor of a display driver*/

extern void ge2dInit(int bpp, int width, int height, void *destination);
extern void ge2dSpriteBlt_Screen(int destx, int desty, int sprite_width, int sprite_height, void *buf);
extern int ge2dBitblt_SetAlphaMode(int opt, int ks, int kd);
extern void ge2dSpriteBltx_Screen(int x, int y, int sprite_sx, int sprite_sy, int width, int height, int sprite_width, int sprite_height, void *buf);
extern void ge2dClip_SetClip(int x1, int y1, int x2, int y2);
extern void ge2dFill_Solid_RGB565(int dx, int dy, int width, int height, int color);
extern void ge2dFill_Solid(int dx, int dy, int width, int height, int color);

static void lcd_fb_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    /* Use ping-pong buffer updating without memory-copy. */
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_RECT_UPDATE, color_p);

    lv_disp_flush_ready(disp_drv);
}

void ge2d_fill_cb(struct _lv_disp_drv_t *disp_drv, lv_color_t *dest_buf, lv_coord_t dest_width,
                  const lv_area_t *fill_area, lv_color_t color)
{
    int32_t act_x1 = fill_area->x1 < 0 ? 0 : fill_area->x1;
    int32_t act_y1 = fill_area->y1 < 0 ? 0 : fill_area->y1;
    int32_t act_x2 = fill_area->x2 > info.width - 1 ? info.width - 1 : fill_area->x2;
    int32_t act_y2 = fill_area->y2 > info.height - 1 ? info.height - 1 : fill_area->y2;
    int32_t fill_area_w = act_x2 - act_x1 + 1;
    int32_t fill_area_h = act_y2 - act_y1 + 1;

    // Enter GE2D ->
    ge2dInit(sizeof(lv_color_t) * 8, info.width, info.height, (void *)dest_buf);
    ge2dClip_SetClip(act_x1, act_y1, act_x2, act_y2);
    if (sizeof(lv_color_t) == 4)
    {
        ge2dFill_Solid(act_x1, act_y1, fill_area_w, fill_area_h, color.full);
    }
    else if (sizeof(lv_color_t) == 2)
    {
        ge2dFill_Solid_RGB565(act_x1, act_y1, fill_area_w, fill_area_h, color.full);
    }
    ge2dClip_SetClip(-1, 0, 0, 0);
    // -> Leave GE2D
}

void lcd_perf_monitor(struct _lv_disp_drv_t *disp_drv, uint32_t time, uint32_t px)
{
    rt_kprintf("Elapsed: %dms, Pixel: %d, Bytes:%d\n", time, px, px * sizeof(lv_color_t));
}

void lv_port_disp_init(void)
{
    rt_err_t result;
    void *buf_1 = RT_NULL;
    void *buf_2 = RT_NULL;

    lcd_device = rt_device_find("lcd");
    if (lcd_device == 0)
    {
        LOG_E("error!");
        return;
    }

    /* get framebuffer address */
    result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK)
    {
        LOG_E("error!");
        /* get device information failed */
        return;
    }

    RT_ASSERT(info.bits_per_pixel == 8 || info.bits_per_pixel == 16 ||
              info.bits_per_pixel == 24 || info.bits_per_pixel == 32);

    buf_1 = (void *)info.framebuffer;
    buf_2 = (void *)((uint32_t)buf_1 + info.height * info.width * info.bits_per_pixel / 8);
    rt_kprintf("LVGL: Use two buffers - buf_1@%08x, buf_2@%08x\n", buf_1, buf_2);

    /*Initialize `disp_buf` with the buffer(s).*/
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, info.width * info.height);

    result = rt_device_open(lcd_device, 0);
    if (result != RT_EOK)
    {
        LOG_E("error!");
        return;
    }

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = info.width;
    disp_drv.ver_res = info.height;
    disp_drv.full_refresh = 1;

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

    /*Write the internal buffer (draw_buf) to the display*/
    disp_drv.flush_cb = lcd_fb_flush;

    /*Fill a memory with a color (GPU only)*/
    disp_drv.gpu_fill_cb = ge2d_fill_cb;

    /* Called after every refresh cycle to tell the rendering and flushing time + the number of flushed pixels */
    //disp_drv.monitor_cb = lcd_perf_monitor;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
