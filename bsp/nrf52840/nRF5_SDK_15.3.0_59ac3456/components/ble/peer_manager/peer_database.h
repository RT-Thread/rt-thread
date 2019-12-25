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

/**@brief Macro for creating a peer ID value from a connection handle.
 *
 * Use this macro with pdb_write_buf_get() or pdb_write_buf_store(). It allows to create a write buffer
 * even if you do not yet know the proper peer ID the data will be stored for.
 *
 * @return @p conn_handle + @ref PM_PEER_ID_N_AVAILABLE_IDS.
 */
#define PDB_TEMP_PEER_ID(conn_handle) (PM_PEER_ID_N_AVAILABLE_IDS + conn_handle)


/**@brief Function for initializing the module.
 *
 * @retval NRF_SUCCESS          If initialization was successful.
 * @retval NRF_ERROR_INTERNAL   An unexpected error happened.
 */
ret_code_t pdb_init(void);

/**@brief Function for freeing a peer's persistent bond storage.
 *
 * @note This function will call @ref pdb_write_buf_release on the data for this peer.
 *
 * @param[in] peer_id  ID to be freed.
 *
 * @retval NRF_SUCCESS              Peer ID was released and clear operation was initiated successfully.
 * @retval NRF_ERROR_INVALID_PARAM  Peer ID was invalid.
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
 * @param[in]  peer_id      ID of the peer to get a write buffer for. If @p peer_id is larger than
 *                          @ref PM_PEER_ID_N_AVAILABLE_IDS, it is interpreted as pertaining to
 *                          the connection with connection handle peer_id - PM_PEER_ID_N_AVAILABLE_IDS.
 *                          See @ref PDB_TEMP_PEER_ID.
 * @param[in]  data_id      The piece of data to get.
 * @param[in]  n_bufs       Number of contiguous buffers needed.
 * @param[out] p_peer_data  Pointers to mutable peer data.
 *
 * @retval NRF_SUCCESS              Data retrieved successfully.
 * @retval NRF_ERROR_INVALID_PARAM  @p data_id was invalid, or @p n_bufs was 0 or more than the total
 *                                  available buffers.
 * @retval NRF_ERROR_FORBIDDEN      n_bufs was higher or lower than the existing buffer. If needed,
 *                                  release the existing buffer with @ref pdb_write_buf_release, and
 *                                  call this function again.
 * @retval NRF_ERROR_NULL           p_peer_data was NULL.
 * @retval NRF_ERROR_BUSY           Not enough buffer(s) available.
 * @retval NRF_ERROR_INTERNAL       Unexpected internal error.
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
 * @param[in]  peer_id  ID of peer to release buffer for.
 * @param[in]  data_id  Which piece of data to release buffer for.
 *
 * @retval NRF_SUCCESS              Successfully released buffer.
 * @retval NRF_ERROR_NOT_FOUND      No buffer was allocated for this peer ID/data ID pair.
 */
ret_code_t pdb_write_buf_release(pm_peer_id_t peer_id, pm_peer_data_id_t data_id);

/**@brief Function for writing data into persistent storage. Writing happens asynchronously.
 *
 * @note This will unlock the data after it has been written.
 *
 * @param[in]  peer_id      The ID used to address the write buffer.
 * @param[in]  data_id      The piece of data to store.
 * @param[in]  new_peer_id  The ID to put in flash. This is usually the same as peer_id, but
 *                          must be valid, i.e. allocated (and smaller than @ref PM_PEER_ID_N_AVAILABLE_IDS).
 *
 * @retval NRF_SUCCESS              Data storing was successfully started.
 * @retval NRF_ERROR_STORAGE_FULL   No space available in persistent storage. Please clear some
 *                                  space, the operation will be reattempted after the next compress
 *                                  procedure.
 * @retval NRF_ERROR_INVALID_PARAM  @p data_id or @p new_peer_id was invalid.
 * @retval NRF_ERROR_NOT_FOUND      No buffer has been allocated for this peer ID/data ID pair.
 * @retval NRF_ERROR_INTERNAL       Unexpected internal error.
 */
ret_code_t pdb_write_buf_store(pm_peer_id_t      peer_id,
                               pm_peer_data_id_t data_id,
                               pm_peer_id_t      new_peer_id);

/** @}
 * @endcond
 */


#ifdef __cplusplus
}
#endif

#endif /* PEER_DATABASE_H__ */


