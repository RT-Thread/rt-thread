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
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_common.h>
#include <drv_config.h>
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
    const char *name;              /**< Registered RT-Thread device name. */
    TIM_TypeDef *instance;         /**< Physical timer peripheral instance. */
    rt_uint32_t channel;           /**< The only selected HAL TIM_CHANNEL_x. */
    rt_uint32_t input_filter;      /**< HAL input digital filter value. */
    rt_uint32_t counter_period;    /**< Default ARR for 16-bit TIM; 32-bit TIM uses its full range. */
    rt_bool_t initial_edge_rising; /**< Initial capture edge when the line level is not sampled. */
    rt_bool_t hardware_both_edges; /**< True only for supported hardware both-edge capture. */
};

/**
 * @brief Register enabled STM32 Input Capture timers with RT-Thread.
 * @return RT_EOK or the first RT-Thread registration error.
 * @note The board must give each TIM and its IRQ a single owner. If HAL
 *       callback registration is enabled, the board must register this
 *       driver's HAL_TIM_IC_CaptureCallback explicitly.
 */
int rt_hw_inputcapture_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DRV_INPUTCAPTURE_H__ */
