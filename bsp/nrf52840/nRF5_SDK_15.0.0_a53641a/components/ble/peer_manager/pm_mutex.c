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
#include "pm_mutex.h"

#include <stdbool.h>
#include <string.h>
#include "nrf_error.h"
#include "app_util_platform.h"



/**@brief Locks the mutex defined by the mask.
 *
 * @param p_mutex pointer to the mutex storage.
 * @param mutex_mask the mask identifying the mutex position.
 *
 * @retval true if the mutex could be locked.
 * @retval false if the mutex was already locked.
 */
static bool lock_by_mask(uint8_t * p_mutex, uint8_t mutex_mask)
{
    bool success = false;

    if ( (*p_mutex & mutex_mask) == 0 )
    {
        CRITICAL_REGION_ENTER();
        if ( (*p_mutex & mutex_mask) == 0 )
        {
            *p_mutex |= mutex_mask;

            success = true;
        }
        CRITICAL_REGION_EXIT();
    }

    return ( success );
}


void pm_mutex_init(uint8_t * p_mutex, uint16_t mutex_size)
{
    if (p_mutex != NULL)
    {
        memset(&p_mutex[0], 0, MUTEX_STORAGE_SIZE(mutex_size));
    }
}


bool pm_mutex_lock(uint8_t * p_mutex, uint16_t mutex_id)
{
    if (p_mutex != NULL)
    {
        return ( lock_by_mask(&(p_mutex[mutex_id >> 3]), (1 << (mutex_id & 0x07))) );
    }
    else
    {
        return false;
    }
}


void pm_mutex_unlock(uint8_t * p_mutex, uint16_t mutex_id)
{
    uint8_t mutex_base = mutex_id >> 3;
    uint8_t mutex_mask = (1 << (mutex_id & 0x07));

    if   ((p_mutex != NULL)
       && (p_mutex[mutex_base] & mutex_mask))
    {
        CRITICAL_REGION_ENTER();
        p_mutex[mutex_base] &= ~mutex_mask;
        CRITICAL_REGION_EXIT();
    }
}


uint16_t pm_mutex_lock_first_available(uint8_t * p_mutex, uint16_t mutex_size)
{
    if (p_mutex != NULL)
    {
        for ( uint16_t i = 0; i < mutex_size; i++ )
        {
            if ( lock_by_mask(&(p_mutex[i >> 3]), 1 << (i & 0x07)) )
            {
                return ( i );
            }
        }
    }

    return ( mutex_size );
}


bool pm_mutex_lock_status_get(uint8_t * p_mutex, uint16_t mutex_id)
{
    if (p_mutex != NULL)
    {
        return ( (p_mutex[mutex_id >> 3] & (1 << (mutex_id & 0x07))) );
    }
    else
    {
        return true;
    }
}
#endif // NRF_MODULE_ENABLED(PEER_MANAGER)
