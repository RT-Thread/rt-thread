/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author           Notes
 * 2023-10-30       ChuShicheng      first version
 */

#include "drv_timer.h"
#include "board.h"

#ifdef BSP_USING_CLOCK_TIMER

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.CLOCK_TIMER"

typedef struct _timer
{
    char *name;
    struct repeating_timer repeat_timer;
    alarm_id_t alarm_id;
    rt_clock_timer_t timer;
}_timer_t;

static void _clock_timer_init(rt_clock_timer_t *timer, rt_uint32_t state);
static rt_err_t _clock_timer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode);
static void _clock_timer_stop(rt_clock_timer_t *timer);
static rt_uint32_t _clock_timer_count_get(rt_clock_timer_t *timer);
static rt_err_t _clock_timer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args);
static int64_t _hwtmr_isr(alarm_id_t id, void *user_data);

static const struct rt_clock_timer_ops _clock_timer_ops = {
    .init = _clock_timer_init,
    .start = _clock_timer_start,
    .stop = _clock_timer_stop,
    .count_get = _clock_timer_count_get,
    .control = _clock_timer_control
};

static const struct rt_clock_timer_info _clock_timer_info = {
    .maxfreq = 1000000UL,
    .minfreq = 1000000UL,
    .maxcnt = 0xFFFF,
    .cntmode = CLOCK_TIMER_MODE_PERIOD
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
    rt_clock_timer_isr(&_tmr->timer);
    return RT_TRUE;
}

static bool _repeat_timer_isr(struct repeating_timer *t)
{
    _timer_t *_tmr = rt_container_of(t, _timer_t, repeat_timer);
    rt_clock_timer_isr(&_tmr->timer);
    return RT_TRUE;
}

static void _clock_timer_init(rt_clock_timer_t *timer, rt_uint32_t state)
{
}

static rt_err_t _clock_timer_start(rt_clock_timer_t *timer, rt_uint32_t cnt, rt_clock_timer_mode_t mode)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);

    if(mode == CLOCK_TIMER_MODE_ONESHOT)
        _tmr->alarm_id = add_alarm_in_us(cnt, _hwtmr_isr, RT_NULL, RT_TRUE);
    else
        add_repeating_timer_us(cnt, _repeat_timer_isr, RT_NULL, &_tmr->repeat_timer);

    return RT_EOK;
}

static void _clock_timer_stop(rt_clock_timer_t *timer)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);
    if(timer->mode == CLOCK_TIMER_MODE_ONESHOT)
        cancel_alarm(_tmr->alarm_id);
    else
        cancel_repeating_timer(&_tmr->repeat_timer);
}

static rt_uint32_t _clock_timer_count_get(rt_clock_timer_t *timer)
{
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);

    return timer_hw->alarm[_tmr->alarm_id];
}

static rt_err_t _clock_timer_control(rt_clock_timer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    _timer_t *_tmr = rt_container_of(timer, _timer_t, timer);

    switch (cmd)
    {
    case CLOCK_TIMER_CTRL_FREQ_SET:
        err = -RT_ERROR;
        break;
    case CLOCK_TIMER_CTRL_INFO_GET:
        *(rt_clock_timer_t*)args = _tmr->timer;
        break;
    case CLOCK_TIMER_CTRL_MODE_SET:
        _tmr->timer.mode = *(rt_uint32_t*)args;
        break;
    case CLOCK_TIMER_CTRL_STOP:
        _clock_timer_stop(timer);
        break;
    }

    return err;
}

int rt_hw_clock_timer_init(void)
{
    int ret = RT_EOK;

    for (uint32_t i = 0; i < sizeof(_timer_obj) / sizeof(_timer_obj[0]); i++)
    {
        _timer_obj[i]->timer.info = &_clock_timer_info;
        _timer_obj[i]->timer.ops = &_clock_timer_ops;
        ret = rt_clock_timer_register(&_timer_obj[i]->timer, _timer_obj[i]->name, _timer_obj[i]);
        if (ret != RT_EOK)
        {
            LOG_E("%s register failed", _timer_obj[i]->name);
        }
    }

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_clock_timer_init);
#endif /* BSP_USING_CLOCK_TIMER */
