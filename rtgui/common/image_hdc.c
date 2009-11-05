#include "libpng/png.h"
#include <rtthread.h>
#include <rtgui/image_hdc.h>
#include <rtgui/rtgui_system.h>

#define HDC_MAGIC_LEN       4

struct rtgui_image_hdc
{
	rt_bool_t is_loaded;

	struct rtgui_filerw* filerw;

	/* hdc image information */
    rt_uint32_t width, height;
    rt_uint32_t pitch;

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

	/* move to the begining of file */
	rtgui_filerw_seek(file, 0, SEEK_SET);

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
	rtgui_filerw_seek(file, start, SEEK_SET);

	return(is_HDC);
}

static rt_bool_t rtgui_image_hdc_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load)
{
    rt_uint32_t header[5];
    struct rtgui_image_hdc* hdc;

    hdc = (struct rtgui_image_hdc*) rtgui_malloc(sizeof(struct rtgui_image_hdc));
    if (hdc == RT_NULL) return RT_FALSE;

    rtgui_filerw_read(file, (char*)&header, 1, sizeof(header));

	/* set image information */
	image->w = header[1]; image->h = header[2];
	image->engine = &rtgui_image_hdc_engine;
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

		rtgui_image_hdc_process(png->png_ptr, png->info_ptr, png);
	}
	else
	{
		png->pixels = RT_NULL;
	}

	return RT_TRUE;
}

static void rtgui_image_hdc_unload(struct rtgui_image* image)
{
	struct rtgui_image_hdc* png;

	if (image != RT_NULL)
	{
		png = (struct rtgui_image_hdc*) image->data;

		png_read_end(png->png_ptr, RT_NULL);

		/* destroy png struct */
		png_destroy_info_struct(png->png_ptr, &png->info_ptr);
		png_destroy_read_struct(&png->png_ptr, RT_NULL, RT_NULL);

		if (png->pixels != RT_NULL) rtgui_free(png->pixels);

		/* release data */
		rtgui_free(png);
	}
}

static void rtgui_image_hdc_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect)
{
	rt_uint16_t x, y, w, h;
	rtgui_color_t* ptr;
	rtgui_color_t foreground;
	struct rtgui_image_hdc* png;

	RT_ASSERT(image != RT_NULL && dc != RT_NULL && rect != RT_NULL);
	RT_ASSERT(image->data != RT_NULL);

	png = (struct rtgui_image_hdc*) image->data;

    if (image->w < rtgui_rect_width(*rect)) w = image->w;
    else w = rtgui_rect_width(*rect);
    if (image->h < rtgui_rect_height(*rect)) h = image->h;
    else h = rtgui_rect_height(*rect);

	/* save foreground color */
	foreground = rtgui_dc_get_color(dc);

    if (png->pixels != RT_NULL)
    {
        ptr = (rtgui_color_t*)png->pixels;
        /* draw each point within dc */
        for (y = 0; y < h; y ++)
        {
            for (x = 0; x < w; x++)
            {
                /* not alpha */
                if ((*ptr >> 24) != 255)
                {
                    rtgui_dc_set_color(dc, *ptr);
                    rtgui_dc_draw_point(dc, x + rect->x1, y + rect->y1);
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
                        rtgui_dc_set_color(dc, RTGUI_ARGB((255 - data[3]), data[0], data[1], data[2]));
                        rtgui_dc_draw_point(dc, x + rect->x1, y + rect->y1);
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

                    rtgui_dc_set_color(dc, RTGUI_ARGB(0, png->info_ptr->palette[data[0]].red,
                        png->info_ptr->palette[data[0]].green,
                        png->info_ptr->palette[data[0]].blue));
                    rtgui_dc_draw_point(dc, x + rect->x1, y + rect->y1);
                }
            }

        default:
            break;
        };

        rtgui_free(row);
    }

	/* restore foreground */
	rtgui_dc_set_color(dc, foreground);
}

void rtgui_image_hdc_init()
{
	/* register png on image system */
	rtgui_image_register_engine(&rtgui_image_hdc_engine);
}
