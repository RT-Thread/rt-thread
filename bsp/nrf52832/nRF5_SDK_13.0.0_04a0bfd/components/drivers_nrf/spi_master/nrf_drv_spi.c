/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(SPI)
#define ENABLED_SPI_COUNT (SPI0_ENABLED+SPI1_ENABLED+SPI2_ENABLED)
#if ENABLED_SPI_COUNT

#include "nrf_drv_spi.h"
#include "nrf_drv_common.h"
#include "nrf_gpio.h"
#include "nrf_assert.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "SPI"

#if SPI_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       SPI_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  SPI_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR SPI_CONFIG_DEBUG_COLOR
#else //SPI_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif //SPI_CONFIG_LOG_ENABLED
#include "nrf_log.h"

#ifndef SPIM_PRESENT
    // Make sure SPIx_USE_EASY_DMA is 0 for nRF51 (if a common
    // "nrf_drv_config.h" file is provided for nRF51 and nRF52).
    #undef  SPI0_USE_EASY_DMA
    #define SPI0_USE_EASY_DMA 0
    #undef  SPI1_USE_EASY_DMA
    #define SPI1_USE_EASY_DMA 0
    #undef  SPI2_USE_EASY_DMA
    #define SPI2_USE_EASY_DMA 0
#endif

#ifndef SPI0_USE_EASY_DMA
#define SPI0_USE_EASY_DMA 0
#endif

#ifndef SPI1_USE_EASY_DMA
#define SPI1_USE_EASY_DMA 0
#endif

#ifndef SPI2_USE_EASY_DMA
#define SPI2_USE_EASY_DMA 0
#endif

// This set of macros makes it possible to exclude parts of code when one type
// of supported peripherals is not used.
#if ((NRF_MODULE_ENABLED(SPI0) && SPI0_USE_EASY_DMA) || \
     (NRF_MODULE_ENABLED(SPI1) && SPI1_USE_EASY_DMA) || \
     (NRF_MODULE_ENABLED(SPI2) && SPI2_USE_EASY_DMA))
    #define SPIM_IN_USE
#endif
#if ((NRF_MODULE_ENABLED(SPI0) && !SPI0_USE_EASY_DMA) || \
     (NRF_MODULE_ENABLED(SPI1) && !SPI1_USE_EASY_DMA) || \
     (NRF_MODULE_ENABLED(SPI2) && !SPI2_USE_EASY_DMA))
    #define SPI_IN_USE
#endif
#if defined(SPIM_IN_USE) && defined(SPI_IN_USE)
    // SPIM and SPI combined
    #define CODE_FOR_SPIM(code) if (p_instance->use_easy_dma) { code }
    #define CODE_FOR_SPI(code)  else { code }
#elif defined(SPIM_IN_USE) && !defined(SPI_IN_USE)
    // SPIM only
    #define CODE_FOR_SPIM(code) { code }
    #define CODE_FOR_SPI(code)
#elif !defined(SPIM_IN_USE) && defined(SPI_IN_USE)
    // SPI only
    #define CODE_FOR_SPIM(code)
    #define CODE_FOR_SPI(code)  { code }
#else
    #error "Wrong configuration."
#endif

#ifdef SPIM_IN_USE
#define END_INT_MASK     NRF_SPIM_INT_END_MASK
#endif

// Control block - driver instance local data.
typedef struct
{
    nrf_drv_spi_evt_handler_t handler;
    void *                p_context;
    nrf_drv_spi_evt_t     evt;  // Keep the struct that is ready for event handler. Less memcpy.
    nrf_drv_state_t       state;
    volatile bool         transfer_in_progress;

    // [no need for 'volatile' attribute for the following members, as they
    //  are not concurrently used in IRQ handlers and main line code]
    uint8_t         ss_pin;
    uint8_t         orc;
    uint8_t         bytes_transferred;

#if NRF_MODULE_ENABLED(SPIM_NRF52_ANOMALY_109_WORKAROUND)
    uint8_t         tx_length;
    uint8_t         rx_length;
#endif

    bool tx_done : 1;
    bool rx_done : 1;
    bool abort   : 1;
} spi_control_block_t;
static spi_control_block_t m_cb[ENABLED_SPI_COUNT];

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    #define IRQ_HANDLER_NAME(n) irq_handler_for_instance_##n
    #define IRQ_HANDLER(n)      static void IRQ_HANDLER_NAME(n)(void)

    #if NRF_MODULE_ENABLED(SPI0)
        IRQ_HANDLER(0);
    #endif
    #if NRF_MODULE_ENABLED(SPI1)
        IRQ_HANDLER(1);
    #endif
    #if NRF_MODULE_ENABLED(SPI2)
        IRQ_HANDLER(2);
    #endif
    static nrf_drv_irq_handler_t const m_irq_handlers[ENABLED_SPI_COUNT] = {
    #if NRF_MODULE_ENABLED(SPI0)
        IRQ_HANDLER_NAME(0),
    #endif
    #if NRF_MODULE_ENABLED(SPI1)
        IRQ_HANDLER_NAME(1),
    #endif
    #if NRF_MODULE_ENABLED(SPI2)
        IRQ_HANDLER_NAME(2),
    #endif
    };
#else
    #define IRQ_HANDLER(n) void SPI##n##_IRQ_HANDLER(void)
#endif // NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)

ret_code_t nrf_drv_spi_init(nrf_drv_spi_t const * const p_instance,
                            nrf_drv_spi_config_t const * p_config,
                            nrf_drv_spi_evt_handler_t handler,
                            void * p_context)
{
    ASSERT(p_config);
    spi_control_block_t * p_cb  = &m_cb[p_instance->drv_inst_idx];
    ret_code_t err_code;

    if (p_cb->state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    if (nrf_drv_common_per_res_acquire(p_instance->p_registers,
            m_irq_handlers[p_instance->drv_inst_idx]) != NRF_SUCCESS)
    {
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
#endif

    p_cb->handler = handler;
    p_cb->p_context = p_context;

    uint32_t mosi_pin;
    uint32_t miso_pin;
    // Configure pins used by the peripheral:
    // - SCK - output with initial value corresponding with the SPI mode used:
    //   0 - for modes 0 and 1 (CPOL = 0), 1 - for modes 2 and 3 (CPOL = 1);
    //   according to the reference manual guidelines this pin and its input
    //   buffer must always be connected for the SPI to work.
    if (p_config->mode <= NRF_DRV_SPI_MODE_1)
    {
        nrf_gpio_pin_clear(p_config->sck_pin);
    }
    else
    {
        nrf_gpio_pin_set(p_config->sck_pin);
    }
    nrf_gpio_cfg(p_config->sck_pin,
                 NRF_GPIO_PIN_DIR_OUTPUT,
                 NRF_GPIO_PIN_INPUT_CONNECT,
                 NRF_GPIO_PIN_NOPULL,
                 NRF_GPIO_PIN_S0S1,
                 NRF_GPIO_PIN_NOSENSE);
    // - MOSI (optional) - output with initial value 0,
    if (p_config->mosi_pin != NRF_DRV_SPI_PIN_NOT_USED)
    {
        mosi_pin = p_config->mosi_pin;
        nrf_gpio_pin_clear(mosi_pin);
        nrf_gpio_cfg_output(mosi_pin);
    }
    else
    {
        mosi_pin = NRF_SPI_PIN_NOT_CONNECTED;
    }
    // - MISO (optional) - input,
    if (p_config->miso_pin != NRF_DRV_SPI_PIN_NOT_USED)
    {
        miso_pin = p_config->miso_pin;
        nrf_gpio_cfg_input(miso_pin, NRF_GPIO_PIN_NOPULL);
    }
    else
    {
        miso_pin = NRF_SPI_PIN_NOT_CONNECTED;
    }
    // - Slave Select (optional) - output with initial value 1 (inactive).
    if (p_config->ss_pin != NRF_DRV_SPI_PIN_NOT_USED)
    {
        nrf_gpio_pin_set(p_config->ss_pin);
        nrf_gpio_cfg_output(p_config->ss_pin);
    }
    m_cb[p_instance->drv_inst_idx].ss_pin = p_config->ss_pin;

    CODE_FOR_SPIM
    (
        NRF_SPIM_Type * p_spim = (NRF_SPIM_Type *)p_instance->p_registers;
        nrf_spim_pins_set(p_spim, p_config->sck_pin, mosi_pin, miso_pin);
        nrf_spim_frequency_set(p_spim,
            (nrf_spim_frequency_t)p_config->frequency);
        nrf_spim_configure(p_spim,
            (nrf_spim_mode_t)p_config->mode,
            (nrf_spim_bit_order_t)p_config->bit_order);

        nrf_spim_orc_set(p_spim, p_config->orc);

        if (p_cb->handler)
        {
            nrf_spim_int_enable(p_spim, END_INT_MASK);
        }

        nrf_spim_enable(p_spim);
    )
    CODE_FOR_SPI
    (
        NRF_SPI_Type * p_spi = p_instance->p_registers;
        nrf_spi_pins_set(p_spi, p_config->sck_pin, mosi_pin, miso_pin);
        nrf_spi_frequency_set(p_spi,
            (nrf_spi_frequency_t)p_config->frequency);
        nrf_spi_configure(p_spi,
            (nrf_spi_mode_t)p_config->mode,
            (nrf_spi_bit_order_t)p_config->bit_order);

        m_cb[p_instance->drv_inst_idx].orc = p_config->orc;

        if (p_cb->handler)
        {
            nrf_spi_int_enable(p_spi, NRF_SPI_INT_READY_MASK);
        }

        nrf_spi_enable(p_spi);
    )

    if (p_cb->handler)
    {
        nrf_drv_common_irq_enable(p_instance->irq, p_config->irq_priority);
    }

    p_cb->transfer_in_progress = false;
    p_cb->state = NRF_DRV_STATE_INITIALIZED;

    NRF_LOG_INFO("Init\r\n");

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n",
                 (uint32_t)__func__,
                 (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

void nrf_drv_spi_uninit(nrf_drv_spi_t const * const p_instance)
{
    spi_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);

    if (p_cb->handler)
    {
        nrf_drv_common_irq_disable(p_instance->irq);
    }

    #define DISABLE_ALL  0xFFFFFFFF

    CODE_FOR_SPIM
    (
        NRF_SPIM_Type * p_spim = (NRF_SPIM_Type *)p_instance->p_registers;
        if (p_cb->handler)
        {
            nrf_spim_int_disable(p_spim, DISABLE_ALL);
            if (p_cb->transfer_in_progress)
            {
                // Ensure that SPI is not performing any transfer.
                nrf_spim_task_trigger(p_spim, NRF_SPIM_TASK_STOP);
                while (!nrf_spim_event_check(p_spim, NRF_SPIM_EVENT_STOPPED)) {}
                p_cb->transfer_in_progress = false;
            }
        }
        nrf_spim_disable(p_spim);
    )
    CODE_FOR_SPI
    (
        NRF_SPI_Type * p_spi = p_instance->p_registers;
        if (p_cb->handler)
        {
            nrf_spi_int_disable(p_spi, DISABLE_ALL);
        }
        nrf_spi_disable(p_spi);
    )
    #undef DISABLE_ALL

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    nrf_drv_common_per_res_release(p_instance->p_registers);
#endif

    p_cb->state = NRF_DRV_STATE_UNINITIALIZED;
}

ret_code_t nrf_drv_spi_transfer(nrf_drv_spi_t const * const p_instance,
                                uint8_t const * p_tx_buffer,
                                uint8_t         tx_buffer_length,
                                uint8_t       * p_rx_buffer,
                                uint8_t         rx_buffer_length)
{
    nrf_drv_spi_xfer_desc_t xfer_desc;
    xfer_desc.p_tx_buffer = p_tx_buffer;
    xfer_desc.p_rx_buffer = p_rx_buffer;
    xfer_desc.tx_length   = tx_buffer_length;
    xfer_desc.rx_length   = rx_buffer_length;

    NRF_LOG_INFO("Transfer tx_len:%d, rx_len:%d.\r\n", tx_buffer_length, rx_buffer_length);
    NRF_LOG_DEBUG("Tx data:\r\n");
    NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_tx_buffer, tx_buffer_length * sizeof(p_tx_buffer));
    return nrf_drv_spi_xfer(p_instance, &xfer_desc, 0);
}

static void finish_transfer(spi_control_block_t * p_cb)
{
    // If Slave Select signal is used, this is the time to deactivate it.
    if (p_cb->ss_pin != NRF_DRV_SPI_PIN_NOT_USED)
    {
        nrf_gpio_pin_set(p_cb->ss_pin);
    }

    // By clearing this flag before calling the handler we allow subsequent
    // transfers to be started directly from the handler function.
    p_cb->transfer_in_progress = false;
    p_cb->evt.type = NRF_DRV_SPI_EVENT_DONE;
    NRF_LOG_INFO("Transfer rx_len:%d.\r\n", p_cb->evt.data.done.rx_length);
    NRF_LOG_DEBUG("Rx data:\r\n");
    NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_cb->evt.data.done.p_rx_buffer,
                          p_cb->evt.data.done.rx_length * sizeof(p_cb->evt.data.done.p_rx_buffer));
    p_cb->handler(&p_cb->evt, p_cb->p_context);
}

#ifdef SPI_IN_USE
// This function is called from IRQ handler or, in blocking mode, directly
// from the 'nrf_drv_spi_transfer' function.
// It returns true as long as the transfer should be continued, otherwise (when
// there is nothing more to send/receive) it returns false.
static bool transfer_byte(NRF_SPI_Type * p_spi, spi_control_block_t * p_cb)
{
    // Read the data byte received in this transfer and store it in RX buffer,
    // if needed.
    volatile uint8_t rx_data = nrf_spi_rxd_get(p_spi);
    if (p_cb->bytes_transferred < p_cb->evt.data.done.rx_length)
    {
        p_cb->evt.data.done.p_rx_buffer[p_cb->bytes_transferred] = rx_data;
    }

    ++p_cb->bytes_transferred;

    // Check if there are more bytes to send or receive and write proper data
    // byte (next one from TX buffer or over-run character) to the TXD register
    // when needed.
    // NOTE - we've already used 'p_cb->bytes_transferred + 1' bytes from our
    //        buffers, because we take advantage of double buffering of TXD
    //        register (so in effect one byte is still being transmitted now);
    //        see how the transfer is started in the 'nrf_drv_spi_transfer'
    //        function.
    uint16_t bytes_used = p_cb->bytes_transferred + 1;

    if (p_cb->abort)
    {
        if (bytes_used < p_cb->evt.data.done.tx_length)
        {
            p_cb->evt.data.done.tx_length = bytes_used;
        }
        if (bytes_used < p_cb->evt.data.done.rx_length)
        {
            p_cb->evt.data.done.rx_length = bytes_used;
        }
    }

    if (bytes_used < p_cb->evt.data.done.tx_length)
    {
        nrf_spi_txd_set(p_spi, p_cb->evt.data.done.p_tx_buffer[bytes_used]);
        return true;
    }
    else if (bytes_used < p_cb->evt.data.done.rx_length)
    {
        nrf_spi_txd_set(p_spi, p_cb->orc);
        return true;
    }

    return (p_cb->bytes_transferred < p_cb->evt.data.done.tx_length ||
            p_cb->bytes_transferred < p_cb->evt.data.done.rx_length);
}

static void spi_xfer(NRF_SPI_Type                  * p_spi,
                     spi_control_block_t           * p_cb,
                     nrf_drv_spi_xfer_desc_t const * p_xfer_desc)
{
    p_cb->bytes_transferred = 0;
    nrf_spi_int_disable(p_spi, NRF_SPI_INT_READY_MASK);

    nrf_spi_event_clear(p_spi, NRF_SPI_EVENT_READY);

    // Start the transfer by writing some byte to the TXD register;
    // if TX buffer is not empty, take the first byte from this buffer,
    // otherwise - use over-run character.
    nrf_spi_txd_set(p_spi,
        (p_xfer_desc->tx_length > 0 ?  p_xfer_desc->p_tx_buffer[0] : p_cb->orc));

    // TXD register is double buffered, so next byte to be transmitted can
    // be written immediately, if needed, i.e. if TX or RX transfer is to
    // be more that 1 byte long. Again - if there is something more in TX
    // buffer send it, otherwise use over-run character.
    if (p_xfer_desc->tx_length > 1)
    {
        nrf_spi_txd_set(p_spi, p_xfer_desc->p_tx_buffer[1]);
    }
    else if (p_xfer_desc->rx_length > 1)
    {
        nrf_spi_txd_set(p_spi, p_cb->orc);
    }

    // For blocking mode (user handler not provided) wait here for READY
    // events (indicating that the byte from TXD register was transmitted
    // and a new incoming byte was moved to the RXD register) and continue
    // transaction until all requested bytes are transferred.
    // In non-blocking mode - IRQ service routine will do this stuff.
    if (p_cb->handler)
    {
        nrf_spi_int_enable(p_spi, NRF_SPI_INT_READY_MASK);
    }
    else
    {
        do {
            while (!nrf_spi_event_check(p_spi, NRF_SPI_EVENT_READY)) {}
            nrf_spi_event_clear(p_spi, NRF_SPI_EVENT_READY);
            NRF_LOG_DEBUG("SPI: Event: NRF_SPI_EVENT_READY.\r\n");
        } while (transfer_byte(p_spi, p_cb));
        if (p_cb->ss_pin != NRF_DRV_SPI_PIN_NOT_USED)
        {
            nrf_gpio_pin_set(p_cb->ss_pin);
        }
    }
}
#endif // SPI_IN_USE

#ifdef SPIM_IN_USE
__STATIC_INLINE void spim_int_enable(NRF_SPIM_Type * p_spim, bool enable)
{
    if (!enable)
    {
        nrf_spim_int_disable(p_spim, END_INT_MASK);
    }
    else
    {
        nrf_spim_int_enable(p_spim, END_INT_MASK);
    }
}

__STATIC_INLINE void spim_list_enable_handle(NRF_SPIM_Type * p_spim, uint32_t flags)
{
    if (NRF_DRV_SPI_FLAG_TX_POSTINC & flags)
    {
        nrf_spim_tx_list_enable(p_spim);
    }
    else
    {
        nrf_spim_tx_list_disable(p_spim);
    }

    if (NRF_DRV_SPI_FLAG_RX_POSTINC & flags)
    {
        nrf_spim_rx_list_enable(p_spim);
    }
    else
    {
        nrf_spim_rx_list_disable(p_spim);
    }
}

static ret_code_t spim_xfer(NRF_SPIM_Type                * p_spim,
                           spi_control_block_t           * p_cb,
                           nrf_drv_spi_xfer_desc_t const * p_xfer_desc,
                           uint32_t                        flags)
{
    ret_code_t err_code;
    // EasyDMA requires that transfer buffers are placed in Data RAM region;
    // signal error if they are not.
    if ((p_xfer_desc->p_tx_buffer != NULL && !nrf_drv_is_in_RAM(p_xfer_desc->p_tx_buffer)) ||
        (p_xfer_desc->p_rx_buffer != NULL && !nrf_drv_is_in_RAM(p_xfer_desc->p_rx_buffer)))
    {
        p_cb->transfer_in_progress = false;
        err_code = NRF_ERROR_INVALID_ADDR;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

#if NRF_MODULE_ENABLED(SPIM_NRF52_ANOMALY_109_WORKAROUND)
    p_cb->tx_length = 0;
    p_cb->rx_length = 0;
#endif

    nrf_spim_tx_buffer_set(p_spim, p_xfer_desc->p_tx_buffer, p_xfer_desc->tx_length);
    nrf_spim_rx_buffer_set(p_spim, p_xfer_desc->p_rx_buffer, p_xfer_desc->rx_length);

    nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_END);

    spim_list_enable_handle(p_spim, flags);

    if (!(flags & NRF_DRV_SPI_FLAG_HOLD_XFER))
    {
        nrf_spim_task_trigger(p_spim, NRF_SPIM_TASK_START);
    }
#if NRF_MODULE_ENABLED(SPIM_NRF52_ANOMALY_109_WORKAROUND)
    if (flags & NRF_DRV_SPI_FLAG_HOLD_XFER)
    {
        nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_STARTED);
        p_cb->tx_length = p_xfer_desc->tx_length;
        p_cb->rx_length = p_xfer_desc->rx_length;
        nrf_spim_tx_buffer_set(p_spim, p_xfer_desc->p_tx_buffer, 0);
        nrf_spim_rx_buffer_set(p_spim, p_xfer_desc->p_rx_buffer, 0);
        nrf_spim_int_enable(p_spim, NRF_SPIM_INT_STARTED_MASK);
    }
#endif

    if (!p_cb->handler)
    {
        while (!nrf_spim_event_check(p_spim, NRF_SPIM_EVENT_END)){}
        if (p_cb->ss_pin != NRF_DRV_SPI_PIN_NOT_USED)
        {
            nrf_gpio_pin_set(p_cb->ss_pin);
        }
    }
    else
    {
        spim_int_enable(p_spim, !(flags & NRF_DRV_SPI_FLAG_NO_XFER_EVT_HANDLER));
    }
    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n",
                 (uint32_t)__func__,
                 (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}
#endif

ret_code_t nrf_drv_spi_xfer(nrf_drv_spi_t     const * const p_instance,
                            nrf_drv_spi_xfer_desc_t const * p_xfer_desc,
                            uint32_t                        flags)
{
    spi_control_block_t * p_cb  = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);
    ASSERT(p_xfer_desc->p_tx_buffer != NULL || p_xfer_desc->tx_length == 0);
    ASSERT(p_xfer_desc->p_rx_buffer != NULL || p_xfer_desc->rx_length == 0);

    ret_code_t err_code = NRF_SUCCESS;

    if (p_cb->transfer_in_progress)
    {
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    else
    {
        if (p_cb->handler && !(flags & (NRF_DRV_SPI_FLAG_REPEATED_XFER |
                                        NRF_DRV_SPI_FLAG_NO_XFER_EVT_HANDLER)))
        {
            p_cb->transfer_in_progress = true;
        }
    }

    p_cb->evt.data.done = *p_xfer_desc;
    p_cb->tx_done = false;
    p_cb->rx_done = false;
    p_cb->abort   = false;

    if (p_cb->ss_pin != NRF_DRV_SPI_PIN_NOT_USED)
    {
        nrf_gpio_pin_clear(p_cb->ss_pin);
    }
    CODE_FOR_SPIM
    (
        return spim_xfer(p_instance->p_registers, p_cb,  p_xfer_desc, flags);
    )
    CODE_FOR_SPI
    (
        if (flags)
        {
            p_cb->transfer_in_progress = false;
            err_code = NRF_ERROR_NOT_SUPPORTED;
        }
        else
        {
            spi_xfer(p_instance->p_registers, p_cb, p_xfer_desc);
        }
        NRF_LOG_INFO("Function: %s, error code: %s.\r\n",
                     (uint32_t)__func__,
                     (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    )
}


void nrf_drv_spi_abort(nrf_drv_spi_t const * p_instance)
{
    spi_control_block_t * p_cb = &m_cb[p_instance->drv_inst_idx];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);

    CODE_FOR_SPIM
    (
        nrf_spim_task_trigger(p_instance->p_registers, NRF_SPIM_TASK_STOP);
        while (!nrf_spim_event_check(p_instance->p_registers, NRF_SPIM_EVENT_STOPPED)) {}
        p_cb->transfer_in_progress = false;
    )
    CODE_FOR_SPI
    (
        p_cb->abort = true;
    )
}


#ifdef SPIM_IN_USE
static void irq_handler_spim(NRF_SPIM_Type * p_spim, spi_control_block_t * p_cb)
{

#if NRF_MODULE_ENABLED(SPIM_NRF52_ANOMALY_109_WORKAROUND)
    if ((nrf_spim_int_enable_check(p_spim, NRF_SPIM_INT_STARTED_MASK)) &&
        (nrf_spim_event_check(p_spim, NRF_SPIM_EVENT_STARTED)) )
    {
        /* Handle first, zero-length, auxiliary transmission. */
        nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_STARTED);
        nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_END);

        ASSERT(p_spim->TXD.MAXCNT == 0);
        p_spim->TXD.MAXCNT = p_cb->tx_length;

        ASSERT(p_spim->RXD.MAXCNT == 0);
        p_spim->RXD.MAXCNT = p_cb->rx_length;

        /* Disable STARTED interrupt, used only in auxiliary transmission. */
        nrf_spim_int_disable(p_spim, NRF_SPIM_INT_STARTED_MASK);

        /* Start the actual, glitch-free transmission. */
        nrf_spim_task_trigger(p_spim, NRF_SPIM_TASK_START);
        return;
    }
#endif

    if (nrf_spim_event_check(p_spim, NRF_SPIM_EVENT_END))
    {
        nrf_spim_event_clear(p_spim, NRF_SPIM_EVENT_END);
        ASSERT(p_cb->handler);
        NRF_LOG_DEBUG("SPIM: Event: NRF_SPIM_EVENT_END.\r\n");
        finish_transfer(p_cb);
    }
}

uint32_t nrf_drv_spi_start_task_get(nrf_drv_spi_t const * p_instance)
{
    NRF_SPIM_Type * p_spim = (NRF_SPIM_Type *)p_instance->p_registers;
    return nrf_spim_task_address_get(p_spim, NRF_SPIM_TASK_START);
}

uint32_t nrf_drv_spi_end_event_get(nrf_drv_spi_t const * p_instance)
{
    NRF_SPIM_Type * p_spim = (NRF_SPIM_Type *)p_instance->p_registers;
    return nrf_spim_event_address_get(p_spim, NRF_SPIM_EVENT_END);
}
#endif // SPIM_IN_USE

#ifdef SPI_IN_USE
static void irq_handler_spi(NRF_SPI_Type * p_spi, spi_control_block_t * p_cb)
{
    ASSERT(p_cb->handler);

    nrf_spi_event_clear(p_spi, NRF_SPI_EVENT_READY);
    NRF_LOG_DEBUG("SPI: Event: NRF_SPI_EVENT_READY.\r\n");

    if (!transfer_byte(p_spi, p_cb))
    {
        finish_transfer(p_cb);
    }
}
#endif // SPI_IN_USE

#if NRF_MODULE_ENABLED(SPI0)
IRQ_HANDLER(0)
{
    spi_control_block_t * p_cb  = &m_cb[SPI0_INSTANCE_INDEX];
    #if SPI0_USE_EASY_DMA
        irq_handler_spim(NRF_SPIM0, p_cb);
    #else
        irq_handler_spi(NRF_SPI0, p_cb);
    #endif
}
#endif // NRF_MODULE_ENABLED(SPI0)

#if NRF_MODULE_ENABLED(SPI1)
IRQ_HANDLER(1)
{
    spi_control_block_t * p_cb  = &m_cb[SPI1_INSTANCE_INDEX];
    #if SPI1_USE_EASY_DMA
        irq_handler_spim(NRF_SPIM1, p_cb);
    #else
        irq_handler_spi(NRF_SPI1, p_cb);
    #endif
}
#endif // NRF_MODULE_ENABLED(SPI1)

#if NRF_MODULE_ENABLED(SPI2)
IRQ_HANDLER(2)
{
    spi_control_block_t * p_cb  = &m_cb[SPI2_INSTANCE_INDEX];
    #if SPI2_USE_EASY_DMA
        irq_handler_spim(NRF_SPIM2, p_cb);
    #else
        irq_handler_spi(NRF_SPI2, p_cb);
    #endif
}
#endif // NRF_MODULE_ENABLED(SPI2)
#endif // ENABLED_SPI_COUNT
#endif // NRF_MODULE_ENABLED(SPI)
