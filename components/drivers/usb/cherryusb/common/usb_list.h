/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_LIST_H
#define USB_LIST_H

#include <string.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * usb_container_of - return the member address of ptr, if the type of ptr is the
 * struct type.
 */
#define usb_container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

/**
 * Single List structure
 */
struct usb_slist_node {
    struct usb_slist_node *next; /**< point to next node. */
};
typedef struct usb_slist_node usb_slist_t; /**< Type for single list. */

/**
 * @brief initialize a single list
 *
 * @param l the single list to be initialized
 */
static inline void usb_slist_init(usb_slist_t *l)
{
    l->next = NULL;
}

static inline void usb_slist_add_head(usb_slist_t *l, usb_slist_t *n)
{
    n->next = l->next;
    l->next = n;
}

static inline void usb_slist_add_tail(usb_slist_t *l, usb_slist_t *n)
{
    usb_slist_t *tmp = l;

    while (tmp->next) {
        tmp = tmp->next;
    }

    /* append the node to the tail */
    tmp->next = n;
    n->next = NULL;
}

static inline void usb_slist_insert(usb_slist_t *l, usb_slist_t *next, usb_slist_t *n)
{
    if (!next) {
        usb_slist_add_tail(next, l);
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

static inline usb_slist_t *usb_slist_remove(usb_slist_t *l, usb_slist_t *n)
{
    usb_slist_t *tmp = l;
    /* remove slist head */
    while (tmp->next && tmp->next != n) {
        tmp = tmp->next;
    }

    /* remove node */
    if (tmp->next != (usb_slist_t *)0) {
        tmp->next = tmp->next->next;
    }

    return l;
}

static inline unsigned int usb_slist_len(const usb_slist_t *l)
{
    unsigned int len = 0;
    const usb_slist_t *list = l->next;

    while (list != NULL) {
        list = list->next;
        len++;
    }

    return len;
}

static inline unsigned int usb_slist_contains(usb_slist_t *l, usb_slist_t *n)
{
    while (l->next) {
        if (l->next == n) {
            return 0;
        }

        l = l->next;
    }

    return 1;
}

static inline usb_slist_t *usb_slist_head(usb_slist_t *l)
{
    return l->next;
}

static inline usb_slist_t *usb_slist_tail(usb_slist_t *l)
{
    while (l->next) {
        l = l->next;
    }

    return l;
}

static inline usb_slist_t *usb_slist_next(usb_slist_t *n)
{
    return n->next;
}

static inline int usb_slist_isempty(usb_slist_t *l)
{
    return l->next == NULL;
}

/**
 * @brief initialize a slist object
 */
#define USB_SLIST_OBJECT_INIT(object) \
    {                                 \
        NULL                          \
    }

/**
 * @brief initialize a slist object
 */
#define USB_SLIST_DEFINE(slist) \
    usb_slist_t slist = { NULL }

/**
 * @brief get the struct for this single list node
 * @param node the entry point
 * @param type the type of structure
 * @param member the name of list in structure
 */
#define usb_slist_entry(node, type, member) \
    usb_container_of(node, type, member)

/**
 * usb_slist_first_entry - get the first element from a slist
 * @ptr:    the slist head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the slist_struct within the struct.
 *
 * Note, that slist is expected to be not empty.
 */
#define usb_slist_first_entry(ptr, type, member) \
    usb_slist_entry((ptr)->next, type, member)

/**
 * usb_slist_tail_entry - get the tail element from a slist
 * @ptr:    the slist head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the slist_struct within the struct.
 *
 * Note, that slist is expected to be not empty.
 */
#define usb_slist_tail_entry(ptr, type, member) \
    usb_slist_entry(usb_slist_tail(ptr), type, member)

/**
 * usb_slist_first_entry_or_null - get the first element from a slist
 * @ptr:    the slist head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the slist_struct within the struct.
 *
 * Note, that slist is expected to be not empty.
 */
#define usb_slist_first_entry_or_null(ptr, type, member) \
    (usb_slist_isempty(ptr) ? NULL : usb_slist_first_entry(ptr, type, member))

/**
 * usb_slist_for_each - iterate over a single list
 * @pos:    the usb_slist_t * to use as a loop cursor.
 * @head:   the head for your single list.
 */
#define usb_slist_for_each(pos, head) \
    for (pos = (head)->next; pos != NULL; pos = pos->next)

#define usb_slist_for_each_safe(pos, next, head)    \
    for (pos = (head)->next, next = pos->next; pos; \
         pos = next, next = pos->next)

/**
 * usb_slist_for_each_entry  -   iterate over single list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your single list.
 * @member: the name of the list_struct within the struct.
 */
#define usb_slist_for_each_entry(pos, head, member)                 \
    for (pos = usb_slist_entry((head)->next, typeof(*pos), member); \
         &pos->member != (NULL);                                    \
         pos = usb_slist_entry(pos->member.next, typeof(*pos), member))

#define usb_slist_for_each_entry_safe(pos, n, head, member)          \
    for (pos = usb_slist_entry((head)->next, typeof(*pos), member),  \
        n = usb_slist_entry(pos->member.next, typeof(*pos), member); \
         &pos->member != (NULL);                                     \
         pos = n, n = usb_slist_entry(pos->member.next, typeof(*pos), member))

/**
 * Double List structure
 */
struct usb_dlist_node {
    struct usb_dlist_node *next; /**< point to next node. */
    struct usb_dlist_node *prev; /**< point to prev node. */
};
typedef struct usb_dlist_node usb_dlist_t; /**< Type for lists. */

/**
 * @brief initialize a list
 *
 * @param l list to be initialized
 */
static inline void usb_dlist_init(usb_dlist_t *l)
{
    l->next = l->prev = l;
}

/**
 * @brief insert a node after a list
 *
 * @param l list to insert it
 * @param n new node to be inserted
 */
static inline void usb_dlist_insert_after(usb_dlist_t *l, usb_dlist_t *n)
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
static inline void usb_dlist_insert_before(usb_dlist_t *l, usb_dlist_t *n)
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
static inline void usb_dlist_remove(usb_dlist_t *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}

/**
 * @brief move node from list.
 * @param n the node to remove from the list.
 */
static inline void usb_dlist_move_head(usb_dlist_t *l, usb_dlist_t *n)
{
    usb_dlist_remove(n);
    usb_dlist_insert_after(l, n);
}

/**
 * @brief move node from list.
 * @param n the node to remove from the list.
 */
static inline void usb_dlist_move_tail(usb_dlist_t *l, usb_dlist_t *n)
{
    usb_dlist_remove(n);
    usb_dlist_insert_before(l, n);
}

/**
 * @brief tests whether a list is empty
 * @param l the list to test.
 */
static inline int usb_dlist_isempty(const usb_dlist_t *l)
{
    return l->next == l;
}

/**
 * @brief get the list length
 * @param l the list to get.
 */
static inline unsigned int usb_dlist_len(const usb_dlist_t *l)
{
    unsigned int len = 0;
    const usb_dlist_t *p = l;

    while (p->next != l) {
        p = p->next;
        len++;
    }

    return len;
}

/**
 * @brief initialize a dlist object
 */
#define USB_DLIST_OBJECT_INIT(object) \
    {                                 \
        &(object), &(object)          \
    }
/**
 * @brief initialize a dlist object
 */
#define USB_DLIST_DEFINE(list) \
    usb_dlist_t list = { &(list), &(list) }

/**
 * @brief get the struct for this entry
 * @param node the entry point
 * @param type the type of structure
 * @param member the name of list in structure
 */
#define usb_dlist_entry(node, type, member) \
    usb_container_of(node, type, member)

/**
 * dlist_first_entry - get the first element from a list
 * @ptr:    the list head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define usb_dlist_first_entry(ptr, type, member) \
    usb_dlist_entry((ptr)->next, type, member)
/**
 * dlist_first_entry_or_null - get the first element from a list
 * @ptr:    the list head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define usb_dlist_first_entry_or_null(ptr, type, member) \
    (usb_dlist_isempty(ptr) ? NULL : usb_dlist_first_entry(ptr, type, member))

/**
 * usb_dlist_for_each - iterate over a list
 * @pos:    the usb_dlist_t * to use as a loop cursor.
 * @head:   the head for your list.
 */
#define usb_dlist_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * usb_dlist_for_each_prev - iterate over a list
 * @pos:    the dlist_t * to use as a loop cursor.
 * @head:   the head for your list.
 */
#define usb_dlist_for_each_prev(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
 * usb_dlist_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:    the dlist_t * to use as a loop cursor.
 * @n:      another dlist_t * to use as temporary storage
 * @head:   the head for your list.
 */
#define usb_dlist_for_each_safe(pos, n, head)              \
    for (pos = (head)->next, n = pos->next; pos != (head); \
         pos = n, n = pos->next)

#define usb_dlist_for_each_prev_safe(pos, n, head)         \
    for (pos = (head)->prev, n = pos->prev; pos != (head); \
         pos = n, n = pos->prev)
/**
 * usb_dlist_for_each_entry  -   iterate over list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define usb_dlist_for_each_entry(pos, head, member)                 \
    for (pos = usb_dlist_entry((head)->next, typeof(*pos), member); \
         &pos->member != (head);                                    \
         pos = usb_dlist_entry(pos->member.next, typeof(*pos), member))

/**
 * usb_usb_dlist_for_each_entry_reverse  -   iterate over list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define usb_dlist_for_each_entry_reverse(pos, head, member)         \
    for (pos = usb_dlist_entry((head)->prev, typeof(*pos), member); \
         &pos->member != (head);                                    \
         pos = usb_dlist_entry(pos->member.prev, typeof(*pos), member))

/**
 * usb_usb_dlist_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:    the type * to use as a loop cursor.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define usb_dlist_for_each_entry_safe(pos, n, head, member)          \
    for (pos = usb_dlist_entry((head)->next, typeof(*pos), member),  \
        n = usb_dlist_entry(pos->member.next, typeof(*pos), member); \
         &pos->member != (head);                                     \
         pos = n, n = usb_dlist_entry(n->member.next, typeof(*n), member))

/**
 * usb_usb_dlist_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:    the type * to use as a loop cursor.
 * @n:      another type * to use as temporary storage
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define usb_dlist_for_each_entry_safe_reverse(pos, n, head, member)  \
    for (pos = usb_dlist_entry((head)->prev, typeof(*pos), field),   \
        n = usb_dlist_entry(pos->member.prev, typeof(*pos), member); \
         &pos->member != (head);                                     \
         pos = n, n = usb_dlist_entry(pos->member.prev, typeof(*pos), member))

#ifdef __cplusplus
}
#endif

#endif /* USB_LIST_H */
