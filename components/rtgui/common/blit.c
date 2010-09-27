#include <rtgui/rtgui.h>
#include <rtgui/blit.h>

/* 2 bpp to 1 bpp */
static void rtgui_blit_line_2_1(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
	return;
}

/* 3 bpp to 1 bpp */
static void rtgui_blit_line_3_1(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
	line = line / 3;
	while (line)
	{
		*dst_ptr = (rt_uint8_t)(((*src_ptr & 0x00E00000)>>16)|
			((*(src_ptr + 1) & 0x0000E000)>>11) |
			((*(src_ptr + 2) & 0x000000C0)>>6));

		src_ptr += 3;
		dst_ptr ++;
		line --;
	}
	return;
}

/* 4 bpp to 1 bpp */
static void rtgui_blit_line_4_1(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
	struct _color {rt_uint8_t r, g, b, a;} *c;

	c = (struct _color*)src_ptr;
	while (line-- > 0)
	{
		*dst_ptr = (c->r & 0xe0) | (c->g & 0xc0) >> 3 | (c->b & 0xe0) >> 5 ;

		c ++;
		dst_ptr ++;
	}
}

/* 1 bpp to 2 bpp */
static void rtgui_blit_line_1_2(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
	return;
}

/* 3 bpp to 2 bpp */
static void rtgui_blit_line_3_2(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
	rt_uint16_t* dst;

	dst = (rt_uint16_t*)dst_ptr;
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

/* 4 bpp to 2 bpp */
static void rtgui_blit_line_4_2(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
	struct _color {rt_uint8_t r, g, b, a;} *c;
	rt_uint16_t* ptr;

	c = (struct _color*)src_ptr;
	ptr = (rt_uint16_t*)dst_ptr;

	line = line / 4;
	while (line-- > 0)
	{
		*ptr = ((c->r & 0xf8) << 8) | ((c->g & 0xfc) << 3) | (c->b >> 3);

		c ++;
		ptr ++;
	}
}

static void rtgui_blit_line_1_3(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
	return;
}

#define HI	1
#define LO	0

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

static void rtgui_blit_line_2_3(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
	rt_uint16_t *src;
	rt_uint32_t *dst;

	src = (rt_uint16_t*)src_ptr;
	dst = (rt_uint32_t*)dst_ptr;

	line = line / 2;
	while (line)
	{
		*dst++ = RGB565_RGBA8888_LUT[src[LO]*2] + RGB565_RGBA8888_LUT[src[HI]*2+1];
		line--;
		src ++;
	}
}

void rtgui_blit_line_direct(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
	rt_memcpy(dst_ptr, src_ptr, line);
}

/* convert 4bpp to 3bpp */
static void rtgui_blit_line_4_3(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
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

static void rtgui_blit_line_1_4(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
}

static void rtgui_blit_line_2_4(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
{
}

/* convert 3bpp to 4bpp */
static void rtgui_blit_line_3_4(rt_uint8_t* dst_ptr, rt_uint8_t* src_ptr, int line)
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
	RT_ASSERT(dst_bpp>0 && dst_bpp < 5);
	RT_ASSERT(src_bpp>0 && src_bpp < 5);

	return _blit_table[dst_bpp][src_bpp];
}
