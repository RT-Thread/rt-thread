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
/**@file
 *
 * @defgroup ble_bas_c Battery Service Client
 * @{
 * @ingroup  ble_sdk_srv
 * @brief    Battery Service Client module.
 *
 * @details  This module contains APIs to read and interact with the Battery Service of a remote
 *           device.
 *
 * @note     The application must propagate BLE stack events to this module by calling
 *           ble_hrs_c_on_ble_evt().
 *
 */

#ifndef BLE_BAS_C_H__
#define BLE_BAS_C_H__

#include <stdint.h>
#include "ble.h"
#include "ble_db_discovery.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup bas_c_enums Enumerations
 * @{
 */

/**@brief Battery Service Client event type. */
typedef enum
{
    BLE_BAS_C_EVT_DISCOVERY_COMPLETE,  /**< Event indicating that the Battery Service has been discovered at the peer. */
    BLE_BAS_C_EVT_BATT_NOTIFICATION,   /**< Event indicating that a notification of the Battery Level characteristic has been received from the peer. */
    BLE_BAS_C_EVT_BATT_READ_RESP       /**< Event indicating that a read response on Battery Level characteristic has been received from peer. */
} ble_bas_c_evt_type_t;

/** @} */

/**
 * @defgroup bas_c_structs Structures
 * @{
 */


/**@brief Structure containing the handles related to the Battery Service found on the peer. */
typedef struct
{
    uint16_t                bl_cccd_handle;  /**< Handle of the CCCD of the Battery Level characteristic. */
    uint16_t                bl_handle;       /**< Handle of the Battery Level characteristic as provided by the SoftDevice. */
} ble_bas_c_db_t;

/**@brief Battery Service Client Event structure. */
typedef struct
{
    ble_bas_c_evt_type_t evt_type;  /**< Event Type. */
    uint16_t conn_handle;           /**< Connection handle relevent to this event.*/
    union
    {
        ble_bas_c_db_t bas_db;         /**< Battery Service related handles found on the peer device. This will be filled if the evt_type is @ref BLE_BAS_C_EVT_DISCOVERY_COMPLETE.*/
        uint8_t        battery_level;  /**< Battery level received from peer. This field will be used for the events @ref BLE_BAS_C_EVT_BATT_NOTIFICATION and @ref BLE_BAS_C_EVT_BATT_READ_RESP.*/
    } params;
} ble_bas_c_evt_t;

/** @} */

/**
 * @defgroup bas_c_types Types
 * @{
 */

// Forward declaration of the ble_bas_t type.
typedef struct ble_bas_c_s ble_bas_c_t;

/**@brief   Event handler type.
 *
 * @details This is the type of the event handler that should be provided by the application
 *          of this module in order to receive events.
 */
typedef void (* ble_bas_c_evt_handler_t) (ble_bas_c_t * p_bas_bas_c, ble_bas_c_evt_t * p_evt);

/** @} */

/**
 * @addtogroup bas_c_structs
 * @{
 */

/**@brief      Battery Service Client structure.

 */
struct ble_bas_c_s
{
    uint16_t                conn_handle;     /**< Connection handle as provided by the SoftDevice. */
    ble_bas_c_db_t          peer_bas_db;     /**< Handles related to BAS on the peer*/
    ble_bas_c_evt_handler_t evt_handler;     /**< Application event handler to be called when there is an event related to the Battery service. */
};

/**@brief   Battery Service Client initialization structure.
 */
typedef struct
{
    ble_bas_c_evt_handler_t evt_handler;  /**< Event handler to be called by the Battery Service Client module whenever there is an event related to the Battery Service. */
} ble_bas_c_init_t;

/** @} */

/**
 * @defgroup bas_c_functions Functions
 * @{
 */

/**@brief      Function for initializing the Battery Service Client module.
 *
 * @details    This function will initialize the module and set up Database Discovery to discover
 *             the Battery Service. After calling this function, call @ref ble_db_discovery_start
 *             to start discovery once a link with a peer has been established.
 *
 * @param[out] p_ble_bas_c      Pointer to the Battery Service client structure.
 * @param[in]  p_ble_bas_c_init Pointer to the Battery Service initialization structure containing
 *                              the initialization information.
 *
 * @retval     NRF_SUCCESS      Operation success.
 * @retval     NRF_ERROR_NULL   A parameter is NULL.
 *                              Otherwise, an error code returned by @ref ble_db_discovery_evt_register.
 */
uint32_t ble_bas_c_init(ble_bas_c_t * p_ble_bas_c, ble_bas_c_init_t * p_ble_bas_c_init);


/**@brief     Function for handling BLE events from the SoftDevice.
 *
 * @details   This function will handle the BLE events received from the SoftDevice. If the BLE
 *            event is relevant for the Battery Service Client module, then it is used to update
 *            interval variables and, if necessary, send events to the application.
 *
 * @note      This function must be called by the application.
 *
 * @param[in] p_ble_bas_c Pointer to the Battery Service client structure.
 * @param[in] p_ble_evt   Pointer to the BLE event.
 */
void ble_bas_c_on_ble_evt(ble_bas_c_t * p_ble_bas_c, const ble_evt_t * p_ble_evt);


/**@brief   Function for enabling notifications on the Battery Level characteristic.
 *
 * @details This function will enable to notification of the Battery Level characteristic at the
 *          peer by writing to the CCCD of the Battery Level Characteristic.
 *
 * @param   p_ble_bas_c Pointer to the Battery Service client structure.
 *
 * @retval  NRF_SUCCESS     If the SoftDevice has been requested to write to the CCCD of the peer.
 *          NRF_ERROR_NULL  Parameter is NULL.
 *                          Otherwise, an error code returned by the SoftDevice API @ref
 *                          sd_ble_gattc_write.
 */
uint32_t ble_bas_c_bl_notif_enable(ble_bas_c_t * p_ble_bas_c);


/**@brief   Function for reading the Battery Level characteristic.
 *
 * @param   p_ble_bas_c Pointer to the Battery Service client structure.
 *
 * @retval  NRF_SUCCESS If the read request was successfully queued to be sent to peer.
 */
uint32_t ble_bas_c_bl_read(ble_bas_c_t * p_ble_bas_c);


/**@brief     Function for handling events from the database discovery module.
 *
 * @details   Call this function when getting a callback event from the DB discovery modue.
 *            This function will handle an event from the database discovery module, and determine
 *            if it relates to the discovery of Battery service at the peer. If so, it will
 *            call the application's event handler indicating that the Battery service has been
 *            discovered at the peer. It also populates the event with the service related
 *            information before providing it to the application.
 *
 * @param     p_ble_bas_c Pointer to the Battery Service client structure.
 * @param[in] p_evt Pointer to the event received from the database discovery module.
 *
 */
void ble_bas_on_db_disc_evt(ble_bas_c_t * p_ble_bas_c, const ble_db_discovery_evt_t * p_evt);


/**@brief     Function for assigning handles to a this instance of bas_c.
 *
 * @details   Call this function when a link has been established with a peer to
 *            associate this link to this instance of the module. This makes it
 *            possible to handle several link and associate each link to a particular
 *            instance of this module. The connection handle and attribute handles will be
 *            provided from the discovery event @ref BLE_BAS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in] p_ble_bas_c    Pointer to the Battery client structure instance to associate.
 * @param[in] conn_handle    Connection handle to associated with the given Battery Client Instance.
 * @param[in] p_peer_handles Attribute handles on the BAS server you want this BAS client to
 *                           interact with.
 */
uint32_t ble_bas_c_handles_assign(ble_bas_c_t *    p_ble_bas_c,
                                  uint16_t         conn_handle,
                                  ble_bas_c_db_t * p_peer_handles);

/** @} */ // End tag for Function group.


#ifdef __cplusplus
}
#endif

#endif // BLE_BAS_C_H__

/** @} */ // End tag for the file.
