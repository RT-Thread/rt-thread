/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Simple doubly-linked list library.
 *
 * Adapted from Xvisor source file libs/include/libs/list.h
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SBI_LIST_H__
#define __SBI_LIST_H__

#include <sbi/sbi_types.h>

#define SBI_LIST_POISON_PREV	0xDEADBEEF
#define SBI_LIST_POISON_NEXT	0xFADEBABE

struct sbi_dlist {
	struct sbi_dlist *next, *prev;
};

#define SBI_LIST_HEAD_INIT(__lname)	{ &(__lname), &(__lname) }

#define SBI_LIST_HEAD(_lname)	\
struct sbi_dlist _lname = SBI_LIST_HEAD_INIT(_lname)

#define SBI_INIT_LIST_HEAD(ptr)	\
do { \
	(ptr)->next = ptr; (ptr)->prev = ptr; \
} while (0);

static inline void __sbi_list_add(struct sbi_dlist *new,
				  struct sbi_dlist *prev,
				  struct sbi_dlist *next)
{
	new->prev = prev;
	new->next = next;
	prev->next = new;
	next->prev = new;
}

/**
 * Adds the new node after the given head.
 * @param new New node that needs to be added to list.
 * @param head List head after which the "new" node should be added.
 * Note: the new node is added after the head.
 */
static inline void sbi_list_add(struct sbi_dlist *new, struct sbi_dlist *head)
{
	__sbi_list_add(new, head, head->next);
}

/**
 * Adds a node at the tail where tnode points to tail node.
 * @param new The new node to be added before tail.
 * @param tnode The current tail node.
 * Note: the new node is added before tail node.
 */
static inline void sbi_list_add_tail(struct sbi_dlist *new,
				     struct sbi_dlist *tnode)
{
	__sbi_list_add(new, tnode->prev, tnode);
}

static inline void __sbi_list_del(struct sbi_dlist *prev,
				  struct sbi_dlist *next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void __sbi_list_del_entry(struct sbi_dlist *entry)
{
	__sbi_list_del(entry->prev, entry->next);
}

/**
 * Deletes a given entry from list.
 * @param node Node to be deleted.
 */
static inline void sbi_list_del(struct sbi_dlist *entry)
{
	__sbi_list_del(entry->prev, entry->next);
	entry->next = (void *)SBI_LIST_POISON_NEXT;
	entry->prev = (void *)SBI_LIST_POISON_PREV;
}

/**
 * Deletes entry from list and reinitialize it.
 * @param entry the element to delete from the list.
 */
static inline void sbi_list_del_init(struct sbi_dlist *entry)
{
	__sbi_list_del_entry(entry);
	SBI_INIT_LIST_HEAD(entry);
}

/**
 * Get the struct for this entry
 * @param ptr the &struct list_head pointer.
 * @param type the type of the struct this is embedded in.
 * @param member the name of the list_struct within the struct.
 */
#define sbi_list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * Get the first element from a list
 * @param ptr the list head to take the element from.
 * @param type the type of the struct this is embedded in.
 * @param member the name of the list_struct within the struct.
 *
 * Note: that list is expected to be not empty.
 */
#define sbi_list_first_entry(ptr, type, member) \
	sbi_list_entry((ptr)->next, type, member)

/**
 * Get the last element from a list
 * @param ptr the list head to take the element from.
 * @param type the type of the struct this is embedded in.
 * @param member the name of the list_head within the struct.
 *
 * Note: that list is expected to be not empty.
 */
#define sbi_list_last_entry(ptr, type, member) \
	sbi_list_entry((ptr)->prev, type, member)

/**
 * Iterate over a list
 * @param pos the &struct list_head to use as a loop cursor.
 * @param head the head for your list.
 */
#define sbi_list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * Iterate over list of given type
 * @param pos the type * to use as a loop cursor.
 * @param head the head for your list.
 * @param member the name of the list_struct within the struct.
 */
#define sbi_list_for_each_entry(pos, head, member) \
	for (pos = sbi_list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = sbi_list_entry(pos->member.next, typeof(*pos), member))

#endif
