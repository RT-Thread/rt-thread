/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
 * @defgroup nrf_ble_ots_c_l2cap Object Transfer Service Client
 * @{
 * @ingroup  nrf_ble_ots_c
 * @brief    Object Transfer Service client module
 *
 * @details  This is the main module of the Object Transfer Service (OTS) client. 
 */
 
#ifndef NRF_BLE_OTS_C_L2CAP_H__
#define NRF_BLE_OTS_C_L2CAP_H__

#include <stdint.h>
#include "ble_gattc.h"
#include "ble.h"
#include "nrf_error.h"
#include "ble_srv_common.h"
#include "ble_db_discovery.h"
#include "sdk_errors.h"
#include "nrf_ble_ots_c.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Function for handling the Application's BLE Stack events.

   @param[in,out] p_ots_c   Pointer to Object Transfer client structure.
   @param[in]     p_ble_evt Pointer to the BLE event received.
*/
void ots_c_l2cap_on_ble_evt(nrf_ble_ots_c_t * const p_ots_c,
                            ble_evt_t const  * const p_ble_evt);


/**@brief Function sending an object.

   @details This Function will only succeed in sending an object if the peer is in a state to
            receive it. call @ref nrf_ble_ots_c_oacp_write_object before this function.

   @param[in,out] p_ots_c Pointer to Object Transfer client structure.
   @param[in,out] p_obj   Pointer to object that will be sent to the peer.
*/
ret_code_t nrf_ble_ots_c_l2cap_obj_send(nrf_ble_ots_c_t * const p_ots_c, ble_data_t  * p_obj);


/**@brief Function for receiving an object.

   @details This Function will only succeed in receiving an object if the peer is in a state to
            send it. call @ref nrf_ble_ots_c_oacp_read_object before this function.

   @param[in,out] p_ots_c Pointer to Object Transfer client structure.
   @param[in,out] p_obj   Pointer to buffer where the received data will be stored.
*/
ret_code_t nrf_ble_ots_c_l2cap_obj_receive(nrf_ble_ots_c_t * const p_ots_c, ble_data_t  * p_obj);


#endif // NRF_BLE_OTS_C_L2CAP_H__

/** @} */
