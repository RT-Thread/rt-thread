/*
 * File      : drv_pm.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author          Notes
 * 2012-08-20     heyuanjie87     the first version
 */
#include "board.h"
#include "drv_pm.h"
#include "drv_pmtimer.h"

#ifdef  RT_USING_PM
#include <drivers/pm.h>

//#define DRV_PM_DEBUG

/**
 * This function caculate the PM tick from OS tick
 *
 * @param tick OS tick
 *
 * @return the PM tick
 */
static rt_tick_t stm32l4_pm_tick_from_os_tick(rt_tick_t tick)
{
    rt_uint32_t freq;

    freq = stm32l4_lptim_get_countfreq();
    freq -= 1;

    return (freq * tick / RT_TICK_PER_SECOND);
}

/**
 * This function caculate the OS tick from PM tick
 *
 * @param tick PM tick
 *
 * @return the OS tick
 */
static rt_tick_t stm32l4_os_tick_from_pm_tick(rt_uint32_t tick)
{
    rt_uint32_t ret, freq;
	static rt_uint32_t remain = 0;
    
    freq = stm32l4_lptim_get_countfreq() - 1;
    //rt_kprintf("lptim freq: %d\n", freq);

	ret = (tick * RT_TICK_PER_SECOND + remain) / freq;
    //rt_kprintf("lptim ret: %d\n", ret);
   
    remain += (tick * RT_TICK_PER_SECOND);
	remain %= freq;
    //rt_kprintf("lptim remain: %d\n", remain);

    
    return (ret);
}

static struct stm32l4_pm _stm32l4_pm;
//CMU_Select_TypeDef _cpu_clock;

/**
 * This function set MCU core into low-power mode
 *
 * @param pm Pointer to power manage structure
 */
static void stm32l4_enter(struct rt_pm *pm)
{
    rt_uint32_t mode;

    mode = pm->pm_mode;
	
    switch (mode)
    {
    case PM_HIGHSPEED_MODE:
    case PM_RUNNING_MODE:
        system_clock_config();
#ifdef DRV_PM_DEBUG
        print_rcc_freq_info();
#endif
        break;

    case PM_SLEEP_MODE:
    case PM_DEEPSLEEP_MODE:
        rt_kprintf("sleep to sleep mode\n");
        system_clock_config();
        HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI);
        break;
    case PM_TIMER_MODE:
    case PM_DEEPTIMER_MODE:
        rt_kprintf("sleep to timer mode\n");
        HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
        break;
    case PM_SHUTDOWN_MODE:
        rt_kprintf("sleep to shutdown mode\n");
        HAL_PWR_EnterSTANDBYMode();
        break;
    case PM_DEEPSHUTDOWN_MODE:  
        rt_kprintf("sleep to deep shutdown mode\n");
        HAL_PWREx_EnterSHUTDOWNMode();
        break;
    default:
        break;
    }
}

/**
 * This function exit from low-power mode
 *
 * @param pm Pointer to power manage structure
 */
static void stm32l4_exit(struct rt_pm *pm)
{
    struct stm32l4_pm *stm32pm;

    stm32pm = &_stm32l4_pm;

    /* Reset pmtimer status */
    stm32pm->timer_status = PMTIMER_ENTER_NONE;
}

static void stm32l4_frequency_change(struct rt_pm *pm, rt_uint32_t frequency)
{
	return;
}

/**
 * This function start the timer of pm
 *
 * @param pm Pointer to power manage structure
 * @param timeout How many OS Ticks that MCU can sleep
 */
static void stm32l4_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    struct stm32l4_pm *stm32pm;

    stm32pm = &_stm32l4_pm;

    if (timeout != RT_TICK_MAX)
    {
        /* Convert OS Tick to pmtimer timeout value */
        timeout = stm32l4_pm_tick_from_os_tick(timeout);
        if (timeout > 40) 
        {
            if (timeout > stm32l4_lptim_tick_max())
                timeout = stm32l4_lptim_tick_max();
            /* Enter PM_TIMER_MODE */
            stm32pm->timer_status = PMTIMER_ENTER_TIMER;
            stm32pm->timer_reload_value = timeout;
            stm32l4_lptim_start(timeout);
        }
        else
        {
            /* Only enter PM_SLEEP_MODE if time is too short */
            stm32pm->timer_status = PMTIMER_ENTER_SLEEP;
        }
    }
    else
    {
        /* Too long so that enter PM_SHUTDOWN_MODE */
        stm32pm->timer_status = PMTIMER_ENTER_STOP;
        /* rt_kprintf("switch to stop mode\n"); */
    }
}

/**
 * This function stop the timer of pm
 *
 * @param pm Pointer to power manage structure
 */
static void stm32l4_timer_stop(struct rt_pm *pm)
{
    struct stm32l4_pm *stm32pm;

    stm32pm = &_stm32l4_pm;

    stm32l4_lptim_stop();
    /* Reset pmtimer status */
    stm32pm->timer_status = PMTIMER_ENTER_NONE;
}

/**
 * This function calculate how many OS Ticks that MCU have suspended
 *
 * @param pm Pointer to power manage structure
 *
 * @return OS Ticks
 */
static rt_tick_t stm32l4_timer_get_tick(struct rt_pm *pm)
{
    rt_uint32_t tick = 0;
    struct stm32l4_pm *stm32pm;
    stm32pm = &_stm32l4_pm;

    if (stm32pm->timer_status == PMTIMER_ENTER_TIMER)
    {
        tick = stm32l4_lptim_get_tick();
    }
    tick = stm32l4_os_tick_from_pm_tick(tick);
    
    return tick;
}

const static struct rt_pm_ops _ops =
{
    stm32l4_enter,
    stm32l4_exit,
    stm32l4_frequency_change,
    stm32l4_timer_start,
    stm32l4_timer_stop,
    stm32l4_timer_get_tick
};

/**
 * This function initialize the power manager
 */
int stm32l4_pm_hw_init(void)
{
    struct stm32l4_pm *stm32pm;
    rt_uint8_t timer_mask;

    stm32pm = &_stm32l4_pm;
    stm32pm->timer_status = PMTIMER_ENTER_NONE;
    stm32pm->timer_reload_value = 0;

    /* initialize timer mask */
    timer_mask = (1UL << PM_TIMER_MODE) | (1UL << PM_DEEPTIMER_MODE);

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, (void *)stm32pm);
    /* initialize lptim, used for PMTIMER mode */
    stm32l4_hw_lptim_init();
	    
    return 0;
}
INIT_BOARD_EXPORT(stm32l4_pm_hw_init);


#endif
