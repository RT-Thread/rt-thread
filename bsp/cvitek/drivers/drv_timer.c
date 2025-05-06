/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024/08/08     ShichengChu    first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_timer.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.TIMER"

#include "pinctrl.h"
#include "mmio.h"
#include "drv_ioremap.h"

#define DW_NR_TIMERS 8

#define TIMER_FREQ 25000000

#define DW_TIMER_GET_RELOAD_VAL(_tim_, _frq_)      ((_tim_ < 25000U) ? ((_frq_ * _tim_) / 1000U) : (_frq_ * (_tim_ / 1000U)))

#define DW_TIMER0_BASE              0x030A0000UL
#define DW_TIMER0_SIZE              0x14U

#define DW_TIMER1_BASE              (DW_TIMER0_BASE+DW_TIMER0_SIZE)
#define DW_TIMER1_SIZE              DW_TIMER0_SIZE

#define DW_TIMER2_BASE              (DW_TIMER1_BASE+DW_TIMER1_SIZE)
#define DW_TIMER2_SIZE              DW_TIMER1_SIZE

#define DW_TIMER3_BASE              (DW_TIMER2_BASE+DW_TIMER2_SIZE)
#define DW_TIMER3_SIZE              DW_TIMER2_SIZE

#define DW_TIMER4_BASE              (DW_TIMER3_BASE+DW_TIMER3_SIZE)
#define DW_TIMER4_SIZE              DW_TIMER3_SIZE

#define DW_TIMER5_BASE              (DW_TIMER4_BASE+DW_TIMER4_SIZE)
#define DW_TIMER5_SIZE              DW_TIMER4_SIZE

#define DW_TIMER6_BASE              (DW_TIMER5_BASE+DW_TIMER5_SIZE)
#define DW_TIMER6_SIZE              DW_TIMER5_SIZE

#define DW_TIMER7_BASE              (DW_TIMER6_BASE+DW_TIMER6_SIZE)
#define DW_TIMER7_SIZE              DW_TIMER6_SIZE

#if defined(BSP_USING_CV18XX) || defined(SOC_CV18XX_AARCH64)

#define TIMER_INTR_0 BSP_TIMER_IRQ_BASE + 0
#define TIMER_INTR_1 BSP_TIMER_IRQ_BASE + 1
#define TIMER_INTR_2 BSP_TIMER_IRQ_BASE + 2
#define TIMER_INTR_3 BSP_TIMER_IRQ_BASE + 3
#define TIMER_INTR_4 BSP_TIMER_IRQ_BASE + 4
#define TIMER_INTR_5 BSP_TIMER_IRQ_BASE + 5
#define TIMER_INTR_6 BSP_TIMER_IRQ_BASE + 6
#define TIMER_INTR_7 BSP_TIMER_IRQ_BASE + 7

#elif defined(BSP_USING_C906_LITTLE)

#define TIMER_INTR_4 BSP_TIMER_IRQ_BASE + 0
#define TIMER_INTR_5 BSP_TIMER_IRQ_BASE + 1
#define TIMER_INTR_6 BSP_TIMER_IRQ_BASE + 2
#define TIMER_INTR_7 BSP_TIMER_IRQ_BASE + 3

#else

#error "Unsupported CPU type!"

#endif

/*! Timer1 Control Reg,     offset: 0x08 */
#define DW_TIMER_CTL_ENABLE_SEL_Pos                                    (0U)
#define DW_TIMER_CTL_ENABLE_SEL_Msk                                    (0x1U << DW_TIMER_CTL_ENABLE_SEL_Pos)
#define DW_TIMER_CTL_ENABLE_SEL_EN                                     DW_TIMER_CTL_ENABLE_SEL_Msk

#define DW_TIMER_CTL_MODE_SEL_Pos                                      (1U)
#define DW_TIMER_CTL_MODE_SEL_Msk                                      (0x1U << DW_TIMER_CTL_MODE_SEL_Pos)
#define DW_TIMER_CTL_MODE_SEL_EN                                       DW_TIMER_CTL_MODE_SEL_Msk

#define DW_TIMER_CTL_INT_MASK_Pos                                      (2U)
#define DW_TIMER_CTL_INT_MASK_Msk                                      (0x1U << DW_TIMER_CTL_INT_MASK_Pos)
#define DW_TIMER_CTL_INT_MAKS_EN                                       DW_TIMER_CTL_INT_MASK_Msk

#define DW_TIMER_CTL_HARD_TRIG_Pos                                     (4U)
#define DW_TIMER_CTL_HARD_TRIG_Msk                                     (0x1U << DW_TIMER_CTL_HARD_TRIG_Pos)
#define DW_TIMER_CTL_HARD_TRIG_EN                                      DW_TIMER_CTL_HARD_TRIG_Msk

/*! Timer EOI,            offset: 0x0c */
#define DW_TIMER_EOI_REG_Pos                                           (0U)
#define DW_TIMER_EOI_REG_Msk                                           (0x1U << DW_TIMER_EOI_REG_Pos)
#define DW_TIMER_EOI_REG_EN                                            DW_TIMER_EOI_REG_Msk

/*! Timer Int Status,     offset: 0x10 */
#define DW_TIMER_INT_STATUS_Pos                                        (0U)
#define DW_TIMER_INT_STATUS_Msk                                        (0x1U << DW_TIMER_INT_STATUS_Pos)
#define DW_TIMER_INT_STATUS_EN                                         DW_TIMER_INT_STATUS_Msk

/*! Timers Int Status,    offset: 0xa0 */
#define DW_TIMERS_INT_STATUS_Pos                                       (0U)
#define DW_TIMERS_INT_STATUS_Msk                                       (0x2U << DW_TIMERS_INT_STATUS_Pos)
#define DW_TIMERS_INT_STATUS_EN                                        DW_TIMERS_INT_STATUS_Msk

/*! Timers EOI,           offset: 0xa4 */
#define DW_TIMERS_EOI_REG_Pos                                          (0U)
#define DW_TIMERS_EOI_REG_Msk                                          (0x2U << DW_TIMERS_EOI_REG_Pos)
#define DW_TIMERS_EOI_REG_EN                                           DW_TIMERS_EOI_REG_Msk

/*! Timers Raw Int Status,offset: 0xa8 */
#define DW_TIMERS_RAW_INT_STA_Pos                                      (0U)
#define DW_TIMERS_RAW_INT_STA_Msk                                      (0x2U << DW_TIMERS_RAW_INT_STA_Pos)
#define DW_TIMERS_RAW_INT_STA_EN                                       DW_TIMERS_RAW_INT_STA_Msk

typedef struct {
    volatile uint32_t TLC;                                                /* Offset: 0x000 (R/W) TimerLoadCount */
    volatile const  uint32_t TCV;                                                /* Offset: 0x004 (R/ ) TimerCurrentValue */
    volatile uint32_t TCR;                                                /* Offset: 0x008 (R/W) TimerControlReg */
    volatile const  uint32_t TEOI;                                               /* Offset: 0x00c (R/ ) TimerEOI */
    volatile const  uint32_t TIS;                                                /* Offset: 0x010 (R/ ) TimerIntStatus */
} dw_timer_regs_t;

typedef struct {
    dw_timer_regs_t timer[DW_NR_TIMERS];
    volatile const  uint32_t TSIS;                                               /* Offset: 0x0a0 (R/ ) TimersIntStatus */
    volatile const  uint32_t TSEOI;                                              /* Offset: 0x0a4 (R/ ) TimersEOI */
    volatile const  uint32_t TSRIS;                                              /* Offset: 0x0a8 (R/ ) TimersRawIntStatus */
} dw_timer_general_regs_t;

typedef struct _timer
{
    char *name;
    dw_timer_regs_t *base;
    rt_uint32_t irqno;
    rt_hwtimer_t timer;
}_timer_t;

static void _timer_init(rt_hwtimer_t *timer, rt_uint32_t state);
static rt_err_t _timer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode);
static void _timer_stop(rt_hwtimer_t *timer);
static rt_uint32_t _timer_count_get(rt_hwtimer_t *timer);
static rt_err_t _timer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args);

static const struct rt_hwtimer_ops _timer_ops = {
    .init = _timer_init,
    .start = _timer_start,
    .stop = _timer_stop,
    .count_get = _timer_count_get,
    .control = _timer_control
};

static const struct rt_hwtimer_info _timer_info = {
    .maxfreq = 25000000UL,
    .minfreq = 25000000UL,
    .maxcnt = 0xFFFFFFFF,
    .cntmode = HWTIMER_MODE_PERIOD
};

static _timer_t _timer_obj[] =
{
#ifdef BSP_USING_TIMER0
    {
        .name = "timer0",
        .base = (dw_timer_regs_t *)DW_TIMER0_BASE,
        .irqno = TIMER_INTR_0
    },
#endif /* BSP_USING_TIMER0 */
#ifdef BSP_USING_TIMER1
    {
        .name = "timer1",
        .base = (dw_timer_regs_t *)DW_TIMER1_BASE,
        .irqno = TIMER_INTR_1
    },
#endif /* BSP_USING_TIMER1 */
#ifdef BSP_USING_TIMER2
    {
        .name = "timer2",
        .base = (dw_timer_regs_t *)DW_TIMER2_BASE,
        .irqno = TIMER_INTR_2
    },
#endif /* BSP_USING_TIMER2 */
#ifdef BSP_USING_TIMER3
    {
        .name = "timer3",
        .base = (dw_timer_regs_t *)DW_TIMER3_BASE,
        .irqno = TIMER_INTR_3
    },
#endif /* BSP_USING_TIMER3 */
#ifdef BSP_USING_TIMER4
    {
        .name = "timer4",
        .base = (dw_timer_regs_t *)DW_TIMER4_BASE,
        .irqno = TIMER_INTR_4
    },
#endif /* BSP_USING_TIMER4 */
#ifdef BSP_USING_TIMER5
    {
        .name = "timer5",
        .base = (dw_timer_regs_t *)DW_TIMER5_BASE,
        .irqno = TIMER_INTR_5
    },
#endif /* BSP_USING_TIMER5 */
#ifdef BSP_USING_TIMER6
    {
        .name = "timer6",
        .base = (dw_timer_regs_t *)DW_TIMER6_BASE,
        .irqno = TIMER_INTR_6
    },
#endif /* BSP_USING_TIMER6 */
#ifdef BSP_USING_TIMER7
    {
        .name = "timer7",
        .base = (dw_timer_regs_t *)DW_TIMER7_BASE,
        .irqno = TIMER_INTR_7
    },
#endif /* BSP_USING_TIMER7 */
};

uint32_t hal_timer_read_load(dw_timer_regs_t *timer_base)
{
    return (timer_base->TLC);
}
void hal_timer_write_load(dw_timer_regs_t *timer_base, uint32_t value)
{
    timer_base->TLC = value;
}
uint32_t hal_timer_get_current(dw_timer_regs_t *timer_base)
{
    return (timer_base->TCV);
}
void hal_timer_set_enable(dw_timer_regs_t *timer_base)
{
    timer_base->TCR |= (DW_TIMER_CTL_ENABLE_SEL_EN);
}
void hal_timer_set_disable(dw_timer_regs_t *timer_base)
{
    timer_base->TCR &= ~(DW_TIMER_CTL_ENABLE_SEL_EN);
}
uint32_t hal_timer_get_enable(dw_timer_regs_t *timer_base)
{
    if ((timer_base->TCR) & DW_TIMER_CTL_ENABLE_SEL_EN)
        return 1;

    return 0;
}
void hal_timer_set_mode_free(dw_timer_regs_t *timer_base)
{
    timer_base->TCR &= ~(DW_TIMER_CTL_MODE_SEL_EN);
}
void hal_timer_set_mode_load(dw_timer_regs_t *timer_base)
{
    timer_base->TCR |= (DW_TIMER_CTL_MODE_SEL_EN);
}
uint32_t hal_timer_get_model(dw_timer_regs_t *timer_base)
{
    if ((timer_base->TCR) & DW_TIMER_CTL_MODE_SEL_EN)
        return 1;

    return 0;
}
void hal_timer_set_mask(dw_timer_regs_t *timer_base)
{
    timer_base->TCR |= (DW_TIMER_CTL_INT_MAKS_EN);
}
void hal_timer_set_unmask(dw_timer_regs_t *timer_base)
{
    timer_base->TCR &= ~(DW_TIMER_CTL_INT_MAKS_EN);
}
uint32_t hal_timer_get_mask(dw_timer_regs_t *timer_base)
{
    if ((timer_base->TCR) & DW_TIMER_CTL_INT_MAKS_EN)
        return 1;

    return 0;
}
void hal_timer_set_hardtrigger_en(dw_timer_regs_t *timer_base)
{
    timer_base->TCR |= (DW_TIMER_CTL_HARD_TRIG_EN);
}
void hal_timer_set_hardtrigger_dis(dw_timer_regs_t *timer_base)
{
    timer_base->TCR &= ~(DW_TIMER_CTL_HARD_TRIG_EN);
}
uint32_t hal_timer_get_hardtrigger(dw_timer_regs_t *timer_base)
{
    if ((timer_base->TCR) & DW_TIMER_CTL_HARD_TRIG_EN)
        return 1;

    return 0;
}
uint32_t hal_timer_clear_irq(dw_timer_regs_t *timer_base)
{
    if ((timer_base->TEOI) & DW_TIMER_EOI_REG_EN)
        return 1;

    return 0;
}
uint32_t hal_timer_get_int_status(dw_timer_regs_t *timer_base)
{
    if ((timer_base->TIS) & DW_TIMER_INT_STATUS_EN)
        return 1;

    return 0;
}
void hal_timer_reset_register(dw_timer_regs_t *timer_base)
{
    timer_base->TCR = 0U;
    timer_base->TLC = 0U;
}
uint32_t hal_timer_general_active_after_mask(dw_timer_general_regs_t *timer_base)
{
    return ((timer_base->TSIS) & DW_TIMERS_INT_STATUS_EN);
}
uint32_t hal_timer_general_clear_irq(dw_timer_general_regs_t *timer_base)
{
    return ((timer_base->TSEOI) & DW_TIMERS_EOI_REG_EN);
}
uint32_t hal_timer_general_active_prior_mask(dw_timer_general_regs_t *timer_base)
{
    return ((timer_base->TSRIS) & DW_TIMERS_RAW_INT_STA_EN);
}

static void rt_hw_hwtmr_isr(int irqno, void *param)
{
    _timer_t *_tmr = param;
    dw_timer_regs_t *timer_base = _tmr->base;

    if (hal_timer_get_int_status(timer_base))
    {
        hal_timer_clear_irq(timer_base);
        hal_timer_set_disable(timer_base);

        rt_device_hwtimer_isr(&_tmr->timer);
        if(_tmr->timer.mode == HWTIMER_MODE_PERIOD)
        {
            hal_timer_set_enable(timer_base);
            hal_timer_set_unmask(timer_base);
        }
    }
}

static void _timer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);

    RT_ASSERT(_tmr!=NULL)
    if(state)
    {
        hal_timer_reset_register(_tmr->base);
    }
}

static rt_err_t _timer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);
    uint32_t tmp_load = cnt;

    hal_timer_set_mode_load(_tmr->base);

    /*FIXME: no less than 10*/
    if (tmp_load < 10)
    {
        tmp_load = 10;
    }

    hal_timer_set_disable(_tmr->base);
    hal_timer_write_load(_tmr->base, tmp_load);

    hal_timer_set_enable(_tmr->base);
    hal_timer_set_unmask(_tmr->base);

    return RT_EOK;
}

static void _timer_stop(rt_hwtimer_t *timer)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);

    hal_timer_set_mask(_tmr->base);
    hal_timer_set_disable(_tmr->base);
}

static rt_uint32_t _timer_count_get(rt_hwtimer_t *timer)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);
    rt_uint32_t cnt = hal_timer_get_current(_tmr->base);

    return cnt;
}

static rt_err_t _timer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        err = -RT_ERROR;
        break;
    case HWTIMER_CTRL_INFO_GET:
        *(rt_hwtimer_t*)args = _tmr->timer;
        break;
    case HWTIMER_CTRL_MODE_SET:
        _tmr->timer.mode = *(rt_uint32_t*)args;
        break;
    case HWTIMER_CTRL_STOP:
        _timer_stop(timer);
        break;
    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

int rt_hw_timer_init(void)
{
    int ret = RT_EOK;

    for (uint32_t i = 0; i < sizeof(_timer_obj) / sizeof(_timer_obj[0]); i++)
    {
        _timer_obj[i].base = (dw_timer_regs_t *)DRV_IOREMAP((void*)_timer_obj[i].base, 0x10000);

        _timer_obj[i].timer.info = &_timer_info;
        _timer_obj[i].timer.ops = &_timer_ops;
        ret = rt_device_hwtimer_register(&_timer_obj[i].timer, _timer_obj[i].name, &_timer_obj[i]);
        if (ret != RT_EOK)
        {
            LOG_E("%s register failed", _timer_obj[i].name);
        }
        rt_hw_interrupt_install(_timer_obj[i].irqno, rt_hw_hwtmr_isr, &_timer_obj[i], _timer_obj[i].name);
        rt_hw_interrupt_umask(_timer_obj[i].irqno);
    }

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_timer_init);
