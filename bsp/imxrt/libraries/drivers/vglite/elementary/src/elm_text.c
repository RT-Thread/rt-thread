/****************************************************************************
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

/*
  ElmDrawText API
 */
/** Include Files */
#include <stdio.h> // for snprintf
#include <stdlib.h>
#include <string.h>

#include "vg_lite.h"
#include "Elm.h"
#include "velm.h"
#include "vg_lite_text.h"
#include "elm_headers.h"
#include "elm_text.h"
#include "elm_precom.h"
#include "vft_draw.h"

/** Macros */
#ifndef VECTOR_DEFAULT_FONT
#define VECTOR_DEFAULT_FONT 1
#endif

#if VECTOR_DEFAULT_FONT /* Use vector font as default font */
#define DEFAULT_FONT_NAME    "SVGFreeSansASCII"
#define DEFAULT_FONT_WEIGHT  eFontWeightRegular
#define DEFAULT_FONT_STRETCH eFontStretchNormal
#define DEFAULT_FONT_STYLE   eFontStyleNormal
#define DEFAULT_FONT_HEIGHT  35
#define DEFAULT_TEXT_FG_COLOR   0xff000000
#define DEFAULT_TEXT_ALIGN  (eTextAlignLeft)

#else /* Use raster font as default font */
#define DEFAULT_FONT_NAME    "DejaVuSans_Oblique"
#define DEFAULT_FONT_WEIGHT  eFontWeightRegular
#define DEFAULT_FONT_STRETCH eFontStretchNormal
#define DEFAULT_FONT_STYLE   eFontStyleItalic
#define DEFAULT_FONT_HEIGHT  35
#define DEFAULT_TEXT_FG_COLOR   0xff000000
#define DEFAULT_TEXT_ALIGN  (eTextAlignLeft)

#endif

/* Maximum font properties from EVO file */
#define MAX_FONT_ATTRIB_COMBINATIONS (32)

#define TRANSPARENT_VGLITE_COLOUR(a, r, g, b) \
    ((uint32_t)(a) << 24) | ((uint32_t)(b) << 16) | ((uint32_t)(g) << 8) | \
    (uint32_t)r

#define OPAQUE_VGLITE_COLOUR(r, g, b)   TRANSPARENT_VGLITE_COLOUR(0xff, r, g, b)

/** Data structures */

/** Internal or external API prototypes */
int vg_lite_is_font_valid(vg_lite_font_t font);
char *vg_lite_get_font_name(vg_lite_font_t font);
vg_lite_error_t vg_lite_free_font_memory(vg_lite_font_t font);
int         ref_object      (el_Object     *object);

/** Globals */
int g_total_system_font = 0;
static font_field_info_t g_default_font_properties[eMaxFontProperties];
static font_field_info_t g_font_properties[MAX_FONT_ATTRIB_COMBINATIONS][eMaxFontProperties];

/** Externs if any */
extern vg_lite_font_attributes_t g_font_attribs;
extern vg_lite_font_t g_last_font;
extern int g_last_font_attrib_idx;

void initialize_elm_text(void)
{
    font_field_info_t *font_fields = NULL;
    /* internal parameters of mcufont library */
    g_font_attribs.alignment = 0;
    g_font_attribs.scale = 1;
    g_font_attribs.width = 1200; /* Describes drawing area */
    g_font_attribs.margin = 5; /* Left margin in drawing area */
    g_font_attribs.bg_color = OPAQUE_VGLITE_COLOUR(0xff,0xff,0xff); // white
    g_font_attribs.last_y = 0;
    g_font_attribs.last_x =0;
    g_font_attribs.last_dx = 0;

    /* Initialize default properties */
    font_fields = &g_default_font_properties[0];

    char *font_name = (char *)elm_alloc(1, strlen(DEFAULT_FONT_NAME)+1);
    strcpy(font_name, DEFAULT_FONT_NAME);
    font_fields[eFontNameProperty].value.data = font_name;
    font_fields[eFontWeightProperty].value.i_value = DEFAULT_FONT_WEIGHT;
    font_fields[eFontStretchProperty].value.i_value = DEFAULT_FONT_STRETCH;
    font_fields[eFontStyleProperty].value.i_value = DEFAULT_FONT_STYLE;
    font_fields[eFontHeightProperty].value.i_value = DEFAULT_FONT_HEIGHT;
    font_fields[eTextColorProperty].value.i_value = DEFAULT_TEXT_FG_COLOR;
    font_fields[eTextAlignProperty].value.i_value = DEFAULT_TEXT_ALIGN;
}

static int get_property(font_field_info_t *dst_font_fields, font_fields_t *src_font_fields, int num_fields)
{
    int i=0;
    int len;

    /* Initialize default values */
    dst_font_fields[eFontWeightProperty].value.i_value = DEFAULT_FONT_WEIGHT;
    dst_font_fields[eFontStretchProperty].value.i_value = DEFAULT_FONT_STRETCH;
    dst_font_fields[eFontStyleProperty].value.i_value = eFontStyleNormal;
    dst_font_fields[eTextAlignProperty].value.i_value = DEFAULT_TEXT_ALIGN;

    dst_font_fields[eFontNameProperty].value.data = NULL;
    dst_font_fields[eFontHeightProperty].value.i_value = DEFAULT_FONT_HEIGHT;
    dst_font_fields[eTextColorProperty].value.i_value = DEFAULT_TEXT_FG_COLOR;

    for(i=0; i<num_fields; i++)
    {
        if(src_font_fields[i].info.eName == FONT_FAMILY ||
           src_font_fields[i].info.eName == FONT_WEIGHT ||
           src_font_fields[i].info.eName == FONT_STRETCH ||
           src_font_fields[i].info.eName == FONT_STYLE ||
           src_font_fields[i].info.eName == TEXT_ANCHOR )
        {
            switch(src_font_fields[i].info.eName)
            {
                case FONT_FAMILY:
                    len = strlen((char *)src_font_fields[i].data);
                    dst_font_fields[eFontNameProperty].eName = FONT_FAMILY;
                    dst_font_fields[eFontNameProperty].value.data =
                        (char *)elm_alloc(1, len+1);
                    strcpy(dst_font_fields[eFontNameProperty].value.data,
                         (char *)src_font_fields[i].data);
                    dst_font_fields[eFontNameProperty].value.data[len] = '\0';
                    break;
                case FONT_WEIGHT:
                    dst_font_fields[eFontWeightProperty].eName = FONT_WEIGHT;
                    dst_font_fields[eFontWeightProperty].value.i_value =
                        (eFontWeight_t)src_font_fields[i].info.value.i_value;
                    break;
                case FONT_STRETCH:
                    dst_font_fields[eFontStretchProperty].eName = FONT_STRETCH;
                    dst_font_fields[eFontStretchProperty].value.i_value =
                      (eFontStretch_t)src_font_fields[i].info.value.i_value;
                    break;
                case FONT_STYLE:
                    dst_font_fields[eFontStyleProperty].eName = FONT_STYLE;
                    dst_font_fields[eFontStyleProperty].value.i_value =
                        (eFontStyle_t)src_font_fields[i].info.value.i_value;
                    break;
                case TEXT_ANCHOR:
                    dst_font_fields[eTextAlignProperty].eName = TEXT_ANCHOR;
                    dst_font_fields[eTextAlignProperty].value.i_value =
                        (eTextAlign_t)src_font_fields[i].info.value.i_value;
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}

vg_lite_error_t draw_text(el_Obj_Buffer *buff,
                                 el_Obj_EVO *evo, vg_lite_matrix_t *mat)
{
    vg_lite_error_t error = VG_LITE_INVALID_ARGUMENT;
    el_Obj_TEXT *text = (el_Obj_TEXT *)evo;
    vg_lite_blend_t blend = (vg_lite_blend_t)text->attribute.blend;
    vg_lite_font_t curr_font = VG_LITE_INVALID_FONT;
    int curr_font_attrib_idx = INVALID_FONT_PROPERTY_IDX;

    vg_lite_font_attributes_t *font_attribs = &g_font_attribs;
    font_field_info_t *font_fields = NULL;

    curr_font_attrib_idx = text->font_id;

    /* Single font caching can be done here (No caching for now)
       Release last font object if it is different
     */
    if ( vg_lite_is_font_valid(g_last_font) == 1 ) {
      /* recycle font objects */
      vg_lite_free_font_memory(g_last_font);
      g_last_font = VG_LITE_INVALID_FONT;
    }

    if(curr_font_attrib_idx != INVALID_FONT_PROPERTY_IDX)
    {
        font_fields = &g_font_properties[curr_font_attrib_idx][0];
        font_fields[eFontHeightProperty].value.i_value = text->font_size;

        curr_font = vg_lite_find_font(
            font_fields[eFontNameProperty].value.data,
            (eFontWeight_t)font_fields[eFontWeightProperty].value.i_value,
            (eFontStretch_t)font_fields[eFontStretchProperty].value.i_value,
            (eFontStyle_t)font_fields[eFontStyleProperty].value.i_value,
            font_fields[eFontHeightProperty].value.i_value
            );
    }

    if (curr_font == VG_LITE_INVALID_FONT) {
        //printf("ERROR: Font not found. Rendering with default configuration\n");
        font_fields = &g_default_font_properties[0];
            curr_font = vg_lite_find_font(
                font_fields[eFontNameProperty].value.data,
                (eFontWeight_t)font_fields[eFontWeightProperty].value.i_value,
                (eFontStretch_t)font_fields[eFontStretchProperty].value.i_value,
                (eFontStyle_t)font_fields[eFontStyleProperty].value.i_value,
                font_fields[eFontHeightProperty].value.i_value);
    }
    if (curr_font == VG_LITE_INVALID_FONT) {
        printf("Font[%s] not found\n", font_fields[eFontNameProperty].value.data);
        return VG_LITE_INVALID_ARGUMENT;
    }
    font_attribs->is_vector_font = vg_lite_is_vector_font(curr_font);
    /* Properties that changes over time */
    font_attribs->text_color = text->attribute.paint.color;
    font_attribs->alignment = (eTextAlign_t)text->text_anchor;
    font_attribs->font_height = font_fields[eFontHeightProperty].value.i_value;
    font_attribs->tspan_has_dx_dy = text->tspan_has_dx_dy;

    error = vg_lite_draw_text(&buff->buffer,
               (char *)text->msg,
               curr_font,
               text->x_pos, text->y_pos,
               &text->attribute.transform.matrix,
               blend,
               font_attribs);

    g_last_font = curr_font;
    g_last_font_attrib_idx = curr_font_attrib_idx;
    return error;
}

/* process font-field data */
static int _process_font_field_data( uint8_t *data_start, uint8_t *data, int num_fields, font_fields_t* fields)
{
    eFontFields_t eName;

    if (g_total_system_font >= MAX_FONT_ATTRIB_COMBINATIONS) {
      printf("WARNING: Font property buffer overflowing...\n"
             "Increase MAX_FONT_ATTRIB_COMBINATIONS\n");
      return -1;
    }

    for(int i=0; i<num_fields; i++)
    {
        fields[i].info.eName = (eFontFields_t)*(uint32_t *)(data + (0 + 3*i) * 4);
        fields[i].offset = *(uint32_t *)(data + (1 + 3*i)* 4);
        fields[i].data = NULL;
        eName = fields[i].info.eName;
        if(eName == FONT_SIZE ||
           eName == HORIZ_ORIGIN_X ||
           eName == HORIZ_ADV_X ||
           eName == ASCENT ||
           eName == ALPHABETIC ||
           eName == CAP_HEIGHT ||
           eName == DESCENT ||
           eName == SLOPE ||
           eName == UNITS_PER_EM ||
           eName == X_HEIGHT
            )
        {
            fields[i].info.value.f_value = *(float *)(data + (2 + 3*i)* 4);
        }
        else
        {
            fields[i].info.value.i_value = *(uint32_t *)(data + (2 + 3*i)* 4);
        }

        if(fields[i].offset != 0)
        {
            fields[i].size = *(uint16_t *)(data_start + fields[i].offset);
            fields[i].data = (uint8_t *)elm_alloc(1, fields[i].size+1);
            memset(fields[i].data,0, fields[i].size+1);
            memcpy(fields[i].data, (void *)(data_start + fields[i].offset + 2), fields[i].size);
        }
    }

    memset(&g_font_properties[g_total_system_font][0], 0,
           sizeof(font_fields_t)*eMaxFontProperties);
    get_property(g_font_properties[g_total_system_font], fields, num_fields);
    g_total_system_font++;

    return 0;
}

/* process ttf-type font data */
static int _process_ttf_font_data(uint8_t *data_start, uint8_t *void_data, font_block_t *fontblockobj, int id)
{
    unsigned int num_fields;
    uint8_t * data = (uint8_t *) void_data;

    fontblockobj->ttf_fonts[id].id = *(uint32_t *)(data);
    fontblockobj->ttf_fonts[id].type = (eElemType_t)*(uint32_t *)(data + 1 * 4);
    num_fields = *(uint32_t *)(data + 2 * 4);
    fontblockobj->ttf_fonts[id].num_fields = num_fields;
    fontblockobj->ttf_fonts[id].fields = (font_fields_t *)elm_alloc(1, num_fields * sizeof(font_fields_t));

    _process_font_field_data(data_start, (uint8_t*)(data + 3 * 4), num_fields, fontblockobj->ttf_fonts[id].fields);
    return 0;
}

/* process vector-type font data */
static int _process_vector_font_data(uint8_t *data_start, uint8_t *data, font_block_t *fontblockobj, int id)
{
    unsigned int num_fields = 0;

    fontblockobj->vector_fonts[id].id = *(uint32_t *)(data);
    fontblockobj->vector_fonts[id].type = (eElemType_t)*(uint32_t *)(data + 1 * 4);
    num_fields = *(uint32_t *)(data + 2 * 4);
    fontblockobj->vector_fonts[id].num_fields = num_fields;
    fontblockobj->vector_fonts[id].fields = (font_fields_t *)elm_alloc(1, num_fields * sizeof(font_fields_t));

    _process_font_field_data(data_start, (uint8_t*)(data + 3 * 4), num_fields, fontblockobj->vector_fonts[id].fields);

    return 0;
}

static int _process_text_font_data(uint8_t *data_start, uint8_t *void_data, font_block_t *fontblockobj, int id)
{
    unsigned int num_fields;
    uint8_t * data = (uint8_t *) void_data;

    fontblockobj->text_fonts[id].id = *(uint32_t *)(data);
    fontblockobj->text_fonts[id].type = (eElemType_t)*(uint32_t *)(data + 1 * 4);
    num_fields = *(uint32_t *)(data + 2 * 4);
    fontblockobj->text_fonts[id].num_fields = num_fields;
    fontblockobj->text_fonts[id].fields = (font_fields_t *)elm_alloc(1, num_fields * sizeof(font_fields_t));

    _process_font_field_data(data_start, (uint8_t*)(data + 3 * 4), num_fields, fontblockobj->text_fonts[id].fields);
    return 0;
}

static uint32_t *alloc_mem(uint32_t size)
{
    uint32_t *data = NULL;
    data = (uint32_t *)elm_alloc(1, size);
    JUMP_IF_NULL(data, error_exit);
#ifdef ENABLE_STRICT_DEBUG_MEMSET
    memset(data, 0, size);
#endif
    return data;
error_exit:
    return NULL;
}

font_block_t *fontblockobj = NULL;

/* load font-data */
int _load_font_data(uint8_t *data)
{
    el_Font_Header *font_header = (el_Font_Header *)data;

    if ( fontblockobj != NULL )
    {
        return -1;
    }

    fontblockobj = (font_block_t *)elm_alloc(1, sizeof(font_block_t));
    memset(fontblockobj, 0, sizeof(font_block_t));

    fontblockobj->size                          = font_header->size_font_block;
    fontblockobj->type                          = eElemTypeFont;
    fontblockobj->num_ttf_fonts                 = font_header->num_ttf_fonts;
    fontblockobj->num_vector_fonts              = font_header->num_vector_fonts;
    fontblockobj->num_text_fonts                = font_header->num_text_fonts;
    fontblockobj->ttf_fonts_block_offset        = font_header->ttf_fonts_block_offset;
    fontblockobj->ttf_fonts_block_length        = font_header->ttf_fonts_block_length;
    fontblockobj->vector_fonts_block_offset     = font_header->vector_fonts_block_offset;
    fontblockobj->vector_fonts_block_length     = font_header->vector_fonts_block_length;
    fontblockobj->text_fonts_block_offset       = font_header->text_fonts_block_offset;
    fontblockobj->text_fonts_block_length       = font_header->text_fonts_block_length;
    fontblockobj->property_block_offset         = font_header->property_block_offset;
    fontblockobj->property_block_length         = font_header->property_block_length;
#ifdef ENABLE_DEBUG_TRACE
    printf("size: %d(%0x)\n", fontblockobj->size, fontblockobj->size);
    printf("type: %d\n", fontblockobj->type);
    printf("num_ttf_fonts: %d\n", fontblockobj->num_ttf_fonts);
    printf("num_vector_fonts: %d\n", fontblockobj->num_vector_fonts);
    printf("num_text_fonts: %d\n", fontblockobj->num_text_fonts);
    printf("ttf_fonts_block_offset: %d(%0x)\n", fontblockobj->ttf_fonts_block_offset,
        fontblockobj->ttf_fonts_block_offset);
    printf("ttf_fonts_block_length: %d(%0x)\n", fontblockobj->ttf_fonts_block_length,
        fontblockobj->ttf_fonts_block_length);
    printf("vector_fonts_block_offset: %d(%0x)\n", fontblockobj->vector_fonts_block_offset,
        fontblockobj->vector_fonts_block_offset);
    printf("vector_fonts_block_length: %d(%0x)\n", fontblockobj->vector_fonts_block_length,
        fontblockobj->vector_fonts_block_length);
    printf("text_fonts_block_offset: %d(%0x)\n", fontblockobj->text_fonts_block_offset,
        fontblockobj->text_fonts_block_offset);
    printf("text_fonts_block_length: %d(%0x)\n", fontblockobj->text_fonts_block_length,
        fontblockobj->text_fonts_block_length);
    printf("property_block_offset: %d(%0x)\n", fontblockobj->property_block_offset,
        fontblockobj->property_block_offset);
    printf("property_block_length: %d(%0x)\n", fontblockobj->property_block_length,
        fontblockobj->property_block_length);
#endif

    g_total_system_font = 0;

    if ( fontblockobj->num_ttf_fonts > 0 ) {
        fontblockobj->sizes_of_ttf_data =
            (unsigned int *)alloc_mem(4 * fontblockobj->num_ttf_fonts);
        fontblockobj->offsets_of_ttf_data =
            (unsigned int *)alloc_mem(4 * fontblockobj->num_ttf_fonts);
        fontblockobj->ttf_fonts = NULL;
        fontblockobj->ttf_fonts = (ttf_font_t *)elm_alloc(1, fontblockobj->num_ttf_fonts * sizeof(ttf_font_t));
        JUMP_IF_NULL(fontblockobj->sizes_of_ttf_data, error_exit);
        JUMP_IF_NULL(fontblockobj->offsets_of_ttf_data, error_exit);
        JUMP_IF_NULL(fontblockobj->ttf_fonts, error_exit);

        memset(fontblockobj->ttf_fonts, 0, fontblockobj->num_ttf_fonts * sizeof(ttf_font_t));
        for(int i=0; i<fontblockobj->num_ttf_fonts; i++)
        {
            fontblockobj->sizes_of_ttf_data[i] = *(uint32_t *)(data + (i) * 4 + fontblockobj->ttf_fonts_block_offset);
            printf("ttf-DataSize: %d(%0x)\n", fontblockobj->sizes_of_ttf_data[i],
                fontblockobj->sizes_of_ttf_data[i]);
            fontblockobj->offsets_of_ttf_data[i] = *(uint32_t *)(data + (i + fontblockobj->num_ttf_fonts) * 4 + fontblockobj->ttf_fonts_block_offset);
            printf("ttf-offset: %d(%0x)\n", fontblockobj->offsets_of_ttf_data[i],
                fontblockobj->offsets_of_ttf_data[i]);

            if (fontblockobj->sizes_of_ttf_data[i] == 0)
            {
                continue;
            }

            _process_ttf_font_data(data, (uint8_t *)(data + fontblockobj->offsets_of_ttf_data[i]), fontblockobj, i);
        }
    }

    if ( fontblockobj->num_vector_fonts > 0 ) {
        fontblockobj->sizes_of_vector_data =
            (unsigned int *)alloc_mem(4 * fontblockobj->num_vector_fonts);
        fontblockobj->offsets_of_vector_data =
            (unsigned int *)alloc_mem(4 * fontblockobj->num_vector_fonts);
        fontblockobj->vector_fonts = NULL;
        fontblockobj->vector_fonts = (vector_font_t *)elm_alloc(1, fontblockobj->num_vector_fonts * sizeof(vector_font_t));
        JUMP_IF_NULL(fontblockobj->sizes_of_vector_data, error_exit);
        JUMP_IF_NULL(fontblockobj->offsets_of_vector_data, error_exit);
        JUMP_IF_NULL(fontblockobj->vector_fonts, error_exit);

        memset(fontblockobj->vector_fonts, 0, fontblockobj->num_vector_fonts * sizeof(vector_font_t));
        for(int i=0; i<fontblockobj->num_vector_fonts; i++)
        {
            fontblockobj->sizes_of_vector_data[i] = *(uint32_t *)(data + (i) * 4 + fontblockobj->vector_fonts_block_offset);
#ifdef ENABLE_DEBUG_TRACE
            printf("vector-DataSize: %d(%0x)\n", fontblockobj->sizes_of_vector_data[i],
                fontblockobj->sizes_of_vector_data[i]);
#endif
            fontblockobj->offsets_of_vector_data[i] = *(uint32_t *)(data + (i + fontblockobj->num_vector_fonts) * 4 + fontblockobj->vector_fonts_block_offset);
#ifdef ENABLE_DEBUG_TRACE
            printf("vector-offset: %d(%0x)\n", fontblockobj->offsets_of_vector_data[i],
                fontblockobj->offsets_of_vector_data[i]);
#endif

            if (fontblockobj->sizes_of_vector_data[i] == 0)
            {
                continue;
            }

            _process_vector_font_data(data, (uint8_t *)(data + fontblockobj->offsets_of_vector_data[i]), fontblockobj, i);
        }
    }

    if ( fontblockobj->num_text_fonts > 0 ) {
        fontblockobj->sizes_of_text_font_data =
          (unsigned int *)alloc_mem(4 * fontblockobj->num_text_fonts);
        fontblockobj->offsets_of_text_font_data =
          (unsigned int *)alloc_mem(4 * fontblockobj->num_text_fonts);
        fontblockobj->text_fonts = NULL;
        fontblockobj->text_fonts = (ttf_font_t *)elm_alloc(1, fontblockobj->num_text_fonts * sizeof(ttf_font_t));
        JUMP_IF_NULL(fontblockobj->sizes_of_text_font_data, error_exit);
        JUMP_IF_NULL(fontblockobj->offsets_of_text_font_data, error_exit);
        JUMP_IF_NULL(fontblockobj->text_fonts, error_exit);
        memset(fontblockobj->text_fonts, 0, fontblockobj->num_text_fonts * sizeof(ttf_font_t));
        for(int i=0; i<fontblockobj->num_text_fonts; i++)
        {
            fontblockobj->sizes_of_text_font_data[i] = *(uint32_t *)(data + (i) * 4 + fontblockobj->text_fonts_block_offset);
#ifdef ENABLE_DEBUG_TRACE
            printf("textfont-DataSize: %d(%0x)\n", fontblockobj->sizes_of_text_font_data[i],
                fontblockobj->sizes_of_text_font_data[i]);
#endif
            fontblockobj->offsets_of_text_font_data[i] = *(uint32_t *)(data + (i + fontblockobj->num_text_fonts) * 4 + fontblockobj->text_fonts_block_offset);
#ifdef ENABLE_DEBUG_TRACE
            printf("textfont-offset: %d(%0x)\n", fontblockobj->offsets_of_text_font_data[i],
                fontblockobj->offsets_of_text_font_data[i]);
#endif

            if (fontblockobj->sizes_of_text_font_data[i] == 0)
            {
                continue;
            }

            _process_text_font_data(data, (uint8_t *)(data + fontblockobj->offsets_of_text_font_data[i]), fontblockobj, i);
        }
    }

    return 0;

error_exit:
    destroy_font_data();

    return -1;
}

#if (defined(__ICCARM__))
/*
 * Disable the unaligned structure attribute warning. Due to the packed data
 * structures used to interpret ELM objects data the IAR compiler issues a
 * number of warnings that certain attributes of the headers might be unaligned.
 * This is not true, however, as all atributes are manually aligned to 4 bytes.
 */
#pragma diag_suppress = Pa039
#endif

#define TEXT_CONTENT_OFFSET_WITHOUT_TRANSFORM   9 * 4
#define TRANSFORM_MATRIX_LENGTH                 9 * 4
ElmHandle _load_text_data(uint8_t *data, el_Obj_EVO *evo)
{
    el_Obj_TEXT *evo_text = NULL;
    uint8_t *text_data = NULL;
    el_Text_Header *text_header = (el_Text_Header *)data;

    if (evo == NULL) {
#if (RTOS && DDRLESS) || BAREMETAL
        evo = alloc_evo(1);
#else
        evo = (el_Obj_EVO *)elm_alloc(1, sizeof(el_Obj_TEXT));
#endif
    }
    JUMP_IF_NULL(evo, error_exit);
#ifdef ENABLE_STRICT_DEBUG_MEMSET
    memset(evo, 0, sizeof(el_Obj_EVO));
#endif
    evo_text = (el_Obj_TEXT *)evo;

    /*
     Default transform matrix is,
       identity matrix
       no-scaling
       zero-translate
    */
    _init_transform(&evo_text->defaultAttrib.transform);
    memcpy(&evo_text->defaultAttrib.transform.matrix, &text_header->matrix,
        sizeof(vg_lite_matrix_t));

    text_data = (uint8_t *)elm_alloc(1, text_header->data_length);

    memcpy(text_data, (void *)(data + sizeof(el_Text_Header)), text_header->data_length);

    evo_text->tspan_has_dx_dy   = text_header->tspan_has_dx_dy;
    evo_text->x_pos             = (int)text_header->x_pos;
    evo_text->y_pos             = (int)text_header->y_pos;
    evo_text->text_anchor       = text_header->text_flags.text_anchor;
    evo_text->font_id           = (int)text_header->font_id;
    evo_text->font_size         = (int)text_header->font_size;
    evo_text->msg               = text_data;

    evo_text->defaultAttrib.quality = (ELM_QUALITY)VG_LITE_HIGH;
    evo_text->defaultAttrib.fill_rule = ELM_EVO_FILL_NZ;
    evo_text->defaultAttrib.blend = ELM_BLEND_SRC_OVER;
    evo_text->defaultAttrib.paint.type = ELM_PAINT_TEXT;
    evo_text->defaultAttrib.paint.color = text_header->color;

    evo_text->object.type = ELM_OBJECT_TYPE_EVO;
    evo_text->object.reference = 0;
    evo_text->attribute = evo_text->defaultAttrib;

    ref_object(&evo_text->object);
    JUMP_IF_NON_ZERO_VALUE(add_object(&evo_text->object), error_exit);

    return evo_text->object.handle;

error_exit:
    if ( (evo_text) && (evo_text->msg != NULL) ) {
        elm_free(evo_text->msg);
        evo_text->msg = NULL;
    }
    if ( evo != NULL ) {
        elm_free(evo);
    }

    return ELM_NULL_HANDLE;
}

#if (defined(__ICCARM__))
/* Restore the unaligned data structure attribute warning */
#pragma diag_default = Pa039
#endif

void _unload_text(el_Obj_EVO *evo)
{
    el_Obj_TEXT *evo_text = (el_Obj_TEXT *)evo;
    if(evo_text->msg != NULL)
    {
        elm_free(evo_text->msg);
        evo_text->msg = NULL;
    }
}
void destroy_font_data()
{
    int i=0, j = 0;
    if(fontblockobj != NULL) {
        if(fontblockobj->sizes_of_ttf_data != NULL){
            elm_free(fontblockobj->sizes_of_ttf_data);
            fontblockobj->sizes_of_ttf_data = NULL;
        }
        if(fontblockobj->offsets_of_ttf_data != NULL){
            elm_free(fontblockobj->offsets_of_ttf_data);
            fontblockobj->offsets_of_ttf_data = NULL;
        }
        if(fontblockobj->sizes_of_vector_data != NULL){
            elm_free(fontblockobj->sizes_of_vector_data);
            fontblockobj->sizes_of_vector_data = NULL;
        }
        if(fontblockobj->offsets_of_vector_data != NULL){
            elm_free(fontblockobj->offsets_of_vector_data);
            fontblockobj->offsets_of_vector_data = NULL;
        }
        if(fontblockobj->sizes_of_text_font_data != NULL){
            elm_free(fontblockobj->sizes_of_text_font_data);
            fontblockobj->sizes_of_text_font_data = NULL;
        }
        if(fontblockobj->offsets_of_text_font_data != NULL){
            elm_free(fontblockobj->offsets_of_text_font_data);
            fontblockobj->offsets_of_text_font_data = NULL;
        }
        for(i=0; i<fontblockobj->num_ttf_fonts; i++)
        {
            if(fontblockobj->ttf_fonts[i].fields != NULL){
                for(j=0; j<fontblockobj->ttf_fonts[i].num_fields; j++)
                {
                    if(fontblockobj->ttf_fonts[i].fields[j].data != NULL) {
                        elm_free(fontblockobj->ttf_fonts[i].fields[j].data);
                        fontblockobj->ttf_fonts[i].fields[j].data = NULL;
                    }
                }
                elm_free(fontblockobj->ttf_fonts[i].fields);
                fontblockobj->ttf_fonts[i].fields = NULL;
            }
        }
        if(fontblockobj->ttf_fonts != NULL){
            elm_free(fontblockobj->ttf_fonts);
            fontblockobj->ttf_fonts = NULL;
        }
        for(i=0; i<fontblockobj->num_vector_fonts; i++)
        {
            if(fontblockobj->vector_fonts[i].fields != NULL){
                for(j=0; j<fontblockobj->vector_fonts[i].num_fields; j++)
                {
                    if(fontblockobj->vector_fonts[i].fields[j].data != NULL) {
                        elm_free(fontblockobj->vector_fonts[i].fields[j].data);
                        fontblockobj->vector_fonts[i].fields[j].data = NULL;
                    }
                }
                elm_free(fontblockobj->vector_fonts[i].fields);
                fontblockobj->vector_fonts[i].fields = NULL;
            }
        }
        if(fontblockobj->vector_fonts != NULL){
            elm_free(fontblockobj->vector_fonts);
            fontblockobj->vector_fonts = NULL;
        }
        for(i=0; i<fontblockobj->num_text_fonts; i++)
        {
            if(fontblockobj->text_fonts[i].fields != NULL){
                for(j=0; j<fontblockobj->text_fonts[i].num_fields; j++)
                {
                    if(fontblockobj->text_fonts[i].fields[j].data != NULL) {
                        elm_free(fontblockobj->text_fonts[i].fields[j].data);
                        fontblockobj->text_fonts[i].fields[j].data = NULL;
                    }
                }
                elm_free(fontblockobj->text_fonts[i].fields);
                fontblockobj->text_fonts[i].fields = NULL;
            }
        }
        if(fontblockobj->text_fonts != NULL){
            elm_free(fontblockobj->text_fonts);
            fontblockobj->text_fonts = NULL;
        }

        elm_free(fontblockobj);
        fontblockobj = NULL;
    }

    vg_lite_unload_font_data();

    for(int i=0; i<g_total_system_font; i++)
    {
        if(g_font_properties[i][eFontNameProperty].value.data != NULL)
        {
            elm_free(g_font_properties[i][eFontNameProperty].value.data);
            g_font_properties[i][eFontNameProperty].value.data = NULL;
        }
    }

    return;
}

void _release_default_text_parameters(void)
{
    if(g_default_font_properties[eFontNameProperty].value.data != NULL)
    {
        elm_free(g_default_font_properties[eFontNameProperty].value.data);
        g_default_font_properties[eFontNameProperty].value.data = NULL;
    }
    return;
}
