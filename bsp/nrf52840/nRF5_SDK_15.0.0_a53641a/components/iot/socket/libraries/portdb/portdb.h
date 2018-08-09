/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
#ifndef PORTDB_H__
#define PORTDB_H__

/**
 * @file portdb.h
 *
 * @defgroup iot_socket_portdb Port Database
 * @ingroup iot_sdk_socket
 * @{
 * @brief Port database for sockets.
 *
 * The port database provides a functionality for registering, allocating, and freeing ports.
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Function for initializing the port database.
 *
 * This must be called before allocating and freeing ports.
 *
 * @param max_len The max length of the portdb.
 *
 * @retval NRF_SUCCESS If successfully initialized.
 */
uint32_t portdb_init(uint32_t max_len);

/**
 * @brief Function for deinitializing the portdb.
 *
 * This will free all memory allocated by this portdb.
 */
void portdb_deinit(void);

/**
 * @brief Function to reset all ports without freeing any memories.
 */
void portdb_reset(void);

/**
 * @brief Function for allocating a port.
 *
 * Looks for an available port in the database and allocates it to the caller.
 *
 * @param[out] p_port Pointer to a variable where the allocated port number should be stored.
 *
 * @retval NRF_SUCCESS               If a free port was located and successfully allocated.
 * @retval SOCKET_NO_AVAILABLE_PORTS If no available ports were found.
 */
uint32_t portdb_alloc(uint16_t * p_port);

/**
 * @brief Function for registering a port.
 *
 * Marks a given port in the database as being in use.
 *
 * @param[in] port The port to mark as in use.
 *
 * @retval NRF_SUCCESS               If port was successfully marked as in use.
 * @retval SOCKET_NO_AVAILABLE_PORTS If there was no slot in which to register the port.
 * @retval SOCKET_PORT_IN_USE        If the port has already been registered or allocated.
 */
uint32_t portdb_register(uint16_t port);

/**
 * @brief Function for freeing a port.
 *
 * Mark a given port as free and make it available for others to register or allocate.
 *
 * @param[in] port The port to mark as free.
 */
void portdb_free(uint16_t port);

#ifdef __cplusplus
}
#endif

/**@} */

#endif // PORTDB_H__
