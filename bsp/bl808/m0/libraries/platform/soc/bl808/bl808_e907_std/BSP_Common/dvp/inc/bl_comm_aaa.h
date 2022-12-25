#ifndef __BL_COMM_3A_H__
#define __BL_COMM_3A_H__

#include "bl_comm_sns.h"

#define IMG_START_SKIP_NUM        1

#define SEC_TO_NS(x)                    ((x) * 1000000000)
#define NS_TO_SEC(x)                    DIV_ROUND(x, 1000000000)

#define INT_TO_EXPO_TIME(x)             (BL_EXPO_TIME)(DIV_ROUND(SEC_TO_NS(1),x))
#define EXPO_TIME_TO_INT(x)             (SEC_TO_NS(1) / (int)(x))
#define EXPO_TIME_1_SEC                 1000000000
#define EXPO_TIME_1_25_SEC              40000000
#define EXPO_TIME_1_30_SEC              INT_TO_EXPO_TIME(30)
#define EXPO_TIME_1_50_SEC              INT_TO_EXPO_TIME(50)
#define EXPO_TIME_1_60_SEC              INT_TO_EXPO_TIME(60)
#define EXPO_TIME_1_100_SEC             10000000
#define EXPO_TIME_1_120_SEC             8333333
#define EXPO_TIME_MIN                   1


#define INT_TO_GAIN_DB(x)               (BL_GAIN_DB)((x) << 8)
#define GAIN_DB_TO_INT(x)               ((int)(x) >> 8)

#define GAIN_X_TO_DB(x)                 (log2((float)(x)) * 6)
#define GAIN_DB_FLOAT_TO_INT(x)         ((int)((float)(x) * 256 + 0.5))
#define GAIN_DB_INT_TO_FLOAT(x)         ((float)(x) / 256)

#define GAIN_6_DB                       1536    /* 6 << 8 */
#define GAIN_0_DB                       0

typedef struct {
    BL_Img_Size_T act_win;
    BL_Img_Size_T out_win;
} aaa_stats_cfg_t;

#endif