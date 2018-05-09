/**
 * \file
 *
 * \brief SAM PWM Driver for SAMB11
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
#ifndef PWM_H_INCLUDED
#define PWM_H_INCLUDED

/**
 * \defgroup asfdoc_samb_pwm_group SAM Pulse Width Modulation Driver (PWM)
 *
 * This driver for Atmel&reg; | SMART SAM devices provides an interface for the
 * configuration and management of the device's Pulse Width Modulation Module
 * (PWM) functionality for waveform generation operations.
 *
 * The following peripherals are used by this module:
 *  - PWM (Pulse Width Modulation)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM B11
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_samb_pwm_prerequisites
 *  - \ref asfdoc_samb_pwm_module_overview
 *  - \ref asfdoc_samb_pwm_special_considerations
 *  - \ref asfdoc_samb_pwm_extra_info
 *  - \ref asfdoc_samb_pwm_examples
 *  - \ref asfdoc_samb_pwm_api_overview
 *
 *
 * \section asfdoc_samb_pwm_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_samb_pwm_module_overview Module Overview
 *
 * PWM is a flexible fully configurable module which has the following features:
 *  - 4 independent configurable pulse width modulator (PWM) blocks.
 *  - It can be connected to an external on board low pass filter to produce
 *    different analog control voltages depending on the configured duty cycle.
 *  - The base frequency of PWM block is the XO clock (26MHz) or the RC oscillator.
 *  - Different duty cycles could be obtained
 *  - The frequency of the PWM pulse is programmable in steps according
 *    to the following relation:
 * \f[
 *    f_{PWM} = \frac{f_{PWM_{base}}} {64 \times 2^i}
 * \f]
 * \f[
 *   i = 0 - 8
 * \f]
 *
 * f<SUB>PWM</SUB><SUB>base</SUB> can be selected to have different values
 * according to the following table. Minimum and maximum fre-quencies supported
 * for each clock selection is listed in the table as well.
 *
 * <table>
 *  <caption>Frequency support</caption>
 *  <tr>
 *    <th>f<SUB>PWM</SUB><SUB>base</SUB></th>
 *    <th>Maximum frequency</th>
 *    <th>Minimum frequency</th>
 *  </tr>
 *  <tr>
 *    <td>26 MHz</td>
 *    <td>406.25 KHz</td>
 *    <td>1.586 KHz</td>
 *  </tr>
 *  <tr>
 *    <td>13 MHz</td>
 *    <td>203.125 KHz</td>
 *    <td>793.45 Hz</td>
 *  </tr>
  *  <tr>
 *    <td>6.5 MHz</td>
 *    <td>101.562 KHz</td>
 *    <td>396.72 Hz</td>
 *  </tr>
  *  <tr>
 *    <td>3.25 MHz</td>
 *    <td>50.781 KHz</td>
 *    <td>198.36 Hz</td>
 *  </tr>
 * </table>
 *
 * \section asfdoc_samb_pwm_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 * \section asfdoc_samb_pwm_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_samb_pwm_extra. This includes:
 *  - \ref asfdoc_samb_pwm_extra_acronyms
 *  - \ref asfdoc_samb_pwm_extra_dependencies
 *  - \ref asfdoc_samb_pwm_extra_errata
 *  - \ref asfdoc_samb_pwm_extra_history
 *
 *
 * \section asfdoc_samb_pwm_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_samb_pwm_exqsg.
 *
 *
 * \section asfdoc_samb_pwm_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \brief PWM device configuration enum.
 *
 *  Enum for the possible settings of pwm device configuration.
 */
enum pwm_device_select {
	/** PWM module 0 */
	PWM0 = 0,
	/** PWM module 1 */
	PWM1,
	/** PWM module 2 */
	PWM2,
	/** PWM module 3 */
	PWM3,
};

/**
 *  \brief PWM sample method configuration enum.
 *
 *  Enum for the possible settings of pwm sample method configuration.
 */
enum pwm_sample_method {
	/** Samples agcdata at >= 1024 cycles and does not lose precision */
	PWM_SAMPLE_METHOD_0 = 0,
	/** Samples at PWM period but will lose LSBs if less than 1024 */
	PWM_SAMPLE_METHOD_1,
};

/**
 *  \brief PWM period configuration enum.
 *
 *  Enum for the possible settings of pwm period configuration.
 */
enum pwm_period {
	/** PWM perid 0 */
	PWM_PERIOD_0 = 0,
	/** PWM perid 1 */
	PWM_PERIOD_1,
	/** PWM perid 2 */
	PWM_PERIOD_2,
	/** PWM perid 3 */
	PWM_PERIOD_3,
	/** PWM perid 4 */
	PWM_PERIOD_4,
	/** PWM perid 5 */
	PWM_PERIOD_5,
	/** PWM perid 6 */
	PWM_PERIOD_6,
	/** PWM perid 7 */
	PWM_PERIOD_7,
	/** PWM perid 8 */
	PWM_PERIOD_8,
};

/**
 *  \brief PWM clock select configuration enum.
 *
 *  Enum for the possible settings of pwm clock select configuration.
 */
enum pwm_clock_select {
	/** Clock 26MHz */
	PWM_CLOCK_SELECT_26_0 = 0,
	/** Clock 13MHz */
	PWM_CLOCK_SELECT_13_0,
	/** Clock 6.5MHz */
	PWM_CLOCK_SELECT_6_5,
	/** Clock 3.25MHz */
	PWM_CLOCK_SELECT_3_25,
};

/**
 *  \brief PWM configuration structure.
 *
 *  Configuration structure for a PWM instance. This structure should be
 *  initialized by the \ref pwm_get_config_defaults() function before being
 *  modified by the user application.
 */
struct pwm_config {
	/** 1 to inverse the polarity */
	bool output_polarity;
	/** AGC data format */
	bool agcdata_format;
	/** Sample method */
	enum pwm_sample_method sample_method;
	/** Programmable PWM update period */
	enum pwm_period period;
	/** This value specifies the duty cycle(%) */
	uint8_t duty_cycle;
	/** PWM Source Clock Frequency Select */
	enum pwm_clock_select clock_select;
	/** PWM PAD pin number */
	uint32_t pin_number_pad;
	/** PWM PAD pinmux selection */
	uint32_t pinmux_sel_pad;
};

/** \name Configuration and initialization
 * @{
 */

void pwm_get_config_defaults(struct pwm_config *const config);
void pwm_set_duty_cycle(enum pwm_device_select device_select, \
					uint8_t duty_cycle);
void pwm_set_period(enum pwm_device_select device_select, \
					enum pwm_period period);
enum status_code pwm_init(enum pwm_device_select device_select, \
					const struct pwm_config *const config);

/** @} */

/**
 * \name Enable/Disable and Reset
 * @{
 */

void pwm_enable(enum pwm_device_select device_select);
void pwm_disable(enum pwm_device_select device_select);
void pwm_reset(enum pwm_device_select device_select);

/** @} */

/** @}*/

#ifdef __cplusplus
}
#endif


/**
 * \page asfdoc_samb_pwm_extra Extra Information for PWM Driver
 *
 * \section asfdoc_samb_pwm_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>PWM</td>
 *		<td>Pulse Width Modulation</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_samb_pwm_extra_dependencies Dependencies
 * There are no dependencies related to this driver.
 *
 *
 * \section asfdoc_samb_pwm_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_samb_pwm_extra_history Module History
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
 * \page asfdoc_samb_pwm_exqsg Examples for PWM Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_samb_pwm_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_samb_pwm_basic_use_case
 *
 * \page asfdoc_samb_pwm_document_revision_history Document Revision History
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
