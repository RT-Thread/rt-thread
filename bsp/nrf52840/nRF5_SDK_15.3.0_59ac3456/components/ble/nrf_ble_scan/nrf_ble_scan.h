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

/** @file
 *
 * @defgroup nrf_ble_scan Scanning Module
 * @{
 * @ingroup ble_sdk_lib
 * @brief Module for handling the BLE scanning.
 *
 * @details The Scanning Module handles the BLE scanning for your application.
 *          The module offers several criteria for filtering the devices available for connection,
 *          and it can also work in the simple mode without using the filtering.
 *          If an event handler is provided, your main application can react to a filter match or to the need of setting the whitelist.
 *          The module can also be configured to automatically
 *          connect after it matches a filter or a device from the whitelist.
 *
 * @note    The Scanning Module also supports applications with a multicentral link.
 */

#ifndef NRF_BLE_SCAN_H__
#define NRF_BLE_SCAN_H__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "ble.h"
#include "ble_gap.h"
#include "app_util.h"
#include "sdk_errors.h"
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@defgroup NRF_BLE_SCAN_FILTER_MODE Filter modes
 * @{ */
#define NRF_BLE_SCAN_NAME_FILTER       (0x01) /**< Filters the device name. */
#define NRF_BLE_SCAN_ADDR_FILTER       (0x02) /**< Filters the device address. */
#define NRF_BLE_SCAN_UUID_FILTER       (0x04) /**< Filters the UUID. */
#define NRF_BLE_SCAN_APPEARANCE_FILTER (0x08) /**< Filters the appearance. */
#define NRF_BLE_SCAN_SHORT_NAME_FILTER (0x10) /**< Filters the device short name. */
#define NRF_BLE_SCAN_ALL_FILTER        (0x1F) /**< Uses the combination of all filters. */
/* @} */

/**@brief Macro for defining a nrf_ble_scan instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define NRF_BLE_SCAN_DEF(_name)                            \
    static nrf_ble_scan_t _name;                           \
    NRF_SDH_BLE_OBSERVER(_name ## _ble_obs,                \
                         NRF_BLE_SCAN_OBSERVER_PRIO,       \
                         nrf_ble_scan_on_ble_evt, &_name); \


/**@brief Enumeration for scanning events.
 *
 * @details These events are propagated to the main application if a handler is provided during
 *          the initialization of the Scanning Module. @ref NRF_BLE_SCAN_EVT_WHITELIST_REQUEST cannot be
 *          ignored if whitelist is used.
 */
typedef enum
{
    NRF_BLE_SCAN_EVT_FILTER_MATCH,         /**< A filter is matched or all filters are matched in the multifilter mode. */
    NRF_BLE_SCAN_EVT_WHITELIST_REQUEST,    /**< Request the whitelist from the main application. For whitelist scanning to work, the whitelist must be set when this event occurs. */
    NRF_BLE_SCAN_EVT_WHITELIST_ADV_REPORT, /**< Send notification to the main application when a device from the whitelist is found. */
    NRF_BLE_SCAN_EVT_NOT_FOUND,            /**< The filter was not matched for the scan data. */
    NRF_BLE_SCAN_EVT_SCAN_TIMEOUT,         /**< Scan timeout. */
    NRF_BLE_SCAN_EVT_SCAN_REQ_REPORT,      /**< Scan request report. */
    NRF_BLE_SCAN_EVT_CONNECTING_ERROR,     /**< Error occurred when establishing the connection. In this event, an error is passed from the function call @ref sd_ble_gap_connect. */
    NRF_BLE_SCAN_EVT_CONNECTED             /**< Connected to device. */
} nrf_ble_scan_evt_t;


/**@brief Types of filters.
 */
typedef enum
{
    SCAN_NAME_FILTER,       /**< Filter for names. */
    SCAN_SHORT_NAME_FILTER, /**< Filter for short names. */
    SCAN_ADDR_FILTER,       /**< Filter for addresses. */
    SCAN_UUID_FILTER,       /**< Filter for UUIDs. */
    SCAN_APPEARANCE_FILTER, /**< Filter for appearances. */
} nrf_ble_scan_filter_type_t;


typedef struct
{
    char const * p_short_name;       /**< Pointer to the short name. */
    uint8_t      short_name_min_len; /**< Minimum length of the short name. */
} nrf_ble_scan_short_name_t;

/**@brief Structure for Scanning Module initialization.
 */
typedef struct
{
    ble_gap_scan_params_t const * p_scan_param;     /**< BLE GAP scan parameters required to initialize the module. Can be initialized as NULL. If NULL, the parameters required to initialize the module are loaded from the static configuration. */
    bool                          connect_if_match; /**< If set to true, the module automatically connects after a filter match or successful identification of a device from the whitelist. */
    ble_gap_conn_params_t const * p_conn_param;     /**< Connection parameters. Can be initialized as NULL. If NULL, the default static configuration is used. */
    uint8_t                       conn_cfg_tag;     /**< Variable to keep track of what connection settings will be used if a filer match or a whitelist match results in a connection. */
} nrf_ble_scan_init_t;


/**@brief Structure for setting the filter status.
 *
 * @details This structure is used for sending filter status to the main application.
 */
typedef struct
{
    uint8_t name_filter_match       : 1; /**< Set to 1 if name filter is matched. */
    uint8_t address_filter_match    : 1; /**< Set to 1 if address filter is matched. */
    uint8_t uuid_filter_match       : 1; /**< Set to 1 if uuid filter is matched. */
    uint8_t appearance_filter_match : 1; /**< Set to 1 if appearance filter is matched. */
    uint8_t short_name_filter_match : 1; /**< Set to 1 if short name filter is matched. */
} nrf_ble_scan_filter_match;


/**@brief Event structure for @ref NRF_BLE_SCAN_EVT_FILTER_MATCH.
 */
typedef struct
{
    ble_gap_evt_adv_report_t const * p_adv_report; /**< Event structure for @ref BLE_GAP_EVT_ADV_REPORT. This data allows the main application to establish connection. */
    nrf_ble_scan_filter_match        filter_match; /**< Matching filters. Information about matched filters. */
} nrf_ble_scan_evt_filter_match_t;


/**@brief Event structure for @ref NRF_BLE_SCAN_EVT_CONNECTING_ERROR.
 */
typedef struct
{
    ret_code_t err_code; /**< Indicates success or failure of an API procedure. In case of failure, a comprehensive error code indicating the cause or reason for failure is provided. */
} nrf_ble_scan_evt_connecting_err_t;


/**@brief Event structure for @ref NRF_BLE_SCAN_EVT_CONNECTED.
 */
typedef struct
{
    ble_gap_evt_connected_t const * p_connected; /**< Connected event parameters. */
    uint16_t                        conn_handle; /**< Connection handle of the device on which the event occurred. */
} nrf_ble_scan_evt_connected_t;


/**@brief Structure for Scanning Module event data.
 *
 * @details This structure is used to send module event data to the main application when an event occurs.
 */
typedef struct
{
    nrf_ble_scan_evt_t scan_evt_id; /**< Type of event propagated to the main application. */
    union
    {
        nrf_ble_scan_evt_filter_match_t   filter_match;           /**< Scan filter match. */
        ble_gap_evt_scan_req_report_t     req_report;             /**< Scan request report parameters. */
        ble_gap_evt_timeout_t             timeout;                /**< Timeout event parameters. */
        ble_gap_evt_adv_report_t const  * p_whitelist_adv_report; /**< Advertising report event parameters for whitelist. */
        ble_gap_evt_adv_report_t const  * p_not_found;            /**< Advertising report event parameters when filter is not found. */
        nrf_ble_scan_evt_connected_t      connected;              /**< Connected event parameters. */
        nrf_ble_scan_evt_connecting_err_t connecting_err;         /**< Error event when connecting. Propagates the error code returned by the SoftDevice API @ref sd_ble_gap_scan_start. */
    } params;
    ble_gap_scan_params_t const * p_scan_params;                  /**< GAP scanning parameters. These parameters are needed to establish connection. */
} scan_evt_t;


/**@brief BLE scanning event handler type.
 */
typedef void (*nrf_ble_scan_evt_handler_t)(scan_evt_t const * p_scan_evt);


#if (NRF_BLE_SCAN_FILTER_ENABLE == 1)

#if (NRF_BLE_SCAN_NAME_CNT > 0)
typedef struct
{
    char    target_name[NRF_BLE_SCAN_NAME_CNT][NRF_BLE_SCAN_NAME_MAX_LEN]; /**< Names that the main application will scan for, and that will be advertised by the peripherals. */
    uint8_t name_cnt;                                                      /**< Name filter counter. */
    bool    name_filter_enabled;                                           /**< Flag to inform about enabling or disabling this filter. */
} nrf_ble_scan_name_filter_t;
#endif

#if (NRF_BLE_SCAN_SHORT_NAME_CNT > 0)
typedef struct
{
    struct
    {
        char    short_target_name[NRF_BLE_SCAN_SHORT_NAME_MAX_LEN]; /**< Short names that the main application will scan for, and that will be advertised by the peripherals. */
        uint8_t short_name_min_len;                                 /**< Minimum length of the short name. */
    } short_name[NRF_BLE_SCAN_SHORT_NAME_CNT];
    uint8_t name_cnt;                                               /**< Short name filter counter. */
    bool    short_name_filter_enabled;                              /**< Flag to inform about enabling or disabling this filter. */
} nrf_ble_scan_short_name_filter_t;
#endif

#if (NRF_BLE_SCAN_ADDRESS_CNT > 0)
typedef struct
{
    ble_gap_addr_t target_addr[NRF_BLE_SCAN_ADDRESS_CNT]; /**< Addresses in the same format as the format used by the SoftDevice that the main application will scan for, and that will be advertised by the peripherals. */
    uint8_t        addr_cnt;                              /**< Address filter counter. */
    bool           addr_filter_enabled;                   /**< Flag to inform about enabling or disabling this filter. */
} nrf_ble_scan_addr_filter_t;
#endif

#if (NRF_BLE_SCAN_UUID_CNT > 0)
typedef struct
{
    ble_uuid_t uuid[NRF_BLE_SCAN_UUID_CNT]; /**< UUIDs that the main application will scan for, and that will be advertised by the peripherals. */
    uint8_t    uuid_cnt;                    /**< UUID filter counter. */
    bool       uuid_filter_enabled;         /**< Flag to inform about enabling or disabling this filter. */
} nrf_ble_scan_uuid_filter_t;
#endif

#if (NRF_BLE_SCAN_APPEARANCE_CNT > 0)
typedef struct
{
    uint16_t appearance[NRF_BLE_SCAN_APPEARANCE_CNT]; /**< Apperances that the main application will scan for, and that will be advertised by the peripherals. */
    uint8_t  appearance_cnt;                          /**< Appearance filter counter. */
    bool     appearance_filter_enabled;               /**< Flag to inform about enabling or disabling this filter. */
} nrf_ble_scan_appearance_filter_t;
#endif

/**@brief Filters data.
 *
 * @details This structure contains all filter data and the information about enabling and disabling any type of filters.
 *          Flag all_filter_mode informs about the filter mode. If this flag is set, then all types of enabled
 *          filters must be matched for the module to send a notification to the main application. Otherwise, it is enough to match
 *          one of filters to send notification.
 */
typedef struct
{
#if (NRF_BLE_SCAN_NAME_CNT > 0)
    nrf_ble_scan_name_filter_t name_filter; /**< Name filter data. */
#endif
#if (NRF_BLE_SCAN_SHORT_NAME_CNT > 0)
    nrf_ble_scan_short_name_filter_t short_name_filter; /**< Short name filter data. */
#endif
#if (NRF_BLE_SCAN_ADDRESS_CNT > 0)
    nrf_ble_scan_addr_filter_t addr_filter; /**< Address filter data. */
#endif
#if (NRF_BLE_SCAN_UUID_CNT > 0)
    nrf_ble_scan_uuid_filter_t uuid_filter; /**< UUID filter data. */
#endif
#if (NRF_BLE_SCAN_APPEARANCE_CNT > 0)
    nrf_ble_scan_appearance_filter_t appearance_filter; /**< Appearance filter data. */
#endif
    bool all_filters_mode;                              /**< Filter mode. If true, all set filters must be matched to generate an event.*/
} nrf_ble_scan_filters_t;

#endif // NRF_BLE_SCAN_FILTER_ENABLE

/**@brief Scan module instance. Options for the different scanning modes.
 *
 * @details This structure stores all module settings. It is used to enable or disable scanning modes
 *          and to configure filters.
 */
typedef struct
{
#if (NRF_BLE_SCAN_FILTER_ENABLE == 1)
    nrf_ble_scan_filters_t scan_filters;                              /**< Filter data. */
#endif
    bool                       connect_if_match;                      /**< If set to true, the module automatically connects after a filter match or successful identification of a device from the whitelist. */
    ble_gap_conn_params_t      conn_params;                           /**< Connection parameters. */
    uint8_t                    conn_cfg_tag;                          /**< Variable to keep track of what connection settings will be used if a filer match or a whitelist match results in a connection. */
    ble_gap_scan_params_t      scan_params;                           /**< GAP scanning parameters. */
    nrf_ble_scan_evt_handler_t evt_handler;                           /**< Handler for the scanning events. Can be initialized as NULL if no handling is implemented in the main application. */
    uint8_t                    scan_buffer_data[NRF_BLE_SCAN_BUFFER]; /**< Buffer where advertising reports will be stored by the SoftDevice. */
    ble_data_t                 scan_buffer;                           /**< Structure-stored pointer to the buffer where advertising reports will be stored by the SoftDevice. */
} nrf_ble_scan_t;


/**@brief Function for indicating that the Scanning Module is using the whitelist.
 *
 * @param[in] p_scan_ctx Pointer to the Scanning Module instance.
 *
 * @return Whether the whitelist is used.
 */
bool is_whitelist_used(nrf_ble_scan_t const * const p_scan_ctx);


/**@brief Function for initializing the Scanning Module.
 *
 * @param[out] p_scan_ctx   Pointer to the Scanning Module instance. This structure must be supplied by
 *                          the application. It is initialized by this function and is later used
 *                          to identify this particular module instance.
 * 
 * @param[in]  p_init       Can be initialized as NULL. If NULL, the parameters required to initialize
 *                          the module are loaded from static configuration.
 *                          If module is to establish the connection automatically, this must be initialized
 *                          with the relevant data.
 * @param[in]  evt_handler  Handler for the scanning events.
 *                          Can be initialized as NULL if no handling is implemented in the main application.
 *
 * @retval NRF_SUCCESS      If initialization was successful.
 * @retval NRF_ERROR_NULL   When the NULL pointer is passed as input.
 */
ret_code_t nrf_ble_scan_init(nrf_ble_scan_t            * const p_scan_ctx,
                             nrf_ble_scan_init_t const * const p_init,
                             nrf_ble_scan_evt_handler_t        evt_handler);


/**@brief Function for starting scanning.
 *
 * @details This function starts the scanning according to the configuration set during the initialization.
 *
 * @param[in] p_scan_ctx       Pointer to the Scanning Module instance.
 *
 * @retval    NRF_SUCCESS      If scanning started. Otherwise, an error code is returned.
 * @retval    NRF_ERROR_NULL   If NULL pointer is passed as input.
 *
 * @return                     This API propagates the error code returned by the
 *                             SoftDevice API @ref sd_ble_gap_scan_start.
 */
ret_code_t nrf_ble_scan_start(nrf_ble_scan_t const * const p_scan_ctx);


/**@brief Function for stopping scanning.
 */
void nrf_ble_scan_stop(void);


#if (NRF_BLE_SCAN_FILTER_ENABLE == 1)

/**@brief Function for enabling filtering.
 *
 * @details The filters can be combined with each other. For example, you can enable one filter or several filters.
 *          For example, (NRF_BLE_SCAN_NAME_FILTER | NRF_BLE_SCAN_UUID_FILTER) enables UUID and name filters.
 *
 * @param[in] mode                  Filter mode: @ref NRF_BLE_SCAN_FILTER_MODE.
 * @param[in] match_all             If this flag is set, all types of enabled filters must be matched
 *                                  before generating @ref NRF_BLE_SCAN_EVT_FILTER_MATCH to the main application. Otherwise, it is enough to match
 *                                  one filter to trigger the filter match event.
 * @param[in] p_scan_ctx            Pointer to the Scanning Module instance.
 *
 * @retval NRF_SUCCESS              If the filters are enabled successfully.
 * @retval NRF_ERROR_INVALID_PARAM  If the filter mode is incorrect. Available filter modes: @ref NRF_BLE_SCAN_FILTER_MODE.
 * @retval NRF_ERROR_NULL           If a NULL pointer is passed as input.
 */
ret_code_t nrf_ble_scan_filters_enable(nrf_ble_scan_t * const p_scan_ctx,
                                       uint8_t                mode,
                                       bool                   match_all);


/**@brief Function for disabling filtering.
 *
 * @details This function disables all filters.
 *          Even if the automatic connection establishing is enabled,
 *          the connection will not be established with the first
            device found after this function is called.
 *
 * @param[in] p_scan_ctx            Pointer to the Scanning Module instance.
 *
 * @retval NRF_SUCCESS              If filters are disabled successfully.
 * @retval NRF_ERROR_NULL           If a NULL pointer is passed as input.
 */
ret_code_t nrf_ble_scan_filters_disable(nrf_ble_scan_t * const p_scan_ctx);


/**@brief Function for getting filter status.
 *
 * @details This function returns the filter setting and whether it is enabled or disabled.

 * @param[out] p_status              Filter status.
 * @param[in]  p_scan_ctx            Pointer to the Scanning Module instance.
 *
 * @retval NRF_SUCCESS               If filter status is returned.
 * @retval NRF_ERROR_NULL            If a NULL pointer is passed as input.
 */
ret_code_t nrf_ble_scan_filter_get(nrf_ble_scan_t   * const p_scan_ctx,
                                   nrf_ble_scan_filters_t * p_status);


/**@brief Function for adding any type of filter to the scanning.
 *
 * @details This function adds a new filter by type @ref nrf_ble_scan_filter_type_t.
 *          The filter will be added if the number of filters of a given type does not exceed @ref NRF_BLE_SCAN_UUID_CNT,
 *          @ref NRF_BLE_SCAN_NAME_CNT, @ref NRF_BLE_SCAN_ADDRESS_CNT, or @ref NRF_BLE_SCAN_APPEARANCE_CNT, depending on the filter type,
 *          and if the same filter has not already been set.
 *
 * @param[in,out] p_scan_ctx        Pointer to the Scanning Module instance.
 * @param[in]     type              Filter type.
 * @param[in]     p_data            The filter data to add.
 *
 * @retval NRF_SUCCESS                    If the filter is added successfully.
 * @retval NRF_ERROR_NULL                 If a NULL pointer is passed as input.
 * @retval NRF_ERROR_DATA_SIZE            If the name filter length is too long. Maximum name filter length corresponds to @ref NRF_BLE_SCAN_NAME_MAX_LEN.
 * @retval NRF_ERROR_NO_MEMORY            If the number of available filters is exceeded.
 * @retval NRF_ERROR_INVALID_PARAM        If the filter type is incorrect. Available filter types: @ref nrf_ble_scan_filter_type_t.
 * @retval BLE_ERROR_GAP_INVALID_BLE_ADDR If the BLE address type is invalid.
 */
ret_code_t nrf_ble_scan_filter_set(nrf_ble_scan_t     * const p_scan_ctx,
                                   nrf_ble_scan_filter_type_t type,
                                   void const               * p_data);


/**@brief Function for removing all set filters.
 *
 * @details The function removes all previously set filters.
 *
 * @note After using this function the filters are still enabled.
 *
 * @param[in,out] p_scan_ctx Pointer to the Scanning Module instance.
 *
 * @retval NRF_SUCCESS       If all filters are removed successfully.
 */
ret_code_t nrf_ble_scan_all_filter_remove(nrf_ble_scan_t * const p_scan_ctx);


#endif // NRF_BLE_SCAN_FILTER_ENABLE


/**@brief Function for changing the scanning parameters.
 *
 **@details Use this function to change scanning parameters. During the parameter change
 *         the scan is stopped. To resume scanning, use @ref nrf_ble_scan_start.
 *         Scanning parameters can be set to NULL. If so, the default static configuration
 *         is used. For example, use this function when the @ref NRF_BLE_SCAN_EVT_WHITELIST_ADV_REPORT event is generated.
 *         The generation of this event means that there is a risk that the whitelist is empty. In such case, this function can change
 *         the scanning parameters, so that the whitelist is not used, and you avoid the error caused by scanning with the whitelist
 *         when there are no devices on the whitelist.
 *
 * @param[in,out] p_scan_ctx     Pointer to the Scanning Module instance.
 * @param[in]     p_scan_param   GAP scanning parameters. Can be initialized as NULL.
 *
 * @retval NRF_SUCCESS          If parameters are changed successfully.
 * @retval NRF_ERROR_NULL       If a NULL pointer is passed as input.
 */
ret_code_t nrf_ble_scan_params_set(nrf_ble_scan_t        * const p_scan_ctx,
                                   ble_gap_scan_params_t const * p_scan_param);


/**@brief Function for handling the BLE stack events of the application.
 *
 * @param[in]     p_ble_evt     Pointer to the BLE event received.
 * @param[in,out] p_scan        Pointer to the Scanning Module instance.
 */
void nrf_ble_scan_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_scan);


/**@brief Function for converting the raw address to the SoftDevice GAP address.
 *
 * @details This function inverts the byte order in the address. If you enter the address as it is displayed
 *          (for example, on a phone screen from left to right), you must use this function to
 *          convert the address to the SoftDevice address type.
 *
 * @param[in]  addr       Address to be converted to the SoftDevice address.
 * @param[out] p_gap_addr The Bluetooth Low Energy address.
 *
 * @retval BLE_ERROR_GAP_INVALID_BLE_ADDR If the BLE address type is invalid.
 * @retval NRF_SUCCESS                    If the address is copied and converted successfully.
 */
ret_code_t nrf_ble_scan_copy_addr_to_sd_gap_addr(ble_gap_addr_t * p_gap_addr,
                                                 uint8_t    const addr[BLE_GAP_ADDR_LEN]);

#ifdef __cplusplus
}
#endif

#endif // NRF_BLE_SCAN_H__

/** @} */
