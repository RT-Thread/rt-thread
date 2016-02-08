#include <rtthread.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/blit.h>
#include <rtgui/driver.h>

#ifdef RTGUI_IMAGE_PNG
#include "png.h"
#include <rtgui/image_png.h>

#define PNG_MAGIC_LEN       8

struct rtgui_image_png
{
    rt_bool_t is_loaded;

    struct rtgui_filerw *filerw;

    /* png image information */
    png_structp png_ptr;
    png_infop info_ptr;

    rt_uint8_t *pixels;
};

static rt_bool_t rtgui_image_png_check(struct rtgui_filerw *file);
static rt_bool_t rtgui_image_png_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load);
static void rtgui_image_png_unload(struct rtgui_image *image);
static void rtgui_image_png_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect);

struct rtgui_image_engine rtgui_image_png_engine =
{
    "png",
    { RT_NULL },
    rtgui_image_png_check,
    rtgui_image_png_load,
    rtgui_image_png_unload,
    rtgui_image_png_blit,
};

static void rtgui_image_png_read_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
    struct rtgui_filerw *filerw = (struct rtgui_filerw *)png_ptr->io_ptr;

    rtgui_filerw_read(filerw, data, length, 1);
}

static rt_bool_t rtgui_image_png_process(png_structp png_ptr, png_infop info_ptr, struct rtgui_image_png *png)
{
    rt_uint32_t x, y;
    png_bytep row;
    png_bytep data;
    rtgui_color_t *ptr;

    row = (png_bytep) rtgui_malloc(png_get_rowbytes(png_ptr, info_ptr));
    if (row == RT_NULL) return RT_FALSE;

    ptr = (rtgui_color_t *)png->pixels;

    switch (info_ptr->color_type)
    {
    case PNG_COLOR_TYPE_RGB:
        for (y = 0; y < info_ptr->height; y++)
        {
            png_read_row(png_ptr, row, png_bytep_NULL);
            for (x = 0; x < info_ptr->width; x++)
            {
                data = &(row[x * 3]);

                ptr[x + y * info_ptr->width] = RTGUI_RGB(data[0], data[1], data[2]);
            }
        }
        break;

    case PNG_COLOR_TYPE_RGBA:
        for (y = 0; y < info_ptr->height; y++)
        {
            png_read_row(png_ptr, row, png_bytep_NULL);
            for (x = 0; x < info_ptr->width; x++)
            {
                data = &(row[x * 4]);

                ptr[x + y * info_ptr->width] = RTGUI_ARGB(data[3], data[0], data[1], data[2]);
            }
        }

        break;

    case PNG_COLOR_TYPE_PALETTE:
        for (y = 0; y < info_ptr->height; y++)
        {
            png_read_row(png_ptr, row, png_bytep_NULL);
            for (x = 0; x < info_ptr->width; x++)
            {
                data = &(row[x]);

                ptr[x] = RTGUI_ARGB(0, info_ptr->palette[data[0]].red,
                                    info_ptr->palette[data[0]].green,
                                    info_ptr->palette[data[0]].blue);
            }
        }

    default:
        break;
    };

    rtgui_free(row);

    return RT_TRUE;
}

static rt_bool_t rtgui_image_png_check(struct rtgui_filerw *file)
{
    int start;
    rt_bool_t is_PNG;
    rt_uint8_t magic[4];

    if (!file) return 0;

    start = rtgui_filerw_tell(file);

    /* move to the begining of file */
    rtgui_filerw_seek(file, 0, SEEK_SET);

    is_PNG = RT_FALSE;
    if (rtgui_filerw_read(file, magic, 1, sizeof(magic)) == sizeof(magic))
    {
        if (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G')
        {
            is_PNG = RT_TRUE;
        }
    }
    rtgui_filerw_seek(file, start, SEEK_SET);

    return(is_PNG);
}

static void _image_png_error_fn(png_structp png_ptr, png_const_charp error_message)
{
	rt_kprintf(error_message);
}

static rt_bool_t rtgui_image_png_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load)
{
    png_uint_32 width;
    png_uint_32 height;
    int bit_depth;
    int color_type;
    double gamma;
    struct rtgui_image_png *png;

    png = (struct rtgui_image_png *) rtgui_malloc(sizeof(struct rtgui_image_png));
    png->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png->png_ptr == RT_NULL)
    {
        rtgui_free(png);
        return RT_FALSE;
    }
	png_set_error_fn(png->png_ptr, RT_NULL, _image_png_error_fn, _image_png_error_fn);
	
    png->info_ptr = png_create_info_struct(png->png_ptr);
    if (png->info_ptr == RT_NULL)
    {
        png_destroy_read_struct(&png->png_ptr, NULL, NULL);
        rtgui_free(png);
        return RT_FALSE;
    }

    png->filerw = file;
	png->is_loaded = RT_FALSE;
    png_set_read_fn(png->png_ptr, png->filerw, rtgui_image_png_read_data);

    png_read_info(png->png_ptr, png->info_ptr);
    png_get_IHDR(png->png_ptr, png->info_ptr, &width, &height, &bit_depth,
                 &color_type, NULL, NULL, NULL);

    /* set image information */
    image->w = width;
    image->h = height;
    image->engine = &rtgui_image_png_engine;
    image->data = png;

    if (bit_depth == 16)
        png_set_strip_16(png->png_ptr);
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_expand(png->png_ptr);
    if (bit_depth < 8)
        png_set_expand(png->png_ptr);
    if (png_get_valid(png->png_ptr, png->info_ptr, PNG_INFO_tRNS))
        png_set_expand(png->png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY ||
            color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png->png_ptr);

    /* Ignore background color */

    /* set gamma conversion */
    if (png_get_gAMA(png->png_ptr, png->info_ptr, &gamma))
        png_set_gamma(png->png_ptr, (double)2.2, gamma);

    png_read_update_info(png->png_ptr, png->info_ptr);

    if (load == RT_TRUE)
    {
        /* load all pixels */
        png->pixels = rtgui_malloc(image->w * image->h * sizeof(rtgui_color_t));
        if (png->pixels == RT_NULL)
        {
            png_read_end(png->png_ptr, RT_NULL);

            /* destroy png struct */
            png_destroy_info_struct(png->png_ptr, &png->info_ptr);
            png_destroy_read_struct(&png->png_ptr, RT_NULL, RT_NULL);

            /* release data */
            rtgui_free(png);
            return RT_FALSE;
        }

        rtgui_image_png_process(png->png_ptr, png->info_ptr, png);
		png_read_end(png->png_ptr, RT_NULL);
		png->is_loaded = RT_TRUE;
		/* close file handler */
		rtgui_filerw_close(png->filerw);
		png->filerw = RT_NULL;
    }
    else
    {
        png->pixels = RT_NULL;
    }

    return RT_TRUE;
}

static void rtgui_image_png_unload(struct rtgui_image *image)
{
    struct rtgui_image_png *png;

    if (image != RT_NULL)
    {
        png = (struct rtgui_image_png *) image->data;

        /* destroy png struct */
        png_destroy_info_struct(png->png_ptr, &png->info_ptr);
        png_destroy_read_struct(&png->png_ptr, RT_NULL, RT_NULL);

        if (png->pixels != RT_NULL) rtgui_free(png->pixels);

        /* release data */
        rtgui_free(png);
    }
}

static void rtgui_image_png_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect)
{
    rt_uint16_t x, y, w, h;
    rtgui_color_t *ptr;
    struct rtgui_image_png *png;
    int fg_maxsample;
    int ialpha;
    float alpha;
    rtgui_color_t color;
    rtgui_color_t c, bgcolor;
    int fc[3], bc[3];
    struct rtgui_graphic_driver *hwdev = rtgui_graphic_get_device();

    RT_ASSERT(image != RT_NULL && dc != RT_NULL && rect != RT_NULL);
    RT_ASSERT(image->data != RT_NULL);

    png = (struct rtgui_image_png *) image->data;

	w = _UI_MIN(image->w, rtgui_rect_width(*rect));
	h = _UI_MIN(image->h, rtgui_rect_height(*rect));

    fg_maxsample = (1 << png->info_ptr->bit_depth) - 1;

    if (png->pixels != RT_NULL)
    {
        ptr = (rtgui_color_t *)png->pixels;
        bgcolor = RTGUI_DC_BC(dc);
        bc[0] = RTGUI_RGB_R(bgcolor);
        bc[1] = RTGUI_RGB_G(bgcolor);
        bc[2] = RTGUI_RGB_B(bgcolor);

        /* draw each point within dc */
        for (y = 0; y < h; y ++)
        {
            for (x = 0; x < w; x++)
            {
                c = *ptr;
                ialpha = RTGUI_RGB_A(c);
                if (ialpha == 0)
                {
                    /*
                     * Foreground image is transparent hear.
                     * If the background image is already in the frame
                     * buffer, there is nothing to do.
                     */
                }
                else if (ialpha == fg_maxsample)
                {
                    /*
                     * Copy foreground pixel to frame buffer.
                     */
                    rtgui_dc_draw_color_point(dc, x + rect->x1, y + rect->y1, c);
                }
                else
                {
                    /* output = alpha * foreground + (1-alpha) * background */
                    /*
                     * Compositing is necessary.
                     * Get floating-point alpha and its complement.
                     * Note: alpha is always linear: gamma does not
                     * affect it.
                     */
                    fc[0] = RTGUI_RGB_R(c);
                    fc[1] = RTGUI_RGB_G(c);
                    fc[2] = RTGUI_RGB_B(c);

                    alpha = (float) ialpha / fg_maxsample;
                    color = RTGUI_RGB((rt_uint8_t)(fc[0] * alpha + bc[0] * (1 - alpha)),
                                      (rt_uint8_t)(fc[1] * alpha + bc[1] * (1 - alpha)),
                                      (rt_uint8_t)(fc[2] * alpha + bc[2] * (1 - alpha)));
                    rtgui_dc_draw_color_point(dc, x + rect->x1, y + rect->y1, color);
                }
                /* move to next color buffer */
                ptr ++;
            }
        }
    }
    else
    {
        png_bytep row;
        png_bytep data;

        row = (png_bytep) rtgui_malloc(png_get_rowbytes(png->png_ptr, png->info_ptr));
        if (row == RT_NULL) return ;

        switch (png->info_ptr->color_type)
        {
		case PNG_COLOR_TYPE_RGB:
			for (y = 0; y < h; y++)
			{
				png_read_row(png->png_ptr, row, png_bytep_NULL);
				for (x = 0; x < w; x++)
				{
					data = &(row[x * 3]);
					rtgui_dc_draw_color_point(dc, x + rect->x1, y + rect->y1,
											  RTGUI_RGB(data[0], data[1], data[2]));
				}
			}
			break;
			
        case PNG_COLOR_TYPE_RGBA:
            for (y = 0; y < h; y++)
            {
                png_read_row(png->png_ptr, row, png_bytep_NULL);
                for (x = 0; x < w; x++)
                {
                    data = &(row[x * 4]);
                    if (data[3] != 0)
                    {
                        rtgui_dc_draw_color_point(dc, x + rect->x1, y + rect->y1,
                                                  RTGUI_ARGB(data[3], data[0], data[1], data[2]));
                    }
                }
            }

            break;

        case PNG_COLOR_TYPE_PALETTE:
            for (y = 0; y < h; y++)
            {
                png_read_row(png->png_ptr, row, png_bytep_NULL);
                for (x = 0; x < w; x++)
                {
                    data = &(row[x]);

                    rtgui_dc_draw_color_point(dc, x + rect->x1, y + rect->y1,
                                              RTGUI_ARGB(0, png->info_ptr->palette[data[0]].red,
                                                         png->info_ptr->palette[data[0]].green,
                                                         png->info_ptr->palette[data[0]].blue));
                }
            }

        default:
            break;
        };

        rtgui_free(row);
    }
}

void rtgui_image_png_init()
{
    /* register png on image system */
    rtgui_image_register_engine(&rtgui_image_png_engine);
}

#elif defined(RTGUI_IMAGE_LODEPNG)
#include "lodepng.h"
#include <rtgui/image_png.h>

static rt_bool_t rtgui_image_png_check(struct rtgui_filerw *file);
static rt_bool_t rtgui_image_png_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load);
static void rtgui_image_png_unload(struct rtgui_image *image);
static void rtgui_image_png_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect);

struct rtgui_image_engine rtgui_image_png_engine =
{
    "png",
    { RT_NULL },
    rtgui_image_png_check,
    rtgui_image_png_load,
    rtgui_image_png_unload,
    rtgui_image_png_blit,
};

static rt_bool_t rtgui_image_png_check(struct rtgui_filerw *file)
{
    int start;
    rt_bool_t is_PNG;
    rt_uint8_t magic[4];

    if (!file) return 0;

    start = rtgui_filerw_tell(file);

    /* move to the begining of file */
    rtgui_filerw_seek(file, 0, SEEK_SET);

    is_PNG = RT_FALSE;
    if (rtgui_filerw_read(file, magic, 1, sizeof(magic)) == sizeof(magic))
    {
        if (magic[0] == 0x89 &&
                magic[1] == 'P' &&
                magic[2] == 'N' &&
                magic[3] == 'G')
        {
            is_PNG = RT_TRUE;
        }
    }
    rtgui_filerw_seek(file, start, SEEK_SET);

    return(is_PNG);
}

static rt_bool_t rtgui_image_png_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load)
{
    unsigned int width;
    unsigned int height;
    unsigned int error;
	
    rt_uint8_t* pixel;
    rt_uint8_t* in;
    rt_uint32_t in_size;

    RT_ASSERT(image != RT_NULL);
    RT_ASSERT(file != RT_NULL);

    rtgui_filerw_seek(file, 0, SEEK_END);
    in_size = rtgui_filerw_tell(file);
    in = rtgui_malloc(in_size);
    if (in == RT_NULL) return RT_FALSE; /* out of memory */

    rtgui_filerw_seek(file, 0, SEEK_SET);
    rtgui_filerw_read(file, in, in_size, 1);

    error = lodepng_decode32(&pixel, &width, &height, in, in_size);    
    if(error) 
	{
		rt_kprintf("error %u: %s\n", error, lodepng_error_text(error));
		rtgui_free(in);
		return RT_FALSE;
	}

    rtgui_free(in);

    /* set image information */
    image->w = width;
    image->h = height;
    image->engine = &rtgui_image_png_engine;
    image->data = pixel;

	/* NOTE: the pixel format of PNG is ABGR888, bit0 R,G,B,A bit31 */
	/* convert pixel to ARGB888, swap B/G */
	{
		rt_uint8_t* pixel_ptr;
		rt_uint8_t* pixel_end;

		pixel_ptr = (rt_uint8_t*) pixel;
		pixel_end = pixel_ptr + width * height * 4;

		while (pixel_ptr < pixel_end)
		{
			pixel_ptr[0] = pixel_ptr[0] ^ pixel_ptr[2];
			pixel_ptr[2] = pixel_ptr[0] ^ pixel_ptr[2];
			pixel_ptr[0] = pixel_ptr[0] ^ pixel_ptr[2];

			pixel_ptr += 4;
		}
	}

    /* close file handler */
    rtgui_filerw_close(file);

    return RT_TRUE;
}

static void rtgui_image_png_unload(struct rtgui_image *image)
{
    rt_uint8_t *pixels;

    if (image != RT_NULL)
    {
        pixels = (rt_uint8_t*) image->data;

        /* release data */
        rtgui_free(pixels);
    }
}

static void rtgui_image_png_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect)
{
	int x, y;
    int w, h;
	struct rtgui_blit_info info;
	struct rtgui_graphic_driver *hw_driver = rtgui_graphic_driver_get_default();

    RT_ASSERT(image != RT_NULL && dc != RT_NULL && rect != RT_NULL);
    RT_ASSERT(image->data != RT_NULL);

#define blending(s, d, a) (((unsigned)(((s) - (d)) * (a)) >> 8) + (d))

	/* this dc is not visible */
	if (rtgui_dc_get_visible(dc) != RT_TRUE) return;

	w = _UI_MIN(image->w, rtgui_rect_width(*rect));
	h = _UI_MIN(image->h, rtgui_rect_height(*rect));

	/* border checking */
	if (rect->x1 < 0) { x = -rect->x1; w += rect->x1; }
	else x = 0;

	if (rect->y1 < 0) { y = -rect->y1; h += rect->y1; }
	else y = 0;

	if (w < 0 || h < 0) return; /* no drawing */

	if ((dc->type == RTGUI_DC_CLIENT) || (dc->type == RTGUI_DC_HW && hw_driver->framebuffer == RT_NULL))
	{
		int dx, dy, start_x;
		rtgui_rect_t r;
		rtgui_color_t *pixel;
		rt_uint8_t alpha;
		rtgui_widget_t *owner = RT_NULL;

		if (dc->type == RTGUI_DC_CLIENT)
		{
			/* get owner and calculate dx,dy */
			owner = RTGUI_CONTAINER_OF(dc, struct rtgui_widget, dc_type);
			dx = owner->extent.x1; dy = owner->extent.y1;
		}
		else
		{
			/* hardware DC */
			struct rtgui_dc_hw *hw = (struct rtgui_dc_hw *) dc;
			dx = hw->owner->extent.x1;
			dy = hw->owner->extent.y1;
		}

		start_x = x;
		for (; y < rect->y1 + h; ++y)
		{
			for (x = start_x; x < rect->x1 + w; ++x)
			{
				pixel = (rtgui_color_t*)((rt_uint8_t*)image->data + (y - rect->y1) * image->w * 4 + 
					(x - rect->x1) * 4);

				alpha = RTGUI_RGB_A(*pixel);
				if (alpha == 0) continue;
				if (alpha == 0xff)
				{
					rtgui_dc_draw_color_point(dc, x, y, *pixel);
				}
				else 
				{
					rtgui_color_t bc, fc;

					/* draw an alpha blending point */
					if (hw_driver->framebuffer != RT_NULL)
						rtgui_dc_blend_point(dc, x, y, RTGUI_BLENDMODE_BLEND,
							RTGUI_RGB_R(*pixel), RTGUI_RGB_G(*pixel), RTGUI_RGB_B(*pixel), RTGUI_RGB_A(*pixel));
					else
					{
						x = x + dx;
						y = y + dy;

						if (dc->type == RTGUI_DC_CLIENT)
						{
							if (rtgui_region_contains_point(&(owner->clip), x, y, &r) != RT_EOK)
								continue ;
						}

						/* get background pixel */
						hw_driver->ops->get_pixel(&bc, x, y);
						/* alpha blending */
						fc = RTGUI_RGB(blending(RTGUI_RGB_R(bc), RTGUI_RGB_R(*pixel),  alpha), 
								blending(RTGUI_RGB_G(bc), RTGUI_RGB_G(*pixel),  alpha), 
								blending(RTGUI_RGB_B(bc), RTGUI_RGB_B(*pixel),  alpha));
						hw_driver->ops->set_pixel(&fc, x, y);
					}
				}
			}
		}
	}
	else
	{
		int dst_x, dst_y;
		
		info.a = 0;

		/* initialize source blit information */
		info.src_fmt = RTGRAPHIC_PIXEL_FORMAT_ARGB888;;
		info.src_h = h;
		info.src_w = w;
		info.src_pitch = image->w * rtgui_color_get_bpp(RTGRAPHIC_PIXEL_FORMAT_ARGB888);
		info.src_skip = info.src_pitch - w * rtgui_color_get_bpp(RTGRAPHIC_PIXEL_FORMAT_ARGB888);
		info.src = (rt_uint8_t *)image->data + y * info.src_pitch + x * rtgui_color_get_bpp(RTGRAPHIC_PIXEL_FORMAT_ARGB888);

		if (rect->x1 < 0) dst_x = 0;
		else dst_x = rect->x1;
		if (rect->y1 < 0) dst_y = 0;
		else dst_y = rect->y1;
		
		/* initialize destination blit information */
		if (dc->type == RTGUI_DC_BUFFER)
		{
			struct rtgui_dc_buffer *buffer;
			buffer = (struct rtgui_dc_buffer*)dc;

			info.dst = rtgui_dc_buffer_get_pixel(RTGUI_DC(buffer)) + dst_y * buffer->pitch + 
				dst_x * rtgui_color_get_bpp(buffer->pixel_format);
			info.dst_h = h;
			info.dst_w = w;
			info.dst_fmt = buffer->pixel_format;
			info.dst_pitch = buffer->pitch;
			info.dst_skip = info.dst_pitch - info.dst_w * rtgui_color_get_bpp(buffer->pixel_format);
		}
		else if (dc->type == RTGUI_DC_HW)
		{
			struct rtgui_widget *owner;
			struct rtgui_rect r;

			owner = ((struct rtgui_dc_hw*)dc)->owner;

			rtgui_graphic_driver_get_rect(RT_NULL, &r);
			
			/* blit destination */
			info.dst = (rt_uint8_t*)hw_driver->framebuffer;
			info.dst = info.dst + (owner->extent.y1 + dst_y) * hw_driver->pitch +
				(owner->extent.x1 + dst_x) * rtgui_color_get_bpp(hw_driver->pixel_format);
			info.dst_fmt = hw_driver->pixel_format;
			info.dst_h = h;
			info.dst_w = w;
			info.dst_pitch = hw_driver->pitch;
			info.dst_skip = info.dst_pitch - info.dst_w * rtgui_color_get_bpp(hw_driver->pixel_format);			
		}

		rtgui_blit(&info);
	}
}

void rtgui_image_png_init()
{
    /* register png on image system */
    rtgui_image_register_engine(&rtgui_image_png_engine);
}
#endif
