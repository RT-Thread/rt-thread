/**
 * \file
 *
 * \brief SAM System related functionality
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
#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

/**
 * \defgroup asfdoc_samb_system_group SAM System (SYSTEM) Driver
 *
 * This driver for Atmel&reg; | SMART SAM devices provides an interface for the configuration
 * and management of the device's system relation functionality, necessary for
 * the basic device operation. This is not limited to a single peripheral, but
 * extends across multiple hardware peripherals.
 *
 * The following peripherals are used by this module
 *  - SYSCTRL (System Control)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM B11
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_samb_system_prerequisites
 *  - \ref asfdoc_samb_system_module_overview
 *  - \ref asfdoc_samb_system_special_considerations
 *  - \ref asfdoc_samb_system_extra_info
 *  - \ref asfdoc_samb_system_examples
 *  - \ref asfdoc_samb_system_api_overview
 *
 *
 * \section asfdoc_samb_system_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_samb_system_module_overview Module Overview
 *
 * The System driver provides a collection of interfaces between the user
 * application logic, and the core device functionality (such as clocks, reset
 * cause determination, etc.) that is required for all applications. It contains
 * a number of sub-modules that control one specific aspect of the device:
 *
 *
 * \section asfdoc_samb_system_special_considerations Special Considerations
 *
 * Most of the functions in this driver have device specific restrictions and
 * caveats; refer to your device datasheet.
 *
 *
 * \section asfdoc_samb_system_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_samb_system_extra. This includes:
 *  - \ref asfdoc_samb_system_extra_acronyms
 *  - \ref asfdoc_samb_system_extra_dependencies
 *  - \ref asfdoc_samb_system_extra_errata
 *  - \ref asfdoc_samb_system_extra_history
 *
 *
 * \section asfdoc_samb_system_examples Examples
 *
 * For SYSTEM module related examples, refer to the sub-modules listed in
 * the \ref asfdoc_samb_system_module_overview "system module overview".
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_samb_drivers_power_exqsg.
 *
 *
 * \section asfdoc_samb_system_api_overview API Overview
 * @{
 */

#include <compiler.h>

#ifdef __cplusplus
extern "C" {
#endif


/* ISR RAM table address, definition from rom code, */
#define ISR_RAM_MAP_START_ADDRESS	(0x10000000)
/* ISR initialization status located in offset 0, definition from rom code*/
#define ISR_RAM_MAP_INITIALIZED (0x20101985)

/**
 * \brief ISR RAM table index
 *
 * Enum for the index of the ISR in RAm.
 *
 */
enum ram_isr_table_index {
	RAM_ISR_TABLE_RESET_INDEX              = 1,
	RAM_ISR_TABLE_NMI_INDEX                = 2,
	RAM_ISR_TABLE_HARDFAULT_INDEX          = 3,
	RAM_ISR_TABLE_SVC_INDEX                = 11,
	RAM_ISR_TABLE_PENDSV_INDEX             = 14,
	RAM_ISR_TABLE_SYSTICK_INDEX            = 15,
	RAM_ISR_TABLE_UARTRX0_INDEX            = 16,
	RAM_ISR_TABLE_UARTTX0_INDEX            = 17,
	RAM_ISR_TABLE_UARTRX1_INDEX            = 18,
	RAM_ISR_TABLE_UARTTX1_INDEX            = 19,
	RAM_ISR_TABLE_SPIRX0_INDEX             = 20,
	RAM_ISR_TABLE_SPITX0_INDEX             = 21,
	RAM_ISR_TABLE_SPIRX1_INDEX             = 22,
	RAM_ISR_TABLE_SPITX1_INDEX             = 23,
	RAM_ISR_TABLE_I2CRX0_INDEX             = 24,
	RAM_ISR_TABLE_I2CTX0_INDEX             = 25,
	RAM_ISR_TABLE_I2CRX1_INDEX             = 26,
	RAM_ISR_TABLE_I2CTX1_INDEX             = 27,
	RAM_ISR_TABLE_WDT0_INDEX               = 28,
	RAM_ISR_TABLE_WDT1_INDEX               = 29,
	RAM_ISR_TABLE_DUALTIMER_INDEX          = 30,
	RAM_ISR_TABLE_BLE_PERIPH_REGS_INDEX    = 31,
	RAM_ISR_TABLE_SECURITY_INDEX           = 32,
	RAM_ISR_TABLE_EFUSE_OUT_OF_RESET_INDEX = 33,
	RAM_ISR_TABLE_SPI_FLASH_INDEX          = 34,
	RAM_ISR_TABLE_LP_CLK_CAL_DONE_INDEX    = 35,	
	RAM_ISR_TABLE_BROWNOUT_DETECTED_INDEX  = 36,	
	RAM_ISR_TABLE_BLE_CORE_RESET_INDEX     = 37,
	RAM_ISR_TABLE_BLE_LP_CORE_RESET_INDEX  = 38,
	RAM_ISR_TABLE_PORT0_COMB_INDEX         = 39,
	RAM_ISR_TABLE_PORT1_COMB_INDEX         = 40,
	RAM_ISR_TABLE_PORT2_COMB_INDEX         = 41,
	RAM_ISR_TABLE_TIMER0_INDEX             = 42,
	RAM_ISR_TABLE_AON_SLEEP_TIMER_INDEX    = 43,
	RAM_ISR_TABLE_BLE_OSC_EN_INDEX         = 44,
	RAM_ISR_TABLE_BLE_WAKEUP_LP_INDEX      = 45,
	RAM_ISR_TABLE_RXTX_SEQ_SLEEP_INDEX     = 46,
	RAM_ISR_TABLE_BLE_CORE_INDEX           = 47,
};

/**
 * \brief SYSTEM peripheral enum
 *
 * Enum for the possible peripheral for the system.
 *
 */
enum system_peripheral {
	/** SPI Flash */
	PERIPHERAL_SPI_FLASH,
	/** SPI0 Core */
	PERIPHERAL_SPI0_CORE,
	/** SPI1 Core */
	PERIPHERAL_SPI1_CORE,
	/** I2C0 Core */
	PERIPHERAL_I2C0_CORE,
	/** ARM Dual Timer */
	PERIPHERAL_DUALT_TIMER,
	/** GPIO Controller */
	PERIPHERAL_GPIO_CLK,
	/** ARM Timer */
	PERIPHERAL_TIMER,
	/** WDT0 */
	PERIPHERAL_WDT0,
	/** WDT1 */
	PERIPHERAL_WDT1,
	/** UART0 Core */
	PERIPHERAL_UART0_CORE,
	/** UART0 Interface */
	PERIPHERAL_UART0_IF,
	/** UART1 Core */
	PERIPHERAL_UART1_CORE,
	/** UART1 Interface */
	PERIPHERAL_UART1_IF,
	/** NVIC */
	PERIPHERAL_NVIC,
	/** IDRAM1 Glue Logic */
	PERIPHERAL_IDRAM1,
	/** IDRAM2 Glue Logic */
	PERIPHERAL_IDRAM2,
	/** ROM */
	PERIPHERAL_ROM,
	/** Low Power Clock Calibration Interface */
	PERIPHERAL_LOW_POWER_IF,
	/** AON Wrapper */
	PERIPHERAL_AON_WRAPPER,
	/** ARM PCLK */
	PERIPHERAL_ARM_PCLK,
	/** ARM Gated PCLK */
	PERIPHERAL_ARM_GATED_PCLK,
	/** ARM BLE 8K Retention Memory */
	PERIPHERAL_ARM_BLE,
	/** Quad Decoder 0 */
	PERIPHERAL_QDEC0,
	/** Quad Decoder 1 */
	PERIPHERAL_QDEC1,
	/** Quad Decoder 2 */
	PERIPHERAL_QDEC2,
	/** I2C1 Core */
	PERIPHERAL_I2C1_CORE,
	/** Low Power Clock Calibration Core */
	PERIPHERAL_LOW_POWER_CORE,

	/* LPMCU_MISC_REGS_LPMCU_CLOCK_ENABLES_1 */
	/** EFUSE1 */
	PERIPHERAL_EFUSE1,
	/** EFUSE2 */
	PERIPHERAL_EFUSE2,
	/** EFUSE3 */
	PERIPHERAL_EFUSE3,
	/** EFUSE4 */
	PERIPHERAL_EFUSE4,
	/** EFUSE5 */
	PERIPHERAL_EFUSE5,
	/** EFUSE6 */
	PERIPHERAL_EFUSE6,
	/** PWM0 */
	PERIPHERAL_PWM0,
	/** PWM1 */
	PERIPHERAL_PWM1,
	/** PWM2 */
	PERIPHERAL_PWM2,
	/** PWM3 */
	PERIPHERAL_PWM3,
	/** PMU Sensor ADC */
	PERIPHERAL_ADC,
	/** SPI0 SCK Phase Internal */
	PERIPHERAL_SPI0_SCK_PHASE,
	/** SPI1 SCK Phase Internal */
	PERIPHERAL_SPI1_SCK_PHASE,
	/** GPIO Controller */
	PERIPHERAL_GPIO_GCLK,
	/** ARM Timer 0 Gated APB */
	PERIPHERAL_TIMER0_GATE,
	/** SHA Core */
	PERIPHERAL_SHA_CORE,
	/** SHA AHB */
	PERIPHERAL_SHA_AHB,
	/** AES Core */
	PERIPHERAL_AES_CORE,
	/** AES AHB */
	PERIPHERAL_AES_AHB,
	/** IDRAM1_0 Memory */
	PERIPHERAL_IDRAM1_0,
	/** IDRAM1_1 Memory */
	PERIPHERAL_IDRAM1_1,
	/** IDRAM1_2 Memory */
	PERIPHERAL_IDRAM1_2,
	/** IDRAM2_0 Memory */
	PERIPHERAL_IDRAM2_0,
	/** IDRAM2_1 Memory */
	PERIPHERAL_IDRAM2_1,

	/** BLE RXTX Sequencer */
	PERIPHERAL_BLE_RXTX,
	/** BLE HAB */
	PERIPHERAL_BLE_AHB,
	/** BLE Periph Regs */
	PERIPHERAL_BLE_PERIPH_REGS,

	/** LPMCU CPU */
	PERIPHERAL_LPMCU_CPU,
	/** SPI Flash Interface */
	PERIPHERAL_SPI_FLASH_IF,
	/** SPI0 Interface */
	PERIPHERAL_SPI0_IF,
	/** SPI1 Interface */
	PERIPHERAL_SPI1_IF,
	/** I2C0 Interface */
	PERIPHERAL_I2C0_IF,
	/** MBIST Logic */
	PERIPHERAL_MBIST,
	/** Low Power Clock Calibration APB */
	PERIPHERAL_LOW_POWER_APB,
	/** LPMCU Debug */
	PERIPHERAL_LPMCU_DEBUG,
	/** Free Running ARM Clock */
	PERIPHERAL_ARM_FREE_CLK,
	/** ARM APB */
	PERIPHERAL_ARM_APB,
	/** I2C1 Interface */
	PERIPHERAL_I2C1_IF,
	/** SPI0 SCK Clock */
	PERIPHERAL_SPI0_SCK_CLK,
	/** SPI1 SCK Clock */
	PERIPHERAL_SPI1_SCK_CLK,
	/** DMA Controller */
	PERIPHERAL_DMA,

	PERIPHERAL_SLEEP_TIMER,
};

/**
 * \brief SYSTEM peripheral enum
 *
 * Enum for the possible peripheral for the system.
 *
 */
enum system_peripheral_aon {
	/** Sleep timer */
	PERIPHERAL_AON_SLEEP_TIMER,
	/** Power sequencer */
	PERIPHERAL_AON_POWER_SEQUENCER,
	/** PD0 */
	PERIPHERAL_AON_PD,
};

/**
 * \brief SYSTEM CLOCK frequency selection enum
 *
 * Enum for the possible frequency selection for the CLOCK.
 *
 */
enum system_clock_freq {
	/** 26MHz */
	CLOCK_FREQ_26_MHZ,
	/** 13MHz */
	CLOCK_FREQ_13_MHZ,
	/** 6.5MHz */
	CLOCK_FREQ_6_5_MHZ,
	/** 3.25MHz */
	CLOCK_FREQ_3_25_MHZ,
};

/**
 * \brief SYSTEM CLOCK resource selection enum
 *
 * Enum for the possible resource selection for the CLOCK.
 *
 */
enum system_clock_resource {
	/** Use 26MHz Crystal Oscillator XO as ARM clock */
	CLOCK_RESOURCE_XO_26_MHZ,
	/** Use either LP 2MHz clock */
	CLOCK_RESOURCE_LP_2_MHZ,
	/** 26MHz integrated RC Oscillator */
	CLOCK_RESOURCE_RC_26_MHZ,
};

/**
 * \brief SYSTEM CLOCK AON resource selection enum
 *
 * Enum for the possible AON resource selection for the CLOCK.
 *
 */
enum system_clock_aon_resource {
	/** OSC 2MHz */
	CLOCK_AON_RESOURCE_2_MHZ,
	/** OSC 2MHz/64 = 31.25KHz */
	CLOCK_AON_RESOURCE_31_25_KHZ,
	/** RTC XO 32.768KHz */
	CLOCK_AON_RESOURCE_32_768_KHZ,
	/** Use default clock */
	CLOCK_AON_DEFAULT,
};

/**
 * \brief Multiplier value for the number of calibration clocks enum
 *
 * Enum for the possible multiplier value for the number of calibration clocks
 *
 */
enum system_calibration_clk_num {
	/** 1 clock */
	CALIBRATION_CLK_NUM_1,
	/** 2 clocks */
	CALIBRATION_CLK_NUM_2,
	/** 4 clocks */
	CALIBRATION_CLK_NUM_4,
	/** 8 clocks */
	CALIBRATION_CLK_NUM_8,
	/** 16 clocks */
	CALIBRATION_CLK_NUM_16,
	/** 32 clocks */
	CALIBRATION_CLK_NUM_32,
	/** 64 clocks */
	CALIBRATION_CLK_NUM_64,
	/** 128 clocks */
	CALIBRATION_CLK_NUM_128,
	/** 256 clocks */
	CALIBRATION_CLK_NUM_256,
	/** 512 clocks */
	CALIBRATION_CLK_NUM_512,
	/** 1024 clocks */
	CALIBRATION_CLK_NUM_1024,
	/** 2048 clocks */
	CALIBRATION_CLK_NUM_2048,
	/** 4096 clocks */
	CALIBRATION_CLK_NUM_4096,
	/** 8192 clocks */
	CALIBRATION_CLK_NUM_8192,
	/** 16384 clocks */
	CALIBRATION_CLK_NUM_16384,
	/** 32768 clocks */
	CALIBRATION_CLK_NUM_32768,
};

/**
 * \brief Interrupt control enum
 *
 * Enum for the possible interrupt control
 *
 */
enum system_calibration_interrput_control {
	/** IRQ when OSC calibration done */
	CALIBRATION_INTERRUPT_OSC_DONE,
	/** IRQ when RTC calibration done */
	CALIBRATION_INTERRUPT_RTC_DONE,
	/** IRQ when OSC or RTC calibration done */
	CALIBRATION_INTERRUPT_OSC_OR_RTC_DONE,
	/** IRQ when OSC and RTC calibration done */
	CALIBRATION_INTERRUPT_OSC_AND_RTC_DONE,
};

enum system_calibration_status {
	/** No calibration in progress */
	CALBRATION_NO_IN_PROGRESS,
	/** Calibration in progress */
	CALBRATION_IN_PROGRESS,
	/** Calibration done */
	CALBRATION_DONE,
};

struct system_calibration_config {
	enum system_calibration_clk_num clk_num;
	enum system_calibration_interrput_control interrupt_control;
	uint16_t osc_fractional_part;
	uint16_t osc_integer_part;
	uint16_t rtc_fractional_part;
	uint16_t rtc_integer_part;
};

/**
 * \name System clock config, enable and disable functions
 * @{
 */
enum status_code system_clock_config( \
				enum system_clock_resource resoure, \
				enum system_clock_freq freq);
uint32_t system_clock_get_value(void);
enum status_code system_clock_peripheral_enable(enum system_peripheral peripheral);
enum status_code system_clock_peripheral_disable(enum system_peripheral peripheral);
enum status_code system_clock_peripheral_freq_config( \
				enum system_peripheral peripheral, \
				enum system_clock_freq freq);
//void system_init(void);
/** @} */

/**
 * \name System and peripheral reset
 * @{
 */
void system_global_reset(void);
enum status_code system_peripheral_reset(enum system_peripheral peripheral);
/** @} */

/**
 * \name System ISR register and unregister
 * @{
 */
void system_register_isr(enum ram_isr_table_index isr_index,
		uint32_t isr_address);
void system_unregister_isr(enum ram_isr_table_index isr_index);
/** @} */

/**
 * \name System clock OSC(32KHz) and RTC(32.768KHz) calibration
 * @{
 */
void system_calibration_get_config_defaults(struct system_calibration_config *config);
void system_calibration_set_config(struct system_calibration_config *config);
enum system_calibration_status system_calibration_get_interrupt_status( \
				struct system_calibration_config *config);

void system_osc_calibration_enable(void);
void system_osc_calibration_disable(void);
enum system_calibration_status system_osc_calibration_get_status(void);
void system_osc_calibration_clear_status(void);
void system_osc_calibration_result(struct system_calibration_config *config);

void system_rtc_calibration_enable(void);
void system_rtc_calibration_disable(void);
enum system_calibration_status system_rtc_calibration_get_status(void);
void system_rtc_calibration_clear_status(void);
void system_rtc_calibration_result(struct system_calibration_config *config);
/** @} */

/**
 * \name System clock aon config
 * @{
 */
enum status_code system_clock_aon_config( \
				enum system_peripheral_aon peripheral_aon, \
				enum system_clock_aon_resource aon_resource);
enum status_code system_clock_peripheral_aon_enable(enum system_peripheral_aon peripheral_aon);
enum status_code system_clock_peripheral_aon_disable(enum system_peripheral_aon peripheral_aon);
/** @} */

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

/**

* \page asfdoc_samb_drivers_power_exqsg Examples for Power Driver
 *
 * This is a list of the available Quick Start Guides (QSGs) and example
 * applications. QSGs are simple examples with step-by-step instructions to
 * configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 * \page asfdoc_samb_system_extra Extra Information for SYSTEM Driver
 *
 * \section asfdoc_samb_system_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *  <tr>
 *      <th>Acronym</th>
 *      <th>Definition</th>
 *  </tr>
 *  <tr>
 *      <td>SYSCTRL</td>
 *      <td>System control interface</td>
 *  </tr>
 * </table>
 *
 *
 * \section asfdoc_samb_system_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_samb_system_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_samb_system_extra_history Module History
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
 *
 * \page asfdoc_samb_system_document_revision_history Document Revision History
 *
 * <table>
 * <tr>
 *      <th>Doc. Rev.</td>
 *      <th>Date</td>
 *      <th>Comments</td>
 *  </tr>
 *  <tr>
 *      <td>A</td>
 *      <td>08/2015</td>
 *      <td>Initial document release</td>
 *  </tr>
 * \endif
 * </table>
 */

#endif /* SYSTEM_H_INCLUDED */

