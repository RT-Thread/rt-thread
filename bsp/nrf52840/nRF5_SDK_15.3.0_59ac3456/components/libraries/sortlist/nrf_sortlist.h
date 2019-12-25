/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
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
#ifndef NRF_SORTLIST_H
#define NRF_SORTLIST_H

#include "sdk_config.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @defgroup nrf_sortlist Sorted list
 * @{
 * @ingroup app_common
 * @brief Module for storing items in the ordered list.
 */

/**
 * @brief Forward declaration of sorted list item.
 */
typedef struct nrf_sortlist_item_s nrf_sortlist_item_t;

/** @brief Prototype of a function which compares two elements.
 *
 * @param p_item0 Item 0.
 * @param p_item1 Item 1.
 *
 * @return True if Item 0 should be higher than Item 1 and false otherwise.
 *
 */
typedef bool (*nrf_sortlist_compare_func_t)(nrf_sortlist_item_t * p_item0, nrf_sortlist_item_t * p_item1);

/**
 * @brief A structure for item in the sorted list.
 */
struct nrf_sortlist_item_s
{
    nrf_sortlist_item_t * p_next;             /* Pointer to the next item in the list. */
};

/**
 * @brief Sorted list instance control block.
 *
 * Control block contains instance data which must be located in read/write memory.
 */
typedef struct
{
    nrf_sortlist_item_t *       p_head;       /* List head.*/
} nrf_sortlist_cb_t;
/**
 * @brief Structure for sorted list instance.
 *
 * Instance can be placed in read only memory.
 */
typedef struct
{
    char *                      p_name;       /* List name. */
    nrf_sortlist_cb_t *         p_cb;         /* List head.*/
    nrf_sortlist_compare_func_t compare_func; /* Function used for comparison. */
} nrf_sortlist_t;

/**
 * @brief Macro for conditionally including instance name.
 *
 * @param _name Instance name.
 */
#define NRF_SORTLIST_INST_NAME(_name) (NRF_LOG_ENABLED && NRF_SORTLIST_CONFIG_LOG_ENABLED) ? \
                                                                           STRINGIFY(_name) : NULL
/**
 * @brief Macro for defining a sorted list instance.
 *
 * @param _name         Instance name.
 * @param _compare_func Pointer to a compare function.
 */
#define NRF_SORTLIST_DEF(_name, _compare_func)                   \
    static nrf_sortlist_cb_t CONCAT_2(_name,_sortlist_cb) = {    \
        .p_head = NULL                                           \
    };                                                           \
    static const nrf_sortlist_t _name = {                        \
        .p_name = NRF_SORTLIST_INST_NAME(_name),                 \
        .p_cb = &CONCAT_2(_name,_sortlist_cb),                   \
        .compare_func = _compare_func,                           \
    }

/**
 * @brief Function for adding an element into a list.
 *
 * New item will be placed in the queue based on the compare function.
 *
 * @param p_list   List instance.
 * @param p_item   Item.
 */
void nrf_sortlist_add(nrf_sortlist_t const * p_list, nrf_sortlist_item_t * p_item);

/**
 * @brief Function for removing an item from the list head.
 *
 * @param p_list   List instance.
 *
 * @return Pointer to the item which was on the list head.
 */
nrf_sortlist_item_t * nrf_sortlist_pop(nrf_sortlist_t const * p_list);

/**
 * @brief Function for getting (without removing) an item from the list head.
 *
 * @param p_list   List instance.
 *
 * @return Pointer to the item which is on the list head.
 */
nrf_sortlist_item_t const * nrf_sortlist_peek(nrf_sortlist_t const * p_list);

/**
 * @brief Function for iterating over the list.
 *
 * @param p_item   Item in the list.
 *
 * @return Pointer to the next item in the list.
 */
nrf_sortlist_item_t const * nrf_sortlist_next(nrf_sortlist_item_t const * p_item);

/**
 * @brief Function for removing an item from the queue.
 *
 * @param p_list   List instance.
 * @param p_item   Item.
 *
 * @retval true  Item was found and removed.
 * @retval false Item not found in the list.
 */
bool nrf_sortlist_remove(nrf_sortlist_t const * p_list, nrf_sortlist_item_t * p_item);

/** @} */

#ifdef __cplusplus
}
#endif

#endif //NRF_SORTLIST_H

