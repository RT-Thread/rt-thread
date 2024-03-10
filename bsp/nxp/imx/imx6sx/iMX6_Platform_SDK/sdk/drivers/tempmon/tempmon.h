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
#if !defined(__tempmon_h__)
#define __tempmon_h__

#include "sdk.h"

//! @addtogroup tempmon
//! @{

//////////////////////////////////////////////////////////////////////////////////////////
// Types
//////////////////////////////////////////////////////////////////////////////////////////

//! @brief Callback prototype used for the temperature alarm.
typedef void (*tempmon_alarm_callback_t)(float temperature);

//////////////////////////////////////////////////////////////////////////////////////////
// API
//////////////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif


//! @brief Initialize the tempmon driver.
//!
//! @retval SUCCESS Driver was initialized successfully.
int tempmon_init(void);

//! @brief Read the current on-die temperature.
//!
//! @return The temperature of the die in degrees C.
float tempmon_get_temp(void);

//! @brief Enable the over-temperature alarm.
//!
//! @param period Measurement period in milliseconds. The maximum period is 2 seconds, and if the
//!     provided value is over this maximum then a period of 2 seconds will be used instead.
//! @param alarmTemp The alarm temperature in degrees C. When the current temperature rises above
//!     this value, an over-temperature alarm interrupt will be raised and the @a alarmCallback
//!     will be invoked.
//! @param alarmCallback Pointer to the function to be called when the current temperature rises
//!     above @a alarmTemp.
void tempmon_set_alarm(uint32_t period, float alarmTemp, tempmon_alarm_callback_t alarmCallback);

//! @brief Disable the over-temperature alarm.
//!
//! Does nothing if the alarm was not previously enabled.
void tempmon_disable_alarm(void);


#if defined(__cplusplus)
}
#endif

//! @}

#endif // __tempmon_h__
//////////////////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////////////////
