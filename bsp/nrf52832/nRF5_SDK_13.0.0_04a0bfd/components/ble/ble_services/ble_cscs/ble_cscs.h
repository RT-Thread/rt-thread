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
 * @defgroup ble_cscs Cycling Speed and Cadence Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Cycling Speed and Cadence Service module.
 *
 * @details This module implements the Cycling Speed and Cadence Service. If enabled, notification
 *          of the Cycling Speead and Candence Measurement is performed when the application
 *          calls ble_cscs_measurement_send().
 *
 *          To use this service, you need to provide the the supported features (@ref BLE_CSCS_FEATURES).
 *          If you choose to support Wheel revolution data (feature bit @ref BLE_CSCS_FEATURE_WHEEL_REV_BIT),
 *          you then need to support the 'setting of cumulative value' operation by the supporting the
 *          Speed and Cadence Control Point (@ref ble_sdk_srv_sc_ctrlpt) by setting the @ref BLE_SRV_SC_CTRLPT_CUM_VAL_OP_SUPPORTED
 *          bit of the ctrplt_supported_functions in the @ref ble_cscs_init_t structure.
 *          If you want to support the 'start autocalibration' control point feature, you need, after the @ref BLE_SC_CTRLPT_EVT_START_CALIBRATION
 *          has been received and the auto calibration is finished, to call the @ref ble_sc_ctrlpt_rsp_send to indicate that the operation is finished
 *          and thus be able to receive new control point operations.
 *          If you want to support the 'sensor location' related operation, you need to provide a list of supported location in the
 *          @ref ble_cscs_init_t structure.
 *
 *
 * @note The application or the service using this module must propagate BLE stack events to the
 *       Cycling Speead and Candence Service module by calling ble_cscs_on_ble_evt() from the
 *       from the @ref softdevice_handler function. This service will forward the event to the @ref ble_sdk_srv_sc_ctrlpt module.
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_CSCS_H__
#define BLE_CSCS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "ble_sc_ctrlpt.h"
#include "ble_sensor_location.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup BLE_CSCS_FEATURES Cycling Speed and Cadence Service feature bits
 * @{ */
#define BLE_CSCS_FEATURE_WHEEL_REV_BIT                  (0x01 << 0)     /**< Wheel Revolution Data Supported bit. */
#define BLE_CSCS_FEATURE_CRANK_REV_BIT                  (0x01 << 1)     /**< Crank Revolution Data Supported bit. */
#define BLE_CSCS_FEATURE_MULTIPLE_SENSORS_BIT           (0x01 << 2)     /**< Multiple Sensor Locations Supported bit. */
/** @} */

/**@brief Cycling Speed and Cadence Service event type. */
typedef enum
{
    BLE_CSCS_EVT_NOTIFICATION_ENABLED,                                  /**< Cycling Speed and Cadence value notification enabled event. */
    BLE_CSCS_EVT_NOTIFICATION_DISABLED                                  /**< Cycling Speed and Cadence value notification disabled event. */
} ble_cscs_evt_type_t;

/**@brief Cycling Speed and Cadence Service event. */
typedef struct
{
    ble_cscs_evt_type_t evt_type;                                       /**< Type of event. */
} ble_cscs_evt_t;

// Forward declaration of the ble_csc_t type.
typedef struct ble_cscs_s ble_cscs_t;

/**@brief Cycling Speed and Cadence Service event handler type. */
typedef void (*ble_cscs_evt_handler_t) (ble_cscs_t * p_cscs, ble_cscs_evt_t * p_evt);

/**@brief Cycling Speed and Cadence Service init structure. This contains all options and data
*         needed for initialization of the service. */
typedef struct
{
    ble_cscs_evt_handler_t       evt_handler;                           /**< Event handler to be called for handling events in the Cycling Speed and Cadence Service. */
    ble_srv_cccd_security_mode_t csc_meas_attr_md;                      /**< Initial security level for cycling speed and cadence measurement attribute */
    ble_srv_cccd_security_mode_t csc_ctrlpt_attr_md;                    /**< Initial security level for cycling speed and cadence control point attribute */
    ble_srv_security_mode_t      csc_feature_attr_md;                   /**< Initial security level for feature attribute */
    uint16_t                     feature;                               /**< Initial value for features of sensor @ref BLE_CSCS_FEATURES. */
    uint8_t                      ctrplt_supported_functions;            /**< Supported control point functionalities see @ref BLE_SRV_SC_CTRLPT_SUPP_FUNC. */
    ble_sc_ctrlpt_evt_handler_t  ctrlpt_evt_handler;                    /**< Event handler */
    ble_sensor_location_t        *list_supported_locations;             /**< List of supported sensor locations.*/
    uint8_t                      size_list_supported_locations;         /**< Number of supported sensor locations in the list.*/
    ble_srv_error_handler_t      error_handler;                         /**< Function to be called in case of an error. */
    ble_sensor_location_t        *sensor_location;                      /**< Initial Sensor Location, if NULL, sensor_location characteristic is not added*/
    ble_srv_cccd_security_mode_t csc_sensor_loc_attr_md;                /**< Initial security level for sensor location attribute */
} ble_cscs_init_t;

/**@brief Cycling Speed and Cadence Service structure. This contains various status information for
 *        the service. */
struct ble_cscs_s
{
    ble_cscs_evt_handler_t       evt_handler;                           /**< Event handler to be called for handling events in the Cycling Speed and Cadence Service. */
    uint16_t                     service_handle;                        /**< Handle of Cycling Speed and Cadence Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t     meas_handles;                          /**< Handles related to the Cycling Speed and Cadence Measurement characteristic. */
    ble_gatts_char_handles_t     feature_handles;                       /**< Handles related to the Cycling Speed and Cadence feature characteristic. */
    ble_gatts_char_handles_t     sensor_loc_handles;                    /**< Handles related to the Cycling Speed and Cadence Sensor Location characteristic. */
    uint16_t                     conn_handle;                           /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint16_t                     feature;                               /**< Bit mask of features available on sensor. */
    ble_sc_ctrlpt_t              ctrl_pt;                               /**< data for speed and cadence control point */
};

/**@brief Cycling Speed and Cadence Service measurement structure. This contains a Cycling Speed and
 *        Cadence Service measurement. */
typedef struct ble_cscs_meas_s
{
    bool        is_wheel_rev_data_present;                              /**< True if Wheel Revolution Data is present in the measurement. */
    bool        is_crank_rev_data_present;                              /**< True if Crank Revolution Data is present in the measurement. */
    uint32_t    cumulative_wheel_revs;                                  /**< Cumulative Wheel Revolutions. */
    uint16_t    last_wheel_event_time;                                  /**< Last Wheel Event Time. */
    uint16_t    cumulative_crank_revs;                                  /**< Cumulative Crank Revolutions. */
    uint16_t    last_crank_event_time;                                  /**< Last Crank Event Time. */
} ble_cscs_meas_t;

/**@brief Function for initializing the Cycling Speed and Cadence Service.
 *
 * @param[out]  p_cscs      Cycling Speed and Cadence Service structure. This structure will have to
 *                          be supplied by the application. It will be initialized by this function,
 *                          and will later be used to identify this particular service instance.
 * @param[in]   p_cscs_init Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_cscs_init(ble_cscs_t * p_cscs, const ble_cscs_init_t * p_cscs_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Cycling Speed and Cadence
 *          Service.
 *
 * @param[in]   p_cscs     Cycling Speed and Cadence Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_cscs_on_ble_evt(ble_cscs_t * p_cscs, ble_evt_t * p_ble_evt);

/**@brief Function for sending cycling speed and cadence measurement if notification has been enabled.
 *
 * @details The application calls this function after having performed a Cycling Speed and Cadence
 *          Service measurement. If notification has been enabled, the measurement data is encoded
 *          and sent to the client.
 *
 * @param[in]   p_cscs         Cycling Speed and Cadence Service structure.
 * @param[in]   p_measurement  Pointer to new cycling speed and cadence measurement.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_cscs_measurement_send(ble_cscs_t * p_cscs, ble_cscs_meas_t * p_measurement);


#ifdef __cplusplus
}
#endif

#endif // BLE_CSCS_H__

/** @} */
