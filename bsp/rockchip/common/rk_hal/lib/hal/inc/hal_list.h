/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#ifndef _HAL_LIST_H_
#define _HAL_LIST_H_

/***************************** Structure Definition **************************/

/** double list struct */
struct HAL_LIST_NODE {
    struct HAL_LIST_NODE *next;
    struct HAL_LIST_NODE *prev;
};

typedef struct HAL_LIST_NODE HAL_LIST;

/***************************** Function Declare ******************************/
/**
 * @brief cast a member of a structure out to the containing structure
 * @param ptr:    the pointer to the member.
 * @param type:   the type of the container struct this is embedded in.
 * @param member: the name of the member within the struct.
 */
#define HAL_CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

/**
 * @brief initialize a list object
 * @param object: object itself.
 */
#define HAL_LIST_OBJECT_INIT(object) { &(object), &(object) }

#define HAL_LIST_HEAD_INIT(name) { &(name), &(name) }

/**
 * @brief initialize a list head
 * @param name: list name..
 */
#define HAL_LIST_HEAD(name) \
    struct HAL_LIST_NODE name = HAL_LIST_HEAD_INIT(name)

/**
 * @brief initialize a list
 * @param l: list to be initialized
 */
__STATIC_INLINE void HAL_LIST_Init(HAL_LIST *l)
{
    l->next = l->prev = l;
}

/**
 * @brief insert a node after a list
 * @param l: list to insert it
 * @param n: new node to be inserted
 */
__STATIC_INLINE void HAL_LIST_InsertAfter(HAL_LIST *l, HAL_LIST *n)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->prev = l;
}

/**
 * @brief insert a node before a list
 * @param n: new node to be inserted
 * @param l: list to insert it
 */
__STATIC_INLINE void HAL_LIST_InsertBefore(HAL_LIST *l, HAL_LIST *n)
{
    l->prev->next = n;
    n->prev = l->prev;

    l->prev = n;
    n->next = l;
}

/**
 * @brief remove node from list.
 * @param n: the node to remove from the list.
 */
__STATIC_INLINE void HAL_LIST_Remove(HAL_LIST *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}

/**
 * @brief tests whether a list is empty
 * @param l: the list to test.
 */
__STATIC_INLINE int HAL_LIST_IsEmpty(const HAL_LIST *l)
{
    return l->next == l;
}

/**
 * @brief get the list length
 * @param l: the list to get.
 */
__STATIC_INLINE uint32_t HAL_LIST_Len(const HAL_LIST *l)
{
    uint32_t len = 0;
    const HAL_LIST *p = l;

    while (p->next != l) {
        p = p->next;
        len++;
    }

    return len;
}

/**
 * @brief get the struct for this entry
 * @param node: the entry point
 * @param type: the type of structure
 * @param member: the name of list in structure
 */
#define HAL_LIST_ENTRY(node, type, member) \
    HAL_CONTAINER_OF(node, type, member)

/**
 * @brief iterate over a list
 * @param pos:  the rt_list_t * to use as a loop cursor.
 * @param head: the head for your list.
 */
#define HAL_LIST_FOR_EACH(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * @brief iterate over a list safe against removal of list entry
 * @param pos:  the rt_list_t * to use as a loop cursor.
 * @param n:    another rt_list_t * to use as temporary storage
 * @param head: the head for your list.
 */
#define HAL_LIST_FOR_EACH_SAFE(pos, n, head)               \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)

/**
 * @brief   iterate over list of given type
 * @param   pos:    the type * to use as a loop cursor.
 * @param   head:   the head for your list.
 * @param   member: the name of the list_struct within the struct.
 */
#define HAL_LIST_FOR_EACH_ENTRY(pos, head, member)                     \
    for (pos = HAL_LIST_ENTRY((head)->next, __typeof__(*pos), member); \
         &pos->member != (head);                                       \
         pos = HAL_LIST_ENTRY(pos->member.next, __typeof__(*pos), member))

/**
 * @brief   iterate over list of given type safe against removal of list entry
 * @param   pos:    the type * to use as a loop cursor.
 * @param   n:      another type * to use as temporary storage
 * @param   head:   the head for your list.
 * @param   member: the name of the list_struct within the struct.
 */
#define HAL_LIST_FOR_EACH_ENTRY_SAFE(pos, n, head, member)               \
    for (pos = HAL_LIST_ENTRY((head)->next, __typeof__(*pos), member),   \
         n = HAL_LIST_ENTRY(pos->member.next, __typeof__(*pos), member); \
         &pos->member != (head);                                         \
         pos = n, n = HAL_LIST_ENTRY(n->member.next, __typeof__(*n), member))

/**
 * @brief   get the first element from a list
 * @param   ptr:    the list head to take the element from.
 * @param   type:   the type of the struct this is embedded in.
 * @param   member: the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define HAL_LIST_FIRST_ENTRY(ptr, type, member) \
    HAL_LIST_ENTRY((ptr)->next, type, member)

#endif
