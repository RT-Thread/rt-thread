/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#include  "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_ADVERTISING)
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "nrf_soc.h"
#include "nrf_log.h"
#include "fstorage.h"
#include "sdk_errors.h"


// Total number of possible advertising modes.
#define BLE_ADV_MODES                  (5)


static bool                            m_initialized;
static bool                            m_advertising_start_pending;                 /**< Flag to keep track of ongoing operations in flash. */

static ble_adv_evt_t                   m_adv_evt;                                   /**< Advertising event propogated to the main application. The event is either a transaction to a new advertising mode, or a request for whitelist or peer address. */

static ble_adv_mode_t                  m_adv_mode_current;                          /**< Variable to keep track of the current advertising mode. */
static ble_adv_modes_config_t          m_adv_modes_config;                          /**< Struct to keep track of disabled and enabled advertising modes, as well as time-outs and intervals.*/
static uint8_t                         m_conn_cfg_tag;                              /**< Variable to keep track of what connection settings will be used if the advertising results in a connection. */

static ble_gap_addr_t                  m_peer_address;                              /**< Address of the most recently connected peer, used for direct advertising. */
static bool                            m_peer_addr_reply_expected;                  /**< Flag to verify that peer address is only set when requested. */

static ble_advdata_t                   m_advdata;                                   /**< Used by the initialization function to set name, appearance, and UUIDs and advertising flags visible to peer devices. */
static ble_advdata_manuf_data_t        m_manuf_specific_data;                       /**< Manufacturer specific data structure*/
static uint8_t                         m_manuf_data_array[BLE_GAP_ADV_MAX_SIZE];    /**< Array to store the Manufacturer specific data*/
static ble_advdata_service_data_t      m_service_data;                              /**< Service data structure. */
static uint8_t                         m_service_data_array[BLE_GAP_ADV_MAX_SIZE];  /**< Array to store the service data. */
static ble_advdata_conn_int_t          m_slave_conn_int;                            /**< Connection interval range structure.*/
static uint16_t                        m_current_slave_link_conn_handle;            /**< Connection handle for the active link. */

static ble_advertising_evt_handler_t   m_evt_handler;                               /**< Handler for the advertising events. Can be initialized as NULL if no handling is implemented on in the main application. */
static ble_advertising_error_handler_t m_error_handler;                             /**< Handler for the advertising error events. */

static bool                            m_whitelist_temporarily_disabled;            /**< Flag to keep track of temporary disabling of the whitelist. */
static bool                            m_whitelist_reply_expected;

#if (NRF_SD_BLE_API_VERSION <= 2)

    // For SoftDevices v 2.x, this module caches a whitelist which is retrieved from the
    // application using an event, and which is passed as a parameter when calling
    // sd_ble_gap_adv_start().

    static ble_gap_addr_t      * m_p_whitelist_addrs[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];
    static ble_gap_irk_t       * m_p_whitelist_irks[BLE_GAP_WHITELIST_IRK_MAX_COUNT];
    static ble_gap_addr_t      m_whitelist_addrs[BLE_GAP_WHITELIST_ADDR_MAX_COUNT];
    static ble_gap_irk_t       m_whitelist_irks[BLE_GAP_WHITELIST_IRK_MAX_COUNT];

    static ble_gap_whitelist_t   m_whitelist =
    {
        .pp_addrs = m_p_whitelist_addrs,
        .pp_irks  = m_p_whitelist_irks
    };

#else

    // For SoftDevices v 3.x, this module does not need to cache a whitelist, but it needs to
    // be aware of whether or not a whitelist has been set (e.g. using the Peer Manager)
    // in order to start advertising with the proper advertising params (filter policy).

    static bool m_whitelist_in_use;

#endif


#if (NRF_SD_BLE_API_VERSION <= 2)

    static bool whitelist_has_entries()
    {
        return ((m_whitelist.addr_count != 0) || (m_whitelist.irk_count != 0));
    }

#else

    static bool whitelist_has_entries()
    {
        return m_whitelist_in_use;
    }

#endif



/**@brief Function for checking if an address is valid.
 */
static bool addr_is_valid(uint8_t const * const addr)
{
    for (uint32_t i = 0; i < BLE_GAP_ADDR_LEN; i++)
    {
        if (addr[i] != 0)
        {
            return true;
        }
    }
    return false;
}


static ble_adv_mode_t adv_mode_next_get(ble_adv_mode_t adv_mode)
{
    return (ble_adv_mode_t)((adv_mode + 1) % BLE_ADV_MODES);
}


/**@brief Function for handling the Connected event.
 *
 * @param[in] p_ble_evt Event received from the BLE stack.
 */
static void on_connected(ble_evt_t const * p_ble_evt)
{
    if (p_ble_evt->evt.gap_evt.params.connected.role == BLE_GAP_ROLE_PERIPH)
    {
        m_current_slave_link_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
    }
}


/**@brief Function for handling the Disconnected event.
 *
 * @param[in] p_ble_evt Event received from the BLE stack.
 */
static void on_disconnected(ble_evt_t const * p_ble_evt)
{
    uint32_t ret;

    m_whitelist_temporarily_disabled = false;

    if (p_ble_evt->evt.gap_evt.conn_handle == m_current_slave_link_conn_handle)
    {
       ret = ble_advertising_start(BLE_ADV_MODE_DIRECTED);
       if ((ret != NRF_SUCCESS) && (m_error_handler != NULL))
       {
           m_error_handler(ret);
       }
    }
}


/**@brief Function for handling the Timeout event.
 *
 * @param[in] p_ble_evt Event received from the BLE stack.
 */
static void on_timeout(ble_evt_t const * p_ble_evt)
{
    ret_code_t ret;

    if (p_ble_evt->evt.gap_evt.params.timeout.src != BLE_GAP_TIMEOUT_SRC_ADVERTISING)
    {
        // Nothing to do.
        return;
    }

    // Start advertising in the next mode.
    ret = ble_advertising_start(adv_mode_next_get(m_adv_mode_current));

    if ((ret != NRF_SUCCESS) && (m_error_handler != NULL))
    {
        m_error_handler(ret);
    }
}


/** @brief Function to determine if a flash write operation in in progress.
 *
 * @return true if a flash operation is in progress, false if not.
 */
static bool flash_access_in_progress()
{
    uint32_t count;

    (void)fs_queued_op_count_get(&count);

    return (count != 0);
}


/**@brief Get the next available advertising mode.
 *
 * @param[in] adv_mode Requested advertising mode.
 *
 * @returns adv_mode if possible, or the best available mode if not.
 */
static ble_adv_mode_t adv_mode_next_avail_get(ble_adv_mode_t adv_mode)
{
    bool peer_addr_is_valid = addr_is_valid(m_peer_address.addr);

    // If a mode is disabled, continue to the next mode.

    switch (adv_mode)
    {
        case BLE_ADV_MODE_DIRECTED:
            if ((m_adv_modes_config.ble_adv_directed_enabled) && peer_addr_is_valid)
            {
                return BLE_ADV_MODE_DIRECTED;
            }
            // Fallthrough.

        case BLE_ADV_MODE_DIRECTED_SLOW:
            if ((m_adv_modes_config.ble_adv_directed_slow_enabled) && peer_addr_is_valid)
            {
                return BLE_ADV_MODE_DIRECTED_SLOW;
            }
            // Fallthrough.

        case BLE_ADV_MODE_FAST:
            if (m_adv_modes_config.ble_adv_fast_enabled)
            {
                return BLE_ADV_MODE_FAST;
            }
            // Fallthrough.

        case BLE_ADV_MODE_SLOW:
            if (m_adv_modes_config.ble_adv_slow_enabled)
            {
                return BLE_ADV_MODE_SLOW;
            }
            // Fallthrough.

        default:
            return BLE_ADV_MODE_IDLE;
    }
}


/**@brief Function for starting directed advertising.
 *
 * @param[out] p_adv_params Advertising parameters.
 *
 * @return NRF_SUCCESS
 */
static ret_code_t set_adv_mode_directed(ble_gap_adv_params_t * p_adv_params)
{
    m_adv_evt  = BLE_ADV_EVT_DIRECTED;

    p_adv_params->p_peer_addr = &m_peer_address;
    p_adv_params->type        = BLE_GAP_ADV_TYPE_ADV_DIRECT_IND;
    p_adv_params->timeout     = 0;
    p_adv_params->interval    = 0;

    return NRF_SUCCESS;
}


/**@brief Function for starting directed slow advertising.
 *
 * @param[out] p_adv_params Advertising parameters.
 *
 * @return NRF_SUCCESS
 */
static ret_code_t set_adv_mode_directed_slow(ble_gap_adv_params_t * p_adv_params)
{
    m_adv_evt = BLE_ADV_EVT_DIRECTED_SLOW;

    p_adv_params->p_peer_addr = &m_peer_address;
    p_adv_params->type        = BLE_GAP_ADV_TYPE_ADV_DIRECT_IND;
    p_adv_params->timeout     = m_adv_modes_config.ble_adv_directed_slow_timeout;
    p_adv_params->interval    = m_adv_modes_config.ble_adv_directed_slow_interval;

    return NRF_SUCCESS;
}


/**@brief Function for starting fast advertising.
 *
 * @param[out] p_adv_params Advertising parameters.
 *
 * @return NRF_SUCCESS or an error from @ref ble_advdata_set().
 */
static ret_code_t set_adv_mode_fast(ble_gap_adv_params_t * p_adv_params)
{
    ret_code_t ret;

    p_adv_params->interval = m_adv_modes_config.ble_adv_fast_interval;
    p_adv_params->timeout  = m_adv_modes_config.ble_adv_fast_timeout;

    if ((m_adv_modes_config.ble_adv_whitelist_enabled) &&
        (!m_whitelist_temporarily_disabled) &&
        (whitelist_has_entries()))
    {
        #if (NRF_SD_BLE_API_VERSION <= 2)
            p_adv_params->p_whitelist = &m_whitelist;
        #endif

        p_adv_params->fp = BLE_GAP_ADV_FP_FILTER_CONNREQ;
        m_advdata.flags  = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;

        ret = ble_advdata_set(&m_advdata, NULL);
        if (ret != NRF_SUCCESS)
        {
            return ret;
        }

        m_adv_evt = BLE_ADV_EVT_FAST_WHITELIST;
    }
    else
    {
        m_adv_evt = BLE_ADV_EVT_FAST;
    }

    return NRF_SUCCESS;
}


/**@brief Function for starting slow advertising.
 *
 * @param[out] p_adv_params Advertising parameters.
 *
 * @return NRF_SUCCESS or an error from @ref ble_advdata_set().
 */
static ret_code_t set_adv_mode_slow(ble_gap_adv_params_t * p_adv_params)
{
    ret_code_t ret;

    p_adv_params->interval = m_adv_modes_config.ble_adv_slow_interval;
    p_adv_params->timeout  = m_adv_modes_config.ble_adv_slow_timeout;

    if ((m_adv_modes_config.ble_adv_whitelist_enabled) &&
        (!m_whitelist_temporarily_disabled) &&
        (whitelist_has_entries()))
    {
        #if (NRF_SD_BLE_API_VERSION <= 2)
        {
            p_adv_params->p_whitelist = &m_whitelist;
        }
        #endif

        p_adv_params->fp = BLE_GAP_ADV_FP_FILTER_CONNREQ;
        m_advdata.flags  = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;

        ret = ble_advdata_set(&m_advdata, NULL);
        if (ret != NRF_SUCCESS)
        {
            return ret;
        }

        m_adv_evt = BLE_ADV_EVT_SLOW_WHITELIST;
    }
    else
    {
        m_adv_evt = BLE_ADV_EVT_SLOW;
    }

    return NRF_SUCCESS;
}


void ble_advertising_conn_cfg_tag_set(uint8_t ble_cfg_tag)
{
    m_conn_cfg_tag = ble_cfg_tag;
}


uint32_t ble_advertising_init(ble_advdata_t                   const * p_advdata,
                              ble_advdata_t                   const * p_srdata,
                              ble_adv_modes_config_t          const * p_config,
                              ble_advertising_evt_handler_t   const   evt_handler,
                              ble_advertising_error_handler_t const   error_handler)
{
    uint32_t ret;

    if ((p_advdata == NULL) || (p_config == NULL))
    {
        return NRF_ERROR_NULL;
    }

    m_initialized                    = true;
    m_adv_mode_current               = BLE_ADV_MODE_IDLE;
    m_adv_modes_config               = *p_config;
    m_conn_cfg_tag                   = BLE_CONN_CFG_TAG_DEFAULT;
    m_evt_handler                    = evt_handler;
    m_error_handler                  = error_handler;
    m_current_slave_link_conn_handle = BLE_CONN_HANDLE_INVALID;

    memset(&m_peer_address, 0, sizeof(m_peer_address));
    memset(&m_advdata,      0, sizeof(m_advdata));

    // Copy advertising data.
    m_advdata.name_type            = p_advdata->name_type;
    m_advdata.include_appearance   = p_advdata->include_appearance;
    m_advdata.flags                = p_advdata->flags;
    m_advdata.short_name_len       = p_advdata->short_name_len;

    m_advdata.uuids_complete       = p_advdata->uuids_complete;
    m_advdata.uuids_more_available = p_advdata->uuids_more_available;
    m_advdata.uuids_solicited      = p_advdata->uuids_solicited;

    if (p_advdata->p_manuf_specific_data != NULL)
    {
        m_advdata.p_manuf_specific_data   = &m_manuf_specific_data;
        m_manuf_specific_data.data.p_data = m_manuf_data_array;
        m_advdata.p_manuf_specific_data->company_identifier =
        p_advdata->p_manuf_specific_data->company_identifier;
        m_advdata.p_manuf_specific_data->data.size = p_advdata->p_manuf_specific_data->data.size;

        for (uint32_t i = 0; i < m_advdata.p_manuf_specific_data->data.size; i++)
        {
            m_manuf_data_array[i] = p_advdata->p_manuf_specific_data->data.p_data[i];
        }
    }

    if (p_advdata->p_service_data_array != NULL)
    {
        m_service_data.data.p_data                   = m_service_data_array;
        m_advdata.p_service_data_array               = &m_service_data;
        m_advdata.p_service_data_array->data.p_data  = m_service_data_array;
        m_advdata.p_service_data_array->data.size    = p_advdata->p_service_data_array->data.size;
        m_advdata.p_service_data_array->service_uuid = p_advdata->p_service_data_array->service_uuid;

        for (uint32_t i = 0; i < m_advdata.p_service_data_array->data.size; i++)
        {
            m_service_data_array[i] = p_advdata->p_service_data_array->data.p_data[i];
        }

        m_advdata.service_data_count = p_advdata->service_data_count;
    }

    if (p_advdata->p_slave_conn_int != NULL)
    {
        m_advdata.p_slave_conn_int                    = &m_slave_conn_int;
        m_advdata.p_slave_conn_int->max_conn_interval = p_advdata->p_slave_conn_int->max_conn_interval;
        m_advdata.p_slave_conn_int->min_conn_interval = p_advdata->p_slave_conn_int->min_conn_interval;
    }

    if (p_advdata->p_tx_power_level != NULL)
    {
        m_advdata.p_tx_power_level = p_advdata->p_tx_power_level;
    }

#if (NRF_SD_BLE_API_VERSION <= 2)
        for (int i = 0; i <BLE_GAP_WHITELIST_ADDR_MAX_COUNT ; i++)
        {
            m_whitelist.pp_addrs[i] = &m_whitelist_addrs[i];
        }

        for (int i = 0; i <BLE_GAP_WHITELIST_IRK_MAX_COUNT ; i++)
        {
            m_whitelist.pp_irks[i] = &m_whitelist_irks[i];
        }
#endif

    ret = ble_advdata_set(&m_advdata, p_srdata);
    return ret;
}


uint32_t ble_advertising_start(ble_adv_mode_t advertising_mode)
{
    uint32_t             ret;
    ble_gap_adv_params_t adv_params;

    if (m_initialized == false)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    m_adv_mode_current = advertising_mode;

    // Delay starting advertising until the flash operations are complete.
    if (flash_access_in_progress())
    {
        m_advertising_start_pending = true;
        return NRF_SUCCESS;
    }

   memset(&m_peer_address, 0, sizeof(m_peer_address));

    if (  ((m_adv_modes_config.ble_adv_directed_enabled)      && (m_adv_mode_current == BLE_ADV_MODE_DIRECTED))
        ||((m_adv_modes_config.ble_adv_directed_slow_enabled) && (m_adv_mode_current == BLE_ADV_MODE_DIRECTED))
        ||((m_adv_modes_config.ble_adv_directed_slow_enabled) && (m_adv_mode_current == BLE_ADV_MODE_DIRECTED_SLOW))
       )
    {
        if (m_evt_handler != NULL)
        {
            m_peer_addr_reply_expected = true;
            m_evt_handler(BLE_ADV_EVT_PEER_ADDR_REQUEST);
        }
        else
        {
            m_peer_addr_reply_expected = false;
        }
    }

    m_adv_mode_current = adv_mode_next_avail_get(advertising_mode);

    // Fetch the whitelist.
    if ((m_evt_handler != NULL) &&
        (m_adv_mode_current == BLE_ADV_MODE_FAST || m_adv_mode_current == BLE_ADV_MODE_SLOW) &&
        (m_adv_modes_config.ble_adv_whitelist_enabled) &&
        (!m_whitelist_temporarily_disabled))
    {
        #if (NRF_SD_BLE_API_VERSION >= 3)
            m_whitelist_in_use = false;
        #endif
        m_whitelist_reply_expected = true;
        m_evt_handler(BLE_ADV_EVT_WHITELIST_REQUEST);
    }
    else
    {
        m_whitelist_reply_expected = false;
    }

    // Initialize advertising parameters with default values.
    memset(&adv_params, 0, sizeof(adv_params));

    adv_params.type = BLE_GAP_ADV_TYPE_ADV_IND;
    adv_params.fp   = BLE_GAP_ADV_FP_ANY;

    // Set advertising parameters and events according to selected advertising mode.
    switch (m_adv_mode_current)
    {
        case BLE_ADV_MODE_DIRECTED:
            ret = set_adv_mode_directed(&adv_params);
            break;

        case BLE_ADV_MODE_DIRECTED_SLOW:
            ret = set_adv_mode_directed_slow(&adv_params);
            break;

        case BLE_ADV_MODE_FAST:
            ret = set_adv_mode_fast(&adv_params);
            break;

        case BLE_ADV_MODE_SLOW:
            ret = set_adv_mode_slow(&adv_params);
            break;

        case BLE_ADV_MODE_IDLE:
            m_adv_evt = BLE_ADV_EVT_IDLE;
            break;

        default:
            break;
    }

    if (m_adv_mode_current != BLE_ADV_MODE_IDLE)
    {
        ret = sd_ble_gap_adv_start(&adv_params, m_conn_cfg_tag);
        if (ret != NRF_SUCCESS)
        {
            return ret;
        }
    }

    if (m_evt_handler != NULL)
    {
        m_evt_handler(m_adv_evt);
    }

    return NRF_SUCCESS;
}


void ble_advertising_on_ble_evt(ble_evt_t const * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connected(p_ble_evt);
            break;

        // Upon disconnection, whitelist will be activated and direct advertising is started.
        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnected(p_ble_evt);
            break;

        // Upon time-out, the next advertising mode is started.
        case BLE_GAP_EVT_TIMEOUT:
            on_timeout(p_ble_evt);
            break;

        default:
            break;
    }
}


void ble_advertising_on_sys_evt(uint32_t sys_evt)
{
    uint32_t ret;

    switch (sys_evt)
    {
        //When a flash operation finishes, re-attempt to start advertising operations.
        case NRF_EVT_FLASH_OPERATION_SUCCESS:
        case NRF_EVT_FLASH_OPERATION_ERROR:
            if (m_advertising_start_pending)
            {
                m_advertising_start_pending = false;
                ret = ble_advertising_start(m_adv_mode_current);
                if ((ret != NRF_SUCCESS) && (m_error_handler != NULL))
                {
                    m_error_handler(ret);
                }
            }
            break;

        default:
            // No implementation needed.
            break;
    }
}


uint32_t ble_advertising_peer_addr_reply(ble_gap_addr_t * p_peer_address)
{
    if (!m_peer_addr_reply_expected)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    m_peer_addr_reply_expected = false;

    memcpy(&m_peer_address, p_peer_address, sizeof(m_peer_address));

    return NRF_SUCCESS;
}


uint32_t ble_advertising_whitelist_reply(ble_gap_addr_t const * p_gap_addrs,
                                         uint32_t               addr_cnt,
                                         ble_gap_irk_t  const * p_gap_irks,
                                         uint32_t               irk_cnt)
{
    if (!m_whitelist_reply_expected)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    m_whitelist_reply_expected = false;

    #if (NRF_SD_BLE_API_VERSION <= 2)

        m_whitelist.addr_count = addr_cnt;
        m_whitelist.irk_count  = irk_cnt;

        for (uint32_t i = 0; i < addr_cnt; i++)
        {
            *m_whitelist.pp_addrs[i] = p_gap_addrs[i];
        }

        for (uint32_t i = 0; i < irk_cnt; i++)
        {
            *m_whitelist.pp_irks[i] = p_gap_irks[i];
        }

    #else

        m_whitelist_in_use = ((addr_cnt > 0) || (irk_cnt > 0));

    #endif

    return NRF_SUCCESS;
}


uint32_t ble_advertising_restart_without_whitelist(void)
{
    uint32_t ret;

    (void) sd_ble_gap_adv_stop();

    m_whitelist_temporarily_disabled = true;

    #if (NRF_SD_BLE_API_VERSION >= 3)
        m_whitelist_in_use = false;
    #endif

    m_advdata.flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;

    ret = ble_advdata_set(&m_advdata, NULL);
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    ret = ble_advertising_start(m_adv_mode_current);
    if ((ret != NRF_SUCCESS) && (m_error_handler != NULL))
    {
        m_error_handler(ret);
    }

    return NRF_SUCCESS;
}

#endif // NRF_MODULE_ENABLED(BLE_ADVERTISING)
