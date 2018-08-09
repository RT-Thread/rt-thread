/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
/**
* @defgroup nrf_queue Queue module
* @{
* @ingroup app_common
* @brief Functions that handle the queue instances.
*/

#ifndef NRF_QUEUE_H__
#define NRF_QUEUE_H__

#include <stdint.h>
#include <stdint.h>
#include <string.h>
#include "nrf_assert.h"
#include "sdk_errors.h"
#include "app_util.h"
#include "app_util_platform.h"
#include "nrf_log_instance.h"
#include "nrf_section.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Name of the module used for logger messaging.
 */
#define NRF_QUEUE_LOG_NAME queue

/**@brief Queue control block. */
typedef struct
{
    volatile size_t front;          //!< Queue front index.
    volatile size_t back;           //!< Queue back index.
    size_t max_utilization;         //!< Maximum utilization of the queue.
} nrf_queue_cb_t;

/**@brief Supported queue modes. */
typedef enum
{
    NRF_QUEUE_MODE_OVERFLOW,        //!< If the queue is full, new element will overwrite the oldest.
    NRF_QUEUE_MODE_NO_OVERFLOW,     //!< If the queue is full, new element will not be accepted.
} nrf_queue_mode_t;

/**@brief Instance of the queue. */
typedef struct
{
    nrf_queue_cb_t * p_cb;              //!< Pointer to the instance control block.
    void           * p_buffer;          //!< Pointer to the memory that is used as storage.
    size_t           size;              //!< Size of the queue.
    size_t           element_size;      //!< Size of one element.
    nrf_queue_mode_t mode;              //!< Mode of the queue.
#if NRF_QUEUE_CLI_CMDS
    const char      * p_name;           //!< Pointer to string with queue name.
#endif
    NRF_LOG_INSTANCE_PTR_DECLARE(p_log) //!< Pointer to instance of the logger object (Conditionally compiled).
} nrf_queue_t;

#if NRF_QUEUE_CLI_CMDS
#define __NRF_QUEUE_ASSIGN_POOL_NAME(_name)            .p_name = STRINGIFY(_name),
#else
#define __NRF_QUEUE_ASSIGN_POOL_NAME(_name)
#endif
/**@brief Create a queue instance.
 *
 * @note  This macro reserves memory for the given queue instance.
 *
 * @param[in]   _type       Type which is stored.
 * @param[in]   _name       Name of the queue.
 * @param[in]   _size       Size of the queue.
 * @param[in]   _mode       Mode of the queue.
 */
#define NRF_QUEUE_DEF(_type, _name, _size, _mode)                                        \
    static _type             CONCAT_2(_name, _nrf_queue_buffer[(_size) + 1]);            \
    static nrf_queue_cb_t    CONCAT_2(_name, _nrf_queue_cb);                             \
    NRF_LOG_INSTANCE_REGISTER(NRF_QUEUE_LOG_NAME, _name,                                 \
                                  NRF_QUEUE_CONFIG_INFO_COLOR,                           \
                                  NRF_QUEUE_CONFIG_DEBUG_COLOR,                          \
                                  NRF_QUEUE_CONFIG_LOG_INIT_FILTER_LEVEL,                \
                                  NRF_QUEUE_CONFIG_LOG_ENABLED ?                         \
                                    NRF_QUEUE_CONFIG_LOG_LEVEL : NRF_LOG_SEVERITY_NONE); \
     NRF_SECTION_ITEM_REGISTER(nrf_queue, const nrf_queue_t  _name) =                    \
        {                                                                                \
            .p_cb           = &CONCAT_2(_name, _nrf_queue_cb),                           \
            .p_buffer       = CONCAT_2(_name,_nrf_queue_buffer),                         \
            .size           = (_size),                                                   \
            .element_size   = sizeof(_type),                                             \
            .mode           = _mode,                                                     \
            __NRF_QUEUE_ASSIGN_POOL_NAME(_name)                                          \
            NRF_LOG_INSTANCE_PTR_INIT(p_log, NRF_QUEUE_LOG_NAME, _name)                  \
        }

/**@brief Declare a queue interface.
 *
 * @param[in]   _type    Type which is stored.
 * @param[in]   _name    Name of the queue.
 */
#define NRF_QUEUE_INTERFACE_DEC(_type, _name)               \
    ret_code_t  _name##_push(_type const * p_element);      \
    ret_code_t  _name##_pop(_type * p_element);             \
    ret_code_t  _name##_peek(_type * p_element);            \
    ret_code_t  _name##_write(_type const * p_data,         \
                              size_t        element_count); \
    ret_code_t  _name##_read(_type * p_data,                \
                             size_t  element_count);        \
    size_t      _name##_out(_type * p_data,                 \
                            size_t  element_count);         \
    size_t      _name##_in(_type const * p_data,            \
                            size_t element_count);          \
    bool        _name##_is_full(void);                      \
    bool        _name##_is_empty(void);                     \
    size_t      _name##_utilization_get(void);              \
    size_t      _name##_available_get(void);                \
    size_t      _name##_max_utilization_get(void);          \
    void        _name##_reset(void)

/**@brief Define a queue interface.
 *
 * @param[in]   _type    Type which is stored.
 * @param[in]   _name    Name of the queue.
 * @param[in]   _p_queue Queue instance.
 */
#define NRF_QUEUE_INTERFACE_DEF(_type, _name, _p_queue)                 \
    ret_code_t _name##_push(_type const * p_element)                    \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_push((_p_queue), p_element);                   \
    }                                                                   \
    ret_code_t _name##_pop(_type * p_element)                           \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_pop((_p_queue), p_element);                    \
    }                                                                   \
    ret_code_t _name##_peek(_type * p_element)                          \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_peek((_p_queue), p_element);                   \
    }                                                                   \
    ret_code_t _name##_write(_type const * p_data,                      \
                             size_t        element_count)               \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_write((_p_queue), p_data, element_count);      \
    }                                                                   \
    ret_code_t _name##_read(_type * p_data,                             \
                            size_t  element_count)                      \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_read((_p_queue), p_data, element_count);       \
    }                                                                   \
    size_t _name##_in(_type const * p_data,                             \
                      size_t  element_count)                            \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_in((_p_queue), p_data, element_count);         \
    }                                                                   \
    size_t _name##_out(_type * p_data,                                  \
                       size_t  element_count)                           \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        ASSERT((_p_queue)->element_size == sizeof(_type));              \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_out((_p_queue), p_data, element_count);        \
    }                                                                   \
    bool _name##_is_full(void)                                          \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        return nrf_queue_is_full(_p_queue);                             \
        GCC_PRAGMA("GCC diagnostic pop")                                \
    }                                                                   \
    bool _name##_is_empty(void)                                         \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_is_empty(_p_queue);                            \
    }                                                                   \
    size_t _name##_utilization_get(void)                                \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_utilization_get(_p_queue);                     \
    }                                                                   \
    size_t _name##_available_get(void)                                  \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_available_get(_p_queue);                       \
    }                                                                   \
    size_t _name##_max_utilization_get(void)                            \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        return nrf_queue_max_utilization_get(_p_queue);                 \
    }                                                                   \
    void _name##_reset(void)                                            \
    {                                                                   \
        GCC_PRAGMA("GCC diagnostic push")                               \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")              \
        ASSERT((_p_queue) != NULL);                                     \
        GCC_PRAGMA("GCC diagnostic pop")                                \
        nrf_queue_reset(_p_queue);                                      \
    }

/**@brief Function for pushing an element to the end of queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[in]   p_element           Pointer to the element that will be stored in the queue.
 *
 * @return      NRF_SUCCESS         If an element has been successfully added.
 * @return      NRF_ERROR_NO_MEM    If the queue is full (only in @ref NRF_QUEUE_MODE_NO_OVERFLOW).
 */
ret_code_t nrf_queue_push(nrf_queue_t const * p_queue, void const * p_element);

/**@brief Generic pop implementation.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[out]  p_element           Pointer where the element will be copied.
 * @param[out]  just_peek           If true, the returned element will not be removed from queue.
 *
 * @return      NRF_SUCCESS         If an element was returned.
 * @return      NRF_ERROR_NOT_FOUND If there are no more elements in the queue.
 */
ret_code_t nrf_queue_generic_pop(nrf_queue_t const * p_queue,
                                 void              * p_element,
                                 bool                just_peek);

/**@brief Pop element from the front of the queue.
 *
 * @param[in]   _p_queue            Pointer to the nrf_queue_t instance.
 * @param[out]  _p_element          Pointer where the element will be copied.
 *
 * @return      NRF_SUCCESS         If an element was returned.
 * @return      NRF_ERROR_NOT_FOUND If there are no more elements in the queue.
 */
#define nrf_queue_pop(_p_queue, _p_element) nrf_queue_generic_pop((_p_queue), (_p_element), false)

/**@brief Peek element from the front of the queue.
 *
 * @param[in]   _p_queue            Pointer to the nrf_queue_t instance.
 * @param[out]  _p_element          Pointer where the element will be copied.
 *
 * @return      NRF_SUCCESS         If an element was returned.
 * @return      NRF_ERROR_NOT_FOUND If there are no more elements in the queue.
 */
#define nrf_queue_peek(_p_queue, _p_element) nrf_queue_generic_pop((_p_queue), (_p_element), true)

/**@brief Function for writing elements to the queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[in]   p_data              Pointer to the buffer with elements to write.
 * @param[in]   element_count       Number of elements to write.
 *
 * @return      NRF_SUCCESS         If an element was written.
 * @return      NRF_ERROR_NO_MEM    There is not enough space in the queue. No element was written.
 */
ret_code_t nrf_queue_write(nrf_queue_t const * p_queue,
                           void const        * p_data,
                           size_t              element_count);

/**@brief Function for writing a portion of elements to the queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[in]   p_data              Pointer to the buffer with elements to write.
 * @param[in]   element_count       Number of elements to write.
 *
 * @return      The number of added elements.
 */
size_t nrf_queue_in(nrf_queue_t const * p_queue,
                    void const        * p_data,
                    size_t              element_count);

/**@brief Function for reading elements from the queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[out]  p_data              Pointer to the buffer where elements will be copied.
 * @param[in]   element_count       Number of elements to read.
 *
 * @return      NRF_SUCCESS         If an element was returned.
 * @return      NRF_ERROR_NOT_FOUND There is not enough elements in the queue.
 */
ret_code_t nrf_queue_read(nrf_queue_t const * p_queue,
                          void              * p_data,
                          size_t              element_count);

/**@brief Function for reading a portion of elements from the queue.
 *
 * @param[in]   p_queue             Pointer to the nrf_queue_t instance.
 * @param[out]  p_data              Pointer to the buffer where elements will be copied.
 * @param[in]   element_count       Number of elements to read.
 *
 * @return      The number of read elements.
 */
size_t nrf_queue_out(nrf_queue_t const * p_queue,
                    void               * p_data,
                    size_t               element_count);

/**@brief Function for checking if the queue is full.
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      True if the queue is full.
 */
bool nrf_queue_is_full(nrf_queue_t const * p_queue);

/**@brief Function for checking if the queue is empty.
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      True if the queue is empty.
 */
bool nrf_queue_is_empty(nrf_queue_t const * p_queue);

/**@brief Function for getting the current queue utilization.
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      Current queue utilization.
 */
size_t nrf_queue_utilization_get(nrf_queue_t const * p_queue);

/**@brief Function for getting the size of available space.
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      Size of available space.
 */
size_t nrf_queue_available_get(nrf_queue_t const * p_queue);

/**@brief Function for getting the maximal queue utilization.
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 * @return      Maximal queue utilization.
 */
size_t nrf_queue_max_utilization_get(nrf_queue_t const * p_queue);

/**@brief Function for resetting the maximal queue utilization.
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 *
 */
void nrf_queue_max_utilization_reset(nrf_queue_t const * p_queue);

/**@brief Function for resetting the queue state.
 *
 * @param[in]   p_queue     Pointer to the queue instance.
 */
void nrf_queue_reset(nrf_queue_t const * p_queue);

#ifdef __cplusplus
}
#endif

#endif // NRF_QUEUE_H__
/** @} */
