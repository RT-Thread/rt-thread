/**
 * \file
 *
 * \brief Time measure related functionality declaration.
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

#ifndef _HPL_TIME_MEASURE_H_INCLUDED
#define _HPL_TIME_MEASURE_H_INCLUDED

/**
 * \addtogroup HPL Time measure
 *
 * \section hpl_time_measure_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief System time type
 */
typedef uint32_t system_time_t;

/**
 * \name HPL functions
 */
//@{
/**
 * \brief Initialize system time module
 *
 * \param[in] hw The pointer to hardware instance to initialize
 */
void _system_time_init(void *const hw);

/**
 * \brief Deinitialize system time module
 *
 * \param[in] hw The pointer to hardware instance to initialize
 */
void _system_time_deinit(void *const hw);

/**
 * \brief Get system time
 *
 * \param[in] hw The pointer to hardware instance to initialize
 */
system_time_t _system_time_get(const void *const hw);

/**
 * \brief Get maximum possible system time
 *
 * \param[in] hw The pointer to hardware instance to initialize
 */
system_time_t _system_time_get_max_time_value(const void *const hw);
//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_TIME_MEASURE_H_INCLUDED */
