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
/**@file lwm2m_objects_tlv.h
 *
 * @defgroup iot_sdk_lwm2m_objects_tlv OMA LWM2M object TLV encoder and decoder API
 * @ingroup iot_sdk_lwm2m
 * @{
 * @brief OMA LWM2M object TLV encoder and decoder API.
 */

#ifndef LWM2M_OBJECTS_TLV_H__
#define LWM2M_OBJECTS_TLV_H__

#include <stdint.h>
#include "lwm2m_objects.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Decode a LWM2M server object from a TLV byte buffer.
 *
 * @note    Resource values NOT found in the tlv will not be altered.
 *
 * @warning lwm2m_string_t and lwm2m_opaque_t values will point to the byte buffer and needs
 *          to be copied by the application before the byte buffer is freed.
 *
 * @param[out] p_server   Pointer to a LWM2M server object to be filled by the decoded TLVs.
 * @param[in]  p_buffer   Pointer to the TLV byte buffer to be decoded.
 * @param[in]  buffer_len Size of the buffer to be decoded.
 *
 * @retval NRF_SUCCESS If decoding was successful.
 */
uint32_t lwm2m_tlv_server_decode(lwm2m_server_t * p_server,
                                 uint8_t *        p_buffer,
                                 uint32_t         buffer_len);

/**@brief Encode a LWM2M server object to a TLV byte buffer.
 *
 * @param[out]   p_buffer     Pointer to a byte buffer to be used to fill the encoded TLVs.
 * @param[inout] p_buffer_len Value by reference indicating the size of the buffer provided.
 *                            Will return the number of used bytes on return.
 * @param[in]    p_server     Pointer to the LWM2M server object to be encoded into TLVs.
 *
 * @retval NRF_SUCCESS If the encoded was successful.
 */
uint32_t lwm2m_tlv_server_encode(uint8_t *        p_buffer,
                                 uint32_t *       p_buffer_len,
                                 lwm2m_server_t * p_server);

/**@brief Decode a LWM2M security object from a TLV byte buffer.
 *
 * @note    Resource values NOT found in the tlv will not be altered.
 *
 * @warning lwm2m_string_t and lwm2m_opaque_t values will point to the byte buffer and needs
 *          to be copied by the application before the byte buffer is freed.
 *
 * @param[out] p_security Pointer to a LWM2M server object to be filled by the decoded TLVs.
 * @param[in]  p_buffer   Pointer to the TLV byte buffer to be decoded.
 * @param[in]  buffer_len Size of the buffer to be decoded.
 *
 * @retval NRF_SUCCESS If decoding was successful.
 */
uint32_t lwm2m_tlv_security_decode(lwm2m_security_t * p_security,
                                   uint8_t *          p_buffer,
                                   uint32_t           buffer_len);

/**@brief Encode a LWM2M security object to a TLV byte buffer.
 *
 * @param[out]   p_buffer     Pointer to a byte buffer to be used to fill the encoded TLVs.
 * @param[inout] p_buffer_len Value by reference indicating the size of the buffer provided.
 *                            Will return the number of used bytes on return.
 * @param[in]    p_security   Pointer to the LWM2M security object to be encoded into TLVs.
 *
 * @retval NRF_SUCCESS If the encoded was successful.
 */
uint32_t lwm2m_tlv_security_encode(uint8_t *          p_buffer,
                                   uint32_t *         p_buffer_len,
                                   lwm2m_security_t * p_security);

#ifdef __cplusplus
}
#endif

#endif // LWM2M_OBJECTS_TLV_H__

/** @} */
