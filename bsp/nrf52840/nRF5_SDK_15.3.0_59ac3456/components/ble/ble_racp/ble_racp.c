/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(BLE_RACP)
#include "ble_racp.h"
#include <stdlib.h>


void ble_racp_decode(uint8_t data_len, uint8_t const * p_data, ble_racp_value_t * p_racp_val)
{
    p_racp_val->opcode      = 0xFF;
    p_racp_val->operator    = 0xFF;
    p_racp_val->operand_len = 0;
    p_racp_val->p_operand   = NULL;

    if (data_len > 0)
    {
        p_racp_val->opcode = p_data[0];
    }
    if (data_len > 1)
    {
        p_racp_val->operator = p_data[1];      //lint !e415
    }
    if (data_len > 2)
    {
        p_racp_val->operand_len = data_len - 2;
        p_racp_val->p_operand   = (uint8_t*)&p_data[2];  //lint !e416
    }
}


uint8_t ble_racp_encode(const ble_racp_value_t * p_racp_val, uint8_t * p_data)
{
    uint8_t len = 0;
    int     i;

    if (p_data != NULL)
    {
        p_data[len++] = p_racp_val->opcode;
        p_data[len++] = p_racp_val->operator;

        for (i = 0; i < p_racp_val->operand_len; i++)
        {
            p_data[len++] = p_racp_val->p_operand[i];
        }
    }

    return len;
}
#endif // NRF_MODULE_ENABLED(BLE_RACP)
