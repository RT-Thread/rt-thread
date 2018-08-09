/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
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
#include "ser_phy.h"
#include "app_error.h"


__weak uint32_t ser_phy_open(ser_phy_events_handler_t events_handler)
{
    /* A function stub. Function should be implemented according to ser_phy.h API. */
    APP_ERROR_CHECK_BOOL(false);

    return NRF_SUCCESS;
}

__weak uint32_t ser_phy_tx_pkt_send(const uint8_t * p_buffer, uint16_t num_of_bytes)
{
    /* A function stub. Function should be implemented according to ser_phy.h API. */
    APP_ERROR_CHECK_BOOL(false);

    return NRF_SUCCESS;
}

__weak uint32_t ser_phy_rx_buf_set(uint8_t * p_buffer)
{
    /* A function stub. Function should be implemented according to ser_phy.h API. */
    APP_ERROR_CHECK_BOOL(false);

    return NRF_SUCCESS;
}

__weak void ser_phy_close(void)
{
    /* A function stub. Function should be implemented according to ser_phy.h API. */
    APP_ERROR_CHECK_BOOL(false);
}


__weak void ser_phy_interrupts_enable(void)
{
    /* A function stub. Function should be implemented according to ser_phy.h API. */
    APP_ERROR_CHECK_BOOL(false);
}


__weak void ser_phy_interrupts_disable(void)
{
    /* A function stub. Function should be implemented according to ser_phy.h API. */
    APP_ERROR_CHECK_BOOL(false);
}


