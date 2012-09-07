#include <rtthread.h>
#include <rtgui/rtgui_system.h>

#ifdef RTGUI_IMAGE_PNG
#include "png.h"
#include <rtgui/image_png.h>

#define PNG_MAGIC_LEN       8

struct rtgui_image_png
{
	rt_bool_t is_loaded;

	struct rtgui_filerw* filerw;

	/* png image information */
	png_structp png_ptr;
	png_infop info_ptr;

	rt_uint8_t *pixels;
};

static rt_bool_t rtgui_image_png_check(struct rtgui_filerw* file);
static rt_bool_t rtgui_image_png_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load);
static void rtgui_image_png_unload(struct rtgui_image* image);
static void rtgui_image_png_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect);

struct rtgui_image_engine rtgui_image_png_engine =
{
	"png",
	{ RT_NULL },
	rtgui_image_png_check,
	rtgui_image_png_load,
	rtgui_image_png_unload,
	rtgui_image_png_blit,
	RT_NULL,
	RT_NULL
};

static void rtgui_image_png_read_data(png_structp png_ptr, png_bytep data, png_size_t length)
{
	struct rtgui_filerw* filerw = (struct rtgui_filerw*)png_ptr->io_ptr;

	rtgui_filerw_read(filerw, data, length, 1);
}

static rt_bool_t rtgui_image_png_process(png_structp png_ptr, png_infop info_ptr, struct rtgui_image_png* png)
{
    rt_uint32_t x, y;
    png_bytep row;
    png_bytep data;
    rtgui_color_t *ptr;

	row = (png_bytep) rtgui_malloc (png_get_rowbytes(png_ptr, info_ptr));
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

					ptr[x+y*info_ptr->width] = RTGUI_RGB(data[0], data[1], data[2]);
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

                    ptr[x+y*info_ptr->width] = RTGUI_ARGB((255 - data[3]), data[0], data[1], data[2]);
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

static rt_bool_t rtgui_image_png_check(struct rtgui_filerw* file)
{
	int start;
	rt_bool_t is_PNG;
	rt_uint8_t magic[4];

	if ( !file ) return 0;

	start = rtgui_filerw_tell(file);

	/* move to the begining of file */
	rtgui_filerw_seek(file, 0, SEEK_SET);

	is_PNG = RT_FALSE;
	if ( rtgui_filerw_read(file, magic, 1, sizeof(magic)) == sizeof(magic) )
	{
		if ( magic[0] == 0x89 &&
				magic[1] == 'P' &&
				magic[2] == 'N' &&
				magic[3] == 'G' )
		{
			is_PNG = RT_TRUE;
		}
	}
	rtgui_filerw_seek(file, start, SEEK_SET);

	return(is_PNG);
}

static rt_bool_t rtgui_image_png_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load)
{
	png_uint_32 width;
	png_uint_32 height;
	int bit_depth;
	int color_type;
	double gamma;
	struct rtgui_image_png* png;

	png = (struct rtgui_image_png*) rtgui_malloc(sizeof(struct rtgui_image_png));
	png->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png->png_ptr == RT_NULL)
	{
		rtgui_free(png);
		return RT_FALSE;
	}

	png->info_ptr = png_create_info_struct(png->png_ptr);
	if (png->info_ptr == RT_NULL)
	{
		png_destroy_read_struct(&png->png_ptr, NULL, NULL);
		rtgui_free(png);
		return RT_FALSE;
	}

	png->filerw = file;
	png_set_read_fn (png->png_ptr, png->filerw, rtgui_image_png_read_data);

	png_read_info(png->png_ptr, png->info_ptr);
	png_get_IHDR(png->png_ptr, png->info_ptr, &width, &height, &bit_depth,
		&color_type, NULL, NULL, NULL);

	/* set image information */
	image->w = width; image->h = height;
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
	}
	else
	{
		png->pixels = RT_NULL;
	}

	return RT_TRUE;
}

static void rtgui_image_png_unload(struct rtgui_image* image)
{
	struct rtgui_image_png* png;

	if (image != RT_NULL)
	{
		png = (struct rtgui_image_png*) image->data;

		png_read_end(png->png_ptr, RT_NULL);

		/* destroy png struct */
		png_destroy_info_struct(png->png_ptr, &png->info_ptr);
		png_destroy_read_struct(&png->png_ptr, RT_NULL, RT_NULL);

		if (png->pixels != RT_NULL) rtgui_free(png->pixels);

		/* release data */
		rtgui_free(png);
	}
}

static void rtgui_image_png_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect)
{
	struct rtgui_graphic_driver* hwdev = rtgui_graphic_get_device();
	rt_uint16_t x, y, w, h;
	rtgui_color_t* ptr;
	struct rtgui_image_png* png;
	int fg_maxsample;
	int ialpha;
	float alpha;
	rtgui_color_t color;
	rtgui_color_t c, bgcolor;
	int fc[3], bc[3];

	RT_ASSERT(image != RT_NULL && dc != RT_NULL && rect != RT_NULL);
	RT_ASSERT(image->data != RT_NULL);

	png = (struct rtgui_image_png*) image->data;

    if (image->w < rtgui_rect_width(*rect)) w = image->w;
    else w = rtgui_rect_width(*rect);
    if (image->h < rtgui_rect_height(*rect)) h = image->h;
    else h = rtgui_rect_height(*rect);
	
	fg_maxsample = (1 << png->info_ptr->bit_depth) - 1;

    if (png->pixels != RT_NULL)
    {
        ptr = (rtgui_color_t*)png->pixels;
        bgcolor = rtgui_color_from_565(RTGUI_DC_BC(dc));
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
				if(ialpha == 0)
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
				{	/* output = alpha * foreground + (1-alpha) * background	*/
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
					color = RTGUI_RGB( (rt_uint8_t)(fc[0]*alpha + bc[0]*(1-alpha)), 
									   (rt_uint8_t)(fc[1]*alpha + bc[1]*(1-alpha)),
									   (rt_uint8_t)(fc[2]*alpha + bc[2]*(1-alpha)));
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

        row = (png_bytep) rtgui_malloc (png_get_rowbytes(png->png_ptr, png->info_ptr));
        if (row == RT_NULL) return ;

        switch (png->info_ptr->color_type)
        {
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
							RTGUI_ARGB((255 - data[3]), data[0], data[1], data[2]));
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
#endif
