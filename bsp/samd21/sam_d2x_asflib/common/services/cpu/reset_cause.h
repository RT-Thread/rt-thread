/**
 * \file
 *
 * \brief CPU reset cause functions
 *
 * Copyright (c) 2010-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef COMMON_DRIVERS_CPU_RESET_CAUSE_H
#define COMMON_DRIVERS_CPU_RESET_CAUSE_H

#include <parts.h>
#include <stdbool.h>

#if XMEGA
# include "xmega_reset_cause.h"
#elif UC3
# include "avr32_reset_cause.h"
#elif SAM4L
# include "sam4l_reset_cause.h"
#else
# error Unsupported chip type
#endif

/**
 * \defgroup reset_cause_group CPU reset cause
 *
 * See \ref reset_cause_quickstart
 *
 * This is a generic interface for getting and clearing the chip reset causes.
 *
 * \section dependencies Dependencies
 *
 * The reset cause interface does not depend on any other modules, as it only
 * accesses a few registers in the device core.
 *
 * On the other hand, the software reset call might depend on \ref sysclk_group
 * to enable the clock to the debug system, for devices doing software reset
 * through the on-chip debug system. This applies only to the 32-bit AVR
 * devices.
 *
 * \section Quick start guide
 * See \ref reset_cause_quickstart
 *
 * @{
 */

/*
 * Sanity check of reset causes, define undefined reset causes to 0. Hence they
 * will always return false when queried.
 */
#ifndef CHIP_RESET_CAUSE_BOD_CPU
/**
 * \brief Brown-out detected on CPU power domain reset cause not available on
 * this chip.
 */
# define CHIP_RESET_CAUSE_BOD_CPU       0
#endif
#ifndef CHIP_RESET_CAUSE_BOD_IO
/**
 * \brief Brown-out detected on I/O power domain reset cause not available on
 * this chip.
 */
# define CHIP_RESET_CAUSE_BOD_IO        0
#endif
#ifndef CHIP_RESET_CAUSE_CPU_ERROR
//! CPU error reset cause not available on this chip.
# define CHIP_RESET_CAUSE_CPU_ERROR     0
#endif
#ifndef CHIP_RESET_CAUSE_EXTRST
//! External reset cause not available on this chip.
# define CHIP_RESET_CAUSE_EXTRST        0
#endif
#ifndef CHIP_RESET_CAUSE_JTAG
//! JTAG reset cause not available on this chip.
# define CHIP_RESET_CAUSE_JTAG          0
#endif
#ifndef CHIP_RESET_CAUSE_OCD
//! On-chip debug system reset cause not available on this chip.
# define CHIP_RESET_CAUSE_OCD           0
#endif
#ifndef CHIP_RESET_CAUSE_POR
//! Power-on-reset reset cause not available on this chip.
# define CHIP_RESET_CAUSE_POR           0
#endif
#ifndef CHIP_RESET_CAUSE_POR_IO
//! Power-on-reset on I/O power domain reset cause not available on this chip.
# define CHIP_RESET_CAUSE_POR_IO           0
#endif
#ifndef CHIP_RESET_CAUSE_SLEEP
//! Wake from Shutdown sleep mode reset cause not available on this chip.
# define CHIP_RESET_CAUSE_SLEEP         0
#endif
#ifndef CHIP_RESET_CAUSE_SOFT
//! Software reset reset cause not available on this chip.
# define CHIP_RESET_CAUSE_SOFT          0
#endif
#ifndef CHIP_RESET_CAUSE_SPIKE
//! Spike detected reset cause not available on this chip.
# define CHIP_RESET_CAUSE_SPIKE         0
#endif
#ifndef CHIP_RESET_CAUSE_WDT
//! Watchdog timeout reset cause not available on this chip.
# define CHIP_RESET_CAUSE_WDT           0
#endif

/**
 * \brief List of reset causes in bit-mask format
 */
enum reset_cause {
	/** \brief Brown-out detected on CPU power domain reset cause */
	RESET_CAUSE_BOD_CPU     = CHIP_RESET_CAUSE_BOD_CPU,
	/** \brief Brown-out detected on I/O power domain reset cause */
	RESET_CAUSE_BOD_IO      = CHIP_RESET_CAUSE_BOD_IO,
	/** \brief CPU error reset cause */
	RESET_CAUSE_CPU_ERROR   = CHIP_RESET_CAUSE_CPU_ERROR,
	/** \brief External reset cause */
	RESET_CAUSE_EXTRST      = CHIP_RESET_CAUSE_EXTRST,
	/** \brief JTAG reset cause */
	RESET_CAUSE_JTAG        = CHIP_RESET_CAUSE_JTAG,
	/** \brief On-chip debug system reset cause */
	RESET_CAUSE_OCD         = CHIP_RESET_CAUSE_OCD,
	/** \brief Power-on-reset reset cause */
	RESET_CAUSE_POR         = CHIP_RESET_CAUSE_POR,
	/** \brief Power-on-reset reset cause */
	RESET_CAUSE_POR_IO         = CHIP_RESET_CAUSE_POR_IO,
	/** \brief Wake from Shutdown sleep mode reset cause */
	RESET_CAUSE_SLEEP       = CHIP_RESET_CAUSE_SLEEP,
	/** \brief Software reset reset cause */
	RESET_CAUSE_SOFT        = CHIP_RESET_CAUSE_SOFT,
	/** \brief Spike detected reset cause */
	RESET_CAUSE_SPIKE       = CHIP_RESET_CAUSE_SPIKE,
	/** \brief Watchdog timeout reset cause */
	RESET_CAUSE_WDT         = CHIP_RESET_CAUSE_WDT,
};

//! \name Management
//@{

/**
 * \fn void reset_do_soft_reset(void)
 * \brief Perform a software reset of the device
 *
 * \note This function will never return.
 * \note This function does not disable interrupts, this is up to the caller to
 *       handle.
 */
/**
 * \fn reset_cause_t reset_cause_get_causes(void)
 * \brief Get all reset causes
 *
 * This function will return a value containing the currently triggered reset
 * cause(s).
 *
 * \return Bit-mask with each active reset cause set to 1.
 */
/**
 * \fn reset_cause_clear_causes(reset_cause_t causes)
 * \brief Clear a bit-mask of reset causes
 *
 * This function will clear the provided reset causes in the reset cause
 * register.
 *
 * \param causes bit-mask of reset causes to clear
 */

//@}

//! \name Specific reset cause helper functions
//@{

/**
 * \brief Check if chip reset was caused by a CPU power brown-out detection
 *
 * \return True if reset was caused by a CPU power brown-out detection
 */
static inline bool reset_cause_is_cpu_brown_out_detected(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_BOD_CPU);
}

/**
 * \brief Check if chip reset was caused by an I/O power brown-out detection
 *
 * \return True if reset was caused by an I/O power brown-out detection
 */
static inline bool reset_cause_is_io_brown_out_detected(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_BOD_IO);
}

/**
 * \brief Check if chip reset was caused by a brown-out detection on any
 * power domain.
 *
 * \return True if reset was caused by a power brown-out detection
 */
static inline bool reset_cause_is_brown_out_detected(void)
{
	return (reset_cause_is_cpu_brown_out_detected() ||
			reset_cause_is_io_brown_out_detected());
}

/**
 * \brief Check if chip reset was caused by a CPU error, illegal access
 *
 * \return True if reset was caused by a CPU error, illegal access
 */
static inline bool reset_cause_is_cpu_error(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_CPU_ERROR);
}

/**
 * \brief Check if chip reset was caused by an external reset
 *
 * \return True if reset was caused by an external reset
 */
static inline bool reset_cause_is_external_reset(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_EXTRST);
}

/**
 * \brief Check if chip reset was caused by a JTAG reset
 *
 * \return True if reset was caused by a JTAG reset
 */
static inline bool reset_cause_is_jtag(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_JTAG);
}

/**
 * \brief Check if chip reset was caused by the on-chip debug system
 *
 * \return True if reset was caused by the on-chip debug system
 */
static inline bool reset_cause_is_ocd(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_OCD);
}

/**
 * \brief Check if chip reset was caused by a power-on-reset
 *
 * \return True if reset was caused by a power-on-reset
 */
static inline bool reset_cause_is_power_on_reset(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_POR);
}

/**
 * \brief Check if chip reset was caused by an I/O power-on-reset
 *
 * \return True if reset was caused by a power-on-reset
 */
static inline bool reset_cause_is_io_power_on_reset(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_POR_IO);
}

/**
 * \brief Check if chip reset was caused by a wake up from shutdown sleep mode
 *
 * \return True if reset was caused by a wake up from shutdown sleep mode
 */
static inline bool reset_cause_is_wake_from_shutdown_sleep(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_SLEEP);
}

/**
 * \brief Check if chip reset was caused by a software reset
 *
 * \return True if reset was caused by a software reset
 */
static inline bool reset_cause_is_software_reset(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_SOFT);
}

/**
 * \brief Check if chip reset was caused by a power spike detection
 *
 * \return True if reset was caused by a spike detection
 */
static inline bool reset_cause_is_spike_detected(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_SPIKE);
}

/**
 * \brief Check if chip reset was caused by a watchdog timeout
 *
 * \return True if reset was caused by a watchdog timeout
 */
static inline bool reset_cause_is_watchdog(void)
{
	return (reset_cause_get_causes() & RESET_CAUSE_WDT);
}

//@}

//! @}

/**
 * \page reset_cause_quickstart Quick start guide for reset cause service
 *
 * This is the quick start guide for the \ref reset_cause_group
 * "Reset Cause service", with step-by-step instructions on how to configure
 * and use the driver in a selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section reset_cause_basic_use_case Basic use case
 * In this basic use case, the reset cause service is used for checking if the
 * last reset was a watchdog reset.
 *
 * \section reset_cause_basic_use_case_setup Setup steps
 *
 * \subsection reset_cause_basic_use_case_setup_code Example code
 * Add to application C-file:
 * \code
	 if (reset_cause_is_watchdog()) {
		// Do action due to last reset being a watchdog reset
		reset_cause_clear_causes(RESET_CAUSE_WDT);
	 }
\endcode
 *
 * \subsection reset_cause_basic_use_case_setup_flow Workflow
 * -# Check for watchdog reset flag:
 *   - \code if (reset_cause_is_watchdog()) { \endcode
 *   - \attention Please consult the specific device datasheet on which reset
 *   causes that are supported.
 * -# Insert your own code taking action here. E.g.: Increase a watchdog reset
 * counter.
 * -# Reset flag if the flag was set to make sure it's not falsely
 * detected in another reset:
 *   - \code reset_cause_clear_causes(RESET_CAUSE_WDT); \endcode
 *
 * \section reset_cause_use_cases Advanced use cases
 * For more advanced use of the Reset Cause service, see the following use cases:
 * - \subpage reset_cause_use_case_1 : Software controlled reset
 */

/**
 * \page reset_cause_use_case_1 Use case #1
 * In this use case, the reset cause service is used to perform a software
 * controlled reset.
 *
 * \section reset_cause_use_case_1_setup Setup steps
 *
 * \subsection reset_cause_use_case_1_setup_flow Workflow
 * -# Call soft reset. This call will not return.
 *   - \code reset_do_soft_reset(); \endcode
 */

#endif /* COMMON_DRIVERS_CPU_RESET_CAUSE_H */
