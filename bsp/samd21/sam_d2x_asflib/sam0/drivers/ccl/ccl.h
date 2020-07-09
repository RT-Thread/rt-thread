/**
 * \file
 *
 * \brief SAM Configurable Custom Logic (CCL) Driver
 *
 * Copyright (C) 2014-2015 Atmel Corporation. All rights reserved.
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

#ifndef CCL_H_INCLUDED
#define CCL_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_ccl_group SAM Configurable Custom Logic (CCL) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for the configuration
 * and management of the device's Configurable Custom Logic functionality.
 *
 * The following peripheral is used by this module:
 *  - CCL (Configurable Custom Logic)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM L21/L22
 *  - Atmel | SMART SAM C20/C21
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_ccl_prerequisites
 *  - \ref asfdoc_sam0_ccl_module_overview
 *  - \ref asfdoc_sam0_ccl_special_considerations
 *  - \ref asfdoc_sam0_ccl_extra_info
 *  - \ref asfdoc_sam0_ccl_examples
 *  - \ref asfdoc_sam0_ccl_api_overview
 *
 *
 * \section asfdoc_sam0_ccl_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_ccl_module_overview Module Overview
 *
 * This driver provides an interface for the Configurable Custom Logic
 * functions on the device.
 *
 * The Configurable Custom Logic (CCL) contains programmable logic
 * which can be connected to the device pins, events, or internal peripherals.
 *
 * Each LUT consists of three inputs, a truth table and optional synchronizer,
 * filter and edge detector. Each LUT can generate an output as a user programmable
 * logic expression with three inputs.
 *
 * The output can be combinatorially generated from the inputs, or filtered to remove spike.
 * An optional sequential module can be enabled. The inputs of sequential module are
 * individually controlled by two independent, adjacent LUT(LUT0/LUT1, LUT2/LUT3 etc.) outputs,
 * enabling complex waveform generation.
 *
 * \section asfdoc_sam0_ccl_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 *
 * \section asfdoc_sam0_ccl_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_ccl_extra. This includes:
 *  - \ref asfdoc_sam0_ccl_extra_acronyms
 *  - \ref asfdoc_sam0_ccl_extra_dependencies
 *  - \ref asfdoc_sam0_ccl_extra_errata
 *  - \ref asfdoc_sam0_ccl_extra_history
 *
 *
 * \section asfdoc_sam0_ccl_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_ccl_exqsg.
 *
 *
 * \section asfdoc_sam0_ccl_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief CCL LUT(look up table) ID number enum.
 */
enum ccl_lut_id {
	/** CCL LUT 0 */
	CCL_LUT_0 = 0,
	/** CCL LUT 1 */
	CCL_LUT_1 = 1,
	/** CCL LUT 2 */
	CCL_LUT_2 = 2,
	/** CCL LUT 3 */
	CCL_LUT_3 = 3,
};

/**
 * \brief CCL sequential module ID number enum.
 */
enum ccl_seq_id {
	/** CCL SEQ 0 */
	CCL_SEQ_0 = 0,
	/** CCL SEQ 1 */
	CCL_SEQ_1 = 1,
};

/**
 * \brief Sequential selection enum.
 *
 * Enum for the sequential selection configuration.
 */
enum ccl_seq_selection {
	/** Sequential logic is disabled */
	CCL_SEQ_DISABLED = CCL_SEQCTRL_SEQSEL_DISABLE,
	/** D flip flop */
	CCL_SEQ_D_FLIP_FLOP = CCL_SEQCTRL_SEQSEL_DFF,
	/** JK flip flop */
	CCL_SEQ_JK_FLIP_FLOP = CCL_SEQCTRL_SEQSEL_JK,
	/** D latch */
	CCL_SEQ_D_LATCH = CCL_SEQCTRL_SEQSEL_LATCH,
	/** RS latch */
	CCL_SEQ_RS_LATCH = CCL_SEQCTRL_SEQSEL_RS,
};

/**
 * \brief LUT Input source selection configuration enum.
 *
 * Enum for the LUT Input source selection.
 */
enum ccl_lut_input_src_sel {
	/** Masked input */
	CCL_LUT_INPUT_SRC_MASK = 0,
	/** Feedback input source */
	CCL_LUT_INPUT_SRC_FEEDBACK = 1,
	/** Linked LUT input source */
	CCL_LUT_INPUT_SRC_LINK = 2,
	/** Event input source */
	CCL_LUT_INPUT_SRC_EVENT = 3,
	/** I/O pin input source */
	CCL_LUT_INPUT_SRC_IO = 4,
	/** AC input source */
	CCL_LUT_INPUT_SRC_AC = 5,
	/** TC input source */
	CCL_LUT_INPUT_SRC_TC = 6,
	/** Alternative TC input source */
	CCL_LUT_INPUT_SRC_ALTTC = 7,
	/** TCC input source */
	CCL_LUT_INPUT_SRC_TCC = 8,
	/** SERCOM input source */
	CCL_LUT_INPUT_SRC_SERCOM = 9,
};

/**
 * \brief Select the LUT output filter options enum.
 *
 * Enum for the LUT output filter options.
 */
enum ccl_lut_filter_sel {
	/** Filter disabled */
	CCL_LUT_FILTER_DISABLE = CCL_LUTCTRL_FILTSEL_DISABLE,
	/** Synchronizer enabled */
	CCL_LUT_FILTER_SYNC = CCL_LUTCTRL_FILTSEL_SYNCH,
	/** Filter enabled */
	CCL_LUT_FILTER_ENABLE = CCL_LUTCTRL_FILTSEL_FILTER,
};

/**
 * \brief CCL module configuration structure.
 *
 *  Configuration structure for CCL module.
 */
struct ccl_config {
	/** GCLK generator used to clock the peripheral */
	enum gclk_generator clock_source;
	/** If \c true, the GCLK_CCL clock will not stop in standby sleep mode */
	bool run_in_standby;
};

/**
 * \brief CCL LUT 0 to 3 configuration structure.
 *
 *  Configuration structure for CCL LUT 0 to 3.
 */
struct ccl_lut_config {
	/**  The value of truth logic as a function of inputs IN[2:0] */
	uint8_t truth_table_value;
	/** If \c true, LUT event output is enabled */
	bool event_output_enable;
	/** If \c true, LUT incoming event is enabled */
	bool event_input_enable;
	/** If \c true, incoming event is inverted */
	bool event_input_inverted_enable;
	/** Selection of the input0 source */
	enum ccl_lut_input_src_sel input0_src_sel;
	/** Selection of the input1 source */
	enum ccl_lut_input_src_sel input1_src_sel;
	/** Selection of the input2 source */
	enum ccl_lut_input_src_sel input2_src_sel;
	/** If \c true, Edge detector is enabled */
	bool edge_selection_enable;
	/**  Selection of the LUT output filter options */
	enum ccl_lut_filter_sel filter_sel;
};

/**
 * \name Initialize and Reset CCL Module
 * @{
 */

/**
 * \brief Initializes CCL module.
 *
 * Resets all registers in the MODULE to their initial state,
 * and then enable the module.
 */
void ccl_init(struct ccl_config *const config);

/**
 * \brief Initializes all members of a CCL configuration structure
 *  to safe defaults.
 *
 *  Initializes all members of a given Configurable Custom Logic configuration
 *  structure to safe and known default values. This function should be called on
 *  all new instances of these configuration structures before being modified
 *  by the user application.
 *
 *  The default configuration is as follows:
 *   \li GCLK_CLL will be stopped in standby sleep mode
 *   \li Generator 0 is the default GCLK generator
 *
 *  \param[out] config  Configuration structure to initialize to default values
 */
static inline void ccl_get_config_defaults(
		struct ccl_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	config->clock_source = GCLK_GENERATOR_0;
	/* Default configuration values */
	config->run_in_standby = false;
}

/**
 * \brief Resets CCL module.
 *
 * Resets all registers in the MODULE to their initial state,
 * and the CCL will be disabled.
 */
static inline void ccl_module_reset(void)
{
	/* Reset CCL. */
	CCL->CTRL.reg |= CCL_CTRL_SWRST;

	while((CCL->CTRL.reg & CCL_CTRL_SWRST));
}
/** @} */

/**
 * \name Enable and Disable CCL Module
 * @{
 */

/**
 * \brief Enables CCL module.
 *
 * Enable the peripheral.
 *
 */
static inline void ccl_module_enable(void)
{
	/* Enable CCL. */
	CCL->CTRL.reg |= CCL_CTRL_ENABLE;
}

/**
 * \brief Disables CCL module.
 *
 * Disables the peripheral.
 */
static inline void ccl_module_disable(void)
{
	/* Disable CCL. */
	CCL->CTRL.reg &= ~CCL_CTRL_ENABLE;
}

/** @} */

/**
 * \name Configure LUT
 * @{
 */

/**
 *  \brief Writes sequential selection to the hardware module.
 *
 *  Writes a given sequential selection configuration to the hardware module.
 *
 *  \note This function can only be used when the CCL module is disabled.
 *
 *  \param[in] seq_selection       Enum for the sequential selection configuration
 *  \param[in] number     SEQ unit number to config
 */
enum status_code ccl_seq_config(const enum ccl_seq_id number,
		const enum ccl_seq_selection seq_selection);

/**
 * \brief Initializes all members of LUT configuration
 * structure to safe defaults.
 *
 *  Initializes all members of LUT configuration
 *  structure to safe defaults. This function should be called on all new
 *  instances of these configuration structures before being modified by the
 *  user application.
 *
 *  The default configuration is as follows:
 *   \li Truth table value is 0x00
 *   \li LUT event output is disabled
 *   \li LUT incoming event is disabled
 *   \li LUT incoming event is not inverted
 *   \li The input IN[2:0] source is masked
 *   \li The edge detector is disabled
 *   \li The LUT output filter is disabled
 *
 *  \param[out] config  LUT configuration structure to initialize to
 *                       default values
 */
void ccl_lut_get_config_defaults(struct ccl_lut_config *const config);

/** \brief Writes LUT configuration to the hardware module.
 *
 *  Writes a given LUT configuration to the hardware  module.
 *
 *  \note This function can only be used when the CCL module is disabled.
 *
 *  \param[in] config       Pointer to the LUT configuration struct
 *  \param[in] number     LUT number to config
 */
enum status_code ccl_lut_set_config(const enum ccl_lut_id number,
		struct ccl_lut_config *const config);
/** @} */

/**
 * \name Enable and Disable LUT
 * @{
 */

/**
 * \brief Enables an LUT that was previously configured.
 *
 *  Enables an LUT that was previously configured via a call to
 *  \ref ccl_lut_set_config function.
 *
 *  \param[in] number      LUT number to enable
 */
void ccl_lut_enable(const enum ccl_lut_id number);

/**
 * \brief Disables an LUT that was previously enabled.
 *
 *  Disables an LUT that was previously enabled via a call to
 *  \ref ccl_lut_enable().
 *
 *  \param[in] number      LUT number to enable
 */
void ccl_lut_disable(const enum ccl_lut_id number);

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */

/**
 * \page asfdoc_sam0_ccl_extra Extra Information for CCL Driver
 *
 * \section asfdoc_sam0_ccl_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *  <tr>
 *		<td>CCL</td>
 *		<td>Configurable Custom Logic</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_ccl_extra_dependencies Dependencies
 * This driver has no dependencies.
 *
 *
 * \section asfdoc_sam0_ccl_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_ccl_extra_history Module History
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
 * \page asfdoc_sam0_ccl_exqsg Examples for CCL Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_ccl_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_ccl_basic_use_case
 *
 * \page asfdoc_sam0_ccl_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42448B</td>
 *		<td>08/2015</td>
 *		<td>Add support for SAM L22</td>
 *	</tr>
 *	<tr>
 *		<td>42448A</td>
 *		<td>06/2015</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */

#endif /* CCL_H_INCLUDED */

