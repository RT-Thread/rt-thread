/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#include "bsp_cli.h"

static bsp_event_callback_t   m_bsp_cli_callback         = NULL;

static void cmd_btn(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    uint32_t id;
    ASSERT(m_bsp_cli_callback != NULL);

    sscanf(argv[1], "%"SCNu32, &id);
    bsp_event_t ev = (bsp_event_t)(BSP_EVENT_KEY_0 + id);
    m_bsp_cli_callback(ev);
}

static void cmd_evt(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    uint32_t id;
    ASSERT(m_bsp_cli_callback != NULL);

    sscanf(argv[1], "%"SCNu32, &id);
    bsp_event_t ev = (bsp_event_t)id;
    m_bsp_cli_callback(ev);
}

ret_code_t bsp_cli_init(bsp_event_callback_t callback)
{
    m_bsp_cli_callback = callback;

    return NRF_SUCCESS;
}

NRF_CLI_CREATE_STATIC_SUBCMD_SET(m_sub_bsp)
{
    NRF_CLI_CMD(btn, NULL, "BSP button event key", cmd_btn),
    NRF_CLI_CMD(evt, NULL, "BSP event id", cmd_evt),
    NRF_CLI_SUBCMD_SET_END
};
NRF_CLI_CMD_REGISTER(bsp, &m_sub_bsp, "bsp", NULL);
