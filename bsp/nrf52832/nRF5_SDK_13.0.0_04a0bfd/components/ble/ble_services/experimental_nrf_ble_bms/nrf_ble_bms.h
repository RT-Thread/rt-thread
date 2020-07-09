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
/** @file
 *
 * @defgroup ble_bms Bond Management Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Bond Management Service (BMS) module.
 *
 * @details This module implements the Bond Management Service (BMS).
 *          By writing to the Bond Management Control Point, the connected peer can request the deletion of
 *          bond information from the device.
 *          If authorization is configured, the application must supply an event handler for receiving Bond
 *          Management Service events. Using this handler, the service requests authorization when
 *          a procedure is requested by writing to the Bond Management Control Point.
 *
 * @msc
 * hscale = "1.3";
 * APP,BMS,PEER;
 * |||;
 * APP rbox PEER [label="Connection established"];
 * |||;
 * BMS<=PEER     [label="BMCP write request {procedure}"];
 * APP<-BMS      [label="NRF_BLE_BMS_EVT_AUTH {auth_code}"];
 * ---           [label="Variant #1: app grants authorization"];
 * APP->BMS      [label="nrf_ble_bms_auth_reponse (true)"];
 * BMS>>APP      [label="NRF_SUCCESS"];
 * BMS=>PEER     [label="BMCP write response"];
 * BMS rbox BMS  [label="Procedure initiated"];
 * ---           [label="Variant #2: app denies authorization"];
 * APP->BMS      [label="nrf_ble_bms_auth_reponse (false)"];
 * BMS>>APP      [label="NRF_SUCCESS"];
 * BMS=>PEER     [label="BMCP error response"];
 * @endmsc
 *
 * @note The application must propagate BLE stack events to the Bond Management Service module by calling
 *       @ref nrf_ble_bms_on_ble_evt() from the @ref softdevice_handler callback.
 *       If the application uses the Queued Writes module, the application must propagate Queued Write events
 *       to the Bond Management Service module by calling @ref nrf_ble_bms_on_qwr_evt() from the
 *       @ref nrf_ble_qwr callback.
 */

#ifndef NRF_BLE_BMS_H__
#define NRF_BLE_BMS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_ble_qwr.h"

#ifdef __cplusplus
extern "C" {
#endif


#define NRF_BLE_BMS_FEATURE_LEN    3                                 //!< Length of the Feature Characteristic (in bytes).
#define NRF_BLE_BMS_CTRLPT_MAX_LEN 128                               //!< Maximum length of the Bond Management Control Point Characteristic (in bytes).
#define NRF_BLE_BMS_CTRLPT_MIN_LEN 1                                 //!< Minimum length of the Bond Management Control Point Characteristic (in bytes).
#define NRF_BLE_BMS_AUTH_CODE_MAX_LEN NRF_BLE_BMS_CTRLPT_MAX_LEN - 1 //!< Maximum length of the Bond Management Control Point Authorization Code (in bytes).


/** @defgroup NRF_BLE_BMS_FEATURES BMS feature bits
 * @{ */
#define NRF_BLE_BMS_REQUESTING_DEVICE_BR_LE                      (0x01 << 0)  //!< Delete bond of the requesting device (BR/EDR and LE).
#define NRF_BLE_BMS_REQUESTING_DEVICE_BR_LE_AUTH_CODE            (0x01 << 1)  //!< Delete bond of the requesting device (BR/EDR and LE) with an authorization code.
#define NRF_BLE_BMS_REQUESTING_DEVICE_BR                         (0x01 << 2)  //!< Delete bond of the requesting device (BR/EDR transport only).
#define NRF_BLE_BMS_REQUESTING_DEVICE_BR_AUTH_CODE               (0x01 << 3)  //!< Delete bond of the requesting device (BR/EDR transport only) with an authorization code.
#define NRF_BLE_BMS_REQUESTING_DEVICE_LE                         (0x01 << 4)  //!< Delete bond of the requesting device (LE transport only).
#define NRF_BLE_BMS_REQUESTING_DEVICE_LE_AUTH_CODE               (0x01 << 5)  //!< Delete bond of the requesting device (LE transport only) with an authorization code.
#define NRF_BLE_BMS_ALL_BONDS_BR_LE                              (0x01 << 6)  //!< Delete all bonds on the device (BR/EDR and LE).
#define NRF_BLE_BMS_ALL_BONDS_BR_LE_AUTH_CODE                    (0x01 << 7)  //!< Delete all bonds on the device (BR/EDR and LE) with an authorization code.
#define NRF_BLE_BMS_ALL_BONDS_BR                                 (0x01 << 8)  //!< Delete all bonds on the device (BR/EDR transport only).
#define NRF_BLE_BMS_ALL_BONDS_BR_AUTH_CODE                       (0x01 << 9)  //!< Delete all bonds on the device (BR/EDR transport only) with an authorization code.
#define NRF_BLE_BMS_ALL_BONDS_LE                                 (0x01 << 10) //!< Delete all bonds on the device (LE transport only).
#define NRF_BLE_BMS_ALL_BONDS_LE_AUTH_CODE                       (0x01 << 11) //!< Delete all bonds on the device (LE transport only) with an authorization code.
#define NRF_BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_BR_LE           (0x01 << 12) //!< Delete all bonds on the device except for the bond of the requesting device (BR/EDR and LE).
#define NRF_BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_BR_LE_AUTH_CODE (0x01 << 13) //!< Delete all bonds on the device except for the bond of the requesting device (BR/EDR and LE) with an authorization code.
#define NRF_BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_BR              (0x01 << 14) //!< Delete all bonds on the device except for the bond of the requesting device (BR/EDR transport only).
#define NRF_BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_BR_AUTH_CODE    (0x01 << 15) //!< Delete all bonds on the device except for the bond of the requesting device (BR/EDR transport only) with an authorization code.
#define NRF_BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_LE              (0x01 << 16) //!< Delete all bonds on the device except for the bond of the requesting device (LE transport only).
#define NRF_BLE_BMS_ALL_EXCEPT_REQUESTING_DEVICE_LE_AUTH_CODE    (0x01 << 17) //!< Delete all bonds on the device except for the bond of the requesting device (LE transport only) with an authorization code.
/** @} */


#define NRF_BLE_BMS_OPCODE_NOT_SUPPORTED (BLE_GATT_STATUS_ATTERR_APP_BEGIN + 0) //!< Error sent back when receiving a control point write with an unsupported opcode.
#define NRF_BLE_BMS_OPERATION_FAILED     (BLE_GATT_STATUS_ATTERR_APP_BEGIN + 1) //!< Error sent back when a control point operation fails.


/**@brief Supported features. */
typedef struct
{
    bool delete_all                     : 1; //!< Indicates whether the application wants to support the operation to delete all bonds.
    bool delete_all_auth                : 1; //!< Indicates whether the application wants to support the operation to delete all bonds with authorization code.
    bool delete_requesting              : 1; //!< Indicates whether the application wants to support the operation to delete the bonds of the requesting device.
    bool delete_requesting_auth         : 1; //!< Indicates whether the application wants to support the operation to delete the bonds of the requesting device with authorization code.
    bool delete_all_but_requesting      : 1; //!< Indicates whether the application wants to support the operation to delete all bonds except for the bond of the requesting device.
    bool delete_all_but_requesting_auth : 1; //!< Indicates whether the application wants to support the operation to delete all bonds except for the bond of the requesting device with authorization code.
} nrf_ble_bms_features_t;


/**@brief BMS Control Point opcodes. */
typedef enum
{
    NRF_BLE_BMS_OP_DEL_BOND_REQ_DEVICE_BR_LE       = 0x01, //!< Initiates the procedure to delete the bond of the requesting device on BR/EDR and LE transports.
    NRF_BLE_BMS_OP_DEL_BOND_REQ_DEVICE_BR_ONLY     = 0x02, //!< Initiates the procedure to delete the bond of the requesting device on BR/EDR transport.
    NRF_BLE_BMS_OP_DEL_BOND_REQ_DEVICE_LE_ONLY     = 0x03, //!< Initiates the procedure to delete the bond of the requesting device on LE transport.
    NRF_BLE_BMS_OP_DEL_ALL_BONDS_ON_SERVER_BR_LE   = 0x04, //!< Initiates the procedure to delete all bonds on the device on BR/EDR and LE transports.
    NRF_BLE_BMS_OP_DEL_ALL_BONDS_ON_SERVER_BR_ONLY = 0x05, //!< Initiates the procedure to delete all bonds on the device on BR/EDR transport.
    NRF_BLE_BMS_OP_DEL_ALL_BONDS_ON_SERVER_LE_ONLY = 0x06, //!< Initiates the procedure to delete all bonds on the device on LE transport.
    NRF_BLE_BMS_OP_DEL_ALL_BUT_ACTIVE_BOND_BR_LE   = 0x07, //!< Initiates the procedure to delete all bonds except for the one of the requesting device on BR/EDR and LE transports.
    NRF_BLE_BMS_OP_DEL_ALL_BUT_ACTIVE_BOND_BR_ONLY = 0x08, //!< Initiates the procedure to delete all bonds except for the one of the requesting device on BR/EDR transport.
    NRF_BLE_BMS_OP_DEL_ALL_BUT_ACTIVE_BOND_LE_ONLY = 0x09, //!< Initiates the procedure to delete all bonds except for the one of the requesting device on LE transport.
    NRF_BLE_BMS_OP_NONE                            = 0xFF  //!< Indicates an invalid opcode or no pending opcode.
} nrf_ble_bms_op_t;


/**@brief Authorization status values. */
typedef enum
{
    NRF_BLE_BMS_AUTH_STATUS_ALLOWED, //!< Authorization is granted.
    NRF_BLE_BMS_AUTH_STATUS_DENIED,  //!< Authorization is denied.
    NRF_BLE_BMS_AUTH_STATUS_PENDING  //!< Authorization is pending.
} nrf_ble_bms_auth_status_t;


/**@brief Received authorization codes. */
typedef struct
{
    uint8_t  code[NRF_BLE_BMS_AUTH_CODE_MAX_LEN]; //!< Authorization code.
    uint16_t len;                                 //!< Length of the authorization code.
} nrf_ble_bms_auth_code_t;


/**@brief BMS event types. */
typedef enum
{
    NRF_BLE_BMS_EVT_AUTH, //!< Event that indicates that the application shall verify the supplied authentication code.
} nrf_ble_bms_evt_type_t;


/**@brief BMS events. */
typedef struct
{
    nrf_ble_bms_evt_type_t  evt_type;  //!< Type of event.
    nrf_ble_bms_auth_code_t auth_code; //!< Received authorization code.
} nrf_ble_bms_evt_t;

/**@brief BMS control points. */
typedef struct
{
    nrf_ble_bms_op_t        op_code;     //!< Control Point Op Code.
    nrf_ble_bms_auth_code_t auth_code;   //!< Control Point Authorization Code.
} nrf_ble_bms_ctrlpt_t;


// Forward declaration of the nrf_ble_bms_t type.
typedef struct nrf_ble_bms_s nrf_ble_bms_t;


/**@brief BMS event handler type. */
typedef void (* nrf_ble_bms_bond_handler_t) (nrf_ble_bms_t const * p_bms);


/**@brief BMS bond management callbacks. */
typedef struct
{
    nrf_ble_bms_bond_handler_t delete_requesting;            //!< Function to be called to delete the bonding information of the requesting device.
    nrf_ble_bms_bond_handler_t delete_all;                   //!< Function to be called to delete the bonding information of all bonded devices.
    nrf_ble_bms_bond_handler_t delete_all_except_requesting; //!< Function to be called to delete the bonding information of all bonded devices except for the requesting device.
} nrf_ble_bms_bond_cbs_t;


/**@brief BMS event handler type. The event handler returns a @ref BLE_GATT_STATUS_CODES "BLE GATT status code". */
typedef void (* ble_bms_evt_handler_t) (nrf_ble_bms_t * p_bms, nrf_ble_bms_evt_t * p_evt);


/**@brief BMS initialization structure that contains all information
 *        needed to initialize the service. */
typedef struct
{
    ble_bms_evt_handler_t   evt_handler;         //!< Event handler to be called for handling events in the Bond Management Service.
    ble_srv_error_handler_t error_handler;       //!< Function to be called if an error occurs.
    nrf_ble_bms_features_t  feature;             //!< Initial value for features of the service.
    security_req_t          bms_feature_sec_req; //!< Initial security level for the Feature characteristic.
    security_req_t          bms_ctrlpt_sec_req;  //!< Initial security level for the Control Point characteristic.
    nrf_ble_qwr_t         * p_qwr;               //!< Pointer to the initialized Queued Write context.
    nrf_ble_bms_bond_cbs_t  bond_callbacks;      //!< Callback functions for deleting bonds.
} nrf_ble_bms_init_t;


/**@brief Status information for the service. */
struct nrf_ble_bms_s
{
    uint16_t                  service_handle;  //!< Handle of the Bond Management Service (as provided by the BLE stack).
    uint16_t                  conn_handle;     //!< Handle of the current connection (as provided by the BLE stack). @ref BLE_CONN_HANDLE_INVALID if not in a connection.
    ble_bms_evt_handler_t     evt_handler;     //!< Event handler to be called for handling events in the Bond Management Service.
    ble_srv_error_handler_t   error_handler;   //!< Function to be called if an error occurs.
    nrf_ble_bms_features_t    feature;         //!< Value for features of the service (see @ref NRF_BLE_BMS_FEATURES).
    ble_gatts_char_handles_t  feature_handles; //!< Handles related to the Bond Management Feature characteristic.
    ble_gatts_char_handles_t  ctrlpt_handles;  //!< Handles related to the Bond Management Control Point characteristic.
    nrf_ble_bms_bond_cbs_t    bond_callbacks;  //!< Callback functions for deleting bonds.
    nrf_ble_bms_auth_status_t auth_status;     //!< Authorization status.
};


/**@brief Function for responding to an authorization request.
 *
 * @details This function should be called when receiving the @ref NRF_BLE_BMS_EVT_AUTH event to
 *          respond to the service with an authorization result.
 *
 * @param[in]   p_bms       BMS structure.
 * @param[in]   authorize   Authorization response. True if the authorization is considered successful.
 *
 * @retval  NRF_ERROR_NULL          If @p p_bms was NULL.
 * @retval  NRF_ERROR_INVALID_STATE If no authorization request was pending.
 * @retval  NRF_SUCCESS             If the response was received successfully.
 */
ret_code_t nrf_ble_bms_auth_response(nrf_ble_bms_t * p_bms, bool authorize);


/**@brief Function for initializing the Bond Management Service.
 *
 * @param[out]  p_bms       BMS structure.
 * @param[in]   p_bms_init  Information needed to initialize the service.
 *
 * @retval NRF_ERROR_NULL   If @p p_bms or @p p_bms_init was NULL.
 * @retval NRF_SUCCESS      If the service was initialized successfully.
 *                          Otherwise, an error code is returned.
 */
ret_code_t nrf_ble_bms_init(nrf_ble_bms_t * p_bms, nrf_ble_bms_init_t * p_bms_init);


/**@brief Function for assigning handles to the Bond Management Service instance.
 *
 * @details Call this function when a link with a peer has been established to
 *          associate the link to this instance of the module.
 *
 * @param[in]   p_bms       Pointer to the BMS structure instance to associate.
 * @param[in]   conn_handle Connection handle to be associated with the given BMS instance.
 *
 * @retval  NRF_ERROR_NULL  If @p p_bms was NULL.
 * @retval  NRF_SUCCESS     If the operation was successful.
 */
ret_code_t nrf_ble_bms_set_conn_handle(nrf_ble_bms_t * p_bms, uint16_t conn_handle);


/**@brief Function for handling Bond Management BLE stack events.
 *
 * @details This function handles all events from the BLE stack that are of interest to the Bond Management Service.
 *
 * @param[in]   p_bms      BMS structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void nrf_ble_bms_on_ble_evt(nrf_ble_bms_t * p_bms, ble_evt_t * p_ble_evt);


/**@brief Function for handling events from the @ref nrf_ble_qwr.
 *
 * @param[in]   p_bms   BMS structure.
 * @param[in]   p_qwr   Queued Write structure.
 * @param[in]   p_evt   Event received from the Queued Writes module.
 *
 * @retval BLE_GATT_STATUS_SUCCESS                    If the received event is accepted.
 * @retval NRF_BLE_QWR_REJ_REQUEST_ERR_CODE           If the received event is not relevant for any of this module's attributes.
 * @retval BLE_BMS_OPCODE_NOT_SUPPORTED               If the received opcode is not supported.
 * @retval BLE_GATT_STATUS_ATTERR_INSUF_AUTHORIZATION If the application handler returns that the authorization code is not valid.
 */
uint16_t nrf_ble_bms_on_qwr_evt(nrf_ble_bms_t     * p_bms,
                                nrf_ble_qwr_t     * p_qwr,
                                nrf_ble_qwr_evt_t * p_evt);


#ifdef __cplusplus
}
#endif

#endif // NRF_BLE_BMS_H__

/** @} */
