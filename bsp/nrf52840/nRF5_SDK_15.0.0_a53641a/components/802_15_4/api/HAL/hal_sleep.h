/**
 * Copyright (c) 2016 - 2018 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef HAL_SLEEP_H_INCLUDED
#define HAL_SLEEP_H_INCLUDED

#include <stdint.h>

/** @file
 * This file contains declaration of the HAL sleep interface.
 *
 * @defgroup hal_sleep HAL Sleep API
 * @ingroup hal_15_4
 * @{
 * @brief Module to declare HAL Sleep API
 * @details The Sleep module implements the only hal_sleep() routine to put the hardware to the sleep mode for some
 * milliseconds. The user can use convenient macros DAYS_TO_MS(), HOURS_TO_MS(), MINS_TO_MS(), and SEC_TO_MS()
 * to convert different time periods into milliseconds. Please note that this module requires a call to
 * hal_sleep_init() which is in turn called by sys_init() before using any module routines. This module is
 * only used to implement the System Sleep interface. The hal_sleep() routine is not assumed to be used by
 * the user explicitly.
 */

/**@brief Converts days to milliseconds */
#define DAYS_TO_MS(d)   ((d) * 3600L * 24L   * 1000L )

/**@brief Converts hours to milliseconds */
#define HOURS_TO_MS(h)  ((h) * 3600L * 1000L )

/**@brief Converts minutes to milliseconds */
#define MINS_TO_MS(m)   ((m) * 60L   * 1000L )

/**@brief Converts seconds to milliseconds */
#define SEC_TO_MS(s)    ((s) * 1000L )

/**@brief   Information, provided by the HAL, in order to explain the reason,
 *          which caused the system to wake up.
 */
typedef enum
{
    UNKNOWN_INTERRUPT, /**< HAL can't define a wake up reason */
    RTC_CC_INTERRUPT   /**< RTC interrupt was the awakening reason */
} hal_wakeup_reason_t;


/**@brief   Puts hardware into the sleep mode for some milliseconds.
 *
 * @param[in]  sleep_time_ms     Time to sleep in ms
 *
 * @retval     wakeup_reason     Specifies reason of awakening
 */
hal_wakeup_reason_t hal_sleep(uint32_t sleep_time_ms);


/**@brief   Initialization of the sleep module
 *
 */
void hal_sleep_init(void);

/** @} */

#endif /* HAL_SLEEP_H_INCLUDED */
