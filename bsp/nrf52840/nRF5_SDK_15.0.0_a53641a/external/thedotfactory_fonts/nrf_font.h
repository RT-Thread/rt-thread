/* Copyright (c) 2016 Eran Duchan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef NRF_FONT_H__
#define NRF_FONT_H__

#include "stdint.h"

/** @file
 *
 * @defgroup nrf_font Font header
 * @{
 * @ingroup nrf_gfx
 *
 * @brief Generated font structures.
 */

/**
 * @brief Font char information.
 */
typedef struct
{
    uint8_t widthBits;                  /**< Width in bits (or pixels) of the character. */
    uint16_t offset;                    /**< Offset of the character's bitmap, in bytes, into the FONT_INFO's data array. */
}FONT_CHAR_INFO;   

/**
 * @brief Font descriptor.
 */
typedef struct
{
    uint8_t height;                     /**< Height in bits (or pixels), of the font's characters. */
    uint8_t startChar;                  /**< The first character in the font (e.g. in charInfo and data). */
    uint8_t endChar;                    /**< The last character in the font. */
    uint8_t spacePixels;                /**< Number of pixels that the space character takes up. */
    const FONT_CHAR_INFO * charInfo;    /**< Pointer to array of char information. */
    const uint8_t * data;               /**< Pointer to a generated array of character visual representation. */
}FONT_INFO;    


/** @} */

#endif // NRF_FONT_H__

