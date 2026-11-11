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
#include "drv_iwdg.h"

#ifdef BSP_USING_IWDG1
#include "iwdg1.h"
#endif

#ifdef BSP_USING_IWDG2
#include "iwdg2.h"
#endif

#if defined(RT_USING_WDT) && (defined(BSP_USING_IWDG1) || defined(BSP_USING_IWDG2))

#define DBG_TAG    "drv.iwdg"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define NS800_USEC_PER_SEC        1000000ULL
#define NS800_MSEC_PER_SEC        1000ULL
#define NS800_IWDG1_CLK_HZ        10000000ULL
#define NS800_IWDG2_CLK_HZ        128000ULL
#define NS800_ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))

enum ns800_iwdg_id
{
    NS800_IWDG1 = 0,
    NS800_IWDG2,
};

struct ns800_iwdg
{
    rt_watchdog_t watchdog;
    enum ns800_iwdg_id id;
    const char *name;
    void *base;
    rt_bool_t started;
    rt_uint64_t timeout_us;
    union
    {
#ifdef BSP_USING_IWDG1
        struct
        {
            IWDG1_Prescaler prescaler;
            IWDG1_Timeout timeout;
        } iwdg1;
#endif
#ifdef BSP_USING_IWDG2
        struct
        {
            IWDG2_Prescaler prescaler;
            rt_uint16_t reload;
        } iwdg2;
#endif
    } hw;
};

static rt_uint64_t ns800_abs_diff_u64(rt_uint64_t a, rt_uint64_t b)
{
    return (a > b) ? (a - b) : (b - a);
}

static rt_uint32_t ns800_timeout_to_seconds(rt_uint64_t timeout_us)
{
    return (rt_uint32_t)((timeout_us + NS800_USEC_PER_SEC - 1ULL) / NS800_USEC_PER_SEC);
}

static rt_uint32_t ns800_timeout_to_ms(rt_uint64_t timeout_us)
{
    return (rt_uint32_t)((timeout_us + NS800_MSEC_PER_SEC - 1ULL) / NS800_MSEC_PER_SEC);
}

#ifdef BSP_USING_IWDG1

static struct ns800_iwdg iwdg1_dev;

static const rt_uint8_t iwdg1_prescaler_code[] =
{
    IWDG1_PRESCALE_DIV1,
    IWDG1_PRESCALE_DIV2,
    IWDG1_PRESCALE_DIV4,
    IWDG1_PRESCALE_DIV8,
    IWDG1_PRESCALE_DIV16,
    IWDG1_PRESCALE_DIV32,
    IWDG1_PRESCALE_DIV128,
    IWDG1_PRESCALE_DIV256,
    IWDG1_PRESCALE_DIV512,
    IWDG1_PRESCALE_DIV1024,
    IWDG1_PRESCALE_DIV2048,
    IWDG1_PRESCALE_DIV4096,
    IWDG1_PRESCALE_DIV8192,
    IWDG1_PRESCALE_DIV64,
};

static const rt_uint32_t iwdg1_prescaler_div[] =
{
    1U, 2U, 4U, 8U, 16U, 32U, 128U, 256U, 512U, 1024U, 2048U, 4096U, 8192U, 64U,
};

static const rt_uint16_t iwdg1_timeout_count[] =
{
    1024U, 4096U, 8192U, 16384U,
};

static rt_uint64_t iwdg1_calc_timeout_us(rt_uint32_t div, rt_uint32_t count)
{
    return ((rt_uint64_t)count * div * NS800_USEC_PER_SEC + NS800_IWDG1_CLK_HZ / 2ULL) / NS800_IWDG1_CLK_HZ;
}

static void iwdg1_select_config(rt_uint32_t timeout_s, struct ns800_iwdg *dev)
{
    rt_uint64_t target_us = (rt_uint64_t)timeout_s * NS800_USEC_PER_SEC;
    rt_uint64_t best_diff = (rt_uint64_t)-1;
    rt_uint32_t best_prescaler = 0;
    rt_uint32_t best_timeout = 0;
    rt_uint32_t psc;
    rt_uint32_t top;

    if (target_us == 0)
    {
        target_us = iwdg1_calc_timeout_us(iwdg1_prescaler_div[0], iwdg1_timeout_count[0]);
    }

    for (psc = 0; psc < NS800_ARRAY_SIZE(iwdg1_prescaler_code); psc++)
    {
        for (top = 0; top < NS800_ARRAY_SIZE(iwdg1_timeout_count); top++)
        {
            rt_uint64_t actual_us = iwdg1_calc_timeout_us(iwdg1_prescaler_div[psc], iwdg1_timeout_count[top]);
            rt_uint64_t diff = ns800_abs_diff_u64(actual_us, target_us);

            if (diff < best_diff)
            {
                best_diff = diff;
                best_prescaler = psc;
                best_timeout = top;
                dev->timeout_us = actual_us;
            }
        }
    }

    dev->hw.iwdg1.prescaler = (IWDG1_Prescaler)iwdg1_prescaler_code[best_prescaler];
    dev->hw.iwdg1.timeout = (IWDG1_Timeout)best_timeout;
}

static void iwdg1_apply_config(struct ns800_iwdg *dev)
{
    IWDG1_configModule((IWDG1_TypeDef *)dev->base,
                       RESET_EN,
                       LPRUN,
                       dev->hw.iwdg1.prescaler,
                       HEAD_PERCENT100,
                       END_PERCENT0,
                       dev->hw.iwdg1.timeout);
    IWDG1_clearErrorStatus((IWDG1_TypeDef *)dev->base);
    IWDG1_clearIntStatus((IWDG1_TypeDef *)dev->base);
}

void IWDG1_Handler(void)
{
    rt_interrupt_enter();
    IWDG1_clearErrorStatus((IWDG1_TypeDef *)iwdg1_dev.base);
    IWDG1_clearIntStatus((IWDG1_TypeDef *)iwdg1_dev.base);
    while (IWDG1_getIntStatus((IWDG1_TypeDef *)iwdg1_dev.base))
    {
        ;
    }
    IWDG1_enableModule((IWDG1_TypeDef *)iwdg1_dev.base);
    rt_interrupt_leave();
}

#endif /* BSP_USING_IWDG1 */

#ifdef BSP_USING_IWDG2

static struct ns800_iwdg iwdg2_dev;

static const rt_uint8_t iwdg2_prescaler_code[] =
{
    IWDG2_PRESCALE_DIV128,
    IWDG2_PRESCALE_DIV2048,
    IWDG2_PRESCALE_DIV1024,
    IWDG2_PRESCALE_DIV512,
    IWDG2_PRESCALE_DIV256,
    IWDG2_PRESCALE_DIV64,
    IWDG2_PRESCALE_DIV32,
    IWDG2_PRESCALE_DIV16,
    IWDG2_PRESCALE_DIV8,
    IWDG2_PRESCALE_DIV4,
};

static const rt_uint32_t iwdg2_prescaler_div[] =
{
    128U, 2048U, 1024U, 512U, 256U, 64U, 32U, 16U, 8U, 4U,
};

static rt_uint64_t iwdg2_calc_timeout_us(rt_uint32_t div, rt_uint32_t reload)
{
    return ((rt_uint64_t)(reload + 1U) * div * NS800_USEC_PER_SEC + NS800_IWDG2_CLK_HZ / 2ULL) / NS800_IWDG2_CLK_HZ;
}

static void iwdg2_select_config(rt_uint32_t timeout_s, struct ns800_iwdg *dev)
{
    rt_uint64_t target_us = (rt_uint64_t)timeout_s * NS800_USEC_PER_SEC;
    rt_uint64_t best_diff = (rt_uint64_t)-1;
    rt_uint32_t best_prescaler = 0;
    rt_uint32_t best_reload = 0;
    rt_uint32_t psc;

    if (target_us == 0)
    {
        target_us = iwdg2_calc_timeout_us(iwdg2_prescaler_div[NS800_ARRAY_SIZE(iwdg2_prescaler_div) - 1], 0U);
    }

    for (psc = 0; psc < NS800_ARRAY_SIZE(iwdg2_prescaler_code); psc++)
    {
        rt_uint64_t ticks;
        rt_uint64_t actual_us;
        rt_uint64_t diff;
        rt_uint64_t tick_us = ((rt_uint64_t)iwdg2_prescaler_div[psc] * NS800_USEC_PER_SEC +
                               NS800_IWDG2_CLK_HZ / 2ULL) / NS800_IWDG2_CLK_HZ;

        if (tick_us == 0)
        {
            tick_us = 1;
        }

        ticks = (target_us + tick_us / 2ULL) / tick_us;
        if (ticks == 0)
        {
            ticks = 1;
        }

        if (ticks > 4096ULL)
        {
            ticks = 4096ULL;
        }

        actual_us = iwdg2_calc_timeout_us(iwdg2_prescaler_div[psc], (rt_uint32_t)(ticks - 1ULL));
        diff = ns800_abs_diff_u64(actual_us, target_us);
        if (diff < best_diff)
        {
            best_diff = diff;
            best_prescaler = psc;
            best_reload = (rt_uint32_t)(ticks - 1ULL);
            dev->timeout_us = actual_us;
        }
    }

    dev->hw.iwdg2.prescaler = (IWDG2_Prescaler)iwdg2_prescaler_code[best_prescaler];
    dev->hw.iwdg2.reload = (rt_uint16_t)best_reload;
}

static rt_err_t iwdg2_apply_config(struct ns800_iwdg *dev)
{
    if (!IWDG2_configModule((IWDG2_TypeDef *)dev->base,
                            RESET_SEL,
                            dev->hw.iwdg2.prescaler,
                            dev->hw.iwdg2.reload))
    {
        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}

void IWDG2_Handler(void)
{
    rt_interrupt_enter();
    if (IWDG2_getIntStatus((IWDG2_TypeDef *)iwdg2_dev.base))
    {
        IWDG2_clearIntStatus((IWDG2_TypeDef *)iwdg2_dev.base);
        while (IWDG2_getIntStatus((IWDG2_TypeDef *)iwdg2_dev.base))
        {
            ;
        }
    }
    rt_interrupt_leave();
}

#endif /* BSP_USING_IWDG2 */

static rt_err_t ns800_iwdg_init(rt_watchdog_t *wdt)
{
    RT_UNUSED(wdt);
    return RT_EOK;
}

static rt_err_t ns800_iwdg_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    struct ns800_iwdg *dev;

    RT_ASSERT(wdt != RT_NULL);
    dev = (struct ns800_iwdg *)wdt->parent.user_data;
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
#ifdef BSP_USING_IWDG1
        if (dev->id == NS800_IWDG1)
        {
            IWDG1_refreshModule((IWDG1_TypeDef *)dev->base);
        }
#endif
#ifdef BSP_USING_IWDG2
        if (dev->id == NS800_IWDG2)
        {
            IWDG2_refreshModule((IWDG2_TypeDef *)dev->base);
        }
#endif
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        if (arg == RT_NULL)
        {
            return -RT_EINVAL;
        }
#ifdef BSP_USING_IWDG1
        if (dev->id == NS800_IWDG1)
        {
            if (dev->started)
            {
                LOG_W("%s timeout cannot be reconfigured after start", dev->name);
                return -RT_EBUSY;
            }
            iwdg1_select_config(*(rt_uint32_t *)arg, dev);
            LOG_I("%s timeout request=%u s actual=%u ms",
                  dev->name, *(rt_uint32_t *)arg, ns800_timeout_to_ms(dev->timeout_us));
        }
#endif
#ifdef BSP_USING_IWDG2
        if (dev->id == NS800_IWDG2)
        {
            rt_err_t ret;

            iwdg2_select_config(*(rt_uint32_t *)arg, dev);
            ret = iwdg2_apply_config(dev);
            if (ret != RT_EOK)
            {
                return ret;
            }

            if (dev->started)
            {
                IWDG2_refreshModule((IWDG2_TypeDef *)dev->base);
            }
            LOG_I("%s timeout request=%u s actual=%u ms",
                  dev->name, *(rt_uint32_t *)arg, ns800_timeout_to_ms(dev->timeout_us));
        }
#endif
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        if (arg == RT_NULL)
        {
            return -RT_EINVAL;
        }
        *(rt_uint32_t *)arg = ns800_timeout_to_seconds(dev->timeout_us);
        break;

    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        return -RT_ENOSYS;

    case RT_DEVICE_CTRL_WDT_START:
        if (!dev->started)
        {
#ifdef BSP_USING_IWDG1
            if (dev->id == NS800_IWDG1)
            {
                iwdg1_apply_config(dev);
                IWDG1_enableModule((IWDG1_TypeDef *)dev->base);
            }
#endif
#ifdef BSP_USING_IWDG2
            if (dev->id == NS800_IWDG2)
            {
                rt_err_t ret = iwdg2_apply_config(dev);
                if (ret != RT_EOK)
                {
                    return ret;
                }
                IWDG2_enableModule((IWDG2_TypeDef *)dev->base);
                IWDG2_refreshModule((IWDG2_TypeDef *)dev->base);
            }
#endif
            dev->started = RT_TRUE;
            LOG_I("%s started, timeout=%u ms", dev->name, ns800_timeout_to_ms(dev->timeout_us));
        }
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        return -RT_ENOSYS;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static const struct rt_watchdog_ops ns800_iwdg_ops =
{
    .init = ns800_iwdg_init,
    .control = ns800_iwdg_control,
};

#ifdef BSP_USING_IWDG1
int rt_hw_iwdg1_init(void)
{
    iwdg1_dev.id = NS800_IWDG1;
    iwdg1_dev.name = IWDG1_DEVICE_NAME;
    iwdg1_dev.base = IWDG1;
    iwdg1_dev.started = RT_FALSE;
    iwdg1_select_config(10U, &iwdg1_dev);
    iwdg1_dev.watchdog.ops = &ns800_iwdg_ops;

    if (rt_hw_watchdog_register(&iwdg1_dev.watchdog,
                                iwdg1_dev.name,
                                RT_DEVICE_FLAG_DEACTIVATE,
                                &iwdg1_dev) != RT_EOK)
    {
        LOG_E("%s register failed", iwdg1_dev.name);
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_iwdg1_init);
#endif /* BSP_USING_IWDG1 */

#ifdef BSP_USING_IWDG2
int rt_hw_iwdg2_init(void)
{
    RCC_unlockRccRegister();
    RCC_enableLircOscillator();
    RCC_lockRccRegister();

    iwdg2_dev.id = NS800_IWDG2;
    iwdg2_dev.name = IWDG2_DEVICE_NAME;
    iwdg2_dev.base = IWDG2;
    iwdg2_dev.started = RT_FALSE;
    iwdg2_select_config(10U, &iwdg2_dev);
    iwdg2_dev.watchdog.ops = &ns800_iwdg_ops;

    if (rt_hw_watchdog_register(&iwdg2_dev.watchdog,
                                iwdg2_dev.name,
                                RT_DEVICE_FLAG_DEACTIVATE,
                                &iwdg2_dev) != RT_EOK)
    {
        LOG_E("%s register failed", iwdg2_dev.name);
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_iwdg2_init);
#endif /* BSP_USING_IWDG2 */

#endif /* RT_USING_WDT && (BSP_USING_IWDG1 || BSP_USING_IWDG2) */

