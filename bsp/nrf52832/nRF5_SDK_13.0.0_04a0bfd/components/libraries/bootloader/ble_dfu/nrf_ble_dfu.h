/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
 * @defgroup nrf_ble_dfu DFU BLE Service
 * @{
 * @ingroup  sdk_nrf_bootloader
 * @brief    Device Firmware Update (DFU) transport layer for <em>Bluetooth</em> low energy.
 *
 * @details  The Device Firmware Update (DFU) Service is a GATT-based service that can be used for
 *           performing firmware updates over BLE. Note that this implementation uses
 *           vendor-specific UUIDs for the service and characteristics and is intended to demonstrate
 *           firmware updates over BLE. See @ref lib_dfu_transport_ble "DFU Transport: BLE" for more information on the service and the profile.
 */

#ifndef NRF_BLE_DFU_H__
#define NRF_BLE_DFU_H__

#include <stdint.h>
#include "ble_gatts.h"
#include "ble.h"


#ifdef __cplusplus
extern "C" {
#endif

// This is a 16-bit UUID.
#define BLE_DFU_SERVICE_UUID                 0xFE59                       //!< The UUID of the DFU Service.

// These UUIDs are used with the Nordic base address to create a 128-bit UUID (0x8EC9XXXXF3154F609FB8838830DAEA50).
#define BLE_DFU_CTRL_PT_UUID                 0x0001                       //!< The UUID of the DFU Control Point.
#define BLE_DFU_PKT_CHAR_UUID                0x0002                       //!< The UUID of the DFU Packet Characteristic.


/**@brief   BLE DFU opcodes.
 *
 * @details These types of opcodes are used in control point access.
 */
typedef enum
{
    BLE_DFU_OP_CODE_CREATE_OBJECT               = 0x01,                                 /**< Value of the opcode field for a 'Create object' request. */
    BLE_DFU_OP_CODE_SET_RECEIPT_NOTIF           = 0x02,                                 /**< Value of the opcode field for a 'Set Packet Receipt Notification' request. */
    BLE_DFU_OP_CODE_CALCULATE_CRC               = 0x03,                                 /**< Value of the opcode field for a 'Calculating checksum' request. */
    BLE_DFU_OP_CODE_EXECUTE_OBJECT              = 0x04,                                 /**< Value of the opcode field for an 'Initialize DFU parameters' request. */
    BLE_DFU_OP_CODE_SELECT_OBJECT               = 0x06,                                 /**< Value of the opcode field for a 'Select object' request. */
    BLE_DFU_OP_CODE_RESPONSE                    = 0x60                                  /**< Value of the opcode field for a response.*/
} ble_dfu_op_code_t;


/**@brief   DFU Service.
 *
 * @details This structure contains status information related to the service.
 */
typedef struct
{
    uint16_t                     service_handle;                        /**< Handle of the DFU Service (as provided by the SoftDevice). */
    uint8_t                      uuid_type;                             /**< UUID type assigned to the DFU Service by the SoftDevice. */
    ble_gatts_char_handles_t     dfu_pkt_handles;                       /**< Handles related to the DFU Packet Characteristic. */
    ble_gatts_char_handles_t     dfu_ctrl_pt_handles;                   /**< Handles related to the DFU Control Point Characteristic. */
} ble_dfu_t;


/**@brief      Function for initializing the DFU Service.
 *
 * @retval     NRF_SUCCESS If the DFU Service and its characteristics were successfully added to the
 *             SoftDevice. Otherwise, an error code is returned.
 */
uint32_t ble_dfu_transport_init(void);


/**@brief      Function for closing down the DFU Service and disconnecting from the host.
 *
 * @retval     NRF_SUCCESS If the DFU Service was correctly closed down.
 */
uint32_t ble_dfu_transport_close(void);

#ifdef __cplusplus
}
#endif

#endif // NRF_BLE_DFU_H__

/** @} */
