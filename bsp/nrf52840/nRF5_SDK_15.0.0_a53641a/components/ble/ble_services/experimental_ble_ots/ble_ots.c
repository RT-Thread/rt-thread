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

#include <stdint.h>
#include <string.h>
#include "ble_ots.h"
#include "ble_ots_object.h"
#include "ble_ots_oacp.h"
#include "fds.h"

#define BLE_OTS_MAX_OBJ_TYPE_SIZE               16
#define BLE_OTS_OBJ_CHANGED_SIZE                7
#define OTS_INVALID_ID                          0xFF

#define SIZE_DATE_TIME                          7

#define BLE_OTS_INVALID_OCTET_OFFSET       BLE_GATT_STATUS_ATTERR_APP_BEGIN + 1
#define BLE_OTS_INVALID_METADATA           BLE_GATT_STATUS_ATTERR_APP_BEGIN + 2
#define BLE_OTS_CONCURRENCY_LIMIT_EXCEEDED BLE_GATT_STATUS_ATTERR_APP_BEGIN + 3


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

/**@brief Function for adding the features characteristic.
 *
 * @param[in]   p_ots                   Object Transfer Service structure.
 * @param[in]   read_access             Read security level for the feature characteristic.
 * @param[in]   p_feature_char_handles  Pointer to the handles for the feature characteristic.
 */
static uint32_t feature_char_add(ble_ots_t * const          p_ots,
                                 security_req_t             read_access,
                                 ble_gatts_char_handles_t * p_feature_char_handles)
{
    ble_add_char_params_t add_char_params;

    uint8_t               feature[BLE_OTS_FEATURE_LEN];

    uint32_t              oacp_features;
    uint32_t              olcp_features;

    oacp_features = 0;
    oacp_features |= (1 << BLE_OTS_OACP_SUPPORT_FEATURE_READ_bp);
    oacp_features |= (1 << BLE_OTS_OACP_SUPPORT_FEATURE_APPEND_bp);
    oacp_features |= (1 << BLE_OTS_OACP_SUPPORT_FEATURE_TRUNCATE_bp);
    oacp_features |= (1 << BLE_OTS_OACP_SUPPORT_FEATURE_PATCH_bp);
    oacp_features |= (1 << BLE_OTS_OACP_SUPPORT_FEATURE_ABORT_bp);

    olcp_features = 0;

    uint32_t i = 0;
    i += uint32_encode(oacp_features, &feature[i]);
    i += uint32_encode(olcp_features, &feature[i]);

    memset(&add_char_params, 0, sizeof(add_char_params));

    add_char_params.uuid            = BLE_UUID_OTS_FEATURES;
    add_char_params.uuid_type       = BLE_UUID_TYPE_BLE;
    add_char_params.max_len         = BLE_OTS_FEATURE_LEN;
    add_char_params.init_len        = BLE_OTS_FEATURE_LEN;
    add_char_params.p_init_value    = &feature[0];
    add_char_params.char_props.read = 1;
    add_char_params.read_access     = read_access;

    return characteristic_add(p_ots->service_handle,
                              &add_char_params,
                              p_feature_char_handles);
}

/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_ots       Object Transfer Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_ots_t * p_ots, ble_evt_t const * p_ble_evt)
{
    p_ots->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

/**@brief     Function for handling the BLE_GAP_EVT_DISCONNECTED event.
 *
 * @param[in] p_ots     OTS Service Structure.
 * @param[in] p_ble_evt Pointer to the event received from BLE stack.
 */
static void on_disconnect(ble_ots_t * p_ots, ble_evt_t const * p_ble_evt)
{
    p_ots->conn_handle = BLE_CONN_HANDLE_INVALID;
}

uint32_t ble_ots_init(ble_ots_t * p_ots, ble_ots_init_t * p_ots_init)
{
    if ((p_ots == NULL) || (p_ots_init == NULL))
    {
        return NRF_ERROR_NULL;
    }

    if (p_ots_init->p_object == NULL)
    {
        return NRF_ERROR_NULL;
    }

    p_ots->conn_handle              = BLE_CONN_HANDLE_INVALID;
    p_ots->error_handler            = p_ots_init->error_handler;
    p_ots->evt_handler              = p_ots_init->evt_handler;
    p_ots->p_current_object         = p_ots_init->p_object;
    p_ots->error_handler            = p_ots_init->error_handler;
    p_ots->evt_handler              = p_ots_init->evt_handler;
    p_ots->p_current_object         = p_ots_init->p_object;


    ble_uuid_t  service_uuid =
    {
        .uuid = BLE_UUID_OTS_SERVICE,
        .type = BLE_UUID_TYPE_BLE
    };
    uint32_t    err_code;

    err_code = fds_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                        &service_uuid,
                                        &(p_ots->service_handle));
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = feature_char_add(p_ots, p_ots_init->feature_char_read_access, &p_ots->feature_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = ble_ots_object_representation_init(&p_ots->object_chars, &p_ots_init->object_chars_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    err_code = ble_ots_oacp_init(&p_ots->oacp_chars, &p_ots_init->oacp_init);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    p_ots->oacp_chars.ots_l2cap.conn_mps = p_ots_init->rx_mps;
    p_ots->oacp_chars.ots_l2cap.conn_mtu = p_ots_init->rx_mtu;

    return NRF_SUCCESS;
}

/**@brief Function for handling the BLE_EVT_TX_COMPLETE event. Calls the hvx buffering module.
 * @param[in]   p_ots       Object Transfer Service structure. */
static inline void on_tx_complete(ble_ots_t * p_ots)
{
    uint32_t err_code;
    err_code = ble_hvx_buffer_process(&p_ots->hvx_buf);
    if (err_code != NRF_SUCCESS)
    {
        p_ots->error_handler(err_code);
    }

}

void ble_ots_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_ots_t * p_ots;
    p_ots = (ble_ots_t*) p_context;

    if ((p_ots == NULL) || (p_ble_evt == NULL))
    {
        return;
    }
    ble_ots_oacp_on_ble_evt(&p_ots->oacp_chars, p_ble_evt);
    ble_ots_object_on_ble_evt(&p_ots->object_chars, p_ble_evt);

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_ots, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_ots, p_ble_evt);
            break;

        case BLE_GATTS_EVT_HVN_TX_COMPLETE:
            on_tx_complete(p_ots);
            break;

        default:
            // No implementation needed.
            break;
    }
}

