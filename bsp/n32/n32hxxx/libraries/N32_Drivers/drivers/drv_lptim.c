/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2026-06-23     ox-horse        first version
 */

#include <board.h>
#include <drv_lptim.h>
#include <rtdevice.h>
#include "drv_config.h"
#include "n32h7xx_exti.h"

/*#define DRV_DEBUG*/
#define LOG_TAG "drv.lptim"
#include <drv_log.h>

#ifdef BSP_USING_LPTIM

#define LPTIM_REG_MAX_VALUE (0xFFFF)

enum
{
#ifdef BSP_USING_LPTIM1
    LPTIM1_INDEX,
#endif
#ifdef BSP_USING_LPTIM2
    LPTIM2_INDEX,
#endif
#ifdef BSP_USING_LPTIM3
    LPTIM3_INDEX,
#endif
#ifdef BSP_USING_LPTIM4
    LPTIM4_INDEX,
#endif
#ifdef BSP_USING_LPTIM5
    LPTIM5_INDEX,
#endif
};

struct n32_hw_lptimer
{
    rt_clock_timer_t time_device;
    LPTIM_Module    *timer;
    IRQn_Type        tim_irqn;
    char            *name;
};

static struct n32_hw_lptimer n32_hw_lptimer_obj[] = {
#ifdef BSP_USING_LPTIM1
    LPTIM1_CONFIG,
#endif
#ifdef BSP_USING_LPTIM2
    LPTIM2_CONFIG,
#endif
#ifdef BSP_USING_LPTIM3
    LPTIM3_CONFIG,
#endif
#ifdef BSP_USING_LPTIM4
    LPTIM4_CONFIG,
#endif
#ifdef BSP_USING_LPTIM5
    LPTIM5_CONFIG,
#endif
};

/**
 * Configure LPTIM clock source to LSI.
 * Each LPTIM has a 4-bit clock selection field in RCC_RDSEL1 at different bit positions.
 * LPTIM1: bits [31:28], LPTIM2: bits [27:24], LPTIM3: bits [23:20],
 * LPTIM4: bits [19:16], LPTIM5: bits [15:12].
 * LSI value = 0x1 shifted to the field position.
 */
static void n32_lptim_clock_source_config(LPTIM_Module *timer)
{
    if (timer == LPTIM1)
    {
        RCC_ConfigLPTIM1Clk(RCC_LPTIMCLK_SRC_LSI);
    }
    else if (timer == LPTIM2)
    {
        RCC_ConfigLPTIM2Clk(RCC_LPTIMCLK_SRC_LSI);
    }
    else if (timer == LPTIM3)
    {
        RCC_ConfigLPTIM3Clk(RCC_LPTIMCLK_SRC_LSI);
    }
    else if (timer == LPTIM4)
    {
        RCC_ConfigLPTIM4Clk(RCC_LPTIMCLK_SRC_LSI);
    }
    else if (timer == LPTIM5)
    {
        RCC_ConfigLPTIM5Clk(RCC_LPTIMCLK_SRC_LSI);
    }
}

/**
 * Enable RD (Retention Domain) peripheral clock for the given LPTIM.
 */
static void n32_lptim_enable_clock(LPTIM_Module *timer)
{
    if (timer == LPTIM1)
    {
        RCC_EnableRDPeriphClk1(RCC_RD_PERIPHEN_M7_LPTIM1 | RCC_RD_PERIPHEN_M4_LPTIM1 |
                                   RCC_RD_PERIPHEN_M7_LPTIM1LP | RCC_RD_PERIPHEN_M4_LPTIM1LP,
                               ENABLE);
    }
    else if (timer == LPTIM2)
    {
        RCC_EnableRDPeriphClk1(RCC_RD_PERIPHEN_M7_LPTIM2 | RCC_RD_PERIPHEN_M4_LPTIM2 |
                                   RCC_RD_PERIPHEN_M7_LPTIM2LP | RCC_RD_PERIPHEN_M4_LPTIM2LP,
                               ENABLE);
    }
    else if (timer == LPTIM3)
    {
        RCC_EnableRDPeriphClk1(RCC_RD_PERIPHEN_M7_LPTIM3 | RCC_RD_PERIPHEN_M4_LPTIM3 |
                                   RCC_RD_PERIPHEN_M7_LPTIM3LP | RCC_RD_PERIPHEN_M4_LPTIM3LP,
                               ENABLE);
    }
    else if (timer == LPTIM4)
    {
        RCC_EnableRDPeriphClk1(RCC_RD_PERIPHEN_M7_LPTIM4 | RCC_RD_PERIPHEN_M4_LPTIM4 |
                                   RCC_RD_PERIPHEN_M7_LPTIM4LP | RCC_RD_PERIPHEN_M4_LPTIM4LP,
                               ENABLE);
    }
    else if (timer == LPTIM5)
    {
        RCC_EnableRDPeriphClk1(RCC_RD_PERIPHEN_M7_LPTIM5 | RCC_RD_PERIPHEN_M4_LPTIM5 |
                                   RCC_RD_PERIPHEN_M7_LPTIM5LP | RCC_RD_PERIPHEN_M4_LPTIM5LP,
                               ENABLE);
    }
}

/**
 * Get EXTI line for the given LPTIM.
 * LPTIM1 -> EXTI 66, LPTIM2 -> EXTI 67, LPTIM3 -> EXTI 68,
 * LPTIM4 -> EXTI 69, LPTIM5 -> EXTI 86
 */
static uint32_t n32_lptim_get_exti_line(LPTIM_Module *timer)
{
    if (timer == LPTIM1)
        return EXTI_LINE66;
    else if (timer == LPTIM2)
        return EXTI_LINE67;
    else if (timer == LPTIM3)
        return EXTI_LINE68;
    else if (timer == LPTIM4)
        return EXTI_LINE69;
    else if (timer == LPTIM5)
        return EXTI_LINE86;
    else
        return 0;
}

/**
 * Configure EXTI interrupt line for LPTIM wakeup.
 */
static void n32_lptim_exti_config(LPTIM_Module *timer)
{
    uint32_t exti_line = n32_lptim_get_exti_line(timer);
    if (exti_line == 0)
        return;

    EXTI_InitType EXTI_InitStructure;
    EXTI_InitStruct(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line    = exti_line;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitPeripheral(&EXTI_InitStructure);
}

/**
 * Clear EXTI pending bit for LPTIM wakeup.
 */
static void n32_lptim_clear_exti_flag(LPTIM_Module *timer)
{
    uint32_t exti_line = n32_lptim_get_exti_line(timer);
    if (exti_line != 0)
    {
        EXTI_ClrITPendBit(exti_line);
    }
}

static const struct rt_clock_timer_info _info = LPTIM_DEV_INFO_CONFIG;

static void timer_init(struct rt_clock_timer_device *timer, rt_uint32_t state)
{
    if (timer == RT_NULL)
    {
        LOG_E("init timer is NULL");
        return;
    }

    if (state)
    {
        struct n32_hw_lptimer *tim_device = rt_container_of(timer, struct n32_hw_lptimer, time_device);
        LPTIM_Module          *lptim      = tim_device->timer;

        if (tim_device == RT_NULL)
        {
            LOG_E("start tim_device is NULL");
            return;
        }
        if (lptim == RT_NULL)
        {
            LOG_E("start %s LPTIM is NULL", tim_device->name);
            return;
        }

        /* Enable LSI clock for LPTIM */
        RCC_EnableLsi(ENABLE);

        /* Wait for LSI ready */
        while (RCC_GetFlagStatus(RCC_FLAG_LSIRD) == RESET)
            ;

        /* Select LSI as LPTIM clock source */
        n32_lptim_clock_source_config(lptim);

        /* Enable LPTIM peripheral clock */
        n32_lptim_enable_clock(lptim);

        /* Configure LPTIM */
        LPTIM_InitType lptim_init;
        LPTIM_StructInit(&lptim_init);
        lptim_init.ClockSource = LPTIM_CLK_SOURCE_INTERNAL;
        lptim_init.Prescaler   = LPTIM_PRESCALER_DIV32;

        if (LPTIM_Init(lptim, &lptim_init) != SUCCESS)
        {
            LOG_E("%s init failed", tim_device->name);
            return;
        }

        /* Set registers update mode to immediate (same as STM32 LPTIM_UPDATE_IMMEDIATE) */
        LPTIM_SetUpdateMode(lptim, LPTIM_UPDATE_MODE_IMMEDIATE);

        /* Enable EXTI clock and configure EXTI line for LPTIM wakeup interrupt */
        RCC_EnableAPB5PeriphClk2(RCC_APB5_PERIPHEN_EXTI, ENABLE);
        n32_lptim_exti_config(lptim);

        /* Configure NVIC */
        NVIC_ClearPendingIRQ(tim_device->tim_irqn);
        NVIC_SetPriority(tim_device->tim_irqn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
        NVIC_EnableIRQ(tim_device->tim_irqn);

        LOG_D("%s init success", tim_device->name);
    }
}

static rt_err_t timer_start(rt_clock_timer_t *timer, rt_uint32_t t, rt_clock_timer_mode_t opmode)
{
    if (timer == RT_NULL)
    {
        LOG_E("start timer is NULL");
        return -RT_EINVAL;
    }

    struct n32_hw_lptimer *tim_device = rt_container_of(timer, struct n32_hw_lptimer, time_device);
    LPTIM_Module          *lptim      = tim_device->timer;

    if (tim_device == RT_NULL)
    {
        LOG_E("start tim_device is NULL");
        return -RT_EINVAL;
    }
    if (lptim == RT_NULL)
    {
        LOG_E("start %s LPTIM is NULL", tim_device->name);
        return -RT_EINVAL;
    }

    /* Enable timeout function */
    LPTIM_TimeoutCmd(lptim, ENABLE);

    /* Enable compare match interrupt */
    LPTIM_ConfigInt(lptim, LPTIM_COMP_MATCH_INT, ENABLE);

    /* Enable LPTIM peripheral */
    LPTIM_Cmd(lptim, ENABLE);
    /* Set the auto-reload and compare values */
    LPTIM_SetAutoReloadValue(lptim, LPTIM_REG_MAX_VALUE);
    LPTIM_SetCompareValue(lptim, t);

    /* Start counter in specified mode */
    if (opmode == CLOCK_TIMER_MODE_ONESHOT)
    {
        LPTIM_StartCounter(lptim, LPTIM_OPERATING_MODE_ONESHOT);
    }
    else
    {
        LPTIM_StartCounter(lptim, LPTIM_OPERATING_MODE_CONTINUOUS);
    }

    LOG_D("start %s success, timeout=%d", tim_device->name, t);
    return RT_EOK;
}

static void timer_stop(rt_clock_timer_t *timer)
{
    if (timer == RT_NULL)
    {
        LOG_E("stop timer is NULL");
        return;
    }

    struct n32_hw_lptimer *tim_device = rt_container_of(timer, struct n32_hw_lptimer, time_device);
    LPTIM_Module          *lptim      = tim_device->timer;

    if (tim_device == RT_NULL)
    {
        LOG_E("stop tim_device is NULL");
        return;
    }
    if (lptim == RT_NULL)
    {
        LOG_E("stop %s LPTIM is NULL", tim_device->name);
        return;
    }

    /* Disable timeout function and interrupt */
    LPTIM_TimeoutCmd(lptim, DISABLE);
    LPTIM_ConfigInt(lptim, LPTIM_COMP_MATCH_INT, DISABLE);

    /* Disable LPTIM peripheral */
    LPTIM_Cmd(lptim, DISABLE);

    LOG_D("stop %s success", tim_device->name);
}

static rt_uint32_t timer_get_freq(LPTIM_Module *lptim)
{
    /* Default configuration: LSI (32768 Hz) / DIV32 = 1024 Hz */
    (void)lptim;
    return 1024;
}

static rt_uint32_t timer_counter_get(rt_clock_timer_t *timer)
{
    struct n32_hw_lptimer *tim_device = rt_container_of(timer, struct n32_hw_lptimer, time_device);
    return LPTIM_GetCounterValue(tim_device->timer);
}

static rt_err_t timer_ctrl(rt_clock_timer_t *timer, rt_uint32_t cmd, void *arg)
{
    if (timer == RT_NULL)
    {
        LOG_E("ctrl timer is NULL");
        return -RT_EINVAL;
    }

    struct n32_hw_lptimer *tim_device = rt_container_of(timer, struct n32_hw_lptimer, time_device);
    LPTIM_Module          *lptim      = tim_device->timer;

    if (tim_device == RT_NULL)
    {
        LOG_E("ctrl tim_device is NULL");
        return -RT_EINVAL;
    }
    if (lptim == RT_NULL)
    {
        LOG_E("ctrl %s LPTIM is NULL", tim_device->name);
        return -RT_EINVAL;
    }

    rt_err_t result = RT_EOK;
    switch (cmd)
    {
    case DRV_HW_LPTIMER_CTRL_GET_TICK_MAX:
    {
        *(rt_uint32_t *)arg = LPTIM_REG_MAX_VALUE;
        break;
    }
    case DRV_HW_LPTIMER_CTRL_GET_FREQ:
    {
        *(rt_uint32_t *)arg = timer_get_freq(lptim);
        break;
    }
    case DRV_HW_LPTIMER_CTRL_START:
    {
        result = timer_start(timer, *(rt_uint32_t *)arg, CLOCK_TIMER_MODE_ONESHOT);
        break;
    }
    case DRV_HW_LPTIMER_CTRL_GET_COUNT:
    {
        *(rt_uint32_t *)arg = timer_counter_get(timer);
        break;
    }
    default:
    {
        result = -RT_ENOSYS;
    }
    break;
    }

    return result;
}

/* IRQ Handlers for each LPTIM instance */

#ifdef BSP_USING_LPTIM1
void LPTIM1_WKUP_IRQHandler(void)
{
    rt_interrupt_enter();
    if (LPTIM_IsActiveIntStatus(n32_hw_lptimer_obj[LPTIM1_INDEX].timer, LPTIM_COMP_MATCH_STATUS))
    {
        LPTIM_ClearIntFlag(n32_hw_lptimer_obj[LPTIM1_INDEX].timer, LPTIM_COMP_MATCH_FLAG);
        n32_lptim_clear_exti_flag(n32_hw_lptimer_obj[LPTIM1_INDEX].timer);
        rt_clock_timer_isr(&n32_hw_lptimer_obj[LPTIM1_INDEX].time_device);
    }
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_LPTIM2
void LPTIM2_WKUP_IRQHandler(void)
{
    rt_interrupt_enter();
    if (LPTIM_IsActiveIntStatus(n32_hw_lptimer_obj[LPTIM2_INDEX].timer, LPTIM_COMP_MATCH_STATUS))
    {
        LPTIM_ClearIntFlag(n32_hw_lptimer_obj[LPTIM2_INDEX].timer, LPTIM_COMP_MATCH_FLAG);
        n32_lptim_clear_exti_flag(n32_hw_lptimer_obj[LPTIM2_INDEX].timer);
        rt_clock_timer_isr(&n32_hw_lptimer_obj[LPTIM2_INDEX].time_device);
    }
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_LPTIM3
void LPTIM3_WKUP_IRQHandler(void)
{
    rt_interrupt_enter();
    if (LPTIM_IsActiveIntStatus(n32_hw_lptimer_obj[LPTIM3_INDEX].timer, LPTIM_COMP_MATCH_STATUS))
    {
        LPTIM_ClearIntFlag(n32_hw_lptimer_obj[LPTIM3_INDEX].timer, LPTIM_COMP_MATCH_FLAG);
        n32_lptim_clear_exti_flag(n32_hw_lptimer_obj[LPTIM3_INDEX].timer);
        rt_clock_timer_isr(&n32_hw_lptimer_obj[LPTIM3_INDEX].time_device);
    }
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_LPTIM4
void LPTIM4_WKUP_IRQHandler(void)
{
    rt_interrupt_enter();
    if (LPTIM_IsActiveIntStatus(n32_hw_lptimer_obj[LPTIM4_INDEX].timer, LPTIM_COMP_MATCH_STATUS))
    {
        LPTIM_ClearIntFlag(n32_hw_lptimer_obj[LPTIM4_INDEX].timer, LPTIM_COMP_MATCH_FLAG);
        n32_lptim_clear_exti_flag(n32_hw_lptimer_obj[LPTIM4_INDEX].timer);
        rt_clock_timer_isr(&n32_hw_lptimer_obj[LPTIM4_INDEX].time_device);
    }
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_LPTIM5
void LPTIM5_WKUP_IRQHandler(void)
{
    rt_interrupt_enter();
    if (LPTIM_IsActiveIntStatus(n32_hw_lptimer_obj[LPTIM5_INDEX].timer, LPTIM_COMP_MATCH_STATUS))
    {
        LPTIM_ClearIntFlag(n32_hw_lptimer_obj[LPTIM5_INDEX].timer, LPTIM_COMP_MATCH_FLAG);
        n32_lptim_clear_exti_flag(n32_hw_lptimer_obj[LPTIM5_INDEX].timer);
        rt_clock_timer_isr(&n32_hw_lptimer_obj[LPTIM5_INDEX].time_device);
    }
    rt_interrupt_leave();
}
#endif

static const struct rt_clock_timer_ops _ops = {
    .init      = timer_init,
    .start     = timer_start,
    .stop      = timer_stop,
    .count_get = timer_counter_get,
    .control   = timer_ctrl,
};

/**
 * Register all enabled LPTIM instances as rt_clock_timer devices.
 */
static int n32_hw_lptim_init(void)
{
    int i      = 0;
    int result = RT_EOK;

    for (i = 0; i < sizeof(n32_hw_lptimer_obj) / sizeof(n32_hw_lptimer_obj[0]); i++)
    {
        n32_hw_lptimer_obj[i].time_device.info = &_info;
        n32_hw_lptimer_obj[i].time_device.ops  = &_ops;
        if (rt_clock_timer_register(&n32_hw_lptimer_obj[i].time_device,
                                    n32_hw_lptimer_obj[i].name, &n32_hw_lptimer_obj[i].timer) == RT_EOK)
        {
            LOG_D("%s register success", n32_hw_lptimer_obj[i].name);
        }
        else
        {
            LOG_E("%s register failed", n32_hw_lptimer_obj[i].name);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(n32_hw_lptim_init);

#endif /* BSP_USING_LPTIM */
