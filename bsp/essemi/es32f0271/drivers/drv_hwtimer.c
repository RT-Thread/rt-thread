/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-10-23     yuzrain       the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drv_hwtimer.h>
#include <board.h>
#include "md_ad16c4t.h"
#include "md_rcu.h"

#ifdef RT_USING_HWTIMER

/* Defien the hardware timer control struct */
struct es32f0_hwtimer_dev
{
    rt_hwtimer_t parent;
    AD16C4T_TypeDef *hwtimer_periph;
    IRQn_Type IRQn;
};

#ifdef BSP_USING_HWTIMER1
static struct es32f0_hwtimer_dev hwtimer1;

void BS16T1_IRQHandler(void)
{
    /* if BS16T1 IT */
    if (BS16T1->IFM & AD16C4T_RIF_UI_MSK)
    {
        SET_BIT(BS16T1->ICR, AD16C4T_ICR_UI_MSK);
        rt_device_hwtimer_isr(&hwtimer1.parent);

        if (HWTIMER_MODE_ONESHOT == hwtimer1.parent.mode)
        {
            CLEAR_BIT(BS16T1->CON1, AD16C4T_CON1_CNTEN_MSK);
        }
    }
}
#endif

static struct rt_hwtimer_info es32f0_hwtimer_info =
{
    48000000, /* maximum count frequency */
    1,        /* minimum count frequency */
    65535,    /* counter maximum value */
    HWTIMER_CNTMODE_UP
};

static void es32f0_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    struct es32f0_hwtimer_dev *hwtimer = (struct es32f0_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    if (1 == state)
    {
        /* Set frequency */
        WRITE_REG(hwtimer->hwtimer_periph->PRES, (SystemCoreClock/hwtimer->parent.freq - 1));
        /* Enable timer IT */
        SET_BIT(hwtimer->hwtimer_periph->IER, AD16C4T_IER_UI_MSK);
        NVIC_EnableIRQ(hwtimer->IRQn);
    }
    else
    {
        /* Dsiable timer IT */
        SET_BIT(hwtimer->hwtimer_periph->IDR, AD16C4T_IER_UI_MSK);
    }
}

static rt_err_t es32f0_hwtimer_start(rt_hwtimer_t *timer,
                                     rt_uint32_t cnt,
                                     rt_hwtimer_mode_t mode)
{
    struct es32f0_hwtimer_dev *hwtimer = (struct es32f0_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    WRITE_REG(hwtimer->hwtimer_periph->AR, cnt);
    SET_BIT(hwtimer->hwtimer_periph->CON1, AD16C4T_CON1_CNTEN_MSK);

    return RT_EOK;
}

static void es32f0_hwtimer_stop(rt_hwtimer_t *timer)
{
    struct es32f0_hwtimer_dev *hwtimer = (struct es32f0_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    CLEAR_BIT(hwtimer->hwtimer_periph->CON1, AD16C4T_CON1_CNTEN_MSK);
}

static rt_uint32_t es32f0_hwtimer_count_get(rt_hwtimer_t *timer)
{
    struct es32f0_hwtimer_dev *hwtimer = (struct es32f0_hwtimer_dev *)timer->parent.user_data;
    uint32_t hwtimer_count = 0;

    RT_ASSERT(hwtimer != RT_NULL);

    hwtimer_count = READ_REG(hwtimer->hwtimer_periph->COUNT);

    return hwtimer_count;
}

static rt_err_t es32f0_hwtimer_control(rt_hwtimer_t *timer,
                                       rt_uint32_t cmd,
                                       void *args)
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t freq = 0;
    struct es32f0_hwtimer_dev *hwtimer = (struct es32f0_hwtimer_dev *)timer->parent.user_data;

    RT_ASSERT(hwtimer != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        freq = *(rt_uint32_t *)args;
        if ((freq < hwtimer->parent.info->minfreq) || (freq > hwtimer->parent.info->maxfreq))
        {
            ret = RT_EINVAL;
        }
        /* Set frequency */
        WRITE_REG(hwtimer->hwtimer_periph->PRES, (SystemCoreClock/freq - 1));
        break;

    case HWTIMER_CTRL_STOP:
        CLEAR_BIT(hwtimer->hwtimer_periph->CON1, AD16C4T_CON1_CNTEN_MSK);
        break;

    default:
        ret = RT_EINVAL;
        break;
    }

    return ret;
}

static struct rt_hwtimer_ops es32f0_hwtimer_ops =
{
    es32f0_hwtimer_init,
    es32f0_hwtimer_start,
    es32f0_hwtimer_stop,
    es32f0_hwtimer_count_get,
    es32f0_hwtimer_control
};

int rt_hw_hwtimer_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_HWTIMER1
    /*Open clock*/
    SET_BIT(RCU->APB1EN, RCU_APB1EN_BS16T1EN_MSK);

    hwtimer1.hwtimer_periph     = BS16T1;
    hwtimer1.IRQn               = BS16T1_IRQn;
    hwtimer1.parent.info        = &es32f0_hwtimer_info;
    hwtimer1.parent.ops         = &es32f0_hwtimer_ops;
    ret = rt_device_hwtimer_register(&hwtimer1.parent, "timer1", &hwtimer1);
#endif

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

#endif
