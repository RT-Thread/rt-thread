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
/** @file
 *
 * @defgroup ble_bps Blood Pressure Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Blood Pressure Service module.
 *
 * @details This module implements the Blood Pressure Service.
 *
 *          If an event handler is supplied by the application, the Blood Pressure
 *          Service will generate Blood Pressure Service events to the application.
 *
 * @note    The application must register this module as BLE event observer using the
 *          NRF_SDH_BLE_OBSERVER macro. Example:
 *          @code
 *              ble_bps_t instance;
 *              NRF_SDH_BLE_OBSERVER(anything, BLE_BPS_BLE_OBSERVER_PRIO,
 *                                   ble_bps_on_ble_evt, &instance);
 *          @endcode
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_BPS_H__
#define BLE_BPS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "ble_date_time.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_bps instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_BPS_DEF(_name)                                                                          \
static ble_bps_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_BPS_BLE_OBSERVER_PRIO,                                                     \
                     ble_bps_on_ble_evt, &_name)


// Blood Pressure Feature bits
#define BLE_BPS_FEATURE_BODY_MOVEMENT_BIT               (0x01 << 0)         /**< Body Movement Detection Support bit. */
#define BLE_BPS_FEATURE_CUFF_FIT_BIT                    (0x01 << 1)         /**< Cuff Fit Detection Support bit. */
#define BLE_BPS_FEATURE_IRREGULAR_PULSE_BIT             (0x01 << 2)         /**< Irregular Pulse Detection Support bit. */
#define BLE_BPS_FEATURE_PULSE_RATE_RANGE_BIT            (0x01 << 3)         /**< Pulse Rate Range Detection Support bit. */
#define BLE_BPS_FEATURE_MEASUREMENT_POSITION_BIT        (0x01 << 4)         /**< Measurement Position Detection Support bit. */
#define BLE_BPS_FEATURE_MULTIPLE_BOND_BIT               (0x01 << 5)         /**< Multiple Bond Support bit. */


/**@brief Blood Pressure Service event type. */
typedef enum
{
    BLE_BPS_EVT_INDICATION_ENABLED,                                         /**< Blood Pressure value indication enabled event. */
    BLE_BPS_EVT_INDICATION_DISABLED,                                        /**< Blood Pressure value indication disabled event. */
    BLE_BPS_EVT_INDICATION_CONFIRMED                                        /**< Confirmation of a blood pressure measurement indication has been received. */
} ble_bps_evt_type_t;

/**@brief Blood Pressure Service event. */
typedef struct
{
    ble_bps_evt_type_t evt_type;                                            /**< Type of event. */
} ble_bps_evt_t;

// Forward declaration of the ble_bps_t type.
typedef struct ble_bps_s ble_bps_t;

/**@brief Blood Pressure Service event handler type. */
typedef void (*ble_bps_evt_handler_t) (ble_bps_t * p_bps, ble_bps_evt_t * p_evt);

/**@brief SFLOAT format (IEEE-11073 16-bit FLOAT, defined as a 16-bit vlue with 12-bit mantissa and
 *        4-bit exponent. */
typedef struct
{
  int8_t  exponent;                                                         /**< Base 10 exponent, only 4 bits */
  int16_t mantissa;                                                         /**< Mantissa, only 12 bits */
} ieee_float16_t;

/**@brief Blood Pressure Service init structure. This contains all options and data
 *        needed for initialization of the service. */
typedef struct
{
    ble_bps_evt_handler_t        evt_handler;                               /**< Event handler to be called for handling events in the Blood Pressure Service. */
    security_req_t               bp_cccd_wr_sec;                            /**< Security requirement for writing blood pressure measurement characteristic CCCD. */
    security_req_t               bp_feature_rd_sec;                         /**< Security requirement for reading the blood pressure feature characteristic. */
    uint16_t                     feature;                                   /**< Initial value for blood pressure feature */
} ble_bps_init_t;

/**@brief Blood Pressure Service structure. This contains various status information for
 *        the service. */
struct ble_bps_s
{
    ble_bps_evt_handler_t        evt_handler;                               /**< Event handler to be called for handling events in the Blood Pressure Service. */
    uint16_t                     service_handle;                            /**< Handle of Blood Pressure Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t     meas_handles;                              /**< Handles related to the Blood Pressure Measurement characteristic. */
    ble_gatts_char_handles_t     feature_handles;                           /**< Handles related to the Blood Pressure Feature characteristic. */
    uint16_t                     conn_handle;                               /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint16_t                     feature;                                   /**< Value of Blood Pressure feature. */
};

/**@brief Blood Pressure Service measurement structure. This contains a Blood Pressure
 *        measurement. */
typedef struct ble_bps_meas_s
{
    bool                         blood_pressure_units_in_kpa;               /**< Blood Pressure Units Flag, 0=mmHg, 1=kPa */
    bool                         time_stamp_present;                        /**< Time Stamp Flag, 0=not present, 1=present. */
    bool                         pulse_rate_present;                        /**< Pulse Rate Flag, 0=not present, 1=present. */
    bool                         user_id_present;                           /**< User ID Flag, 0=not present, 1=present. */
    bool                         measurement_status_present;                /**< Measurement Status Flag, 0=not present, 1=present. */
    ieee_float16_t               blood_pressure_systolic;                   /**< Blood Pressure Measurement Compound Value - Systolic. */
    ieee_float16_t               blood_pressure_diastolic;                  /**< Blood Pressure Measurement Compound Value - Diastolic . */
    ieee_float16_t               mean_arterial_pressure;                    /**< Blood Pressure Measurement Compound Value - Mean Arterial Pressure. */
    ble_date_time_t              time_stamp;                                /**< Time Stamp. */
    ieee_float16_t               pulse_rate;                                /**< Pulse Rate. */
    uint8_t                      user_id;                                   /**< User ID. */
    uint16_t                     measurement_status;                        /**< Measurement Status. */
} ble_bps_meas_t;


/**@brief Function for initializing the Blood Pressure Service.
 *
 * @param[out]  p_bps       Blood Pressure Service structure. This structure will have to
 *                          be supplied by the application. It will be initialized by this function,
 *                          and will later be used to identify this particular service instance.
 * @param[in]   p_bps_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_bps_init(ble_bps_t * p_bps, ble_bps_init_t const * p_bps_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Blood Pressure Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Blood Pressure Service structure.
 */
void ble_bps_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for sending blood pressure measurement if indication has been enabled.
 *
 * @details The application calls this function after having performed a Blood Pressure
 *          measurement. If indication has been enabled, the measurement data is encoded and
 *          sent to the client.
 *
 * @param[in]   p_bps       Blood Pressure Service structure.
 * @param[in]   p_bps_meas  Pointer to new blood pressure measurement.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_bps_measurement_send(ble_bps_t * p_bps, ble_bps_meas_t * p_bps_meas);


/**@brief Function for checking if indication of Blood Pressure Measurement is currently enabled.
 *
 * @param[in]   p_bps                  Blood Pressure Service structure.
 * @param[out]  p_indication_enabled   TRUE if indication is enabled, FALSE otherwise.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_bps_is_indication_enabled(ble_bps_t * p_bps, bool * p_indication_enabled);


#ifdef __cplusplus
}
#endif

#endif // BLE_BPS_H__

/** @} */
