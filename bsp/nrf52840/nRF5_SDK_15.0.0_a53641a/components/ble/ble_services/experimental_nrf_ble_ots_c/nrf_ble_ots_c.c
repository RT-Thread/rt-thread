/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_OTS_C)
#include <stdlib.h>
#include "nrf_ble_ots_c.h"
#include "nrf_ble_ots_c_oacp.h"
#include "nrf_ble_ots_c_l2cap.h"
#include "ble.h"

#define NRF_LOG_MODULE_NAME ble_ots_c
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#include "sdk_common.h"


#define BLE_OTS_OACP_SUPPORT_FEATURE_CREATE_bp          0
#define BLE_OTS_OACP_SUPPORT_FEATURE_DELETE_bp          1
#define BLE_OTS_OACP_SUPPORT_FEATURE_CALC_CHECKSUM_bp   2
#define BLE_OTS_OACP_SUPPORT_FEATURE_EXECUTE_bp         3
#define BLE_OTS_OACP_SUPPORT_FEATURE_READ_bp            4
#define BLE_OTS_OACP_SUPPORT_FEATURE_WRITE_bp           5
#define BLE_OTS_OACP_SUPPORT_FEATURE_APPEND_bp          6
#define BLE_OTS_OACP_SUPPORT_FEATURE_TRUNCATE_bp        7
#define BLE_OTS_OACP_SUPPORT_FEATURE_PATCH_bp           8
#define BLE_OTS_OACP_SUPPORT_FEATURE_ABORT_bp           9

#define BLE_OTS_OLCP_SUPPORT_FEATURE_GOTO_bp            0
#define BLE_OTS_OLCP_SUPPORT_FEATURE_ORDER_bp           1
#define BLE_OTS_OLCP_SUPPORT_FEATURE_REQ_NUM_OBJECTS_bp 2
#define BLE_OTS_OLCP_SUPPORT_FEATURE_CLEAR_MARKING_bp   3

#define MODULE_INITIALIZED (p_ots_c->initialized)   /**< Macro designating whether the module has been initialized properly. */

static const ble_uuid_t m_ots_uuid = {BLE_UUID_OTS_SERVICE, BLE_UUID_TYPE_BLE};  /**< Object Transfer Service UUID. */


ret_code_t nrf_ble_ots_c_init(nrf_ble_ots_c_t      * p_ots_c,
                              nrf_ble_ots_c_init_t * p_ots_c_init)
{
    ret_code_t err_code = NRF_SUCCESS;
    VERIFY_PARAM_NOT_NULL(p_ots_c);
    VERIFY_PARAM_NOT_NULL(p_ots_c_init);
    VERIFY_PARAM_NOT_NULL(p_ots_c_init->evt_handler);
    memset (p_ots_c, 0, sizeof(nrf_ble_ots_c_t));

    p_ots_c->conn_handle = BLE_CONN_HANDLE_INVALID;
    p_ots_c->evt_handler = p_ots_c_init->evt_handler;

    err_code = ble_db_discovery_evt_register(&m_ots_uuid);
    VERIFY_SUCCESS(err_code);

    p_ots_c->initialized = true;
    return err_code;
}


/**@brief Function for checking whether the peer's Object Transfer Service instance has been discovered.

   @param[in] p_ots_c Pointer to the GATT Service client structure instance.

   @return True if the Object Transfer service handles are valid.
   @return False if the Object Transfer service handles are invalid
 */
static bool ots_gatt_handles_are_valid(const nrf_ble_ots_c_t * const p_ots_c)
{
    return   (p_ots_c->service.object_prop_char.handle_value != BLE_GATT_HANDLE_INVALID
           && p_ots_c->service.object_size_char.handle_value != BLE_GATT_HANDLE_INVALID
           && p_ots_c->service.object_type_char.handle_value != BLE_GATT_HANDLE_INVALID
           && p_ots_c->service.ots_feature_char.handle_value != BLE_GATT_HANDLE_INVALID);
}


ret_code_t nrf_ble_ots_c_feature_read(nrf_ble_ots_c_t * const p_ots_c)
{
    VERIFY_MODULE_INITIALIZED();

    ret_code_t err_code;
    err_code = sd_ble_gattc_read(p_ots_c->conn_handle,
                                 p_ots_c->service.ots_feature_char.handle_value,
                                 0);
    return err_code;
}


ret_code_t nrf_ble_ots_c_obj_size_read(nrf_ble_ots_c_t * const p_ots_c)
{
    VERIFY_MODULE_INITIALIZED();
    
    if( p_ots_c->service.object_size_char.handle_value == BLE_GATT_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }
    ret_code_t err_code;
    err_code = sd_ble_gattc_read(p_ots_c->conn_handle,
                                 p_ots_c->service.object_size_char.handle_value,
                                 0);
    return err_code;
}

/**@brief     Function for handling read response events.
 *
 * @details   This function will validate the read response and raise the appropriate
 *            event to the application.
 *
 * @param[in] p_bas_c   Pointer to the Battery Service Client Structure.
 * @param[in] p_ble_evt Pointer to the SoftDevice event.
 */
static void on_read_rsp(nrf_ble_ots_c_t * p_ots_c, const ble_evt_t * p_ble_evt)
{
    const ble_gattc_evt_read_rsp_t * p_response;

    // Check if the event is on the link for this instance
    if (p_ots_c->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle)
    {
        return;
    }

    p_response = &p_ble_evt->evt.gattc_evt.params.read_rsp;

    if (p_response->handle == p_ots_c->service.ots_feature_char.handle_value)
    {
        nrf_ble_ots_c_evt_t evt;

        evt.conn_handle = p_ble_evt->evt.gattc_evt.conn_handle;
        evt.evt_type    = NRF_BLE_OTS_C_EVT_FEATURE_READ_RESP;

        uint32_t oacp_features;
        oacp_features = uint32_decode(&p_response->data[0]);
        evt.params.feature.oacp_create   = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_CREATE_bp;
        evt.params.feature.oacp_delete   = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_DELETE_bp;
        evt.params.feature.oacp_crc      = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_CALC_CHECKSUM_bp;
        evt.params.feature.oacp_execute  = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_EXECUTE_bp;
        evt.params.feature.oacp_read     = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_READ_bp;
        evt.params.feature.oacp_write    = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_WRITE_bp;
        evt.params.feature.oacp_append   = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_APPEND_bp;
        evt.params.feature.oacp_truncate = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_TRUNCATE_bp;
        evt.params.feature.oacp_patch    = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_PATCH_bp;
        evt.params.feature.oacp_abort    = oacp_features >> BLE_OTS_OACP_SUPPORT_FEATURE_ABORT_bp;

        uint32_t olcp_features;
/*lint --e{415} --e{416} -save suppress Warning 415: Likely access of out-of-bounds pointer */
        olcp_features = uint32_decode(&p_response->data[sizeof(uint32_t)]);
/*lint -restore*/
        evt.params.feature.olcp_goto    = olcp_features >> BLE_OTS_OLCP_SUPPORT_FEATURE_GOTO_bp;
        evt.params.feature.olcp_order   = olcp_features >> BLE_OTS_OLCP_SUPPORT_FEATURE_ORDER_bp;
        evt.params.feature.olcp_req_num = olcp_features >> BLE_OTS_OLCP_SUPPORT_FEATURE_REQ_NUM_OBJECTS_bp;
        evt.params.feature.olcp_clear   = olcp_features >> BLE_OTS_OLCP_SUPPORT_FEATURE_CLEAR_MARKING_bp;

        p_ots_c->evt_handler(&evt);
    }
    if (p_response->handle == p_ots_c->service.object_size_char.handle_value)
    {
        nrf_ble_ots_c_evt_t evt;

        evt.conn_handle = p_ble_evt->evt.gattc_evt.conn_handle;
        evt.evt_type    = NRF_BLE_OTS_C_EVT_SIZE_READ_RESP;

        uint8_t  len = 0;
        evt.params.size.current_size = uint32_decode(&p_response->data[len]);
        len += sizeof(uint32_t);
/*lint --e{415} --e{416} -save suppress Warning 415: Likely access of out-of-bounds pointer */
        evt.params.size.allocated_size = uint32_decode(&p_response->data[len]);
/*lint -restore*/

/*lint --e{438} -save */
        len += sizeof(uint32_t);
/*lint -restore*/

        p_ots_c->evt_handler(&evt);
    }
}


void nrf_ble_ots_c_on_db_disc_evt(nrf_ble_ots_c_t const * const p_ots_c,
                                    ble_db_discovery_evt_t  * const p_evt)
{
    VERIFY_MODULE_INITIALIZED_VOID();

    nrf_ble_ots_c_evt_t evt;
    ble_gatt_db_char_t* p_chars;

    p_chars      = p_evt->params.discovered_db.charateristics;
    evt.evt_type = NRF_BLE_OTS_C_EVT_DISCOVERY_FAILED;

    if ((p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE) &&
        (p_evt->params.discovered_db.srv_uuid.uuid == BLE_UUID_OTS_SERVICE) &&
        (p_evt->params.discovered_db.srv_uuid.type == BLE_UUID_TYPE_BLE))
    {
        // Find the handles of the ANCS characteristic.
        for (uint32_t i = 0; i < p_evt->params.discovered_db.char_count; i++)
        {
            switch (p_chars[i].characteristic.uuid.uuid)
            {
                case BLE_UUID_OTS_FEATURES:
                    NRF_LOG_DEBUG("OTS Feature Characteristic found.\r\n");
                    memcpy(&evt.params.handles.ots_feature_char,
                           &p_chars[i].characteristic,
                           sizeof(ble_gattc_char_t));
                    break;

                case BLE_UUID_OTS_OBJECT_NAME:
                    NRF_LOG_DEBUG("Object Name Characteristic found.\r\n");
                    memcpy(&evt.params.handles.object_name_char,
                           &p_chars[i].characteristic,
                           sizeof(ble_gattc_char_t));
                    break;

                case BLE_UUID_OTS_OBJECT_TYPE:
                    NRF_LOG_DEBUG("Object Type Characteristic found.\r\n");
                    memcpy(&evt.params.handles.object_type_char,
                           &p_chars[i].characteristic,
                           sizeof(ble_gattc_char_t));
                    break;

                case BLE_UUID_OTS_OBJECT_SIZE:
                    NRF_LOG_DEBUG("Object Size Characteristic found.\r\n");
                    memcpy(&evt.params.handles.object_size_char,
                           &p_chars[i].characteristic,
                           sizeof(ble_gattc_char_t));
                    break;

                case BLE_UUID_OTS_OBJECT_PROPERTIES:
                    NRF_LOG_DEBUG("Object Properties Characteristic found.\r\n");
                    memcpy(&evt.params.handles.object_prop_char,
                           &p_chars[i].characteristic,
                           sizeof(ble_gattc_char_t));
                    break;

                case BLE_UUID_OTS_OACP:
                    NRF_LOG_DEBUG("Object Action Control Point found. CCCD Handle %x\r\n", p_chars[i].cccd_handle);
                    memcpy(&evt.params.handles.object_action_cp_char,
                           &p_chars[i].characteristic,
                           sizeof(ble_gattc_char_t));
                    evt.params.handles.object_action_cp_cccd.handle = p_chars[i].cccd_handle;
                    break;

                default:
                    break;
            }
        }
        evt.evt_type    = NRF_BLE_OTS_C_EVT_DISCOVERY_COMPLETE;
        evt.conn_handle = p_evt->conn_handle;
        p_ots_c->evt_handler(&evt);
    }
    else
    {
        evt.evt_type = NRF_BLE_OTS_C_EVT_DISCOVERY_FAILED;
        p_ots_c->evt_handler(&evt);
    }
}


/**@brief Function for handling the Disconnect event.

   @param[in] p_cts      Pointer to the GATT Service client structure instance.
   @param[in] p_ble_evt  Event received from the BLE stack.
 */
static void on_disconnect(nrf_ble_ots_c_t * const p_ots_c, ble_evt_t const * const p_ble_evt)
{
    if (p_ots_c->conn_handle == p_ble_evt->evt.gap_evt.conn_handle)
    {
        p_ots_c->conn_handle = BLE_CONN_HANDLE_INVALID;

        if (ots_gatt_handles_are_valid(p_ots_c))
        {
            // There was a valid instance of ots on the peer. Send an event to the
            // application, so that it can do any clean up related to this module.
            nrf_ble_ots_c_evt_t evt;

            evt.evt_type = NRF_BLE_OTS_C_EVT_DISCONN_COMPLETE;

            p_ots_c->evt_handler(&evt);
            memset(&p_ots_c->service, 0, sizeof(nrf_ble_ots_c_service_t));
        }
    }
}


void nrf_ble_ots_c_on_ble_evt(ble_evt_t const * const p_ble_evt,
                              void            * p_context)
{
    nrf_ble_ots_c_t * p_ots_c;
    p_ots_c = (nrf_ble_ots_c_t*) p_context;

    VERIFY_MODULE_INITIALIZED_VOID();
    VERIFY_PARAM_NOT_NULL_VOID(p_ots_c);
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_ots_c, p_ble_evt);
            break;

        case BLE_GATTC_EVT_READ_RSP:
            on_read_rsp(p_ots_c, p_ble_evt);
            break;

        case BLE_GATTC_EVT_WRITE_RSP:
            //on_write_rsp()
            NRF_LOG_DEBUG("error handle write response: %x\r\n", p_ble_evt->evt.gattc_evt.error_handle);
            break;

        default:
            break;
    }
    ots_c_l2cap_on_ble_evt(p_ots_c, p_ble_evt);
    ots_c_oacp_on_ble_evt(p_ots_c, p_ble_evt);
}


ret_code_t nrf_ble_ots_c_handles_assign(nrf_ble_ots_c_t                 * const p_ots_c,
                                        uint16_t                        const conn_handle,
                                        nrf_ble_ots_c_service_t const * const p_peer_handles)
{
    VERIFY_MODULE_INITIALIZED();
    VERIFY_PARAM_NOT_NULL(p_ots_c);

    p_ots_c->conn_handle = conn_handle;
    if (p_peer_handles != NULL)
    {
        p_ots_c->service.ots_feature_char.handle_value      = p_peer_handles->ots_feature_char.handle_value;
        p_ots_c->service.object_type_char.handle_value      = p_peer_handles->object_type_char.handle_value;
        p_ots_c->service.object_size_char.handle_value      = p_peer_handles->object_size_char.handle_value;
        p_ots_c->service.object_prop_char.handle_value      = p_peer_handles->object_prop_char.handle_value;
        p_ots_c->service.object_action_cp_char.handle_value = p_peer_handles->object_action_cp_char.handle_value;
        p_ots_c->service.object_action_cp_cccd.handle       = p_peer_handles->object_action_cp_cccd.handle;

    }
    return NRF_SUCCESS;
}


#endif // NRF_MODULE_ENABLED(BLE_OTS_C)
