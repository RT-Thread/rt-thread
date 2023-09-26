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
#include "Elm.h"
#include "velm.h"

#ifndef _elm_text_h_
#define _elm_text_h_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum eElemType {
    eElemTypeLinearGradient         = 0,
    eElemTypePath                   = 1,
    eElemTypeGroup                  = 2,
    eElemTypeText                   = 3,
    eElemTypeTspan                  = 4,
    eElemTypeFont                   = 5,
    eElemTypeTtfFont                = 6,
    eElemTypeVectorFont             = 7,
    eElemTypeTextFont               = 8,
} eElemType_t;

typedef enum eFontVariant {
    eFontVariantNormal      = 1,
    eFontVariantSmallCaps   = 2,
    eFontVariantInherit     = 3,
} eFontVariant_t;

typedef enum eDisplayAlign {
    eDisplayAlignBefore     = 1,
    eDisplayAlignCenter     = 2,
    eDisplayAlignAfter      = 3,
    eDisplayAlignAuto       = 1,
} eDisplayAlign_t;

typedef enum eFontFields {
    HORIZ_ADV_X         = 0,
    HORIZ_ORIGIN_X      = 1,
    ASCENT              = 2,
    ALPHABETIC          = 3,
    BBOX                = 4,
    CAP_HEIGHT          = 5,
    DESCENT             = 6,
    FONT_FAMILY         = 7,
    FONT_SIZE           = 8,
    FONT_STRETCH        = 9,
    FONT_STYLE          = 10,
    FONT_TYPE           = 11,
    FONT_VARIANT        = 12,
    FONT_WEIGHT         = 13,
    SLOPE               = 14,
    UNICODE_RANGE       = 15,
    UNITS_PER_EM        = 16,
    X_HEIGHT            = 17,
    TEXT_ANCHOR         = 18,
    MAX_FONT_ATTRIBUTES = 19,
} eFontFields_t;

typedef struct glyph {
    uint8_t     glyph_name;
    uint8_t     unicode;
    uint32_t    horiz_adv_x;
    uint32_t    path_data_length;
    void        *path_data;
} glyph_t;

typedef struct glyph_table {
    uint32_t    offset;
    uint32_t    size;
} glyph_table_t;

typedef union value_type {
    uint32_t    i_value;
    float       f_value;
    char       *data;
} value_type_t;

typedef struct font_field_info {
    value_type_t    value;
    eFontFields_t   eName;
} font_field_info_t;

typedef struct font_fields {
    font_field_info_t   info;
    uint32_t            offset;
    uint32_t            size;
    unsigned char       *data;
} font_fields_t;

typedef struct vector_font {
    uint32_t        id;
    eElemType_t     type;
    uint32_t        num_fields;
    font_fields_t   *fields;
    glyph_table_t   *glyph_table;
    glyph_t         *glyph_offset;
} vector_font_t;

typedef struct ttf_font {
    uint32_t        id;
    eElemType_t     type;
    uint32_t        num_fields;
    font_fields_t   *fields;
} ttf_font_t;

typedef struct font_prop {
    uint32_t        num_props;
    font_fields_t   *prop_values;
} font_prop_t;

typedef struct font_block {
    uint32_t        size;
    eElemType_t     type;
    uint32_t        num_ttf_fonts;
    uint32_t        num_vector_fonts;
    uint32_t        num_text_fonts;
    uint32_t        ttf_fonts_block_offset;
    uint32_t        ttf_fonts_block_length;
    uint32_t        vector_fonts_block_offset;
    uint32_t        vector_fonts_block_length;
    uint32_t        text_fonts_block_offset;
    uint32_t        text_fonts_block_length;
    uint32_t        property_block_offset;
    uint32_t        property_block_length;
    font_prop_t     *font_prop;
    unsigned int    *sizes_of_ttf_data;
    unsigned int    *offsets_of_ttf_data;
    ttf_font_t      *ttf_fonts;
    unsigned int    *sizes_of_vector_data;
    unsigned int    *offsets_of_vector_data;
    vector_font_t   *vector_fonts;
    unsigned int    *sizes_of_text_font_data;
    unsigned int    *offsets_of_text_font_data;
    ttf_font_t      *text_fonts;
} font_block_t;

typedef struct {
    el_Object           object;
    el_Attribute        attribute;
    el_Attribute        defaultAttrib;
    uint32_t            tspan_has_dx_dy;
    uint32_t            text_anchor;
    uint32_t            font_size;
    uint32_t            font_id;
    uint32_t            x_pos;
    uint32_t            y_pos;
    unsigned char       *msg;
} el_Obj_TEXT;

typedef enum eAppProperties {
  eFontNameProperty,
  eFontHeightProperty,
  eFontWeightProperty,
  eFontStretchProperty,
  eFontStyleProperty,
  eTextColorProperty,
  eTextAlignProperty,
  eMaxFontProperties,
} eAppProperties_t;

vg_lite_error_t draw_text(el_Obj_Buffer *buff,
                                 el_Obj_EVO *evo, vg_lite_matrix_t *mat);

extern font_block_t *fontblockobj;

int _load_font_data(uint8_t *data);

ElmHandle _load_text_data(uint8_t *data, el_Obj_EVO *evo);
void _unload_text(el_Obj_EVO *evo);
void _init_transform(el_Transform *transform);
void initialize_elm_text(void);
void destroy_font_data();
void _release_default_text_parameters(void);

#ifdef __cplusplus
}
#endif

#endif /* _elm_text_h_ */
