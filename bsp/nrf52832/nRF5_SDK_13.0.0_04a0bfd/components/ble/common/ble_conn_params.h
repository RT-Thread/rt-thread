/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
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
 * @defgroup ble_sdk_lib_conn_params Connection Parameters Negotiation
 * @{
 * @ingroup ble_sdk_lib
 * @brief Module for initiating and executing a connection parameters negotiation procedure.
 */

#ifndef BLE_CONN_PARAMS_H__
#define BLE_CONN_PARAMS_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Connection Parameters Module event type. */
typedef enum
{
    BLE_CONN_PARAMS_EVT_FAILED   ,                                  /**< Negotiation procedure failed. */
    BLE_CONN_PARAMS_EVT_SUCCEEDED                                   /**< Negotiation procedure succeeded. */
} ble_conn_params_evt_type_t;

/**@brief Connection Parameters Module event. */
typedef struct
{
    ble_conn_params_evt_type_t evt_type;                            /**< Type of event. */
} ble_conn_params_evt_t;

/**@brief Connection Parameters Module event handler type. */
typedef void (*ble_conn_params_evt_handler_t) (ble_conn_params_evt_t * p_evt);

/**@brief Connection Parameters Module init structure. This contains all options and data needed for
 *        initialization of the connection parameters negotiation module. */
typedef struct
{
    ble_gap_conn_params_t *       p_conn_params;                    /**< Pointer to the connection parameters desired by the application. When calling ble_conn_params_init, if this parameter is set to NULL, the connection parameters will be fetched from host. */
    uint32_t                      first_conn_params_update_delay;   /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (in number of timer ticks). */
    uint32_t                      next_conn_params_update_delay;    /**< Time between each call to sd_ble_gap_conn_param_update after the first (in number of timer ticks). Recommended value 30 seconds as per BLUETOOTH SPECIFICATION Version 4.0. */
    uint8_t                       max_conn_params_update_count;     /**< Number of attempts before giving up the negotiation. */
    uint16_t                      start_on_notify_cccd_handle;      /**< If procedure is to be started when notification is started, set this to the handle of the corresponding CCCD. Set to BLE_GATT_HANDLE_INVALID if procedure is to be started on connect event. */
    bool                          disconnect_on_fail;               /**< Set to TRUE if a failed connection parameters update shall cause an automatic disconnection, set to FALSE otherwise. */
    ble_conn_params_evt_handler_t evt_handler;                      /**< Event handler to be called for handling events in the Connection Parameters. */
    ble_srv_error_handler_t       error_handler;                    /**< Function to be called in case of an error. */
} ble_conn_params_init_t;


/**@brief Function for initializing the Connection Parameters module.
 *
 * @note If the negotiation procedure should be triggered when notification/indication of
 *       any characteristic is enabled by the peer, then this function must be called after
 *       having initialized the services.
 *
 * @param[in]   p_init  This contains information needed to initialize this module.
 *
 * @return      NRF_SUCCESS on successful initialization, otherwise an error code.
 */
uint32_t ble_conn_params_init(const ble_conn_params_init_t * p_init);

/**@brief Function for stopping the Connection Parameters module.
 *
 * @details This function is intended to be used by the application to clean up the connection
 *          parameters update module. This will stop the connection parameters update timer if
 *          running, thereby preventing any impending connection parameters update procedure. This
 *          function must be called by the application when it needs to clean itself up (for
 *          example, before disabling the bluetooth SoftDevice) so that an unwanted timer expiry
 *          event can be avoided.
 *
 * @return      NRF_SUCCESS on successful initialization, otherwise an error code.
 */
uint32_t ble_conn_params_stop(void);

/**@brief Function for changing the current connection parameters to a new set.
 *
 *  @details Use this function to change the connection parameters to a new set of parameter
 *       (ie different from the ones given at init of the module).
 *       This function is useful for scenario where most of the time the application
 *       needs a relatively big connection interval, and just sometimes, for a temporary
 *       period requires shorter connection interval, for example to transfer a higher
 *       amount of data.
 *       If the given parameters does not match the current connection's parameters
 *       this function initiates a new negotiation.
 *
 * @param[in]   new_params  This contains the new connections parameters to setup.
 *
 * @return      NRF_SUCCESS on successful initialization, otherwise an error code.
 */
uint32_t ble_conn_params_change_conn_params(ble_gap_conn_params_t *new_params);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack that are of interest to this module.
 *
 * @param[in]   p_ble_evt  The event received from the BLE stack.
 */
void ble_conn_params_on_ble_evt(ble_evt_t * p_ble_evt);


#ifdef __cplusplus
}
#endif

#endif // BLE_CONN_PARAMS_H__

/** @} */
