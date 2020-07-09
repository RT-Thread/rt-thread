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
 * @defgroup ble_rscs Running Speed and Cadence Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Running Speed and Cadence Service module.
 *
 * @details This module implements the Running Speed and Cadence Service. If enabled, notification
 *          of the Running Speead and Candence Measurement is performed when the application
 *          calls ble_rscs_measurement_send().
 *
 *          If an event handler is supplied by the application, the Running Speed and Cadence
 *          Service will generate Running Speed and Cadence Service events to the application.
 *
 * @note The application must propagate BLE stack events to the Running Speead and Candence Service
 *       module by calling ble_rscs_on_ble_evt() from the @ref softdevice_handler function.
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_RSCS_H__
#define BLE_RSCS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble_srv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Running Speed and Cadence Service feature bits. */
#define BLE_RSCS_FEATURE_INSTANT_STRIDE_LEN_BIT             (0x01 << 0)     /**< Instantaneous Stride Length Measurement Supported bit. */
#define BLE_RSCS_FEATURE_TOTAL_DISTANCE_BIT                 (0x01 << 1)     /**< Total Distance Measurement Supported bit. */
#define BLE_RSCS_FEATURE_WALKING_OR_RUNNING_STATUS_BIT      (0x01 << 2)     /**< Walking or Running Status Supported bit. */
#define BLE_RSCS_FEATURE_CALIBRATION_PROCEDURE_BIT          (0x01 << 3)     /**< Calibration Procedure Supported bit. */
#define BLE_RSCS_FEATURE_MULTIPLE_SENSORS_BIT               (0x01 << 4)     /**< Multiple Sensor Locations Supported bit. */

/**@brief Running Speed and Cadence Service event type. */
typedef enum
{
    BLE_RSCS_EVT_NOTIFICATION_ENABLED,                                      /**< Running Speed and Cadence value notification enabled event. */
    BLE_RSCS_EVT_NOTIFICATION_DISABLED                                      /**< Running Speed and Cadence value notification disabled event. */
} ble_rscs_evt_type_t;

/**@brief Running Speed and Cadence Service event. */
typedef struct
{
    ble_rscs_evt_type_t evt_type;                                           /**< Type of event. */
} ble_rscs_evt_t;

// Forward declaration of the ble_rsc types.
typedef struct ble_rscs_s      ble_rscs_t;
typedef struct ble_rscs_meas_s ble_rscs_meas_t;

/**@brief Running Speed and Cadence Service event handler type. */
typedef void (*ble_rscs_evt_handler_t) (ble_rscs_t * p_rscs, ble_rscs_evt_t * p_evt);

/**@brief Running Speed and Cadence Service measurement structure. This contains a Running Speed and
 *        Cadence measurement. */
struct ble_rscs_meas_s
{
    bool        is_inst_stride_len_present;                                 /**< True if Instantaneous Stride Length is present in the measurement. */
    bool        is_total_distance_present;                                  /**< True if Total Distance is present in the measurement. */
    bool        is_running;                                                 /**< True if running, False if walking. */
    uint16_t    inst_speed;                                                 /**< Instantaneous Speed. */
    uint8_t     inst_cadence;                                               /**< Instantaneous Cadence. */
    uint16_t    inst_stride_length;                                         /**< Instantaneous Stride Length. */
    uint32_t    total_distance;                                             /**< Total Distance. */
};

/**@brief Running Speed and Cadence Service init structure. This contains all options and data
 *        needed for initialization of the service. */
typedef struct
{
    ble_rscs_evt_handler_t       evt_handler;                               /**< Event handler to be called for handling events in the Running Speed and Cadence Service. */
    ble_srv_cccd_security_mode_t rsc_meas_attr_md;                          /**< Initial security level for running speed and cadence measurement attribute */
    ble_srv_security_mode_t      rsc_feature_attr_md;                       /**< Initial security level for feature attribute */
    uint16_t                     feature;                                   /**< Initial value for features of sensor. */
    ble_rscs_meas_t              initial_rcm;                               /**< Initial Running Speed Cadence Measurement.*/
} ble_rscs_init_t;

/**@brief Running Speed and Cadence Service structure. This contains various status information for
 *        the service. */
struct ble_rscs_s
{
    ble_rscs_evt_handler_t       evt_handler;                               /**< Event handler to be called for handling events in the Running Speed and Cadence Service. */
    uint16_t                     service_handle;                            /**< Handle of Running Speed and Cadence Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t     meas_handles;                              /**< Handles related to the Running Speed and Cadence Measurement characteristic. */
    ble_gatts_char_handles_t     feature_handles;                           /**< Handles related to the Running Speed and Cadence feature characteristic. */
    uint16_t                     conn_handle;                               /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint16_t                     feature;                                   /**< Bit mask of features available on sensor. */
};



/**@brief Function for initializing the Running Speed and Cadence Service.
 *
 * @param[out]  p_rscs      Running Speed and Cadence Service structure. This structure will have to
 *                          be supplied by the application. It will be initialized by this function,
 *                          and will later be used to identify this particular service instance.
 * @param[in]   p_rscs_init Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_rscs_init(ble_rscs_t * p_rscs, const ble_rscs_init_t * p_rscs_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Running Speed and Cadence
 *          Service.
 *
 * @param[in]   p_rscs     Running Speed and Cadence Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_rscs_on_ble_evt(ble_rscs_t * p_rscs, ble_evt_t * p_ble_evt);

/**@brief Function for sending running speed and cadence measurement if notification has been enabled.
 *
 * @details The application calls this function after having performed a Running Speed and Cadence
 *          measurement. If notification has been enabled, the measurement data is encoded and sent
 *          to the client.
 *
 * @param[in]   p_rscs         Running Speed and Cadence Service structure.
 * @param[in]   p_measurement  Pointer to new running speed and cadence measurement.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_rscs_measurement_send(ble_rscs_t * p_rscs, ble_rscs_meas_t * p_measurement);


#ifdef __cplusplus
}
#endif

#endif // BLE_RSCS_H__

/** @} */
