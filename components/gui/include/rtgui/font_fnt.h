#ifndef __FONT_FNT_H__
#define __FONT_FNT_H__

#include <rtgui/font.h>
#include <rtgui/dc.h>

/* fnt font header */
struct fnt_header
{
	rt_uint8_t version[4];
	rt_uint16_t max_width;
	rt_uint16_t height;
	rt_uint16_t ascent;
	rt_uint16_t depth;
	
	rt_uint32_t first_char;
	rt_uint32_t default_char;
	rt_uint32_t size;
	rt_uint32_t nbits;
	rt_uint32_t noffset;
	rt_uint32_t nwidth;
};
typedef rt_uint8_t MWIMAGEBITS;

struct fnt_font
{
	struct fnt_header header;

	const MWIMAGEBITS *bits;   /* nbits */
	const rt_uint16_t *offset; /* noffset */
	const rt_uint8_t  *width;  /* nwidth */
};
extern const struct rtgui_font_engine fnt_font_engine;

struct rtgui_font *fnt_font_create(const char* filename);

#endif

