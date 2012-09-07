#include <rtthread.h>
#include <rtgui/dc_hw.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/image_hdc.h>

#define HDC_MAGIC_LEN       4

struct rtgui_image_hdc
{
	rt_bool_t is_loaded;

	/* hdc image information */
	rt_uint16_t byte_per_pixel;
    rt_uint16_t pitch;

	rt_size_t   pixel_offset;
	rt_uint8_t *pixels;

	struct rtgui_filerw* filerw;
	const struct rtgui_graphic_driver* hw_driver;
};

static rt_bool_t rtgui_image_hdc_check(struct rtgui_filerw* file);
static rt_bool_t rtgui_image_hdc_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load);
static void rtgui_image_hdc_unload(struct rtgui_image* image);
static void rtgui_image_hdc_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect);
static void rtgui_image_hdcmm_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* dst_rect);

struct rtgui_image_engine rtgui_image_hdc_engine =
{
	"hdc",
	{ RT_NULL },
	rtgui_image_hdc_check,
	rtgui_image_hdc_load,
	rtgui_image_hdc_unload,
	rtgui_image_hdc_blit,
	RT_NULL,
	RT_NULL
};

const struct rtgui_image_engine rtgui_image_hdcmm_engine =
{
	"hdcmm",
	{RT_NULL},
	RT_NULL,
	RT_NULL,
	RT_NULL,
	rtgui_image_hdcmm_blit,
	RT_NULL,
	RT_NULL
};

static rt_bool_t rtgui_image_hdc_check(struct rtgui_filerw* file)
{
	int start;
	rt_bool_t is_HDC;
	rt_uint8_t magic[4];

	if ( !file ) return 0;

	start = rtgui_filerw_tell(file);

	/* move to the beginning of file */
	rtgui_filerw_seek(file, 0, RTGUI_FILE_SEEK_SET);

	is_HDC = RT_FALSE;
	if ( rtgui_filerw_read(file, magic, 1, sizeof(magic)) == sizeof(magic) )
	{
		if ( magic[0] == 'H' &&
				magic[1] == 'D' &&
				magic[2] == 'C' &&
				magic[3] == '\0' )
		{
			is_HDC = RT_TRUE;
		}
	}
	rtgui_filerw_seek(file, start, RTGUI_FILE_SEEK_SET);

	return(is_HDC);
}

static rt_bool_t rtgui_image_hdc_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load)
{
    rt_uint32_t header[5];
    struct rtgui_image_hdc* hdc;

    hdc = (struct rtgui_image_hdc*) rtgui_malloc(sizeof(struct rtgui_image_hdc));
    if (hdc == RT_NULL) return RT_FALSE;

	hdc->hw_driver = rtgui_graphic_driver_get_default();
	if (hdc->hw_driver == RT_NULL) { rtgui_free(hdc); return RT_FALSE; }

    rtgui_filerw_read(file, (char*)&header, 1, sizeof(header));

	/* set image information */
	image->w = (rt_uint16_t)header[1]; image->h = (rt_uint16_t)header[2];
	image->engine = &rtgui_image_hdc_engine;
	image->data = hdc;
	hdc->filerw = file;
	hdc->byte_per_pixel = hdc->hw_driver->bits_per_pixel/8;
	hdc->pitch = image->w * hdc->byte_per_pixel;
	hdc->pixel_offset = rtgui_filerw_tell(file);

	if (load == RT_TRUE)
	{
		/* load all pixels */
		hdc->pixels = rtgui_malloc(image->h * hdc->pitch);
		if (hdc->pixels == RT_NULL)
		{
            /* release data */
            rtgui_free(hdc);
            return RT_FALSE;
		}

		rtgui_filerw_read(hdc->filerw, hdc->pixels, 1, image->h * hdc->pitch);
		rtgui_filerw_close(hdc->filerw);
		hdc->filerw = RT_NULL;
		hdc->pixel_offset = 0;
	}
	else
	{
		hdc->pixels = RT_NULL;
	}

	return RT_TRUE;
}

static void rtgui_image_hdc_unload(struct rtgui_image* image)
{
	struct rtgui_image_hdc* hdc;

	if (image != RT_NULL)
	{
		hdc = (struct rtgui_image_hdc*) image->data;

		if (hdc->pixels != RT_NULL) rtgui_free(hdc->pixels);
		if (hdc->filerw != RT_NULL)
		{
			rtgui_filerw_close(hdc->filerw);
			hdc->filerw = RT_NULL;
		}

		/* release data */
		rtgui_free(hdc);
	}
}

static void rtgui_image_hdc_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* dst_rect)
{
	rt_uint16_t y, w, h;
	struct rtgui_image_hdc* hdc;

	RT_ASSERT(image != RT_NULL || dc != RT_NULL || dst_rect != RT_NULL);

	/* this dc is not visible */
	if (rtgui_dc_get_visible(dc) != RT_TRUE) return;

	hdc = (struct rtgui_image_hdc*) image->data;
	RT_ASSERT(hdc != RT_NULL);

	/* the minimum rect */
    if (image->w < rtgui_rect_width(*dst_rect)) w = image->w;
    else w = rtgui_rect_width(*dst_rect);
    if (image->h < rtgui_rect_height(*dst_rect)) h = image->h;
    else h = rtgui_rect_height(*dst_rect);

    if (hdc->pixels != RT_NULL)
    {
		rt_uint8_t* ptr;

		/* get pixel pointer */
		ptr = hdc->pixels;

		for (y = 0; y < h; y ++)
		{
			dc->engine->blit_line(dc, dst_rect->x1, dst_rect->x1 + w, dst_rect->y1 + y, ptr);
			ptr += hdc->pitch;
		}
    }
    else
    {
		rt_uint8_t* ptr;
		ptr = rtgui_malloc(hdc->pitch);
		if (ptr == RT_NULL) return; /* no memory */

		/* seek to the begin of pixel data */
		rtgui_filerw_seek(hdc->filerw, hdc->pixel_offset, RTGUI_FILE_SEEK_SET);

		for (y = 0; y < h; y ++)
		{
			/* read pixel data */
			if (rtgui_filerw_read(hdc->filerw, ptr, 1, hdc->pitch) != hdc->pitch)
				break; /* read data failed */

			dc->engine->blit_line(dc, dst_rect->x1,  dst_rect->x1 + w, dst_rect->y1 + y, ptr);
		}

		rtgui_free(ptr);
    }
}

static void rtgui_image_hdcmm_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* dst_rect)
{
	rt_uint8_t* ptr;
	rt_uint16_t y, w, h;
	struct rtgui_image_hdcmm* hdc;

	RT_ASSERT(image != RT_NULL || dc != RT_NULL || dst_rect != RT_NULL);

	/* this dc is not visible */
	if (rtgui_dc_get_visible(dc) != RT_TRUE) return;

	hdc = (struct rtgui_image_hdcmm*) image;
	RT_ASSERT(hdc != RT_NULL);

	/* the minimum rect */
    if (image->w < rtgui_rect_width(*dst_rect)) w = image->w;
    else w = rtgui_rect_width(*dst_rect);
    if (image->h < rtgui_rect_height(*dst_rect)) h = image->h;
    else h = rtgui_rect_height(*dst_rect);


	/* get pixel pointer */
	ptr = hdc->pixels;

	for (y = 0; y < h; y ++)
	{
		dc->engine->blit_line(dc, dst_rect->x1, dst_rect->x1 + w, dst_rect->y1 + y, ptr);
		ptr += hdc->pitch;
	}
}

void rtgui_image_hdc_init()
{
	/* register hdc on image system */
	rtgui_image_register_engine(&rtgui_image_hdc_engine);
}
