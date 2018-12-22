/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup ble_dfu Buttonless DFU Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Buttonless DFU Service module.
 *
 * @details
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_DFU_H__
#define BLE_DFU_H__

#include <stdint.h>
#include "ble_srv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLE_DFU_BUTTONLESS_CHAR_UUID        0x0003

/**< Nordic vendor specific base UUID. */
#define BLE_NORDIC_VENDOR_BASE_UUID                 \
{{                                                  \
    0x50, 0xEA, 0xDA, 0x30, 0x88, 0x83, 0xB8, 0x9F, \
    0x60, 0x4F, 0x15, 0xF3, 0x00, 0x00, 0xC9, 0x8E  \
}}

#define BLE_DFU_ENTER_BOOTLOADER 0x01

typedef enum {
    BLE_DFU_EVT_ENTERING_BOOTLOADER,   /**< Event indicating that the bootloader will be entered after return of this event.*/
    BLE_DFU_EVT_INDICATION_ENABLED,    /**< Indication that the control point is enabled.*/
    BLE_DFU_EVT_INDICATION_DISABLED    /**< Indication that the control point is disabled.*/
} ble_dfu_evt_type_t;

typedef struct {
    ble_dfu_evt_type_t type;
} ble_dfu_evt_t;

/* Forward declaration of the ble_dfu_type type. */
typedef struct ble_dfu_s ble_dfu_t;

/**@brief Nordic Buttonless DFU Service event handler type. */
typedef void (*ble_dfu_evt_handler_t) (ble_dfu_t * p_dfu, ble_dfu_evt_t * p_evt);



// Control Point response values
typedef enum
{
    DFU_RSP_RESERVED              = 0x00,                                        /**< Reserved for future use. */
    DFU_RSP_SUCCESS               = 0x01,                                        /**< Success. */
    DFU_RSP_OP_CODE_NOT_SUPPORTED = 0x02,                                        /**< Op Code not supported. */
    DFU_RSP_OPERATION_FAILED      = 0x04,                                        /**< Operation Failed. */
    DFU_RSP_CCCD_CONFIG_IMPROPER  = BLE_GATT_STATUS_ATTERR_CPS_CCCD_CONFIG_ERROR /**< CCCD is improperly configured. */
} ble_dfu_rsp_code_t;

// Control Point Op Code values
typedef enum
{
    DFU_OP_RESERVED                         = 0x00, /**< Reserved for future use. */
    DFU_OP_ENTER_BOOTLOADER                 = 0x01, /**< Enter bootloader. */
    DFU_OP_RESPONSE_CODE                    = 0x20  /**< Response code. */
} ble_dfu_buttonless_op_code_t;



struct ble_dfu_s {
    uint8_t                     uuid_type;                      /**< UUID type for DFU UUID. */
    uint16_t                    service_handle;                 /**< Handle of DFU (as provided by the SoftDevice). */
    uint16_t                    conn_handle;
    ble_gatts_char_handles_t    control_point_char;             /**< Handles related to the DFU Control Point characteristic. */
    bool                        is_ctrlpt_indication_enabled;

    ble_dfu_evt_handler_t       evt_handler;                    /**< Event handler which is called right before. */

    bool                        is_waiting_for_reset;           /**< Flag indicating that the device will enter bootloader. */
};

typedef struct {
    ble_dfu_evt_handler_t       evt_handler;                    /**< Event handler which is called right before. */
    security_req_t              ctrl_point_security_req_write_perm;      /**< Read security level of the LN Control Point characteristic. */
    security_req_t              ctrl_point_security_req_cccd_write_perm; /**< CCCD write security level of the LN Control Point characteristic. */
} ble_dfu_init_t;


/**@brief Function for initializing the Device Firmware Update module
 *
 *
 * @param[in]   p_dfu        DFU Service structure.
 * @param[in]   p_dfu_init   The structure containing the values of characteristics needed by the
 *                           service.
 *
 * @return      NRF_SUCCESS on successful initialization of service.
 */
uint32_t ble_dfu_init(ble_dfu_t * p_dfu, const ble_dfu_init_t * p_dfu_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @param[in]   p_dfu      DFU Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_dfu_on_ble_evt(ble_dfu_t * p_dfu, ble_evt_t * p_ble_evt);


#ifdef __cplusplus
}
#endif

#endif // BLE_DIS_H__

/** @} */
