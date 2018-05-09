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
#if NRF_MODULE_ENABLED(FDS)
#include "fds.h"
#include "fds_internal_defs.h"

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "fstorage.h"
#include "nrf_error.h"

#if defined(FDS_CRC_ENABLED)
    #include "crc16.h"
#endif


static void fs_event_handler(fs_evt_t const * const evt, fs_ret_t result);

// Our fstorage configuration.
FS_REGISTER_CFG(fs_config_t fs_config) =
{
    .callback  = fs_event_handler,
    .num_pages = FDS_PHY_PAGES,
    // We register with the highest priority in order to be assigned
    // the pages with the highest memory address (closest to the bootloader).
    .priority  = 0xFF
};

// Used to flag a record as dirty, i.e. ready for garbage collection.
// Must be statically allocated since it will be written to flash.
__ALIGN(4) static fds_tl_t const m_fds_tl_dirty =
{
    .record_key   = FDS_RECORD_KEY_DIRTY,
    .length_words = 0xFFFF  // Leave the record length field unchanged in flash.
};

// Internal status flags.
static uint8_t              m_flags;

// The number of registered users and their callback functions.
static uint8_t              m_users;
static fds_cb_t             m_cb_table[FDS_MAX_USERS];

// The latest (largest) record ID written so far.
static uint32_t             m_latest_rec_id;

// The internal queues.
static fds_op_queue_t       m_op_queue;
static fds_chunk_queue_t    m_chunk_queue;

// Structures used to hold informations about virtual pages.
static fds_page_t           m_pages[FDS_MAX_PAGES];
static fds_swap_page_t      m_swap_page;

// Garbage collection data.
static fds_gc_data_t        m_gc;


static void flag_set(fds_flags_t flag)
{
    CRITICAL_SECTION_ENTER();
    m_flags |= flag;
    CRITICAL_SECTION_EXIT();
}


static void flag_clear(fds_flags_t flag)
{
    CRITICAL_SECTION_ENTER();
    m_flags &= ~(flag);
    CRITICAL_SECTION_EXIT();
}


static bool flag_is_set(fds_flags_t flag)
{
    return (m_flags & flag);
}


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
            p_evt->id               = FDS_EVT_WRITE;
            p_evt->write.file_id    = p_op->write.header.ic.file_id;
            p_evt->write.record_key = p_op->write.header.tl.record_key;
            p_evt->write.record_id  = p_op->write.header.record_id;
            break;

        case FDS_OP_UPDATE:
            p_evt->id                      = FDS_EVT_UPDATE;
            p_evt->write.file_id           = p_op->write.header.ic.file_id;
            p_evt->write.record_key        = p_op->write.header.tl.record_key;
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
            break;

        case FDS_OP_GC:
            p_evt->id = FDS_EVT_GC;
            break;

        default:
            // Should not happen.
            break;
    }
}


static bool header_is_valid(fds_header_t const * const p_header)
{
    return ((p_header->ic.file_id    != FDS_FILE_ID_INVALID) &&
            (p_header->tl.record_key != FDS_RECORD_KEY_DIRTY));
}


static bool address_is_valid(uint32_t const * const p_addr)
{
    return ((p_addr != NULL) &&
            (p_addr >= fs_config.p_start_addr) &&
            (p_addr <= fs_config.p_end_addr)   &&
            (is_word_aligned(p_addr)));
}


static bool chunk_is_aligned(fds_record_chunk_t const * const p_chunk, uint32_t num_chunks)
{
    for (uint32_t i = 0; i < num_chunks; i++)
    {
        if (!is_word_aligned(p_chunk[i].p_data))
        {
            return false;
        }
    }
    return true;
}


// Reads a page tag, and determines if the page is used to store data or as swap.
static fds_page_type_t page_identify(uint32_t const * const p_page_addr)
{
    if (p_page_addr[FDS_PAGE_TAG_WORD_0] != FDS_PAGE_TAG_MAGIC)
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
    for (uint16_t i = 0; i < FDS_MAX_PAGES; i++)
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
    uint32_t const * const p_end_addr          = p_addr + FDS_PAGE_SIZE;
    bool                   dirty_record_found  = false;

    p_addr         += FDS_PAGE_TAG_SIZE;
    *words_written  = FDS_PAGE_TAG_SIZE;

    while ((p_addr < p_end_addr) && (*p_addr != FDS_ERASED_WORD))
    {
        // NOTE: Skip records with a dirty key or with a missing file ID.
        fds_header_t const * const p_header = (fds_header_t*)p_addr;

        if (!header_is_valid(p_header))
        {
            dirty_record_found = true;
        }
        else
        {
            // Update the latest (largest) record ID.
            if (p_header->record_id > m_latest_rec_id)
            {
               m_latest_rec_id = p_header->record_id;
            }
        }

        // Jump to the next record.
        p_addr         += (FDS_HEADER_SIZE + p_header->tl.length_words);
        *words_written += (FDS_HEADER_SIZE + p_header->tl.length_words);
    }

    if (can_gc != NULL)
    {
        *can_gc = dirty_record_found;
    }
}


static void page_offsets_update(fds_page_t * const p_page, uint16_t length_words)
{
    p_page->write_offset   += (FDS_HEADER_SIZE + length_words);
    p_page->words_reserved -= (FDS_HEADER_SIZE + length_words);
}


// Tags a page as swap, i.e., reserved for GC.
static ret_code_t page_tag_write_swap()
{
    // Needs to be statically allocated since it will be written to flash.
    static uint32_t const page_tag_swap[] = {FDS_PAGE_TAG_MAGIC, FDS_PAGE_TAG_SWAP};
    return fs_store(&fs_config, m_swap_page.p_addr, page_tag_swap, FDS_PAGE_TAG_SIZE, NULL);
}


// Tags a page as data, i.e, ready for storage.
static ret_code_t page_tag_write_data(uint32_t const * const p_page_addr)
{
    // Needs to be statically allocated since it will be written to flash.
    static uint32_t const page_tag_data[] = {FDS_PAGE_TAG_MAGIC, FDS_PAGE_TAG_DATA};
    return fs_store(&fs_config, p_page_addr, page_tag_data, FDS_PAGE_TAG_SIZE, NULL);
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
    for (uint16_t page = 0; page < FDS_MAX_PAGES; page++)
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
    CRITICAL_SECTION_ENTER();
    m_latest_rec_id++;
    CRITICAL_SECTION_EXIT();
    return m_latest_rec_id;
}


// Given a page and a record, finds the next valid record on that page. If p_record is NULL,
// search from the beginning of the page, otherwise, resume searching from the address
// pointed by p_record. Returns true if a record is found, returns false otherwise.
// If no record is found, p_record is unchanged.
static bool record_find_next(uint16_t page, uint32_t const ** p_record)
{
    fds_header_t const * p_header;
    uint32_t     const * p_next_rec = (*p_record);

    // If this is not the first invocation on this page, then jump to the next record.
    // Otherwise, start searching from the beginning of the page.
    if (p_next_rec != NULL)
    {
        p_header    = ((fds_header_t*)p_next_rec);
        p_next_rec += (FDS_HEADER_SIZE + p_header->tl.length_words);
    }
    else
    {
        p_next_rec = m_pages[page].p_addr + FDS_PAGE_TAG_SIZE;
    }

    // Read records from the page, until a valid record is found or the end of the page is
    // reached. The argument p_record is only updated if a valid record is found.
    while ((p_next_rec < (m_pages[page].p_addr + FDS_PAGE_SIZE) &&
           *p_next_rec != FDS_ERASED_WORD))
    {
        p_header = (fds_header_t*)p_next_rec;

        if (header_is_valid(p_header))
        {
            *p_record = p_next_rec;
            return true;
        }
        else
        {
            // The record is not valid, jump to the next.
            p_next_rec += (FDS_HEADER_SIZE + (p_header->tl.length_words));
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
    for (*p_page = 0; *p_page < FDS_MAX_PAGES; (*p_page)++)
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
static ret_code_t record_find(uint16_t          const * const p_file_id,
                              uint16_t          const * const p_record_key,
                              fds_record_desc_t       * const p_desc,
                              fds_find_token_t        * const p_token)
{
    if (!flag_is_set(FDS_FLAG_INITIALIZED))
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_desc == NULL || p_token == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    // Begin (or resume) searching for a record.
    for (; p_token->page < FDS_MAX_PAGES; p_token->page++)
    {
        if (m_pages[p_token->page].page_type != FDS_PAGE_DATA)
        {
            // Skip this page.
            continue;
        }

        while (record_find_next(p_token->page, &p_token->p_addr))
        {
            fds_header_t const * const p_header = (fds_header_t*)p_token->p_addr;

            // A valid record was found, check its header for a match.
            if ((p_file_id != NULL) &&
                (p_header->ic.file_id != *p_file_id))
            {
                continue;
            }

            if ((p_record_key != NULL) &&
                (p_header->tl.record_key != *p_record_key))
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


// Retrieve basic statistics about dirty records on a page.
static void dirty_records_stat(uint16_t         page,
                               uint16_t * const p_dirty_records,
                               uint16_t * const p_word_count)
{
    fds_header_t const * p_header;
    uint32_t     const * p_rec;

    p_rec = m_pages[page].p_addr + FDS_PAGE_TAG_SIZE;

    while ((p_rec < (m_pages[page].p_addr + FDS_PAGE_SIZE)) &&
           (*p_rec != FDS_ERASED_WORD))
    {
        p_header = (fds_header_t*)p_rec;

        if (!header_is_valid(p_header))
        {
            (*p_dirty_records) += 1;
            (*p_word_count)    += FDS_HEADER_SIZE + p_header->tl.length_words;
        }

        p_rec += (FDS_HEADER_SIZE + (p_header->tl.length_words));
    }
}


// Advances one position in the queue.
// Returns true if the queue is not empty.
static bool queue_advance(void)
{
    // Reset the current element.
    memset(&m_op_queue.op[m_op_queue.rp], 0x00, sizeof(fds_op_t));

    if (m_op_queue.count != 0)
    {
        // Advance in the queue, wrapping around if necessary.
        m_op_queue.rp = (m_op_queue.rp + 1) % FDS_OP_QUEUE_SIZE;
        m_op_queue.count--;
    }

    return (m_op_queue.count != 0);
}


// Given a pointer to an element in the chunk queue, computes the pointer to
// the next element in the queue. Handles wrap around.
void chunk_queue_next(fds_record_chunk_t ** pp_chunk)
{
    if ((*pp_chunk) != &m_chunk_queue.chunk[FDS_CHUNK_QUEUE_SIZE - 1])
    {
        (*pp_chunk)++;
        return;
    }

    *pp_chunk = &m_chunk_queue.chunk[0];
}


// Retrieve the current chunk, and advance the queue.
static void chunk_queue_get_and_advance(fds_record_chunk_t ** pp_chunk)
{
    if (m_chunk_queue.count != 0)
    {
        // Point to the current chunk and advance the queue.
        *pp_chunk = &m_chunk_queue.chunk[m_chunk_queue.rp];

        m_chunk_queue.rp = (m_chunk_queue.rp + 1) % FDS_CHUNK_QUEUE_SIZE;
        m_chunk_queue.count--;
    }
}


static void chunk_queue_skip(fds_op_t const * const p_op)
{
    if ((p_op->op_code == FDS_OP_WRITE) ||
        (p_op->op_code == FDS_OP_UPDATE))
    {
        m_chunk_queue.rp    += p_op->write.chunk_count;
        m_chunk_queue.count -= p_op->write.chunk_count;
    }
}


// Enqueue an operation.
static bool op_enqueue(fds_op_t           const * const p_op,
                       uint32_t                         num_chunks,
                       fds_record_chunk_t const * const p_chunk)
{
    uint32_t idx;
    bool     ret = false;

    CRITICAL_SECTION_ENTER();
    if  ((m_op_queue.count    <= FDS_OP_QUEUE_SIZE - 1) &&
         (m_chunk_queue.count <= FDS_CHUNK_QUEUE_SIZE - num_chunks))
    {
        idx = (m_op_queue.count + m_op_queue.rp) % FDS_OP_QUEUE_SIZE;

        m_op_queue.op[idx] = *p_op;
        m_op_queue.count++;

        if (num_chunks != 0)
        {
            idx = (m_chunk_queue.count + m_chunk_queue.rp) % FDS_CHUNK_QUEUE_SIZE;

            fds_record_chunk_t * p_chunk_dst;
            p_chunk_dst = &m_chunk_queue.chunk[idx];

            for (uint32_t i = 0; i < num_chunks; i++)
            {
                *p_chunk_dst = p_chunk[i];
                chunk_queue_next(&p_chunk_dst);
            }

            m_chunk_queue.count += num_chunks;
        }

        ret = true;
    }
    CRITICAL_SECTION_EXIT();

    return ret;
}


// This function is called during initialization to setup the page structure (m_pages) and
// provide additional information regarding eventual further initialization steps.
static fds_init_opts_t pages_init()
{
    uint32_t ret = NO_PAGES;
    // The index of the page being initialized in m_pages[].
    uint16_t page = 0;
    bool     swap_set_but_not_found  = false;

    for (uint16_t i = 0; i < FDS_VIRTUAL_PAGES; i++)
    {
        uint32_t        const * const p_page_addr = fs_config.p_start_addr + (i * FDS_PAGE_SIZE);
        fds_page_type_t const         page_type   = page_identify(p_page_addr);

        switch (page_type)
        {
            case FDS_PAGE_UNDEFINED:
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
                    // Do not initialize or use this page.
                    m_pages[page++].page_type = FDS_PAGE_UNDEFINED;
                }
                break;

            case FDS_PAGE_DATA:
                m_pages[page].page_type = FDS_PAGE_DATA;
                m_pages[page].p_addr    = p_page_addr;
                // Scan the page to compute its write offset and determine whether or not the page
                // can be garbage collected. Additionally, update the latest kwown record ID.
                page_scan(p_page_addr, &m_pages[page].write_offset, &m_pages[page].can_gc);

                ret |= PAGE_DATA;
                page++;

                break;

            case FDS_PAGE_SWAP:
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
                break;

            default:
                // Shouldn't happen.
                break;
        }
    }

    return (fds_init_opts_t)ret;
}


// Write the first part of a record header (the key and length).
static ret_code_t record_header_write_begin(fds_op_t * const p_op, uint32_t * const p_addr)
{
    ret_code_t ret;
    ret = fs_store(&fs_config, p_addr + FDS_OFFSET_TL,
                  (uint32_t*)&p_op->write.header.tl, FDS_HEADER_SIZE_TL, NULL);

    // Write the record ID next.
    p_op->write.step = FDS_OP_WRITE_RECORD_ID;

    return (ret == FS_SUCCESS) ? FDS_SUCCESS : FDS_ERR_BUSY;
}


static ret_code_t record_header_write_id(fds_op_t * const p_op, uint32_t * const p_addr)
{
    ret_code_t ret;
    ret = fs_store(&fs_config, p_addr + FDS_OFFSET_ID,
                   (uint32_t*)&p_op->write.header.record_id, FDS_HEADER_SIZE_ID, NULL);

    // If this record has zero chunk, write the last part of the header directly.
    // Otherwise, write the record chunks next.
    p_op->write.step = (p_op->write.chunk_count != 0) ? FDS_OP_WRITE_CHUNKS :
                                                        FDS_OP_WRITE_HEADER_FINALIZE;

    return (ret == FS_SUCCESS) ? FDS_SUCCESS : FDS_ERR_BUSY;
}


static ret_code_t record_header_write_finalize(fds_op_t * const p_op, uint32_t * const p_addr)
{
    ret_code_t ret;
    ret = fs_store(&fs_config, p_addr + FDS_OFFSET_IC,
                   (uint32_t*)&p_op->write.header.ic, FDS_HEADER_SIZE_IC, NULL);

    // If this is a simple write operation, then this is the last step.
    // If this is an update instead, delete the old record next.
    p_op->write.step = (p_op->op_code == FDS_OP_UPDATE) ? FDS_OP_WRITE_FLAG_DIRTY :
                                                          FDS_OP_WRITE_DONE;

    return (ret == FS_SUCCESS) ? FDS_SUCCESS : FDS_ERR_BUSY;
}


static ret_code_t record_header_flag_dirty(uint32_t * const p_record, uint16_t page_to_gc)
{
    // Flag the record as dirty.
    fs_ret_t ret = fs_store(&fs_config, p_record,
                            (uint32_t*)&m_fds_tl_dirty, FDS_HEADER_SIZE_TL, NULL);

    if (ret != FS_SUCCESS)
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

        p_op->del.file_id    = p_header->ic.file_id;
        p_op->del.record_key = p_header->tl.record_key;

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


// Writes a record chunk to flash and advances the chunk queue. Additionally, decrements
// the number of chunks left to write for this operation and accumulates the offset.
static ret_code_t record_write_chunk(fds_op_t * const p_op, uint32_t * const p_addr)
{
    ret_code_t           ret;
    fds_record_chunk_t * p_chunk = NULL;

    // Retrieve the next chunk to be written.
    chunk_queue_get_and_advance(&p_chunk);

    ret = fs_store(&fs_config, p_addr + p_op->write.chunk_offset,
                   p_chunk->p_data, p_chunk->length_words, NULL);

    // Accumulate the offset.
    p_op->write.chunk_offset += p_chunk->length_words;

    // Decrement the number of chunks left to write.
    // NOTE: If chunk_count is initially zero, this function is not called
    // because this step is skipped entirely. See record_header_write_id().
    p_op->write.chunk_count--;

    if (p_op->write.chunk_count == 0)
    {
        // All record chunks have been written; write the last part of
        // the record header to finalize the write operation.
        p_op->write.step = FDS_OP_WRITE_HEADER_FINALIZE;
    }

    return (ret == NRF_SUCCESS) ? FDS_SUCCESS : FDS_ERR_BUSY;
}


#if defined(FDS_CRC_ENABLED)

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
    for (uint16_t i = 0; i < FDS_MAX_PAGES; i++)
    {
        m_gc.do_gc_page[i] = (m_pages[i].page_type == FDS_PAGE_DATA);
    }
}


// Obtain the next page to be garbage collected.
// Returns true if there are pages left to garbage collect, returns false otherwise.
static bool gc_page_next(uint16_t * const p_next_page)
{
    bool ret = false;

    for (uint16_t i = 0; i < FDS_MAX_PAGES; i++)
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

    return fs_erase(&fs_config, m_swap_page.p_addr, FDS_PHY_PAGES_IN_VPAGE, NULL);
}


// Erase the page being garbage collected, or erase the swap in case there are any open
// records on the page being garbage collected.
static ret_code_t gc_page_erase(void)
{
    uint32_t       ret;
    uint16_t const gc = m_gc.cur_page;

    if (m_pages[gc].records_open == 0)
    {
        ret = fs_erase(&fs_config, m_pages[gc].p_addr, FDS_PHY_PAGES_IN_VPAGE, NULL);
        m_gc.state = GC_ERASE_PAGE;
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
    uint16_t     const         record_len = FDS_HEADER_SIZE + p_header->tl.length_words;

    m_gc.state = GC_COPY_RECORD;

    // Copy the record to swap; it is guaranteed to fit in the destination page,
    // so there is no need to check its size. This will either succeed or timeout.
    return fs_store(&fs_config, p_dest, m_gc.p_record_src, record_len, NULL);
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
    uint16_t     const         record_len = FDS_HEADER_SIZE + p_header->tl.length_words;

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
        // Swap was sucessfully promoted.
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

    if (prev_ret != FS_SUCCESS)
    {
        // A previous operation has timed out.
        flag_clear(FDS_FLAG_INITIALIZING);
        return FDS_ERR_OPERATION_TIMEOUT;
    }

    switch (p_op->init.step)
    {
        case FDS_OP_INIT_TAG_SWAP:
            // The page write offset was determined previously by pages_init().
            ret             = page_tag_write_swap();
            p_op->init.step = FDS_OP_INIT_TAG_DATA;
            break;

        case FDS_OP_INIT_TAG_DATA:
        {
            // Tag remaining erased pages as data.
            bool write_reqd = false;
            for (uint16_t i = 0; i < FDS_MAX_PAGES; i++)
            {
                if (m_pages[i].page_type == FDS_PAGE_ERASED)
                {
                    ret = page_tag_write_data(m_pages[i].p_addr);
                    m_pages[i].page_type = FDS_PAGE_DATA;
                    write_reqd           = true;
                    break;
                }
            }
            if (!write_reqd)
            {
                flag_set(FDS_FLAG_INITIALIZED);
                flag_clear(FDS_FLAG_INITIALIZING);
                return FDS_OP_COMPLETED;
            }
        }
        break;

        case FDS_OP_INIT_ERASE_SWAP:
            ret = fs_erase(&fs_config, m_swap_page.p_addr, FDS_PHY_PAGES_IN_VPAGE, NULL);
            // If the swap is going to be discarded then reset its write_offset.
            m_swap_page.write_offset = FDS_PAGE_TAG_SIZE;
            p_op->init.step          = FDS_OP_INIT_TAG_SWAP;
            break;

        case FDS_OP_INIT_PROMOTE_SWAP:
        {
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
            p_op->init.step       = FDS_OP_INIT_TAG_SWAP;
        }
        break;

        default:
            // Should not happen.
            break;
    }

    if (ret != FDS_SUCCESS)
    {
        // fstorage queue was full.
        flag_clear(FDS_FLAG_INITIALIZING);
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

    if (prev_ret != FS_SUCCESS)
    {
        // The previous operation has timed out, update offsets.
        page_offsets_update(p_page, p_op->write.header.tl.length_words);
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

        case FDS_OP_WRITE_CHUNKS:
            ret = record_write_chunk(p_op, p_write_addr);
            break;

        case FDS_OP_WRITE_HEADER_FINALIZE:
            ret = record_header_write_finalize(p_op, p_write_addr);
            break;

        case FDS_OP_WRITE_FLAG_DIRTY:
            ret = record_header_flag_dirty((uint32_t*)desc.p_record, page);
            p_op->write.step = FDS_OP_WRITE_DONE;
            break;

        case FDS_OP_WRITE_DONE:
            ret = FDS_OP_COMPLETED;

#if defined(FDS_CRC_ENABLED)
            if (flag_is_set(FDS_FLAG_VERIFY_CRC))
            {
                if (!crc_verify_success(p_op->write.header.ic.crc16,
                                        p_op->write.header.tl.length_words,
                                        p_write_addr))
                {
                    ret = FDS_ERR_CRC_CHECK_FAILED;
                }
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
        page_offsets_update(p_page, p_op->write.header.tl.length_words);
    }

    return ret;
}


static ret_code_t delete_execute(uint32_t prev_ret, fds_op_t * const p_op)
{
    ret_code_t ret;

    if (prev_ret != FS_SUCCESS)
    {
        return FDS_ERR_OPERATION_TIMEOUT;
    }

    switch (p_op->del.step)
    {
        case FDS_OP_DEL_RECORD_FLAG_DIRTY:
            ret = record_find_and_delete(p_op);
            p_op->del.step = FDS_OP_DEL_DONE;
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

    if (prev_ret != FS_SUCCESS)
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


static void queue_process(fs_ret_t result)
{
    ret_code_t         ret;
    fds_op_t   * const p_op = &m_op_queue.op[m_op_queue.rp];

    switch (p_op->op_code)
    {
        case FDS_OP_INIT:
            ret = init_execute(result, p_op);
            break;

        case FDS_OP_WRITE:
        case FDS_OP_UPDATE:
            ret = write_execute(result, p_op);
            break;

        case FDS_OP_DEL_RECORD:
        case FDS_OP_DEL_FILE:
            ret = delete_execute(result, p_op);
            break;

        case FDS_OP_GC:
            ret = gc_execute(result);
            break;

        default:
            ret = FDS_ERR_INTERNAL;
            break;
    }

    if (ret != FDS_OP_EXECUTING)
    {
        fds_evt_t evt;

        if (ret == FDS_OP_COMPLETED)
        {
            evt.result = FDS_SUCCESS;
        }
        else
        {
            // Either FDS_ERR_BUSY, FDS_ERR_OPERATION_TIMEOUT,
            // FDS_ERR_CRC_CHECK_FAILED or FDS_ERR_NOT_FOUND.
            evt.result = ret;

            // If this operation had any chunks in the queue, skip them.
            chunk_queue_skip(p_op);
        }

        event_prepare(p_op, &evt);
        event_send(&evt);

        // Advance the queue, and if there are any queued operations, process them.
        if (queue_advance())
        {
            queue_process(FS_SUCCESS);
        }
        else
        {
            // No more elements in the queue. Clear the FDS_FLAG_PROCESSING flag,
            // so that new operation can start processing the queue.
            flag_clear(FDS_FLAG_PROCESSING);
        }
    }
}


static void queue_start(void)
{
    if (!flag_is_set(FDS_FLAG_PROCESSING))
    {
        flag_set(FDS_FLAG_PROCESSING);
        queue_process(FS_SUCCESS);
    }
}


static void fs_event_handler(fs_evt_t const * const p_evt, fs_ret_t result)
{
    queue_process(result);
}


// Enqueues write and update operations.
static ret_code_t write_enqueue(fds_record_desc_t         * const p_desc,
                                fds_record_t        const * const p_record,
                                fds_reserve_token_t const * const p_tok,
                                fds_op_code_t                     op_code)
{
    ret_code_t ret;
    fds_op_t   op;
    uint16_t   page;
    uint16_t   crc          = 0;
    uint16_t   length_words = 0;

    if (!flag_is_set(FDS_FLAG_INITIALIZED))
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

    if (!chunk_is_aligned(p_record->data.p_chunks,
                          p_record->data.num_chunks))
    {
        return FDS_ERR_UNALIGNED_ADDR;
    }

    // No space was previously reserved for this operation.
    if (p_tok == NULL)
    {
        // Compute the total length of the record.
        for (uint32_t i = 0; i < p_record->data.num_chunks; i++)
        {
            length_words += p_record->data.p_chunks[i].length_words;
        }

        // Find a page where to write data.
        ret = write_space_reserve(length_words, &page);

        if (ret != FDS_SUCCESS)
        {
            // There is either not enough flash space available (FDS_ERR_NO_SPACE_IN_FLASH) or
            // the record exceeds the virtual page size (FDS_ERR_RECORD_TOO_LARGE).
            return ret;
        }
    }
    else
    {
        page         = p_tok->page;
        length_words = p_tok->length_words;
    }

    // Initialize the operation.
    op.op_code                      = op_code;
    op.write.step                   = FDS_OP_WRITE_HEADER_BEGIN;
    op.write.page                   = page;
    op.write.chunk_count            = p_record->data.num_chunks;
    op.write.chunk_offset           = FDS_OFFSET_DATA;
    op.write.header.record_id       = record_id_new();
    op.write.header.ic.file_id      = p_record->file_id;
    op.write.header.tl.record_key   = p_record->key;
    op.write.header.tl.length_words = length_words;

    if (op_code == FDS_OP_UPDATE)
    {
        op.write.step             = FDS_OP_WRITE_FIND_RECORD;
        // Save the record ID of the record to be updated.
        op.write.record_to_delete = p_desc->record_id;
    }

#if defined (FDS_CRC_ENABLED)
    // First, compute the CRC for the first 6 bytes of the header which contain the
    // record key, length and file ID, then, compute the CRC of the record ID (4 bytes).
    crc = crc16_compute((uint8_t*)&op.write.header,           6, NULL);
    crc = crc16_compute((uint8_t*)&op.write.header.record_id, 4, &crc);

    for (uint32_t i = 0; i < p_record->data.num_chunks; i++)
    {
        // Compute the CRC for the record data.
        crc = crc16_compute((uint8_t*)p_record->data.p_chunks[i].p_data,
                            p_record->data.p_chunks[i].length_words * sizeof(uint32_t), &crc);
    }
#endif

    op.write.header.ic.crc16 = crc;

    // Attempt to enqueue the operation.
    if (!op_enqueue(&op, p_record->data.num_chunks, p_record->data.p_chunks))
    {
        // No space availble in the queues. Cancel the reservation of flash space.
        CRITICAL_SECTION_ENTER();
        write_space_free(length_words, page);
        CRITICAL_SECTION_EXIT();

        return FDS_ERR_NO_SPACE_IN_QUEUES;
    }

     // Initialize the record descriptor, if provided.
    if (p_desc != NULL)
    {
        p_desc->p_record       = NULL;
        // Don't invoke record_id_new() again !
        p_desc->record_id      = op.write.header.record_id;
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

    CRITICAL_SECTION_ENTER();
    if (m_users == FDS_MAX_USERS)
    {
        ret = FDS_ERR_USER_LIMIT_REACHED;
    }
    else
    {
        m_cb_table[m_users] = cb;
        m_users++;

        ret = FDS_SUCCESS;
    }
    CRITICAL_SECTION_EXIT();

    return ret;
}


ret_code_t fds_init(void)
{
    fds_evt_t const evt_success =
    {
        .id     = FDS_EVT_INIT,
        .result = FDS_SUCCESS
    };

    // No initialization is necessary. Notify the application immediately.
    if (flag_is_set(FDS_FLAG_INITIALIZED))
    {
        event_send(&evt_success);
        return FDS_SUCCESS;
    }

    if (flag_is_set(FDS_FLAG_INITIALIZING))
    {
        return FDS_SUCCESS;
    }

    flag_set(FDS_FLAG_INITIALIZING);

    (void)fs_init();

    // Initialize the page structure (m_pages), and determine which
    // initialization steps are required given the current state of the filesystem.
    fds_op_t op;
    op.op_code = FDS_OP_INIT;

    fds_init_opts_t init_opts = pages_init();

    switch (init_opts)
    {
        case NO_PAGES:
        case NO_SWAP:
            return FDS_ERR_NO_PAGES;

        case ALREADY_INSTALLED:
            // No initialization is necessary. Notify the application immediately.
            flag_set(FDS_FLAG_INITIALIZED);
            flag_clear(FDS_FLAG_INITIALIZING);
            event_send(&evt_success);
            return FDS_SUCCESS;

        case FRESH_INSTALL:
        case TAG_SWAP:
            op.init.step = FDS_OP_INIT_TAG_SWAP;
            break;

        case PROMOTE_SWAP:
        case PROMOTE_SWAP_INST:
            op.init.step = FDS_OP_INIT_PROMOTE_SWAP;
            break;

        case DISCARD_SWAP:
            op.init.step = FDS_OP_INIT_ERASE_SWAP;
            break;

        case TAG_DATA:
        case TAG_DATA_INST:
            op.init.step = FDS_OP_INIT_TAG_DATA;
            break;

        default:
            // Should not happen.
            break;
    }

    // This cannot fail since it will be the first operation in the queue.
    (void)op_enqueue(&op, 0, NULL);

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

#if defined(FDS_CRC_ENABLED)
        if (!crc_verify_success(p_header->ic.crc16,
                                p_header->tl.length_words,
                                p_desc->p_record))
        {
            return FDS_ERR_CRC_CHECK_FAILED;
        }
#endif

        CRITICAL_SECTION_ENTER();
        m_pages[page].records_open++;
        CRITICAL_SECTION_EXIT();

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

    if (!flag_is_set(FDS_FLAG_INITIALIZED))
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

    if (!flag_is_set(FDS_FLAG_INITIALIZED))
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_tok == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    if (p_tok->page > FDS_MAX_PAGES)
    {
        // The page does not exist. This shouldn't happen.
        return FDS_ERR_INVALID_ARG;
    }

    fds_page_t const * const p_page = &m_pages[p_tok->page];

    CRITICAL_SECTION_ENTER();
    if (p_page->words_reserved - (FDS_HEADER_SIZE + p_tok->length_words) >= 0)
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
    fds_op_t op;

    if (!flag_is_set(FDS_FLAG_INITIALIZED))
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_desc == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    op.op_code              = FDS_OP_DEL_RECORD;
    op.del.step             = FDS_OP_DEL_RECORD_FLAG_DIRTY;
    op.del.record_to_delete = p_desc->record_id;

    if (op_enqueue(&op, 0, NULL))
    {
        queue_start();
        return FDS_SUCCESS;
    }

   return FDS_ERR_NO_SPACE_IN_QUEUES;
}


ret_code_t fds_file_delete(uint16_t file_id)
{
    fds_op_t op;

    if (!flag_is_set(FDS_FLAG_INITIALIZED))
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (file_id == FDS_FILE_ID_INVALID)
    {
        return FDS_ERR_INVALID_ARG;
    }

    op.op_code      = FDS_OP_DEL_FILE;
    op.del.step     = FDS_OP_DEL_FILE_FLAG_DIRTY;
    op.del.file_id  = file_id;

    if (op_enqueue(&op, 0, NULL))
    {
        queue_start();
        return FDS_SUCCESS;
    }

    return FDS_ERR_NO_SPACE_IN_QUEUES;
}


ret_code_t fds_gc(void)
{
    fds_op_t op;

    if (!flag_is_set(FDS_FLAG_INITIALIZED))
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    op.op_code = FDS_OP_GC;

    if (op_enqueue(&op, 0, NULL))
    {
        if (m_gc.state != GC_BEGIN)
        {
            // Resume GC by retrying the last step.
            m_gc.resume = true;
        }

        queue_start();
        return FDS_SUCCESS;
    }

    return FDS_ERR_NO_SPACE_IN_QUEUES;
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

    if (!flag_is_set(FDS_FLAG_INITIALIZED))
    {
        return FDS_ERR_NOT_INITIALIZED;
    }

    if (p_stat == NULL)
    {
        return FDS_ERR_NULL_ARG;
    }

    memset(p_stat, 0x00, sizeof(fds_stat_t));

    for (uint16_t i = 0; i < FDS_MAX_PAGES; i++)
    {
        uint32_t const * p_record   = NULL;
        uint16_t const   words_used = m_pages[i].write_offset + m_pages[i].words_reserved;

        p_stat->open_records   += m_pages[i].records_open;
        p_stat->words_reserved += m_pages[i].words_reserved;
        p_stat->words_used     += words_used;
        contig_words           =  (words_in_page - words_used);

        if (contig_words > p_stat->largest_contig)
        {
            p_stat->largest_contig = contig_words;
        }

        while (record_find_next(i, &p_record))
        {
            p_stat->valid_records++;
        }

        dirty_records_stat(i, &p_stat->dirty_records, &p_stat->freeable_words);
    }

    return FDS_SUCCESS;
}


#if defined(FDS_CRC_ENABLED)

ret_code_t fds_verify_crc_on_writes(bool enable)
{
    if (enable)
    {
        flag_set(FDS_FLAG_VERIFY_CRC);
    }
    else
    {
        flag_clear(FDS_FLAG_VERIFY_CRC);
    }

    return FDS_SUCCESS;
}

#endif
#endif //NRF_MODULE_ENABLED(FDS)
