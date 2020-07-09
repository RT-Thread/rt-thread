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
#ifndef MUTEX_H__
#define MUTEX_H__


#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @cond NO_DOXYGEN
 * @defgroup pm_mutex Mutex
 * @ingroup peer_manager
 * @{
 * @brief An internal module of @ref peer_manager. This module provides thread-safe mutexes.
 */


/**@brief Defines the storage size of a specified mutex group.
 *
 * @param number_of_mutexes the number of mutexes in the group.
 */
#define MUTEX_STORAGE_SIZE(number_of_mutexes) ((7 + (number_of_mutexes)) >> 3)


/**@brief Initializes a mutex group.
 *
 * @param[in] p_mutex     Pointer to the mutex group. See @ref MUTEX_STORAGE_SIZE().
 * @param[in] mutex_size  The size of the mutex group in number of mutexes.
 */
void pm_mutex_init(uint8_t * p_mutex, uint16_t mutex_size);


/**@brief Locks the mutex specified by the bit id.
 *
 * @param[inout] p_mutex       Pointer to the mutex group.
 * @param[in]    mutex_bit_id  The bit id of the mutex.
 *
 * @retval true   if it was possible to lock the mutex.
 * @retval false  otherwise.
 */
bool pm_mutex_lock(uint8_t * p_mutex, uint16_t mutex_bit_id);


/**@brief Locks the first unlocked mutex within the mutex group.
 *
 * @param[in, out] p_mutex     Pointer to the mutex group.
 * @param[in]      mutex_size  The size of the mutex group.
 *
 * @return The first unlocked mutex id in the group.
 * @retval group-size  if there was no unlocked mutex available.
 */
uint16_t pm_mutex_lock_first_available(uint8_t * p_mutex, uint16_t mutex_size);


/**@brief Unlocks the mutex specified by the bit id.
 *
 * @param[in, out] p_mutex       Pointer to the mutex group.
 * @param[in]      mutex_bit_id  The bit id of the mutex.
 */
void pm_mutex_unlock(uint8_t * p_mutex, uint16_t mutex_bit_id);


/**@brief Gets the locking status of the specified mutex.
 *
 * @param[in, out] p_mutex      Pointer to the mutex group.
 * @param[in]      mutex_bit_id The bit id of the mutex.
 *
 * @retval true   if the mutex was locked.
 * @retval false  otherwise.
 */
bool pm_mutex_lock_status_get(uint8_t * p_mutex, uint16_t mutex_bit_id);



#ifdef __cplusplus
}
#endif

#endif // MUTEX_H__

/** @}
 * @endcond
 */
