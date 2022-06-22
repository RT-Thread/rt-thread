/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-08-28     WillianChan   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <drv_lcd.h>
#include "rttlogo.h"
#ifdef BSP_USING_LCD_QRCODE
#include <lcd_qrcode.h>
#endif /* BSP_USING_LCD_QRCODE */

static int lcd_sample(void)
{
    lcd_clear(WHITE);
    lcd_show_image(0, 0, 240, 69, image_rttlogo);
    lcd_set_color(WHITE, BLACK);
    lcd_show_string(10, 69, 24, "Hello, RT-Thread!");
    lcd_draw_line(0, 69+24, 240, 69+24);
#ifdef BSP_USING_LCD_QRCODE
    lcd_show_qrcode(54, 69+24+6, 4, ECC_LOW, "https://www.rt-thread.org/", 4);
#endif /* BSP_USING_LCD_QRCODE */

    return RT_EOK;
}
INIT_APP_EXPORT(lcd_sample);
