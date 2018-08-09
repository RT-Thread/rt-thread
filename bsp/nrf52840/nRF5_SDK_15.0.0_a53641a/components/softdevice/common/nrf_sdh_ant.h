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

/**@file
 *
 * @defgroup nrf_sdh_ant ANT support in SoftDevice Handler
 * @{
 * @ingroup  nrf_sdh
 * @brief    This file contains the declarations of types and functions required for ANT stack support.
 */

#ifndef NRF_SDH_ANT_H__
#define NRF_SDH_ANT_H__

#include "ant_parameters.h"
#include "app_util.h"
#include "nrf_section_iter.h"
#include "sdk_errors.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_SDH_ANT_EVT_CHANNEL_FIELD_SIZE  1   //!< Size of the channel field in ANT stack event
#define NRF_SDH_ANT_EVT_EVENT_FIELD_SIZE    1   //!< Size of the event field in ANT stack event

/**@brief Size of the buffer provided to the ANT SoftDevice.
 * @hideinitializer
 */
#define NRF_SDH_ANT_BUF_SIZE    ANT_ENABLE_GET_REQUIRED_SPACE(                                      \
                                    NRF_SDH_ANT_TOTAL_CHANNELS_ALLOCATED,                           \
                                    NRF_SDH_ANT_ENCRYPTED_CHANNELS,                                 \
                                    NRF_SDH_ANT_BURST_QUEUE_SIZE,                                   \
                                    NRF_SDH_ANT_EVENT_QUEUE_SIZE)

/**@brief Size of the buffer provided to the ANT SoftDevice to receive ANT events. */
#define NRF_SDH_ANT_MESSAGE_SIZE ((CEIL_DIV(MESG_BUFFER_SIZE, sizeof(uint32_t))) * sizeof(uint32_t))

/**@brief Size of the buffer provided to the Events Scheduler to hold ANT events. */
#define NRF_SDH_ANT_EVT_BUF_SIZE ((CEIL_DIV(NRF_SDH_ANT_MESSAGE_SIZE +         \
                                     NRF_SDH_ANT_EVT_CHANNEL_FIELD_SIZE +      \
                                     NRF_SDH_ANT_EVT_EVENT_FIELD_SIZE,         \
                                     sizeof(uint32_t))) * sizeof(uint32_t))


#if !(defined(__LINT__))
/**@brief   Macro for registering an ANT observer. Modules that want to be
 *          notified about ANT events must register the handler using this macro.
 *
 * @details This macro places the observer in a section named "sdh_ant_observers".
 *
 * @param[in]   _name       Observer name.
 * @param[in]   _prio       Priority of the observer event handler.
 *                          The smaller the number, the higher the priority.
 * @param[in]   _handler    ANT event handler.
 * @param[in]   _context    Parameter to the event handler.
 * @hideinitializer
 */
#define NRF_SDH_ANT_OBSERVER(_name, _prio, _handler, _context)                                      \
STATIC_ASSERT(NRF_SDH_ANT_ENABLED, "NRF_SDH_ANT_ENABLED not set!");                                 \
STATIC_ASSERT(_prio < NRF_SDH_ANT_OBSERVER_PRIO_LEVELS, "Priority level unavailable.");             \
NRF_SECTION_SET_ITEM_REGISTER(sdh_ant_observers, _prio, static nrf_sdh_ant_evt_observer_t _name) =  \
{                                                                                                   \
    .handler   = _handler,                                                                          \
    .p_context = _context                                                                           \
}

/**@brief   Macro for registering an array of @ref nrf_sdh_ant_evt_observer_t.
 *          Modules that want to be notified about ANT events must register the handler using
 *          this macro.
 *
 * Each observer's handler will be dispatched an event with its relative context from @p _context.
 * This macro places the observer in a section named "sdh_ant_observers".
 *
 * @param[in]   _name       Observer name.
 * @param[in]   _prio       Priority of the observer event handler.
 *                          The smaller the number, the higher the priority.
 * @param[in]   _handler    ANT event handler.
 * @param[in]   _context    An array of parameters to the event handler.
 * @param[in]   _cnt        Number of observers to register.
 * @hideinitializer
 */
#define NRF_SDH_ANT_OBSERVERS(_name, _prio, _handler, _context, _cnt)                                    \
STATIC_ASSERT(NRF_SDH_ANT_ENABLED, "NRF_SDH_ANT_ENABLED not set!");                                      \
STATIC_ASSERT(_prio < NRF_SDH_ANT_OBSERVER_PRIO_LEVELS, "Priority level unavailable.");                  \
NRF_SECTION_SET_ITEM_REGISTER(sdh_ant_observers, _prio, static nrf_sdh_ant_evt_observer_t _name[_cnt]) = \
{                                                                                                        \
    MACRO_REPEAT_FOR(_cnt, HANDLER_SET, _handler, _context)                                              \
}

#if !(defined(DOXYGEN))
#define HANDLER_SET(_idx, _handler, _context)                                                       \
{                                                                                                   \
    .handler   = _handler,                                                                          \
    .p_context = _context[_idx],                                                                    \
},
#endif

#else // __LINT__

/* Swallow semicolons */
/*lint -save -esym(528, *) -esym(529, *) : Symbol not referenced. */
#define NRF_SDH_ANT_OBSERVER(A, B, C, D)     static int semicolon_swallow_##A
#define NRF_SDH_ANT_OBSERVERS(A, B, C, D, E) static int semicolon_swallow_##A
/*lint -restore */

#endif


/**@brief   ANT stack event. */
typedef struct
{
    ANT_MESSAGE message;    //!< ANT Message.
    uint8_t     channel;    //!< Channel number.
    uint8_t     event;      //!< Event code.
} ant_evt_t;

/**@brief   ANT stack event handler. */
typedef void (*nrf_sdh_ant_evt_handler_t)(ant_evt_t * p_ant_evt, void * p_context);

/**@brief   ANT event observer. */
typedef struct
{
    nrf_sdh_ant_evt_handler_t handler;      //!< ANT event handler.
    void *                    p_context;    //!< A parameter to the event handler.
} const nrf_sdh_ant_evt_observer_t;


/**@brief   Function for configuring and enabling the ANT stack.
 *
 * @details The function sets the channel configuration for the stack using the parameters
 *          provided in the @c sdk_config file. It also assigns a correspondingly large
 *          buffer as a static resource.
 */
ret_code_t nrf_sdh_ant_enable(void);

#ifdef __cplusplus
}
#endif

#endif // NRF_SDH_ANT_H__

/** @} */
