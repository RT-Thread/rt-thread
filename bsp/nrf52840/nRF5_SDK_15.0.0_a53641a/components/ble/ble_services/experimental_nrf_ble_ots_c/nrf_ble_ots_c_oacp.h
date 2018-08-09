/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
 * @defgroup nrf_ble_ots_c_oacp Object Transfer Service Client Object Action Control Point
 * @{
 * @ingroup  nrf_ble_ots_c
 * @brief    Object Action Control Point module
 *
 * @details  This is the Object Action Control Point module of the Object Transfer Service (OTS) client. 
 */
 
#ifndef NRF_BLE_OTS_C_OACP_H__
#define NRF_BLE_OTS_C_OACP_H__

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


/**@brief Function for enabling remote indication.

   @param[in,out] p_ots_c Pointer to Object Transfer client structure.
   @param[in]     enable  True to enable Object Action Control Point (OACP) indication, false to disable.

   @retval NRF_SUCCESS Operation success.
   @return             If functions from other modules return errors to this function,
                       the @ref nrf_error are propagated.
*/
ret_code_t nrf_ble_ots_c_indication_enable(nrf_ble_ots_c_t * const p_ots_c,
                                           bool                const enable);


/**@brief Function for requesting a write of an object.

   @details With this function we let the peer know the length of the object we want to write.
            (The object itself is not written by this function.)
            The peer will indicate a response on the Object Action Control Point.
            If the write is accepted (the event NRF_BLE_OTS_C_OACP_RES_SUCCESS ), an object can be
            transfered with @ref nrf_ble_ots_c_l2cap_obj_send.

   @param[in,out] p_ots_c  Pointer to Object Transfer client structure.
   @param[in]     offset   Offset of the write.
   @param[in]     len      length of the object to write.
   @param[in]     truncate True to let the write truncate on the object.

   @retval NRF_SUCCESS             Operation success.
   @retval NRF_ERROR_INVALID_STATE Module is not initialized, or the handles of the peer OACP
                                   are invalid.
   @return                         If functions from other modules return errors to this function,
                                   the @ref nrf_error are propagated.
*/
ret_code_t nrf_ble_ots_c_oacp_write_object(nrf_ble_ots_c_t * const p_ots_c, uint32_t offset, uint32_t len, bool truncate);

/**@brief Function for requesting a read of an object.

   @param[in,out] p_ots_c Pointer to Object Transfer client structure.
   @param[in]     offset  Offset of the read.
   @param[in]     len     length of the read.

   @retval NRF_SUCCESS Operation success.
   @return             If functions from other modules return errors to this function,
                       the @ref nrf_error are propagated.
*/
ret_code_t nrf_ble_ots_c_oacp_read_object(nrf_ble_ots_c_t * const p_ots_c, uint32_t offset, uint32_t len);


/**@brief Function for handling the Application's BLE Stack events.

   @param[in,out] p_ots_c   Pointer to Object Transfer client structure.
   @param[in]     p_ble_evt Pointer to the BLE event received.
*/
void ots_c_oacp_on_ble_evt(nrf_ble_ots_c_t * const p_ots_c,
                           ble_evt_t const * const p_ble_evt);


#endif // NRF_BLE_OTS_C_OACP_H__

/** @} */
