/**
 * \file
 *
 * \brief Common Delay Service
 *
 * Copyright (c) 2014-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef _DELAY_H_
#define _DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sysclk.h>

#if UC3
#   include <cycle_counter.h>
#elif XMEGA
#   include "xmega/cycle_counter.h"
#elif MEGA
#   include "mega/cycle_counter.h"
#elif SAM
#   include "sam/cycle_counter.h"
#endif

/**
 * @defgroup group_common_services_delay Busy-Wait Delay Routines
 *
 * This module provides simple loop-based delay routines for those
 * applications requiring a brief wait during execution. Common API
 * for UC3, XMEGA, and AVR MEGA.
 *
 * @{
 */

/**
 * @def F_CPU
 * @brief MCU Clock Frequency (Hertz)
 *
 * @deprecated
 * The \ref F_CPU configuration constant is used for compatibility with the
 * \ref group_common_services_delay routines. The common loop-based delay
 * routines are designed to use the \ref clk_group modules while anticipating
 * support for legacy applications assuming a statically defined clock
 * frequency. Applications using a statically configured MCU clock frequency
 * can define \ref F_CPU (Hertz), in which case the common delay routines will
 * use this value rather than calling sysclk_get_cpu_hz() to get the current
 * MCU clock frequency.
 */
#ifndef F_CPU
#       define F_CPU sysclk_get_cpu_hz()
#endif

/**
 * @def delay_init
 *
 * @brief Initialize the delay driver.
 * @param fcpu_hz CPU frequency in Hz
 *
 * @deprecated
 * This function is provided for compatibility with ASF applications that
 * may not have been updated to configure the system clock via the common
 * clock service; e.g. sysclk_init() and a configuration header file are
 * used to configure clocks.
 *
 * The functions in this module call \ref sysclk_get_cpu_hz() function to
 * obtain the system clock frequency.
 */
#define delay_init(fcpu_hz)

/**
 * @def delay_s
 * @brief Delay in seconds.
 * @param delay Delay in seconds
 */
#define delay_s(delay)      ((delay) ? cpu_delay_ms(1000 * delay, F_CPU) : cpu_delay_us(1, F_CPU))

/**
 * @def delay_ms
 * @brief Delay in milliseconds.
 * @param delay Delay in milliseconds
 */
#define delay_ms(delay)     ((delay) ? cpu_delay_ms(delay, F_CPU) : cpu_delay_us(1, F_CPU))

/**
 * @def delay_us
 * @brief Delay in microseconds.
 * @param delay Delay in microseconds
 */
#define delay_us(delay)     ((delay) ? cpu_delay_us(delay, F_CPU) : cpu_delay_us(1, F_CPU))

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _DELAY_H_ */
