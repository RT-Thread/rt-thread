/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author           Notes
 * 2023-04-01       wcx1024979076    first version
 */

#include "drv_hwtimer.h"
#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_HWTIMER

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.HWTIMER"


typedef struct _gptimer
{
    const char *name;
    rt_hwtimer_t timer;
    struct bflb_device_s *bflb_timer;
} _gptimer_t;

static void _hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state);
static rt_err_t _hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode);
static void _hwtimer_stop(rt_hwtimer_t *timer);
static rt_uint32_t _hwtimer_count_get(rt_hwtimer_t *timer);
static rt_err_t _hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args);

static void _hwtmr_isr(_gptimer_t *gptmr);

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
    .maxcnt = 0xFFFFFFFFUL,
    .cntmode = HWTIMER_MODE_PERIOD
};

#ifdef BSP_USING_TIMER0
static _gptimer_t timer0 = {.name = "timer0"};
#endif /* BSP_USING_TIMER0 */
#ifdef BSP_USING_TIMER1
static _gptimer_t timer1 = {.name = "timer1" };
#endif /* BSP_USING_TIMER1 */

static _gptimer_t *s_gptimers[] = {
#ifdef BSP_USING_TIMER0
       &timer0,
#endif  /* BSP_USING_TIMER0 */
#ifdef BSP_USING_TIMER1
       &timer1,
#endif /* BSP_USING_TIMER1 */
    };

#ifdef BSP_USING_TIMER0
void timer0_isr(int irq, void *arg)
{
    _hwtmr_isr(&timer0);
}
#endif  /* BSP_USING_TIMER0 */

#ifdef BSP_USING_TIMER1
void timer1_isr(int irq, void *arg)
{
    _hwtmr_isr(&timer1);
}
#endif  /* BSP_USING_TIMER1 */

static void _hwtmr_isr(_gptimer_t *timer)
{
    bool hwtmr_stat = bflb_timer_get_compint_status(timer->bflb_timer, TIMER_COMP_ID_0);
    if (hwtmr_stat)
    {
        rt_device_hwtimer_isr(&timer->timer);
        bflb_timer_compint_clear(timer->bflb_timer, TIMER_COMP_ID_0);
    }
}

static void _hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    _gptimer_t *_gptmr = (_gptimer_t*)timer->parent.user_data;

    struct bflb_timer_config_s cfg;
    cfg.counter_mode = TIMER_COUNTER_MODE_PROLOAD;
    cfg.clock_source = TIMER_CLKSRC_XTAL;
    cfg.clock_div = 40;
    cfg.trigger_comp_id = TIMER_COMP_ID_0;
    cfg.comp0_val = 0;
    cfg.comp1_val = 0;
    cfg.comp2_val = 0;
    cfg.preload_val = 0;

    bflb_timer_init(_gptmr->bflb_timer, &cfg);
}

static rt_err_t _hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    _gptimer_t *_gptmr = (_gptimer_t*) timer->parent.user_data;

    struct bflb_timer_config_s cfg;
    if(mode == HWTIMER_MODE_ONESHOT)
        cfg.counter_mode = TIMER_COUNTER_MODE_UP;
    else
        cfg.counter_mode = TIMER_COUNTER_MODE_PROLOAD;
    cfg.clock_source = TIMER_CLKSRC_XTAL;
    cfg.clock_div = 40;
    cfg.trigger_comp_id = TIMER_COMP_ID_0;
    cfg.comp0_val = cnt;
    cfg.comp1_val = cnt;
    cfg.comp2_val = cnt;
    cfg.preload_val = 0;

    bflb_timer_init(_gptmr->bflb_timer, &cfg);
    bflb_irq_enable(_gptmr->bflb_timer->irq_num);
    bflb_timer_start(_gptmr->bflb_timer);

    return RT_EOK;
}

static void _hwtimer_stop(rt_hwtimer_t *timer)
{
    _gptimer_t *_gptmr = (_gptimer_t*)timer->parent.user_data;
    bflb_timer_stop(_gptmr->bflb_timer);
}

static rt_uint32_t _hwtimer_count_get(rt_hwtimer_t *timer)
{
    _gptimer_t *_gptmr = (_gptimer_t*)timer->parent.user_data;

    rt_uint32_t current_cnt = bflb_timer_get_countervalue(_gptmr->bflb_timer);

    return current_cnt;
}

static rt_err_t _hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    _gptimer_t *_gptmr = (_gptimer_t*) timer->parent.user_data;
    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        err = -RT_ERROR;
        break;
    case HWTIMER_CTRL_INFO_GET:
        *(rt_hwtimer_t*)args = _gptmr->timer;
        break;
    case HWTIMER_CTRL_MODE_SET:
        _gptmr->timer.mode = *(rt_uint32_t*)args;
        break;
    case HWTIMER_CTRL_STOP:
        bflb_timer_stop(_gptmr->bflb_timer);
        break;
    }

    return err;
}


int rt_hw_hwtimer_init(void)
{
    int ret = RT_EOK;
    for (uint32_t i = 0; i < sizeof(s_gptimers) / sizeof(s_gptimers[0]); i++)
    {
        s_gptimers[i]->timer.info = &_hwtimer_info;
        s_gptimers[i]->timer.ops = &_hwtimer_ops;
        s_gptimers[i]->bflb_timer = bflb_device_get_by_name(s_gptimers[i]->name);
        ret = rt_device_hwtimer_register(&s_gptimers[i]->timer, s_gptimers[i]->name, s_gptimers[i]);
        if (ret != RT_EOK)
        {
            LOG_E("%s register failed", s_gptimers[i]->name);
        }
    }

#ifdef BSP_USING_TIMER0
    bflb_irq_attach(bflb_device_get_by_name("timer0")->irq_num, timer0_isr, NULL);
#endif  /* BSP_USING_TIMER0 */

#ifdef BSP_USING_TIMER1
    bflb_irq_attach(bflb_device_get_by_name("timer1")->irq_num, timer1_isr, NULL);
#endif  /* BSP_USING_TIMER1 */

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);
#endif /* BSP_USING_HWTIMER */
