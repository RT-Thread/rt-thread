/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-06-02     Bernard      the first version
 * 2018-08-02     Tanek        split run and sleep modes, support custom mode
 * 2019-04-28     Zero-Free    improve PM mode and device ops interface
 * 2020-11-23     zhangsz      update pm mode select
 * 2020-11-27     zhangsz      update pm 2.0
 */

#ifndef __PM_H__
#define __PM_H__

#include <stdint.h>
#include <rtthread.h>
#include <drivers/lptimer.h>

/* All modes used for rt_pm_request() and rt_pm_release() */
enum
{
    /* sleep modes */
    PM_SLEEP_MODE_NONE = 0,
    PM_SLEEP_MODE_IDLE,
    PM_SLEEP_MODE_LIGHT,
    PM_SLEEP_MODE_DEEP,
    PM_SLEEP_MODE_STANDBY,
    PM_SLEEP_MODE_SHUTDOWN,
    PM_SLEEP_MODE_MAX,
};

enum
{
    /* run modes*/
    PM_RUN_MODE_HIGH_SPEED = 0,
    PM_RUN_MODE_NORMAL_SPEED,
    PM_RUN_MODE_MEDIUM_SPEED,
    PM_RUN_MODE_LOW_SPEED,
    PM_RUN_MODE_MAX,
};

enum
{
    RT_PM_FREQUENCY_PENDING = 0x01,
};

/* The name of all modes used in the msh command "pm_dump" */
#define PM_SLEEP_MODE_NAMES     \
{                               \
    "None Mode",                \
    "Idle Mode",                \
    "LightSleep Mode",          \
    "DeepSleep Mode",           \
    "Standby Mode",             \
    "Shutdown Mode",            \
}

#define PM_RUN_MODE_NAMES       \
{                               \
    "High Speed",               \
    "Normal Speed",             \
    "Medium Speed",             \
    "Low Mode",                 \
}

#ifndef PM_USING_CUSTOM_CONFIG
/**
 * Modules used for
 * pm_module_request(PM_BOARD_ID, PM_SLEEP_MODE_IDLE)
 * pm_module_release(PM_BOARD_ID, PM_SLEEP_MODE_IDLE)
 * pm_module_release_all(PM_BOARD_ID, PM_SLEEP_MODE_IDLE)
 */
enum pm_module_id {
    PM_NONE_ID = 0,
    PM_POWER_ID,
    PM_BOARD_ID,
    PM_BSP_ID,
    PM_MAIN_ID,
    PM_PMS_ID,
    PM_PMC_ID,
    PM_TASK_ID,
    PM_SPI_ID,
    PM_I2C_ID,
    PM_UART_ID,
    PM_CAN_ID,
    PM_ETH_ID,
    PM_SENSOR_ID,
    PM_LCD_ID,
    PM_KEY_ID,
    PM_TP_ID,
    PM_MODULE_MAX_ID, /* enum must! */
};

#else

#include <pm_cfg.h>

#endif /* PM_USING_CUSTOM_CONFIG */

#ifndef RT_PM_DEFAULT_SLEEP_MODE
#define RT_PM_DEFAULT_SLEEP_MODE        PM_SLEEP_MODE_NONE
#endif

#ifndef RT_PM_DEFAULT_DEEPSLEEP_MODE
#define RT_PM_DEFAULT_DEEPSLEEP_MODE    PM_SLEEP_MODE_DEEP
#endif

#ifndef RT_PM_DEFAULT_RUN_MODE
#define RT_PM_DEFAULT_RUN_MODE          PM_RUN_MODE_NORMAL_SPEED
#endif

/**
 * device control flag to request or release power
 */
#define RT_PM_DEVICE_CTRL_RELEASE   (RT_DEVICE_CTRL_BASE(PM) + 0x00)
#define RT_PM_DEVICE_CTRL_REQUEST   (RT_DEVICE_CTRL_BASE(PM) + 0x01)

struct rt_pm;

/**
 * low power mode operations
 */
struct rt_pm_ops
{
    void (*sleep)(struct rt_pm *pm, rt_uint8_t mode);
    void (*run)(struct rt_pm *pm, rt_uint8_t mode);
    void (*timer_start)(struct rt_pm *pm, rt_uint32_t timeout);
    void (*timer_stop)(struct rt_pm *pm);
    rt_tick_t (*timer_get_tick)(struct rt_pm *pm);
};

struct rt_device_pm_ops
{
    int (*suspend)(const struct rt_device *device, rt_uint8_t mode);
    void (*resume)(const struct rt_device *device, rt_uint8_t mode);
    int (*frequency_change)(const struct rt_device *device, rt_uint8_t mode);
};

struct rt_device_pm
{
    const struct rt_device *device;
    const struct rt_device_pm_ops *ops;
};

struct rt_pm_module
{
    rt_uint8_t req_status;
    rt_bool_t busy_flag;
    rt_uint32_t timeout;
    rt_uint32_t start_time;
};

/**
 * power management
 */
struct rt_pm
{
    struct rt_device parent;

    /* modes */
    rt_uint8_t modes[PM_SLEEP_MODE_MAX];
    rt_uint8_t sleep_mode;    /* current sleep mode */
    rt_uint8_t run_mode;      /* current running mode */

    /* modules request status*/
    struct rt_pm_module module_status[PM_MODULE_MAX_ID];

    /* sleep request table */
    rt_uint32_t sleep_status[PM_SLEEP_MODE_MAX - 1][(PM_MODULE_MAX_ID + 31) / 32];

    /* the list of device, which has PM feature */
    rt_uint8_t device_pm_number;
    struct rt_device_pm *device_pm;

    /* if the mode has timer, the corresponding bit is 1*/
    rt_uint8_t timer_mask;
    rt_uint8_t flags;

    const struct rt_pm_ops *ops;
};

enum
{
    RT_PM_ENTER_SLEEP = 0,
    RT_PM_EXIT_SLEEP,
};

struct rt_pm_notify
{
    void (*notify)(rt_uint8_t event, rt_uint8_t mode, void *data);
    void *data;
};

void rt_pm_request(rt_uint8_t sleep_mode);
void rt_pm_release(rt_uint8_t sleep_mode);
void rt_pm_release_all(rt_uint8_t sleep_mode);
int rt_pm_run_enter(rt_uint8_t run_mode);

void rt_pm_device_register(struct rt_device *device, const struct rt_device_pm_ops *ops);
void rt_pm_device_unregister(struct rt_device *device);

void rt_pm_notify_set(void (*notify)(rt_uint8_t event, rt_uint8_t mode, void *data), void *data);
void rt_pm_default_set(rt_uint8_t sleep_mode);

void rt_system_pm_init(const struct rt_pm_ops *ops,
                       rt_uint8_t              timer_mask,
                       void                 *user_data);
void rt_pm_module_request(uint8_t module_id, rt_uint8_t sleep_mode);
void rt_pm_module_release(uint8_t module_id, rt_uint8_t sleep_mode);
void rt_pm_module_release_all(uint8_t module_id, rt_uint8_t sleep_mode);
void rt_pm_module_delay_sleep(rt_uint8_t module_id, rt_tick_t timeout);
rt_uint32_t rt_pm_module_get_status(void);
rt_uint8_t rt_pm_get_sleep_mode(void);
struct rt_pm *rt_pm_get_handle(void);

/* sleep : request or release */
void rt_pm_sleep_request(rt_uint16_t module_id, rt_uint8_t mode);
void rt_pm_sleep_release(rt_uint16_t module_id, rt_uint8_t mode);
void rt_pm_sleep_none_request(rt_uint16_t module_id);
void rt_pm_sleep_none_release(rt_uint16_t module_id);
void rt_pm_sleep_idle_request(rt_uint16_t module_id);
void rt_pm_sleep_idle_release(rt_uint16_t module_id);
void rt_pm_sleep_light_request(rt_uint16_t module_id);
void rt_pm_sleep_light_release(rt_uint16_t module_id);

#endif /* __PM_H__ */
