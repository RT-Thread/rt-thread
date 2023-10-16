/**
 * \file
 *
 * \brief Events declaration.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef _UTILS_EVENT_H_INCLUDED
#define _UTILS_EVENT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <utils.h>
#include <utils_list.h>
#include <events.h>

/**
 * \brief The maximum amount of events
 */
#define EVENT_MAX_AMOUNT 8

/**
 * \brief The size of event mask used, it is EVENT_MAX_AMOUNT rounded up to the
 *        closest number divisible by 8.
 */
#define EVENT_MASK_SIZE (round_up(EVENT_MAX_AMOUNT, 8))

/**
 * \brief The type of event ID. IDs should start with 0 and be in numerical order.
 */
typedef uint8_t event_id_t;

/**
 * \brief The type of returned parameter. This type is big enough to contain
 *        pointer to data on any platform.
 */
typedef uintptr_t event_data_t;

/**
 * \brief The type of returned parameter. This type is big enough to contain
 *        pointer to data on any platform.
 */
typedef void (*event_cb_t)(event_id_t id, event_data_t data);

/**
 * \brief Event structure
 */
struct event {
	struct list_element elem;                  /*! The pointer to next event */
	uint8_t             mask[EVENT_MASK_SIZE]; /*! Mask of event IDs callback is called for */
	event_cb_t          cb;                    /*! Callback to be called when an event occurs */
};

/**
 * \brief Subscribe to event
 *
 * \param[in] event The pointer to event structure
 * \param[in] id The event ID to subscribe to
 * \param[in] cb The callback function to call when the given event occurs
 *
 * \return The status of subscription
 */
int32_t event_subscribe(struct event *const event, const event_id_t id, event_cb_t cb);

/**
 * \brief Remove event from subscription
 *
 * \param[in] event The pointer to event structure
 * \param[in] id The event ID to remove subscription from
 *
 * \return The status of subscription removing
 */
int32_t event_unsubscribe(struct event *const event, const event_id_t id);

/**
 * \brief Post event
 *
 * \param[in] id The event ID to post
 * \param[in] data The event data to be passed to event subscribers
 */
void event_post(const event_id_t id, const event_data_t data);

#ifdef __cplusplus
}
#endif

#endif /* _UTILS_EVENT_H_INCLUDED */
