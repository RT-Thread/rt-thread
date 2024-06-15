#include <rtthread.h>
#include <rtdevice.h>
#include <stdint.h>
#include <stdlib.h>
#include "drv_lcd.h"

static void drawarea(rt_device_t dev, struct rt_device_graphic_info *info,
                     int x, int y, int w, int h, uint16_t c)
{
    struct rt_device_rect_info rect;
    uint16_t *fb;
    int i, j;

    fb = (uint16_t *)info->framebuffer;
    fb += (info->width * y);
    fb += x;

    for (j = 0; j < h; j++)
    {
        for (i = 0; i < w; i++)
        {
            fb[i] = c;
        }
        fb += info->width;
    }

    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;

    rt_device_control(dev, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
}

static int showcolor(int argc, char **argv)
{
    unsigned char r = 0, g = 0, b = 0;
    char *devname = "lcd";
    rt_device_t dev;
    struct rt_device_graphic_info info;
    int result;
    int x = 0, y = 0;
    int i;
    uint16_t c;

    for (i = 1; i < argc; i++)
    {
        switch (i)
        {
        case 1:
            r = atoi(argv[i]);
            break;
        case 2:
            g = atoi(argv[i]);
            break;
        case 3:
            b = atoi(argv[i]);
            break;
        }
    }

    dev = rt_device_find(devname);
    if (!dev)
    {
        rt_kprintf("lcd: %s not found\n", devname);
        return -1;
    }

    if (rt_device_open(dev, 0) != 0)
    {
        rt_kprintf("lcd open fail\n");
        return -1;
    }

    result = rt_device_control(dev, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK)
    {
        rt_kprintf("get device information failed\n");
        return result;
    }

    c = (uint16_t)(((r >> 3) << 11) | ((g >> 2) << 6) | ((b >> 3)));
    drawarea(dev, &info, x, y, 24, 24, c);

    lcd_set_color(BLACK, BLUE);
    lcd_show_string(0, 40, 16, "hello world");
    lcd_show_string(0, 60, 24, "hello world");
    lcd_show_string(0, 90, 32, "hello world");
    lcd_draw_line(0, 200, 319, 200);
    lcd_draw_circle(270, 120, 30);

    lcd_set_color(BLACK, RED);
    lcd_show_string(0, 130, 32, "after set color");
    lcd_draw_line(0, 0, 319, 239);
    lcd_draw_rectangle(50, 10, 170, 145);
    lcd_draw_circle(160, 120, 50);

    rt_device_close(dev);
    return 0;
}
MSH_CMD_EXPORT(showcolor, showcolor R G B-- R / G / B : 0 ~255);
