/**
 * \file
 *
 * \brief SAM Brown Out Detector Driver
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
 * The following peripherals are used by this module:
 * - SUPC (Supply Controller)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM C20/C21
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
 * threshold for the module. In case of a BOD detection the BOD will either reset
 * the system or raise a hardware interrupt so that a safe power-down sequence can
 * be attempted.
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
 * \brief Brown Out Detector input clock prescale values.
 *
 * List of possible BODVDD controller prescaler values, to reduce the sampling
 * speed of a BODVDD to lower the power consumption.
 */
enum bodvdd_prescale {
	/** Divide input prescaler clock by 2 */
	BODVDD_PRESCALE_DIV_2       = SUPC_BODVDD_PSEL(0),
	/** Divide input prescaler clock by 4 */
	BODVDD_PRESCALE_DIV_4       = SUPC_BODVDD_PSEL(1),
	/** Divide input prescaler clock by 8 */
	BODVDD_PRESCALE_DIV_8       = SUPC_BODVDD_PSEL(2),
	/** Divide input prescaler clock by 16 */
	BODVDD_PRESCALE_DIV_16      = SUPC_BODVDD_PSEL(3),
	/** Divide input prescaler clock by 32 */
	BODVDD_PRESCALE_DIV_32      = SUPC_BODVDD_PSEL(4),
	/** Divide input prescaler clock by 64 */
	BODVDD_PRESCALE_DIV_64      = SUPC_BODVDD_PSEL(5),
	/** Divide input prescaler clock by 128 */
	BODVDD_PRESCALE_DIV_128     = SUPC_BODVDD_PSEL(6),
	/** Divide input prescaler clock by 256 */
	BODVDD_PRESCALE_DIV_256     = SUPC_BODVDD_PSEL(7),
	/** Divide input prescaler clock by 512 */
	BODVDD_PRESCALE_DIV_512     = SUPC_BODVDD_PSEL(8),
	/** Divide input prescaler clock by 1024 */
	BODVDD_PRESCALE_DIV_1024    = SUPC_BODVDD_PSEL(9),
	/** Divide input prescaler clock by 2048 */
	BODVDD_PRESCALE_DIV_2048    = SUPC_BODVDD_PSEL(10),
	/** Divide input prescaler clock by 4096 */
	BODVDD_PRESCALE_DIV_4096    = SUPC_BODVDD_PSEL(11),
	/** Divide input prescaler clock by 8192 */
	BODVDD_PRESCALE_DIV_8192    = SUPC_BODVDD_PSEL(12),
	/** Divide input prescaler clock by 16384 */
	BODVDD_PRESCALE_DIV_16384   = SUPC_BODVDD_PSEL(13),
	/** Divide input prescaler clock by 32768 */
	BODVDD_PRESCALE_DIV_32768   = SUPC_BODVDD_PSEL(14),
	/** Divide input prescaler clock by 65536 */
	BODVDD_PRESCALE_DIV_65536   = SUPC_BODVDD_PSEL(15),
};

/**
 * \brief Brown Out Detector sampling modes in active sleep mode.
 *
 * List of possible BODVDD module voltage sampling modes in active sleep mode.
 */
enum bodvdd_mode_in_active {
	/** BODVDD will sample the supply line continuously */
	BODVDD_ACTCFG_CONTINUOUS = 0,
	/** BODVDD will use the BODVDD sampling clock (1kHz) to sample the supply line */
	BODVDD_ACTCFG_SAMPLED    = SUPC_BODVDD_ACTCFG,
};

/**
 * \brief Brown Out Detector sampling modes in standby sleep mode.
 *
 * List of possible BODVDD module voltage sampling modes in standby sleep mode.
 */
enum bodvdd_mode_in_standby {
	/** BODVDD will sample the supply line continuously */
	BODVDD_STDBYCFG_CONTINUOUS = 0,
	/** BODVDD will use the BODVDD sampling clock (1kHz) to sample the supply line */
	BODVDD_STDBYCFG_SAMPLED    = SUPC_BODVDD_STDBYCFG,
};

/**
 * \brief Brown Out Detector detection actions.
 *
 * List of possible BODVDD actions when a BODVDD module detects a brown-out condition.
 */
enum bodvdd_action {
	/** A BODVDD detect will do nothing, and the BODVDD state must be polled */
	BODVDD_ACTION_NONE      = SUPC_BODVDD_ACTION(0),
	/** A BODVDD detect will reset the device */
	BODVDD_ACTION_RESET     = SUPC_BODVDD_ACTION(1),
	/** A BODVDD detect will fire an interrupt */
	BODVDD_ACTION_INTERRUPT = SUPC_BODVDD_ACTION(2),
	/** A BODVDD detect will put the device in backup sleep mode */
	BODVDD_ACTION_BACKUP    = SUPC_BODVDD_ACTION(3),
};

/** Configuration structure for a BODVDD module. */
struct bodvdd_config {
	/** Input sampler clock prescaler factor, to reduce the 1kHz clock from the
	 *  ULP32K to lower the sampling rate of the BODVDD */
	enum bodvdd_prescale prescaler;
	/** BODVDD configuration in active mode */
	enum bodvdd_mode_in_active mode_in_active;
	/** BODVDD configuration in backup sleep mode */
	enum bodvdd_mode_in_standby mode_in_standby;
	/** Action to perform when a low power detection is made */
	enum bodvdd_action action;
	/** BODVDD level to trigger at when monitors VDD except in backup sleep mode */
	uint8_t level;
	/** If \c true, the BODVDD is kept enabled and sampled during standby */
	bool run_in_standby;
	/** If \c true, enables detection hysteresis */
	bool hysteresis;
};

/**
 * \name Configuration and Initialization
 * @{
 */

/**
 * \brief Get default BODVDD configuration.
 *
 * The default BODVDD configuration is:
 * - Clock prescaler set to divide the input clock by two
 * - Continuous in active mode
 * - Continuous in standby mode
 * - Reset on BODVDD detect
 * - Hysteresis enabled
 * - BODVDD level 42 on V<SUB>DD</SUB>
 * - BODVDD kept enabled during standby
 *
 * \param[out] conf  BODVDD configuration struct to set to default settings
 */
static inline void bodvdd_get_config_defaults(
		struct bodvdd_config *const conf)
{
	/* Sanity check arguments */
	Assert(conf);

	conf->prescaler       = BODVDD_PRESCALE_DIV_2;
	conf->mode_in_active  = BODVDD_ACTCFG_CONTINUOUS;
	conf->mode_in_standby = BODVDD_STDBYCFG_CONTINUOUS;
	conf->action          = BODVDD_ACTION_RESET;
	conf->level           = 0x2A;
	conf->run_in_standby  = true;
	conf->hysteresis      = true;
}

enum status_code bodvdd_set_config(
		struct bodvdd_config *const conf);

/**
 * \brief Enables a configured BODVDD module.
 *
 * Enables the BODVDD module that has been previously configured.
 *
 * \return Error code indicating the status of the enable operation.
 *
 * \retval STATUS_OK               If the BODVDD was successfully enabled
 */
static inline enum status_code bodvdd_enable(void)
{
	SUPC->BODVDD.reg |= SUPC_BODVDD_ENABLE;
	while (!(SUPC->STATUS.reg & SUPC_STATUS_BVDDSRDY)) {
		/* Wait for BODVDD register sync ready */
	}

	return STATUS_OK;
}

/**
 * \brief Disables an enabled BODVDD module.
 *
 * Disables the BODVDD module that was previously enabled.
 *
 * \return Error code indicating the status of the disable operation.
 *
 * \retval STATUS_OK               If the BODVDD was successfully disabled
 */
static inline enum status_code bodvdd_disable(void)
{
	SUPC->INTENCLR.reg = SUPC_INTENCLR_BODVDDRDY | SUPC_INTENCLR_BODVDDDET | SUPC_INTENCLR_BVDDSRDY;
	SUPC->INTFLAG.reg = SUPC_INTFLAG_BODVDDRDY | SUPC_INTFLAG_BODVDDDET | SUPC_INTFLAG_BVDDSRDY;
	SUPC->BODVDD.reg &= ~SUPC_BODVDD_ENABLE;
	return STATUS_OK;
}

/**
 * \brief Checks if the BODVDD low voltage detection has occurred.
 *
 * Determines if the BODVDD has detected a voltage lower than its
 * configured threshold.
 *
 * \return Detection status of the BODVDD.
 *
 * \retval true   If the BODVDD has detected a low voltage condition
 * \retval false  If the BODVDD has not detected a low voltage condition
 */
static inline bool bodvdd_is_detected(void)
{
	return SUPC->STATUS.bit.BODVDDDET;
}

/**
 * \brief Clears the low voltage detection state of the BODVDD.
 *
 * Clears the low voltage condition of the BODVDD module, so that new
 * low voltage conditions can be detected.
 *
 */
static inline void bodvdd_clear_detected(void)
{
	SUPC->INTFLAG.reg = SUPC_INTFLAG_BODVDDDET;
	return;
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
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_bod_basic_use_case
 *
 *  - \subpage asfdoc_sam0_bod_application_use_case
 *
 * \page asfdoc_sam0_bod_application_use_case Application Use Case for BOD - Application
 * The preferred method of setting BODVDD levels and settings is trough the fuses.
 * When it is desirable to set it in software, see the below use case.
 *
 * In this use case, a new BODVDD level might be set in SW if the clock settings
 * are adjusted after a battery has charged to a higher level. When the battery
 * discharges, the chip will reset when the battery level is below the SW BODVDD level.
 * Now the chip will run at a lower clock rate and the BODVDD level from fuse.
 * The chip should always measure the voltage before adjusting the frequency up.
 *
 * \page asfdoc_sam0_bod_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42701A</td>
 *		<td>07/2016</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */


#ifdef __cplusplus
}
#endif

#endif /* BOD_FEATURE_H_INCLUDED */
