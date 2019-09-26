/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-06-02     Bernard      the first version
 * 2018-08-02     Tanek        split run and sleep modes, support custom mode
 * 2019-04-28     Zero-Free    improve PM mode and device ops interface
 */

#ifndef __PM_H__
#define __PM_H__

#include <rtthread.h>

#ifndef PM_HAS_CUSTOM_CONFIG

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

#define RT_PM_DEFAULT_SLEEP_MODE PM_SLEEP_MODE_IDLE
#define RT_PM_DEFAULT_RUN_MODE   PM_RUN_MODE_NORMAL_SPEED

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

#else /* PM_HAS_CUSTOM_CONFIG */

#include <pm_cfg.h>

#endif /* PM_HAS_CUSTOM_CONFIG */

/**
 * device control flag to request or release power
 */
#define RT_PM_DEVICE_CTRL_REQUEST   0x01
#define RT_PM_DEVICE_CTRL_RELEASE   0x00

struct rt_pm;

/**
 * low power mode operations
 */
struct rt_pm_ops
{
    void (*sleep)(struct rt_pm *pm, uint8_t mode);
    void (*run)(struct rt_pm *pm, uint8_t mode);
    void (*timer_start)(struct rt_pm *pm, rt_uint32_t timeout);
    void (*timer_stop)(struct rt_pm *pm);
    rt_tick_t (*timer_get_tick)(struct rt_pm *pm);
};

struct rt_device_pm_ops
{
    int (*suspend)(const struct rt_device *device, uint8_t mode);
    void (*resume)(const struct rt_device *device, uint8_t mode);
    int (*frequency_change)(const struct rt_device *device, uint8_t mode);
};

struct rt_device_pm
{
    const struct rt_device *device;
    const struct rt_device_pm_ops *ops;
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
    void (*notify)(uint8_t event, uint8_t mode, void *data);
    void *data;
};

void rt_pm_request(uint8_t sleep_mode);
void rt_pm_release(uint8_t sleep_mode);
int rt_pm_run_enter(uint8_t run_mode);

void rt_pm_device_register(struct rt_device *device, const struct rt_device_pm_ops *ops);
void rt_pm_device_unregister(struct rt_device *device);

void rt_pm_notify_set(void (*notify)(uint8_t event, uint8_t mode, void *data), void *data);
void rt_pm_default_set(uint8_t sleep_mode);

void rt_system_pm_init(const struct rt_pm_ops *ops,
                       uint8_t              timer_mask,
                       void                 *user_data);

#endif /* __PM_H__ */
