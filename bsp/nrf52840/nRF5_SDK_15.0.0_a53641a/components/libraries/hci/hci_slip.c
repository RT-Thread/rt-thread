/**
 * Copyright (c) 2013 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(HCI_SLIP)
#include "hci_slip.h"
#include <stdlib.h>
#include "app_uart.h"
#include "nrf_error.h"

#define APP_SLIP_END        0xC0                            /**< SLIP code for identifying the beginning and end of a packet frame.. */
#define APP_SLIP_ESC        0xDB                            /**< SLIP escape code. This code is used to specify that the following character is specially encoded. */
#define APP_SLIP_ESC_END    0xDC                            /**< SLIP special code. When this code follows 0xDB, this character is interpreted as payload data 0xC0.. */
#define APP_SLIP_ESC_ESC    0xDD                            /**< SLIP special code. When this code follows 0xDB, this character is interpreted as payload data 0xDB. */

/** @brief States for the SLIP state machine. */
typedef enum
{
    SLIP_OFF,                                               /**< SLIP state OFF. */
    SLIP_READY,                                             /**< SLIP state ON. */
    SLIP_TRANSMITTING,                                      /**< SLIP state is transmitting indicating write() has been called but data transmission has not completed. */
} slip_states_t;

static slip_states_t            m_current_state = SLIP_OFF; /** Current state for the SLIP TX state machine. */

static hci_slip_event_handler_t m_slip_event_handler;       /** Event callback function for handling of SLIP events, @ref hci_slip_evt_type_t . */

static const uint8_t *          mp_tx_buffer;               /** Pointer to the current TX buffer that is in transmission. */
static uint32_t                 m_tx_buffer_length;         /** Length of the current TX buffer that is in transmission. */
static volatile uint32_t        m_tx_buffer_index;          /** Current index for next byte to transmit in the mp_tx_buffer. */

static uint8_t *                mp_rx_buffer;               /** Pointer to the current RX buffer where the next SLIP decoded packet will be stored. */
static uint32_t                 m_rx_buffer_length;         /** Length of the current RX buffer. */
static uint32_t                 m_rx_received_count;        /** Number of SLIP decoded bytes received and stored in mp_rx_buffer. */


/**@brief Function for parsing bytes received on the UART until a SLIP escape byte is received.
 *
 * @param[in]  byte  Byte received in UART module.
 */
static void handle_rx_byte_default(uint8_t byte);

/**@brief Function for parsing bytes received on the UART until SLIP end byte is received.
 *
 * @param[in]  byte  Byte received in UART module.
 */
static void handle_rx_byte_wait_start(uint8_t byte);

/**@brief Function for decoding a received SLIP escape byte.
 *        It will ensure correct decoding of the byte following the SLIP escape byte.
 *
 * @param[in]  byte  Byte received in UART module.
 */
static void handle_rx_byte_esc(uint8_t byte);

/**@brief Function pointer for parsing and decoding SLIP bytes from the UART module.
 *
 * @param[in]  byte  Byte received in UART module.
 */
static void (*handle_rx_byte) (uint8_t byte) = handle_rx_byte_wait_start;

/**@brief Function pointer for sending a byte through the UART module.
 */
static uint32_t send_tx_byte_default(void);

/**@brief Function for transferring a SLIP escape byte (0xDB) when special bytes are transferred,
 *        that is 0xC0 and 0xDB.
 */
static uint32_t send_tx_byte_esc(void);

/**@brief Function for transferring a byte when it collides with SLIP commands and follows the SLIP
 *        escape byte, that is 0xC0 => 0xDC and 0xDB => 0xDD.
 */
static uint32_t send_tx_byte_encoded(void);

/**@brief Function for transferring the SLIP end frame byte, 0xC0.
 */
static uint32_t send_tx_byte_end(void);

/**@brief Function pointer for sending a byte through the UART module.
 */
uint32_t (*send_tx_byte) (void) = send_tx_byte_default;


static uint32_t send_tx_byte_end(void)
{
    uint32_t err_code = app_uart_put(APP_SLIP_END);

    if ((err_code == NRF_SUCCESS) && (m_tx_buffer_index == 0))
    {
        // Packet transmission started.
        send_tx_byte = send_tx_byte_default;
    }

    return err_code;
}


static uint32_t send_tx_byte_default(void)
{
    uint32_t err_code = app_uart_put(mp_tx_buffer[m_tx_buffer_index]);

    if (err_code == NRF_SUCCESS)
    {
        m_tx_buffer_index++;
    }

    return err_code;
}


static uint32_t send_tx_byte_encoded(void)
{
    uint32_t err_code;

    switch (mp_tx_buffer[m_tx_buffer_index])
    {
        case APP_SLIP_END:
            err_code = app_uart_put(APP_SLIP_ESC_END);
            break;

        case APP_SLIP_ESC:
            err_code = app_uart_put(APP_SLIP_ESC_ESC);
            break;

        default:
            err_code = NRF_ERROR_NO_MEM;
            break;
    }

    if (err_code == NRF_SUCCESS)
    {
        m_tx_buffer_index++;
        send_tx_byte = send_tx_byte_default;
    }

    return err_code;
}


static uint32_t send_tx_byte_esc(void)
{
    uint32_t err_code = app_uart_put(APP_SLIP_ESC);

    if (err_code == NRF_SUCCESS)
    {
        send_tx_byte = send_tx_byte_encoded;
    }

    return err_code;
}


/** @brief Function for transferring the content of the mp_tx_buffer to the UART.
 *         It continues to transfer bytes until the UART buffer is full or the complete buffer is
 *         transferred.
 */
static void transmit_buffer(void)
{
    uint32_t err_code = NRF_SUCCESS;

    while (m_tx_buffer_index < m_tx_buffer_length)
    {
        if ((mp_tx_buffer[m_tx_buffer_index] == APP_SLIP_END  ||
             mp_tx_buffer[m_tx_buffer_index] == APP_SLIP_ESC) &&
             send_tx_byte == send_tx_byte_default)
        {
            send_tx_byte = send_tx_byte_esc;
        }

        err_code = send_tx_byte();

        if (err_code == NRF_ERROR_NO_MEM || err_code == NRF_ERROR_BUSY)
        {
            // No memory left in UART TX buffer. Abort and wait for APP_UART_TX_EMPTY to continue.
            return;
        }
    }

    send_tx_byte = send_tx_byte_end;

    err_code = send_tx_byte();

    if (err_code == NRF_SUCCESS)
    {
        // Packet transmission ended. Notify higher level.
        m_current_state = SLIP_READY;

        if (m_slip_event_handler != NULL)
        {
            hci_slip_evt_t event = {HCI_SLIP_TX_DONE, mp_tx_buffer, m_tx_buffer_index};

            m_slip_event_handler(event);
        }
    }
}


/** @brief Function for handling the reception of a SLIP end byte.
 *         If the number of bytes received is greater than zero it will call m_slip_event_handler
 *         with number of bytes received and invalidate the mp_rx_buffer to protect against data
 *         corruption.
 *         No new bytes can be received until a new RX buffer is supplied.
 */
static void handle_slip_end(void)
{
    if (m_rx_received_count > 0)
    {
        // Full packet received, push it up.
        if (m_slip_event_handler != NULL)
        {
            hci_slip_evt_t event = {HCI_SLIP_RX_RDY, mp_rx_buffer, m_rx_received_count};

            m_rx_received_count  = 0;
            mp_rx_buffer         = NULL;

            m_slip_event_handler(event);
        }
    }
}


static void handle_rx_byte_esc(uint8_t byte)
{
    switch (byte)
    {
        case APP_SLIP_END:
            handle_slip_end();
            break;

        case APP_SLIP_ESC_END:
            mp_rx_buffer[m_rx_received_count++] = APP_SLIP_END;
            break;

        case APP_SLIP_ESC_ESC:
            mp_rx_buffer[m_rx_received_count++] = APP_SLIP_ESC;
            break;

        default:
            mp_rx_buffer[m_rx_received_count++] = byte;
            break;
    }

    handle_rx_byte = handle_rx_byte_default;
}


static void handle_rx_byte_default(uint8_t byte)
{
    switch (byte)
    {
        case APP_SLIP_END:
            handle_slip_end();
            break;

        case APP_SLIP_ESC:
            handle_rx_byte = handle_rx_byte_esc;
            break;

        default:
            mp_rx_buffer[m_rx_received_count++] = byte;
            break;
    }
}


static void handle_rx_byte_wait_start(uint8_t byte)
{
    if (byte == APP_SLIP_END)
    {
        handle_rx_byte = handle_rx_byte_default;
    }
}


/** @brief Function for checking the current index and length of the RX buffer to determine if the
 *         buffer is full. If an event handler has been registered, the callback function will
 *         be executed..
 *
 * @retval true     If RX buffer has overflowed.
 * @retval false    otherwise.
 *
 */
static bool rx_buffer_overflowed(void)
{
    if (mp_rx_buffer == NULL || m_rx_received_count >= m_rx_buffer_length)
    {
        if (m_slip_event_handler != NULL)
        {
            hci_slip_evt_t event = {HCI_SLIP_RX_OVERFLOW, mp_rx_buffer, m_rx_received_count};
            m_slip_event_handler(event);
        }

        return true;
    }

    return false;
}


/** @brief Function for handling the UART module event. It parses events from the UART when
 *         bytes are received/transmitted.
 *
 *  @param[in] uart_event   Event received from app_uart module.
 */
static void slip_uart_eventhandler(app_uart_evt_t * uart_event)
{
    if (uart_event->evt_type == APP_UART_TX_EMPTY && m_current_state == SLIP_TRANSMITTING)
    {
        transmit_buffer();
    }

    if ((uart_event->evt_type == APP_UART_DATA) && (!rx_buffer_overflowed()))
    {
        handle_rx_byte(uart_event->data.value);
    }
}


/** @brief Function for enabling the UART module when the SLIP layer is opened.
 */
static uint32_t slip_uart_open(void)
{
    uint32_t err_code;

    app_uart_comm_params_t comm_params =
    {
        HCI_UART_RX_PIN,
        HCI_UART_TX_PIN,
        HCI_UART_RTS_PIN,
        HCI_UART_CTS_PIN,
        (app_uart_flow_control_t)HCI_UART_FLOW_CONTROL,
        false,
        HCI_UART_BAUDRATE
    };

    err_code = app_uart_init(&comm_params,
                             NULL,
                             slip_uart_eventhandler,
                             APP_IRQ_PRIORITY_LOWEST);

    if (err_code == NRF_SUCCESS)
    {
        m_current_state = SLIP_READY;
    }

    return err_code;
}


uint32_t hci_slip_evt_handler_register(hci_slip_event_handler_t event_handler)
{
    m_slip_event_handler = event_handler;

    return NRF_SUCCESS;
}


uint32_t hci_slip_open()
{
    switch (m_current_state)
    {
        case SLIP_OFF:
            return slip_uart_open();

        default:
            // Do nothing.
            break;
    }

    return NRF_SUCCESS;
}


uint32_t hci_slip_close()
{
    m_current_state   = SLIP_OFF;
    uint32_t err_code = app_uart_close();

    return err_code;
}


uint32_t hci_slip_write(const uint8_t * p_buffer, uint32_t length)
{
    if (p_buffer == NULL)
    {
        return NRF_ERROR_INVALID_ADDR;
    }

    switch (m_current_state)
    {
        case SLIP_READY:
            m_tx_buffer_index  = 0;
            m_tx_buffer_length = length;
            mp_tx_buffer       = p_buffer;
            m_current_state    = SLIP_TRANSMITTING;
            send_tx_byte       = send_tx_byte_end;

            transmit_buffer();
            return NRF_SUCCESS;

        case SLIP_TRANSMITTING:
            return NRF_ERROR_NO_MEM;

        case SLIP_OFF:
        default:
            return NRF_ERROR_INVALID_STATE;
    }
}


uint32_t hci_slip_rx_buffer_register(uint8_t * p_buffer, uint32_t length)
{
    mp_rx_buffer        = p_buffer;
    m_rx_buffer_length  = length;
    m_rx_received_count = 0;
    handle_rx_byte      = handle_rx_byte_wait_start;
    return NRF_SUCCESS;
}
#endif //NRF_MODULE_ENABLED(HCI_SLIP)
