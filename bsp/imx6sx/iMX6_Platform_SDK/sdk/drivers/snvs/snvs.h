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
 * @file snvs.h
 * @brief  SNVS driver header file.
 */

#ifndef __SNVS_H__
#define __SNVS_H__

#include "sdk.h"

//! @addtogroup diag_snvs
//! @{

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Presently nothing to do as part of snvs initialization
 *
 */
void snvs_init(void);

/*!
 * @brief Presently nothing to do as part of snvs deinit
 *
 */
void snvs_deinit(void);

/*!
 * @brief Enable or disable non-secured real time counter
 *
 * @param   state True to enable the counter and false to disable it.
 */
void snvs_rtc_counter(uint8_t state);

/*!
 * @brief Enable or disable non-secured time alarm
 *
 * @param   state True to enable the alarm and false to disable it.
 */
void snvs_rtc_alarm(uint8_t state);

/*!
 * @brief Enable or disable non-secured periodic interrupt
 *
 * @param   freq Frequence for periodic interrupt, valid values 0 to 15,
 *          a value greater than 15 will be regarded as 15.
 * @param   state True to enable the alarm and false to disable it.
 */
void snvs_rtc_periodic_interrupt(uint8_t freq, uint8_t state);

/*!
 * @brief Enable or disable secure real time counter
 *
 * @param   state 1 to enable the counter and any other value to disable it.
 */
void snvs_srtc_counter(uint8_t state);

/*!
 * @brief Enable or disable secure time alarm
 *
 * @param   state 1 to enable the alarm and any other value to disable it.
 */
void snvs_srtc_alarm(uint8_t state);

/*!
 * @brief Programs non-secured real time counter
 *
 * @param   count 64-bit integer to program into 47-bit RTC counter register;
 *          only 47-bit LSB will be used
 */
void snvs_rtc_set_counter(uint64_t count);

/*!
 * @brief Sets non-secured RTC time alarm register
 *
 * @param   timeout 64-bit integer to program into 47-bit time alarm register;
 *          only 47-bit LSB will be used
 */
void snvs_rtc_set_alarm_timeout(uint64_t timeout);

/*!
 * @brief Programs secure real time counter
 *
 * @param   count 64-bit integer to program into 47-bit SRTC counter register;
 *          only 47-bit LSB will be used
 */
void snvs_srtc_set_counter(uint64_t count);

/*!
 * @brief Set secured RTC time alarm register
 *
 * @param   timeout 32-bit integer to program into 32-bit time alarm register;
 */
void snvs_srtc_set_alarm_timeout(uint32_t timeout);

#if defined(__cplusplus)
}
#endif

//! @}

#endif //__SNVS_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
