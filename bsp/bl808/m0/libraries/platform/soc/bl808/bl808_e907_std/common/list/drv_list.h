/**
 * @file drv_list.h
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#ifndef __DRV_LIST_H__
#define __DRV_LIST_H__

#include "string.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * container_of - return the member address of ptr, if the type of ptr is the
 * struct type.
 */
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

/**
 * Double List structure
 */
struct dlist_node {
    struct dlist_node *next; /**< point to next node. */
    struct dlist_node *prev; /**< point to prev node. */
};
typedef struct dlist_node dlist_t; /**< Type for lists. */

/**
 * @brief initialize a list
 *
 * @param l list to be initialized
 */
static inline void dlist_init(dlist_t *l)
{
    l->next = l->prev = l;
}

/**
 * @brief insert a node after a list
 *
 * @param l list to insert it
 * @param n new node to be inserted
 */
static inline void dlist_insert_after(dlist_t *l, dlist_t *n)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->prev = l;
}

/**
 * @brief insert a node before a list
 *
 * @param n new node to be inserted
 * @param l list to insert it
 */
static inline void dlist_insert_before(dlist_t *l, dlist_t *n)
{
    l->prev->next = n;
    n->prev = l->prev;

    l->prev = n;
    n->next = l;
}

/**
 * @brief remove node from list.
 * @param n the node to remove from the list.
 */
static inline void dlist_remove(dlist_t *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}

/**
 * @brief move node from list.
 * @param n the node to remove from the list.
 */
static inline void dlist_move_head(dlist_t *l, dlist_t *n)
{
    dlist_remove(n);
    dlist_insert_after(l, n);
}

/**
 * @brief move node from list.
 * @param n the node to remove from the list.
 */
static inline void dlist_move_tail(dlist_t *l, dlist_t *n)
{
    dlist_remove(n);
    dlist_insert_before(l, n);
}

/**
 * @brief tests whether a list is empty
 * @param l the list to test.
 */
static inline int dlist_isempty(const dlist_t *l)
{
    return l->next == l;
}

/**
 * @brief get the list length
 * @param l the list to get.
 */
static inline unsigned int dlist_len(const dlist_t *l)
{
    unsigned int len = 0;
    const dlist_t *p = l;

    while (p->next != l) {
        p = p->next;
        len++;
    }

    return len;
}

/**
 * @brief initialize a dlist object
 */
#define DLIST_OBJECT_INIT(object) \
    {                             \
        &(object), &(object)      \
    }
/**
 * @brief initialize a dlist object
 */
#define DLIST_DEFINE(list) \
    dlist_t list = { &(list), &(list) }

/**
 * dlist_first_entry - get the first element from a list
 * @ptr:    the list head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define dlist_first_entry(ptr, type, member) \
    dlist_entry((ptr)->next, type, member)
/**
 * dlist_first_entry_or_null - get the first element from a list
 * @ptr:    the list head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define dlist_first_entry_or_null(ptr, type, member) \
    (dlist_isempty(ptr) ? NULL : dlist_first_entry(ptr, type, member))

/**
 * @brief get the struct for this entry
 * @param node the entry point
 * @param type the type of structure
 * @param member the name of list in structure
 */
#define dlist_entry(node, type, member) \
    container_of(node, type, member)

/**
 * dlist_for_each - iterate over a list
 * @pos:    the dlist_t * to use as a loop cursor.
 * @head:   the head for your list.
 */
#define dlist_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * dlist_for_each_prev - iterate over a list
 * @pos:    the dlist_t * to use as a loop cursor.
 * @head:   the head for your list.
 */
#define dlist_for_each_prev(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
 * dlist_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:    the dlist_t * to use as a loop cursor.
 * @n:      another dlist_t * to use as temporary storage
 * @head:   the head for your list.
 */
#define dlist_for_each_safe(pos, n, head)                  \
    for (pos = (head)->next, n = pos->next; pos != (head); \
         pos = n, n = pos->next)

#define dlist_for_each_prev_safe(pos, n, head)             \
    for (pos = (head)->prev, n = pos->prev; pos != (head); \
         pos = n, n = pos->prev)
/**
 * dlist_for_each_entry  -   iterate over list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define dlist_for_each_entry(pos, head, member)                 \
    for (pos = dlist_entry((head)->next, typeof(*pos), member); \
         &pos->member != (head);                                \
         pos = dlist_entry(pos->member.next, typeof(*pos), member))

/**
 * dlist_for_each_entry_reverse  -   iterate over list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define dlist_for_each_entry_reverse(pos, head, member)         \
    for (pos = dlist_entry((head)->prev, typeof(*pos), member); \
         &pos->member != (head);                                \
         pos = dlist_entry(pos->member.prev, typeof(*pos), member))

/**
 * dlist_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:    the type * to use as a loop cursor.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define dlist_for_each_entry_safe(pos, n, head, member)          \
    for (pos = dlist_entry((head)->next, typeof(*pos), member),  \
        n = dlist_entry(pos->member.next, typeof(*pos), member); \
         &pos->member != (head);                                 \
         pos = n, n = dlist_entry(n->member.next, typeof(*n), member))

/**
 * dlist_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:    the type * to use as a loop cursor.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define dlist_for_each_entry_safe_reverse(pos, n, head, member)  \
    for (pos = dlist_entry((head)->prev, typeof(*pos), field),   \
        n = dlist_entry(pos->member.prev, typeof(*pos), member); \
         &pos->member != (head);                                 \
         pos = n, n = dlist_entry(pos->member.prev, typeof(*pos), member))

/**
 * Single List structure
 */
struct slist_node {
    struct slist_node *next; /**< point to next node. */
};
typedef struct slist_node slist_t; /**< Type for single list. */

/**
 * @brief initialize a single list
 *
 * @param l the single list to be initialized
 */
static inline void slist_init(slist_t *l)
{
    l->next = NULL;
}

static inline void slist_add_head(slist_t *l, slist_t *n)
{
    n->next = l->next;
    l->next = n;
}

static inline void slist_add_tail(slist_t *l, slist_t *n)
{
    while (l->next) {
        l = l->next;
    }

    /* append the node to the tail */
    l->next = n;
    n->next = NULL;
}

static inline void slist_insert(slist_t *l, slist_t *next, slist_t *n)
{
    if (!next) {
        slist_add_tail(next, l);
        return;
    }

    while (l->next) {
        if (l->next == next) {
            l->next = n;
            n->next = next;
        }

        l = l->next;
    }
}

static inline slist_t *slist_remove(slist_t *l, slist_t *n)
{
    /* remove slist head */
    while (l->next && l->next != n) {
        l = l->next;
    }

    /* remove node */
    if (l->next != (slist_t *)0) {
        l->next = l->next->next;
    }

    return l;
}

static inline unsigned int slist_len(const slist_t *l)
{
    unsigned int len = 0;
    const slist_t *list = l->next;

    while (list != NULL) {
        list = list->next;
        len++;
    }

    return len;
}

static inline unsigned int slist_contains(slist_t *l, slist_t *n)
{
    while (l->next) {
        if (l->next == n) {
            return 0;
        }

        l = l->next;
    }

    return 1;
}

static inline slist_t *slist_head(slist_t *l)
{
    return l->next;
}

static inline slist_t *slist_tail(slist_t *l)
{
    while (l->next) {
        l = l->next;
    }

    return l;
}

static inline slist_t *slist_next(slist_t *n)
{
    return n->next;
}

static inline int slist_isempty(slist_t *l)
{
    return l->next == NULL;
}

/**
 * @brief initialize a slist object
 */
#define SLIST_OBJECT_INIT(object) \
    {                             \
        NULL                      \
    }

/**
 * @brief initialize a slist object
 */
#define SLIST_DEFINE(slist) \
    slist_t slist = { NULL }

/**
 * @brief get the struct for this single list node
 * @param node the entry point
 * @param type the type of structure
 * @param member the name of list in structure
 */
#define slist_entry(node, type, member) \
    container_of(node, type, member)

/**
 * slist_first_entry - get the first element from a slist
 * @ptr:    the slist head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the slist_struct within the struct.
 *
 * Note, that slist is expected to be not empty.
 */
#define slist_first_entry(ptr, type, member) \
    slist_entry((ptr)->next, type, member)

/**
 * slist_tail_entry - get the tail element from a slist
 * @ptr:    the slist head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the slist_struct within the struct.
 *
 * Note, that slist is expected to be not empty.
 */
#define slist_tail_entry(ptr, type, member) \
    slist_entry(slist_tail(ptr), type, member)

/**
 * slist_first_entry_or_null - get the first element from a slist
 * @ptr:    the slist head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the slist_struct within the struct.
 *
 * Note, that slist is expected to be not empty.
 */
#define slist_first_entry_or_null(ptr, type, member) \
    (slist_isempty(ptr) ? NULL : slist_first_entry(ptr, type, member))

/**
 * slist_for_each - iterate over a single list
 * @pos:    the slist_t * to use as a loop cursor.
 * @head:   the head for your single list.
 */
#define slist_for_each(pos, head) \
    for (pos = (head)->next; pos != NULL; pos = pos->next)

#define slist_for_each_safe(pos, next, head)        \
    for (pos = (head)->next, next = pos->next; pos; \
         pos = next, next = pos->next)

/**
 * slist_for_each_entry  -   iterate over single list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your single list.
 * @member: the name of the list_struct within the struct.
 */
#define slist_for_each_entry(pos, head, member)                 \
    for (pos = slist_entry((head)->next, typeof(*pos), member); \
         &pos->member != (NULL);                                \
         pos = slist_entry(pos->member.next, typeof(*pos), member))

#define slist_for_each_entry_safe(pos, n, head, member)          \
    for (pos = slist_entry((head)->next, typeof(*pos), member),  \
        n = slist_entry(pos->member.next, typeof(*pos), member); \
         &pos->member != (NULL);                                 \
         pos = n, n = slist_entry(pos->member.next, typeof(*pos), member))

#ifdef __cplusplus
}
#endif

#endif