/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
#include "mltypes.h"

#ifndef INV_DATA_BUILDER_H__
#define INV_DATA_BUILDER_H__

#ifdef __cplusplus
extern "C" {
#endif

// Uncomment this flag to enable playback debug and record or playback scenarios
//#define INV_PLAYBACK_DBG

/** This is a new sample of accel data */
#define INV_ACCEL_NEW 1
/** This is a new sample of gyro data */
#define INV_GYRO_NEW 2
/** This is a new sample of compass data */
#define INV_MAG_NEW 4
/** This is a new sample of temperature data */
#define INV_TEMP_NEW 8
/** This is a new sample of quaternion data */
#define INV_QUAT_NEW 16

/** Set if the data is contiguous. Typically not set if a sample was skipped */
#define INV_CONTIGUOUS 16
/** Set if the calibrated data has been solved for */
#define INV_CALIBRATED 32
/* INV_NEW_DATA set for a new set of data, cleared if not available. */
#define INV_NEW_DATA 64
/* Set if raw data exists */
#define INV_RAW_DATA 128
/* Set if the sensor is on */
#define INV_SENSOR_ON 256
/* Set if quaternion has bias correction applied */
#define INV_BIAS_APPLIED 512

#define INV_PRIORITY_MOTION_NO_MOTION          100
#define INV_PRIORITY_GYRO_TC                   150
#define INV_PRIORITY_QUATERNION_GYRO_ACCEL     200
#define INV_PRIORITY_QUATERNION_NO_GYRO        250
#define INV_PRIORITY_MAGNETIC_DISTURBANCE      300
#define INV_PRIORITY_HEADING_FROM_GYRO         350
#define INV_PRIORITY_COMPASS_BIAS_W_GYRO       375
#define INV_PRIORITY_COMPASS_VECTOR_CAL        400
#define INV_PRIORITY_COMPASS_ADV_BIAS          500
#define INV_PRIORITY_9_AXIS_FUSION             600
#define INV_PRIORITY_QUATERNION_ADJUST_9_AXIS  700
#define INV_PRIORITY_QUATERNION_ACCURACY       750
#define INV_PRIORITY_RESULTS_HOLDER            800
#define INV_PRIORITY_INUSE_AUTO_CALIBRATION    850
#define INV_PRIORITY_HAL_OUTPUTS               900
#define INV_PRIORITY_GLYPH                     950
#define INV_PRIORITY_SHAKE                     975
#define INV_PRIORITY_SM                        1000

struct inv_single_sensor_t {
    /** Orientation Descriptor. Describes how to go from the mounting frame to the body frame when
    * the rotation matrix could be thought of only having elements of 0,1,-1.
    * 2 bits are used to describe the column of the 1 or -1 and the 3rd bit is used for the sign.
    * Bit 8 is sign of +/- 1 in third row. Bit 6-7 is column of +/-1 in third row.
    * Bit 5 is sign of +/- 1 in second row. Bit 3-4 is column of +/-1 in second row.
    * Bit 2 is sign of +/- 1 in first row. Bit 0-1 is column of +/-1 in first row.
    */
    int orientation;
    /** The raw data in raw data units in the mounting frame */
    short raw[3];
    /** Raw data in body frame */
    long raw_scaled[3];
    /** Calibrated data */
    long calibrated[3];
    long sensitivity;
    /** Sample rate in microseconds */
    long sample_rate_us;
    long sample_rate_ms;
    /** INV_CONTIGUOUS is set for contiguous data. Will not be set if there was a sample
    * skipped due to power savings turning off this sensor.
    * INV_NEW_DATA set for a new set of data, cleared if not available.
    * INV_CALIBRATED_SET if calibrated data has been solved for */
    int status;
    /** 0 to 3 for how well sensor data and biases are known. 3 is most accurate. */
    int accuracy;
    inv_time_t timestamp;
    inv_time_t timestamp_prev;
    /** Bandwidth in Hz */
    int bandwidth;
};
struct inv_quat_sensor_t {
    long raw[4];
    /** INV_CONTIGUOUS is set for contiguous data. Will not be set if there was a sample
    * skipped due to power savings turning off this sensor.
    * INV_NEW_DATA set for a new set of data, cleared if not available.
    * INV_CALIBRATED_SET if calibrated data has been solved for */
    int status;
    inv_time_t timestamp;
    long sample_rate_us;
    long sample_rate_ms;
};

struct inv_soft_iron_t {
    long raw[3];
    long trans[3];
    long matrix_d[9];  // Q30 format fixed point. The dynamic range is (-2.0 to 2.0);
    float matrix_f[9];

    int enable;
};

struct inv_sensor_cal_t {
    struct inv_single_sensor_t gyro;
    struct inv_single_sensor_t accel;
    struct inv_single_sensor_t compass;
    struct inv_single_sensor_t temp;
    struct inv_quat_sensor_t quat;
    struct inv_soft_iron_t soft_iron;
    /** Combinations of INV_GYRO_NEW, INV_ACCEL_NEW, INV_MAG_NEW to indicate
    * which data is a new sample as these data points may have different sample rates.
    */
    int status;
};

// Useful for debug record and playback
typedef enum {
    RD_NO_DEBUG,
    RD_RECORD,
    RD_PLAYBACK
} rd_dbg_mode;

typedef enum {
    PLAYBACK_DBG_TYPE_GYRO,
    PLAYBACK_DBG_TYPE_ACCEL,
    PLAYBACK_DBG_TYPE_COMPASS,
    PLAYBACK_DBG_TYPE_TEMPERATURE,
    PLAYBACK_DBG_TYPE_EXECUTE,
    PLAYBACK_DBG_TYPE_A_ORIENT,
    PLAYBACK_DBG_TYPE_G_ORIENT,
    PLAYBACK_DBG_TYPE_C_ORIENT,
    PLAYBACK_DBG_TYPE_A_SAMPLE_RATE,
    PLAYBACK_DBG_TYPE_C_SAMPLE_RATE,
    PLAYBACK_DBG_TYPE_G_SAMPLE_RATE,
    PLAYBACK_DBG_TYPE_GYRO_OFF,
    PLAYBACK_DBG_TYPE_ACCEL_OFF,
    PLAYBACK_DBG_TYPE_COMPASS_OFF,
    PLAYBACK_DBG_TYPE_Q_SAMPLE_RATE,
    PLAYBACK_DBG_TYPE_QUAT

} inv_rd_dbg_states;

/** Maximum number of data callbacks that are supported. Safe to increase if needed.*/
#define INV_MAX_DATA_CB 20

#ifdef INV_PLAYBACK_DBG
#include <stdio.h>
void inv_turn_on_data_logging(FILE *file);
void inv_turn_off_data_logging();
#endif

void inv_set_gyro_orientation_and_scale(int orientation, long sensitivity);
void inv_set_accel_orientation_and_scale(int orientation,
        long sensitivity);
void inv_set_compass_orientation_and_scale(int orientation,
        long sensitivity);
void inv_set_gyro_sample_rate(long sample_rate_us);
void inv_set_compass_sample_rate(long sample_rate_us);
void inv_set_quat_sample_rate(long sample_rate_us);
void inv_set_accel_sample_rate(long sample_rate_us);
void inv_set_gyro_bandwidth(int bandwidth_hz);
void inv_set_accel_bandwidth(int bandwidth_hz);
void inv_set_compass_bandwidth(int bandwidth_hz);

void inv_get_gyro_sample_rate_ms(long *sample_rate_ms);
void inv_get_accel_sample_rate_ms(long *sample_rate_ms);
void inv_get_compass_sample_rate_ms(long *sample_rate_ms);

inv_error_t inv_register_data_cb(inv_error_t (*func)
                                 (struct inv_sensor_cal_t * data), int priority,
                                 int sensor_type);
inv_error_t inv_unregister_data_cb(inv_error_t (*func)
                                   (struct inv_sensor_cal_t * data));

inv_error_t inv_build_gyro(const short *gyro, inv_time_t timestamp);
inv_error_t inv_build_compass(const long *compass, int status,
                                  inv_time_t timestamp);
inv_error_t inv_build_accel(const long *accel, int status,
                            inv_time_t timestamp);
inv_error_t inv_build_temp(const long temp, inv_time_t timestamp);
inv_error_t inv_build_quat(const long *quat, int status, inv_time_t timestamp);
inv_error_t inv_execute_on_data(void);

void inv_get_compass_bias(long *bias);

void inv_set_compass_bias(const long *bias, int accuracy);
void inv_set_compass_disturbance(int dist);
void inv_set_gyro_bias(const long *bias, int accuracy);
void inv_set_accel_bias(const long *bias, int accuracy);
void inv_set_accel_accuracy(int accuracy);
void inv_set_accel_bias_mask(const long *bias, int accuracy, int mask);

void inv_get_compass_soft_iron_matrix_d(long *matrix);
void inv_set_compass_soft_iron_matrix_d(long *matrix);

void inv_get_compass_soft_iron_matrix_f(float *matrix);
void inv_set_compass_soft_iron_matrix_f(float *matrix);

void inv_get_compass_soft_iron_output_data(long *data);
void inv_get_compass_soft_iron_input_data(long *data);
void inv_set_compass_soft_iron_input_data(const long *data);

void inv_reset_compass_soft_iron_matrix(void);
void inv_enable_compass_soft_iron_matrix(void);
void inv_disable_compass_soft_iron_matrix(void);

void inv_get_gyro_bias(long *bias, long *temp);
void inv_get_accel_bias(long *bias, long *temp);

void inv_gyro_was_turned_off(void);
void inv_accel_was_turned_off(void);
void inv_compass_was_turned_off(void);
void inv_quaternion_sensor_was_turned_off(void);
inv_error_t inv_init_data_builder(void);
long inv_get_gyro_sensitivity(void);
long inv_get_accel_sensitivity(void);
long inv_get_compass_sensitivity(void);

void inv_get_accel_set(long *data, int8_t *accuracy, inv_time_t * timestamp);
void inv_get_gyro_set(long *data, int8_t *accuracy, inv_time_t * timestamp);
void inv_get_gyro_set_raw(long *data, int8_t *accuracy, inv_time_t * timestamp);
void inv_get_compass_set(long *data, int8_t *accuracy, inv_time_t * timestamp);

void inv_get_gyro(long *gyro);

int inv_get_gyro_accuracy(void);
int inv_get_accel_accuracy(void);
int inv_get_mag_accuracy(void);

int inv_get_compass_on(void);
int inv_get_gyro_on(void);
int inv_get_accel_on(void);

inv_time_t inv_get_last_timestamp(void);
int inv_get_compass_disturbance(void);

//New DMP Cal Functions
inv_error_t inv_get_gyro_orient(int *orient);
inv_error_t inv_get_accel_orient(int *orient);

// internal
int inv_get_gyro_bias_tc_set(void);

#ifdef __cplusplus
}
#endif

#endif  /* INV_DATA_BUILDER_H__ */