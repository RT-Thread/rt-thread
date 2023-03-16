/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-3-25       Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_WDT)

#include <rthw.h>
#include <rtdevice.h>
#include "NuMicro.h"

#define LOG_TAG    "drv.wdt"
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL   LOG_LVL_ERROR
#define DBG_COLOR
#include <rtdbg.h>

/* Private define ---------------------------------------------------------------*/
enum
{
    WDT_START = -1,
#if defined(BSP_USING_WDT0)
    WDT0_IDX,
#endif
#if defined(BSP_USING_WDT1)
    WDT1_IDX,
#endif
#if defined(BSP_USING_WDT2)
    WDT2_IDX,
#endif
    WDT_CNT
};

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

struct nu_wdt
{
    struct rt_watchdog_device parent;
    char *name;
    WDT_T *base;
    IRQn_Type irqn;
    uint32_t modid;
    struct soft_time_handle soft_time;
};
typedef struct nu_wdt *nu_wdt_t;

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_wdt_init(rt_watchdog_t *dev);
static rt_err_t nu_wdt_control(rt_watchdog_t *dev, int cmd, void *args);
static uint32_t nu_wdt_get_module_clock(nu_wdt_t);
static uint32_t nu_wdt_get_working_hz(nu_wdt_t);
static void soft_time_init(soft_time_handle_t *const soft_time);
static void soft_time_setup(uint32_t wanted_sec, uint32_t hz, soft_time_handle_t *const soft_time);
static void soft_time_feed_dog(soft_time_handle_t *const soft_time);
static void nu_wdt_isr(int vector, void *param);
/* Public functions -------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static struct nu_wdt nu_wdt_arr [] =
{
#if defined(BSP_USING_WDT0)
    { .name = "wdt0", .base = WDT0, .irqn = WDT0_IRQn, .modid = WDT0_MODULE },
#endif
#if defined(BSP_USING_WDT1)
    { .name = "wdt1", .base = WDT1, .irqn = WDT1_IRQn, .modid = WDT1_MODULE },
#endif
#if defined(BSP_USING_WDT2)
    { .name = "wdt2", .base = WDT2, .irqn = WDT2_IRQn, .modid = WDT2_MODULE },
#endif
};

static struct rt_watchdog_ops ops_wdt =
{
    .init = nu_wdt_init,
    .control = nu_wdt_control,
};


/* wdt device driver initialize. */
int rt_hw_wdt_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (WDT_START + 1); i < WDT_CNT; i++)
    {
        nu_wdt_t psNuWdt = &nu_wdt_arr[i];

        if (WDT_GET_RESET_FLAG(psNuWdt->base))
        {
            LOG_W("%s: System re-boots from watchdog timer reset.\n", psNuWdt->name);
            WDT_CLEAR_RESET_FLAG(psNuWdt->base);
        }

        psNuWdt->parent.ops = &ops_wdt;
        ret = rt_hw_watchdog_register(&psNuWdt->parent, psNuWdt->name, RT_DEVICE_FLAG_RDWR, psNuWdt);
        RT_ASSERT(ret == RT_EOK);

        rt_hw_interrupt_install(psNuWdt->irqn, nu_wdt_isr, psNuWdt, psNuWdt->name);
        rt_hw_interrupt_umask(psNuWdt->irqn);
    }

    return (int)ret;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);


/* Register rt-thread device.init() entry. */
static rt_err_t nu_wdt_init(rt_watchdog_t *dev)
{
    nu_wdt_t psNuWdt = (nu_wdt_t)dev;
    RT_ASSERT(dev != RT_NULL);

    soft_time_init(&psNuWdt->soft_time);

    return RT_EOK;
}


static uint32_t nu_wdt_get_module_clock(nu_wdt_t psNuWdt)
{
    uint32_t ret = 0;
    switch (psNuWdt->modid)
    {
    case WDT0_MODULE:
    case WDT1_MODULE:
    case WDT2_MODULE:
        ret =  CLK_GetModuleClockSource(psNuWdt->modid);
        break;

    default:
        break;
    }

    return ret;
}


static uint32_t nu_wdt_get_working_hz(nu_wdt_t psNuWdt)
{
    uint32_t src_clk, hz = 0;

    src_clk = nu_wdt_get_module_clock(psNuWdt);

    switch (src_clk)
    {
    case 1: /* CLK_CLKSEL3_WDT0SEL_LXT */
        hz = __LXT;
        break;

    case 2: /* CLK_CLKSEL3_WDT0SEL_PCLK3_DIV4096 */
        hz = CLK_GetPCLK3Freq() / 4096;
        break;

    case 3: /* CLK_CLKSEL3_WDT0SEL_LIRC */
        hz = __LIRC;
        break;

    default:
        break;
    }

    LOG_D("[%s] modid=%x src_clk=%d src_hz=%d\n", psNuWdt->name, psNuWdt->modid, src_clk, hz);

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

    LOG_D("wanted_sec=%d\n", soft_time->wanted_sec);
    LOG_D("full_iterations=%d\n", soft_time->full_iterations);
    LOG_D("left_iterations=%d\n", soft_time->left_iterations);
    LOG_D("report_sec=%d\n", soft_time->report_sec);
    LOG_D("clock_hz=%d\n", soft_time->clock_hz);

}


static void soft_time_feed_dog(soft_time_handle_t *const soft_time)
{
    soft_time->feed_dog = RT_TRUE;
}


/* Register rt-thread device.control() entry. */
static rt_err_t nu_wdt_control(rt_watchdog_t *dev, int cmd, void *args)
{
    uint32_t wanted_sec, hz;
    rt_err_t ret = RT_EOK;

    nu_wdt_t psNuWdt = (nu_wdt_t)dev;
    RT_ASSERT(dev);

    //SYS_UnlockReg();

    hz = nu_wdt_get_working_hz(psNuWdt);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:

        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
            break;
        }

        *((uint32_t *)args) = psNuWdt->soft_time.report_sec;
        LOG_D("[GET]report_sec=%d\n", psNuWdt->soft_time.report_sec);
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:

        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
            break;
        }

        wanted_sec = *((uint32_t *)args);

        if (wanted_sec == 0)
        {
            ret = -RT_EINVAL;
            break;
        }

        soft_time_setup(wanted_sec, hz, &psNuWdt->soft_time);
        LOG_D("[SET]report_sec=%d\n", psNuWdt->soft_time.report_sec);
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:

        if (args == RT_NULL)
        {
            ret = -RT_EINVAL;
            break;
        }

        *((uint32_t *)args) = CONV_IT_TO_SEC(hz, psNuWdt->soft_time.left_iterations);
        break;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:

        /* Make a mark that the application has fed the watchdog. */
        soft_time_feed_dog(&psNuWdt->soft_time);
        break;

    case RT_DEVICE_CTRL_WDT_START:

        WDT_RESET_COUNTER(psNuWdt->base);
        WDT_Open(psNuWdt->base, MIN_TOUTSEL, WDT_RESET_DELAY_1026CLK, TRUE, TRUE);
        WDT_EnableInt(psNuWdt->base);
        break;

    case RT_DEVICE_CTRL_WDT_STOP:

        WDT_Close(psNuWdt->base);
        break;

    default:
        ret = RT_ERROR;
    }

    //SYS_LockReg();

    return -(ret);
}


/* wdt interrupt entry */
static void nu_wdt_isr(int vector, void *param)
{
    nu_wdt_t psNuWdt = (nu_wdt_t)param;
    RT_ASSERT(param != RT_NULL);

    /* Clear wdt interrupt flag */
    if (WDT_GET_TIMEOUT_INT_FLAG(psNuWdt->base))
    {
        WDT_CLEAR_TIMEOUT_INT_FLAG(psNuWdt->base);
    }

    /* Clear wdt wakeup flag */
    if (WDT_GET_TIMEOUT_WAKEUP_FLAG(psNuWdt->base))
    {
        WDT_CLEAR_TIMEOUT_WAKEUP_FLAG(psNuWdt->base);
    }

    /* The soft time has not reached the configured timeout yet. Clear the wdt counter
       any way to prevent the system from hardware wdt reset. */
    if (psNuWdt->soft_time.left_iterations-- > 0)
    {
        WDT_RESET_COUNTER(psNuWdt->base);
    }

    /* The soft time reaches the configured timeout boundary. Clear the wdt
       counter if he application has fed the dog at least once until now. */
    else
    {
        if ((psNuWdt->soft_time.feed_dog) && (!psNuWdt->soft_time.expired))
        {
            WDT_RESET_COUNTER(psNuWdt->base);
            psNuWdt->soft_time.feed_dog =  RT_FALSE;
            psNuWdt->soft_time.left_iterations = psNuWdt->soft_time.full_iterations;
        }
        else
        {
            /* Application does not feed the dog in time. */
            psNuWdt->soft_time.expired = RT_TRUE;
        }
    }
}

#endif /* BSP_USING_WDT */


