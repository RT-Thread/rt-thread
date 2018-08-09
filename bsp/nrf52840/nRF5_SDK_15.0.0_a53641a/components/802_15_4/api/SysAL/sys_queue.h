/**
 * Copyright (c) 2016 - 2018 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
#ifndef SYS_QUEUE_H_INCLUDED
#define SYS_QUEUE_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>

/** @file
 * This file contains declarations of the primitives to work with queues and necessary types.
 *
 * @defgroup sys_queues Queue API
 * @ingroup sys_15_4
 * @{
 * @brief Module to declare the queue API.
 * @details The queue module implements a set of routines to deal with queues. Before
 * any calls to its API are issued, a queue must be initialized using sys_queue_init(). The following routines
 * return queue items from different parts of an initialized queue without removing it from the queue:
 * sys_queue_front(), sys_queue_back(), sys_queue_next(), and sys_queue_at().
 * The following routines insert elements to the queue: sys_queue_push_front(),
 * sys_queue_push_back(), sys_queue_push_predicated(), sys_queue_push_predicated_force(), and sys_queue_insert().
 * The following routines remove elements from the queue: sys_queue_pop_front(), sys_queue_remove(),
 * sys_queue_remove_after(). These helper routines get information about a queue: sys_queue_size() and
 * sys_queue_is_empty(). The module also supports an iterator macro implemented by SYS_QUEUE_FOR_EACH().
 */

/**@brief       Queue item descriptor.
 *
 * @details     In order to store any user data struct in a queue, the user struct should contain
 *              a field of type 'sys_queue_item_t'. This field may be at any offset.
 *              The user data item can be cast from the queue item,
 *              by the \ref GET_PARENT_BY_FIELD() macro from sys_utils.h.
 */
typedef struct sys_queue_item_s
{
    struct sys_queue_item_s * next;
} sys_queue_item_t;

/**@brief       Queue descriptor.
 */
typedef sys_queue_item_t sys_queue_t;

/**@brief       Prototype of a predicate function for pushing an item into the queue.
 *
 * @details     As a user of the queue library, implement the predicate function and pass it
 *              as a parameter to \ref sys_queue_push_predicated(). You can choose 
 *              whether insertion of a new item should be done before the given existing item of
 *              the queue, or not.
 *
 * @param[in]   p_before_item  Pointer to the existing item before which a new item 
 *                             should be inserted.
 * @param[in]   p_new_item     Pointer to the item to be inserted into the queue.
 *
 * @retval      true   Insertion is to be done before the given item, false otherwise.
 */
typedef bool (* sys_queue_push_predicate_t)(
                    sys_queue_item_t * p_before_item,
                    sys_queue_item_t * p_new_item);


/**@brief       Function for initializing the queue before any other usage of the queue.
 *
 * @details     Initialize (reset) the queue to its initial state. The queue becomes empty.
 *
 * @param[in]   p_queue    Queue to be initialized.
 */
void sys_queue_init(sys_queue_t * p_queue);


/**@brief       Function for getting the front (head) item of the queue without removing it.
 *
 * @details     Return a pointer to the item from the head of the queue but leave it in the queue.
 *
 * @param[in]   p_queue    Queue to get the item from.
 *
 * @retval      Pointer to the head item of the queue, or NULL if the queue is empty.
 */
sys_queue_item_t * sys_queue_front(const sys_queue_t * p_queue);


/**@brief       Function for getting the back (tail) item of the queue without removing it.
 *
 * @details     Return a pointer to the item from the tail of the queue but leave it in the queue.
 *
 * @param[in]   p_queue    Queue to get the item from.
 *
 * @retval      Pointer to the tail item of the queue, or NULL if the queue is empty.
 */
sys_queue_item_t * sys_queue_back(const sys_queue_t * p_queue);


/**@brief   Function for getting the item, next to the given item of the queue.
 *
 * @details Return a pointer to the next item after the given one, or NULL if the 
 *          given item is the last item of the queue.
 *
 * @param[in] p_queue     Pointer to the queue.
 * @param[in] p_item      Pointer to the item.
 *
 * @retval  Pointer to the next item after the given one, or NULL if the 
 *          given item is the last item of the queue.
 */
sys_queue_item_t * sys_queue_next(const sys_queue_t * p_queue, const sys_queue_item_t * p_item);


/**@brief       Function for pushing an item to the front (head) of the queue.
 *
 * @details     This function inserts an item to the head of the queue.
 *
 * @param[in]   p_queue    Queue to push the item to.
 * @param[in]   p_item     Item to insert to the front of the queue.
 */
void sys_queue_push_front(sys_queue_t * p_queue, sys_queue_item_t * p_item);


/**@brief       Function for pushing an item to the back (tail) of the queue.
 *
 * @details     This function inserts an item to the tail of the queue.
 *
 * @param[in]   p_queue    Queue to push the item to.
 * @param[in]   p_item     Item to insert to the tail of the queue.
 */
void sys_queue_push_back(sys_queue_t * p_queue, sys_queue_item_t * p_item);


/**@brief       Function for pushing an item to the queue with a predicate.
 *
 * @details     Conditionally push an item to the queue using the given predicate that tries to determine
 *              the insertion position.
 *
 * @param[in]   p_queue    Queue to push the item to.
 * @param[in]   p_item     Item to be pushed.
 * @param[in]   predicate  Predicate to be used to find the insertion position.
 *
 * @retval  true    The item was inserted into the queue, false otherwise.
 */
bool sys_queue_push_predicated(
            sys_queue_t *               p_queue,
            sys_queue_item_t *          p_item,
            sys_queue_push_predicate_t  predicate);


/**@brief       Function for pushing an item to the queue with a predicate forcing insertion to the tail if the predicate
 *              fails.
 *
 * @details     Unconditionally push an item to the queue using the given predicate that tries to
 *              determine the insertion position.
 *              If predicate returns false, then force the insertion to the tail of the queue.
 *
 * @param[in]   p_queue    Queue to push item to.
 * @param[in]   p_item     Item to be pushed.
 * @param[in]   predicate  Predicate to be used to find the insertion position.
 */
void sys_queue_push_predicated_force(
            sys_queue_t *               p_queue,
            sys_queue_item_t *          p_item,
            sys_queue_push_predicate_t  predicate);


/**@brief       Function for getting and removing the front (head) item from the queue.
 *
 * @details     Get an item from the head of the queue and remove it from the queue.
 *
 * @param[in]   p_queue    Queue to get and remove the head item from.
 *
 * @retval      Pointer to the head item of queue or NULL if the queue is empty.
 */
sys_queue_item_t * sys_queue_pop_front(sys_queue_t * p_queue);


/**@brief       Function for removing an item from the queue.
 *
 * @details     The given item will be removed from the queue.
 *
 * @note        The complexity of this function is O(n). Use function \ref sys_queue_remove_after()
 *              whenever the previous item of the queue is known. 
 *
 * @param[in]   p_queue    Queue to remove the item from.
 * @param[in]   p_item     Item to remove from the queue.
 */
void sys_queue_remove(sys_queue_t * p_queue, sys_queue_item_t * p_item);


/**@brief       Function for removing the item after the given item from the queue.
 *
 * @details     The item next to the given one will be removed from the queue.
 *
 * @param[in]   p_queue         Queue to remove the item from.
 * @param[in]   p_after_item    Next to this item will be removed.
 */
void sys_queue_remove_after(sys_queue_t * p_queue, sys_queue_item_t * p_after_item);


/**@brief       Function for returning the current size of a queue, i.e. number of elements inside it.
 *
 * @details     This function goes through the whole queue, so it is relatively slow.
 *
 * @param[in]   p_queue         Queue to work with.
 *
 * @retval      Number of items currently inserted into the queue.
 */
uint8_t sys_queue_size(const sys_queue_t * p_queue);


/**@brief       Function for returning a pointer to the item inside a queue represented by an index.
 *
 * @details     This function searches through the whole queue, so it is relatively slow.
 *
 * @param[in]   p_queue         Queue to work with.
 * @param[in]   index           Requested index.
 *
 * @retval      Pointer to the requested item or NULL if the queue size is less
 *              than \a index.
 */
sys_queue_item_t * sys_queue_at(const sys_queue_t * p_queue, const uint8_t index);


/**@brief       Function for inserting an item at the specified position represented by an index in the queue.
 *              If this position is too big, it is inserted to the tail of the queue.
 *
 * @details     This function searches through the whole queue, so it is relatively slow.
 *
 * @param[in]   p_queue         Queue to insert to.
 * @param[in]   p_item          Item to be inserted.
 * @param[in]   pos             Position inside the queue (0 is the front).
 */
void sys_queue_insert(sys_queue_t * p_queue, sys_queue_item_t * p_item, const uint8_t pos);


/**@brief       Function for determining if a queue is empty.
 *
 * @param[in]   p_queue         Queue to be checked.
 *
 * @retval      True if queue is empty, false otherwise.
 */
bool sys_queue_is_empty(const sys_queue_t * p_queue);


/**@brief       Macro for iterating through all items in the queue.
 *
 * @param[in]   p_queue     Pointer to the queue (sys_queue_t *).
 * @param[in]   p_iterator  Variable to be used as an iterator (sys_queue_item_t *).
 */
#define SYS_QUEUE_FOR_EACH(p_queue, p_iterator)                            \
            for (sys_queue_item_t * p_iterator = sys_queue_front(p_queue); \
                 p_iterator != NULL;                                       \
                 p_iterator = sys_queue_next(p_queue, p_iterator))

/** @} */

#endif // SYS_QUEUE_H_INCLUDED
