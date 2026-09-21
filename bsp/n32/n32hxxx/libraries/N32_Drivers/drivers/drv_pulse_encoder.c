/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-23     ox-horse     first version
 * 2026-08-19     ox-horse     Add N32H47X_48X
 * 2026-08-19     ox-horse     Add N32H49X
 */

#include <board.h>
#include "drv_config.h"

/* The driver owns the peripheral registers, so it pulls in the peripheral
 * header itself instead of relying on board.h to have declared it.
 */
#if defined(SOC_SERIES_N32H7xx)
#include <n32h7xx_tim.h>
#elif defined(SOC_SERIES_N32H49x)
#include <n32h49x_tim.h>
#elif defined(SOC_SERIES_N32H47x_48x)
#include <n32h47x_48x_tim.h>
#endif

#ifdef RT_USING_PULSE_ENCODER
#include "drv_tim.h"

//#define DRV_DEBUG
#define LOG_TAG "drv.pulse_encoder"
#include <drv_log.h>

/* NOTE: A timer instance must NOT be enabled for both clock-timer (BSP_USING_ATIMx/GTIMx/BTIMx)
 * and pulse-encoder (BSP_USING_PULSE_ENCODERx) simultaneously. The Kconfig should enforce
 * mutual exclusivity, otherwise ISR symbol conflicts will occur at link time.
 */

#if defined(SOC_SERIES_N32H7xx)
#if !defined(BSP_USING_PULSE_ENCODER1) && !defined(BSP_USING_PULSE_ENCODER2) && !defined(BSP_USING_PULSE_ENCODER3) && !defined(BSP_USING_PULSE_ENCODER4) && !defined(BSP_USING_PULSE_ENCODER5) && !defined(BSP_USING_PULSE_ENCODER6) && !defined(BSP_USING_PULSE_ENCODER7) && !defined(BSP_USING_PULSE_ENCODER8) && !defined(BSP_USING_PULSE_ENCODER9) && !defined(BSP_USING_PULSE_ENCODER10) && !defined(BSP_USING_PULSE_ENCODER11) && !defined(BSP_USING_PULSE_ENCODER12) && !defined(BSP_USING_PULSE_ENCODER13) && !defined(BSP_USING_PULSE_ENCODER14)
#error "Please define at least one BSP_USING_PULSE_ENCODERx"
#endif
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
#if !defined(BSP_USING_PULSE_ENCODER1) && !defined(BSP_USING_PULSE_ENCODER2) && !defined(BSP_USING_PULSE_ENCODER3) && !defined(BSP_USING_PULSE_ENCODER5) && !defined(BSP_USING_PULSE_ENCODER6) && !defined(BSP_USING_PULSE_ENCODER7) && !defined(BSP_USING_PULSE_ENCODER8) && !defined(BSP_USING_PULSE_ENCODER9) && !defined(BSP_USING_PULSE_ENCODER10) && !defined(BSP_USING_PULSE_ENCODER11) && !defined(BSP_USING_PULSE_ENCODER12) && !defined(BSP_USING_PULSE_ENCODER13) && !defined(BSP_USING_PULSE_ENCODER14)
#error "Please define at least one BSP_USING_PULSE_ENCODERx"
#endif
#endif /* SOC_SERIES_N32H7xx */

/* Auto-reload value for 16-bit encoder mode. Using half of the range
 * allows for overflow tracking in both directions. */
#define AUTO_RELOAD_VALUE 0x7FFF

enum
{
#ifdef BSP_USING_PULSE_ENCODER1
    PULSE_ENCODER1_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER2
    PULSE_ENCODER2_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER3
    PULSE_ENCODER3_INDEX,
#endif
#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_PULSE_ENCODER4
    PULSE_ENCODER4_INDEX,
#endif
#endif /* SOC_SERIES_N32H7xx */
#ifdef BSP_USING_PULSE_ENCODER5
    PULSE_ENCODER5_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER6
    PULSE_ENCODER6_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER7
    PULSE_ENCODER7_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER8
    PULSE_ENCODER8_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER9
    PULSE_ENCODER9_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER10
    PULSE_ENCODER10_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER11
    PULSE_ENCODER11_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER12
    PULSE_ENCODER12_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER13
    PULSE_ENCODER13_INDEX,
#endif
#ifdef BSP_USING_PULSE_ENCODER14
    PULSE_ENCODER14_INDEX,
#endif
};

struct n32_pulse_encoder_device
{
    struct rt_pulse_encoder_device pulse_encoder;
    TIM_Module *timer;
    IRQn_Type tim_irqn;
    rt_int32_t over_under_flowcount;
    char *name;
};

static struct n32_pulse_encoder_device n32_pulse_encoder_obj[] = {
#ifdef BSP_USING_PULSE_ENCODER1
    PULSE_ENCODER1_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER2
    PULSE_ENCODER2_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER3
    PULSE_ENCODER3_CONFIG,
#endif
#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_PULSE_ENCODER4
    PULSE_ENCODER4_CONFIG,
#endif
#endif /* SOC_SERIES_N32H7xx */
#ifdef BSP_USING_PULSE_ENCODER5
    PULSE_ENCODER5_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER6
    PULSE_ENCODER6_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER7
    PULSE_ENCODER7_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER8
    PULSE_ENCODER8_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER9
    PULSE_ENCODER9_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER10
    PULSE_ENCODER10_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER11
    PULSE_ENCODER11_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER12
    PULSE_ENCODER12_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER13
    PULSE_ENCODER13_CONFIG,
#endif
#ifdef BSP_USING_PULSE_ENCODER14
    PULSE_ENCODER14_CONFIG,
#endif
};

static rt_uint32_t pulse_encoder_auto_reload_get(TIM_Module *timer)
{
#if defined(SOC_SERIES_N32H49x)
    if (IS_GTIM1_4_DEVICE(timer))
    {
        return 0x7FFFFFFFU;
    }
#endif /* SOC_SERIES_N32H49x */

    return AUTO_RELOAD_VALUE;
}

/**
 * @brief Initialize the pulse encoder hardware.
 */
static rt_err_t pulse_encoder_init(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct n32_pulse_encoder_device *n32_device;
    TIM_TimeBaseInitType TIM_TimeBaseStructure;

    n32_device = (struct n32_pulse_encoder_device *)pulse_encoder;

    /* Enable timer clock */
    n32_tim_enable_clock(n32_device->timer);

    /* Configure time base for encoder mode */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.CounterMode = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period = pulse_encoder_auto_reload_get(n32_device->timer);
    TIM_TimeBaseStructure.ClkDiv = TIM_CLK_DIV1;
    TIM_InitTimeBase(n32_device->timer, &TIM_TimeBaseStructure);

    /* Limit update interrupt source to counter overflow/underflow only (URS equivalent) */
    TIM_ConfigUpdateRequestIntSrc(n32_device->timer, TIM_UPDATE_SRC_REGULAR);

    /* Configure encoder interface in quadrature mode (TI1 + TI2) */
    TIM_ConfigEncoderInterface(n32_device->timer,
                               TIM_ENCODE_QUA_MODE_TI12,
                               TIM_IC_POLARITY_RISING,
                               TIM_IC_POLARITY_RISING);

    /* Configure TI1 and TI2 input capture with filter */
    ConfigTI1(n32_device->timer, TIM_IC_POLARITY_RISING, TIM_IC_SELECTION_DIRECTTI, 3);
    ConfigTI2(n32_device->timer, TIM_IC_POLARITY_RISING, TIM_IC_SELECTION_DIRECTTI, 3);

    /* Configure NVIC for update interrupt (overflow tracking) */
    NVIC_SetPriority(n32_device->tim_irqn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 3, 0));
    NVIC_EnableIRQ(n32_device->tim_irqn);

    /* Clear update flag and enable update interrupt source */
    TIM_ClearFlag(n32_device->timer, TIM_FLAG_UPDATE);
#if defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
    TIM_ConfigUpdateEvt(n32_device->timer, ENABLE);
#else
    /* N32H7xx has no TIM_ConfigUpdateEvt, and its TIM_EnableUpdateEvt is
     * named backwards: ENABLE *sets* CTRL1.UPDIS, which suppresses update
     * events, and TIM_ConfigInt above only wrote DINTEN.  UIF would never
     * be raised, so pulse_encoder_update_isr() would never run and the
     * count would silently wrap at 0x7FFF instead of tracking the encoder.
     * DISABLE clears UPDIS and re-enables the event.
     */
    TIM_EnableUpdateEvt(n32_device->timer, DISABLE);
#endif

    LOG_D("%s init success", n32_device->name);

    return RT_EOK;
}

/**
 * @brief Get the accumulated encoder count (handles counter overflow).
 */
static rt_int32_t pulse_encoder_get_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct n32_pulse_encoder_device *n32_device;
    rt_uint32_t auto_reload;
    rt_int64_t count;

    n32_device = (struct n32_pulse_encoder_device *)pulse_encoder;
    auto_reload = pulse_encoder_auto_reload_get(n32_device->timer);
    count = TIM_GetCnt(n32_device->timer);
    count += (rt_int64_t)n32_device->over_under_flowcount * ((rt_int64_t)auto_reload + 1);

    return (rt_int32_t)count;
}

/**
 * @brief Clear the encoder count and overflow accumulator.
 */
static rt_err_t pulse_encoder_clear_count(struct rt_pulse_encoder_device *pulse_encoder)
{
    struct n32_pulse_encoder_device *n32_device;

    n32_device = (struct n32_pulse_encoder_device *)pulse_encoder;

    n32_device->over_under_flowcount = 0;
    TIM_SetCnt(n32_device->timer, 0);

    return RT_EOK;
}

/**
 * @brief Control the pulse encoder (enable/disable).
 */
static rt_err_t pulse_encoder_control(struct rt_pulse_encoder_device *pulse_encoder, rt_uint32_t cmd, void *args)
{
    rt_err_t result;
    struct n32_pulse_encoder_device *n32_device;

    n32_device = (struct n32_pulse_encoder_device *)pulse_encoder;
    result = RT_EOK;

    switch (cmd)
    {
    case PULSE_ENCODER_CMD_ENABLE:
        /* Enable update interrupt for overflow tracking */
        TIM_ConfigInt(n32_device->timer, TIM_INT_UPDATE, ENABLE);
        /* Enable timer counter */
        TIM_Enable(n32_device->timer, ENABLE);
        break;

    case PULSE_ENCODER_CMD_DISABLE:
        /* Disable update interrupt */
        TIM_ConfigInt(n32_device->timer, TIM_INT_UPDATE, DISABLE);
        /* Stop timer counter */
        TIM_Enable(n32_device->timer, DISABLE);
        break;

    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

/**
 * @brief ISR update handler: track overflow/underflow for 32-bit position accumulation.
 */
static void pulse_encoder_update_isr(struct n32_pulse_encoder_device *device)
{
    /* TIM Update event (overflow/underflow) */
    if (TIM_GetFlagStatus(device->timer, TIM_FLAG_UPDATE) != RESET)
    {
        TIM_ClearFlag(device->timer, TIM_FLAG_UPDATE);

        /* Check counting direction */
        if ((device->timer->CTRL1 & TIM_CNT_MODE_DOWN) != 0U)
        {
            device->over_under_flowcount--;
        }
        else
        {
            device->over_under_flowcount++;
        }
    }
    /* Capture compare 1 event */
    if (TIM_GetFlagStatus(device->timer, TIM_FLAG_CC1) != RESET)
    {
        TIM_ClearFlag(device->timer, TIM_FLAG_CC1);
    }
    /* Capture compare 2 event */
    if (TIM_GetFlagStatus(device->timer, TIM_FLAG_CC2) != RESET)
    {
        TIM_ClearFlag(device->timer, TIM_FLAG_CC2);
    }
    /* Capture compare 3 event */
    if (TIM_GetFlagStatus(device->timer, TIM_FLAG_CC3) != RESET)
    {
        TIM_ClearFlag(device->timer, TIM_FLAG_CC3);
    }
    /* Capture compare 4 event */
    if (TIM_GetFlagStatus(device->timer, TIM_FLAG_CC4) != RESET)
    {
        TIM_ClearFlag(device->timer, TIM_FLAG_CC4);
    }
    /* Break input event */
    if (TIM_GetFlagStatus(device->timer, TIM_FLAG_BREAK) != RESET)
    {
        TIM_ClearFlag(device->timer, TIM_FLAG_BREAK);
    }
    /* Trigger detection event */
    if (TIM_GetFlagStatus(device->timer, TIM_FLAG_TRIG) != RESET)
    {
        TIM_ClearFlag(device->timer, TIM_FLAG_TRIG);
    }
    /* Commutation event */
    if (TIM_GetFlagStatus(device->timer, TIM_FLAG_COM) != RESET)
    {
        TIM_ClearFlag(device->timer, TIM_FLAG_COM);
    }
}

/* ---- ISR Handlers ---- */

#ifdef BSP_USING_PULSE_ENCODER1
void ATIM1_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER1_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER2
void ATIM2_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER2_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER3
void ATIM3_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER3_INDEX]);
    rt_interrupt_leave();
}
#endif

#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_PULSE_ENCODER4
void ATIM4_UP_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER4_INDEX]);
    rt_interrupt_leave();
}
#endif
#endif /* SOC_SERIES_N32H7xx */

#if defined(SOC_SERIES_N32H7xx)
#ifdef BSP_USING_PULSE_ENCODER5
void GTIMA1_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER5_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER6
void GTIMA2_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER6_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER7
void GTIMA3_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER7_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER8
void GTIMA4_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER8_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER9
void GTIMA5_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER9_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER10
void GTIMA6_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER10_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER11
void GTIMA7_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER11_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER12
void GTIMB1_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER12_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER13
void GTIMB2_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER13_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER14
void GTIMB3_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER14_INDEX]);
    rt_interrupt_leave();
}
#endif
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
#ifdef BSP_USING_PULSE_ENCODER5
void GTIM1_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER5_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER6
void GTIM2_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER6_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER7
void GTIM3_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER7_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER8
void GTIM4_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER8_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER9
void GTIM5_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER9_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER10
void GTIM6_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER10_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER11
void GTIM7_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER11_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER12
void GTIM8_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER12_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER13
void GTIM9_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER13_INDEX]);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_PULSE_ENCODER14
void GTIM10_IRQHandler(void)
{
    rt_interrupt_enter();
    pulse_encoder_update_isr(&n32_pulse_encoder_obj[PULSE_ENCODER14_INDEX]);
    rt_interrupt_leave();
}
#endif
#endif /* SOC_SERIES_N32H7xx */

/* ---- Device Registration ---- */

static const struct rt_pulse_encoder_ops _ops = {
    .init = pulse_encoder_init,
    .get_count = pulse_encoder_get_count,
    .clear_count = pulse_encoder_clear_count,
    .control = pulse_encoder_control,
};

static int n32_pulse_encoder_init(void)
{
    int i;
    int result;

    result = RT_EOK;
    for (i = 0; i < sizeof(n32_pulse_encoder_obj) / sizeof(n32_pulse_encoder_obj[0]); i++)
    {
        n32_pulse_encoder_obj[i].pulse_encoder.type = AB_PHASE_PULSE_ENCODER;
        n32_pulse_encoder_obj[i].pulse_encoder.ops = &_ops;

        if (rt_device_pulse_encoder_register(&n32_pulse_encoder_obj[i].pulse_encoder,
                                             n32_pulse_encoder_obj[i].name, RT_NULL) != RT_EOK)
        {
            LOG_E("%s register failed", n32_pulse_encoder_obj[i].name);
            result = -RT_ERROR;
        }
        else
        {
            LOG_D("%s register success", n32_pulse_encoder_obj[i].name);
        }
    }

    return result;
}
INIT_BOARD_EXPORT(n32_pulse_encoder_init);

#endif /* RT_USING_PULSE_ENCODER */
