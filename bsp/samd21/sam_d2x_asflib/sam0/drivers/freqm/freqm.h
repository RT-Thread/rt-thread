/**
 * \file
 *
 * \brief SAM Frequency Meter (FREQM) Driver
 *
 * Copyright (C) 2015-2016 Atmel Corporation. All rights reserved.
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

#ifndef FREQM_H_INCLUDED
#define FREQM_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_freqm_group SAM Frequency Meter (FREQM) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for the configuration
 * and management of the device's Frequency Meter functionality.
 *
 * The following driver API modes are covered by this manual:
 * - Polled APIs
 * \if FREQM_CALLBACK_MODE
 * - Callback APIs
 * \endif
 *
 * The following peripheral is used by this module:
 *  - FREQM (Frequency Meter)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM L22
 *  - Atmel | SMART SAM C20
 *  - Atmel | SMART SAM C21
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_freqm_prerequisites
 *  - \ref asfdoc_sam0_freqm_module_overview
 *  - \ref asfdoc_sam0_freqm_special_considerations
 *  - \ref asfdoc_sam0_freqm_extra_info
 *  - \ref asfdoc_sam0_freqm_examples
 *  - \ref asfdoc_sam0_freqm_api_overview
 *
 *
 * \section asfdoc_sam0_freqm_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_freqm_module_overview Module Overview
 *
 * The module accurately measures the frequency of a clock by comparing it to a
 * known reference clock as soon as the FREQM is enabled. Two generic clocks are
 * used by the FREQM. The frequency of the measured clock is:
 * \f[
 *    f_{CLK\_MSR} = \frac{VALUE}{REFNUM} \times f_{CLK\_REF}
 * \f]
 * Ratio can be measured with 24-bit accuracy.
 *
 * The FREQM has one interrupt source, which generates when a frequency measurement
 * is done. It can be used to wake up the device from sleep modes.
 *
 * This driver provides an interface for the FREQM functions on the device.
 *
 * \section asfdoc_sam0_freqm_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 *
 * \section asfdoc_sam0_freqm_extra_info Extra Information
 *
 * For extra information see \ref asfdoc_sam0_freqm_extra. This includes:
 *  - \ref asfdoc_sam0_freqm_extra_acronyms
 *  - \ref asfdoc_sam0_freqm_extra_dependencies
 *  - \ref asfdoc_sam0_freqm_extra_errata
 *  - \ref asfdoc_sam0_freqm_extra_history
 *
 *
 * \section asfdoc_sam0_freqm_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_freqm_exqsg.
 *
 *
 * \section asfdoc_sam0_freqm_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system.h>

#ifdef __cplusplus
extern "C" {
#endif

#if FREQM_CALLBACK_MODE == true
/** Forward declaration of struct */
struct freqm_module;

extern struct freqm_module *_freqm_instance;

/** Type definition for a FREQM module callback function. */
typedef void (*freqm_callback_t)(void);

/** Enum for possible callback types for the FREQM module. */
enum freqm_callback {
	/** Callback for measurement done */
	FREQM_CALLBACK_DONE = 0,
	/** Number of available callbacks */
#if !defined(__DOXYGEN__)
	FREQM_CALLBACK_N,
#endif
};
#endif

/**
 * \brief FREQM software device instance structure.
 *
 * FREQM software instance structure, used to retain software state information
 * of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct freqm_module {
#if !defined(__DOXYGEN__)
	/** Hardware module pointer of the associated FREQM peripheral */
	Freqm *hw;
	/** The frequency of reference clock in Hz*/
	uint32_t ref_clock_freq;
#  if FREQM_CALLBACK_MODE == true
	/** Array of callbacks */
	freqm_callback_t callback[FREQM_CALLBACK_N];
#  endif
#endif
};

/** Enum for the possible status types for the FREQM module. */
enum freqm_status {
	/** FREQM measurement is finish */
	FREQM_STATUS_MEASURE_DONE =  0,
	/** FREQM measurement is ongoing or not */
	FREQM_STATUS_MEASURE_BUSY =  1,
	/** FREQM sticky count value overflow */
	FREQM_STATUS_CNT_OVERFLOW =  2,
};

/**
 * \brief FREQM module configuration structure.
 *
 *  Configuration structure for a Frequency Meter.
 */
struct freqm_config {
	/** GCLK source select for measurement */
	enum gclk_generator msr_clock_source;
	/** GCLK source select for reference */
	enum gclk_generator ref_clock_source;
	/** Measurement duration in number of reference clock cycles. Range 1~255 */
	uint16_t ref_clock_circles;
};

/**
 * \brief Determines if the hardware module(s) are currently synchronizing to the bus.
 *
 * Checks to see if the underlying hardware peripheral module(s) are currently
 * synchronizing across multiple clock domains to the hardware bus. This
 * function can be used to delay further operations on a module until such time
 * that it is ready, to prevent blocking delays for synchronization in the
 * user application.
 *
 * \return Synchronization status of the underlying hardware module(s).
 *
 * \retval false If the module has completed synchronization
 * \retval true If the module synchronization is ongoing
 */
static inline bool freqm_is_syncing(void)
{
	Freqm *const freqm_module = FREQM;

	if (freqm_module->SYNCBUSY.reg) {
		return true;
	}

	return false;
}

/**
 * \name Driver Initialization and Configuration
 * @{
 */
enum status_code freqm_init(
		struct freqm_module *const module_inst,
		Freqm *const hw,
		struct freqm_config *const config);

/**
 * \brief Initializes all members of a FREQM configuration structure
 *  to safe defaults.
 *
 *  Initializes all members of a given Frequency Meter configuration
 *  structure to safe known default values. This function should be called on
 *  all new instances of these configuration structures before being modified
 *  by the user application.
 *
 *  The default configuration is as follows:
 *   \li Measurement clock source is GCLK0
 *   \li Reference clock source is GCLK1
 *   \li Frequency Meter Reference Clock Cycles 127
 *
 *  \param[in] config  Configuration structure to initialize to default values
 */
static inline void freqm_get_config_defaults(
		struct freqm_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Default configuration values */
	config->msr_clock_source = GCLK_GENERATOR_0;
	config->ref_clock_source = GCLK_GENERATOR_1;
	config->ref_clock_circles = 127;
}

/**
 * \brief Enables a FREQM that was previously configured.
 *
 * Enables Frequency Meter that was previously configured via a
 * call to \ref freqm_init().
 *
 * \param[in] module_inst  Software instance for the Frequency Meter peripheral
 */
static inline void freqm_enable(
		struct freqm_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Freqm *const freqm_module = module_inst->hw;

	/* Enable FREQM */
	freqm_module->CTRLA.reg |= FREQM_CTRLA_ENABLE;

	while (freqm_is_syncing()) {
		/* Wait for all hardware modules to complete synchronization */
	}
}

/**
 * \brief Disables a FREQM that was previously enabled.
 *
 * Disables Frequency Meter that was previously started via a call
 * to \ref freqm_enable().
 *
 * \param[in] module_inst  Software instance for the Frequency Meter peripheral
 */
static inline void freqm_disable(
		struct freqm_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Freqm *const freqm_module = module_inst->hw;

	/* Disbale interrupt */
	freqm_module->INTENCLR.reg = FREQM_INTENCLR_MASK;
	/* Clear interrupt flag */
	freqm_module->INTFLAG.reg = FREQM_INTFLAG_MASK;

	/* Disable FREQM */
	freqm_module->CTRLA.reg &= ~FREQM_CTRLA_ENABLE;

	while (freqm_is_syncing()) {
		/* Wait for all hardware modules to complete synchronization */
	}
}

/** @} */

/**
 * \name Read FREQM Result
 * @{
 */
/**
 * \brief Start a manual measurement process.
 *
 * \param[in] module Pointer to the FREQM software instance struct
 */
static inline void freqm_start_measure(struct freqm_module *const module)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	/* Trigger measurement */
	module->hw->CTRLB.reg |= FREQM_CTRLB_START;
}

/**
 * \brief Clears module overflow flag.
 *
 * Clears the overflow flag of the module.
 *
 * \param[in] module Pointer to the FREQM software instance struct
 */
static inline void freqm_clear_overflow(struct freqm_module *const module)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	/* Clear overflow flag */
	module->hw->STATUS.reg = FREQM_STATUS_OVF;
}

enum freqm_status freqm_get_result_value(
		struct freqm_module *const module_inst, uint32_t *result);

/** @} */

#ifdef __cplusplus
}
#endif
/** @} */


/**
 * \page asfdoc_sam0_freqm_extra Extra Information for FREQM Driver
 *
 * \section asfdoc_sam0_freqm_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *  <tr>
 *		<td>FREQM</td>
 *		<td>Frequency Meter</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_freqm_extra_dependencies Dependencies
 * This driver has no dependencies.
 *
 *
 * \section asfdoc_sam0_freqm_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_freqm_extra_history Module History
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
 * \page asfdoc_sam0_freqm_exqsg Examples for FREQM Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_freqm_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_freqm_basic_use_case
 * \if FREQM_CALLBACK_MODE
 *  - \subpage asfdoc_sam0_freqm_basic_use_case_callback
 * \endif
 *
 * \page asfdoc_sam0_freqm_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42506A</td>
 *		<td>08/2015</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */

#endif /* FREQM_H_INCLUDED */

