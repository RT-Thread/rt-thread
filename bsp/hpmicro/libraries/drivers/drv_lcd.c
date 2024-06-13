/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2024-02-20   HPMicro     First version
 */

#include <rtthread.h>

#ifdef BSP_USING_RTT_LCD_DRIVER
#include "board.h"
#include "hpm_l1c_drv.h"
#include "hpm_lcdc_drv.h"
#include "hpm_pdma_drv.h"
#include "hpm_panel.h"


#define LCD_BITS_PER_PIXEL  16
#define LCD_PIXEL_FORMAT    RTGRAPHIC_PIXEL_FORMAT_RGB565
#define LCD_LAYER_INDEX     (0)
#define LCD_LAYER_DONE_MASK (1U << LCD_LAYER_INDEX)
struct hpm_lcd
{
    LCDC_Type *lcd_base;
    rt_uint8_t lcd_irq;
    struct rt_semaphore lcd_lock;
    char *bus_name;
    struct rt_device parent;
    struct rt_device_graphic_info lcd_info;
    uint32_t lcd_buffer_size;
};

static rt_err_t hpm_lcd_init(struct rt_device *device);
static rt_err_t hpm_lcd_control(struct rt_device *device, int cmd, void *args);
static int hpm_lcdc_init(struct hpm_lcd *lcd, struct rt_device_graphic_info *info);

static uint8_t __attribute__((section(".framebuffer"), aligned(HPM_L1C_CACHELINE_SIZE))) lcdc_framebuffer[PANEL_SIZE_WIDTH * PANEL_SIZE_HEIGHT * LCD_BITS_PER_PIXEL / 8];


#ifdef RT_USING_DEVICE_OPS
const struct rt_device_ops hpm_lcd_ops = {
    .init = hpm_lcd_init,
    .open = RT_NULL,
    .close = RT_NULL,
    .read = RT_NULL,
    .write = RT_NULL,
    .control = hpm_lcd_control,
};
#endif

static struct hpm_lcd hpm_lcds[] =
{
    {
        .bus_name = "lcd0",
        .lcd_buffer_size = (PANEL_SIZE_WIDTH * PANEL_SIZE_HEIGHT * LCD_BITS_PER_PIXEL / 8),
        .lcd_base = HPM_LCDC,
        .lcd_irq = BOARD_LCD_IRQ,
        .parent.type = RT_Device_Class_Graphic,
#ifdef RT_USING_DEVICE_OPS
        .parent.ops = &hpm_lcd_ops,
#else
        .parent.init = hpm_lcd_init,
        .parent.open = RT_NULL,
        .parent.close = RT_NULL,
        .parent.read = RT_NULL,
        .parent.write = RT_NULL,
        .parent.control = hpm_lcd_control,
#endif
    },
};

void isr_lcd_d0(void)
{
    lcdc_disable_interrupt(hpm_lcds[0].lcd_base, LCDC_INT_EN_VSYNC_MASK);
    rt_sem_release(&hpm_lcds[0].lcd_lock);
    lcdc_clear_status(hpm_lcds[0].lcd_base, LCDC_ST_VSYNC_MASK);
}
SDK_DECLARE_EXT_ISR_M(BOARD_LCD_IRQ, isr_lcd_d0)

static rt_err_t hpm_lcd_init(struct rt_device *device)
{
    /* nothing, right now */
    (void *)device;
    return RT_EOK;
}

static rt_err_t hpm_lcd_control(struct rt_device *device, int cmd, void *args)
{
    uint32_t aligned_start, aligned_end, aligned_size;
    struct hpm_lcd *lcd = (struct hpm_lcd *)device->user_data;
    hpm_panel_t *panel = hpm_panel_find_device_default();
    struct rt_device_graphic_info *info = RT_NULL;
    uint32_t buffer;

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_SET_MODE:
        info = (struct rt_device_graphic_info *)args;
        rt_sem_trytake(&lcd->lcd_lock);
        lcdc_disable_interrupt(lcd->lcd_base, LCDC_INT_EN_VSYNC_MASK);
        rt_thread_delay(10);
        hpm_lcdc_init(lcd, info);
        break;

    case RTGRAPHIC_CTRL_RECT_UPDATE:
        if (args != RT_NULL)
        {
            buffer = (uint32_t)args;
        }
        else
        {
            buffer = (uint32_t)lcd->lcd_info.framebuffer;
        }
        if (l1c_dc_is_enabled())
        {
            aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN(buffer);
            aligned_end = HPM_L1C_CACHELINE_ALIGN_UP(buffer + lcd->lcd_buffer_size);
            aligned_size = aligned_end - aligned_start;
            l1c_dc_writeback(aligned_start, aligned_size);
        }
        if (lcdc_layer_control_shadow_loaded(lcd->lcd_base, 0))
        {
            lcdc_layer_set_next_buffer(lcd->lcd_base, 0, (rt_uint32_t)buffer);
        }
        break;

    case RTGRAPHIC_CTRL_WAIT_VSYNC:
        rt_sem_trytake(&lcd->lcd_lock);
        lcdc_enable_interrupt(lcd->lcd_base, LCDC_INT_EN_VSYNC_MASK);
        rt_sem_take(&lcd->lcd_lock, RT_WAITING_FOREVER);
        break;

    case RTGRAPHIC_CTRL_POWERON:
        hpm_panel_set_backlight(panel, true);
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
        hpm_panel_set_backlight(panel, false);
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        info = (struct rt_device_graphic_info *)args;

        RT_ASSERT(info != RT_NULL);
        info->pixel_format  = lcd->lcd_info.pixel_format;
        info->bits_per_pixel = 16;
        info->width         = lcd->lcd_info.width;
        info->height        = lcd->lcd_info.height;
        info->framebuffer   = lcd->lcd_info.framebuffer;
        break;

    default:
        break;
    }
}

static int hpm_lcdc_init(struct hpm_lcd *lcd, struct rt_device_graphic_info *info)
{
    lcdc_config_t config = {0};
    display_pixel_format_t pixel_format;
    lcdc_get_default_config(lcd->lcd_base, &config);
    board_panel_para_to_lcdc(&config);

    if (info->framebuffer == RT_NULL)
    {
        return -RT_ERROR;
    }
    rt_memcpy(&lcd->lcd_info, info, sizeof(struct rt_device_graphic_info));
    lcd->lcd_info.framebuffer = lcdc_framebuffer;
    if (info->pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565)
    {
        pixel_format = display_pixel_format_rgb565;
    }
    else if (info->pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
    {
        pixel_format = display_pixel_format_rgb565;
    }
    else {
        return -RT_ERROR;
    }
    lcdc_init(lcd->lcd_base, &config);
    memset(lcd->lcd_info.framebuffer, 0, info->width * info->height * info->bits_per_pixel / 8);
    lcdc_layer_config_t layer;
    lcdc_get_default_layer_config(lcd->lcd_base, &layer, pixel_format, LCD_LAYER_INDEX);

    layer.position_x = 0;
    layer.position_y = 0;
    layer.width = info->width;
    layer.height = info->height;
    layer.buffer = (rt_uint32_t)lcd->lcd_info.framebuffer;
    layer.background.u = 0;

    if (status_success != lcdc_config_layer(lcd->lcd_base, LCD_LAYER_INDEX, &layer, true)) {
        return -RT_ERROR;
    }

    lcdc_turn_on_display(lcd->lcd_base);
    lcdc_enable_interrupt(lcd->lcd_base, LCDC_INT_EN_VSYNC_MASK);
    intc_m_enable_irq_with_priority(lcd->lcd_irq, 7);
    return 0;
}

int drv_lcd_hw_init(void)
{
    rt_err_t result = RT_EOK;
    struct rt_device_graphic_info lcd_info;
    for (uint32_t i = 0; i < sizeof(hpm_lcds) / sizeof(hpm_lcds[0]); i++)
    {
        struct hpm_lcd *lcd = &hpm_lcds[i];
        struct rt_device *device = &lcd->parent;
        lcd->parent.user_data = lcd;
        /* init lcd_lock semaphore */
        result = rt_sem_init(&hpm_lcds[0].lcd_lock, "lcd_lock", 0, RT_IPC_FLAG_FIFO);
        if (result != RT_EOK)
        {
            result = -RT_ENOMEM;
            goto __exit;
        }
        /* config LCD dev info */

        lcd_info.height = PANEL_SIZE_HEIGHT;
        lcd_info.width = PANEL_SIZE_WIDTH;
        lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
        lcd_info.pixel_format = LCD_PIXEL_FORMAT;
        lcd_info.framebuffer = lcdc_framebuffer;
        /* register lcd device */
        rt_device_register(device, hpm_lcds[i].bus_name, RT_DEVICE_FLAG_RDWR);
        board_init_lcd();
        if (hpm_lcdc_init(&hpm_lcds[i], &lcd_info) != RT_EOK)
        {
            result = -RT_ERROR;
            goto __exit;
        }
__exit:
        if (result != RT_EOK)
        {
            rt_sem_delete(&hpm_lcds[i].lcd_lock);
        }
        return result;
    }
}
INIT_BOARD_EXPORT(drv_lcd_hw_init);

#endif /* BSP_USING_RTT_LCD_DRIVER */
