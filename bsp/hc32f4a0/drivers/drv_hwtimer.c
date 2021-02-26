/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */

#include <rtdevice.h>
#include <rtdbg.h>

#ifdef RT_USING_HWTIMER

#if !defined(BSP_USING_TIMER1)  && !defined(BSP_USING_TIMER2)  && !defined(BSP_USING_TIMER3) && \
    !defined(BSP_USING_TIMER4)  && !defined(BSP_USING_TIMER5)  && !defined(BSP_USING_TIMER6) && \
    !defined(BSP_USING_TIMER7)  && !defined(BSP_USING_TIMER8)  && !defined(BSP_USING_TIMER9) && \
    !defined(BSP_USING_TIMER10) && !defined(BSP_USING_TIMER11) && !defined(BSP_USING_TIMER12)
#error "Please define at least one BSP_USING_TIMERx"
/* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable TIMER */
#endif

#include "drv_hwtimer.h"
#include "drv_irq.h"

enum
{
#ifdef BSP_USING_TIMER1
    TIMER1_INDEX,
#endif
#ifdef BSP_USING_TIMER2
    TIMER2_INDEX,
#endif
#ifdef BSP_USING_TIMER3
    TIMER3_INDEX,
#endif
#ifdef BSP_USING_TIMER4
    TIMER4_INDEX,
#endif
#ifdef BSP_USING_TIMER5
    TIMER5_INDEX,
#endif
#ifdef BSP_USING_TIMER6
    TIMER6_INDEX,
#endif
#ifdef BSP_USING_TIMER7
    TIMER7_INDEX,
#endif
#ifdef BSP_USING_TIMER8
    TIMER8_INDEX,
#endif
#ifdef BSP_USING_TIMER9
    TIMER9_INDEX,
#endif
#ifdef BSP_USING_TIMER10
    TIMER10_INDEX,
#endif
#ifdef BSP_USING_TIMER11
    TIMER11_INDEX,
#endif
#ifdef BSP_USING_TIMER12
    TIMER12_INDEX,
#endif
};

#ifdef BSP_USING_TIMER1
static void timer1_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER2
static void timer2_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER3
static void timer3_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER4
static void timer4_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER5
static void timer5_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER6
static void timer6_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER7
static void timer7_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER8
static void timer8_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER9
static void timer9_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER10
static void timer10_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER11
static void timer11_irq_handler(void);
#endif
#ifdef BSP_USING_TIMER12
static void timer12_irq_handler(void);
#endif

struct hc32_hwtimer_config
{
    rt_hwtimer_t           time_device;
    M4_TMRA_TypeDef        *timer_periph;
    struct hc32_irq_config irq_config;
    func_ptr_t             irq_callback;
    uint32_t               extend_div;
    uint32_t               extend_cnt;
    char                   *name;
};

#ifndef HC32_TIMER_CONFIG
#define HC32_TIMER_CONFIG(periph, irq, label, src, irq_info)                   \
    {                                                                          \
        .timer_periph       = periph,                                          \
        .irq_callback       = irq,                                             \
        .name               = label,                                           \
        .irq_config         = irq_info,                                        \
        .irq_config.int_src = src,                                             \
    }
#endif /* HC32_TIMER_CONFIG */

static struct hc32_hwtimer_config hwtimer_obj[] =
{
#ifdef BSP_USING_TIMER1
    HC32_TIMER_CONFIG(M4_TMRA_1,  timer1_irq_handler,  "timer1",  INT_TMRA_1_OVF,  TIMER1_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER2
    HC32_TIMER_CONFIG(M4_TMRA_2,  timer2_irq_handler,  "timer2",  INT_TMRA_2_OVF,  TIMER2_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER3
    HC32_TIMER_CONFIG(M4_TMRA_3,  timer3_irq_handler,  "timer3",  INT_TMRA_3_OVF,  TIMER3_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER4
    HC32_TIMER_CONFIG(M4_TMRA_4,  timer4_irq_handler,  "timer4",  INT_TMRA_4_OVF,  TIMER4_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER5
    HC32_TIMER_CONFIG(M4_TMRA_5,  timer5_irq_handler,  "timer5",  INT_TMRA_5_OVF,  TIMER5_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER6
    HC32_TIMER_CONFIG(M4_TMRA_6,  timer6_irq_handler,  "timer6",  INT_TMRA_6_OVF,  TIMER6_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER7
    HC32_TIMER_CONFIG(M4_TMRA_7,  timer7_irq_handler,  "timer7",  INT_TMRA_7_OVF,  TIMER7_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER8
    HC32_TIMER_CONFIG(M4_TMRA_8,  timer8_irq_handler,  "timer8",  INT_TMRA_8_OVF,  TIMER8_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER9
    HC32_TIMER_CONFIG(M4_TMRA_9,  timer9_irq_handler,  "timer9",  INT_TMRA_9_OVF,  TIMER9_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER10
    HC32_TIMER_CONFIG(M4_TMRA_10, timer10_irq_handler, "timer10", INT_TMRA_10_OVF, TIMER10_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER11
    HC32_TIMER_CONFIG(M4_TMRA_11, timer11_irq_handler, "timer11", INT_TMRA_11_OVF, TIMER11_IRQ_CONFIG),
#endif
#ifdef BSP_USING_TIMER12
    HC32_TIMER_CONFIG(M4_TMRA_12, timer12_irq_handler, "timer12", INT_TMRA_12_OVF, TIMER12_IRQ_CONFIG),
#endif
};

static void hc32_timer_irq_handler(struct hc32_hwtimer_config *timer_config)
{
    if ((++timer_config->extend_cnt) >= timer_config->extend_div)
    {
        timer_config->extend_cnt = 0;
        rt_device_hwtimer_isr(&timer_config->time_device);
    }
    TMRA_ClrStatus(timer_config->timer_periph, (TMRA_FLAG_OVF | TMRA_FLAG_UNF));
}

#ifdef BSP_USING_TIMER1
static void timer1_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER1_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER2
static void timer2_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER2_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER3
static void timer3_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER3_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER4
static void timer4_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER4_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER5
static void timer5_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER5_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER6
static void timer6_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER6_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER7
static void timer7_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER7_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER8
static void timer8_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER8_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER9
static void timer9_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER9_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER10
static void timer10_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER10_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER11
static void timer11_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER11_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIMER12
static void timer12_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_timer_irq_handler(&hwtimer_obj[TIMER12_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static rt_uint16_t hc32_timer_get_unit_number(M4_TMRA_TypeDef *TMRAx)
{
    rt_uint16_t unit_num;
    const rt_uint32_t unit_step = 0x400U;

    if (((rt_uint32_t)TMRAx) >= ((rt_uint32_t)M4_TMRA_1))
    {
        unit_num = (((rt_uint32_t)TMRAx) - ((rt_uint32_t)M4_TMRA_1)) / unit_step;
    }
    else
    {
        unit_num = (((rt_uint32_t)TMRAx) - ((rt_uint32_t)M4_TMRA_5)) / unit_step + 4;
    }

    return unit_num;
}

static void hc32_timer_clock_config(M4_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    rt_uint32_t timer_periph;
    rt_uint16_t unit_num;

    unit_num     = hc32_timer_get_unit_number(TMRAx);
    timer_periph = PWC_FCG2_TMRA_1 << unit_num;
    PWC_Fcg2PeriphClockCmd(timer_periph, enNewState);
}

static void hc32_timer_get_div_value(M4_TMRA_TypeDef *TMRAx, uint32_t freq, uint16_t *div, uint32_t *extend_div)
{
    stc_clk_freq_t stcClkFreq;
    rt_uint32_t divisor, remainder;
    rt_uint16_t div_val;
    rt_uint32_t clk_freq;
    rt_uint16_t unit_num;

    CLK_GetClockFreq(&stcClkFreq);
    unit_num = hc32_timer_get_unit_number(TMRAx);
    if (unit_num >= 4)
    {
        clk_freq = stcClkFreq.pclk1Freq;
    }
    else
    {
        clk_freq = stcClkFreq.pclk0Freq;
    }
    divisor   = clk_freq / freq;
    remainder = clk_freq % freq;
    for (div_val=1; div_val<=1024; div_val<<=1)
    {
        if (((divisor % 2) == 0) && (remainder == 0))
        {
            remainder = divisor % 2;
            divisor   = divisor / 2;
        }
        else
        {
            break;
        }
    }
    *extend_div = divisor;
    *div        = (__CLZ(__RBIT(div_val))) << TMRA_BCSTR_CKDIV_POS;
}

static void hc32_timer_interrupt_config(struct rt_hwtimer_device *timer, en_functional_state_t enNewState)
{
    struct hc32_hwtimer_config *timer_config = RT_NULL;

    timer_config = (struct hc32_hwtimer_config *)timer;
    if (INT_MAX == timer_config->irq_config.int_src)
    {
        LOG_D("%s interrupt init failed", timer_config->name);
        return;
    }

    if (Enable == enNewState)
    {
        /* Enable the specified interrupts of Timer */
        hc32_install_irq_handler(&timer_config->irq_config, timer_config->irq_callback, RT_FALSE);
        NVIC_EnableIRQ(timer_config->irq_config.irq);
        TMRA_IntCmd(timer_config->timer_periph, TMRA_INT_OVF, Enable);
    }
    else
    {
        /* Disable the specified interrupts of Timer */
        TMRA_IntCmd(timer_config->timer_periph, TMRA_INT_OVF, Disable);
        NVIC_DisableIRQ(timer_config->irq_config.irq);
    }
}

static void hc32_timer_init(struct rt_hwtimer_device *timer, rt_uint32_t state)
{
    stc_tmra_init_t stcTmraInit;
    struct hc32_hwtimer_config *timer_config = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    timer_config = (struct hc32_hwtimer_config *)timer;
    if (state)
    {
        /* Enable Timer peripheral clock. */
        hc32_timer_clock_config(timer_config->timer_periph, Enable);
        TMRA_DeInit(timer_config->timer_periph);
        TMRA_StructInit(&stcTmraInit);
        stcTmraInit.u32CntDir = TMRA_DIR_UP;
        TMRA_Init(timer_config->timer_periph, &stcTmraInit);
        LOG_D("%s init success", timer_config->name);
    }
    else
    {
        TMRA_DeInit(timer_config->timer_periph);
        hc32_timer_interrupt_config(timer, Disable);
        /* Disable Timer peripheral clock. */
        hc32_timer_clock_config(timer_config->timer_periph, Disable);
    }
}

static rt_err_t hc32_timer_start(struct rt_hwtimer_device *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    rt_err_t result = RT_EOK;
    struct hc32_hwtimer_config *timer_config = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    timer_config = (struct hc32_hwtimer_config *)timer;
    if (mode == HWTIMER_MODE_ONESHOT)
    {
        TMRA_SetOvfOperation(timer_config->timer_periph, TMRA_OVF_CNT_STOP);
    }
    else
    {
        TMRA_SetOvfOperation(timer_config->timer_periph, TMRA_OVF_CNT_CONTINUE);
    }
    timer_config->extend_cnt = 0;
    TMRA_SetCntVal(timer_config->timer_periph, 0);
    TMRA_SetPeriodVal(timer_config->timer_periph, cnt - 1);
    hc32_timer_interrupt_config(timer, Enable);
    TMRA_Start(timer_config->timer_periph);

    return result;
}

static void hc32_timer_stop(struct rt_hwtimer_device *timer)
{
    struct hc32_hwtimer_config *timer_config = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    timer_config = (struct hc32_hwtimer_config *)timer;
    /* stop timer */
    TMRA_Stop(timer_config->timer_periph);
    hc32_timer_interrupt_config(timer, Disable);
    TMRA_SetCntVal(timer_config->timer_periph, 0);
}

static rt_uint32_t hc32_timer_get_counter(struct rt_hwtimer_device *timer)
{
    rt_uint32_t count_val;
    rt_uint32_t period_val;
    float temp;
    struct hc32_hwtimer_config *timer_config = RT_NULL;

    RT_ASSERT(timer != RT_NULL);
    timer_config = (struct hc32_hwtimer_config *)timer;
    period_val = TMRA_GetPeriodVal(timer_config->timer_periph);
    count_val  = TMRA_GetCntVal(timer_config->timer_periph);
    temp = (timer_config->extend_cnt * period_val + count_val);
    temp = temp / (timer_config->extend_div * period_val) * period_val;
    count_val = (rt_uint32_t)temp;

    return count_val;
}

static rt_err_t hc32_timer_ctrl(struct rt_hwtimer_device *timer, rt_uint32_t cmd, void *args)
{
    struct hc32_hwtimer_config *timer_config = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(timer != RT_NULL);
    RT_ASSERT(args != RT_NULL);
    timer_config = (struct hc32_hwtimer_config *)timer;
    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        rt_uint32_t freq;
        rt_uint16_t div_val;
        rt_uint32_t extend_div_val;

        /* set timer frequency */
        freq = *((rt_uint32_t *)args);
        hc32_timer_get_div_value(timer_config->timer_periph, freq, &div_val, &extend_div_val);
        TMRA_SetPCLKDiv(timer_config->timer_periph, div_val);
        timer_config->extend_div = extend_div_val;
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

static const struct rt_hwtimer_ops hwtimer_ops =
{
    .init      = hc32_timer_init,
    .start     = hc32_timer_start,
    .stop      = hc32_timer_stop,
    .count_get = hc32_timer_get_counter,
    .control   = hc32_timer_ctrl,
};

static const struct rt_hwtimer_info hwtimer_info =
{
    .maxfreq = 30000000,
    .minfreq = 1000,
    .maxcnt  = 0xFFFF,
    .cntmode = HWTIMER_CNTMODE_UP,
};

static int rt_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(hwtimer_obj) / sizeof(hwtimer_obj[0]); i++)
    {
        hwtimer_obj[i].time_device.info = &hwtimer_info;
        hwtimer_obj[i].time_device.ops  = &hwtimer_ops;
        if (rt_device_hwtimer_register(&hwtimer_obj[i].time_device, hwtimer_obj[i].name, hwtimer_obj[i].timer_periph) == RT_EOK)
        {
            LOG_D("%s register success", hwtimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", hwtimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hwtimer_init);

#endif /* RT_USING_HWTIMER */
