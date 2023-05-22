/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-24     Rbb666       the first version
 */

#include <rtthread.h>

#if (defined(BSP_USING_LCD)) || (defined(SOC_SERIES_R7FA6M3))

#include <lcd_port.h>

#include "r_display_api.h"
#include "hal_data.h"

//#define DRV_DEBUG
//#define LOG_TAG             "drv.lcd"
//#include <drv_log.h>

struct drv_lcd_device
{
    struct rt_device parent;
    struct rt_device_graphic_info lcd_info;

    void *framebuffer;
};

struct drv_lcd_device _lcd;

uint16_t screen_rotation;
uint16_t *lcd_current_working_buffer = (uint16_t *)&fb_background[0];

// jpeg and lvgl can only select one
__WEAK void _ra_port_display_callback(display_callback_args_t *p_args)
{
    if (DISPLAY_EVENT_LINE_DETECTION == p_args->event)
    {
    }
}

void turn_on_lcd_backlight(void)
{
    rt_pin_mode(LCD_BL_PIN, PIN_MODE_OUTPUT);   /* LCD_BL */
    rt_pin_write(LCD_BL_PIN, PIN_HIGH);
}

void ra_bsp_lcd_init(void)
{
    fsp_err_t error;
    // Set screen rotation to default view
    screen_rotation = ROTATION_ZERO;

    /**  Display driver open */
    error = R_GLCDC_Open(&g_display0_ctrl, &g_display0_cfg);
    if (FSP_SUCCESS == error)
    {
        /**  Display driver start */
        error = R_GLCDC_Start(&g_display0_ctrl);
    }
}

void ra_bsp_lcd_set_display_buffer(uint8_t index)
{
    R_GLCDC_BufferChange(&g_display0_ctrl, fb_background[index - 1], DISPLAY_FRAME_LAYER_1);
}

void ra_bsp_lcd_set_working_buffer(uint8_t index)
{
    if (index >= 1 && index <= 2)
    {
        lcd_current_working_buffer = (uint16_t *)fb_background[index - 1];
    }
}

void ra_bsp_lcd_enable_double_buffer(void)
{
    ra_bsp_lcd_set_display_buffer(1);
    ra_bsp_lcd_set_working_buffer(2);
}

void ra_bsp_lcd_clear(uint16_t color)
{
    for (uint32_t i = 0; i < (LCD_WIDTH * LCD_HEIGHT); i++)
    {
        lcd_current_working_buffer[i] = color;
    }
}

void ra_bsp_lcd_swap_buffer(void)
{
    if (lcd_current_working_buffer == (uint16_t *)fb_background[0])
    {
        ra_bsp_lcd_set_display_buffer(1);
        ra_bsp_lcd_set_working_buffer(2);
    }
    else
    {
        ra_bsp_lcd_set_display_buffer(2);
        ra_bsp_lcd_set_working_buffer(1);
    }
}

void bsp_lcd_draw_pixel(uint32_t x, uint32_t y, uint16_t color)
{
    // Verify pixel is within LCD range
    if ((x < LCD_WIDTH) && (y < LCD_HEIGHT))
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
        rt_kprintf("draw pixel outof range:%d,%d\n", x, y);
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
            bsp_lcd_draw_pixel(x_start + x_offset, cycle_y, *pixel++);
        }
        cycle_y++;
    }
}

static rt_err_t ra_lcd_init(rt_device_t device)
{
    RT_ASSERT(device != RT_NULL);

    ra_bsp_lcd_init();

    return RT_EOK;
}

static rt_err_t ra_lcd_control(rt_device_t device, int cmd, void *args)
{
    struct drv_lcd_device *lcd = (struct drv_lcd_device *)device;

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        struct rt_device_rect_info *info = (struct rt_device_rect_info *)args;

        (void)info; /* nothing, right now */
        rt_kprintf("update screen...\n");
    }
    break;

    case RTGRAPHIC_CTRL_POWERON:
        rt_pin_write(LCD_BL_PIN, PIN_HIGH);
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

int rt_hw_lcd_init(void)
{
    rt_err_t result = RT_EOK;
    struct rt_device *device = &_lcd.parent;

    /* memset _lcd to zero */
    memset(&_lcd, 0x00, sizeof(_lcd));

    /* config LCD dev info */
    _lcd.lcd_info.height = LCD_HEIGHT;
    _lcd.lcd_info.width = LCD_WIDTH;
    _lcd.lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd.lcd_info.pixel_format = LCD_PIXEL_FORMAT;

    _lcd.lcd_info.framebuffer = (uint8_t *)&fb_background[0];

    device->type    = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &lcd_ops;
#else
    device->init    = ra_lcd_init;
    device->control = ra_lcd_control;
#endif

    /* register lcd device */
    rt_device_register(device, "lcd", RT_DEVICE_FLAG_RDWR);

    turn_on_lcd_backlight();

    // Initialize lcd controller
    ra_lcd_init(device);

    ra_bsp_lcd_set_display_buffer(1);

    screen_rotation = ROTATION_ZERO;

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_lcd_init);

int lcd_test()
{
    struct drv_lcd_device *lcd;
    lcd = (struct drv_lcd_device *)rt_device_find("lcd");

    while (1)
    {
        /* red */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
        {
            lcd->lcd_info.framebuffer[2 * i] = 0x00;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0xF8;
        }
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
        /* green */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
        {
            lcd->lcd_info.framebuffer[2 * i] = 0xE0;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0x07;
        }
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
        /* blue */
        for (int i = 0; i < LCD_BUF_SIZE / 2; i++)
        {
            lcd->lcd_info.framebuffer[2 * i] = 0x1F;
            lcd->lcd_info.framebuffer[2 * i + 1] = 0x00;
        }
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(lcd_test, lcd_test);

#endif /* BSP_USING_LCD */
