/**
 * \file
 *
 * \brief SAM L21/L22/R30 Power functionality
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
#ifndef POWER_H_INCLUDED
#define POWER_H_INCLUDED

#include <compiler.h>
#include <clock.h>

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
	/** IDLE sleep mode */
	SYSTEM_SLEEPMODE_IDLE       = PM_SLEEPCFG_SLEEPMODE(0x2),
	/** STANDBY sleep mode */
	SYSTEM_SLEEPMODE_STANDBY    = PM_SLEEPCFG_SLEEPMODE_STANDBY,
	/** BACKUP sleep mode */
	SYSTEM_SLEEPMODE_BACKUP     = PM_SLEEPCFG_SLEEPMODE_BACKUP,
	/** OFF sleep mode */
	SYSTEM_SLEEPMODE_OFF        = PM_SLEEPCFG_SLEEPMODE_OFF,
};

/**
 * \brief Performance level.
 *
 * List of performance levels. Performance level technique consists of
 * adjusting the regulator output voltage to reduce power consumption.
 */
enum system_performance_level {
	/** Performance level 0 */
	SYSTEM_PERFORMANCE_LEVEL_0  = PM_PLCFG_PLSEL_PL0,
	/** Performance level 2 */
	SYSTEM_PERFORMANCE_LEVEL_2  = PM_PLCFG_PLSEL_PL2,
};

/**
 * \brief RAM Back-biasing mode.
 *
 * List of RAM back bias modes. By default, in standby sleep mode,
 * RAM is in low power mode (back biased) if its power domain is in
 * retention state. This behavior can be changed by configuring the Back Bias
 * bit groups in STDBYCFG(STDBYCFG.BBIASxx).
 */
enum system_ram_back_bias_mode {
	/** Retention Back biasing mode */
	SYSTEM_RAM_BACK_BIAS_RETENTION = 0,
	/** Standby Back Biasing mode */
	SYSTEM_RAM_BACK_BIAS_STANDBY,
	/** Standby OFF mode */
	SYSTEM_RAM_BACK_BIAS_STANDBY_OFF,
	/** Always OFF mode */
	SYSTEM_RAM_BACK_BIAS_OFF,
};

#if SAML21 || SAMR30
/**
 * \brief Linked power domain.
 *
 * List of linked power domains. Power domains can be linked to each other.
 * It allows a power domain (PDn) to be kept in active state if the inferior
 * power domain (PDn-1) is in active state too.
 */
enum system_linked_power_domain {
	/** Power domains PD0/PD1/PD2 are not linked */
	SYSTEM_LINKED_POWER_DOMAIN_DEFAULT   = PM_STDBYCFG_LINKPD_DEFAULT_Val,
	/** Power domains PD0 and PD1 are linked */
	SYSTEM_LINKED_POWER_DOMAIN_PD01      = PM_STDBYCFG_LINKPD_PD01_Val,
	/** Power domains PD1 and PD2 are linked */
	SYSTEM_LINKED_POWER_DOMAIN_PD12      = PM_STDBYCFG_LINKPD_PD12_Val,
	/** All Power domains are linked */
	SYSTEM_LINKED_POWER_DOMAIN_PD012     = PM_STDBYCFG_LINKPD_PD012_Val,
};

#if (SAML21XXXB) || (SAMR30)
/**
 * \brief VREG switching mode.
 *
 * List of VREG switching modes.
 */
enum system_vreg_switch_mode {
	/** Automatic mode. */
	SYSTEM_SYSTEM_VREG_SWITCH_AUTO = 0,
	/** Performance oriented. */
	SYSTEM_SYSTEM_VREG_SWITCH_PERFORMANCE,
	/** Low Power consumption oriented. */
	SYSTEM_SYSTEM_VREG_SWITCH_LP,
};
#endif

/**
 * \brief Power domain.
 *
 * List of power domains. Power domain gating technique consists of turning
 * on or off power domain voltage to save power while keeping other domains
 * powered up.
 */
enum system_power_domain {
	/** All power domains switching are handled by hardware */
	SYSTEM_POWER_DOMAIN_DEFAULT = PM_STDBYCFG_PDCFG_DEFAULT_Val,
	/** Power domain 0 (PD0) is forced ACTIVE */
	SYSTEM_POWER_DOMAIN_PD0     = PM_STDBYCFG_PDCFG_PD0_Val,
	/** Power domain 0 and 1 (PD0 and PD1) are forced ACTIVE */
	SYSTEM_POWER_DOMAIN_PD01    = PM_STDBYCFG_PDCFG_PD01_Val,
	/** All power domains are forced ACTIVE */
	SYSTEM_POWER_DOMAIN_PD012   = PM_STDBYCFG_PDCFG_PD012_Val,
};
#endif

#if SAML22
/**
 * \brief Voltage Regulator switch in Standby mode.
 *
 */
enum system_vreg_switch_mode {
	/** Automatic mode. */
	SYSTEM_VREG_SWITCH_AUTO        = PM_STDBYCFG_VREGSMOD_AUTO_Val,
	/** Performance oriented. */
	SYSTEM_VREG_SWITCH_PERFORMANCE = PM_STDBYCFG_VREGSMOD_PERFORMANCE_Val,
	/** Low Power consumption oriented. */
	SYSTEM_VREG_SWITCH_LP          = PM_STDBYCFG_VREGSMOD_LP_Val,
};

#endif

/**
 * \brief Voltage regulator.
 *
 * Voltage regulators selection. In active mode, the voltage regulator
 * can be chosen on the fly between a LDO or a Buck converter.
 */
enum system_voltage_regulator_sel {
	/** The voltage regulator in active mode is a LDO voltage regulator */
	SYSTEM_VOLTAGE_REGULATOR_LDO    = SUPC_VREG_SEL_LDO_Val,
	/** The voltage regulator in active mode is a buck converter */
	SYSTEM_VOLTAGE_REGULATOR_BUCK   = SUPC_VREG_SEL_BUCK_Val,
};

/**
 * \brief Low power efficiency.
 *
 * Low power mode efficiency.
 */
enum system_voltage_regulator_low_power_efficiency {
	/** The voltage regulator in Low power mode has the default efficiency and
		support the whole VDD range (1.62V to 3.6V) */
	SYSTEM_VOLTAGE_REGULATOR_LOW_POWER_EFFICIENCY_DEFAULT,
	/** The voltage regulator in Low power mode has the highest efficiency and
		support the limited VDD range (2.5V to 3.6V) */
	SYSTEM_VOLTAGE_REGULATOR_LOW_POWER_EFFICIENCY_HIGHTEST,
};

/**
 * \brief Voltage reference value.
 *
 * Voltage references selection.
 */
enum system_voltage_references_sel {
	/** 1.0V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_1V0    = SUPC_VREF_SEL_1V0_Val,
	/** 1.1V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_1V1    = SUPC_VREF_SEL_1V1_Val,
	/** 1.2V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_1V2    = SUPC_VREF_SEL_1V2_Val,
	/** 1.25V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_1V25   = SUPC_VREF_SEL_1V25_Val,
	/** 2.0V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_2V0    = SUPC_VREF_SEL_2V0_Val,
	/** 2.2V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_2V2    = SUPC_VREF_SEL_2V2_Val,
	/** 2.4V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_2V4    = SUPC_VREF_SEL_2V4_Val,
	/** 2.5V voltage reference typical value */
	SYSTEM_VOLTAGE_REFERENCE_2V5    = SUPC_VREF_SEL_2V5_Val,
};

/**
 * \brief Battery power switch configuration enum.
 *
 * Enum for Battery power switch modes.
 */
enum system_battery_power_switch {
	/** The backup domain is always supplied by main power */
	SYSTEM_BATTERY_POWER_SWITCH_NONE      = SUPC_BBPS_CONF_NONE_Val,
	/** The power switch is handled by the automatic power switch */
	SYSTEM_BATTERY_POWER_SWITCH_AUTOMATIC = SUPC_BBPS_CONF_APWS_Val,
	/** The backup domain is always supplied by battery backup power */
	SYSTEM_BATTERY_POWER_SWITCH_FORCED    = SUPC_BBPS_CONF_FORCED_Val,
	/** The power switch is handled by the BOD33 */
	SYSTEM_BATTERY_POWER_SWITCH_BOD33     = SUPC_BBPS_CONF_BOD33_Val,
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
	/** Voltage reference output */
	SYSTEM_VOLTAGE_REFERENCE_OUTPUT,
};

/**
 * \brief Backup IO enum.
 *
 * List of Backup input and output pins.
 * If enabled (\ref system_backup_pin_output_enable), the pins can be driven
 * by the SUPC.
 */
enum system_backup_pin {
	/** Power Supply OK status pin */
	SYSTEM_BACKUP_PIN_PSOK  = (0x1 << 0),
	/** Backup output pin 0  */
	SYSTEM_BACKUP_PIN_OUT_0 = (0x1 << 1),
	/** Backup output pin 1  */
	SYSTEM_BACKUP_PIN_OUT_1 = (0x1 << 2)
};

/**
 * \brief Standby configuration.
 *
 * Configuration structure for standby mode.
 */
struct system_standby_config {
#if SAML21 || SAMR30
	/** Power domain. */
	enum system_power_domain  power_domain;
	/** Enable dynamic power gating for power domain 0 */
	bool enable_dpgpd0;
	/** Enable dynamic power gating for power domain 1 */
	bool enable_dpgpd1;
#if (SAML21XXXA)
	/** Automatic VREG switching disable. */
	bool disable_avregsd;
#else
	/** VREG switching mode */
	enum system_vreg_switch_mode vregs_mode;
#endif
	/** Linked power domain */
	enum system_linked_power_domain linked_power_domain;
#elif SAML22
	/** Regulator switch mode in standby. */
	enum system_vreg_switch_mode vreg_switch_mode;
#endif
	/** Back bias for HMCRAMCHS. */
	enum system_ram_back_bias_mode hmcramchs_back_bias;
	/** Back bias for HMCRAMCLP */
	enum system_ram_back_bias_mode hmcramclp_back_bias;
};

/**
 * \brief Voltage Regulator System (VREG) Control configuration.
 *
 * Configuration structure for VREG.
 */
struct system_voltage_regulator_config {
	/** Voltage scaling period */
	uint8_t  voltage_scale_period;
	/** Voltage scaling voltage step */
	uint8_t voltage_scale_step;
	/** Run in standby in standby sleep mode */
	bool run_in_standby;
	/** Voltage Regulator Selection */
	enum system_voltage_regulator_sel  regulator_sel;
	/** Low power efficiency */
	enum system_voltage_regulator_low_power_efficiency low_power_efficiency;
#if SAML22 || SAML21XXXB
	/** Run in standby in performance level 0. */
	bool run_in_standby_pl0;
#endif
};

/**
 * \brief Voltage References System (VREF) Control configuration.
 *
 * Configuration structure for VREF.
 */
struct system_voltage_references_config {
	/** Voltage References Selection */
	enum system_voltage_references_sel  sel;
	/** On Demand Control */
	bool on_demand;
	/** Run in standby */
	bool run_in_standby;
#if SAML22
	/** Temperature Sensor Selection. */
	bool temperature_sensor_sel;
#endif
};

/**
 * \brief Battery Backup Power Switch (BBPS) Control configuration.
 *
 * Configuration structure for Battery Backup Power Switch (BBPS).
 */
struct system_battery_backup_power_switch_config {
	/** Enable device wake up when BBPS switches from
		battery backup power to main power */
	bool wake_enabled;
	/** Battery backup power switch configuration */
	enum system_battery_power_switch battery_power_switch;
};

/**
 * \name Voltage Regulator
 * @{
 */

/**
 * \brief Retrieve the default configuration for voltage regulator.
 *
 * Fills a configuration structure with the default configuration:
 *   - Voltage scaling period is 1μs
 *   - Voltage scaling voltage step is 2*min_step
 *   - The voltage regulator is in low power mode in Standby sleep mode
 *   - The voltage regulator in active mode is an LDO voltage regulator
 *   - The voltage regulator in Low power mode has the default efficiency
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_voltage_regulator_get_config_defaults(
		struct system_voltage_regulator_config *const config)
{
	Assert(config);
	config->voltage_scale_period = 0;
	config->voltage_scale_step   = 0;
	config->run_in_standby       = false;
	config->regulator_sel        = SYSTEM_VOLTAGE_REGULATOR_LDO;
	config->low_power_efficiency = SYSTEM_VOLTAGE_REGULATOR_LOW_POWER_EFFICIENCY_DEFAULT;
#if SAML22 || SAML21XXXB
	config->run_in_standby_pl0   = false;
#endif
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
	Assert(config);
	SUPC->VREG.bit.VSPER    = config->voltage_scale_period;
	SUPC->VREG.bit.VSVSTEP  = config->voltage_scale_step;
	SUPC->VREG.bit.RUNSTDBY = config->run_in_standby;
	SUPC->VREG.bit.SEL      = config->regulator_sel;
#if (SAML21XXXB) || (SAMR30)
	SUPC->VREG.bit.LPEFF    = config->low_power_efficiency;
#endif
#if SAML22 || SAML21XXXB
	SUPC->VREG.bit.STDBYPL0 = config->run_in_standby_pl0;
#endif
	while(!(SUPC->STATUS.reg & SUPC_STATUS_VREGRDY)) {
		;
	}
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
 *   - 1.0V voltage reference typical value
 *   - On demand control disabled
 *   - The voltage reference and the temperature sensor are halted during standby sleep mode
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_voltage_reference_get_config_defaults(
		struct system_voltage_references_config *const config)
{
	Assert(config);
	config->sel            = SYSTEM_VOLTAGE_REFERENCE_1V0;
	config->on_demand      = false;
	config->run_in_standby = false;
#if SAML22
	config->temperature_sensor_sel = false;
#endif
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
#if SAML22
	SUPC->VREF.bit.TSSEL    = config->temperature_sensor_sel;
#endif
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
 * \name Battery Backup Power Switch
 * @{
 */

/**
 * \brief Retrieve the default configuration for battery backup power switch control.
 *
 * Fills a configuration structure with the default configuration:
 *   - The main Power Supply OK status is not available on the PSOK pin
 *   - The device is not woken up when switched from battery backup power to main power
 *   - The backup domain is always supplied by main power
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_battery_backup_power_switch_get_config_defaults(
		struct system_battery_backup_power_switch_config *const config)
{
	Assert(config);
	config->wake_enabled         = false;
	config->battery_power_switch = SYSTEM_BATTERY_POWER_SWITCH_NONE;
}

/**
 * \brief Configure battery backup power switch.
 *
 * Configures battery backup power switch with the given configuration.
 *
 * \param[in] config  Battery backup power switch configuration structure containing
 *                    the new config
 */
static inline void system_battery_backup_power_switch_set_config(
		struct system_battery_backup_power_switch_config *const config)
{
	Assert(config);
	uint32_t new_config = SUPC->BBPS.reg & SUPC_BBPS_PSOKEN;

	if(config->wake_enabled) {
		new_config |= SUPC_BBPS_WAKEEN;
	}

	new_config |= SUPC_BBPS_CONF(config->battery_power_switch);

	SUPC->BBPS.reg = new_config;

	if (config->battery_power_switch == SYSTEM_BATTERY_POWER_SWITCH_AUTOMATIC) {
		while (!(SUPC->STATUS.reg & SUPC_STATUS_APWSRDY)) {
			;
		}
	}
}

/**
 * @}
 */

/**
 * \name Output Pins in Backup Mode
 * @{
 */

/**
 *  \brief Enable the backup pin output.
 *
 *  The output is enabled and driven by the SUPC.
 *
 *  \param[in] pin Backup pin index
 */
static inline void system_backup_pin_output_enable(
		enum system_backup_pin pin)
{
	if (pin == SYSTEM_BACKUP_PIN_PSOK) {
		SUPC->BBPS.reg |= SUPC_BBPS_PSOKEN;
	} else {
		SUPC->BKOUT.reg |= SUPC_BKOUT_EN(pin >> 1);
	}
}

/**
 *  \brief Disable the backup pin output.
 *
 *  The output is not enabled.
 *
 *  \param[in] pin Backup pin index
 */
static inline void system_backup_pin_output_disable(
		enum system_backup_pin pin)
{
	if (pin == SYSTEM_BACKUP_PIN_PSOK) {
		SUPC->BBPS.reg &= ~SUPC_BBPS_PSOKEN;
	} else {
		SUPC->BKOUT.reg &= ~SUPC_BKOUT_EN(pin >> 1);
	}
}

/**
 * \brief Check if backup pin output is enabled.
 *
 *  \param[in] pin Backup pin index
 *
 * \return The enabled status.
 * \retval true The output is enabled
 * \retval false The output is not enabled
 */
static inline bool system_backup_pin_output_is_enabled(
		enum system_backup_pin pin)
{
	bool enabled = false;

	if (pin == SYSTEM_BACKUP_PIN_PSOK) {
		if (SUPC->BBPS.reg & SUPC_BBPS_PSOKEN) {
			enabled = true;
		}
	} else {
		if (SUPC->BKOUT.reg & SUPC_BKOUT_EN(pin >> 1)) {
			enabled = true;
		}
	}
	return enabled;
}

/**
 *  \brief Enable the backup pin toggle on RTC event.
 *
 *  Toggle output on RTC event is enabled.
 *
 *  \param[in] pin Backup pin index
 */
static inline void system_backup_pin_output_enable_rtc_toggle(
		enum system_backup_pin pin)
{
	Assert(pin != SYSTEM_BACKUP_PIN_PSOK);

	SUPC->BKOUT.reg |= SUPC_BKOUT_RTCTGL(pin >> 1);
}

/**
 *  \brief Disable the backup pin toggle on RTC event.
 *
 *  Toggle output on RTC event is disabled.
 *
 *  \param[in] pin Backup pin index
 */
static inline void system_backup_pin_output_disable_rtc_toggle(
		enum system_backup_pin pin)
{
	Assert(pin != SYSTEM_BACKUP_PIN_PSOK);

	SUPC->BKOUT.reg &= ~SUPC_BKOUT_RTCTGL(pin >> 1);
}

/**
 *  \brief Set the backup pin.
 *
 *  Set the corresponding output pin.
 *
 *  \param[in] pin Backup pin index
 */
static inline void system_backup_pin_output_set(
		enum system_backup_pin pin)
{
	Assert(pin != SYSTEM_BACKUP_PIN_PSOK);

	SUPC->BKOUT.reg |= SUPC_BKOUT_SET(pin >> 1);
}

/**
 *  \brief Clear the backup pin.
 *
 *  Clear the corresponding output.
 *
 *  \param[in] pin Backup pin index
 */
static inline void system_backup_pin_output_clear(
		enum system_backup_pin pin)
{
	Assert(pin != SYSTEM_BACKUP_PIN_PSOK);

	SUPC->BKOUT.reg |= SUPC_BKOUT_CLR(pin >> 1);
}

/**
 *  \brief Get the backup I/O input values.
 *
 *  Get the backup I/O data input values. If the corresponding pin is enabled,
 *  the I/O input value is given on the pin.
 *
 *  \param[in] pin Backup pin index
 *
 * \return The backup I/O input level value.
 */
static inline bool system_backup_pin_output_get(enum system_backup_pin pin)
{
	Assert(pin != SYSTEM_BACKUP_PIN_PSOK);

	return (SUPC->BKIN.reg & SUPC_BKIN_BKIN(pin >> 1));
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
	while(PM->SLEEPCFG.reg != sleep_mode) ;
}

/**
 * \brief Put the system to sleep waiting for interrupt.
 *
 * Executes a device DSB (Data Synchronization Barrier) instruction to ensure
 * all ongoing memory accesses have completed. Further, a WFI (Wait For Interrupt)
 * instruction is executed to place the device into the sleep mode specified by
 * \ref system_set_sleepmode.
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
 * \name Performance Level Control
 * @{
 */

/**
 * \brief Switch performance level.
 *
 *  The bus frequency must be reduced prior to scaling down the performance level,
 *  in order to not exceed the maximum frequency allowed for the performance level.
 *
 *  When scaling up the performance level (for example from PL0 to PL2), the bus
 *  frequency can be increased first when the performance level transition is
 *  completed. Check the performance level status before increasing the frequency.
 *
 * \param[in] performance_level  Performance level to switch
 *
 * \retval STATUS_ERR_INVALID_ARG  Invalid parameter
 * \retval STATUS_OK               Successfully
 */
static inline enum status_code system_switch_performance_level(
					const enum system_performance_level performance_level)
{

	if (performance_level == (enum system_performance_level)PM->PLCFG.reg) {
		return STATUS_OK;
	}

#if SAML22 || SAML21XXXB
	if (PM->PLCFG.reg & PM_PLCFG_PLDIS) {
		return STATUS_ERR_INVALID_ARG;
	}
#endif

	/* Clear performance level status */
	PM->INTFLAG.reg = PM_INTFLAG_PLRDY;

	/* Switch performance level */
	PM->PLCFG.reg = performance_level;

	/* Waiting performance level ready */
	while (!PM->INTFLAG.reg) {
		;
	}
	return STATUS_OK;
}

#if SAML22 || SAML21XXXB
/**
 * \brief Enable performance level switch.
 *
 * Enable performance level switch.
 */
static inline void system_performance_level_enable(void)
{
	PM->PLCFG.reg &= ~PM_PLCFG_PLDIS;
}

/**
 * \brief Disable performance level switch.
 *
 * Disable performance level switch.
 */
static inline void system_performance_level_disable(void)
{
	PM->PLCFG.reg |= PM_PLCFG_PLDIS;
}
#endif

/**
 * \brief Get performance level.
 *
 * Get performance level.
 *
 * \return Current performance level.
 */
static inline enum system_performance_level system_get_performance_level(void)
{
	return (enum system_performance_level)PM->PLCFG.reg;
}

/**
 * \brief Get performance level status.
 *
 * Get performance level status.
 * \return Performance level status: Written to one when the performance level is ready.
 */
static inline uint8_t system_get_performance_level_status(void)
{
	return PM->INTFLAG.reg;
}

/**
 * \brief Clear performance level status.
 *
 * Clear performance level status.
 */
static inline void system_clear_performance_level_status(void)
{
	PM->INTFLAG.reg = PM_INTFLAG_PLRDY;
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
 *   - Retention back biasing mode for HMCRAMCLP
 *   - Retention back biasing mode for HMCRAMCHS
 *   - Power domains PD0/PD1/PD2 are not linked
 *   - Automatic VREG switching is used
 *   - Dynamic power gating for power domain 1 is disabled
 *   - Dynamic power gating for power domain 0 is disabled
 *   - All power domains switching are handled by hardware
 *
 * \param[out] config  Configuration structure to fill with default values
 */
static inline void system_standby_get_config_defaults(
		struct system_standby_config *const config)
{
	Assert(config);
#if SAML21 || SAMR30
	config->power_domain        = SYSTEM_POWER_DOMAIN_DEFAULT;
	config->enable_dpgpd0       = false;
	config->enable_dpgpd1       = false;
#if (SAML21XXXB) || (SAMR30)
	config->vregs_mode          = SYSTEM_SYSTEM_VREG_SWITCH_AUTO;
#else
	config->disable_avregsd     = false;
#endif
	config->linked_power_domain = SYSTEM_LINKED_POWER_DOMAIN_DEFAULT;
#elif SAML22
	config->vreg_switch_mode    = SYSTEM_VREG_SWITCH_AUTO;
#endif
	config->hmcramchs_back_bias = SYSTEM_RAM_BACK_BIAS_RETENTION;
	config->hmcramclp_back_bias = SYSTEM_RAM_BACK_BIAS_RETENTION;
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
#if SAML21 || SAMR30
	PM->STDBYCFG.reg = PM_STDBYCFG_PDCFG(config->power_domain)
					 | (config->enable_dpgpd0 << PM_STDBYCFG_DPGPD0_Pos)
					 | (config->enable_dpgpd1 << PM_STDBYCFG_DPGPD1_Pos)
#if (SAML21XXXB) || (SAMR30)
					 | PM_STDBYCFG_VREGSMOD(config->vregs_mode)
#else
					 | (config->disable_avregsd << PM_STDBYCFG_AVREGSD_Pos)
#endif
					 | PM_STDBYCFG_LINKPD(config->linked_power_domain)
					 | PM_STDBYCFG_BBIASHS(config->hmcramchs_back_bias)
					 | PM_STDBYCFG_BBIASLP(config->hmcramclp_back_bias);
#elif SAML22
	PM->STDBYCFG.reg = PM_STDBYCFG_VREGSMOD(config->vreg_switch_mode) |
					 PM_STDBYCFG_BBIASHS(config->hmcramchs_back_bias);
#endif
}

/**
 * @}
 */

/**
 * \name I/O Retention
 * @{
 */

/**
 * \brief Enable I/O retention.
 *
 *  Enable I/O retention. After waking up from Backup mode, I/O lines are held
 *  until the bit is written to 0.
 */
static inline void system_io_retension_enable(void)
{
	PM->CTRLA.reg = PM_CTRLA_IORET;
}

/**
 * \brief Disable I/O retention.
 *
 * Disable IO retention. After waking up from Backup mode, I/O lines are not held.
 */
static inline void system_io_retension_disable(void)
{
	PM->CTRLA.reg = PM_CTRLA_MASK & (~PM_CTRLA_IORET);
}

/**
 * @}
 */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* POWER_H_INCLUDED */
