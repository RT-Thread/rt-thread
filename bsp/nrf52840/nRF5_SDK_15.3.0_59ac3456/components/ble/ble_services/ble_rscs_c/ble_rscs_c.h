/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
/**
 * @defgroup ble_rscs_c Running Speed and Cadence Service Client
 * @{
 * @ingroup ble_sdk_srv
 *
 * @details  This module contains the APIs and types exposed by the Running Speed and Cadence
 *           Service Client module. These APIs and types can be used by the application to perform
 *           discovery of Running Speed and Cadence Service at the peer and interact with it.
 *
 * @note    The application must register this module as BLE event observer using the
 *          NRF_SDH_BLE_OBSERVER macro. Example:
 *          @code
 *              ble_rscs_c_t instance;
 *              NRF_SDH_BLE_OBSERVER(anything, BLE_RSCS_C_BLE_OBSERVER_PRIO,
 *                                   ble_rscs_c_on_ble_evt, &instance);
 *          @endcode
 */
#ifndef BLE_RSCS_C_H__
#define BLE_RSCS_C_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_db_discovery.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_rscs_c instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_RSCS_C_DEF(_name)                                                                       \
static ble_rscs_c_t _name;                                                                          \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_RSCS_C_BLE_OBSERVER_PRIO,                                                  \
                     ble_rscs_c_on_ble_evt, &_name)

/** @brief Macro for defining multiple ble_rscs_c instances.
 *
 * @param   _name   Name of the array of instances.
 * @param   _cnt    Number of instances to define.
 * @hideinitializer
 */
#define BLE_RSCS_C_ARRAY_DEF(_name, _cnt)                 \
static ble_rscs_c_t _name[_cnt];                          \
NRF_SDH_BLE_OBSERVERS(_name ## _obs,                      \
                      BLE_RSCS_C_BLE_OBSERVER_PRIO,       \
                      ble_rscs_c_on_ble_evt, &_name, _cnt)

#define BLE_RSCS_INSTANT_STRIDE_LEN_PRESENT     0x00  /**< Instantaneous Stride Length Measurement Supported bit. */
#define BLE_RSCS_TOTAL_DISTANCE_PRESENT         0x01  /**< Total Distance Measurement Supported bit. */
#define BLE_RSCS_WALKING_OR_RUNNING_STATUS_BIT  0x02  /**< Walking or Running Status Supported bit. */


/**@brief   Structure containing the handles related to the Running Speed and Cadence Service found on the peer. */
typedef struct
{
    uint16_t rsc_cccd_handle;                /**< Handle of the CCCD of the Running Speed and Cadence characteristic. */
    uint16_t rsc_handle;                     /**< Handle of the Running Speed and Cadence characteristic as provided by the SoftDevice. */
} ble_rscs_c_db_t;

/**@brief   RSCS Client event type. */
typedef enum
{
    BLE_RSCS_C_EVT_DISCOVERY_COMPLETE = 1,  /**< Event indicating that the Running Speed and Cadence Service has been discovered at the peer. */
    BLE_RSCS_C_EVT_RSC_NOTIFICATION         /**< Event indicating that a notification of the Running Speed and Cadence measurement characteristic has been received from the peer. */
} ble_rscs_c_evt_type_t;

/**@brief   Structure containing the Running Speed and Cadence measurement received from the peer. */
typedef struct
{
    bool     is_inst_stride_len_present;             /**< True if Instantaneous Stride Length is present in the measurement. */
    bool     is_total_distance_present;              /**< True if Total Distance is present in the measurement. */
    bool     is_running;                             /**< True if running, False if walking. */
    uint16_t inst_speed;                             /**< Instantaneous Speed. */
    uint8_t  inst_cadence;                           /**< Instantaneous Cadence. */
    uint16_t inst_stride_length;                     /**< Instantaneous Stride Length. */
    uint32_t total_distance;                         /**< Total Distance. */
} ble_rsc_t;

/**@brief   Running Speed and Cadence Event structure. */
typedef struct
{
    ble_rscs_c_evt_type_t evt_type;  /**< Type of the event. */
    uint16_t  conn_handle;           /**< Connection handle on which the rscs_c event  occured.*/
    union
    {
        ble_rscs_c_db_t rscs_db;           /**< Running Speed and Cadence Service related handles found on the peer device. This will be filled if the evt_type is @ref BLE_RSCS_C_EVT_DISCOVERY_COMPLETE.*/
        ble_rsc_t       rsc;               /**< Running Speed and Cadence measurement received. This will be filled if the evt_type is @ref BLE_RSCS_C_EVT_RSC_NOTIFICATION. */
    } params;
} ble_rscs_c_evt_t;

// Forward declaration of the ble_rscs_c_t type.
typedef struct ble_rscs_c_s ble_rscs_c_t;

/**@brief   Event handler type.
 *
 * @details This is the type of the event handler that should be provided by the application
 *          of this module in order to receive events.
 */
typedef void (* ble_rscs_c_evt_handler_t) (ble_rscs_c_t * p_ble_rscs_c, ble_rscs_c_evt_t * p_evt);

/**@brief   Running Speed and Cadence client structure. */
struct ble_rscs_c_s
{
    uint16_t                 conn_handle;      /**< Connection handle as provided by the SoftDevice. */
    ble_rscs_c_db_t          peer_db;          /**< Handles related to RSCS on the peer*/
    ble_rscs_c_evt_handler_t evt_handler;      /**< Application event handler to be called when there is an event related to the Running Speed and Cadence service. */
};

/**@brief   Running Speed and Cadence client initialization structure. */
typedef struct
{
    ble_rscs_c_evt_handler_t evt_handler;  /**< Event handler to be called by the Running Speed and Cadence Client module whenever there is an event related to the Running Speed and Cadence Service. */
} ble_rscs_c_init_t;


/**@brief      Function for initializing the Running Speed and Cadence Service Client module.
 *
 * @details    This function will initialize the module and set up Database Discovery to discover
 *             the Running Speed and Cadence Service. After calling this function, call @ref ble_db_discovery_start
 *             to start discovery once a link with a peer has been established.
 *
 * @param[out] p_ble_rscs_c      Pointer to the RSC Service client structure.
 * @param[in]  p_ble_rscs_c_init Pointer to the RSC Service initialization structure containing
 *                               the initialization information.
 *
 * @retval     NRF_SUCCESS      Operation success.
 * @retval     NRF_ERROR_NULL   A parameter is NULL.
 *                              Otherwise, an error code returned by @ref ble_db_discovery_evt_register.
 */
uint32_t ble_rscs_c_init(ble_rscs_c_t * p_ble_rscs_c, ble_rscs_c_init_t * p_ble_rscs_c_init);


/**@brief   Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Running Speed and Cadence
 *          Service client.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Running Speed and Cadence Service client structure.
 */
void ble_rscs_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


uint32_t ble_rscs_c_rsc_notif_enable(ble_rscs_c_t * p_ble_rscs_c);


/**@brief   Function for handling events from the database discovery module.
 *
 * @details Call this function when getting a callback event from the DB discovery modue.
 *          This function will handle an event from the database discovery module, and determine
 *          if it relates to the discovery of Running Speed and Cadence service at the peer.
 *          If so, it will call the application's event handler indicating that the RSC service has
 *          been discovered at the peer. It also populates the event with the service related
 *          information before providing it to the application.
 *
 * @param     p_ble_rscs_c Pointer to the Runnind Speed and Cadence Service client structure.
 * @param[in] p_evt Pointer to the event received from the database discovery module.
 */
void ble_rscs_on_db_disc_evt(ble_rscs_c_t * p_ble_rscs_c, ble_db_discovery_evt_t const * p_evt);


/**@brief   Function for assigning handles to a this instance of rscs_c.
 *
 * @details Call this function when a link has been established with a peer to
 *          associate this link to this instance of the module. This makes it
 *          possible to handle several link and associate each link to a particular
 *          instance of this module. The connection handle and attribute handles will be
 *          provided from the discovery event @ref BLE_RSCS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in]   p_ble_rscs_c    Pointer to the RSC client structure instance to associate.
 * @param[in]   conn_handle     Connection handle to associated with the given RSCS Client Instance.
 * @param[in]   p_peer_handles  Attribute handles on the RSCS server that you want this RSCS client
 *                              to interact with.
 */
uint32_t ble_rscs_c_handles_assign(ble_rscs_c_t    * p_ble_rscs_c,
                                   uint16_t          conn_handle,
                                   ble_rscs_c_db_t * p_peer_handles);


#ifdef __cplusplus
}
#endif

#endif // BLE_RSCS_C_H__

/** @} */ // End tag for the file.
