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
/**@file
 *
 * @defgroup ble_hrs_c Heart Rate Service Client
 * @{
 * @ingroup  ble_sdk_srv
 * @brief    Heart Rate Service Client module.
 *
 * @details  This module contains the APIs and types exposed by the Heart Rate Service Client
 *           module. These APIs and types can be used by the application to perform discovery of
 *           Heart Rate Service at the peer and interact with it.
 *
 * @warning  Currently this module only has support for Heart Rate Measurement characteristic. This
 *           means that it will be able to enable notification of the characteristic at the peer and
 *           be able to receive Heart Rate Measurement notifications from the peer. It does not
 *           support the Body Sensor Location and the Heart Rate Control Point characteristics.
 *           When a Heart Rate Measurement is received, this module will decode only the
 *           Heart Rate Measurement Value (both 8 bit and 16 bit) field from it and provide it to
 *           the application.
 *
 * @note    The application must register this module as BLE event observer using the
 *          NRF_SDH_BLE_OBSERVER macro. Example:
 *          @code
 *              ble_hrs_c_t instance;
 *              NRF_SDH_BLE_OBSERVER(anything, BLE_HRS_C_BLE_OBSERVER_PRIO,
 *                                   ble_hrs_c_on_ble_evt, &instance);
 *          @endcode
 */

#ifndef BLE_HRS_C_H__
#define BLE_HRS_C_H__

#include <stdint.h>
#include "ble.h"
#include "ble_db_discovery.h"
#include "sdk_config.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_hrs_c instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_HRS_C_DEF(_name)                                                                        \
static ble_hrs_c_t _name;                                                                           \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HRS_C_BLE_OBSERVER_PRIO,                                                   \
                     ble_hrs_c_on_ble_evt, &_name)

/** @brief Macro for defining multiple ble_hrs_c instances.
 *
 * @param   _name   Name of the array of instances.
 * @param   _cnt    Number of instances to define.
 * @hideinitializer
 */
#define BLE_HRS_C_ARRAY_DEF(_name, _cnt)                 \
static ble_hrs_c_t _name[_cnt];                          \
NRF_SDH_BLE_OBSERVERS(_name ## _obs,                     \
                      BLE_HRS_C_BLE_OBSERVER_PRIO,       \
                      ble_hrs_c_on_ble_evt, &_name, _cnt)


/** @brief  Maximum number of RR intervals to be decoded for each HRM notifications (any extra RR intervals will be ignored).
 *
 * This define should be defined in the sdk_config.h file to override the default.
 */
#ifndef BLE_HRS_C_RR_INTERVALS_MAX_CNT
#define BLE_HRS_C_RR_INTERVALS_MAX_CNT 20
#endif


/**
 * @defgroup hrs_c_enums Enumerations
 * @{
 */

/**@brief HRS Client event type. */
typedef enum
{
    BLE_HRS_C_EVT_DISCOVERY_COMPLETE = 1,  /**< Event indicating that the Heart Rate Service has been discovered at the peer. */
    BLE_HRS_C_EVT_HRM_NOTIFICATION         /**< Event indicating that a notification of the Heart Rate Measurement characteristic has been received from the peer. */
} ble_hrs_c_evt_type_t;

/** @} */

/**
 * @defgroup hrs_c_structs Structures
 * @{
 */

/**@brief Structure containing the heart rate measurement received from the peer. */
typedef struct
{
    uint16_t hr_value;                                        /**< Heart Rate Value. */
    uint8_t  rr_intervals_cnt;                                /**< Number of RR intervals. */
    uint16_t rr_intervals[BLE_HRS_C_RR_INTERVALS_MAX_CNT];    /**< RR intervals. */
} ble_hrm_t;

/**@brief Structure containing the handles related to the Heart Rate Service found on the peer. */
typedef struct
{
    uint16_t hrm_cccd_handle;  /**< Handle of the CCCD of the Heart Rate Measurement characteristic. */
    uint16_t hrm_handle;       /**< Handle of the Heart Rate Measurement characteristic as provided by the SoftDevice. */
} hrs_db_t;

/**@brief Heart Rate Event structure. */
typedef struct
{
    ble_hrs_c_evt_type_t evt_type;    /**< Type of the event. */
    uint16_t             conn_handle; /**< Connection handle on which the Heart Rate service was discovered on the peer device..*/
    union
    {
        hrs_db_t  peer_db;            /**< Heart Rate related handles found on the peer device.. This will be filled if the evt_type is @ref BLE_HRS_C_EVT_DISCOVERY_COMPLETE.*/
        ble_hrm_t hrm;                /**< Heart rate measurement received. This will be filled if the evt_type is @ref BLE_HRS_C_EVT_HRM_NOTIFICATION. */
    } params;
} ble_hrs_c_evt_t;

/** @} */

/**
 * @defgroup hrs_c_types Types
 * @{
 */

// Forward declaration of the ble_bas_t type.
typedef struct ble_hrs_c_s ble_hrs_c_t;

/**@brief   Event handler type.
 *
 * @details This is the type of the event handler that should be provided by the application
 *          of this module in order to receive events.
 */
typedef void (* ble_hrs_c_evt_handler_t) (ble_hrs_c_t * p_ble_hrs_c, ble_hrs_c_evt_t * p_evt);

/** @} */

/**
 * @addtogroup hrs_c_structs
 * @{
 */

/**@brief Heart Rate Client structure.
 */
struct ble_hrs_c_s
{
    uint16_t                conn_handle;      /**< Connection handle as provided by the SoftDevice. */
    hrs_db_t                peer_hrs_db;      /**< Handles related to HRS on the peer*/
    ble_hrs_c_evt_handler_t evt_handler;      /**< Application event handler to be called when there is an event related to the heart rate service. */
};

/**@brief Heart Rate Client initialization structure.
 */
typedef struct
{
    ble_hrs_c_evt_handler_t evt_handler;  /**< Event handler to be called by the Heart Rate Client module whenever there is an event related to the Heart Rate Service. */
} ble_hrs_c_init_t;

/** @} */


/**
 * @defgroup hrs_c_functions Functions
 * @{
 */

/**@brief     Function for initializing the heart rate client module.
 *
 * @details   This function will register with the DB Discovery module. There it
 *            registers for the Heart Rate Service. Doing so will make the DB Discovery
 *            module look for the presence of a Heart Rate Service instance at the peer when a
 *            discovery is started.
 *
 * @param[in] p_ble_hrs_c      Pointer to the heart rate client structure.
 * @param[in] p_ble_hrs_c_init Pointer to the heart rate initialization structure containing the
 *                             initialization information.
 *
 * @retval    NRF_SUCCESS On successful initialization. Otherwise an error code. This function
 *                        propagates the error code returned by the Database Discovery module API
 *                        @ref ble_db_discovery_evt_register.
 */
uint32_t ble_hrs_c_init(ble_hrs_c_t * p_ble_hrs_c, ble_hrs_c_init_t * p_ble_hrs_c_init);


/**@brief     Function for handling BLE events from the SoftDevice.
 *
 * @details   This function will handle the BLE events received from the SoftDevice. If a BLE
 *            event is relevant to the Heart Rate Client module, then it uses it to update
 *            interval variables and, if necessary, send events to the application.
 *
 * @param[in] p_ble_evt     Pointer to the BLE event.
 * @param[in] p_context     Pointer to the heart rate client structure.
 */
void ble_hrs_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief   Function for requesting the peer to start sending notification of Heart Rate
 *          Measurement.
 *
 * @details This function will enable to notification of the Heart Rate Measurement at the peer
 *          by writing to the CCCD of the Heart Rate Measurement Characteristic.
 *
 * @param   p_ble_hrs_c Pointer to the heart rate client structure.
 *
 * @retval  NRF_SUCCESS If the SoftDevice has been requested to write to the CCCD of the peer.
 *                      Otherwise, an error code. This function propagates the error code returned
 *                      by the SoftDevice API @ref sd_ble_gattc_write.
 */
uint32_t ble_hrs_c_hrm_notif_enable(ble_hrs_c_t * p_ble_hrs_c);


/**@brief     Function for handling events from the database discovery module.
 *
 * @details   Call this function when getting a callback event from the DB discovery modue.
 *            This function will handle an event from the database discovery module, and determine
 *            if it relates to the discovery of heart rate service at the peer. If so, it will
 *            call the application's event handler indicating that the heart rate service has been
 *            discovered at the peer. It also populates the event with the service related
 *            information before providing it to the application.
 *
 * @param[in] p_ble_hrs_c Pointer to the heart rate client structure instance to associate.
 * @param[in] p_evt Pointer to the event received from the database discovery module.
 *
 */
void ble_hrs_on_db_disc_evt(ble_hrs_c_t * p_ble_hrs_c, const ble_db_discovery_evt_t * p_evt);


/**@brief     Function for assigning a handles to a this instance of hrs_c.
 *
 * @details   Call this function when a link has been established with a peer to
 *            associate this link to this instance of the module. This makes it
 *            possible to handle several link and associate each link to a particular
 *            instance of this module.The connection handle and attribute handles will be
 *            provided from the discovery event @ref BLE_HRS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in] p_ble_hrs_c        Pointer to the heart rate client structure instance to associate.
 * @param[in] conn_handle        Connection handle to associated with the given Heart Rate Client Instance.
 * @param[in] p_peer_hrs_handles Attribute handles for the HRS server you want this HRS_C client to
 *                               interact with.
 */
uint32_t ble_hrs_c_handles_assign(ble_hrs_c_t *    p_ble_hrs_c,
                                  uint16_t         conn_handle,
                                  const hrs_db_t * p_peer_hrs_handles);

/** @} */ // End tag for Function group.


#ifdef __cplusplus
}
#endif

#endif // BLE_HRS_C_H__

/** @} */ // End tag for the file.
