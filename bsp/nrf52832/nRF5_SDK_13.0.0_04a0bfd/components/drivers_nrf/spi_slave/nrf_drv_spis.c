/**
 * Copyright (c) 2013 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(SPIS)
#define ENABLED_SPIS_COUNT (SPIS0_ENABLED+SPIS1_ENABLED+SPIS2_ENABLED)
#if ENABLED_SPIS_COUNT
#include "nrf_drv_spis.h"
#include <stdbool.h>
#include <stdio.h>
#include "nrf.h"
#include "nrf_gpio.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "nrf_drv_common.h"
#include "nrf_assert.h"

#define NRF_LOG_MODULE_NAME "SPIS"

#if SPIS_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       SPIS_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  SPIS_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR SPIS_CONFIG_DEBUG_COLOR
#define EVT_TO_STR(event) \
    (event == NRF_SPIS_EVENT_ACQUIRED ? "NRF_SPIS_EVENT_ACQUIRED" : \
    (event == NRF_SPIS_EVENT_END      ? "NRF_SPIS_EVENT_END" : \
                                        "UNKNOWN ERROR"))

#else //SPIS_CONFIG_LOG_ENABLED
#define EVT_TO_STR(event)   ""
#define NRF_LOG_LEVEL       0
#endif //SPIS_CONFIG_LOG_ENABLED
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#if NRF_MODULE_ENABLED(SPIS_NRF52_ANOMALY_109_WORKAROUND)
#include "nrf_drv_gpiote.h"
#define USE_DMA_ISSUE_WORKAROUND
// This handler is called by the GPIOTE driver when a falling edge is detected
// on the CSN line. There is no need to do anything here. The handling of the
// interrupt itself provides a protection for DMA transfers.
static void csn_event_handler(nrf_drv_gpiote_pin_t pin,
                              nrf_gpiote_polarity_t action)
{
}
#endif


/**@brief States of the SPI transaction state machine. */
typedef enum
{
    SPIS_STATE_INIT,                                 /**< Initialization state. In this state the module waits for a call to @ref spi_slave_buffers_set. */
    SPIS_BUFFER_RESOURCE_REQUESTED,                  /**< State where the configuration of the memory buffers, which are to be used in SPI transaction, has started. */
    SPIS_BUFFER_RESOURCE_CONFIGURED,                 /**< State where the configuration of the memory buffers, which are to be used in SPI transaction, has completed. */
    SPIS_XFER_COMPLETED                              /**< State where SPI transaction has been completed. */
} nrf_drv_spis_state_t;


#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    #define IRQ_HANDLER_NAME(n) irq_handler_for_instance_##n
    #define IRQ_HANDLER(n)      static void IRQ_HANDLER_NAME(n)(void)

    #if NRF_MODULE_ENABLED(SPIS0)
        IRQ_HANDLER(0);
    #endif
    #if NRF_MODULE_ENABLED(SPIS1)
        IRQ_HANDLER(1);
    #endif
    #if NRF_MODULE_ENABLED(SPIS2)
        IRQ_HANDLER(2);
    #endif
    static nrf_drv_irq_handler_t const m_irq_handlers[ENABLED_SPIS_COUNT] = {
    #if NRF_MODULE_ENABLED(SPIS0)
        IRQ_HANDLER_NAME(0),
    #endif
    #if NRF_MODULE_ENABLED(SPIS1)
        IRQ_HANDLER_NAME(1),
    #endif
    #if NRF_MODULE_ENABLED(SPIS2)
        IRQ_HANDLER_NAME(2),
    #endif
    };
#else
    #define IRQ_HANDLER(n) void SPIS##n##_IRQ_HANDLER(void)
#endif // PERIPHERAL_RESOURCE_SHARING_ENABLED

#define SPIS_IRQHANDLER_TEMPLATE(NUM) \
    IRQ_HANDLER(NUM)                                                        \
    {                                                                       \
        spis_irq_handler(NRF_SPIS##NUM, &m_cb[SPIS##NUM##_INSTANCE_INDEX]); \
    }


/**@brief SPIS control block - driver instance local data. */
typedef struct
{
    volatile uint32_t             tx_buffer_size;  //!< SPI slave TX buffer size in bytes.
    volatile uint32_t             rx_buffer_size;  //!< SPI slave RX buffer size in bytes.
    nrf_drv_spis_event_handler_t  handler;         //!< SPI event handler.
    volatile const uint8_t *      tx_buffer;       //!< SPI slave TX buffer.
    volatile uint8_t *            rx_buffer;       //!< SPI slave RX buffer.
    nrf_drv_state_t               state;           //!< driver initialization state.
    volatile nrf_drv_spis_state_t spi_state;       //!< SPI slave state.
} spis_cb_t;

static spis_cb_t m_cb[ENABLED_SPIS_COUNT];

ret_code_t nrf_drv_spis_init(nrf_drv_spis_t const * const  p_instance,
                             nrf_drv_spis_config_t const * p_config,
                             nrf_drv_spis_event_handler_t  event_handler)
{
    ASSERT(p_config);
    spis_cb_t * p_cb = &m_cb[p_instance->instance_id];
    ret_code_t err_code;

    NRF_SPIS_Type * p_spis = p_instance->p_reg;

    if (p_cb->state != NRF_DRV_STATE_UNINITIALIZED)
    {
        err_code = NRF_ERROR_INVALID_STATE;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    if ((uint32_t)p_config->mode > (uint32_t)NRF_DRV_SPIS_MODE_3)
    {
        err_code = NRF_ERROR_INVALID_PARAM;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    if (!event_handler)
    {
        err_code = NRF_ERROR_NULL;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    if (nrf_drv_common_per_res_acquire(p_spis,
            m_irq_handlers[p_instance->instance_id]) != NRF_SUCCESS)
    {
        err_code = NRF_ERROR_BUSY;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
#endif

    // Configure the SPI pins for input.
    uint32_t mosi_pin;
    uint32_t miso_pin;

    if (p_config->miso_pin != NRF_DRV_SPIS_PIN_NOT_USED)
    {
        nrf_gpio_cfg(p_config->miso_pin,
                    NRF_GPIO_PIN_DIR_INPUT,
                    NRF_GPIO_PIN_INPUT_CONNECT,
                    NRF_GPIO_PIN_NOPULL,
                    p_config->miso_drive,
                    NRF_GPIO_PIN_NOSENSE);
        miso_pin = p_config->miso_pin;
    }
    else
    {
        miso_pin = NRF_SPIS_PIN_NOT_CONNECTED;
    }

    if (p_config->mosi_pin != NRF_DRV_SPIS_PIN_NOT_USED)
    {
        nrf_gpio_cfg(p_config->mosi_pin,
                     NRF_GPIO_PIN_DIR_INPUT,
                     NRF_GPIO_PIN_INPUT_CONNECT,
                     NRF_GPIO_PIN_NOPULL,
                     NRF_GPIO_PIN_S0S1,
                     NRF_GPIO_PIN_NOSENSE);
        mosi_pin = p_config->mosi_pin;
    }
    else
    {
        mosi_pin = NRF_SPIS_PIN_NOT_CONNECTED;
    }

    nrf_gpio_cfg(p_config->csn_pin,
                 NRF_GPIO_PIN_DIR_INPUT,
                 NRF_GPIO_PIN_INPUT_CONNECT,
                 p_config->csn_pullup,
                 NRF_GPIO_PIN_S0S1,
                 NRF_GPIO_PIN_NOSENSE);

    nrf_gpio_cfg(p_config->sck_pin,
                 NRF_GPIO_PIN_DIR_INPUT,
                 NRF_GPIO_PIN_INPUT_CONNECT,
                 NRF_GPIO_PIN_NOPULL,
                 NRF_GPIO_PIN_S0S1,
                 NRF_GPIO_PIN_NOSENSE);

    nrf_spis_pins_set(p_spis, p_config->sck_pin, mosi_pin, miso_pin, p_config->csn_pin);

    nrf_spis_rx_buffer_set(p_spis, NULL, 0);
    nrf_spis_tx_buffer_set(p_spis, NULL, 0);

    // Configure SPI mode.
    nrf_spis_configure(p_spis, (nrf_spis_mode_t) p_config->mode,
                               (nrf_spis_bit_order_t) p_config->bit_order);

    // Configure DEF and ORC characters.
    nrf_spis_def_set(p_spis, p_config->def);
    nrf_spis_orc_set(p_spis, p_config->orc);

    // Clear possible pending events.
    nrf_spis_event_clear(p_spis, NRF_SPIS_EVENT_END);
    nrf_spis_event_clear(p_spis, NRF_SPIS_EVENT_ACQUIRED);

    // Enable END_ACQUIRE shortcut.
    nrf_spis_shorts_enable(p_spis, NRF_SPIS_SHORT_END_ACQUIRE);

    m_cb[p_instance->instance_id].spi_state = SPIS_STATE_INIT;
    m_cb[p_instance->instance_id].handler = event_handler;

#if defined(USE_DMA_ISSUE_WORKAROUND)
    // Configure a GPIOTE channel to generate interrupts on each falling edge
    // on the CSN line. Handling of these interrupts will make the CPU active,
    // and thus will protect the DMA transfers started by SPIS right after it
    // is selected for communication.
    // [the GPIOTE driver may be already initialized at this point (by this
    //  driver when another SPIS instance is used, or by an application code),
    //  so just ignore the returned value]
    (void)nrf_drv_gpiote_init();
    static nrf_drv_gpiote_in_config_t const csn_gpiote_config =
        GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    ret_code_t gpiote_err_code = nrf_drv_gpiote_in_init(p_config->csn_pin,
        &csn_gpiote_config, csn_event_handler);
    if (gpiote_err_code != NRF_SUCCESS)
    {
        err_code = NRF_ERROR_INTERNAL;
        NRF_LOG_INFO("Function: %s, error code: %s.\r\n",
                     (uint32_t)__func__,
                     (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }
    nrf_drv_gpiote_in_event_enable(p_config->csn_pin, true);
#endif

    // Enable IRQ.
    nrf_spis_int_enable(p_spis, NRF_SPIS_INT_ACQUIRED_MASK | NRF_SPIS_INT_END_MASK);
    nrf_drv_common_irq_enable(p_instance->irq, p_config->irq_priority);

    p_cb->state = NRF_DRV_STATE_INITIALIZED;

    // Enable SPI slave device.
    nrf_spis_enable(p_spis);

    err_code = NRF_SUCCESS;
    NRF_LOG_INFO("Function: %s, error code: %s.\r\n",
                 (uint32_t)__func__,
                 (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}


void nrf_drv_spis_uninit(nrf_drv_spis_t const * const p_instance)
{
    spis_cb_t * p_cb = &m_cb[p_instance->instance_id];
    ASSERT(p_cb->state != NRF_DRV_STATE_UNINITIALIZED);

    NRF_SPIS_Type * p_spis = p_instance->p_reg;

    #define DISABLE_ALL 0xFFFFFFFF
    nrf_spis_disable(p_spis);
    nrf_drv_common_irq_disable(p_instance->irq);
    nrf_spis_int_disable(p_spis, DISABLE_ALL);
    #undef  DISABLE_ALL

#if NRF_MODULE_ENABLED(PERIPHERAL_RESOURCE_SHARING)
    nrf_drv_common_per_res_release(p_spis);
#endif

    p_cb->state = NRF_DRV_STATE_UNINITIALIZED;
    NRF_LOG_INFO("Initialized.\r\n");
}


/**@brief Function for executing the state entry action. */
static void spis_state_entry_action_execute(NRF_SPIS_Type * p_spis,
                                            spis_cb_t * p_cb)
{
    nrf_drv_spis_event_t event;

    switch (p_cb->spi_state)
    {
        case SPIS_BUFFER_RESOURCE_REQUESTED:
            nrf_spis_task_trigger(p_spis, NRF_SPIS_TASK_ACQUIRE);
            break;

        case SPIS_BUFFER_RESOURCE_CONFIGURED:
            event.evt_type  = NRF_DRV_SPIS_BUFFERS_SET_DONE;
            event.rx_amount = 0;
            event.tx_amount = 0;

            APP_ERROR_CHECK_BOOL(p_cb->handler != NULL);
            p_cb->handler(event);
            break;

        case SPIS_XFER_COMPLETED:
            event.evt_type  = NRF_DRV_SPIS_XFER_DONE;
            event.rx_amount = nrf_spis_rx_amount_get(p_spis);
            event.tx_amount = nrf_spis_tx_amount_get(p_spis);
            NRF_LOG_INFO("Transfer rx_len:%d.\r\n", event.rx_amount);
            NRF_LOG_DEBUG("Rx data:\r\n");
            NRF_LOG_HEXDUMP_DEBUG((uint8_t *)p_cb->rx_buffer,
                                  event.rx_amount * sizeof(p_cb->rx_buffer));
            APP_ERROR_CHECK_BOOL(p_cb->handler != NULL);
            p_cb->handler(event);
            break;

        default:
            // No implementation required.
            break;
    }
}

/**@brief Function for changing the state of the SPI state machine.
 *
 * @param[in] p_spis    SPIS instance register.
 * @param[in] p_cb      SPIS instance control block.
 * @param[in] new_state State where the state machine transits to.
 */
static void spis_state_change(NRF_SPIS_Type * p_spis,
                              spis_cb_t * p_cb,
                              nrf_drv_spis_state_t new_state)
{
    p_cb->spi_state = new_state;
    spis_state_entry_action_execute(p_spis, p_cb);
}


ret_code_t nrf_drv_spis_buffers_set(nrf_drv_spis_t const * const  p_instance,
                                    const uint8_t * p_tx_buffer,
                                    uint8_t   tx_buffer_length,
                                    uint8_t * p_rx_buffer,
                                    uint8_t   rx_buffer_length)
{
    spis_cb_t * p_cb = &m_cb[p_instance->instance_id];
    uint32_t err_code;

    VERIFY_PARAM_NOT_NULL(p_rx_buffer);
    VERIFY_PARAM_NOT_NULL(p_tx_buffer);

    // EasyDMA requires that transfer buffers are placed in Data RAM region;
    // signal error if they are not.
    if ((p_tx_buffer != NULL && !nrf_drv_is_in_RAM(p_tx_buffer)) ||
        (p_rx_buffer != NULL && !nrf_drv_is_in_RAM(p_rx_buffer)))
    {
        err_code = NRF_ERROR_INVALID_ADDR;
        NRF_LOG_WARNING("Function: %s, error code: %s.\r\n",
                        (uint32_t)__func__,
                        (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
        return err_code;
    }

    switch (p_cb->spi_state)
    {
        case SPIS_STATE_INIT:
        case SPIS_XFER_COMPLETED:
        case SPIS_BUFFER_RESOURCE_CONFIGURED:
            p_cb->tx_buffer      = p_tx_buffer;
            p_cb->rx_buffer      = p_rx_buffer;
            p_cb->tx_buffer_size = tx_buffer_length;
            p_cb->rx_buffer_size = rx_buffer_length;
            err_code             = NRF_SUCCESS;

            spis_state_change(p_instance->p_reg, p_cb, SPIS_BUFFER_RESOURCE_REQUESTED);
            break;

        case SPIS_BUFFER_RESOURCE_REQUESTED:
            err_code = NRF_ERROR_INVALID_STATE;
            break;

        default:
            // @note: execution of this code path would imply internal error in the design.
            err_code = NRF_ERROR_INTERNAL;
            break;
    }

    NRF_LOG_INFO("Function: %s, error code: %s.\r\n",
                 (uint32_t)__func__,
                 (uint32_t)NRF_LOG_ERROR_STRING_GET(err_code));
    return err_code;
}

static void spis_irq_handler(NRF_SPIS_Type * p_spis, spis_cb_t * p_cb)
{
    // @note: as multiple events can be pending for processing, the correct event processing order
    // is as follows:
    // - SPI semaphore acquired event.
    // - SPI transaction complete event.

    // Check for SPI semaphore acquired event.
    if (nrf_spis_event_check(p_spis, NRF_SPIS_EVENT_ACQUIRED))
    {
        nrf_spis_event_clear(p_spis, NRF_SPIS_EVENT_ACQUIRED);
        NRF_LOG_DEBUG("SPIS: Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_SPIS_EVENT_ACQUIRED));

        switch (p_cb->spi_state)
        {
            case SPIS_BUFFER_RESOURCE_REQUESTED:
                nrf_spis_tx_buffer_set(p_spis, (uint8_t *)p_cb->tx_buffer, p_cb->tx_buffer_size);
                nrf_spis_rx_buffer_set(p_spis, (uint8_t *)p_cb->rx_buffer, p_cb->rx_buffer_size);

                nrf_spis_task_trigger(p_spis, NRF_SPIS_TASK_RELEASE);

                spis_state_change(p_spis, p_cb, SPIS_BUFFER_RESOURCE_CONFIGURED);
                break;

            default:
                // No implementation required.
                break;
        }
    }

    // Check for SPI transaction complete event.
    if (nrf_spis_event_check(p_spis, NRF_SPIS_EVENT_END))
    {
        nrf_spis_event_clear(p_spis, NRF_SPIS_EVENT_END);
        NRF_LOG_DEBUG("SPIS: Event: %s.\r\n", (uint32_t)EVT_TO_STR(NRF_SPIS_EVENT_END));

        switch (p_cb->spi_state)
        {
            case SPIS_BUFFER_RESOURCE_CONFIGURED:
                spis_state_change(p_spis, p_cb, SPIS_XFER_COMPLETED);
                break;

            default:
                // No implementation required.
                break;
        }
    }
}

#if NRF_MODULE_ENABLED(SPIS0)
    SPIS_IRQHANDLER_TEMPLATE(0)
#endif

#if NRF_MODULE_ENABLED(SPIS1)
    SPIS_IRQHANDLER_TEMPLATE(1)
#endif

#if NRF_MODULE_ENABLED(SPIS2)
    SPIS_IRQHANDLER_TEMPLATE(2)
#endif

#endif // SPI_COUNT > 0
#endif // NRF_MODULE_ENABLED(SPIS)
