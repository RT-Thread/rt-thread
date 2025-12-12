/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "psf.h"
#include "render.h"

struct render
{
    struct rt_device *fbdev;
    struct rt_device_graphic_info info;
    struct fb_var_screeninfo var;
    struct fb_fix_screeninfo fix;

    struct psf_font psf;
    rt_uint32_t xlate;
    rt_uint32_t font_line_length;
    rt_uint32_t buffer_idx;
    rt_size_t buffer_size;
    rt_size_t line_size;
    rt_size_t screen_size;
    rt_size_t font_size;
    rt_uint8_t color_size;
    rt_uint8_t *cursor, *cursor_backend;

    struct render_point position, start_point, end_point;

    rt_uint32_t foreground, background;
    rt_uint32_t raw_foreground, raw_background;
    rt_uint32_t red_off, green_off, blue_off, alpha_off;
    rt_uint32_t red_mask, green_mask, blue_mask, alpha_mask;

    void *hook_ptr;

    void (*set_pixel)(void *fb, rt_uint32_t color);
    rt_uint32_t (*get_pixel)(void *fb);

    void *(*last_buffer)(void);
    void *(*next_buffer)(void);
    void (*move_buffer)(void *dst, void *src, rt_size_t size);
    void (*pan_display)(void);
};

static struct render _render = {};

rt_err_t render_load_fbdev(struct rt_device *fbdev)
{
    rt_err_t err = RT_EOK;
    struct render *rd = &_render;

    if ((err = rt_device_open(fbdev, 0)))
    {
        return err;
    }

    rd->fbdev = fbdev;

    err |= rt_device_control(fbdev, FBIOGET_VSCREENINFO, &rd->var);
    err |= rt_device_control(fbdev, FBIOGET_FSCREENINFO, &rd->fix);
    err |= rt_device_control(fbdev, RTGRAPHIC_CTRL_GET_INFO, &rd->info);

    rt_device_close(fbdev);

    return err;
}

static rt_uint32_t parse_color(struct render_color *color)
{
    rt_uint32_t color_value;
    struct render *rd = &_render;

    color_value = ((color->red & rd->red_mask) << rd->red_off) |
                  ((color->green & rd->green_mask) << rd->green_off) |
                  ((color->blue & rd->blue_mask) << rd->blue_off);

    if (rd->var.transp.length)
    {
        color_value |= (color->alpha & rd->alpha_mask) << rd->alpha_off;
    }

    return color_value;
}

static void set_pixel16(void *fb, rt_uint32_t color)
{
    rt_memcpy(fb, &color, 2);
}

static rt_uint32_t get_pixel16(void *fb)
{
    rt_uint16_t color;

    rt_memcpy(&color, fb, 2);

    return color;
}

static void set_pixel24(void *fb, rt_uint32_t color)
{
    rt_memcpy(fb, &color, 3);
}

static rt_uint32_t get_pixel24(void *fb)
{
    rt_uint32_t color;

    rt_memcpy(&color, fb, 3);

    return color;
}

static void set_pixel32(void *fb, rt_uint32_t color)
{
    *(rt_uint32_t *)fb = color;
}

static rt_uint32_t get_pixel32(void *fb)
{
    return *(rt_uint32_t *)fb;
}

static void *last_buffer_single(void)
{
    struct render *rd = &_render;

    return (void *)rd->info.framebuffer;
}

static void *fb_next_buffer_dummy(void)
{
    return last_buffer_single();
}

static void fb_move_buffer_single(void *dst, void *src, rt_size_t size)
{
    rt_memmove(dst, src, size);
}

static void fb_pan_display_dummy(void)
{
}

static void *last_buffer_multi(void)
{
    struct render *rd = &_render;

    return (void *)rd->info.framebuffer + rd->buffer_idx * rd->line_size;
}

static void *fb_next_buffer(void)
{
    struct render *rd = &_render;

    if (rd->buffer_idx < rd->buffer_size)
    {
        ++rd->buffer_idx;
    }
    else
    {
        rd->buffer_idx = 0;
    }

    return last_buffer_multi();
}

static void fb_move_buffer_multi(void *dst, void *src, rt_size_t size)
{
    struct render *rd = &_render;

    if (rd->buffer_idx == 0)
    {
        fb_move_buffer_single(dst, src, size);
    }
}

static void fb_pan_display(void)
{
    struct render *rd = &_render;

    rd->var.yoffset = rd->buffer_idx * rd->psf.height;

    rt_device_control(rd->fbdev, FBIOPAN_DISPLAY, &rd->var);
}

static void color_hook_dummy(void *, rt_uint32_t *);

rt_err_t render_load_font(const char *psf_data, rt_size_t size,
        struct render_color *foreground, struct render_color *background,
        struct render_point *out_start_point, struct render_point *out_end_point)
{
    rt_err_t err;
    rt_uint8_t *font_data, *cursor, *cursor_backend;
    rt_uint32_t foreground_color, background_color;
    struct psf_font new_psf;
    struct render *rd = &_render;

    if ((err = psf_initialize(psf_data, &new_psf)))
    {
        return err;
    }

    if (!new_psf.count)
    {
        return -RT_EEMPTY;
    }

    /* Font + Cursor + Cursor backend */
    rd->color_size = rd->var.bits_per_pixel / 8;
    font_data = rt_malloc_align(rd->color_size * new_psf.glyph * (new_psf.count + 2), sizeof(rt_ubase_t));

    if (!font_data)
    {
        return -RT_ENOMEM;
    }

    cursor = font_data + rd->color_size * new_psf.glyph * new_psf.count;
    cursor_backend = cursor + rd->color_size * new_psf.glyph * new_psf.count;

    rd->red_off = rd->var.red.offset;
    rd->red_mask = RT_GENMASK(rd->var.red.length, 0);
    rd->green_off = rd->var.green.offset;
    rd->green_mask = RT_GENMASK(rd->var.green.length, 0);
    rd->blue_off = rd->var.blue.offset;
    rd->blue_mask = RT_GENMASK(rd->var.blue.length, 0);
    rd->alpha_off = rd->var.transp.offset;
    rd->alpha_mask = RT_GENMASK(rd->var.transp.length, 0);

    foreground_color = parse_color(foreground);
    background_color = parse_color(background);

    if ((err = psf_parse(&new_psf, font_data, cursor_backend,
            rd->color_size, foreground_color, background_color)))
    {
        rt_free(font_data);

        return err;
    }

    if (rd->psf.font_data)
    {
        rt_free((void *)rd->psf.font_data);
    }

    rd->foreground = rd->raw_foreground = foreground_color;
    rd->background = rd->raw_background = background_color;
    rd->hook_ptr = &color_hook_dummy;

    rt_memcpy(&rd->psf, &new_psf, sizeof(rd->psf));

    rd->font_line_length = rd->psf.width * rd->color_size;
    rd->xlate = rd->fix.line_length - rd->font_line_length;

    rd->line_size = rd->psf.height * rd->fix.line_length;
    rd->screen_size = rd->var.xres * rd->var.yres * rd->color_size;
    rd->font_size = rd->psf.glyph * rd->color_size;
    rd->buffer_idx = 0;
    rd->buffer_size = (rd->fix.smem_len - rd->screen_size) / rd->line_size;

    if (rd->buffer_size)
    {
        rd->var.yres_virtual = (rd->fix.smem_len / rd->screen_size) * rd->var.yres;

        if (rt_device_control(rd->fbdev, FBIOPUT_VSCREENINFO, &rd->var))
        {
            /* Enable double buffer fail */
            rd->buffer_size = 0;
        }
    }

    if (rd->buffer_size)
    {
        rd->last_buffer = last_buffer_multi;
        rd->next_buffer = fb_next_buffer;
        rd->move_buffer = fb_move_buffer_single;
        rd->pan_display = fb_pan_display;
    }
    else
    {
        rd->last_buffer = last_buffer_single;
        rd->next_buffer = fb_next_buffer_dummy;
        rd->move_buffer = fb_move_buffer_multi;
        rd->pan_display = fb_pan_display_dummy;
    }

    rd->cursor = cursor;
    rd->cursor_backend = cursor_backend;

    rd->start_point.row = rd->var.yoffset / rd->psf.height;
    rd->start_point.col = rd->var.xoffset / rd->psf.width;
    rd->end_point.row = rd->var.yres / rd->psf.height - 1;
    rd->end_point.col = rd->var.xres / rd->psf.width - 1;

    if (out_start_point)
    {
        rt_memcpy(out_start_point, &rd->start_point, sizeof(*out_start_point));
    }

    if (out_end_point)
    {
        rt_memcpy(out_end_point, &rd->end_point, sizeof(*out_end_point));
    }

    switch (rd->var.bits_per_pixel)
    {
    case 32:
        rd->set_pixel = set_pixel32;
        rd->get_pixel = get_pixel32;
        break;

    case 24:
        rd->set_pixel = set_pixel24;
        rd->get_pixel = get_pixel24;
        break;

    case 16:
        rd->set_pixel = set_pixel16;
        rd->get_pixel = get_pixel16;
        break;

    default: break;
    }

    return RT_EOK;
}

void render_clear_display(void)
{
    void *fb, *fb_end;
    rt_uint32_t color;
    rt_size_t color_size;
    struct render *rd = &_render;
    typeof(rd->set_pixel) set_pixel_handler = rd->set_pixel;

    fb = rd->next_buffer();
    fb_end = fb + rd->screen_size;

    color = rd->background;
    color_size = rd->color_size;

    while (fb < fb_end)
    {
        set_pixel_handler(fb, color);

        fb += color_size;
    }

    rd->pan_display();
    render_move_cursor(RT_NULL);
}

static void roll_display(void)
{
    rt_uint32_t color;
    rt_size_t screen_size, flush_size, color_size;
    void *old_fb, *fb, *fb_end;
    struct render *rd = &_render;
    typeof(rd->set_pixel) set_pixel_handler = rd->set_pixel;

    color = rd->background;
    color_size = rd->color_size;
    screen_size = rd->screen_size;
    flush_size = screen_size - rd->line_size;

    old_fb = rd->last_buffer();
    fb = rd->next_buffer();
    fb_end = fb + screen_size;

    rd->move_buffer(fb, old_fb + rd->line_size, flush_size);
    /* The last line */
    fb += flush_size;

    while (fb < fb_end)
    {
        set_pixel_handler(fb, color);

        fb += color_size;
    }

    rd->pan_display();
    rt_device_control(rd->fbdev, FBIO_WAITFORVSYNC, RT_NULL);
}

static void color_hook_dummy(void *fb, rt_uint32_t *out_color)
{
}

static void color_hook_transform(void *fb, rt_uint32_t *out_color)
{
    rt_uint32_t color;
    struct render *rd = &_render;

    rt_memcpy(&color, out_color, rd->color_size);

    if (color == rd->raw_foreground)
    {
        *out_color = rd->foreground;
    }
    else if (color == rd->raw_background)
    {
        *out_color = rd->background;
    }
}

void render_set_foreground(struct render_color *foreground)
{
    struct render *rd = &_render;

    rd->foreground = parse_color(foreground);

    if (rd->foreground != rd->raw_foreground)
    {
        rd->hook_ptr = color_hook_transform;
    }
    else
    {
        rd->hook_ptr = color_hook_dummy;
    }
}

void render_set_background(struct render_color *background)
{
    struct render *rd = &_render;

    rd->background = parse_color(background);

    if (rd->foreground != rd->raw_foreground)
    {
        rd->hook_ptr = color_hook_transform;
    }
    else
    {
        rd->hook_ptr = color_hook_dummy;
    }
}

static void color_hook_invert(void *fb, rt_uint32_t *out_color)
{
    struct render *rd = &_render;

    *out_color ^= rd->get_pixel(fb) & ~(rd->alpha_mask << rd->alpha_off);
}

static void draw_block(void *block, void (*color_hook)(void *fb, rt_uint32_t *out_color))
{
    void *fb;
    rt_size_t color_size;
    int font_width, font_height, xlate;
    struct render *rd = &_render;
    typeof(rd->set_pixel) set_pixel_handler = rd->set_pixel;

    color_size = rd->color_size;
    font_width = rd->psf.width;
    font_height = rd->psf.height;
    xlate = rd->xlate;

    fb = rd->last_buffer();
    fb += rd->position.col * rd->font_line_length + rd->position.row * rd->line_size;

    for (int y = 0; y < font_height; ++y)
    {
        for (int x = 0; x < font_width; ++x)
        {
            rt_uint32_t color = *(rt_uint32_t *)block;

            color_hook(fb, &color);
            set_pixel_handler(fb, color);

            fb += color_size;
            block += color_size;
        }

        fb += xlate;
    }
}

static void cursor_leave(void)
{
    struct render *rd = &_render;

    draw_block(rd->cursor, &color_hook_invert);
}

static void cursor_update(void)
{
    struct render *rd = &_render;

    draw_block(rd->cursor, &color_hook_invert);

    rt_device_control(rd->fbdev, FBIO_WAITFORVSYNC, RT_NULL);
}

void render_select_cursor(enum cursor shape)
{
    void *cursor;
    rt_size_t color_size;
    int font_width, font_height;
    rt_uint32_t foreground, background;
    struct render *rd = &_render;
    typeof(rd->set_pixel) set_pixel_handler = rd->set_pixel;

    cursor = rd->cursor;
    font_width = rd->psf.width;
    font_height = rd->psf.height;
    foreground = rd->foreground;
    background = rd->background;
    color_size = rd->color_size;

    switch (shape)
    {
    case CURSOR_HLINE:
        for (int y = 0; y < font_height; ++y)
        {
            for (int x = 0; x < font_width; ++x)
            {
                if (y + 1 < font_height)
                {
                    set_pixel_handler(cursor, background);
                }
                else
                {
                    set_pixel_handler(cursor, foreground);
                }

                cursor += color_size;
            }
        }
        break;

    case CURSOR_VLINE:
        for (int i = 0; i < font_height; ++i)
        {
            set_pixel_handler(cursor, foreground);
            cursor += color_size;

            for (int x = 1; x < font_width; ++x)
            {
                set_pixel_handler(cursor, background);

                cursor += color_size;
            }
        }
        break;

    case CURSOR_BLOCK:
        for (int y = 0; y < font_height; ++y)
        {
            for (int x = 0; x < font_width; ++x)
            {
                set_pixel_handler(cursor, foreground);

                cursor += color_size;
            }
        }
        break;

    default:
        return;
    }

    cursor_update();
}

void render_move_cursor(struct render_point *position)
{
    struct render *rd = &_render;

    if (position)
    {
        cursor_leave();

        if (position->row > rd->end_point.row || position->col > rd->end_point.col)
        {
            return;
        }

        rt_memcpy(&rd->position, position, sizeof(rd->position));
    }
    else
    {
        rt_memset(&rd->position, 0, sizeof(rd->position));
    }

    cursor_update();
}

void render_reset_cursor(struct render_point *out_position)
{
    struct render *rd = &_render;

    cursor_leave();

    rd->position.col = rd->start_point.col;

    cursor_update();
    render_current_cursor(out_position);
}

void render_return_cursor(struct render_point *out_position)
{
    struct render *rd = &_render;

    cursor_leave();

    rd->position.col = rd->start_point.col;

    if (rd->position.row >= rd->end_point.row)
    {
        roll_display();
    }
    else
    {
        ++rd->position.row;
    }

    cursor_update();
    render_current_cursor(out_position);
}

void render_current_cursor(struct render_point *out_position)
{
    struct render *rd = &_render;

    if (out_position)
    {
        rt_memcpy(out_position, &rd->position, sizeof(rd->position));
    }
}

void render_put_char(char ch)
{
    struct render *rd = &_render;

    draw_block((void *)rd->psf.font_data + ch * rd->font_size, rd->hook_ptr);

    ++rd->position.col;

    if (rd->position.col > rd->end_point.col)
    {
        rd->position.col = rd->start_point.col;

        if (rd->position.row >= rd->end_point.row)
        {
            roll_display();
        }
        else
        {
            ++rd->position.row;
        }
    }

    cursor_update();
}
