/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup app_util Utility Functions and Definitions
 * @{
 * @ingroup app_common
 *
 * @brief Various types and definitions available to all applications.
 */

#ifndef APP_UTIL_BDS_H__
#define APP_UTIL_BDS_H__

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "compiler_abstraction.h"
#include "app_util.h"
#include "ble_srv_common.h"
#include "nordic_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t nibble_t;
typedef uint32_t uint24_t;
typedef uint64_t uint40_t;

/**@brief IEEE 11073-20601 Regulatory Certification Data List Structure */
typedef struct
{
    uint8_t *  p_list;                                          /**< Pointer the byte array containing the encoded opaque structure based on IEEE 11073-20601 specification. */
    uint8_t    list_len;                                        /**< Length of the byte array. */
} regcertdatalist_t;

/**@brief SFLOAT format (IEEE-11073 16-bit FLOAT, meaning 4 bits for exponent (base 10) and 12 bits mantissa) */
typedef struct
{
  int8_t exponent;                                             /**< Base 10 exponent, should be using only 4 bits */
  int16_t mantissa;                                            /**< Mantissa, should be using only 12 bits */
} sfloat_t;

/**@brief Date and Time structure. */
typedef struct
{
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hours;
    uint8_t  minutes;
    uint8_t  seconds;
} ble_date_time_t;


/**@brief Function for encoding a uint16 value.
 *
 * @param[in]   p_value          Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t bds_uint16_encode(const uint16_t * p_value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((*p_value & 0x00FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((*p_value & 0xFF00) >> 8);
    return sizeof(uint16_t);
}

static __INLINE uint8_t bds_int16_encode(const int16_t * p_value, uint8_t * p_encoded_data)
{
    uint16_t tmp = *p_value;
    return bds_uint16_encode(&tmp, p_encoded_data);
}

/**@brief Function for encoding a uint24 value.
 *
 * @param[in]   p_value          Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t bds_uint24_encode(const uint32_t * p_value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((*p_value & 0x000000FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((*p_value & 0x0000FF00) >> 8);
    p_encoded_data[2] = (uint8_t) ((*p_value & 0x00FF0000) >> 16);
    return (3);
}


/**@brief Function for encoding a uint32 value.
 *
 * @param[in]   p_value          Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t bds_uint32_encode(const uint32_t * p_value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((*p_value & 0x000000FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((*p_value & 0x0000FF00) >> 8);
    p_encoded_data[2] = (uint8_t) ((*p_value & 0x00FF0000) >> 16);
    p_encoded_data[3] = (uint8_t) ((*p_value & 0xFF000000) >> 24);
    return sizeof(uint32_t);
}


/**@brief Function for encoding a uint40 value.
 *
 * @param[in]   p_value          Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t bds_uint40_encode(const uint64_t * p_value, uint8_t * p_encoded_data)
{
    p_encoded_data[0] = (uint8_t) ((*p_value & 0x00000000000000FF) >> 0);
    p_encoded_data[1] = (uint8_t) ((*p_value & 0x000000000000FF00) >> 8);
    p_encoded_data[2] = (uint8_t) ((*p_value & 0x0000000000FF0000) >> 16);
    p_encoded_data[3] = (uint8_t) ((*p_value & 0x00000000FF000000) >> 24);
    p_encoded_data[4] = (uint8_t) ((*p_value & 0x000000FF00000000) >> 32);
    return 5;
}

/**@brief Function for encoding a sfloat value.
 *
 * @param[in]   p_value          Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 *
 * @return      Number of bytes written.
 */
static __INLINE uint8_t bds_sfloat_encode(const sfloat_t * p_value, uint8_t * p_encoded_data)
{
    uint16_t encoded_val;

    encoded_val = ((p_value->exponent << 12) & 0xF000) |
                            ((p_value->mantissa <<  0) & 0x0FFF);

    return(bds_uint16_encode(&encoded_val, p_encoded_data));
}


/**@brief Function for encoding a uint8_array value.
 *
 * @param[in]   p_value          Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.
 */
static __INLINE uint8_t bds_uint8_array_encode(const uint8_array_t * p_value,
                                               uint8_t             * p_encoded_data)
{
    memcpy(p_encoded_data, p_value->p_data, p_value->size);
    return p_value->size;
}


/**@brief Function for encoding a utf8_str value.
 *
 * @param[in]   p_value          Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.

 */
static __INLINE uint8_t bds_ble_srv_utf8_str_encode(const ble_srv_utf8_str_t * p_value,
                                                    uint8_t                  * p_encoded_data)
{
    memcpy(p_encoded_data, p_value->p_str, p_value->length);
    return p_value->length;
}

/**@brief Function for encoding a regcertdatalist value.
 *
 * @param[in]   p_value          Value to be encoded.
 * @param[out]  p_encoded_data   Buffer where the encoded data is to be written.

 */
static __INLINE uint8_t bds_regcertdatalist_encode(const regcertdatalist_t * p_value,
                                                   uint8_t                 * p_encoded_data)
{
    memcpy(p_encoded_data, p_value->p_list, p_value->list_len);
    return p_value->list_len;
}


/**@brief Function for decoding a date_time value.
 *
 * @param[in]   p_date_time    pointer to the date_time structure to encode.
 * @param[in]   p_encoded_data pointer to the encoded data
 * @return      length of the encoded field.
 */
static __INLINE uint8_t bds_ble_date_time_encode(const ble_date_time_t * p_date_time,
                                                 uint8_t               * p_encoded_data)
{
    uint8_t len = bds_uint16_encode(&p_date_time->year, &p_encoded_data[0]);

    p_encoded_data[len++] = p_date_time->month;
    p_encoded_data[len++] = p_date_time->day;
    p_encoded_data[len++] = p_date_time->hours;
    p_encoded_data[len++] = p_date_time->minutes;
    p_encoded_data[len++] = p_date_time->seconds;

    return len;
}


/**@brief Function for decoding a uint16 value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_decoded_val    pointer to the decoded value
 * @return      length of the decoded field.
 */
static __INLINE uint8_t bds_uint16_decode(const uint8_t len,
                                          const uint8_t * p_encoded_data,
                                          uint16_t      * p_decoded_val)
{
    UNUSED_VARIABLE(len);
    *p_decoded_val = (((uint16_t)((uint8_t *)p_encoded_data)[0])) |
                     (((uint16_t)((uint8_t *)p_encoded_data)[1]) << 8 );
    return (sizeof(uint16_t));
}


/**@brief Function for decoding a int16 value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_decoded_val    pointer to the decoded value
 * @return      length of the decoded field.
 */
static __INLINE uint8_t bds_int16_decode(const uint8_t len,
                                         const uint8_t * p_encoded_data,
                                         int16_t       * p_decoded_val)
{
    UNUSED_VARIABLE(len);
    uint16_t tmp = 0;
    uint8_t retval = bds_uint16_decode(len, p_encoded_data, &tmp);
    *p_decoded_val = (int16_t)tmp;
    return retval;
}


/**@brief Function for decoding a uint24 value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_decoded_val    pointer to the decoded value
 *
 * @return      length of the decoded field.
 */
static __INLINE uint8_t bds_uint24_decode(const uint8_t len,
                                          const uint8_t * p_encoded_data,
                                          uint32_t      * p_decoded_val)
{
    UNUSED_VARIABLE(len);
    *p_decoded_val = (((uint32_t)((uint8_t *)p_encoded_data)[0]) << 0)  |
                     (((uint32_t)((uint8_t *)p_encoded_data)[1]) << 8)  |
                     (((uint32_t)((uint8_t *)p_encoded_data)[2]) << 16);
    return (3);
}


/**@brief Function for decoding a uint32 value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_decoded_val    pointer to the decoded value
 *
 * @return      length of the decoded field.
 */
static __INLINE uint8_t bds_uint32_decode(const uint8_t len,
                                          const uint8_t * p_encoded_data,
                                          uint32_t      * p_decoded_val)
{
    UNUSED_VARIABLE(len);
    *p_decoded_val = (((uint32_t)((uint8_t *)p_encoded_data)[0]) << 0)  |
                     (((uint32_t)((uint8_t *)p_encoded_data)[1]) << 8)  |
                     (((uint32_t)((uint8_t *)p_encoded_data)[2]) << 16) |
                     (((uint32_t)((uint8_t *)p_encoded_data)[3]) << 24 );
    return (sizeof(uint32_t));
}


/**@brief Function for decoding a uint40 value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_decoded_val    pointer to the decoded value
 *
 * @return      length of the decoded field.
 */
static __INLINE uint8_t bds_uint40_decode(const uint8_t len,
                                          const uint8_t * p_encoded_data,
                                          uint64_t      * p_decoded_val)
{
    UNUSED_VARIABLE(len);
    *p_decoded_val = (((uint64_t)((uint8_t *)p_encoded_data)[0]) << 0)  |
                     (((uint64_t)((uint8_t *)p_encoded_data)[1]) << 8)  |
                     (((uint64_t)((uint8_t *)p_encoded_data)[2]) << 16) |
                     (((uint64_t)((uint8_t *)p_encoded_data)[3]) << 24 )|
                     (((uint64_t)((uint8_t *)p_encoded_data)[4]) << 32 );
    return (40);
}


/**@brief Function for decoding a sfloat value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_decoded_val    pointer to the decoded value
 *
 * @return      length of the decoded field.

 */
static __INLINE uint8_t bds_sfloat_decode(const uint8_t len,
                                          const uint8_t * p_encoded_data,
                                          sfloat_t      * p_decoded_val)
{

    p_decoded_val->exponent = 0;
    bds_uint16_decode(len, p_encoded_data, (uint16_t*)&p_decoded_val->mantissa);
    p_decoded_val->exponent = (uint8_t)((p_decoded_val->mantissa & 0xF000) >> 12);
    p_decoded_val->mantissa &= 0x0FFF;
    return len;
}


/**@brief Function for decoding a uint8_array value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_decoded_val    pointer to the decoded value
 *
 * @return      length of the decoded field.
 */
static __INLINE uint8_t bds_uint8_array_decode(const uint8_t len,
                                               const uint8_t * p_encoded_data,
                                               uint8_array_t * p_decoded_val)
{
    memcpy(p_decoded_val->p_data, p_encoded_data, len);
    p_decoded_val->size = len;
    return p_decoded_val->size;
}


/**@brief Function for decoding a utf8_str value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_decoded_val    pointer to the decoded value
 *
 * @return      length of the decoded field.
 */
static __INLINE uint8_t bds_ble_srv_utf8_str_decode(const uint8_t      len,
                                                    const uint8_t      * p_encoded_data,
                                                    ble_srv_utf8_str_t * p_decoded_val)
{
    p_decoded_val->p_str = (uint8_t*)p_encoded_data;
    p_decoded_val->length = len;
    return p_decoded_val->length;
}


/**@brief Function for decoding a regcertdatalist value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_decoded_val    pointer to the decoded value
 *
 * @return      length of the decoded field.
 */
static __INLINE uint8_t bds_regcertdatalist_decode(const uint8_t     len,
                                                   const uint8_t     * p_encoded_data,
                                                   regcertdatalist_t * p_decoded_val)
{
    memcpy(p_decoded_val->p_list, p_encoded_data, len);
    p_decoded_val->list_len = len;
    return p_decoded_val->list_len;
}


/**@brief Function for decoding a date_time value.
 *
 * @param[in]   len              length of the field to be decoded.
 * @param[in]   p_encoded_data   Buffer where the encoded data is stored.
 * @param[in]   p_date_time      pointer to the decoded value
 *
 * @return      length of the decoded field.
 */
static __INLINE uint8_t bds_ble_date_time_decode(const uint8_t   len,
                                                 const uint8_t   * p_encoded_data,
                                                 ble_date_time_t * p_date_time)
{
    UNUSED_VARIABLE(len);
    uint8_t pos          = bds_uint16_decode(len, &p_encoded_data[0], &p_date_time->year);
    p_date_time->month   = p_encoded_data[pos++];
    p_date_time->day     = p_encoded_data[pos++];
    p_date_time->hours   = p_encoded_data[pos++];
    p_date_time->minutes = p_encoded_data[pos++];
    p_date_time->seconds = p_encoded_data[pos++];

    return pos;
}


#ifdef __cplusplus
}
#endif

#endif // APP_UTIL_BDS_H__

/** @} */
