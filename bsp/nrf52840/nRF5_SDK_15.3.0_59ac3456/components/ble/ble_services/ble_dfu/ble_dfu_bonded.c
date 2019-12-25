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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "nrf_dfu_ble_svci_bond_sharing.h"
#include "nordic_common.h"
#include "nrf_error.h"
#include "ble_dfu.h"
#include "nrf_log.h"
#include "peer_manager.h"
#include "gatts_cache_manager.h"
#include "peer_id.h"
#include "nrf_sdh_soc.h"
#include "nrf_strerror.h"

#if (NRF_DFU_BLE_BUTTONLESS_SUPPORTS_BONDS)


void ble_dfu_buttonless_on_sys_evt(uint32_t, void * );
uint32_t nrf_dfu_svci_vector_table_set(void);
uint32_t nrf_dfu_svci_vector_table_unset(void);

/**@brief Define function for async interface to set peer data. */
NRF_SVCI_ASYNC_FUNC_DEFINE(NRF_DFU_SVCI_SET_PEER_DATA, nrf_dfu_set_peer_data, nrf_dfu_peer_data_t);

// Register SoC observer for the Buttonless Secure DFU service
NRF_SDH_SOC_OBSERVER(m_dfu_buttonless_soc_obs, BLE_DFU_SOC_OBSERVER_PRIO, ble_dfu_buttonless_on_sys_evt, NULL);

ble_dfu_buttonless_t       * mp_dfu;
static nrf_dfu_peer_data_t   m_peer_data;


/**@brief Function for handling Peer Manager events.
 *
 * @param[in] p_evt  Peer Manager event.
 */
static void pm_evt_handler(pm_evt_t const * p_evt)
{
    uint32_t ret;

    if (mp_dfu == NULL)
    {
        return;
    }

    // Only handle this when we are waiting to reset into DFU mode
    if (!mp_dfu->is_waiting_for_reset)
    {
        return;
    }

    switch(p_evt->evt_id)
    {
        case PM_EVT_PEER_DATA_UPDATE_SUCCEEDED:
            if (p_evt->params.peer_data_update_succeeded.data_id == PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING)
            {
                mp_dfu->peers_count--;
                NRF_LOG_DEBUG("Updating Service Changed indication for peers, %d left", mp_dfu->peers_count);
                if (mp_dfu->peers_count == 0)
                {
                    NRF_LOG_DEBUG("Finished updating Service Changed indication for peers");
                    // We have updated Service Changed Indication for all devices.
                    ret = ble_dfu_buttonless_bootloader_start_finalize();
                    if (ret != NRF_SUCCESS)
                    {
                        mp_dfu->evt_handler(BLE_DFU_EVT_BOOTLOADER_ENTER_FAILED);
                    }
                }
            }
            break;

        case PM_EVT_PEER_DATA_UPDATE_FAILED:
            // Failure to update data. Service Changed cannot be sent but DFU mode is still possible
            ret = ble_dfu_buttonless_bootloader_start_finalize();
            if (ret != NRF_SUCCESS)
            {
                mp_dfu->evt_handler(BLE_DFU_EVT_BOOTLOADER_ENTER_FAILED);
            }
            break;

        default:
            break;
    }
}


static uint32_t retrieve_peer_data(void)
{
    ret_code_t              ret;
    pm_peer_data_bonding_t  bonding_data = {0};
    pm_peer_id_t            peer_id;

    ret = pm_peer_id_get(mp_dfu->conn_handle, &peer_id);
    VERIFY_SUCCESS(ret);

    if (peer_id == PM_PEER_ID_INVALID)
    {
        return NRF_ERROR_FORBIDDEN;
    }

    ret = pm_peer_data_bonding_load(peer_id, &bonding_data);
    VERIFY_SUCCESS(ret);

    memcpy(&m_peer_data.ble_id,  &bonding_data.peer_ble_id, sizeof(ble_gap_id_key_t));
    memcpy(&m_peer_data.enc_key, &bonding_data.own_ltk,     sizeof(ble_gap_enc_key_t));

    uint16_t len = SYSTEM_SERVICE_ATT_SIZE;
    ret = sd_ble_gatts_sys_attr_get(mp_dfu->conn_handle,
                                    m_peer_data.sys_serv_attr,
                                    &len,
                                    BLE_GATTS_SYS_ATTR_FLAG_SYS_SRVCS);

    NRF_LOG_DEBUG("system attribute table len: %d", len);

    return ret;
}


/**@brief Function for entering the bootloader.
 *
 * @details This starts forwarding peer data to the Secure DFU bootloader.
 */
static uint32_t enter_bootloader(void)
{
    uint32_t ret;

    NRF_LOG_INFO("Writing peer data to the bootloader...");

    if (mp_dfu->is_waiting_for_svci)
    {
        return ble_dfu_buttonless_resp_send(DFU_OP_ENTER_BOOTLOADER, DFU_RSP_BUSY);
    }

    // If retrieve_peer_data returns NRF_ERROR_FORBIDDEN, then the device was not bonded.
    ret = retrieve_peer_data();
    VERIFY_SUCCESS(ret);

    ret = nrf_dfu_set_peer_data(&m_peer_data);
    if (ret == NRF_SUCCESS)
    {
        // The request was accepted. Waiting for sys events to progress.
        mp_dfu->is_waiting_for_svci = true;
    }
    else if (ret == NRF_ERROR_FORBIDDEN)
    {
        NRF_LOG_ERROR("The bootloader has write protected its settings page. This prohibits setting the peer data. "\
                      "The bootloader must be compiled with NRF_BL_SETTINGS_PAGE_PROTECT=0 to allow setting the peer data.");
    }

    return ret;
}


uint32_t ble_dfu_buttonless_backend_init(ble_dfu_buttonless_t * p_dfu)
{
    VERIFY_PARAM_NOT_NULL(p_dfu);

    // Set the memory used by the backend.
    mp_dfu = p_dfu;

    // Initialize the Peer manager handler.
    return pm_register(&pm_evt_handler);
}


uint32_t ble_dfu_buttonless_async_svci_init(void)
{
    uint32_t ret;

    // Set the vector table base address to the bootloader.
    ret = nrf_dfu_svci_vector_table_set();
    NRF_LOG_DEBUG("nrf_dfu_svci_vector_table_set() -> %s",
                  (ret == NRF_SUCCESS) ? "success" : nrf_strerror_get(ret));
    VERIFY_SUCCESS(ret);

    // Initialize the asynchronous SuperVisor interface to set peer data in Secure DFU bootloader.
    ret = nrf_dfu_set_peer_data_init();
    NRF_LOG_DEBUG("nrf_dfu_set_peer_data_init() -> %s",
                  (ret == NRF_SUCCESS) ? "success" : nrf_strerror_get(ret));
    VERIFY_SUCCESS(ret);

    // Set the vector table base address back to main application.
    ret = nrf_dfu_svci_vector_table_unset();
    NRF_LOG_DEBUG("nrf_dfu_svci_vector_table_unset() -> %s",
                  (ret == NRF_SUCCESS) ? "success" : nrf_strerror_get(ret));

    return ret;
}


void ble_dfu_buttonless_on_sys_evt(uint32_t sys_evt, void * p_context)
{
    uint32_t ret;

    if (!nrf_dfu_set_peer_data_is_initialized())
    {
        return;
    }

    ret = nrf_dfu_set_peer_data_on_sys_evt(sys_evt);
    if (ret == NRF_ERROR_INVALID_STATE)
    {
        // The system event is not from an operation started by buttonless DFU.
        // No action is taken, and nothing is reported.
    }
    else if (ret == NRF_SUCCESS)
    {
        // Peer data was successfully forwarded to the Secure DFU bootloader.
        // Set the flag indicating that we are waiting for indication response
        // to activate the reset.
        mp_dfu->is_waiting_for_reset = true;
        mp_dfu->is_waiting_for_svci  = false;

        // Report back the positive response
        ret = ble_dfu_buttonless_resp_send(DFU_OP_ENTER_BOOTLOADER, DFU_RSP_SUCCESS);
        if (ret != NRF_SUCCESS)
        {
            mp_dfu->evt_handler(BLE_DFU_EVT_RESPONSE_SEND_ERROR);
            mp_dfu->is_waiting_for_reset = false;
        }
    }
    else
    {
        // Failed to set peer data. Report this.
        mp_dfu->is_waiting_for_reset = false;
        mp_dfu->is_waiting_for_svci  = false;
        ret = ble_dfu_buttonless_resp_send(DFU_OP_ENTER_BOOTLOADER, DFU_RSP_BUSY);

        // Report the failure to send the response to the client
        if (ret != NRF_SUCCESS)
        {
            mp_dfu->evt_handler(BLE_DFU_EVT_RESPONSE_SEND_ERROR);
        }

        // Report the failure to enter DFU mode
        mp_dfu->evt_handler(BLE_DFU_EVT_BOOTLOADER_ENTER_FAILED);
    }
}


uint32_t ble_dfu_buttonless_char_add(ble_dfu_buttonless_t * p_dfu)
{
    ble_add_char_params_t add_char_params;

    memset(&add_char_params, 0, sizeof(add_char_params));
    add_char_params.uuid                = BLE_DFU_BUTTONLESS_BONDED_CHAR_UUID;
    add_char_params.uuid_type           = p_dfu->uuid_type;
    add_char_params.char_props.indicate = 1;
    add_char_params.char_props.write    = 1;
    add_char_params.is_defered_write    = true;
    add_char_params.is_var_len          = true;
    add_char_params.max_len             = BLE_GATT_ATT_MTU_DEFAULT;

    add_char_params.cccd_write_access = SEC_JUST_WORKS;
    add_char_params.write_access      = SEC_JUST_WORKS;
    add_char_params.read_access       = SEC_OPEN;

    return characteristic_add(p_dfu->service_handle, &add_char_params, &p_dfu->control_point_char);
}


void ble_dfu_buttonless_on_ctrl_pt_write(ble_gatts_evt_write_t const * p_evt_write)
{
    uint32_t ret;
    ble_dfu_buttonless_rsp_code_t rsp_code = DFU_RSP_OPERATION_FAILED;

    // Start executing the control point write action
    switch (p_evt_write->data[0])
    {
        case DFU_OP_ENTER_BOOTLOADER:
            ret = enter_bootloader();
            if (ret == NRF_SUCCESS)
            {
                rsp_code = DFU_RSP_SUCCESS;
            }
            else if (ret == NRF_ERROR_BUSY)
            {
                rsp_code = DFU_RSP_BUSY;
            }
            else if (ret == NRF_ERROR_FORBIDDEN)
            {
                rsp_code = DFU_RSP_NOT_BONDED;
            }
            break;

        default:
            rsp_code = DFU_RSP_OP_CODE_NOT_SUPPORTED;
            break;
    }

    // Report back in case of error
    if (rsp_code != DFU_RSP_SUCCESS)
    {
        ret = ble_dfu_buttonless_resp_send((ble_dfu_buttonless_op_code_t)p_evt_write->data[0],
                                            rsp_code);

        if (ret != NRF_SUCCESS)
        {
            mp_dfu->evt_handler(BLE_DFU_EVT_RESPONSE_SEND_ERROR);
        }

        // Report the error to the main application
        mp_dfu->evt_handler(BLE_DFU_EVT_BOOTLOADER_ENTER_FAILED);
    }
}


uint32_t ble_dfu_buttonless_bootloader_start_prepare(void)
{
    NRF_LOG_DEBUG("In ble_dfu_buttonless_bootloader_start_prepare");

    // Indicate to main app that DFU mode is starting.
    // This event can be used to let the device take down any connection to
    // bonded devices.
    mp_dfu->evt_handler(BLE_DFU_EVT_BOOTLOADER_ENTER_PREPARE);

    // Store the number of peers for which Peer Manager is expected to successfully write events.
    mp_dfu->peers_count = peer_id_n_ids();

    // Set local database changed to get Service Changed indication for all bonded peers
    // on next bootup (either because of a successful or aborted DFU).
    gscm_local_database_has_changed();

    return NRF_SUCCESS;
}

#endif // NRF_DFU_BLE_BUTTONLESS_SUPPORTS_BONDS

