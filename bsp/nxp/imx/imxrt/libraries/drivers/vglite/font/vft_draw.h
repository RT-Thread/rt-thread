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

#ifndef _VFT_DRAW_H
#define _VFT_DRAW_H

#include <stdint.h>

typedef enum eFontBlkType {
    eUnkBlock,
    eFontFaceDesc,
    eGlyphTableDesc,
    eKernTableDesc,
    eGlyphData,
    eMaxBlock
}eFontBlock_t;

static const int32_t BLK_HDR_SIZE = 4;

typedef struct path_descriptor {
    float bounds[4];
    uint32_t num_draw_cmds;
    uint32_t draw_cmds_offset;
    float* draw_cmds;  /* NOTE: this will be used while loading table, DONT REMOVE */
}path_desc_t;

typedef struct kern_desc {
    uint16_t unicode;
    uint16_t kern;
}kern_desc_t;

typedef struct glyph_descriptor {
    uint16_t unicode; /* unicode name */
    uint16_t horiz_adv_x; /* Short to align to 32-bit boundry */
    uint32_t kern_num_entries;
    uint32_t kern_table_offset;
    kern_desc_t* kern_table;  /* NOTE: this will be used while loading table, DONT REMOVE */
    path_desc_t path;
}glyph_desc_t;

typedef struct font_face_info {
    int8_t font_family_name[64];
    uint16_t units_per_em;
    uint16_t ascent;
    uint16_t descent;
    uint16_t vg_font;
    uint32_t num_glyphs;
    glyph_desc_t* glyphs; /* NOTE: this will be used while loading table, DONT REMOVE */
}font_face_desc_t;

//NOTE: No glyph caching at this time

/* Load vector font ROM table from file */
font_face_desc_t* vft_load(char* vcft_file_path);

/* Find glyph of given character from glyph table */
glyph_desc_t* vft_find_glyph(font_face_desc_t* font_face, uint16_t ug2);

/* Find distance between 2 glyph symbols */
int vft_glyph_distance(glyph_desc_t* g1, glyph_desc_t* g2);

/*
* Get internal vector path of given glyph
* This is internal function
*/
path_desc_t* vft_get_glyph_path(glyph_desc_t* g2);

/* Draw vector font based glyph on given x,y co-ordinate */
void vft_draw_glyph(int x, int y, glyph_desc_t* g2);

/* Compute horizotal pixels coverted by this path */
int vft_compute_dx(glyph_desc_t* g2);

/* Unload font face descriptor and all glyphs */
void vft_unload(font_face_desc_t*);

/* Draw string with vector font s*/
int vg_lite_vtf_draw_text(vg_lite_buffer_t *rt, int x, int y,
                      vg_lite_blend_t blend,
                      vg_lite_font_t font,
                      vg_lite_matrix_t *matrix,
                      vg_lite_font_attributes_t  * attributes,
                      char *text);

/* Internal memory allocator API */
void *_mem_allocate(int size);
void _mem_free(void *buf);

vg_lite_error_t vg_lite_load_font_data(vg_lite_font_t font, int font_height);
font_face_desc_t* vft_load_from_buffer(char* buf_base, int file_size);
void vg_lite_unload_font_data(void);

#endif //!_VFT_DRAW_H
