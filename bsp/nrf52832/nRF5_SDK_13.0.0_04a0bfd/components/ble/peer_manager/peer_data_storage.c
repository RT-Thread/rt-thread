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
#if NRF_MODULE_ENABLED(PEER_MANAGER)
#include "peer_data_storage.h"

#include <stdint.h>
#include <string.h>
#include "sdk_errors.h"
#include "peer_manager_types.h"
#include "peer_manager_internal.h"
#include "peer_id.h"
#include "fds.h"


// Macro for verifying that the peer id is within a valid range.
#define VERIFY_PEER_ID_IN_RANGE(id)         VERIFY_FALSE((id >= PM_PEER_ID_N_AVAILABLE_IDS), \
                                            NRF_ERROR_INVALID_PARAM)

// Macro for verifying that the peer data id is withing a valid range.
#define VERIFY_PEER_DATA_ID_IN_RANGE(id)    VERIFY_TRUE(peer_data_id_is_valid(id), \
                                            NRF_ERROR_INVALID_PARAM)

// The number of registered event handlers.
#define PDS_EVENT_HANDLERS_CNT              (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))


// Peer Data Storage event handler in Peer Database.
extern void pdb_pds_evt_handler(pds_evt_t const *);

// Peer Data Storage events' handlers.
// The number of elements in this array is PDS_EVENT_HANDLERS_CNT.
static pds_evt_handler_t const m_evt_handlers[] =
{
    pdb_pds_evt_handler,
};

static bool m_module_initialized  = false;
static bool m_peer_delete_queued  = false;
static bool m_peer_delete_ongoing = false;

// A token used for Flash Data Storage searches.
static fds_find_token_t m_fds_ftok;


// Function for dispatching events to all registered event handlers.
static void pds_evt_send(pds_evt_t * p_event)
{
    for (uint32_t i = 0; i < PDS_EVENT_HANDLERS_CNT; i++)
    {
        m_evt_handlers[i](p_event);
    }
}


// Function to convert peer IDs to file IDs.
static uint16_t peer_id_to_file_id(pm_peer_id_t peer_id)
{
    return (uint16_t)(peer_id + PEER_ID_TO_FILE_ID);
}


// Function to convert peer data id to type id.
static pm_peer_id_t file_id_to_peer_id(uint16_t file_id)
{
    return (pm_peer_id_t)(file_id + FILE_ID_TO_PEER_ID);
}


// Function to convert peer data IDs to record keys.
static uint16_t peer_data_id_to_record_key(pm_peer_data_id_t peer_data_id)
{
    return (uint16_t)(peer_data_id + DATA_ID_TO_RECORD_KEY);
}


// Function to convert record keys to peer data IDs.
static pm_peer_data_id_t record_key_to_peer_data_id(uint16_t record_key)
{
    return (pm_peer_data_id_t)(record_key + RECORD_KEY_TO_DATA_ID);
}


// Function for checking whether a file ID is relevant for the Peer Manager.
static bool file_id_within_pm_range(uint16_t file_id)
{
    return ((PDS_FIRST_RESERVED_FILE_ID <= file_id)
         && (file_id <= PDS_LAST_RESERVED_FILE_ID));
}


// Function for checking whether a record key is relevant for the Peer Manager.
static bool record_key_within_pm_range(uint16_t record_key)
{
    return ((PDS_FIRST_RESERVED_RECORD_KEY <= record_key)
         && (record_key <= PDS_LAST_RESERVED_RECORD_KEY));
}


static bool peer_data_id_is_valid(pm_peer_data_id_t data_id)
{
    return ((data_id == PM_PEER_DATA_ID_BONDING)                 ||
            (data_id == PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING) ||
            (data_id == PM_PEER_DATA_ID_GATT_LOCAL)              ||
            (data_id == PM_PEER_DATA_ID_GATT_REMOTE)             ||
            (data_id == PM_PEER_DATA_ID_PEER_RANK)               ||
            (data_id == PM_PEER_DATA_ID_APPLICATION));
}


// Function for deleting all data beloning to a peer.
// These operations will be sent to FDS one at a time.
static void peer_data_delete()
{
    ret_code_t        ret;
    pm_peer_id_t      peer_id;
    uint16_t          file_id;
    fds_record_desc_t desc;
    fds_find_token_t  ftok;

    memset(&ftok, 0x00, sizeof(fds_find_token_t));
    peer_id = peer_id_get_next_deleted(PM_PEER_ID_INVALID);

    while (    (peer_id != PM_PEER_ID_INVALID)
            && (fds_record_find_in_file(peer_id_to_file_id(peer_id), &desc, &ftok)
            == FDS_ERR_NOT_FOUND))
    {
        peer_id_free(peer_id);
        peer_id = peer_id_get_next_deleted(peer_id);
    }

    if (!m_peer_delete_ongoing && (peer_id != PM_PEER_ID_INVALID))
    {
        m_peer_delete_ongoing = true;

        file_id = peer_id_to_file_id(peer_id);
        ret     = fds_file_delete(file_id);

        if (ret == FDS_ERR_NO_SPACE_IN_QUEUES)
        {
            m_peer_delete_queued = true;
        }
        else if (ret != NRF_SUCCESS)
        {
            m_peer_delete_ongoing = false;

            pds_evt_t pds_evt;

            pds_evt.evt_id      = PDS_EVT_ERROR_UNEXPECTED;
            pds_evt.peer_id     = peer_id;
            pds_evt.data_id     = PM_PEER_DATA_ID_INVALID;
            pds_evt.store_token = PM_STORE_TOKEN_INVALID;
            pds_evt.result      = ret;

            pds_evt_send(&pds_evt);
        }
    }
}


static ret_code_t peer_data_find(pm_peer_id_t              peer_id,
                                 pm_peer_data_id_t         data_id,
                                 fds_record_desc_t * const p_desc)
{
    ret_code_t       ret;
    fds_find_token_t ftok;

    NRF_PM_DEBUG_CHECK(peer_id < PM_PEER_ID_N_AVAILABLE_IDS);
    NRF_PM_DEBUG_CHECK(peer_data_id_is_valid(data_id));
    NRF_PM_DEBUG_CHECK(p_desc != NULL);

    memset(&ftok, 0x00, sizeof(fds_find_token_t));

    uint16_t file_id    = peer_id_to_file_id(peer_id);
    uint16_t record_key = peer_data_id_to_record_key(data_id);

    ret = fds_record_find(file_id, record_key, p_desc, &ftok);

    if (ret != FDS_SUCCESS)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    return NRF_SUCCESS;
}


static void peer_ids_load()
{
    fds_record_desc_t  record_desc;
    fds_flash_record_t record;
    fds_find_token_t   ftok;

    memset(&ftok, 0x00, sizeof(fds_find_token_t));

    uint16_t const record_key = peer_data_id_to_record_key(PM_PEER_DATA_ID_BONDING);

    while (fds_record_find_by_key(record_key, &record_desc, &ftok) == FDS_SUCCESS)
    {
        pm_peer_id_t peer_id;

        // It is safe to ignore the return value since the descriptor was
        // just obtained and also 'record' is different from NULL.
        (void)fds_record_open(&record_desc, &record);
        peer_id = file_id_to_peer_id(record.p_header->ic.file_id);
        (void)fds_record_close(&record_desc);

        (void)peer_id_allocate(peer_id);
    }
}


static void fds_evt_handler(fds_evt_t const * const p_fds_evt)
{
    pds_evt_t pds_evt;

    pds_evt.result = (p_fds_evt->result == FDS_SUCCESS);

    switch (p_fds_evt->id)
    {
        case FDS_EVT_WRITE:
        case FDS_EVT_UPDATE:
            if (   file_id_within_pm_range(p_fds_evt->write.file_id)
                || record_key_within_pm_range(p_fds_evt->write.record_key))
            {
                pds_evt.peer_id = file_id_to_peer_id(p_fds_evt->write.file_id);
                pds_evt.data_id = record_key_to_peer_data_id(p_fds_evt->write.record_key);

                if (p_fds_evt->id == FDS_EVT_WRITE)
                {
                    pds_evt.evt_id = (p_fds_evt->result == FDS_SUCCESS) ? PDS_EVT_STORED :
                                                                          PDS_EVT_ERROR_STORE;
                }
                else
                {
                    pds_evt.evt_id = (p_fds_evt->result == FDS_SUCCESS) ? PDS_EVT_UPDATED :
                                                                          PDS_EVT_ERROR_UPDATE;
                }

                pds_evt.result      = p_fds_evt->result;
                pds_evt.store_token = p_fds_evt->write.record_id;

                pds_evt_send(&pds_evt);
            }
            break;

        case FDS_EVT_DEL_RECORD:
            if (   file_id_within_pm_range(p_fds_evt->del.file_id)
                || record_key_within_pm_range(p_fds_evt->del.record_key))
            {
                pds_evt.peer_id = file_id_to_peer_id(p_fds_evt->del.file_id);
                pds_evt.data_id = record_key_to_peer_data_id(p_fds_evt->del.record_key);

                pds_evt.evt_id = (p_fds_evt->result == FDS_SUCCESS) ? PDS_EVT_CLEARED :
                                                                      PDS_EVT_ERROR_CLEAR;

                pds_evt.store_token = p_fds_evt->del.record_id;

                pds_evt_send(&pds_evt);
            }
            break;

        case FDS_EVT_DEL_FILE:
            {
                if (    file_id_within_pm_range(p_fds_evt->del.file_id)
                    && (p_fds_evt->del.record_key == FDS_RECORD_KEY_DIRTY))
                {
                    pds_evt.peer_id = file_id_to_peer_id(p_fds_evt->del.file_id);
                    pds_evt.data_id = record_key_to_peer_data_id(p_fds_evt->del.record_key);

                    pds_evt.data_id = PM_PEER_DATA_ID_INVALID;
                    if (p_fds_evt->result == FDS_SUCCESS)
                    {
                        pds_evt.evt_id = PDS_EVT_PEER_ID_CLEAR;
                        peer_id_free(pds_evt.peer_id);
                    }
                    else
                    {
                        pds_evt.evt_id = PDS_EVT_ERROR_PEER_ID_CLEAR;
                    }

                    m_peer_delete_queued  = false;
                    m_peer_delete_ongoing = false;

                    peer_data_delete();

                    pds_evt_send(&pds_evt);
                }
            }
            break;

        case FDS_EVT_GC:
            pds_evt.evt_id = PDS_EVT_COMPRESSED;
            pds_evt_send(&pds_evt);
            break;

        default:
            break;
    }

    if (m_peer_delete_queued)
    {
        m_peer_delete_queued  = false;
        peer_data_delete();
    }
}


ret_code_t pds_init()
{
    ret_code_t ret;

    // Check for re-initialization if debugging.
    NRF_PM_DEBUG_CHECK(!m_module_initialized);

    ret = fds_register(fds_evt_handler);
    if (ret != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    ret = fds_init();
    if (ret != NRF_SUCCESS)
    {
        return NRF_ERROR_STORAGE_FULL;
    }

    peer_id_init();
    peer_ids_load();

    m_module_initialized = true;

    return NRF_SUCCESS;
}


ret_code_t pds_peer_data_read(pm_peer_id_t                    peer_id,
                              pm_peer_data_id_t               data_id,
                              pm_peer_data_t          * const p_data,
                              uint32_t          const * const p_buf_len)
{
    ret_code_t         ret;
    fds_record_desc_t  rec_desc;
    fds_flash_record_t rec_flash;

    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_data != NULL);

    VERIFY_PEER_ID_IN_RANGE(peer_id);
    VERIFY_PEER_DATA_ID_IN_RANGE(data_id);

    ret = peer_data_find(peer_id, data_id, &rec_desc);

    if (ret != NRF_SUCCESS)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    // Shouldn't fail, unless the record was deleted in the meanwhile or the CRC check has failed.
    ret = fds_record_open(&rec_desc, &rec_flash);

    if (ret != NRF_SUCCESS)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    // @note emdi: could this actually be set by the caller and used instead
    // of an additional parameter (data_id) ?
    p_data->data_id      = data_id;
    p_data->length_words = rec_flash.p_header->tl.length_words;

    // If p_buf_len is NULL, provide a pointer to data in flash, otherwise,
    // check that the buffer is large enough and copy the data in flash into the buffer.
    if (p_buf_len != NULL)
    {
        uint32_t const data_len_bytes = (p_data->length_words * sizeof(uint32_t));

        if ((*p_buf_len) <= data_len_bytes)
        {
            memcpy(p_data->p_all_data, rec_flash.p_data, data_len_bytes);
        }
        else
        {
            return NRF_ERROR_NO_MEM;
        }
    }
    else
    {
        // The cast is necessary because if no buffer is provided, we just copy the pointer,
        // but it that case it should be considered a pointer to const data by the caller,
        // since it is a pointer to data in flash.
        p_data->p_all_data = (void*)rec_flash.p_data;
    }

    // Shouldn't fail unless the record was already closed, in which case it can be ignored.
    (void)fds_record_close(&rec_desc);

    return NRF_SUCCESS;
}


void pds_peer_data_iterate_prepare(void)
{
    memset(&m_fds_ftok, 0x00, sizeof(fds_find_token_t));
}


bool pds_peer_data_iterate(pm_peer_data_id_t            data_id,
                           pm_peer_id_t         * const p_peer_id,
                           pm_peer_data_flash_t * const p_data)
{
    ret_code_t         ret;
    uint16_t           rec_key;
    fds_record_desc_t  rec_desc;
    fds_flash_record_t rec_flash;

    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_peer_id != NULL);
    NRF_PM_DEBUG_CHECK(p_data    != NULL);

    // @note emdi: should we check the data_id ?
    rec_key = peer_data_id_to_record_key(data_id);

    if (fds_record_find_by_key(rec_key, &rec_desc, &m_fds_ftok) != NRF_SUCCESS)
    {
        return false;
    }

    ret = fds_record_open(&rec_desc, &rec_flash);

    if (ret != NRF_SUCCESS)
    {
        // It can only happen if the record was deleted after the call to fds_record_find_by_key(),
        // before we could open it, or if CRC support was enabled in Flash Data Storage at compile
        // time and the CRC check failed.
        return false;
    }

    p_data->data_id      = data_id;
    p_data->length_words = rec_flash.p_header->tl.length_words;
    p_data->p_all_data   = rec_flash.p_data;

    *p_peer_id           = file_id_to_peer_id(rec_flash.p_header->ic.file_id);

    (void)fds_record_close(&rec_desc);

    return true;
}


ret_code_t pds_space_reserve(pm_peer_data_const_t const * p_peer_data,
                             pm_prepare_token_t         * p_prepare_token)
{
    ret_code_t ret;

    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_peer_data     != NULL);
    NRF_PM_DEBUG_CHECK(p_prepare_token != NULL);

    VERIFY_PEER_DATA_ID_IN_RANGE(p_peer_data->data_id);

    ret = fds_reserve((fds_reserve_token_t*)p_prepare_token, p_peer_data->length_words);

    switch (ret)
    {
        case FDS_SUCCESS:
            return NRF_SUCCESS;

        case FDS_ERR_RECORD_TOO_LARGE:
            return NRF_ERROR_INVALID_LENGTH;

        case FDS_ERR_NO_SPACE_IN_FLASH:
            return NRF_ERROR_STORAGE_FULL;

        default:
            return NRF_ERROR_INTERNAL;
    }
}


ret_code_t pds_space_reserve_cancel(pm_prepare_token_t prepare_token)
{
    ret_code_t ret;

    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(prepare_token != PDS_PREPARE_TOKEN_INVALID);

    ret = fds_reserve_cancel((fds_reserve_token_t*)&prepare_token);

    if (ret != FDS_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    return NRF_SUCCESS;
}


ret_code_t pds_peer_data_store(pm_peer_id_t                 peer_id,
                               pm_peer_data_const_t const * p_peer_data,
                               pm_prepare_token_t           prepare_token,
                               pm_store_token_t           * p_store_token)
{
    ret_code_t         ret;
    fds_record_t       rec;
    fds_record_desc_t  rec_desc;
    fds_record_chunk_t rec_chunk;

    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_peer_data != NULL);

    VERIFY_PEER_ID_IN_RANGE(peer_id);
    VERIFY_PEER_DATA_ID_IN_RANGE(p_peer_data->data_id);

    // Prepare chunk.
    rec_chunk.p_data       = p_peer_data->p_all_data;
    rec_chunk.length_words = p_peer_data->length_words;

    // Prepare the record to be stored in flash.
    rec.file_id         = peer_id_to_file_id(peer_id);
    rec.key             = peer_data_id_to_record_key(p_peer_data->data_id);
    rec.data.p_chunks   = &rec_chunk;
    rec.data.num_chunks = 1;

    ret = peer_data_find(peer_id, p_peer_data->data_id, &rec_desc);

    if (ret == NRF_ERROR_NOT_FOUND)
    {
        // No previous data exists in flash.
        if (prepare_token == PDS_PREPARE_TOKEN_INVALID)
        {
            // No space was previously reserved.
            ret = fds_record_write(&rec_desc, &rec);
        }
        else
        {
            // Space for this record was previously reserved.
            ret = fds_record_write_reserved(&rec_desc, &rec, (fds_reserve_token_t*)&prepare_token);
        }
    }
    else // NRF_SUCCESS
    {
        if (prepare_token != PDS_PREPARE_TOKEN_INVALID)
        {
            (void)fds_reserve_cancel((fds_reserve_token_t*)&prepare_token);
        }

        // Update existing record.
        ret = fds_record_update(&rec_desc, &rec);
    }

    switch (ret)
    {
        case FDS_SUCCESS:
            if (p_store_token != NULL)
            {
                // Update the store token.
                (void)fds_record_id_from_desc(&rec_desc, (uint32_t*)p_store_token);
            }
            return NRF_SUCCESS;

        case FDS_ERR_BUSY:
        case FDS_ERR_NO_SPACE_IN_QUEUES:
            return NRF_ERROR_BUSY;

        case FDS_ERR_NO_SPACE_IN_FLASH:
            return NRF_ERROR_STORAGE_FULL;

        default:
            return NRF_ERROR_INTERNAL;
    }
}


// @note emdi: unused..
ret_code_t pds_peer_data_delete(pm_peer_id_t peer_id, pm_peer_data_id_t data_id)
{
    ret_code_t        ret;
    fds_record_desc_t record_desc;

    NRF_PM_DEBUG_CHECK(m_module_initialized);

    VERIFY_PEER_ID_IN_RANGE(peer_id);
    VERIFY_PEER_DATA_ID_IN_RANGE(data_id);

    ret = peer_data_find(peer_id, data_id, &record_desc);

    if (ret != NRF_SUCCESS)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    ret = fds_record_delete(&record_desc);

    switch (ret)
    {
        case FDS_SUCCESS:
            return NRF_SUCCESS;

        case FDS_ERR_NO_SPACE_IN_QUEUES:
            return NRF_ERROR_BUSY;

        default:
            return NRF_ERROR_INTERNAL;
    }
}


pm_peer_id_t pds_peer_id_allocate(void)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return peer_id_allocate(PM_PEER_ID_INVALID);
}


ret_code_t pds_peer_id_free(pm_peer_id_t peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    VERIFY_PEER_ID_IN_RANGE(peer_id);

    (void)peer_id_delete(peer_id);
    peer_data_delete();

    return NRF_SUCCESS;
}


bool pds_peer_id_is_allocated(pm_peer_id_t peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return peer_id_is_allocated(peer_id);
}


pm_peer_id_t pds_next_peer_id_get(pm_peer_id_t prev_peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return peer_id_get_next_used(prev_peer_id);
}


pm_peer_id_t pds_next_deleted_peer_id_get(pm_peer_id_t prev_peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return peer_id_get_next_deleted(prev_peer_id);
}


uint32_t pds_peer_count_get(void)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return peer_id_n_ids();
}
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
