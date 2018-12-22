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
#ifndef __RTC_H__
#define __RTC_H__

//! @addtogroup diag_rtc
//! @{

/*!
 * @file rtc.h
 * @brief  RTC driver header file.
 */

#include "sdk.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Type for an RTC timer callback function.
typedef void (*rtc_callback_t)(void * arg);

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes RTC.
 *
 * Enables non-secured real time counter, disables alarm and periodic interrupt.
 * It also registers an interrupt service handler.
 */
void rtc_init(void);

/*!
 * Disables interrupt, counter, alarm and periodic alarm
 */
void rtc_deinit(void);

/*!
 * @brief Setup up a one-shot timer.
 *
 * @param   timeout Set RTC alarm timeout.
 * @param   callback Callback function to be called from isr.
 * @param   arg Arbitrary argument passed to the callacbk function.
 */
void rtc_setup_onetime_timer(uint64_t timeout, rtc_callback_t callback, void * arg);

/*!
 * @brief Sets up a periodic timer.
 *
 * @param   periodic_bit Periodic interrupt freq (valid values 0-15)
 * @param   callback Pointer to callback function
 * @param   arg Arbitrary argument passed to the callacbk function.
 */
void rtc_setup_periodic_timer(uint32_t periodic_bit, rtc_callback_t callback, void * arg);

/*!
 * @brief Disables the periodic timer.
 */
void rtc_disable_periodic_timer(void);

#if defined(__cplusplus)
}
#endif

//! @}

#endif //__RTC_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
