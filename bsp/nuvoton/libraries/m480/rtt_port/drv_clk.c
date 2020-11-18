/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-03-25      klcheng      First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_CLK)

#include <rtdevice.h>
#include <rtdbg.h>
#include <stdint.h>
#include <string.h>
#include <NuMicro.h>


/* Private define ---------------------------------------------------------------*/

/* pm run mode speed mapping */
#define CONFIG_HIGH_SPEED_FREQ      (192000000ul)
#define CONFIG_NORMAL_SPEED_FREQ    (192000000ul)
#define CONFIG_MEDIMUM_SPEED_FREQ   (144000000ul)
#define CONFIG_LOW_SPEED_FREQ       (72000000ul)

/* pm sleep mode mapping */
#define CONFIG_MODE_LIGHT           (CLK_PMUCTL_PDMSEL_FWPD)
#define CONFIG_MODE_DEEP            (CLK_PMUCTL_PDMSEL_PD)
#define CONFIG_MODE_STANDBY         (CLK_PMUCTL_PDMSEL_SPD1)
#define CONFIG_MODE_SHUTDOWN        (CLK_PMUCTL_PDMSEL_DPD)


#if defined (NU_CLK_INVOKE_WKTMR)
    /* Wake-up timer clock source is OSC10K */
    #define WKTMR_INTERVAL              (CLK_PMUCTL_WKTMRIS_65536)
#endif


/* Timer module assigned for pm device usage. */
/* e.g. If TIMERn is reserved for pm, then define the PM_TIMER_USE_INSTANCE
        macro to n value (without parentheses). */
#define PM_TIMER_USE_INSTANCE       3


/* Concatenate */
#define _CONCAT2_(x, y)             x##y
#define _CONCAT3_(x, y, z)          x##y##z
#define CONCAT2(x, y)               _CONCAT2_(x, y)
#define CONCAT3(x, y, z)            _CONCAT3_(x,y,z)

/* Concatenate the macros of timer instance for driver usage. */
#define PM_TIMER                    CONCAT2(TIMER, PM_TIMER_USE_INSTANCE)
#define PM_TMR                      CONCAT2(TMR, PM_TIMER_USE_INSTANCE)
#define PM_TIMER_MODULE             CONCAT2(PM_TMR, _MODULE)
#define PM_TIMER_IRQn               CONCAT2(PM_TMR, _IRQn)
#define PM_TIMER_IRQHandler         CONCAT2(PM_TMR, _IRQHandler)
#define PM_TIMER_SEL_LXT            CONCAT3(CLK_CLKSEL1_, PM_TMR, SEL_LXT)

/* Private typedef --------------------------------------------------------------*/


/* Private functions ------------------------------------------------------------*/
static void pm_sleep(struct rt_pm *pm, rt_uint8_t mode);
static void pm_run(struct rt_pm *pm, rt_uint8_t mode);
static void pm_timer_start(struct rt_pm *pm, rt_uint32_t timeout);
static void pm_timer_stop(struct rt_pm *pm);
static rt_tick_t pm_timer_get_tick(struct rt_pm *pm);
static rt_tick_t pm_tick_from_os_tick(rt_tick_t os_tick);
static rt_tick_t os_tick_from_pm_tick(rt_tick_t pm_tick);

/* Public functions -------------------------------------------------------------*/
int rt_hw_pm_init(void);

/* Private variables ------------------------------------------------------------*/
static struct rt_pm_ops ops =
{
    .sleep = pm_sleep,
    .run = pm_run,
    .timer_start = pm_timer_start,
    .timer_stop = pm_timer_stop,
    .timer_get_tick = pm_timer_get_tick,
};

struct rt_device pm;



/* pm sleep() entry */
static void pm_sleep(struct rt_pm *pm, rt_uint8_t mode)
{
    SYS_UnlockReg();

    switch (mode)
    {
    /*  wake-up source:                                                    */
    /*      PM_SLEEP_MODE_LIGHT : TIMERn                                   */
    /*      PM_SLEEP_MODE_DEEP : TIMERn                                    */
    /*      PM_SLEEP_MODE_STANDBY : wake-up timer  (optional)              */
    /*      PM_SLEEP_MODE_SHUTDOWN : wake-up timer  (optional)             */

    case PM_SLEEP_MODE_NONE:
    case PM_SLEEP_MODE_IDLE:
        break;

    case PM_SLEEP_MODE_LIGHT:

        CLK_SetPowerDownMode(CONFIG_MODE_LIGHT);
        CLK_PowerDown();
        break;

    case PM_SLEEP_MODE_DEEP:

        CLK_SetPowerDownMode(CONFIG_MODE_DEEP);
        CLK_PowerDown();
        break;

    case PM_SLEEP_MODE_STANDBY:

#if defined (NU_CLK_INVOKE_WKTMR)

        /* Enable wake-up timer with pre-defined interval if it is invoked */
        CLK_SET_WKTMR_INTERVAL(WKTMR_INTERVAL);
        CLK_ENABLE_WKTMR();
#endif
        CLK_SetPowerDownMode(CONFIG_MODE_STANDBY);
        CLK_PowerDown();
        break;

    case PM_SLEEP_MODE_SHUTDOWN:

#if defined (NU_CLK_INVOKE_WKTMR)
        /* Enable wake-up timer with pre-defined interval if it is invoked */
        CLK_SET_WKTMR_INTERVAL(WKTMR_INTERVAL);
        CLK_ENABLE_WKTMR();
#endif
        CLK_SetPowerDownMode(CONFIG_MODE_SHUTDOWN);
        CLK_PowerDown();
        break;

    default:
        RT_ASSERT(0);
        break;
    }

    SYS_LockReg();
}


/* pm run() entry */
static void pm_run(struct rt_pm *pm, rt_uint8_t mode)
{
    static uint8_t prev_mode = RT_PM_DEFAULT_RUN_MODE;

    /* ignore it if power mode is the same. */
    if (mode == prev_mode)
        return;

    prev_mode = mode;

    SYS_UnlockReg();

    /* Switch run mode frequency using PLL + HXT if HXT is enabled.
       Otherwise, the system clock will use PLL + HIRC. */
    switch (mode)
    {
    case PM_RUN_MODE_HIGH_SPEED:

        CLK_SetCoreClock(CONFIG_HIGH_SPEED_FREQ);
        break;

    case PM_RUN_MODE_NORMAL_SPEED:

        CLK_SetCoreClock(CONFIG_NORMAL_SPEED_FREQ);
        break;

    case PM_RUN_MODE_MEDIUM_SPEED:

        CLK_SetCoreClock(CONFIG_MEDIMUM_SPEED_FREQ);
        break;

    case PM_RUN_MODE_LOW_SPEED:

        CLK_SetCoreClock(CONFIG_LOW_SPEED_FREQ);
        break;

    default:
        RT_ASSERT(0);
        break;
    }

    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    SYS_LockReg();
}


static void hw_timer_init(void)
{
    /* Assign a hardware timer for pm usage. */
    SYS_UnlockReg();
    CLK_SetModuleClock(PM_TIMER_MODULE, PM_TIMER_SEL_LXT, MODULE_NoMsk);
    CLK_EnableModuleClock(PM_TIMER_MODULE);
    SYS_LockReg();

    /* Initialize timer and enable wakeup function. */
    TIMER_Open(PM_TIMER, TIMER_CONTINUOUS_MODE, 1);
    TIMER_SET_PRESCALE_VALUE(PM_TIMER, 0);
    TIMER_EnableInt(PM_TIMER);
    TIMER_EnableWakeup(PM_TIMER);
    NVIC_EnableIRQ(PM_TIMER_IRQn);
}


/* convert os tick to pm timer tick */
static rt_tick_t pm_tick_from_os_tick(rt_tick_t os_tick)
{
    rt_uint32_t hz = TIMER_GetModuleClock(PM_TIMER);

    return (rt_tick_t)(hz * os_tick / RT_TICK_PER_SECOND);
}


/* convert pm timer tick to os tick */
static rt_tick_t os_tick_from_pm_tick(rt_tick_t pm_tick)
{
    static rt_uint32_t os_tick_remain = 0;
    rt_uint32_t ret, hz;

    hz = TIMER_GetModuleClock(PM_TIMER);
    ret = (pm_tick * RT_TICK_PER_SECOND + os_tick_remain) / hz;

    os_tick_remain += (pm_tick * RT_TICK_PER_SECOND);
    os_tick_remain %= hz;

    return ret;
}


/* pm_ops timer_get_tick() entry */
static rt_tick_t pm_timer_get_tick(struct rt_pm *pm)
{
    rt_tick_t tick;

    tick = TIMER_GetCounter(PM_TIMER);

    return os_tick_from_pm_tick(tick);
}


/* pm timer_start() entry */
static void pm_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    int tick;

    if (timeout == RT_TICK_MAX)
        return;

    /* start pm timer to compensate the os tick in power down mode */
    tick = pm_tick_from_os_tick(timeout);
    TIMER_SET_CMP_VALUE(PM_TIMER, tick);
    TIMER_Start(PM_TIMER);
}


/* pm timer_stop() entry */
static void pm_timer_stop(struct rt_pm *pm)
{
    TIMER_Stop(PM_TIMER);
    TIMER_ResetCounter(PM_TIMER);
}


/* pm device driver initialize. */
int rt_hw_pm_init(void)
{
    rt_uint8_t timer_mask;

    if (CLK_GetPMUWKSrc())
    {
        /* Release I/O hold status after wake-up from Standby Power-down Mode (SPD) */
        CLK->IOPDCTL = 1;

        /* Clear Power Manager Status register */
        CLK->PMUSTS = CLK_PMUSTS_CLRWK_Msk;
    }

    hw_timer_init();

    /* initialize timer mask */
    timer_mask = (1UL << PM_SLEEP_MODE_LIGHT) |
                 (1UL << PM_SLEEP_MODE_DEEP);

    /* initialize system pm module */
    rt_system_pm_init(&ops, timer_mask, RT_NULL);

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_pm_init);


/* pm timer interrupt entry */
void PM_TIMER_IRQHandler(void)
{
    rt_interrupt_enter();

    if (TIMER_GetIntFlag(PM_TIMER))
    {
        TIMER_ClearIntFlag(PM_TIMER);
    }

    if (TIMER_GetWakeupFlag(PM_TIMER))
    {
        TIMER_ClearWakeupFlag(PM_TIMER);
    }

    rt_interrupt_leave();
}

#endif /* BSP_USING_CLK */



