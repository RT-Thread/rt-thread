/**
 ****************************************************************************************
 *
 * @file ke_queue.h
 *
 * @brief This file contains the definition of the message object, queue element
 * object and queue object
 *
 * Copyright (C) RivieraWaves 2009-2015
 *
 *
 ****************************************************************************************
 */

#ifndef _KE_QUEUE_H_
#define _KE_QUEUE_H_
//
/**
 ****************************************************************************************
 * @addtogroup QUEUE Queues and Lists
 * @ingroup KERNEL
 * @brief Queue management module
 *
 * This module implements the functions used for managing message queues.
 * These functions must not be called under IRQ!
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>              // standard integer
#include <stdbool.h>             // standard boolean
#include "ble_arch.h"            // compiler definitions
#include "ke_config.h"           // kernel configuration
#include "co_list.h"             // list definition

/*
 * FUNCTION PROTOTYPES
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Pop entry to the queue
 *
 * @param[in]  queue    Pointer to the queue.
 * @param[in]  element  Pointer to the element.
 ****************************************************************************************
 */
__INLINE void ke_queue_push(struct co_list *const queue, struct co_list_hdr *const element)
{
    co_list_push_back(queue, element);
}

/**
 ****************************************************************************************
 * @brief Pop entry from the queue
 *
 * @param[in]  queue    Pointer to the queue.
 *
 * @return              Pointer to the element.
 ****************************************************************************************
 */
__INLINE struct co_list_hdr *ke_queue_pop(struct co_list *const queue)
{
    return co_list_pop_front(queue);
}

/**
 ****************************************************************************************
 * @brief Extracts an element matching a given algorithm.
 *
 * @param[in]  queue    Pointer to the queue.
 * @param[in]  func     Matching function.
 * @param[in]  arg      Match argument.
 *
 * @return              Pointer to the element found and removed (NULL otherwise).
 ****************************************************************************************
 */
struct co_list_hdr *ke_queue_extract(struct co_list * const queue,
                                 bool (*func)(struct co_list_hdr const * elmt, uint32_t arg),
                                 uint32_t arg);

/**
 ****************************************************************************************
 * @brief Insert an element in a sorted queue.
 *
 * This primitive use a comparison function from the parameter list to select where the
 * element must be inserted.
 *
 * @param[in]  queue    Pointer to the queue.
 * @param[in]  element  Pointer to the element to insert.
 * @param[in]  cmp      Comparison function (return true if first element has to be inserted
 *                      before the second one).
 *
 * @return              Pointer to the element found and removed (NULL otherwise).
 ****************************************************************************************
 */
void ke_queue_insert(struct co_list * const queue, struct co_list_hdr * const element,
                     bool (*cmp)(struct co_list_hdr const *elementA,
                     struct co_list_hdr const *elementB));

/// @} QUEUE

#endif // _KE_QUEUE_H_
