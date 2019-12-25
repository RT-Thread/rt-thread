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
 * @defgroup ble_hts Health Thermometer Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Health Thermometer Service module.
 *
 * @details This module implements the Health Thermometer Service.
 *
 *          If an event handler is supplied by the application, the Health Thermometer
 *          Service will generate Health Thermometer Service events to the application.
 *
 * @note    The application must register this module as BLE event observer using the
 *          NRF_SDH_BLE_OBSERVER macro. Example:
 *          @code
 *              ble_hts_t instance;
 *              NRF_SDH_BLE_OBSERVER(anything, BLE_HTS_BLE_OBSERVER_PRIO,
 *                                   ble_hts_on_ble_evt, &instance);
 *          @endcode
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_HTS_H__
#define BLE_HTS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "ble_date_time.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_hts instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_HTS_DEF(_name)                                                                          \
static ble_hts_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HTS_BLE_OBSERVER_PRIO,                                                     \
                     ble_hts_on_ble_evt, &_name)

// Temperature Type measurement locations
#define BLE_HTS_TEMP_TYPE_ARMPIT        1
#define BLE_HTS_TEMP_TYPE_BODY          2
#define BLE_HTS_TEMP_TYPE_EAR           3
#define BLE_HTS_TEMP_TYPE_FINGER        4
#define BLE_HTS_TEMP_TYPE_GI_TRACT      5
#define BLE_HTS_TEMP_TYPE_MOUTH         6
#define BLE_HTS_TEMP_TYPE_RECTUM        7
#define BLE_HTS_TEMP_TYPE_TOE           8
#define BLE_HTS_TEMP_TYPE_EAR_DRUM      9


/**@brief Health Thermometer Service event type. */
typedef enum
{
    BLE_HTS_EVT_INDICATION_ENABLED,                                         /**< Health Thermometer value indication enabled event. */
    BLE_HTS_EVT_INDICATION_DISABLED,                                        /**< Health Thermometer value indication disabled event. */
    BLE_HTS_EVT_INDICATION_CONFIRMED                                        /**< Confirmation of a temperature measurement indication has been received. */
} ble_hts_evt_type_t;

/**@brief Health Thermometer Service event. */
typedef struct
{
    ble_hts_evt_type_t evt_type;                                            /**< Type of event. */
} ble_hts_evt_t;

// Forward declaration of the ble_hts_t type.
typedef struct ble_hts_s ble_hts_t;

/**@brief Health Thermometer Service event handler type. */
typedef void (*ble_hts_evt_handler_t) (ble_hts_t * p_hts, ble_hts_evt_t * p_evt);

/**@brief FLOAT format (IEEE-11073 32-bit FLOAT, defined as a 32-bit value with a 24-bit mantissa
 *        and an 8-bit exponent. */
typedef struct
{
  int8_t  exponent;                                                         /**< Base 10 exponent */
  int32_t mantissa;                                                         /**< Mantissa, should be using only 24 bits */
} ieee_float32_t;

/**@brief Health Thermometer Service init structure. This contains all options and data
 *        needed for initialization of the service. */
typedef struct
{
    ble_hts_evt_handler_t        evt_handler;                               /**< Event handler to be called for handling events in the Health Thermometer Service. */
    security_req_t               ht_meas_cccd_wr_sec;                       /**< Security requirement for writing health thermometer measurement characteristic CCCD. */
    security_req_t               ht_type_rd_sec;                            /**< Security requirement for reading health thermometer type characteristic. */
    uint8_t                      temp_type_as_characteristic;               /**< Set non-zero if temp type given as characteristic */
    uint8_t                      temp_type;                                 /**< Temperature type if temperature characteristic is used */
} ble_hts_init_t;

/**@brief Health Thermometer Service structure. This contains various status information for
 *        the service. */
struct ble_hts_s
{
    ble_hts_evt_handler_t        evt_handler;                               /**< Event handler to be called for handling events in the Health Thermometer Service. */
    uint16_t                     service_handle;                            /**< Handle of Health Thermometer Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t     meas_handles;                              /**< Handles related to the Health Thermometer Measurement characteristic. */
    ble_gatts_char_handles_t     temp_type_handles;                         /**< Handles related to the Health Thermometer Temperature Type characteristic. */
    uint16_t                     conn_handle;                               /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint8_t                      temp_type;                                 /**< Temperature type indicates where the measurement was taken. */
};

/**@brief Health Thermometer Service measurement structure. This contains a Health Thermometer
 *        measurement. */
typedef struct ble_hts_meas_s
{
    bool                         temp_in_fahr_units;                        /**< True if Temperature is in Fahrenheit units, Celcius otherwise. */
    bool                         time_stamp_present;                        /**< True if Time Stamp is present. */
    bool                         temp_type_present;                         /**< True if Temperature Type is present. */
    ieee_float32_t               temp_in_celcius;                           /**< Temperature Measurement Value (Celcius). */
    ieee_float32_t               temp_in_fahr;                              /**< Temperature Measurement Value (Fahrenheit). */
    ble_date_time_t              time_stamp;                                /**< Time Stamp. */
    uint8_t                      temp_type;                                 /**< Temperature Type. */
} ble_hts_meas_t;


/**@brief Function for initializing the Health Thermometer Service.
 *
 * @param[out]  p_hts       Health Thermometer Service structure. This structure will have to
 *                          be supplied by the application. It will be initialized by this function,
 *                          and will later be used to identify this particular service instance.
 * @param[in]   p_hts_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_hts_init(ble_hts_t * p_hts, const ble_hts_init_t * p_hts_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Health Thermometer Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Health Thermometer Service structure.
 */
void ble_hts_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for sending health thermometer measurement if indication has been enabled.
 *
 * @details The application calls this function after having performed a Health Thermometer
 *          measurement. If indication has been enabled, the measurement data is encoded and
 *          sent to the client.
 *
 * @param[in]   p_hts       Health Thermometer Service structure.
 * @param[in]   p_hts_meas  Pointer to new health thermometer measurement.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_hts_measurement_send(ble_hts_t * p_hts, ble_hts_meas_t * p_hts_meas);


/**@brief Function for checking if indication of Temperature Measurement is currently enabled.
 *
 * @param[in]   p_hts                  Health Thermometer Service structure.
 * @param[out]  p_indication_enabled   TRUE if indication is enabled, FALSE otherwise.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_hts_is_indication_enabled(ble_hts_t * p_hts, bool * p_indication_enabled);


#ifdef __cplusplus
}
#endif

#endif // BLE_HTS_H__

/** @} */
