/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
  * @defgroup nrf_balloc Block memory allocator
  * @{
  * @ingroup app_common
  * @brief This module handles block memory allocator features.
  */


#ifndef NRF_BALLOC_H__
#define NRF_BALLOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk_errors.h"
#include "sdk_config.h"
#include "app_util_platform.h"
#include "app_util.h"
#include "nrf_log_instance.h"
#include "nrf_section.h"

/** @brief Name of the module used for logger messaging.
 */
#define NRF_BALLOC_LOG_NAME balloc

#if NRF_BALLOC_CONFIG_DEBUG_ENABLED || NRF_BALLOC_CLI_CMDS
#define NRF_BALLOC_HAS_NAME 1
#else
#define NRF_BALLOC_HAS_NAME 0
#endif

/**@defgroup NRF_BALLOC_DEBUG Macros for preparing debug flags for block allocator module.
 * @{ */
#define NRF_BALLOC_DEBUG_HEAD_GUARD_WORDS_SET(words)        (((words) & 0xFF) << 0)
#define NRF_BALLOC_DEBUG_HEAD_GUARD_WORDS_GET(flags)        (((flags) >> 0) & 0xFF)
#define NRF_BALLOC_DEBUG_TAIL_GUARD_WORDS_SET(words)        (((words) & 0xFF) << 8)
#define NRF_BALLOC_DEBUG_TAIL_GUARD_WORDS_GET(flags)        (((flags) >> 8) & 0xFF)

#define NRF_BALLOC_DEBUG_BASIC_CHECKS_SET(enable)           (!!(enable) << 16)
#define NRF_BALLOC_DEBUG_BASIC_CHECKS_GET(flags)            (flags & (1 << 16))
#define NRF_BALLOC_DEBUG_DOUBLE_FREE_CHECK_SET(enable)      (!!(enable) << 17)
#define NRF_BALLOC_DEBUG_DOUBLE_FREE_CHECK_GET(flags)       (flags & (1 << 17))
#define NRF_BALLOC_DEBUG_DATA_TRASHING_CHECK_SET(enable)    (!!(enable) << 18)
#define NRF_BALLOC_DEBUG_DATA_TRASHING_CHECK_GET(flags)     (flags & (1 << 18))
/**@} */

/**@brief Default debug flags for @ref nrf_balloc. This is used by the @ref NRF_BALLOC_DEF macro.
 *        Flags can be changed in @ref sdk_config.
 */
#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
    #define NRF_BALLOC_DEFAULT_DEBUG_FLAGS                                                      \
    (                                                                                           \
        NRF_BALLOC_DEBUG_HEAD_GUARD_WORDS_SET(NRF_BALLOC_CONFIG_HEAD_GUARD_WORDS)           |   \
        NRF_BALLOC_DEBUG_TAIL_GUARD_WORDS_SET(NRF_BALLOC_CONFIG_TAIL_GUARD_WORDS)           |   \
        NRF_BALLOC_DEBUG_BASIC_CHECKS_SET(NRF_BALLOC_CONFIG_BASIC_CHECKS_ENABLED)           |   \
        NRF_BALLOC_DEBUG_DOUBLE_FREE_CHECK_SET(NRF_BALLOC_CONFIG_DOUBLE_FREE_CHECK_ENABLED) |   \
        NRF_BALLOC_DEBUG_DATA_TRASHING_CHECK_SET(NRF_BALLOC_CONFIG_DATA_TRASHING_CHECK_ENABLED) \
    )
#else
    #define NRF_BALLOC_DEFAULT_DEBUG_FLAGS   0
#endif // NRF_BALLOC_CONFIG_DEBUG_ENABLED

/**@brief Block memory allocator control block.*/
typedef struct
{
    uint8_t * p_stack_pointer;          //!< Current allocation stack pointer.
    uint8_t   max_utilization;          //!< Maximum utilization of the memory pool.
} nrf_balloc_cb_t;

/**@brief Block memory allocator pool instance. The pool is made of elements of the same size. */
typedef struct
{
    nrf_balloc_cb_t * p_cb;             //!< Pointer to the instance control block.
    uint8_t         * p_stack_base;     //!< Base of the allocation stack.
                                        /**<
                                         * Stack is used to store handlers to not allocated elements.
                                         */
    uint8_t         * p_stack_limit;    //!< Maximum possible value of the allocation stack pointer.
    void            * p_memory_begin;   //!< Pointer to the start of the memory pool.
                                        /**<
                                         * Memory is used as a heap for blocks.
                                         */
    NRF_LOG_INSTANCE_PTR_DECLARE(p_log) //!< Pointer to instance of the logger object (Conditionally compiled).
#if NRF_BALLOC_HAS_NAME
    const char      * p_name;           //!< Pointer to string with pool name.
#endif
#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
    uint32_t          debug_flags;      //!< Debugging settings.
                                        /**<
                                         * Debug flag should be created by @ref NRF_BALLOC_DEBUG.
                                         */
#endif // NRF_BALLOC_CONFIG_DEBUG_ENABLED
    uint16_t          block_size;       //!< Size of the allocated block (including debug overhead).
                                        /**<
                                         * Single block contains user element with header and tail
                                         * words.
                                         */
} nrf_balloc_t;

/**@brief Get total memory consumed by single block (element size with overhead caused by debug
 *        flags).
 *
 * @param[in]   _element_size    Size of an element.
 * @param[in]   _debug_flags     Debug flags.
 */
#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
    #define NRF_BALLOC_BLOCK_SIZE(_element_size, _debug_flags)                      \
    (                                                                               \
       (sizeof(uint32_t) * NRF_BALLOC_DEBUG_HEAD_GUARD_WORDS_GET(_debug_flags)) +   \
       ALIGN_NUM(sizeof(uint32_t), (_element_size)) +                               \
       (sizeof(uint32_t) * NRF_BALLOC_DEBUG_TAIL_GUARD_WORDS_GET(_debug_flags))     \
    )
#else
    #define NRF_BALLOC_BLOCK_SIZE(_element_size, _debug_flags)  \
                ALIGN_NUM(sizeof(uint32_t), (_element_size))
#endif // NRF_BALLOC_CONFIG_DEBUG_ENABLED


/**@brief Get element size ( excluding debugging overhead is present)
 *        flags).
 *
 * @param[in]   _p_balloc   Pointer to balloc instance.
 */
#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
#define NRF_BALLOC_ELEMENT_SIZE(_p_balloc) \
           (ALIGN_NUM(sizeof(uint32_t), (_p_balloc)->block_size) -                                 \
           ((sizeof(uint32_t) * NRF_BALLOC_DEBUG_HEAD_GUARD_WORDS_GET((_p_balloc)->debug_flags)) + \
           (sizeof(uint32_t) * NRF_BALLOC_DEBUG_TAIL_GUARD_WORDS_GET((_p_balloc)->debug_flags))))
#else
#define NRF_BALLOC_ELEMENT_SIZE(_p_balloc) \
           (_p_balloc)->block_size
#endif // NRF_BALLOC_CONFIG_DEBUG_ENABLED

#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
#define __NRF_BALLOC_ASSIGN_DEBUG_FLAGS(_debug_flags)   .debug_flags = (_debug_flags),
#else
#define __NRF_BALLOC_ASSIGN_DEBUG_FLAGS(_debug_flags)
#endif

#if NRF_BALLOC_HAS_NAME
#define __NRF_BALLOC_ASSIGN_POOL_NAME(_name)            .p_name = STRINGIFY(_name),
#else
#define __NRF_BALLOC_ASSIGN_POOL_NAME(_name)
#endif


/**@brief Create a block allocator instance with custom debug flags.
 *
 * @note  This macro reserves memory for the given block allocator instance.
 *
 * @param[in]   _name           Name of the allocator.
 * @param[in]   _element_size   Size of one element.
 * @param[in]   _pool_size      Size of the pool.
 * @param[in]   _debug_flags    Debug flags (@ref NRF_BALLOC_DEBUG).
 */
#define NRF_BALLOC_DBG_DEF(_name, _element_size, _pool_size, _debug_flags)                      \
    STATIC_ASSERT((_pool_size) <= UINT8_MAX);                                                   \
    static uint8_t              CONCAT_2(_name, _nrf_balloc_pool_stack)[(_pool_size)];          \
    static uint32_t             CONCAT_2(_name,_nrf_balloc_pool_mem)                            \
        [NRF_BALLOC_BLOCK_SIZE(_element_size, _debug_flags) * (_pool_size) / sizeof(uint32_t)]; \
    static nrf_balloc_cb_t      CONCAT_2(_name,_nrf_balloc_cb);                                 \
    NRF_LOG_INSTANCE_REGISTER(NRF_BALLOC_LOG_NAME, _name,                                       \
                              NRF_BALLOC_CONFIG_INFO_COLOR,                                     \
                              NRF_BALLOC_CONFIG_DEBUG_COLOR,                                    \
                              NRF_BALLOC_CONFIG_INITIAL_LOG_LEVEL,                              \
                              NRF_BALLOC_CONFIG_LOG_ENABLED ?                                   \
                                      NRF_BALLOC_CONFIG_LOG_LEVEL : NRF_LOG_SEVERITY_NONE);     \
    NRF_SECTION_ITEM_REGISTER(nrf_balloc, const nrf_balloc_t  _name) =                          \
        {                                                                                       \
            .p_cb           = &CONCAT_2(_name,_nrf_balloc_cb),                                  \
            .p_stack_base   = CONCAT_2(_name,_nrf_balloc_pool_stack),                           \
            .p_stack_limit  = CONCAT_2(_name,_nrf_balloc_pool_stack) + (_pool_size),            \
            .p_memory_begin = CONCAT_2(_name,_nrf_balloc_pool_mem),                             \
            .block_size     = NRF_BALLOC_BLOCK_SIZE(_element_size, _debug_flags),               \
                                                                                                \
            NRF_LOG_INSTANCE_PTR_INIT(p_log, NRF_BALLOC_LOG_NAME, _name)                        \
            __NRF_BALLOC_ASSIGN_POOL_NAME(_name)                                                \
            __NRF_BALLOC_ASSIGN_DEBUG_FLAGS(_debug_flags)                                       \
        }

/**@brief Create a block allocator instance.
 *
 * @note  This macro reserves memory for the given block allocator instance.
 *
 * @param[in]   _name           Name of the allocator.
 * @param[in]   _element_size   Size of one element.
 * @param[in]   _pool_size      Size of the pool.
 */
#define NRF_BALLOC_DEF(_name, _element_size, _pool_size)                                           \
            NRF_BALLOC_DBG_DEF(_name, _element_size, _pool_size, NRF_BALLOC_DEFAULT_DEBUG_FLAGS)

/**@brief Create a block allocator interface.
 *
 * @param[in]   _type    Type which is allocated.
 * @param[in]   _name    Name of the allocator.
 */
#define NRF_BALLOC_INTERFACE_DEC(_type, _name)    \
    _type * CONCAT_2(_name,_alloc)(void);                  \
    void    CONCAT_2(_name,_free)(_type * p_element)

/**@brief Define a custom block allocator interface.
 *
 * @param[in]   _attr    Function attribute that will be added to allocator function definition.
 * @param[in]   _type    Type which is allocated.
 * @param[in]   _name    Name of the allocator.
 * @param[in]   _p_pool  Pool from which data will be allocated.
 */
#define NRF_BALLOC_INTERFACE_CUSTOM_DEF(_attr, _type, _name, _p_pool)           \
    _attr _type * CONCAT_2(_name,_alloc)(void)                                  \
    {                                                                           \
        GCC_PRAGMA("GCC diagnostic push")                                       \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")                      \
        ASSERT((_p_pool) != NULL);                                              \
        ASSERT((_p_pool)->block_size >=                                         \
               NRF_BALLOC_BLOCK_SIZE(sizeof(_type), (_p_pool)->debug_flags));   \
        GCC_PRAGMA("GCC diagnostic pop")                                        \
        return (_type *)(nrf_balloc_alloc(_p_pool));                            \
    }                                                                           \
                                                                                \
    _attr void CONCAT_2(_name,_free)(_type * p_element)                         \
    {                                                                           \
        GCC_PRAGMA("GCC diagnostic push")                                       \
        GCC_PRAGMA("GCC diagnostic ignored \"-Waddress\"")                      \
        ASSERT((_p_pool) != NULL);                                              \
        ASSERT((_p_pool)->block_size >=                                         \
               NRF_BALLOC_BLOCK_SIZE(sizeof(_type), (_p_pool)->debug_flags));   \
        GCC_PRAGMA("GCC diagnostic pop")                                        \
        nrf_balloc_free((_p_pool), p_element);                                  \
    }

/**@brief Define block allocator interface.
 *
 * @param[in]   _type    Type which is allocated.
 * @param[in]   _name    Name of the allocator.
 * @param[in]   _p_pool  Pool from which data will be allocated.
 */
#define NRF_BALLOC_INTERFACE_DEF(_type, _name, _p_pool)        \
        NRF_BALLOC_INTERFACE_CUSTOM_DEF(/* empty */, _type, _name, _p_pool)

/**@brief Define a local block allocator interface.
 *
 * @param[in]   _type    Type which is allocated.
 * @param[in]   _name    Name of the allocator.
 * @param[in]   _p_pool  Pool from which data will be allocated.
 */
#define NRF_BALLOC_INTERFACE_LOCAL_DEF(_type, _name, _p_pool)  \
        NRF_BALLOC_INTERFACE_CUSTOM_DEF(static, _type, _name, _p_pool)

/**@brief Function for initializing a block memory allocator pool.
 *
 * @param[out]  p_pool          Pointer to the pool that is to be initialized.
 *
 * @return  NRF_SUCCESS on success, otherwise error code.
 */
ret_code_t nrf_balloc_init(nrf_balloc_t const * p_pool);

/**@brief Function for allocating an element from the pool.
 *
 * @note    This module guarantees that the returned memory is aligned to 4.
 *
 * @param[in]   p_pool  Pointer to the memory pool from which the element will be allocated.
 *
 * @return      Allocated element or NULL if the specified pool is empty.
 */
void * nrf_balloc_alloc(nrf_balloc_t const * p_pool);

/**@brief Function for freeing an element back to the pool.
 *
 * @param[in]   p_pool      Pointer to the memory pool.
 * @param[in]   p_element   Element to be freed.
 */
void nrf_balloc_free(nrf_balloc_t const * p_pool, void * p_element);

/**@brief Function for getting maximum memory pool utilization.
 *
 * @param[in]   p_pool Pointer to the memory pool instance.
 *
 * @return Maximum number of elements allocated from the pool.
 */
__STATIC_INLINE uint8_t nrf_balloc_max_utilization_get(nrf_balloc_t const * p_pool);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION
__STATIC_INLINE uint8_t nrf_balloc_max_utilization_get(nrf_balloc_t const * p_pool)
{
    ASSERT(p_pool != NULL);
    return p_pool->p_cb->max_utilization;
}
#endif //SUPPRESS_INLINE_IMPLEMENTATION

/**@brief Function for getting current memory pool utilization.
 *
 * @param[in]   p_pool Pointer to the memory pool instance.
 *
 * @return Maximum number of elements allocated from the pool.
 */
__STATIC_INLINE uint8_t nrf_balloc_utilization_get(nrf_balloc_t const * p_pool);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION
__STATIC_INLINE uint8_t nrf_balloc_utilization_get(nrf_balloc_t const * p_pool)
{
    ASSERT(p_pool != NULL);
    return (p_pool->p_stack_limit - p_pool->p_cb->p_stack_pointer);
}
#endif //SUPPRESS_INLINE_IMPLEMENTATION

#ifdef __cplusplus
}
#endif

#endif // NRF_BALLOC_H__
/** @} */
