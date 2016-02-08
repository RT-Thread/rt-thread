/*
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-24     onelife      add TJpgDec (Tiny JPEG Decompressor) support
 */
#include <rtthread.h>
#include <rtgui/rtgui.h>

#ifdef RTGUI_IMAGE_JPEG
#include <stdio.h>
#include <stdlib.h>
#include "jpeglib.h"

#include <rtgui/rtgui_system.h>
#include <rtgui/filerw.h>
#include <rtgui/image_jpeg.h>
#include <rtgui/blit.h>

#ifdef RTGUI_USING_DFS_FILERW
#include <dfs_posix.h>
#endif

static rt_bool_t rtgui_image_jpeg_check(struct rtgui_filerw *file);
static rt_bool_t rtgui_image_jpeg_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load);
static void rtgui_image_jpeg_unload(struct rtgui_image *image);
static void rtgui_image_jpeg_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect);

struct rtgui_jpeg_error_mgr
{
    struct jpeg_error_mgr pub;  /* "public" fields */
};

struct rtgui_image_jpeg
{
    rt_bool_t is_loaded;

    struct rtgui_filerw *filerw;

    /* jpeg structure */
    struct jpeg_decompress_struct cinfo;
    struct rtgui_jpeg_error_mgr errmgr;

    rt_uint8_t *pixels;
    rt_uint8_t *line_pixels;
};

struct rtgui_image_engine rtgui_image_jpeg_engine =
{
    "jpeg",
    {RT_NULL},
    rtgui_image_jpeg_check,
    rtgui_image_jpeg_load,
    rtgui_image_jpeg_unload,
    rtgui_image_jpeg_blit
};

struct rtgui_image_engine rtgui_image_jpg_engine =
{
    "jpg",
    {RT_NULL},
    rtgui_image_jpeg_check,
    rtgui_image_jpeg_load,
    rtgui_image_jpeg_unload,
    rtgui_image_jpeg_blit
};

#define INPUT_BUFFER_SIZE   4096
typedef struct
{
    struct jpeg_source_mgr pub;

    struct rtgui_filerw *ctx;
    rt_uint8_t buffer[INPUT_BUFFER_SIZE];
} rtgui_jpeg_source_mgr;

/*
* Initialize source --- called by jpeg_read_header
* before any data is actually read.
*/
static void init_source(j_decompress_ptr cinfo)
{
    /* We don't actually need to do anything */
    return;
}

/*
* Fill the input buffer --- called whenever buffer is emptied.
*/
static boolean fill_input_buffer(j_decompress_ptr cinfo)
{
    rtgui_jpeg_source_mgr *src = (rtgui_jpeg_source_mgr *) cinfo->src;
    int nbytes;

    nbytes = rtgui_filerw_read(src->ctx, src->buffer, 1, INPUT_BUFFER_SIZE);
    if (nbytes <= 0)
    {
        /* Insert a fake EOI marker */
        src->buffer[0] = (rt_uint8_t) 0xFF;
        src->buffer[1] = (rt_uint8_t) JPEG_EOI;
        nbytes = 2;
    }

    src->pub.next_input_byte = src->buffer;
    src->pub.bytes_in_buffer = nbytes;

    return TRUE;
}


/*
* Skip data --- used to skip over a potentially large amount of
* uninteresting data (such as an APPn marker).
*
* Writers of suspendable-input applications must note that skip_input_data
* is not granted the right to give a suspension return.  If the skip extends
* beyond the data currently in the buffer, the buffer can be marked empty so
* that the next read will cause a fill_input_buffer call that can suspend.
* Arranging for additional bytes to be discarded before reloading the input
* buffer is the application writer's problem.
*/
static void skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
    rtgui_jpeg_source_mgr *src = (rtgui_jpeg_source_mgr *) cinfo->src;

    /* Just a dumb implementation for now.  Could use fseek() except
    * it doesn't work on pipes.  Not clear that being smart is worth
    * any trouble anyway --- large skips are infrequent.
    */
    if (num_bytes > 0)
    {
        while (num_bytes > (long) src->pub.bytes_in_buffer)
        {
            num_bytes -= (long) src->pub.bytes_in_buffer;
            (void) src->pub.fill_input_buffer(cinfo);
            /* note we assume that fill_input_buffer will never
            * return FALSE, so suspension need not be handled.
            */
        }
        src->pub.next_input_byte += (size_t) num_bytes;
        src->pub.bytes_in_buffer -= (size_t) num_bytes;
    }
}

/*
* Terminate source --- called by jpeg_finish_decompress
* after all data has been read.
*/
static void term_source(j_decompress_ptr cinfo)
{
    /* We don't actually need to do anything */
    return;
}

/*
* Prepare for input from a stdio stream.
* The caller must have already opened the stream, and is responsible
* for closing it after finishing decompression.
*/
static void rtgui_jpeg_filerw_src_init(j_decompress_ptr cinfo, struct rtgui_filerw *ctx)
{
    rtgui_jpeg_source_mgr *src;

    /* The source object and input buffer are made permanent so that a series
    * of JPEG images can be read from the same file by calling jpeg_stdio_src
    * only before the first one.  (If we discarded the buffer at the end of
    * one image, we'd likely lose the start of the next one.)
    * This makes it unsafe to use this manager and a different source
    * manager serially with the same JPEG object.  Caveat programmer.
    */
    if (cinfo->src == NULL)     /* first time for this JPEG object? */
    {
        cinfo->src = (struct jpeg_source_mgr *)
                     (*cinfo->mem->alloc_small)((j_common_ptr) cinfo, JPOOL_PERMANENT,
                                                sizeof(rtgui_jpeg_source_mgr));
        src = (rtgui_jpeg_source_mgr *) cinfo->src;
    }

    src = (rtgui_jpeg_source_mgr *) cinfo->src;
    src->pub.init_source = init_source;
    src->pub.fill_input_buffer = fill_input_buffer;
    src->pub.skip_input_data = skip_input_data;
    src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
    src->pub.term_source = term_source;
    src->ctx = ctx;
    src->pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
    src->pub.next_input_byte = NULL; /* until buffer loaded */
}

/* get line data of a jpeg image */
static rt_uint8_t *rtgui_image_get_line(struct rtgui_image *image, int h)
{
    struct rtgui_image_jpeg *jpeg;
    rt_uint8_t *result_ptr;

    JSAMPARRAY buffer;      /* Output row buffer */
    int row_stride;

    RT_ASSERT(image != RT_NULL);
    jpeg = (struct rtgui_image_jpeg *) image->data;
    RT_ASSERT(jpeg != RT_NULL);

    if (h < 0 || h > image->h) return RT_NULL;

    /* if the image is loaded, */
    if (jpeg->is_loaded == RT_TRUE)
    {
        result_ptr = jpeg->pixels + (image->w * sizeof(rtgui_color_t)) * h;

        return result_ptr;
    }

    if (jpeg->line_pixels == RT_NULL)
        jpeg->line_pixels = rtgui_malloc(image->w * sizeof(rtgui_color_t));

    row_stride = jpeg->cinfo.output_width * jpeg->cinfo.output_components;
    buffer = (*jpeg->cinfo.mem->alloc_sarray)
             ((j_common_ptr) &jpeg->cinfo, JPOOL_IMAGE, row_stride, 1);

    /* decompress line data */
    jpeg->cinfo.output_scanline = h;
    jpeg_read_scanlines(&jpeg->cinfo, buffer, (JDIMENSION) 1);

    /* copy pixels memory */
    {
        int index;
        rtgui_color_t *ptr;

        ptr = (rtgui_color_t *)jpeg->line_pixels;
        for (index = 0; index < image->w; index ++)
            ptr[index] = RTGUI_ARGB(0, buffer[0][index * 3], buffer[0][index * 3 + 1], buffer[0][index * 3 + 2]);
    }

    return jpeg->line_pixels;
}

static rt_bool_t rtgui_image_jpeg_loadall(struct rtgui_image *image)
{
    struct rtgui_image_jpeg *jpeg;
    rt_uint8_t *line_ptr;
    JSAMPARRAY buffer;      /* Output row buffer */
    int row_stride;

    jpeg = (struct rtgui_image_jpeg *) image->data;
    RT_ASSERT(jpeg != RT_NULL);

    /* already load */
    if (jpeg->pixels != RT_NULL) return RT_TRUE;

    /* allocate all pixels */
    jpeg->pixels = rtgui_malloc(image->h * image->w * sizeof(rtgui_color_t));
    if (jpeg->pixels == RT_NULL) return RT_FALSE;

    /* reset scan line to zero */
    jpeg->cinfo.output_scanline = 0;
    line_ptr = jpeg->pixels;

    row_stride = jpeg->cinfo.output_width * jpeg->cinfo.output_components;
    buffer = (*jpeg->cinfo.mem->alloc_sarray)
             ((j_common_ptr) &jpeg->cinfo, JPOOL_IMAGE, row_stride, 1);

    /* decompress all pixels */
    while (jpeg->cinfo.output_scanline < jpeg->cinfo.output_height)
    {
        /* jpeg_read_scanlines expects an array of pointers to scanlines.
        * Here the array is only one element long, but you could ask for
        * more than one scanline at a time if that's more convenient.
        */
        (void) jpeg_read_scanlines(&jpeg->cinfo, buffer, 1);

        /* copy pixels memory */
        {
            int index;
            rtgui_color_t *ptr;

            ptr = (rtgui_color_t *)line_ptr;
            for (index = 0; index < image->w; index ++)
                ptr[index] = RTGUI_ARGB(0, buffer[0][index * 3], buffer[0][index * 3 + 1], buffer[0][index * 3 + 2]);
        }

        /* move to next line */
        line_ptr += image->w * sizeof(rtgui_color_t);
    }

    /* decompress done */
    rtgui_filerw_close(jpeg->filerw);
    jpeg_finish_decompress(&jpeg->cinfo);

    jpeg->is_loaded = RT_TRUE;
    return RT_TRUE;
}

void rtgui_image_jpeg_init()
{
    /* register jpeg on image system */
    rtgui_image_register_engine(&rtgui_image_jpeg_engine);
    /* register jpg on image system */
    rtgui_image_register_engine(&rtgui_image_jpg_engine);
}

static void my_error_exit(j_common_ptr cinfo)
{
}

static void output_no_message(j_common_ptr cinfo)
{
    /* do nothing */
}

static rt_bool_t rtgui_image_jpeg_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load)
{
    struct rtgui_image_jpeg *jpeg;

    jpeg = (struct rtgui_image_jpeg *) rtgui_malloc(sizeof(struct rtgui_image_jpeg));
    if (jpeg == RT_NULL) return RT_FALSE;

    jpeg->filerw = file;

    /* read file header */
    /* Create a decompression structure and load the JPEG header */
    jpeg->cinfo.err = jpeg_std_error(&jpeg->errmgr.pub);
    jpeg->errmgr.pub.error_exit = my_error_exit;
    jpeg->errmgr.pub.output_message = output_no_message;

    jpeg_create_decompress(&jpeg->cinfo);
    rtgui_jpeg_filerw_src_init(&jpeg->cinfo, jpeg->filerw);
    (void)jpeg_read_header(&jpeg->cinfo, TRUE);

    image->w = jpeg->cinfo.image_width;
    image->h = jpeg->cinfo.image_height;

    /* set image private data and engine */
    image->data = jpeg;
    image->engine = &rtgui_image_jpeg_engine;

    /* start decompression */
    (void) jpeg_start_decompress(&jpeg->cinfo);

    jpeg->cinfo.out_color_space = JCS_RGB;
    jpeg->cinfo.quantize_colors = FALSE;
    /* use fast jpeg */
    jpeg->cinfo.scale_num   = 1;
    jpeg->cinfo.scale_denom = 1;
    jpeg->cinfo.dct_method = JDCT_FASTEST;
    jpeg->cinfo.do_fancy_upsampling = FALSE;

    jpeg->pixels = RT_NULL;
    jpeg->is_loaded = RT_FALSE;

    /* allocate line pixels */
    jpeg->line_pixels = rtgui_malloc(image->w * sizeof(rtgui_color_t));
    if (jpeg->line_pixels == RT_NULL)
    {
        /* no memory */
        jpeg_finish_decompress(&jpeg->cinfo);
        jpeg_destroy_decompress(&jpeg->cinfo);
        rt_free(jpeg);

        return RT_FALSE;
    }

    if (load == RT_TRUE) rtgui_image_jpeg_loadall(image);

    /* create jpeg image successful */
    return RT_TRUE;
}


static void rtgui_image_jpeg_unload(struct rtgui_image *image)
{
    if (image != RT_NULL)
    {
        struct rtgui_image_jpeg *jpeg;

        jpeg = (struct rtgui_image_jpeg *) image->data;
        RT_ASSERT(jpeg != RT_NULL);

        if (jpeg->is_loaded == RT_TRUE)
            rtgui_free(jpeg->pixels);
        if (jpeg->line_pixels != RT_NULL) rtgui_free(jpeg->line_pixels);

        if (jpeg->is_loaded != RT_TRUE)
        {
            rtgui_filerw_close(jpeg->filerw);
            jpeg_finish_decompress(&jpeg->cinfo);
        }
        jpeg_destroy_decompress(&jpeg->cinfo);
        rt_free(jpeg);
    }
}

static void rtgui_image_jpeg_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect)
{
    rt_uint16_t x, y;
    rtgui_color_t *ptr;
    struct rtgui_image_jpeg *jpeg;

    RT_ASSERT(image != RT_NULL && dc != RT_NULL && rect != RT_NULL);

    jpeg = (struct rtgui_image_jpeg *) image->data;
    RT_ASSERT(jpeg != RT_NULL);

    if (jpeg->pixels != RT_NULL)
    {
        ptr = (rtgui_color_t *) jpeg->pixels;

		if (dc->type == RTGUI_DC_BUFFER)
		{
			/* blit ARGB888 to this buffered DC */
			int dst_x, dst_y;
			int w, h;
			struct rtgui_blit_info info;
			struct rtgui_dc_buffer *buffer = (struct rtgui_dc_buffer*)dc;

			w = _UI_MIN(image->w, rtgui_rect_width(*rect));
			h = _UI_MIN(image->h, rtgui_rect_height(*rect));

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
			info.dst = rtgui_dc_buffer_get_pixel(RTGUI_DC(buffer)) + dst_y * buffer->pitch + 
				dst_x * rtgui_color_get_bpp(buffer->pixel_format);
			info.dst_h = h;
			info.dst_w = w;
			info.dst_fmt = buffer->pixel_format;
			info.dst_pitch = buffer->pitch;
			info.dst_skip = info.dst_pitch - info.dst_w * rtgui_color_get_bpp(buffer->pixel_format);

			rtgui_blit(&info);
		}
		else
		{
	        /* draw each point within dc */
	        for (y = 0; y < image->h; y ++)
	        {
	            for (x = 0; x < image->w; x++)
	            {
	                /* not alpha */
	                if ((*ptr >> 24) != 255)
	                {
	                    rtgui_dc_draw_color_point(dc, x + rect->x1, y + rect->y1, *ptr);
	                }

	                /* move to next color buffer */
	                ptr ++;
	            }
	        }
		}
    }
    else
    {
        /* seek to the begin of file */
        rtgui_filerw_seek(jpeg->filerw, 0, RTGUI_FILE_SEEK_SET);

        /* decompress line and line */
        for (y = 0; y < image->h; y ++)
        {
            ptr = (rtgui_color_t *)rtgui_image_get_line(image, y);
            for (x = 0; x < image->w; x++)
            {
                /* not alpha */
                if ((*ptr >> 24) != 255)
                {
                    rtgui_dc_draw_color_point(dc, x + rect->x1, y + rect->y1, *ptr);
                }

                /* move to next color buffer */
                ptr ++;
            }
        }
    }
}

static rt_bool_t rtgui_image_jpeg_check(struct rtgui_filerw *file)
{
    int start;
    rt_bool_t is_JPG;
    int in_scan;
    rt_uint8_t magic[4];

    if (file == RT_NULL) return RT_FALSE; /* open file failed */

    start = rtgui_filerw_tell(file);
    is_JPG = RT_FALSE;
    in_scan = 0;

    /* seek to the begining of file */
    rtgui_filerw_seek(file, 0, RTGUI_FILE_SEEK_SET);

    if (rtgui_filerw_read(file, magic, 2, 1))
    {
        if ((magic[0] == 0xFF) && (magic[1] == 0xD8))
        {
            is_JPG = RT_TRUE;
            while (is_JPG == RT_TRUE)
            {
                if (rtgui_filerw_read(file, magic, 1, 2) != 2)
                {
                    is_JPG = RT_FALSE;
                }
                else if ((magic[0] != 0xFF) && (in_scan == 0))
                {
                    is_JPG = RT_FALSE;
                }
                else if ((magic[0] != 0xFF) || (magic[1] == 0xFF))
                {
                    /* Extra padding in JPEG (legal) */
                    /* or this is data and we are scanning */
                    rtgui_filerw_seek(file, -1, RTGUI_FILE_SEEK_CUR);
                }
                else if (magic[1] == 0xD9)
                {
                    /* Got to end of good JPEG */
                    break;
                }
                else if ((in_scan == 1) && (magic[1] == 0x00))
                {
                    /* This is an encoded 0xFF within the data */
                }
                else if ((magic[1] >= 0xD0) && (magic[1] < 0xD9))
                {
                    /* These have nothing else */
                }
                else if (rtgui_filerw_read(file, magic + 2, 1, 2) != 2)
                {
                    is_JPG = RT_FALSE;
                }
                else
                {
                    /* Yes, it's big-endian */
                    rt_uint32_t start;
                    rt_uint32_t size;
                    rt_uint32_t end;
                    start = rtgui_filerw_tell(file);
                    size = (magic[2] << 8) + magic[3];
                    end = rtgui_filerw_seek(file, size - 2, RTGUI_FILE_SEEK_CUR);
                    if (end != start + size - 2) is_JPG = RT_FALSE;
                    if (magic[1] == 0xDA)
                    {
                        /* Now comes the actual JPEG meat */
                        /* It is a JPEG. */
                        break;
                    }
                }
            }
        }
    }
    rtgui_filerw_seek(file, start, RTGUI_FILE_SEEK_SET);

    return is_JPG;
}

#endif

#if defined(RTGUI_IMAGE_TJPGD)
/***************************************************************************//**
 * @file    image_jpg.c
 * @brief   JPEG decoder using TJpgDec module (elm-chan.org)
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 *  LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2012-01-24   onelife     Initial creation for limited memory devices
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup TJpgDec
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "tjpgd.h"

#include <rtgui/rtgui_system.h>
#include <rtgui/filerw.h>
#include <rtgui/blit.h>
#include <rtgui/image_jpeg.h>

#ifdef RTGUI_USING_DFS_FILERW
#include <dfs_posix.h>
#endif

/* Private typedef -----------------------------------------------------------*/
struct rtgui_image_jpeg
{
    struct rtgui_filerw *filerw;
    struct rtgui_dc *dc;
    rt_uint16_t dst_x, dst_y;
    rt_uint16_t dst_w, dst_h;
    rt_bool_t is_loaded;
	rt_uint8_t byte_per_pixel;

	JDEC tjpgd;                     /* jpeg structure */
    void *pool;
    rt_uint8_t *pixels;
};

/* Private define ------------------------------------------------------------*/
#define TJPGD_WORKING_BUFFER_SIZE   (32 * 1024)

/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static rt_bool_t rtgui_image_jpeg_check(struct rtgui_filerw *file);
static rt_bool_t rtgui_image_jpeg_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load);
static void rtgui_image_jpeg_unload(struct rtgui_image *image);
static void rtgui_image_jpeg_blit(struct rtgui_image *image,
                                  struct rtgui_dc *dc, struct rtgui_rect *dst_rect);

/* Private variables ---------------------------------------------------------*/
struct rtgui_image_engine rtgui_image_jpeg_engine =
{
    "jpeg",
    {RT_NULL},
    rtgui_image_jpeg_check,
    rtgui_image_jpeg_load,
    rtgui_image_jpeg_unload,
    rtgui_image_jpeg_blit
};

struct rtgui_image_engine rtgui_image_jpg_engine =
{
    "jpg",
    {RT_NULL},
    rtgui_image_jpeg_check,
    rtgui_image_jpeg_load,
    rtgui_image_jpeg_unload,
    rtgui_image_jpeg_blit
};

/* Private functions ---------------------------------------------------------*/
void rtgui_image_jpeg_init()
{
    /* register jpeg on image system */
    rtgui_image_register_engine(&rtgui_image_jpeg_engine);
    /* register jpg on image system */
    rtgui_image_register_engine(&rtgui_image_jpg_engine);
}

static UINT tjpgd_in_func(JDEC *jdec, BYTE *buff, UINT ndata)
{
    struct rtgui_filerw *file = *(struct rtgui_filerw **)jdec->device;

    if (buff == RT_NULL)
    {
        return rtgui_filerw_seek(file, ndata, RTGUI_FILE_SEEK_CUR);
    }

    return rtgui_filerw_read(file, (void *)buff, 1, ndata);
}

static UINT tjpgd_out_func(JDEC *jdec, void *bitmap, JRECT *rect)
{
    struct rtgui_image_jpeg *jpeg = (struct rtgui_image_jpeg *)jdec->device;
    rt_uint16_t w, h, y;
    rt_uint16_t rectWidth;               /* Width of source rectangular (bytes) */
    rt_uint8_t *src, *dst;

    /* Copy the decompressed RGB rectangular to the frame buffer */
    rectWidth = (rect->right - rect->left + 1) * jpeg->byte_per_pixel;
    src = (rt_uint8_t *)bitmap;

    if (jpeg->is_loaded == RT_TRUE)
    {
        rt_uint16_t imageWidth;          /* Width of image (bytes) */

        imageWidth = (jdec->width >> jdec->scale) * jpeg->byte_per_pixel;
        dst = jpeg->pixels + rect->top * imageWidth + rect->left * jpeg->byte_per_pixel;
        /* Left-top of destination rectangular */
        for (h = rect->top; h <= rect->bottom; h++)
        {
            rt_memcpy(dst, src, rectWidth);
            src += rectWidth;
            dst += imageWidth;           /* Next line */
        }
    }
    else
    {
        /* we decompress from top to bottom if the block is beyond the right
         * boundary, just continue to next block. However, if the block is
         * beyond the bottom boundary, we don't need to decompress the rest. */
        if (rect->left > jpeg->dst_w) return 1;
        if (rect->top  > jpeg->dst_h) return 0;

		w = _UI_MIN(rect->right, jpeg->dst_w);
        w = w - rect->left + 1;
		h = _UI_MIN(rect->bottom, jpeg->dst_h);
        h = h - rect->top + 1;

        for (y = 0; y < h; y++)
        {
            jpeg->dc->engine->blit_line(jpeg->dc,
                                        jpeg->dst_x + rect->left, jpeg->dst_x + rect->left + w,
                                        jpeg->dst_y + rect->top + y,
                                        src);
            src += rectWidth;
        }
    }
    return 1;                           /* Continue to decompress */
}

static rt_bool_t rtgui_image_jpeg_check(struct rtgui_filerw *file)
{
	rt_uint8_t soi[2];
	rtgui_filerw_seek(file, 0, RTGUI_FILE_SEEK_SET);
	rtgui_filerw_read(file, &soi, 2, 1);
	rtgui_filerw_seek(file, 0, RTGUI_FILE_SEEK_SET);

	/* check SOI==FFD8 */
	if (soi[0] == 0xff && soi[1] == 0xd8) return RT_TRUE;

	return RT_FALSE;
}

static rt_bool_t rtgui_image_jpeg_load(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load)
{
    rt_bool_t res = RT_FALSE;
    struct rtgui_image_jpeg *jpeg;
    JRESULT ret;
	struct rtgui_graphic_driver *hw_driver;

    do
    {
        jpeg = (struct rtgui_image_jpeg *)rt_malloc(sizeof(struct rtgui_image_jpeg));
        if (jpeg == RT_NULL) break;

        jpeg->filerw = file;
        jpeg->is_loaded = load;
        jpeg->pixels = RT_NULL;

		/* allocate memory pool */
        jpeg->pool = rt_malloc(TJPGD_WORKING_BUFFER_SIZE);
        if (jpeg->pool == RT_NULL)
        {
            rt_kprintf("TJPGD err: no mem (%d)\n", TJPGD_WORKING_BUFFER_SIZE);
            break;
        }

        if (rtgui_filerw_seek(jpeg->filerw, 0, RTGUI_FILE_SEEK_SET) == -1)
        {
            break;
        }

        ret = jd_prepare(&jpeg->tjpgd, tjpgd_in_func, jpeg->pool,
                         TJPGD_WORKING_BUFFER_SIZE, (void *)jpeg);
        if (ret != JDR_OK)
        {
            if (ret == JDR_FMT3)
            {
                rt_kprintf("TJPGD: not supported format\n");
            }
            break;
        }

		/* use RGB565 format */
		hw_driver = rtgui_graphic_driver_get_default();
		if (hw_driver->pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565)
		{
			jpeg->tjpgd.format = 1;
			jpeg->byte_per_pixel = 2;
		}
		/* else use RGB888 format */
		else jpeg->byte_per_pixel = 3;

        image->w = (rt_uint16_t)jpeg->tjpgd.width;
        image->h = (rt_uint16_t)jpeg->tjpgd.height;
        /* set image private data and engine */
        image->data = jpeg;
        image->engine = &rtgui_image_jpeg_engine;

        if (jpeg->is_loaded == RT_TRUE)
        {
            jpeg->pixels = (rt_uint8_t *)rtgui_malloc(
                               jpeg->byte_per_pixel * image->w * image->h);
            if (jpeg->pixels == RT_NULL)
            {
                rt_kprintf("TJPGD err: no mem to load (%d)\n",
                           jpeg->byte_per_pixel * image->w * image->h);
                break;
            }

            ret = jd_decomp(&jpeg->tjpgd, tjpgd_out_func, 0);
            if (ret != JDR_OK) break;

            rtgui_filerw_close(jpeg->filerw);
			jpeg->filerw = RT_NULL;
        }
        res = RT_TRUE;
    } while (0);

    if (jpeg && (!res || jpeg->is_loaded))
    {
        rt_free(jpeg->pool);
		jpeg->pool = RT_NULL;
    }

    if (!res)
    {
        if (jpeg)
            rtgui_free(jpeg->pixels);
        rt_free(jpeg);

		image->data   = RT_NULL;
		image->engine = RT_NULL;
    }

    /* create jpeg image successful */
    return res;
}

static void rtgui_image_jpeg_unload(struct rtgui_image *image)
{
    if (image != RT_NULL)
    {
        struct rtgui_image_jpeg *jpeg;

        jpeg = (struct rtgui_image_jpeg *) image->data;
        RT_ASSERT(jpeg != RT_NULL);

        if (jpeg->is_loaded == RT_TRUE)
        {
            rtgui_free(jpeg->pixels);
        }
        else
        {
            rt_free(jpeg->pool);
            rtgui_filerw_close(jpeg->filerw);
        }
        rt_free(jpeg);
    }
}

static void rtgui_image_jpeg_blit(struct rtgui_image *image,
                                  struct rtgui_dc *dc, struct rtgui_rect *dst_rect)
{
    rt_uint16_t y, w, h, xoff, yoff;
    struct rtgui_image_jpeg *jpeg;

    jpeg = (struct rtgui_image_jpeg *) image->data;
    RT_ASSERT(image != RT_NULL || dc != RT_NULL || dst_rect != RT_NULL || jpeg != RT_NULL);

    /* this dc is not visible */
    if (rtgui_dc_get_visible(dc) != RT_TRUE)
        return;
    jpeg->dc = dc;

    xoff = 0;
    if (dst_rect->x1 < 0)
    {
        xoff = -dst_rect->x1;
        dst_rect->x1 = 0;
    }
    yoff = 0;
    if (dst_rect->y1 < 0)
    {
        yoff = -dst_rect->y1;
        dst_rect->y1 = 0;
    }

    if (xoff >= image->w || yoff >= image->h)
        return;

    /* the minimum rect */
    w = _UI_MIN(image->w - xoff, rtgui_rect_width (*dst_rect));
    h = _UI_MIN(image->h - yoff, rtgui_rect_height(*dst_rect));

    if (rtgui_dc_get_pixel_format(dc) == RTGRAPHIC_PIXEL_FORMAT_RGB888 &&
        jpeg->tjpgd.format != 0)
    {
        jpeg->tjpgd.format = 0;
        jpeg->byte_per_pixel = 3;
    }
    else if (rtgui_dc_get_pixel_format(dc) == RTGRAPHIC_PIXEL_FORMAT_RGB565 &&
             jpeg->tjpgd.format != 1)
    {
        jpeg->tjpgd.format = 1;
        jpeg->byte_per_pixel = 2;
    }

    if (!jpeg->is_loaded)
    {
        JRESULT ret;

        /* TODO support xoff/yoff. */
        jpeg->dst_x = dst_rect->x1;
        jpeg->dst_y = dst_rect->y1;
        jpeg->dst_w = w;
        jpeg->dst_h = h;
        ret = jd_decomp(&jpeg->tjpgd, tjpgd_out_func, 0);
        if (ret != JDR_OK)
            return;
    }
    else
    {
        if ((rtgui_dc_get_pixel_format(dc) == RTGRAPHIC_PIXEL_FORMAT_RGB888 && jpeg->tjpgd.format == 0) ||
            (rtgui_dc_get_pixel_format(dc) == RTGRAPHIC_PIXEL_FORMAT_RGB565 && jpeg->tjpgd.format == 1))
        {
            rt_uint16_t imageWidth = image->w * jpeg->byte_per_pixel;
            rt_uint8_t *src = jpeg->pixels + yoff * imageWidth + xoff + jpeg->byte_per_pixel;

            for (y = 0; y < h; y++)
            {
                dc->engine->blit_line(dc,
                                      dst_rect->x1, dst_rect->x1 + w,
                                      dst_rect->y1 + y,
                                      src);
                src += imageWidth;
            }
        }
        /* if the format is not match, only support DC buffer */
        else if (dc->type == RTGUI_DC_BUFFER)
        {
            struct rtgui_blit_info info;
            struct rtgui_dc_buffer *buffer;

            buffer = (struct rtgui_dc_buffer*)dc;

            info.src = jpeg->pixels + yoff * image->w * jpeg->byte_per_pixel + xoff + jpeg->byte_per_pixel;
            info.src_h = rtgui_rect_height(*dst_rect);
            info.src_w = rtgui_rect_width(*dst_rect);
            info.src_fmt = (jpeg->tjpgd.format == 0? RTGRAPHIC_PIXEL_FORMAT_RGB888 : RTGRAPHIC_PIXEL_FORMAT_RGB565);
            info.src_pitch = info.src_w * jpeg->byte_per_pixel;
            info.src_skip = info.src_pitch - info.src_w * jpeg->byte_per_pixel;

            info.dst = rtgui_dc_buffer_get_pixel(RTGUI_DC(buffer)) + dst_rect->y1 * buffer->pitch +
                dst_rect->x1 * rtgui_color_get_bpp(buffer->pixel_format);
            info.dst_h = rtgui_rect_height(*dst_rect);
            info.dst_w = rtgui_rect_width(*dst_rect);
            info.dst_fmt = buffer->pixel_format;
            info.dst_pitch = buffer->pitch;
            info.dst_skip = info.dst_pitch - info.dst_w * rtgui_color_get_bpp(buffer->pixel_format);

            rtgui_blit(&info);
        }
    }
}
#endif /* defined(RTGUI_IMAGE_TJPGD) */
