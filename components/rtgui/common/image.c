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
 * 2012-01-24     onelife      add TJpgDec (Tiny JPEG Decompressor) support
 * 2012-08-29     amsl         add Image zoom interface.
 */
#include <rtthread.h>
#include <rtgui/image.h>

#include <rtgui/image_hdc.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/image_container.h>

#include <string.h>

#ifdef RTGUI_IMAGE_XPM
#include <rtgui/image_xpm.h>
#endif

#ifdef RTGUI_IMAGE_BMP
#include <rtgui/image_bmp.h>
#endif
#if (defined(RTGUI_IMAGE_JPEG) || defined(RTGUI_IMAGE_TJPGD))
#include <rtgui/image_jpeg.h>
#endif
#ifdef RTGUI_IMAGE_PNG
#include <rtgui/image_png.h>
#endif

static rtgui_list_t _rtgui_system_image_list = {RT_NULL};

/* initialize rtgui image system */
void rtgui_system_image_init(void)
{
	/* always support HDC image */
	rtgui_image_hdc_init();

#ifdef RTGUI_IMAGE_XPM
	rtgui_image_xpm_init();
#endif
	
#ifdef RTGUI_IMAGE_BMP
	rtgui_image_bmp_init();
#endif

#if (defined(RTGUI_IMAGE_JPEG) || defined(RTGUI_IMAGE_TJPGD))
	rtgui_image_jpeg_init();
#endif

#ifdef RTGUI_IMAGE_PNG
	rtgui_image_png_init();
#endif

#ifdef RTGUI_IMAGE_CONTAINER
	/* initialize image container */
	rtgui_system_image_container_init(RT_FALSE);
#endif
}

static struct rtgui_image_engine* rtgui_image_get_engine(const char* type)
{
	struct rtgui_list_node *node;
	struct rtgui_image_engine *engine;

	rtgui_list_foreach(node, &_rtgui_system_image_list)
	{
		engine = rtgui_list_entry(node, struct rtgui_image_engine, list);

		if (strncasecmp(engine->name, type, strlen(engine->name)) ==0)
			return engine;
	}

	return RT_NULL;
}

#if defined(RTGUI_USING_DFS_FILERW)
struct rtgui_image_engine* rtgui_image_get_engine_by_filename(const char* fn)
{
	struct rtgui_list_node *node;
	struct rtgui_image_engine *engine;
	const char* ext;

	ext = fn + rt_strlen(fn);
	while (ext != fn)
	{
		if (*ext == '.') { ext ++; break; }
		ext --;
	}
	if (ext == fn) return RT_NULL; /* no ext */

	rtgui_list_foreach(node, &_rtgui_system_image_list)
	{
		engine = rtgui_list_entry(node, struct rtgui_image_engine, list);
		if (strncasecmp(engine->name, ext, strlen(engine->name)) == 0)
			return engine;
	}

	return RT_NULL;
}
RTM_EXPORT(rtgui_image_get_engine_by_filename);

struct rtgui_image* rtgui_image_create_from_file(const char* type, const char* filename, rt_bool_t load)
{
	struct rtgui_filerw* filerw;
	struct rtgui_image_engine* engine;
	struct rtgui_image* image = RT_NULL;

	/* create filerw context */
	filerw = rtgui_filerw_create_file(filename, "rb");
	if (filerw == RT_NULL) return RT_NULL;

	/* get image engine */
	engine = rtgui_image_get_engine(type);
	if (engine == RT_NULL)
	{
		/* close filerw context */
		rtgui_filerw_close(filerw);
		return RT_NULL;
	}

	if (engine->image_check(filerw) == RT_TRUE)
	{
		image = (struct rtgui_image*) rtgui_malloc(sizeof(struct rtgui_image));
		if (image == RT_NULL)
		{
			/* close filerw context */
			rtgui_filerw_close(filerw);
			return RT_NULL;
		}

		image->palette = RT_NULL;
		if (engine->image_load(image, filerw, load) != RT_TRUE)
		{
			/* close filerw context */
			rtgui_filerw_close(filerw);
			return RT_NULL;
		}

		/* set image engine */
		image->engine = engine;
	}
	else
	{
		rtgui_filerw_close(filerw);
	}

	return image;
}
RTM_EXPORT(rtgui_image_create_from_file);

struct rtgui_image* rtgui_image_create(const char* filename, rt_bool_t load)
{
	struct rtgui_filerw* filerw;
	struct rtgui_image_engine* engine;
	struct rtgui_image* image = RT_NULL;

	/* create filerw context */
	filerw = rtgui_filerw_create_file(filename, "rb");
	if (filerw == RT_NULL) return RT_NULL;

	/* get image engine */
	engine = rtgui_image_get_engine_by_filename(filename);
	if (engine == RT_NULL)
	{
		/* close filerw context */
		rtgui_filerw_close(filerw);
		return RT_NULL;
	}

	if (engine->image_check(filerw) == RT_TRUE)
	{
		image = (struct rtgui_image*) rtgui_malloc(sizeof(struct rtgui_image));
		if (image == RT_NULL)
		{
			/* close filerw context */
			rtgui_filerw_close(filerw);
			return RT_NULL;
		}

		image->palette = RT_NULL;
		if (engine->image_load(image, filerw, load) != RT_TRUE)
		{
			/* close filerw context */
			rtgui_filerw_close(filerw);
			return RT_NULL;
		}

		/* set image engine */
		image->engine = engine;
	}
	else
	{
		rtgui_filerw_close(filerw);
	}

	return image;
}
RTM_EXPORT(rtgui_image_create);
#endif

struct rtgui_image* rtgui_image_create_from_mem(const char* type, const rt_uint8_t* data, rt_size_t length, rt_bool_t load)
{
	struct rtgui_filerw* filerw;
	struct rtgui_image_engine* engine;
	struct rtgui_image* image = RT_NULL;

	/* create filerw context */
	filerw = rtgui_filerw_create_mem(data, length);
	if (filerw == RT_NULL) return RT_NULL;

	/* get image engine */
	engine = rtgui_image_get_engine(type);
	if (engine == RT_NULL)
	{
		/* close filerw context */
		rtgui_filerw_close(filerw);
		return RT_NULL;
	}

	if (engine->image_check(filerw) == RT_TRUE)
	{
		image = (struct rtgui_image*) rtgui_malloc(sizeof(struct rtgui_image));
		if (image == RT_NULL)
		{
			/* close filerw context */
			rtgui_filerw_close(filerw);
			return RT_NULL;
		}

		image->palette = RT_NULL;
		if (engine->image_load(image, filerw, load) != RT_TRUE)
		{
			/* close filerw context */
			rtgui_filerw_close(filerw);
			return RT_NULL;
		}

		/* set image engine */
		image->engine = engine;
	}
	else
	{
		rtgui_filerw_close(filerw);
	}

	return image;
}
RTM_EXPORT(rtgui_image_create_from_mem);

void rtgui_image_destroy(struct rtgui_image* image)
{
	RT_ASSERT(image != RT_NULL);

	image->engine->image_unload(image);
	if (image->palette != RT_NULL)
		rtgui_free(image->palette);
	rtgui_free(image);
}
RTM_EXPORT(rtgui_image_destroy);

/* register an image engine */
void rtgui_image_register_engine(struct rtgui_image_engine* engine)
{
	RT_ASSERT(engine!= RT_NULL);

	rtgui_list_append(&_rtgui_system_image_list, &(engine->list));
}
RTM_EXPORT(rtgui_image_register_engine);

void rtgui_image_blit(struct rtgui_image* image, struct rtgui_dc* dc, struct rtgui_rect* rect)
{
	RT_ASSERT(dc	!= RT_NULL);
	RT_ASSERT(rect	!= RT_NULL);

	if (rtgui_dc_get_visible(dc) != RT_TRUE) return;

	if (image != RT_NULL && image->engine != RT_NULL)
	{
		/* use image engine to blit */
		image->engine->image_blit(image, dc, rect);
	}
}
RTM_EXPORT(rtgui_image_blit);

struct rtgui_image_palette* rtgui_image_palette_create(rt_uint32_t ncolors)
{
	struct rtgui_image_palette* palette = RT_NULL;

	if (ncolors > 0)
	{
		palette = (struct rtgui_image_palette*) rtgui_malloc(sizeof(struct rtgui_image_palette) + 
			sizeof(rtgui_color_t) * ncolors);
		if (palette != RT_NULL) palette->colors = (rtgui_color_t*)(palette + 1);
	}

	return palette;
}
RTM_EXPORT(rtgui_image_palette_create);

void rtgui_image_get_rect(struct rtgui_image* image, struct rtgui_rect* rect)
{
	RT_ASSERT(image != RT_NULL);
	RT_ASSERT(rect  != RT_NULL);

	rect->x1 = 0; rect->y1 = 0;
	rect->x2 = image->w; rect->y2 = image->h;
}
RTM_EXPORT(rtgui_image_get_rect);

rtgui_image_t* rtgui_image_zoom(rtgui_image_t* image, float scalew, float scaleh, rt_uint32_t mode)  
{ 
	if (image != RT_NULL && image->engine != RT_NULL)
	{
		return image->engine->image_zoom(image, scalew, scaleh, mode);
	}		
	return RT_NULL;
} 
RTM_EXPORT(rtgui_image_zoom);

rtgui_image_t* rtgui_image_rotate(rtgui_image_t* image, float angle)
{
	if (image != RT_NULL && image->engine != RT_NULL)
	{
		return image->engine->image_rotate(image, angle);
	}
	return RT_NULL;
}
RTM_EXPORT(rtgui_image_rotate);
