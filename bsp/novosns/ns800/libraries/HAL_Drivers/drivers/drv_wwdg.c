/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-05-13     Jeffery Yuan      first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_wwdg.h"
#include "wwdg.h"

#ifdef RT_USING_WDT
#ifdef BSP_USING_WWDG

#define DBG_TAG    "drv.wwdg"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifndef HCLK_FREQ_HZ
#define HCLK_FREQ_HZ           200000000ULL
#endif

#define NS800_WWDG_COUNTER_MIN 0x40U
#define NS800_WWDG_COUNTER_MAX 0x7FU
#define NS800_WWDG_TICK_BASE   4096ULL
#define NS800_USEC_PER_SEC     1000000ULL
#define NS800_MSEC_PER_SEC     1000ULL
#define NS800_ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

struct ns800_wwdg
{
    rt_watchdog_t watchdog;
    WWDG_TypeDef *base;
    WWDG_Prescaler prescaler;
    rt_uint8_t reload;
    rt_uint8_t window;
    rt_uint64_t timeout_us;
    rt_bool_t started;
    rt_bool_t early_wakeup_irq;
};

static struct ns800_wwdg wwdg_dev;

static const rt_uint8_t wwdg_prescaler_div[] =
{
    1U, 2U, 4U, 8U, 16U, 32U, 64U, 128U,
};

static rt_uint64_t wwdg_abs_diff_u64(rt_uint64_t a, rt_uint64_t b)
{
    return (a > b) ? (a - b) : (b - a);
}

static rt_uint64_t wwdg_calc_timeout_us(rt_uint32_t div, rt_uint32_t reload)
{
    rt_uint32_t ticks = reload - (NS800_WWDG_COUNTER_MIN - 1U);

    return ((rt_uint64_t)ticks * NS800_WWDG_TICK_BASE * div * NS800_USEC_PER_SEC +
            HCLK_FREQ_HZ / 2ULL) / HCLK_FREQ_HZ;
}

static rt_uint32_t wwdg_timeout_to_ms(rt_uint64_t timeout_us)
{
    return (rt_uint32_t)((timeout_us + NS800_MSEC_PER_SEC - 1ULL) / NS800_MSEC_PER_SEC);
}

static void wwdg_select_config(rt_uint32_t timeout_s, struct ns800_wwdg *dev)
{
    rt_uint64_t target_us = (rt_uint64_t)timeout_s * NS800_USEC_PER_SEC;
    rt_uint64_t best_diff = (rt_uint64_t)-1;
    rt_uint32_t best_prescaler = 0;
    rt_uint32_t best_reload = NS800_WWDG_COUNTER_MAX;
    rt_uint32_t psc;

    if (target_us == 0)
    {
        target_us = wwdg_calc_timeout_us(wwdg_prescaler_div[0], NS800_WWDG_COUNTER_MIN);
    }

    for (psc = 0; psc < NS800_ARRAY_SIZE(wwdg_prescaler_div); psc++)
    {
        rt_uint64_t tick_us = (NS800_WWDG_TICK_BASE * wwdg_prescaler_div[psc] * NS800_USEC_PER_SEC +
                               HCLK_FREQ_HZ / 2ULL) / HCLK_FREQ_HZ;
        rt_uint64_t ticks;
        rt_uint32_t reload;
        rt_uint64_t actual_us;
        rt_uint64_t diff;

        if (tick_us == 0)
        {
            tick_us = 1;
        }

        ticks = (target_us + tick_us / 2ULL) / tick_us;
        if (ticks == 0)
        {
            ticks = 1;
        }

        if (ticks > 64ULL)
        {
            ticks = 64ULL;
        }

        reload = (rt_uint32_t)(ticks + (NS800_WWDG_COUNTER_MIN - 1U));
        actual_us = wwdg_calc_timeout_us(wwdg_prescaler_div[psc], reload);
        diff = wwdg_abs_diff_u64(actual_us, target_us);
        if (diff < best_diff)
        {
            best_diff = diff;
            best_prescaler = psc;
            best_reload = reload;
            dev->timeout_us = actual_us;
        }
    }

    dev->prescaler = (WWDG_Prescaler)best_prescaler;
    dev->reload = (rt_uint8_t)best_reload;
    dev->window = (rt_uint8_t)best_reload;
}

static void wwdg_apply_config(struct ns800_wwdg *dev)
{
    WWDG_configModule(dev->base,
                      dev->early_wakeup_irq ? WWDG_EARLY_WAKEUP_INT : WWDG_DIRECT_RESET,
                      dev->prescaler,
                      dev->window);
}

void wwdg_isr(void)
{
    rt_interrupt_enter();
    if (WWDG_getIntStatus(wwdg_dev.base))
    {
        WWDG_refreshModule(wwdg_dev.base, wwdg_dev.reload);
        WWDG_clearIntStatus(wwdg_dev.base);
        while (WWDG_getIntStatus(wwdg_dev.base))
        {
            ;
        }
    }
    rt_interrupt_leave();
}

static rt_err_t wwdg_init(rt_watchdog_t *wdt)
{
    RT_UNUSED(wdt);
    return RT_EOK;
}

static rt_err_t wwdg_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    struct ns800_wwdg *dev;

    RT_ASSERT(wdt != RT_NULL);
    dev = (struct ns800_wwdg *)wdt->parent.user_data;
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        WWDG_refreshModule(dev->base, dev->reload);
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        if (arg == RT_NULL)
        {
            return -RT_EINVAL;
        }
        wwdg_select_config(*(rt_uint32_t *)arg, dev);
        if (dev->started)
        {
            wwdg_apply_config(dev);
            WWDG_refreshModule(dev->base, dev->reload);
        }
        LOG_W("%s timeout request=%u s actual=%u ms",
              WWDG_DEVICE_NAME,
              *(rt_uint32_t *)arg,
              wwdg_timeout_to_ms(dev->timeout_us));
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        if (arg == RT_NULL)
        {
            return -RT_EINVAL;
        }
        *(rt_uint32_t *)arg = (rt_uint32_t)((dev->timeout_us + NS800_USEC_PER_SEC - 1ULL) / NS800_USEC_PER_SEC);
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        return -RT_ENOSYS;

    case RT_DEVICE_CTRL_WDT_START:
        if (!dev->started)
        {
            wwdg_apply_config(dev);
            WWDG_clearIntStatus(dev->base);
            WWDG_enableModule(dev->base, dev->reload);
            dev->started = RT_TRUE;
            LOG_I("%s started, timeout=%u ms", WWDG_DEVICE_NAME, wwdg_timeout_to_ms(dev->timeout_us));
        }
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        return -RT_ENOSYS;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static const struct rt_watchdog_ops wwdg_ops =
{
    .init = wwdg_init,
    .control = wwdg_control,
};

int rt_hw_wwdg_init(void)
{
    wwdg_dev.base = WWDG;
    wwdg_dev.started = RT_FALSE;
    wwdg_dev.early_wakeup_irq = RT_FALSE;
    wwdg_select_config(1U, &wwdg_dev);
    wwdg_dev.watchdog.ops = &wwdg_ops;

    if (rt_hw_watchdog_register(&wwdg_dev.watchdog,
                                WWDG_DEVICE_NAME,
                                RT_DEVICE_FLAG_DEACTIVATE,
                                &wwdg_dev) != RT_EOK)
    {
        LOG_E("%s register failed", WWDG_DEVICE_NAME);
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_wwdg_init);

#endif /* BSP_USING_WWDG */
#endif /* RT_USING_WDT */

