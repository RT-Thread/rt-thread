/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef DRV_RTC_H__
#define DRV_RTC_H__

#include <nrfx.h>
#include <hal/nrf_rtc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup drv_rtc RTC driver
 * @{
 * @ingroup app_timer
 * @brief   Real Timer Counter (RTC) peripheral driver for app_timer.
 */

/** @brief Maximum RTC counter value. */
#define DRV_RTC_MAX_CNT     RTC_COUNTER_COUNTER_Msk

/** @brief Time requires to update registers between RTC and MCU domains. */
#define DRV_RTC_CONFIG_APPLY_TIME_US 33

/**
 * @brief Minimum delta value between set value and counter value.
 *
 * RTC peripheral requires two ticks to be sure that value it properly set in RTC value. Compare
 * channel function requires additional one tick to avoid problematic situations (lack or additional
 * unspecified event) when Compare Channel register is reseting or setting to N+2 value.
 */
#define DRV_RTC_MIN_TICK_HANDLED 3

/** @brief Macro to convert microseconds into ticks. */
#define DRV_RTC_US_TO_TICKS(us,freq) (us >= 2^17 ? \
    ((((us)/1000)*(freq))/1000U) : (((us)*(freq))/1000000U) )


/** @brief RTC driver instance structure. */
typedef struct
{
    NRF_RTC_Type  * p_reg;            /**< Pointer to instance register set. */
    IRQn_Type       irq;              /**< Instance IRQ ID. */
    uint8_t         instance_id;      /**< Instance index. */
    uint8_t         cc_channel_count; /**< Number of capture/compare channels. */
} drv_rtc_t;

/** @brief Macro for creating RTC driver instance.*/
#define DRV_RTC_INSTANCE(id)                                       \
{                                                                  \
    .p_reg            = NRFX_CONCAT_2(NRF_RTC, id),                \
    .irq              = NRFX_CONCAT_3(RTC, id, _IRQn),             \
    .instance_id      = NRFX_CONCAT_3(DRV_RTC_RTC, id, _INST_IDX), \
    .cc_channel_count = NRF_RTC_CC_CHANNEL_COUNT(id),              \
}

enum {
#if defined(APP_TIMER_V2_RTC0_ENABLED)
    DRV_RTC_RTC0_INST_IDX,
#endif
#if defined(APP_TIMER_V2_RTC1_ENABLED)
    DRV_RTC_RTC1_INST_IDX,
#endif
#if defined(APP_TIMER_V2_RTC2_ENABLED)
    DRV_RTC_RTC2_INST_IDX,
#endif
    DRV_RTC_ENABLED_COUNT
};

/** @brief RTC driver instance configuration structure. */
typedef struct
{
    uint16_t prescaler;          /**< Prescaler. */
    uint8_t  interrupt_priority; /**< Interrupt priority. */
} drv_rtc_config_t;

/** @brief RTC instance default configuration. */
#define DRV_RTC_DEFAULT_CONFIG                                                     \
{                                                                                  \
    .prescaler          = RTC_FREQ_TO_PRESCALER(DRV_RTC_DEFAULT_CONFIG_FREQUENCY), \
    .interrupt_priority = DRV_RTC_DEFAULT_CONFIG_IRQ_PRIORITY,                     \
}

/** @brief RTC driver instance handler type. */
typedef void (*drv_rtc_handler_t)(drv_rtc_t const * const  p_instance);

/**
 * @brief Function for initializing the RTC driver instance.
 *
 * After initialization, the instance is in power off state. The LFCLK (@ref nrfx_clock)
 * has to be started before using @ref drv_rtc.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] p_config   Pointer to the structure with initial configuration.
 * @param[in] handler    Event handler provided by the user. Must not be NULL.
 *
 * @retval NRF_SUCCESS             If successfully initialized.
 * @retval NRF_ERROR_INVALID_STATE If the instance is already initialized.
 */
ret_code_t drv_rtc_init(drv_rtc_t const * const  p_instance,
                        drv_rtc_config_t const * p_config,
                        drv_rtc_handler_t        handler);

/**
 * @brief Function for uninitializing the RTC driver instance.
 *
 * After uninitialization, the instance is in idle state. The hardware should return to the state
 *       before initialization. The function asserts if the instance is in idle state.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
void drv_rtc_uninit(drv_rtc_t const * const p_instance);

/**
 * @brief Function for starting RTC clock.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
void drv_rtc_start(drv_rtc_t const * const p_instance);

/**
 * @brief Function for stopping RTC clock.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
void drv_rtc_stop(drv_rtc_t const * const p_instance);

/**
 * @brief Function for configuring compare channel.
 *
 * @note Function disables interrupts and only enable compare events. Remember to enable interrupt
 * using @ref drv_rtc_compare_enable in case of using it.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] cc         Compare channel index.
 * @param[in] abs_value  Absolute value to be set in the compare register.
 * @param[in] irq_enable True to enable interrupt.
 */
void drv_rtc_compare_set(drv_rtc_t const * const p_instance,
                         uint32_t                cc,
                         uint32_t                abs_value,
                         bool                    irq_enable);

/**
 * @brief Function for configuring compare channel with safe window.
 *
 * Maximum possible relative value is limited by safe window to detect
 * cases when requested compare event has already occured.
 *
 * @param[in] p_instance  Pointer to the driver instance structure.
 * @param[in] cc          Compare channel index.
 * @param[in] abs_value   Absolute value to be set in the compare register.
 * @param[in] safe_window Width of the safe window.
 *
 * @retval NRF_ERROR_TIMEOUT If @par abs_value is in safe window of event occured before
 *                           enabling compare channel intterupt.
 * @retval NRF_SUCCESS       If successfully set.
 */
ret_code_t drv_rtc_windowed_compare_set(drv_rtc_t const * const p_instance,
                                        uint32_t                    cc,
                                        uint32_t                    abs_value,
                                        uint16_t                    safe_window);

/**
 * @brief Function for enabling overflow event and interrupt.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] irq_enable True to enable interrupt.
 */
void drv_rtc_overflow_enable(drv_rtc_t const * const p_instance, bool irq_enable);

/**
 * @brief Function for diabling overflow event and interrupt.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
void drv_rtc_overflow_disable(drv_rtc_t const * const p_instance);

/**
 * @brief Function for checking if overflow event has occured.
 *
 * @note Event is cleared after reading.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @return True if interrupt pending, false otherwise.
 */
bool drv_rtc_overflow_pending(drv_rtc_t const * const p_instance);

/**
 * @brief Function for enabling tick event and interrupt.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] irq_enable True to enable interrupt.
 */
void drv_rtc_tick_enable(drv_rtc_t const * const p_instance, bool irq_enable);

/**
 * @brief Function for disabling tick event and interrupt.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
void drv_rtc_tick_disable(drv_rtc_t const * const p_instance);

/**
 * @brief Function for checking if tick event has occured.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @return True if interrupt pending, false otherwise.
 */
bool drv_rtc_tick_pending(drv_rtc_t const * const p_instance);

/**
 * @brief Function for enabling compare channel event and interrupt.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] cc         Compare channel index.
 * @param[in] irq_enable True to enable interrupt.
 */
void drv_rtc_compare_enable(drv_rtc_t const * const p_instance,
                            uint32_t cc,
                            bool irq_enable);

/**
 * @brief Function for disabling compare channel event and interrupt.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] cc         Compare channel index.
 */
void drv_rtc_compare_disable(drv_rtc_t const * const p_instance, uint32_t cc);

/**
 * @brief Function for checking if compare channel event has occured.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 * @param[in] cc         Compare channel index.
 *
 * @return True if interrupt pending, false otherwise.
 */
bool drv_rtc_compare_pending(drv_rtc_t const * const p_instance, uint32_t cc);

/**
 * @brief Function for getting current value of RTC counter.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 *
 * @return Counter value.
 */
uint32_t drv_rtc_counter_get(drv_rtc_t const * const p_instance);

/**
 * @brief Function for triggering RTC interrupt.
 *
 * @param[in] p_instance Pointer to the driver instance structure.
 */
void drv_rtc_irq_trigger(drv_rtc_t const * const p_instance);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // DRV_RTC_H__
