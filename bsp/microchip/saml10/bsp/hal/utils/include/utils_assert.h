/**
 * \file
 *
 * \brief Asserts related functionality.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#ifndef _ASSERT_H_INCLUDED
#define _ASSERT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>

#ifndef USE_SIMPLE_ASSERT
//# define USE_SIMPLE_ASSERT
#endif

/**
 * \brief Assert macro
 *
 * This macro is used to throw asserts. It can be mapped to different function
 * based on debug level.
 *
 * \param[in] condition A condition to be checked;
 *                      assert is thrown if the given condition is false
 */
#define ASSERT(condition) ASSERT_IMPL((condition), __FILE__, __LINE__)

#ifdef DEBUG

#ifdef USE_SIMPLE_ASSERT
#define ASSERT_IMPL(condition, file, line)                                                                             \
	if (!(condition))                                                                                                  \
		__asm("BKPT #0");
#else
#define ASSERT_IMPL(condition, file, line) assert((condition), file, line)
#endif

#else /* DEBUG */

#ifdef USE_SIMPLE_ASSERT
#define ASSERT_IMPL(condition, file, line) ((void)0)
#else
#define ASSERT_IMPL(condition, file, line) ((void)0)
#endif

#endif /* DEBUG */

/**
 * \brief Assert function
 *
 * This function is used to throw asserts.
 *
 * \param[in] condition A condition to be checked; assert is thrown if the given
 *                      condition is false
 * \param[in] file File name
 * \param[in] line Line number
 */
void assert(const bool condition, const char *const file, const int line);

#ifdef __cplusplus
}
#endif
#endif /* _ASSERT_H_INCLUDED */
