/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
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
/* This module declares the Memory Management functionality.
 * Please use sys_mm_init before calling to any module routines.
 * Call sys_mm_alloc to allocate memory.
 * Use sys_mm_free to free the allocated memory
 */

#ifndef SYS_MEMORY_MANAGER_H_INCLUDED
#define SYS_MEMORY_MANAGER_H_INCLUDED

#include <stddef.h>
#include <stdint.h>

/** @file
 * This file contains declarations of the Memory manager API.
 *
 * @defgroup sys_memory_manager Memory Manager API
 * @ingroup sys_15_4
 * @{
 * @brief Module to declare Memory Manager API.
 * @details The Memory Manager module implements the standard API for allocating/freeing memory chunks. The module must
 * be initialized by sys_mm_init() before a call to any alloc/free routines. The memory can be allocated by a
 * call to sys_mm_alloc() and freed by a call to sys_mm_free(). Minimal chunk of memory to allocate is one byte,
 * however the sys_mm_alloc() routine will allocate the number of bytes aligned to the length of the
 * machine word (e.g. 4 bytes for 32-bit architectures). The module is implemented using the doubly linked
 * lists API.
 */

/**@brief Function for initializing the memory manager.
 * @details Initialize the memory manager pool of the 'size' bytes length at 'p_start' address.
 * 
 * @param p_start Pool start address.
 * @param size    Size of the pool in bytes.
 */
void sys_mm_init(void * p_start, size_t size);


/**@brief Function for allocating memory in the pool.
 * @details Search and allocate free memory resources.
 *
 * @param[in] size Size of the requested memory.
 *
 * @retval    Pointer to allocated memory,
 *            NULL in case of error.
 */
void * sys_mm_alloc(size_t size);


/**@brief Function for freeing the allocated memory.
 *
 * @param[in] p_addr Pointer to the memory to free.
 *
 */
void sys_mm_free(void * p_addr);

/** @} */

#endif // SYS_MEMORY_MANAGER_H_INCLUDED
