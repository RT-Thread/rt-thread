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
#ifndef SYS_LIST_H_INCLUDED
#define SYS_LIST_H_INCLUDED

/** @file
 * This file contains declarations of the doubly linked list primitives and necessary types.
 * This implementation is Linux-proven and used in the memory management module.
 *
 * @defgroup sys_list Doubly linked list API.
 * @ingroup sys_15_4
 * @{
 * @brief Module to declare the doubly linked list API.
 */

/**
 * Internal list "head" struct.
 */
struct sys_list_head
{
    struct sys_list_head * next;
    struct sys_list_head * prev;
};

typedef struct sys_list_head sys_list_head_t;


/**
 * @brief Initializes a list by variable name.
 * @warning this macro assumes that a list "head" (sys_list_head_t) variable
 * with name \a name is already created.
 *
 * @param[inout] name The "head" struct name.
 */
#define LIST_HEAD_INIT(name) { &(name), &(name) }

/**
 * @brief Defines and initializes a new list.
 * @details A call to this macro creates a new variable with the given name and
 * initializes it as a list "head".
 *
 * @param[inout] name The "head" struct name.
 */
#define LIST_HEAD(name) sys_list_head_t name = { &(name), &(name) }


/**
 * @brief Initializes a list by pointer.
 *
 * @param[inout] ptr Pointer to a list.
 */
#define INIT_LIST_HEAD(ptr)                         \
    do                                              \
    {                                               \
        (ptr)->prev = (ptr);                        \
        (ptr)->next = (ptr);                        \
    } while (0)


/**
 * @brief Checks if a list is empty.
 *
 * @param[in] sys_list_head Pointer to a list.
 * @return 0 if not empty, non-zero otherwise.
 */
#define IS_EMPTY(sys_list_head) (sys_list_head)->next == (sys_list_head)


/**
 * @brief Adds a new item to the list between \a l_prev and \a l_next elements.
 * @warning This routine assumes that \a l_next is next to \a l_prev in the list.
 * @note This is an internal helper routine which is not intended to be used by the user.
 *
 * @param[in] l_prev Pointer to the previous element.
 * @param[in] l_next Pointer to the next element.
 * @param[in] l_new  Pointer to a new element.
 */
static inline void sys_ll_list_add(sys_list_head_t * l_prev,
                                   sys_list_head_t * l_next,
                                   sys_list_head_t * l_new)
{
    l_new->prev = l_prev;
    l_prev->next = l_new;
    l_next->prev = l_new;
    l_new->next = l_next;
}

/**
 * @brief Deletes an element between \a l_prev and \a l_next elements.
 * @warning This macro assumes that \a l_next is next to \a l_prev in the list.
 * @note This is an internal helper routine which is not intended to be used by the user.
 *
 * @param[in] l_prev Pointer to the previous element.
 * @param[in] l_next Pointer to the next element.
 */
static inline void sys_ll_list_del(sys_list_head_t * l_next,
                                   sys_list_head_t * l_prev)
{
    l_next->prev = l_prev;
    l_prev->next = l_next;
}

/**
 * @brief Function for adding a new item to the head of the list.
 *
 * @param[in] new  Pointer to a new element.
 * @param[in] head Pointer to the list head.
 */
static inline void sys_list_add(sys_list_head_t * new, sys_list_head_t * head)
{
    sys_ll_list_add(head, head->next, new);
}


/**
 * @brief Function for adding a new item to the tail of the list.
 *
 * @param[in] new  Pointer to a new element.
 * @param[in] head Pointer to the list head.
 */
static inline void sys_list_add_tail(sys_list_head_t * new, sys_list_head_t * head)
{
    sys_ll_list_add(head->prev, head, new);
}


/**
 * @brief Function for deleting an entry from list.
 *
 * @param[in] entry The element to delete from the list.
 */
static inline void sys_list_del(sys_list_head_t * entry)
{
    sys_ll_list_del(entry->next, entry->prev);
}


/**
 * @brief Function for deleting an entry from the list and reinitializing it.
 *
 * @param[in] entry The element to delete from the list.
 */
static inline void sys_list_del_init(sys_list_head_t * entry)
{
    sys_ll_list_del(entry->next, entry->prev);
    INIT_LIST_HEAD(entry);
}


/**
 * @brief Function for testing if a list is empty.
 
 * @param[in] head The list to test.
 * @return 0 if not empty, non-zero otherwise.
 */
static inline unsigned int sys_list_empty(sys_list_head_t * head)
{
    return IS_EMPTY(head);
}


/**
 * @brief Sets a pointer to a variable to the parent structure pointer using a
 * pointer to a field in this structure.
 *
 * @note This is a version of @ref GET_PARENT_BY_FIELD() extended by setting to a variable.
 *
 * @param[out] ll_ret_var Variable pointer name to return.
 * @param[in] ll_ptr      Pointer to the structure field.
 * @param[in] ll_type     Name of the parent structure.
 * @param[in] ll_member   Name of the structure field.
 */
#define SYS_LIST_ENTRY(ll_ret_var, ll_ptr, ll_type, ll_member)       \
    do                                                               \
    {                                                                \
        size_t  p = (size_t) ll_ptr;                                 \
        size_t  off = offsetof(ll_type, ll_member);                  \
        ll_ret_var = (ll_type *) (p - off);                          \
    } while (0)


/**
 * @brief Iterates through the list.
 * @note Use @ref SYS_LIST_FOR_EACH_SAFE() for thread-safe cases.
 *
 * @param[out] pos Iterator variable.
 * @param[in] head Pointer to the list head.
 */
#define SYS_LIST_FOR_EACH(pos, head)                                 \
    for (pos = ((head)->next);                                       \
         ((pos) != (head));                                          \
         pos = (pos)->next)


/**
 * @brief Thread-safe version of @ref SYS_LIST_FOR_EACH().
 *
 * @param[out] ll_pos   Iterator variable.
 * @param[out] ll_pos_n Temporary iterator variable (next entry).
 * @param[in] ll_head   Pointer to the list head.
 */
#define SYS_LIST_FOR_EACH_SAFE(ll_pos, ll_pos_n, ll_head)            \
    for (ll_pos = (ll_head)->next, ll_pos_n = (ll_head)->next->next; \
        (ll_pos) != (ll_head);                                       \
         ll_pos = ll_pos_n, ll_pos_n = ll_pos->next)

/** @} */

#endif /* SYS_LIST_H_INCLUDED */
