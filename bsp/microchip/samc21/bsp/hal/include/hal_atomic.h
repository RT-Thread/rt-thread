/**
 * \file
 *
 * \brief Critical sections related functionality declaration.
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

#ifndef _HAL_ATOMIC_H_INCLUDED
#define _HAL_ATOMIC_H_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup doc_driver_hal_helper_atomic
 *
 *@{
 */

/**
 * \brief Type for the register holding global interrupt enable flag
 */
typedef uint32_t hal_atomic_t;

/**
 * \brief Helper macro for entering critical sections
 *
 * This macro is recommended to be used instead of a direct call
 * hal_enterCritical() function to enter critical
 * sections. No semicolon is required after the macro.
 *
 * \section atomic_usage Usage Example
 * \code
 * CRITICAL_SECTION_ENTER()
 * Critical code
 * CRITICAL_SECTION_LEAVE()
 * \endcode
 */
#define CRITICAL_SECTION_ENTER()                                                                                       \
	{                                                                                                                  \
		volatile hal_atomic_t __atomic;                                                                                \
		atomic_enter_critical(&__atomic);

/**
 * \brief Helper macro for leaving critical sections
 *
 * This macro is recommended to be used instead of a direct call
 * hal_leaveCritical() function to leave critical
 * sections. No semicolon is required after the macro.
 */
#define CRITICAL_SECTION_LEAVE()                                                                                       \
	atomic_leave_critical(&__atomic);                                                                                  \
	}

/**
 * \brief Disable interrupts, enter critical section
 *
 * Disables global interrupts. Supports nested critical sections,
 * so that global interrupts are only re-enabled
 * upon leaving the outermost nested critical section.
 *
 * \param[out] atomic The pointer to a variable to store the value of global
 * interrupt enable flag
 */
void atomic_enter_critical(hal_atomic_t volatile *atomic);

/**
 * \brief Exit atomic section
 *
 * Enables global interrupts. Supports nested critical sections,
 * so that global interrupts are only re-enabled
 * upon leaving the outermost nested critical section.
 *
 * \param[in] atomic The pointer to a variable, which stores the latest stored
 * value of the global interrupt enable flag
 */
void atomic_leave_critical(hal_atomic_t volatile *atomic);

/**
 * \brief Retrieve the current driver version
 *
 * \return Current driver version.
 */
uint32_t atomic_get_version(void);
/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* _HAL_ATOMIC_H_INCLUDED */
