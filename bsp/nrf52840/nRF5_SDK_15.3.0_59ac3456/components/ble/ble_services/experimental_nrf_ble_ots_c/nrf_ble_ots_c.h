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
 * @defgroup nrf_ble_ots_c Object Transfer Service Client
 * @{
 * @ingroup  ble_sdk_srv
 * @brief    Object Transfer Service client module
 *
 * @details  This is the main module of the Object Transfer Service (OTS) client.
 */

#ifndef NRF_BLE_OTS_C_H__
#define NRF_BLE_OTS_C_H__

#include <stdint.h>
#include "ble_gattc.h"
#include "ble.h"
#include "nrf_error.h"
#include "ble_srv_common.h"
#include "ble_db_discovery.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_ots instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define NRF_BLE_OTS_C_DEF(_name)                                                                    \
static nrf_ble_ots_c_t _name;                                                                       \
NRF_SDH_BLE_OBSERVER(_name ## _ble_obs,                                                             \
                     BLE_OTS_C_BLE_OBSERVER_PRIO,                                                   \
                     nrf_ble_ots_c_on_ble_evt, &_name)                                              \

/** @brief Macro for defining multiple ble_ots instances.
 *
 * @param   _name   Name of the array of instances.
 * @param   _cnt    Number of instances to define.
 * @hideinitializer
 */
#define NRF_BLE_OTS_C_ARRAY_DEF(_name, _cnt)                 \
static nrf_ble_ots_c_t _name[_cnt];                          \
NRF_SDH_BLE_OBSERVERS(_name ## _ble_obs,                     \
                      BLE_OTS_C_BLE_OBSERVER_PRIO,           \
                      nrf_ble_ots_c_on_ble_evt, &_name, _cnt)


/** @brief Types of Object Action Control Point Procedures. */
typedef enum
{
    NRF_BLE_OTS_C_OACP_PROC_CREATE        = 0x01, //!< Create object.
    NRF_BLE_OTS_C_OACP_PROC_DELETE        = 0x02, //!< Delete object.
    NRF_BLE_OTS_C_OACP_PROC_CALC_CHKSUM   = 0x03, //!< Calculate Checksum.
    NRF_BLE_OTS_C_OACP_PROC_EXECUTE       = 0x04, //!< Execute Object.
    NRF_BLE_OTS_C_OACP_PROC_READ          = 0x05, //!< Read object.
    NRF_BLE_OTS_C_OACP_PROC_WRITE         = 0x06, //!< Write object.
    NRF_BLE_OTS_C_OACP_PROC_ABORT         = 0x07, //!< Abort object.
    NRF_BLE_OTS_C_OACP_PROC_RESP          = 0x60  //!< Procedure response.
} ble_ots_c_oacp_proc_type_t;

/** @brief Object Action Control Point return codes. */
typedef enum
{
    NRF_BLE_OTS_C_OACP_RES_SUCCESS        = 0x01, //!< Success.
    NRF_BLE_OTS_C_OACP_RES_OPCODE_NOT_SUP = 0x02, //!< Not supported
    NRF_BLE_OTS_C_OACP_RES_INV_PARAM      = 0x03, //!< Invalid parameter
    NRF_BLE_OTS_C_OACP_RES_INSUFF_RES     = 0x04, //!< Insufficient resources.
    NRF_BLE_OTS_C_OACP_RES_INV_OBJ        = 0x05, //!< Invalid object.
    NRF_BLE_OTS_C_OACP_RES_CHAN_UNAVAIL   = 0x06, //!< Channel unavailable.
    NRF_BLE_OTS_C_OACP_RES_UNSUP_TYPE     = 0x07, //!< Unsupported procedure.
    NRF_BLE_OTS_C_OACP_RES_NOT_PERMITTED  = 0x08, //!< Procedure not permitted.
    NRF_BLE_OTS_C_OACP_RES_OBJ_LOCKED     = 0x09, //!< Object locked.
    NRF_BLE_OTS_C_OACP_RES_OPER_FAILED    = 0x0A  //!< Operation Failed.
} ble_ots_c_oacp_res_code_t;

/**@brief Type of the Object Transfer Service client event. */
typedef enum
{
    NRF_BLE_OTS_C_EVT_DISCOVERY_FAILED,   //!< Event indicating that the Object Transfer Service has not been found on the peer.
    NRF_BLE_OTS_C_EVT_DISCOVERY_COMPLETE, //!< Event indicating that the Object Transfer Service is present on the peer device.
    NRF_BLE_OTS_C_EVT_DISCONN_COMPLETE,   //!< Event indicating that the Object Transfer Service client module has finished processing the BLE_GAP_EVT_DISCONNECTED event. The event can be used by the application to do clean up related to the Object Transfer Service client.
    NRF_BLE_OTS_C_EVT_FEATURE_READ_RESP,  //!< Event indicating that the feature characteristic was read, The available features of the peer will be provided in the event.
    NRF_BLE_OTS_C_EVT_OACP_RESP,          //!< Event indicating that a response was received (result of a write to the OACP).
    NRF_BLE_OTS_C_EVT_OBJ_READ,           //!< Event indicating that the Object Transfer Service client finished reading object from the peer.
    NRF_BLE_OTS_C_EVT_OBJ_WRITE,          //!< Event indicating that the Object Transfer Service client finished writing an object to the peer.
    NRF_BLE_OTS_C_EVT_CHANNEL_RELEASED,   //!< Event indicating that the L2CAP Connection Oriented Channel has been disconnected
    NRF_BLE_OTS_C_EVT_SIZE_READ_RESP,     //!< Event indicating that the object size characteristic was read.
    NRF_BLE_OTS_C_EVT_PROP_READ_RESP      //!< Event indicating that the object properties characteristic was read.
} nrf_ble_ots_c_evt_type_t;

/** @brief Structure to hold the features of a server. */
typedef struct
{
    uint8_t oacp_create   : 1;
    uint8_t oacp_delete   : 1;
    uint8_t oacp_crc      : 1;
    uint8_t oacp_execute  : 1;
    uint8_t oacp_read     : 1;
    uint8_t oacp_write    : 1;
    uint8_t oacp_append   : 1;
    uint8_t oacp_truncate : 1;
    uint8_t oacp_patch    : 1;
    uint8_t oacp_abort    : 1;
    uint8_t olcp_goto     : 1;
    uint8_t olcp_order    : 1;
    uint8_t olcp_req_num  : 1;
    uint8_t olcp_clear    : 1;
} nrf_ble_ots_c_feature_t;


/**@brief Properties of an Object Transfer Service object. */
typedef union
{
    struct
    {
        bool is_delete_permitted   :1; /**< Object can be deleted. */
        bool is_execute_permitted  :1; /**< Object can be executed. */
        bool is_read_permitted     :1; /**< Object can be read. */
        bool is_write_permitted    :1; /**< Object can be written. */
        bool is_append_permitted   :1; /**< Object can be appended. */
        bool is_truncate_permitted :1; /**< When writing using truncate mode, and the written length is shorter than the object, the object size is decreased. */
        bool is_patch_permitted    :1; /**< When patching, a part of the object is replaced. */
        bool is_marked             :1; /**< Boolean to keep track of if the object is marked or not. */
    } decoded;
    uint32_t raw;
} nrf_ble_ots_c_obj_properties_t;


/**@brief Structure used for holding the Object Transfer Service found during the
          discovery process.
 */
typedef struct
{
    ble_gattc_service_t service;               //!< The Object Transfer Service holding the discovered Object Transfer Service. (0x1825).
    ble_gattc_char_t    ots_feature_char;      //!< OTS Feature (0x2ABD)
    ble_gattc_char_t    object_name_char;      //!< Object Name (0x2ABE)
    ble_gattc_char_t    object_type_char;      //!< Object Type (0x2ABF)
    ble_gattc_char_t    object_size_char;      //!< Object Size (0x2AC0)
    ble_gattc_char_t    object_prop_char;      //!< Object Properties (0x2AC4)
    ble_gattc_char_t    object_action_cp_char; //!< Object Action Control Point (0x2AC5)
    ble_gattc_desc_t    object_action_cp_cccd; //!< Object Action Control Point Descriptor. Enables or disables Object Transfer notifications.
} nrf_ble_ots_c_service_t;

/** @brief Structure to hold responses received when writing to the Object Action Control Point on the server. */
typedef struct
{  
    ble_ots_c_oacp_proc_type_t request_op_code;
    ble_ots_c_oacp_res_code_t  result_code;
} nrf_ble_ots_c_oacp_response_t;

/** @brief Structure to hold the size of the object on the server when read from the Object Size characteristic on the server. */
typedef struct
{
    uint32_t current_size;
    uint32_t allocated_size;
} nrf_ble_ots_c_obj_size;

/**@brief Structure containing the event from the Object Transfer client module to the application.
 */
typedef struct
{
    nrf_ble_ots_c_evt_type_t evt_type;    /**< Type of event. See @ref nrf_ble_ots_c_evt_type_t. */
    uint16_t                 conn_handle; /**< Handle of the connection for which this event has occurred. */
    union
    {
        nrf_ble_ots_c_feature_t        feature;  /**< Will be provided if the event type is @ref NRF_BLE_OTS_C_EVT_FEATURE_READ_RESP.*/
        nrf_ble_ots_c_service_t        handles;  /**< Handles that the Object Transfer service occupies in the peer device. Will be filled if the event type is @ref NRF_BLE_OTS_C_EVT_DISCOVERY_COMPLETE.*/
        nrf_ble_ots_c_oacp_response_t  response; /**< Will be provided if the event type is @ref NRF_BLE_OTS_C_EVT_OACP_RESP. */
        ble_data_t                     object;   /**< Will be provided if the event type is @ref NRF_BLE_OTS_C_EVT_OBJ_READ. */
        nrf_ble_ots_c_obj_size         size;     /**< Will be provided if the event type is @ref NRF_BLE_OTS_C_EVT_SIZE_READ_RESP. */
        nrf_ble_ots_c_obj_properties_t prop;     /**< Will be provided if the eevnt type is @ref NRF_BLE_OTS_C_EVT_PROP_READ_RESP. */
    } params;
} nrf_ble_ots_c_evt_t;


/**@brief Object Transfer handler type. */
typedef void (* nrf_ble_ots_c_evt_handler_t)(nrf_ble_ots_c_evt_t * p_evt);


/**@brief Structure for holding the information related to the Object Transfer Service.

   @warning This structure must be zero-initialized.
*/
typedef struct
{
    bool                        initialized;       /**< Boolean telling whether the context has been initialized or not. */
    uint16_t                    conn_handle;       /**< Active connection handle */
    nrf_ble_ots_c_service_t     service;           /**< Structure to store the different handles and UUIDs related to the service. */
    nrf_ble_ots_c_evt_handler_t evt_handler;       /**< Pointer to event handler function. */
    ble_srv_error_handler_t     err_handler;       /**< Pointer to error handler function. */
    uint16_t                    local_cid;         /**< Connection ID of the current connection. */
    ble_l2cap_evt_ch_setup_t    ch_setup;          /**< L2CAP Channel Setup Completed Event Parameters. */
    uint32_t                    transmitted_bytes; /**< Variable used when transferring an object to the peer. */
    uint32_t                    received_bytes;    /**< Variable used when transferring an object from the peer. */
    ble_data_t                * current_obj;       /**< Pointer to the current object to be transferred. */
} nrf_ble_ots_c_t;


/**@brief Initialization parameters, these must be supplied when calling @ref nrf_ble_ots_c_init. */
typedef struct
{
    nrf_ble_ots_c_evt_handler_t evt_handler; /**< The event handler that is called by the Object Transfer client module when any related event occurs. */
    ble_srv_error_handler_t     err_handler; /**< the error handler that is called by the Object Transfer client module if any error occurs. */
} nrf_ble_ots_c_init_t;

/**@brief Function for initializing the Object Transfer client module.

   @param[in,out] p_ots_c      Pointer to the Object Transfer Service client structure instance.
   @param[in]     p_ots_c_init Init parameters contraining the event handler that is called by
                                 the Object Transfer client module when any related event occurs.

   @retval NRF_SUCCESS    If the service was initialized successfully.
   @retval NRF_ERROR_NULL If any of the input parameters are NULL.
   @return                If functions from other modules return errors to this function,
                          the @ref nrf_error are propagated.
*/
ret_code_t nrf_ble_ots_c_init(nrf_ble_ots_c_t      * p_ots_c,
                                nrf_ble_ots_c_init_t * p_ots_c_init);


/**@brief Function for handling events from the database discovery module.

   @details This function will handle an event from the database discovery module, and determine
            if it relates to the discovery of Object Transfer Service at the peer. If so,
            it will call the application's event handler indicating that Object Transfer Service
            has been discovered at the peer.

   @param[in,out] p_ots_c Pointer to the Object Transfer Service client structure instance.
   @param[in]     p_evt   Pointer to the event received from the database discovery module.
*/
void nrf_ble_ots_c_on_db_disc_evt(nrf_ble_ots_c_t const * const p_ots_c,
                                  ble_db_discovery_evt_t  * const p_evt);


/**@brief Function for reading the features characteristic (@ref BLE_UUID_OTS_FEATURES) on the server.

   @param[in,out] p_ots_c Pointer to Object Transfer client structure.

   @retval NRF_SUCCESS Operation success.
   @return             If functions from other modules return errors to this function,
                       the @ref nrf_error are propagated.
*/
ret_code_t nrf_ble_ots_c_feature_read(nrf_ble_ots_c_t * const p_ots_c);


/**@brief Function for reading the Object Size characteristic (@ref BLE_UUID_OTS_FEATURES) on the server.

   @param[in,out] p_ots_c Pointer to Object Transfer client structure.

   @retval NRF_SUCCESS Operation success.
   @return             NRF_ERROR_INVALID_STATE if the Object Size characteristic has not been discovered. 
   @return             If functions from other modules return errors to this function,
                       the @ref nrf_error are propagated.
*/
ret_code_t nrf_ble_ots_c_obj_size_read(nrf_ble_ots_c_t * const p_ots_c);


/**@brief Function for reading the Object properties (@ref BLE_UUID_OTS_OBJECT_PROPERTIES) on the server.

   @param[in,out] p_ots_c Pointer to Object Transfer client structure.

   @retval NRF_SUCCESS             Operation success.
   @retval NRF_ERROR_INVALID_STATE If the Object Properties characteristic has not been discovered.
   @return                         If functions from other modules return errors to this function,
                                   the @ref nrf_error are propagated.
*/
ret_code_t nrf_ble_ots_c_obj_properties_read(nrf_ble_ots_c_t * const p_ots_c);


/**@brief Function for handling the Application's BLE Stack events.

   @param[in]     p_ble_evt   Pointer to the BLE event received.
   @param[in,out] p_context   Pointer to the Object Transfer Service client structure instance.
*/
void nrf_ble_ots_c_on_ble_evt(const ble_evt_t   * const p_ble_evt, void * p_context);


ret_code_t nrf_ble_ots_c_obj_name_read(nrf_ble_ots_c_t * const p_ots_c, ble_data_t  * p_obj);
ret_code_t nrf_ble_ots_c_obj_name_write(nrf_ble_ots_c_t * const p_ots_c, ble_data_t  * p_obj);
ret_code_t nrf_ble_ots_c_obj_type_read(nrf_ble_ots_c_t * const p_ots_c);


/**@brief   Function for assigning handles to a Object Transfer Service client instance.

   @details Call this function when a link has been established with a peer to
            associate this link to an instance of the module. This makes it
            possible to handle several link and associate each link to a particular
            instance of the Object Transfer Service client module. The connection handle and
            attribute handles will be provided from the discovery event
            @ref NRF_BLE_OTS_C_EVT_DISCOVERY_COMPLETE.

   @param[in,out] p_ots_c    Pointer to the Object Transfer Service client structure instance to associate
                             with the handles.
   @param[in] conn_handle    Connection handle to be associated with the given Object Transfer Service client
                             Instance.
   @param[in] p_peer_handles Attribute handles on the Object Transfer Service server that you want this
                             Object Transfer Service client to interact with.

   @retval NRF_SUCCESS    If the connection handle was successfully stored in the Object Transfer Service instance.
   @retval NRF_ERROR_NULL If any of the input parameters are NULL.
*/
ret_code_t nrf_ble_ots_c_handles_assign(nrf_ble_ots_c_t       * const p_ots_c,
                                        uint16_t                const conn_handle,
                                        nrf_ble_ots_c_service_t const * const p_peer_handles);

#endif // NRF_BLE_OTS_C_H__

/** @} */
