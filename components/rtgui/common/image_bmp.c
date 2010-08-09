#include <rtthread.h>
#include <rtgui/dc_hw.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/image_bmp.h>

/* Compression encodings for BMP files */
#ifndef BI_RGB
#define BI_RGB			0
#define BI_RLE8			1
#define BI_RLE4			2
#define BI_BITFIELDS	3
#endif

struct rtgui_image_bmp
{
	rt_bool_t is_loaded;

	rt_size_t   pixel_offset;
	rt_uint8_t *pixels;

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

static rt_bool_t rtgui_image_bmp_check(struct rtgui_filerw* file)
{
	char magic[2];
	rt_bool_t is_bmp;

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

static rt_bool_t rtgui_image_bmp_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load)
{
    struct rtgui_image_bmp* bmp;

    bmp = (struct rtgui_image_bmp*) rtgui_malloc(sizeof(struct rtgui_image_bmp));
    if (bmp == RT_NULL) return RT_FALSE;

	bmp->hw_driver = rtgui_graphic_driver_get_default();
	if (bmp->hw_driver == RT_NULL) { rtgui_free(bmp); return RT_FALSE; }

    rtgui_filerw_read(file, (char*)&header, 1, sizeof(header));

	/* set image information */
	image->w = (rt_uint16_t)header[1]; image->h = (rt_uint16_t)header[2];
	image->engine = &rtgui_image_bmp_engine;
	image->data = bmp;
	bmp->filerw = file;
	bmp->byte_per_pixel = bmp->hw_driver->byte_per_pixel;
	bmp->pitch = image->w * bmp->byte_per_pixel;
	bmp->pixel_offset = rtgui_filerw_tell(file);

	if (load == RT_TRUE)
	{
		/* load all pixels */
		bmp->pixels = rtgui_malloc(image->h * bmp->pitch);
		if (bmp->pixels == RT_NULL)
		{
            /* release data */
            rtgui_free(bmp);
            return RT_FALSE;
		}

		rtgui_filerw_read(bmp->filerw, bmp->pixels, 1, image->h * bmp->pitch);
		rtgui_filerw_close(bmp->filerw);
		bmp->filerw = RT_NULL;
		bmp->pixel_offset = 0;
	}
	else
	{
		bmp->pixels = RT_NULL;
	}

	return RT_TRUE;
}

static void rtgui_image_bmp_unload(struct rtgui_image* image)
{
	struct rtgui_image_bmp* bmp;

	if (image != RT_NULL)
	{
		bmp = (struct rtgui_image_bmp*) image->data;

		if (bmp->pixels != RT_NULL) rtgui_free(bmp->pixels);
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
	rt_uint16_t y, w, h;
	struct rtgui_image_bmp* bmp;

	RT_ASSERT(image != RT_NULL || dc != RT_NULL || dst_rect != RT_NULL);

	/* this dc is not visible */
	if (rtgui_dc_get_visible(dc) != RT_TRUE) return;

	bmp = (struct rtgui_image_bmp*) image->data;
	RT_ASSERT(bmp != RT_NULL);

	if ((dc->type != RTGUI_DC_HW) || (dc->type != RTGUI_DC_CLIENT)) return;

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

		for (y = 0; y < h; y ++)
		{
			rtgui_dc_client_draw_raw_hline(dc, ptr, dst_rect->x1, dst_rect->x1 + w, dst_rect->y1 + y);
			ptr += bmp->pitch;
		}
    }
    else
    {
		rt_uint8_t* ptr;
		ptr = rtgui_malloc(bmp->pitch);
		if (ptr == RT_NULL) return; /* no memory */

		/* seek to the begin of pixel data */
		rtgui_filerw_seek(bmp->filerw, bmp->pixel_offset, RTGUI_FILE_SEEK_SET);

		for (y = 0; y < h; y ++)
		{
			/* read pixel data */
			if (rtgui_filerw_read(bmp->filerw, ptr, 1, bmp->pitch) != bmp->pitch)
				break; /* read data failed */

			rtgui_dc_client_draw_raw_hline(dc, ptr, dst_rect->x1,  dst_rect->x1 + w, dst_rect->y1 + y);
		}

		rtgui_free(ptr);
    }
}

void rtgui_image_bmp_init()
{
	/* register bmp on image system */
	rtgui_image_register_engine(&rtgui_image_bmp_engine);
}
