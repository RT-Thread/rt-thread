/* A compressed font format based on run length encoding and dictionary
 * compression.
 */

#ifndef _MF_RLEFONT_H_
#define _MF_RLEFONT_H_

#include "mf_font.h"

/* Versions of the RLE font format that are supported. */
#define MF_RLEFONT_VERSION_4_SUPPORTED 1

/* Structure for a range of characters. This implements a sparse storage of
 * character indices, so that you can e.g. pick a 100 characters in the middle
 * of the UTF16 range and just store them. */
struct mf_rlefont_char_range_s
{
    /* The number of the first character in this range. */
    uint16_t first_char;

    /* The total count of characters in this range. */
    uint16_t char_count;

    /* Lookup table with the start indices into glyph_data. */
    uint16_t *glyph_offsets;
    uint32_t glyph_offsets_size;
    uint32_t glyph_offsets_fp_offset;

    /* The encoded glyph data for glyphs in this range. */
    uint8_t *glyph_data;
    uint32_t glyph_data_size;
    uint32_t glyph_data_fp_offset;
};

/* Structure for a single encoded font. */
struct mf_rlefont_s
{
    struct mf_font_s font;

    /* Version of the font definition used. */
    uint8_t version;

    /* Big array of the data for all the dictionary entries. */
    uint8_t *dictionary_data;
    uint32_t dictionary_data_size;
    uint32_t dictionary_data_fp_offset;

    /* Lookup table with the start indices into dictionary_data.
     * Contains N+1 entries, so that the length of the entry can
     * be determined by subtracting from the next offset. */
    uint16_t *dictionary_offsets;
    uint32_t dictionary_offsets_size;
    uint32_t dictionary_offsets_fp_offset;

    /* Number of dictionary entries using the RLE encoding.
     * Entries starting at this index use the dictionary encoding. */
    uint8_t rle_entry_count;

    /* Total number of dictionary entries.
     * Entries after this are nonexistent. */
    uint8_t dict_entry_count;

    /* Number of discontinuous character ranges */
    uint8_t char_range_count;

    /* Array of the character ranges */
    struct mf_rlefont_char_range_s *char_ranges;
};

#ifdef MF_RLEFONT_INTERNALS
/* Internal functions, don't use these directly. */
MF_EXTERN uint8_t mf_rlefont_render_character(const struct mf_font_s *font,
                                              int16_t x0, int16_t y0,
                                              mf_char character,
                                              mf_pixel_callback_t callback,
                                              void *state);

MF_EXTERN uint8_t mf_rlefont_character_width(const struct mf_font_s *font,
                                             mf_char character);
#endif

#endif
