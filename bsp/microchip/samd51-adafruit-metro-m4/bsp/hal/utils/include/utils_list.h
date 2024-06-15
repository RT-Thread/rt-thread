/**
 * \file
 *
 * \brief List declaration.
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

#ifndef _UTILS_LIST_H_INCLUDED
#define _UTILS_LIST_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup doc_driver_hal_utils_list
 *
 * @{
 */

#include <compiler.h>

/**
 * \brief List element type
 */
struct list_element {
	struct list_element *next;
};

/**
 * \brief List head type
 */
struct list_descriptor {
	struct list_element *head;
};

/**
 * \brief Reset list
 *
 * \param[in] list The pointer to a list descriptor
 */
static inline void list_reset(struct list_descriptor *const list)
{
	list->head = NULL;
}

/**
 * \brief Retrieve list head
 *
 * \param[in] list The pointer to a list descriptor
 *
 * \return A pointer to the head of the given list or NULL if the list is
 * empty
 */
static inline void *list_get_head(const struct list_descriptor *const list)
{
	return (void *)list->head;
}

/**
 * \brief Retrieve next list head
 *
 * \param[in] list The pointer to a list element
 *
 * \return A pointer to the next list element or NULL if there is not next
 * element
 */
static inline void *list_get_next_element(const void *const element)
{
	return element ? ((struct list_element *)element)->next : NULL;
}

/**
 * \brief Insert an element as list head
 *
 * \param[in] list The pointer to a list element
 * \param[in] element An element to insert to the given list
 */
void list_insert_as_head(struct list_descriptor *const list, void *const element);

/**
 * \brief Insert an element after the given list element
 *
 * \param[in] after An element to insert after
 * \param[in] element Element to insert to the given list
 */
void list_insert_after(void *const after, void *const element);

/**
 * \brief Insert an element at list end
 *
 * \param[in] after An element to insert after
 * \param[in] element Element to insert to the given list
 */
void list_insert_at_end(struct list_descriptor *const list, void *const element);

/**
 * \brief Check whether an element belongs to a list
 *
 * \param[in] list The pointer to a list
 * \param[in] element An element to check
 *
 * \return The result of checking
 * \retval true If the given element is an element of the given list
 * \retval false Otherwise
 */
bool is_list_element(const struct list_descriptor *const list, const void *const element);

/**
 * \brief Removes list head
 *
 * This function removes the list head and sets the next element after the list
 * head as a new list head.
 *
 * \param[in] list The pointer to a list
 *
 * \return The pointer to the new list head of NULL if the list head is NULL
 */
void *list_remove_head(struct list_descriptor *const list);

/**
 * \brief Removes the list element
 *
 * \param[in] list The pointer to a list
 * \param[in] element An element to remove
 *
 * \return The result of element removing
 * \retval true The given element is removed from the given list
 * \retval false The given element is not an element of the given list
 */
bool list_delete_element(struct list_descriptor *const list, const void *const element);

/**@}*/

#ifdef __cplusplus
}
#endif
#endif /* _UTILS_LIST_H_INCLUDED */
