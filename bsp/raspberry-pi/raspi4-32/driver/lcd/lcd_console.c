
/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-11-09     bigmagic       first version
 */

#include "lcd_console.h"
#include "lcd_font_20.h"

#define LCD_CONSOLE_FLUSH_NOW    1

#define CONSOLE_NAME    "hdmi"
#define COLOR_DELTA     0.05

#ifndef LCD_CONSOLE_FLUSH_NOW
static rt_thread_t console_flush_thread_tid = RT_NULL;
#define CONSOLE_FLUSH_THREAD_STACK_SIZE   (1024)
#define CONSOLE_FLUSH_THREAD_PRIORITY     (20)
#define CONSOLE_FLUSH_THREAD_TIMESLICE    (10)
#define LCD_CONSOLE_DELAY                 (100)  //100ms
#endif

static rt_device_t console_dev = RT_NULL;

static fb_t console_fb;
static rt_uint8_t* virt_buffer;

static rt_uint32_t CHAR_W = 8;
static rt_uint32_t CHAR_H = 20;

static int prev_x_offset = 0;

static void newline(fb_t* fb)
{
    uint8_t* to;
    uint8_t* from;
    int i;
    fb->y++;
    fb->x = 5 * fb->depth;

    if (fb->y == (fb->height / CHAR_H))
    {
        to = (uint8_t*) fb->vaddr;
        from = to + (CHAR_H * fb->pitch);

        for (i = 0; i < ((fb->height - CHAR_H) * fb->pitch); i++)
        {
            *to++ = *from++;
        }

        if(fb->depth >= 3)
        {
            uint32_t *addr_32bit = (uint32_t*) (fb->vaddr) + (fb->height - CHAR_H) * fb->width;

            for (i = 0; i < (CHAR_H * fb->width); i++)
            {
                *addr_32bit++ = fb->back;
            }
        }
        else
        {
            uint16_t *addr_16bit = (uint16_t*) (fb->vaddr) + (fb->height - CHAR_H) * fb->width;

            for (i = 0; i < (CHAR_H * fb->width); i++)
            {
                *addr_16bit++ = fb->back;
            }
        }
        fb->y =  fb->y - 1;
    }
}


static void fb_draw_char(fb_t *fb, char s)
{
    unsigned char* addr = (unsigned char*) fb->vaddr;
    unsigned char *glyph = (unsigned char *)lcd_console_font_dejavu_20_glyph_bitmap + lcd_console_font_dejavu_20_glyph_dsc[s - 32].glyph_index;
    CHAR_W = lcd_console_font_dejavu_20_glyph_dsc[s - 32].w_px;

    fb->x = fb->x + prev_x_offset * fb->depth;

    int i, j, line, mask, bytesperline = (CHAR_W + 7) / 8;
    int kk = (bytesperline) * 8;
    prev_x_offset = CHAR_W + 2;
    // calculate the offset on screen
    int offs = (fb->y * CHAR_H * fb->pitch) + fb->x;

    // display a character
    for (j = 0; j < CHAR_H; j++)
    {
        // display one row
        line = offs;
        mask = 1;
        mask = 0x80;
        for (i = 0; i < kk; i++)
        {
            if(fb->depth >= 3)
            {
                *((unsigned int*) (addr + line)) = ((int) *(glyph + ((i)/8)) * 1) & mask ? fb->fore : fb->back;
            }
            else
            {
                *((unsigned short*) (addr + line)) = ((int) *(glyph + ((i)/8)) * 1) & mask ? fb->fore : fb->back;
            }

            mask >>= 1;
            if(mask == 0)
            {
                mask = 0x80;
            }
            line += fb->depth;
        }
        // adjust to next line
        glyph += bytesperline;
        offs += fb->pitch;
    }
}

void fb_print(char *s)
{
    fb_t *fb = &console_fb;
    // draw next character if it's not zero
    while (*s)
    {
        // handle carrige return
        if (*s == '\r')
        {
            fb->x = 5 * fb->depth;
        }
        else if (*s == '\n')
        {
            newline(fb);
        }
        else if (*s == '\t')
        {
            //tab is 8 spaces
            if((fb->x + 8 * fb->depth) < (fb->width) * fb->depth)
            {
                fb->x = fb->x + 8 * fb->depth;
            }
        }
        else if (*s == '\b')
        {
            if (fb->x > 5 * fb->depth)
            {
                fb->x = fb->x - prev_x_offset * fb->depth;
                fb_draw_char(fb, ' ');
            }
        }
        else if((fb->x + prev_x_offset * fb->depth + 5 * fb->depth) >= (fb->width * fb->depth))
        {
            newline(fb);
            fb_draw_char(fb, *s);
        }
        else
        {
            fb_draw_char(fb, *s);
        }
        s++;
    }

#ifdef LCD_CONSOLE_FLUSH_NOW
    rt_memcpy((void *)fb->paddr, (void *)fb->vaddr, fb->size);
    if(console_dev != RT_NULL)
    {
        rt_device_control(console_dev,RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
    }
#endif
}

#ifndef LCD_CONSOLE_FLUSH_NOW
void lcd_console_task_entry(void *param)
{
    fb_t *fb = (fb_t *)param;
    while (1)
    {
        rt_memcpy((void *)fb->paddr, (void *)fb->vaddr, fb->size);
        if(console_dev != RT_NULL)
        {
            rt_device_control(console_dev,RTGRAPHIC_CTRL_RECT_UPDATE, RT_NULL);
        }
        rt_thread_mdelay(LCD_CONSOLE_DELAY);
    }

}
#endif

int lcd_console_init(void)
{
    struct rt_device_graphic_info info;
    console_dev = rt_device_find(CONSOLE_NAME);
    if(console_dev == RT_NULL)
    {
        rt_kprintf("no console dev!\n");
        return 0;
    }

    if(console_dev->ref_count >= 1)
    {
        rt_kprintf("lcd console has open!\n");
        return 0;
    }

    rt_device_open(console_dev,RT_DEVICE_OFLAG_RDWR);

    rt_device_control(console_dev, RTGRAPHIC_CTRL_GET_INFO, &info);

    virt_buffer = (rt_uint8_t* )rt_malloc(info.width * info.height * (info.bits_per_pixel/8));
    rt_memset(virt_buffer, 0 , info.width * info.height * (info.bits_per_pixel/8));
    console_fb.width = info.width;
    console_fb.height = info.height;
    console_fb.pitch = info.width * (info.bits_per_pixel/8);
    console_fb.vaddr = (rt_uint32_t)virt_buffer;
    console_fb.paddr = (rt_uint32_t)info.framebuffer;
    console_fb.size = info.width * info.height * (info.bits_per_pixel/8);
    console_fb.depth = info.bits_per_pixel/8;
    console_fb.x = 0;
    console_fb.y = 0;
    if(console_fb.depth >= 3)
    {
        console_fb.fore = CONSOLE_WHITE_32;
        console_fb.back = CONSOLE_BLACK_32;
    }
    else
    {
        console_fb.fore = CONSOLE_WHITE_16;
        console_fb.back = CONSOLE_BLACK_16;
    }

#ifndef LCD_CONSOLE_FLUSH_NOW
    console_flush_thread_tid = rt_thread_create("lcd_console", lcd_console_task_entry, (void *)&console_fb,
                                       CONSOLE_FLUSH_THREAD_STACK_SIZE,
                                       CONSOLE_FLUSH_THREAD_PRIORITY, CONSOLE_FLUSH_THREAD_TIMESLICE);
    if (console_flush_thread_tid != RT_NULL)
        rt_thread_startup(console_flush_thread_tid);
#endif
    /*
    * note:
    * if serial console and lcd console together
    * you can add /src/kservice.c:rt_kprintf
    * #ifdef USING_LCD_CONSOLE
    *     fb_print((char*)rt_log_buf);
    * #endif
    *
    * remove rt_console_set_device(CONSOLE_NAME);
    */
    rt_console_set_device(CONSOLE_NAME);

    rt_show_version();//show rt-thread logo

    return 0;
}
INIT_APP_EXPORT(lcd_console_init);
