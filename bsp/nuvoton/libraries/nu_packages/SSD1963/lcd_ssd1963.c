/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-2-23       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(NU_PKG_USING_SSD1963)

#include <rtdevice.h>
#include <lcd_ssd1963.h>

#if defined(NU_PKG_SSD1963_WITH_OFFSCREEN_FRAMEBUFFER)
    #if !defined(NU_PKG_SSD1963_LINE_BUFFER_NUMBER)
        #define NU_PKG_SSD1963_LINE_BUFFER_NUMBER   YSIZE_PHYS
    #endif
#endif

#define ssd1963_delay_ms(ms)    rt_thread_mdelay(ms)
static void ssd1963_fillscreen(rt_uint16_t color);

static struct rt_device_graphic_info g_SSD1963Info =
{
    .bits_per_pixel = 16,
    .pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565,
    .framebuffer = RT_NULL,
    .width = XSIZE_PHYS,
    .pitch = XSIZE_PHYS * 2,
    .height = YSIZE_PHYS
};

static rt_err_t ssd1963_pin_init(void)
{
    rt_pin_mode(BOARD_USING_SSD1963_PIN_DC, PIN_MODE_OUTPUT);
    rt_pin_mode(BOARD_USING_SSD1963_PIN_RESET, PIN_MODE_OUTPUT);
    rt_pin_mode(BOARD_USING_SSD1963_PIN_BACKLIGHT, PIN_MODE_OUTPUT);
    rt_pin_mode(BOARD_USING_SSD1963_PIN_DISPLAY, PIN_MODE_OUTPUT);

    CLR_RS;
    CLR_RST;
    SET_BACKLIGHT_OFF;
    SET_DISP_OFF;

    return RT_EOK;
}

static rt_err_t ssd1963_lcd_init(rt_device_t dev)
{
    /* Hardware reset */
    SET_RST;
    ssd1963_delay_ms(5);     // Delay 5ms

    CLR_RST;
    ssd1963_delay_ms(20);    // Delay 20ms

    SET_RST;
    ssd1963_delay_ms(40);    // Delay 40ms

    /* Initial control registers */
    ssd1963_send_cmd(0x01);    //Software reset
    ssd1963_delay_ms(10);

    ssd1963_send_cmd(0xe0);    //Start PLL. Before the start, the system was operated with the crystal oscillator or clock input.
    ssd1963_send_cmd_parameter(0x01);   //0: Disable PLL, 1:Enable PLL.

    ssd1963_delay_ms(50);

    ssd1963_send_cmd(0xe0);
    ssd1963_send_cmd_parameter(0x03);   //0: Disable PLL, 1:Enable PLL. 3:Enable+LOCK PLL
    ssd1963_delay_ms(5);

    ssd1963_send_cmd(0xb0);    //SET LCD MODE  SET TFT MODE
    ssd1963_send_cmd_parameter(0x20);   //SET 24Bit, Disable TFT FRC & dithering, DCLK in falling edge, LLINE Active low, LFRAME Active low
    ssd1963_send_cmd_parameter(0x00);   //SET TFT mode
    ssd1963_send_cmd_parameter(0x01);   //SET horizontal size=480-1 HightByte
    ssd1963_send_cmd_parameter(0xdf);   //SET horizontal size=480-1 LowByte
    ssd1963_send_cmd_parameter(0x01);   //SET vertical size=272-1 HightByte
    ssd1963_send_cmd_parameter(0x0f);   //SET vertical size=272-1 LowByte
    ssd1963_send_cmd_parameter(0x00);   //SET even/odd line RGB seq.=RGB

    ssd1963_send_cmd(0xf0);    //SET pixel data I/F format=16bit(565 format)
    ssd1963_send_cmd_parameter(0x03);

    //ssd1963_send_cmd(0xf0);    //SET pixel data I/F format=8bit (666 format)
    //ssd1963_send_cmd_parameter(0x00);

    ssd1963_send_cmd(0x36);    // SET read from frame buffer to the display is RGB
    ssd1963_send_cmd_parameter(0x00);

    ssd1963_send_cmd(0xe2);
    ssd1963_send_cmd_parameter(0x1d);
    ssd1963_send_cmd_parameter(0x02);
    ssd1963_send_cmd_parameter(0x54);

    ssd1963_send_cmd(0xe6);    //SET pixel clock frequency
    ssd1963_send_cmd_parameter(0x01);
    ssd1963_send_cmd_parameter(0x99);
    ssd1963_send_cmd_parameter(0x9a);

    ssd1963_send_cmd(0xb4);    //SET HBP,
    ssd1963_send_cmd_parameter(0x02);   //SET HSYNC Tatol = 525
    ssd1963_send_cmd_parameter(0x0d);
    ssd1963_send_cmd_parameter(0x00);   //SET HBP = 20
    ssd1963_send_cmd_parameter(0x14);
    ssd1963_send_cmd_parameter(0x05);    //SET VBP 5
    ssd1963_send_cmd_parameter(0x00);    //SET Hsync pulse start position
    ssd1963_send_cmd_parameter(0x00);
    ssd1963_send_cmd_parameter(0x00);    //SET Hsync pulse subpixel start position

    ssd1963_send_cmd(0xb6);     //SET VBP,
    ssd1963_send_cmd_parameter(0x01);    //SET Vsync total 292
    ssd1963_send_cmd_parameter(0x24);
    ssd1963_send_cmd_parameter(0x00);    //SET VBP = 10
    ssd1963_send_cmd_parameter(0x0a);
    ssd1963_send_cmd_parameter(0x05);    //SET Vsync pulse 5
    ssd1963_send_cmd_parameter(0x00);    //SET Vsync pulse start position
    ssd1963_send_cmd_parameter(0x00);

    ssd1963_send_cmd(0x29);    //SET display on
    ssd1963_delay_ms(5);

    ssd1963_fillscreen(0);

    SET_DISP_ON;

    SET_BACKLIGHT_ON;

    return RT_EOK;
}

#if defined(NU_PKG_SSD1963_WITH_OFFSCREEN_FRAMEBUFFER)
static void ssd1963_fillrect(uint16_t *pixels, struct rt_device_rect_info *pRectInfo)
{
    ssd1963_set_column(pRectInfo->x, pRectInfo->x + pRectInfo->width - 1);
    ssd1963_set_page(pRectInfo->y, pRectInfo->y + pRectInfo->height - 1);
    ssd1963_send_cmd(0x2c);

    ssd1963_send_pixels(pixels, pRectInfo->height * pRectInfo->width * 2);
}
#endif

static void ssd1963_fillscreen(rt_uint16_t color)
{
#if defined(NU_PKG_SSD1963_WITH_OFFSCREEN_FRAMEBUFFER)
    struct rt_device_rect_info rectinfo;
    int filled_line_num = 0;

    while (filled_line_num < YSIZE_PHYS)
    {
        int pixel_count;
        rectinfo.x = 0;
        rectinfo.y = filled_line_num;
        rectinfo.width = XSIZE_PHYS;
        rectinfo.height = (NU_PKG_SSD1963_LINE_BUFFER_NUMBER < YSIZE_PHYS) ? NU_PKG_SSD1963_LINE_BUFFER_NUMBER : YSIZE_PHYS;

        pixel_count = XSIZE_PHYS * NU_PKG_SSD1963_LINE_BUFFER_NUMBER;
        rt_uint16_t *pu16ShadowBuf = (rt_uint16_t *)g_SSD1963Info.framebuffer;

        while (pixel_count > 0)
        {
            *pu16ShadowBuf++ = color;
            pixel_count--;
        }
        ssd1963_fillrect((uint16_t *)g_SSD1963Info.framebuffer, &rectinfo);
        filled_line_num += NU_PKG_SSD1963_LINE_BUFFER_NUMBER;
    }
#else
    ssd1963_set_column(0, (XSIZE_PHYS - 1));
    ssd1963_set_page(0, (YSIZE_PHYS - 1));
    ssd1963_send_cmd(0x2c);

    for (int i = 0; i < (XSIZE_PHYS * YSIZE_PHYS); i++)
        ssd1963_send_pixel_data(color);
#endif
}

static void ssd1963_lcd_set_pixel(const char *color, int x, int y)
{
    ssd1963_set_column(x, x);
    ssd1963_set_page(y, y);
    ssd1963_send_cmd(0x2c);
    ssd1963_send_pixel_data(*(uint16_t *)color);
}

static void ssd1963_lcd_draw_hline(const char *pixel, int x1, int x2, int y)
{
    ssd1963_set_column(x1, x2);
    ssd1963_set_page(y, y);
    ssd1963_send_cmd(0x2c);

    for (; x1 < x2; x1++)
        ssd1963_send_pixel_data(*(uint16_t *)pixel);
}

static void ssd1963_lcd_draw_vline(const char *pixel, int x, int y1, int y2)
{
    ssd1963_set_column(x, x);
    ssd1963_set_page(y1, y2);
    ssd1963_send_cmd(0x2c);

    for (; y1 < y2; y1++)
        ssd1963_send_pixel_data(*(uint16_t *)pixel);
}

static void ssd1963_lcd_blit_line(const char *pixels, int x, int y, rt_size_t size)
{
    rt_uint16_t *ptr = (rt_uint16_t *)pixels;

    ssd1963_set_column(x, x + size);
    ssd1963_set_page(y, y);
    ssd1963_send_cmd(0x2c);

    while (size--)
        ssd1963_send_pixel_data(*ptr++);
}

static rt_err_t ssd1963_lcd_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t ssd1963_lcd_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t ssd1963_lcd_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info;

        info = (struct rt_device_graphic_info *) args;
        RT_ASSERT(info != RT_NULL);
        rt_memcpy(args, (void *)&g_SSD1963Info, sizeof(struct rt_device_graphic_info));
    }
    break;

    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
#if defined(NU_PKG_SSD1963_WITH_OFFSCREEN_FRAMEBUFFER)
        struct rt_device_rect_info *psRectInfo = (struct rt_device_rect_info *)args;
        rt_uint16_t *pixels  = (rt_uint16_t *)g_SSD1963Info.framebuffer;
        RT_ASSERT(args);

        ssd1963_fillrect(pixels, psRectInfo);
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
static struct rt_device_graphic_ops ssd1963_ops =
{
    ssd1963_lcd_set_pixel,
    ssd1963_lcd_get_pixel,
    ssd1963_lcd_draw_hline,
    ssd1963_lcd_draw_vline,
    ssd1963_lcd_blit_line
};

int rt_hw_lcd_ssd1963_init(void)
{
    ssd1963_pin_init();

    /* register lcd device */
    lcd_device.type = RT_Device_Class_Graphic;
    lcd_device.init = ssd1963_lcd_init;
    lcd_device.open = ssd1963_lcd_open;
    lcd_device.close = ssd1963_lcd_close;
    lcd_device.control = ssd1963_lcd_control;
    lcd_device.read = RT_NULL;
    lcd_device.write = RT_NULL;

    lcd_device.user_data = &ssd1963_ops;

#if defined(NU_PKG_SSD1963_WITH_OFFSCREEN_FRAMEBUFFER)
    g_SSD1963Info.framebuffer = rt_malloc_align((g_SSD1963Info.pitch * NU_PKG_SSD1963_LINE_BUFFER_NUMBER) + 32, 32);
    RT_ASSERT(g_SSD1963Info.framebuffer != RT_NULL);
    g_SSD1963Info.smem_len = g_SSD1963Info.pitch * NU_PKG_SSD1963_LINE_BUFFER_NUMBER;
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

    ssd1963_lcd_init(NULL);

    color = 0x0; //Black, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ssd1963_fillscreen(color);
    ssd1963_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0xffff; //White, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ssd1963_fillscreen(color);
    ssd1963_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0x1f; //Blue, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ssd1963_fillscreen(color);
    ssd1963_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0x07e0; //Green, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ssd1963_fillscreen(color);
    ssd1963_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0xf800; //Red, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    ssd1963_fillscreen(color);
    ssd1963_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0xffff; //White, RGB
    rt_kprintf("lcd draw hline, pixel: 0x%X, x1: %d, x2: %d, y: %d\n", color, x, x + 20, y);
    ssd1963_lcd_draw_hline((const char *)&color, x, x + 20, y);

    color = 0xffff; //White, RGB
    rt_kprintf("lcd draw vline, pixel: 0x%X, x: %d, y: %d\n", color, y, y + 20);
    ssd1963_lcd_draw_vline((const char *)&color, x, y, y + 20);

    for (i = 0; i < LINE_LEN; i++)
        pixels[i] = 20 + i * 5;

    x = y = 50;
    rt_kprintf("lcd blit line, start: x: %d, y: %d\n", x, y);
    ssd1963_lcd_blit_line((const char *)&pixels[0], x, y, LINE_LEN);

    x = y = 200;
    color = 0x07E0; //Green, RGB
    rt_kprintf("lcd set pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
    ssd1963_lcd_set_pixel((const char *)&color, x, y);
    color = 0x0;
    ssd1963_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    x = y = 200;
    color = 0x1f; //Blue, RGB
    rt_kprintf("lcd set pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
    ssd1963_lcd_set_pixel((const char *)&color, x, y);
    color = 0x0;
    ssd1963_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    x = y = 200;
    color = 0xf800; //Red, RGB
    rt_kprintf("lcd set pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
    ssd1963_lcd_set_pixel((const char *)&color, x, y);
    color = 0x0;
    ssd1963_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
}
MSH_CMD_EXPORT(lcd_test, test lcd display);
#endif

#endif /* if defined(NU_PKG_USING_SSD1963) */
