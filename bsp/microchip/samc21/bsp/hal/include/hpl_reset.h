/**
 * \file
 *
 * \brief Reset related functionality declaration.
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

#ifndef _HPL_RESET_H_INCLUDED
#define _HPL_RESET_H_INCLUDED

/**
 * \addtogroup HPL Reset
 *
 * \section hpl_reset_rev Revision History
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
 * \brief Reset reason enumeration
 *
 * The list of possible reset reasons.
 */
enum reset_reason {

	RESET_REASON_POR     = 1,
	RESET_REASON_BODCORE = 2,
	RESET_REASON_BODVDD  = 4,
	RESET_REASON_EXT     = 16,
	RESET_REASON_WDT     = 32,
	RESET_REASON_SYST    = 64
};

/**
 * \name HPL functions
 */
//@{
/**
 * \brief Retrieve the reset reason
 *
 * Retrieves the reset reason of the last MCU reset.
 *
 *\return An enum value indicating the reason of the last reset.
 */
enum reset_reason _get_reset_reason(void);

/**
 * \brief Reset MCU
 */
void _reset_mcu(void);
//@}

#ifdef __cplusplus
}
#endif
/**@}*/
#endif /* _HPL_RESET_H_INCLUDED */
