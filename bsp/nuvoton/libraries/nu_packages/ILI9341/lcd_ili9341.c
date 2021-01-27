/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(NU_PKG_USING_ILI9341)

#include <rtdevice.h>
#include <lcd_ili9341.h>

static struct rt_device_graphic_info g_Ili9341Info =
{
    .bits_per_pixel = 16,
    .pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565,
    .framebuffer = RT_NULL,
    .width = XSIZE_PHYS,
    .height = YSIZE_PHYS
};

static void ili9341_delay_ms(rt_uint32_t nms)
{
    rt_thread_mdelay(nms);
}

static rt_err_t ili9341_pin_init(void)
{
    rt_pin_mode(BOARD_USING_ILI9341_PIN_DC, PIN_MODE_OUTPUT);
    rt_pin_mode(BOARD_USING_ILI9341_PIN_RESET, PIN_MODE_OUTPUT);
    rt_pin_mode(BOARD_USING_ILI9341_PIN_BACKLIGHT, PIN_MODE_OUTPUT);

    SET_RS;
    SET_RST;
    SET_BACKLIGHT_OFF;

    return RT_EOK;
}

static rt_err_t ili9341_lcd_init(rt_device_t dev)
{
    /* Hardware reset */
    SET_RST;
    ili9341_delay_ms(5);     // Delay 5ms

    CLR_RST;
    ili9341_delay_ms(20);    // Delay 20ms

    SET_RST;
    ili9341_delay_ms(40);    // Delay 40ms

    /* Initial control registers */
    ili9341_send_cmd(0xCB);
    ili9341_send_cmd_parameter(0x39);
    ili9341_send_cmd_parameter(0x2C);
    ili9341_send_cmd_parameter(0x00);
    ili9341_send_cmd_parameter(0x34);
    ili9341_send_cmd_parameter(0x02);

    ili9341_send_cmd(0xCF);
    ili9341_send_cmd_parameter(0x00);
    ili9341_send_cmd_parameter(0xC1);
    ili9341_send_cmd_parameter(0x30);

    ili9341_send_cmd(0xE8);
    ili9341_send_cmd_parameter(0x85);
    ili9341_send_cmd_parameter(0x00);
    ili9341_send_cmd_parameter(0x78);

    ili9341_send_cmd(0xEA);
    ili9341_send_cmd_parameter(0x00);
    ili9341_send_cmd_parameter(0x00);

    ili9341_send_cmd(0xED);
    ili9341_send_cmd_parameter(0x64);
    ili9341_send_cmd_parameter(0x03);
    ili9341_send_cmd_parameter(0x12);
    ili9341_send_cmd_parameter(0x81);

    ili9341_send_cmd(0xF7);
    ili9341_send_cmd_parameter(0x20);

    ili9341_send_cmd(0xC0);
    ili9341_send_cmd_parameter(0x23);

    ili9341_send_cmd(0xC1);
    ili9341_send_cmd_parameter(0x10);

    ili9341_send_cmd(0xC5);
    ili9341_send_cmd_parameter(0x3e);
    ili9341_send_cmd_parameter(0x28);

    ili9341_send_cmd(0xC7);
    ili9341_send_cmd_parameter(0x86);

    ili9341_send_cmd(0x36);

    if (g_Ili9341Info.width == 240)
        ili9341_send_cmd_parameter(0x48); // for 240x320
    else
        ili9341_send_cmd_parameter(0xE8); // for 320x240

    ili9341_send_cmd(0x3A);
    ili9341_send_cmd_parameter(0x55);

    ili9341_send_cmd(0xB1);
    ili9341_send_cmd_parameter(0x00);
    ili9341_send_cmd_parameter(0x18);

    ili9341_send_cmd(0xB6);
    ili9341_send_cmd_parameter(0x08);
    ili9341_send_cmd_parameter(0x82);
    ili9341_send_cmd_parameter(0x27);

    ili9341_send_cmd(0xF2);
    ili9341_send_cmd_parameter(0x00);

    ili9341_send_cmd(0x26);
    ili9341_send_cmd_parameter(0x01);

    ili9341_send_cmd(0xE0);
    ili9341_send_cmd_parameter(0x0F);
    ili9341_send_cmd_parameter(0x31);
    ili9341_send_cmd_parameter(0x2B);
    ili9341_send_cmd_parameter(0x0C);
    ili9341_send_cmd_parameter(0x0E);
    ili9341_send_cmd_parameter(0x08);
    ili9341_send_cmd_parameter(0x4E);
    ili9341_send_cmd_parameter(0xF1);
    ili9341_send_cmd_parameter(0x37);
    ili9341_send_cmd_parameter(0x07);
    ili9341_send_cmd_parameter(0x10);
    ili9341_send_cmd_parameter(0x03);
    ili9341_send_cmd_parameter(0x0E);
    ili9341_send_cmd_parameter(0x09);
    ili9341_send_cmd_parameter(0x00);

    ili9341_send_cmd(0xE1);
    ili9341_send_cmd_parameter(0x00);
    ili9341_send_cmd_parameter(0x0E);
    ili9341_send_cmd_parameter(0x14);
    ili9341_send_cmd_parameter(0x03);
    ili9341_send_cmd_parameter(0x11);
    ili9341_send_cmd_parameter(0x07);
    ili9341_send_cmd_parameter(0x31);
    ili9341_send_cmd_parameter(0xC1);
    ili9341_send_cmd_parameter(0x48);
    ili9341_send_cmd_parameter(0x08);
    ili9341_send_cmd_parameter(0x0F);
    ili9341_send_cmd_parameter(0x0C);
    ili9341_send_cmd_parameter(0x31);
    ili9341_send_cmd_parameter(0x36);
    ili9341_send_cmd_parameter(0x0F);

    ili9341_send_cmd(0x11);

    ili9341_delay_ms(120);   // Delay 120ms

    ili9341_send_cmd(0x29);  //Display on

    SET_BACKLIGHT_ON;

    return RT_EOK;
}

#if defined(NU_PKG_ILI9341_WITH_OFFSCREEN_FRAMEBUFFER)
static void ili9341_fillrect(uint16_t *pixels, struct rt_device_rect_info *pRectInfo)
{
    ili9341_set_column(pRectInfo->x, pRectInfo->x + pRectInfo->width);
    ili9341_set_page(pRectInfo->y, pRectInfo->y + pRectInfo->height);
    ili9341_send_cmd(0x2c);

    ili9341_send_pixels(pixels, pRectInfo->height * pRectInfo->width * 2);
}
#endif

static void ili9341_fillscreen(rt_uint16_t color)
{
#if defined(NU_PKG_ILI9341_WITH_OFFSCREEN_FRAMEBUFFER)
    struct rt_device_rect_info rectinfo = { 0, 0, XSIZE_PHYS,  YSIZE_PHYS };
    int pixel_count = XSIZE_PHYS * YSIZE_PHYS;
    rt_uint16_t *pu16ShadowBuf = (rt_uint16_t *)g_Ili9341Info.framebuffer;

    while (pixel_count--)
    {
        *pu16ShadowBuf++ = color;
    }
    ili9341_fillrect((uint16_t *)g_Ili9341Info.framebuffer, &rectinfo);
#else
    ili9341_set_column(0, (XSIZE_PHYS - 1));
    ili9341_set_page(0, (YSIZE_PHYS - 1));
    ili9341_send_cmd(0x2c);

    for (int i = 0; i < (XSIZE_PHYS * YSIZE_PHYS); i++)
        ili9341_send_pixel_data(color);
#endif
}

static void ili9341_lcd_set_pixel(const char *color, int x, int y)
{
    ili9341_set_column(x, x);
    ili9341_set_page(y, y);
    ili9341_send_cmd(0x2c);
    ili9341_send_pixel_data(*(uint16_t *)color);
}

static void ili9341_lcd_draw_hline(const char *pixel, int x1, int x2, int y)
{
    ili9341_set_column(x1, x2);
    ili9341_set_page(y, y);
    ili9341_send_cmd(0x2c);

    for (; x1 < x2; x1++)
        ili9341_send_pixel_data(*(uint16_t *)pixel);
}

static void ili9341_lcd_draw_vline(const char *pixel, int x, int y1, int y2)
{
    ili9341_set_column(x, x);
    ili9341_set_page(y1, y2);
    ili9341_send_cmd(0x2c);

    for (; y1 < y2; y1++)
        ili9341_send_pixel_data(*(uint16_t *)pixel);
}

static void ili9341_lcd_blit_line(const char *pixels, int x, int y, rt_size_t size)
{
    rt_uint16_t *ptr = (rt_uint16_t *)pixels;

    ili9341_set_column(x, x + size);
    ili9341_set_page(y, y);
    ili9341_send_cmd(0x2c);

    while (size--)
        ili9341_send_pixel_data(*ptr++);
}

static rt_err_t ili9341_lcd_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t ili9341_lcd_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t ili9341_lcd_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info;

        info = (struct rt_device_graphic_info *) args;
        RT_ASSERT(info != RT_NULL);
        rt_memcpy(args, (void *)&g_Ili9341Info, sizeof(struct rt_device_graphic_info));
    }
    break;

    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
#if defined(NU_PKG_ILI9341_WITH_OFFSCREEN_FRAMEBUFFER)
        RT_ASSERT(args != RT_NULL);
        ili9341_fillrect((uint16_t *)g_Ili9341Info.framebuffer, (struct rt_device_rect_info *) args);
#else
        /* nothong to be done */
#endif
    }
    break;
    default:
        break;
    }

    return RT_EOK;
}

static struct rt_device lcd_device;
static struct rt_device_graphic_ops ili9341_ops =
{
    ili9341_lcd_set_pixel,
    ili9341_lcd_get_pixel,
    ili9341_lcd_draw_hline,
    ili9341_lcd_draw_vline,
    ili9341_lcd_blit_line
};

int rt_hw_lcd_ili9341_init(void)
{
    ili9341_pin_init();

    /* register lcd device */
    lcd_device.type = RT_Device_Class_Graphic;
    lcd_device.init = ili9341_lcd_init;
    lcd_device.open = ili9341_lcd_open;
    lcd_device.close = ili9341_lcd_close;
    lcd_device.control = ili9341_lcd_control;
    lcd_device.read = RT_NULL;
    lcd_device.write = RT_NULL;

    lcd_device.user_data = &ili9341_ops;

#if defined(NU_PKG_ILI9341_WITH_OFFSCREEN_FRAMEBUFFER)
    g_Ili9341Info.framebuffer = rt_malloc_align(g_Ili9341Info.bits_per_pixel / 2 * g_Ili9341Info.height * g_Ili9341Info.width, 32);
    RT_ASSERT(g_Ili9341Info.framebuffer != RT_NULL);
#endif

    /* register graphic device driver */
    rt_device_register(&lcd_device, "lcd", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

    return 0;
}

#ifdef RT_USING_FINSH
#define LINE_LEN 32
static void lcd_test(int argc, char *argv[])
{
    uint16_t pixels[LINE_LEN];
    uint16_t color;
    int x, y, i;
    x = y = 100;

    ili9341_lcd_init(NULL);

    color = 0x0; //Black, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ili9341_fillscreen(color);
    ili9341_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0xffff; //White, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ili9341_fillscreen(color);
    ili9341_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0x1f; //Blue, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ili9341_fillscreen(color);
    ili9341_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0x07e0; //Green, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ili9341_fillscreen(color);
    ili9341_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0xf800; //Red, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ili9341_fillscreen(color);
    ili9341_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0xffff; //White, RGB
    rt_kprintf("lcd draw hline, pixel: 0x%X, x1: %d, x2: %d, y: %d\n", color, x, x + 20, y);
    ili9341_lcd_draw_hline((const char *)&color, x, x + 20, y);

    color = 0xffff; //White, RGB
    rt_kprintf("lcd draw vline, pixel: 0x%X, x: %d, y: %d\n", color, y, y + 20);
    ili9341_lcd_draw_vline((const char *)&color, x, y, y + 20);

    for (i = 0; i < LINE_LEN; i++)
        pixels[i] = 20 + i * 5;

    x = y = 50;
    rt_kprintf("lcd blit line, start: x: %d, y: %d\n", x, y);
    ili9341_lcd_blit_line((const char *)&pixels[0], x, y, LINE_LEN);

    x = y = 200;
    color = 0x07E0; //Green, RGB
    rt_kprintf("lcd set pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
    ili9341_lcd_set_pixel((const char *)&color, x, y);
    color = 0x0;
    ili9341_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    x = y = 200;
    color = 0x1f; //Blue, RGB
    rt_kprintf("lcd set pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
    ili9341_lcd_set_pixel((const char *)&color, x, y);
    color = 0x0;
    ili9341_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    x = y = 200;
    color = 0xf800; //Red, RGB
    rt_kprintf("lcd set pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
    ili9341_lcd_set_pixel((const char *)&color, x, y);
    color = 0x0;
    ili9341_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
}
MSH_CMD_EXPORT(lcd_test, test lcd display);
#endif

#endif /* if defined(NU_PKG_USING_ILI9341) */
