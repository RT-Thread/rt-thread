/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-17     Wayne        The first version
 */
/**
 * @file lv_gpu_n9h30_ge2d.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <lvgl.h>

#include "lv_gpu_n9h30_ge2d.h"
#include "nu_2d.h"
#include "mmu.h"

/*********************
 *      DEFINES
 *********************/

#if LV_COLOR_16_SWAP
    #error "Can't use GE2D with LV_COLOR_16_SWAP 1"
#endif

#if !((LV_COLOR_DEPTH == 16) || (LV_COLOR_DEPTH == 32))
    /*Can't use GPU with other formats*/
    #error "Can't use GPU with other formats"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void lv_draw_n9h30_ge2d_blend_fill(lv_color_t *dest_buf, lv_coord_t dest_stride, const lv_area_t *fill_area,
        lv_color_t color);


static void lv_draw_n9h30_ge2d_blend_map(lv_color_t *dest_buf, const lv_area_t *dest_area, lv_coord_t dest_stride,
        const lv_color_t *src_buf, lv_coord_t src_stride, lv_opa_t opa);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Turn on the peripheral and set output color mode, this only needs to be done once
 */
void lv_draw_n9h30_ge2d_ctx_init(lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx)
{
    lv_draw_sw_init_ctx(drv, draw_ctx);

    lv_draw_n9h30_ge2d_ctx_t *ge2d_draw_ctx = (lv_draw_sw_ctx_t *)draw_ctx;

    ge2d_draw_ctx->blend = lv_draw_n9h30_ge2d_blend;
    ge2d_draw_ctx->base_draw.wait_for_finish = lv_gpu_n9h30_ge2d_wait_cb;
}

void lv_draw_n9h30_ge2d_ctx_deinit(lv_disp_drv_t *drv, lv_draw_ctx_t *draw_ctx)
{
    LV_UNUSED(drv);
    LV_UNUSED(draw_ctx);
}

void lv_draw_n9h30_ge2d_blend(lv_draw_ctx_t *draw_ctx, const lv_draw_sw_blend_dsc_t *dsc)
{
    lv_area_t blend_area;
    int32_t blend_area_w;
    bool done = false;

    if (!_lv_area_intersect(&blend_area, dsc->blend_area, draw_ctx->clip_area)) return;

    blend_area_w = lv_area_get_width(&blend_area);

    if ((lv_area_get_size(&blend_area) > 7200) &&
            (((blend_area_w * (LV_COLOR_DEPTH / 2)) & 0x3) == 0) &&
            (dsc->mask_buf == NULL) && (dsc->blend_mode == LV_BLEND_MODE_NORMAL))
    {
        lv_coord_t dest_stride = lv_area_get_width(draw_ctx->buf_area);

        lv_color_t *dest_buf = draw_ctx->buf;
        dest_buf += dest_stride * (blend_area.y1 - draw_ctx->buf_area->y1) + (blend_area.x1 - draw_ctx->buf_area->x1);

        const lv_color_t *src_buf = dsc->src_buf;
        if (src_buf)
        {
            lv_coord_t src_stride;
            src_stride = lv_area_get_width(dsc->blend_area);
            src_buf += src_stride * (blend_area.y1 - dsc->blend_area->y1) + (blend_area.x1 -  dsc->blend_area->x1);
            lv_area_move(&blend_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);
            lv_draw_n9h30_ge2d_blend_map(dest_buf, &blend_area, dest_stride, src_buf, src_stride, dsc->opa);
            done = true;
        }
        else if (dsc->opa >= LV_OPA_MAX)
        {
            lv_area_move(&blend_area, -draw_ctx->buf_area->x1, -draw_ctx->buf_area->y1);
            lv_draw_n9h30_ge2d_blend_fill(dest_buf, dest_stride, &blend_area, dsc->color);
            done = true;
        }
    }

    if (!done)
    {
        lv_draw_sw_blend_basic(draw_ctx, dsc);
    }
}

static void lv_draw_n9h30_ge2d_blend_fill(lv_color_t *dest_buf, lv_coord_t dest_stride, const lv_area_t *fill_area,
        lv_color_t color)
{
    int32_t fill_area_w = lv_area_get_width(fill_area);
    int32_t fill_area_h = lv_area_get_height(fill_area);

    lv_color_t *start_buf = dest_buf - (fill_area->y1 * dest_stride) - fill_area->x1;

//    rt_kprintf("[blend_fill %d %08x] %dx%d %d %d\n", lv_area_get_size(fill_area), dest_buf, fill_area_w, fill_area_h, fill_area->x1, fill_area->y1 );

    if (IS_CACHEABLE_VRAM(dest_buf))
        mmu_clean_invalidated_dcache((uint32_t)dest_buf, sizeof(lv_color_t) * (dest_stride * fill_area_h + fill_area_w));

    /*Hardware filling*/
    // Enter GE2D ->
    ge2dInit(sizeof(lv_color_t) * 8, dest_stride, fill_area->y2, (void *)start_buf);

    ge2dClip_SetClip(fill_area->x1, fill_area->y1, fill_area->x2, fill_area->y2);

    if (sizeof(lv_color_t) == 4)
        ge2dFill_Solid(fill_area->x1, fill_area->y1, fill_area_w, fill_area_h, color.full);
    else if (sizeof(lv_color_t) == 2)
        ge2dFill_Solid_RGB565(fill_area->x1, fill_area->y1, fill_area_w, fill_area_h, color.full);

    ge2dClip_SetClip(-1, 0, 0, 0);
    // -> Leave GE2D
}

static void lv_draw_n9h30_ge2d_blend_map(lv_color_t *dest_buf, const lv_area_t *dest_area, lv_coord_t dest_stride,
        const lv_color_t *src_buf, lv_coord_t src_stride, lv_opa_t opa)
{
    int32_t dest_w = lv_area_get_width(dest_area);
    int32_t dest_h = lv_area_get_height(dest_area);

    //rt_kprintf("[blend_map %d %08x -> %08x] (x:%d y:%d, %dx%d) <stride src:%d dst:%d>\n", lv_area_get_size(dest_area), src_buf, dest_buf, dest_x, dest_y, dest_w, dest_h, src_stride, dest_stride);

    if (!IS_CACHEABLE_VRAM(dest_buf))
    {
        const lv_color_t *dest_start_buf = dest_buf - (dest_area->y1 * dest_stride) - dest_area->x1;
        int32_t dest_x = dest_area->x1;
        int32_t dest_y = dest_area->y1;

        // Enter GE2D ->
        ge2dInit(sizeof(lv_color_t) * 8, dest_stride, dest_area->y2, (void *)dest_start_buf);

        if (opa >= LV_OPA_MAX)
        {
            ge2dBitblt_SetAlphaMode(0, 0, 0);
            ge2dBitblt_SetDrawMode(0, 0, 0);
        }
        else
        {
            ge2dBitblt_SetAlphaMode(1, opa, opa);
        }

        if (IS_CACHEABLE_VRAM(src_buf))
            mmu_clean_dcache((uint32_t)src_buf, sizeof(lv_color_t) * (src_stride * dest_h + dest_w));

        ge2dSpriteBlt_Screen(dest_x, dest_y, dest_w, dest_h, (void *)src_buf);
        // -> Leave GE2D
    }
    else
    {
        int32_t x, y;

        /*Simple copy*/
        for (y = 0; y < dest_h; y++)
        {
            for (x = 0; x < dest_w; x++)
            {
                dest_buf[x] = src_buf[x];
            }
            dest_buf += dest_stride;
            src_buf += src_stride;
        }
    }
}

void lv_gpu_n9h30_ge2d_wait_cb(lv_draw_ctx_t *draw_ctx)
{
    lv_draw_sw_wait_for_finish(draw_ctx);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
