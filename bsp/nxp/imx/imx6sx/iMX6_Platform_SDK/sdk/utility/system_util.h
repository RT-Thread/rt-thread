/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file  system_util.h
 * @brief header file for the system utility functions.
 *
 */

#ifndef _SYSTEM_UTIL_H_
#define _SYSTEM_UTIL_H_

//! @addtogroup diag_util
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Typedef for an input filter function for read_input_string().
typedef bool (*input_string_filter_t)(char newChar, const char * currentString);

//! @brief HAB failsafe routine typedef.
typedef void hab_rvt_failsafe_t(void);

//! ROM Vector Table starts at address 0x94
#define HAB_RVT_FAILSAFE (*(uint32_t *) 0x000000BC)
#define hab_rvt_failsafe ((hab_rvt_failsafe_t *) HAB_RVT_FAILSAFE)

////////////////////////////////////////////////////////////////////////////////
// Board support
////////////////////////////////////////////////////////////////////////////////

//! @name Board support
//@{
//! @brief UART port instance number used for the debug UART.
//!
//! This is used by the driver in order to factor out board
//! specific functionality. It must be defined by the board support
//! library or the application.
extern uint32_t g_debug_uart_port;
//@}

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Exception signaling and handling for C lib functions.
 *
 * This function never returns.
 *
 * In release builds (i.e., the DEBUG macro is not defined), the processor will be put
 * to sleep using the WFI instruction.
 *
 * @param    return_code     not used
 */
void _sys_exit(int32_t return_code);

/*!
 * @brief Breakpoint function.
 */
void mybkpt(void);

int _raw_puts(char str[]);

/*!
 * @brief Read a string from interactive console input.
 *
 * @param filter Optional filter function. If this parameter is not NULL, it will be called
 *      for every character that is read from the input. If it returns true, then the
 *      new character will be added to the output string.
 * @return The string that was read in. The string is allocated with malloc() and must be
 *      freed by the caller.
 */
char * read_input_string(input_string_filter_t filter);

/*!
 * This function waits for an input char to be received from the UART. Once a char is received,
 * it tests against the passed in char and return 0 if they don't match. 
 * @param   c        the input character to be expected (NOT case sensitive)
 * @param   indent   pointer to a character buffer to use for indenting text to screen
 * @return  0        if input char doesn't match with c
 *          non-zero otherwise
 */
int32_t is_input_char(uint8_t c, const char* const indent);

/*!
 * @brief Reads a hex number from console input.
 */
uint32_t get_input_hex(void);

/*!
 * @brief Reads a decimal number from console input.
 */
int read_int(void);

/*!
 * @brief Function to jump into the ROM Serial Download Protocol.
 * 
 * Control never returns to the caller once this function is called.
 */
void jump_to_sdp(void);


#if defined(__cplusplus)
}
#endif

//! @}

#endif //_SYSTEM_UTIL_H_
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
