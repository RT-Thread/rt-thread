/**
 * \file
 *
 * \brief Events implementation.
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

#include <utils_event.h>
#include <utils_assert.h>
#include <string.h>

#define EVENT_WORD_BITS (sizeof(event_word_t) * 8)

static struct list_descriptor events;
static uint8_t                subscribed[EVENT_MASK_SIZE];

int32_t event_subscribe(struct event *const event, const event_id_t id, event_cb_t cb)
{
	/* get byte and bit number of the given event in the event mask */
	const uint8_t position = id >> 3;
	const uint8_t mask     = 1 << (id & 0x7);

	ASSERT(event && cb && (id < EVENT_MAX_AMOUNT));

	if (event->mask[position] & mask) {
		return ERR_NO_CHANGE; /* Already subscribed */
	}

	if (!is_list_element(&events, event)) {
		memset(event->mask, 0, EVENT_MASK_SIZE);
		list_insert_as_head(&events, event);
	}
	event->cb = cb;
	event->mask[position] |= mask;

	subscribed[position] |= mask;

	return ERR_NONE;
}

int32_t event_unsubscribe(struct event *const event, const event_id_t id)
{
	/* get byte and bit number of the given event in the event mask */
	const uint8_t       position = id >> 3;
	const uint8_t       mask     = 1 << (id & 0x7);
	const struct event *current;
	uint8_t             i;

	ASSERT(event && (id < EVENT_MAX_AMOUNT));

	if (!(event->mask[position] & mask)) {
		return ERR_NO_CHANGE; /* Already unsubscribed */
	}

	event->mask[position] &= ~mask;

	/* Check if there are more subscribers */
	for ((current = (const struct event *)list_get_head(&events)); current;
	     current = (const struct event *)list_get_next_element(current)) {
		if (current->mask[position] & mask) {
			break;
		}
	}
	if (!current) {
		subscribed[position] &= ~mask;
	}

	/* Remove event from the list. Can be unsave, document it! */
	for (i = 0; i < ARRAY_SIZE(event->mask); i++) {
		if (event->mask[i]) {
			return ERR_NONE;
		}
	}
	list_delete_element(&events, event);

	return ERR_NONE;
}

void event_post(const event_id_t id, const event_data_t data)
{
	/* get byte and bit number of the given event in the event mask */
	const uint8_t       position = id >> 3;
	const uint8_t       mask     = 1 << (id & 0x7);
	const struct event *current;

	ASSERT((id < EVENT_MAX_AMOUNT));

	if (!(subscribed[position] & mask)) {
		return; /* No subscribers */
	}

	/* Find all subscribers */
	for ((current = (const struct event *)list_get_head(&events)); current;
	     current = (const struct event *)list_get_next_element(current)) {
		if (current->mask[position] & mask) {
			current->cb(id, data);
		}
	}
}
