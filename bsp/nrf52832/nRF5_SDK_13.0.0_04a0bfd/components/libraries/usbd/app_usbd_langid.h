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

#ifndef APP_USBD_LANGID_H__
#define APP_USBD_LANGID_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file
 * @brief This file contains LANGID variable type with all defined values
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
 * Offset of the lowest bit of primary language identifier
 * @sa app_usbd_langid_t
 */
#define APP_USB_LANG_OFFSET 0

/**
 * Bitmask for a primary language identifier
 * @sa app_usbd_langid_t
 */
#define APP_USB_LANG_MASK  BF_MASK(10, APP_USB_LANG_OFFSET)

/**
 * Offset of the lowest bit of sub-language identifier
 * @sa app_usbd_langid_t
 */
#define APP_USB_SUBLANG_OFFSET 10

/**
 * Bitmask for a sub-language identifier
 * @sa app_usbd_langid_t
 */
#define APP_USB_SUBLANG_MASK  BF_MASK(6, APP_USB_SUBLANG_OFFSET)

/**
 * @brief Primary language identifiers
 *
 * Mnemonics for primary language identifiers.
 * This mnemonics can be combined using logical OR operator with @ref app_usbd_langid_sub_t.
 */
typedef enum
{
    APP_USBD_LANG_ARABIC     = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Arabic */
    APP_USBD_LANG_BULGARIAN  = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Bulgarian */
    APP_USBD_LANG_CATALAN    = 0x03U << ( APP_USB_LANG_OFFSET ), /**< Catalan */
    APP_USBD_LANG_CHINESE    = 0x04U << ( APP_USB_LANG_OFFSET ), /**< Chinese */
    APP_USBD_LANG_CZECH      = 0x05U << ( APP_USB_LANG_OFFSET ), /**< Czech */
    APP_USBD_LANG_DANISH     = 0x06U << ( APP_USB_LANG_OFFSET ), /**< Danish */
    APP_USBD_LANG_GERMAN     = 0x07U << ( APP_USB_LANG_OFFSET ), /**< German */
    APP_USBD_LANG_GREEK      = 0x08U << ( APP_USB_LANG_OFFSET ), /**< Greek */
    APP_USBD_LANG_ENGLISH    = 0x09U << ( APP_USB_LANG_OFFSET ), /**< English */
    APP_USBD_LANG_SPANISH    = 0x0aU << ( APP_USB_LANG_OFFSET ), /**< Spanish */
    APP_USBD_LANG_FINNISH    = 0x0bU << ( APP_USB_LANG_OFFSET ), /**< Finnish */
    APP_USBD_LANG_FRENCH     = 0x0cU << ( APP_USB_LANG_OFFSET ), /**< French */
    APP_USBD_LANG_HEBREW     = 0x0dU << ( APP_USB_LANG_OFFSET ), /**< Hebrew */
    APP_USBD_LANG_HUNGARIAN  = 0x0eU << ( APP_USB_LANG_OFFSET ), /**< Hungarian */
    APP_USBD_LANG_ICELANDIC  = 0x0fU << ( APP_USB_LANG_OFFSET ), /**< Icelandic */
    APP_USBD_LANG_ITALIAN    = 0x10U << ( APP_USB_LANG_OFFSET ), /**< Italian */
    APP_USBD_LANG_JAPANESE   = 0x11U << ( APP_USB_LANG_OFFSET ), /**< Japanese */
    APP_USBD_LANG_KOREAN     = 0x12U << ( APP_USB_LANG_OFFSET ), /**< Korean */
    APP_USBD_LANG_DUTCH      = 0x13U << ( APP_USB_LANG_OFFSET ), /**< Dutch */
    APP_USBD_LANG_NORWEGIAN  = 0x14U << ( APP_USB_LANG_OFFSET ), /**< Norwegian */
    APP_USBD_LANG_POLISH     = 0x15U << ( APP_USB_LANG_OFFSET ), /**< Polish */
    APP_USBD_LANG_PORTUGUESE = 0x16U << ( APP_USB_LANG_OFFSET ), /**< Portuguese */
    APP_USBD_LANG_ROMANIAN   = 0x18U << ( APP_USB_LANG_OFFSET ), /**< Romanian */
    APP_USBD_LANG_RUSSIAN    = 0x19U << ( APP_USB_LANG_OFFSET ), /**< Russian */
    APP_USBD_LANG_CROATIAN   = 0x1aU << ( APP_USB_LANG_OFFSET ), /**< Croatian */
    APP_USBD_LANG_SERBIAN    = 0x1aU << ( APP_USB_LANG_OFFSET ), /**< Serbian */
    APP_USBD_LANG_SLOVAK     = 0x1bU << ( APP_USB_LANG_OFFSET ), /**< Slovak */
    APP_USBD_LANG_ALBANIAN   = 0x1cU << ( APP_USB_LANG_OFFSET ), /**< Albanian */
    APP_USBD_LANG_SWEDISH    = 0x1dU << ( APP_USB_LANG_OFFSET ), /**< Swedish */
    APP_USBD_LANG_THAI       = 0x1eU << ( APP_USB_LANG_OFFSET ), /**< Thai */
    APP_USBD_LANG_TURKISH    = 0x1fU << ( APP_USB_LANG_OFFSET ), /**< Turkish */
    APP_USBD_LANG_URDU       = 0x20U << ( APP_USB_LANG_OFFSET ), /**< Urdu */
    APP_USBD_LANG_INDONESIAN = 0x21U << ( APP_USB_LANG_OFFSET ), /**< Indonesian */
    APP_USBD_LANG_UKRANIAN   = 0x22U << ( APP_USB_LANG_OFFSET ), /**< Ukrainian */
    APP_USBD_LANG_BELARUSIAN = 0x23U << ( APP_USB_LANG_OFFSET ), /**< Belarusian */
    APP_USBD_LANG_SLOVENIAN  = 0x24U << ( APP_USB_LANG_OFFSET ), /**< Slovenian */
    APP_USBD_LANG_ESTONIAN   = 0x25U << ( APP_USB_LANG_OFFSET ), /**< Estonian */
    APP_USBD_LANG_LATVIAN    = 0x26U << ( APP_USB_LANG_OFFSET ), /**< Latvian */
    APP_USBD_LANG_LITHUANIAN = 0x27U << ( APP_USB_LANG_OFFSET ), /**< Lithuanian */
    APP_USBD_LANG_FARSI      = 0x29U << ( APP_USB_LANG_OFFSET ), /**< Farsi */
    APP_USBD_LANG_VIETNAMESE = 0x2aU << ( APP_USB_LANG_OFFSET ), /**< Vietnamese */
    APP_USBD_LANG_ARMENIAN   = 0x2bU << ( APP_USB_LANG_OFFSET ), /**< Armenian */
    APP_USBD_LANG_AZERI      = 0x2cU << ( APP_USB_LANG_OFFSET ), /**< Azeri */
    APP_USBD_LANG_BASQUE     = 0x2dU << ( APP_USB_LANG_OFFSET ), /**< Basque */
    APP_USBD_LANG_MACEDONIAN = 0x2fU << ( APP_USB_LANG_OFFSET ), /**< Macedonian */
    APP_USBD_LANG_AFRIKAANS  = 0x36U << ( APP_USB_LANG_OFFSET ), /**< Afrikaans */
    APP_USBD_LANG_GEORGIAN   = 0x37U << ( APP_USB_LANG_OFFSET ), /**< Georgian */
    APP_USBD_LANG_FAEROESE   = 0x38U << ( APP_USB_LANG_OFFSET ), /**< Faeroese */
    APP_USBD_LANG_HINDI      = 0x39U << ( APP_USB_LANG_OFFSET ), /**< Hindi */
    APP_USBD_LANG_MALAY      = 0x3eU << ( APP_USB_LANG_OFFSET ), /**< Malay */
    APP_USBD_LANG_KAZAK      = 0x3fU << ( APP_USB_LANG_OFFSET ), /**< Kazak */
    APP_USBD_LANG_SWAHILI    = 0x41U << ( APP_USB_LANG_OFFSET ), /**< Swahili */
    APP_USBD_LANG_UZBEK      = 0x43U << ( APP_USB_LANG_OFFSET ), /**< Uzbek */
    APP_USBD_LANG_TATAR      = 0x44U << ( APP_USB_LANG_OFFSET ), /**< Tatar */
    APP_USBD_LANG_BENGALI    = 0x45U << ( APP_USB_LANG_OFFSET ), /**< Bengali */
    APP_USBD_LANG_PUNJABI    = 0x46U << ( APP_USB_LANG_OFFSET ), /**< Punjabi */
    APP_USBD_LANG_GUJARATI   = 0x47U << ( APP_USB_LANG_OFFSET ), /**< Gujarati */
    APP_USBD_LANG_ORIYA      = 0x48U << ( APP_USB_LANG_OFFSET ), /**< Oriya */
    APP_USBD_LANG_TAMIL      = 0x49U << ( APP_USB_LANG_OFFSET ), /**< Tamil */
    APP_USBD_LANG_TELUGU     = 0x4aU << ( APP_USB_LANG_OFFSET ), /**< Telugu */
    APP_USBD_LANG_KANNADA    = 0x4bU << ( APP_USB_LANG_OFFSET ), /**< Kannada */
    APP_USBD_LANG_MALAYALAM  = 0x4cU << ( APP_USB_LANG_OFFSET ), /**< Malayalam */
    APP_USBD_LANG_ASSAMESE   = 0x4dU << ( APP_USB_LANG_OFFSET ), /**< Assamese */
    APP_USBD_LANG_MARATHI    = 0x4eU << ( APP_USB_LANG_OFFSET ), /**< Marathi */
    APP_USBD_LANG_SANSKRIT   = 0x4fU << ( APP_USB_LANG_OFFSET ), /**< Sanskrit */
    APP_USBD_LANG_KONKANI    = 0x57U << ( APP_USB_LANG_OFFSET ), /**< Konkani */
    APP_USBD_LANG_MANIPURI   = 0x58U << ( APP_USB_LANG_OFFSET ), /**< Manipuri */
    APP_USBD_LANG_SINDHI     = 0x59U << ( APP_USB_LANG_OFFSET ), /**< Sindhi */
    APP_USBD_LANG_KASHMIRI   = 0x60U << ( APP_USB_LANG_OFFSET ), /**< Kashmiri */
    APP_USBD_LANG_NEPALI     = 0x61U << ( APP_USB_LANG_OFFSET ), /**< Nepali */
    APP_USBD_LANG_HID        = 0xffU << ( APP_USB_LANG_OFFSET ), /**< Reserved for USB HID Class use */
}app_usbd_langid_primary_t;

/**
 * @brief Sublanguage identifiers
 *
 * Mnemonics with sublanguage values.
 * Use them in combination with @ref app_usbd_langid_primary_t.
 */
typedef enum
{
    APP_USBD_SUBLANG_ARABIC_SAUDI_ARABIA        = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Saudi Arabia) */
    APP_USBD_SUBLANG_ARABIC_IRAQ                = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Iraq) */
    APP_USBD_SUBLANG_ARABIC_EGYPT               = 0x03U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Egypt) */
    APP_USBD_SUBLANG_ARABIC_LIBYA               = 0x04U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Libya) */
    APP_USBD_SUBLANG_ARABIC_ALGERIA             = 0x05U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Algeria) */
    APP_USBD_SUBLANG_ARABIC_MOROCCO             = 0x06U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Morocco) */
    APP_USBD_SUBLANG_ARABIC_TUNISIA             = 0x07U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Tunisia) */
    APP_USBD_SUBLANG_ARABIC_OMAN                = 0x08U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Oman) */
    APP_USBD_SUBLANG_ARABIC_YEMEN               = 0x09U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Yemen) */
    APP_USBD_SUBLANG_ARABIC_SYRIA               = 0x10U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Syria) */
    APP_USBD_SUBLANG_ARABIC_JORDAN              = 0x11U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Jordan) */
    APP_USBD_SUBLANG_ARABIC_LEBANON             = 0x12U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Lebanon) */
    APP_USBD_SUBLANG_ARABIC_KUWAIT              = 0x13U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Kuwait) */
    APP_USBD_SUBLANG_ARABIC_UAE                 = 0x14U << ( APP_USB_LANG_OFFSET ), /**< Arabic (U.A.E.) */
    APP_USBD_SUBLANG_ARABIC_BAHRAIN             = 0x15U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Bahrain) */
    APP_USBD_SUBLANG_ARABIC_QATAR               = 0x16U << ( APP_USB_LANG_OFFSET ), /**< Arabic (Qatar) */
    APP_USBD_SUBLANG_AZERI_CYRILLIC             = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Azeri (Cyrillic) */
    APP_USBD_SUBLANG_AZERI_LATIN                = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Azeri (Latin) */
    APP_USBD_SUBLANG_CHINESE_TRADITIONAL        = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Chinese (Traditional) */
    APP_USBD_SUBLANG_CHINESE_SIMPLIFIED         = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Chinese (Simplified) */
    APP_USBD_SUBLANG_CHINESE_HONGKONG           = 0x03U << ( APP_USB_LANG_OFFSET ), /**< Chinese (Hong Kong SAR, PRC) */
    APP_USBD_SUBLANG_CHINESE_SINGAPORE          = 0x04U << ( APP_USB_LANG_OFFSET ), /**< Chinese (Singapore) */
    APP_USBD_SUBLANG_CHINESE_MACAU              = 0x05U << ( APP_USB_LANG_OFFSET ), /**< Chinese (Macau SAR) */
    APP_USBD_SUBLANG_DUTCH                      = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Dutch */
    APP_USBD_SUBLANG_DUTCH_BELGIAN              = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Dutch (Belgian) */
    APP_USBD_SUBLANG_ENGLISH_US                 = 0x01U << ( APP_USB_LANG_OFFSET ), /**< English (US) */
    APP_USBD_SUBLANG_ENGLISH_UK                 = 0x02U << ( APP_USB_LANG_OFFSET ), /**< English (UK) */
    APP_USBD_SUBLANG_ENGLISH_AUS                = 0x03U << ( APP_USB_LANG_OFFSET ), /**< English (Australian) */
    APP_USBD_SUBLANG_ENGLISH_CAN                = 0x04U << ( APP_USB_LANG_OFFSET ), /**< English (Canadian) */
    APP_USBD_SUBLANG_ENGLISH_NZ                 = 0x05U << ( APP_USB_LANG_OFFSET ), /**< English (New Zealand) */
    APP_USBD_SUBLANG_ENGLISH_EIRE               = 0x06U << ( APP_USB_LANG_OFFSET ), /**< English (Ireland) */
    APP_USBD_SUBLANG_ENGLISH_SOUTH_AFRICA       = 0x07U << ( APP_USB_LANG_OFFSET ), /**< English (South Africa) */
    APP_USBD_SUBLANG_ENGLISH_JAMAICA            = 0x08U << ( APP_USB_LANG_OFFSET ), /**< English (Jamaica) */
    APP_USBD_SUBLANG_ENGLISH_CARIBBEAN          = 0x09U << ( APP_USB_LANG_OFFSET ), /**< English (Caribbean) */
    APP_USBD_SUBLANG_ENGLISH_BELIZE             = 0x0aU << ( APP_USB_LANG_OFFSET ), /**< English (Belize) */
    APP_USBD_SUBLANG_ENGLISH_TRINIDAD           = 0x0bU << ( APP_USB_LANG_OFFSET ), /**< English (Trinidad) */
    APP_USBD_SUBLANG_ENGLISH_PHILIPPINES        = 0x0cU << ( APP_USB_LANG_OFFSET ), /**< English (Zimbabwe) */
    APP_USBD_SUBLANG_ENGLISH_ZIMBABWE           = 0x0dU << ( APP_USB_LANG_OFFSET ), /**< English (Philippines) */
    APP_USBD_SUBLANG_FRENCH                     = 0x01U << ( APP_USB_LANG_OFFSET ), /**< French */
    APP_USBD_SUBLANG_FRENCH_BELGIAN             = 0x02U << ( APP_USB_LANG_OFFSET ), /**< French (Belgian) */
    APP_USBD_SUBLANG_FRENCH_CANADIAN            = 0x03U << ( APP_USB_LANG_OFFSET ), /**< French (Canadian) */
    APP_USBD_SUBLANG_FRENCH_SWISS               = 0x04U << ( APP_USB_LANG_OFFSET ), /**< French (Swiss) */
    APP_USBD_SUBLANG_FRENCH_LUXEMBOURG          = 0x05U << ( APP_USB_LANG_OFFSET ), /**< French (Luxembourg) */
    APP_USBD_SUBLANG_FRENCH_MONACO              = 0x06U << ( APP_USB_LANG_OFFSET ), /**< French (Monaco) */
    APP_USBD_SUBLANG_GERMAN                     = 0x01U << ( APP_USB_LANG_OFFSET ), /**< German */
    APP_USBD_SUBLANG_GERMAN_SWISS               = 0x02U << ( APP_USB_LANG_OFFSET ), /**< German (Swiss) */
    APP_USBD_SUBLANG_GERMAN_AUSTRIAN            = 0x03U << ( APP_USB_LANG_OFFSET ), /**< German (Austrian) */
    APP_USBD_SUBLANG_GERMAN_LUXEMBOURG          = 0x04U << ( APP_USB_LANG_OFFSET ), /**< German (Luxembourg) */
    APP_USBD_SUBLANG_GERMAN_LIECHTENSTEIN       = 0x05U << ( APP_USB_LANG_OFFSET ), /**< German (Liechtenstein) */
    APP_USBD_SUBLANG_ITALIAN                    = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Italian */
    APP_USBD_SUBLANG_ITALIAN_SWISS              = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Italian (Swiss) */
    APP_USBD_SUBLANG_KASHMIRI_INDIA             = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Kashmiri (India) */
    APP_USBD_SUBLANG_KOREAN                     = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Korean */
    APP_USBD_SUBLANG_LITHUANIAN                 = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Lithuanian */
    APP_USBD_SUBLANG_MALAY_MALAYSIA             = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Malay (Malaysia) */
    APP_USBD_SUBLANG_MALAY_BRUNEI_DARUSSALAM    = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Malay (Brunei Darassalam) */
    APP_USBD_SUBLANG_NEPALI_INDIA               = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Nepali (India) */
    APP_USBD_SUBLANG_NORWEGIAN_BOKMAL           = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Norwegian (Bokmal) */
    APP_USBD_SUBLANG_NORWEGIAN_NYNORSK          = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Norwegian (Nynorsk) */
    APP_USBD_SUBLANG_PORTUGUESE                 = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Portuguese (Brazilian) */
    APP_USBD_SUBLANG_PORTUGUESE_BRAZILIAN       = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Portuguese */
    APP_USBD_SUBLANG_SERBIAN_LATIN              = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Serbian (Latin) */
    APP_USBD_SUBLANG_SERBIAN_CYRILLIC           = 0x03U << ( APP_USB_LANG_OFFSET ), /**< Serbian (Cyrillic) */
    APP_USBD_SUBLANG_SPANISH                    = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Castilian) */
    APP_USBD_SUBLANG_SPANISH_MEXICAN            = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Mexican) */
    APP_USBD_SUBLANG_SPANISH_MODERN             = 0x03U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Modern) */
    APP_USBD_SUBLANG_SPANISH_GUATEMALA          = 0x04U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Guatemala) */
    APP_USBD_SUBLANG_SPANISH_COSTA_RICA         = 0x05U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Costa Rica) */
    APP_USBD_SUBLANG_SPANISH_PANAMA             = 0x06U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Panama) */
    APP_USBD_SUBLANG_SPANISH_DOMINICAN_REPUBLIC = 0x07U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Dominican Republic) */
    APP_USBD_SUBLANG_SPANISH_VENEZUELA          = 0x08U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Venezuela) */
    APP_USBD_SUBLANG_SPANISH_COLOMBIA           = 0x09U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Colombia) */
    APP_USBD_SUBLANG_SPANISH_PERU               = 0x0aU << ( APP_USB_LANG_OFFSET ), /**< Spanish (Peru) */
    APP_USBD_SUBLANG_SPANISH_ARGENTINA          = 0x0bU << ( APP_USB_LANG_OFFSET ), /**< Spanish (Argentina) */
    APP_USBD_SUBLANG_SPANISH_ECUADOR            = 0x0cU << ( APP_USB_LANG_OFFSET ), /**< Spanish (Ecuador) */
    APP_USBD_SUBLANG_SPANISH_CHILE              = 0x0dU << ( APP_USB_LANG_OFFSET ), /**< Spanish (Chile) */
    APP_USBD_SUBLANG_SPANISH_URUGUAY            = 0x0eU << ( APP_USB_LANG_OFFSET ), /**< Spanish (Uruguay) */
    APP_USBD_SUBLANG_SPANISH_PARAGUAY           = 0x0fU << ( APP_USB_LANG_OFFSET ), /**< Spanish (Paraguay) */
    APP_USBD_SUBLANG_SPANISH_BOLIVIA            = 0x10U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Bolivia) */
    APP_USBD_SUBLANG_SPANISH_EL_SALVADOR        = 0x11U << ( APP_USB_LANG_OFFSET ), /**< Spanish (El Salvador) */
    APP_USBD_SUBLANG_SPANISH_HONDURAS           = 0x12U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Honduras) */
    APP_USBD_SUBLANG_SPANISH_NICARAGUA          = 0x13U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Nicaragua) */
    APP_USBD_SUBLANG_SPANISH_PUERTO_RICO        = 0x14U << ( APP_USB_LANG_OFFSET ), /**< Spanish (Puerto Rico) */
    APP_USBD_SUBLANG_SWEDISH                    = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Swedish */
    APP_USBD_SUBLANG_SWEDISH_FINLAND            = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Swedish (Finland) */
    APP_USBD_SUBLANG_URDU_PAKISTAN              = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Urdu (Pakistan) */
    APP_USBD_SUBLANG_URDU_INDIA                 = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Urdu (India) */
    APP_USBD_SUBLANG_UZBEK_LATIN                = 0x01U << ( APP_USB_LANG_OFFSET ), /**< Uzbek (Latin) */
    APP_USBD_SUBLANG_UZBEK_CYRILLIC             = 0x02U << ( APP_USB_LANG_OFFSET ), /**< Uzbek (Cyrillic) */
    APP_USBD_SUBLANG_HID_USAGE_DATA_DESCRIPTOR  = 0x01U << ( APP_USB_LANG_OFFSET ), /**< HID (Usage Data Descriptor) */
    APP_USBD_SUBLANG_HID_VENDOR_DEFINED_1       = 0x3cU << ( APP_USB_LANG_OFFSET ), /**< HID (Vendor Defined 1) */
    APP_USBD_SUBLANG_HID_VENDOR_DEFINED_2       = 0x3dU << ( APP_USB_LANG_OFFSET ), /**< HID (Vendor Defined 2) */
    APP_USBD_SUBLANG_HID_VENDOR_DEFINED_3       = 0x3eU << ( APP_USB_LANG_OFFSET ), /**< HID (Vendor Defined 3) */
    APP_USBD_SUBLANG_HID_VENDOR_DEFINED_4       = 0x3fU << ( APP_USB_LANG_OFFSET ), /**< HID (Vendor Defined 4) */
}app_usbd_langid_sub_t;

/**
 * @brief LANGID variable
 *
 * The LANGID value is composed from:
 * - 10-bit (9-0)  of Primary Language Identifiers
 * - 6-bit (15-10) of Sublanguage Identifiers.
 *
 * @sa app_usbd_langid_primary_t
 * @sa app_usbd_langid_sub_t
 */
typedef uint16_t app_usbd_langid_t;

#ifdef __cplusplus
}
#endif

#endif /* APP_USBD_LANGID_H__ */
