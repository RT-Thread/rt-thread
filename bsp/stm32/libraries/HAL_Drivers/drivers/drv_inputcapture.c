/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-11-01     wdfk-prog         first version
 * 2026-11-10     wdfk-prog         support independent capture channels and exclusive PWM Input
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

#define LOG_TAG "drv.inputcapture"
#include <drv_log.h>

/** @brief Stable indices of enabled physical timer instances. */
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
    STM32_CAPTURE_TIMER_COUNT /**< Number of enabled physical timers. */
};

/** @brief Timer-handle storage shared by all capture channels of one physical TIM. */
static TIM_HandleTypeDef stm32_capture_timers[STM32_CAPTURE_TIMER_COUNT];

/** @brief Fixed configurations of independent EDGE, PWM Input and dual-edge devices. */
static const struct stm32_inputcapture_config stm32_capture_configs[] = {
#ifdef BSP_USING_INPUT_CAPTURE_TIM1
#if BSP_INPUT_CAPTURE_TIM1_PWM_INPUT == 1
    INPUTCAPTURE_TIM1_PWM_CONFIG,
#elif defined(BSP_INPUT_CAPTURE_TIM1_DUAL_EDGE)
    INPUTCAPTURE_TIM1_DUAL_CONFIG,
#else
#ifdef BSP_INPUT_CAPTURE_TIM1_CH1
    INPUTCAPTURE_TIM1_CH1_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM1_CH1 */
#ifdef BSP_INPUT_CAPTURE_TIM1_CH2
    INPUTCAPTURE_TIM1_CH2_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM1_CH2 */
#ifdef BSP_INPUT_CAPTURE_TIM1_CH3
    INPUTCAPTURE_TIM1_CH3_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM1_CH3 */
#ifdef BSP_INPUT_CAPTURE_TIM1_CH4
    INPUTCAPTURE_TIM1_CH4_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM1_CH4 */
#endif /* BSP_INPUT_CAPTURE_TIM1_PWM_INPUT */
#endif /* BSP_USING_INPUT_CAPTURE_TIM1 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM2
#if BSP_INPUT_CAPTURE_TIM2_PWM_INPUT == 1
    INPUTCAPTURE_TIM2_PWM_CONFIG,
#elif defined(BSP_INPUT_CAPTURE_TIM2_DUAL_EDGE)
    INPUTCAPTURE_TIM2_DUAL_CONFIG,
#else
#ifdef BSP_INPUT_CAPTURE_TIM2_CH1
    INPUTCAPTURE_TIM2_CH1_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM2_CH1 */
#ifdef BSP_INPUT_CAPTURE_TIM2_CH2
    INPUTCAPTURE_TIM2_CH2_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM2_CH2 */
#ifdef BSP_INPUT_CAPTURE_TIM2_CH3
    INPUTCAPTURE_TIM2_CH3_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM2_CH3 */
#ifdef BSP_INPUT_CAPTURE_TIM2_CH4
    INPUTCAPTURE_TIM2_CH4_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM2_CH4 */
#endif /* BSP_INPUT_CAPTURE_TIM2_PWM_INPUT */
#endif /* BSP_USING_INPUT_CAPTURE_TIM2 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM3
#if BSP_INPUT_CAPTURE_TIM3_PWM_INPUT == 1
    INPUTCAPTURE_TIM3_PWM_CONFIG,
#elif defined(BSP_INPUT_CAPTURE_TIM3_DUAL_EDGE)
    INPUTCAPTURE_TIM3_DUAL_CONFIG,
#else
#ifdef BSP_INPUT_CAPTURE_TIM3_CH1
    INPUTCAPTURE_TIM3_CH1_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM3_CH1 */
#ifdef BSP_INPUT_CAPTURE_TIM3_CH2
    INPUTCAPTURE_TIM3_CH2_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM3_CH2 */
#ifdef BSP_INPUT_CAPTURE_TIM3_CH3
    INPUTCAPTURE_TIM3_CH3_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM3_CH3 */
#ifdef BSP_INPUT_CAPTURE_TIM3_CH4
    INPUTCAPTURE_TIM3_CH4_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM3_CH4 */
#endif /* BSP_INPUT_CAPTURE_TIM3_PWM_INPUT */
#endif /* BSP_USING_INPUT_CAPTURE_TIM3 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM4
#if BSP_INPUT_CAPTURE_TIM4_PWM_INPUT == 1
    INPUTCAPTURE_TIM4_PWM_CONFIG,
#elif defined(BSP_INPUT_CAPTURE_TIM4_DUAL_EDGE)
    INPUTCAPTURE_TIM4_DUAL_CONFIG,
#else
#ifdef BSP_INPUT_CAPTURE_TIM4_CH1
    INPUTCAPTURE_TIM4_CH1_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM4_CH1 */
#ifdef BSP_INPUT_CAPTURE_TIM4_CH2
    INPUTCAPTURE_TIM4_CH2_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM4_CH2 */
#ifdef BSP_INPUT_CAPTURE_TIM4_CH3
    INPUTCAPTURE_TIM4_CH3_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM4_CH3 */
#ifdef BSP_INPUT_CAPTURE_TIM4_CH4
    INPUTCAPTURE_TIM4_CH4_CONFIG,
#endif /* BSP_INPUT_CAPTURE_TIM4_CH4 */
#endif /* BSP_INPUT_CAPTURE_TIM4_PWM_INPUT */
#endif /* BSP_USING_INPUT_CAPTURE_TIM4 */
};

/** @brief Runtime state of one independent EDGE, PWM Input or dual-edge device. */
struct stm32_capture_device
{
    struct rt_inputcapture_device parent;           /**< RT-Thread Input Capture device and FIFO. */
    const struct stm32_inputcapture_config *config; /**< Immutable physical-channel configuration. */
    TIM_HandleTypeDef *timer;                       /**< Shared HAL handle of the owning physical TIM. */
    rt_uint32_t pulsewidth_us;                      /**< Last completed pulse interval, microseconds. */
    rt_uint32_t counter_hz;                         /**< Timer counter frequency, hertz. */
    rt_uint32_t previous_count;                     /**< Previous EDGE or dual-edge capture CCR value. */
    rt_bool_t first_edge;                           /**< Ignore the first incomplete interval after opening. */
    rt_bool_t next_edge_rising;                     /**< Next expected EDGE or DUAL_EDGE polarity. */
    volatile rt_bool_t active;                      /**< Capture device has started. */
};

/** @brief Logical capture-device states in the same order as the configuration table. */
static struct stm32_capture_device
    stm32_capture_devices[sizeof(stm32_capture_configs) / sizeof(stm32_capture_configs[0])];

/**
 * @brief Resolve the shared HAL handle of one physical TIM.
 * @param instance Physical TIM instance.
 * @return HAL handle or RT_NULL for an unsupported instance.
 */
static TIM_HandleTypeDef *stm32_capture_get_timer(TIM_TypeDef *instance)
{
#ifdef BSP_USING_INPUT_CAPTURE_TIM1
    if (instance == TIM1)
    {
        return &stm32_capture_timers[STM32_CAPTURE_TIM1_INDEX];
    }
#endif /* BSP_USING_INPUT_CAPTURE_TIM1 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM2
    if (instance == TIM2)
    {
        return &stm32_capture_timers[STM32_CAPTURE_TIM2_INDEX];
    }
#endif /* BSP_USING_INPUT_CAPTURE_TIM2 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM3
    if (instance == TIM3)
    {
        return &stm32_capture_timers[STM32_CAPTURE_TIM3_INDEX];
    }
#endif /* BSP_USING_INPUT_CAPTURE_TIM3 */
#ifdef BSP_USING_INPUT_CAPTURE_TIM4
    if (instance == TIM4)
    {
        return &stm32_capture_timers[STM32_CAPTURE_TIM4_INDEX];
    }
#endif /* BSP_USING_INPUT_CAPTURE_TIM4 */
    return RT_NULL;
}

/**
 * @brief Find the logical capture device assigned to a HAL channel interrupt.
 * @param timer Shared HAL handle containing the physical TIM instance.
 * @param channel HAL TIM_CHANNEL_x selector.
 * @return Matching logical device or RT_NULL.
 */
static struct stm32_capture_device *stm32_capture_find_device(TIM_HandleTypeDef *timer, rt_uint32_t channel)
{
    rt_size_t i; /* Logical device index. */

    for (i = 0; i < sizeof(stm32_capture_devices) / sizeof(stm32_capture_devices[0]); i++)
    {
        if (stm32_capture_devices[i].timer == timer &&
            (stm32_capture_devices[i].config->channel == channel
#ifdef BSP_USING_INPUT_CAPTURE_DUAL_EDGE
             || (stm32_capture_devices[i].config->dual_edge &&
                 (stm32_capture_devices[i].config->channel == TIM_CHANNEL_1 ? TIM_CHANNEL_2 : TIM_CHANNEL_1) == channel)
#endif /* BSP_USING_INPUT_CAPTURE_DUAL_EDGE */
                 ))
        {
            return &stm32_capture_devices[i];
        }
    }
    return RT_NULL;
}

/**
 * @brief Convert HAL's active capture channel into the corresponding CCR selector.
 * @param channel HAL active input-capture channel.
 * @return TIM_CHANNEL_x selector, or an invalid selector if no channel is active.
 */
static rt_uint32_t stm32_capture_channel(HAL_TIM_ActiveChannel channel)
{
    switch (channel)
    {
    case HAL_TIM_ACTIVE_CHANNEL_1:
        return TIM_CHANNEL_1;
    case HAL_TIM_ACTIVE_CHANNEL_2:
        return TIM_CHANNEL_2;
    case HAL_TIM_ACTIVE_CHANNEL_3:
        return TIM_CHANNEL_3;
    case HAL_TIM_ACTIVE_CHANNEL_4:
        return TIM_CHANNEL_4;
    default:
        return (rt_uint32_t)-1;
    }
}

/**
 * @brief Check whether another logical device has started on this physical timer.
 * @param timer Shared physical TIM handle.
 * @return RT_TRUE if any logical capture device is running.
 * @note Callers serialize first open/close operations on the same TIM.
 */
static rt_bool_t stm32_capture_timer_active(TIM_HandleTypeDef *timer)
{
    rt_size_t i; /* Logical device index. */

    for (i = 0; i < sizeof(stm32_capture_devices) / sizeof(stm32_capture_devices[0]); i++)
    {
        if (stm32_capture_devices[i].timer == timer && stm32_capture_devices[i].active)
        {
            return RT_TRUE;
        }
    }
    return RT_FALSE;
}

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

#if defined(BSP_USING_INPUT_CAPTURE_PWM_INPUT) || defined(BSP_USING_INPUT_CAPTURE_DUAL_EDGE)
/**
 * @brief Find the indirect channel paired with a direct capture channel.
 * @param channel Direct TI input channel (CH1 or CH2).
 * @return Partner channel (CH2 or CH1).
 */
static rt_uint32_t stm32_capture_paired_partner(rt_uint32_t channel)
{
    return channel == TIM_CHANNEL_1 ? TIM_CHANNEL_2 : TIM_CHANNEL_1;
}
#endif /* BSP_USING_INPUT_CAPTURE_PWM_INPUT || BSP_USING_INPUT_CAPTURE_DUAL_EDGE */

#ifdef BSP_USING_INPUT_CAPTURE_PWM_INPUT
/**
 * @brief Configure PWM Input's direct/indirect channels and slave-reset mode.
 * @param device PWM Input logical device.
 * @return RT_EOK on success, a negative RT-Thread error otherwise.
 */
static rt_err_t stm32_capture_pwm_input_init(struct stm32_capture_device *device)
{
    const struct stm32_inputcapture_config *config = device->config; /* Physical TI configuration. */
    TIM_HandleTypeDef *timer = device->timer;                        /* Physical TIM handle. */
    TIM_IC_InitTypeDef ic = {0};                                     /* Both capture channels. */
    TIM_SlaveConfigTypeDef slave = {0};                              /* Reset trigger configuration. */

    ic.ICPolarity = config->initial_edge_rising ? TIM_INPUTCHANNELPOLARITY_RISING : TIM_INPUTCHANNELPOLARITY_FALLING;
    ic.ICSelection = TIM_ICSELECTION_DIRECTTI;
    ic.ICPrescaler = TIM_ICPSC_DIV1;
    ic.ICFilter = config->input_filter;
    if (HAL_TIM_IC_ConfigChannel(timer, &ic, config->channel) != HAL_OK)
    {
        LOG_E("%s PWM direct channel configuration failed", config->name);
        return -RT_ERROR;
    }
    ic.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    ic.ICPolarity = config->initial_edge_rising ? TIM_INPUTCHANNELPOLARITY_FALLING : TIM_INPUTCHANNELPOLARITY_RISING;
    if (HAL_TIM_IC_ConfigChannel(timer, &ic, stm32_capture_paired_partner(config->channel)) != HAL_OK)
    {
        LOG_E("%s PWM indirect channel configuration failed", config->name);
        return -RT_ERROR;
    }
    slave.SlaveMode = TIM_SLAVEMODE_RESET;
    slave.InputTrigger = config->channel == TIM_CHANNEL_1 ? TIM_TS_TI1FP1 : TIM_TS_TI2FP2;
    slave.TriggerPolarity = config->initial_edge_rising ? TIM_TRIGGERPOLARITY_RISING : TIM_TRIGGERPOLARITY_FALLING;
    slave.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;
    slave.TriggerFilter = config->input_filter;
    if (HAL_TIM_SlaveConfigSynchro(timer, &slave) != HAL_OK)
    {
        LOG_E("%s PWM reset trigger configuration failed", config->name);
        return -RT_ERROR;
    }
    /* With URS=1, only CNT overflow sets UIF; the normal slave reset does not. */
    __HAL_TIM_URS_ENABLE(timer);
    return RT_EOK;
}

/**
 * @brief Start PWM Input's indirect latch and direct-channel capture interrupt.
 * @param device PWM Input logical device.
 * @return HAL_OK on success, HAL error code otherwise.
 */
static HAL_StatusTypeDef stm32_capture_pwm_input_open(struct stm32_capture_device *device)
{
    TIM_HandleTypeDef *timer = device->timer;                                    /* Physical TIM handle. */
    rt_uint32_t partner = stm32_capture_paired_partner(device->config->channel); /* Indirect channel. */
    HAL_StatusTypeDef status;                                                    /* Channel start result. */

    status = HAL_TIM_IC_Start(timer, partner);
    if (status != HAL_OK)
    {
        return status;
    }
    /* Let the indirect channel latch without IRQ; only the reset edge interrupts. */
    __HAL_TIM_CLEAR_FLAG(timer, TIM_FLAG_CC1 | TIM_FLAG_CC2 | TIM_FLAG_CC1OF | TIM_FLAG_CC2OF |
                                    TIM_FLAG_UPDATE);
    status = HAL_TIM_IC_Start_IT(timer, device->config->channel);
    if (status != HAL_OK)
    {
        HAL_TIM_IC_Stop(timer, partner);
    }
    return status;
}

/**
 * @brief Stop both PWM Input channels while keeping a failed close retryable.
 * @param device PWM Input logical device.
 * @return HAL_OK on success, HAL error code otherwise.
 */
static HAL_StatusTypeDef stm32_capture_pwm_input_close(struct stm32_capture_device *device)
{
    TIM_HandleTypeDef *timer = device->timer; /* Physical TIM handle. */
    HAL_StatusTypeDef status;                 /* Channel stop result. */

    status = HAL_TIM_IC_Stop_IT(timer, device->config->channel);
    if (status != HAL_OK)
    {
        return status;
    }
    status = HAL_TIM_IC_Stop(timer, stm32_capture_paired_partner(device->config->channel));
    if (status != HAL_OK)
    {
        HAL_TIM_IC_Start_IT(timer, device->config->channel);
    }
    return status;
}

/**
 * @brief Convert one complete PWM Input period into high/low pulse records.
 * @param device PWM Input logical device whose reset-edge capture completed.
 * @note Indirect captures have no IRQ, avoiding cross-channel callback ordering.
 */
static void stm32_capture_pwm_input_sample(struct stm32_capture_device *device)
{
    const struct stm32_inputcapture_config *config = device->config;                                  /* Direct TI and reset edge. */
    TIM_HandleTypeDef *timer = device->timer;                                                         /* Physical timer. */
    rt_uint32_t partner = stm32_capture_paired_partner(config->channel);                              /* Indirect CCR. */
    rt_uint32_t partner_flag = partner == TIM_CHANNEL_1 ? TIM_FLAG_CC1 : TIM_FLAG_CC2;                /* Pending capture. */
    rt_uint32_t partner_overflow = partner == TIM_CHANNEL_1 ? TIM_FLAG_CC1OF : TIM_FLAG_CC2OF;        /* Indirect overrun. */
    rt_uint32_t direct_overflow = config->channel == TIM_CHANNEL_1 ? TIM_FLAG_CC1OF : TIM_FLAG_CC2OF; /* Reset overrun. */
    rt_uint32_t flags = timer->Instance->SR;                                                          /* Pending capture, overrun and update flags. */
    rt_uint32_t period = HAL_TIM_ReadCapturedValue(timer, config->channel);                           /* Reset-to-reset interval. */
    rt_uint32_t segment = HAL_TIM_ReadCapturedValue(timer, partner);                                  /* First part of the period. */
    /* With URS set, a latched UIF means this period crossed ARR and the CCR values are truncated. */
    rt_bool_t valid = !device->first_edge &&
                      (flags & TIM_FLAG_UPDATE) == 0U &&
                      (flags & partner_flag) != 0U &&
                      (flags & partner_overflow) == 0U &&
                      (flags & direct_overflow) == 0U &&
                      period != 0U && segment < period; /* Reject initial/overcaptured or incomplete periods. */

    device->first_edge = RT_FALSE;
    /* Snapshot SR before CCR reads; do not clear CCxIF again or lose a newer capture. */
    __HAL_TIM_CLEAR_FLAG(timer, TIM_FLAG_UPDATE | partner_overflow | direct_overflow);
    if (!valid)
    {
        return;
    }
    /* A rising reset edge yields high then low; falling yields low then high. */
    device->pulsewidth_us =
        (rt_uint32_t)(((rt_uint64_t)segment * 1000000ULL + device->counter_hz / 2U) / device->counter_hz);
    rt_hw_inputcapture_isr(&device->parent, config->initial_edge_rising);
    device->pulsewidth_us =
        (rt_uint32_t)(((rt_uint64_t)(period - segment) * 1000000ULL + device->counter_hz / 2U) /
                      device->counter_hz);
    rt_hw_inputcapture_isr(&device->parent, !config->initial_edge_rising);
}
#endif /* BSP_USING_INPUT_CAPTURE_PWM_INPUT */

#ifdef BSP_USING_INPUT_CAPTURE_DUAL_EDGE
/**
 * @brief Configure two capture channels on one TI input without slave reset.
 * @param device Exclusive dual-edge capture device.
 * @return RT_EOK or an RT-Thread hardware configuration error.
 */
static rt_err_t stm32_capture_dual_edge_init(struct stm32_capture_device *device)
{
    const struct stm32_inputcapture_config *config = device->config; /* Direct channel and polarity. */
    TIM_HandleTypeDef *timer = device->timer;                        /* Shared physical TIM. */
    TIM_IC_InitTypeDef ic = {0};                                     /* Direct/indirect capture setup. */

    ic.ICPolarity = config->initial_edge_rising ? TIM_INPUTCHANNELPOLARITY_RISING : TIM_INPUTCHANNELPOLARITY_FALLING;
    ic.ICSelection = TIM_ICSELECTION_DIRECTTI;
    ic.ICPrescaler = TIM_ICPSC_DIV1;
    ic.ICFilter = config->input_filter;
    if (HAL_TIM_IC_ConfigChannel(timer, &ic, config->channel) != HAL_OK)
    {
        LOG_E("%s dual-edge direct channel configuration failed", config->name);
        return -RT_ERROR;
    }
    /* The paired channel timestamps the opposite edge of this same physical TI pin. */
    ic.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    ic.ICPolarity = config->initial_edge_rising ? TIM_INPUTCHANNELPOLARITY_FALLING : TIM_INPUTCHANNELPOLARITY_RISING;
    ic.ICFilter = config->dual_partner_filter;
    if (HAL_TIM_IC_ConfigChannel(timer, &ic, stm32_capture_paired_partner(config->channel)) != HAL_OK)
    {
        LOG_E("%s dual-edge indirect channel configuration failed", config->name);
        return -RT_ERROR;
    }
    return RT_EOK;
}

/**
 * @brief Start both dual-edge capture interrupts and undo the first on failure.
 * @param device Exclusive dual-edge capture device.
 * @return HAL_OK or a HAL channel-start failure.
 */
static HAL_StatusTypeDef stm32_capture_dual_edge_open(struct stm32_capture_device *device)
{
    TIM_HandleTypeDef *timer = device->timer;                                    /* Shared physical TIM. */
    rt_uint32_t partner = stm32_capture_paired_partner(device->config->channel); /* Indirect channel. */
    HAL_StatusTypeDef status;                                                    /* Channel start/stop result. */

    __HAL_TIM_CLEAR_FLAG(timer, TIM_FLAG_CC1 | TIM_FLAG_CC2 | TIM_FLAG_CC1OF | TIM_FLAG_CC2OF);
    status = HAL_TIM_IC_Start_IT(timer, partner);
    if (status != HAL_OK)
    {
        return status;
    }
    status = HAL_TIM_IC_Start_IT(timer, device->config->channel);
    if (status != HAL_OK)
    {
        if (HAL_TIM_IC_Stop_IT(timer, partner) != HAL_OK)
        {
            LOG_E("%s dual-edge start rollback failed", device->config->name);
        }
    }
    return status;
}

/**
 * @brief Stop both dual-edge channels; restore the first if the second fails.
 * @param device Exclusive dual-edge capture device.
 * @return HAL_OK on success, HAL error code otherwise.
 */
static HAL_StatusTypeDef stm32_capture_dual_edge_close(struct stm32_capture_device *device)
{
    TIM_HandleTypeDef *timer = device->timer; /* Shared physical TIM. */
    HAL_StatusTypeDef status;                 /* Channel stop result. */

    status = HAL_TIM_IC_Stop_IT(timer, device->config->channel);
    if (status != HAL_OK)
    {
        return status;
    }
    status = HAL_TIM_IC_Stop_IT(timer, stm32_capture_paired_partner(device->config->channel));
    if (status != HAL_OK)
    {
        if (HAL_TIM_IC_Start_IT(timer, device->config->channel) != HAL_OK)
        {
            LOG_E("%s dual-edge close rollback failed", device->config->name);
        }
    }
    return status;
}

/**
 * @brief Report one already-latched dual-edge timestamp in chronological order.
 * @param device Exclusive paired-channel Input Capture device.
 * @param channel Physical channel that latched the edge.
 * @param captured CCR timestamp read by the IRQ dispatcher.
 * @note CCR differences are modulo ARR+1: intervals at least one full wrap are ambiguous.
 */
static void stm32_capture_dual_edge_sample(struct stm32_capture_device *device,
                                           rt_uint32_t channel, rt_uint32_t captured)
{
    TIM_HandleTypeDef *timer = device->timer; /* Shared free-running TIM counter. */
    rt_uint32_t delta;                        /* Elapsed ticks modulo timer ARR+1. */
    rt_bool_t was_high;                       /* Level ending at the captured edge. */

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
        if (delta != 0U)
        {
            /* A rising edge closes LOW; a falling edge closes HIGH, regardless of channel order. */
            was_high = (channel == device->config->channel) ? !device->config->initial_edge_rising
                                                            : device->config->initial_edge_rising;
            device->pulsewidth_us =
                (rt_uint32_t)(((rt_uint64_t)delta * 1000000ULL + device->counter_hz / 2U) /
                              device->counter_hz);
            rt_hw_inputcapture_isr(&device->parent, was_high);
        }
    }
    device->previous_count = captured;
    device->first_edge = RT_FALSE;
    /* A valid next edge on the same TI input must have the opposite polarity. */
    device->next_edge_rising = (channel == device->config->channel) ? !device->config->initial_edge_rising
                                                                    : device->config->initial_edge_rising;
}

/**
 * @brief Consume paired captures and identify whether DUAL_EDGE owns this timer IRQ.
 * @param timer Shared physical TIM handle for the incoming interrupt.
 * @return RT_TRUE if DUAL_EDGE handled the IRQ, including inactive or discarded events;
 *         RT_FALSE if the IRQ must be dispatched through the normal HAL handler.
 * @note Reading a CCR acknowledges CCxIF, so HAL must not redispatch a handled dual-edge IRQ.
 */
static rt_bool_t stm32_capture_dual_edge_handle_irq(TIM_HandleTypeDef *timer)
{
    struct stm32_capture_device *device = stm32_capture_find_device(timer, TIM_CHANNEL_1); /* Paired TI owner. */

    if (device != RT_NULL && device->config->dual_edge)
    {
        if (device->active)
        {
            rt_uint32_t flags = timer->Instance->SR;                     /* Pending edge/overcapture snapshot. */
            rt_uint32_t pending = flags & (TIM_FLAG_CC1 | TIM_FLAG_CC2); /* Captures to consume. */
            rt_uint32_t cc1 = 0U;                                        /* CH1 timestamp, valid only when CC1IF was set. */
            rt_uint32_t cc2 = 0U;                                        /* CH2 timestamp, valid only when CC2IF was set. */
            rt_uint32_t overcapture;                                     /* A lost capture makes both intervals untrustworthy. */
            rt_uint32_t delta1;                                          /* CH1 elapsed ticks from the previous accepted edge. */
            rt_uint32_t delta2;                                          /* CH2 elapsed ticks from the previous accepted edge. */
            rt_uint32_t expected;                                        /* Channel of the next physical polarity after the last accepted edge. */

            /* Reading an input CCR clears CCxIF. Do not clear it again after the read. */
            if (pending & TIM_FLAG_CC1)
            {
                cc1 = HAL_TIM_ReadCapturedValue(timer, TIM_CHANNEL_1);
            }
            if (pending & TIM_FLAG_CC2)
            {
                cc2 = HAL_TIM_ReadCapturedValue(timer, TIM_CHANNEL_2);
            }
            overcapture = (flags | timer->Instance->SR) & (TIM_FLAG_CC1OF | TIM_FLAG_CC2OF);
            if (overcapture)
            {
                __HAL_TIM_CLEAR_FLAG(timer, overcapture);
                device->first_edge = RT_TRUE;
                return RT_TRUE;
            }

            if (pending == (TIM_FLAG_CC1 | TIM_FLAG_CC2))
            {
                /* HAL serves CC1 before CC2, which is not necessarily physical edge order.
                 * The previous timestamp can order both events only within one counter wrap. */
                if (device->first_edge)
                {
                    return RT_TRUE; /* Initial paired events have no known chronological anchor. */
                }
                delta1 = (cc1 >= device->previous_count) ? cc1 - device->previous_count
                                                         : (timer->Init.Period - device->previous_count + 1U) + cc1;
                delta2 = (cc2 >= device->previous_count) ? cc2 - device->previous_count
                                                         : (timer->Init.Period - device->previous_count + 1U) + cc2;
                expected = (device->next_edge_rising == device->config->initial_edge_rising)
                               ? device->config->channel
                               : stm32_capture_paired_partner(device->config->channel);
                if (delta1 == 0U || delta2 == 0U || delta1 == delta2 ||
                    (delta1 < delta2 ? TIM_CHANNEL_1 : TIM_CHANNEL_2) != expected)
                {
                    /* Lost or ambiguous ordering must not produce a wrapped, false pulse. */
                    device->first_edge = RT_TRUE;
                    return RT_TRUE;
                }
                if (delta1 < delta2)
                {
                    stm32_capture_dual_edge_sample(device, TIM_CHANNEL_1, cc1);
                    stm32_capture_dual_edge_sample(device, TIM_CHANNEL_2, cc2);
                }
                else
                {
                    stm32_capture_dual_edge_sample(device, TIM_CHANNEL_2, cc2);
                    stm32_capture_dual_edge_sample(device, TIM_CHANNEL_1, cc1);
                }
            }
            /* A single CCxIF is normal in DUAL_EDGE. Unlike legacy EDGE mode,
             * both polarities remain armed instead of switching the active edge.
             * As in the legacy driver, a missed opposite edge cannot be recovered:
             * a later same-polarity capture may report an incorrect long interval.
             * No polarity-alternation check is applied to single pending events. */
            else if (pending & TIM_FLAG_CC1)
            {
                stm32_capture_dual_edge_sample(device, TIM_CHANNEL_1, cc1);
            }
            else if (pending & TIM_FLAG_CC2)
            {
                stm32_capture_dual_edge_sample(device, TIM_CHANNEL_2, cc2);
            }
        }
        return RT_TRUE; /* DUAL_EDGE owns both capture IRQs; HAL must not dispatch them again. */
    }
    return RT_FALSE;
}
#endif /* BSP_USING_INPUT_CAPTURE_DUAL_EDGE */

/**
 * @brief Dispatch DUAL_EDGE captures in timestamp order, otherwise use HAL's normal TIM IRQ path.
 * @param timer Shared physical TIM handle.
 */
static void stm32_capture_handle_irq(TIM_HandleTypeDef *timer)
{
#ifdef BSP_USING_INPUT_CAPTURE_DUAL_EDGE
    if (stm32_capture_dual_edge_handle_irq(timer))
    {
        return;
    }
#endif /* BSP_USING_INPUT_CAPTURE_DUAL_EDGE */
    HAL_TIM_IRQHandler(timer);
}

/**
 * @brief Initialize the shared physical TIM and this device's capture channel.
 * @param inputcapture RT-Thread capture device to initialize.
 * @return RT_EOK on success, negative RT-Thread error otherwise.
 */
static rt_err_t stm32_capture_init(struct rt_inputcapture_device *inputcapture)
{
    struct stm32_capture_device *device =
        rt_container_of(inputcapture, struct stm32_capture_device, parent); /* Logical capture state. */
    const struct stm32_inputcapture_config *config = device->config;        /* Board mapping. */
    TIM_HandleTypeDef *timer = device->timer;                               /* Shared HAL timer handle. */
    TIM_IC_InitTypeDef ic = {0};                                            /* EDGE channel settings. */
    rt_uint32_t clock = stm32_inputcapture_timer_clock(config->instance);   /* Physical TIM clock. */

    if (clock < BSP_INPUT_CAPTURE_COUNTER_HZ || clock % BSP_INPUT_CAPTURE_COUNTER_HZ != 0U)
    {
        LOG_E("%s unsupported TIM clock %u for %u Hz", config->name, clock, BSP_INPUT_CAPTURE_COUNTER_HZ);
        return -RT_EINVAL;
    }
    /* The first device initializes shared PSC/ARR and CubeMX IC MSP only once. */
    if (timer->State == HAL_TIM_STATE_RESET)
    {
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
        if (HAL_TIM_IC_Init(timer) != HAL_OK)
        {
            LOG_E("%s timer HAL initialization failed", config->name);
            return -RT_ERROR;
        }
    }
    device->counter_hz = BSP_INPUT_CAPTURE_COUNTER_HZ;
#ifdef BSP_USING_INPUT_CAPTURE_PWM_INPUT
    if (config->pwm_input)
    {
        return stm32_capture_pwm_input_init(device);
    }
#endif /* BSP_USING_INPUT_CAPTURE_PWM_INPUT */
#ifdef BSP_USING_INPUT_CAPTURE_DUAL_EDGE
    if (config->dual_edge)
    {
        return stm32_capture_dual_edge_init(device);
    }
#endif /* BSP_USING_INPUT_CAPTURE_DUAL_EDGE */

    ic.ICPolarity = config->initial_edge_rising ? TIM_INPUTCHANNELPOLARITY_RISING : TIM_INPUTCHANNELPOLARITY_FALLING;
    if (config->hardware_both_edges)
    {
#if STM32_INPUTCAPTURE_HAL_HAS_BOTHEDGE_POLARITY
        ic.ICPolarity = STM32_INPUTCAPTURE_HAL_BOTHEDGE_POLARITY;
#else
        return -RT_ENOSYS;
#endif /* STM32_INPUTCAPTURE_HAL_HAS_BOTHEDGE_POLARITY */
    }
    ic.ICSelection = TIM_ICSELECTION_DIRECTTI;
    ic.ICPrescaler = TIM_ICPSC_DIV1;
    ic.ICFilter = config->input_filter;
    if (HAL_TIM_IC_ConfigChannel(timer, &ic, config->channel) != HAL_OK)
    {
        LOG_E("%s EDGE channel configuration failed", config->name);
        return -RT_ERROR;
    }
    return RT_EOK;
}

/**
 * @brief Start capture on this logical device without resetting a running timer.
 * @param inputcapture Device to open.
 * @return RT_EOK or a negative FIFO/HAL error code.
 */
static rt_err_t stm32_capture_open(struct rt_inputcapture_device *inputcapture)
{
    struct stm32_capture_device *device =
        rt_container_of(inputcapture, struct stm32_capture_device, parent); /* Logical capture device. */
    const struct stm32_inputcapture_config *config = device->config;        /* Capture config. */
    TIM_HandleTypeDef *timer = device->timer;                               /* Shared timer. */
    HAL_StatusTypeDef status;                                               /* Capture start result. */

    if (!inputcapture->ringbuff)
    {
        return -RT_ENOMEM;
    }
    device->first_edge = RT_TRUE;
    device->previous_count = 0U;
    device->pulsewidth_us = 0U;
    device->next_edge_rising = config->initial_edge_rising;
    /* CNT is shared; only the first active logical device may reset it. */
    if (!stm32_capture_timer_active(timer))
    {
        __HAL_TIM_SET_COUNTER(timer, 0U);
    }
    /* HAL can dispatch CC IRQ before Start_IT returns; publish the ISR gate first. */
    device->active = RT_TRUE;
#ifdef BSP_USING_INPUT_CAPTURE_PWM_INPUT
    if (config->pwm_input)
    {
        status = stm32_capture_pwm_input_open(device);
    }
    else
#endif /* BSP_USING_INPUT_CAPTURE_PWM_INPUT */
#ifdef BSP_USING_INPUT_CAPTURE_DUAL_EDGE
        if (config->dual_edge)
    {
        status = stm32_capture_dual_edge_open(device);
    }
    else
#endif /* BSP_USING_INPUT_CAPTURE_DUAL_EDGE */
    {
        if (!config->hardware_both_edges)
        {
            __HAL_TIM_SET_CAPTUREPOLARITY(timer, config->channel,
                                          device->next_edge_rising ? TIM_INPUTCHANNELPOLARITY_RISING : TIM_INPUTCHANNELPOLARITY_FALLING);
        }
        /* Clear stale capture and overcapture flags for this EDGE channel only. */
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
        status = HAL_TIM_IC_Start_IT(timer, config->channel);
    }
    if (status != HAL_OK)
    {
        device->active = RT_FALSE;
        LOG_E("%s capture start failed", config->name);
        return -RT_ERROR;
    }
    return RT_EOK;
}

/**
 * @brief Stop only this logical device's channels, retaining the shared TIM.
 * @param inputcapture Device to stop.
 * @return RT_EOK or a negative HAL error code.
 */
static rt_err_t stm32_capture_close(struct rt_inputcapture_device *inputcapture)
{
    struct stm32_capture_device *device =
        rt_container_of(inputcapture, struct stm32_capture_device, parent); /* Logical capture device. */
    HAL_StatusTypeDef status;                                               /* HAL channel stop result. */

    if (!device->active)
    {
        return RT_EOK;
    }
#ifdef BSP_USING_INPUT_CAPTURE_PWM_INPUT
    if (device->config->pwm_input)
    {
        status = stm32_capture_pwm_input_close(device);
    }
    else
#endif /* BSP_USING_INPUT_CAPTURE_PWM_INPUT */
#ifdef BSP_USING_INPUT_CAPTURE_DUAL_EDGE
        if (device->config->dual_edge)
    {
        status = stm32_capture_dual_edge_close(device);
    }
    else
#endif /* BSP_USING_INPUT_CAPTURE_DUAL_EDGE */
    {
        status = HAL_TIM_IC_Stop_IT(device->timer, device->config->channel);
    }
    if (status != HAL_OK)
    {
        LOG_E("%s capture stop failed", device->config->name);
        return -RT_ERROR;
    }
    device->active = RT_FALSE;
    return RT_EOK;
}

/**
 * @brief Return the last recorded pulse duration to RT-Thread's FIFO.
 * @param inputcapture Source capture device.
 * @param pulsewidth_us Output duration, microseconds.
 * @return RT_EOK.
 */
static rt_err_t stm32_capture_get_pulsewidth(struct rt_inputcapture_device *inputcapture,
                                             rt_uint32_t *pulsewidth_us)
{
    struct stm32_capture_device *device =
        rt_container_of(inputcapture, struct stm32_capture_device, parent); /* Logical capture device. */
    *pulsewidth_us = device->pulsewidth_us;
    return RT_EOK;
}

/** @brief RT-Thread Input Capture backend operations. */
static const struct rt_inputcapture_ops stm32_capture_ops = {
    .init = stm32_capture_init,
    .open = stm32_capture_open,
    .close = stm32_capture_close,
    .get_pulsewidth = stm32_capture_get_pulsewidth,
};

/**
 * @brief Route a physical TIM capture interrupt to its owning logical device.
 * @param timer Shared HAL timer handle reporting the captured CCR channel.
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *timer)
{
    rt_uint32_t channel = stm32_capture_channel(timer->Channel);                     /* Selected HAL CCR channel. */
    struct stm32_capture_device *device = stm32_capture_find_device(timer, channel); /* Logical owner. */
    const struct stm32_inputcapture_config *config;                                  /* Board channel configuration. */
    rt_uint32_t captured;                                                            /* Timestamp captured by hardware. */
    rt_uint32_t delta;                                                               /* Ticks since the preceding captured edge. */
    rt_bool_t was_high;                                                              /* Level of the completed interval. */

    if (device == RT_NULL || !device->active)
    {
        return;
    }
    config = device->config;
#ifdef BSP_USING_INPUT_CAPTURE_PWM_INPUT
    if (config->pwm_input)
    {
        stm32_capture_pwm_input_sample(device);
        return;
    }
#endif /* BSP_USING_INPUT_CAPTURE_PWM_INPUT */
#ifdef BSP_USING_INPUT_CAPTURE_DUAL_EDGE
    if (config->dual_edge)
    {
        return; /* Paired channels are consumed together by the TIM IRQ dispatcher. */
    }
#endif /* BSP_USING_INPUT_CAPTURE_DUAL_EDGE */

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
 * @brief Register one RT-Thread device per EDGE channel or per exclusive paired-input TIM.
 * @return RT_EOK or a configuration/registration failure.
 */
int rt_hw_inputcapture_init(void)
{
    rt_size_t i;     /* Current logical capture device. */
    rt_err_t status; /* Registration result. */

    for (i = 0; i < sizeof(stm32_capture_devices) / sizeof(stm32_capture_devices[0]); i++)
    {
        stm32_capture_devices[i].config = &stm32_capture_configs[i];
        stm32_capture_devices[i].timer = stm32_capture_get_timer(stm32_capture_configs[i].instance);
        stm32_capture_devices[i].parent.ops = &stm32_capture_ops;
        status = rt_device_inputcapture_register(&stm32_capture_devices[i].parent,
                                                 stm32_capture_configs[i].name,
                                                 &stm32_capture_devices[i]);
        if (status != RT_EOK)
        {
            LOG_E("%s registration failed: %d", stm32_capture_configs[i].name, status);
            return status;
        }
        LOG_D("%s registered", stm32_capture_configs[i].name);
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_inputcapture_init);

#ifdef BSP_USING_INPUT_CAPTURE_TIM1
/** @brief Dispatch TIM1 input-capture IRQ under the RT-Thread ISR boundary. */
void TIM1_CC_IRQHandler(void)
{
    rt_interrupt_enter();
    stm32_capture_handle_irq(&stm32_capture_timers[STM32_CAPTURE_TIM1_INDEX]);
    rt_interrupt_leave();
}
#endif /* BSP_USING_INPUT_CAPTURE_TIM1 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM2
/** @brief Dispatch TIM2 input-capture IRQ under the RT-Thread ISR boundary. */
void TIM2_IRQHandler(void)
{
    rt_interrupt_enter();
    stm32_capture_handle_irq(&stm32_capture_timers[STM32_CAPTURE_TIM2_INDEX]);
    rt_interrupt_leave();
}
#endif /* BSP_USING_INPUT_CAPTURE_TIM2 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM3
/** @brief Dispatch TIM3 input-capture IRQ under the RT-Thread ISR boundary. */
void TIM3_IRQHandler(void)
{
    rt_interrupt_enter();
    stm32_capture_handle_irq(&stm32_capture_timers[STM32_CAPTURE_TIM3_INDEX]);
    rt_interrupt_leave();
}
#endif /* BSP_USING_INPUT_CAPTURE_TIM3 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM4
/** @brief Dispatch TIM4 input-capture IRQ under the RT-Thread ISR boundary. */
void TIM4_IRQHandler(void)
{
    rt_interrupt_enter();
    stm32_capture_handle_irq(&stm32_capture_timers[STM32_CAPTURE_TIM4_INDEX]);
    rt_interrupt_leave();
}
#endif /* BSP_USING_INPUT_CAPTURE_TIM4 */

