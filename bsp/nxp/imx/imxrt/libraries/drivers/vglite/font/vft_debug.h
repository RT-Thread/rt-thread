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

//#define ENABLE_DEBUG_TRACE

#ifdef ENABLE_DEBUG_TRACE
/* With debug configuration */

/* Macros */
#define TRACE_DBG(x) printf x
#define TRACE_BIN(x) // printf x  /* Tracer for binary layout */
#define TRACE_WRN(x) printf x
#define TRACE_INFO(x) printf x
#define TRACE_ERR(x) printf x
#define DBG_ARY(obj, param, count) \
  dbg_float_ary(#param, &obj->param[0], count, &g_offset);

#define DBG_INT_ARY(obj, param, count) \
  dbg_int_ary(#param, obj->param, count, &g_offset);

#define DBG_FIELD(obj, param) \
  dbg_int_param(#param, obj->param, &g_offset)

#define DBG_READ_32B(name, value, offset) \
    dbg_int_param_no_offset_update(name, value, offset)
extern int g_offset;

#define VFT_DBG_FONT_FACE_DESC(a,b) vft_dbg_font_face_desc(a,b)
#define VFT_DBG_GLYPH_TABLE(a,b) vft_dbg_glyph_table(a,b)
#define VFT_DBG_KERN_TABLE(a,b)  vft_dbg_kern_table(a,b)
#define VFT_DBG_PATH_TABLE(a,b)  vft_dbg_path_table(a,b)

static int g_offset = 0; /* Dummy just to solve build errors */
#define DBG_TRACE(x)
#define DBG_INC_OFFSET(x)  g_offset += (x);
#define DBG_OFFSET()  (g_offset)

/* Prorotypes */
void vft_dbg_font_face_desc(font_face_desc_t* font_face, int offset);
void vft_dbg_glyph_desc(glyph_desc_t* g, int offset);
void vft_dbg_kern_desc(kern_desc_t* kern_desc, int num_kern_entries, int offset);
void vfg_dbg_path_data(path_desc_t* path_data_desc, int offset);
void vft_dbg_matrix(char *name, vg_lite_matrix_t *mat);
void vft_dbg_path_table(font_face_desc_t* font_face, int offset);
void vft_dbg_kern_table(font_face_desc_t* font_face, int offset);
void vft_dbg_glyph_table(font_face_desc_t* font_face, int offset);

void dbg_float_ary_no_offset_update(char *name, float *ary,
                                    int count, int disk_offset);
void dbg_int_ary_no_offset_update(char *name, uint32_t *ary,
                                  int count, int disk_offset);
void dbg_int_param_no_offset_update(char *name, uint32_t value, int disk_offset);

#else
/** Without -debug configuration */
/* Macros */
#define TRACE_DBG(x)
#define TRACE_BIN(x)
#define TRACE_WRN(x) printf x
#define TRACE_INFO(x)
#define TRACE_ERR(x) printf x

#define DBG_READ_32B(a,b,c)
#define DBG_TRACE(x)
#define vft_dbg_glyph_desc(g,offset)
#define dbg_float_ary_no_offset_update(a, b, c,d)
#define dbg_int_ary_no_offset_update(a, b, c,d)
#define vft_dbg_path_bounds(a,b,c)
#define vft_dbg_path(a,b,c)

#define VFT_DBG_FONT_FACE_DESC(a,b)
#define VFT_DBG_GLYPH_TABLE(a,b)
#define VFT_DBG_KERN_TABLE(a,b)
#define VFT_DBG_PATH_TABLE(a,b)

#define DBG_INC_OFFSET(x)
#define DBG_OFFSET()  (0)

#endif

#define TRACE_BIN_FIELD_STR(x) TRACE_BIN(("BIN:   %08x: "#x"=%s\n",offset,_desc.x));
#define TRACE_BIN_FIELD_UINT16(x) TRACE_BIN(("BIN:   %08x: "#x"=%hu\n",offset,_desc.x)); offset += 2;
#define TRACE_BIN_FIELD_UINT32(x) TRACE_BIN(("BIN:   %08x: "#x"=%u\n",offset,_desc.x)); offset += 4;
#define TRACE_BIN_FIELD_FLOAT(x) TRACE_BIN(("BIN:   %08x: "#x"=%f\n",offset,_desc.x)); offset += 4;

