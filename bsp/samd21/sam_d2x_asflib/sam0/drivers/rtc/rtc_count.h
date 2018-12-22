/**
 * \file
 *
 * \brief SAM RTC Driver (Count Mode)
 *
 * Copyright (C) 2012-2016 Atmel Corporation. All rights reserved.
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

#ifndef RTC_COUNT_H_INCLUDED
#define RTC_COUNT_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_rtc_count_group SAM RTC Count (RTC COUNT) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides
 * an interface for the configuration and management of the device's Real Time
 * Clock functionality in Count operating mode, for the configuration and
 * retrieval of the current RTC counter value. The following driver API modes
 * are covered by this manual:
 *
 *  - Polled APIs
 * \if RTC_COUNT_CALLBACK_MODE
 *  - Callback APIs
 * \endif
 *
 * The following peripheral is used by this module:
 *  - RTC (Real Time Clock)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM D20/D21
 *  - Atmel | SMART SAM R21
 *  - Atmel | SMART SAM D09/D10/D11
 *  - Atmel | SMART SAM L21/L22
 *  - Atmel | SMART SAM DA1
 *  - Atmel | SMART SAM C20/C21
 *  - Atmel | SMART SAM HA1
 *  - Atmel | SMART SAM R30
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_rtc_count_prerequisites
 *  - \ref asfdoc_sam0_rtc_count_module_overview
 *  - \ref asfdoc_sam0_rtc_count_special_considerations
 *  - \ref asfdoc_sam0_rtc_count_extra_info
 *  - \ref asfdoc_sam0_rtc_count_examples
 *  - \ref asfdoc_sam0_rtc_count_api_overview
 *
 *
 * \section asfdoc_sam0_rtc_count_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_rtc_count_module_overview Module Overview
 *
 * The RTC module in the SAM devices is a 32-bit counter, with a 10-bit
 * programmable prescaler. Typically, the RTC clock is run continuously,
 * including in the device's low-power sleep modes, to track the current time
 * and date information. The RTC can be used as a source to wake up the system
 * at a scheduled time or periodically using the alarm functions.
 *
 * In this driver, the RTC is operated in Count mode. This allows for an
 * easy integration of an asynchronous counter into a user application, which is
 * capable of operating while the device is in sleep mode.
 *
 * Whilst operating in Count mode, the RTC features:
 *  - 16-bit counter mode
 *   - Selectable counter period
 *   - Up to six configurable compare values
 *  - 32-bit counter mode
 *   - Clear counter value on match
 *   - Up to four configurable compare values
 *
 * \subsection asfdoc_sam0_rtc_count_features Driver Feature Macro Definition
 * <table>
 *  <tr>
 *    <th>Driver Feature Macro</th>
 *    <th>Supported devices</th>
 *  </tr>
 *  <tr>
 *    <td>FEATURE_RTC_PERIODIC_INT</td>
 *    <td>SAM L21/L22/C20/C21/R30</td>
 *  </tr>
 *  <tr>
 *    <td>FEATURE_RTC_PRESCALER_OFF</td>
 *    <td>SAM L21/L22/C20/C21/R30</td>
 *  </tr>
 *  <tr>
 *    <td>FEATURE_RTC_CLOCK_SELECTION</td>
 *    <td>SAM L21/L22/C20/C21/R30</td>
 *  </tr>
 *  <tr>
 *    <td>FEATURE_RTC_GENERAL_PURPOSE_REG</td>
 *    <td>SAM L21/L22/R30</td>
 *  </tr>
 *  <tr>
 *    <td>FEATURE_RTC_CONTINUOUSLY_UPDATED</td>
 *    <td>SAM D20, SAM D21, SAM R21, SAM D10, SAM D11, SAM DA1, SAM HA1</td>
 *  </tr>
 *  <tr>
 *    <td>FEATURE_RTC_TAMPER_DETECTION</td>
 *    <td>SAM L22</td>
 *  </tr>
 * </table>
 * \note The specific features are only available in the driver when the
 * selected device supports those features.
 *
 * \section asfdoc_sam0_rtc_count_module_overview_compares Compare and Overflow
 * The RTC can be used with up to 4/6 compare values (depending on selected
 * operation mode). These compare values will trigger on match with the current
 * RTC counter value, and can be set up to trigger an interrupt, event, or both.
 * The RTC can also be configured to clear the counter value on compare match
 * in 32-bit mode, resetting the count value back to zero.
 *
 * If the RTC is operated without the Clear on Match option enabled, or in
 * 16-bit mode, the RTC counter value will instead be cleared on overflow once
 * the maximum count value has been reached:
 *
 * \f[ COUNT_{MAX} = 2^{32}-1 \f] for 32-bit counter mode, and
 * \f[ COUNT_{MAX} = 2^{16}-1 \f] for 16-bit counter mode.
 *
 * When running in 16-bit mode, the overflow value is selectable with a period
 * value. The counter overflow will then occur when the counter value reaches
 * the specified period value.
 *
 * \subsection asfdoc_sam0_rtc_count_module_overview_periodic Periodic Events
 * The RTC can generate events at periodic intervals, allowing for direct
 * peripheral actions without CPU intervention. The periodic events can be
 * generated on the upper eight bits of the RTC prescaler, and will be generated on
 * the rising edge transition of the specified bit. The resulting periodic
 * frequency can be calculated by the following formula:
 *
 * \f[ f_{PERIODIC}=\frac{f_{ASY}}{2^{n+3}} \f]
 *
 * Where \f$f_{ASY}\f$ refers to the \e asynchronous clock is set up in the RTC
 * module configuration. The \b n parameter is the event source generator index
 * of the RTC module. If the asynchronous clock is operated at the recommended
 * frequency of 1KHz, the formula results in the values shown in
 * \ref asfdoc_sam0_rtc_count_module_rtc_hz "the table below".
 *
 * \anchor asfdoc_sam0_rtc_count_module_rtc_hz
 * <table>
 *   <caption>RTC Event Frequencies for Each Prescaler Bit Using a 1KHz Clock</caption>
 *   <tr>
 *      <th>n</th> <th>Periodic event</th>
 *   </tr>
 *   <tr>
 *      <td>7</td> <td>1Hz</td>
 *   </tr>
 *   <tr>
 *      <td>6</td> <td>2Hz</td>
 *   </tr>
 *   <tr>
 *      <td>5</td> <td>4Hz</td>
 *   </tr>
 *   <tr>
 *      <td>4</td> <td>8Hz</td>
 *   </tr>
 *   <tr>
 *      <td>3</td> <td>16Hz</td>
 *   </tr>
 *   <tr>
 *      <td>2</td> <td>32Hz</td>
 *   </tr>
 *   <tr>
 *      <td>1</td> <td>64Hz</td>
 *   </tr>
 *   <tr>
 *      <td>0</td> <td>128Hz</td>
 *   </tr>
 * </table>
 *
 * \note The connection of events between modules requires the use of the
 *       \ref asfdoc_sam0_events_group "SAM Event System (EVENTS) Driver"
 *       to route output event of one module to the the input event of another.
 *       For more information on event routing, refer to the event driver
 *       documentation.
 *
 * \subsection asfdoc_sam0_rtc_count_module_overview_correction Digital Frequency Correction
 * The RTC module contains Digital Frequency Correction logic to compensate for
 * inaccurate source clock frequencies which would otherwise result in skewed
 * time measurements. The correction scheme requires that at least two bits
 * in the RTC module prescaler are reserved by the correction logic. As a
 * result of this implementation, frequency correction is only available when
 * the RTC is running from a 1Hz reference clock.
 *
 * The correction procedure is implemented by subtracting or adding a single
 * cycle from the RTC prescaler every 1024 RTC GCLK cycles. The adjustment is
 * applied the specified number of time (maximum 127) over 976 of these periods. The
 * corresponding correction in PPM will be given by:
 *
 * \f[ Correction(PPM) = \frac{VALUE}{999424}10^6 \f]
 *
 * The RTC clock will tick faster if provided with a positive correction value,
 * and slower when given a negative correction value.
 *
 *
 * \subsection asfdoc_sam0_rtc_count_module_overview_tamper_detect RTC Tamper Detect
 * see \ref asfdoc_sam0_rtc_tamper_detect
 *
 * \section asfdoc_sam0_rtc_count_special_considerations Special Considerations
 *
 * \subsection asfdoc_sam0_rtc_count_special_considerations_clock Clock Setup
 * \subsubsection asfdoc_sam0_rtc_count_clock_samd_r SAM D20/D21/R21/D10/D11/DA1/HA1 Clock Setup
 * The RTC is typically clocked by a specialized GCLK generator that has a
 * smaller prescaler than the others. By default the RTC clock is on, selected
 * to use the internal 32KHz RC-oscillator with a prescaler of 32, giving a
 * resulting clock frequency of 1KHz to the RTC.  When the internal RTC
 * prescaler is set to 1024, this yields an end-frequency of 1Hz.
 *
 * The implementer also has the option to set other end-frequencies.
 * \ref asfdoc_sam0_rtc_count_rtc_out_freq "The table below" lists the
 * available RTC frequencies for each possible GCLK and RTC input prescaler
 * options.
 *
 * \anchor asfdoc_sam0_rtc_count_rtc_out_freq
 * <table>
 *   <caption>RTC Output Frequencies from Allowable Input Clocks</caption>
 *   <tr>
 *     <th>End-frequency</th>
 *     <th>GCLK prescaler</th>
 *     <th>RTC prescaler</th>
 *   </tr>
 *   <tr>
 *     <td>32KHz</td>
 *     <td>1</td>
 *     <td>1</td>
 *   </tr>
 *   <tr>
 *     <td>1KHz</td>
 *     <td>32</td>
 *     <td>1</td>
 *   </tr>
 *   <tr>
 *     <td>1Hz</td>
 *     <td>32</td>
 *     <td>1024</td>
 *   </tr>
 * </table>
 *
 * The overall RTC module clocking scheme is shown in
 * \ref asfdoc_sam0_rtc_count_rtc_clock_fig "the figure below".
 *
 * \anchor asfdoc_sam0_rtc_count_rtc_clock_fig
 * \dot
 * digraph clocking_scheme {
 *     rankdir=LR;
 *     GCLK [shape="record", label="<f0> GCLK | <f1> RTC_GCLK",
 *         bgcolor="lightgray", style="filled"];
 *     RTCPRE [shape="record" label="<f0> RTC | <f1> RTC PRESCALER"];
 *     RTC [shape="record", label="<f0> RTC | <f1> RTC CLOCK"];
 *
 *     GCLK:f1 -> RTCPRE:f1;
 *     RTCPRE:f1 -> RTC:f1;
 * }
 * \enddot
 *
 * \subsubsection asfdoc_sam0_rtc_count_clock_saml SAM L21/C20/C21/R30 Clock Setup
 * The RTC clock can be selected from OSC32K, XOSC32K, or OSCULP32K, and a 32KHz
 * or 1KHz oscillator clock frequency is required. This clock must be
 * configured and enabled in the 32KHz oscillator controller before using the RTC.
 *
 * The table below lists the available RTC clock \ref asfdoc_sam0_rtc_count_rtc_clk.
 *
 * \anchor asfdoc_sam0_rtc_count_rtc_clk
 * <table>
 *   <caption>RTC Clocks Source</caption>
 *   <tr>
 *     <th>RTC clock frequency</th>
 *     <th>Clock source</th>
 *     <th>Description</th>
 *   </tr>
 *   <tr>
 *     <td>1.024KHz</td>
 *     <td>ULP1K</td>
 *     <td>1.024KHz from 32KHz internal ULP oscillator</td>
 *   </tr>
 *   <tr>
 *     <td>32.768KHz</td>
 *     <td>ULP32K</td>
 *     <td>32.768KHz from 32KHz internal ULP oscillator</td>
 *   </tr>
 *   <tr>
 *     <td>1.024KHz</td>
 *     <td>OSC1K</td>
 *     <td>1.024KHz from 32KHz internal oscillator</td>
 *   </tr>
 *   <tr>
 *     <td>32.768KHz</td>
 *     <td>OSC32K</td>
 *     <td>32.768KHz from 32KHz internal oscillator</td>
 *   </tr>
 *   <tr>
 *     <td>1.024KHz</td>
 *     <td>XOSC1K</td>
 *     <td>1.024KHz from 32KHz internal oscillator</td>
 *   </tr>
 *   <tr>
 *     <td>32.768KHz</td>
 *     <td>XOSC32K</td>
 *     <td>32.768KHz from 32KHz external crystal oscillator</td>
 *   </tr>
 * </table>
 *
 * \section asfdoc_sam0_rtc_count_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_rtc_count_extra. This includes:
 *  - \ref asfdoc_sam0_rtc_count_extra_acronyms
 *  - \ref asfdoc_sam0_rtc_count_extra_dependencies
 *  - \ref asfdoc_sam0_rtc_count_extra_errata
 *  - \ref asfdoc_sam0_rtc_count_extra_history
 *
 *
 * \section asfdoc_sam0_rtc_count_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_rtc_count_exqsg.
 *
 *
 * \section asfdoc_sam0_rtc_count_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <conf_clocks.h>

#if RTC_COUNT_ASYNC == true
#  include <system_interrupt.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name Driver Feature Definition
 *
 * Define port features set according to different device family.
 * @{
*/
#if (SAML21) || (SAML22) || (SAMC20) || (SAMC21) || (SAMR30) || defined(__DOXYGEN__)
/** RTC periodic interval interrupt. */
#  define FEATURE_RTC_PERIODIC_INT
/** RTC prescaler is off. */
#  define FEATURE_RTC_PRESCALER_OFF
/** RTC clock selection. */
#  define FEATURE_RTC_CLOCK_SELECTION
#  if !(SAMC20) && !(SAMC21)
/** General purpose registers. */
#  define FEATURE_RTC_GENERAL_PURPOSE_REG
#  endif
#else
/** RTC continuously updated. */
#  define FEATURE_RTC_CONTINUOUSLY_UPDATED
#endif

#if (SAML22) || defined(__DOXYGEN__)
/** RTC tamper detection. */
#  define FEATURE_RTC_TAMPER_DETECTION
#endif

/*@}*/

#ifdef FEATURE_RTC_CLOCK_SELECTION
/**
 * \brief Available clock source for RTC.
 * RTC clock source.
 */
enum rtc_clock_sel {
	/** 1.024KHz from 32KHz internal ULP oscillator */
	RTC_CLOCK_SELECTION_ULP1K = OSC32KCTRL_RTCCTRL_RTCSEL_ULP1K_Val,
	/** 32.768KHz from 32KHz internal ULP oscillator */
	RTC_CLOCK_SELECTION_ULP32K = OSC32KCTRL_RTCCTRL_RTCSEL_ULP32K_Val,
#if !(SAML22)
	/** 1.024KHz from 32KHz internal oscillator */
	RTC_CLOCK_SELECTION_OSC1K = OSC32KCTRL_RTCCTRL_RTCSEL_OSC1K_Val,
	/** 32.768KHz from 32KHz internal oscillator */
	RTC_CLOCK_SELECTION_OSC32K = OSC32KCTRL_RTCCTRL_RTCSEL_OSC32K_Val,
#endif
	/** 1.024KHz from 32KHz external oscillator */
	RTC_CLOCK_SELECTION_XOSC1K = OSC32KCTRL_RTCCTRL_RTCSEL_XOSC1K_Val,
	/** 32.768KHz from 32.768KHz external crystal oscillator */
	RTC_CLOCK_SELECTION_XOSC32K = OSC32KCTRL_RTCCTRL_RTCSEL_XOSC32K_Val,
};
#endif

/**
 * \brief Available operation modes for the RTC.
 *
 * RTC Count operating modes, to select the counting width and associated module
 * operation.
 */
enum rtc_count_mode {
	/** RTC Count module operates in 16-bit mode */
	RTC_COUNT_MODE_16BIT = 0,
	/** RTC Count module operates in 32-bit mode */
	RTC_COUNT_MODE_32BIT = 1,
};

#if !defined (RTC_NUM_OF_COMP16) && defined(RTC_COMP16_NUM)
#define RTC_NUM_OF_COMP16 RTC_COMP16_NUM
#endif

/**
 * \brief Available compare channels.
 *
 * \note Not all compare channels are available in all devices and modes.
 */
enum rtc_count_compare {
	/** Compare channel 0 */
	RTC_COUNT_COMPARE_0 = 0,
#if (RTC_NUM_OF_COMP16 > 1) || defined(__DOXYGEN__)
	/** Compare channel 1 */
	RTC_COUNT_COMPARE_1 = 1,
#endif
#if (RTC_NUM_OF_COMP16 > 2) || defined(__DOXYGEN__)
	/** Compare channel 2 */
	RTC_COUNT_COMPARE_2 = 2,
#endif
#if (RTC_NUM_OF_COMP16 > 3)	|| defined(__DOXYGEN__)
	/** Compare channel 3 */
	RTC_COUNT_COMPARE_3 = 3,
#endif
#if (RTC_NUM_OF_COMP16 > 4) || defined(__DOXYGEN__)
	/** Compare channel 4 */
	RTC_COUNT_COMPARE_4 = 4,
#endif
#if (RTC_NUM_OF_COMP16 > 5) || defined(__DOXYGEN__)
	/** Compare channel 5 */
	RTC_COUNT_COMPARE_5 = 5,
#endif
};

#ifdef FEATURE_RTC_PERIODIC_INT
/**
 * \brief Available periodic interval source.
 */
enum rtc_count_periodic_interval{
	/** Periodic interval 0 */
	RTC_COUNT_PERIODIC_INTERVAL_0 = 0,
	/** Periodic interval 1 */
	RTC_COUNT_PERIODIC_INTERVAL_1 = 1,
	/** Periodic interval 2 */
	RTC_COUNT_PERIODIC_INTERVAL_2 = 2,
	/** Periodic interval 3 */
	RTC_COUNT_PERIODIC_INTERVAL_3 = 3,
	/** Periodic interval 4 */
	RTC_COUNT_PERIODIC_INTERVAL_4 = 4,
	/** Periodic interval 5 */
	RTC_COUNT_PERIODIC_INTERVAL_5 = 5,
	/** Periodic interval 6 */
	RTC_COUNT_PERIODIC_INTERVAL_6 = 6,
	/** Periodic interval 7 */
	RTC_COUNT_PERIODIC_INTERVAL_7 = 7,
};
#endif

#if RTC_COUNT_ASYNC == true
#ifdef FEATURE_RTC_PERIODIC_INT
/**
 * \brief Callback types.
 *
 * The available callback types for the RTC count module.
 */
enum rtc_count_callback {
	/** Callback for Periodic Interval 0 Interrupt */
	RTC_COUNT_CALLBACK_PERIODIC_INTERVAL_0 = 0,
	/** Callback for Periodic Interval 1 Interrupt */
	RTC_COUNT_CALLBACK_PERIODIC_INTERVAL_1,
	/** Callback for Periodic Interval 2 Interrupt */
	RTC_COUNT_CALLBACK_PERIODIC_INTERVAL_2,
	/** Callback for Periodic Interval 3 Interrupt */
	RTC_COUNT_CALLBACK_PERIODIC_INTERVAL_3,
	/** Callback for Periodic Interval 4 Interrupt */
	RTC_COUNT_CALLBACK_PERIODIC_INTERVAL_4,
	/** Callback for Periodic Interval 5 Interrupt */
	RTC_COUNT_CALLBACK_PERIODIC_INTERVAL_5,
	/** Callback for Periodic Interval 6 Interrupt */
	RTC_COUNT_CALLBACK_PERIODIC_INTERVAL_6,
	/** Callback for Periodic Interval 7 Interrupt */
	RTC_COUNT_CALLBACK_PERIODIC_INTERVAL_7,
	/** Callback for compare channel 0 */
	RTC_COUNT_CALLBACK_COMPARE_0,
#  if (RTC_NUM_OF_COMP16 > 1) || defined(__DOXYGEN__)
	/** Callback for compare channel 1 */
	RTC_COUNT_CALLBACK_COMPARE_1,
#  endif
#  if (RTC_NUM_OF_COMP16 > 2) || defined(__DOXYGEN__)
	/** Callback for compare channel 2 */
	RTC_COUNT_CALLBACK_COMPARE_2,
#  endif
#  if (RTC_NUM_OF_COMP16 > 3) || defined(__DOXYGEN__)
	/** Callback for compare channel 3 */
	RTC_COUNT_CALLBACK_COMPARE_3,
#  endif
#  if (RTC_NUM_OF_COMP16 > 4) || defined(__DOXYGEN__)
	/** Callback for compare channel 4 */
	RTC_COUNT_CALLBACK_COMPARE_4,
#  endif
#  if (RTC_NUM_OF_COMP16 > 5) || defined(__DOXYGEN__)
	/** Callback for compare channel 5 */
	RTC_COUNT_CALLBACK_COMPARE_5,
#  endif

#ifdef FEATURE_RTC_TAMPER_DETECTION
	/** Callback for tamper */
	RTC_COUNT_CALLBACK_TAMPER,
#endif

	/** Callback for overflow */
	RTC_COUNT_CALLBACK_OVERFLOW,
#  if !defined(__DOXYGEN__)
	/** Total number of callbacks */
	_RTC_COUNT_CALLBACK_N
#  endif
};
#else
/**
 * \brief Callback types.
 *
 * The available callback types for the RTC count module.
 */
enum rtc_count_callback {
	/** Callback for compare channel 0 */
	RTC_COUNT_CALLBACK_COMPARE_0 = 0,
#  if (RTC_NUM_OF_COMP16 > 1) || defined(__DOXYGEN__)
	/** Callback for compare channel 1 */
	RTC_COUNT_CALLBACK_COMPARE_1,
#  endif
#  if (RTC_NUM_OF_COMP16 > 2) || defined(__DOXYGEN__)
	/** Callback for compare channel 2 */
	RTC_COUNT_CALLBACK_COMPARE_2,
#  endif
#  if (RTC_NUM_OF_COMP16 > 3) || defined(__DOXYGEN__)
	/** Callback for compare channel 3 */
	RTC_COUNT_CALLBACK_COMPARE_3,
#  endif
#  if (RTC_NUM_OF_COMP16 > 4) || defined(__DOXYGEN__)
	/** Callback for compare channel 4 */
	RTC_COUNT_CALLBACK_COMPARE_4,
#  endif
#  if (RTC_NUM_OF_COMP16 > 5) || defined(__DOXYGEN__)
	/** Callback for compare channel 5 */
	RTC_COUNT_CALLBACK_COMPARE_5,
#  endif

#ifdef FEATURE_RTC_TAMPER_DETECTION
	/** Callback for tamper */
	RTC_COUNT_CALLBACK_TAMPER,
#endif

	/** Callback for overflow */
	RTC_COUNT_CALLBACK_OVERFLOW,
#  if !defined(__DOXYGEN__)
	/** Total number of callbacks */
	_RTC_COUNT_CALLBACK_N
#  endif
};
#endif

#  if !defined(__DOXYGEN__)
typedef void (*rtc_count_callback_t)(void);
#  endif
#endif

#ifdef FEATURE_RTC_PRESCALER_OFF
/**
 * \brief RTC input clock prescaler settings.
 *
 * The available input clock prescaler values for the RTC count module.
 */
enum rtc_count_prescaler {
	/** RTC prescaler is off, and the input clock frequency is
	prescaled by a factor of 1 */
	RTC_COUNT_PRESCALER_OFF      = RTC_MODE0_CTRLA_PRESCALER_OFF,
	/** RTC input clock frequency is prescaled by a factor of 1 */
	RTC_COUNT_PRESCALER_DIV_1    = RTC_MODE0_CTRLA_PRESCALER_DIV1,
	/** RTC input clock frequency is prescaled by a factor of 2 */
	RTC_COUNT_PRESCALER_DIV_2    = RTC_MODE0_CTRLA_PRESCALER_DIV2,
	/** RTC input clock frequency is prescaled by a factor of 4 */
	RTC_COUNT_PRESCALER_DIV_4    = RTC_MODE0_CTRLA_PRESCALER_DIV4,
	/** RTC input clock frequency is prescaled by a factor of 8 */
	RTC_COUNT_PRESCALER_DIV_8    = RTC_MODE0_CTRLA_PRESCALER_DIV8,
	/** RTC input clock frequency is prescaled by a factor of 16 */
	RTC_COUNT_PRESCALER_DIV_16   = RTC_MODE0_CTRLA_PRESCALER_DIV16,
	/** RTC input clock frequency is prescaled by a factor of 32 */
	RTC_COUNT_PRESCALER_DIV_32   = RTC_MODE0_CTRLA_PRESCALER_DIV32,
	/** RTC input clock frequency is prescaled by a factor of 64 */
	RTC_COUNT_PRESCALER_DIV_64   = RTC_MODE0_CTRLA_PRESCALER_DIV64,
	/** RTC input clock frequency is prescaled by a factor of 128 */
	RTC_COUNT_PRESCALER_DIV_128  = RTC_MODE0_CTRLA_PRESCALER_DIV128,
	/** RTC input clock frequency is prescaled by a factor of 256 */
	RTC_COUNT_PRESCALER_DIV_256  = RTC_MODE0_CTRLA_PRESCALER_DIV256,
	/** RTC input clock frequency is prescaled by a factor of 512 */
	RTC_COUNT_PRESCALER_DIV_512  = RTC_MODE0_CTRLA_PRESCALER_DIV512,
	/** RTC input clock frequency is prescaled by a factor of 1024 */
	RTC_COUNT_PRESCALER_DIV_1024 = RTC_MODE0_CTRLA_PRESCALER_DIV1024,
};
#else
/**
 * \brief RTC input clock prescaler settings.
 *
 * The available input clock prescaler values for the RTC count module.
 */
enum rtc_count_prescaler {
	/** RTC input clock frequency is prescaled by a factor of 1 */
	RTC_COUNT_PRESCALER_DIV_1    = RTC_MODE0_CTRL_PRESCALER_DIV1,
	/** RTC input clock frequency is prescaled by a factor of 2 */
	RTC_COUNT_PRESCALER_DIV_2    = RTC_MODE0_CTRL_PRESCALER_DIV2,
	/** RTC input clock frequency is prescaled by a factor of 4 */
	RTC_COUNT_PRESCALER_DIV_4    = RTC_MODE0_CTRL_PRESCALER_DIV4,
	/** RTC input clock frequency is prescaled by a factor of 8 */
	RTC_COUNT_PRESCALER_DIV_8    = RTC_MODE0_CTRL_PRESCALER_DIV8,
	/** RTC input clock frequency is prescaled by a factor of 16 */
	RTC_COUNT_PRESCALER_DIV_16   = RTC_MODE0_CTRL_PRESCALER_DIV16,
	/** RTC input clock frequency is prescaled by a factor of 32 */
	RTC_COUNT_PRESCALER_DIV_32   = RTC_MODE0_CTRL_PRESCALER_DIV32,
	/** RTC input clock frequency is prescaled by a factor of 64 */
	RTC_COUNT_PRESCALER_DIV_64   = RTC_MODE0_CTRL_PRESCALER_DIV64,
	/** RTC input clock frequency is prescaled by a factor of 128 */
	RTC_COUNT_PRESCALER_DIV_128  = RTC_MODE0_CTRL_PRESCALER_DIV128,
	/** RTC input clock frequency is prescaled by a factor of 256 */
	RTC_COUNT_PRESCALER_DIV_256  = RTC_MODE0_CTRL_PRESCALER_DIV256,
	/** RTC input clock frequency is prescaled by a factor of 512 */
	RTC_COUNT_PRESCALER_DIV_512  = RTC_MODE0_CTRL_PRESCALER_DIV512,
	/** RTC input clock frequency is prescaled by a factor of 1024 */
	RTC_COUNT_PRESCALER_DIV_1024 = RTC_MODE0_CTRL_PRESCALER_DIV1024,
};
#endif

/**
 * \brief RTC Count event enable/disable structure.
 *
 * Event flags for the \ref rtc_count_enable_events() and
 * \ref rtc_count_disable_events().
 */
struct rtc_count_events {
	/** Generate an output event on each overflow of the RTC count */
	bool generate_event_on_overflow;
	/** Generate an output event on a compare channel match against the RTC
	 *  count */
	bool generate_event_on_compare[RTC_NUM_OF_COMP16];
	/** Generate an output event periodically at a binary division of the RTC
	 *  counter frequency */
	bool generate_event_on_periodic[8];
#ifdef FEATURE_RTC_TAMPER_DETECTION
	/** Generate an output event on every tamper input */
	bool generate_event_on_tamper;
	/** Tamper input event and capture the COUNT value */
	bool on_event_to_tamper;
#endif
};

#if !defined(__DOXYGEN__)
/**
 * \brief Device structure.
 */
struct rtc_module {
	/** RTC hardware module */
	Rtc *hw;
	/** Operation mode of count */
	enum rtc_count_mode mode;
#ifdef FEATURE_RTC_CONTINUOUSLY_UPDATED
	/** Set if counter value should be continuously updated */
	bool continuously_update;
#endif
#  if RTC_COUNT_ASYNC == true
	/** Pointers to callback functions */
	volatile rtc_count_callback_t callbacks[_RTC_COUNT_CALLBACK_N];
	/** Mask for registered callbacks */
	volatile uint16_t registered_callback;
	/** Mask for enabled callbacks */
	volatile uint16_t enabled_callback;
#  endif
};
#endif

/**
 * \brief RTC Count configuration structure.
 *
 * Configuration structure for the RTC instance. This structure should
 * be initialized using the \ref rtc_count_get_config_defaults() before any
 * user configurations are set.
 */
struct rtc_count_config {
	/** Input clock prescaler for the RTC module */
	enum rtc_count_prescaler prescaler;
	/** Select the operation mode of the RTC */
	enum rtc_count_mode mode;
	/** If true, clears the counter value on compare match. Only available
	 *  whilst running in 32-bit mode */
	bool clear_on_match;
#ifdef FEATURE_RTC_CONTINUOUSLY_UPDATED
	/** Continuously update the counter value so no synchronization is
	 *  needed for reading */
	bool continuously_update;
#endif
#if (SAML21XXXB) || (SAML22) || (SAMC20) || (SAMC21) || (SAMR30)
	/** Enable count read synchronization. The COUNT value requires
	 * synchronization when reading. Disabling the synchronization
	 * will prevent the COUNT value from displaying the current value. */
	bool enable_read_sync;
#endif

	/** Array of Compare values. Not all Compare values are available in 32-bit
	 *  mode */
	uint32_t compare_values[RTC_NUM_OF_COMP16];
};


/**
 * \name Configuration and Initialization
 * @{
 */

/**
 *  \brief Gets the RTC default configurations.
 *
 *  Initializes the configuration structure to default values. This
 *  function should be called at the start of any RTC initialization.
 *
 *  The default configuration is:
 *  - Input clock divided by a factor of 1024
 *  - RTC in 32-bit mode
 *  - Clear on compare match off
 *  - Continuously sync count register off
 *  - No event source on
 *  - All compare values equal 0
 *  - Count read synchronization is enabled for SAM L22
 *
 *  \param[out] config  Configuration structure to be initialized to default
 *                      values
 */
static inline void rtc_count_get_config_defaults(
		struct rtc_count_config *const config)
{
	/* Sanity check argument */
	Assert(config);

	/* Set default into configuration structure */
	config->prescaler           = RTC_COUNT_PRESCALER_DIV_1024;
	config->mode                = RTC_COUNT_MODE_32BIT;
	config->clear_on_match      = false;

#ifdef FEATURE_RTC_CONTINUOUSLY_UPDATED
	config->continuously_update = false;
#endif
#if (SAML21XXXB) || (SAML22) || (SAMC20) || (SAMC21) || (SAMR30)
	config->enable_read_sync    = true;
#endif

	for (uint8_t i = 0; i < RTC_NUM_OF_COMP16; i++) {
		config->compare_values[i] = 0;
	}
}

void rtc_count_reset(struct rtc_module *const module);
void rtc_count_enable(struct rtc_module *const module);
void rtc_count_disable(struct rtc_module *const module);

#if (RTC_INST_NUM > 1) && !defined(__DOXYGEN__)
/**
 * \internal Find the index of given RTC module instance.
 *
 * \param[in] RTC module instance pointer
 *
 * \return Index of the given AC module instance.
 */
uint8_t _rtc_get_inst_index(
		Rtc *const hw)
{
	/* List of available RTC modules */
	static Rtc *const rtc_modules[RTC_INST_NUM] = RTC_INSTS;

	/* Find index for RTC instance */
	for (uint32_t i = 0; i < RTC_INST_NUM; i++) {
		if (hw == rtc_modules[i]) {
			return i;
		}
	}

	/* Invalid data given */
	Assert(false);
	return 0;
}
#endif /* (RTC_INST_NUM > 1) && !defined(__DOXYGEN__) */

enum status_code rtc_count_init(
		struct rtc_module *const module,
		Rtc *const hw,
		const struct rtc_count_config *const config);

enum status_code rtc_count_frequency_correction(
		struct rtc_module *const module,
		const int8_t value);

/** @} */

/** \name Count and Compare Value Management
 * @{
 */
enum status_code rtc_count_set_count(
		struct rtc_module *const module,
		const uint32_t count_value);

uint32_t rtc_count_get_count(struct rtc_module *const module);

enum status_code rtc_count_set_compare(
		struct rtc_module *const module,
		const uint32_t comp_value,
		const enum rtc_count_compare comp_index);

enum status_code rtc_count_get_compare(
		struct rtc_module *const module,
		uint32_t *const comp_value,
		const enum rtc_count_compare comp_index);

enum status_code rtc_count_set_period(
		struct rtc_module *const module,
		uint16_t period_value);

enum status_code rtc_count_get_period(
		struct rtc_module *const module,
		uint16_t *const period_value);

/** @} */


/** \name Status Management
 * @{
 */

/**
 * \brief Check if an RTC overflow has occurred.
 *
 * Checks the overflow flag in the RTC. The flag is set when there
 * is an overflow in the clock.
 *
 * \param[in,out]  module  RTC hardware module
 *
 * \return Overflow state of the RTC module.
 *
 * \retval true   If the RTC count value has overflowed
 * \retval false  If the RTC count value has not overflowed
 */

static inline bool rtc_count_is_overflow(struct rtc_module *const module)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	Rtc *const rtc_module = module->hw;

	/* Return status of flag */
	return (rtc_module->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_OVF);
}

/**
 * \brief Clears the RTC overflow flag.
 *
 * Clears the RTC module counter overflow flag, so that new overflow conditions
 * can be detected.
 *
 * \param[in,out]  module  RTC hardware module
 */
static inline void rtc_count_clear_overflow(struct rtc_module *const module)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	Rtc *const rtc_module = module->hw;

	/* Clear OVF flag */
	rtc_module->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_OVF;
}

#ifdef FEATURE_RTC_PERIODIC_INT
/**
 * \brief Check if an RTC periodic interval interrupt has occurred.
 *
 * Checks the periodic interval flag in the RTC.
 *
 * \param[in,out]  module  RTC hardware module
 * \param[in]  n  RTC periodic interval interrupt
 *
 * \return Periodic interval interrupt state of the RTC module.
 *
 * \retval true   RTC periodic interval interrupt occurs
 * \retval false  RTC periodic interval interrupt doesn't occur
 */
static inline bool rtc_count_is_periodic_interval(struct rtc_module *const module,
										enum rtc_count_periodic_interval n)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	Rtc *const rtc_module = module->hw;

	/* Return status of flag */
	return (rtc_module->MODE0.INTFLAG.reg & RTC_MODE0_INTFLAG_PER(1 << n));
}

/**
 * \brief Clears the RTC periodic interval flag.
 *
 * Clears the RTC module counter periodic interval flag, so that new periodic
 *  interval conditions can be detected.
 *
 * \param[in,out]  module  RTC hardware module
 * \param[in]  n  RTC periodic interval interrupt
 */
static inline void rtc_count_clear_periodic_interval(struct rtc_module *const module,
												enum rtc_count_periodic_interval n)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	Rtc *const rtc_module = module->hw;

	/* Clear periodic interval flag */
	rtc_module->MODE0.INTFLAG.reg = RTC_MODE0_INTFLAG_PER(1 << n);
}
#endif
bool rtc_count_is_compare_match(
		struct rtc_module *const module,
		const enum rtc_count_compare comp_index);

enum status_code rtc_count_clear_compare_match(
		struct rtc_module *const module,
		const enum rtc_count_compare comp_index);

/** @} */


/**
 * \name Event Management
 * @{
 */

/**
 * \brief Enables an RTC event output.
 *
 *  Enables one or more output events from the RTC module. See
 *  \ref rtc_count_events for a list of events this module supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in,out]  module  RTC hardware module
 *  \param[in] events    Struct containing flags of events to enable
 */
static inline void rtc_count_enable_events(
		struct rtc_module *const module,
		struct rtc_count_events *const events)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	Rtc *const rtc_module = module->hw;

	uint32_t event_mask = 0;

	/* Check if the user has requested an overflow event */
	if (events->generate_event_on_overflow) {
		event_mask |= RTC_MODE0_EVCTRL_OVFEO;
	}

	/* Check if the user has requested any compare events */
	for (uint8_t i = 0; i < RTC_NUM_OF_COMP16; i++) {
		if (events->generate_event_on_compare[i]) {
			event_mask |= RTC_MODE0_EVCTRL_CMPEO(1 << i);
		}
	}

	/* Check if the user has requested any periodic events */
	for (uint8_t i = 0; i < 8; i++) {
		if (events->generate_event_on_periodic[i]) {
			event_mask |= RTC_MODE0_EVCTRL_PEREO(1 << i);
		}
	}

#ifdef FEATURE_RTC_TAMPER_DETECTION
	/* Check if the user has requested a tamper event output. */
	if (events->generate_event_on_tamper) {
		event_mask |= RTC_MODE0_EVCTRL_TAMPEREO;
	}

	/* Check if the user has requested a tamper event input. */
	if (events->on_event_to_tamper) {
		event_mask |= RTC_MODE0_EVCTRL_TAMPEVEI;
	}
#endif

	/* Enable given event(s). */
	rtc_module->MODE0.EVCTRL.reg |= event_mask;
}

/**
 * \brief Disables an RTC event output.
 *
 *  Disabled one or more output events from the RTC module. See
 *  \ref rtc_count_events for a list of events this module supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in,out]  module  RTC hardware module
 *  \param[in] events    Struct containing flags of events to disable
 */
static inline void rtc_count_disable_events(
		struct rtc_module *const module,
		struct rtc_count_events *const events)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);

	Rtc *const rtc_module = module->hw;

	uint32_t event_mask = 0;

	/* Check if the user has requested an overflow event */
	if (events->generate_event_on_overflow) {
		event_mask |= RTC_MODE0_EVCTRL_OVFEO;
	}

	/* Check if the user has requested any compare events */
	for (uint8_t i = 0; i < RTC_NUM_OF_COMP16; i++) {
		if (events->generate_event_on_compare[i]) {
			event_mask |= RTC_MODE0_EVCTRL_CMPEO(1 << i);
		}
	}

	/* Check if the user has requested any periodic events */
	for (uint8_t i = 0; i < 8; i++) {
		if (events->generate_event_on_periodic[i]) {
			event_mask |= RTC_MODE0_EVCTRL_PEREO(1 << i);
		}
	}

#ifdef FEATURE_RTC_TAMPER_DETECTION
	/* Check if the user has requested a tamper event output. */
	if (events->generate_event_on_tamper) {
		event_mask |= RTC_MODE0_EVCTRL_TAMPEREO;
	}

	/* Check if the user has requested a tamper event input. */
	if (events->on_event_to_tamper) {
		event_mask |= RTC_MODE0_EVCTRL_TAMPEVEI;
	}
#endif

	/* Disable given event(s). */
	rtc_module->MODE0.EVCTRL.reg &= ~event_mask;
}

/** @} */

#ifdef FEATURE_RTC_GENERAL_PURPOSE_REG
/**
 * \name RTC General Purpose Registers
 * @{
 */

/**
 * \brief Write a value into general purpose register.
 *
 * \param[in] module  Pointer to the software instance struct
 * \param[in] n  General purpose type
 * \param[in] index General purpose register index (0..3)
 *
 */
static inline void rtc_write_general_purpose_reg(
	struct rtc_module *const module,
	const  uint8_t index,
	uint32_t value)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);
	Assert(index <= 3);

	Rtc *const rtc_module = module->hw;

	rtc_module->MODE0.GP[index].reg = value;
}

/**
 * \brief Read the value from general purpose register.
 *
 * \param[in] module  Pointer to the software instance struct
 * \param[in] index General purpose register index (0..3)
 *
 * \return Value of general purpose register.
 */
static inline uint32_t rtc_read_general_purpose_reg(
	struct rtc_module *const module,
	const  uint8_t index)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(module->hw);
	Assert(index <= 3);

	Rtc *const rtc_module = module->hw;

	return rtc_module->MODE0.GP[index].reg;
}

/** @} */
#endif

#ifdef FEATURE_RTC_TAMPER_DETECTION
#include "rtc_tamper.h"
/**
 * \brief Get the tamper stamp value.
 *
 * \param[in,out] module  Pointer to the software instance struct
 *
 * \return The current tamper stamp value as a 32-bit unsigned integer.
 */
uint32_t rtc_tamper_get_stamp (struct rtc_module *const module);
#endif


/** @} */

#ifdef __cplusplus
}
#endif

/**
 * \page asfdoc_sam0_rtc_count_extra Extra Information for RTC COUNT Driver
 *
 * \section asfdoc_sam0_rtc_count_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</td>
 *		<th>Description</td>
 *	</tr>
 *	<tr>
 *		<td>RTC</td>
 *		<td>Real Time Counter</td>
 *	</tr>
 *	<tr>
 *		<td>PPM</td>
 *		<td>Part Per Million</td>
 *	</tr>
 *	<tr>
 *		<td>RC</td>
 *		<td>Resistor/Capacitor</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_rtc_count_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_sam0_rtc_count_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_rtc_count_extra_history Module History
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
 *		<td>Added support for SAM C21</td>
 *	</tr>
 *	<tr>
 *		<td>Added support for SAM L21/L22</td>
 *	</tr>
 *	<tr>
 *		<td>Added support for SAM R30</td>
 *	</tr>
 *	<tr>
 *		<td>Added support for RTC tamper feature</td>
 *	</tr>
 *	<tr>
 *		<td>
 *          Added driver instance parameter to all API function calls, except
 *          get_config_defaults
 *      </td>
 *	</tr>
 *	<tr>
 *		<td>
 *			Updated initialization function to also enable the digital interface
 *          clock to the module if it is disabled
 *		</td>
 *	</tr>
 *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_rtc_count_exqsg Examples for RTC (COUNT) Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_rtc_count_group. QSGs are simple
 * examples with step-by-step instructions to configure and use this driver in a
 * selection of use cases. Note that a QSG can be compiled as a standalone
 * application or be added to the user application.
 *
 *  - \subpage asfdoc_sam0_rtc_count_basic_use_case
 * \if RTC_COUNT_CALLBACK_MODE
 *  - \subpage asfdoc_sam0_rtc_count_callback_use_case
 * \endif
 *  - \subpage asfdoc_sam0_rtc_tamper_dma_use_case
 *
 * \page asfdoc_sam0_rtc_count_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</th>
 *		<th>Date</th>
 *		<th>Comments</th>
 *	</tr>
 *	<tr>
 *		<td>42111E</td>
 *		<td>12/2015</td>
 *		<td>Added support for SAM L21/L22, SAM C21, SAM D09, SAMR30 and SAM DA1</td>
 *	</tr>
 *	<tr>
 *		<td>42111D</td>
 *		<td>12/2014</td>
 *		<td>Added support for SAM R21 and SAM D10/D11</td>
 *	</tr>
 *	<tr>
 *		<td>42111C</td>
 *		<td>01/2014</td>
 *		<td>Added support for SAM D21</td>
 *	</tr>
 *	<tr>
 *		<td>42111B</td>
 *		<td>06/2013</td>
 *		<td>Added additional documentation on the event system. Corrected
 *          documentation typos.</td>
 *	</tr>
 *	<tr>
 *		<td>42111A</td>
 *		<td>06/2013</td>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 */

#endif /* RTC_COUNT_H_INCLUDED */
