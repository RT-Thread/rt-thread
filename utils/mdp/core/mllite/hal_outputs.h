/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
#include "mltypes.h"

#ifndef INV_HAL_OUTPUTS_H__
#define INV_HAL_OUTPUTS_H__

#ifdef __cplusplus
extern "C" {
#endif

    int inv_get_sensor_type_orientation(float *values, int8_t *accuracy,
                                         inv_time_t * timestamp);
    int inv_get_sensor_type_accelerometer(float *values, int8_t *accuracy,
                                           inv_time_t * timestamp);
    int inv_get_sensor_type_gyroscope(float *values, int8_t *accuracy,
                                       inv_time_t * timestamp);
    int inv_get_sensor_type_gyroscope_raw(float *values, int8_t *accuracy,
                                       inv_time_t * timestamp);
    int inv_get_sensor_type_magnetic_field(float *values, int8_t *accuracy,
                                            inv_time_t * timestamp);
    int inv_get_sensor_type_rotation_vector(float *values, int8_t *accuracy,
            inv_time_t * timestamp);

    int inv_get_sensor_type_linear_acceleration(float *values,
            int8_t *accuracy,
            inv_time_t * timestamp);
    int inv_get_sensor_type_gravity(float *values, int8_t *accuracy,
                                     inv_time_t * timestamp);

    inv_error_t inv_enable_hal_outputs(void);
    inv_error_t inv_disable_hal_outputs(void);
    inv_error_t inv_init_hal_outputs(void);
    inv_error_t inv_start_hal_outputs(void);
    inv_error_t inv_stop_hal_outputs(void);

#ifdef __cplusplus
}
#endif

#endif                          // INV_HAL_OUTPUTS_H__