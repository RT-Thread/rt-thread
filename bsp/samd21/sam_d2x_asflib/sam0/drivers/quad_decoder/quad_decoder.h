/**
 * \file
 *
 * \brief SAM QUAD DECODER Driver for SAMB11
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
#ifndef QUAD_DECODER_H_INCLUDED
#define QUAD_DECODER_H_INCLUDED

/**
 * \defgroup asfdoc_samb_quad_decoder_group SAM Quadrature Decoder
 *
 * This driver for Atmel&reg; | SMART SAM devices provides an interface for the
 * configuration and management of the device's Quadrature Decoder functionality.
 *
 * The following peripherals are used by this module:
 *  - Quadrature Decoder
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM B11
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_samb_quad_decoder_prerequisites
 *  - \ref asfdoc_samb_quad_decoder_module_overview
 *  - \ref asfdoc_samb_quad_decoder_special_considerations
 *  - \ref asfdoc_samb_quad_decoder_extra_info
 *  - \ref asfdoc_samb_quad_decoder_examples
 *  - \ref asfdoc_samb_quad_decoder_api_overview
 *
 *
 * \section asfdoc_samb_quad_decoder_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_samb_quad_decoder_module_overview Module Overview
 * A Quadrature Decoder is used to decode the output of a Quadrature Encoder,
 * it can be used for precision measurement of speed, acceleration, and position
 * of a motor's rotor and with rotary knobs to determine user input. The SAMB11
 * contains 3 Quadrature Decoder. Each one may be programmed independently.
 * The Quadrature Decoder require initialization prior to being enabled. 
 * Quadrature Decoder is a flexible fully configurable module which has the following features:
 *
 *   - 3 independent configurable Quadrature Decoder blocks.
 *
 *   - 16-bits resolution counters.
 *
 *   - 16-bits resolution Lower and Upper threshold control values.
 *
 *   - Input clock selection (only for MP).
 *
 * \subsection asfdoc_samb_quad_decoder_module_overview_thresholds Setting Thresholds
 * The Quadrature Decoder have lower and upper thresholds. These are used for interrupt
 * generation. The interrupt is generated whenever the counter is greater than or equal
 * to the higher threshold and less than or equal to the lower threshold. Setting each
 * module Higher and Lower threshold values as described below:
 *
 * \anchor asfdoc_sam0_quad_decoder_thresholds
 * <table>
 *  <caption>Quad-Decoder Register Thresholds</caption>
 *  <tr>
 *    <th>Filed name</th>
 *    <th>Bits range</th>
 *    <th>Description</th>
 *  </tr>
 *  <tr>
 *    <td>Upper</td>
 *    <td>[15 : 0]</td>
 *    <td>Upper threshold value</td>
 *  </tr>
 *  <tr>
 *    <td>Lower</td>
 *    <td>[31 : 16]</td>
 *    <td>Lower threshold value</td>
 *  </tr>
 * </table>
 *
 * \subsection asfdoc_samb_quad_decoder_module_overview_clock Setting Clock
 * The Quadrature Decoder have 4 different clock options to support different
 * application requirements. The possible options are 26 MHz, 13 MHz, 6.5 MHz
 * and 3.25 MHz This clock is used to sample the incoming Quad Decoder inputs.
 *
 * \section asfdoc_samb_quad_decoder_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 * \section asfdoc_samb_quad_decoder_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_samb_quad_decoder_extra. This includes:
 *  - \ref asfdoc_samb_quad_decoder_extra_acronyms
 *  - \ref asfdoc_samb_quad_decoder_extra_dependencies
 *  - \ref asfdoc_samb_quad_decoder_extra_errata
 *  - \ref asfdoc_samb_quad_decoder_extra_history
 *
 *
 * \section asfdoc_samb_quad_decoder_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_samb_quad_decoder_exqsg.
 *
 *
 * \section asfdoc_samb_quad_decoder_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Type definition for a DUALTIMER module callback function. */
typedef void (*quad_decoder_callback_t)(void);

/**
 * \brief QUAD DECODER index number
 *
 * Values is the axis(x,y,z) of QUAD DECODER instance.
 */
enum quad_decoder_axis {
	/** AXIS X */
	QDEC_AXIS_X = 0,
	/** AXIS Y */
	QDEC_AXIS_Y,
	/** AXIS Z */
	QDEC_AXIS_Z,
};

/**
 * \brief QUAD DECODER module clock input
 *
 * QUAD DECODER module clock.
 *
 */
enum quad_decoder_clock_input {
	/** Source from clock input 0: 26MHz */
	QDEC_CLK_INPUT_0 = 0,
	/** Source from clock input 1: 13MHz */
	QDEC_CLK_INPUT_1,
	/** Source from clock input 2: 6.5MHz */
	QDEC_CLK_INPUT_2,
	/** Source from clock input 3: 3MHz */
	QDEC_CLK_INPUT_3,
};

/**
 * \brief Quad Decoder private configuration structure.
 *
 * Private configuration struct for Quad Decoder instance.
 */
struct quad_decoder_private_config {
	/** Quad Decoder Source Clock Frequency Select */
	enum quad_decoder_clock_input clock_sel;
	/** Upper Threshold of counter for Quad Decoder */
	int16_t threshold_upper;
	/** Lower Threshold of counter for Quad Decoder */
	int16_t threshold_lower;
	/** Dec_in_a pin number */
	/** Dec_in_b pin number */
	uint32_t pin_number_pad[2];
	/** Dec_in_a pinmux selection */
	/** Dec_in_b pinmux selection */
	uint32_t pinmux_sel_pad[2];
};

/**
 * \brief QUAD DECODER configuration structure.
 *
 * Configuration struct for a QUAD DECODER instance.
 * This structure should be initialized by the
 * \ref quad_decoder_get_config_defaults function
 * before being modified by the user application.
 */
struct quad_decoder_config {
	uint8_t qdec_enalbe;
	struct quad_decoder_private_config qdec0;
	struct quad_decoder_private_config qdec1;
	struct quad_decoder_private_config qdec2;
};

/**
 * \name Configuration and Initialization
 * @{
 */
void quad_decoder_get_config_defaults(
		struct quad_decoder_config *config);
void quad_decoder_init(const struct quad_decoder_config *config);
/** @} */

/**
 * \name Enable and disable module
 * @{
 */
void quad_decoder_enable(enum quad_decoder_axis qdec);
void quad_decoder_disable(enum quad_decoder_axis qdec);
/** @} */

/**
 * \name Get value
 * @{
 */
int16_t quad_decoder_get_counter(enum quad_decoder_axis qdec);
/** @} */

/**
 * \name Callback register/unregister
 * @{
 */
void quad_decoder_register_callback(enum quad_decoder_axis qdec,
		quad_decoder_callback_t fun);
void quad_decoder_unregister_callback(enum quad_decoder_axis qdec);
/** @} */

/** @}*/
#ifdef __cplusplus
}
#endif

/**
 * \page asfdoc_samb_quad_decoder_extra Extra Information for Quadrature Decoder Driver
 *
 * \section asfdoc_samb_quad_decoder_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>Quadrature Decoder</td>
 *		<td>Quadrature Decoder</td>
 *	</tr>
 * </table>
 *
 * \section asfdoc_samb_quad_decoder_extra_dependencies Dependencies
 * There are no dependencies related to this driver.
 *
 *
 * \section asfdoc_samb_quad_decoder_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_samb_quad_decoder_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *  <tr>
 *      <th>Changelog</th>
 *  </tr>
 *  <tr>
 *      <td>Initial Release</td>
 *  </tr>
 * </table>
 */

/**
 * \page asfdoc_samb_quad_decoder_exqsg Examples for Quadrature Decoder Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_samb_quad_decoder_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_samb_quad_decoder_basic_use_case
 *
 * \page asfdoc_samb_quad_decoder_document_revision_history Document Revision History
 *
 * <table>
 *  <tr>
 *    <th>Doc. Rev.</td>
 *    <th>Date</td>
 *    <th>Comments</td>
 *  </tr>
 *  <tr>
 *    <td>A</td>
 *    <td>09/2015</td>
 *    <td>Initial release</td>
 *  </tr>
 * </table>
 */

#endif