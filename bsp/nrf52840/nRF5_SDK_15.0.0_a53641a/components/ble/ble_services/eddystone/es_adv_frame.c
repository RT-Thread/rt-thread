/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#include "es_adv_frame.h"
#include "es_slot.h"


/**@brief Function for setting advertisement data, using 'ble_advdata_encode'.
 *
 * @param[in] p_scrsp_data      Scan response data.
 * @param[in] p_es_data_array   Eddystone service data array.
 */
static void fill_adv_data(ble_advdata_t * p_scrsp_data, uint8_array_t * p_es_data_array, ble_gap_adv_data_t * const p_adv_data)
{
    ble_advdata_t adv_data;
    ret_code_t    err_code;
    ble_uuid_t    adv_uuids[]   = {{ES_UUID, BLE_UUID_TYPE_BLE}};
    uint8_array_t es_data_array = {0};

    ble_advdata_service_data_t service_data; // Structure to hold Service Data.

    service_data.service_uuid = APP_ES_UUID; // Eddystone UUID to allow discoverability on iOS devices.

    service_data.data = (p_es_data_array != NULL) ? *p_es_data_array : es_data_array;

    // Build and set advertising data.
    memset(&adv_data, 0, sizeof(ble_advdata_t));

    adv_data.name_type               = BLE_ADVDATA_NO_NAME;
    adv_data.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    adv_data.uuids_complete.uuid_cnt = sizeof(adv_uuids) / sizeof(adv_uuids[0]);
    adv_data.uuids_complete.p_uuids  = adv_uuids;
    adv_data.p_service_data_array    = &service_data;
    adv_data.service_data_count      = (p_es_data_array != NULL) ? 1 : 0;

    err_code = ble_advdata_encode(&adv_data,
                                  p_adv_data->adv_data.p_data,
                                  &p_adv_data->adv_data.len);
    APP_ERROR_CHECK(err_code);
    if (p_scrsp_data != NULL)
    {
        err_code = ble_advdata_encode(p_scrsp_data,
                                      p_adv_data->scan_rsp_data.p_data,
                                      &p_adv_data->scan_rsp_data.len);
        APP_ERROR_CHECK(err_code);
    }
    else
    {
        p_adv_data->scan_rsp_data.p_data = NULL;
        p_adv_data->scan_rsp_data.len    = 0;
    }
}


void es_adv_frame_fill_connectable_adv_data(ble_advdata_t * p_scrsp_data, ble_gap_adv_data_t * const p_adv_data)
{
    fill_adv_data(p_scrsp_data, NULL, p_adv_data);
}


void es_adv_frame_fill_non_connectable_adv_data(uint8_t slot_no, bool etlm, ble_gap_adv_data_t * const p_adv_data)
{
    uint8_array_t         es_data_array = {0};
    const es_slot_reg_t * p_reg         = es_slot_get_registry();

    if (etlm)
    {
        es_slot_etlm_update(slot_no);

        // If eTLM, the incoming slot_no points to the corresponding EID slot, update to point to TLM slot.
        slot_no = p_reg->tlm_slot;
    }

    // If TLM, update the TLM data.
    else if (p_reg->slots[slot_no].adv_frame.type == ES_FRAME_TYPE_TLM)
    {
        es_slot_tlm_update();
    }

    es_data_array.p_data = (uint8_t *)&p_reg->slots[slot_no].adv_frame.frame;
    es_data_array.size   = p_reg->slots[slot_no].adv_frame.length;

    fill_adv_data(NULL, &es_data_array, p_adv_data);
}
