/**
 * Copyright (c) 2015-2017 - 2018, Nordic Semiconductor ASA
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
#ifdef COMMISSIONING_ENABLED

#include <string.h>
#include "boards.h"
#include "ble_hci.h"
#include "nrf_soc.h"
#include "app_error.h"
#include "fds.h"
#include "ble_advdata.h"
#include "commissioning.h"
#include "nordic_common.h"
#include "ble_srv_common.h"
#include "sdk_config.h"

#define MINIMUM_ACTION_DELAY              2                                                         /**< Delay before executing an action after the control point was written (in seconds). */

#define SEC_PARAM_BOND                    0                                                         /**< Perform bonding. */
#define SEC_PARAM_MITM                    1                                                         /**< Man In The Middle protection required (applicable when display module is detected). */
#define SEC_PARAM_IO_CAPABILITIES         BLE_GAP_IO_CAPS_KEYBOARD_ONLY                             /**< Display I/O capabilities. */
#define SEC_PARAM_OOB                     0                                                         /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE            7                                                         /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE            16                                                        /**< Maximum encryption key size. */

#define COMM_FDS_FILE_ID                  0xCAFE                                                    /**< The ID of the file that the record belongs to. */
#define COMM_FDS_RECORD_KEY               0xBEAF                                                    /**< The record key of FDS record that keeps node settings. */

#define NUMBER_OF_COMMISSIONING_TIMERS    4
#define TIMER_INDEX_DELAYED_ACTION        0
#define TIMER_INDEX_CONFIG_MODE           1
#define TIMER_INDEX_JOINING_MODE          2
#define TIMER_INDEX_IDENTITY_MODE         3

#define SEC_TO_MILLISEC(PARAM) (PARAM * 1000)

static commissioning_settings_t           m_node_settings;                                          /**< All node settings as configured through the Node Configuration Service. */
static commissioning_evt_handler_t        m_commissioning_evt_handler;                              /**< Commissioning event handler of the parent layer. */
static bool                               m_power_off_on_failure = false;                            /**< Power off on failure setting from the last NCFGS event. */
static commissioning_timer_t              m_commissioning_timers[NUMBER_OF_COMMISSIONING_TIMERS];

static ipv6_medium_ble_gap_params_t       m_config_mode_gap_params;                                 /**< Advertising parameters in Config mode. */
static ipv6_medium_ble_adv_params_t       m_config_mode_adv_params;                                 /**< GAP parameters in Config mode. */

static ipv6_medium_ble_gap_params_t       m_joining_mode_gap_params;                                /**< Advertising parameters in Joining mode. */
static ipv6_medium_ble_adv_params_t       m_joining_mode_adv_params;                                /**< GAP parameters in Joining mode. */

static ble_uuid_t                         m_config_mode_adv_uuids[] =          \
                                              {
                                                  {BLE_UUID_NODE_CFG_SERVICE,  \
                                                   BLE_UUID_TYPE_VENDOR_BEGIN}
                                              };                                                    /**< Config mode: List of available service UUIDs in advertisement data. */

static ble_uuid_t                         m_joining_mode_adv_uuids[] = \
                                              {
                                                  {BLE_UUID_IPSP_SERVICE, BLE_UUID_TYPE_BLE}
                                              };                                                    /**< Joining mode: List of available service UUIDs in advertisement data. */

static uint16_t                           m_conn_handle = BLE_CONN_HANDLE_INVALID;                  /**< Handle of the active connection. */
static uint8_t                            m_current_mode = NODE_MODE_NONE;                          /**< Current mode value. */
static uint8_t                            m_next_mode = NODE_MODE_NONE;                             /**< Value of the mode the node will enter when the timeout handler of m_delayed_action_timer is triggered. */

#if (FDS_ENABLED == 1)
static fds_record_desc_t                  m_fds_record_desc;                                        /**< Descriptor of FDS record. */
#endif

#define COMM_ENABLE_LOGS          1                                                                 /**< Set to 0 to disable debug trace in the module. */

#if COMMISSIONING_CONFIG_LOG_ENABLED

#define NRF_LOG_MODULE_NAME commissioning

#define NRF_LOG_LEVEL       COMMISSIONING_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  COMMISSIONING_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR COMMISSIONING_CONFIG_DEBUG_COLOR

#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define COMM_TRC     NRF_LOG_DEBUG                                                              /**< Used for getting trace of execution in the module. */
#define COMM_ERR     NRF_LOG_ERROR                                                              /**< Used for logging errors in the module. */
#define COMM_DUMP    NRF_LOG_HEXDUMP_DEBUG                                                      /**< Used for dumping octet information to get details of bond information etc. */

#define COMM_ENTRY()                       COMM_TRC(">> %s", __func__)
#define COMM_EXIT()                        COMM_TRC("<< %s", __func__)

#else // COMMISSIONING_CONFIG_LOG_ENABLED

#define COMM_TRC(...)                                                                           /**< Disables traces. */
#define COMM_DUMP(...)                                                                          /**< Disables dumping of octet streams. */
#define COMM_ERR(...)                                                                           /**< Disables error logs. */

#define COMM_ENTRY(...)
#define COMM_EXIT(...)

#endif // COMMISSIONING_CONFIG_LOG_ENABLED


/**@brief Function for validating all node settings.
 */
static bool settings_are_valid()
{
    uint8_t tmp = m_node_settings.poweron_mode;
    if (tmp == 0xFF)
    {
        return false;
    }
    else
    {
        return true;
    }
}

#if (FDS_ENABLED == 1)
/**@brief Function for updating the node settings in persistent memory.
 */
static uint32_t persistent_settings_update(void)
{
    uint32_t err_code;

    fds_find_token_t token;
    memset(&token, 0, sizeof(token));

    fds_record_t record;
    memset(&record, 0, sizeof(record));

    record.file_id           = COMM_FDS_FILE_ID;
    record.key               = COMM_FDS_RECORD_KEY;
    record.data.p_data       = &m_node_settings;
    record.data.length_words = ALIGN_NUM(4, sizeof(commissioning_settings_t))/sizeof(uint32_t);

    // Try to find FDS record with node settings.
    err_code = fds_record_find(COMM_FDS_FILE_ID, COMM_FDS_RECORD_KEY, &m_fds_record_desc, &token);
    if (err_code == FDS_SUCCESS)
    {
        err_code = fds_record_update(&m_fds_record_desc, &record);
    }
    else
    {

        err_code = fds_record_write(&m_fds_record_desc, &record);
    }

    if (err_code == FDS_ERR_NO_SPACE_IN_FLASH)
    {
        // Run garbage collector to reclaim the flash space that is occupied by records that have been deleted,
        // or that failed to be completely written due to, for example, a power loss.
        err_code = fds_gc();
    }

    return err_code;
}


/**@brief Function for loading node settings from the persistent memory.
 */
static void persistent_settings_load(void)
{
    uint32_t           err_code = FDS_SUCCESS;
    fds_flash_record_t record;

    fds_find_token_t token;
    memset(&token, 0, sizeof(token));

    // Try to find FDS record with node settings.
    err_code = fds_record_find(COMM_FDS_FILE_ID, COMM_FDS_RECORD_KEY, &m_fds_record_desc, &token);
    if (err_code == FDS_SUCCESS)
    {
        err_code = fds_record_open(&m_fds_record_desc, &record);
        if (err_code == FDS_SUCCESS)
        {
            if (record.p_data)
            {
                memcpy(&m_node_settings, record.p_data, sizeof(m_node_settings));
            }
        }
    }
}


/**@brief Function for clearing node settings from the persistent memory.
 */
static void persistent_settings_clear(void)
{
    fds_record_delete(&m_fds_record_desc);
}

/**@brief Function for handling File Data Storage events.
 */
static void persistent_settings_cb(fds_evt_t const * p_evt)
{
    if (p_evt->id == FDS_EVT_GC)
    {
        if (settings_are_valid())
        {
            persistent_settings_update();
        }
    }
}


/**@brief Function for initializing the File Data Storage module.
 */
static uint32_t persistent_settings_init(void)
{
    uint32_t err_code;

    err_code = fds_init();
    if (err_code == FDS_SUCCESS)
    {
        err_code = fds_register(persistent_settings_cb);
    }

    return err_code;
}
#endif


/**@brief Function for setting advertisement parameters in Config mode.
 */
static void config_mode_adv_params_set(void)
{
    COMM_ENTRY();
    memset(&m_config_mode_adv_params, 0x00, sizeof(m_config_mode_adv_params));

    m_config_mode_adv_params.advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    m_config_mode_adv_params.advdata.include_appearance      = false;
    m_config_mode_adv_params.advdata.flags                   = \
        BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    m_config_mode_adv_params.advdata.uuids_complete.uuid_cnt = \
        sizeof(m_config_mode_adv_uuids) / sizeof(m_config_mode_adv_uuids[0]);
    m_config_mode_adv_params.advdata.uuids_complete.p_uuids  = m_config_mode_adv_uuids;
    m_config_mode_adv_params.advdata.p_manuf_specific_data   = NULL;

    if (m_node_settings.id_data_store.identity_data_len > 0)
    {
        m_config_mode_adv_params.sr_man_specific_data.data.size          = \
            m_node_settings.id_data_store.identity_data_len;
        m_config_mode_adv_params.sr_man_specific_data.data.p_data        = \
            m_node_settings.id_data_store.identity_data;
        m_config_mode_adv_params.sr_man_specific_data.company_identifier = \
            COMPANY_IDENTIFIER;
        m_config_mode_adv_params.srdata.p_manuf_specific_data            = \
            &m_config_mode_adv_params.sr_man_specific_data;
    }
    else
    {
        m_config_mode_adv_params.srdata.p_manuf_specific_data = NULL;
    }

    m_config_mode_adv_params.advparams.properties.type = BLE_GAP_ADV_TYPE_CONNECTABLE_SCANNABLE_UNDIRECTED;
    m_config_mode_adv_params.advparams.p_peer_addr     = NULL;                             // Undirected advertisement.
    m_config_mode_adv_params.advparams.filter_policy   = BLE_GAP_ADV_FP_ANY;
    m_config_mode_adv_params.advparams.interval        = CONFIG_MODE_ADV_ADV_INTERVAL;
    m_config_mode_adv_params.advparams.duration        = CONFIG_MODE_ADV_TIMEOUT;

    COMM_EXIT();
}


/**@brief Function for setting GAP parameters in Config mode.
 */
static void config_mode_gap_params_set(void)
{
    COMM_ENTRY();

    memset(&m_config_mode_gap_params, 0x00, sizeof(m_config_mode_gap_params));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&m_config_mode_gap_params.sec_mode);

    m_config_mode_gap_params.p_dev_name   = (const uint8_t *)CONFIG_MODE_DEVICE_NAME;
    m_config_mode_gap_params.dev_name_len = strlen(CONFIG_MODE_DEVICE_NAME);

    m_config_mode_gap_params.gap_conn_params.min_conn_interval = \
                                                           (uint16_t)CONFIG_MODE_MIN_CONN_INTERVAL;
    m_config_mode_gap_params.gap_conn_params.max_conn_interval = \
                                                           (uint16_t)CONFIG_MODE_MAX_CONN_INTERVAL;
    m_config_mode_gap_params.gap_conn_params.slave_latency     = CONFIG_MODE_SLAVE_LATENCY;
    m_config_mode_gap_params.gap_conn_params.conn_sup_timeout  = CONFIG_MODE_CONN_SUP_TIMEOUT;

    COMM_EXIT();
}


/**@brief Function for setting advertisement parameters in Joining mode.
 */
static void joining_mode_adv_params_set(void)
{
    COMM_ENTRY();

    memset(&m_joining_mode_adv_params, 0x00, sizeof(m_joining_mode_adv_params));

    if (m_node_settings.ssid_store.ssid_len > 0)
    {
        m_joining_mode_adv_params.adv_man_specific_data.data.size          = \
            m_node_settings.ssid_store.ssid_len;
        m_joining_mode_adv_params.adv_man_specific_data.data.p_data        = \
            m_node_settings.ssid_store.ssid;
        m_joining_mode_adv_params.adv_man_specific_data.company_identifier = \
            COMPANY_IDENTIFIER;
    }

    m_joining_mode_adv_params.advdata.name_type               = BLE_ADVDATA_NO_NAME;
    m_joining_mode_adv_params.advdata.include_appearance      = false;
    m_joining_mode_adv_params.advdata.flags                   = \
        BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;
    m_joining_mode_adv_params.advdata.uuids_complete.uuid_cnt = \
        sizeof(m_joining_mode_adv_uuids) / sizeof(m_joining_mode_adv_uuids[0]);
    m_joining_mode_adv_params.advdata.uuids_complete.p_uuids  = m_joining_mode_adv_uuids;
    if (m_node_settings.ssid_store.ssid_len > 0)
    {
        m_joining_mode_adv_params.advdata.p_manuf_specific_data   = \
            &m_joining_mode_adv_params.adv_man_specific_data;
    }
    else
    {
        m_joining_mode_adv_params.advdata.p_manuf_specific_data = NULL;
    }

    if (m_node_settings.id_data_store.identity_data_len > 0)
    {
        m_joining_mode_adv_params.sr_man_specific_data.data.size          = \
            m_node_settings.id_data_store.identity_data_len;
        m_joining_mode_adv_params.sr_man_specific_data.data.p_data        = \
            m_node_settings.id_data_store.identity_data;
        m_joining_mode_adv_params.sr_man_specific_data.company_identifier = \
            COMPANY_IDENTIFIER;
        m_joining_mode_adv_params.srdata.p_manuf_specific_data            = \
            &m_joining_mode_adv_params.sr_man_specific_data;
    }
    else
    {
        m_joining_mode_adv_params.srdata.p_manuf_specific_data = NULL;
    }

    m_joining_mode_adv_params.advparams.properties.type = BLE_GAP_ADV_TYPE_CONNECTABLE_SCANNABLE_UNDIRECTED;
    m_joining_mode_adv_params.advparams.p_peer_addr     = NULL;                             // Undirected advertisement.
    m_joining_mode_adv_params.advparams.filter_policy   = BLE_GAP_ADV_FP_ANY;
    m_joining_mode_adv_params.advparams.interval        = APP_ADV_ADV_INTERVAL;
    m_joining_mode_adv_params.advparams.duration        = APP_ADV_DURATION;

    COMM_EXIT();
}


/**@brief Function for setting GAP parameters in Joining mode.
 */
static void joining_mode_gap_params_set(void)
{
    COMM_ENTRY();

    memset(&m_joining_mode_gap_params, 0x00, sizeof(m_joining_mode_gap_params));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&m_joining_mode_gap_params.sec_mode);

    m_joining_mode_gap_params.appearance = BLE_APPEARANCE_UNKNOWN;

    m_joining_mode_gap_params.p_dev_name   = (const uint8_t *)DEVICE_NAME;
    m_joining_mode_gap_params.dev_name_len = strlen(DEVICE_NAME);

    m_joining_mode_gap_params.gap_conn_params.min_conn_interval = \
                                                          (uint16_t)JOINING_MODE_MIN_CONN_INTERVAL;
    m_joining_mode_gap_params.gap_conn_params.max_conn_interval = \
                                                          (uint16_t)JOINING_MODE_MAX_CONN_INTERVAL;
    m_joining_mode_gap_params.gap_conn_params.slave_latency     = JOINING_MODE_SLAVE_LATENCY;
    m_joining_mode_gap_params.gap_conn_params.conn_sup_timeout  = JOINING_MODE_CONN_SUP_TIMEOUT;

    COMM_EXIT();
}


/**@brief Function for starting a timer in the Commissioning module.
 *
 */
static void commissioning_timer_start(uint8_t index, uint32_t timeout_sec)
{
    m_commissioning_timers[index].is_timer_running  = true;
    m_commissioning_timers[index].current_value_sec = timeout_sec;
}


/**@brief Function for stopping and re-setting a timer in the Commissioning module.
 *
 */
static void commissioning_timer_stop_reset(uint8_t index)
{
    m_commissioning_timers[index].is_timer_running  = false;
    m_commissioning_timers[index].current_value_sec = 0x00;
}


void commissioning_node_mode_change(uint8_t new_mode)
{
    COMM_ENTRY();

    commissioning_evt_t commissioning_evt;
    memset(&commissioning_evt, 0x00, sizeof(commissioning_evt));
    commissioning_evt.p_commissioning_settings   = &m_node_settings;
    commissioning_evt.power_off_enable_requested = m_power_off_on_failure;

    commissioning_timer_stop_reset(TIMER_INDEX_DELAYED_ACTION);
    commissioning_timer_stop_reset(TIMER_INDEX_CONFIG_MODE);
    commissioning_timer_stop_reset(TIMER_INDEX_JOINING_MODE);

    config_mode_gap_params_set();
    config_mode_adv_params_set();
    joining_mode_gap_params_set();
    joining_mode_adv_params_set();

    m_current_mode = new_mode;

    switch (m_current_mode)
    {
        case NODE_MODE_CONFIG:
        {
            commissioning_evt.commissioning_evt_id = COMMISSIONING_EVT_CONFIG_MODE_ENTER;
            m_commissioning_evt_handler(&commissioning_evt);

            // Start Configuration mode timer.
            COMM_TRC("Config mode timeout: %ld seconds", m_node_settings.config_mode_to);
            commissioning_timer_start(TIMER_INDEX_CONFIG_MODE, m_node_settings.config_mode_to);

            break;
        }
        case NODE_MODE_JOINING:
        {
            commissioning_evt.commissioning_evt_id = COMMISSIONING_EVT_JOINING_MODE_ENTER;
            m_commissioning_evt_handler(&commissioning_evt);

            // Start Joining mode timer.
            COMM_TRC("Joining mode timeout: %ld seconds", m_node_settings.joining_mode_to);
            commissioning_timer_start(TIMER_INDEX_JOINING_MODE, m_node_settings.joining_mode_to);

            break;
        }
        case NODE_MODE_IDENTITY:
        {
            commissioning_evt.commissioning_evt_id = COMMISSIONING_EVT_IDENTITY_MODE_ENTER;
            m_commissioning_evt_handler(&commissioning_evt);

            // Start Identity mode timer.
            COMM_TRC("Identity mode timeout: %ld seconds", m_node_settings.id_mode_to);
            commissioning_timer_start(TIMER_INDEX_IDENTITY_MODE, m_node_settings.id_mode_to);

            break;
        }
        default:
        {
            break;
        }
    }

    COMM_EXIT();
}


/**@brief Function for handling the Delayed action timer timeout.
 *
 * @details This function will be called each time the delayed action timer expires.
 *
 */
static void action_timeout_handler(void)
{
    COMM_ENTRY();

    commissioning_node_mode_change(m_next_mode);

    COMM_EXIT();
}


/**@brief Function for handling the Config mode timer timeout.
 *
 * @details This function will be called each time the Config mode timer expires.
 *
 */
static void config_mode_timeout_handler(void)
{
    COMM_ENTRY();

    switch (m_node_settings.config_mode_failure)
    {
        case NCFGS_SOF_NO_CHANGE:
            // Fall-through.
        case NCFGS_SOF_CONFIG_MODE:
        {
            commissioning_node_mode_change(NODE_MODE_CONFIG);

            break;
        }
        case NCFGS_SOF_PWR_OFF:
        {
            LEDS_OFF(LEDS_MASK);
            // The main timer in Config mode timed out, power off.
            UNUSED_VARIABLE(sd_power_system_off());

            break;
        }
    }

    COMM_EXIT();
}


/**@brief Function for handling the Joining mode timer timeout.
 *
 * @details This function will be called each time the Joining mode timer expires.
 *
 */
void joining_mode_timeout_handler(void)
{
    COMM_ENTRY();

    switch (m_node_settings.joining_mode_failure)
    {
        case NCFGS_SOF_NO_CHANGE:
        {
            commissioning_node_mode_change(NODE_MODE_JOINING);
            break;
        }
        case NCFGS_SOF_PWR_OFF:
        {
            LEDS_OFF(LEDS_MASK);

            UNUSED_VARIABLE(sd_power_system_off());
            break;
        }
        case NCFGS_SOF_CONFIG_MODE:
        {
            commissioning_node_mode_change(NODE_MODE_CONFIG);
            break;
        }
    }

    COMM_EXIT();
}


/**@brief Function for handling the Identity mode timer timeout.
 *
 * @details This function will be called each time the Identity mode timer expires.
 *
 */
void identity_mode_timeout_handler(void)
{
    COMM_ENTRY();

    commissioning_evt_t commissioning_evt;
    memset(&commissioning_evt, 0x00, sizeof(commissioning_evt));
    commissioning_evt.commissioning_evt_id = COMMISSIONING_EVT_IDENTITY_MODE_EXIT;

    m_commissioning_evt_handler(&commissioning_evt);

    COMM_EXIT();
}


void commissioning_joining_mode_timer_ctrl( \
         joining_mode_timer_ctrl_cmd_t joining_mode_timer_ctrl_cmd)
{
    switch (joining_mode_timer_ctrl_cmd)
    {
        case JOINING_MODE_TIMER_STOP_RESET:
        {
            commissioning_timer_stop_reset(TIMER_INDEX_JOINING_MODE);

            break;
        }
        case JOINING_MODE_TIMER_START:
        {
            commissioning_timer_start(TIMER_INDEX_JOINING_MODE, m_node_settings.joining_mode_to);

            break;
        }
    }
}


void commissioning_gap_params_get(ipv6_medium_ble_gap_params_t ** pp_node_gap_params)
{
    switch (m_current_mode)
    {
        case NODE_MODE_JOINING:
        {
            *pp_node_gap_params = &m_joining_mode_gap_params;

            break;
        }
        case NODE_MODE_IDENTITY:
            // Fall-through.
        case NODE_MODE_CONFIG:
        {
            *pp_node_gap_params = &m_config_mode_gap_params;

            break;
        }
    }
}


void commissioning_adv_params_get(ipv6_medium_ble_adv_params_t ** pp_node_adv_params)
{
    switch (m_current_mode)
    {
        case NODE_MODE_JOINING:
        {
            *pp_node_adv_params = &m_joining_mode_adv_params;

            break;
        }
        case NODE_MODE_IDENTITY:
            // Fall-through.
        case NODE_MODE_CONFIG:
        {
            *pp_node_adv_params = &m_config_mode_adv_params;

            break;
        }
    }
}


/**@brief Function for reading all node settings from the persistent storage.
 */
static void read_node_settings(void)
{
    memset(&m_node_settings, 0x00, sizeof(m_node_settings));

#if (FDS_ENABLED == 1)
    persistent_settings_load();
#endif // FDS_ENABLED

    if (m_node_settings.ssid_store.ssid_len > NCFGS_SSID_MAX_LEN)
    {
        m_node_settings.ssid_store.ssid_len = 0;
    }
    if (m_node_settings.keys_store.keys_len > NCFGS_KEYS_MAX_LEN)
    {
        m_node_settings.keys_store.keys_len = 0;
    }
    if (m_node_settings.id_data_store.identity_data_len > NCFGS_IDENTITY_DATA_MAX_LEN)
    {
        m_node_settings.id_data_store.identity_data_len = 0;
    }

    // The duration of each mode needs to be at least 10 second.
    m_node_settings.joining_mode_to = \
        (m_node_settings.joining_mode_to < 10) ? 10 : m_node_settings.joining_mode_to;
    m_node_settings.config_mode_to  = \
        (m_node_settings.config_mode_to  < 10) ? 10 : m_node_settings.config_mode_to;
    m_node_settings.id_mode_to      = \
        (m_node_settings.id_mode_to      < 10) ? 10 : m_node_settings.id_mode_to;
}

#if (COMM_ENABLE_LOGS == 1)
/**@brief Function for printing all node settings.
 */
static void print_node_settings(void)
{
    COMM_TRC("");
    COMM_TRC("     Commissioning settings in memory:");
    COMM_TRC("                           Start mode: %5d", m_node_settings.poweron_mode);
    COMM_TRC("           Mode if Joining Mode fails: %5d", m_node_settings.joining_mode_failure);
    COMM_TRC("      General timeout in Joining Mode: %5ld", m_node_settings.joining_mode_to);
    COMM_TRC("     Mode if Configuration Mode fails: %5d", m_node_settings.config_mode_failure);
    COMM_TRC("General timeout in Configuration Mode: %5ld", m_node_settings.config_mode_to);
    COMM_TRC("               Identity Mode duration: %5ld", m_node_settings.id_mode_to);
    COMM_TRC("                   Stored Keys length: %5d", m_node_settings.keys_store.keys_len);
    COMM_TRC("                          Stored Keys:");
    uint8_t ii;
    for (ii=0; ii<m_node_settings.keys_store.keys_len; ++ii)
    {
        COMM_TRC("0x%02X", m_node_settings.keys_store.keys[ii]);
    }
    COMM_TRC("");
    COMM_TRC("                   Stored SSID length: %5d", m_node_settings.ssid_store.ssid_len);
    COMM_TRC("                          Stored SSID:");
    for (ii=0; ii<m_node_settings.ssid_store.ssid_len; ++ii)
    {
        COMM_TRC("0x%02X", m_node_settings.ssid_store.ssid[ii]);
    }
    COMM_TRC("");
    COMM_TRC("          Stored Identity Data length: %5d", m_node_settings.id_data_store.identity_data_len);
    COMM_TRC("                 Stored Identity Data:");
    for (ii=0; ii<m_node_settings.id_data_store.identity_data_len; ++ii)
    {
        COMM_TRC("0x%02X", m_node_settings.id_data_store.identity_data[ii]);
    }
    COMM_TRC("");
}
#endif // (COMM_ENABLE_LOGS == 1)


void commissioning_settings_clear(void)
{
    COMM_ENTRY();
    memset(&m_node_settings, 0x00, sizeof(m_node_settings));

#if (FDS_ENABLED == 1)
    persistent_settings_clear();
#endif // FDS_ENABLED

    COMM_EXIT();
}


void commissioning_ble_evt_handler(const ble_evt_t * p_ble_evt)
{
    uint32_t err_code;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
        {
            m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            commissioning_timer_stop_reset(TIMER_INDEX_DELAYED_ACTION);
            commissioning_timer_stop_reset(TIMER_INDEX_CONFIG_MODE);

            break;
        }
        case BLE_GAP_EVT_DISCONNECTED:
        {
            m_conn_handle = BLE_CONN_HANDLE_INVALID;
            if (m_current_mode == NODE_MODE_CONFIG)
            {
                commissioning_timer_start(TIMER_INDEX_CONFIG_MODE, \
                                          m_node_settings.config_mode_to);
            }
            if (m_current_mode == NODE_MODE_JOINING)
            {
                commissioning_timer_start(TIMER_INDEX_JOINING_MODE, \
                                          m_node_settings.joining_mode_to);
            }

            break;
        }
        case BLE_GAP_EVT_AUTH_KEY_REQUEST:
        {
            if (m_current_mode == NODE_MODE_JOINING)
            {
                // If passkey is shorter than BLE_GAP_PASSKEY_LEN, add '0' character.
                if (m_node_settings.keys_store.keys_len < BLE_GAP_PASSKEY_LEN)
                {
                    memset(&m_node_settings.keys_store.keys[m_node_settings.keys_store.keys_len], \
                           '0', BLE_GAP_PASSKEY_LEN - m_node_settings.keys_store.keys_len);
                }

                // Short passkey to 6-length character.
                m_node_settings.keys_store.keys[BLE_GAP_PASSKEY_LEN] = 0;

                COMM_TRC("Stored passkey is: %s", m_node_settings.keys_store.keys);

                err_code = sd_ble_gap_auth_key_reply(m_conn_handle,                 \
                                                     BLE_GAP_AUTH_KEY_TYPE_PASSKEY, \
                                                     m_node_settings.keys_store.keys);
                APP_ERROR_CHECK(err_code);
            }

            break;
        }
        case BLE_GAP_EVT_AUTH_STATUS:
        {
            if (m_current_mode == NODE_MODE_JOINING)
            {
                COMM_TRC("Status of authentication: %08x", \
                              p_ble_evt->evt.gap_evt.params.auth_status.auth_status);
            }

            break;
        }
        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
        {
            if (m_current_mode == NODE_MODE_JOINING)
            {
                ble_gap_sec_params_t sec_param;
                ble_gap_sec_keyset_t keys_exchanged;

                memset(&sec_param, 0, sizeof(ble_gap_sec_params_t));
                memset(&keys_exchanged, 0, sizeof(ble_gap_sec_keyset_t));

                sec_param.bond         = SEC_PARAM_BOND;
                sec_param.oob          = SEC_PARAM_OOB;
                sec_param.min_key_size = SEC_PARAM_MIN_KEY_SIZE;
                sec_param.max_key_size = SEC_PARAM_MAX_KEY_SIZE;
                sec_param.mitm         = SEC_PARAM_MITM;
                sec_param.io_caps      = SEC_PARAM_IO_CAPABILITIES;

                err_code = sd_ble_gap_sec_params_reply(p_ble_evt->evt.gap_evt.conn_handle,
                                                       BLE_GAP_SEC_STATUS_SUCCESS,
                                                       &sec_param,
                                                       &keys_exchanged);
                APP_ERROR_CHECK(err_code);
            }

            break;
        }
        default:
        {
            break;
        }
    }
}


void on_ble_ncfgs_evt(ble_ncfgs_data_t * ncfgs_data)
{
    COMM_ENTRY();

    commissioning_timer_stop_reset(TIMER_INDEX_DELAYED_ACTION);
    commissioning_timer_stop_reset(TIMER_INDEX_CONFIG_MODE);

    uint32_t mode_duration_sec;
    mode_duration_sec = ncfgs_data->ctrlp_value.duration_sec;
    mode_duration_sec = (mode_duration_sec == 0) ? 1 : mode_duration_sec;

    switch (ncfgs_data->ctrlp_value.opcode)
    {
        case NCFGS_OPCODE_GOTO_JOINING_MODE:
        {
            m_next_mode = NODE_MODE_JOINING;

            m_node_settings.joining_mode_to      = mode_duration_sec;
            m_node_settings.joining_mode_failure = ncfgs_data->ctrlp_value.state_on_failure;

            /* This code will get executed in two scenarios:
               - if the previous mode was Config mode and now we are ready to connect to the router, or
               - if the previous mode was Joining mode and the state on failure was set to No Change.
            */
            if (m_node_settings.joining_mode_failure == NCFGS_SOF_NO_CHANGE)
            {
                m_node_settings.poweron_mode = NODE_MODE_JOINING;
            }
            else
            {
                // If the state on failure is NOT No Change, start next time in Config mode.
                m_node_settings.poweron_mode = NODE_MODE_CONFIG;
            }

            if (m_node_settings.joining_mode_failure == NCFGS_SOF_PWR_OFF)
            {
                COMM_TRC("Will power off on failure.");
                m_power_off_on_failure = true;  // The assert handler will power off the system.
            }

            break;
        }
        case NCFGS_OPCODE_GOTO_CONFIG_MODE:
        {
            m_next_mode = NODE_MODE_CONFIG;

            m_node_settings.config_mode_to      = mode_duration_sec;
            m_node_settings.config_mode_failure = ncfgs_data->ctrlp_value.state_on_failure;

            /* The node is about to enter Config mode. Regardless of what the state on failure
               setting is (No Change or Pwr Off or Cfg Mode), the poweron_mode value should be Cfg Mode. */
            m_node_settings.poweron_mode = NODE_MODE_CONFIG;

            if (m_node_settings.config_mode_failure == NCFGS_SOF_PWR_OFF)
            {
                COMM_TRC("Will power off on failure.");
                m_power_off_on_failure = true;  // The assert handler will power off the system.
            }

            break;
        }
        case NCFGS_OPCODE_GOTO_IDENTITY_MODE:
        {
            m_next_mode = NODE_MODE_IDENTITY;

            m_node_settings.id_mode_to = mode_duration_sec;

            break;
        }
        default:
        {
            break;
        }
    }

    memcpy(&m_node_settings.ssid_store,    &ncfgs_data->ssid_from_router, sizeof(ssid_store_t));
    memcpy(&m_node_settings.keys_store,    &ncfgs_data->keys_from_router, sizeof(keys_store_t));
    memcpy(&m_node_settings.id_data_store, &ncfgs_data->id_data,          sizeof(id_data_store_t));

#if (COMM_ENABLE_LOGS == 1)
    print_node_settings();
#endif // (COMM_ENABLE_LOGS == 1)

#if (FDS_ENABLED == 1)
    uint32_t err_code = persistent_settings_update();
    APP_ERROR_CHECK(err_code);
#endif // FDS_ENABLED

    uint32_t action_delay_written = ncfgs_data->ctrlp_value.delay_sec;
    // Set the timeout value to at least MINIMUM_ACTION_DELAY second(s).
    // This is to make sure that storing settings in the persistent
    // storage completes before activating the next mode.
    action_delay_written = (action_delay_written < MINIMUM_ACTION_DELAY) ? \
                           MINIMUM_ACTION_DELAY : action_delay_written;

    COMM_TRC("Action delay: %ld seconds.", action_delay_written);
    commissioning_timer_start(TIMER_INDEX_DELAYED_ACTION, action_delay_written);

    COMM_EXIT();
}


void commissioning_time_tick(iot_timer_time_in_ms_t wall_clock_value)
{
    UNUSED_PARAMETER(wall_clock_value);
    uint8_t index;

    for (index=0; index<NUMBER_OF_COMMISSIONING_TIMERS; ++index)
    {
        if (m_commissioning_timers[index].is_timer_running == true)
        {
            m_commissioning_timers[index].current_value_sec -= COMMISSIONING_TICK_INTERVAL_SEC;

            if (m_commissioning_timers[index].current_value_sec == 0)
            {
                commissioning_timer_stop_reset(index);
                m_commissioning_timers[index].timeout_handler();
            }
        }
    }
}


static void commissioning_timers_init(void)
{
    memset(m_commissioning_timers, 0x00, sizeof(m_commissioning_timers));
    m_commissioning_timers[TIMER_INDEX_DELAYED_ACTION].timeout_handler = \
                                                                            action_timeout_handler;
    m_commissioning_timers[TIMER_INDEX_CONFIG_MODE].timeout_handler    = \
                                                                       config_mode_timeout_handler;
    m_commissioning_timers[TIMER_INDEX_JOINING_MODE].timeout_handler   = \
                                                                      joining_mode_timeout_handler;
    m_commissioning_timers[TIMER_INDEX_IDENTITY_MODE].timeout_handler  = \
                                                                     identity_mode_timeout_handler;
}

uint32_t commissioning_init(commissioning_init_params_t   * p_init_param, \
                            uint8_t                       * p_poweron_state)
{
    COMM_ENTRY();
    uint32_t err_code = NRF_SUCCESS;

    m_commissioning_evt_handler = p_init_param->commissioning_evt_handler;
    m_power_off_on_failure = false;

    // Initialize Commissioning timers.

    commissioning_timers_init();

    // Initialize GATT server.

    err_code = ble_ncfgs_init(on_ble_ncfgs_evt);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

#if (FDS_ENABLED == 1)
    err_code = persistent_settings_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
#endif

    // Read application settings from persistent storage.
    read_node_settings();

#if (COMM_ENABLE_LOGS == 1)
    print_node_settings();
#endif // (COMM_ENABLE_LOGS == 1)

    if (!settings_are_valid()) // If the settings are invalid for any reason go to Config mode.
    {
        COMM_ERR("Invalid settings!");

        commissioning_settings_clear();

        memset(&m_node_settings, 0x00, sizeof(m_node_settings));
        m_node_settings.config_mode_to = 300;

        *p_poweron_state = NODE_MODE_CONFIG;
    }
    else
    {
        if (m_node_settings.poweron_mode == NODE_MODE_JOINING)
        {
            /* This code will get executed in two scenarios:
               - if the previous mode was Config mode and now we are ready to connect to the router, or
               - if the previous mode was Joining mode and the state on failure was set to No Change.
            */
            if ((m_node_settings.joining_mode_failure == NCFGS_SOF_PWR_OFF)       || \
                (m_node_settings.joining_mode_failure == NCFGS_SOF_CONFIG_MODE))
            {
                // If the state on failure is NOT No Change, start next time in Config mode.
                m_node_settings.poweron_mode = NODE_MODE_CONFIG;
#if (FDS_ENABLED == 1)
                err_code = persistent_settings_update();
                APP_ERROR_CHECK(err_code);
#endif // FDS_ENABLED
            }

            if (m_node_settings.joining_mode_failure == NCFGS_SOF_PWR_OFF)
            {
                COMM_TRC("Will power off on failure.");
                m_power_off_on_failure = true;  // The assert handler will power off the system.
            }

            *p_poweron_state = NODE_MODE_JOINING;
        }
        else
        {
            /* The app is about to enter Config mode. Regardless of what the state on failure
               setting is (No Change or Pwr Off or Cfg Mode), the poweron_mode value should remain the same. */

            if (m_node_settings.config_mode_failure == NCFGS_SOF_PWR_OFF)
            {
                COMM_TRC("Will power off on failure.");
                m_power_off_on_failure = true;  // The assert handler will power off the system.
            }

            *p_poweron_state = NODE_MODE_CONFIG;
        }
    }

    // Set advertising and GAP parameters.
    config_mode_gap_params_set();
    config_mode_adv_params_set();
    joining_mode_gap_params_set();
    joining_mode_adv_params_set();

    COMM_EXIT();
    return err_code;
}

#endif // COMMISSIONING_ENABLED
