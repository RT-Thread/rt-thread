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
#include "portdb.h"
#include <string.h>
#include "iot_common.h"
#include "iot_errors.h"
#include "mem_manager.h"
#include "nrf_error.h"

#define IANA_EPHEMRAL_BEGIN 49152u                                                                  /**< Minimum port number of the ephemeral port range. */
#define IANA_EPHEMRAL_END   65535u                                                                  /**< Maximum port number of the ephemeral port range. */

static uint16_t * m_portdb;                                                                         /**< A pointer to the port database. */
static uint32_t   m_portdb_len;                                                                     /**< Length of the port database. */



static __INLINE uint32_t db_size_get(void)
{
    return m_portdb_len * sizeof(uint16_t);
}


static __INLINE void db_reset(void)
{
    memset(&m_portdb[0], 0, db_size_get());
}


uint32_t portdb_init(uint32_t max_ports)
{
    uint32_t err_code = NRF_SUCCESS;
    m_portdb_len = max_ports;
    m_portdb = nrf_malloc(db_size_get());
    if (m_portdb == NULL)
    {
        err_code = NRF_ERROR_NO_MEM;
    }
    else
    {
        db_reset();
    }
    return err_code;
}


void portdb_deinit(void)
{
    nrf_free(m_portdb);
    m_portdb = NULL;
    m_portdb_len = 0;
}


void portdb_reset(void)
{
    db_reset();
}


static inline uint32_t check_port_in_use(uint16_t port)
{
    uint32_t err_code = NRF_SUCCESS;

    for (uint32_t i = 0; i < m_portdb_len; i++)
    {
        if (m_portdb[i] == port)
        {
            err_code = SOCKET_PORT_IN_USE;
            break;
        }
    }
    return err_code;
}

static inline uint32_t find_free_index(uint32_t * p_idx)
{
    uint32_t err_code = SOCKET_NO_AVAILABLE_PORTS;

    for (uint32_t i = 0; i < m_portdb_len; i++)
    {
        if (m_portdb[i] == 0)
        {
            *p_idx = i;
            err_code = NRF_SUCCESS;
            break;
        }
    }
    return err_code;
}

static uint32_t portdb_find_available_index(uint32_t * p_idx, uint16_t port)
{
    uint32_t err_code = SOCKET_NO_AVAILABLE_PORTS;

    err_code = check_port_in_use(port);

    if (err_code == NRF_SUCCESS)
    {
        err_code = find_free_index(p_idx);
    }
    return err_code;
}

uint32_t portdb_register(uint16_t port)
{
    uint32_t idx = 0;
    uint32_t err_code = portdb_find_available_index(&idx, port);

    if (err_code == NRF_SUCCESS)
    {
        m_portdb[idx] = port;
    }
    return err_code;
}

uint32_t portdb_alloc(uint16_t * p_port)
{
    uint32_t err_code = SOCKET_NO_AVAILABLE_PORTS;
    for (uint32_t i = IANA_EPHEMRAL_BEGIN; i <= IANA_EPHEMRAL_END; i++)
    {
		uint16_t port = (uint16_t)i;
        err_code = portdb_register(port);

        if (err_code == NRF_SUCCESS)
        {
            *p_port = port;
            break;
        }
        else if (err_code == SOCKET_NO_AVAILABLE_PORTS)
        {
            break;
        }
    }
    return err_code;
}

void portdb_free(uint16_t port)
{
    for (uint32_t i = 0; i < m_portdb_len; i++)
    {
        if (m_portdb[i] == port)
        {
            m_portdb[i] = 0;
            break;
        }
    }
}
