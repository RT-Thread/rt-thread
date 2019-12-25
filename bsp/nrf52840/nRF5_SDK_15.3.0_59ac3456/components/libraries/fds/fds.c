/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(FDS)
#include "fds.h"
#include "fds_internal_defs.h"

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "nrf_error.h"
#include "nrf_atomic.h"
#include "nrf_atfifo.h"

#include "nrf_fstorage.h"
#if (FDS_BACKEND == NRF_FSTORAGE_SD)
#include "nrf_fstorage_sd.h"
#elif (FDS_BACKEND == NRF_FSTORAGE_NVMC)
#include "nrf_fstorage_nvmc.h"
#else
#error Invalid FDS backend.
#endif

#if (FDS_CRC_CHECK_ON_READ)
#include "crc16.h"
#endif


static void fs_event_handler(nrf_fstorage_evt_t * evt);

NRF_FSTORAGE_DEF(nrf_fstorage_t m_fs) =
{
    // The flash area boundaries are set in fds_init().
    .evt_handler = fs_event_handler,
};

// Internal status flags.
static struct
{
    bool volatile     initialized;
    nrf_atomic_flag_t initializing;
} m_flags;

// The number of queued operations.
// Incremented by queue_start() and decremented by queue_has_next().
static nrf_atomic_u32_t  m_queued_op_cnt;

// The number of registered users and their callback functions.
static nrf_atomic_u32_t     m_users;
static fds_cb_t             m_cb_table[FDS_MAX_USERS];

// The latest (largest) record ID written so far.
static nrf_atomic_u32_t     m_latest_rec_id;

// Queue of fds operations.
NRF_ATFIFO_DEF(m_queue, fds_op_t, FDS_OP_QUEUE_SIZE);

// Structures used to hold informations about virtual pages.
static fds_page_t           m_pages[FDS_DATA_PAGES];
static fds_swap_page_t      m_swap_page;

// Garbage collection data.
static fds_gc_data_t        m_gc;


static void event_send(fds_evt_t const * const p_evt)
{
    for (uint32_t user = 0; user < FDS_MAX_USERS; user++)
    {
        if (m_cb_table[user] != NULL)
        {
            m_cb_table[user](p_evt);
        }
    }
}


static void event_prepare(fds_op_t const * const p_op, fds_evt_t * const p_evt)
{
    switch (p_op->op_code)
    {
        case FDS_OP_INIT:
            p_evt->id = FDS_EVT_INIT;
            break;

        case FDS_OP_WRITE:
            p_evt->id                      = FDS_EVT_WRITE;
            p_evt->write.file_id           = p_op->write.header.file_id;
            p_evt->write.record_key        = p_op->write.header.record_key;
            p_evt->write.record_id         = p_op->write.header.record_id;
            p_evt->write.is_record_updated = 0;
            break;

        case FDS_OP_UPDATE:
            p_evt->id                      = FDS_EVT_UPDATE;
            p_evt->write.file_id           = p_op->write.header.file_id;
            p_evt->write.record_key        = p_op->write.header.record_key;
            p_evt->write.record_id         = p_op->write.header.record_id;
            p_evt->write.is_record_updated = (p_op->write.step == FDS_OP_WRITE_DONE);
            break;

        case FDS_OP_DEL_RECORD:
            p_evt->id             = FDS_EVT_DEL_RECORD;
            p_evt->del.file_id    = p_op->del.file_id;
            p_evt->del.record_key = p_op->del.record_key;
            p_evt->del.record_id  = p_op->del.record_to_delete;
            break;

        case FDS_OP_DEL_FILE:
            p_evt->id             = FDS_EVT_DEL_FILE;
            p_evt->del.file_id    = p_op->del.file_id;
            p_evt->del.record_key = FDS_RECORD_KEY_DIRTY;
            p_evt->del.record_id  = 0;
            break;

        case FDS_OP_GC:
            p_evt->id = FDS_EVT_GC;
            break;

        default:
            // Should not happen.
            break;
    }
}


static bool header_has_next(fds_header_t const * p_hdr, uint32_t const * p_page_end)
{
    uint32_t const * const p_hdr32 = (uint32_t*)p_hdr;
    return (   ( p_hdr32 <  p_page_end)
            && (*p_hdr32 != FDS_ERASED_WORD));  // Check last to be on the safe side (dereference)
}


// Jump to the next header.
static fds_header_t const * header_jump(fds_header_t const * const p_hdr)
{
    return (fds_header_t*)((uint32_t*)p_hdr + FDS_HEADER_SIZE + p_hdr->length_words);
}


static fds_header_status_t header_check(fds_header_t const * p_hdr, uint32_t const * p_page_end)
{
    if (((uint32_t*)header_jump(p_hdr) > p_page_end))
    {
        // The length field would jump across the page boundary.
        // FDS won't allow writing such a header, therefore it has been corrupted.
        return FDS_HEADER_CORRUPT;
    }

    if (   (p_hdr->file_id    == FDS_FILE_ID_INVALID)
        || (p_hdr->record_key == FDS_RECORD_KEY_DIRTY))
    {
        return FDS_HEADER_DIRTY;
    }

    return FDS_HEADER_VALID;
}


static bool address_is_valid(uint32_t const * const p_addr)
{
    return ((p_addr != NULL) &&
            (p_addr >= (uint32_t*)m_fs.start_addr) &&
            (p_addr <= (uint32_t*)m_fs.end_addr)   &&
            (is_word_aligned(p_addr)));
}


// Reads a page tag, and determines if the page is used to store data or as swap.
static fds_page_type_t page_identify(uint32_t const * const p_page_addr)
{
    if (   (p_page_addr == NULL)    // Should never happen.
        || (p_page_addr[FDS_PAGE_TAG_WORD_0] != FDS_PAGE_TAG_MAGIC))
    {
        return FDS_PAGE_UNDEFINED;
    }

    switch (p_page_addr[FDS_PAGE_TAG_WORD_1])
    {
        case FDS_PAGE_TAG_SWAP:
            return FDS_PAGE_SWAP;

        case FDS_PAGE_TAG_DATA:
            return FDS_PAGE_DATA;

        default:
            return FDS_PAGE_UNDEFINED;
    }
}


static bool page_is_erased(uint32_t const * const p_page_addr)
{
    for (uint32_t i = 0; i < FDS_PAGE_SIZE; i++)
    {
        if (*(p_page_addr + i) != FDS_ERASED_WORD)
        {
            return false;
        }
    }

    return true;
}


// NOTE: Must be called from within a critical section.
static bool page_has_space(uint16_t page, uint16_t length_words)
{
    length_words += m_pages[page].write_offset;
    length_words += m_pages[page].words_reserved;
    return (length_words < FDS_PAGE_SIZE);
}


// Given a pointer to a record, find the index of the page on which it is stored.
// Returns FDS_SUCCESS if the page is found, FDS_ERR_NOT_FOUND otherwise.
static ret_code_t page_from_record(uint16_t * const p_page, uint32_t const * const p_rec)
{
    ret_code_t ret = FDS_ERR_NOT_FOUND;

    CRITICAL_SECTION_ENTER();
    for (uint16_t i = 0; i < FDS_DATA_PAGES; i++)
    {
        if ((p_rec > m_pages[i].p_addr) &&
            (p_rec < m_pages[i].p_addr + FDS_PAGE_SIZE))
        {
            ret     = FDS_SUCCESS;
            *p_page = i;
            break;
        }
    }
    CRITICAL_SECTION_EXIT();

    return ret;
}


// Scan a page to determine how many words have been written to it.
// This information is used to set the page write offset during initialization.
// Additionally, this function updates the latest record ID as it proceeds.
// If an invalid record header is found, the can_gc argument is set to true.
static void page_scan(uint32_t const *       p_addr,
                      uint16_t       * const words_written,
                      bool           * const can_gc)
{
    uint32_t const * const p_page_end = p_addr + FDS_PAGE_SIZE;

    p_addr         += FDS_PAGE_TAG_SIZE;
    *words_written  = FDS_PAGE_TAG_SIZE;

    fds_header_t const * p_header = (fds_header_t*)p_addr;

    while (header_has_next(p_header, p_page_end))
    {
        fds_header_status_t hdr = header_check(p_header, p_page_end);

        if (hdr == FDS_HEADER_VALID)
        {
            // Update the latest (largest) record ID.
            if (p_header->record_id > m_latest_rec_id)
            {
                m_latest_rec_id = p_header->record_id;
            }
        }
        else
        {
            if (can_gc != NULL)
            {
                *can_gc = true;
            }

            if (hdr == FDS_HEADER_CORRUPT)
            {
                // It could happen that a record has a corrupt header which would set a
                // wrong offset for this page. In such cases, update this value to its maximum,
                // to ensure that no new records will be written to this page and to enable
                // correct statistics reporting by fds_stat().
                *words_written = FDS_PAGE_SIZE;

                // We can't continue to scan this page.
                return;
            }
        }

        *words_written += (FDS_HEADER_SIZE + p_header->length_words);
        p_header        = header_jump(p_header);
    }
}


static void page_offsets_update(fds_page_t * const p_page, fds_op_t const * p_op)
{
    // If the first part of the header has been written correctly, update the offset as normal.
    // Even if the record has not been written completely, fds is still able to continue normal
    // operation. Incomplete records will be deleted the next time garbage collection is run.
    // If we failed at the very beginning of the write operation, restore the offset
    // to the previous value so that no holes will be left in the flash.
    if (p_op->write.step > FDS_OP_WRITE_RECORD_ID)
    {
        p_page->write_offset += (FDS_HEADER_SIZE + p_op->write.header.length_words);
    }

    p_page->words_reserved -= (FDS_HEADER_SIZE + p_op->write.header.length_words);
}


// Tags a page as swap, i.e., reserved for GC.
static ret_code_t page_tag_write_swap(void)
{
    // The tag needs to be statically allocated since it is not buffered by fstorage.
    static uint32_t const page_tag_swap[] = {FDS_PAGE_TAG_MAGIC, FDS_PAGE_TAG_SWAP};
    return nrf_fstorage_write(&m_fs, (uint32_t)m_swap_page.p_addr, page_tag_swap, FDS_PAGE_TAG_SIZE * sizeof(uint32_t), NULL);
}


// Tags a page as data, i.e, ready for storage.
static ret_code_t page_tag_write_data(uint32_t const * const p_page_addr)
{
    // The tag needs to be statically allocated since it is not buffered by fstorage.
    static uint32_t const page_tag_data[] = {FDS_PAGE_TAG_MAGIC, FDS_PAGE_TAG_DATA};
    return nrf_fstorage_write(&m_fs, (uint32_t)p_page_addr, page_tag_data, FDS_PAGE_TAG_SIZE * sizeof(uint32_t), NULL);
}


// Reserve space on a page.
// NOTE: this function takes into the account the space required for the record header.
static ret_code_t write_space_reserve(uint16_t length_words, uint16_t * p_page)
{
    bool           space_reserved  = false;
    uint16_t const total_len_words = length_words + FDS_HEADER_SIZE;

    if (total_len_words >= FDS_PAGE_SIZE - FDS_PAGE_TAG_SIZE)
    {
        return FDS_ERR_RECORD_TOO_LARGE;
    }

    CRITICAL_SECTION_ENTER();
    for (uint16_t page = 0; page < FDS_DATA_PAGES; page++)
    {
        if ((m_pages[page].page_type == FDS_PAGE_DATA) &&
            (page_has_space(page, total_len_words)))
        {
            space_reserved = true;
            *p_page        = page;

            m_pages[page].words_reserved += total_len_words;
            break;
        }
    }
    CRITICAL_SECTION_EXIT();

    return (space_reserved) ? FDS_SUCCESS : FDS_ERR_NO_SPACE_IN_FLASH;
}


// Undo a write_space_reserve() call.
// NOTE: Must be called within a critical section.
static void write_space_free(uint16_t length_words, uint16_t page)
{
    m_pages[page].words_reserved -= (length_words + FDS_HEADER_SIZE);
}


static uint32_t record_id_new(void)
{
    return nrf_atomic_u32_add(&m_latest_rec_id, 1);
}


// Given a page and a record, find the next valid record on that page.
// If p_record is NULL, search from the beginning of the page,
// otherwise, resume searching from p_record.
// Return true if a record is found, false otherwise.
// If no record is found, p_record is unchanged.
static bool record_find_next(uint16_t page, uint32_t const ** p_record)
{
    uint32_t const * p_page_end = (m_pages[page].p_addr + FDS_PAGE_SIZE);

    // If this is the first call on this page, start searching from its beginning.
    // Otherwise, jump to the next record.
    fds_header_t const * p_header = (fds_header_t*)(*p_record);

    if (p_header != NULL)
    {
        p_header = header_jump(p_header);
    }
    else
    {
        p_header = (fds_header_t*)(m_pages[page].p_addr + FDS_PAGE_TAG_SIZE);
    }

    // Read records from the page until:
    // - a valid record is found or
    // - the last record on a page is found

    while (header_has_next(p_header, p_page_end))
    {
        switch (header_check(p_header, p_page_end))
        {
            case FDS_HEADER_VALID:
                *p_record = (uint32_t*)p_header;
                return true;

            case FDS_HEADER_DIRTY:
                p_header = header_jump(p_header);
                break;

            case FDS_HEADER_CORRUPT:
                // We can't reliably jump over this record.
                // There is nothing more we can do on this page.
                return false;
        }
    }

    // No more valid records on this page.
    return false;
}


// Find a record given its descriptor and retrive the page in which the record is stored.
// NOTE: Do not pass NULL as an argument for p_page.
static bool record_find_by_desc(fds_record_desc_t * const p_desc, uint16_t * const p_page)
{
    // If the gc_run_count field in the descriptor matches our counter, then the record has
    // not been moved. If the address is valid, and the record ID matches, there is no need
    // to find the record again. Only lookup the page in which the record is stored.

    if ((address_is_valid(p_desc->p_record))     &&
        (p_desc->gc_run_count == m_gc.run_count) &&
        (p_desc->record_id    == ((fds_header_t*)p_desc->p_record)->record_id))
    {
        return (page_from_record(p_page, p_desc->p_record) == FDS_SUCCESS);
    }

    // Otherwise, find the record in flash.
    for (*p_page = 0; *p_page < FDS_DATA_PAGES; (*p_page)++)
    {
        // Set p_record to NULL to make record_find_next() search from the beginning of the page.
        uint32_t const * p_record = NULL;

        while (record_find_next(*p_page, &p_record))
        {
            fds_header_t const * const p_header = (fds_header_t*)p_record;
            if (p_header->record_id == p_desc->record_id)
            {
                p_desc->p_record     = p_record;
                p_desc->gc_run_count = m_gc.run_count;
                return true;
            }
        }
    }

    return false;
}


// Search for a record and return its descriptor.
// If p_file_id is NULL, only the record key will be used for matching.
// If p_record_key is NULL, only the file ID will be used for matching.
// If both are NULL, it will iterate through all records.
static ret_code_t record_find(uint16_t          const * p_file_id,
                              uint16_t          const * p_record_key,
                              fds_record_desc_t       * p_desc,
                              fds_find_token_t        * p_token)
{
    if (!m_flags.initialized)
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_desc == NULL || p_token == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    // Begin (or resume) searching for a record.
    for (; p_token->page < FDS_DATA_PAGES; p_token->page++)
    {
        if (m_pages[p_token->page].page_type != FDS_PAGE_DATA)
        {
            // It might be that the page is FDS_PAGE_UNDEFINED.
            // Skip this page.
            continue;
        }

        while (record_find_next(p_token->page, &p_token->p_addr))
        {
            fds_header_t const * p_header = (fds_header_t*)p_token->p_addr;

            // A valid record was found, check its header for a match.
            if ((p_file_id != NULL) &&
                (p_header->file_id != *p_file_id))
            {
                continue;
            }

            if ((p_record_key != NULL) &&
                (p_header->record_key != *p_record_key))
            {
                continue;
            }

            // Record found; update the descriptor.
            p_desc->record_id    = p_header->record_id;
            p_desc->p_record     = p_token->p_addr;
            p_desc->gc_run_count = m_gc.run_count;

            return FDS_SUCCESS;
        }

        // We have scanned an entire page. Set the address in the token to NULL
        // so that it will be updated in the next iteration.
        p_token->p_addr = NULL;
    }

    return FDS_ERR_NOT_FOUND;
}


// Retrieve statistics about dirty records on a page.
static void records_stat(uint16_t   page,
                         uint16_t * p_valid_records,
                         uint16_t * p_dirty_records,
                         uint16_t * p_freeable_words,
                         bool     * p_corruption)
{
    fds_header_t const *       p_header   = (fds_header_t*)(m_pages[page].p_addr + FDS_PAGE_TAG_SIZE);
    uint32_t     const * const p_page_end = (m_pages[page].p_addr + FDS_PAGE_SIZE);

    while (header_has_next(p_header, p_page_end))
    {
        switch (header_check(p_header, p_page_end))
        {
            case FDS_HEADER_DIRTY:
                *p_dirty_records  += 1;
                *p_freeable_words += FDS_HEADER_SIZE + p_header->length_words;
                p_header = header_jump(p_header);
                break;

            case FDS_HEADER_VALID:
                *p_valid_records += 1;
                p_header = header_jump(p_header);
                break;

            case FDS_HEADER_CORRUPT:
            {
                *p_dirty_records  += 1;
                *p_freeable_words += (p_page_end - (uint32_t*)p_header);
                *p_corruption      = true;
                // We can't continue on this page.
                return;
            }

            default:
                break;
        }
    }
}


// Get a buffer on the queue of operations.
static fds_op_t * queue_buf_get(nrf_atfifo_item_put_t * p_iput_ctx)
{
    fds_op_t * const p_op = (fds_op_t*) nrf_atfifo_item_alloc(m_queue, p_iput_ctx);

    memset(p_op, 0x00, sizeof(fds_op_t));
    return p_op;
}


// Commit a buffer to the queue of operations.
static void queue_buf_store(nrf_atfifo_item_put_t * p_iput_ctx)
{
    (void) nrf_atfifo_item_put(m_queue, p_iput_ctx);
}


// Load the next operation from the queue.
static fds_op_t * queue_load(nrf_atfifo_item_get_t * p_iget_ctx)
{
    return (fds_op_t*) nrf_atfifo_item_get(m_queue, p_iget_ctx);
}


// Free the currently loaded operation.
static void queue_free(nrf_atfifo_item_get_t * p_iget_ctx)
{
    // Free the current queue element.
    (void) nrf_atfifo_item_free(m_queue, p_iget_ctx);
}


static bool queue_has_next(void)
{
    // Decrement the number of queued operations.
    ASSERT(m_queued_op_cnt != 0);
    return nrf_atomic_u32_sub(&m_queued_op_cnt, 1);
}


// This function is called during initialization to setup the page structure (m_pages) and
// provide additional information regarding eventual further initialization steps.
static fds_init_opts_t pages_init(void)
{
    uint32_t ret                    = NO_PAGES;
    uint16_t page                   = 0;
    uint16_t total_pages_available  = FDS_VIRTUAL_PAGES;
    bool     swap_set_but_not_found = false;

    for (uint16_t i = 0; i < FDS_VIRTUAL_PAGES; i++)
    {
        uint32_t        const * const p_page_addr = (uint32_t*)m_fs.start_addr + (i * FDS_PAGE_SIZE);
        fds_page_type_t const         page_type   = page_identify(p_page_addr);

        switch (page_type)
        {
            case FDS_PAGE_UNDEFINED:
            {
                if (page_is_erased(p_page_addr))
                {
                    if (m_swap_page.p_addr != NULL)
                    {
                        // If a swap page is already set, flag the page as erased (in m_pages)
                        // and try to tag it as data (in flash) later on during initialization.
                        m_pages[page].page_type    = FDS_PAGE_ERASED;
                        m_pages[page].p_addr       = p_page_addr;
                        m_pages[page].write_offset = FDS_PAGE_TAG_SIZE;

                        // This is a candidate for a potential new swap page, in case the
                        // current swap is going to be promoted to complete a GC instance.
                        m_gc.cur_page = page;
                        page++;
                    }
                    else
                    {
                        // If there is no swap page yet, use this one.
                        m_swap_page.p_addr       = p_page_addr;
                        m_swap_page.write_offset = FDS_PAGE_TAG_SIZE;
                        swap_set_but_not_found   = true;
                    }

                    ret |= PAGE_ERASED;
                }
                else
                {
                    // The page contains non-FDS data.
                    // Do not initialize or use this page.
                    total_pages_available--;
                    m_pages[page].p_addr    = p_page_addr;
                    m_pages[page].page_type = FDS_PAGE_UNDEFINED;
                    page++;
                }
            } break;

            case FDS_PAGE_DATA:
            {
                m_pages[page].page_type = FDS_PAGE_DATA;
                m_pages[page].p_addr    = p_page_addr;

                // Scan the page to compute its write offset and determine whether or not the page
                // can be garbage collected. Additionally, update the latest kwown record ID.
                page_scan(p_page_addr, &m_pages[page].write_offset, &m_pages[page].can_gc);

                ret |= PAGE_DATA;
                page++;
            } break;

            case FDS_PAGE_SWAP:
            {
                if (swap_set_but_not_found)
                {
                    m_pages[page].page_type    = FDS_PAGE_ERASED;
                    m_pages[page].p_addr       = m_swap_page.p_addr;
                    m_pages[page].write_offset = FDS_PAGE_TAG_SIZE;

                    page++;
                }

                m_swap_page.p_addr = p_page_addr;
                // If the swap is promoted, this offset should be kept, otherwise,
                // it should be set to FDS_PAGE_TAG_SIZE.
                page_scan(p_page_addr, &m_swap_page.write_offset, NULL);

                ret |= (m_swap_page.write_offset == FDS_PAGE_TAG_SIZE) ?
                        PAGE_SWAP_CLEAN : PAGE_SWAP_DIRTY;
            } break;

            default:
                // Shouldn't happen.
                break;
        }
    }

    if (total_pages_available < 2)
    {
        ret &= NO_PAGES;
    }

    return (fds_init_opts_t)ret;
}


// Write the first part of a record header (the key and length).
static ret_code_t record_header_write_begin(fds_op_t * const p_op, uint32_t * const p_addr)
{
    ret_code_t ret;

    // Write the record ID next.
    p_op->write.step = FDS_OP_WRITE_RECORD_ID;

    ret = nrf_fstorage_write(&m_fs, (uint32_t)(p_addr + FDS_OFFSET_TL),
        &p_op->write.header.record_key, FDS_HEADER_SIZE_TL * sizeof(uint32_t), NULL);

    return (ret == NRF_SUCCESS) ? FDS_SUCCESS : FDS_ERR_BUSY;
}


static ret_code_t record_header_write_id(fds_op_t * const p_op, uint32_t * const p_addr)
{
    ret_code_t ret;

    // If this record has no data, write the last part of the header directly.
    // Otherwise, write the record data next.
    p_op->write.step = (p_op->write.p_data != NULL) ?
                        FDS_OP_WRITE_DATA : FDS_OP_WRITE_HEADER_FINALIZE;

    ret = nrf_fstorage_write(&m_fs, (uint32_t)(p_addr + FDS_OFFSET_ID),
        &p_op->write.header.record_id, FDS_HEADER_SIZE_ID * sizeof(uint32_t), NULL);

    return (ret == NRF_SUCCESS) ? FDS_SUCCESS : FDS_ERR_BUSY;
}


static ret_code_t record_header_write_finalize(fds_op_t * const p_op, uint32_t * const p_addr)
{
    ret_code_t ret;

    // If this is a simple write operation, then this is the last step.
    // If this is an update instead, delete the old record next.
    p_op->write.step = (p_op->op_code == FDS_OP_UPDATE) ?
                        FDS_OP_WRITE_FLAG_DIRTY : FDS_OP_WRITE_DONE;

    ret = nrf_fstorage_write(&m_fs, (uint32_t)(p_addr + FDS_OFFSET_IC),
        &p_op->write.header.file_id, FDS_HEADER_SIZE_IC * sizeof(uint32_t), NULL);

    return (ret == NRF_SUCCESS) ? FDS_SUCCESS : FDS_ERR_BUSY;
}


static ret_code_t record_header_flag_dirty(uint32_t * const p_record, uint16_t page_to_gc)
{
    // Used to flag a record as dirty, i.e. ready for garbage collection.
    // Must be statically allocated since it will be written to flash.
    __ALIGN(4) static uint32_t const dirty_header = {0xFFFF0000};

    // Flag the record as dirty.
    ret_code_t ret;

    ret = nrf_fstorage_write(&m_fs, (uint32_t)p_record,
        &dirty_header, FDS_HEADER_SIZE_TL * sizeof(uint32_t), NULL);

    if (ret != NRF_SUCCESS)
    {
        return FDS_ERR_BUSY;
    }

    m_pages[page_to_gc].can_gc = true;

    return FDS_SUCCESS;
}


static ret_code_t record_find_and_delete(fds_op_t * const p_op)
{
    ret_code_t        ret;
    uint16_t          page;
    fds_record_desc_t desc = {0};

    desc.record_id = p_op->del.record_to_delete;

    if (record_find_by_desc(&desc, &page))
    {
        fds_header_t const * const p_header = (fds_header_t const *)desc.p_record;

        // Copy the record key and file ID, so that they can be returned in the event.
        // In case this function is run as part of an update, there is no need to copy
        // the file ID and record key since they are present in the header stored
        // in the queue element.

        p_op->del.file_id    = p_header->file_id;
        p_op->del.record_key = p_header->record_key;

        // Flag the record as dirty.
        ret = record_header_flag_dirty((uint32_t*)desc.p_record, page);
    }
    else
    {
        // The record never existed, or it has already been deleted.
        ret = FDS_ERR_NOT_FOUND;
    }

    return ret;
}


// Finds a record within a file and flags it as dirty.
static ret_code_t file_find_and_delete(fds_op_t * const p_op)
{
    ret_code_t        ret;
    fds_record_desc_t desc;

    // This token must persist across calls.
    static fds_find_token_t tok = {0};

    // Pass NULL to ignore the record key.
    ret = record_find(&p_op->del.file_id, NULL, &desc, &tok);

    if (ret == FDS_SUCCESS)
    {
         // A record was found: flag it as dirty.
        ret = record_header_flag_dirty((uint32_t*)desc.p_record, tok.page);
    }
    else // FDS_ERR_NOT_FOUND
    {
        // No more records were found. Zero the token, so that it can be reused.
        memset(&tok, 0x00, sizeof(fds_find_token_t));
    }

    return ret;
}


// Writes record data to flash.
static ret_code_t record_write_data(fds_op_t * const p_op, uint32_t * const p_addr)
{
    ret_code_t ret;

    p_op->write.step = FDS_OP_WRITE_HEADER_FINALIZE;

    ret = nrf_fstorage_write(&m_fs, (uint32_t)(p_addr + FDS_OFFSET_DATA),
        p_op->write.p_data,  p_op->write.header.length_words * sizeof(uint32_t), NULL);

    return (ret == NRF_SUCCESS) ? FDS_SUCCESS : FDS_ERR_BUSY;
}


#if (FDS_CRC_CHECK_ON_READ)
static bool crc_verify_success(uint16_t crc, uint16_t len_words, uint32_t const * const p_data)
{
    uint16_t computed_crc;

    // The CRC is computed on the entire record, except the CRC field itself.
    // The record header is 12 bytes, out of these we have to skip bytes 6 to 8 where the
    // CRC itself is stored. Then we compute the CRC for the rest of the record, from byte 8 of
    // the header (where the record ID begins) to the end of the record data.
    computed_crc = crc16_compute((uint8_t const *)p_data,  6, NULL);
    computed_crc = crc16_compute((uint8_t const *)p_data + 8,
                                 (FDS_HEADER_SIZE_ID + len_words) * sizeof(uint32_t),
                                 &computed_crc);

    return (computed_crc == crc);
}
#endif


static void gc_init(void)
{
    m_gc.run_count++;
    m_gc.cur_page = 0;
    m_gc.resume   = false;

    // Setup which pages to GC. Defer checking for open records and the can_gc flag,
    // as other operations might change those while GC is running.
    for (uint16_t i = 0; i < FDS_DATA_PAGES; i++)
    {
        m_gc.do_gc_page[i] = (m_pages[i].page_type == FDS_PAGE_DATA);
    }
}


// Obtain the next page to be garbage collected.
// Returns true if there are pages left to garbage collect, returns false otherwise.
static bool gc_page_next(uint16_t * const p_next_page)
{
    bool ret = false;

    for (uint16_t i = 0; i < FDS_DATA_PAGES; i++)
    {
        if (m_gc.do_gc_page[i])
        {
            // Do not attempt to GC this page again.
            m_gc.do_gc_page[i] = false;

            // Only GC pages with no open records and with some records which have been deleted.
            if ((m_pages[i].records_open == 0) && (m_pages[i].can_gc == true))
            {
                *p_next_page = i;
                ret = true;
                break;
            }
        }
    }

    return ret;
}


static ret_code_t gc_swap_erase(void)
{
    m_gc.state               = GC_DISCARD_SWAP;
    m_swap_page.write_offset = FDS_PAGE_TAG_SIZE;

    return nrf_fstorage_erase(&m_fs, (uint32_t)m_swap_page.p_addr, FDS_PHY_PAGES_IN_VPAGE, NULL);
}


// Erase the page being garbage collected, or erase the swap in case there are any open
// records on the page being garbage collected.
static ret_code_t gc_page_erase(void)
{
    uint32_t       ret;
    uint16_t const gc = m_gc.cur_page;

    if (m_pages[gc].records_open == 0)
    {
        m_gc.state = GC_ERASE_PAGE;

        ret = nrf_fstorage_erase(&m_fs, (uint32_t)m_pages[gc].p_addr, FDS_PHY_PAGES_IN_VPAGE, NULL);
    }
    else
    {
        // If there are open records, stop garbage collection on this page.
        // Discard the swap and try to garbage collect another page.
        ret = gc_swap_erase();
    }

    return ret;
}


// Copy the current record to swap.
static ret_code_t gc_record_copy(void)
{
    fds_header_t const * const p_header   = (fds_header_t*)m_gc.p_record_src;
    uint32_t     const * const p_dest     = m_swap_page.p_addr + m_swap_page.write_offset;
    uint16_t     const         record_len = FDS_HEADER_SIZE + p_header->length_words;

    m_gc.state = GC_COPY_RECORD;

    // Copy the record to swap; it is guaranteed to fit in the destination page,
    // so there is no need to check its size. This will either succeed or timeout.
    return nrf_fstorage_write(&m_fs, (uint32_t)p_dest, m_gc.p_record_src,
                              record_len * sizeof(uint32_t),
                              NULL);
}


static ret_code_t gc_record_find_next(void)
{
    ret_code_t ret;

    // Find the next valid record to copy.
    if (record_find_next(m_gc.cur_page, &m_gc.p_record_src))
    {
        ret = gc_record_copy();
    }
    else
    {
        // No more records left to copy on this page; swap pages.
        ret = gc_page_erase();
    }

    return ret;
}


// Promote the swap by tagging it as a data page.
static ret_code_t gc_swap_promote(void)
{
    m_gc.state = GC_PROMOTE_SWAP;
    return page_tag_write_data(m_pages[m_gc.cur_page].p_addr);
}


// Tag the page just garbage collected as swap.
static ret_code_t gc_tag_new_swap(void)
{
    m_gc.state        = GC_TAG_NEW_SWAP;
    m_gc.p_record_src = NULL;
    return page_tag_write_swap();
}


static ret_code_t gc_next_page(void)
{
    if (!gc_page_next(&m_gc.cur_page))
    {
        // No pages left to GC; GC has terminated. Reset the state.
        m_gc.state        = GC_BEGIN;
        m_gc.cur_page     = 0;
        m_gc.p_record_src = NULL;

        return FDS_OP_COMPLETED;
    }

    return gc_record_find_next();
}


// Update the swap page offeset after a record has been successfully copied to it.
static void gc_update_swap_offset(void)
{
    fds_header_t const * const p_header   = (fds_header_t*)m_gc.p_record_src;
    uint16_t     const         record_len = FDS_HEADER_SIZE + p_header->length_words;

    m_swap_page.write_offset += record_len;
}


static void gc_swap_pages(void)
{
    // The page being garbage collected will be the new swap page,
    // and the current swap will be used as a data page (promoted).
    uint32_t const * const p_addr = m_swap_page.p_addr;

    m_swap_page.p_addr            = m_pages[m_gc.cur_page].p_addr;
    m_pages[m_gc.cur_page].p_addr = p_addr;

    // Keep the offset for this page, but reset it for the swap.
    m_pages[m_gc.cur_page].write_offset = m_swap_page.write_offset;
    m_swap_page.write_offset            = FDS_PAGE_TAG_SIZE;
}


static void gc_state_advance(void)
{
    switch (m_gc.state)
    {
        case GC_BEGIN:
            gc_init();
            m_gc.state = GC_NEXT_PAGE;
            break;

        // A record was successfully copied.
        case GC_COPY_RECORD:
            gc_update_swap_offset();
            m_gc.state = GC_FIND_NEXT_RECORD;
            break;

        // A page was successfully erased. Prepare to promote the swap.
        case GC_ERASE_PAGE:
            gc_swap_pages();
            m_gc.state = GC_PROMOTE_SWAP;
            break;

        // Swap was discarded because the page being GC'ed had open records.
        case GC_DISCARD_SWAP:
        // Swap was successfully promoted.
        case GC_PROMOTE_SWAP:
            // Prepare to tag the page just GC'ed as swap.
            m_gc.state = GC_TAG_NEW_SWAP;
            break;

        case GC_TAG_NEW_SWAP:
            m_gc.state = GC_NEXT_PAGE;
            break;

        default:
            // Should not happen.
            break;
    }
}


// Initialize the filesystem.
static ret_code_t init_execute(uint32_t prev_ret, fds_op_t * const p_op)
{
    ret_code_t ret = FDS_ERR_INTERNAL;

    if (prev_ret != NRF_SUCCESS)
    {
        // A previous operation has timed out.
        m_flags.initializing = false;
        return FDS_ERR_OPERATION_TIMEOUT;
    }

    switch (p_op->init.step)
    {
        case FDS_OP_INIT_TAG_SWAP:
        {
            // The page write offset was determined previously by pages_init().
            p_op->init.step = FDS_OP_INIT_TAG_DATA;
            ret             = page_tag_write_swap();
        } break;

        case FDS_OP_INIT_TAG_DATA:
        {
            // Tag remaining erased pages as data.
            bool write_reqd = false;
            for (uint16_t i = 0; i < FDS_DATA_PAGES; i++)
            {
                if (m_pages[i].page_type == FDS_PAGE_ERASED)
                {
                    m_pages[i].page_type = FDS_PAGE_DATA;
                    write_reqd           = true;
                    ret = page_tag_write_data(m_pages[i].p_addr);
                    break;
                }
            }
            if (!write_reqd)
            {
                m_flags.initialized  = true;
                m_flags.initializing = false;
                return FDS_OP_COMPLETED;
            }
        } break;

        case FDS_OP_INIT_ERASE_SWAP:
        {
            // If the swap is going to be discarded then reset its write_offset.
            p_op->init.step          = FDS_OP_INIT_TAG_SWAP;
            m_swap_page.write_offset = FDS_PAGE_TAG_SIZE;

            ret = nrf_fstorage_erase(&m_fs, (uint32_t)m_swap_page.p_addr, FDS_PHY_PAGES_IN_VPAGE, NULL);
        } break;

        case FDS_OP_INIT_PROMOTE_SWAP:
        {
            p_op->init.step       = FDS_OP_INIT_TAG_SWAP;

            // When promoting the swap, keep the write_offset set by pages_init().
            ret = page_tag_write_data(m_swap_page.p_addr);

            uint16_t const         gc         = m_gc.cur_page;
            uint32_t const * const p_old_swap = m_swap_page.p_addr;

            // Execute the swap.
            m_swap_page.p_addr = m_pages[gc].p_addr;
            m_pages[gc].p_addr = p_old_swap;

            // Copy the offset from the swap to the new page.
            m_pages[gc].write_offset = m_swap_page.write_offset;
            m_swap_page.write_offset = FDS_PAGE_TAG_SIZE;

            m_pages[gc].page_type = FDS_PAGE_DATA;
        } break;

        default:
            // Should not happen.
            break;
    }

    if (ret != FDS_SUCCESS)
    {
        // fstorage queue was full.
        m_flags.initializing = false;
        return FDS_ERR_BUSY;
    }

    return FDS_OP_EXECUTING;
}


// Executes write and update operations.
static ret_code_t write_execute(uint32_t prev_ret, fds_op_t * const p_op)
{
    ret_code_t         ret;
    uint32_t   *       p_write_addr;
    fds_page_t * const p_page = &m_pages[p_op->write.page];

    // This must persist across calls.
    static fds_record_desc_t desc = {0};
    // When a record is updated, this variable will hold the page where the old
    // copy was stored. This will be used to set the can_gc flag when the header is
    // invalidated (FDS_OP_WRITE_FLAG_DIRTY).
    static uint16_t page;

    if (prev_ret != NRF_SUCCESS)
    {
        // The previous operation has timed out, update offsets.
        page_offsets_update(p_page, p_op);
        return FDS_ERR_OPERATION_TIMEOUT;
    }

    // Compute the address where to write data.
    p_write_addr = (uint32_t*)(p_page->p_addr + p_page->write_offset);

    // Execute the current step of the operation, and set one to be executed next.
    switch (p_op->write.step)
    {
        case FDS_OP_WRITE_FIND_RECORD:
        {
            // The first step of updating a record constists of locating the copy to be deleted.
            // If the old copy couldn't be found for any reason then the update should fail.
            // This prevents duplicates when queuing multiple updates of the same record.
            desc.p_record  = NULL;
            desc.record_id = p_op->write.record_to_delete;

            if (!record_find_by_desc(&desc, &page))
            {
                return FDS_ERR_NOT_FOUND;
            }
            // Setting the step is redundant since we are falling through.
        }
        // Fallthrough to FDS_OP_WRITE_HEADER_BEGIN.

        case FDS_OP_WRITE_HEADER_BEGIN:
            ret = record_header_write_begin(p_op, p_write_addr);
            break;

        case FDS_OP_WRITE_RECORD_ID:
            ret = record_header_write_id(p_op, p_write_addr);
            break;

        case FDS_OP_WRITE_DATA:
            ret = record_write_data(p_op, p_write_addr);
            break;

        case FDS_OP_WRITE_HEADER_FINALIZE:
            ret = record_header_write_finalize(p_op, p_write_addr);
            break;

        case FDS_OP_WRITE_FLAG_DIRTY:
            p_op->write.step = FDS_OP_WRITE_DONE;
            ret = record_header_flag_dirty((uint32_t*)desc.p_record, page);
            break;

        case FDS_OP_WRITE_DONE:
            ret = FDS_OP_COMPLETED;

#if (FDS_CRC_CHECK_ON_WRITE)
            if (!crc_verify_success(p_op->write.header.crc16,
                                    p_op->write.header.length_words,
                                    p_write_addr))
            {
                ret = FDS_ERR_CRC_CHECK_FAILED;
            }
#endif
            break;

        default:
            ret = FDS_ERR_INTERNAL;
            break;
    }

    // An operation has either completed or failed. It may have failed because fstorage
    // ran out of memory, or because the user tried to delete a record which did not exist.
    if (ret != FDS_OP_EXECUTING)
    {
        // There won't be another callback for this operation, so update the page offset now.
        page_offsets_update(p_page, p_op);
    }

    return ret;
}


static ret_code_t delete_execute(uint32_t prev_ret, fds_op_t * const p_op)
{
    ret_code_t ret;

    if (prev_ret != NRF_SUCCESS)
    {
        return FDS_ERR_OPERATION_TIMEOUT;
    }

    switch (p_op->del.step)
    {
        case FDS_OP_DEL_RECORD_FLAG_DIRTY:
            p_op->del.step = FDS_OP_DEL_DONE;
            ret = record_find_and_delete(p_op);
            break;

        case FDS_OP_DEL_FILE_FLAG_DIRTY:
            ret = file_find_and_delete(p_op);
            if (ret == FDS_ERR_NOT_FOUND)
            {
                // No more records could be found.
                // There won't be another callback for this operation, so return now.
                ret = FDS_OP_COMPLETED;
            }
            break;

        case FDS_OP_DEL_DONE:
            ret = FDS_OP_COMPLETED;
            break;

        default:
            ret = FDS_ERR_INTERNAL;
            break;
    }

    return ret;
}


static ret_code_t gc_execute(uint32_t prev_ret)
{
    ret_code_t ret;

    if (prev_ret != NRF_SUCCESS)
    {
        return FDS_ERR_OPERATION_TIMEOUT;
    }

    if (m_gc.resume)
    {
        m_gc.resume = false;
    }
    else
    {
        gc_state_advance();
    }

    switch (m_gc.state)
    {
        case GC_NEXT_PAGE:
            ret = gc_next_page();
            break;

        case GC_FIND_NEXT_RECORD:
            ret = gc_record_find_next();
            break;

        case GC_COPY_RECORD:
            ret = gc_record_copy();
            break;

        case GC_ERASE_PAGE:
            ret = gc_page_erase();
            break;

        case GC_PROMOTE_SWAP:
            ret = gc_swap_promote();
            break;

        case GC_TAG_NEW_SWAP:
            ret = gc_tag_new_swap();
            break;

        default:
            // Should not happen.
            ret = FDS_ERR_INTERNAL;
            break;
    }

    // Either FDS_OP_EXECUTING, FDS_OP_COMPLETED, FDS_ERR_BUSY or FDS_ERR_INTERNAL.
    return ret;
}


static void queue_process(ret_code_t result)
{
    static fds_op_t              * m_p_cur_op;  // Current fds operation.
    static nrf_atfifo_item_get_t   m_iget_ctx;  // Queue context for the current operation.

    while (true)
    {
        if (m_p_cur_op == NULL)
        {
            // Load the next from the queue if no operation is being executed.
            m_p_cur_op = queue_load(&m_iget_ctx);
        }

        /* We can reach here in three ways:
         * from queue_start(): something was just queued
         * from the fstorage event handler: an operation is being executed
         * looping: we only loop if there are operations still in the queue
         *
         * In all these three cases, m_p_cur_op != NULL.
         */
        ASSERT(m_p_cur_op != NULL);

        switch (m_p_cur_op->op_code)
        {
            case FDS_OP_INIT:
                result = init_execute(result, m_p_cur_op);
                break;

            case FDS_OP_WRITE:
            case FDS_OP_UPDATE:
                result = write_execute(result, m_p_cur_op);
                break;

            case FDS_OP_DEL_RECORD:
            case FDS_OP_DEL_FILE:
                result = delete_execute(result, m_p_cur_op);
                break;

            case FDS_OP_GC:
                result = gc_execute(result);
                break;

            default:
                result = FDS_ERR_INTERNAL;
                break;
        }

        if (result == FDS_OP_EXECUTING)
        {
            // The operation has not completed yet. Wait for the next system event.
            break;
        }

        // The operation has completed (either successfully or with an error).
        // - send an event to the user
        // - free the operation buffer
        // - execute any other queued operations

        fds_evt_t evt =
        {
            // The operation might have failed for one of the following reasons:
            // FDS_ERR_BUSY              - flash subsystem can't accept the operation
            // FDS_ERR_OPERATION_TIMEOUT - flash subsystem timed out
            // FDS_ERR_CRC_CHECK_FAILED  - a CRC check failed
            // FDS_ERR_NOT_FOUND         - no record found (delete/update)
            .result = (result == FDS_OP_COMPLETED) ? FDS_SUCCESS : result,
        };

        event_prepare(m_p_cur_op, &evt);
        event_send(&evt);

        // Zero the pointer to the current operation so that this function
        // will fetch a new one from the queue next time it is run.
        m_p_cur_op = NULL;

        // The result of the operation must be reset upon re-entering the loop to ensure
        // the next operation won't be affected by eventual errors in previous operations.
        result = NRF_SUCCESS;

        // Free the queue element used by the current operation.
        queue_free(&m_iget_ctx);

        if (!queue_has_next())
        {
            // No more elements left. Nothing to do.
            break;
        }
    }
}


static void queue_start(void)
{
    if (!nrf_atomic_u32_fetch_add(&m_queued_op_cnt, 1))
    {
        queue_process(NRF_SUCCESS);
    }
}


static void fs_event_handler(nrf_fstorage_evt_t * p_evt)
{
    queue_process(p_evt->result);
}


// Enqueues write and update operations.
static ret_code_t write_enqueue(fds_record_desc_t         * const p_desc,
                                fds_record_t        const * const p_record,
                                fds_reserve_token_t const * const p_tok,
                                fds_op_code_t                     op_code)
{
    ret_code_t              ret;
    uint16_t                page;
    uint16_t                crc          = 0;
    uint16_t                length_words = 0;
    fds_op_t              * p_op;
    nrf_atfifo_item_put_t   iput_ctx;

    if (!m_flags.initialized)
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_record == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    if ((p_record->file_id == FDS_FILE_ID_INVALID) ||
        (p_record->key     == FDS_RECORD_KEY_DIRTY))
    {
        return FDS_ERR_INVALID_ARG;
    }

    if (!is_word_aligned(p_record->data.p_data))
    {
        return FDS_ERR_UNALIGNED_ADDR;
    }

    // No space was previously reserved in flash for this operation.
    if (p_tok == NULL)
    {
        // Find a page where to write data.
        length_words = p_record->data.length_words;
        ret = write_space_reserve(length_words, &page);

        if (ret != FDS_SUCCESS)
        {
            // There is either not enough space in flash (FDS_ERR_NO_SPACE_IN_FLASH) or
            // the record exceeds the size of virtual page (FDS_ERR_RECORD_TOO_LARGE).
            return ret;
        }
    }
    else
    {
        page         = p_tok->page;
        length_words = p_tok->length_words;
    }

    // Get a buffer on the queue of operations.
    p_op = queue_buf_get(&iput_ctx);
    if (p_op == NULL)
    {
        CRITICAL_SECTION_ENTER();
        write_space_free(length_words, page);
        CRITICAL_SECTION_EXIT();
        return FDS_ERR_NO_SPACE_IN_QUEUES;
    }

    // Initialize the operation.
    p_op->op_code                   = op_code;
    p_op->write.step                = FDS_OP_WRITE_HEADER_BEGIN;
    p_op->write.page                = page;
    p_op->write.p_data              = p_record->data.p_data;
    p_op->write.header.record_id    = record_id_new();
    p_op->write.header.file_id      = p_record->file_id;
    p_op->write.header.record_key   = p_record->key;
    p_op->write.header.length_words = length_words;

    if (op_code == FDS_OP_UPDATE)
    {
        p_op->write.step             = FDS_OP_WRITE_FIND_RECORD;
        // Save the record ID of the record to be updated.
        p_op->write.record_to_delete = p_desc->record_id;
    }

#if (FDS_CRC_CHECK_ON_READ)
    // First, compute the CRC for the first 6 bytes of the header which contain the
    // record key, length and file ID, then, compute the CRC of the record ID (4 bytes).
    crc = crc16_compute((uint8_t*)&p_op->write.header,           6, NULL);
    crc = crc16_compute((uint8_t*)&p_op->write.header.record_id, 4, &crc);

    // Compute the CRC for the record data.
    crc = crc16_compute((uint8_t*)p_record->data.p_data,
                        p_record->data.length_words * sizeof(uint32_t), &crc);
#endif

    p_op->write.header.crc16 = crc;

    queue_buf_store(&iput_ctx);

     // Initialize the record descriptor, if provided.
    if (p_desc != NULL)
    {
        p_desc->p_record       = NULL;
        // Don't invoke record_id_new() again !
        p_desc->record_id      = p_op->write.header.record_id;
        p_desc->record_is_open = false;
        p_desc->gc_run_count   = m_gc.run_count;
    }

    // Start processing the queue, if necessary.
    queue_start();

    return FDS_SUCCESS;
}


ret_code_t fds_register(fds_cb_t cb)
{
    ret_code_t ret;

    if (m_users == FDS_MAX_USERS)
    {
        ret = FDS_ERR_USER_LIMIT_REACHED;
    }
    else
    {
        m_cb_table[m_users] = cb;
        (void) nrf_atomic_u32_add(&m_users, 1);

        ret = FDS_SUCCESS;
    }

    return ret;
}


static uint32_t flash_end_addr(void)
{
    uint32_t const bootloader_addr = BOOTLOADER_ADDRESS;
    uint32_t const page_sz         = NRF_FICR->CODEPAGESIZE;

#if defined(NRF52810_XXAA) || defined(NRF52811_XXAA)
    // Hardcode the number of flash pages, necessary for SoC emulation.
    // nRF52810 on nRF52832 and
    // nRF52811 on nRF52840
    uint32_t const code_sz = 48;
#else
   uint32_t const code_sz = NRF_FICR->CODESIZE;
#endif

    uint32_t end_addr = (bootloader_addr != 0xFFFFFFFF) ? bootloader_addr : (code_sz * page_sz);

    return end_addr - (FDS_PHY_PAGES_RESERVED * FDS_PHY_PAGE_SIZE * sizeof(uint32_t));
}


static void flash_bounds_set(void)
{
    uint32_t flash_size  = (FDS_PHY_PAGES * FDS_PHY_PAGE_SIZE * sizeof(uint32_t));
    m_fs.end_addr   = flash_end_addr();
    m_fs.start_addr = m_fs.end_addr - flash_size;
}


static ret_code_t flash_subsystem_init(void)
{
    flash_bounds_set();

    #if   (FDS_BACKEND == NRF_FSTORAGE_SD)
        return nrf_fstorage_init(&m_fs, &nrf_fstorage_sd, NULL);
    #elif (FDS_BACKEND == NRF_FSTORAGE_NVMC)
        return nrf_fstorage_init(&m_fs, &nrf_fstorage_nvmc, NULL);
    #else
        #error Invalid FDS_BACKEND.
    #endif
}


static void queue_init(void)
{
    (void) NRF_ATFIFO_INIT(m_queue);
}


ret_code_t fds_init(void)
{
    ret_code_t ret;
    fds_evt_t const evt_success =
    {
        .id     = FDS_EVT_INIT,
        .result = FDS_SUCCESS,
    };

    if (m_flags.initialized)
    {
        // No initialization is necessary. Notify the application immediately.
        event_send(&evt_success);
        return FDS_SUCCESS;
    }

    if (nrf_atomic_flag_set_fetch(&m_flags.initializing))
    {
        // If we were already initializing, return.
        return FDS_SUCCESS;
    }

    // Otherwise, the flag is set and we proceed to initialization.

    ret = flash_subsystem_init();
    if (ret != NRF_SUCCESS)
    {
        return ret;
    }

    queue_init();

    // Initialize the page structure (m_pages), and determine which
    // initialization steps are required given the current state of the filesystem.

    fds_init_opts_t init_opts = pages_init();

    switch (init_opts)
    {
        case NO_PAGES:
        case NO_SWAP:
            return FDS_ERR_NO_PAGES;

        case ALREADY_INSTALLED:
        {
            // No initialization is necessary. Notify the application immediately.
            m_flags.initialized  = true;
            m_flags.initializing = false;
            event_send(&evt_success);
            return FDS_SUCCESS;
        }

        default:
            break;
    }

    // A write operation is necessary to initialize the fileystem.

    nrf_atfifo_item_put_t iput_ctx;

    fds_op_t * p_op = queue_buf_get(&iput_ctx);
    if (p_op == NULL)
    {
        return FDS_ERR_NO_SPACE_IN_QUEUES;
    }

    p_op->op_code = FDS_OP_INIT;

    switch (init_opts)
    {
        case FRESH_INSTALL:
        case TAG_SWAP:
            p_op->init.step = FDS_OP_INIT_TAG_SWAP;
            break;

        case PROMOTE_SWAP:
        case PROMOTE_SWAP_INST:
            p_op->init.step = FDS_OP_INIT_PROMOTE_SWAP;
            break;

        case DISCARD_SWAP:
            p_op->init.step = FDS_OP_INIT_ERASE_SWAP;
            break;

        case TAG_DATA:
        case TAG_DATA_INST:
            p_op->init.step = FDS_OP_INIT_TAG_DATA;
            break;

        default:
            // Should not happen.
            break;
    }

    queue_buf_store(&iput_ctx);
    queue_start();

    return FDS_SUCCESS;
}


ret_code_t fds_record_open(fds_record_desc_t  * const p_desc,
                           fds_flash_record_t * const p_flash_rec)
{
    uint16_t page;

    if ((p_desc == NULL) || (p_flash_rec == NULL))
    {
        return FDS_ERR_NULL_ARG;
    }

    // Find the record if necessary.
    if (record_find_by_desc(p_desc, &page))
    {
        fds_header_t const * const p_header = (fds_header_t*)p_desc->p_record;

#if (FDS_CRC_CHECK_ON_READ)
        if (!crc_verify_success(p_header->crc16,
                                p_header->length_words,
                                p_desc->p_record))
        {
            return FDS_ERR_CRC_CHECK_FAILED;
        }
#endif

        (void) nrf_atomic_u32_add(&m_pages[page].records_open, 1);

        // Initialize p_flash_rec.
        p_flash_rec->p_header = p_header;
        p_flash_rec->p_data   = (p_desc->p_record + FDS_HEADER_SIZE);

        // Set the record as open in the descriptor.
        p_desc->record_is_open = true;

        return FDS_SUCCESS;
    }

    // The record could not be found.
    // It either never existed or it has been deleted.
    return FDS_ERR_NOT_FOUND;
}


ret_code_t fds_record_close(fds_record_desc_t * const p_desc)
{
    ret_code_t ret;
    uint16_t   page;

    if (p_desc == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    if (record_find_by_desc((fds_record_desc_t*)p_desc, &page))
    {
        CRITICAL_SECTION_ENTER();
        if ((m_pages[page].records_open > 0) && (p_desc->record_is_open))
        {

            m_pages[page].records_open--;
            p_desc->record_is_open = false;

            ret = FDS_SUCCESS;
        }
        else
        {
            ret = FDS_ERR_NO_OPEN_RECORDS;
        }
        CRITICAL_SECTION_EXIT();
    }
    else
    {
        ret = FDS_ERR_NOT_FOUND;
    }

    return ret;
}


ret_code_t fds_reserve(fds_reserve_token_t * const p_tok, uint16_t length_words)
{
    ret_code_t ret;
    uint16_t   page;

    if (!m_flags.initialized)
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_tok == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    ret = write_space_reserve(length_words, &page);

    if (ret == FDS_SUCCESS)
    {
        p_tok->page         = page;
        p_tok->length_words = length_words;
    }

    return ret;
}


ret_code_t fds_reserve_cancel(fds_reserve_token_t * const p_tok)
{
    ret_code_t ret;

    if (!m_flags.initialized)
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_tok == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    if (p_tok->page > FDS_DATA_PAGES)
    {
        // The page does not exist. This shouldn't happen.
        return FDS_ERR_INVALID_ARG;
    }

    fds_page_t const * const p_page = &m_pages[p_tok->page];

    CRITICAL_SECTION_ENTER();
    if ((FDS_HEADER_SIZE + p_tok->length_words) <= p_page->words_reserved)
    {
        // Free reserved space.
        write_space_free(p_tok->length_words, p_tok->page);

        // Clean the token.
        p_tok->page         = 0;
        p_tok->length_words = 0;
        ret = FDS_SUCCESS;
    }
    else
    {
        // We are trying to cancel a reservation of more words than how many are
        // currently reserved on the page. Clearly, this shouldn't happen.
        ret = FDS_ERR_INVALID_ARG;
    }
    CRITICAL_SECTION_EXIT();

    return ret;
}


ret_code_t fds_record_write(fds_record_desc_t       * const p_desc,
                            fds_record_t      const * const p_record)
{
    return write_enqueue(p_desc, p_record, NULL, FDS_OP_WRITE);
}


ret_code_t fds_record_write_reserved(fds_record_desc_t         * const p_desc,
                                     fds_record_t        const * const p_record,
                                     fds_reserve_token_t const * const p_tok)
{
    // A NULL token is not allowed when writing to a reserved space.
    if (p_tok == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    return write_enqueue(p_desc, p_record, p_tok, FDS_OP_WRITE);
}


ret_code_t fds_record_update(fds_record_desc_t       * const p_desc,
                             fds_record_t      const * const p_record)
{
    // A NULL descriptor is not allowed when updating a record.
    if (p_desc == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    return write_enqueue(p_desc, p_record, NULL, FDS_OP_UPDATE);
}


ret_code_t fds_record_delete(fds_record_desc_t * const p_desc)
{
    fds_op_t * p_op;
    nrf_atfifo_item_put_t iput_ctx;

    if (!m_flags.initialized)
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_desc == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    p_op = queue_buf_get(&iput_ctx);
    if (p_op == NULL)
    {
        return FDS_ERR_NO_SPACE_IN_QUEUES;
    }

    p_op->op_code              = FDS_OP_DEL_RECORD;
    p_op->del.step             = FDS_OP_DEL_RECORD_FLAG_DIRTY;
    p_op->del.record_to_delete = p_desc->record_id;

    queue_buf_store(&iput_ctx);
    queue_start();

    return FDS_SUCCESS;
}


ret_code_t fds_file_delete(uint16_t file_id)
{
    fds_op_t * p_op;
    nrf_atfifo_item_put_t iput_ctx;

    if (!m_flags.initialized)
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (file_id == FDS_FILE_ID_INVALID)
    {
        return FDS_ERR_INVALID_ARG;
    }

    p_op = queue_buf_get(&iput_ctx);
    if (p_op == NULL)
    {
        return FDS_ERR_NO_SPACE_IN_QUEUES;
    }

    p_op->op_code      = FDS_OP_DEL_FILE;
    p_op->del.step     = FDS_OP_DEL_FILE_FLAG_DIRTY;
    p_op->del.file_id  = file_id;

    queue_buf_store(&iput_ctx);
    queue_start();

    return FDS_SUCCESS;
}


ret_code_t fds_gc(void)
{
    fds_op_t * p_op;
    nrf_atfifo_item_put_t iput_ctx;

    if (!m_flags.initialized)
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    p_op = queue_buf_get(&iput_ctx);
    if (p_op == NULL)
    {
        return FDS_ERR_NO_SPACE_IN_QUEUES;
    }

    p_op->op_code = FDS_OP_GC;

    queue_buf_store(&iput_ctx);

    if (m_gc.state != GC_BEGIN)
    {
        // Resume GC by retrying the last step.
        m_gc.resume = true;
    }

    queue_start();

    return FDS_SUCCESS;
}


ret_code_t fds_record_iterate(fds_record_desc_t * const p_desc,
                              fds_find_token_t  * const p_token)
{
    return record_find(NULL, NULL, p_desc, p_token);
}


ret_code_t fds_record_find(uint16_t                  file_id,
                           uint16_t                  record_key,
                           fds_record_desc_t * const p_desc,
                           fds_find_token_t  * const p_token)
{
    return record_find(&file_id, &record_key, p_desc, p_token);
}


ret_code_t fds_record_find_by_key(uint16_t                  record_key,
                                  fds_record_desc_t * const p_desc,
                                  fds_find_token_t  * const p_token)
{
    return record_find(NULL, &record_key, p_desc, p_token);
}


ret_code_t fds_record_find_in_file(uint16_t                  file_id,
                                   fds_record_desc_t * const p_desc,
                                   fds_find_token_t  * const p_token)
{
    return record_find(&file_id, NULL, p_desc, p_token);
}


ret_code_t fds_descriptor_from_rec_id(fds_record_desc_t * const p_desc,
                                      uint32_t                  record_id)
{
    if (p_desc == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    // Zero the descriptor and set the record_id field.
    memset(p_desc, 0x00, sizeof(fds_record_desc_t));
    p_desc->record_id = record_id;

    return FDS_SUCCESS;
}


ret_code_t fds_record_id_from_desc(fds_record_desc_t const * const p_desc,
                                   uint32_t                * const p_record_id)
{
    if ((p_desc == NULL) || (p_record_id == NULL))
    {
        return FDS_ERR_NULL_ARG;
    }

    *p_record_id = p_desc->record_id;

    return FDS_SUCCESS;
}


ret_code_t fds_stat(fds_stat_t * const p_stat)
{
    uint16_t const words_in_page = FDS_PAGE_SIZE;
    // The largest number of free contiguous words on any page.
    uint16_t       contig_words  = 0;

    if (!m_flags.initialized)
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_stat == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    memset(p_stat, 0x00, sizeof(fds_stat_t));

    p_stat->pages_available = FDS_VIRTUAL_PAGES;

    for (uint16_t page = 0; page < FDS_DATA_PAGES; page++)
    {
        uint16_t const words_used = m_pages[page].write_offset + m_pages[page].words_reserved;

        if (page_identify(m_pages[page].p_addr) == FDS_PAGE_UNDEFINED)
        {
            p_stat->pages_available--;
        }

        p_stat->open_records   += m_pages[page].records_open;
        p_stat->words_reserved += m_pages[page].words_reserved;
        p_stat->words_used     += words_used;

        contig_words = (words_in_page - words_used);
        if (contig_words > p_stat->largest_contig)
        {
            p_stat->largest_contig = contig_words;
        }

        records_stat(page,
                     &p_stat->valid_records,
                     &p_stat->dirty_records,
                     &p_stat->freeable_words,
                     &p_stat->corruption);
    }

    return FDS_SUCCESS;
}

#endif //NRF_MODULE_ENABLED(FDS)
