/**
 * \file
 *
 * \brief INTC software driver API for AVR UC3 devices.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _INTC_H_
#define _INTC_H_

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup intc_group INTC Software Driver API for AVR UC3
 *
 * This is a software module to register interrupt handlers at any specified
 * interrupt level to any interrupt line managed by the INTC module in AVR UC3
 * devices.
 * @{
 */

//! Maximal number of interrupt request lines per group.
#define AVR32_INTC_MAX_NUM_IRQS_PER_GRP      32

//! Number of interrupt priority levels.
#define AVR32_INTC_NUM_INT_LEVELS            (1 << AVR32_INTC_IPR_INTLEVEL_SIZE)


#ifdef __AVR32_ABI_COMPILER__
// (Automatically defined when compiling for AVR UC3, not when assembling).

extern void INTC_init_interrupts(void);
extern void INTC_register_interrupt(__int_handler handler, uint32_t irq,
		uint32_t int_level);

#endif  // __AVR32_ABI_COMPILER__

//! @}

#ifdef __cplusplus
}
#endif

#endif  // _INTC_H_
