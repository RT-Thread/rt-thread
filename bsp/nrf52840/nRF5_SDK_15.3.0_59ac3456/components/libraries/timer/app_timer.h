/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup app_timer Application Timer
 * @{
 * @ingroup app_common
 *
 * @brief Application timer functionality.
 *
 * @details This module enables the application to create multiple timer instances based on the RTC1
 *          peripheral. Checking for time-outs and invocation of user time-out handlers is performed
 *          in the RTC1 interrupt handler. List handling is done using a software interrupt (SWI0).
 *          Both interrupt handlers are running in APP_LOW priority level.
 *
 * @details When calling app_timer_start() or app_timer_stop(), the timer operation is just queued,
 *          and the software interrupt is triggered. The actual timer start/stop operation is
 *          executed by the SWI0 interrupt handler. Since the SWI0 interrupt is running in APP_LOW,
 *          if the application code calling the timer function is running in APP_LOW or APP_HIGH,
 *          the timer operation will not be performed until the application handler has returned.
 *          This will be the case, for example, when stopping a timer from a time-out handler when not using
 *          the scheduler.
 *
 * @details Use the USE_SCHEDULER parameter of the APP_TIMER_INIT() macro to select if the
 *          @ref app_scheduler should be used or not. Even if the scheduler is
 *          not used, app_timer.h will include app_scheduler.h, so when
 *          compiling, app_scheduler.h must be available in one of the compiler include paths.
 */

#ifndef APP_TIMER_H__
#define APP_TIMER_H__
#include "sdk_config.h"
#include "app_error.h"
#include "app_util.h"
#include "compiler_abstraction.h"
#include "nordic_common.h"
#ifdef APP_TIMER_V2
#include "nrf_log_instance.h"
#include "nrf_sortlist.h"
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Name of the module used for logger messaging.
 */
#define APP_TIMER_LOG_NAME app_timer

#define APP_TIMER_CLOCK_FREQ            32768                     /**< Clock frequency of the RTC timer used to implement the app timer module. */
#define APP_TIMER_MIN_TIMEOUT_TICKS     5                         /**< Minimum value of the timeout_ticks parameter of app_timer_start(). */

#ifdef RTX
#define APP_TIMER_NODE_SIZE             40                        /**< Size of app_timer.timer_node_t (used to allocate data). */
#else
#define APP_TIMER_NODE_SIZE             32                        /**< Size of app_timer.timer_node_t (used to allocate data). */
#endif // RTX

#define APP_TIMER_SCHED_EVENT_DATA_SIZE sizeof(app_timer_event_t) /**< Size of event data when scheduler is used. */

#define APP_TIMER_MAX_CNT_VAL          RTC_COUNTER_COUNTER_Msk    /**< Maximum counter value that can be returned by @ref app_timer_cnt_get. */

/**@brief Convert milliseconds to timer ticks.
 *
 * This macro uses 64-bit integer arithmetic, but as long as the macro parameters are
 *       constants (i.e. defines), the computation will be done by the preprocessor.
 *
 * @param[in]  MS          Milliseconds.
 *
 * @return     Number of timer ticks.
 */
#ifndef FREERTOS
#define APP_TIMER_TICKS(MS)                                \
            ((uint32_t)ROUNDED_DIV(                        \
            (MS) * (uint64_t)APP_TIMER_CLOCK_FREQ,         \
            1000 * (APP_TIMER_CONFIG_RTC_FREQUENCY + 1)))
#else
#include "FreeRTOSConfig.h"
#define APP_TIMER_TICKS(MS) (uint32_t)ROUNDED_DIV((MS)*configTICK_RATE_HZ,1000)
#endif


/**
 * @brief Create a timer identifier and statically allocate memory for the timer.
 *
 * @param timer_id Name of the timer identifier variable that will be used to control the timer.
 */
#define APP_TIMER_DEF(timer_id) _APP_TIMER_DEF(timer_id)

/**@brief Application time-out handler type. */
typedef void (*app_timer_timeout_handler_t)(void * p_context);

#ifdef APP_TIMER_V2
/**
 * @brief app_timer control block
 */
typedef struct
{
    nrf_sortlist_item_t         list_item;     /**< Token used by sortlist. */
    volatile uint32_t           end_val;       /**< RTC counter value when timer expires. */
    uint32_t                    repeat_period; /**< Repeat period (0 if single shot mode). */
    app_timer_timeout_handler_t handler;       /**< User handler. */
    void *                      p_context;     /**< User context. */
    NRF_LOG_INSTANCE_PTR_DECLARE(p_log)        /**< Pointer to instance of the logger object (Conditionally compiled). */
    volatile bool               active;        /**< Flag indicating that timer is active. */
} app_timer_t;

/**@brief Timer ID type.
 * Never declare a variable of this type, but use the macro @ref APP_TIMER_DEF instead.*/
typedef app_timer_t * app_timer_id_t;

#define _APP_TIMER_DEF(timer_id)                                                              \
    NRF_LOG_INSTANCE_REGISTER(APP_TIMER_LOG_NAME, timer_id,                                   \
                              APP_TIMER_CONFIG_INFO_COLOR,                                    \
                              APP_TIMER_CONFIG_DEBUG_COLOR,                                   \
                              APP_TIMER_CONFIG_INITIAL_LOG_LEVEL,                             \
                              APP_TIMER_CONFIG_LOG_ENABLED ?                                  \
                                         APP_TIMER_CONFIG_LOG_LEVEL : NRF_LOG_SEVERITY_NONE); \
    static app_timer_t CONCAT_2(timer_id,_data) = {                                           \
            .active = false,                                                                  \
            NRF_LOG_INSTANCE_PTR_INIT(p_log, APP_TIMER_LOG_NAME, timer_id)                    \
    };                                                                                        \
    static const app_timer_id_t timer_id = &CONCAT_2(timer_id,_data)

#else //APP_TIMER_V2
typedef struct app_timer_t { uint32_t data[CEIL_DIV(APP_TIMER_NODE_SIZE, sizeof(uint32_t))]; } app_timer_t;

/**@brief Timer ID type.
 * Never declare a variable of this type, but use the macro @ref APP_TIMER_DEF instead.*/
typedef app_timer_t * app_timer_id_t;

#define _APP_TIMER_DEF(timer_id)                                      \
    static app_timer_t CONCAT_2(timer_id,_data) = { {0} };           \
    static const app_timer_id_t timer_id = &CONCAT_2(timer_id,_data)

#endif


/**@brief Structure passed to app_scheduler. */
typedef struct
{
    app_timer_timeout_handler_t timeout_handler;
    void *                      p_context;
} app_timer_event_t;

/**@brief Timer modes. */
typedef enum
{
    APP_TIMER_MODE_SINGLE_SHOT,                 /**< The timer will expire only once. */
    APP_TIMER_MODE_REPEATED                     /**< The timer will restart each time it expires. */
} app_timer_mode_t;

/**@brief Function for initializing the timer module.
 *
 * @retval     NRF_SUCCESS               If the module was initialized successfully.
 */
ret_code_t app_timer_init(void);

/**@brief Function for creating a timer instance.
 *
 * @param[in]  p_timer_id        Pointer to timer identifier.
 * @param[in]  mode              Timer mode.
 * @param[in]  timeout_handler   Function to be executed when the timer expires.
 *
 * @retval     NRF_SUCCESS               If the timer was successfully created.
 * @retval     NRF_ERROR_INVALID_PARAM   If a parameter was invalid.
 * @retval     NRF_ERROR_INVALID_STATE   If the application timer module has not been initialized or
 *                                       the timer is running.
 *
 * @note This function does the timer allocation in the caller's context. It is also not protected
 *       by a critical region. Therefore care must be taken not to call it from several interrupt
 *       levels simultaneously.
 * @note The function can be called again on the timer instance and will re-initialize the instance if
 *       the timer is not running.
 * @attention The FreeRTOS and RTX app_timer implementation does not allow app_timer_create to
 *       be called on the previously initialized instance.
 */
ret_code_t app_timer_create(app_timer_id_t const *      p_timer_id,
                            app_timer_mode_t            mode,
                            app_timer_timeout_handler_t timeout_handler);

/**@brief Function for starting a timer.
 *
 * @param[in]       timer_id      Timer identifier.
 * @param[in]       timeout_ticks Number of ticks (of RTC1, including prescaling) to time-out event
 *                                (minimum 5 ticks).
 * @param[in]       p_context     General purpose pointer. Will be passed to the time-out handler when
 *                                the timer expires.
 *
 * @retval     NRF_SUCCESS               If the timer was successfully started.
 * @retval     NRF_ERROR_INVALID_PARAM   If a parameter was invalid.
 * @retval     NRF_ERROR_INVALID_STATE   If the application timer module has not been initialized or the timer
 *                                       has not been created.
 * @retval     NRF_ERROR_NO_MEM          If the timer operations queue was full.
 *
 * @note The minimum timeout_ticks value is 5.
 * @note For multiple active timers, time-outs occurring in close proximity to each other (in the
 *       range of 1 to 3 ticks) will have a positive jitter of maximum 3 ticks.
 * @note When calling this method on a timer that is already running, the second start operation
 *       is ignored.
 */
ret_code_t app_timer_start(app_timer_id_t timer_id, uint32_t timeout_ticks, void * p_context);

/**@brief Function for stopping the specified timer.
 *
 * @param[in]  timer_id                  Timer identifier.
 *
 * @retval     NRF_SUCCESS               If the timer was successfully stopped.
 * @retval     NRF_ERROR_INVALID_PARAM   If a parameter was invalid.
 * @retval     NRF_ERROR_INVALID_STATE   If the application timer module has not been initialized or the timer
 *                                       has not been created.
 * @retval     NRF_ERROR_NO_MEM          If the timer operations queue was full.
 */
ret_code_t app_timer_stop(app_timer_id_t timer_id);

/**@brief Function for stopping all running timers.
 *
 * @retval     NRF_SUCCESS               If all timers were successfully stopped.
 * @retval     NRF_ERROR_INVALID_STATE   If the application timer module has not been initialized.
 * @retval     NRF_ERROR_NO_MEM          If the timer operations queue was full.
 */
ret_code_t app_timer_stop_all(void);

/**@brief Function for returning the current value of the RTC1 counter.
 *
 * @return    Current value of the RTC1 counter.
 */
uint32_t app_timer_cnt_get(void);

/**@brief Function for computing the difference between two RTC1 counter values.
 *
 * @param[in]  ticks_to       Value returned by app_timer_cnt_get().
 * @param[in]  ticks_from     Value returned by app_timer_cnt_get().
 *
 * @return    Number of ticks from ticks_from to ticks_to.
 */
uint32_t app_timer_cnt_diff_compute(uint32_t   ticks_to,
                                    uint32_t   ticks_from);


/**@brief Function for getting the maximum observed operation queue utilization.
 *
 * Function for tuning the module and determining OP_QUEUE_SIZE value and thus module RAM usage.
 *
 * @note APP_TIMER_WITH_PROFILER must be enabled to use this functionality.
 *
 * @return Maximum number of events in queue observed so far.
 */
uint8_t app_timer_op_queue_utilization_get(void);

/**
 * @brief Function for pausing RTC activity which drives app_timer.
 *
 * @note This function can be used for debugging purposes to ensure
 *       that application is halted when entering a breakpoint.
 */
void app_timer_pause(void);

/**
 * @brief Function for resuming RTC activity which drives app_timer.
 *
 * @note This function can be used for debugging purposes to resume
 *       application activity.
 */
void app_timer_resume(void);

#ifdef __cplusplus
}
#endif

#endif // APP_TIMER_H__

/** @} */
