/**
 * \file
 *
 * \brief SAM Brown Out Detector Driver
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
 * - SUPC (Supply Controller)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM L21/L22
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
 * List of possible BOD33 controller prescaler values, to reduce the sampling
 * speed of a BOD33 to lower the power consumption.
 */
enum bod33_prescale {
	/** Divide input prescaler clock by 2 */
	BOD33_PRESCALE_DIV_2       = SUPC_BOD33_PSEL(0),
	/** Divide input prescaler clock by 4 */
	BOD33_PRESCALE_DIV_4       = SUPC_BOD33_PSEL(1),
	/** Divide input prescaler clock by 8 */
	BOD33_PRESCALE_DIV_8       = SUPC_BOD33_PSEL(2),
	/** Divide input prescaler clock by 16 */
	BOD33_PRESCALE_DIV_16      = SUPC_BOD33_PSEL(3),
	/** Divide input prescaler clock by 32 */
	BOD33_PRESCALE_DIV_32      = SUPC_BOD33_PSEL(4),
	/** Divide input prescaler clock by 64 */
	BOD33_PRESCALE_DIV_64      = SUPC_BOD33_PSEL(5),
	/** Divide input prescaler clock by 128 */
	BOD33_PRESCALE_DIV_128     = SUPC_BOD33_PSEL(6),
	/** Divide input prescaler clock by 256 */
	BOD33_PRESCALE_DIV_256     = SUPC_BOD33_PSEL(7),
	/** Divide input prescaler clock by 512 */
	BOD33_PRESCALE_DIV_512     = SUPC_BOD33_PSEL(8),
	/** Divide input prescaler clock by 1024 */
	BOD33_PRESCALE_DIV_1024    = SUPC_BOD33_PSEL(9),
	/** Divide input prescaler clock by 2048 */
	BOD33_PRESCALE_DIV_2048    = SUPC_BOD33_PSEL(10),
	/** Divide input prescaler clock by 4096 */
	BOD33_PRESCALE_DIV_4096    = SUPC_BOD33_PSEL(11),
	/** Divide input prescaler clock by 8192 */
	BOD33_PRESCALE_DIV_8192    = SUPC_BOD33_PSEL(12),
	/** Divide input prescaler clock by 16384 */
	BOD33_PRESCALE_DIV_16384   = SUPC_BOD33_PSEL(13),
	/** Divide input prescaler clock by 32768 */
	BOD33_PRESCALE_DIV_32768   = SUPC_BOD33_PSEL(14),
	/** Divide input prescaler clock by 65536 */
	BOD33_PRESCALE_DIV_65536   = SUPC_BOD33_PSEL(15),
};

/**
 * \brief Brown Out Detector voltage monitors.
 *
 * List of possible BOD33 module voltage monitored in active and standby mode.
 */
enum bod33_vol_monitor {
	/** The BOD33 monitors the VDD power pin in active and standby mode */
	BOD33_VMON_VDD  = 0,
	/** The BOD33 monitors the VBAT power pin in active and standby mode */
	BOD33_VMON_VBAT = SUPC_BOD33_VMON,
};

/**
 * \brief Brown Out Detector sampling modes in active sleep mode.
 *
 * List of possible BOD33 module voltage sampling modes in active sleep mode.
 */
enum bod33_mode_in_active {
	/** BOD33 will sample the supply line continuously */
	BOD33_ACTCFG_CONTINUOUS = 0,
	/** BOD33 will use the BOD33 sampling clock (1KHz) to sample the supply line */
	BOD33_ACTCFG_SAMPLED    = SUPC_BOD33_ACTCFG,
};

/**
 * \brief Brown Out Detector sampling modes in standby sleep mode.
 *
 * List of possible BOD33 module voltage sampling modes in standby sleep mode.
 */
enum bod33_mode_in_standby {
	/** BOD33 will sample the supply line continuously */
	BOD33_STDBYCFG_CONTINUOUS = 0,
	/** BOD33 will use the BOD33 sampling clock (1KHz) to sample the supply line */
	BOD33_STDBYCFG_SAMPLED    = SUPC_BOD33_STDBYCFG,
};

/**
 * \brief Brown Out Detector detection actions.
 *
 * List of possible BOD33 actions when a BOD33 module detects a brown-out condition.
 */
enum bod33_action {
	/** A BOD33 detect will do nothing, and the BOD33 state must be polled */
	BOD33_ACTION_NONE      = SUPC_BOD33_ACTION(0),
	/** A BOD33 detect will reset the device */
	BOD33_ACTION_RESET     = SUPC_BOD33_ACTION(1),
	/** A BOD33 detect will fire an interrupt */
	BOD33_ACTION_INTERRUPT = SUPC_BOD33_ACTION(2),
	/** A BOD33 detect will put the device in backup sleep mode */
	BOD33_ACTION_BACKUP    = SUPC_BOD33_ACTION(3),
};

/** Configuration structure for a BOD33 module. */
struct bod33_config {
	/** Input sampler clock prescaler factor, to reduce the 1KHz clock from the
	 *  ULP32K to lower the sampling rate of the BOD33 */
	enum bod33_prescale prescaler;
	/** Voltage monitored in active and standby mode */
	enum bod33_vol_monitor monitor;
	/** BOD33 configuration in active mode */
	enum bod33_mode_in_active mode_in_active;
	/** BOD33 configuration in backup sleep mode */
	enum bod33_mode_in_standby mode_in_standby;
	/** Action to perform when a low power detection is made */
	enum bod33_action action;
	/** BOD33 level to trigger at when monitors VBAT or in backup sleep mode */
	uint8_t backuplevel;
	/** BOD33 level to trigger at when monitors VDD excpt in backup sleep mode */
	uint8_t level;
	/** If \c true, the BOD33 is kept enabled and sampled during device sleep */
	bool run_in_backup;
	/** If \c true, the BOD33 is kept enabled and sampled during standby */
	bool run_in_standby;
	/** If \c true, enables detection hysteresis */
	bool hysteresis;
};


/**
 * \brief Brown Out Detector input clock prescale values.
 *
 * List of possible BOD12 controller prescaler values, to reduce the sampling
 * speed of a BOD12 to lower the power consumption.
 */
enum bod12_prescale {
	/** Divide input prescaler clock by 2 */
	BOD12_PRESCALE_DIV_2       = SUPC_BOD12_PSEL(0),
	/** Divide input prescaler clock by 4 */
	BOD12_PRESCALE_DIV_4       = SUPC_BOD12_PSEL(1),
	/** Divide input prescaler clock by 8 */
	BOD12_PRESCALE_DIV_8       = SUPC_BOD12_PSEL(2),
	/** Divide input prescaler clock by 16 */
	BOD12_PRESCALE_DIV_16      = SUPC_BOD12_PSEL(3),
	/** Divide input prescaler clock by 32 */
	BOD12_PRESCALE_DIV_32      = SUPC_BOD12_PSEL(4),
	/** Divide input prescaler clock by 64 */
	BOD12_PRESCALE_DIV_64      = SUPC_BOD12_PSEL(5),
	/** Divide input prescaler clock by 128 */
	BOD12_PRESCALE_DIV_128     = SUPC_BOD12_PSEL(6),
	/** Divide input prescaler clock by 256 */
	BOD12_PRESCALE_DIV_256     = SUPC_BOD12_PSEL(7),
	/** Divide input prescaler clock by 512 */
	BOD12_PRESCALE_DIV_512     = SUPC_BOD12_PSEL(8),
	/** Divide input prescaler clock by 1024 */
	BOD12_PRESCALE_DIV_1024    = SUPC_BOD12_PSEL(9),
	/** Divide input prescaler clock by 2048 */
	BOD12_PRESCALE_DIV_2048    = SUPC_BOD12_PSEL(10),
	/** Divide input prescaler clock by 4096 */
	BOD12_PRESCALE_DIV_4096    = SUPC_BOD12_PSEL(11),
	/** Divide input prescaler clock by 8192 */
	BOD12_PRESCALE_DIV_8192    = SUPC_BOD12_PSEL(12),
	/** Divide input prescaler clock by 16384 */
	BOD12_PRESCALE_DIV_16384   = SUPC_BOD12_PSEL(13),
	/** Divide input prescaler clock by 32768 */
	BOD12_PRESCALE_DIV_32768   = SUPC_BOD12_PSEL(14),
	/** Divide input prescaler clock by 65536 */
	BOD12_PRESCALE_DIV_65536   = SUPC_BOD12_PSEL(15),
};

/**
 * \brief Brown Out Detector sampling modes in active sleep mode.
 *
 * List of possible BOD12 module voltage sampling modes in active sleep mode.
 */
enum bod12_mode_in_active {
	/** BOD12 will sample the supply line continuously */
	BOD12_ACTCFG_CONTINUOUS = 0,
	/** BOD12 will use the BOD12 sampling clock (1KHz) to sample the supply line */
	BOD12_ACTCFG_SAMPLED    = SUPC_BOD12_ACTCFG,
};

/**
 * \brief Brown Out Detector sampling modes in standby sleep mode.
 *
 * List of possible BOD12 module voltage sampling modes in standby sleep mode.
 */
enum bod12_mode_in_standby {
	/** BOD12 will sample the supply line continuously */
	BOD12_STDBYCFG_CONTINUOUS = 0,
	/** BOD12 will use the BOD12 sampling clock (1KHz) to sample the supply line */
	BOD12_STDBYCFG_SAMPLED    = SUPC_BOD12_STDBYCFG,
};

/**
 * \brief Brown Out Detector detection actions.
 *
 * List of possible BOD12 actions when a BOD12 module detects a brown-out condition.
 */
enum bod12_action {
	/** A BOD12 detect will do nothing, and the BOD12 state must be polled */
	BOD12_ACTION_NONE      = SUPC_BOD12_ACTION(0),
	/** A BOD12 detect will reset the device */
	BOD12_ACTION_RESET     = SUPC_BOD12_ACTION(1),
	/** A BOD12 detect will fire an interrupt */
	BOD12_ACTION_INTERRUPT = SUPC_BOD12_ACTION(2),
};

/** Configuration structure for a BOD12 module. */
struct bod12_config {
	/** Input sampler clock prescaler factor, to reduce the 1KHz clock from the
	 *  ULP32K to lower the sampling rate of the BOD12 */
	enum bod12_prescale prescaler;
	/** BOD12 configuration in active mode */
	enum bod12_mode_in_active mode_in_active;
	/** BOD12 configuration in backup sleep mode */
	enum bod12_mode_in_standby mode_in_standby;
	/** Action to perform when a low power detection is made */
	enum bod12_action action;
	/** BOD12 level to trigger at (see electrical section of device datasheet) */
	uint8_t level;
	/** If \c true, the BOD12 is kept enabled and sampled during device sleep */
	bool run_in_standby;
	/** If \c true, enables detection hysteresis */
	bool hysteresis;
};


/**
 * \name Configuration and Initialization
 * @{
 */

/**
 * \brief Get default BOD33 configuration.
 *
 * The default BOD33 configuration is:
 * - Clock prescaler set to divide the input clock by two
 * - Continuous in active mode
 * - Continuous in standby mode
 * - Monitor the V<SUB>DD</SUB> power pin
 * - No action on BOD33 detect
 * - Hysteresis enabled
 * - BOD33 level 0x7 on V<SUB>DD</SUB>
 * - BOD33 level 0x7 on V<SUB>BAT</SUB>
 * - BOD33 kept enabled during device sleep
 * - BOD33 kept enabled during standby
 *
 * \param[out] conf  BOD33 configuration struct to set to default settings
 */
static inline void bod33_get_config_defaults(
		struct bod33_config *const conf)
{
	/* Sanity check arguments */
	Assert(conf);

	conf->prescaler       = BOD33_PRESCALE_DIV_2;
	conf->monitor         = BOD33_VMON_VDD;
	conf->mode_in_active  = BOD33_ACTCFG_CONTINUOUS;
	conf->mode_in_standby = BOD33_STDBYCFG_CONTINUOUS;
	conf->action          = BOD33_ACTION_NONE;
	conf->level           = 0x7;
	conf->backuplevel     = 0x7;
	conf->run_in_backup   = true;
	conf->run_in_standby  = true;
	conf->hysteresis      = true;
}

enum status_code bod33_set_config(
		struct bod33_config *const conf);

/**
 * \brief Enables a configured BOD33 module.
 *
 * Enables the BOD33 module that has been previously configured.
 *
 * \return Error code indicating the status of the enable operation.
 *
 * \retval STATUS_OK               If the BOD33 was successfully enabled
 */
static inline enum status_code bod33_enable(void)
{
	SUPC->BOD33.reg |= SUPC_BOD33_ENABLE;
	while (!(SUPC->STATUS.reg & SUPC_STATUS_B33SRDY)) {
		/* Wait for BOD33 register sync ready */
	}

	return STATUS_OK;
}

/**
 * \brief Disables an enabled BOD33 module.
 *
 * Disables the BOD33 module that was previously enabled.
 *
 * \return Error code indicating the status of the disable operation.
 *
 * \retval STATUS_OK               If the BOD33 was successfully disabled
 */
static inline enum status_code bod33_disable(void)
{
	SUPC->INTENCLR.reg = SUPC_INTENCLR_BOD33RDY | SUPC_INTENCLR_BOD33DET | SUPC_INTENCLR_B33SRDY;
	SUPC->INTFLAG.reg = SUPC_INTFLAG_BOD33RDY | SUPC_INTFLAG_BOD33DET | SUPC_INTFLAG_B33SRDY;
	SUPC->BOD33.reg &= ~SUPC_BOD33_ENABLE;
	return STATUS_OK;
}

/**
 * \brief Checks if the BOD33 low voltage detection has occurred.
 *
 * Determines if the BOD33 has detected a voltage lower than its
 * configured threshold.
 *
 * \return Detection status of the BOD33.
 *
 * \retval true   If the BOD33 has detected a low voltage condition
 * \retval false  If the BOD33 has not detected a low voltage condition
 */
static inline bool bod33_is_detected(void)
{
	return SUPC->STATUS.bit.BOD33DET;
}

/**
 * \brief Clears the low voltage detection state of the BOD33.
 *
 * Clears the low voltage condition of BOD33 module, so that new
 * low voltage conditions can be detected.
 *
 */
static inline void bod33_clear_detected(void)
{
	SUPC->INTFLAG.reg = SUPC_INTFLAG_BOD33DET;
	return;
}

/**
 * \brief Get default BOD12 configuration.
 *
 * The default BOD12 configuration is:
 * - Clock prescaler set to divide the input clock by two
 * - Continuous in active mode
 * - Continuous in standby mode
 * - Reset on BOD12 detect
 * - Hysteresis enabled
 * - BOD12 level 0x12
 * - BOD12 kept enabled during device sleep
 *
 * \param[out] conf  BOD12 configuration struct to set to default settings
 */
static inline void bod12_get_config_defaults(
		struct bod12_config *const conf)
{
	/* Sanity check arguments */
	Assert(conf);

	conf->prescaler       = BOD12_PRESCALE_DIV_2;
	conf->mode_in_active  = BOD12_ACTCFG_CONTINUOUS;
	conf->mode_in_standby = BOD12_STDBYCFG_CONTINUOUS;
	conf->action          = BOD12_ACTION_RESET;
	conf->level           = 0x12;
	conf->run_in_standby  = true;
	conf->hysteresis      = true;
}

enum status_code bod12_set_config(
		struct bod12_config *const conf);

/**
 * \brief Enables a configured BOD12 module.
 *
 * Enables the BOD12 module that has been previously configured.
 *
 * \return Error code indicating the status of the enable operation.
 *
 * \retval STATUS_OK               If the BOD12 was successfully enabled
 */
static inline enum status_code bod12_enable(void)
{
	SUPC->BOD12.reg |= SUPC_BOD12_ENABLE;
	while (!(SUPC->STATUS.reg & SUPC_STATUS_B12SRDY)) {
		/* Wait for BOD12 register sync ready */
	}

	return STATUS_OK;
}

/**
 * \brief Disables an enabled BOD12 module.
 *
 * Disables the BOD12 module that was previously enabled.
 *
 * \return Error code indicating the status of the disable operation.
 *
 * \retval STATUS_OK               If the BOD12 was successfully disabled
 */
static inline enum status_code bod12_disable(void)
{
	SUPC->INTENCLR.reg = SUPC_INTENCLR_BOD12RDY | SUPC_INTENCLR_BOD12DET | SUPC_INTENCLR_B12SRDY;
	SUPC->INTFLAG.reg = SUPC_INTFLAG_BOD12RDY | SUPC_INTFLAG_BOD12DET | SUPC_INTFLAG_B12SRDY;
	SUPC->BOD12.reg &= ~SUPC_BOD12_ENABLE;
	return STATUS_OK;
}

/**
 * \brief Checks if the BOD12 low voltage detection has occurred.
 *
 * Determines if the BOD12 has detected a voltage lower than its
 * configured threshold.
 *
 * \return Detection status of the BOD12.
 *
 * \retval true   If the BOD12 has detected a low voltage condition
 * \retval false  If the BOD12 has not detected a low voltage condition
 */
static inline bool bod12_is_detected(void)
{
	return SUPC->STATUS.bit.BOD12DET;
}

/**
 * \brief Clears the low voltage detection state of the BOD12.
 *
 * Clears the low voltage condition of BOD12 module, so that new
 * low voltage conditions can be detected.
 *
 */
static inline void bod12_clear_detected(void)
{
	SUPC->INTFLAG.reg = SUPC_INTFLAG_BOD12DET;
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
 *		<td>42453B</td>
 *		<td>12/2015</td>
 *		<td>Added support for SAM L22</td>
 *	</tr>
 *	<tr>
 *		<td>42453A</td>
 *		<td>06/2015</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */


#ifdef __cplusplus
}
#endif

#endif /* BOD_FEATURE_H_INCLUDED */
