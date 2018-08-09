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
#if NRF_MODULE_ENABLED(NRF_BLE_GATTS_C)

#include "nrf_ble_gatts_c.h"
#include <string.h>
#include "ble.h"

#define NRF_LOG_MODULE_NAME nrf_ble_gatts_c
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


#define GATTS_LOG          NRF_LOG_DEBUG            /**< A debug logger macro that can be used in this file to perform logging over UART. */
#define MODULE_INITIALIZED (p_gatts_c->initialized) /**< Macro indicating whether the module has been initialized properly. */

static const ble_uuid_t m_gatts_uuid = {BLE_UUID_GATT, BLE_UUID_TYPE_BLE};  /**< Service Changed indication UUID. */


/**@brief Function for handling the indication and notifications from the GATT Service Server.

   @param[in] p_gatts_c       Pointer to Service Changed client structure.
   @param[in] p_ble_gattc_evt Pointer to a gattc event.
*/
static void on_hvx(nrf_ble_gatts_c_t const * const p_gatts_c,
                   ble_gattc_evt_t   const * const p_ble_gattc_evt)
{
    uint16_t srv_changed_handle = p_gatts_c->srv_changed_char.characteristic.handle_value;

    if ((p_ble_gattc_evt->params.hvx.handle == srv_changed_handle)
        && (p_gatts_c->evt_handler != NULL))
    {
        ret_code_t err_code = sd_ble_gattc_hv_confirm(p_ble_gattc_evt->conn_handle,
                                                      srv_changed_handle);

        if ((err_code != NRF_SUCCESS) && (p_gatts_c->err_handler != NULL))
        {
            p_gatts_c->err_handler(err_code);
        }

        nrf_ble_gatts_c_evt_t         evt;
        nrf_ble_gatts_c_evt_handler_t evt_handler = p_gatts_c->evt_handler;

        /*lint --e{415} --e{416} -save suppress Warning 415: Likely access of out-of-bounds pointer */
        evt.params.handle_range.start_handle = uint16_decode(p_ble_gattc_evt->params.hvx.data);
        evt.params.handle_range.end_handle   = uint16_decode(p_ble_gattc_evt->params.hvx.data + sizeof(uint16_t));
        /*lint -restore*/

        evt.evt_type    = NRF_BLE_GATTS_C_EVT_SRV_CHANGED;
        evt.conn_handle = p_ble_gattc_evt->conn_handle;

        GATTS_LOG ("Service Changed Indication.\n\r");
        evt_handler(&evt);

    }
}


ret_code_t nrf_ble_gatts_c_init(nrf_ble_gatts_c_t      * p_gatts_c,
                                nrf_ble_gatts_c_init_t * p_gatts_c_init)
{
    ret_code_t err_code = NRF_SUCCESS;
    VERIFY_PARAM_NOT_NULL(p_gatts_c);
    VERIFY_PARAM_NOT_NULL(p_gatts_c_init);
    VERIFY_PARAM_NOT_NULL(p_gatts_c_init->evt_handler);
    memset (p_gatts_c, 0, sizeof(nrf_ble_gatts_c_t));

    p_gatts_c->conn_handle = BLE_CONN_HANDLE_INVALID;
    p_gatts_c->evt_handler = p_gatts_c_init->evt_handler;

    err_code = ble_db_discovery_evt_register(&m_gatts_uuid);
    VERIFY_SUCCESS(err_code);

    p_gatts_c->initialized = true;
    return err_code;
}


/**@brief Function for checking whether the peer's GATT Service instance and the Service Changed
          Characteristic have been discovered.

   @param[in] p_gatts_c Pointer to the GATT Service client structure instance.

   @return True if the Service Changed Characteristic handle is valid.
   @return False if the Service Changed Characteristic handle is invalid.
 */
static bool gatts_gatt_handles_are_valid(nrf_ble_gatts_c_t const * const p_gatts_c)
{
    return (p_gatts_c->srv_changed_char.characteristic.handle_value != BLE_GATT_HANDLE_INVALID);
}


ret_code_t nrf_ble_gatts_c_enable_indication(nrf_ble_gatts_c_t * const p_gatts_c,
                                             bool const                enable)
{
    VERIFY_MODULE_INITIALIZED();

    if (    (p_gatts_c->conn_handle == BLE_CONN_HANDLE_INVALID)
        || !(gatts_gatt_handles_are_valid(p_gatts_c)))
    {
        return NRF_ERROR_INVALID_STATE;
    }

    ret_code_t err_code = NRF_SUCCESS;
    uint16_t   cccd_val = (enable) ? BLE_GATT_HVX_INDICATION : 0;

    ble_gattc_write_params_t gattc_params =
    {
        .handle   = p_gatts_c->srv_changed_char.cccd_handle,
        .len      = BLE_CCCD_VALUE_LEN,
        .p_value  = (uint8_t *)&cccd_val,
        .offset   = 0,
        .write_op = BLE_GATT_OP_WRITE_REQ,
    };

    err_code = sd_ble_gattc_write(p_gatts_c->conn_handle, &gattc_params);
    return err_code;
}


void nrf_ble_gatts_c_on_db_disc_evt(nrf_ble_gatts_c_t const * const p_gatts_c,
                                    ble_db_discovery_evt_t  * const p_evt)
{
    VERIFY_MODULE_INITIALIZED_VOID();

    nrf_ble_gatts_c_evt_t evt;
    ble_gatt_db_char_t  * p_chars;

    p_chars      = p_evt->params.discovered_db.charateristics;
    evt.evt_type = NRF_BLE_GATTS_C_EVT_DISCOVERY_FAILED;

    if (   (p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE)
        && (p_evt->params.discovered_db.srv_uuid.uuid == BLE_UUID_GATT)
        && (p_evt->params.discovered_db.srv_uuid.type == BLE_UUID_TYPE_BLE))
    {
        // Find the handles of the Service Changed Characteristics.
        for (uint32_t i = 0; i < p_evt->params.discovered_db.char_count; i++)
        {
            if (   (p_chars[i].characteristic.uuid.uuid == BLE_UUID_GATT_CHARACTERISTIC_SERVICE_CHANGED)
                && (p_chars[i].characteristic.char_props.indicate != 0))
            {
                memcpy(&evt.params.srv_changed_char,
                       &p_chars[i],
                       sizeof(ble_gatt_db_char_t));

                evt.evt_type           = NRF_BLE_GATTS_C_EVT_DISCOVERY_COMPLETE;
                GATTS_LOG("Service Changed Characteristic found.\n\r");
                break;
            }
        }
    }

    if (p_gatts_c->evt_handler != NULL)
    {
        nrf_ble_gatts_c_evt_handler_t evt_handler = p_gatts_c->evt_handler;
        evt.conn_handle                           = p_evt->conn_handle;
        evt_handler(&evt);
    }
}


/**@brief Function for handling the Disconnect event.

   @param[in] p_cts      Pointer to the GATT Service client structure instance.
   @param[in] p_ble_evt  Event received from the BLE stack.
 */
static void on_disconnect(nrf_ble_gatts_c_t * p_gatts_c, ble_evt_t const * p_ble_evt)
{
    if (p_gatts_c->conn_handle == p_ble_evt->evt.gap_evt.conn_handle)
    {
        p_gatts_c->conn_handle = BLE_CONN_HANDLE_INVALID;

        if (gatts_gatt_handles_are_valid(p_gatts_c))
        {
            // There was a valid instance of GATTS on the peer. Send an event to the
            // application, so that it can do any clean up related to this module.
            nrf_ble_gatts_c_evt_t evt;

            evt.evt_type = NRF_BLE_GATTS_C_EVT_DISCONN_COMPLETE;

            p_gatts_c->evt_handler(&evt);
            p_gatts_c->srv_changed_char.characteristic.handle_value = BLE_GATT_HANDLE_INVALID;
            p_gatts_c->srv_changed_char.cccd_handle                 = BLE_GATT_HANDLE_INVALID;
            p_gatts_c->srv_changed_char.ext_prop_handle             = BLE_GATT_HANDLE_INVALID;
            p_gatts_c->srv_changed_char.report_ref_handle           = BLE_GATT_HANDLE_INVALID;
            p_gatts_c->srv_changed_char.user_desc_handle            = BLE_GATT_HANDLE_INVALID;
        }
    }
}


void nrf_ble_gatts_c_on_ble_evt(ble_evt_t const * p_ble_evt,
                                void            * p_context)
{
    nrf_ble_gatts_c_t * p_gatts_c;
    p_gatts_c = p_context;

    VERIFY_MODULE_INITIALIZED_VOID();
    VERIFY_PARAM_NOT_NULL_VOID(p_gatts_c);
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_gatts_c, p_ble_evt);
            break;

        case BLE_GATTC_EVT_HVX:
            on_hvx(p_gatts_c, &(p_ble_evt->evt.gattc_evt));
            break;

        default:
            break;
    }
}


ret_code_t nrf_ble_gatts_c_handles_assign(nrf_ble_gatts_c_t        * const p_gatts_c,
                                          uint16_t                   const conn_handle,
                                          ble_gatt_db_char_t const * const p_peer_handles)
{
    VERIFY_PARAM_NOT_NULL(p_gatts_c);
    VERIFY_MODULE_INITIALIZED();

    p_gatts_c->conn_handle = conn_handle;
    if (p_peer_handles != NULL)
    {
        p_gatts_c->srv_changed_char.cccd_handle                 = p_peer_handles->cccd_handle;
        p_gatts_c->srv_changed_char.ext_prop_handle             = p_peer_handles->ext_prop_handle;
        p_gatts_c->srv_changed_char.report_ref_handle           = p_peer_handles->report_ref_handle;
        p_gatts_c->srv_changed_char.user_desc_handle            = p_peer_handles->user_desc_handle;
        p_gatts_c->srv_changed_char.characteristic.handle_value = p_peer_handles->characteristic.handle_value;

    }
    return NRF_SUCCESS;
}
#endif // NRF_MODULE_ENABLED(BLE_GATTS_C)
