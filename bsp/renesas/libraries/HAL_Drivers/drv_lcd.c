/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-24     Rbb666       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_LCD
#ifdef SOC_SERIES_R7FA8M85
#include <ra8/lcd_config.h>
#else
#include <ra6m3/lcd_config.h>
#endif
#include <drv_lcd.h>

#include "hal_data.h"

#define DRV_DEBUG
#define LOG_TAG             "drv_lcd"
#include <drv_log.h>
struct drv_lcd_device
{
    struct rt_device parent;
    struct rt_device_graphic_info lcd_info;
};

struct drv_lcd_device _lcd;
static uint16_t screen_rotation;
static struct rt_completion sync_completion;

static uint16_t *gp_single_buffer = NULL;
static uint16_t *gp_double_buffer = NULL;
static uint16_t *lcd_current_working_buffer = (uint16_t *) &fb_background[0];

#ifdef SOC_SERIES_R7FA8M85
static uint8_t lcd_framebuffer[LCD_BUF_SIZE] BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION(".sdram");
#endif

// G2D
extern d2_device *d2_handle0;
static d2_device **_d2_handle_user = &d2_handle0;
static d2_renderbuffer *renderbuffer;

#ifdef SOC_SERIES_R7FA8M85
extern void ra8_mipi_lcd_init(void);
#endif

rt_weak void DisplayVsyncCallback(display_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (DISPLAY_EVENT_LINE_DETECTION == p_args->event)
    {
        rt_completion_done(&sync_completion);
    }
    rt_interrupt_leave();
}

// Wait until Vsync is triggered through callback function
static void vsync_wait(void)
{
    rt_completion_wait(&sync_completion, RT_WAITING_FOREVER);
}

static void turn_on_lcd_backlight(void)
{
#ifdef BSP_USING_LCD_PWM_BACKLIGHT
    struct rt_device_pwm *pwm_dev;

    /* turn on the LCD backlight */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(LCD_PWM_DEV_NAME);
    /* pwm frequency:100K = 10000ns */
    rt_pwm_set(pwm_dev, 0, 10000, 7000);
    rt_pwm_enable(pwm_dev, 0);
#else
    rt_pin_mode(LCD_BL_PIN, PIN_MODE_OUTPUT);   /* LCD_BL */
    rt_pin_write(LCD_BL_PIN, PIN_HIGH);
#endif
}

static void ra_bsp_lcd_clear(uint16_t color)
{
    for (uint32_t i = 0; i < LCD_BUF_SIZE; i++)
    {
        lcd_current_working_buffer[i] = color;
    }
}

void lcd_draw_pixel(uint32_t x, uint32_t y, uint16_t color)
{
    // Verify pixel is within LCD range
    if ((x <= LCD_WIDTH) && (y <= LCD_HEIGHT))
    {
        switch (screen_rotation)
        {
        case ROTATION_ZERO:
        {
            lcd_current_working_buffer[(y * LCD_WIDTH) + x] = color;
            break;
        }
        case ROTATION_180:
        {
            lcd_current_working_buffer[((LCD_HEIGHT - y) * LCD_WIDTH) + (LCD_WIDTH - x)] = color;
            break;
        }
        default:
        {
            lcd_current_working_buffer[(y * LCD_WIDTH) + x] = color;
            break;
        }
        }
    }
    else
    {
        LOG_D("draw pixel outof range:%d,%d", x, y);
    }
}

void lcd_fill_array(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, void *pcolor)
{
    uint16_t *pixel = RT_NULL;
    uint16_t cycle_y, x_offset = 0;

    pixel = (uint16_t *)pcolor;

    for (cycle_y = y_start; cycle_y <= y_end;)
    {
        for (x_offset = 0; x_start + x_offset <= x_end; x_offset++)
        {
            lcd_draw_pixel(x_start + x_offset, cycle_y, *pixel++);
        }
        cycle_y++;
    }
}

d2_device *d2_handle_obj_get(void)
{
    return *_d2_handle_user;
}

d2_renderbuffer *d2_renderbuffer_get(void)
{
    return renderbuffer;
}

void lcd_draw_jpg(int32_t x, int32_t y, const void *p, int32_t xSize, int32_t ySize)
{
    uint32_t ModeSrc;
    ModeSrc = d2_mode_rgb565;

    // Generate render operations
    d2_framebuffer(d2_handle_obj_get(), (uint16_t *)&fb_background[0], LCD_WIDTH, LCD_WIDTH, LCD_HEIGHT, ModeSrc);

    d2_selectrenderbuffer(d2_handle_obj_get(), d2_renderbuffer_get());
    d2_cliprect(d2_handle_obj_get(), 0, 0, LCD_WIDTH, LCD_HEIGHT);
    d2_setblitsrc(d2_handle_obj_get(), (void *) p, xSize, xSize, ySize, ModeSrc);
    d2_blitcopy(d2_handle_obj_get(), xSize, ySize, 0, 0, (d2_width)(LCD_WIDTH << 4), (d2_width)(LCD_HEIGHT << 4),
                (d2_point)(x << 4), (d2_point)(y << 4), 0);

    // Execute render operations
    d2_executerenderbuffer(d2_handle_obj_get(), d2_renderbuffer_get(), 0);

    // In single-buffered mode always wait for DRW to finish before returning
    d2_flushframe(d2_handle_obj_get());
}

void lcd_gpu_fill_array(size_t x1, size_t y1, size_t x2, size_t y2, uint16_t *color_data)
{
    uint32_t ModeSrc;
    int32_t width;
    int32_t heigh;

    width = (x2 - x1) + 1;
    heigh = (y2 - y1) + 1;

    ModeSrc = d2_mode_rgb565;

    // Generate render operations
    d2_framebuffer(d2_handle_obj_get(), (uint16_t *)&fb_background[0], LCD_WIDTH, LCD_WIDTH, LCD_HEIGHT, ModeSrc);

    d2_selectrenderbuffer(d2_handle_obj_get(), d2_renderbuffer_get());
    d2_cliprect(d2_handle_obj_get(), 0, 0, LCD_WIDTH, LCD_HEIGHT);
    d2_setblitsrc(d2_handle_obj_get(), (void *) color_data, width, width, heigh, ModeSrc);
    d2_blitcopy(d2_handle_obj_get(), width, heigh, 0, 0, (d2_width)(LCD_WIDTH << 4), (d2_width)(LCD_HEIGHT << 4),
                (d2_point)(x1 << 4), (d2_point)(y1 << 4), 0);

    // Execute render operations
    d2_executerenderbuffer(d2_handle_obj_get(), d2_renderbuffer_get(), 0);
    // In single-buffered mode always wait for DRW to finish before returning
    d2_flushframe(d2_handle_obj_get());
}

void g2d_display_write_area(const void *pSrc, void *pDst, int WidthSrc, int HeightSrc, int x, int y)
{
    uint32_t ModeSrc;
    ModeSrc = d2_mode_rgb565;

    /* Set the new buffer to the current draw buffer */
    d2_framebuffer(d2_handle_obj_get(), (uint16_t *)pDst, LCD_WIDTH, LCD_WIDTH, LCD_HEIGHT, ModeSrc);

    d2_selectrenderbuffer(d2_handle_obj_get(), d2_renderbuffer_get());
    d2_cliprect(d2_handle_obj_get(), 0, 0, LCD_WIDTH, LCD_HEIGHT);
    d2_setblitsrc(d2_handle_obj_get(), (void *) pSrc, WidthSrc, WidthSrc, HeightSrc, ModeSrc);
    d2_blitcopy(d2_handle_obj_get(), WidthSrc, HeightSrc, 0, 0, (d2_width)(WidthSrc << 4), (d2_width)(HeightSrc << 4),
                (d2_point)(x << 4), (d2_point)(y << 4), 0);

    /* End the current display list */
    d2_executerenderbuffer(d2_handle_obj_get(), d2_renderbuffer_get(), 0);
    d2_flushframe(d2_handle_obj_get());
}

static int g2d_drv_hwInit(void)
{
    d2_s32 d2_err;
    uint32_t ModeSrc;
    ModeSrc = d2_mode_rgb565;

    // Initialize D/AVE 2D driver
    *_d2_handle_user = d2_opendevice(0);
    d2_err = d2_inithw(*_d2_handle_user, 0);
    if (d2_err != D2_OK)
    {
        LOG_E("g2d init fail");
        d2_closedevice(*_d2_handle_user);
        return -RT_ERROR;
    }

    // Clear both buffers
    d2_framebuffer(*_d2_handle_user, (uint16_t *)&fb_background[0], LCD_WIDTH, LCD_WIDTH,
                   LCD_HEIGHT, ModeSrc);
    d2_clear(*_d2_handle_user, 0x000000);

    // Set various D2 parameters
    d2_setblendmode(*_d2_handle_user, d2_bm_alpha, d2_bm_one_minus_alpha);
    d2_setalphamode(*_d2_handle_user, d2_am_constant);
    d2_setalpha(*_d2_handle_user, UINT8_MAX);
    d2_setantialiasing(*_d2_handle_user, 1);
    d2_setlinecap(*_d2_handle_user, d2_lc_butt);
    d2_setlinejoin(*_d2_handle_user, d2_lj_miter);

    renderbuffer = d2_newrenderbuffer(*_d2_handle_user, 20, 20);
    if (!renderbuffer)
    {
        LOG_E("no renderbuffer");
        d2_closedevice(*_d2_handle_user);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t ra_lcd_control(rt_device_t device, int cmd, void *args)
{
    struct drv_lcd_device *lcd = (struct drv_lcd_device *)device;

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
#ifdef SOC_SERIES_R7FA8M85
        struct rt_device_rect_info *info = (struct rt_device_rect_info *)args;
#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
        SCB_CleanInvalidateDCache_by_Addr((uint32_t *)lcd->lcd_info.framebuffer, sizeof(fb_background[0]));
#endif
#if defined(ENABLE_DOUBLE_BUFFER) && ENABLE_DOUBLE_BUFFER
        /* Swap the active framebuffer */
        lcd_current_working_buffer = (lcd_current_working_buffer == gp_single_buffer) ? gp_double_buffer : gp_single_buffer;
#endif

        g2d_display_write_area((uint8_t *)lcd->lcd_info.framebuffer, lcd_current_working_buffer,
                               info->width, info->height, info->x, info->y);
#if defined(ENABLE_DOUBLE_BUFFER) && ENABLE_DOUBLE_BUFFER
        /* Now that the framebuffer is ready, update the GLCDC buffer pointer on the next Vsync */
        fsp_err_t err = R_GLCDC_BufferChange(&g_display0_ctrl, (uint8_t *) lcd_current_working_buffer, DISPLAY_FRAME_LAYER_1);
        RT_ASSERT(err == 0);
#endif
#endif  /* SOC_SERIES_R7FA8M85 */
        /* wait for vsync interrupt */
        vsync_wait();
    }
    break;

    case RTGRAPHIC_CTRL_POWERON:
        turn_on_lcd_backlight();
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
        rt_pin_write(LCD_BL_PIN, PIN_LOW);
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info = (struct rt_device_graphic_info *)args;

        RT_ASSERT(info != RT_NULL);
        info->pixel_format  = lcd->lcd_info.pixel_format;
        info->bits_per_pixel = 16;
        info->width         = lcd->lcd_info.width;
        info->height        = lcd->lcd_info.height;
        info->framebuffer   = lcd->lcd_info.framebuffer;
    }
    break;

    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

static rt_err_t drv_lcd_init(struct rt_device *device)
{
    return RT_EOK;
}

static void reset_lcd_panel(void)
{
#ifdef LCD_RST_PIN
    rt_pin_mode(LCD_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LCD_RST_PIN, PIN_LOW);
    rt_thread_mdelay(100);
    rt_pin_write(LCD_RST_PIN, PIN_HIGH);
    rt_thread_mdelay(100);
#endif
}

static rt_err_t ra_bsp_lcd_init(void)
{
    fsp_err_t error;

    /* Set screen rotation to default view */
    screen_rotation = ROTATION_ZERO;

    /*  Display driver open */
    error = R_GLCDC_Open(&g_display0_ctrl, &g_display0_cfg);
    if (FSP_SUCCESS == error)
    {
#ifdef SOC_SERIES_R7FA8M85
        /* config mipi */
        ra8_mipi_lcd_init();
#endif
        /* Initialize g2d */
        error = g2d_drv_hwInit();

        /* Display driver start */
        error = R_GLCDC_Start(&g_display0_ctrl);
    }

    return error;
}

int rt_hw_lcd_init(void)
{
    struct rt_device *device = &_lcd.parent;

    /* memset _lcd to zero */
    memset(&_lcd, 0x00, sizeof(_lcd));

    /* config LCD dev info */
    _lcd.lcd_info.height = LCD_HEIGHT;
    _lcd.lcd_info.width = LCD_WIDTH;
    _lcd.lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd.lcd_info.pixel_format = LCD_PIXEL_FORMAT;
#ifdef SOC_SERIES_R7FA8M85
    _lcd.lcd_info.framebuffer = (uint8_t *)lcd_framebuffer;
#else
    _lcd.lcd_info.framebuffer = (uint8_t *)&fb_background[0];
#endif
    LOG_D("\nlcd framebuffer address:%#x", _lcd.lcd_info.framebuffer);
    memset(_lcd.lcd_info.framebuffer, 0x0, LCD_BUF_SIZE);

    device->type    = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &lcd_ops;
#else
    device->init    = drv_lcd_init;
    device->control = ra_lcd_control;
#endif

    /* register lcd device */
    rt_device_register(device, "lcd", RT_DEVICE_FLAG_RDWR);

    rt_completion_init(&sync_completion);

    /* Initialize buffer pointers */
    gp_single_buffer = (uint16_t *) g_display0_cfg.input[0].p_base;

    /* Double buffer for drawing color bands with good quality */
    gp_double_buffer = gp_single_buffer + LCD_BUF_SIZE;

    reset_lcd_panel();

    ra_bsp_lcd_init();

    /* turn on lcd  backlight */
    turn_on_lcd_backlight();

    ra_bsp_lcd_clear(0x0);

    screen_rotation = ROTATION_ZERO;

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_lcd_init);

#ifdef SOC_SERIES_R7FA8M85
rt_weak void ra8_mipi_lcd_init(void)
{
    LOG_E("please Implementation function %s", __func__);
}
#endif

int lcd_test(void)
{
    struct drv_lcd_device *lcd;
    struct rt_device_rect_info rect_info;
    rect_info.x = 0;
    rect_info.y = 0;
    rect_info.width = LCD_WIDTH;
    rect_info.height = LCD_HEIGHT;

    lcd = (struct drv_lcd_device *)rt_device_find("lcd");

    for (int i = 0; i < 2; i++)
    {
        /* red */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
        {
            lcd->lcd_info.framebuffer[2 * i] = 0x00;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0xF8;
        }
        LOG_D("red buffer...");
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        rt_thread_mdelay(1000);
        /* green */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
        {
            lcd->lcd_info.framebuffer[2 * i] = 0xE0;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0x07;
        }
        LOG_D("green buffer...");
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        rt_thread_mdelay(1000);
        /* blue */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
        {
            lcd->lcd_info.framebuffer[2 * i] = 0x1F;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0x00;
        }
        LOG_D("blue buffer...");
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}
MSH_CMD_EXPORT(lcd_test, lcd test cmd);

#endif /* BSP_USING_LCD */
