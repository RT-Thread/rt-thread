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
#ifndef _CONN_BLE_GAP_SEC_KEYS_H
#define _CONN_BLE_GAP_SEC_KEYS_H

/**@file
 *
 * @defgroup conn_ble_gap_sec_keys GAP Functions for managing memory for security keys on connectivity device
 * @{
 * @ingroup  ser_conn_s130_codecs
 *
 * @brief    GAP Connectivity auxiliary functions for providing static memory required by the SoftDevice. This memory is used to store GAP security keys.
 */

#include "ble_gap.h"
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif


/**@brief GAP connection - keyset mapping structure.
 *
 * @note  This structure is used to map keysets to connection instances, and will be stored in a static table.
 */
typedef struct
{
  uint16_t                conn_handle;     /**< Connection handle. */
  uint8_t                 conn_active;     /**< Indication that keys for this connection are used by the SoftDevice. 0: keys used; 1: keys not used. */
  ble_gap_sec_keyset_t    keyset;          /**< Keyset structure, see @ref ble_gap_sec_keyset_t. */
  ble_gap_enc_key_t       enc_key_own;     /**< Own Encryption Key, see @ref ble_gap_enc_key_t. */
  ble_gap_id_key_t        id_key_own;      /**< Own Identity Key, see @ref ble_gap_id_key_t. */
  ble_gap_sign_info_t     sign_key_own;    /**< Own Signing Information, see @ref ble_gap_sign_info_t. */
  ble_gap_lesc_p256_pk_t  pk_own;          /**< Own Public key, see @ref ble_gap_lesc_p256_pk_t. */
  ble_gap_enc_key_t       enc_key_peer;    /**< Peer Encryption Key, see @ref ble_gap_enc_key_t. */
  ble_gap_id_key_t        id_key_peer;     /**< Peer Identity Key, see @ref ble_gap_id_key_t. */
  ble_gap_sign_info_t     sign_key_peer;   /**< Peer Signing Information, see @ref ble_gap_sign_info_t. */
  ble_gap_lesc_p256_pk_t  pk_peer;         /**< Peer Public key, see @ref ble_gap_lesc_p256_pk_t. */
} ser_ble_gap_conn_keyset_t;

/**@brief Initializes buffer pool. */
void conn_ble_gap_sec_keys_init(void);

/**@brief Allocates instance in m_conn_keys_table[] for storage of encryption keys.
 *
 * @param[out]    p_index             Pointer to the index of allocated instance.
 *
 * @retval NRF_SUCCESS                Success.
 * @retval NRF_ERROR_NO_MEM           No free instance available.
 */
uint32_t conn_ble_gap_sec_context_create(uint32_t *p_index);

/**@brief Releases the instance identified by a connection handle.
 *
 * @param[in]     conn_handle         conn_handle
 *
 * @retval NRF_SUCCESS                Context released.
 * @retval NRF_ERROR_NOT_FOUND        Instance with conn_handle not found.
 */
uint32_t conn_ble_gap_sec_context_destroy(uint16_t conn_handle);

/**@brief Finds index of the instance identified by a connection handle in m_conn_keys_table[].
 *
 * @param[in]     conn_handle         conn_handle
 *
 * @param[out]    p_index             Pointer to the index of entry in the context table corresponding to the given conn_handle.
 *
 * @retval NRF_SUCCESS                Context table entry found.
 * @retval NRF_ERROR_NOT_FOUND        Instance with the conn_handle not found.
 */
uint32_t conn_ble_gap_sec_context_find(uint16_t conn_handle, uint32_t *p_index);
/** @} */

/** @brief Function allocates data from the pool.
 *
 * @param id ID used for buffer identification. If buffer with given ID is already allocated the pointer to that buffer is returned.
 * @return   Allocated buffer of NULL.
 */
uint8_t * conn_ble_gap_ble_data_buf_alloc(uint32_t id);

/** @brief Function for freeing the buffer.
 * @param p_data Buffer to be freed.
 */
uint32_t conn_ble_gap_ble_data_buf_free(uint8_t * p_data);

void conn_ble_gap_scan_data_set(uint8_t * p_scan_data);
void conn_ble_gap_scan_data_unset(bool free);

#ifdef __cplusplus
}
#endif

#endif //_CONN_BLE_GAP_SEC_KEYS_H
