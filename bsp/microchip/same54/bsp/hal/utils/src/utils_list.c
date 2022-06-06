/**
 * \file
 *
 * \brief List functionality implementation.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <utils_list.h>
#include <utils_assert.h>

/**
 * \brief Check whether element belongs to list
 */
bool is_list_element(const struct list_descriptor *const list, const void *const element)
{
	struct list_element *it;
	for (it = list->head; it; it = it->next) {
		if (it == element) {
			return true;
		}
	}

	return false;
}

/**
 * \brief Insert an element as list head
 */
void list_insert_as_head(struct list_descriptor *const list, void *const element)
{
	ASSERT(!is_list_element(list, element));

	((struct list_element *)element)->next = list->head;
	list->head                             = (struct list_element *)element;
}

/**
 * \brief Insert an element after the given list element
 */
void list_insert_after(void *const after, void *const element)
{
	((struct list_element *)element)->next = ((struct list_element *)after)->next;
	((struct list_element *)after)->next   = (struct list_element *)element;
}

/**
 * \brief Insert an element at list end
 */
void list_insert_at_end(struct list_descriptor *const list, void *const element)
{
	struct list_element *it = list->head;

	ASSERT(!is_list_element(list, element));

	if (!list->head) {
		list->head                             = (struct list_element *)element;
		((struct list_element *)element)->next = NULL;
		return;
	}

	while (it->next) {
		it = it->next;
	}
	it->next                               = (struct list_element *)element;
	((struct list_element *)element)->next = NULL;
}

/**
 * \brief Removes list head
 */
void *list_remove_head(struct list_descriptor *const list)
{
	if (list->head) {
		struct list_element *tmp = list->head;

		list->head = list->head->next;
		return (void *)tmp;
	}

	return NULL;
}

/**
 * \brief Removes list element
 */
bool list_delete_element(struct list_descriptor *const list, const void *const element)
{
	if (!element) {
		return false;
	}

	if (list->head == element) {
		list->head = list->head->next;
		return true;
	} else {
		struct list_element *it = list->head;

		while (it && it->next != element) {
			it = it->next;
		}
		if (it) {
			it->next = ((struct list_element *)element)->next;
			return true;
		}
	}

	return false;
}

//@}
