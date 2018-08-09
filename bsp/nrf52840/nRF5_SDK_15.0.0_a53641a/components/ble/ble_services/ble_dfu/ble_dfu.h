/**
 * Copyright (c) 2012 - 2018, Nordic Semiconductor ASA
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
 * @details This module implements a proprietary Buttonless Secure DFU Service. The service can
 *          be configured to support bonds or not. The bond support configuration must correspond to the
 *          requirement of Secure DFU bootloader.
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_DFU_H__
#define BLE_DFU_H__

#include <stdint.h>
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"


#ifdef __cplusplus
extern "C" {
#endif


/**@brief   SoC observer priority.
 * @details Priority of this module's SoC event handler.
 */
#define BLE_DFU_SOC_OBSERVER_PRIO   1

#define BLE_DFU_BUTTONLESS_CHAR_UUID        (0x0003)    /**< Value combined with vendor-specific base to create Unbonded Buttonless characteristic UUID. */
#define BLE_DFU_BUTTONLESS_BONDED_CHAR_UUID (0x0004)    /**< Value combined with vendor-specific base to create Bonded Buttonless characteristic UUID. */


/**@brief Nordic vendor-specific base UUID.
 */
#define BLE_NORDIC_VENDOR_BASE_UUID                 \
{{                                                  \
    0x50, 0xEA, 0xDA, 0x30, 0x88, 0x83, 0xB8, 0x9F, \
    0x60, 0x4F, 0x15, 0xF3, 0x00, 0x00, 0xC9, 0x8E  \
}}


/**@brief Nordic Buttonless DFU Service event type .
 */
typedef enum
{
    BLE_DFU_EVT_BOOTLOADER_ENTER_PREPARE,   /**< Event indicating that the device is preparing to enter bootloader.*/
    BLE_DFU_EVT_BOOTLOADER_ENTER,           /**< Event indicating that the bootloader will be entered after return of this event.*/
    BLE_DFU_EVT_BOOTLOADER_ENTER_FAILED,    /**< Failure to enter bootloader mode.*/
    BLE_DFU_EVT_RESPONSE_SEND_ERROR,        /**< Failure to send response.*/
} ble_dfu_buttonless_evt_type_t;


/**@brief Nordic Buttonless DFU Service event handler type.
 */
typedef void (*ble_dfu_buttonless_evt_handler_t) (ble_dfu_buttonless_evt_type_t p_evt);
/**@brief Enumeration of Bootloader DFU response codes.
 */
typedef enum
{
    DFU_RSP_INVALID               = 0x00,                                           /**< Invalid op code. */
    DFU_RSP_SUCCESS               = 0x01,                                           /**< Success. */
    DFU_RSP_OP_CODE_NOT_SUPPORTED = 0x02,                                           /**< Op code not supported. */
    DFU_RSP_OPERATION_FAILED      = 0x04,                                           /**< Operation failed. */
    DFU_RSP_ADV_NAME_INVALID      = 0x05,                                           /**< Requested advertisement name is too short or too long. */
    DFU_RSP_BUSY                  = 0x06,                                           /**< Ongoing async operation. */
    DFU_RSP_NOT_BONDED            = 0x07,                                           /**< Buttonless unavailable due to device not bonded. */
    DFU_RSP_CCCD_CONFIG_IMPROPER  = BLE_GATT_STATUS_ATTERR_CPS_CCCD_CONFIG_ERROR    /**< CCCD is improperly configured. */
} ble_dfu_buttonless_rsp_code_t;


/**@brief Enumeration of Bootloader DFU Operation codes.
 */
typedef enum
{
    DFU_OP_RESERVED         = 0x00, /**< Reserved for future use. */
    DFU_OP_ENTER_BOOTLOADER = 0x01, /**< Enter bootloader. */
    DFU_OP_SET_ADV_NAME     = 0x02, /**< Set advertisement name to use in DFU mode. */
    DFU_OP_RESPONSE_CODE    = 0x20  /**< Response code. */
} ble_dfu_buttonless_op_code_t;


/**@brief Type holding memory used by Secure DFU Buttonless Service.
  */
typedef struct
{
    uint8_t                             uuid_type;                      /**< UUID type for DFU UUID. */
    uint16_t                            service_handle;                 /**< Service Handle of DFU (as provided by the SoftDevice). */
    uint16_t                            conn_handle;                    /**< Connection handle for the current peer. */
    ble_gatts_char_handles_t            control_point_char;             /**< Handles related to the DFU Control Point characteristic. */
    uint32_t                            peers_count;                    /**< Counter to see how many persistently stored peers must be updated for Service Changed indication. This value will be counted down when comparing write requests. */
    ble_dfu_buttonless_evt_handler_t    evt_handler;                    /**< Event handler that is called upon Buttonless DFU events. See @ref ble_dfu_buttonless_evt_type_t. */
    bool                                is_ctrlpt_indication_enabled;   /**< Flag indicating that indication is enabled for the control point. */
    bool                                is_waiting_for_reset;           /**< Flag indicating that the device will enter bootloader. */
    bool                                is_waiting_for_svci;            /**< Flag indicating that the device is waiting for async SVCI operation */
} ble_dfu_buttonless_t;


/**@brief Type used to initialize the Secure DFU Buttonless Service.
 */
typedef struct
{
    ble_dfu_buttonless_evt_handler_t evt_handler;                       /**< Bootloader event handler. */
} ble_dfu_buttonless_init_t;


/**@brief Function for initializing the Device Firmware Update module.
 *
 * @param[in]   p_dfu_init   Structure containing the values of characteristics needed by the
 *                           service.
 * @retval      NRF_SUCCESS on successful initialization of the service.
 */
uint32_t ble_dfu_buttonless_init(const ble_dfu_buttonless_init_t * p_dfu_init);


/**@brief Function for initializing the async SVCI interface.
 *
 * @warning Ensure that no interrupts are triggered when calling this functions as
 *          interrupts and exceptions are forwarded to the bootloader for the period
 *          of the call and may be lost.
 *
 * @details This configures the async interface for calling to the
 *          bootloader through SVCI interface.
 *
 * @retval NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_dfu_buttonless_async_svci_init(void);


/**@brief Function to initialize the backend Secure DFU Buttonless service which is either
 *        supports bonds or not.
 *
 * @note    Do not call this function directly. It is called internally by @ref ble_dfu_buttonless_init.
 *
 * @param[in] p_dfu     Nordic DFU Service structure.
 *
 * @return NRF_SUCCESS  On sucessfully initializing, otherwise an error code.
 */
uint32_t ble_dfu_buttonless_backend_init(ble_dfu_buttonless_t * p_dfu);



/**@brief Function for adding the buttonless characteristic.
 *
 * @note This will be implemented differently on bonded/unbonded Buttonless DFU service.
 *
 * @param[in] p_dfu       Nordic DFU Service structure.
 *
 * @return NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_dfu_buttonless_char_add(ble_dfu_buttonless_t * p_dfu);


/**@brief Function for sending a response back to the client.
 *
 * @param[in]   op_code     Operation code to send the response for.
 * @param[in]   rsp_code    Response code for the operation.
 *
 * @retval NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_dfu_buttonless_resp_send(ble_dfu_buttonless_op_code_t op_code, ble_dfu_buttonless_rsp_code_t rsp_code);


/**@brief Function for handling the application's BLE stack events.
 *
 * @details Handles all events from the BLE stack of interest to the DFU buttonless service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   BLE context structure.
 */
void ble_dfu_buttonless_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for handling control point write requests.
 *
 * @details Handles write requests to the control point in
 *          DFU with bonds or without bonds.
 *
 * @param[in]   p_evt_write     GATTS write event.
 */
void ble_dfu_buttonless_on_ctrl_pt_write(ble_gatts_evt_write_t const * p_evt_write);


/**@brief Function for preparing to enter the bootloader.
 *
 * @warning This function is called directly. (It is called internally).
 *
 * @retval Any error code from calling @ref sd_ble_gap_disconnect.
 */
uint32_t ble_dfu_buttonless_bootloader_start_prepare(void);


/**@brief Function for finalizing entering the bootloader.
 *
 * @warning This function is not to be called. (It is called internally).
 *
 * @retval NRF_SUCCESS Finalize was started correctly.
 */
uint32_t ble_dfu_buttonless_bootloader_start_finalize(void);

#ifdef __cplusplus
}
#endif

#endif // BLE_DIS_H__

/** @} */
