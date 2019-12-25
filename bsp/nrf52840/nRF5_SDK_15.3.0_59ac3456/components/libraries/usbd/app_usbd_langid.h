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

#ifndef APP_USBD_LANGID_H__
#define APP_USBD_LANGID_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * @brief This file contains LANGID variable type with all defined values.
 *
 * This file was created using Language Identifiers (LANGIDs) 3/29/00 Version 1.0,
 * available on USB web page:
 * http://www.usb.org/developers/docs/USB_LANGIDs.pdf
 *
 * @note
 * Do not include this file directly to the project.
 * It is included by @file app_usbd_request.h.
 */

/**
 * Offset of the lowest bit of primary language identifier.
 * @sa app_usbd_langid_t
 */
#define APP_USB_LANG_OFFSET 0

/**
 * Bitmask for a primary language identifier.
 * @sa app_usbd_langid_t
 */
#define APP_USB_LANG_MASK  BF_MASK(10, APP_USB_LANG_OFFSET)

/**
 * Macro for defining language identifier.
 *
 * @param x Language identifier value.
 */
#define APP_USB_LANG_DEF(x) ((x) << (APP_USB_LANG_OFFSET))

/**
 * Offset of the lowest bit of sublanguage identifier.
 * @sa app_usbd_langid_t
 */
#define APP_USB_SUBLANG_OFFSET 10

/**
 * Bitmask for a sublanguage identifier.
 * @sa app_usbd_langid_t
 */
#define APP_USB_SUBLANG_MASK  BF_MASK(6, APP_USB_SUBLANG_OFFSET)

/**
 * Macro for defining language identifier.
 *
 * @param x Language identifier value.
 */
#define APP_USB_SUBLANG_DEF(x) ((x) << (APP_USB_SUBLANG_OFFSET))

/**
 * @brief Primary language identifiers.
 *
 * Mnemonics for primary language identifiers.
 * This mnemonics can be combined using the logical OR operator with @ref app_usbd_langid_sub_t.
 */
typedef enum
{
    APP_USBD_LANG_ARABIC     = APP_USB_LANG_DEF(0x01U), /**< Arabic */
    APP_USBD_LANG_BULGARIAN  = APP_USB_LANG_DEF(0x02U), /**< Bulgarian */
    APP_USBD_LANG_CATALAN    = APP_USB_LANG_DEF(0x03U), /**< Catalan */
    APP_USBD_LANG_CHINESE    = APP_USB_LANG_DEF(0x04U), /**< Chinese */
    APP_USBD_LANG_CZECH      = APP_USB_LANG_DEF(0x05U), /**< Czech */
    APP_USBD_LANG_DANISH     = APP_USB_LANG_DEF(0x06U), /**< Danish */
    APP_USBD_LANG_GERMAN     = APP_USB_LANG_DEF(0x07U), /**< German */
    APP_USBD_LANG_GREEK      = APP_USB_LANG_DEF(0x08U), /**< Greek */
    APP_USBD_LANG_ENGLISH    = APP_USB_LANG_DEF(0x09U), /**< English */
    APP_USBD_LANG_SPANISH    = APP_USB_LANG_DEF(0x0aU), /**< Spanish */
    APP_USBD_LANG_FINNISH    = APP_USB_LANG_DEF(0x0bU), /**< Finnish */
    APP_USBD_LANG_FRENCH     = APP_USB_LANG_DEF(0x0cU), /**< French */
    APP_USBD_LANG_HEBREW     = APP_USB_LANG_DEF(0x0dU), /**< Hebrew */
    APP_USBD_LANG_HUNGARIAN  = APP_USB_LANG_DEF(0x0eU), /**< Hungarian */
    APP_USBD_LANG_ICELANDIC  = APP_USB_LANG_DEF(0x0fU), /**< Icelandic */
    APP_USBD_LANG_ITALIAN    = APP_USB_LANG_DEF(0x10U), /**< Italian */
    APP_USBD_LANG_JAPANESE   = APP_USB_LANG_DEF(0x11U), /**< Japanese */
    APP_USBD_LANG_KOREAN     = APP_USB_LANG_DEF(0x12U), /**< Korean */
    APP_USBD_LANG_DUTCH      = APP_USB_LANG_DEF(0x13U), /**< Dutch */
    APP_USBD_LANG_NORWEGIAN  = APP_USB_LANG_DEF(0x14U), /**< Norwegian */
    APP_USBD_LANG_POLISH     = APP_USB_LANG_DEF(0x15U), /**< Polish */
    APP_USBD_LANG_PORTUGUESE = APP_USB_LANG_DEF(0x16U), /**< Portuguese */
    APP_USBD_LANG_ROMANIAN   = APP_USB_LANG_DEF(0x18U), /**< Romanian */
    APP_USBD_LANG_RUSSIAN    = APP_USB_LANG_DEF(0x19U), /**< Russian */
    APP_USBD_LANG_CROATIAN   = APP_USB_LANG_DEF(0x1aU), /**< Croatian */
    APP_USBD_LANG_SERBIAN    = APP_USB_LANG_DEF(0x1aU), /**< Serbian */
    APP_USBD_LANG_SLOVAK     = APP_USB_LANG_DEF(0x1bU), /**< Slovak */
    APP_USBD_LANG_ALBANIAN   = APP_USB_LANG_DEF(0x1cU), /**< Albanian */
    APP_USBD_LANG_SWEDISH    = APP_USB_LANG_DEF(0x1dU), /**< Swedish */
    APP_USBD_LANG_THAI       = APP_USB_LANG_DEF(0x1eU), /**< Thai */
    APP_USBD_LANG_TURKISH    = APP_USB_LANG_DEF(0x1fU), /**< Turkish */
    APP_USBD_LANG_URDU       = APP_USB_LANG_DEF(0x20U), /**< Urdu */
    APP_USBD_LANG_INDONESIAN = APP_USB_LANG_DEF(0x21U), /**< Indonesian */
    APP_USBD_LANG_UKRANIAN   = APP_USB_LANG_DEF(0x22U), /**< Ukrainian */
    APP_USBD_LANG_BELARUSIAN = APP_USB_LANG_DEF(0x23U), /**< Belarusian */
    APP_USBD_LANG_SLOVENIAN  = APP_USB_LANG_DEF(0x24U), /**< Slovenian */
    APP_USBD_LANG_ESTONIAN   = APP_USB_LANG_DEF(0x25U), /**< Estonian */
    APP_USBD_LANG_LATVIAN    = APP_USB_LANG_DEF(0x26U), /**< Latvian */
    APP_USBD_LANG_LITHUANIAN = APP_USB_LANG_DEF(0x27U), /**< Lithuanian */
    APP_USBD_LANG_FARSI      = APP_USB_LANG_DEF(0x29U), /**< Farsi */
    APP_USBD_LANG_VIETNAMESE = APP_USB_LANG_DEF(0x2aU), /**< Vietnamese */
    APP_USBD_LANG_ARMENIAN   = APP_USB_LANG_DEF(0x2bU), /**< Armenian */
    APP_USBD_LANG_AZERI      = APP_USB_LANG_DEF(0x2cU), /**< Azeri */
    APP_USBD_LANG_BASQUE     = APP_USB_LANG_DEF(0x2dU), /**< Basque */
    APP_USBD_LANG_MACEDONIAN = APP_USB_LANG_DEF(0x2fU), /**< Macedonian */
    APP_USBD_LANG_AFRIKAANS  = APP_USB_LANG_DEF(0x36U), /**< Afrikaans */
    APP_USBD_LANG_GEORGIAN   = APP_USB_LANG_DEF(0x37U), /**< Georgian */
    APP_USBD_LANG_FAEROESE   = APP_USB_LANG_DEF(0x38U), /**< Faeroese */
    APP_USBD_LANG_HINDI      = APP_USB_LANG_DEF(0x39U), /**< Hindi */
    APP_USBD_LANG_MALAY      = APP_USB_LANG_DEF(0x3eU), /**< Malay */
    APP_USBD_LANG_KAZAK      = APP_USB_LANG_DEF(0x3fU), /**< Kazak */
    APP_USBD_LANG_SWAHILI    = APP_USB_LANG_DEF(0x41U), /**< Swahili */
    APP_USBD_LANG_UZBEK      = APP_USB_LANG_DEF(0x43U), /**< Uzbek */
    APP_USBD_LANG_TATAR      = APP_USB_LANG_DEF(0x44U), /**< Tatar */
    APP_USBD_LANG_BENGALI    = APP_USB_LANG_DEF(0x45U), /**< Bengali */
    APP_USBD_LANG_PUNJABI    = APP_USB_LANG_DEF(0x46U), /**< Punjabi */
    APP_USBD_LANG_GUJARATI   = APP_USB_LANG_DEF(0x47U), /**< Gujarati */
    APP_USBD_LANG_ORIYA      = APP_USB_LANG_DEF(0x48U), /**< Oriya */
    APP_USBD_LANG_TAMIL      = APP_USB_LANG_DEF(0x49U), /**< Tamil */
    APP_USBD_LANG_TELUGU     = APP_USB_LANG_DEF(0x4aU), /**< Telugu */
    APP_USBD_LANG_KANNADA    = APP_USB_LANG_DEF(0x4bU), /**< Kannada */
    APP_USBD_LANG_MALAYALAM  = APP_USB_LANG_DEF(0x4cU), /**< Malayalam */
    APP_USBD_LANG_ASSAMESE   = APP_USB_LANG_DEF(0x4dU), /**< Assamese */
    APP_USBD_LANG_MARATHI    = APP_USB_LANG_DEF(0x4eU), /**< Marathi */
    APP_USBD_LANG_SANSKRIT   = APP_USB_LANG_DEF(0x4fU), /**< Sanskrit */
    APP_USBD_LANG_KONKANI    = APP_USB_LANG_DEF(0x57U), /**< Konkani */
    APP_USBD_LANG_MANIPURI   = APP_USB_LANG_DEF(0x58U), /**< Manipuri */
    APP_USBD_LANG_SINDHI     = APP_USB_LANG_DEF(0x59U), /**< Sindhi */
    APP_USBD_LANG_KASHMIRI   = APP_USB_LANG_DEF(0x60U), /**< Kashmiri */
    APP_USBD_LANG_NEPALI     = APP_USB_LANG_DEF(0x61U), /**< Nepali */
    APP_USBD_LANG_HID        = APP_USB_LANG_DEF(0xffU), /**< Reserved for USB HID Class use. */
} app_usbd_langid_primary_t;

/**
 * @brief Sublanguage identifiers.
 *
 * Mnemonics with sublanguage values.
 * Use them in combination with @ref app_usbd_langid_primary_t.
 */
typedef enum
{
    APP_USBD_SUBLANG_ARABIC_SAUDI_ARABIA        = APP_USB_SUBLANG_DEF(0x01U), /**< Arabic (Saudi Arabia) */
    APP_USBD_SUBLANG_ARABIC_IRAQ                = APP_USB_SUBLANG_DEF(0x02U), /**< Arabic (Iraq) */
    APP_USBD_SUBLANG_ARABIC_EGYPT               = APP_USB_SUBLANG_DEF(0x03U), /**< Arabic (Egypt) */
    APP_USBD_SUBLANG_ARABIC_LIBYA               = APP_USB_SUBLANG_DEF(0x04U), /**< Arabic (Libya) */
    APP_USBD_SUBLANG_ARABIC_ALGERIA             = APP_USB_SUBLANG_DEF(0x05U), /**< Arabic (Algeria) */
    APP_USBD_SUBLANG_ARABIC_MOROCCO             = APP_USB_SUBLANG_DEF(0x06U), /**< Arabic (Morocco) */
    APP_USBD_SUBLANG_ARABIC_TUNISIA             = APP_USB_SUBLANG_DEF(0x07U), /**< Arabic (Tunisia) */
    APP_USBD_SUBLANG_ARABIC_OMAN                = APP_USB_SUBLANG_DEF(0x08U), /**< Arabic (Oman) */
    APP_USBD_SUBLANG_ARABIC_YEMEN               = APP_USB_SUBLANG_DEF(0x09U), /**< Arabic (Yemen) */
    APP_USBD_SUBLANG_ARABIC_SYRIA               = APP_USB_SUBLANG_DEF(0x10U), /**< Arabic (Syria) */
    APP_USBD_SUBLANG_ARABIC_JORDAN              = APP_USB_SUBLANG_DEF(0x11U), /**< Arabic (Jordan) */
    APP_USBD_SUBLANG_ARABIC_LEBANON             = APP_USB_SUBLANG_DEF(0x12U), /**< Arabic (Lebanon) */
    APP_USBD_SUBLANG_ARABIC_KUWAIT              = APP_USB_SUBLANG_DEF(0x13U), /**< Arabic (Kuwait) */
    APP_USBD_SUBLANG_ARABIC_UAE                 = APP_USB_SUBLANG_DEF(0x14U), /**< Arabic (U.A.E.) */
    APP_USBD_SUBLANG_ARABIC_BAHRAIN             = APP_USB_SUBLANG_DEF(0x15U), /**< Arabic (Bahrain) */
    APP_USBD_SUBLANG_ARABIC_QATAR               = APP_USB_SUBLANG_DEF(0x16U), /**< Arabic (Qatar) */
    APP_USBD_SUBLANG_AZERI_CYRILLIC             = APP_USB_SUBLANG_DEF(0x01U), /**< Azeri (Cyrillic) */
    APP_USBD_SUBLANG_AZERI_LATIN                = APP_USB_SUBLANG_DEF(0x02U), /**< Azeri (Latin) */
    APP_USBD_SUBLANG_CHINESE_TRADITIONAL        = APP_USB_SUBLANG_DEF(0x01U), /**< Chinese (Traditional) */
    APP_USBD_SUBLANG_CHINESE_SIMPLIFIED         = APP_USB_SUBLANG_DEF(0x02U), /**< Chinese (Simplified) */
    APP_USBD_SUBLANG_CHINESE_HONGKONG           = APP_USB_SUBLANG_DEF(0x03U), /**< Chinese (Hong Kong SAR, PRC) */
    APP_USBD_SUBLANG_CHINESE_SINGAPORE          = APP_USB_SUBLANG_DEF(0x04U), /**< Chinese (Singapore) */
    APP_USBD_SUBLANG_CHINESE_MACAU              = APP_USB_SUBLANG_DEF(0x05U), /**< Chinese (Macau SAR) */
    APP_USBD_SUBLANG_DUTCH                      = APP_USB_SUBLANG_DEF(0x01U), /**< Dutch */
    APP_USBD_SUBLANG_DUTCH_BELGIAN              = APP_USB_SUBLANG_DEF(0x02U), /**< Dutch (Belgian) */
    APP_USBD_SUBLANG_ENGLISH_US                 = APP_USB_SUBLANG_DEF(0x01U), /**< English (US) */
    APP_USBD_SUBLANG_ENGLISH_UK                 = APP_USB_SUBLANG_DEF(0x02U), /**< English (UK) */
    APP_USBD_SUBLANG_ENGLISH_AUS                = APP_USB_SUBLANG_DEF(0x03U), /**< English (Australian) */
    APP_USBD_SUBLANG_ENGLISH_CAN                = APP_USB_SUBLANG_DEF(0x04U), /**< English (Canadian) */
    APP_USBD_SUBLANG_ENGLISH_NZ                 = APP_USB_SUBLANG_DEF(0x05U), /**< English (New Zealand) */
    APP_USBD_SUBLANG_ENGLISH_EIRE               = APP_USB_SUBLANG_DEF(0x06U), /**< English (Ireland) */
    APP_USBD_SUBLANG_ENGLISH_SOUTH_AFRICA       = APP_USB_SUBLANG_DEF(0x07U), /**< English (South Africa) */
    APP_USBD_SUBLANG_ENGLISH_JAMAICA            = APP_USB_SUBLANG_DEF(0x08U), /**< English (Jamaica) */
    APP_USBD_SUBLANG_ENGLISH_CARIBBEAN          = APP_USB_SUBLANG_DEF(0x09U), /**< English (Caribbean) */
    APP_USBD_SUBLANG_ENGLISH_BELIZE             = APP_USB_SUBLANG_DEF(0x0aU), /**< English (Belize) */
    APP_USBD_SUBLANG_ENGLISH_TRINIDAD           = APP_USB_SUBLANG_DEF(0x0bU), /**< English (Trinidad) */
    APP_USBD_SUBLANG_ENGLISH_PHILIPPINES        = APP_USB_SUBLANG_DEF(0x0cU), /**< English (Zimbabwe) */
    APP_USBD_SUBLANG_ENGLISH_ZIMBABWE           = APP_USB_SUBLANG_DEF(0x0dU), /**< English (Philippines) */
    APP_USBD_SUBLANG_FRENCH                     = APP_USB_SUBLANG_DEF(0x01U), /**< French */
    APP_USBD_SUBLANG_FRENCH_BELGIAN             = APP_USB_SUBLANG_DEF(0x02U), /**< French (Belgian) */
    APP_USBD_SUBLANG_FRENCH_CANADIAN            = APP_USB_SUBLANG_DEF(0x03U), /**< French (Canadian) */
    APP_USBD_SUBLANG_FRENCH_SWISS               = APP_USB_SUBLANG_DEF(0x04U), /**< French (Switzerland) */
    APP_USBD_SUBLANG_FRENCH_LUXEMBOURG          = APP_USB_SUBLANG_DEF(0x05U), /**< French (Luxembourg) */
    APP_USBD_SUBLANG_FRENCH_MONACO              = APP_USB_SUBLANG_DEF(0x06U), /**< French (Monaco) */
    APP_USBD_SUBLANG_GERMAN                     = APP_USB_SUBLANG_DEF(0x01U), /**< German */
    APP_USBD_SUBLANG_GERMAN_SWISS               = APP_USB_SUBLANG_DEF(0x02U), /**< German (Switzerland) */
    APP_USBD_SUBLANG_GERMAN_AUSTRIAN            = APP_USB_SUBLANG_DEF(0x03U), /**< German (Austria) */
    APP_USBD_SUBLANG_GERMAN_LUXEMBOURG          = APP_USB_SUBLANG_DEF(0x04U), /**< German (Luxembourg) */
    APP_USBD_SUBLANG_GERMAN_LIECHTENSTEIN       = APP_USB_SUBLANG_DEF(0x05U), /**< German (Liechtenstein) */
    APP_USBD_SUBLANG_ITALIAN                    = APP_USB_SUBLANG_DEF(0x01U), /**< Italian */
    APP_USBD_SUBLANG_ITALIAN_SWISS              = APP_USB_SUBLANG_DEF(0x02U), /**< Italian (Switzerland) */
    APP_USBD_SUBLANG_KASHMIRI_INDIA             = APP_USB_SUBLANG_DEF(0x02U), /**< Kashmiri (India) */
    APP_USBD_SUBLANG_KOREAN                     = APP_USB_SUBLANG_DEF(0x01U), /**< Korean */
    APP_USBD_SUBLANG_LITHUANIAN                 = APP_USB_SUBLANG_DEF(0x01U), /**< Lithuanian */
    APP_USBD_SUBLANG_MALAY_MALAYSIA             = APP_USB_SUBLANG_DEF(0x01U), /**< Malay (Malaysia) */
    APP_USBD_SUBLANG_MALAY_BRUNEI_DARUSSALAM    = APP_USB_SUBLANG_DEF(0x02U), /**< Malay (Brunei Darassalam) */
    APP_USBD_SUBLANG_NEPALI_INDIA               = APP_USB_SUBLANG_DEF(0x02U), /**< Nepali (India) */
    APP_USBD_SUBLANG_NORWEGIAN_BOKMAL           = APP_USB_SUBLANG_DEF(0x01U), /**< Norwegian (Bokmal) */
    APP_USBD_SUBLANG_NORWEGIAN_NYNORSK          = APP_USB_SUBLANG_DEF(0x02U), /**< Norwegian (Nynorsk) */
    APP_USBD_SUBLANG_PORTUGUESE                 = APP_USB_SUBLANG_DEF(0x01U), /**< Portuguese */
    APP_USBD_SUBLANG_PORTUGUESE_BRAZILIAN       = APP_USB_SUBLANG_DEF(0x02U), /**< Portuguese (Brazil) */
    APP_USBD_SUBLANG_SERBIAN_LATIN              = APP_USB_SUBLANG_DEF(0x02U), /**< Serbian (Latin) */
    APP_USBD_SUBLANG_SERBIAN_CYRILLIC           = APP_USB_SUBLANG_DEF(0x03U), /**< Serbian (Cyrillic) */
    APP_USBD_SUBLANG_SPANISH                    = APP_USB_SUBLANG_DEF(0x01U), /**< Spanish (Traditional) */
    APP_USBD_SUBLANG_SPANISH_MEXICAN            = APP_USB_SUBLANG_DEF(0x02U), /**< Spanish (Mexican) */
    APP_USBD_SUBLANG_SPANISH_MODERN             = APP_USB_SUBLANG_DEF(0x03U), /**< Spanish (Modern) */
    APP_USBD_SUBLANG_SPANISH_GUATEMALA          = APP_USB_SUBLANG_DEF(0x04U), /**< Spanish (Guatemala) */
    APP_USBD_SUBLANG_SPANISH_COSTA_RICA         = APP_USB_SUBLANG_DEF(0x05U), /**< Spanish (Costa Rica) */
    APP_USBD_SUBLANG_SPANISH_PANAMA             = APP_USB_SUBLANG_DEF(0x06U), /**< Spanish (Panama) */
    APP_USBD_SUBLANG_SPANISH_DOMINICAN_REPUBLIC = APP_USB_SUBLANG_DEF(0x07U), /**< Spanish (Dominican Republic) */
    APP_USBD_SUBLANG_SPANISH_VENEZUELA          = APP_USB_SUBLANG_DEF(0x08U), /**< Spanish (Venezuela) */
    APP_USBD_SUBLANG_SPANISH_COLOMBIA           = APP_USB_SUBLANG_DEF(0x09U), /**< Spanish (Colombia) */
    APP_USBD_SUBLANG_SPANISH_PERU               = APP_USB_SUBLANG_DEF(0x0aU), /**< Spanish (Peru) */
    APP_USBD_SUBLANG_SPANISH_ARGENTINA          = APP_USB_SUBLANG_DEF(0x0bU), /**< Spanish (Argentina) */
    APP_USBD_SUBLANG_SPANISH_ECUADOR            = APP_USB_SUBLANG_DEF(0x0cU), /**< Spanish (Ecuador) */
    APP_USBD_SUBLANG_SPANISH_CHILE              = APP_USB_SUBLANG_DEF(0x0dU), /**< Spanish (Chile) */
    APP_USBD_SUBLANG_SPANISH_URUGUAY            = APP_USB_SUBLANG_DEF(0x0eU), /**< Spanish (Uruguay) */
    APP_USBD_SUBLANG_SPANISH_PARAGUAY           = APP_USB_SUBLANG_DEF(0x0fU), /**< Spanish (Paraguay) */
    APP_USBD_SUBLANG_SPANISH_BOLIVIA            = APP_USB_SUBLANG_DEF(0x10U), /**< Spanish (Bolivia) */
    APP_USBD_SUBLANG_SPANISH_EL_SALVADOR        = APP_USB_SUBLANG_DEF(0x11U), /**< Spanish (El Salvador) */
    APP_USBD_SUBLANG_SPANISH_HONDURAS           = APP_USB_SUBLANG_DEF(0x12U), /**< Spanish (Honduras) */
    APP_USBD_SUBLANG_SPANISH_NICARAGUA          = APP_USB_SUBLANG_DEF(0x13U), /**< Spanish (Nicaragua) */
    APP_USBD_SUBLANG_SPANISH_PUERTO_RICO        = APP_USB_SUBLANG_DEF(0x14U), /**< Spanish (Puerto Rico) */
    APP_USBD_SUBLANG_SWEDISH                    = APP_USB_SUBLANG_DEF(0x01U), /**< Swedish */
    APP_USBD_SUBLANG_SWEDISH_FINLAND            = APP_USB_SUBLANG_DEF(0x02U), /**< Swedish (Finland) */
    APP_USBD_SUBLANG_URDU_PAKISTAN              = APP_USB_SUBLANG_DEF(0x01U), /**< Urdu (Pakistan) */
    APP_USBD_SUBLANG_URDU_INDIA                 = APP_USB_SUBLANG_DEF(0x02U), /**< Urdu (India) */
    APP_USBD_SUBLANG_UZBEK_LATIN                = APP_USB_SUBLANG_DEF(0x01U), /**< Uzbek (Latin) */
    APP_USBD_SUBLANG_UZBEK_CYRILLIC             = APP_USB_SUBLANG_DEF(0x02U), /**< Uzbek (Cyrillic) */
    APP_USBD_SUBLANG_HID_USAGE_DATA_DESCRIPTOR  = APP_USB_SUBLANG_DEF(0x01U), /**< HID (Usage Data Descriptor) */
    APP_USBD_SUBLANG_HID_VENDOR_DEFINED_1       = APP_USB_SUBLANG_DEF(0x3cU), /**< HID (Vendor Defined 1) */
    APP_USBD_SUBLANG_HID_VENDOR_DEFINED_2       = APP_USB_SUBLANG_DEF(0x3dU), /**< HID (Vendor Defined 2) */
    APP_USBD_SUBLANG_HID_VENDOR_DEFINED_3       = APP_USB_SUBLANG_DEF(0x3eU), /**< HID (Vendor Defined 3) */
    APP_USBD_SUBLANG_HID_VENDOR_DEFINED_4       = APP_USB_SUBLANG_DEF(0x3fU), /**< HID (Vendor Defined 4) */
} app_usbd_langid_sub_t;

/**
 * @brief LANGID variable.
 *
 * The LANGID value is composed of:
 * - 10 bits (9-0) of Primary Language Identifier,
 * - 6 bits (15-10) of Sublanguage Identifier.
 *
 * @sa app_usbd_langid_primary_t
 * @sa app_usbd_langid_sub_t
 */
typedef uint16_t app_usbd_langid_t;

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_LANGID_H__ */
