/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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
#include <rtdevice.h>

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

/* Sensor types */

#define RT_SENSOR_CLASS_NONE           (0)
#define RT_SENSOR_CLASS_ACCE           (1)  /* Accelerometer     */
#define RT_SENSOR_CLASS_GYRO           (2)  /* Gyroscope         */
#define RT_SENSOR_CLASS_MAG            (3)  /* Magnetometer      */
#define RT_SENSOR_CLASS_TEMP           (4)  /* Temperature       */
#define RT_SENSOR_CLASS_HUMI           (5)  /* Relative Humidity */
#define RT_SENSOR_CLASS_BARO           (6)  /* Barometer         */
#define RT_SENSOR_CLASS_LIGHT          (7)  /* Ambient light     */
#define RT_SENSOR_CLASS_PROXIMITY      (8)  /* Proximity         */
#define RT_SENSOR_CLASS_HR             (9)  /* Heart Rate        */
#define RT_SENSOR_CLASS_TVOC           (10) /* TVOC Level        */
#define RT_SENSOR_CLASS_NOISE          (11) /* Noise Loudness    */
#define RT_SENSOR_CLASS_STEP           (12) /* Step sensor       */
#define RT_SENSOR_CLASS_FORCE          (13) /* Force sensor      */
#define RT_SENSOR_CLASS_DUST           (14) /* Dust sensor       */
#define RT_SENSOR_CLASS_ECO2           (15) /* eCO2 sensor       */

/* Sensor vendor types */

#define RT_SENSOR_VENDOR_UNKNOWN       (0)
#define RT_SENSOR_VENDOR_STM           (1)  /* STMicroelectronics */
#define RT_SENSOR_VENDOR_BOSCH         (2)  /* Bosch */
#define RT_SENSOR_VENDOR_INVENSENSE    (3)  /* Invensense */
#define RT_SENSOR_VENDOR_SEMTECH       (4)  /* Semtech */
#define RT_SENSOR_VENDOR_GOERTEK       (5)  /* Goertek */
#define RT_SENSOR_VENDOR_MIRAMEMS      (6)  /* MiraMEMS */
#define RT_SENSOR_VENDOR_DALLAS        (7)  /* Dallas */
#define RT_SENSOR_VENDOR_ASAIR         (8)  /* Aosong */
#define RT_SENSOR_VENDOR_SHARP         (9)  /* Sharp */
#define RT_SENSOR_VENDOR_SENSIRION     (10) /* Sensirion */

/* Sensor unit types */

#define  RT_SENSOR_UNIT_NONE           (0)
#define  RT_SENSOR_UNIT_MG             (1)  /* Accelerometer           unit: mG         */
#define  RT_SENSOR_UNIT_MDPS           (2)  /* Gyroscope               unit: mdps       */
#define  RT_SENSOR_UNIT_MGAUSS         (3)  /* Magnetometer            unit: mGauss     */
#define  RT_SENSOR_UNIT_LUX            (4)  /* Ambient light           unit: lux        */
#define  RT_SENSOR_UNIT_CM             (5)  /* Distance                unit: cm         */
#define  RT_SENSOR_UNIT_PA             (6)  /* Barometer               unit: pa         */
#define  RT_SENSOR_UNIT_PERMILLAGE     (7)  /* Relative Humidity       unit: permillage */
#define  RT_SENSOR_UNIT_DCELSIUS       (8)  /* Temperature             unit: dCelsius   */
#define  RT_SENSOR_UNIT_HZ             (9)  /* Frequency               unit: HZ         */
#define  RT_SENSOR_UNIT_ONE            (10) /* Dimensionless quantity  unit: 1          */
#define  RT_SENSOR_UNIT_BPM            (11) /* Heart rate              unit: bpm        */
#define  RT_SENSOR_UNIT_MM             (12) /* Distance                unit: mm         */
#define  RT_SENSOR_UNIT_MN             (13) /* Force                   unit: mN         */

/* Sensor communication interface types */

#define  RT_SENSOR_INTF_I2C            (1 << 0)
#define  RT_SENSOR_INTF_SPI            (1 << 1)
#define  RT_SENSOR_INTF_UART           (1 << 2)
#define  RT_SENSOR_INTF_ONEWIRE        (1 << 3)

/* Sensor power mode types */

#define  RT_SENSOR_POWER_NONE          (0)
#define  RT_SENSOR_POWER_DOWN          (1)  /* power down mode   */
#define  RT_SENSOR_POWER_NORMAL        (2)  /* normal-power mode */
#define  RT_SENSOR_POWER_LOW           (3)  /* low-power mode    */
#define  RT_SENSOR_POWER_HIGH          (4)  /* high-power mode   */

/* Sensor work mode types */

#define  RT_SENSOR_MODE_NONE           (0)
#define  RT_SENSOR_MODE_POLLING        (1)  /* One shot only read a data */
#define  RT_SENSOR_MODE_INT            (2)  /* TODO: One shot interrupt only read a data */
#define  RT_SENSOR_MODE_FIFO           (3)  /* TODO: One shot interrupt read all fifo data */

/* Sensor control cmd types */

#define  RT_SENSOR_CTRL_GET_ID         (0)  /* Get device id */
#define  RT_SENSOR_CTRL_GET_INFO       (1)  /* Get sensor info */
#define  RT_SENSOR_CTRL_SET_RANGE      (2)  /* Set the measure range of sensor. unit is info of sensor */
#define  RT_SENSOR_CTRL_SET_ODR        (3)  /* Set output date rate. unit is HZ */
#define  RT_SENSOR_CTRL_SET_MODE       (4)  /* Set sensor's work mode. ex. RT_SENSOR_MODE_POLLING,RT_SENSOR_MODE_INT */
#define  RT_SENSOR_CTRL_SET_POWER      (5)  /* Set power mode. args type of sensor power mode. ex. RT_SENSOR_POWER_DOWN,RT_SENSOR_POWER_NORMAL */
#define  RT_SENSOR_CTRL_SELF_TEST      (6)  /* Take a self test */

#define  RT_SENSOR_CTRL_USER_CMD_START 0x100  /* User commands should be greater than 0x100 */

struct rt_sensor_info
{
    rt_uint8_t     type;                    /* The sensor type */
    rt_uint8_t     vendor;                  /* Vendor of sensors */
    const char    *model;                   /* model name of sensor */
    rt_uint8_t     unit;                    /* unit of measurement */
    rt_uint8_t     intf_type;               /* Communication interface type */
    rt_int32_t     range_max;               /* maximum range of this sensor's value. unit is 'unit' */
    rt_int32_t     range_min;               /* minimum range of this sensor's value. unit is 'unit' */
    rt_uint32_t    period_min;              /* Minimum measurement period,unit:ms. zero = not a constant rate */
    rt_uint8_t     fifo_max;
};

struct rt_sensor_intf
{
    char                       *dev_name;   /* The name of the communication device */
    rt_uint8_t                  type;       /* Communication interface type */
    void                       *user_data;  /* Private data for the sensor. ex. i2c addr,spi cs,control I/O */
};

struct rt_sensor_config
{
    struct rt_sensor_intf        intf;      /* sensor interface config */
    struct rt_device_pin_mode    irq_pin;   /* Interrupt pin, The purpose of this pin is to notification read data */
    rt_uint8_t                   mode;      /* sensor work mode */
    rt_uint8_t                   power;     /* sensor power mode */
    rt_uint16_t                  odr;       /* sensor out data rate */
    rt_int32_t                   range;     /* sensor range of measurement */
};

typedef struct rt_sensor_device *rt_sensor_t;

struct rt_sensor_device
{
    struct rt_device             parent;    /* The standard device */

    struct rt_sensor_info        info;      /* The sensor info data */
    struct rt_sensor_config      config;    /* The sensor config data */

    void                        *data_buf;  /* The buf of the data received */
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
    rt_int32_t x;
    rt_int32_t y;
    rt_int32_t z;
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
        rt_int32_t           temp;          /* Temperature.         unit: dCelsius    */
        rt_int32_t           humi;          /* Relative humidity.   unit: permillage  */
        rt_int32_t           baro;          /* Pressure.            unit: pascal (Pa) */
        rt_int32_t           light;         /* Light.               unit: lux         */
        rt_int32_t           proximity;     /* Distance.            unit: centimeters */
        rt_int32_t           hr;            /* Heart rate.          unit: bpm         */
        rt_int32_t           tvoc;          /* TVOC.                unit: permillage  */
        rt_int32_t           noise;         /* Noise Loudness.      unit: HZ          */
        rt_uint32_t          step;          /* Step sensor.         unit: 1           */
        rt_int32_t           force;         /* Force sensor.        unit: mN          */
        rt_uint32_t          dust;          /* Dust sensor.         unit: ug/m3       */
        rt_uint32_t          eco2;          /* eCO2 sensor.         unit: ppm         */
    } data;
};

struct rt_sensor_ops
{
    rt_size_t (*fetch_data)(struct rt_sensor_device *sensor, void *buf, rt_size_t len);
    rt_err_t (*control)(struct rt_sensor_device *sensor, int cmd, void *arg);
};

int rt_hw_sensor_register(rt_sensor_t sensor,
                          const char              *name,
                          rt_uint32_t              flag,
                          void                    *data);

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_H__ */
