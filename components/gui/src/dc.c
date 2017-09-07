/*
 * File      : dc.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 * 2010-09-20     richard      modified rtgui_dc_draw_round_rect
 * 2010-09-27     Bernard      fix draw_mono_bmp issue
 * 2011-04-25     Bernard      fix fill polygon issue, which found by loveic
 */

/* for sin/cos etc */
#include <math.h>

#include <rtgui/dc.h>
#include <rtgui/dc_hw.h>
#include <rtgui/dc_client.h>

#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/title.h>

#include <string.h> /* for strlen */
#include <stdlib.h> /* fir qsort  */

static int _int_compare(const void *a, const void *b)
{
    return (*(const int *) a) - (*(const int *) b);
}

void rtgui_dc_destory(struct rtgui_dc *dc)
{
    if (dc == RT_NULL) return;

    dc->engine->fini(dc);
    rtgui_free(dc);
}
RTM_EXPORT(rtgui_dc_destory);

void rtgui_dc_draw_line(struct rtgui_dc *dc, int x1, int y1, int x2, int y2)
{
    if (dc == RT_NULL) return;

    if (y1 == y2)
    {
        rtgui_dc_draw_hline(dc, x1, x2, y1);
    }
    else if (x1 == x2)
    {
        rtgui_dc_draw_vline(dc, x1, y1, y2);
    }
    else
    {
        int dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;
        register rt_base_t i;
        /* rtgui_rect_t rect; */

        dx = x2 - x1;       /* the horizontal distance of the line */
        dy = y2 - y1;       /* the vertical distance of the line */

#define rtgui_sgn(x) ((x<0)?-1:((x>0)?1:0)) /* macro to return the sign of a number */

        dxabs = _UI_ABS(dx);
        dyabs = _UI_ABS(dy);
        sdx = rtgui_sgn(dx);
        sdy = rtgui_sgn(dy);
        x = dyabs >> 1;
        y = dxabs >> 1;
        px = x1;
        py = y1;

        if (dxabs >= dyabs) /* the line is more horizontal than vertical */
        {
            for (i = 0; i < dxabs; i++)
            {
                y += dyabs;
                if (y >= dxabs)
                {
                    y -= dxabs;
                    py += sdy;
                }
                px += sdx;

                /* draw this point */
                rtgui_dc_draw_point(dc, px, py);
            }
        }
        else                /* the line is more vertical than horizontal */
        {
            for (i = 0; i < dyabs; i++)
            {
                x += dxabs;
                if (x >= dyabs)
                {
                    x -= dyabs;
                    px += sdx;
                }
                py += sdy;

                /* draw this point */
                rtgui_dc_draw_point(dc, px, py);
            }
        }
    }
}
RTM_EXPORT(rtgui_dc_draw_line);

void rtgui_dc_draw_horizontal_line(struct rtgui_dc *dc, int x1, int x2, int y)
{
    rtgui_color_t color;

    if (dc == RT_NULL) return ;

    /* save old color */
    color = RTGUI_DC_FC(dc);

    RTGUI_DC_FC(dc) = dark_grey;
    rtgui_dc_draw_hline(dc, x1, x2, y);

    y ++;

    RTGUI_DC_FC(dc) = high_light;
    rtgui_dc_draw_hline(dc, x1, x2, y);

    /* restore color */
    RTGUI_DC_FC(dc) = color;
}
RTM_EXPORT(rtgui_dc_draw_horizontal_line);

void rtgui_dc_draw_vertical_line(struct rtgui_dc *dc, int x, int y1, int y2)
{
    rtgui_color_t color;

    if (dc == RT_NULL) return ;

    /* save old color */
    color = RTGUI_DC_FC(dc);

    RTGUI_DC_FC(dc) = dark_grey;
    rtgui_dc_draw_vline(dc, x, y1, y2);

    x ++;

    RTGUI_DC_FC(dc) = high_light;
    rtgui_dc_draw_vline(dc, x, y1, y2);

    /* restore color */
    RTGUI_DC_FC(dc) = color;
}
RTM_EXPORT(rtgui_dc_draw_vertical_line);

void rtgui_dc_draw_rect(struct rtgui_dc *dc, struct rtgui_rect *rect)
{
    rtgui_dc_draw_hline(dc, rect->x1, rect->x2, rect->y1);
    rtgui_dc_draw_hline(dc, rect->x1, rect->x2, rect->y2 - 1);

    rtgui_dc_draw_vline(dc, rect->x1, rect->y1, rect->y2);
    rtgui_dc_draw_vline(dc, rect->x2 - 1, rect->y1, rect->y2);
}
RTM_EXPORT(rtgui_dc_draw_rect);

void rtgui_dc_fill_rect_forecolor(struct rtgui_dc *dc, struct rtgui_rect *rect)
{
    rtgui_color_t save_color;
    /*save the background color of dc*/
    save_color = RTGUI_DC_BC(dc);
    /*set the background color to fore color*/
    RTGUI_DC_BC(dc) = RTGUI_DC_FC(dc);
    dc->engine->fill_rect(dc, rect);
    /*restore the background color of dc*/
    RTGUI_DC_BC(dc) = save_color;
}
RTM_EXPORT(rtgui_dc_fill_rect_forecolor);

void rtgui_dc_draw_round_rect(struct rtgui_dc *dc, struct rtgui_rect *rect, int r)
{
    RT_ASSERT(((rect->x2 - rect->x1) / 2 >= r) && ((rect->y2 - rect->y1) / 2 >= r));

    if (r < 0)
    {
        return;
    }

    if (r == 0)
    {
        rtgui_dc_draw_rect(dc, rect);
        return;
    }

    if (((rect->x2 - rect->x1) / 2 >= r) && ((rect->y2 - rect->y1) / 2 >= r))
    {
        rtgui_dc_draw_arc(dc, rect->x1 + r, rect->y1 + r, r, 180, 270);
        rtgui_dc_draw_arc(dc, rect->x2 - r, rect->y1 + r, r, 270, 360);
        rtgui_dc_draw_arc(dc, rect->x1 + r, rect->y2 - r, r, 90,  180);
        rtgui_dc_draw_arc(dc, rect->x2 - r, rect->y2 - r, r, 0,   90);

        rtgui_dc_draw_hline(dc, rect->x1 + r, rect->x2 - r, rect->y1);
        rtgui_dc_draw_hline(dc, rect->x1 + r, rect->x2 - r, rect->y2);
        rtgui_dc_draw_vline(dc, rect->x1, rect->y1 + r, rect->y2 - r);
        rtgui_dc_draw_vline(dc, rect->x2, rect->y1 + r, rect->y2 - r);
    }
}
RTM_EXPORT(rtgui_dc_draw_round_rect);

void rtgui_dc_fill_round_rect(struct rtgui_dc *dc, struct rtgui_rect *rect, int r)
{
    struct rtgui_rect rect_temp;

    RT_ASSERT(((rect->x2 - rect->x1) / 2 >= r) && ((rect->y2 - rect->y1) / 2 >= r));

    if (((rect->x2 - rect->x1) / 2 >= r) && ((rect->y2 - rect->y1) / 2 >= r))
    {
        rect_temp.x1 = rect->x1 + r;
        rect_temp.y1 = rect->y1;
        rect_temp.x2 = rect->x2 - r;
        rect_temp.y2 = rect->y2;
        rtgui_dc_fill_rect_forecolor(dc, &rect_temp);//fill rect with foreground

        rect_temp.x1 = rect->x1;
        rect_temp.y1 = rect->y1 + r;
        rect_temp.x2 = rect->x1 + r;
        rect_temp.y2 = rect->y2 - r;
        rtgui_dc_fill_rect_forecolor(dc, &rect_temp);//fill rect with foreground

        rect_temp.x1 = rect->x2 - r;
        rect_temp.y1 = rect->y1 + r;
        rect_temp.x2 = rect->x2;
        rect_temp.y2 = rect->y2 - r;
        rtgui_dc_fill_rect_forecolor(dc, &rect_temp);//fill rect with foreground

        rtgui_dc_fill_circle(dc, rect->x1 + r, rect->y1 + r, r);
        rtgui_dc_fill_circle(dc, rect->x2 - r, rect->y2 - r, r);
        rtgui_dc_fill_circle(dc, rect->x2 - r, rect->y1 + r, r);
        rtgui_dc_fill_circle(dc, rect->x1 + r, rect->y2 - r, r);
    }
}
RTM_EXPORT(rtgui_dc_fill_round_rect);

void rtgui_dc_draw_shaded_rect(struct rtgui_dc *dc, rtgui_rect_t *rect,
                               rtgui_color_t c1, rtgui_color_t c2)
{
    RT_ASSERT(dc != RT_NULL);

    RTGUI_DC_FC(dc) = c1;
    rtgui_dc_draw_vline(dc, rect->x1, rect->y1, rect->y2);
    rtgui_dc_draw_hline(dc, rect->x1 + 1, rect->x2, rect->y1);

    RTGUI_DC_FC(dc) = c2;
    rtgui_dc_draw_vline(dc, rect->x2 - 1, rect->y1, rect->y2);
    rtgui_dc_draw_hline(dc, rect->x1, rect->x2, rect->y2 - 1);
}
RTM_EXPORT(rtgui_dc_draw_shaded_rect);

void rtgui_dc_fill_gradient_rectv(struct rtgui_dc *dc, rtgui_rect_t *rect,
                                  rtgui_color_t c1, rtgui_color_t c2)
{
    int y, step;
    rtgui_color_t fc;

    RT_ASSERT(dc != RT_NULL);
    RT_ASSERT(rect != RT_NULL);

    step = rtgui_rect_height(*rect);
    fc = RTGUI_DC_FC(dc);

    for (y = rect->y1; y < rect->y2; y++)
    {
        RTGUI_DC_FC(dc) = RTGUI_ARGB(((int)RTGUI_RGB_A(c2) - RTGUI_RGB_A(c1)) * (y - rect->y1) / step + RTGUI_RGB_A(c1),
                                     ((int)RTGUI_RGB_R(c2) - RTGUI_RGB_R(c1)) * (y - rect->y1) / step + RTGUI_RGB_R(c1),
                                     ((int)RTGUI_RGB_G(c2) - RTGUI_RGB_G(c1)) * (y - rect->y1) / step + RTGUI_RGB_G(c1),
                                     ((int)RTGUI_RGB_B(c2) - RTGUI_RGB_B(c1)) * (y - rect->y1) / step + RTGUI_RGB_B(c1));
        rtgui_dc_draw_hline(dc, rect->x1, rect->x2, y);
    }

    RTGUI_DC_FC(dc) = fc;
}
RTM_EXPORT(rtgui_dc_fill_gradient_rectv);

void rtgui_dc_draw_focus_rect(struct rtgui_dc *dc, rtgui_rect_t *rect)
{
    int x, y;

    for (x = rect->x1; x < rect->x2 - 1; x += 2)
    {
        rtgui_dc_draw_point(dc, x, rect->y1);
        rtgui_dc_draw_point(dc, x, rect->y2 - 1);
    }

    for (y = rect->y1; y < rect->y2; y += 2)
    {
        rtgui_dc_draw_point(dc, rect->x1, y);
        rtgui_dc_draw_point(dc, rect->x2 - 1, y);
    }
}
RTM_EXPORT(rtgui_dc_draw_focus_rect);

void rtgui_dc_draw_text(struct rtgui_dc *dc, const char *text, struct rtgui_rect *rect)
{
    rt_uint32_t len;
    struct rtgui_font *font;
    struct rtgui_rect text_rect;

    RT_ASSERT(dc != RT_NULL);

    font = RTGUI_DC_FONT(dc);
    if (font == RT_NULL)
    {
        /* use system default font */
        font = rtgui_font_default();
    }

    /* text align */
    rtgui_font_get_metrics(font, text, &text_rect);
    rtgui_rect_moveto_align(rect, &text_rect, RTGUI_DC_TEXTALIGN(dc));

    len = strlen((const char *)text);
    rtgui_font_draw(font, dc, text, len, &text_rect);
}
RTM_EXPORT(rtgui_dc_draw_text);

void rtgui_dc_draw_text_stroke(struct rtgui_dc *dc, const char *text, struct rtgui_rect *rect,
                               rtgui_color_t color_stroke, rtgui_color_t color_core)
{
    int x, y;
    rtgui_rect_t r;
    rtgui_color_t fc;

    RT_ASSERT(dc != RT_NULL);

    fc = RTGUI_DC_FC(dc);
    RTGUI_DC_FC(dc) = color_stroke;
    for (x = -1; x < 2; x++)
    {
        for (y = -1; y < 2; y++)
        {
            r = *rect;
            rtgui_rect_moveto(&r, x, y);
            rtgui_dc_draw_text(dc, text, &r);
        }
    }
    RTGUI_DC_FC(dc) = color_core;
    rtgui_dc_draw_text(dc, text, rect);
    RTGUI_DC_FC(dc) = fc;
}
RTM_EXPORT(rtgui_dc_draw_text_stroke);

/*
 * draw a monochrome color bitmap data
 */
void rtgui_dc_draw_mono_bmp(struct rtgui_dc *dc, int x, int y, int w, int h, const rt_uint8_t *data)
{
    int i, j, k;

    /* get word bytes */
    w = (w + 7) / 8;

    /* draw mono bitmap data */
    for (i = 0; i < h; i ++)
        for (j = 0; j < w; j++)
            for (k = 0; k < 8; k++)
                if (((data[i * w + j] >> (7 - k)) & 0x01) != 0)
                    rtgui_dc_draw_point(dc, x + 8 * j + k, y + i);
}
RTM_EXPORT(rtgui_dc_draw_mono_bmp);

void rtgui_dc_draw_byte(struct rtgui_dc *dc, int x, int y, int h, const rt_uint8_t *data)
{
    rtgui_dc_draw_mono_bmp(dc, x, y, 8, h, data);
}
RTM_EXPORT(rtgui_dc_draw_byte);

void rtgui_dc_draw_word(struct rtgui_dc *dc, int x, int y, int h, const rt_uint8_t *data)
{
    rtgui_dc_draw_mono_bmp(dc, x, y, 16, h, data);
}
RTM_EXPORT(rtgui_dc_draw_word);

void rtgui_dc_draw_border(struct rtgui_dc *dc, rtgui_rect_t *rect, int flag)
{
    rtgui_rect_t r;
    rtgui_color_t color;

    if (dc == RT_NULL) return ;

    /* save old color */
    color = RTGUI_DC_FC(dc);

    r = *rect;
    switch (flag)
    {
    case RTGUI_BORDER_RAISE:
        rtgui_dc_draw_shaded_rect(dc, &r, high_light, black);
        rtgui_rect_inflate(&r, -1);
        rtgui_dc_draw_shaded_rect(dc, &r, light_grey, dark_grey);
        break;

    case RTGUI_BORDER_SUNKEN:
        rtgui_dc_draw_shaded_rect(dc, &r, dark_grey, high_light);
        rtgui_rect_inflate(&r, -1);
        rtgui_dc_draw_shaded_rect(dc, &r, black, light_grey);
        break;

    case RTGUI_BORDER_BOX:
        rtgui_dc_draw_shaded_rect(dc, &r, dark_grey, high_light);
        rtgui_rect_inflate(&r, -1);
        rtgui_dc_draw_shaded_rect(dc, &r, high_light, dark_grey);
        break;

    case RTGUI_BORDER_STATIC:
        rtgui_dc_draw_shaded_rect(dc, &r, dark_grey, high_light);
        break;

    case RTGUI_BORDER_EXTRA:
        RTGUI_DC_FC(dc) = light_grey;
        rtgui_dc_draw_rect(dc, &r);
        break;

    case RTGUI_BORDER_SIMPLE:
        RTGUI_DC_FC(dc) = black;
        rtgui_dc_draw_rect(dc, &r);
        break;

    default:
        break;
    }

    /* restore color */
    RTGUI_DC_FC(dc) = color;
}
RTM_EXPORT(rtgui_dc_draw_border);

void rtgui_dc_draw_polygon(struct rtgui_dc *dc, const int *vx, const int *vy, int count)
{
    int i;
    const int *x1, *y1, *x2, *y2;

    /*
     * Sanity check
     */
    if (count < 3) return;

    /*
     * Pointer setup
     */
    x1 = x2 = vx;
    y1 = y2 = vy;
    x2++;
    y2++;

    /*
     * Draw
     */
    for (i = 1; i < count; i++)
    {
        rtgui_dc_draw_line(dc, *x1, *y1, *x2, *y2);
        x1 = x2;
        y1 = y2;
        x2++;
        y2++;
    }
    rtgui_dc_draw_line(dc, *x1, *y1, *vx, *vy);
}
RTM_EXPORT(rtgui_dc_draw_polygon);

void rtgui_dc_fill_polygon(struct rtgui_dc *dc, const int *vx, const int *vy, int count)
{
    int i;
    int y, xa, xb;
    int miny, maxy;
    int x1, y1;
    int x2, y2;
    int ind1, ind2;
    int ints;
    int *poly_ints = RT_NULL;

    /*
     * Sanity check number of edges
     */
    if (count < 3) return;

    /*
     * Allocate temp array, only grow array
     */
    poly_ints = (int *) rtgui_malloc(sizeof(int) * count);
    if (poly_ints == RT_NULL) return ; /* no memory, failed */

    /*
     * Determine Y maximal
     */
    miny = vy[0];
    maxy = vy[0];
    for (i = 1; (i < count); i++)
    {
        if (vy[i] < miny) miny = vy[i];
        else if (vy[i] > maxy) maxy = vy[i];
    }

    /*
     * Draw, scanning y
     */
    for (y = miny; (y <= maxy); y++)
    {
        ints = 0;
        for (i = 0; (i < count); i++)
        {
            if (!i)
            {
                ind1 = count - 1;
                ind2 = 0;
            }
            else
            {
                ind1 = i - 1;
                ind2 = i;
            }
            y1 = vy[ind1];
            y2 = vy[ind2];
            if (y1 < y2)
            {
                x1 = vx[ind1];
                x2 = vx[ind2];
            }
            else if (y1 > y2)
            {
                y2 = vy[ind1];
                y1 = vy[ind2];
                x2 = vx[ind1];
                x1 = vx[ind2];
            }
            else
            {
                continue;
            }

            if (((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2)))
            {
                poly_ints[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
            }
        }

        qsort(poly_ints, ints, sizeof(int), _int_compare);

        for (i = 0; (i < ints); i += 2)
        {
            xa = poly_ints[i] + 1;
            xa = (xa >> 16) + ((xa & 32768) >> 15);
            xb = poly_ints[i + 1] - 1;
            xb = (xb >> 16) + ((xb & 32768) >> 15);
            rtgui_dc_draw_hline(dc, xa, xb, y);
        }
    }

    /* release memory */
    rtgui_free(poly_ints);
}
RTM_EXPORT(rtgui_dc_fill_polygon);

void rtgui_dc_draw_circle(struct rtgui_dc *dc, int x, int y, int r)
{
    rtgui_dc_draw_ellipse(dc, x, y, r, r);
}
RTM_EXPORT(rtgui_dc_draw_circle);

enum
{
    QUARTER_BTM,
    QUARTER_BTM_LEFT,
    QUARTER_BTM_RIGHT,
    QUARTER_TOP,
    QUARTER_TOP_LEFT,
    QUARTER_TOP_RIGHT,
    QUARTER_FULL,
};

static void _fill_quarter_circle(struct rtgui_dc *dc,
                                 rt_int16_t ox, rt_int16_t oy,
                                 rt_int16_t rad, int quadrant)
{
    /* Midpoint circle algorithm. */
    int dk, x, y;

    dk = 1 - rad;
    x = 0;
    y = rad;

    while (x <= y)
    {
        switch (quadrant)
        {
        case QUARTER_BTM:
            rtgui_dc_draw_hline(dc, ox - x, ox + x, oy + y);
            rtgui_dc_draw_hline(dc, ox - y, ox + y, oy + x);
            break;
        case QUARTER_BTM_LEFT:
            rtgui_dc_draw_hline(dc, ox, ox + x, oy + y);
            rtgui_dc_draw_hline(dc, ox, ox + y, oy + x);
            break;
        case QUARTER_BTM_RIGHT:
            rtgui_dc_draw_hline(dc, ox, ox - x, oy + y);
            rtgui_dc_draw_hline(dc, ox, ox - y, oy + x);
            break;
        case QUARTER_TOP_RIGHT:
            rtgui_dc_draw_hline(dc, ox, ox - x, oy - y);
            rtgui_dc_draw_hline(dc, ox, ox - y, oy - x);
            break;
        case QUARTER_TOP_LEFT:
            rtgui_dc_draw_hline(dc, ox, ox + x, oy - y);
            rtgui_dc_draw_hline(dc, ox, ox + y, oy - x);
            break;
        case QUARTER_TOP:
            rtgui_dc_draw_hline(dc, ox - x, ox + x, oy - y);
            rtgui_dc_draw_hline(dc, ox - y, ox + y, oy - x);
            break;
        case QUARTER_FULL:
            rtgui_dc_draw_hline(dc, ox - x, ox + x, oy + y);
            rtgui_dc_draw_hline(dc, ox - y, ox + y, oy + x);
            rtgui_dc_draw_hline(dc, ox - x, ox + x, oy - y);
            rtgui_dc_draw_hline(dc, ox - y, ox + y, oy - x);
            break;
        default:
            RT_ASSERT(0);
        };

        if (dk > 0)
        {
            y--;
            dk += 2 * (x - y) + 5;
        }
        else
        {
            dk += 2 * x + 3;
        }
        x++;
    }
}

void rtgui_dc_fill_circle(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r)
{
    /*
     * Sanity check radius
     */
    if (r < 0)
        return;

    /*
     * Special case for r=0 - draw a point
     */
    if (r == 0)
    {
        rtgui_dc_draw_point(dc, x, y);
        return;
    }

    _fill_quarter_circle(dc, x, y, r, QUARTER_FULL);
}
RTM_EXPORT(rtgui_dc_fill_circle);

void rtgui_dc_draw_arc(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end)
{
    rt_int16_t cx = 0;
    rt_int16_t cy = r;
    rt_int16_t df = 1 - r;
    rt_int16_t d_e = 3;
    rt_int16_t d_se = -2 * r + 5;
    rt_int16_t xpcx, xmcx, xpcy, xmcy;
    rt_int16_t ypcy, ymcy, ypcx, ymcx;
    rt_uint8_t drawoct;
    int startoct, endoct, oct, stopval_start, stopval_end;
    double temp;

    stopval_start = 0;
    stopval_end = 0;
    temp = 0;

    /* Sanity check radius */
    if (r < 0) return ;
    /* Special case for r=0 - draw a point */
    if (r == 0)
    {
        rtgui_dc_draw_point(dc, x, y);
        return;
    }

    /*
     * Draw arc
     */

    // Octant labelling
    //
    //  \ 5 | 6 /
    //   \  |  /
    //  4 \ | / 7
    //     \|/
    //------+------ +x
    //     /|\
    //  3 / | \ 0
    //   /  |  \
    //  / 2 | 1 \
    //      +y

    drawoct = 0; // 0x00000000
    // whether or not to keep drawing a given octant.
    // For example: 0x00111100 means we're drawing in octants 2-5

    // 0 <= start & end < 360; note that sometimes start > end - if so, arc goes back through 0.
    while (start < 0) start += 360;
    while (end < 0) end += 360;
    /* Fixup angles */
    start = start % 360;
    end = end % 360;


    // now, we find which octants we're drawing in.
    startoct = start / 45;
    endoct = end / 45;
    oct = startoct - 1; // we increment as first step in loop

    //stopval_start, stopval_end; // what values of cx to stop at.
    do
    {
        oct = (oct + 1) % 8;

        if (oct == startoct)
        {
            // need to compute stopval_start for this octant.  Look at picture above if this is unclear
            switch (oct)
            {
            case 0:
            case 3:
                temp = sin(start * M_PI / 180);
                break;
            case 1:
            case 6:
                temp = cos(start * M_PI / 180);
                break;
            case 2:
            case 5:
                temp = -cos(start * M_PI / 180);
                break;
            case 4:
            case 7:
                temp = -sin(start * M_PI / 180);
                break;
            }
            temp *= r;
            stopval_start = (int)temp; // always round down.
            // This isn't arbitrary, but requires graph paper to explain well.
            // The basic idea is that we're always changing drawoct after we draw, so we
            // stop immediately after we render the last sensible pixel at x = ((int)temp).

            // and whether to draw in this octant initially
            if (oct % 2) drawoct |= (1 << oct); // this is basically like saying drawoct[oct] = true, if drawoct were a bool array
            else         drawoct &= 255 - (1 << oct); // this is basically like saying drawoct[oct] = false
        }

        if (oct == endoct)
        {
            // need to compute stopval_end for this octant
            switch (oct)
            {
            case 0:
            case 3:
                temp = sin(end * M_PI / 180);
                break;
            case 1:
            case 6:
                temp = cos(end * M_PI / 180);
                break;
            case 2:
            case 5:
                temp = -cos(end * M_PI / 180);
                break;
            case 4:
            case 7:
                temp = -sin(end * M_PI / 180);
                break;
            }
            temp *= r;
            stopval_end = (int)temp;

            // and whether to draw in this octant initially
            if (startoct == endoct)
            {
                // note:      we start drawing, stop, then start again in this case
                // otherwise: we only draw in this octant, so initialize it to false, it will get set back to true
                if (start > end)
                {
                    // unfortunately, if we're in the same octant and need to draw over the whole circle,
                    // we need to set the rest to true, because the while loop will end at the bottom.
                    drawoct = 255;
                }
                else
                {
                    drawoct &= 255 - (1 << oct);
                }
            }
            else if (oct % 2) drawoct &= 255 - (1 << oct);
            else              drawoct |= (1 << oct);
        }
        else if (oct != startoct)     // already verified that it's != endoct
        {
            drawoct |= (1 << oct); // draw this entire segment
        }
    }
    while (oct != endoct);

    // so now we have what octants to draw and when to draw them.  all that's left is the actual raster code.
    do
    {
        ypcy = y + cy;
        ymcy = y - cy;
        if (cx > 0)
        {
            xpcx = x + cx;
            xmcx = x - cx;
            // always check if we're drawing a certain octant before adding a pixel to that octant.
            if (drawoct & 4)  rtgui_dc_draw_point(dc, xmcx, ypcy); // drawoct & 4 = 22; drawoct[2]
            if (drawoct & 2)  rtgui_dc_draw_point(dc, xpcx, ypcy);
            if (drawoct & 32) rtgui_dc_draw_point(dc, xmcx, ymcy);
            if (drawoct & 64) rtgui_dc_draw_point(dc, xpcx, ymcy);
        }
        else
        {
            if (drawoct & 6)  rtgui_dc_draw_point(dc, x, ypcy); // 4 + 2; drawoct[2] || drawoct[1]
            if (drawoct & 96) rtgui_dc_draw_point(dc, x, ymcy); // 32 + 64
        }

        xpcy = x + cy;
        xmcy = x - cy;
        if (cx > 0 && cx != cy)
        {
            ypcx = y + cx;
            ymcx = y - cx;
            if (drawoct & 8)   rtgui_dc_draw_point(dc, xmcy, ypcx);
            if (drawoct & 1)   rtgui_dc_draw_point(dc, xpcy, ypcx);
            if (drawoct & 16)  rtgui_dc_draw_point(dc, xmcy, ymcx);
            if (drawoct & 128) rtgui_dc_draw_point(dc, xpcy, ymcx);
        }
        else if (cx == 0)
        {
            if (drawoct & 24)  rtgui_dc_draw_point(dc, xmcy, y); // 8 + 16
            if (drawoct & 129) rtgui_dc_draw_point(dc, xpcy, y); // 1 + 128
        }

        /*
         * Update whether we're drawing an octant
         */
        if (stopval_start == cx)
        {
            // works like an on-off switch because start & end may be in the same octant.
            if (drawoct & (1 << startoct)) drawoct &= 255 - (1 << startoct);
            else drawoct |= (1 << startoct);
        }
        if (stopval_end == cx)
        {
            if (drawoct & (1 << endoct)) drawoct &= 255 - (1 << endoct);
            else drawoct |= (1 << endoct);
        }

        /*
         * Update pixels
         */
        if (df < 0)
        {
            df += d_e;
            d_e += 2;
            d_se += 2;
        }
        else
        {
            df += d_se;
            d_e += 2;
            d_se += 4;
            cy--;
        }

        cx++;
    }
    while (cx <= cy);
}
RTM_EXPORT(rtgui_dc_draw_arc);

void rtgui_dc_draw_annulus(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r1, rt_int16_t r2, rt_int16_t start, rt_int16_t end)
{
    rt_int16_t start_x, start_y;
    rt_int16_t end_x, end_y;
    double temp;
    rt_int16_t temp_val = 0;

    /* Sanity check radius */
    if ((r1 < 0) || (r2 < 0)) return ;
    /* Special case for r=0 - draw a point */
    if ((r1 == 0) && (r2 == 0))
    {
        rtgui_dc_draw_point(dc, x, y);
        return;
    }

    while (start < 0) start += 360;
    while (end < 0) end += 360;

    rtgui_dc_draw_arc(dc, x, y, r1, start, end);
    rtgui_dc_draw_arc(dc, x, y, r2, start, end);

    temp     = cos(start * M_PI / 180);
    temp_val = (int)(temp * r1);
    start_x  = x + temp_val;
    temp_val = (int)(temp * r2);
    end_x    = x + temp_val;

    temp     = sin(start * M_PI / 180);
    temp_val = (int)(temp * r1);
    start_y  = y + temp_val;
    temp_val = (int)(temp * r2);
    end_y    = y + temp_val;

    rtgui_dc_draw_line(dc, start_x, start_y, end_x, end_y);

    temp     = cos(end * M_PI / 180);
    temp_val = (int)(temp * r1);
    start_x  = x + temp_val;
    temp_val = (int)(temp * r2);
    end_x    = x + temp_val;

    temp     = sin(end * M_PI / 180);
    temp_val = (int)(temp * r1);
    start_y  = y + temp_val;
    temp_val = (int)(temp * r2);
    end_y    = y + temp_val;

    rtgui_dc_draw_line(dc, start_x, start_y, end_x, end_y);
}
RTM_EXPORT(rtgui_dc_draw_annulus);

void rtgui_dc_draw_ellipse(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry)
{
    int ix, iy;
    int h, i, j, k;
    int oh, oi, oj, ok;
    int xmh, xph, ypk, ymk;
    int xmi, xpi, ymj, ypj;
    int xmj, xpj, ymi, ypi;
    int xmk, xpk, ymh, yph;

    /*
     * Sanity check radii
     */
    if ((rx < 0) || (ry < 0))  return;

    /*
     * Special case for rx=0 - draw a vline
     */
    if (rx == 0)
    {
        rtgui_dc_draw_vline(dc, x, y - ry, y + ry);
        return;
    }

    /*
     * Special case for ry=0 - draw a hline
     */
    if (ry == 0)
    {
        rtgui_dc_draw_hline(dc, x - rx, x + rx, y);
        return;
    }

    /*
     * Init vars
     */
    oh = oi = oj = ok = 0xFFFF;

    if (rx > ry)
    {
        ix = 0;
        iy = rx * 64;

        do
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * ry) / rx;
            k = (i * ry) / rx;

            if (((ok != k) && (oj != k)) || ((oj != j) && (ok != j)) || (k != j))
            {
                xph = x + h;
                xmh = x - h;
                if (k > 0)
                {
                    ypk = y + k;
                    ymk = y - k;
                    rtgui_dc_draw_point(dc, xmh, ypk);
                    rtgui_dc_draw_point(dc, xph, ypk);
                    rtgui_dc_draw_point(dc, xmh, ymk);
                    rtgui_dc_draw_point(dc, xph, ymk);
                }
                else
                {
                    rtgui_dc_draw_point(dc, xmh, y);
                    rtgui_dc_draw_point(dc, xph, y);
                }
                ok = k;
                xpi = x + i;
                xmi = x - i;
                if (j > 0)
                {
                    ypj = y + j;
                    ymj = y - j;
                    rtgui_dc_draw_point(dc, xmi, ypj);
                    rtgui_dc_draw_point(dc, xpi, ypj);
                    rtgui_dc_draw_point(dc, xmi, ymj);
                    rtgui_dc_draw_point(dc, xpi, ymj);
                }
                else
                {
                    rtgui_dc_draw_point(dc, xmi, y);
                    rtgui_dc_draw_point(dc, xpi, y);
                }
                oj = j;
            }

            ix = ix + iy / rx;
            iy = iy - ix / rx;
        }
        while (i > h);
    }
    else
    {
        ix = 0;
        iy = ry * 64;

        do
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * rx) / ry;
            k = (i * rx) / ry;

            if (((oi != i) && (oh != i)) || ((oh != h) && (oi != h) && (i != h)))
            {
                xmj = x - j;
                xpj = x + j;
                if (i > 0)
                {
                    ypi = y + i;
                    ymi = y - i;
                    rtgui_dc_draw_point(dc, xmj, ypi);
                    rtgui_dc_draw_point(dc, xpj, ypi);
                    rtgui_dc_draw_point(dc, xmj, ymi);
                    rtgui_dc_draw_point(dc, xpj, ymi);
                }
                else
                {
                    rtgui_dc_draw_point(dc, xmj, y);
                    rtgui_dc_draw_point(dc, xpj, y);
                }
                oi = i;
                xmk = x - k;
                xpk = x + k;
                if (h > 0)
                {
                    yph = y + h;
                    ymh = y - h;
                    rtgui_dc_draw_point(dc, xmk, yph);
                    rtgui_dc_draw_point(dc, xpk, yph);
                    rtgui_dc_draw_point(dc, xmk, ymh);
                    rtgui_dc_draw_point(dc, xpk, ymh);
                }
                else
                {
                    rtgui_dc_draw_point(dc, xmk, y);
                    rtgui_dc_draw_point(dc, xpk, y);
                }
                oh = h;
            }

            ix = ix + iy / ry;
            iy = iy - ix / ry;
        }
        while (i > h);
    }
}
RTM_EXPORT(rtgui_dc_draw_ellipse);

void rtgui_dc_fill_ellipse(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry)
{
    int ix, iy;
    int h, i, j, k;
    int oh, oi, oj, ok;
    int xmh, xph;
    int xmi, xpi;
    int xmj, xpj;
    int xmk, xpk;

    /*
     * Special case for rx=0 - draw a vline
     */
    if (rx == 0)
    {
        rtgui_dc_draw_vline(dc, x, y - ry, y + ry);
        return;
    }

    /* special case for ry=0 - draw a hline  */
    if (ry == 0)
    {
        rtgui_dc_draw_hline(dc, x - rx, x + rx, y);
        return;
    }

    /*
     * Init vars
     */
    oh = oi = oj = ok = 0xFFFF;

    /*
     * Draw
     */
    if (rx > ry)
    {
        ix = 0;
        iy = rx * 64;

        do
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * ry) / rx;
            k = (i * ry) / rx;

            if ((ok != k) && (oj != k))
            {
                xph = x + h;
                xmh = x - h;
                if (k > 0)
                {
                    rtgui_dc_draw_hline(dc, xmh, xph, y + k);
                    rtgui_dc_draw_hline(dc, xmh, xph, y - k);
                }
                else
                {
                    rtgui_dc_draw_hline(dc, xmh, xph, y);
                }
                ok = k;
            }
            if ((oj != j) && (ok != j) && (k != j))
            {
                xmi = x - i;
                xpi = x + i;
                if (j > 0)
                {
                    rtgui_dc_draw_hline(dc, xmi, xpi, y + j);
                    rtgui_dc_draw_hline(dc, xmi, xpi, y - j);
                }
                else
                {
                    rtgui_dc_draw_hline(dc, xmi, xpi, y);
                }
                oj = j;
            }

            ix = ix + iy / rx;
            iy = iy - ix / rx;

        }
        while (i > h);
    }
    else
    {
        ix = 0;
        iy = ry * 64;

        do
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * rx) / ry;
            k = (i * rx) / ry;

            if ((oi != i) && (oh != i))
            {
                xmj = x - j;
                xpj = x + j;
                if (i > 0)
                {
                    rtgui_dc_draw_hline(dc, xmj, xpj, y + i);
                    rtgui_dc_draw_hline(dc, xmj, xpj, y - i);
                }
                else
                {
                    rtgui_dc_draw_hline(dc, xmj, xpj, y);
                }
                oi = i;
            }
            if ((oh != h) && (oi != h) && (i != h))
            {
                xmk = x - k;
                xpk = x + k;
                if (h > 0)
                {
                    rtgui_dc_draw_hline(dc, xmk, xpk, y + h);
                    rtgui_dc_draw_hline(dc, xmk, xpk, y - h);
                }
                else
                {
                    rtgui_dc_draw_hline(dc, xmk, xpk, y);
                }
                oh = h;
            }
            ix = ix + iy / ry;
            iy = iy - ix / ry;
        }
        while (i > h);
    }
}
RTM_EXPORT(rtgui_dc_fill_ellipse);

void rtgui_dc_draw_pie(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t rad, rt_int16_t start, rt_int16_t end)
{
    double angle, start_angle, end_angle;
    double deltaAngle;
    double dr;
    int numpoints, i;
    int *vx, *vy;

    /* Sanity check radii */
    if (rad < 0) return ;

    /*
     * Fixup angles
     */
    start = start % 360;
    end = end % 360;

    /*
     * Special case for rad=0 - draw a point
     */
    if (rad == 0)
    {
        rtgui_dc_draw_point(dc, x, y);
        return;
    }

    /*
     * Variable setup
     */
    dr = (double) rad;
    deltaAngle = 3.0 / dr;
    start_angle = (double) start * (2.0 * M_PI / 360.0);
    end_angle = (double) end * (2.0 * M_PI / 360.0);
    if (start > end)
    {
        end_angle += (2.0 * M_PI);
    }

    /* We will always have at least 2 points */
    numpoints = 2;

    /* Count points (rather than calculating it) */
    angle = start_angle;
    while (angle < end_angle)
    {
        angle += deltaAngle;
        numpoints++;
    }

    /* Allocate combined vertex array */
    vx = vy = (int *) rtgui_malloc(2 * sizeof(int) * numpoints);
    if (vx == RT_NULL) return ;

    /* Update point to start of vy */
    vy += numpoints;

    /* Center */
    vx[0] = x;
    vy[0] = y;

    /* First vertex */
    angle = start_angle;
    vx[1] = x + (int)(dr * cos(angle));
    vy[1] = y + (int)(dr * sin(angle));

    if (numpoints < 3)
    {
        rtgui_dc_draw_line(dc, vx[0], vy[0], vx[1], vy[1]);
    }
    else
    {
        /* Calculate other vertices */
        i = 2;
        angle = start_angle;
        while (angle < end_angle)
        {
            angle += deltaAngle;
            if (angle > end_angle)
            {
                angle = end_angle;
            }
            vx[i] = x + (int)(dr * cos(angle));
            vy[i] = y + (int)(dr * sin(angle));
            i++;
        }

        /* Draw */
        rtgui_dc_draw_polygon(dc, vx, vy, numpoints);
    }

    /* Free combined vertex array */
    rtgui_free(vx);
    return;
}
RTM_EXPORT(rtgui_dc_draw_pie);

// Octant labelling
//
//  \ 5 | 6 /
//   \  |  /
//  4 \ | / 7
//     \|/
//------+------ +x
//     /|\
//  3 / | \ 0
//   /  |  \
//  / 2 | 1 \
//      +y
static void _draw_octant(struct rtgui_dc *dc,
                         rt_int16_t ox, rt_int16_t oy,
                         rt_int16_t y1, rt_int16_t y2, rt_int16_t x, int oct)
{
    switch (oct % 8)
    {
    case 0:
        rtgui_dc_draw_line(dc, ox +  x, oy + y1, ox +  x, oy + y2);
        break;
    case 1:
        /* Ugly hack to get the edge right. */
        y2 += 1;
        y1 += 1;
        x -= 1;
        rtgui_dc_draw_line(dc, ox + y1, oy +  x, ox + y2, oy +  x);
        break;
    case 2:
        y2 -= 1;
        y1 -= 1;
        x -= 1;
        rtgui_dc_draw_line(dc, ox - y2, oy +  x, ox - y1, oy +  x);
        break;
    case 3:
        x -= 1;
        rtgui_dc_draw_line(dc, ox -  x, oy + y1, ox -  x, oy + y2);
        break;
    case 4:
        x -= 1;
        rtgui_dc_draw_line(dc, ox -  x, oy - y2, ox -  x, oy - y1);
        break;
    case 5:
        y2 -= 1;
        y1 -= 1;
        rtgui_dc_draw_line(dc, ox - y2, oy -  x, ox - y1, oy -  x);
        break;
    case 6:
        y2 += 1;
        y1 += 1;
        rtgui_dc_draw_line(dc, ox + y1, oy -  x, ox + y2, oy -  x);
        break;
    case 7:
        rtgui_dc_draw_line(dc, ox +  x, oy - y2, ox +  x, oy - y1);
        break;
    };
}

static void _fill_small_pie(struct rtgui_dc *dc,
                            rt_int16_t ox, rt_int16_t oy,
                            rt_int16_t rad, rt_int16_t start, rt_int16_t end,
                            int oct)
{
    /* Midpoint circle algorithm. */
    int dk, x, y;
    /* Start X, end X, */
    rt_int16_t sx, ex, ty, my;
    enum {ST_NONE, ST_ARC, ST_TRI} st;

    RT_ASSERT(0 <= start && start <= 45);
    RT_ASSERT(0 <= end && end <= 45);
    if (start == end)
        return;
    RT_ASSERT(start < end);
    RT_ASSERT(rad > 0);

    /* cos(90 - start) == sin(start) */
    sx = rad * sin(start * M_PI / 180);
    ex = rad * sin(end * M_PI / 180);

    dk = 1 - rad;
    x = 0;
    y = rad;

    st = ST_NONE;
    my = ex;
    while (x <= y)
    {
        rt_int16_t lx;

        if (x < sx)
        {
        }
        else if (x == sx)
        {
            /* Start point. */
            st = ST_ARC;
            ty = y;
        }
        else if (x <= ex)
        {
            /* Between the pie. */
            RT_ASSERT(st == ST_ARC);
        }
        else /* x > ex */
        {
            /* End. */
            st = ST_TRI;
            my = y;
            break;
        }

        /* Drawing. */
        if (st == ST_ARC)
        {
            lx = y * sx / ty;
            /* Change from math coordinate to plot coordinate. */
            _draw_octant(dc, ox, oy, lx, x, y, oct);
        }

        /* Midpoint increment. */
        if (dk > 0)
        {
            y--;
            dk += 2 * (x - y) + 5;
        }
        else
        {
            dk += 2 * x + 3;
        }
        x++;
    }
    /* Draw bottom part. */
    for (; y >= 0; y--)
    {
        rt_int16_t lx, rx;

        lx = y * sx / ty;
        rx = y * ex / my;

        _draw_octant(dc, ox, oy, lx, rx, y, oct);
    }
}

void rtgui_dc_fill_pie(struct rtgui_dc *dc,
                       rt_int16_t x, rt_int16_t y, rt_int16_t rad,
                       rt_int16_t start, rt_int16_t end)
{
    /* Sanity check radii */
    if (rad < 0)
        return;
    if (rad == 0)
    {
        rtgui_dc_draw_point(dc, x, y);
        return;
    }

    if (end - start >= 360)
    {
        rtgui_dc_fill_circle(dc, x, y, rad);
        return;
    }
    if (start == end)
        return;

    /*
     * Fixup angles
     */
    while (start < 0)
    {
        start += 360;
        end   += 360;
    }
    while (start >= 360)
    {
        start -= 360;
        end   -= 360;
    }

    if (end < start)
        end += 360;

    while (start / 45 != end / 45)
    {
        /* The start and end are not in the same piece. */
        if ((start / 45) % 2)
        {
            _fill_small_pie(dc, x, y, rad,
                            0, 45 - start % 45, start / 45);
            start += 45 - start % 45;
        }
        else
        {
            _fill_small_pie(dc, x, y, rad,
                            start % 45, 45, start / 45);
            start += 45 - start % 45;
        }
    }
    if ((start / 45) % 2)
    {
        _fill_small_pie(dc, x, y, rad,
                        90 - end % 90, 90 - start % 90, start / 45);
    }
    else
    {
        _fill_small_pie(dc, x, y, rad,
                        start % 45, end % 45, start / 45);
    }

    return;
}
RTM_EXPORT(rtgui_dc_fill_pie);

/*
 * set gc of dc
 */
void rtgui_dc_set_gc(struct rtgui_dc *dc, rtgui_gc_t *gc)
{
    RT_ASSERT(dc != RT_NULL);

    switch (dc->type)
    {
    case RTGUI_DC_CLIENT:
    {
        rtgui_widget_t *owner;
        /* get owner */
        owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);
        owner->gc = *gc;
        break;
    }
    case RTGUI_DC_HW:
    {
        struct rtgui_dc_hw *dc_hw;

        dc_hw = (struct rtgui_dc_hw *) dc;
        RT_ASSERT(dc_hw->owner != RT_NULL);
        dc_hw->owner->gc = *gc;
        break;
    }
    case RTGUI_DC_BUFFER:
    {
        struct rtgui_dc_buffer *dc_buffer;

        dc_buffer = (struct rtgui_dc_buffer *)dc;
        dc_buffer->gc = *gc;
        break;
    }
    }
}
RTM_EXPORT(rtgui_dc_set_gc);

/*
 * get gc of dc
 */
rtgui_gc_t *rtgui_dc_get_gc(struct rtgui_dc *dc)
{
    rtgui_gc_t *gc = RT_NULL;

    RT_ASSERT(dc != RT_NULL);

    switch (dc->type)
    {
    case RTGUI_DC_CLIENT:
    {
        rtgui_widget_t *owner;
        /* get owner */
        owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);
        gc = &owner->gc;
        break;
    }
    case RTGUI_DC_HW:
    {
        struct rtgui_dc_hw *dc_hw;

        dc_hw = (struct rtgui_dc_hw *) dc;
        RT_ASSERT(dc_hw->owner != RT_NULL);
        gc = &dc_hw->owner->gc;
        break;
    }
    case RTGUI_DC_BUFFER:
    {
        struct rtgui_dc_buffer *dc_buffer;

        dc_buffer = (struct rtgui_dc_buffer *)dc;
        gc = &dc_buffer->gc;
        break;
    }
    }

    return gc;
}
RTM_EXPORT(rtgui_dc_get_gc);

/*
 * get visible status of dc
 */
rt_bool_t rtgui_dc_get_visible(struct rtgui_dc *dc)
{
    rt_bool_t result = RT_TRUE;

    RT_ASSERT(dc != RT_NULL);

    if (rtgui_graphic_driver_is_vmode())
        return RT_TRUE;

    switch (dc->type)
    {
    case RTGUI_DC_CLIENT:
    {
        rtgui_widget_t *owner;
        /* get owner */
        owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);
        if (!RTGUI_WIDGET_IS_DC_VISIBLE(owner)) result = RT_FALSE;
        break;
    }
    case RTGUI_DC_HW:
    {
        struct rtgui_dc_hw *dc_hw;

        dc_hw = (struct rtgui_dc_hw *) dc;
        if (!RTGUI_WIDGET_IS_DC_VISIBLE(dc_hw->owner)) result = RT_FALSE;
        break;
    }

    default:
        /* use default value */
        break;
    }

    return result;
}
RTM_EXPORT(rtgui_dc_get_visible);

/*
 * get rect of dc
 */
void rtgui_dc_get_rect(struct rtgui_dc *dc, rtgui_rect_t *rect)
{
    RT_ASSERT(dc != RT_NULL);

    switch (dc->type)
    {
    case RTGUI_DC_CLIENT:
    {
        rtgui_widget_t *owner;
        /* get owner */
        owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);
        /* we should return the clipped rectangular information */
        rect->x1 = owner->clip.extents.x1 - owner->extent.x1;
        rect->y1 = owner->clip.extents.y1 - owner->extent.y1;
        rect->x2 = rect->x1 + owner->clip.extents.x2 - owner->clip.extents.x1;
        rect->y2 = rect->y1 + owner->clip.extents.y2 - owner->clip.extents.y1;
        // rtgui_widget_get_rect(owner, rect);
        break;
    }
    case RTGUI_DC_HW:
    {
        rtgui_widget_t *owner;
        struct rtgui_dc_hw *dc_hw;

        dc_hw = (struct rtgui_dc_hw *) dc;
        owner = dc_hw->owner;
        rtgui_widget_get_rect(owner, rect);
        break;
    }
    case RTGUI_DC_BUFFER:
    {
        struct rtgui_dc_buffer *dc_buffer;

        dc_buffer = (struct rtgui_dc_buffer *)dc;
        rtgui_rect_init(rect, 0, 0, dc_buffer->width, dc_buffer->height);
        break;
    }
    }

    return;
}
RTM_EXPORT(rtgui_dc_get_rect);

rt_uint8_t rtgui_dc_get_pixel_format(struct rtgui_dc *dc)
{
    rt_uint8_t pixel_fmt;

    RT_ASSERT(dc != RT_NULL);

    switch (dc->type)
    {
    case RTGUI_DC_CLIENT:
    case RTGUI_DC_HW:
    {
        struct rtgui_graphic_driver *hw_driver;

        hw_driver = rtgui_graphic_driver_get_default();
        pixel_fmt = hw_driver->pixel_format;
        break;
    }
    case RTGUI_DC_BUFFER:
    {
        struct rtgui_dc_buffer *dc_buffer;

        dc_buffer = (struct rtgui_dc_buffer *)dc;
        pixel_fmt = dc_buffer->pixel_format;
        break;
    }
    default:
        RT_ASSERT(0);
    }

    return pixel_fmt;
}
RTM_EXPORT(rtgui_dc_get_pixel_format);

void rtgui_dc_logic_to_device(struct rtgui_dc *dc, struct rtgui_point *point)
{
    switch (dc->type)
    {
    case RTGUI_DC_CLIENT:
    {
        rtgui_widget_t *owner;
        /* get owner */
        owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);
        point->x += owner->extent.x1;
        point->y += owner->extent.y1;
        break;
    }
    case RTGUI_DC_HW:
    {
        rtgui_widget_t *owner;
        struct rtgui_dc_hw *dc_hw;

        dc_hw = (struct rtgui_dc_hw *) dc;
        owner = dc_hw->owner;
        point->x += owner->extent.x1;
        point->y += owner->extent.y1;
        break;
    }

    case RTGUI_DC_BUFFER: /* no conversion */
        break;
    }
}
RTM_EXPORT(rtgui_dc_logic_to_device);

void rtgui_dc_rect_to_device(struct rtgui_dc *dc, struct rtgui_rect *rect)
{
    switch (dc->type)
    {
    case RTGUI_DC_CLIENT:
    {
        rtgui_widget_t *owner;
        /* get owner */
        owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);

        rtgui_rect_moveto(rect, owner->extent.x1, owner->extent.y1);
        break;
    }
    case RTGUI_DC_HW:
    {
        rtgui_widget_t *owner;
        struct rtgui_dc_hw *dc_hw;

        dc_hw = (struct rtgui_dc_hw *) dc;
        owner = dc_hw->owner;
        rtgui_rect_moveto(rect, owner->extent.x1, owner->extent.y1);
        break;
    }

    case RTGUI_DC_BUFFER: /* no conversion */
        break;
    }
}
RTM_EXPORT(rtgui_dc_rect_to_device);

extern struct rt_mutex cursor_mutex;
extern void rtgui_mouse_show_cursor(void);
extern void rtgui_mouse_hide_cursor(void);

struct rtgui_dc *rtgui_dc_begin_drawing(rtgui_widget_t *owner)
{
    struct rtgui_dc *dc;
    struct rtgui_widget *widget;
    struct rtgui_win *win;

    RT_ASSERT(owner != RT_NULL);

    win = owner->toplevel;
    if (win == RT_NULL)
        return RT_NULL;

    if (!(win->flag & RTGUI_WIN_FLAG_ACTIVATE) &&
            (win->outer_clip.extents.x1 == win->outer_clip.extents.x2 ||
             win->outer_clip.extents.y1 == win->outer_clip.extents.y2))
        return RT_NULL;

    /* increase drawing count */
    win->drawing ++;

    /* always drawing on the virtual mode */
    if (rtgui_graphic_driver_is_vmode() == RT_FALSE)
    {
        /* set the initial visible as true */
        RTGUI_WIDGET_DC_SET_VISIBLE(owner);

        /* check the visible of widget */
        widget = owner;
        while (widget != RT_NULL)
        {
            if (RTGUI_WIDGET_IS_HIDE(widget))
            {
                RTGUI_WIDGET_DC_SET_UNVISIBLE(owner);
                win->drawing --;
                return RT_NULL;
            }
            widget = widget->parent;
        }
    }

    rtgui_screen_lock(RT_WAITING_FOREVER);

    /* create client or hardware DC */
    if ((rtgui_region_is_flat(&owner->clip) == RT_EOK) &&
            rtgui_rect_is_equal(&(owner->extent), &(owner->clip.extents)) == RT_EOK)
        dc = rtgui_dc_hw_create(owner);
    else
        dc = rtgui_dc_client_create(owner);

    if (dc == RT_NULL)
    {
        /* restore drawing counter */
        win->drawing--;
        rtgui_screen_unlock();
    }
    else if (win->drawing == 1 && rtgui_graphic_driver_is_vmode() == RT_FALSE)
    {
#ifdef RTGUI_USING_MOUSE_CURSOR
        rt_mutex_take(&cursor_mutex, RT_WAITING_FOREVER);
        rtgui_mouse_hide_cursor();
#endif

        if (! RTGUI_IS_WINTITLE(win))
        {
            /* send draw begin to server */
            struct rtgui_event_update_begin eupdate;
            RTGUI_EVENT_UPDATE_BEGIN_INIT(&(eupdate));
            eupdate.rect = RTGUI_WIDGET(win)->extent;

            rtgui_server_post_event((struct rtgui_event *)&eupdate, sizeof(eupdate));
        }
    }

    return dc;
}
RTM_EXPORT(rtgui_dc_begin_drawing);

void rtgui_dc_end_drawing(struct rtgui_dc *dc)
{
    struct rtgui_widget *owner;
    struct rtgui_win *win;

    RT_ASSERT(dc != RT_NULL);

    /* get owner */
    if (dc->type == RTGUI_DC_CLIENT)
        owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);
    else if (dc->type == RTGUI_DC_HW)
        owner = ((struct rtgui_dc_hw *)dc)->owner;
    else return ; /* bad DC type */
    /* get window */
    win = owner->toplevel;

    /* decrease drawing counter */
    win->drawing --;
    if (win->drawing == 0 && rtgui_graphic_driver_is_vmode() == RT_FALSE)
    {
#ifdef RTGUI_USING_MOUSE_CURSOR
        rt_mutex_release(&cursor_mutex);
        /* show cursor */
        rtgui_mouse_show_cursor();
#endif

        if (RTGUI_IS_WINTITLE(win))
        {
            /* update screen */
            rtgui_graphic_driver_screen_update(rtgui_graphic_driver_get_default(),
                                               &(owner->extent));
        }
        else
        {
            /* send to server for window update */
            struct rtgui_event_update_end eupdate;
            RTGUI_EVENT_UPDATE_END_INIT(&(eupdate));
            eupdate.rect = owner->extent;

            rtgui_server_post_event((struct rtgui_event *)&eupdate, sizeof(eupdate));
        }
    }

    dc->engine->fini(dc);
    rtgui_screen_unlock();
}
RTM_EXPORT(rtgui_dc_end_drawing);

