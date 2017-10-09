/*
 * File      : image.h
 * This file is part of RT-Thread GUI Engine
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#ifndef __RTGUI_IMAGE_H__
#define __RTGUI_IMAGE_H__

#include <rtgui/dc.h>
#include <rtgui/filerw.h>
#include <rtgui/region.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rtgui_image;
struct rtgui_image_engine
{
    const char *name;
    struct rtgui_list_node list;

    /* image engine function */
    rt_bool_t (*image_check)(struct rtgui_filerw *file);

    rt_bool_t (*image_load)(struct rtgui_image *image, struct rtgui_filerw *file, rt_bool_t load);
    void (*image_unload)(struct rtgui_image *image);

    void (*image_blit)(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect);
};

struct rtgui_image_palette
{
    rtgui_color_t *colors;
    rt_uint32_t ncolors;
};
typedef struct rtgui_image_palette rtgui_image_palette_t;

struct rtgui_image
{
    /* image metrics */
    rt_uint16_t w, h;

    /* image engine */
    const struct rtgui_image_engine *engine;

    /* image palette */
    rtgui_image_palette_t *palette;

    /* image private data */
    void *data;
};
typedef struct rtgui_image rtgui_image_t;

/* init rtgui image system */
void rtgui_system_image_init(void);

#if defined(RTGUI_USING_DFS_FILERW)
struct rtgui_image_engine *rtgui_image_get_engine_by_filename(const char *fn);
struct rtgui_image *rtgui_image_create_from_file(const char *type, const char *filename, rt_bool_t load);
struct rtgui_image *rtgui_image_create(const char *filename, rt_bool_t load);
#endif

struct rtgui_image *rtgui_image_create_from_mem(const char *type, const rt_uint8_t *data, rt_size_t length, rt_bool_t load);
void rtgui_image_destroy(struct rtgui_image *image);

/* get image's rect */
void rtgui_image_get_rect(struct rtgui_image *image, struct rtgui_rect *rect);

/* register an image engine */
void rtgui_image_register_engine(struct rtgui_image_engine *engine);

/* blit an image on DC */
void rtgui_image_blit(struct rtgui_image *image, struct rtgui_dc *dc, struct rtgui_rect *rect);
struct rtgui_image_palette *rtgui_image_palette_create(rt_uint32_t ncolors);

#ifdef __cplusplus
}
#endif

#endif

