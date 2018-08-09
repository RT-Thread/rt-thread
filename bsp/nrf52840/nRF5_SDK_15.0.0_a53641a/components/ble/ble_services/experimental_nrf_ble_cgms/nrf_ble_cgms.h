/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
 * @defgroup ble_cgms Continuous Glucose Monitoring Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Continuous Glucose Monitoring Service (CGMS) module.
 *
 * @details This module implements a sensor for the Continuous Glucose Monitoring Service.
 *          The sensor is a GATT Server that sends CGM measurements to a connected CGMS
 *          Collector. The CGMS Sensor stores records that can be accessed with the
 *          Record Access Control Point (RACP). The collector can access the features and status
 *          of the sensor. Session Run Time and Session Start Time can be used to convey timing
 *          information between the sensor and the collector. The Specific Operations Control Point
 *          is used to stop and start monitoring sessions, among other things.
 *
 * @note    The application must register this module as BLE event observer using the
 *          NRF_SDH_BLE_OBSERVER macro. Example:
 *          @code
 *              nrf_ble_cgms_t instance;
 *              NRF_SDH_BLE_OBSERVER(anything, NRF_BLE_CGMS_BLE_OBSERVER_PRIO,
 *                                   nrf_ble_cgms_on_ble_evt, &instance);
 *          @endcode
 */

#ifndef NRF_BLE_CGMS_H__
#define NRF_BLE_CGMS_H__

#include "ble_srv_common.h"
#include "sdk_errors.h"
#include "ble_racp.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a nrf_ble_cgms instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define NRF_BLE_CGMS_DEF(_name)                                                                     \
static nrf_ble_cgms_t _name;                                                                        \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     NRF_BLE_CGMS_BLE_OBSERVER_PRIO,                                                \
                     nrf_ble_cgms_on_ble_evt, &_name)

/**@name CGM Feature characteristic defines
 * @{ */
#define NRF_BLE_CGMS_FEAT_CALIBRATION_SUPPORTED                           (0x01 << 0)  //!< Calibration supported.
#define NRF_BLE_CGMS_FEAT_PATIENT_HIGH_LOW_ALERTS_SUPPORTED               (0x01 << 1)  //!< Patient High/Low Alerts supported.
#define NRF_BLE_CGMS_FEAT_HYPO_ALERTS_SUPPORTED                           (0x01 << 2)  //!< Hypo Alerts supported.
#define NRF_BLE_CGMS_FEAT_HYPER_ALERTS_SUPPORTED                          (0x01 << 3)  //!< Hyper Alerts supported.
#define NRF_BLE_CGMS_FEAT_RATE_OF_INCREASE_DECREASE_ALERTS_SUPPORTED      (0x01 << 4)  //!< Rate of Increase/Decrease Alerts supported.
#define NRF_BLE_CGMS_FEAT_DEVICE_SPECIFIC_ALERT_SUPPORTED                 (0x01 << 5)  //!< Device Specific Alert supported.
#define NRF_BLE_CGMS_FEAT_SENSOR_MALFUNCTION_DETECTION_SUPPORTED          (0x01 << 6)  //!< Sensor Malfunction Detection supported.
#define NRF_BLE_CGMS_FEAT_SENSOR_TEMPERATURE_HIGH_LOW_DETECTION_SUPPORTED (0x01 << 7)  //!< Sensor Temperature High-Low Detection supported.
#define NRF_BLE_CGMS_FEAT_SENSOR_RESULT_HIGH_LOW_DETECTION_SUPPORTED      (0x01 << 8)  //!< Sensor Result High-Low Detection supported.
#define NRF_BLE_CGMS_FEAT_LOW_BATTERY_DETECTION_SUPPORTED                 (0x01 << 9)  //!< Low Battery Detection supported.
#define NRF_BLE_CGMS_FEAT_SENSOR_TYPE_ERROR_DETECTION_SUPPORTED           (0x01 << 10) //!< Sensor Type Error Detection supported.
#define NRF_BLE_CGMS_FEAT_GENERAL_DEVICE_FAULT_SUPPORTED                  (0x01 << 11) //!< General Device Fault supported.
#define NRF_BLE_CGMS_FEAT_E2E_CRC_SUPPORTED                               (0x01 << 12) //!< E2E-CRC supported.
#define NRF_BLE_CGMS_FEAT_MULTIPLE_BOND_SUPPORTED                         (0x01 << 13) //!< Multiple Bond supported.
#define NRF_BLE_CGMS_FEAT_MULTIPLE_SESSIONS_SUPPORTED                     (0x01 << 14) //!< Multiple Sessions supported.
#define NRF_BLE_CGMS_FEAT_CGM_TREND_INFORMATION_SUPPORTED                 (0x01 << 15) //!< CGM Trend Information supported.
#define NRF_BLE_CGMS_FEAT_CGM_QUALITY_SUPPORTED                           (0x01 << 16) //!< CGM Quality supported.
/** @} */

/**@name Continuous Glucose Monitoring type
 * @{ */
#define NRF_BLE_CGMS_MEAS_TYPE_CAP_BLOOD     0x01  //!< Capillary Whole blood.
#define NRF_BLE_CGMS_MEAS_TYPE_CAP_PLASMA    0x02  //!< Capillary Plasma.
#define NRF_BLE_CGMS_MEAS_TYPE_VEN_BLOOD     0x03  //!< Venous Whole blood.
#define NRF_BLE_CGMS_MEAS_TYPE_VEN_PLASMA    0x04  //!< Venous Plasma.
#define NRF_BLE_CGMS_MEAS_TYPE_ART_BLOOD     0x05  //!< Arterial Whole blood.
#define NRF_BLE_CGMS_MEAS_TYPE_ART_PLASMA    0x06  //!< Arterial Plasma.
#define NRF_BLE_CGMS_MEAS_TYPE_UNDET_BLOOD   0x07  //!< Undetermined Whole blood.
#define NRF_BLE_CGMS_MEAS_TYPE_UNDET_PLASMA  0x08  //!< Undetermined Plasma.
#define NRF_BLE_CGMS_MEAS_TYPE_FLUID         0x09  //!< Interstitial Fluid (ISF).
#define NRF_BLE_CGMS_MEAS_TYPE_CONTROL       0x0A  //!< Control Solution.
/** @} */

/**@name CGM sample location
 * @{ */
#define NRF_BLE_CGMS_MEAS_LOC_FINGER         0x01  //!< Finger.
#define NRF_BLE_CGMS_MEAS_LOC_AST            0x02  //!< Alternate Site Test (AST).
#define NRF_BLE_CGMS_MEAS_LOC_EAR            0x03  //!< Earlobe.
#define NRF_BLE_CGMS_MEAS_LOC_CONTROL        0x04  //!< Control solution.
#define NRF_BLE_CGMS_MEAS_LOC_SUB_TISSUE     0x05  //!< Subcutaneous tissue.
#define NRF_BLE_CGMS_MEAS_LOC_NOT_AVAIL      0x0F  //!< Sample Location value not available.
/** @} */

/**@name CGM Measurement Sensor Status Annunciation
 * @{ */
#define NRF_BLE_CGMS_STATUS_SESSION_STOPPED                  (0x01 << 0) //!< Status: Session Stopped.
#define NRF_BLE_CGMS_STATUS_DEVICE_BATTERY_LOW               (0x01 << 1) //!< Status: Device Battery Low.
#define NRF_BLE_CGMS_STATUS_SENSOR_TYPE_INCORRECT_FOR_DEVICE (0x01 << 2) //!< Status: Sensor type incorrect for device.
#define NRF_BLE_CGMS_STATUS_SENSOR_MALFUNCTION               (0x01 << 3) //!< Status: Sensor malfunction.
#define NRF_BLE_CGMS_STATUS_DEVICE_SPECIFIC_ALERT            (0x01 << 4) //!< Status: Device Specific Alert.
#define NRF_BLE_CGMS_STATUS_GENERAL_DEVICE_FAULT             (0x01 << 5) //!< Status: General device fault has occurred in the sensor.
/** @} */

/**@name CGM Measurement flags
 * @{ */
#define NRF_BLE_CGMS_FLAG_TREND_INFO_PRESENT                 0x01        //!< CGM Trend Information Present.
#define NRF_BLE_CGMS_FLAGS_QUALITY_PRESENT                   0x02        //!< CGM Quality Present.
#define NRF_BLE_CGMS_STATUS_FLAGS_WARNING_OCT_PRESENT        0x20        //!< Sensor Status Annunciation Field, Warning-Octet present.
#define NRF_BLE_CGMS_STATUS_FLAGS_CALTEMP_OCT_PRESENT        0x40        //!< Sensor Status Annunciation Field, Cal/Temp-Octet present.
#define NRF_BLE_CGMS_STATUS_FLAGS_STATUS_OCT_PRESENT         0x80        //!< Sensor Status Annunciation Field, Status-Octet present.
/** @} */

/**@name Byte length of various commands (used for validating, encoding, and decoding data).
 * @{ */
#define NRF_BLE_CGMS_MEAS_OP_LEN            1                               //!< Length of the opcode inside the Glucose Measurement packet.
#define NRF_BLE_CGMS_MEAS_HANDLE_LEN        2                               //!< Length of the handle inside the Glucose Measurement packet.
#define NRF_BLE_CGMS_MEAS_LEN_MAX           (BLE_GATT_ATT_MTU_DEFAULT - \
                                             NRF_BLE_CGMS_MEAS_OP_LEN - \
                                             NRF_BLE_CGMS_MEAS_HANDLE_LEN)  //!< Maximum size of a transmitted Glucose Measurement.

#define NRF_BLE_CGMS_MEAS_REC_LEN_MAX       15                              //!< Maximum length of one measurement record. Size 1 byte, flags 1 byte, glucose concentration 2 bytes, offset 2 bytes, status 3 bytes, trend 2 bytes, quality 2 bytes, CRC 2 bytes.
#define NRF_BLE_CGMS_MEAS_REC_LEN_MIN       6                               //!< Minimum length of one measurement record. Size 1 byte, flags 1 byte, glucose concentration 2 bytes, offset 2 bytes.
#define NRF_BLE_CGMS_MEAS_REC_PER_NOTIF_MAX (NRF_BLE_CGMS_MEAS_LEN_MAX / \
                                             NRF_BLE_CGMS_MEAS_REC_LEN_MIN) //!< Maximum number of records per notification. We can send more than one measurement record per notification, but we do not want a a single record split over two notifications.

#define NRF_BLE_CGMS_SOCP_RESP_CODE_LEN     2                               //!< Length of a response. Response code 1 byte, response value 1 byte.
#define NRF_BLE_CGMS_FEATURE_LEN            6                               //!< Length of a feature. Feature 3 bytes, type 4 bits, sample location 4 bits, CRC 2 bytes.
#define NRF_BLE_CGMS_STATUS_LEN             7                               //!< Length of a status. Offset 2 bytes, status 3 bytes, CRC 2 bytes.
#define NRF_BLE_CGMS_MAX_CALIB_LEN          10                              //!< Length of a calibration record. Concentration 2 bytes, time 2 bytes, calibration 4 bits, calibration sample location 4 bits, next calibration time 2 bytes, record number 2 bytes, calibration status 1 byte.
#define NRF_BLE_CGMS_CALIBS_NB_MAX          5                               //!< Maximum number of calibration values that can be stored.
#define NRF_BLE_CGMS_SST_LEN                9                               //!< Length of the start time. Date time 7 bytes, time zone 1 byte, DST 1 byte.
#define NRF_BLE_CGMS_CRC_LEN                2                               //!< Length of the CRC bytes (if used).
#define NRF_BLE_CGMS_SRT_LEN                2                               //!< Length of the Session Run Time attribute.

#define NRF_BLE_CGMS_SOCP_RESP_LEN          (NRF_BLE_CGMS_MEAS_LEN_MAX - \
                                            NRF_BLE_CGMS_SOCP_RESP_CODE_LEN) //!< Max lenth of a SOCP response.

#define NRF_BLE_CGMS_RACP_PENDING_OPERANDS_MAX 2                             // !< Maximum number of pending Record Access Control Point operations.
/** @} */

/**
 * @defgroup nrf_ble_cgms_enums Enumerations
 * @{
 */

/**@brief CGM Service events. */
typedef enum
{
    NRF_BLE_CGMS_EVT_NOTIFICATION_ENABLED,  /**< Glucose value notification enabled. */
    NRF_BLE_CGMS_EVT_NOTIFICATION_DISABLED, /**< Glucose value notification disabled. */
    NRF_BLE_CGMS_EVT_START_SESSION,         /**< Glucose value notification start session. */
    NRF_BLE_CGMS_EVT_STOP_SESSION,          /**< Glucose value notification stop session. */
    NRF_BLE_CGMS_EVT_WRITE_COMM_INTERVAL,   /**< Glucose value write communication interval. */
} nrf_ble_cgms_evt_type_t;


/**@brief CGM Service communication states. */
typedef enum
{
    STATE_NO_COMM,                 /**< The service is not in a communicating state. */
    STATE_RACP_PROC_ACTIVE,        /**< Processing requested data. */
    STATE_RACP_RESPONSE_PENDING,   /**< There is an RACP indication waiting to be sent. */
    STATE_RACP_RESPONSE_IND_VERIF, /**< Waiting for a verification of an RACP indication. */
    STATE_SOCP_RESPONSE_PENDING,   /**< There is an SOCP indication waiting to be sent. */
    STATE_SOCP_RESPONSE_IND_VERIF  /**< Waiting for a verification of an SOCP indication. */
} nrf_ble_cgms_com_state_t;

/** @} */ // End tag for Enumeration group.

/**
 * @defgroup nrf_ble_cgms_structs Structures
 * @{
 */

/**@brief CGM Service event. */
typedef struct
{
    nrf_ble_cgms_evt_type_t evt_type; /**< Type of event. */
} nrf_ble_cgms_evt_t;

/** @} */ // End tag for Structure group.

/**
 * @defgroup nrf_ble_cgms_types Types
 * @{
 */

/**@brief Forward declaration of the nrf_ble_cgms_t type. */
typedef struct ble_cgms_s nrf_ble_cgms_t;


/**@brief CGM Service event handler type. */
typedef void (* ble_cgms_evt_handler_t) (nrf_ble_cgms_t * p_cgms, nrf_ble_cgms_evt_t * p_evt);

/** @} */ // End tag for Types group.

/**
 * @addtogroup nrf_ble_cgms_structs
 * @{
 */

/**@brief CGM Measurement Sensor Status Annunciation. */
typedef struct
{
    uint8_t warning;               /**< Warning annunciation. */
    uint8_t calib_temp;            /**< Calibration and Temperature annunciation. */
    uint8_t status;                /**< Status annunciation. */
} nrf_ble_cgms_sensor_annunc_t;


/**@brief CGM measurement. */
typedef struct
{
    uint8_t                      flags;                      /**< Indicates the presence of optional fields and the Sensor Status Annunciation field. */
    uint16_t                     glucose_concentration;      /**< Glucose concentration. 16-bit word comprising 4-bit exponent and signed 12-bit mantissa. */
    uint16_t                     time_offset;                /**< Time offset. Represents the time difference between measurements. */
    nrf_ble_cgms_sensor_annunc_t sensor_status_annunciation; /**< Sensor Status Annunciation. Variable length, can include Status, Cal/Temp, and Warning. */
    uint16_t                     trend;                      /**< Optional field that can include Trend Information. */
    uint16_t                     quality;                    /**< Optional field that includes the Quality of the measurement. */
} nrf_ble_cgms_meas_t;


/**@brief CGM Measurement record. */
typedef struct
{
    nrf_ble_cgms_meas_t meas; /**< CGM measurement. */
} ble_cgms_rec_t;


/**@brief Features supported by the CGM Service. */
typedef struct
{
    uint32_t feature;         /**< Information on supported features in the CGM Service. */
    uint8_t  type;            /**< Type. */
    uint8_t  sample_location; /**< Sample location. */
}nrf_ble_cgms_feature_t;


/**@brief Status of the CGM measurement. */
typedef struct
{
    uint16_t                     time_offset; /**< Time offset. */
    nrf_ble_cgms_sensor_annunc_t status;      /**< Status. */
} nrf_ble_cgm_status_t;


/**@brief CGM Service initialization structure that contains all options and data needed for
 *        initializing the service. */
typedef struct
{
    ble_cgms_evt_handler_t  evt_handler;           /**< Event handler to be called for handling events in the CGM Service. */
    ble_srv_error_handler_t error_handler;         /**< Function to be called when an error occurs. */
    nrf_ble_cgms_feature_t  feature;               /**< Features supported by the service. */
    nrf_ble_cgm_status_t    initial_sensor_status; /**< Sensor status. */
    uint16_t                initial_run_time;      /**< Run time. */
} nrf_ble_cgms_init_t;


/**@brief Specific Operation Control Point response structure. */
typedef struct
{
    uint8_t opcode;                               /**< Opcode describing the response. */
    uint8_t req_opcode;                           /**< The original opcode for the request to which this response belongs. */
    uint8_t rsp_code;                             /**< Response code. */
    uint8_t resp_val[NRF_BLE_CGMS_SOCP_RESP_LEN]; /**< Array containing the response value. */
    uint8_t size_val;                             /**< Length of the response value. */
} ble_socp_rsp_t;


/**@brief Calibration value. */
typedef struct
{
    uint8_t value[NRF_BLE_CGMS_MAX_CALIB_LEN]; /**< Array containing the calibration value. */
} nrf_ble_cgms_calib_t;


/**@brief Record Access Control Point transaction data. */
typedef struct
{
    uint8_t          racp_proc_operator;                                                    /**< Operator of the current request. */
    uint16_t         racp_proc_record_ndx;                                                  /**< Current record index. */
    uint16_t         racp_proc_records_ndx_last_to_send;                                    /**< The last record to send, can be used together with racp_proc_record_ndx to determine a range of records to send. (used by greater/less filters). */
    uint16_t         racp_proc_records_reported;                                            /**< Number of reported records. */
    uint16_t         racp_proc_records_reported_since_txcomplete;                           /**< Number of reported records since the last TX_COMPLETE event. */
    ble_racp_value_t racp_request;                                                          /**< RACP procedure that has been requested from the peer. */
    ble_racp_value_t pending_racp_response;                                                 /**< RACP response to be sent. */
    uint8_t          pending_racp_response_operand[NRF_BLE_CGMS_RACP_PENDING_OPERANDS_MAX]; /**< Operand of the RACP response to be sent. */
} nrf_ble_cgms_racp_t;


/** @brief Handles related to CGM characteristics. */
typedef struct
{
    ble_gatts_char_handles_t measurment; /**< Handles related to the CGM Measurement characteristic. */
    ble_gatts_char_handles_t feature;    /**< Handles related to the CGM Feature characteristic. */
    ble_gatts_char_handles_t sst;        /**< Handles related to the CGM Session Start Time characteristic. */
    ble_gatts_char_handles_t racp;       /**< Handles related to the CGM Record Access Control Point characteristic. */
    ble_gatts_char_handles_t srt;        /**< Handles related to the CGM Session Run Time characteristic. */
    ble_gatts_char_handles_t socp;       /**< Handles related to the CGM Specific Operations Control Point characteristic. */
    ble_gatts_char_handles_t status;     /**< Handles related to the CGM Status characteristic. */
} nrf_ble_cgms_char_handler_t;


/**@brief Status information for the CGM Service. */
struct ble_cgms_s
{
    ble_cgms_evt_handler_t      evt_handler;                                 /**< Event handler to be called for handling events in the CGM Service. */
    ble_srv_error_handler_t     error_handler;                               /**< Function to be called if an error occurs. */
    uint16_t                    service_handle;                              /**< Handle of the CGM Service (as provided by the BLE stack). */
    nrf_ble_cgms_char_handler_t char_handles;                                /**< GATTS characteristic handles for the different characteristics in the service. */
    uint16_t                    conn_handle;                                 /**< Handle of the current connection (as provided by the BLE stack; @ref BLE_CONN_HANDLE_INVALID if not in a connection). */
    nrf_ble_cgms_feature_t      feature;                                     /**< Structure to store the value of the feature characteristic. */
    uint8_t                     comm_interval;                               /**< Variable to keep track of the communication interval. */
    ble_socp_rsp_t              socp_response;                               /**< Structure containing reponse data to be indicated to the peer device. */
    nrf_ble_cgms_calib_t        calibration_val[NRF_BLE_CGMS_CALIBS_NB_MAX]; /**< Calibration value. Can be read from and written to SOCP. */
    bool                        is_session_started;                          /**< Indicator if we are currently in a session. */
    uint8_t                     nb_run_session;                              /**< Variable to keep track of the number of sessions that were run. */
    uint16_t                    session_run_time;                            /**< Variable to store the expected run time of a session. */
    nrf_ble_cgm_status_t        sensor_status;                               /**< Structure to keep track of the sensor status. */
    nrf_ble_cgms_com_state_t    cgms_com_state;                              /**< Current communication state. */
    nrf_ble_cgms_racp_t         racp_data;                                   /**< Structure to manage Record Access requests. */
};

/** @} */


/**
 * @defgroup nrf_ble_cgms_functions Functions
 * @{
 */

/**@brief Function for updating the status.
 *
 * @param[in] p_cgms   Instance of the CGM Service.
 * @param[in] p_status New status.
 *
 * @retval NRF_SUCCESS    If the status was updated successfully.
 * @return                If functions from other modules return errors to this function,
 *                        the @ref nrf_error are propagated.
 */
ret_code_t nrf_ble_cgms_update_status(nrf_ble_cgms_t * p_cgms, nrf_ble_cgm_status_t * p_status);


/**@brief Function for initializing the CGM Service.
 *
 * @param[out] p_cgms      CGM Service structure. This structure must be supplied by
 *                         the application. It is initialized by this function and will later
 *                         be used to identify this particular service instance.
 * @param[in]  p_cgms_init Information needed to initialize the service.
 *
 * @retval NRF_SUCCESS    If the service was initialized successfully.
 * @retval NRF_ERROR_NULL If any of the input parameters are NULL.
 * @return                If functions from other modules return errors to this function,
 *                        the @ref nrf_error are propagated.
 */
ret_code_t nrf_ble_cgms_init(nrf_ble_cgms_t * p_cgms, const nrf_ble_cgms_init_t * p_cgms_init);


/**@brief Function for handling the application's BLE stack events.
 *
 * @details Handles all events from the BLE stack that are of interest to the CGM Service.
 *
 * @param[in] p_ble_evt Event received from the BLE stack.
 * @param[in] p_context Instance of the CGM Service.
 */
void nrf_ble_cgms_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for reporting a new glucose measurement to the CGM Service module.
 *
 * @details The application calls this function after having performed a new glucose measurement.
 *          The new measurement is recorded in the RACP database.
 *
 * @param[in] p_cgms Instance of the CGM Service.
 * @param[in] p_rec  Pointer to the glucose record (measurement plus context).
 *
 * @retval NRF_SUCCESS If a measurement was successfully created.
 * @return             If functions from other modules return errors to this function,
 *                     the @ref nrf_error are propagated.
 */
ret_code_t nrf_ble_cgms_meas_create(nrf_ble_cgms_t * p_cgms, ble_cgms_rec_t * p_rec);


/**@brief Function for assigning a connection handle to a CGM Service instance.
 *
 * @param[in] p_cgms      Instance of the CGM Service.
 * @param[in] conn_handle Connection Handle to use for this instance of the CGM Service.
 *
 * @retval NRF_SUCCESS    If the connection handle was successfully stored in the CGM Service instance.
 * @retval NRF_ERROR_NULL If any of the input parameters are NULL.
 */
ret_code_t nrf_ble_cgms_conn_handle_assign(nrf_ble_cgms_t * p_cgms, uint16_t conn_handle);


/**@brief Function for setting the Session Run Time attribute value.
 *
 * @param[in] p_cgms   Instance of the CGM Service.
 * @param[in] run_time Run Time that will be displayed in the Session Run Time
 *                     attribute value.
 *
 * @retval NRF_SUCCESS If the Session Run Time attribute value was set successfully.
 * @return             If functions from other modules return errors to this function,
 *                     the @ref nrf_error are propagated.
 */
ret_code_t nrf_ble_cgms_srt_set(nrf_ble_cgms_t * p_cgms, uint16_t run_time);

/** @} */ // End tag for Function group.

#ifdef __cplusplus
}
#endif

#endif // NRF_BLE_CGMS_H__

/** @} */
