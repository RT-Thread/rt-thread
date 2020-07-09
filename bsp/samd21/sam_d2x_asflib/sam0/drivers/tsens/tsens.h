/**
 * \file
 *
 * \brief SAM Temperature Sensor (TSENS) Driver
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

#ifndef TSENS_H_INCLUDED
#define TSENS_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_tsens_group SAM Temperature Sensor (TSENS) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides
 * an interface for the configuration and management of the device's
 * Configurable Custom Logic functionality.
 *
 * The following peripheral is used by this module:
 *  - TSENS (Temperature Sensor)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM C21
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_tsens_prerequisites
 *  - \ref asfdoc_sam0_tsens_module_overview
 *  - \ref asfdoc_sam0_tsens_special_considerations
 *  - \ref asfdoc_sam0_tsens_extra_info
 *  - \ref asfdoc_sam0_tsens_examples
 *  - \ref asfdoc_sam0_tsens_api_overview
 *
 *
 * \section asfdoc_sam0_tsens_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_tsens_module_overview Module Overview
 *
 * The Temperature Sensor (TSENS) can be used to accurately measure the operating
 * temperature of the device. TSENS accurately measures the operating
 * temperature of the device by comparing the difference in two temperature
 * dependent frequencies to a known frequency. The frequency of the
 * temperature dependent oscillator (TOSC) is measured twice: first with the
 * min configuration and next with the maximum configuration. The resulting signed
 * value is proportional to the temperature and is corrected for offset by the
 * contents of the OFFSET register.
 *
 * Accurately measures a temperature:
 *  - ±1°C over 0°C ~ 60°C
 *  - ±3°C over -40°C ~ 85°C
 *  - ±5°C over -40°C ~ 105°C
 *
 * The number of periods of GCLK_TSENS used for the measurement is defined by
 * the GAIN register. The width of the resulting pulse is measured using a
 * counter clocked by GCLK_TSENS in the up direction for the 1<SUP>st</SUP> phase and in
 * the down 2<SUP>nd</SUP> phase. Register GAIN and OFFSET is loaded from NVM, or can also
 * be fixed by user.
 * \f[
 *    VALUE = OFFSET + (\frac{f_{TOSCMIN} - f_{TOSCMAX}}{f_{GCLK}}) \times GAIN
 * \f]
 *
 * \note If fix this bitfield, the relationship between GCLK frequency, GAIN
 * and resolution as below:
 * <table>
 *  <tr>
 *	  <th>Resolution (#/°C)</th>
 *	  <th>GAIN@48MHz</th>
 *	  <th>GAIN@40MHz</th>
 *	</tr>
 *	<tr>
 *	  <td>&times;1 (1°C)</td>
 *    <td>960</td>
 *    <td>800</td>
 *  </tr>
 *	<tr>
 *	  <td>&times;10 (0.1°C)</td>
 *    <td>9600</td>
 *    <td>8000</td>
 *  </tr>
 *	<tr>
 *	  <td>&times;100 (0.01°C)</td>
 *    <td>96000</td>
 *    <td>80000</td>
 *  </tr>
 * </table>
 *
 * \subsection asfdoc_sam0_tsens_module_overview_window_monitor Window Monitor
 * The TSENS module window monitor function can be used to automatically
 * compare the conversion result against a predefined pair of upper and
 * lower threshold values.
 *
 *
 * \subsection asfdoc_sam0_tsens_module_overview_events Events
 * Event generation and event actions are configurable in the TSENS.
 *
 * The TSENS has one actions that can be triggered upon event reception:
 * \li Start conversion
 *
 * The TSENS can generate the following output event:
 * \li Window monitor
 *
 * If the event actions are enabled in the configuration, any incoming event
 * will trigger the action.
 *
 * If the window monitor event is enabled, an event will be generated
 * when the configured window condition is detected.
 *
 * \section asfdoc_sam0_tsens_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 *
 * \section asfdoc_sam0_tsens_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_tsens_extra. This includes:
 *  - \ref asfdoc_sam0_tsens_extra_acronyms
 *  - \ref asfdoc_sam0_tsens_extra_dependencies
 *  - \ref asfdoc_sam0_tsens_extra_errata
 *  - \ref asfdoc_sam0_tsens_extra_history
 *
 *
 * \section asfdoc_sam0_tsens_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_tsens_exqsg.
 *
 *
 * \section asfdoc_sam0_tsens_api_overview API Overview
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system.h>

/**
 * The magnitude of the temperature measurement value decreases with increasing
 * temperature, i.e. it has a negative temperature coefficient.
 * \ref asfdoc_sam0_tsens_extra_errata "Errata reference: 14476".
 */
#define ERRATA_14476       true

/**
 * \name Module Status Flags
 *
 * TSENS status flags, returned by \ref tsens_get_status() and cleared by
 * \ref tsens_clear_status().
 *
 * @{
 */

/** TSENS result ready. */
#define TSENS_STATUS_RESULT_READY  (1UL << 0)
/** TSENS result overwritten before read. */
#define TSENS_STATUS_OVERRUN       (1UL << 1)
/** Window monitor match. */
#define TSENS_STATUS_WINDOW        (1UL << 2)
/** TSENS result overflows. */
#define TSENS_STATUS_OVERFLOW      (1UL << 3)

/** @} */

/**
 * \brief TSENS window monitor mode enum.
 *
 * Enum for the possible window monitor modes for the TSENS.
 *
 */
enum tsens_window_mode {
	/** No window mode */
	TSENS_WINDOW_MODE_DISABLE          = TSENS_CTRLC_WINMODE_DISABLE,
	/** RESULT > WINLT */
	TSENS_WINDOW_MODE_ABOVE            = TSENS_CTRLC_WINMODE_ABOVE,
	/** RESULT < WINUT */
	TSENS_WINDOW_MODE_BELOW            = TSENS_CTRLC_WINMODE_BELOW,
	/** WINLT < RESULT < WINUT */
	TSENS_WINDOW_MODE_INSIDE           = TSENS_CTRLC_WINMODE_INSIDE,
	/** !(WINLT < RESULT < WINUT) */
	TSENS_WINDOW_MODE_OUTSIDE          = TSENS_CTRLC_WINMODE_OUTSIDE,
	/** VALUE > WINUT with hysteresis to WINLT */
	TSENS_WINDOW_MODE_HYST_ABOVE       = TSENS_CTRLC_WINMODE_HYST_ABOVE,
	/** VALUE < WINLT with hysteresis to WINUT */
	TSENS_WINDOW_MODE_HYST_BELOW       = TSENS_CTRLC_WINMODE_HYST_BELOW,
};

/**
 * \brief TSENS event action enum.
 *
 * Enum for the possible actions to take on an incoming event.
 *
 */
enum tsens_event_action {
	/** Event action disabled */
	TSENS_EVENT_ACTION_DISABLED         = 0,
	/** Start conversion */
	TSENS_EVENT_ACTION_START_CONV       = TSENS_EVCTRL_STARTEI,
};

/**
 * \brief Window monitor configuration structure.
 *
 * Window monitor configuration structure.
 */
struct tsens_window_config {
	/** Selected window mode */
	enum tsens_window_mode window_mode;
	/** Lower window value */
	int32_t window_lower_value;
	/** Upper window value */
	int32_t window_upper_value;
};

/**
 * \brief TSENS event enable/disable structure.
 *
 * Event flags for the TSENS module. This is used to enable and
 * disable events via \ref tsens_enable_events() and \ref tsens_disable_events().
 */
struct tsens_events {
	/** Enable event generation on window monitor */
	bool generate_event_on_window_monitor;
};

/**
 * \brief Calibration configuration structure.
 *
 * Calibration configuration structure.
 */
struct tsens_calibration {
	/** Time amplifier gain */
	uint32_t gain;
	/** Offset correction */
	int32_t offset;
};

/**
 * \brief TSENS configuration structure.
 *
 * Configuration structure for an TSENS instance. This structure should be
 * initialized by the \ref tsens_get_config_defaults() function before being
 * modified by the user application.
 */
struct tsens_config {
	/** GCLK generator used to clock the peripheral */
	enum gclk_generator clock_source;
	/** Enables free running mode if true */
	bool free_running;
	/** Enables TSENS in standby sleep mode if true */
	bool run_in_standby;
	/** Window monitor configuration structure */
	struct tsens_window_config window;
	/** Event action to take on incoming event */
	enum tsens_event_action event_action;
	/** Calibration value */
	struct tsens_calibration calibration;
};


/**
 * \name Driver Initialization and Configuration
 * @{
 */
enum status_code tsens_init(struct tsens_config *config);
void tsens_get_config_defaults(struct tsens_config *const config);

/** @} */

/**
 * \name Status Management
 * @{
 */

/**
 * \brief Retrieves the current module status.
 *
 * Retrieves the status of the module, giving overall state information.
 *
 * \return Bit mask of TSENS status flags.
 *
 * \retval TSENS_STATUS_RESULT_READY  TSENS result is ready to be read
 * \retval TSENS_STATUS_OVERRUN       TSENS result overwritten before read
 * \retval TSENS_STATUS_WINDOW        TSENS has detected a value inside the set
 *                                    window range
 * \retval TSENS_STATUS_OVERFLOW      TSENS result overflows
 */
static inline uint32_t tsens_get_status(void)
{
	uint32_t int_flags = TSENS->INTFLAG.reg;

	uint32_t status_flags = 0;

	/* Check for TSENS Result Ready */
	if (int_flags & TSENS_INTFLAG_RESRDY) {
		status_flags |= TSENS_STATUS_RESULT_READY;
	}

	/* Check for TSENS Overrun */
	if (int_flags & TSENS_INTFLAG_OVERRUN) {
		status_flags |= TSENS_STATUS_OVERRUN;
	}

	/* Check for TSENS Window Match */
	if (int_flags & TSENS_INTFLAG_WINMON) {
		status_flags |= TSENS_STATUS_WINDOW;
	}

	/* Check for TSENS overflow */
	if (int_flags & TSENS_INTFLAG_OVF) {
		status_flags |= TSENS_STATUS_OVERFLOW;
	}

	return status_flags;
}

/**
 * \brief Clears a module status flag.
 *
 * Clears the given status flag of the module.
 *
 * \param[in] module_inst   Pointer to the TSENS software instance struct
 * \param[in] status_flags  Bitmask of \c TSENS_STATUS_* flags to clear
 */
static inline void tsens_clear_status(const uint32_t status_flags)
{
	uint32_t int_flags = 0;

	/* Check for TSENS Result Ready */
	if (status_flags & TSENS_INTFLAG_RESRDY) {
		 int_flags |= TSENS_STATUS_RESULT_READY;
	}

	/* Check for TSENS Overrun */
	if (status_flags & TSENS_INTFLAG_OVERRUN) {
		int_flags |= TSENS_STATUS_OVERRUN;
	}

	/* Check for TSENS Window Match */
	if (status_flags & TSENS_INTFLAG_WINMON) {
		int_flags |= TSENS_STATUS_WINDOW;
	}

	/* Check for TSENS overflow */
	if (status_flags & TSENS_INTFLAG_OVF) {
		int_flags |= TSENS_STATUS_OVERFLOW;
	}

	/* Clear interrupt flag */
	TSENS->INTFLAG.reg = int_flags;
}

/** @} */

/**
 * \name Enable, Disable, and Reset TSENS Module, Start Conversion and Read Result
 * @{
 */

/**
 * \brief Determines if the hardware module is currently synchronizing to the bus.
 *
 * Checks to see if the underlying hardware peripheral module(s) are currently
 * synchronizing across multiple clock domains to the hardware bus. This
 * function can be used to delay further operations on a module until such time
 * that it is ready, to prevent blocking delays for synchronization in the
 * user application.
 *
 * \return Synchronization status of the underlying hardware module(s).
 *
 * \retval true  If the module synchronization is ongoing
 * \retval false If the module has completed synchronization
 */
static inline bool tsens_is_syncing(void)
{
	if (TSENS->SYNCBUSY.reg) {
		return true;
	}

	return false;
}

/**
 * \brief Enables the TSENS module.
 *
 * Enables an TSENS module that has previously been configured.

 */
static inline void tsens_enable(void)
{
	TSENS->CTRLA.reg |= TSENS_CTRLA_ENABLE;

	while (tsens_is_syncing()) {
		/* Wait for synchronization */
	}
}

/**
 * \brief Disables the TSENS module.
 *
 * Disables an TSENS module that was previously enabled.
 *
 */
static inline void tsens_disable(void)
{
	TSENS->INTENCLR.reg = TSENS_INTENCLR_MASK;
	TSENS->INTFLAG.reg = TSENS_INTFLAG_MASK;
	TSENS->CTRLA.reg &= ~TSENS_CTRLA_ENABLE;

	while (tsens_is_syncing()) {
		/* Wait for synchronization */
	}
}

/**
 * \brief Resets the TSENS module.
 *
 * Resets an TSENS module, clearing all module state and registers to their
 * default values.
 *
 */
static inline void tsens_reset(void)
{
	/* Disable to make sure the pipeline is flushed before reset */
	tsens_disable();

	/* Software reset the module */
	TSENS->CTRLA.reg |= TSENS_CTRLA_SWRST;

	while (tsens_is_syncing()) {
		/* Wait for synchronization */
	}
}


/**
 * \brief Enables an TSENS event output.
 *
 *  Enables one or more input or output events to or from the TSENS module. See
 *  \ref tsens_events "tsens_events" for a list of events this module supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in] events       Struct containing flags of events to enable
 */
static inline void tsens_enable_events(struct tsens_events *const events)
{
	/* Sanity check arguments */
	Assert(events);

	uint32_t event_mask = 0;

	/* Configure Window Monitor event */
	if (events->generate_event_on_window_monitor) {
		event_mask |= TSENS_EVCTRL_WINEO;
	}

	TSENS->EVCTRL.reg |= event_mask;
}

/**
 * \brief Disables an TSENS event output.
 *
 *  Disables one or more output events to or from the TSENS module. See
 *  \ref tsens_events "tsens_events" for a list of events this module supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in] events       Struct containing flags of events to disable
 */
static inline void tsens_disable_events(struct tsens_events *const events)
{
	/* Sanity check arguments */
	Assert(events);

	uint32_t event_mask = 0;

	/* Configure Window Monitor event */
	if (events->generate_event_on_window_monitor) {
		event_mask |= TSENS_EVCTRL_WINEO;
	}

	TSENS->EVCTRL.reg &= ~event_mask;
}

/**
 * \brief Start a TSENS conversion.
 *
 * Start a new TSENS conversion.
 *
 */
static inline void tsens_start_conversion(void)
{
	TSENS->CTRLB.reg |= TSENS_CTRLB_START;

	while (tsens_is_syncing()) {
		/* Wait for synchronization */
	}
}

enum status_code tsens_read(int32_t *result);
/** @} */
/** @} */


/**
 * \page asfdoc_sam0_tsens_extra Extra Information for TSENS Driver
 *
 * \section asfdoc_sam0_tsens_extra_acronyms Acronym
 * Below is a table listing the acronym used in this module, along with their
 * intended meaning.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *  <tr>
 *		<td>TSENS</td>
 *		<td>Temperature Sensor</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_tsens_extra_dependencies Dependencies
 * This driver has no dependencies.
 *
 *
 * \section asfdoc_sam0_tsens_extra_errata Errata
 * Errata reference: 14476.
 *
 * The magnitude of the temperature measurement value decreases with increasing
 * temperature, i.e. it has a negative temperature coefficient.
 *
 *
 * \section asfdoc_sam0_tsens_extra_history Module History
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
 * \page asfdoc_sam0_tsens_exqsg Examples for TSENS Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_tsens_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_tsens_basic_use_case
 *  - \subpage asfdoc_sam0_tsens_basic_use_case_callback
 *
 * \page asfdoc_sam0_tsens_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</th>
 *		<th>Date</th>
 *		<th>Comments</th>
 *	</tr>
 *	<tr>
 *		<td>42542A</td>
 *		<td>12/2015</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */

#ifdef __cplusplus
}
#endif

#endif /* TSENS_H_INCLUDED */

