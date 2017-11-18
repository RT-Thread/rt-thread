/*
 * File      : pm.h
 * COPYRIGHT (C) 2012, Shanghai Real-Thread Technology Co., Ltd
 *
 * All rights reserved.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-06-02     Bernard      the first version
 */

#ifndef __PM_H__
#define __PM_H__

#include <rtthread.h>

#ifdef RT_USING_PM
enum
{
    PM_HIGHSPEED_MODE = 0,  /* mode 0 */
    PM_RUNNING_MODE,        /* mode 1 */
    PM_SLEEP_MODE,          /* mode 2 */
    PM_DEEPSLEEP_MODE,      /* mode 3 */
    PM_TIMER_MODE,          /* mode 4 */
    PM_DEEPTIMER_MODE,      /* mode 5 */
    PM_SHUTDOWN_MODE,       /* mode 6 */
    PM_DEEPSHUTDOWN_MODE,   /* mode 7 */
    PM_MODE_MAX = PM_DEEPSHUTDOWN_MODE,
};

#define RT_PM_DEVICE(device) (struct rt_pm *)(device)

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

	void (*frequency_change)(struct rt_pm *pm, rt_uint32_t frequency);

    void (*timer_start)(struct rt_pm *pm, rt_uint32_t timeout);
    void (*timer_stop)(struct rt_pm *pm);
    rt_tick_t (*timer_get_tick)(struct rt_pm *pm);
};

struct rt_device_pm_ops
{
	void (*frequency_change)(const struct rt_device* device);
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
    rt_uint8_t mode[PM_MODE_MAX + 1];
    rt_uint8_t  pm_mode;    /* current pm mode */
    rt_uint8_t  timer_mask;

	/* the list of device, which has PM feature */
	rt_uint8_t device_pm_number;
	struct rt_device_pm* device_pm;
	struct rt_semaphore  lock;

    rt_uint32_t pm_tick;

    const struct rt_pm_ops *ops;
};

void rt_pm_enter(void);
void rt_pm_exit(void);

void rt_pm_request(rt_ubase_t mode);
void rt_pm_release(rt_ubase_t mode);
void rt_pm_frequency_change(rt_uint32_t frequency);

void rt_pm_register_device(struct rt_device* device, const struct rt_device_pm_ops* ops);
void rt_pm_unregister_device(struct rt_device* device);

void rt_system_pm_init(const struct rt_pm_ops *ops,
                       rt_uint8_t              timer_mask,
                       void                   *user_data);

#endif

#endif
