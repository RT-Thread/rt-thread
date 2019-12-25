/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#ifndef BLE_L2CAP_EVT_APP_H__
#define BLE_L2CAP_EVT_APP_H__

/**@file
 *
 * @defgroup ble_l2cap_evt_app L2CAP Application event decoders
 * @{
 * @ingroup  ser_app_s130_codecs
 *
 * @brief    L2CAP Application event decoders.
 */
#include "ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Decodes ble_l2cap_evt_rx event.
 *
 * If \p p_event is null, the required length of \p p_event is returned in \p p_event_len.
 *
 * @param[in] p_buf            Pointer to the beginning of an event packet.
 * @param[in] packet_len       Length (in bytes) of the event packet.
 * @param[in,out] p_event      Pointer to a \ref ble_evt_t buffer where the decoded event will be
 *                             stored. If NULL, required length will be returned in \p p_event_len.
 * @param[in,out] p_event_len  \c in: Size (in bytes) of \p p_event buffer.
 *                             \c out: Length of decoded contents of \p p_event.
 *
 * @retval NRF_SUCCESS               Decoding success.
 * @retval NRF_ERROR_NULL            Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH  Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_DATA_SIZE       Decoding failure. Length of \p p_event is too small to
 *                                   hold decoded event.
 */
uint32_t ble_l2cap_evt_rx_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              ble_evt_t * const     p_event,
                              uint32_t * const      p_event_len);

uint32_t ble_l2cap_evt_ch_setup_request_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              ble_evt_t * const     p_event,
                              uint32_t * const      p_event_len);

uint32_t ble_l2cap_evt_ch_setup_refused_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              ble_evt_t * const     p_event,
                              uint32_t * const      p_event_len);

uint32_t ble_l2cap_evt_ch_setup_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              ble_evt_t * const     p_event,
                              uint32_t * const      p_event_len);

uint32_t ble_l2cap_evt_ch_released_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              ble_evt_t * const     p_event,
                              uint32_t * const      p_event_len);

uint32_t ble_l2cap_evt_ch_sdu_buf_released_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              ble_evt_t * const     p_event,
                              uint32_t * const      p_event_len);

uint32_t ble_l2cap_evt_ch_credit_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              ble_evt_t * const     p_event,
                              uint32_t * const      p_event_len);

uint32_t ble_l2cap_evt_ch_rx_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              ble_evt_t * const     p_event,
                              uint32_t * const      p_event_len);


uint32_t ble_l2cap_evt_ch_tx_dec(uint8_t const * const p_buf,
                              uint32_t              packet_len,
                              ble_evt_t * const     p_event,
                              uint32_t * const      p_event_len);
/** @} */

#ifdef __cplusplus
}
#endif

#endif
