/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
/**@file lwm2m_objects.h
 *
 * @defgroup iot_sdk_lwm2m_objects OMA LWM2M objects definitions and types
 * @ingroup iot_sdk_lwm2m
 * @{
 * @brief OMA LWM2M objects definitions and types.
 *
 * @note The definitions used in this module are from the OMA LWM2M
 *       "Lightweight Machine to Machine Technical Specification - OMA_TS-LightweightM2M-V1_0-20131210-C".
 *       The specification could be found at http://openmobilealliance.org/.
 */

#ifndef LWM2M_OBJECTS_H__
#define LWM2M_OBJECTS_H__

#include <stdint.h>
#include <stdbool.h>
#include "lwm2m_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/* @brief LWM2M Enabler Object IDs Appendix E  */
#define LWM2M_OBJ_SECURITY                                0
#define LWM2M_OBJ_SERVER                                  1
#define LWM2M_OBJ_ACL                                     2
#define LWM2M_OBJ_DEVICE                                  3
#define LWM2M_OBJ_CONN_MON                                4
#define LWM2M_OBJ_FIRMWARE                                5
#define LWM2M_OBJ_LOCATION                                6
#define LWM2M_OBJ_CONN_STAT                               7

/* @brief LWM2M Registry Objects */
#define LWM2M_OBJ_SOFTWARE_UPDATE                         9

/* LWM2M Security Resource IDs Appendix E.1 */
#define LWM2M_SECURITY_SERVER_URI                         0
#define LWM2M_SECURITY_BOOTSTRAP_SERVER                   1
#define LWM2M_SECURITY_SECURITY_MODE                      2
#define LWM2M_SECURITY_PUBLIC_KEY                         3
#define LWM2M_SECURITY_SERVER_PUBLIC_KEY                  4
#define LWM2M_SECURITY_SECRET_KEY                         5
#define LWM2M_SECURITY_SMS_SECURITY_MODE                  6
#define LWM2M_SECURITY_SMS_BINDING_KEY_PARAM              7
#define LWM2M_SECURITY_SMS_BINDING_SECRET_KEY             8
#define LWM2M_SECURITY_SERVER_SMS_NUMBER                  9
#define LWM2M_SECURITY_SHORT_SERVER_ID                    10
#define LWM2M_SECURITY_CLIENT_HOLD_OFF_TIME               11


/* LWM2M Server Resources Appendix E.2 */
#define LWM2M_SERVER_SHORT_SERVER_ID                      0
#define LWM2M_SERVER_LIFETIME                             1
#define LWM2M_SERVER_DEFAULT_MIN_PERIOD                   2
#define LWM2M_SERVER_DEFAULT_MAX_PERIOD                   3
#define LWM2M_SERVER_DISABLE                              4
#define LWM2M_SERVER_DISABLE_TIMEOUT                      5
#define LWM2M_SERVER_NOTIFY_WHEN_DISABLED                 6
#define LWM2M_SERVER_BINDING                              7
#define LWM2M_SERVER_REGISTRATION_UPDATE_TRIGGER          8


/* LWM2M Firmware update Resources Appendix E.6 */
#define LWM2M_FIRMWARE_PACKAGE                            0
#define LWM2M_FIRMWARE_PACKAGE_URI                        1
#define LWM2M_FIRMWARE_UPDATE                             2
#define LWM2M_FIRMWARE_STATE                              3
#define LWM2M_FIRMWARE_UPDATE_SUPPORTED_OBJECTS           4
#define LWM2M_FIRMWARE_UPDATE_RESULT                      5

#define LWM2M_FIRMWARE_STATE_IDLE                         1
#define LWM2M_FIRMWARE_STATE_DOWNLOADING                  2
#define LWM2M_FIRMWARE_STATE_DOWNLOADED                   3

#define LWM2M_FIRMWARE_UPDATE_RESULT_DEFAULT              0
#define LWM2M_FIRMWARE_UPDATE_RESULT_SUCCESS              1
#define LWM2M_FIRMWARE_UPDATE_RESULT_ERROR_STORAGE        2
#define LWM2M_FIRMWARE_UPDATE_RESULT_ERROR_MEMORY         3
#define LWM2M_FIRMWARE_UPDATE_RESULT_ERROR_CONN_LOST      4
#define LWM2M_FIRMWARE_UPDATE_RESULT_ERROR_CRC            5
#define LWM2M_FIRMWARE_UPDATE_RESULT_ERROR_UNSUPPORTED    6
#define LWM2M_FIRMWARE_UPDATE_RESULT_ERROR_INVALID_URI    7


/* LWM2M ACL Resources */
#define LWM2M_ACL_OBJECT_ID                               0
#define LWM2M_ACL_INSTANCE_ID                             1
#define LWM2M_ACL_ACL                                     2
#define LWM2M_ACL_CONTROL_OWNER                           3

/* LWM2M Connectivity Monitoring Resources */
#define LWM2M_CONN_MON_NETWORK_BEARER                     0
#define LWM2M_CONN_MON_AVAILABLE_NETWORK_BEARER           1
#define LWM2M_CONN_MON_RADIO_SIGNAL_STRENGHT              2
#define LWM2M_CONN_MON_LINK_QUALITY                       3
#define LWM2M_CONN_MON_IP_ADDRESSES                       4
#define LWM2M_CONN_MON_ROUTER_IP_ADRESSES                 5
#define LWM2M_CONN_MON_LINK_UTILIZATION                   6
#define LWM2M_CONN_MON_APN                                7
#define LWM2M_CONN_MON_CELL_ID                            8
#define LWM2M_CONN_MON_SMNC                               9
#define LWM2M_CONN_MON_SMCC                               10

/* LWM2M Connectivity Statistics */
#define LWM2M_CONN_STAT_SMS_TX_COUNTER                    0
#define LWM2M_CONN_STAT_SMS_RX_COUNTER                    1
#define LWM2M_CONN_STAT_TX_DATA                           2
#define LWM2M_CONN_STAT_RX_DATA                           3
#define LWM2M_CONN_STAT_MAX_MSG_SIZE                      4
#define LWM2M_CONN_STAT_AVG_MSG_SIZE                      5
#define LWM2M_CONN_STAT_START_RESET                       6

/* LWM2M Device */
#define LWM2M_DEVICE_MANUFACTURER                         0
#define LWM2M_DEVICE_MODEL_NUMBER                         1
#define LWM2M_DEVICE_SERIAL_NUMBER                        2
#define LWM2M_DEVICE_FIRMWARE_VERSION                     3
#define LWM2M_DEVICE_REBOOT                               4
#define LWM2M_DEVICE_FACTORY_RESET                        5
#define LWM2M_DEVICE_AVAILABLE_POWER_SOURCES              6
#define LWM2M_DEVICE_POWER_SOURCE_VOLTAGE                 7
#define LWM2M_DEVICE_POWER_SOURCE_CURRENT                 8
#define LWM2M_DEVICE_BATTERY_LEVEL                        9
#define LWM2M_DEVICE_MEMORY_FREE                         10
#define LWM2M_DEVICE_ERROR_CODE                          11
#define LWM2M_DEVICE_RESET_ERROR_CODE                    12
#define LWM2M_DEVICE_CURRENT_TIME                        13
#define LWM2M_DEVICE_UTC_OFFSET                          14
#define LWM2M_DEVICE_TIMEZONE                            15
#define LWM2M_DEVICE_SUPPORTED_BINDINGS                  16

/* LWM2M Location */
#define LWM2M_LOCATION_LATITUDE                           0
#define LWM2M_LOCATION_LONGITUDE                          1
#define LWM2M_LOCATION_ALTITUDE                           2
#define LWM2M_LOCATION_UNCERTAINTY                        3
#define LWM2M_LOCATION_VELOCITY                           4
#define LWM2M_LOCATION_TIMESTAMP                          5

/* LWM2M Software update */
#define LWM2M_SW_UPDATE_PKG_NAME                          0
#define LWM2M_SW_UPDATE_PKG_VERSION                       1
#define LWM2M_SW_UPDATE_PACKAGE                           2
#define LWM2M_SW_UPDATE_PACKAGE_URI                       3
#define LWM2M_SW_UPDATE_INSTALL                           4
#define LWM2M_SW_UPDATE_CHECKPOINT                        5
#define LWM2M_SW_UPDATE_UNINSTALL                         6
#define LWM2M_SW_UPDATE_UPDATE_STATE                      7
#define LWM2M_SW_UPDATE_SUPPORTED_OBJECTS                 8

/**
 * LWM2M Enabler
 */

typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. MUST be first. */
    uint8_t                     operations[12];         /* Internal. MUST be second. */
    uint16_t                    resource_ids[12];       /* Internal. MUST be third. */

    /* Public members. */
    lwm2m_string_t              server_uri;
    bool                        bootstrap_server;
    uint8_t                     security_mode;
    lwm2m_opaque_t              public_key;
    lwm2m_opaque_t              server_public_key;
    lwm2m_opaque_t              secret_key;
    uint8_t                     sms_security_mode;
    lwm2m_opaque_t              sms_binding_key_param;
    lwm2m_opaque_t              sms_binding_secret_keys;
    uint32_t                    sms_number;
    uint16_t                    short_server_id;
    lwm2m_time_t                client_hold_off_time;

} lwm2m_security_t;

typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. MUST be first. */
    uint8_t                     operations[9];          /* Internal. MUST be second. */
    uint16_t                    resource_ids[9];        /* Internal. MUST be third. */

    /* Public members. */
    uint16_t                    short_server_id;
    lwm2m_time_t                lifetime;
    lwm2m_time_t                default_minimum_period;
    lwm2m_time_t                default_maximum_period;
    void *                      disable;                         // Function pointer.
    lwm2m_time_t                disable_timeout;
    bool                        notification_storing_on_disabled;
    lwm2m_string_t              binding;
    void *                      registration_update_trigger;     // Function pointer.

} lwm2m_server_t;

typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. MUST be first. */
    uint8_t                     operations[6];          /* Internal. MUST be second. */
    uint16_t                    resource_ids[6];        /* Internal. MUST be third. */

    /* Public members. */
    lwm2m_opaque_t              package;
    lwm2m_string_t              package_uri;
    uint8_t                     state;
    bool                        update_supported_objects;
    uint8_t                     update_result;

} lwm2m_firmware_t;

typedef struct
{
    lwm2m_instance_prototype_t  proto;
    uint8_t                     operations[4];
    uint16_t                    resource_ids[4];

    /* Public members. */
    uint16_t                    acl_object_id;
    uint16_t                    acl_instance_id;
    uint16_t                    acl;
    uint16_t                    control_owner;

} lwm2m_acl_t;

typedef struct
{
    lwm2m_instance_prototype_t  proto;
    uint8_t                     operations[11];
    uint16_t                    resource_ids[11];

    /* Public members. */
    uint32_t                    network_bearer;
    uint32_t                    available_network_bearer;// TODO this is a list!
    uint32_t                    radio_signal_strength;   // Unit: dBm
    uint32_t                    link_quality;
    lwm2m_string_t              ip_addresses;            // TODO: this is a list!
    lwm2m_string_t              router_ip_addresses;     // TODO: this is a list!
    uint8_t                     link_utilization;        // Unit: percent
    lwm2m_string_t              apn;                     // TODO: this is a list!
    uint32_t                    cell_id;
    uint8_t                     smnc;                    // Unit: percent
    uint32_t                    smcc;

} lwm2m_connectivity_monitoring_t;

typedef struct
{
    lwm2m_instance_prototype_t  proto;
    uint8_t                     operations[7];
    uint16_t                    resource_ids[7];

    /* Public members. */
    uint32_t                    sms_tx_counter;
    uint32_t                    sms_rx_counter;
    uint32_t                    tx_data;                 // Unit: kilo-bytes
    uint32_t                    rx_data;                 // Unit: kilo-bytes
    uint32_t                    max_message_size;        // Unit: byte
    uint32_t                    average_message_size;    // Unit: byte
    /* StartOrReset is Execute only */

} lwm2m_connectivity_statistics_t;

typedef struct
{
    lwm2m_instance_prototype_t  proto;
    uint8_t                     operations[17];
    uint16_t                    resource_ids[17];

    /* Public members. */
    lwm2m_string_t              manufacturer;
    lwm2m_string_t              model_number;
    lwm2m_string_t              serial_number;
    lwm2m_string_t              firmware_version;
    /* Reboot is execute only */
    /* Factory reset is execute only */
    uint8_t                     avail_power_sources;     // TODO: this is a list, Range: 0-7
    uint32_t                    power_source_voltage;    // TODO: this is a list, Unit: mV
    uint32_t                    power_source_current;    // TODO: this is a list, Unit: mA
    uint8_t                     battery_level;           // Unit: percent
    uint32_t                    memory_free;             // Unit: KB
    uint32_t                    error_code;              // TODO: this is a list
    /* Reset Error code is execute only */
    lwm2m_time_t                current_time;
    lwm2m_string_t              utc_offset;
    lwm2m_string_t              timezone;
    lwm2m_string_t              supported_bindings;      // TODO this is a list

} lwm2m_device_t;

typedef struct
{
    lwm2m_instance_prototype_t  proto;
    uint8_t                     operations[6];
    uint16_t                    resource_ids[6];

    /* Public members. */
    lwm2m_string_t              latitude;                // Unit: Deg
    lwm2m_string_t              longitude;               // Unit: Deg
    lwm2m_string_t              altitude;                // Unit: m
    lwm2m_string_t              uncertainty;             // Unit: m
    lwm2m_opaque_t              velocity;                // Unit: Refers to 3GPP GAD specs
    lwm2m_time_t                timestamp;               // Range: 0-6

} lwm2m_location_t;

typedef struct
{
    lwm2m_instance_prototype_t  proto;
    uint8_t                     operations[9];
    uint16_t                    resource_ids[9];

    /* Public members. */
    lwm2m_string_t              pkg_name;
    lwm2m_string_t              pkg_version;
    lwm2m_opaque_t              package;
    lwm2m_string_t              package_uri;
    /* Install is execute only */
    uint16_t                    checkpoint;              // TODO: this is of type Objlnk
    /* Uninstall is execute only */
    uint8_t                     update_state;            // Range: 1-5
    bool                        update_supported_objects;

} lwm2m_software_update_t;

/**@brief Initialize a LWM2M security object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void lwm2m_instance_security_init(lwm2m_security_t * p_instance);

/**@brief Initialize a LWM2M server object instance.
 *
 * @details Must be called before any use of the instance.

 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void lwm2m_instance_server_init(lwm2m_server_t * p_instance);

/**@brief Initialize a LWM2M firmware object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void lwm2m_instance_firmware_init(lwm2m_firmware_t * p_instance);

/**@brief Initialize a LWM2M ACL object instance
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void lwm2m_instance_acl_init(lwm2m_acl_t * p_instance);

/**@brief Initialize a LWM2M connectivity monitoring object instance
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void lwm2m_instance_connectivity_monitoring_init(lwm2m_connectivity_monitoring_t * p_instance);

/**@brief Initialize a LWM2M connectivity statistics object instance
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void lwm2m_instance_connectivity_statistics_init(lwm2m_connectivity_statistics_t * p_instance);

/**@brief Initialize a LWM2M device object instance
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void lwm2m_instance_device_init(lwm2m_device_t * p_instance);

/**@brief Initialize a LWM2M location object instance
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void lwm2m_instance_location_init(lwm2m_location_t * p_instance);

/**@brief Initialize a LWM2M software update object instance
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void lwm2m_instance_software_update_init(lwm2m_software_update_t * p_instance);

#ifdef __cplusplus
}
#endif

#endif // LWM2M_OBJECTS_H__

/** @} */
