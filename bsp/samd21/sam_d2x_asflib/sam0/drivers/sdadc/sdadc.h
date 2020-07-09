/**
 * \file
 *
 * \brief SAM Sigma-Delta Analog-to-Digital Converter (SDADC) Driver
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

#ifndef SDADC_H_INCLUDED
#define SDADC_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_sdadc_group SAM Sigma-Delta Analog-to-Digital Converter (SDADC) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for the configuration
 * and management of the device's SDADC functionality.
 *
 * The following peripheral is used by this module:
 *  - SDADC (Sigma-Delta Analog-to-Digital Converter)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM C21
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_sdadc_prerequisites
 *  - \ref asfdoc_sam0_sdadc_module_overview
 *  - \ref asfdoc_sam0_sdadc_special_considerations
 *  - \ref asfdoc_sam0_sdadc_extra_info
 *  - \ref asfdoc_sam0_sdadc_examples
 *  - \ref asfdoc_sam0_sdadc_api_overview
 *
 *
 * \section asfdoc_sam0_sdadc_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_sdadc_module_overview Module Overview
 *
 * The Sigma-Delta Analog-to-Digital Converter (SDADC) converts analog signals to
 * digital values. The sigma-delta architecture of the SDADC implies a filtering
 * and a decimation of the bitstream at the output of the SDADC. The input selection
 * is up to three input analog channels.
 *
 * The SDADC provides up to 16-bit resolution at about 1000 samples per second (1KSPS)
 * and sized 24 bits signed result to handle filtering and gain correction without overflow.
 * The SDADC measurements can be started by either application software or an incoming
 * event from another peripheral in the device.
 *
 * The conversion is performed on a full range between 0V and the reference voltage.
 * Both internal and external reference voltages can be selected. The reference range
 * must be set to match the voltage of the reference used. Analog inputs between
 * these voltages convert to values based on a linear conversion.
 *
 *
 * \subsection asfdoc_sam0_sdadc_module_overview_clock Sample Clock
 * A generic clock (GCLK_SDADC) is required to generate the CLK_SDADC to the SDADC
 * module. The SDADC features a prescaler, which enables conversion at lower clock
 * rates than the input Generic Clock to the SDADC module.
 *
 * The SDADC data sampling frequency (CLK_SDADC_FS) in the SDADC module is the
 * CLK_SDADC/4, the reduction comes from the phase generator between the prescaler
 * and the SDADC.
 *
 * OSR is the Over Sampling Ratio, which can be modified to change the output data
 * rate. The conversion time depends on the selected OSR and the sampling frequency
 * of the SDADC.
 * The conversion time can be described with:
 * \f[
 * t_{SAMPLE} = \frac {22 + 3 \times OSR} {CLK \_ SDADC \_ FS}
 * \f]
 * -# Initialization of the SDADC (22 sigma-delta samples).
 * -# Filling of the decimation filter (3*OSR sigma-delta samples).
 *
 * \subsection asfdoc_sam0_sdadc_module_overview_offset_corr Gain and Offset Correction
 * A specific offset, gain, and shift can be applied to each source of the SDADC
 * by performing the following operation:
 * \f[
 * Data = (Data_{0} + OFFSET) \times \frac {GAIN}{2^{SHIFT}}
 * \f]
 *
 *
 * \subsection asfdoc_sam0_sdadc_module_overview_window_monitor Window Monitor
 * The SDADC module window monitor function can be used to automatically compare
 * the conversion result against a predefined pair of upper and lower
 * threshold values.
 *
 *
 * \subsection asfdoc_sam0_sdadc_module_overview_events Events
 * Event generation and event actions are configurable in the SDADC.
 *
 * The SDADC has two actions that can be triggered upon event reception:
 * \li Start conversion
 * \li Conversion flush
 *
 * The SDADC can generate two kinds of events:
 * \li Window monitor
 * \li Result ready
 *
 * If the event actions are enabled in the configuration, any incoming event
 * will trigger the action.
 *
 * If the window monitor event is enabled, an event will be generated
 * when the configured window condition is detected.
 *
 * If the result ready event is enabled, an event will be generated when a
 * conversion is completed.
 *
 *
 * \section asfdoc_sam0_sdadc_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 *
 * \section asfdoc_sam0_sdadc_extra_info Extra Information
 *
 * For extra information see \ref asfdoc_sam0_sdadc_extra. This includes:
 *  - \ref asfdoc_sam0_sdadc_extra_acronyms
 *  - \ref asfdoc_sam0_sdadc_extra_dependencies
 *  - \ref asfdoc_sam0_sdadc_extra_errata
 *  - \ref asfdoc_sam0_sdadc_extra_history
 *
 *
 * \section asfdoc_sam0_sdadc_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_sdadc_exqsg.
 *
 *
 * \section asfdoc_sam0_sdadc_api_overview API Overview
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system.h>

#if SDADC_CALLBACK_MODE == true
#  include <system_interrupt.h>

#if !defined(__DOXYGEN__)
extern struct sdadc_module *_sdadc_instances[SDADC_INST_NUM];
#endif

/** Forward definition of the device instance. */
struct sdadc_module;

/** Type of the callback functions. */
typedef void (*sdadc_callback_t)(const struct sdadc_module *const module);

/**
 * \brief SDADC Callback enum.
 *
 * Callback types for SDADC callback driver.
 *
 */
enum sdadc_callback {
	/** Callback for buffer received */
	SDADC_CALLBACK_READ_BUFFER,
	/** Callback when window is hit */
	SDADC_CALLBACK_WINDOW,
	/** Callback for error */
	SDADC_CALLBACK_ERROR,
#  if !defined(__DOXYGEN__)
	/** Number of available callbacks */
	SDADC_CALLBACK_N,
#  endif
};

#endif

/**
 * \name Module Status Flags
 *
 * SDADC status flags, returned by \ref sdadc_get_status() and cleared by
 * \ref sdadc_clear_status().
 *
 * @{
 */

/** SDADC result ready. */
#define SDADC_STATUS_RESULT_READY  (1UL << 0)
/** SDADC result overwritten before read. */
#define SDADC_STATUS_OVERRUN       (1UL << 1)
/** Window monitor match. */
#define SDADC_STATUS_WINDOW        (1UL << 2)

/** @} */

/**
 * \brief SDADC reference voltage enum.
 *
 * Enum for the possible reference voltages for the SDADC.
 *
 */
enum sdadc_reference_select {
	/** Internal Bandgap Reference */
	SDADC_REFERENCE_INTREF = SDADC_REFCTRL_REFSEL(0),
	/** External reference B */
	SDADC_REFERENCE_AREFB  = SDADC_REFCTRL_REFSEL(1),
	/** DACOUT */
	SDADC_REFERENCE_DACOUT = SDADC_REFCTRL_REFSEL(2),
	/** VDDANA */
	SDADC_REFERENCE_INTVCC = SDADC_REFCTRL_REFSEL(3),
};

/**
 * \brief SDADC reference range enum.
 *
 * Enum for the matched voltage range of the SDADC reference used.
 *
 */
enum sdadc_reference_range {
	/** Vref < 1.4V */
	SDADC_REFRANGE_0 = SDADC_REFCTRL_REFRANGE(0),
	/** 1.4V < Vref < 2.4V */
	SDADC_REFRANGE_1 = SDADC_REFCTRL_REFRANGE(1),
	/** 2.4V < Vref < 3.6V */
	SDADC_REFRANGE_2 = SDADC_REFCTRL_REFRANGE(2),
	/** Vref > 3.6V */
	SDADC_REFRANGE_3 = SDADC_REFCTRL_REFRANGE(3),
};

/**
 * \brief SDADC over sampling ratio enum.
 *
 * Enum for the over sampling ratio, which change the output data rate.
 *
 */
enum sdadc_over_sampling_ratio {
	/** SDADC over Sampling Ratio is 64 */
	SDADC_OVER_SAMPLING_RATIO64    = SDADC_CTRLB_OSR(0),
	/** SDADC over Sampling Ratio is 128 */
	SDADC_OVER_SAMPLING_RATIO128   = SDADC_CTRLB_OSR(1),
	/** SDADC over Sampling Ratio is 256 */
	SDADC_OVER_SAMPLING_RATIO256   = SDADC_CTRLB_OSR(2),
	/** SDADC over Sampling Ratio is 512 */
	SDADC_OVER_SAMPLING_RATIO512   = SDADC_CTRLB_OSR(3),
	/** SDADC over Sampling Ratio is 1024 */
	SDADC_OVER_SAMPLING_RATIO1024  = SDADC_CTRLB_OSR(4),
};

/**
 * \brief SDADC window monitor mode enum.
 *
 * Enum for the possible window monitor modes for the SDADC.
 *
 */
enum sdadc_window_mode {
	/** No window mode */
	SDADC_WINDOW_MODE_DISABLE          = SDADC_WINCTRL_WINMODE(0),
	/** RESULT > WINLT */
	SDADC_WINDOW_MODE_ABOVE            = SDADC_WINCTRL_WINMODE(1),
	/** RESULT < WINUT */
	SDADC_WINDOW_MODE_BELOW            = SDADC_WINCTRL_WINMODE(2),
	/** WINLT < RESULT < WINUT */
	SDADC_WINDOW_MODE_INSIDE           = SDADC_WINCTRL_WINMODE(3),
	/** !(WINLT < RESULT < WINUT) */
	SDADC_WINDOW_MODE_OUTSIDE          = SDADC_WINCTRL_WINMODE(4),
};

/**
 * \brief SDADC event action enum.
 *
 * Enum for the possible actions to take on an incoming event.
 *
 */
enum sdadc_event_action {
	/** Event action disabled */
	SDADC_EVENT_ACTION_DISABLED         = 0,
	/** Flush SDADC and start conversion */
	SDADC_EVENT_ACTION_FLUSH_START_CONV = SDADC_EVCTRL_FLUSHEI,
	/** Start conversion */
	SDADC_EVENT_ACTION_START_CONV       = SDADC_EVCTRL_STARTEI,
};

/**
 * \brief SDADC MUX input selection enum.
 *
 * Enum for the possible MUX input selections for the SDADC.
 *
 */
enum sdadc_mux_input {
	/** Select SDADC AINN0 and AINP0 pins */
	SDADC_MUX_INPUT_AIN0    = SDADC_INPUTCTRL_MUXSEL_AIN0,
	/** Select SDADC AINN1 and AINP1 pins */
	SDADC_MUX_INPUT_AIN1    = SDADC_INPUTCTRL_MUXSEL_AIN1,
	/** Select SDADC AINN2 and AINP2 pins */
	SDADC_MUX_INPUT_AIN2    = SDADC_INPUTCTRL_MUXSEL_AIN2,
};

#if SDADC_CALLBACK_MODE == true
/**
 * Enum for the possible SDADC interrupt flags.
 */
enum sdadc_interrupt_flag {
	/** SDADC result ready */
	SDADC_INTERRUPT_RESULT_READY = SDADC_INTFLAG_RESRDY,
	/** SDADC result overwritten before read */
	SDADC_INTERRUPT_OVERRUN      = SDADC_INTFLAG_OVERRUN,
	/** Window monitor match */
	SDADC_INTERRUPT_WINDOW       = SDADC_INTFLAG_WINMON,
};
#endif

/**
 * \brief Reference configuration structure.
 *
 * Reference configuration structure.
 */
struct sdadc_reference {
	/** Reference voltage selection */
	enum sdadc_reference_select ref_sel;
	/** Reference voltage range */
	enum sdadc_reference_select ref_range;
	/** Reference buffer turning switch */
	bool on_ref_buffer;
};

/**
 * \brief Window monitor configuration structure.
 *
 * Window monitor configuration structure.
 */
struct sdadc_window_config {
	/** Selected window mode */
	enum sdadc_window_mode window_mode;
	/** Lower window value */
	int32_t window_lower_value;
	/** Upper window value */
	int32_t window_upper_value;
};

/**
 * \brief SDADC event enable/disable structure.
 *
 * Event flags for the SDADC module. This is used to enable and
 * disable events via \ref sdadc_enable_events() and \ref sdadc_disable_events().
 */
struct sdadc_events {
	/** Enable event generation on conversion done */
	bool generate_event_on_conversion_done;
	/** Enable event generation on window monitor */
	bool generate_event_on_window_monitor;
};

/**
 * \brief SDADC correction configuration structure.
 *
 * Offset, gain, and shift correction configuration structure.
 * Part of the \ref sdadc_config struct will be initialized by
 * \ref sdadc_get_config_defaults.
 */
struct sdadc_correction_config {
	/** Offset correction */
	int32_t offset_correction;
	/** Gain correction */
	uint16_t gain_correction;
	/** Shift correction */
	uint8_t shift_correction;
};

/**
 * \brief SDADC configuration structure.
 *
 * Configuration structure for an SDADC instance. This structure should be
 * initialized by the \ref sdadc_get_config_defaults()
 * function before being modified by the user application.
 */
struct sdadc_config {
	/** GCLK generator used to clock the peripheral */
	enum gclk_generator clock_source;
	/** Voltage reference */
	struct sdadc_reference reference;
	/** Over sampling ratio */
	enum sdadc_over_sampling_ratio osr;
	/** Clock prescaler */
	uint8_t clock_prescaler;
	/** Skip Count */
	uint8_t skip_count;
	/** MUX input */
	enum sdadc_mux_input mux_input;
	/** Enables free running mode if true */
	bool freerunning;
	/** Enables SDADC in standby sleep mode if true */
	bool run_in_standby;
	/** Enables SDADC depend on other peripheral if true */
	bool on_command;
	/** Enables positive input in the sequence if true */
	bool seq_enable[3];
	/** Window monitor configuration structure */
	struct sdadc_window_config window;
	/** Gain and offset correction configuration structure */
	struct sdadc_correction_config correction;
	/** Event action to take on incoming event */
	enum sdadc_event_action event_action;
};

/**
 * \brief SDADC software device instance structure.
 *
 * SDADC software instance structure, used to retain software state information
 * of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct sdadc_module {
#if !defined(__DOXYGEN__)
	/** Pointer to SDADC hardware module */
	Sdadc *hw;
	/** Keep reference configuration so we know when enable is called */
	struct sdadc_reference reference;
#  if SDADC_CALLBACK_MODE == true
	/** Array to store callback functions */
	sdadc_callback_t callback[SDADC_CALLBACK_N];
	/** Pointer to buffer used for SDADC results */
	volatile int32_t *job_buffer;
	/** Remaining number of conversions in current job */
	volatile uint16_t remaining_conversions;
	/** Bit mask for callbacks registered */
	uint8_t registered_callback_mask;
	/** Bit mask for callbacks enabled */
	uint8_t enabled_callback_mask;
	/** Holds the status of the ongoing or last conversion job */
	volatile enum status_code job_status;
	/** If software triggering is needed */
	bool software_trigger;
#  endif
#endif
};

/**
 * \name Driver Initialization and Configuration
 * @{
 */
enum status_code sdadc_init(
		struct sdadc_module *const module_inst,
		Sdadc *hw,
		struct sdadc_config *config);

/**
 * \brief Initializes an SDADC configuration structure to defaults.
 *
 * Initializes a given SDADC configuration struct to a set of known default
 * values. This function should be called on any new instance of the
 * configuration struct before being modified by the user application.
 *
 * The default configuration is as follows:
 *  \li GCLK generator 0 (GCLK main) clock source
 *  \li Positive reference 1
 *  \li Div 2 clock prescaler
 *  \li Over Sampling Ratio is 64
 *  \li Skip 0 samples
 *  \li MUX input on SDADC AIN1
 *  \li All events (input and generation) disabled
 *  \li Free running disabled
 *  \li Run in standby disabled
 *  \li On command disabled
 *  \li Disable all positive input in sequence
 *  \li Window monitor disabled
 *  \li No gain/offset/shift correction
 *
 * \param[out] config  Pointer to configuration struct to initialize to
 *                     default values
 */
static inline void sdadc_get_config_defaults(struct sdadc_config *const config)
{
	Assert(config);
	config->clock_source                  = GCLK_GENERATOR_0;
	config->reference.ref_sel             = SDADC_REFERENCE_INTREF;
	config->reference.ref_range           = SDADC_REFRANGE_0;
	config->reference.on_ref_buffer       = false;
	config->clock_prescaler               = 2;
	config->osr                           = SDADC_OVER_SAMPLING_RATIO64;
	config->skip_count                    = 2;
	config->mux_input                     = SDADC_MUX_INPUT_AIN1;
	config->event_action                  = SDADC_EVENT_ACTION_DISABLED;
	config->freerunning                   = false;
	config->run_in_standby                = false;
	config->on_command                    = false;
	config->seq_enable[0]                 = false;
	config->seq_enable[1]                 = false;
	config->seq_enable[2]                 = false;
	config->window.window_mode            = SDADC_WINDOW_MODE_DISABLE;
	config->window.window_upper_value     = 0;
	config->window.window_lower_value     = 0;
	config->correction.gain_correction    = 1;
	config->correction.offset_correction  = SDADC_OFFSETCORR_RESETVALUE;
	config->correction.shift_correction   = SDADC_SHIFTCORR_RESETVALUE;
}

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
 * \param[in] module_inst  Pointer to the SDADC software instance struct
 *
 * \return Bitmask of \c SDADC_STATUS_* flags.
 *
 * \retval SDADC_STATUS_RESULT_READY  SDADC result is ready to be read
 * \retval SDADC_STATUS_WINDOW        SDADC has detected a value inside the set
 *                                  window range
 * \retval SDADC_STATUS_OVERRUN       SDADC result has overrun
 */
static inline uint32_t sdadc_get_status(
		struct sdadc_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

	uint32_t int_flags = sdadc_module->INTFLAG.reg;

	uint32_t status_flags = 0;

	/* Check for SDADC Result Ready */
	if (int_flags & SDADC_INTFLAG_RESRDY) {
		status_flags |= SDADC_STATUS_RESULT_READY;
	}

	/* Check for SDADC Window Match */
	if (int_flags & SDADC_INTFLAG_WINMON) {
		status_flags |= SDADC_STATUS_WINDOW;
	}

	/* Check for SDADC Overrun */
	if (int_flags & SDADC_INTFLAG_OVERRUN) {
		status_flags |= SDADC_STATUS_OVERRUN;
	}

	return status_flags;
}

/**
 * \brief Clears a module status flag.
 *
 * Clears the given status flag of the module.
 *
 * \param[in] module_inst   Pointer to the SDADC software instance struct
 * \param[in] status_flags  Bitmask of \c SDADC_STATUS_* flags to clear
 */
static inline void sdadc_clear_status(
		struct sdadc_module *const module_inst,
		const uint32_t status_flags)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

	uint32_t int_flags = 0;

	/* Check for SDADC Result Ready */
	if (status_flags & SDADC_STATUS_RESULT_READY) {
		int_flags |= SDADC_INTFLAG_RESRDY;
	}

	/* Check for SDADC Window Match */
	if (status_flags & SDADC_STATUS_WINDOW) {
		int_flags |= SDADC_INTFLAG_WINMON;
	}

	/* Check for SDADC Overrun */
	if (status_flags & SDADC_STATUS_OVERRUN) {
		int_flags |= SDADC_INTFLAG_OVERRUN;
	}

	/* Clear interrupt flag */
	sdadc_module->INTFLAG.reg = int_flags;
}

/**
 * \brief Get a module sequence flag.
 *
 * Get the given status flag of the module.
 *
 * \param[in]   module_inst   Pointer to the SDADC software instance struct
 * \param[out]  seq_state     Identifies the last conversion done in the sequence
 *
 * \return Status of the SDADC sequence conversion.
 *
 * \retval true  When the sequence start
 * \retval false When the last conversion in a sequence is done
 */
static inline bool sdadc_get_sequence_status(
		struct sdadc_module *const module_inst,
		uint8_t* seq_state)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

	/* Get SDADC result */
	*seq_state = sdadc_module->SEQSTATUS.reg & SDADC_SEQSTATUS_SEQSTATE_Msk;

	return ((sdadc_module->SEQSTATUS.bit.SEQBUSY == 1) ? true : false);
}
/** @} */

/**
 * \name Enable, Disable, and Reset SDADC Module, Start Conversion and Read Result
 * @{
 */

/**
 * \brief Determines if the hardware module(s) are currently synchronizing to the bus.
 *
 * Checks to see if the underlying hardware peripheral module(s) are currently
 * synchronizing across multiple clock domains to the hardware bus. This
 * function can be used to delay further operations on a module until such time
 * that it is ready, to prevent blocking delays for synchronization in the
 * user application.
 *
 * \param[in] module_inst  Pointer to the SDADC software instance struct
 *
 * \return Synchronization status of the underlying hardware module(s).
 *
 * \retval true  If the module synchronization is ongoing
 * \retval false If the module has completed synchronization
 */
static inline bool sdadc_is_syncing(
	struct sdadc_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);

	Sdadc *const sdadc_module = module_inst->hw;

	if (sdadc_module->SYNCBUSY.reg) {
		return true;
	}

	return false;
}

/**
 * \brief Enables the SDADC module.
 *
 * Enables an SDADC module that has previously been configured. If any internal reference
 * is selected it will be enabled.
 *
 * \param[in] module_inst  Pointer to the SDADC software instance struct
 */
static inline enum status_code sdadc_enable(
		struct sdadc_module *const module_inst)
{
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

#if SDADC_CALLBACK_MODE == true
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_SDADC);
#endif

	sdadc_module->CTRLA.reg |= SDADC_CTRLA_ENABLE;
	return STATUS_OK;
}

/**
 * \brief Disables the SDADC module.
 *
 * Disables an SDADC module that was previously enabled.
 *
 * \param[in] module_inst Pointer to the SDADC software instance struct
 */
static inline enum status_code sdadc_disable(
		struct sdadc_module *const module_inst)
{
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

#if SDADC_CALLBACK_MODE == true
	system_interrupt_disable(SYSTEM_INTERRUPT_MODULE_SDADC);
#endif

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Disbale interrupt */
	sdadc_module->INTENCLR.reg = SDADC_INTENCLR_MASK;
	/* Clear interrupt flag */
	sdadc_module->INTFLAG.reg = SDADC_INTFLAG_MASK;

	sdadc_module->CTRLA.reg &= ~SDADC_CTRLA_ENABLE;
	return STATUS_OK;
}

/**
 * \brief Resets the SDADC module.
 *
 * Resets an SDADC module, clearing all module state, and registers to their
 * default values.
 *
 * \param[in] module_inst  Pointer to the SDADC software instance struct
 */
static inline enum status_code sdadc_reset(
		struct sdadc_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

	/* Disable to make sure the pipeline is flushed before reset */
	sdadc_disable(module_inst);

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Software reset the module */
	sdadc_module->CTRLA.reg |= SDADC_CTRLA_SWRST;
	return STATUS_OK;
}


/**
 * \brief Enables an SDADC event input or output.
 *
 *  Enables one or more input or output events to or from the SDADC module. See
 *  \ref sdadc_events for a list of events this module supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in] module_inst  Software instance for the SDADC peripheral
 *  \param[in] events       Struct containing flags of events to enable
 */
static inline void sdadc_enable_events(
		struct sdadc_module *const module_inst,
		struct sdadc_events *const events)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(events);

	Sdadc *const sdadc_module = module_inst->hw;

	uint32_t event_mask = 0;

	/* Configure Window Monitor event */
	if (events->generate_event_on_window_monitor) {
		event_mask |= SDADC_EVCTRL_WINMONEO;
	}

	/* Configure Result Ready event */
	if (events->generate_event_on_conversion_done) {
		event_mask |= SDADC_EVCTRL_RESRDYEO;
	}

	sdadc_module->EVCTRL.reg |= event_mask;
}

/**
 * \brief Disables an SDADC event input or output.
 *
 *  Disables one or more input or output events to or from the SDADC module. See
 *  \ref sdadc_events for a list of events this module supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in] module_inst  Software instance for the SDADC peripheral
 *  \param[in] events       Struct containing flags of events to disable
 */
static inline void sdadc_disable_events(
		struct sdadc_module *const module_inst,
		struct sdadc_events *const events)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(events);

	Sdadc *const sdadc_module = module_inst->hw;

	uint32_t event_mask = 0;

	/* Configure Window Monitor event */
	if (events->generate_event_on_window_monitor) {
		event_mask |= SDADC_EVCTRL_WINMONEO;
	}

	/* Configure Result Ready event */
	if (events->generate_event_on_conversion_done) {
		event_mask |= SDADC_EVCTRL_RESRDYEO;
	}

	sdadc_module->EVCTRL.reg &= ~event_mask;
}

/**
 * \brief Starts an SDADC conversion.
 *
 * Starts a new SDADC conversion.
 *
 * \param[in] module_inst  Pointer to the SDADC software instance struct
 */
static inline void sdadc_start_conversion(
		struct sdadc_module *const module_inst)
{
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	sdadc_module->SWTRIG.reg |= SDADC_SWTRIG_START;
}

/**
 * \brief Reads the SDADC result.
 *
 * Reads the result from an SDADC conversion that was previously started.
 *
 * \param[in]  module_inst  Pointer to the SDADC software instance struct
 * \param[out] result       Pointer to store the result value in
 *
 * \return Status of the SDADC read request.
 * \retval STATUS_OK           The result was retrieved successfully
 * \retval STATUS_BUSY         A conversion result was not ready
 * \retval STATUS_ERR_OVERFLOW The result register has been overwritten by the
 *                             SDADC module before the result was read by the software
 */
static inline enum status_code sdadc_read(
		struct sdadc_module *const module_inst,
		int32_t *result)
{
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(result);

	if (!(sdadc_get_status(module_inst) & SDADC_STATUS_RESULT_READY)) {
		/* Result not ready */
		return STATUS_BUSY;
	}

	Sdadc *const sdadc_module = module_inst->hw;

	/* Get SDADC result */
	*result = ((int32_t)(sdadc_module->RESULT.reg << 8)) >> 8;

	/* Reset ready flag */
	sdadc_clear_status(module_inst, SDADC_STATUS_RESULT_READY);

	if (sdadc_get_status(module_inst) & SDADC_STATUS_OVERRUN) {
		sdadc_clear_status(module_inst, SDADC_STATUS_OVERRUN);
		return STATUS_ERR_OVERFLOW;
	}

	return STATUS_OK;
}

/** @} */

/**
 * \name Runtime Changes of SDADC Module
 * @{
 */

/**
 * \brief Flushes the SDADC pipeline.
 *
 * Flushes the pipeline and restart the SDADC clock on the next peripheral clock
 * edge. All conversions in progress will be lost. When flush is complete, the
 * module will resume where it left off.
 *
 * \param[in] module_inst  Pointer to the SDADC software instance struct
 */
static inline void sdadc_flush(
		struct sdadc_module *const module_inst)
{
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	sdadc_module->SWTRIG.reg |= SDADC_SWTRIG_FLUSH;
}

/**
 * \brief Sets the SDADC window mode.
 *
 * Sets the SDADC window mode to a given mode and value range.
 *
 * \param[in] module_inst         Pointer to the SDADC software instance struct
 * \param[in] window_mode         Window monitor mode to set
 * \param[in] window_lower_value  Lower window monitor threshold value
 * \param[in] window_upper_value  Upper window monitor threshold value
  */
static inline void sdadc_set_window_mode(
		struct sdadc_module *const module_inst,
		const enum sdadc_window_mode window_mode,
		const int16_t window_lower_value,
		const int16_t window_upper_value)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Set window mode */
	sdadc_module->WINCTRL.reg = window_mode << SDADC_WINCTRL_WINMODE_Pos;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Set lower window monitor threshold value */
	sdadc_module->WINLT.reg = window_lower_value << SDADC_WINLT_WINLT_Pos;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Set upper window monitor threshold value */
	sdadc_module->WINUT.reg = window_upper_value << SDADC_WINUT_WINUT_Pos;
}

/**
 * \brief Sets MUX SDADC input pin.
 *
 * Sets the MUX SDADC input pin selection.
 *
 * \param[in] module_inst     Pointer to the SDADC software instance struct
 * \param[in] mux_input       MUX input pin
 */
static inline void sdadc_set_mux_input(
		struct sdadc_module *const module_inst,
		const enum sdadc_mux_input mux_input)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Set mux input pin */
	sdadc_module->INPUTCTRL.reg =
			(sdadc_module->INPUTCTRL.reg & ~SDADC_INPUTCTRL_MUXSEL_Msk) | mux_input;
}


/** @} */

#if SDADC_CALLBACK_MODE == true
/**
 * \name Enable and Disable Interrupts
 * @{
 */

/**
 * \brief Enable interrupt.
 *
 * Enable the given interrupt request from the SDADC module.
 *
 * \param[in] module_inst Pointer to the SDADC software instance struct
 * \param[in] interrupt Interrupt to enable
 */
static inline void sdadc_enable_interrupt(struct sdadc_module *const module_inst,
		enum sdadc_interrupt_flag interrupt)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;
	/* Enable interrupt */
	sdadc_module->INTENSET.reg = interrupt;
}

/**
 * \brief Disable interrupt.
 *
 * Disable the given interrupt request from the SDADC module.
 *
 * \param[in] module_inst Pointer to the SDADC software instance struct
 * \param[in] interrupt Interrupt to disable
 */
static inline void sdadc_disable_interrupt(struct sdadc_module *const module_inst,
		enum sdadc_interrupt_flag interrupt)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Sdadc *const sdadc_module = module_inst->hw;
	/* Enable interrupt */
	sdadc_module->INTENCLR.reg = interrupt;
}

/** @} */
#endif /* SDADC_CALLBACK_MODE == true */

#ifdef __cplusplus
}
#endif

/** @} */

/**
 * \page asfdoc_sam0_sdadc_extra Extra Information for SDADC Driver
 *
 * \section asfdoc_sam0_sdadc_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *  <tr>
 *		<td>SDADC</td>
 *		<td>Sigma-Delta Analog-to-Digital Converter</td>
 *	</tr>
 *  <tr>
 *		<td>OSR</td>
 *		<td>Over Sampling Ratio</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_sdadc_extra_dependencies Dependencies
 * This driver has no dependencies.
 *
 *
 * \section asfdoc_sam0_sdadc_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_sdadc_extra_history Module History
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
 * \page asfdoc_sam0_sdadc_exqsg Examples for SDADC Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_sdadc_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_sdadc_basic_use_case
 * \if SDADC_CALLBACK_MODE
 *  - \subpage asfdoc_sam0_sdadc_basic_use_case_callback
 * \endif
 *
 * \page asfdoc_sam0_sdadc_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42496A</td>
 *		<td>09/2015</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */

#endif /* SDADC_H_INCLUDED */

