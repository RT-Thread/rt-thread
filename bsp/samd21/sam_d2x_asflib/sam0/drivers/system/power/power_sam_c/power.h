/**
 * \file
 *
 * \brief SAM C2x Power functionality
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
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
#ifndef POWER_H_INCLUDED
#define POWER_H_INCLUDED

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_sam0_system_group
 * @{
 */

/**
 * \brief Device sleep modes.
 *
 * List of available sleep modes in the device. A table of clocks available in
 * different sleep modes can be found in \ref asfdoc_sam0_system_module_overview_sleep_mode.
 */
enum system_sleepmode {
	/** IDLE 0 sleep mode */
	SYSTEM_SLEEPMODE_IDLE_0 = PM_SLEEPCFG_SLEEPMODE(0),
	/** IDLE 1 sleep mode */
	SYSTEM_SLEEPMODE_IDLE_1 = PM_SLEEPCFG_SLEEPMODE(0x1),
	/** IDLE 2 sleep mode */
	SYSTEM_SLEEPMODE_IDLE_2 = PM_SLEEPCFG_SLEEPMODE(0x2),
	/** Standby sleep mode */
	SYSTEM_SLEEPMODE_STANDBY = PM_SLEEPCFG_SLEEPMODE(0x4),
};

/**
 * \brief Voltage reference value for ADC/DAC.
 *
 * Voltage references selection for ADC/DAC.
 */
enum system_voltage_references_sel {
	/** 1.024V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_1V024  = SUPC_VREF_SEL_1V024_Val,
	/** 2.048V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_2V048  = SUPC_VREF_SEL_2V048_Val,
	/** 4.096V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_4V096    = SUPC_VREF_SEL_4V096_Val,
};


/**
 * \brief Voltage reference.
 *
 * List of available voltage references (VREF) that may be used within the
 * device.
 */
enum system_voltage_reference {
	/** Temperature sensor voltage reference */
	SYSTEM_VOLTAGE_REFERENCE_TEMPSENSE,
	/** Voltage reference output for ADC/DAC */
	SYSTEM_VOLTAGE_REFERENCE_OUTPUT,
};

/**
 * \brief Voltage Regulator System (VREG) Control configuration.
 *
 * Configuration structure for VREG.
 */
struct system_voltage_regulator_config {
	/** Run in standby in standby sleep mode */
	bool run_in_standby;
};

/**
 * \brief Voltage References System (VREF) Control configuration.
 *
 * Configuration structure for VREF.
 */
struct system_voltage_references_config {
	/** Voltage references selection */
	enum system_voltage_references_sel  sel;
	/** On demand control */
	bool on_demand;
	/** Run in standby */
	bool run_in_standby;
};

/**
 * \brief Voltage Regulator switch in Standby mode.
 *
 */
enum system_vreg_switch_mode {
	/** Automatic mode */
	SYSTEM_VREG_SWITCH_AUTO        = PM_STDBYCFG_VREGSMOD_AUTO_Val,
	/** Performance oriented */
	SYSTEM_VREG_SWITCH_PERFORMANCE = PM_STDBYCFG_VREGSMOD_PERFORMANCE_Val,
	/** Low Power consumption oriented */
	SYSTEM_VREG_SWITCH_LP          = PM_STDBYCFG_VREGSMOD_LP_Val,
};

/**
 * \brief Standby configuration.
 *
 * Configuration structure for standby mode.
 */
struct system_standby_config {
	/** Regulator switch mode in standby */
	enum system_vreg_switch_mode vreg_switch_mode;
	/** Back bias for HMCRAMCHS (false: no, true: standby) */
	bool hmcramchs_back_bias;
};

/**
 * \name Voltage Regulator
 * @{
 */

/**
 * \brief Retrieve the default configuration for voltage regulator.
 *
 * Fills a configuration structure with the default configuration:
 *   - The voltage regulator is in low power mode in Standby sleep mode
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_voltage_regulator_get_config_defaults(
		struct system_voltage_regulator_config *const config)
{
	Assert(config);
	config->run_in_standby       = false;
}

/**
 * \brief Configure voltage regulator.
 *
 * Configures voltage regulator with the given configuration.
 *
 * \param[in] config  Voltage regulator configuration structure containing
 *                    the new config
 */
static inline void system_voltage_regulator_set_config(
		struct system_voltage_regulator_config *const config)
{
	SUPC->VREG.bit.RUNSTDBY = config->run_in_standby;
}

/**
* \brief Enable the selected voltage regulator.
 *
 * Enables the selected voltage regulator source.
 */
static inline void system_voltage_regulator_enable(void)
{
	SUPC->VREG.reg |= SUPC_VREG_ENABLE;
}

/**
 * \brief Disable the selected voltage regulator.
 *
 * Disables the selected voltage regulator.
 */
static inline void system_voltage_regulator_disable(void)
{
	SUPC->VREG.reg &= ~SUPC_VREG_ENABLE;
}

/**
 * @}
 */

/**
 * \name Voltage References
 * @{
 */

/**
 * \brief Retrieve the default configuration for voltage reference.
 *
 * Fill a configuration structure with the default configuration:
 *   - 1.024V voltage reference typical value
 *   - On demand control:disabled
 *   - The voltage reference and the temperature sensor are halted during standby sleep mode
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_voltage_reference_get_config_defaults(
		struct system_voltage_references_config *const config)
{
	Assert(config);
	config->sel            = SYSTEM_VOLTAGE_REFERENCE_1V024;
	config->on_demand      = false;
	config->run_in_standby = false;
}

/**
 * \brief Configure voltage reference.
 *
 * Configures voltage reference with the given configuration.
 *
 * \param[in] config  Voltage reference configuration structure containing
 *                    the new config
 */
static inline void system_voltage_reference_set_config(
		struct system_voltage_references_config *const config)
{
	Assert(config);
	SUPC->VREF.bit.SEL      = config->sel;
	SUPC->VREF.bit.ONDEMAND = config->on_demand;
	SUPC->VREF.bit.RUNSTDBY = config->run_in_standby;
}

/**
 * \brief Enable the selected voltage reference.
 *
 * Enables the selected voltage reference source, making the voltage reference
 * available on a pin as well as an input source to the analog peripherals.
 *
 * \param[in] vref  Voltage reference to enable
 */
static inline void system_voltage_reference_enable(
		const enum system_voltage_reference vref)
{
	switch (vref) {
		case SYSTEM_VOLTAGE_REFERENCE_TEMPSENSE:
			SUPC->VREF.reg |= SUPC_VREF_TSEN;
			break;
		case SYSTEM_VOLTAGE_REFERENCE_OUTPUT:
			SUPC->VREF.reg |= SUPC_VREF_VREFOE;
			break;
		default:
			Assert(false);
			return;
	}
}

/**
 * \brief Disable the selected voltage reference.
 *
 * Disables the selected voltage reference source.
 *
 * \param[in] vref  Voltage reference to disable
 */
static inline void system_voltage_reference_disable(
		const enum system_voltage_reference vref)
{
	switch (vref) {
		case SYSTEM_VOLTAGE_REFERENCE_TEMPSENSE:
			SUPC->VREF.reg &= ~SUPC_VREF_TSEN;
			break;
		case SYSTEM_VOLTAGE_REFERENCE_OUTPUT:
			SUPC->VREF.reg &= ~SUPC_VREF_VREFOE;
			break;
		default:
			Assert(false);
			return;
	}
}

/**
 * @}
 */

/**
 * \name Device Sleep Control
 * @{
 */

/**
 * \brief Set the sleep mode of the device.
 *
 * Sets the sleep mode of the device; the configured sleep mode will be entered
 * upon the next call of the \ref system_sleep() function.
 *
 * For an overview of which systems are disabled in sleep for the different
 * sleep modes, see \ref asfdoc_sam0_system_module_overview_sleep_mode.
 *
 * \param[in] sleep_mode  Sleep mode to configure for the next sleep operation
 */
static inline void system_set_sleepmode(
	const enum system_sleepmode sleep_mode)
{
	PM->SLEEPCFG.reg = sleep_mode;
}


/**
 * \brief Put the system to sleep waiting for interrupt.
 *
 * Executes a device DSB (Data Synchronization Barrier) instruction to ensure
 * all ongoing memory accesses have completed, then a WFI (Wait For Interrupt)
 * instruction to place the device into the sleep mode specified by
 * \ref system_set_sleepmode until woken by an interrupt.
 */
static inline void system_sleep(void)
{
	__DSB();
	__WFI();
}

/**
 * @}
 */

/**
 * \name Standby Configuration
 * @{
 */

/**
 * \brief Retrieve the default configuration for standby.
 *
 * Fills a configuration structure with the default configuration for standby:
 *   - Automatic VREG switching is used
 *   - Retention back biasing mode for HMCRAMCHS
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_standby_get_config_defaults(
		struct system_standby_config *const config)
{
	Assert(config);

	config->vreg_switch_mode    = SYSTEM_VREG_SWITCH_AUTO;
	config->hmcramchs_back_bias = false;
}

/**
 * \brief Configure standby mode.
 *
 * Configures standby with the given configuration.
 *
 * \param[in] config  Standby configuration structure containing
 *                    the new config
 */
static inline void system_standby_set_config(
		struct system_standby_config *const config)
{
	Assert(config);

	PM->STDBYCFG.reg = PM_STDBYCFG_VREGSMOD(config->vreg_switch_mode) |
					 PM_STDBYCFG_BBIASHS(config->hmcramchs_back_bias);
}

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* POWER_H_INCLUDED */
