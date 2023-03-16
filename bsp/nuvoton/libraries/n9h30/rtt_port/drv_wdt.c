/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_WDT)

#include <rthw.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "NuMicro.h"
#include <drv_sys.h>

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
static uint32_t wdt_get_working_hz(void);
static void soft_time_init(soft_time_handle_t *const soft_time);
static void soft_time_setup(uint32_t wanted_sec, uint32_t hz, soft_time_handle_t *const soft_time);
static void soft_time_feed_dog(soft_time_handle_t *const soft_time);
static void nu_wdt_isr(int vector, void *param);

/* Public functions -------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static struct soft_time_handle soft_time;
static struct rt_watchdog_device device_wdt;
static struct rt_watchdog_ops ops_wdt =
{
    .init = wdt_init,
    .control = wdt_control,
};

static void hw_wdt_init(void)
{
    nu_sys_ipclk_enable(WDTCKEN);

    rt_hw_interrupt_install(IRQ_WDT, nu_wdt_isr, &device_wdt, "wdt");
    rt_hw_interrupt_umask(IRQ_WDT);
}


/* wdt device driver initialize. */
int rt_hw_wdt_init(void)
{
    rt_err_t ret;

    hw_wdt_init();

    device_wdt.ops = &ops_wdt;
    ret = rt_hw_watchdog_register(&device_wdt, "wdt", RT_DEVICE_FLAG_RDWR, RT_NULL);

    return (int)ret;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);


/* Register rt-thread device.init() entry. */
static rt_err_t wdt_init(rt_watchdog_t *dev)
{
    soft_time_init(&soft_time);

    return RT_EOK;
}


static uint32_t wdt_get_working_hz(void)
{
    static uint32_t u32ClkTbl[4] = {12000000, 12000000 / 128, 0, 32768};
    uint32_t u32WDT_S = (inpw(REG_CLK_DIVCTL8) & (0x3 << 8)) >> 8;
    uint32_t clk = 0;

    switch (u32WDT_S)
    {
    case 0: // XIN Hz
    case 1: // XIN/128 Hz
    case 3: // 32.768 Hz
        clk = u32ClkTbl[u32WDT_S];
        break;

    case 2: // PCLK/4096 Hz
        clk = sysGetClock(SYS_PCLK) * 1000000 / 4096;
        break;

    default:
        break;
    }

    return clk;
}



static void soft_time_init(soft_time_handle_t *const soft_time)
{
    rt_memset((void *)soft_time, 0, sizeof(struct soft_time_handle));

}


static void soft_time_setup(uint32_t wanted_sec, uint32_t hz, soft_time_handle_t *const soft_time)
{
    rt_base_t level = rt_hw_interrupt_disable();

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

    if (dev == NULL)
        return -(RT_EINVAL);

    hz = wdt_get_working_hz();

    SYS_UnlockReg();

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

    SYS_LockReg();

    return -(ret);
}


/* wdt interrupt entry */
static void nu_wdt_isr(int vector, void *param)
{
    /* Clear wdt interrupt flag */
    if (WDT_GET_TIMEOUT_INT_FLAG())
    {
        WDT_CLEAR_TIMEOUT_INT_FLAG();
    }

    SYS_UnlockReg();

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

    SYS_LockReg();
}

#endif /* BSP_USING_WDT */


