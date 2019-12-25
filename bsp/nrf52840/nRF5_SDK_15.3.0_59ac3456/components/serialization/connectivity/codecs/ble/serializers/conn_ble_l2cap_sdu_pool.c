/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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

#include "conn_ble_l2cap_sdu_pool.h"
#include "app_util.h"
#include "nrf_balloc.h"


#define MAX_NUM_OF_BUFFERS 8

#define ID_SIZE 4

#define TOTAL_BUF_SIZE (CONN_BLE_L2CAP_SDU_MAX_BUFFER_SIZE+ID_SIZE)

NRF_BALLOC_DEF(m_pool, TOTAL_BUF_SIZE, MAX_NUM_OF_BUFFERS);

void conn_ble_l2cap_sdu_pool_init(void)
{
    (void)nrf_balloc_init(&m_pool);
}

uint8_t * conn_ble_l2cap_sdu_pool_alloc(uint16_t length, uint32_t id)
{
    if (length > CONN_BLE_L2CAP_SDU_MAX_BUFFER_SIZE)
    {
        return NULL;
    }

    uint32_t * p_buf = nrf_balloc_alloc(&m_pool);
    *p_buf = id;
    p_buf++;
    return (uint8_t *)p_buf;
}

uint32_t  conn_ble_l2cap_sdu_pool_id_get(void * p_data)
{
    uint32_t * p_buf = (uint32_t *)p_data;
    p_buf--;
    return *p_buf;
}

void  conn_ble_l2cap_sdu_pool_free(void * p_data)
{
    uint32_t * p_buf = (uint32_t *)p_data;
    p_buf--;
    nrf_balloc_free(&m_pool, p_buf);
}
