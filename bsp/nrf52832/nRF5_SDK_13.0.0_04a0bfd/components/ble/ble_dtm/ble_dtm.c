/**
 * Copyright (c) 2012 - 2017, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(BLE_DTM)
#include "ble_dtm.h"
#include "ble_dtm_hw.h"
#include <stdbool.h>
#include <string.h>
#include "nrf.h"

#define DTM_HEADER_OFFSET        0                                         /**< Index where the header of the pdu is located. */
#define DTM_HEADER_SIZE          2                                         /**< Size of PDU header. */
#define DTM_PAYLOAD_MAX_SIZE     255                                       /**< Maximum payload size allowed during dtm execution. */
#define DTM_LENGTH_OFFSET        (DTM_HEADER_OFFSET + 1)                   /**< Index where the length of the payload is encoded. */
#define DTM_PDU_MAX_MEMORY_SIZE  (DTM_HEADER_SIZE + DTM_PAYLOAD_MAX_SIZE)  /**< Maximum PDU size allowed during dtm execution. */
#define DTM_ON_AIR_OVERHEAD_SIZE 10                                        /**< Size of the packet on air without the payload (preamble + sync word + type + RFU + length + CRC). */

#define RX_MODE          true   /**< Constant defining RX mode for radio during dtm test. */
#define TX_MODE          false  /**< Constant defining TX mode for radio during dtm test. */

#define PHYS_CH_MAX      39     /**< Maximum number of valid channels in BLE. */

// Values that for now are "constants" - they could be configured by a function setting them,
// but most of these are set by the BLE DTM standard, so changing them is not relevant.
#define RFPHY_TEST_0X0F_REF_PATTERN  0x0f  /**<  RF-PHY test packet patterns, for the repeated octet packets. */
#define RFPHY_TEST_0X55_REF_PATTERN  0x55  /**<  RF-PHY test packet patterns, for the repeated octet packets. */

#define PRBS9_CONTENT  {0xFF, 0xC1, 0xFB, 0xE8, 0x4C, 0x90, 0x72, 0x8B,   \
                        0xE7, 0xB3, 0x51, 0x89, 0x63, 0xAB, 0x23, 0x23,   \
                        0x02, 0x84, 0x18, 0x72, 0xAA, 0x61, 0x2F, 0x3B,   \
                        0x51, 0xA8, 0xE5, 0x37, 0x49, 0xFB, 0xC9, 0xCA,   \
                        0x0C, 0x18, 0x53, 0x2C, 0xFD, 0x45, 0xE3, 0x9A,   \
                        0xE6, 0xF1, 0x5D, 0xB0, 0xB6, 0x1B, 0xB4, 0xBE,   \
                        0x2A, 0x50, 0xEA, 0xE9, 0x0E, 0x9C, 0x4B, 0x5E,   \
                        0x57, 0x24, 0xCC, 0xA1, 0xB7, 0x59, 0xB8, 0x87,   \
                        0xFF, 0xE0, 0x7D, 0x74, 0x26, 0x48, 0xB9, 0xC5,   \
                        0xF3, 0xD9, 0xA8, 0xC4, 0xB1, 0xD5, 0x91, 0x11,   \
                        0x01, 0x42, 0x0C, 0x39, 0xD5, 0xB0, 0x97, 0x9D,   \
                        0x28, 0xD4, 0xF2, 0x9B, 0xA4, 0xFD, 0x64, 0x65,   \
                        0x06, 0x8C, 0x29, 0x96, 0xFE, 0xA2, 0x71, 0x4D,   \
                        0xF3, 0xF8, 0x2E, 0x58, 0xDB, 0x0D, 0x5A, 0x5F,   \
                        0x15, 0x28, 0xF5, 0x74, 0x07, 0xCE, 0x25, 0xAF,   \
                        0x2B, 0x12, 0xE6, 0xD0, 0xDB, 0x2C, 0xDC, 0xC3,   \
                        0x7F, 0xF0, 0x3E, 0x3A, 0x13, 0xA4, 0xDC, 0xE2,   \
                        0xF9, 0x6C, 0x54, 0xE2, 0xD8, 0xEA, 0xC8, 0x88,   \
                        0x00, 0x21, 0x86, 0x9C, 0x6A, 0xD8, 0xCB, 0x4E,   \
                        0x14, 0x6A, 0xF9, 0x4D, 0xD2, 0x7E, 0xB2, 0x32,   \
                        0x03, 0xC6, 0x14, 0x4B, 0x7F, 0xD1, 0xB8, 0xA6,   \
                        0x79, 0x7C, 0x17, 0xAC, 0xED, 0x06, 0xAD, 0xAF,   \
                        0x0A, 0x94, 0x7A, 0xBA, 0x03, 0xE7, 0x92, 0xD7,   \
                        0x15, 0x09, 0x73, 0xE8, 0x6D, 0x16, 0xEE, 0xE1,   \
                        0x3F, 0x78, 0x1F, 0x9D, 0x09, 0x52, 0x6E, 0xF1,   \
                        0x7C, 0x36, 0x2A, 0x71, 0x6C, 0x75, 0x64, 0x44,   \
                        0x80, 0x10, 0x43, 0x4E, 0x35, 0xEC, 0x65, 0x27,   \
                        0x0A, 0xB5, 0xFC, 0x26, 0x69, 0x3F, 0x59, 0x99,   \
                        0x01, 0x63, 0x8A, 0xA5, 0xBF, 0x68, 0x5C, 0xD3,   \
                        0x3C, 0xBE, 0x0B, 0xD6, 0x76, 0x83, 0xD6, 0x57,   \
                        0x05, 0x4A, 0x3D, 0xDD, 0x81, 0x73, 0xC9, 0xEB,   \
                        0x8A, 0x84, 0x39, 0xF4, 0x36, 0x0B, 0xF7}           /**< The PRBS9 sequence used as packet payload.
                                                                                 The bytes in the sequence is in the right order, but the bits of each byte in the array is reverse.
                                                                                 of that found by running the PRBS9 algorithm. This is because of the endianess of the nRF5 radio. */

/**@brief Structure holding the PDU used for transmitting/receiving a PDU.
 */
typedef struct
{
    uint8_t content[DTM_HEADER_SIZE + DTM_PAYLOAD_MAX_SIZE];                 /**< PDU packet content. */
} pdu_type_t;

/**@brief States used for the DTM test implementation.
 */
typedef enum
{
    STATE_UNINITIALIZED,                                                     /**< The DTM is uninitialized. */
    STATE_IDLE,                                                              /**< State when system has just initialized, or current test has completed. */
    STATE_TRANSMITTER_TEST,                                                  /**< State used when a DTM Transmission test is running. */
    STATE_CARRIER_TEST,                                                      /**< State used when a DTM Carrier test is running (Vendor specific test). */
    STATE_RECEIVER_TEST                                                      /**< State used when a DTM Receive test is running. */
} state_t;

// Internal variables set as side effects of commands or events.
static state_t           m_state = STATE_UNINITIALIZED;                      /**< Current machine state. */
static uint16_t          m_rx_pkt_count;                                     /**< Number of valid packets received. */
static pdu_type_t        m_pdu;                                              /**< PDU to be sent. */
static uint16_t          m_event;                                            /**< current command status - initially "ok", may be set if error detected, or to packet count. */
static bool              m_new_event;                                        /**< Command has been processed - number of not yet reported event bytes. */
static uint32_t          m_packet_length;                                    /**< Payload length of transmitted PDU, bits 2:7 of 16-bit dtm command. */
static dtm_pkt_type_t    m_packet_type;                                      /**< Bits 0..1 of 16-bit transmit command, or 0xFFFFFFFF. */
static dtm_freq_t        m_phys_ch;                                          /**< 0..39 physical channel number (base 2402 MHz, Interval 2 MHz), bits 8:13 of 16-bit dtm command. */
static uint32_t          m_current_time = 0;                                 /**< Counter for interrupts from timer to ensure that the 2 bytes forming a DTM command are received within the time window. */

// Nordic specific configuration values (not defined by BLE standard).
// Definition of initial values found in ble_dtm.h
static int32_t           m_tx_power          = DEFAULT_TX_POWER;             /**< TX power for transmission test, default to maximum value (+4 dBm). */
static NRF_TIMER_Type *  mp_timer            = DEFAULT_TIMER;                /**< Timer to be used. */
static IRQn_Type         m_timer_irq         = DEFAULT_TIMER_IRQn;           /**< which interrupt line to clear on every timeout */

static uint8_t const     m_prbs_content[]    = PRBS9_CONTENT;                /**< Pseudo-random bit sequence defined by the BLE standard. */
static uint8_t           m_packetHeaderLFlen = 8;                            /**< Length of length field in packet Header (in bits). */
static uint8_t           m_packetHeaderS0len = 1;                            /**< Length of S0 field in packet Header (in bytes). */
static uint8_t           m_packetHeaderS1len = 0;                            /**< Length of S1 field in packet Header (in bits). */
static uint8_t           m_crcConfSkipAddr   = 1;                            /**< Leave packet address field out of CRC calculation. */
static uint8_t           m_static_length     = 0;                            /**< Number of bytes sent in addition to the var.length payload. */
static uint32_t          m_balen             = 3;                            /**< Base address length in bytes. */
static uint32_t          m_endian            = RADIO_PCNF1_ENDIAN_Little;    /**< On air endianess of packet, this applies to the S0, LENGTH, S1 and the PAYLOAD fields. */
static uint32_t          m_whitening         = RADIO_PCNF1_WHITEEN_Disabled; /**< Whitening disabled. */
static uint8_t           m_crcLength         = RADIO_CRCCNF_LEN_Three;       /**< CRC Length (in bytes). */
static uint32_t          m_address           = 0x71764129;                   /**< Address. */
static uint32_t          m_crc_poly          = 0x0000065B;                   /**< CRC polynomial. */
static uint32_t          m_crc_init          = 0x00555555;                   /**< Initial value for CRC calculation. */
static uint8_t           m_radio_mode        = RADIO_MODE_MODE_Ble_1Mbit;    /**< nRF51 specific radio mode value. */
static uint32_t          m_txIntervaluS      = 2500;                          /**< Time between start of Tx packets (in uS). */


/**@brief Function for verifying that a received PDU has the expected structure and content.
 */
static bool check_pdu(void)
{
    uint8_t        k;                // Byte pointer for running through PDU payload
    uint8_t        pattern;          // Repeating octet value in payload
    dtm_pkt_type_t pdu_packet_type;  // Note: PDU packet type is a 4-bit field in HCI, but 2 bits in BLE DTM
    uint32_t       length = 0;

    pdu_packet_type = (dtm_pkt_type_t)(m_pdu.content[DTM_HEADER_OFFSET] & 0x0F);
    length          = m_pdu.content[DTM_LENGTH_OFFSET];

    if ((pdu_packet_type > (dtm_pkt_type_t)PACKET_TYPE_MAX) || (length > DTM_PAYLOAD_MAX_SIZE))
    {
        return false;
    }

    if (pdu_packet_type == DTM_PKT_PRBS9)
    {
        // Payload does not consist of one repeated octet; must compare ir with entire block into
        return (memcmp(m_pdu.content + DTM_HEADER_SIZE, m_prbs_content, length) == 0);
    }

    if (pdu_packet_type == DTM_PKT_0X0F)
    {
        pattern = RFPHY_TEST_0X0F_REF_PATTERN;
    }
    else
    {
        pattern = RFPHY_TEST_0X55_REF_PATTERN;
    }

    for (k = 0; k < length; k++)
    {
        // Check repeated pattern filling the PDU payload
        if (m_pdu.content[k + 2] != pattern)
        {
            return false;
        }
    }
    return true;
}


/**@brief Function for turning off the radio after a test.
 *        Also called after test done, to be ready for next test.
 */
static void radio_reset(void)
{
    NRF_PPI->CHENCLR = PPI_CHENCLR_CH0_Msk | PPI_CHENCLR_CH1_Msk;

    NRF_RADIO->SHORTS          = 0;
    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->TASKS_DISABLE   = 1;

    while (NRF_RADIO->EVENTS_DISABLED == 0)
    {
        // Do nothing
    }

    NRF_RADIO->EVENTS_DISABLED = 0;
    NRF_RADIO->TASKS_RXEN      = 0;
    NRF_RADIO->TASKS_TXEN      = 0;

    m_rx_pkt_count = 0;
}


/**@brief Function for initializing the radio for DTM.
 */
static uint32_t radio_init(void)
{
    if(dtm_radio_validate(m_tx_power, m_radio_mode) != DTM_SUCCESS)
    {
        return DTM_ERROR_ILLEGAL_CONFIGURATION;
    }

    // Turn off radio before configuring it
    radio_reset();

    NRF_RADIO->TXPOWER = m_tx_power;
    NRF_RADIO->MODE    = m_radio_mode << RADIO_MODE_MODE_Pos;

    // Set the access address, address0/prefix0 used for both Rx and Tx address
    NRF_RADIO->PREFIX0    &= ~RADIO_PREFIX0_AP0_Msk;
    NRF_RADIO->PREFIX0    |= (m_address >> 24) & RADIO_PREFIX0_AP0_Msk;
    NRF_RADIO->BASE0       = m_address << 8;
    NRF_RADIO->RXADDRESSES = RADIO_RXADDRESSES_ADDR0_Enabled << RADIO_RXADDRESSES_ADDR0_Pos;
    NRF_RADIO->TXADDRESS   = (0x00 << RADIO_TXADDRESS_TXADDRESS_Pos) & RADIO_TXADDRESS_TXADDRESS_Msk;

    // Configure CRC calculation
    NRF_RADIO->CRCCNF = (m_crcConfSkipAddr << RADIO_CRCCNF_SKIP_ADDR_Pos) |
                        (m_crcLength << RADIO_CRCCNF_LEN_Pos);

    NRF_RADIO->PCNF0 = (m_packetHeaderS1len << RADIO_PCNF0_S1LEN_Pos) |
                       (m_packetHeaderS0len << RADIO_PCNF0_S0LEN_Pos) |
                       (m_packetHeaderLFlen << RADIO_PCNF0_LFLEN_Pos);

    NRF_RADIO->PCNF1 = (m_whitening          << RADIO_PCNF1_WHITEEN_Pos) |
                       (m_endian             << RADIO_PCNF1_ENDIAN_Pos)  |
                       (m_balen              << RADIO_PCNF1_BALEN_Pos)   |
                       (m_static_length      << RADIO_PCNF1_STATLEN_Pos) |
                       (DTM_PAYLOAD_MAX_SIZE << RADIO_PCNF1_MAXLEN_Pos);

    return DTM_SUCCESS;
}


/**@brief Function for preparing the radio. At start of each test: Turn off RF, clear interrupt flags of RF, initialize the radio
 *        at given RF channel.
 *
 *@param[in] rx     boolean indicating if radio should be prepared in rx mode (true) or tx mode.
 */
static void radio_prepare(bool rx)
{
    dtm_turn_off_test();
    NRF_RADIO->CRCPOLY      = m_crc_poly;
    NRF_RADIO->CRCINIT      = m_crc_init;
    NRF_RADIO->FREQUENCY    = (m_phys_ch << 1) + 2;                  // Actual frequency (MHz): 2400 + register value
    NRF_RADIO->PACKETPTR    = (uint32_t)&m_pdu;                      // Setting packet pointer will start the radio
    NRF_RADIO->EVENTS_READY = 0;
    NRF_RADIO->SHORTS       = (1 << RADIO_SHORTS_READY_START_Pos) |  // Shortcut between READY event and START task
                              (1 << RADIO_SHORTS_END_DISABLE_Pos);   // Shortcut between END event and DISABLE task

    if (rx)
    {
        NRF_RADIO->EVENTS_END = 0;
        NRF_RADIO->TASKS_RXEN = 1;  // shorts will start radio in RX mode when it is ready
    }
    else // tx
    {
        NRF_RADIO->TXPOWER = m_tx_power;
    }
}


/**@brief Function for terminating the ongoing test (if any) and closing down the radio.
 */
static void dtm_test_done(void)
{
    dtm_turn_off_test();
    NRF_PPI->CHENCLR = 0x01;
    NRF_PPI->CH[0].EEP = 0;     // Break connection from timer to radio to stop transmit loop
    NRF_PPI->CH[0].TEP = 0;

    radio_reset();
    m_state = STATE_IDLE;
}


/**@brief Function for configuring the timer for 625us cycle time.
 */
static uint32_t timer_init(void)
{
    // Use 16MHz from external crystal
    // This could be customized for RC/Xtal, or even to use a 32 kHz crystal
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_HFCLKSTART    = 1;

    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0)
    {
        // Do nothing while waiting for the clock to start
    }

    mp_timer->TASKS_STOP        = 1;                      // Stop timer, if it was running
    mp_timer->TASKS_CLEAR       = 1;
    mp_timer->MODE              = TIMER_MODE_MODE_Timer;  // Timer mode (not counter)
    mp_timer->EVENTS_COMPARE[0] = 0;                      // clean up possible old events
    mp_timer->EVENTS_COMPARE[1] = 0;
    mp_timer->EVENTS_COMPARE[2] = 0;
    mp_timer->EVENTS_COMPARE[3] = 0;

    // Timer is polled, but enable the compare0 interrupt in order to wakeup from CPU sleep
    mp_timer->INTENSET    = TIMER_INTENSET_COMPARE0_Msk;
    mp_timer->SHORTS      = 1 << TIMER_SHORTS_COMPARE0_CLEAR_Pos;  // Clear the count every time timer reaches the CCREG0 count
    mp_timer->PRESCALER   = 4;                                     // Input clock is 16MHz, timer clock = 2 ^ prescale -> interval 1us
    mp_timer->CC[0]       = m_txIntervaluS;                        // 625uS with 1MHz clock to the timer
    mp_timer->CC[1]       = UART_POLL_CYCLE;                       // Depends on the baud rate of the UART. Default baud rate of 19200 will result in a 260uS time with 1MHz clock to the timer
    mp_timer->TASKS_START = 1;                                     // Start the timer - it will be running continuously
    m_current_time        = 0;
    return DTM_SUCCESS;
}


/**@brief Function for handling vendor specific commands.
 *        Used when packet type is set to Vendor specific.
 *        The length field is used for encoding vendor specific command.
 *        The frequency field is used for encoding vendor specific options to the command.
 *
 * @param[in]   vendor_cmd      Vendor specific command to be executed.
 * @param[in]   vendor_option   Vendor specific option to the vendor command.
 *
 * @return      DTM_SUCCESS or one of the DTM_ERROR_ values
 */
static uint32_t dtm_vendor_specific_pkt(uint32_t vendor_cmd, dtm_freq_t vendor_option)
{
    switch (vendor_cmd)
    {
        // nRFgo Studio uses CARRIER_TEST_STUDIO to indicate a continuous carrier without
        // a modulated signal.
        case CARRIER_TEST:
        case CARRIER_TEST_STUDIO:
            // Not a packet type, but used to indicate that a continuous carrier signal
            // should be transmitted by the radio.
            radio_prepare(TX_MODE);

            dtm_constant_carrier();

            // Shortcut between READY event and START task
            NRF_RADIO->SHORTS = 1 << RADIO_SHORTS_READY_START_Pos;

            // Shortcut will start radio in Tx mode when it is ready
            NRF_RADIO->TASKS_TXEN = 1;
            m_state               = STATE_CARRIER_TEST;
            break;

        case SET_TX_POWER:
            if (!dtm_set_txpower(vendor_option))
            {
                return DTM_ERROR_ILLEGAL_CONFIGURATION;
            }
            break;

        case SELECT_TIMER:
            if (!dtm_set_timer(vendor_option))
            {
                return DTM_ERROR_ILLEGAL_CONFIGURATION;
            }
            break;
    }
    // Event code is unchanged, successful
    return DTM_SUCCESS;
}


uint32_t dtm_init(void)
{
    if ((timer_init() != DTM_SUCCESS) || (radio_init() != DTM_SUCCESS))
    {
        return DTM_ERROR_ILLEGAL_CONFIGURATION;
    }
    m_new_event     = false;
    m_state         = STATE_IDLE;
    m_packet_length = 0;

    // Enable wake-up on event
    SCB->SCR |= SCB_SCR_SEVONPEND_Msk;

    return DTM_SUCCESS;
}


uint32_t dtm_wait(void)
{
    // Enable wake-up on event
    SCB->SCR |= SCB_SCR_SEVONPEND_Msk;

    for (;;)
    {
        // Event may be the reception of a packet -
        // handle radio first, to give it highest priority:
        if (NRF_RADIO->EVENTS_END != 0)
        {
            NRF_RADIO->EVENTS_END = 0;
            NVIC_ClearPendingIRQ(RADIO_IRQn);

            if (m_state == STATE_RECEIVER_TEST)
            {
                NRF_RADIO->TASKS_RXEN = 1;
                if ((NRF_RADIO->CRCSTATUS == 1) && check_pdu())
                {
                    // Count the number of successfully received packets
                    m_rx_pkt_count++;
                }
                // Note that failing packets are simply ignored (CRC or contents error).

                // Zero fill all pdu fields to avoid stray data
                memset(&m_pdu, 0, DTM_PDU_MAX_MEMORY_SIZE);
            }
            // If no RECEIVER_TEST is running, ignore incoming packets (but do clear IRQ!)
        }

        // Check for timeouts:
        if (mp_timer->EVENTS_COMPARE[0] != 0)
        {
            mp_timer->EVENTS_COMPARE[0] = 0;
        }
        else if (mp_timer->EVENTS_COMPARE[1] != 0)
        {
            // Reset timeout event flag for next iteration.
            mp_timer->EVENTS_COMPARE[1] = 0;
            NVIC_ClearPendingIRQ(m_timer_irq);
            return ++m_current_time;
        }

        // Other events: No processing
    }
}


uint32_t dtm_cmd(dtm_cmd_t cmd, dtm_freq_t freq, uint32_t length, dtm_pkt_type_t payload)
{
    // Save specified packet in static variable for tx/rx functions to use.
    // Note that BLE conformance testers always use full length packets.
    m_packet_length = (m_packet_length & 0xC0) | ((uint8_t)length & 0x3F);
    m_packet_type   = payload;
    m_phys_ch       = freq;

    // Clean out any non-retrieved event that might linger from an earlier test
    m_new_event     = true;

    // Set default event; any error will set it to LE_TEST_STATUS_EVENT_ERROR
    m_event         = LE_TEST_STATUS_EVENT_SUCCESS;

    if (m_state == STATE_UNINITIALIZED)
    {
        // Application has not explicitly initialized DTM,
        return DTM_ERROR_UNINITIALIZED;
    }

    if (cmd == LE_RESET)
    {
        // Note that timer will continue running after a reset
        dtm_test_done();
        if (freq == 0x01)
        {
            m_packet_length = length << 6;
        }
        else
        {
            m_packet_length = 0;
        }
        return DTM_SUCCESS;
    }

    if (cmd == LE_TEST_END)
    {
        if (m_state == STATE_IDLE)
        {
            // Sequencing error - only rx or tx test may be ended!
            m_event = LE_TEST_STATUS_EVENT_ERROR;
            return DTM_ERROR_INVALID_STATE;
        }
        m_event = LE_PACKET_REPORTING_EVENT | m_rx_pkt_count;
        dtm_test_done();
        return DTM_SUCCESS;
    }

    if (m_state != STATE_IDLE)
    {
        // Sequencing error - only TEST_END/RESET are legal while test is running
        // Note: State is unchanged; ongoing test not affected
        m_event = LE_TEST_STATUS_EVENT_ERROR;
        return DTM_ERROR_INVALID_STATE;
    }

    // Check for illegal values of m_phys_ch. Skip the check if the packet is vendor spesific.
    if (payload != DTM_PKT_VENDORSPECIFIC && m_phys_ch > PHYS_CH_MAX)
    {
        // Parameter error
        // Note: State is unchanged; ongoing test not affected
        m_event = LE_TEST_STATUS_EVENT_ERROR;
        return DTM_ERROR_ILLEGAL_CHANNEL;
    }

    m_rx_pkt_count = 0;

    if (cmd == LE_RECEIVER_TEST)
    {
        // Zero fill all pdu fields to avoid stray data from earlier test run
        memset(&m_pdu, 0, DTM_PDU_MAX_MEMORY_SIZE);
        radio_prepare(RX_MODE);                      // Reinitialize "everything"; RF interrupts OFF
        m_state = STATE_RECEIVER_TEST;
        return DTM_SUCCESS;
    }

    if (cmd == LE_TRANSMITTER_TEST)
    {
        // Check for illegal values of m_packet_length. Skip the check if the packet is vendor spesific.
        if (payload != DTM_PKT_VENDORSPECIFIC && m_packet_length > DTM_PAYLOAD_MAX_SIZE)
        {
            // Parameter error
            m_event = LE_TEST_STATUS_EVENT_ERROR;
            return DTM_ERROR_ILLEGAL_LENGTH;
        }

        // Note that PDU uses 4 bits even though BLE DTM uses only 2 (the HCI SDU uses all 4)
        m_pdu.content[DTM_HEADER_OFFSET] = ((uint8_t)m_packet_type & 0x0F);
        m_pdu.content[DTM_LENGTH_OFFSET] = m_packet_length;

        switch (m_packet_type)
        {
            case DTM_PKT_PRBS9:
                // Non-repeated, must copy entire pattern to PDU
                memcpy(m_pdu.content + DTM_HEADER_SIZE, m_prbs_content, m_packet_length);
                break;

            case DTM_PKT_0X0F:
                // Bit pattern 00001111 repeated
                memset(m_pdu.content + DTM_HEADER_SIZE, RFPHY_TEST_0X0F_REF_PATTERN, m_packet_length);
                break;

            case DTM_PKT_0X55:
                // Bit pattern 01010101 repeated
                memset(m_pdu.content + DTM_HEADER_SIZE, RFPHY_TEST_0X55_REF_PATTERN, m_packet_length);
                break;

            case DTM_PKT_VENDORSPECIFIC:
                // The length field is for indicating the vendor specific command to execute.
                // The frequency field is used for vendor specific options to the command.
                return dtm_vendor_specific_pkt(length, freq);

            default:
                // Parameter error
                m_event = LE_TEST_STATUS_EVENT_ERROR;
                return DTM_ERROR_ILLEGAL_CONFIGURATION;
        }

        // Initialize CRC value, set channel:
        radio_prepare(TX_MODE);
        // Set the timer to the correct period. The delay between each packet is described in the
        // Bluetooth Core Spsification version 4.2 Vol. 6 Part F Section 4.1.6.
        if ((m_packet_length + DTM_ON_AIR_OVERHEAD_SIZE ) * 8  <= 376)
        {
            mp_timer->CC[0]       = 625;                        // 625uS with 1MHz clock to the timer
        }
        else if ((m_packet_length + DTM_ON_AIR_OVERHEAD_SIZE ) * 8  <= 1000)
        {
            mp_timer->CC[0]       = 1250;                        // 625uS with 1MHz clock to the timer
        }
        else if ((m_packet_length + DTM_ON_AIR_OVERHEAD_SIZE ) * 8  <= 1624)
        {
            mp_timer->CC[0]       = 1875;                        // 625uS with 1MHz clock to the timer
        }
        else
        {
            mp_timer->CC[0]       = 2500;                        // 625uS with 1MHz clock to the timer
        }

        // Configure PPI so that timer will activate radio every 625 us
        NRF_PPI->CH[0].EEP = (uint32_t)&mp_timer->EVENTS_COMPARE[0];
        NRF_PPI->CH[0].TEP = (uint32_t)&NRF_RADIO->TASKS_TXEN;
        NRF_PPI->CHENSET   = 0x01;
        m_state            = STATE_TRANSMITTER_TEST;
    }
    return DTM_SUCCESS;
}


bool dtm_event_get(dtm_event_t *p_dtm_event)
{
    bool was_new = m_new_event;
    // mark the current event as retrieved
    m_new_event  = false;
    *p_dtm_event = m_event;
    // return value indicates whether this value was already retrieved.
    return was_new;
}


// =================================================================================================
// Configuration functions (only for parameters not definitely determined by the BLE DTM standard).
// These functions return true if successful, false if value could not be set


/**@brief Function for configuring the output power for transmitter test.
          This function may be called directly, or through dtm_cmd() specifying
          DTM_PKT_VENDORSPECIFIC as payload, SET_TX_POWER as length, and the dBm value as frequency.
 */
bool dtm_set_txpower(uint32_t new_tx_power)
{
    // radio->TXPOWER register is 32 bits, low octet a signed value, upper 24 bits zeroed
    int8_t new_power8 = (int8_t)(new_tx_power & 0xFF);

    // The two most significant bits are not sent in the 6 bit field of the DTM command.
    // These two bits are 1's if and only if the tx_power is a negative number.
    // All valid negative values have the fourth most significant bit as 1.
    // All valid positive values have the fourth most significant bit as 0.
    // By checking this bit, the two most significant bits can be determined.
    new_power8 = (new_power8 & 0x30) != 0 ? (new_power8 | 0xC0) : new_power8;

    if (m_state > STATE_IDLE)
    {
        // radio must be idle to change the tx power
        return false;
    }

    m_tx_power = new_power8;

    return true;
}


/**@brief Function for selecting a timer resource.
 *        This function may be called directly, or through dtm_cmd() specifying
 *        DTM_PKT_VENDORSPECIFIC as payload, SELECT_TIMER as length, and the timer as freq
 *
 * @param[in] new_timer     Timer id for the timer to use: 0, 1, or 2.
 *
 * @return true if the timer was successfully changed, false otherwise.
 */
bool dtm_set_timer(uint32_t new_timer)
{
    if (m_state > STATE_IDLE)
    {
        return false;
    }
    return dtm_hw_set_timer(&mp_timer, &m_timer_irq, new_timer);
}

/// @}
#endif // NRF_MODULE_ENABLED(BLE_DTM)
