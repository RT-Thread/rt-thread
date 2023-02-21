/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#include <rthw.h>
#include <rtdebug.h>
#include <drivers/hwtimer.h>
#include "ch56x_sys.h"
#include "ch56x_timer.h"
#include "isr_sp.h"

#if !defined(BSP_USING_TMR0) && !defined(BSP_USING_TMR1) && !defined(BSP_USING_TMR2)
    #error "Please define at least one TMRx"
#endif

struct hwtimer_device
{
    struct rt_hwtimer_device parent;
    struct rt_hwtimer_info hwtimer_info;
    volatile struct timer_registers *reg_base;
    rt_hwtimer_mode_t tmode;
    irq_number_t irqn;
    char *name;
};

#ifdef BSP_USING_TMR0
static struct hwtimer_device hwtimer_device_0 =
{
    .hwtimer_info =
    {
        .maxfreq = 80000000,
        .minfreq = 80000000,
        .maxcnt  = 0x3ffffff,
        .cntmode = HWTIMER_CNTMODE_UP,
    },
    .reg_base = (struct timer_registers *)TMR0_REG_BASE,
    .tmode = HWTIMER_MODE_PERIOD,
    .irqn = TMR0_IRQn,
    .name = "timer0",
};
#endif

#ifdef BSP_USING_TMR1
static struct hwtimer_device hwtimer_device_1 =
{
    .hwtimer_info =
    {
        .maxfreq = 80000000,
        .minfreq = 80000000,
        .maxcnt  = 0x3ffffff,
        .cntmode = HWTIMER_CNTMODE_UP,
    },
    .reg_base = (struct timer_registers *)TMR1_REG_BASE,
    .tmode = HWTIMER_MODE_PERIOD,
    .irqn = TMR1_IRQn,
    .name = "timer1",
};
#endif

#ifdef BSP_USING_TMR2
static struct hwtimer_device hwtimer_device_2 =
{
    .hwtimer_info =
    {
        .maxfreq = 80000000,
        .minfreq = 80000000,
        .maxcnt  = 0x3ffffff,
        .cntmode = HWTIMER_CNTMODE_UP,
    },
    .reg_base = (struct timer_registers *)TMR2_REG_BASE,
    .tmode = HWTIMER_MODE_PERIOD,
    .irqn = TMR2_IRQn,
    .name = "timer2",
};
#endif

static void hwtimer_stop(struct rt_hwtimer_device *timer);

static void hwtimer_init(struct rt_hwtimer_device *timer, uint32_t state)
{
    struct hwtimer_device *hwtimer_device = (void *)timer;

    RT_ASSERT(hwtimer_device != RT_NULL);

    /* no resource processing, `state` ignored */
    hwtimer_stop(timer);

    if (hwtimer_device->irqn != TMR0_IRQn)
    {
        hwtimer_device->reg_base->CTRL_DMA.reg = 0;
    }
}

static rt_err_t hwtimer_start(struct rt_hwtimer_device *timer, uint32_t cnt, rt_hwtimer_mode_t mode)
{
    struct hwtimer_device *hwtimer_device = (void *)timer;
    volatile struct timer_registers *txreg;

    RT_ASSERT(hwtimer_device != RT_NULL);

    /* hwtimer_device->tmode may be different from timer->mode.
     * For multi-cycle ONESHOT, tmode is set to PERIOD at hwtimer_start.
    */
    hwtimer_device->tmode = mode;

    sys_clk_off_by_irqn(hwtimer_device->irqn, SYS_SLP_CLK_ON);
    txreg = hwtimer_device->reg_base;
    txreg->CNT_END = cnt;
    txreg->CTRL_MOD.reg = RB_TMR_ALL_CLEAR;
    txreg->CTRL_MOD.reg = RB_TMR_COUNT_EN;
    txreg->INTER_EN.cyc_end = 1;
    rt_hw_interrupt_umask(hwtimer_device->irqn);

    return RT_EOK;
}

static void hwtimer_stop(struct rt_hwtimer_device *timer)
{
    struct hwtimer_device *hwtimer_device = (void *)timer;
    volatile struct timer_registers *txreg;

    RT_ASSERT(hwtimer_device != RT_NULL);

    rt_hw_interrupt_mask(hwtimer_device->irqn);
    /* note: RB_TMR_COUNT_EN cleared */
    txreg = hwtimer_device->reg_base;
    txreg->CTRL_MOD.reg = RB_TMR_ALL_CLEAR;
    txreg->INTER_EN.reg = 0;
    sys_clk_off_by_irqn(hwtimer_device->irqn, SYS_SLP_CLK_OFF);
}

static uint32_t hwtimer_count_get(struct rt_hwtimer_device *timer)
{
    struct hwtimer_device *hwtimer_device = (void *)timer;

    RT_ASSERT(hwtimer_device != RT_NULL);

    return hwtimer_device->reg_base->COUNT;
}

static rt_err_t hwtimer_control(
    struct rt_hwtimer_device *timer, uint32_t cmd, void *args)
{
    struct hwtimer_device *hwtimer_device = (void *)timer;
    rt_err_t result = RT_EOK;

    RT_ASSERT(hwtimer_device != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        /*  clocking for ch56x timers are fixed to Fsys */
        if (args == RT_NULL || *(uint32_t *)args != timer->info->minfreq)
        {
            result = -RT_EINVAL;
        }
        break;

    case HWTIMER_CTRL_STOP:
    case HWTIMER_CTRL_INFO_GET:
    case HWTIMER_CTRL_MODE_SET:
    default:
        result = -RT_ENOSYS;
    }

    return result;
}

static const struct rt_hwtimer_ops hwtimer_ops =
{
    .init = hwtimer_init,
    .start = hwtimer_start,
    .stop = hwtimer_stop,
    .count_get = hwtimer_count_get,
    .control = hwtimer_control,
};

static int rt_hw_hwtimer_init(void)
{
    struct hwtimer_device *devices[3];

    uint32_t Fsys = sys_hclk_get();

    int n = 0;

#ifdef BSP_USING_TMR2
    devices[n++] = &hwtimer_device_2;
#endif
#ifdef BSP_USING_TMR1
    devices[n++] = &hwtimer_device_1;
#endif
#ifdef BSP_USING_TMR0
    devices[n++] = &hwtimer_device_0;
#endif

    while (--n >= 0)
    {
        struct hwtimer_device *hwtimer_device = devices[n];
        /* counting frequency is fixed to Fsys */
        hwtimer_device->hwtimer_info.maxfreq = Fsys;
        hwtimer_device->hwtimer_info.minfreq = Fsys;
        hwtimer_device->parent.info = &hwtimer_device->hwtimer_info;
        hwtimer_device->parent.ops = &hwtimer_ops;
        rt_device_hwtimer_register(
            &hwtimer_device->parent, hwtimer_device->name, RT_NULL);
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);

static void _hwtimer_isr_common(struct hwtimer_device *hwtimer_device)
{
    volatile struct timer_registers *txreg = hwtimer_device->reg_base;

    if (txreg->INT_FLAG.cyc_end)
    {
        if (hwtimer_device->tmode == HWTIMER_MODE_ONESHOT)
        {
            /* disable timer to emulate oneshot */
            txreg->CTRL_MOD.reg = 0;
        }
        rt_device_hwtimer_isr(&hwtimer_device->parent);
        txreg->INT_FLAG.cyc_end = 1;
    }
}

#ifdef BSP_USING_TMR0
void tmr0_irq_handler(void) __attribute__((interrupt()));
void tmr0_irq_handler(void)
{
    isr_sp_enter();
    rt_interrupt_enter();
    _hwtimer_isr_common(&hwtimer_device_0);
    rt_interrupt_leave();
    isr_sp_leave();
}
#endif

#ifdef BSP_USING_TMR1
void tmr1_irq_handler(void) __attribute__((interrupt()));
void tmr1_irq_handler(void)
{
    isr_sp_enter();
    rt_interrupt_enter();
    _hwtimer_isr_common(&hwtimer_device_1);
    rt_interrupt_leave();
    isr_sp_leave();
}
#endif

#ifdef BSP_USING_TMR2
void tmr2_irq_handler(void) __attribute__((interrupt()));
void tmr2_irq_handler(void)
{
    isr_sp_enter();
    rt_interrupt_enter();
    _hwtimer_isr_common(&hwtimer_device_2);
    rt_interrupt_leave();
    isr_sp_leave();
}
#endif
