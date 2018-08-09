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
/** @file mqtt_internal.h
 *
 * @brief Function and data structures internal to MQTT module.
 */

#ifndef MQTT_INTERNAL_H_
#define MQTT_INTERNAL_H_

#include "nordic_common.h"
#include "sdk_common.h"
#include "sdk_config.h"
#include "mqtt.h"
#include "iot_errors.h"
#include "nrf_tls.h"
#include <stdint.h>
#include <string.h>
#include "nrf_error.h"
#include "nrf_tls.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MQTT_MAX_CLIENTS
#define MQTT_MAX_CLIENTS          1                                            /**< Maximum number of clients that can be managed by the module. */
#endif //MQTT_MAX_CLIENTS

#ifndef MQTT_KEEPALIVE
#define MQTT_KEEPALIVE            60                                           /**< Keep alive time for MQTT (in seconds). Sending of Ping Requests to be keep the connection alive are governed by this value. */
#endif //MQTT_KEEPALIVE

#ifndef MQTT_MAX_PACKET_LENGTH
#define MQTT_MAX_PACKET_LENGTH    128                                          /**< Maximum MQTT packet size that can be sent (including the fixed and variable header). */
#endif // MQTT_MAX_PACKET_LENGTH

#define MQTT_FIXED_HEADER_SIZE              2                                  /**< Fixed header minimum size. Remaining length size is 1 in this case. */
#define MQTT_FIXED_HEADER_EXTENDED_SIZE     5                                  /**< Maximum size of the fixed header.  Remaining length size is 4 in this case. */

/**@brief MQTT Control Packet Types. */
#define MQTT_PKT_TYPE_CONNECT      0x10
#define MQTT_PKT_TYPE_CONNACK      0x20
#define MQTT_PKT_TYPE_PUBLISH      0x30
#define MQTT_PKT_TYPE_PUBACK       0x40
#define MQTT_PKT_TYPE_PUBREC       0x50
#define MQTT_PKT_TYPE_PUBREL       0x60
#define MQTT_PKT_TYPE_PUBCOMP      0x70
#define MQTT_PKT_TYPE_SUBSCRIBE    0x82 // QoS 1 for subscribe
#define MQTT_PKT_TYPE_SUBACK       0x90
#define MQTT_PKT_TYPE_UNSUBSCRIBE  0xA2
#define MQTT_PKT_TYPE_UNSUBACK     0xB0
#define MQTT_PKT_TYPE_PINGREQ      0xC0
#define MQTT_PKT_TYPE_PINGRSP      0xD0
#define MQTT_PKT_TYPE_DISCONNECT   0xE0


/**@brief Masks for MQTT header flags. */
#define MQTT_HEADER_DUP_MASK       0x08
#define MQTT_HEADER_QOS_MASK       0x06
#define MQTT_HEADER_RETAIN_MASK    0x01
#define MQTT_HEADER_CONNACK_MASK   0x0F

/**@brief Masks for MQTT header flags. */
#define MQTT_CONNECT_FLAG_CLEAN_SESSION 0x02
#define MQTT_CONNECT_FLAG_WILL_TOPIC    0x04
#define MQTT_CONNECT_FLAG_WILL_RETAIN   0x20
#define MQTT_CONNECT_FLAG_PASSWORD      0x40
#define MQTT_CONNECT_FLAG_USERNAME      0x80

/**@brief Size of mandatory header of MQTT Packet. */
#define MQTT_PKT_HEADER_SIZE       2

/**@brief */
#define MQTT_MAX_PAYLOAD_SIZE      0x0FFFFFFF

/**@brief Maximum size of variable and payload in the packet.  */
#define MQTT_MAX_VARIABLE_HEADER_N_PAYLOAD (MQTT_MAX_PACKET_LENGTH - MQTT_FIXED_HEADER_EXTENDED_SIZE)

/**@brief Defines size of uint8 in bytes. */
#define SIZE_OF_UINT8                1

/**@brief Defines size of uint8 in bytes. */
#define SIZE_OF_UINT16               2

/**@brief Computes total size needed to pack a UTF8 string. */
#define GET_UT8STR_BUFFER_SIZE(STR) (SIZE_OF_UINT16 + (STR)->utf_strlen)

/**@brief Computes total size needed to pack a binary stream. */
#define GET_BINSTR_BUFFER_SIZE(STR) ((STR)->bin_strlen)

/**@brief Unsubscribe packet size. */
#define MQTT_UNSUBSCRIBE_PKT_SIZE  4

/**@brief Sets MQTT Client's state with one indicated in 'STATE'. */
#define MQTT_SET_STATE(CLIENT, STATE) ((CLIENT)->state |= (STATE))

/**@brief Sets MQTT Client's state exclusive to 'STATE'. */
#define MQTT_SET_STATE_EXCLUSIVE(CLIENT, STATE) ((CLIENT)->state = (STATE))

/**@brief Verifies if MQTT Client's state is set with one indicated in 'STATE'. */
#define MQTT_VERIFY_STATE(CLIENT, STATE) ((CLIENT)->state & (STATE))

/**@brief Reset 'STATE' in MQTT Client's state. */
#define MQTT_RESET_STATE(CLIENT, STATE) ((CLIENT)->state &= ~(STATE))

/**@brief Initialize MQTT Client's state. */
#define MQTT_STATE_INIT(CLIENT) (CLIENT)->state = MQTT_STATE_IDLE

/**@brief Computes the first byte of MQTT message header based on message type, duplication flag,
 *        QoS and  the retain flag.
 */
#define MQTT_MESSAGES_OPTIONS(TYPE, DUP, QOS, RETAIN)    \
        (((TYPE)      & 0xF0)   |                        \
        (((DUP) << 3) & 0x08)   |                        \
        (((QOS) << 1) & 0x06)   |                        \
        ((RETAIN) & 0x01))


#define MQTT_EVT_FLAG_NONE                       0x00000000
#define MQTT_EVT_FLAG_INSTANCE_RESET             0x00000001


/**
 * @defgroup iot_mqtt_mutex_lock_unlock Module's Mutex Lock/Unlock Macros.
 *
 * @details Macros used to lock and unlock modules. Currently, SDK does not use mutexes but
 *          framework is provided in case the need to use an alternative architecture arises.
 * @{
 */
#define MQTT_MUTEX_LOCK()   SDK_MUTEX_LOCK(m_mqtt_mutex)                       /**< Lock module using mutex */
#define MQTT_MUTEX_UNLOCK() SDK_MUTEX_UNLOCK(m_mqtt_mutex)                     /**< Unlock module using mutex */

/** @} */

/**@brief Check if the input pointer is NULL, if so it returns NRF_ERROR_NULL.
 */
#define NULL_PARAM_CHECK(PARAM)                                                                   \
        if ((PARAM) == NULL)                                                                      \
        {                                                                                         \
            return (NRF_ERROR_NULL | IOT_MQTT_ERR_BASE);                                          \
        }

#define NULL_PARAM_CHECK_VOID(PARAM)                                                              \
        if ((PARAM) == NULL)                                                                      \
        {                                                                                         \
            return;                                                                               \
        }

/**@brief MQTT States. */
typedef enum
{
    MQTT_STATE_IDLE           = 0x00000000,                                    /**< Idle state, implying the client entry in the table is unused/free. */
    MQTT_STATE_TCP_CONNECTING = 0x00000001,                                    /**< TCP Connection has been requested, awaiting result of the request. */
    MQTT_STATE_TCP_CONNECTED  = 0x00000002,                                    /**< TCP Connection successfully established. */
    MQTT_STATE_CONNECTED      = 0x00000004,                                    /**< MQTT Connection successful. */
    MQTT_STATE_PENDING_WRITE  = 0x00000008,                                    /**< State that indicates write callback is awaited for an issued request. */
    MQTT_STATE_DISCONNECTING  = 0x00000010                                     /**< TCP Disconnect has been requested, awaiting result of the request. */
} mqtt_state_t;


/**@brief Packs unsigned 8 bit value to the buffer at the offset requested.
 *
 * @param[in]    val        Value to be packed.
 * @param[in]    buffer_len Total size of the buffer on which value is to be packed.
 *                          This shall not be zero.
 * @param[out]   p_buffer   Buffer where the value is to be packed.
 * @param[inout] p_offset   Offset on the buffer where the value is to be packed. If the procedure
 *                          is successful, the offset is incremented to point to the next write/pack
 *                          location on the buffer.
 *
 * @retval NRF_SUCCESS         if procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length.
 */
uint32_t pack_uint8(uint8_t      val,
                    uint32_t     buffer_len,
                    uint8_t    * const p_buffer,
                    uint32_t   * const p_offset);


/**@brief Packs unsigned 16 bit value to the buffer at the offset requested.
 *
 * @param[in]    val        Value to be packed.
 * @param[in]    buffer_len Total size of the buffer on which value is to be packed.
 *                          This shall not be zero.
 * @param[out]   p_buffer   Buffer where the value is to be packed.
 * @param[inout] p_offset   Offset on the buffer where the value is to be packed. If the procedure
 *                          is successful, the offset is incremented to point to the next write/pack
 *                          location on the buffer.
 *
 * @retval NRF_SUCCESS         if the procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length minus
 *                             the size of unsigned 16 bit integer.
 */
uint32_t pack_uint16(uint16_t     val,
                     uint32_t     buffer_len,
                     uint8_t    * const p_buffer,
                     uint32_t   * const p_offset);


/**@brief Packs utf8 string to the buffer at the offset requested.
 *
 * @param[in]    p_str      UTF-8 string and its length to be packed.
 * @param[in]    buffer_len Total size of the buffer on which string is to be packed.
 *                          This shall not be zero.
 * @param[out]   p_buffer   Buffer where the string is to be packed.
 * @param[inout] p_offset   Offset on the buffer where the string is to be packed. If the procedure
 *                          is successful, the offset is incremented to point to the next write/pack
 *                          location on the buffer.
 *
 * @retval NRF_SUCCESS         if the procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length minus
 *                             the size of unsigned 16 bit integer.
 * @retval NRF_ERROR_NO_MEM    if there is no room on the buffer to pack the string.
 */
uint32_t pack_utf8_str(mqtt_utf8_t const * const p_str,
                       uint32_t                  buffer_len,
                       uint8_t           * const p_buffer,
                       uint32_t          * const p_offset);


/**@brief Packs binary string to the buffer at the offset requested.
 *
 * @param[in]    p_str      Binary string and its length to be packed.
 * @param[in]    buffer_len Total size of the buffer on which string is to be packed.
 * @param[in]    p_buffer   Buffer where the string is to be packed.
 * @param[inout] p_offset   Offset on the buffer where the string is to be packed. If the procedure
 *                          is successful, the offset is incremented to point to the next write/pack
 *                          location on the buffer.
 *
 * @retval NRF_SUCCESS         if the procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length.
 * @retval NRF_ERROR_NO_MEM    if there is no room on the buffer to pack the string.
 */
uint32_t pack_bin_str(mqtt_binstr_t const * const p_str,
                      uint32_t                    buffer_len,
                      uint8_t             * const p_buffer,
                      uint32_t            * const p_offset);


/**@brief Unpacks unsigned 8 bit value from the buffer from the offset requested.
 *
 * @param[out]   p_val      Memory where the value is to be unpacked.
 * @param[in]    buffer_len Total size of the buffer. This shall not be zero.
 * @param[in]    p_buffer   Buffer from which the value is to be unpacked.
 * @param[inout] p_offset   Offset on the buffer from where the value is to be unpacked. If the
 *                          procedure is successful, the offset is incremented to point to the next
 *                          read/unpack location on the buffer.
 *
 * @retval NRF_SUCCESS         if the procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length.
 */
uint32_t unpack_uint8(uint8_t     *       p_val,
                      uint32_t            buffer_len,
                      uint8_t     * const p_buffer,
                      uint32_t    * const p_offset);

/**@brief Unpacks unsigned 16 bit value from the buffer from the offset requested.
 *
 * @param[out]   p_val      Memory where the value is to be unpacked.
 * @param[in]    buffer_len Total size of the buffer. This shall not be zero.
 * @param[in]    p_buffer   Buffer from which the value is to be unpacked.
 * @param[inout] p_offset   Offset on the buffer from where the value is to be unpacked. If the
 *                          procedure is successful, the offset is incremented to point to the next
 *                          read/unpack location on the buffer.
 *
 * @retval NRF_SUCCESS         if the procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length.
 */
uint32_t unpack_uint16(uint16_t    *       p_val,
                       uint32_t            buffer_len,
                       uint8_t     * const p_buffer,
                       uint32_t    * const p_offset);


/**@brief Unpacks unsigned 16 bit value from the buffer from the offset requested.
 *
 * @param[out]   p_str      Memory where the utf8 string and its value are to be unpacked.
 *                          No copy of data is performed for the string.
 * @param[in]    buffer_len Total size of the buffer. This shall not be zero.
 * @param[in]    p_buffer   Buffer from which the string is to be unpacked.
 * @param[inout] p_offset   Offset on the buffer from where the value is to be unpacked. If the
 *                          procedure is successful, the offset is incremented to point to the next
 *                          read/unpack location on the buffer.
 *
 * @retval NRF_SUCCESS         if the procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length.
 */
uint32_t unpack_utf8_str(mqtt_utf8_t    * const p_str,
                         uint32_t               buffer_len,
                         uint8_t        * const p_buffer,
                         uint32_t       * const p_offset);


/**@brief Unpacks binary string from the buffer from the offset requested.
 *
 * @param[out]   p_str      Memory where the binary string and its length are to be unpacked.
 *                          No copy of data is performed for the string.
 * @param[in]    buffer_len Total size of the buffer. This shall not be zero.
 * @param[in]    p_buffer   Buffer where the value is to be unpacked.
 * @param[inout] p_offset   Offset on the buffer from where the value is to be unpacked. If the
 *                          procedure is successful, the offset is incremented to point to the next
 *                          read/unpack location on the buffer.
 *
 * @retval NRF_SUCCESS         if the procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length.
 */
uint32_t unpack_bin_str(mqtt_binstr_t   * const p_str,
                        uint32_t                buffer_len,
                        uint8_t         * const p_buffer,
                        uint32_t        * const p_offset);


/**@brief Unpacks utf8 string from the buffer from the offset requested.
 *
 * @param[out]   p_str      Memory where the utf8 string and its length are to be unpacked.
 * @param[in]    buffer_len Total size of the buffer. This shall not be zero.
 * @param[in]    p_buffer   Buffer where the value is to be unpacked.
 * @param[inout] p_offset   Offset on the buffer from where the value is to be unpacked. If the
 *                          procedure is successful, the offset is incremented to point to the next
 *                          read/unpack location on the buffer.
 *
 * @retval NRF_SUCCESS         if the procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length.
 */
uint32_t zero_len_str_encode(uint32_t            buffer_len,
                             uint8_t     * const p_buffer,
                             uint32_t    * const p_offset);


/**@brief Computes and encodes length for the MQTT fixed header.
 *
 * @note The remaining length is not packed as a fixed unsigned 32 bit integer. Instead it is packed
 *       on algorithm below:
 *
 * @code
 * do
 *            encodedByte = X MOD 128
 *            X = X DIV 128
 *            // if there are more data to encode, set the top bit of this byte
 *            if ( X > 0 )
 *                encodedByte = encodedByte OR 128
 *            endif
 *                'output' encodedByte
 *       while ( X > 0 )
 * @endcode
 *
 * @param[in]    remaining_length Length of variable header and payload in the MQTT message.
 * @param[out]   p_buffer         Buffer where the length is to be packed.
 * @param[inout] p_offset         Offset on the buffer where the length is to be packed.
 */
void packet_length_encode(uint32_t remaining_length, uint8_t * p_buffer, uint32_t * p_offset);


/**@brief Decode MQTT Packet Length in the MQTT fixed header.
 *
 * @param[in]    p_buffer           Buffer where the length is to be decoded.
 * @param[in]    buffer_len         Length of p_buffer
 * @param[out]   p_remaining_length Length of variable header and payload in the MQTT message.
 * @param[inout] p_offset           Offset on the buffer from where the length is to be unpacked.
 *
 * @retval NRF_SUCCESS         if the procedure is successful.
 * @retval NRF_ERROR_DATA_SIZE if the offset is greater than or equal to the buffer length.
 */
uint32_t packet_length_decode(uint8_t  * p_buffer,
                              uint32_t   buffer_len,
                              uint32_t * p_remaining_length,
                              uint32_t * p_offset);


/**@brief Encodes fixed header for the MQTT message and provides pointer to start of the header.
 *
 * @param[in]    message_type     Message type containing packet type and the flags.
 *                                Use @ref MQTT_MESSAGES_OPTIONS to construct the message_type.
 * @param[in]    length           Buffer where the message payload along with variable header.
 * @param[inout] pp_packet        Pointer to the MQTT message variable header and payload.
 *                                The 5 bytes before the start of the message are assumed by the
 *                                routine to be available to pack the fixed header. However, since
 *                                the fixed header length is variable length, the pointer to the
 *                                start of the MQTT message along with encoded fixed header is
 *                                supplied as output parameter if the procedure was successful.
 *
 * @retval 0xFFFFFFFF if the procedure failed, else length of total MQTT message along with the
 *                    fixed header.
 */
uint32_t mqtt_encode_fixed_header(uint8_t message_type, uint32_t length, uint8_t ** pp_packet);


/**@brief Constructs/encodes connect packet.
 *
 * @param[in]  p_client          Identifies the client for which the procedure is requested.
 *                               All information required for creating the packet like client id,
 *                               clean session flag, retain session flag etc are assumed to be
 *                               populated for the client instance when this procedure is requested.
 * @param[out] pp_packet         Pointer to the MQTT connect message.
 * @param[out] p_packet_length   Length of the connect request.
 *
 * @retval 0xFFFFFFFF if the procedure failed, else length of total MQTT message along with the
 *                    fixed header.
 */
void connect_request_encode(const mqtt_client_t *  p_client,
                            uint8_t             ** pp_packet,
                            uint32_t            *  p_packet_length);

#ifdef __cplusplus
}
#endif

#endif // MQTT_INTERNAL_H_
