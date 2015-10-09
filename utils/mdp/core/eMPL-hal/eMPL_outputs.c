/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */

/**
 *   @defgroup  HAL_Outputs hal_outputs
 *   @brief     Motion Library - HAL Outputs
 *              Sets up common outputs for HAL
 *
 *   @{
 *       @file eMPL_outputs.c
 *       @brief Embedded MPL outputs.
 */
#include "eMPL_outputs.h"
#include "ml_math_func.h"
#include "mlmath.h"
#include "start_manager.h"
#include "data_builder.h"
#include "results_holder.h"

struct eMPL_output_s {
    long quat[4];
    int quat_accuracy;
    int gyro_status;
    int accel_status;
    int compass_status;
    int nine_axis_status;
    inv_time_t nine_axis_timestamp;
};

static struct eMPL_output_s eMPL_out;

/**
 *  @brief      Acceleration (g's) in body frame.
 *  Embedded MPL defines gravity as positive acceleration pointing away from
 *  the Earth.
 *  @param[out] data        Acceleration in g's, q16 fixed point.
 *  @param[out] accuracy    Accuracy of the measurement from 0 (least accurate)
 *                          to 3 (most accurate).
 *  @param[out] timestamp   The time in milliseconds when this sensor was read.
 *  @return     1 if data was updated.
 */
int inv_get_sensor_type_accel(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    inv_get_accel_set(data, accuracy, timestamp);
    if (eMPL_out.accel_status & INV_NEW_DATA)
        return 1;
    else
        return 0;
}

/**
 *  @brief      Angular velocity (degrees per second) in body frame.
 *  @param[out] data        Angular velocity in dps, q16 fixed point.
 *  @param[out] accuracy    Accuracy of the measurement from 0 (least accurate)
 *                          to 3 (most accurate).
 *  @param[out] timestamp   The time in milliseconds when this sensor was read.
 *  @return     1 if data was updated. 
 */
int inv_get_sensor_type_gyro(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    inv_get_gyro_set(data, accuracy, timestamp);
    if (eMPL_out.gyro_status & INV_NEW_DATA)
        return 1;
    else
        return 0;
}

/**
 *  @brief      Magnetic field strength in body frame.
 *  @param[out] data        Field strength in microteslas, q16 fixed point.
 *  @param[out] accuracy    Accuracy of the measurement from 0 (least accurate)
 *                          to 3 (most accurate).
 *  @param[out] timestamp   The time in milliseconds when this sensor was read.
 *  @return     1 if data was updated. 
 */
int inv_get_sensor_type_compass(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    inv_get_compass_set(data, accuracy, timestamp);
    if (eMPL_out.compass_status & INV_NEW_DATA)
        return 1;
    else
        return 0;
}

/**
 *  @brief      Body-to-world frame quaternion.
 *  The elements are output in the following order: W, X, Y, Z.
 *  @param[out] data        Quaternion, q30 fixed point.
 *  @param[out] accuracy    Accuracy of the measurement from 0 (least accurate)
 *                          to 3 (most accurate).
 *  @param[out] timestamp   The time in milliseconds when this sensor was read.
 *  @return     1 if data was updated. 
 */
int inv_get_sensor_type_quat(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    memcpy(data, eMPL_out.quat, sizeof(eMPL_out.quat));
    accuracy[0] = eMPL_out.quat_accuracy;
    timestamp[0] = eMPL_out.nine_axis_timestamp;
    return eMPL_out.nine_axis_status;
}

/**
 *  @brief      Quaternion-derived heading.
 *  @param[out] data        Heading in degrees, q16 fixed point.
 *  @param[out] accuracy    Accuracy of the measurement from 0 (least accurate)
 *                          to 3 (most accurate).
 *  @param[out] timestamp   The time in milliseconds when this sensor was read.
 *  @return     1 if data was updated. 
 */
int inv_get_sensor_type_heading(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    long t1, t2, q00, q03, q12, q22;
    float fdata;

    q00 = inv_q29_mult(eMPL_out.quat[0], eMPL_out.quat[0]);
    q03 = inv_q29_mult(eMPL_out.quat[0], eMPL_out.quat[3]);
    q12 = inv_q29_mult(eMPL_out.quat[1], eMPL_out.quat[2]);
    q22 = inv_q29_mult(eMPL_out.quat[2], eMPL_out.quat[2]);

    /* X component of the Ybody axis in World frame */
    t1 = q12 - q03;

    /* Y component of the Ybody axis in World frame */
    t2 = q22 + q00 - (1L << 30);
    fdata = atan2f((float) t1, (float) t2) * 180.f / (float) M_PI;
    if (fdata < 0.f)
        fdata += 360.f;
    data[0] = (long)(fdata * 65536.f);

    accuracy[0] = eMPL_out.quat_accuracy;
    timestamp[0] = eMPL_out.nine_axis_timestamp;
    return eMPL_out.nine_axis_status;
}

/**
 *  @brief      Body-to-world frame euler angles.
 *  The euler angles are output with the following convention:
 *  Pitch: -180 to 180
 *  Roll: -90 to 90
 *  Yaw: -180 to 180
 *  @param[out] data        Euler angles in degrees, q16 fixed point.
 *  @param[out] accuracy    Accuracy of the measurement from 0 (least accurate)
 *                          to 3 (most accurate).
 *  @param[out] timestamp   The time in milliseconds when this sensor was read.
 *  @return     1 if data was updated.
 */
int inv_get_sensor_type_euler(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    long t1, t2, t3;
    long q00, q01, q02, q03, q11, q12, q13, q22, q23, q33;
    float values[3];

    q00 = inv_q29_mult(eMPL_out.quat[0], eMPL_out.quat[0]);
    q01 = inv_q29_mult(eMPL_out.quat[0], eMPL_out.quat[1]);
    q02 = inv_q29_mult(eMPL_out.quat[0], eMPL_out.quat[2]);
    q03 = inv_q29_mult(eMPL_out.quat[0], eMPL_out.quat[3]);
    q11 = inv_q29_mult(eMPL_out.quat[1], eMPL_out.quat[1]);
    q12 = inv_q29_mult(eMPL_out.quat[1], eMPL_out.quat[2]);
    q13 = inv_q29_mult(eMPL_out.quat[1], eMPL_out.quat[3]);
    q22 = inv_q29_mult(eMPL_out.quat[2], eMPL_out.quat[2]);
    q23 = inv_q29_mult(eMPL_out.quat[2], eMPL_out.quat[3]);
    q33 = inv_q29_mult(eMPL_out.quat[3], eMPL_out.quat[3]);

    /* X component of the Ybody axis in World frame */
    t1 = q12 - q03;

    /* Y component of the Ybody axis in World frame */
    t2 = q22 + q00 - (1L << 30);
    values[2] = -atan2f((float) t1, (float) t2) * 180.f / (float) M_PI;

    /* Z component of the Ybody axis in World frame */
    t3 = q23 + q01;
    values[0] =
        atan2f((float) t3,
                sqrtf((float) t1 * t1 +
                      (float) t2 * t2)) * 180.f / (float) M_PI;
    /* Z component of the Zbody axis in World frame */
    t2 = q33 + q00 - (1L << 30);
    if (t2 < 0) {
        if (values[0] >= 0)
            values[0] = 180.f - values[0];
        else
            values[0] = -180.f - values[0];
    }

    /* X component of the Xbody axis in World frame */
    t1 = q11 + q00 - (1L << 30);
    /* Y component of the Xbody axis in World frame */
    t2 = q12 + q03;
    /* Z component of the Xbody axis in World frame */
    t3 = q13 - q02;

    values[1] =
        (atan2f((float)(q33 + q00 - (1L << 30)), (float)(q13 - q02)) *
          180.f / (float) M_PI - 90);
    if (values[1] >= 90)
        values[1] = 180 - values[1];

    if (values[1] < -90)
        values[1] = -180 - values[1];
    data[0] = (long)(values[0] * 65536.f);
    data[1] = (long)(values[1] * 65536.f);
    data[2] = (long)(values[2] * 65536.f);

    accuracy[0] = eMPL_out.quat_accuracy;
    timestamp[0] = eMPL_out.nine_axis_timestamp;
    return eMPL_out.nine_axis_status;
}

/**
 *  @brief      Body-to-world frame rotation matrix.
 *  @param[out] data        Rotation matrix, q30 fixed point.
 *  @param[out] accuracy    Accuracy of the measurement from 0 (least accurate)
 *                          to 3 (most accurate).
 *  @param[out] timestamp   The time in milliseconds when this sensor was read.
 *  @return     1 if data was updated.
 */
int inv_get_sensor_type_rot_mat(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    inv_quaternion_to_rotation(eMPL_out.quat, data);
    accuracy[0] = eMPL_out.quat_accuracy;
    timestamp[0] = eMPL_out.nine_axis_timestamp;
    return eMPL_out.nine_axis_status;
}

static inv_error_t inv_generate_eMPL_outputs
    (struct inv_sensor_cal_t *sensor_cal)
{
    int use_sensor;
    long sr = 1000;
    inv_get_quaternion_set(eMPL_out.quat, &eMPL_out.quat_accuracy, &eMPL_out.nine_axis_timestamp);
    eMPL_out.gyro_status = sensor_cal->gyro.status;
    eMPL_out.accel_status = sensor_cal->accel.status;
    eMPL_out.compass_status = sensor_cal->compass.status;
    
    /* Find the highest sample rate and tie sensor fusion timestamps to that one. */
    if (sensor_cal->gyro.status & INV_SENSOR_ON) {
        sr = sensor_cal->gyro.sample_rate_ms;
        use_sensor = 0;
    }
    if ((sensor_cal->accel.status & INV_SENSOR_ON) && (sr > sensor_cal->accel.sample_rate_ms)) {
        sr = sensor_cal->accel.sample_rate_ms;
        use_sensor = 1;
    }
    if ((sensor_cal->compass.status & INV_SENSOR_ON) && (sr > sensor_cal->compass.sample_rate_ms)) {
        sr = sensor_cal->compass.sample_rate_ms;
        use_sensor = 2;
    }
    if ((sensor_cal->quat.status & INV_SENSOR_ON) && (sr > sensor_cal->quat.sample_rate_ms)) {
        sr = sensor_cal->quat.sample_rate_ms;
        use_sensor = 3;
    }

    switch (use_sensor) {
    default:
    case 0:
        eMPL_out.nine_axis_status = (sensor_cal->gyro.status & INV_NEW_DATA) ? 1 : 0;
        eMPL_out.nine_axis_timestamp = sensor_cal->gyro.timestamp;
        break;
    case 1:
        eMPL_out.nine_axis_status = (sensor_cal->accel.status & INV_NEW_DATA) ? 1 : 0;
        eMPL_out.nine_axis_timestamp = sensor_cal->accel.timestamp;
        break;
    case 2:
        eMPL_out.nine_axis_status = (sensor_cal->compass.status & INV_NEW_DATA) ? 1 : 0;
        eMPL_out.nine_axis_timestamp = sensor_cal->compass.timestamp;
        break;
    case 3:
        eMPL_out.nine_axis_status = (sensor_cal->quat.status & INV_NEW_DATA) ? 1 : 0;
        eMPL_out.nine_axis_timestamp = sensor_cal->quat.timestamp;
        break;
    }
    
    
    return INV_SUCCESS;
}

static inv_error_t inv_start_eMPL_outputs(void)
{
    return inv_register_data_cb(inv_generate_eMPL_outputs,
        INV_PRIORITY_HAL_OUTPUTS, INV_GYRO_NEW | INV_ACCEL_NEW | INV_MAG_NEW);
}

static inv_error_t inv_stop_eMPL_outputs(void)
{
    return inv_unregister_data_cb(inv_generate_eMPL_outputs);
}

static inv_error_t inv_init_eMPL_outputs(void)
{
    memset(&eMPL_out, 0, sizeof(eMPL_out));
    return INV_SUCCESS;
}

/**
 *  @brief  Turns on creation and storage of HAL type results.
 */
inv_error_t inv_enable_eMPL_outputs(void)
{
    inv_error_t result;
    result = inv_init_eMPL_outputs();
    if (result)
        return result;
    return inv_register_mpl_start_notification(inv_start_eMPL_outputs);
}

/**
 *  @brief  Turns off creation and storage of HAL type results.
 */
inv_error_t inv_disable_eMPL_outputs(void)
{
    inv_stop_eMPL_outputs();
    return inv_unregister_mpl_start_notification(inv_start_eMPL_outputs);
}

/**
 * @}
 */