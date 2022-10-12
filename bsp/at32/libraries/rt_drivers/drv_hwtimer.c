/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include "board.h"
#include "drv_hwtimer.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.hwtimer"
#include <drv_log.h>

#ifdef BSP_USING_HWTIMER

enum
{
#ifdef BSP_USING_HWTMR1
    TMR1_INDEX,
#endif

#ifdef BSP_USING_HWTMR2
    TMR2_INDEX,
#endif

#ifdef BSP_USING_HWTMR3
    TMR3_INDEX,
#endif

#ifdef BSP_USING_HWTMR4
    TMR4_INDEX,
#endif

#ifdef BSP_USING_HWTMR5
    TMR5_INDEX,
#endif

#ifdef BSP_USING_HWTMR6
    TMR6_INDEX,
#endif

#ifdef BSP_USING_HWTMR7
    TMR7_INDEX,
#endif

#ifdef BSP_USING_HW_TMR8
    TMR8_INDEX,
#endif

#ifdef BSP_USING_HWTMR9
    TMR9_INDEX,
#endif

#ifdef BSP_USING_HWTMR10
    TMR10_INDEX,
#endif

#ifdef BSP_USING_HWTMR11
    TMR11_INDEX,
#endif

#ifdef BSP_USING_HWTMR12
    TMR12_INDEX,
#endif

#ifdef BSP_USING_HWTMR13
    TMR13_INDEX,
#endif

#ifdef BSP_USING_HWTMR14
    TMR14_INDEX,
#endif

#ifdef BSP_USING_HWTMR15
    TMR15_INDEX,
#endif
};

struct at32_hwtimer
{
    rt_hwtimer_t  tmr_device;
    tmr_type*     tmr_x;
    IRQn_Type     tmr_irqn;
    char          *name;
};

static struct at32_hwtimer at32_hwtimer_obj[] =
{
#ifdef BSP_USING_HWTMR1
    TMR1_CONFIG,
#endif

#ifdef BSP_USING_HWTMR2
    TMR2_CONFIG,
#endif

#ifdef BSP_USING_HWTMR3
    TMR3_CONFIG,
#endif

#ifdef BSP_USING_HWTMR4
    TMR4_CONFIG,
#endif

#ifdef BSP_USING_HWTMR5
    TMR5_CONFIG,
#endif

#ifdef BSP_USING_HWTMR6
    TMR6_CONFIG,
#endif

#ifdef BSP_USING_HWTMR7
    TMR7_CONFIG,
#endif

#ifdef BSP_USING_HWTMR8
    TMR8_CONFIG,
#endif

#ifdef BSP_USING_HWTMR9
    TMR9_CONFIG,
#endif

#ifdef BSP_USING_HWTMR10
    TMR10_CONFIG,
#endif

#ifdef BSP_USING_HWTMR11
    TMR11_CONFIG,
#endif

#ifdef BSP_USING_HWTMR12
    TMR12_CONFIG,
#endif

#ifdef BSP_USING_HWTMR13
    TMR13_CONFIG,
#endif

#ifdef BSP_USING_HWTMR14
    TMR14_CONFIG,
#endif

#ifdef BSP_USING_HWTMR15
    TMR15_CONFIG,
#endif
};

static void tmr_pclk_get(rt_uint32_t *pclk1_doubler, rt_uint32_t *pclk2_doubler)
{
    crm_clocks_freq_type  clocks_struct;

    *pclk1_doubler = 1;
    *pclk2_doubler = 1;

    crm_clocks_freq_get(&clocks_struct);

    if(clocks_struct.ahb_freq != clocks_struct.apb1_freq)
    {
        *pclk1_doubler = 2;
    }

    if(clocks_struct.ahb_freq != clocks_struct.apb2_freq)
    {
        *pclk2_doubler = 2;
    }
}

static void at32_timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    crm_clocks_freq_type clocks_struct;
    rt_uint32_t pclk1_doubler = 0, pclk2_doubler = 0;
    rt_uint32_t prescaler_value = 0, tmr_clock = 0;
    tmr_type *tmr_x = RT_NULL;
    struct at32_hwtimer *tmr_device = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    if (state)
    {
        tmr_x = (tmr_type *)timer->parent.user_data;
        tmr_device = (struct at32_hwtimer *)timer;

        /* timer clock enable */
        at32_msp_hwtmr_init(tmr_x);

        /* get timer clock */
        tmr_pclk_get(&pclk1_doubler, &pclk2_doubler);
        crm_clocks_freq_get(&clocks_struct);

        if(
#if defined (TMR1)
        (tmr_x == TMR1)
#endif
#if defined (TMR8)
        || (tmr_x == TMR8)
#endif
#if defined (TMR9)
        || (tmr_x == TMR9)
#endif
#if defined (TMR10)
        || (tmr_x == TMR10)
#endif
#if defined (TMR11)
        || (tmr_x == TMR11)
#endif
        )
        {
            tmr_clock = clocks_struct.apb2_freq * pclk2_doubler;
        }
        else
        {
            tmr_clock = clocks_struct.apb1_freq * pclk1_doubler;
        }
        /* set timer clock is 1mhz */
        prescaler_value = (uint32_t)(tmr_clock / 10000) - 1;
        tmr_base_init(tmr_x, 10000 - 1, prescaler_value);
        tmr_clock_source_div_set(tmr_x, TMR_CLOCK_DIV1);
        tmr_repetition_counter_set(tmr_x, 0);

        if (timer->info->cntmode == HWTIMER_CNTMODE_UP)
        {
            tmr_cnt_dir_set(tmr_x, TMR_COUNT_UP);
        }
        else
        {
            tmr_cnt_dir_set(tmr_x, TMR_COUNT_DOWN);
        }

        /* enable the timer global interrupt and clear flag */
        nvic_irq_enable(tmr_device->tmr_irqn, 2, 0);

        tmr_interrupt_enable(tmr_x, TMR_OVF_INT, TRUE);
        tmr_flag_clear(tmr_x, TMR_OVF_INT);

        LOG_D("%s init success", tmr_device->name);
    }
}

static rt_err_t at32_timer_start(rt_hwtimer_t *timer, rt_uint32_t pr, rt_hwtimer_mode_t opmode)
{
    rt_err_t result = RT_EOK;
    tmr_type *tmr_x = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    tmr_x = (tmr_type *)timer->parent.user_data;

    /* set tmr_x count */
    tmr_counter_value_set(tmr_x, 0);
    /* set tmr_x period register */
    tmr_period_value_set(tmr_x, pr - 1);

    if (opmode == HWTIMER_MODE_ONESHOT)
    {
        /* set timer to one cycle mode */
        tmr_one_cycle_mode_enable(tmr_x, TRUE);
    }
    else
    {
        /* set timer to period mode */
        tmr_one_cycle_mode_enable(tmr_x, FALSE);
    }

    /* start timer */
    tmr_counter_enable(tmr_x, TRUE);

    return result;
}

static void at32_timer_stop(rt_hwtimer_t *timer)
{
    tmr_type *tmr_x = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    tmr_x = (tmr_type *)timer->parent.user_data;

    /* stop timer */
    tmr_counter_enable(tmr_x, FALSE);

    /* set tmr_x count */
    tmr_counter_value_set(tmr_x, 0);
}

static rt_uint32_t at32_timer_counter_get(rt_hwtimer_t *timer)
{
    tmr_type *tmr_x = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tmr_x = (tmr_type *)timer->parent.user_data;

    return tmr_counter_value_get(tmr_x);
}

static rt_err_t at32_timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    crm_clocks_freq_type clocks_struct;
    tmr_type *tmr_x = RT_NULL;
    rt_err_t result = RT_EOK;
    rt_uint32_t pclk1_doubler = 0, pclk2_doubler = 0, tmr_clock = 0;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    tmr_x = (tmr_type *)timer->parent.user_data;

    switch(cmd)
    {
        case HWTIMER_CTRL_FREQ_SET:
        {
            rt_uint32_t freq;
            rt_uint16_t val;

            /* get timer frequence */
            freq = *((rt_uint32_t *)arg);

            /* get timer clock */
            tmr_pclk_get(&pclk1_doubler, &pclk2_doubler);
            crm_clocks_freq_get(&clocks_struct);
            if(
#if defined (TMR1)
            (tmr_x == TMR1)
#endif
#if defined (TMR8)
            || (tmr_x == TMR8)
#endif
#if defined (TMR9)
            || (tmr_x == TMR9)
#endif
#if defined (TMR10)
            || (tmr_x == TMR10)
#endif
#if defined (TMR11)
            || (tmr_x == TMR11)
#endif
            )
            {
                tmr_clock = clocks_struct.apb2_freq * pclk2_doubler;
            }
            else
            {
                tmr_clock = clocks_struct.apb1_freq * pclk1_doubler;
            }
            /* set div value */
            val = tmr_clock / freq;

            tmr_div_value_set(tmr_x, val - 1);
            tmr_event_sw_trigger(tmr_x, TMR_OVERFLOW_SWTRIG);
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

static const struct rt_hwtimer_info _info = TMR_DEV_INFO_CONFIG;
static const struct rt_hwtimer_ops _ops =
{
    .init      = at32_timer_init,
    .start     = at32_timer_start,
    .stop      = at32_timer_stop,
    .count_get = at32_timer_counter_get,
    .control   = at32_timer_ctrl,
};

#ifdef BSP_USING_HWTMR2
void TMR2_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(tmr_flag_get(TMR2, TMR_OVF_FLAG) == SET)
    {
        rt_device_hwtimer_isr(&at32_hwtimer_obj[TMR2_INDEX].tmr_device);
        tmr_flag_clear(TMR2, TMR_OVF_FLAG);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTMR3
void TMR3_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(tmr_flag_get(TMR3, TMR_OVF_FLAG) == SET)
    {
        rt_device_hwtimer_isr(&at32_hwtimer_obj[TMR3_INDEX].tmr_device);
        tmr_flag_clear(TMR3, TMR_OVF_FLAG);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTMR4
void TMR4_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(tmr_flag_get(TMR4, TMR_OVF_FLAG) == SET)
    {
        rt_device_hwtimer_isr(&at32_hwtimer_obj[TMR4_INDEX].tmr_device);
        tmr_flag_clear(TMR4, TMR_OVF_FLAG);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HWTMR5
void TMR5_GLOBAL_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if(tmr_flag_get(TMR5, TMR_OVF_FLAG) == SET)
    {
        rt_device_hwtimer_isr(&at32_hwtimer_obj[TMR5_INDEX].tmr_device);
        tmr_flag_clear(TMR5, TMR_OVF_FLAG);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static int rt_hw_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(at32_hwtimer_obj) / sizeof(at32_hwtimer_obj[0]); i++)
    {
        at32_hwtimer_obj[i].tmr_device.info = &_info;
        at32_hwtimer_obj[i].tmr_device.ops  = &_ops;
        if (rt_device_hwtimer_register(&at32_hwtimer_obj[i].tmr_device, at32_hwtimer_obj[i].name, at32_hwtimer_obj[i].tmr_x) == RT_EOK)
        {
            LOG_D("%s register success", at32_hwtimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", at32_hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif /* BSP_USING_HWTIMER */
