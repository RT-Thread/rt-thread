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
 * @defgroup ble_hids Human Interface Device Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Human Interface Device Service module.
 *
 * @details This module implements the Human Interface Device Service with the corresponding set of
 *          characteristics. During initialization it adds the Human Interface Device Service and
 *          a set of characteristics as per the Human Interface Device Service specification and
 *          the user requirements to the BLE stack database.
 *
 *          If enabled, notification of Input Report characteristics is performed when the
 *          application calls the corresponding ble_hids_xx_input_report_send() function.
 *
 *          If an event handler is supplied by the application, the Human Interface Device Service
 *          will generate Human Interface Device Service events to the application.
 *
 * @note The application must propagate BLE stack events to the Human Interface Device Service
 *       module by calling ble_hids_on_ble_evt() from the @ref softdevice_handler callback.
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_HIDS_H__
#define BLE_HIDS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @name Report Type values
 * @anchor BLE_HIDS_REPORT_TYPE @{
 */
// Report Type values
#define BLE_HIDS_REP_TYPE_INPUT                 1
#define BLE_HIDS_REP_TYPE_OUTPUT                2
#define BLE_HIDS_REP_TYPE_FEATURE               3
/** @} */

// Maximum number of the various Report Types
#define BLE_HIDS_MAX_INPUT_REP                  10
#define BLE_HIDS_MAX_OUTPUT_REP                 10
#define BLE_HIDS_MAX_FEATURE_REP                10

// Information Flags
#define HID_INFO_FLAG_REMOTE_WAKE_MSK           0x01
#define HID_INFO_FLAG_NORMALLY_CONNECTABLE_MSK  0x02

/**@brief HID Service characteristic id. */
typedef struct
{
    uint16_t uuid;                                  /**< UUID of characteristic. */
    uint8_t  rep_type;                              /**< Type of report (only used for BLE_UUID_REPORT_CHAR, see @ref BLE_HIDS_REPORT_TYPE). */
    uint8_t  rep_index;                             /**< Index of the characteristic (only used for BLE_UUID_REPORT_CHAR). */
} ble_hids_char_id_t;

/**@brief HID Service event type. */
typedef enum
{
    BLE_HIDS_EVT_HOST_SUSP,                         /**< Suspend command received. */
    BLE_HIDS_EVT_HOST_EXIT_SUSP,                    /**< Exit suspend command received. */
    BLE_HIDS_EVT_NOTIF_ENABLED,                     /**< Notification enabled event. */
    BLE_HIDS_EVT_NOTIF_DISABLED,                    /**< Notification disabled event. */
    BLE_HIDS_EVT_REP_CHAR_WRITE,                    /**< A new value has been written to an Report characteristic. */
    BLE_HIDS_EVT_BOOT_MODE_ENTERED,                 /**< Boot mode entered. */
    BLE_HIDS_EVT_REPORT_MODE_ENTERED,               /**< Report mode entered. */
    BLE_HIDS_EVT_REPORT_READ                        /**< Read with response */
} ble_hids_evt_type_t;

/**@brief HID Service event. */
typedef struct
{
    ble_hids_evt_type_t evt_type;                   /**< Type of event. */
    union
    {
        struct
        {
            ble_hids_char_id_t char_id;             /**< Id of characteristic for which notification has been started. */
        } notification;
        struct
        {
            ble_hids_char_id_t char_id;             /**< Id of characteristic having been written. */
            uint16_t           offset;              /**< Offset for the write operation. */
            uint16_t           len;                 /**< Length of the incoming data. */
            uint8_t*           data;                /**< Incoming data, variable length */
        } char_write;
        struct
        {
            ble_hids_char_id_t char_id;             /**< Id of characteristic being read. */
        } char_auth_read;
    } params;
    ble_evt_t * p_ble_evt;                          /**< corresponding received ble event, NULL if not relevant */
} ble_hids_evt_t;

// Forward declaration of the ble_hids_t type.
typedef struct ble_hids_s ble_hids_t;

/**@brief HID Service event handler type. */
typedef void (*ble_hids_evt_handler_t) (ble_hids_t * p_hids, ble_hids_evt_t * p_evt);

/**@brief HID Information characteristic value. */
typedef struct
{
    uint16_t                      bcd_hid;          /**< 16-bit unsigned integer representing version number of base USB HID Specification implemented by HID Device */
    uint8_t                       b_country_code;   /**< Identifies which country the hardware is localized for. Most hardware is not localized and thus this value would be zero (0). */
    uint8_t                       flags;            /**< See http://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.hid_information.xml */
    ble_srv_security_mode_t       security_mode;    /**< Security mode for the HID Information characteristic. */
} ble_hids_hid_information_t;

/**@brief HID Service Input Report characteristic init structure. This contains all options and
 *        data needed for initialization of one Input Report characteristic. */
typedef struct
{
    uint16_t                      max_len;          /**< Maximum length of characteristic value. */
    ble_srv_report_ref_t          rep_ref;          /**< Value of the Report Reference descriptor. */
    ble_srv_cccd_security_mode_t  security_mode;    /**< Security mode for the HID Input Report characteristic, including cccd. */
    uint8_t                       read_resp : 1;    /**< Should application generate a response to read requests. */
} ble_hids_inp_rep_init_t;

/**@brief HID Service Output Report characteristic init structure. This contains all options and
 *        data needed for initialization of one Output Report characteristic. */
typedef struct
{
    uint16_t                      max_len;          /**< Maximum length of characteristic value. */
    ble_srv_report_ref_t          rep_ref;          /**< Value of the Report Reference descriptor. */
    ble_srv_cccd_security_mode_t  security_mode;    /**< Security mode for the HID Output Report characteristic, including cccd. */
    uint8_t                       read_resp : 1;    /**< Should application generate a response to read requests. */
} ble_hids_outp_rep_init_t;

/**@brief HID Service Feature Report characteristic init structure. This contains all options and
 *        data needed for initialization of one Feature Report characteristic. */
typedef struct
{
    uint16_t                      max_len;          /**< Maximum length of characteristic value. */
    ble_srv_report_ref_t          rep_ref;          /**< Value of the Report Reference descriptor. */
    ble_srv_cccd_security_mode_t  security_mode;    /**< Security mode for the HID Service Feature Report characteristic, including cccd. */
    uint8_t                       read_resp : 1;    /**< Should application generate a response to read requests. */
} ble_hids_feature_rep_init_t;

/**@brief HID Service Report Map characteristic init structure. This contains all options and data
 *        needed for initialization of the Report Map characteristic. */
typedef struct
{
    uint8_t *                     p_data;           /**< Report map data. */
    uint16_t                      data_len;         /**< Length of report map data. */
    uint8_t                       ext_rep_ref_num;  /**< Number of Optional External Report Reference descriptors. */
    ble_uuid_t *                  p_ext_rep_ref;    /**< Optional External Report Reference descriptor (will be added if != NULL). */
    ble_srv_security_mode_t       security_mode;    /**< Security mode for the HID Service Report Map characteristic. */
} ble_hids_rep_map_init_t;

/**@brief HID Report characteristic structure. */
typedef struct
{
    ble_gatts_char_handles_t      char_handles;     /**< Handles related to the Report characteristic. */
    uint16_t                      ref_handle;       /**< Handle of the Report Reference descriptor. */
} ble_hids_rep_char_t;

/**@brief HID Service init structure. This contains all options and data needed for initialization
 *        of the service. */
typedef struct
{
    ble_hids_evt_handler_t        evt_handler;                                  /**< Event handler to be called for handling events in the HID Service. */
    ble_srv_error_handler_t       error_handler;                                /**< Function to be called in case of an error. */
    bool                          is_kb;                                        /**< TRUE if device is operating as a keyboard, FALSE if it is not. */
    bool                          is_mouse;                                     /**< TRUE if device is operating as a mouse, FALSE if it is not. */
    uint8_t                       inp_rep_count;                                /**< Number of Input Report characteristics. */
    ble_hids_inp_rep_init_t *     p_inp_rep_array;                              /**< Information about the Input Report characteristics. */
    uint8_t                       outp_rep_count;                               /**< Number of Output Report characteristics. */
    ble_hids_outp_rep_init_t *    p_outp_rep_array;                             /**< Information about the Output Report characteristics. */
    uint8_t                       feature_rep_count;                            /**< Number of Feature Report characteristics. */
    ble_hids_feature_rep_init_t * p_feature_rep_array;                          /**< Information about the Feature Report characteristics. */
    ble_hids_rep_map_init_t       rep_map;                                      /**< Information nedeed for initialization of the Report Map characteristic. */
    ble_hids_hid_information_t    hid_information;                              /**< Value of the HID Information characteristic. */
    uint8_t                       included_services_count;                      /**< Number of services to include in HID service. */
    uint16_t *                    p_included_services_array;                    /**< Array of services to include in HID service. */
    ble_srv_security_mode_t       security_mode_protocol;                       /**< Security settings for HID service protocol attribute */
    ble_srv_security_mode_t       security_mode_ctrl_point;                     /**< Security settings for HID service Control Point attribute */
    ble_srv_cccd_security_mode_t  security_mode_boot_mouse_inp_rep;             /**< Security settings for HID service Mouse input report attribute */
    ble_srv_cccd_security_mode_t  security_mode_boot_kb_inp_rep;                /**< Security settings for HID service Keyboard input report attribute */
    ble_srv_security_mode_t       security_mode_boot_kb_outp_rep;               /**< Security settings for HID service Keyboard output report attribute */
} ble_hids_init_t;

/**@brief HID Service structure. This contains various status information for the service. */
struct ble_hids_s
{
    ble_hids_evt_handler_t        evt_handler;                                  /**< Event handler to be called for handling events in the HID Service. */
    ble_srv_error_handler_t       error_handler;                                /**< Function to be called in case of an error. */
    uint16_t                      service_handle;                               /**< Handle of HID Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t      protocol_mode_handles;                        /**< Handles related to the Protocol Mode characteristic (will only be created if ble_hids_init_t.is_kb or ble_hids_init_t.is_mouse is set). */
    uint8_t                       inp_rep_count;                                /**< Number of Input Report characteristics. */
    ble_hids_rep_char_t           inp_rep_array[BLE_HIDS_MAX_INPUT_REP];        /**< Information about the Input Report characteristics. */
    uint8_t                       outp_rep_count;                               /**< Number of Output Report characteristics. */
    ble_hids_rep_char_t           outp_rep_array[BLE_HIDS_MAX_OUTPUT_REP];      /**< Information about the Output Report characteristics. */
    uint8_t                       feature_rep_count;                            /**< Number of Feature Report characteristics. */
    ble_hids_rep_char_t           feature_rep_array[BLE_HIDS_MAX_FEATURE_REP];  /**< Information about the Feature Report characteristics. */
    ble_gatts_char_handles_t      rep_map_handles;                              /**< Handles related to the Report Map characteristic. */
    uint16_t                      rep_map_ext_rep_ref_handle;                   /**< Handle of the Report Map External Report Reference descriptor. */
    ble_gatts_char_handles_t      boot_kb_inp_rep_handles;                      /**< Handles related to the Boot Keyboard Input Report characteristic (will only be created if ble_hids_init_t.is_kb is set). */
    ble_gatts_char_handles_t      boot_kb_outp_rep_handles;                     /**< Handles related to the Boot Keyboard Output Report characteristic (will only be created if ble_hids_init_t.is_kb is set). */
    ble_gatts_char_handles_t      boot_mouse_inp_rep_handles;                   /**< Handles related to the Boot Mouse Input Report characteristic (will only be created if ble_hids_init_t.is_mouse is set). */
    ble_gatts_char_handles_t      hid_information_handles;                      /**< Handles related to the Report Map characteristic. */
    ble_gatts_char_handles_t      hid_control_point_handles;                    /**< Handles related to the Report Map characteristic. */
    uint16_t                      conn_handle;                                  /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
};

/**@brief Function for initializing the HID Service.
 *
 * @param[out]  p_hids       HID Service structure. This structure will have to be supplied by the
 *                           application. It will be initialized by this function, and will later be
 *                           used to identify this particular service instance.
 * @param[in]   p_hids_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_hids_init(ble_hids_t * p_hids, const ble_hids_init_t * p_hids_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the HID Service.
 *
 * @param[in]   p_hids     HID Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_hids_on_ble_evt(ble_hids_t * p_hids, ble_evt_t * p_ble_evt);

/**@brief Function for sending Input Report.
 *
 * @details Sends data on an Input Report characteristic.
 *
 * @param[in]   p_hids       HID Service structure.
 * @param[in]   rep_index    Index of the characteristic (corresponding to the index in
 *                           ble_hids_t.inp_rep_array as passed to ble_hids_init()).
 * @param[in]   len          Length of data to be sent.
 * @param[in]   p_data       Pointer to data to be sent.
 *
 * @return      NRF_SUCCESS on successful sending of input report, otherwise an error code.
 */
uint32_t ble_hids_inp_rep_send(ble_hids_t * p_hids,
                               uint8_t      rep_index,
                               uint16_t     len,
                               uint8_t *    p_data);

/**@brief Function for sending Boot Keyboard Input Report.
 *
 * @details Sends data on an Boot Keyboard Input Report characteristic.
 *
 * @param[in]   p_hids       HID Service structure.
 * @param[in]   len          Length of data to be sent.
 * @param[in]   p_data       Pointer to data to be sent.
 *
 * @return      NRF_SUCCESS on successful sending of the report, otherwise an error code.
 */
uint32_t ble_hids_boot_kb_inp_rep_send(ble_hids_t * p_hids,
                                       uint16_t     len,
                                       uint8_t *    p_data);

/**@brief Function for sending Boot Mouse Input Report.
 *
 * @details Sends data on an Boot Mouse Input Report characteristic.
 *
 * @param[in]   p_hids              HID Service structure.
 * @param[in]   buttons             State of mouse buttons.
 * @param[in]   x_delta             Horizontal movement.
 * @param[in]   y_delta             Vertical movement.
 * @param[in]   optional_data_len   Length of optional part of Boot Mouse Input Report.
 * @param[in]   p_optional_data     Optional part of Boot Mouse Input Report.
 *
 * @return      NRF_SUCCESS on successful sending of the report, otherwise an error code.
 */
uint32_t ble_hids_boot_mouse_inp_rep_send(ble_hids_t * p_hids,
                                          uint8_t      buttons,
                                          int8_t       x_delta,
                                          int8_t       y_delta,
                                          uint16_t     optional_data_len,
                                          uint8_t *    p_optional_data);

/**@brief Function for getting the current value of Output Report from the stack.
 *
 * @details Fetches the current value of the output report characteristic from the stack.
 *
 * @param[in]   p_hids      HID Service structure.
 * @param[in]   rep_index   Index of the characteristic (corresponding to the index in
 *                          ble_hids_t.outp_rep_array as passed to ble_hids_init()).
 * @param[in]   len         Length of output report needed.
 * @param[in]   offset      Offset in bytes to read from.
 * @param[out]  p_outp_rep  Pointer to the output report.
 *
 * @return      NRF_SUCCESS on successful read of the report, otherwise an error code.
 */
uint32_t ble_hids_outp_rep_get(ble_hids_t * p_hids,
                               uint8_t      rep_index,
                               uint16_t     len,
                               uint8_t      offset,
                               uint8_t *    p_outp_rep);


#ifdef __cplusplus
}
#endif

#endif // BLE_HIDS_H__

/** @} */
