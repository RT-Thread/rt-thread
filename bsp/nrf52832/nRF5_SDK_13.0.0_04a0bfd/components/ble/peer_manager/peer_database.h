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
#ifndef PEER_DATABASE_H__
#define PEER_DATABASE_H__

#include <stdint.h>
#include "peer_manager_types.h"
#include "peer_manager_internal.h"
#include "sdk_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @cond NO_DOXYGEN
 * @defgroup peer_database Peer Database
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. A module for simple management of reading and
 *        writing of peer data into persistent storage.
 *
 */

#define PDB_WRITE_BUF_SIZE (sizeof(pm_peer_data_bonding_t)) //!< The size (in bytes) of each block in the internal buffer accessible via @ref pdb_write_buf_get.

/**@brief Events that can come from the peer_database module.
 */
typedef enum
{
    PDB_EVT_WRITE_BUF_STORED,   /**< A @ref pdb_write_buf_store operation has completed successfully. */
    PDB_EVT_RAW_STORED,         /**< A @ref pdb_raw_store operation has completed successfully. */
    PDB_EVT_RAW_STORE_FAILED,   /**< A @ref pdb_raw_store operation has failed. */
    PDB_EVT_CLEARED,            /**< A @ref pdb_clear operation has completed successfully. */
    PDB_EVT_CLEAR_FAILED,       /**< A @ref pdb_clear operation has failed. */
    PDB_EVT_PEER_FREED,         /**< A @ref pdb_peer_free operation has completed successfully. All associated data has been erased. */
    PDB_EVT_PEER_FREE_FAILED,   /**< A @ref pdb_peer_free operation has failed. */
    PDB_EVT_COMPRESSED,         /**< A compress procedure has completed. */
    PDB_EVT_ERROR_NO_MEM,       /**< An operation is blocked because the flash is full. It will be reattempted automatically after the next compress procedure. */
    PDB_EVT_ERROR_UNEXPECTED,   /**< An unexpected error occurred. This is a fatal error. */
} pdb_evt_id_t;

/**@brief Events that can come from the peer_database module.
 */
typedef struct
{
    pdb_evt_id_t      evt_id;  /**< The event that has happened. */
    pm_peer_id_t      peer_id; /**< The id of the peer the event pertains to. */
    pm_peer_data_id_t data_id; /**< The data the event pertains to. */
    union
    {
        struct
        {
            bool update;                   /**< If true, an existing value was overwritten. */
        } write_buf_stored_evt;            /**< Additional information pertaining to the @ref PDB_EVT_WRITE_BUF_STORED event. */
        struct
        {
            pm_store_token_t store_token;  /**< A token identifying the store operation this event pertains to. */
        } raw_stored_evt;                  /**< Additional information pertaining to the @ref PDB_EVT_RAW_STORED event. */
        struct
        {
            pm_store_token_t store_token;  /**< A token identifying the store operation this event pertains to. */
            ret_code_t       err_code;     /**< Error code specifying what went wrong. */
        } error_raw_store_evt;             /**< Additional information pertaining to the @ref PDB_EVT_RAW_STORE_FAILED event. */
        struct
        {
            ret_code_t err_code;           /**< The error that occurred. */
        } clear_failed_evt;                /**< Additional information pertaining to the @ref PDB_EVT_CLEAR_FAILED event. */
        struct
        {
            ret_code_t err_code;           /**< The error that occurred. */
        } peer_free_failed_evt;            /**< Additional information pertaining to the @ref PDB_EVT_PEER_FREE_FAILED event. */
        struct
        {
            ret_code_t err_code;           /**< The unexpected error that occurred. */
        } error_unexpected;                /**< Additional information pertaining to the @ref PDB_EVT_ERROR_UNEXPECTED event. */
    } params;
} pdb_evt_t;

/**@brief Event handler for events from the peer_data_storage module.
 *
 * @param[in]  p_event   The event that has happened.
 */
typedef void (*pdb_evt_handler_t)(pdb_evt_t const * p_event);


/**@brief Function for initializing the module.
 *
 * @retval NRF_SUCCESS          If initialization was successful.
 * @retval NRF_ERROR_INTERNAL   An unexpected error happened.
 */
ret_code_t pdb_init(void);


/**@brief Function for allocating persistent bond storage for a peer.
 *
 * @return  The ID of the newly allocated storage.
 * @retval  PM_PEER_ID_INVALID  If no peer ID is available.
 */
pm_peer_id_t pdb_peer_allocate(void);


/**@brief Function for freeing a peer's persistent bond storage.
 *
 * @note This function will call @ref pdb_write_buf_release on the data for this peer.
 *
 * @param[in] peer_id  ID to be freed.
 *
 * @retval NRF_SUCCESS              Peer ID was released and clear operation was initiated successfully.
 * @retval NRF_ERROR_INVALID_PARAM  Peer ID was invalid.
 * @retval NRF_ERROR_INVALID_STATE  Module is not initialized.
 */
ret_code_t pdb_peer_free(pm_peer_id_t peer_id);


/**@brief Function for retrieving a pointer to peer data in flash (read-only).
 *
 * @note  Dereferencing this pointer is not the safest thing to do if interrupts are enabled,
 *        because Flash Data Storage garbage collection might move the data around. Either disable
 *        interrupts while using the data, or use @ref pdb_peer_data_load.
 *
 * @param[in]  peer_id      The peer the data belongs to.
 * @param[in]  data_id      The data to read.
 * @param[out] p_peer_data  The peer data, read-only.
 *
 * @retval NRF_SUCCESS              If the pointer to the data was retrieved successfully.
 * @retval NRF_ERROR_INVALID_PARAM  If either @p peer_id or @p data_id are invalid.
 * @retval NRF_ERROR_NOT_FOUND      If data was not found in flash.
 */
ret_code_t pdb_peer_data_ptr_get(pm_peer_id_t                 peer_id,
                                 pm_peer_data_id_t            data_id,
                                 pm_peer_data_flash_t * const p_peer_data);


/**@brief Function for retrieving pointers to a write buffer for peer data.
 *
 * @details This function will provide pointers to a buffer of the data. The data buffer will not be
 *          written to persistent storage until @ref pdb_write_buf_store is called. The buffer is
 *          released by calling either @ref pdb_write_buf_release, @ref pdb_write_buf_store, or
 *          @ref pdb_peer_free.
 *
 *          When the data_id refers to a variable length data type, the available size is written
 *          to the data, both the top-level, and any internal length fields.
 *
 * @note Calling this function on a peer_id/data_id pair that already has a buffer created will
 *       give the same buffer, not create a new one. If n_bufs was increased since last time, the
 *       buffer might be relocated to be able to provide additional room. In this case, the data
 *       will be copied. If n_bufs was increased since last time, this function might return @ref
 *       NRF_ERROR_BUSY. In that case, the buffer is automatically released.
 *
 * @param[in]  peer_id      ID of peer to get a write buffer for.
 * @param[in]  data_id      Which piece of data to get.
 * @param[in]  n_bufs       The number of contiguous buffers needed.
 * @param[out] p_peer_data  Pointers to mutable peer data.
 *
 * @retval NRF_SUCCESS              Data retrieved successfully.
 * @retval NRF_ERROR_INVALID_PARAM  Data ID or Peer ID was invalid or unallocated, or n_bufs was 0
 *                                  or more than the total available buffers.
 * @retval NRF_ERROR_NULL           p_peer_data was NULL.
 * @retval NRF_ERROR_BUSY           Not enough buffer(s) available.
 * @retval NRF_ERROR_INTERNAL       Unexpected internal error.
 * @retval NRF_ERROR_INVALID_STATE  Module is not initialized.
 */
ret_code_t pdb_write_buf_get(pm_peer_id_t      peer_id,
                             pm_peer_data_id_t data_id,
                             uint32_t          n_bufs,
                             pm_peer_data_t  * p_peer_data);


/**@brief Function for freeing a write buffer allocated with @ref pdb_write_buf_get.
 *
 * @note This function will not write peer data to persistent memory. Data in released buffer will
 *       be lost.
 *
 * @note This function will undo any previous call to @ref pdb_write_buf_store_prepare for this
 *       piece of data.
 *
 * @param[in]  peer_id  ID of peer to release buffer for.
 * @param[in]  data_id  Which piece of data to release buffer for.
 *
 * @retval NRF_SUCCESS              Successfully released buffer.
 * @retval NRF_ERROR_NOT_FOUND      No buffer was allocated for this peer ID/data ID pair.
 * @retval NRF_ERROR_INVALID_STATE  Module is not initialized.
 * @retval NRF_ERROR_INTERNAL       Unexpected internal error.
 */
ret_code_t pdb_write_buf_release(pm_peer_id_t peer_id, pm_peer_data_id_t data_id);


/**@brief Function for reserving space in persistent storage for data in a buffer.
 *
 * @note This function only works for data which has a write buffer allocated. If the write buffer
 *       is released, this prepare is undone.
 *
 * @note If space has already been reserved for this data, nothing is done.
 *
 * @param[in]  peer_id  The peer whose data to reserve space for.
 * @param[in]  data_id  The type of data to reserve space for.
 *
 * @retval NRF_SUCCESS              Successfully reserved space in persistent storage.
 * @retval NRF_ERROR_STORAGE_FULL   Not enough room in persistent storage.
 * @retval NRF_ERROR_BUSY           Could not process request at this time. Reattempt later.
 * @retval NRF_ERROR_NOT_FOUND      No buffer has been allocated for this peer ID/data ID pair.
 * @retval NRF_ERROR_INVALID_PARAM  Data ID or Peer ID was invalid or unallocated.
 * @retval NRF_ERROR_INVALID_STATE  Module is not initialized.
 */
ret_code_t pdb_write_buf_store_prepare(pm_peer_id_t peer_id, pm_peer_data_id_t data_id);


/**@brief Function for writing data into persistent storage. Writing happens asynchronously.
 *
 * @note This will unlock the data after it has been written.
 *
 * @param[in]  peer_id      ID of peer to store data for.
 * @param[in]  data_id      Which piece of data to store.
 *
 * @retval NRF_SUCCESS              Data storing was successfully started.
 * @retval NRF_ERROR_STORAGE_FULL   No space available in persistent storage. Please clear some
 *                                  space, the operation will be reattempted after the next compress
 *                                  procedure. This error will not happen if
 *                                  @ref pdb_write_buf_store_prepare is called beforehand.
 * @retval NRF_ERROR_INVALID_PARAM  Data ID was invalid.
 * @retval NRF_ERROR_NOT_FOUND      No buffer has been allocated for this peer ID/data ID pair.
 * @retval NRF_ERROR_INVALID_STATE  Module is not initialized.
 * @retval NRF_ERROR_INTERNAL       Unexpected internal error.
 */
ret_code_t pdb_write_buf_store(pm_peer_id_t      peer_id,
                               pm_peer_data_id_t data_id);


/**@brief Function for clearing data from persistent storage.
 *
 * @param[in]  peer_id  ID of peer to clear data for.
 * @param[in]  data_id  Which piece of data to clear.
 *
 * @retval NRF_SUCCESS              The clear was initiated successfully.
 * @retval NRF_ERROR_INVALID_PARAM  Data ID or peer ID was invalid.
 * @retval NRF_ERROR_NOT_FOUND      Nothing to clear for this peer ID/data ID combination.
 * @retval NRF_ERROR_BUSY           Underlying modules are busy and can't take any more requests at
 *                                  this moment.
 * @retval NRF_ERROR_INVALID_STATE  Module is not initialized.
 * @retval NRF_ERROR_INTERNAL       Internal error.
 */
ret_code_t pdb_clear(pm_peer_id_t peer_id, pm_peer_data_id_t data_id);


/**@brief Function for querying the number of valid peer IDs available. I.E the number of peers
 *        in persistent storage.
 *
 * @return  The number of valid peer IDs.
 */
uint32_t pdb_n_peers(void);


/**@brief Function for getting the next peer ID in the sequence of all used peer IDs. Can be
 *        used to loop through all used peer IDs.
 *
 * @note @ref PM_PEER_ID_INVALID is considered to be before the first and after the last ordinary
 *       peer ID.
 *
 * @param[in]  prev_peer_id  The previous peer ID.
 *
 * @return  The next peer ID.
 * @return  The first ordinary peer ID  if prev_peer_id was @ref PM_PEER_ID_INVALID.
 * @retval  PM_PEER_ID_INVALID          if prev_peer_id was the last ordinary peer ID.
 */
pm_peer_id_t pdb_next_peer_id_get(pm_peer_id_t prev_peer_id);


/**@brief Function for getting the next peer ID in the sequence of all peer IDs pending deletion.
 *        Can be used to loop through all used peer IDs.
 *
 * @note @ref PM_PEER_ID_INVALID is considered to be before the first and after the last ordinary
 *       peer ID.
 *
 * @param[in]  prev_peer_id  The previous peer ID.
 *
 * @return  The next peer ID pending deletion.
 * @return  The first ordinary peer ID  if prev_peer_id was @ref PM_PEER_ID_INVALID.
 * @retval  PM_PEER_ID_INVALID          if prev_peer_id was the last ordinary peer ID.
 */
pm_peer_id_t pdb_next_deleted_peer_id_get(pm_peer_id_t prev_peer_id);


/**@brief Function for updating currently stored peer data to a new version
 *
 * @details Updating happens asynchronously.
 *          Expect a @ref PDS_EVT_STORED or @ref PDS_EVT_ERROR_STORE for the store token
 *          and a @ref PDS_EVT_ERROR_CLEAR or @ref PDS_EVT_ERROR_CLEAR for the old token
 *
 * @param[in]   peer_data           New data
 * @param[in]   old_token           Store token for the old data
 * @param[out]  p_store_token       Store token for the new data
 *
 * @retval NRF_SUCESS               The update was initiated successfully
 * @retval NRF_ERROR_NOT_FOUND      The old store token was invalid.
 * @retval NRF_ERROR_NULL           Data contained a NULL pointer.
 * @retval NRF_ERROR_STORAGE_FULL   No space available in persistent storage.
 * @retval NRF_ERROR_BUSY           FDS or underlying modules are busy and can't take any
 *                                  more requests
 * @retval NRF_ERROR_INVALID_STATE  Module is not initialized.
 */
ret_code_t pdb_peer_data_update(pm_peer_data_const_t        peer_data,
                                pm_store_token_t            old_token,
                                pm_store_token_t          * p_store_token);


/**@brief Function for copy peer data from flash into a provided buffer.
 *
 * @param[in]    peer_id      The peer the data belongs to.
 * @param[in]    data_id      The data to read.
 * @param[inout] p_peer_data  The buffer where to copy data into. The field @c length_words in this
 *                            parameter must represent the buffer length in words.
 *
 * @note Actually, it represents the buffer length in bytes upon entering the function,
 * and upon exit it represents the length of the data in words.. not good. Fix this.
 *
 * @retval NRF_SUCCESS              If the operation was successful.
 * @retval NRF_ERROR_INVALID_PARAM  If @p peer_id or @p data_id are invalid.
 * @retval NRF_ERROR_NOT_FOUND      If the data was not found in flash.
 * @retval NRF_ERROR_NO_MEM         If the provided buffer is too small.
 */
ret_code_t pdb_peer_data_load(pm_peer_id_t              peer_id,
                              pm_peer_data_id_t         data_id,
                              pm_peer_data_t    * const p_peer_data);


/**@brief Function for writing data directly to persistent storage from external memory.
 *
 * @param[in]  peer_id        ID of peer to write data for.
 * @param[in]  p_peer_data    Data to store.
 * @param[out] p_store_token  A token identifying this particular store operation. The token can be
 *                            used to identify events pertaining to this operation.
 *
 * @retval NRF_SUCCESS               Data successfully written.
 * @retval NRF_ERROR_INVALID_PARAM   Data ID or Peer ID was invalid or unallocated.
 * @retval NRF_ERROR_NULL            p_peer_data contained a NULL pointer.
 * @retval NRF_ERROR_STORAGE_FULL    No space available in persistent storage.
 * @retval NRF_ERROR_INVALID_LENGTH  Data length above the maximum allowed.
 * @retval NRF_ERROR_BUSY            Unable to perform operation at this time.
 */
ret_code_t pdb_raw_store(pm_peer_id_t           peer_id,
                         pm_peer_data_const_t * p_peer_data,
                         pm_store_token_t     * p_store_token);

/** @}
 * @endcond
 */


#ifdef __cplusplus
}
#endif

#endif /* PEER_DATABASE_H__ */


