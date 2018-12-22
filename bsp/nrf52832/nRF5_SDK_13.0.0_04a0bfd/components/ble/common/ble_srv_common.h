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
 * @defgroup ble_sdk_srv_common Common service definitions
 * @{
 * @ingroup ble_sdk_srv
 * @brief Constants, type definitions, and functions that are common to all services.
 */

#ifndef BLE_SRV_COMMON_H__
#define BLE_SRV_COMMON_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble_types.h"
#include "app_util.h"
#include "ble.h"
#include "ble_gap.h"
#include "ble_gatt.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup UUID_SERVICES Service UUID definitions
 * @{ */
#define BLE_UUID_ALERT_NOTIFICATION_SERVICE                      0x1811     /**< Alert Notification service UUID. */
#define BLE_UUID_BATTERY_SERVICE                                 0x180F     /**< Battery service UUID. */
#define BLE_UUID_BLOOD_PRESSURE_SERVICE                          0x1810     /**< Blood Pressure service UUID. */
#define BLE_UUID_CURRENT_TIME_SERVICE                            0x1805     /**< Current Time service UUID. */
#define BLE_UUID_CYCLING_SPEED_AND_CADENCE                       0x1816     /**< Cycling Speed and Cadence service UUID. */
#define BLE_UUID_LOCATION_AND_NAVIGATION_SERVICE                 0x1819     /**< Location and Navigation service UUID. */
#define BLE_UUID_DEVICE_INFORMATION_SERVICE                      0x180A     /**< Device Information service UUID. */
#define BLE_UUID_GLUCOSE_SERVICE                                 0x1808     /**< Glucose service UUID. */
#define BLE_UUID_HEALTH_THERMOMETER_SERVICE                      0x1809     /**< Health Thermometer service UUID. */
#define BLE_UUID_HEART_RATE_SERVICE                              0x180D     /**< Heart Rate service UUID. */
#define BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE                  0x1812     /**< Human Interface Device service UUID. */
#define BLE_UUID_IMMEDIATE_ALERT_SERVICE                         0x1802     /**< Immediate Alert service UUID. */
#define BLE_UUID_LINK_LOSS_SERVICE                               0x1803     /**< Link Loss service UUID. */
#define BLE_UUID_NEXT_DST_CHANGE_SERVICE                         0x1807     /**< Next Dst Change service UUID. */
#define BLE_UUID_PHONE_ALERT_STATUS_SERVICE                      0x180E     /**< Phone Alert Status service UUID. */
#define BLE_UUID_REFERENCE_TIME_UPDATE_SERVICE                   0x1806     /**< Reference Time Update service UUID. */
#define BLE_UUID_RUNNING_SPEED_AND_CADENCE                       0x1814     /**< Running Speed and Cadence service UUID. */
#define BLE_UUID_SCAN_PARAMETERS_SERVICE                         0x1813     /**< Scan Parameters service UUID. */
#define BLE_UUID_TX_POWER_SERVICE                                0x1804     /**< TX Power service UUID. */
#define BLE_UUID_IPSP_SERVICE                                    0x1820     /**< Internet Protocol Support service UUID. */
#define BLE_UUID_BMS_SERVICE                                     0x181E     /**< BOND MANAGEMENT service UUID*/
#define BLE_UUID_CGM_SERVICE                                     0x181F     /**< Continuous Glucose Monitoring service UUID*/
#define BLE_UUID_PLX_SERVICE                                     0x1822     /**< Pulse Oximeter Service UUID*/


/** @} */

/** @defgroup UUID_CHARACTERISTICS Characteristic UUID definitions
 * @{ */
#define BLE_UUID_REMOVABLE_CHAR                                  0x2A3A     /**< Removable characteristic UUID. */
#define BLE_UUID_SERVICE_REQUIRED_CHAR                           0x2A3B     /**< Service Required characteristic UUID. */
#define BLE_UUID_ALERT_CATEGORY_ID_CHAR                          0x2A43     /**< Alert Category Id characteristic UUID. */
#define BLE_UUID_ALERT_CATEGORY_ID_BIT_MASK_CHAR                 0x2A42     /**< Alert Category Id Bit Mask characteristic UUID. */
#define BLE_UUID_ALERT_LEVEL_CHAR                                0x2A06     /**< Alert Level characteristic UUID. */
#define BLE_UUID_ALERT_NOTIFICATION_CONTROL_POINT_CHAR           0x2A44     /**< Alert Notification Control Point characteristic UUID. */
#define BLE_UUID_ALERT_STATUS_CHAR                               0x2A3F     /**< Alert Status characteristic UUID. */
#define BLE_UUID_BATTERY_LEVEL_CHAR                              0x2A19     /**< Battery Level characteristic UUID. */
#define BLE_UUID_BLOOD_PRESSURE_FEATURE_CHAR                     0x2A49     /**< Blood Pressure Feature characteristic UUID. */
#define BLE_UUID_BLOOD_PRESSURE_MEASUREMENT_CHAR                 0x2A35     /**< Blood Pressure Measurement characteristic UUID. */
#define BLE_UUID_BODY_SENSOR_LOCATION_CHAR                       0x2A38     /**< Body Sensor Location characteristic UUID. */
#define BLE_UUID_BOOT_KEYBOARD_INPUT_REPORT_CHAR                 0x2A22     /**< Boot Keyboard Input Report characteristic UUID. */
#define BLE_UUID_BOOT_KEYBOARD_OUTPUT_REPORT_CHAR                0x2A32     /**< Boot Keyboard Output Report characteristic UUID. */
#define BLE_UUID_BOOT_MOUSE_INPUT_REPORT_CHAR                    0x2A33     /**< Boot Mouse Input Report characteristic UUID. */
#define BLE_UUID_CURRENT_TIME_CHAR                               0x2A2B     /**< Current Time characteristic UUID. */
#define BLE_UUID_DATE_TIME_CHAR                                  0x2A08     /**< Date Time characteristic UUID. */
#define BLE_UUID_DAY_DATE_TIME_CHAR                              0x2A0A     /**< Day Date Time characteristic UUID. */
#define BLE_UUID_DAY_OF_WEEK_CHAR                                0x2A09     /**< Day Of Week characteristic UUID. */
#define BLE_UUID_DST_OFFSET_CHAR                                 0x2A0D     /**< Dst Offset characteristic UUID. */
#define BLE_UUID_EXACT_TIME_256_CHAR                             0x2A0C     /**< Exact Time 256 characteristic UUID. */
#define BLE_UUID_FIRMWARE_REVISION_STRING_CHAR                   0x2A26     /**< Firmware Revision String characteristic UUID. */
#define BLE_UUID_GLUCOSE_FEATURE_CHAR                            0x2A51     /**< Glucose Feature characteristic UUID. */
#define BLE_UUID_GLUCOSE_MEASUREMENT_CHAR                        0x2A18     /**< Glucose Measurement characteristic UUID. */
#define BLE_UUID_GLUCOSE_MEASUREMENT_CONTEXT_CHAR                0x2A34     /**< Glucose Measurement Context characteristic UUID. */
#define BLE_UUID_HARDWARE_REVISION_STRING_CHAR                   0x2A27     /**< Hardware Revision String characteristic UUID. */
#define BLE_UUID_HEART_RATE_CONTROL_POINT_CHAR                   0x2A39     /**< Heart Rate Control Point characteristic UUID. */
#define BLE_UUID_HEART_RATE_MEASUREMENT_CHAR                     0x2A37     /**< Heart Rate Measurement characteristic UUID. */
#define BLE_UUID_HID_CONTROL_POINT_CHAR                          0x2A4C     /**< Hid Control Point characteristic UUID. */
#define BLE_UUID_HID_INFORMATION_CHAR                            0x2A4A     /**< Hid Information characteristic UUID. */
#define BLE_UUID_IEEE_REGULATORY_CERTIFICATION_DATA_LIST_CHAR    0x2A2A     /**< IEEE Regulatory Certification Data List characteristic UUID. */
#define BLE_UUID_INTERMEDIATE_CUFF_PRESSURE_CHAR                 0x2A36     /**< Intermediate Cuff Pressure characteristic UUID. */
#define BLE_UUID_INTERMEDIATE_TEMPERATURE_CHAR                   0x2A1E     /**< Intermediate Temperature characteristic UUID. */
#define BLE_UUID_LOCAL_TIME_INFORMATION_CHAR                     0x2A0F     /**< Local Time Information characteristic UUID. */
#define BLE_UUID_MANUFACTURER_NAME_STRING_CHAR                   0x2A29     /**< Manufacturer Name String characteristic UUID. */
#define BLE_UUID_MEASUREMENT_INTERVAL_CHAR                       0x2A21     /**< Measurement Interval characteristic UUID. */
#define BLE_UUID_MODEL_NUMBER_STRING_CHAR                        0x2A24     /**< Model Number String characteristic UUID. */
#define BLE_UUID_UNREAD_ALERT_CHAR                               0x2A45     /**< Unread Alert characteristic UUID. */
#define BLE_UUID_NEW_ALERT_CHAR                                  0x2A46     /**< New Alert characteristic UUID. */
#define BLE_UUID_PNP_ID_CHAR                                     0x2A50     /**< PNP Id characteristic UUID. */
#define BLE_UUID_PROTOCOL_MODE_CHAR                              0x2A4E     /**< Protocol Mode characteristic UUID. */
#define BLE_UUID_RECORD_ACCESS_CONTROL_POINT_CHAR                0x2A52     /**< Record Access Control Point characteristic UUID. */
#define BLE_UUID_REFERENCE_TIME_INFORMATION_CHAR                 0x2A14     /**< Reference Time Information characteristic UUID. */
#define BLE_UUID_REPORT_CHAR                                     0x2A4D     /**< Report characteristic UUID. */
#define BLE_UUID_REPORT_MAP_CHAR                                 0x2A4B     /**< Report Map characteristic UUID. */
#define BLE_UUID_RINGER_CONTROL_POINT_CHAR                       0x2A40     /**< Ringer Control Point characteristic UUID. */
#define BLE_UUID_RINGER_SETTING_CHAR                             0x2A41     /**< Ringer Setting characteristic UUID. */
#define BLE_UUID_SCAN_INTERVAL_WINDOW_CHAR                       0x2A4F     /**< Scan Interval Window characteristic UUID. */
#define BLE_UUID_SCAN_REFRESH_CHAR                               0x2A31     /**< Scan Refresh characteristic UUID. */
#define BLE_UUID_SERIAL_NUMBER_STRING_CHAR                       0x2A25     /**< Serial Number String characteristic UUID. */
#define BLE_UUID_SOFTWARE_REVISION_STRING_CHAR                   0x2A28     /**< Software Revision String characteristic UUID. */
#define BLE_UUID_SUPPORTED_NEW_ALERT_CATEGORY_CHAR               0x2A47     /**< Supported New Alert Category characteristic UUID. */
#define BLE_UUID_SUPPORTED_UNREAD_ALERT_CATEGORY_CHAR            0x2A48     /**< Supported Unread Alert Category characteristic UUID. */
#define BLE_UUID_SYSTEM_ID_CHAR                                  0x2A23     /**< System Id characteristic UUID. */
#define BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR                    0x2A1C     /**< Temperature Measurement characteristic UUID. */
#define BLE_UUID_TEMPERATURE_TYPE_CHAR                           0x2A1D     /**< Temperature Type characteristic UUID. */
#define BLE_UUID_TIME_ACCURACY_CHAR                              0x2A12     /**< Time Accuracy characteristic UUID. */
#define BLE_UUID_TIME_SOURCE_CHAR                                0x2A13     /**< Time Source characteristic UUID. */
#define BLE_UUID_TIME_UPDATE_CONTROL_POINT_CHAR                  0x2A16     /**< Time Update Control Point characteristic UUID. */
#define BLE_UUID_TIME_UPDATE_STATE_CHAR                          0x2A17     /**< Time Update State characteristic UUID. */
#define BLE_UUID_TIME_WITH_DST_CHAR                              0x2A11     /**< Time With Dst characteristic UUID. */
#define BLE_UUID_TIME_ZONE_CHAR                                  0x2A0E     /**< Time Zone characteristic UUID. */
#define BLE_UUID_TX_POWER_LEVEL_CHAR                             0x2A07     /**< TX Power Level characteristic UUID. */
#define BLE_UUID_CSC_FEATURE_CHAR                                0x2A5C     /**< Cycling Speed and Cadence Feature characteristic UUID. */
#define BLE_UUID_CSC_MEASUREMENT_CHAR                            0x2A5B     /**< Cycling Speed and Cadence Measurement characteristic UUID. */
#define BLE_UUID_RSC_FEATURE_CHAR                                0x2A54     /**< Running Speed and Cadence Feature characteristic UUID. */
#define BLE_UUID_SC_CTRLPT_CHAR                                  0x2A55     /**< Speed and Cadence Control Point UUID. */
#define BLE_UUID_RSC_MEASUREMENT_CHAR                            0x2A53     /**< Running Speed and Cadence Measurement characteristic UUID. */
#define BLE_UUID_SENSOR_LOCATION_CHAR                            0x2A5D     /**< Sensor Location characteristic UUID. */
#define BLE_UUID_EXTERNAL_REPORT_REF_DESCR                       0x2907     /**< External Report Reference descriptor UUID. */
#define BLE_UUID_REPORT_REF_DESCR                                0x2908     /**< Report Reference descriptor UUID. */
#define BLE_UUID_LN_FEATURE_CHAR                                 0x2A6A     /**< Location Navigation Service, Feature characteristic UUID. */
#define BLE_UUID_LN_POSITION_QUALITY_CHAR                        0x2A69     /**< Location Navigation Service, Position quality UUID. */
#define BLE_UUID_LN_LOCATION_AND_SPEED_CHAR                      0x2A67     /**< Location Navigation Service, Location and Speed characteristic UUID. */
#define BLE_UUID_LN_NAVIGATION_CHAR                              0x2A68     /**< Location Navigation Service, Navigation characteristic UUID. */
#define BLE_UUID_LN_CONTROL_POINT_CHAR                           0x2A6B     /**< Location Navigation Service, Control point characteristic UUID. */
#define BLE_UUID_BMS_CTRLPT                                      0x2AA4     /**< BMS Control Point characteristic UUID. */
#define BLE_UUID_BMS_FEATURE                                     0x2AA5     /**< BMS Feature characteristic UUID. */
#define BLE_UUID_CGM_MEASUREMENT                                 0x2AA7     /**< CGM Service, Measurement characteristic UUID*/
#define BLE_UUID_CGM_FEATURE                                     0x2AA8     /**< CGM Service, Feature characteristic UUID*/
#define BLE_UUID_CGM_STATUS                                      0x2AA9     /**< CGM Service, Status characteristic UUID*/
#define BLE_UUID_CGM_SESSION_START_TIME                          0x2AAA     /**< CGM Service, session start time characteristic UUID*/
#define BLE_UUID_CGM_SESSION_RUN_TIME                            0x2AAB     /**< CGM Service, session run time characteristic UUID*/
#define BLE_UUID_CGM_SPECIFIC_OPS_CTRLPT                         0x2AAC     /**< CGM Service, specific ops ctrlpt characteristic UUID*/
#define BLE_UUID_PLX_SPOT_CHECK_MEAS                             0x2A5E     /**< PLX Service, spot check measurement characteristic UUID*/
#define BLE_UUID_PLX_CONTINUOUS_MEAS                             0x2A5F     /**< PLX Service, continuous measurement characteristic UUID*/
#define BLE_UUID_PLX_FEATURES                                    0x2A60     /**< PLX Service, feature characteristic UUID*/





/** @} */

/** @defgroup ALERT_LEVEL_VALUES Definitions for the Alert Level characteristic values
 * @{ */
#define BLE_CHAR_ALERT_LEVEL_NO_ALERT                            0x00       /**< No Alert. */
#define BLE_CHAR_ALERT_LEVEL_MILD_ALERT                          0x01       /**< Mild Alert. */
#define BLE_CHAR_ALERT_LEVEL_HIGH_ALERT                          0x02       /**< High Alert. */
/** @} */

#define BLE_SRV_ENCODED_REPORT_REF_LEN                           2          /**< The length of an encoded Report Reference Descriptor. */
#define BLE_CCCD_VALUE_LEN                                       2          /**< The length of a CCCD value. */

/**@brief Type definition for error handler function that will be called in case of an error in
 *        a service or a service library module. */
typedef void (*ble_srv_error_handler_t) (uint32_t nrf_error);



/**@brief Value of a Report Reference descriptor.
 *
 * @details This is mapping information that maps the parent characteristic to the Report ID(s) and
 *          Report Type(s) defined within a Report Map characteristic.
 */
typedef struct
{
    uint8_t report_id;                                  /**< Non-zero value if there is more than one instance of the same Report Type */
    uint8_t report_type;                                /**< Type of Report characteristic (see @ref BLE_HIDS_REPORT_TYPE) */
} ble_srv_report_ref_t;

/**@brief UTF-8 string data type.
 *
 * @note The type can only hold a pointer to the string data (i.e. not the actual data).
 */
typedef struct
{
    uint16_t  length;                                   /**< String length. */
    uint8_t * p_str;                                    /**< String data. */
} ble_srv_utf8_str_t;


/**@brief Security settings structure.
 * @details This structure contains the security options needed during initialization of the
 *          service.
 */
typedef struct
{
    ble_gap_conn_sec_mode_t read_perm;                  /**< Read permissions. */
    ble_gap_conn_sec_mode_t write_perm;                 /**< Write permissions. */
} ble_srv_security_mode_t;

/**@brief Security settings structure.
 * @details This structure contains the security options needed during initialization of the
 *          service. It can be used when the characteristics contains a CCCD.
 */
typedef struct
{
    ble_gap_conn_sec_mode_t cccd_write_perm;            /**< Write permissions for Client Characteristic Configuration Descriptor. */
    ble_gap_conn_sec_mode_t read_perm;                  /**< Read permissions. */
    ble_gap_conn_sec_mode_t write_perm;                 /**< Write permissions. */
} ble_srv_cccd_security_mode_t;

/**@brief Function for decoding a CCCD value, and then testing if notification is
 *        enabled.
 *
 * @param[in]   p_encoded_data   Buffer where the encoded CCCD is stored.
 *
 * @retval      TRUE If notification is enabled.
 * @retval      FALSE Otherwise.
 */
bool ble_srv_is_notification_enabled(uint8_t const * p_encoded_data);


/**@brief Function for decoding a CCCD value, and then testing if indication is
 *        enabled.
 *
 * @param[in]   p_encoded_data   Buffer where the encoded CCCD is stored.
 *
 * @retval      TRUE If indication is enabled.
 * @retval      FALSE Otherwise.
 */
bool ble_srv_is_indication_enabled(uint8_t const * p_encoded_data);


/**@brief Function for encoding a Report Reference Descriptor.
 *
 * @param[in]   p_encoded_buffer  The buffer of the encoded data.
 * @param[in]   p_report_ref      Report Reference value to be encoded.
 *
 * @return      Length of the encoded data.
 */
uint8_t ble_srv_report_ref_encode(uint8_t *                    p_encoded_buffer,
                                  const ble_srv_report_ref_t * p_report_ref);

/**@brief Function for making a UTF-8 structure refer to an ASCII string.
 *
 * @param[out]  p_utf8   UTF-8 structure to be set.
 * @param[in]   p_ascii  ASCII string to be referred to.
 */
void ble_srv_ascii_to_utf8(ble_srv_utf8_str_t * p_utf8, char * p_ascii);


/**@brief Security Access enumeration.
 * @details This enumeration gives the possible requirements for accessing a characteristic value.
 */
typedef enum
{
    SEC_NO_ACCESS    = 0,            /**< Not possible to access. */
    SEC_OPEN         = 1,            /**< Access open. */
    SEC_JUST_WORKS   = 2,            /**< Access possible with 'Just Works' security at least. */
    SEC_MITM         = 3,            /**< Access possible with 'MITM' security at least. */
    SEC_SIGNED       = 4,            /**< Access possible with 'signed' security at least. */
    SEC_SIGNED_MITM  = 5             /**< Access possible with 'signed and MITM' security at least. */
}security_req_t;


/**@brief Characteristic User Descriptor parameters.
 * @details This structure contains the parameters for User Descriptor.
 */
typedef struct
{
    uint16_t               max_size;                      /**< Maximum size of the user descriptor*/
    uint16_t               size;                          /**< Size of the user descriptor*/
    uint8_t                *p_char_user_desc;             /**< User descriptor content, pointer to a UTF-8 encoded string (non-NULL terminated)*/
    bool                   is_var_len;                    /**< Indicates if the user descriptor has variable length.*/
    ble_gatt_char_props_t  char_props;                    /**< user descriptor properties.*/
    bool                   is_defered_read;               /**< Indicate if deferred read operations are supported.*/
    bool                   is_defered_write;              /**< Indicate if deferred write operations are supported.*/
    security_req_t         read_access;                   /**< Security requirement for reading the user descriptor.*/
    security_req_t         write_access;                  /**< Security requirement for writing the user descriptor.*/
    bool                   is_value_user;                 /**< Indicate if the content of the characteristic is to be stored in the application (user) or in the stack.*/
}ble_add_char_user_desc_t;


/**@brief Add characteristic parameters structure.
 * @details This structure contains the parameters needed to use the @ref characteristic_add function.
 */
typedef struct
{
    uint16_t                    uuid;                     /**< Characteristic UUID (16 bits UUIDs).*/
    uint8_t                     uuid_type;                /**< Base UUID. If 0, the Bluetooth SIG UUID will be used. Otherwise, this should be a value returned by @ref sd_ble_uuid_vs_add when adding the base UUID.*/
    uint16_t                    max_len;                  /**< Maximum length of the characteristic value.*/
    uint16_t                    init_len;                 /**< Initial length of the characteristic value.*/
    uint8_t *                   p_init_value;             /**< Initial encoded value of the characteristic.*/
    bool                        is_var_len;               /**< Indicates if the characteristic value has variable length.*/
    ble_gatt_char_props_t       char_props;               /**< Characteristic properties.*/
    ble_gatt_char_ext_props_t   char_ext_props;           /**< Characteristic extended properties.*/
    bool                        is_defered_read;          /**< Indicate if deferred read operations are supported.*/
    bool                        is_defered_write;         /**< Indicate if deferred write operations are supported.*/
    security_req_t              read_access;              /**< Security requirement for reading the characteristic value.*/
    security_req_t              write_access;             /**< Security requirement for writing the characteristic value.*/
    security_req_t              cccd_write_access;        /**< Security requirement for writing the characteristic's CCCD.*/
    bool                        is_value_user;            /**< Indicate if the content of the characteristic is to be stored in the application (user) or in the stack.*/
    ble_add_char_user_desc_t    *p_user_descr;            /**< Pointer to user descriptor if needed*/
    ble_gatts_char_pf_t         *p_presentation_format;   /**< Pointer to characteristic format if needed*/
} ble_add_char_params_t;


/**@brief Add descriptor parameters structure.
 * @details This structure contains the parameters needed to use the @ref descriptor_add function.
 */
typedef struct
{
    uint16_t       uuid;                     /**< descriptor UUID (16 bits UUIDs).*/
    uint8_t        uuid_type;                /**< Base UUID. If 0, the Bluetooth SIG UUID will be used. Otherwise, this should be a value returned by @ref sd_ble_uuid_vs_add when adding the base UUID.*/
    bool           is_defered_read;          /**< Indicate if deferred read operations are supported.*/
    bool           is_defered_write;         /**< Indicate if deferred write operations are supported.*/
    bool           is_var_len;               /**< Indicates if the descriptor value has variable length.*/
    security_req_t read_access;              /**< Security requirement for reading the descriptor value.*/
    security_req_t write_access;             /**< Security requirement for writing the descriptor value.*/
    bool           is_value_user;            /**< Indicate if the content of the characteristic is to be stored in the application (user) or in the stack.*/
    uint16_t       init_len;                 /**< Initial descriptor value length in bytes. */
    uint16_t       init_offs;                /**< Initial descriptor value offset in bytes. If different from zero, the first init_offs bytes of the attribute value will be left uninitialized. */
    uint16_t       max_len;                  /**< Maximum descriptor value length in bytes, see @ref BLE_GATTS_ATTR_LENS_MAX for maximum values. */
    uint8_t*       p_value;                  /**< Pointer to the value of the descriptor*/
} ble_add_descr_params_t;


/**@brief Function for adding a characteristic to a given service.
 *
 * If no pointer is given for the initial value,
 * the initial length parameter will be ignored and the initial length will be 0.
 *
 * @param[in]  service_handle Handle of the service to which the characteristic is to be added.
 * @param[in]  p_char_props   Information needed to add the characteristic.
 * @param[out] p_char_handle  Handle of the added characteristic.
 *
 * @retval      NRF_SUCCESS If the characteristic was added successfully. Otherwise, an error code is returned.
 */
uint32_t characteristic_add(uint16_t                   service_handle,
                            ble_add_char_params_t *    p_char_props,
                            ble_gatts_char_handles_t * p_char_handle);


/**@brief Function for adding a characteristic's descriptor to a given characteristic.
 *
 * @param[in]  char_handle    Handle of the characteristic to which the descriptor is to be added, if @ref BLE_GATT_HANDLE_INVALID is used, it will be placed sequentially.
 * @param[in]  p_descr_props  Information needed to add the descriptor.
 * @param[out] p_descr_handle Handle of the added descriptor.
 *
 * @retval      NRF_SUCCESS If the characteristic was added successfully. Otherwise, an error code is returned.
 */
uint32_t descriptor_add(uint16_t                   char_handle,
                        ble_add_descr_params_t *   p_descr_props,
                        uint16_t *                 p_descr_handle);



#ifdef __cplusplus
}
#endif

#endif // BLE_SRV_COMMON_H__

/** @} */
