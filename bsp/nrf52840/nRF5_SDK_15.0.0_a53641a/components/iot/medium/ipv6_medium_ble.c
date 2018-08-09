/**
 * Copyright (c) 2015-2018 - 2018, Nordic Semiconductor ASA
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
#include "boards.h"
#include "ipv6_medium.h"
#include "ipv6_medium_ble.h"
#include "ble_advdata.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_ipsp.h"
#include "sdk_config.h"
#include "nrf_sdm.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#ifdef COMMISSIONING_ENABLED
#include "commissioning.h"
#endif // COMMISSIONING_ENABLED

#define PUBLIC_BLE_GAP_ADDR_CREATE_FROM_EUI64(ble_gap_addr, eui64, ble_gap_addr_type)              \
             ble_gap_addr[0] = eui64[7];                                                           \
             ble_gap_addr[1] = eui64[6];                                                           \
             ble_gap_addr[2] = eui64[5];                                                           \
             ble_gap_addr[3] = eui64[2];                                                           \
             ble_gap_addr[4] = eui64[1];                                                           \
             ble_gap_addr[5] = 0x00;                                                               \
             ble_gap_addr_type = BLE_GAP_ADDR_TYPE_PUBLIC;

#define IOT_TIMER_DISABLE_API_PARAM_CHECK    0

#if (IOT_TIMER_DISABLE_API_PARAM_CHECK == 0)

#define NULL_PARAM_CHECK(PARAM)                                                                    \
        if ((PARAM) == NULL)                                                                       \
        {                                                                                          \
            return (NRF_ERROR_NULL);                                                               \
        }

#else // IOT_TIMER_DISABLE_API_PARAM_CHECK

#define NULL_PARAM_CHECK(PARAM)

#endif //IOT_TIMER_DISABLE_API_PARAM_CHECK

#define BLE_IPV6_MEDIUM_BLE_OBSERVER_PRIO   1                                                       /**< BLE observer priority. */
#define BLE_IPSP_TAG                        35                                                      /**< Identifies the L2CAP configuration used with SoftDevice. */


static ipv6_medium_instance_id_t         m_module_instance_id = 0x01;                               /**< Module instance identifier. As of today, only a single instance is supported. */
static ipv6_medium_evt_handler_t         m_ipv6_medium_evt_handler;                                 /**< Pointer to the event handler procedure of the parent layer. */
static ipv6_medium_error_handler_t       m_ipv6_medium_error_handler;                               /**< Pointer to the error handler procedure of the parent layer. */
static ble_gap_addr_t                    m_local_ble_addr;                                          /**< Local BT device address. */
static ipv6_medium_ble_gap_params_t    * m_p_node_gap_params;                                       /**< Pointer to advertising parameters to be used. */
static ipv6_medium_ble_adv_params_t    * m_p_node_adv_params;                                       /**< Pointer to GAP parameters to be used. */

#ifndef COMMISSIONING_ENABLED
static ipv6_medium_ble_gap_params_t      m_gap_params;                                              /**< Advertising parameters w/o commissioning. */
static ipv6_medium_ble_adv_params_t      m_adv_params;                                              /**< GAP parameters w/o commissioning. */
static ble_uuid_t                        m_adv_uuids[] =
                                             {
                                                 {BLE_UUID_IPSP_SERVICE, BLE_UUID_TYPE_BLE}
                                             };                                                     /**< List of available service UUIDs in advertisement data. */
#else // COMMISSIONING_ENABLED
static uint16_t                          m_conn_handle = BLE_CONN_HANDLE_INVALID;                   /**< Handle of the active connection. */
static bool                              m_connectable_mode_active = false;                         /**< Indicates if the node is in connectable mode. */
static commissioning_id_mode_cb_t        m_commissioning_id_mode_cb;
static commissioning_poweroff_cb_t       m_commissioning_power_off_cb;
static bool                              m_adv_params_applied = false;                              /**< Indicates if advertising (and GAP) parameters have been applied. */
#endif // COMMISSIONING_ENABLED

static uint8_t                           m_adv_handle = BLE_GAP_ADV_SET_HANDLE_NOT_SET;             /**< Advertising handle used to identify an advertising set. */
static uint8_t                           m_enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];              /**< Buffer for storing an encoded advertising set. */

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
        .p_data = NULL,
        .len    = 0
        
    }
};

#if IPV6_MEDIUM_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME ipv6_medium

#define NRF_LOG_LEVEL       IPV6_MEDIUM_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  IPV6_MEDIUM_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR IPV6_MEDIUM_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define IPV6M_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define IPV6M_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define IPV6M_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#define IPV6M_ENTRY()                       IPV6M_TRC(">> %s", __func__)
#define IPV6M_EXIT()                        IPV6M_TRC("<< %s", __func__)

#else // IPV6_MEDIUM_CONFIG_LOG_ENABLED

#define IPV6M_TRC(...)                                                                           /**< Disables traces. */
#define IPV6M_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define IPV6M_ERR(...)                                                                           /**< Disables error logs. */

#define IPV6M_ENTRY(...)
#define IPV6M_EXIT(...)

#endif // IPV6_MEDIUM_CONFIG_LOG_ENABLED


#ifndef COMMISSIONING_ENABLED

/**@brief Function for setting advertisement parameters.
 *
 * @details These parameters are applied if the Commissioning module is
 *          not used or in Joining mode.
 */
static void adv_params_set(void)
{
    IPV6M_ENTRY();
    memset(&m_adv_params, 0x00, sizeof(m_adv_params));

    m_adv_params.advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    m_adv_params.advdata.flags                   = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;
    m_adv_params.advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    m_adv_params.advdata.uuids_complete.p_uuids  = m_adv_uuids;

    m_adv_params.advparams.properties.type = BLE_GAP_ADV_TYPE_CONNECTABLE_SCANNABLE_UNDIRECTED;
    m_adv_params.advparams.p_peer_addr     = NULL; // Undirected advertisement.
    m_adv_params.advparams.filter_policy   = BLE_GAP_ADV_FP_ANY;
    m_adv_params.advparams.interval        = APP_ADV_ADV_INTERVAL;
    m_adv_params.advparams.duration        = APP_ADV_DURATION;

    IPV6M_EXIT();
}

/**@brief Function for setting GAP parameters.
 *
 * @details These parameters are applied if the Commissioning module is
 *          not used or in Joining mode.
 */
static void gap_params_set(void)
{
    memset(&m_gap_params, 0x00, sizeof(m_gap_params));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&m_gap_params.sec_mode);

    m_gap_params.appearance = BLE_APPEARANCE_UNKNOWN;

    m_gap_params.p_dev_name   = (const uint8_t *)DEVICE_NAME;
    m_gap_params.dev_name_len = strlen(DEVICE_NAME);

    m_gap_params.gap_conn_params.min_conn_interval = (uint16_t)MIN_CONN_INTERVAL;
    m_gap_params.gap_conn_params.max_conn_interval = (uint16_t)MAX_CONN_INTERVAL;
    m_gap_params.gap_conn_params.slave_latency     = SLAVE_LATENCY;
    m_gap_params.gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;
}

#endif // COMMISSIONING_ENABLED


/**@brief Function for applying the advertisement parameters.
 *
 * @details Encodes the required advertising data and passes it to the stack.
 */
static void adv_params_apply(void)
{
    uint32_t err_code;


    err_code = ble_advdata_encode(&m_p_node_adv_params->advdata, m_adv_data.adv_data.p_data, &m_adv_data.adv_data.len);
    APP_ERROR_CHECK(err_code);
#ifndef COMMISSIONING_ENABLED
    err_code = sd_ble_gap_adv_set_configure(&m_adv_handle, &m_adv_data, &m_adv_params.advparams);
    APP_ERROR_CHECK(err_code);
#else
    err_code = sd_ble_gap_adv_set_configure(&m_adv_handle, &m_adv_data, &m_p_node_adv_params->advparams);
    APP_ERROR_CHECK(err_code);
#endif
}


/**@brief Function for applying the GAP configuration.
 *
 * @details This function sets up all the necessary GAP (Generic Access Profile) parameters of the
 *          device including the device name, appearance, and the preferred connection parameters.
 */
static void gap_params_apply(void)
{
    uint32_t err_code;

    err_code = sd_ble_gap_device_name_set(&m_p_node_gap_params->sec_mode, \
                                          m_p_node_gap_params->p_dev_name, \
                                          m_p_node_gap_params->dev_name_len);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ble_gap_appearance_set(m_p_node_gap_params->appearance);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ble_gap_ppcp_set(&m_p_node_gap_params->gap_conn_params);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling the application's BLE Stack events and
 *        passing them on to the applications as generic transport medium events.
 *
 * @param[in]   p_ble_evt   Bluetooth stack event.
 */
static void on_ble_evt(ble_evt_t const * p_ble_evt)
{
    ipv6_medium_evt_t ipv6_medium_evt;

    memset(&ipv6_medium_evt, 0x00, sizeof(ipv6_medium_evt));
    ipv6_medium_evt.ipv6_medium_instance_id.ipv6_medium_instance_id   = m_module_instance_id;
    ipv6_medium_evt.ipv6_medium_instance_id.ipv6_medium_instance_type = IPV6_MEDIUM_ID_BLE;
    ipv6_medium_evt.medium_specific.ble.p_ble_evt                     = (ble_evt_t*)p_ble_evt;

    ipv6_medium_error_t ipv6_medium_error;
    memset(&ipv6_medium_error, 0x00, sizeof(ipv6_medium_error));
    ipv6_medium_error.ipv6_medium_instance_id.ipv6_medium_instance_id   = m_module_instance_id;
    ipv6_medium_error.ipv6_medium_instance_id.ipv6_medium_instance_type = IPV6_MEDIUM_ID_BLE;

    bool do_notify_event = false;
    bool do_notify_error = false;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
#ifdef COMMISSIONING_ENABLED
            m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
#endif // COMMISSIONING_ENABLED
            ipv6_medium_evt.ipv6_medium_evt_id = IPV6_MEDIUM_EVT_CONN_UP;
            do_notify_event = true;

            break;
        }
        case BLE_GAP_EVT_DISCONNECTED:
        {
#ifdef COMMISSIONING_ENABLED
            m_conn_handle = BLE_CONN_HANDLE_INVALID;
#endif // COMMISSIONING_ENABLED
            ipv6_medium_evt.ipv6_medium_evt_id = IPV6_MEDIUM_EVT_CONN_DOWN;
            do_notify_event = true;

            break;
        }
        case BLE_GAP_EVT_ADV_SET_TERMINATED:
        {
            if (p_ble_evt->evt.gap_evt.params.adv_set_terminated.reason == BLE_GAP_EVT_ADV_SET_TERMINATED_REASON_TIMEOUT)
            {
                ipv6_medium_evt.ipv6_medium_evt_id = IPV6_MEDIUM_EVT_CONNECTABLE_MODE_EXIT;
                do_notify_event = true;
            }
            else
            {
                // This is not necessarily an error, only added here to show error handler usage.
                ipv6_medium_error.medium_specific.ble.dummy_value = 0x13;
                do_notify_error = true;
            }
            break;
        }
        default:
        {
            ipv6_medium_evt.ipv6_medium_evt_id = IPV6_MEDIUM_EVT_PHY_SPECIFIC;
            do_notify_event = true;

            break;
        }
    }

    ble_ipsp_evt_handler(p_ble_evt);

    if (do_notify_event == true)
    {
        m_ipv6_medium_evt_handler(&ipv6_medium_evt);
    }
    if (do_notify_error == true)
    {
        m_ipv6_medium_error_handler(&ipv6_medium_error);
    }
}

/*
 * @brief Function for handling BLE events.
 *
 * @param[in]   p_ble_evt       Event received from the BLE stack.
 * @param[in]   p_context       Context.
 */
static void ble_evt_handler(const ble_evt_t * p_ble_evt, void * p_context)
{
    UNUSED_PARAMETER(p_context);
#ifdef COMMISSIONING_ENABLED
    commissioning_ble_evt_handler(p_ble_evt);
    ble_ncfgs_ble_evt_handler(p_ble_evt);
#endif // COMMISSIONING_ENABLED

    on_ble_evt(p_ble_evt);
}




/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
static uint32_t ble_stack_init(void)
{
    ret_code_t    err_code;
    uint32_t      ram_start = 0;
    ble_cfg_t     ble_cfg;

    err_code = nrf_sdh_enable_request();

    if (err_code == NRF_SUCCESS)
    {
        // Fetch the start address of the application RAM.
        err_code = nrf_sdh_ble_app_ram_start_get(&ram_start);
    }

    if (err_code == NRF_SUCCESS)
    {
        // Configure the maximum number of connections.
        memset(&ble_cfg, 0, sizeof(ble_cfg));
        ble_cfg.gap_cfg.role_count_cfg.periph_role_count  = BLE_IPSP_MAX_CHANNELS;
        ble_cfg.gap_cfg.role_count_cfg.central_role_count = 0;
        ble_cfg.gap_cfg.role_count_cfg.central_sec_count  = 0;
        err_code = sd_ble_cfg_set(BLE_GAP_CFG_ROLE_COUNT, &ble_cfg, ram_start);
    }

    if (err_code == NRF_SUCCESS)
    {
        memset(&ble_cfg, 0, sizeof(ble_cfg));

        // Configure total number of connections.
        ble_cfg.conn_cfg.conn_cfg_tag                     = BLE_IPSP_TAG;
        ble_cfg.conn_cfg.params.gap_conn_cfg.conn_count   = BLE_IPSP_MAX_CHANNELS;
        ble_cfg.conn_cfg.params.gap_conn_cfg.event_length = BLE_GAP_EVENT_LENGTH_DEFAULT;
        err_code = sd_ble_cfg_set(BLE_CONN_CFG_GAP, &ble_cfg, ram_start);

    }

    if (err_code ==  NRF_SUCCESS)
    {
        memset(&ble_cfg, 0, sizeof(ble_cfg));

        // Configure the number of custom UUIDS.
#ifdef COMMISSIONING_ENABLED
        ble_cfg.common_cfg.vs_uuid_cfg.vs_uuid_count = 1;
#else
        ble_cfg.common_cfg.vs_uuid_cfg.vs_uuid_count = 0;
#endif // COMMISSIONING_ENABLED

        err_code = sd_ble_cfg_set(BLE_COMMON_CFG_VS_UUID, &ble_cfg, ram_start);
    }

    if (err_code == NRF_SUCCESS)
    {
        memset(&ble_cfg, 0, sizeof(ble_cfg));

        // Set L2CAP channel configuration
        ble_cfg.conn_cfg.conn_cfg_tag                        = BLE_IPSP_TAG;
        ble_cfg.conn_cfg.params.l2cap_conn_cfg.rx_mps        = BLE_IPSP_RX_MPS;
        ble_cfg.conn_cfg.params.l2cap_conn_cfg.rx_queue_size = BLE_IPSP_RX_BUFFER_COUNT;
        ble_cfg.conn_cfg.params.l2cap_conn_cfg.tx_mps        = BLE_IPSP_TX_MPS;
        ble_cfg.conn_cfg.params.l2cap_conn_cfg.tx_queue_size = 1;
        ble_cfg.conn_cfg.params.l2cap_conn_cfg.ch_count      = 1; // One IPSP channel per link.
        err_code = sd_ble_cfg_set(BLE_CONN_CFG_L2CAP, &ble_cfg, ram_start);
    }

    if (err_code == NRF_SUCCESS)
    {
        memset(&ble_cfg, 0, sizeof(ble_cfg));

        // Set the ATT table size.
#ifdef COMMISSIONING_ENABLED
        ble_cfg.gatts_cfg.attr_tab_size.attr_tab_size = 1024;
#else
        ble_cfg.gatts_cfg.attr_tab_size.attr_tab_size = 256;
#endif // COMMISSIONING_ENABLED
        err_code = sd_ble_cfg_set(BLE_GATTS_CFG_ATTR_TAB_SIZE, &ble_cfg, ram_start);
    }

    if (err_code ==  NRF_SUCCESS)
    {
        err_code = nrf_sdh_ble_enable(&ram_start);
    }

    NRF_SDH_BLE_OBSERVER(m_ble_evt_observer, BLE_IPV6_MEDIUM_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);

    return err_code;
}


uint32_t ipv6_medium_connectable_mode_enter(ipv6_medium_instance_id_t ipv6_medium_instance_id)
{
    IPV6M_ENTRY();

    if (ipv6_medium_instance_id != m_module_instance_id)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

#ifdef COMMISSIONING_ENABLED
    if (m_adv_params_applied == false)
    {
        // Apply advertising (and GAP) parameters, if not applied when node mode changed.
        commissioning_gap_params_get(&m_p_node_gap_params);
        commissioning_adv_params_get(&m_p_node_adv_params);
        gap_params_apply();
        adv_params_apply();
    }
    m_adv_params_applied = false;
#endif // COMMISSIONING_ENABLED

    adv_params_apply();

    uint32_t err_code = sd_ble_gap_adv_start(m_adv_handle, BLE_IPSP_TAG);
#ifdef COMMISSIONING_ENABLED
    if (err_code == NRF_SUCCESS)
    {
        m_connectable_mode_active = true;
    }
#endif // COMMISSIONING_ENABLED
    IPV6M_EXIT();
    return err_code;
}


uint32_t ipv6_medium_connectable_mode_exit(ipv6_medium_instance_id_t ipv6_medium_instance_id)
{
    if (ipv6_medium_instance_id != m_module_instance_id)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    uint32_t err_code = sd_ble_gap_adv_stop(m_adv_handle);
#ifdef COMMISSIONING_ENABLED
    if (err_code == NRF_SUCCESS)
    {
        m_connectable_mode_active = false;
    }
#endif // COMMISSIONING_ENABLED
    return err_code;
}


uint32_t ipv6_medium_eui48_get(ipv6_medium_instance_id_t   ipv6_medium_instance_id, \
                               eui48_t                   * p_ipv6_medium_eui48)
{
    if (ipv6_medium_instance_id != m_module_instance_id)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    ble_gap_addr_t local_ble_addr;
    uint32_t err_code = sd_ble_gap_addr_get(&local_ble_addr);

    memcpy(p_ipv6_medium_eui48->identifier, local_ble_addr.addr, EUI_48_SIZE);

    return err_code;
}


uint32_t ipv6_medium_eui48_set(ipv6_medium_instance_id_t   ipv6_medium_instance_id, \
                               eui48_t                   * p_ipv6_medium_eui48)
{
    if (ipv6_medium_instance_id != m_module_instance_id)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    if (p_ipv6_medium_eui48->identifier[5] != 0x00)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    m_local_ble_addr.addr_type = BLE_GAP_ADDR_TYPE_PUBLIC;
    memcpy(m_local_ble_addr.addr, p_ipv6_medium_eui48->identifier, EUI_48_SIZE);

    return sd_ble_gap_addr_set(&m_local_ble_addr);
}


uint32_t ipv6_medium_eui64_get(ipv6_medium_instance_id_t   ipv6_medium_instance_id, \
                               eui64_t                   * p_ipv6_medium_eui64)
{
    if (ipv6_medium_instance_id != m_module_instance_id)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    ble_gap_addr_t local_ble_addr;

    uint32_t err_code = sd_ble_gap_addr_get(&local_ble_addr);
    APP_ERROR_CHECK(err_code);

    IPV6_EUI64_CREATE_FROM_EUI48(p_ipv6_medium_eui64->identifier,
                                 local_ble_addr.addr,
                                 local_ble_addr.addr_type);
    return NRF_SUCCESS;
}


uint32_t ipv6_medium_eui64_set(ipv6_medium_instance_id_t   ipv6_medium_instance_id, \
                               eui64_t                   * p_ipv6_medium_eui64)
{
    if (ipv6_medium_instance_id != m_module_instance_id)
    {
        return NRF_ERROR_INVALID_PARAM;
    }
    if ((p_ipv6_medium_eui64->identifier[0] != 0x02)  ||
        (p_ipv6_medium_eui64->identifier[3] != 0xFF)  ||
        (p_ipv6_medium_eui64->identifier[4] != 0xFE))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    ble_gap_addr_t local_ble_addr;

    PUBLIC_BLE_GAP_ADDR_CREATE_FROM_EUI64(local_ble_addr.addr, \
                                          p_ipv6_medium_eui64->identifier, \
                                          local_ble_addr.addr_type);

    return sd_ble_gap_addr_set(&local_ble_addr);
}


#ifdef COMMISSIONING_ENABLED

void commissioning_evt_handler(commissioning_evt_t * p_commissioning_evt)
{
    IPV6M_ENTRY();

    switch (p_commissioning_evt->commissioning_evt_id)
    {
        case COMMISSIONING_EVT_CONFIG_MODE_ENTER:
            // Fall-through.
        case COMMISSIONING_EVT_JOINING_MODE_ENTER:
        {
            m_commissioning_power_off_cb(p_commissioning_evt->power_off_enable_requested);

            if (m_conn_handle != BLE_CONN_HANDLE_INVALID)
            {
                // Making sure that advertising (and GAP) parameters are
                // applied when entering connectable mode the next time.
                m_adv_params_applied = false;
                UNUSED_VARIABLE(sd_ble_gap_disconnect(m_conn_handle, \
                                                      BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION));
            }
            else
            {
                bool do_return_to_connectable_mode = m_connectable_mode_active;
                UNUSED_VARIABLE(ipv6_medium_connectable_mode_exit(m_module_instance_id));

                commissioning_gap_params_get(&m_p_node_gap_params);
                commissioning_adv_params_get(&m_p_node_adv_params);
                gap_params_apply();
                adv_params_apply();
                // Advertising and GAP parameters applied, making sure that
                // it is not repeated when entering connectable mode the next time.
                m_adv_params_applied = true;

                if (do_return_to_connectable_mode == true)
                {
                    // Restart connectable mode, if the node was in connectable mode applying
                    // the new parameters.
                    UNUSED_VARIABLE(ipv6_medium_connectable_mode_enter(m_module_instance_id));
                }
            }

            break;
        }
        case COMMISSIONING_EVT_IDENTITY_MODE_ENTER:
        {
            m_commissioning_id_mode_cb(CMD_IDENTITY_MODE_ENTER);

            break;
        }
        case COMMISSIONING_EVT_IDENTITY_MODE_EXIT:
        {
            m_commissioning_id_mode_cb(CMD_IDENTITY_MODE_EXIT);

            break;
        }
        default:
        {
            // No implementation needed.
            break;
        }
    }

    IPV6M_EXIT();
}

#endif // COMMISSIONING_ENABLED


uint32_t ipv6_medium_init(ipv6_medium_init_params_t * p_init_param,          \
                          ipv6_medium_type_t          desired_medium_type,   \
                          ipv6_medium_instance_t    * p_new_medium_instance)
{
    IPV6M_ENTRY();
    uint32_t err_code = NRF_SUCCESS;
    NULL_PARAM_CHECK(p_init_param->ipv6_medium_evt_handler);
    if (desired_medium_type != IPV6_MEDIUM_ID_BLE)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    m_ipv6_medium_evt_handler   = p_init_param->ipv6_medium_evt_handler;
    m_ipv6_medium_error_handler = p_init_param->ipv6_medium_error_handler;

    p_new_medium_instance->ipv6_medium_instance_type = IPV6_MEDIUM_ID_BLE;
    p_new_medium_instance->ipv6_medium_instance_id   = m_module_instance_id;

    err_code = ble_stack_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

#ifndef COMMISSIONING_ENABLED
    gap_params_set();
    adv_params_set();
    m_p_node_gap_params = &m_gap_params;
    m_p_node_adv_params = &m_adv_params;
    gap_params_apply();
#else // COMMISSIONING_ENABLED
    m_commissioning_id_mode_cb   = p_init_param->commissioning_id_mode_cb;
    m_commissioning_power_off_cb = p_init_param->commissioning_power_off_cb;

    commissioning_init_params_t init_param;
    memset(&init_param, 0x00, sizeof(init_param));
    init_param.commissioning_evt_handler = commissioning_evt_handler;
    uint8_t new_mode;
    err_code = commissioning_init(&init_param, \
                                  &new_mode);

    commissioning_node_mode_change(new_mode);
#endif // COMMISSIONING_ENABLED

    IPV6M_EXIT();
    return err_code;
}
