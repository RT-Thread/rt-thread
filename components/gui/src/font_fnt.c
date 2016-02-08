/*
 * rockbox fnt font engine 
 */
#include <rtgui/font_fnt.h>
#include <rtgui/rtgui_system.h>

static void rtgui_fnt_font_draw_text(struct rtgui_font *font, struct rtgui_dc *dc, const char *text, rt_ubase_t len, struct rtgui_rect *rect);
static void rtgui_fnt_font_get_metrics(struct rtgui_font *font, const char *text, rtgui_rect_t *rect);
const struct rtgui_font_engine fnt_font_engine =
{
	RT_NULL,
	RT_NULL,
    rtgui_fnt_font_draw_text,
    rtgui_fnt_font_get_metrics
};

void rtgui_fnt_font_draw_text(struct rtgui_font *font, struct rtgui_dc *dc, const char *text, rt_ubase_t len, struct rtgui_rect *rect)
{
	int ch, i, j, c, width;
	rt_uint32_t position;
	struct fnt_font *fnt;
	rt_uint8_t *data_ptr;

	fnt = (struct fnt_font*)font->data;
	RT_ASSERT(fnt != RT_NULL);

	while (len)
	{
		/* get character */
		ch = *text;
		/* NOTE: we only support asc character right now */
		if (ch > 0x80) 
		{
			text += 1; len -= 1;
			continue;
		}

		/* get position and width */
		if (fnt->offset == RT_NULL)
		{
			width = fnt->header.max_width;
			position = (ch - fnt->header.first_char) * width * ((fnt->header.height + 7)/8);
		}
		else
		{
			width = fnt->width[ch - fnt->header.first_char];
			position = fnt->offset[ch - fnt->header.first_char];
		}

		/* draw a character */
		data_ptr = (rt_uint8_t*)&fnt->bits[position];
		for (i = 0; i < width; i ++) /* x */
		{
			for (j = 0; j < 8; j ++) /* y */
			{
				for (c = 0; c < (fnt->header.height + 7)/8; c ++)
				{
					/* check drawable region */
					if ((rect->x1 + i > rect->x2) || (rect->y1 + c * 8 + j > rect->y2))
						continue;

					if (data_ptr[i + c * width] & (1 << j)) 
						rtgui_dc_draw_point(dc, rect->x1 + i, rect->y1 + c * 8 + j);
				}
			}
		}

		rect->x1 += width;
		text += 1;
		len -= 1;
	}
}

void rtgui_fnt_font_get_metrics(struct rtgui_font *font, const char *text, rtgui_rect_t *rect)
{
	int ch;
	struct fnt_font *fnt;

	fnt = (struct fnt_font*)font->data;
	RT_ASSERT(fnt != RT_NULL);

	rt_memset(rect, 0x00, sizeof(rtgui_rect_t));
	rect->y2 = fnt->header.height;

	while (*text)
	{
		if (fnt->width == RT_NULL)
		{
			/* fixed width font */
			rect->x2 += fnt->header.max_width;
		}
		else
		{
			ch = *text;
			/* NOTE: we only support asc character right now */
			if (ch > 0x80) 
			{
				text += 1;
				continue;
			}
			
			rect->x2 += fnt->width[ch - fnt->header.first_char];
		}

		text += 1;
	}
}

#ifdef RTGUI_USING_FNT_FILE
#include <dfs_posix.h>

rt_inline int readbyte(int fd, unsigned char *cp)
{
	unsigned char buf[1];

	if (read(fd, buf, 1) != 1)
		return 0;
	*cp = buf[0];
	return 1;
}

rt_inline int readshort(int fd, unsigned short *sp)
{
	unsigned char buf[2];

	if (read(fd, buf, 2) != 2)
		return 0;
	*sp = buf[0] | (buf[1] << 8);
	return 1;
}

rt_inline int readlong(int fd, rt_uint32_t *lp)
{
	unsigned char buf[4];

	if (read(fd, buf, 4) != 4)
		return 0;
	*lp = buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
	return 1;
}

rt_inline int readstr(int fd, char *buf, int count)
{
	return read(fd, buf, count);
}

struct rtgui_font *fnt_font_create(const char* filename, const char* font_family)
{
	int fd = -1;
	rt_uint32_t index;
	struct rtgui_font *font = RT_NULL;
	struct fnt_font *fnt = RT_NULL;
	struct fnt_header *fnt_header;

	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
	{
		goto __exit;
	}

	font = (struct rtgui_font*) rtgui_malloc (sizeof(struct rtgui_font));
	if (font == RT_NULL) goto __exit;
	fnt = (struct fnt_font*) rtgui_malloc (sizeof(struct fnt_font));
	if (fnt == RT_NULL) goto __exit;
	rt_memset(fnt, 0x00, sizeof(struct fnt_font));
	font->data = (void*)fnt;

	fnt_header = &(fnt->header);
	if (readstr(fd, fnt_header->version, 4) != 4) goto __exit;
	if (!readshort(fd, &fnt_header->max_width)) goto __exit;
	if (!readshort(fd, &fnt_header->height)) goto __exit;
	if (!readshort(fd, &fnt_header->ascent)) goto __exit;
	if (!readshort(fd, &fnt_header->depth)) goto __exit;

	if (!readlong(fd, &fnt_header->first_char)) goto __exit;
	if (!readlong(fd, &fnt_header->default_char)) goto __exit;
	if (!readlong(fd, &fnt_header->size)) goto __exit;
	if (!readlong(fd, &fnt_header->nbits)) goto __exit;
	if (!readlong(fd, &fnt_header->noffset)) goto __exit;
	if (!readlong(fd, &fnt_header->nwidth)) goto __exit;

	fnt->bits = (MWIMAGEBITS*) rtgui_malloc (fnt_header->nbits * sizeof(MWIMAGEBITS));
	if (fnt->bits == RT_NULL) goto __exit;
	/* read data */
	if (readstr(fd, &(fnt->bits[0]), fnt_header->nbits) != fnt_header->nbits) goto __exit;

	/* check boundary */
	if (fnt_header->nbits & 0x01)
	{
		rt_uint16_t pad;
		readshort(fd, &pad);
		pad = pad; /* skip warning */
	}
	
	if (fnt_header->noffset != 0)
	{
		fnt->offset = rtgui_malloc (fnt_header->noffset * sizeof(rt_uint32_t));
		if (fnt->offset == RT_NULL) goto __exit;

		for (index = 0; index < fnt_header->noffset; index ++)
		{
			if (!readshort(fd, &(fnt->offset[index]))) goto __exit;
		}
	}

	if (fnt_header->nwidth != 0)
	{
		fnt->width = rtgui_malloc (fnt_header->nwidth * sizeof(rt_uint8_t));
		if (fnt->width == RT_NULL) goto __exit;

		for (index = 0; index < fnt_header->nwidth; index ++)
		{
			if (!readbyte(fd, &(fnt->width[index]))) goto __exit;
		}
	}

	close(fd);

	font->family = rt_strdup(font_family);
	font->height = fnt->header.height;
	font->refer_count = 0;
	font->engine = &fnt_font_engine;
	
	/* add to system */
	rtgui_font_system_add_font(font);

	return font;

__exit:
	if (fd >= 0) close(fd);
	if (fnt != RT_NULL)
	{
		if (fnt->bits != RT_NULL) rtgui_free(fnt->bits);
		if (fnt->offset != RT_NULL) rtgui_free(fnt->offset);
		if (fnt->width != RT_NULL) rtgui_free(fnt->width);

		rtgui_free(fnt);
	}

	if (font != RT_NULL)
	{
		rtgui_free(font);
	}
	return RT_NULL;
}
#endif

