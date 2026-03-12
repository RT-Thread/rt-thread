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
#include <drivers/clock_time.h>
#include "ch56x_sys.h"
#include "ch56x_timer.h"
#include "isr_sp.h"

#if !defined(BSP_USING_TMR0) && !defined(BSP_USING_TMR1) && !defined(BSP_USING_TMR2)
    #error "Please define at least one TMRx"
#endif

struct clock_timer_device
{
    struct rt_clock_timer_device parent;
    struct rt_clock_timer_info clock_timer_info;
    volatile struct timer_registers *reg_base;
    rt_clock_timer_mode_t tmode;
    irq_number_t irqn;
    char *name;
};

#ifdef BSP_USING_TMR0
static struct clock_timer_device clock_timer_device_0 =
{
    .clock_timer_info =
    {
        .maxfreq = 80000000,
        .minfreq = 80000000,
        .maxcnt  = 0x3ffffff,
        .cntmode = CLOCK_TIMER_CNTMODE_UP,
    },
    .reg_base = (struct timer_registers *)TMR0_REG_BASE,
    .tmode = CLOCK_TIMER_MODE_PERIOD,
    .irqn = TMR0_IRQn,
    .name = "timer0",
};
#endif

#ifdef BSP_USING_TMR1
static struct clock_timer_device clock_timer_device_1 =
{
    .clock_timer_info =
    {
        .maxfreq = 80000000,
        .minfreq = 80000000,
        .maxcnt  = 0x3ffffff,
        .cntmode = CLOCK_TIMER_CNTMODE_UP,
    },
    .reg_base = (struct timer_registers *)TMR1_REG_BASE,
    .tmode = CLOCK_TIMER_MODE_PERIOD,
    .irqn = TMR1_IRQn,
    .name = "timer1",
};
#endif

#ifdef BSP_USING_TMR2
static struct clock_timer_device clock_timer_device_2 =
{
    .clock_timer_info =
    {
        .maxfreq = 80000000,
        .minfreq = 80000000,
        .maxcnt  = 0x3ffffff,
        .cntmode = CLOCK_TIMER_CNTMODE_UP,
    },
    .reg_base = (struct timer_registers *)TMR2_REG_BASE,
    .tmode = CLOCK_TIMER_MODE_PERIOD,
    .irqn = TMR2_IRQn,
    .name = "timer2",
};
#endif

static void clock_timer_stop(struct rt_clock_timer_device *timer);

static void clock_timer_init(struct rt_clock_timer_device *timer, uint32_t state)
{
    struct clock_timer_device *clock_timer_device = (void *)timer;

    RT_ASSERT(clock_timer_device != RT_NULL);

    /* no resource processing, `state` ignored */
    clock_timer_stop(timer);

    if (clock_timer_device->irqn != TMR0_IRQn)
    {
        clock_timer_device->reg_base->CTRL_DMA.reg = 0;
    }
}

static rt_err_t clock_timer_start(struct rt_clock_timer_device *timer, uint32_t cnt, rt_clock_timer_mode_t mode)
{
    struct clock_timer_device *clock_timer_device = (void *)timer;
    volatile struct timer_registers *txreg;

    RT_ASSERT(clock_timer_device != RT_NULL);

    /* clock_timer_device->tmode may be different from timer->mode.
     * For multi-cycle ONESHOT, tmode is set to PERIOD at clock_timer_start.
    */
    clock_timer_device->tmode = mode;

    sys_clk_off_by_irqn(clock_timer_device->irqn, SYS_SLP_CLK_ON);
    txreg = clock_timer_device->reg_base;
    txreg->CNT_END = cnt;
    txreg->CTRL_MOD.reg = RB_TMR_ALL_CLEAR;
    txreg->CTRL_MOD.reg = RB_TMR_COUNT_EN;
    txreg->INTER_EN.cyc_end = 1;
    rt_hw_interrupt_umask(clock_timer_device->irqn);

    return RT_EOK;
}

static void clock_timer_stop(struct rt_clock_timer_device *timer)
{
    struct clock_timer_device *clock_timer_device = (void *)timer;
    volatile struct timer_registers *txreg;

    RT_ASSERT(clock_timer_device != RT_NULL);

    rt_hw_interrupt_mask(clock_timer_device->irqn);
    /* note: RB_TMR_COUNT_EN cleared */
    txreg = clock_timer_device->reg_base;
    txreg->CTRL_MOD.reg = RB_TMR_ALL_CLEAR;
    txreg->INTER_EN.reg = 0;
    sys_clk_off_by_irqn(clock_timer_device->irqn, SYS_SLP_CLK_OFF);
}

static uint32_t clock_timer_count_get(struct rt_clock_timer_device *timer)
{
    struct clock_timer_device *clock_timer_device = (void *)timer;

    RT_ASSERT(clock_timer_device != RT_NULL);

    return clock_timer_device->reg_base->COUNT;
}

static rt_err_t clock_timer_control(
    struct rt_clock_timer_device *timer, uint32_t cmd, void *args)
{
    struct clock_timer_device *clock_timer_device = (void *)timer;
    rt_err_t result = RT_EOK;

    RT_ASSERT(clock_timer_device != RT_NULL);

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
        /*  clocking for ch56x timers are fixed to Fsys */
        if (args == RT_NULL || *(uint32_t *)args != timer->info->minfreq)
        {
            result = -RT_EINVAL;
        }
        break;

    case CLOCK_TIMER_CTRL_STOP:
    case CLOCK_TIMER_CTRL_INFO_GET:
    case CLOCK_TIMER_CTRL_MODE_SET:
    default:
        result = -RT_ENOSYS;
    }

    return result;
}

static const struct rt_clock_timer_ops clock_timer_ops =
{
    .init = clock_timer_init,
    .start = clock_timer_start,
    .stop = clock_timer_stop,
    .count_get = clock_timer_count_get,
    .control = clock_timer_control,
};

static int rt_hw_clock_timer_init(void)
{
    struct clock_timer_device *devices[3];

    uint32_t Fsys = sys_hclk_get();

    int n = 0;

#ifdef BSP_USING_TMR2
    devices[n++] = &clock_timer_device_2;
#endif
#ifdef BSP_USING_TMR1
    devices[n++] = &clock_timer_device_1;
#endif
#ifdef BSP_USING_TMR0
    devices[n++] = &clock_timer_device_0;
#endif

    while (--n >= 0)
    {
        struct clock_timer_device *clock_timer_device = devices[n];
        /* counting frequency is fixed to Fsys */
        clock_timer_device->clock_timer_info.maxfreq = Fsys;
        clock_timer_device->clock_timer_info.minfreq = Fsys;
        clock_timer_device->parent.info = &clock_timer_device->clock_timer_info;
        clock_timer_device->parent.ops = &clock_timer_ops;
        rt_clock_timer_register(
            &clock_timer_device->parent, clock_timer_device->name, RT_NULL);
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);

static void _clock_timer_isr_common(struct clock_timer_device *clock_timer_device)
{
    volatile struct timer_registers *txreg = clock_timer_device->reg_base;

    if (txreg->INT_FLAG.cyc_end)
    {
        if (clock_timer_device->tmode == CLOCK_TIMER_MODE_ONESHOT)
        {
            /* disable timer to emulate oneshot */
            txreg->CTRL_MOD.reg = 0;
        }
        rt_clock_timer_isr(&clock_timer_device->parent);
        txreg->INT_FLAG.cyc_end = 1;
    }
}

#ifdef BSP_USING_TMR0
void tmr0_irq_handler(void) __attribute__((interrupt()));
void tmr0_irq_handler(void)
{
    isr_sp_enter();
    rt_interrupt_enter();
    _clock_timer_isr_common(&clock_timer_device_0);
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
    _clock_timer_isr_common(&clock_timer_device_1);
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
    _clock_timer_isr_common(&clock_timer_device_2);
    rt_interrupt_leave();
    isr_sp_leave();
}
#endif
