/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-06-02     Bernard      the first version
 * 2018-08-02     Tanek        split run and sleep modes, support custom mode
 */

#ifndef __PM_H__
#define __PM_H__

#include <rtthread.h>

#ifndef PM_HAS_CUSTOM_CONFIG

/* All modes used for rt_pm_request() adn rt_pm_release() */
enum
{
    /* run modes */
    PM_RUN_MODE_NORMAL = 0,

    /* sleep modes */
    PM_SLEEP_MODE_SLEEP,
    PM_SLEEP_MODE_TIMER,
    PM_SLEEP_MODE_SHUTDOWN,
};

/* The name of all modes used in the msh command "pm_dump" */
#define PM_MODE_NAMES           \
{                               \
    "Running Mode",             \
                                \
    "Sleep Mode",               \
    "Timer Mode",               \
    "Shutdown Mode",            \
}

/* run mode count : 1 */
#define PM_RUN_MODE_COUNT       1
/* sleep mode count : 3 */
#define PM_SLEEP_MODE_COUNT     3

/* support redefining default run mode */
#ifndef PM_RUN_MODE_DEFAULT
#define PM_RUN_MODE_DEFAULT     0
#endif

/* support redefining default sleep mode */
#ifndef PM_SLEEP_MODE_DEFAULT
#define PM_SLEEP_MODE_DEFAULT   (PM_SLEEP_MODE_START)
#endif

/* support redefining the minimum tick into sleep mode */
#ifndef PM_MIN_ENTER_SLEEP_TICK
#define PM_MIN_ENTER_SLEEP_TICK   (1)
#endif

#else /* PM_HAS_CUSTOM_CONFIG */

#include <pm_cfg.h>

#ifndef PM_RUN_MODE_COUNT
#error  "You must defined PM_RUN_MODE_COUNT on pm_cfg.h"
#endif

#ifndef PM_SLEEP_MODE_COUNT
#error  "You must defined PM_SLEEP_MODE_COUNT on pm_cfg.h"
#endif

#ifndef PM_MODE_DEFAULT
#error  "You must defined PM_MODE_DEFAULT on pm_cfg.h"
#endif

#ifndef PM_MODE_NAMES
#error  "You must defined PM_MODE_NAMES on pm_cfg.h"
#endif

#ifndef PM_RUN_MODE_DEFAULT
#error  "You must defined PM_RUN_MODE_DEFAULT on pm_cfg.h"
#endif

/* The default sleep mode(PM_SLEEP_MODE_DEFAULT) are not required.
 * If the default mode is defined, it is requested once in rt_system_pm_init()
 */

#endif /* PM_HAS_CUSTOM_CONFIG */

/* run mode must start at 0 */
#define PM_RUN_MODE_START       0
/* the values of the run modes and sleep mode must be consecutive */
#define PM_SLEEP_MODE_START     PM_RUN_MODE_COUNT
/* all mode count */
#define PM_MODE_COUNT           (PM_RUN_MODE_COUNT + PM_SLEEP_MODE_COUNT)
/* The last mode, will be request in rt_system_pm_init() */
#define PM_MODE_MAX             (PM_RUN_MODE_COUNT + PM_SLEEP_MODE_COUNT - 1)

#if PM_MODE_COUNT > 32
#error "The number of modes cannot exceed 32"
#endif

/**
 * device control flag to request or release power
 */
#define RT_PM_DEVICE_CTRL_REQUEST   0x01
#define RT_PM_DEVICE_CTRL_RELEASE   0x02

struct rt_pm;

/**
 * low power mode operations
 */
struct rt_pm_ops
{
    void (*enter)(struct rt_pm *pm);
    void (*exit)(struct rt_pm *pm);

#if PM_RUN_MODE_COUNT > 1
    void (*frequency_change)(struct rt_pm *pm, rt_uint32_t frequency);
#endif

    void (*timer_start)(struct rt_pm *pm, rt_uint32_t timeout);
    void (*timer_stop)(struct rt_pm *pm);
    rt_tick_t (*timer_get_tick)(struct rt_pm *pm);
};

struct rt_device_pm_ops
{
#if PM_RUN_MODE_COUNT > 1
    void (*frequency_change)(const struct rt_device* device);
#endif

    void (*suspend)(const struct rt_device* device);
    void (*resume) (const struct rt_device* device);
};

struct rt_device_pm
{
    const struct rt_device* device;
    const struct rt_device_pm_ops* ops;
};

/**
 * power management
 */
struct rt_pm
{
    struct rt_device parent;

    /* modes */
    rt_uint8_t modes[PM_MODE_COUNT];
    rt_uint8_t current_mode;    /* current pm mode */
    rt_uint8_t exit_count;

    /* the list of device, which has PM feature */
    rt_uint8_t device_pm_number;
    struct rt_device_pm* device_pm;
    struct rt_semaphore  device_lock;

    /* if the mode has timer, the corresponding bit is 1*/
    rt_uint32_t timer_mask;

    const struct rt_pm_ops *ops;
};

void rt_pm_enter(void);
void rt_pm_exit(void);

void rt_pm_request(rt_ubase_t mode);
void rt_pm_release(rt_ubase_t mode);

void rt_pm_register_device(struct rt_device* device, const struct rt_device_pm_ops* ops);
void rt_pm_unregister_device(struct rt_device* device);

void rt_system_pm_init(const struct rt_pm_ops *ops,
                       rt_uint8_t              timer_mask,
                       void                   *user_data);

#endif /* __PM_H__ */
