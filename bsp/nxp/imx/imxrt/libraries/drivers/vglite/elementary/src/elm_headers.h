/****************************************************************************
*
*    Copyright 2021 Vivante Corporation, Santa Clara, California.
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

#ifndef __ELM_HEADERS_H__
#define __ELM_HEADERS_H__


#define ATTR_PACKED __attribute__((packed, aligned(4)))


typedef struct {
    vg_lite_matrix_t          matrix;
    uint32_t                  reserved;
    uint32_t                  stop_count;
    uint32_t                  stop_offset;
    uint32_t                  color_offset;
} el_EVO_GradData;

typedef struct {
    vg_lite_radial_gradient_parameter_t params;
    vg_lite_radial_gradient_spreadmode_t spread_mode;
} el_EVO_RadGradDataExt;

struct el_PaintType_t {
    uint32_t                  paint:28;
    uint32_t                  flags:1;
    uint32_t                  is_image:1;
    uint32_t                  is_pattern:1;
    uint32_t                  has_pattern:1;
};

typedef struct ATTR_PACKED {
    uint32_t                  type;
    vg_lite_float_t           min_x, min_y, max_x, max_y;
    uint32_t                  format;
    uint32_t                  length:31;
    uint32_t                  arc_flag:1;
    uint32_t                  offset;
    vg_lite_matrix_t          matrix;
    uint32_t                  reserved;
    uint32_t                  quality;
    uint32_t                  fill_rule;
    uint32_t                  blend;
    union {
        uint32_t              paint_data;
        struct el_PaintType_t paint_type;
    };
    vg_lite_color_t           color;
    el_EVO_GradData           grad;
} el_EVO_Polygon;

typedef struct ATTR_PACKED {
    uint32_t                  type;
    uint32_t                  namelength;
    char                      eboname[76];
    union {
        uint32_t              paint_data;
        struct el_PaintType_t paint_type;
    };
    vg_lite_matrix_t          matrix;
    uint32_t                  width;
    uint32_t                  height;
} el_EVO_Image;

typedef struct ATTR_PACKED {
    union {
        el_EVO_Polygon        polygon;
        el_EVO_Image          image;
    };
} el_EVO_Header;

typedef struct ATTR_PACKED {
    uint32_t                  type;
    uint32_t                  size_font_block;
    uint32_t                  num_ttf_fonts;
    uint32_t                  num_vector_fonts;
    uint32_t                  num_text_fonts;
    uint32_t                  ttf_fonts_block_offset;
    uint32_t                  ttf_fonts_block_length;
    uint32_t                  vector_fonts_block_offset;
    uint32_t                  vector_fonts_block_length;
    uint32_t                  text_fonts_block_offset;
    uint32_t                  text_fonts_block_length;
    uint32_t                  property_block_offset;
    uint32_t                  property_block_length;
} el_Font_Header;

struct el_TextFlags_t {
    uint32_t                  flags1:1;
    uint32_t                  text_anchor:2;
    uint32_t                  flags2:29;
};

typedef struct ATTR_PACKED {
    uint32_t                  type;
    uint32_t                  size_text_block;
    uint32_t                  tspan_has_dx_dy;
    float                     x_pos;
    float                     y_pos;
    float                     font_size;
    uint32_t                  font_id;
    uint32_t                  color;
    union {
        uint32_t              flags_data;
        struct el_TextFlags_t text_flags;
    };
    vg_lite_matrix_t          matrix;
    uint32_t                  reserved;
    uint16_t                  data_length;
} el_Text_Header;

typedef struct ATTR_PACKED {
    uint32_t                  type;
    uint32_t                  width;
    uint32_t                  height;
    uint32_t                  stride;
    uint32_t                  tiled;
    uint32_t                  format;
    uint32_t                  data_offset;
} el_EBO_Header;

typedef struct ATTR_PACKED {
    uint32_t                  clut_count;
    uint32_t                  clut_data_offset;
} el_EBO_Palette;

typedef struct ATTR_PACKED {
    uint32_t                  type;
    vg_lite_matrix_t          matrix;
    uint32_t                  count;
} el_EGO_Header;


#endif /* __ELM_HEADERS_H__ */
