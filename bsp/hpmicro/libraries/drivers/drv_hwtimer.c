/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>
#ifdef RT_USING_HWTIMER

#include "drv_hwtimer.h"
#include "board.h"
#include "hpm_gptmr_drv.h"


typedef struct _hpm_gptimer
{
    GPTMR_Type *base;
    const char *name;
    rt_hwtimer_t timer;
    uint32_t channel;
    clock_name_t clock_name;
    int32_t irq_num;
} hpm_gptimer_t;

static void hpm_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state);
static rt_err_t hpm_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode);
static void hpm_hwtimer_stop(rt_hwtimer_t *timer);
static rt_uint32_t hpm_hwtimer_count_get(rt_hwtimer_t *timer);
static rt_err_t hpm_hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args);

static void hpm_hwtmr_isr(hpm_gptimer_t *gptmr);

static const struct rt_hwtimer_ops hpm_hwtimer_ops = {
        .init = hpm_hwtimer_init,
        .start = hpm_hwtimer_start,
        .stop = hpm_hwtimer_stop,
        .count_get = hpm_hwtimer_count_get,
        .control = hpm_hwtimer_control
};

static const struct rt_hwtimer_info hpm_hwtimer_info = {
        .maxfreq = 100000000UL,
        .minfreq = 93750UL,
        .maxcnt = 0xFFFFFFFFUL,
        .cntmode = HWTIMER_CNTMODE_UP
};


#ifdef BSP_USING_GPTMR0
static hpm_gptimer_t timer0 = {.name = "GPT0", .base = HPM_GPTMR0, .clock_name = clock_gptmr0, .irq_num = IRQn_GPTMR0 };
#endif
#ifdef BSP_USING_GPTMR1
static hpm_gptimer_t timer1 = {.name = "GPT1", .base = HPM_GPTMR1, .clock_name = clock_gptmr1, .irq_num = IRQn_GPTMR1 };
#endif
#ifdef BSP_USING_GPTMR2
static hpm_gptimer_t timer2 = {.name = "GPT2", .base = HPM_GPTMR2, .clock_name = clock_gptmr2, .irq_num = IRQn_GPTMR2 };
#endif
#ifdef BSP_USING_GPTMR3
static hpm_gptimer_t timer3 = {.name = "GPT3", .base = HPM_GPTMR3, .clock_name = clock_gptmr3, .irq_num = IRQn_GPTMR3 };
#endif
#ifdef BSP_USING_GPTMR4
static hpm_gptimer_t timer4 = {.name = "GPT4", .base = HPM_GPTMR4, .clock_name = clock_gptmr4, .irq_num = IRQn_GPTMR4 };
#endif
#ifdef BSP_USING_GPTMR5
static hpm_gptimer_t timer5 = {.name = "GPT5", .base = HPM_GPTMR5, .clock_name = clock_gptmr5, .irq_num = IRQn_GPTMR5 };
#endif
#ifdef BSP_USING_GPTMR6
static hpm_gptimer_t timer6 = {.name = "GPT6", .base = HPM_GPTMR6, .clock_name = clock_gptmr6, .irq_num = IRQn_GPTMR6 };
#endif
#ifdef BSP_USING_GPTMR7
static hpm_gptimer_t timer7 = {.name = "GPT7", .base = HPM_GPTMR7, .clock_name = clock_gptmr7, .irq_num = IRQn_GPTMR7 };
#endif


static hpm_gptimer_t *s_gptimers[] = {
#ifdef BSP_USING_GPTMR0
       &timer0,
#endif
#ifdef BSP_USING_GPTMR1
       &timer1,
#endif
#ifdef BSP_USING_GPTMR2
       &timer2,
#endif
#ifdef BSP_USING_GPTMR3
       &timer3,
#endif
#ifdef BSP_USING_GPTMR4
       &timer4,
#endif
#ifdef BSP_USING_GPTMR5
       &timer5,
#endif
#ifdef BSP_USING_GPTMR6
       &timer6,
#endif
#ifdef BSP_USING_GPTMR7
       &timer7,
#endif
    };

#ifdef BSP_USING_GPTMR0
void gptmr0_isr(void)
{
    hpm_hwtmr_isr(&timer0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR0, gptmr0_isr);
#endif

#ifdef BSP_USING_GPTMR1
void gptmr1_isr(void)
{
    hpm_hwtmr_isr(&timer1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR1, gptmr1_isr);
#endif

#ifdef BSP_USING_GPTMR2
void gptmr2_isr(void)
{
    hpm_hwtmr_isr(&timer2);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR2, gptmr2_isr);
#endif

#ifdef BSP_USING_GPTMR3
void gptmr3_isr(void)
{
    hpm_hwtmr_isr(&timer3);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR3, gptmr3_isr);
#endif

#ifdef BSP_USING_GPTMR4
void gptmr4_isr(void)
{
    hpm_hwtmr_isr(&timer4);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR4, gptmr4_isr);
#endif

#ifdef BSP_USING_GPTMR5
void gptmr5_isr(void)
{
    hpm_hwtmr_isr(&timer5);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR5, gptmr5_isr);
#endif

#ifdef BSP_USING_GPTMR6
void gptmr6_isr(void)
{
    hpm_hwtmr_isr(&timer6);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR6, gptmr6_isr);
#endif

#ifdef BSP_USING_GPTMR7
void gptmr7_isr(void)
{
    hpm_hwtmr_isr(&timer7);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPTMR7, gptmr7_isr);
#endif

static void hpm_hwtmr_isr(hpm_gptimer_t *timer)
{
    uint32_t hwtmr_stat = gptmr_get_status(timer->base);
    if ((hwtmr_stat & GPTMR_CH_RLD_STAT_MASK(timer->channel)) != 0U)
    {
        rt_device_hwtimer_isr(&timer->timer);
        gptmr_clear_status(timer->base, GPTMR_CH_RLD_STAT_MASK(timer->channel));
    }
}

static void hpm_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    hpm_gptimer_t *hpm_gptmr = (hpm_gptimer_t*)timer->parent.user_data;
    GPTMR_Type *base = hpm_gptmr->base;
    gptmr_channel_config_t config;

    if (state == 1)
    {
        hpm_gptmr->timer.freq = board_init_gptmr_clock(base);
        gptmr_channel_get_default_config(base, &config);
        gptmr_channel_config(base, hpm_gptmr->channel, &config, false);
    }
}

static rt_err_t hpm_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    hpm_gptimer_t *hpm_gptmr = (hpm_gptimer_t*) timer->parent.user_data;
    GPTMR_Type *base = hpm_gptmr->base;

    gptmr_channel_config_t config;
    gptmr_channel_get_default_config(base, &config);
    config.cmp[0] = 0;
    config.reload = cnt;

    timer->mode = mode;

    gptmr_channel_config(base, hpm_gptmr->channel, &config, true);

    gptmr_clear_status(base, 0xFU);
    gptmr_enable_irq(base, GPTMR_CH_RLD_IRQ_MASK(hpm_gptmr->channel));

    gptmr_channel_update_count(base, hpm_gptmr->channel, 0);
    gptmr_start_counter(base, hpm_gptmr->channel);

    intc_m_enable_irq_with_priority(hpm_gptmr->irq_num, 1);

    return RT_EOK;
}

static void hpm_hwtimer_stop(rt_hwtimer_t *timer)
{
    hpm_gptimer_t *hpm_gptmr = (hpm_gptimer_t*)timer->parent.user_data;
    GPTMR_Type *base = hpm_gptmr->base;

    gptmr_stop_counter(base, hpm_gptmr->channel);
}

static rt_uint32_t hpm_hwtimer_count_get(rt_hwtimer_t *timer)
{
    hpm_gptimer_t *hpm_gptmr = (hpm_gptimer_t*)timer->parent.user_data;
    GPTMR_Type *base = hpm_gptmr->base;

    rt_uint32_t current_cnt = gptmr_channel_get_counter(base, hpm_gptmr->channel, gptmr_counter_type_normal);

    return current_cnt;
}

static rt_err_t hpm_hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    hpm_gptimer_t *hpm_gptmr = (hpm_gptimer_t*) timer->parent.user_data;
    GPTMR_Type *base = hpm_gptmr->base;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        err = -RT_ERROR;
        break;
    case HWTIMER_CTRL_INFO_GET:
        *(rt_hwtimer_t*)args = hpm_gptmr->timer;
        break;
    case HWTIMER_CTRL_MODE_SET:
        hpm_gptmr->timer.mode = *(rt_uint32_t*)args;
        break;
    case HWTIMER_CTRL_STOP:
        gptmr_stop_counter(base, hpm_gptmr->channel);
        break;
    }

    return err;
}


int rt_hw_hwtimer_init(void)
{
    int ret = RT_EOK;

    for (uint32_t i = 0; i < ARRAY_SIZE(s_gptimers); i++)
    {
        s_gptimers[i]->timer.info = &hpm_hwtimer_info;
        s_gptimers[i]->timer.ops = &hpm_hwtimer_ops;
        ret = rt_device_hwtimer_register(&s_gptimers[i]->timer, s_gptimers[i]->name, s_gptimers[i]);
        if (ret != RT_EOK)
        {
            LOG_E("%s register failed\n", s_gptimers[i]->name);
        }
    }

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif /* BSP_USING_GPTMR */
