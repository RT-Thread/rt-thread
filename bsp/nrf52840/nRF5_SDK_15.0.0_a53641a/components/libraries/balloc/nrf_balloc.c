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
#include "sdk_common.h"
 #if NRF_MODULE_ENABLED(NRF_BALLOC)

#include "nrf_section.h"
#include "nrf_balloc.h"
#include "app_util_platform.h"


#if NRF_BALLOC_CONFIG_LOG_ENABLED
    #define NRF_LOG_LEVEL             NRF_BALLOC_CONFIG_LOG_LEVEL
    #define NRF_LOG_INITIAL_LEVEL     NRF_BALLOC_CONFIG_INITIAL_LOG_LEVEL
    #define NRF_LOG_INFO_COLOR        NRF_BALLOC_CONFIG_INFO_COLOR
    #define NRF_LOG_DEBUG_COLOR       NRF_BALLOC_CONFIG_DEBUG_COLOR
#else
    #define NRF_LOG_LEVEL       0
#endif // NRF_BALLOC_CONFIG_LOG_ENABLED
#include "nrf_log.h"

#define HEAD_GUARD_FILL     0xBAADF00D      /**< Magic number used to mark head guard.*/
#define TAIL_GUARD_FILL     0xBAADCAFE      /**< Magic number used to mark tail guard.*/
#define FREE_MEM_FILL       0xBAADBAAD      /**< Magic number used to mark free memory.*/

#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
#define POOL_ID(_p_pool) _p_pool->p_name
#define POOL_MARKER     "%s"
#else
#define POOL_ID(_p_pool) _p_pool
#define POOL_MARKER     "0x%08X"
#endif

NRF_SECTION_DEF(nrf_balloc, nrf_balloc_t);

#if NRF_BALLOC_CLI_CMDS
#include "nrf_cli.h"

static void nrf_balloc_status(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    UNUSED_PARAMETER(argv);

    if (nrf_cli_help_requested(p_cli))
    {
        nrf_cli_help_print(p_cli, NULL, 0);
        return;
    }

    if (argc > 1)
    {
        nrf_cli_fprintf(p_cli, NRF_CLI_ERROR, "Bad argument count");
        return;
    }

    uint32_t num_of_instances = NRF_SECTION_ITEM_COUNT(nrf_balloc, nrf_balloc_t);
    uint32_t i;

    for (i = 0; i < num_of_instances; i++)
    {
        const nrf_balloc_t * p_instance = NRF_SECTION_ITEM_GET(nrf_balloc, nrf_balloc_t, i);

        uint32_t element_size = NRF_BALLOC_ELEMENT_SIZE(p_instance);
        uint32_t dbg_addon  = p_instance->block_size - element_size;
        uint32_t pool_size  = p_instance->p_stack_limit - p_instance->p_stack_base;
        uint32_t max_util   = nrf_balloc_max_utilization_get(p_instance);
        uint32_t util       = nrf_balloc_utilization_get(p_instance);
        const char * p_name = p_instance->p_name;
        nrf_cli_fprintf(p_cli, NRF_CLI_NORMAL,
                        "%s\r\n\t- Element size:\t%d + %d bytes of debug information\r\n"
                        "\t- Usage:\t%u%% (%u out of %u elements)\r\n"
                        "\t- Maximum:\t%u%% (%u out of %u elements)\r\n\r\n",
                        p_name, element_size, dbg_addon,
                        100ul * util/pool_size, util,pool_size,
                        100ul * max_util/pool_size, max_util,pool_size);

    }
}
// Register "balloc" command and its subcommands in CLI.
NRF_CLI_CREATE_STATIC_SUBCMD_SET(nrf_balloc_commands)
{
     NRF_CLI_CMD(status, NULL, "Print status of balloc instances.", nrf_balloc_status),
     NRF_CLI_SUBCMD_SET_END
};

NRF_CLI_CMD_REGISTER(balloc, &nrf_balloc_commands, "Commands for BALLOC management", nrf_balloc_status);
#endif //NRF_BALLOC_CLI_CMDS

#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
/**@brief  Validate block memory, prepare block guards, and calculate pointer to the element.
 *
 * @param[in]   p_pool  Pointer to the memory pool.
 * @param[in]   p_head  Pointer to the beginning of the block.
 *
 * @return      Pointer to the element.
 */
__STATIC_INLINE void * nrf_balloc_block_unwrap(nrf_balloc_t const * p_pool, void * p_head)
{
    ASSERT((p_pool != NULL) && ((p_pool->block_size % sizeof(uint32_t)) == 0));
    ASSERT((p_head != NULL) && (((uint32_t)(p_head) % sizeof(uint32_t)) == 0));

    uint32_t head_words  = NRF_BALLOC_DEBUG_HEAD_GUARD_WORDS_GET(p_pool->debug_flags);
    uint32_t tail_words  = NRF_BALLOC_DEBUG_TAIL_GUARD_WORDS_GET(p_pool->debug_flags);

    uint32_t * p_tail    = (uint32_t *)((size_t)(p_head) + p_pool->block_size);
    uint32_t * p_element = (uint32_t *)p_head + head_words;

    if (NRF_BALLOC_DEBUG_DATA_TRASHING_CHECK_GET(p_pool->debug_flags))
    {
        for (uint32_t * ptr = p_head; ptr < p_tail; ptr++)
        {
            if (*ptr != FREE_MEM_FILL)
            {
                NRF_LOG_INST_ERROR(p_pool->p_log,
                                   "Detected free memory corruption at 0x%08X (0x%08X != 0x%08X)",
                                   ptr, *ptr, FREE_MEM_FILL);
                APP_ERROR_CHECK_BOOL(false);
            }
        }
    }

    for (uint32_t * ptr = p_head; ptr < p_element; ptr++)
    {
        *ptr = HEAD_GUARD_FILL;
    }

    for (uint32_t * ptr = ( p_tail - tail_words); ptr < p_tail; ptr++)
    {
        *ptr = TAIL_GUARD_FILL;
    }

    return p_element;
}

/**@brief  Calculate pointer to the block, validate block guards, and mark block memory as free.
 *
 * @param[in]   p_pool      Pointer to the memory pool.
 * @param[in]   p_element   Pointer to the element.
 *
 * @return      Pointer to the beginning of the block.
 */
__STATIC_INLINE void * nrf_balloc_element_wrap(nrf_balloc_t const * p_pool, void * p_element)
{
    ASSERT((p_pool    != NULL) && ((p_pool->block_size % sizeof(uint32_t))    == 0));
    ASSERT((p_element != NULL) && (((uint32_t)(p_element) % sizeof(uint32_t)) == 0));

    uint32_t head_words  = NRF_BALLOC_DEBUG_HEAD_GUARD_WORDS_GET(p_pool->debug_flags);
    uint32_t tail_words  = NRF_BALLOC_DEBUG_TAIL_GUARD_WORDS_GET(p_pool->debug_flags);

    uint32_t * p_head   = (uint32_t *)p_element - head_words;
    uint32_t * p_tail   = (uint32_t *)((size_t)(p_head) + p_pool->block_size);

    for (uint32_t * ptr = p_head; ptr < (uint32_t *)p_element; ptr++)
    {
        if (*ptr != HEAD_GUARD_FILL)
        {
            NRF_LOG_INST_ERROR(p_pool->p_log,
                               "Detected Head Guard corruption at 0x%08X (0x%08X != 0x%08X)",
                               ptr, *ptr, HEAD_GUARD_FILL);
            APP_ERROR_CHECK_BOOL(false);
        }
    }

    for (uint32_t * ptr = ( p_tail - tail_words); ptr < p_tail; ptr++)
    {
        if (*ptr != TAIL_GUARD_FILL)
        {
            NRF_LOG_INST_ERROR(p_pool->p_log,
                               "Detected Tail Guard corruption at 0x%08X (0x%08X != 0x%08X)",
                               ptr, *ptr, TAIL_GUARD_FILL);
            APP_ERROR_CHECK_BOOL(false);
        }
    }

    if (NRF_BALLOC_DEBUG_DATA_TRASHING_CHECK_GET(p_pool->debug_flags))
    {
        for (uint32_t * ptr = p_head; ptr < p_tail; ptr++)
        {
            *ptr = FREE_MEM_FILL;
        }
    }

    return p_head;
}

#endif // NRF_BALLOC_CONFIG_DEBUG_ENABLED

/**@brief  Convert block index to a pointer.
 *
 * @param[in]   p_pool      Pointer to the memory pool.
 * @param[in]   idx         Index of the block.
 *
 * @return      Pointer to the beginning of the block.
 */
static void * nrf_balloc_idx2block(nrf_balloc_t const * p_pool, uint8_t idx)
{
    ASSERT(p_pool != NULL);
    return (uint8_t *)(p_pool->p_memory_begin) + ((size_t)(idx) * p_pool->block_size);
}

/**@brief  Convert block pointer to index.
 *
 * @param[in]   p_pool      Pointer to the memory pool.
 * @param[in]   p_block     Pointer to the beginning of the block.
 *
 * @return      Index of the block.
 */
static uint8_t nrf_balloc_block2idx(nrf_balloc_t const * p_pool, void const * p_block)
{
    ASSERT(p_pool != NULL);
    return ((size_t)(p_block) - (size_t)(p_pool->p_memory_begin)) / p_pool->block_size;
}

ret_code_t nrf_balloc_init(nrf_balloc_t const * p_pool)
{
    uint8_t pool_size;

    VERIFY_PARAM_NOT_NULL(p_pool);

    ASSERT(p_pool->p_cb);
    ASSERT(p_pool->p_stack_base);
    ASSERT(p_pool->p_stack_limit);
    ASSERT(p_pool->p_memory_begin);
    ASSERT(p_pool->block_size);

    pool_size       = p_pool->p_stack_limit - p_pool->p_stack_base;

#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
    void *p_memory_end = (uint8_t *)(p_pool->p_memory_begin) + (pool_size * p_pool->block_size);
    if (NRF_BALLOC_DEBUG_DATA_TRASHING_CHECK_GET(p_pool->debug_flags))
    {
        for (uint32_t * ptr = p_pool->p_memory_begin; ptr < (uint32_t *)(p_memory_end); ptr++)
        {
            *ptr = FREE_MEM_FILL;
        }
    }
#endif

    NRF_LOG_INST_INFO(p_pool->p_log, "Initialized (size: %u x %u = %u bytes)",
                      pool_size,
                      p_pool->block_size,
                      pool_size * p_pool->block_size);

    p_pool->p_cb->p_stack_pointer = p_pool->p_stack_base;
    while (pool_size--)
    {
        *(p_pool->p_cb->p_stack_pointer)++ = pool_size;
    }

    p_pool->p_cb->max_utilization = 0;

    return NRF_SUCCESS;
}

void * nrf_balloc_alloc(nrf_balloc_t const * p_pool)
{
    ASSERT(p_pool != NULL);

    void * p_block = NULL;

    CRITICAL_REGION_ENTER();

    if (p_pool->p_cb->p_stack_pointer > p_pool->p_stack_base)
    {
        // Allocate block.
        p_block = nrf_balloc_idx2block(p_pool, *--(p_pool->p_cb->p_stack_pointer));

        // Update utilization statistics.
        uint8_t utilization = p_pool->p_stack_limit - p_pool->p_cb->p_stack_pointer;
        if (p_pool->p_cb->max_utilization < utilization)
        {
            p_pool->p_cb->max_utilization = utilization;
        }
    }

    CRITICAL_REGION_EXIT();

#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
    if (p_block != NULL)
    {
        p_block = nrf_balloc_block_unwrap(p_pool, p_block);
    }
#endif

    NRF_LOG_INST_DEBUG(p_pool->p_log, "Allocating element: 0x%08X", p_block);

    return p_block;
}

void nrf_balloc_free(nrf_balloc_t const * p_pool, void * p_element)
{
    ASSERT(p_pool != NULL);
    ASSERT(p_element != NULL)

    NRF_LOG_INST_DEBUG(p_pool->p_log, "Freeing element: 0x%08X", p_element);

#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
    void * p_block = nrf_balloc_element_wrap(p_pool, p_element);

    // These checks could be done outside critical region as they use only pool configuration data.
    if (NRF_BALLOC_DEBUG_BASIC_CHECKS_GET(p_pool->debug_flags))
    {
        uint8_t pool_size  = p_pool->p_stack_limit - p_pool->p_stack_base;
        void *p_memory_end = (uint8_t *)(p_pool->p_memory_begin) + (pool_size * p_pool->block_size);

        // Check if the element belongs to this pool.
        if ((p_block < p_pool->p_memory_begin) || (p_block >= p_memory_end))
        {
            NRF_LOG_INST_ERROR(p_pool->p_log,
                              "Attempted to free element (0x%08X) that does not belong to the pool.",
                              p_element);
            APP_ERROR_CHECK_BOOL(false);
        }

        // Check if the pointer is valid.
        if ((((size_t)(p_block) - (size_t)(p_pool->p_memory_begin)) % p_pool->block_size) != 0)
        {
            NRF_LOG_INST_ERROR(p_pool->p_log,
                               "Attempted to free corrupted element address (0x%08X).", p_element);
            APP_ERROR_CHECK_BOOL(false);
        }
    }
#else
    void * p_block = p_element;
#endif // NRF_BALLOC_CONFIG_DEBUG_ENABLED

    CRITICAL_REGION_ENTER();

#if NRF_BALLOC_CONFIG_DEBUG_ENABLED
    // These checks have to be done in critical region as they use p_pool->p_stack_pointer.
    if (NRF_BALLOC_DEBUG_BASIC_CHECKS_GET(p_pool->debug_flags))
    {
        // Check for allocated/free ballance.
        if (p_pool->p_cb->p_stack_pointer >= p_pool->p_stack_limit)
        {
            NRF_LOG_INST_ERROR(p_pool->p_log,
                               "Attempted to free an element (0x%08X) while the pool is full.",
                               p_element);
            APP_ERROR_CHECK_BOOL(false);
        }
    }

    if (NRF_BALLOC_DEBUG_DOUBLE_FREE_CHECK_GET(p_pool->debug_flags))
    {
        // Check for double free.
        for (uint8_t * p_idx = p_pool->p_stack_base; p_idx < p_pool->p_cb->p_stack_pointer; p_idx++)
        {
            if (nrf_balloc_idx2block(p_pool, *p_idx) == p_block)
            {
                NRF_LOG_INST_ERROR(p_pool->p_log, "Attempted to double-free an element (0x%08X).",
                                   p_element);
                APP_ERROR_CHECK_BOOL(false);
            }
        }
    }
#endif // NRF_BALLOC_CONFIG_DEBUG_ENABLED

    // Free the element.
    *(p_pool->p_cb->p_stack_pointer)++ = nrf_balloc_block2idx(p_pool, p_block);

    CRITICAL_REGION_EXIT();
}

#endif // NRF_MODULE_ENABLED(NRF_BALLOC)
