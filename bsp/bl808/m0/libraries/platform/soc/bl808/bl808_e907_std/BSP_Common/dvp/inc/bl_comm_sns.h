#ifndef __BL_COMM_SNS_H__
#define __BL_COMM_SNS_H__

#include <stdint.h>
#include <stdbool.h>
#include <bl808_comm_mm.h>

typedef enum {
    SENSOR_UID_SC1245 = 0,
    SENSOR_UID_SC2232 = 1,
    SENSOR_UID_OV9732 = 2,
    SENSOR_UID_C2490 = 3,
    SENSOR_UID_NUM = 3,
} BL_SENSOR_UID_E;

typedef unsigned int BL_EXPO_TIME;    /* exposure time type */

#define ENUM_VALUE_INVALID  0xFFFF

typedef enum {
    VIDEO_MODE_720P_5 = 0,
    VIDEO_MODE_720P_10 = 1,
    VIDEO_MODE_720P_20 = 2,
    VIDEO_MODE_720P_25 = 3,
    VIDEO_MODE_720P_30,
    VIDEO_MODE_720P_50,
    VIDEO_MODE_720P_59_94,
    VIDEO_MODE_1080P_5,
    VIDEO_MODE_1080P_10,
    VIDEO_MODE_1080P_12P5,
    VIDEO_MODE_1080P_15,
    VIDEO_MODE_1080P_20,
    VIDEO_MODE_1080P_25,
    VIDEO_MODE_1080P_30,
    VIDEO_MODE_UXGA_25,
    VIDEO_MODE_INVALID = ENUM_VALUE_INVALID,
} VIDEO_MODE_E;

typedef enum {
    BL_DAY_MODE = 0,
    BL_NIGHT_MODE = 1,
} BL_DSP2_DAY_NIGHT_MODE_T;

typedef struct {
    float r_gain;
    float b_gain;
} rb_gain_fp_t;

typedef struct {
    int position;
    int value;
} intpl_point_t;

typedef struct {
    uint16_t width;
    uint16_t height;
} res_config_t;

typedef int BL_COLOR_TEMP;                   /* ct value in K */

/**************************** helper functions ***********************************/

#define INIT_OBJ(obj)   \
    do {    \
        memset(&obj, 0, sizeof(obj));   \
    } while (0)

bool is_param_valid(int value, int min, int max);
void clip_param_range(int *value, int min, int max);
intpl_point_t create_intpl_point(int position, int value);
int linear_interpolate(intpl_point_t *point_L, intpl_point_t *point_H, int pos, int *value);

#endif /* __BL_COMM_SNS_H__ */
