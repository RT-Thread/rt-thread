/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
/**@file
 *
 * @defgroup ble_advertising Advertising Module
 * @{
 * @ingroup  ble_sdk_lib
 * @brief    Module for handling connectable BLE advertising.
 *
 * @details  The Advertising Module handles connectable advertising for your application. It can
 *           be configured with advertising modes to suit most typical use cases.
 *           Your main application can react to changes in advertising modes
 *           if an event handler is provided.
 *
 * @note     The Advertising Module supports only applications with a single peripheral link.
 *
 */

#ifndef BLE_ADVERTISING_H__
#define BLE_ADVERTISING_H__

#include <stdint.h>
#include "nrf_error.h"
#include "ble.h"
#include "ble_gattc.h"
#include "ble_advdata.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_advertising instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_ADVERTISING_DEF(_name)                                                                  \
static ble_advertising_t _name;                                                                     \
NRF_SDH_BLE_OBSERVER(_name ## _ble_obs,                                                             \
                     BLE_ADV_BLE_OBSERVER_PRIO,                                                     \
                     ble_advertising_on_ble_evt, &_name);                                           \
NRF_SDH_SOC_OBSERVER(_name ## _soc_obs,                                                             \
                     BLE_ADV_SOC_OBSERVER_PRIO,                                                     \
                     ble_advertising_on_sys_evt, &_name)


/**@brief   Advertising modes. */
typedef enum
{
    BLE_ADV_MODE_IDLE,               /**< Idle; no connectable advertising is ongoing. */
    BLE_ADV_MODE_DIRECTED_HIGH_DUTY, /**< Directed advertising (high duty cycle) attempts to connect to the most recently disconnected peer. */
    BLE_ADV_MODE_DIRECTED,           /**< Directed advertising (low duty cycle) attempts to connect to the most recently disconnected peer. */
    BLE_ADV_MODE_FAST,               /**< Fast advertising will connect to any peer device, or filter with a whitelist if one exists. */
    BLE_ADV_MODE_SLOW,               /**< Slow advertising is similar to fast advertising. By default, it uses a longer advertising interval and time-out than fast advertising. However, these options are defined by the user. */
} ble_adv_mode_t;

/**@brief   Advertising events.
 *
 * @details These events are propagated to the main application if a handler was provided during
 *          initialization of the Advertising Module. Events for modes that are not used can be
 *          ignored. Similarly, BLE_ADV_EVT_WHITELIST_REQUEST and BLE_ADV_EVT_PEER_ADDR_REQUEST
 *          can be ignored if whitelist and direct advertising is not used.
 */
typedef enum
{
    BLE_ADV_EVT_IDLE,                /**< Idle; no connectable advertising is ongoing.*/
    BLE_ADV_EVT_DIRECTED_HIGH_DUTY,  /**< Direct advertising mode has started. */
    BLE_ADV_EVT_DIRECTED,            /**< Directed advertising (low duty cycle) has started. */
    BLE_ADV_EVT_FAST,                /**< Fast advertising mode has started. */
    BLE_ADV_EVT_SLOW,                /**< Slow advertising mode has started. */
    BLE_ADV_EVT_FAST_WHITELIST,      /**< Fast advertising mode using the whitelist has started. */
    BLE_ADV_EVT_SLOW_WHITELIST,      /**< Slow advertising mode using the whitelist has started. */
    BLE_ADV_EVT_WHITELIST_REQUEST,   /**< Request a whitelist from the main application. For whitelist advertising to work, the whitelist must be set when this event occurs. */
    BLE_ADV_EVT_PEER_ADDR_REQUEST    /**< Request a peer address from the main application. For directed advertising to work, the peer address must be set when this event occurs. */
} ble_adv_evt_t;

/**@brief   Options for the different advertisement modes.
 *
 * @details This structure is used to enable or disable advertising modes and to configure time-out
 *          periods and advertising intervals.
 */
typedef struct
{
    bool     ble_adv_on_disconnect_disabled;     /**< Enable or disable automatic return to advertising upon disconnecting.*/
    bool     ble_adv_whitelist_enabled;          /**< Enable or disable use of the whitelist. */
    bool     ble_adv_directed_high_duty_enabled; /**< Enable or disable direct advertising mode. can only be used if ble_adv_legacy_enabled is true. */
    bool     ble_adv_directed_enabled;           /**< Enable or disable direct advertising mode. */
    bool     ble_adv_fast_enabled;               /**< Enable or disable fast advertising mode. */
    bool     ble_adv_slow_enabled;               /**< Enable or disable slow advertising mode. */
    uint32_t ble_adv_directed_interval;          /**< Advertising interval for directed advertising. */
    uint32_t ble_adv_directed_timeout;           /**< Time-out (number of tries) for direct advertising. */
    uint32_t ble_adv_fast_interval;              /**< Advertising interval for fast advertising. */
    uint32_t ble_adv_fast_timeout;               /**< Time-out (in seconds) for fast advertising. */
    uint32_t ble_adv_slow_interval;              /**< Advertising interval for slow advertising. */
    uint32_t ble_adv_slow_timeout;               /**< Time-out (in seconds) for slow advertising. */
    bool     ble_adv_extended_enabled;           /**< Enable or disable extended advertising. */
    uint32_t ble_adv_secondary_phy;              /**< PHY for the secondary (extended) advertising @ref BLE_GAP_PHYS (BLE_GAP_PHY_1MBPS, BLE_GAP_PHY_2MBPS or BLE_GAP_PHY_CODED). */
    uint32_t ble_adv_primary_phy;                /**< PHY for the primary advertising. @ref BLE_GAP_PHYS (BLE_GAP_PHY_1MBPS, BLE_GAP_PHY_2MBPS or BLE_GAP_PHY_CODED). */
} ble_adv_modes_config_t;

/**@brief   BLE advertising event handler type. */
typedef void (*ble_adv_evt_handler_t) (ble_adv_evt_t const adv_evt);

/**@brief   BLE advertising error handler type. */
typedef void (*ble_adv_error_handler_t) (uint32_t nrf_error);

typedef struct
{
    bool                    initialized;
    bool                    advertising_start_pending;                        /**< Flag to keep track of ongoing operations in flash. */
    ble_adv_mode_t          adv_mode_current;                                 /**< Variable to keep track of the current advertising mode. */
    ble_adv_modes_config_t  adv_modes_config;                                 /**< Struct to keep track of disabled and enabled advertising modes, as well as time-outs and intervals.*/
    uint8_t                 conn_cfg_tag;                                     /**< Variable to keep track of what connection settings will be used if the advertising results in a connection. */

    ble_adv_evt_t           adv_evt;                                          /**< Advertising event propogated to the main application. The event is either a transaction to a new advertising mode, or a request for whitelist or peer address. */
    ble_adv_evt_handler_t   evt_handler;                                      /**< Handler for the advertising events. Can be initialized as NULL if no handling is implemented on in the main application. */
    ble_adv_error_handler_t error_handler;                                    /**< Handler for the advertising error events. */

    ble_gap_adv_params_t    adv_params;                                       /**< GAP advertising parameters. */
    uint8_t                 adv_handle;                                       /**< Handle for the advertising set. */
    uint8_t                 enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];       /**< Current advertising data in encoded form. */
    uint8_t                 enc_scan_rsp_data[BLE_GAP_ADV_SET_DATA_SIZE_MAX]; /**< Current scan response data in encoded form. */
    ble_gap_adv_data_t      adv_data;                                         /**< Advertising data. */
    ble_gap_adv_data_t     *p_adv_data;                                       /**< Will be set to point to @ref ble_advertising_t::adv_data for undirected advertising, and will be set to NULL for directed advertising. */

    uint16_t                current_slave_link_conn_handle;                   /**< Connection handle for the active link. */
    ble_gap_addr_t          peer_address;                                     /**< Address of the most recently connected peer, used for direct advertising. */
    bool                    peer_addr_reply_expected;                         /**< Flag to verify that peer address is only set when requested. */
    bool                    whitelist_temporarily_disabled;                   /**< Flag to keep track of temporary disabling of the whitelist. */
    bool                    whitelist_reply_expected;                         /**< Flag to verify that the whitelist is only set when requested. */
    bool                    whitelist_in_use;                                 /**< This module needs to be aware of whether or not a whitelist has been set (e.g. using the Peer Manager) in order to start advertising with the proper advertising params (filter policy). */
} ble_advertising_t;

typedef struct
{
    uint32_t interval;
    uint32_t timeout;
    bool     enabled;
} ble_adv_mode_config_t;

/**@brief     Initialization parameters for the Advertising Module.
 * @details This structure is used to pass advertising options, advertising data,
 *          and an event handler to the Advertising Module during initialization.
 */
typedef struct
{
    ble_advdata_t           advdata;       /**< Advertising data: name, appearance, discovery flags, and more. */
    ble_advdata_t           srdata;        /**< Scan response data: Supplement to advertising data. */
    ble_adv_modes_config_t  config;        /**< Select which advertising modes and intervals will be utilized.*/
    ble_adv_evt_handler_t   evt_handler;   /**< Event handler that will be called upon advertising events. */
    ble_adv_error_handler_t error_handler; /**< Error handler that will propogate internal errors to the main applications. */
} ble_advertising_init_t;


/**@brief   Function for handling BLE events.
 *
 * @details This function must be called from the BLE stack event dispatcher for
 *          the module to handle BLE events that are relevant for the Advertising Module.
 *
 * @param[in] p_ble_evt     BLE stack event.
 * @param[in] p_adv         Advertising module instance.
 */
void ble_advertising_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_adv);


/**@brief   Function for handling system events.
 *
 * @details This function must be called to handle system events that are relevant
 *          for the Advertising Module. Specifically, the advertising module can not use the
 *          softdevice as long as there are pending writes to the flash memory. This
 *          event handler is designed to delay advertising until there is no flash operation.
 *
 * @param[in] sys_evt       System event.
 * @param[in] p_adv         Advertising module instance.
 */
void ble_advertising_on_sys_evt(uint32_t sys_evt, void * p_adv);


/**@brief   Function for initializing the Advertising Module.
 *
 * @details Encodes the required advertising data and passes it to the stack.
 *          Also builds a structure to be passed to the stack when starting advertising.
 *          The supplied advertising data is copied to a local structure and is manipulated
 *          depending on what advertising modes are started in @ref ble_advertising_start.
 *
 * @param[out] p_advertising Advertising module instance. This structure must be supplied by
 *                           the application. It is initialized by this function and will later
 *                           be used to identify this particular module instance.
 * @param[in] p_init         Information needed to initialize the module.
 *
 * @retval NRF_SUCCESS             If initialization was successful.
 * @retval NRF_ERROR_INVALID_PARAM If the advertising configuration in \p p_init is invalid.
 * @return If functions from other modules return errors to this function, the @ref nrf_error are propagated.
 */
uint32_t ble_advertising_init(ble_advertising_t            * const p_advertising,
                              ble_advertising_init_t const * const p_init);


 /**@brief  Function for changing the connection settings tag that will be used for upcoming connections.
 *
 * @details See @ref sd_ble_cfg_set for more details about changing connection settings. If this
 *          function is never called, @ref BLE_CONN_CFG_TAG_DEFAULT will be used.
 *
 * @param[in] p_advertising Advertising module instance.
 * @param[in] ble_cfg_tag Configuration for the connection settings (see @ref sd_ble_cfg_set).
 */
void ble_advertising_conn_cfg_tag_set(ble_advertising_t * const p_advertising, uint8_t ble_cfg_tag);

/**@brief   Function for starting advertising.
 *
 * @details You can start advertising in any of the advertising modes that you enabled
 *          during initialization.
 *
 * @param[in] p_advertising    Advertising module instance.
 * @param[in] advertising_mode Advertising mode.
 *
 * @retval @ref NRF_SUCCESS On success, else an error code indicating reason for failure.
 * @retval @ref NRF_ERROR_INVALID_STATE If the module is not initialized.
 */
uint32_t ble_advertising_start(ble_advertising_t * const p_advertising,
                               ble_adv_mode_t            advertising_mode);


/**@brief   Function for setting the peer address.
 *
 * @details The peer address must be set by the application upon receiving a
 *          @ref BLE_ADV_EVT_PEER_ADDR_REQUEST event. Without the peer address, the directed
 *          advertising mode will not be run.
 *
 * @param[in] p_advertising Advertising module instance.
 * @param[in] p_peer_addr  Pointer to a peer address.
 *
 * @retval @ref NRF_SUCCESS Successfully stored the peer address pointer in the advertising module.
 * @retval @ref NRF_ERROR_INVALID_STATE If a reply was not expected.
 */
uint32_t ble_advertising_peer_addr_reply(ble_advertising_t * const p_advertising,
                                         ble_gap_addr_t          * p_peer_addr);


/**@brief   Function for setting a whitelist.
 *
 * @details The whitelist must be set by the application upon receiving a
 *          @ref BLE_ADV_EVT_WHITELIST_REQUEST event. Without the whitelist, the whitelist
 *          advertising for fast and slow modes will not be run.
 *
 * @param[in] p_advertising Advertising module instance.
 * @param[in] p_gap_addrs   The list of GAP addresses to whitelist.
 * @param[in] addr_cnt      The number of GAP addresses to whitelist.
 * @param[in] p_gap_irks    The list of peer IRK to whitelist.
 * @param[in] irk_cnt       The number of peer IRK to whitelist.
 *
 * @retval @ref NRF_SUCCESS                 If the operation was successful.
 * @retval @ref NRF_ERROR_INVALID_STATE     If a call to this function was made without a
 *                                          BLE_ADV_EVT_WHITELIST_REQUEST event being received.
 */
uint32_t ble_advertising_whitelist_reply(ble_advertising_t * const p_advertising,
                                         ble_gap_addr_t const    * p_gap_addrs,
                                         uint32_t               addr_cnt,
                                         ble_gap_irk_t  const * p_gap_irks,
                                         uint32_t               irk_cnt);


/**@brief   Function for disabling whitelist advertising.
 *
 * @details This function temporarily disables whitelist advertising.
 *          Calling this function resets the current time-out countdown.
 *
 * @param[in]  p_advertising Advertising module instance.
 *
 * @retval @ref NRF_SUCCESS On success, else an error message propogated from the Softdevice.
 */
uint32_t ble_advertising_restart_without_whitelist(ble_advertising_t * const p_advertising);


/**@brief   Function for changing advertising modes configuration.
 *
 * @details This function can be called if you wish to reconfigure the advertising modes that the
 *          advertising module will cycle through. Enable or disable modes as listed in
 *          @ref ble_adv_mode_t; or change the duration of the advertising and use of whitelist.
 *
 *          Keep in mind that @ref ble_adv_modes_config_t is also supplied when calling
 *          @ref ble_advertising_init. Calling @ref ble_advertising_modes_config_set
 *          is only necessary if your application requires this behaviour to change.
 *
 * @param[in]  p_advertising      Advertising module instance.
 * @param[in]  p_adv_modes_config Struct to keep track of disabled and enabled advertising modes,
 *                                as well as time-outs and intervals.
 */
void ble_advertising_modes_config_set(ble_advertising_t            * const p_advertising,
                                      ble_adv_modes_config_t const * const p_adv_modes_config);
/** @} */


#ifdef __cplusplus
}
#endif

#endif // BLE_ADVERTISING_H__

/** @} */
