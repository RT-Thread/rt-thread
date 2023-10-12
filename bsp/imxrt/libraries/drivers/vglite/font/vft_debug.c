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
#include "vg_lite_text.h"
#include "vft_draw.h"
#include "vft_debug.h"

#ifdef ENABLE_DEBUG_TRACE

/** Macros */

/** Data structures */
typedef enum path_type {
    PATH_DONE,
    PATH_CLOSE,
    MOVE_TO,
    MOVE_TO_REL,
    LINE_TO,
    LINE_TO_REL,
    QUAD_TO,
    QUAD_TO_REL,
    CUBI_TO,
    CUBI_TO_REL,
    NUM_PATH_CMD
} path_type_t;

/** Internal or external API prototypes */

/** Globals */
static const int data_count[] =
{
    0,
    0,
    2,
    2,
    2,
    2,
    4,
    4,
    6,
    6
};

static char s_cmd_name[][16] =
{
    {"PATH_DONE" },
    {"PATH_CLOSE" },
    {"MOVE_TO" },
    {"MOVE_TO_REL" },
    {"LINE_TO" },
    {"LINE_TO_REL" },
    {"QUAD_TO" },
    {"QUAD_TO_REL" },
    {"CUBI_TO" },
    {"CUBI_TO_REL" },
    {"NUM_PATH_CMD"},
};


/** Externs if any */

/** Code section */
void vfg_dbg_path_data(path_desc_t* path_data_desc, int offset)
{
    float* draw_cmds;

    draw_cmds = &path_data_desc->draw_cmds[0];

    for (int i = 0; i < path_data_desc->num_draw_cmds; i++) {
        uint32_t cmd, j;

        cmd = *((uint32_t*)(&draw_cmds[i]));
        if (cmd < NUM_PATH_CMD) {
            TRACE_BIN(("BIN:   %08x: %s(%d) [",
                offset + i * 4,
                s_cmd_name[cmd], cmd));
            for (j = 0; j < data_count[cmd]; j++) {
                TRACE_BIN((" %.2f", draw_cmds[i + j + 1]));
            }
            i += j;
            TRACE_BIN(("]\n"));
        }
    }
}

void vft_dbg_path(char *prefix, void *draw_cmds_args, int num_draw_cmds)
{
    float* draw_cmds;

    draw_cmds = draw_cmds_args;
    int offset = 0;
    for (int i = 0; i < num_draw_cmds; i++) {
        uint32_t cmd, j;

        cmd = *((uint32_t*)(&draw_cmds[i]));
        if (cmd < NUM_PATH_CMD) {
            printf("BIN:   %08x: %s(%d) [",
                offset + i * 4,
                s_cmd_name[cmd], cmd);
            for (j = 0; j < data_count[cmd]; j++) {
                printf(" %.2f", draw_cmds[i + j + 1]);
            }
            i += j;
            printf("]\n");
        }
    }
}

void vft_dbg_path_bounds(char *name, float *ary, int num_elements)
{
    float* array_data;

    array_data = ary;
    printf("%s [",name);
    for (int i = 0; i < num_elements; i++) {
         printf(" %.2f", array_data[i]);
    }
    printf("]\n");
}

void vft_dbg_kern_desc(kern_desc_t* kern_desc, int num_kern_entries, int offset)
{
    for (int i = 0; i < num_kern_entries; i++) {
        TRACE_BIN(("BIN:   %08x: [%d] (u,k)=(%hu, %hu)\n",
            (int)(offset + i * sizeof(kern_desc_t)),
            i,
            kern_desc[i].unicode,
            kern_desc[i].kern));
    }
}
void vft_dbg_glyph_desc(glyph_desc_t* g, int offset)
{
    glyph_desc_t _desc = *g; /* Temporary copy descriptor*/

    TRACE_BIN_FIELD_UINT16(unicode);
    TRACE_BIN_FIELD_UINT16(horiz_adv_x);
    TRACE_BIN_FIELD_UINT32(kern_num_entries);
    TRACE_BIN_FIELD_UINT32(kern_table_offset);
    TRACE_BIN_FIELD_FLOAT(path.bounds[0]);
    TRACE_BIN_FIELD_FLOAT(path.bounds[1]);
    TRACE_BIN_FIELD_FLOAT(path.bounds[2]);
    TRACE_BIN_FIELD_FLOAT(path.bounds[3]);
    TRACE_BIN_FIELD_UINT32(path.num_draw_cmds);
    TRACE_BIN_FIELD_UINT32(path.draw_cmds_offset);

}

/* TRACE values for debugging purpose */
void vft_dbg_font_face_desc(font_face_desc_t* font_face, int offset)
{
    font_face_desc_t _desc = *font_face; /* Temporary copy descriptor*/

    TRACE_INFO(("font-face-block\n"));

    TRACE_BIN_FIELD_STR(font_family_name); offset += sizeof(_desc.font_family_name);
    TRACE_BIN_FIELD_UINT16(units_per_em);
    TRACE_BIN_FIELD_UINT16(ascent);
    TRACE_BIN_FIELD_UINT16(descent);
    TRACE_BIN_FIELD_UINT16(vg_font);
    TRACE_BIN_FIELD_UINT32(num_glyphs);
}

void vft_dbg_matrix(char *name, vg_lite_matrix_t *mat)
{
   printf("%s\n",name);
   printf(" %0.3f %0.3f %0.3f\n",
             mat->m[0][0],mat->m[0][1],mat->m[0][2]);
   printf(" %0.3f %0.3f %0.3f\n",
             mat->m[1][0],mat->m[1][1],mat->m[1][2]);
   printf(" %0.3f %0.3f %0.3f\n",
             mat->m[2][0],mat->m[1][1],mat->m[2][2]);
}

void vft_dbg_path_table(font_face_desc_t* font_face, int offset)
{
    TRACE_INFO(("path-block\n"));
    for (uint32_t i = 0; i < font_face->num_glyphs; i++) {
        glyph_desc_t* g = &font_face->glyphs[i];
        TRACE_BIN(("Glyph - path: '%c' unicode = %d\n", g->unicode, g->unicode));
        offset = g->path.draw_cmds_offset;
        vfg_dbg_path_data(&g->path, offset);
    }
}

void vft_dbg_kern_table(font_face_desc_t* font_face, int offset)
{
    TRACE_INFO(("kern-block\n"));
    for (uint32_t i = 0; i < font_face->num_glyphs; i++) {
        glyph_desc_t* g = &font_face->glyphs[i];

        TRACE_INFO(("Kern: '%c' unicode=%hu\n", g->unicode, g->unicode));

        vft_dbg_kern_desc(&g->kern_table[0],
            g->kern_num_entries,
            offset);
        offset += (g->kern_num_entries * sizeof(kern_desc_t));
    }
}

void vft_dbg_glyph_table(font_face_desc_t* font_face, int offset)
{
    TRACE_INFO(("glyph-block\n"));
    for (uint32_t i = 0; i < font_face->num_glyphs; i++) {
        glyph_desc_t* g = &font_face->glyphs[i];
        TRACE_INFO(("Glyph: '%c'\n", g->unicode));
        vft_dbg_glyph_desc(g, offset);
        offset += sizeof(glyph_desc_t);
    }
}

int g_offset = 0;

void dbg_float_ary(char *name, float *ary, int count, int *disk_offset)
{
    int i;
    int offset = *disk_offset;
    for (i=0; i<count; i++) {
        DBG_TRACE(("DBG:  %s[%d]=%f offset=%d\n", \
            name, \
            i, \
            ary[i], offset));
        offset+= 4;
    }
    *disk_offset = offset;
}

void dbg_int_ary(char *name, uint32_t *ary, int count, int *disk_offset)
{
    int i;
    int offset = *disk_offset;
    for (i=0; i<count; i++) {
        DBG_TRACE(("DBG:  %s[%d]=%d offset=%d\n", \
            name, \
            i, \
            ary[i], offset));
        offset+= 4;
    }
    *disk_offset = offset;
}

void dbg_int_param(char *name, uint32_t value, int *disk_offset)
{
    int offset = *disk_offset;
    DBG_TRACE(("DBG:  %s=%d offset=%d\n", \
        name, \
        value, offset));
    offset+= 4;
    *disk_offset = offset;
}

void dbg_float_ary_no_offset_update(char *name, float *ary,
                                    int count, int disk_offset)
{
    int i;
    int offset = disk_offset;
    for (i=0; i<count; i++) {
        DBG_TRACE(("DBG:  %s[%d]=%f offset=%d\n", \
            name, \
            i, \
            ary[i], offset));
        offset+= 4;
    }
}

void dbg_int_ary_no_offset_update(char *name, uint32_t *ary,
                                  int count, int disk_offset)
{
    int i;
    int offset = disk_offset;
    for (i=0; i<count; i++) {
        DBG_TRACE(("DBG:  %s[%d]=%d offset=%d\n", \
            name, \
            i, \
            ary[i], offset));
        offset+= 4;
    }
}

void dbg_int_param_no_offset_update(char *name, uint32_t value, int disk_offset)
{
    int offset = disk_offset;
    DBG_TRACE(("DBG:  %s=%d offset=%d\n", \
        name, \
        value, offset));
    offset+= 4;
}

#endif
