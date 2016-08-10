/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
 
/**
 *   @defgroup  Data_Builder data_builder
 *   @brief     Motion Library - Data Builder
 *              Constructs and Creates the data for MPL
 *
 *   @{
 *       @file data_builder.c
 *       @brief Data Builder.
 */

#undef MPL_LOG_NDEBUG
#define MPL_LOG_NDEBUG 0 /* Use 0 to turn on MPL_LOGV output */

#include <string.h>

#include "ml_math_func.h"
#include "data_builder.h"
#include "mlmath.h"
#include "storage_manager.h"
#include "message_layer.h"
#include "results_holder.h"

#include "log.h"
#undef MPL_LOG_TAG
#define MPL_LOG_TAG "MPL"

typedef inv_error_t (*inv_process_cb_func)(struct inv_sensor_cal_t *data);

struct process_t {
    inv_process_cb_func func;
    int priority;
    int data_required;
};

struct inv_db_save_t {
    /** Compass Bias in Chip Frame in Hardware units scaled by 2^16 */
    long compass_bias[3];
    /** Gyro Bias in Chip Frame in Hardware units scaled by 2^16 */
    long gyro_bias[3];
    /** Temperature when *gyro_bias was stored. */
    long gyro_temp;
    /** Flag to indicate temperature compensation that biases where stored. */
    int gyro_bias_tc_set;
    /** Accel Bias in Chip Frame in Hardware units scaled by 2^16 */
    long accel_bias[3];
    /** Temperature when accel bias was stored. */
    long accel_temp;
    long gyro_temp_slope[3];
    /** Sensor Accuracy */
    int gyro_accuracy;
    int accel_accuracy;
    int compass_accuracy;
};

struct inv_data_builder_t {
    int num_cb;
    struct process_t process[INV_MAX_DATA_CB];
    struct inv_db_save_t save;
    int compass_disturbance;
#ifdef INV_PLAYBACK_DBG
    int debug_mode;
    int last_mode;
    FILE *file;
#endif
};

void inv_apply_calibration(struct inv_single_sensor_t *sensor, const long *bias);
static void inv_set_contiguous(void);

static struct inv_data_builder_t inv_data_builder;
static struct inv_sensor_cal_t sensors;

/** Change this key if the data being stored by this file changes */
#define INV_DB_SAVE_KEY 53395

#ifdef INV_PLAYBACK_DBG

/** Turn on data logging to allow playback of same scenario at a later time.
* @param[in] file File to write to, must be open.
*/
void inv_turn_on_data_logging(FILE *file)
{
    MPL_LOGV("input data logging started\n");
    inv_data_builder.file = file;
    inv_data_builder.debug_mode = RD_RECORD;
}

/** Turn off data logging to allow playback of same scenario at a later time.
* File passed to inv_turn_on_data_logging() must be closed after calling this.
*/
void inv_turn_off_data_logging()
{
    MPL_LOGV("input data logging stopped\n");
    inv_data_builder.debug_mode = RD_NO_DEBUG;
    inv_data_builder.file = NULL;
}
#endif

/** This function receives the data that was stored in non-volatile memory between power off */
static inv_error_t inv_db_load_func(const unsigned char *data)
{
    memcpy(&inv_data_builder.save, data, sizeof(inv_data_builder.save));
    // copy in the saved accuracy in the actual sensors accuracy
    sensors.gyro.accuracy = inv_data_builder.save.gyro_accuracy;
    sensors.accel.accuracy = inv_data_builder.save.accel_accuracy;
    sensors.compass.accuracy = inv_data_builder.save.compass_accuracy;
    // TODO
    if (sensors.compass.accuracy == 3) {
        inv_set_compass_bias_found(1);
    }
    return INV_SUCCESS;
}

/** This function returns the data to be stored in non-volatile memory between power off */
static inv_error_t inv_db_save_func(unsigned char *data)
{
    memcpy(data, &inv_data_builder.save, sizeof(inv_data_builder.save));
    return INV_SUCCESS;
}

/** Initialize the data builder
*/
inv_error_t inv_init_data_builder(void)
{
    /* TODO: Hardcode temperature scale/offset here. */
    memset(&inv_data_builder, 0, sizeof(inv_data_builder));
    memset(&sensors, 0, sizeof(sensors));

    // disable the soft iron transform process
    inv_reset_compass_soft_iron_matrix();

    return inv_register_load_store(inv_db_load_func, inv_db_save_func,
                                   sizeof(inv_data_builder.save),
                                   INV_DB_SAVE_KEY);
}

/** Gyro sensitivity.
* @return A scale factor to convert device units to degrees per second scaled by 2^16
* such that degrees_per_second  = device_units * sensitivity / 2^30. Typically
* it works out to be the maximum rate * 2^15.
*/
long inv_get_gyro_sensitivity()
{
    return sensors.gyro.sensitivity;
}

/** Accel sensitivity.
* @return A scale factor to convert device units to g's scaled by 2^16
* such that g_s  = device_units * sensitivity / 2^30. Typically
* it works out to be the maximum accel value in g's * 2^15.
*/
long inv_get_accel_sensitivity(void)
{
    return sensors.accel.sensitivity;
}

/** Compass sensitivity.
* @return A scale factor to convert device units to micro Tesla scaled by 2^16
* such that uT  = device_units * sensitivity / 2^30. Typically
* it works out to be the maximum uT * 2^15.
*/
long inv_get_compass_sensitivity(void)
{
    return sensors.compass.sensitivity;
}

/** Sets orientation and sensitivity field for a sensor.
* @param[out] sensor Structure to apply settings to
* @param[in] orientation Orientation description of how part is mounted.
* @param[in] sensitivity A Scale factor to convert from hardware units to
*            standard units (dps, uT, g).
*/
void set_sensor_orientation_and_scale(struct inv_single_sensor_t *sensor,
                                 int orientation, long sensitivity)
{
    sensor->sensitivity = sensitivity;
    sensor->orientation = orientation;
}

/** Sets the Orientation and Sensitivity of the gyro data.
* @param[in] orientation A scalar defining the transformation from chip mounting
*            to the body frame. The function inv_orientation_matrix_to_scalar()
*            can convert the transformation matrix to this scalar and describes the
*            scalar in further detail.
* @param[in] sensitivity A scale factor to convert device units to degrees per second scaled by 2^16
*            such that degrees_per_second  = device_units * sensitivity / 2^30. Typically
*            it works out to be the maximum rate * 2^15.
*/
void inv_set_gyro_orientation_and_scale(int orientation, long sensitivity)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_G_ORIENT;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(&orientation, sizeof(orientation), 1, inv_data_builder.file);
        fwrite(&sensitivity, sizeof(sensitivity), 1, inv_data_builder.file);
    }
#endif
    set_sensor_orientation_and_scale(&sensors.gyro, orientation,
                                     sensitivity);
}

/** Set Gyro Sample rate in micro seconds.
* @param[in] sample_rate_us Set Gyro Sample rate in us
*/
void inv_set_gyro_sample_rate(long sample_rate_us)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_G_SAMPLE_RATE;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(&sample_rate_us, sizeof(sample_rate_us), 1, inv_data_builder.file);
    }
#endif
    sensors.gyro.sample_rate_us = sample_rate_us;
    sensors.gyro.sample_rate_ms = sample_rate_us / 1000;
    if (sensors.gyro.bandwidth == 0) {
        sensors.gyro.bandwidth = (int)(1000000L / sample_rate_us);
    }
}

/** Set Accel Sample rate in micro seconds.
* @param[in] sample_rate_us Set Accel Sample rate in us
*/
void inv_set_accel_sample_rate(long sample_rate_us)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_A_SAMPLE_RATE;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(&sample_rate_us, sizeof(sample_rate_us), 1, inv_data_builder.file);
    }
#endif
    sensors.accel.sample_rate_us = sample_rate_us;
    sensors.accel.sample_rate_ms = sample_rate_us / 1000;
    if (sensors.accel.bandwidth == 0) {
        sensors.accel.bandwidth = (int)(1000000L / sample_rate_us);
    }
}

/** Set Compass Sample rate in micro seconds.
* @param[in] sample_rate_us Set Gyro Sample rate in micro seconds.
*/
void inv_set_compass_sample_rate(long sample_rate_us)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_C_SAMPLE_RATE;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(&sample_rate_us, sizeof(sample_rate_us), 1, inv_data_builder.file);
    }
#endif
    sensors.compass.sample_rate_us = sample_rate_us;
    sensors.compass.sample_rate_ms = sample_rate_us / 1000;
    if (sensors.compass.bandwidth == 0) {
        sensors.compass.bandwidth = (int)(1000000L / sample_rate_us);
    }
}

void inv_get_gyro_sample_rate_ms(long *sample_rate_ms)
{
	*sample_rate_ms = sensors.gyro.sample_rate_ms;
}

void inv_get_accel_sample_rate_ms(long *sample_rate_ms)
{
	*sample_rate_ms = sensors.accel.sample_rate_ms;
}

void inv_get_compass_sample_rate_ms(long *sample_rate_ms)
{
	*sample_rate_ms = sensors.compass.sample_rate_ms;
}

/** Set Quat Sample rate in micro seconds.
* @param[in] sample_rate_us Set Quat Sample rate in us
*/
void inv_set_quat_sample_rate(long sample_rate_us)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_Q_SAMPLE_RATE;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(&sample_rate_us, sizeof(sample_rate_us), 1, inv_data_builder.file);
    }
#endif
    sensors.quat.sample_rate_us = sample_rate_us;
    sensors.quat.sample_rate_ms = sample_rate_us / 1000;
}

/** Set Gyro Bandwidth in Hz
* @param[in] bandwidth_hz Gyro bandwidth in Hz
*/
void inv_set_gyro_bandwidth(int bandwidth_hz)
{
    sensors.gyro.bandwidth = bandwidth_hz;
}

/** Set Accel Bandwidth in Hz
* @param[in] bandwidth_hz Gyro bandwidth in Hz
*/
void inv_set_accel_bandwidth(int bandwidth_hz)
{
    sensors.accel.bandwidth = bandwidth_hz;
}

/** Set Compass Bandwidth in Hz
* @param[in]  bandwidth_hz Gyro bandwidth in Hz
*/
void inv_set_compass_bandwidth(int bandwidth_hz)
{
    sensors.compass.bandwidth = bandwidth_hz;
}

/** Helper function stating whether the compass is on or off.
 * @return TRUE if compass if on, 0 if compass if off
*/
int inv_get_compass_on()
{
    return (sensors.compass.status & INV_SENSOR_ON) == INV_SENSOR_ON;
}

/** Helper function stating whether the gyro is on or off.
 * @return TRUE if gyro if on, 0 if gyro if off
*/
int inv_get_gyro_on()
{
    return (sensors.gyro.status & INV_SENSOR_ON) == INV_SENSOR_ON;
}

/** Helper function stating whether the acceleromter is on or off.
 * @return TRUE if accel if on, 0 if accel if off
*/
int inv_get_accel_on()
{
    return (sensors.accel.status & INV_SENSOR_ON) == INV_SENSOR_ON;
}

/** Get last timestamp across all 3 sensors that are on.
* This find out which timestamp has the largest value for sensors that are on.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_time_t inv_get_last_timestamp()
{
    inv_time_t timestamp = 0;
    if (sensors.accel.status & INV_SENSOR_ON) {
        timestamp = sensors.accel.timestamp;
    }
    if (sensors.gyro.status & INV_SENSOR_ON) {
        if (timestamp < sensors.gyro.timestamp) {
            timestamp = sensors.gyro.timestamp;
        }
    }
    if (sensors.compass.status & INV_SENSOR_ON) {
        if (timestamp < sensors.compass.timestamp) {
            timestamp = sensors.compass.timestamp;
        }
    }
    if (sensors.temp.status & INV_SENSOR_ON) {
        if (timestamp < sensors.temp.timestamp)
            timestamp = sensors.temp.timestamp;
    }
    return timestamp;
}

/** Sets the orientation and sensitivity of the gyro data.
* @param[in] orientation A scalar defining the transformation from chip mounting
*            to the body frame. The function inv_orientation_matrix_to_scalar()
*            can convert the transformation matrix to this scalar and describes the
*            scalar in further detail.
* @param[in] sensitivity A scale factor to convert device units to g's
*            such that g's = device_units * sensitivity / 2^30. Typically
*            it works out to be the maximum g_value * 2^15.
*/
void inv_set_accel_orientation_and_scale(int orientation, long sensitivity)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_A_ORIENT;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(&orientation, sizeof(orientation), 1, inv_data_builder.file);
        fwrite(&sensitivity, sizeof(sensitivity), 1, inv_data_builder.file);
    }
#endif
    set_sensor_orientation_and_scale(&sensors.accel, orientation,
                                     sensitivity);
}

/** Sets the Orientation and Sensitivity of the gyro data.
* @param[in] orientation A scalar defining the transformation from chip mounting
*            to the body frame. The function inv_orientation_matrix_to_scalar()
*            can convert the transformation matrix to this scalar and describes the
*            scalar in further detail.
* @param[in] sensitivity A scale factor to convert device units to uT
*            such that uT = device_units * sensitivity / 2^30. Typically
*            it works out to be the maximum uT_value * 2^15.
*/
void inv_set_compass_orientation_and_scale(int orientation, long sensitivity)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_C_ORIENT;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(&orientation, sizeof(orientation), 1, inv_data_builder.file);
        fwrite(&sensitivity, sizeof(sensitivity), 1, inv_data_builder.file);
    }
#endif
    set_sensor_orientation_and_scale(&sensors.compass, orientation, sensitivity);
}

void inv_matrix_vector_mult(const long *A, const long *x, long *y)
{
    y[0] = inv_q30_mult(A[0], x[0]) + inv_q30_mult(A[1], x[1]) + inv_q30_mult(A[2], x[2]);
    y[1] = inv_q30_mult(A[3], x[0]) + inv_q30_mult(A[4], x[1]) + inv_q30_mult(A[5], x[2]);
    y[2] = inv_q30_mult(A[6], x[0]) + inv_q30_mult(A[7], x[1]) + inv_q30_mult(A[8], x[2]);
}

/** Takes raw data stored in the sensor, removes bias, and converts it to
* calibrated data in the body frame. Also store raw data for body frame.
* @param[in,out] sensor structure to modify
* @param[in] bias bias in the mounting frame, in hardware units scaled by
*                 2^16. Length 3.
*/
void inv_apply_calibration(struct inv_single_sensor_t *sensor, const long *bias)
{
    long raw32[3];

    // Convert raw to calibrated
    raw32[0] = (long)sensor->raw[0] << 15;
    raw32[1] = (long)sensor->raw[1] << 15;
    raw32[2] = (long)sensor->raw[2] << 15;

    inv_convert_to_body_with_scale(sensor->orientation, sensor->sensitivity << 1, raw32, sensor->raw_scaled);

    raw32[0] -= bias[0] >> 1;
    raw32[1] -= bias[1] >> 1;
    raw32[2] -= bias[2] >> 1;

    inv_convert_to_body_with_scale(sensor->orientation, sensor->sensitivity << 1, raw32, sensor->calibrated);

    sensor->status |= INV_CALIBRATED;
}

/** Returns the current bias for the compass
* @param[out] bias Compass bias in hardware units scaled by 2^16. In mounting frame.
*             Length 3.
*/
void inv_get_compass_bias(long *bias)
{
    if (bias != NULL) {
        memcpy(bias, inv_data_builder.save.compass_bias, sizeof(inv_data_builder.save.compass_bias));
    }
}

void inv_set_compass_bias(const long *bias, int accuracy)
{
    if (memcmp(inv_data_builder.save.compass_bias, bias, sizeof(inv_data_builder.save.compass_bias))) {
        memcpy(inv_data_builder.save.compass_bias, bias, sizeof(inv_data_builder.save.compass_bias));
        inv_apply_calibration(&sensors.compass, inv_data_builder.save.compass_bias);
    }
    sensors.compass.accuracy = accuracy;
    inv_data_builder.save.compass_accuracy = accuracy;
    inv_set_message(INV_MSG_NEW_CB_EVENT, INV_MSG_NEW_CB_EVENT, 0);
}

/** Set the state of a compass disturbance
* @param[in] dist 1=disturbance, 0=no disturbance
*/
void inv_set_compass_disturbance(int dist)
{
    inv_data_builder.compass_disturbance = dist;
}

int inv_get_compass_disturbance(void) {
    return inv_data_builder.compass_disturbance;
}
/** Sets the accel bias.
* @param[in] bias Accel bias, length 3. In HW units scaled by 2^16 in body frame
* @param[in] accuracy Accuracy rating from 0 to 3, with 3 being most accurate.
*/
void inv_set_accel_bias(const long *bias, int accuracy)
{
    if (bias) {
        if (memcmp(inv_data_builder.save.accel_bias, bias, sizeof(inv_data_builder.save.accel_bias))) {
            memcpy(inv_data_builder.save.accel_bias, bias, sizeof(inv_data_builder.save.accel_bias));
            inv_apply_calibration(&sensors.accel, inv_data_builder.save.accel_bias);
        }
    }
    sensors.accel.accuracy = accuracy;
    inv_data_builder.save.accel_accuracy = accuracy;
    inv_set_message(INV_MSG_NEW_AB_EVENT, INV_MSG_NEW_AB_EVENT, 0);
}

/** Sets the accel accuracy.
* @param[in] accuracy Accuracy rating from 0 to 3, with 3 being most accurate.
*/
void inv_set_accel_accuracy(int accuracy)
{
    sensors.accel.accuracy = accuracy;
    inv_data_builder.save.accel_accuracy = accuracy;
    inv_set_message(INV_MSG_NEW_AB_EVENT, INV_MSG_NEW_AB_EVENT, 0);
}

/** Sets the accel bias with control over which axis.
* @param[in] bias Accel bias, length 3. In HW units scaled by 2^16 in body frame
* @param[in] accuracy Accuracy rating from 0 to 3, with 3 being most accurate.
* @param[in] mask Mask to select axis to apply bias set.
*/
void inv_set_accel_bias_mask(const long *bias, int accuracy, int mask)
{
    if (bias) {
        if (mask & 1){
            inv_data_builder.save.accel_bias[0] = bias[0];
        }
        if (mask & 2){
            inv_data_builder.save.accel_bias[1] = bias[1];
        }
        if (mask & 4){
            inv_data_builder.save.accel_bias[2] = bias[2];
        }

        inv_apply_calibration(&sensors.accel, inv_data_builder.save.accel_bias);
    }
    sensors.accel.accuracy = accuracy;
    inv_data_builder.save.accel_accuracy = accuracy;
    inv_set_message(INV_MSG_NEW_AB_EVENT, INV_MSG_NEW_AB_EVENT, 0);
}


/** Sets the gyro bias
* @param[in] bias Gyro bias in hardware units scaled by 2^16. In chip mounting frame.
*            Length 3.
* @param[in] accuracy Accuracy of bias. 0 = least accurate, 3 = most accurate.
*/
void inv_set_gyro_bias(const long *bias, int accuracy)
{
    if (bias != NULL) {
        if (memcmp(inv_data_builder.save.gyro_bias, bias, sizeof(inv_data_builder.save.gyro_bias))) {
            memcpy(inv_data_builder.save.gyro_bias, bias, sizeof(inv_data_builder.save.gyro_bias));
            inv_apply_calibration(&sensors.gyro, inv_data_builder.save.gyro_bias);
        }
    }
    sensors.gyro.accuracy = accuracy;
    inv_data_builder.save.gyro_accuracy = accuracy;

    /* TODO: What should we do if there's no temperature data? */
    if (sensors.temp.calibrated[0])
        inv_data_builder.save.gyro_temp = sensors.temp.calibrated[0];
    else
        /* Set to 27 deg C for now until we've got a better solution. */
        inv_data_builder.save.gyro_temp = 1769472L;
    inv_set_message(INV_MSG_NEW_GB_EVENT, INV_MSG_NEW_GB_EVENT, 0);

    /* TODO: this flag works around the synchronization problem seen with using
       the user-exposed message layer to signal the temperature compensation
       module that gyro biases were set.
       A better, cleaner method is certainly needed. */
    inv_data_builder.save.gyro_bias_tc_set = true;
}

/**
 *  @internal
 *  @brief  Return whether gyro biases were set to signal the temperature
 *          compensation algorithm that it can collect a data point to build
 *          the temperature slope while in no motion state.
 *          The flag clear automatically after is read.
 *  @return true if the flag was set, indicating gyro biases were set.
 *          false if the flag was not set.
 */
int inv_get_gyro_bias_tc_set(void)
{
    int flag = (inv_data_builder.save.gyro_bias_tc_set == true);
    inv_data_builder.save.gyro_bias_tc_set = false;
    return flag;
}

/* TODO: Add this information to inv_sensor_cal_t */
/**
 *  Get the gyro biases and temperature record from MPL
 *  @param[in] bias
 *              Gyro bias in hardware units scaled by 2^16.
 *              In chip mounting frame.
 *              Length 3.
 *  @param[in] temp
 *              Tempearature in degrees C.
 */
void inv_get_gyro_bias(long *bias, long *temp)
{
    if (bias != NULL)
        memcpy(bias, inv_data_builder.save.gyro_bias,
               sizeof(inv_data_builder.save.gyro_bias));
    if (temp != NULL)
        temp[0] = inv_data_builder.save.gyro_temp;
}

/** Get Accel Bias
* @param[out] bias Accel bias where
* @param[out] temp Temperature where 1 C = 2^16
*/
void inv_get_accel_bias(long *bias, long *temp)
{
    if (bias != NULL)
        memcpy(bias, inv_data_builder.save.accel_bias,
               sizeof(inv_data_builder.save.accel_bias));
    if (temp != NULL)
        temp[0] = inv_data_builder.save.accel_temp;
}

/** 
 *  Record new accel data for use when inv_execute_on_data() is called
 *  @param[in]  accel accel data. 
 *              Length 3. 
 *              Calibrated data is in m/s^2 scaled by 2^16 in body frame. 
 *              Raw data is in device units in chip mounting frame.
 *  @param[in]  status 
 *              Lower 2 bits are the accuracy, with 0 being inaccurate, and 3 
 *              being most accurate.
 *              The upper bit INV_CALIBRATED, is set if the data was calibrated 
 *              outside MPL and it is not set if the data being passed is raw. 
 *              Raw data should be in device units, typically in a 16-bit range.
 *  @param[in]  timestamp 
 *              Monotonic time stamp, for Android it's in nanoseconds.
 *  @return     Returns INV_SUCCESS if successful or an error code if not.
 */
inv_error_t inv_build_accel(const long *accel, int status, inv_time_t timestamp)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_ACCEL;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(accel, sizeof(accel[0]), 3, inv_data_builder.file);
        fwrite(&timestamp, sizeof(timestamp), 1, inv_data_builder.file);
    }
#endif

    if ((status & INV_CALIBRATED) == 0) {
        sensors.accel.raw[0] = (short)accel[0];
        sensors.accel.raw[1] = (short)accel[1];
        sensors.accel.raw[2] = (short)accel[2];
        sensors.accel.status |= INV_RAW_DATA;
        inv_apply_calibration(&sensors.accel, inv_data_builder.save.accel_bias);
    } else {
        sensors.accel.calibrated[0] = accel[0];
        sensors.accel.calibrated[1] = accel[1];
        sensors.accel.calibrated[2] = accel[2];
        sensors.accel.status |= INV_CALIBRATED;
        sensors.accel.accuracy = status & 3;
        inv_data_builder.save.accel_accuracy = status & 3;
    }
    sensors.accel.status |= INV_NEW_DATA | INV_SENSOR_ON;
    sensors.accel.timestamp_prev = sensors.accel.timestamp;
    sensors.accel.timestamp = timestamp;

    return INV_SUCCESS;
}

/** Record new gyro data and calls inv_execute_on_data() if previous
* sample has not been processed.
* @param[in] gyro Data is in device units. Length 3.
* @param[in] timestamp Monotonic time stamp, for Android it's in nanoseconds.
* @param[out] executed Set to 1 if data processing was done.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_build_gyro(const short *gyro, inv_time_t timestamp)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_GYRO;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(gyro, sizeof(gyro[0]), 3, inv_data_builder.file);
        fwrite(&timestamp, sizeof(timestamp), 1, inv_data_builder.file);
    }
#endif

    memcpy(sensors.gyro.raw, gyro, 3 * sizeof(short));
    sensors.gyro.status |= INV_NEW_DATA | INV_RAW_DATA | INV_SENSOR_ON;
    sensors.gyro.timestamp_prev = sensors.gyro.timestamp;
    sensors.gyro.timestamp = timestamp;
    inv_apply_calibration(&sensors.gyro, inv_data_builder.save.gyro_bias);

    return INV_SUCCESS;
}

/** Record new compass data for use when inv_execute_on_data() is called
* @param[in] compass Compass data, if it was calibrated outside MPL, the units are uT scaled by 2^16.
*            Length 3.
* @param[in] status Lower 2 bits are the accuracy, with 0 being inaccurate, and 3 being most accurate.
*            The upper bit INV_CALIBRATED, is set if the data was calibrated outside MPL and it is
*            not set if the data being passed is raw. Raw data should be in device units, typically
*            in a 16-bit range.
* @param[in] timestamp Monotonic time stamp, for Android it's in nanoseconds.
* @param[out] executed Set to 1 if data processing was done.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_build_compass(const long *compass, int status,
                              inv_time_t timestamp)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_COMPASS;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(compass, sizeof(compass[0]), 3, inv_data_builder.file);
        fwrite(&timestamp, sizeof(timestamp), 1, inv_data_builder.file);
    }
#endif

    if ((status & INV_CALIBRATED) == 0) {
        long data[3];
        inv_set_compass_soft_iron_input_data(compass);
        inv_get_compass_soft_iron_output_data(data);
        sensors.compass.raw[0] = (short)data[0];
        sensors.compass.raw[1] = (short)data[1];
        sensors.compass.raw[2] = (short)data[2];
        inv_apply_calibration(&sensors.compass, inv_data_builder.save.compass_bias);
        sensors.compass.status |= INV_RAW_DATA;
    } else {
        sensors.compass.calibrated[0] = compass[0];
        sensors.compass.calibrated[1] = compass[1];
        sensors.compass.calibrated[2] = compass[2];
        sensors.compass.status |= INV_CALIBRATED;
        sensors.compass.accuracy = status & 3;
        inv_data_builder.save.compass_accuracy = status & 3;
    }
    sensors.compass.timestamp_prev = sensors.compass.timestamp;
    sensors.compass.timestamp = timestamp;
    sensors.compass.status |= INV_NEW_DATA | INV_SENSOR_ON;

    return INV_SUCCESS;
}

/** Record new temperature data for use when inv_execute_on_data() is called.
 *  @param[in]  temp Temperature data in q16 format.
 *  @param[in]  timestamp   Monotonic time stamp; for Android it's in
 *                          nanoseconds.
* @return Returns INV_SUCCESS if successful or an error code if not.
 */
inv_error_t inv_build_temp(const long temp, inv_time_t timestamp)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_TEMPERATURE;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(&temp, sizeof(temp), 1, inv_data_builder.file);
        fwrite(&timestamp, sizeof(timestamp), 1, inv_data_builder.file);
    }
#endif
    sensors.temp.calibrated[0] = temp;
    sensors.temp.status |= INV_NEW_DATA | INV_RAW_DATA | INV_SENSOR_ON;
    sensors.temp.timestamp_prev = sensors.temp.timestamp;
    sensors.temp.timestamp = timestamp;
    /* TODO: Apply scale, remove offset. */

    return INV_SUCCESS;
}
/** quaternion data
* @param[in] quat Quaternion data. 2^30 = 1.0 or 2^14=1 for 16-bit data. 
*                 Real part first. Length 4.  
* @param[in] status number of axis, 16-bit or 32-bit
* @param[in] timestamp
* @param[in]  timestamp   Monotonic time stamp; for Android it's in
*                         nanoseconds.
* @param[out] executed Set to 1 if data processing was done.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_build_quat(const long *quat, int status, inv_time_t timestamp)
{
#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_QUAT;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
        fwrite(quat, sizeof(quat[0]), 4, inv_data_builder.file);
        fwrite(&timestamp, sizeof(timestamp), 1, inv_data_builder.file);
    }
#endif
    
    memcpy(sensors.quat.raw, quat, sizeof(sensors.quat.raw));
    sensors.quat.timestamp = timestamp;
    sensors.quat.status |= INV_NEW_DATA | INV_RAW_DATA | INV_SENSOR_ON;
    sensors.quat.status |= (INV_BIAS_APPLIED & status);

    return INV_SUCCESS;
}

/** This should be called when the accel has been turned off. This is so
* that we will know if the data is contiguous.
*/
void inv_accel_was_turned_off()
{
    sensors.accel.status = 0;
}

/** This should be called when the compass has been turned off. This is so
* that we will know if the data is contiguous.
*/
void inv_compass_was_turned_off()
{
    sensors.compass.status = 0;
}

/** This should be called when the quaternion data from the DMP has been turned off. This is so
* that we will know if the data is contiguous.
*/
void inv_quaternion_sensor_was_turned_off(void)
{
    sensors.quat.status = 0;
}

/** This should be called when the gyro has been turned off. This is so
* that we will know if the data is contiguous.
*/
void inv_gyro_was_turned_off()
{
    sensors.gyro.status = 0;
}

/** This should be called when the temperature sensor has been turned off.
 *  This is so that we will know if the data is contiguous.
 */
void inv_temperature_was_turned_off()
{
    sensors.temp.status = 0;
}

/** Registers to receive a callback when there is new sensor data.
* @internal
* @param[in] func Function pointer to receive callback when there is new sensor data
* @param[in] priority Lower priority numbers receive a callback before larger numbers. All priority
*            numbers must be unique.
* @param[in] sensor_type Sets the type of data that triggers the callback. Must be non-zero. May be
*            a combination. INV_ACCEL_NEW = accel data, INV_GYRO_NEW =
*            gyro data, INV_MAG_NEW = compass data. So passing in
*            INV_ACCEL_NEW | INV_MAG_NEW, a
*            callback would be generated if there was new magnetomer data OR new accel data.
*/
inv_error_t inv_register_data_cb(
    inv_error_t (*func)(struct inv_sensor_cal_t *data),
    int priority, int sensor_type)
{
    inv_error_t result = INV_SUCCESS;
    int kk, nn;

    // Make sure we haven't registered this function already
    // Or used the same priority
    for (kk = 0; kk < inv_data_builder.num_cb; ++kk) {
        if ((inv_data_builder.process[kk].func == func) ||
                (inv_data_builder.process[kk].priority == priority)) {
            return INV_ERROR_INVALID_PARAMETER;    //fixme give a warning
        }
    }

    // Make sure we have not filled up our number of allowable callbacks
    if (inv_data_builder.num_cb <= INV_MAX_DATA_CB - 1) {
        kk = 0;
        if (inv_data_builder.num_cb != 0) {
            // set kk to be where this new callback goes in the array
            while ((kk < inv_data_builder.num_cb) &&
                    (inv_data_builder.process[kk].priority < priority)) {
                kk++;
            }
            if (kk != inv_data_builder.num_cb) {
                // We need to move the others
                for (nn = inv_data_builder.num_cb; nn > kk; --nn) {
                    inv_data_builder.process[nn] =
                        inv_data_builder.process[nn - 1];
                }
            }
        }
        // Add new callback
        inv_data_builder.process[kk].func = func;
        inv_data_builder.process[kk].priority = priority;
        inv_data_builder.process[kk].data_required = sensor_type;
        inv_data_builder.num_cb++;
    } else {
        MPL_LOGE("Unable to add feature callback as too many were already registered\n");
        result = INV_ERROR_MEMORY_EXAUSTED;
    }

    return result;
}

/** Unregisters the callback that happens when new sensor data is received.
* @internal
* @param[in] func Function pointer to receive callback when there is new sensor data
* @param[in] priority Lower priority numbers receive a callback before larger numbers. All priority
*            numbers must be unique.
* @param[in] sensor_type Sets the type of data that triggers the callback. Must be non-zero. May be
*            a combination. INV_ACCEL_NEW = accel data, INV_GYRO_NEW =
*            gyro data, INV_MAG_NEW = compass data. So passing in
*            INV_ACCEL_NEW | INV_MAG_NEW, a
*            callback would be generated if there was new magnetomer data OR new accel data.
*/
inv_error_t inv_unregister_data_cb(
    inv_error_t (*func)(struct inv_sensor_cal_t *data))
{
    int kk, nn;

    for (kk = 0; kk < inv_data_builder.num_cb; ++kk) {
        if (inv_data_builder.process[kk].func == func) {
            // Delete this callback
            for (nn = kk + 1; nn < inv_data_builder.num_cb; ++nn) {
                inv_data_builder.process[nn - 1] =
                    inv_data_builder.process[nn];
            }
            inv_data_builder.num_cb--;
            return INV_SUCCESS;
        }
    }

    return INV_SUCCESS;    // We did not find the callback
}

/** After at least one of inv_build_gyro(), inv_build_accel(), or
* inv_build_compass() has been called, this function should be called.
* It will process the data it has received and update all the internal states
* and features that have been turned on.
* @return Returns INV_SUCCESS if successful or an error code if not.
*/
inv_error_t inv_execute_on_data(void)
{
    inv_error_t result, first_error;
    int kk;
    int mode;

#ifdef INV_PLAYBACK_DBG
    if (inv_data_builder.debug_mode == RD_RECORD) {
        int type = PLAYBACK_DBG_TYPE_EXECUTE;
        fwrite(&type, sizeof(type), 1, inv_data_builder.file);
    }
#endif
    // Determine what new data we have
    mode = 0;
    if (sensors.gyro.status & INV_NEW_DATA)
        mode |= INV_GYRO_NEW;
    if (sensors.accel.status & INV_NEW_DATA)
        mode |= INV_ACCEL_NEW;
    if (sensors.compass.status & INV_NEW_DATA)
        mode |= INV_MAG_NEW;
    if (sensors.temp.status & INV_NEW_DATA)
        mode |= INV_TEMP_NEW;
    if (sensors.quat.status & INV_NEW_DATA)
        mode |= INV_QUAT_NEW;

    first_error = INV_SUCCESS;

    for (kk = 0; kk < inv_data_builder.num_cb; ++kk) {
        if (mode & inv_data_builder.process[kk].data_required) {
            result = inv_data_builder.process[kk].func(&sensors);
            if (result && !first_error) {
                first_error = result;
            }
        }
    }

    inv_set_contiguous();

    return first_error;
}

/** Cleans up status bits after running all the callbacks. It sets the contiguous flag.
*
*/
static void inv_set_contiguous(void)
{
    inv_time_t current_time = 0;
    if (sensors.gyro.status & INV_NEW_DATA) {
        sensors.gyro.status |= INV_CONTIGUOUS;
        current_time = sensors.gyro.timestamp;
    }
    if (sensors.accel.status & INV_NEW_DATA) {
        sensors.accel.status |= INV_CONTIGUOUS;
        current_time = MAX(current_time, sensors.accel.timestamp);
    }
    if (sensors.compass.status & INV_NEW_DATA) {
        sensors.compass.status |= INV_CONTIGUOUS;
        current_time = MAX(current_time, sensors.compass.timestamp);
    }
    if (sensors.temp.status & INV_NEW_DATA) {
        sensors.temp.status |= INV_CONTIGUOUS;
        current_time = MAX(current_time, sensors.temp.timestamp);
    }
    if (sensors.quat.status & INV_NEW_DATA) {
        sensors.quat.status |= INV_CONTIGUOUS;
        current_time = MAX(current_time, sensors.quat.timestamp);
    }

#if 0
    /* See if sensors are still on. These should be turned off by inv_*_was_turned_off()
     * type functions. This is just in case that breaks down. We make sure
     * all the data is within 2 seconds of the newest piece of data*/
    if (inv_delta_time_ms(current_time, sensors.gyro.timestamp) >= 2000)
        inv_gyro_was_turned_off();
    if (inv_delta_time_ms(current_time, sensors.accel.timestamp) >= 2000)
        inv_accel_was_turned_off();
    if (inv_delta_time_ms(current_time, sensors.compass.timestamp) >= 2000)
        inv_compass_was_turned_off();
    /* TODO: Temperature might not need to be read this quickly. */
    if (inv_delta_time_ms(current_time, sensors.temp.timestamp) >= 2000)
        inv_temperature_was_turned_off();
#endif

    /* clear bits */
    sensors.gyro.status &= ~INV_NEW_DATA;
    sensors.accel.status &= ~INV_NEW_DATA;
    sensors.compass.status &= ~INV_NEW_DATA;
    sensors.temp.status &= ~INV_NEW_DATA;
    sensors.quat.status &= ~INV_NEW_DATA;
}

/** Gets a whole set of accel data including data, accuracy and timestamp.
 * @param[out] data Accel Data where 1g = 2^16
 * @param[out] accuracy Accuracy 0 being not accurate, and 3 being most accurate.
 * @param[out] timestamp The timestamp of the data sample.
*/
void inv_get_accel_set(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    if (data != NULL) {
        memcpy(data, sensors.accel.calibrated, sizeof(sensors.accel.calibrated));
    }
    if (timestamp != NULL) {
        *timestamp = sensors.accel.timestamp;
    }
    if (accuracy != NULL) {
        *accuracy = sensors.accel.accuracy;
    }
}

/** Gets a whole set of gyro data including data, accuracy and timestamp.
 * @param[out] data Gyro Data where 1 dps = 2^16
 * @param[out] accuracy Accuracy 0 being not accurate, and 3 being most accurate.
 * @param[out] timestamp The timestamp of the data sample.
*/
void inv_get_gyro_set(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    memcpy(data, sensors.gyro.calibrated, sizeof(sensors.gyro.calibrated));
    if (timestamp != NULL) {
        *timestamp = sensors.gyro.timestamp;
    }
    if (accuracy != NULL) {
        *accuracy = sensors.gyro.accuracy;
    }
}

/** Gets a whole set of gyro raw data including data, accuracy and timestamp.
 * @param[out] data Gyro Data where 1 dps = 2^16
 * @param[out] accuracy Accuracy 0 being not accurate, and 3 being most accurate.
 * @param[out] timestamp The timestamp of the data sample.
*/
void inv_get_gyro_set_raw(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    memcpy(data, sensors.gyro.raw_scaled, sizeof(sensors.gyro.raw_scaled));
    if (timestamp != NULL) {
        *timestamp = sensors.gyro.timestamp;
    }
    if (accuracy != NULL) {
        *accuracy = sensors.gyro.accuracy;
    }
}

/** Get's latest gyro data.
* @param[out] gyro Gyro Data, Length 3. 1 dps = 2^16.
*/
void inv_get_gyro(long *gyro)
{
    memcpy(gyro, sensors.gyro.calibrated, sizeof(sensors.gyro.calibrated));
}

/** Gets a whole set of compass data including data, accuracy and timestamp.
 * @param[out] data Compass Data where 1 uT = 2^16
 * @param[out] accuracy Accuracy 0 being not accurate, and 3 being most accurate.
 * @param[out] timestamp The timestamp of the data sample.
*/
void inv_get_compass_set(long *data, int8_t *accuracy, inv_time_t *timestamp)
{
    memcpy(data, sensors.compass.calibrated, sizeof(sensors.compass.calibrated));
    if (timestamp != NULL) {
        *timestamp = sensors.compass.timestamp;
    }
    if (accuracy != NULL) {
        if (inv_data_builder.compass_disturbance)
            *accuracy = 0;
        else
            *accuracy = sensors.compass.accuracy;
    }
}

/** Gets a whole set of temperature data including data, accuracy and timestamp.
 *  @param[out] data        Temperature data where 1 degree C = 2^16
 *  @param[out] accuracy    0 to 3, where 3 is most accurate.
 *  @param[out] timestamp   The timestamp of the data sample.
 */
void inv_get_temp_set(long *data, int *accuracy, inv_time_t *timestamp)
{
    data[0] = sensors.temp.calibrated[0];
    if (timestamp)
        *timestamp = sensors.temp.timestamp;
    if (accuracy)
        *accuracy = sensors.temp.accuracy;
}

/** Returns accuracy of gyro.
 * @return Accuracy of gyro with 0 being not accurate, and 3 being most accurate.
*/
int inv_get_gyro_accuracy(void)
{
    return sensors.gyro.accuracy;
}

/** Returns accuracy of compass.
 * @return Accuracy of compass with 0 being not accurate, and 3 being most accurate.
*/
int inv_get_mag_accuracy(void)
{
    if (inv_data_builder.compass_disturbance)
        return 0;
    return sensors.compass.accuracy;
}

/** Returns accuracy of accel.
 * @return Accuracy of accel with 0 being not accurate, and 3 being most accurate.
*/
int inv_get_accel_accuracy(void)
{
    return sensors.accel.accuracy;
}

inv_error_t inv_get_gyro_orient(int *orient)
{
    *orient = sensors.gyro.orientation;
    return 0;
}

inv_error_t inv_get_accel_orient(int *orient)
{
    *orient = sensors.accel.orientation;
    return 0;
}

/*======================================================================*/
/*   compass soft iron module                                           */
/*======================================================================*/

/** Gets the 3x3 compass transform matrix in 32 bit Q30 fixed point format.
 * @param[out] the pointer of the 3x3 matrix in Q30 format
*/
void inv_get_compass_soft_iron_matrix_d(long *matrix) {
    int i;
    for (i=0; i<9; i++)  {
        matrix[i] = sensors.soft_iron.matrix_d[i];
    }
}

/** Sets the 3x3 compass transform matrix in 32 bit Q30 fixed point format.
 * @param[in] the pointer of the 3x3 matrix in Q30 format
*/
void inv_set_compass_soft_iron_matrix_d(long *matrix)  {
    int i;
    for (i=0; i<9; i++)  {
        // set the floating point matrix
        sensors.soft_iron.matrix_d[i] = matrix[i];
        // convert to Q30 format
        sensors.soft_iron.matrix_f[i] = inv_q30_to_float(matrix[i]);
    }
}
/** Gets the 3x3 compass transform matrix in 32 bit floating point format.
 * @param[out] the pointer of the 3x3 matrix in floating point format
*/
void inv_get_compass_soft_iron_matrix_f(float *matrix)  {
    int i;
    for (i=0; i<9; i++)  {
        matrix[i] = sensors.soft_iron.matrix_f[i];
    }
}
/** Sets the 3x3 compass transform matrix in 32 bit floating point format.
 * @param[in] the pointer of the 3x3 matrix in floating point format
*/
void inv_set_compass_soft_iron_matrix_f(float *matrix)   {
    int i;
    for (i=0; i<9; i++)  {
        // set the floating point matrix
        sensors.soft_iron.matrix_f[i] = matrix[i];
        // convert to Q30 format
        sensors.soft_iron.matrix_d[i] = (long )(matrix[i]*ROT_MATRIX_SCALE_LONG);
    }
}

/** This subroutine gets the fixed point Q30 compass data after the soft iron transformation.
 * @param[out] the pointer of the 3x1 vector compass data in MPL format
*/
void inv_get_compass_soft_iron_output_data(long *data) {
    int i;
    for (i=0; i<3; i++)  {
        data[i] = sensors.soft_iron.trans[i];
    }
}
/** This subroutine gets the fixed point Q30 compass data before the soft iron transformation.
 * @param[out] the pointer of the 3x1 vector compass data in MPL format
*/
void inv_get_compass_soft_iron_input_data(long *data)  {
    int i;
    for (i=0; i<3; i++)  {
        data[i] = sensors.soft_iron.raw[i];
    }
}
/** This subroutine sets the compass raw data for the soft iron transformation.
 * @param[int] the pointer of the 3x1 vector compass raw data in MPL format
*/
void inv_set_compass_soft_iron_input_data(const long *data)  {
    int i;
    for (i=0; i<3; i++)  {
        sensors.soft_iron.raw[i] = data[i];
    }
    if (sensors.soft_iron.enable == 1)  {
        mlMatrixVectorMult(sensors.soft_iron.matrix_d, data, sensors.soft_iron.trans);
    } else {
        for (i=0; i<3; i++)  {
            sensors.soft_iron.trans[i] = data[i];
        }
    }
}

/** This subroutine resets the the soft iron transformation to unity matrix and
 * disable the soft iron transformation process by default.
*/
void inv_reset_compass_soft_iron_matrix(void)  {
    int i;
    for (i=0; i<9; i++) {
        sensors.soft_iron.matrix_f[i] = 0.0f;
    }

    memset(&sensors.soft_iron.matrix_d,0,sizeof(sensors.soft_iron.matrix_d));

    for (i=0; i<3; i++)  {
        // set the floating point matrix
        sensors.soft_iron.matrix_f[i*4] = 1.0;
        // set the fixed point matrix
        sensors.soft_iron.matrix_d[i*4] = ROT_MATRIX_SCALE_LONG;
    }

    inv_disable_compass_soft_iron_matrix();
}

/** This subroutine enables the the soft iron transformation process.
*/
void inv_enable_compass_soft_iron_matrix(void)   {
    sensors.soft_iron.enable = 1;
}

/** This subroutine disables the the soft iron transformation process.
*/
void inv_disable_compass_soft_iron_matrix(void)   {
    sensors.soft_iron.enable = 0;
}

/**
 * @}
 */