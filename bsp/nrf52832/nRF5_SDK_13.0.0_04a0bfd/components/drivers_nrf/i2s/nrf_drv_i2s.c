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
#if NRF_MODULE_ENABLED(I2S)
#include "nrf_drv_i2s.h"
#include "nrf_drv_common.h"
#include "nrf_gpio.h"
#include "nrf_assert.h"
#include "app_util_platform.h"

#define NRF_LOG_MODULE_NAME "I2S"

#if I2S_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       I2S_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  I2S_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR I2S_CONFIG_DEBUG_COLOR
#define EVT_TO_STR(event)   (event == NRF_I2S_EVENT_RXPTRUPD ? "NRF_I2S_EVENT_RXPTRUPD" :                \
                            (event == NRF_I2S_EVENT_TXPTRUPD ? "NRF_I2S_EVENT_TXPTRUPD" :                \
                            (event == NRF_I2S_EVENT_STOPPED ? "NRF_I2S_EVENT_STOPPED" : "UNKNOWN EVENT")))
#else //I2S_CONFIG_LOG_ENABLED
#define EVT_TO_STR(event)   ""
#define NRF_LOG_LEVEL       0
#endif //I2S_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define MODULE_INITIALIZED (m_cb.state == NRF_DRV_STATE_INITIALIZED) /**< Macro designating whether the module has been initialized properly. */

// Control block - driver instance local data.
typedef struct
{
    nrf_drv_i2s_data_handler_t handler;
    nrf_drv_state_t            state;

    bool       synchronized_mode : 1;
    bool       rx_ready          : 1;
    bool       tx_ready          : 1;
    bool       just_started      : 1;
    uint16_t   buffer_half_size;
    uint32_t * p_rx_buffer;
    uint32_t * p_tx_buffer;
} i2s_control_block_t;
static i2s_control_block_t m_cb;


static nrf_drv_i2s_config_t const m_default_config = NRF_DRV_I2S_DEFAULT_CONFIG;


static void configure_pins(nrf_drv_i2s_config_t const * p_config)
{
    uint32_t mck_pin, sdout_pin, sdin_pin;

    // Configure pins used by the peripheral:

    // - SCK and LRCK (required) - depending on the mode of operation these
    //   pins are configured as outputs (in Master mode) or inputs (in Slave
    //   mode).
    if (p_config->mode == NRF_I2S_MODE_MASTER)
    {
        nrf_gpio_cfg_output(p_config->sck_pin);
        nrf_gpio_cfg_output(p_config->lrck_pin);
    }
    else
    {
        nrf_gpio_cfg_input(p_config->sck_pin,  NRF_GPIO_PIN_NOPULL);
        nrf_gpio_cfg_input(p_config->lrck_pin, NRF_GPIO_PIN_NOPULL);
    }

    // - MCK (optional) - always output,
    if (p_config->mck_pin != NRF_DRV_I2S_PIN_NOT_USED)
    {
        mck_pin = p_config->mck_pin;
        nrf_gpio_cfg_output(mck_pin);
    }
    else
    {
        mck_pin = NRF_I2S_PIN_NOT_CONNECTED;
    }

    // - SDOUT (optional) - always output,
    if (p_config->sdout_pin != NRF_DRV_I2S_PIN_NOT_USED)
    {
        sdout_pin = p_config->sdout_pin;
        nrf_gpio_cfg_output(sdout_pin);
    }
    else
    {
        sdout_pin = NRF_I2S_PIN_NOT_CONNECTED;
    }

    // - SDIN (optional) - always input.
    if (p_config->sdin_pin != NRF_DRV_I2S_PIN_NOT_USED)
    {
        sdin_pin = p_config->sdin_pin;
        nrf_gpio_cfg_input(sdin_pin, NRF_GPIO_PIN_NOPULL);
    }
    else
    {
        sdin_pin = NRF_I2S_PIN_NOT_CONNECTED;
    }

    nrf_i2s_pins_set(NRF_I2S, p_config->sck_pin, p_config->lrck_pin,
        mck_pin, sdout_pin, sdin_pin);
}


ret_code_t nrf_drv_i2s_init(nrf_drv_i2s_config_t const * p_config,
                            nrf_drv_i2s_data_handler_t   handler)
{
    ASSERT(handler);

    ret_code_t err_code;

    if (m_cb.state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    if (p_config == NULL)
    {
        p_config = &m_default_config;
    }

    if (!nrf_i2s_configure(NRF_I2S, p_config->mode,
                                    p_config->format,
                                    p_config->alignment,
                                    p_config->sample_width,
                                    p_config->channels,
                                    p_config->mck_setup,
                                    p_config->ratio))
    {
        err_code = NRF_ERROR_INVALID_PARAM;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    configure_pins(p_config);

    m_cb.handler = handler;

    nrf_drv_common_irq_enable(I2S_IRQn, p_config->irq_priority);

    m_cb.state = NRF_DRV_STATE_INITIALIZED;

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_i2s_uninit(void)
{
    ASSERT(m_cb.state != NRF_DRV_STATE_UNINITIALIZED);

    nrf_drv_i2s_stop();

    nrf_drv_common_irq_disable(I2S_IRQn);

    m_cb.state = NRF_DRV_STATE_UNINITIALIZED;
    NRF_LOG_INFO("Initialized.\r\n");
}


ret_code_t nrf_drv_i2s_start(uint32_t * p_rx_buffer,
                             uint32_t * p_tx_buffer,
                             uint16_t   buffer_size,
                             uint8_t    flags)
{
    ASSERT((p_rx_buffer != NULL) || (p_tx_buffer != NULL));

    uint16_t buffer_half_size = buffer_size / 2;
    ASSERT(buffer_half_size != 0);

    VERIFY_MODULE_INITIALIZED();

    ret_code_t err_code;

    if ((p_rx_buffer != NULL) && !nrf_drv_is_in_RAM(p_rx_buffer))
    {
        err_code = NRF_ERROR_INVALID_ADDR;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    if ((p_tx_buffer != NULL) && !nrf_drv_is_in_RAM(p_tx_buffer))
    {
        err_code = NRF_ERROR_INVALID_ADDR;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    // Initially we set up the peripheral to use the first half of each buffer,
    // then in 'I2S_IRQHandler' we will switch to the second half.
    nrf_i2s_transfer_set(NRF_I2S, buffer_half_size, p_rx_buffer, p_tx_buffer);

    m_cb.p_rx_buffer      = p_rx_buffer;
    m_cb.p_tx_buffer      = p_tx_buffer;
    m_cb.buffer_half_size = buffer_half_size;
    m_cb.just_started     = true;

    if ((flags & NRF_DRV_I2S_FLAG_SYNCHRONIZED_MODE) &&
        // [synchronized mode makes sense only when both RX and TX are enabled]
        (m_cb.p_rx_buffer != NULL) && (m_cb.p_tx_buffer != NULL))
    {
        m_cb.synchronized_mode = true;
        m_cb.rx_ready          = false;
        m_cb.tx_ready          = false;
    }
    else
    {
        m_cb.synchronized_mode = false;
    }

    nrf_i2s_enable(NRF_I2S);

    m_cb.state = NRF_DRV_STATE_POWERED_ON;

    if (m_cb.p_tx_buffer != NULL)
    {
        // Get from the application the first portion of data to be sent - we
        // need to have it in the transmit buffer before we start the transfer.
        // Unless the synchronized mode is active. In this mode we must wait
        // with this until the first portion of data is received, so here we
        // just make sure that there will be silence on the SDOUT line prior
        // to that moment.
        if (m_cb.synchronized_mode)
        {
            memset(m_cb.p_tx_buffer, 0, buffer_size);
        }
        else
        {
            m_cb.handler(NULL, m_cb.p_tx_buffer, m_cb.buffer_half_size);
        }
    }

    nrf_i2s_event_clear(NRF_I2S, NRF_I2S_EVENT_RXPTRUPD);
    nrf_i2s_event_clear(NRF_I2S, NRF_I2S_EVENT_TXPTRUPD);
    nrf_i2s_int_enable(NRF_I2S,
        NRF_I2S_INT_RXPTRUPD_MASK | NRF_I2S_INT_TXPTRUPD_MASK);
    nrf_i2s_task_trigger(NRF_I2S, NRF_I2S_TASK_START);

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n", (uint32_t)__func__, (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_i2s_stop(void)
{
    ASSERT(m_cb.state != NRF_DRV_STATE_UNINITIALIZED);

    // First disable interrupts, then trigger the STOP task, so no spurious
    // RXPTRUPD and TXPTRUPD events (see FTPAN-55) will be processed.
    nrf_i2s_int_disable(NRF_I2S,
        NRF_I2S_INT_RXPTRUPD_MASK | NRF_I2S_INT_TXPTRUPD_MASK);

    nrf_i2s_task_trigger(NRF_I2S, NRF_I2S_TASK_STOP);

    nrf_i2s_disable(NRF_I2S);

    m_cb.state = NRF_DRV_STATE_INITIALIZED;

    NRF_LOG_INFO("Disabled.");
}


void I2S_IRQHandler(void)
{
    uint32_t * p_data_received = NULL;
    uint32_t * p_data_to_send  = NULL;

    if (nrf_i2s_event_check(NRF_I2S, NRF_I2S_EVENT_TXPTRUPD))
    {
        nrf_i2s_event_clear(NRF_I2S, NRF_I2S_EVENT_TXPTRUPD);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_I2S_EVENT_TXPTRUPD));

        // If transmission is not enabled, but for some reason the TXPTRUPD
        // event has been generated, just ignore it.
        if (m_cb.p_tx_buffer != NULL)
        {
            uint32_t * p_tx_buffer_next;
            if (nrf_i2s_tx_buffer_get(NRF_I2S) == m_cb.p_tx_buffer)
            {
                p_tx_buffer_next = m_cb.p_tx_buffer + m_cb.buffer_half_size;
            }
            else
            {
                p_tx_buffer_next = m_cb.p_tx_buffer;
            }
            nrf_i2s_tx_buffer_set(NRF_I2S, p_tx_buffer_next);

            m_cb.tx_ready = true;

            // Now the part of the buffer that we've configured as "next" should
            // be filled by the application with proper data to be sent;
            // the peripheral is sending data from the other part of the buffer
            // (but it will finish soon...).
            p_data_to_send = p_tx_buffer_next;

        }
    }

    if (nrf_i2s_event_check(NRF_I2S, NRF_I2S_EVENT_RXPTRUPD))
    {
        nrf_i2s_event_clear(NRF_I2S, NRF_I2S_EVENT_RXPTRUPD);
        NRF_LOG_DEBUG("Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_I2S_EVENT_RXPTRUPD));

        // If reception is not enabled, but for some reason the RXPTRUPD event
        // has been generated, just ignore it.
        if (m_cb.p_rx_buffer != NULL)
        {
            uint32_t * p_rx_buffer_next;
            if (nrf_i2s_rx_buffer_get(NRF_I2S) == m_cb.p_rx_buffer)
            {
                p_rx_buffer_next = m_cb.p_rx_buffer + m_cb.buffer_half_size;
            }
            else
            {
                p_rx_buffer_next = m_cb.p_rx_buffer;
            }
            nrf_i2s_rx_buffer_set(NRF_I2S, p_rx_buffer_next);

            m_cb.rx_ready = true;

            // The RXPTRUPD event is generated for the first time right after
            // the transfer is started. Since there is no data received yet at
            // this point we only update the buffer pointer (it is done above),
            // there is no callback to the application.
            // [for synchronized mode this has to be handled differently -
            //  see below]
            if (m_cb.just_started && !m_cb.synchronized_mode)
            {
                m_cb.just_started = false;
            }
            else
            {
                // The RXPTRUPD event indicates that from now on the peripheral
                // will be filling the part of the buffer that was pointed at
                // the time the event has been generated, hence now we can let
                // the application process the data stored in the other part of
                // the buffer - the one that we've just set to be filled next.
                p_data_received = p_rx_buffer_next;
            }
        }
    }

    // Call the data handler passing received data to the application and/or
    // requesting data to be sent.
    if (!m_cb.synchronized_mode)
    {
        if ((p_data_received != NULL) || (p_data_to_send != NULL))
        {
            if (p_data_received != NULL)
            {
                NRF_LOG_DEBUG("Rx data:\r\n");
                NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_data_received,
                                        m_cb.buffer_half_size * sizeof(p_data_received));
            }
            m_cb.handler(p_data_received, p_data_to_send,
                m_cb.buffer_half_size);
            if (p_data_to_send != NULL)
            {
                NRF_LOG_DEBUG("Tx data:\r\n");
                NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_data_to_send,
                                        m_cb.buffer_half_size * sizeof(p_data_to_send));
            }
        }
    }
    // In the synchronized mode wait until the events for both RX and TX occur.
    // And ignore the initial occurrences of these events, since they only
    // indicate that the transfer has started - no data is received yet at
    // that moment, so we have got nothing to pass to the application.
    else
    {
        if (m_cb.rx_ready && m_cb.tx_ready)
        {
            m_cb.rx_ready = false;
            m_cb.tx_ready = false;

            if (m_cb.just_started)
            {
                m_cb.just_started = false;
            }
            else
            {
                NRF_LOG_DEBUG("Rx data:\r\n");
                NRF_LOG_HEXDUMP_DEBUG((uint8_t *)nrf_i2s_rx_buffer_get(NRF_I2S),
                                        m_cb.buffer_half_size * sizeof(p_data_to_send));
                m_cb.handler(nrf_i2s_rx_buffer_get(NRF_I2S),
                             nrf_i2s_tx_buffer_get(NRF_I2S),
                             m_cb.buffer_half_size);
                NRF_LOG_DEBUG("Tx data:\r\n");
                NRF_LOG_HEXDUMP_DEBUG((uint8_t *)nrf_i2s_tx_buffer_get(NRF_I2S),
                                        m_cb.buffer_half_size * sizeof(p_data_to_send));
            }
        }
    }
}
#endif //NRF_MODULE_ENABLED(I2S)
