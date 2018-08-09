/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include "sdk_config.h"
#if APP_USBD_ENABLED
#include "app_usbd_string_desc.h"
#include "app_usbd_langid.h"
#include "app_usbd_core.h"
#include "nordic_common.h"

/**
 * @defgroup app_usbd_string_desc
 * @ingroup app_usbd
 *
 * USBD string descriptors management
 * @{
 */

/**
 * @brief Array with language identifiers
 *
 * This array would be used to search the proper string for selected language.
 */
static const uint16_t m_langids[] = { APP_USBD_STRINGS_LANGIDS };

/**
 * @brief Language ID descriptor
 *
 * Language
 */


/**
 * @brief Mnemonics for the string positions in the array
 *
 * The mnemonics for the indexes of the strings inside the string array.
 */
enum {
    APP_USBD_STRING_ID_LANGIDS_ARRAY_POS = 0,  /**< Supported language identifiers */
    APP_USBD_STRING_ID_MANUFACTURER_ARRAY_POS, /**< Manufacturer name */
    APP_USBD_STRING_ID_PRODUCT_ARRAY_POS,      /**< Product name */
    APP_USBD_STRING_ID_SERIAL_ARRAY_POS,       /**< Serial number */
#define X(mnemonic, str_idx, ...) CONCAT_2(mnemonic, _ARRAY_POS),
    APP_USBD_STRINGS_USER
#undef X
};

/**
 * @brief String index into internal array index conversion table
 *
 * The array that transforms the USB string indexes into internal array position.
 * @note Value 0 used to mark non-existing string.
 */
static const uint8_t m_string_translation[APP_USBD_STRING_ID_CNT] =
{
    [APP_USBD_STRING_ID_LANGIDS     ] = APP_USBD_STRING_ID_LANGIDS_ARRAY_POS,
    [APP_USBD_STRING_ID_MANUFACTURER] = APP_USBD_STRING_ID_MANUFACTURER_ARRAY_POS,
    [APP_USBD_STRING_ID_PRODUCT     ] = APP_USBD_STRING_ID_PRODUCT_ARRAY_POS,
    [APP_USBD_STRING_ID_SERIAL      ] = APP_USBD_STRING_ID_SERIAL_ARRAY_POS,
#define X(mnemonic, str_idx, ...) [mnemonic] = CONCAT_2(mnemonic, _ARRAY_POS),
    APP_USBD_STRINGS_USER
#undef X
};

#ifndef APP_USBD_STRINGS_MANUFACTURER_EXTERN
#define APP_USBD_STRINGS_MANUFACTURER_EXTERN 0
#endif

#ifndef APP_USBD_STRINGS_PRODUCT_EXTERN
#define APP_USBD_STRINGS_PRODUCT_EXTERN 0
#endif

#ifndef APP_USBD_STRING_SERIAL_EXTERN
#define APP_USBD_STRING_SERIAL_EXTERN 0
#endif

#if APP_USBD_STRINGS_MANUFACTURER_EXTERN
extern uint16_t APP_USBD_STRINGS_MANUFACTURER[];
#endif

#if APP_USBD_STRINGS_PRODUCT_EXTERN
extern uint16_t APP_USBD_STRINGS_PRODUCT[];
#endif

#if APP_USBD_STRING_SERIAL_EXTERN
extern uint16_t APP_USBD_STRING_SERIAL[];
#endif


/**
 * @brief String descriptors table
 * */
static const uint16_t * m_string_dsc[APP_USBD_STRING_ID_CNT][ARRAY_SIZE(m_langids)] =
{
    [APP_USBD_STRING_ID_LANGIDS_ARRAY_POS]      = { APP_USBD_STRING_DESC(APP_USBD_STRINGS_LANGIDS) },
    [APP_USBD_STRING_ID_MANUFACTURER_ARRAY_POS] = { APP_USBD_STRINGS_MANUFACTURER },
    [APP_USBD_STRING_ID_PRODUCT_ARRAY_POS]      = { APP_USBD_STRINGS_PRODUCT },
    [APP_USBD_STRING_ID_SERIAL_ARRAY_POS]       = { APP_USBD_STRING_SERIAL },
#define X(mnemonic, str_idx, ...) [CONCAT_2(mnemonic, _ARRAY_POS)] = { __VA_ARGS__ },
    APP_USBD_STRINGS_USER
#undef X
};



uint16_t const * app_usbd_string_desc_get(app_usbd_string_desc_idx_t idx, uint16_t langid)
{
    /* LANGID string */
    if (APP_USBD_STRING_ID_LANGIDS == idx)
    {
        return m_string_dsc[APP_USBD_STRING_ID_LANGIDS_ARRAY_POS][0];
    }

    /* Searching for the language */
    uint8_t lang_idx = 0;
    if (ARRAY_SIZE(m_langids) > 1)
    {
        while (m_langids[lang_idx] != langid)
        {
            if (++lang_idx >= ARRAY_SIZE(m_langids))
            {
                return NULL;
            }
        }
    }

    /* Get the string index in array */
    if (idx >= ARRAY_SIZE(m_string_translation))
    {
        return NULL;
    }

    uint8_t str_pos = m_string_translation[idx];
    if (str_pos == 0)
    {
        return NULL;
    }

    uint16_t const * p_str = m_string_dsc[str_pos][lang_idx];
    if ((ARRAY_SIZE(m_langids) > 1) && (lang_idx != 0))
    {
        if (p_str == NULL)
        {
            p_str = m_string_dsc[str_pos][0];
        }
    }

    return p_str;
}

/** @} */
#endif // APP_USBD_ENABLED
