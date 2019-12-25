/**
 * Copyright (c) 2018 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_BLE_SCAN)

#include "sdk_config.h"
#include <stdlib.h>

#include "nrf_ble_scan.h"

#include <string.h>
#include "app_error.h"
#include "nrf_assert.h"
#include "sdk_macros.h"
#include "ble_advdata.h"

#define NRF_LOG_MODULE_NAME ble_scan
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();


/**@brief Function for establishing the connection with a device.
 *
 * @details Connection is established if @ref NRF_BLE_SCAN_EVT_FILTER_MATCH
 *          or @ref NRF_BLE_SCAN_EVT_WHITELIST_ADV_REPORT occurs and the module was
 *          initialized in the automatic connection mode. This function can generate an event
 *          to the main application when @ref sd_ble_gap_connect is used inside the function and it returns value
 *          that is different than @ref NRF_SUCCESS.
 *
 * @param[in] p_scan_ctx   Pointer to the Scanning Module instance.
 * @param[in] p_adv_report Advertising data.
 */
static void nrf_ble_scan_connect_with_target(nrf_ble_scan_t           const * const p_scan_ctx,
                                             ble_gap_evt_adv_report_t const * const p_adv_report)
{
    ret_code_t err_code;
    scan_evt_t scan_evt;

    // For readability.
    ble_gap_addr_t const        * p_addr        = &p_adv_report->peer_addr;
    ble_gap_scan_params_t const * p_scan_params = &p_scan_ctx->scan_params;
    ble_gap_conn_params_t const * p_conn_params = &p_scan_ctx->conn_params;
    uint8_t                       con_cfg_tag   = p_scan_ctx->conn_cfg_tag;

    // Return if the automatic connection is disabled.
    if (!p_scan_ctx->connect_if_match)
    {
        return;
    }

    // Stop scanning.
    nrf_ble_scan_stop();

    memset(&scan_evt, 0, sizeof(scan_evt));

    // Establish connection.
    err_code = sd_ble_gap_connect(p_addr,
                                  p_scan_params,
                                  p_conn_params,
                                  con_cfg_tag);

    NRF_LOG_DEBUG("Connecting");

    scan_evt.scan_evt_id                    = NRF_BLE_SCAN_EVT_CONNECTING_ERROR;
    scan_evt.params.connecting_err.err_code = err_code;

    NRF_LOG_DEBUG("Connection status: %d", err_code);

    // If an error occurred, send an event to the event handler.
    if ((err_code != NRF_SUCCESS) && (p_scan_ctx->evt_handler != NULL))
    {
        p_scan_ctx->evt_handler(&scan_evt);
    }

}


/**@brief Function for decoding the BLE address type.
 *
 * @param[in] p_addr 	The BLE address.
 *
 * @return    			Address type, or an error if the address type is incorrect, that is it does not match @ref BLE_GAP_ADDR_TYPES.
 *
 */
static uint16_t nrf_ble_scan_address_type_decode(uint8_t const * p_addr)
{
    uint8_t addr_type = p_addr[0];

    // See Bluetooth Core Specification Vol 6, Part B, section 1.3.
    addr_type  = addr_type >> 6;
    addr_type &= 0x03;

    // Check address type.
    switch (addr_type)
    {
        case 0:
        {
            return BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_NON_RESOLVABLE;
        }

        case 1:
        {
            return BLE_GAP_ADDR_TYPE_PUBLIC;
        }

        case 2:
        {
            return BLE_GAP_ADDR_TYPE_RANDOM_PRIVATE_RESOLVABLE;
        }

        case 3:
        {
            return BLE_GAP_ADDR_TYPE_RANDOM_STATIC;
        }

        default:
        {
            return BLE_ERROR_GAP_INVALID_BLE_ADDR;
        }
    }
}


#if (NRF_BLE_SCAN_FILTER_ENABLE == 1)
#if (NRF_BLE_SCAN_ADDRESS_CNT > 0)

/**@brief Function for searching for the provided address in the advertisement packets.
 *
 * @details Use this function to parse the received advertising data for the provided address.
 *        
 *
 * @param[in]   p_adv_report   Advertising data to parse.
 * @param[in]   p_addr         Address to search for. The address length must correspond to @ref BLE_GAP_ADDR_LEN.
 *
 * @return   True if the provided address was found, false otherwise.
 */
static bool find_peer_addr(ble_gap_evt_adv_report_t const * const p_adv_report,
                           ble_gap_addr_t const                 * p_addr)
{
    if (p_addr->addr_type == p_adv_report->peer_addr.addr_type)
    {
        // Compare addresses.
        if (memcmp(p_addr->addr,
                   p_adv_report->peer_addr.addr,
                   sizeof(p_adv_report->peer_addr.addr)) == 0)
        {
            return true;
        }
    }
    return false;
}


/** @brief Function for comparing the provided address with the addresses of the advertising devices.
 *
 * @param[in] p_adv_report    Advertising data to parse.
 * @param[in] p_scan_ctx      Pointer to the Scanning Module instance.
 *
 * @retval True when the address matches with the addresses of the advertising devices. False otherwise.
 */
static bool adv_addr_compare(ble_gap_evt_adv_report_t const * const p_adv_report,
                             nrf_ble_scan_t const * const           p_scan_ctx)
{
    ble_gap_addr_t const * p_addr  = p_scan_ctx->scan_filters.addr_filter.target_addr;
    uint8_t                counter = p_scan_ctx->scan_filters.addr_filter.addr_cnt;

    for (uint8_t index = 0; index < counter; index++)
    {
        // Search for address.
        if (find_peer_addr(p_adv_report, &p_addr[index]))
        {
            return true;
        }
    }

    return false;
}


/**@brief Function for adding target address to the scanning filter.
 *
 * @param[in]     p_addr            Target address in the format required by the SoftDevice. If you need to convert the address, use @ref nrf_ble_scan_copy_addr_to_sd_gap_addr. The address length must correspond to @ref BLE_GAP_ADDR_LEN.
 * @param[in,out] p_scan_ctx        Pointer to the Scanning Module instance.
 *
 * @retval NRF_SUCCESS                    If the filter is added successfully or if you try to add a filter that was already added before.
 * @retval NRF_ERROR_NO_MEMORY            If the number of available filters is exceeded.
 * @retval BLE_ERROR_GAP_INVALID_BLE_ADDR If the BLE address type is invalid.
 */
static ret_code_t nrf_ble_scan_addr_filter_add(nrf_ble_scan_t * const p_scan_ctx,
                                               uint8_t        const * p_addr)
{
    ble_gap_addr_t * p_addr_filter = p_scan_ctx->scan_filters.addr_filter.target_addr;
    uint8_t        * p_counter     = &p_scan_ctx->scan_filters.addr_filter.addr_cnt;
    uint8_t          index;
    uint16_t         addr_type;
    uint8_t          temp_addr[BLE_GAP_ADDR_LEN];

    // If no memory for filter.
    if (*p_counter >= NRF_BLE_SCAN_ADDRESS_CNT)
    {
        return NRF_ERROR_NO_MEM;
    }

    // Check for duplicated filter.
    for (index = 0; index < NRF_BLE_SCAN_ADDRESS_CNT; index++)
    {
        if (!memcmp(p_addr_filter[index].addr, p_addr, BLE_GAP_ADDR_LEN))
        {
            return NRF_SUCCESS;
        }
    }

    // Inverting the address.
    for (uint8_t i = 0; i < BLE_GAP_ADDR_LEN; i++)
    {
        temp_addr[i] = p_addr[(BLE_GAP_ADDR_LEN - 1) - i];
    }

    // Decode address type.
    addr_type = nrf_ble_scan_address_type_decode(temp_addr);

    if (addr_type == BLE_ERROR_GAP_INVALID_BLE_ADDR)
    {
        return BLE_ERROR_GAP_INVALID_BLE_ADDR;
    }

    // Add target address to filter.
    p_addr_filter[*p_counter].addr_type = (uint8_t)addr_type;

    for (uint8_t i = 0; i < BLE_GAP_ADDR_LEN; i++)
    {
        p_addr_filter[*p_counter].addr[i] = p_addr[i];
    }

    NRF_LOG_DEBUG("Filter set on address type %i, address 0x",
                  p_addr_filter[*p_counter].addr_type);

    for (index = 0; index < BLE_GAP_ADDR_LEN; index++)
    {
        NRF_LOG_DEBUG("%x", p_addr_filter[*p_counter].addr[index]);
    }

    NRF_LOG_DEBUG("\n\r");

    // Increase the address filter counter.
    *p_counter += 1;

    return NRF_SUCCESS;
}


#endif // NRF_BLE_SCAN_ADDRESS_CNT


#if (NRF_BLE_SCAN_NAME_CNT > 0)
/** @brief Function for comparing the provided name with the advertised name.
 *
 * @param[in] p_adv_report    Advertising data to parse.
 * @param[in] p_scan_ctx      Pointer to the Scanning Module instance.
 *
 * @retval True when the names match. False otherwise.
 */
static bool adv_name_compare(ble_gap_evt_adv_report_t const * p_adv_report,
                             nrf_ble_scan_t     const * const p_scan_ctx)
{
    nrf_ble_scan_name_filter_t const * p_name_filter = &p_scan_ctx->scan_filters.name_filter;
    uint8_t                            counter       =
        p_scan_ctx->scan_filters.name_filter.name_cnt;
    uint8_t  index;
    uint16_t data_len;

    data_len = p_adv_report->data.len;

    // Compare the name found with the name filter.
    for (index = 0; index < counter; index++)
    {
        if (ble_advdata_name_find(p_adv_report->data.p_data,
                                  data_len,
                                  p_name_filter->target_name[index]))
        {
            return true;
        }
    }

    return false;
}


/**@brief Function for adding name of the peripheral to the scanning filter.
 *
 * @param[in]     p_name            Peripheral name.
 * @param[in,out] p_scan_ctx        Pointer to the Scanning Module instance.
 *
 * @retval NRF_SUCCESS              If the filter is added successfully or if you try to add a filter that was already added before.
 * @retval NRF_ERROR_NULL           If a NULL pointer is passed as input.
 * @retval NRF_ERROR_DATA_SIZE      If the name filter length is too long. The maximum filter name length corresponds to @ref NRF_BLE_SCAN_NAME_MAX_LEN.
 * @retval NRF_ERROR_NO_MEMORY      If the number of available filters is exceeded.
 */
static ret_code_t nrf_ble_scan_name_filter_add(nrf_ble_scan_t * const p_scan_ctx,
                                               char           const * p_name)
{
    uint8_t   index;
    uint8_t * counter  = &p_scan_ctx->scan_filters.name_filter.name_cnt;
    uint8_t   name_len = strlen(p_name);

    // Check the name length.
    if ((name_len == 0) || (name_len > NRF_BLE_SCAN_NAME_MAX_LEN))
    {
        return NRF_ERROR_DATA_SIZE;
    }

    // If no memory for filter.
    if (*counter >= NRF_BLE_SCAN_NAME_CNT)
    {
        return NRF_ERROR_NO_MEM;
    }

    // Check for duplicated filter.
    for (index = 0; index < NRF_BLE_SCAN_NAME_CNT; index++)
    {
        if (!strcmp(p_scan_ctx->scan_filters.name_filter.target_name[index], p_name))
        {
            return NRF_SUCCESS;
        }
    }

    // Add name to filter.
    memcpy(p_scan_ctx->scan_filters.name_filter.target_name[(*counter)++],
           p_name,
           strlen(p_name));

    NRF_LOG_DEBUG("Adding filter on %s name", p_name);

    return NRF_SUCCESS;
}


#endif // NRF_BLE_SCAN_NAME_CNT


#if (NRF_BLE_SCAN_SHORT_NAME_CNT > 0)
/** @brief Function for comparing the provided short name with the advertised short name.
 *
 * @param[in] p_adv_report    Advertising data to parse.
 * @param[in] p_scan_ctx      Pointer to the Scanning Module instance.
 *
 * @retval True when the names match. False otherwise.
 */
static bool adv_short_name_compare(ble_gap_evt_adv_report_t const * const p_adv_report,
                                   nrf_ble_scan_t           const * const p_scan_ctx)
{
    nrf_ble_scan_short_name_filter_t const * p_name_filter =
        &p_scan_ctx->scan_filters.short_name_filter;
    uint8_t  counter = p_scan_ctx->scan_filters.short_name_filter.name_cnt;
    uint8_t  index;
    uint16_t data_len;

    data_len = p_adv_report->data.len;

    // Compare the name found with the name filters.
    for (index = 0; index < counter; index++)
    {
        if (ble_advdata_short_name_find(p_adv_report->data.p_data,
                                        data_len,
                                        p_name_filter->short_name[index].short_target_name,
                                        p_name_filter->short_name[index].short_name_min_len))
        {
            return true;
        }
    }

    return false;
}


/**@brief Function for adding the short name of the peripheral to the scanning filter.
 *
 * @param[in]     p_short_name      Short name of the peripheral.
 * @param[in,out] p_scan_ctx        Pointer to the Scanning Module instance.
 *
 * @retval NRF_SUCCESS              If the filter is added successfully or if you try to add a filter that was already added before.
 * @retval NRF_ERROR_NULL           If a NULL pointer is passed as input.
 * @retval NRF_ERROR_DATA_SIZE      If the name filter length is too long. The maximum filter name length corresponds to @ref NRF_BLE_SCAN_SHORT_NAME_MAX_LEN.
 * @retval NRF_ERROR_NO_MEMORY      If the number of available filters is exceeded.
 */
static ret_code_t nrf_ble_scan_short_name_filter_add(nrf_ble_scan_t            * const p_scan_ctx,
                                                     nrf_ble_scan_short_name_t const * p_short_name)
{
    uint8_t   index;
    uint8_t * p_counter =
        &p_scan_ctx->scan_filters.short_name_filter.name_cnt;
    nrf_ble_scan_short_name_filter_t * p_short_name_filter =
        &p_scan_ctx->scan_filters.short_name_filter;
    uint8_t name_len = strlen(p_short_name->p_short_name);

    // Check the name length.
    if ((name_len == 0) || (name_len > NRF_BLE_SCAN_SHORT_NAME_MAX_LEN))
    {
        return NRF_ERROR_DATA_SIZE;
    }

    // If no memory for filter.
    if (*p_counter >= NRF_BLE_SCAN_SHORT_NAME_CNT)
    {
        return NRF_ERROR_NO_MEM;
    }

    // Check for duplicated filter.
    for (index = 0; index < NRF_BLE_SCAN_SHORT_NAME_CNT; index++)
    {
        if (!strcmp(p_short_name_filter->short_name[index].short_target_name,
                    p_short_name->p_short_name))
        {
            return NRF_SUCCESS;
        }
    }

    // Add name to the filter.
    p_short_name_filter->short_name[(*p_counter)].short_name_min_len =
        p_short_name->short_name_min_len;
    memcpy(p_short_name_filter->short_name[(*p_counter)++].short_target_name,
           p_short_name->p_short_name,
           strlen(p_short_name->p_short_name));

    NRF_LOG_DEBUG("Adding filter on %s name", p_short_name->p_short_name);

    return NRF_SUCCESS;
}


#endif


#if (NRF_BLE_SCAN_UUID_CNT > 0)
/**@brief Function for comparing the provided UUID with the UUID in the advertisement packets.
 *
 * @param[in]   p_adv_report   Advertising data to parse.
 * @param[in]   p_scan_ctx     Pointer to the Scanning Module instance.
 *
 * @return      True if the UUIDs match. False otherwise.
 */
static bool adv_uuid_compare(ble_gap_evt_adv_report_t const * const p_adv_report,
                             nrf_ble_scan_t           const * const p_scan_ctx)
{
    nrf_ble_scan_uuid_filter_t const * p_uuid_filter    = &p_scan_ctx->scan_filters.uuid_filter;
    bool const                         all_filters_mode = p_scan_ctx->scan_filters.all_filters_mode;
    uint8_t const                      counter          =
        p_scan_ctx->scan_filters.uuid_filter.uuid_cnt;
    uint8_t  index;
    uint16_t data_len;
    uint8_t  uuid_match_cnt = 0;

    data_len = p_adv_report->data.len;

    for (index = 0; index < counter; index++)
    {

        if (ble_advdata_uuid_find(p_adv_report->data.p_data,
                                  data_len,
                                  &p_uuid_filter->uuid[index]))
        {
            uuid_match_cnt++;

            // In the normal filter mode, only one UUID is needed to match.
            if (!all_filters_mode)
            {
                break;
            }
        }
        else if (all_filters_mode)
        {
            break;
        }
        else
        {
            // Do nothing.
        }
    }

    // In the multifilter mode, all UUIDs must be found in the advertisement packets.
    if ((all_filters_mode && (uuid_match_cnt == counter)) ||
        ((!all_filters_mode) && (uuid_match_cnt > 0)))
    {
        return true;
    }

    return false;
}


/**@brief Function for adding UUID to the scanning filter.
 *
 * @param[in]     uuid       UUID, 16-bit size.
 * @param[in,out] p_scan_ctx Pointer to the Scanning Module instance.
 *
 * @retval NRF_SUCCESS              If the scanning started. Otherwise, an error code is returned, also if you tried to add a filter that was already added before.
 * @retval NRF_ERROR_NO_MEMORY      If the number of available filters is exceeded.
 */
static ret_code_t nrf_ble_scan_uuid_filter_add(nrf_ble_scan_t * const p_scan_ctx,
                                               ble_uuid_t     const * p_uuid)
{
    ble_uuid_t * p_uuid_filter = p_scan_ctx->scan_filters.uuid_filter.uuid;
    uint8_t    * p_counter     = &p_scan_ctx->scan_filters.uuid_filter.uuid_cnt;
    uint8_t      index;

    // If no memory.
    if (*p_counter >= NRF_BLE_SCAN_UUID_CNT)
    {
        return NRF_ERROR_NO_MEM;
    }

    // Check for duplicated filter.
    for (index = 0; index < NRF_BLE_SCAN_UUID_CNT; index++)
    {
        if (p_uuid_filter[index].uuid == p_uuid->uuid)
        {
            return NRF_SUCCESS;
        }
    }

    // Add UUID to the filter.
    p_uuid_filter[(*p_counter)++] = *p_uuid;
    NRF_LOG_DEBUG("Added filter on UUID %x", p_uuid->uuid);

    return NRF_SUCCESS;
}


#endif // NRF_BLE_SCAN_UUID_CNT


#if (NRF_BLE_SCAN_APPEARANCE_CNT)
/**@brief Function for comparing the provided appearance with the appearance in the advertisement packets.
 *
 * @param[in]     p_adv_report Advertising data to parse.
 * @param[in,out] p_scan_ctx   Pointer to the Scanning Module instance.
 *
 * @return      True if the appearances match. False otherwise.
 */
static bool adv_appearance_compare(ble_gap_evt_adv_report_t const * const p_adv_report,
                                   nrf_ble_scan_t           const * const p_scan_ctx)
{
    nrf_ble_scan_appearance_filter_t const * p_appearance_filter =
        &p_scan_ctx->scan_filters.appearance_filter;
    uint8_t const counter =
        p_scan_ctx->scan_filters.appearance_filter.appearance_cnt;
    uint8_t  index;
    uint16_t data_len;

    data_len = p_adv_report->data.len;

    // Verify if the advertised appearance matches the provided appearance.
    for (index = 0; index < counter; index++)
    {
        if (ble_advdata_appearance_find(p_adv_report->data.p_data,
                                        data_len,
                                        &p_appearance_filter->appearance[index]))
        {
            return true;
        }
    }
    return false;
}


/**@brief Function for adding appearance to the scanning filter.
 *
 * @param[in]     appearance       Appearance to be added.
 * @param[in,out] p_scan_ctx       Pointer to the Scanning Module instance.
 *
 * @retval NRF_SUCCESS             If the filter is added successfully or if you try to add a filter that was already added before.
 * @retval NRF_ERROR_NULL          If a NULL pointer is passed as input.
 * @retval NRF_ERROR_NO_MEMORY     If the number of available filters is exceeded.
 */
static ret_code_t nrf_ble_scan_appearance_filter_add(nrf_ble_scan_t * const p_scan_ctx,
                                                     uint16_t               appearance)
{
    uint16_t * p_appearance_filter = p_scan_ctx->scan_filters.appearance_filter.appearance;
    uint8_t  * p_counter           = &p_scan_ctx->scan_filters.appearance_filter.appearance_cnt;
    uint8_t    index;

    // If no memory.
    if (*p_counter >= NRF_BLE_SCAN_APPEARANCE_CNT)
    {
        return NRF_ERROR_NO_MEM;
    }

    // Check for duplicated filter.
    for ( index = 0; index < NRF_BLE_SCAN_APPEARANCE_CNT; index++)
    {
        if (p_appearance_filter[index] == appearance)
        {
            return NRF_SUCCESS;
        }
    }

    // Add appearance to the filter.
    p_appearance_filter[(*p_counter)++] = appearance;
    NRF_LOG_DEBUG("Added filter on appearance %x", appearance);
    return NRF_SUCCESS;
}


#endif // NRF_BLE_SCAN_APPEARANCE_CNT


ret_code_t nrf_ble_scan_filter_set(nrf_ble_scan_t     * const p_scan_ctx,
                                   nrf_ble_scan_filter_type_t type,
                                   void const               * p_data)
{
    VERIFY_PARAM_NOT_NULL(p_scan_ctx);
    VERIFY_PARAM_NOT_NULL(p_data);

    switch (type)
    {
#if (NRF_BLE_SCAN_NAME_CNT > 0)
        case SCAN_NAME_FILTER:
        {
            char * p_name = (char *)p_data;
            return nrf_ble_scan_name_filter_add(p_scan_ctx, p_name);
        }
#endif

#if (NRF_BLE_SCAN_SHORT_NAME_CNT > 0)
        case SCAN_SHORT_NAME_FILTER:
        {
            nrf_ble_scan_short_name_t * p_short_name = (nrf_ble_scan_short_name_t *)p_data;
            return nrf_ble_scan_short_name_filter_add(p_scan_ctx, p_short_name);
        }
#endif

#if (NRF_BLE_SCAN_ADDRESS_CNT > 0)
        case SCAN_ADDR_FILTER:
        {
            uint8_t * p_addr = (uint8_t *)p_data;
            return nrf_ble_scan_addr_filter_add(p_scan_ctx, p_addr);
        }
#endif

#if (NRF_BLE_SCAN_UUID_CNT > 0)
        case SCAN_UUID_FILTER:
        {
            ble_uuid_t * p_uuid = (ble_uuid_t *)p_data;
            return nrf_ble_scan_uuid_filter_add(p_scan_ctx, p_uuid);
        }
#endif

#if (NRF_BLE_SCAN_APPEARANCE_CNT > 0)
        case SCAN_APPEARANCE_FILTER:
        {
            uint16_t appearance = *((uint16_t *)p_data);
            return nrf_ble_scan_appearance_filter_add(p_scan_ctx, appearance);
        }
#endif

        default:
            return NRF_ERROR_INVALID_PARAM;
    }
}


ret_code_t nrf_ble_scan_all_filter_remove(nrf_ble_scan_t * const p_scan_ctx)
{
#if (NRF_BLE_SCAN_NAME_CNT > 0)
    nrf_ble_scan_name_filter_t * p_name_filter = &p_scan_ctx->scan_filters.name_filter;
    memset(p_name_filter->target_name, 0, sizeof(p_name_filter->target_name));
    p_name_filter->name_cnt = 0;
#endif

#if (NRF_BLE_SCAN_SHORT_NAME_CNT > 0)
    nrf_ble_scan_short_name_filter_t * p_short_name_filter =
        &p_scan_ctx->scan_filters.short_name_filter;
    memset(p_short_name_filter->short_name, 0, sizeof(p_short_name_filter->short_name));
    p_short_name_filter->name_cnt = 0;
#endif

#if (NRF_BLE_SCAN_ADDRESS_CNT > 0)
    nrf_ble_scan_addr_filter_t * p_addr_filter = &p_scan_ctx->scan_filters.addr_filter;
    memset(p_addr_filter->target_addr, 0, sizeof(p_addr_filter->target_addr));
    p_addr_filter->addr_cnt = 0;
#endif

#if (NRF_BLE_SCAN_UUID_CNT > 0)
    nrf_ble_scan_uuid_filter_t * p_uuid_filter = &p_scan_ctx->scan_filters.uuid_filter;
    memset(p_uuid_filter->uuid, 0, sizeof(p_uuid_filter->uuid));
    p_uuid_filter->uuid_cnt = 0;
#endif

#if (NRF_BLE_SCAN_APPEARANCE_CNT > 0)
    nrf_ble_scan_appearance_filter_t * p_appearance_filter =
        &p_scan_ctx->scan_filters.appearance_filter;
    memset(p_appearance_filter->appearance, 0, sizeof(p_appearance_filter->appearance));
    p_appearance_filter->appearance_cnt = 0;
#endif

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_scan_filters_enable(nrf_ble_scan_t * const p_scan_ctx,
                                       uint8_t                mode,
                                       bool                   match_all)
{
    VERIFY_PARAM_NOT_NULL(p_scan_ctx);

    // Check if the mode is correct.
    if ((!(mode & NRF_BLE_SCAN_ADDR_FILTER)) &&
        (!(mode & NRF_BLE_SCAN_NAME_FILTER)) &&
        (!(mode & NRF_BLE_SCAN_UUID_FILTER)) &&
        (!(mode & NRF_BLE_SCAN_SHORT_NAME_FILTER)) &&
        (!(mode & NRF_BLE_SCAN_APPEARANCE_FILTER)))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    ret_code_t err_code;

    // Disable filters.
    err_code = nrf_ble_scan_filters_disable(p_scan_ctx);
    ASSERT(err_code == NRF_SUCCESS);

    nrf_ble_scan_filters_t * p_filters = &p_scan_ctx->scan_filters;

    // Turn on the filters of your choice.
#if (NRF_BLE_SCAN_ADDRESS_CNT > 0)
    if (mode & NRF_BLE_SCAN_ADDR_FILTER)
    {
        p_filters->addr_filter.addr_filter_enabled = true;
    }
#endif

#if (NRF_BLE_SCAN_NAME_CNT > 0)
    if (mode & NRF_BLE_SCAN_NAME_FILTER)
    {
        p_filters->name_filter.name_filter_enabled = true;
    }
#endif

#if (NRF_BLE_SCAN_SHORT_NAME_CNT > 0)
    if (mode & NRF_BLE_SCAN_SHORT_NAME_FILTER)
    {
        p_filters->short_name_filter.short_name_filter_enabled = true;
    }
#endif

#if (NRF_BLE_SCAN_UUID_CNT > 0)
    if (mode & NRF_BLE_SCAN_UUID_FILTER)
    {
        p_filters->uuid_filter.uuid_filter_enabled = true;
    }
#endif

#if (NRF_BLE_SCAN_APPEARANCE_CNT > 0)
    if (mode & NRF_BLE_SCAN_APPEARANCE_FILTER)
    {
        p_filters->appearance_filter.appearance_filter_enabled = true;
    }
#endif

    // Select the filter mode.
    p_filters->all_filters_mode = match_all;

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_scan_filters_disable(nrf_ble_scan_t * const p_scan_ctx)
{
    VERIFY_PARAM_NOT_NULL(p_scan_ctx);

    // Disable all filters.
#if (NRF_BLE_SCAN_NAME_CNT > 0)
    bool * p_name_filter_enabled = &p_scan_ctx->scan_filters.name_filter.name_filter_enabled;
    *p_name_filter_enabled = false;
#endif

#if (NRF_BLE_SCAN_ADDRESS_CNT > 0)
    bool * p_addr_filter_enabled = &p_scan_ctx->scan_filters.addr_filter.addr_filter_enabled;
    *p_addr_filter_enabled = false;
#endif

#if (NRF_BLE_SCAN_UUID_CNT > 0)
    bool * p_uuid_filter_enabled = &p_scan_ctx->scan_filters.uuid_filter.uuid_filter_enabled;
    *p_uuid_filter_enabled = false;
#endif

#if (NRF_BLE_SCAN_APPEARANCE_CNT > 0)
    bool * p_appearance_filter_enabled =
        &p_scan_ctx->scan_filters.appearance_filter.appearance_filter_enabled;
    *p_appearance_filter_enabled = false;
#endif

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_scan_filter_get(nrf_ble_scan_t * const   p_scan_ctx,
                                   nrf_ble_scan_filters_t * p_status)
{
    VERIFY_PARAM_NOT_NULL(p_scan_ctx);
    VERIFY_PARAM_NOT_NULL(p_status);

    *p_status = p_scan_ctx->scan_filters;

    return NRF_SUCCESS;
}


#endif // NRF_BLE_SCAN_FILTER_ENABLE

/**@brief Function for calling the BLE_GAP_EVT_ADV_REPORT event to check whether the received
 *        scanning data matches the scan configuration.
 *
 * @param[in] p_scan_ctx    Pointer to the Scanning Module instance.
 * @param[in] p_adv_report  Advertising report.
 */
static void nrf_ble_scan_on_adv_report(nrf_ble_scan_t           const * const p_scan_ctx,
                                       ble_gap_evt_adv_report_t const * const p_adv_report)
{
    scan_evt_t scan_evt;

#if (NRF_BLE_SCAN_FILTER_ENABLE == 1)
    uint8_t filter_cnt       = 0;
    uint8_t filter_match_cnt = 0;
#endif

    memset(&scan_evt, 0, sizeof(scan_evt));

    scan_evt.p_scan_params = &p_scan_ctx->scan_params;

    // If the whitelist is used, do not check the filters and return.
    if (is_whitelist_used(p_scan_ctx))
    {
        scan_evt.scan_evt_id        = NRF_BLE_SCAN_EVT_WHITELIST_ADV_REPORT;
        scan_evt.params.p_not_found = p_adv_report;
        p_scan_ctx->evt_handler(&scan_evt);

        UNUSED_RETURN_VALUE(sd_ble_gap_scan_start(NULL, &p_scan_ctx->scan_buffer));
        nrf_ble_scan_connect_with_target(p_scan_ctx, p_adv_report);

        return;
    }

#if (NRF_BLE_SCAN_FILTER_ENABLE == 1)
    bool const all_filter_mode   = p_scan_ctx->scan_filters.all_filters_mode;
    bool       is_filter_matched = false;

#if (NRF_BLE_SCAN_ADDRESS_CNT > 0)
    bool const addr_filter_enabled = p_scan_ctx->scan_filters.addr_filter.addr_filter_enabled;
#endif

#if (NRF_BLE_SCAN_NAME_CNT > 0)
    bool const name_filter_enabled = p_scan_ctx->scan_filters.name_filter.name_filter_enabled;
#endif

#if (NRF_BLE_SCAN_SHORT_NAME_CNT > 0)
    bool const short_name_filter_enabled =
        p_scan_ctx->scan_filters.short_name_filter.short_name_filter_enabled;
#endif

#if (NRF_BLE_SCAN_UUID_CNT > 0)
    bool const uuid_filter_enabled = p_scan_ctx->scan_filters.uuid_filter.uuid_filter_enabled;
#endif

#if (NRF_BLE_SCAN_APPEARANCE_CNT > 0)
    bool const appearance_filter_enabled =
        p_scan_ctx->scan_filters.appearance_filter.appearance_filter_enabled;
#endif


#if (NRF_BLE_SCAN_ADDRESS_CNT > 0)
    // Check the address filter.
    if (addr_filter_enabled)
    {
        // Number of active filters.
        filter_cnt++;
        if (adv_addr_compare(p_adv_report, p_scan_ctx))
        {
            // Number of filters matched.
            filter_match_cnt++;
            // Information about the filters matched.
            scan_evt.params.filter_match.filter_match.address_filter_match = true;
            is_filter_matched = true;
        }
    }
#endif

#if (NRF_BLE_SCAN_NAME_CNT > 0)
    // Check the name filter.
    if (name_filter_enabled)
    {
        filter_cnt++;
        if (adv_name_compare(p_adv_report, p_scan_ctx))
        {
            filter_match_cnt++;

            // Information about the filters matched.
            scan_evt.params.filter_match.filter_match.name_filter_match = true;
            is_filter_matched = true;
        }
    }
#endif

#if (NRF_BLE_SCAN_SHORT_NAME_CNT > 0)
    if (short_name_filter_enabled)
    {
        filter_cnt++;
        if (adv_short_name_compare(p_adv_report, p_scan_ctx))
        {
            filter_match_cnt++;

            // Information about the filters matched.
            scan_evt.params.filter_match.filter_match.short_name_filter_match = true;
            is_filter_matched = true;
        }
    }
#endif

#if (NRF_BLE_SCAN_UUID_CNT > 0)
    // Check the UUID filter.
    if (uuid_filter_enabled)
    {
        filter_cnt++;
        if (adv_uuid_compare(p_adv_report, p_scan_ctx))
        {
            filter_match_cnt++;
            // Information about the filters matched.
            scan_evt.params.filter_match.filter_match.uuid_filter_match = true;
            is_filter_matched = true;
        }
    }
#endif

#if (NRF_BLE_SCAN_APPEARANCE_CNT > 0)
    // Check the appearance filter.
    if (appearance_filter_enabled)
    {
        filter_cnt++;
        if (adv_appearance_compare(p_adv_report, p_scan_ctx))
        {
            filter_match_cnt++;
            // Information about the filters matched.
            scan_evt.params.filter_match.filter_match.appearance_filter_match = true;
            is_filter_matched = true;
        }
    }

    scan_evt.scan_evt_id = NRF_BLE_SCAN_EVT_NOT_FOUND;
#endif

    scan_evt.params.filter_match.p_adv_report = p_adv_report;

    // In the multifilter mode, the number of the active filters must equal the number of the filters matched to generate the notification.
    if (all_filter_mode && (filter_match_cnt == filter_cnt))
    {
        scan_evt.scan_evt_id = NRF_BLE_SCAN_EVT_FILTER_MATCH;
        nrf_ble_scan_connect_with_target(p_scan_ctx, p_adv_report);
    }
    // In the normal filter mode, only one filter match is needed to generate the notification to the main application.
    else if ((!all_filter_mode) && is_filter_matched)
    {
        scan_evt.scan_evt_id = NRF_BLE_SCAN_EVT_FILTER_MATCH;
        nrf_ble_scan_connect_with_target(p_scan_ctx, p_adv_report);
    }
    else
    {
        scan_evt.scan_evt_id        = NRF_BLE_SCAN_EVT_NOT_FOUND;
        scan_evt.params.p_not_found = p_adv_report;

    }

    // If the event handler is not NULL, notify the main application.
    if (p_scan_ctx->evt_handler != NULL)
    {
        p_scan_ctx->evt_handler(&scan_evt);
    }

#endif // NRF_BLE_SCAN_FILTER_ENABLE

    // Resume the scanning.
    UNUSED_RETURN_VALUE(sd_ble_gap_scan_start(NULL, &p_scan_ctx->scan_buffer));
}


/**@brief Function for checking whether the whitelist is used.
 *
 * @param[in] p_scan_ctx   Scanning Module instance.
 */
bool is_whitelist_used(nrf_ble_scan_t const * const p_scan_ctx)
{
    if (p_scan_ctx->scan_params.filter_policy == BLE_GAP_SCAN_FP_WHITELIST ||
        p_scan_ctx->scan_params.filter_policy == BLE_GAP_SCAN_FP_WHITELIST_NOT_RESOLVED_DIRECTED)
    {
        return true;
    }

    return false;
}


/**@brief Function for restoring the default scanning parameters.
 *
 * @param[out] p_scan_ctx    Pointer to the Scanning Module instance.
 */
static void nrf_ble_scan_default_param_set(nrf_ble_scan_t * const p_scan_ctx)
{
    // Set the default parameters.
    p_scan_ctx->scan_params.active        = 1;
    p_scan_ctx->scan_params.interval      = NRF_BLE_SCAN_SCAN_INTERVAL;
    p_scan_ctx->scan_params.window        = NRF_BLE_SCAN_SCAN_WINDOW;
    p_scan_ctx->scan_params.timeout       = NRF_BLE_SCAN_SCAN_DURATION;
    p_scan_ctx->scan_params.filter_policy = BLE_GAP_SCAN_FP_ACCEPT_ALL;
    p_scan_ctx->scan_params.scan_phys     = BLE_GAP_PHY_1MBPS;
}


/**@brief Function for setting the default connection parameters.
 *
 * @param[out] p_scan_ctx    Pointer to the Scanning Module instance.
 */
static void nrf_ble_scan_default_conn_param_set(nrf_ble_scan_t * const p_scan_ctx)
{
    p_scan_ctx->conn_params.conn_sup_timeout =
        (uint16_t)MSEC_TO_UNITS(NRF_BLE_SCAN_SUPERVISION_TIMEOUT, UNIT_10_MS);
    p_scan_ctx->conn_params.min_conn_interval =
        (uint16_t)MSEC_TO_UNITS(NRF_BLE_SCAN_MIN_CONNECTION_INTERVAL, UNIT_1_25_MS);
    p_scan_ctx->conn_params.max_conn_interval =
        (uint16_t)MSEC_TO_UNITS(NRF_BLE_SCAN_MAX_CONNECTION_INTERVAL, UNIT_1_25_MS);
    p_scan_ctx->conn_params.slave_latency =
        (uint16_t)NRF_BLE_SCAN_SLAVE_LATENCY;
}


/**@brief Function for calling the BLE_GAP_EVT_TIMEOUT event.
 *
 * @param[in] p_scan_ctx  Pointer to the Scanning Module instance.
 * @param[in] p_gap       GAP event structure.
 */
static void nrf_ble_scan_on_timeout(nrf_ble_scan_t const * const p_scan_ctx,
                                    ble_gap_evt_t  const * const p_gap)
{
    ble_gap_evt_timeout_t const * p_timeout = &p_gap->params.timeout;
    scan_evt_t                    scan_evt;

    memset(&scan_evt, 0, sizeof(scan_evt));

    if (p_timeout->src == BLE_GAP_TIMEOUT_SRC_SCAN)
    {
        NRF_LOG_DEBUG("BLE_GAP_SCAN_TIMEOUT");
        if (p_scan_ctx->evt_handler != NULL)
        {
            scan_evt.scan_evt_id        = NRF_BLE_SCAN_EVT_SCAN_TIMEOUT;
            scan_evt.p_scan_params      = &p_scan_ctx->scan_params;
            scan_evt.params.timeout.src = p_timeout->src;

            p_scan_ctx->evt_handler(&scan_evt);
        }
    }
}


/**@brief Function for calling the BLE_GAP_EVT_SCAN_REQ_REPORT event.
 *
 * @param[in] p_scan_ctx  Pointer to the Scanning Module instance.
 * @param[in] p_gap       GAP event structure.
 */
static void nrf_ble_scan_on_req_report(nrf_ble_scan_t const * const p_scan_ctx,
                                       ble_gap_evt_t  const * const p_gap)
{
    ble_gap_evt_scan_req_report_t const * p_req_report = &p_gap->params.scan_req_report;
    scan_evt_t                            scan_evt;

    memset(&scan_evt, 0, sizeof(scan_evt));

    if (p_scan_ctx->evt_handler != NULL)
    {
        scan_evt.scan_evt_id       = NRF_BLE_SCAN_EVT_SCAN_REQ_REPORT;
        scan_evt.p_scan_params     = &p_scan_ctx->scan_params;
        scan_evt.params.req_report = *p_req_report;

        p_scan_ctx->evt_handler(&scan_evt);
    }
}


/**@brief Function for stopping the scanning.
 */
void nrf_ble_scan_stop(void)
{
    // It is ok to ignore the function return value here, because this function can return NRF_SUCCESS or
    // NRF_ERROR_INVALID_STATE, when app is not in the scanning state.
    UNUSED_RETURN_VALUE(sd_ble_gap_scan_stop());
}


ret_code_t nrf_ble_scan_init(nrf_ble_scan_t            * const p_scan_ctx,
                             nrf_ble_scan_init_t const * const p_init,
                             nrf_ble_scan_evt_handler_t        evt_handler)
{
    VERIFY_PARAM_NOT_NULL(p_scan_ctx);

    p_scan_ctx->evt_handler = evt_handler;

#if (NRF_BLE_SCAN_FILTER_ENABLE == 1)
    // Disable all scanning filters.
    memset(&p_scan_ctx->scan_filters, 0, sizeof(p_scan_ctx->scan_filters));
#endif

    // If the pointer to the initialization structure exist, use it to scan the configuration.
    if (p_init != NULL)
    {
        p_scan_ctx->connect_if_match = p_init->connect_if_match;
        p_scan_ctx->conn_cfg_tag     = p_init->conn_cfg_tag;

        if (p_init->p_scan_param != NULL)
        {
            p_scan_ctx->scan_params = *p_init->p_scan_param;
        }
        else
        {
            // Use the default static configuration.
            nrf_ble_scan_default_param_set(p_scan_ctx);
        }

        if (p_init->p_conn_param != NULL)
        {
            p_scan_ctx->conn_params = *p_init->p_conn_param;
        }
        else
        {
            // Use the default static configuration.
            nrf_ble_scan_default_conn_param_set(p_scan_ctx);
        }
    }
    // If pointer is NULL, use the static default configuration.
    else
    {
        nrf_ble_scan_default_param_set(p_scan_ctx);
        nrf_ble_scan_default_conn_param_set(p_scan_ctx);

        p_scan_ctx->connect_if_match = false;
    }

    // Assign a buffer where the advertising reports are to be stored by the SoftDevice.
    p_scan_ctx->scan_buffer.p_data = p_scan_ctx->scan_buffer_data;
    p_scan_ctx->scan_buffer.len    = NRF_BLE_SCAN_BUFFER;

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_scan_start(nrf_ble_scan_t const * const p_scan_ctx)
{
    VERIFY_PARAM_NOT_NULL(p_scan_ctx);

    ret_code_t err_code;
    scan_evt_t scan_evt;

    memset(&scan_evt, 0, sizeof(scan_evt));

    nrf_ble_scan_stop();

    // If the whitelist is used and the event handler is not NULL, send the whitelist request to the main application.
    if (is_whitelist_used(p_scan_ctx))
    {
        if (p_scan_ctx->evt_handler != NULL)
        {
            scan_evt.scan_evt_id = NRF_BLE_SCAN_EVT_WHITELIST_REQUEST;
            p_scan_ctx->evt_handler(&scan_evt);
        }
    }

    // Start the scanning.
    err_code = sd_ble_gap_scan_start(&p_scan_ctx->scan_params, &p_scan_ctx->scan_buffer);

    // It is okay to ignore this error, because the scan stopped earlier.
    if ((err_code != NRF_ERROR_INVALID_STATE) && (err_code != NRF_SUCCESS))
    {
        NRF_LOG_ERROR("sd_ble_gap_scan_start returned 0x%x", err_code);
        return (err_code);
    }
    NRF_LOG_DEBUG("Scanning");

    return NRF_SUCCESS;
}


ret_code_t nrf_ble_scan_params_set(nrf_ble_scan_t              * const p_scan_ctx,
                                   ble_gap_scan_params_t const * const p_scan_param)
{
    VERIFY_PARAM_NOT_NULL(p_scan_ctx);

    nrf_ble_scan_stop();

    if (p_scan_param != NULL)
    {
        // Assign new scanning parameters.
        p_scan_ctx->scan_params = *p_scan_param;
    }
    else
    {
        // If NULL, use the default static configuration.
        nrf_ble_scan_default_param_set(p_scan_ctx);
    }

    NRF_LOG_DEBUG("Scanning parameters have been changed successfully");

    return NRF_SUCCESS;
}


/**@brief Function for calling the BLE_GAP_EVT_CONNECTED event.
 *
 * @param[in] p_scan_ctx  Pointer to the Scanning Module instance.
 * @param[in] p_gap_evt   GAP event structure.
 */
static void nrf_ble_scan_on_connected_evt(nrf_ble_scan_t const * const p_scan_ctx,
                                          ble_gap_evt_t  const * const p_gap_evt)
{
    scan_evt_t scan_evt;

    memset(&scan_evt, 0, sizeof(scan_evt));
    scan_evt.scan_evt_id                  = NRF_BLE_SCAN_EVT_CONNECTED;
    scan_evt.params.connected.p_connected = &p_gap_evt->params.connected;
    scan_evt.params.connected.conn_handle = p_gap_evt->conn_handle;
    scan_evt.p_scan_params                = &p_scan_ctx->scan_params;

    if (p_scan_ctx->evt_handler != NULL)
    {
        p_scan_ctx->evt_handler(&scan_evt);
    }
}


ret_code_t nrf_ble_scan_copy_addr_to_sd_gap_addr(ble_gap_addr_t * p_gap_addr,
                                                 const uint8_t    addr[BLE_GAP_ADDR_LEN])
{
    uint16_t addr_type;

    addr_type = nrf_ble_scan_address_type_decode(addr);

    if (addr_type == BLE_ERROR_GAP_INVALID_BLE_ADDR)
    {
        return BLE_ERROR_GAP_INVALID_BLE_ADDR;
    }

    p_gap_addr->addr_type = addr_type;

    for (uint8_t i = 0; i < BLE_GAP_ADDR_LEN; ++i)
    {
        p_gap_addr->addr[i] = addr[BLE_GAP_ADDR_LEN - (i + 1)];
    }

    return NRF_SUCCESS;
}


void nrf_ble_scan_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_contex)
{
    nrf_ble_scan_t                 * p_scan_data  = (nrf_ble_scan_t *)p_contex;
    ble_gap_evt_adv_report_t const * p_adv_report = &p_ble_evt->evt.gap_evt.params.adv_report;
    ble_gap_evt_t const            * p_gap_evt    = &p_ble_evt->evt.gap_evt;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_ADV_REPORT:
            nrf_ble_scan_on_adv_report(p_scan_data, p_adv_report);
            break;

        case BLE_GAP_EVT_TIMEOUT:
            nrf_ble_scan_on_timeout(p_scan_data, p_gap_evt);
            break;

        case BLE_GAP_EVT_SCAN_REQ_REPORT:
            nrf_ble_scan_on_req_report(p_scan_data, p_gap_evt);

            break;

        case BLE_GAP_EVT_CONNECTED:
            nrf_ble_scan_on_connected_evt(p_scan_data, p_gap_evt);
            break;

        default:
            break;
    }
}


#endif // NRF_BLE_SCAN_ENABLED

