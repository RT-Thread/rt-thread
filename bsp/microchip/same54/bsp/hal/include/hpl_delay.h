/**
 * \file
 *
 * \brief Delay related functionality declaration.
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

#ifndef _HPL_DELAY_H_INCLUDED
#define _HPL_DELAY_H_INCLUDED

/**
 * \addtogroup HPL Delay
 *
 * \section hpl_delay_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#ifndef _UNIT_TEST_
#include <compiler.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name HPL functions
 */
//@{

/**
 * \brief Initialize delay functionality
 *
 * \param[in] hw The pointer to hardware instance
 */
void _delay_init(void *const hw);

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of us
 *
 * \param[in] us The amount of us to delay for
 *
 * \return The amount of cycles
 */
uint32_t _get_cycles_for_us(const uint16_t us);

/**
 * \brief Retrieve the amount of cycles to delay for the given amount of ms
 *
 * \param[in] ms The amount of ms to delay for
 *
 * \return The amount of cycles
 */
uint32_t _get_cycles_for_ms(const uint16_t ms);

/**
 * \brief Delay loop to delay n number of cycles
 *
 * \param[in] hw The pointer to hardware instance
 * \param[in] cycles The amount of cycles to delay for
 */
void _delay_cycles(void *const hw, uint32_t cycles);
//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_DELAY_H_INCLUDED */
