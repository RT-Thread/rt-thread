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
#ifndef PEER_ID_H__
#define PEER_ID_H__


#include <stdint.h>
#include "sdk_errors.h"
#include "ble_gap.h"
#include "peer_manager_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @cond NO_DOXYGEN
 * @defgroup peer_id Peer IDs
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. This module keeps track of which peer IDs are in
 *        use and which are free.
 */


/**@brief Function for initializing the module.
 */
void peer_id_init(void);


/**@brief Function for claiming an unused peer ID.
 *
 * @param peer_id  The peer ID to allocate. If this is @ref PM_PEER_ID_INVALID, the first available
 *                 will be allocated.
 *
 * @return  The allocated peer ID.
 * @retval  PM_PEER_ID_INVALID  If no peer ID could be allocated or module is not initialized.
 */
pm_peer_id_t peer_id_allocate(pm_peer_id_t peer_id);


/**@brief Function for marking a peer ID for deletion.
 *
 * @param peer_id  The peer ID to delete.
 *
 * @retval  true   Deletion was successful.
 * @retval  false  Peer ID already marked for deletion, peer_id was PM_PEER_ID_INVALID, or module is
 *                 not initialized.
 */
bool peer_id_delete(pm_peer_id_t peer_id);


/**@brief Function for freeing a peer ID and clearing all data associated with it in persistent
 *        storage.
 *
 * @param[in]  peer_id  Peer ID to free.
 */
void peer_id_free(pm_peer_id_t peer_id);


/**@brief Function for finding out whether a peer ID is marked for deletion.
 *
 * @param[in]  peer_id  The peer ID to inquire about.
 *
 * @retval  true   peer_id is in marked for deletion.
 * @retval  false  peer_id is not marked for deletion, or the module is not initialized.
 */
bool peer_id_is_deleted(pm_peer_id_t peer_id);


/**@brief Function for finding out whether a peer ID is in use.
 *
 * @param[in]  peer_id  The peer ID to inquire about.
 *
 * @retval  true   peer_id is in use.
 * @retval  false  peer_id is free, or the module is not initialized.
 */
bool peer_id_is_allocated(pm_peer_id_t peer_id);


/**@brief Function for getting the next peer ID in the sequence of all used peer IDs. Can be
 *        used to loop through all used peer IDs.
 *
 * @note @ref PM_PEER_ID_INVALID is considered to be before the first and after the last ordinary
 *       peer ID.
 *
 * @param[in]  prev_peer_id  The previous peer ID.
 *
 * @return  The next peer ID.
 * @return  The first used peer ID  if prev_peer_id was @ref PM_PEER_ID_INVALID.
 * @retval  PM_PEER_ID_INVALID      if prev_peer_id was the last ordinary peer ID or the module is
 *                                  not initialized.
 */
pm_peer_id_t peer_id_get_next_used(pm_peer_id_t prev_peer_id);


/**@brief Function for getting the next peer ID in the sequence of all peer IDs marked for deletion.
 *        Can be used to loop through all peer IDs marked for deletion.
 *
 * @note @ref PM_PEER_ID_INVALID is considered to be before the first and after the last ordinary
 *       peer ID.
 *
 * @param[in]  prev_peer_id  The previous peer ID.
 *
 * @return  The next peer ID.
 * @return  The first used peer ID  if prev_peer_id was @ref PM_PEER_ID_INVALID.
 * @retval  PM_PEER_ID_INVALID      if prev_peer_id was the last ordinary peer ID or the module is
 *                                  not initialized.
 */
pm_peer_id_t peer_id_get_next_deleted(pm_peer_id_t prev_peer_id);


/**@brief Function for querying the number of valid peer IDs available. I.E the number of peers
 *        in persistent storage.
 *
 * @return  The number of valid peer IDs, or 0 if module is not initialized.
 */
uint32_t peer_id_n_ids(void);

/** @}
 * @endcond
 */


#ifdef __cplusplus
}
#endif

#endif /* PEER_ID_H__ */
