/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-04     RTT          add LVGL port for the MIPI DSI LCD
 * 2026-09-08     CYFS         port the board demo with internal camera rendering and IPA updates
 */

#include <rtconfig.h>

#ifdef PKG_USING_LVGL

#include <lvgl.h>
#include <rtdevice.h>
#include <board.h>

#include "gd32h77x_78x_ipa.h"

#define DBG_TAG                         "lvgl.disp"
#define DBG_LVL                         DBG_INFO
#include <rtdbg.h>

#define LCD_DEVICE_NAME                 "lcd"
#define TOUCH_DEVICE_NAME               "gt911"
#define TOUCH_POINT_COUNT               5U

#define LCD_BYTES_PER_PIXEL             2U

#if defined(BSP_USING_OV7670)
#define LVGL_DISPLAY_WIDTH              LV_HOR_RES_MAX
#define LVGL_DISPLAY_HEIGHT             LV_VER_RES_MAX
#define LVGL_USE_DIRECT_FRAMEBUFFER     0
#define LVGL_USE_IPA_FRAMEBUFFER        1
#define LCD_DRAW_BUFFER_LINES           32U
#elif LV_USE_DEMO_SMARTWATCH && !defined(BSP_USING_LVGL_BOARD_DEMO)
#define LVGL_DISPLAY_WIDTH              384U
#define LVGL_DISPLAY_HEIGHT             384U
#define LVGL_USE_DIRECT_FRAMEBUFFER     0
#else
#define LVGL_DISPLAY_WIDTH              LV_HOR_RES_MAX
#define LVGL_DISPLAY_HEIGHT             LV_VER_RES_MAX
#define LVGL_USE_DIRECT_FRAMEBUFFER     0
#endif

#ifndef LVGL_USE_IPA_FRAMEBUFFER
#define LVGL_USE_IPA_FRAMEBUFFER        0
#define LCD_DRAW_BUFFER_LINES           150U
#endif

#if !LVGL_USE_DIRECT_FRAMEBUFFER
#define LCD_DRAW_BUFFER_SIZE            (LVGL_DISPLAY_WIDTH * LCD_DRAW_BUFFER_LINES * LCD_BYTES_PER_PIXEL)
#endif

static rt_device_t lcd_device;
static struct rt_device_graphic_info lcd_info;
static lv_display_t *lvgl_display;
#if !LVGL_USE_DIRECT_FRAMEBUFFER
rt_align(32) static uint8_t lcd_draw_buffer_1[LCD_DRAW_BUFFER_SIZE];
#if !LVGL_USE_IPA_FRAMEBUFFER
rt_align(32) static uint8_t lcd_draw_buffer_2[LCD_DRAW_BUFFER_SIZE];
#endif
#endif
static rt_uint16_t lcd_viewport_x;
static rt_uint16_t lcd_viewport_y;
#if !LVGL_USE_DIRECT_FRAMEBUFFER && !LVGL_USE_IPA_FRAMEBUFFER
static volatile lv_display_t *g_flushing_display;
#endif
static rt_bool_t display_ready;
#if LVGL_USE_DIRECT_FRAMEBUFFER
static rt_bool_t flush_error_reported;
#endif

#if LVGL_USE_IPA_FRAMEBUFFER
static rt_uint8_t *lcd_scanout_framebuffer;
static rt_uint8_t *lcd_render_framebuffer;
static lv_area_t lcd_pending_area;
static rt_bool_t lcd_pending_valid;
static rt_bool_t lcd_pipeline_faulted;
static rt_uint32_t lcd_ipa_error_flags;
#endif

#ifdef BSP_USING_TOUCH_GT911
int rt_hw_gt911_port_init(void);

static rt_device_t touch_device;
static lv_coord_t touch_x;
static lv_coord_t touch_y;
static rt_bool_t touch_pressed;
#endif

#if LVGL_USE_IPA_FRAMEBUFFER
static void lcd_ipa_init(void)
{
    rcu_periph_clock_enable(RCU_IPA);
    NVIC_DisableIRQ(IPA_IRQn);
    ipa_deinit();
    ipa_interval_clock_num_config(255U);
    ipa_inter_timer_config(IPA_INTER_TIMER_ENABLE);
}

static rt_err_t lcd_ipa_copy(const void *source, void *destination,
                              rt_uint32_t width, rt_uint32_t height,
                              rt_uint32_t source_stride, rt_uint32_t destination_stride)
{
    rt_tick_t start;
    rt_uint32_t flags;
    rt_err_t result = RT_EOK;

    if ((IPA_CTL & IPA_CTL_TEN) != 0U)
    {
        /* This configuration gives IPA exclusively to the synchronous port. */
        lcd_ipa_error_flags |= IPA_INTF;
        ipa_deinit();
        __DSB();
        return -RT_EBUSY;
    }
    IPA_CTL = IPA_FGTODE;
    IPA_INTC = 0x3FU;
    IPA_FMADDR = (rt_uint32_t)source;
    IPA_DMADDR = (rt_uint32_t)destination;
    IPA_FLOFF = source_stride / LCD_BYTES_PER_PIXEL - width;
    IPA_DLOFF = destination_stride / LCD_BYTES_PER_PIXEL - width;
    IPA_FPCTL = FOREGROUND_PPF_RGB565;
    IPA_DPCTL = DESTINATION_PPF_RGB565;
    IPA_BSCTL = 0x10001000U;
    IPA_DIMS = 0U;
    IPA_IMS = (width << 16U) | height;
    __DSB();
    start = rt_tick_get();
    IPA_CTL |= IPA_CTL_TEN;
    while (1)
    {
        flags = IPA_INTF;
        if ((flags & (IPA_INTF_TAEIF | IPA_INTF_WCFIF | IPA_INTF_LACIF)) != 0U)
        {
            lcd_ipa_error_flags |= flags;
            result = -RT_EIO;
            break;
        }
        if (((flags & IPA_INTF_FTFIF) != 0U) && ((IPA_CTL & IPA_CTL_TEN) == 0U))
        {
            break;
        }
        if ((rt_tick_t)(rt_tick_get() - start) >= rt_tick_from_millisecond(100U))
        {
            result = -RT_ETIMEOUT;
            break;
        }
    }
    if (result != RT_EOK)
    {
        /* Stop this port's engine before LVGL can reuse its source buffer. */
        ipa_deinit();
    }
    __DSB();
    /* The scanout windows are write-through. Drop stale CPU lines after DMA,
     * without writing any CPU cache contents back over the IPA result. */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, destination,
                         (height - 1U) * destination_stride + width * LCD_BYTES_PER_PIXEL);
    return result;
}

static rt_err_t lcd_ipa_present(void)
{
    rt_err_t result;
    rt_uint8_t *old_scanout;
    rt_uint32_t row;
    rt_uint32_t lines;
    rt_uint32_t offset;
    rt_uint32_t stride = lcd_info.width * LCD_BYTES_PER_PIXEL;
    rt_uint32_t width = lv_area_get_width(&lcd_pending_area);

    result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, lcd_render_framebuffer);
    if (result != RT_EOK)
    {
        return result;
    }
    result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_WAIT_VSYNC, RT_NULL);
    if (result != RT_EOK)
    {
        return result;
    }
    old_scanout = lcd_scanout_framebuffer;
    lcd_scanout_framebuffer = lcd_render_framebuffer;
    lcd_render_framebuffer = old_scanout;

    /* Only the hardware reload releases the old front buffer. Synchronize the
     * changed rectangle with IPA so the next partial frame retains other pixels. */
    for (row = lcd_pending_area.y1; row <= (rt_uint32_t)lcd_pending_area.y2; row += lines)
    {
        lines = (rt_uint32_t)lcd_pending_area.y2 - row + 1U;
        if (lines > LCD_DRAW_BUFFER_LINES)
        {
            lines = LCD_DRAW_BUFFER_LINES;
        }
        offset = row * stride + lcd_pending_area.x1 * LCD_BYTES_PER_PIXEL;
        result = lcd_ipa_copy(lcd_scanout_framebuffer + offset, lcd_render_framebuffer + offset,
                              width, lines, stride, stride);
        if (result != RT_EOK)
        {
            return result;
        }
    }
    lcd_pending_valid = RT_FALSE;
    return RT_EOK;
}

static void lcd_flush(lv_display_t *display, const lv_area_t *area, uint8_t *color_p)
{
    lv_draw_buf_t *draw_buf = lv_display_get_buf_active(display);
    rt_uint32_t width = lv_area_get_width(area);
    rt_uint32_t height = lv_area_get_height(area);
    rt_uint32_t stride;
    rt_uint32_t offset;
    rt_err_t result = -RT_EINVAL;

    if (lcd_pipeline_faulted)
    {
        lv_display_flush_ready(display);
        return;
    }
    if ((draw_buf == RT_NULL) || (area->x1 < 0) || (area->y1 < 0) ||
        (area->x2 >= lcd_info.width) || (area->y2 >= lcd_info.height) ||
        (area->x2 < area->x1) || (area->y2 < area->y1) ||
        (color_p != lcd_draw_buffer_1))
    {
        goto failed;
    }
    stride = draw_buf->header.stride;
    if ((stride < width * LCD_BYTES_PER_PIXEL) || ((stride & 1U) != 0U) ||
        (stride > sizeof(lcd_draw_buffer_1) / height))
    {
        goto failed;
    }
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, color_p, stride * height);
    offset = (area->y1 * lcd_info.width + area->x1) * LCD_BYTES_PER_PIXEL;
    result = lcd_ipa_copy(color_p, lcd_render_framebuffer + offset, width, height,
                          stride, lcd_info.width * LCD_BYTES_PER_PIXEL);
    if (result != RT_EOK)
    {
        goto failed;
    }
    if (!lcd_pending_valid)
    {
        lcd_pending_area = *area;
        lcd_pending_valid = RT_TRUE;
    }
    else
    {
        if (area->x1 < lcd_pending_area.x1) lcd_pending_area.x1 = area->x1;
        if (area->y1 < lcd_pending_area.y1) lcd_pending_area.y1 = area->y1;
        if (area->x2 > lcd_pending_area.x2) lcd_pending_area.x2 = area->x2;
        if (area->y2 > lcd_pending_area.y2) lcd_pending_area.y2 = area->y2;
    }
    if (lv_display_flush_is_last(display))
    {
        result = lcd_ipa_present();
        if (result != RT_EOK)
        {
            goto failed;
        }
    }
    lv_display_flush_ready(display);
    return;

failed:
    /* No CPU fallback: hold the last submitted image, never reuse an uncertain
     * scanout buffer. The console remains available for diagnostics. */
    lcd_pipeline_faulted = RT_TRUE;
    LOG_E("IPA display pipeline stopped: %d flags=%08x; reboot required", result, lcd_ipa_error_flags);
    lv_display_flush_ready(display);
}
#elif !LVGL_USE_DIRECT_FRAMEBUFFER
static void lcd_clean_dcache(void *address, rt_size_t size)
{
#if __CORTEX_M >= 0x07
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, address, size);
#else
    RT_UNUSED(address);
    RT_UNUSED(size);
#endif
}

static void lcd_ipa_init(void)
{
    rcu_periph_clock_enable(RCU_IPA);
    ipa_interval_clock_num_config(255U);
    ipa_inter_timer_config(IPA_INTER_TIMER_ENABLE);
}

static void lcd_flush(lv_display_t *display,
                      const lv_area_t *area,
                      uint8_t *color_p)
{
    rt_uint32_t width;
    rt_uint32_t height;

    width = (rt_uint32_t)lv_area_get_width(area);
    height = (rt_uint32_t)lv_area_get_height(area);

    /* LVGL serializes flushes, matching the reference project's strategy. */
    while (g_flushing_display != RT_NULL)
    {
    }
    g_flushing_display = display;

    lcd_clean_dcache(color_p, (rt_size_t)width * height * LCD_BYTES_PER_PIXEL);

    IPA_CTL = IPA_FGTODE | IPA_CTL_FTFIE;
    IPA_FMADDR = (rt_uint32_t)color_p;
    IPA_DMADDR = (rt_uint32_t)lcd_info.framebuffer +
                 (rt_uint32_t)2U *
                 ((rt_uint32_t)lcd_info.width *
                  ((rt_uint32_t)area->y1 + lcd_viewport_y) +
                  (rt_uint32_t)area->x1 + lcd_viewport_x);
    IPA_FLOFF = 0U;
    IPA_DLOFF = (rt_uint32_t)lcd_info.width - width;
    IPA_FPCTL = FOREGROUND_PPF_RGB565;
    IPA_IMS = (width << 16U) | (height & 0xFFFFU);
    IPA_CTL |= IPA_CTL_TEN;
}

void IPA_IRQHandler(void)
{
    rt_interrupt_enter();

    if (SET == ipa_interrupt_flag_get(IPA_INT_FLAG_FTF))
    {
        ipa_interrupt_flag_clear(IPA_INT_FLAG_FTF);
        if (g_flushing_display != RT_NULL)
        {
            lv_display_flush_ready((lv_display_t *)g_flushing_display);
            g_flushing_display = RT_NULL;
        }
    }

    rt_interrupt_leave();
}
#else
static void lcd_flush(lv_display_t *display,
                      const lv_area_t *area,
                      uint8_t *color_p)
{
    rt_err_t result;
    rt_bool_t swap_submitted = RT_FALSE;

    RT_UNUSED(area);

    if (!lv_display_flush_is_last(display))
    {
        lv_display_flush_ready(display);
        return;
    }

    /* Direct mode reuses the old scanout buffer after flush_ready. A failed
     * wait must retain ownership, and retrying it must not submit another swap. */
    do
    {
        if (!swap_submitted)
        {
            result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY,
                                       color_p);
            swap_submitted = (result == RT_EOK);
        }
        if (swap_submitted)
        {
            result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_WAIT_VSYNC,
                                       RT_NULL);
        }
        if (result != RT_EOK)
        {
            if (!flush_error_reported)
            {
                LOG_E("framebuffer swap failed: %d; retaining buffers", result);
                flush_error_reported = RT_TRUE;
            }
            rt_thread_mdelay(1U);
        }
    } while (result != RT_EOK);

    flush_error_reported = RT_FALSE;
    lv_display_flush_ready(display);
}
#endif

void lv_port_disp_init(void)
{
    rt_err_t result;
    rt_uint32_t framebuffer_size;
#if LVGL_USE_DIRECT_FRAMEBUFFER
    rt_uint8_t *back_framebuffer;
#endif

    lcd_device = rt_device_find(LCD_DEVICE_NAME);
    if (lcd_device == RT_NULL)
    {
        LOG_E("cannot find %s device", LCD_DEVICE_NAME);
        return;
    }

    result = rt_device_open(lcd_device, RT_DEVICE_OFLAG_RDWR);
    if (result != RT_EOK)
    {
        LOG_E("cannot open %s device: %d", LCD_DEVICE_NAME, result);
        return;
    }

    result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_GET_INFO, &lcd_info);
    framebuffer_size = (rt_uint32_t)lcd_info.width * lcd_info.height *
                       LCD_BYTES_PER_PIXEL;
    if ((result != RT_EOK) ||
        (lcd_info.width != LV_HOR_RES_MAX) ||
        (lcd_info.height != LV_VER_RES_MAX) ||
        (lcd_info.pixel_format != RTGRAPHIC_PIXEL_FORMAT_RGB565) ||
        (lcd_info.bits_per_pixel != 16U) ||
        (lcd_info.framebuffer == RT_NULL) ||
        (lcd_info.smem_len < framebuffer_size *
                             ((LVGL_USE_DIRECT_FRAMEBUFFER || LVGL_USE_IPA_FRAMEBUFFER) ? 2U : 1U)))
    {
        LOG_E("invalid %s framebuffer", LCD_DEVICE_NAME);
        rt_device_close(lcd_device);
        return;
    }

    lcd_viewport_x = (rt_uint16_t)((lcd_info.width - LVGL_DISPLAY_WIDTH) / 2U);
    lcd_viewport_y = (rt_uint16_t)((lcd_info.height - LVGL_DISPLAY_HEIGHT) / 2U);

#if LVGL_USE_IPA_FRAMEBUFFER
    if (((rt_ubase_t)lcd_draw_buffer_1 < 0x24000000U) ||
        ((rt_ubase_t)lcd_draw_buffer_1 + sizeof(lcd_draw_buffer_1) > (rt_ubase_t)GD32_SRAM_END))
    {
        LOG_E("LVGL draw buffer must be in AXI SRAM");
        rt_device_close(lcd_device);
        return;
    }
    lcd_scanout_framebuffer = lcd_info.framebuffer;
    lcd_render_framebuffer = lcd_scanout_framebuffer + framebuffer_size;
#endif

    lvgl_display = lv_display_create(LVGL_DISPLAY_WIDTH, LVGL_DISPLAY_HEIGHT);
    if (lvgl_display == RT_NULL)
    {
        LOG_E("cannot create LVGL display");
        rt_device_close(lcd_device);
        return;
    }

    lv_display_set_color_format(lvgl_display, LV_COLOR_FORMAT_RGB565);
#if LVGL_USE_DIRECT_FRAMEBUFFER
    back_framebuffer = (rt_uint8_t *)lcd_info.framebuffer + framebuffer_size;
    lv_display_set_buffers(lvgl_display,
                           back_framebuffer,
                           lcd_info.framebuffer,
                           framebuffer_size,
                           LV_DISPLAY_RENDER_MODE_DIRECT);
#elif LVGL_USE_IPA_FRAMEBUFFER
    lv_display_set_buffers(lvgl_display, lcd_draw_buffer_1, RT_NULL,
                           sizeof(lcd_draw_buffer_1), LV_DISPLAY_RENDER_MODE_PARTIAL);
#else
    lv_display_set_buffers(lvgl_display,
                           lcd_draw_buffer_1,
                           lcd_draw_buffer_2,
                           sizeof(lcd_draw_buffer_1),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);
#endif
    lv_display_set_flush_cb(lvgl_display, lcd_flush);
    lv_display_set_default(lvgl_display);

#if !LVGL_USE_DIRECT_FRAMEBUFFER
    lcd_ipa_init();
#if !LVGL_USE_IPA_FRAMEBUFFER
    nvic_irq_enable(IPA_IRQn, 2U, 0U);
#endif
#endif
    display_ready = RT_TRUE;

#if LVGL_USE_DIRECT_FRAMEBUFFER
    LOG_I("%ux%u RGB565 direct framebuffers at %p/%p",
          lcd_info.width, lcd_info.height,
          lcd_info.framebuffer, back_framebuffer);
    LOG_I("vertical blank framebuffer swapping enabled");
#elif LVGL_USE_IPA_FRAMEBUFFER
    LOG_I("AXI SRAM partial rendering: %u lines, %u bytes at %p",
          LCD_DRAW_BUFFER_LINES, (rt_uint32_t)sizeof(lcd_draw_buffer_1), lcd_draw_buffer_1);
    LOG_I("IPA back-buffer flush and sync, vertical blank swaps at %p/%p",
          lcd_scanout_framebuffer, lcd_render_framebuffer);
#else
    LOG_I("%ux%u LVGL viewport centered on %ux%u RGB565 panel",
          LVGL_DISPLAY_WIDTH, LVGL_DISPLAY_HEIGHT,
          lcd_info.width, lcd_info.height);
    LOG_I("partial buffers (%u lines) at %p/%p",
          LCD_DRAW_BUFFER_LINES,
          lcd_draw_buffer_1, lcd_draw_buffer_2);
    LOG_I("reference IPA flush strategy enabled");
#endif
}

#ifdef BSP_USING_TOUCH_GT911
static void touch_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    struct rt_touch_data touch_data[TOUCH_POINT_COUNT];
    rt_size_t point_index;
    rt_bool_t active_point_found = RT_FALSE;

    RT_UNUSED(indev);

    rt_memset(touch_data, 0, sizeof(touch_data));
    if (rt_device_read(touch_device, 0, touch_data, TOUCH_POINT_COUNT) == TOUCH_POINT_COUNT)
    {
        for (point_index = 0; point_index < TOUCH_POINT_COUNT; point_index++)
        {
            if ((touch_data[point_index].event == RT_TOUCH_EVENT_DOWN) ||
                (touch_data[point_index].event == RT_TOUCH_EVENT_MOVE))
            {
                if ((touch_data[point_index].x_coordinate >= lcd_viewport_x) &&
                    (touch_data[point_index].x_coordinate < lcd_viewport_x + LVGL_DISPLAY_WIDTH) &&
                    (touch_data[point_index].y_coordinate >= lcd_viewport_y) &&
                    (touch_data[point_index].y_coordinate < lcd_viewport_y + LVGL_DISPLAY_HEIGHT))
                {
                    touch_x = (lv_coord_t)(touch_data[point_index].x_coordinate - lcd_viewport_x);
                    touch_y = (lv_coord_t)(touch_data[point_index].y_coordinate - lcd_viewport_y);
                    touch_pressed = RT_TRUE;
                }
                else
                {
                    touch_pressed = RT_FALSE;
                }

                active_point_found = RT_TRUE;
                break;
            }
        }

        if (!active_point_found)
        {
            for (point_index = 0; point_index < TOUCH_POINT_COUNT; point_index++)
            {
                if (touch_data[point_index].event == RT_TOUCH_EVENT_UP)
                {
                    touch_pressed = RT_FALSE;
                    break;
                }
            }
        }
    }

    data->point.x = touch_x;
    data->point.y = touch_y;
    data->state = touch_pressed ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
}
#endif

void lv_port_indev_init(void)
{
#ifdef BSP_USING_TOUCH_GT911
    rt_err_t result;
    lv_indev_t *input_device;

    touch_device = rt_device_find(TOUCH_DEVICE_NAME);
    if (touch_device == RT_NULL)
    {
        result = rt_hw_gt911_port_init();
        if (result == RT_EOK)
        {
            touch_device = rt_device_find(TOUCH_DEVICE_NAME);
        }
        if (touch_device == RT_NULL)
        {
            LOG_E("cannot initialize %s device: %d",
                  TOUCH_DEVICE_NAME, result);
            return;
        }
    }

    result = rt_device_open(touch_device, RT_DEVICE_OFLAG_RDONLY);
    if (result != RT_EOK)
    {
        LOG_E("cannot open %s device: %d", TOUCH_DEVICE_NAME, result);
        touch_device = RT_NULL;
        return;
    }

    input_device = lv_indev_create();
    if (input_device == RT_NULL)
    {
        LOG_E("cannot create LVGL input device");
        rt_device_close(touch_device);
        touch_device = RT_NULL;
        return;
    }

    lv_indev_set_type(input_device, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(input_device, touch_read);
    lv_indev_set_display(input_device, lvgl_display);

    LOG_I("%s registered as LVGL pointer", TOUCH_DEVICE_NAME);
#endif
}

void lv_user_gui_init(void)
{
    if (!display_ready)
    {
        return;
    }

#ifdef BSP_USING_LVGL_BOARD_DEMO
    extern void board_demo_init(void);

    board_demo_init();
    lv_refr_now(NULL);
#elif LV_USE_DEMO_SMARTWATCH
    extern void lv_demo_smartwatch(void);

    lv_demo_smartwatch();
    lv_refr_now(NULL);
#elif LV_USE_DEMO_BENCHMARK
    extern void lv_demo_benchmark(void);

    lv_demo_benchmark();
    lv_refr_now(NULL);
#elif defined(PKG_USING_LV_MUSIC_DEMO)
    extern void lv_demo_music(void);

    lv_demo_music();
    lv_refr_now(NULL);
#else
    LOG_W("no LVGL demo is enabled");
    lv_refr_now(NULL);
#endif

#if defined(BSP_USING_OV7670_PREVIEW) && !defined(BSP_USING_LVGL_BOARD_DEMO) && \
    !LV_USE_DEMO_SMARTWATCH
    extern void ov7670_preview_init(void);

    ov7670_preview_init();
#endif
}

#endif /* PKG_USING_LVGL */
