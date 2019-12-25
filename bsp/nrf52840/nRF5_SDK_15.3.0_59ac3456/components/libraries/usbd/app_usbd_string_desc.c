/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#include "utf.h"

/**
 * @defgroup app_usbd_string_desc
 * @ingroup app_usbd
 *
 * USBD string descriptor management
 * @{
 */

/**
 * @brief Array with language identifiers.
 *
 * This array is used to search the proper string for the selected language.
 */
static uint16_t const m_langids[] = { APP_USBD_STRINGS_LANGIDS };

/**
 * @brief Language ID descriptor.
 *
 * Language.
 */


/**
 * @brief Mnemonics for the string positions in the array.
 *
 * The mnemonics for the indexes of the strings inside the string array.
 */
enum {
    APP_USBD_STRING_ID_LANGIDS_ARRAY_POS = 0,  /**< Supported language identifiers. */

#if (APP_USBD_STRING_ID_MANUFACTURER != 0)
    APP_USBD_STRING_ID_MANUFACTURER_ARRAY_POS, /**< Manufacturer name. */
#endif // (APP_USBD_STRING_ID_MANUFACTURER != 0)

#if (APP_USBD_STRING_ID_PRODUCT != 0)
    APP_USBD_STRING_ID_PRODUCT_ARRAY_POS, /**< Product name. */
#endif // (APP_USBD_STRING_ID_PRODUCT != 0)

#if (APP_USBD_STRING_ID_SERIAL != 0)
    APP_USBD_STRING_ID_SERIAL_ARRAY_POS, /**<  Serial number. */
#endif // (APP_USBD_STRING_ID_SERIAL != 0)

#if (APP_USBD_STRING_ID_CONFIGURATION != 0)
    APP_USBD_STRING_ID_CONFIGURATION_ARRAY_POS, /**< Configuration string. */
#endif // (APP_USBD_STRING_ID_CONFIGURATION != 0)

#define X(mnemonic, str_idx, ...) CONCAT_2(mnemonic, _ARRAY_POS),
    APP_USBD_STRINGS_USER
#undef X
};

/**
 * @brief String index into internal array index conversion table.
 *
 * The array that transforms the USB string indexes into internal array position.
 * @note Value 0 is used to mark non-existing string.
 */
static uint8_t const m_string_translation[APP_USBD_STRING_ID_CNT] =
{
    [APP_USBD_STRING_ID_LANGIDS] = APP_USBD_STRING_ID_LANGIDS_ARRAY_POS,

#if (APP_USBD_STRING_ID_MANUFACTURER != 0)
    [APP_USBD_STRING_ID_MANUFACTURER] = APP_USBD_STRING_ID_MANUFACTURER_ARRAY_POS,
#endif // (APP_USBD_STRING_ID_MANUFACTURER != 0)

#if (APP_USBD_STRING_ID_PRODUCT != 0)
    [APP_USBD_STRING_ID_PRODUCT] = APP_USBD_STRING_ID_PRODUCT_ARRAY_POS,
#endif // (APP_USBD_STRING_ID_PRODUCT != 0)

#if (APP_USBD_STRING_ID_SERIAL != 0)
    [APP_USBD_STRING_ID_SERIAL] = APP_USBD_STRING_ID_SERIAL_ARRAY_POS,
#endif // (APP_USBD_STRING_ID_SERIAL != 0)

#if (APP_USBD_STRING_ID_CONFIGURATION != 0)
    [APP_USBD_STRING_ID_CONFIGURATION] = APP_USBD_STRING_ID_CONFIGURATION_ARRAY_POS,
#endif // (APP_USBD_STRING_ID_CONFIGURATION != 0)

#define X(mnemonic, str_idx, ...) [mnemonic] = CONCAT_2(mnemonic, _ARRAY_POS),
    APP_USBD_STRINGS_USER
#undef X
};

#ifndef APP_USBD_STRINGS_MANUFACTURER_EXTERN
#define APP_USBD_STRINGS_MANUFACTURER_EXTERN 0
#endif

#if APP_USBD_STRINGS_MANUFACTURER_EXTERN
extern uint8_t APP_USBD_STRINGS_MANUFACTURER[];
#endif

#ifndef APP_USBD_STRINGS_PRODUCT_EXTERN
#define APP_USBD_STRINGS_PRODUCT_EXTERN 0
#endif

#if APP_USBD_STRINGS_PRODUCT_EXTERN
extern uint8_t APP_USBD_STRINGS_PRODUCT[];
#endif

#ifndef APP_USBD_STRING_SERIAL_EXTERN
#define APP_USBD_STRING_SERIAL_EXTERN 0
#endif

#if APP_USBD_STRING_SERIAL_EXTERN
extern uint8_t APP_USBD_STRING_SERIAL[];
#endif

#ifndef APP_USBD_STRING_CONFIGURATION_EXTERN
#define APP_USBD_STRING_CONFIGURATION_EXTERN 0
#endif

#if APP_USBD_STRING_CONFIGURATION_EXTERN
extern uint8_t APP_USBD_STRING_CONFIGURATION[];
#endif

/**
 * @brief String descriptor table.
 * */
static uint8_t const * m_string_dsc[APP_USBD_STRING_ID_CNT][ARRAY_SIZE(m_langids)] =
{
    [APP_USBD_STRING_ID_LANGIDS_ARRAY_POS] = {APP_USBD_STRING_RAW16_DESC(APP_USBD_STRINGS_LANGIDS)},

#if (APP_USBD_STRING_ID_MANUFACTURER != 0)
    [APP_USBD_STRING_ID_MANUFACTURER_ARRAY_POS] = { APP_USBD_STRINGS_MANUFACTURER },
#endif // (APP_USBD_STRING_ID_MANUFACTURER != 0)

#if (APP_USBD_STRING_ID_PRODUCT != 0)
    [APP_USBD_STRING_ID_PRODUCT_ARRAY_POS] = { APP_USBD_STRINGS_PRODUCT },
#endif // (APP_USBD_STRING_ID_PRODUCT != 0)

#if (APP_USBD_STRING_ID_SERIAL != 0)
    [APP_USBD_STRING_ID_SERIAL_ARRAY_POS] = { APP_USBD_STRING_SERIAL },
#endif // (APP_USBD_STRING_ID_SERIAL != 0)

#if (APP_USBD_STRING_ID_CONFIGURATION != 0)
    [APP_USBD_STRING_ID_CONFIGURATION_ARRAY_POS] = { APP_USBD_STRINGS_CONFIGURATION },
#endif // (APP_USBD_STRING_ID_CONFIGURATION != 0)

#define X(mnemonic, str_idx, ...) [CONCAT_2(mnemonic, _ARRAY_POS)] = {__VA_ARGS__},
    APP_USBD_STRINGS_USER
#undef X
};

/**
 * @brief Function for preparing UTF16 string descriptor.
 *
 * @param idx    String descriptor ID.
 * @param langid Language ID.
 *
 * @return Pointer to the string descriptor.
 */
static uint16_t * app_usbd_prepare_string(uint8_t idx, uint16_t langid)
{
    if (m_string_dsc[idx][langid][0] == 0x00)
    {
        return (uint16_t *) &(m_string_dsc[idx][langid][2]);
    }

#if ((APP_USBD_CONFIG_DESC_STRING_SIZE * 2) + 2) <= NRF_DRV_USBD_EPSIZE
    uint16_t * string_buffer = app_usbd_core_setup_transfer_buff_get(NULL);
#else
    static uint16_t string_buffer[APP_USBD_CONFIG_DESC_STRING_SIZE + 1];
    // + 1 element for string descriptor type and size
#endif

    uint8_t         size  = 0;
    const uint8_t * p_pos = m_string_dsc[idx][langid];

#if APP_USBD_CONFIG_DESC_STRING_UTF_ENABLED
    size = utf8UTF16Count((char *) p_pos, 0);
    ASSERT(size <= APP_USBD_CONFIG_DESC_STRING_SIZE);

    uint16_t * p_out = &(string_buffer[1]);
    uint32_t   rune;

    while (*p_pos != 0)
    {
        p_pos = (uint8_t *) utf8DecodeRune((char *) p_pos, 0, &rune);
        p_out += utf16EncodeRune(rune, p_out);
    }
#else
    while(*p_pos != 0)
    {
        ASSERT(size < APP_USBD_CONFIG_DESC_STRING_SIZE);
        ++size;
        string_buffer[size] = *p_pos;
        ++p_pos;
    }
#endif

    // Descriptor size is length of the string times 2 bytes per character + 2 bytes for
    // descriptor type and size.
    string_buffer[0] = (0xff & (size * 2 + 2)) | ((uint16_t)APP_USBD_DESCRIPTOR_STRING) << 8;

    return string_buffer;
}

uint16_t const * app_usbd_string_desc_get(uint8_t idx, uint16_t langid)
{
    /* LANGID string. */
    if (APP_USBD_STRING_ID_LANGIDS == idx)
    {
        return app_usbd_prepare_string(APP_USBD_STRING_ID_LANGIDS_ARRAY_POS, 0);
    }

    /* Searching for the language. */
    uint8_t lang_idx = 0;
    if (ARRAY_SIZE(m_langids) > 1)
    {
        while (m_langids[lang_idx] != langid)
        {
            ++lang_idx;
            if (lang_idx >= ARRAY_SIZE(m_langids))
            {
                return NULL;
            }
        }
    }

    /* Get the string index in array. */
    if (idx >= ARRAY_SIZE(m_string_translation))
    {
        return NULL;
    }

    uint8_t str_pos = m_string_translation[idx];
    if (str_pos == 0)
    {
        return NULL;
    }

    if ((ARRAY_SIZE(m_langids) > 1) && (lang_idx != 0))
    {
        if (m_string_dsc[str_pos][lang_idx] == NULL)
        {
            lang_idx = 0;
        }
    }

    if (m_string_dsc[str_pos][lang_idx] == NULL)
    {
        return NULL;
    }

    return app_usbd_prepare_string(str_pos, lang_idx);
}

/** @} */
#endif // APP_USBD_ENABLED
