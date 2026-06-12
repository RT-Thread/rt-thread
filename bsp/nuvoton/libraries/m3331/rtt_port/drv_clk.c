/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_CLK)

#include "NuMicro.h"
#include "rtdevice.h"
#include "rthw.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.clk"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

/* pm run mode speed mapping */
#define CONFIG_HIGH_SPEED_FREQ      (__HSI)
#define CONFIG_NORMAL_SPEED_FREQ    (__HSI)
#define CONFIG_MEDIMUM_SPEED_FREQ   (__HSI/2)
#define CONFIG_LOW_SPEED_FREQ       (__HSI/2)

/* pm sleep mode mapping */
#define CONFIG_MODE_LIGHT           (CLK_PMUCTL_PDMSEL_FWPD)
#define CONFIG_MODE_DEEP            (CLK_PMUCTL_PDMSEL_NPD)
#define CONFIG_MODE_STANDBY         (CLK_PMUCTL_PDMSEL_SPD)
#define CONFIG_MODE_SHUTDOWN        (CLK_PMUCTL_PDMSEL_DPD)
#if defined (NU_CLK_INVOKE_WKTMR)
    /* The Wake-up Timer Time-out Interval selection. It could be
    * CLK_PMUCTL_WKTMRIS_512     - Select Wake-up Timer Time-out Interval is 512 LIRC clocks (16 ms)
    * CLK_PMUCTL_WKTMRIS_1024    - Select Wake-up Timer Time-out Interval is 1204 LIRC clocks (32 ms)
    * CLK_PMUCTL_WKTMRIS_2048    - Select Wake-up Timer Time-out Interval is 2048 LIRC clocks (64 ms)
    * CLK_PMUCTL_WKTMRIS_4096    - Select Wake-up Timer Time-out Interval is 4096 LIRC clocks (128 ms)
    * CLK_PMUCTL_WKTMRIS_8192    - Select Wake-up Timer Time-out Interval is 8192 LIRC clocks (256 ms)
    * CLK_PMUCTL_WKTMRIS_16384   - Select Wake-up Timer Time-out Interval is 16384 LIRC clocks (512 ms)
    * CLK_PMUCTL_WKTMRIS_32768   - Select Wake-up Timer Time-out Interval is 32768 LIRC clocks (1024 ms)
    * CLK_PMUCTL_WKTMRIS_65536   - Select Wake-up Timer Time-out Interval is 65536 LIRC clocks (2048 ms)
    * CLK_PMUCTL_WKTMRIS_131072  - Select Wake-up Timer Time-out Interval is 131072 LIRC clocks (4096 ms)
    * CLK_PMUCTL_WKTMRIS_262144  - Select Wake-up Timer Time-out Interval is 262144 LIRC clocks (8192 ms)
    * CLK_PMUCTL_WKTMRIS_524288  - Select Wake-up Timer Time-out Interval is 524288 LIRC clocks (16384 ms)
    * CLK_PMUCTL_WKTMRIS_1048576 - Select Wake-up Timer Time-out Interval is 1048576 LIRC clocks (32768 ms)
    * CLK_PMUCTL_WKTMRIS_2097152 - Select Wake-up Timer Time-out Interval is 2097152 LIRC clocks (65536 ms)
    * CLK_PMUCTL_WKTMRIS_4194304 - Select Wake-up Timer Time-out Interval is 4194304 LIRC clocks (131072 ms)
    */
    #define WKTMR_INTERVAL          (CLK_PMUCTL_WKTMRIS_131072)
#endif

/* Timer module assigned for pm device usage. */
/* e.g. If TIMERn is reserved for pm, then define the PM_TIMER_USE_INSTANCE
        macro to n value (without parentheses). */
#define PM_TIMER_USE_INSTANCE       3

/* Concatenate */
#define _CONCAT2_(x, y)             x##y
#define _CONCAT3_(x, y, z)          x##y##z
#define CONCAT2(x, y)               _CONCAT2_(x, y)
#define CONCAT3(x, y, z)            _CONCAT3_(x, y, z)

/* Concatenate the macros of timer instance for driver usage. */
#define PM_TIMER                    CONCAT2(TIMER, PM_TIMER_USE_INSTANCE)
#define PM_TMR                      CONCAT2(TMR, PM_TIMER_USE_INSTANCE)
#define PM_TIMER_MODULE             CONCAT2(PM_TMR, _MODULE)
#define PM_TIMER_IRQn               CONCAT2(PM_TMR, _IRQn)
#define PM_TIMER_IRQHandler         CONCAT2(PM_TMR, _IRQHandler)
#define PM_TIMER_SEL_LXT            CONCAT3(CLK_CLKSEL1_, PM_TMR, SEL_LXT)

/* Types / Structures ---------------------------------------------------------*/

/* Static Function Prototypes ------------------------------------------------*/
static void pm_sleep(struct rt_pm *pm, rt_uint8_t mode);
static void pm_run(struct rt_pm *pm, rt_uint8_t mode);
static void pm_timer_start(struct rt_pm *pm, rt_uint32_t timeout);
static void pm_timer_stop(struct rt_pm *pm);
static rt_tick_t pm_timer_get_tick(struct rt_pm *pm);
static rt_tick_t pm_tick_from_os_tick(rt_tick_t os_tick);
static rt_tick_t os_tick_from_pm_tick(rt_tick_t pm_tick);
int rt_hw_pm_init(void);

/* Static Variables ----------------------------------------------------------*/
static struct rt_pm_ops ops =
{
    .sleep = pm_sleep,
    .run = pm_run,
    .timer_start = pm_timer_start,
    .timer_stop = pm_timer_stop,
    .timer_get_tick = pm_timer_get_tick,
};

/* Sleep and power-down mapping */
static const uint32_t g_au32SleepingMode[PM_SLEEP_MODE_MAX] =
{
    0,
    0,
    CONFIG_MODE_LIGHT,
    CONFIG_MODE_DEEP,
    CONFIG_MODE_STANDBY,
    CONFIG_MODE_SHUTDOWN
};

/* Functions Implementation --------------------------------------------------*/

rt_weak void pm_get_wksrc(void)
{
    uint32_t u32RegRstsrc;

    if ((u32RegRstsrc = CLK_GetPMUWKSrc()) != 0)
    {
        /* Release I/O hold status after wake-up from Standby Power-down Mode (SPD) */
        CLK->IOPDCTL = 1;

        rt_kprintf("CLK_PMUSTS: 0x%08X\n", u32RegRstsrc);

        /* Clear Power Manager Status register */
        CLK->PMUSTS = CLK_PMUSTS_CLRWK_Msk;
    }
}

rt_weak void pm_set_wksrc(rt_uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_STANDBY:
    /* FALLTHROUGH */
    case PM_SLEEP_MODE_SHUTDOWN:
#if defined (NU_CLK_INVOKE_WKTMR)
        /* Enable wake-up timer with pre-defined interval if it is invoked */
        CLK_SET_WKTMR_INTERVAL(WKTMR_INTERVAL);
        CLK_ENABLE_WKTMR();
#elif defined(BSP_USING_RTC)
        /* Enable RTC wake-up. */
        CLK_ENABLE_RTCWK();
#endif
    default:
        return;
    }
}

rt_weak void pm_sleep_before(rt_uint8_t mode)
{
}

rt_weak void pm_sleep_after(rt_uint8_t mode)
{
}
static void pm_sleep(struct rt_pm *pm, rt_uint8_t mode)
{
    RT_ASSERT(mode < PM_SLEEP_MODE_MAX);

    /*  wake-up source:                                                    */
    /*      PM_SLEEP_MODE_LIGHT : TIMERn                                   */
    /*      PM_SLEEP_MODE_DEEP : TIMERn                                    */
    /*      PM_SLEEP_MODE_STANDBY : wake-up timer  (optional)              */
    /*      PM_SLEEP_MODE_SHUTDOWN : wake-up timer  (optional)             */

    switch (mode)
    {
    case PM_SLEEP_MODE_STANDBY:
    /* Standby mode, CPU stops, device context loss (can be saved to special peripherals),
    usually reset after wake-up */

    /* FALLTHROUGH */

    case PM_SLEEP_MODE_SHUTDOWN:
    /* Shutdown mode, lower power consumption than Standby mode, context is usually irrecoverable, reset after wake-up */

    /* FALLTHROUGH */

    case PM_SLEEP_MODE_LIGHT:
    /* Light sleep modes, CPU stops, most clocks and peripherals stop, and time compensation is required after wake-up. */

    /* FALLTHROUGH */

    case PM_SLEEP_MODE_DEEP:
        /* Deep sleep mode, CPU stops, only a few low power peripheral work, can be awakened by special interrupts */

        pm_set_wksrc(mode);

        break;

    case PM_SLEEP_MODE_IDLE:
        /* The idle mode, which stops CPU and part of the clock when the system is idle. Any event or interrupt can wake up system. */
        CLK_Idle();

    /* FALLTHROUGH */

    case PM_SLEEP_MODE_NONE:
    /* The system is active without any power reduction. */

    default:
        return;
    }
    pm_sleep_before(mode);

    /* Flush TX FIFO of default console UART. */
    if (rt_console_get_device())
        rt_device_control(rt_console_get_device(), 9527, 0);

    /* Set Power-down Mode */
    CLK_SetPowerDownMode(g_au32SleepingMode[mode]);

    /* Here, take a break. */
    CLK_PowerDown();

    /* Do something after wakeup. */
    pm_sleep_after(mode);
}
static void pm_run(struct rt_pm *pm, rt_uint8_t mode)
{
    static uint8_t prev_mode = RT_PM_DEFAULT_RUN_MODE;

    /* ignore it if power mode is the same. */
    if (mode == prev_mode)
        return;

    prev_mode = mode;

    /* Switch run mode frequency using PLL + HXT if HXT is enabled.
       Otherwise, the system clock will use PLL + HIRC. */
    switch (mode)
    {
    case PM_RUN_MODE_HIGH_SPEED:

        LOG_I("Set CPU frequency to %d!!!", CONFIG_HIGH_SPEED_FREQ);
        CLK_SetCoreClock(CONFIG_HIGH_SPEED_FREQ);
        break;

    case PM_RUN_MODE_NORMAL_SPEED:

        LOG_I("Set CPU frequency to %d!!!", CONFIG_NORMAL_SPEED_FREQ);
        CLK_SetCoreClock(CONFIG_NORMAL_SPEED_FREQ);
        break;

    case PM_RUN_MODE_MEDIUM_SPEED:

        LOG_I("Set CPU frequency to %d!!!", CONFIG_MEDIMUM_SPEED_FREQ);
        CLK_SetCoreClock(CONFIG_MEDIMUM_SPEED_FREQ);
        break;

    case PM_RUN_MODE_LOW_SPEED:

        LOG_I("Set CPU frequency to %d!!!", CONFIG_LOW_SPEED_FREQ);
        CLK_SetCoreClock(CONFIG_LOW_SPEED_FREQ);
        break;

    default:
        return;
    }

    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    LOG_I("Current HCLK/CPU/PCLK0/PCLK1 frequency are %d/%d/%d/%d!!!",
          CLK_GetHCLKFreq(),
          CLK_GetCPUFreq(),
          CLK_GetPCLK0Freq(),
          CLK_GetPCLK1Freq());
}

static void hw_timer_init(void)
{
    /* Assign a hardware timer for pm usage. */
    CLK_SetModuleClock(PM_TIMER_MODULE, PM_TIMER_SEL_LXT, MODULE_NoMsk);
    CLK_EnableModuleClock(PM_TIMER_MODULE);

    /* Initialize timer and enable wakeup function. */
    TIMER_Open(PM_TIMER, TIMER_CONTINUOUS_MODE, 1);
    TIMER_SET_PRESCALE_VALUE(PM_TIMER, 0);
    TIMER_EnableInt(PM_TIMER);
    TIMER_EnableWakeup(PM_TIMER);
    NVIC_EnableIRQ(PM_TIMER_IRQn);
}
static rt_tick_t pm_tick_from_os_tick(rt_tick_t os_tick)
{
    rt_uint32_t hz = TIMER_GetModuleClock(PM_TIMER);

    return (rt_tick_t)(hz * os_tick / RT_TICK_PER_SECOND);
}
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
static rt_tick_t pm_timer_get_tick(struct rt_pm *pm)
{
    rt_tick_t tick = TIMER_GetCounter(PM_TIMER);

    return os_tick_from_pm_tick(tick);
}
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
static void pm_timer_stop(struct rt_pm *pm)
{
    TIMER_Stop(PM_TIMER);
    TIMER_ResetCounter(PM_TIMER);
}
int rt_hw_pm_init(void)
{
    rt_uint8_t timer_mask;

    pm_get_wksrc();

    hw_timer_init();

    /* Set the bit corresponding to Deep Sleep mode to enable sleep time compensation */
    timer_mask = (1UL << PM_SLEEP_MODE_LIGHT) | (1UL << PM_SLEEP_MODE_DEEP);

    /* initialize system pm module */
    rt_system_pm_init(&ops, timer_mask, RT_NULL);

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_pm_init);

extern void rt_pm_exit_critical(rt_uint32_t ctx, rt_uint8_t sleep_mode);
void rt_pm_exit_critical(rt_uint32_t ctx, rt_uint8_t sleep_mode)
{
    if ((sleep_mode == PM_SLEEP_MODE_LIGHT) || (sleep_mode == PM_SLEEP_MODE_DEEP))
    {
        if (TIMER_GetIntFlag(PM_TIMER))
        {
            TIMER_ClearIntFlag(PM_TIMER);
        }

        if (TIMER_GetWakeupFlag(PM_TIMER))
        {
            TIMER_ClearWakeupFlag(PM_TIMER);
        }

        NVIC_ClearPendingIRQ(PM_TIMER_IRQn);
    }

    rt_hw_interrupt_enable(ctx);
}
#endif /* BSP_USING_CLK */
