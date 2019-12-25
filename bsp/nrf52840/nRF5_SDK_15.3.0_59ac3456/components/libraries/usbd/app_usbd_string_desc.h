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
#ifndef APP_USBD_STRING_DESC_H__
#define APP_USBD_STRING_DESC_H__

#include <stdint.h>
#include "sdk_common.h"
#include "app_usbd.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup app_usbd_string_desc USBD string descriptors
 * @ingroup app_usbd
 *
 * @brief @tagAPI52840 USBD string descriptor management.
 * @{
 */

/**
 * @brief USB Language identifier initialization.
 *
 * @param[in] lang Language identifier.
 */
#define APP_USBD_LANG(lang) \
    ((app_usbd_langid_t) lang)

/**
 * @brief USB Language identifier with sublanguage initialization.
 *
 * @param[in] lang    Language identifier.
 * @param[in] sublang Sublanguage identifier.
 */
#define APP_USBD_LANG_AND_SUBLANG(lang, sublang) \
    ((app_usbd_langid_t) lang | (app_usbd_langid_t) sublang)

/**
 * @brief USB string initialization.
 *
 * Macro that creates initialization values for the USB string.
 * The string must be declared as a NULL-terminated string.
 *
 * @param[in] str NULL-terminated string.
 *
 * @return String descriptor initialization data.
 */
#define APP_USBD_STRING_DESC(str) (const uint8_t *)(const char[]){str}

/**
 * @brief USB raw 8-bit string initialization.
 *
 * Macro that creates header for raw values passed into descriptor.
 * Values must be of the uint8_t type and separated by commas.
 *
 * @param[in] ... comma-separated values.
 *
 * @return String descriptor initialization data.
 */
#define APP_USBD_STRING_RAW8_DESC(...) (const uint8_t[]){                                          \
    0x00, 0x00, /* NULL character at start to differentiate from normal string */                  \
    (0xff & (sizeof((uint8_t[]){__VA_ARGS__}) + 2)),                                               \
    (APP_USBD_DESCRIPTOR_STRING),                                                                  \
    __VA_ARGS__ }

/**
 * @brief USB raw 16-bit string initialization.
 *
 * Macro that creates header for raw values passed into descriptor.
 * Values must be of the uint16_t type and separated by commas.
 *
 * @param[in] ... comma-separated values.
 *
 * @return String descriptor initialization data.
 */
#define APP_USBD_STRING_RAW16_DESC(...) (const uint8_t *) ((const uint16_t[]){                     \
    0x00,  /* NULL character at start to differentiate from normal string */                       \
    (0xff & (sizeof((uint16_t[]){__VA_ARGS__}) + 2)) |                                             \
    ((uint16_t)APP_USBD_DESCRIPTOR_STRING) << 8,                                                   \
    __VA_ARGS__ })

/**
 * @brief USB string descriptors IDs
 */
typedef enum {
    APP_USBD_STRING_ID_LANGIDS = 0,  /**< Supported language identifiers */

    /// Placeholders used only for alignement of user strings. Do not use or modify them.

#if (APP_USBD_STRING_ID_MANUFACTURER != 0)
    APP_USBD_STRING_ID_MANUFACTURER_PLACEHOLDER = APP_USBD_STRING_ID_MANUFACTURER,
#endif // (APP_USBD_STRING_ID_MANUFACTURER != 0)

#if (APP_USBD_STRING_ID_PRODUCT != 0)
    APP_USBD_STRING_ID_PRODUCT_PLACEHOLDER = APP_USBD_STRING_ID_PRODUCT,
#endif // (APP_USBD_STRING_ID_PRODUCT != 0)

#if (APP_USBD_STRING_ID_SERIAL != 0)
    APP_USBD_STRING_ID_SERIAL_PLACEHOLDER = APP_USBD_STRING_ID_SERIAL,
#endif // (APP_USBD_STRING_ID_SERIAL != 0)

#if (APP_USBD_STRING_ID_CONFIGURATION != 0)
    APP_USBD_STRING_ID_CONFIGURATION_PLACEHOLDER = APP_USBD_STRING_ID_CONFIGURATION,
#endif // (APP_USBD_STRING_ID_CONFIGURATION != 0)

#define X(mnemonic, str_idx, ...) mnemonic str_idx,
    APP_USBD_STRINGS_USER
#undef X

    APP_USBD_STRING_ID_CNT           /**< Total number of identifiers. */
} app_usbd_string_desc_idx_t;

/**
 * @brief Get string descriptor.
 *
 * @param[in] idx    String descriptor index.
 * @param[in] langid Selected language for the string.
 * @return String descriptor, or NULL if it does not exist.
 * */
uint16_t const * app_usbd_string_desc_get(uint8_t idx, uint16_t langid);

/**
 * @brief Get string length.
 *
 * Function for getting string length from descriptor (descriptor returned by @ref app_usbd_string_desc_get).
 *
 * @param[in] p_str String descriptor pointer.
 * @return Total descriptor length in bytes.
 */
static inline size_t app_usbd_string_desc_length(uint16_t const * p_str)
{
    return ((const app_usbd_descriptor_string_t *)p_str)->bLength;
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_STRING_DESC_H__ */
