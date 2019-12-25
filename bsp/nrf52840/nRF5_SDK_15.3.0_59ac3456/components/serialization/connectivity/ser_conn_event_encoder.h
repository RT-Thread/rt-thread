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
/**
 * @addtogroup ser_conn Connectivity application code
 * @ingroup ble_sdk_lib_serialization
 * @brief Encoders, decoders, and event handlers related to the Connectivity Chip.
 */

/** @file
 *
 * @defgroup ser_event_encoder Events encoder in the Connectivity Chip
 * @{
 * @ingroup ser_conn
 *
 * @brief Events encoder for BLE SoftDevice.
 *
 * @details This file contains declaration of common function used for serializing BLE SoftDevice
 *          events.
 *
 */
#ifndef SER_CONN_EVENT_ENCODER_H__
#define SER_CONN_EVENT_ENCODER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief A function for encoding a @ref ble_evt_t. The function passes the serialized byte stream
 *        to the transport layer after encoding.
 *
 * @details The function is called by the application scheduler to process an event previously
 *          pulled from BLE SoftDevice.
 *          The function creates a new packet, calls an appropriate event encoder and sends the
 *          packet to the Application Chip.
 *
 * @param[in]   p_event_data   Pointer to event data of type @ref ble_evt_t.
 * @param[in]   event_size     Event data size.
 */
void ser_conn_ble_event_encoder(void * p_event_data, uint16_t event_size);

/**@brief A function for encoding a @ref ant_evt_t. The function passes the serialized byte stream
 *        to the transport layer after encoding.
 *
 * @details The function is called by the application scheduler to process an event previously
 *          pulled from ANT SoftDevice.
 *          The function creates a new packet, calls an appropriate event encoder and sends the
 *          packet to the Application Chip.
 *
 * @param[in]   p_event_data   Pointer to event data of type @ref ant_evt_t.
 * @param[in]   event_size     Event data size.
 */
void ser_conn_ant_event_encoder(void * p_event_data, uint16_t event_size);

#ifdef __cplusplus
}
#endif

#endif /* SER_CONN_EVENT_ENCODER_H__ */

/** @} */
