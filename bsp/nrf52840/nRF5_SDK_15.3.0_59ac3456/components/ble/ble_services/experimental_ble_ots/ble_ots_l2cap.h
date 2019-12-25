/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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

/**@file
 *
 * @defgroup ble_sdk_srv_ots_l2cap Object Transfer Service, l2cap channel handling
 * @{
 * @ingroup  ble_ots
 * @brief    Object Transfer Service module
 *
 * @details  This module is responsible for handling the l2cap connection oriented channels.
 */

#ifndef BLE_OTS_L2CAP_H__
#define BLE_OTS_L2CAP_H__

#include <stdint.h>
#include "ble_ots.h"

/**@brief Function for initializing the Object Transfer Service l2cap module.
 *
 * @param[out]  p_ots_l2cap         Object Transfer Service l2cap structure. This structure will have to be
 *                                  supplied by the application. It will be initialized by this function,
 *                                  and will later be used to identify this particular instance.
 * @param[in]   p_ots_l2cap_init    Information needed to initialize the module.
 *
 * @return      NRF_SUCCESS on successful initialization, otherwise an error code.
 */
uint32_t ble_ots_l2cap_init(ble_ots_l2cap_t * p_ots_l2cap, ble_ots_l2cap_init_t * p_ots_l2cap_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the l2cap module.
 *
 * @param[in]   p_ots_l2cap Object transfer service l2cap module structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void ble_ots_l2cap_on_ble_evt(ble_ots_l2cap_t * p_ots_l2cap, ble_evt_t const * p_ble_evt);


/**@brief Function starting to send the data in the transfer buffer.
 *
 * @param[in]   p_ots_l2cap Object transfer service l2cap module structure.
 * @param[in]   p_data      Pointer to the data to be sent.
 * @param[in]   data_len    The length of the data to be sent.
 *
 * @return      NRF_SUCCESS             If the transmission was started.
 * @return      NRF_ERROR_INVALID_STATE When in an invalid state. Otherwise an other error code.
 */
uint32_t ble_ots_l2cap_obj_send(ble_ots_l2cap_t * p_ots_l2cap, uint8_t * p_data, uint16_t data_len);


/**@brief Function starting to receive data to the transfer buffer.
 *
 * @param[in]   p_ots_l2cap     Object transfer service l2cap module structure.
 * @param[in]   len             The length of the data to be received.
 *
 * @return      NRF_SUCCESS             If the transmission was started.
 * @return      NRF_ERROR_INVALID_STATE When in an invalid state. Otherwise an other error code.
 */
uint32_t ble_ots_l2cap_start_recv(ble_ots_l2cap_t * p_ots_l2cap, uint16_t len);


/**@brief Function that checks if the channel is available for transmission.
 *
 * @param[in]   p_ots_l2cap     Object transfer service l2cap module structure.
 *
 * @return      true if the channel is available.
 */
bool ble_ots_l2cap_is_channel_available(ble_ots_l2cap_t * p_ots_l2cap);


/**@brief Function starting to abort the current transmission.
 *
 * @param[in]   p_ots_l2cap     Object transfer service l2cap module structure.
 *
 * @return      NRF_SUCCESS             If the transmission was aborted.
 * @return      NRF_ERROR_INVALID_STATE When in an invalid state. Otherwise an other error code.
 */
uint32_t ble_ots_l2cap_abort_transmission(ble_ots_l2cap_t * p_ots_l2cap);

#endif // BLE_OTS_L2CAP_H__

/** @} */ // End tag for the file.

