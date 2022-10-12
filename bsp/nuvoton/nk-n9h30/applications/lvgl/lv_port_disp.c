/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-17     Wayne        The first version
 */
#include <lvgl.h>
#include "nu_2d.h"
#include "mmu.h"

#if (LV_USE_GPU_N9H30_GE2D && LV_VERSION_CHECK(8, 2, 0))
    #include "lv_gpu_n9h30_ge2d.h"
#endif

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

static void *buf3_next = RT_NULL;

static uint32_t u32FirstFlush = 0;

static void nu_antitearing(lv_disp_draw_buf_t *draw_buf, lv_color_t *color_p)
{
    if (buf3_next)
    {
        /* vsync-none: Use triple screen-sized buffers. */
        if (draw_buf->buf1 == color_p)
            draw_buf->buf1 = buf3_next;
        else
            draw_buf->buf2 = buf3_next;

        draw_buf->buf_act = buf3_next;
        buf3_next = color_p;
    }
    else
    {
        /* vsync-after: Use ping-pong screen-sized buffers only.*/
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_WAIT_VSYNC, RT_NULL);
    }
}

static void nu_flush_full_refresh(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    if (IS_CACHEABLE_VRAM(color_p))
        mmu_clean_dcache((uint32_t)color_p, disp_drv->draw_buf->size * sizeof(lv_color_t));

    /* Use PANDISPLAY without H/W copying */
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, color_p);

    nu_antitearing(disp_drv->draw_buf, color_p);

    if (!u32FirstFlush)
    {
        /* Enable backlight at first flushing. */
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_POWERON, RT_NULL);
        u32FirstFlush = 1;
    }

    lv_disp_flush_ready(disp_drv);
}

static void nu_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
#if (LV_USE_GPU_N9H30_GE2D==1)
    lv_draw_sw_blend_dsc_t blend_flush = {0};
    lv_draw_ctx_t draw_flush = {0};
    lv_area_t flush_area = {0, 0, info.width - 1, info.height - 1 };

    blend_flush.blend_area = area;
    blend_flush.src_buf    = color_p;
    blend_flush.mask_buf   = NULL;
    blend_flush.opa        = LV_OPA_MAX;
    blend_flush.blend_mode = LV_BLEND_MODE_NORMAL;

    draw_flush.buf         = info.framebuffer;
    draw_flush.clip_area   = &flush_area;
    draw_flush.buf_area    = &flush_area;

    lv_draw_n9h30_ge2d_blend(&draw_flush, (const lv_draw_sw_blend_dsc_t *)&blend_flush);

#else
    int32_t flush_area_w = lv_area_get_width(area);
    int32_t flush_area_h = lv_area_get_height(area);

    //if ( flush_area_w&0x3 != 0 )
    //    rt_kprintf("[%s %08x] %dx%d %d %d\n", __func__, color_p, flush_area_w, flush_area_h, area->x1, area->y1 );

    /* Update dirty region. */
    // Enter GE2D ->
    ge2dInit(sizeof(lv_color_t) * 8, info.width, info.height, (void *)info.framebuffer);
    ge2dBitblt_SetAlphaMode(-1, 0, 0);
    ge2dBitblt_SetDrawMode(-1, 0, 0);

    ge2dSpriteBlt_Screen(area->x1, area->y1, flush_area_w, flush_area_h, (void *)color_p);
    // -> Leave GE2D
#endif

    if (!u32FirstFlush)
    {
        /* Enable backlight at first flushing. */
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_POWERON, RT_NULL);
        u32FirstFlush = 1;
    }

    lv_disp_flush_ready(disp_drv);
}

#if LV_VERSION_EQUAL(8, 1, 0)
static void nu_fill_cb(struct _lv_disp_drv_t *disp_drv, lv_color_t *dest_buf, lv_coord_t dest_width,
                       const lv_area_t *fill_area, lv_color_t color)
{
    int32_t fill_area_w = lv_area_get_width(fill_area);
    int32_t fill_area_h = lv_area_get_height(fill_area);


    if (lv_area_get_size(fill_area) < 3600)
    {
        /*Software filling*/
        int y;
        lv_color_t *disp_buf_first = dest_buf + dest_width * fill_area->y1 + fill_area->x1;
        for (y = 0; y < fill_area_h; y++)
        {
            lv_color_fill(disp_buf_first, color, fill_area_w);
            disp_buf_first += dest_width;
        }
    }
    else
    {
        //rt_kprintf("[blend_fill %d %08x] %dx%d %d %d\n", lv_area_get_size(fill_area), dest_buf, fill_area_w, fill_area_h, fill_area->x1, fill_area->y1 );

        if (IS_CACHEABLE_VRAM(dest_buf))
            mmu_clean_invalidated_dcache((uint32_t)dest_buf, sizeof(lv_color_t) * (dest_width * fill_area_h + fill_area_w));

        /*Hardware filling*/
        // Enter GE2D ->
        ge2dInit(sizeof(lv_color_t) * 8, fill_area_w, fill_area_h, (void *)dest_buf);

        ge2dClip_SetClip(fill_area->x1, fill_area->y1, fill_area->x2, fill_area->y2);

        if (sizeof(lv_color_t) == 4)
            ge2dFill_Solid(fill_area->x1, fill_area->y1, fill_area_w, fill_area_h, color.full);
        else if (sizeof(lv_color_t) == 2)
            ge2dFill_Solid_RGB565(fill_area->x1, fill_area->y1, fill_area_w, fill_area_h, color.full);

        ge2dClip_SetClip(-1, 0, 0, 0);
        // -> Leave GE2D
    }
}
#endif

void nu_perf_monitor(struct _lv_disp_drv_t *disp_drv, uint32_t time, uint32_t px)
{
    rt_kprintf("Elapsed: %dms, Pixel: %d, Bytes:%d, %d%\n", time, px, px * sizeof(lv_color_t), px * 100 / disp_drv->draw_buf->size);
}

void lv_port_disp_init(void)
{
    rt_err_t result;
    void *buf1 = RT_NULL;
    void *buf2 = RT_NULL;
    uint32_t u32FBSize;

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

    /* Disable backlight at startup. */
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_POWEROFF, RT_NULL);

    RT_ASSERT(info.bits_per_pixel == 8 || info.bits_per_pixel == 16 ||
              info.bits_per_pixel == 24 || info.bits_per_pixel == 32);

    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = info.width;
    disp_drv.ver_res = info.height;
    u32FBSize = info.height * info.width * (info.bits_per_pixel / 8);

#if (LV_USE_ANTI_TEARING==1)
    disp_drv.full_refresh = 1;
#endif

    if (disp_drv.full_refresh)
    {
#if (LV_USE_GPU_N9H30_GE2D==1)
        buf1 = (void *)info.framebuffer;  // Use Non-cacheable VRAM
#else
        buf1 = (void *)((uint32_t)info.framebuffer & ~BIT31); // Use Cacheable VRAM
#endif
        buf2 = (void *)((uint32_t)buf1 + u32FBSize);
        buf3_next = (void *)((uint32_t)buf2 + u32FBSize);
        rt_kprintf("LVGL: Use triple screen-sized buffers(full_refresh) - buf1@%08x, buf2@%08x, buf3_next@%08x\n", buf1, buf2, buf3_next);

        disp_drv.flush_cb = nu_flush_full_refresh;
    }
    else
    {
        buf1 = (void *)(((uint32_t)info.framebuffer) + u32FBSize);
        buf2 = (void *)((uint32_t)buf1 + u32FBSize);
        rt_kprintf("LVGL: Use two screen-sized buffers - buf1@%08x, buf2@%08x\n", buf1, buf2);
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, info.framebuffer);

        disp_drv.flush_cb = nu_flush;
    }

    /*Initialize `disp_buf` with the buffer(s).*/
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, info.width * info.height);

    result = rt_device_open(lcd_device, 0);
    if (result != RT_EOK)
    {
        LOG_E("error!");
        return;
    }

    /*Set a display buffer*/
    disp_drv.draw_buf = &disp_buf;

#if LV_VERSION_EQUAL(8, 1, 0)
    /*Fill a memory with a color (GPU only)*/
    disp_drv.gpu_fill_cb = nu_fill_cb;
#endif

#if (LV_USE_GPU_N9H30_GE2D && LV_VERSION_CHECK(8, 2, 0))
    disp_drv.draw_ctx_init = lv_draw_n9h30_ge2d_ctx_init;
    disp_drv.draw_ctx_deinit = lv_draw_n9h30_ge2d_ctx_init;
    disp_drv.draw_ctx_size = sizeof(lv_draw_n9h30_ge2d_ctx_t);
#endif

    /*Called after every refresh cycle to tell the rendering and flushing time + the number of flushed pixels*/
    //disp_drv.monitor_cb = nu_perf_monitor;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}
