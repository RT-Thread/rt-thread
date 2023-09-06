/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-04     Rbb666       first version
 */

#include "board.h"
#include "drv_hwtimer.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.timer"
#include <rtdbg.h>

#ifdef RT_USING_HWTIMER

static struct ra_hwtimer ra_hwtimer_obj[BSP_TIMERS_NUM] =
{
#ifdef BSP_USING_TIM0
    [BSP_TIMER0_INDEX] = TIMER_DRV_INITIALIZER(0),
#endif
#ifdef BSP_USING_TIM1
    [BSP_TIMER1_INDEX] = TIMER_DRV_INITIALIZER(1),
#endif
};

const rt_uint32_t PLCKD_FREQ_PRESCALER[PLCKD_PRESCALER_MAX_SELECT] =
{
#ifdef SOC_SERIES_R7FA6M3
    PLCKD_PRESCALER_120M,
    PLCKD_PRESCALER_60M,
    PLCKD_PRESCALER_30M,
    PLCKD_PRESCALER_15M,
    PLCKD_PRESCALER_7_5M,
    PLCKD_PRESCALER_3_75M,
    PLCKD_PRESCALER_1_875M,
#endif
};

static void timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    RT_ASSERT(timer != RT_NULL);

    struct ra_hwtimer *tim;
    tim = (struct ra_hwtimer *)timer->parent.user_data;

    if (state)
    {
        fsp_err_t fsp_err = FSP_SUCCESS;

        fsp_err = R_GPT_Open(tim->g_ctrl, tim->g_cfg);

        if (fsp_err != FSP_SUCCESS)
        {
            LOG_E("%s init fail", tim->name);
        }
    }
}

static rt_err_t timer_start(rt_hwtimer_t *timer, rt_uint32_t pr, rt_hwtimer_mode_t opmode)
{
    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(opmode != RT_NULL);

    struct ra_hwtimer *tim;
    tim = (struct ra_hwtimer *)timer->parent.user_data;
    fsp_err_t err = FSP_SUCCESS;

    /* set timer count */
    R_GPT_CounterSet(tim->g_ctrl, 0);
    /* set timer period register */
    err = R_GPT_PeriodSet(tim->g_ctrl, pr);

    if (err != FSP_SUCCESS)
    {
        return -RT_ERROR;
    }

    /* set timer to one cycle mode */
    err = R_GPT_Start(tim->g_ctrl);

    return (err == FSP_SUCCESS) ? RT_EOK : -RT_ERROR;
}

static void timer_stop(rt_hwtimer_t *timer)
{
    struct ra_hwtimer *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    tim = (struct ra_hwtimer *)timer->parent.user_data;

    /* stop timer */
    R_GPT_Stop(tim->g_ctrl);

    /* set timer count */
    R_GPT_CounterSet(tim->g_ctrl, 0);
}

static rt_uint32_t timer_counter_get(rt_hwtimer_t *timer)
{
    struct ra_hwtimer *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);

    tim = (struct ra_hwtimer *)timer->parent.user_data;

    timer_info_t info;
    if (R_GPT_InfoGet(tim->g_ctrl, &info) != FSP_SUCCESS)
        return -RT_ERROR;

    return info.period_counts;
}

static rt_err_t timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    rt_err_t result = RT_EOK;
    struct ra_hwtimer *tim = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(arg != RT_NULL);

    tim = (struct ra_hwtimer *)timer->parent.user_data;

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        rt_uint8_t index = 0;
        rt_uint32_t freq = *((rt_uint32_t *)arg);

        for (rt_uint8_t i = 0; i < PLCKD_PRESCALER_MAX_SELECT; i++)
        {
            if (freq <= PLCKD_FREQ_PRESCALER[i])
            {
                index = i;
            }
        }
        tim->g_ctrl->p_reg->GTCR_b.TPCS = index;
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

static void timer_one_shot_check(void)
{
    IRQn_Type irq = R_FSP_CurrentIrqGet();

    /* Recover ISR context saved in open. */
    gpt_instance_ctrl_t *p_instance_ctrl = (gpt_instance_ctrl_t *) R_FSP_IsrContextGet(irq);

    /* If one-shot mode is selected, stop the timer since period has expired. */
    if (TIMER_MODE_ONE_SHOT == p_instance_ctrl->p_cfg->mode)
    {
        p_instance_ctrl->p_reg->GTSTP = p_instance_ctrl->channel_mask;

        /* Clear the GPT counter and the overflow flag after the one shot pulse has being generated */
        p_instance_ctrl->p_reg->GTCNT = 0;
        p_instance_ctrl->p_reg->GTCCR[0U] = 0;
        p_instance_ctrl->p_reg->GTCCR[1U] = 0;

        /* Clear pending interrupt to make sure it doesn't fire again if another overflow has already occurred. */
        R_BSP_IrqClearPending(irq);
    }
}

#ifdef BSP_USING_TIM0
void timer0_callback(timer_callback_args_t *p_args)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIMER_EVENT_CYCLE_END == p_args->event)
    {
        rt_device_hwtimer_isr(&ra_hwtimer_obj[BSP_TIMER0_INDEX].tmr_device);

        timer_one_shot_check();
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM1
void timer1_callback(timer_callback_args_t *p_args)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (TIMER_EVENT_CYCLE_END == p_args->event)
    {
        rt_device_hwtimer_isr(&ra_hwtimer_obj[BSP_TIMER1_INDEX].tmr_device);

        timer_one_shot_check();
    }

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static const struct rt_hwtimer_ops _ops =
{
    .init = timer_init,
    .start = timer_start,
    .stop = timer_stop,
    .count_get = timer_counter_get,
    .control = timer_ctrl,
};

static const struct rt_hwtimer_info _info = TMR_DEV_INFO_CONFIG;

static int rt_hw_hwtimer_init(void)
{
    int result = RT_EOK;

    for (int i = 0; i < sizeof(ra_hwtimer_obj) / sizeof(ra_hwtimer_obj[0]); i++)
    {
        ra_hwtimer_obj[i].tmr_device.info = &_info;
        ra_hwtimer_obj[i].tmr_device.ops  = &_ops;
        if (rt_device_hwtimer_register(&ra_hwtimer_obj[i].tmr_device, ra_hwtimer_obj[i].name, &ra_hwtimer_obj[i]) == RT_EOK)
        {
            LOG_D("%s register success", ra_hwtimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", ra_hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_hwtimer_init);

/* This is a hwtimer example */
#define HWTIMER_DEV_NAME "timer0" /* device name */

static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return RT_EOK;
}

int hwtimer_sample(void)
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;
    rt_device_t hw_dev = RT_NULL;
    rt_hwtimer_mode_t mode;
    rt_uint32_t freq = 1875000; /* 1Mhz */

    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return -RT_ERROR;
    }

    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);

    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* Example Set the timeout period of the timer */
    timeout_s.sec = 1;  /* secend */
    timeout_s.usec = 0; /* microsecend */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return -RT_ERROR;
    }

    /* read hwtimer value */
    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}
MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample);

#endif /* BSP_USING_HWTIMER */
