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
 * @defgroup iot_sdk_ipso_objects IPSO Smart Object definititions and types
 * @ingroup iot_sdk_lwm2m
 * @{
 * @brief IPSO objects definitions and types.
 *
 * @note The definitions used in this module are from the IPSO Alliance
 *       "IPSO SmartOject Guideline - Smart Objects Starter Pack1.0".
 *       The specification could be found at http://www.ipso-alliance.org/.
 */

#ifndef IPSO_OBJECTS_H__
#define IPSO_OBJECTS_H__

#include "lwm2m_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IPSO_SO_ID_DIGITAL_INPUT                          3200
#define IPSO_SO_ID_DIGITAL_OUTPUT                         3201
#define IPSO_SO_ID_ANALOGUE_INPUT                         3202
#define IPSO_SO_ID_ANALOGUE_OUTPUT                        3203
#define IPSO_SO_ID_GENERIC_SENSOR                         3300
#define IPSO_SO_ID_ILLUMINANCE_SENSOR                     3301
#define IPSO_SO_ID_PRESENCE_SENSOR                        3302
#define IPSO_SO_ID_TEMPERATURE_SENSOR                     3303
#define IPSO_SO_ID_HUMIDITY_SENSOR                        3304
#define IPSO_SO_ID_POWER_MEASUREMENT                      3305
#define IPSO_SO_ID_ACTUATION                              3306
#define IPSO_SO_ID_SET_POINT                              3308
#define IPSO_SO_ID_LOAD_CONTROL                           3310
#define IPSO_SO_ID_LIGHT_CONTROL                          3311
#define IPSO_SO_ID_POWER_CONTROL                          3312
#define IPSO_SO_ID_ACCELEROMETER                          3313
#define IPSO_SO_ID_MAGNETOMETER                           3314
#define IPSO_SO_ID_BAROMETER                              3315

/** @brief IPSO Reusable Resource IDs (Section 21). */
#define IPSO_RR_ID_DIGITAL_INPUT_STATE                    5500
#define IPSO_RR_ID_DIGITAL_INPUT_COUNTER                  5501
#define IPSO_RR_ID_DIGITAL_INPUT_POLARITY                 5502
#define IPSO_RR_ID_DIGITAL_INPUT_DEBOUNCE_PERIOD          5503
#define IPSO_RR_ID_DIGITAL_INPUT_EDGE_SELECTION           5504
#define IPSO_RR_ID_DIGITAL_INPUT_COUNTER_RESET            5505

#define IPSO_RR_ID_DIGITAL_OUTPUT_STATE                   5550
#define IPSO_RR_ID_DIGITAL_OUTPUT_POLARITY                5551


// Digital output polarity options.
#define IPSO_RR_ID_DIGITAL_OUTPUT_POLARITY_NORMAL         0
#define IPSO_RR_ID_DIGITAL_OUTPUT_POLARITY_REVERSED       1

#define IPSO_RR_ID_ANALOG_INPUT_CURRENT_VALUE             5600
#define IPSO_RR_ID_MIN_MEASURED_VALUE                     5601
#define IPSO_RR_ID_MAX_MEASURED_VALUE                     5602
#define IPSO_RR_ID_MIN_RANGE_VALUE                        5603
#define IPSO_RR_ID_MAX_RANGE_VALUE                        5604
#define IPSO_RR_ID_RESET_MIN_MAX_MEASURED_VALUES          5605

#define IPSO_RR_ID_ANALOG_OUTPUT_CURRENT_VALUE            5650

#define IPSO_RR_ID_SENSOR_VALUE                           5700
#define IPSO_RR_ID_SENSOR_UNITS                           5701
#define IPSO_RR_ID_X_VALUE                                5702
#define IPSO_RR_ID_Y_VALUE                                5703
#define IPSO_RR_ID_Z_VALUE                                5704
#define IPSO_RR_ID_COMPASS_DIRECTION                      5705
#define IPSO_RR_ID_COLOUR                                 5706

#define IPSO_RR_ID_APPLICATION_TYPE                       5750
#define IPSO_RR_ID_SENSOR_TYPE                            5751

#define IPSO_RR_ID_INSTANTANEOUS_ACTIVE_POWER             5800
#define IPSO_RR_ID_MIN_MEASURED_ACTIVE_POWER              5801
#define IPSO_RR_ID_MAX_MEASURED_ACTIVE_POWER              5802
#define IPSO_RR_ID_MIN_RANGE_ACTIVE_POWER                 5803
#define IPSO_RR_ID_MAX_RANGE_ACTIVE_POWER                 5804
#define IPSO_RR_ID_CUMULATIVE_ACTIVE_POWER                5805
#define IPSO_RR_ID_ACTIVE_POWER_CALIBRATION               5806

#define IPSO_RR_ID_INSTANTANEOUS_REACTIVE_POWER           5810
#define IPSO_RR_ID_MIN_MEASURED_REACTIVE_POWER            5811
#define IPSO_RR_ID_MAX_MEASURED_REACTIVE_POWER            5812
#define IPSO_RR_ID_MIN_RANGE_REACTIVE_POWER               5813
#define IPSO_RR_ID_MAX_RANGE_REACTIVE_POWER               5814
#define IPSO_RR_ID_CUMULATIVE_REACTIVE_POWER              5815
#define IPSO_RR_ID_REACTIVE_POWER_CALIBRATION             5816

#define IPSO_RR_ID_POWER_FACTOR                           5820
#define IPSO_RR_ID_CURRENT_CALIBRATION                    5821
#define IPSO_RR_ID_RESET_CUMULATIVE_ENERGY                5822
#define IPSO_RR_ID_EVENT_IDENTIFIER                       5823
#define IPSO_RR_ID_START_TIME                             5824
#define IPSO_RR_ID_DURATION_IN_MIN                        5825
#define IPSO_RR_ID_CRITICALITY_LEVEL                      5826
#define IPSO_RR_ID_AVG_LOAD_ADJPCT                        5827
#define IPSO_RR_ID_DUTY_CYCLE                             5828

#define IPSO_RR_ID_ON_OFF                                 5850
#define IPSO_RR_ID_DIMMER                                 5851
#define IPSO_RR_ID_ON_TIME                                5852
#define IPSO_RR_ID_MULTI_STATE_OUTPUT                     5853

#define IPSO_RR_ID_SETPOINT_VALUE                         5900

#define IPSO_RR_ID_BUSY_TO_CLEAR_DELAY                    5903
#define IPSO_RR_ID_CLEAR_TO_BUSY_DELAY                    5904



/* Digital input ID: 3200 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[8];          /* Internal. */
    uint16_t                    resource_ids[8];        /* Internal. */

    /* Public members. */
    bool                        state;
    uint32_t                    counter;
    bool                        polarity;
    uint32_t                    debounce_period; /* Unit: milliseconds */
    uint8_t                     edge_selection; /* Range: 1-3 */
    /* Counter reset is execute only */
    lwm2m_string_t              application_type;
    lwm2m_string_t              sensor_type;

} ipso_digital_input_t;


/* Digital output ID: 3201 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. MUST be first. */
    uint8_t                     operations[3];          /* Internal. MUST be second. */
    uint16_t                    resource_ids[3];        /* Internal. MUST be third. */

    /* Public members. */
    bool                        digital_output_state;
    bool                        digital_output_polarity;
    lwm2m_string_t              application_type;

} ipso_digital_output_t;

/* Analog input ID: 3202 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[8];          /* Internal. */
    uint16_t                    resource_ids[8];        /* Internal. */

    /* Public members. */
    float                       current_value;
    float                       min_measured_value;
    float                       max_measured_value;
    float                       min_range_value;
    float                       max_range_value;
    /* Reset min and max measured values is execute only */
    lwm2m_string_t              application_type;
    lwm2m_string_t              sensor_type;
} ipso_analog_input_t;

/* Analog output ID: 3203 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[4];          /* Internal. */
    uint16_t                    resource_ids[4];        /* Internal. */

    /* Public members. */
    float                       current_value;
    float                       min_range_value;
    float                       max_range_value;
    lwm2m_string_t              application_type;

} ipso_analog_output_t;

/* Generic sensor ID: 3300 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[9];          /* Internal. */
    uint16_t                    resource_ids[9];        /* Internal. */

    /* Public members. */
    float                       sensor_value;
    lwm2m_string_t              units;
    float                       min_measured_value;
    float                       max_measured_value;
    float                       min_range_value;
    float                       max_range_value;
    /* Reset min and max measured values is execute only */
    lwm2m_string_t              application_type;
    lwm2m_string_t              sensor_type;

} ipso_generic_sensor_t;

/* Illuminance ID: 3301 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[7];          /* Internal. */
    uint16_t                    resource_ids[7];        /* Internal. */

    /* Public members. */
    float                       sensor_value;
    lwm2m_string_t              units;
    float                       min_measured_value;
    float                       max_measured_value;
    float                       min_range_value;
    float                       max_range_value;
    /* Reset min and max measured values is execute only */

} ipso_illuminance_t;

/* Presence ID: 3302 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[8];          /* Internal. */
    uint16_t                    resource_ids[8];        /* Internal. */

    /* Public members. */
    bool                        digital_input_state;
    uint32_t                    digital_input_counter;
    /* Digital input counter reset is execute only */
    lwm2m_string_t              sensor_type;
    uint32_t                    busy_to_clear_delay; // Unit: ms
    uint32_t                    clear_to_busy_delay; // Unit: ms


} ipso_presence_t;

/* Temperature ID: 3303 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[7];          /* Internal. */
    uint16_t                    resource_ids[7];        /* Internal. */

    /* Public members. */
    float                       sensor_value;
    lwm2m_string_t              units;
    float                       min_measured_value;
    float                       max_measured_value;
    float                       min_range_value;
    float                       max_range_value;
    /* Reset min and max measured values is execute only */


} ipso_temperature_t;

/* Humidity ID: 3304 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[8];          /* Internal. */
    uint16_t                    resource_ids[8];        /* Internal. */

    /* Public members. */
    float                       sensor_value;
    lwm2m_string_t              units;
    float                       min_measured_value;
    float                       max_measured_value;
    float                       min_range_value;
    float                       max_range_value;
    /* Reset min and max measured values is execute only */

} ipso_humidity_t;

/* Power measurement ID: 3305 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[18];          /* Internal. */
    uint16_t                    resource_ids[18];        /* Internal. */

    /* Public members. */
    float                       instantaneous_active_power;
    float                       min_measured_active_power;
    float                       max_measured_active_power;
    float                       min_range_active_power;
    float                       max_range_active_power;
    float                       cumulative_active_power;
    float                       active_power_calibration;
    float                       instantaneous_reactive_power;
    float                       min_measured_reactive_power;
    float                       max_measured_reactive_power;
    float                       min_range_reactive_power;
    float                       max_range_reactive_power;
    /* Reset min and max measured values is execute only */
    float                       cumulative_reactive_power;
    float                       reactive_power_calibration;
    float                       power_factor;
    float                       current_calibration;
    /* Reset cumulative is execute only */

} ipso_power_measurement_t;

/* Actuation ID: 3306 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[5];          /* Internal. */
    uint16_t                    resource_ids[5];        /* Internal. */

    /* Public members. */
    bool                        on;
    uint16_t                    dimmer; // Unit: % Range: 0 - 100
    uint32_t                    on_time; // Unit: s
    lwm2m_string_t              multi_state_output;
    lwm2m_string_t              application_type;

} ipso_actuation_t;

/* Set point ID: 3308 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[4];          /* Internal. */
    uint16_t                    resource_ids[4];        /* Internal. */

    /* Public members. */
    float                       set_point_value;
    lwm2m_string_t              colour;
    lwm2m_string_t              units;
    lwm2m_string_t              application_type;

} ipso_set_point_t;

/* Load control ID: 3310 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[6];          /* Internal. */
    uint16_t                    resource_ids[6];        /* Internal. */

    /* Public members. */
    lwm2m_string_t              event_identifier;
    lwm2m_time_t                start_time;
    uint32_t                    duration_in_min;
    uint8_t                     criticality_level; // Range: 0-3
    uint16_t                    avg_load_adjpct; // Unit: % range: 0-100
    uint16_t                    duty_cycle; // Unit: % range: 0-100


} ipso_load_control_t;

/* Light control ID: 3311 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[7];          /* Internal. */
    uint16_t                    resource_ids[7];        /* Internal. */

    /* Public members. */
    bool                        on;
    uint16_t                    dimmer; // Unit: % Range: 0 - 100
    lwm2m_string_t              colour;
    lwm2m_string_t              units;
    uint32_t                    on_time; // Unit: s
    float                       cumulative_active_power;
    float                       power_factor;

} ipso_light_control_t;

/* Power control ID: 3312 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[5];          /* Internal. */
    uint16_t                    resource_ids[5];        /* Internal. */

    /* Public members. */
    bool                        on;
    uint16_t                    dimmer; // Unit: % Range: 0 - 100
    uint32_t                    on_time; // Unit: s
    float                       cumulative_active_power;
    float                       power_factor;

} ipso_power_control_t;

/* Accelerometer ID: 3313 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[6];          /* Internal. */
    uint16_t                    resource_ids[6];        /* Internal. */

    /* Public members. */
    float                       x_value;
    float                       y_value;
    float                       z_value;
    lwm2m_string_t              units;
    float                       min_range_value;
    float                       max_range_value;

} ipso_accelerometer_t;

/* Magnetometer ID: 3314 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[8];          /* Internal. */
    uint16_t                    resource_ids[8];        /* Internal. */

    /* Public members. */
    float                       x_value;
    float                       y_value;
    float                       z_value;
    lwm2m_string_t              units;
    float                       compass_direction; // Unit: deg  Range: 0-360

} ipso_magnetometer_t;

/* Barometer ID: 3315 */
typedef struct
{
    lwm2m_instance_prototype_t  proto;                  /* Internal. */
    uint8_t                     operations[7];          /* Internal. */
    uint16_t                    resource_ids[7];        /* Internal. */

    /* Public members. */
    float                       sensor_value;
    lwm2m_string_t              units;
    float                       min_measured_value;
    float                       max_measured_value;
    float                       min_range_value;
    float                       max_range_value;
    /* Reset min and max measured values is execute only */

} ipso_barometer_t;


/**@brief Initialize an IPSO digital input object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_digital_input_init(ipso_digital_input_t * p_instance);

/**@brief Initialize an IPSO digital output object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_digital_output_init(ipso_digital_output_t * p_instance);

/**@brief Initialize an IPSO analog input object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_analog_input_init(ipso_analog_input_t * p_instance);

/**@brief Initialize an IPSO analog output object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_analog_output_init(ipso_analog_output_t * p_instance);

/**@brief Initialize an IPSO generic sensor object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_generic_sensor_init(ipso_generic_sensor_t * p_instance);

/**@brief Initialize an IPSO illuminance object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_illuminance_init(ipso_illuminance_t * p_instance);

/**@brief Initialize an IPSO presence object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_presence_init(ipso_presence_t * p_instance);

/**@brief Initialize an IPSO temperature object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_temperature_init(ipso_temperature_t * p_instance);

/**@brief Initialize an IPSO humidity object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_humidity_init(ipso_humidity_t * p_instance);

/**@brief Initialize an IPSO power measurement object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_power_measurement_init(ipso_power_measurement_t * p_instance);

/**@brief Initialize an IPSO actuation object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_actuation_init(ipso_actuation_t * p_instance);

/**@brief Initialize an IPSO set point object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_set_point_init(ipso_set_point_t * p_instance);

/**@brief Initialize an IPSO load control object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_load_control_init(ipso_load_control_t * p_instance);

/**@brief Initialize an IPSO light control object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_light_control_init(ipso_light_control_t * p_instance);

/**@brief Initialize an IPSO power control object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_power_control_init(ipso_power_control_t * p_instance);

/**@brief Initialize an IPSO accelerometer object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_accelerometer_init(ipso_accelerometer_t * p_instance);

/**@brief Initialize an IPSO magnetometer object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_magnetometer_init(ipso_magnetometer_t * p_instance);

/**@brief Initialize an IPSO barometer object instance.
 *
 * @details Must be called before any use of the instance.
 *
 * @param[in] p_instance Pointer to instance structure to initialize.
 */
void ipso_instance_barometer_init(ipso_barometer_t * p_instance);

#ifdef __cplusplus
}
#endif

#endif // LWM2M_OBJECTS_H__

/** @} */
