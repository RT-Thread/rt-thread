/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-2-7        YCHuang12        First version
*
******************************************************************************/

#include <rtconfig.h>

#if (defined(BSP_USING_TIMER) && defined(RT_USING_HWTIMER))

#include <rtdevice.h>
#include <NuMicro.h>

/* Private define ---------------------------------------------------------------*/
#define NU_TIMER_DEVICE(timer) (nu_timer_t *)(timer)

/* Private typedef --------------------------------------------------------------*/
typedef struct nu_timer
{
    rt_hwtimer_t parent;
    TIMER_T *timer_periph;
    IRQn_Type IRQn;
} nu_timer_t;

/* Private functions ------------------------------------------------------------*/
static void nu_timer_init(rt_hwtimer_t *timer, rt_uint32_t state);
static rt_err_t nu_timer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t opmode);
static void nu_timer_stop(rt_hwtimer_t *timer);
static rt_uint32_t nu_timer_count_get(rt_hwtimer_t *timer);
static rt_err_t nu_timer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args);

/* Public functions -------------------------------------------------------------*/


/* Private variables ------------------------------------------------------------*/
#ifdef BSP_USING_TIMER0
    static nu_timer_t nu_timer0;
#endif

#ifdef BSP_USING_TIMER1
    static nu_timer_t nu_timer1;
#endif

#ifdef BSP_USING_TIMER2
    static nu_timer_t nu_timer2;
#endif

#ifdef BSP_USING_TIMER3
    static nu_timer_t nu_timer3;
#endif

static struct rt_hwtimer_info nu_timer_info =
{
    12000000, /* maximum count frequency */
    46875,        /* minimum count frequency */
    0xFFFFFF,          /* the maximum counter value */
    HWTIMER_CNTMODE_UP,/* Increment or Decreasing count mode */
};

static struct rt_hwtimer_ops nu_timer_ops =
{
    nu_timer_init,
    nu_timer_start,
    nu_timer_stop,
    nu_timer_count_get,
    nu_timer_control
};

/* Functions define ------------------------------------------------------------*/
static void nu_timer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    RT_ASSERT(timer != RT_NULL);

    nu_timer_t *nu_timer = NU_TIMER_DEVICE(timer->parent.user_data);
    RT_ASSERT(nu_timer != RT_NULL);
    RT_ASSERT(nu_timer->timer_periph != RT_NULL);

    if (1 == state)
    {
        uint32_t timer_clk;
        struct rt_hwtimer_info *info = &nu_timer_info;

        timer_clk = TIMER_GetModuleClock(nu_timer->timer_periph);
        info->maxfreq = timer_clk;
        info->minfreq = timer_clk / 256;
        TIMER_Open(nu_timer->timer_periph, TIMER_ONESHOT_MODE, 1);
        TIMER_EnableInt(nu_timer->timer_periph);
        NVIC_EnableIRQ(nu_timer->IRQn);
    }
    else
    {
        NVIC_DisableIRQ(nu_timer->IRQn);
        TIMER_DisableInt(nu_timer->timer_periph);
        TIMER_Close(nu_timer->timer_periph);
    }
}

static rt_err_t nu_timer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t opmode)
{
    rt_err_t err = RT_EOK;
    RT_ASSERT(timer != RT_NULL);

    nu_timer_t *nu_timer = NU_TIMER_DEVICE(timer->parent.user_data);
    RT_ASSERT(nu_timer != RT_NULL);
    RT_ASSERT(nu_timer->timer_periph != RT_NULL);

    if (cnt > 1 && cnt <= 0xFFFFFF)
    {
        TIMER_SET_CMP_VALUE(nu_timer->timer_periph, cnt);
    }
    else
    {
        rt_kprintf("nu_timer_start set compared value failed\n");
        err = RT_ERROR;
    }

    if (HWTIMER_MODE_PERIOD == opmode)
    {
        TIMER_SET_OPMODE(nu_timer->timer_periph, TIMER_PERIODIC_MODE);
    }
    else if (HWTIMER_MODE_ONESHOT == opmode)
    {
        TIMER_SET_OPMODE(nu_timer->timer_periph, TIMER_ONESHOT_MODE);
    }
    else
    {
        rt_kprintf("nu_timer_start set operation mode failed\n");
        err = RT_ERROR;
    }

    TIMER_Start(nu_timer->timer_periph);

    return err;
}

static void nu_timer_stop(rt_hwtimer_t *timer)
{
    RT_ASSERT(timer != RT_NULL);

    nu_timer_t *nu_timer = NU_TIMER_DEVICE(timer->parent.user_data);
    RT_ASSERT(nu_timer != RT_NULL);
    RT_ASSERT(nu_timer->timer_periph != RT_NULL);

    TIMER_Stop(nu_timer->timer_periph);
}

static rt_uint32_t nu_timer_count_get(rt_hwtimer_t *timer)
{
    RT_ASSERT(timer != RT_NULL);

    nu_timer_t *nu_timer = NU_TIMER_DEVICE(timer->parent.user_data);
    RT_ASSERT(nu_timer != RT_NULL);
    RT_ASSERT(nu_timer->timer_periph != RT_NULL);

    return TIMER_GetCounter(nu_timer->timer_periph);
}

static rt_err_t nu_timer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t ret = RT_EOK;

    RT_ASSERT(timer != RT_NULL);

    nu_timer_t *nu_timer = NU_TIMER_DEVICE(timer->parent.user_data);
    RT_ASSERT(nu_timer != RT_NULL);
    RT_ASSERT(nu_timer->timer_periph != RT_NULL);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint32_t pre;

        clk = TIMER_GetModuleClock(nu_timer->timer_periph);
        pre = clk / *((uint32_t *)args) - 1;
        TIMER_SET_PRESCALE_VALUE(nu_timer->timer_periph, pre);
        *((uint32_t *)args) = clk / (pre + 1) ;
    }
    break;

    case HWTIMER_CTRL_STOP:
        TIMER_Stop(nu_timer->timer_periph);
        break;

    default:
        ret = RT_EINVAL;
        break;
    }

    return ret;
}

int rt_hw_timer_init(void)
{
    rt_err_t ret = RT_EOK;

#ifdef BSP_USING_TIMER0
    nu_timer0.timer_periph = TIMER0;
    nu_timer0.parent.info = &nu_timer_info;
    nu_timer0.parent.ops = &nu_timer_ops;
    nu_timer0.IRQn = TMR0_IRQn;
    ret = rt_device_hwtimer_register(&nu_timer0.parent, "timer0", &nu_timer0);
    if (ret != RT_EOK)
    {
        rt_kprintf("timer0 register failed\n");
    }
    SYS_ResetModule(TMR0_RST);
    CLK_EnableModuleClock(TMR0_MODULE);
#endif

#ifdef BSP_USING_TIMER1
    nu_timer1.timer_periph = TIMER1;
    nu_timer1.parent.info = &nu_timer_info;
    nu_timer1.parent.ops = &nu_timer_ops;
    nu_timer1.IRQn = TMR1_IRQn;
    ret = rt_device_hwtimer_register(&nu_timer1.parent, "timer1", &nu_timer1);
    if (ret != RT_EOK)
    {
        rt_kprintf("timer1 register failed\n");
    }
    SYS_ResetModule(TMR1_RST);
    CLK_EnableModuleClock(TMR1_MODULE);
#endif

#ifdef BSP_USING_TIMER2
    nu_timer2.timer_periph = TIMER2;
    nu_timer2.parent.info = &nu_timer_info;
    nu_timer2.parent.ops = &nu_timer_ops;
    nu_timer2.IRQn = TMR2_IRQn;
    ret = rt_device_hwtimer_register(&nu_timer2.parent, "timer2", &nu_timer2);
    if (ret != RT_EOK)
    {
        rt_kprintf("timer2 register failed\n");
    }
    SYS_ResetModule(TMR2_RST);
    CLK_EnableModuleClock(TMR2_MODULE);
#endif

#ifdef BSP_USING_TIMER3
    nu_timer3.timer_periph = TIMER3;
    nu_timer3.parent.info = &nu_timer_info;
    nu_timer3.parent.ops = &nu_timer_ops;
    nu_timer3.IRQn = TMR3_IRQn;
    ret = rt_device_hwtimer_register(&nu_timer3.parent, "timer3", &nu_timer3);
    if (ret != RT_EOK)
    {
        rt_kprintf("timer3 register failed\n");
    }
    SYS_ResetModule(TMR3_RST);
    CLK_EnableModuleClock(TMR3_MODULE);
#endif

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_timer_init);

#ifdef BSP_USING_TIMER0
void TMR0_IRQHandler(void)
{
    rt_interrupt_enter();

    if (TIMER_GetIntFlag(TIMER0))
    {
        TIMER_ClearIntFlag(TIMER0);
        rt_device_hwtimer_isr(&nu_timer0.parent);
    }

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER1
void TMR1_IRQHandler(void)
{
    rt_interrupt_enter();

    if (TIMER_GetIntFlag(TIMER1))
    {
        TIMER_ClearIntFlag(TIMER1);
        rt_device_hwtimer_isr(&nu_timer1.parent);
    }

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER2
void TMR2_IRQHandler(void)
{
    rt_interrupt_enter();

    if (TIMER_GetIntFlag(TIMER2))
    {
        TIMER_ClearIntFlag(TIMER2);
        rt_device_hwtimer_isr(&nu_timer2.parent);
    }

    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER3
void TMR3_IRQHandler(void)
{
    rt_interrupt_enter();

    if (TIMER_GetIntFlag(TIMER3))
    {
        TIMER_ClearIntFlag(TIMER3);
        rt_device_hwtimer_isr(&nu_timer3.parent);
    }

    rt_interrupt_leave();
}
#endif

#endif //#if (defined(BSP_USING_TIMER) && defined(RT_USING_HWTIMER))
