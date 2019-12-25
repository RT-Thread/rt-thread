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
 * @defgroup ble_gls Glucose Service
 * @{
 * @ingroup ble_sdk_srv
 * @brief Glucose Service module.
 *
 * @details This module implements the Glucose Service.
 *
 * @note    The application must register this module as BLE event observer using the
 *          NRF_SDH_BLE_OBSERVER macro. Example:
 *          @code
 *              ble_gls_t instance;
 *              NRF_SDH_BLE_OBSERVER(anything, BLE_GLS_BLE_OBSERVER_PRIO,
 *                                   ble_gls_on_ble_evt, &instance);
 *          @endcode
 *
 * @note Attention!
 *  To maintain compliance with Nordic Semiconductor ASA Bluetooth profile
 *  qualification listings, this section of source code must not be modified.
 */

#ifndef BLE_GLS_H__
#define BLE_GLS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "ble_date_time.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_gls instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_GLS_DEF(_name)                                                                          \
static ble_gls_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_GLS_BLE_OBSERVER_PRIO,                                                     \
                     ble_gls_on_ble_evt, &_name)


/**@brief Glucose feature */
#define BLE_GLS_FEATURE_LOW_BATT                        0x0001  /**< Low Battery Detection During Measurement Supported */
#define BLE_GLS_FEATURE_MALFUNC                         0x0002  /**< Sensor Malfunction Detection Supported */
#define BLE_GLS_FEATURE_SAMPLE_SIZE                     0x0004  /**< Sensor Sample Size Supported */
#define BLE_GLS_FEATURE_INSERT_ERR                      0x0008  /**< Sensor Strip Insertion Error Detection Supported */
#define BLE_GLS_FEATURE_TYPE_ERR                        0x0010  /**< Sensor Strip Type Error Detection Supported */
#define BLE_GLS_FEATURE_RES_HIGH_LOW                    0x0020  /**< Sensor Result High-Low Detection Supported */
#define BLE_GLS_FEATURE_TEMP_HIGH_LOW                   0x0040  /**< Sensor Temperature High-Low Detection Supported */
#define BLE_GLS_FEATURE_READ_INT                        0x0080  /**< Sensor Read Interrupt Detection Supported */
#define BLE_GLS_FEATURE_GENERAL_FAULT                   0x0100  /**< General Device Fault Supported */
#define BLE_GLS_FEATURE_TIME_FAULT                      0x0200  /**< Time Fault Supported */
#define BLE_GLS_FEATURE_MULTI_BOND                      0x0400  /**< Multiple Bond Supported */

/**@brief Glucose measurement flags */
#define BLE_GLS_MEAS_FLAG_TIME_OFFSET                   0x01    /**< Time Offset Present */
#define BLE_GLS_MEAS_FLAG_CONC_TYPE_LOC                 0x02    /**< Glucose Concentration, Type, and Sample Location Present */
#define BLE_GLS_MEAS_FLAG_UNITS_KG_L                    0x00    /**< Glucose Concentration Units kg/L */
#define BLE_GLS_MEAS_FLAG_UNITS_MOL_L                   0x04    /**< Glucose Concentration Units mol/L */
#define BLE_GLS_MEAS_FLAG_SENSOR_STATUS                 0x08    /**< Sensor Status Annunciation Present */
#define BLE_GLS_MEAS_FLAG_CONTEXT_INFO                  0x10    /**< Context Information Follows */

/**@brief Glucose measurement type */
#define BLE_GLS_MEAS_TYPE_CAP_BLOOD                     1       /**< Capillary whole blood */
#define BLE_GLS_MEAS_TYPE_CAP_PLASMA                    2       /**< Capillary plasma */
#define BLE_GLS_MEAS_TYPE_VEN_BLOOD                     3       /**< Venous whole blood */
#define BLE_GLS_MEAS_TYPE_VEN_PLASMA                    4       /**< Venous plasma */
#define BLE_GLS_MEAS_TYPE_ART_BLOOD                     5       /**< Arterial whole blood */
#define BLE_GLS_MEAS_TYPE_ART_PLASMA                    6       /**< Arterial plasma */
#define BLE_GLS_MEAS_TYPE_UNDET_BLOOD                   7       /**< Undetermined whole blood */
#define BLE_GLS_MEAS_TYPE_UNDET_PLASMA                  8       /**< Undetermined plasma */
#define BLE_GLS_MEAS_TYPE_FLUID                         9       /**< Interstitial fluid (ISF) */
#define BLE_GLS_MEAS_TYPE_CONTROL                       10      /**< Control solution */

/**@brief Glucose measurement location */
#define BLE_GLS_MEAS_LOC_FINGER                         1       /**< Finger */
#define BLE_GLS_MEAS_LOC_AST                            2       /**< Alternate Site Test (AST) */
#define BLE_GLS_MEAS_LOC_EAR                            3       /**< Earlobe */
#define BLE_GLS_MEAS_LOC_CONTROL                        4       /**< Control solution */
#define BLE_GLS_MEAS_LOC_NOT_AVAIL                      15      /**< Sample Location value not available */

/**@brief Glucose sensor status annunciation */
#define BLE_GLS_MEAS_STATUS_BATT_LOW                    0x0001  /**< Device battery low at time of measurement */
#define BLE_GLS_MEAS_STATUS_SENSOR_FAULT                0x0002  /**< Sensor malfunction or faulting at time of measurement */
#define BLE_GLS_MEAS_STATUS_SAMPLE_SIZE                 0x0004  /**< Sample size for blood or control solution insufficient at time of measurement */
#define BLE_GLS_MEAS_STATUS_STRIP_INSERT                0x0008  /**< Strip insertion error */
#define BLE_GLS_MEAS_STATUS_STRIP_TYPE                  0x0010  /**< Strip type incorrect for device */
#define BLE_GLS_MEAS_STATUS_RESULT_HIGH                 0x0020  /**< Sensor result higher than the device can process */
#define BLE_GLS_MEAS_STATUS_RESULT_LOW                  0x0040  /**< Sensor result lower than the device can process */
#define BLE_GLS_MEAS_STATUS_TEMP_HIGH                   0x0080  /**< Sensor temperature too high for valid test/result at time of measurement */
#define BLE_GLS_MEAS_STATUS_TEMP_LOW                    0x0100  /**< Sensor temperature too low for valid test/result at time of measurement */
#define BLE_GLS_MEAS_STATUS_STRIP_PULL                  0x0200  /**< Sensor read interrupted because strip was pulled too soon at time of measurement */
#define BLE_GLS_MEAS_STATUS_GENERAL_FAULT               0x0400  /**< General device fault has occurred in the sensor */
#define BLE_GLS_MEAS_STATUS_TIME_FAULT                  0x0800  /**< Time fault has occurred in the sensor and time may be inaccurate */

/**@brief Glucose measurement context flags */
#define BLE_GLS_CONTEXT_FLAG_CARB                       0x01    /**< Carbohydrate id and carbohydrate present */
#define BLE_GLS_CONTEXT_FLAG_MEAL                       0x02    /**< Meal present */
#define BLE_GLS_CONTEXT_FLAG_TESTER                     0x04    /**< Tester-health present */
#define BLE_GLS_CONTEXT_FLAG_EXERCISE                   0x08    /**< Exercise duration and exercise intensity present */
#define BLE_GLS_CONTEXT_FLAG_MED                        0x10    /**< Medication ID and medication present */
#define BLE_GLS_CONTEXT_FLAG_MED_KG                     0x00    /**< Medication value units, kilograms */
#define BLE_GLS_CONTEXT_FLAG_MED_L                      0x20    /**< Medication value units, liters */
#define BLE_GLS_CONTEXT_FLAG_HBA1C                      0x40    /**< Hba1c present */
#define BLE_GLS_CONTEXT_FLAG_EXT                        0x80    /**< Extended flags present */

/**@brief Glucose measurement context carbohydrate ID */
#define BLE_GLS_CONTEXT_CARB_BREAKFAST                  1       /**< Breakfast */
#define BLE_GLS_CONTEXT_CARB_LUNCH                      2       /**< Lunch */
#define BLE_GLS_CONTEXT_CARB_DINNER                     3       /**< Dinner */
#define BLE_GLS_CONTEXT_CARB_SNACK                      4       /**< Snack */
#define BLE_GLS_CONTEXT_CARB_DRINK                      5       /**< Drink */
#define BLE_GLS_CONTEXT_CARB_SUPPER                     6       /**< Supper */
#define BLE_GLS_CONTEXT_CARB_BRUNCH                     7       /**< Brunch */

/**@brief Glucose measurement context meal */
#define BLE_GLS_CONTEXT_MEAL_PREPRANDIAL                1       /**< Preprandial (before meal) */
#define BLE_GLS_CONTEXT_MEAL_POSTPRANDIAL               2       /**< Postprandial (after meal) */
#define BLE_GLS_CONTEXT_MEAL_FASTING                    3       /**< Fasting */
#define BLE_GLS_CONTEXT_MEAL_CASUAL                     4       /**< Casual (snacks, drinks, etc.) */
#define BLE_GLS_CONTEXT_MEAL_BEDTIME                    5       /**< Bedtime */

/**@brief Glucose measurement context tester */
#define BLE_GLS_CONTEXT_TESTER_SELF                     1       /**< Self */
#define BLE_GLS_CONTEXT_TESTER_PRO                      2       /**< Health care professional */
#define BLE_GLS_CONTEXT_TESTER_LAB                      3       /**< Lab test */
#define BLE_GLS_CONTEXT_TESTER_NOT_AVAIL                15      /**< Tester value not available */

/**@brief Glucose measurement context health */
#define BLE_GLS_CONTEXT_HEALTH_MINOR                    1       /**< Minor health issues */
#define BLE_GLS_CONTEXT_HEALTH_MAJOR                    2       /**< Major health issues */
#define BLE_GLS_CONTEXT_HEALTH_MENSES                   3       /**< During menses */
#define BLE_GLS_CONTEXT_HEALTH_STRESS                   4       /**< Under stress */
#define BLE_GLS_CONTEXT_HEALTH_NONE                     5       /**< No health issues */
#define BLE_GLS_CONTEXT_HEALTH_NOT_AVAIL                15      /**< Health value not available */

/**@brief Glucose measurement context medication ID */
#define BLE_GLS_CONTEXT_MED_RAPID                       1       /**< Rapid acting insulin */
#define BLE_GLS_CONTEXT_MED_SHORT                       2       /**< Short acting insulin */
#define BLE_GLS_CONTEXT_MED_INTERMED                    3       /**< Intermediate acting insulin */
#define BLE_GLS_CONTEXT_MED_LONG                        4       /**< Long acting insulin */
#define BLE_GLS_CONTEXT_MED_PREMIX                      5       /**< Pre-mixed insulin */


/**@brief SFLOAT format (IEEE-11073 16-bit FLOAT, meaning 4 bits for exponent (base 10) and 12 bits mantissa) */
typedef struct
{
  int8_t exponent;                                             /**< Base 10 exponent, should be using only 4 bits */
  int16_t mantissa;                                            /**< Mantissa, should be using only 12 bits */
} sfloat_t;

/**@brief Glucose Service event type. */
typedef enum
{
    BLE_GLS_EVT_NOTIFICATION_ENABLED,                          /**< Glucose value notification enabled event. */
    BLE_GLS_EVT_NOTIFICATION_DISABLED                          /**< Glucose value notification disabled event. */
} ble_gls_evt_type_t;

/**@brief Glucose Service event. */
typedef struct
{
    ble_gls_evt_type_t evt_type;                               /**< Type of event. */
} ble_gls_evt_t;

// Forward declaration of the ble_gls_t type.
typedef struct ble_gls_s ble_gls_t;

/**@brief Glucose Service event handler type. */
typedef void (*ble_gls_evt_handler_t) (ble_gls_t * p_gls, ble_gls_evt_t * p_evt);

/**@brief Glucose Measurement structure. This contains glucose measurement value. */
typedef struct
{
    uint8_t         flags;                                     /**< Flags */
    uint16_t        sequence_number;                           /**< Sequence number */
    ble_date_time_t base_time;                                 /**< Time stamp */
    int16_t         time_offset;                               /**< Time offset */
    sfloat_t        glucose_concentration;                     /**< Glucose concentration */
    uint8_t         type;                                      /**< Type */
    uint8_t         sample_location;                           /**< Sample location */
    uint16_t        sensor_status_annunciation;                /**< Sensor status annunciation */
} ble_gls_meas_t;

/**@brief Glucose measurement context structure */
typedef struct
{
    uint8_t       flags;                                       /**< Flags */
    uint8_t       extended_flags;                              /**< Extended Flags */
    uint8_t       carbohydrate_id;                             /**< Carbohydrate ID */
    sfloat_t      carbohydrate;                                /**< Carbohydrate */
    uint8_t       meal;                                        /**< Meal */
    uint8_t       tester_and_health;                           /**< Tester and health */
    uint16_t      exercise_duration;                           /**< Exercise Duration */
    uint8_t       exercise_intensity;                          /**< Exercise Intensity */
    uint8_t       medication_id;                               /**< Medication ID */
    sfloat_t      medication;                                  /**< Medication */
    uint16_t      hba1c;                                       /**< HbA1c */
} ble_gls_meas_context_t;

/**@brief Glucose measurement record */
typedef struct
{
    ble_gls_meas_t          meas;                              /**< Glucose measurement */
    ble_gls_meas_context_t  context;                           /**< Glucose measurement context */
} ble_gls_rec_t;

/**@brief Glucose Service init structure. This contains all options and data needed for
 *        initialization of the service. */
typedef struct
{
    ble_gls_evt_handler_t     evt_handler;                     /**< Event handler to be called for handling events in the Glucose Service. */
    ble_srv_error_handler_t   error_handler;                   /**< Function to be called in case of an error. */
    uint16_t                  feature;                         /**< Glucose Feature value indicating supported features. */
    bool                      is_context_supported;            /**< Determines if optional Glucose Measurement Context is to be supported. */
    security_req_t            gl_meas_cccd_wr_sec;             /**< Security requirement for writing glucose measurement characteristic CCCD. */
    security_req_t            gl_feature_rd_sec;               /**< Security requirement for reading glucose feature characteristic. */
    security_req_t            racp_cccd_wr_sec;                /**< Security requirement for writing RACP Characteristic CCCD. */
    security_req_t            racp_wr_sec;                     /**< Security requirement for writing RACP Characteristic. (Service specification mandates authentication) */
} ble_gls_init_t;

/**@brief Glucose Service structure. This contains various status information for the service. */
struct ble_gls_s
{
    ble_gls_evt_handler_t     evt_handler;                     /**< Event handler to be called for handling events in the Glucose Service. */
    ble_srv_error_handler_t   error_handler;                   /**< Function to be called in case of an error. */
    uint16_t                  service_handle;                  /**< Handle of Glucose Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t  glm_handles;                     /**< Handles related to the Glucose Measurement characteristic. */
    ble_gatts_char_handles_t  glm_context_handles;             /**< Handles related to the Glucose Measurement Context characteristic. */
    ble_gatts_char_handles_t  glf_handles;                     /**< Handles related to the Glucose Feature characteristic. */
    ble_gatts_char_handles_t  racp_handles;                    /**< Handles related to the Record Access Control Point characteristic. */
    uint16_t                  conn_handle;                     /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint16_t                  feature;
    bool                      is_context_supported;
};


/**@brief Function for initializing the Glucose Service.
 *
 * @details This call allows the application to initialize the Glucose Service.
 *
 * @param[out]  p_gls       Glucose Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_gls_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_gls_init(ble_gls_t * p_gls, ble_gls_init_t const * p_gls_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Glucose Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Glucose Service structure.
 */
void ble_gls_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for reporting a new glucose measurement to the glucose service module.
 *
 * @details The application calls this function after having performed a new glucose measurement.
 *          The new measurement is recorded in the RACP database.
 *
 * @param[in]   p_gls                    Glucose Service structure.
 * @param[in]   p_rec                    Pointer to glucose record (measurement plus context).
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_gls_glucose_new_meas(ble_gls_t * p_gls, ble_gls_rec_t * p_rec);


#ifdef __cplusplus
}
#endif

#endif // BLE_GLS_H__

/** @} */

