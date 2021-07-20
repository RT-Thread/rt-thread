/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "bcm283x.h"
#include "drv_timer.h"
#include <drivers/hwtimer.h>
#include "cp15.h"

static void rt_systimer_init(rt_hwtimer_t *hwtimer, rt_uint32_t state)
{
    if (state == 0)
        hwtimer->ops->stop(hwtimer);
}

static rt_err_t rt_systimer_start(rt_hwtimer_t *hwtimer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    rt_err_t result = RT_EOK;
    rt_systimer_t *timer = (rt_systimer_t *)hwtimer->parent.user_data;
    int timer_id = timer->timer_id;
    if (mode == HWTIMER_MODE_PERIOD)
        timer->cnt = cnt;
    else
        timer->cnt = 0; 
    __DSB();
    if (timer_id == 1)
    {
        rt_hw_interrupt_umask(IRQ_SYSTIMER_MATCH_1);   
        STIMER_C1 = STIMER_CLO + cnt;
    } 
    else if (timer_id == 3)
    {
        rt_hw_interrupt_umask(IRQ_SYSTIMER_MATCH_3);   
        STIMER_C3 = STIMER_CLO + cnt;
    }
    else    
        result = -RT_ERROR;
    __DSB();
         
    return result;
}

static void rt_systimer_stop(rt_hwtimer_t *hwtimer)
{
    rt_systimer_t *timer = (rt_systimer_t *)hwtimer->parent.user_data;
    int timer_id = timer->timer_id;
    if (timer_id == 1)
        rt_hw_interrupt_mask(IRQ_SYSTIMER_MATCH_1);      
    else if (timer_id == 3)
        rt_hw_interrupt_mask(IRQ_SYSTIMER_MATCH_3); 
 
}

static rt_err_t rt_systimer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    /* The frequency value is an immutable value. */
    if (cmd == HWTIMER_CTRL_FREQ_SET)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ENOSYS;
    }
}

const static struct rt_hwtimer_ops systimer_ops = 
{
    rt_systimer_init,
    rt_systimer_start,
    rt_systimer_stop,
    RT_NULL,
    rt_systimer_ctrl
};

void rt_device_systimer_isr(int vector, void *param)
{
    rt_hwtimer_t *hwtimer = (rt_hwtimer_t *) param;
    rt_systimer_t *timer = (rt_systimer_t *)hwtimer->parent.user_data;
    RT_ASSERT(timer != RT_NULL);
    int timer_id = timer->timer_id;

    __DSB();
    if (timer_id == 1)
    {
        STIMER_CS = 0x2;
        STIMER_C1 = STIMER_CLO + timer->cnt;               
    }   
    else if (timer_id == 3)
    {
        STIMER_CS = 0x8;
        STIMER_C3 = STIMER_CLO + timer->cnt;                 
    }
    
    __DSB();
    rt_device_hwtimer_isr(hwtimer);
}
    
static struct rt_hwtimer_device _hwtimer1;
static struct rt_hwtimer_device _hwtimer3;
static struct rt_systimer_device _systimer1;
static struct rt_systimer_device _systimer3;

static const struct rt_hwtimer_info _info =
{
    1000000,            /* the maxinum count frequency can be set */
    1000000,            /* the maxinum count frequency can be set */
    0xFFFFFFFF,         /* the maximum counter value */
    HWTIMER_CNTMODE_UP  /* count mode (inc/dec) */
};

int rt_hw_systimer_init(void)
{
#ifdef RT_USING_SYSTIMER1
    _systimer1.timer_id =1;
    _hwtimer1.ops = &systimer_ops;
    _hwtimer1.info = &_info;
    rt_device_hwtimer_register(&_hwtimer1, "timer1",&_systimer1);
    rt_hw_interrupt_install(IRQ_SYSTIMER_MATCH_1, rt_device_systimer_isr, &_hwtimer1, "systimer1");
    rt_hw_interrupt_umask(IRQ_SYSTIMER_MATCH_1);
#endif

#ifdef RT_USING_SYSTIMER3
    _systimer3.timer_id =3;
    _hwtimer3.ops = &systimer_ops;
    _hwtimer3.info = &_info;
    rt_device_hwtimer_register(&_hwtimer3, "timer3",&_systimer3);
    rt_hw_interrupt_install(IRQ_SYSTIMER_MATCH_3, rt_device_systimer_isr, &_hwtimer3, "systimer3");
    
#endif

    return 0;
}
