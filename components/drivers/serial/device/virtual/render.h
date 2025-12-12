/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __VIRTUAL_RENDER_H__
#define __VIRTUAL_RENDER_H__

#include <rtdef.h>

struct render_color
{
    rt_uint32_t red;
    rt_uint32_t green;
    rt_uint32_t blue;
    rt_uint32_t alpha;
};

struct render_point
{
    rt_uint32_t row;
    rt_uint32_t col;
};

enum cursor
{
    CURSOR_HLINE,
    CURSOR_VLINE,
    CURSOR_BLOCK,
};

rt_err_t render_load_fbdev(struct rt_device *fbdev);
rt_err_t render_load_font(const char *psf_data, rt_size_t size,
        struct render_color *foreground, struct render_color *background,
        struct render_point *out_start_point, struct render_point *out_end_point);

void render_clear_display(void);

void render_set_foreground(struct render_color *foreground);
void render_set_background(struct render_color *background);
rt_inline void render_set_color(struct render_color *foreground, struct render_color *background)
{
    render_set_foreground(foreground);
    render_set_background(background);
}

void render_select_cursor(enum cursor shape);
void render_move_cursor(struct render_point *position);
void render_reset_cursor(struct render_point *out_position);
void render_return_cursor(struct render_point *out_position);
void render_current_cursor(struct render_point *out_position);

void render_put_char(char ch);

#endif /* __VIRTUAL_RENDER_H__ */
