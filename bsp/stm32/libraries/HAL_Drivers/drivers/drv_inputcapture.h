/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-11-01     wdfk-prog         first version
 */
#ifndef __DRV_INPUTCAPTURE_H__
#define __DRV_INPUTCAPTURE_H__

#include <board.h>
#include <drivers/rt_inputcapture.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Hardware mapping for one STM32 timer Input Capture device.
     * @note GPIO, peripheral clocks and NVIC setup belong to CubeMX's HAL MSP
     *       initialization, not to this device mapping.
     */
    struct stm32_inputcapture_config
    {
        const char *name;                /**< Registered RT-Thread device name. */
        TIM_TypeDef *instance;           /**< Physical timer peripheral instance. */
        rt_uint32_t channel;             /**< Selected direct-TI HAL TIM_CHANNEL_x. */
        rt_uint32_t input_filter;        /**< HAL input digital filter value. */
        rt_uint32_t counter_period;      /**< Configured timer auto-reload value. */
        rt_bool_t initial_edge_rising;   /**< Initial capture edge when the line level is not sampled. */
        rt_bool_t hardware_both_edges;   /**< True only for supported hardware both-edge capture. */
        rt_bool_t pwm_input;             /**< PWM Input uses CH1/CH2 and reserves the entire physical TIM. */
        rt_bool_t dual_edge;             /**< Pair CH1/CH2 for independent edge timestamps on one TI input. */
        rt_uint32_t dual_partner_filter; /**< Digital filter for the indirect channel in dual-edge mode. */
    };

    /**
     * @brief Register enabled STM32 Input Capture timers with RT-Thread.
     * @return RT_EOK or the first RT-Thread registration error.
     */
    int rt_hw_inputcapture_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DRV_INPUTCAPTURE_H__ */
