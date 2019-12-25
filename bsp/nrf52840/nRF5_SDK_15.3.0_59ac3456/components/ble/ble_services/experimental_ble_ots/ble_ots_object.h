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
 * @defgroup ble_sdk_srv_ots_obj Object Transfer Service, Object characteristics
 * @{
 * @ingroup  ble_ots
 * @brief    Object Transfer Service module
 *
 * @details  This module is responsible for the object properties characteristics.
 */

#ifndef BLE_OTS_OBJECT_H__
#define BLE_OTS_OBJECT_H__

#include <stdint.h>
#include "ble_ots.h"

/**@brief Function for initializing the Object Transfer Object representation characteristics.
 *
 * @param[out]  p_ots_object_chars Object Transfer Service object characteristics representation structure. *                                        This structure will have to be supplied by the application. It *                                        will be initialized by this function, and will later be used to *                                        identify this particular instance.
 * @param[in]   p_ots_object_chars_init   Information needed to initialize the module.
 *
 * @return      NRF_SUCCESS on successful initialization, otherwise an error code.
 */
uint32_t ble_ots_object_representation_init(ble_ots_object_chars_t      * p_ots_object_chars,
                                            ble_ots_object_chars_init_t * p_ots_object_chars_init);

/**@brief Refresh the characteristics of the current object.
 * @param[in] p_ots_object_chars Pointer the the object characteristics.
 * @return NRF_SUCCESS if everything was refreshed.
 */
uint32_t ble_ots_object_refresh_current(ble_ots_object_chars_t * p_ots_object_chars);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the list filter module.
 *
 * @param[in]  p_ots_object_chars   Pointer the the object characteristics.
 * @param[in]  p_ble_evt            Event received from the BLE stack.
 */
void ble_ots_object_on_ble_evt(ble_ots_object_chars_t * p_ots_object_chars,
                               ble_evt_t const * p_ble_evt);

#endif // BLE_OTS_OBJECT_H__

/** @} */ // End tag for the file.
