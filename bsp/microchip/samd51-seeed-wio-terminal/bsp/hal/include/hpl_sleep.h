/**
 * \file
 *
 * \brief Sleep related functionality declaration.
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

#ifndef _HPL_SLEEP_H_INCLUDED
#define _HPL_SLEEP_H_INCLUDED

/**
 * \addtogroup HPL Sleep
 *
 * \section hpl_sleep_rev Revision History
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
 * \brief Set the sleep mode for the device
 *
 * This function sets the sleep mode for the device.
 * For an overview of which systems are disabled in sleep for the different
 * sleep modes see datasheet.
 *
 * \param[in] mode Sleep mode to use
 *
 * \return the status of a sleep request
 * \retval -1 The requested sleep mode was invalid
 * \retval  0 The operation completed successfully, sleep mode is set
 */
int32_t _set_sleep_mode(const uint8_t mode);

/**
 * \brief Reset MCU
 */
void _reset_mcu(void);

/**
 * \brief Put MCU to sleep
 */
void _go_to_sleep(void);
//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_SLEEP_H_INCLUDED */
