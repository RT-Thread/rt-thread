#include <rtthread.h>
#include <rtdevice.h>

#define LOG_TAG "drv.timer_w"
#include <rtdbg.h>

#include "drv_config.h"
#include "hal_data.h"

#define RA_TIMER_W_MAX_FREQ (BSP_CFG_XTALM_HZ)
#define RA_TIMER_W_MIN_FREQ (BSP_CFG_XTALM_HZ / 32U)
#define RA_TIMER_W_FREQ_COUNT (32U)

#define RA_TIMER_W_FREQ_TABLE \
    BSP_CFG_XTALM_HZ / 1U,  BSP_CFG_XTALM_HZ / 2U,  BSP_CFG_XTALM_HZ / 3U,  BSP_CFG_XTALM_HZ / 4U, \
    BSP_CFG_XTALM_HZ / 5U,  BSP_CFG_XTALM_HZ / 6U,  BSP_CFG_XTALM_HZ / 7U,  BSP_CFG_XTALM_HZ / 8U, \
    BSP_CFG_XTALM_HZ / 9U,  BSP_CFG_XTALM_HZ / 10U, BSP_CFG_XTALM_HZ / 11U, BSP_CFG_XTALM_HZ / 12U, \
    BSP_CFG_XTALM_HZ / 13U, BSP_CFG_XTALM_HZ / 14U, BSP_CFG_XTALM_HZ / 15U, BSP_CFG_XTALM_HZ / 16U, \
    BSP_CFG_XTALM_HZ / 17U, BSP_CFG_XTALM_HZ / 18U, BSP_CFG_XTALM_HZ / 19U, BSP_CFG_XTALM_HZ / 20U, \
    BSP_CFG_XTALM_HZ / 21U, BSP_CFG_XTALM_HZ / 22U, BSP_CFG_XTALM_HZ / 23U, BSP_CFG_XTALM_HZ / 24U, \
    BSP_CFG_XTALM_HZ / 25U, BSP_CFG_XTALM_HZ / 26U, BSP_CFG_XTALM_HZ / 27U, BSP_CFG_XTALM_HZ / 28U, \
    BSP_CFG_XTALM_HZ / 29U, BSP_CFG_XTALM_HZ / 30U, BSP_CFG_XTALM_HZ / 31U, BSP_CFG_XTALM_HZ / 32U

enum
{
#if defined(BSP_USING_TIM0) && !defined(BSP_USING_PWM0)
    BSP_TIMER0_INDEX,
#endif
#if defined(BSP_USING_TIM1) && !defined(BSP_USING_PWM1)
    BSP_TIMER1_INDEX,
#endif
#if defined(BSP_USING_TIM2) && !defined(BSP_USING_PWM2)
    BSP_TIMER2_INDEX,
#endif
#if defined(BSP_USING_TIM3) && !defined(BSP_USING_PWM3)
    BSP_TIMER3_INDEX,
#endif
#if defined(BSP_USING_TIM4) && !defined(BSP_USING_PWM4)
    BSP_TIMER4_INDEX,
#endif
#if defined(BSP_USING_TIM5) && !defined(BSP_USING_PWM5)
    BSP_TIMER5_INDEX,
#endif
#if defined(BSP_USING_TIM6) && !defined(BSP_USING_PWM6)
    BSP_TIMER6_INDEX,
#endif
#if defined(BSP_USING_TIM7) && !defined(BSP_USING_PWM7)
    BSP_TIMER7_INDEX,
#endif
    RA_TIMER_W_TIMER_COUNT
};

#ifdef RT_USING_CLOCK_TIME
struct ra_timer_w_timer
{
    rt_clock_timer_t          tmr_device;
    tim_w_instance_ctrl_t    *g_ctrl;
    const timer_instance_t   *g_timer;
    const timer_cfg_t        *g_cfg;
    const char               *name;
    rt_bool_t                  opened;
};

static struct ra_timer_w_timer ra_timer_w_timer_obj[RA_TIMER_W_TIMER_COUNT] =
{
#if defined(BSP_USING_TIM0) && !defined(BSP_USING_PWM0)
    [BSP_TIMER0_INDEX] = { .name = "timer0", .g_cfg = &g_timer0_cfg, .g_ctrl = &g_timer0_ctrl, .g_timer = &g_timer0 },
#endif
#if defined(BSP_USING_TIM1) && !defined(BSP_USING_PWM1)
    [BSP_TIMER1_INDEX] = { .name = "timer1", .g_cfg = &g_timer1_cfg, .g_ctrl = &g_timer1_ctrl, .g_timer = &g_timer1 },
#endif
#if defined(BSP_USING_TIM2) && !defined(BSP_USING_PWM2)
    [BSP_TIMER2_INDEX] = { .name = "timer2", .g_cfg = &g_timer2_cfg, .g_ctrl = &g_timer2_ctrl, .g_timer = &g_timer2 },
#endif
#if defined(BSP_USING_TIM3) && !defined(BSP_USING_PWM3)
    [BSP_TIMER3_INDEX] = { .name = "timer3", .g_cfg = &g_timer3_cfg, .g_ctrl = &g_timer3_ctrl, .g_timer = &g_timer3 },
#endif
#if defined(BSP_USING_TIM4) && !defined(BSP_USING_PWM4)
    [BSP_TIMER4_INDEX] = { .name = "timer4", .g_cfg = &g_timer4_cfg, .g_ctrl = &g_timer4_ctrl, .g_timer = &g_timer4 },
#endif
#if defined(BSP_USING_TIM5) && !defined(BSP_USING_PWM5)
    [BSP_TIMER5_INDEX] = { .name = "timer5", .g_cfg = &g_timer5_cfg, .g_ctrl = &g_timer5_ctrl, .g_timer = &g_timer5 },
#endif
#if defined(BSP_USING_TIM6) && !defined(BSP_USING_PWM6)
    [BSP_TIMER6_INDEX] = { .name = "timer6", .g_cfg = &g_timer6_cfg, .g_ctrl = &g_timer6_ctrl, .g_timer = &g_timer6 },
#endif
#if defined(BSP_USING_TIM7) && !defined(BSP_USING_PWM7)
    [BSP_TIMER7_INDEX] = { .name = "timer7", .g_cfg = &g_timer7_cfg, .g_ctrl = &g_timer7_ctrl, .g_timer = &g_timer7 },
#endif
};

static const rt_uint32_t ra_timer_w_freq_table[RA_TIMER_W_FREQ_COUNT] =
{
    RA_TIMER_W_FREQ_TABLE
};

static rt_uint32_t ra_timer_w_freq_select(rt_uint32_t requested, rt_uint32_t *actual)
{
    rt_uint32_t index = 0;
    rt_uint64_t best_diff = ~(rt_uint64_t) 0;

    for (rt_uint32_t i = 0; i < RA_TIMER_W_FREQ_COUNT; i++)
    {
        rt_uint64_t current = ra_timer_w_freq_table[i];
        rt_uint64_t diff = (current > requested) ? (current - requested) : (requested - current);

        if (diff < best_diff)
        {
            best_diff = diff;
            index = i;
        }
    }

    if (actual != RT_NULL)
    {
        *actual = ra_timer_w_freq_table[index];
    }

    return index;
}

static void timer_init(struct rt_clock_timer_device *timer, rt_uint32_t state)
{
    struct ra_timer_w_timer *tim;

    RT_ASSERT(timer != RT_NULL);
    tim = (struct ra_timer_w_timer *) timer->parent.user_data;

    if (state)
    {
        if (R_TIM_W_Open(tim->g_ctrl, tim->g_cfg) != FSP_SUCCESS)
        {
            LOG_E("%s init failed", tim->name);
            return;
        }

        tim->opened = RT_TRUE;
    }
    else if (tim->opened)
    {
        if (R_TIM_W_Close(tim->g_ctrl) != FSP_SUCCESS)
        {
            LOG_W("%s close failed", tim->name);
        }

        tim->opened = RT_FALSE;
    }
}

static rt_err_t timer_start(rt_clock_timer_t *timer, rt_uint32_t period,
                            rt_clock_timer_mode_t mode)
{
    struct ra_timer_w_timer *tim;

    RT_ASSERT(timer != RT_NULL);
    RT_UNUSED(mode);

    tim = (struct ra_timer_w_timer *) timer->parent.user_data;
    if (!tim->opened)
    {
        return -RT_ERROR;
    }

    /* TIM_W one-shot timing is stopped by rt_clock_timer_isr(). */
    if (R_TIM_W_Reset(tim->g_ctrl) != FSP_SUCCESS ||
        R_TIM_W_PeriodSet(tim->g_ctrl, period) != FSP_SUCCESS ||
        R_TIM_W_Start(tim->g_ctrl) != FSP_SUCCESS)
    {
        LOG_E("%s start failed", tim->name);
        return -RT_ERROR;
    }

    return RT_EOK;
}

static void timer_stop(rt_clock_timer_t *timer)
{
    struct ra_timer_w_timer *tim;

    RT_ASSERT(timer != RT_NULL);
    tim = (struct ra_timer_w_timer *) timer->parent.user_data;

    if (!tim->opened)
    {
        return;
    }

    (void) R_TIM_W_Stop(tim->g_ctrl);
    (void) R_TIM_W_Reset(tim->g_ctrl);
}

static rt_uint32_t timer_counter_get(rt_clock_timer_t *timer)
{
    struct ra_timer_w_timer *tim;
    timer_status_t status;

    RT_ASSERT(timer != RT_NULL);
    tim = (struct ra_timer_w_timer *) timer->parent.user_data;

    if (!tim->opened || (R_TIM_W_StatusGet(tim->g_ctrl, &status) != FSP_SUCCESS))
    {
        return 0;
    }

    return status.counter;
}

static rt_err_t timer_ctrl(rt_clock_timer_t *timer, rt_uint32_t cmd, void *arg)
{
    struct ra_timer_w_timer *tim;
    rt_uint32_t requested;
    rt_uint32_t actual;
    rt_uint32_t divider;

    RT_ASSERT(timer != RT_NULL);
    tim = (struct ra_timer_w_timer *) timer->parent.user_data;

    if (cmd != CLOCK_TIMER_CTRL_FREQ_SET)
    {
        return -RT_ENOSYS;
    }

    if (arg == RT_NULL)
    {
        return -RT_EINVAL;
    }

    requested = *((rt_uint32_t *) arg);
    if ((requested < RA_TIMER_W_MIN_FREQ) ||
        (requested > RA_TIMER_W_MAX_FREQ))
    {
        return -RT_EINVAL;
    }

    divider = ra_timer_w_freq_select(requested, &actual);
    tim->g_ctrl->p_reg->TIMER_PRE_SETTINGS_REG_b.TIM_PRESCALER2 = divider;

    /* clock_timer stores the value returned through arg as its active rate. */
    *((rt_uint32_t *) arg) = actual;
    return RT_EOK;
}

#if defined(BSP_USING_TIM0) && !defined(BSP_USING_PWM0)
void timer0_callback(timer_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if ((p_args != RT_NULL) && (p_args->event == TIMER_EVENT_CYCLE_END))
    {
        rt_clock_timer_isr(&ra_timer_w_timer_obj[BSP_TIMER0_INDEX].tmr_device);
    }
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_TIM1) && !defined(BSP_USING_PWM1)
void timer1_callback(timer_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if ((p_args != RT_NULL) && (p_args->event == TIMER_EVENT_CYCLE_END))
    {
        rt_clock_timer_isr(&ra_timer_w_timer_obj[BSP_TIMER1_INDEX].tmr_device);
    }
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_TIM2) && !defined(BSP_USING_PWM2)
void timer2_callback(timer_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if ((p_args != RT_NULL) && (p_args->event == TIMER_EVENT_CYCLE_END))
    {
        rt_clock_timer_isr(&ra_timer_w_timer_obj[BSP_TIMER2_INDEX].tmr_device);
    }
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_TIM3) && !defined(BSP_USING_PWM3)
void timer3_callback(timer_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if ((p_args != RT_NULL) && (p_args->event == TIMER_EVENT_CYCLE_END))
    {
        rt_clock_timer_isr(&ra_timer_w_timer_obj[BSP_TIMER3_INDEX].tmr_device);
    }
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_TIM4) && !defined(BSP_USING_PWM4)
void timer4_callback(timer_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if ((p_args != RT_NULL) && (p_args->event == TIMER_EVENT_CYCLE_END))
    {
        rt_clock_timer_isr(&ra_timer_w_timer_obj[BSP_TIMER4_INDEX].tmr_device);
    }
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_TIM5) && !defined(BSP_USING_PWM5)
void timer5_callback(timer_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if ((p_args != RT_NULL) && (p_args->event == TIMER_EVENT_CYCLE_END))
    {
        rt_clock_timer_isr(&ra_timer_w_timer_obj[BSP_TIMER5_INDEX].tmr_device);
    }
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_TIM6) && !defined(BSP_USING_PWM6)
void timer6_callback(timer_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if ((p_args != RT_NULL) && (p_args->event == TIMER_EVENT_CYCLE_END))
    {
        rt_clock_timer_isr(&ra_timer_w_timer_obj[BSP_TIMER6_INDEX].tmr_device);
    }
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_TIM7) && !defined(BSP_USING_PWM7)
void timer7_callback(timer_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if ((p_args != RT_NULL) && (p_args->event == TIMER_EVENT_CYCLE_END))
    {
        rt_clock_timer_isr(&ra_timer_w_timer_obj[BSP_TIMER7_INDEX].tmr_device);
    }
    rt_interrupt_leave();
}
#endif

static const struct rt_clock_timer_ops ra_timer_w_ops =
{
    .init       = timer_init,
    .start      = timer_start,
    .stop       = timer_stop,
    .count_get  = timer_counter_get,
    .control    = timer_ctrl,
};

static const struct rt_clock_timer_info ra_timer_w_info =
{
    .maxfreq = RA_TIMER_W_MAX_FREQ,
    .minfreq = RA_TIMER_W_MIN_FREQ,
    .maxcnt  = 0xFFFFFFFFU,
    .cntmode = CLOCK_TIMER_CNTMODE_UP,
};

static int rt_hw_timer_w_init(void)
{
    int result = RT_EOK;

    for (rt_size_t i = 0; i < RA_TIMER_W_TIMER_COUNT; i++)
    {
        ra_timer_w_timer_obj[i].tmr_device.info = &ra_timer_w_info;
        ra_timer_w_timer_obj[i].tmr_device.ops  = &ra_timer_w_ops;

        if (rt_clock_timer_register(&ra_timer_w_timer_obj[i].tmr_device,
                                    ra_timer_w_timer_obj[i].name,
                                    &ra_timer_w_timer_obj[i]) != RT_EOK)
        {
            LOG_E("%s register failed", ra_timer_w_timer_obj[i].name);
            result = -RT_ERROR;
        }
        else
        {
            LOG_D("%s register success", ra_timer_w_timer_obj[i].name);
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_timer_w_init);

#endif /* RT_USING_CLOCK_TIME */
