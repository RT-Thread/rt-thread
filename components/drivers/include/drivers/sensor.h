/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-31     flybreak     first version
 */

#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <rtthread.h>
#include "pin.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_RTC
#define  rt_sensor_get_ts()  time(RT_NULL)   /* API for the sensor to get the timestamp */
#else
#define  rt_sensor_get_ts()  rt_tick_get()   /* API for the sensor to get the timestamp */
#endif

#define  RT_PIN_NONE                   0xFFFF    /* RT PIN NONE */
#define  RT_DEVICE_FLAG_FIFO_RX        0x200     /* Flag to use when the sensor is open by fifo mode */

#define  RT_SENSOR_MODULE_MAX          (3)       /* The maximum number of members of a sensor module */

#define RT_SENSOR_MACRO_GET_NAME(macro) (macro##_STR)

/* Sensor types */
#define RT_SENSOR_TYPE_NONE           (0)
#define RT_SENSOR_TYPE_NONE_STR       "None"
#define RT_SENSOR_TYPE_ACCE           (1)
#define RT_SENSOR_TYPE_ACCE_STR       "Accelerometer"
#define RT_SENSOR_TYPE_GYRO           (2)
#define RT_SENSOR_TYPE_GYRO_STR       "Gyroscope"
#define RT_SENSOR_TYPE_MAG            (3)
#define RT_SENSOR_TYPE_MAG_STR        "Magnetometer"
#define RT_SENSOR_TYPE_TEMP           (4)
#define RT_SENSOR_TYPE_TEMP_STR       "Temperature"
#define RT_SENSOR_TYPE_HUMI           (5)
#define RT_SENSOR_TYPE_HUMI_STR       "Relative Humidity"
#define RT_SENSOR_TYPE_BARO           (6)
#define RT_SENSOR_TYPE_BARO_STR       "Barometer"
#define RT_SENSOR_TYPE_LIGHT          (7)
#define RT_SENSOR_TYPE_LIGHT_STR      "Ambient light"
#define RT_SENSOR_TYPE_PROXIMITY      (8)
#define RT_SENSOR_TYPE_PROXIMITY_STR  "Proximity"
#define RT_SENSOR_TYPE_HR             (9)
#define RT_SENSOR_TYPE_HR_STR         "Heart Rate"
#define RT_SENSOR_TYPE_TVOC           (10)
#define RT_SENSOR_TYPE_TVOC_STR       "TVOC Level"
#define RT_SENSOR_TYPE_NOISE          (11)
#define RT_SENSOR_TYPE_NOISE_STR      "Noise Loudness"
#define RT_SENSOR_TYPE_STEP           (12)
#define RT_SENSOR_TYPE_STEP_STR       "Step"
#define RT_SENSOR_TYPE_FORCE          (13)
#define RT_SENSOR_TYPE_FORCE_STR      "Force"
#define RT_SENSOR_TYPE_DUST           (14)
#define RT_SENSOR_TYPE_DUST_STR       "Dust"
#define RT_SENSOR_TYPE_ECO2           (15)
#define RT_SENSOR_TYPE_ECO2_STR       "eCO2"
#define RT_SENSOR_TYPE_GNSS           (16)
#define RT_SENSOR_TYPE_GNSS_STR       "GNSS"
#define RT_SENSOR_TYPE_TOF            (17)
#define RT_SENSOR_TYPE_TOF_STR        "ToF"
#define RT_SENSOR_TYPE_SPO2           (18)
#define RT_SENSOR_TYPE_SPO2_STR       "SpO2"
#define RT_SENSOR_TYPE_IAQ            (19)
#define RT_SENSOR_TYPE_IAQ_STR        "IAQ"
#define RT_SENSOR_TYPE_ETOH           (20)
#define RT_SENSOR_TYPE_ETOH_STR       "EtOH"
#define RT_SENSOR_TYPE_BP             (21)
#define RT_SENSOR_TYPE_BP_STR         "Blood Pressure"

/* Sensor vendor types */
#define RT_SENSOR_VENDOR_UNKNOWN       (0)
#define RT_SENSOR_VENDOR_UNKNOWN_STR   "Vendor Unknown"
#define RT_SENSOR_VENDOR_STM           (1)
#define RT_SENSOR_VENDOR_STM_STR       "STMicroelectronics"
#define RT_SENSOR_VENDOR_BOSCH         (2)
#define RT_SENSOR_VENDOR_BOSCH_STR     "Bosch"
#define RT_SENSOR_VENDOR_INVENSENSE    (3)
#define RT_SENSOR_VENDOR_INVENSENSE_STR "Invensense"
#define RT_SENSOR_VENDOR_SEMTECH       (4)
#define RT_SENSOR_VENDOR_SEMTECH_STR   "Semtech"
#define RT_SENSOR_VENDOR_GOERTEK       (5)
#define RT_SENSOR_VENDOR_GOERTEK_STR   "Goertek"
#define RT_SENSOR_VENDOR_MIRAMEMS      (6)
#define RT_SENSOR_VENDOR_MIRAMEMS_STR  "MiraMEMS"
#define RT_SENSOR_VENDOR_DALLAS        (7)
#define RT_SENSOR_VENDOR_DALLAS_STR    "Dallas"
#define RT_SENSOR_VENDOR_ASAIR         (8)
#define RT_SENSOR_VENDOR_ASAIR_STR     "Aosong"
#define RT_SENSOR_VENDOR_SHARP         (9)
#define RT_SENSOR_VENDOR_SHARP_STR     "Sharp"
#define RT_SENSOR_VENDOR_SENSIRION     (10)
#define RT_SENSOR_VENDOR_SENSIRION_STR "Sensirion"
#define RT_SENSOR_VENDOR_TI            (11)
#define RT_SENSOR_VENDOR_TI_STR        "Texas Instruments"
#define RT_SENSOR_VENDOR_PLANTOWER     (12)
#define RT_SENSOR_VENDOR_PLANTOWER_STR "Plantower"
#define RT_SENSOR_VENDOR_AMS           (13)
#define RT_SENSOR_VENDOR_AMS_STR       "ams-OSRAM AG"
#define RT_SENSOR_VENDOR_MAXIM         (14)
#define RT_SENSOR_VENDOR_MAXIM_STR     "Maxim Integrated"
#define RT_SENSOR_VENDOR_MELEXIS       (15)
#define RT_SENSOR_VENDOR_MELEXIS_STR   "Melexis"

/* Sensor unit types */
#define RT_SENSOR_UNIT_NONE           (0)  /* Dimensionless quantity */
#define RT_SENSOR_UNIT_NONE_STR       ""
#define RT_SENSOR_UNIT_MG             (1)  /* Accelerometer           unit: mG         */
#define RT_SENSOR_UNIT_MG_STR         "mG"
#define RT_SENSOR_UNIT_MDPS           (2)  /* Gyroscope               unit: mdps       */
#define RT_SENSOR_UNIT_MDPS_STR       "mdps"
#define RT_SENSOR_UNIT_MGAUSS         (3)  /* Magnetometer            unit: mGauss     */
#define RT_SENSOR_UNIT_MGAUSS_STR     "mGauss"
#define RT_SENSOR_UNIT_LUX            (4)  /* Ambient light           unit: lux        */
#define RT_SENSOR_UNIT_LUX_STR        "lux"
#define RT_SENSOR_UNIT_CM             (5)  /* Distance                unit: cm         */
#define RT_SENSOR_UNIT_CM_STR         "cm"
#define RT_SENSOR_UNIT_MM             (6)  /* Distance                unit: mm         */
#define RT_SENSOR_UNIT_MM_STR         "mm"
#define RT_SENSOR_UNIT_PA             (7)  /* Barometer               unit: Pa         */
#define RT_SENSOR_UNIT_PA_STR         "Pa"
#define RT_SENSOR_UNIT_MMHG           (8)  /* Blood Pressure          unit: mmHg       */
#define RT_SENSOR_UNIT_MMHG_STR       "mmHg"
#define RT_SENSOR_UNIT_PERCENTAGE     (9)  /* Relative Humidity       unit: percentage */
#define RT_SENSOR_UNIT_PERCENTAGE_STR "%"
#define RT_SENSOR_UNIT_CELSIUS        (10) /* Temperature             unit: Celsius ℃ */
#define RT_SENSOR_UNIT_CELSIUS_STR    "C"
#define RT_SENSOR_UNIT_FAHRENHEIT     (11) /* Temperature             unit: Fahrenheit ℉ */
#define RT_SENSOR_UNIT_FAHRENHEIT_STR "F"
#define RT_SENSOR_UNIT_KELVIN         (12) /* Temperature             unit: K          */
#define RT_SENSOR_UNIT_KELVIN_STR     "K"
#define RT_SENSOR_UNIT_HZ             (13) /* Frequency               unit: Hz         */
#define RT_SENSOR_UNIT_HZ_STR         "Hz"
#define RT_SENSOR_UNIT_BPM            (14) /* Heart rate              unit: bpm        */
#define RT_SENSOR_UNIT_BPM_STR        "bpm"
#define RT_SENSOR_UNIT_MN             (15) /* Force                   unit: mN         */
#define RT_SENSOR_UNIT_MN_STR         "mN"
#define RT_SENSOR_UNIT_N              (16) /* Force                   unit: N          */
#define RT_SENSOR_UNIT_N_STR          "N"
#define RT_SENSOR_UNIT_PPM            (17) /* Concentration           unit: ppm        */
#define RT_SENSOR_UNIT_PPM_STR        "ppm"
#define RT_SENSOR_UNIT_PPB            (18) /* Concentration           unit: ppb        */
#define RT_SENSOR_UNIT_PPB_STR        "ppb"
#define RT_SENSOR_UNIT_DMS            (19) /* Coordinates             unit: DMS        */
#define RT_SENSOR_UNIT_DMS_STR        "DMS"
#define RT_SENSOR_UNIT_DD             (20) /* Coordinates             unit: DD         */
#define RT_SENSOR_UNIT_DD_STR         "DD"
#define RT_SENSOR_UNIT_MGM3           (21) /* Concentration           unit: mg/m3      */
#define RT_SENSOR_UNIT_MGM3_STR       "mg/m3"

/* Sensor communication interface types */
#define RT_SENSOR_INTF_I2C            (1 << 0)
#define RT_SENSOR_INTF_I2C_STR        "I2C"
#define RT_SENSOR_INTF_SPI            (1 << 1)
#define RT_SENSOR_INTF_SPI_STR        "SPI"
#define RT_SENSOR_INTF_UART           (1 << 2)
#define RT_SENSOR_INTF_UART_STR       "UART"
#define RT_SENSOR_INTF_ONEWIRE        (1 << 3)
#define RT_SENSOR_INTF_ONEWIRE_STR    "1-Wire"

/* Sensor power mode types */
#define RT_SENSOR_POWER_NONE          (0)
#define RT_SENSOR_POWER_NONE_STR      "None"
#define RT_SENSOR_POWER_DOWN          (1)  /* power down mode   */
#define RT_SENSOR_POWER_DOWN_STR      "Down"
#define RT_SENSOR_POWER_NORMAL        (2)  /* normal-power mode */
#define RT_SENSOR_POWER_NORMAL_STR    "Normal"
#define RT_SENSOR_POWER_LOW           (3)  /* low-power mode    */
#define RT_SENSOR_POWER_LOW_STR       "Low"
#define RT_SENSOR_POWER_HIGH          (4)  /* high-power mode   */
#define RT_SENSOR_POWER_HIGH_STR      "High"

/* Sensor fetch data mode types */
#define RT_SENSOR_FETCH_NONE          (0)
#define RT_SENSOR_FETCH_POLLING       (1)  /* One shot only read a data */
#define RT_SENSOR_FETCH_INT           (2)  /* TODO: One shot interrupt only read a data */
#define RT_SENSOR_FETCH_FIFO          (3)  /* TODO: One shot interrupt read all fifo data */

/* Sensor control cmd types */
#define RT_SENSOR_CTRL_SET_FETCH_MODE      (RT_DEVICE_CTRL_BASE(Sensor) + 1)  /* Set fetch data mode. ex. RT_SENSOR_FETCH_POLLING,RT_SENSOR_FETCH_INT */
#define RT_SENSOR_CTRL_SET_RATE_MODE       (RT_DEVICE_CTRL_BASE(Sensor) + 2)  /* Set data output rate mode. should be defined in specific sensor driver header file */
#define RT_SENSOR_CTRL_SET_POWER_MODE      (RT_DEVICE_CTRL_BASE(Sensor) + 3)  /* Set power mode. args type of sensor power mode. ex. RT_SENSOR_POWER_DOWN, RT_SENSOR_POWER_NORMAL */
#define RT_SENSOR_CTRL_SET_SCALE_MODE      (RT_DEVICE_CTRL_BASE(Sensor) + 4)  /* Set scale mode. should be defined in specific sensor driver header file */
#define RT_SENSOR_CTRL_SET_RESOLUTION_MODE (RT_DEVICE_CTRL_BASE(Sensor) + 5)  /* Set resolution mode. should be defined in specific sensor driver header file */
#define RT_SENSOR_CTRL_SELF_TEST           (RT_DEVICE_CTRL_BASE(Sensor) + 6)  /* Take a self test */
#define RT_SENSOR_CTRL_SOFTRESET           (RT_DEVICE_CTRL_BASE(Sensor) + 7)  /* soft reset sensor */

#define  RT_SENSOR_CTRL_USER_CMD_START 0x100  /* User commands should be greater than 0x100 */

/* sensor floating data type */
#ifdef RT_USING_SENSOR_DOUBLE_FLOAT
typedef double rt_sensor_float_t;
#else
typedef float rt_sensor_float_t;
#endif /* RT_USING_SENSOR_DOUBLE_FLOAT */

/* sensor basic information */
struct rt_sensor_info
{
    rt_uint8_t          type;               /* the sensor type */
    rt_uint8_t          vendor;             /* vendor of sensors */
    const char         *name;               /* sensor name */
    rt_uint8_t          unit;               /* unit of measurement */
    rt_uint8_t          intf_type;          /* sensor supports communication interface type, such as RT_SENSOR_INTF_I2C | RT_SENSOR_INTF_SPI */
    rt_uint8_t          fifo_max;
};

/* sensor interface */
struct rt_sensor_intf
{
    char          *com_dev_name;            /* the name of the communication device */
    rt_uint8_t     type;                    /* current sensor communication interface type, such as RT_SENSOR_INTF_I2C (only choose one) */
    void          *arg;                     /* Interface argument for the sensor. ex. i2c addr, spi cs, control I/O */
};

/* sensor configuration */
struct rt_sensor_config
{
    /* application users configurations */
    struct rt_sensor_intf       intf;       /* sensor interface config */
    struct rt_device_pin_mode   irq_pin;    /* interrupt pin, The purpose of this pin is to notification read data */

    /* internel configurations */
    rt_uint8_t                  fetch_mode; /* sensor mode, eg. polling / interrupt / fifo */
    rt_uint8_t                  power_mode; /* sensor power mode eg. power down / high / normal / low */
    rt_uint8_t                  scale_mode; /* sensor scale mode, defined in specific sensor driver header file */
    rt_uint8_t                  rate_mode;  /* sensor output data rate mode, defined in specific sensor driver header file */
    rt_uint8_t                  resolution_mode; /* sensor resolution mode, defined in specific sensor driver header file */
    rt_sensor_float_t           range_max;  /* maximum range of this sensor's value. unit is 'unit' */
    rt_sensor_float_t           range_min;  /* minimum range of this sensor's value. unit is 'unit' */
    rt_sensor_float_t           resolution; /* sensor resolution */
    rt_sensor_float_t           error;      /* sensor error */
    rt_uint32_t                 period_min; /* minimum measurement period,unit:ms. 0 = not a constant rate */
};

typedef struct rt_sensor_device *rt_sensor_t;
typedef struct rt_sensor_data   *rt_sensor_data_t;
typedef struct rt_sensor_info   *rt_sensor_info_t;

struct rt_sensor_device
{
    struct rt_device             parent;    /* The standard device */

    struct rt_sensor_info        info;      /* The sensor info data */
    struct rt_sensor_config      config;    /* The sensor config data */

    rt_sensor_data_t             data_buf;  /* The buf of the data received */
    rt_size_t                    data_len;  /* The size of the data received */

    const struct rt_sensor_ops  *ops;       /* The sensor ops */

    struct rt_sensor_module     *module;    /* The sensor module */

    rt_err_t (*irq_handle)(rt_sensor_t sensor);             /* Called when an interrupt is generated, registered by the driver */
};

struct rt_sensor_module
{
    rt_mutex_t                   lock;                      /* The module lock */

    rt_sensor_t                  sen[RT_SENSOR_MODULE_MAX]; /* The module contains a list of sensors */
    rt_uint8_t                   sen_num;                   /* Number of sensors contained in the module */
};

/* 3-axis Data Type */
struct sensor_3_axis
{
    rt_sensor_float_t x;
    rt_sensor_float_t y;
    rt_sensor_float_t z;
};

/* Blood Pressure Data Type */
struct sensor_bp
{
    rt_sensor_float_t sbp; /* SBP: systolic pressure */
    rt_sensor_float_t dbp; /* DBP: diastolic pressure */
};

struct coordinates
{
    rt_sensor_float_t longitude;
    rt_sensor_float_t latitude;
};

struct rt_sensor_data
{
    rt_uint32_t         timestamp;          /* The timestamp when the data was received */
    rt_uint8_t          type;               /* The sensor type of the data */
    union
    {
        struct sensor_3_axis acce;          /* Accelerometer.       unit: mG          */
        struct sensor_3_axis gyro;          /* Gyroscope.           unit: mdps        */
        struct sensor_3_axis mag;           /* Magnetometer.        unit: mGauss      */
        struct coordinates   coord;         /* Coordinates          unit: degrees     */
        struct sensor_bp     bp;            /* BloodPressure.       unit: mmHg        */
        rt_sensor_float_t    temp;          /* Temperature.         unit: dCelsius    */
        rt_sensor_float_t    humi;          /* Relative humidity.   unit: permillage  */
        rt_sensor_float_t    baro;          /* Pressure.            unit: pascal (Pa) */
        rt_sensor_float_t    light;         /* Light.               unit: lux         */
        rt_sensor_float_t    proximity;     /* Distance.            unit: centimeters */
        rt_sensor_float_t    hr;            /* Heart rate.          unit: bpm         */
        rt_sensor_float_t    tvoc;          /* TVOC.                unit: permillage  */
        rt_sensor_float_t    noise;         /* Noise Loudness.      unit: HZ          */
        rt_sensor_float_t    step;          /* Step sensor.         unit: 1           */
        rt_sensor_float_t    force;         /* Force sensor.        unit: mN          */
        rt_sensor_float_t    dust;          /* Dust sensor.         unit: ug/m3       */
        rt_sensor_float_t    eco2;          /* eCO2 sensor.         unit: ppm         */
        rt_sensor_float_t    spo2;          /* SpO2 sensor.         unit: permillage  */
        rt_sensor_float_t    iaq;           /* IAQ sensor.          unit: 1           */
        rt_sensor_float_t    etoh;          /* EtOH sensor.         unit: ppm         */
    } data;
};

struct rt_sensor_ops
{
    rt_ssize_t (*fetch_data)(rt_sensor_t sensor, rt_sensor_data_t buf, rt_size_t len);
    rt_err_t (*control)(rt_sensor_t sensor, int cmd, void *arg);
};

int rt_hw_sensor_register(rt_sensor_t     sensor,
                          const char     *name,
                          rt_uint32_t     flag,
                          void           *data);

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_H__ */
