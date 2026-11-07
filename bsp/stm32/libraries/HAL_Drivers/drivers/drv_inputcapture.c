/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-11-01     wdfk-prog         first version
 */
#include <board.h>
#include <rtdevice.h>
#include "drv_inputcapture.h"
#include "drv_config.h"

/**
 * @brief Convert a 1-based timer capture channel to the HAL TIM_CHANNEL_x value.
 * @param number Input capture channel number (1 through 4).
 * @note STM32F1 and STM32H7 HALs use a 4-unit channel encoding stride.
 */
#define STM32_CAPTURE_CHANNEL(number) (((number) - 1U) * 4U)

/**
 * @brief Check whether the RCC TIMPRE clock multiplier is currently selected.
 * @note STM32H7 exposes the TIMPRE bit in RCC->CFGR; STM32F1 has no TIMPRE.
 *       Other series may place TIMPRE in a different register and need a
 *       corresponding adapter here. Availability is detected by the CMSIS bit.
 */
#if defined(RCC_CFGR_TIMPRE)
#define STM32_INPUTCAPTURE_TIMPRE_ENABLED() ((RCC->CFGR & RCC_CFGR_TIMPRE) != 0U)
#else
#define STM32_INPUTCAPTURE_TIMPRE_ENABLED() (0U)
#endif /* defined(RCC_CFGR_TIMPRE) */

/**
 * @brief Check whether a specific TIM instance has a 32-bit counter.
 * @param instance STM32 TIM peripheral instance.
 * @note STM32H7 TIM2 has a 32-bit counter, while STM32F1 timer widths vary
 *       by device. Query the HAL/CMSIS instance capability when present;
 *       otherwise use the conservative 16-bit ARR configuration.
 */
#if defined(IS_TIM_32B_COUNTER_INSTANCE)
#define STM32_INPUTCAPTURE_TIM_HAS_32BIT_COUNTER(instance) (IS_TIM_32B_COUNTER_INSTANCE(instance))
#else
#define STM32_INPUTCAPTURE_TIM_HAS_32BIT_COUNTER(instance) (0U)
#endif /* defined(IS_TIM_32B_COUNTER_INSTANCE) */

/**
 * @brief Whether HAL exposes a both-edge input capture polarity constant.
 * @note This macro exists in STM32F1, STM32H7 and some other HAL series; it is
 *       not H7-specific. Its presence alone does not guarantee every TIM/channel
 *       can capture both edges. The board remains responsible for that choice.
 */
#if defined(TIM_INPUTCHANNELPOLARITY_BOTHEDGE)
#define STM32_INPUTCAPTURE_HAL_HAS_BOTHEDGE_POLARITY 1
/** @brief HAL polarity value used for hardware both-edge capture, if available. */
#define STM32_INPUTCAPTURE_HAL_BOTHEDGE_POLARITY TIM_INPUTCHANNELPOLARITY_BOTHEDGE
#else
#define STM32_INPUTCAPTURE_HAL_HAS_BOTHEDGE_POLARITY 0
#endif /* defined(TIM_INPUTCHANNELPOLARITY_BOTHEDGE) */

/** @brief Stable indices for selected physical timer instances. */
enum stm32_capture_index
{
#ifdef BSP_USING_INPUT_CAPTURE_TIM1
    STM32_CAPTURE_TIM1_INDEX,
#endif /* BSP_USING_INPUT_CAPTURE_TIM1 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM2
    STM32_CAPTURE_TIM2_INDEX,
#endif /* BSP_USING_INPUT_CAPTURE_TIM2 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM3
    STM32_CAPTURE_TIM3_INDEX,
#endif /* BSP_USING_INPUT_CAPTURE_TIM3 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM4
    STM32_CAPTURE_TIM4_INDEX,
#endif /* BSP_USING_INPUT_CAPTURE_TIM4 */
    STM32_CAPTURE_DEVICE_COUNT
};

/** @brief Board-selected physical timer capture configuration table. */
static const struct stm32_inputcapture_config stm32_capture_configs[] = {
#ifdef BSP_USING_INPUT_CAPTURE_TIM1
    INPUTCAPTURE_TIM1_CONFIG,
#endif /* BSP_USING_INPUT_CAPTURE_TIM1 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM2
    INPUTCAPTURE_TIM2_CONFIG,
#endif /* BSP_USING_INPUT_CAPTURE_TIM2 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM3
    INPUTCAPTURE_TIM3_CONFIG,
#endif /* BSP_USING_INPUT_CAPTURE_TIM3 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM4
    INPUTCAPTURE_TIM4_CONFIG,
#endif /* BSP_USING_INPUT_CAPTURE_TIM4 */
};

/** @brief Runtime state owned by one RT-Thread physical Capture device. */
struct stm32_capture_device
{
    struct rt_inputcapture_device parent;           /**< RT-Thread Input Capture object. */
    const struct stm32_inputcapture_config *config; /**< Immutable timer configuration. */
    TIM_HandleTypeDef timer;                        /**< HAL timer handle owned by this driver. */
    rt_uint32_t pulsewidth_us;                      /**< Last completed edge interval, in us. */
    rt_uint32_t counter_hz;                         /**< Timer counter frequency, in Hz. */
    rt_uint32_t previous_count;                     /**< Last captured CCR value. */
    rt_bool_t first_edge;                           /**< Ignore the first partial interval. */
    rt_bool_t next_edge_rising;                     /**< Edge direction tracked for each sample. */
    volatile rt_bool_t active;                      /**< Capture channel is running. */
};

/** @brief One Capture device state per enabled timer instance. */
static struct stm32_capture_device stm32_capture_devices[STM32_CAPTURE_DEVICE_COUNT];

/**
 * @brief Obtain the effective timer input clock, including APB prescaling.
 * @param instance Physical TIM instance.
 * @return Timer clock frequency in Hz.
 */
static rt_uint32_t stm32_inputcapture_timer_clock(TIM_TypeDef *instance)
{
    rt_uint32_t hclk = HAL_RCC_GetHCLKFreq(); /* Timer APB parent clock, in Hz. */
    rt_uint32_t pclk;                         /* Selected APB peripheral clock, in Hz. */
    rt_uint32_t divider;                      /* APB prescaler relative to HCLK. */

    pclk = ((rt_ubase_t)instance >= (rt_ubase_t)APB2PERIPH_BASE) ? HAL_RCC_GetPCLK2Freq() : HAL_RCC_GetPCLK1Freq();
    if (pclk == 0U)
    {
        return 0U;
    }
    divider = hclk / pclk;
    if (divider <= 1U)
    {
        return pclk;
    }
    /* TIMPRE is an optional RCC feature; the common HAL adapter handles its absence. */
    if (STM32_INPUTCAPTURE_TIMPRE_ENABLED() && divider >= 4U)
    {
        return pclk * 4U;
    }
    return pclk * 2U;
}

/**
 * @brief Initialize one timer for hardware input capture with a 1-channel configuration.
 * @param inputcapture Device whose hardware timer is initialized.
 * @return RT_EOK, or a negative HAL/clock error code.
 */
static rt_err_t stm32_capture_init(struct rt_inputcapture_device *inputcapture)
{
    struct stm32_capture_device *device =
        rt_container_of(inputcapture, struct stm32_capture_device, parent); /* Capture state. */
    const struct stm32_inputcapture_config *config = device->config;        /* Board mapping. */
    TIM_HandleTypeDef *timer = &device->timer;                              /* Private HAL TIM handle. */
    TIM_IC_InitTypeDef ic = { 0 };                                          /* Single direct-TI input channel setup. */
    rt_uint32_t clock = stm32_inputcapture_timer_clock(config->instance);   /* Effective TIM clock. */

    if (clock < BSP_INPUT_CAPTURE_COUNTER_HZ || clock % BSP_INPUT_CAPTURE_COUNTER_HZ != 0U)
    {
        return -RT_EINVAL;
    }
    timer->Instance = config->instance;
    timer->Init.Prescaler = clock / BSP_INPUT_CAPTURE_COUNTER_HZ - 1U;
    timer->Init.CounterMode = TIM_COUNTERMODE_UP;
    timer->Init.Period = config->counter_period;
    /* Use the full hardware range only when this specific TIM has a 32-bit counter. */
    if (STM32_INPUTCAPTURE_TIM_HAS_32BIT_COUNTER(config->instance))
    {
        timer->Init.Period = 0xFFFFFFFFU;
    }
    timer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    timer->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    device->counter_hz = BSP_INPUT_CAPTURE_COUNTER_HZ;

    /* HAL_TIM_IC_Init invokes the HAL_TIM_IC_MspInit provided by CubeMX. */
    if (HAL_TIM_IC_Init(timer) != HAL_OK)
    {
        return -RT_ERROR;
    }

    ic.ICPolarity = config->initial_edge_rising ? TIM_INPUTCHANNELPOLARITY_RISING : TIM_INPUTCHANNELPOLARITY_FALLING;
    if (config->hardware_both_edges)
    {
#if STM32_INPUTCAPTURE_HAL_HAS_BOTHEDGE_POLARITY
        ic.ICPolarity = STM32_INPUTCAPTURE_HAL_BOTHEDGE_POLARITY;
#else
        HAL_TIM_IC_DeInit(timer);
        return -RT_ENOSYS;
#endif /* STM32_INPUTCAPTURE_HAL_HAS_BOTHEDGE_POLARITY */
    }
    ic.ICSelection = TIM_ICSELECTION_DIRECTTI;
    ic.ICPrescaler = TIM_ICPSC_DIV1;
    ic.ICFilter = config->input_filter;
    if (HAL_TIM_IC_ConfigChannel(timer, &ic, config->channel) != HAL_OK)
    {
        HAL_TIM_IC_DeInit(timer);
        return -RT_ERROR;
    }
    return RT_EOK;
}

/**
 * @brief Start the selected Capture channel after RT-Thread creates its FIFO.
 * @param inputcapture RT-Thread Input Capture device to open.
 * @return RT_EOK or a negative FIFO/HAL error code.
 */
static rt_err_t stm32_capture_open(struct rt_inputcapture_device *inputcapture)
{
    struct stm32_capture_device *device =
        rt_container_of(inputcapture, struct stm32_capture_device, parent); /* Capture state. */
    const struct stm32_inputcapture_config *config = device->config;        /* Board mapping. */
    TIM_HandleTypeDef *timer = &device->timer;                              /* Configured timer. */

    if (!inputcapture->ringbuff)
    {
        return -RT_ENOMEM;
    }
    device->first_edge = RT_TRUE;
    device->previous_count = 0U;
    device->pulsewidth_us = 0U;
    device->next_edge_rising = config->initial_edge_rising;
    __HAL_TIM_SET_COUNTER(timer, 0U);
    if (!config->hardware_both_edges)
    {
        __HAL_TIM_SET_CAPTUREPOLARITY(timer, config->channel,
                                      device->next_edge_rising ? TIM_INPUTCHANNELPOLARITY_RISING : TIM_INPUTCHANNELPOLARITY_FALLING);
    }
    /* Clear stale capture and overcapture flags before enabling this channel's interrupt. */
    switch (config->channel)
    {
    case TIM_CHANNEL_1:
        __HAL_TIM_CLEAR_FLAG(timer, TIM_FLAG_CC1 | TIM_FLAG_CC1OF);
        break;
    case TIM_CHANNEL_2:
        __HAL_TIM_CLEAR_FLAG(timer, TIM_FLAG_CC2 | TIM_FLAG_CC2OF);
        break;
    case TIM_CHANNEL_3:
        __HAL_TIM_CLEAR_FLAG(timer, TIM_FLAG_CC3 | TIM_FLAG_CC3OF);
        break;
    case TIM_CHANNEL_4:
        __HAL_TIM_CLEAR_FLAG(timer, TIM_FLAG_CC4 | TIM_FLAG_CC4OF);
        break;
    }
    device->active = RT_TRUE;
    if (HAL_TIM_IC_Start_IT(timer, config->channel) != HAL_OK)
    {
        device->active = RT_FALSE;
        return -RT_ERROR;
    }
    return RT_EOK;
}

/**
 * @brief Stop the Capture channel without modifying CubeMX-owned NVIC state.
 * @param inputcapture RT-Thread device to stop.
 * @return RT_EOK or a negative HAL stop error.
 */
static rt_err_t stm32_capture_close(struct rt_inputcapture_device *inputcapture)
{
    struct stm32_capture_device *device =
        rt_container_of(inputcapture, struct stm32_capture_device, parent); /* Capture state. */
    if (!device->active)
    {
        return RT_EOK;
    }
    if (HAL_TIM_IC_Stop_IT(&device->timer, device->config->channel) != HAL_OK)
    {
        return -RT_ERROR;
    }
    /* Only clear the ISR gate after HAL confirms the capture channel has stopped. */
    device->active = RT_FALSE;
    return RT_EOK;
}

/**
 * @brief Return the most recently recorded pulse duration to RT-Thread's FIFO.
 * @param inputcapture Source Capture device.
 * @param pulsewidth_us Output pulse duration in microseconds.
 * @return RT_EOK.
 */
static rt_err_t stm32_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture,
                                             rt_uint32_t *pulsewidth_us)
{
    struct stm32_capture_device *device =
        rt_container_of(inputcapture, struct stm32_capture_device, parent); /* Capture state. */
    *pulsewidth_us = device->pulsewidth_us;
    return RT_EOK;
}

/** @brief RT-Thread Input Capture HAL backend operations. */
static const struct rt_inputcapture_ops stm32_capture_ops = {
    .init = stm32_capture_init,
    .open = stm32_capture_open,
    .close = stm32_capture_close,
    .get_pulsewidth = stm32_capture_get_pulsewidth,
};

/**
 * @brief Push a complete interval from the only configured capture channel.
 * @param timer HAL timer for which Input Capture completed.
 * @note The IRQ caller must pass a driver-owned timer handle and the selected
 *       capture channel. Handle/channel validation is intentionally omitted
 *       from this hot path; a foreign callback can cause invalid memory access.
 * @note Software polarity switching can miss short edges; hardware both-edge
 *       sampling assumes every transition is observed in order. Intervals
 *       longer than one counter period cannot be reconstructed without overflow tracking.
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *timer)
{
    struct stm32_capture_device *device =
        rt_container_of(timer, struct stm32_capture_device, timer);  /* Owner of the HAL TIM handle. */
    const struct stm32_inputcapture_config *config = device->config; /* Selected channel mapping. */
    rt_uint32_t captured;                                            /* Hardware CCR value at the selected edge. */
    rt_uint32_t delta;                                               /* Timer ticks elapsed, permitting one wrap. */
    rt_bool_t was_high;                                              /* Logic level of the interval just ended. */

    if (!device->active)
    {
        return;
    }
    captured = HAL_TIM_ReadCapturedValue(timer, config->channel);
    was_high = device->next_edge_rising ? RT_FALSE : RT_TRUE;
    device->next_edge_rising = !device->next_edge_rising;
    if (!config->hardware_both_edges)
    {
        __HAL_TIM_SET_CAPTUREPOLARITY(timer, config->channel,
                                      device->next_edge_rising ? TIM_INPUTCHANNELPOLARITY_RISING : TIM_INPUTCHANNELPOLARITY_FALLING);
    }
    if (!device->first_edge)
    {
        if (captured >= device->previous_count)
        {
            delta = captured - device->previous_count;
        }
        else
        {
            delta = (timer->Init.Period - device->previous_count + 1U) + captured;
        }
        device->pulsewidth_us =
            (rt_uint32_t)(((rt_uint64_t)delta * 1000000ULL + device->counter_hz / 2U) / device->counter_hz);
        rt_hw_inputcapture_isr(&device->parent, was_high);
    }
    device->previous_count = captured;
    device->first_edge = RT_FALSE;
}

/**
 * @brief Register every timer selected in the board's Input Capture configuration.
 * @return RT_EOK or the first registration failure.
 */
int rt_hw_inputcapture_init(void)
{
    rt_size_t i;     /* Current physical timer. */
    rt_err_t status; /* Device registration status. */

    for (i = 0; i < STM32_CAPTURE_DEVICE_COUNT; ++i)
    {
        stm32_capture_devices[i].config = &stm32_capture_configs[i];
        stm32_capture_devices[i].parent.ops = &stm32_capture_ops;
        status = rt_device_inputcapture_register(&stm32_capture_devices[i].parent,
                                                 stm32_capture_configs[i].name,
                                                 &stm32_capture_devices[i]);
        if (status != RT_EOK)
        {
            return status;
        }
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_inputcapture_init);

#ifdef BSP_USING_INPUT_CAPTURE_TIM1
/** @brief Dispatch TIM1 Capture IRQ within one RT-Thread interrupt boundary. */
void TIM1_CC_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_capture_devices[STM32_CAPTURE_TIM1_INDEX].timer);
    rt_interrupt_leave();
}
#endif /* BSP_USING_INPUT_CAPTURE_TIM1 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM2
/** @brief Dispatch TIM2 Capture IRQ within one RT-Thread interrupt boundary. */
void TIM2_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_capture_devices[STM32_CAPTURE_TIM2_INDEX].timer);
    rt_interrupt_leave();
}
#endif /* BSP_USING_INPUT_CAPTURE_TIM2 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM3
/** @brief Dispatch TIM3 Capture IRQ within one RT-Thread interrupt boundary. */
void TIM3_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_capture_devices[STM32_CAPTURE_TIM3_INDEX].timer);
    rt_interrupt_leave();
}
#endif /* BSP_USING_INPUT_CAPTURE_TIM3 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM4
/** @brief Dispatch TIM4 Capture IRQ within one RT-Thread interrupt boundary. */
void TIM4_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_TIM_IRQHandler(&stm32_capture_devices[STM32_CAPTURE_TIM4_INDEX].timer);
    rt_interrupt_leave();
}
#endif /* BSP_USING_INPUT_CAPTURE_TIM4 */
