/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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

struct hwtimer_device
{
    struct rt_hwtimer_device parent;
    struct rt_hwtimer_info hwtimer_info;
    volatile struct timer_registers *reg_base;
    rt_hwtimer_mode_t mode;
    irq_number_t irqn;
    char *name;
};

#ifdef BSP_USING_TMR0
static struct hwtimer_device hwtimer_device_0 =
{
    .hwtimer_info =
    {
        .maxfreq = 1000000,
        .minfreq = 1000,
        .maxcnt  = 0x3ffffff,
        .cntmode = HWTIMER_CNTMODE_UP,
    },
    .reg_base = (struct timer_register *)TMR0_REG_BASE,
    .mode = HWTIMER_MODE_PERIOD,
    .irqn = TMR0_IRQn,
    .name = "timer0",
};
#endif

#ifdef BSP_USING_TMR1
static struct hwtimer_device hwtimer_device_1 =
{
    .hwtimer_info =
    {
        .maxfreq = 1000000,
        .minfreq = 1000,
        .maxcnt  = 0x3ffffff,
        .cntmode = HWTIMER_CNTMODE_UP,
    },
    .reg_base = (struct timer_register *)TMR1_REG_BASE,
    .mode = HWTIMER_MODE_PERIOD,
    .irqn = TMR1_IRQn,
    .name = "timer1",
};
#endif

#ifdef BSP_USING_TMR2
static struct hwtimer_device hwtimer_device_2 =
{
    .hwtimer_info =
    {
        .maxfreq = 1000000,
        .minfreq = 1000,
        .maxcnt  = 0x3ffffff,
        .cntmode = HWTIMER_CNTMODE_UP,
    },
    .reg_base = (struct timer_register *)TMR2_REG_BASE,
    .mode = HWTIMER_MODE_PERIOD,
    .irqn = TMR2_IRQn,
    .name = "timer2",
};
#endif

static void hwtimer_stop(struct rt_hwtimer_device *device);

static void hwtimer_init(struct rt_hwtimer_device *device, uint32_t state)
{
    struct hwtimer_device *hwtimer_device = (struct hwtimer_device *)device;
    volatile struct timer_registers *txreg;

    RT_ASSERT(hwtimer_device != RT_NULL);

    /* no resource processing, `state` ignored */
    hwtimer_stop(device);

    txreg = hwtimer_device->reg_base;
    txreg->INTER_EN.reg = 0;
    txreg->INT_FLAG.reg = RB_TMR_IX_MASK;

    if (hwtimer_device->irqn != TMR0_IRQn)
    {
        txreg->CTRL_DMA.reg = 0;
    }
}

static rt_err_t hwtimer_start(struct rt_hwtimer_device *device, uint32_t cnt, rt_hwtimer_mode_t mode)
{
    struct hwtimer_device *hwtimer_device = (struct hwtimer_device *)device;
    volatile struct timer_registers *txreg;

    RT_ASSERT(hwtimer_device != RT_NULL);

    /* no hw support for HWTIMER_MODE_ONESHOT, emulated with software */
    hwtimer_device->mode = mode;

    sys_clk_off_by_irqn(hwtimer_device->irqn, SYS_SLP_CLK_ON);
    txreg = hwtimer_device->reg_base;
    txreg->CTRL_MOD.reg = RB_TMR_ALL_CLEAR;
    txreg->CNT_END = cnt;
    txreg->INT_FLAG.reg = RB_TMR_IX_MASK;
    txreg->INTER_EN.cyc_end = 1;
    rt_hw_interrupt_unmask(hwtimer_device->irqn);
    txreg->CTRL_MOD.reg = RB_TMR_COUNT_EN;

    return RT_EOK;
}

static void hwtimer_stop(struct rt_hwtimer_device *device)
{
    struct hwtimer_device *hwtimer_device = (struct hwtimer_device *)device;

    RT_ASSERT(hwtimer_device != RT_NULL);

    rt_hw_interrupt_mask(hwtimer_device->irqn);
    /* note: RB_TMR_COUNT_EN cleared */
    hwtimer_device->reg_base->CTRL_MOD.reg = RB_TMR_ALL_CLEAR;
    hwtimer_device->reg_base->INTER_EN.cyc_end = 0;
    sys_clk_off_by_irqn(hwtimer_device->irqn, SYS_SLP_CLK_OFF);
}

static uint32_t hwtimer_count_get(struct rt_hwtimer_device *device)
{
    struct hwtimer_device *hwtimer_device = (struct hwtimer_device *)device;

    RT_ASSERT(hwtimer_device != RT_NULL);

    return hwtimer_device->reg_base->COUNT;
}

static rt_err_t hwtimer_control(
    struct rt_hwtimer_device *device, uint32_t cmd, void *args)
{
    struct hwtimer_device *hwtimer_device = (struct hwtimer_device *)device;
    rt_err_t result = RT_EOK;

    RT_ASSERT(hwtimer_device != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        if (args == RT_NULL)
            result = -RT_EINVAL;
        else
        {
            uint32_t freq = *((uint32_t *)args);
            uint32_t cntx = (sys_hclk_get() + (freq >> 1)) / freq;
            hwtimer_device->reg_base->CNT_END = cntx;
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
        struct hwtimer_device *timer = devices[n];
        timer->parent.info = &timer->hwtimer_info;
        timer->parent.ops = &hwtimer_ops;
        rt_device_hwtimer_register(
            &timer->parent, timer->name, RT_NULL);
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);

static void _hwtimer_isr_common(struct hwtimer_device *hwtimer_device)
{
    volatile struct timer_registers *txreg = hwtimer_device->reg_base;

    if (txreg->INT_FLAG.cyc_end)
    {
        if (hwtimer_device->mode == HWTIMER_MODE_ONESHOT)
        {
            /* disable timer to emulate oneshot */
            txreg->CTRL_MOD.reg = 0;
        }
        txreg->INT_FLAG.cyc_end = 1;
        rt_device_hwtimer_isr(&hwtimer_device->parent);
    }
}

#ifdef BSP_USING_TMR0
void tmr0_irq_handler(void) __attribute__((interrupt()));
void tmr0_irq_handler(void)
{
    rt_interrupt_enter();
    _hwtimer_isr_common(&hwtimer_device_0);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR1
void tmr1_irq_handler(void) __attribute__((interrupt()));
void tmr1_irq_handler(void)
{
    rt_interrupt_enter();
    _hwtimer_isr_common(&hwtimer_device_1);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TMR2
void tmr2_irq_handler(void) __attribute__((interrupt()));
void tmr2_irq_handler(void)
{
    rt_interrupt_enter();
    _hwtimer_isr_common(&hwtimer_device_2);
    rt_interrupt_leave();
}
#endif
