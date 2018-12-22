/**
 * \file
 *
 * \brief SAM True Random Number Generator (TRNG) Driver
 *
 * Copyright (C) 2014-2016 Atmel Corporation. All rights reserved.
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

#ifndef TRNG_H_INCLUDED
#define TRNG_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_trng_group SAM True Random Number Generator (TRNG) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for the configuration
 * and management of the device's True Random Number Generator functionality.
 *
 * The following driver API modes are covered by this manual:
 * - Polled APIs
 * \if TRNG_CALLBACK_MODE
 * - Callback APIs
 * \endif
 *
 * The following peripheral is used by this module:
 *  - TRNG (True Random Number Generator)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM L21/L22
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_trng_prerequisites
 *  - \ref asfdoc_sam0_trng_module_overview
 *  - \ref asfdoc_sam0_trng_special_considerations
 *  - \ref asfdoc_sam0_trng_extra_info
 *  - \ref asfdoc_sam0_trng_examples
 *  - \ref asfdoc_sam0_trng_api_overview
 *
 *
 * \section asfdoc_sam0_trng_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_trng_module_overview Module Overview
 *
 * This driver provides an interface for the TRNG functions on the device.
 *
 * As soon as the TRNG is enabled, the module provides a new 32-bit random
 * data, for every 84 CLK_TRNG_APB clock cycles.
 *
 *
 * \section asfdoc_sam0_trng_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 *
 * \section asfdoc_sam0_trng_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_trng_extra. This includes:
 *  - \ref asfdoc_sam0_trng_extra_acronyms
 *  - \ref asfdoc_sam0_trng_extra_dependencies
 *  - \ref asfdoc_sam0_trng_extra_errata
 *  - \ref asfdoc_sam0_trng_extra_history
 *
 *
 * \section asfdoc_sam0_trng_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_trng_exqsg.
 *
 *
 * \section asfdoc_sam0_trng_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system.h>

#ifdef __cplusplus
extern "C" {
#endif

#if TRNG_CALLBACK_MODE == true
/* Forward declaration of struct */
struct trng_module;

extern struct trng_module *_trng_instance;

/** Type definition for a TRNG module callback function. */
typedef void (*trng_callback_t)(struct trng_module *const module_inst);

/** Enum for possible callback types for the TRNG module. */
enum trng_callback {
	/** Callback for specific number of random data ready */
	TRNG_CALLBACK_READ_BUFFER = 0,
	/** Number of available callbacks */
#if !defined(__DOXYGEN__)
	TRNG_CALLBACK_N,
#endif
};
#endif

/**
 * \brief TRNG software device instance structure.
 *
 * TRNG software instance structure, used to retain software state information
 * of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct trng_module {
#if !defined(__DOXYGEN__)
	/** Hardware module pointer of the associated TRNG peripheral */
	Trng *hw;
#  if TRNG_CALLBACK_MODE == true
	/** Array of callbacks */
	trng_callback_t callback[TRNG_CALLBACK_N];
	/** Bit mask for callbacks registered */
	uint8_t register_callback_mask;
	/** Bit mask for callbacks enabled */
	uint8_t enable_callback_mask;
	/** Holds the status of the ongoing or last read job */
	volatile enum status_code job_status;
	/** Pointer to buffer used for TRNG results */
	volatile uint32_t *job_buffer;
	/** Remaining number of TRNG results in current job */
	volatile uint32_t remaining_number;
#  endif
#endif
};

/**
 * \brief TRNG module configuration structure.
 *
 *  Configuration structure for a True Random Number Generator.
 */
struct trng_config {
	/** If \c true, the True Random Number Generator will not be stopped in
	 *  standby sleep mode */
	bool run_in_standby;
};

/**
 * \brief TRNG event enable/disable structure.
 *
 * Event flags for the TRNG module. This is used to enable and
 * disable events via \ref trng_enable_events() and \ref trng_disable_events().
 */
struct trng_events {
	/** Enable event generation on random data ready */
	bool generate_event_on_data_ready;
};


/**
 * \name Driver Initialization and Configuration
 * @{
 */
enum status_code trng_init(
		struct trng_module *const module_inst,
		Trng *const hw,
		struct trng_config *const config);

/**
 * \brief Initializes all members of a TRNG configuration structure
 *  to safe defaults.
 *
 *  Initializes all members of a given True Random Number Generator configuration
 *  structure to safe known default values. This function should be called on
 *  all new instances of these configuration structures before being modified
 *  by the user application.
 *
 *  The default configuration is as follows:
 *   \li True Random Number Generator will not be stopped in standby sleep mode
 *
 *  \param[out] config  Configuration structure to initialize to default values
 */
static inline void trng_get_config_defaults(
		struct trng_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Default configuration values */
	config->run_in_standby = false;
}

/**
 * \brief Enables a TRNG that was previously configured.
 *
 * Enables True Random Number Generator that was previously configured via a
 * call to \ref trng_init().
 *
 * \param[in] module_inst  Software instance for the True Random Number
 *                         Generator peripheral
 */
static inline void trng_enable(
		struct trng_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Trng *const trng_module = module_inst->hw;

	/* Enable TRNG */
	trng_module->CTRLA.reg |= TRNG_CTRLA_ENABLE;
}

/**
 * \brief Disables a TRNG that was previously enabled.
 *
 * Disables True Random Number Generator that was previously started via a call
 * to \ref trng_enable().
 *
 * \param[in] module_inst  Software instance for the True Random Number
 *                         Generator peripheral
 */
static inline void trng_disable(
		struct trng_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Trng *const trng_module = module_inst->hw;

	/* Disbale interrupt */
	trng_module->INTENCLR.reg = TRNG_INTENCLR_MASK;
	/* Clear interrupt flag */
	trng_module->INTFLAG.reg = TRNG_INTFLAG_MASK;

	/* Disable TRNG */
	trng_module->CTRLA.reg &= ~TRNG_CTRLA_ENABLE;
}

/**
 * \brief Enables a TRNG event output.
 *
 *  Enables output events from the True Random Number Generator
 *  module. See \ref Section Struct trng_events for a list of events this module
 *  supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in] module_inst  Software instance for the TRNG peripheral
 *  \param[in] events       Struct containing flags of events to enable
 */
static inline void trng_enable_events(
		struct trng_module *const module_inst,
		struct trng_events *const events)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Trng *const trng_module = module_inst->hw;

	if (events->generate_event_on_data_ready) {
		/* Enable data ready event output */
		trng_module->EVCTRL.reg |= TRNG_EVCTRL_DATARDYEO;
	}
}

/**
 * \brief Disables a TRNG event output.
 *
 *  Disables output events from the True Random Number Generator
 *  module. See \ref Section Struct trng_events for a list of events
 *  this module supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in] module_inst  Software instance for the TRNG peripheral
 *  \param[in] events       Struct containing flags of events to disable
 */
static inline void trng_disable_events(
		struct trng_module *const module_inst,
		struct trng_events *const events)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Trng *const trng_module = module_inst->hw;

	if (events->generate_event_on_data_ready) {
		/* Disable data ready event output */
		trng_module->EVCTRL.reg &= ~TRNG_EVCTRL_DATARDYEO;
	}
}
/** @} */

/**
 * \name Read TRNG Result
 * @{
 */

/**
 * \brief Read the random data result
 *
 * Reads the random data result.
 *
 * \param[in]  module_inst  Pointer to the TRNG software instance struct
 * \param[out] result       Pointer to store the result value in
 *
 * \return Status of the TRNG read request.
 * \retval STATUS_OK           The result was retrieved successfully
 * \retval STATUS_BUSY         A random result was not ready
 */
static inline enum status_code trng_read(
		struct trng_module *const module_inst,
		uint32_t *result)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(result);

	Trng *const trng_hw = module_inst->hw;

	if (!(trng_hw->INTFLAG.reg & TRNG_INTFLAG_DATARDY)) {
		/* Result not ready */
		return STATUS_BUSY;
	}

	/* Get randomly generated output data (it will clear data ready flag) */
	*result = trng_hw->DATA.reg;

	return STATUS_OK;
}
/** @} */

#ifdef __cplusplus
}
#endif

/** @} */

/**
 * \page asfdoc_sam0_trng_extra Extra Information for TRNG Driver
 *
 * \section asfdoc_sam0_trng_extra_acronyms Acronyms
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *  <tr>
 *		<td>TRNG</td>
 *		<td>True Random Number Generator</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_trng_extra_dependencies Dependencies
 * This driver has no dependencies.
 *
 *
 * \section asfdoc_sam0_trng_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_trng_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
  *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_trng_exqsg Examples for TRNG Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_trng_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_trng_basic_use_case
 * \if TRNG_CALLBACK_MODE
 *  - \subpage asfdoc_sam0_trng_basic_use_case_callback
 * \endif
 *
 * \page asfdoc_sam0_trng_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42444B</td>
 *		<td>01/2016</td>
 *		<td>Added support for SAM L22</td>
 *	</tr>
 *	<tr>
 *		<td>42444A</td>
 *		<td>06/2015</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */

#endif /* TRNG_H_INCLUDED */

