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
/* Disclaimer: This client implementation of the Apple Notification Center Service can and will be changed at any time by Nordic Semiconductor ASA.
 * Server implementations such as the ones found in iOS can be changed at any time by Apple and may cause this client implementation to stop working.
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_ANCS_C)
#include "nrf_ble_ancs_c.h"
#include "ancs_tx_buffer.h"
#include "ancs_attr_parser.h"
#include "ancs_app_attr_get.h"
#include "ble_err.h"
#include "ble_srv_common.h"
#include "ble_db_discovery.h"
#include "app_error.h"
#define NRF_LOG_MODULE_NAME ble_ancs_c
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define BLE_ANCS_NOTIF_EVT_ID_INDEX       0     /**< Index of the Event ID field when parsing notifications. */
#define BLE_ANCS_NOTIF_FLAGS_INDEX        1     /**< Index of the Flags field when parsing notifications. */
#define BLE_ANCS_NOTIF_CATEGORY_ID_INDEX  2     /**< Index of the Category ID field when parsing notifications. */
#define BLE_ANCS_NOTIF_CATEGORY_CNT_INDEX 3     /**< Index of the Category Count field when parsing notifications. */
#define BLE_ANCS_NOTIF_NOTIF_UID          4     /**< Index of the Notification UID field when patsin notifications. */

#define BLE_CCCD_NOTIFY_BIT_MASK         0x0001 /**< Enable notification bit. */

#define TIME_STRING_LEN                  15     /**< Unicode Technical Standard (UTS) #35 date format pattern "yyyyMMdd'T'HHmmSS" + "'\0'". */


/**@brief 128-bit service UUID for the Apple Notification Center Service. */
ble_uuid128_t const ble_ancs_base_uuid128 =
{
    {
        // 7905F431-B5CE-4E99-A40F-4B1E122D00D0
        0xd0, 0x00, 0x2d, 0x12, 0x1e, 0x4b, 0x0f, 0xa4,
        0x99, 0x4e, 0xce, 0xb5, 0x31, 0xf4, 0x05, 0x79
    }
};


/**@brief 128-bit control point UUID. */
ble_uuid128_t const ble_ancs_cp_base_uuid128 =
{
    {
        // 69d1d8f3-45e1-49a8-9821-9BBDFDAAD9D9
        0xd9, 0xd9, 0xaa, 0xfd, 0xbd, 0x9b, 0x21, 0x98,
        0xa8, 0x49, 0xe1, 0x45, 0xf3, 0xd8, 0xd1, 0x69
    }
};

/**@brief 128-bit notification source UUID. */
ble_uuid128_t const ble_ancs_ns_base_uuid128 =
{
    {
        // 9FBF120D-6301-42D9-8C58-25E699A21DBD
        0xbd, 0x1d, 0xa2, 0x99, 0xe6, 0x25, 0x58, 0x8c,
        0xd9, 0x42, 0x01, 0x63, 0x0d, 0x12, 0xbf, 0x9f

    }
};

/**@brief 128-bit data source UUID. */
ble_uuid128_t const ble_ancs_ds_base_uuid128 =
{
    {
        // 22EAC6E9-24D6-4BB5-BE44-B36ACE7C7BFB
        0xfb, 0x7b, 0x7c, 0xce, 0x6a, 0xb3, 0x44, 0xbe,
        0xb5, 0x4b, 0xd6, 0x24, 0xe9, 0xc6, 0xea, 0x22
    }
};


/**@brief  Function for handling Disconnected event received from the SoftDevice.
 *
 * @details This function check if the disconnect event is happening on the link
 *          associated with the current instance of the module, if so it will set its
 *          conn_handle to invalid.
 *
 * @param[in] p_ancs    Pointer to the ANCS client structure.
 * @param[in] p_ble_evt Pointer to the BLE event received.
 */
static void on_disconnected(ble_ancs_c_t * p_ancs, ble_evt_t const * p_ble_evt)
{
    if (p_ancs->conn_handle == p_ble_evt->evt.gap_evt.conn_handle)
    {
        p_ancs->conn_handle = BLE_CONN_HANDLE_INVALID;
    }
}


void ble_ancs_c_on_db_disc_evt(ble_ancs_c_t * p_ancs, ble_db_discovery_evt_t * p_evt)
{
    NRF_LOG_DEBUG("Database Discovery handler called with event 0x%x", p_evt->evt_type);

    ble_ancs_c_evt_t     evt;
    ble_gatt_db_char_t * p_chars;

    p_chars = p_evt->params.discovered_db.charateristics;

    // Check if the ANCS Service was discovered.
    if (   (p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE)
        && (p_evt->params.discovered_db.srv_uuid.uuid == ANCS_UUID_SERVICE)
        && (p_evt->params.discovered_db.srv_uuid.type == p_ancs->service.service.uuid.type))
    {
        // Find the handles of the ANCS characteristic.
        for (uint32_t i = 0; i < p_evt->params.discovered_db.char_count; i++)
        {
            switch (p_chars[i].characteristic.uuid.uuid)
            {
                case ANCS_UUID_CHAR_CONTROL_POINT:
                    NRF_LOG_INFO("Control Point Characteristic found.");
                    memcpy(&evt.service.control_point_char,
                           &p_chars[i].characteristic,
                           sizeof(ble_gattc_char_t));
                    break;

                case ANCS_UUID_CHAR_DATA_SOURCE:
                    NRF_LOG_INFO("Data Source Characteristic found.");
                    memcpy(&evt.service.data_source_char,
                           &p_chars[i].characteristic,
                           sizeof(ble_gattc_char_t));
                    evt.service.data_source_cccd.handle = p_chars[i].cccd_handle;
                    break;

                case ANCS_UUID_CHAR_NOTIFICATION_SOURCE:
                    NRF_LOG_INFO("Notification point Characteristic found.");
                    memcpy(&evt.service.notif_source_char,
                           &p_chars[i].characteristic,
                           sizeof(ble_gattc_char_t));
                    evt.service.notif_source_cccd.handle = p_chars[i].cccd_handle;
                    break;

                default:
                    break;
            }
        }
        evt.evt_type    = BLE_ANCS_C_EVT_DISCOVERY_COMPLETE;
        evt.conn_handle = p_evt->conn_handle;
        p_ancs->evt_handler(&evt);
    }
    else
    {
        evt.evt_type = BLE_ANCS_C_EVT_DISCOVERY_FAILED;
        p_ancs->evt_handler(&evt);
    }
}


/**@brief Function for checking if data in an iOS notification is out of bounds.
 *
 * @param[in] notif  An iOS notification.
 *
 * @retval NRF_SUCCESS             If the notification is within bounds.
 * @retval NRF_ERROR_INVALID_PARAM If the notification is out of bounds.
 */
static uint32_t ble_ancs_verify_notification_format(ble_ancs_c_evt_notif_t const * notif)
{
    if (   (notif->evt_id >= BLE_ANCS_NB_OF_EVT_ID)
       || (notif->category_id >= BLE_ANCS_NB_OF_CATEGORY_ID))
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    return NRF_SUCCESS;
}

/**@brief Function for receiving and validating notifications received from the Notification Provider.
 *
 * @param[in] p_ancs     Pointer to an ANCS instance to which the event belongs.
 * @param[in] p_data_src Pointer to data that was received from the Notification Provider.
 * @param[in] hvx_len    Length of the data that was received by the Notification Provider.
 */
static void parse_notif(ble_ancs_c_t const * p_ancs,
                        uint8_t      const * p_data_src,
                        uint16_t     const   hvx_data_len)
{
    ble_ancs_c_evt_t ancs_evt;
    uint32_t         err_code;
    if (hvx_data_len != BLE_ANCS_NOTIFICATION_DATA_LENGTH)
    {
        ancs_evt.evt_type = BLE_ANCS_C_EVT_INVALID_NOTIF;
        p_ancs->evt_handler(&ancs_evt);
    }

    /*lint --e{415} --e{416} -save suppress Warning 415: possible access out of bond */
    ancs_evt.notif.evt_id                    =
            (ble_ancs_c_evt_id_values_t) p_data_src[BLE_ANCS_NOTIF_EVT_ID_INDEX];

    ancs_evt.notif.evt_flags.silent          =
            (p_data_src[BLE_ANCS_NOTIF_FLAGS_INDEX] >> BLE_ANCS_EVENT_FLAG_SILENT) & 0x01;

    ancs_evt.notif.evt_flags.important       =
            (p_data_src[BLE_ANCS_NOTIF_FLAGS_INDEX] >> BLE_ANCS_EVENT_FLAG_IMPORTANT) & 0x01;

    ancs_evt.notif.evt_flags.pre_existing    =
            (p_data_src[BLE_ANCS_NOTIF_FLAGS_INDEX] >> BLE_ANCS_EVENT_FLAG_PREEXISTING) & 0x01;

    ancs_evt.notif.evt_flags.positive_action =
            (p_data_src[BLE_ANCS_NOTIF_FLAGS_INDEX] >> BLE_ANCS_EVENT_FLAG_POSITIVE_ACTION) & 0x01;

    ancs_evt.notif.evt_flags.negative_action =
            (p_data_src[BLE_ANCS_NOTIF_FLAGS_INDEX] >> BLE_ANCS_EVENT_FLAG_NEGATIVE_ACTION) & 0x01;

    ancs_evt.notif.category_id               =
        (ble_ancs_c_category_id_val_t) p_data_src[BLE_ANCS_NOTIF_CATEGORY_ID_INDEX];

    ancs_evt.notif.category_count            = p_data_src[BLE_ANCS_NOTIF_CATEGORY_CNT_INDEX];
    ancs_evt.notif.notif_uid = uint32_decode(&p_data_src[BLE_ANCS_NOTIF_NOTIF_UID]);
    /*lint -restore*/

    err_code = ble_ancs_verify_notification_format(&ancs_evt.notif);
    if (err_code == NRF_SUCCESS)
    {
        ancs_evt.evt_type = BLE_ANCS_C_EVT_NOTIF;
    }
    else
    {
        ancs_evt.evt_type = BLE_ANCS_C_EVT_INVALID_NOTIF;
    }

    p_ancs->evt_handler(&ancs_evt);
}


ret_code_t nrf_ble_ancs_c_app_attr_request(ble_ancs_c_t  * p_ancs,
                                           uint8_t const * p_app_id,
                                           uint32_t        len)
{
    return ancs_c_app_attr_request(p_ancs, p_app_id, len);
}


/**@brief Function for receiving and validating notifications received from the Notification Provider.
 *
 * @param[in] p_ancs    Pointer to an ANCS instance to which the event belongs.
 * @param[in] p_ble_evt Bluetooth stack event.
 */
static void on_evt_gattc_notif(ble_ancs_c_t * p_ancs, ble_evt_t const * p_ble_evt)
{
    ble_gattc_evt_hvx_t const * p_notif = &p_ble_evt->evt.gattc_evt.params.hvx;

    if (p_ble_evt->evt.gattc_evt.conn_handle != p_ancs->conn_handle)
    {
        return;
    }

    if (p_notif->handle == p_ancs->service.notif_source_char.handle_value)
    {
        parse_notif(p_ancs, p_notif->data, p_notif->len);
    }
    else if (p_notif->handle == p_ancs->service.data_source_char.handle_value)
    {
        ancs_parse_get_attrs_response(p_ancs, p_notif->data, p_notif->len);
    }
    else
    {
        // No applicable action.
    }
}

/**@brief Function for handling error response events.
 *
 * @param[in] p_ancs_c   Pointer to the Battery Service Client Structure.
 * @param[in] p_ble_evt Pointer to the SoftDevice event.
 */
static void on_ctrlpt_error_rsp(ble_ancs_c_t * p_ancs, ble_evt_t const * p_ble_evt)
{
    ble_ancs_c_evt_t ancs_evt;

    ancs_evt.evt_type    = BLE_ANCS_C_EVT_NP_ERROR;
    ancs_evt.err_code_np = p_ble_evt->evt.gattc_evt.gatt_status;

    p_ancs->evt_handler(&ancs_evt);
}

/**@brief Function for handling write response events.
 *
 * @param[in] p_ancs_c   Pointer to the Battery Service Client Structure.
 * @param[in] p_ble_evt Pointer to the SoftDevice event.
 */
static void on_write_rsp(ble_ancs_c_t * p_ancs, ble_evt_t const* p_ble_evt)
{
    // Check if the event if on the link for this instance
    if (p_ancs->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle)
    {
        return;
    }
    if ((p_ble_evt->evt.gattc_evt.error_handle != BLE_GATT_HANDLE_INVALID)
        && (p_ble_evt->evt.gattc_evt.error_handle == p_ancs->service.control_point_char.handle_value))
    {
         on_ctrlpt_error_rsp(p_ancs,p_ble_evt);
    }
    // Check if there is any message to be sent across to the peer and send it.
    tx_buffer_process();
}


void ble_ancs_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_ancs_c_t * p_ancs = (ble_ancs_c_t *)p_context;
    uint16_t        evt   = p_ble_evt->header.evt_id;

    switch (evt)
    {
        case BLE_GATTC_EVT_WRITE_RSP:
            on_write_rsp(p_ancs, p_ble_evt);
            break;

        case BLE_GATTC_EVT_HVX:
            on_evt_gattc_notif(p_ancs, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnected(p_ancs, p_ble_evt);
            break;

        default:
            break;
    }
}


ret_code_t ble_ancs_c_init(ble_ancs_c_t * p_ancs, ble_ancs_c_init_t const * p_ancs_init)
{
    uint32_t err_code;

    //Verify that the parameters needed for to initialize this instance of ANCS are not NULL.
    VERIFY_PARAM_NOT_NULL(p_ancs);
    VERIFY_PARAM_NOT_NULL(p_ancs_init);
    VERIFY_PARAM_NOT_NULL(p_ancs_init->evt_handler);

    //Initialize state for the attribute parsing state machine.
    p_ancs->parse_info.parse_state = COMMAND_ID;
    p_ancs->parse_info.p_data_dest = NULL;
    p_ancs->parse_info.current_attr_index   = 0;
    p_ancs->parse_info.current_app_id_index = 0;

    p_ancs->evt_handler   = p_ancs_init->evt_handler;
    p_ancs->error_handler = p_ancs_init->error_handler;
    p_ancs->conn_handle   = BLE_CONN_HANDLE_INVALID;

    p_ancs->service.data_source_cccd.uuid.uuid  = BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG;
    p_ancs->service.notif_source_cccd.uuid.uuid = BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG;

    // Make sure instance of service is clear. GATT handles inside the service and characteristics are set to @ref BLE_GATT_HANDLE_INVALID.
    memset(&p_ancs->service, 0, sizeof(ble_ancs_c_service_t));
    tx_buffer_init();

    // Assign UUID types.
    err_code = sd_ble_uuid_vs_add(&ble_ancs_base_uuid128, &p_ancs->service.service.uuid.type);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ble_uuid_vs_add(&ble_ancs_cp_base_uuid128, &p_ancs->service.control_point_char.uuid.type);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ble_uuid_vs_add(&ble_ancs_ns_base_uuid128, &p_ancs->service.notif_source_char.uuid.type);
    VERIFY_SUCCESS(err_code);

    err_code = sd_ble_uuid_vs_add(&ble_ancs_ds_base_uuid128, &p_ancs->service.data_source_char.uuid.type);
    VERIFY_SUCCESS(err_code);

    // Assign UUID to the service.
    p_ancs->service.service.uuid.uuid = ANCS_UUID_SERVICE;
    p_ancs->service.service.uuid.type = p_ancs->service.service.uuid.type;

    return ble_db_discovery_evt_register(&p_ancs->service.service.uuid);
}


/**@brief Function for creating a TX message for writing a CCCD.
 *
 * @param[in] conn_handle  Connection handle on which to perform the configuration.
 * @param[in] handle_cccd  Handle of the CCCD.
 * @param[in] enable       Enable or disable GATTC notifications.
 *
 * @retval NRF_SUCCESS              If the message was created successfully.
 * @retval NRF_ERROR_INVALID_PARAM  If one of the input parameters was invalid.
 */
static uint32_t cccd_configure(const uint16_t conn_handle, const uint16_t handle_cccd, bool enable)
{
    tx_message_t   p_msg;
    memset(&p_msg, 0, sizeof(tx_message_t));
    uint16_t       cccd_val = enable ? BLE_CCCD_NOTIFY_BIT_MASK : 0;

    p_msg.req.write_req.gattc_params.handle   = handle_cccd;
    p_msg.req.write_req.gattc_params.len      = 2;
    p_msg.req.write_req.gattc_params.p_value  = p_msg.req.write_req.gattc_value;
    p_msg.req.write_req.gattc_params.offset   = 0;
    p_msg.req.write_req.gattc_params.write_op = BLE_GATT_OP_WRITE_REQ;
    p_msg.req.write_req.gattc_value[0]        = LSB_16(cccd_val);
    p_msg.req.write_req.gattc_value[1]        = MSB_16(cccd_val);
    p_msg.conn_handle                         = conn_handle;
    p_msg.type                                = WRITE_REQ;

    tx_buffer_insert(&p_msg);

    tx_buffer_process();
    return NRF_SUCCESS;
}


ret_code_t ble_ancs_c_notif_source_notif_enable(ble_ancs_c_t const * p_ancs)
{
    NRF_LOG_INFO("Enable Notification Source notifications. writing to handle: %i ",
         p_ancs->service.notif_source_cccd.handle);
    return cccd_configure(p_ancs->conn_handle, p_ancs->service.notif_source_cccd.handle, true);
}


ret_code_t ble_ancs_c_notif_source_notif_disable(ble_ancs_c_t const * p_ancs)
{
    return cccd_configure(p_ancs->conn_handle, p_ancs->service.notif_source_cccd.handle, false);
}


ret_code_t ble_ancs_c_data_source_notif_enable(ble_ancs_c_t const * p_ancs)
{
    NRF_LOG_INFO("Enable Data Source notifications. Writing to handle: %i ",
        p_ancs->service.data_source_cccd.handle);
    return cccd_configure(p_ancs->conn_handle, p_ancs->service.data_source_cccd.handle, true);
}


ret_code_t ble_ancs_c_data_source_notif_disable(ble_ancs_c_t const * p_ancs)
{
    return cccd_configure(p_ancs->conn_handle, p_ancs->service.data_source_cccd.handle, false);
}


uint32_t ble_ancs_get_notif_attrs(ble_ancs_c_t * p_ancs,
                                  uint32_t const p_uid)
{
    tx_message_t p_msg;
    memset(&p_msg, 0, sizeof(tx_message_t));

    uint32_t index                   = 0;
    p_ancs->number_of_requested_attr = 0;


    p_msg.req.write_req.gattc_params.handle   = p_ancs->service.control_point_char.handle_value;
    p_msg.req.write_req.gattc_params.p_value  = p_msg.req.write_req.gattc_value;
    p_msg.req.write_req.gattc_params.offset   = 0;
    p_msg.req.write_req.gattc_params.write_op = BLE_GATT_OP_WRITE_REQ;

    //Encode Command ID.
    p_msg.req.write_req.gattc_value[index++] = BLE_ANCS_COMMAND_ID_GET_NOTIF_ATTRIBUTES;

    //Encode Notification UID.
    index += uint32_encode(p_uid, &(p_msg.req.write_req.gattc_value[index]));

    //Encode Attribute ID.
    for (uint32_t attr = 0; attr < BLE_ANCS_NB_OF_NOTIF_ATTR; attr++)
    {
        if (p_ancs->ancs_notif_attr_list[attr].get == true)
        {
            p_msg.req.write_req.gattc_value[index++] = attr;
            if ((attr == BLE_ANCS_NOTIF_ATTR_ID_TITLE) ||
                (attr == BLE_ANCS_NOTIF_ATTR_ID_SUBTITLE) ||
                (attr == BLE_ANCS_NOTIF_ATTR_ID_MESSAGE))
            {
                //Encode Length field, only applicable for Title, Subtitle and Message
                index += uint16_encode(p_ancs->ancs_notif_attr_list[attr].attr_len,
                                       &(p_msg.req.write_req.gattc_value[index]));
            }
            p_ancs->number_of_requested_attr++;
        }
    }
    p_msg.req.write_req.gattc_params.len        = index;
    p_msg.conn_handle                           = p_ancs->conn_handle;
    p_msg.type                                  = WRITE_REQ;
    p_ancs->parse_info.expected_number_of_attrs = p_ancs->number_of_requested_attr;

    tx_buffer_insert(&p_msg);
    tx_buffer_process();

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_ancs_c_attr_add(ble_ancs_c_t                       * p_ancs,
                                   ble_ancs_c_notif_attr_id_val_t const id,
                                   uint8_t                            * p_data,
                                   uint16_t const                      len)
{
    VERIFY_PARAM_NOT_NULL(p_data);

    if ((len == 0) || (len > BLE_ANCS_ATTR_DATA_MAX))
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    p_ancs->ancs_notif_attr_list[id].get         = true;
    p_ancs->ancs_notif_attr_list[id].attr_len    = len;
    p_ancs->ancs_notif_attr_list[id].p_attr_data = p_data;

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_ancs_c_app_attr_add(ble_ancs_c_t                     * p_ancs,
                                       ble_ancs_c_app_attr_id_val_t const id,
                                       uint8_t                          * p_data,
                                       uint16_t const                     len)
{
    VERIFY_PARAM_NOT_NULL(p_ancs);
    VERIFY_PARAM_NOT_NULL(p_data);

    if ((len == 0) || (len > BLE_ANCS_ATTR_DATA_MAX))
    {
        return NRF_ERROR_INVALID_LENGTH;
    }

    p_ancs->ancs_app_attr_list[id].get         = true;
    p_ancs->ancs_app_attr_list[id].attr_len    = len;
    p_ancs->ancs_app_attr_list[id].p_attr_data = p_data;

    return NRF_SUCCESS;
}

ret_code_t ble_ancs_c_app_attr_remove(ble_ancs_c_t                     * p_ancs,
                                      ble_ancs_c_app_attr_id_val_t const id)
{
    p_ancs->ancs_app_attr_list[id].get         = false;
    p_ancs->ancs_app_attr_list[id].attr_len    = 0;
    p_ancs->ancs_app_attr_list[id].p_attr_data = NULL;
    return NRF_SUCCESS;
}

ret_code_t ble_ancs_c_notif_attr_remove(ble_ancs_c_t                          * p_ancs,
                                        ble_ancs_c_notif_attr_id_val_t const id)
{
    p_ancs->ancs_notif_attr_list[id].get         = false;
    p_ancs->ancs_notif_attr_list[id].attr_len    = 0;
    p_ancs->ancs_notif_attr_list[id].p_attr_data = NULL;
    return NRF_SUCCESS;
}

ret_code_t nrf_ble_ancs_c_attr_req_clear_all(ble_ancs_c_t * p_ancs)
{
    memset(p_ancs->ancs_notif_attr_list, 0 , sizeof(p_ancs->ancs_notif_attr_list));
    memset(p_ancs->ancs_app_attr_list, 0 , sizeof(p_ancs->ancs_app_attr_list));
    return NRF_SUCCESS;
}


ret_code_t nrf_ble_ancs_c_request_attrs(ble_ancs_c_t * p_ancs,
                                        ble_ancs_c_evt_notif_t const * p_notif)
{
    uint32_t err_code;
    err_code = ble_ancs_verify_notification_format(p_notif);
    VERIFY_SUCCESS(err_code);

    err_code                       = ble_ancs_get_notif_attrs(p_ancs, p_notif->notif_uid);
    p_ancs->parse_info.parse_state = COMMAND_ID;
    VERIFY_SUCCESS(err_code);

    return NRF_SUCCESS;
}

static uint16_t encode_notif_action(uint8_t * p_encoded_data, uint32_t uid, ble_ancs_c_action_id_values_t action_id)
{
    uint8_t index = 0;

    p_encoded_data[index++] = BLE_ANCS_COMMAND_ID_GET_PERFORM_NOTIF_ACTION;
    index                  += uint32_encode(uid, &p_encoded_data[index]);
    p_encoded_data[index++] = (uint8_t)action_id;

    return index;
}

ret_code_t nrf_ancs_perform_notif_action(ble_ancs_c_t * p_ancs, uint32_t uid, ble_ancs_c_action_id_values_t action_id)
{
    VERIFY_PARAM_NOT_NULL(p_ancs);

    tx_message_t msg;
    memset(&msg, 0, sizeof(tx_message_t));

    uint16_t len = encode_notif_action(msg.req.write_req.gattc_value, uid, action_id);

    msg.req.write_req.gattc_params.handle   = p_ancs->service.control_point_char.handle_value;
    msg.req.write_req.gattc_params.p_value  = msg.req.write_req.gattc_value;
    msg.req.write_req.gattc_params.offset   = 0;
    msg.req.write_req.gattc_params.write_op = BLE_GATT_OP_WRITE_REQ;

    msg.req.write_req.gattc_params.len      = len;
    msg.conn_handle                         = p_ancs->conn_handle;
    msg.type                                = WRITE_REQ;

    tx_buffer_insert(&msg);
    tx_buffer_process();

    return NRF_SUCCESS;
}

ret_code_t nrf_ble_ancs_c_handles_assign(ble_ancs_c_t * p_ancs,
                                         uint16_t const conn_handle,
                                         ble_ancs_c_service_t const * p_peer_handles)
{
    VERIFY_PARAM_NOT_NULL(p_ancs);

    p_ancs->conn_handle = conn_handle;

    if (p_peer_handles != NULL)
    {
        p_ancs->service.control_point_char.handle_value = p_peer_handles->control_point_char.handle_value;
        p_ancs->service.data_source_cccd.handle         = p_peer_handles->data_source_cccd.handle;
        p_ancs->service.data_source_char.handle_value   = p_peer_handles->data_source_char.handle_value;
        p_ancs->service.notif_source_cccd.handle        = p_peer_handles->notif_source_cccd.handle;
        p_ancs->service.notif_source_char.handle_value  = p_peer_handles->notif_source_char.handle_value;
    }

    return NRF_SUCCESS;
}

#endif// NRF_MODULE_ENABLED(BLE_ANCS_C)
