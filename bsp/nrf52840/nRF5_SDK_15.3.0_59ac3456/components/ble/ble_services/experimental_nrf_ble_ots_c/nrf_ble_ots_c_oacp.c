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

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_OTS_C_OACP)
#include <stdlib.h>
#include "nrf_ble_ots_c_oacp.h"
#include "ble.h"

#define NRF_LOG_MODULE_NAME ble_ots_c_oacp
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#include "sdk_common.h"

#define BLE_OTS_OACP_WRITE_OP_SIZE 10
#define BLE_OTS_OACP_READ_OP_SIZE  9

#define MODULE_INITIALIZED (p_ots_c->initialized)

static void oacp_response(nrf_ble_ots_c_t const * const p_ots_c,
                          ble_gattc_evt_t const * const p_ble_gattc_evt)
{
    nrf_ble_ots_c_evt_t         evt;
    nrf_ble_ots_c_evt_handler_t evt_handler = p_ots_c->evt_handler;

/*lint --e{415} --e{416} -save suppress Warning 415: Likely access of out-of-bounds pointer */
    evt.params.response.request_op_code = (ble_ots_c_oacp_proc_type_t) p_ble_gattc_evt->params.hvx.data[sizeof(uint8_t)];
    evt.params.response.result_code     = (ble_ots_c_oacp_res_code_t) p_ble_gattc_evt->params.hvx.data[2*sizeof(uint8_t)];
/*lint -restore*/
    evt.evt_type    = NRF_BLE_OTS_C_EVT_OACP_RESP;
    evt.conn_handle = p_ble_gattc_evt->conn_handle;
    evt_handler(&evt);
}

/**@brief Function for handling the indication and notifications from the GATT Service Server.

   @param[in] p_ots_c       Pointer to Object Transfer client structure.
   @param[in] p_ble_gattc_evt Pointer to a gattc event.
*/
static void on_hvx(nrf_ble_ots_c_t const * const p_ots_c,
                   ble_gattc_evt_t const * const p_ble_gattc_evt)
{


    uint16_t oacp_handle = p_ots_c->service.object_action_cp_char.handle_value;

    if ((p_ble_gattc_evt->params.hvx.handle == oacp_handle)
        && (p_ots_c->evt_handler != NULL))
    {
        ret_code_t err_code = sd_ble_gattc_hv_confirm(p_ble_gattc_evt->conn_handle,
                                                      oacp_handle);

        if ((err_code != NRF_SUCCESS) && (p_ots_c->err_handler != NULL))
        {
            p_ots_c->err_handler(err_code);
        }
        uint8_t op_code = p_ble_gattc_evt->params.hvx.data[0];
        
        if(op_code == NRF_BLE_OTS_C_OACP_PROC_RESP)
        {
            oacp_response(p_ots_c, p_ble_gattc_evt);
        }
    }
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


ret_code_t nrf_ble_ots_c_indication_enable(nrf_ble_ots_c_t * const p_ots_c,
                                           bool const              enable)
{
    VERIFY_MODULE_INITIALIZED();
    VERIFY_TRUE(ots_gatt_handles_are_valid(p_ots_c), NRF_ERROR_INVALID_STATE);

    if (p_ots_c->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    ret_code_t err_code = NRF_SUCCESS;

    ble_gattc_write_params_t gattc_params;
    
    memset(&gattc_params, 0x00, sizeof(gattc_params));
    uint16_t cccd_val = (enable) ? BLE_GATT_HVX_INDICATION : 0;

    gattc_params.handle   = p_ots_c->service.object_action_cp_cccd.handle;
    gattc_params.len      = BLE_CCCD_VALUE_LEN;
    gattc_params.p_value  = (uint8_t *)&cccd_val;
    gattc_params.offset   = 0;
    gattc_params.write_op = BLE_GATT_OP_WRITE_REQ;

    err_code = sd_ble_gattc_write(p_ots_c->conn_handle, &gattc_params);
    return err_code;
}


ret_code_t nrf_ble_ots_c_oacp_write_object(nrf_ble_ots_c_t * const p_ots_c, uint32_t offset, uint32_t len, bool truncate)
{
    VERIFY_MODULE_INITIALIZED();
    VERIFY_TRUE(ots_gatt_handles_are_valid(p_ots_c), NRF_ERROR_INVALID_STATE);

    if (p_ots_c->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    ret_code_t err_code = NRF_SUCCESS;

    uint8_t val[BLE_OTS_OACP_WRITE_OP_SIZE];
    memset(val, 0, sizeof(val));

    uint32_t i = 0;

    // OP Code
    val[i++] = NRF_BLE_OTS_C_OACP_PROC_WRITE;

    //Offset
    i += uint32_encode(offset, &val[i]);

    //Len
    i += uint32_encode(len, &val[i]);

    val[i] |= (truncate << 0);
    ble_gattc_write_params_t gattc_params;
    memset(&gattc_params, 0, sizeof(ble_gattc_write_params_t));

    gattc_params.handle   = p_ots_c->service.object_action_cp_char.handle_value;
    gattc_params.len      = i;
    gattc_params.p_value  = (uint8_t *)val;
    gattc_params.offset   = 0;
    gattc_params.write_op = BLE_GATT_OP_WRITE_REQ;

    err_code = sd_ble_gattc_write(p_ots_c->conn_handle, &gattc_params);
    if(err_code != NRF_SUCCESS)
    {
        p_ots_c->err_handler(err_code);
    }
    return err_code;
}

ret_code_t nrf_ble_ots_c_oacp_read_object(nrf_ble_ots_c_t * const p_ots_c, uint32_t offset, uint32_t len)
{
    VERIFY_MODULE_INITIALIZED();
    VERIFY_TRUE(ots_gatt_handles_are_valid(p_ots_c), NRF_ERROR_INVALID_STATE);

    if (p_ots_c->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    ret_code_t err_code = NRF_SUCCESS;

    uint8_t val[BLE_OTS_OACP_READ_OP_SIZE];
    memset(val, 0, sizeof(val));

    uint32_t i = 0;

    // OP Code
    val[i++] = NRF_BLE_OTS_C_OACP_PROC_READ;

    //Offset
    i += uint32_encode(offset, &val[i]);

    //Len
    i += uint32_encode(len, &val[i]);

    ble_gattc_write_params_t gattc_params;
    memset(&gattc_params, 0, sizeof(ble_gattc_write_params_t));

    gattc_params.handle   = p_ots_c->service.object_action_cp_char.handle_value;
    gattc_params.len      = sizeof(val);
    gattc_params.p_value  = (uint8_t *)val;
    gattc_params.offset   = 0;
    gattc_params.write_op = BLE_GATT_OP_WRITE_REQ;

    err_code = sd_ble_gattc_write(p_ots_c->conn_handle, &gattc_params);
    return err_code;
}



void ots_c_oacp_on_ble_evt(nrf_ble_ots_c_t * const p_ots_c,
                           ble_evt_t const * const p_ble_evt)
{
    VERIFY_MODULE_INITIALIZED_VOID();
    VERIFY_PARAM_NOT_NULL_VOID(p_ots_c);
    VERIFY_PARAM_NOT_NULL_VOID(p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {

        case BLE_GATTC_EVT_HVX:
            on_hvx(p_ots_c, &(p_ble_evt->evt.gattc_evt));
            break;

        default:
            break;
    }
}

#endif // NRF_MODULE_ENABLED(BLE_OTS_C)
