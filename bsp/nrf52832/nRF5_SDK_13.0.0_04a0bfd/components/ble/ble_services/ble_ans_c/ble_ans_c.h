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
 * @defgroup ble_ans_c Alert Notification Service Client
 * @{
 * @ingroup ble_sdk_srv
 * @brief Alert Notification module.
 *
 * @details This module implements the Alert Notification Client according to the
 *          Alert Notification Profile.
 *
 * @note The application must propagate BLE stack events to the Alert Notification Client module
 *       by calling ble_ans_c_on_ble_evt() from the @ref softdevice_handler callback.
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */
#ifndef BLE_ANS_C_H__
#define BLE_ANS_C_H__

#include "ble.h"
#include "ble_gatts.h"
#include "ble_types.h"
#include "sdk_common.h"
#include "ble_srv_common.h"
#include "ble_db_discovery.h"

#ifdef __cplusplus
extern "C" {
#endif


// Forward declaration of the ble_ans_c_t type.
typedef struct ble_ans_c_s ble_ans_c_t;

/** Alerts types as defined in the alert category id; UUID: 0x2A43. */
typedef enum
{
    ANS_TYPE_SIMPLE_ALERT           = 0,                   /**< General text alert or non-text alert.*/
    ANS_TYPE_EMAIL                  = 1,                   /**< Alert when email messages arrives.*/
    ANS_TYPE_NEWS                   = 2,                   /**< News feeds such as RSS, Atom.*/
    ANS_TYPE_NOTIFICATION_CALL      = 3,                   /**< Incoming call.*/
    ANS_TYPE_MISSED_CALL            = 4,                   /**< Missed call.*/
    ANS_TYPE_SMS_MMS                = 5,                   /**< SMS/MMS message arrives.*/
    ANS_TYPE_VOICE_MAIL             = 6,                   /**< Voice mail.*/
    ANS_TYPE_SCHEDULE               = 7,                   /**< Alert occurred on calendar, planner.*/
    ANS_TYPE_HIGH_PRIORITIZED_ALERT = 8,                   /**< Alert that should be handled as high priority.*/
    ANS_TYPE_INSTANT_MESSAGE        = 9,                   /**< Alert for incoming instant messages.*/
    ANS_TYPE_ALL_ALERTS             = 0xFF                 /**< Identifies All Alerts. */
} ble_ans_category_id_t;

/** Alerts notification control point commands as defined in the Alert Notification Specification;
 * UUID: 0x2A44.
 */
typedef enum
{
    ANS_ENABLE_NEW_INCOMING_ALERT_NOTIFICATION      = 0,      /**< Enable New Incoming Alert Notification.*/
    ANS_ENABLE_UNREAD_CATEGORY_STATUS_NOTIFICATION  = 1,      /**< Enable Unread Category Status Notification.*/
    ANS_DISABLE_NEW_INCOMING_ALERT_NOTIFICATION     = 2,      /**< Disable New Incoming Alert Notification.*/
    ANS_DISABLE_UNREAD_CATEGORY_STATUS_NOTIFICATION = 3,      /**< Disable Unread Category Status Notification.*/
    ANS_NOTIFY_NEW_INCOMING_ALERT_IMMEDIATELY       = 4,      /**< Notify New Incoming Alert immediately.*/
    ANS_NOTIFY_UNREAD_CATEGORY_STATUS_IMMEDIATELY   = 5,      /**< Notify Unread Category Status immediately.*/
} ble_ans_command_id_t;

/**@brief Alert Notification Event types that are passed from client to application on an event. */
typedef enum
{
    BLE_ANS_C_EVT_DISCOVERY_COMPLETE,                         /**< A successful connection has been established and the characteristics of the server has been fetched. */
    BLE_ANS_C_EVT_DISCOVERY_FAILED,                           /**< It was not possible to discover service or characteristics of the connected peer. */
    BLE_ANS_C_EVT_DISCONN_COMPLETE,                           /**< The connection has been taken down. */
    BLE_ANS_C_EVT_NOTIFICATION,                               /**< A valid Alert Notification has been received from the server.*/
    BLE_ANS_C_EVT_READ_RESP,                                  /**< A read response has been received from the server.*/
    BLE_ANS_C_EVT_WRITE_RESP                                  /**< A write response has been received from the server.*/
} ble_ans_c_evt_type_t;

/**@brief Alert Notification Control Point structure. */
typedef struct
{
    ble_ans_command_id_t  command;                            /**< The command to be written to the control point, see @ref ble_ans_command_id_t. */
    ble_ans_category_id_t category;                           /**< The category for the control point for which the command applies, see @ref ble_ans_category_id_t. */
} ble_ans_control_point_t;

/**@brief Alert Notification Setting structure containing the supported alerts in the service.
  *
  *@details
  * The structure contains bit fields describing which alerts that are supported:
  * 0 = Unsupported
  * 1 = Supported
  */
typedef struct
{
    uint8_t ans_simple_alert_support           : 1;           /**< Support for General text alert or non-text alert.*/
    uint8_t ans_email_support                  : 1;           /**< Support for Alert when email messages arrives.*/
    uint8_t ans_news_support                   : 1;           /**< Support for News feeds such as RSS, Atom.*/
    uint8_t ans_notification_call_support      : 1;           /**< Support for Incoming call.*/
    uint8_t ans_missed_call_support            : 1;           /**< Support for Missed call.*/
    uint8_t ans_sms_mms_support                : 1;           /**< Support for SMS/MMS message arrives.*/
    uint8_t ans_voice_mail_support             : 1;           /**< Support for Voice mail.*/
    uint8_t ans_schedule_support               : 1;           /**< Support for Alert occurred on calendar, planner.*/
    uint8_t ans_high_prioritized_alert_support : 1;           /**< Support for Alert that should be handled as high priority.*/
    uint8_t ans_instant_message_support        : 1;           /**< Support for Alert for incoming instant messages.*/
    uint8_t reserved                           : 6;           /**< Reserved for future use. */
} ble_ans_alert_settings_t;

/**@brief Alert Notification structure
 */
typedef struct
{
    uint8_t   alert_category;                                 /**< Alert category to which this alert belongs.*/
    uint8_t   alert_category_count;                           /**< Number of alerts in the category. */
    uint32_t  alert_msg_length;                               /**< Length of optional text message send by the server. */
    uint8_t * p_alert_msg_buf;                                /**< Pointer to buffer containing the optional text message. */
} ble_ans_alert_notification_t;


/**@brief Struct to hold information on the Alert Notification Service if found on the server.
*/
typedef struct
{
    ble_gattc_service_t service;                              /**< The GATT service holding the discovered Alert Notification Service. */
    ble_gattc_char_t    alert_notif_ctrl_point;               /**< Characteristic for the Alert Notification Control Point. @ref BLE_UUID_ALERT_NOTIFICATION_CONTROL_POINT_CHAR */
    ble_gattc_char_t    suported_new_alert_cat;               /**< Characteristic for the Supported New Alert category. @ref BLE_UUID_SUPPORTED_NEW_ALERT_CATEGORY_CHAR */
    ble_gattc_char_t    suported_unread_alert_cat;            /**< Characteristic for the Unread Alert category. @ref BLE_UUID_SUPPORTED_UNREAD_ALERT_CATEGORY_CHAR */
    ble_gattc_char_t    new_alert;                            /**< Characteristic for the New Alert Notification.  @ref BLE_UUID_NEW_ALERT_CHAR */
    ble_gattc_desc_t    new_alert_cccd;                       /**< Characteristic Descriptor for New Alert Category. Enables or Disables GATT notifications */
    ble_gattc_char_t    unread_alert_status;                  /**< Characteristic for the Unread Alert Notification. @ref BLE_UUID_UNREAD_ALERT_CHAR */
    ble_gattc_desc_t    unread_alert_cccd;                    /**< Characteristic Descriptor for Unread Alert Category. Enables or Disables GATT notifications */
} ble_ans_c_service_t;


/**@brief Alert Notification Event structure
 *
 * @details The structure contains the event that should be handled, as well as
 *          additional information.
 */
typedef struct
{
    ble_ans_c_evt_type_t                evt_type;             /**< Type of event. */
    uint16_t                            conn_handle;          /**< Connection handle on which the ANS service was discovered on the peer device. This will be filled if the evt_type is @ref BLE_ANS_C_EVT_DISCOVERY_COMPLETE.*/
    ble_uuid_t                          uuid;                 /**< UUID of the event in case of an alert or notification. */
    union
    {
        ble_ans_alert_settings_t        settings;             /**< Setting returned from server on read request. */
        ble_ans_alert_notification_t    alert;                /**< Alert Notification data sent by the server. */
        uint32_t                        error_code;           /**< Additional status/error code if the event was caused by a stack error or gatt status, e.g. during service discovery. */
        ble_ans_c_service_t             service;              /**< Info on the discovered Alert Notification Service discovered. This will be filled if the evt_type is @ref BLE_ANS_C_EVT_DISCOVERY_COMPLETE.*/
    } data;
} ble_ans_c_evt_t;

/**@brief Alert Notification event handler type. */
typedef void (*ble_ans_c_evt_handler_t) (ble_ans_c_evt_t * p_evt);


/**@brief Alert Notification structure. This contains various status information for the client. */
struct ble_ans_c_s
{
    ble_ans_c_evt_handler_t             evt_handler;          /**< Event handler to be called for handling events in the Alert Notification Client Application. */
    ble_srv_error_handler_t             error_handler;        /**< Function to be called in case of an error. */
    uint16_t                            conn_handle;          /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint8_t                             central_handle;       /**< Handle for the currently connected central if peer is bonded. */
    uint8_t                             service_handle;       /**< Handle to the service in the database to use for this instance. */
    uint32_t                            message_buffer_size;  /**< Size of message buffer to hold the additional text messages received on notifications. */
    uint8_t *                           p_message_buffer;     /**< Pointer to the buffer to be used for additional text message handling. */
    ble_ans_c_service_t                 service;              /**< Struct to store the different handles and UUIDs related to the service. */
};

/**@brief Alert Notification init structure. This contains all options and data needed for
 *        initialization of the client.*/
typedef struct
{
    ble_ans_c_evt_handler_t             evt_handler;          /**< Event handler to be called for handling events in the Battery Service. */
    ble_srv_error_handler_t             error_handler;        /**< Function to be called in case of an error. */
    uint32_t                            message_buffer_size;  /**< Size of buffer to handle messages. */
    uint8_t *                           p_message_buffer;     /**< Pointer to buffer for passing messages. */
} ble_ans_c_init_t;


/**@brief     Function for handling events from the database discovery module.
 *
 * @details   Call this function when getting a callback event from the DB discovery modue.
 *            This function will handle an event from the database discovery module, and determine
 *            if it relates to the discovery of heart rate service at the peer. If so, it will
 *            call the application's event handler indicating that the heart rate service has been
 *            discovered at the peer. It also populates the event with the service related
 *            information before providing it to the application.
 *
 * @param[in] p_ans   Pointer to the Alert Notification client structure instance that will handle
 *                    the discovery.
 * @param[in] p_evt   Pointer to the event received from the database discovery module.
 */
void ble_ans_c_on_db_disc_evt(ble_ans_c_t * p_ans, const ble_db_discovery_evt_t * p_evt);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Alert Notification Client.
 *
 * @param[in]   p_ans      Alert Notification Client structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_ans_c_on_ble_evt(ble_ans_c_t * p_ans, const ble_evt_t * p_ble_evt);


/**@brief Function for initializing the Alert Notification Client.
 *
 * @param[out]  p_ans       Alert Notification Client structure. This structure will have to be
 *                          supplied by the application. It will be initialized by this function,
 *                          and will later be used to identify this particular client instance.
 * @param[in]   p_ans_init  Information needed to initialize the client.
 *
 * @return      NRF_SUCCESS on successful initialization of client, otherwise an error code.
 */
uint32_t ble_ans_c_init(ble_ans_c_t * p_ans, const ble_ans_c_init_t * p_ans_init);


/**@brief Function for writing the to CCCD to enable new alert notifications from the Alert Notification Service.
 *
 * @param[in]  p_ans       Alert Notification structure. This structure will have to be supplied by
 *                         the application. It identifies the particular client instance to use.
 *
 * @return     NRF_SUCCESS on successful writing of the CCCD, otherwise an error code.
 */
uint32_t ble_ans_c_enable_notif_new_alert(const ble_ans_c_t * p_ans);


/**@brief Function for writing to the CCCD to enable unread alert notifications from the Alert Notification Service.
 *
 * @param[in]  p_ans       Alert Notification structure. This structure will have to be supplied by
 *                         the application. It identifies the particular client instance to use.
 *
 * @return     NRF_SUCCESS on successful writing of the CCCD, otherwise an error code.
 */
uint32_t ble_ans_c_enable_notif_unread_alert(const ble_ans_c_t * p_ans);


/**@brief Function for writing to the CCCD to disable new alert notifications from the Alert Notification Service.
 *
 * @param[in]  p_ans       Alert Notification structure. This structure will have to be supplied by
 *                         the application. It identifies the particular client instance to use.
 *
 * @return     NRF_SUCCESS on successful writing of the CCCD, otherwise an error code.
 */
uint32_t ble_ans_c_disable_notif_new_alert(const ble_ans_c_t * p_ans);


/**@brief Function for writing to the CCCD to disable unread alert notifications from the Alert Notification Service.
 *
 * @param[in]  p_ans       Alert Notification structure. This structure will have to be supplied by
 *                         the application. It identifies the particular client instance to use.
 *
 * @return     NRF_SUCCESS on successful writing of the CCCD, otherwise an error code.
 */
uint32_t ble_ans_c_disable_notif_unread_alert(const ble_ans_c_t * p_ans);


/**@brief Function for writing to the Alert Notification Control Point to specify alert notification behavior in the
 * Alert Notification Service on the Central.
 *
 * @param[in]  p_ans           Alert Notification structure. This structure will have to be
 *                             supplied by the application. It identifies the particular client
 *                             instance to use.
 * @param[in]  p_control_point Alert Notification Control Point structure. This structure
 *                             specifies the values to write to the Alert Notification Control
 *                             Point, UUID 0x2A44.
 *
 * @return     NRF_SUCCESS     on successful writing of the Control Point, otherwise an error code.
 */
uint32_t ble_ans_c_control_point_write(const ble_ans_c_t             * p_ans,
                                       const ble_ans_control_point_t * p_control_point);


/**@brief Function for reading the Supported New Alert characteristic value of the service.
 *        The value describes the alerts supported in the central.
 *
 * @param[in]  p_ans       Alert Notification structure. This structure will have to be supplied by
 *                         the application. It identifies the particular client instance to use.
 *
 * @return     NRF_SUCCESS on successful transmission of the read request, otherwise an error code.
 */
uint32_t ble_ans_c_new_alert_read(const ble_ans_c_t * p_ans);


/**@brief Function for reading the Supported Unread Alert characteristic value of the service.
 *        The value describes the alerts supported in the central.
 *
 * @param[in]  p_ans       Alert Notification structure. This structure will have to be supplied by
 *                         the application. It identifies the particular client instance to use.
 *
 * @return     NRF_SUCCESS on successful transmission of the read request, otherwise an error code.
 */
uint32_t ble_ans_c_unread_alert_read(const ble_ans_c_t * p_ans);


/**@brief Function for requesting the peer to notify the New Alert characteristics immediately.
 *
 * @param[in]  p_ans       Alert Notification structure. This structure will have to be supplied by
 *                         the application. It identifies the particular client instance to use.
 * @param[in]  category    The category ID for which the peer should notify the client.
 *
 * @return     NRF_SUCCESS on successful transmission of the read request, otherwise an error code.
 */
uint32_t ble_ans_c_new_alert_notify(const ble_ans_c_t * p_ans, ble_ans_category_id_t category);


/**@brief Function for requesting the peer to notify the Unread Alert characteristics immediately.
 *
 * @param[in]  p_ans       Alert Notification structure. This structure will have to be supplied by
 *                         the application. It identifies the particular client instance to use.
 * @param[in]  category    The category ID for which the peer should notify the client.
 *
 * @return     NRF_SUCCESS on successful transmission of the read request, otherwise an error code.
 */
uint32_t ble_ans_c_unread_alert_notify(const ble_ans_c_t * p_ans, ble_ans_category_id_t category);


/**@brief     Function for assigning a handles to a an instance of ans_c.
 *
 * @details   Call this function when a link has been established with a peer to
 *            associate this link to an instance of the module. This makes it
 *            possible to handle several link and associate each link to a particular
 *            instance of the ans_c module. The connection handle and attribute handles will be
 *            provided from the discovery event @ref BLE_ANS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in] p_ans              Pointer to the Alert Notification client structure instance to
 *                               associate with the handles.
 * @param[in] conn_handle        Connection handle to associated with the given Alert Notification Client
 *                               Instance.
 * @param[in] p_peer_handles     Attribute handles on the ANS server that you want this ANS client to
 *                               interact with.
 *
 */
uint32_t ble_ans_c_handles_assign(ble_ans_c_t               * p_ans,
                                  const uint16_t              conn_handle,
                                  const ble_ans_c_service_t * p_peer_handles);




#ifdef __cplusplus
}
#endif

#endif // BLE_ANS_C_H__

/** @} */

