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
#ifndef _OCOTP_DRV_H_
#define _OCOTP_DRV_H_

/*!
 * @file  ocotp.h
 * @brief Header file with API for the OCOTP driver.
 * @ingroup diag_ocotp
 */

#include "sdk.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define PITC_ERROR_OTP_RW (-1)

#define ERROR_OTP_PROGRAM_HCLK                  (PITC_ERROR_OTP_RW)
//! Could not set VDDIO voltage
#define ERROR_OTP_SET_VOLTAGE                   (PITC_ERROR_OTP_RW-1)
//! OTP Controller is busy
#define ERROR_OTP_CTRL_BUSY                     (PITC_ERROR_OTP_RW-2)
//! OTP Controller is reporting error
#define ERROR_OTP_CTRL_ERROR                    (PITC_ERROR_OTP_RW-3)
//! OTP Controller has timeout on write
#define ERROR_OTP_CTRL_TIMEOUT                  (PITC_ERROR_OTP_RW-4)
//! OTP Controller returns read open
#define ERROR_OTP_RD_BANK_OPEN                  (PITC_ERROR_OTP_RW-5)
//! invalid OTP register
#define ERROR_OTP_INVALID_REGISTER              (PITC_ERROR_OTP_RW-6)

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * Read the value of fuses located at bank/row.
 *
 * @param  bank Bank of the fuse.
 * @param  row Row or word of the fuse.
 * @return The value of the fuses at the given bank and row.
 */
int32_t ocotp_sense_fuse(uint32_t bank, uint32_t row);

/*!
 * Program fuses located at bank/row to value.
 *
 * @param  bank Bank of the fuses.
 * @param  row Row or word of the fuses.
 * @param  value Value to program in fuses.
 */
void ocotp_fuse_blow_row(uint32_t bank, uint32_t row, uint32_t value);

/*!
 * @brief Reload OTP shadow registers.
 *
 * @retval ERROR_OTP_CTRL_BUSY, if busy
 * @retval ERROR_OTP_CTRL_ERROR, if error
 * @retval otherwise SUCCESS
 */
int ocotp_reload_otp_shadow_registers(void);

#if defined(__cplusplus)
extern "C" {
#endif

#endif //_OCOTP_DRV_H_
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
