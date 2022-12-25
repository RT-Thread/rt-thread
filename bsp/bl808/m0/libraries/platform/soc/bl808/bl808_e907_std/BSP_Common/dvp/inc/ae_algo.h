#ifndef __AE_ALGO_H__
#define __AE_ALGO_H__

#include "bl_comm_aaa.h"

typedef enum {
    AE_MODE_AUTO = 0,
    AE_MODE_LOCK,
    AE_MODE_SHUTTER_PRIORITY,       /* iso locked */
    AE_MODE_GAIN_PRIORITY,          /* shutter locked */
    AE_MODE_AUTO_LOW_SPEED,
    AE_MODE_DBG_VIRTUAL,
    AE_MODE_INVALID,
} AE_MODE;

typedef enum {
    AE_STATE_IDLE = 0,
    AE_STATE_INITED,
    AE_STATE_RUNNING,
    AE_STATE_PENDING,
} AE_STATE;

typedef enum {
    AE_METERING_AVERAGE = 0,
    AE_METERING_CENTER_WEIGHTED,
    AE_METERING_SPOT,
    AE_METERING_CUSTOM,
    AE_METERING_NUM,
} AE_METERING;

typedef struct {
    aaa_stats_cfg_t stats_cfg;
} ae_config_t;

typedef struct {
    AE_MODE       ae_mode;
    AE_METERING   ae_metering;
    uint32_t      expo_time_update;
    uint32_t      iso_update;
    uint32_t      sys_gain_update;
    BL_EXPO_TIME  expo_time;
    BL_GAIN_DB    iso;
    BL_GAIN_DB    sys_gain;
    int           luma_target;
} ae_info_t;

int ae_init(void);
int ae_config(ae_config_t *ae_config, bool is_virtual_sensor);
int ae_control(void);
int ae_get_info(ae_info_t **ae_info);

/* Update ae statistics from hw*/
void ae_update_stats(void);

/* set/get ae mode */
int ae_set_mode(AE_MODE mode);
int ae_get_mode(AE_MODE *mode);

/* Target value ranges from 0~255 */
int ae_set_luma_target(int target);
int ae_get_luma_target(int *target);

/* set/get ae metering mode */
int ae_get_metering_mode(AE_METERING *mode);
int ae_set_metering_mode(AE_METERING mode);

/* Speed value ranges from 0~16 */
int ae_set_speed(int speed);

/* Luma value ranges from 0~255 */
int ae_get_luma(void);

/* Set and get SW limitation by AE strategy */
int ae_set_exposure_max(BL_EXPO_TIME max_expo);
int ae_get_exposure_max(BL_EXPO_TIME *max_expo);
int ae_set_exposure_min(BL_EXPO_TIME min_expo);
int ae_get_exposure_min(BL_EXPO_TIME *min_expo);
int ae_set_gain_max(float gain_f);
int ae_get_gain_min(float *gain_f);

/* Get HW limitation of sensor */
int ae_get_sensor_exposure_max(BL_EXPO_TIME *max_expo);
int ae_get_sensor_exposure_min(BL_EXPO_TIME *min_expo);
int ae_get_sensor_gain_max(float *max_gain_f);

/* Set and get sensor exposure and gain */
int ae_set_sensor_exposure(BL_EXPO_TIME expo_time);
int ae_get_sensor_exposure(BL_EXPO_TIME *expo_time);
int ae_get_sensor_gain(float *gain_f);
int ae_set_sensor_gain(float gain_f);

/* Misc */
void ae_force_refresh(void);


#endif //__AE_ALGO_H__
