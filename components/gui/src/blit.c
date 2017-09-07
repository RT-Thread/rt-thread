/*
 * File      : blit.h
 * This file is part of RT-Thread GUI
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
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
 * 2012-01-24     onelife      add one more blit table which exchanges the
 *                             positions of R and B color components in output
 * 2013-10-04     Bernard      porting SDL software render to RT-Thread GUI
 */

/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
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
  3. This notice may not be removed or altered from any source distribution.
*/

#include <rtgui/rtgui.h>
#include <rtgui/blit.h>
#include <rtgui/color.h>

/* Lookup tables to expand partial bytes to the full 0..255 range */

static const rt_uint8_t lookup_0[] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146,
147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171,
172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196,
197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221,
222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246,
247, 248, 249, 250, 251, 252, 253, 254, 255
};

static const rt_uint8_t lookup_1[] = {
0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118,
120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140, 142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166,
168, 170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196, 198, 200, 202, 204, 206, 208, 210, 212, 214,
216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252, 255
};

static const rt_uint8_t lookup_2[] = {
0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 85, 89, 93, 97, 101, 105, 109, 113, 117,
121, 125, 129, 133, 137, 141, 145, 149, 153, 157, 161, 165, 170, 174, 178, 182, 186, 190, 194, 198, 202, 206, 210, 214, 218,
222, 226, 230, 234, 238, 242, 246, 250, 255
};

static const rt_uint8_t lookup_3[] = {
0, 8, 16, 24, 32, 41, 49, 57, 65, 74, 82, 90, 98, 106, 115, 123, 131, 139, 148, 156, 164, 172, 180, 189, 197, 205, 213, 222,
230, 238, 246, 255
};

static const rt_uint8_t lookup_4[] = {
0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255
};

static const rt_uint8_t lookup_5[] = {
0, 36, 72, 109, 145, 182, 218, 255
};

static const rt_uint8_t lookup_6[] = {
0, 85, 170, 255
};

static const rt_uint8_t lookup_7[] = {
0, 255
};

static const rt_uint8_t lookup_8[] = {
255
};

const rt_uint8_t* rtgui_blit_expand_byte[9] = {
    lookup_0,
    lookup_1,
    lookup_2,
    lookup_3,
    lookup_4,
    lookup_5,
    lookup_6,
    lookup_7,
    lookup_8
};

/* 2 bpp to 1 bpp */
static void rtgui_blit_line_2_1(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    return;
}

/* 3 bpp to 1 bpp */
static void rtgui_blit_line_3_1(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    line = line / 3;
    while (line)
    {
        *dst_ptr = (rt_uint8_t)(((*src_ptr & 0x00E00000) >> 16) |
                                ((*(src_ptr + 1) & 0x0000E000) >> 11) |
                                ((*(src_ptr + 2) & 0x000000C0) >> 6));

        src_ptr += 3;
        dst_ptr ++;
        line --;
    }
    return;
}

/* 4 bpp to 1 bpp */
static void rtgui_blit_line_4_1(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    struct _color
    {
        rt_uint8_t r, g, b, a;
    } *c;

    c = (struct _color *)src_ptr;
    while (line-- > 0)
    {
        *dst_ptr = (c->r & 0xe0) | (c->g & 0xc0) >> 3 | (c->b & 0xe0) >> 5 ;

        c ++;
        dst_ptr ++;
    }
}

/* 1 bpp to 2 bpp */
static void rtgui_blit_line_1_2(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    return;
}

/* 3 bpp to 2 bpp */
static void rtgui_blit_line_3_2(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    rt_uint16_t *dst;

    dst = (rt_uint16_t *)dst_ptr;
    line = line / 3;
    while (line)
    {
        *dst = (((*(src_ptr + 2) << 8) & 0x0000F800) |
                ((*(src_ptr + 1) << 3) & 0x000007E0)     |
                ((*src_ptr >> 3) & 0x0000001F));

        src_ptr += 3;
        dst ++;
        line --;
    }

    return;
}

/* 4 bpp to 2 bpp (ARGB --> RGB565) */
static void rtgui_blit_line_4_2(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    int width = line/4;
    rt_uint32_t *srcp = (rt_uint32_t *) src_ptr;
    rt_uint16_t *dstp = (rt_uint16_t *) dst_ptr;

	/* *INDENT-OFF* */
	DUFFS_LOOP4({
	rt_uint32_t s = *srcp;
	unsigned alpha = s >> 27; /* downscale alpha to 5 bits */
	/* FIXME: Here we special-case opaque alpha since the
	   compositioning used (>>8 instead of /255) doesn't handle
	   it correctly. Also special-case alpha=0 for speed?
	   Benchmark this! */
	if(alpha) {
	  if(alpha == (255 >> 3)) {
		*dstp = (rt_uint16_t)((s >> 8 & 0xf800) + (s >> 5 & 0x7e0) + (s >> 3  & 0x1f));
	  } else {
		rt_uint32_t d = *dstp;
		/*
		 * convert source and destination to G0RAB65565
		 * and blend all components at the same time
		 */
		s = ((s & 0xfc00) << 11) + (s >> 8 & 0xf800)
		  + (s >> 3 & 0x1f);
		d = (d | d << 16) & 0x07e0f81f;
		d += (s - d) * alpha >> 5;
		d &= 0x07e0f81f;
		*dstp = (rt_uint16_t)(d | d >> 16);
	  }
	}
	srcp++;
	dstp++;
	}, width);
}

static void rtgui_blit_line_1_3(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    return;
}

#define HI  1
#define LO  0

/* Special optimized blit for RGB 5-6-5 --> RGBA 8-8-8-8 */
static const rt_uint32_t RGB565_RGBA8888_LUT[512] =
{
    0x000000ff, 0x00000000, 0x000008ff, 0x00200000,
    0x000010ff, 0x00400000, 0x000018ff, 0x00610000,
    0x000020ff, 0x00810000, 0x000029ff, 0x00a10000,
    0x000031ff, 0x00c20000, 0x000039ff, 0x00e20000,
    0x000041ff, 0x08000000, 0x00004aff, 0x08200000,
    0x000052ff, 0x08400000, 0x00005aff, 0x08610000,
    0x000062ff, 0x08810000, 0x00006aff, 0x08a10000,
    0x000073ff, 0x08c20000, 0x00007bff, 0x08e20000,
    0x000083ff, 0x10000000, 0x00008bff, 0x10200000,
    0x000094ff, 0x10400000, 0x00009cff, 0x10610000,
    0x0000a4ff, 0x10810000, 0x0000acff, 0x10a10000,
    0x0000b4ff, 0x10c20000, 0x0000bdff, 0x10e20000,
    0x0000c5ff, 0x18000000, 0x0000cdff, 0x18200000,
    0x0000d5ff, 0x18400000, 0x0000deff, 0x18610000,
    0x0000e6ff, 0x18810000, 0x0000eeff, 0x18a10000,
    0x0000f6ff, 0x18c20000, 0x0000ffff, 0x18e20000,
    0x000400ff, 0x20000000, 0x000408ff, 0x20200000,
    0x000410ff, 0x20400000, 0x000418ff, 0x20610000,
    0x000420ff, 0x20810000, 0x000429ff, 0x20a10000,
    0x000431ff, 0x20c20000, 0x000439ff, 0x20e20000,
    0x000441ff, 0x29000000, 0x00044aff, 0x29200000,
    0x000452ff, 0x29400000, 0x00045aff, 0x29610000,
    0x000462ff, 0x29810000, 0x00046aff, 0x29a10000,
    0x000473ff, 0x29c20000, 0x00047bff, 0x29e20000,
    0x000483ff, 0x31000000, 0x00048bff, 0x31200000,
    0x000494ff, 0x31400000, 0x00049cff, 0x31610000,
    0x0004a4ff, 0x31810000, 0x0004acff, 0x31a10000,
    0x0004b4ff, 0x31c20000, 0x0004bdff, 0x31e20000,
    0x0004c5ff, 0x39000000, 0x0004cdff, 0x39200000,
    0x0004d5ff, 0x39400000, 0x0004deff, 0x39610000,
    0x0004e6ff, 0x39810000, 0x0004eeff, 0x39a10000,
    0x0004f6ff, 0x39c20000, 0x0004ffff, 0x39e20000,
    0x000800ff, 0x41000000, 0x000808ff, 0x41200000,
    0x000810ff, 0x41400000, 0x000818ff, 0x41610000,
    0x000820ff, 0x41810000, 0x000829ff, 0x41a10000,
    0x000831ff, 0x41c20000, 0x000839ff, 0x41e20000,
    0x000841ff, 0x4a000000, 0x00084aff, 0x4a200000,
    0x000852ff, 0x4a400000, 0x00085aff, 0x4a610000,
    0x000862ff, 0x4a810000, 0x00086aff, 0x4aa10000,
    0x000873ff, 0x4ac20000, 0x00087bff, 0x4ae20000,
    0x000883ff, 0x52000000, 0x00088bff, 0x52200000,
    0x000894ff, 0x52400000, 0x00089cff, 0x52610000,
    0x0008a4ff, 0x52810000, 0x0008acff, 0x52a10000,
    0x0008b4ff, 0x52c20000, 0x0008bdff, 0x52e20000,
    0x0008c5ff, 0x5a000000, 0x0008cdff, 0x5a200000,
    0x0008d5ff, 0x5a400000, 0x0008deff, 0x5a610000,
    0x0008e6ff, 0x5a810000, 0x0008eeff, 0x5aa10000,
    0x0008f6ff, 0x5ac20000, 0x0008ffff, 0x5ae20000,
    0x000c00ff, 0x62000000, 0x000c08ff, 0x62200000,
    0x000c10ff, 0x62400000, 0x000c18ff, 0x62610000,
    0x000c20ff, 0x62810000, 0x000c29ff, 0x62a10000,
    0x000c31ff, 0x62c20000, 0x000c39ff, 0x62e20000,
    0x000c41ff, 0x6a000000, 0x000c4aff, 0x6a200000,
    0x000c52ff, 0x6a400000, 0x000c5aff, 0x6a610000,
    0x000c62ff, 0x6a810000, 0x000c6aff, 0x6aa10000,
    0x000c73ff, 0x6ac20000, 0x000c7bff, 0x6ae20000,
    0x000c83ff, 0x73000000, 0x000c8bff, 0x73200000,
    0x000c94ff, 0x73400000, 0x000c9cff, 0x73610000,
    0x000ca4ff, 0x73810000, 0x000cacff, 0x73a10000,
    0x000cb4ff, 0x73c20000, 0x000cbdff, 0x73e20000,
    0x000cc5ff, 0x7b000000, 0x000ccdff, 0x7b200000,
    0x000cd5ff, 0x7b400000, 0x000cdeff, 0x7b610000,
    0x000ce6ff, 0x7b810000, 0x000ceeff, 0x7ba10000,
    0x000cf6ff, 0x7bc20000, 0x000cffff, 0x7be20000,
    0x001000ff, 0x83000000, 0x001008ff, 0x83200000,
    0x001010ff, 0x83400000, 0x001018ff, 0x83610000,
    0x001020ff, 0x83810000, 0x001029ff, 0x83a10000,
    0x001031ff, 0x83c20000, 0x001039ff, 0x83e20000,
    0x001041ff, 0x8b000000, 0x00104aff, 0x8b200000,
    0x001052ff, 0x8b400000, 0x00105aff, 0x8b610000,
    0x001062ff, 0x8b810000, 0x00106aff, 0x8ba10000,
    0x001073ff, 0x8bc20000, 0x00107bff, 0x8be20000,
    0x001083ff, 0x94000000, 0x00108bff, 0x94200000,
    0x001094ff, 0x94400000, 0x00109cff, 0x94610000,
    0x0010a4ff, 0x94810000, 0x0010acff, 0x94a10000,
    0x0010b4ff, 0x94c20000, 0x0010bdff, 0x94e20000,
    0x0010c5ff, 0x9c000000, 0x0010cdff, 0x9c200000,
    0x0010d5ff, 0x9c400000, 0x0010deff, 0x9c610000,
    0x0010e6ff, 0x9c810000, 0x0010eeff, 0x9ca10000,
    0x0010f6ff, 0x9cc20000, 0x0010ffff, 0x9ce20000,
    0x001400ff, 0xa4000000, 0x001408ff, 0xa4200000,
    0x001410ff, 0xa4400000, 0x001418ff, 0xa4610000,
    0x001420ff, 0xa4810000, 0x001429ff, 0xa4a10000,
    0x001431ff, 0xa4c20000, 0x001439ff, 0xa4e20000,
    0x001441ff, 0xac000000, 0x00144aff, 0xac200000,
    0x001452ff, 0xac400000, 0x00145aff, 0xac610000,
    0x001462ff, 0xac810000, 0x00146aff, 0xaca10000,
    0x001473ff, 0xacc20000, 0x00147bff, 0xace20000,
    0x001483ff, 0xb4000000, 0x00148bff, 0xb4200000,
    0x001494ff, 0xb4400000, 0x00149cff, 0xb4610000,
    0x0014a4ff, 0xb4810000, 0x0014acff, 0xb4a10000,
    0x0014b4ff, 0xb4c20000, 0x0014bdff, 0xb4e20000,
    0x0014c5ff, 0xbd000000, 0x0014cdff, 0xbd200000,
    0x0014d5ff, 0xbd400000, 0x0014deff, 0xbd610000,
    0x0014e6ff, 0xbd810000, 0x0014eeff, 0xbda10000,
    0x0014f6ff, 0xbdc20000, 0x0014ffff, 0xbde20000,
    0x001800ff, 0xc5000000, 0x001808ff, 0xc5200000,
    0x001810ff, 0xc5400000, 0x001818ff, 0xc5610000,
    0x001820ff, 0xc5810000, 0x001829ff, 0xc5a10000,
    0x001831ff, 0xc5c20000, 0x001839ff, 0xc5e20000,
    0x001841ff, 0xcd000000, 0x00184aff, 0xcd200000,
    0x001852ff, 0xcd400000, 0x00185aff, 0xcd610000,
    0x001862ff, 0xcd810000, 0x00186aff, 0xcda10000,
    0x001873ff, 0xcdc20000, 0x00187bff, 0xcde20000,
    0x001883ff, 0xd5000000, 0x00188bff, 0xd5200000,
    0x001894ff, 0xd5400000, 0x00189cff, 0xd5610000,
    0x0018a4ff, 0xd5810000, 0x0018acff, 0xd5a10000,
    0x0018b4ff, 0xd5c20000, 0x0018bdff, 0xd5e20000,
    0x0018c5ff, 0xde000000, 0x0018cdff, 0xde200000,
    0x0018d5ff, 0xde400000, 0x0018deff, 0xde610000,
    0x0018e6ff, 0xde810000, 0x0018eeff, 0xdea10000,
    0x0018f6ff, 0xdec20000, 0x0018ffff, 0xdee20000,
    0x001c00ff, 0xe6000000, 0x001c08ff, 0xe6200000,
    0x001c10ff, 0xe6400000, 0x001c18ff, 0xe6610000,
    0x001c20ff, 0xe6810000, 0x001c29ff, 0xe6a10000,
    0x001c31ff, 0xe6c20000, 0x001c39ff, 0xe6e20000,
    0x001c41ff, 0xee000000, 0x001c4aff, 0xee200000,
    0x001c52ff, 0xee400000, 0x001c5aff, 0xee610000,
    0x001c62ff, 0xee810000, 0x001c6aff, 0xeea10000,
    0x001c73ff, 0xeec20000, 0x001c7bff, 0xeee20000,
    0x001c83ff, 0xf6000000, 0x001c8bff, 0xf6200000,
    0x001c94ff, 0xf6400000, 0x001c9cff, 0xf6610000,
    0x001ca4ff, 0xf6810000, 0x001cacff, 0xf6a10000,
    0x001cb4ff, 0xf6c20000, 0x001cbdff, 0xf6e20000,
    0x001cc5ff, 0xff000000, 0x001ccdff, 0xff200000,
    0x001cd5ff, 0xff400000, 0x001cdeff, 0xff610000,
    0x001ce6ff, 0xff810000, 0x001ceeff, 0xffa10000,
    0x001cf6ff, 0xffc20000, 0x001cffff, 0xffe20000,
};

/* Special optimized blit for RGB 5-6-5 --> ARGB 8-8-8-8 */
static const rt_uint32_t RGB565_ARGB8888_LUT[512] = {
    0x00000000, 0xff000000, 0x00000008, 0xff002000,
    0x00000010, 0xff004000, 0x00000018, 0xff006100,
    0x00000020, 0xff008100, 0x00000029, 0xff00a100,
    0x00000031, 0xff00c200, 0x00000039, 0xff00e200,
    0x00000041, 0xff080000, 0x0000004a, 0xff082000,
    0x00000052, 0xff084000, 0x0000005a, 0xff086100,
    0x00000062, 0xff088100, 0x0000006a, 0xff08a100,
    0x00000073, 0xff08c200, 0x0000007b, 0xff08e200,
    0x00000083, 0xff100000, 0x0000008b, 0xff102000,
    0x00000094, 0xff104000, 0x0000009c, 0xff106100,
    0x000000a4, 0xff108100, 0x000000ac, 0xff10a100,
    0x000000b4, 0xff10c200, 0x000000bd, 0xff10e200,
    0x000000c5, 0xff180000, 0x000000cd, 0xff182000,
    0x000000d5, 0xff184000, 0x000000de, 0xff186100,
    0x000000e6, 0xff188100, 0x000000ee, 0xff18a100,
    0x000000f6, 0xff18c200, 0x000000ff, 0xff18e200,
    0x00000400, 0xff200000, 0x00000408, 0xff202000,
    0x00000410, 0xff204000, 0x00000418, 0xff206100,
    0x00000420, 0xff208100, 0x00000429, 0xff20a100,
    0x00000431, 0xff20c200, 0x00000439, 0xff20e200,
    0x00000441, 0xff290000, 0x0000044a, 0xff292000,
    0x00000452, 0xff294000, 0x0000045a, 0xff296100,
    0x00000462, 0xff298100, 0x0000046a, 0xff29a100,
    0x00000473, 0xff29c200, 0x0000047b, 0xff29e200,
    0x00000483, 0xff310000, 0x0000048b, 0xff312000,
    0x00000494, 0xff314000, 0x0000049c, 0xff316100,
    0x000004a4, 0xff318100, 0x000004ac, 0xff31a100,
    0x000004b4, 0xff31c200, 0x000004bd, 0xff31e200,
    0x000004c5, 0xff390000, 0x000004cd, 0xff392000,
    0x000004d5, 0xff394000, 0x000004de, 0xff396100,
    0x000004e6, 0xff398100, 0x000004ee, 0xff39a100,
    0x000004f6, 0xff39c200, 0x000004ff, 0xff39e200,
    0x00000800, 0xff410000, 0x00000808, 0xff412000,
    0x00000810, 0xff414000, 0x00000818, 0xff416100,
    0x00000820, 0xff418100, 0x00000829, 0xff41a100,
    0x00000831, 0xff41c200, 0x00000839, 0xff41e200,
    0x00000841, 0xff4a0000, 0x0000084a, 0xff4a2000,
    0x00000852, 0xff4a4000, 0x0000085a, 0xff4a6100,
    0x00000862, 0xff4a8100, 0x0000086a, 0xff4aa100,
    0x00000873, 0xff4ac200, 0x0000087b, 0xff4ae200,
    0x00000883, 0xff520000, 0x0000088b, 0xff522000,
    0x00000894, 0xff524000, 0x0000089c, 0xff526100,
    0x000008a4, 0xff528100, 0x000008ac, 0xff52a100,
    0x000008b4, 0xff52c200, 0x000008bd, 0xff52e200,
    0x000008c5, 0xff5a0000, 0x000008cd, 0xff5a2000,
    0x000008d5, 0xff5a4000, 0x000008de, 0xff5a6100,
    0x000008e6, 0xff5a8100, 0x000008ee, 0xff5aa100,
    0x000008f6, 0xff5ac200, 0x000008ff, 0xff5ae200,
    0x00000c00, 0xff620000, 0x00000c08, 0xff622000,
    0x00000c10, 0xff624000, 0x00000c18, 0xff626100,
    0x00000c20, 0xff628100, 0x00000c29, 0xff62a100,
    0x00000c31, 0xff62c200, 0x00000c39, 0xff62e200,
    0x00000c41, 0xff6a0000, 0x00000c4a, 0xff6a2000,
    0x00000c52, 0xff6a4000, 0x00000c5a, 0xff6a6100,
    0x00000c62, 0xff6a8100, 0x00000c6a, 0xff6aa100,
    0x00000c73, 0xff6ac200, 0x00000c7b, 0xff6ae200,
    0x00000c83, 0xff730000, 0x00000c8b, 0xff732000,
    0x00000c94, 0xff734000, 0x00000c9c, 0xff736100,
    0x00000ca4, 0xff738100, 0x00000cac, 0xff73a100,
    0x00000cb4, 0xff73c200, 0x00000cbd, 0xff73e200,
    0x00000cc5, 0xff7b0000, 0x00000ccd, 0xff7b2000,
    0x00000cd5, 0xff7b4000, 0x00000cde, 0xff7b6100,
    0x00000ce6, 0xff7b8100, 0x00000cee, 0xff7ba100,
    0x00000cf6, 0xff7bc200, 0x00000cff, 0xff7be200,
    0x00001000, 0xff830000, 0x00001008, 0xff832000,
    0x00001010, 0xff834000, 0x00001018, 0xff836100,
    0x00001020, 0xff838100, 0x00001029, 0xff83a100,
    0x00001031, 0xff83c200, 0x00001039, 0xff83e200,
    0x00001041, 0xff8b0000, 0x0000104a, 0xff8b2000,
    0x00001052, 0xff8b4000, 0x0000105a, 0xff8b6100,
    0x00001062, 0xff8b8100, 0x0000106a, 0xff8ba100,
    0x00001073, 0xff8bc200, 0x0000107b, 0xff8be200,
    0x00001083, 0xff940000, 0x0000108b, 0xff942000,
    0x00001094, 0xff944000, 0x0000109c, 0xff946100,
    0x000010a4, 0xff948100, 0x000010ac, 0xff94a100,
    0x000010b4, 0xff94c200, 0x000010bd, 0xff94e200,
    0x000010c5, 0xff9c0000, 0x000010cd, 0xff9c2000,
    0x000010d5, 0xff9c4000, 0x000010de, 0xff9c6100,
    0x000010e6, 0xff9c8100, 0x000010ee, 0xff9ca100,
    0x000010f6, 0xff9cc200, 0x000010ff, 0xff9ce200,
    0x00001400, 0xffa40000, 0x00001408, 0xffa42000,
    0x00001410, 0xffa44000, 0x00001418, 0xffa46100,
    0x00001420, 0xffa48100, 0x00001429, 0xffa4a100,
    0x00001431, 0xffa4c200, 0x00001439, 0xffa4e200,
    0x00001441, 0xffac0000, 0x0000144a, 0xffac2000,
    0x00001452, 0xffac4000, 0x0000145a, 0xffac6100,
    0x00001462, 0xffac8100, 0x0000146a, 0xffaca100,
    0x00001473, 0xffacc200, 0x0000147b, 0xfface200,
    0x00001483, 0xffb40000, 0x0000148b, 0xffb42000,
    0x00001494, 0xffb44000, 0x0000149c, 0xffb46100,
    0x000014a4, 0xffb48100, 0x000014ac, 0xffb4a100,
    0x000014b4, 0xffb4c200, 0x000014bd, 0xffb4e200,
    0x000014c5, 0xffbd0000, 0x000014cd, 0xffbd2000,
    0x000014d5, 0xffbd4000, 0x000014de, 0xffbd6100,
    0x000014e6, 0xffbd8100, 0x000014ee, 0xffbda100,
    0x000014f6, 0xffbdc200, 0x000014ff, 0xffbde200,
    0x00001800, 0xffc50000, 0x00001808, 0xffc52000,
    0x00001810, 0xffc54000, 0x00001818, 0xffc56100,
    0x00001820, 0xffc58100, 0x00001829, 0xffc5a100,
    0x00001831, 0xffc5c200, 0x00001839, 0xffc5e200,
    0x00001841, 0xffcd0000, 0x0000184a, 0xffcd2000,
    0x00001852, 0xffcd4000, 0x0000185a, 0xffcd6100,
    0x00001862, 0xffcd8100, 0x0000186a, 0xffcda100,
    0x00001873, 0xffcdc200, 0x0000187b, 0xffcde200,
    0x00001883, 0xffd50000, 0x0000188b, 0xffd52000,
    0x00001894, 0xffd54000, 0x0000189c, 0xffd56100,
    0x000018a4, 0xffd58100, 0x000018ac, 0xffd5a100,
    0x000018b4, 0xffd5c200, 0x000018bd, 0xffd5e200,
    0x000018c5, 0xffde0000, 0x000018cd, 0xffde2000,
    0x000018d5, 0xffde4000, 0x000018de, 0xffde6100,
    0x000018e6, 0xffde8100, 0x000018ee, 0xffdea100,
    0x000018f6, 0xffdec200, 0x000018ff, 0xffdee200,
    0x00001c00, 0xffe60000, 0x00001c08, 0xffe62000,
    0x00001c10, 0xffe64000, 0x00001c18, 0xffe66100,
    0x00001c20, 0xffe68100, 0x00001c29, 0xffe6a100,
    0x00001c31, 0xffe6c200, 0x00001c39, 0xffe6e200,
    0x00001c41, 0xffee0000, 0x00001c4a, 0xffee2000,
    0x00001c52, 0xffee4000, 0x00001c5a, 0xffee6100,
    0x00001c62, 0xffee8100, 0x00001c6a, 0xffeea100,
    0x00001c73, 0xffeec200, 0x00001c7b, 0xffeee200,
    0x00001c83, 0xfff60000, 0x00001c8b, 0xfff62000,
    0x00001c94, 0xfff64000, 0x00001c9c, 0xfff66100,
    0x00001ca4, 0xfff68100, 0x00001cac, 0xfff6a100,
    0x00001cb4, 0xfff6c200, 0x00001cbd, 0xfff6e200,
    0x00001cc5, 0xffff0000, 0x00001ccd, 0xffff2000,
    0x00001cd5, 0xffff4000, 0x00001cde, 0xffff6100,
    0x00001ce6, 0xffff8100, 0x00001cee, 0xffffa100,
    0x00001cf6, 0xffffc200, 0x00001cff, 0xffffe200
};

static void rtgui_blit_line_2_3(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    rt_uint16_t *src;
    rt_uint32_t *dst;

    src = (rt_uint16_t *)src_ptr;
    dst = (rt_uint32_t *)dst_ptr;

    line = line / 2;
    while (line)
    {
        *dst++ = RGB565_RGBA8888_LUT[src[LO] * 2] + RGB565_RGBA8888_LUT[src[HI] * 2 + 1];
        line--;
        src ++;
    }
}

void rtgui_blit_line_direct(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    rt_memcpy(dst_ptr, src_ptr, line);
}

/* convert 4bpp to 3bpp */
static void rtgui_blit_line_4_3(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    line = line / 4;
    while (line)
    {
        *dst_ptr++ = *src_ptr++;
        *dst_ptr++ = *src_ptr++;
        *dst_ptr++ = *src_ptr++;
        src_ptr ++;
        line --;
    }
}

static void rtgui_blit_line_1_4(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
}

static void rtgui_blit_line_2_4(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
}

/* convert 3bpp to 4bpp */
static void rtgui_blit_line_3_4(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    line = line / 4;
    while (line)
    {
        *dst_ptr++ = *src_ptr++;
        *dst_ptr++ = *src_ptr++;
        *dst_ptr++ = *src_ptr++;
        *dst_ptr++ = 0;
        line --;
    }
}

static const rtgui_blit_line_func _blit_table[5][5] =
{
    /* 0_0, 1_0, 2_0, 3_0, 4_0 */
    {RT_NULL, RT_NULL, RT_NULL, RT_NULL, RT_NULL },
    /* 0_1, 1_1, 2_1, 3_1, 4_1 */
    {RT_NULL, rtgui_blit_line_direct, rtgui_blit_line_2_1, rtgui_blit_line_3_1, rtgui_blit_line_4_1 },
    /* 0_2, 1_2, 2_2, 3_2, 4_2 */
    {RT_NULL, rtgui_blit_line_1_2, rtgui_blit_line_direct, rtgui_blit_line_3_2, rtgui_blit_line_4_2 },
    /* 0_3, 1_3, 2_3, 3_3, 4_3 */
    {RT_NULL, rtgui_blit_line_1_3, rtgui_blit_line_2_3, rtgui_blit_line_direct, rtgui_blit_line_4_3 },
    /* 0_4, 1_4, 2_4, 3_4, 4_4 */
    {RT_NULL, rtgui_blit_line_1_4, rtgui_blit_line_2_4, rtgui_blit_line_3_4, rtgui_blit_line_direct },
};

rtgui_blit_line_func rtgui_blit_line_get(int dst_bpp, int src_bpp)
{
    RT_ASSERT(dst_bpp > 0 && dst_bpp < 5);
    RT_ASSERT(src_bpp > 0 && src_bpp < 5);

    return _blit_table[dst_bpp][src_bpp];
}


static void rtgui_blit_line_3_2_inv(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    rt_uint16_t *dst;

    dst = (rt_uint16_t *)dst_ptr;
    line = line / 3;
    while (line)
    {
        *dst = (((*src_ptr << 8) & 0x0000F800) |
                ((*(src_ptr + 1) << 3) & 0x000007E0)     |
                ((*(src_ptr + 2) >> 3) & 0x0000001F));

        src_ptr += 3;
        dst ++;
        line --;
    }

    return;
}

void rtgui_blit_line_2_2_inv(rt_uint8_t *dst_ptr, rt_uint8_t *src_ptr, int line)
{
    rt_uint16_t *dst, *src;

    dst = (rt_uint16_t *)dst_ptr;
    src = (rt_uint16_t *)src_ptr;
    line = line / 2;
    while (line)
    {
        *dst = ((*src << 11) & 0xF800) | (*src & 0x07E0) | ((*src >> 11) & 0x001F);
        src ++;
        dst ++;
        line --;
    }
}

static const rtgui_blit_line_func _blit_table_inv[5][5] =
{
    /* 0_0, 1_0, 2_0, 3_0, 4_0 */
    {RT_NULL, RT_NULL, RT_NULL, RT_NULL, RT_NULL },
    /* 0_1, 1_1, 2_1, 3_1, 4_1 */
    {RT_NULL, rtgui_blit_line_direct, rtgui_blit_line_2_1, rtgui_blit_line_3_1, rtgui_blit_line_4_1 },
    /* 0_2, 1_2, 2_2, 3_2, 4_2 */
    {RT_NULL, rtgui_blit_line_1_2, rtgui_blit_line_2_2_inv, rtgui_blit_line_3_2_inv, rtgui_blit_line_4_2 },
    /* 0_3, 1_3, 2_3, 3_3, 4_3 */
    {RT_NULL, rtgui_blit_line_1_3, rtgui_blit_line_2_3, rtgui_blit_line_direct, rtgui_blit_line_4_3 },
    /* 0_4, 1_4, 2_4, 3_4, 4_4 */
    {RT_NULL, rtgui_blit_line_1_4, rtgui_blit_line_2_4, rtgui_blit_line_3_4, rtgui_blit_line_direct },
};

/* get blit function for BGR565 */
rtgui_blit_line_func rtgui_blit_line_get_inv(int dst_bpp, int src_bpp)
{
    RT_ASSERT(dst_bpp > 0 && dst_bpp < 5);
    RT_ASSERT(src_bpp > 0 && src_bpp < 5);

    return _blit_table_inv[dst_bpp][src_bpp];
}

/* 16bpp special case for per-surface alpha=50%: blend 2 pixels in parallel */
/* blend a single 16 bit pixel at 50% */
#define BLEND16_50(d, s, mask)						\
	((((s & mask) + (d & mask)) >> 1) + (s & d & (~mask & 0xffff)))

/* blend two 16 bit pixels at 50% */
#define BLEND2x16_50(d, s, mask)					     \
	(((s & (mask | mask << 16)) >> 1) + ((d & (mask | mask << 16)) >> 1) \
	 + (s & d & (~(mask | mask << 16))))

static void
Blit16to16SurfaceAlpha128(struct rtgui_blit_info * info, rt_uint16_t mask)
{
    int width = info->dst_w;
    int height = info->dst_h;
    rt_uint16_t *srcp = (rt_uint16_t *) info->src;
    int srcskip = info->src_skip >> 1;
    rt_uint16_t *dstp = (rt_uint16_t *) info->dst;
    int dstskip = info->dst_skip >> 1;

    while (height--) {
        if (((unsigned int) srcp ^ (unsigned int) dstp) & 2) {
            /*
             * Source and destination not aligned, pipeline it.
             * This is mostly a win for big blits but no loss for
             * small ones
             */
            rt_uint32_t prev_sw;
            int w = width;

            /* handle odd destination */
            if ((unsigned int) dstp & 2) {
                rt_uint16_t d = *dstp, s = *srcp;
                *dstp = BLEND16_50(d, s, mask);
                dstp++;
                srcp++;
                w--;
            }
            srcp++;             /* srcp is now 32-bit aligned */

            /* bootstrap pipeline with first halfword */
            prev_sw = ((rt_uint32_t *) srcp)[-1];

            while (w > 1) {
                rt_uint32_t sw, dw, s;
                sw = *(rt_uint32_t *) srcp;
                dw = *(rt_uint32_t *) dstp;
                s = (prev_sw >> 16) + (sw << 16);
                prev_sw = sw;
                *(rt_uint32_t *) dstp = BLEND2x16_50(dw, s, mask);
                dstp += 2;
                srcp += 2;
                w -= 2;
            }

            /* final pixel if any */
            if (w) {
                rt_uint16_t d = *dstp, s;
                s = (rt_uint16_t) (prev_sw >> 16);
                *dstp = BLEND16_50(d, s, mask);
                srcp++;
                dstp++;
            }
            srcp += srcskip - 1;
            dstp += dstskip;
        } else {
            /* source and destination are aligned */
            int w = width;

            /* first odd pixel? */
            if ((unsigned int) srcp & 2) {
                rt_uint16_t d = *dstp, s = *srcp;
                *dstp = BLEND16_50(d, s, mask);
                srcp++;
                dstp++;
                w--;
            }
            /* srcp and dstp are now 32-bit aligned */

            while (w > 1) {
                rt_uint32_t sw = *(rt_uint32_t *) srcp;
                rt_uint32_t dw = *(rt_uint32_t *) dstp;
                *(rt_uint32_t *) dstp = BLEND2x16_50(dw, sw, mask);
                srcp += 2;
                dstp += 2;
                w -= 2;
            }

            /* last odd pixel? */
            if (w) {
                rt_uint16_t d = *dstp, s = *srcp;
                *dstp = BLEND16_50(d, s, mask);
                srcp++;
                dstp++;
            }
            srcp += srcskip;
            dstp += dstskip;
        }
    }
}

/* fast RGB565->RGB565 blending with pixel alpha */
static void
Blit565to565PixelAlpha(struct rtgui_blit_info * info)
{
    unsigned alpha = info->a;
    if (alpha == 128)
    {
        Blit16to16SurfaceAlpha128(info, 0xf7de);
        return;
    }
    else if (alpha == 255)
    {
        int len = info->dst_w * 2;
        int height = info->dst_h;
        rt_uint8_t *srcp = info->src;
        rt_uint8_t *dstp = info->dst;

        while (height--)
        {
            rt_memcpy(dstp, srcp, len);
            dstp += info->dst_skip + len;
            srcp += info->src_skip + len;
        }
        return;
    }
    else
    {
        /* R and B only have 5 bits. So 5 bits of alpha is enough. */
        alpha >>= 3;
    }

    if (alpha == 0)
        return;

    {
        int width = info->dst_w / 2;
        int height = info->dst_h;
        rt_uint32_t *srcp = (rt_uint32_t *) info->src;
        rt_uint32_t *dstp = (rt_uint32_t *) info->dst;

        while (height--) {
            DUFFS_LOOP4(
            {
                rt_uint32_t s = *srcp++;
                rt_uint32_t d = *dstp;
                rt_uint32_t su = (s << 16) | (s >> 16);
                rt_uint32_t du = (d << 16) | (d >> 16);

                s &= 0x07e0f81f;
                d &= 0x07e0f81f;
                su &= 0x07e0f81f;
                du &= 0x07e0f81f;

                du = ((su - du) * alpha / 32 + du) & 0x07e0f81f;
                d = ((s - d) * alpha / 32 + d) & 0x07e0f81f;
                *dstp++ = (du << 16) | (du >> 16) | d;
            }, width);
            /* Deal with the last pixel. */
            if (info->dst_w % 2)
            {
                rt_uint32_t s = *(rt_uint16_t*)srcp;
                rt_uint32_t d = *(rt_uint16_t*)dstp;

                s = (s | s << 16) & 0x07e0f81f;
                d = (d | d << 16) & 0x07e0f81f;
                d += (s - d) * alpha / 32;
                d &= 0x07e0f81f;
                *(rt_uint16_t*)dstp = (rt_uint16_t)(d | d >> 16);
                srcp = (rt_uint32_t*)((unsigned int)srcp + 2);
                dstp = (rt_uint32_t*)((unsigned int)dstp + 2);
            }
            srcp = (rt_uint32_t*)((unsigned int)srcp + info->src_skip);
            dstp = (rt_uint32_t*)((unsigned int)dstp + info->dst_skip);
        }
    }
}

/* fast RGB888->(A)RGB888 blending with surface alpha=128 special case */
static void BlitRGBtoRGBSurfaceAlpha128(struct rtgui_blit_info *info)
{
	int width = info->dst_w;
	int height = info->dst_h;
	rt_uint32_t *srcp = (rt_uint32_t *)info->src;
	int srcskip = info->src_skip >> 2;
	rt_uint32_t *dstp = (rt_uint32_t *)info->dst;
	int dstskip = info->dst_skip >> 2;

	while(height--) {
	    DUFFS_LOOP4({
		    rt_uint32_t s = *srcp++;
		    rt_uint32_t d = *dstp;
		    *dstp++ = ((((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1)
			       + (s & d & 0x00010101)) | 0xff000000;
	    }, width);
	    srcp += srcskip;
	    dstp += dstskip;
	}
}

/* fast RGB888->(A)RGB888 blending with surface alpha */
static void BlitRGBtoRGBSurfaceAlpha(struct rtgui_blit_info *info)
{
	unsigned int alpha = info->a;
	if(alpha == 128) {
		BlitRGBtoRGBSurfaceAlpha128(info);
	} else {
		int width = info->dst_w;
		int height = info->dst_h;
		rt_uint32_t *srcp = (rt_uint32_t *)info->src;
		int srcskip = info->src_skip >> 2;
		rt_uint32_t *dstp = (rt_uint32_t *)info->dst;
		int dstskip = info->dst_skip >> 2;

		while(height--) {
			DUFFS_LOOP4({
				rt_uint32_t s;
				rt_uint32_t d;
				rt_uint32_t s1;
				rt_uint32_t d1;
				s = *srcp;
				d = *dstp;
				s1 = s & 0xff00ff;
				d1 = d & 0xff00ff;
				d1 = (d1 + ((s1 - d1) * alpha >> 8))
				     & 0xff00ff;
				s &= 0xff00;
				d &= 0xff00;
				d = (d + ((s - d) * alpha >> 8)) & 0xff00;
				*dstp = d1 | d | 0xff000000;
				++srcp;
				++dstp;
			}, width);
			srcp += srcskip;
			dstp += dstskip;
		}
	}
}

/* fast ARGB8888->RGB565 blending with pixel alpha */
static void BlitARGBto565PixelAlpha(struct rtgui_blit_info * info)
{
    int width = info->dst_w;
    int height = info->dst_h;
    rt_uint32_t *srcp = (rt_uint32_t *) info->src;
    int srcskip = info->src_skip >> 2;
    rt_uint16_t *dstp = (rt_uint16_t *) info->dst;
    int dstskip = info->dst_skip >> 1;

    while (height--) {
	    /* *INDENT-OFF* */
	    DUFFS_LOOP4({
		rt_uint32_t s = *srcp;
		unsigned alpha = s >> 27; /* downscale alpha to 5 bits */
		/* FIXME: Here we special-case opaque alpha since the
		   compositioning used (>>8 instead of /255) doesn't handle
		   it correctly. Also special-case alpha=0 for speed?
		   Benchmark this! */
		if(alpha) {
		  if(alpha == (255 >> 3)) {
		    *dstp = (rt_uint16_t)((s >> 8 & 0xf800) + (s >> 5 & 0x7e0) + (s >> 3  & 0x1f));
		  } else {
		    rt_uint32_t d = *dstp;
		    /*
		     * convert source and destination to G0RAB65565
		     * and blend all components at the same time
		     */
		    s = ((s & 0xfc00) << 11) + (s >> 8 & 0xf800)
		      + (s >> 3 & 0x1f);
		    d = (d | d << 16) & 0x07e0f81f;
		    d += (s - d) * alpha >> 5;
		    d &= 0x07e0f81f;
		    *dstp = (rt_uint16_t)(d | d >> 16);
		  }
		}
		srcp++;
		dstp++;
	    }, width);
	    /* *INDENT-ON* */
        srcp += srcskip;
        dstp += dstskip;
    }
}

/* fast ARGB888->(A)RGB888 blending with pixel alpha */
static void BlitRGBtoRGBPixelAlpha(struct rtgui_blit_info *info)
{
	int width = info->dst_w;
	int height = info->dst_h;
	rt_uint32_t *srcp = (rt_uint32_t *)info->src;
	int srcskip = info->src_skip >> 2;
	rt_uint32_t *dstp = (rt_uint32_t *)info->dst;
	int dstskip = info->dst_skip >> 2;

	while(height--) {
	    DUFFS_LOOP4({
		rt_uint32_t dalpha;
		rt_uint32_t d;
		rt_uint32_t s1;
		rt_uint32_t d1;
		rt_uint32_t s = *srcp;
		rt_uint32_t alpha = s >> 24;
            
		/* FIXME: Here we special-case opaque alpha since the
		   compositioning used (>>8 instead of /255) doesn't handle
		   it correctly. Also special-case alpha=0 for speed?
		   Benchmark this! */
		if(alpha == 255) {
		    *dstp = (s & 0x00ffffff) | (*dstp & 0xff000000);
		} else {
		    /*
		     * take out the middle component (green), and process
		     * the other two in parallel. One multiply less.
		     */
		    d = *dstp;
		    dalpha = d & 0xff000000;
		    s1 = s & 0xff00ff;
		    d1 = d & 0xff00ff;
		    d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff;
		    s &= 0xff00;
		    d &= 0xff00;
		    d = (d + ((s - d) * alpha >> 8)) & 0xff00;
		    *dstp = d1 | d | dalpha;
		}
		++srcp;
		++dstp;
	    }, width);
	    srcp += srcskip;
	    dstp += dstskip;
	}
}

static void BlitARGB8888toARGB8888PixelAlpha(struct rtgui_blit_info *info)
{
    rt_uint32_t srcpixel;
    rt_uint32_t srcR, srcG, srcB, srcA;
    rt_uint32_t dstpixel;
    rt_uint32_t dstR, dstG, dstB, dstA;

    while (info->dst_h--) {
        rt_uint32_t *src = (rt_uint32_t *)info->src;
        rt_uint32_t *dst = (rt_uint32_t *)info->dst;
        int n = info->dst_w;
        while (n--) {
            srcpixel = *src;
            srcA = (rt_uint8_t)(srcpixel >> 24); srcR = (rt_uint8_t)(srcpixel >> 16); srcG = (rt_uint8_t)(srcpixel >> 8); srcB = (rt_uint8_t)srcpixel;
            dstpixel = *dst;
            dstA = (rt_uint8_t)(dstpixel >> 24); dstR = (rt_uint8_t)(dstpixel >> 16); dstG = (rt_uint8_t)(dstpixel >> 8); dstB = (rt_uint8_t)dstpixel;

            dstR = srcR + ((255 - srcA) * dstR) / 255;
            dstG = srcG + ((255 - srcA) * dstG) / 255;
            dstB = srcB + ((255 - srcA) * dstB) / 255;
            dstA = srcA + ((255 - srcA) * dstA) / 255;

            dstpixel = ((rt_uint32_t)dstA << 24) | ((rt_uint32_t)dstR << 16) | ((rt_uint32_t)dstG << 8) | dstB;
            *dst = dstpixel;
            ++src;
            ++dst;
        }
        info->src += info->src_pitch;
        info->dst += info->dst_pitch;
    }
}

/* Special optimized blit for RGB 5-6-5 --> 32-bit RGB surfaces */
#define RGB565_32(dst, src, map) (map[src[LO]*2] + map[src[HI]*2+1])
static void
BlitRGB565to32(struct rtgui_blit_info * info, const rt_uint32_t* map)
{
    int width, height;
    rt_uint8_t *src;
    rt_uint32_t *dst;
    int srcskip, dstskip;

    /* Set up some basic variables */
    width = info->dst_w;
    height = info->dst_h;
    src = (rt_uint8_t *) info->src;
    srcskip = info->src_skip;
    dst = (rt_uint32_t *) info->dst;
    dstskip = info->dst_skip / 4;

    while (height--) {
        /* *INDENT-OFF* */
        DUFFS_LOOP(
        {
            *dst++ = RGB565_32(dst, src, map);
            src += 2;
        },
        width);
        /* *INDENT-ON* */
        src += srcskip;
        dst += dstskip;
    }
}

static void
BlitRGB565toARGB8888(struct rtgui_blit_info * info)
{
    BlitRGB565to32(info, RGB565_ARGB8888_LUT);
}

void rtgui_blit(struct rtgui_blit_info * info)
{
    if (info->src_h == 0 ||
        info->src_w == 0 ||
        info->dst_h == 0 ||
        info->dst_w == 0)
        return;

    /* We only use the dst_w in the low level drivers. So adjust the info right
     * here. Note the origin is always (0, 0). */
    if (info->src_w < info->dst_w)
    {
        info->dst_w = info->src_w;
        info->dst_skip  = info->dst_pitch - info->dst_w *
                         rtgui_color_get_bpp(info->dst_fmt);
    }
    else if (info->src_w > info->dst_w)
    {
        info->src_skip = info->src_pitch - info->dst_w *
                         rtgui_color_get_bpp(info->src_fmt);
    }

    if (info->src_h < info->dst_h)
        info->dst_h = info->src_h;

	if (info->src_fmt == RTGRAPHIC_PIXEL_FORMAT_RGB565)
	{
		if (info->dst_fmt == RTGRAPHIC_PIXEL_FORMAT_RGB565)
			Blit565to565PixelAlpha(info);
		else if (info->dst_fmt == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
			BlitRGB565toARGB8888(info);
	}
	else if (info->src_fmt == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
	{
		if (info->dst_fmt == RTGRAPHIC_PIXEL_FORMAT_RGB565)
			BlitARGBto565PixelAlpha(info);
		else if (info->dst_fmt == RTGRAPHIC_PIXEL_FORMAT_RGB888)
			BlitRGBtoRGBPixelAlpha(info);
		else if (info->dst_fmt == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
			BlitARGB8888toARGB8888PixelAlpha(info);
	}
    else if (info->src_fmt == RTGRAPHIC_PIXEL_FORMAT_RGB888)
    {
        if (info->dst_fmt == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
            BlitRGBtoRGBSurfaceAlpha(info);
    }
}
RTM_EXPORT(rtgui_blit);

#if 0
void rtgui_blit_client(rtgui_blit_info_src* src, struct rtgui_dc* client, struct rtgui_rect *dc_rect)
{
	int index;
	struct rtgui_widget* widget;
	rtgui_region_t clip_region;
	rtgui_rect_t rect;

	/* get owner widget */
    widget = RTGUI_CONTAINER_OF(client, struct rtgui_widget, dc_type);
	/* get rect information */
	if (dc_rect == NULL) rtgui_dc_get_rect(client, &rect);
	else rect = *dc_rect;

	/* to device */
	rtgui_rect_moveto(&rect, widget->extent.x1, widget->extent.y1);
	/* get the clipped region */
    rtgui_region_intersect_rect(&clip_region, &widget->clip, &rect);

	/* only 1 rect in extant */
	if (clip_region.data == RT_NULL)
	{
		struct rtgui_blit_info info;
	}
	else
	{
		/* blit on each rect */
	    for (index = 0; index < clip_region.data.numRects; index ++)
	    {
	    }
	}

    rtgui_region_fini(&clip_region);
}
RTM_EXPORT(rtgui_blit_client);
#endif

