/**
 * Copyright (c) 2013 - 2019, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(HCI_MEM_POOL)
#include "hci_mem_pool.h"
#include <stdbool.h>
#include <stdio.h>

/**@brief RX buffer element instance structure.
 */
typedef struct
{
    uint8_t  rx_buffer[HCI_RX_BUF_SIZE];                            /**< RX buffer memory array. */
    uint32_t length;                                                /**< Length of the RX buffer memory array. */
} rx_buffer_elem_t;

/**@brief RX buffer queue element instance structure.
 */
typedef struct
{
    rx_buffer_elem_t * p_buffer;                                    /**< Pointer to RX buffer element. */
    uint32_t           free_window_count;                           /**< Free space element count. */
    uint32_t           free_available_count;                        /**< Free area element count. */
    uint32_t           read_available_count;                        /**< Read area element count. */
    uint32_t           write_index;                                 /**< Write position index. */
    uint32_t           read_index;                                  /**< Read position index. */
    uint32_t           free_index;                                  /**< Free position index. */
} rx_buffer_queue_t;

static bool              m_is_tx_allocated;                         /**< Boolean value to determine if the TX buffer is allocated. */
static rx_buffer_elem_t  m_rx_buffer_elem_queue[HCI_RX_BUF_QUEUE_SIZE]; /**< RX buffer element instances. */
static rx_buffer_queue_t m_rx_buffer_queue;                         /**< RX buffer queue element instance. */


uint32_t hci_mem_pool_open(void)
{
    m_is_tx_allocated                      = false;
    m_rx_buffer_queue.p_buffer             = m_rx_buffer_elem_queue;
    m_rx_buffer_queue.free_window_count    = HCI_RX_BUF_QUEUE_SIZE;
    m_rx_buffer_queue.free_available_count = 0;
    m_rx_buffer_queue.read_available_count = 0;
    m_rx_buffer_queue.write_index          = 0;
    m_rx_buffer_queue.read_index           = 0;
    m_rx_buffer_queue.free_index           = 0;

    return NRF_SUCCESS;
}


uint32_t hci_mem_pool_close(void)
{
    return NRF_SUCCESS;
}


uint32_t hci_mem_pool_tx_alloc(void ** pp_buffer)
{
    static uint8_t tx_buffer[HCI_TX_BUF_SIZE];

    uint32_t err_code;

    if (pp_buffer == NULL)
    {
        return NRF_ERROR_NULL;
    }

    if (!m_is_tx_allocated)
    {
            m_is_tx_allocated = true;
            *pp_buffer        = tx_buffer;
            err_code          = NRF_SUCCESS;
    }
    else
    {
        err_code              = NRF_ERROR_NO_MEM;
    }

    return err_code;
}


uint32_t hci_mem_pool_tx_free(void)
{
    m_is_tx_allocated = false;

    return NRF_SUCCESS;
}


uint32_t hci_mem_pool_rx_produce(uint32_t length, void ** pp_buffer)
{
    uint32_t err_code;

    if (pp_buffer == NULL)
    {
        return NRF_ERROR_NULL;
    }
    *pp_buffer = NULL;

    if (m_rx_buffer_queue.free_window_count != 0)
    {
        if (length <= HCI_RX_BUF_SIZE)
        {
            --(m_rx_buffer_queue.free_window_count);
            ++(m_rx_buffer_queue.read_available_count);

            *pp_buffer                    =
                    m_rx_buffer_queue.p_buffer[m_rx_buffer_queue.write_index].rx_buffer;

            m_rx_buffer_queue.free_index |= (1u << m_rx_buffer_queue.write_index);

            // @note: Adjust the write_index making use of the fact that the buffer size is of
            // power of two and two's complement arithmetic. For details refer example to book
            // "Making embedded systems: Elicia White".
            m_rx_buffer_queue.write_index =
                    (m_rx_buffer_queue.write_index + 1u) & (HCI_RX_BUF_QUEUE_SIZE - 1u);

            err_code                      = NRF_SUCCESS;
        }
        else
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    }
    else
    {
        err_code = NRF_ERROR_NO_MEM;
    }

    return err_code;
}


uint32_t hci_mem_pool_rx_consume(uint8_t * p_buffer)
{
    uint32_t err_code;
    uint32_t consume_index;
    uint32_t start_index;

    if (m_rx_buffer_queue.free_available_count != 0)
    {
        // Find the buffer that has been freed -
        // Start at read_index minus free_available_count and then increment until read index.
        err_code      = NRF_ERROR_INVALID_ADDR;
        consume_index = (m_rx_buffer_queue.read_index - m_rx_buffer_queue.free_available_count) &
                        (HCI_RX_BUF_QUEUE_SIZE - 1u);
        start_index   = consume_index;

        do
        {
            if (m_rx_buffer_queue.p_buffer[consume_index].rx_buffer == p_buffer)
            {
                m_rx_buffer_queue.free_index ^= (1u << consume_index);
                err_code = NRF_SUCCESS;
                break;
            }
            else
            {
                consume_index = (consume_index + 1u) & (HCI_RX_BUF_QUEUE_SIZE - 1u);
            }
        }
        while (consume_index != m_rx_buffer_queue.read_index);

        while (!(m_rx_buffer_queue.free_index & (1 << start_index)) &&
                (m_rx_buffer_queue.free_available_count != 0))
        {
            --(m_rx_buffer_queue.free_available_count);
            ++(m_rx_buffer_queue.free_window_count);
            start_index = (consume_index + 1u) & (HCI_RX_BUF_QUEUE_SIZE - 1u);
        }
    }
    else
    {
        err_code = NRF_ERROR_NO_MEM;
    }

    return err_code;
}


uint32_t hci_mem_pool_rx_data_size_set(uint32_t length)
{
    // @note: Adjust the write_index making use of the fact that the buffer size is of power
    // of two and two's complement arithmetic. For details refer example to book
    // "Making embedded systems: Elicia White".
    const uint32_t index = (m_rx_buffer_queue.write_index - 1u) & (HCI_RX_BUF_QUEUE_SIZE - 1u);
    m_rx_buffer_queue.p_buffer[index].length = length;

    return NRF_SUCCESS;
}


uint32_t hci_mem_pool_rx_extract(uint8_t ** pp_buffer, uint32_t * p_length)
{
    uint32_t err_code;

    if ((pp_buffer == NULL) || (p_length == NULL))
    {
        return NRF_ERROR_NULL;
    }

    if (m_rx_buffer_queue.read_available_count != 0)
    {
        --(m_rx_buffer_queue.read_available_count);
        ++(m_rx_buffer_queue.free_available_count);

        *pp_buffer                   =
            m_rx_buffer_queue.p_buffer[m_rx_buffer_queue.read_index].rx_buffer;
        *p_length                    =
            m_rx_buffer_queue.p_buffer[m_rx_buffer_queue.read_index].length;

        // @note: Adjust the write_index making use of the fact that the buffer size is of power
        // of two and two's complement arithmetic. For details refer example to book
        // "Making embedded systems: Elicia White".
        m_rx_buffer_queue.read_index =
            (m_rx_buffer_queue.read_index + 1u) & (HCI_RX_BUF_QUEUE_SIZE - 1u);

        err_code                     = NRF_SUCCESS;
    }
    else
    {
        err_code                     = NRF_ERROR_NO_MEM;
    }

    return err_code;
}
#endif //NRF_MODULE_ENABLED(HCI_MEM_POOL)
