/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10    Zohar_Lee    first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_HWTIMER0
    static rt_hwtimer_t swm320_timer0;
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
    static rt_hwtimer_t swm320_timer1;
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
    static rt_hwtimer_t swm320_timer2;
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
    static rt_hwtimer_t swm320_timer3;
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
    static rt_hwtimer_t swm320_timer4;
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
    static rt_hwtimer_t swm320_timer5;
#endif //BSP_USING_HWTIMER5

static rt_hwtimer_mode_t swm320_timer0_mode = HWTIMER_MODE_PERIOD;
static rt_hwtimer_mode_t swm320_timer1_mode = HWTIMER_MODE_PERIOD;
static rt_hwtimer_mode_t swm320_timer2_mode = HWTIMER_MODE_PERIOD;
static rt_hwtimer_mode_t swm320_timer3_mode = HWTIMER_MODE_PERIOD;
static rt_hwtimer_mode_t swm320_timer4_mode = HWTIMER_MODE_PERIOD;
static rt_hwtimer_mode_t swm320_timer5_mode = HWTIMER_MODE_PERIOD;

static void swm320_hwtimer_init(struct rt_hwtimer_device *timer,
                                rt_uint32_t state)
{
    rt_device_t dev = &timer->parent;

    TIMR_Init(dev->user_data,
              TIMR_MODE_TIMER,
              SystemCoreClock / timer->freq,
              1);
    if (1 == state)
        TIMR_Start(dev->user_data);
    else if (0 == state)
        TIMR_Stop(dev->user_data);
}

static rt_err_t swm320_hwtimer_start(struct rt_hwtimer_device *timer,
                                     rt_uint32_t cnt,
                                     rt_hwtimer_mode_t mode)
{
    TIMR_Start(timer->parent.user_data);

    return RT_EOK;
}

static void swm320_hwtimer_stop(struct rt_hwtimer_device *timer)
{
    TIMR_Stop(timer->parent.user_data);
}

static rt_uint32_t swm320_hwtimer_count_get(struct rt_hwtimer_device *timer)
{
    rt_uint32_t hwtimer_count = 0;

    hwtimer_count = TIMR_GetCurValue(timer->parent.user_data);

    return hwtimer_count;
}

static void swm320_hwtimer_freq_set(struct rt_hwtimer_device *timer, void *freq)
{
    uint32_t period = SystemCoreClock / *(uint32_t *)freq;
    TIMR_SetPeriod(timer->parent.user_data, period);
}

static void swm320_hwtimer_info_get(struct rt_hwtimer_device *timer, void *info)
{
    *(struct rt_hwtimer_info *)info = *timer->info;
}

static rt_uint32_t swm320_hwtimer_mode_set(struct rt_hwtimer_device *timer,
        void *mode)
{
#ifdef BSP_USING_HWTIMER0
    if (&swm320_timer0 == timer)
    {
        if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer0_mode = HWTIMER_MODE_ONESHOT;
        }
        else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer0_mode = HWTIMER_MODE_PERIOD;
        }
        else
        {
            return 0;
        }
    }
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
    if (&swm320_timer1 == timer)
    {
        if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer1_mode = HWTIMER_MODE_ONESHOT;
        }
        else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer1_mode = HWTIMER_MODE_PERIOD;
        }
        else
        {
            return 0;
        }
    }
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
    if (&swm320_timer2 == timer)
    {
        if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer2_mode = HWTIMER_MODE_ONESHOT;
        }
        else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer2_mode = HWTIMER_MODE_PERIOD;
        }
        else
        {
            return 0;
        }
    }
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
    if (&swm320_timer3 == timer)
    {
        if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer3_mode = HWTIMER_MODE_ONESHOT;
        }
        else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer3_mode = HWTIMER_MODE_PERIOD;
        }
        else
        {
            return 0;
        }
    }
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
    if (&swm320_timer4 == timer)
    {
        if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer4_mode = HWTIMER_MODE_ONESHOT;
        }
        else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer4_mode = HWTIMER_MODE_PERIOD;
        }
        else
        {
            return 0;
        }
    }
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
    if (&swm320_timer5 == timer)
    {
        if (HWTIMER_MODE_ONESHOT == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer5_mode = HWTIMER_MODE_ONESHOT;
        }
        else if (HWTIMER_MODE_PERIOD == *(rt_hwtimer_mode_t *)mode)
        {
            swm320_timer5_mode = HWTIMER_MODE_PERIOD;
        }
        else
        {
            return 0;
        }
    }
#endif //BSP_USING_HWTIMER5

    return RT_EOK;
}

static rt_err_t swm320_hwtimer_control(struct rt_hwtimer_device *timer,
                                       rt_uint32_t cmd,
                                       void *args)
{
    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        swm320_hwtimer_freq_set(timer, args);
        break;
    case HWTIMER_CTRL_STOP:
        swm320_hwtimer_stop(timer);
        break;
    case HWTIMER_CTRL_INFO_GET:
        swm320_hwtimer_info_get(timer, args);
        break;
    case HWTIMER_CTRL_MODE_SET:
        swm320_hwtimer_mode_set(timer, args);
        break;
    default:
        break;
    }

    return RT_EOK;
}

#ifdef BSP_USING_HWTIMER0
void TIMR0_Handler(void)
{
    TIMR_INTClr(TIMR0);
    rt_device_hwtimer_isr(&swm320_timer0);
}
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
void TIMR1_Handler(void)
{
    TIMR_INTClr(TIMR1);
    rt_device_hwtimer_isr(&swm320_timer1);
}
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
void TIMR2_Handler(void)
{
    TIMR_INTClr(TIMR2);
    rt_device_hwtimer_isr(&swm320_timer2);
}
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
void TIMR3_Handler(void)
{
    TIMR_INTClr(TIMR3);
    rt_device_hwtimer_isr(&swm320_timer3);
}
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
void TIMR4_Handler(void)
{
    TIMR_INTClr(TIMR4);
    rt_device_hwtimer_isr(&swm320_timer4);
}
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
void TIMR5_Handler(void)
{
    TIMR_INTClr(TIMR5);
    rt_device_hwtimer_isr(&swm320_timer5);
}
#endif //BSP_USING_HWTIMER5

const static struct rt_hwtimer_ops swm320_hwtimer_ops =
{
    swm320_hwtimer_init,
    swm320_hwtimer_start,
    swm320_hwtimer_stop,
    swm320_hwtimer_count_get,
    swm320_hwtimer_control
};
const struct rt_hwtimer_info swm320_hwtimer_info =
{
    32000, /*默认使用最低频率工作，即32K*/
    1,     /*2的32次方*/
    4294967295,
    0
};

int rt_hw_hwtimer_init(void)
{
    void *user_data = RT_NULL;

#ifdef BSP_USING_HWTIMER0
    user_data = TIMR0;
    swm320_timer0.parent.user_data = user_data;
    swm320_timer0.info = &swm320_hwtimer_info;
    swm320_timer0.ops = &swm320_hwtimer_ops;
    rt_device_hwtimer_register(&swm320_timer0, "timer0", TIMR0);
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
    user_data = TIMR1;
    swm320_timer1.parent.user_data = user_data;
    swm320_timer1.info = &swm320_hwtimer_info;
    swm320_timer1.ops = &swm320_hwtimer_ops;
    rt_device_hwtimer_register(&swm320_timer1, "timer1", TIMR1);
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
    user_data = TIMR2;
    swm320_timer2.parent.user_data = user_data;
    swm320_timer2.info = &swm320_hwtimer_info;
    swm320_timer2.ops = &swm320_hwtimer_ops;
    rt_device_hwtimer_register(&swm320_timer2, "timer2", TIMR2);
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
    user_data = TIMR3;
    swm320_timer3.parent.user_data = user_data;
    swm320_timer3.info = &swm320_hwtimer_info;
    swm320_timer3.ops = &swm320_hwtimer_ops;
    rt_device_hwtimer_register(&swm320_timer3, "timer3", TIMR3);

#endif //BSP_USING_HWTIMER3
#ifdef BSP_USING_HWTIMER4
    user_data = TIMR4;
    swm320_timer4.parent.user_data = user_data;
    swm320_timer4.info = &swm320_hwtimer_info;
    swm320_timer4.ops = &swm320_hwtimer_ops;
    rt_device_hwtimer_register(&swm320_timer4, "timer4", TIMR4);
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
    user_data = TIMR5;
    swm320_timer5.parent.user_data = user_data;
    swm320_timer5.info = &swm320_hwtimer_info;
    swm320_timer5.ops = &swm320_hwtimer_ops;
    rt_device_hwtimer_register(&swm320_timer5, "timer5", TIMR5);
#endif //BSP_USING_HWTIMER5o

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_hwtimer_init);
