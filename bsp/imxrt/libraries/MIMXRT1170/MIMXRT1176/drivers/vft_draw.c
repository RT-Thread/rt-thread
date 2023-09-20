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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vg_lite.h"
#include "vg_lite_text.h"
#include "vft_draw.h"
#include "vft_debug.h"

#include "rtthread.h"

/** Macros */
#define VFT_ALLOC(x) _mem_allocate(x)
#define VFT_FREE(x) _mem_free(x)
#define READ_BIN_FIELD(x) memcpy(&g->x, (buf + offset), sizeof(g->x));  offset += sizeof(g->x)
#define READ_BIN_FIELD_STR(x) READ_BIN_FIELD(x)
#define READ_BIN_FIELD_UINT16(x) READ_BIN_FIELD(x)
#define READ_BIN_FIELD_UINT32(x) READ_BIN_FIELD(x)
#define READ_BIN_FIELD_FLOAT(x) READ_BIN_FIELD(x)
#define READ_BIN_FIELD_DUMMY_POINTER(x) offset += 4;
#define GLYPH_CACHE_SIZE 16
#define ENABLE_TEXT_WRAP 0
#define HALT_ALLOCATOR_ERROR 1

/** Data structures */
typedef struct glyph_cache_desc {
    vg_lite_path_t *h_path;
    glyph_desc_t *g;
    uint32_t use_count;
}glyph_cache_desc_t;

/** Internal or external API prototypes */

/** Globals */
static int g_glyph_cache_init_done = 0;
static glyph_cache_desc_t g_glyph_cache[GLYPH_CACHE_SIZE];
int g_total_bytes = 0;

/** Externs if any */

/* Internal API, not published to user */
font_face_desc_t *_vg_lite_get_vector_font(vg_lite_font_t font_idx);
void matrix_multiply(vg_lite_matrix_t * matrix, vg_lite_matrix_t *mult);

void *_mem_allocate(int size)
{
  char *buf = NULL;

  if ( size == 0 ) {
    printf("ERROR: HALT: Why allocating %d bytes\n", size);
#if HALT_ALLOCATOR_ERROR
    while(1);
#else
    return NULL;
#endif
  }

  buf = rt_malloc(size);
  if (buf == NULL) {
    printf("ERROR: HALT: allocating %d bytes \"system out of memory\"\n", size);
#if HALT_ALLOCATOR_ERROR
    while(1);
#else
    return NULL;
#endif
  }
  g_total_bytes += size;
  return buf;
}

void _mem_free(void *buf)
{
    rt_free(buf);
}

/** GLYPH CACHING Code */
void glyph_cache_init(void)
{
    if ( g_glyph_cache_init_done == 0 ) {
        memset(g_glyph_cache,0,sizeof(g_glyph_cache));
        g_glyph_cache_init_done = 1;
    }
}

void glyph_cache_free(void)
{
    int i;
    for (i=0; i<GLYPH_CACHE_SIZE; i++) {
        if ( g_glyph_cache[i].h_path != NULL ) {
            /* For non-mapped path this resetting is sufficient */
            vg_lite_clear_path(g_glyph_cache[i].h_path);

            /* Release path handle */
            VFT_FREE(g_glyph_cache[i].h_path);

            /* Reset pointer */
            g_glyph_cache[i].h_path = NULL;
        }
    }

    /* Next time font init will be required */
    g_glyph_cache_init_done = 0;
}

vg_lite_path_t *vft_cache_lookup(glyph_desc_t *g)
{
    int i;
    int unused_idx = 0;

    /* Not present caching code does not handle multiple font-face */
    glyph_cache_init();

    /* Check if path object for given glyph exists */
    for (i=0; i<GLYPH_CACHE_SIZE; i++) {
        if ( g_glyph_cache[i].g != NULL && g->unicode ==
            g_glyph_cache[i].g->unicode )
        {
            g_glyph_cache[i].use_count++;
            return g_glyph_cache[i].h_path;
        }
    }

    /* Find least used descriptor */
    unused_idx = 0;
    for (i=1; i<GLYPH_CACHE_SIZE; i++) {
      if ( g_glyph_cache[i].use_count <
          g_glyph_cache[unused_idx].use_count ) {
            unused_idx = i;
      }
    }
    /* Re-cycle descriptor */
    if ( g_glyph_cache[unused_idx].h_path != NULL ) {
        /* For non-mapped path this resetting is sufficient */
        vg_lite_clear_path(g_glyph_cache[unused_idx].h_path);
    } else {
        /* Allocate new path object */
        g_glyph_cache[unused_idx].h_path =
            (vg_lite_path_t *)VFT_ALLOC(sizeof(vg_lite_path_t));
    }
    /* Allocate new path */
    vg_lite_init_path(g_glyph_cache[unused_idx].h_path,
                      VG_LITE_FP32, VG_LITE_HIGH,
                      g->path.num_draw_cmds*4,
                      g->path.draw_cmds,
                      g->path.bounds[0],
                      g->path.bounds[1],
                      g->path.bounds[2],
                      g->path.bounds[3]);
    g_glyph_cache[unused_idx].g = g;
    g_glyph_cache[unused_idx].use_count = 1;
    return g_glyph_cache[unused_idx].h_path;
}

/** Render text using vector fonts */
int vg_lite_vtf_draw_text(vg_lite_buffer_t *rt, int x, int y,
                      vg_lite_blend_t blend,
                      vg_lite_font_t font,
                      vg_lite_matrix_t *matrix,
                      vg_lite_font_attributes_t  * attributes,
                      char *text)
{
    font_face_desc_t *font_face;
    glyph_desc_t* g1 = NULL;
    glyph_desc_t* g2;
    int error = 0;
    float font_scale = 1.0;
    int text_wrap = 0;

    font_face = (font_face_desc_t *)_vg_lite_get_vector_font(font);

    attributes->last_dx = 0;
    font_scale = ((1.0*attributes->font_height)/font_face->units_per_em);

    vg_lite_matrix_t mat;

    vg_lite_fill_t    fill_rule = VG_LITE_FILL_NON_ZERO;
    vg_lite_color_t   color = attributes->text_color;

    /* Compute size of tex in pixels
     * For center alignment adjust x position
     * Present parser has bug in encoding alignment value,
     * Once it is fixed following code will align text in center
     */
    if ( attributes->alignment == eTextAlignCenter ||
         attributes->alignment == eTextAlignRight ) {
        char *t2 = text;
        int dx = 0;
        uint16_t ug2; /* Unicode glyph */
        int kx;

        /* Case of center alignement */
        while (*t2 != '\0') {
            ug2 = *t2;
            kx = 0;
            g2 = vft_find_glyph(font_face, ug2);
            if (g1 != NULL && g2 != NULL) {
                kx = vft_glyph_distance(g1, g2);
            }

            dx += ((g2->horiz_adv_x + kx )* font_scale);
            t2++;
        }

        if ( attributes->alignment == eTextAlignCenter) {
            x -= (dx/2);
        } else if ( attributes->alignment == eTextAlignRight) {
            x -= (dx);
        }
    }

    /* Compute pixels that will cover this vector path */
    while (*text != '\0') {
        uint16_t ug2; /* Unicode glyph */
        int kx;

        if (text_wrap == 0) {
            vg_lite_identity(&mat);
            matrix_multiply(&mat, matrix);
            vg_lite_translate(x,y, &mat);
            vg_lite_scale(font_scale,font_scale, &mat); // 0.35 = height/units_per_em
            vg_lite_scale(-1.0,1.0, &mat);
            vg_lite_scale(-1.0,-1.0, &mat);
            text_wrap = 1;
        }

        /* Read unicode character */
        kx = 0;
        ug2 = *text;
        g2 = vft_find_glyph(font_face, ug2);
        if (g1 != NULL && g2 != NULL) {
            kx = vft_glyph_distance(g1, g2);
        }

#if (ENABLE_TEXT_WRAP==1)
        /* Wrap text */
        if ( (x + attributes->last_dx + ((g2->horiz_adv_x + kx )* font_scale))
              >= (720 - 5) )
        {
          text_wrap = 0;
          attributes->last_dx = 0;
          y += (attributes->font_height + 1);
          continue;
        }
#endif /* ENABLE_TEXT_WRAP */

        /* Compute glyph size in horizontal dimension */
        g1 = g2;
        text++;

        error = vg_lite_draw(rt, vft_cache_lookup(g2),
                             fill_rule,
                             &mat,
                             blend,
                             color);
        if ( error != VG_LITE_SUCCESS ) {
          break;
        }

        vg_lite_translate(g2->horiz_adv_x + kx, 0, &mat);
        attributes->last_dx += ((g2->horiz_adv_x + kx )* font_scale);
    }

    attributes->last_dx += 2; /* Space between 2 text strings */

    return 0;
}

void load_font_face(font_face_desc_t* font_face, uint8_t* buf, int font_face_offset)
{
    font_face_desc_t* g = font_face;
    int offset = font_face_offset;

    READ_BIN_FIELD_STR(font_family_name);
    READ_BIN_FIELD_UINT16(units_per_em);
    READ_BIN_FIELD_UINT16(ascent);
    READ_BIN_FIELD_UINT16(descent);
    READ_BIN_FIELD_UINT16(vg_font);
    READ_BIN_FIELD_UINT32(num_glyphs);
}

void load_glyph_table(font_face_desc_t* font_face, uint8_t* buf, int glyph_table_offset)
{
    int offset = glyph_table_offset;

    for (uint32_t i = 0; i < font_face->num_glyphs; i++) {
        glyph_desc_t* g = &font_face->glyphs[i];

        memset(g, 0, sizeof(glyph_desc_t));
        READ_BIN_FIELD_UINT16(unicode);
        READ_BIN_FIELD_UINT16(horiz_adv_x);
        READ_BIN_FIELD_UINT32(kern_num_entries);
        READ_BIN_FIELD_UINT32(kern_table_offset);
        READ_BIN_FIELD_DUMMY_POINTER();
        READ_BIN_FIELD_FLOAT(path.bounds[0]);
        READ_BIN_FIELD_FLOAT(path.bounds[1]);
        READ_BIN_FIELD_FLOAT(path.bounds[2]);
        READ_BIN_FIELD_FLOAT(path.bounds[3]);
        READ_BIN_FIELD_UINT32(path.num_draw_cmds);
        READ_BIN_FIELD_UINT32(path.draw_cmds_offset);
        READ_BIN_FIELD_DUMMY_POINTER();

        font_face->glyphs[i].kern_table = (kern_desc_t *)(buf + font_face->glyphs[i].kern_table_offset);
        font_face->glyphs[i].path.draw_cmds = (float *)(buf + font_face->glyphs[i].path.draw_cmds_offset);

        TRACE_INFO(("Glyph: '%c'\n", g->unicode));
        vft_dbg_glyph_desc(g, d_offset);
    }
}

/* Load vector font ROM table from file */
font_face_desc_t* vft_load_from_buffer(char* buf_base, int file_size)
{
    font_face_desc_t* font_face = NULL;
    uint32_t* blk_hdr;
    //int error = 0;

    /* Setup internal memory pointers of font_face_desc_t */
    int font_face_offset = 0;
    int glyph_table_offset = 0;
    //int kern_table_offset = 0;
    //int path_data_offset = 0;
    int offset = 0;

    /* May be we can avoid this lookup */
    while (offset < file_size) {
        blk_hdr = (uint32_t*)(buf_base + offset);
        eFontBlock_t eType = (eFontBlock_t)((*blk_hdr) >> 24);
        int size  = ((*blk_hdr) & ((1<<24)-1));
        TRACE_BIN(("BIN: %08x:  block(%hu, %hu)\n",
            offset, eType, size));
        offset += BLK_HDR_SIZE;

        /* Check integrity of block and then only proceed */
        switch (eType) {
        case eFontFaceDesc:
            font_face_offset = offset;
            break;
        case eGlyphTableDesc:
            glyph_table_offset = offset;
            break;
        case eKernTableDesc:
            //kern_table_offset = offset;
            break;
        case eGlyphData:
            //path_data_offset = offset;
            break;
        default:
        case eUnkBlock:
        case eMaxBlock:
            return NULL;;
        }
        offset += size;
    }

    if (offset < 0 || offset > file_size) {
        printf("ERROR: Vector font file integrity error aborting..\n");
        return NULL;
    }

    /* Make structure binary compliant to reduce loading time */
    font_face = (font_face_desc_t*)(buf_base + font_face_offset);
    font_face->glyphs = (glyph_desc_t*)(buf_base + glyph_table_offset);

    VFT_DBG_FONT_FACE_DESC(font_face, font_face_offset);
    for (uint32_t i = 0; i < font_face->num_glyphs; i++) {
        /* Update internal pointer from memory mapped file */
        font_face->glyphs[i].kern_table =
            (kern_desc_t*)(buf_base + font_face->glyphs[i].kern_table_offset);
        font_face->glyphs[i].path.draw_cmds =
            (float*)(buf_base +
                font_face->glyphs[i].path.draw_cmds_offset);
       /* Try to get these paramters from Binary object or attributes */
       //vg_lite_format_t data_format = VG_LITE_FP32; //VG_LITE_S16;
       //vg_lite_quality_t quality = VG_LITE_HIGH;
    }
    VFT_DBG_GLYPH_TABLE(font_face, glyph_table_offset);

    VFT_DBG_KERN_TABLE(font_face, kern_table_offset);
    VFT_DBG_PATH_TABLE(font_face, path_data_offset);

    return font_face;
}

/* Find glyph of given character from glyph table */
glyph_desc_t* vft_find_glyph(font_face_desc_t* font_face, uint16_t ug2)
{
    const int num_glyphs = font_face->num_glyphs;
    glyph_desc_t* glyphs = font_face->glyphs;

    /*
    * Present approach is slow linear search, this is ok in 1st prototype
    * Since glyph table is already sorted, we can have binary search
    */
    for (int i = 0; i < num_glyphs; i++) {
        if (glyphs[i].unicode == ug2) {
            return (glyph_desc_t*)&glyphs[i];
        }
    }
    return (glyph_desc_t*)&glyphs[0];;
}

/* Find distance between 2 glyph symbols */
int vft_glyph_distance(glyph_desc_t* g1, glyph_desc_t* g2)
{
    signed short kx = 0;
    uint16_t ug2 = g2->unicode;
    kern_desc_t* kern_table = &g1->kern_table[0];

    for (int i = 0; i < g1->kern_num_entries; i++) {
        if (kern_table[i].unicode == ug2) {
            signed short *pkx = (signed short *)&kern_table[i].kern;
            kx = *pkx;
            break;
        }
    }

    return kx;
}

/*
* Get internal vector path of given glyph
* This is internal function
*/
path_desc_t* vft_get_glyph_path(glyph_desc_t* g2)
{
    return &g2->path;
}

/* Unload font face descriptor and all glyphs */
void vft_unload(font_face_desc_t* font_face)
{
    glyph_cache_free();
    //VFT_FREE(font_face);
}
