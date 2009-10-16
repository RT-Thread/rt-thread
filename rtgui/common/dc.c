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
 */
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>

void rtgui_dc_destory(struct rtgui_dc* dc)
{
	if (dc == RT_NULL) return;

	dc->fini(dc);
	rtgui_free(dc);
}

/*
 * draw a point on dc
 */
void rtgui_dc_draw_point(struct rtgui_dc* dc, int x, int y)
{
	if (dc == RT_NULL) return;

	dc->draw_point(dc, x, y);
}

#if 0
void rtgui_dc_draw_point_alpha(struct rtgui_dc* dc, int x, int y, rt_uint8_t alpha)
{
	if (dc == RT_NULL || alpha == 0xff) return;

	if (dc->draw_point_alpha != RT_NULL)
		dc->draw_point_alpha(dc, x, y, alpha);
	else
	{
		rtgui_color_t color;

		/* soft alpha bending */
		color = dc->get_color(dc, int x, int y);
		dc->draw_point(dc, x, y);
	}
}
#endif

/*
 * draw a vertical line on dc
 */
void rtgui_dc_draw_vline(struct rtgui_dc* dc, int x, int y1, int y2)
{
	if (dc == RT_NULL) return;

	dc->draw_vline(dc, x, y1, y2);
}

/*
 * draw a horizontal line on dc
 */
void rtgui_dc_draw_hline(struct rtgui_dc* dc, int x1, int x2, int y)
{
	if (dc == RT_NULL) return;

	dc->draw_hline(dc, x1, x2, y);
}

void rtgui_dc_draw_line (struct rtgui_dc* dc, int x1, int y1, int x2, int y2)
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

		dx = x2 - x1;		/* the horizontal distance of the line */
		dy = y2 - y1;		/* the vertical distance of the line */

#define rtgui_sgn(x) ((x<0)?-1:((x>0)?1:0))	/* macro to return the sign of a number */
#define rtgui_abs(x) ((x)>=0? (x):-(x))		/* macro to return the absolute value */

		dxabs = rtgui_abs(dx);
		dyabs = rtgui_abs(dy);
		sdx = rtgui_sgn(dx);
		sdy = rtgui_sgn(dy);
		x = dyabs >> 1;
		y = dxabs >> 1;
		px = x1;
		py = y1;

		if(dxabs >= dyabs)	/* the line is more horizontal than vertical */
		{
			for(i = 0; i < dxabs; i++)
			{
				y += dyabs;
				if(y >= dxabs)
				{
					y -= dxabs;
					py += sdy;
				}
				px += sdx;

				/* draw this point */
				dc->draw_point(dc, px, py);
			}
		}
		else				/* the line is more vertical than horizontal */
		{
			for(i = 0; i < dyabs; i++)
			{
				x += dxabs;
				if(x >= dyabs)
				{
					x -= dyabs;
					px += sdx;
				}
				py += sdy;

				/* draw this point */
				dc->draw_point(dc, px, py);
			}
		}
	}
}

#if 0
/* AA Line */
#define AAlevels 	256
#define AAbits 		8

int rtgui_dc_draw_line_aa(struct rtgui_dc* dc, rt_int16_t x1, rt_int16_t y1, rt_int16_t x2, rt_int16_t y2)
{
	Sint32 xx0, yy0, xx1, yy1;
	int result;
	rt_uint32_t intshift, erracc, erradj;
	rt_uint32_t erracctmp, wgt, wgtcompmask;
	int dx, dy, tmp, xdir, y0p1, x0pxdir;

	/*
	 * Keep on working with 32bit numbers
	 */
	xx0 = x1;
	yy0 = y1;
	xx1 = x2;
	yy1 = y2;

	/*
	 * Reorder points if required
	 */
	if (yy0 > yy1)
	{
		tmp = yy0;
		yy0 = yy1;
		yy1 = tmp;
		tmp = xx0;
		xx0 = xx1;
		xx1 = tmp;
	}

	/*
	 * Calculate distance
	 */
	dx = xx1 - xx0;
	dy = yy1 - yy0;

	/*
	 * Adjust for negative dx and set xdir
	 */
	if (dx >= 0)
	{
		xdir = 1;
	}
	else
	{
		xdir = -1;
		dx = (-dx);
	}

	/*
	 * Check for special cases
	 */
	if (dx == 0)
	{
		/*
		 * Vertical line
		 */
		rtgui_dc_draw_vline(dc, x1, y1, y2);
		return ;
	}
	else if (dy == 0)
	{
		/*
		 * Horizontal line
		 */
		rtgui_dc_draw_hline(dc, x1, x2, y1);
		return ;
	}
	else if (dx == dy)
	{
		/*
		 * Diagonal line
		 */
		rtgui_dc_draw_line(dc, x1, y1, x2, y2);
		return ;
	}

	/*
	 * Zero accumulator
	 */
	erracc = 0;

	/*
	 * # of bits by which to shift erracc to get intensity level
	 */
	intshift = 32 - AAbits;
	/*
	 * Mask used to flip all bits in an intensity weighting
	 */
	wgtcompmask = AAlevels - 1;

	/*
	 * Draw the initial pixel in the foreground color
	 */
	rtgui_dc_draw_point(dc, x1, y1);

	/*
	 * x-major or y-major?
	 */
	if (dy > dx)
	{
		/*
		 * y-major.  Calculate 16-bit fixed point fractional part of a pixel that
		 * X advances every time Y advances 1 pixel, truncating the result so that
		 * we won't overrun the endpoint along the X axis
		 */
		/*
		 * Not-so-portable version: erradj = ((Uint64)dx << 32) / (Uint64)dy;
		 */
		erradj = ((dx << 16) / dy) << 16;

		/*
		 * draw all pixels other than the first and last
		 */
		x0pxdir = xx0 + xdir;
		while (--dy)
		{
			erracctmp = erracc;
			erracc += erradj;
			if (erracc <= erracctmp)
			{
				/*
				 * rollover in error accumulator, x coord advances
				 */
				xx0 = x0pxdir;
				x0pxdir += xdir;
			}
			yy0++;		/* y-major so always advance Y */

			/*
			 * the AAbits most significant bits of erracc give us the intensity
			 * weighting for this pixel, and the complement of the weighting for
			 * the paired pixel.
			 */
			wgt = (erracc >> intshift) & 255;
			rtgui_dc_draw_point_alpha (dc, xx0, yy0, 255 - wgt);
			rtgui_dc_draw_point_alpha (dc, x0pxdir, yy0, wgt);
		}
	}
	else
	{

		/*
		 * x-major line.  Calculate 16-bit fixed-point fractional part of a pixel
		 * that Y advances each time X advances 1 pixel, truncating the result so
		 * that we won't overrun the endpoint along the X axis.
		 */
		/*
		 * Not-so-portable version: erradj = ((Uint64)dy << 32) / (Uint64)dx;
		 */
		erradj = ((dy << 16) / dx) << 16;

		/*
		 * draw all pixels other than the first and last
		 */
		y0p1 = yy0 + 1;
		while (--dx)
		{

			erracctmp = erracc;
			erracc += erradj;
			if (erracc <= erracctmp)
			{
				/*
				 * Accumulator turned over, advance y
				 */
				yy0 = y0p1;
				y0p1++;
			}
			xx0 += xdir;	/* x-major so always advance X */
			/*
			 * the AAbits most significant bits of erracc give us the intensity
			 * weighting for this pixel, and the complement of the weighting for
			 * the paired pixel.
			 */
			wgt = (erracc >> intshift) & 255;
			rtgui_dc_draw_point_alpha (dc, xx0, yy0, 255 - wgt);
			rtgui_dc_draw_point_alpha (dc, xx0, y0p1, wgt);
		}
	}

	/*
	 * Draw final pixel, always exactly intersected by the line and doesn't
	 * need to be weighted.
	 */
	rtgui_dc_draw_point(dc, x2, y2);
}
#endif

void rtgui_dc_draw_rect (struct rtgui_dc* dc, struct rtgui_rect* rect)
{
	rtgui_dc_draw_hline(dc, rect->x1, rect->x2, rect->y1);
	rtgui_dc_draw_hline(dc, rect->x1, rect->x2, rect->y2 - 1);

	rtgui_dc_draw_vline(dc, rect->x1, rect->y1, rect->y2);
	rtgui_dc_draw_vline(dc, rect->x2 - 1, rect->y1, rect->y2);
}

void rtgui_dc_fill_rect (struct rtgui_dc* dc, struct rtgui_rect* rect)
{
	if (dc == RT_NULL) return;

	dc->fill_rect(dc, rect);
}

void rtgui_dc_blit(struct rtgui_dc* dc, struct rtgui_point* dc_point, struct rtgui_dc* dest, rtgui_rect_t* rect)
{
	if (dc == RT_NULL || dest == RT_NULL || rect == RT_NULL) return;

	dc->blit(dc, dc_point, dest, rect);
}

void rtgui_dc_draw_text (struct rtgui_dc* dc, const rt_uint8_t* text, struct rtgui_rect* rect)
{
	rt_uint32_t len;
	struct rtgui_font *font;
#ifdef RTGUI_USING_FONTHZ
	struct rtgui_font *gb2312_font;
#endif
	struct rtgui_rect text_rect;

	RT_ASSERT(dc != RT_NULL);

	font = rtgui_dc_get_font(dc);
	if (font == RT_NULL)
	{
		/* use system default font */
		font = rtgui_font_default();
	}

#ifdef RTGUI_USING_FONTHZ
	gb2312_font = rtgui_font_refer("hz", font->height);
	if (gb2312_font == RT_NULL)
	{
		gb2312_font = rtgui_font_refer("hz", 16);
	}
#endif

	/* text align */
	rtgui_font_get_metrics(font, text, &text_rect);
	rtgui_rect_moveto_align(rect, &text_rect, rtgui_dc_get_textalign(dc));

#ifdef RTGUI_USING_FONTHZ
	while (*text)
	{
		len = 0;
		while (*(text + len) < 0x80 && *(text + len)) len ++;
		if (len > 0)
		{
			rtgui_font_draw(font, dc, text, len, &text_rect);

			text += len;
		}

		len = 0;
		while (*(text + len) > 0x80) len ++;
		if (len > 0)
		{
			rtgui_font_draw(gb2312_font, dc, text, len, &text_rect);

			text += len;
		}
	}

	rtgui_font_derefer(gb2312_font);
#else
	len = strlen(text);
	rtgui_font_draw(font, dc, text, len, &text_rect);
#endif
}

void rtgui_dc_set_color(struct rtgui_dc* dc, rtgui_color_t color)
{
	if (dc != RT_NULL)
	{
		dc->set_color(dc, color);
	}
}

rtgui_color_t rtgui_dc_get_color(struct rtgui_dc* dc)
{
	if (dc != RT_NULL)
	{
		return dc->get_color(dc);
	}

	return white;
}

void rtgui_dc_set_font(struct rtgui_dc* dc, rtgui_font_t* font)
{
	if (dc != RT_NULL)
	{
		dc->set_font(dc, font);
	}
}

rtgui_font_t* rtgui_dc_get_font(struct rtgui_dc* dc)
{
	if (dc != RT_NULL)
	{
		return dc->get_font(dc);
	}

	return RT_NULL;
}

void rtgui_dc_set_textalign(struct rtgui_dc* dc, rt_int32_t align)
{
	if (dc != RT_NULL)
	{
		dc->set_textalign(dc, align);
	}
}

rt_int32_t rtgui_dc_get_textalign(struct rtgui_dc* dc)
{
	if (dc != RT_NULL)
	{
		return dc->get_textalign(dc);
	}

	return RTGUI_ALIGN_NOT;
}

rt_bool_t rtgui_dc_get_visible(struct rtgui_dc* dc)
{
	if (dc != RT_NULL)
	{
		return dc->get_visible(dc);
	}

	return RT_FALSE;
}

void rtgui_dc_draw_shaded_rect(struct rtgui_dc* dc, rtgui_rect_t* rect,
							   rtgui_color_t c1, rtgui_color_t c2)
{
	RT_ASSERT(dc != RT_NULL);

	rtgui_dc_set_color(dc, c1);
    rtgui_dc_draw_vline(dc, rect->x1, rect->y1, rect->y2);
    rtgui_dc_draw_hline(dc, rect->x1 + 1, rect->x2, rect->y1);

	rtgui_dc_set_color(dc, c2);
    rtgui_dc_draw_vline(dc, rect->x2, rect->y1, rect->y2);
    rtgui_dc_draw_hline(dc, rect->x1, rect->x2 + 1, rect->y2);
}

void rtgui_dc_draw_border(struct rtgui_dc* dc, rtgui_rect_t* rect, int flag)
{
	rtgui_rect_t r;
	rtgui_color_t color;

	if (dc == RT_NULL) return ;

	/* save old color */
	color = rtgui_dc_get_color(dc);

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
		rtgui_dc_set_color(dc, light_grey);
		rtgui_dc_draw_rect(dc, &r);
		break;

	case RTGUI_BORDER_SIMPLE:
		rtgui_dc_set_color(dc, black);
		rtgui_dc_draw_rect(dc, &r);
		break;

	default:
		break;
	}

	/* restore color */
	rtgui_dc_set_color(dc, color);
}

void rtgui_dc_draw_horizontal_line(struct rtgui_dc* dc, int x1, int x2, int y)
{
	rtgui_color_t color;

	if (dc == RT_NULL) return ;

	/* save old color */
	color = rtgui_dc_get_color(dc);

	rtgui_dc_set_color(dc, dark_grey);
	rtgui_dc_draw_hline(dc, x1, x2, y);

	y ++;

	rtgui_dc_set_color(dc, high_light);
	rtgui_dc_draw_hline(dc, x1, x2, y);

	/* restore color */
	rtgui_dc_set_color(dc, color);
}

void rtgui_dc_draw_vertical_line(struct rtgui_dc* dc, int x, int y1, int y2)
{
	rtgui_color_t color;

	if (dc == RT_NULL) return ;

	/* save old color */
	color = rtgui_dc_get_color(dc);

	rtgui_dc_set_color(dc, dark_grey);
	rtgui_dc_draw_hline(dc, x, y1, y2);

	x ++;

	rtgui_dc_set_color(dc, high_light);
	rtgui_dc_draw_hline(dc, x, y1, y2);

	/* restore color */
	rtgui_dc_set_color(dc, color);
}

void rtgui_dc_draw_arrow(struct rtgui_dc* dc, rtgui_rect_t* rect, int kind)
{
	rt_int32_t i;
	rt_int32_t x1, y1, x2, y2;
	rtgui_rect_t r = {0, 0, 0, 0};

    static const rt_uint8_t ARROW_WIDTH  = 7;
    static const rt_uint8_t ARROW_LENGTH = 4;

	x1 = y1 = 0;

	switch (kind)
	{
	case RTGUI_ARRAW_UP:
	case RTGUI_ARRAW_DOWN:
		r.x2 = ARROW_WIDTH;
		r.y2 = ARROW_LENGTH;
		break;

	case RTGUI_ARRAW_LEFT:
	case RTGUI_ARRAW_RIGHT:
		r.x2 = ARROW_LENGTH;
		r.y2 = ARROW_WIDTH;
		break;
	}
	rtgui_rect_moveto_align(rect, &r, RTGUI_ALIGN_CENTER_HORIZONTAL | RTGUI_ALIGN_CENTER_VERTICAL);

	switch (kind)
	{
	case RTGUI_ARRAW_UP:
		x1 = r.x1 + (ARROW_WIDTH - 1)/2;;
		y1 = r.y1;
		break;
	case RTGUI_ARRAW_DOWN:
		x1 = r.x1 + (ARROW_WIDTH - 1)/2;
		y1 = r.y1 + ARROW_LENGTH - 1;
		break;
	case RTGUI_ARRAW_LEFT:
		x1 = r.x1;
		y1 = r.y1 + (ARROW_WIDTH - 1)/2;
		break;
	case RTGUI_ARRAW_RIGHT:
		x1 = r.x1 + ARROW_LENGTH - 1;
		y1 = r.y1 + (ARROW_WIDTH - 1)/2;
		break;
	default:
		return;
	}
	x2 = x1;
	y2 = y1;

	for (i = 0; i < ARROW_LENGTH; i++)
	{
		rtgui_dc_draw_line(dc, x1, y1, x2, y2);

		switch (kind)
		{
		case RTGUI_ARRAW_UP:
			x1 --;
			x2 ++;
			y1 ++;
			y2 ++;
			break;

		case RTGUI_ARRAW_DOWN:
			x1 --;
			x2 ++;
			y1 --;
			y2 --;
			break;

		case RTGUI_ARRAW_LEFT:
			y1 --;
			y2 ++;
			x1 ++;
			x2 ++;
			break;

		case RTGUI_ARRAW_RIGHT:
			y1 --;
			y2 ++;
			x1 --;
			x2 --;
			break;
		}
	}
}

void rtgui_dc_draw_polygon(struct rtgui_dc* dc, const int *vx, const int *vy, int count)
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

static int _int_compare(const void *a, const void *b)
{
	return (*(const int *) a) - (*(const int *) b);
}

void rtgui_dc_fill_polygon(struct rtgui_dc* dc, const int* vx, const int* vy, int count)
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
	poly_ints = (int *) rt_malloc(sizeof(int) * count);
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
	for (y = miny; (y <= maxy); y++) {
		ints = 0;
		for (i = 0; (i < count); i++) {
			if (!i) {
				ind1 = count - 1;
				ind2 = 0;
			} else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = vy[ind1];
			y2 = vy[ind2];
			if (y1 < y2) {
				x1 = vx[ind1];
				x2 = vx[ind2];
			} else if (y1 > y2) {
				y2 = vy[ind1];
				y1 = vy[ind2];
				x2 = vx[ind1];
				x1 = vx[ind2];
			} else {
				continue;
			}

			if ( ((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2)) )
			{
				poly_ints[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			}
		}

		qsort(poly_ints, ints, sizeof(int), _int_compare);

		for (i = 0; (i < ints); i += 2)
		{
			xa = poly_ints[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = poly_ints[i+1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			rtgui_dc_draw_hline(dc, xa, xb, y);
		}
	}
}

void rtgui_dc_draw_circle(struct rtgui_dc* dc, int x, int y, int r)
{
    rt_int16_t cx = 0;
    rt_int16_t cy = r;
    rt_int16_t df = 1 - r;
    rt_int16_t d_e = 3;
    rt_int16_t d_se = -2 * r + 5;
    rt_int16_t xpcx, xmcx, xpcy, xmcy;
    rt_int16_t ypcy, ymcy, ypcx, ymcx;

    /*
     * sanity check radius
     */
    if (r < 0) return ;

    /* special case for r=0 - draw a point  */
    if (r == 0) rtgui_dc_draw_point(dc, x, y);

    /*
     * draw circle
     */
	do
	{
		ypcy = y + cy;
		ymcy = y - cy;
		if (cx > 0)
		{
		    xpcx = x + cx;
		    xmcx = x - cx;
		    rtgui_dc_draw_point(dc, xmcx, ypcy);
		    rtgui_dc_draw_point(dc, xpcx, ypcy);
		    rtgui_dc_draw_point(dc, xmcx, ymcy);
		    rtgui_dc_draw_point(dc, xpcx, ymcy);
		}
		else
		{
		    rtgui_dc_draw_point(dc, x, ymcy);
		    rtgui_dc_draw_point(dc, x, ypcy);
		}
		xpcy = x + cy;
		xmcy = x - cy;
		if ((cx > 0) && (cx != cy))
		{
		    ypcx = y + cx;
		    ymcx = y - cx;
		    rtgui_dc_draw_point(dc, xmcy, ypcx);
		    rtgui_dc_draw_point(dc, xpcy, ypcx);
		    rtgui_dc_draw_point(dc, xmcy, ymcx);
		    rtgui_dc_draw_point(dc, xpcy, ymcx);
		}
		else if (cx == 0)
		{
		    rtgui_dc_draw_point(dc, xmcy, y);
		    rtgui_dc_draw_point(dc, xpcy, y);
		}

	    /*
	     * Update
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
	}while (cx <= cy);
}

void rtgui_dc_fill_circle(struct rtgui_dc* dc, rt_int16_t x, rt_int16_t y, rt_int16_t r)
{
    rt_int16_t cx = 0;
    rt_int16_t cy = r;
    rt_int16_t ocx = (rt_int16_t) 0xffff;
    rt_int16_t ocy = (rt_int16_t) 0xffff;
    rt_int16_t df = 1 - r;
    rt_int16_t d_e = 3;
    rt_int16_t d_se = -2 * r + 5;
    rt_int16_t xpcx, xmcx, xpcy, xmcy;
    rt_int16_t ypcy, ymcy, ypcx, ymcx;

    /*
     * Sanity check radius
     */
    if (r < 0) return;

    /*
     * Special case for r=0 - draw a point
     */
    if (r == 0)
    {
    	rtgui_dc_draw_point(dc, x, y);
		return ;
    }

    /*
     * Draw
     */
    do {
	xpcx = x + cx;
	xmcx = x - cx;
	xpcy = x + cy;
	xmcy = x - cy;
	if (ocy != cy) {
	    if (cy > 0) {
		ypcy = y + cy;
		ymcy = y - cy;
		rtgui_dc_draw_hline(dc, xmcx, xpcx, ypcy);
		rtgui_dc_draw_hline(dc, xmcx, xpcx, ymcy);
	    } else {
		rtgui_dc_draw_hline(dc, xmcx, xpcx, y);
	    }
	    ocy = cy;
	}
	if (ocx != cx) {
	    if (cx != cy) {
		if (cx > 0) {
		    ypcx = y + cx;
		    ymcx = y - cx;
		    rtgui_dc_draw_hline(dc, xmcy, xpcy, ymcx);
		    rtgui_dc_draw_hline(dc, xmcy, xpcy, ypcx);
		} else {
		    rtgui_dc_draw_hline(dc, xmcy, xpcy, y);
		}
	    }
	    ocx = cx;
	}
	/*
	 * Update
	 */
	if (df < 0) {
	    df += d_e;
	    d_e += 2;
	    d_se += 2;
	} else {
	    df += d_se;
	    d_e += 2;
	    d_se += 4;
	    cy--;
	}
	cx++;
    } while (cx <= cy);
}

void rtgui_dc_draw_ellipse(struct rtgui_dc* dc, rt_int16_t x, rt_int16_t y, rt_int16_t rx, rt_int16_t ry)
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
	    } while (i > h);
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
	    } while (i > h);
	}
}

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
    if (ry == 0) {
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
    if (rx > ry) {
	ix = 0;
	iy = rx * 64;

	do {
	    h = (ix + 32) >> 6;
	    i = (iy + 32) >> 6;
	    j = (h * ry) / rx;
	    k = (i * ry) / rx;

	    if ((ok != k) && (oj != k)) {
		xph = x + h;
		xmh = x - h;
		if (k > 0) {
		    rtgui_dc_draw_hline(dc, xmh, xph, y + k);
		    rtgui_dc_draw_hline(dc, xmh, xph, y - k);
		} else {
		    rtgui_dc_draw_hline(dc, xmh, xph, y);
		}
		ok = k;
	    }
	    if ((oj != j) && (ok != j) && (k != j)) {
		xmi = x - i;
		xpi = x + i;
		if (j > 0) {
		    rtgui_dc_draw_hline(dc, xmi, xpi, y + j);
		    rtgui_dc_draw_hline(dc, xmi, xpi, y - j);
		} else {
		    rtgui_dc_draw_hline(dc, xmi, xpi, y);
		}
		oj = j;
	    }

	    ix = ix + iy / rx;
	    iy = iy - ix / rx;

	} while (i > h);
    } else {
	ix = 0;
	iy = ry * 64;

	do {
	    h = (ix + 32) >> 6;
	    i = (iy + 32) >> 6;
	    j = (h * rx) / ry;
	    k = (i * rx) / ry;

	    if ((oi != i) && (oh != i)) {
		xmj = x - j;
		xpj = x + j;
		if (i > 0) {
		    rtgui_dc_draw_hline(dc, xmj, xpj, y + i);
		    rtgui_dc_draw_hline(dc, xmj, xpj, y - i);
		} else {
		    rtgui_dc_draw_hline(dc, xmj, xpj, y);
		}
		oi = i;
	    }
	    if ((oh != h) && (oi != h) && (i != h)) {
		xmk = x - k;
		xpk = x + k;
		if (h > 0) {
		    rtgui_dc_draw_hline(dc, xmk, xpk, y + h);
		    rtgui_dc_draw_hline(dc, xmk, xpk, y - h);
		} else {
		    rtgui_dc_draw_hline(dc, xmk, xpk, y);
		}
		oh = h;
	    }
	    ix = ix + iy / ry;
	    iy = iy - ix / ry;
	} while (i > h);
    }
}

void rtgui_dc_draw_focus_rect(struct rtgui_dc* dc, rtgui_rect_t* rect)
{
	int i;

	for (i = rect->x1; i <= rect->x2; i += 2)
	{
		rtgui_dc_draw_point(dc, i, rect->y1);
		rtgui_dc_draw_point(dc, i, rect->y2);
	}

	for (i = rect->y1; i <= rect->y2; i += 2)
	{
		rtgui_dc_draw_point(dc, rect->x1, i);
		rtgui_dc_draw_point(dc, rect->x2, i);
	}
}

void rtgui_dc_get_rect(struct rtgui_dc*dc, rtgui_rect_t* rect)
{
	if (dc != RT_NULL && rect != RT_NULL)
	{
		dc->get_rect(dc, rect);
	}
}
