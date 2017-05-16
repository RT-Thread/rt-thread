/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
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
#ifndef _APP_BLE_GAP_SEC_KEYS_H
#define _APP_BLE_GAP_SEC_KEYS_H

 /**@file
 *
 * @defgroup app_ble_gap_sec_keys GAP Functions for managing memory for security keys in the application device.
 * @{
 * @ingroup  ser_app_s130_codecs
 *
 * @brief    GAP Application auxiliary functions for synchronizing the GAP security keys with the ones stored in the connectivity device.
 */

#include "ble_gap.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SER_MAX_CONNECTIONS
#define SER_MAX_CONNECTIONS 8
#endif
/**@brief GAP connection - keyset mapping structure.
 *
 * @note  This structure is used to map keysets to connection instances and store them in a static table.
 */
typedef struct
{
  uint16_t               conn_handle;    /**< Connection handle.*/
  uint8_t                conn_active;    /**< Indication that keys for this connection are used by the SoftDevice. 0: keys used; 1: keys not used. */
  ble_gap_sec_keyset_t   keyset;         /**< Keyset structure, see @ref ble_gap_sec_keyset_t.*/
} ser_ble_gap_app_keyset_t;

/**@brief Allocates the instance in m_app_keys_table[] for storage of encryption keys.
 *
 * @param[in]     conn_handle         conn_handle
 * @param[out]    p_index             Pointer to the index of the allocated instance.
 *
 * @retval NRF_SUCCESS                Context allocated.
 * @retval NRF_ERROR_NO_MEM           No free instance available.
 */
uint32_t app_ble_gap_sec_context_create(uint16_t conn_handle, uint32_t *p_index);

/**@brief Release the instance identified by a connection handle.
 *
 * @param[in]     conn_handle         conn_handle
 *
 * @retval NRF_SUCCESS                Context released.
 * @retval NRF_ERROR_NOT_FOUND        Instance with conn_handle not found.
 */
uint32_t app_ble_gap_sec_context_destroy(uint16_t conn_handle);

/**@brief Finds index of instance identified by a connection handle in m_app_keys_table[].
 *
 * @param[in]     conn_handle         conn_handle
 *
 * @param[out]    p_index             Pointer to the index of the entry in the context table corresponding to the given conn_handle.
 *
 * @retval NRF_SUCCESS                Context found.
 * @retval NRF_ERROR_NOT_FOUND        Instance with conn_handle not found.
 */
uint32_t app_ble_gap_sec_context_find(uint16_t conn_handle, uint32_t *p_index);
/** @} */


#ifdef __cplusplus
}
#endif

#endif //_APP_BLE_GAP_SEC_KEYS_H
