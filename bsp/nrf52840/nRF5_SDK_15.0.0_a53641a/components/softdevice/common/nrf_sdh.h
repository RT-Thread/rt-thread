/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
 * @defgroup nrf_sdh SoftDevice Handler
 * @{
 * @ingroup  app_common
 * @brief    API for initializing and disabling the SoftDevice.
 */

#ifndef NRF_SDH_H__
#define NRF_SDH_H__

#include <stdbool.h>
#include "sdk_config.h"
#include "sdk_errors.h"
#include "nrf_section_iter.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Softdevice Handler dispatch models
 * @{
 * @ingroup  nrf_sdh */

/**@brief   SoftDevice events are passed to the application from the interrupt context. */
#define NRF_SDH_DISPATCH_MODEL_INTERRUPT  0

/**@brief   SoftDevice events are passed to the application using @ref app_scheduler.
 *
 * @note    @ref app_scheduler must be initialized before enabling the SoftDevice handler.
 */
#define NRF_SDH_DISPATCH_MODEL_APPSH      1

/**@brief   SoftDevice events are polled manually using @ref nrf_sdh_evts_poll().
 *
 * @note    In this mode, a user application can also implement SD_EVT_IRQHandler() to receive a
 *          notification about incoming events.
 */
#define NRF_SDH_DISPATCH_MODEL_POLLING    2

/** @} */

/**
 * @name SoftDevice Handler state change requests
 * @{
 * @ingroup  nrf_sdh */

/**@brief   SoftDevice Handler state requests. */
typedef enum
{
    NRF_SDH_EVT_ENABLE_REQUEST,     //!< Request to enable the SoftDevice.
    NRF_SDH_EVT_DISABLE_REQUEST,    //!< Request to disable the SoftDevice.
} nrf_sdh_req_evt_t;

/**@brief   SoftDevice Handler state request handler.
 *
 * @retval  true    If ready for the SoftDevice to change state.
 * @retval  false   If not ready for the SoftDevice to change state.
 *                  If false is returned, the state change is aborted.
 */
typedef bool (*nrf_sdh_req_evt_handler_t)(nrf_sdh_req_evt_t request, void * p_context);

/**@brief   SoftDevice Handler state request observer. */
typedef struct
{
    nrf_sdh_req_evt_handler_t handler;      //!< Request handler.
    void *                    p_context;    //!< A parameter to the handler function.
} const nrf_sdh_req_observer_t;

/**@brief   Macro for registering a SoftDevice state change request observer.
 *
 * An observer of SoftDevice state change requests receives requests to change the state of the
 * SoftDevice from enabled to disabled and vice versa. These requests may or may not be acknowledged
 * by the observer, depending on the value returned by its request handler function. Thus, a
 * request observer has the capability to defer the change of state of the SoftDevice. If it does
 * so, it has the responsibility to call @ref nrf_sdh_request_continue when it is ready to let the
 * SoftDevice change its state. If such capability is not necessary and you only need to be informed
 * about changes of the SoftDevice state, use the @ref NRF_SDH_STATE_OBSERVER macro instead.
 *
 * @note    This macro places the observer in a section named "sdh_req_observers".
 *
 * @param[in]   _observer   Name of the observer.
 * @param[in]   _prio       Priority of the observer's event handler.
 *                          The smaller the number, the higher the priority.
 * @hideinitializer
 */
#define NRF_SDH_REQUEST_OBSERVER(_observer, _prio)                                                  \
STATIC_ASSERT(NRF_SDH_ENABLED, "NRF_SDH_ENABLED not set!");                                         \
STATIC_ASSERT(_prio < NRF_SDH_REQ_OBSERVER_PRIO_LEVELS, "Priority level unavailable.");             \
/*lint -esym(528,*_observer) -esym(529,*_observer) : Symbol not referenced. */                      \
NRF_SECTION_SET_ITEM_REGISTER(sdh_req_observers, _prio, nrf_sdh_req_observer_t const _observer)

/** @} */

/**
 * @name SoftDevice Handler state events
 * @{
 * @ingroup  nrf_sdh */

/**@brief   SoftDevice Handler state events. */
typedef enum
{
    NRF_SDH_EVT_STATE_ENABLE_PREPARE,   //!< SoftDevice is going to be enabled.
    NRF_SDH_EVT_STATE_ENABLED,          //!< SoftDevice is enabled.
    NRF_SDH_EVT_STATE_DISABLE_PREPARE,  //!< SoftDevice is going to be disabled.
    NRF_SDH_EVT_STATE_DISABLED,         //!< SoftDevice is disabled.
} nrf_sdh_state_evt_t;

/**@brief   SoftDevice Handler state event handler. */
typedef void (*nrf_sdh_state_evt_handler_t)(nrf_sdh_state_evt_t state, void * p_context);

/**@brief   SoftDevice Handler state observer. */
typedef struct
{
    nrf_sdh_state_evt_handler_t   handler;      //!< State event handler.
    void                        * p_context;    //!< A parameter to the event handler.
} const nrf_sdh_state_observer_t;

/**@brief   Macro for registering a SoftDevice state observer.
 *
 * A SoftDevice state observer receives events when the SoftDevice state has changed or is
 * about to change. These events are only meant to inform the state observer, which, contrary
 * to a state change request observer, does not have the capability to defer the change of state.
 * If such capability is required, use the @ref NRF_SDH_REQUEST_OBSERVER macro instead.
 *
 *  This macro places the observer in a section named "sdh_state_observers".
 *
 * @param[in]   _observer   Name of the observer.
 * @param[in]   _prio       Priority of the observer's event handler.
 *                          The smaller the number, the higher the priority.
 * @hideinitializer
 */
#define NRF_SDH_STATE_OBSERVER(_observer, _prio)                                                           \
STATIC_ASSERT(NRF_SDH_ENABLED, "NRF_SDH_ENABLED not set!");                                                \
STATIC_ASSERT(_prio < NRF_SDH_STATE_OBSERVER_PRIO_LEVELS, "Priority level unavailable.");                  \
/*lint -esym(528,*_observer) -esym(529,*_observer) : Symbol not referenced. */                             \
NRF_SECTION_SET_ITEM_REGISTER(sdh_state_observers, _prio, static nrf_sdh_state_observer_t const _observer)

/** @} */

/**
 * @name SoftDevice stack events
 * @{
 * @ingroup  nrf_sdh */

/**@brief   SoftDevice stack event handler. */
typedef void (*nrf_sdh_stack_evt_handler_t)(void * p_evt);

/**@brief   SoftDevice stack event observer. */
typedef struct
{
    nrf_sdh_stack_evt_handler_t handler;    //!< SoftDevice event handler.
    void *                      p_context;  //!< A parameter to the event handler.
} const nrf_sdh_stack_observer_t;

/**@brief   Macro for registering a SoftDevice stack events observer.
 *
 * A SoftDevice stack event observer receives all events from the SoftDevice. These events can be
 * either BLE, ANT, or SoC events. If you need to receive BLE, ANT, or SoC events separately, use the
 * @ref NRF_SDH_BLE_OBSERVER, @ref NRF_SDH_ANT_OBSERVER, or @ref NRF_SDH_SOC_OBSERVER macros
 * respectively.
 *
 * @note    This macro places the observer in a section named "sdh_stack_observers".
 *
 * @param[in]   _observer   Name of the observer.
 * @param[in]   _prio       Priority of the observer's event handler.
 *                          The smaller the number, the higher the priority.
 ** @hideinitializer
 */
#define NRF_SDH_STACK_OBSERVER(_observer, _prio)                                                          \
STATIC_ASSERT(NRF_SDH_ENABLED, "NRF_SDH_ENABLED not set!");                                               \
STATIC_ASSERT(_prio < NRF_SDH_STACK_OBSERVER_PRIO_LEVELS, "Priority level unavailable.");                 \
/*lint -esym(528,*_observer) -esym(529,*_observer) : Symbol not referenced. */                            \
NRF_SECTION_SET_ITEM_REGISTER(sdh_stack_observers, _prio, static nrf_sdh_stack_observer_t const _observer)

/** @} */

/**@brief   Function for requesting to enable the SoftDevice.
 *
 * This function issues a @ref NRF_SDH_EVT_ENABLE_REQUEST request to all observers that
 * were registered using the @ref NRF_SDH_REQUEST_OBSERVER macro. The observers may or
 * may not acknowledge the request. If all observers acknowledge the request, the
 * SoftDevice will be enabled. Otherwise, the process will be stopped and the observers
 * that did not acknowledge have the responsibility to restart it by calling
 * @ref nrf_sdh_request_continue when they are ready for the SoftDevice to change state.
 *
 * @retval  NRF_SUCCESS                 The process is started.
 * @retval  NRF_ERROR_INVALID_STATE     The SoftDevice is already enabled.
 */
ret_code_t nrf_sdh_enable_request(void);


/**@brief   Function for requesting to disable the SoftDevice.
 *
 * This function issues a @ref NRF_SDH_EVT_DISABLE_REQUEST request to all observers that
 * were registered using the @ref NRF_SDH_REQUEST_OBSERVER macro. The observers may or
 * may not acknowledge the request. If all observers acknowledge the request, the
 * SoftDevice will be disabled. Otherwise, the process will be stopped and the observers
 * that did not acknowledge have the responsibility to restart it by calling
 * @ref nrf_sdh_request_continue when they are ready for the SoftDevice to change state.
 *
 * @retval  NRF_SUCCESS                 The process is started.
 * @retval  NRF_ERROR_INVALID_STATE     The SoftDevice is already disabled.
 */
ret_code_t nrf_sdh_disable_request(void);


/**@brief   Function for restarting the SoftDevice Enable/Disable process.
 *
 * Modules which did not acknowledge a @ref NRF_SDH_EVT_ENABLE_REQUEST or
 * @ref NRF_SDH_EVT_DISABLE_REQUEST request must call this function to restart the
 * SoftDevice state change process.
 *
 * @retval  NRF_SUCCESS                 The process is restarted.
 * @retval  NRF_ERROR_INVALID_STATE     No state change request was pending.
 */
ret_code_t nrf_sdh_request_continue(void);


/**@brief   Function for retrieving the SoftDevice state.
 *
 * @retval  true    If the SoftDevice is enabled.
 * @retval  false   If the SoftDevice is disabled.
 */
bool nrf_sdh_is_enabled(void);


/**@brief   Function for stopping the incoming stack events.
 *
 * This function disables the SoftDevice interrupt. To resume polling for events,
 * call @ref nrf_sdh_resume.
 */
void nrf_sdh_suspend(void);


/**@brief   Function for resuming polling incoming events from the SoftDevice. */
void nrf_sdh_resume(void);


/**@brief   Function for retrieving the information about the module state.
 *
 * @retval  true    The SoftDevice handler is paused, and it will not fetch events from the stack.
 * @retval  false   The SoftDevice handler is running, and it will fetch and dispatch events from
 *                  the stack to the registered stack observers.
 */
bool nrf_sdh_is_suspended(void);


/**@brief   Function for polling stack events from the SoftDevice.
 *
 * The events are passed to the application using the registered event handlers.
 *
 * @note    @ref NRF_SDH_DISPATCH_MODEL_POLLING must be selected to use this function.
 */
void nrf_sdh_evts_poll(void);


#ifdef __cplusplus
}
#endif

#endif // NRF_SDH_H__

/** @} */
