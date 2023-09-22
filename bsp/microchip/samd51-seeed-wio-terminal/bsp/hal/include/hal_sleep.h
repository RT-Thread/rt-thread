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

#ifndef _HAL_SLEEP_H_INCLUDED
#define _HAL_SLEEP_H_INCLUDED

#include <hpl_sleep.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup doc_driver_hal_helper_sleep
 *
 *@{
 */

/**
 * \brief Set the sleep mode of the device and put the MCU to sleep
 *
 * For an overview of which systems are disabled in sleep for the different
 * sleep modes, see the data sheet.
 *
 * \param[in] mode Sleep mode to use
 *
 * \return The status of a sleep request
 * \retval -1 The requested sleep mode was invalid or not available
 * \retval  0 The operation completed successfully, returned after leaving the
 *            sleep
 */
int sleep(const uint8_t mode);

/**
 * \brief Retrieve the current driver version
 *
 * \return Current driver version.
 */
uint32_t sleep_get_version(void);
/**@}*/
#ifdef __cplusplus
}
#endif
#endif /* _HAL_SLEEP_H_INCLUDED */
