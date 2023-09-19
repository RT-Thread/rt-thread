/***********************************************************************************************//**
 * \file cy_retarget_io.h
 *
 * \brief
 * Provides APIs for transmitting messages to or from the board via standard
 * printf/scanf functions. Messages are transmitted over a UART connection which
 * is generally connected to a host machine. Transmission is done at 115200 baud
 * using the tx and rx pins provided by the user of this library. The UART
 * instance is made available via cy_retarget_io_uart_obj in case any changes
 * to the default configuration are desired.
 * NOTE: If the application is built using newlib-nano, by default, floating
 * point format strings (%f) are not supported. To enable this support you must
 * add '-u _printf_float' to the linker command line.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2018-2021 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **************************************************************************************************/

/**
 * \addtogroup group_board_libs Retarget IO
 * \{
 */

#pragma once

#include <stdio.h>
#include "cy_result.h"
#include "cyhal_hw_types.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** UART HAL object used by this library */
extern cyhal_uart_t cy_retarget_io_uart_obj;

/** UART baud rate */
#define CY_RETARGET_IO_BAUDRATE             (115200)

#ifdef DOXYGEN

/** Defining this macro enables conversion of line feed (LF) into carriage
 * return followed by line feed (CR & LF) on the output direction (STDOUT). You
 * can define this macro through the DEFINES variable in the application
 * Makefile.
 */
#define CY_RETARGET_IO_CONVERT_LF_TO_CRLF

#endif // DOXYGEN

/**
 * \brief Initialization function for redirecting low level IO commands to allow
 * sending messages over a UART interface. This will setup the communication
 * interface to allow using printf and related functions.
 *
 * In an RTOS environment, this function must be called after the RTOS has been
 * initialized.
 *
 * \param tx UART TX pin
 * \param rx UART RX pin
 * \param baudrate UART baudrate
 * \returns CY_RSLT_SUCCESS if successfully initialized, else an error about
 * what went wrong
 */
cy_rslt_t cy_retarget_io_init(cyhal_gpio_t tx, cyhal_gpio_t rx, uint32_t baudrate);

/**
 * \brief Checks whether there is data waiting to be written to the serial console.
 * \returns true if there are pending TX transactions, otherwise false
 */
bool cy_retarget_io_is_tx_active();

/**
 * \brief Releases the UART interface allowing it to be used for other purposes.
 * After calling this, printf and related functions will no longer work.
 */
void cy_retarget_io_deinit(void);

#if defined(__cplusplus)
}
#endif

/** \} group_board_libs */
