/**
 * Copyright (c) 2012 - 2018, Nordic Semiconductor ASA
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
/** @file
 *
 * @defgroup ble_dtm DTM - Direct Test Mode
 * @{
 * @ingroup ble_sdk_lib
 * @brief Module for testing RF/PHY using DTM commands.
 */

#ifndef BLE_DTM_H__
#define BLE_DTM_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Configuration parameters. */
#define DTM_BITRATE                     UARTE_BAUDRATE_BAUDRATE_Baud19200   /**< Serial bitrate on the UART */
#define DEFAULT_TX_POWER                RADIO_TXPOWER_TXPOWER_0dBm          /**< Default Transmission power using in the DTM module. */
#define DEFAULT_TIMER                   NRF_TIMER0                          /**< Default timer used for timing. */
#define DEFAULT_TIMER_IRQn              TIMER0_IRQn                         /**< IRQ used for timer. NOTE: MUST correspond to DEFAULT_TIMER. */

/**@brief BLE DTM command codes. */
typedef uint32_t dtm_cmd_t;                                                 /**< DTM command type. */

#define LE_TEST_SETUP                   0                                   /**< DTM command: Set PHY or modulation, configure upper two bits of length,
                                                                             request matrix of supported features or request max values of parameters. */
#define LE_RECEIVER_TEST                1                                   /**< DTM command: Start receive test. */
#define LE_TRANSMITTER_TEST             2                                   /**< DTM command: Start transmission test. */
#define LE_TEST_END                     3                                   /**< DTM command: End test and send packet report. */

#define LE_TEST_SETUP_RESET             0                                   /**< DTM command parameter: Stop TX/RX, reset the packet length upper bits and set the PHY to 1Mbit. */
#define LE_TEST_SETUP_SET_UPPER         1                                   /**< DTM command parameter: Set the upper two bits of the length field. */
#define LE_TEST_SETUP_SET_PHY           2                                   /**< DTM command parameter: Select the PHY to be used for packets. */
#define LE_TEST_SETUP_SELECT_MODULATION 3                                   /**< DTM command parameter: Select standard or stable modulation index. Stable modulation index is not supported. */
#define LE_TEST_SETUP_READ_SUPPORTED    4                                   /**< DTM command parameter: Read the supported test case features. */
#define LE_TEST_SETUP_READ_MAX          5                                   /**< DTM command parameter: Read the max supported time and length for packets. */

#define LE_PHY_1M                       1                                   /**< DTM command parameter: Set PHY for future packets to use 1MBit PHY. */
#define LE_PHY_2M                       2                                   /**< DTM command parameter: Set PHY for future packets to use 2MBit PHY. */
#define LE_PHY_LE_CODED_S8              3                                   /**< DTM command parameter: Set PHY for future packets to use coded PHY with S=8. */
#define LE_PHY_LE_CODED_S2              4                                   /**< DTM command parameter: Set PHY for future packets to use coded PHY with S=2 */

// Configuration options used as parameter 2
// when cmd == LE_TRANSMITTER_TEST and payload == DTM_PKT_VENDORSPECIFIC
// Configuration value, if any, is supplied in parameter 3

#define CARRIER_TEST                    0                                   /**< Length=0 indicates a constant, unmodulated carrier until LE_TEST_END or LE_RESET */
#define CARRIER_TEST_STUDIO             1                                   /**< nRFgo Studio uses value 1 in length field, to indicate a constant, unmodulated carrier until LE_TEST_END or LE_RESET */
#define SET_TX_POWER                    2                                   /**< Set transmission power, value -40..+4 dBm in steps of 4 */
#define SELECT_TIMER                    3                                   /**< Select on of the 16 MHz timers 0, 1 or 2 */

#define LE_PACKET_REPORTING_EVENT       0x8000                              /**< DTM Packet reporting event, returned by the device to the tester. */
#define LE_TEST_STATUS_EVENT_SUCCESS    0x0000                              /**< DTM Status event, indicating success. */
#define LE_TEST_STATUS_EVENT_ERROR      0x0001                              /**< DTM Status event, indicating an error. */

#define DTM_PKT_PRBS9                   0x00                                /**< Bit pattern PRBS9. */
#define DTM_PKT_0X0F                    0x01                                /**< Bit pattern 11110000 (LSB is the leftmost bit). */
#define DTM_PKT_0X55                    0x02                                /**< Bit pattern 10101010 (LSB is the leftmost bit). */
#define DTM_PKT_0XFF                    0x03                                /**< Bit pattern 11111111 (Used only for coded PHY). */
#define DTM_PKT_VENDORSPECIFIC          0x03                                /**< Vendor specific PKT field value. Nordic: Continuous carrier test, or configuration. */
#define DTM_PKT_TYPE_VENDORSPECIFIC     0xFF                                /**< Vendor specific packet type for internal use. */

// The pdu payload type for each bit pattern. Identical to the PKT value except pattern 0xFF which is 0x04.
#define DTM_PDU_TYPE_PRBS9              0x00                                /**< PDU payload type for bit pattern PRBS9. */
#define DTM_PDU_TYPE_0X0F               0x01                                /**< PDU payload type for bit pattern 11110000 (LSB is the leftmost bit). */
#define DTM_PDU_TYPE_0X55               0x02                                /**< PDU payload type for bit pattern 10101010 (LSB is the leftmost bit). */
#define DTM_PDU_TYPE_0XFF               0x04                                /**< PDU payload type for bit pattern 11111111 (Used only for coded PHY). */

/**@brief Return codes from dtm_cmd(). */
#define DTM_SUCCESS                     0x00                                /**< Indicate that the DTM function completed with success. */
#define DTM_ERROR_ILLEGAL_CHANNEL       0x01                                /**< Physical channel number must be in the range 0..39. */
#define DTM_ERROR_INVALID_STATE         0x02                                /**< Sequencing error: Command is not valid now. */
#define DTM_ERROR_ILLEGAL_LENGTH        0x03                                /**< Payload size must be in the range 0..37. */
#define DTM_ERROR_ILLEGAL_CONFIGURATION 0x04                                /**< Parameter out of range (legal range is function dependent). */
#define DTM_ERROR_UNINITIALIZED         0x05                                /**< DTM module has not been initialized by the application. */

/**@details The UART poll cycle in micro seconds.
 *          A baud rate of e.g. 19200 bits / second, and 8 data bits, 1 start/stop bit, no flow control,
 *          give the time to transmit a byte: 10 bits * 1/19200 = approx: 520 us.
 *          To ensure no loss of bytes, the UART should be polled every 260 us.
 */
#if DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud9600
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/9600/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud14400
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/14400/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud19200
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/19200/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud28800
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/28800/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud38400
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/38400/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud57600
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/57600/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud76800
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/768000/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud115200
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/115200/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud230400
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/230400/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud250000
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/250000/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud460800
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/460800/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud921600
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/921600/2))
#elif DTM_BITRATE == UARTE_BAUDRATE_BAUDRATE_Baud1M
#define UART_POLL_CYCLE ((uint32_t)(10*1e6/1e6/2))
#else
// It is possible to find values that work for other baud rates, but the formula above is not
// guaranteed to work for all values. Suitable values may have to be found by trial and error.
#error "Unsupported baud rate set."
#endif

// Note: DTM_PKT_VENDORSPECIFIC, is not a packet type
#define PACKET_TYPE_MAX                 DTM_PKT_0XFF                    /**< Highest value allowed as DTM Packet type. */

/** @brief BLE DTM event type. */
typedef uint32_t dtm_event_t;                                           /**< Type for handling DTM event. */

/** @brief BLE DTM frequency type. */
typedef uint32_t dtm_freq_t;                                            /**< Physical channel, valid range: 0..39. */

/**@brief BLE DTM packet types. */
typedef uint32_t dtm_pkt_type_t;                                        /**< Type for holding the requested DTM payload type.*/


/**@brief Function for initializing or re-initializing DTM module
 *
 * @return DTM_SUCCESS on successful initialization of the DTM module.
*/
uint32_t dtm_init(void);


/**@brief Function for giving control to dtmlib for handling timer and radio events.
 *        Will return to caller at 625us intervals or whenever another event than radio occurs
 *        (such as UART input). Function will put MCU to sleep between events.
 *
 * @return      Time counter, incremented every 625 us.
 */
uint32_t dtm_wait(void);


/**@brief Function for calling when a complete command has been prepared by the Tester.
 *
 * @param[in]   cmd       One of the DTM_CMD values (bits 14:15 in the 16-bit UART format).
 * @param[in]   freq      Phys. channel no - actual frequency = (2402 + freq * 2) MHz (bits 8:13 in
 *                        the 16-bit UART format).
 * @param[in]   length    Payload length, 0..37 (bits 2:7 in the 16-bit UART format).
 * @param[in]   payload   One of the DTM_PKT values (bits 0:1 in the 16-bit UART format).
 *
 * @return      DTM_SUCCESS or one of the DTM_ERROR_ values
 */
uint32_t dtm_cmd(dtm_cmd_t cmd, dtm_freq_t freq, uint32_t length, dtm_pkt_type_t payload);


/**@brief Function for reading the result of a DTM command
 *
 * @param[out]  p_dtm_event   Pointer to buffer for 16 bit event code according to DTM standard.
 *
 * @return      true: new event, false: no event since last call, this event has been read earlier
 */
bool dtm_event_get(dtm_event_t * p_dtm_event);


/**@brief Function for configuring the timer to use.
 *
 * @note        Must be called when no DTM test is running.
 *
 * @param[in]   new_timer   Index (0..2) of timer to be used by the DTM library
 *
 * @return      true: success, new timer was selected, false: parameter error
 */
bool dtm_set_timer(uint32_t new_timer);


/**@brief Function for configuring the transmit power.
 *
 * @note        Must be called when no DTM test is running.
 *
 * @param[in]   new_tx_power   New output level, +4..-40, in steps of 4.
 *
 * @return      true: tx power setting changed, false: parameter error
 */
bool dtm_set_txpower(uint32_t new_tx_power);


#ifdef __cplusplus
}
#endif

#endif // BLE_DTM_H__

/** @} */
