/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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

#include <string.h>
#include "nrf_svci_async_handler.h"
#include "app_error.h"
#include "nrf_nvmc.h"
#include "nrf_dfu_types.h"
#include "nrf_dfu_ble_svci_bond_sharing.h"
#include "nrf_log.h"
#include "nrf_dfu_settings.h"
#include "sdk_config.h"


#if (NRF_DFU_TRANSPORT_BLE && NRF_DFU_BLE_REQUIRES_BONDS)


NRF_SVCI_ASYNC_HANDLER_CREATE(NRF_DFU_SVCI_SET_PEER_DATA,
    nrf_dfu_set_peer_data, nrf_dfu_peer_data_t, nrf_dfu_peer_data_state_t);


static uint32_t nrf_dfu_set_peer_data_handler(nrf_dfu_set_peer_data_svci_async_t * p_async)
{
    VERIFY_PARAM_NOT_NULL(p_async);

    p_async->async_func      = nrf_dfu_set_peer_data_on_call;
    p_async->sys_evt_handler = nrf_dfu_set_peer_data_on_sys_evt;
    p_async->state           = DFU_PEER_DATA_STATE_INITIALIZED;

    return NRF_SUCCESS;
}


static uint32_t nrf_dfu_set_peer_data_on_call(nrf_dfu_peer_data_t       * p_data,
                                              nrf_dfu_peer_data_state_t * p_state)
{
    uint32_t ret_val = NRF_ERROR_BUSY;

    VERIFY_PARAM_NOT_NULL(p_state);

    switch (*p_state)
    {
        case DFU_PEER_DATA_STATE_INVALID:
            return NRF_ERROR_INVALID_STATE;

        case DFU_PEER_DATA_STATE_INITIALIZED:
            ret_val = nrf_dfu_settings_peer_data_write(p_data);
            if (ret_val == NRF_SUCCESS)
            {
                *p_state = DFU_PEER_DATA_STATE_WRITE_REQUESTED;
            }
            break;

        case DFU_PEER_DATA_STATE_WRITE_REQUESTED:
            return NRF_ERROR_BUSY;

        case DFU_PEER_DATA_STATE_WRITE_FINISHED:
            return NRF_ERROR_INVALID_STATE;

        case DFU_PEER_DATA_STATE_WRITE_FAILED:
            return NRF_ERROR_INVALID_STATE;
    }

    return ret_val;
}


static uint32_t nrf_dfu_set_peer_data_on_sys_evt(uint32_t sys_event, nrf_dfu_peer_data_state_t * p_state)
{
    uint32_t ret_val = NRF_ERROR_INVALID_STATE;

    VERIFY_PARAM_NOT_NULL(p_state);

    if (*p_state == DFU_PEER_DATA_STATE_WRITE_REQUESTED)
    {
        switch (sys_event)
        {
            case NRF_EVT_FLASH_OPERATION_ERROR:
                return NRF_ERROR_BUSY;

            case NRF_EVT_FLASH_OPERATION_SUCCESS:
                ret_val = NRF_SUCCESS;
                (*p_state) = DFU_PEER_DATA_STATE_WRITE_FINISHED;
                break;

            default:
                // Event not intended for us
                break;
        }
    }

    return ret_val;
}

#elif (NRF_DFU_TRANSPORT_BLE && !NRF_DFU_BLE_REQUIRES_BONDS)


NRF_SVCI_ASYNC_HANDLER_CREATE(NRF_DFU_SVCI_SET_ADV_NAME,
    nrf_dfu_set_adv_name,  nrf_dfu_adv_name_t,  nrf_dfu_set_adv_name_state_t);


static uint32_t nrf_dfu_set_adv_name_handler(nrf_dfu_set_adv_name_svci_async_t * p_async)
{
    VERIFY_PARAM_NOT_NULL(p_async);

    p_async->async_func      = nrf_dfu_set_adv_name_on_call;
    p_async->sys_evt_handler = nrf_dfu_set_adv_name_on_sys_evt;
    p_async->state           = DFU_ADV_NAME_STATE_INITIALIZED;

    return NRF_SUCCESS;
}


static uint32_t nrf_dfu_set_adv_name_on_call(nrf_dfu_adv_name_t           * p_adv_name,
                                             nrf_dfu_set_adv_name_state_t * p_state)
{
    uint32_t ret_val = NRF_ERROR_BUSY;

    VERIFY_PARAM_NOT_NULL(p_state);

    switch (*p_state)
    {
        case DFU_ADV_NAME_STATE_INVALID:
            return NRF_ERROR_INVALID_STATE;

        case DFU_ADV_NAME_STATE_INITIALIZED:
            ret_val = nrf_dfu_settings_adv_name_write(p_adv_name);
            if (ret_val == NRF_SUCCESS)
            {
                *p_state = DFU_ADV_NAME_STATE_WRITE_REQUESTED;
            }
            break;

        case DFU_ADV_NAME_STATE_WRITE_REQUESTED:
            return NRF_ERROR_BUSY;

        case DFU_ADV_NAME_STATE_WRITE_FINISHED:
            return NRF_ERROR_INVALID_STATE;

        case DFU_ADV_NAME_STATE_WRITE_FAILED:
            return NRF_ERROR_INVALID_STATE;
    }

    return ret_val;
}


static uint32_t nrf_dfu_set_adv_name_on_sys_evt(uint32_t sys_event, nrf_dfu_set_adv_name_state_t * p_state)
{
    uint32_t ret_val = NRF_ERROR_INVALID_STATE;

    VERIFY_PARAM_NOT_NULL(p_state);

    if (*p_state == DFU_ADV_NAME_STATE_WRITE_REQUESTED)
    {
        switch (sys_event)
        {
            case NRF_EVT_FLASH_OPERATION_ERROR:
                return NRF_ERROR_BUSY;

            case NRF_EVT_FLASH_OPERATION_SUCCESS:
                ret_val = NRF_SUCCESS;
                (*p_state) = DFU_ADV_NAME_STATE_WRITE_FINISHED;
                break;

            default:
                // Event not intended for us
                break;
        }
    }

    return ret_val;
}

#endif  // NRF_DFU_TRANSPORT_BLE && !NRF_DFU_BLE_REQUIRES_BONDS
