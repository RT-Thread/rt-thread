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
#include "peer_id.h"

#include <stdint.h>
#include <string.h>
#include "sdk_errors.h"
#include "peer_manager_types.h"
#include "pm_mutex.h"


typedef struct
{
    uint8_t used_peer_ids[MUTEX_STORAGE_SIZE(PM_PEER_ID_N_AVAILABLE_IDS)];  /**< Bitmap designating which peer IDs are in use. */
    uint8_t deleted_peer_ids[MUTEX_STORAGE_SIZE(PM_PEER_ID_N_AVAILABLE_IDS)]; /**< Bitmap designating which peer IDs are marked for deletion. */
} pi_t;


static pi_t m_pi = {{0}, {0}};


static void internal_state_reset(pi_t * p_pi)
{
    memset(p_pi, 0, sizeof(pi_t));
}


void peer_id_init(void)
{
    internal_state_reset(&m_pi);
    pm_mutex_init(m_pi.used_peer_ids, PM_PEER_ID_N_AVAILABLE_IDS);
    pm_mutex_init(m_pi.deleted_peer_ids, PM_PEER_ID_N_AVAILABLE_IDS);
}


static pm_peer_id_t claim(pm_peer_id_t peer_id, uint8_t * mutex_group)
{
    pm_peer_id_t allocated_peer_id = PM_PEER_ID_INVALID;
    if (peer_id == PM_PEER_ID_INVALID)
    {
        allocated_peer_id = pm_mutex_lock_first_available(mutex_group, PM_PEER_ID_N_AVAILABLE_IDS);
        if (allocated_peer_id == PM_PEER_ID_N_AVAILABLE_IDS)
        {
            allocated_peer_id = PM_PEER_ID_INVALID;
        }
    }
    else if (peer_id < PM_PEER_ID_N_AVAILABLE_IDS)
    {
        bool lock_success = pm_mutex_lock(mutex_group, peer_id);
        allocated_peer_id = lock_success ? peer_id : PM_PEER_ID_INVALID;
    }
    return allocated_peer_id;
}


static void release(pm_peer_id_t peer_id, uint8_t * mutex_group)
{
    if (peer_id < PM_PEER_ID_N_AVAILABLE_IDS)
    {
        pm_mutex_unlock(mutex_group, peer_id);
    }
}


pm_peer_id_t peer_id_allocate(pm_peer_id_t peer_id)
{
    return claim(peer_id, m_pi.used_peer_ids);
}


bool peer_id_delete(pm_peer_id_t peer_id)
{
    pm_peer_id_t deleted_peer_id;

    if (peer_id == PM_PEER_ID_INVALID)
    {
        return false;
    }

    deleted_peer_id = claim(peer_id, m_pi.deleted_peer_ids);

    return (deleted_peer_id == peer_id);
}


void peer_id_free(pm_peer_id_t peer_id)
{
    release(peer_id, m_pi.used_peer_ids);
    release(peer_id, m_pi.deleted_peer_ids);
}


bool peer_id_is_allocated(pm_peer_id_t peer_id)
{
    if (peer_id < PM_PEER_ID_N_AVAILABLE_IDS)
    {
        return pm_mutex_lock_status_get(m_pi.used_peer_ids, peer_id);
    }
    return false;
}


bool peer_id_is_deleted(pm_peer_id_t peer_id)
{
    if (peer_id < PM_PEER_ID_N_AVAILABLE_IDS)
    {
        return pm_mutex_lock_status_get(m_pi.deleted_peer_ids, peer_id);
    }
    return false;
}


pm_peer_id_t next_id_get(pm_peer_id_t prev_peer_id, uint8_t * mutex_group)
{
    pm_peer_id_t i = (prev_peer_id == PM_PEER_ID_INVALID) ? 0 : (prev_peer_id + 1);
    for (; i < PM_PEER_ID_N_AVAILABLE_IDS; i++)
    {
        if (pm_mutex_lock_status_get(mutex_group, i))
        {
            return i;
        }
    }

    return PM_PEER_ID_INVALID;
}


pm_peer_id_t peer_id_get_next_used(pm_peer_id_t peer_id)
{
    peer_id = next_id_get(peer_id, m_pi.used_peer_ids);

    while (peer_id != PM_PEER_ID_INVALID)
    {
        if (!peer_id_is_deleted(peer_id))
        {
            return peer_id;
        }

        peer_id = next_id_get(peer_id, m_pi.used_peer_ids);
    }

    return peer_id;
}


pm_peer_id_t peer_id_get_next_deleted(pm_peer_id_t prev_peer_id)
{
    return next_id_get(prev_peer_id, m_pi.deleted_peer_ids);
}


uint32_t peer_id_n_ids(void)
{
    uint32_t n_ids = 0;

    for (pm_peer_id_t i = 0; i < PM_PEER_ID_N_AVAILABLE_IDS; i++)
    {
        n_ids += pm_mutex_lock_status_get(m_pi.used_peer_ids, i);
    }

    return n_ids;
}
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
