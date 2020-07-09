/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(FSTORAGE)
#include "fstorage.h"
#include "fstorage_internal_defs.h"

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "nrf_error.h"
#include "nrf_soc.h"


static uint8_t       m_flags;       // fstorage status flags.
static fs_op_queue_t m_queue;       // Queue of requested operations.
static uint8_t       m_retry_count; // Number of times the last flash operation was retried.

// Sends events to the application.
static void send_event(fs_op_t const * const p_op, fs_ret_t result)
{
    fs_evt_t evt;
    memset(&evt, 0x00, sizeof(fs_evt_t));

    switch (p_op->op_code)
    {
        case FS_OP_STORE:
            evt.id                 = FS_EVT_STORE;
            evt.store.p_data       = p_op->store.p_dest;
            evt.store.length_words = p_op->store.length_words;
            break;

        case FS_OP_ERASE:
            evt.id               = FS_EVT_ERASE;
            evt.erase.first_page = p_op->erase.page - p_op->erase.pages_erased;
            evt.erase.last_page  = p_op->erase.page;
            break;

        default:
            // Should not happen.
            break;
    }
    evt.p_context = p_op->p_context;

    p_op->p_config->callback(&evt, result);
}


// Checks that a configuration is non-NULL and within section variable bounds.
static bool check_config(fs_config_t const * const config)
{
#ifndef DFU_SUPPORT_SIGNING
    if ((config != NULL) &&
        ((uint32_t)FS_SECTION_START_ADDR <= (uint32_t)config) &&
        ((uint32_t)FS_SECTION_END_ADDR   >  (uint32_t)config))
    {
        return true;
    }

    return false;
#else
    return true;
#endif
}


// Executes a store operation.
static uint32_t store_execute(fs_op_t const * const p_op)
{
    uint16_t chunk_len;

    if ((p_op->store.length_words - p_op->store.offset) < FS_MAX_WRITE_SIZE_WORDS)
    {
        chunk_len = p_op->store.length_words - p_op->store.offset;
    }
    else
    {
        chunk_len = FS_MAX_WRITE_SIZE_WORDS;
    }

    return sd_flash_write((uint32_t*)p_op->store.p_dest + p_op->store.offset,
                          (uint32_t*)p_op->store.p_src  + p_op->store.offset,
                          chunk_len);
}


// Executes an erase operation.
static uint32_t erase_execute(fs_op_t const * const p_op)
{
    return sd_flash_page_erase(p_op->erase.page);
}


// Advances the queue, wrapping around if necessary.
// If no elements are left in the queue, clears the FS_FLAG_PROCESSING flag.
static void queue_advance(void)
{
    if (--m_queue.count == 0)
    {
        m_flags &= ~FS_FLAG_PROCESSING;
    }

    if (++m_queue.rp == FS_QUEUE_SIZE)
    {
        m_queue.rp = 0;
    }
}


// Processes the current element in the queue. If the queue is empty, does nothing.
static void queue_process(void)
{
    uint32_t         ret;
    fs_op_t  * const p_op = &m_queue.op[m_queue.rp];

    if (m_queue.count > 0)
    {
        switch (p_op->op_code)
        {
            case FS_OP_STORE:
                ret = store_execute(p_op);
                break;

            case FS_OP_ERASE:
                ret = erase_execute(p_op);
                break;

             default:
                ret = FS_ERR_INTERNAL;
                break;
        }

        // There is a pending flash operation which was not initiated by this module.
        // Stop processing the queue and wait for a system event.
        if (ret == NRF_ERROR_BUSY)
        {
            m_flags &= ~FS_FLAG_PROCESSING;
            m_flags |= FS_FLAG_FLASH_REQ_PENDING;
        }
        else if (ret != NRF_SUCCESS)
        {
            // An error has occurred.
            send_event(p_op, FS_ERR_INTERNAL);
        }
        else
        {
            // Operation is executing.
        }
    }
}


// Starts processing the queue if there are no pending flash operations, both inside and
// outside this module. Returns immediately otherwise.
static void queue_start(void)
{
    if (!(m_flags & FS_FLAG_PROCESSING) &&
        !(m_flags & FS_FLAG_FLASH_REQ_PENDING))
    {
        m_flags |= FS_FLAG_PROCESSING;
        queue_process();
    }
}


// Flash operation success callback handler. Keeps track of the progress of an operation.
// If it has finished, advances the queue and notifies the application.
static void on_operation_success(fs_op_t * const p_op)
{
    m_retry_count = 0;

    switch (p_op->op_code)
    {
        case FS_OP_STORE:
        {
            uint16_t chunk_len;

            if ((p_op->store.length_words - p_op->store.offset) < FS_MAX_WRITE_SIZE_WORDS)
            {
                chunk_len = p_op->store.length_words - p_op->store.offset;
            }
            else
            {
                chunk_len = FS_MAX_WRITE_SIZE_WORDS;
            }

            p_op->store.offset += chunk_len;

            if (p_op->store.offset == p_op->store.length_words)
            {
                // The operation has finished.
                send_event(p_op, FS_SUCCESS);
                queue_advance();
            }
        }
        break;

        case FS_OP_ERASE:
        {
            p_op->erase.page++;
            p_op->erase.pages_erased++;

            if (p_op->erase.pages_erased == p_op->erase.pages_to_erase)
            {
                send_event(p_op, FS_SUCCESS);
                queue_advance();
            }
        }
        break;

        default:
            // Should not happen.
            break;
    }
}


// Flash operation failure callback handler. If the maximum number of retries has
// been reached, notifies the application and advances the queue.
static void on_operation_failure(fs_op_t const * const p_op)
{
    if (++m_retry_count > FS_OP_MAX_RETRIES)
    {
        m_retry_count = 0;

        send_event(p_op, FS_ERR_OPERATION_TIMEOUT);
        queue_advance();
    }
}


// Retrieves a pointer to the next free element in the queue.
// Additionally, increases the number of elements stored in the queue.
static bool queue_get_next_free(fs_op_t ** p_op)
{
    uint32_t idx;

    if (m_queue.count == FS_QUEUE_SIZE)
    {
        return false;
    }

    idx = ((m_queue.rp + m_queue.count) < FS_QUEUE_SIZE) ?
           (m_queue.rp + m_queue.count) : ((m_queue.rp + m_queue.count)-FS_QUEUE_SIZE);

    m_queue.count++;

    // Zero the element so that unassigned fields will be zero.
    memset(&m_queue.op[idx], 0x00, sizeof(fs_op_t));

    *p_op = &m_queue.op[idx];

    return true;
}


fs_ret_t fs_init(void)
{
    uint32_t const   total_users     = FS_SECTION_ITEM_COUNT;
    uint32_t         configs_to_init = FS_SECTION_ITEM_COUNT;
    uint32_t const * p_current_end   = FS_PAGE_END_ADDR;

    if (m_flags & FS_FLAG_INITIALIZED)
    {
        return FS_SUCCESS;
    }

    // Each fstorage user has registered one configuration.
    // The total number of users (and thus the total number of configurations) is
    // kept in total_users. Some of these users might have specified their flash
    // boundaries in their configurations. This function sets the flash boundaries
    // for the remaining user configurations without further user interaction.

    // First, determine how many user configurations this function has to initialize,
    // out of the total. This number will be kept in configs_to_init.

    for (uint32_t i = 0; i < total_users; i++)
    {
        fs_config_t const * const p_config = FS_SECTION_ITEM_GET(i);

        if ((p_config->p_start_addr != NULL) &&
            (p_config->p_end_addr   != NULL))
        {
            configs_to_init--;
        }
    }

    // For each configuration to initialize, assign flash space based on the priority
    // specified. Higher priority means a higher memory address.

    for (uint32_t i = 0; i < configs_to_init; i++)
    {
        fs_config_t * p_config_i   = FS_SECTION_ITEM_GET(i);
        uint8_t       max_priority = 0;
        uint8_t       max_index    = i;

        for (uint32_t j = 0; j < total_users; j++)
        {
            fs_config_t const * const p_config_j = FS_SECTION_ITEM_GET(j);

            #if 0
            if (p_config_j->priority == p_config_i->priority)
            {
                // Duplicated priorities are not allowed.
                return FS_ERR_INVALID_CFG;
            }
            #endif

            if ((p_config_j->p_start_addr != NULL) &&
                (p_config_j->p_end_addr   != NULL))
            {
                // When calculating the configuration with the next highest priority
                // skip configurations which were already set during a previous iteration.
                // This check needs to be here to prevent re-using the configurations
                // with higher priorities which we used in previous iterations.
                continue;
            }

            if (p_config_j->priority > max_priority)
            {
                max_priority = p_config_j->priority;
                max_index    = j;
            }
        }

        p_config_i = FS_SECTION_ITEM_GET(max_index);

        p_config_i->p_end_addr   = p_current_end;
        p_config_i->p_start_addr = p_current_end - (p_config_i->num_pages * FS_PAGE_SIZE_WORDS);

        p_current_end = p_config_i->p_start_addr;
    }

    m_flags |= FS_FLAG_INITIALIZED;

    return FS_SUCCESS;
}


fs_ret_t fs_fake_init(void)
{
    m_flags |= FS_FLAG_INITIALIZED;
    return FS_SUCCESS;
}


fs_ret_t fs_store(fs_config_t const * const p_config,
                  uint32_t    const * const p_dest,
                  uint32_t    const * const p_src,
                  uint16_t    const         length_words,
                  void *                    p_context)
{
    fs_op_t * p_op;

    if (!(m_flags & FS_FLAG_INITIALIZED))
    {
        return FS_ERR_NOT_INITIALIZED;
    }

    if (!check_config(p_config))
    {
        return FS_ERR_INVALID_CFG;
    }

    if ((p_src == NULL) || (p_dest == NULL))
    {
        return FS_ERR_NULL_ARG;
    }

    // Check that both pointers are word aligned.
    if (((uint32_t)p_src  & 0x03) ||
        ((uint32_t)p_dest & 0x03))
    {
        return FS_ERR_UNALIGNED_ADDR;
    }

    // Check that the operation doesn't go outside the client's memory boundaries.
    if ((p_config->p_start_addr > p_dest) ||
        (p_config->p_end_addr   < (p_dest + length_words)))
    {
        return FS_ERR_INVALID_ADDR;
    }

    if (length_words == 0)
    {
        return FS_ERR_INVALID_ARG;
    }

    if (!queue_get_next_free(&p_op))
    {
        return FS_ERR_QUEUE_FULL;
    }

    // Initialize the operation.
    p_op->p_context          = p_context;
    p_op->p_config           = p_config;
    p_op->op_code            = FS_OP_STORE;
    p_op->store.p_src        = p_src;
    p_op->store.p_dest       = p_dest;
    p_op->store.length_words = length_words;

    queue_start();

    return FS_SUCCESS;
}


fs_ret_t fs_erase(fs_config_t const * const p_config,
                  uint32_t    const * const p_page_addr,
                  uint16_t    const         num_pages,
                  void *                    p_context)
{
    fs_op_t * p_op;

    if (!(m_flags & FS_FLAG_INITIALIZED))
    {
        return FS_ERR_NOT_INITIALIZED;
    }

    if (!check_config(p_config))
    {
        return FS_ERR_INVALID_CFG;
    }

    if (p_page_addr == NULL)
    {
        return FS_ERR_NULL_ARG;
    }

    // Check that the page is aligned to a page boundary.
    if (((uint32_t)p_page_addr & (FS_PAGE_SIZE-1)) != 0)
    {
        return FS_ERR_UNALIGNED_ADDR;
    }

    // Check that the operation doesn't go outside the client's memory boundaries.
    if ((p_page_addr < p_config->p_start_addr) ||
        (p_page_addr + (FS_PAGE_SIZE_WORDS * num_pages) > p_config->p_end_addr))
    {
        return FS_ERR_INVALID_ADDR;
    }

    if (num_pages == 0)
    {
        return FS_ERR_INVALID_ARG;
    }

    if (!queue_get_next_free(&p_op))
    {
        return FS_ERR_QUEUE_FULL;
    }

    // Initialize the operation.
    p_op->p_context            = p_context;
    p_op->p_config             = p_config;
    p_op->op_code              = FS_OP_ERASE;
    p_op->erase.page           = ((uint32_t)p_page_addr / FS_PAGE_SIZE);
    p_op->erase.pages_to_erase = num_pages;

    queue_start();

    return FS_SUCCESS;
}


fs_ret_t fs_queued_op_count_get(uint32_t * const p_op_count)
{
    if (p_op_count == NULL)
    {
        return FS_ERR_NULL_ARG;
    }

    *p_op_count = m_queue.count;

    return FS_SUCCESS;
}


void fs_sys_event_handler(uint32_t sys_evt)
{
    fs_op_t * const p_op = &m_queue.op[m_queue.rp];

    if (m_flags & FS_FLAG_PROCESSING)
    {
        // A flash operation was initiated by this module. Handle the result.
        switch (sys_evt)
        {
            case NRF_EVT_FLASH_OPERATION_SUCCESS:
                on_operation_success(p_op);
                break;

            case NRF_EVT_FLASH_OPERATION_ERROR:
                on_operation_failure(p_op);
                break;
        }
    }
    else if ((m_flags & FS_FLAG_FLASH_REQ_PENDING))
    {
        // A flash operation was initiated outside this module.
        // A callback which indicates that it has finished was received.
        m_flags &= ~FS_FLAG_FLASH_REQ_PENDING;

        // If there are any elements left in the queue, set FS_FLAG_PROCESSING.
        if (m_queue.count > 0)
        {
           m_flags |= FS_FLAG_PROCESSING;
        }
    }

    // Resume processing the queue, if necessary.
    queue_process();
}

bool fs_queue_is_full(void)
{
    return (m_queue.count == FS_QUEUE_SIZE);
}

bool fs_queue_is_empty(void)
{
    return (m_queue.count == 0);
}

#endif //NRF_MODULE_ENABLED(FSTORAGE)
