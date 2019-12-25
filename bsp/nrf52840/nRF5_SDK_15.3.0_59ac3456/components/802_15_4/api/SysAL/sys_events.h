/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
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
#ifndef SYS_EVENTS_H_INCLUDED
#define SYS_EVENTS_H_INCLUDED

#include <stddef.h>
#include "sys_queue.h"

/** @file
 * This file contains declarations of the Events API and necessary types. The Events feature is implemented
 * using the Queue functionality.
 *
 * @defgroup sys_events System events API
 * @ingroup sys_15_4
 * @{
 * @brief Module for declaring system events API.
 * @details The Events module defines some routines to subscribe/unsubscribe to/from system events. The events pool
 * can be extended by adding new events to the sys_event_id_t enumeration. The registered callbacks
 * can be called for an array of events. The callbacks can be called implicitly via posting the event by the
 * sys_event_post() routine.
 */

/**@brief   IDs of globally available events.
 *
 * @details Event IDs are system extension points that allow the user to implement
 *          specific processing of predefined set of events, occurring in different modules.
 */
typedef enum
{
    SYS_EVENT_FALLING_ASLEEP,      /**< Falling asleep event. */
    SYS_EVENT_WAKE_UP,             /**< Waking up event. */
    SYS_EVENT_OUT_OF_MEMORY,       /**< Out of memory event. */
    SYS_EVENT_MEMORY_FREED,        /**< Memory was freed up event. */

    /** \note The list of system events can be extended during the implementation phase. */

    /* The following event IDs are used only for unit testing */
    TST_EVENT_0,                   /**< Test event #0. */
    TST_EVENT_1,                   /**< Test event #1. */
    TST_EVENT_2,                   /**< Test event #2. */

#if (CONFIG_USE_SYS_TASK_NOTIFIER == 1)
    /** This event is posted when there are unhandled events available in
     * any of the schedulers.
     */
    SYS_EVENT_NEW_TASK,
#endif

    SYS_EVENTS_AMOUNT
} sys_event_id_t;


/**@brief   Prototype of user-implemented callback for processing an event.
 *
 * @details This callback is registered for the given event by a *_subscribe routine,
 *          and is then called by the system events engine, when this event occurs.
 *
 * @param[in]   p_data  Pointer to the data, specific for this event.
 */
typedef void (* sys_event_callback_t)(const void * p_data);


/**@brief   Event descriptor.
 *
 * @details This descriptor is used to subscribe/unsubscribe to/from the event.
 */
typedef struct
{
    /** Service field. */
    sys_queue_item_t      queue_item;

    /** ID of the event to which this callback is to be subscribed. */
    sys_event_id_t        event_id;

    /** Callback function which is to be called when this event occurs. */
    sys_event_callback_t  callback;
} sys_event_desc_t;


/**@brief Function for initializing the global events infrastructure.
 */
void sys_events_init(void);


/**@brief Function for subscribing to a system event.
 *
 * @param[in]   p_event_desc    Pointer to the event descriptor.
 */
void sys_event_subscribe(sys_event_desc_t * p_event_desc);


/**@brief Function for unsubscribing from a system event event.
 *
 * @param[in]   p_event_desc    Pointer to the event descriptor.
 */
void sys_event_unsubscribe(sys_event_desc_t * p_event_desc);


/**@brief Function for subscribing to a group of events.
 *
 * @param[in]   p_desc_array    Pointer to the array of event descriptors.
 * @param[in]   desc_amount     Amount of event descriptors in the array.
 */
void sys_events_array_subscribe(sys_event_desc_t * p_desc_array, size_t desc_amount);


/**@brief Function for unsubscribing from the group of events.
 *
 *
 * @param[in]   p_desc_array    Pointer to the array of event descriptors.
 * @param[in]   desc_amount     Amount of the event descriptors in the array.
 */
void sys_events_array_unsubscribe(sys_event_desc_t * p_desc_array, size_t desc_amount);


/**@brief Function for posting an event.
 *
 * @details This function is used to notify all the subscribers of the given events via 
 *          their callbacks, when the given event occurs.
 *
 * @param[in]   event_id    ID of the event to be posted.
 * @param[in]   p_data      Pointer to be passed to the event handlers' callbacks.
 */
void sys_event_post(sys_event_id_t event_id, const void * p_data);

/** @} */

#endif // SYS_EVENTS_H_INCLUDED
