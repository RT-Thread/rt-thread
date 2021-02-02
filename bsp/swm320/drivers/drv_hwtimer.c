/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10    Zohar_Lee    first version
 * 2020-07-10    lik          format file
 */

#include "drv_hwtimer.h"

#ifdef RT_USING_HWTIMER
#ifdef BSP_USING_TIM

enum
{
#ifdef BSP_USING_TIM0
    TIM0_INDEX,
#endif
#ifdef BSP_USING_TIM1
    TIM1_INDEX,
#endif
#ifdef BSP_USING_TIM2
    TIM2_INDEX,
#endif
#ifdef BSP_USING_TIM3
    TIM3_INDEX,
#endif
#ifdef BSP_USING_TIM4
    TIM4_INDEX,
#endif
#ifdef BSP_USING_TIM5
    TIM5_INDEX,
#endif
};

static struct swm_hwtimer_cfg hwtimer_cfg[] =
    {
#ifdef BSP_USING_TIM0
        TIM0_CFG,
#endif
#ifdef BSP_USING_TIM1
        TIM1_CFG,
#endif
#ifdef BSP_USING_TIM2
        TIM2_CFG,
#endif
#ifdef BSP_USING_TIM3
        TIM3_CFG,
#endif
#ifdef BSP_USING_TIM4
        TIM4_CFG,
#endif
#ifdef BSP_USING_TIM5
        TIM5_CFG,
#endif
};

static struct swm_hwtimer hwtimer_drv[sizeof(hwtimer_cfg) / sizeof(hwtimer_cfg[0])] = {0};

static void swm_timer_init(struct rt_hwtimer_device *timer_device, rt_uint32_t state)
{
    struct swm_hwtimer_cfg *cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);

    if (state)
    {
        cfg = timer_device->parent.user_data;
        TIMR_Init(cfg->TIMRx, TIMR_MODE_TIMER, SystemCoreClock, 1);
        timer_device->freq = SystemCoreClock;
    }
}

static rt_err_t swm_timer_start(rt_hwtimer_t *timer_device, rt_uint32_t cnt, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    struct swm_hwtimer_cfg *cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);
    cfg = timer_device->parent.user_data;

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        timer_device->mode = HWTIMER_MODE_ONESHOT;
    }
    else
    {
        timer_device->mode = HWTIMER_MODE_PERIOD;
    }
    TIMR_SetPeriod(cfg->TIMRx, cnt);
    TIMR_Stop(cfg->TIMRx);
    TIMR_Start(cfg->TIMRx);

    return result;
}

static void swm_timer_stop(rt_hwtimer_t *timer_device)
{
    struct swm_hwtimer_cfg *cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);
    cfg = timer_device->parent.user_data;

    /* stop timer */
    TIMR_Stop(cfg->TIMRx);
}

static rt_uint32_t swm_timer_count_get(rt_hwtimer_t *timer_device)
{
    struct swm_hwtimer_cfg *cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);
    cfg = timer_device->parent.user_data;

    return TIMR_GetCurValue(cfg->TIMRx);
}

static rt_err_t swm_timer_ctrl(rt_hwtimer_t *timer_device, rt_uint32_t cmd, void *args)
{
    struct swm_hwtimer_cfg *cfg = RT_NULL;
    rt_err_t result = RT_EOK;
    RT_ASSERT(timer_device != RT_NULL);
    RT_ASSERT(args != RT_NULL);
    cfg = timer_device->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        rt_uint32_t freq;
        freq = *(rt_uint32_t *)args;

        TIMR_Init(cfg->TIMRx, TIMR_MODE_TIMER, SystemCoreClock / freq, 1);
    }
    break;
    default:
    {
        result = -RT_ENOSYS;
    }
    break;
    }

    return result;
}

static const struct rt_hwtimer_info _info = TIM_DEV_INFO_CONFIG;

static struct rt_hwtimer_ops swm_hwtimer_ops =
    {
        .init = swm_timer_init,
        .start = swm_timer_start,
        .stop = swm_timer_stop,
        .count_get = swm_timer_count_get,
        .control = swm_timer_ctrl};

void rt_hw_hwtimer_isr(rt_hwtimer_t *timer_device)
{
    struct swm_hwtimer_cfg *cfg = RT_NULL;
    RT_ASSERT(timer_device != RT_NULL);
    cfg = timer_device->parent.user_data;

    TIMR_INTClr(cfg->TIMRx);
    rt_device_hwtimer_isr(timer_device);
}
#ifdef BSP_USING_TIM0
void TIMR0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_hwtimer_isr(&(hwtimer_drv[TIM0_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM0

#ifdef BSP_USING_TIM1
void TIMR1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_hwtimer_isr(&(hwtimer_drv[TIM1_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM1

#ifdef BSP_USING_TIM2
void TIMR2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_hwtimer_isr(&(hwtimer_drv[TIM2_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM2

#ifdef BSP_USING_TIM3
void TIMR3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_hwtimer_isr(&(hwtimer_drv[TIM3_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM3

#ifdef BSP_USING_TIM4
void TIMR4_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_hwtimer_isr(&(hwtimer_drv[TIM4_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM4

#ifdef BSP_USING_TIM5
void TIMR5_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    rt_hw_hwtimer_isr(&(hwtimer_drv[TIM5_INDEX].time_device));
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif //BSP_USING_TIM5

static int rt_hw_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(hwtimer_cfg) / sizeof(hwtimer_cfg[0]); i++)
    {
        hwtimer_drv[i].cfg = &hwtimer_cfg[i];
        hwtimer_drv[i].time_device.info = &_info;
        hwtimer_drv[i].time_device.ops = &swm_hwtimer_ops;
        if (rt_device_hwtimer_register(&hwtimer_drv[i].time_device, hwtimer_drv[i].cfg->name, hwtimer_drv[i].cfg) == RT_EOK)
        {
            ;
        }
        else
        {
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif /* BSP_USING_TIM */
#endif /* RT_USING_HWTIMER */
