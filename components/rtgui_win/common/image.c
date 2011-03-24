/*
 * File      : image.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#include <rtthread.h>
#include <rtgui/image.h>

#include <rtgui/image_xpm.h>
#include <rtgui/image_hdc.h>
#include <rtgui/rtgui_system.h>

#include <string.h>

#ifdef RTGUI_IMAGE_BMP
#include <rtgui/image_bmp.h>
#endif
#ifdef RTGUI_IMAGE_JPEG
#include <rtgui/image_jpeg.h>
#endif
#ifdef RTGUI_IMAGE_PNG
#include <rtgui/image_png.h>
#endif

static rtgui_list_t _rtgui_system_image_list = {RT_NULL};

/* init rtgui image system */
void rtgui_system_image_init(void)
{
	/* always support XPM image */
	rtgui_image_xpm_init();
	rtgui_image_hdc_init();
	
#ifdef RTGUI_IMAGE_BMP
	rtgui_image_bmp_init();
#endif

#ifdef RTGUI_IMAGE_JPEG
	rtgui_image_jpeg_init();
#endif

#ifdef RTGUI_IMAGE_PNG
	rtgui_image_png_init();
#endif
}

static struct rtgui_image_engine* rtgui_image_get_engine(const char* type)
{
	rtgui_list_t *node;
	struct rtgui_image_engine *engine;

	rtgui_list_foreach(node, &_rtgui_system_image_list)
	{
		engine = rtgui_list_entry(node, struct rtgui_image_engine, list);

		if(strncasecmp(engine->name, type, strlen(engine->name)) ==0)
			return engine;
	}

	return RT_NULL;
}

#if defined(RTGUI_USING_DFS_FILERW) || defined(RTGUI_USING_STDIO_FILERW)
rtgui_image_t* rtgui_image_create_from_file(const char* type, const char* filename, rt_bool_t load)
{
	struct rtgui_filerw* file;
	struct rtgui_image_engine* engine;
	rtgui_image_t* image = RT_NULL;

	/* create filerw context */
	file = rtgui_filerw_create_file(filename, "rb");
	if(file == RT_NULL) return RT_NULL;

	/* get image engine */
	engine = rtgui_image_get_engine(type); 
	if(engine == RT_NULL)
	{
		/* close filerw context */
		rtgui_filerw_close(file);
		return RT_NULL;
	}

	if(engine->image_check(file) == RT_TRUE)
	{
		image = (rtgui_image_t*) rt_malloc(sizeof(rtgui_image_t)); 
		if(image == RT_NULL) 
		{
			/* close filerw context */
			rtgui_filerw_close(file);
			return RT_NULL;
		}

		if(engine->image_load(image, file, load) != RT_TRUE)
		{	
			/* close filerw context */
			rtgui_filerw_close(file);
			return RT_NULL;
		}

		/* set image engine */
		image->engine = engine;
	}
	else
	{
		rtgui_filerw_close(file);
	}

	return image;
}
#endif

rtgui_image_t* rtgui_image_create_from_mem(const char* type, const rt_uint8_t* data, rt_size_t length, rt_bool_t load)
{
	struct rtgui_filerw* file;
	struct rtgui_image_engine* engine;
	rtgui_image_t* image = RT_NULL;

	/* create filerw context */
	file = rtgui_filerw_create_mem(data, length);
	if(file == RT_NULL) return RT_NULL;

	/* È¡µÃÍ¼ÏñÒýÇæget image engine */
	engine = rtgui_image_get_engine(type);
	if(engine == RT_NULL)
	{
		/* close filerw context */
		rtgui_filerw_close(file);
		return RT_NULL;
	}

	if(engine->image_check(file) == RT_TRUE)
	{
		image = (rtgui_image_t*)rt_malloc(sizeof(rtgui_image_t));
		if(image == RT_NULL)
		{
			/* close filerw context */
			rtgui_filerw_close(file);
			return RT_NULL;
		}

		if(engine->image_load(image, file, load) != RT_TRUE)
		{
			/* close filerw context */
			rtgui_filerw_close(file);
			return RT_NULL;
		}

		/* set image engine */
		image->engine = engine;
	}
	else
	{
		rtgui_filerw_close(file);
	}

	return image;
}

void rtgui_image_destroy(rtgui_image_t* image)
{
	RT_ASSERT(image != RT_NULL);

	image->engine->image_unload(image);
	rt_free(image);
}

/* register an image engine */
void rtgui_image_register_engine(struct rtgui_image_engine* engine)
{
	RT_ASSERT(engine!= RT_NULL);

	rtgui_list_append(&_rtgui_system_image_list, &(engine->list));
}

void rtgui_image_blit(rtgui_image_t *image, rtgui_dc_t *dc, rtgui_rect_t *rect)
{
	RT_ASSERT(rect	!= RT_NULL);

	if(image != RT_NULL && image->engine != RT_NULL)
	{
		/* use image engine to blit */
		image->engine->image_blit(image, dc, rect);
	}
}

void rtgui_image_paste(rtgui_image_t *image, rtgui_dc_t *dc, rtgui_rect_t *rect, rtgui_color_t shield_color)
{
	RT_ASSERT(rect != RT_NULL);
	
	if(image != RT_NULL && image->engine != RT_NULL)
	{
		/* use image engine to blit */
		image->engine->image_paste(image, dc, rect, shield_color);
	}	
}

struct rtgui_image_palette* rtgui_image_palette_create(rt_uint32_t ncolors)
{
	struct rtgui_image_palette* palette = RT_NULL;

	if (ncolors > 0)
	{
		palette = (struct rtgui_image_palette*) rt_malloc(sizeof(struct rtgui_image_palette) + sizeof(rtgui_color_t) * ncolors);
		if (palette != RT_NULL) palette->colors = (rtgui_color_t*)(palette + 1);
	}

	return palette;
}

