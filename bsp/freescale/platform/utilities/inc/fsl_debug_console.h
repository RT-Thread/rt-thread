/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#if !defined(__FSL_DEBUG_CONSOLE_H__)
#define __FSL_DEBUG_CONSOLE_H__

#include <stdint.h>
#include "fsl_os_abstraction.h"

/*
 * @addtogroup debug_console
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define IO_MAXLINE  20

#if (defined (FSL_RTOS_MQX) && (MQX_COMMON_CONFIG != MQX_LITE_CONFIG))
#define PRINTF          printf
#define SCANF           scanf
#define PUTCHAR         putchar
#define GETCHAR         getchar
#include <stdio.h>
#else
/*Configuration for toolchain's printf/scanf or KSDK version printf/scanf */
#define PRINTF          debug_printf
//#define PRINTF          printf
#define SCANF           debug_scanf
//#define SCANF           scanf
#define PUTCHAR         debug_putchar
//#define PUTCHAR         putchar
#define GETCHAR         debug_getchar
//#define GETCHAR         getchar
#endif

/*! @brief Error code for the debug console driver. */
typedef enum _debug_console_status {
    kStatus_DEBUGCONSOLE_Success = 0U,
    kStatus_DEBUGCONSOLE_InvalidDevice,
    kStatus_DEBUGCONSOLE_AllocateMemoryFailed,
    kStatus_DEBUGCONSOLE_Failed 
} debug_console_status_t;

/*! @brief Supported debug console hardware device type. */
typedef enum _debug_console_device_type {
    kDebugConsoleNone   = 0U,
    kDebugConsoleLPSCI  = 15U,     /*<! Use strange start number to avoid treating 0
                                     as correct device type. Sometimes user forget
                                     to specify the device type but only use the 
                                     default value '0' as the device type.  */
    kDebugConsoleUART   = 16U,
    kDebugConsoleLPUART = 17U,
    kDebugConsoleUSBCDC = 18U
} debug_console_device_type_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @name Initialization*/
/*@{*/

/*!
 * @brief Init the UART/LPUART used for debug messages.
 *
 * Call this function to enable debug log messages to be output via the specified UART/LPUART
 * base address and at the specified baud rate. Just initializes the UART/LPUART to the given baud
 * rate and 8N1. After this function has returned, stdout and stdin will be connected to the
 * selected UART/LPUART. The debug_printf() function also uses this UART/LPUART.
 *
 * @param uartInstance Which UART/LPUART instance is used to send debug messages.
 * @param baudRate The desired baud rate in bits per second.
 * @param device Low level device type for the debug console.
 * @return Whether initialization was successful or not. 
 */
debug_console_status_t DbgConsole_Init(
        uint32_t uartInstance, uint32_t baudRate, debug_console_device_type_t device);

/*!
 * @brief Deinit the UART/LPUART used for debug messages.
 *
 * Call this function to disable debug log messages to be output via the specified UART/LPUART
 * base address and at the specified baud rate.
 * @return Whether de-initialization was successful or not.
 */
debug_console_status_t DbgConsole_DeInit(void);

/*!
 * @brief   Prints formatted output to the standard output stream.
 *
 * Call this function to print formatted output to the standard output stream.
 *
 * @param   fmt_s   Format control string.
 * @return  Returns the number of characters printed, or a negative value if an error occurs.
 */
int debug_printf(const char  *fmt_s, ...);

/*!
 * @brief   Writes a character to stdout.
 *
 * Call this function to write a character to stdout.
 *
 * @param   ch  Character to be written.
 * @return  Returns the character written.
 */
int debug_putchar(int ch);

/*!
 * @brief   Reads formatted data from the standard input stream.
 *
 * Call this function to read formatted data from the standard input stream.
 *
 * @param   fmt_ptr Format control string.
 * @return  Returns the number of fields successfully converted and assigned.
 */
int debug_scanf(const char  *fmt_ptr, ...);

/*!
 * @brief   Reads a character from standard input.
 *
 * Call this function to read a character from standard input.
 *
 * @return  Returns the character read.
 */
int debug_getchar(void);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_DEBUG_CONSOLE_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/
