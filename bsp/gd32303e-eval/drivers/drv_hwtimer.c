/*
 * Copyright (c) 2006-2023
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       		  	Notes
 * 2022-07-17     zengjianwei         	first version
 */

#include <board.h>
#include <drivers/hwtimer.h>
#include <rtdevice.h>
#include <rtthread.h>

//#define DRV_DEBUG
#define LOG_TAG "drv.hwtimer"
#include <rtdbg.h>

#ifdef RT_USING_HWTIMER

#define TIM_DEV_INFO_CONFIG                                                                                            \
    {                                                                                                                  \
        .maxfreq = 1000000, .minfreq = 2000, .maxcnt = 0xFFFF, .cntmode = HWTIMER_CNTMODE_UP,                          \
    }

typedef enum
{
#ifdef RT_USING_TIM0
    TIM0_INDEX,
#endif
#ifdef RT_USING_TIM1
    TIM1_INDEX,
#endif
#ifdef RT_USING_TIM2
    TIM2_INDEX,
#endif
#ifdef RT_USING_TIM3
    TIM3_INDEX,
#endif
#ifdef RT_USING_TIM4
    TIM4_INDEX,
#endif
#ifdef RT_USING_TIM5
    TIM5_INDEX,
#endif
#ifdef RT_USING_TIM6
    TIM6_INDEX,
#endif
#ifdef RT_USING_TIM7
    TIM7_INDEX,
#endif

#ifndef GD32F30X_HD
#ifdef RT_USING_TIM8
    TIM8_INDEX,
#endif
#ifdef RT_USING_TIM9
    TIM9_INDEX,
#endif
#ifdef RT_USING_TIM10
    TIM10_INDEX,
#endif
#ifdef RT_USING_TIM11
    TIM11_INDEX,
#endif
#ifdef RT_USING_TIM12
    TIM12_INDEX,
#endif
#ifdef RT_USING_TIM13
    TIM13_INDEX,
#endif
#endif
} TIM_INDEX;

/*
 * Copied from include/linux/...
 */

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member)                                                                                \
    ({                                                                                                                 \
        const typeof(((type *)0)->member) *__mptr = (ptr);                                                             \
        (type *)((char *)__mptr - offsetof(type, member));                                                             \
    })

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define list_entry(ptr, type, member) container_of(ptr, type, member)

typedef struct
{
    rt_uint32_t TimerX; // TIMER1~TIMER13
    IRQn_Type tim_irqn;
    char *name;
} TIM_HANDLE_S;

struct gd32_hwtimer
{
    rt_hwtimer_t time_device;
    TIM_HANDLE_S tim_handle;
};

static struct gd32_hwtimer gd32_hwtimer_obj[] = {
#ifdef RT_USING_TIM0
    {.tim_handle = {TIMER0, TIMER0_UP_IRQn, "timer0"}},
#endif

#ifdef RT_USING_TIM1
    {.tim_handle = {TIMER1, TIMER1_IRQn, "timer1"}},
#endif

#ifdef RT_USING_TIM2
    {.tim_handle = {TIMER2, TIMER2_IRQn, "timer2"}},
#endif

#ifdef RT_USING_TIM3
    {.tim_handle = {TIMER3, TIMER3_IRQn, "timer3"}},
#endif

#ifdef RT_USING_TIM4
    {.tim_handle = {TIMER4, TIMER4_IRQn, "timer4"}},
#endif

#ifdef RT_USING_TIM5
    {.tim_handle = {TIMER5, TIMER5_IRQn, "timer5"}},
#endif

#ifdef RT_USING_TIM6
    {.tim_handle = {TIMER6, TIMER6_IRQn, "timer6"}},
#endif

#ifdef RT_USING_TIM7
    {.tim_handle = {TIMER7, TIMER7_UP_IRQn, "timer7"}},
#endif

#ifndef GD32F30X_HD
#ifdef RT_USING_TIM8
    {.tim_handle = {TIMER8, TIMER0_BRK_TIMER8_IRQn, "timer8"}},
#endif

#ifdef RT_USING_TIM9
    {.tim_handle = {TIMER9, TIMER0_UP_TIMER9_IRQn, "timer9"}},
#endif

#ifdef RT_USING_TIM10
    {.tim_handle = {TIMER10, TIMER0_TRG_CMT_TIMER10_IRQn, "timer10"}},
#endif

#ifdef RT_USING_TIM11
    {.tim_handle = {TIMER11, TIMER7_BRK_TIMER11_IRQn, "timer11"}},
#endif

#ifdef RT_USING_TIM12
    {.tim_handle = {TIMER12, TIMER7_UP_TIMER12_IRQn, "timer12"}},
#endif

#ifdef RT_USING_TIM13
    {.tim_handle = {TIMER13, TIMER7_TRG_CMT_TIMER13_IRQn, "timer13"}},
#endif
#endif
};

static rcu_periph_enum hwtimer_timer_to_rcu(rt_uint32_t Timerx)
{
    switch (Timerx)
    {
#ifdef RT_USING_TIM0
    case TIMER0:
        return RCU_TIMER0;
#endif
#ifdef RT_USING_TIM1
    case TIMER1:
        return RCU_TIMER1;
#endif
#ifdef RT_USING_TIM2
    case TIMER2:
        return RCU_TIMER2;
#endif
#ifdef RT_USING_TIM3
    case TIMER3:
        return RCU_TIMER3;
#endif
#ifdef RT_USING_TIM4
    case TIMER4:
        return RCU_TIMER4;
#endif
#ifdef RT_USING_TIM5
    case TIMER5:
        return RCU_TIMER5;
#endif
#ifdef RT_USING_TIM6
    case TIMER6:
        return RCU_TIMER6;
#endif
#ifdef RT_USING_TIM7
    case TIMER7:
        return RCU_TIMER7;
#endif

#ifndef GD32F30X_HD
#ifdef RT_USING_TIM8
    case TIMER8:
        return RCU_TIMER8;
#endif
#ifdef RT_USING_TIM9
    case TIMER9:
        return RCU_TIMER9;
#endif
#ifdef RT_USING_TIM10
    case TIMER10:
        return RCU_TIMER10;
#endif
#ifdef RT_USING_TIM11
    case TIMER11:
        return RCU_TIMER11;
#endif
#ifdef RT_USING_TIM12
    case TIMER12:
        return RCU_TIMER12;
#endif
#ifdef RT_USING_TIM13
    case TIMER13:
        return RCU_TIMER13;
#endif
#endif

    default:
        LOG_E("Unsport timer periph!\n");
        return RCU_TIMER0;
    }
}

static void hw_timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    TIM_HANDLE_S *pTim = RT_NULL;
    // struct gd32_hwtimer *tim_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    if (state)
    {
        pTim = (TIM_HANDLE_S *)timer->parent.user_data;
        // tim_device = (struct gd32_hwtimer *)timer;

        /* set the TIMx priority */
        nvic_irq_enable(pTim->tim_irqn, 1, 0);

        rcu_periph_clock_enable(hwtimer_timer_to_rcu(pTim->TimerX));
        timer_deinit(pTim->TimerX);

        /* time init */
        timer_parameter_struct timer_initpara;
        timer_initpara.prescaler = 120 * 100 - 1;
        timer_initpara.counterdirection = TIMER_COUNTER_UP;
        timer_initpara.period = 0xffff;
        timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
        timer_init(pTim->TimerX, &timer_initpara);

        timer_counter_value_config(pTim->TimerX, 0);
        timer_update_source_config(pTim->TimerX, TIMER_UPDATE_SRC_REGULAR);
        timer_auto_reload_shadow_disable(pTim->TimerX);
        timer_single_pulse_mode_config(pTim->TimerX, TIMER_SP_MODE_SINGLE);

        /* enable the TIMx Interrupt */
        timer_interrupt_enable(pTim->TimerX, TIMER_INT_UP);
        /* clear interrupt flag */
        timer_interrupt_flag_clear(pTim->TimerX, TIMER_INT_FLAG_UP);
        timer_enable(pTim->TimerX);
        LOG_D("%s init success", pTim->name);
    }
}

static rt_err_t hw_timer_start(rt_hwtimer_t *timer, rt_uint32_t t, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    TIM_HANDLE_S *pTim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    pTim = (TIM_HANDLE_S *)timer->parent.user_data;

    /* set tim cnt */
    timer_counter_value_config(pTim->TimerX, 0);
    /* set tim arr */
    timer_autoreload_value_config(pTim->TimerX, t - 1);
    /* clear interrupt flag */
    timer_interrupt_flag_clear(pTim->TimerX, TIMER_INT_FLAG_UP);

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to single mode */
        timer_single_pulse_mode_config(pTim->TimerX, TIMER_SP_MODE_SINGLE);
    }
    else
    {
        LOG_D("TIMER_SP_MODE_REPETITIVE\n");
        timer_single_pulse_mode_config(pTim->TimerX, TIMER_SP_MODE_REPETITIVE);
    }

    /* start timer */
    /*if (HAL_TIM_Base_Start_IT(tim) != HAL_OK)
    {
        LOG_E("TIM start failed");
        result = -RT_ERROR;
    }*/
    timer_interrupt_enable(pTim->TimerX, TIMER_INT_UP);
    timer_enable(pTim->TimerX);

    return result;
}

static void hw_timer_stop(rt_hwtimer_t *timer)
{
    TIM_HANDLE_S *pTim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    pTim = (TIM_HANDLE_S *)timer->parent.user_data;

    /* stop timer */
    timer_interrupt_disable(pTim->TimerX, TIMER_INT_UP);
    timer_disable(pTim->TimerX);

    /* set tim cnt */
    timer_counter_value_config(pTim->TimerX, 0);
}

static rt_err_t hw_timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    TIM_HANDLE_S *pTim = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    pTim = (TIM_HANDLE_S *)timer->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET: {
        rt_uint32_t freq;
        rt_uint32_t psc;

        /* set timer frequence */
        freq = *((rt_uint32_t *)arg);
        psc = rcu_clock_freq_get(CK_SYS) / freq;

        timer_prescaler_config(pTim->TimerX, psc - 1, TIMER_PSC_RELOAD_NOW);

        /* Update frequency value */
        timer_event_software_generate(pTim->TimerX, TIMER_EVENT_SRC_UPG);
    }
    break;

    case HWTIMER_CTRL_MODE_SET: {
        rt_hwtimer_mode_t mode = *((rt_hwtimer_mode_t *)arg);
        if (HWTIMER_MODE_ONESHOT == mode)
        {
            timer_single_pulse_mode_config(pTim->TimerX, TIMER_SP_MODE_SINGLE);
        }
        else
        {
            timer_single_pulse_mode_config(pTim->TimerX, TIMER_SP_MODE_REPETITIVE);
        }
    }
    break;

    case HWTIMER_CTRL_INFO_GET: {
        struct rt_hwtimer_info *pTimer_info = (struct rt_hwtimer_info *)arg;
        pTimer_info->maxfreq = 0;
        pTimer_info->minfreq = 0;
        pTimer_info->maxcnt = 0;
        pTimer_info->cntmode = 1;
    }
    break;

    case HWTIMER_CTRL_STOP: {
        timer_interrupt_disable(pTim->TimerX, TIMER_INT_UP);
        timer_disable(pTim->TimerX);
    }
    break;

    default: {
        result = -RT_ENOSYS;
    }
    break;
    }

    return result;
}

static rt_uint32_t hw_timer_counter_get(rt_hwtimer_t *timer)
{
    TIM_HANDLE_S *pTim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    pTim = (TIM_HANDLE_S *)timer->parent.user_data;

    return timer_counter_read(pTim->TimerX);
}

static const struct rt_hwtimer_info _info = TIM_DEV_INFO_CONFIG;

static const struct rt_hwtimer_ops _ops = {
    .init = hw_timer_init,
    .start = hw_timer_start,
    .stop = hw_timer_stop,
    .count_get = hw_timer_counter_get,
    .control = hw_timer_ctrl,
};

#ifdef RT_USING_TIM0
void TIMER0_UP_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER0, TIMER_INT_FLAG_UP) == SET)
    {
        timer_interrupt_flag_clear(TIMER0, TIMER_INT_FLAG_UP);
        /* enter interrupt */
        rt_interrupt_enter();
        rt_device_hwtimer_isr(&gd32_hwtimer_obj[TIM0_INDEX].time_device);
        /* leave interrupt */
        rt_interrupt_leave();
    }
}
#endif

#ifdef RT_USING_TIM1
void TIMER1_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER1, TIMER_INT_FLAG_UP) == SET)
    {
        timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);
        /* enter interrupt */
        rt_interrupt_enter();
        rt_device_hwtimer_isr(&gd32_hwtimer_obj[TIM1_INDEX].time_device);
        /* leave interrupt */
        rt_interrupt_leave();
    }
}
#endif

#ifdef RT_USING_TIM2
void TIMER2_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER2, TIMER_INT_FLAG_UP) == SET)
    {
        timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_UP);
        /* enter interrupt */
        rt_interrupt_enter();
        rt_device_hwtimer_isr(&gd32_hwtimer_obj[TIM2_INDEX].time_device);
        /* leave interrupt */
        rt_interrupt_leave();
    }
}
#endif

#ifdef RT_USING_TIM3
void TIMER3_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER3, TIMER_INT_FLAG_UP) == SET)
    {
        timer_interrupt_flag_clear(TIMER3, TIMER_INT_FLAG_UP);
        /* enter interrupt */
        rt_interrupt_enter();
        rt_device_hwtimer_isr(&gd32_hwtimer_obj[TIM3_INDEX].time_device);
        /* leave interrupt */
        rt_interrupt_leave();
    }
}
#endif

#ifdef RT_USING_TIM4
void TIMER4_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER4, TIMER_INT_FLAG_UP) == SET)
    {
        timer_interrupt_flag_clear(TIMER4, TIMER_INT_FLAG_UP);
        /* enter interrupt */
        rt_interrupt_enter();
        rt_device_hwtimer_isr(&gd32_hwtimer_obj[TIM4_INDEX].time_device);
        /* leave interrupt */
        rt_interrupt_leave();
    }
}
#endif

#ifdef RT_USING_TIM5
void TIMER5_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER5, TIMER_INT_FLAG_UP) == SET)
    {
        timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);
        /* enter interrupt */
        rt_interrupt_enter();
        rt_device_hwtimer_isr(&gd32_hwtimer_obj[TIM5_INDEX].time_device);
        /* leave interrupt */
        rt_interrupt_leave();
    }
}
#endif

#ifdef RT_USING_TIM6
void TIMER6_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER6, TIMER_INT_FLAG_UP) == SET)
    {
        timer_interrupt_flag_clear(TIMER6, TIMER_INT_FLAG_UP);
        /* enter interrupt */
        rt_interrupt_enter();
        rt_device_hwtimer_isr(&gd32_hwtimer_obj[TIM6_INDEX].time_device);
        /* leave interrupt */
        rt_interrupt_leave();
    }
}
#endif

#ifdef RT_USING_TIM7
void TIMER7_UP_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER7, TIMER_INT_FLAG_UP) == SET)
    {
        timer_interrupt_flag_clear(TIMER7, TIMER_INT_FLAG_UP);
        /* enter interrupt */
        rt_interrupt_enter();
        rt_device_hwtimer_isr(&gd32_hwtimer_obj[TIM7_INDEX].time_device);
        /* leave interrupt */
        rt_interrupt_leave();
    }
}
#endif

static int gd32_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(gd32_hwtimer_obj) / sizeof(gd32_hwtimer_obj[0]); i++)
    {
        gd32_hwtimer_obj[i].time_device.info = &_info;
        gd32_hwtimer_obj[i].time_device.ops = &_ops;
        if (rt_device_hwtimer_register(&gd32_hwtimer_obj[i].time_device, gd32_hwtimer_obj[i].tim_handle.name,
                                       &gd32_hwtimer_obj[i].tim_handle) == RT_EOK)
        {
            LOG_D("%s register success", gd32_hwtimer_obj[i].tim_handle.name);
        }
        else
        {
            LOG_E("%s register failed", gd32_hwtimer_obj[i].tim_handle.name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(gd32_hwtimer_init);

#endif /* RT_USING_HWTIMER */
