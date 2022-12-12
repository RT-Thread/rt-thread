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

#if defined(NU_PKG_USING_FSA506)

#include <rtdevice.h>
#include <lcd_fsa506.h>

#if defined(NU_PKG_FSA506_WITH_OFFSCREEN_FRAMEBUFFER)
    #if !defined(NU_PKG_FSA506_LINE_BUFFER_NUMBER)
        #define NU_PKG_FSA506_LINE_BUFFER_NUMBER   YSIZE_PHYS
    #endif
#endif

#define fsa506_delay_ms(ms)    rt_thread_mdelay(ms)
static void fsa506_fillscreen(rt_uint16_t color);

static struct rt_device_graphic_info g_FSA506Info =
{
    .bits_per_pixel = 16,
    .pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565,
    .framebuffer = RT_NULL,
    .width = XSIZE_PHYS,
    .pitch = XSIZE_PHYS * 2,
    .height = YSIZE_PHYS
};

static rt_err_t fsa506_pin_init(void)
{
    SET_BACKLIGHT_OFF;
    rt_pin_mode(BOARD_USING_FSA506_PIN_BACKLIGHT, PIN_MODE_OUTPUT);

    CLR_RS;
    CLR_RST;
    rt_pin_mode(BOARD_USING_FSA506_PIN_DC, PIN_MODE_OUTPUT);
    rt_pin_mode(BOARD_USING_FSA506_PIN_RESET, PIN_MODE_OUTPUT);

    return RT_EOK;
}

static rt_err_t fsa506_lcd_init(rt_device_t dev)
{
    SET_BACKLIGHT_OFF;

    /* Hardware reset */
    CLR_RST;
    fsa506_delay_ms(100);    // Delay 100ms

    SET_RST;
    fsa506_delay_ms(500);    // Delay 500ms

    fsa506_write_reg(0x40, 0x12);   // [5]:PLL control 20~100MHz [2:1]:Output Driving 8mA, [0]:Output slew Fast
    fsa506_write_reg(0x41, 0x05);   // PLL Programmable pre-divider: 5
    fsa506_write_reg(0x42, 0x06);   // PLL Programmable loop divider: 6

    /* Set the panel X size */
    fsa506_write_reg(0x08, (XSIZE_PHYS >> 8)); //Set the panel X size H[1.0]
    fsa506_write_reg(0x09, (XSIZE_PHYS));    //Set the panel X size L[7:0]

    /* Memory write start address */
    fsa506_write_reg(0x0a, 0x00); //[17:16] bits of memory write start address
    fsa506_write_reg(0x0b, 0x00); //[15:8] bits of memory write start address
    fsa506_write_reg(0x0c, 0x00); //[7:0] bits of memory write start address

    /* Clock & format */
    fsa506_write_reg(0x10, 0x0D); //[0-1] : 20MHz, [2]: Parallel panel, [3]: Normal operation
    fsa506_write_reg(0x11, 0x05); //[3-5]: RGB, [0-2]BGR

    /* For TFT output timing adjust */
    fsa506_write_reg(0x12, 0x00);                      //Hsync start position H-Byte
    fsa506_write_reg(0x13, 0x00);                      //Hsync start position L-Byte
    fsa506_write_reg(0x14, (41 >> 8));        //Hsync pulse width H-Byte
    fsa506_write_reg(0x15, (41));             //Hsync pulse width L-Byte

    fsa506_write_reg(0x16, (43 >> 8));        //DE pulse start position H-Byte
    fsa506_write_reg(0x17, (43));             //DE pulse start position L-Byte
    fsa506_write_reg(0x18, (XSIZE_PHYS >> 8)); //DE pulse width H-Byte
    fsa506_write_reg(0x19, (XSIZE_PHYS));     //DE pulse width L-Byte
    fsa506_write_reg(0x1a, (525 >> 8));       //Hsync total clocks H-Byte
    fsa506_write_reg(0x1b, (525));            //Hsync total clocks H-Byte
    fsa506_write_reg(0x1c, 0x00);                      //Vsync start position H-Byte
    fsa506_write_reg(0x1d, 0x00);                      //Vsync start position L-Byte
    fsa506_write_reg(0x1e, (10 >> 8));        //Vsync pulse width H-Byte
    fsa506_write_reg(0x1f, (10));             //Vsync pulse width L-Byte
    fsa506_write_reg(0x20, (12 >> 8));        //Vertical DE pulse start position H-Byte
    fsa506_write_reg(0x21, (12));             //Vertical DE pulse start position L-Byte
    fsa506_write_reg(0x22, (YSIZE_PHYS >> 8)); //Vertical Active width H-Byte
    fsa506_write_reg(0x23, (YSIZE_PHYS));     //Vertical Active width H-Byte
    fsa506_write_reg(0x24, (286 >> 8));       //Vertical total width H-Byte
    fsa506_write_reg(0x25, (286));            //Vertical total width L-Byte

    fsa506_write_reg(0x26, 0x00);                      //Memory read start address
    fsa506_write_reg(0x27, 0x00);                      //Memory read start address
    fsa506_write_reg(0x28, 0x00);                      //Memory read start address
    fsa506_write_reg(0x29, 0x01);                      //[0] Load output timing related setting (H sync., V sync. and DE) to take effect

    //[7:4] Reserved
    //[3]   Output pin X_DCON level control
    //[2]   Output clock inversion     0: Normal 1: Inverse
    //[1:0] Image rotate
    //      00: 0? 01: 90? 10: 270?11: 180?
    fsa506_write_reg(0x2d, (1 << 2) | 0x08);

    /* Set the Horizontal offset  */
    fsa506_write_reg(0x30, 0x00);                        //_H byte H-Offset[3:0]
    fsa506_write_reg(0x31, 0x00);                        //_L byte H-Offset[7:0]
    fsa506_write_reg(0x32, 0x00);                        //_H byte V-Offset[3:0]
    fsa506_write_reg(0x33, 0x00);                        //_L byte V-Offset[7:0]
    fsa506_write_reg(0x34, (XSIZE_PHYS >> 8));  //H byte H-def[3:0]
    fsa506_write_reg(0x35, (XSIZE_PHYS));       //_L byte H-def[7:0]
    fsa506_write_reg(0x36, ((2 * YSIZE_PHYS) >> 8)); //[3:0] MSB of image vertical physical resolution in memory
    fsa506_write_reg(0x37, (2 * YSIZE_PHYS));   //[7:0] LSB of image vertical physical resolution in memory

    fsa506_fillscreen(0);

    SET_BACKLIGHT_ON;

    return RT_EOK;
}

#if defined(NU_PKG_FSA506_WITH_OFFSCREEN_FRAMEBUFFER)
static void fsa506_fillrect(uint16_t *pixels, struct rt_device_rect_info *pRectInfo)
{
    fsa506_set_column(pRectInfo->x, pRectInfo->x + pRectInfo->width - 1);
    fsa506_set_page(pRectInfo->y, pRectInfo->y + pRectInfo->height - 1);

    fsa506_send_cmd(0xC1);
    fsa506_send_pixels(pixels, pRectInfo->height * pRectInfo->width * 2);
    fsa506_send_cmd_done();
}
#endif

static void fsa506_fillscreen(rt_uint16_t color)
{
#if defined(NU_PKG_FSA506_WITH_OFFSCREEN_FRAMEBUFFER)
    struct rt_device_rect_info rectinfo;
    int filled_line_num = 0;

    while (filled_line_num < YSIZE_PHYS)
    {
        int pixel_count;
        rectinfo.x = 0;
        rectinfo.y = filled_line_num;
        rectinfo.width = XSIZE_PHYS;
        rectinfo.height = (NU_PKG_FSA506_LINE_BUFFER_NUMBER < YSIZE_PHYS) ? NU_PKG_FSA506_LINE_BUFFER_NUMBER : YSIZE_PHYS;

        pixel_count = XSIZE_PHYS * NU_PKG_FSA506_LINE_BUFFER_NUMBER;
        rt_uint16_t *pu16ShadowBuf = (rt_uint16_t *)g_FSA506Info.framebuffer;

        while (pixel_count > 0)
        {
            *pu16ShadowBuf++ = color;
            pixel_count--;
        }
        fsa506_fillrect((uint16_t *)g_FSA506Info.framebuffer, &rectinfo);
        filled_line_num += NU_PKG_FSA506_LINE_BUFFER_NUMBER;
    }
#else
    fsa506_set_column(0, (XSIZE_PHYS - 1));
    fsa506_set_page(0, (YSIZE_PHYS - 1));

    fsa506_send_cmd(0xC1);
    for (int i = 0; i < (XSIZE_PHYS * YSIZE_PHYS); i++)
        fsa506_send_pixel_data(color);
    fsa506_send_cmd_done();
#endif
}

static void fsa506_lcd_set_pixel(const char *color, int x, int y)
{
    fsa506_set_column(x, x);
    fsa506_set_page(y, y);

    fsa506_send_cmd(0xC1);
    fsa506_send_pixel_data(*(uint16_t *)color);
    fsa506_send_cmd_done();
}

static void fsa506_lcd_draw_hline(const char *pixel, int x1, int x2, int y)
{
    fsa506_set_column(x1, x2);
    fsa506_set_page(y, y);

    fsa506_send_cmd(0xC1);
    for (; x1 < x2; x1++)
        fsa506_send_pixel_data(*(uint16_t *)pixel);
    fsa506_send_cmd_done();
}

static void fsa506_lcd_draw_vline(const char *pixel, int x, int y1, int y2)
{
    fsa506_set_column(x, x);
    fsa506_set_page(y1, y2);

    fsa506_send_cmd(0xC1);
    for (; y1 < y2; y1++)
        fsa506_send_pixel_data(*(uint16_t *)pixel);
    fsa506_send_cmd_done();
}

static void fsa506_lcd_blit_line(const char *pixels, int x, int y, rt_size_t size)
{
    rt_uint16_t *ptr = (rt_uint16_t *)pixels;

    fsa506_set_column(x, x + size);
    fsa506_set_page(y, y);

    fsa506_send_cmd(0xC1);
    while (size--)
        fsa506_send_pixel_data(*ptr++);
    fsa506_send_cmd_done();
}

static rt_err_t fsa506_lcd_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t fsa506_lcd_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t fsa506_lcd_control(rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info;

        info = (struct rt_device_graphic_info *) args;
        RT_ASSERT(info != RT_NULL);
        rt_memcpy(args, (void *)&g_FSA506Info, sizeof(struct rt_device_graphic_info));
    }
    break;

    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
#if defined(NU_PKG_FSA506_WITH_OFFSCREEN_FRAMEBUFFER)
        struct rt_device_rect_info *psRectInfo = (struct rt_device_rect_info *)args;
        rt_uint16_t *pixels  = (rt_uint16_t *)g_FSA506Info.framebuffer;
        RT_ASSERT(args);

        fsa506_fillrect(pixels, psRectInfo);
#else
        /* nothong to be done */
#endif
    }
    break;

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static struct rt_device lcd_device;
static struct rt_device_graphic_ops fsa506_ops =
{
    fsa506_lcd_set_pixel,
    fsa506_lcd_get_pixel,
    fsa506_lcd_draw_hline,
    fsa506_lcd_draw_vline,
    fsa506_lcd_blit_line
};

int rt_hw_lcd_fsa506_init(void)
{
    fsa506_pin_init();

    /* register lcd device */
    lcd_device.type = RT_Device_Class_Graphic;
    lcd_device.init = fsa506_lcd_init;
    lcd_device.open = fsa506_lcd_open;
    lcd_device.close = fsa506_lcd_close;
    lcd_device.control = fsa506_lcd_control;
    lcd_device.read = RT_NULL;
    lcd_device.write = RT_NULL;

    lcd_device.user_data = &fsa506_ops;

#if defined(NU_PKG_FSA506_WITH_OFFSCREEN_FRAMEBUFFER)
    g_FSA506Info.framebuffer = rt_malloc_align((g_FSA506Info.pitch * NU_PKG_FSA506_LINE_BUFFER_NUMBER) + 32, 32);
    RT_ASSERT(g_FSA506Info.framebuffer != RT_NULL);
    g_FSA506Info.smem_len = g_FSA506Info.pitch * NU_PKG_FSA506_LINE_BUFFER_NUMBER;
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

    fsa506_lcd_init(NULL);

    color = 0x0; //Black, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    fsa506_fillscreen(color);
    fsa506_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0xffff; //White, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    fsa506_fillscreen(color);
    fsa506_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0x1f; //Blue, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    fsa506_fillscreen(color);
    fsa506_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0x07e0; //Green, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    fsa506_fillscreen(color);
    fsa506_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0xf800; //Red, RGB
    rt_kprintf("Brush 0x%X on screen.\n", color);
    fsa506_fillscreen(color);
    fsa506_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    color = 0xffff; //White, RGB
    rt_kprintf("lcd draw hline, pixel: 0x%X, x1: %d, x2: %d, y: %d\n", color, x, x + 20, y);
    fsa506_lcd_draw_hline((const char *)&color, x, x + 20, y);

    color = 0xffff; //White, RGB
    rt_kprintf("lcd draw vline, pixel: 0x%X, x: %d, y: %d\n", color, y, y + 20);
    fsa506_lcd_draw_vline((const char *)&color, x, y, y + 20);

    for (i = 0; i < LINE_LEN; i++)
        pixels[i] = 20 + i * 5;

    x = y = 50;
    rt_kprintf("lcd blit line, start: x: %d, y: %d\n", x, y);
    fsa506_lcd_blit_line((const char *)&pixels[0], x, y, LINE_LEN);

    x = y = 200;
    color = 0x07E0; //Green, RGB
    rt_kprintf("lcd set pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
    fsa506_lcd_set_pixel((const char *)&color, x, y);
    color = 0x0;
    fsa506_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    x = y = 200;
    color = 0x1f; //Blue, RGB
    rt_kprintf("lcd set pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
    fsa506_lcd_set_pixel((const char *)&color, x, y);
    color = 0x0;
    fsa506_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);

    x = y = 200;
    color = 0xf800; //Red, RGB
    rt_kprintf("lcd set pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
    fsa506_lcd_set_pixel((const char *)&color, x, y);
    color = 0x0;
    fsa506_lcd_get_pixel((char *)&color, x, y);
    rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d\n", color, x, y);
}
MSH_CMD_EXPORT(lcd_test, test lcd display);
#endif

#endif /* if defined(NU_PKG_USING_FSA506) */
