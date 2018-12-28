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

#define SWM320_HWTIMER_DEVICE(hwtimer) (struct swm320_hwtimer_dev *)(hwtimer)

struct swm320_hwtimer_dev
{
    rt_hwtimer_t parent;
    TIMR_TypeDef *hwtimer_periph;
};

#ifdef BSP_USING_HWTIMER0
static struct swm320_hwtimer_dev hwtimer0;

void TIMR0_Handler(void)
{
    TIMR_INTClr(TIMR0);
    rt_device_hwtimer_isr(&hwtimer0.parent);
    
    if (HWTIMER_MODE_ONESHOT == hwtimer0.parent.mode)
    {
        TIMR_Stop(hwtimer0.hwtimer_periph);
    }  
}
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
static struct swm320_hwtimer_dev hwtimer1;

void TIMR1_Handler(void)
{
    TIMR_INTClr(TIMR1);
    rt_device_hwtimer_isr(&hwtimer1.parent);

    if (HWTIMER_MODE_ONESHOT == hwtimer1.parent.mode)
    {
        TIMR_Stop(hwtimer1.hwtimer_periph);
    } 
}
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
static struct swm320_hwtimer_dev hwtimer2;

void TIMR2_Handler(void)
{
    TIMR_INTClr(TIMR2);
    rt_device_hwtimer_isr(&hwtimer2.parent);
    
    if (HWTIMER_MODE_ONESHOT == hwtimer2.parent.mode)
    {
        TIMR_Stop(hwtimer2.hwtimer_periph);
    } 
}
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
static struct swm320_hwtimer_dev hwtimer3;

void TIMR3_Handler(void)
{
    TIMR_INTClr(TIMR3);
    rt_device_hwtimer_isr(&hwtimer3.parent);
    
    if (HWTIMER_MODE_ONESHOT == hwtimer3.parent.mode)
    {
        TIMR_Stop(hwtimer3.hwtimer_periph);
    }
}
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
static struct swm320_hwtimer_dev hwtimer4;

void TIMR4_Handler(void)
{
    TIMR_INTClr(TIMR4);
    rt_device_hwtimer_isr(&hwtimer4.parent);
    
    if (HWTIMER_MODE_ONESHOT == hwtimer4.parent.mode)
    {
        TIMR_Stop(hwtimer4.hwtimer_periph);
    }
}
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
static struct swm320_hwtimer_dev hwtimer5;

void TIMR5_Handler(void)
{
    TIMR_INTClr(TIMR5);
    rt_device_hwtimer_isr(&hwtimer5.parent);
    
    if (HWTIMER_MODE_ONESHOT == hwtimer5.parent.mode)
    {
        TIMR_Stop(hwtimer5.hwtimer_periph);
    }
}
#endif //BSP_USING_HWTIMER5

static struct rt_hwtimer_info swm320_hwtimer_info =
{
    120000000,  /*时钟源为系统时钟*/
    120000000, 
    4294967295, /*32位计数器，2的32次方*/
    HWTIMER_CNTMODE_DW
};

static void swm320_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    struct swm320_hwtimer_dev *hwtimer = SWM320_HWTIMER_DEVICE(timer->parent.user_data);

    RT_ASSERT(hwtimer != RT_NULL);

    if (1 == state)
    {
        TIMR_Init(hwtimer->hwtimer_periph,
                  TIMR_MODE_TIMER,
                  SystemCoreClock,
                  1);
    }
    hwtimer->parent.freq = SystemCoreClock;
    swm320_hwtimer_info.maxfreq = SystemCoreClock;
    swm320_hwtimer_info.minfreq = SystemCoreClock;
}

static rt_err_t swm320_hwtimer_start(rt_hwtimer_t *timer,
                                     rt_uint32_t cnt,
                                     rt_hwtimer_mode_t mode)
{
    struct swm320_hwtimer_dev *hwtimer = SWM320_HWTIMER_DEVICE(timer->parent.user_data);

    RT_ASSERT(hwtimer != RT_NULL);

    TIMR_SetPeriod(hwtimer->hwtimer_periph, cnt);
    TIMR_Start(hwtimer->hwtimer_periph);

    return RT_EOK;
}

static void swm320_hwtimer_stop(rt_hwtimer_t *timer)
{
    struct swm320_hwtimer_dev *hwtimer = SWM320_HWTIMER_DEVICE(timer->parent.user_data);

    RT_ASSERT(hwtimer != RT_NULL);

    TIMR_Stop(hwtimer->hwtimer_periph);
}

static rt_uint32_t swm320_hwtimer_count_get(rt_hwtimer_t *timer)
{
    struct swm320_hwtimer_dev *hwtimer = SWM320_HWTIMER_DEVICE(timer->parent.user_data);
    uint32_t hwtimer_count = 0;

    RT_ASSERT(hwtimer != RT_NULL);

    hwtimer_count = TIMR_GetCurValue(hwtimer->hwtimer_periph);

    return hwtimer_count;
}

static rt_err_t swm320_hwtimer_control(rt_hwtimer_t *timer,
                                       rt_uint32_t cmd,
                                       void *args)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t freq = 0;
    struct swm320_hwtimer_dev *hwtimer = SWM320_HWTIMER_DEVICE(timer->parent.user_data);

    RT_ASSERT(hwtimer != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        freq = *(rt_uint32_t*)args;
        if (freq != SystemCoreClock)
        {
            ret = RT_EINVAL;
        }
        break;
    case HWTIMER_CTRL_STOP:
        TIMR_Stop(hwtimer->hwtimer_periph);
        break;
    default:
        ret = RT_EINVAL;
        break;
    }

    return ret;
}

static struct rt_hwtimer_ops swm320_hwtimer_ops =
{
    swm320_hwtimer_init,
    swm320_hwtimer_start,
    swm320_hwtimer_stop,
    swm320_hwtimer_count_get,
    swm320_hwtimer_control
};

int rt_hw_hwtimer_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_HWTIMER0
    hwtimer0.hwtimer_periph = TIMR0;
    hwtimer0.parent.info = &swm320_hwtimer_info;
    hwtimer0.parent.ops = &swm320_hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer0.parent, "timer0", &hwtimer0);
#endif //BSP_USING_HWTIMER0

#ifdef BSP_USING_HWTIMER1
    hwtimer1.hwtimer_periph = TIMR1;
    hwtimer1.parent.info = &swm320_hwtimer_info;
    hwtimer1.parent.ops = &swm320_hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer1.parent, "timer1", &hwtimer1);
#endif //BSP_USING_HWTIMER1

#ifdef BSP_USING_HWTIMER2
    hwtimer2.hwtimer_periph = TIMR2;
    hwtimer2.parent.info = &swm320_hwtimer_info;
    hwtimer2.parent.ops = &swm320_hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer2.parent, "timer2", &hwtimer2);
#endif //BSP_USING_HWTIMER2

#ifdef BSP_USING_HWTIMER3
    hwtimer3.hwtimer_periph = TIMR3;
    hwtimer3.parent.info = &swm320_hwtimer_info;
    hwtimer3.parent.ops = &swm320_hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer3.parent, "timer3", &hwtimer3);
#endif //BSP_USING_HWTIMER3

#ifdef BSP_USING_HWTIMER4
    hwtimer4.hwtimer_periph = TIMR4;
    hwtimer4.parent.info = &swm320_hwtimer_info;
    hwtimer4.parent.ops = &swm320_hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer4.parent, "timer4", &hwtimer4);
#endif //BSP_USING_HWTIMER4

#ifdef BSP_USING_HWTIMER5
    hwtimer5.hwtimer_periph = TIMR5;
    hwtimer5.parent.info = &swm320_hwtimer_info;
    hwtimer5.parent.ops = &swm320_hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer5.parent, "timer5", &hwtimer5);
#endif //BSP_USING_HWTIMER5

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);
