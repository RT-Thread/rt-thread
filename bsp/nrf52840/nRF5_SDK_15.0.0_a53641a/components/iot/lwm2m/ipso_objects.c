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
#include <string.h>
#include <stddef.h>

#include "ipso_objects.h"
#include "lwm2m.h"
#include "lwm2m_tlv.h"

//lint -e516 -save // Symbol '__INTADDR__()' has arg. type conflict
#define LWM2M_INSTANCE_OFFSET_SET(instance, type) \
    instance->proto.operations_offset = offsetof(type, operations); \
    instance->proto.resource_ids_offset = offsetof(type, resource_ids);
//lint -restore

void ipso_instance_digital_input_init(ipso_digital_input_t * p_instance)
{
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_digital_input_t);

    p_instance->proto.object_id     = IPSO_SO_ID_DIGITAL_INPUT;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_digital_input_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[3] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[4] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[5] = LWM2M_OPERATION_CODE_EXECUTE;
    p_instance->operations[6] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[7] = LWM2M_OPERATION_CODE_READ;


    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_DIGITAL_INPUT_STATE;
    p_instance->resource_ids[1] = IPSO_RR_ID_DIGITAL_INPUT_COUNTER;
    p_instance->resource_ids[2] = IPSO_RR_ID_DIGITAL_INPUT_POLARITY;
    p_instance->resource_ids[3] = IPSO_RR_ID_DIGITAL_INPUT_DEBOUNCE_PERIOD;
    p_instance->resource_ids[4] = IPSO_RR_ID_DIGITAL_INPUT_EDGE_SELECTION;
    p_instance->resource_ids[5] = IPSO_RR_ID_DIGITAL_INPUT_COUNTER_RESET;
    p_instance->resource_ids[6] = IPSO_RR_ID_APPLICATION_TYPE;
    p_instance->resource_ids[7] = IPSO_RR_ID_SENSOR_TYPE;


}

void ipso_instance_digital_output_init(ipso_digital_output_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_digital_output_t);

    p_instance->proto.object_id     = IPSO_SO_ID_DIGITAL_OUTPUT;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_digital_output_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[1] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[2] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_DIGITAL_OUTPUT_STATE;
    p_instance->resource_ids[1] = IPSO_RR_ID_DIGITAL_OUTPUT_POLARITY;
    p_instance->resource_ids[2] = IPSO_RR_ID_APPLICATION_TYPE;
}


void ipso_instance_analog_input_init(ipso_analog_input_t * p_instance)
{

    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_analog_input_t);

    p_instance->proto.object_id     = IPSO_SO_ID_ANALOGUE_INPUT;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_analog_input_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[5] = LWM2M_OPERATION_CODE_EXECUTE;
    p_instance->operations[6] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[7] = LWM2M_OPERATION_CODE_READ;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_ANALOG_INPUT_CURRENT_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_MIN_MEASURED_VALUE;
    p_instance->resource_ids[2] = IPSO_RR_ID_MAX_MEASURED_VALUE;
    p_instance->resource_ids[3] = IPSO_RR_ID_MIN_RANGE_VALUE;
    p_instance->resource_ids[4] = IPSO_RR_ID_MAX_RANGE_VALUE;
    p_instance->resource_ids[5] = IPSO_RR_ID_RESET_MIN_MAX_MEASURED_VALUES;
    p_instance->resource_ids[6] = IPSO_RR_ID_APPLICATION_TYPE;
    p_instance->resource_ids[7] = IPSO_RR_ID_SENSOR_TYPE;
}

void ipso_instance_analog_output_init(ipso_analog_output_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_analog_output_t);

    p_instance->proto.object_id     = IPSO_SO_ID_ANALOGUE_OUTPUT;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_analog_output_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_ANALOG_OUTPUT_CURRENT_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_MIN_RANGE_VALUE;
    p_instance->resource_ids[2] = IPSO_RR_ID_MAX_RANGE_VALUE;
    p_instance->resource_ids[3] = IPSO_RR_ID_APPLICATION_TYPE;
}

void ipso_instance_generic_sensor_init(ipso_generic_sensor_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_generic_sensor_t);

    p_instance->proto.object_id     = IPSO_SO_ID_GENERIC_SENSOR;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_generic_sensor_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[5] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[6] = LWM2M_OPERATION_CODE_EXECUTE;
    p_instance->operations[7] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[8] = LWM2M_OPERATION_CODE_READ;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_SENSOR_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_SENSOR_UNITS;
    p_instance->resource_ids[2] = IPSO_RR_ID_MIN_MEASURED_VALUE;
    p_instance->resource_ids[3] = IPSO_RR_ID_MAX_MEASURED_VALUE;
    p_instance->resource_ids[4] = IPSO_RR_ID_MIN_RANGE_VALUE;
    p_instance->resource_ids[5] = IPSO_RR_ID_MAX_RANGE_VALUE;
    p_instance->resource_ids[6] = IPSO_RR_ID_RESET_MIN_MAX_MEASURED_VALUES;
    p_instance->resource_ids[7] = IPSO_RR_ID_APPLICATION_TYPE;
    p_instance->resource_ids[8] = IPSO_RR_ID_SENSOR_TYPE;
}

void ipso_instance_illuminance_init(ipso_illuminance_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_illuminance_t);

    p_instance->proto.object_id     = IPSO_SO_ID_ILLUMINANCE_SENSOR;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_illuminance_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[5] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[6] = LWM2M_OPERATION_CODE_EXECUTE;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_SENSOR_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_SENSOR_UNITS;
    p_instance->resource_ids[2] = IPSO_RR_ID_MIN_MEASURED_VALUE;
    p_instance->resource_ids[3] = IPSO_RR_ID_MAX_MEASURED_VALUE;
    p_instance->resource_ids[4] = IPSO_RR_ID_MIN_RANGE_VALUE;
    p_instance->resource_ids[5] = IPSO_RR_ID_MAX_RANGE_VALUE;
    p_instance->resource_ids[6] = IPSO_RR_ID_RESET_MIN_MAX_MEASURED_VALUES;
}

void ipso_instance_presence_init(ipso_presence_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_presence_t);

    p_instance->proto.object_id     = IPSO_SO_ID_PRESENCE_SENSOR;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_presence_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_EXECUTE;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[5] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_DIGITAL_INPUT_STATE;
    p_instance->resource_ids[1] = IPSO_RR_ID_DIGITAL_INPUT_COUNTER;
    p_instance->resource_ids[2] = IPSO_RR_ID_DIGITAL_INPUT_COUNTER_RESET;
    p_instance->resource_ids[3] = IPSO_RR_ID_SENSOR_TYPE;
    p_instance->resource_ids[4] = IPSO_RR_ID_BUSY_TO_CLEAR_DELAY;
    p_instance->resource_ids[5] = IPSO_RR_ID_CLEAR_TO_BUSY_DELAY;
}

void ipso_instance_temperature_init(ipso_temperature_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_temperature_t);

    p_instance->proto.object_id     = IPSO_SO_ID_TEMPERATURE_SENSOR;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_temperature_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[5] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[6] = LWM2M_OPERATION_CODE_EXECUTE;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_SENSOR_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_SENSOR_UNITS;
    p_instance->resource_ids[2] = IPSO_RR_ID_MIN_MEASURED_VALUE;
    p_instance->resource_ids[3] = IPSO_RR_ID_MAX_MEASURED_VALUE;
    p_instance->resource_ids[4] = IPSO_RR_ID_MIN_RANGE_VALUE;
    p_instance->resource_ids[5] = IPSO_RR_ID_MAX_RANGE_VALUE;
    p_instance->resource_ids[6] = IPSO_RR_ID_RESET_MIN_MAX_MEASURED_VALUES;
}

void ipso_instance_humidity_init(ipso_humidity_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_humidity_t);

    p_instance->proto.object_id     = IPSO_SO_ID_HUMIDITY_SENSOR;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_humidity_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[5] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[6] = LWM2M_OPERATION_CODE_EXECUTE;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_SENSOR_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_SENSOR_UNITS;
    p_instance->resource_ids[2] = IPSO_RR_ID_MIN_MEASURED_VALUE;
    p_instance->resource_ids[3] = IPSO_RR_ID_MAX_MEASURED_VALUE;
    p_instance->resource_ids[4] = IPSO_RR_ID_MIN_RANGE_VALUE;
    p_instance->resource_ids[5] = IPSO_RR_ID_MAX_RANGE_VALUE;
    p_instance->resource_ids[6] = IPSO_RR_ID_RESET_MIN_MAX_MEASURED_VALUES;
}

void ipso_instance_power_measurement_init(ipso_power_measurement_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_power_measurement_t);

    p_instance->proto.object_id     = IPSO_SO_ID_POWER_MEASUREMENT;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_power_measurement_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[5] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[6] = LWM2M_OPERATION_CODE_WRITE;
    p_instance->operations[7] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[8] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[9] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[10] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[11] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[12] = LWM2M_OPERATION_CODE_EXECUTE;
    p_instance->operations[13] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[14] = LWM2M_OPERATION_CODE_WRITE;
    p_instance->operations[15] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[16] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[17] = LWM2M_OPERATION_CODE_EXECUTE;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_INSTANTANEOUS_ACTIVE_POWER;
    p_instance->resource_ids[1] = IPSO_RR_ID_MIN_MEASURED_ACTIVE_POWER;
    p_instance->resource_ids[2] = IPSO_RR_ID_MAX_MEASURED_ACTIVE_POWER;
    p_instance->resource_ids[3] = IPSO_RR_ID_MIN_RANGE_ACTIVE_POWER;
    p_instance->resource_ids[4] = IPSO_RR_ID_MAX_RANGE_ACTIVE_POWER;
    p_instance->resource_ids[5] = IPSO_RR_ID_CUMULATIVE_ACTIVE_POWER;
    p_instance->resource_ids[6] = IPSO_RR_ID_ACTIVE_POWER_CALIBRATION;
    p_instance->resource_ids[7] = IPSO_RR_ID_INSTANTANEOUS_REACTIVE_POWER;
    p_instance->resource_ids[8] = IPSO_RR_ID_MIN_MEASURED_REACTIVE_POWER;
    p_instance->resource_ids[9] = IPSO_RR_ID_MAX_MEASURED_REACTIVE_POWER;
    p_instance->resource_ids[10] = IPSO_RR_ID_MIN_RANGE_REACTIVE_POWER;
    p_instance->resource_ids[11] = IPSO_RR_ID_MAX_RANGE_REACTIVE_POWER;
    p_instance->resource_ids[12] = IPSO_RR_ID_RESET_MIN_MAX_MEASURED_VALUES;
    p_instance->resource_ids[13] = IPSO_RR_ID_CUMULATIVE_REACTIVE_POWER;
    p_instance->resource_ids[14] = IPSO_RR_ID_REACTIVE_POWER_CALIBRATION;
    p_instance->resource_ids[15] = IPSO_RR_ID_POWER_FACTOR;
    p_instance->resource_ids[16] = IPSO_RR_ID_CURRENT_CALIBRATION;
    p_instance->resource_ids[17] = IPSO_RR_ID_RESET_CUMULATIVE_ENERGY;
}

void ipso_instance_actuation_init(ipso_actuation_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_actuation_t);

    p_instance->proto.object_id     = IPSO_SO_ID_ACTUATION;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_actuation_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[1] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[2] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[3] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[4] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_ON_OFF;
    p_instance->resource_ids[1] = IPSO_RR_ID_DIMMER;
    p_instance->resource_ids[2] = IPSO_RR_ID_ON_TIME;
    p_instance->resource_ids[3] = IPSO_RR_ID_MULTI_STATE_OUTPUT;
    p_instance->resource_ids[4] = IPSO_RR_ID_APPLICATION_TYPE;
}

void ipso_instance_set_point_init(ipso_set_point_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_set_point_t);

    p_instance->proto.object_id     = IPSO_SO_ID_SET_POINT;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_set_point_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[1] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_SETPOINT_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_COLOUR;
    p_instance->resource_ids[2] = IPSO_RR_ID_SENSOR_UNITS;
    p_instance->resource_ids[3] = IPSO_RR_ID_APPLICATION_TYPE;
}

void ipso_instance_load_control_init(ipso_load_control_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_load_control_t);

    p_instance->proto.object_id     = IPSO_SO_ID_LOAD_CONTROL;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_load_control_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[1] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[2] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[3] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[4] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[5] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_EVENT_IDENTIFIER;
    p_instance->resource_ids[1] = IPSO_RR_ID_START_TIME;
    p_instance->resource_ids[2] = IPSO_RR_ID_DURATION_IN_MIN;
    p_instance->resource_ids[3] = IPSO_RR_ID_CRITICALITY_LEVEL;
    p_instance->resource_ids[4] = IPSO_RR_ID_AVG_LOAD_ADJPCT;
    p_instance->resource_ids[5] = IPSO_RR_ID_DUTY_CYCLE;
}

void ipso_instance_light_control_init(ipso_light_control_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_light_control_t);

    p_instance->proto.object_id     = IPSO_SO_ID_LIGHT_CONTROL;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_light_control_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[1] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[2] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[5] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[6] = LWM2M_OPERATION_CODE_READ;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_ON_OFF;
    p_instance->resource_ids[1] = IPSO_RR_ID_DIMMER;
    p_instance->resource_ids[2] = IPSO_RR_ID_COLOUR;
    p_instance->resource_ids[3] = IPSO_RR_ID_SENSOR_UNITS;
    p_instance->resource_ids[4] = IPSO_RR_ID_ON_TIME;
    p_instance->resource_ids[5] = IPSO_RR_ID_CUMULATIVE_ACTIVE_POWER;
    p_instance->resource_ids[6] = IPSO_RR_ID_POWER_FACTOR;
}

void ipso_instance_power_control_init(ipso_power_control_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_power_control_t);

    p_instance->proto.object_id     = IPSO_SO_ID_POWER_CONTROL;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_power_control_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[1] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[2] = (LWM2M_OPERATION_CODE_READ | LWM2M_OPERATION_CODE_WRITE);
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_ON_OFF;
    p_instance->resource_ids[1] = IPSO_RR_ID_DIMMER;
    p_instance->resource_ids[2] = IPSO_RR_ID_ON_TIME;
    p_instance->resource_ids[3] = IPSO_RR_ID_CUMULATIVE_ACTIVE_POWER;
    p_instance->resource_ids[4] = IPSO_RR_ID_POWER_FACTOR;
}

void ipso_instance_accelerometer_init(ipso_accelerometer_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_accelerometer_t);

    p_instance->proto.object_id     = IPSO_SO_ID_ACCELEROMETER;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_accelerometer_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[5] = LWM2M_OPERATION_CODE_READ;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_X_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_Y_VALUE;
    p_instance->resource_ids[2] = IPSO_RR_ID_Z_VALUE;
    p_instance->resource_ids[3] = IPSO_RR_ID_SENSOR_UNITS;
    p_instance->resource_ids[4] = IPSO_RR_ID_MIN_RANGE_VALUE;
    p_instance->resource_ids[5] = IPSO_RR_ID_MAX_RANGE_VALUE;
}

void ipso_instance_magnetometer_init(ipso_magnetometer_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_magnetometer_t);

    p_instance->proto.object_id     = IPSO_SO_ID_MAGNETOMETER;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_magnetometer_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;

    // Set resource IDs.
    p_instance->resource_ids[0] = IPSO_RR_ID_X_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_Y_VALUE;
    p_instance->resource_ids[2] = IPSO_RR_ID_Z_VALUE;
    p_instance->resource_ids[3] = IPSO_RR_ID_SENSOR_UNITS;
    p_instance->resource_ids[4] = IPSO_RR_ID_COMPASS_DIRECTION;
}

void ipso_instance_barometer_init(ipso_barometer_t * p_instance)
{
    // Set prototype variables.
    LWM2M_INSTANCE_OFFSET_SET(p_instance, ipso_barometer_t);

    p_instance->proto.object_id     = IPSO_SO_ID_BAROMETER;
    p_instance->proto.instance_id   = 0;
    p_instance->proto.num_resources = sizeof(((ipso_barometer_t *)0)->operations);

    // Set access types.
    p_instance->operations[0] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[1] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[2] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[3] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[4] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[5] = LWM2M_OPERATION_CODE_READ;
    p_instance->operations[6] = LWM2M_OPERATION_CODE_EXECUTE;

    // Set resource IDs.


    p_instance->resource_ids[0] = IPSO_RR_ID_SENSOR_VALUE;
    p_instance->resource_ids[1] = IPSO_RR_ID_SENSOR_UNITS;
    p_instance->resource_ids[2] = IPSO_RR_ID_MIN_MEASURED_VALUE;
    p_instance->resource_ids[3] = IPSO_RR_ID_MAX_MEASURED_VALUE;
    p_instance->resource_ids[4] = IPSO_RR_ID_MIN_RANGE_VALUE;
    p_instance->resource_ids[5] = IPSO_RR_ID_MAX_RANGE_VALUE;
    p_instance->resource_ids[6] = IPSO_RR_ID_RESET_MIN_MAX_MEASURED_VALUES;
}
