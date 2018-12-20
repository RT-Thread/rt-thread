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

#include <rthw.h>
#include <rtthread.h>
#include <drivers/pm.h>

#ifdef RT_USING_PM

static struct rt_pm _pm;

/**
 * This function will suspend all registered devices
 */
static void _pm_device_suspend(void)
{
    int index;

    for (index = 0; index < _pm.device_pm_number; index++)
    {
        if (_pm.device_pm[index].ops->suspend != RT_NULL)
        {
            _pm.device_pm[index].ops->suspend(_pm.device_pm[index].device);
        }
    }
}

/**
 * This function will resume all registered devices
 */
static void _pm_device_resume(void)
{
    int index;

    for (index = 0; index < _pm.device_pm_number; index++)
    {
        if (_pm.device_pm[index].ops->resume != RT_NULL)
        {
            _pm.device_pm[index].ops->resume(_pm.device_pm[index].device);
        }
    }
}

#if PM_RUN_MODE_COUNT > 1
/**
 * This function will update the frequency of all registered devices
 */
static void _pm_device_frequency_change(void)
{
    rt_uint32_t index;

    /* make the frequency change */
    for (index = 0; index < _pm.device_pm_number; index ++)
    {
        if (_pm.device_pm[index].ops->frequency_change != RT_NULL)
            _pm.device_pm[index].ops->frequency_change(_pm.device_pm[index].device);
    }
}
#endif

/**
 * This function will enter corresponding power mode.
 */
void rt_pm_enter(void)
{
    rt_ubase_t level;
    struct rt_pm *pm;
    rt_uint32_t index;
    rt_tick_t timeout_tick;

    pm = &_pm;

    /* disable interrupt before check run modes */
    level = rt_hw_interrupt_disable();
    /* check each run mode, and decide to swithc to run mode or sleep mode */
    for (index = 0; index < PM_RUN_MODE_COUNT; index++)
    {
        if (pm->modes[index])
        {
            if (index > pm->current_mode)
            {
                pm->ops->exit(pm);
                pm->current_mode = index;
                pm->ops->enter(pm);
#if PM_RUN_MODE_COUNT > 1
                pm->ops->frequency_change(pm, 0);
                _pm_device_frequency_change();
#endif
            }

            rt_hw_interrupt_enable(level);
            /* The current mode is run mode, no need to check sleep mode */
            return ;
        }
    }
    /* enable interrupt after check run modes */
    rt_hw_interrupt_enable(level);

    level = rt_hw_interrupt_disable();
    /* check each sleep mode to decide which mode can system sleep. */
    for (index = PM_SLEEP_MODE_START; index < PM_SLEEP_MODE_START + PM_SLEEP_MODE_COUNT; index++)
    {
        if (pm->modes[index])
        {
            /* let mcu sleep when system is idle */

            /* run mode to sleep mode */
            if (pm->current_mode < PM_SLEEP_MODE_START)
            {
                /* exit run mode */
                pm->ops->exit(pm);
            }

            /* set current power mode */
            pm->current_mode = index;
            pm->exit_count = 1;

            /* suspend all of devices with PM feature */
            _pm_device_suspend();

            /* should start pm timer */
            if (pm->timer_mask & (1 << index))
            {
                /* get next os tick */
                timeout_tick = rt_timer_next_timeout_tick();
                if (timeout_tick != RT_TICK_MAX)
                {
                    timeout_tick -= rt_tick_get();

#if defined(PM_MIN_ENTER_SLEEP_TICK) && PM_MIN_ENTER_SLEEP_TICK > 0
                    if (timeout_tick < PM_MIN_ENTER_SLEEP_TICK)
                    {
                        rt_hw_interrupt_enable(level);
                        /* limit the minimum time to enter timer sleep mode */
                        return ;
                    }
#endif
                }
                /* startup pm timer */
                pm->ops->timer_start(pm, timeout_tick);
            }

            /* enter sleep and wait to be waken up */
            pm->ops->enter(pm);

            /* exit from low power mode */
            rt_pm_exit();

            rt_hw_interrupt_enable(level);
            return ;
        }
    }

    rt_hw_interrupt_enable(level);
}

/**
 * This function exits from sleep mode.
 */
void rt_pm_exit(void)
{
    rt_ubase_t level;
    struct rt_pm *pm;
    rt_tick_t delta_tick;

    pm = &_pm;

    level = rt_hw_interrupt_disable();

    if (pm->exit_count)
    {
        pm->exit_count = 0;

        if (pm->current_mode >= PM_SLEEP_MODE_START)
        {
            /* sleep mode with timer */
            if (pm->timer_mask & (1 << pm->current_mode))
            {
                /* get the tick of pm timer */
                delta_tick = pm->ops->timer_get_tick(pm);

                /* stop pm timer */
                pm->ops->timer_stop(pm);

                if (delta_tick)
                {
                    /* adjust OS tick */
                    rt_tick_set(rt_tick_get() + delta_tick);
                    /* check system timer */
                    rt_timer_check();
                }
            }

            /* exit from sleep mode */
            pm->ops->exit(pm);
            /* resume the device with PM feature */
            _pm_device_resume();
        }
    }

    rt_hw_interrupt_enable(level);
}

/**
 * Upper application or device driver requests the system
 * stall in corresponding power mode.
 *
 * @param parameter the parameter of run mode or sleep mode
 */
void rt_pm_request(rt_ubase_t mode)
{
    rt_ubase_t level;
    struct rt_pm *pm;

    pm = &_pm;

    if (mode > PM_MODE_MAX)
        return;

    level = rt_hw_interrupt_disable();

    /* update pm modes table */
    pm->modes[mode] ++;

    /* request higter mode with a smaller mode value*/
    if (mode < pm->current_mode)
    {
        /* the old current mode is RUN mode, need to all pm->ops->exit(),
         * if not, it has already called in rt_pm_exit()
         */
        if (pm->current_mode < PM_SLEEP_MODE_START)
        {
            pm->ops->exit(pm);
        }
        else if (pm->exit_count)
        {
            /* call exeit when global interrupt is disable */
            pm->ops->exit(pm);
            pm->exit_count = 0;
        }

        /* update current mode */
        pm->current_mode = mode;

        /* current mode is higher run mode */
        if (mode < PM_SLEEP_MODE_START)
        {
            /* enter run mode */
            pm->ops->enter(pm);
#if PM_RUN_MODE_COUNT > 1
            /* frequency change */
            pm->ops->frequency_change(pm, 0);
            _pm_device_frequency_change();
#endif
        }
        else
        {
            /* do nothing when request higher sleep mode,
             * and swithc to new sleep mode in rt_pm_enter()
             */
        }
    }

    rt_hw_interrupt_enable(level);
}

/**
 * Upper application or device driver releases the stall
 * of corresponding power mode.
 *
 * @param parameter the parameter of run mode or sleep mode
 *
 */
void rt_pm_release(rt_ubase_t mode)
{
    rt_ubase_t level;
    struct rt_pm *pm;

    pm = &_pm;

    if (mode > PM_MODE_MAX)
        return;

    level = rt_hw_interrupt_disable();

    if (pm->modes[mode] > 0)
        pm->modes[mode] --;

    rt_hw_interrupt_enable(level);
}

/**
 * Register a device with PM feature
 *
 * @param device the device with PM feature
 * @param ops the PM ops for device
 */
void rt_pm_register_device(struct rt_device *device, const struct rt_device_pm_ops *ops)
{
    rt_ubase_t level;
    struct rt_device_pm *device_pm;

    RT_DEBUG_NOT_IN_INTERRUPT;

    level = rt_hw_interrupt_disable();

    device_pm = (struct rt_device_pm *)RT_KERNEL_REALLOC(_pm.device_pm,
                (_pm.device_pm_number + 1) * sizeof(struct rt_device_pm));
    if (device_pm != RT_NULL)
    {
        _pm.device_pm = device_pm;
        _pm.device_pm[_pm.device_pm_number].device = device;
        _pm.device_pm[_pm.device_pm_number].ops    = ops;
        _pm.device_pm_number += 1;
    }

    rt_sem_release(&(_pm.device_lock));

    rt_hw_interrupt_enable(level);
}

/**
 * Unregister device from PM manager.
 *
 * @param device the device with PM feature
 */
void rt_pm_unregister_device(struct rt_device *device)
{
    rt_ubase_t level;
    rt_uint32_t index;
    RT_DEBUG_NOT_IN_INTERRUPT;

    level = rt_hw_interrupt_disable();

    for (index = 0; index < _pm.device_pm_number; index ++)
    {
        if (_pm.device_pm[index].device == device)
        {
            /* remove current entry */
            for (; index < _pm.device_pm_number - 1; index ++)
            {
                _pm.device_pm[index] = _pm.device_pm[index + 1];
            }

            _pm.device_pm[_pm.device_pm_number - 1].device = RT_NULL;
            _pm.device_pm[_pm.device_pm_number - 1].ops = RT_NULL;

            _pm.device_pm_number -= 1;
            /* break out and not touch memory */
            break;
        }
    }

    rt_hw_interrupt_enable(level);
}

/**
 * RT-Thread device interface for PM device
 */
static rt_size_t _rt_pm_device_read(rt_device_t dev,
                                    rt_off_t    pos,
                                    void       *buffer,
                                    rt_size_t   size)
{
    struct rt_pm *pm;
    rt_size_t length;

    length = 0;
    pm = (struct rt_pm *)dev;
    RT_ASSERT(pm != RT_NULL);

    if (pos <= PM_MODE_MAX)
    {
        int mode;

        mode = pm->modes[pos];
        length = rt_snprintf(buffer, size, "%d", mode);
    }

    return length;
}

static rt_size_t _rt_pm_device_write(rt_device_t dev,
                                     rt_off_t    pos,
                                     const void *buffer,
                                     rt_size_t   size)
{
    unsigned char request;

    if (size)
    {
        /* get request */
        request = *(unsigned char *)buffer;
        if (request == '1')
        {
            rt_pm_request(pos);
        }
        else if (request == '0')
        {
            rt_pm_release(pos);
        }
    }

    return 1;
}

static rt_err_t _rt_pm_device_control(rt_device_t dev,
                                      int         cmd,
                                      void       *args)
{
    rt_uint32_t mode;

    switch (cmd)
    {
    case RT_PM_DEVICE_CTRL_REQUEST:
        mode = (rt_uint32_t)args;
        rt_pm_request(mode);
        break;

    case RT_PM_DEVICE_CTRL_RELEASE:
        mode = (rt_uint32_t)args;
        rt_pm_release(mode);
        break;
    }

    return RT_EOK;
}

/**
 * This function will initialize power management.
 *
 * @param ops the PM operations.
 * @param timer_mask indicates which mode has timer feature.
 * @param user_data user data
 */
void rt_system_pm_init(const struct rt_pm_ops *ops,
                       rt_uint8_t              timer_mask,
                       void                   *user_data)
{
    struct rt_device *device;
    struct rt_pm *pm;

    pm = &_pm;
    device = &(_pm.parent);

    device->type        = RT_Device_Class_PM;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = RT_NULL;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = _rt_pm_device_read;
    device->write       = _rt_pm_device_write;
    device->control     = _rt_pm_device_control;
    device->user_data   = user_data;

    /* register PM device to the system */
    rt_device_register(device, "pm", RT_DEVICE_FLAG_RDWR);

    /* todo : add to kernel source code */
    rt_thread_idle_sethook(rt_pm_enter);

    rt_memset(pm->modes, 0, sizeof(pm->modes));
    pm->current_mode = PM_RUN_MODE_DEFAULT;

    pm->timer_mask = timer_mask;

    pm->ops = ops;

    pm->device_pm = RT_NULL;
    pm->device_pm_number = 0;

    /* initialize semaphore */
    rt_sem_init(&(pm->device_lock), "pm", 1, RT_IPC_FLAG_FIFO);

    /* request in default running mode */
    rt_pm_request(PM_RUN_MODE_DEFAULT);

#ifdef PM_SLEEP_MODE_DEFAULT
    /* request in default sleep mode */
    rt_pm_request(PM_SLEEP_MODE_DEFAULT);
#endif

    /* must hold on deep shutdown mode */
    rt_pm_request(PM_MODE_MAX);
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static void rt_pm_release_mode(int argc, char **argv)
{
    int mode = 0;
    if (argc >= 2)
    {
        mode = atoi(argv[1]);
    }

    rt_pm_release(mode);
}
MSH_CMD_EXPORT_ALIAS(rt_pm_release_mode, pm_release, release power management mode);

static void rt_pm_request_mode(int argc, char **argv)
{
    int mode = 0;
    if (argc >= 2)
    {
        mode = atoi(argv[1]);
    }

    rt_pm_request(mode);
}
MSH_CMD_EXPORT_ALIAS(rt_pm_request_mode, pm_request, request power management mode);

static void rt_pm_dump_status(void)
{
    static const char *pm_str[] = PM_MODE_NAMES;
    rt_uint32_t index;
    struct rt_pm *pm;

    pm = &_pm;

    rt_kprintf("| Power Management Mode | Counter | Timer |\n");
    rt_kprintf("+-----------------------+---------+-------+\n");
    for (index = 0; index <= PM_MODE_MAX; index ++)
    {
        int has_timer = 0;
        if (pm->timer_mask & (1 << index))
            has_timer = 1;

        rt_kprintf("| %021s | %7d | %5d |\n", pm_str[index], pm->modes[index], has_timer);
    }
    rt_kprintf("+-----------------------+---------+-------+\n");

    rt_kprintf("pm current mode: %s\n", pm_str[pm->current_mode]);
}
FINSH_FUNCTION_EXPORT_ALIAS(rt_pm_dump_status, pm_dump, dump power management status);
MSH_CMD_EXPORT_ALIAS(rt_pm_dump_status, pm_dump, dump power management status);
#endif

#endif /* RT_USING_PM */
