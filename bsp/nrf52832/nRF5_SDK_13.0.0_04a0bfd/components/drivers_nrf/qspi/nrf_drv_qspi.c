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
#include "sdk_config.h"

#if QSPI_ENABLED

#include "nrf_drv_qspi.h"
#include "nrf_drv_common.h"
#include "nrf_gpio.h"
#include "nrf_assert.h"

/**
 * @brief Command byte used to read status register.
 *
 */
#define QSPI_STD_CMD_RDSR 0x05

/**
 * @brief Byte used to mask status register and retrieve the write-in-progess bit.
 *
 */
#define QSPI_MEM_STATUSREG_WIP_Pos 0x01

#define QSPI_WAIT_READY() do {                                         \
        while (!nrf_qspi_event_check(NRF_QSPI, NRF_QSPI_EVENT_READY)); \
    } while(0)

/**
  * @brief Control block - driver instance local data.
  *
  */
typedef struct
{
    nrf_drv_qspi_handler_t handler;          /**< Handler. */
    nrf_drv_state_t        state;            /**< Driver state. */
    volatile bool          interrupt_driven; /**< Information if the current operation is performed and is interrupt-driven. */
    void *                 p_context;        /**< Driver context used in interrupt. */
} qspi_control_block_t;

static qspi_control_block_t m_cb;

static ret_code_t qspi_task_perform(nrf_qspi_task_t task)
{
    // Wait for peripheral
    if (m_cb.interrupt_driven)
    {
        return NRF_ERROR_BUSY;
    }

    nrf_qspi_event_clear(NRF_QSPI, NRF_QSPI_EVENT_READY);

    if (m_cb.handler)
    {
        m_cb.interrupt_driven = true;
        nrf_qspi_int_enable(NRF_QSPI, NRF_QSPI_INT_READY_MASK);
    }

    nrf_qspi_task_trigger(NRF_QSPI, task);

    if (m_cb.handler == NULL)
    {
        QSPI_WAIT_READY();
    }
    return NRF_SUCCESS;
}

static bool qspi_pins_configure(nrf_qspi_pins_t const * p_config)
{
    // Check if the user set meaningful values to struct fields. If not, return false.
    if ((p_config->sck_pin == NRF_QSPI_PIN_NOT_CONNECTED) ||
        (p_config->csn_pin == NRF_QSPI_PIN_NOT_CONNECTED) ||
        (p_config->io0_pin == NRF_QSPI_PIN_NOT_CONNECTED) ||
        (p_config->io1_pin == NRF_QSPI_PIN_NOT_CONNECTED))
    {
        return false;
    }

    nrf_qspi_pins_set(NRF_QSPI, p_config);

    return true;
}

ret_code_t nrf_drv_qspi_init(nrf_drv_qspi_config_t const * p_config,
                             nrf_drv_qspi_handler_t        handler,
                             void *                        p_context)
{
    if (m_cb.state != NRF_DRV_STATE_UNINITIALIZED)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    if (!qspi_pins_configure(&p_config->pins))
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    nrf_qspi_ifconfig0_set(NRF_QSPI, &p_config->prot_if);
    nrf_qspi_ifconfig1_set(NRF_QSPI, &p_config->phy_if);

    m_cb.interrupt_driven = false;
    m_cb.handler = handler;
    m_cb.p_context = p_context;

    /* QSPI interrupt is disabled because the device should be enabled in polling mode (wait for activate
       task event ready)*/
    nrf_qspi_int_disable(NRF_QSPI, NRF_QSPI_INT_READY_MASK);

    if (handler)
    {
        nrf_drv_common_irq_enable(QSPI_IRQn, p_config->irq_priority);
    }

    m_cb.state = NRF_DRV_STATE_INITIALIZED;

    nrf_qspi_enable(NRF_QSPI);

    nrf_qspi_event_clear(NRF_QSPI, NRF_QSPI_EVENT_READY);
    nrf_qspi_task_trigger(NRF_QSPI, NRF_QSPI_TASK_ACTIVATE);

    // Waiting for the peripheral to activate
    QSPI_WAIT_READY();

    return NRF_SUCCESS;
}

ret_code_t nrf_drv_qspi_cinstr_xfer(nrf_qspi_cinstr_conf_t const * p_config,
                                    void const *                   p_tx_buffer,
                                    void *                         p_rx_buffer)
{
    ASSERT(m_cb.state != NRF_DRV_STATE_UNINITIALIZED);

    if (m_cb.interrupt_driven)
    {
        return NRF_ERROR_BUSY;
    }

    nrf_qspi_event_clear(NRF_QSPI, NRF_QSPI_EVENT_READY);
    /* In some cases, only opcode should be sent. To prevent execution, set function code is
     * surrounded by an if.
     */
    if (p_tx_buffer)
    {
        nrf_qspi_cinstrdata_set(NRF_QSPI, p_config->length, p_tx_buffer);
    }
    nrf_qspi_int_disable(NRF_QSPI, NRF_QSPI_INT_READY_MASK);

    nrf_qspi_cinstr_transfer_start(NRF_QSPI, p_config);

    QSPI_WAIT_READY();
    nrf_qspi_int_enable(NRF_QSPI, NRF_QSPI_INT_READY_MASK);

    if (p_rx_buffer)
    {
        nrf_qspi_cinstrdata_get(NRF_QSPI, p_config->length, p_rx_buffer);
    }

    return NRF_SUCCESS;
}

ret_code_t nrf_drv_qspi_cinstr_quick_send(uint8_t               opcode,
                                          nrf_qspi_cinstr_len_t length,
                                          void const *          p_tx_buffer)
{
    nrf_qspi_cinstr_conf_t config = NRF_DRV_QSPI_DEFAULT_CINSTR(opcode, length);
    return nrf_drv_qspi_cinstr_xfer(&config, p_tx_buffer, NULL);
}

ret_code_t nrf_drv_qspi_mem_busy_check(void)
{
    ret_code_t ret_code;
    uint8_t status_value = 0;

    nrf_qspi_cinstr_conf_t config = NRF_DRV_QSPI_DEFAULT_CINSTR(QSPI_STD_CMD_RDSR,
                                                                NRF_QSPI_CINSTR_LEN_2B);

    ret_code = nrf_drv_qspi_cinstr_xfer(&config, &status_value, &status_value);

    if (ret_code != NRF_SUCCESS)
    {
        return ret_code;
    }

    if ((status_value & QSPI_MEM_STATUSREG_WIP_Pos) != 0x00)
    {
        return NRF_ERROR_BUSY;
    }

    return NRF_SUCCESS;
}

void nrf_drv_qspi_uninit(void)
{
    ASSERT(m_cb.state != NRF_DRV_STATE_UNINITIALIZED);

    nrf_qspi_int_disable(NRF_QSPI, NRF_QSPI_INT_READY_MASK);

    nrf_qspi_disable(NRF_QSPI);

    nrf_drv_common_irq_disable(QSPI_IRQn);

    nrf_qspi_event_clear(NRF_QSPI, NRF_QSPI_EVENT_READY);

    m_cb.state = NRF_DRV_STATE_UNINITIALIZED;
}

ret_code_t nrf_drv_qspi_write(void const * p_tx_buffer,
                              size_t       tx_buffer_length,
                              uint32_t     dst_address)
{
    ASSERT(m_cb.state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(p_tx_buffer != NULL);

    if (!nrf_drv_is_in_RAM(p_tx_buffer))
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    nrf_qspi_write_buffer_set(NRF_QSPI, p_tx_buffer, tx_buffer_length, dst_address);
    return qspi_task_perform(NRF_QSPI_TASK_WRITESTART);

}

ret_code_t nrf_drv_qspi_read(void *   p_rx_buffer,
                             size_t   rx_buffer_length,
                             uint32_t src_address)
{
    ASSERT(m_cb.state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(p_rx_buffer != NULL);

    if (!nrf_drv_is_in_RAM(p_rx_buffer))
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    nrf_qspi_read_buffer_set(NRF_QSPI, p_rx_buffer, rx_buffer_length, src_address);
    return qspi_task_perform(NRF_QSPI_TASK_READSTART);
}

ret_code_t nrf_drv_qspi_erase(nrf_qspi_erase_len_t length,
                              uint32_t             start_address)
{
    ASSERT(m_cb.state != NRF_DRV_STATE_UNINITIALIZED);
    nrf_qspi_erase_ptr_set(NRF_QSPI, start_address, length);
    return qspi_task_perform(NRF_QSPI_TASK_ERASESTART);
}

ret_code_t nrf_drv_qspi_chip_erase(void)
{
    return nrf_drv_qspi_erase(NRF_QSPI_ERASE_LEN_ALL, 0);
}

void QSPI_IRQHandler(void)
{
    // Catch Event ready interrupts
    if (nrf_qspi_event_check(NRF_QSPI, NRF_QSPI_EVENT_READY))
    {
        m_cb.interrupt_driven = false;
        nrf_qspi_event_clear(NRF_QSPI, NRF_QSPI_EVENT_READY);
        m_cb.handler(NRF_DRV_QSPI_EVENT_DONE, m_cb.p_context);
    }
}

#endif // QSPI_ENABLED
