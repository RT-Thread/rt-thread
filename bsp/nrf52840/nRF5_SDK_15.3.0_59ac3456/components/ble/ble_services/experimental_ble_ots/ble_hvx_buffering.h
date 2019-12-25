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
 * @defgroup ble_sdk_srv_ots_buf Object Transfer Service, HVX buffering
 * @{
 * @ingroup  ble_ots
 * @brief    Object Transfer Service module
 *
 * @details  This module is responsible for buffering indications and notifications. 
 */

#ifndef BLE_HVX_BUFFERING_H__
#define BLE_HVX_BUFFERING_H__


#include <stdint.h>
#include "ble_types.h"
#include "ble_gatts.h"

#define BLE_HVX_BUF_LEN  (1 << 3) // 8
#define BLE_HVX_BUF_MASK (BLE_HVX_BUF_LEN-1)

/**@brief ble_hvx_t represents one notification/indication. */
typedef struct {
    uint16_t               conn_handle;                    /**< The associated connection handle. */
    uint8_t                data[BLE_GATT_ATT_MTU_DEFAULT]; /**< The hvx data. */
    uint16_t               data_len;
    ble_gatts_hvx_params_t params;                  /**< Parameters of the hvx. */
} ble_hvx_t;

/**@brief ble_hvx_buf_t is the structure holding the state of the hvx buffering module. */
typedef struct {   
    ble_hvx_t               buf[BLE_HVX_BUF_LEN];   /**< A buffer of nofications/indications. */

    uint8_t                 insert_index;
    uint8_t                 read_index;
} ble_hvx_buf_t;

/**@brief Function for initializing the HVX buffer module.
 *
 * @param[out]  p_ble_hvx_buf   HVX buffering structure.
 * @return      NRF_SUCCESS     If the given paramer is valid.
 */
uint32_t ble_hvx_init(ble_hvx_buf_t * p_ble_hvx_buf);

/**@brief Function for obtaining the pointer to the next hvx. The user can then fill out the hvx structure.
 *
 * @param[in]   p_ble_hvx_buf   HVX buffering structure.
 * @return      ble_hvx_t *     If there is a free ble_hvx_t.
 * @return      NULL            If there is no free ble_hvx_t, or an invalid parameter is supplied.
 */
ble_hvx_t * ble_hvx_get_p_to_next_hvx(ble_hvx_buf_t * p_ble_hvx_buf);

/**@brief Function for sending something from the HVX buffer.
 *
 * @param[in]   p_ble_hvx_buf   HVX buffering structure.
 * @return      NRF_SUCCESS     If a indication/notification was successfully sent.
 */
uint32_t ble_hvx_buffer_process(ble_hvx_buf_t * p_ble_hvx_buf);


#endif // BLE_HVX_BUFFERING_H__

/** @} */

