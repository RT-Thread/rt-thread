/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_FLEXIO_UART_SHARE_H__
#define __FSL_FLEXIO_UART_SHARE_H__

#include <stdint.h>
#include <stdbool.h>
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*!
 * @addtogroup flexio_uart_driver
 * @{
 */

/*! @brief Error codes for the FLEXIO UART driver. */
typedef enum flexio_uart_status
{
    kStatus_FlexIO_UART_Success                  = 0x00U, 
    kStatus_FlexIO_UART_TxBusy                   = 0x01U, 
    kStatus_FlexIO_UART_RxBusy                   = 0x02U,  
    kStatus_FlexIO_UART_NoTransmitInProgress     = 0x03U,
    kStatus_FlexIO_UART_NoReceiveInProgress      = 0x04U, 
    kStatus_FlexIO_UART_Timeout                  = 0x05U,
    kStatus_FlexIO_UART_NoDataToDeal             = 0x06U,   
    kStatus_FlexIO_UART_TxUnderRun               = 0x07U,
    kStatus_FlexIO_UART_RxOverRun                = 0x08U,
    kStatus_FlexIO_UART_InvalidParam             = 0x09U  
} flexio_uart_status_t;
/*!
 * @brief FlexIO UART number of bits in a character.
 *
 * These constants define the number of allowable data bits per UART character. Note, check the
 * UART documentation to determine if the desired UART baseAddr supports the desired number
 * of data bits per UART character.
 */
typedef enum  flexio_uart_bit_count_per_char {
    kFlexIOUart5BitsPerChar = 5U,   /*!< 5-bit data characters @internal gui name="5" */
    kFlexIOUart6BitsPerChar = 6U,   /*!< 6-bit data characters @internal gui name="6" */
    kFlexIOUart7BitsPerChar = 7U,   /*!< 7-bit data characters @internal gui name="7" */
    kFlexIOUart8BitsPerChar = 8U    /*!< 8-bit data characters @internal gui name="8" */
} flexio_uart_bit_count_per_char_t;
/*!
 * @brief FlexIO UART mode.
 *
 * These constants define the operation mode of FlexIO UART: Only enable transmit, only enable receive,
 * or use both. 
 */
typedef enum flexio_uart_mode
{
    flexioUART_TxOnly = 0x0U, /*!< Transmit mode only @internal gui name="Tx" */
    flexioUART_RxOnly = 0x1U, /*!< Receive mode only @internal gui name="Rx" */
    flexioUART_TxRx   = 0x2U /*!< Both modes @internal gui name="Tx+Rx" */
}flexio_uart_mode_t;
/*!
 * @brief FlexIO UART hardware resource configuration.
 *
 * These constants define the hardware resource used by the FlexIO UART transmit/receive device and include
 * the external pin and internal shifter and timer.
 * @internal gui name="UART hardware configuration" id="uartHwCfg"
 */
typedef struct flexio_uart_hwconfig{
    uint32_t pinIdx; /*!< Data line pin. @internal gui name="Data pin" id="uartPin" */
    uint32_t shifterIdx; /*!< Shifter @internal gui name="Shifter" id="uartShifter" */
    uint32_t timerIdx; /*!< Timer @internal gui name="Timer" id="uartTimer" */
}flexio_uart_hwconfig_t;

/*! @}*/

#endif

#endif /* __FSL_FLEXIO_UART_SHARE_H__*/
