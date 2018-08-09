/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
/** @file mqtt_decoder.c
 *
 * @brief Decoder functions needs for decoding packets received from the broker.
 */

#include "mqtt_internal.h"

#if MQTT_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME mqtt_dec

#define NRF_LOG_LEVEL       MQTT_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  MQTT_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR MQTT_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define MQTT_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define MQTT_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define MQTT_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#define MQTT_ENTRY()                       MQTT_TRC(">> %s", __func__)
#define MQTT_EXIT()                        MQTT_TRC("<< %s", __func__)

#else // MQTT_CONFIG_LOG_ENABLED

#define MQTT_TRC(...)                                                                           /**< Disables traces. */
#define MQTT_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define MQTT_ERR(...)                                                                           /**< Disables error logs. */

#define MQTT_ENTRY(...)
#define MQTT_EXIT(...)

#endif // MQTT_CONFIG_LOG_ENABLED

#define MQTT_LENGTH_VALUE_MASK         0x7F
#define MQTT_LENGTH_CONTINUATION_BIT   0x80
#define MQTT_LENGTH_MULTIPLIER         0x80


uint32_t unpack_uint8(uint8_t    * p_val,
                      uint32_t     buffer_len,
                      uint8_t    * const buffer,
                      uint32_t   * const p_offset)
{
    uint32_t       err_code = NRF_ERROR_DATA_SIZE;

    if (buffer_len > (*p_offset))
    {
        const uint32_t available_len = buffer_len - (*p_offset);

        MQTT_TRC(">> %s BL:%08x, B:%p, O:%08x A:%08x", __func__,
                      buffer_len, buffer, (*p_offset), available_len);

        if (available_len >= SIZE_OF_UINT8)
        {
            // Create unit8 value.
            (*p_val)     = buffer[*p_offset];

            // Increment offset.
            (*p_offset) += SIZE_OF_UINT8;

            // Indicate success.
            err_code     = NRF_SUCCESS;
        }
    }

    MQTT_TRC("<< %s result:0x%08x val:0x%02x", __func__, err_code, (*p_val));
    return err_code;
}


uint32_t unpack_uint16(uint16_t   * p_val,
                       uint32_t     buffer_len,
                       uint8_t    * const buffer,
                       uint32_t   * const p_offset)
{
    uint32_t       err_code = NRF_ERROR_DATA_SIZE;

    if (buffer_len > (*p_offset))
    {
        const uint32_t available_len = buffer_len - (*p_offset);

        MQTT_TRC(">> %s BL:%08x, B:%p, O:%08x A:%08x", __func__,
                      buffer_len, buffer, (*p_offset), available_len);

        if (available_len >= SIZE_OF_UINT16)
        {
            // Create unit16 value.
            (*p_val)     = ((buffer[*p_offset]    & 0x00FF) << 8); // MSB
            (*p_val)    |= (buffer[(*p_offset+1)] & 0x00FF);        // LSB

            // Increment offset.
            (*p_offset) += SIZE_OF_UINT16;

            // Indicate success.
            err_code     = NRF_SUCCESS;
        }
    }

    MQTT_TRC("<< %s result:0x%08x val:0x%04x", __func__, err_code, (*p_val));

    return err_code;
}


uint32_t unpack_utf8_str(mqtt_utf8_t    * const p_str,
                         uint32_t               buffer_len,
                         uint8_t        * const buffer,
                         uint32_t       * const p_offset)
{
    uint16_t utf8_strlen;
    uint32_t err_code = unpack_uint16(&utf8_strlen, buffer_len, buffer, p_offset);

    p_str->p_utf_str  = NULL;
    p_str->utf_strlen = 0;

    if (err_code == NRF_SUCCESS)
    {
        const uint32_t available_len = buffer_len - (*p_offset);

        MQTT_TRC(">> %s BL:%08x, B:%p, O:%08x A:%08x", __func__,
                      buffer_len, buffer, (*p_offset), available_len);

        if (utf8_strlen <= available_len)
        {
            // Zero length UTF8 strings permitted.
            if (utf8_strlen)
            {
                // Point to right location in buffer.
                p_str->p_utf_str   = &buffer[(*p_offset)];
            }

            // Populate length field.
            p_str->utf_strlen  = utf8_strlen;

            // Increment offset.
            (*p_offset)       += utf8_strlen;

            // Indicate success
            err_code = NRF_SUCCESS;
        }
        else
        {
            // Reset to original value.
            (*p_offset) -= SIZE_OF_UINT16;

            err_code = NRF_ERROR_DATA_SIZE;
        }
    }

    MQTT_TRC("<< %s result:0x%08x utf8 len:0x%08x", __func__, err_code, p_str->utf_strlen);

    return err_code;
}


uint32_t unpack_bin_str(mqtt_binstr_t    * const p_str,
                        uint32_t                 buffer_len,
                        uint8_t          * const buffer,
                        uint32_t         * const p_offset)
{
    uint32_t error_code = NRF_ERROR_DATA_SIZE;

    MQTT_TRC(">> %s BL:%08x, B:%p, O:%08x", __func__,
                  buffer_len, buffer, (*p_offset));

    if (buffer_len >= (*p_offset))
    {
        p_str->p_bin_str  = NULL;
        p_str->bin_strlen = 0;

        // Indicate success zero length binary strings are permitted.
        error_code        = NRF_SUCCESS;

        const uint32_t available_len = buffer_len - (*p_offset);

        if (available_len)
        {
            // Point to start of binary string.
            p_str->p_bin_str  = &buffer[(*p_offset)];
            p_str->bin_strlen = available_len;

            // Increment offset.
            (*p_offset)      += available_len;
        }
    }

    MQTT_TRC("<< %s bin len:0x%08x", __func__, p_str->bin_strlen);

    return error_code;
}


uint32_t packet_length_decode(uint8_t  * p_buffer,
                              uint32_t   buffer_len,
                              uint32_t * p_remaining_length,
                              uint32_t * p_offset)
{
    uint32_t index            = (*p_offset);
    uint32_t remaining_length = 0;
    uint32_t multiplier       = 1;

    do
    {
        if (index >= buffer_len)
        {
            return NRF_ERROR_DATA_SIZE;
        }

        remaining_length += (p_buffer[index] & MQTT_LENGTH_VALUE_MASK) * multiplier;
        multiplier       *= MQTT_LENGTH_MULTIPLIER;

    } while ((p_buffer[index++] & MQTT_LENGTH_CONTINUATION_BIT) != 0);

    *p_offset           = index;
    *p_remaining_length = remaining_length;

    MQTT_TRC("%s: RL:0x%08x RLS:0x%08x", __func__, remaining_length, index);

    return NRF_SUCCESS;
}
