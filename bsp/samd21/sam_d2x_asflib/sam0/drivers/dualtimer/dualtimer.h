/**
 * \file
 *
 * \brief SAM DUALTIMER Driver for SAMB11
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
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef DUALTIMER_H_INCLUDED
#define DUALTIMER_H_INCLUDED

/**
 * \defgroup asfdoc_samb_dualtimer_group SAM DUALTIMER
 *
 * This driver for Atmel&reg; | SMART SAM devices provides an interface for the
 * configuration and management of the device's DUALTIMER functionality.
 *
 * The following peripherals are used by this module:
 *  - DUALTIMER
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM B11
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_samb_dualtimer_prerequisites
 *  - \ref asfdoc_samb_dualtimer_module_overview
 *  - \ref asfdoc_samb_dualtimer_special_considerations
 *  - \ref asfdoc_samb_dualtimer_extra_info
 *  - \ref asfdoc_samb_dualtimer_examples
 *  - \ref asfdoc_samb_dualtimer_api_overview
 *
 *
 * \section asfdoc_samb_dualtimer_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_samb_dualtimer_module_overview Module Overview
 *  The dual-input timers module provides a set of timing and counting related functionality,
 * and each timer could setup respective. The module can be configured to use an 16-,
 * or 32-bit down-counter that can generate interrupts when they reach 0.
 *
 * \subsection asfdoc_samb_dual_timer_module_overview_counter_mode Counter Mode
 * For each timer, the following modes of operation are available:
 * - One-shot timer mode
 *
 *   The counter generates an interrupt once. When the counter reaches 0,
 *   it halts until you reprogram it. You can do this using one of the following:
 *
 *   1. Clearing the one-shot count bit in the control register, in which case the
 *     count proceeds according to the selection of Free-running or Periodic mode.
 *   
 *   2. Writing a new value to the Load Value register.
 * - Free-running Mode
 *
 *   The counter wraps after reaching its zero value, and continues to count down from
 *   the maximum value. This is the default mode.
 * - Periodic Mode
 *
 *   The counter generates an interrupt at a constant interval, reloading the original
 *   value after wrapping past zero.
 *
 * \subsection asfdoc_samb_dual_timer_module_overview_counter_size Counter Size
 * Each timer module can be configured in one of two different counter
 * sizes; 16-, and 32-bit. The size of the counter determines the maximum
 * value it can count to before an overflow occurs and the count is reset back
 * to zero. \ref asfdoc_sam0_count_size_vs_top "The table below" shows the
 * maximum values for each of the possible counter sizes.
 *
 * \anchor asfdoc_sam0_count_size_vs_top
 * <table>
 *  <caption>Timer Counter Sizes and Their Maximum Count Values</caption>
 *  <tr>
 *    <th>Counter size</th>
 *    <th>Max. (hexadecimal)</th>
 *    <th>Max. (decimal)</th>
 *  </tr>
 *  <tr>
 *    <td>16-bit</td>
 *    <td>0xFFFF</td>
 *    <td>65,535</td>
 *  </tr>
 *  <tr>
 *    <td>32-bit</td>
 *    <td>0xFFFFFFFF</td>
 *    <td>4,294,967,295</td>
 *  </tr>
 * </table>
 *
 * \subsection asfdoc_samb_dual_timer_module_overview_clock Clock Settings
 *
 * \subsubsection asfdoc_sam0_dual_timer_module_overview_clock_selection Clock Selection
 * The timers contain the PCLK and TIMCLK clock inputs. PCLK is the main APB system
 * clock, and is used by the register interface. TIMCLK is the input to the prescale
 * units and the decrementing counters.
 *
 * This provision of two clock inputs enables the counters to continue to run while 
 * the APB system is in a sleep state when PCLK is disabled. External system control
 * logic must handle the changeover periods when PCLK is disabled and enabled to ensure
 * that the PCLK and TIMCLK inputs are fed with synchronous signals when any register
 * access is to occur.
 *
 * \subsubsection asfdoc_sam0_dual_timer_module_overview_clock_prescaler Prescaler
 * Each timer module in the SAM B11 has its own individual clock prescaler, which can
 * be used to divide the input clock frequency used in the counter. This prescaler
 * only scales the clock used to provide clock pulses for the counter to count, the clock
 * can be divide to 1, 16, or 256.
 *
 * \section asfdoc_samb_dualtimer_special_considerations Special Considerations
 *
 * There are no special considerations for this module.
 *
 * \section asfdoc_samb_dualtimer_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_samb_dualtimer_extra. This includes:
 *  - \ref asfdoc_samb_dualtimer_extra_acronyms
 *  - \ref asfdoc_samb_dualtimer_extra_dependencies
 *  - \ref asfdoc_samb_dualtimer_extra_errata
 *  - \ref asfdoc_samb_dualtimer_extra_history
 *
 *
 * \section asfdoc_samb_dualtimer_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_samb_dualtimer_exqsg.
 *
 *
 * \section asfdoc_samb_dualtimer_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system_sam_b.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Type definition for a DUALTIMER module callback function. */
typedef void (*dualtimer_callback_t)(void);

/**
 * \brief Specifies the timer1 or timer2.
 *
 * This enum specifies duatimer timer1 or timer2.
 */
enum dualtimer_timer {
	/** Dualtimer timer1 */
	DUALTIMER_TIMER1 = 0,
	/** Dualtimer timer2 */
	DUALTIMER_TIMER2,
};

/**
 * \brief DUALTIMER module clock input.
 *
 * DUALTIMER module clock.
 */
enum dualtimer_clock_input {
	/** source from clock input 0: 26MHz */
	DUALTIMER_CLK_INPUT_0 = 0,
	/** source from clock input 1: 13MHz */
	DUALTIMER_CLK_INPUT_1,
	/** source from clock input 2: 6.5MHz */
	DUALTIMER_CLK_INPUT_2,
	/** source from clock input 3: 3MHz*/
	DUALTIMER_CLK_INPUT_3,
};

/**
 * \brief Specifies if the counter is 16-bit, or 32-bit.
 *
 * This enum specifies counter with one-shot, free running or periodic counter mode.
 */
enum dualtimer_counter_mode {
	/** Counter in one-shot mode */
	DUALTIMER_ONE_SHOT_MODE = 0,
	/** Counter is in free-running mode */
	DUALTIMER_FREE_RUNNING_MODE,
	/** Counter is in periodic mode */
	DUALTIMER_PERIODIC_MODE,
};

/**
 * \brief Dualtimer counter mode enum.
 *
 * This enum specify the maximum value it is possible to count to.
 */
enum dualtimer_counter_size {
	/** 16-bit counter */
	DUALTIMER_COUNTER_SIZE_16BIT = 0,
	/** 32-bit counter */
	DUALTIMER_COUNTER_SIZE_32BIT,
};

/**
 * \brief Dualtimer clock prescaler values.
 *
 * This enum is used to choose the clock prescaler
 * configuration. The prescaler divides the clock frequency of the
 * Dual Timer module to make the counter count slower.
 */
enum dualtimer_clock_prescaler {
	/** Divide clock by 1 */
	DUALTIMER_CLOCK_PRESCALER_DIV1 = 0,
	/** Divide clock by 16 */
	DUALTIMER_CLOCK_PRESCALER_DIV16,
	/** Divide clock by 256 */
	DUALTIMER_CLOCK_PRESCALER_DIV256,
};

/**
 * \brief Dualtimer set counter.
 *
 * This enum is used to choose set the load register or
 * background load register. The difference to set load
 * register is that writes to background register do not
 * cause the counter to immediately restart from the new value.
 */
enum dualtimer_set_register {
	/** Set current counter */
	DUALTIMER_SET_CURRUNT_REG = 0,
	/** Set background counter */
	DUALTIMER_SET_BG_REG,
};

/**
 * \brief Dualtimer private configuration structure.
 *
 * Private configuration struct for Dualtimer instance.
 */
struct dualtimer_private_config {
	/** Enable timer */
	bool timer_enable;
	/** Selects one-shot or wrapping counter mode */
	enum dualtimer_counter_mode counter_mode;
	/** Selects 16-bit or 32- bit counter size */
	enum dualtimer_counter_size counter_size;
	/** Selects the prescaler value */
	enum dualtimer_clock_prescaler clock_prescaler;
	/** Enable the interrupt */
	bool interrup_enable;
	/** Counter load value */
	uint32_t load_value;
};

/**
 * \brief Dualtimer configuration structure.
 *
 * Configuration struct for Dualtimer instance. This structure should be
 * initialized by the \ref dualtimer_get_config_defaults function before being
 * modified by the user application.
 */
struct dualtimer_config {
	/** Timer1 private configuration */
	struct dualtimer_private_config timer1;
	/** Timer2 private configuration */
	struct dualtimer_private_config timer2;
	/** Selects Dualtimer clock frequency */
	enum dualtimer_clock_input clock_source;
};

/**
 * \name Configuration and Initialization
 * @{
 */
void dualtimer_get_config_defaults(struct dualtimer_config *config);
void dualtimer_init(const struct dualtimer_config *config);
/** @} */

/**
 * \name Get and set value
 * @{
 */
uint32_t dualtimer_get_value(enum dualtimer_timer timer);
void dualtimer_set_counter(enum dualtimer_timer timer,
		enum dualtimer_set_register cur_bg, uint32_t value);
/** @} */

/**
 * \name Get and Clear status
 * @{
 */
uint8_t dualtimer_get_status(enum dualtimer_timer timer);
uint8_t dualtimer_get_interrupt_status(enum dualtimer_timer timer);
void dualtimer_clear_interrupt_status(enum dualtimer_timer timer);
/** @} */

/**
 * \name Enable and disable module
 * @{
 */
void dualtimer_enable(enum dualtimer_timer timer);
void dualtimer_disable(enum dualtimer_timer timer);
/** @} */

/**
 * \name Callback
 * @{
 */
void dualtimer_register_callback(enum dualtimer_timer timer, dualtimer_callback_t fun);
void dualtimer_unregister_callback(enum dualtimer_timer timer);
/** @} */

/** @}*/

#ifdef __cplusplus
}
#endif

/**
 * \page asfdoc_samb_dualtimer_extra Extra Information for DUALTIMER Driver
 *
 * \section asfdoc_samb_dualtimer_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>DUALTIMER</td>
 *		<td>Dualtimer</td>
 *	</tr>
 * </table>
 *
 * \section asfdoc_samb_dualtimer_extra_dependencies Dependencies
 * There are no dependencies related to this driver.
 *
 *
 * \section asfdoc_samb_dualtimer_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_samb_dualtimer_extra_history Module History
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
 * \page asfdoc_samb_dualtimer_exqsg Examples for DUALTIMER Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_samb_dualtimer_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_samb_dualtimer_basic_use_case
 *
 * \page asfdoc_samb_dualtimer_document_revision_history Document Revision History
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