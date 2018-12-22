/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/sensor/sensor_pri.h
**
** \version     $Id$
**
** \brief       1
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#ifndef _SENSOR_PRI_H_
#define _SENSOR_PRI_H_



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
//#define SENSOR_DEBUG

#define GD_VIN_SRC_DISABLED             (0)
#define GD_VIN_SRC_ENABLED_FOR_VIDEO    (0x01)
#define GD_VIN_SRC_ENABLED_FOR_STILL    (0x02)

#define GD_VIDEO_FORMAT(format)         (format)
#define GD_VIDEO_FORMAT_AUTO            GD_VIDEO_FORMAT(0)
#define GD_VIDEO_FORMAT_INTERLACE       GD_VIDEO_FORMAT(1)
#define GD_VIDEO_FORMAT_PROGRESSIVE     GD_VIDEO_FORMAT(2)

#define GD_VIDEO_TYPE(type)             (type)
#define GD_VIDEO_TYPE_AUTO              GD_VIDEO_TYPE(0)
#define GD_VIDEO_TYPE_YUV_601           GD_VIDEO_TYPE(1)
#define GD_VIDEO_TYPE_YUV_656           GD_VIDEO_TYPE(2)
#define GD_VIDEO_TYPE_RGB_601           GD_VIDEO_TYPE(3)
#define GD_VIDEO_TYPE_RGB_656           GD_VIDEO_TYPE(4)
#define GD_VIDEO_TYPE_RGB_RAW           GD_VIDEO_TYPE(5)    //Sensor
#define GD_VIDEO_TYPE_YUV_BT1120        GD_VIDEO_TYPE(6)
#define GD_VIDEO_TYPE_RGB_BT1120        GD_VIDEO_TYPE(7)

#define GD_VIDEO_TYPE_IS_YUV(type)      (((type) == GD_VIDEO_TYPE_YUV_601) || ((type) == GD_VIDEO_TYPE_YUV_656) ||    \
                                        ((type) == GD_VIDEO_TYPE_YUV_BT1120))


//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************
typedef enum
{
    GD_VIN_CAPTURE_MODE_ERS_CONTINUOUS = 0,
    GD_VIN_CAPTURE_MODE_ERS_SNAPSHOT,
    GD_VIN_CAPTURE_MODE_ERS_BULB,
    GD_VIN_CAPTURE_MODE_GRR_SNAPSHOT,
    GD_VIN_CAPTURE_MODE_GRR_BULB
}gd_vin_capture_mode_e;

typedef enum
{
    GD_VIN_TRIGGER_SOURCE_GPIO = 0,
    GD_VIN_TRIGGER_SOURCE_EXT
}gd_vin_trigger_source_e;

typedef enum
{
    GD_VIN_FLASH_LEVEL_LOW = 0,
    GD_VIN_FLASH_LEVEL_HIGH
}gd_vin_flash_level_e;

typedef enum
{
    GD_VIN_FLASH_OFF = 0,
    GD_VIN_FLASH_ON
}gd_vin_flash_statusl_e;

typedef enum
{
    PLL_CLK_10D1001MHZ      =  9990010,
    PLL_CLK_10MHZ           = 10000000,
    PLL_CLK_13D1001MHZ      = 12987012,
    PLL_CLK_13MHZ           = 13000000,
    PLL_CLK_13_5D1001MHZ    = 13486513,
    PLL_CLK_13_5MHZ         = 13500000,
    PLL_CLK_17_97515MHZ     = 17975154,
    PLL_CLK_17_97554MHZ     = 17975544,
    PLL_CLK_17_98201MHZ     = 17982018,
    PLL_CLK_18_44MHz        = 18440000,
    PLL_CLK_22_5MHZ         = 22500000,
    PLL_CLK_23_9772MHZ      = 23977223,
    PLL_CLK_23_9784MHZ      = 23978422,
    PLL_CLK_23_99MHZ        = 23998277,
    PLL_CLK_23_967MHZ       = 23967392,
    PLL_CLK_23_971MHZ       = 23971444,
    PLL_CLK_24D1001MHZ      = 23976024,
    PLL_CLK_23_996MHZ       = 23996483,
    PLL_CLK_24MHZ           = 24000000,
    PLL_CLK_24M1001MHZ      = 24024000,
    PLL_CLK_24_072MHZ       = 24072001,
    PLL_CLK_24_3MHZ         = 24300000,
    PLL_CLK_24_54MHZ        = 24545430,
    PLL_CLK_25MHZ           = 25000000,
    PLL_CLK_27D1001MHZ      = 26973027,
    PLL_CLK_26_9823MHZ      = 26982318,
    PLL_CLK_26_9485MHZ      = 26948544, /* - 1 LN at 60hz */
    PLL_CLK_26_9568MHZ      = 26956800, /* - 1 LN at 50hz */
    PLL_CLK_27MHZ           = 27000000,
    PLL_CLK_27_0432MHZ      = 27043200, /* + 1 LN at 50hz */
    PLL_CLK_27_0514MHZ      = 27051402, /* + 1 LN at 60hz */
    PLL_CLK_27M1001MHZ      = 27027000,
    PLL_CLK_30MHZ           = 30000000,
    PLL_CLK_27_1792MHZ      = 27179210,
    PLL_CLK_32_5D1001MHZ    = 32467532,
    PLL_CLK_36D1001MHZ      = 35964036,
    PLL_CLK_36MHZ           = 36000000,
    PLL_CLK_36_20MHZ        = 36197802,
    PLL_CLK_36_23MHZ        = 36234000,
    PLL_CLK_37_125D1001MHZ  = 37087912,
    PLL_CLK_37_125MHZ       = 37125000,
    PLL_CLK_42D1001MHZ      = 41958042,
    PLL_CLK_42MHZ           = 42000000,
    PLL_CLK_45MHZ           = 45000000,
    PLL_CLK_48D1001MHZ      = 47952048,
    PLL_CLK_48MHZ           = 48000000,
    PLL_CLK_48_6MHZ         = 48600000,
    PLL_CLK_49_5D1001MHZ    = 49450549,
    PLL_CLK_49_5MHZ         = 49500000,
    PLL_CLK_54MHZ           = 54000000,
    PLL_CLK_54M1001MHZ      = 54054000,
    PLL_CLK_60MHZ           = 60000000,
    PLL_CLK_60M1001MHZ      = 60060000,
    PLL_CLK_60_05MHz        = 60054545,
    PLL_CLK_60_16MHZ        = 60164835,
    PLL_CLK_60_18MHZ        = 60183566,
    PLL_CLK_60_29MHZ        = 60285794,
    PLL_CLK_60_33MHZ        = 60329670,
    PLL_CLK_60_35MHZ        = 60346080,
    PLL_CLK_60_39MHZ        = 60390000,
    PLL_CLK_60_48MHz        = 60480000,
    PLL_CLK_64D1001MHZ      = 63936064,
    PLL_CLK_64MHZ           = 64000000,
    PLL_CLK_65D1001MHZ      = 64935064,
    PLL_CLK_72D1001MHZ      = 71928072,
    PLL_CLK_72MHZ           = 72000000,
    PLL_CLK_74_25D1001MHZ   = 74175824,
    PLL_CLK_74_25MHZ        = 74250000,
    PLL_CLK_80MHZ           = 80000000,
    PLL_CLK_90D1001MHZ      = 89910090,
    PLL_CLK_90MHZ           = 90000000,
    PLL_CLK_90_62D1001MHZ   = 90525314,
    PLL_CLK_90_62MHZ        = 90615840,
    PLL_CLK_90_69D1001MHZ   = 90596763,
    PLL_CLK_90_69MHZ        = 90687360,
    PLL_CLK_95_993D1001MHZ  = 95896903,
    PLL_CLK_96D1001MHZ      = 95904096,
    PLL_CLK_96MHZ           = 96000000,
    PLL_CLK_99D1001MHZ      = 98901099,
    PLL_CLK_99MHZ           = 99000000,
    PLL_CLK_99_18D1001MHZ   = 99081439,
    PLL_CLK_99_18MHZ        = 99180720,
    PLL_CLK_108MHZ          = 108000000,
    PLL_CLK_148_5D1001MHZ   = 148351648,
    PLL_CLK_148_5MHZ        = 148500000,
    PLL_CLK_120MHZ          = 120000000,
    PLL_CLK_144MHZ          = 144000000,
    PLL_CLK_150MHZ          = 150000000,
    PLL_CLK_156MHZ          = 156000000,
    PLL_CLK_160MHZ          = 160000000,
    PLL_CLK_192MHZ          = 192000000,
    PLL_CLK_216MHZ          = 216000000,
    PLL_CLK_230_4MHZ        = 230400000,
    PLL_CLK_240MHZ          = 240000000,
    PLL_CLK_288MHZ          = 288000000,
    PLL_CLK_320MHZ          = 320000000,
    PLL_CLK_384MHZ          = 384000000
}PLL_CLK_HZ;

//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************
typedef struct
{
    GD_VIDEO_MODE_E mode;
    U32             preview_index;
    U32             preview_mode_type;
    U32             still_index;
    U32             still_mode_type;
}gd_video_mode_s;


typedef struct  {
    S16 bl_oo;
    S16 bl_oe;
    S16 bl_eo;
    S16 bl_ee;
}gd_vin_black_level_compensation_s;

typedef struct
{
    //GD_VIN_SRC_SET_STILL_MODE
    gd_vin_capture_mode_e     capture_mode;
    gd_vin_trigger_source_e   trigger_source;
    GD_VIDEO_MODE_E         still_mode;
    gd_vin_flash_level_e      flash_level;
    gd_vin_flash_statusl_e     flash_status;

    U32 shutter_time;
    S32 gain_db;
    gd_vin_black_level_compensation_s sw_blc;
    U32 fps;
}gd_vin_src_still_info_s;

typedef struct
{
    //struct i2c_client        client;
    //struct __amba_vin_source    source;
    int             current_video_index;
    GD_VIDEO_MODE_E current_vin_mode;
    U16             cap_start_x;
    U16             cap_start_y;
    U16             cap_cap_w;
    U16             cap_cap_h;
    U8              active_capinfo_num;
    U8              mirror_pattern;             // 9710
    U8              bayer_pattern;
    U32             frame_rate;
    int             pll_index;
    U32             mode_type;
    U32             mode_index;
    //amba_vin_black_level_compensation current_sw_blc;
    U32             current_shutter_time;
    U32             current_gain_db;
    U16             min_agc_index;
    U16             max_agc_index;
    U16             old_shr_width_upper;
    S32             current_slowshutter_mode;   // 9710

    GD_SENSOR_AGC_INFO_S  agc_info;
    //amba_vin_shutter_info_t shutter_info;
}GD_SENSOR_INFO_S;

typedef struct
{
    const char* name;
    U16         regAddr;
}GD_SENSOR_REG_S;

//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************



#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif



#endif /* _SENSOR_PRI_H_ */

