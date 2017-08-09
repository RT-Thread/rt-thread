/*
 * File      : pm.c
 * COPYRIGHT (C) 2012, Shanghai Real-Thread Technology Co., Ltd
 *
 * All rights reserved.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-06-02     Bernard      the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <drivers/pm.h>
#ifdef RT_USING_PM

struct rt_pm _pm;

static void _pm_device_suspend(void)
{
	rt_uint32_t index;

	for (index = 0; index < _pm.device_pm_number; index ++)
	{
		if (_pm.device_pm[index].ops->suspend != RT_NULL)
		{
			_pm.device_pm[index].ops->suspend(_pm.device_pm[index].device);
		}
	}
}

static void _pm_device_resume(void)
{
	rt_uint32_t index;

	for (index = 0; index < _pm.device_pm_number; index ++)
	{
		if (_pm.device_pm[index].ops->suspend != RT_NULL)
		{
			_pm.device_pm[index].ops->suspend(_pm.device_pm[index].device);
		}
	}
}

static void _pm_device_frequency_change(void)
{
	rt_uint32_t index;
	rt_uint32_t level;

	/* make the frequency change */
	level = rt_hw_interrupt_disable();
	for (index = 0; index < _pm.device_pm_number; index ++)
	{
		if (_pm.device_pm[index].ops->frequency_change != RT_NULL)
			_pm.device_pm[index].ops->frequency_change(_pm.device_pm[index].device);
	}
	rt_hw_interrupt_enable(level);
}

/**
 * This function will enter corresponding power mode.
 */
void rt_pm_enter(void)
{
    struct rt_pm *pm;
    rt_uint32_t index;
    rt_tick_t timeout_tick;

    pm = &_pm;
    
    /* check each low power mode to decide which mode can system sleep. */
    for (index = 0; index < PM_MODE_MAX + 1; index ++)
    {
        if (pm->mode[index])
        {
            if (pm->timer_mask & (1 << index))
            {                
                /* should start pm timer */
                timeout_tick = rt_timer_next_timeout_tick();
                if (timeout_tick == RT_TICK_MAX)
                {
                    /* startup pm timer to keep comptible */
                    pm->ops->timer_start(pm, timeout_tick);
                }
                else
                {
                    timeout_tick -= rt_tick_get();
                    /* startup pm timer */
                    pm->ops->timer_start(pm, timeout_tick);
                }
                pm->pm_tick = pm->ops->timer_get_tick(pm);
            }
            
            /* let mcu sleep when system is idle */
            if (index > PM_RUNNING_MODE || index < pm->pm_mode)
            {
                /* set current power mode */
                pm->pm_mode = index;

				/* suspend all of devices with PM feature */
				_pm_device_suspend();
                pm->ops->enter(pm);
            }
            /* exit from low power mode */
            rt_pm_exit();
            break;
        }
    }
}

/**
 * This function exits from low power mode.
 */
void rt_pm_exit(void)
{
    struct rt_pm *pm;
    rt_tick_t delta_tick;

    pm = &_pm;
    
    /* exit from timer mode */
    if (pm->pm_mode > PM_DEEPSLEEP_MODE && pm->pm_mode < PM_SHUTDOWN_MODE)
    {
        /* get the tick of pm timer */
        delta_tick = pm->ops->timer_get_tick(pm);

        /* rt_kprintf("delta tick: %d\n", delta_tick); */
        /* stop pm timer */
        pm->ops->timer_stop(pm);
        //rt_kprintf("lptim os tick: %d\n", delta_tick);

        if (delta_tick > 0)
        {
            /* adjust OS tick */
            rt_tick_set(rt_tick_get() + delta_tick);
            /* check system timer */
            rt_timer_check();
            /* invoke low power driver ops */
            pm->ops->exit(pm);
			/* resume the device with PM feature */
			_pm_device_resume();
        }
    }

    /* exit from shutdown mode */
    if (pm->pm_mode > PM_DEEPTIMER_MODE)
    {
        /* invoke low power driver ops */
        pm->ops->exit(pm);
		/* resume the device with PM feature */
		_pm_device_resume();
    }
}

/**
 * Upper application or device driver requests the system
 * stall in corresponding power mode.
 */
void rt_pm_request(rt_ubase_t mode)
{
    rt_ubase_t level;
    struct rt_pm *pm;

    pm = &_pm;

    if (mode > PM_MODE_MAX)
        return;

    level = rt_hw_interrupt_disable();
    pm->mode[mode] ++;
    rt_hw_interrupt_enable(level);

    if (mode < pm->pm_mode)
    {
        pm->pm_mode = mode;
        pm->ops->exit(pm);
        pm->ops->enter(pm);
    }
}

/**
 * Upper application or device driver releases the stall 
 * of corresponding power mode. 
 */
void rt_pm_release(rt_ubase_t mode)
{
    rt_ubase_t level;
    struct rt_pm *pm;

    pm = &_pm;

    if (mode > PM_MODE_MAX)
        return;

    level = rt_hw_interrupt_disable();
    if (pm->mode[mode] > 0)
        pm->mode[mode] --;
    rt_hw_interrupt_enable(level);
}

/**
 * Register a device with PM feature
 *
 * @param device the device with PM feature
 * @param ops the PM ops for device 
 */
void rt_pm_register_device(struct rt_device* device, const struct rt_device_pm_ops* ops)
{
	struct rt_device_pm* device_pm;
	RT_DEBUG_NOT_IN_INTERRUPT;

	rt_sem_take(&(_pm.lock), RT_WAITING_FOREVER);
	
	device_pm = (struct rt_device_pm*)RT_KERNEL_REALLOC(_pm.device_pm, 
		(_pm.device_pm_number + 1)* sizeof(struct rt_device_pm));
	if (device_pm != RT_NULL)
	{
		_pm.device_pm = device_pm;
		_pm.device_pm[_pm.device_pm_number].device = device;
		_pm.device_pm[_pm.device_pm_number].ops    = ops;
		_pm.device_pm_number += 1;
	}

	rt_sem_release(&(_pm.lock));
}

/**
 * Unregister device from PM manager.
 *
 * @param device the device with PM feature
 */
void rt_pm_unregister_device(struct rt_device* device)
{
	rt_uint32_t index;
	RT_DEBUG_NOT_IN_INTERRUPT;

	rt_sem_take(&(_pm.lock), RT_WAITING_FOREVER);
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

	rt_sem_release(&(_pm.lock));
}

/**
 * Change the frequency of system.
 *
 * @param frequency the destination frequency need to be changed.
 * 
 * @note the frequency value is defined by BSP. 
 */
void rt_pm_frequency_change(rt_uint32_t frequency)
{
	/* make the frequency change */
	if (_pm.ops->frequency_change != RT_NULL)
	{
		/* do frequency change on the device driver level */
		_pm.ops->frequency_change(&_pm, frequency);
		/* notifiy all of device with PM feature */
		_pm_device_frequency_change();
	}
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
    pm = RT_PM_DEVICE(dev);
    RT_ASSERT(pm != RT_NULL);

    if (pos <= PM_MODE_MAX)
    {
        int mode;

        mode = pm->mode[pos];
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
                                      rt_uint8_t  cmd,
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
    rt_thread_idle_sethook(rt_pm_enter);

    rt_memset(pm->mode, 0, sizeof(pm->mode));
    pm->pm_mode = PM_RUNNING_MODE;
    pm->timer_mask = timer_mask;
    pm->pm_tick = 0;

    pm->ops = ops;
	pm->device_pm = RT_NULL;
	pm->device_pm_number = 0;
	/* initialize semaphore */
	rt_sem_init(&(pm->lock), "pm", 1, RT_IPC_FLAG_FIFO);

    /* invoke pm request in running mode */
    rt_pm_request(PM_RUNNING_MODE);
    /* request sleep mode */
    rt_pm_request(PM_SLEEP_MODE);
    /* must hold on deep shutdown mode */
    rt_pm_request(PM_DEEPSHUTDOWN_MODE);
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static const char* pm_str[] = 
{
    "High Speed Mode", 
    "Running Mode", 
    "Sleep Mode", 
    "Deep Sleep Mode", 
    "Timer Mode", 
    "Deep Timer Mode",
    "Shutdown Mode", 
    "Deep Shutdown Mode", 
};

void rt_pm_dump_status(void)
{
    rt_uint32_t index;
    struct rt_pm *pm;

    pm = &_pm;

    rt_kprintf("Power Management Mode Status:\n");
	rt_kprintf("+--------------------+----+\n");
    for (index = 0; index < PM_MODE_MAX + 1; index ++)
    {
		rt_kprintf("| %018s | %2d |\n", pm_str[index], pm->mode[index]);
    }
	rt_kprintf("+--------------------+----+\n\n");

    rt_kprintf("timer mask: 0x%02x\n", pm->timer_mask);
    rt_kprintf("pm timer tick: %d\n", pm->pm_tick);
}
FINSH_FUNCTION_EXPORT_ALIAS(rt_pm_dump_status, pm_dump, dump power management status);
MSH_CMD_EXPORT_ALIAS(rt_pm_dump_status, pm_dump, dump power management status);
#endif

#endif
