/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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

#ifndef NRF_DFU_SERIAL_H__
#define NRF_DFU_SERIAL_H__

#include <stdint.h>
#include "sdk_errors.h"
#include "nrf_dfu_req_handler.h"
#include "nrf_dfu_transport.h"


#ifdef __cplusplus
extern "C" {
#endif

/**@file
 *
 * @defgroup nrf_dfu_serial DFU Serial transports shared part
 * @{
 * @ingroup  nrf_dfu
 * @brief    Shared part of Device Firmware Update (DFU) transport layers using serial interface (UART, USB CDC ACM).
 *
 * @defgroup nrf_dfu_serial_uart DFU Serial UART transport
 * @ingroup  nrf_dfu_serial
 * @brief    Configuration for Device Firmware Update (DFU) transport layer using UART.
 *
 * @defgroup nrf_dfu_serial_usb DFU Serial USB CDC ACM transport
 * @ingroup  nrf_dfu_serial
 * @brief    Configuration for Device Firmware Update (DFU) transport layer using USB CDC ACM.
 *
 */

#define NRF_SERIAL_MAX_RESPONSE_SIZE (sizeof(nrf_dfu_response_t))

/**
 * Prototype for function for sending response over serial DFU transport.
 */
typedef ret_code_t (*nrf_serial_rsp_func_t)(uint8_t const * p_data, uint32_t length);

/**
 * Prototype for function for freeing RX buffer.
 *
 * Function is called when input data is processed.
 */
typedef void (*nrf_serial_rx_buf_free_func_t)(void * p_buf);


/**@brief   DFU serial transport layer state.
 *
 * @details This structure contains status information related to the serial transport layer type.
 */
typedef struct
{
    uint16_t                      pkt_notif_target;
    uint16_t                      pkt_notif_target_count;
    nrf_serial_rsp_func_t         rsp_func;
    nrf_serial_rx_buf_free_func_t payload_free_func;
    uint32_t                      mtu;
    uint8_t *                     p_rsp_buf;
    nrf_dfu_transport_t const *   p_low_level_transport;
} nrf_dfu_serial_t;

void nrf_dfu_serial_on_packet_received(nrf_dfu_serial_t       * p_transport,
                                       uint8_t          const * p_data,
                                       uint32_t                 length);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // NRF_DFU_SERIAL_H__
