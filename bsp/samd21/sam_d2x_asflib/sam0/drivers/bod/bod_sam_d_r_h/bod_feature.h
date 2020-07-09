/**
 * \file
 *
 * \brief SAM Brown Out Detector Driver
 *
 * Copyright (C) 2013-2016 Atmel Corporation. All rights reserved.
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
#ifndef BOD_FEATURE_H_INCLUDED
#define BOD_FEATURE_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup asfdoc_sam0_bod_group SAM Brown Out Detector (BOD) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for the configuration
 * and management of the device's Brown Out Detector (BOD) modules, to detect
 * and respond to under-voltage events and take an appropriate action.
 *
 * The following peripheral is used by this module:
 * - SYSCTRL (System Control)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM D20/D21
 *  - Atmel | SMART SAM R21
 *  - Atmel | SMART SAM D10/D11
 *  - Atmel | SMART SAM DA1
 *  - Atmel | SMART SAM HA1
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_bod_prerequisites
 *  - \ref asfdoc_sam0_bod_module_overview
 *  - \ref asfdoc_sam0_bod_special_considerations
 *  - \ref asfdoc_sam0_bod_extra_info
 *  - \ref asfdoc_sam0_bod_examples
 *  - \ref asfdoc_sam0_bod_api_overview
 *
 *
 * \section asfdoc_sam0_bod_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_bod_module_overview Module Overview
 *
 * The SAM devices contain a number of Brown Out Detector (BOD) modules.
 * Each BOD monitors the supply voltage for any dips that go below the set
 * threshold for the module. In case of a BOD detection the BOD will either 
 * reset the system or raise a hardware interrupt so that a safe power-down
 * sequence can be attempted.
 *
 *
 * \section asfdoc_sam0_bod_special_considerations Special Considerations
 *
 * The time between a BOD interrupt being raised and a failure of the processor
 * to continue executing (in the case of a core power failure) is system
 * specific; care must be taken that all critical BOD detection events can
 * complete within the amount of time available.
 *
 * \section asfdoc_sam0_bod_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_bod_extra. This includes:
 *  - \ref asfdoc_sam0_bod_extra_acronyms
 *  - \ref asfdoc_sam0_bod_extra_dependencies
 *  - \ref asfdoc_sam0_bod_extra_errata
 *  - \ref asfdoc_sam0_bod_extra_history
 *
 *
 * \section asfdoc_sam0_bod_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_bod_exqsg.
 *
 *
 * \section asfdoc_sam0_bod_api_overview API Overview
 * @{
 */

/**
 * \brief Brown Out Detector hardware instance IDs.
 *
 * List of possible BOD controllers within the device.
 */
enum bod {
	/** BOD33 External I/O voltage */
	BOD_BOD33,
};

/**
 * \brief Brown Out Detector input clock prescale values.
 *
 * List of possible BOD controller prescaler values, to reduce the sampling
 * speed of a BOD to lower the power consumption.
 */
enum bod_prescale {
	/** Divide input prescaler clock by 2 */
	BOD_PRESCALE_DIV_2       = SYSCTRL_BOD33_PSEL(0),
	/** Divide input prescaler clock by 4 */
	BOD_PRESCALE_DIV_4       = SYSCTRL_BOD33_PSEL(1),
	/** Divide input prescaler clock by 8 */
	BOD_PRESCALE_DIV_8       = SYSCTRL_BOD33_PSEL(2),
	/** Divide input prescaler clock by 16 */
	BOD_PRESCALE_DIV_16      = SYSCTRL_BOD33_PSEL(3),
	/** Divide input prescaler clock by 32*/
	BOD_PRESCALE_DIV_32      = SYSCTRL_BOD33_PSEL(4),
	/** Divide input prescaler clock by 64 */
	BOD_PRESCALE_DIV_64      = SYSCTRL_BOD33_PSEL(5),
	/** Divide input prescaler clock by 128 */
	BOD_PRESCALE_DIV_128     = SYSCTRL_BOD33_PSEL(6),
	/** Divide input prescaler clock by 256 */
	BOD_PRESCALE_DIV_256     = SYSCTRL_BOD33_PSEL(7),
	/** Divide input prescaler clock by 512 */
	BOD_PRESCALE_DIV_512     = SYSCTRL_BOD33_PSEL(8),
	/** Divide input prescaler clock by 1024 */
	BOD_PRESCALE_DIV_1024    = SYSCTRL_BOD33_PSEL(9),
	/** Divide input prescaler clock by 2048 */
	BOD_PRESCALE_DIV_2048    = SYSCTRL_BOD33_PSEL(10),
	/** Divide input prescaler clock by 4096 */
	BOD_PRESCALE_DIV_4096    = SYSCTRL_BOD33_PSEL(11),
	/** Divide input prescaler clock by 8192 */
	BOD_PRESCALE_DIV_8192    = SYSCTRL_BOD33_PSEL(12),
	/** Divide input prescaler clock by 16384 */
	BOD_PRESCALE_DIV_16384   = SYSCTRL_BOD33_PSEL(13),
	/** Divide input prescaler clock by 32768 */
	BOD_PRESCALE_DIV_32768   = SYSCTRL_BOD33_PSEL(14),
	/** Divide input prescaler clock by 65536 */
	BOD_PRESCALE_DIV_65536   = SYSCTRL_BOD33_PSEL(15),
};

/**
 * \brief Brown Out Detector detection actions.
 *
 * List of possible BOD actions when a BOD module detects a brown out condition.
 */
enum bod_action {
	/** A BOD detect will do nothing, and the BOD state can't be polled */
	BOD_ACTION_NONE      = SYSCTRL_BOD33_ACTION(0),
	/** A BOD detect will reset the device */
	BOD_ACTION_RESET     = SYSCTRL_BOD33_ACTION(1),
	/** A BOD detect will fire an interrupt */
	BOD_ACTION_INTERRUPT = SYSCTRL_BOD33_ACTION(2),
};

/**
 * \brief Brown Out Detector sampling modes.
 *
 * List of possible BOD module voltage sampling modes.
 */
enum bod_mode {
	/** BOD will sample the supply line continuously */
	BOD_MODE_CONTINUOUS  = 0,
	/** BOD will use the BOD sampling clock (1KHz) to sample the supply line */
	BOD_MODE_SAMPLED     = SYSCTRL_BOD33_MODE,
};

/** Configuration structure for a BOD module. */
struct bod_config {
	/** Input sampler clock prescaler factor, to reduce the 1KHz clock from the
	 *  ULP32K to lower the sampling rate of the BOD */
	enum bod_prescale prescaler;
	/** Sampling configuration mode for the BOD */
	enum bod_mode mode;
	/** Action to perform when a low power detection is made */
	enum bod_action action;
	/** BOD level to trigger at (see electrical section of device datasheet) */
	uint8_t level;
	/** If \c true, enables detection hysteresis */
	bool hysteresis;
	/** If \c true, the BOD is kept enabled and sampled during device sleep */
	bool run_in_standby;
};

/**
 * \name Configuration and Initialization
 * @{
 */

/**
 * \brief Get default BOD configuration.
 *
 * The default BOD configuration is:
 * - Clock prescaler set to divide the input clock by two
 * - Continuous mode
 * - Reset on BOD detect
 * - Hysteresis enabled
 * - BOD level 0x12
 * - BOD kept enabled during device sleep
 *
 * \param[out] conf  BOD configuration struct to set to default settings
 */
static inline void bod_get_config_defaults(
		struct bod_config *const conf)
{
	/* Sanity check arguments */
	Assert(conf);

	conf->prescaler      = BOD_PRESCALE_DIV_2;
	conf->mode           = BOD_MODE_CONTINUOUS;
	conf->action         = BOD_ACTION_RESET;
	conf->level          = 0x27;
	conf->hysteresis     = true;
	conf->run_in_standby = true;
}

enum status_code bod_set_config(
		const enum bod bod_id,
		struct bod_config *const conf);

/**
 * \brief Enables a configured BOD module.
 *
 * Enables the specified BOD module that has been previously configured.
 *
 * \param[in] bod_id  BOD module to enable
 *
 * \return Error code indicating the status of the enable operation.
 *
 * \retval STATUS_OK               If the BOD was successfully enabled
 * \retval STATUS_ERR_INVALID_ARG  An invalid BOD was supplied
 */
static inline enum status_code bod_enable(
		const enum bod bod_id)
{
	switch (bod_id) {
		case BOD_BOD33:
			SYSCTRL->BOD33.reg |= SYSCTRL_BOD33_ENABLE;
			break;
		default:
			Assert(false);
			return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/**
 * \brief Disables an enabled BOD module.
 *
 * Disables the specified BOD module that was previously enabled.
 *
 * \param[in] bod_id  BOD module to disable
 *
 * \return Error code indicating the status of the disable operation.
 *
 * \retval STATUS_OK               If the BOD was successfully disabled
 * \retval STATUS_ERR_INVALID_ARG  An invalid BOD was supplied
 */
static inline enum status_code bod_disable(
		const enum bod bod_id)
{
	switch (bod_id) {
		case BOD_BOD33:
			SYSCTRL->INTENCLR.reg = SYSCTRL_INTENCLR_BOD33RDY | SYSCTRL_INTENCLR_BOD33DET | SYSCTRL_INTENCLR_B33SRDY;
			SYSCTRL->INTFLAG.reg = SYSCTRL_INTFLAG_BOD33RDY | SYSCTRL_INTFLAG_BOD33DET | SYSCTRL_INTFLAG_B33SRDY;
			SYSCTRL->BOD33.reg &= ~SYSCTRL_BOD33_ENABLE;
			break;
		default:
			Assert(false);
			return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/**
 * \brief Checks if a specified BOD low voltage detection has occurred.
 *
 * Determines if a specified BOD has detected a voltage lower than its
 * configured threshold.
 *
 * \param[in] bod_id  BOD module to check
 *
 * \return Detection status of the specified BOD.
 *
 * \retval true   If the BOD has detected a low voltage condition
 * \retval false  If the BOD has not detected a low voltage condition
 */
static inline bool bod_is_detected(
		const enum bod bod_id)
{
	switch (bod_id) {
		case BOD_BOD33:
			return SYSCTRL->INTFLAG.bit.BOD33DET;
		default:
			Assert(false);
			return false;
	}
}

/**
 * \brief Clears the low voltage detection state of a specified BOD.
 *
 * Clears the low voltage condition of a specified BOD module, so that new
 * low voltage conditions can be detected.
 *
 * \param[in] bod_id  BOD module to clear
 */
static inline void bod_clear_detected(
		const enum bod bod_id)
{
	switch (bod_id) {
		case BOD_BOD33:
			SYSCTRL->INTFLAG.reg = SYSCTRL_INTFLAG_BOD33DET;
			return;
		default:
			Assert(false);
			return;
	}
}

/** @} */

/**
 * @}
 */


/**
 * \page asfdoc_sam0_bod_extra Extra Information for BOD Driver
 *
 * \section asfdoc_sam0_bod_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>BOD</td>
 *      <td>Brown Out Detector</td>
 *  </tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_bod_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_sam0_bod_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_bod_extra_history Module History
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
 *		<td>Removed BOD12 reference</td>
 *	</tr>
 *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_bod_exqsg Examples for BOD Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_bod_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_bod_basic_use_case
 *
 *  - \subpage asfdoc_sam0_bod_application_use_case
 *
 * \page asfdoc_sam0_bod_application_use_case Application Use Case for BOD - Application
 * The preferred method of setting BOD33 levels and settings is through the fuses.
 * When it is desirable to set it in software, see the below use case.
 *
 * In this use case, a new BOD33 level might be set in SW if the clock settings
 * are adjusted up after a battery has charged to a higher level. When the battery
 * discharges, the chip will reset when the battery level is below SW BOD33 level.
 * Now the chip will run at a lower clock rate and the BOD33 level from fuse.
 * The chip should always measure the voltage before adjusting the frequency up.
 *
 * \page asfdoc_sam0_bod_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</th>
 *		<th>Date</th>
 *		<th>Comments</th>
 *	</tr>
 *	<tr>
 *		<td>42149E</td>
 *		<td>12/2015</td>
 *		<td>Added support for SAM DA1</td>
 *	</tr>
 *	<tr>
 *		<td>42149D</td>
 *		<td>12/2014</td>
 *		<td>Added support for SAM R21, and SAM D10/D11</td>
 *	</tr>
 *	<tr>
 *		<td>42149C</td>
 *		<td>01/2014</td>
 *		<td>Added support for SAM D21</td>
 *	</tr>
 *	<tr>
 *		<td>42149B</td>
 *		<td>06/2013</td>
 *		<td>Corrected documentation typos</td>
 *	</tr>
 *	<tr>
 *		<td>42149A</td>
 *		<td>06/2013</td>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 */

#ifdef __cplusplus
}
#endif

#endif /* BOD_FEATURE_H_INCLUDED */
