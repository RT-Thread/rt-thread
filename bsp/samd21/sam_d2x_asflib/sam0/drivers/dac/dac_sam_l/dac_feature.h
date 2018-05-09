/**
 * \file
 *
 * \brief SAM Peripheral Digital-to-Analog Converter Driver
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
#ifndef DAC_FEATURE_H_INCLUDED
#define DAC_FEATURE_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_dac_group SAM Digital-to-Analog (DAC) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an interface for the conversion of
 * digital values to analog voltage. The following driver API modes are covered
 * by this manual:
 *
 *  - Polled APIs
 * \if DAC_CALLBACK_MODE
 *  - Callback APIs
 * \endif
 *
 * The following peripheral is used by this module:
 *  - DAC (Digital-to-Analog Converter)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM L21
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_dac_prerequisites
 *  - \ref asfdoc_sam0_dac_module_overview
 *  - \ref asfdoc_sam0_dac_special_considerations
 *  - \ref asfdoc_sam0_dac_extra_info
 *  - \ref asfdoc_sam0_dac_examples
 *  - \ref asfdoc_sam0_dac_api_overview
 *
 *
 * \section asfdoc_sam0_dac_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_dac_module_overview Module Overview
 *
 * The Digital-to-Analog converter converts a digital value to an analog voltage.
 * The DAC Controller can operate as two independent DACs or as a single DAC
 * in differential mode. Each DAC has a 12-bit resolution and it is capable of
 * converting up to 1M samples per second (Msps).
 *
 * A common use of DAC is to generate audio signals by connecting the DAC
 * output to a speaker, or to generate a reference voltage; either for an
 * external circuit or an internal peripheral such as the Analog Comparator.
 *
 * After being set up, the DAC will convert new digital values written to the
 * conversion data register (DATA0 or DATA1) to an analog value either on the
 * DAC output (VOUT0 or VOUT1) pin of the device, or internally for use as an
 * input to the AC, ADC, and other analog modules.
 *
 * Writing the DATA register will start a new conversion. It is also possible
 * to trigger the conversion from the event system.
 *
 * A simplified block diagram of the DAC can be seen in
 * \ref asfdoc_sam0_dac_module_block_diagram "the figure below".
 *
 * \anchor asfdoc_sam0_dac_module_block_diagram
 * \image html dac_block_diagram_saml.svg "DAC Block Diagram"
 *
 * \subsection asfdoc_sam0_dac_conversion_range Conversion Range
 * The conversion range is between GND and the selected voltage reference.
 * Available voltage references are:
 * \li Voltage supply (VDDANA)
 * \li Internal bandgap reference (INTREF)
 * \li Unbuffered External voltage reference (VREFPU)
 * \li Buffered External voltage reference (VREFPB)
 *
 * \note Internal references will be enabled by the driver, but not disabled.
 * Any reference not used by the application should be disabled by the application.
 *
 * The output voltage from a DAC channel is given as:
 * \f[
 *    V_{OUTx} = \frac{DATAx}{0x3FF} \times VREF
 * \f]
 * The differential output voltage is given as:
 * \f[
 *    V_{OUT} = \frac{DATA0}{0x1FF} \times VREF = (V_{OUT0}-V_{OUT1})
 * \f]
 *
 * \subsection asfdoc_sam0_dac_conversion Conversion
 * The conversion digital value written to the DATA register will be converted
 * to an analog value. Writing the DATA register will start a new conversion.
 * It is also possible to write the conversion value to the DATABUF register,
 * the writing of the DATA register can then be triggered from the event
 * system, which will load the value from DATABUF to DATA.
 *
 * \subsection asfdoc_sam0_dac_analog_output Analog Output
 * The analog output value can be output to the VOUTx converted by DACx, and
 * each data conversion can be started independently.
 *
 * In differential mode, DAC0 and DAC1 are operating synchronously to convert
 * value. VOUT0 is the positive output and VOUT1 the negative output.
 *
 * VOUT0 signal is internally connected so that it can be used as input for
 * AC, ADC, or OPAMP modules when DAC0 is enabled.
 * \note The pin VOUT0 will be dedicated to internal input and cannot be
 * configured as alternate function.
 *
 * \subsection asfdoc_sam0_dac_events Events
 * Events generation and event actions are configurable in the DAC.
 * The DAC has one event line input and one event output: <i>Start Conversion</i>
 * and <i>Data Buffer Empty</i>.
 *
 * If the Start Conversion input event is enabled in the module configuration,
 * an incoming event will load data from the data buffer to the data register
 * and start a new conversion. This method synchronizes conversions with
 * external events (such as those from a timer module) and ensures regular and
 * fixed conversion intervals.
 *
 * If the Data Buffer Empty output event is enabled in the module configuration,
 * events will be generated when the DAC data buffer register becomes empty and
 * new data can be loaded to the buffer.
 *
 * \note The connection of events between modules requires the use of the
 *       \ref asfdoc_sam0_events_group "SAM Event System Driver (EVENTS)"
 *       to route output event of one module to the the input event of another.
 *       For more information on event routing, refer to the event driver
 *       documentation.
 *
 * \subsection asfdoc_sam0_dac_data_adjust Left and Right Adjusted Values
 * The 12-bit input value to the DAC is contained in a 16-bit register. This
 * can be configured to be either left or right adjusted. In
 * \ref asfdoc_sam0_dac_module_adj_modes "the figure below" both options are
 * shown, and the position of the most (MSB) and the least (LSB) significant bits
 * are indicated. The unused bits should always be written to zero.
 *
 * \anchor asfdoc_sam0_dac_module_adj_modes
 * \dot
 * digraph {
 *   subgraph cluster_right {
 *      msbl [label="MSB", shape=none, group="msbl"];
 *      lsbl [label="LSB", shape=none];
 *      node [shape=none];
 *      color="white";
 *      reg_left [label=<
 *        <table cellspacing="0" cellpadding="2" width="100%">
 *          <tr>
 *            <td port="msb">15</td>
 *            <td>14</td>
 *            <td>13</td>
 *            <td>12</td>
 *            <td>11</td>
 *            <td>10</td>
 *            <td>9</td>
 *            <td>8</td>
 *            <td>7</td>
 *            <td>6</td>
 *            <td>5</td>
 *            <td port="lsb">4</td>
 *            <td>3</td>
 *            <td>2</td>
 *            <td>1</td>
 *            <td>0</td>
 *          </tr>
 *          <tr>
 *            <td COLSPAN="12"> DATA[11:0] </td>
 *            <td BGCOLOR="lightgray"> </td>
 *            <td BGCOLOR="lightgray"> </td>
 *            <td BGCOLOR="lightgray"> </td>
 *            <td BGCOLOR="lightgray"> </td>
 *          </tr>
 *        </table>
 *      >];
 *      msbl -> reg_left:msb:n;
 *      lsbl -> reg_left:lsb;
 *      label ="Left adjusted.\n";
 *   }
 *   subgraph cluster_left {
 *      rankdir=TB;
 *      msb [label="MSB", shape=none];
 *      lsb [label="LSB", shape=none];
 *      color="white";
 *      node [shape=none];
 *      reg_right [label=<
 *        <table cellspacing="0" cellpadding="2">
 *          <tr>
 *            <td>15</td>
 *            <td>14</td>
 *            <td>13</td>
 *            <td>12</td>
 *            <td port="msb">11</td>
 *            <td>10</td>
 *            <td>9</td>
 *            <td>8</td>
 *            <td>7</td>
 *            <td>6</td>
 *            <td>5</td>
 *            <td>4</td>
 *            <td>3</td>
 *            <td>2</td>
 *            <td>1</td>
 *            <td port="lsb">0</td>
 *          </tr>
 *          <tr>
 *            <td BGCOLOR="lightgray"></td>
 *            <td BGCOLOR="lightgray"></td>
 *            <td BGCOLOR="lightgray"></td>
 *            <td BGCOLOR="lightgray"></td>
 *            <td COLSPAN="12"> DATA[11:0] </td>
 *          </tr>
 *        </table>
 *      >];
 *      msb -> reg_right:msb;
 *      lsb -> reg_right:lsb:n;
 *      label = "Right adjusted.\n";
 *      graph [shape=none];
 *  }
 * }
 * \enddot
 *
 * \subsection asfdoc_sam0_dac_clk_sources Clock Sources
 * The clock for the DAC interface (CLK_DAC) is generated by the Power Manager.
 * This clock is turned on by default, and can be enabled and disabled in the
 * Power Manager.
 *
 * Additionally, an asynchronous clock source (GCLK_DAC) is required.
 * These clocks are normally disabled by default. The selected clock source
 * must be enabled in the Power Manager before it can be used by the DAC.
 * The DAC core operates asynchronously from the user interface and
 * peripheral bus. As a consequence, the DAC needs two clock cycles of both
 * CLK_DAC and GCLK_DAC to synchronize the values written to some of the
 * control and data registers.
 * The oscillator source for the GCLK_DAC clock is selected in the Supply
 * Control Interface (SUPC).
 *
 * \section asfdoc_sam0_dac_special_considerations Special Considerations
 *
 * \subsection asfdoc_sam0_dac_special_considerations_sleep Sleep Mode
 * The DAC can do conversions in Active or Idle modes, and will continue the
 * conversions in standby sleep mode if the RUNSTDBY bit in the DACCTRLx
 * register is set. Otherwise, the DACx will stop conversions.
 *
 * If DACx conversion is stopped in standby sleep mode, DACx is disabled to
 * reduce power consumption. When exiting standby sleep mode, DACx is enabled
 * therefore startup time is required before starting a new conversion.
 *
 * \subsection asfdoc_sam0_dac_special_considerations_conversion_time Conversion Time
 * DAC conversion time is approximately 2.85µs. The user must ensure that new
 * data is not written to the DAC before the last conversion is complete.
 * Conversions should be triggered by a periodic event from a Timer/Counter or
 * another peripheral.
 *
 *
 * \section asfdoc_sam0_dac_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_dac_extra. This includes:
 *  - \ref asfdoc_sam0_dac_extra_acronyms
 *  - \ref asfdoc_sam0_dac_extra_dependencies
 *  - \ref asfdoc_sam0_dac_extra_errata
 *  - \ref asfdoc_sam0_dac_extra_history
 *
 *
 * \section asfdoc_sam0_dac_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_dac_exqsg.
 *
 *
 * \section asfdoc_sam0_dac_api_overview API Overview
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <clock.h>
#include <gclk.h>


/**
 * \name DAC Status Flags
 *
 * DAC status flags, returned by \ref dac_get_status() and cleared by
 * \ref dac_clear_status().
 * @{
 */

/** Data Buffer Empty Channel 0 - Set when data is transferred from DATABUF
 *  to DATA by a start conversion event and DATABUF is ready for new data.
 */
#define DAC_STATUS_CHANNEL_0_EMPTY     (1UL << 0)

/** Data Buffer Empty Channel 1 - Set when data is transferred from DATABUF
 *  to DATA by a start conversion event and DATABUF is ready for new data.
 */
#define DAC_STATUS_CHANNEL_1_EMPTY     (1UL << 1)

/** Underrun Channel 0 - Set when a start conversion event occurs when
 *  DATABUF is empty.
 */
#define DAC_STATUS_CHANNEL_0_UNDERRUN  (1UL << 2)

/** Underrun Channel 1 - Set when a start conversion event occurs when
 *  DATABUF is empty.
 */
#define DAC_STATUS_CHANNEL_1_UNDERRUN  (1UL << 3)

/** @} */

/**
 * \brief DAC reference voltage enum.
 *
 * Enum for the possible reference voltages for the DAC.
 */
enum dac_reference {
	/** Unbuffered external voltage reference */
	DAC_REFERENCE_VREFPU = DAC_CTRLB_REFSEL(0),
	/** Analog VCC as reference */
	DAC_REFERENCE_VDDANA = DAC_CTRLB_REFSEL(1),
	/** Buffered external voltage reference */
	DAC_REFERENCE_VREFPB = DAC_CTRLB_REFSEL(2),
	/** Internal bandgap reference */
	DAC_REFERENCE_INTREF = DAC_CTRLB_REFSEL(3),
};

/**
 * \brief DAC current control enum.
 *
 * Enum for the current in output buffer according the conversion rate.
 */
enum dac_current_ctrl {
	/** GCLK_DAC <= 1.2MHz */
	DAC_CURRENT_100K  = DAC_DACCTRL_CCTRL(0),
	/** 1.2MHz < GCLK_DAC <= 6MHz */
	DAC_CURRENT_1M   = DAC_DACCTRL_CCTRL(1),
	/** 6MHz < GCLK_DAC <= 12MHz */
	DAC_CURRENT_12M = DAC_DACCTRL_CCTRL(2),
	/** Reserved */
	DAC_CURRENT_RESERVED  = DAC_DACCTRL_CCTRL(3),
};

/**
 * \brief DAC channel selection enum.
 *
 * Enum for the DAC channel selection.
 */
enum dac_channel {
	/** DAC output channel 0 */
	DAC_CHANNEL_0,
	/** DAC output channel 1 */
	DAC_CHANNEL_1,
#if !defined(__DOXYGEN__)
	DAC_CHANNEL_N,
#endif
};

/**
 * \brief DAC software device instance structure.
 *
 * DAC software instance structure, used to retain software state information
 * of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct dac_module {
#if !defined(__DOXYGEN__)
	/** DAC hardware module */
	Dac *hw;
	/** Reference selection */
	enum dac_reference reference;
	/** DAC event selection */
	bool start_on_event[DAC_CHANNEL_N];
#  if DAC_CALLBACK_MODE == true
	/** Pointer to buffer used for ADC results */
	volatile uint16_t *job_buffer[DAC_CHANNEL_N];
	/** Remaining number of conversions in current job */
	volatile uint16_t remaining_conversions[DAC_CHANNEL_N];
	/** Transferred number of conversions in current job */
	volatile uint16_t transferred_conversions[DAC_CHANNEL_N];
	/** DAC callback enable */
	bool callback_enable[DAC_CHANNEL_N][DAC_CALLBACK_N];
	/** DAC registered callback functions */
	dac_callback_t callback[DAC_CHANNEL_N][DAC_CALLBACK_N];
	/** Holds the status of the ongoing or last conversion job */
	volatile enum status_code job_status[DAC_CHANNEL_N];
#  endif
#endif
};

/**
 * \brief DAC configuration structure.
 *
 * Configuration structure for a DAC instance. This structure should be
 * initialized by the \ref dac_get_config_defaults()
 * function before being modified by the user application.
 */
struct dac_config {
	/** Differential mode enable data */
	bool differential_mode;
	/** Reference voltage */
	enum dac_reference reference;
	/** GCLK generator used to clock the peripheral */
	enum gclk_generator clock_source;
};

/**
 * \brief DAC channel configuration structure.
 *
 * Configuration for a DAC channel. This structure should be initialized by the
 * \ref dac_chan_get_config_defaults() function before being modified by the
 * user application.
 */
struct dac_chan_config {
	/** Left adjusted data */
	bool left_adjust;
	/** Current control data */
	enum dac_current_ctrl current;
	/**
	 * The DAC behaves as in normal mode when the chip enters STANDBY sleep
	 * mode
	 */
	bool run_in_standby;
	/** Dither mode enable data */
	bool dither_mode;
	/**
	 * The DAC conversion refreshed periodically when used to generate a static
	 * voltage
	 */
	uint8_t refresh_period;
};

/**
 * \brief DAC event enable/disable structure.
 *
 * Event flags for the DAC module. This is used to enable and
 * disable events via \ref dac_enable_events() and \ref dac_disable_events().
 */
struct dac_events {
	/** Start a new DAC0 conversion */
	bool on_event_chan0_start_conversion;
	/** Start a new DAC1 conversion */
	bool on_event_chan1_start_conversion;
	/** Enable event generation on DAC0 data buffer empty */
	bool generate_event_on_chan0_buffer_empty;
	/** Enable event generation on DAC1 data buffer empty */
	bool generate_event_on_chan1_buffer_empty;
	/** Enable the falling edge of the input event for DAC0 */
	bool generate_event_on_chan0_falling_edge;
	/** Enable the falling edge of the input event for DAC1 */
	bool generate_event_on_chan1_falling_edge;
};

/**
 * \name Status Management (Channel)
 * @{
 */
bool dac_chan_is_end_of_conversion(
		struct dac_module *const module_inst,
		enum dac_channel channel);
/** @} */

/** @} */

/**
 * \page asfdoc_sam0_dac_extra Extra Information for DAC Driver
 *
 * \section asfdoc_sam0_dac_extra_acronyms Acronyms
 * The table below presents the acronyms used in this module:
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>ADC</td>
 *		<td>Analog-to-Digital Converter</td>
 *	</tr>
 *	<tr>
 *		<td>AC</td>
 *		<td>Analog Comparator</td>
 *	</tr>
 *	<tr>
 *		<td>DAC</td>
 *		<td>Digital-to-Analog Converter</td>
 *	</tr>
 *	<tr>
 *		<td>LSB</td>
 *		<td>Least Significant Bit</td>
 *	</tr>
 *	<tr>
 *		<td>MSB</td>
 *		<td>Most Significant Bit</td>
 *	</tr>
 *	<tr>
 *		<td>DMA</td>
 *		<td>Direct Memory Access</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_dac_extra_dependencies Dependencies
 * This driver has the following dependency:
 *
 *  - \ref asfdoc_sam0_system_pinmux_group "System Pin Multiplexer Driver"
 *
 *
 * \section asfdoc_sam0_dac_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_dac_extra_history Module History
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
 * \page asfdoc_sam0_dac_exqsg Examples for DAC Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_dac_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_dac_basic_use_case
 * \if DAC_CALLBACK_MODE
 *  - \subpage asfdoc_sam0_dac_basic_use_case_callback
 * \endif
 * \if DAC_DMA_USE_MODE_SELECTION
 *  - \subpage asfdoc_sam0_adc_dma_use_case_dac_in_dma
 * \endif
 *
 * \if DAC_DMA_USE_MODE_SELECTION
 * \page asfdoc_sam0_adc_dma_use_case_dac_in_dma Quick Start Guide for Using DMA with ADC/DAC
 * For this examples, see
 * \ref asfdoc_sam0_adc_dma_use_case
 * \endif
 *
 * \page asfdoc_sam0_dac_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42450A</td>
 *		<td>07/2015</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */
#ifdef __cplusplus
}
#endif


#endif /* DAC_FEATURE_H_INCLUDED */

