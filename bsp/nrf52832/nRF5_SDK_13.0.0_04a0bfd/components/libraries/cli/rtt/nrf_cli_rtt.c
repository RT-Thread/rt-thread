/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(NRF_CLI_RTT)
#include <SEGGER_RTT_Conf.h>
#include <SEGGER_RTT.h>
#include "nrf_cli_rtt.h"



static ret_code_t cli_rtt_init(void)
{
    SEGGER_RTT_Init();
    return NRF_SUCCESS;
}

static ret_code_t cli_rtt_uninit(void)
{
    return NRF_SUCCESS;
}

static ret_code_t cli_rtt_read(void * p_data,
                               size_t length,
                               size_t * p_cnt)
{
    size_t rcnt = SEGGER_RTT_Read(NRF_CLI_RTT_TERMINAL_ID, p_data, length);
    if (p_cnt)
    {
        *p_cnt = rcnt;
    }

    return NRF_SUCCESS;
}

static ret_code_t cli_rtt_write(const void * p_data,
                                size_t length,
                                size_t * p_cnt)
{
    size_t wcnt;
    size_t acc = 0;
    do {
        wcnt = SEGGER_RTT_Write(NRF_CLI_RTT_TERMINAL_ID, p_data, length);

        acc += wcnt;
        length -= wcnt;
    } while (length);

    if (p_cnt)
    {
        *p_cnt = acc;
    }

    return NRF_SUCCESS;
}

const nrf_cli_transport_t nrf_cli_rtt_transport = {
        .init = cli_rtt_init,
        .uninit = cli_rtt_uninit,
        .read = cli_rtt_read,
        .write = cli_rtt_write,
};

#endif
