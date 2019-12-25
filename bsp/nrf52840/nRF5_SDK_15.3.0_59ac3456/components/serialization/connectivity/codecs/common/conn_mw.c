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
#include <stddef.h>

#include "ble_serialization.h"
#include "nrf_soc.h"

/**@brief Connectivity middleware handler type. */
typedef uint32_t (*conn_mw_handler_t)(uint8_t const * const p_rx_buf,
                                      uint32_t              rx_buf_len,
                                      uint8_t * const       p_tx_buf,
                                      uint32_t * const      p_tx_buf_len);

/**@brief Connectivity middleware item. */
typedef struct
{
    uint8_t           opcode;     /**< Opcode by which specific codec is identified */
    conn_mw_handler_t fp_handler; /**< Function pointer to handler associated with given opcode */
} conn_mw_item_t;

/* Include handlers for given softdevice */
#include "conn_mw_items.c"

/**@brief Number of registered connectivity middleware handlers. */
static const uint32_t conn_mw_item_len = sizeof (conn_mw_item) / sizeof (conn_mw_item[0]);

/**@brief Local function for finding connectivity middleware handler in the table.. */
static conn_mw_handler_t conn_mw_handler_get(uint8_t opcode)
{
    conn_mw_handler_t fp_handler = NULL;
    uint32_t          i;

    for (i = 0; i < conn_mw_item_len; i++)
    {
        if (opcode == conn_mw_item[i].opcode)
        {
            fp_handler = conn_mw_item[i].fp_handler;
            break;
        }
    }

    return fp_handler;
}

uint32_t conn_mw_handler(uint8_t const * const p_rx_buf,
                         uint32_t              rx_buf_len,
                         uint8_t * const       p_tx_buf,
                         uint32_t * const      p_tx_buf_len)
{
    SER_ASSERT_NOT_NULL(p_rx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf);
    SER_ASSERT_NOT_NULL(p_tx_buf_len);

    conn_mw_handler_t fp_handler;
    uint32_t          err_code = NRF_SUCCESS;
    uint8_t           opcode   = p_rx_buf[SER_CMD_OP_CODE_POS];

    fp_handler = conn_mw_handler_get(opcode);

    if (fp_handler)
    {
        err_code = fp_handler(p_rx_buf, rx_buf_len, p_tx_buf, p_tx_buf_len);
    }
    else
    {
        err_code = NRF_ERROR_NOT_SUPPORTED;
    }

    return err_code;
}
