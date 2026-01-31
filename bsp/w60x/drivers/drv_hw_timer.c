/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-19     fanwenl      1st version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "wm_type_def.h"
#include "wm_timer.h"
#include "drv_hw_timer.h"

#ifdef BSP_USING_CLOCK_TIMER

struct wm_timer_Type
{
    enum tls_timer_unit unit;
    enum tls_timer_id id;
};

static void wm_timer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
    struct tls_timer_cfg timer_cfg;
    struct wm_timer_Type *wm_timer = (struct wm_timer_Type *)timer->parent.user_data;

    timer_cfg.unit = wm_timer->unit;
    timer_cfg.timeout = 0xFFFFFFFF;
    timer_cfg.is_repeat = 0;
    timer_cfg.callback = NULL;
    timer_cfg.arg = NULL;

    if (state == 1)
    {
        tls_timer_create(&timer_cfg, wm_timer->id);
    }
    else if (state == 0)
    {
        tls_timer_destroy(wm_timer->id);
    }
}

static rt_err_t wm_timer_start(rt_clock_timer_t *timer, rt_uint32_t t, rt_clock_timer_mode_t opmode)
{
    struct wm_timer_Type *wm_timer = (struct wm_timer_Type *)timer->parent.user_data;
    uint8_t m;

    tls_timer_change(wm_timer->id, t);
    m = (opmode == CLOCK_TIMER_MODE_ONESHOT) ? 0 : 1;
    tls_timer_set_mode(wm_timer->id, m);
    tls_timer_start(wm_timer->id);

    return RT_EOK;
}

static void wm_timer_stop(rt_clock_timer_t *timer)
{
    struct wm_timer_Type *wm_timer = (struct wm_timer_Type *)timer->parent.user_data;

    tls_timer_stop(wm_timer->id);
}

static rt_uint32_t wm_timer_get(rt_clock_timer_t *timer)
{
    return 0;
}

static rt_err_t wm_timer_ctrl(rt_clock_timer_t *timer, rt_uint32_t cmd, void *arg)
{
    /* The frequency value is an immutable value. */
    if (cmd != CLOCK_TIMER_CTRL_FREQ_SET)
    {
        return -RT_ENOSYS;
    }
    if ( *(rt_uint32_t*)arg == 1000000)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ENOSYS;
    }
}

static const struct rt_clock_timer_info _info =
{
    1000000,            /* the maximum count frequency can be set */
    1000000,            /* the minimum count frequency can be set */
    0xFFFFFFFF,         /* the maximum counter value */
    CLOCK_TIMER_CNTMODE_DW, /* Increment or Decreasing count mode */
};

static const struct rt_clock_timer_ops _ops =
{
    wm_timer_init,
    wm_timer_start,
    wm_timer_stop,
    wm_timer_get,
    wm_timer_ctrl,
};

#ifdef USING_HW_TIMER1
static rt_clock_timer_t _timer1;
static struct wm_timer_Type wm_timer1;
#endif
#ifdef USING_HW_TIMER2
static rt_clock_timer_t _timer2;
static struct wm_timer_Type wm_timer2;
#endif
#ifdef USING_HW_TIMER3
static rt_clock_timer_t _timer3;
static struct wm_timer_Type wm_timer3;
#endif
#ifdef USING_HW_TIMER4
static rt_clock_timer_t _timer4;
static struct wm_timer_Type wm_timer4;
#endif
#ifdef USING_HW_TIMER5
static rt_clock_timer_t _timer5;
static struct wm_timer_Type wm_timer5;
#endif

int wm_hw_timer_init(void)
{
#ifdef USING_HW_TIMER1
    wm_timer1.id = TLS_TIMER_ID_1;
    wm_timer1.unit = TLS_TIMER_UNIT_US;

    _timer1.info = &_info;
    _timer1.ops = &_ops;

    rt_clock_timer_register(&_timer1, "timer1", &wm_timer1);
#endif
#ifdef USING_HW_TIMER2
    wm_timer2.id = TLS_TIMER_ID_2;
    wm_timer2.unit = TLS_TIMER_UNIT_US;

    _timer2.info = &_info;
    _timer2.ops = &_ops;

    rt_clock_timer_register(&_timer2, "timer2", &wm_timer2);
#endif
#ifdef USING_HW_TIMER3
    wm_timer3.id = TLS_TIMER_ID_3;
    wm_timer3.unit = TLS_TIMER_UNIT_US;

    _timer3.info = &_info;
    _timer3.ops = &_ops;

    rt_clock_timer_register(&_timer3, "timer3", &wm_timer3);
#endif
#ifdef USING_HW_TIMER4
    wm_timer4.id = TLS_TIMER_ID_4;
    wm_timer4.unit = TLS_TIMER_UNIT_US;

    _timer4.info = &_info;
    _timer4.ops = &_ops;

    rt_clock_timer_register(&_timer4, "timer4", &wm_timer4);
#endif
#ifdef USING_HW_TIMER5
    wm_timer5.id = TLS_TIMER_ID_5;
    wm_timer5.unit = TLS_TIMER_UNIT_US;

    _timer5.info = &_info;
    _timer5.ops = &_ops;

    rt_clock_timer_register(&_timer5, "timer5", &wm_timer5);
#endif
    return 0;
}
INIT_BOARD_EXPORT(wm_hw_timer_init);

void TIM1_IRQHandler(void)
{
    timer_clear_irq(1);
#ifdef USING_HW_TIMER1
    rt_clock_timer_isr(&_timer1);
#endif
}
void TIM2_IRQHandler(void)
{
    timer_clear_irq(2);
#ifdef USING_HW_TIMER2
    rt_clock_timer_isr(&_timer2);
#endif
}
void TIM3_IRQHandler(void)
{
    timer_clear_irq(3);
#ifdef USING_HW_TIMER3
    rt_clock_timer_isr(&_timer3);
#endif
}
void TIM4_IRQHandler(void)
{
    timer_clear_irq(4);
#ifdef USING_HW_TIMER4
    rt_clock_timer_isr(&_timer4);
#endif
}
void TIM5_IRQHandler(void)
{
    timer_clear_irq(5);
#ifdef USING_HW_TIMER5
    rt_clock_timer_isr(&_timer5);
#endif
}
#endif /* BSP_USING_CLOCK_TIMER */
