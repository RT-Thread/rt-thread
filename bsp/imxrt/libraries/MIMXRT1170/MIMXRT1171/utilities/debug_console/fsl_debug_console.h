/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018, 2020, 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Debug console shall provide input and output functions to scan and print formatted data.
 * o Support a format specifier for PRINTF follows this prototype "%[flags][width][.precision][length]specifier"
 *   - [flags] :'-', '+', '#', ' ', '0'
 *   - [width]:  number (0,1...)
 *   - [.precision]: number (0,1...)
 *   - [length]: do not support
 *   - [specifier]: 'd', 'i', 'f', 'F', 'x', 'X', 'o', 'p', 'u', 'c', 's', 'n'
 * o Support a format specifier for SCANF follows this prototype " %[*][width][length]specifier"
 *   - [*]: is supported.
 *   - [width]: number (0,1...)
 *   - [length]: 'h', 'hh', 'l','ll','L'. ignore ('j','z','t')
 *   - [specifier]: 'd', 'i', 'u', 'f', 'F', 'e', 'E', 'g', 'G', 'a', 'A', 'o', 'c', 's'
 */

#ifndef _FSL_DEBUGCONSOLE_H_
#define _FSL_DEBUGCONSOLE_H_

#include "fsl_common.h"

/*!
 * @addtogroup debugconsole
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Definition select redirect toolchain printf, scanf to uart or not. */
#define DEBUGCONSOLE_REDIRECT_TO_TOOLCHAIN 0U /*!< Select toolchain printf and scanf. */
#define DEBUGCONSOLE_REDIRECT_TO_SDK       1U /*!< Select SDK version printf, scanf. */
#define DEBUGCONSOLE_DISABLE               2U /*!< Disable debugconsole function. */

/*! @brief Definition to select sdk or toolchain printf, scanf. The macro only support
 * to be redefined in project setting.
 */
#ifndef SDK_DEBUGCONSOLE
#define SDK_DEBUGCONSOLE DEBUGCONSOLE_REDIRECT_TO_SDK
#endif

#if (SDK_DEBUGCONSOLE != DEBUGCONSOLE_DISABLE) || defined(SDK_DEBUGCONSOLE_UART)
#include "fsl_component_serial_manager.h"

extern serial_handle_t g_serialHandle; /*!< serial manager handle */
#endif /* (SDK_DEBUGCONSOLE != DEBUGCONSOLE_DISABLE) || defined(SDK_DEBUGCONSOLE_UART) */

#if defined(SDK_DEBUGCONSOLE) && !(SDK_DEBUGCONSOLE)
#include <stdio.h>
#else
#include <stdarg.h>
#endif

/*! @brief Definition to select redirect toolchain printf, scanf to uart or not.
 *
 *  if SDK_DEBUGCONSOLE defined to 0,it represents select toolchain printf, scanf.
 *  if SDK_DEBUGCONSOLE defined to 1,it represents select SDK version printf, scanf.
 *  if SDK_DEBUGCONSOLE defined to 2,it represents disable debugconsole function.
 */
#if SDK_DEBUGCONSOLE == DEBUGCONSOLE_DISABLE /* Disable debug console */
static inline int DbgConsole_Disabled(void)
{
    return -1;
}
#define PRINTF(...)  DbgConsole_Disabled()
#define SCANF(...)   DbgConsole_Disabled()
#define PUTCHAR(...) DbgConsole_Disabled()
#define GETCHAR()    DbgConsole_Disabled()
#elif SDK_DEBUGCONSOLE == DEBUGCONSOLE_REDIRECT_TO_SDK /* Select printf, scanf, putchar, getchar of SDK version. */
#define PRINTF  DbgConsole_Printf
#define SCANF   DbgConsole_Scanf
#define PUTCHAR DbgConsole_Putchar
#define GETCHAR DbgConsole_Getchar
#elif SDK_DEBUGCONSOLE == DEBUGCONSOLE_REDIRECT_TO_TOOLCHAIN /* Select printf, scanf, putchar, getchar of toolchain. \ \
                                                              */
#define PRINTF  printf
#define SCANF   scanf
#define PUTCHAR putchar
#define GETCHAR getchar
#endif /* SDK_DEBUGCONSOLE */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @name Initialization*/
/* @{ */

#if ((SDK_DEBUGCONSOLE == DEBUGCONSOLE_REDIRECT_TO_SDK) || defined(SDK_DEBUGCONSOLE_UART))
/*!
 * @brief Initializes the peripheral used for debug messages.
 *
 * Call this function to enable debug log messages to be output via the specified peripheral
 * initialized by the serial manager module.
 * After this function has returned, stdout and stdin are connected to the selected peripheral.
 *
 * @param instance      The instance of the module.If the device is kSerialPort_Uart,
 *                      the instance is UART peripheral instance. The UART hardware peripheral
 *                      type is determined by UART adapter. For example, if the instance is 1,
 *                      if the lpuart_adapter.c is added to the current project, the UART periheral
 *                      is LPUART1.
 *                      If the uart_adapter.c is added to the current project, the UART periheral
 *                      is UART1.
 * @param baudRate      The desired baud rate in bits per second.
 * @param device        Low level device type for the debug console, can be one of the following.
 *                      @arg kSerialPort_Uart,
 *                      @arg kSerialPort_UsbCdc
 * @param clkSrcFreq    Frequency of peripheral source clock.
 *
 * @return              Indicates whether initialization was successful or not.
 * @retval kStatus_Success          Execution successfully
 */
status_t DbgConsole_Init(uint8_t instance, uint32_t baudRate, serial_port_type_t device, uint32_t clkSrcFreq);

/*!
 * @brief De-initializes the peripheral used for debug messages.
 *
 * Call this function to disable debug log messages to be output via the specified peripheral
 * initialized by the serial manager module.
 *
 * @return Indicates whether de-initialization was successful or not.
 */
status_t DbgConsole_Deinit(void);
/*!
 * @brief Prepares to enter low power consumption.
 *
 * This function is used to prepare to enter low power consumption.
 *
 * @return Indicates whether de-initialization was successful or not.
 */
status_t DbgConsole_EnterLowpower(void);

/*!
 * @brief Restores from low power consumption.
 *
 * This function is used to restore from low power consumption.
 *
 * @return Indicates whether de-initialization was successful or not.
 */
status_t DbgConsole_ExitLowpower(void);

#else
/*!
 * Use an error when SDK_DEBUGCONSOLE is not DEBUGCONSOLE_REDIRECT_TO_SDK and
 * SDK_DEBUGCONSOLE_UART is not defined.
 */
static inline status_t DbgConsole_Error(void)
{
    return (status_t)kStatus_Fail;
}

#define DbgConsole_Init(...)  DbgConsole_Error()
#define DbgConsole_Deinit(...)  DbgConsole_Error()
#define DbgConsole_EnterLowpower(...)  DbgConsole_Error()
#define DbgConsole_ExitLowpower(...)  DbgConsole_Error()

#endif /* ((SDK_DEBUGCONSOLE == DEBUGCONSOLE_REDIRECT_TO_SDK) || defined(SDK_DEBUGCONSOLE_UART)) */

#if (defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE == DEBUGCONSOLE_REDIRECT_TO_SDK))
/*!
 * @brief Writes formatted output to the standard output stream.
 *
 * Call this function to write a formatted output to the standard output stream.
 *
 * @param   fmt_s Format control string.
 * @return  Returns the number of characters printed or a negative value if an error occurs.
 */
int DbgConsole_Printf(const char *fmt_s, ...);

/*!
 * @brief Writes formatted output to the standard output stream.
 *
 * Call this function to write a formatted output to the standard output stream.
 *
 * @param   fmt_s Format control string.
 * @param   formatStringArg Format arguments.
 * @return  Returns the number of characters printed or a negative value if an error occurs.
 */
int DbgConsole_Vprintf(const char *fmt_s, va_list formatStringArg);

/*!
 * @brief Writes a character to stdout.
 *
 * Call this function to write a character to stdout.
 *
 * @param   ch Character to be written.
 * @return  Returns the character written.
 */
int DbgConsole_Putchar(int ch);

/*!
 * @brief Reads formatted data from the standard input stream.
 *
 * Call this function to read formatted data from the standard input stream.
 *
 * @note Due the limitation in the BM OSA environment (CPU is blocked in the function,
 * other tasks will not be scheduled), the function cannot be used when the
 * DEBUG_CONSOLE_TRANSFER_NON_BLOCKING is set in the BM OSA environment.
 * And an error is returned when the function called in this case. The suggestion
 * is that polling the non-blocking function DbgConsole_TryGetchar to get the input char.
 *
 * @param   fmt_s Format control string.
 * @return  Returns the number of fields successfully converted and assigned.
 */
int DbgConsole_Scanf(char *fmt_s, ...);

/*!
 * @brief Reads a character from standard input.
 *
 * Call this function to read a character from standard input.
 *
 * @note Due the limitation in the BM OSA environment (CPU is blocked in the function,
 * other tasks will not be scheduled), the function cannot be used when the
 * DEBUG_CONSOLE_TRANSFER_NON_BLOCKING is set in the BM OSA environment.
 * And an error is returned when the function called in this case. The suggestion
 * is that polling the non-blocking function DbgConsole_TryGetchar to get the input char.
 *
 * @return Returns the character read.
 */
int DbgConsole_Getchar(void);

/*!
 * @brief Writes formatted output to the standard output stream with the blocking mode.
 *
 * Call this function to write a formatted output to the standard output stream with the blocking mode.
 * The function will send data with blocking mode no matter the DEBUG_CONSOLE_TRANSFER_NON_BLOCKING set
 * or not.
 * The function could be used in system ISR mode with DEBUG_CONSOLE_TRANSFER_NON_BLOCKING set.
 *
 * @param   fmt_s Format control string.
 * @return  Returns the number of characters printed or a negative value if an error occurs.
 */
int DbgConsole_BlockingPrintf(const char *fmt_s, ...);

/*!
 * @brief Writes formatted output to the standard output stream with the blocking mode.
 *
 * Call this function to write a formatted output to the standard output stream with the blocking mode.
 * The function will send data with blocking mode no matter the DEBUG_CONSOLE_TRANSFER_NON_BLOCKING set
 * or not.
 * The function could be used in system ISR mode with DEBUG_CONSOLE_TRANSFER_NON_BLOCKING set.
 *
 * @param   fmt_s Format control string.
 * @param   formatStringArg Format arguments.
 * @return  Returns the number of characters printed or a negative value if an error occurs.
 */
int DbgConsole_BlockingVprintf(const char *fmt_s, va_list formatStringArg);

/*!
 * @brief Debug console flush.
 *
 * Call this function to wait the tx buffer empty.
 * If interrupt transfer is using, make sure the global IRQ is enable before call this function
 * This function should be called when
 * 1, before enter power down mode
 * 2, log is required to print to terminal immediately
 * @return Indicates whether wait idle was successful or not.
 */
status_t DbgConsole_Flush(void);

#ifdef DEBUG_CONSOLE_TRANSFER_NON_BLOCKING
/*!
 * @brief Debug console try to get char
 * This function provides a API which will not block current task, if character is
 * available return it, otherwise return fail.
 * @param ch the address of char to receive
 * @return Indicates get char was successful or not.
 */
status_t DbgConsole_TryGetchar(char *ch);
#endif

#endif /* SDK_DEBUGCONSOLE */

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_DEBUGCONSOLE_H_ */
