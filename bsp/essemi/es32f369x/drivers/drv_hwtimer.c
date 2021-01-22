/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-3-19      wangyq       the first version
 * 2019-11-01     wangyq        update libraries
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drv_hwtimer.h>
#include <board.h>
#include <ald_cmu.h>
#include <ald_timer.h>

#ifdef RT_USING_HWTIMER

struct es32f3_hwtimer_dev
{
    rt_hwtimer_t parent;
    timer_handle_t *hwtimer_periph;
    IRQn_Type IRQn;
};

#ifdef BSP_USING_HWTIMER0
static struct es32f3_hwtimer_dev hwtimer0;

void BS16T0_Handler(void)
{
    ald_timer_clear_flag_status(hwtimer0.hwtimer_periph, TIMER_FLAG_UPDATE);
    rt_device_hwtimer_isr(&hwtimer0.parent);

    if (HWTIMER_MODE_ONESHOT == hwtimer0.parent.mode)
    {
        ald_timer_base_stop(hwtimer0.hwtimer_periph);
    }
}
#endif

#ifdef BSP_USING_HWTIMER1
static struct es32f3_hwtimer_dev hwtimer1;
/* can not use when UART2 Handler is enabled */
void BS16T1_Handler(void)
{
    /* if BS16T1 it */
    if (ald_timer_get_it_status(hwtimer1.hwtimer_periph, TIMER_IT_UPDATE) &&
            ald_timer_get_flag_status(hwtimer1.hwtimer_periph, TIMER_FLAG_UPDATE))
    {
        ald_timer_clear_flag_status(hwtimer1.hwtimer_periph, TIMER_FLAG_UPDATE);
        rt_device_hwtimer_isr(&hwtimer1.parent);

        if (HWTIMER_MODE_ONESHOT == hwtimer1.parent.mode)
        {
            ald_timer_base_stop(hwtimer1.hwtimer_periph);
        }
    }
}
#endif

static struct rt_hwtimer_info es32f3_hwtimer_info =
{
    96000000, /* maximum count frequency */
    1,        /* minimum count frequency */
    65535,    /* counter maximum value */
    HWTIMER_CNTMODE_UP
};

static void es32f3_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    if (1 == state)
    {
        ald_timer_base_init(hwtimer->hwtimer_periph);
        ald_timer_interrupt_config(hwtimer->hwtimer_periph, TIMER_IT_UPDATE, ENABLE);
        NVIC_EnableIRQ(hwtimer->IRQn);
    }
    hwtimer->parent.freq = ald_cmu_get_pclk1_clock();
    es32f3_hwtimer_info.maxfreq = ald_cmu_get_pclk1_clock();
    es32f3_hwtimer_info.minfreq = ald_cmu_get_pclk1_clock();
}

static rt_err_t es32f3_hwtimer_start(rt_hwtimer_t *timer,
                                     rt_uint32_t cnt,
                                     rt_hwtimer_mode_t mode)
{
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    WRITE_REG(hwtimer->hwtimer_periph->perh->AR, cnt);
    ald_timer_base_start(hwtimer->hwtimer_periph);

    return RT_EOK;
}

static void es32f3_hwtimer_stop(rt_hwtimer_t *timer)
{
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    ald_timer_base_stop(hwtimer->hwtimer_periph);
}

static rt_uint32_t es32f3_hwtimer_count_get(rt_hwtimer_t *timer)
{
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;
    uint32_t hwtimer_count = 0;

    RT_ASSERT(hwtimer != RT_NULL);

    hwtimer_count = READ_REG(hwtimer->hwtimer_periph->perh->COUNT);

    return hwtimer_count;
}

static rt_err_t es32f3_hwtimer_control(rt_hwtimer_t *timer,
                                       rt_uint32_t cmd,
                                       void *args)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t freq = 0;
    struct es32f3_hwtimer_dev *hwtimer = (struct es32f3_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        freq = *(rt_uint32_t *)args;
        if (freq != ald_cmu_get_pclk1_clock())
        {
            ret = -RT_ERROR;
        }
        break;

    case HWTIMER_CTRL_STOP:
        ald_timer_base_stop(hwtimer->hwtimer_periph);
        break;

    default:
        ret = RT_EINVAL;
        break;
    }

    return ret;
}

static struct rt_hwtimer_ops es32f3_hwtimer_ops =
{
    es32f3_hwtimer_init,
    es32f3_hwtimer_start,
    es32f3_hwtimer_stop,
    es32f3_hwtimer_count_get,
    es32f3_hwtimer_control
};

int rt_hw_hwtimer_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_HWTIMER0
    static timer_handle_t _hwtimer_periph0;
    _hwtimer_periph0.perh = BS16T0;
    hwtimer0.IRQn = BS16T0_IRQn;
    hwtimer0.hwtimer_periph = &_hwtimer_periph0;
    hwtimer0.parent.info = &es32f3_hwtimer_info;
    hwtimer0.parent.ops = &es32f3_hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer0.parent, "timer0", &hwtimer0);
#endif

#ifdef BSP_USING_HWTIMER1
    static timer_handle_t _hwtimer_periph1;
    _hwtimer_periph1.perh = BS16T1;
    hwtimer1.IRQn = BS16T1_IRQn;
    hwtimer1.hwtimer_periph = &_hwtimer_periph1;
    hwtimer1.parent.info = &es32f3_hwtimer_info;
    hwtimer1.parent.ops = &es32f3_hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer1.parent, "timer1", &hwtimer1);
#endif

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif
