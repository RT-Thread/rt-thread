/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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
#ifndef __KEYPAD_PORT_H__
#define __KEYPAD_PORT_H__

//! @addtogroup diag_keypad
//! @{

/*!
 * @file keypad_port.h
 * @brief Keypad port driver header file.
 */

#include "sdk.h"

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the keypad controller.
 *
 * @param kpp_col Mask of active columns in the keypad.
 * @param kpp_row Mask of active rows in the keypad.
 */
void kpp_open(uint8_t kpp_col, uint8_t kpp_row);

/*!
 * @brief Close the keypad driver.
 *
 * Leaves the keypad controller in a known state. Interrupts are disabled. All rows
 * are disabled.
 */
void kpp_close(void);

/*!
 * @brief Keypad port function to return the read key.
 *
 * @param[out] rd_keys Active columns in the keypad.
 * @param returnImmediately Pass true to wait for a key pressed interrupt, or false to read
 *      the keypad state immediately.
 */
void kpp_get_keypad_state(uint16_t *rd_keys, bool returnImmediately);

/*!
 * @brief Waits for all keys to release.
 *
 * The hardware can only detect this condition, and couldn't
 * detect the release of a single key but by doing it
 * by software.
 */
void kpp_wait_for_release_state(void);

#if defined(__cplusplus)
}
#endif

//! @}

#endif /* __KEYPAD_PORT_H__ */
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
