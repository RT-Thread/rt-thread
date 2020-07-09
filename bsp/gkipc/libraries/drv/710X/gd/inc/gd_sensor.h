/*!
*******************************************************************************
**
** \file      gd_sensor.h
**
** \brief     sensor driver.
**
**            (C) Goke Microelectronics China 2002 - 2014
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Id: gd_sensor.h, v1.00 2014/07/14 08:13:54 $
**
******************************************************************************/
#ifndef _GD_SENSOR_H_
#define _GD_SENSOR_H_

#include <gtypes.h>
#include <gmodids.h>
#include "gd_i2c.h"
#include "gd_spi.h"

//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
#define GD_SENSOR_GPIO_NOT_USED     0xFF

/*! \brief The base error code for the sensor driver.*/
//#define GD_SENSOR_ERR_BASE (GD_SENSOR_MODULE_ID<<16)
#define GD_SENSOR_ERR_BASE (0x09<<16)

/*=========================Start GD_VIDEO_INFO==============================*/

#define GD_VIDEO_FPS(fps)               (512000000 / fps)
#define GD_VIDEO_FPS_AUTO               0           //0
#define GD_VIDEO_FPS_1                  512000000   //(512000000 / 1)
#define GD_VIDEO_FPS_2                  256000000   //(512000000 / 2)
#define GD_VIDEO_FPS_3                  170666667   //(512000000 / 3)
#define GD_VIDEO_FPS_3_125              163840000   //(512000000 / 25 * 8)
#define GD_VIDEO_FPS_3_75               136533333   //(512000000 / 15 * 4)
#define GD_VIDEO_FPS_4                  128000000   //(512000000 / 4)
#define GD_VIDEO_FPS_5                  102400000   //(512000000 / 5)
#define GD_VIDEO_FPS_6                   85333333   //(512000000 / 6)
#define GD_VIDEO_FPS_6_25                81920000   //(512000000 / 25 * 4)
#define GD_VIDEO_FPS_7_5                 68266667   //(512000000 / 15 * 2)
#define GD_VIDEO_FPS_10                  51200000   //(512000000 / 10)
#define GD_VIDEO_FPS_12                  42666667   //(512000000 / 12)
#define GD_VIDEO_FPS_12_5                40960000   //(512000000 / 25 * 2)
#define GD_VIDEO_FPS_13                  39384615   //(512000000 / 13)
#define GD_VIDEO_FPS_14                  36571428   //(512000000 / 14)
#define GD_VIDEO_FPS_15                  34133333   //(512000000 / 15)
#define GD_VIDEO_FPS_20                  25600000   //(512000000 / 20)
#define GD_VIDEO_FPS_23_976              21354688   //(512000000 / 23976 * 1000)
#define GD_VIDEO_FPS_24                  21333333   //(512000000 / 24)
#define GD_VIDEO_FPS_25                  20480000   //(512000000 / 25)
#define GD_VIDEO_FPS_29_97               17083750   //(512000000 / 2997 * 100)
#define GD_VIDEO_FPS_30                  17066667   //(512000000 / 30)
#define GD_VIDEO_FPS_50                  10240000   //(512000000 / 50)
#define GD_VIDEO_FPS_59_94                8541875   //(512000000 / 5994 * 100)
#define GD_VIDEO_FPS_60                   8533333   //(512000000 / 60)
#define GD_VIDEO_FPS_120                  4266667   //(512000000 / 120)

#define GD_VIDEO_BITS(bits)             (bits)
#define GD_VIDEO_BITS_AUTO              GD_VIDEO_BITS(0)
#define GD_VIDEO_BITS_8                 GD_VIDEO_BITS(8)
#define GD_VIDEO_BITS_10                GD_VIDEO_BITS(10)
#define GD_VIDEO_BITS_12                GD_VIDEO_BITS(12)
#define GD_VIDEO_BITS_14                GD_VIDEO_BITS(14)
#define GD_VIDEO_BITS_16                GD_VIDEO_BITS(16)

#define GD_VIDEO_RATIO(ratio)           (ratio)
#define GD_VIDEO_RATIO_AUTO             GD_VIDEO_RATIO(0)
#define GD_VIDEO_RATIO_4_3              GD_VIDEO_RATIO(1)
#define GD_VIDEO_RATIO_16_9             GD_VIDEO_RATIO(2)
#define GD_VIDEO_RATIO_1_1              GD_VIDEO_RATIO(4)

// SENSOR READ-OUT MODES
#define GD_SENSOR_SONYICX495_FRAME_READ_OUT (0x0)
#define GD_SENSOR_SONYICX495_4_16_HORI      (0x1)
#define GD_SENSOR_SONYICX495_4_16_NO_HORI   (0x2)
#define GD_SENSOR_SONYICX495_4_8_HORI       (0x3)
#define GD_SENSOR_SONYICX495_4_8_NO_HORI    (0x4)
#define GD_SENSOR_SONYICX495_AF_MODE        (0x5)

#define GD_SENSOR_MICRON_MP9T001_2xV_2xH_Binning                        (0x1)
#define GD_SENSOR_MICRON_MP9T001_CFA_PHHASE_CORRECTION_VERTICAL_ONLY    (0x2)
#define GD_SENSOR_MICRON_MP9T001_CFA_PHHASE_CORRECTION_HORIZONTAL_ONLY  (0x3)
//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************
enum
{
    /*!
    ** The SENSOR is not of the right mode to to perform
    ** a requested function, e.g. writing to a GPIO which was
    ** configured as input.
    */
    /*! IC could not be identified. */
    GD_ERR_SENSOR_UNKNOWN_DEVICE = GD_SENSOR_ERR_BASE,
    /*! Opening a sensor instance failed. */
    GD_ERR_SENSOR_OPEN,
    /*! The SENSOR is busy, e.g. with tuning. */
    GD_ERR_SENSOR_BUSY,
    /*! GPIO error, e.g. for reseting the SENSOR. */
    GD_ERR_SENSOR_GPIO,
    /*! I2C communication error. */
    GD_ERR_SENSOR_I2C,
    /*! SPI communication error. */
    GD_ERR_SENSOR_SPI,
    /*! Timeout, i.e. the SENSOR did not respond in time. */
    GD_ERR_SENSOR_TIMER,
    /*! Other error, not further specified. */
    GD_ERR_SENSOR_OTHER,
    GD_ERR_FUNC_NOT_SUPPORTED,
};

/*!
*******************************************************************************
**
** \brief Delivery system types.
**
******************************************************************************/
// SENSOR IDs
typedef enum
{
    GD_SENSOR_SYSTEM_TYPE_UNKOWN = 0,   //
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9T001     =   1,
    GD_SENSOR_SYSTEM_TYPE_ALTASENS_PROCAMHD  =   2,
    GD_SENSOR_SYSTEM_TYPE_SONY_ICX495CCD     =   3,
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9P001     =   4,    //micron 5meg, same for MT9P031
    GD_SENSOR_SYSTEM_TYPE_OV5260             =   5,
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9M002     =   6,    // micron 1.6meg
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9P401     =   7,
    GD_SENSOR_SYSTEM_TYPE_Altasens_ALTA3372  =   8,
    GD_SENSOR_SYSTEM_TYPE_Altasens_ALTA5262  =   9,
    GD_SENSOR_SYSTEM_TYPE_SONY_IMX017        =  10,
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9N001     =  11,    // micron 9meg
    GD_SENSOR_SYSTEM_TYPE_SONY_IMX039        =  12,
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9J001     =  13,    // micron 10meg
    GD_SENSOR_SYSTEM_TYPE_SEMCOYHD           =  14,
    GD_SENSOR_SYSTEM_TYPE_SONYIMX044         =  15,
    GD_SENSOR_SYSTEM_TYPE_OV5633             =  16,
    GD_SENSOR_SYSTEM_TYPE_OV9710             =  17,
    GD_SENSOR_SYSTEM_TYPE_OV9715             =  17,
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9V136     =  18,
    GD_SENSOR_SYSTEM_TYPE_OV7720             =  19,
    GD_SENSOR_SYSTEM_TYPE_OV7725             =  19,
    GD_SENSOR_SYSTEM_TYPE_OV7740             =  20,
    GD_SENSOR_SYSTEM_TYPE_OV10620            =  21,
    GD_SENSOR_SYSTEM_TYPE_OV10630            =  21,
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9P031     =  22,    // variant of micron5m
    GD_SENSOR_SYSTEM_TYPE_OV9810             =  23,
    GD_SENSOR_SYSTEM_TYPE_OV8810             =  24,
    GD_SENSOR_SYSTEM_TYPE_SONYIMX032         =  25,
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9P014     =  26,
    GD_SENSOR_SYSTEM_TYPE_OV2710             =  27,
    GD_SENSOR_SYSTEM_TYPE_OV2715             =  27,
    GD_SENSOR_SYSTEM_TYPE_OV5653             =  28,
    GD_SENSOR_SYSTEM_TYPE_SONYIMX035         =  29,
    GD_SENSOR_SYSTEM_TYPE_OV14810            =  29,
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9M033     =  30,
    GD_SENSOR_SYSTEM_TYPE_OV7962             =  31,
    GD_SENSOR_SYSTEM_TYPE_SEC_S5K4AWFX       =  32,    //Samsung
    GD_SENSOR_SYSTEM_TYPE_MICRON_MT9T002     =  32,    // copy from uItron iOne
    GD_SENSOR_SYSTEM_TYPE_SAMSUNG_S5K5B3GX   =  32,
    GD_SENSOR_SYSTEM_TYPE_SONYIMX072         =  33,
    GD_SENSOR_SYSTEM_TYPE_SONYIMX122         =  34,
    GD_SENSOR_SYSTEM_TYPE_SONYIMX222         =  34,
    GD_SENSOR_SYSTEM_TYPE_SONYIMX121         =  35,
    GD_SENSOR_SYSTEM_TYPE_MICRON_AR0331      =  42,
    GD_SENSOR_SYSTEM_TYPE_GENERIC_SENSOR     = 127,       //changed to 127 in new DSP firmware
}GD_SENSOR_SYSTEM_TYPE_E;

typedef enum
{
    GD_VIDEO_SYSTEM_AUTO = 0,
    GD_VIDEO_SYSTEM_NTSC,
    GD_VIDEO_SYSTEM_PAL,
    GD_VIDEO_SYSTEM_SECAM,
    GD_VIDEO_SYSTEM_ALL,
}GD_SENSOR_VIDEO_SYSTEM_E;


typedef enum
{
    GD_VIN_SRC_IDLE = 20000,
    GD_VIN_SRC_RESET,
    GD_VIN_SRC_SET_POWER,
    GD_VIN_SRC_SUSPEND,
    GD_VIN_SRC_RESUME,

    GD_VIN_SRC_GET_INFO = 20100,
    GD_VIN_SRC_GET_VIDEO_INFO,
    GD_VIN_SRC_GET_CAPABILITY,
    GD_VIN_SRC_CHECK_VIDEO_MODE,
    GD_VIN_SRC_SELECT_CHANNEL,
    GD_VIN_SRC_GET_AGC_INFO,
    GD_VIN_SRC_GET_SHUTTER_INFO,
    GD_VIN_SRC_GET_VBLANK_TIME,

    GD_VIN_SRC_GET_VIDEO_MODE = 21000,
    GD_VIN_SRC_GET_STILL_MODE,
    GD_VIN_SRC_GET_FPN,
    GD_VIN_SRC_GET_BLC,
    GD_VIN_SRC_GET_CAP_WINDOW,
    GD_VIN_SRC_GET_FRAME_RATE,    //Ref GD_VIDEO_FPS
    GD_VIN_SRC_GET_BLANK,
    GD_VIN_SRC_GET_PIXEL_SKIP_BIN,
    GD_VIN_SRC_GET_SHUTTER_TIME,
    GD_VIN_SRC_GET_GAIN_DB,
    GD_VIN_SRC_GET_CAPTURE_MODE,
    GD_VIN_SRC_GET_TRIGGER_MODE,
    GD_VIN_SRC_GET_LOW_LIGHT_MODE,
    GD_VIN_SRC_GET_SLOWSHUTTER_MODE,
    GD_VIN_SRC_GET_MIRROR_MODE,
    GD_VIN_SRC_GET_ANTI_FLICKER,
    GD_VIN_SRC_GET_DGAIN_RATIO,
    GD_VIN_SRC_GET_OPERATION_MODE,
    GD_VIN_SRC_GET_SENSOR_TEMPERATURE,

    GD_VIN_SRC_SET_VIDEO_MODE = 22000,
    GD_VIN_SRC_SET_STILL_MODE,
    GD_VIN_SRC_SET_FPN,
    GD_VIN_SRC_SET_BLC,
    GD_VIN_SRC_SET_CAP_WINDOW,
    GD_VIN_SRC_SET_FRAME_RATE,    //Ref GD_VIDEO_FPS
    GD_VIN_SRC_SET_BLANK,
    GD_VIN_SRC_SET_PIXEL_SKIP_BIN,
    GD_VIN_SRC_SET_SHUTTER_TIME,
    GD_VIN_SRC_SET_GAIN_DB,
    GD_VIN_SRC_SET_CAPTURE_MODE,
    GD_VIN_SRC_SET_TRIGGER_MODE,
    GD_VIN_SRC_SET_LOW_LIGHT_MODE,
    GD_VIN_SRC_SET_SLOWSHUTTER_MODE,
    GD_VIN_SRC_SET_MIRROR_MODE,
    GD_VIN_SRC_SET_ANTI_FLICKER,
    GD_VIN_SRC_SET_OPERATION_MODE,
    GD_VIN_SRC_SET_DGAIN_RATIO,

    GD_VIN_SRC_TEST_DUMP_REG = 29000,
    GD_VIN_SRC_TEST_GET_DEV_ID,
    GD_VIN_SRC_TEST_GET_REG_DATA,
    GD_VIN_SRC_TEST_SET_REG_DATA,

    GD_VIN_SRC_TEST_DUMP_SBRG_REG = 30000,
    GD_VIN_SRC_TEST_GET_SBRG_REG_DATA,
    GD_VIN_SRC_TEST_SET_SBRG_REG_DATA,
}GD_SENSOR_CMD_E;

/* ======================= Standart format defines ========================== */
typedef enum
{
    GD_VIDEO_MODE_MISC_FIRST    = 0,
    GD_VIDEO_MODE_AUTO          = 0,

    GD_VIDEO_MODE_320_240       = 1,        //320x240
    GD_VIDEO_MODE_320_288       = 2,        //320x288
    GD_VIDEO_MODE_360_240       = 3,        //360x240
    GD_VIDEO_MODE_360_288       = 4,        //360x288
    GD_VIDEO_MODE_480_240       = 5,        //480x240
    GD_VIDEO_MODE_720_240       = 6,        //720x240
    GD_VIDEO_MODE_960_240       = 7,        //960x240
    GD_VIDEO_MODE_VGA           = 8,        //640x480
    GD_VIDEO_MODE_SVGA          = 9,        //800x600
    GD_VIDEO_MODE_XGA           = 10,       //1024x768
    GD_VIDEO_MODE_SXGA          = 11,       //1280x1024
    GD_VIDEO_MODE_UXGA          = 12,       //1600x1200
    GD_VIDEO_MODE_QXGA          = 13,       //2048x1536
    GD_VIDEO_MODE_WVGA          = 14,       //800x480
    GD_VIDEO_MODE_WSVGA         = 15,       //1024x600
    GD_VIDEO_MODE_1280_960      = 16,       //1280x960
    GD_VIDEO_MODE_WXGA          = 17,       //1280x800
    GD_VIDEO_MODE_WSXGA         = 18,       //1440x900
    GD_VIDEO_MODE_WSXGAP        = 19,       //1680x1050
    GD_VIDEO_MODE_WUXGA         = 20,       //1920x1200

    /* Add new format below and update GD_VIDEO_MODE_NUM*/
    GD_VIDEO_MODE_480_640       = 21,       //480x640
    GD_VIDEO_MODE_SXGAP         = 22,       //1400x1050
    GD_VIDEO_MODE_QSXGA         = 23,       //2592x1944
    GD_VIDEO_MODE_HVGA          = 24,       //320x480
    GD_VIDEO_MODE_480_800       = 25,       //480x800
    GD_VIDEO_MODE_2048_1152     = 26,       //2048x1152
    GD_VIDEO_MODE_1920_1440     = 27,       //1920x1440
    GD_VIDEO_MODE_2560x1440     = 28,       //2560x1440, 3.7MP
    GD_VIDEO_MODE_2208x1242     = 29,       //2208x1242, 2.7MP
    GD_VIDEO_MODE_2304x1296     = 30,       //2304x1296
    GD_VIDEO_MODE_2304x1536     = 31,       //2304x1536, 3.4MP
    GD_VIDEO_MODE_240_400       = 32,       //240x400
    GD_VIDEO_MODE_2160P30       = 33,       //3840x2160@30fps
    GD_VIDEO_MODE_2160P25       = 34,       //3840x2160@25fps
    GD_VIDEO_MODE_2160P24       = 35,       //3840x2160@24fps
    GD_VIDEO_MODE_2160P24_SE    = 36,       //4096x2160@24fps, SMPTE
    GD_VIDEO_MODE_HDMI_NATIVE   = 37,       //Best Native Resolution
    GD_VIDEO_MODE_720P24        = 38,       //720p24
    GD_VIDEO_MODE_720P25        = 39,       //720p25
    GD_VIDEO_MODE_720P30        = 40,       //720p30
    GD_VIDEO_MODE_1296P60       = 41,       //2304x1296@60fps
    GD_VIDEO_MODE_1152x648      = 42,       //1152x648
    GD_VIDEO_MODE_4096x2160     = 43,       //4096x2160
    GD_VIDEO_MODE_4016x3016     = 44,       //4016x3016
    GD_VIDEO_MODE_4000x3000     = 45,       //4000x3000
    GD_VIDEO_MODE_960_540       = 46,       //960x540
    GD_VIDEO_MODE_3280_2464     = 47,       //3280x2464
    GD_VIDEO_MODE_3280_1852     = 48,       //3280x1852
    GD_VIDEO_MODE_2520_1424     = 49,       //2520x1424
    GD_VIDEO_MODE_1640_1232     = 50,       //1640x1232
    GD_VIDEO_MODE_2048_1080     = 51,       //2048x1080
    GD_VIDEO_MODE_3840x2160     = 52,       //3840x2160
    GD_VIDEO_MODE_768_512       = 53,       //768x512
    GD_VIDEO_MODE_FWVGA         = 54,       //854x480
    GD_VIDEO_MODE_1296_972      = 55,       //1296x972
    GD_VIDEO_MODE_640_400       = 56,       //640x400
    GD_VIDEO_MODE_1296_1032     = 57,       //1296x1032
    GD_VIDEO_MODE_3264_2448     = 58,       //3264x2448
    GD_VIDEO_MODE_2304_1836     = 59,       //2304x1836
    GD_VIDEO_MODE_3264_1836     = 60,       //3264x1836
    GD_VIDEO_MODE_2208_1836     = 61,       //2208x1836
    GD_VIDEO_MODE_1280_918      = 62,       //1280x918
    GD_VIDEO_MODE_816_612       = 63,       //816x612
    GD_VIDEO_MODE_320_306       = 64,       //320x306
    GD_VIDEO_MODE_3072_2048     = 65,       //3072x2048
    GD_VIDEO_MODE_2592_1944     = 66,       //2592x1944
    GD_VIDEO_MODE_1536_1024     = 67,       //1536x1024
    GD_VIDEO_MODE_2560_2048     = 68,       //2560x2048
    GD_VIDEO_MODE_MISC_LAST,

    GD_VIDEO_MODE_OFF           = 0xF000,

    //Still Standard
    GD_VIDEO_MODE_STILL_FIRST   = 0xFFE0,
    GD_VIDEO_MODE_3M_4_3        = 0xFFE0,
    GD_VIDEO_MODE_3M_16_9       = 0xFFE1,
    GD_VIDEO_MODE_4M_4_3        = 0xFFE2,
    GD_VIDEO_MODE_4M_16_9       = 0xFFE3,
    GD_VIDEO_MODE_5M_4_3        = 0xFFE4,
    GD_VIDEO_MODE_5M_16_9       = 0xFFE5,
    GD_VIDEO_MODE_STILL_LAST,

    //Video Standard
    GD_VIDEO_MODE_STANDARD_FIRST= 0xFFF0,
    GD_VIDEO_MODE_480I          = 0xFFF0,
    GD_VIDEO_MODE_576I          = 0xFFF1,
    GD_VIDEO_MODE_D1_NTSC       = 0xFFF2,   //480p
    GD_VIDEO_MODE_D1_PAL        = 0xFFF3,   //576p
    GD_VIDEO_MODE_720P          = 0xFFF4,
    GD_VIDEO_MODE_720P_PAL      = 0xFFF5,   //720p50
    GD_VIDEO_MODE_1080I         = 0xFFF6,
    GD_VIDEO_MODE_1080I_PAL     = 0xFFF7,   //1080i50
    GD_VIDEO_MODE_1080P         = 0xFFF8,
    GD_VIDEO_MODE_1080P_PAL     = 0xFFF9,   //1080i50
    GD_VIDEO_MODE_1080I48       = 0xFFFA,   //1080i48
    GD_VIDEO_MODE_1080P24       = 0xFFFB,   //1080p24
    GD_VIDEO_MODE_1080P25       = 0xFFFC,   //1080p25
    GD_VIDEO_MODE_1080P30       = 0xFFFD,   //1080p30
    GD_VIDEO_MODE_1080P60       = 0xFFFE,
    GD_VIDEO_MODE_STANDARD_LAST = 0xFFFF,

    GD_VIDEO_MODE_TEST          = 0xFFFE,
    GD_VIDEO_MODE_MAX           = 0xFFFF,
}GD_VIDEO_MODE_E;

typedef enum
{
    GD_VIN_SRC_MIRROR_HORRIZONTALLY_VERTICALLY = 0,
    GD_VIN_SRC_MIRROR_HORRIZONTALLY,
    GD_VIN_SRC_MIRROR_VERTICALLY,
    GD_VIN_SRC_MIRROR_NONE,
    GD_VIN_SRC_MIRROR_AUTO = 255,
}GD_SENSOR_MIRROR_PATTERN_E;

typedef enum
{
    GD_VIN_SRC_BAYER_PATTERN_RG = 0,
    GD_VIN_SRC_BAYER_PATTERN_BG,
    GD_VIN_SRC_BAYER_PATTERN_GR,
    GD_VIN_SRC_BAYER_PATTERN_GB,

    GD_VIN_SRC_BAYER_PATTERN_AUTO = 255,
}GD_SENSOR_BAYER_PATTERN_E;

//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************
/*!
*******************************************************************************
**
** \brief Front-end device data parameters.
**
** \sa    GD_SENSOR_OPEN_PARAMS_S
**
******************************************************************************/
typedef struct
{
    /* Delivery system type of sensor. */
    GD_SENSOR_SYSTEM_TYPE_E systemType;
    /*! I2C device address for Sensor. */
    U8 i2cAddrSensor;
    /*! Handle of I2C channel for communication. */
    GD_HANDLE handleI2C;
    /*! Handle of I2C channel for communication. */
    GD_HANDLE handleSPI;
    GD_HANDLE spicsGPIO;
    /*! Handle of GPIO pin to reset the sensor (NULL = no HW reset). */
    GD_HANDLE resetGPIO;
    GD_HANDLE powerGPIO;
    /*! Device specific function for docmd the sensor. */
    GERR (*sensorDoCmdFct)(GD_HANDLE*, GD_SENSOR_CMD_E, void*);
    /*! Device specific function for closing the sensor. */
    GERR (*sensorCloseFct)(GD_HANDLE*);
    /*! Device specific function for resetting the sensor. */
    GERR (*sensorResetFct)(GD_HANDLE*);
    void* pinfo;
    char* name;
}GD_SENSOR_DEVICE_DATA_S;

/*!
*******************************************************************************
**
** \brief Open parameters.
**
** \sa    GD_SENSOR_Open()
**
******************************************************************************/
typedef struct
{
    /*! I2C open parameters (NULL = not used). */
    GD_I2C_OPEN_PARAMS_S* pI2COpenParams;
    /*! I2C device address for Sensor. */
    U8 i2cAddrSensor;

    GD_SPI_OPEN_PARAMS_S* pSPIOpenParams;

    GBOOL usei2c;

    S8 resetGPIO;
    S8 powerGPIO;

    /*! Delivery system type. */
    GD_SENSOR_SYSTEM_TYPE_E systemType;
    /*!
    ** Pointer to open function of device specific driver.
    ** If set to NULL, the low level sensor drivers provided
    ** by the GOKESDK will be used.
    */
    GERR (*sensorOpenFct)(GD_SENSOR_DEVICE_DATA_S*);
    char* name;
}GD_SENSOR_OPEN_PARAMS_S;

typedef struct
{
    U32     width;
    U32     height;
    U32     fps;
    U8      format;
    U8      type;
    U8      bits;
    U8      ratio;
    U8      system;
    U8      flip;
    U8      rotate;
    U16     rev;
}GD_SENSOR_VIDEO_INFO_S;


/* agc info */
typedef struct
{
    S32    db_max;
    S32    db_min;
    S32    db_step;
}GD_SENSOR_AGC_INFO_S;

typedef struct
{
    U16        max_shutter_value;    // not used
    U16        min_shutter_value;    // not used
    U16        shutter_step;        // shutter_step/gain_step
}GD_SENSOR_SHUTTER_INFO_S;

typedef struct
{
    GD_SENSOR_MIRROR_PATTERN_E pattern;
    GD_SENSOR_BAYER_PATTERN_E  bayer_pattern;
}GD_SENSOR_MIRROR_MODE_S;

typedef struct
{
    U32 reg;
    U32 data;
    U32 regmap;
}GD_SENSOR_REG_DATA_S;

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

GERR GD_SENSOR_Init(void);
GERR GD_SENSOR_Open(GD_SENSOR_OPEN_PARAMS_S* pOpenParams, GD_HANDLE* pHandle);
GERR GD_SENSOR_Close(GD_HANDLE* pHandle);
GERR GD_SENSOR_Reset(GD_HANDLE* pHandle);
GERR GD_SENSOR_Sleep(U32 nMesc);
GERR GD_SENSOR_DoCmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args);

/* open functions for front end detect */
GERR GD_SENSOR_DetectOpen_OV2710_parallel(GD_SENSOR_OPEN_PARAMS_S* pOpenParams, GD_HANDLE* pHandle);
GERR GD_SENSOR_Detect_OV2710_parallel(GD_I2C_OPEN_PARAMS_S* pI2COpenParams);
GERR GD_SENSOR_DetectOpen_OV9710(GD_SENSOR_OPEN_PARAMS_S* pOpenParams, GD_HANDLE* pHandle);
GERR GD_SENSOR_Detect_OV9710(GD_I2C_OPEN_PARAMS_S* pI2COpenParams);
GERR GD_SENSOR_DetectOpen_IMX222(GD_SENSOR_OPEN_PARAMS_S* pOpenParams, GD_HANDLE* pHandle);
GERR GD_SENSOR_Detect_IMX222(GD_SPI_OPEN_PARAMS_S* pSPIOpenParams);

#ifdef __cplusplus
}
#endif



#endif /* _GD_SENSOR_H_ */
/* end of gd_sensor.h */

