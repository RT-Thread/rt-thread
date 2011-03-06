#include <rtthread.h>
#include <rtgui/rtgui.h>

#ifdef RTGUI_IMAGE_JPEG
#include <stdio.h>
#include <stdlib.h>
#include "jpeglib.h"

#include <rtgui/rtgui_system.h>
#include <rtgui/filerw.h>
#include <rtgui/image_jpeg.h>

#ifdef RTGUI_USING_DFS_FILERW
#include <dfs_posix.h>
#endif

static rt_bool_t rtgui_image_jpeg_check(struct rtgui_filerw* file);
static rt_bool_t rtgui_image_jpeg_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load);
static void rtgui_image_jpeg_unload(struct rtgui_image* image);
static void rtgui_image_jpeg_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect);

struct rtgui_jpeg_error_mgr
{
	struct jpeg_error_mgr pub;	/* "public" fields */
};

struct rtgui_image_jpeg
{
	rt_bool_t is_loaded;

	struct rtgui_filerw* filerw;

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

#define INPUT_BUFFER_SIZE	4096
typedef struct {
	struct jpeg_source_mgr pub;

	struct rtgui_filerw* ctx;
	rt_uint8_t buffer[INPUT_BUFFER_SIZE];
} rtgui_jpeg_source_mgr;

/*
* Initialize source --- called by jpeg_read_header
* before any data is actually read.
*/
static void init_source (j_decompress_ptr cinfo)
{
	/* We don't actually need to do anything */
	return;
}

/*
* Fill the input buffer --- called whenever buffer is emptied.
*/
static boolean fill_input_buffer (j_decompress_ptr cinfo)
{
	rtgui_jpeg_source_mgr * src = (rtgui_jpeg_source_mgr *) cinfo->src;
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
static void skip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
	rtgui_jpeg_source_mgr * src = (rtgui_jpeg_source_mgr *) cinfo->src;

	/* Just a dumb implementation for now.	Could use fseek() except
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
static void term_source (j_decompress_ptr cinfo)
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
	if (cinfo->src == NULL) {	/* first time for this JPEG object? */
		cinfo->src = (struct jpeg_source_mgr *)
			(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
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
static rt_uint8_t *rtgui_image_get_line(struct rtgui_image* image, int h)
{
	struct rtgui_image_jpeg* jpeg;
	rt_uint8_t *result_ptr;

	JSAMPARRAY buffer;		/* Output row buffer */
	int row_stride;

	RT_ASSERT(image != RT_NULL);
	jpeg = (struct rtgui_image_jpeg*) image->data;
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

		ptr = (rtgui_color_t*)jpeg->line_pixels;
		for (index = 0; index < image->w; index ++)
			ptr[index] = RTGUI_ARGB(0, buffer[0][index*3], buffer[0][index*3+1], buffer[0][index*3+2]);
	}

	return jpeg->line_pixels;
}

static rt_bool_t rtgui_image_jpeg_loadall(struct rtgui_image* image)
{
	struct rtgui_image_jpeg* jpeg;
	rt_uint8_t* line_ptr;
	JSAMPARRAY buffer;		/* Output row buffer */
	int row_stride;

	jpeg = (struct rtgui_image_jpeg*) image->data;
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

			ptr = (rtgui_color_t*)line_ptr;
			for (index = 0; index < image->w; index ++)
				ptr[index] = RTGUI_ARGB(0, buffer[0][index*3], buffer[0][index*3+1], buffer[0][index*3+2]);
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

static rt_bool_t rtgui_image_jpeg_load(struct rtgui_image* image, struct rtgui_filerw* file, rt_bool_t load)
{
	struct rtgui_image_jpeg* jpeg;

	jpeg = (struct rtgui_image_jpeg*) rtgui_malloc(sizeof(struct rtgui_image_jpeg));
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
	jpeg->cinfo.scale_num	= 1;
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
		rt_free(jpeg);

		return RT_FALSE;
	}

	if (load == RT_TRUE) rtgui_image_jpeg_loadall(image);

	/* create jpeg image successful */
	return RT_TRUE;
}


static void rtgui_image_jpeg_unload(struct rtgui_image* image)
{
	if (image != RT_NULL)
	{
		struct rtgui_image_jpeg* jpeg;

		jpeg = (struct rtgui_image_jpeg*) image->data;
		RT_ASSERT(jpeg != RT_NULL);

		if (jpeg->is_loaded == RT_TRUE)
			rtgui_free(jpeg->pixels);
		if (jpeg->line_pixels != RT_NULL) rtgui_free(jpeg->line_pixels);

		if (jpeg->is_loaded != RT_TRUE)
		{
			rtgui_filerw_close(jpeg->filerw);
			jpeg_finish_decompress(&jpeg->cinfo);
		}
		rt_free(jpeg);
	}
}

static void rtgui_image_jpeg_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect)
{
	rt_uint16_t x, y;
	rtgui_color_t* ptr;
	struct rtgui_image_jpeg* jpeg;

	RT_ASSERT(image != RT_NULL && dc != RT_NULL && rect != RT_NULL);

	jpeg = (struct rtgui_image_jpeg*) image->data;
	RT_ASSERT(jpeg != RT_NULL);

	if (jpeg->pixels != RT_NULL)
	{
		ptr = (rtgui_color_t*) jpeg->pixels;

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
	else 
	{
		/* seek to the begin of file */
		rtgui_filerw_seek(jpeg->filerw, 0, SEEK_SET);

		/* decompress line and line */
		for (y = 0; y < image->h; y ++)
		{
			ptr = (rtgui_color_t*)rtgui_image_get_line(image, y);
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

static rt_bool_t rtgui_image_jpeg_check(struct rtgui_filerw* file)
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
	rtgui_filerw_seek(file, 0, SEEK_SET);
		
	if ( rtgui_filerw_read(file, magic, 2, 1) ) {
		if ( (magic[0] == 0xFF) && (magic[1] == 0xD8) ) {
			is_JPG = RT_TRUE;
			while (is_JPG == RT_TRUE) {
				if(rtgui_filerw_read(file, magic, 1, 2) != 2) {
					is_JPG = RT_FALSE;
				} else if( (magic[0] != 0xFF) && (in_scan == 0) ) {
					is_JPG = RT_FALSE;
				} else if( (magic[0] != 0xFF) || (magic[1] == 0xFF) ) {
					/* Extra padding in JPEG (legal) */
					/* or this is data and we are scanning */
					rtgui_filerw_seek(file, -1, SEEK_CUR);
				} else if(magic[1] == 0xD9) {
					/* Got to end of good JPEG */
					break;
				} else if( (in_scan == 1) && (magic[1] == 0x00) ) {
					/* This is an encoded 0xFF within the data */
				} else if( (magic[1] >= 0xD0) && (magic[1] < 0xD9) ) {
					/* These have nothing else */
				} else if(rtgui_filerw_read(file, magic+2, 1, 2) != 2) {
					is_JPG = RT_FALSE;
				} else {
					/* Yes, it's big-endian */
					rt_uint32_t start;
					rt_uint32_t size;
					rt_uint32_t end;
					start = rtgui_filerw_tell(file);
					size = (magic[2] << 8) + magic[3];
					end = rtgui_filerw_seek(file, size-2, SEEK_CUR);
					if ( end != start + size - 2 ) is_JPG = RT_FALSE;
					if ( magic[1] == 0xDA ) {
						/* Now comes the actual JPEG meat */
						/* It is a JPEG. */
						break;
					}
				}
			}
		}
	}
	rtgui_filerw_seek(file, start, SEEK_SET);

	return is_JPG;
}

#endif
