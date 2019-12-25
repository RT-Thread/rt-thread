/**
 * Copyright (c) 2016 - 2019 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
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
#ifndef SYS_SLAB_ALLOCATOR_H_INCLUDED
#define SYS_SLAB_ALLOCATOR_H_INCLUDED

#include "phy_pd_data.h"

#ifndef CONFIG_SLAB_FRAME_POOL_SIZE
#define CONFIG_SLAB_FRAME_POOL_SIZE 4
#warning "CONFIG_SLAB_FRAME_POOL_SIZE not set in .config, using default"
#endif

/** @file
 * This file contains declarations of the SLAB allocator API.
 *
 * @defgroup sys_slab_allocator SLAB Allocator API
 * @ingroup sys_15_4
 * @{
 * @brief Module for declaring the SLAB Allocator API
 */

/**@brief  The SLAB allocator buffer type (free or busy buffer).
 */
typedef enum
{
    SYS_SLAB_FREE_BUFFER,      /**< The buffer is free */
    SYS_SLAB_BUSY_BUFFER,      /**< The buffer is busy */
} sys_slab_buffer_type_t;

/**@brief Initializes the SLAB allocator.
 *
 * @details Preallocates the frame pool
 */
void sys_sa_init(void);

/**@brief Resets the SLAB allocator.
 *
 * @details Clear allocated the frame pools
 */
void sys_sa_reset(void);

/**@brief   Inserts item into one of the queues of the SLAB allocator.
 *
 * @details This function is used to put the item into the SLAB allocator
 *          queue. Type of buffer shall be chosen.
 *
 * @param[in]   type    Type of an inserted buffer (free or busy).
 * @param[in]   p_item  Pointer to an inserted buffer.
 */
void sys_sa_buffer_put(sys_slab_buffer_type_t type, pd_data_ind_t * p_item);

/**@brief   Gets item from one of the queues of the SLAB allocator.
 *
 * @details This function is used to get the item from the SLAB allocator
 *          queues. Type of buffer shall be chosen. The buffer is deleted
 *          from the SLAB allocator
 *
 * @param[in]   type    Type of a gotten buffer (free or busy).
 *
 * @retval  Pointer to a gotten buffer in case of success. NULL otherwise.
 */
pd_data_ind_t * sys_sa_buffer_get(sys_slab_buffer_type_t type);

/**@brief   Deletes an allocated item from the heap.
 *
 * @details This function is used to delete allocated by SLAB allocator buffer
 *          from the heap. Pointer to a frame memory of an allocated item shall be used.
 *
 * @param[in] p_frame   Pointer to a frame memory of an allocated item.
 */
void sys_sa_buffer_free(uint8_t * p_frame);

/**@brief  Returns buffer back to queue of free buffers.
 *
 * @details This function is used to return allocated buffer back to the queue
 *          without allocation and deallocation.
 *
 * @param[in] p_item   Pointer to an allocated item.
 */
void sys_sa_buffer_release(pd_data_ind_t * p_item);

/**@brief  Allocates memory for the queue of free buffers.
 *
 * @details This function is used to allocate buffer from heap
 *          and put them into the queue
 *
 * @retval  True in case of success. False otherwise.
 */
bool sys_sa_memory_allocate(void);

/**@brief  Checks if there are any buffers in the SLAB allocator queue or not.
 *
 * @details Type of checked buffers shall be passed.
 *
 * @param[in] type   Type of an checked buffers (free or busy).
 *
 * @retval  True in case of absence of buffers. False otherwise.
 */
bool sys_sa_is_empty(sys_slab_buffer_type_t type);

/** @} */

#endif /* SYS_SLAB_ALLOCATOR_H_INCLUDED */
