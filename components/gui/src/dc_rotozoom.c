/*
 * File      : dc_rotozoom.c
 * This file is part of RT-Thread GUI
 * COPYRIGHT (C) 2006 - 2014, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-03-15     Bernard      porting SDL_gfx to RT-Thread GUI
 */

/*  

SDL_rotozoom.c: rotozoomer, zoomer and shrinker for 32bit or 8bit surfaces

Copyright (C) 2001-2012  Andreas Schiffler

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.

Andreas Schiffler -- aschiffler at ferzkopp dot net
*/

#include <stdlib.h>
#include <string.h>
#include <rtgui/rtgui.h>
#include <rtgui/dc.h>
#include <rtgui/dc_draw.h>
#include <rtgui/color.h>
#include <rtgui/rtgui_system.h>

#include <math.h>

/* ---- Internally used structures */

/*!
\brief A 32 bit RGBA pixel.
*/
typedef struct tColorRGBA {
	rt_uint8_t r;
	rt_uint8_t g;
	rt_uint8_t b;
	rt_uint8_t a;
} tColorRGBA;

/*!
\brief A 8bit Y/palette pixel.
*/
typedef struct tColorY {
	rt_uint8_t y;
} tColorY;

/*! 
\brief Returns maximum of two numbers a and b.
*/
#define MAX(a,b)    (((a) > (b)) ? (a) : (b))

/*! 
\brief Number of guard rows added to destination surfaces.

This is a simple but effective workaround for observed issues.
These rows allocate extra memory and are then hidden from the surface.
Rows are added to the end of destination surfaces when they are allocated. 
This catches any potential overflows which seem to happen with 
just the right src image dimensions and scale/rotation and can lead
to a situation where the program can segfault.
*/
#define GUARD_ROWS (2)

/*!
\brief Lower limit of absolute zoom factor or rotation degrees.
*/
#define VALUE_LIMIT	0.001

void rtgui_dc_zoom_size(int width, int height, double zoomx, double zoomy, int *dstwidth, int *dstheight);

/*! 
\brief Internal 32 bit integer-factor averaging Shrinker.

Shrinks 32 bit RGBA/ABGR 'src' surface to 'dst' surface.
Averages color and alpha values values of src pixels to calculate dst pixels.
Assumes src and dst surfaces are of 32 bit depth.
Assumes dst surface was allocated with the correct dimensions.

\param src The surface to shrink (input).
\param dst The shrunken surface (output).
\param factorx The horizontal shrinking ratio.
\param factory The vertical shrinking ratio.

\return 0 for success or -1 for error.
*/
int _rtgui_dc_shrink_RGBA(struct rtgui_dc_buffer * src, struct rtgui_dc_buffer * dst, int factorx, int factory)
{
	int x, y, dx, dy, sgap, dgap, ra, ga, ba, aa;
	int n_average;
	tColorRGBA *sp, *osp, *oosp;
	tColorRGBA *dp;

	/*
	* Averaging integer shrink
	*/

	/* Precalculate division factor */
	n_average = factorx*factory;

	/*
	* Scan destination
	*/
	sp = (tColorRGBA *) src->pixel;
	sgap = src->pitch - src->width * 4;
    sgap = sgap;

	dp = (tColorRGBA *) dst->pixel;
	dgap = dst->pitch - dst->width * 4;

	for (y = 0; y < dst->height; y++) 
	{
		osp=sp;
		for (x = 0; x < dst->width; x++) 
		{
			/* Trace out source box and accumulate */
			oosp=sp;
			ra=ga=ba=aa=0;
			for (dy=0; dy < factory; dy++) 
			{
				for (dx=0; dx < factorx; dx++) 
				{
					ra += sp->r;
					ga += sp->g;
					ba += sp->b;
					aa += sp->a;

					sp++;
				} 
				/* src dx loop */
				sp = (tColorRGBA *)((rt_uint8_t*)sp + (src->pitch - 4*factorx)); // next y
			}
			/* src dy loop */

			/* next box-x */
			sp = (tColorRGBA *)((rt_uint8_t*)oosp + 4*factorx);

			/* Store result in destination */
			dp->r = ra/n_average;
			dp->g = ga/n_average;
			dp->b = ba/n_average;
			dp->a = aa/n_average;

			/*
			* Advance destination pointer 
			*/
			dp++;
		} 
		/* dst x loop */

		/* next box-y */
		sp = (tColorRGBA *)((rt_uint8_t*)osp + src->pitch*factory);

		/*
		* Advance destination pointers 
		*/
		dp = (tColorRGBA *) ((rt_uint8_t *) dp + dgap);
	} 
	/* dst y loop */

	return (0);
}

/*! 
\brief Internal 32 bit Zoomer with optional anti-aliasing by bilinear interpolation.

Zooms 32 bit RGBA/ABGR 'src' surface to 'dst' surface.
Assumes src and dst surfaces are of 32 bit depth.
Assumes dst surface was allocated with the correct dimensions.

\param src The surface to zoom (input).
\param dst The zoomed surface (output).
\param flipx Flag indicating if the image should be horizontally flipped.
\param flipy Flag indicating if the image should be vertically flipped.
\param smooth Antialiasing flag; set to SMOOTHING_ON to enable.

\return 0 for success or -1 for error.
*/
int _rtgui_dc_zoom_RGBA(struct rtgui_dc_buffer * src, struct rtgui_dc_buffer * dst, int flipx, int flipy, int smooth)
{
	int x, y, sx, sy, ssx, ssy, *sax, *say, *csax, *csay, *salast, csx, csy, ex, ey, cx, cy, sstep, sstepx, sstepy;
	tColorRGBA *c00, *c01, *c10, *c11;
	tColorRGBA *sp, *csp, *dp;
	int spixelgap, spixelw, spixelh, dgap, t1, t2;

	/*
	* Allocate memory for row/column increments 
	*/
	if ((sax = (int *) rtgui_malloc((dst->width + 1) * sizeof(rt_uint32_t))) == RT_NULL) {
		return (-1);
	}
	if ((say = (int *) rtgui_malloc((dst->height + 1) * sizeof(rt_uint32_t))) == RT_NULL) {
		rtgui_free(sax);
		return (-1);
	}

	/*
	* Precalculate row increments 
	*/
	spixelw = (src->width - 1);
	spixelh = (src->height- 1);
	if (smooth) {
		sx = (int) (65536.0 * (double) spixelw / (double) (dst->width - 1));
		sy = (int) (65536.0 * (double) spixelh / (double) (dst->height - 1));
	} else {
		sx = (int) (65536.0 * (double) (src->width) / (double) (dst->width));
		sy = (int) (65536.0 * (double) (src->height) / (double) (dst->height));
	}

	/* Maximum scaled source size */
	ssx = (src->width << 16) - 1;
	ssy = (src->height << 16) - 1;

	/* Precalculate horizontal row increments */
	csx = 0;
	csax = sax;
	for (x = 0; x <= dst->width; x++) {
		*csax = csx;
		csax++;
		csx += sx;

		/* Guard from overflows */
		if (csx > ssx) { 
			csx = ssx; 
		}
	}

	/* Precalculate vertical row increments */
	csy = 0;
	csay = say;
	for (y = 0; y <= dst->height; y++) {
		*csay = csy;
		csay++;
		csy += sy;

		/* Guard from overflows */
		if (csy > ssy) {
			csy = ssy;
		}
	}

	sp = (tColorRGBA *) src->pixel;
	dp = (tColorRGBA *) dst->pixel;
	dgap = dst->pitch - dst->width * 4;
	spixelgap = src->pitch/4;

	if (flipx) sp += spixelw;
	if (flipy) sp += (spixelgap * spixelh);

	/*
	* Switch between interpolating and non-interpolating code 
	*/
	if (smooth) {

		/*
		* Interpolating Zoom 
		*/
		csay = say;
		for (y = 0; y < dst->height; y++) {
			csp = sp;
			csax = sax;
			for (x = 0; x < dst->width; x++) {
				/*
				* Setup color source pointers 
				*/
				ex = (*csax & 0xffff);
				ey = (*csay & 0xffff);
				cx = (*csax >> 16);
				cy = (*csay >> 16);
				sstepx = cx < spixelw;
				sstepy = cy < spixelh;
				c00 = sp;
				c01 = sp;
				c10 = sp;
				if (sstepy) {
					if (flipy) {
						c10 -= spixelgap;
					} else {
						c10 += spixelgap;
					}
				}
				c11 = c10;
				if (sstepx) {
					if (flipx) {
						c01--;
						c11--;
					} else {
						c01++;
						c11++;
					}
				}

				/*
				* Draw and interpolate colors 
				*/
				t1 = ((((c01->r - c00->r) * ex) >> 16) + c00->r) & 0xff;
				t2 = ((((c11->r - c10->r) * ex) >> 16) + c10->r) & 0xff;
				dp->r = (((t2 - t1) * ey) >> 16) + t1;
				t1 = ((((c01->g - c00->g) * ex) >> 16) + c00->g) & 0xff;
				t2 = ((((c11->g - c10->g) * ex) >> 16) + c10->g) & 0xff;
				dp->g = (((t2 - t1) * ey) >> 16) + t1;
				t1 = ((((c01->b - c00->b) * ex) >> 16) + c00->b) & 0xff;
				t2 = ((((c11->b - c10->b) * ex) >> 16) + c10->b) & 0xff;
				dp->b = (((t2 - t1) * ey) >> 16) + t1;
				t1 = ((((c01->a - c00->a) * ex) >> 16) + c00->a) & 0xff;
				t2 = ((((c11->a - c10->a) * ex) >> 16) + c10->a) & 0xff;
				dp->a = (((t2 - t1) * ey) >> 16) + t1;				
				/*
				* Advance source pointer x
				*/
				salast = csax;
				csax++;				
				sstep = (*csax >> 16) - (*salast >> 16);
				if (flipx) {
					sp -= sstep;
				} else {
					sp += sstep;
				}

				/*
				* Advance destination pointer x
				*/
				dp++;
			}
			/*
			* Advance source pointer y
			*/
			salast = csay;
			csay++;
			sstep = (*csay >> 16) - (*salast >> 16);
			sstep *= spixelgap;
			if (flipy) { 
				sp = csp - sstep;
			} else {
				sp = csp + sstep;
			}

			/*
			* Advance destination pointer y
			*/
			dp = (tColorRGBA *) ((rt_uint8_t *) dp + dgap);
		}
	} else {
		/*
		* Non-Interpolating Zoom 
		*/		
		csay = say;
		for (y = 0; y < dst->height; y++) {
			csp = sp;
			csax = sax;
			for (x = 0; x < dst->width; x++) {
				/*
				* Draw 
				*/
				*dp = *sp;

				/*
				* Advance source pointer x
				*/
				salast = csax;
				csax++;				
				sstep = (*csax >> 16) - (*salast >> 16);
				if (flipx) sstep = -sstep;
				sp += sstep;

				/*
				* Advance destination pointer x
				*/
				dp++;
			}
			/*
			* Advance source pointer y
			*/
			salast = csay;
			csay++;
			sstep = (*csay >> 16) - (*salast >> 16);
			sstep *= spixelgap;
			if (flipy) sstep = -sstep;			
			sp = csp + sstep;

			/*
			* Advance destination pointer y
			*/
			dp = (tColorRGBA *) ((rt_uint8_t *) dp + dgap);
		}
	}

	/*
	* Remove temp arrays 
	*/
	rtgui_free(sax);
	rtgui_free(say);

	return (0);
}

/*! 
\brief Internal 32 bit rotozoomer with optional anti-aliasing.

Rotates and zooms 32 bit RGBA/ABGR 'src' surface to 'dst' surface based on the control 
parameters by scanning the destination surface and applying optionally anti-aliasing
by bilinear interpolation.
Assumes src and dst surfaces are of 32 bit depth.
Assumes dst surface was allocated with the correct dimensions.

\param src Source surface.
\param dst Destination surface.
\param cx Horizontal center coordinate.
\param cy Vertical center coordinate.
\param isin Integer version of sine of angle.
\param icos Integer version of cosine of angle.
\param flipx Flag indicating horizontal mirroring should be applied.
\param flipy Flag indicating vertical mirroring should be applied.
\param smooth Flag indicating anti-aliasing should be used.
*/
int _rtgui_dc_transform_RGBA(struct rtgui_dc_buffer * src, struct rtgui_dc_buffer * dst, 
	int cx, int cy, int isin, int icos, int flipx, int flipy, int smooth)
{
	int x, y, t1, t2, dx, dy, xd, yd, sdx, sdy, ax, ay, ex, ey, sw, sh;
	tColorRGBA c00, c01, c10, c11, cswap;
	tColorRGBA *pc, *sp;
	int gap;

	/*
	* Variable setup 
	*/
	xd = ((src->width - dst->width) << 15);
	yd = ((src->height - dst->height) << 15);
	ax = (cx << 16) - (icos * cx);
	ay = (cy << 16) - (isin * cx);
	sw = src->width - 1;
	sh = src->height - 1;
	pc = (tColorRGBA*) dst->pixel;
	gap = dst->pitch - dst->width * 4;

	/*
	* Switch between interpolating and non-interpolating code 
	*/
	if (smooth) {
		for (y = 0; y < dst->height; y++) 
		{
			dy = cy - y;
			sdx = (ax + (isin * dy)) + xd;
			sdy = (ay - (icos * dy)) + yd;
			for (x = 0; x < dst->width; x++) 
			{
				dx = (sdx >> 16);
				dy = (sdy >> 16);
				if (flipx) dx = sw - dx;
				if (flipy) dy = sh - dy;
				if ((dx > -1) && (dy > -1) && (dx < (src->width-1)) && (dy < (src->height-1))) 
				{
					sp = (tColorRGBA *)src->pixel;;
					sp += ((src->pitch/4) * dy);
					sp += dx;
					c00 = *sp;
					sp += 1;
					c01 = *sp;
					sp += (src->pitch/4);
					c11 = *sp;
					sp -= 1;
					c10 = *sp;
					if (flipx) {
						cswap = c00; c00=c01; c01=cswap;
						cswap = c10; c10=c11; c11=cswap;
					}
					if (flipy) {
						cswap = c00; c00=c10; c10=cswap;
						cswap = c01; c01=c11; c11=cswap;
					}
					/*
					* Interpolate colors 
					*/
					ex = (sdx & 0xffff);
					ey = (sdy & 0xffff);
					t1 = ((((c01.r - c00.r) * ex) >> 16) + c00.r) & 0xff;
					t2 = ((((c11.r - c10.r) * ex) >> 16) + c10.r) & 0xff;
					pc->r = (((t2 - t1) * ey) >> 16) + t1;
					t1 = ((((c01.g - c00.g) * ex) >> 16) + c00.g) & 0xff;
					t2 = ((((c11.g - c10.g) * ex) >> 16) + c10.g) & 0xff;
					pc->g = (((t2 - t1) * ey) >> 16) + t1;
					t1 = ((((c01.b - c00.b) * ex) >> 16) + c00.b) & 0xff;
					t2 = ((((c11.b - c10.b) * ex) >> 16) + c10.b) & 0xff;
					pc->b = (((t2 - t1) * ey) >> 16) + t1;
					t1 = ((((c01.a - c00.a) * ex) >> 16) + c00.a) & 0xff;
					t2 = ((((c11.a - c10.a) * ex) >> 16) + c10.a) & 0xff;
					pc->a = (((t2 - t1) * ey) >> 16) + t1;
				}
				sdx += icos;
				sdy += isin;
				pc++;
			}
			pc = (tColorRGBA *) ((rt_uint8_t *) pc + gap);
		}
	} else {
		for (y = 0; y < dst->height; y++) {
			dy = cy - y;
			sdx = (ax + (isin * dy)) + xd;
			sdy = (ay - (icos * dy)) + yd;
			for (x = 0; x < dst->width; x++) {
				dx = (short) (sdx >> 16);
				dy = (short) (sdy >> 16);
				if (flipx) dx = (src->width-1)-dx;
				if (flipy) dy = (src->height-1)-dy;
				if ((dx >= 0) && (dy >= 0) && (dx < src->width) && (dy < src->height)) {
					sp = (tColorRGBA *) ((rt_uint8_t *) src->pixel + src->pitch * dy);
					sp += dx;
					*pc = *sp;
				}
				sdx += icos;
				sdy += isin;
				pc++;
			}
			pc = (tColorRGBA *) ((rt_uint8_t *) pc + gap);
		}
	}

	return 0;
}

/*!
\brief Rotates a 32 bit surface in increments of 90 degrees.

Specialized 90 degree rotator which rotates a 'src' surface in 90 degree 
increments clockwise returning a new surface. Faster than rotozoomer since
not scanning or interpolation takes place. Input surface must be 32 bit.
(code contributed by J. Schiller, improved by C. Allport and A. Schiffler)

\param src Source surface to rotate.
\param numClockwiseTurns Number of clockwise 90 degree turns to apply to the source.

\returns The new, rotated surface; or RT_NULL for surfaces with incorrect input format.
*/
struct rtgui_dc* rtgui_dc_rotate_90degrees(struct rtgui_dc_buffer* src, int numClockwiseTurns) 
{
	int row, col, newWidth, newHeight;
	int bpp, src_ipr, dst_ipr;
	struct rtgui_dc_buffer* dst;
	rt_uint32_t* srcBuf;
	rt_uint32_t* dstBuf;

	/* sanity check */
	if (src == RT_NULL) return RT_NULL;
	/* we only support 32bit */
	if (rtgui_color_get_bits(src->pixel_format) != 32) return RT_NULL;

	/* normalize numClockwiseTurns */
	while(numClockwiseTurns < 0) { numClockwiseTurns += 4; }
	numClockwiseTurns = (numClockwiseTurns % 4);

	/* if it's even, our new width will be the same as the source surface */
	newWidth = (numClockwiseTurns % 2) ? (src->height) : (src->width);
	newHeight = (numClockwiseTurns % 2) ? (src->width) : (src->height);
	dst = (struct rtgui_dc_buffer*) rtgui_dc_buffer_create_pixformat(RTGRAPHIC_PIXEL_FORMAT_ARGB888, newWidth, newHeight);
	if(!dst) return RT_NULL;

	/* Calculate int-per-row */
	bpp = rtgui_color_get_bpp(src->pixel_format);
	src_ipr = src->pitch / bpp;
	dst_ipr = dst->pitch / bpp;

	switch(numClockwiseTurns) 
	{
	case 0: /* Make a copy of the surface */
		{
			/* Unfortunately SDL_BlitSurface cannot be used to make a copy of the surface
			since it does not preserve alpha. */
			if (src->pitch == dst->pitch) 
			{
				/* If the pitch is the same for both surfaces, the memory can be copied all at once. */
				rt_memcpy(dst->pixel, src->pixel, (src->height * src->pitch));
			}
			else
			{
				/* If the pitch differs, copy each row separately */
				srcBuf = (rt_uint32_t*)(src->pixel); 
				dstBuf = (rt_uint32_t*)(dst->pixel);
				
				for (row = 0; row < src->height; row++) 
				{
					rt_memcpy(dstBuf, srcBuf, dst->width * bpp);
					srcBuf += src_ipr;
					dstBuf += dst_ipr;
				} /* end for(col) */
			} /* end for(row) */
		}
		break;

		/* rotate clockwise */
	case 1: /* rotated 90 degrees clockwise */
		{
			for (row = 0; row < src->height; ++row) {
				srcBuf = (rt_uint32_t*)(src->pixel) + (row * src_ipr);
				dstBuf = (rt_uint32_t*)(dst->pixel) + (dst->width - row - 1);
				for (col = 0; col < src->width; ++col) {
					*dstBuf = *srcBuf;
					++srcBuf;
					dstBuf += dst_ipr;
				} 
				/* end for(col) */
			} 
			/* end for(row) */
		}
		break;

	case 2: /* rotated 180 degrees clockwise */
		{
			for (row = 0; row < src->height; ++row) 
			{
				srcBuf = (rt_uint32_t*)(src->pixel) + (row * src_ipr);
				dstBuf = (rt_uint32_t*)(dst->pixel) + ((dst->height - row - 1) * dst_ipr) + (dst->width - 1);
				for (col = 0; col < src->width; ++col) 
				{
					*dstBuf = *srcBuf;
					++srcBuf;
					--dstBuf;
				} 
			} 
		}
		break;

	case 3:
		{
			for (row = 0; row < src->height; ++row) 
			{
				srcBuf = (rt_uint32_t*)(src->pixel) + (row * src_ipr);
				dstBuf = (rt_uint32_t*)(dst->pixel) + row + ((dst->height - 1) * dst_ipr);
				for (col = 0; col < src->width; ++col) 
				{
					*dstBuf = *srcBuf;
					++srcBuf;
					dstBuf -= dst_ipr;
				} 
			} 
		}
		break;
	} 
	/* end switch */

	return RTGUI_DC(dst);
}

/*!
\brief Internal target surface sizing function for rotozooms with trig result return. 

\param width The source surface width.
\param height The source surface height.
\param angle The angle to rotate in degrees.
\param zoomx The horizontal scaling factor.
\param zoomy The vertical scaling factor.
\param dstwidth The calculated width of the destination surface.
\param dstheight The calculated height of the destination surface.
\param canglezoom The sine of the angle adjusted by the zoom factor.
\param sanglezoom The cosine of the angle adjusted by the zoom factor.

*/
void _rtgui_dc_rotozoom_size(int width, int height, double angle, double zoomx, double zoomy, 
	int *dstwidth, int *dstheight, 
	double *canglezoom, double *sanglezoom)
{
	double x, y, cx, cy, sx, sy;
	double radangle;
	int dstwidthhalf, dstheighthalf;

	/*
	* Determine destination width and height by rotating a centered source box 
	*/
	radangle = angle * (M_PI / 180.0);
	*sanglezoom = sin(radangle);
	*canglezoom = cos(radangle);
	*sanglezoom *= zoomx;
	*canglezoom *= zoomx;
	x = (double)(width / 2);
	y = (double)(height / 2);
	cx = *canglezoom * x;
	cy = *canglezoom * y;
	sx = *sanglezoom * x;
	sy = *sanglezoom * y;

	dstwidthhalf = MAX((int)
		ceil(MAX(MAX(MAX(fabs(cx + sy), fabs(cx - sy)), fabs(-cx + sy)), fabs(-cx - sy))), 1);
	dstheighthalf = MAX((int)
		ceil(MAX(MAX(MAX(fabs(sx + cy), fabs(sx - cy)), fabs(-sx + cy)), fabs(-sx - cy))), 1);
	*dstwidth = 2 * dstwidthhalf;
	*dstheight = 2 * dstheighthalf;
}

/*! 
\brief Returns the size of the resulting target surface for a rotozoomSurface() call. 

\param width The source surface width.
\param height The source surface height.
\param angle The angle to rotate in degrees.
\param zoom The scaling factor.
\param dstwidth The calculated width of the rotozoomed destination surface.
\param dstheight The calculated height of the rotozoomed destination surface.
*/
void rtgui_dc_rotozoom_size(int width, int height, double angle, double zoom, int *dstwidth, int *dstheight)
{
	double dummy_sanglezoom, dummy_canglezoom;

	_rtgui_dc_rotozoom_size(width, height, angle, zoom, zoom, dstwidth, dstheight, &dummy_sanglezoom, &dummy_canglezoom);
}

/*!
\brief Rotates and zooms a surface with different horizontal and vertival scaling factors and optional anti-aliasing. 

Rotates and zooms a 32bit or 8bit 'src' surface to newly created 'dst' surface.
'angle' is the rotation in degrees, 'zoomx and 'zoomy' scaling factors. If 'smooth' is set
then the destination 32bit surface is anti-aliased. If the surface is not 8bit
or 32bit RGBA/ABGR it will be converted into a 32bit RGBA format on the fly.

\param src The surface to rotozoom.
\param angle The angle to rotate in degrees.
\param zoomx The horizontal scaling factor.
\param zoomy The vertical scaling factor.
\param smooth Antialiasing flag; set to SMOOTHING_ON to enable.

\return The new rotozoomed surface.
*/
struct rtgui_dc *rtgui_dc_rotozoom(struct rtgui_dc *dc, double angle, double zoomx, double zoomy, int smooth)
{
	struct rtgui_dc_buffer *rz_src;
	struct rtgui_dc_buffer *rz_dst;
	double zoominv;
	double sanglezoom, canglezoom, sanglezoominv, canglezoominv;
	int dstwidthhalf, dstwidth, dstheighthalf, dstheight;
	int flipx,flipy;
	int result;

	/*
	* Sanity check 
	*/
	rz_src = (struct rtgui_dc_buffer*)(dc);
	if (rz_src == RT_NULL) return (RT_NULL);
	/* we only support 32bit */
	if (rtgui_color_get_bits(rz_src->pixel_format) != 32) return RT_NULL;

	/*
	* Sanity check zoom factor 
	*/
	flipx = (zoomx<0.0);
	if (flipx) zoomx=-zoomx;
	flipy = (zoomy<0.0);
	if (flipy) zoomy=-zoomy;
	if (zoomx < VALUE_LIMIT) zoomx = VALUE_LIMIT;
	if (zoomy < VALUE_LIMIT) zoomy = VALUE_LIMIT;
	zoominv = 65536.0 / (zoomx * zoomx);

	/*
	* Check if we have a rotozoom or just a zoom 
	*/
	if (fabs(angle) > VALUE_LIMIT)
	{
		/*
		* Angle!=0: full rotozoom 
		*/
		/*
		* ----------------------- 
		*/

		/* Determine target size */
		_rtgui_dc_rotozoom_size(rz_src->width, rz_src->height, angle, zoomx, zoomy, &dstwidth, &dstheight, &canglezoom, &sanglezoom);

		/*
		* Calculate target factors from sin/cos and zoom 
		*/
		sanglezoominv = sanglezoom;
		canglezoominv = canglezoom;
		sanglezoominv *= zoominv;
		canglezoominv *= zoominv;

		/* Calculate half size */
		dstwidthhalf = dstwidth / 2;
		dstheighthalf = dstheight / 2;

		/*
		* Alloc space to completely contain the rotated surface 
		*/
		rz_dst = (struct rtgui_dc_buffer*)rtgui_dc_buffer_create_pixformat(RTGRAPHIC_PIXEL_FORMAT_ARGB888, 
			dstwidth, dstheight + GUARD_ROWS);
		/* Check target */
		if (rz_dst == RT_NULL)return RT_NULL;

		/*
		* Call the 32bit transformation routine to do the rotation (using alpha) 
		*/
		result = _rtgui_dc_transform_RGBA(rz_src, rz_dst, dstwidthhalf, dstheighthalf,
			(int) (sanglezoominv), (int) (canglezoominv), 
			flipx, flipy,
			smooth);
		if (result != 0)
		{
			rtgui_dc_destory(RTGUI_DC(rz_dst));
			rz_dst = RT_NULL;			
		}
	} 
	else 
	{
		/*
		* Angle=0: Just a zoom 
		*/

		/*
		* Calculate target size
		*/
		rtgui_dc_zoom_size(rz_src->width, rz_src->height, zoomx, zoomy, &dstwidth, &dstheight);

		/*
		* Alloc space to completely contain the zoomed surface 
		*/
		rz_dst = (struct rtgui_dc_buffer*)rtgui_dc_buffer_create_pixformat(RTGRAPHIC_PIXEL_FORMAT_ARGB888, 
			dstwidth, dstheight + GUARD_ROWS);
		/* Check target */
		if (rz_dst == RT_NULL) return RT_NULL;
		
		/*
		* Call the 32bit transformation routine to do the zooming (using alpha) 
		*/
		result = _rtgui_dc_zoom_RGBA(rz_src, rz_dst, flipx, flipy, smooth);
		if (result != 0)
		{
			rtgui_dc_destory(RTGUI_DC(rz_dst));
			rz_dst = RT_NULL;
		}
	}

	/*
	* Return destination surface 
	*/
	return RTGUI_DC(rz_dst);
}
RTM_EXPORT(rtgui_dc_rotozoom);
/*!
\brief Calculates the size of the target surface for a rtgui_dc_zoom() call.

The minimum size of the target surface is 1. The input factors can be positive or negative.

\param width The width of the source surface to zoom.
\param height The height of the source surface to zoom.
\param zoomx The horizontal zoom factor.
\param zoomy The vertical zoom factor.
\param dstwidth Pointer to an integer to store the calculated width of the zoomed target surface.
\param dstheight Pointer to an integer to store the calculated height of the zoomed target surface.
*/
void rtgui_dc_zoom_size(int width, int height, double zoomx, double zoomy, int *dstwidth, int *dstheight)
{
	/*
	* Make zoom factors positive 
	*/
	int flipx, flipy;
	flipx = (zoomx<0.0);
	if (flipx) zoomx = -zoomx;
	flipy = (zoomy<0.0);
	if (flipy) zoomy = -zoomy;

	/*
	* Sanity check zoom factors 
	*/
	if (zoomx < VALUE_LIMIT) {
		zoomx = VALUE_LIMIT;
	}
	if (zoomy < VALUE_LIMIT) {
		zoomy = VALUE_LIMIT;
	}

	/*
	* Calculate target size 
	*/
	*dstwidth = (int) floor(((double) width * zoomx) + 0.5);
	*dstheight = (int) floor(((double) height * zoomy) + 0.5);
	if (*dstwidth < 1) {
		*dstwidth = 1;
	}
	if (*dstheight < 1) {
		*dstheight = 1;
	}
}

/*! 
\brief Zoom a surface by independent horizontal and vertical factors with optional smoothing.

Zooms a 32bit or 8bit 'src' surface to newly created 'dst' surface.
'zoomx' and 'zoomy' are scaling factors for width and height. If 'smooth' is on
then the destination 32bit surface is anti-aliased. If the surface is not 8bit
or 32bit RGBA/ABGR it will be converted into a 32bit RGBA format on the fly.
If zoom factors are negative, the image is flipped on the axes.

\param src The surface to zoom.
\param zoomx The horizontal zoom factor.
\param zoomy The vertical zoom factor.
\param smooth Antialiasing flag; set to SMOOTHING_ON to enable.

\return The new, zoomed surface.
*/
struct rtgui_dc *rtgui_dc_zoom(struct rtgui_dc *dc, double zoomx, double zoomy, int smooth)
{
	struct rtgui_dc_buffer *rz_src;
	struct rtgui_dc_buffer *rz_dst;
	int dstwidth, dstheight;
	int flipx, flipy;

	/* Sanity check */
	if (dc == RT_NULL) return dc;
	rz_src = (struct rtgui_dc_buffer*)(dc);
	/* we only support 32bit */
	if (rtgui_color_get_bits(rz_src->pixel_format) != 32) return RT_NULL;

	flipx = (zoomx<0.0);
	if (flipx) zoomx = -zoomx;
	flipy = (zoomy<0.0);
	if (flipy) zoomy = -zoomy;

	/* Get size if target */
	rtgui_dc_zoom_size(rz_src->width, rz_src->height, zoomx, zoomy, &dstwidth, &dstheight);

	/*
	* Alloc space to completely contain the zoomed surface 
	*/
	rz_dst = (struct rtgui_dc_buffer*)rtgui_dc_buffer_create_pixformat(RTGRAPHIC_PIXEL_FORMAT_ARGB888, 
		dstwidth, dstheight + GUARD_ROWS);
	/* Check target */
	if (rz_dst == RT_NULL) return RT_NULL;

	/*
	* Call the 32bit transformation routine to do the zooming (using alpha) 
	*/
	if (_rtgui_dc_zoom_RGBA(rz_src, rz_dst, flipx, flipy, smooth) != 0)
	{
		rtgui_dc_destory(RTGUI_DC(rz_dst));
		rz_dst = RT_NULL;
	}

	/*
	* Return destination surface 
	*/
	return RTGUI_DC(rz_dst);
}
RTM_EXPORT(rtgui_dc_zoom);

/*! 
\brief Shrink a dc by an integer ratio using averaging.

Shrinks a 32bit or 8bit 'src' buffer dc to a newly created 'dst' dc.
'factorx' and 'factory' are the shrinking ratios (i.e. 2=1/2 the size,
3=1/3 the size, etc.) The destination dc is antialiased by averaging
the source box RGBA or Y information. If the surface is not 8bit
or 32bit RGBA/ABGR it will be converted into a 32bit RGBA format on the fly.
The input surface is not modified. The output surface is newly allocated.

\param src The surface to shrink.
\param factorx The horizontal shrinking ratio.
\param factory The vertical shrinking ratio.

\return The new, shrunken surface.
*/
struct rtgui_dc *rtgui_dc_shrink(struct rtgui_dc *dc, int factorx, int factory)
{
	struct rtgui_dc_buffer *rz_src;
	struct rtgui_dc_buffer *rz_dst;
	int dstwidth, dstheight;

	/*
	* Sanity check 
	*/
	if (dc == RT_NULL) return dc;
	rz_src = (struct rtgui_dc_buffer*)(dc);
	/* we only support 32bit */
	if (rtgui_color_get_bits(rz_src->pixel_format) != 32) return RT_NULL;

	/* Get size for target */
	dstwidth=rz_src->width/factorx;
	while (dstwidth*factorx>rz_src->width) { dstwidth--; }
	dstheight=rz_src->height/factory;
	while (dstheight*factory>rz_src->height) { dstheight--; }
	
	/*
	* Target surface is 32bit with source RGBA/ABGR ordering 
	*/
	rz_dst = (struct rtgui_dc_buffer*)rtgui_dc_buffer_create_pixformat(RTGRAPHIC_PIXEL_FORMAT_ARGB888, 
		dstwidth, dstheight + GUARD_ROWS);
	/* Check target */
	if (rz_dst == RT_NULL) return RT_NULL;

	/*
	* Call the 32bit transformation routine to do the shrinking (using alpha) 
	*/
	if (_rtgui_dc_shrink_RGBA(rz_src, rz_dst, factorx, factory) != 0)
	{
		rtgui_dc_destory(RTGUI_DC(rz_dst));
		rz_dst = RT_NULL;
	}

	/*
	* Return destination surface 
	*/
	return RTGUI_DC(rz_dst);
}
RTM_EXPORT(rtgui_dc_shrink);

