/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
/**
 *   @defgroup  HAL_Outputs
 *   @brief     Motion Library - HAL Outputs
 *              Sets up common outputs for HAL
 *
 *   @{
 *       @file  eMPL_outputs.h
 *       @brief Embedded MPL outputs.
 */
#ifndef _EMPL_OUTPUTS_H_
#define _EMPL_OUTPUTS_H_

#include "mltypes.h"

#ifdef __cplusplus
extern "C" {
#endif

    int inv_get_sensor_type_accel(long *data, int8_t *accuracy, inv_time_t *timestamp);
    int inv_get_sensor_type_gyro(long *data, int8_t *accuracy, inv_time_t *timestamp);
    int inv_get_sensor_type_compass(long *data, int8_t *accuracy, inv_time_t *timestamp);
    int inv_get_sensor_type_quat(long *data, int8_t *accuracy, inv_time_t *timestamp);
    int inv_get_sensor_type_euler(long *data, int8_t *accuracy, inv_time_t *timestamp);
    int inv_get_sensor_type_rot_mat(long *data, int8_t *accuracy, inv_time_t *timestamp);
    int inv_get_sensor_type_heading(long *data, int8_t *accuracy, inv_time_t *timestamp);

    inv_error_t inv_enable_eMPL_outputs(void);
    inv_error_t inv_disable_eMPL_outputs(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef _EMPL_OUTPUTS_H_ */

/**
 *  @}
 */