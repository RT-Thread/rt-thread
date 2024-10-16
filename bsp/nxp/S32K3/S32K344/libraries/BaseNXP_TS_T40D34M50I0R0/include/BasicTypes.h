/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 5.0.0
* Build Version : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
#ifndef BASICTYPES_H
#define BASICTYPES_H

#include "Platform_Types.h"

#if defined(INT8_MIN) && defined(INT16_MIN) && defined(INT16_MIN) && defined(INT32_MIN) && defined(INT64_MIN)  && \
    defined(INT8_MAX) && defined(INT16_MAX) && defined(INT16_MAX) && defined(INT32_MAX) && defined(INT64_MAX)  && \
    defined(UINT8_MAX) && defined(UINT16_MAX) && defined(UINT16_MAX) && defined(UINT32_MAX) && defined(UINT64_MAX)
/* if stdint.h included in Platform_Types.h, we are set */
#else
    #if !defined(NO_STDINT_H)
        #include <stdint.h>
    #else
/* define stdint.h-like types over Platform_Types.h */

/**
@brief Unsigned 8 bit integer with range of 0 ..+255 (0x00..0xFF) -
       8 bit
*/
typedef uint8 uint8_t;

/**
@brief Unsigned 16 bit integer with range of 0 ..+65535 (0x0000..0xFFFF) -
       16 bit
*/
typedef uint16 uint16_t;

/**
@brief Unsigned 32 bit integer with range of 0 ..+4294967295 (0x00000000..0xFFFFFFFF) -
       32 bit
*/
typedef uint32 uint32_t;

/**
@brief Unsigned 64 bit integer with range of 0 ..18446744073709551615 (0x0000000000000000..0xFFFFFFFFFFFFFFFF) -
       64 bit
*/
typedef uint64 uint64_t;

/**
@brief Signed 8 bit integer with range of -128 ..+127 (0x80..0x7F) -
       7 bit + 1 sign bit
*/
typedef sint8 sint8_t;

/**
@brief Signed 16 bit integer with range of -32768 ..+32767 (0x8000..0x7FFF) -
       15 bit + 1 sign bit
*/
typedef sint16 sint16_t;

/**
@brief Signed 32 bit integer with range of -2147483648.. +2147483647 (0x80000000..0x7FFFFFFF) -
       31 bit + 1 sign bit
*/
typedef sint32 sint32_t;

/**
@brief Signed 64 bit integer with range of -9223372036854775808.. +9223372036854775807 (0x8000000000000000..0x7FFFFFFFFFFFFFFF) -
       63 bit + 1 sign bit
*/
typedef sint64 sint64_t;

/**
@brief Signed 8 bit integer with range of -128 ..+127 (0x80..0x7F) -
       7 bit + 1 sign bit
*/
typedef sint8 int8_t;

/**
@brief Signed 16 bit integer with range of -32768 ..+32767 (0x8000..0x7FFF) -
       15 bit + 1 sign bit
*/
typedef sint16 int16_t;

/**
@brief Signed 32 bit integer with range of -2147483648.. +2147483647 (0x80000000..0x7FFFFFFF) -
       31 bit + 1 sign bit
*/
typedef sint32 int32_t;

/**
@brief Signed 64 bit integer with range of -9223372036854775808.. +9223372036854775807 (0x8000000000000000..0x7FFFFFFFFFFFFFFF) -
       63 bit + 1 sign bit
*/
typedef sint64 int64_t;

/**
@brief Unsigned integer at least 8 bit long. Range of at least 0 ..+255 (0x00..0xFF) -
       8 bit
*/
typedef uint8_least uint8_least_t;

/**
@brief  Unsigned integer at least 16 bit long. Range of at least 0 ..+65535 (0x0000..0xFFFF) -
        16 bit
*/
typedef uint16_least uint16_least_t;

/**
@brief Unsigned integer at least 32 bit long. Range of at least 0 ..+4294967295 (0x00000000..0xFFFFFFFF) -
       32 bit
*/
typedef uint32_least uint32_least_t;

/**
@brief Unsigned integer at least 64 bit long. Range of at least 0 ..18446744073709551615 (0x0000000000000000..0xFFFFFFFFFFFFFFFF) -
       64 bit
*/
typedef unsigned long long uint64_least_t;

/**
@brief Signed integer at least 8 bit long. Range - at least -128 ..+127.
       At least 7 bit + 1 bit sign
*/
typedef sint8_least sint8_least_t;

/**
@brief Signed integer at least 16 bit long. Range - at least -32768 ..+32767.
       At least 15 bit + 1 bit sign
*/
typedef sint16_least sint16_least_t;

/**
@brief Signed integer at least 32 bit long. Range - at least -2147483648.. +2147483647.
       At least 31 bit + 1 bit sign
*/
typedef sint32_least sint32_least_t;

/**
@brief Signed 64 bit integer with range of -9223372036854775808.. +9223372036854775807.
       At least 63 bit + 1 bit sign
*/
typedef sint64 sint64_least_t;

/**
@brief Signed integer at least 8 bit long. Range - at least -128 ..+127.
       At least 7 bit + 1 bit sign
*/
typedef sint8_least int8_least_t;

/**
@brief Signed integer at least 16 bit long. Range - at least -32768 ..+32767.
       At least 15 bit + 1 bit sign
*/
typedef sint16_least int16_least_t;

/**
@brief Signed integer at least 32 bit long. Range - at least -2147483648.. +2147483647.
       At least 31 bit + 1 bit sign
*/
typedef sint32_least int32_least_t;

/**
@brief Signed integer at least 64 bit long. Range - at least -9223372036854775808.. +9223372036854775807.
       At least 63 bit + 1 bit sign
*/
typedef sint64 int64_least_t;
    #endif /* !defined(NO_STDINT_H) */
#endif /* defined(INT8_MIN) && defined(INT16_MIN) ... */

#endif /* BASICTYPES_H */
