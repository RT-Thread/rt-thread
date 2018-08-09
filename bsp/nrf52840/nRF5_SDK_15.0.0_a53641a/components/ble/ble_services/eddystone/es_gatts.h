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

#ifndef ES_GATTS_H__
#define ES_GATTS_H__

#include <stdint.h>
#include "nrf_ble_escs.h"

/**
 * @file
 * @defgroup eddystone_gatts GATTS
 * @brief Functions for handling GATTS write and read requests.
 * @ingroup eddystone
 * @{
 */

ret_code_t es_gatts_init(nrf_ble_escs_t * p_ble_escs);

/**@brief Function for handling all write requests from the Central.
 *
 * @param[in]   p_escs      Pointer to the Eddystone Configuration Service.
 * @param[in]   uuid        The UUID of the characteristic that is being written to.
 * @param[in]   val_handle  Value handle field of the characteristic handle of the characteristic that is being written to.
 * @param[in]   p_data      Pointer to the data to be written.
 * @param[in]   length      Length of the data to be written.
 *
 */
void es_gatts_handle_write(nrf_ble_escs_t     * p_escs,
                                uint16_t        uuid,
                                uint16_t        val_handle,
                                uint8_t const * p_data,
                                uint16_t        length);


/**@brief Function for handling all read requests from the Central.
 *
 * @param[in]   p_escs      Pointer to the Eddystone Configuration Service.
 * @param[in]   uuid        The UUID of the characteristic that is being read from.
 * @param[in]   val_handle  Value handle field of the characteristic handle of the characteristic that is being read from.
 *
 */
void es_gatts_handle_read(nrf_ble_escs_t * p_escs, uint16_t uuid, uint16_t val_handle);

/**@brief Function for sending an RW-authorization reply.
 *
 * @param[in]   p_escs      Pointer to the Eddystone Configuration Service.
 * @param[in]   p_reply     Pointer to the reply to send.
 *
 * @retval NRF_SUCCESS              If the reply was successfully issued to the SoftDevice.
 * @retval NRF_ERROR_NULL           If either of the pointers @p p_escs or @p p_reply is NULL.
 * @retval NRF_ERROR_INVALID_STATE  If the connection handle of @p p_escs is invalid.
 * @return                          Otherwise, an error code from sd_ble_gatts_rw_authorize_reply() is returned.
 */
ret_code_t es_gatts_send_reply(nrf_ble_escs_t * p_escs, ble_gatts_rw_authorize_reply_params_t * p_reply);

/**@brief Function for sending an RW-authorization reply with status 'Operation not permitted'.
 *
 * @param[in]   p_escs      Pointer to the Eddystone Configuration Service.
 * @param[in]   op_is_read  Flag that specifies if the operation being responded to is a 'read' operation.
                            If false, a 'write' operation is assumed.
 *
 * @retval NRF_ERROR_NULL   If @p p_escs is NULL.
 * @return                  Otherwise, the error code from es_gatts_send_reply() is returned.
 */
ret_code_t es_gatts_send_op_not_permitted(nrf_ble_escs_t * p_escs, bool op_is_read);

/**
 * @}
 */

#endif // ES_GATTS_H__
