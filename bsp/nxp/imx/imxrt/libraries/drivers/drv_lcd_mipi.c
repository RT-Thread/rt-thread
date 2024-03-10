/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-10-30     Tanek        the first version
 * 2023-09-25     Frogrey      export MIPI DSI config parameters.
 */

#include <rtthread.h>

#ifdef BSP_USING_LCD_MIPI

#include "display_support.h"
#include "drv_lcd_mipi.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_elcdif.h"
#include "drv_gpio.h"

#define LOG_TAG             "drv.lcd_mipi"
#include <drv_log.h>

#if !defined(LCD_MIPI_WIDTH) || !defined(LCD_MIPI_HEIGHT)
#error "Please config mipi dsi pixel parameters."
#endif

#if !defined(LCD_MIPI_HFP) || !defined(LCD_MIPI_HBP) || !defined(LCD_MIPI_HSW) || \
    !defined(LCD_MIPI_VFP) || !defined(LCD_MIPI_VBP) || !defined(LCD_MIPI_VSW)
#error "Please config mipi dsi timing parameters."
#endif

#if !defined(LCD_MIPI_BL_PIN) || !defined(LCD_MIPI_RST_PIN)
#error "Please config mipi dsi backlight or reset pin."
#endif

struct imxrt_lcd_mipi
{
    struct rt_device device;
    struct rt_device_graphic_info info;
};

static struct imxrt_lcd_mipi lcd_mipi;

static rt_err_t imxrt_lcd_mipi_init(rt_device_t device)
{
    RT_ASSERT(device != RT_NULL);

    BOARD_PrepareDisplayController();

    /* MIPI DSI DEVICE INFORMATION*/
    lcd_mipi.info.width          = LCD_MIPI_WIDTH;
    lcd_mipi.info.height         = LCD_MIPI_HEIGHT;
#if DEMO_USE_XRGB8888
    lcd_mipi.info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_ARGB888;
    lcd_mipi.info.bits_per_pixel = 32;
#elif DEMO_USE_RGB565
    lcd_mipi.info.pixel_format   = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    lcd_mipi.info.bits_per_pixel = 16;
#else
    lcd_mipi.info.bits_per_pixel = 16;
#endif

    return RT_EOK;
}

static rt_err_t imxrt_lcd_mipi_control(rt_device_t device, int cmd, void *args)
{
    switch(cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        break;

    case RTGRAPHIC_CTRL_POWERON:
        rt_pin_write(LCD_MIPI_BL_PIN, PIN_HIGH);
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
        rt_pin_write(LCD_MIPI_BL_PIN, PIN_LOW);
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
        rt_memcpy(args, &lcd_mipi.info, sizeof(lcd_mipi.info));
        break;

    case RTGRAPHIC_CTRL_SET_MODE:
        break;
    }

    return RT_EOK;
}

int rt_hw_lcd_mipi_init(void)
{
    rt_err_t ret;

    lcd_mipi.device.type    = RT_Device_Class_Graphic;
    lcd_mipi.device.init    = imxrt_lcd_mipi_init;
    lcd_mipi.device.open    = RT_NULL;
    lcd_mipi.device.close   = RT_NULL;
    lcd_mipi.device.read    = RT_NULL;
    lcd_mipi.device.write   = RT_NULL;
    lcd_mipi.device.control = imxrt_lcd_mipi_control;

    lcd_mipi.device.user_data = (void *)&lcd_mipi.info;

    ret = rt_device_register(&lcd_mipi.device, "lcd_mipi", RT_DEVICE_FLAG_RDWR);

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_lcd_mipi_init);

#endif /* BSP_USING_LCD_MIPI */
