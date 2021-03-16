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

#include <rthw.h>
#include <rtthread.h>
#include <drivers/pm.h>

#ifdef RT_USING_PM

static struct rt_pm _pm;

/* default mode : system power on */
static rt_uint8_t _pm_default_sleep = RT_PM_DEFAULT_SLEEP_MODE;

/* default deepsleep mode : tick-less mode */
static rt_uint8_t _pm_default_deepsleep = RT_PM_DEFAULT_DEEPSLEEP_MODE;

static struct rt_pm_notify _pm_notify;
static rt_uint8_t _pm_init_flag = 0;

#define RT_PM_TICKLESS_THRESH (2)

RT_WEAK rt_uint32_t rt_pm_enter_critical(rt_uint8_t sleep_mode)
{
    return rt_hw_interrupt_disable();
}

RT_WEAK void rt_pm_exit_critical(rt_uint32_t ctx, rt_uint8_t sleep_mode)
{
    rt_hw_interrupt_enable(ctx);
}

/**
 * This function will suspend all registered devices
 */
static int _pm_device_suspend(rt_uint8_t mode)
{
    int index, ret = RT_EOK;

    for (index = 0; index < _pm.device_pm_number; index++)
    {
        if (_pm.device_pm[index].ops->suspend != RT_NULL)
        {
            ret = _pm.device_pm[index].ops->suspend(_pm.device_pm[index].device, mode);
            if(ret != RT_EOK)
                break;
        }
    }

    return ret;
}

/**
 * This function will resume all registered devices
 */
static void _pm_device_resume(rt_uint8_t mode)
{
    int index;

    for (index = 0; index < _pm.device_pm_number; index++)
    {
        if (_pm.device_pm[index].ops->resume != RT_NULL)
        {
            _pm.device_pm[index].ops->resume(_pm.device_pm[index].device, mode);
        }
    }
}

/**
 * This function will update the frequency of all registered devices
 */
static void _pm_device_frequency_change(rt_uint8_t mode)
{
    rt_uint32_t index;

    /* make the frequency change */
    for (index = 0; index < _pm.device_pm_number; index ++)
    {
        if (_pm.device_pm[index].ops->frequency_change != RT_NULL)
            _pm.device_pm[index].ops->frequency_change(_pm.device_pm[index].device, mode);
    }
}

/**
 * This function will update the system clock frequency when idle
 */
static void _pm_frequency_scaling(struct rt_pm *pm)
{
    rt_base_t level;

    if (pm->flags & RT_PM_FREQUENCY_PENDING)
    {
        level = rt_hw_interrupt_disable();
        /* change system runing mode */
        pm->ops->run(pm, pm->run_mode);
        /* changer device frequency */
        _pm_device_frequency_change(pm->run_mode);
        pm->flags &= ~RT_PM_FREQUENCY_PENDING;
        rt_hw_interrupt_enable(level);
    }
}

/**
 * This function selects the sleep mode according to the rt_pm_request/rt_pm_release count.
 */
static rt_uint8_t _pm_select_sleep_mode(struct rt_pm *pm)
{
    int index;
    rt_uint8_t mode;

    mode = _pm_default_deepsleep;
    for (index = PM_SLEEP_MODE_NONE; index < PM_SLEEP_MODE_MAX; index ++)
    {
        if (pm->modes[index])
        {
            mode = index;
            break;
        }
    }
    pm->sleep_mode = mode;

    return mode;
}

/**
 * pm module request delay sleep.
 */
void rt_pm_module_delay_sleep(rt_uint8_t module_id, rt_tick_t timeout)
{
    rt_base_t level;
    struct rt_pm *pm;

    if (_pm_init_flag == 0)
        return;

    if (module_id > (PM_MODULE_MAX_ID - 1))
        return;

    level = rt_hw_interrupt_disable();
    pm = &_pm;
    pm->module_status[module_id].busy_flag = RT_TRUE;
    pm->module_status[module_id].timeout = timeout;
    pm->module_status[module_id].start_time = rt_tick_get();
    rt_hw_interrupt_enable(level);
}

/**
 * This function check if all modules in idle status.
 */
static rt_bool_t _pm_device_check_idle(void)
{
    struct rt_pm *pm;

    if (_pm_init_flag == 0)
        return RT_TRUE;

    pm = &_pm;
    for (int i = 0; i < PM_MODULE_MAX_ID; i++)
    {
        if (pm->module_status[i].busy_flag == RT_TRUE)
        {
            if (rt_tick_get() - pm->module_status[i].start_time > pm->module_status[i].timeout)
            {
                pm->module_status[i].busy_flag = RT_FALSE;
                pm->module_status[i].timeout = 0x00;
            }
        }
        if (pm->module_status[i].busy_flag == RT_TRUE)
        {
            return RT_FALSE;
        }
    }

    return RT_TRUE;
}

/**
 * This function changes the power sleep mode base on the result of selection
 */
static void _pm_change_sleep_mode(struct rt_pm *pm)
{
    rt_tick_t timeout_tick, delta_tick;
    rt_base_t level;
    int ret = RT_EOK;

    level = rt_pm_enter_critical(pm->sleep_mode);

    /* module busy request */
    if (_pm_device_check_idle() == RT_FALSE)
    {
        pm->ops->sleep(pm, PM_SLEEP_MODE_NONE);
        rt_pm_exit_critical(level, pm->sleep_mode);
        return;
    }

    if (_pm.sleep_mode == PM_SLEEP_MODE_NONE)
    {
        pm->ops->sleep(pm, PM_SLEEP_MODE_NONE);
        rt_pm_exit_critical(level, pm->sleep_mode);
    }
    else
    {
        /* Notify app will enter sleep mode */
        if (_pm_notify.notify)
            _pm_notify.notify(RT_PM_ENTER_SLEEP, pm->sleep_mode, _pm_notify.data);

        /* Suspend all peripheral device */
        ret = _pm_device_suspend(pm->sleep_mode);
        if (ret != RT_EOK)
        {
            _pm_device_resume(pm->sleep_mode);
            if (_pm_notify.notify)
                _pm_notify.notify(RT_PM_EXIT_SLEEP, pm->sleep_mode, _pm_notify.data);
            rt_pm_exit_critical(level, pm->sleep_mode);

            return;
        }

        /* Tickless*/
        if (pm->timer_mask & (0x01 << pm->sleep_mode))
        {
            timeout_tick = rt_timer_next_timeout_tick();
            if (timeout_tick == RT_TICK_MAX)
            {
                if (pm->ops->timer_start)
                {
                    pm->ops->timer_start(pm, RT_TICK_MAX);
                }
            }
            else
            {
                timeout_tick = timeout_tick - rt_tick_get();
                if (timeout_tick < RT_PM_TICKLESS_THRESH)
                {
                    pm->sleep_mode = PM_SLEEP_MODE_IDLE;
                }
                else
                {
                    pm->ops->timer_start(pm, timeout_tick);
                }
            }
        }

        /* enter lower power state */
        pm->ops->sleep(pm, pm->sleep_mode);

        /* wake up from lower power state*/
        if (pm->timer_mask & (0x01 << pm->sleep_mode))
        {
            delta_tick = pm->ops->timer_get_tick(pm);
            pm->ops->timer_stop(pm);
            if (delta_tick)
            {
                rt_tick_set(rt_tick_get() + delta_tick);
            }
        }

        /* resume all device */
        _pm_device_resume(pm->sleep_mode);

        if (_pm_notify.notify)
            _pm_notify.notify(RT_PM_EXIT_SLEEP, pm->sleep_mode, _pm_notify.data);

        rt_pm_exit_critical(level, pm->sleep_mode);

        if (pm->timer_mask & (0x01 << pm->sleep_mode))
        {
            if (delta_tick)
            {
                rt_timer_check();
            }
        }
    }
}

/**
 * This function will enter corresponding power mode.
 */
void rt_system_power_manager(void)
{
    if (_pm_init_flag == 0)
        return;

    /* CPU frequency scaling according to the runing mode settings */
    _pm_frequency_scaling(&_pm);

    /* Low Power Mode Processing */
    _pm_change_sleep_mode(&_pm);
}

/**
 * Upper application or device driver requests the system
 * stall in corresponding power mode.
 *
 * @param parameter the parameter of run mode or sleep mode
 */
void rt_pm_request(rt_uint8_t mode)
{
    rt_base_t level;
    struct rt_pm *pm;

    if (_pm_init_flag == 0)
        return;

    if (mode > (PM_SLEEP_MODE_MAX - 1))
        return;

    level = rt_hw_interrupt_disable();
    pm = &_pm;
    if (pm->modes[mode] < 255)
        pm->modes[mode] ++;
    _pm_select_sleep_mode(pm);
    rt_hw_interrupt_enable(level);
}

/**
 * Upper application or device driver releases the stall
 * of corresponding power mode.
 *
 * @param parameter the parameter of run mode or sleep mode
 *
 */
void rt_pm_release(rt_uint8_t mode)
{
    rt_ubase_t level;
    struct rt_pm *pm;

    if (_pm_init_flag == 0)
        return;

    if (mode > (PM_SLEEP_MODE_MAX - 1))
        return;

    level = rt_hw_interrupt_disable();
    pm = &_pm;
    if (pm->modes[mode] > 0)
        pm->modes[mode] --;
    _pm_select_sleep_mode(pm);
    rt_hw_interrupt_enable(level);
}

/**
 * Upper application or device driver releases all the stall
 * of corresponding power mode.
 *
 * @param parameter the parameter of run mode or sleep mode
 *
 */
void rt_pm_release_all(rt_uint8_t mode)
{
    rt_ubase_t level;
    struct rt_pm *pm;

    if (_pm_init_flag == 0)
        return;

    if (mode > (PM_SLEEP_MODE_MAX - 1))
        return;

    level = rt_hw_interrupt_disable();
    pm = &_pm;
    pm->modes[mode] = 0;
    _pm_select_sleep_mode(pm);
    rt_hw_interrupt_enable(level);
}

/**
 * Upper application or device driver requests the system
 * stall in corresponding power mode.
 *
 * @param module_id the application or device module id
 * @param mode the system power sleep mode
 */
void rt_pm_module_request(uint8_t module_id, rt_uint8_t mode)
{
    rt_base_t level;
    struct rt_pm *pm;

    if (_pm_init_flag == 0)
        return;

    if (mode > (PM_SLEEP_MODE_MAX - 1))
        return;

    if (module_id > (PM_MODULE_MAX_ID - 1))
        return;

    level = rt_hw_interrupt_disable();
    pm = &_pm;
    pm->module_status[module_id].req_status = 0x01;
    if (pm->modes[mode] < 255)
        pm->modes[mode] ++;
    _pm_select_sleep_mode(pm);
    rt_hw_interrupt_enable(level);
}

/**
 * Upper application or device driver releases the stall
 * of corresponding power mode.
 *
 * @param module_id the application or device module id
 * @param mode the system power sleep mode
 *
 */
void rt_pm_module_release(uint8_t module_id, rt_uint8_t mode)
{
    rt_ubase_t level;
    struct rt_pm *pm;

    if (_pm_init_flag == 0)
        return;

    if (mode > (PM_SLEEP_MODE_MAX - 1))
        return;

    if (module_id > (PM_MODULE_MAX_ID - 1))
        return;

    level = rt_hw_interrupt_disable();
    pm = &_pm;
    if (pm->modes[mode] > 0)
        pm->modes[mode] --;
    if (pm->modes[mode] == 0)
        pm->module_status[module_id].req_status = 0x00;
    _pm_select_sleep_mode(pm);
    rt_hw_interrupt_enable(level);
}

/**
 * Upper application or device driver releases all the stall
 * of corresponding power mode.
 *
 * @param module_id the application or device module id
 * @param mode the system power sleep mode
 *
 */
void rt_pm_module_release_all(uint8_t module_id, rt_uint8_t mode)
{
    rt_ubase_t level;
    struct rt_pm *pm;

    if (_pm_init_flag == 0)
        return;

    if (mode > (PM_SLEEP_MODE_MAX - 1))
        return;

    level = rt_hw_interrupt_disable();
    pm = &_pm;
    pm->modes[mode] = 0;
    pm->module_status[module_id].req_status = 0x00;
    _pm_select_sleep_mode(pm);
    rt_hw_interrupt_enable(level);
}

/**
 * Register a device with PM feature
 *
 * @param device the device with PM feature
 * @param ops the PM ops for device
 */
void rt_pm_device_register(struct rt_device *device, const struct rt_device_pm_ops *ops)
{
    rt_base_t level;
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

    rt_hw_interrupt_enable(level);
}

/**
 * Unregister device from PM manager.
 *
 * @param device the device with PM feature
 */
void rt_pm_device_unregister(struct rt_device *device)
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
 * This function set notification callback for application
 */
void rt_pm_notify_set(void (*notify)(rt_uint8_t event, rt_uint8_t mode, void *data), void *data)
{
    _pm_notify.notify = notify;
    _pm_notify.data = data;
}

/**
 * This function set default sleep mode when no pm_request
 */
void rt_pm_default_set(rt_uint8_t sleep_mode)
{
    _pm_default_sleep = sleep_mode;
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

    if (pos < PM_SLEEP_MODE_MAX)
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
        if (request ==  0x01)
        {
            rt_pm_request(pos);
        }
        else if (request == 0x00)
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

int rt_pm_run_enter(rt_uint8_t mode)
{
    rt_base_t level;
    struct rt_pm *pm;

    if (_pm_init_flag == 0)
        return -RT_EIO;

    if (mode > PM_RUN_MODE_MAX)
        return -RT_EINVAL;

    level = rt_hw_interrupt_disable();
    pm = &_pm;
    if (mode < pm->run_mode)
    {
        /* change system runing mode */
        pm->ops->run(pm, mode);
        /* changer device frequency */
        _pm_device_frequency_change(mode);
    }
    else
    {
        pm->flags |= RT_PM_FREQUENCY_PENDING;
    }
    pm->run_mode = mode;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pm_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _rt_pm_device_read,
    _rt_pm_device_write,
    _rt_pm_device_control,
};
#endif

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

#ifdef RT_USING_DEVICE_OPS
    device->ops = &pm_ops;
#else
    device->init        = RT_NULL;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = _rt_pm_device_read;
    device->write       = _rt_pm_device_write;
    device->control     = _rt_pm_device_control;
#endif
    device->user_data   = user_data;

    /* register PM device to the system */
    rt_device_register(device, "pm", RT_DEVICE_FLAG_RDWR);

    rt_memset(pm->modes, 0, sizeof(pm->modes));
    pm->sleep_mode = _pm_default_sleep;

    /* when system power on, set default sleep modes */
    pm->modes[pm->sleep_mode] = 1;
    pm->module_status[PM_POWER_ID].req_status = 1;
    pm->run_mode   = RT_PM_DEFAULT_RUN_MODE;
    pm->timer_mask = timer_mask;

    pm->ops = ops;

    pm->device_pm = RT_NULL;
    pm->device_pm_number = 0;

#if IDLE_THREAD_STACK_SIZE <= 256
    #error "[pm.c ERR] IDLE Stack Size Too Small!"
#endif

    _pm_init_flag = 1;
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static const char *_pm_sleep_str[] = PM_SLEEP_MODE_NAMES;
static const char *_pm_run_str[] = PM_RUN_MODE_NAMES;

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

static void rt_pm_release_mode_all(int argc, char **argv)
{
    int mode = 0;
    if (argc >= 2)
    {
        mode = atoi(argv[1]);
    }

    rt_pm_release_all(mode);
}
MSH_CMD_EXPORT_ALIAS(rt_pm_release_mode_all, pm_release_all, release power management mode count);

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

static void rt_module_release_mode(int argc, char **argv)
{
    int module = 0;
    int mode = 0;

    if (argc >= 3)
    {
        module = atoi(argv[1]);
        mode = atoi(argv[2]);
    }

    rt_pm_module_release(module, mode);
}
MSH_CMD_EXPORT_ALIAS(rt_module_release_mode, pm_module_release, release module power mode);

static void rt_module_release_mode_all(int argc, char **argv)
{
    int module = 0;
    int mode = 0;

    if (argc >= 3)
    {
        module = atoi(argv[1]);
        mode = atoi(argv[2]);
    }

    rt_pm_module_release_all(module, mode);
}
MSH_CMD_EXPORT_ALIAS(rt_module_release_mode_all, pm_module_release_all, release power management mode count);

static void rt_module_request_mode(int argc, char **argv)
{
    int module = 0;
    int mode = 0;

    if (argc >= 3)
    {
        module = atoi(argv[1]);
        mode = atoi(argv[2]);
    }

    rt_pm_module_request(module, mode);
}
MSH_CMD_EXPORT_ALIAS(rt_module_request_mode, pm_module_request, request power management mode);

static void rt_module_delay_sleep(int argc, char **argv)
{
    int module = 0;
    unsigned int timeout = 0;

    if (argc >= 3)
    {
        module = atoi(argv[1]);
        timeout = atoi(argv[2]);
    }

    rt_pm_module_delay_sleep(module, timeout);
}
MSH_CMD_EXPORT_ALIAS(rt_module_delay_sleep, pm_module_delay, module request delay sleep);

static void rt_pm_run_mode_switch(int argc, char **argv)
{
    int mode = 0;
    if (argc >= 2)
    {
        mode = atoi(argv[1]);
    }

    rt_pm_run_enter(mode);
}
MSH_CMD_EXPORT_ALIAS(rt_pm_run_mode_switch, pm_run, switch power management run mode);

rt_uint32_t rt_pm_module_get_status(void)
{
    rt_uint8_t index = 0;
    struct rt_pm *pm;
    rt_uint32_t req_status = 0x00;
    pm = &_pm;

    for (index = 0; index < 32; index ++)
    {
        if (pm->module_status[index].req_status == 0x01)
            req_status |= 1<<index;
        if (index >= PM_MODULE_MAX_ID)
            break;
    }

    return req_status;
}

rt_uint8_t rt_pm_get_sleep_mode(void)
{
    struct rt_pm *pm;

    pm = &_pm;
    return pm->sleep_mode;
}

static void rt_pm_dump_status(void)
{
    rt_uint32_t index;
    struct rt_pm *pm;

    pm = &_pm;

    rt_kprintf("| Power Management Mode | Counter | Timer |\n");
    rt_kprintf("+-----------------------+---------+-------+\n");
    for (index = 0; index < PM_SLEEP_MODE_MAX; index ++)
    {
        int has_timer = 0;
        if (pm->timer_mask & (1 << index))
            has_timer = 1;

        rt_kprintf("| %021s | %7d | %5d |\n", _pm_sleep_str[index], pm->modes[index], has_timer);
    }
    rt_kprintf("+-----------------------+---------+-------+\n");

    rt_kprintf("pm current sleep mode: %s\n", _pm_sleep_str[pm->sleep_mode]);
    rt_kprintf("pm current run mode:   %s\n", _pm_run_str[pm->run_mode]);

    rt_kprintf("\n");
    rt_kprintf("| module | busy | start time |  timeout  |\n");
    rt_kprintf("+--------+------+------------+-----------+\n");
    for (index = 0; index < PM_MODULE_MAX_ID; index ++)
    {
        if ((pm->module_status[index].busy_flag == RT_TRUE) ||
            (pm->module_status[index].req_status != 0x00))
        {
            rt_kprintf("|  %04d  |  %d   | 0x%08x | 0x%08x |\n",
                index, pm->module_status[index].busy_flag,
                pm->module_status[index].start_time,
                pm->module_status[index].timeout);
        }
    }
    rt_kprintf("+--------+------+------------+-----------+\n");
}
FINSH_FUNCTION_EXPORT_ALIAS(rt_pm_dump_status, pm_dump, dump power management status);
MSH_CMD_EXPORT_ALIAS(rt_pm_dump_status, pm_dump, dump power management status);
#endif

#endif /* RT_USING_PM */
