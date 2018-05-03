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
/* Attention!
*  To maintain compliance with Nordic Semiconductor ASA’s Bluetooth profile
*  qualification listings, this section of source code must not be modified.
*/
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_HIDS)
#include "ble_hids.h"
#include <string.h>
#include "app_error.h"
#include "ble_srv_common.h"


// Protocol Mode values
#define PROTOCOL_MODE_BOOT               0x00                        /**< Boot Protocol Mode. */
#define PROTOCOL_MODE_REPORT             0x01                        /**< Report Protocol Mode. */

// HID Control Point values
#define HIDS_CONTROL_POINT_SUSPEND       0                           /**< Suspend command. */
#define HIDS_CONTROL_POINT_EXIT_SUSPEND  1                           /**< Exit Suspend command. */

#define DEFAULT_PROTOCOL_MODE            PROTOCOL_MODE_REPORT        /**< Default value for the Protocol Mode characteristic. */
#define INITIAL_VALUE_HID_CONTROL_POINT  HIDS_CONTROL_POINT_SUSPEND  /**< Initial value for the HID Control Point characteristic. */

#define ENCODED_HID_INFORMATION_LEN      4                           /**< Maximum size of an encoded HID Information characteristic. */

#define BOOT_KB_INPUT_REPORT_MAX_SIZE    8                           /**< Maximum size of a Boot Keyboard Input Report (as per Appendix B in Device Class Definition for Human Interface Devices (HID), Version 1.11). */
#define BOOT_KB_OUTPUT_REPORT_MAX_SIZE   1                           /**< Maximum size of a Boot Keyboard Output Report (as per Appendix B in Device Class Definition for Human Interface Devices (HID), Version 1.11). */
#define BOOT_MOUSE_INPUT_REPORT_MIN_SIZE 3                           /**< Minimum size of a Boot Mouse Input Report (as per Appendix B in Device Class Definition for Human Interface Devices (HID), Version 1.11). */
#define BOOT_MOUSE_INPUT_REPORT_MAX_SIZE 8                           /**< Maximum size of a Boot Mouse Input Report (as per Appendix B in Device Class Definition for Human Interface Devices (HID), Version 1.11). */


/**@brief Function for making a HID Service characteristic id.
 *
 * @param[in]   uuid        UUID of characteristic.
 * @param[in]   rep_type    Type of report.
 * @param[in]   rep_index   Index of the characteristic.
 *
 * @return      HID Service characteristic id structure.
 */
static ble_hids_char_id_t make_char_id(uint16_t uuid, uint8_t rep_type, uint8_t rep_index)
{
    ble_hids_char_id_t char_id = {0};

    char_id.uuid      = uuid;
    char_id.rep_type  = rep_type;
    char_id.rep_index = rep_index;

    return char_id;
}


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_hids      HID Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_hids_t * p_hids, ble_evt_t * p_ble_evt)
{
    uint32_t          err_code;
    uint8_t           default_protocol_mode;
    ble_gatts_value_t gatts_value;

    p_hids->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;

    if (p_hids->protocol_mode_handles.value_handle)
    {
        // Set Protocol Mode characteristic value to default value
        default_protocol_mode = DEFAULT_PROTOCOL_MODE;

        // Initialize value struct.
        memset(&gatts_value, 0, sizeof(gatts_value));

        gatts_value.len     = sizeof(uint8_t);
        gatts_value.offset  = 0;
        gatts_value.p_value = &default_protocol_mode;

        err_code = sd_ble_gatts_value_set(p_hids->conn_handle,
                                          p_hids->protocol_mode_handles.value_handle,
                                          &gatts_value);
        if ((err_code != NRF_SUCCESS) && (p_hids->error_handler != NULL))
        {
            p_hids->error_handler(err_code);
        }
    }
}


/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_hids      HID Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_hids_t * p_hids, ble_evt_t * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_hids->conn_handle = BLE_CONN_HANDLE_INVALID;
}


/**@brief Function for handling write events to the HID Control Point value.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_evt_write   Write event received from the BLE stack.
 */
static void on_control_point_write(ble_hids_t * p_hids, ble_gatts_evt_write_t * p_evt_write)
{
    if ((p_evt_write->len == 1) && (p_hids->evt_handler != NULL))
    {
        ble_hids_evt_t evt;

        // HID Control Point written, propagate event to application
        switch (p_evt_write->data[0])
        {
            case HIDS_CONTROL_POINT_SUSPEND:
                evt.evt_type = BLE_HIDS_EVT_HOST_SUSP;
                break;

            case HIDS_CONTROL_POINT_EXIT_SUSPEND:
                evt.evt_type = BLE_HIDS_EVT_HOST_EXIT_SUSP;
                break;

            default:
                // Illegal Control Point value, ignore
                return;
        }

        p_hids->evt_handler(p_hids, &evt);
    }
}


/**@brief Function for handling write events to the Protocol Mode value.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_evt_write   Write event received from the BLE stack.
 */
static void on_protocol_mode_write(ble_hids_t * p_hids, ble_gatts_evt_write_t * p_evt_write)
{
    if ((p_evt_write->len == 1) && (p_hids->evt_handler != NULL))
    {
        ble_hids_evt_t evt;

        // HID Protocol Mode written, propagate event to application
        switch (p_evt_write->data[0])
        {
            case PROTOCOL_MODE_BOOT:
                evt.evt_type = BLE_HIDS_EVT_BOOT_MODE_ENTERED;
                break;

            case PROTOCOL_MODE_REPORT:
                evt.evt_type = BLE_HIDS_EVT_REPORT_MODE_ENTERED;
                break;

            default:
                // Illegal Protocol Mode value, ignore
                return;
        }

        p_hids->evt_handler(p_hids, &evt);
    }
}


/**@brief Function for handling write events to a report CCCD.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_char_id     Id of report characteristic.
 * @param[in]   p_evt_write   Write event received from the BLE stack.
 */
static void on_report_cccd_write(ble_hids_t            * p_hids,
                                 ble_hids_char_id_t    * p_char_id,
                                 ble_gatts_evt_write_t * p_evt_write)
{
    if (p_evt_write->len == 2)
    {
        // CCCD written, update notification state
        if (p_hids->evt_handler != NULL)
        {
            ble_hids_evt_t evt;

            if (ble_srv_is_notification_enabled(p_evt_write->data))
            {
                evt.evt_type = BLE_HIDS_EVT_NOTIF_ENABLED;
            }
            else
            {
                evt.evt_type = BLE_HIDS_EVT_NOTIF_DISABLED;
            }
            evt.params.notification.char_id = *p_char_id;

            p_hids->evt_handler(p_hids, &evt);
        }
    }
}


/**@brief Function for handling write events to a report value.
 *
 * @param[in]   p_hids      HID Service structure.
 * @param[in]   p_char_id   Id of report characteristic.
 */
static void on_report_value_write(ble_hids_t         * p_hids,
                                  ble_evt_t          * p_ble_evt,
                                  ble_hids_char_id_t * p_char_id)
{
    if (p_hids->evt_handler != NULL)
    {
        ble_hids_evt_t evt;

        evt.evt_type                  = BLE_HIDS_EVT_REP_CHAR_WRITE;
        evt.params.char_write.char_id = *p_char_id;
        evt.params.char_write.offset  = p_ble_evt->evt.gatts_evt.params.write.offset;
        evt.params.char_write.len     = p_ble_evt->evt.gatts_evt.params.write.len;
        evt.params.char_write.data    = p_ble_evt->evt.gatts_evt.params.write.data;

        p_hids->evt_handler(p_hids, &evt);
    }
}

/**@brief Handle authorize read events to a report value.
 *
 * @param[in]   p_hids      HID Service structure.
 * @param[in]   p_char_id   Id of report characteristic.
 */
static void on_report_value_read_auth(ble_hids_t         * p_hids,
                                      ble_hids_char_id_t * p_char_id,
                                      ble_evt_t          * p_ble_evt)
{
    if (p_hids->evt_handler != NULL)
    {
        ble_hids_evt_t evt;

        evt.evt_type                      = BLE_HIDS_EVT_REPORT_READ;
        evt.params.char_auth_read.char_id = *p_char_id;
        evt.p_ble_evt                     = p_ble_evt;

        p_hids->evt_handler(p_hids, &evt);
    }
}

/**@brief Function for finding the Characteristic Id of a characteristic corresponding to a CCCD handle.
 *
 * @param[in]   p_hids      HID Service structure.
 * @param[in]   handle      Handle to search for.
 * @param[out]  p_char_id   Id of report characteristic.
 *
 * @return      TRUE if CCCD handle was found, FALSE otherwise.
 */
static bool inp_rep_cccd_identify(ble_hids_t         * p_hids,
                                  uint16_t             handle,
                                  ble_hids_char_id_t * p_char_id)
{
    uint8_t i;

    for (i = 0; i < p_hids->inp_rep_count; i++)
    {
        if (handle == p_hids->inp_rep_array[i].char_handles.cccd_handle)
        {
            *p_char_id = make_char_id(BLE_UUID_REPORT_CHAR, BLE_HIDS_REP_TYPE_INPUT, i);
            return true;
        }
    }

    return false;
}


/**@brief Function for finding the Characteristic Id of a characteristic corresponding to a value handle.
 *
 * @param[in]   p_hids      HID Service structure.
 * @param[in]   handle      Handle to search for.
 * @param[out]  p_char_id   Id of report characteristic.
 *
 * @return      TRUE if value handle was found, FALSE otherwise.
 */
static bool rep_value_identify(ble_hids_t         * p_hids,
                               uint16_t             handle,
                               ble_hids_char_id_t * p_char_id)
{
    uint8_t i;

    for (i = 0; i < p_hids->inp_rep_count; i++)
    {
        if (handle == p_hids->inp_rep_array[i].char_handles.value_handle)
        {
            *p_char_id = make_char_id(BLE_UUID_REPORT_CHAR, BLE_HIDS_REP_TYPE_INPUT, i);
            return true;
        }
    }

    for (i = 0; i < p_hids->outp_rep_count; i++)
    {
        if (handle == p_hids->outp_rep_array[i].char_handles.value_handle)
        {
            *p_char_id = make_char_id(BLE_UUID_REPORT_CHAR, BLE_HIDS_REP_TYPE_OUTPUT, i);
            return true;
        }
    }

    for (i = 0; i < p_hids->feature_rep_count; i++)
    {
        if (handle == p_hids->feature_rep_array[i].char_handles.value_handle)
        {
            *p_char_id = make_char_id(BLE_UUID_REPORT_CHAR, BLE_HIDS_REP_TYPE_FEATURE, i);
            return true;
        }
    }

    return false;
}


/**@brief Function for handling the Write event.
 *
 * @param[in]   p_hids      HID Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_hids_t * p_hids, ble_evt_t * p_ble_evt)
{
    ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    ble_hids_char_id_t      char_id;

    if (p_evt_write->handle == p_hids->hid_control_point_handles.value_handle)
    {
        on_control_point_write(p_hids, p_evt_write);
    }
    else if (p_evt_write->handle == p_hids->protocol_mode_handles.value_handle)
    {
        on_protocol_mode_write(p_hids, p_evt_write);
    }
    else if (p_evt_write->handle == p_hids->boot_kb_inp_rep_handles.cccd_handle)
    {
        char_id = make_char_id(BLE_UUID_BOOT_KEYBOARD_INPUT_REPORT_CHAR, 0, 0);
        on_report_cccd_write(p_hids, &char_id, p_evt_write);
    }
    else if (p_evt_write->handle == p_hids->boot_kb_inp_rep_handles.value_handle)
    {
        char_id = make_char_id(BLE_UUID_BOOT_KEYBOARD_INPUT_REPORT_CHAR, 0, 0);
        on_report_value_write(p_hids, p_ble_evt, &char_id);
    }
    else if (p_evt_write->handle == p_hids->boot_mouse_inp_rep_handles.cccd_handle)
    {
        char_id = make_char_id(BLE_UUID_BOOT_MOUSE_INPUT_REPORT_CHAR, 0, 0);
        on_report_cccd_write(p_hids, &char_id, p_evt_write);
    }
    else if (p_evt_write->handle == p_hids->boot_mouse_inp_rep_handles.value_handle)
    {
        char_id = make_char_id(BLE_UUID_BOOT_MOUSE_INPUT_REPORT_CHAR, 0, 0);
        on_report_value_write(p_hids, p_ble_evt, &char_id);
    }
    else if (inp_rep_cccd_identify(p_hids, p_evt_write->handle, &char_id))
    {
        on_report_cccd_write(p_hids, &char_id, p_evt_write);
    }
    else if (rep_value_identify(p_hids, p_evt_write->handle, &char_id))
    {
        on_report_value_write(p_hids, p_ble_evt, &char_id);
    }
    else
    {
        // No implementation needed.
    }
}

/**@brief Read/write authorize request event handler.
 *
 * @param[in]   p_hids      HID Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_rw_authorize_request(ble_hids_t * p_hids, ble_evt_t * p_ble_evt)
{
    ble_gatts_evt_rw_authorize_request_t * evt_rw_auth = &p_ble_evt->evt.gatts_evt.params.authorize_request;
    ble_hids_char_id_t                     char_id;

    if (evt_rw_auth->type != BLE_GATTS_AUTHORIZE_TYPE_READ)
    {
        // Unexpected operation
        return;
    }

    if (rep_value_identify(p_hids, evt_rw_auth->request.read.handle, &char_id))
    {
        on_report_value_read_auth(p_hids, &char_id, p_ble_evt);
    }
}

void ble_hids_on_ble_evt(ble_hids_t * p_hids, ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_hids, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_hids, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_hids, p_ble_evt);
            break;

        case BLE_GATTS_EVT_RW_AUTHORIZE_REQUEST:
            on_rw_authorize_request(p_hids, p_ble_evt);
            break;
        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for adding Protocol Mode characteristics.
 *
 * @param[in]   p_hids       HID Service structure.
 * @param[in]   p_sec_mode   Characteristic security settings.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t protocol_mode_char_add(ble_hids_t                    * p_hids,
                                       const ble_srv_security_mode_t * p_sec_mode)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    uint8_t             initial_protocol_mode;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read          = 1;
    char_md.char_props.write_wo_resp = 1;
    char_md.p_char_user_desc         = NULL;
    char_md.p_char_pf                = NULL;
    char_md.p_user_desc_md           = NULL;
    char_md.p_cccd_md                = NULL;
    char_md.p_sccd_md                = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_PROTOCOL_MODE_CHAR);

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_sec_mode->read_perm;
    attr_md.write_perm = p_sec_mode->write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    initial_protocol_mode = DEFAULT_PROTOCOL_MODE;

    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = sizeof(uint8_t);
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = sizeof(uint8_t);
    attr_char_value.p_value      = &initial_protocol_mode;

    return sd_ble_gatts_characteristic_add(p_hids->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           &p_hids->protocol_mode_handles);
}


/**@brief Function for adding report characteristics.
 *
 * @param[in]   p_hids              HID Service structure.
 * @param[in]   p_properties        Report characteristic properties.
 * @param[in]   max_len             Maximum length of report value.
 * @param[in]   p_rep_ref           Report Reference descriptor.
 * @param[in]   p_rep_ref_attr_md   Characteristic security settings.
 * @param[in]   is_read_resp        Characteristic read authorization.
 * @param[out]  p_rep_char          Handles of new characteristic.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t rep_char_add(ble_hids_t *                   p_hids,
                             ble_gatt_char_props_t *        p_properties,
                             uint16_t                       max_len,
                             ble_srv_report_ref_t *         p_rep_ref,
                             ble_srv_cccd_security_mode_t * p_rep_ref_attr_md,
                             bool                           is_read_resp,
                             ble_hids_rep_char_t *          p_rep_char)
{
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    uint8_t             encoded_rep_ref[BLE_SRV_ENCODED_REPORT_REF_LEN];

    // Add Report characteristic
    if (p_properties->notify)
    {
        memset(&cccd_md, 0, sizeof(cccd_md));
        BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
        cccd_md.write_perm = p_rep_ref_attr_md->cccd_write_perm;
        cccd_md.vloc = BLE_GATTS_VLOC_STACK;
    }

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props       = *p_properties;
    char_md.p_char_user_desc = NULL;
    char_md.p_char_pf        = NULL;
    char_md.p_user_desc_md   = NULL;
    char_md.p_cccd_md        = (p_properties->notify) ? &cccd_md : NULL;
    char_md.p_sccd_md        = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_REPORT_CHAR);

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_rep_ref_attr_md->read_perm;
    attr_md.write_perm = p_rep_ref_attr_md->write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = is_read_resp ? 1 : 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 1;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = 0;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = max_len;
    attr_char_value.p_value   = NULL;

    err_code = sd_ble_gatts_characteristic_add(p_hids->service_handle,
                                               &char_md,
                                               &attr_char_value,
                                               &p_rep_char->char_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add Report Reference descriptor
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_REPORT_REF_DESCR);

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_rep_ref_attr_md->read_perm;
    attr_md.write_perm = p_rep_ref_attr_md->write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = ble_srv_report_ref_encode(encoded_rep_ref, p_rep_ref);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = attr_char_value.init_len;
    attr_char_value.p_value   = encoded_rep_ref;

    return sd_ble_gatts_descriptor_add(p_rep_char->char_handles.value_handle,
                                       &attr_char_value,
                                       &p_rep_char->ref_handle);
}


/**@brief Function for adding Report Map characteristics.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_hids_init   Service initialization structure.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t rep_map_char_add(ble_hids_t * p_hids, const ble_hids_init_t * p_hids_init)
{
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    // Add Report Map characteristic
    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read  = 1;
    char_md.p_char_user_desc = NULL;
    char_md.p_char_pf        = NULL;
    char_md.p_user_desc_md   = NULL;
    char_md.p_cccd_md        = NULL;
    char_md.p_sccd_md        = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_REPORT_MAP_CHAR);

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_hids_init->rep_map.security_mode.read_perm;
    attr_md.write_perm = p_hids_init->rep_map.security_mode.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 1;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = p_hids_init->rep_map.data_len;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = p_hids_init->rep_map.data_len;
    attr_char_value.p_value   = p_hids_init->rep_map.p_data;

    err_code = sd_ble_gatts_characteristic_add(p_hids->service_handle,
                                               &char_md,
                                               &attr_char_value,
                                               &p_hids->rep_map_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    if (p_hids_init->rep_map.ext_rep_ref_num != 0 && p_hids_init->rep_map.p_ext_rep_ref == NULL)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    for (int i = 0; i < p_hids_init->rep_map.ext_rep_ref_num; ++i)
    {
        uint8_t encoded_rep_ref[sizeof(ble_uuid128_t)];
        uint8_t encoded_rep_ref_len;

        // Add External Report Reference descriptor
        BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_EXTERNAL_REPORT_REF_DESCR);

        memset(&attr_md, 0, sizeof(attr_md));

        BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&attr_md.read_perm);
        BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);

        attr_md.vloc    = BLE_GATTS_VLOC_STACK;
        attr_md.rd_auth = 0;
        attr_md.wr_auth = 0;
        attr_md.vlen    = 0;

        err_code = sd_ble_uuid_encode(&p_hids_init->rep_map.p_ext_rep_ref[i],
                                      &encoded_rep_ref_len,
                                      encoded_rep_ref);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        memset(&attr_char_value, 0, sizeof(attr_char_value));

        attr_char_value.p_uuid    = &ble_uuid;
        attr_char_value.p_attr_md = &attr_md;
        attr_char_value.init_len  = encoded_rep_ref_len;
        attr_char_value.init_offs = 0;
        attr_char_value.max_len   = attr_char_value.init_len;
        attr_char_value.p_value   = encoded_rep_ref;

        err_code = sd_ble_gatts_descriptor_add(p_hids->rep_map_handles.value_handle,
                                               &attr_char_value,
                                               &p_hids->rep_map_ext_rep_ref_handle);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    return NRF_SUCCESS;
}


/**@brief Function for adding Input Report characteristics.
 *
 * @param[in]   p_hids           HID Service structure.
 * @param[in]   uuid             UUID of report characteristic to be added.
 * @param[in]   max_data_len     Maximum length of report value.
 * @param[in]   p_sec_mode       Characteristic security settings.
 * @param[out]  p_char_handles   Handles of new characteristic.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t boot_inp_rep_char_add(ble_hids_t                         * p_hids,
                                      uint16_t                             uuid,
                                      uint16_t                             max_data_len,
                                      const ble_srv_cccd_security_mode_t * p_sec_mode,
                                      ble_gatts_char_handles_t           * p_char_handles)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&cccd_md, 0, sizeof(cccd_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    cccd_md.write_perm = p_sec_mode->cccd_write_perm;
    cccd_md.vloc       = BLE_GATTS_VLOC_STACK;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read   = 1;
    char_md.char_props.write  = (p_sec_mode->write_perm.sm) ? 1 : 0;
    char_md.char_props.notify = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = &cccd_md;
    char_md.p_sccd_md         = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, uuid);

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_sec_mode->read_perm;
    attr_md.write_perm = p_sec_mode->write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = 0;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = max_data_len;
    attr_char_value.p_value   = NULL;

    return sd_ble_gatts_characteristic_add(p_hids->service_handle,
                                           &char_md,
                                           &attr_char_value,
                                           p_char_handles);
}


/**@brief Function for adding Boot Keyboard Output Report characteristics.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_hids_init   Service initialization structure.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t boot_kb_outp_rep_char_add(ble_hids_t * p_hids, const ble_hids_init_t * p_hids_init)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read          = 1;
    char_md.char_props.write         = 1;
    char_md.char_props.write_wo_resp = 1;
    char_md.p_char_user_desc         = NULL;
    char_md.p_char_pf                = NULL;
    char_md.p_user_desc_md           = NULL;
    char_md.p_cccd_md                = NULL;
    char_md.p_sccd_md                = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_BOOT_KEYBOARD_OUTPUT_REPORT_CHAR);

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_hids_init->security_mode_boot_kb_outp_rep.read_perm;
    attr_md.write_perm = p_hids_init->security_mode_boot_kb_outp_rep.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = 0;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = BOOT_KB_OUTPUT_REPORT_MAX_SIZE;
    attr_char_value.p_value   = NULL;

    return sd_ble_gatts_characteristic_add(p_hids->service_handle, &char_md, &attr_char_value,
                                           &p_hids->boot_kb_outp_rep_handles);
}


/**@brief Function for encoding a HID Information characteristic value.
 *
 * @param[out]  p_encoded_buffer    Buffer where the encoded data will be written.
 * @param[in]   p_hid_information   Measurement to be encoded.
 *
 * @return      Size of encoded data.
 */
static uint8_t encode_hid_information(uint8_t                          * p_encoded_buffer,
                                      const ble_hids_hid_information_t * p_hid_information)
{
    uint8_t len = uint16_encode(p_hid_information->bcd_hid, p_encoded_buffer);

    p_encoded_buffer[len++] = p_hid_information->b_country_code;
    p_encoded_buffer[len++] = p_hid_information->flags;

    APP_ERROR_CHECK_BOOL(len == ENCODED_HID_INFORMATION_LEN);

    return len;
}


/**@brief Function for adding HID Information characteristics.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_hids_init   Service initialization structure.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t hid_information_char_add(ble_hids_t * p_hids, const ble_hids_init_t * p_hids_init)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    uint8_t             encoded_hid_information[ENCODED_HID_INFORMATION_LEN];
    uint8_t             hid_info_len;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read  = 1;
    char_md.p_char_user_desc = NULL;
    char_md.p_char_pf        = NULL;
    char_md.p_user_desc_md   = NULL;
    char_md.p_cccd_md        = NULL;
    char_md.p_sccd_md        = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_HID_INFORMATION_CHAR);

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_hids_init->hid_information.security_mode.read_perm;
    attr_md.write_perm = p_hids_init->hid_information.security_mode.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    hid_info_len = encode_hid_information(encoded_hid_information, &p_hids_init->hid_information);

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = hid_info_len;
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = attr_char_value.init_len;
    attr_char_value.p_value   = encoded_hid_information;

    return sd_ble_gatts_characteristic_add(p_hids->service_handle, &char_md,
                                           &attr_char_value,
                                           &p_hids->hid_information_handles);
}


/**@brief Function for adding HID Control Point characteristics.
 *
 * @param[in]   p_hids       HID Service structure.
 * @param[in]   p_sec_mode   Characteristic security settings.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t hid_control_point_char_add(ble_hids_t                    * p_hids,
                                           const ble_srv_security_mode_t * p_sec_mode)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;
    uint8_t             initial_hid_control_point;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.write_wo_resp = 1;
    char_md.p_char_user_desc         = NULL;
    char_md.p_char_pf                = NULL;
    char_md.p_user_desc_md           = NULL;
    char_md.p_cccd_md                = NULL;
    char_md.p_sccd_md                = NULL;

    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_HID_CONTROL_POINT_CHAR);

    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_sec_mode->read_perm;
    attr_md.write_perm = p_sec_mode->write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    initial_hid_control_point = INITIAL_VALUE_HID_CONTROL_POINT;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(uint8_t);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(uint8_t);
    attr_char_value.p_value   = &initial_hid_control_point;

    return sd_ble_gatts_characteristic_add(p_hids->service_handle, &char_md,
                                           &attr_char_value,
                                           &p_hids->hid_control_point_handles);
}


/**@brief Function for adding input report characteristics.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_hids_init   Service initialization structure.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t inp_rep_characteristics_add(ble_hids_t            * p_hids,
                                            const ble_hids_init_t * p_hids_init)
{
    if ((p_hids_init->inp_rep_count != 0) && (p_hids_init->p_inp_rep_array != NULL))
    {
        uint8_t i;

        for (i = 0; i < p_hids_init->inp_rep_count; i++)
        {
            uint32_t                  err_code;
            ble_hids_inp_rep_init_t * p_rep_init = &p_hids_init->p_inp_rep_array[i];
            ble_gatt_char_props_t     properties;

            memset(&properties, 0, sizeof(properties));

            properties.read   = true;
            properties.write  = p_rep_init->security_mode.write_perm.sm ? 1 : 0;
            properties.notify = true;

            err_code = rep_char_add(p_hids,
                                    &properties,
                                    p_rep_init->max_len,
                                    &p_rep_init->rep_ref,
                                    &p_rep_init->security_mode,
                                    p_rep_init->read_resp,
                                    &p_hids->inp_rep_array[i]);
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }
        }
    }

    return NRF_SUCCESS;
}


/**@brief Function for adding output report characteristics.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_hids_init   Service initialization structure.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t outp_rep_characteristics_add(ble_hids_t            * p_hids,
                                             const ble_hids_init_t * p_hids_init)
{
    if ((p_hids_init->outp_rep_count != 0) && (p_hids_init->p_outp_rep_array != NULL))
    {
        uint8_t i;

        for (i = 0; i < p_hids_init->outp_rep_count; i++)
        {
            uint32_t                   err_code;
            ble_hids_outp_rep_init_t * p_rep_init = &p_hids_init->p_outp_rep_array[i];
            ble_gatt_char_props_t      properties;

            memset(&properties, 0, sizeof(properties));

            properties.read          = true;
            properties.write         = true;
            properties.write_wo_resp = true;

            err_code = rep_char_add(p_hids,
                                    &properties,
                                    p_rep_init->max_len,
                                    &p_rep_init->rep_ref,
                                    &p_rep_init->security_mode,
                                    p_rep_init->read_resp,
                                    &p_hids->outp_rep_array[i]);
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }
        }
    }

    return NRF_SUCCESS;
}


/**@brief Function for adding feature report characteristics.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_hids_init   Service initialization structure.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t feature_rep_characteristics_add(ble_hids_t            * p_hids,
                                                const ble_hids_init_t * p_hids_init)
{
    if ((p_hids_init->feature_rep_count != 0) && (p_hids_init->p_feature_rep_array != NULL))
    {
        uint8_t i;

        for (i = 0; i < p_hids_init->feature_rep_count; i++)
        {
            uint32_t                      err_code;
            ble_hids_feature_rep_init_t * p_rep_init = &p_hids_init->p_feature_rep_array[i];
            ble_gatt_char_props_t         properties;

            memset(&properties, 0, sizeof(properties));

            properties.read  = true;
            properties.write = true;

            err_code = rep_char_add(p_hids,
                                    &properties,
                                    p_rep_init->max_len,
                                    &p_rep_init->rep_ref,
                                    &p_rep_init->security_mode,
                                    p_rep_init->read_resp,
                                    &p_hids->feature_rep_array[i]);
            if (err_code != NRF_SUCCESS)
            {
                return err_code;
            }
        }
    }

    return NRF_SUCCESS;
}


/**@brief Function for adding included services.
 *
 * @param[in]   p_hids        HID Service structure.
 * @param[in]   p_hids_init   Service initialization structure.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t includes_add(ble_hids_t * p_hids, const ble_hids_init_t * p_hids_init)
{
    uint32_t err_code;
    uint8_t  i;
    uint16_t unused_include_handle;

    for (i = 0; i < p_hids_init->included_services_count; i++)
    {
        err_code = sd_ble_gatts_include_add(p_hids->service_handle,
                                            p_hids_init->p_included_services_array[i],
                                            &unused_include_handle);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    return NRF_SUCCESS;
}


uint32_t ble_hids_init(ble_hids_t * p_hids, const ble_hids_init_t * p_hids_init)
{
    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    if ((p_hids_init->inp_rep_count > BLE_HIDS_MAX_INPUT_REP) ||
        (p_hids_init->outp_rep_count > BLE_HIDS_MAX_OUTPUT_REP) ||
        (p_hids_init->feature_rep_count > BLE_HIDS_MAX_FEATURE_REP)
       )
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    // Initialize service structure.
    p_hids->evt_handler       = p_hids_init->evt_handler;
    p_hids->error_handler     = p_hids_init->error_handler;
    p_hids->inp_rep_count     = p_hids_init->inp_rep_count;
    p_hids->outp_rep_count    = p_hids_init->outp_rep_count;
    p_hids->feature_rep_count = p_hids_init->feature_rep_count;
    p_hids->conn_handle       = BLE_CONN_HANDLE_INVALID;

    // Add service.
    BLE_UUID_BLE_ASSIGN(ble_uuid, BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE);

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &ble_uuid,
                                        &p_hids->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add includes.
    err_code = includes_add(p_hids, p_hids_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    if (p_hids_init->is_kb || p_hids_init->is_mouse)
    {
        // Add Protocol Mode characteristic.
        err_code = protocol_mode_char_add(p_hids, &p_hids_init->security_mode_protocol);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    // Add Input Report characteristics (if any).
    err_code = inp_rep_characteristics_add(p_hids, p_hids_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add Output Report characteristics (if any).
    err_code = outp_rep_characteristics_add(p_hids, p_hids_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add Feature Report characteristic (if any).
    err_code = feature_rep_characteristics_add(p_hids, p_hids_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add Report Map characteristic.
    err_code = rep_map_char_add(p_hids, p_hids_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    if (p_hids_init->is_kb)
    {
        // Add Boot Keyboard Input Report characteristic.
        err_code = boot_inp_rep_char_add(p_hids,
                                         BLE_UUID_BOOT_KEYBOARD_INPUT_REPORT_CHAR,
                                         BOOT_KB_INPUT_REPORT_MAX_SIZE,
                                         &p_hids_init->security_mode_boot_kb_inp_rep,
                                         &p_hids->boot_kb_inp_rep_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }

        // Add Boot Keyboard Output Report characteristic.
        err_code = boot_kb_outp_rep_char_add(p_hids, p_hids_init);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    if (p_hids_init->is_mouse)
    {
        // Add Boot Mouse Input Report characteristic.
        err_code = boot_inp_rep_char_add(p_hids,
                                         BLE_UUID_BOOT_MOUSE_INPUT_REPORT_CHAR,
                                         BOOT_MOUSE_INPUT_REPORT_MAX_SIZE,
                                         &p_hids_init->security_mode_boot_mouse_inp_rep,
                                         &p_hids->boot_mouse_inp_rep_handles);
        if (err_code != NRF_SUCCESS)
        {
            return err_code;
        }
    }

    // Add HID Information characteristic.
    err_code = hid_information_char_add(p_hids, p_hids_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add HID Control Point characteristic.
    err_code = hid_control_point_char_add(p_hids, &p_hids_init->security_mode_ctrl_point);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}


uint32_t ble_hids_inp_rep_send(ble_hids_t * p_hids,
                               uint8_t      rep_index,
                               uint16_t     len,
                               uint8_t    * p_data)
{
    uint32_t err_code;

    if (rep_index < p_hids->inp_rep_count)
    {
        ble_hids_rep_char_t * p_rep_char = &p_hids->inp_rep_array[rep_index];

        if (p_hids->conn_handle != BLE_CONN_HANDLE_INVALID)
        {
            ble_gatts_hvx_params_t hvx_params;
            uint16_t               hvx_len = len;

            memset(&hvx_params, 0, sizeof(hvx_params));

            hvx_params.handle = p_rep_char->char_handles.value_handle;
            hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
            hvx_params.offset = 0;
            hvx_params.p_len  = &hvx_len;
            hvx_params.p_data = p_data;

            err_code = sd_ble_gatts_hvx(p_hids->conn_handle, &hvx_params);
            if ((err_code == NRF_SUCCESS) && (hvx_len != len))
            {
                err_code = NRF_ERROR_DATA_SIZE;
            }
        }
        else
        {
            err_code = NRF_ERROR_INVALID_STATE;
        }
    }
    else
    {
        err_code = NRF_ERROR_INVALID_PARAM;
    }

    return err_code;
}


uint32_t ble_hids_boot_kb_inp_rep_send(ble_hids_t * p_hids, uint16_t len, uint8_t * p_data)
{
    uint32_t err_code;

    if (p_hids->conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        ble_gatts_hvx_params_t hvx_params;
        uint16_t               hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_hids->boot_kb_inp_rep_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &hvx_len;
        hvx_params.p_data = p_data;

        err_code = sd_ble_gatts_hvx(p_hids->conn_handle, &hvx_params);
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}


uint32_t ble_hids_boot_mouse_inp_rep_send(ble_hids_t * p_hids,
                                          uint8_t      buttons,
                                          int8_t       x_delta,
                                          int8_t       y_delta,
                                          uint16_t     optional_data_len,
                                          uint8_t    * p_optional_data)
{
    uint32_t err_code;

    if (p_hids->conn_handle != BLE_CONN_HANDLE_INVALID)
    {
        uint16_t hvx_len = BOOT_MOUSE_INPUT_REPORT_MIN_SIZE + optional_data_len;

        if (hvx_len <= BOOT_MOUSE_INPUT_REPORT_MAX_SIZE)
        {
            uint8_t                buffer[BOOT_MOUSE_INPUT_REPORT_MAX_SIZE];
            ble_gatts_hvx_params_t hvx_params;

            APP_ERROR_CHECK_BOOL(BOOT_MOUSE_INPUT_REPORT_MIN_SIZE == 3);

            // Build buffer
            buffer[0] = buttons;
            buffer[1] = (uint8_t)x_delta;
            buffer[2] = (uint8_t)y_delta;

            if (optional_data_len > 0)
            {
                memcpy(&buffer[3], p_optional_data, optional_data_len);
            }

            // Pass buffer to stack
            memset(&hvx_params, 0, sizeof(hvx_params));

            hvx_params.handle = p_hids->boot_mouse_inp_rep_handles.value_handle;
            hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
            hvx_params.offset = 0;
            hvx_params.p_len  = &hvx_len;
            hvx_params.p_data = buffer;

            err_code = sd_ble_gatts_hvx(p_hids->conn_handle, &hvx_params);
            if ((err_code == NRF_SUCCESS) &&
                (hvx_len != BOOT_MOUSE_INPUT_REPORT_MIN_SIZE + optional_data_len)
               )
            {
                err_code = NRF_ERROR_DATA_SIZE;
            }
        }
        else
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}


uint32_t ble_hids_outp_rep_get(ble_hids_t * p_hids,
                               uint8_t      rep_index,
                               uint16_t     len,
                               uint8_t      offset,
                               uint8_t    * p_outp_rep)
{
    ble_gatts_value_t gatts_value;

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = len;
    gatts_value.offset  = offset;
    gatts_value.p_value = p_outp_rep;

    return sd_ble_gatts_value_get(p_hids->conn_handle,
                                  p_hids->outp_rep_array[rep_index].char_handles.value_handle,
                                  &gatts_value);
}

/**
  @}
*/
#endif // NRF_MODULE_ENABLED(BLE_HIDS)
