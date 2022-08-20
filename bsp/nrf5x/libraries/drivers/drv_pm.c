/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-09     forest-rain    first version
 */

#include <board.h>
#include <drv_lptim.h>

#include <nrfx_power.h>
#include <nrfx_uart.h>
#include <nrfx_systick.h>

#ifdef RT_USING_PM

#define FPU_EXCEPTION_MASK 0x0000009F

/**
 * This function will setup nrf ram retention, just for a example
 *
 * @param retention
 */
RT_WEAK void nrf_ram_retention(bool retention)
{
    // Switch on both RAM banks when in System OFF mode.
#if defined(NRF52832_XXAA) || defined(NRF51422) || defined(NRF51822)
    if(retention == false)
    {
        NRF_POWER->RAMON &=~((POWER_RAMON_OFFRAM0_RAM0On << POWER_RAMON_OFFRAM0_Pos) |
                            (POWER_RAMON_OFFRAM1_RAM1On << POWER_RAMON_OFFRAM1_Pos));
    }
    else
    {
        NRF_POWER->RAMON |= (POWER_RAMON_OFFRAM0_RAM0On << POWER_RAMON_OFFRAM0_Pos) |
                            (POWER_RAMON_OFFRAM1_RAM1On << POWER_RAMON_OFFRAM1_Pos);
    }
#elif defined(NRF52840_XXAA) || defined(NRF52833_XXAA)
    uint32_t ram_section;
    ram_section = (POWER_RAM_POWER_S0POWER_On << POWER_RAM_POWER_S0POWER_Pos)      |
                            (POWER_RAM_POWER_S1POWER_On      << POWER_RAM_POWER_S1POWER_Pos)      |
                            (POWER_RAM_POWER_S2POWER_On      << POWER_RAM_POWER_S2POWER_Pos)      |
                            (POWER_RAM_POWER_S3POWER_On      << POWER_RAM_POWER_S3POWER_Pos)      |
                            (POWER_RAM_POWER_S4POWER_On      << POWER_RAM_POWER_S4POWER_Pos)      |
                            (POWER_RAM_POWER_S5POWER_On      << POWER_RAM_POWER_S5POWER_Pos)      |
                            (POWER_RAM_POWER_S6POWER_On      << POWER_RAM_POWER_S6POWER_Pos)      |
                            (POWER_RAM_POWER_S7POWER_On      << POWER_RAM_POWER_S7POWER_Pos)      |
                            (POWER_RAM_POWER_S8POWER_On      << POWER_RAM_POWER_S8POWER_Pos)      |
                            (POWER_RAM_POWER_S9POWER_On      << POWER_RAM_POWER_S9POWER_Pos)      |
                            (POWER_RAM_POWER_S10POWER_On     << POWER_RAM_POWER_S10POWER_Pos)     |
                            (POWER_RAM_POWER_S11POWER_On     << POWER_RAM_POWER_S11POWER_Pos)     |
                            (POWER_RAM_POWER_S12POWER_On     << POWER_RAM_POWER_S12POWER_Pos)     |
                            (POWER_RAM_POWER_S13POWER_On     << POWER_RAM_POWER_S13POWER_Pos)     |
                            (POWER_RAM_POWER_S14POWER_On     << POWER_RAM_POWER_S14POWER_Pos)     |
                            (POWER_RAM_POWER_S15POWER_On     << POWER_RAM_POWER_S15POWER_Pos)     |
                            (POWER_RAM_POWER_S0RETENTION_On  << POWER_RAM_POWER_S0RETENTION_Pos)  |
                            (POWER_RAM_POWER_S1RETENTION_On  << POWER_RAM_POWER_S1RETENTION_Pos)  |
                            (POWER_RAM_POWER_S2RETENTION_On  << POWER_RAM_POWER_S2RETENTION_Pos)  |
                            (POWER_RAM_POWER_S3RETENTION_On  << POWER_RAM_POWER_S3RETENTION_Pos)  |
                            (POWER_RAM_POWER_S4RETENTION_On  << POWER_RAM_POWER_S4RETENTION_Pos)  |
                            (POWER_RAM_POWER_S5RETENTION_On  << POWER_RAM_POWER_S5RETENTION_Pos)  |
                            (POWER_RAM_POWER_S6RETENTION_On  << POWER_RAM_POWER_S6RETENTION_Pos)  |
                            (POWER_RAM_POWER_S7RETENTION_On  << POWER_RAM_POWER_S7RETENTION_Pos)  |
                            (POWER_RAM_POWER_S8RETENTION_On  << POWER_RAM_POWER_S8RETENTION_Pos)  |
                            (POWER_RAM_POWER_S9RETENTION_On  << POWER_RAM_POWER_S9RETENTION_Pos)  |
                            (POWER_RAM_POWER_S10RETENTION_On << POWER_RAM_POWER_S10RETENTION_Pos) |
                            (POWER_RAM_POWER_S11RETENTION_On << POWER_RAM_POWER_S11RETENTION_Pos) |
                            (POWER_RAM_POWER_S12RETENTION_On << POWER_RAM_POWER_S12RETENTION_Pos) |
                            (POWER_RAM_POWER_S13RETENTION_On << POWER_RAM_POWER_S13RETENTION_Pos) |
                            (POWER_RAM_POWER_S14RETENTION_On << POWER_RAM_POWER_S14RETENTION_Pos) |
                            (POWER_RAM_POWER_S15RETENTION_On << POWER_RAM_POWER_S15RETENTION_Pos);
        
        if(retention == false)
        {
            NRF_POWER->RAM[0].POWERCLR = ram_section;
        }
        else
        {
            NRF_POWER->RAM[0].POWERSET = ram_section;
        }
        
#else
#error 'Unsupported MCU'
#endif
}

/**
 * This function will put nrfx into system on mode
 *
 * @param none
 */
static void nrf_sleep(void)
{
    // Trigger an event when an interrupt is pending. This allows to wake up
    // the processor from disabled interrupts.
    SCB->SCR |= SCB_SCR_SEVONPEND_Msk;

    #if defined(NRF52)  || defined(NRF52840_XXAA)
    /* Clear exceptions and PendingIRQ from the FPU unit */
    __set_FPSCR(__get_FPSCR()  & ~(FPU_EXCEPTION_MASK));
    (void) __get_FPSCR();
    NVIC_ClearPendingIRQ(FPU_IRQn);
    #endif

#if NRF_SDH_SOC_ENABLED == 1
    sd_app_evt_wait();
#else
    // Clear the internal event register.
    __SEV();
    __WFE();

    // Wait for an event.
    __WFE();
#endif
}

/**
 * This function will put nrfx into sleep mode.
 *
 * @param pm pointer to power manage structure
 */
static void sleep(struct rt_pm *pm, uint8_t mode)
{
    switch (mode)
    {
        case PM_SLEEP_MODE_NONE:
            break;

        //case PM_SLEEP_MODE_IDLE:
        //    break;
        
        case PM_SLEEP_MODE_LIGHT:
            // System On - Constant latency
            NRF_POWER->TASKS_CONSTLAT = 1;
            nrf_sleep();
            break;

        case PM_SLEEP_MODE_DEEP:
            // System On - Low Power (default)
            NRF_POWER->TASKS_LOWPWR = 1;
            nrf_sleep();
            break;

        case PM_SLEEP_MODE_STANDBY:
            // System Off (ram retention)
            nrf_ram_retention(true);
            nrf_power_system_off(NRF_POWER);
            break;
        
    case PM_SLEEP_MODE_SHUTDOWN:
            // System Off (no ram retention)
            nrf_ram_retention(false);
            nrf_power_system_off(NRF_POWER);
            break;
    
        default:
            RT_ASSERT(0);
            break;
    }
}

static uint8_t run_speed[2][2] =
{
    {64, 0},
    {64, 1},
};

static void run(struct rt_pm *pm, uint8_t mode)
{
    static uint8_t last_mode;
    static char *run_str[] = PM_RUN_MODE_NAMES;

    if (mode == last_mode)
        return;
    last_mode = mode;

    rt_kprintf("switch to %s mode, frequency = %d MHz\n", run_str[mode], run_speed[mode][0]);
}

/**
 * This function caculate the PM tick from OS tick
 *
 * @param tick OS tick
 *
 * @return the PM tick
 */
static rt_tick_t nrfx_pm_tick_from_os_tick(rt_tick_t tick)
{
    rt_uint32_t freq = nrfx_lptim_get_countfreq();

    return (freq * tick / RT_TICK_PER_SECOND);
}

/**
 * This function caculate the OS tick from PM tick
 *
 * @param tick PM tick
 *
 * @return the OS tick
 */
static rt_tick_t nrfx_os_tick_from_pm_tick(rt_uint32_t tick)
{
    static rt_uint32_t os_tick_remain = 0;
    rt_uint32_t ret, freq;

    freq = nrfx_lptim_get_countfreq();
    ret = (tick * RT_TICK_PER_SECOND + os_tick_remain) / freq;

    os_tick_remain += (tick * RT_TICK_PER_SECOND);
    os_tick_remain %= freq;

    return ret;
}

/**
 * This function start the timer of pm
 *
 * @param pm Pointer to power manage structure
 * @param timeout How many OS Ticks that MCU can sleep
 */
static void pm_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    RT_ASSERT(pm != RT_NULL);
    RT_ASSERT(timeout > 0);

    if (timeout != RT_TICK_MAX)
    {
        /* Convert OS Tick to pmtimer timeout value */
        timeout = nrfx_pm_tick_from_os_tick(timeout);
        if (timeout > nrfx_lptim_get_tick_max())
        {
            timeout = nrfx_lptim_get_tick_max();
        }

        /* Enter PM_TIMER_MODE */
        nrfx_lptim_start(timeout);
    }
}

/**
 * This function stop the timer of pm
 *
 * @param pm Pointer to power manage structure
 */
static void pm_timer_stop(struct rt_pm *pm)
{
    RT_ASSERT(pm != RT_NULL);

    /* Reset pmtimer status */
    nrfx_lptim_stop();
}

/**
 * This function calculate how many OS Ticks that MCU have suspended
 *
 * @param pm Pointer to power manage structure
 *
 * @return OS Ticks
 */
static rt_tick_t pm_timer_get_tick(struct rt_pm *pm)
{
    rt_uint32_t timer_tick;

    RT_ASSERT(pm != RT_NULL);

    timer_tick = nrfx_lptim_get_current_tick();

    return nrfx_os_tick_from_pm_tick(timer_tick);
}

/**
 * This function initialize the power manager
 */
int drv_pm_hw_init(void)
{
    static const struct rt_pm_ops _ops =
    {
        sleep,
        run,
        pm_timer_start,
        pm_timer_stop,
        pm_timer_get_tick
    };
    
    rt_uint8_t timer_mask = 0;

    /* initialize timer mask */
    timer_mask = 1UL << PM_SLEEP_MODE_DEEP;

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);

    return 0;
}

INIT_BOARD_EXPORT(drv_pm_hw_init);

#endif /* RT_USING_PM */
