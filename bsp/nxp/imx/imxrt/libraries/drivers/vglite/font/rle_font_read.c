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
#include <mcufont.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vg_lite.h"
#include "buf_reader.h"
#include "vg_lite_text.h"
#include "vft_draw.h"
#include "vft_debug.h"

/** Macros */
#define __COUNTOF(x) (sizeof(x)/sizeof(x[0]))
#define MAX_SYSTEM_FONTS (8)

#define RCD_ALLOC(x) _mem_allocate(x)
#define RCD_FREE(x) _mem_free(x)

#ifdef ENABLE_DEBUG_TRACE
static int g_id;

#define DBG_ID() (g_id)
#define DBG_INC_ID() (g_id++)
#define DBG_SET_ID(x) g_id = x
#else

#define DBG_ID() (0)
#define DBG_INC_ID() (0)
#define DBG_SET_ID(x)
#endif

#if APP_ENABLE_SDCARD
#define sprintf_s snprintf
#endif

/** Data structures */
typedef struct font_height_list {
    const char font_height;
    const char ref_font_height;
    const char ref_font_scale;
} font_height_list_t;

typedef struct font_info_internal {
  /* Variable shared between user and driver */
  vg_lite_font_params_t font_params;
  /* any additional variables internal to driver */
  int valid;
  /* Internal loaded raster font */
  struct mf_font_s *_raster_font;
  /* Internal loaded vector font */
  font_face_desc_t *_vector_font;
}font_info_internal_t;

/** Internal or external API prototypes */

/** Globals */
static font_info_internal_t s_device_fonts[MAX_SYSTEM_FONTS];

/** Local function prototypes */
int read_rle_font_header(bufferred_reader_t *f, struct mf_font_s* font);
int read_rle_font_from_buffer(char *buf, int size, struct mf_font_s* font);
int load_raster_font(char *data, int data_len, struct mf_font_s** font);

int read_8b(bufferred_reader_t *f, uint8_t* pdata);
int read_16b(bufferred_reader_t *f, uint16_t* pword);
int read_32b(bufferred_reader_t *f, uint32_t* pword);
int read_16b_blob(bufferred_reader_t *f, uint16_t** ary, uint32_t* ary_len);
int read_8b_blob(bufferred_reader_t *f, uint8_t** ary, uint32_t* ary_len);
int free_rle_font_memory(struct mf_font_s** font);
vg_lite_error_t vg_lite_free_font_memory(vg_lite_font_t font);
vg_lite_error_t vg_lite_load_font_data(vg_lite_font_t font, int font_height);

/** Externs if any */

/** Code section */
vg_lite_font_t vg_lite_find_font(
    char *font_name,
    eFontWeight_t  font_weight,
    eFontStretch_t font_stretch,
    eFontStyle_t   font_style,
    int font_height);

vg_lite_error_t vg_lite_register_font(vg_lite_font_t *font,
    vg_lite_font_params_t *params)
{
  int i;
  int free_entry = VG_LITE_INVALID_FONT;

  if (font != NULL)
    *font = VG_LITE_INVALID_FONT;

  /* Check if font is already registered */
  for (i=0; i<MAX_SYSTEM_FONTS; i++) {
    /* Is entry is valid ? */
    if ( s_device_fonts[i].valid == 0 ) {
        /* Grab free entry in list for new font */
        if (free_entry == -1 ) {
            free_entry = i;
        }
    } else if (s_device_fonts[i].valid == 1 ) {
      /* Does font.name matches */
      if ( strncmp(s_device_fonts[i].font_params.name,
                  params->name,
                  strlen(s_device_fonts[i].font_params.name)) == 0)
      {
            return VG_LITE_ALREADY_EXISTS;
      }
    } else {
      printf("Corrupt font table\n");
      return VG_LITE_INVALID_ARGUMENT;
    }
  }

  /* Check if list is completely full or not */
  if ( i == MAX_SYSTEM_FONTS && free_entry == VG_LITE_INVALID_FONT) {
      /* Font List descriptor exhausted */
      return VG_LITE_OUT_OF_RESOURCES;
  } else {
      /* Add new font in global table */
      memcpy(&s_device_fonts[free_entry].font_params, params, sizeof(vg_lite_font_params_t));
      s_device_fonts[free_entry].valid = 1;
/*
   Loading font here leads to low run-time memory, we may need to characterize memory usage
   e.g. pure path test don't require font, eventhrough application registers them
*/
#if 0
      error = vg_lite_load_font_data(free_entry, params->font_height);
      if ( error != 0 ) {
          s_device_fonts[free_entry].valid = 0;
          return error;
      }
#endif
  }

  if (font != NULL)
    *font = free_entry;

  return VG_LITE_SUCCESS;
}

int vg_lite_is_font_valid(vg_lite_font_t font)
{
    if (font < MAX_SYSTEM_FONTS) {
        if (s_device_fonts[font].valid == 1)
            return 0;
    }
    return VG_LITE_INVALID_ARGUMENT;
}

int vg_lite_is_vector_font(vg_lite_font_t font)
{
    if (font < MAX_SYSTEM_FONTS) {
        if (s_device_fonts[font].valid == 1)
            return (s_device_fonts[font].font_params.font_type ==
                eFontTypeVector);
        else
            return 0;
    }
    return VG_LITE_INVALID_ARGUMENT;;
}

vg_lite_error_t vg_lite_unregister_font(vg_lite_font_t font)
{
    if (vg_lite_is_font_valid(font) != 0 ) {
        /* Font not found */
        return VG_LITE_INVALID_ARGUMENT;;
    }

    vg_lite_free_font_memory(font);
    s_device_fonts[font].valid = 0;
    return VG_LITE_SUCCESS;
}

char *vg_lite_get_font_name(vg_lite_font_t font)
{
  if ( vg_lite_is_font_valid(font) != 0 ) {
        return NULL;
  }

  return (char *)s_device_fonts[font].font_params.name;
}

vg_lite_error_t vg_lite_free_font_memory(vg_lite_font_t font)
{
  if ( vg_lite_is_font_valid(font) != 0 ) {
        /* Font not found */
        return VG_LITE_INVALID_ARGUMENT;
  }
  switch (s_device_fonts[font].font_params.font_type) {
    case eFontTypeVector:
      if ( s_device_fonts[font]._vector_font != NULL ) {
          vft_unload(s_device_fonts[font]._vector_font);
          s_device_fonts[font]._vector_font = NULL;
      }
      break;
    case eFontTypeRaster:
      if ( s_device_fonts[font]._raster_font != NULL ) {
          free_rle_font_memory(&s_device_fonts[font]._raster_font);
          s_device_fonts[font]._raster_font = NULL;
      }
      break;
  }

  return VG_LITE_SUCCESS;
}

font_face_desc_t *_vg_lite_get_vector_font(vg_lite_font_t font)
{
  if ( vg_lite_is_font_valid(font) != 0 ) {
        return NULL;
  }

  return s_device_fonts[font]._vector_font;
}

struct mf_font_s *_vg_lite_get_raster_font(vg_lite_font_t font)
{
  if ( vg_lite_is_font_valid(font) != 0 ) {
        return NULL;
  }

  return s_device_fonts[font]._raster_font;
}

vg_lite_error_t vg_lite_load_font_data(vg_lite_font_t font, int font_height)
{
  if ( vg_lite_is_font_valid(font) != 0 ) {
        /* Font not found */
        return VG_LITE_INVALID_ARGUMENT;
  }

  switch (s_device_fonts[font].font_params.font_type) {
    case eFontTypeVector:
      if (s_device_fonts[font]._vector_font == NULL ) {
          //printf("Loading vector font : [%s]\n",
          //       s_device_fonts[font].font_params.name);
          s_device_fonts[font]._vector_font =
          vft_load_from_buffer(
                 s_device_fonts[font].font_params.data,
                 s_device_fonts[font].font_params.data_len);
          if ( s_device_fonts[font]._vector_font == NULL )  {
                return VG_LITE_INVALID_ARGUMENT;
          }
      }
      return VG_LITE_SUCCESS;
    case eFontTypeRaster:
      if (s_device_fonts[font]._raster_font == NULL ) {
          //printf("Loading raster font : [%s]\n",
          //       s_device_fonts[font].font_params.name);
          /* Raster fonts height should match */
          if ( font_height == s_device_fonts[font].font_params.font_height &&
              load_raster_font(
                 s_device_fonts[font].font_params.data,
                 s_device_fonts[font].font_params.data_len,
                 &s_device_fonts[font]._raster_font) != 0)
          {
              return VG_LITE_INVALID_ARGUMENT;
          }
      }
      return VG_LITE_SUCCESS;
  }
  return VG_LITE_INVALID_ARGUMENT;
}


vg_lite_font_t vg_lite_find_font(
    char *font_name_list,
    eFontWeight_t  font_weight,
    eFontStretch_t font_stretch,
    eFontStyle_t   font_style,
    int font_height)
{
    int i;
    char tmp_data;
    int font_found = 0;
    int end_pos = 0; /* End position of font name */
    char *font_name;
    /*
    printf("Font params: [%s],%d, %d, %d, %d\n",
           font_name_list,
           font_weight,
           font_stretch,
           font_style,
           font_height);
    */

    /* While probing font, if required font is found, then
       only keep that name in supplied font list */

    /* Split and extract font name one-by-one */
    font_name = font_name_list;
    while (font_found == 0 &&
           font_name[end_pos] != '\0')
    {
        tmp_data = '\0';
        /* Scan for seperator */
        while (font_name[end_pos] != '\0') {
            if (font_name[end_pos] == ',' || font_name[end_pos] == ' ' ||
              font_name[end_pos] == '\t')
            {
                tmp_data = font_name[end_pos];
                font_name[end_pos] = '\0';
                break;
            }
            end_pos++;
        }

        /* Search for exact font-name match */
        for (i=0; i<__COUNTOF(s_device_fonts); i++) {
           if (s_device_fonts[i].valid == 0)
               continue;

           /* For vector font only compare name */
           if (s_device_fonts[i].font_params.font_type == eFontTypeVector ) {
                if ( strlen(font_name) > 0 &&
                    strcmp(font_name,
                    s_device_fonts[i].font_params.name) == 0)
                {
                   font_name[end_pos] = tmp_data; /* Restor delimeter */
                   return i;
                }
           } else {
                /* For raster font compare all properties */
                if (s_device_fonts[i].font_params.font_weight == font_weight &&
                    s_device_fonts[i].font_params.font_stretch == font_stretch &&
                    s_device_fonts[i].font_params.font_style == font_style )
                {
                    if ( strlen(font_name) > 0 &&
                        strcmp(font_name,
                        s_device_fonts[i].font_params.name) == 0)
                    {
                       font_name[end_pos] = tmp_data; /* Restor delimeter */

                       if (s_device_fonts[i].font_params.font_height == font_height)
                       {
                            return i;
                       }
                        /* Update font_name_list to improve future searches */
                        strncpy(font_name_list, font_name, strlen(font_name)+1);
                    }
                }
            }
        }
        /* Continue searching for other font entries */
        font_name[end_pos] = tmp_data;
        font_name += (end_pos + 1);
        end_pos = 0;
    }
    printf("WARNING: [%s] Font not found\r\n",font_name_list);

    return VG_LITE_INVALID_FONT;
}

void vg_lite_text_init(void)
{
    static int font_table_ready = 0;

    if (font_table_ready)
        return;

    /* Initialize font table */
    memset(s_device_fonts, 0, MAX_SYSTEM_FONTS * sizeof(font_info_internal_t));
    font_table_ready = 1;
}

/* Read-Write 8-bit unsigned int data */
int read_8b(bufferred_reader_t * f, uint8_t* pdata)
{
    bufferred_fread(pdata, 1, 1, f);
    TRACE_DBG(("%d) 8b: fp=%08x %d %d\r\n", DBG_INC_ID(),
               bufferred_ftell(f) - 1, 1, *pdata));
    return 1;
}

/* Read-Write 16-bit unsigned int data */
int read_16b(bufferred_reader_t * f, uint16_t* pword)
{
    uint8_t buf[4];
    uint16_t word;

    bufferred_fread(buf, 2, 1, f);
    word = 0;   word += buf[1];
    word <<= 8; word += buf[0];

    TRACE_DBG(("%d) 16b: fp=%08x %d %d\r\n", DBG_INC_ID(),
               bufferred_ftell(f)-2, 2, word));
    *pword = word;
    return 2;
}

/* Read-write 32-bit unsigned int data */
int read_32b(bufferred_reader_t * f, uint32_t* pword)
{
    uint8_t buf[4];
    uint32_t word;

    bufferred_fread(buf, 4, 1, f);
    word = 0;   word += buf[3];
    word <<= 8; word += buf[2];
    word <<= 8; word += buf[1];
    word <<= 8; word += buf[0];

    *pword = word;
    TRACE_DBG(("%d) 32b: fp=%08x %d %d\r\n", DBG_INC_ID(),
               bufferred_ftell(f) - 4, 4,
               word));
    return 4;
}

int read_16b_blob(bufferred_reader_t * f, uint16_t** ary, uint32_t* ary_len)
{
    uint16_t blob_len = 0;

    *ary_len = 0;
    bufferred_fread(&blob_len, 1, sizeof(uint16_t), f);
    *ary = (uint16_t *)RCD_ALLOC(blob_len * sizeof(uint16_t)); /* Malloc must be aligned on 2 byte boundary */
    if (*ary == NULL) {
        TRACE_ERR(("ERROR: malloc failed\n"));;
        return VG_LITE_OUT_OF_MEMORY;
    }
    if ((((unsigned long)*ary) & 0x1) != 0) {
        TRACE_ERR(("ERROR: malloc pointer not 2 byte aligned\n"));;
        return VG_LITE_NOT_ALIGNED;
    }
    TRACE_DBG(("%d ) 16b_blob: fp=%08x %d\r\n", DBG_INC_ID(), bufferred_ftell(f)-2,
               (int)blob_len));
    bufferred_fread(*ary, 2, blob_len, f);
    *ary_len = blob_len * 2;

    return blob_len + 2; /* Actual bytes read from file */
}

int read_8b_blob(bufferred_reader_t * f, uint8_t** ary, uint32_t *ary_len)
{
    uint16_t blob_len = 0;
    uint8_t* p_tmp = (uint8_t *)NULL;
    bufferred_fread(&blob_len, 1, sizeof(uint16_t), f);
    //TRACE_DBG(("%d) 8b_blob: %d\r\n", DBG_INC_ID(), blob_len));
    p_tmp = (uint8_t *)RCD_ALLOC(blob_len+1);
    if (p_tmp == NULL) {
        TRACE_ERR(("ERROR: malloc failed\n"));;
        return VG_LITE_OUT_OF_MEMORY;
    }
    TRACE_DBG(("%d ) 8b_blob: fp=%08x %d\r\n", DBG_INC_ID(), bufferred_ftell(f)-2,
               (int)blob_len));
    bufferred_fread(p_tmp, 1, blob_len, f);
    p_tmp[blob_len] = 0;
    *ary = p_tmp;

    return blob_len + 2; /* Actual bytes read from file */
}

#define EXIT_IF_NEGATIVE(param) if ((ret = param) < 0) return ret;

int read_rle_font_header(bufferred_reader_t * f, struct mf_font_s* font)
{
    int raw_header_offset = 0;
    struct mf_rlefont_s* mfont = (struct mf_rlefont_s*)font;
    uint32_t size = 0;
    int ret = 0;

    TRACE_DBG(("** %s\r\n", __FUNCTION__));
    DBG_SET_ID(0);

    EXIT_IF_NEGATIVE(read_8b_blob(f, (uint8_t **)&font->full_name, &size));
    raw_header_offset += ret; /* font.full_name */

    EXIT_IF_NEGATIVE(read_8b_blob(f, (uint8_t **)&font->short_name, &size));
    raw_header_offset += ret; /* font.short_name */

    EXIT_IF_NEGATIVE(read_8b(f, &font->width));
    raw_header_offset += 1;                       /* font.width */

    EXIT_IF_NEGATIVE(read_8b(f, &font->height));
    raw_header_offset += 1;                       /* font.height */

    EXIT_IF_NEGATIVE(read_8b(f, &font->min_x_advance));
    raw_header_offset += 1;                       /* font.min_x_advance */

    EXIT_IF_NEGATIVE(read_8b(f, &font->max_x_advance));
    raw_header_offset += 1;                       /* font.max_x_advance */

    EXIT_IF_NEGATIVE(read_8b(f, (uint8_t *)&font->baseline_x));
    raw_header_offset += 1;                       /* font.baseline_x */

    EXIT_IF_NEGATIVE(read_8b(f, &font->baseline_y));
    raw_header_offset += 1;                       /* font.baseline_y */

    EXIT_IF_NEGATIVE(read_8b(f, &font->line_height));
    raw_header_offset += 1;                       /* font.line_height */

    EXIT_IF_NEGATIVE(read_8b(f, &font->flags));
    raw_header_offset += 1;                       /* font.flags */

    EXIT_IF_NEGATIVE(read_16b(f, &font->fallback_character));
    raw_header_offset += 2;                       /* font.fallback_character */

    EXIT_IF_NEGATIVE(read_8b(f, &(mfont->version)));
    raw_header_offset += 1;                           /* mf_rlefont_s.version */

    /* Other mf_rlefont_s variables */
    uint16_t value = 0;
    EXIT_IF_NEGATIVE(read_16b(f, &value)); //&mfont->dictionary_data_size));
    mfont->dictionary_data_size = value;
    raw_header_offset += 2;                           /* mf_rlefont_s.dictionary_data_size */

    EXIT_IF_NEGATIVE(read_32b(f, &mfont->dictionary_data_fp_offset));
    raw_header_offset += 4;                           /* mf_rlefont_s.dictionary_data_fp_offset */

    value = 0;
    EXIT_IF_NEGATIVE(read_16b(f, &value)); //mfont->dictionary_offsets_size));
    mfont->dictionary_offsets_size = value;
    raw_header_offset += 2;                           /* mf_rlefont_s.dictionary_data_size */

    EXIT_IF_NEGATIVE(read_32b(f, &mfont->dictionary_offsets_fp_offset));
    raw_header_offset += 4;                           /* mf_rlefont_s.dictionary_data_fp_offset */

    EXIT_IF_NEGATIVE(read_8b(f, &mfont->rle_entry_count));
    raw_header_offset += 1;                           /* mf_rlefont_s.rle_entry_count */

    EXIT_IF_NEGATIVE(read_8b(f, &mfont->dict_entry_count));
    raw_header_offset += 1;                           /* mf_rlefont_s.dict_entry_count */

    EXIT_IF_NEGATIVE(read_8b(f, &mfont->char_range_count));
    raw_header_offset += 1;                           /* mf_rlefont_s.char_range_count */

    mfont->char_ranges = (struct mf_rlefont_char_range_s *)RCD_ALLOC(sizeof(struct mf_rlefont_char_range_s)* mfont->char_range_count);
    memset(mfont->char_ranges, 0, sizeof(struct mf_rlefont_char_range_s) * mfont->char_range_count);

    /* Skip size of ranges */
    for (int r = 0; r < mfont->char_range_count; r++) {
        EXIT_IF_NEGATIVE(read_16b(f, &mfont->char_ranges[r].first_char));
        raw_header_offset += 2;                           /* mf_rlefont_s.char_ranges[r].first_char */

        EXIT_IF_NEGATIVE(read_16b(f, &mfont->char_ranges[r].char_count));
        raw_header_offset += 2;                           /* mf_rlefont_s.char_ranges[r].char_count */

        EXIT_IF_NEGATIVE(read_32b(f, &mfont->char_ranges[r].glyph_offsets_fp_offset));
        raw_header_offset += 4;                           /* mf_rlefont_s.char_ranges[r].glyph_offsets_fp_offset */

        EXIT_IF_NEGATIVE(read_32b(f, &mfont->char_ranges[r].glyph_offsets_size));
        raw_header_offset += 4;                           /* mf_rlefont_s.char_ranges[r].glyph_offsets_size */

        EXIT_IF_NEGATIVE(read_32b(f, &mfont->char_ranges[r].glyph_data_fp_offset));
        raw_header_offset += 4;                           /* mf_rlefont_s.char_ranges[r].glyph_offsets_fp_offset */

        EXIT_IF_NEGATIVE(read_32b(f, &mfont->char_ranges[r].glyph_data_size));
        raw_header_offset += 4;                           /* mf_rlefont_s.char_ranges[r].glyph_offsets_size */
    }
    return raw_header_offset;
}

/* Writes a BMP file. The data is assumed to be 8-bit grayscale. */
int read_rle_font_from_buffer(char *buff, int size, struct mf_font_s* font)
{
    struct mf_rlefont_s* mfont = (struct mf_rlefont_s*)font;
    bufferred_reader_t f_obj;
    bufferred_reader_t * f = &f_obj;
    int raw_header_offset = 0;
    int fp_offset;
    int ret;

    DBG_SET_ID(0);

    /* No need to dynamically allocate small descriptor */
    if ( bufferred_fopen(f, buff, size) < 0 ) {
        /* Font file open failed */
        return VG_LITE_INVALID_ARGUMENT;
    }

    raw_header_offset = read_rle_font_header(f, font);
    if (mfont->dictionary_data_fp_offset != raw_header_offset) {
        TRACE_ERR(("ERROR: dictonary offset is different"));
    }
    TRACE_DBG(("** %s\r\n", __FUNCTION__));
    DBG_SET_ID(0);

    /* Skip header portion */
    bufferred_fseek(f, raw_header_offset, SEEK_SET);
    /* Write dictionary entries */
    fp_offset = raw_header_offset;
    TRACE_DBG(("dictionary_data_fp_offset=%08x %08x\r\n",
        mfont->dictionary_data_fp_offset, bufferred_ftell(f)));
    //mfont->dictionary_data_fp_offset = fp_offset;
    EXIT_IF_NEGATIVE(read_8b_blob(f, &mfont->dictionary_data,
        &mfont->dictionary_data_size));
    fp_offset += mfont->dictionary_data_size + 2;

    //mfont->dictionary_offsets_fp_offset = fp_offset;
    TRACE_DBG(("dictionary_offsets_fp_offset=%08x %08x\r\n",
        mfont->dictionary_offsets_fp_offset, bufferred_ftell(f)));
    EXIT_IF_NEGATIVE(read_16b_blob(f, &mfont->dictionary_offsets,
        &mfont->dictionary_offsets_size));
    fp_offset += mfont->dictionary_offsets_size + 2;

    /* Write range entries */
    for (int r = 0; r < mfont->char_range_count; r++) {
        //mfont->char_ranges[r].glyph_offsets_fp_offset = fp_offset;
        TRACE_DBG(("mfont->char_ranges[%d].glyph_offsets=%08x %08x\r\n", r,
            mfont->char_ranges[r].glyph_offsets_fp_offset, bufferred_ftell(f)));
        EXIT_IF_NEGATIVE(read_16b_blob(f, &mfont->char_ranges[r].glyph_offsets,
            &mfont->char_ranges[r].glyph_offsets_size));
        fp_offset += mfont->char_ranges[r].glyph_offsets_size + 2;

        //mfont->char_ranges[r].glyph_data_fp_offset = fp_offset;
        TRACE_DBG(("mfont->char_ranges[%d].glyph_data_fp_offset=%08x %08x\r\n",
            r,
            mfont->char_ranges[r].glyph_data_fp_offset, bufferred_ftell(f)));
        EXIT_IF_NEGATIVE(read_8b_blob(f, &mfont->char_ranges[r].glyph_data,\
            &mfont->char_ranges[r].glyph_data_size));
        fp_offset += mfont->char_ranges[r].glyph_data_size + 2;
    }

    bufferred_fclose(f);
    return 0;
}

int load_raster_font(char *data, int data_len, struct mf_font_s** font)
{
    int ret;

    /* Allocate font memory */
    *font = (struct mf_font_s*)RCD_ALLOC(sizeof(struct mf_rlefont_s));
    if (*font == NULL) {
        return VG_LITE_OUT_OF_MEMORY;
    }
    memset(*font, 0, sizeof(struct mf_rlefont_s));

    /* Load font from file */
    ret = read_rle_font_from_buffer(data,
                                    data_len, *font);
    if (ret < 0) {
        return ret;
    }

    /* Update generic char width pointers of mculib */
    uint8_t mf_rlefont_character_width(const struct mf_font_s* font,
        uint16_t character);
    uint8_t mf_rlefont_render_character(const struct mf_font_s* font,
        int16_t x0, int16_t y0,
        uint16_t character,
        mf_pixel_callback_t callback,
        void* state);

    (*font)->character_width = &mf_rlefont_character_width;
    (*font)->render_character = &mf_rlefont_render_character;


    return 0;
}

int free_rle_font_memory(struct mf_font_s** font)
{
    struct mf_rlefont_s* mfont = (struct mf_rlefont_s*)(*font);

    RCD_FREE(mfont->font.full_name);
    RCD_FREE(mfont->font.short_name);
    RCD_FREE(mfont->dictionary_data);
    RCD_FREE(mfont->dictionary_offsets);
    for (int r = 0; r < mfont->char_range_count; r++) {
        RCD_FREE(mfont->char_ranges[r].glyph_offsets);
        RCD_FREE(mfont->char_ranges[r].glyph_data);
    }
    #ifdef DEBUG_RESET_DATASTRUCTURE_ON_FREE
    memset(mfont->char_ranges);
    #endif
    RCD_FREE(mfont->char_ranges);

    #ifdef DEBUG_RESET_DATASTRUCTURE_ON_FREE
    memset(mfont);
    #endif
    RCD_FREE(mfont);

    *font = NULL;
    return 0;
}

void vg_lite_unload_font_data(void)
{
    for(int i=0; i<MAX_SYSTEM_FONTS; i++)
    {
        vg_lite_free_font_memory(i);
    }

    return;
}
