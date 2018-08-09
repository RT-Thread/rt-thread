/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#include "peer_database.h"

#include <string.h>
#include "peer_manager_types.h"
#include "peer_manager_internal.h"
#include "peer_data_storage.h"
#include "pm_buffer.h"


/**@brief Macro for verifying that the data ID is among the values eligible for using the write buffer.
 *
 * @param[in] data_id  The data ID to verify.
 */
// @note emdi: could this maybe be a function?
#define VERIFY_DATA_ID_WRITE_BUF(data_id)                                                    \
do                                                                                           \
{                                                                                            \
    if (((data_id) != PM_PEER_DATA_ID_BONDING) && ((data_id) != PM_PEER_DATA_ID_GATT_LOCAL)) \
    {                                                                                        \
        return NRF_ERROR_INVALID_PARAM;                                                      \
    }                                                                                        \
} while (0)


// The number of registered event handlers.
#define PDB_EVENT_HANDLERS_CNT      (sizeof(m_evt_handlers) / sizeof(m_evt_handlers[0]))


// Peer Database event handlers in other Peer Manager submodules.
extern void pm_pdb_evt_handler(pm_evt_t * p_event);
extern void sm_pdb_evt_handler(pm_evt_t * p_event);
#if !defined(PM_SERVICE_CHANGED_ENABLED) || (PM_SERVICE_CHANGED_ENABLED == 1)
extern void gscm_pdb_evt_handler(pm_evt_t * p_event);
#endif
extern void gcm_pdb_evt_handler(pm_evt_t * p_event);

// Peer Database events' handlers.
// The number of elements in this array is PDB_EVENT_HANDLERS_CNT.
static pm_evt_handler_internal_t const m_evt_handlers[] =
{
    pm_pdb_evt_handler,
    sm_pdb_evt_handler,
#if !defined(PM_SERVICE_CHANGED_ENABLED) || (PM_SERVICE_CHANGED_ENABLED == 1)
    gscm_pdb_evt_handler,
#endif
    gcm_pdb_evt_handler,
};


/**@brief Struct for keeping track of one write buffer, from allocation, until it is fully written
 *        or cancelled.
 */
typedef struct
{
    pm_peer_id_t        peer_id;               /**< The peer ID this buffer belongs to. */
    pm_peer_data_id_t   data_id;               /**< The data ID this buffer belongs to. */
    pm_prepare_token_t  prepare_token;         /**< Token given by Peer Data Storage if room in flash has been reserved. */
    pm_store_token_t    store_token;           /**< Token given by Peer Data Storage when a flash write has been successfully requested. This is used as the check for whether such an operation has been successfully requested. */
    uint8_t             n_bufs;                /**< The number of buffer blocks containing peer data. */
    uint8_t             buffer_block_id;       /**< The index of the first (or only) buffer block containing peer data. */
    uint8_t             store_flash_full : 1;  /**< Flag indicating that the buffer was attempted written to flash, but a flash full error was returned and the operation should be retried after room has been made. */
    uint8_t             store_busy       : 1;  /**< Flag indicating that the buffer was attempted written to flash, but a busy error was returned and the operation should be retried. */
} pdb_buffer_record_t;


static bool                m_module_initialized;
static pm_buffer_t         m_write_buffer;                                 /**< The internal states of the write buffer. */
static pdb_buffer_record_t m_write_buffer_records[PM_FLASH_BUFFERS];       /**< The available write buffer records. */
static bool                m_pending_store = false;                        /**< Whether there are any pending (Not yet successfully requested in Peer Data Storage) store operations. This flag is for convenience only. The real bookkeeping is in the records (@ref m_write_buffer_records). */



/**@brief Function for invalidating a record of a write buffer allocation.
 *
 * @param[in]  p_record  The record to invalidate.
 */
static void write_buffer_record_invalidate(pdb_buffer_record_t * p_record)
{
    p_record->peer_id          = PM_PEER_ID_INVALID;
    p_record->data_id          = PM_PEER_DATA_ID_INVALID;
    p_record->buffer_block_id  = PM_BUFFER_INVALID_ID;
    p_record->store_busy       = false;
    p_record->store_flash_full = false;
    p_record->n_bufs           = 0;
    p_record->prepare_token    = PDS_PREPARE_TOKEN_INVALID;
    p_record->store_token      = PM_STORE_TOKEN_INVALID;
}


/**@brief Function for finding a record of a write buffer allocation.
 *
 * @param[in]    peer_id  The peer ID in the record.
 * @param[inout] p_index  In: The starting index, out: The index of the record
 *
 * @return  A pointer to the matching record, or NULL if none was found.
 */
static pdb_buffer_record_t * write_buffer_record_find_next(pm_peer_id_t peer_id, uint32_t * p_index)
{
    for (uint32_t i = *p_index; i < PM_FLASH_BUFFERS; i++)
    {
        if ((m_write_buffer_records[i].peer_id == peer_id))
        {
            *p_index = i;
            return &m_write_buffer_records[i];
        }
    }
    return NULL;
}


/**@brief Function for finding a record of a write buffer allocation.
 *
 * @param[in]  peer_id  The peer ID in the record.
 * @param[in]  data_id  The data ID in the record.
 *
 * @return  A pointer to the matching record, or NULL if none was found.
 */
static pdb_buffer_record_t * write_buffer_record_find(pm_peer_id_t      peer_id,
                                                      pm_peer_data_id_t data_id)
{
    uint32_t index = 0;
    pdb_buffer_record_t * p_record = write_buffer_record_find_next(peer_id, &index);

    while ((p_record != NULL) && ( (p_record->data_id != data_id)
                                || (p_record->store_busy)
                                || (p_record->store_flash_full)
                                || (p_record->store_token != PM_STORE_TOKEN_INVALID)))
    {
        index++;
        p_record = write_buffer_record_find_next(peer_id, &index);
    }

    return p_record;
}


/**@brief Function for finding a record of a write buffer allocation that has been sent to be stored.
 *
 * @param[in]  store_token  The store token received when store was called for the record.
 *
 * @return  A pointer to the matching record, or NULL if none was found.
 */
static pdb_buffer_record_t * write_buffer_record_find_stored(pm_store_token_t store_token)
{
    for (int i = 0; i < PM_FLASH_BUFFERS; i++)
    {
        if (m_write_buffer_records[i].store_token == store_token)
        {
            return &m_write_buffer_records[i];
        }
    }
    return NULL;
}


/**@brief Function for finding an available record for write buffer allocation.
 *
 * @return  A pointer to the available record, or NULL if none was found.
 */
static pdb_buffer_record_t * write_buffer_record_find_unused(void)
{
    return write_buffer_record_find(PM_PEER_ID_INVALID, PM_PEER_DATA_ID_INVALID);
}


/**@brief Function for gracefully deactivating a write buffer record.
 *
 * @details This function will first release any buffers, then invalidate the record.
 *
 * @param[inout] p_write_buffer_record  The record to release.
 *
 * @return  A pointer to the matching record, or NULL if none was found.
 */
static void write_buffer_record_release(pdb_buffer_record_t * p_write_buffer_record)
{
    for (uint32_t i = 0; i < p_write_buffer_record->n_bufs; i++)
    {
        pm_buffer_release(&m_write_buffer, p_write_buffer_record->buffer_block_id + i);
    }

    write_buffer_record_invalidate(p_write_buffer_record);
}


/**@brief Function for claiming and activating a write buffer record.
 *
 * @param[out] pp_write_buffer_record  The claimed record.
 * @param[in]  peer_id                 The peer ID this record should have.
 * @param[in]  data_id                 The data ID this record should have.
 */
static void write_buffer_record_acquire(pdb_buffer_record_t ** pp_write_buffer_record,
                                        pm_peer_id_t           peer_id,
                                        pm_peer_data_id_t      data_id)
{
    if (pp_write_buffer_record == NULL)
    {
        return;
    }
    *pp_write_buffer_record = write_buffer_record_find_unused();
    if (*pp_write_buffer_record == NULL)
    {
        // This also means the buffer is full.
        return;
    }
    (*pp_write_buffer_record)->peer_id = peer_id;
    (*pp_write_buffer_record)->data_id = data_id;
}


/**@brief Function for dispatching outbound events to all registered event handlers.
 *
 * @param[in]  p_event  The event to dispatch.
 */
static void pdb_evt_send(pm_evt_t * p_event)
{
    for (uint32_t i = 0; i < PDB_EVENT_HANDLERS_CNT; i++)
    {
        m_evt_handlers[i](p_event);
    }
}


/**@brief Function for resetting the internal state of the Peer Database module.
 *
 * @param[out] p_event  The event to dispatch.
 */
static void internal_state_reset()
{
    for (uint32_t i = 0; i < PM_FLASH_BUFFERS; i++)
    {
        write_buffer_record_invalidate(&m_write_buffer_records[i]);
    }
}


static void peer_data_point_to_buffer(pm_peer_data_t * p_peer_data, pm_peer_data_id_t data_id, uint8_t * p_buffer_memory, uint16_t n_bufs)
{
    uint16_t n_bytes = n_bufs * PDB_WRITE_BUF_SIZE;
    p_peer_data->data_id    = data_id;

    p_peer_data->p_all_data   = (pm_peer_data_bonding_t *)p_buffer_memory;
    p_peer_data->length_words = BYTES_TO_WORDS(n_bytes);
}


static void peer_data_const_point_to_buffer(pm_peer_data_const_t * p_peer_data, pm_peer_data_id_t data_id,  uint8_t * p_buffer_memory, uint32_t n_bufs)
{
    peer_data_point_to_buffer((pm_peer_data_t*)p_peer_data, data_id, p_buffer_memory, n_bufs);
}


static void write_buf_length_words_set(pm_peer_data_const_t * p_peer_data)
{
    switch (p_peer_data->data_id)
    {
        case PM_PEER_DATA_ID_BONDING:
            p_peer_data->length_words = PM_BONDING_DATA_N_WORDS();
            break;
        case PM_PEER_DATA_ID_SERVICE_CHANGED_PENDING:
            p_peer_data->length_words = PM_SC_STATE_N_WORDS();
            break;
        case PM_PEER_DATA_ID_PEER_RANK:
            p_peer_data->length_words = PM_USAGE_INDEX_N_WORDS();
            break;
        case PM_PEER_DATA_ID_GATT_LOCAL:
            p_peer_data->length_words = PM_LOCAL_DB_N_WORDS(p_peer_data->p_local_gatt_db->len);
            break;
        default:
            // No action needed.
            break;
    }
}


/**@brief Function for writing data into persistent storage. Writing happens asynchronously.
 *
 * @note This will unlock the data after it has been written.
 *
 * @param[in]  p_write_buffer_record  The write buffer record to write into persistent storage.
 *
 * @retval NRF_SUCCESS              Data storing was successfully started.
 * @retval NRF_ERROR_STORAGE_FULL   No space available in persistent storage. Please clear some
 *                                  space, the operation will be reattempted after the next compress
 *                                  procedure. This error will not happen if
 *                                  @ref pdb_write_buf_store_prepare is called beforehand.
 * @retval NRF_ERROR_INVALID_PARAM  Data ID was invalid.
 * @retval NRF_ERROR_INVALID_STATE  Module is not initialized.
 * @retval NRF_ERROR_INTERNAL       Unexpected internal error.
 */
ret_code_t write_buf_store(pdb_buffer_record_t * p_write_buffer_record)
{
    ret_code_t            err_code = NRF_SUCCESS;
    pm_peer_data_const_t  peer_data = {.data_id = p_write_buffer_record->data_id};
    uint8_t             * p_buffer_memory;

    p_buffer_memory = pm_buffer_ptr_get(&m_write_buffer, p_write_buffer_record->buffer_block_id);
    if (p_buffer_memory == NULL)
    {
        return NRF_ERROR_INTERNAL;
    }

    peer_data_const_point_to_buffer(&peer_data,
                                     p_write_buffer_record->data_id,
                                     p_buffer_memory,
                                     p_write_buffer_record->n_bufs);
    write_buf_length_words_set(&peer_data);

    err_code = pds_peer_data_store(p_write_buffer_record->peer_id,
                                   &peer_data,
                                   p_write_buffer_record->prepare_token,
                                   &p_write_buffer_record->store_token);


    switch (err_code)
    {
        case NRF_SUCCESS:
            p_write_buffer_record->store_busy       = false;
            p_write_buffer_record->store_flash_full = false;
            break;

        case NRF_ERROR_BUSY:
            p_write_buffer_record->store_busy       = true;
            p_write_buffer_record->store_flash_full = false;
            m_pending_store                         = true;

            err_code = NRF_SUCCESS;
            break;

        case NRF_ERROR_STORAGE_FULL:
            p_write_buffer_record->store_busy       = false;
            p_write_buffer_record->store_flash_full = true;
            m_pending_store                         = true;
            break;

        case NRF_ERROR_INVALID_PARAM:
            // No action.
            break;

        default:
            err_code = NRF_ERROR_INTERNAL;
            break;
    }

    return err_code;
}


/**@brief This calls @ref write_buf_store and sends events based on the return value.
 *
 * See @ref write_buf_store for more info.
 *
 * @return  Whether or not the store operation succeeded.
 */
static bool write_buf_store_in_event(pdb_buffer_record_t * p_write_buffer_record)
{
    ret_code_t err_code;
    pm_evt_t   event;

    err_code = write_buf_store(p_write_buffer_record);
    if (err_code != NRF_SUCCESS)
    {
        event.conn_handle = BLE_CONN_HANDLE_INVALID;
        event.peer_id     = p_write_buffer_record->peer_id;

        if (err_code == NRF_ERROR_STORAGE_FULL)
        {
            event.evt_id = PM_EVT_STORAGE_FULL;
        }
        else
        {
            event.evt_id                        = PM_EVT_ERROR_UNEXPECTED;
            event.params.error_unexpected.error = err_code;
        }

        pdb_evt_send(&event);

        return false;
    }

    return true;
}


/**@brief This reattempts store operations on write buffers, that previously failed because of @ref
 *        NRF_ERROR_BUSY or @ref NRF_ERROR_STORAGE_FULL errors.
 *
 * param[in]  retry_flash_full  Whether to retry operations that failed because of an
 *                              @ref NRF_ERROR_STORAGE_FULL error.
 */
static void reattempt_previous_operations(bool retry_flash_full)
{
    bool found_pending_operation = false;

    if (!m_pending_store)
    {
        return;
    }

    for (uint32_t i = 0; i < PM_FLASH_BUFFERS; i++)
    {
        if  ((m_write_buffer_records[i].store_busy)
          || (m_write_buffer_records[i].store_flash_full && retry_flash_full))
        {
            found_pending_operation = true;

            bool success = write_buf_store_in_event(&m_write_buffer_records[i]);

            if (!success)
            {
                return;
            }
        }
    }

    if (!found_pending_operation)
    {
        // All records have been searched and none were pending.
        // Clear flag so records aren't searched.
        m_pending_store = false;
    }
}


/**@brief Function for handling events from the Peer Data Storage module.
 *        This function is extern in Peer Data Storage.
 *
 * @param[in]  p_event  The event to handle.
 */
void pdb_pds_evt_handler(pm_evt_t * p_event)
{
    pdb_buffer_record_t * p_write_buffer_record;
    bool                  evt_send         = true;
    bool                  retry_flash_full = false;

    p_write_buffer_record = write_buffer_record_find_stored(p_event->params.peer_data_update_succeeded.token);

    switch (p_event->evt_id)
    {
        case PM_EVT_PEER_DATA_UPDATE_SUCCEEDED:
            if (   (p_event->params.peer_data_update_succeeded.action == PM_PEER_DATA_OP_UPDATE)
                && (p_write_buffer_record != NULL))
            {
                // The write came from PDB.
                write_buffer_record_release(p_write_buffer_record);
            }
            break;

        case PM_EVT_PEER_DATA_UPDATE_FAILED:
            if (   (p_event->params.peer_data_update_succeeded.action == PM_PEER_DATA_OP_UPDATE)
                && (p_write_buffer_record != NULL))
            {
                // The write came from PDB, retry.
                p_write_buffer_record->store_token = PM_STORE_TOKEN_INVALID;
                p_write_buffer_record->store_busy  = true;
                m_pending_store                    = true;
                evt_send                           = false;
            }
            break;

        case PM_EVT_FLASH_GARBAGE_COLLECTED:
            retry_flash_full = true;
            break;

        default:
            break;
    }

    if (evt_send)
    {
        // Forward the event to all registered Peer Database event handlers.
        pdb_evt_send(p_event);
    }

    reattempt_previous_operations(retry_flash_full);
}


ret_code_t pdb_init()
{
    ret_code_t ret;

    NRF_PM_DEBUG_CHECK(!m_module_initialized);

    internal_state_reset();

    PM_BUFFER_INIT(&m_write_buffer, PM_FLASH_BUFFERS, PDB_WRITE_BUF_SIZE, ret);

    if (ret != NRF_SUCCESS)
    {
        return NRF_ERROR_INTERNAL;
    }

    m_module_initialized = true;

    return NRF_SUCCESS;
}


pm_peer_id_t pdb_peer_allocate(void)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return pds_peer_id_allocate();
}


ret_code_t pdb_peer_free(pm_peer_id_t peer_id)
{
    ret_code_t err_code_in  = NRF_SUCCESS;
    ret_code_t err_code_out = NRF_SUCCESS;

    NRF_PM_DEBUG_CHECK(m_module_initialized);

    uint32_t index = 0;
    pdb_buffer_record_t * p_record = write_buffer_record_find_next(peer_id, &index);

    while (p_record != NULL)
    {
        err_code_in = pdb_write_buf_release(peer_id, p_record->data_id);

        if (   (err_code_in != NRF_SUCCESS)
            && (err_code_in != NRF_ERROR_NOT_FOUND))
        {
            err_code_out = NRF_ERROR_INTERNAL;
        }

        index++;
        p_record = write_buffer_record_find_next(peer_id, &index);
    }

    if (err_code_out == NRF_SUCCESS)
    {
        err_code_in = pds_peer_id_free(peer_id);

        if (err_code_in == NRF_SUCCESS)
        {
            // No action needed.
        }
        else if (err_code_in == NRF_ERROR_INVALID_PARAM)
        {
            err_code_out = NRF_ERROR_INVALID_PARAM;
        }
        else
        {
            err_code_out = NRF_ERROR_INTERNAL;
        }
    }

    return err_code_out;
}


ret_code_t pdb_peer_data_ptr_get(pm_peer_id_t                 peer_id,
                                 pm_peer_data_id_t            data_id,
                                 pm_peer_data_flash_t * const p_peer_data)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_peer_data != NULL);

    // Pass NULL to only retrieve a pointer.
    return pds_peer_data_read(peer_id, data_id, (pm_peer_data_t*)p_peer_data, NULL);
}



ret_code_t pdb_write_buf_get(pm_peer_id_t      peer_id,
                             pm_peer_data_id_t data_id,
                             uint32_t          n_bufs,
                             pm_peer_data_t  * p_peer_data)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    VERIFY_PARAM_NOT_NULL(p_peer_data);
    VERIFY_DATA_ID_WRITE_BUF(data_id);

    if (   (n_bufs == 0)
        || (n_bufs > PM_FLASH_BUFFERS)
        || !pds_peer_id_is_allocated(peer_id))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    pdb_buffer_record_t * p_write_buffer_record;
    uint8_t             * p_buffer_memory;
    bool                  new_record = false;

    p_write_buffer_record = write_buffer_record_find(peer_id, data_id);

    if (p_write_buffer_record == NULL)
    {
        // No buffer exists.
        write_buffer_record_acquire(&p_write_buffer_record, peer_id, data_id);
        if (p_write_buffer_record == NULL)
        {
            return NRF_ERROR_BUSY;
        }
    }
    else if (p_write_buffer_record->n_bufs != n_bufs)
    {
        // Buffer exists with a different n_bufs from what was requested.
        return NRF_ERROR_FORBIDDEN;
    }

    if (p_write_buffer_record->buffer_block_id == PM_BUFFER_INVALID_ID)
    {
        p_write_buffer_record->buffer_block_id = pm_buffer_block_acquire(&m_write_buffer, n_bufs);

        if (p_write_buffer_record->buffer_block_id == PM_BUFFER_INVALID_ID)
        {
            write_buffer_record_invalidate(p_write_buffer_record);
            return NRF_ERROR_BUSY;
        }

        new_record = true;
    }

    p_write_buffer_record->n_bufs = n_bufs;

    p_buffer_memory = pm_buffer_ptr_get(&m_write_buffer, p_write_buffer_record->buffer_block_id);

    if (p_buffer_memory == NULL)
    {
        return NRF_ERROR_INTERNAL;
    }

    peer_data_point_to_buffer(p_peer_data, data_id, p_buffer_memory, n_bufs);
    if (new_record && (data_id == PM_PEER_DATA_ID_GATT_LOCAL))
    {
        p_peer_data->p_local_gatt_db->len = PM_LOCAL_DB_LEN(p_peer_data->length_words);
    }

    return NRF_SUCCESS;
}


ret_code_t pdb_write_buf_release(pm_peer_id_t peer_id, pm_peer_data_id_t data_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    ret_code_t            err_code = NRF_SUCCESS;
    pdb_buffer_record_t * p_write_buffer_record;
    p_write_buffer_record = write_buffer_record_find(peer_id, data_id);

    if (p_write_buffer_record == NULL)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    if (p_write_buffer_record->prepare_token != PDS_PREPARE_TOKEN_INVALID)
    {
        err_code = pds_space_reserve_cancel(p_write_buffer_record->prepare_token);
        if (err_code != NRF_SUCCESS)
        {
            err_code = NRF_ERROR_INTERNAL;
        }
    }

    write_buffer_record_release(p_write_buffer_record);

    return err_code;
}


ret_code_t pdb_write_buf_store_prepare(pm_peer_id_t peer_id, pm_peer_data_id_t data_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    VERIFY_DATA_ID_WRITE_BUF(data_id);

    ret_code_t            err_code = NRF_SUCCESS;
    pdb_buffer_record_t * p_write_buffer_record;
    p_write_buffer_record = write_buffer_record_find(peer_id, data_id);

    if (p_write_buffer_record == NULL)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    if (p_write_buffer_record->prepare_token == PDS_PREPARE_TOKEN_INVALID)
    {
        uint8_t * p_buffer_memory = pm_buffer_ptr_get(&m_write_buffer,
                                                       p_write_buffer_record->buffer_block_id);
        pm_peer_data_const_t peer_data = {.data_id = data_id};

        if (p_buffer_memory == NULL)
        {
            return NRF_ERROR_INTERNAL;
        }

        peer_data_const_point_to_buffer(&peer_data, data_id, p_buffer_memory, p_write_buffer_record->n_bufs);

        write_buf_length_words_set(&peer_data);

        err_code = pds_space_reserve(&peer_data, &p_write_buffer_record->prepare_token);
        if (err_code == NRF_ERROR_INVALID_LENGTH)
        {
            return NRF_ERROR_INTERNAL;
        }
    }

    return err_code;
}


ret_code_t pdb_write_buf_store(pm_peer_id_t      peer_id,
                               pm_peer_data_id_t data_id,
                               pm_peer_id_t      new_peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);

    VERIFY_DATA_ID_WRITE_BUF(data_id);

    pdb_buffer_record_t * p_write_buffer_record = write_buffer_record_find(peer_id, data_id);

    if (p_write_buffer_record == NULL)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    p_write_buffer_record->peer_id = new_peer_id;
    p_write_buffer_record->data_id = data_id;
    return write_buf_store(p_write_buffer_record);
}


ret_code_t pdb_clear(pm_peer_id_t peer_id, pm_peer_data_id_t data_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return pds_peer_data_delete(peer_id, data_id);
}


uint32_t pdb_n_peers(void)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return pds_peer_count_get();
}


pm_peer_id_t pdb_next_peer_id_get(pm_peer_id_t prev_peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return pds_next_peer_id_get(prev_peer_id);
}


pm_peer_id_t pdb_next_deleted_peer_id_get(pm_peer_id_t prev_peer_id)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return pds_next_deleted_peer_id_get(prev_peer_id);
}


ret_code_t pdb_peer_data_load(pm_peer_id_t              peer_id,
                        pm_peer_data_id_t data_id,
                              pm_peer_data_t    * const p_peer_data)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    NRF_PM_DEBUG_CHECK(p_peer_data != NULL);

    // Provide the buffer length in bytes.
    uint32_t const data_len_bytes = (p_peer_data->length_words * sizeof(uint32_t));
    return pds_peer_data_read(peer_id, data_id, p_peer_data, &data_len_bytes);
}


ret_code_t pdb_raw_store(pm_peer_id_t         peer_id,
                         pm_peer_data_const_t * p_peer_data,
                         pm_store_token_t   * p_store_token)
{
    NRF_PM_DEBUG_CHECK(m_module_initialized);
    return pds_peer_data_store(peer_id, p_peer_data, PDS_PREPARE_TOKEN_INVALID, p_store_token);
}
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
