/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-3-15       Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_WDT)
#include <rthw.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "NuMicro.h"

/*-------------------------------------------------------------------------------*/
/* watchdog timer timeout look up table                                          */
/*-------------------------------------------------------------------------------*/
/* clock = LIRC 32000Hz.                                                         */
/*                                                                               */
/*      working hz   toutsel     exp     cycles      timeout (s)                 */
/*      32000        0           4       16          0.0005                      */
/*                   1           6       64          0.0020                      */
/*                   2           8       256         0.0080                      */
/*                   3           10      1024        0.0320                      */
/*                   4           12      4096        0.1280                      */
/*                   5           14      16384       0.5120                      */
/*                   6           16      65536       2.0480                      */
/*                   7           18      262144      8.1920                      */
/*                   8           20      1048576     32.7680                     */
/*-------------------------------------------------------------------------------*/
/* clock = LXT 32768Hz.                                                          */
/*                                                                               */
/*      working hz   toutsel     exp     cycles      timeout (s)                 */
/*      32768        0           4       16          0.0005                      */
/*                   1           6       64          0.0020                      */
/*                   2           8       256         0.0078                      */
/*                   3           10      1024        0.0313                      */
/*                   4           12      4096        0.1250                      */
/*                   5           14      16384       0.5000                      */
/*                   6           16      65536       2.0000                      */
/*                   7           18      262144      8.0000                      */
/*                   8           20      1048576     32.000                      */
/*-------------------------------------------------------------------------------*/
/* clock = 96MHz HCLK divide 2048 = 93750 Hz.                                    */
/*                                                                               */
/*      working hz   toutsel     exp     cycles      timeout (s)                 */
/*      46875        0           4       16          0.00034                     */
/*                   1           6       64          0.00137                     */
/*                   2           8       256         0.00546                     */
/*                   3           10      1024        0.02185                     */
/*                   4           12      4096        0.08738                     */
/*                   5           14      16384       0.34953                     */
/*                   6           16      65536       1.39810                     */
/*                   7           18      262144      5.59241                     */
/*                   8           20      1048576     22.3696                     */
/*-------------------------------------------------------------------------------*/

/* Private define ---------------------------------------------------------------*/

/* Pick a suitable wdt timeout interval, it is a trade-off between the
   consideration of timeout accuracy and the system performance. The MIN_CYCLES
   parameter is a numerical value of the toutsel setting, and it must be set to
   a correct one which matches to the literal meaning of MIN_TOUTSEL. */
#define MIN_TOUTSEL                 (WDT_TIMEOUT_2POW10)
#define MIN_CYCLES                  (1024)


/* Macros to convert the value between the timeout interval and the soft time iterations. */
#define ROUND_TO_INTEGER(value)         ((int)(((value) * 10 + 5) / 10))
#define CONV_SEC_TO_IT(hz, secs)        (ROUND_TO_INTEGER((float)((secs) * (hz)) / (float)(MIN_CYCLES)))
#define CONV_IT_TO_SEC(hz, iterations)  (ROUND_TO_INTEGER((float)((iterations) * (MIN_CYCLES)) / (float)(hz)))


/* Private typedef --------------------------------------------------------------*/
struct soft_time_handle
{
    int clock_hz;
    int wanted_sec;
    int report_sec;
    int left_iterations;
    int full_iterations;
    rt_bool_t expired;
    rt_bool_t feed_dog;
};

typedef volatile struct soft_time_handle soft_time_handle_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t wdt_init(rt_watchdog_t *dev);
static rt_err_t wdt_control(rt_watchdog_t *dev, int cmd, void *args);
static uint32_t wdt_get_module_clock(void);
static uint32_t wdt_get_working_hz(void);
static void soft_time_init(soft_time_handle_t *const soft_time);
static void soft_time_setup(uint32_t wanted_sec, uint32_t hz, soft_time_handle_t *const soft_time);
static void soft_time_feed_dog(soft_time_handle_t *const soft_time);

#if defined(RT_USING_PM)
    static int wdt_pm_suspend(const struct rt_device *device, rt_uint8_t mode);
    static void wdt_pm_resume(const struct rt_device *device, rt_uint8_t mode);
    static int wdt_pm_frequency_change(const struct rt_device *device, rt_uint8_t mode);
    static void soft_time_freqeucy_change(uint32_t new_hz, soft_time_handle_t *const soft_time);
#endif

/* Public functions -------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static struct soft_time_handle soft_time;
static struct rt_watchdog_device device_wdt;
static struct rt_watchdog_ops ops_wdt =
{
    .init = wdt_init,
    .control = wdt_control,
};

#if defined(RT_USING_PM)

static struct rt_device_pm_ops device_pm_ops =
{
    .suspend = wdt_pm_suspend,
    .resume = wdt_pm_resume,
    .frequency_change = wdt_pm_frequency_change
};
#endif


#if defined(RT_USING_PM)

/* device pm suspend() entry. */
static int wdt_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
    case PM_SLEEP_MODE_IDLE:
    case PM_SLEEP_MODE_STANDBY:
    case PM_SLEEP_MODE_SHUTDOWN:
        break;

    case PM_SLEEP_MODE_LIGHT:
    case PM_SLEEP_MODE_DEEP:
    {
        uint32_t u32RegLockBackup = SYS_IsRegLocked();
        SYS_UnlockReg();

        WDT->CTL &= ~WDT_CTL_WDTEN_Msk;

        if (u32RegLockBackup)
            SYS_LockReg();

        break;
    }
    default:
        break;
    }

    return (int)RT_EOK;
}


/* device pm resume() entry. */
static void wdt_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
    case PM_SLEEP_MODE_IDLE:
    case PM_SLEEP_MODE_STANDBY:
    case PM_SLEEP_MODE_SHUTDOWN:
        break;

    case PM_SLEEP_MODE_LIGHT:
    case PM_SLEEP_MODE_DEEP:
    {
        uint32_t u32RegLockBackup = SYS_IsRegLocked();
        SYS_UnlockReg();
        WDT->CTL |= WDT_CTL_WDTEN_Msk;

        if (u32RegLockBackup)
            SYS_LockReg();
    }
    break;

    default:
        break;
    }
}


/* device pm frequency_change() entry. */
static int wdt_pm_frequency_change(const struct rt_device *device, rt_uint8_t mode)
{
    uint32_t clk, new_hz;

    new_hz = wdt_get_working_hz();
    clk = wdt_get_module_clock();

    if (clk == CLK_CLKSEL1_WDTSEL_HCLK_DIV2048)
    {
        if (new_hz == soft_time.clock_hz)
            return (int)(RT_EOK);

        /* frequency change occurs in critical section */
        soft_time_freqeucy_change(new_hz, &soft_time);
    }

    return (int)(RT_EOK);
}


static void soft_time_freqeucy_change(uint32_t new_hz, soft_time_handle_t *const soft_time)
{
    rt_base_t level;
    soft_time_handle_t new_time;
    rt_bool_t corner_case = RT_FALSE;

    level = rt_hw_interrupt_disable();

    new_time.clock_hz = new_hz;
    new_time.feed_dog = soft_time->feed_dog;
    new_time.expired = soft_time->expired;
    new_time.wanted_sec = soft_time->wanted_sec;
    new_time.full_iterations = CONV_SEC_TO_IT(new_hz, soft_time->wanted_sec);
    new_time.report_sec = CONV_IT_TO_SEC(new_hz, new_time.full_iterations);

    new_time.left_iterations = ROUND_TO_INTEGER((float)soft_time->left_iterations *
                               (float)new_hz / (float)soft_time->clock_hz);

    if ((new_time.left_iterations == 0) && (soft_time->left_iterations > 0))
    {
        new_time.left_iterations++;;
        corner_case = RT_TRUE;
    }

    *soft_time = new_time;
    rt_hw_interrupt_enable(level);

    if (corner_case)
    {
        LOG_W("pm frequency change cause wdt internal left iterations convert to 0.\n\r  \
               wdt driver will add another 1 iteration for this corner case.");
    }
}
#endif


static void hw_wdt_init(void)
{
    uint32_t u32RegLockBackup = SYS_IsRegLocked();
    SYS_UnlockReg();

    if (WDT_GET_RESET_FLAG())
    {
        LOG_W("System re-boots from watchdog timer reset.\n");
        WDT_CLEAR_RESET_FLAG();
    }

    if (u32RegLockBackup)
        SYS_LockReg();

    NVIC_EnableIRQ(WDT_IRQn);
}


/* wdt device driver initialize. */
int rt_hw_wdt_init(void)
{
    rt_err_t ret;

    hw_wdt_init();

    device_wdt.ops = &ops_wdt;
    ret = rt_hw_watchdog_register(&device_wdt, "wdt", RT_DEVICE_FLAG_RDWR, RT_NULL);

#if defined(RT_USING_PM)

    rt_pm_device_register((struct rt_device *)&device_wdt, &device_pm_ops);
#endif

    return (int)ret;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);


/* Register rt-thread device.init() entry. */
static rt_err_t wdt_init(rt_watchdog_t *dev)
{
    soft_time_init(&soft_time);
    hw_wdt_init();

    return RT_EOK;
}


static uint32_t wdt_get_module_clock(void)
{
    return (CLK_GetModuleClockSource(WDT_MODULE) << CLK_CLKSEL1_WDTSEL_Pos);
}


static uint32_t wdt_get_working_hz(void)
{
    uint32_t clk, hz = 0;

    clk = wdt_get_module_clock();

    switch (clk)
    {
    case CLK_CLKSEL1_WDTSEL_LIRC:
        hz = __LIRC;
        break;

    case CLK_CLKSEL1_WDTSEL_LXT:
        hz = __LXT;
        break;

    case CLK_CLKSEL1_WDTSEL_HCLK_DIV2048:
        hz = CLK_GetHCLKFreq() / 2048;
        break;

    default:
        break;
    }

    return hz;
}


static void soft_time_init(soft_time_handle_t *const soft_time)
{
    rt_memset((void *)soft_time, 0, sizeof(struct soft_time_handle));

}


static void soft_time_setup(uint32_t wanted_sec, uint32_t hz, soft_time_handle_t *const soft_time)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    soft_time->expired = RT_FALSE;
    soft_time->feed_dog = RT_FALSE;
    soft_time->wanted_sec = wanted_sec;
    soft_time->full_iterations = CONV_SEC_TO_IT(hz, wanted_sec);
    soft_time->left_iterations = soft_time->full_iterations;
    soft_time->report_sec = CONV_IT_TO_SEC(hz, soft_time->full_iterations);
    soft_time->clock_hz = hz;

    rt_hw_interrupt_enable(level);
}


static void soft_time_feed_dog(soft_time_handle_t *const soft_time)
{
    soft_time->feed_dog = RT_TRUE;
}


/* Register rt-thread device.control() entry. */
static rt_err_t wdt_control(rt_watchdog_t *dev, int cmd, void *args)
{
    uint32_t wanted_sec, hz;
    uint32_t *buf;
    rt_err_t ret = RT_EOK;
    uint32_t u32RegLockBackup;

    if (dev == NULL)
        return -(RT_EINVAL);

    u32RegLockBackup = SYS_IsRegLocked();

    SYS_UnlockReg();

    hz = wdt_get_working_hz();

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:

        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
            break;
        }

        buf = (uint32_t *)args;
        *buf = soft_time.report_sec;
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:

        wanted_sec = *((uint32_t *)args);

        if (wanted_sec == 0)
        {
            ret = -RT_EINVAL;
            break;
        }

        soft_time_setup(wanted_sec, hz, &soft_time);
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:

        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
            break;
        }

        buf = (uint32_t *)args;
        *buf = CONV_IT_TO_SEC(hz, soft_time.left_iterations);
        break;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:

        /* Make a mark that the application has fed the watchdog. */
        soft_time_feed_dog(&soft_time);
        break;

    case RT_DEVICE_CTRL_WDT_START:

        WDT_RESET_COUNTER();
        WDT_Open(MIN_TOUTSEL, WDT_RESET_DELAY_1026CLK, TRUE, TRUE);
        WDT_EnableInt();
        break;

    case RT_DEVICE_CTRL_WDT_STOP:

        WDT_Close();
        break;

    default:
        ret = RT_ERROR;
    }

    if (u32RegLockBackup)
        SYS_LockReg();

    return -(ret);
}


/* wdt interrupt entry */
void WDT_IRQHandler(void)
{
    rt_interrupt_enter();

    /* Clear wdt interrupt flag */
    if (WDT_GET_TIMEOUT_INT_FLAG())
    {
        WDT_CLEAR_TIMEOUT_INT_FLAG();
    }

    /* Clear wdt wakeup flag */
    if (WDT_GET_TIMEOUT_WAKEUP_FLAG())
    {
        WDT_CLEAR_TIMEOUT_WAKEUP_FLAG();
    }

    /* The soft time has not reached the configured timeout yet. Clear the wdt counter
       any way to prevent the system from hardware wdt reset. */
    if (soft_time.left_iterations-- > 0)
    {
        WDT_RESET_COUNTER();
    }

    /* The soft time reaches the configured timeout boundary. Clear the wdt
       counter if he application has fed the dog at least once until now. */
    else
    {
        if ((soft_time.feed_dog) && (!soft_time.expired))
        {
            WDT_RESET_COUNTER();
            soft_time.feed_dog =  RT_FALSE;
            soft_time.left_iterations = soft_time.full_iterations;
        }
        else
        {
            /* Application does not feed the dog in time. */
            soft_time.expired = RT_TRUE;
        }
    }

    rt_interrupt_leave();
}

#endif /* BSP_USING_WDT */


