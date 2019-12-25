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
/**@file
 *
 * @defgroup ser_phy_spi_5W_hw_driver_master spi_5W_master.c
 * @{
 * @ingroup ser_phy_spi_5W_hw_driver_master
 *
 * @brief SPI_5W_RAW hardware driver.
 */

#include "app_error.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf.h"
#include "spi_5W_master.h"
#include "ser_config_5W_app.h"
#include "ser_phy_debug_app.h"
#include "sdk_common.h"


#define _static

#define DOUBLE_BUFFERED /**< A flag for enabling double buffering. */

#define SPI_PIN_DISCONNECTED 0xFFFFFFFF /**< A value used to the PIN deinitialization. */
#define SPI_DEFAULT_TX_BYTE  0x00       /**< Default byte (used to clock transmission
                                             from slave to the master) */

typedef struct
{
    NRF_SPI_Type * p_nrf_spi; /**< A pointer to the NRF SPI master */
    IRQn_Type      irq_type;  /**< A type of NVIC IRQn */

    uint8_t * p_tx_buffer; /**< A pointer to TX buffer. */
    uint16_t  tx_length;   /**< A length of TX buffer. */
    uint16_t  tx_index;    /**< A index of the current element in the TX buffer. */

    uint8_t * p_rx_buffer; /**< A pointer to RX buffer. */
    uint16_t  rx_length;   /**< A length RX buffer. */
    uint16_t  rx_index;    /**< A index of the current element in the RX buffer. */

    uint16_t max_length; /**< Max length (Max of the TX and RX length). */
    uint16_t bytes_count;
    uint8_t  pin_slave_select; /**< A pin for Slave Select. */

    spi_master_event_handler_t callback_event_handler; /**< A handler for event callback function. */
    spi_master_state_t         state;                  /**< A state of an instance of SPI master. */
    bool                       start_flag;
    bool                       abort_flag;

} spi_master_instance_t;

#ifdef _SPI_5W_
typedef enum
{
    HOOK_STATE_DISABLED,
    HOOK_STATE_IDLE,
    HOOK_STATE_GUARDED,
    HOOK_STATE_ABORTED,
    HOOK_STATE_RESTARTED,
    HOOK_STATE_PASSING
} spi_hook_state_t;


_static spi_master_event_handler_t m_ser_phy_event_handler;
_static spi_master_hw_instance_t   m_spi_master_hw_instance;
_static spi_hook_state_t           m_hook_state = HOOK_STATE_DISABLED;
#endif

#ifdef SER_PHY_DEBUG_APP_ENABLE
_static spi_master_raw_callback_t m_debug_callback;
#endif

_static spi_master_instance_t m_spi_master_instances[SPI_MASTER_HW_ENABLED_COUNT];

static __INLINE spi_master_instance_t * spi_master_get_instance(
    const spi_master_hw_instance_t spi_master_hw_instance);
static __INLINE void spi_master_send_recv_irq(spi_master_instance_t * const p_spi_instance);
static __INLINE void spi_master_signal_evt(spi_master_instance_t * const p_spi_instance,
                                           spi_master_evt_type_t         event_type,
                                           const uint16_t                data);

#ifdef SPI_MASTER_0_ENABLE
/**
 * @brief SPI0 interrupt handler.
 */
void SPI0_TWI0_IRQHandler(void)
{
    if (NRF_SPI0->EVENTS_READY != 0)
    {
        NRF_SPI0->EVENTS_READY = 0;

        spi_master_instance_t * p_spi_instance = spi_master_get_instance(SPI_MASTER_0);

        spi_master_send_recv_irq(p_spi_instance);
    }
}
#endif //SPI_MASTER_0_ENABLE

#ifdef SPI_MASTER_1_ENABLE
/**
 * @brief SPI0 interrupt handler.
 */
void SPI1_TWI1_IRQHandler(void)
{
    if (NRF_SPI1->EVENTS_READY != 0)
    {
        NRF_SPI1->EVENTS_READY = 0;

        spi_master_instance_t * p_spi_instance = spi_master_get_instance(SPI_MASTER_1);

        spi_master_send_recv_irq(p_spi_instance);
    }
}
#endif //SPI_MASTER_1_ENABLE

#if defined(SPI_MASTER_0_ENABLE) || defined(SPI_MASTER_1_ENABLE)

/**@brief Function for getting an instance of SPI master. */
static __INLINE spi_master_instance_t * spi_master_get_instance(
    const spi_master_hw_instance_t spi_master_hw_instance)
{
    return &(m_spi_master_instances[(uint8_t)spi_master_hw_instance]);
}

/** @brief Function for initializing instance of SPI master by default values. */
static __INLINE void spi_master_init_hw_instance(NRF_SPI_Type *          p_nrf_spi,
                                                 IRQn_Type               irq_type,
                                                 spi_master_instance_t * p_spi_instance)
{
    APP_ERROR_CHECK_BOOL(p_spi_instance != NULL);

    p_spi_instance->p_nrf_spi = p_nrf_spi;
    p_spi_instance->irq_type  = irq_type;

    p_spi_instance->p_tx_buffer = NULL;
    p_spi_instance->tx_length   = 0;
    p_spi_instance->tx_index    = 0;

    p_spi_instance->p_rx_buffer = NULL;
    p_spi_instance->rx_length   = 0;
    p_spi_instance->rx_index    = 0;

    p_spi_instance->bytes_count      = 0;
    p_spi_instance->max_length       = 0;
    p_spi_instance->pin_slave_select = 0;

    p_spi_instance->callback_event_handler = NULL;

    p_spi_instance->state      = SPI_MASTER_STATE_DISABLED;
    p_spi_instance->abort_flag = false;
    p_spi_instance->start_flag = false;
}

/**@brief Function for initializing TX or RX buffer. */
static __INLINE void spi_master_buffer_init(uint8_t * const  p_buf,
                                            const uint16_t   buf_len,
                                            uint8_t * *      pp_buf,
                                            uint16_t * const p_buf_len,
                                            uint16_t * const p_index)
{
    APP_ERROR_CHECK_BOOL(pp_buf != NULL);
    APP_ERROR_CHECK_BOOL(p_buf_len != NULL);
    APP_ERROR_CHECK_BOOL(p_index != NULL);

    *pp_buf    = p_buf;
    *p_buf_len = (p_buf != NULL) ? buf_len : 0;
    *p_index   = 0;
}

/**@brief Function for releasing TX or RX buffer. */
static __INLINE void spi_master_buffer_release(uint8_t * * const pp_buf, uint16_t * const p_buf_len)
{
    APP_ERROR_CHECK_BOOL(pp_buf != NULL);
    APP_ERROR_CHECK_BOOL(p_buf_len != NULL);

    *pp_buf    = NULL;
    *p_buf_len = 0;
}

/**@brief Function for sending events by callback. */
static __INLINE void spi_master_signal_evt(spi_master_instance_t * const p_spi_instance,
                                           spi_master_evt_type_t         event_type,
                                           const uint16_t                data)
{
    APP_ERROR_CHECK_BOOL(p_spi_instance != NULL);

    if (p_spi_instance->callback_event_handler != NULL)
    {
        spi_master_evt_t event = {SPI_MASTER_EVT_TYPE_MAX, 0};
        event.type = event_type;
        event.data = data;
        p_spi_instance->callback_event_handler(event);
    }
}

/**@brief Function insert to a TX buffer another byte or two bytes (depends on flag @ref DOUBLE_BUFFERED). */
static __INLINE void spi_master_send_initial_bytes(spi_master_instance_t * const p_spi_instance)
{
    APP_ERROR_CHECK_BOOL(p_spi_instance != NULL);

    p_spi_instance->p_nrf_spi->TXD = ((p_spi_instance->p_tx_buffer != NULL) &&
                                      (p_spi_instance->tx_index < p_spi_instance->tx_length)) ?
                                     p_spi_instance->p_tx_buffer[p_spi_instance->tx_index] :
                                     SPI_DEFAULT_TX_BYTE;
    (p_spi_instance->tx_index)++;

    #ifdef DOUBLE_BUFFERED

    if (p_spi_instance->tx_index < p_spi_instance->max_length)
    {
        p_spi_instance->p_nrf_spi->TXD = ((p_spi_instance->p_tx_buffer != NULL) &&
                                          (p_spi_instance->tx_index < p_spi_instance->tx_length)) ?
                                         p_spi_instance->p_tx_buffer[p_spi_instance->tx_index] :
                                         SPI_DEFAULT_TX_BYTE;
        (p_spi_instance->tx_index)++;
    }
    #endif
}

/**@brief Function for receiving and sending data from IRQ. (The same for both IRQs). */
static __INLINE void spi_master_send_recv_irq(spi_master_instance_t * const p_spi_instance)
{

    uint8_t rx_byte;

    APP_ERROR_CHECK_BOOL(p_spi_instance != NULL);
    APP_ERROR_CHECK_BOOL(p_spi_instance->state == SPI_MASTER_STATE_BUSY);

    p_spi_instance->bytes_count++;
    rx_byte = p_spi_instance->p_nrf_spi->RXD;

    if (p_spi_instance->start_flag)
    {
        p_spi_instance->start_flag = false;
        spi_master_signal_evt(p_spi_instance, SPI_MASTER_EVT_FIRST_BYTE_RECEIVED, (uint16_t)rx_byte);
    }
    else if (p_spi_instance->abort_flag  ) //this is tricky, but callback for SPI_MASTER_EVT_FIRST_BYTE_RECEIVED will set this flag for a first byte, which is bad because there is still byte in a buffer
    {                                      //and for a single byte transaction you will get XFERDONE event to restart
        p_spi_instance->abort_flag = false;
        p_spi_instance->state      = SPI_MASTER_STATE_ABORTED;
        nrf_gpio_pin_set(p_spi_instance->pin_slave_select);
        spi_master_signal_evt(p_spi_instance, SPI_MASTER_EVT_TRANSFER_ABORTED, 0);
        return;
    }

    if ((p_spi_instance->p_rx_buffer != NULL) &&
        (p_spi_instance->rx_index < p_spi_instance->rx_length))
    {
        p_spi_instance->p_rx_buffer[p_spi_instance->rx_index++] = rx_byte;
    }

    if ((p_spi_instance->tx_index < p_spi_instance->max_length) && (!(p_spi_instance->abort_flag))) //do not TX if you know that there is an abort to be done - this should work for a DOUBLE BUFFERING ???
    {
        p_spi_instance->p_nrf_spi->TXD = ((p_spi_instance->p_tx_buffer != NULL) &&
                                          (p_spi_instance->tx_index < p_spi_instance->tx_length)) ?
                                         p_spi_instance->p_tx_buffer[p_spi_instance->tx_index] :
                                         SPI_DEFAULT_TX_BYTE;
        (p_spi_instance->tx_index)++;
    }

    if (p_spi_instance->bytes_count >= p_spi_instance->max_length)
    {
        APP_ERROR_CHECK_BOOL(p_spi_instance->bytes_count == p_spi_instance->max_length);
        nrf_gpio_pin_set(p_spi_instance->pin_slave_select);
        p_spi_instance->state = SPI_MASTER_STATE_IDLE;
        spi_master_signal_evt(p_spi_instance,
                              SPI_MASTER_EVT_TRANSFER_COMPLETED,
                              p_spi_instance->tx_index);
    }
    return;
}
#endif //defined(SPI_MASTER_0_ENABLE) || defined(SPI_MASTER_1_ENABLE)


/**
 * @brief Function for opening and initializing a SPI master driver. */
uint32_t spi_master_open(const spi_master_hw_instance_t    spi_master_hw_instance,
                         spi_master_config_t const * const p_spi_master_config)
{
    #if defined(SPI_MASTER_0_ENABLE) || defined(SPI_MASTER_1_ENABLE)


    VERIFY_PARAM_NOT_NULL(p_spi_master_config);

    spi_master_instance_t * p_spi_instance = spi_master_get_instance(spi_master_hw_instance);

    switch (spi_master_hw_instance)
    {
    #ifdef SPI_MASTER_0_ENABLE
        case SPI_MASTER_0:
            spi_master_init_hw_instance(NRF_SPI0, SPI0_TWI0_IRQn, p_spi_instance);
            break;
    #endif //SPI_MASTER_0_ENABLE

    #ifdef SPI_MASTER_1_ENABLE
        case SPI_MASTER_1:
            spi_master_init_hw_instance(NRF_SPI1, SPI1_TWI1_IRQn, p_spi_instance);
            break;
    #endif //SPI_MASTER_1_ENABLE

        default:
            break;
    }

    //A Slave select must be set as high before setting it as output,
    //because during connect it to the pin it causes glitches.
    nrf_gpio_pin_set(p_spi_master_config->SPI_Pin_SS);
    nrf_gpio_cfg_output(p_spi_master_config->SPI_Pin_SS);
    nrf_gpio_pin_set(p_spi_master_config->SPI_Pin_SS);

    //Configure GPIO
    nrf_gpio_cfg_output(p_spi_master_config->SPI_Pin_SCK);
    nrf_gpio_cfg_output(p_spi_master_config->SPI_Pin_MOSI);
    nrf_gpio_cfg_input(p_spi_master_config->SPI_Pin_MISO, NRF_GPIO_PIN_NOPULL);
    p_spi_instance->pin_slave_select = p_spi_master_config->SPI_Pin_SS;

    /* Configure SPI hardware */
    p_spi_instance->p_nrf_spi->PSELSCK  = p_spi_master_config->SPI_Pin_SCK;
    p_spi_instance->p_nrf_spi->PSELMOSI = p_spi_master_config->SPI_Pin_MOSI;
    p_spi_instance->p_nrf_spi->PSELMISO = p_spi_master_config->SPI_Pin_MISO;

    p_spi_instance->p_nrf_spi->FREQUENCY = p_spi_master_config->SPI_Freq;

    p_spi_instance->p_nrf_spi->CONFIG =
        (uint32_t)(p_spi_master_config->SPI_CPHA << SPI_CONFIG_CPHA_Pos) |
        (p_spi_master_config->SPI_CPOL << SPI_CONFIG_CPOL_Pos) |
        (p_spi_master_config->SPI_ORDER << SPI_CONFIG_ORDER_Pos);


    /* Clear waiting interrupts and events */
    p_spi_instance->p_nrf_spi->EVENTS_READY = 0;

    NVIC_ClearPendingIRQ(p_spi_instance->irq_type);
    NVIC_SetPriority(p_spi_instance->irq_type, APP_IRQ_PRIORITY_MID);

    /* Clear event handler */
    p_spi_instance->callback_event_handler = NULL;

    /* Enable interrupt */
    p_spi_instance->p_nrf_spi->INTENSET = (SPI_INTENSET_READY_Set << SPI_INTENCLR_READY_Pos);
    NVIC_EnableIRQ(p_spi_instance->irq_type);

    /* Enable SPI hardware */
    p_spi_instance->p_nrf_spi->ENABLE = (SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos);

    /* Change state to IDLE */
    p_spi_instance->state = SPI_MASTER_STATE_IDLE;

    return NRF_SUCCESS;
    #else
    return NRF_ERROR_NOT_SUPPORTED;
    #endif
}

/**
 * @brief Function for closing a SPI master driver.
 */
void spi_master_close(const spi_master_hw_instance_t spi_master_hw_instance)
{
    #if defined(SPI_MASTER_0_ENABLE) || defined(SPI_MASTER_1_ENABLE)
    spi_master_instance_t * p_spi_instance = spi_master_get_instance(spi_master_hw_instance);

    /* Disable interrupt */
    NVIC_ClearPendingIRQ(p_spi_instance->irq_type);
    NVIC_DisableIRQ(p_spi_instance->irq_type);

    p_spi_instance->p_nrf_spi->ENABLE = (SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos);

    /* Set Slave Select pin as input with pull-up. */
    nrf_gpio_pin_set(p_spi_instance->pin_slave_select);
    nrf_gpio_cfg_input(p_spi_instance->pin_slave_select, NRF_GPIO_PIN_PULLUP);
    p_spi_instance->pin_slave_select = (uint8_t)0xFF;

    /* Disconnect pins from SPI hardware */
    p_spi_instance->p_nrf_spi->PSELSCK  = (uint32_t)SPI_PIN_DISCONNECTED;
    p_spi_instance->p_nrf_spi->PSELMOSI = (uint32_t)SPI_PIN_DISCONNECTED;
    p_spi_instance->p_nrf_spi->PSELMISO = (uint32_t)SPI_PIN_DISCONNECTED;

    /* Reset to default values */
    spi_master_init_hw_instance(NULL, (IRQn_Type)0, p_spi_instance);
    #else
    return;
    #endif
}

/**
 * @brief Function for getting current state of the SPI master driver.
 */
__INLINE spi_master_state_t spi_master_get_state(
    const spi_master_hw_instance_t spi_master_hw_instance)
{
    #if defined(SPI_MASTER_0_ENABLE) || defined(SPI_MASTER_1_ENABLE)
    spi_master_instance_t * spi_instance = spi_master_get_instance(spi_master_hw_instance);
    return spi_instance->state;
    #else
    return SPI_MASTER_STATE_DISABLED;
    #endif
}

/**
 * @brief Function for event handler registration.
 */
__INLINE void spi_master_evt_handler_reg(const spi_master_hw_instance_t spi_master_hw_instance,
                                         spi_master_event_handler_t     event_handler)
{
    #if defined(SPI_MASTER_0_ENABLE) || defined(SPI_MASTER_1_ENABLE)
    spi_master_instance_t * spi_instance = spi_master_get_instance(spi_master_hw_instance);
    spi_instance->callback_event_handler = event_handler;
    #else
    return;
    #endif
}

/**
 * @brief Function for transmitting data between SPI master and SPI slave.
 */
uint32_t spi_master_send_recv(const spi_master_hw_instance_t spi_master_hw_instance,
                              uint8_t * const p_tx_buf, const uint16_t tx_buf_len,
                              uint8_t * const p_rx_buf, const uint16_t rx_buf_len)
{
    #if defined(SPI_MASTER_0_ENABLE) || defined(SPI_MASTER_1_ENABLE)
    spi_master_instance_t * p_spi_instance = spi_master_get_instance(spi_master_hw_instance);

    uint32_t err_code   = NRF_SUCCESS;
    uint16_t max_length = 0;

    if (p_spi_instance->state == SPI_MASTER_STATE_IDLE)
    {
        NVIC_DisableIRQ(p_spi_instance->irq_type);

        max_length = (rx_buf_len > tx_buf_len) ? rx_buf_len : tx_buf_len;

        if (max_length > 0)
        {
            p_spi_instance->state       = SPI_MASTER_STATE_BUSY;
            p_spi_instance->start_flag  = true; //abort_flag should set by abort and cleared only by restart
            p_spi_instance->bytes_count = 0;
            p_spi_instance->max_length  = max_length;
            spi_master_buffer_release(&(p_spi_instance->p_tx_buffer), &(p_spi_instance->tx_length));
            spi_master_buffer_release(&(p_spi_instance->p_rx_buffer), &(p_spi_instance->rx_length));
            /* Initialize buffers */
            spi_master_buffer_init(p_tx_buf, tx_buf_len, &(p_spi_instance->p_tx_buffer),
                                   &(p_spi_instance->tx_length), &(p_spi_instance->tx_index));
            spi_master_buffer_init(p_rx_buf, rx_buf_len, &(p_spi_instance->p_rx_buffer),
                                   &(p_spi_instance->rx_length), &(p_spi_instance->rx_index));
            nrf_gpio_pin_clear(p_spi_instance->pin_slave_select);
            spi_master_send_initial_bytes(p_spi_instance);
            spi_master_signal_evt(p_spi_instance, SPI_MASTER_EVT_TRANSFER_STARTED, max_length);
        }
        else
        {
            err_code = NRF_ERROR_INVALID_PARAM;
        }

        NVIC_EnableIRQ(p_spi_instance->irq_type);
    }
    else
    {
        err_code = NRF_ERROR_BUSY;
    }

    return err_code;
    #else
    return NRF_ERROR_NOT_SUPPORTED;
    #endif
}

#ifdef _SPI_5W_

/**
 * @brief Function for aborting transfer
 */
uint32_t spi_master_abort(const spi_master_hw_instance_t spi_master_hw_instance)
{
    spi_master_instance_t * p_spi_instance = spi_master_get_instance(spi_master_hw_instance);

    NVIC_DisableIRQ(p_spi_instance->irq_type);

    if (p_spi_instance->state == SPI_MASTER_STATE_BUSY)
    {
        //set_flag - but only when there are events pending
        //ignore when in IDLE - must be able to restart a completed transfer
        p_spi_instance->abort_flag = true;
    }
    NVIC_EnableIRQ(p_spi_instance->irq_type);
    return NRF_SUCCESS;
}

/**
 * @brief Function for restarting transfer
 */
uint32_t spi_master_restart(const spi_master_hw_instance_t spi_master_hw_instance)
{
    spi_master_instance_t * p_spi_instance = spi_master_get_instance(spi_master_hw_instance);

    NVIC_DisableIRQ(p_spi_instance->irq_type);
    spi_master_signal_evt(p_spi_instance, SPI_MASTER_EVT_TRANSFER_RESTARTED, 0);
    p_spi_instance->state       = SPI_MASTER_STATE_BUSY;
    p_spi_instance->bytes_count = 0;
    p_spi_instance->tx_index    = 0;
    p_spi_instance->rx_index    = 0;
    p_spi_instance->start_flag  = true;
    p_spi_instance->abort_flag  = false; //you should force clearing abort flag - no other way for 1 byte transfer
    nrf_gpio_pin_clear(p_spi_instance->pin_slave_select);
    spi_master_send_initial_bytes(p_spi_instance);
    NVIC_EnableIRQ(p_spi_instance->irq_type);

    return NRF_SUCCESS;
}

static void spi_5W_master_event_handler(spi_master_evt_t evt)
{

    switch (m_hook_state)
    {
        case HOOK_STATE_IDLE:

            if (evt.type == SPI_MASTER_EVT_TRANSFER_STARTED)
            {
                DEBUG_EVT_SPI_MASTER_RAW_XFER_GUARDED(0);
                m_hook_state = HOOK_STATE_GUARDED;
                m_ser_phy_event_handler(evt);
            }
            break;

        case HOOK_STATE_GUARDED:

            if (evt.type == SPI_MASTER_EVT_FIRST_BYTE_RECEIVED)
            {
                if (evt.data == 0)
                {
                    DEBUG_EVT_SPI_MASTER_RAW_XFER_PASSED(0);
                    m_hook_state = HOOK_STATE_PASSING;
                }
                else
                {
                    DEBUG_EVT_SPI_MASTER_RAW_XFER_ABORTED(0);
                    m_hook_state = HOOK_STATE_ABORTED;
                    (void)spi_master_abort(m_spi_master_hw_instance);
                }
            }
            break;

        case HOOK_STATE_ABORTED:

            if ((evt.type == SPI_MASTER_EVT_TRANSFER_ABORTED) ||
                (evt.type == SPI_MASTER_EVT_TRANSFER_COMPLETED))
            {
                DEBUG_EVT_SPI_MASTER_RAW_XFER_RESTARTED(0);
                m_hook_state = HOOK_STATE_RESTARTED;
                (void)spi_master_restart(m_spi_master_hw_instance);
            }
            break;

        case HOOK_STATE_RESTARTED:

            if (evt.type == SPI_MASTER_EVT_TRANSFER_RESTARTED)
            {
                DEBUG_EVT_SPI_MASTER_RAW_XFER_GUARDED(0);
                m_hook_state = HOOK_STATE_GUARDED;
            }
            break;

        case HOOK_STATE_PASSING:

            if (evt.type == SPI_MASTER_EVT_TRANSFER_COMPLETED)
            {
                m_hook_state = HOOK_STATE_IDLE;
                m_ser_phy_event_handler(evt); //this is the only way to get a signal from complete transaction
            }
            break;

        default:
            break;
    }
}

void spi_5W_master_evt_handler_reg(const spi_master_hw_instance_t spi_master_hw_instance,
                                   spi_master_event_handler_t     event_handler)
{
    m_ser_phy_event_handler  = event_handler;
    m_spi_master_hw_instance = spi_master_hw_instance;
    m_hook_state             = HOOK_STATE_IDLE;
    spi_master_evt_handler_reg(spi_master_hw_instance, spi_5W_master_event_handler);
    return;
}

#endif

/** @} */
