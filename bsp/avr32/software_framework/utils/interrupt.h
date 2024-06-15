/**
 * \file
 *
 * \brief Global interrupt management for 8- and 32-bit AVR
 *
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef UTILS_INTERRUPT_H
#define UTILS_INTERRUPT_H

#include <parts.h>

#if XMEGA || MEGA
#  include "interrupt/interrupt_avr8.h"
#elif UC3
#  include "interrupt/interrupt_avr32.h"
#elif SAM || SAMB
#  include "interrupt/interrupt_sam_nvic.h"
#else
#  error Unsupported device.
#endif

/**
 * \defgroup interrupt_group Global interrupt management
 *
 * This is a driver for global enabling and disabling of interrupts.
 *
 * @{
 */

#if defined(__DOXYGEN__)
/**
 * \def CONFIG_INTERRUPT_FORCE_INTC
 * \brief Force usage of the ASF INTC driver
 *
 * Predefine this symbol when preprocessing to force the use of the ASF INTC driver.
 * This is useful to ensure compatibility across compilers and shall be used only when required
 * by the application needs.
 */
#  define CONFIG_INTERRUPT_FORCE_INTC
#endif

//! \name Global interrupt flags
//@{
/**
 * \typedef irqflags_t
 * \brief Type used for holding state of interrupt flag
 */

/**
 * \def cpu_irq_enable
 * \brief Enable interrupts globally
 */

/**
 * \def cpu_irq_disable
 * \brief Disable interrupts globally
 */

/**
 * \fn irqflags_t cpu_irq_save(void)
 * \brief Get and clear the global interrupt flags
 *
 * Use in conjunction with \ref cpu_irq_restore.
 *
 * \return Current state of interrupt flags.
 *
 * \note This function leaves interrupts disabled.
 */

/**
 * \fn void cpu_irq_restore(irqflags_t flags)
 * \brief Restore global interrupt flags
 *
 * Use in conjunction with \ref cpu_irq_save.
 *
 * \param flags State to set interrupt flag to.
 */

/**
 * \fn bool cpu_irq_is_enabled_flags(irqflags_t flags)
 * \brief Check if interrupts are globally enabled in supplied flags
 *
 * \param flags Currents state of interrupt flags.
 *
 * \return True if interrupts are enabled.
 */

/**
 * \def cpu_irq_is_enabled
 * \brief Check if interrupts are globally enabled
 *
 * \return True if interrupts are enabled.
 */
//@}

//! @}

/**
 * \ingroup interrupt_group
 * \defgroup interrupt_deprecated_group Deprecated interrupt definitions
 */

#endif /* UTILS_INTERRUPT_H */
