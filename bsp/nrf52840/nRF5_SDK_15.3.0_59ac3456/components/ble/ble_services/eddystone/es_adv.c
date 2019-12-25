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
#include "es_adv.h"
#include "app_error.h"
#include "es_adv_frame.h"
#include "es_adv_timing.h"
#include "es_tlm.h"
#include "es_slot.h"

static es_adv_evt_handler_t m_adv_evt_handler;                                       //!< Eddystone advertisement event handler.
static bool                 m_is_connected       = false;                            //!< Is the Eddystone beacon in a connected state.
static bool                 m_remain_connectable = false;                            //!< Should the Eddystone beacon remain connectable.
static uint8_t              m_ecs_uuid_type      = 0;                                //!< UUID type of the Eddystone Configuration Service.
static uint16_t             m_adv_interval       = APP_CFG_NON_CONN_ADV_INTERVAL_MS; //!< Current advertisement interval.

static uint8_t   m_enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];                    //!< Buffer for storing an encoded advertising set.
static uint8_t   m_enc_scan_response_data[BLE_GAP_ADV_SET_DATA_SIZE_MAX];         //!< Buffer for storing an encoded scan data.
static uint8_t  *mp_adv_handle;                                                   //!< Pointer to the advertising handle.

/**@brief Struct that contains pointers to the encoded advertising data. */
static ble_gap_adv_data_t m_adv_data =
{
    .adv_data =
    {
        .p_data = m_enc_advdata,
        .len    = BLE_GAP_ADV_SET_DATA_SIZE_MAX
    },
    .scan_rsp_data =
    {
        .p_data = m_enc_scan_response_data,
        .len    = BLE_GAP_ADV_SET_DATA_SIZE_MAX
        
    }
};

/**@brief Function for invoking registered callback.
 *
 * @param[in] evt Event to issue to callback.
 */
static void invoke_callback(es_adv_evt_t evt)
{
    if (m_adv_evt_handler != NULL)
    {
        m_adv_evt_handler(evt);
    }
}

/**@brief Starting advertising.
 * @param[in]   p_adv_params  Advertisement parameters to use.
 */
static void adv_start(ble_gap_adv_params_t * p_adv_params)
{
    ret_code_t err_code = NRF_SUCCESS;

    es_tlm_adv_cnt_inc();

    err_code = sd_ble_gap_adv_set_configure(mp_adv_handle, &m_adv_data, p_adv_params);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ble_gap_adv_start(*mp_adv_handle, BLE_CONN_CFG_TAG_DEFAULT);

    if (err_code != NRF_ERROR_BUSY && err_code != NRF_SUCCESS)
    {
        APP_ERROR_CHECK(err_code);
    }
}


/**@brief  Given state of Eddystone beacon, get advertisement parameters. */
static void get_adv_params(ble_gap_adv_params_t * p_adv_params,
                           bool                   non_connectable,
                           bool                   remain_connectable)
{
    // Initialize advertising parameters (used when starting advertising).
    memset(p_adv_params, 0, sizeof(ble_gap_adv_params_t));

    // Non-connectable
    p_adv_params->properties.type = non_connectable
                                  ? BLE_GAP_ADV_TYPE_NONCONNECTABLE_NONSCANNABLE_UNDIRECTED
                                  : BLE_GAP_ADV_TYPE_CONNECTABLE_SCANNABLE_UNDIRECTED;
    p_adv_params->p_peer_addr     = NULL; // Undirected advertisement.
    p_adv_params->filter_policy   = BLE_GAP_ADV_FP_ANY;
    p_adv_params->interval        = non_connectable ? m_adv_interval : APP_CFG_CONNECTABLE_ADV_INTERVAL_MS;
    p_adv_params->duration        = non_connectable
                                  ? APP_CFG_NON_CONN_ADV_TIMEOUT
                                  : (remain_connectable ? 0 : APP_CFG_CONNECTABLE_ADV_TIMEOUT);
    p_adv_params->primary_phy     = BLE_GAP_PHY_1MBPS;
}


/**@brief  Update advertisement data and start connectable advertisements. */
static void connectable_adv_start(void)
{
    ble_gap_adv_params_t connectable_adv_params;
    ble_advdata_t        scrsp_data;
    ble_uuid_t           scrp_uuids[] = {{BLE_UUID_ESCS_SERVICE, m_ecs_uuid_type}};

    memset(&scrsp_data, 0, sizeof(scrsp_data));
    scrsp_data.name_type               = BLE_ADVDATA_FULL_NAME;
    scrsp_data.include_appearance      = false;
    scrsp_data.uuids_complete.uuid_cnt = sizeof(scrp_uuids) / sizeof(scrp_uuids[0]);
    scrsp_data.uuids_complete.p_uuids  = scrp_uuids;

    m_adv_data.scan_rsp_data.p_data = m_enc_scan_response_data;
    m_adv_data.scan_rsp_data.len    = BLE_GAP_ADV_SET_DATA_SIZE_MAX;

    // As the data to be written does not depend on the slot_no, we can safely send
    es_adv_frame_fill_connectable_adv_data(&scrsp_data, &m_adv_data);

    get_adv_params(&connectable_adv_params, false, m_remain_connectable);
    adv_start(&connectable_adv_params);

    invoke_callback(ES_ADV_EVT_CONNECTABLE_ADV_STARTED);
}


static void adv_stop(void)
{
    ret_code_t err_code;

    err_code = sd_ble_gap_adv_stop(*mp_adv_handle);
    if (err_code != NRF_ERROR_INVALID_STATE)
    {
        APP_ERROR_CHECK(err_code);
    }

    es_adv_timing_stop();
}


static void adv_restart(void)
{
    if (!m_remain_connectable)
    {
        es_adv_start_non_connctable_adv();
    }

    else
    {
        connectable_adv_start();
    }
}


/**@brief Function handling events from @ref es_adv_timing.c.
 *
 * @param[in] p_evt Advertisement timing event.
 */
static void adv_timing_callback(const es_adv_timing_evt_t * p_evt)
{
    ret_code_t            err_code;
    ble_gap_adv_params_t  non_connectable_adv_params;
    const es_slot_reg_t * p_reg = es_slot_get_registry();

    // As new advertisement data will be loaded, stop advertising.
    err_code = sd_ble_gap_adv_stop(*mp_adv_handle);
    if (err_code != NRF_ERROR_INVALID_STATE && err_code != BLE_ERROR_INVALID_ADV_HANDLE)
    {
        APP_ERROR_CHECK(err_code);
    }

    // If a non-eTLM frame is to be advertised.
    if (p_evt->evt_id == ES_ADV_TIMING_EVT_ADV_SLOT)
    {
        err_code = sd_ble_gap_tx_power_set(BLE_GAP_TX_POWER_ROLE_ADV, 0, p_reg->slots[p_evt->slot_no].radio_tx_pwr);
        if (err_code != BLE_ERROR_INVALID_ADV_HANDLE)
        {
            APP_ERROR_CHECK(err_code);
        }
            es_adv_frame_fill_non_connectable_adv_data(p_evt->slot_no, false, &m_adv_data);
        }

    // If an eTLM frame is to be advertised
    else if (p_evt->evt_id == ES_ADV_TIMING_EVT_ADV_ETLM)
    {
        err_code = sd_ble_gap_tx_power_set(BLE_GAP_TX_POWER_ROLE_ADV, 0, p_reg->slots[p_reg->tlm_slot].radio_tx_pwr);
        APP_ERROR_CHECK(err_code);

        es_adv_frame_fill_non_connectable_adv_data(p_evt->slot_no, true, &m_adv_data);
    }

    invoke_callback(ES_ADV_EVT_NON_CONN_ADV);

    get_adv_params(&non_connectable_adv_params, true, m_remain_connectable);
    adv_start(&non_connectable_adv_params);
}


void es_adv_start_connectable_adv(void)
{
    if (!m_is_connected)
    {
        adv_stop();

        connectable_adv_start();
    }
}


void es_adv_start_non_connctable_adv(void)
{
    es_adv_timing_start(m_adv_interval);
}


void es_adv_remain_connectable_set(bool remain_connectable)
{
    m_remain_connectable = remain_connectable;
}


bool es_adv_remain_connectable_get(void)
{
    return m_remain_connectable;
}


void es_adv_on_ble_evt(ble_evt_t const * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            m_is_connected = true;

            // The beacon must provide these advertisements for the client to see updated values
            // during the connection.
            es_adv_start_non_connctable_adv();
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            m_is_connected = false;

            // Stop all advertising to give some time for writing to flash.
            adv_stop();
            adv_restart();
            break;

        case BLE_GAP_EVT_ADV_SET_TERMINATED:
            if (p_ble_evt->evt.gap_evt.params.adv_set_terminated.reason == BLE_GAP_EVT_ADV_SET_TERMINATED_REASON_TIMEOUT &&
                !m_is_connected)
            {
                invoke_callback(ES_ADV_EVT_CONNECTABLE_ADV_STOPPED);

                adv_restart();
            }
            break;

        default:
            break;
    }
}


void es_adv_interval_set(nrf_ble_escs_adv_interval_t interval)
{
    const es_slot_reg_t * p_reg = es_slot_get_registry();
    uint16_t min_valid_adv_interval;

    bool eTLM_required = (p_reg->num_configured_eid_slots > 0) && (p_reg->tlm_configured);

    min_valid_adv_interval = eTLM_required ?                                                               \
                                    p_reg->num_configured_slots * (APP_CONFIG_ADV_FRAME_SPACING_MS_MIN +   \
                                                                   APP_CONFIG_ADV_FRAME_ETLM_SPACING_MS)   \
                                           :                                                               \
                                    p_reg->num_configured_slots * APP_CONFIG_ADV_FRAME_SPACING_MS_MIN;

    m_adv_interval = (interval > min_valid_adv_interval) ? interval : min_valid_adv_interval;

#ifdef APP_CONFIG_ADV_INTERVAL_MS_MAX
    if (m_adv_interval > APP_CONFIG_ADV_INTERVAL_MS_MAX)
    {
        m_adv_interval = APP_CONFIG_ADV_INTERVAL_MS_MAX;
    }
#endif // APP_CONFIG_ADV_INTERVAL_MS_MAX
}


nrf_ble_escs_adv_interval_t es_adv_interval_get(void)
{
    return m_adv_interval;
}


void es_adv_init(uint8_t                     ecs_uuid_type,
                 es_adv_evt_handler_t        adv_event_handler,
                 nrf_ble_escs_adv_interval_t adv_interval,
                 bool                        remain_connectable,
                 uint8_t * const p_adv_handle)
{
    m_ecs_uuid_type      = ecs_uuid_type;
    m_adv_evt_handler    = adv_event_handler;
    m_is_connected       = false;
    m_remain_connectable = remain_connectable;
    m_adv_interval       = adv_interval;
    mp_adv_handle        = p_adv_handle;

    es_tlm_init();

    es_adv_timing_init(adv_timing_callback);
}

void es_adv_timers_init(void)
{
    es_adv_timing_timers_init();
}
