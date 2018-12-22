/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "sdk_common.h"
#include "app_usbd.h"
#include "app_usbd_string_config.h"

/**
 * @defgroup app_usbd_string_desc USBD string descriptors
 * @ingroup app_usbd
 *
 * @brief @tagAPI52840 USBD string descriptors management.
 * @{
 */

/**
 * @brief USB string initialization
 *
 * Macro that creates initialization values for USB string.
 * The format contains header and string itself.
 * The string should be declared as an array of uint16_t type.
 *
 * @param[in] ... Comma separated string letters or language ID.
 * @return String descriptor initialization data.
 */
#define APP_USBD_STRING_DESC(...) (const uint16_t[]){  \
    (0xff & (sizeof((uint16_t[]){__VA_ARGS__}) + 2)) | \
    ((uint16_t)APP_USBD_DESCRIPTOR_STRING) << 8,       \
    __VA_ARGS__ }

/**
 * @brief USB string descriptors ID's
 */
typedef enum {
    APP_USBD_STRING_ID_LANGIDS = 0,  /**< Supported language identifiers */
    APP_USBD_STRING_ID_MANUFACTURER, /**< Manufacturer name */
    APP_USBD_STRING_ID_PRODUCT,      /**< Product name */
    APP_USBD_STRING_ID_SERIAL,       /**< Serial number */

#define X(mnemonic, str_idx, ...) mnemonic str_idx,
    APP_USBD_STRINGS_USER
#undef X

    APP_USBD_STRING_ID_CNT           /**< Total number of identifiers */
} app_usbd_string_desc_idx_t;

/**
 * @brief Get string descriptor
 *
 * @param[in] idx    String descriptor index
 * @param[in] langid Selected language for the string
 * @return String descriptor or NULL if not exist
 * */
uint16_t const * app_usbd_string_desc_get(app_usbd_string_desc_idx_t idx, uint16_t langid);

/**
 * @brief Get string length
 *
 * Function to get string length from descriptor (descriptor returned by @ref app_usbd_string_desc_get)
 *
 * @param[in] p_str String descriptor pointer
 * @return Total descriptor length in bytes
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
