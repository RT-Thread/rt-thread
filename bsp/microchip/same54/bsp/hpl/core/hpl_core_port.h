/**
 * \file
 *
 * \brief Core related functionality implementation.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _HPL_CORE_PORT_H_INCLUDED
#define _HPL_CORE_PORT_H_INCLUDED

#include <peripheral_clk_config.h>

/* It's possible to include this file in ARM ASM files (e.g., in FreeRTOS IAR
 * portable implement, portasm.s -> FreeRTOSConfig.h -> hpl_core_port.h),
 * there will be assembling errors.
 * So the following things are not included for assembling.
 */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#ifndef _UNIT_TEST_
#include <compiler.h>
#endif

/**
 * \brief Check if it's in ISR handling
 * \return \c true if it's in ISR
 */
static inline bool _is_in_isr(void)
{
	return (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk);
}

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _HPL_CORE_PORT_H_INCLUDED */
