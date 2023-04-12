/*
 * Copyright 2017-2018, 2020, 2022 NXP
 * All rights reserved.
 *
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
 * @addtogroup debugconsolelite
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Definition select redirect toolchain printf, scanf to uart or not. */
#define DEBUGCONSOLE_REDIRECT_TO_TOOLCHAIN 0U /*!< Select toolchain printf and scanf. */
#define DEBUGCONSOLE_REDIRECT_TO_SDK       1U /*!< Select SDK version printf, scanf. */
#define DEBUGCONSOLE_DISABLE               2U /*!< Disable debugconsole function. */

/*! @brief Definition to select sdk or toolchain printf, scanf. */
#ifndef SDK_DEBUGCONSOLE
#define SDK_DEBUGCONSOLE DEBUGCONSOLE_REDIRECT_TO_SDK
#endif

#if defined(SDK_DEBUGCONSOLE) && !(SDK_DEBUGCONSOLE)
#include <stdio.h>
#else
#include <stdarg.h>
#endif

/*! @brief Definition to printf the float number. */
#ifndef PRINTF_FLOAT_ENABLE
#define PRINTF_FLOAT_ENABLE 0U
#endif /* PRINTF_FLOAT_ENABLE */

/*! @brief Definition to scanf the float number. */
#ifndef SCANF_FLOAT_ENABLE
#define SCANF_FLOAT_ENABLE 0U
#endif /* SCANF_FLOAT_ENABLE */

/*! @brief Definition to support advanced format specifier for printf. */
#ifndef PRINTF_ADVANCED_ENABLE
#define PRINTF_ADVANCED_ENABLE 0U
#endif /* PRINTF_ADVANCED_ENABLE */

/*! @brief Definition to support advanced format specifier for scanf. */
#ifndef SCANF_ADVANCED_ENABLE
#define SCANF_ADVANCED_ENABLE 0U
#endif /* SCANF_ADVANCED_ENABLE */

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
#elif SDK_DEBUGCONSOLE == \
    DEBUGCONSOLE_REDIRECT_TO_TOOLCHAIN /* Select printf, scanf, putchar, getchar of toolchain. \ */
#define PRINTF  printf
#define SCANF   scanf
#define PUTCHAR putchar
#define GETCHAR getchar
#endif /* SDK_DEBUGCONSOLE */
/*! @} */

/*! @brief serial port type
 *
 *  The serial port type aligned with the definition in serial manager, but please note
 *  only kSerialPort_Uart can be supported in debug console lite.
 */
#ifndef _SERIAL_PORT_T_
#define _SERIAL_PORT_T_
typedef enum _serial_port_type
{
    kSerialPort_None = 0U, /*!< Serial port is none */
    kSerialPort_Uart = 1U, /*!< Serial port UART */
    kSerialPort_UsbCdc,    /*!< Serial port USB CDC */
    kSerialPort_Swo,       /*!< Serial port SWO */
    kSerialPort_Virtual,   /*!< Serial port Virtual */
    kSerialPort_Rpmsg,     /*!< Serial port RPMSG */
    kSerialPort_UartDma,   /*!< Serial port UART DMA*/
    kSerialPort_SpiMaster, /*!< Serial port SPIMASTER*/
    kSerialPort_SpiSlave,  /*!< Serial port SPISLAVE*/
} serial_port_type_t;
#endif

/*!
 * @addtogroup debugconsolelite
 * @{
 */
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
 * Call this function to enable debug log messages to be output via the specified peripheral,
 * frequency of peripheral source clock, and base address at the specified baud rate.
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
 *                      @arg kSerialPort_Uart.
 * @param clkSrcFreq    Frequency of peripheral source clock.
 *
 * @return              Indicates whether initialization was successful or not.
 * @retval kStatus_Success          Execution successfully
 * @retval kStatus_Fail             Execution failure
 */
status_t DbgConsole_Init(uint8_t instance, uint32_t baudRate, serial_port_type_t device, uint32_t clkSrcFreq);

/*!
 * @brief De-initializes the peripheral used for debug messages.
 *
 * Call this function to disable debug log messages to be output via the specified peripheral
 * base address and at the specified baud rate.
 *
 * @return Indicates whether de-initialization was successful or not.
 */
status_t DbgConsole_Deinit(void);

#else
/*!
 * Use an error to replace the DbgConsole_Init when SDK_DEBUGCONSOLE is not DEBUGCONSOLE_REDIRECT_TO_SDK and
 * SDK_DEBUGCONSOLE_UART is not defined.
 */
static inline status_t DbgConsole_Init(uint8_t instance,
                                       uint32_t baudRate,
                                       serial_port_type_t device,
                                       uint32_t clkSrcFreq)
{
    (void)instance;
    (void)baudRate;
    (void)device;
    (void)clkSrcFreq;
    return (status_t)kStatus_Fail;
}
/*!
 * Use an error to replace the DbgConsole_Deinit when SDK_DEBUGCONSOLE is not DEBUGCONSOLE_REDIRECT_TO_SDK and
 * SDK_DEBUGCONSOLE_UART is not defined.
 */
static inline status_t DbgConsole_Deinit(void)
{
    return (status_t)kStatus_Fail;
}

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
 * @param   fmt_s Format control string.
 * @return  Returns the number of fields successfully converted and assigned.
 */
int DbgConsole_Scanf(char *fmt_s, ...);

/*!
 * @brief Reads a character from standard input.
 *
 * Call this function to read a character from standard input.
 *
 * @return Returns the character read.
 */
int DbgConsole_Getchar(void);

#endif /* SDK_DEBUGCONSOLE */

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */
#endif /* _FSL_DEBUGCONSOLE_H_ */
