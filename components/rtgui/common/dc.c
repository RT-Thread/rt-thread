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
 * 2010-09-20	  richard	   modified rtgui_dc_draw_round_rect
 * 2010-09-27     Bernard      fix draw_mono_bmp issue
 * 2011-04-25     Bernard      fix fill polygon issue, which found by loveic
 */
#include <rtgui/dc.h>
#include <rtgui/rtgui_system.h>

#include <string.h>	/* for strlen */
#include <stdlib.h>	/* fir qsort  */

/* for sin/cos etc */
#include <math.h>
#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

static int _int_compare(const void *a, const void *b)
{
	return (*(const int *) a) - (*(const int *) b);
}

void rtgui_dc_destory(struct rtgui_dc* dc)
{
	if (dc == RT_NULL) return;

	dc->engine->fini(dc);
	rtgui_free(dc);
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
				rtgui_dc_draw_point(dc, px, py);
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
				rtgui_dc_draw_point(dc, px, py);
			}
		}
	}
}

void rtgui_dc_draw_horizontal_line(struct rtgui_dc* dc, int x1, int x2, int y)
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

void rtgui_dc_draw_vertical_line(struct rtgui_dc* dc, int x, int y1, int y2)
{
	rtgui_color_t color;

	if (dc == RT_NULL) return ;

	/* save old color */
	color = RTGUI_DC_FC(dc);

	RTGUI_DC_FC(dc) = dark_grey;
	rtgui_dc_draw_hline(dc, x, y1, y2);

	x ++;

	RTGUI_DC_FC(dc) = high_light;
	rtgui_dc_draw_hline(dc, x, y1, y2);

	/* restore color */
	RTGUI_DC_FC(dc) = color;
}

void rtgui_dc_draw_rect (struct rtgui_dc* dc, struct rtgui_rect* rect)
{
	rtgui_dc_draw_hline(dc, rect->x1, rect->x2, rect->y1);
	rtgui_dc_draw_hline(dc, rect->x1, rect->x2, rect->y2 - 1);

	rtgui_dc_draw_vline(dc, rect->x1, rect->y1, rect->y2);
	rtgui_dc_draw_vline(dc, rect->x2 - 1, rect->y1, rect->y2);
}

void rtgui_dc_fill_rect_forecolor(struct rtgui_dc* dc, struct rtgui_rect* rect)
{
    int i = 0;
    
    rtgui_dc_draw_rect(dc, rect);
    do
    {
        rtgui_dc_draw_hline(dc, rect->x1+1, rect->x2-1, rect->y1+i);
		i++;
    }while(!(rect->y1+i == rect->y2));
}

void rtgui_dc_draw_round_rect(struct rtgui_dc* dc, struct rtgui_rect* rect, int r)
{
	RT_ASSERT(((rect->x2 - rect->x1)/2 >= r)&&((rect->y2-rect->y1)/2 >= r));
	
	if(r < 0)
	{
		return;
	}
	
	if(r == 0)
	{
		rtgui_dc_draw_rect(dc, rect);
		return;
	}
	
	if(((rect->x2 - rect->x1)/2 >= r)&&((rect->y2-rect->y1)/2 >= r))
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

void rtgui_dc_fill_round_rect(struct rtgui_dc* dc, struct rtgui_rect* rect, int r)
{
    struct rtgui_rect rect_temp;

	RT_ASSERT(((rect->x2 - rect->x1)/2 >= r)&&((rect->y2-rect->y1)/2 >= r));
	
	if(((rect->x2 - rect->x1)/2 >= r)&&((rect->y2-rect->y1)/2 >= r))
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

void rtgui_dc_draw_shaded_rect(struct rtgui_dc* dc, rtgui_rect_t* rect,
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

void rtgui_dc_draw_focus_rect(struct rtgui_dc* dc, rtgui_rect_t* rect)
{
	int i;

	for (i = rect->x1; i < rect->x2; i += 2)
	{
		rtgui_dc_draw_point(dc, i, rect->y1);
		rtgui_dc_draw_point(dc, i, rect->y2 - 1);
	}

	for (i = rect->y1; i < rect->y2; i += 2)
	{
		rtgui_dc_draw_point(dc, rect->x1, i);
		rtgui_dc_draw_point(dc, rect->x2 - 1, i);
	}
}

void rtgui_dc_draw_text (struct rtgui_dc* dc, const char* text, struct rtgui_rect* rect)
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

	len = strlen((const char*)text);
	rtgui_font_draw(font, dc, text, len, &text_rect);
}

/*
 * draw a monochrome color bitmap data
 */
void rtgui_dc_draw_mono_bmp(struct rtgui_dc* dc, int x, int y, int w, int h, const rt_uint8_t* data)
{
	int i, j, k;

	/* get word bytes */
	w = (w + 7)/8;

	/* draw mono bitmap data */
	for (i = 0; i < h; i ++)
		for (j = 0; j < w; j++)
			for (k = 0; k < 8; k++)
				if ( ((data[i*w + j] >> (7-k)) & 0x01) != 0)
					rtgui_dc_draw_point(dc, x + 8*j + k, y + i);
}

void rtgui_dc_draw_byte(struct rtgui_dc*dc, int x, int y, int h, const rt_uint8_t* data)
{
	rtgui_dc_draw_mono_bmp(dc, x, y, 8, h, data);
}

void rtgui_dc_draw_word(struct rtgui_dc*dc, int x, int y, int h, const rt_uint8_t* data)
{
	rtgui_dc_draw_mono_bmp(dc, x, y, 16, h, data);
}

void rtgui_dc_draw_border(struct rtgui_dc* dc, rtgui_rect_t* rect, int flag)
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

void rtgui_dc_draw_regular_polygon(struct rtgui_dc* dc, int x, int y, int r, int count, rt_uint16_t angle)
{
	int i, temp_val;
	double temp;
	float angle_interval;
	int *xx;
	int *x_head;
	int *yy;
	int *y_head;

	/*
	* Sanity check
	*/
	 if (count < 3) return;
	
    angle_interval = 360.0 / count;

	/*
	* Pointer setup
	*/

	x_head = xx = (int *)rt_malloc(sizeof(int) * count);
	y_head = yy = (int *)rt_malloc(sizeof(int) * count);

    for(i = 0; i < count; i++)
    {
        temp	 = cos(((angle_interval * i) + angle) * M_PI / 180);
        temp     *= r;
	    temp_val = (int)temp;
	    *xx      = temp_val + x;
		
		temp	 = sin(((angle_interval * i) + angle) * M_PI / 180); 
		temp     *= r;
	    temp_val = (int)temp;
	    *yy      = temp_val + y;

	    xx++;
	    yy++;
    }
    
    rtgui_dc_draw_polygon(dc, (const int *)x_head, (const int *)y_head, count);  

	rt_free(x_head);
	rt_free(y_head);

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

	/* release memory */
	rtgui_free(poly_ints);
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
	do {
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
			else		 drawoct &= 255 - (1 << oct); // this is basically like saying drawoct[oct] = false
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
			else			  drawoct |= (1 << oct);
		} else if (oct != startoct) { // already verified that it's != endoct
			drawoct |= (1 << oct); // draw this entire segment
		}
	} while (oct != endoct);

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
	} while (cx <= cy);
}

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
	
	temp	 = cos(start * M_PI / 180);
	temp_val = (int)(temp * r1);
    start_x  = x + temp_val;
	temp_val = (int)(temp * r2);
	end_x    = x + temp_val;

	temp	 = sin(start * M_PI / 180);
	temp_val = (int)(temp * r1);
    start_y  = y + temp_val;
	temp_val = (int)(temp * r2);
	end_y    = y + temp_val; 

    rtgui_dc_draw_line(dc, start_x, start_y, end_x, end_y);

	temp	 = cos(end * M_PI / 180);
	temp_val = (int)(temp * r1);
    start_x  = x + temp_val;
	temp_val = (int)(temp * r2);
	end_x    = x + temp_val;

	temp	 = sin(end * M_PI / 180);
	temp_val = (int)(temp * r1);
    start_y  = y + temp_val;
	temp_val = (int)(temp * r2);
	end_y    = y + temp_val; 

    rtgui_dc_draw_line(dc, start_x, start_y, end_x, end_y);    
}

void rtgui_dc_draw_sector(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end)
{
    int start_x, start_y;
    int end_x, end_y;

    /* Sanity check radius */
	if (r < 0) return ;
	/* Special case for r=0 - draw a point */
	if (r == 0)
	{
		 rtgui_dc_draw_point(dc, x, y);
		 return;
	}
	
	while (start < 0) start += 360;
	while (end < 0) end += 360;

	/* Fixup angles */
	start = start % 360;
	end = end % 360;

    rtgui_dc_draw_arc(dc, x, y, r, start, end);         

    start_x = x + r * cos(start * M_PI / 180);
    start_y = y + r * sin(start * M_PI / 180);

    end_x = x + r * cos(end * M_PI / 180);
    end_y = y + r * sin(end * M_PI / 180);

    rtgui_dc_draw_line(dc, x, y, start_x, start_y);
    rtgui_dc_draw_line(dc, x, y, end_x, end_y); 
}

void rtgui_dc_fill_sector(struct rtgui_dc *dc, rt_int16_t x, rt_int16_t y, rt_int16_t r, rt_int16_t start, rt_int16_t end)
{
    int start_x, start_y;
    int end_x, end_y;

    /* Sanity check radius */
	if (r < 0) return ;
	/* Special case for r=0 - draw a point */
	if (r == 0)
	{
		 rtgui_dc_draw_point(dc, x, y);
		 return;
	}
	
	while (start < 0) start += 360;
	while (end < 0) end += 360;

	/* Fixup angles */
	start = start % 360;
	end = end % 360;

    end_x = x + r * cos(end * M_PI / 180);
    end_y = y + r * sin(end * M_PI / 180);

    do
    {
        start_x = x + r * cos(start * M_PI / 180);
        start_y = y + r * sin(start * M_PI / 180); 
        start ++;
        
	    rtgui_dc_draw_line(dc, x, y, start_x, start_y); 
	}while(!((start_x == end_x) && (start_y == end_y)));
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


