/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright 2020 NXP
*    All Rights Reserved.
*
*    Permission is hereby granted, free of charge, to any person obtaining
*    a copy of this software and associated documentation files (the
*    'Software'), to deal in the Software without restriction, including
*    without limitation the rights to use, copy, modify, merge, publish,
*    distribute, sub license, and/or sell copies of the Software, and to
*    permit persons to whom the Software is furnished to do so, subject
*    to the following conditions:
*
*    The above copyright notice and this permission notice (including the
*    next paragraph) shall be included in all copies or substantial
*    portions of the Software.
*
*    THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
*    IN NO EVENT SHALL VIVANTE AND/OR ITS SUPPLIERS BE LIABLE FOR ANY
*    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
*    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

/** Include Files */
#include "vg_lite.h"
#include "vg_lite_text.h"
#include <stdio.h>
#include <string.h>

#include <mcufont.h>
#include "vft_draw.h"

/** Macros */

/** Data structures */
typedef struct {
    /* Font related parameters */
    vg_lite_font_attributes_t *attributes;
    vg_lite_buffer_t buffer;
    uint16_t width;
    uint16_t height;
    uint16_t y;
    const struct mf_font_s *rcd_font;
} text_context_t;

/** Internal or external API prototypes */
struct mf_font_s *_vg_lite_get_raster_font(vg_lite_font_t font_idx);
int vg_lite_is_font_valid(vg_lite_font_t font);

/** Globals */
vg_lite_font_attributes_t g_font_attribs;
vg_lite_font_t g_last_font = VG_LITE_INVALID_FONT;
int g_last_font_attrib_idx;

/** Externs if any */

/* Capture unique values of alpha */
static unsigned int g_index_table[257];

/* text_color is in ARGB8888 format */
int init_256pallet_color_table(unsigned int bg_color, unsigned int fg_color)
{
  int i;
  g_index_table[0] = 0; /* Background color */
  int fg_r = ((fg_color>>0)&0xff);
  int fg_g = ((fg_color>>8)&0xff);
  int fg_b = ((fg_color>>16)&0xff);

  int bg_r = ((bg_color>>0)&0xff);
  int bg_g = ((bg_color>>8)&0xff);
  int bg_b = ((bg_color>>16)&0xff);

  for (i=1; i<256; i++) {
    int r, g, b;
    int a = 0xff;
    register int mult, mult2;

    mult = ((i*1024)/256);
    mult2 = (((256-i)*1024)/256);

    /* Blend with white bg */
    r = ( ((bg_r * mult2)>>10) +((fg_r * mult)>>10) );
    g = ( ((bg_g * mult2)>>10) +((fg_g * mult)>>10) );
    b = ( ((bg_b * mult2)>>10) +((fg_b * mult)>>10) );
    g_index_table[i] = ((a) + (r<<8) + (g<<16)+(b<<24));
  }
  return 0;
}

/* Callback to write to a memory buffer. */
static void pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha,
                           void *state)
{
    text_context_t *s = (text_context_t*)state;
    uint32_t pos;
    uint32_t value;
    uint32_t *raw_pixel_buffer = (uint32_t *)s->buffer.memory;
    int stride = s->buffer.stride;

    if (y < 0 || y >= s->height) return;
    if (x < 0 || x + count >= s->width) return;

    while (count--)
    {
        pos = (uint32_t)stride * y + x;
        value = g_index_table[alpha];

        raw_pixel_buffer[pos] = value;

        x++;
    }
}

/* Callback to render characters. */
static uint8_t character_callback(int16_t x, int16_t y, mf_char character,
                                  void *state)
{
    text_context_t *s = (text_context_t*)state;
    return mf_render_character(s->rcd_font, x, y, character, pixel_callback, state);
}

/* Callback to render lines. */
static bool line_callback(const char *line, uint16_t count, void *state)
{
    text_context_t *s = (text_context_t*)state;

    if (s->attributes->justify)
    {
        mf_render_justified(s->rcd_font, s->attributes->anchor, s->y,
                            s->width - s->attributes->margin * 2,
                            line, count, character_callback, state);
    }
    else
    {
        mf_render_aligned(s->rcd_font, s->attributes->anchor, s->y,
                          (enum mf_align_t)s->attributes->alignment, line, count,
                          character_callback, state);
    }
    s->y += s->rcd_font->line_height;
    return true;
}

/* Callback to just count the lines.
 * Used to decide the image height */
bool count_lines(const char *line, uint16_t count, void *state)
{
    int *linecount = (int*)state;
    (*linecount)++;
    return true;
}

vg_lite_error_t alloc_font_buffer(vg_lite_buffer_t *buffer, int width , int height)
{
    vg_lite_error_t error;

    /* Align width to 16 pixels, heigh to 16 pixels */
    width = ((width+15)&(~15));
    height = ((height+15)&(~15));

    /* Allocate memory from VGLITE space */
    buffer->width  = width;
    buffer->height = height;
    buffer->format = VG_LITE_ARGB8888;
    buffer->stride = 0;
    error = vg_lite_allocate(buffer);
    buffer->stride = width;
    buffer->tiled = VG_LITE_LINEAR;

    return error;
}

static vg_lite_error_t free_font_buffer(vg_lite_buffer_t *buffer)
{
    vg_lite_error_t error;

    error = vg_lite_free(buffer);

    return error;
}

void matrix_multiply(vg_lite_matrix_t * matrix, vg_lite_matrix_t * mult)
{
    vg_lite_matrix_t temp;
    int row, column;

    /* Process all rows. */
    for (row = 0; row < 3; row++) {
        /* Process all columns. */
        for (column = 0; column < 3; column++) {
            /* Compute matrix entry. */
            temp.m[row][column] =  (matrix->m[row][0] * mult->m[0][column])
            + (matrix->m[row][1] * mult->m[1][column])
            + (matrix->m[row][2] * mult->m[2][column]);
        }
    }

    /* Copy temporary matrix into result. */
    memcpy(matrix, &temp, sizeof(temp));
}

vg_lite_error_t vg_lite_draw_text(vg_lite_buffer_t *target,
                                  char *text,
                                  vg_lite_font_t font,
                                  int x,
                                  int y,
                                  vg_lite_matrix_t *matrix,
                                  vg_lite_blend_t blend,
                                  vg_lite_font_attributes_t *attributes)
{
    vg_lite_error_t error;
    int height;
    text_context_t ctx_text;
    vg_lite_matrix_t m_text;
    int text_img_size = 0;
    font_face_desc_t* font_face = NULL;
    int text_width_in_pixels = 0;
    int tmpX;

    memset(&ctx_text, 0, sizeof(ctx_text));
    ctx_text.attributes = attributes;

    if ( vg_lite_is_font_valid(font) != 0 ) {
        return VG_LITE_INVALID_ARGUMENT;
    }

    error = vg_lite_load_font_data(font,
                                 attributes->font_height);
    if ( error != 0 ) {
        return VG_LITE_INVALID_ARGUMENT;
    }

    if(attributes->tspan_has_dx_dy != 0)
    {
        if ( x < 0 )
            x = attributes->last_x + attributes->last_dx;
        if ( y < 0 )
            y = attributes->last_y;
    }

    // Dynamic decision
    if ( attributes->is_vector_font == 0 ) {
        init_256pallet_color_table(attributes->bg_color, attributes->text_color);

        /* Application specifies actual font by reading proper rcd file */
        ctx_text.rcd_font = _vg_lite_get_raster_font(font);

        /* Count number of lines to decide font buffer size. */
        height = 0;
        mf_text_draw_area(ctx_text.rcd_font, attributes->width - 2 * attributes->margin,
                    text, &height, &text_width_in_pixels);
        height *= attributes->font_height;
        height += 4;

        if( attributes->tspan_has_dx_dy == 0) {
            y -= attributes->font_height;
        }

        tmpX = x;
        if(attributes->alignment == eTextAlignCenter) {
            tmpX -= text_width_in_pixels/2;
        } else if(attributes->alignment == eTextAlignRight) {
            tmpX -= text_width_in_pixels;
        }
        /* Manually calculate X-offset for text-alignemnt; mcufont just
         * doesn't render half part(left-part) for center alignment and
         * full string skipped for right-alignment, So again set it to
         * left-alignment for font-attrib, as offsets are already
         * calculated and alignment handled in other way */
        attributes->alignment = 0;

        /* Allocate and initialize vg_lite_buffer that can hold font text
         * Note: ctx_text.width and ctx_text.height get used by internal
         *   state of MF rendering engine. Based on amount of text to render
         *   This buffer gets allocated, and buffer width gets aligned to
         *   16 pixel boundary
         */
        ctx_text.width = attributes->width;
        /* Memory optimization */
        ctx_text.width = text_width_in_pixels;
        /* Align width to 16 pixel boundary */
        if (ctx_text.width & 15) {
            ctx_text.width += 15;
            ctx_text.width &= (~15);
        }

        ctx_text.height = height;
        error = alloc_font_buffer(&ctx_text.buffer, ctx_text.width, ctx_text.height);
        if ( error != VG_LITE_SUCCESS) {
            printf("WARNING: alloc_font_buffer failed(%d).\r\n",error);
        }
        ctx_text.y = 2;

        /* Initialize vg_lite buffer with transperant color */
        /* Due to alignment requirement of vg_lite, font buffer can be larger */
        if ( ctx_text.buffer.format == VG_LITE_ARGB8888 )
          text_img_size = ctx_text.buffer.width * ctx_text.buffer.height * 4;
        else
          text_img_size = ctx_text.buffer.width * ctx_text.buffer.height;
        memset(ctx_text.buffer.memory, 0,
               text_img_size);

        /* Render font text into vg_lite_buffer  */
        mf_wordwrap(ctx_text.rcd_font, attributes->width - 2 * attributes->margin,
                    text, line_callback, &ctx_text);

        /* Draw font bitmap on render target */
        vg_lite_identity(&m_text);
        matrix_multiply(&m_text, matrix);
        vg_lite_translate(x, y, &m_text);
        vg_lite_scale(1.0, 1.0, &m_text);
        if ( ctx_text.buffer.format == VG_LITE_ARGB8888 )
          ctx_text.buffer.stride = ctx_text.width*4;

        error = vg_lite_blit(target, &ctx_text.buffer, &m_text, blend,
                    0, VG_LITE_FILTER_POINT);
        if ( error != VG_LITE_SUCCESS) {
            printf("WARNING: vg_lite_blit failed(%d).\r\n",error);
        }

        error = vg_lite_finish();
        if ( error != VG_LITE_SUCCESS) {
            printf("WARNING: vg_lite_finish failed(%d).\r\n",error);
        }

        error = free_font_buffer(&ctx_text.buffer);
        if ( error != VG_LITE_SUCCESS) {
            printf("WARNING: vg_lite_finish failed(%d).\r\n",error);
        }
        attributes->last_dx = text_width_in_pixels;
    } else {
      error = (vg_lite_error_t)vg_lite_vtf_draw_text(target,
                                    x, y,
                                    blend,
                                    font,
                                    matrix,
                                    attributes,
                                    text);
         /* Note: vg_lite_vtf_draw_text updates attributes->last_dx internally
            This assignment is just to keep code similar to rcd code */
        attributes->last_dx = attributes->last_dx;

        error = vg_lite_finish();
        if ( error != VG_LITE_SUCCESS) {
            printf("WARNING: vg_lite_finish failed(%d).\r\n",error);
        }

        vft_unload(font_face);
    }
    attributes->last_x = x;
    attributes->last_y = y;

    return error;
}
