/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author           Notes
 * 2023-10-30       ChuShicheng      first version
 */

#include "drv_hwtimer.h"
#include "board.h"

#ifdef BSP_USING_HWTIMER

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.HWTIMER"

typedef struct _timer
{
    char *name;
    struct repeating_timer repeat_timer;
    alarm_id_t alarm_id;
    rt_hwtimer_t timer;
}_timer_t;

static void _hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state);
static rt_err_t _hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode);
static void _hwtimer_stop(rt_hwtimer_t *timer);
static rt_uint32_t _hwtimer_count_get(rt_hwtimer_t *timer);
static rt_err_t _hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args);
static int64_t _hwtmr_isr(alarm_id_t id, void *user_data);

static const struct rt_hwtimer_ops _hwtimer_ops = {
    .init = _hwtimer_init,
    .start = _hwtimer_start,
    .stop = _hwtimer_stop,
    .count_get = _hwtimer_count_get,
    .control = _hwtimer_control
};

static const struct rt_hwtimer_info _hwtimer_info = {
    .maxfreq = 1000000UL,
    .minfreq = 1000000UL,
    .maxcnt = 0xFFFF,
    .cntmode = HWTIMER_MODE_PERIOD
};

#ifdef BSP_USING_TIMER0
static _timer_t timer0 = {.name = "timer0"};
#endif /* BSP_USING_TIMER0 */
#ifdef BSP_USING_TIMER1
static _timer_t timer1 = {.name = "timer1" };
#endif /* BSP_USING_TIMER1 */
#ifdef BSP_USING_TIMER2
static _timer_t timer2 = {.name = "timer2"};
#endif /* BSP_USING_TIMER2 */
#ifdef BSP_USING_TIMER3
static _timer_t timer3 = {.name = "timer3" };
#endif /* BSP_USING_TIMER3 */

static _timer_t *_timer_obj[] = {
#ifdef BSP_USING_TIMER0
        &timer0,
#endif  /* BSP_USING_TIMER0 */
#ifdef BSP_USING_TIMER1
        &timer1,
#endif /* BSP_USING_TIMER1 */
#ifdef BSP_USING_TIMER2
        &timer2,
#endif  /* BSP_USING_TIMER2 */
#ifdef BSP_USING_TIMER3
        &timer3,
#endif /* BSP_USING_TIMER3 */
};

static int64_t _hwtmr_isr(alarm_id_t id, void *user_data)
{
    _timer_t *_tmr = rt_container_of(id, _timer_t, alarm_id);
    rt_device_hwtimer_isr(&_tmr->timer);
    return RT_TRUE;
}

static bool _repeat_timer_isr(struct repeating_timer *t)
{
    _timer_t *_tmr = rt_container_of(t, _timer_t, repeat_timer);
    rt_device_hwtimer_isr(&_tmr->timer);
    return RT_TRUE;
}

static void _hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
}

static rt_err_t _hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);

    if(mode == HWTIMER_MODE_ONESHOT)
        _tmr->alarm_id = add_alarm_in_us(cnt, _hwtmr_isr, RT_NULL, RT_TRUE);
    else
        add_repeating_timer_us(cnt, _repeat_timer_isr, RT_NULL, &_tmr->repeat_timer);

    return RT_EOK;
}

static void _hwtimer_stop(rt_hwtimer_t *timer)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);
    if(timer->mode == HWTIMER_MODE_ONESHOT)
        cancel_alarm(_tmr->alarm_id);
    else
        cancel_repeating_timer(&_tmr->repeat_timer);
}

static rt_uint32_t _hwtimer_count_get(rt_hwtimer_t *timer)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);

    return timer_hw->alarm[_tmr->alarm_id];
}

static rt_err_t _hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
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
        _hwtimer_stop(timer);
        break;
    }

    return err;
}

int rt_hw_hwtimer_init(void)
{
    int ret = RT_EOK;

    for (uint32_t i = 0; i < sizeof(_timer_obj) / sizeof(_timer_obj[0]); i++)
    {
        _timer_obj[i]->timer.info = &_hwtimer_info;
        _timer_obj[i]->timer.ops = &_hwtimer_ops;
        ret = rt_device_hwtimer_register(&_timer_obj[i]->timer, _timer_obj[i]->name, _timer_obj[i]);
        if (ret != RT_EOK)
        {
            LOG_E("%s register failed", _timer_obj[i]->name);
        }
    }

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);
#endif /* BSP_USING_HWTIMER */
