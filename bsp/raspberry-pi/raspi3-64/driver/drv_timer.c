/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include "drv_timer.h"
#include "interrupt.h"
#include "raspi.h"

#ifdef BSP_USING_SYSTIMER

static void raspi_systimer_init(rt_hwtimer_t *hwtimer, rt_uint32_t state)
{
    if (state == 0)
        hwtimer->ops->stop(hwtimer);
}

static rt_err_t raspi_systimer_start(rt_hwtimer_t *hwtimer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    rt_err_t result = RT_EOK;
    rt_systimer_t *timer = (rt_systimer_t *)hwtimer->parent.user_data;
    int timer_id = timer->timer_id;

    if (mode == HWTIMER_MODE_PERIOD)
        timer->cnt = cnt;
    else
        timer->cnt = 0;

    __sync_synchronize();
    if (timer_id == 1)
    {
        rt_hw_interrupt_umask(IRQ_SYSTEM_TIMER_1);
        STIMER_C1 = STIMER_CLO + cnt;
    }
    else if (timer_id == 3)
    {
        rt_hw_interrupt_umask(IRQ_SYSTEM_TIMER_3);
        STIMER_C3 = STIMER_CLO + cnt;
    }
    else
        result = -RT_ERROR;

    __sync_synchronize();

    return result;
}

static void raspi_systimer_stop(rt_hwtimer_t *hwtimer)
{
    rt_systimer_t *timer = (rt_systimer_t *)hwtimer->parent.user_data;
    int timer_id = timer->timer_id;
    if (timer_id == 1)
        rt_hw_interrupt_mask(IRQ_SYSTEM_TIMER_1);
    else if (timer_id == 3)
        rt_hw_interrupt_mask(IRQ_SYSTEM_TIMER_3);

}

static rt_err_t raspi_systimer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
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


void rt_device_systimer_isr(int vector, void *param)
{

    rt_hwtimer_t *hwtimer = (rt_hwtimer_t *) param;
    rt_systimer_t *timer = (rt_systimer_t *)hwtimer->parent.user_data;
    RT_ASSERT(timer != RT_NULL);

    int timer_id = timer->timer_id;

    __sync_synchronize();
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
    __sync_synchronize();

    rt_device_hwtimer_isr(hwtimer);
}

#ifdef RT_USING_SYSTIMER1
static struct rt_hwtimer_device _hwtimer1;
static rt_systimer_t _systimer1;
#endif

#ifdef RT_USING_SYSTIMER3
static struct rt_hwtimer_device _hwtimer3;
static rt_systimer_t _systimer3;
#endif

const static struct rt_hwtimer_ops systimer_ops =
{
    raspi_systimer_init,
    raspi_systimer_start,
    raspi_systimer_stop,
    RT_NULL,
    raspi_systimer_ctrl
};

static const struct rt_hwtimer_info _info =
{
    1000000,            /* the maxinum count frequency can be set */
    1000000,            /* the maxinum count frequency can be set */
    0xFFFFFFFF,         /* the maximum counter value */
    HWTIMER_CNTMODE_UP  /* count mode (inc/dec) */
};

#endif

int rt_hw_systimer_init(void)
{

#ifdef BSP_USING_SYSTIMER

#ifdef RT_USING_SYSTIMER1
    _systimer1.timer_id =1;
    _hwtimer1.ops = &systimer_ops;
    _hwtimer1.info = &_info;
    rt_device_hwtimer_register(&_hwtimer1, "timer1",&_systimer1);
    rt_hw_interrupt_install(IRQ_SYSTEM_TIMER_1, rt_device_systimer_isr, &_hwtimer1, "systimer1");
    rt_hw_interrupt_umask(IRQ_SYSTEM_TIMER_1);
#endif

#ifdef RT_USING_SYSTIMER3
    _systimer3.timer_id =3;
    _hwtimer3.ops = &systimer_ops;
    _hwtimer3.info = &_info;
    rt_device_hwtimer_register(&_hwtimer3, "timer3",&_systimer3);
    rt_hw_interrupt_install(IRQ_SYSTEM_TIMER_3, rt_device_systimer_isr, &_hwtimer3, "systimer3");
    rt_hw_interrupt_umask(IRQ_SYSTEM_TIMER_3);
#endif

#endif

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_systimer_init);
