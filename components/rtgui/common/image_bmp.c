#include <rtthread.h>
#include <rtgui/dc_hw.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/image_bmp.h>
#include <rtgui/blit.h>

#ifdef RTGUI_IMAGE_BMP
/* Compression encodings for BMP files */
#ifndef BI_RGB
#define BI_RGB			0
#define BI_RLE8			1
#define BI_RLE4			2
#define BI_BITFIELDS	3
#endif

#define hw_driver				(rtgui_graphic_driver_get_default())

struct rtgui_image_bmp
{
	rt_bool_t is_loaded;

	rt_uint32_t Rmask;
	rt_uint32_t Gmask;
	rt_uint32_t Bmask;

	rt_size_t   pixel_offset;

	rt_uint8_t  byte_per_pixel;
	rt_uint8_t  pad;
	rt_uint8_t  ExpandBMP;

	rt_uint8_t *pixels;
	rt_uint8_t *line_pixels;
	rt_uint32_t pitch;

	struct rtgui_filerw* filerw;
};

struct rtgui_image_bmp_header
{
	/* The Win32 BMP file header (14 bytes) */
	char   magic[2];
	rt_uint32_t bfSize;
	rt_uint16_t bfReserved1;
	rt_uint16_t bfReserved2;
	rt_uint32_t bfOffBits;

	/* The Win32 BITMAPINFOHEADER struct (40 bytes) */
	rt_uint32_t biSize;
	rt_int32_t  biWidth;
	rt_int32_t  biHeight;
	rt_uint16_t biPlanes;
	rt_uint16_t biBitCount;
	rt_uint32_t biCompression;
	rt_uint32_t biSizeImage;
	rt_int32_t  biXPelsPerMeter;
	rt_int32_t  biYPelsPerMeter;
	rt_uint32_t biClrUsed;
	rt_uint32_t biClrImportant;
};

static rt_bool_t rtgui_image_bmp_check(struct rtgui_filerw* file);
static rt_bool_t rtgui_image_bmp_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load);
static void rtgui_image_bmp_unload(struct rtgui_image* image);
static void rtgui_image_bmp_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect);

struct rtgui_image_engine rtgui_image_bmp_engine =
{
	"bmp",
	{ RT_NULL },
	rtgui_image_bmp_check,
	rtgui_image_bmp_load,
	rtgui_image_bmp_unload,
	rtgui_image_bmp_blit
};

rt_inline rt_uint32_t rtgui_filerw_read32(struct rtgui_filerw* src)
{
	rt_uint32_t value;
	rtgui_filerw_read(src, &value, (sizeof value), 1);
	return value;
}

rt_inline rt_uint16_t rtgui_filerw_read16(struct rtgui_filerw* src)
{
	rt_uint16_t value;
	rtgui_filerw_read(src, &value, (sizeof value), 1);
	return value;

}

static rt_bool_t rtgui_image_bmp_check(struct rtgui_filerw* file)
{
	char magic[2];
	rt_bool_t is_bmp;
	rt_off_t start;

	if ( !file ) return 0;

	start = rtgui_filerw_tell(file);

	/* move to the beginning of file */
	rtgui_filerw_seek(file, 0, RTGUI_FILE_SEEK_SET);

	is_bmp = RT_FALSE;
	if ( rtgui_filerw_read(file, magic, 1, sizeof(magic)) == sizeof(magic) )
	{
		if (magic[0] == 'B' &&
				magic[1] == 'M')
		{
			is_bmp = RT_TRUE;
		}
	}

	rtgui_filerw_seek(file, start, RTGUI_FILE_SEEK_SET);

	return(is_bmp);
}

static struct rtgui_image_palette* rtgui_image_bmp_load_palette(struct rtgui_image_bmp_header* header, struct rtgui_filerw* src)
{
	/* Load the palette, if any */
	rt_size_t i;
	struct rtgui_image_palette* palette;

	if (header->biClrUsed == 0)
		header->biClrUsed = 1 << header->biBitCount;

	palette = rtgui_image_palette_create(header->biClrUsed);
	if (palette == RT_NULL) return RT_NULL;

	if ( header->biSize == 12 )
	{
		rt_uint8_t r, g, b;
		for ( i = 0; i < (int)header->biClrUsed; ++i )
		{
			rtgui_filerw_read(src, &b, 1, 1);
			rtgui_filerw_read(src, &g, 1, 1);
			rtgui_filerw_read(src, &r, 1, 1);
			palette->colors[i] = RTGUI_RGB(r, g, b);
		}
	}
	else
	{
		rt_uint8_t r, g, b, a;
		for ( i = 0; i < (int)header->biClrUsed; ++i )
		{
			rtgui_filerw_read(src, &b, 1, 1);
			rtgui_filerw_read(src, &g, 1, 1);
			rtgui_filerw_read(src, &r, 1, 1);
			rtgui_filerw_read(src, &a, 1, 1);
			palette->colors[i] = RTGUI_ARGB(a, r, g, b);
		}
	}

	return palette;
}

static rt_bool_t rtgui_image_bmp_load(struct rtgui_image* image, struct rtgui_filerw* src, rt_bool_t load)
{
	rt_uint32_t Rmask;
	rt_uint32_t Gmask;
	rt_uint32_t Bmask;
	int ExpandBMP, bmpPitch;
	struct rtgui_image_bmp* bmp;
	struct rtgui_image_bmp_header* header;
	struct rtgui_image_palette* palette;

	bmp = RT_NULL;
	header = RT_NULL;
	palette = RT_NULL;
	header = (struct rtgui_image_bmp_header*) rtgui_malloc(sizeof(struct rtgui_image_bmp_header));
	if (header == RT_NULL) return RT_FALSE;

	if ( rtgui_filerw_read(src, header->magic, 1, sizeof(header->magic)) ==
		sizeof(sizeof(header->magic)) )
	{
		if (header->magic[0] != 'B' ||
			header->magic[1] != 'M')
		{
			goto __exit;
		}
	}

	header->bfSize		= rtgui_filerw_read32(src);
	header->bfReserved1	= rtgui_filerw_read16(src);
	header->bfReserved2	= rtgui_filerw_read16(src);
	header->bfOffBits	= rtgui_filerw_read32(src);

	/* Read the Win32 BITMAPINFOHEADER */
	header->biSize		= rtgui_filerw_read32(src);
	if ( header->biSize == 12 )
	{
		header->biWidth		= (rt_uint32_t)rtgui_filerw_read16(src);
		header->biHeight	= (rt_uint32_t)rtgui_filerw_read16(src);
		header->biPlanes	= rtgui_filerw_read16(src);
		header->biBitCount	= rtgui_filerw_read16(src);
		header->biCompression	= BI_RGB;
		header->biSizeImage	= 0;
		header->biXPelsPerMeter	= 0;
		header->biYPelsPerMeter	= 0;
		header->biClrUsed	= 0;

		header->biClrImportant	= 0;

	}
	else
	{
		header->biWidth		= rtgui_filerw_read32(src);
		header->biHeight	= rtgui_filerw_read32(src);
		header->biPlanes	= rtgui_filerw_read16(src);
		header->biBitCount	= rtgui_filerw_read16(src);
		header->biCompression	= rtgui_filerw_read32(src);
		header->biSizeImage	= rtgui_filerw_read32(src);
		header->biXPelsPerMeter	= rtgui_filerw_read32(src);
		header->biYPelsPerMeter	= rtgui_filerw_read32(src);
		header->biClrUsed	= rtgui_filerw_read32(src);
		header->biClrImportant	= rtgui_filerw_read32(src);

	}

	/* allocate palette and expand 1 and 4 bit bitmaps to 8 bits per pixel */
	switch (header->biBitCount)
	{
	case 1:
		ExpandBMP = header->biBitCount;
		palette = rtgui_image_bmp_load_palette(header, src);
		header->biBitCount = 8;
		break;

	case 4:
		ExpandBMP = header->biBitCount;
		palette = rtgui_image_bmp_load_palette(header, src);
		header->biBitCount = 8;
		break;

	case 8:
		palette = rtgui_image_bmp_load_palette(header, src);
		ExpandBMP = 0;
		break;

	default:
		ExpandBMP = 0;
		break;
	}

	/* We don't support any BMP compression right now */
	Rmask = Gmask = Bmask = 0;
	switch (header->biCompression)
	{
	case BI_RGB:
		/* If there are no masks, use the defaults */
		if ( header->bfOffBits == (14 + header->biSize) )
		{
			/* Default values for the BMP format */
			switch (header->biBitCount)
			{
			case 15:
			case 16:
				Rmask = 0x7C00;
				Gmask = 0x03E0;
				Bmask = 0x001F;
				break;

			case 24:
			case 32:
				Rmask = 0x00FF0000;
				Gmask = 0x0000FF00;
				Bmask = 0x000000FF;
				break;

			default:
				break;
			}
			break;
		}
		/* Fall through -- read the RGB masks */

	case BI_BITFIELDS:
		switch (header->biBitCount)
		{
		case 15:
		case 16:
		case 32:
			Rmask = rtgui_filerw_read32(src);
			Gmask = rtgui_filerw_read32(src);
			Bmask = rtgui_filerw_read32(src);
			break;

		default:
			break;
		}
		break;

	default:
		rt_kprintf("Compressed BMP files not supported\n");
		goto __exit;
	}

	bmp = (struct rtgui_image_bmp*) rtgui_malloc(sizeof(struct rtgui_image_bmp));
	if (bmp == RT_NULL)
		goto __exit;

	/* set image information */
	image->w = header->biWidth;
	image->h = header->biHeight;
	image->engine = &rtgui_image_bmp_engine;
	image->data = bmp;
	bmp->filerw = src;
	bmp->byte_per_pixel = header->biBitCount/8;
	bmp->pitch = image->w * bmp->byte_per_pixel;
	bmp->pixel_offset = header->bfOffBits;
	bmp->Rmask = Rmask; bmp->Gmask = Gmask; bmp->Bmask = Bmask;
	bmp->ExpandBMP = ExpandBMP;
	if (palette != RT_NULL) image->palette = palette;

	/* get padding */
	switch (ExpandBMP)
	{
	case 1:
		bmpPitch = (header->biWidth + 7) >> 3;
		bmp->pad  = (((bmpPitch)%4) ? (4-((bmpPitch)%4)) : 0);
		break;

	case 4:
		bmpPitch = (header->biWidth + 1) >> 1;
		bmp->pad  = (((bmpPitch)%4) ? (4-((bmpPitch)%4)) : 0);
		break;

	default:
		bmp->pad  = ((bmp->pitch%4) ? (4-(bmp->pitch%4)) : 0);
		break;
	}

	if (load == RT_TRUE)
	{
		rt_uint8_t *bits;
		rt_uint32_t i;

		/* load all pixels */
		bmp->pixels = rtgui_malloc(image->h * bmp->pitch);
		if (bmp->pixels == RT_NULL)
			goto __exit;

		/* Read the pixels.  Note that the bmp image is upside down */
		if ( rtgui_filerw_seek(src, bmp->pixel_offset, RTGUI_FILE_SEEK_SET) < 0)
			goto __exit;

		bits = bmp->pixels + image->h * bmp->pitch;
		while ( bits > bmp->pixels )
		{
			bits -= bmp->pitch;
			switch (ExpandBMP)
			{
			case 1:
			case 4:
				{
					rt_uint8_t pixel = 0;
					int   shift = (8 - ExpandBMP);
					for ( i=0; i < image->w; ++i )
					{
						if ( i % (8/ExpandBMP) == 0 )
						{
							if ( !rtgui_filerw_read(src, &pixel, 1, 1) )
								goto __exit;

						}
						*(bits+i) = (pixel>>shift);
						pixel <<= ExpandBMP;
					}
				}
				break;

			default:
				if ( rtgui_filerw_read(src, bits, 1, bmp->pitch) != bmp->pitch ) goto __exit;
				break;
			}

			/* Skip padding bytes  */
			if ( bmp->pad )
			{
				rt_uint8_t padbyte;
				for ( i=0; i < bmp->pad; ++i )
				{
					rtgui_filerw_read(src, &padbyte, 1, 1);
				}
			}
		}

		rtgui_filerw_close(bmp->filerw);
		bmp->line_pixels = RT_NULL;
		bmp->filerw = RT_NULL;
		bmp->pixel_offset = 0;
	}
	else
	{
		bmp->pixels = RT_NULL;
		bmp->line_pixels = rtgui_malloc(bmp->pitch);
	}

	return RT_TRUE;

__exit:
	rtgui_free(header);
	if (palette != RT_NULL)
	{
		rtgui_free(palette);
		image->palette = RT_NULL;
	}

	if (bmp != RT_NULL)
		rtgui_free(bmp->pixels);
	rtgui_free(bmp);
	return RT_FALSE;
}

static void rtgui_image_bmp_unload(struct rtgui_image* image)
{
	struct rtgui_image_bmp* bmp;

	if (image != RT_NULL)
	{
		bmp = (struct rtgui_image_bmp*) image->data;

		if (bmp->pixels != RT_NULL) rtgui_free(bmp->pixels);
		if (bmp->line_pixels != RT_NULL) rtgui_free(bmp->line_pixels);
		if (bmp->filerw != RT_NULL)
		{
			rtgui_filerw_close(bmp->filerw);
			bmp->filerw = RT_NULL;
		}

		/* release data */
		rtgui_free(bmp);
	}
}

static void rtgui_image_bmp_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* dst_rect)
{
	int y;
	rt_uint16_t w, h;
	struct rtgui_image_bmp* bmp;

	RT_ASSERT(image != RT_NULL || dc != RT_NULL || dst_rect != RT_NULL);

	/* this dc is not visible */
	if (rtgui_dc_get_visible(dc) != RT_TRUE) return;

	bmp = (struct rtgui_image_bmp*) image->data;
	RT_ASSERT(bmp != RT_NULL);

	/* the minimum rect */
	if (image->w < rtgui_rect_width(*dst_rect)) w = image->w;
	else w = rtgui_rect_width(*dst_rect);
	if (image->h < rtgui_rect_height(*dst_rect)) h = image->h;
	else h = rtgui_rect_height(*dst_rect);

	if (bmp->pixels != RT_NULL)
	{
		rt_uint8_t* ptr;

		/* get pixel pointer */
		ptr = bmp->pixels;
		if (bmp->byte_per_pixel == hw_driver->bits_per_pixel/8)
		{
			for (y = 0; y < h; y ++)
			{
				dc->engine->blit_line(dc, 
					dst_rect->x1, dst_rect->x1 + w,
					dst_rect->y1 + y, 
					ptr);
				ptr += bmp->pitch;
			}
		}
		else
		{
			rt_size_t pitch;
			rt_uint8_t *line_ptr;

			if (image->palette == RT_NULL)
			{
				rtgui_blit_line_func blit_line;
				line_ptr = (rt_uint8_t*) rtgui_malloc((hw_driver->bits_per_pixel/8) * w);
				blit_line = rtgui_blit_line_get(hw_driver->bits_per_pixel/8 , bmp->byte_per_pixel);
				pitch = w * bmp->byte_per_pixel;
				if (line_ptr != RT_NULL)
				{
					for (y = 0; y < h; y ++)
					{
						blit_line(line_ptr, ptr, pitch);
						dc->engine->blit_line(dc,
							dst_rect->x1, dst_rect->x1 + w,
							dst_rect->y1 + y, 
							line_ptr);
						ptr += bmp->pitch;
					}
				}
				rtgui_free(line_ptr);
			}
			else
			{
				int x;
				rtgui_color_t color;

				/* use palette */
				for (y = 0; y < h; y ++)
				{
					ptr = bmp->pixels + (y * bmp->pitch);
					for (x = 0; x < w; x ++)
					{
						color = image->palette->colors[*ptr]; ptr ++;
						rtgui_dc_draw_color_point(dc, dst_rect->x1 + x, dst_rect->y1 + y, color);
					}
				}
			}
		}
	}
	else
	{
		int offset;
		rt_uint8_t *bits;

		/* calculate offset */
		switch (bmp->ExpandBMP)
		{
		case 1:
			offset = (image->h - h) * (image->w/8) * bmp->byte_per_pixel;
			break;

		case 4:
			offset = (image->h - h) * (image->w/2) * bmp->byte_per_pixel;
			break;

		default:
			offset = (image->h - h) * image->w * bmp->byte_per_pixel;
			break;
		}
		/* seek to the begin of pixel data */
		rtgui_filerw_seek(bmp->filerw, bmp->pixel_offset + offset, RTGUI_FILE_SEEK_SET);

		if (bmp->ExpandBMP == 1 || bmp->ExpandBMP == 4)
		{
			int x;
			rtgui_color_t color;
			/* 1, 4 bit per pixels */

			/* draw each line */
			for (y = h - 1; y >= 0; y --)
			{
				/* read pixel data */
				rt_uint8_t pixel = 0;
				int   shift = (8 - bmp->ExpandBMP);
				int i;

				bits = bmp->line_pixels;
				for ( i=0; i < image->w; ++i )
				{
					if ( i % (8/bmp->ExpandBMP) == 0 )
					{
						if ( !rtgui_filerw_read(bmp->filerw, &pixel, 1, 1) )
							return;
					}
					*(bits+i) = (pixel>>shift);
					pixel <<= bmp->ExpandBMP;
				}

				/* Skip padding bytes  */
				if (bmp->pad)
				{
					int i;
					rt_uint8_t padbyte;
					for ( i=0; i < bmp->pad; ++i )
						rtgui_filerw_read(bmp->filerw, &padbyte, 1, 1);
				}

				/* use palette */
				bits = bmp->line_pixels;
				for (x = 0; x < w; x ++)
				{
					color = image->palette->colors[*bits]; bits ++;
					rtgui_dc_draw_color_point(dc, dst_rect->x1 + x, dst_rect->y1 + y, color);
				}
			}
		}
		else
		{
			rt_uint8_t *line_ptr = (rt_uint8_t*) rtgui_malloc((hw_driver->bits_per_pixel/8) * w);
			if (line_ptr == RT_NULL) return;

			/* draw each line */
			for (y = h - 1; y >= 0; y --)
			{
				/* read line pixels */
				rtgui_filerw_read(bmp->filerw, bmp->line_pixels, 1, bmp->pitch);

				/* Skip padding bytes  */
				if (bmp->pad)
				{
					int i;
					rt_uint8_t padbyte;
					for ( i=0; i < bmp->pad; ++i )
						rtgui_filerw_read(bmp->filerw, &padbyte, 1, 1);
				}

				if (image->palette == RT_NULL)
				{
					int pitch;
					rtgui_blit_line_func blit_line;
					blit_line = rtgui_blit_line_get(hw_driver->bits_per_pixel/8 , bmp->byte_per_pixel);
					pitch = w * bmp->byte_per_pixel;
					if (line_ptr != RT_NULL)
					{
						blit_line(line_ptr, bmp->line_pixels, pitch);
						dc->engine->blit_line(dc,
							dst_rect->x1, dst_rect->x1 + w,
							dst_rect->y1 + y, 
							line_ptr);
					}
				}
				else 
				{
					int x;
					rtgui_color_t color;

					/* use palette */
					bits = bmp->line_pixels;
					for (x = 0; x < w; x ++)
					{
						color = image->palette->colors[*bits]; bits ++;
						rtgui_dc_draw_color_point(dc, dst_rect->x1 + x, dst_rect->y1 + y, color);
					}
				}
			}
			if (line_ptr != RT_NULL) rtgui_free(line_ptr);
		}
	}
}

void rtgui_image_bmp_init()
{
	/* register bmp on image system */
	rtgui_image_register_engine(&rtgui_image_bmp_engine);
}
#endif
