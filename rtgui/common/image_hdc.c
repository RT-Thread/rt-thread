#include <rtthread.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#define HDC_MAGIC_LEN       4

struct rtgui_image_hdc
{
	rt_bool_t is_loaded;

	struct rtgui_filerw* filerw;
	struct rtgui_graphic_driver* hw_driver;

	/* hdc image information */
	rt_uint16_t byte_per_pixel;
    rt_uint16_t pitch;

	rt_size_t   pixel_offset;
	rt_uint8_t *pixels;
};

static rt_bool_t rtgui_image_hdc_check(struct rtgui_filerw* file);
static rt_bool_t rtgui_image_hdc_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load);
static void rtgui_image_hdc_unload(struct rtgui_image* image);
static void rtgui_image_hdc_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect);

struct rtgui_image_engine rtgui_image_hdc_engine =
{
	"hdc",
	{ RT_NULL },
	rtgui_image_hdc_check,
	rtgui_image_hdc_load,
	rtgui_image_hdc_unload,
	rtgui_image_hdc_blit
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
	image->w = header[1]; image->h = header[2];
	image->engine = &rtgui_image_hdc_engine;
	image->data = hdc;
	hdc->filerw = file;
	hdc->byte_per_pixel = hdc->hw_driver->byte_per_pixel;
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

static void rtgui_image_hdc_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect)
{
	rt_uint16_t y, w, h;
	rtgui_color_t foreground;
	struct rtgui_image_hdc* hdc;
	rt_uint16_t rect_pitch, hw_pitch;
	rtgui_rect_t dc_rect;

	RT_ASSERT(image != RT_NULL && dc != RT_NULL && rect != RT_NULL);

	/* this dc is not visible */
	if (dc->get_visible(dc) != RT_TRUE) return;

	hdc = (struct rtgui_image_hdc*) image->data;
	RT_ASSERT(hdc != RT_NULL);

	/* transfer logic coordinate to physical coordinate */
	if (dc->type == RTGUI_DC_HW)
	{
		struct rtgui_dc_hw *hw_dc = (struct rtgui_dc_hw*)dc;
		dc_rect = hw_dc->owner->extent;
	}
	else rtgui_dc_get_rect(dc, &dc_rect);
	rtgui_rect_moveto(rect, dc_rect.x1, dc_rect.y1);

	/* the minimum rect */
    if (image->w < rtgui_rect_width(*rect)) w = image->w;
    else w = rtgui_rect_width(*rect);
    if (image->h < rtgui_rect_height(*rect)) h = image->h;
    else h = rtgui_rect_height(*rect);

	/* get rect pitch */
	rect_pitch = w * hdc->byte_per_pixel;
	hw_pitch = hdc->hw_driver->width * hdc->hw_driver->byte_per_pixel;

	/* save foreground color */
	foreground = rtgui_dc_get_color(dc);

    if (hdc->pixels != RT_NULL)
    {
		if (hdc->hw_driver->get_framebuffer() != RT_NULL)
		{
			rt_uint8_t* rect_ptr;
			rt_uint8_t* hw_ptr;

			/* get pixel pointer */
			hw_ptr = hdc->hw_driver->get_framebuffer();
			rect_ptr = hdc->pixels;

			/* move hardware pixel pointer */
			hw_ptr += rect->y1 * hdc->pitch + rect->x1 * hdc->byte_per_pixel;

			for (y = 0; y < h; y ++)
			{
				rt_memcpy(hw_ptr, rect_ptr, rect_pitch);
				hw_ptr += hw_pitch;
				rect_ptr += rect_pitch;
			}
		}
		else
		{
			rt_uint8_t* rect_ptr;

			/* get pixel pointer */
			rect_ptr = hdc->pixels;

			for (y = 0; y < h; y ++)
			{
				hdc->hw_driver->draw_raw_hline(rect_ptr, rect->x1,  rect->x2, rect->y1 + y);
				rect_ptr += rect_pitch;
			}
		}
    }
    else
    {
		rt_uint8_t* rect_ptr;
		rect_ptr = rtgui_malloc(rect_pitch);
		if (rect_ptr == RT_NULL) return; /* no memory */

		/* seek to the begin of pixel data */
		rtgui_filerw_seek(hdc->filerw, hdc->pixel_offset, RTGUI_FILE_SEEK_SET);

		if (hdc->hw_driver->get_framebuffer() != RT_NULL)
		{
			rt_uint8_t* hw_ptr;

			/* get pixel pointer */
			hw_ptr = hdc->hw_driver->get_framebuffer();
			/* move hardware pixel pointer */
			hw_ptr += rect->y1 * hdc->pitch + rect->x1 * hdc->byte_per_pixel;

			for (y = 0; y < h; y ++)
			{
				/* read pixel data */
				if (rtgui_filerw_read(hdc->filerw, rect_ptr, 1, rect_pitch) != rect_pitch)
					break; /* read data failed */

				rt_memcpy(hw_ptr, rect_ptr, rect_pitch);
				hw_ptr += hw_pitch;
			}
		}
		else
		{
			for (y = 0; y < h; y ++)
			{
				/* read pixel data */
				if (rtgui_filerw_read(hdc->filerw, rect_ptr, 1, rect_pitch) != rect_pitch)
					break; /* read data failed */

				hdc->hw_driver->draw_raw_hline(rect_ptr, rect->x1,  rect->x2, rect->y1 + y);
			}
		}

		rtgui_free(rect_ptr);
    }

	/* restore foreground */
	rtgui_dc_set_color(dc, foreground);
}

void rtgui_image_hdc_init()
{
	/* register hdc on image system */
	rtgui_image_register_engine(&rtgui_image_hdc_engine);
}
