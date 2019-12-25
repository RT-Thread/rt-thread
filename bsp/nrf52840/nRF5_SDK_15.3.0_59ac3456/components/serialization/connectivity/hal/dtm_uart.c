/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
/**
   @defgroup dtm_standalone main.c
   @{
   @ingroup ble_sdk_app_dtm_serial
   @brief Stand-alone DTM application for UART interface.

 */

#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"
#include "ble_dtm.h"
#include "nrf_gpio.h"
#include "dtm_uart.h"
#include "nrf_error.h"
#include "app_util.h"
#include "nrf_drv_uart.h"
#include "nrf_peripherals.h"
#include "app_util_platform.h"

//Configuration parameters.
#define BITRATE UART_BAUDRATE_BAUDRATE_Baud57600 /**< Serial bitrate on the UART */

//@note: The BLE DTM 2-wire UART standard specifies 8 data bits, 1 stop bit, no flow control.
//These parameters are not configurable in the BLE standard.

/**@details Maximum iterations needed in the main loop between stop bit 1st byte and start bit 2nd
 * byte. DTM standard allows 5000us delay between stop bit 1st byte and start bit 2nd byte.
 * As the time is only known when a byte is received, then the time between between stop bit 1st
 * byte and stop bit 2nd byte becomes:
 *      5000us + transmission time of 2nd byte.
 *
 * Byte transmission time is (Baud rate of 19200):
 *      10bits * 1/19200 = approx. 520 us/byte (8 data bits + start & stop bit).
 *
 * Loop time on polling UART register for received byte is defined in ble_dtm.c as:
 *   UART_POLL_CYCLE = 260 us
 *
 * The max time between two bytes thus becomes (loop time: 260us / iteration):
 *      (5000us + 520us) / 260us / iteration = 21.2 iterations.
 *
 * This is rounded down to 21.
 *
 * @note If UART bit rate is changed, this value should be recalculated as well.
 */

static uint32_t       m_baud_rates[] = {[UART_BAUD_RATE_1200]   = NRF_UART_BAUDRATE_1200,
                                        [UART_BAUD_RATE_2400]   = NRF_UART_BAUDRATE_2400,
                                        [UART_BAUD_RATE_4800]   = NRF_UART_BAUDRATE_4800,
                                        [UART_BAUD_RATE_9600]   = NRF_UART_BAUDRATE_9600,
                                        [UART_BAUD_RATE_14400]  = NRF_UART_BAUDRATE_14400,
                                        [UART_BAUD_RATE_19200]  = NRF_UART_BAUDRATE_19200,
                                        [UART_BAUD_RATE_28800]  = NRF_UART_BAUDRATE_28800,
                                        [UART_BAUD_RATE_38400]  = NRF_UART_BAUDRATE_38400,
                                        [UART_BAUD_RATE_57600]  = NRF_UART_BAUDRATE_57600,
                                        [UART_BAUD_RATE_76800]  = NRF_UART_BAUDRATE_76800,
                                        [UART_BAUD_RATE_115200] = NRF_UART_BAUDRATE_115200 };


static uint32_t       m_iteration[] = {[UART_BAUD_RATE_1200]   = 51,
                                       [UART_BAUD_RATE_2400]   = 35,
                                       [UART_BAUD_RATE_4800]   = 27,
                                       [UART_BAUD_RATE_9600]   = 23,
                                       [UART_BAUD_RATE_14400]  = 21,
                                       [UART_BAUD_RATE_19200]  = 21,
                                       [UART_BAUD_RATE_28800]  = 20,
                                       [UART_BAUD_RATE_38400]  = 20,
                                       [UART_BAUD_RATE_57600]  = 19,
                                       [UART_BAUD_RATE_76800]  = 19,
                                       [UART_BAUD_RATE_115200] = 19, };

static uint32_t       m_iterations_next_byte_max = 51;

static nrf_drv_uart_t m_dtm_uart_driver = NRF_DRV_UART_INSTANCE(0);

/**@brief Function for UART initialization.
 */
static uint32_t uart_init(app_uart_stream_comm_params_t * p_comm_params)
{
    if (p_comm_params->baud_rate > UART_BAUD_RATE_115200)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    nrf_drv_uart_config_t config = NRF_DRV_UART_DEFAULT_CONFIG;

    config.pselrxd = p_comm_params->rx_pin_no;
    config.pseltxd = p_comm_params->tx_pin_no;
    config.baudrate = (nrf_uart_baudrate_t) m_baud_rates[p_comm_params->baud_rate];
    config.hwfc = NRF_UART_HWFC_DISABLED;
    config.parity = NRF_UART_PARITY_EXCLUDED;
#if defined(NRF_DRV_UART_WITH_UARTE) && defined(NRF_DRV_UART_WITH_UART)
    //Current implementation of DTM requires legacy UART features and 
    // it will not work on nrf52810.
    config.use_easy_dma = false;
#endif
    nrf_drv_uart_uninit(&m_dtm_uart_driver);
    uint32_t err_code = nrf_drv_uart_init(&m_dtm_uart_driver, &config, NULL);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    nrf_drv_uart_rx_enable(&m_dtm_uart_driver);

    m_iterations_next_byte_max = m_iteration[p_comm_params->baud_rate];

    return NRF_SUCCESS;
}


/**@brief Function for splitting UART command bit fields into separate command parameters for the DTM library.
 *
 * @param[in]   command   The packed UART command.
 * @return      result status from dtmlib.
 */
static uint32_t dtm_cmd_put(uint16_t command)
{
    dtm_cmd_t      command_code = (command >> 14) & 0x03;
    dtm_freq_t     freq         = (command >> 8) & 0x3F;
    uint32_t       length       = (command >> 2) & 0x3F;
    dtm_pkt_type_t payload      = command & 0x03;

    //Check for Vendor Specific payload.
    if (payload == 0x03)
    {
        /* Note that in a HCI adaption layer, as well as in the DTM PDU format,
           the value 0x03 is a distinct bit pattern (PRBS15). Even though BLE does not
           support PRBS15, this implementation re-maps 0x03 to DTM_PKT_VENDORSPECIFIC,
           to avoid the risk of confusion, should the code be extended to greater coverage.
         */
        payload = DTM_PKT_VENDORSPECIFIC;
    }
    return dtm_cmd(command_code, freq, length, payload);
}


/**@brief Function for application main entry.
 *
 * @details This function serves as an adaptation layer between a 2-wire UART interface and the
 *          dtmlib. After initialization, DTM commands submitted through the UART are forwarded to
 *          dtmlib and events (i.e. results from the command) is reported back through the UART.
 */
uint32_t dtm_start(app_uart_stream_comm_params_t uart_comm_params)
{
    uint32_t    current_time;
    uint32_t    dtm_error_code;
    uint32_t    msb_time          = 0;     //Time when MSB of the DTM command was read. Used to catch stray bytes from "misbehaving" testers.
    bool        is_msb_read       = false; //True when MSB of the DTM command has been read and the application is waiting for LSB.
    uint16_t    dtm_cmd_from_uart = 0;     //Packed command containing command_code:freqency:length:payload in 2:6:6:2 bits.
    uint8_t     rx_byte;                   //Last byte read from UART.
    dtm_event_t result;                    //Result of a DTM operation.
    uint32_t    err_code;

    err_code = uart_init(&uart_comm_params);

    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    dtm_error_code = dtm_init();

    if (dtm_error_code != DTM_SUCCESS)
    {
        //If DTM cannot be correctly initialized, then we just return.
        return NRF_ERROR_INTERNAL;
    }

    for (;; )
    {
        //Will return every timeout, 625 us.
        current_time = dtm_wait();

        if (NRF_SUCCESS != nrf_drv_uart_rx(&m_dtm_uart_driver, &rx_byte,1))
        {
            return NRF_ERROR_INTERNAL;
        }

        if (!is_msb_read)
        {
            //This is first byte of two-byte command.
            is_msb_read       = true;
            dtm_cmd_from_uart = ((dtm_cmd_t)rx_byte) << 8;
            msb_time          = current_time;

            //Go back and wait for 2nd byte of command word.
            continue;
        }

        //This is the second byte read; combine it with the first and process command
        if (current_time > (msb_time + m_iterations_next_byte_max))
        {
            //More than ~5mS after msb: Drop old byte, take the new byte as MSB.
            //The variable is_msb_read will remains true.
            //Go back and wait for 2nd byte of the command word.
            dtm_cmd_from_uart = ((dtm_cmd_t)rx_byte) << 8;
            msb_time          = current_time;
            continue;
        }

        //2-byte UART command received.
        is_msb_read        = false;
        dtm_cmd_from_uart |= (dtm_cmd_t)rx_byte;

        if (dtm_cmd_put(dtm_cmd_from_uart) != DTM_SUCCESS)
        {
            //Extended error handling may be put here.
            //Default behavior is to return the event on the UART (see below);
            //the event report will reflect any lack of success.
        }

        //Retrieve result of the operation. This implementation will busy-loop
        //for the duration of the byte transmissions on the UART.
        if (dtm_event_get(&result))
        {
            //Report command status on the UART.
            uint8_t tx_byte = (result >> 8) & 0xFF;

            //Transmit MSB of the result.
            (void)nrf_drv_uart_tx(&m_dtm_uart_driver, &tx_byte, 1);

            //Transmit LSB of the result.
            tx_byte = result & 0xFF;
            (void)nrf_drv_uart_tx(&m_dtm_uart_driver, &tx_byte, 1);
        }
    }
}

/// @}
