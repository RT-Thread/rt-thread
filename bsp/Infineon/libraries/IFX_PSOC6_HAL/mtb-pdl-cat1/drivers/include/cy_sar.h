/***************************************************************************//**
* \file cy_sar.h
* \version 2.10
*
* Header file for the SAR driver.
*
********************************************************************************
* \copyright
* Copyright 2017-2021 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_sar
* \{
* This driver configures and controls the SAR ADC subsystem block, which is a
* part of \ref group_pass_structure "PASS" hardware block.
*
* The functions and other declarations used in this driver are in cy_sar.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* This SAR ADC block is comprised of:
*   - a 12-bit SAR converter (SARADC)
*   - an embedded reference block (SARREF)
*   - a mux (\ref group_sar_sarmux "SARMUX") at the inputs of the converter
*   - a sequence controller (\ref group_sar_sarmux "SARSEQ") that enables multi-channel acquisition
*       in a round robin fashion, without CPU intervention, to maximize scan rates.
*
* Devices with PASS_v2 hardware block may contain multiple SAR ADC blocks.
*
* \image html sar_block_diagram.png
*
* The high level features of the subsystem are:
*   - maximum sample rate of 1 Msps (2 Msps for devices with PASS_v2 hardware block)
*   - sixteen individually configurable channels (depends on device routing capabilities)
*   - per channel selectable
*       - single-ended or differential input mode
*       - input from external pin (8 channels in single-ended mode or 4 channels in differential mode)
*         or from internal signals (AMUXBUS, CTB, Die Temperature Sensor)
*       - choose one of four programmable acquisition times
*       - averaging and accumulation
*   - scan can be triggered by firmware or hardware in single shot or continuous mode
*   - hardware averaging from 2 to 256 samples
*   - selectable voltage references
*       - internal VDDA and VDDA/2 references
*       - buffered 1.2 V bandgap reference from \ref group_sysanalog_aref "AREF"
*       - external reference from dedicated pin
*   - interrupt generation
*   - built-in FIFO buffer (PASS_v2 only)
*   - ability to perform scans in Deep Sleep power mode (PASS_v2 only).
*
* \section group_sar_usage Usage
*
* The high level steps to use this driver are:
*
*   -# \ref group_sar_initialization
*   -# \ref group_sar_trigger_conversions
*   -# \ref group_sar_handle_interrupts
*   -# \ref group_sar_retrieve_result
*   -# \ref group_sar_fifo_usage
*
* \section group_sar_initialization Initialization and Enable
*
* To configure the SAR subsystem, call \ref Cy_SAR_Init. Pass in a pointer to the \ref SAR_Type
* structure for the base hardware register address and pass in the configuration structure,
* \ref cy_stc_sar_config_t.
*
* \note Make sure to choose correct hardware identifiers, taking into account the indexing in the used device:
* \snippet sar/snippet/main.c SNIPPET_SAR_HW_COMPATIBILITY
*
*
* After initialization, call \ref Cy_SAR_Enable to enable the hardware.
*
* Here is guidance on how to set the data fields of the configuration structure:
*
* \subsection group_sar_init_struct_ctrl uint32_t ctrl
*
* This field specifies configurations that apply to all channels such as the Vref
* source or the negative terminal selection for all single-ended channels.
* Select a value from each of the following enums that begin with "cy_en_sar_ctrl_" and "OR" them together.
*   - \ref cy_en_sar_ctrl_pwr_ctrl_vref_t
*   - \ref cy_en_sar_ctrl_vref_sel_t
*   - \ref cy_en_sar_ctrl_bypass_cap_t
*   - \ref cy_en_sar_ctrl_neg_sel_t
*   - \ref cy_en_sar_ctrl_hw_ctrl_negvref_t
*   - \ref cy_en_sar_ctrl_comp_delay_t
*   - \ref cy_en_sar_ctrl_comp_pwr_t
*   - \ref cy_en_sar_ctrl_sarmux_deep_sleep_t
*   - \ref cy_en_sar_ctrl_sarseq_routing_switches_t
*
* \snippet sar/snippet/main.c SNIPPET_CTRL
*
* \subsection group_sar_init_struct_sampleCtrl uint32_t sampleCtrl
*
* This field configures sampling details that apply to all channels.
* Select a value from each of the following enums that begin with "cy_en_sar_sample_" and "OR" them together.
*   - \ref cy_en_sar_sample_ctrl_result_align_t
*   - \ref cy_en_sar_sample_ctrl_single_ended_format_t
*   - \ref cy_en_sar_sample_ctrl_differential_format_t
*   - \ref cy_en_sar_sample_ctrl_avg_cnt_t
*   - \ref cy_en_sar_sample_ctrl_avg_mode_t
*   - \ref cy_en_sar_sample_ctrl_trigger_mode_t
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SAMPLE_CTRL
*
* \subsection group_sar_init_struct_sampleTime01 uint32_t sampleTime01
*
* This field configures the value for sample times 0 and 1 in ADC clock cycles.
*
* The SAR has four programmable 10-bit aperture times that are configured using two data fields,
* \ref group_sar_init_struct_sampleTime01 and
* \ref group_sar_init_struct_sampleTime23.
* Ten bits allow for a range of 0 to 1023 cycles, however 0 and 1 are invalid.
* The minimum aperture time is 167 ns. With an 18 MHz ADC clock, this is
* equal to 3 cycles or a value of 4 in this field. The actual aperture time is one cycle less than
* the value stored in this field.
*
* Use the shifts defined in \ref cy_en_sar_sample_time_shift_t.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SAMPLE_TIME01
*
* \subsection group_sar_init_struct_sampleTime23 uint32_t sampleTime23
*
* This field configures the value for sample times 2 and 3 in ADC clock cycles.
* Use the shifts defined in \ref cy_en_sar_sample_time_shift_t.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SAMPLE_TIME23
*
* \subsection group_sar_init_struct_rangeThres uint32_t rangeThres
*
* This field configures the upper and lower thresholds for the range interrupt.
* These thresholds apply on a global level for all channels with range detection enabled.
*
* The SARSEQ supports range detection to allow for automatic detection of sample values
* compared to two programmable thresholds without CPU involvement.
* Range detection is done after averaging, alignment, and sign extension (if applicable). In other words the
* threshold values need to have the same data format as the result data.
* The values are interpreted as signed or unsigned according to each channel's configuration.
*
* Use the shifts defined in \ref cy_en_sar_range_thres_shift_t.
*
* The \ref Cy_SAR_SetLowLimit and \ref Cy_SAR_SetHighLimit provide run-time configurability of these thresholds.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_RANGE_THRES
*
* \subsection group_sar_init_struct_rangeCond cy_en_sar_range_detect_condition_t rangeCond
*
* This field configures the condition (below, inside, outside, or above) that will trigger
* the range interrupt. Select a value from the \ref cy_en_sar_range_detect_condition_t enum.
*
* \subsection group_sar_init_struct_chanEn uint32_t chanEn
*
* This field configures which channels will be scanned.
* Each bit corresponds to a channel. Bit 0 enables channel 0, bit 1 enables channel 1,
* bit 2 enables channel 2, and so on.
*
* \subsection group_sar_init_struct_chanConfig uint32_t chanConfig[16]
*
* Each channel has its own channel configuration register.
* The channel configuration specifies which pin/signal is connected to that channel
* and how the channel is sampled.
*
* Select a value from each of the following enums that begin with "cy_en_sar_chan_config_" and "OR" them together.
*
*   - \ref cy_en_sar_chan_config_input_mode_t
*   - \ref cy_en_sar_chan_config_pos_pin_addr_t
*   - \ref cy_en_sar_chan_config_pos_port_addr_t
*   - \ref cy_en_sar_chan_config_avg_en_t
*   - \ref cy_en_sar_chan_config_sample_time_t
*   - \ref cy_en_sar_chan_config_neg_pin_addr_t
*   - \ref cy_en_sar_chan_config_neg_port_addr_t
*
* Some important considerations are:
*   - The POS_PORT_ADDR and POS_PIN_ADDR bit fields are used by the SARSEQ to select
*   the connection to the positive terminal (Vplus) of the ADC for each channel.
*   - When the channel is an unpaired differential input (\ref CY_SAR_CHAN_DIFFERENTIAL_UNPAIRED), the
*   NEG_PORT_ADDR and NEG_PIN_ADDR are used by the SARSEQ to select the connection
*   to the negative terminal (Vminus) of the ADC.
*   - When the channel is a differential input pair (\ref CY_SAR_CHAN_DIFFERENTIAL_PAIRED), the NEG_PORT_ADDR and NEG_PIN_ADDR are ignored.
*   For differential input pairs, only the pin for the positive terminal needs to be
*   specified and this pin must be even. For example, Pin 0 (positive terminal) and Pin 1 (negative terminal)
*   are a pair. Pin 2 (positive terminal) and Pin 3 (negative terminal) are a pair.
*
* If the SARSEQ is disabled (\ref cy_en_sar_ctrl_sarseq_routing_switches_t) or
* it is not controlling any switches (\ref group_sar_init_struct_muxSwitchSqCtrl = 0), the port and pin addresses
* are ignored. This is possible when there is only one channel to scan.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_CHAN_CONFIG
*
* \subsection group_sar_init_struct_intrMask uint32_t intrMask
*
* This field configures which interrupt events (end of scan, overflow, or firmware collision) will be serviced by the firmware.
*
* Select one or more values from the \ref group_sar_macros_interrupt enum and "OR" them
* together.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_INTR_MASK
*
* \subsection group_sar_init_struct_satIntrMask uint32_t satIntrMask
*
* This field configures which channels will cause a saturation interrupt.
*
* The SARSEQ has a saturation detect that is always applied to every conversion.
* This feature detects whether a channel's sample value is equal to the minimum or maximum values.
* This allows the firmware to take action, for example, discard the result, when the SARADC saturates.
* The sample value is tested right after conversion, that is, before averaging. This means that it
* can happen that the interrupt is set while the averaged result in the data register is not
* equal to the minimum or maximum.
*
* Each bit corresponds to a channel. A value of 0 disables saturation detection for all channels.
*
* \subsection group_sar_init_struct_rangeIntrMask uint32_t rangeIntrMask
*
* This field configures which channels will cause a range detection interrupt.
* Each bit corresponds to a channel. A value of 0 disables range detection for all channels.
*
* \subsection group_sar_init_struct_muxSwitch uint32_t muxSwitch
*
* This field is the firmware control of the SARMUX switches.
*
* Use one or more values from the \ref cy_en_sar_mux_switch_fw_ctrl_t enum and "OR" them together.
* If the SARSEQ is enabled, the SARMUX switches that will be used must
* also be closed using this firmware control.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_MUX_SWITCH
*
* Firmware control can be changed at run-time by calling \ref Cy_SAR_SetAnalogSwitch with \ref CY_SAR_MUX_SWITCH0
* and the desired switch states.
*
* \subsection group_sar_init_struct_muxSwitchSqCtrl uint32_t muxSwitchSqCtrl
*
* This field enables or disables SARSEQ control of the SARMUX switches.
* To disable control of all switches, set this field to 0. To disable the SARSEQ all together,
* use \ref CY_SAR_SARSEQ_SWITCH_DISABLE when configuring the \ref group_sar_init_struct_ctrl register.
*
* Use one or more values from the \ref cy_en_sar_mux_switch_sq_ctrl_t enum and "OR" them together.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_MUX_SQ_CTRL
*
* SARSEQ control can be changed at run-time by calling \ref Cy_SAR_SetSwitchSarSeqCtrl.
*
* \subsection group_sar_init_struct_configRouting bool configRouting
*
* If true, the \ref group_sar_init_struct_muxSwitch and \ref group_sar_init_struct_muxSwitchSqCtrl fields
* will be used. If false, the fields will be ignored.
*
* \subsection group_sar_init_struct_vrefMvValue uint32_t vrefMvValue
*
* This field sets the value of the reference voltage in millivolts used. This value
* is used for converting counts to volts in the \ref Cy_SAR_CountsTo_Volts, \ref Cy_SAR_CountsTo_mVolts, and
* \ref Cy_SAR_CountsTo_uVolts functions.
*
* The rest of the \ref cy_stc_sar_config_t fields starting from \ref cy_stc_sar_config_t::clock affects
* SAR ADC configuration only for PASS_ver2. Refer to \ref cy_stc_sar_config_t for details.
*
* \section group_sar_trigger_conversions Triggering Conversions
*
* The SAR subsystem has the following modes for triggering a conversion:
* <table class="doxtable">
*   <tr>
*     <th>Mode</th>
*     <th>Description</th>
*     <th>Usage</th>
*   </tr>
*   <tr>
*     <td>Continuous</td>
*     <td>After completing a scan, the
*     SARSEQ will immediately start the next scan. That is, the SARSEQ will always be BUSY.
*     As a result all other triggers, firmware or hardware, are essentially ignored.
*  </td>
*     <td>To enter this mode, call \ref Cy_SAR_StartConvert with \ref CY_SAR_START_CONVERT_CONTINUOUS.
*     To stop continuous conversions, call \ref Cy_SAR_StopConvert.
*     </td>
*   </tr>
*   <tr>
*     <td>Firmware single shot</td>
*     <td>A single conversion of all enabled channels is triggered with a function call to \ref Cy_SAR_StartConvert with
*     \ref CY_SAR_START_CONVERT_SINGLE_SHOT.
*     </td>
*     <td>
*     Firmware triggering is always available by calling \ref Cy_SAR_StartConvert with \ref CY_SAR_START_CONVERT_SINGLE_SHOT.
*     To allow only firmware triggering, or disable
*     hardware triggering, set up the \ref cy_stc_sar_config_t config structure with \ref CY_SAR_TRIGGER_MODE_FW_ONLY.
*     </td>
*   </tr>
*   <tr>
*     <td>Hardware edge sensitive</td>
*     <td>A single conversion of all enabled channels is triggered on the rising edge of the hardware
*     trigger signal.</td>
*     <td>To enable this mode, set up the \ref cy_stc_sar_config_t config structure with
*     \ref CY_SAR_TRIGGER_MODE_FW_AND_HWEDGE.</td>
*    </tr>
*    <tr>
*     <td>Hardware level sensitive</td>
*     <td>Conversions are triggered continuously when the hardware trigger signal is high.</td>
*     <td>To enable this mode, set up the \ref cy_stc_sar_config_t config structure with
*     \ref CY_SAR_TRIGGER_MODE_FW_AND_HWLEVEL.</td>
*    </tr>
* </table>
*
* If trigger occurs during a scan, a \ref CY_SAR_INTR_FW_COLLISION interrupt occurs and the trigger is delayed until after end of scan.
*
* The trigger mode can be changed during run time with \ref Cy_SAR_SetConvertMode.
*
* For the hardware trigger modes, use the \ref group_trigmux driver to route an internal or external
* signal to the SAR trigger input.
* When making the required \ref Cy_TrigMux_Connect calls, use the pre-defined enum, TRIG6_OUT_PASS_TR_SAR_IN,
* for the SAR trigger input.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_CONFIG_TRIGGER
*
* \section group_sar_handle_interrupts Handling Interrupts
*
* The SAR can generate interrupts on these events:
*
*   - End of scan (EOS): when scanning of all enabled channels complete.
*   - Overflow: when the result register is updated before the previous result is read.
*   - FW collision: when a new trigger is received while the SAR is still processing the previous trigger.
*   - Saturation detection: when the channel result is equal to the minimum or maximum value.
*   - Range detection: when the channel result meets the programmed upper or lower threshold values.
*
* The SAR interrupt to the NVIC is raised any time the intersection (logic and) of the interrupt
* flags and the corresponding interrupt masks are non-zero.
*
* Implement an interrupt routine and assign it to the SAR interrupt.
* Use the pre-defined enum, pass_interrupt_sar_IRQn, as the interrupt source for the SAR.
*
* The following code snippet demonstrates how to implement a routine to handle the interrupt.
* The routine gets called when any one of the SAR interrupts are triggered.
* When servicing an interrupt, the user must clear the interrupt so that subsequent
* interrupts can be handled.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_ISR
*
* The following code snippet demonstrates how to configure and enable the interrupt.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_CONFIG_INTR
*
* Alternately, instead of handling the interrupts, the \ref Cy_SAR_IsEndConversion function
* allows for firmware polling of the end of conversion status.
*
* \section group_sar_retrieve_result Retrieve Channel Results
*
* Retrieve the ADC result by calling \ref Cy_SAR_GetResult16 with the desired channel.
* To convert the result to a voltage, pass the ADC result to \ref Cy_SAR_CountsTo_Volts, \ref Cy_SAR_CountsTo_mVolts, or
* \ref Cy_SAR_CountsTo_uVolts.
*
* \section group_sar_fifo_usage FIFO Usage
*
* The PASS_ver2 SAR can operate in the system Deep Sleep power mode.
* To do so the SAR should be clocked by the \ref group_sysanalog_dpslp,
* triggered by the \ref group_sysanalog_timer, and use the FIFO:
* \snippet sar/snippet/main.c SNIPPET_FIFO_ISR
* \snippet sar/snippet/main.c SNIPPET_FIFO_OPERATE
*
* \section group_sar_clock SAR Clock Configuration
*
* The SAR requires a clock. Assign a clock to the SAR using the
* pre-defined enum, PCLK_PASS_CLOCK_SAR, to identify the SAR subsystem.
* Set the clock divider value to achieve the desired clock rate. The SAR can support
* a maximum frequency of 18 MHz.
*
* For PASS_ver2 the maximum clock frequency is 36 MHz.
* Also, the SAR clock could be switched to the \ref group_sysanalog_dpslp to operate in
* the system Deep Sleed power mode using \ref cy_stc_sar_config_t::clock.
*
* \snippet sar/snippet/main.c SAR_SNIPPET_CONFIGURE_CLOCK
*
* \section group_sar_scan_time Scan Rate
*
* The scan rate is dependent on the following:
*
*   - ADC clock rate
*   - Number of channels
*   - Averaging
*   - Resolution
*   - Acquisition times
*
* \subsection group_sar_acquisition_time Acquisition Time
*
* The acquisition time of a channel is based on which of the four global aperture times are selected for that
* channel. The selection is done during initialization per channel with \ref group_sar_init_struct_chanConfig.
* The four global aperture times are also set during initialization with \ref group_sar_init_struct_sampleTime01 and
* \ref group_sar_init_struct_sampleTime23. Note that these global aperture times are in SAR clock cycles and the
* acquisition time is 1 less than that value in the register.
*
* \image html sar_acquisition_time_eqn.png
*
* \subsection group_sar_channel_sample_time Channel Sample Time
*
* The sample time for a channel is the time required to acquire the analog signal
* and convert it to a digital code.
*
* \image html sar_channel_sample_time_eqn.png
*
* The SAR ADC is a 12-bit converter so Resolution = 12.
*
* \subsection group_sar_total_scan_time Total Scan Time
*
* Channels using one of the sequential averaging modes (\ref CY_SAR_AVG_MODE_SEQUENTIAL_ACCUM or \ref CY_SAR_AVG_MODE_SEQUENTIAL_FIXED)
* are sampled multiple times per scan. The number of samples averaged are set during initialization
* with \ref group_sar_init_struct_sampleCtrl using one of the values from \ref cy_en_sar_sample_ctrl_avg_cnt_t.
* Channels that are not averaged or use the \ref CY_SAR_AVG_MODE_INTERLEAVED mode are only sampled once per scan.
*
* The total scan time is the sum of each channel's sample time multiplied by the samples per scan.
*
* \image html sar_scan_rate_eqn.png
*
* where N is the total number of channels in the scan.
*
* \section group_sar_sarmux SARMUX and SARSEQ
*
* The SARMUX is an analog programmable multiplexer. Its switches can be controlled by the SARSEQ or firmware.
* and the inputs can come from:
*   - a dedicated port (can support 8 single-ended channels or 4 differential channels)
*   - an internal die temperature (DieTemp) sensor
*   - CTB output via SARBUS0/1 (if CTBs are available on the device)
*   - AMUXBUSA/B
*
* The following figure shows the SARMUX switches. See the device datasheet for the exact location of SARMUX pins.
*
* \image html sar_sarmux_switches.png
*
* When using the SARSEQ, the following configurations must be performed:
*   - enable SARSEQ control of required switches (see \ref group_sar_init_struct_muxSwitchSqCtrl)
*   - close the required switches with firmware (see \ref group_sar_init_struct_muxSwitch)
*   - configure the POS_PORT_ADDR and POS_PIN_ADDR, and if used, the NEG_PORT_ADDR and NEG_PIN_ADDR (see \ref group_sar_init_struct_chanConfig)
*
* While firmware can control every switch in the SARMUX, not every switch can be controlled by the SARSEQ (green switches in the above figure).
* Additionally, switches outside of the SARMUX such as the AMUXBUSA/B switches or
* CTB switches will require separate function calls (see \ref group_gpio "GPIO" and \ref group_ctb "CTB" drivers).
* The SARSEQ can control three switches in the \ref group_ctb "CTB" driver (see \ref Cy_CTB_EnableSarSeqCtrl).
* These switches need to be enabled for SARSEQ control if the CTB outputs are used as the SARMUX inputs.
*
* The following table shows the required POS_PORT_ADDR and POS_PIN_ADDR settings
* for different input connections.
*
* <table class="doxtable">
*   <tr>
*     <th>Input Connection Selection</th>
*     <th>POS_PORT_ADDR</th>
*     <th>POS_PIN_ADDR</th>
*   </tr>
*   <tr>
*     <td>SARMUX dedicated port</td>
*     <td>\ref CY_SAR_POS_PORT_ADDR_SARMUX</td>
*     <td>\ref CY_SAR_CHAN_POS_PIN_ADDR_0 through \ref CY_SAR_CHAN_POS_PIN_ADDR_7</td>
*   </tr>
*   <tr>
*     <td>DieTemp sensor</td>
*     <td>\ref CY_SAR_POS_PORT_ADDR_SARMUX_VIRT</td>
*     <td>\ref CY_SAR_CHAN_POS_PIN_ADDR_0</td>
*   </tr>
*   <tr>
*     <td>AMUXBUSA</td>
*     <td>\ref CY_SAR_POS_PORT_ADDR_SARMUX_VIRT</td>
*     <td>\ref CY_SAR_CHAN_POS_PIN_ADDR_2</td>
*   </tr>
*   <tr>
*     <td>AMUXBUSB</td>
*     <td>\ref CY_SAR_POS_PORT_ADDR_SARMUX_VIRT</td>
*     <td>\ref CY_SAR_CHAN_POS_PIN_ADDR_3</td>
*   </tr>
*   <tr>
*     <td>CTB0 Opamp0 1x output</td>
*     <td>\ref CY_SAR_POS_PORT_ADDR_CTB0</td>
*     <td>\ref CY_SAR_CHAN_POS_PIN_ADDR_2</td>
*   </tr>
*   <tr>
*     <td>CTB0 Opamp1 1x output</td>
*     <td>\ref CY_SAR_POS_PORT_ADDR_CTB0</td>
*     <td>\ref CY_SAR_CHAN_POS_PIN_ADDR_3</td>
*   </tr>
* </table>
*
* \subsection group_sar_sarmux_dietemp Input from DieTemp sensor
*
* When using the DieTemp sensor, always use single-ended mode.
* The temperature sensor can be routed to Vplus using the \ref CY_SAR_MUX_FW_TEMP_VPLUS switch.
* Connecting this switch will also enable the sensor. Set the \ref group_sar_acquisition_time "acquisition time" to
* be at least 1 us to meet the settling time of the temperature sensor.
*
* \image html sar_sarmux_dietemp.png
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SARMUX_DIETEMP
*
* \subsection group_sar_sarmux_se_diff Input from SARMUX port
*
* The following figure and code snippet show how two GPIOs on the SARMUX dedicated port
* are connected to the SARADC as separate single-ended channels and as a differential-pair channel.
*
* \image html sar_sarmux_dedicated_port.png
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SARMUX_SE_DIFF
*
* \subsection group_sar_sarmux_ctb Input from CTB output visa SARBUS0/1
*
* The following figure and code snippet show how the two opamp outputs from the CTB
* are connected to the SARADC as separate single-ended channels and as a differential-pair channel.
* Note that separate function calls are needed to configure and enable the opamps, perform required analog routing,
* and enable SARSEQ control of the switches contained in the CTB.
*
* \image html sar_sarmux_ctb.png
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SARMUX_CTB
*
* \subsection group_sar_sarmux_amuxbus Input from other pins through AMUXBUSA/B
*
* The following figure and code snippet show how two GPIOs on any port through the AMUXBUSA and AMUXBUSB
* are connected to the SARADC as separate single-ended channels and as a differential-pair channel.
* Note that separate function calls are needed to route the device pins to the SARMUX. The AMUXBUSes
* are separated into multiple segments and these segments are connected/disconnected using the AMUX_SPLIT_CTL
* registers in the HSIOM.
*
* \image html sar_sarmux_amuxbus.png
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SARMUX_AMUXBUS
*
*
* To connect SARMUX to any other non-dedicated port, you may need to close additional HSIOM switches to route signals
* through AMUXBUS.
* For more detail, see the device TRM, AMUX splitting.
*
* The following code snippet is an alternative pin configuration. To connect Port 1 to AMUXBUS, close the left and
* right switches of AMUX_SPLIT_CTL[1] and AMUX_SPLIT_CTL[6].
*
* \warning
* This snippet shows how to configure pins for CY8C6347BZI-BLD53.
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SARMUX_CUSTOM_PORT
*
* \section group_sar_low_power Low Power Support
* This SAR driver provides a callback function to handle power mode transitions.
* The \ref Cy_SAR_DeepSleepCallback function ensures that SAR conversions are stopped
* before Deep Sleep entry. Upon wakeup, the callback
* enables the hardware and continuous conversions, if previously enabled.
*
* To trigger the callback execution, the callback must be registered before calling \ref Cy_SysPm_CpuEnterDeepSleep. Refer to
* \ref group_syspm driver for more information about power mode transitions and
* callback registration.
*
* Recall that during configuration of the \ref group_sar_init_struct_ctrl "ctrl" field,
* the SARMUX can be configured to remain enabled in Deep Sleep mode.
* All other blocks (SARADC, REFBUF, and SARSEQ) do not support Deep Sleep mode operation.
*
* \section group_sar_more_information More Information
* For more information on the SAR ADC subsystem, refer to the technical reference manual (TRM).
*
* \section group_sar_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>2.10</td>
*     <td>The FIFO level validation in debug mode is fixed in the Cy_SAR_FifoSetLevel().</td>
*     <td>Bug fixing.</td>
*   </tr>
*   <tr>
*     <td>2.0.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="4">2.0</td>
*     <td>Added the next PASS_ver2 features: \ref group_sar_functions_lp, \ref group_sar_functions_fifo, and \ref group_sar_functions_trig.</td>
*     <td>New silicon support.</td>
*   </tr>
*   <tr>
*     <td>The Result Format check is added to the \ref Cy_SAR_Init function when the interleaved averaging mode is used.</td>
*     <td>HW bug workaround.</td>
*   </tr>
*   <tr>
*     <td>\ref Cy_SAR_Enable and \ref Cy_SAR_Disable functions behavior is changed -
*         now \ref Cy_SAR_Disable checks the busy status before shutting down, and \ref Cy_SAR_Enable doesn't.</td>
*     <td>Bug fixing.</td>
*   </tr>
*   <tr>
*     <td>Fixed/Documented MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.20.3</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.20.2</td>
*     <td>Code snippets update.</td>
*     <td>PDL infrastructure update, documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.20.1</td>
*     <td>Code snippets update.</td>
*     <td>PDL infrastructure update, documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.20</td>
*     <td>Flattened the organization of the driver source code into the single source directory and the single include directory.</td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">1.10</td>
*     <td> Added workaround for parts with out of range CAP_TRIM in Init API.</td>
*     <td> Correct CAP_TRIM is necessary achieving specified SAR ADC linearity</td>
*   </tr>
*   <tr>
*     <td> Turn off the entire hardware block only if the SARMUX is not enabled
*          for Deep Sleep operation.
*     </td>
*     <td> Improvement of the \ref Cy_SAR_DeepSleep flow</td>
*   </tr>
*   <tr>
*     <td>Updated "Low Power Support" section to describe registering the Deep Sleep callback.
*         Added parenthesis around logical AND operation in Sleep API.</td>
*     <td>Documentation update and clarification</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_sar_macros Macros
*   \{
*       \defgroup group_sar_macros_interrupt        Interrupt Masks
*   \}
* \defgroup group_sar_functions Functions
*   \{
*       \defgroup group_sar_functions_basic         Initialization and Basic Functions
*       \defgroup group_sar_functions_power         Low Power Callback
*       \defgroup group_sar_functions_config        Run-time Configuration Functions
*       \defgroup group_sar_functions_countsto      Counts Conversion Functions
*       \defgroup group_sar_functions_interrupt     Interrupt Functions
*       \defgroup group_sar_functions_switches      SARMUX Switch Control Functions
*       \defgroup group_sar_functions_helper        Useful Configuration Query Functions
*       \defgroup group_sar_functions_lp            Low Power features control Functions
*       \defgroup group_sar_functions_fifo          FIFO buffer control Functions
*       \defgroup group_sar_functions_trig          Common triggering Functions for multiple SAR instances
*   \}
* \defgroup group_sar_data_structures Data Structures
* \defgroup group_sar_enums Enumerated Types
*   \{
*       \defgroup group_sar_ctrl_register_enums         Control Register Enums
*       \defgroup group_sar_sample_ctrl_register_enums  Sample Control Register Enums
*       \defgroup group_sar_sample_time_shift_enums     Sample Time Register Enums
*       \defgroup group_sar_range_thres_register_enums  Range Interrupt Register Enums
*       \defgroup group_sar_chan_config_register_enums  Channel Configuration Register Enums
*       \defgroup group_sar_mux_switch_register_enums   SARMUX Switch Control Register Enums
*   \}
*/

#if !defined(CY_SAR_H)
#define CY_SAR_H

#include "cy_device.h"

#ifdef CY_IP_MXS40PASS_SAR

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "cy_syslib.h"
#include "cy_syspm.h"

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 27, \
'SAR_Type will typecast to either SAR_V1_Type or SAR_V2_Type but not both on PDL initialization based on the target device at compile time.');

/** \addtogroup group_sar_macros
* \{
*/

/** Driver major version */
#define CY_SAR_DRV_VERSION_MAJOR        2

/** Driver minor version */
#define CY_SAR_DRV_VERSION_MINOR        10

/** SAR driver identifier */
#define CY_SAR_ID                       CY_PDL_DRV_ID(0x01u)

/** \cond Legacy definition, use CY_SAR_SEQ_NUM_CHANNELS instead */
#define CY_SAR_MAX_NUM_CHANNELS         (PASS_SAR_SAR_CHANNELS)
/** \endcond */

/** Number of sequencer channels */
#define CY_SAR_SEQ_NUM_CHANNELS         (PASS_SAR_SAR_CHANNELS)

/** Number of all channels including the injection channel */
#define CY_SAR_NUM_CHANNELS             (CY_SAR_SEQ_NUM_CHANNELS + 1UL)

/** Injection channel index */
#define CY_SAR_INJ_CHANNEL              (CY_SAR_SEQ_NUM_CHANNELS)

/** Channels mask */
#define CY_SAR_CHANNELS_MASK            ((1UL << CY_SAR_SEQ_NUM_CHANNELS) - 1UL)

/** Injection channel mask */
#define CY_SAR_INJ_CHAN_MASK            (1UL << CY_SAR_INJ_CHANNEL)


/** \addtogroup group_sar_macros_interrupt
* \{
*/

/** Interrupt masks */
#define CY_SAR_INTR_EOS                 (SAR_INTR_MASK_EOS_MASK_Msk)           /**< Enable end of scan (EOS) interrupt */
#define CY_SAR_INTR_OVERFLOW            (SAR_INTR_MASK_OVERFLOW_MASK_Msk)      /**< Enable overflow interrupt */
#define CY_SAR_INTR_FW_COLLISION        (SAR_INTR_MASK_FW_COLLISION_MASK_Msk)  /**< Enable firmware collision interrupt */
#define CY_SAR_INTR_INJ_EOC             (SAR_INTR_INJ_EOC_INTR_Msk)            /**< Enable injection channel end of conversion (EOC) interrupt */
#define CY_SAR_INTR_INJ_SATURATE        (SAR_INTR_INJ_SATURATE_INTR_Msk)       /**< Enable injection channel saturation interrupt */
#define CY_SAR_INTR_INJ_RANGE           (SAR_INTR_INJ_RANGE_INTR_Msk)          /**< Enable injection channel range detection interrupt */
#define CY_SAR_INTR_INJ_COLLISION       (SAR_INTR_INJ_COLLISION_INTR_Msk)      /**< Enable injection channel firmware collision interrupt */
#define CY_SAR_INTR_FIFO_LEVEL          (PASS_FIFO_V2_INTR_FIFO_LEVEL_Msk)     /**< Enable FIFO level interrupt */
#define CY_SAR_INTR_FIFO_OVERFLOW       (PASS_FIFO_V2_INTR_FIFO_OVERFLOW_Msk)  /**< Enable FIFO overflow interrupt */
#define CY_SAR_INTR_FIFO_UNDERFLOW      (PASS_FIFO_V2_INTR_FIFO_UNDERFLOW_Msk) /**< Enable FIFO underflow interrupt */

/** Combined interrupt mask */
#define CY_SAR_INTR                     (CY_SAR_INTR_EOS | \
                                         CY_SAR_INTR_OVERFLOW | \
                                         CY_SAR_INTR_FW_COLLISION | \
                                         CY_SAR_INTR_INJ_EOC | \
                                         CY_SAR_INTR_INJ_SATURATE | \
                                         CY_SAR_INTR_INJ_RANGE | \
                                         CY_SAR_INTR_INJ_COLLISION)

/** Combined interrupt mask for FIFO */
#define CY_SAR_INTR_FIFO                (CY_SAR_INTR_FIFO_LEVEL | \
                                         CY_SAR_INTR_FIFO_OVERFLOW | \
                                         CY_SAR_INTR_FIFO_UNDERFLOW)
/** \} group_sar_macros_interrupt */

/** \defgroup group_sysanalog_sar_select SAR block instance masks
* \{
* Specifies the SAR block instance.
*/
#define CY_SAR_SAR0                     (1UL)                           /**< SAR 0 instance */
#define CY_SAR_SAR1                     (2UL)                           /**< SAR 1 instance */
#define CY_SAR_SAR2                     (4UL)                           /**< SAR 2 instance */
#define CY_SAR_SAR3                     (8UL)                           /**< SAR 3 instance */
#define CY_SAR_INSTANCE_MASK(base)      (1UL << CY_SAR_INSTANCE(base))  /**< Convert SAR base to instance mask. Could be used instead of SAR 0 - SAR 3 instance masks */
#define CY_SAR_TIMER                    (1UL<<31UL)                     /**< Trigger source is Timer. Used only for simultTrigSource configuration in \ref cy_stc_sar_common_config_t */
/** \} group_sysanalog_sar_select */

/** \cond INTERNAL */
#define CY_SAR_DEINIT                   (0UL)             /**< De-init value for most SAR registers */
#define CY_SAR_SAMPLE_TIME_DEINIT       ((3UL << SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos) | (3UL << SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos))  /**< De-init value for the SAMPLE_TIME* registers */
#define CY_SAR_CLEAR_ALL_SWITCHES       (0x3FFFFFFFUL)    /**< Value to clear all SARMUX switches */
#define CY_SAR_DEINIT_SQ_CTRL           (SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P0_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P1_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P2_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P3_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P4_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P5_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P6_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P7_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_VSSA_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_TEMP_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_AMUXBUSA_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_AMUXBUSB_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_SARBUS0_Msk \
                                        | SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_SARBUS1_Msk)
#define CY_SAR_REG_CTRL_MASK            (SAR_CTRL_PWR_CTRL_VREF_Msk \
                                        | SAR_CTRL_VREF_SEL_Msk \
                                        | SAR_CTRL_VREF_BYP_CAP_EN_Msk \
                                        | SAR_CTRL_NEG_SEL_Msk \
                                        | SAR_CTRL_SAR_HW_CTRL_NEGVREF_Msk \
                                        | SAR_CTRL_COMP_DLY_Msk \
                                        | SAR_CTRL_REFBUF_EN_Msk \
                                        | SAR_CTRL_COMP_PWR_Msk \
                                        | SAR_CTRL_DEEPSLEEP_ON_Msk \
                                        | SAR_CTRL_DSI_SYNC_CONFIG_Msk \
                                        | SAR_CTRL_DSI_MODE_Msk \
                                        | SAR_CTRL_SWITCH_DISABLE_Msk \
                                        | SAR_CTRL_ENABLED_Msk)
#define CY_SAR_REG_SAMPLE_CTRL_MASK     (SAR_SAMPLE_CTRL_LEFT_ALIGN_Msk \
                                        | SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Msk \
                                        | SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Msk \
                                        | SAR_SAMPLE_CTRL_AVG_CNT_Msk \
                                        | SAR_SAMPLE_CTRL_AVG_SHIFT_Msk \
                                        | SAR_SAMPLE_CTRL_AVG_MODE_Msk \
                                        | SAR_SAMPLE_CTRL_CONTINUOUS_Msk \
                                        | SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Msk \
                                        | SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk \
                                        | SAR_SAMPLE_CTRL_DSI_SYNC_TRIGGER_Msk \
                                        | SAR_SAMPLE_CTRL_UAB_SCAN_MODE_Msk \
                                        | SAR_SAMPLE_CTRL_REPEAT_INVALID_Msk \
                                        | SAR_SAMPLE_CTRL_VALID_SEL_Msk \
                                        | SAR_SAMPLE_CTRL_VALID_SEL_EN_Msk \
                                        | SAR_SAMPLE_CTRL_VALID_IGNORE_Msk \
                                        | SAR_SAMPLE_CTRL_TRIGGER_OUT_EN_Msk \
                                        | SAR_SAMPLE_CTRL_EOS_DSI_OUT_EN_Msk)
#define CY_SAR_REG_CHAN_CONFIG_MASK     (SAR_CHAN_CONFIG_POS_PIN_ADDR_Msk \
                                        | SAR_CHAN_CONFIG_POS_PORT_ADDR_Msk \
                                        | SAR_CHAN_CONFIG_DIFFERENTIAL_EN_Msk \
                                        | SAR_CHAN_CONFIG_AVG_EN_Msk \
                                        | SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Msk \
                                        | SAR_CHAN_CONFIG_NEG_PIN_ADDR_Msk \
                                        | SAR_CHAN_CONFIG_NEG_PORT_ADDR_Msk \
                                        | SAR_CHAN_CONFIG_NEG_ADDR_EN_Msk \
                                        | SAR_CHAN_CONFIG_DSI_OUT_EN_Msk)
#define CY_SAR_REG_SAMPLE_TIME_MASK     (SAR_SAMPLE_TIME01_SAMPLE_TIME0_Msk | SAR_SAMPLE_TIME01_SAMPLE_TIME1_Msk)

#define CY_SAR_2US_DELAY                (2u)              /**< Delay used in Enable API function to avoid SAR deadlock */
#define CY_SAR_10V_COUNTS               (10.0F)           /**< Value of 10 in volts */
#define CY_SAR_10MV_COUNTS              (10000)           /**< Value of 10 in millivolts */
#define CY_SAR_10UV_COUNTS              (10000000L)       /**< Value of 10 in microvolts */
#define CY_SAR_WRK_MAX_12BIT            (0x00001000L)     /**< Maximum SAR work register value for a 12-bit resolution */
#define CY_SAR_RANGE_LIMIT_MAX          (0xFFFFUL)        /**< Maximum value for the low and high range interrupt threshold values */
#define CY_SAR_CAP_TRIM_MAX             (0x3FUL)          /**< Maximum value for CAP_TRIM */
#define CY_SAR_CAP_TRIM_MIN             (0x00UL)          /**< Maximum value for CAP_TRIM */
#define CY_SAR_CAP_TRIM                 (0x0BUL)          /**< Correct cap trim value */

/* Macros for conditions used in CY_ASSERT calls */
#define CY_SAR_CHANNUM(chan)            ((chan) < CY_SAR_MAX_NUM_CHANNELS) /* legacy */
#define CY_SAR_CHANMASK(mask)           (0UL == ((mask) & ~CY_SAR_CHANNELS_MASK))
#define CY_SAR_INJMASK(mask)            (0UL == ((mask) & ~(CY_SAR_INJ_CHAN_MASK | CY_SAR_CHANNELS_MASK)))
#define CY_SAR_RANGECOND(cond)          ((cond) <= CY_SAR_RANGE_COND_OUTSIDE)
#define CY_SAR_INTRMASK(mask)           (0UL == ((mask) & ~CY_SAR_INTR))
#define CY_SAR_FIFO_INTRMASK(mask)      (0UL == ((mask) & ~CY_SAR_INTR_FIFO))
#define CY_SAR_TRIGGER(mode)            (((mode) == CY_SAR_TRIGGER_MODE_FW_ONLY) || \
                                         ((mode) == CY_SAR_TRIGGER_MODE_FW_AND_HWEDGE) || \
                                         ((mode) == CY_SAR_TRIGGER_MODE_FW_AND_HWLEVEL))
#define CY_SAR_RETURN(mode)             (((mode) == CY_SAR_RETURN_STATUS) || \
                                         ((mode) == CY_SAR_WAIT_FOR_RESULT) || \
                                         ((mode) == CY_SAR_RETURN_STATUS_INJ) || \
                                         ((mode) == CY_SAR_WAIT_FOR_RESULT_INJ))
#define CY_SAR_STARTCONVERT(mode)       (((mode) == CY_SAR_START_CONVERT_SINGLE_SHOT) || ((mode) == CY_SAR_START_CONVERT_CONTINUOUS))
#define CY_SAR_RANGE_LIMIT(limit)       ((limit) <= CY_SAR_RANGE_LIMIT_MAX)
#define CY_SAR_SWITCHSELECT(select)     ((select) == CY_SAR_MUX_SWITCH0)
#define CY_SAR_SWITCHMASK(mask)         ((mask) <= CY_SAR_CLEAR_ALL_SWITCHES)
#define CY_SAR_SWITCHSTATE(state)       (((state) == CY_SAR_SWITCH_OPEN) || ((state) == CY_SAR_SWITCH_CLOSE))
#define CY_SAR_SQMASK(mask)             (((mask) & (~CY_SAR_DEINIT_SQ_CTRL)) == 0UL)
#define CY_SAR_SQCTRL(ctrl)             (((ctrl) == CY_SAR_SWITCH_SEQ_CTRL_ENABLE) || ((ctrl) == CY_SAR_SWITCH_SEQ_CTRL_DISABLE))
#define CY_SAR_CTRL(value)              (((value) & (~CY_SAR_REG_CTRL_MASK)) == 0UL)
#define CY_SAR_SAMPLE_CTRL(value)       (((value) & (~CY_SAR_REG_SAMPLE_CTRL_MASK)) == 0UL)
#define CY_SAR_SAMPLE_TIME(value)       (((value) & (~CY_SAR_REG_SAMPLE_TIME_MASK)) == 0UL)
#define CY_SAR_CHAN_CONFIG(value)       (((value) & (~CY_SAR_REG_CHAN_CONFIG_MASK)) == 0UL)
#define CY_SAR_IS_FIFO_LEVEL_VALID(level) ((level) <= PASS_FIFO_V2_LEVEL_LEVEL_Msk)
#define CY_SAR_IS_CLK_VALID(clock)      (((clock) == CY_SAR_CLK_PERI) || \
                                         ((clock) == CY_SAR_CLK_DEEPSLEEP))

#define CY_SAR_IS_DSCLK(base)           ((uint32_t)CY_SAR_CLK_DEEPSLEEP == _FLD2VAL(PASS_V2_SAR_CLOCK_SEL_CLOCK_SEL, PASS_SAR_CLOCK_SEL(base)))
/** \endcond */

/** \} group_sar_macro */


/** \cond
 * These arrays exposed here for BWC
 * Not recommended to directly use in application code
 */
extern volatile int16_t Cy_SAR_offset[CY_SAR_NUM_CHANNELS][CY_SAR_INSTANCES];
extern volatile int32_t Cy_SAR_countsPer10Volt[CY_SAR_NUM_CHANNELS][CY_SAR_INSTANCES];
/** \endcond */


/** \addtogroup group_sar_enums
* \{
*/

/******************************************************************************
 * Enumerations
 *****************************************************************************/

/** The SAR status/error code definitions */
typedef enum
{
    CY_SAR_SUCCESS    = 0x00UL,                                      /**< Success */
    CY_SAR_BAD_PARAM  = CY_SAR_ID | CY_PDL_STATUS_ERROR | 0x01UL,    /**< Invalid input parameters */
    CY_SAR_TIMEOUT    = CY_SAR_ID | CY_PDL_STATUS_ERROR | 0x02UL,    /**< A timeout occurred */
    CY_SAR_CONVERSION_NOT_COMPLETE = CY_SAR_ID | CY_PDL_STATUS_ERROR | 0x03UL, /**< SAR conversion is not complete */
} cy_en_sar_status_t;

/** Definitions for starting a conversion used in \ref Cy_SAR_StartConvert */
typedef enum
{
    CY_SAR_START_CONVERT_SINGLE_SHOT = 0UL, /**< Start a single scan (one shot) from firmware */
    CY_SAR_START_CONVERT_CONTINUOUS  = 1UL, /**< Continuously scan enabled channels and ignores all triggers, firmware or hardware */
} cy_en_sar_start_convert_sel_t;

/** Definitions for the return mode used in \ref Cy_SAR_IsEndConversion */
typedef enum
{
    CY_SAR_RETURN_STATUS       = 0UL,    /**< Immediately returns the conversion status. */
    CY_SAR_WAIT_FOR_RESULT     = 1UL,    /**< Does not return a result until the conversion of all sequential channels is complete. This mode is blocking. */
    CY_SAR_RETURN_STATUS_INJ   = 2UL,    /**< Immediately returns the conversion status of the injection channel. */
    CY_SAR_WAIT_FOR_RESULT_INJ = 3UL,    /**< Does not return a result until the conversion of injection channels is complete. This mode is blocking. */
} cy_en_sar_return_mode_t;

/** Switch state definitions */
typedef enum
{
    CY_SAR_SWITCH_OPEN      = 0UL,    /**< Open the switch */
    CY_SAR_SWITCH_CLOSE     = 1UL     /**< Close the switch */
} cy_en_sar_switch_state_t;

/** Definitions for sequencer control of switches */
typedef enum
{
    CY_SAR_SWITCH_SEQ_CTRL_DISABLE = 0UL, /**< Disable sequencer control of switch */
    CY_SAR_SWITCH_SEQ_CTRL_ENABLE  = 1UL  /**< Enable sequencer control of switch */
} cy_en_sar_switch_sar_seq_ctrl_t;

/** Switch register selection for \ref Cy_SAR_SetAnalogSwitch and \ref Cy_SAR_GetAnalogSwitch */
typedef enum
{
    CY_SAR_MUX_SWITCH0  = 0UL,      /**< SARMUX switch control register */
} cy_en_sar_switch_register_sel_t;

/** \addtogroup group_sar_ctrl_register_enums
* This set of enumerations aids in configuring the SAR CTRL register
* \{
*/
/** Reference voltage buffer power mode definitions */
typedef enum
{
    CY_SAR_VREF_PWR_100     = 0UL << SAR_CTRL_PWR_CTRL_VREF_Pos,      /**< Full power (100%) */
    CY_SAR_VREF_PWR_80      = 1UL << SAR_CTRL_PWR_CTRL_VREF_Pos,      /**< 80% power */
    CY_SAR_VREF_PWR_60      = 2UL << SAR_CTRL_PWR_CTRL_VREF_Pos,      /**< 60% power */
    CY_SAR_VREF_PWR_50      = 3UL << SAR_CTRL_PWR_CTRL_VREF_Pos,      /**< 50% power */
    CY_SAR_VREF_PWR_40      = 4UL << SAR_CTRL_PWR_CTRL_VREF_Pos,      /**< 40% power */
    CY_SAR_VREF_PWR_30      = 5UL << SAR_CTRL_PWR_CTRL_VREF_Pos,      /**< 30% power */
    CY_SAR_VREF_PWR_20      = 6UL << SAR_CTRL_PWR_CTRL_VREF_Pos,      /**< 20% power */
    CY_SAR_VREF_PWR_10      = 7UL << SAR_CTRL_PWR_CTRL_VREF_Pos,      /**< 10% power */
} cy_en_sar_ctrl_pwr_ctrl_vref_t;

/** Reference voltage selection definitions */
typedef enum
{
    CY_SAR_VREF_SEL_BGR         = 4UL << SAR_CTRL_VREF_SEL_Pos,     /**< System wide bandgap from \ref group_sysanalog "AREF" (Vref buffer on) */
    CY_SAR_VREF_SEL_EXT         = 5UL << SAR_CTRL_VREF_SEL_Pos,     /**< External Vref direct from a pin */
    CY_SAR_VREF_SEL_VDDA_DIV_2  = 6UL << SAR_CTRL_VREF_SEL_Pos,     /**< Vdda/2 (Vref buffer on) */
    CY_SAR_VREF_SEL_VDDA        = 7UL << SAR_CTRL_VREF_SEL_Pos      /**< Vdda */
} cy_en_sar_ctrl_vref_sel_t;

/** Vref bypass cap enable.
* When enabled, a bypass capacitor should
* be connected to the dedicated Vref pin of the device.
* Refer to the device datasheet for the minimum bypass capacitor value to use.
*/
typedef enum
{
    CY_SAR_BYPASS_CAP_DISABLE = 0UL << SAR_CTRL_VREF_BYP_CAP_EN_Pos,    /**< Disable Vref bypass cap */
    CY_SAR_BYPASS_CAP_ENABLE  = 1UL << SAR_CTRL_VREF_BYP_CAP_EN_Pos     /**< Enable Vref bypass cap */
} cy_en_sar_ctrl_bypass_cap_t;

/** Negative terminal (Vminus) selection definitions for single-ended channels.
*
* The Vminus input for single ended channels can be connected to
* Vref, VSSA, or routed out to an external pin.
* The options for routing to a pin are through Pin 1, Pin 3, Pin 5, or Pin 7
* of the SARMUX dedicated port or an acore wire in AROUTE, if available on the device.
*
* \ref CY_SAR_NEG_SEL_VSSA_KELVIN comes straight from a Vssa pad without any shared branches
* so as to keep quiet and avoid voltage drops.
*/
typedef enum
{
    CY_SAR_NEG_SEL_VSSA_KELVIN  = 0UL << SAR_CTRL_NEG_SEL_Pos,  /**< Connect Vminus to VSSA_KELVIN */
    CY_SAR_NEG_SEL_P1           = 2UL << SAR_CTRL_NEG_SEL_Pos,  /**< Connect Vminus to Pin 1 of SARMUX dedicated port */
    CY_SAR_NEG_SEL_P3           = 3UL << SAR_CTRL_NEG_SEL_Pos,  /**< Connect Vminus to Pin 3 of SARMUX dedicated port */
    CY_SAR_NEG_SEL_P5           = 4UL << SAR_CTRL_NEG_SEL_Pos,  /**< Connect Vminus to Pin 5 of SARMUX dedicated port */
    CY_SAR_NEG_SEL_P7           = 5UL << SAR_CTRL_NEG_SEL_Pos,  /**< Connect Vminus to Pin 6 of SARMUX dedicated port */
    CY_SAR_NEG_SEL_ACORE        = 6UL << SAR_CTRL_NEG_SEL_Pos,  /**< Connect Vminus to an ACORE in AROUTE */
    CY_SAR_NEG_SEL_VREF         = 7UL << SAR_CTRL_NEG_SEL_Pos,  /**< Connect Vminus to VREF input of SARADC */
} cy_en_sar_ctrl_neg_sel_t;

/** Enable hardware control of the switch between Vref and the Vminus input */
typedef enum
{
    CY_SAR_CTRL_NEGVREF_FW_ONLY = 0UL << SAR_CTRL_SAR_HW_CTRL_NEGVREF_Pos,    /**< Only firmware control of the switch */
    CY_SAR_CTRL_NEGVREF_HW      = 1UL << SAR_CTRL_SAR_HW_CTRL_NEGVREF_Pos     /**< Enable hardware control of the switch */
} cy_en_sar_ctrl_hw_ctrl_negvref_t;

/** Configure the comparator latch delay */
typedef enum
{
    CY_SAR_CTRL_COMP_DLY_2P5    = 0UL << SAR_CTRL_COMP_DLY_Pos,    /**< 2.5 ns delay, use for SAR conversion rate up to 2.5 Msps */
    CY_SAR_CTRL_COMP_DLY_4      = 1UL << SAR_CTRL_COMP_DLY_Pos,    /**< 4 ns delay, use for SAR conversion rate up to 2.0 Msps */
    CY_SAR_CTRL_COMP_DLY_10     = 2UL << SAR_CTRL_COMP_DLY_Pos,    /**< 10 ns delay, use for SAR conversion rate up to 1.5 Msps */
    CY_SAR_CTRL_COMP_DLY_12     = 3UL << SAR_CTRL_COMP_DLY_Pos     /**< 12 ns delay, use for SAR conversion rate up to 1 Msps */
} cy_en_sar_ctrl_comp_delay_t;

/** Configure the comparator power mode */
typedef enum
{
    CY_SAR_COMP_PWR_100     = 0UL << SAR_CTRL_COMP_PWR_Pos,      /**< 100% power, use this for > 2 Msps */
    CY_SAR_COMP_PWR_80      = 1UL << SAR_CTRL_COMP_PWR_Pos,      /**< 80% power, use this for 1.5 - 2 Msps */
    CY_SAR_COMP_PWR_60      = 2UL << SAR_CTRL_COMP_PWR_Pos,      /**< 60% power, use this for 1.0 - 1.5 Msps */
    CY_SAR_COMP_PWR_50      = 3UL << SAR_CTRL_COMP_PWR_Pos,      /**< 50% power, use this for 500 ksps - 1 Msps */
    CY_SAR_COMP_PWR_40      = 4UL << SAR_CTRL_COMP_PWR_Pos,      /**< 40% power, use this for 250 - 500 ksps */
    CY_SAR_COMP_PWR_30      = 5UL << SAR_CTRL_COMP_PWR_Pos,      /**< 30% power, use this for 100 - 250 ksps */
    CY_SAR_COMP_PWR_20      = 6UL << SAR_CTRL_COMP_PWR_Pos,      /**< 20% power, use this for TDB sps */
    CY_SAR_COMP_PWR_10      = 7UL << SAR_CTRL_COMP_PWR_Pos,      /**< 10% power, use this for < 100 ksps */
} cy_en_sar_ctrl_comp_pwr_t;

/** Enable or disable the SARMUX during Deep Sleep power mode. */
typedef enum
{
    CY_SAR_DEEPSLEEP_SARMUX_OFF = 0UL << SAR_CTRL_DEEPSLEEP_ON_Pos,    /**< Disable SARMUX operation during Deep Sleep */
    CY_SAR_DEEPSLEEP_SARMUX_ON  = 1UL << SAR_CTRL_DEEPSLEEP_ON_Pos     /**< Enable SARMUX operation during Deep Sleep */
} cy_en_sar_ctrl_sarmux_deep_sleep_t;

/** Enable or disable the SARSEQ control of routing switches */
typedef enum
{
    CY_SAR_SARSEQ_SWITCH_ENABLE    = 0UL << SAR_CTRL_SWITCH_DISABLE_Pos,    /**< Enable the SARSEQ to change the routing switches defined in the channel configurations */
    CY_SAR_SARSEQ_SWITCH_DISABLE   = 1UL << SAR_CTRL_SWITCH_DISABLE_Pos     /**< Disable the SARSEQ. It is up to the firmware to set the routing switches */
} cy_en_sar_ctrl_sarseq_routing_switches_t;

/* \} */

/** \addtogroup group_sar_sample_ctrl_register_enums
* This set of enumerations are used in configuring the SAR SAMPLE_CTRL register
* \{
*/
/** Configure result alignment, either left or right aligned.
*
* \note
* Averaging always uses right alignment. If the \ref CY_SAR_LEFT_ALIGN
* is selected with averaging enabled, it is ignored.
*
* \note
* The voltage conversion functions (\ref Cy_SAR_CountsTo_Volts, \ref Cy_SAR_CountsTo_mVolts,
* \ref Cy_SAR_CountsTo_uVolts) are only valid for right alignment.
* */
typedef enum
{
    CY_SAR_RIGHT_ALIGN  = 0UL << SAR_SAMPLE_CTRL_LEFT_ALIGN_Pos,    /**< Right align result data to bits [11:0] with sign extension to 16 bits if channel is signed */
    CY_SAR_LEFT_ALIGN   = 1UL << SAR_SAMPLE_CTRL_LEFT_ALIGN_Pos     /**< Left align result data to bits [15:4] */
} cy_en_sar_sample_ctrl_result_align_t;

/** Configure format, signed or unsigned, of single-ended channels */
typedef enum
{
    CY_SAR_SINGLE_ENDED_UNSIGNED  = 0UL << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos,    /**< Result data for single-ended channels is unsigned */
    CY_SAR_SINGLE_ENDED_SIGNED    = 1UL << SAR_SAMPLE_CTRL_SINGLE_ENDED_SIGNED_Pos     /**< Result data for single-ended channels is signed */
} cy_en_sar_sample_ctrl_single_ended_format_t;

/** Configure format, signed or unsigned, of differential channels */
typedef enum
{
    CY_SAR_DIFFERENTIAL_UNSIGNED  = 0UL << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos,    /**< Result data for differential channels is unsigned */
    CY_SAR_DIFFERENTIAL_SIGNED    = 1UL << SAR_SAMPLE_CTRL_DIFFERENTIAL_SIGNED_Pos     /**< Result data for differential channels is signed */
} cy_en_sar_sample_ctrl_differential_format_t;

/** Configure number of samples for averaging.
* This applies only to channels with averaging enabled.
*/
typedef enum
{
    CY_SAR_AVG_CNT_2          = 0UL << SAR_SAMPLE_CTRL_AVG_CNT_Pos,    /**< Set samples averaged to 2 */
    CY_SAR_AVG_CNT_4          = 1UL << SAR_SAMPLE_CTRL_AVG_CNT_Pos,    /**< Set samples averaged to 4 */
    CY_SAR_AVG_CNT_8          = 2UL << SAR_SAMPLE_CTRL_AVG_CNT_Pos,    /**< Set samples averaged to 8 */
    CY_SAR_AVG_CNT_16         = 3UL << SAR_SAMPLE_CTRL_AVG_CNT_Pos,    /**< Set samples averaged to 16 */
    CY_SAR_AVG_CNT_32         = 4UL << SAR_SAMPLE_CTRL_AVG_CNT_Pos,    /**< Set samples averaged to 32 */
    CY_SAR_AVG_CNT_64         = 5UL << SAR_SAMPLE_CTRL_AVG_CNT_Pos,    /**< Set samples averaged to 64 */
    CY_SAR_AVG_CNT_128        = 6UL << SAR_SAMPLE_CTRL_AVG_CNT_Pos,    /**< Set samples averaged to 128 */
    CY_SAR_AVG_CNT_256        = 7UL << SAR_SAMPLE_CTRL_AVG_CNT_Pos     /**< Set samples averaged to 256 */
} cy_en_sar_sample_ctrl_avg_cnt_t;

/** Configure the averaging mode.
*
* - Sequential accumulate and dump: a channel will be sampled back to back.
*   The result is added to a running sum in a 20-bit register. At the end
*   of the scan, the accumulated value is shifted right to fit into 16 bits
*   and stored into the CHAN_RESULT register.
* - Sequential fixed:  a channel will be sampled back to back.
*   The result is added to a running sum in a 20-bit register. At the end
*   of the scan, the accumulated value is shifted right to fit into 12 bits
*   and stored into the CHAN_RESULT register.
* - Interleaved: a channel will be sampled once per scan.
*   The result is added to a running sum in a 16-bit register.
*   In the scan where the final averaging count is reached,
*   the accumulated value is shifted right to fit into 12 bits
*   and stored into the CHAN_RESULT register.
*   In all other scans, the CHAN_RESULT will have an invalid result.
*   In interleaved mode, make sure that the averaging
*   count is low enough to ensure that the intermediate value does not exceed 16 bits,
*   that is averaging count is 16 or less. Otherwise, the MSBs will be lost.
*   In the special case that averaging is enabled for all enabled channels
*   and interleaved mode is used, the interrupt frequency
*   will be reduced by a factor of the number of samples averaged.
*/
typedef enum
{
    CY_SAR_AVG_MODE_SEQUENTIAL_ACCUM    = 0UL,                               /**< Set mode to sequential accumulate and dump */
    CY_SAR_AVG_MODE_SEQUENTIAL_FIXED    = SAR_SAMPLE_CTRL_AVG_SHIFT_Msk,     /**< Set mode to sequential 12-bit fixed */
    CY_SAR_AVG_MODE_INTERLEAVED         = SAR_SAMPLE_CTRL_AVG_MODE_Msk,      /**< Set mode to interleaved. Number of samples per scan must be 16 or less. */
} cy_en_sar_sample_ctrl_avg_mode_t;

/** Configure the trigger mode.
*
* Firmware triggering is always enabled and can be single shot or continuous.
* Additionally, hardware triggering can be enabled with the option to be
* edge or level sensitive.
*/
typedef enum
{
    CY_SAR_TRIGGER_MODE_FW_ONLY        = 0UL,                                /**< Firmware trigger only, disable hardware trigger*/
    CY_SAR_TRIGGER_MODE_FW_AND_HWEDGE  = SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Msk, /**< Enable edge sensitive hardware trigger. Each rising edge will trigger a single scan. */
    CY_SAR_TRIGGER_MODE_FW_AND_HWLEVEL = SAR_SAMPLE_CTRL_DSI_TRIGGER_EN_Msk | SAR_SAMPLE_CTRL_DSI_TRIGGER_LEVEL_Msk, /**< Enable level sensitive hardware trigger. The SAR will continuously scan while the trigger signal is high. */
} cy_en_sar_sample_ctrl_trigger_mode_t;

/* \} */

/** \addtogroup group_sar_sample_time_shift_enums
* This set of enumerations aids in configuring the SAR SAMPLE_TIME* registers
* \{
*/
/** Configure the sample time by using these shifts */
typedef enum
{
    CY_SAR_SAMPLE_TIME0_SHIFT       = SAR_SAMPLE_TIME01_SAMPLE_TIME0_Pos,             /**< Shift for sample time 0 */
    CY_SAR_SAMPLE_TIME1_SHIFT       = SAR_SAMPLE_TIME01_SAMPLE_TIME1_Pos,             /**< Shift for sample time 1 */
    CY_SAR_SAMPLE_TIME2_SHIFT       = SAR_SAMPLE_TIME23_SAMPLE_TIME2_Pos,             /**< Shift for sample time 2 */
    CY_SAR_SAMPLE_TIME3_SHIFT       = SAR_SAMPLE_TIME23_SAMPLE_TIME3_Pos,             /**< Shift for sample time 3 */
} cy_en_sar_sample_time_shift_t;
/* \} */

/** \addtogroup group_sar_range_thres_register_enums
* This set of enumerations aids in configuring the SAR RANGE* registers
* \{
*/
/** Configure the lower and upper thresholds for range detection
*
* The SARSEQ supports range detection to allow for automatic detection of sample
* values compared to two programmable thresholds without CPU involvement.
* Range detection is defined by two global thresholds and a condition.
* The RANGE_LOW value defines the lower threshold and RANGE_HIGH defines
* the upper threshold of the range.
*
* Range detect is done after averaging, alignment, and sign extension (if applicable).
* In other words, the thresholds values must have the same data format as the result data.
* Range detection is always done for all channels scanned. By making RANGE_INTR_MASK=0,
* the firmware can choose to ignore the range detect interrupt for any channel.
*/
typedef enum
{
    CY_SAR_RANGE_LOW_SHIFT      = SAR_RANGE_THRES_RANGE_LOW_Pos,        /**< Shift for setting lower limit of range detection */
    CY_SAR_RANGE_HIGH_SHIFT     = SAR_RANGE_THRES_RANGE_HIGH_Pos,       /**< Shift for setting upper limit of range detection */
} cy_en_sar_range_thres_shift_t;

/** Configure the condition (below, inside, above, or outside) of the range detection interrupt */
typedef enum
{
    CY_SAR_RANGE_COND_BELOW     = 0UL,  /**< Range interrupt detected when result < RANGE_LOW */
    CY_SAR_RANGE_COND_INSIDE    = 1UL,  /**< Range interrupt detected when RANGE_LOW <= result < RANGE_HIGH */
    CY_SAR_RANGE_COND_ABOVE     = 2UL,  /**< Range interrupt detected when RANGE_HIGH <= result */
    CY_SAR_RANGE_COND_OUTSIDE   = 3UL,  /**< Range interrupt detected when result < RANGE_LOW || RANGE_HIGH <= result */
} cy_en_sar_range_detect_condition_t;
/* \} */

/** \addtogroup group_sar_chan_config_register_enums
* This set of enumerations aids in configuring the SAR CHAN_CONFIG register
* \{
*/
/** Configure the input mode of the channel
*
* - Single ended channel: the \ref cy_en_sar_ctrl_neg_sel_t selection in the \ref group_sar_init_struct_ctrl register
*   determines what drives the Vminus pin
* - Differential paired: Vplus and Vminus are a pair. Bit 0 of \ref cy_en_sar_chan_config_pos_pin_addr_t "POS_PIN_ADDR"
*   is ignored and considered to be 0.
*   In other words, \ref cy_en_sar_chan_config_pos_pin_addr_t "POS_PIN_ADDR" points to the even pin of a pin pair.
*   The even pin is connected to Vplus and the odd pin is connected to Vminus.
*   \ref cy_en_sar_chan_config_pos_port_addr_t "POS_PORT_ADDR" is used to identify the port that contains the pins.
* - Differential unpaired: The \ref cy_en_sar_chan_config_neg_pin_addr_t "NEG_PIN_ADDR" and
*   \ref cy_en_sar_chan_config_neg_port_addr_t "NEG_PORT_ADDR" determine what drives the Vminus pin.
*   This is a variation of differential mode with no even-odd pair limitation
*/
typedef enum
{
    CY_SAR_CHAN_SINGLE_ENDED            = 0UL,                                     /**< Single ended channel */
    CY_SAR_CHAN_DIFFERENTIAL_PAIRED     = SAR_CHAN_CONFIG_DIFFERENTIAL_EN_Msk,     /**< Differential with even-odd pair limitation */
    CY_SAR_CHAN_DIFFERENTIAL_UNPAIRED   = SAR_CHAN_CONFIG_NEG_ADDR_EN_Msk          /**< Differential with no even-odd pair limitation */
} cy_en_sar_chan_config_input_mode_t;

/** Configure address of the pin connected to the Vplus terminal of the SARADC. */
typedef enum
{
    CY_SAR_CHAN_POS_PIN_ADDR_0     = 0UL,                                            /**< Pin 0 on port specified in \ref cy_en_sar_chan_config_pos_port_addr_t */
    CY_SAR_CHAN_POS_PIN_ADDR_1     = 1UL << SAR_CHAN_CONFIG_POS_PIN_ADDR_Pos,        /**< Pin 1 on port specified in \ref cy_en_sar_chan_config_pos_port_addr_t */
    CY_SAR_CHAN_POS_PIN_ADDR_2     = 2UL << SAR_CHAN_CONFIG_POS_PIN_ADDR_Pos,        /**< Pin 2 on port specified in \ref cy_en_sar_chan_config_pos_port_addr_t */
    CY_SAR_CHAN_POS_PIN_ADDR_3     = 3UL << SAR_CHAN_CONFIG_POS_PIN_ADDR_Pos,        /**< Pin 3 on port specified in \ref cy_en_sar_chan_config_pos_port_addr_t */
    CY_SAR_CHAN_POS_PIN_ADDR_4     = 4UL << SAR_CHAN_CONFIG_POS_PIN_ADDR_Pos,        /**< Pin 4 on port specified in \ref cy_en_sar_chan_config_pos_port_addr_t */
    CY_SAR_CHAN_POS_PIN_ADDR_5     = 5UL << SAR_CHAN_CONFIG_POS_PIN_ADDR_Pos,        /**< Pin 5 on port specified in \ref cy_en_sar_chan_config_pos_port_addr_t */
    CY_SAR_CHAN_POS_PIN_ADDR_6     = 6UL << SAR_CHAN_CONFIG_POS_PIN_ADDR_Pos,        /**< Pin 6 on port specified in \ref cy_en_sar_chan_config_pos_port_addr_t */
    CY_SAR_CHAN_POS_PIN_ADDR_7     = 7UL << SAR_CHAN_CONFIG_POS_PIN_ADDR_Pos,        /**< Pin 7 on port specified in \ref cy_en_sar_chan_config_pos_port_addr_t */
} cy_en_sar_chan_config_pos_pin_addr_t;

/** Configure address of the port that contains the pin connected to the Vplus terminal of the SARADC
*
* - \ref CY_SAR_POS_PORT_ADDR_SARMUX is for the dedicated SARMUX port (8 pins)
* - Port 1 through 4 are respectively the pins of CTB0, CTB1, CTB2, and CTB3 (if present)
* - Port 7, 5, and 6 (VPORT0/1/2) are the groups of internal signals that can be selected
*   in the SARMUX or AROUTE (if present).
*
* See the \ref group_sar_sarmux section for more guidance.
*/
typedef enum
{
    CY_SAR_POS_PORT_ADDR_SARMUX         = 0UL,                                       /**< Dedicated SARMUX port with 8 possible pins */
    CY_SAR_POS_PORT_ADDR_CTB0           = 1UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< Outputs from CTB0, if present */
    CY_SAR_POS_PORT_ADDR_CTB1           = 2UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< Outputs from CTB1, if present */
    CY_SAR_POS_PORT_ADDR_CTB2           = 3UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< Outputs from CTB2, if present */
    CY_SAR_POS_PORT_ADDR_CTB3           = 4UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< Outputs from CTB3, if present */
    CY_SAR_POS_PORT_ADDR_AROUTE_VIRT2   = 5UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< AROUTE virtual port (VPORT2), if present */
    CY_SAR_POS_PORT_ADDR_AROUTE_VIRT1   = 6UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< AROUTE virtual port (VPORT1), if present */
    CY_SAR_POS_PORT_ADDR_SARMUX_VIRT    = 7UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< SARMUX virtual port for DieTemp and AMUXBUSA/B */
} cy_en_sar_chan_config_pos_port_addr_t;

/** Enable or disable averaging for the channel */
typedef enum
{
    CY_SAR_CHAN_AVG_DISABLE      = 0UL,                                 /**< Disable averaging for the channel */
    CY_SAR_CHAN_AVG_ENABLE       = 1UL << SAR_CHAN_CONFIG_AVG_EN_Pos    /**< Enable averaging for the channel */
} cy_en_sar_chan_config_avg_en_t;

/** Select which sample time to use for the channel.
* There are four global samples times available set by \ref group_sar_init_struct_sampleTime01 and
* \ref group_sar_init_struct_sampleTime23.
*/
typedef enum
{
    CY_SAR_CHAN_SAMPLE_TIME_0     = 0UL,                                          /**< Use sample time 0 for the channel */
    CY_SAR_CHAN_SAMPLE_TIME_1     = 1UL << SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Pos,   /**< Use sample time 1 for the channel */
    CY_SAR_CHAN_SAMPLE_TIME_2     = 2UL << SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Pos,   /**< Use sample time 2 for the channel */
    CY_SAR_CHAN_SAMPLE_TIME_3     = 3UL << SAR_CHAN_CONFIG_SAMPLE_TIME_SEL_Pos,   /**< Use sample time 3 for the channel */
} cy_en_sar_chan_config_sample_time_t;

/** Configure address of the pin connected to the Vminus terminal of the SARADC. */
typedef enum
{
    CY_SAR_CHAN_NEG_PIN_ADDR_0     = 0UL,                                            /**< Pin 0 on port specified in \ref cy_en_sar_chan_config_neg_port_addr_t */
    CY_SAR_CHAN_NEG_PIN_ADDR_1     = 1UL << SAR_CHAN_CONFIG_NEG_PIN_ADDR_Pos,        /**< Pin 1 on port specified in \ref cy_en_sar_chan_config_neg_port_addr_t */
    CY_SAR_CHAN_NEG_PIN_ADDR_2     = 2UL << SAR_CHAN_CONFIG_NEG_PIN_ADDR_Pos,        /**< Pin 2 on port specified in \ref cy_en_sar_chan_config_neg_port_addr_t */
    CY_SAR_CHAN_NEG_PIN_ADDR_3     = 3UL << SAR_CHAN_CONFIG_NEG_PIN_ADDR_Pos,        /**< Pin 3 on port specified in \ref cy_en_sar_chan_config_neg_port_addr_t */
    CY_SAR_CHAN_NEG_PIN_ADDR_4     = 4UL << SAR_CHAN_CONFIG_NEG_PIN_ADDR_Pos,        /**< Pin 4 on port specified in \ref cy_en_sar_chan_config_neg_port_addr_t */
    CY_SAR_CHAN_NEG_PIN_ADDR_5     = 5UL << SAR_CHAN_CONFIG_NEG_PIN_ADDR_Pos,        /**< Pin 5 on port specified in \ref cy_en_sar_chan_config_neg_port_addr_t */
    CY_SAR_CHAN_NEG_PIN_ADDR_6     = 6UL << SAR_CHAN_CONFIG_NEG_PIN_ADDR_Pos,        /**< Pin 6 on port specified in \ref cy_en_sar_chan_config_neg_port_addr_t */
    CY_SAR_CHAN_NEG_PIN_ADDR_7     = 7UL << SAR_CHAN_CONFIG_NEG_PIN_ADDR_Pos,        /**< Pin 7 on port specified in \ref cy_en_sar_chan_config_neg_port_addr_t */
} cy_en_sar_chan_config_neg_pin_addr_t;

/** Configure address of the port that contains the pin connected to the Vminus terminal of the SARADC.
*
* - Port 0 is 8 pins of the SARMUX
* - Port 7, 5, and 6 (VPORT0/1/2) are the groups of internal signals that can be selected
*   in the SARMUX or AROUTE (if present).
*/
typedef enum
{
    CY_SAR_NEG_PORT_ADDR_SARMUX         = 0UL,                                       /**< Dedicated SARMUX port with 8 possible pins */
    CY_SAR_NEG_PORT_ADDR_AROUTE_VIRT2   = 5UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< AROUTE virtual port (VPORT2), if present */
    CY_SAR_NEG_PORT_ADDR_AROUTE_VIRT1   = 6UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< AROUTE virtual port (VPORT1), if present */
    CY_SAR_NEG_PORT_ADDR_SARMUX_VIRT    = 7UL << SAR_CHAN_CONFIG_POS_PORT_ADDR_Pos,  /**< SARMUX virtual port for AMUXBUSA/B */
} cy_en_sar_chan_config_neg_port_addr_t;


/** Configure address of the port that contains the pin connected to the Vplus terminal of the injection channel
*
* - \ref CY_SAR_INJ_PORT_ADDR_SARMUX is for the dedicated SARMUX port (8 pins)
* - Ports 1 through 4 are respectively the pins of CTB0, CTB1, CTB2, and CTB3 (if present)
* - Ports 7 and 6 are the groups of internal signals that can be selected
*   in the SARMUX or AROUTE (if present).
*
* See the \ref group_sar_sarmux section for more guidance.
*/
typedef enum
{
    CY_SAR_INJ_PORT_ADDR_SARMUX         = 0UL,                                           /**< Dedicated SARMUX port with 8 possible pins */
    CY_SAR_INJ_PORT_ADDR_CTB0           = 1UL << SAR_INJ_CHAN_CONFIG_INJ_PORT_ADDR_Pos,  /**< Outputs from CTB0, if present */
    CY_SAR_INJ_PORT_ADDR_CTB1           = 2UL << SAR_INJ_CHAN_CONFIG_INJ_PORT_ADDR_Pos,  /**< Outputs from CTB1, if present */
    CY_SAR_INJ_PORT_ADDR_CTB2           = 3UL << SAR_INJ_CHAN_CONFIG_INJ_PORT_ADDR_Pos,  /**< Outputs from CTB2, if present */
    CY_SAR_INJ_PORT_ADDR_CTB3           = 4UL << SAR_INJ_CHAN_CONFIG_INJ_PORT_ADDR_Pos,  /**< Outputs from CTB3, if present */
    CY_SAR_INJ_PORT_ADDR_AROUTE_VIRT    = 6UL << SAR_INJ_CHAN_CONFIG_INJ_PORT_ADDR_Pos,  /**< AROUTE virtual port (VPORT), if present */
    CY_SAR_INJ_PORT_ADDR_SARMUX_VIRT    = 7UL << SAR_INJ_CHAN_CONFIG_INJ_PORT_ADDR_Pos,  /**< SARMUX virtual port for DieTemp and AMUXBUSA/B */
} cy_en_sar_inj_chan_config_port_addr_t;


/* \} */

/** \cond left here for BWC, deprecated for new designs */
typedef enum
{
    CY_SAR_INTR_MASK_NONE           = 0UL,
    CY_SAR_INTR_EOS_MASK            = SAR_INTR_MASK_EOS_MASK_Msk,
    CY_SAR_INTR_OVERFLOW_MASK       = SAR_INTR_MASK_OVERFLOW_MASK_Msk,
    CY_SAR_INTR_FW_COLLISION_MASK   = SAR_INTR_MASK_FW_COLLISION_MASK_Msk,
} cy_en_sar_intr_mask_t;
/* \endcond */


/** \addtogroup group_sar_mux_switch_register_enums
* This set of enumerations aids in configuring the \ref group_sar_init_struct_muxSwitch and \ref group_sar_init_struct_muxSwitchSqCtrl registers
* \{
*/

/** Firmware control for the SARMUX switches to connect analog signals to the SAR ADC
*
* To close multiple switches, "OR" the enum values together.
*
* See the \ref group_sar_sarmux section for more guidance.
*/
typedef enum
{
    /* SARMUX pins to Vplus */
    CY_SAR_MUX_FW_P0_VPLUS         = SAR_MUX_SWITCH0_MUX_FW_P0_VPLUS_Msk,    /**< Switch between Pin 0 of SARMUX and Vplus of SARADC */
    CY_SAR_MUX_FW_P1_VPLUS         = SAR_MUX_SWITCH0_MUX_FW_P1_VPLUS_Msk,    /**< Switch between Pin 1 of SARMUX and Vplus of SARADC */
    CY_SAR_MUX_FW_P2_VPLUS         = SAR_MUX_SWITCH0_MUX_FW_P2_VPLUS_Msk,    /**< Switch between Pin 2 of SARMUX and Vplus of SARADC */
    CY_SAR_MUX_FW_P3_VPLUS         = SAR_MUX_SWITCH0_MUX_FW_P3_VPLUS_Msk,    /**< Switch between Pin 3 of SARMUX and Vplus of SARADC */
    CY_SAR_MUX_FW_P4_VPLUS         = SAR_MUX_SWITCH0_MUX_FW_P4_VPLUS_Msk,    /**< Switch between Pin 4 of SARMUX and Vplus of SARADC */
    CY_SAR_MUX_FW_P5_VPLUS         = SAR_MUX_SWITCH0_MUX_FW_P5_VPLUS_Msk,    /**< Switch between Pin 5 of SARMUX and Vplus of SARADC */
    CY_SAR_MUX_FW_P6_VPLUS         = SAR_MUX_SWITCH0_MUX_FW_P6_VPLUS_Msk,    /**< Switch between Pin 6 of SARMUX and Vplus of SARADC */
    CY_SAR_MUX_FW_P7_VPLUS         = SAR_MUX_SWITCH0_MUX_FW_P7_VPLUS_Msk,    /**< Switch between Pin 7 of SARMUX and Vplus of SARADC */

    /* SARMUX pins to Vminus */
    CY_SAR_MUX_FW_P0_VMINUS        = SAR_MUX_SWITCH0_MUX_FW_P0_VMINUS_Msk,   /**< Switch between Pin 0 of SARMUX and Vminus of SARADC */
    CY_SAR_MUX_FW_P1_VMINUS        = SAR_MUX_SWITCH0_MUX_FW_P1_VMINUS_Msk,   /**< Switch between Pin 1 of SARMUX and Vminus of SARADC */
    CY_SAR_MUX_FW_P2_VMINUS        = SAR_MUX_SWITCH0_MUX_FW_P2_VMINUS_Msk,   /**< Switch between Pin 2 of SARMUX and Vminus of SARADC */
    CY_SAR_MUX_FW_P3_VMINUS        = SAR_MUX_SWITCH0_MUX_FW_P3_VMINUS_Msk,   /**< Switch between Pin 3 of SARMUX and Vminus of SARADC */
    CY_SAR_MUX_FW_P4_VMINUS        = SAR_MUX_SWITCH0_MUX_FW_P4_VMINUS_Msk,   /**< Switch between Pin 4 of SARMUX and Vminus of SARADC */
    CY_SAR_MUX_FW_P5_VMINUS        = SAR_MUX_SWITCH0_MUX_FW_P5_VMINUS_Msk,   /**< Switch between Pin 5 of SARMUX and Vminus of SARADC */
    CY_SAR_MUX_FW_P6_VMINUS        = SAR_MUX_SWITCH0_MUX_FW_P6_VMINUS_Msk,   /**< Switch between Pin 6 of SARMUX and Vminus of SARADC */
    CY_SAR_MUX_FW_P7_VMINUS        = SAR_MUX_SWITCH0_MUX_FW_P7_VMINUS_Msk,   /**< Switch between Pin 7 of SARMUX and Vminus of SARADC */

    /* Vssa to Vminus and temperature sensor to Vplus */
    CY_SAR_MUX_FW_VSSA_VMINUS      = SAR_MUX_SWITCH0_MUX_FW_VSSA_VMINUS_Msk,    /**< Switch between VSSA and Vminus of SARADC */
    CY_SAR_MUX_FW_TEMP_VPLUS       = SAR_MUX_SWITCH0_MUX_FW_TEMP_VPLUS_Msk,     /**< Switch between the DieTemp sensor and vplus of SARADC */

    /* Amuxbus A and B to Vplus and Vminus */
    CY_SAR_MUX_FW_AMUXBUSA_VPLUS   = SAR_MUX_SWITCH0_MUX_FW_AMUXBUSA_VPLUS_Msk,     /**< Switch between AMUXBUSA and vplus of SARADC */
    CY_SAR_MUX_FW_AMUXBUSB_VPLUS   = SAR_MUX_SWITCH0_MUX_FW_AMUXBUSB_VPLUS_Msk,     /**< Switch between AMUXBUSB and vplus of SARADC */
    CY_SAR_MUX_FW_AMUXBUSA_VMINUS  = SAR_MUX_SWITCH0_MUX_FW_AMUXBUSA_VMINUS_Msk,    /**< Switch between AMUXBUSA and vminus of SARADC */
    CY_SAR_MUX_FW_AMUXBUSB_VMINUS  = SAR_MUX_SWITCH0_MUX_FW_AMUXBUSB_VMINUS_Msk,    /**< Switch between AMUXBUSB and vminus of SARADC */

    /* Sarbus 0 and 1 to Vplus and Vminus */
    CY_SAR_MUX_FW_SARBUS0_VPLUS    = SAR_MUX_SWITCH0_MUX_FW_SARBUS0_VPLUS_Msk,      /**< Switch between SARBUS0 and vplus of SARADC */
    CY_SAR_MUX_FW_SARBUS1_VPLUS    = SAR_MUX_SWITCH0_MUX_FW_SARBUS1_VPLUS_Msk,      /**< Switch between SARBUS1 and vplus of SARADC */
    CY_SAR_MUX_FW_SARBUS0_VMINUS   = SAR_MUX_SWITCH0_MUX_FW_SARBUS0_VMINUS_Msk,     /**< Switch between SARBUS0 and vminus of SARADC */
    CY_SAR_MUX_FW_SARBUS1_VMINUS   = SAR_MUX_SWITCH0_MUX_FW_SARBUS1_VMINUS_Msk,     /**< Switch between SARBUS1 and vminus of SARADC */

    /* SARMUX pins to Core IO */
    CY_SAR_MUX_FW_P4_COREIO0       = SAR_MUX_SWITCH0_MUX_FW_P4_COREIO0_Msk,      /**< Switch between Pin 4 of SARMUX and coreio0, if present */
    CY_SAR_MUX_FW_P5_COREIO1       = SAR_MUX_SWITCH0_MUX_FW_P5_COREIO1_Msk,      /**< Switch between Pin 5 of SARMUX and coreio1, if present */
    CY_SAR_MUX_FW_P6_COREIO2       = SAR_MUX_SWITCH0_MUX_FW_P6_COREIO2_Msk,      /**< Switch between Pin 6 of SARMUX and coreio2, if present */
    CY_SAR_MUX_FW_P7_COREIO3       = SAR_MUX_SWITCH0_MUX_FW_P7_COREIO3_Msk,      /**< Switch between Pin 7 of SARMUX and coreio3, if present */
} cy_en_sar_mux_switch_fw_ctrl_t;

/** Mask definitions of SARMUX switches that can be controlled by the SARSEQ.
*
* To enable sequencer control of multiple switches, "OR" the enum values together.
*
* See the \ref group_sar_sarmux section for more guidance.
*/
typedef enum
{
    CY_SAR_MUX_SQ_CTRL_P0           = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P0_Msk,        /**< Enable SARSEQ control of Pin 0 switches (for Vplus and Vminus) of SARMUX dedicated port */
    CY_SAR_MUX_SQ_CTRL_P1           = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P1_Msk,        /**< Enable SARSEQ control of Pin 1 switches (for Vplus and Vminus) of SARMUX dedicated port */
    CY_SAR_MUX_SQ_CTRL_P2           = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P2_Msk,        /**< Enable SARSEQ control of Pin 2 switches (for Vplus and Vminus) of SARMUX dedicated port */
    CY_SAR_MUX_SQ_CTRL_P3           = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P3_Msk,        /**< Enable SARSEQ control of Pin 3 switches (for Vplus and Vminus) of SARMUX dedicated port */
    CY_SAR_MUX_SQ_CTRL_P4           = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P4_Msk,        /**< Enable SARSEQ control of Pin 4 switches (for Vplus and Vminus) of SARMUX dedicated port */
    CY_SAR_MUX_SQ_CTRL_P5           = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P5_Msk,        /**< Enable SARSEQ control of Pin 5 switches (for Vplus and Vminus) of SARMUX dedicated port */
    CY_SAR_MUX_SQ_CTRL_P6           = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P6_Msk,        /**< Enable SARSEQ control of Pin 6 switches (for Vplus and Vminus) of SARMUX dedicated port */
    CY_SAR_MUX_SQ_CTRL_P7           = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_P7_Msk,        /**< Enable SARSEQ control of Pin 7 switches (for Vplus and Vminus) of SARMUX dedicated port */
    CY_SAR_MUX_SQ_CTRL_VSSA         = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_VSSA_Msk,      /**< Enable SARSEQ control of the switch between VSSA and Vminus */
    CY_SAR_MUX_SQ_CTRL_TEMP         = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_TEMP_Msk,      /**< Enable SARSEQ control of the switch between DieTemp and Vplus */
    CY_SAR_MUX_SQ_CTRL_AMUXBUSA     = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_AMUXBUSA_Msk,  /**< Enable SARSEQ control of AMUXBUSA switches (for Vplus and Vminus) */
    CY_SAR_MUX_SQ_CTRL_AMUXBUSB     = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_AMUXBUSB_Msk,  /**< Enable SARSEQ control of AMUXBUSB switches (for Vplus and Vminus) */
    CY_SAR_MUX_SQ_CTRL_SARBUS0      = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_SARBUS0_Msk,   /**< Enable SARSEQ control of SARBUS0 switches (for Vplus and Vminus) */
    CY_SAR_MUX_SQ_CTRL_SARBUS1      = SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_SARBUS1_Msk,   /**< Enable SARSEQ control of SARBUS1 switches (for Vplus and Vminus) */
} cy_en_sar_mux_switch_sq_ctrl_t;

/* \} */


/** For PASS_V2 the SAR clock can come from:
*   - one of the CLK_PERI dividers
*   - PASS Deep Sleep Clock (CLK_DPSLP)
*/
typedef enum
{
    CY_SAR_CLK_PERI       = 0UL,    /**< SAR clock source is one of \ref group_sysclk "PERI" dividers (SAR is only operational in chip ACTIVE mode) */
    CY_SAR_CLK_DEEPSLEEP  = 1UL     /**< SAR clock source is \ref group_sysanalog_dpslp "CLK_DPSLP" (SAR can be operational in both chip ACTIVE and DEEPSLEEP modes) */
} cy_en_sar_clock_source_t;

/** Definitions for simultaneous scan trigger signal event selection */
typedef enum
{
    CY_SAR_SIMULT_TRIG_EVENT_EDGE   = 0UL, /**< Positive edge detected on the trigger signal triggers a new scan */
    CY_SAR_SIMULT_TRIG_EVENT_LEVEL  = 1UL, /**< SAR will do continuous scans as long as the trigger signal remains high */
} cy_en_sar_simult_trig_event_sel_t;

/** Definitions for simultaneous scan trigger synchronization */
typedef enum
{
    CY_SAR_SIMULT_TRIG_SYNC_NONE      = 0UL, /**< Bypass clock domain synchronization of the simultaneous trigger signal */
    CY_SAR_SIMULT_TRIG_SYNC_SAR_CLOCK = 1UL, /**< Synchronize the simultaneous trigger signal to the SAR clock domain */
} cy_en_sar_simult_trig_sync_sel_t;

/** Definitions for simultaneous scan sampling mode */
typedef enum
{
    CY_SAR_SIMULT_TRIG_SAMPLE_SINGLE     = 0UL, /**< Perform single scan on the trigger event */
    CY_SAR_SIMULT_TRIG_SAMPLE_SCAN_CNT   = 1UL, /**< On the trigger event perform number of scans, specified by scanCount */
} cy_en_sar_simult_trig_sample_sel_t;

/** Definitions for simultaneous scan interrupt generation */
typedef enum
{
    CY_SAR_SIMULT_TRIG_INTR_EOS       = 0UL, /**< Generate interrupt on each End of Sample event */
    CY_SAR_SIMULT_TRIG_INTR_SCAN_CNT  = 1UL, /**< Generate interrupt on End of Sample event only when sample number = scanCount */
}cy_en_sar_simult_trig_intr_sel_t;

/** \} group_sar_enums */

/** \addtogroup group_sar_data_structures
* \{
*/

/***************************************
*       Configuration Structures
***************************************/

/** FIFO configuration structure **/
typedef struct
{
    bool chanId;                                        /**< Enable the channel ID in the results */
    bool chainToNext;                                   /**< Chain the FIFO to the next FIFO */
    bool clrTrIntrOnRead;                               /**< Enable the FIFO level trigger (and optional level interrupt) clearing on FIFO read */
    uint32_t level;                                     /**< A trigger (and optional interrupt) event occurs when the number of FIFO entries overcomes the Level setting. Range: 1..256 */
    bool trOut;                                         /**< SAR output trigger is set by the 'level' condition */
} cy_stc_sar_fifo_config_t;


/** This structure is used to initialize the SAR ADC subsystem.
*
* The SAR ADC subsystem is highly configurable with many options.
* When calling \ref Cy_SAR_Init, provide a pointer to the structure containing this configuration data.
* A set of enumerations is provided in this
* driver to help with configuring this structure.
*
* See the \ref group_sar_initialization section for guidance.
**/
typedef struct
{
    uint32_t ctrl;                                      /**< Control register settings (applies to all channels) */
    uint32_t sampleCtrl;                                /**< Sample control register settings (applies to all channels) */
    uint32_t sampleTime01;                              /**< Sample time in ADC clocks for Sample Time 0 and 1 */
    uint32_t sampleTime23;                              /**< Sample time in ADC clocks for Sample Time 2 and 3 */
    uint32_t rangeThres;                                /**< Range detect threshold register for all channels */
    cy_en_sar_range_detect_condition_t rangeCond;       /**< Range detect condition (below, inside, output, or above) for all channels */
    uint32_t chanEn;                                    /**< Enable bits for the channels */
    uint32_t chanConfig[CY_SAR_NUM_CHANNELS];           /**< Channel configuration */
    uint32_t intrMask;                                  /**< Interrupt enable mask */
    uint32_t satIntrMask;                               /**< Saturation detection interrupt enable mask */
    uint32_t rangeIntrMask;                             /**< Range detection interrupt enable mask  */
    uint32_t muxSwitch;                                 /**< SARMUX firmware switches to connect analog signals to SAR */
    uint32_t muxSwitchSqCtrl;                           /**< Enable SARSEQ control of specific SARMUX switches */
    bool configRouting;                                 /**< Configure or ignore routing related registers (muxSwitch, muxSwitchSqCtrl) */
    uint32_t vrefMvValue;                               /**< Reference voltage in millivolts used in converting counts to volts */
    cy_en_sar_clock_source_t clock;                     /**< Clock source selection (enable/disable SAR operation in the Deep Sleep mode). Ignored for PASS_ver1. */
    cy_stc_sar_fifo_config_t const * fifoCfgPtr;        /**< Pointer to the FIFO configuration structure \ref cy_stc_sar_fifo_config_t, if NULL - the FIFO is not used. Should be NULL for PASS_ver1. */
    bool trTimer;                                       /**< SAR is being triggered from the Timer \ref group_sysanalog_timer . Ignored for PASS_ver1. */
    bool scanCnt;                                       /**< Enable the scanning counter, configured by \ref Cy_SAR_CommonInit. Ignored for PASS_ver1. */
    bool scanCntIntr;                                   /**< EOS interrupt on scanning counter event. Ignored for PASS_ver1. */
} cy_stc_sar_config_t;

/** SAR triggering configuration structure */
typedef struct
{
    uint32_t                            pwrUpDelay;              /**< Power up delay for SAR blocks in Deep Sleep Clock cycles. Range 0..255. */
    uint32_t                            scanCount;               /**< Configures the number of samples SAR will take when triggered. Range 1..256. */
    uint32_t                            simultControl;           /**< Configures the SAR ADCs for simultaneous control. The value is a combined mask, created using following macros:
                                                                  * - CY_SAR_SAR0
                                                                  * - CY_SAR_SAR1
                                                                  * - CY_SAR_SAR2
                                                                  * - CY_SAR_SAR3
                                                                  * See \ref group_sysanalog_sar_select
                                                                  */
    uint32_t                            simultTrigSource;        /**< Configures the trigger source for simultaneous SAR hardware trigger. Use one of the following values:
                                                                  * - CY_SAR_SAR0
                                                                  * - CY_SAR_SAR1
                                                                  * - CY_SAR_SAR2
                                                                  * - CY_SAR_SAR3
                                                                  * - CY_SAR_TIMER
                                                                  * See \ref group_sysanalog_sar_select
                                                                  */
    cy_en_sar_simult_trig_event_sel_t   simultTrigEvent;         /**< Configures simultaneous trigger signal event */
    cy_en_sar_simult_trig_sync_sel_t    simultTrigSync;          /**< Enables synchronization of trigger signal */
    cy_en_sar_simult_trig_sample_sel_t  simultSamplesPerTrigger; /**< Configures scan sampling mode for each trigger event */
    cy_en_sar_simult_trig_intr_sel_t    simultEOSIntrSelect;     /**< Configures EOS interrupt condition */
}cy_stc_sar_common_config_t ;

/** This structure is used by the driver to backup the state of the SAR
* before entering sleep so that it can be re-enabled after waking up */
typedef struct
{
    uint32_t hwEnabled;                                 /**< SAR enabled state */
    uint32_t continuous;                                /**< State of the continuous bit */
} cy_stc_sar_state_backup_t;

/** Structure to read the FIFO buffer */
typedef struct
{
    uint16_t   value; /**< SAR sample */
    uint16_t channel; /**< SAR channel */
} cy_stc_sar_fifo_read_t;

/** \} group_sar_data_structures */

/** \addtogroup group_sar_functions
* \{
*/

/** This macro is for backward compatibility macro for driver v1.10 and before,
 * the preferred API is \ref Cy_SAR_DeepSleep */
#define Cy_SAR_Sleep    Cy_SAR_DeepSleep

/***************************************
*        Function Prototypes
***************************************/

/** \addtogroup group_sar_functions_trig
* This set of functions is for initialization and usage of SAR common settings
* and simultaneous triggering.
* \{
*/
cy_en_sar_status_t Cy_SAR_CommonInit(PASS_Type *base, const cy_stc_sar_common_config_t  * trigConfig);
__STATIC_INLINE void Cy_SAR_SimultStart(PASS_Type *base, uint32_t sarMask, cy_en_sar_start_convert_sel_t mode);
__STATIC_INLINE void Cy_SAR_SimultStop(PASS_Type *base, uint32_t sarMask);
/** \} */


/** \addtogroup group_sar_functions_basic
* This set of functions is for initialization and basic usage
* \{
*/
cy_en_sar_status_t Cy_SAR_Init(SAR_Type *base, const cy_stc_sar_config_t *config);
cy_en_sar_status_t Cy_SAR_DeInit(SAR_Type *base, bool deInitRouting);
void Cy_SAR_Enable(SAR_Type *base);
void Cy_SAR_Disable(SAR_Type *base);
void Cy_SAR_StartConvert(SAR_Type *base, cy_en_sar_start_convert_sel_t startSelect);
void Cy_SAR_StopConvert(SAR_Type *base);
cy_en_sar_status_t Cy_SAR_IsEndConversion(SAR_Type *base, cy_en_sar_return_mode_t retMode);
int16_t Cy_SAR_GetResult16(const SAR_Type *base, uint32_t chan);
int32_t Cy_SAR_GetResult32(const SAR_Type *base, uint32_t chan);
__STATIC_INLINE uint32_t Cy_SAR_GetChanResultUpdated(const SAR_Type *base);
__STATIC_INLINE void Cy_SAR_EnableInjection(SAR_Type *base, bool tailgating);
/** \} */

/** \addtogroup group_sar_functions_power
* This set of functions is for Deep Sleep entry and exit
* \{
*/
cy_en_syspm_status_t Cy_SAR_DeepSleepCallback(const cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
void Cy_SAR_DeepSleep(SAR_Type *base);
void Cy_SAR_Wakeup(SAR_Type *base);
/** \} */

/** \addtogroup group_sar_functions_config
* This set of functions allows changes to the SAR configuration
* after initialization.
* \{
*/
void Cy_SAR_SetConvertMode(SAR_Type *base, cy_en_sar_sample_ctrl_trigger_mode_t mode);
__STATIC_INLINE void Cy_SAR_SetChanMask(SAR_Type *base, uint32_t enableMask);
void Cy_SAR_SetLowLimit(SAR_Type *base, uint32_t lowLimit);
void Cy_SAR_SetHighLimit(SAR_Type *base, uint32_t highLimit);
__STATIC_INLINE void Cy_SAR_SetRangeCond(SAR_Type *base, cy_en_sar_range_detect_condition_t cond);
/** \} */

/** \addtogroup group_sar_functions_countsto
* This set of functions performs counts to *volts conversions.
* \{
*/
int16_t Cy_SAR_RawCounts2Counts(const SAR_Type *base, uint32_t chan, int16_t adcCounts);
float32_t Cy_SAR_CountsTo_Volts(const SAR_Type *base, uint32_t chan, int16_t adcCounts);
int16_t Cy_SAR_CountsTo_mVolts(const SAR_Type *base, uint32_t chan, int16_t adcCounts);
int32_t Cy_SAR_CountsTo_uVolts(const SAR_Type *base, uint32_t chan, int16_t adcCounts);
cy_en_sar_status_t Cy_SAR_SetChannelOffset(const SAR_Type *base, uint32_t chan, int16_t offset);
cy_en_sar_status_t Cy_SAR_SetChannelGain(const SAR_Type *base, uint32_t chan, int32_t adcGain);
/** \} */


/** \cond
 * Deprecated functions
 * Don't support multi-instance
 * For existing projects the mapping is on SAR0 instance
 * Strongly not recommended for new designs
 * Use Cy_SAR_SetChannelOffset and Cy_SAR_SetChannelGain instead
 */
__STATIC_INLINE cy_en_sar_status_t Cy_SAR_SetOffset(uint32_t chan, int16_t offset)
{
    return (Cy_SAR_SetChannelOffset(CY_SAR0_BASE, chan, offset));
}

__STATIC_INLINE cy_en_sar_status_t Cy_SAR_SetGain(uint32_t chan, int32_t adcGain)
{
    return (Cy_SAR_SetChannelGain(CY_SAR0_BASE, chan, adcGain));
}
/** \endcond */


/** \addtogroup group_sar_functions_switches
* This set of functions is for controlling/querying the SARMUX switches
* \{
*/
void Cy_SAR_SetAnalogSwitch(SAR_Type *base, cy_en_sar_switch_register_sel_t switchSelect, uint32_t switchMask, cy_en_sar_switch_state_t state);
uint32_t Cy_SAR_GetAnalogSwitch(const SAR_Type *base, cy_en_sar_switch_register_sel_t switchSelect);
__STATIC_INLINE void Cy_SAR_SetVssaVminusSwitch(SAR_Type *base, cy_en_sar_switch_state_t state);
void Cy_SAR_SetSwitchSarSeqCtrl(SAR_Type *base, uint32_t switchMask, cy_en_sar_switch_sar_seq_ctrl_t ctrl);
__STATIC_INLINE void Cy_SAR_SetVssaSarSeqCtrl(SAR_Type *base, cy_en_sar_switch_sar_seq_ctrl_t ctrl);
/** \} */

/** \addtogroup group_sar_functions_interrupt
* This set of functions are related to SAR interrupts.
* \{
*/
__STATIC_INLINE uint32_t Cy_SAR_GetInterruptStatus(const SAR_Type *base);
__STATIC_INLINE void Cy_SAR_ClearInterrupt(SAR_Type *base, uint32_t intrMask);
__STATIC_INLINE void Cy_SAR_SetInterrupt(SAR_Type *base, uint32_t intrMask);
__STATIC_INLINE void Cy_SAR_SetInterruptMask(SAR_Type *base, uint32_t intrMask);
__STATIC_INLINE uint32_t Cy_SAR_GetInterruptMask(const SAR_Type *base);
__STATIC_INLINE uint32_t Cy_SAR_GetInterruptStatusMasked(const SAR_Type *base);

__STATIC_INLINE uint32_t Cy_SAR_GetRangeInterruptStatus(const SAR_Type *base);
__STATIC_INLINE void Cy_SAR_ClearRangeInterrupt(SAR_Type *base, uint32_t chanMask);
__STATIC_INLINE void Cy_SAR_SetRangeInterrupt(SAR_Type *base, uint32_t chanMask);
__STATIC_INLINE void Cy_SAR_SetRangeInterruptMask(SAR_Type *base, uint32_t chanMask);
__STATIC_INLINE uint32_t Cy_SAR_GetRangeInterruptMask(const SAR_Type *base);
__STATIC_INLINE uint32_t Cy_SAR_GetRangeInterruptStatusMasked(const SAR_Type *base);

__STATIC_INLINE uint32_t Cy_SAR_GetSatInterruptStatus(const SAR_Type *base);
__STATIC_INLINE void Cy_SAR_ClearSatInterrupt(SAR_Type *base, uint32_t chanMask);
__STATIC_INLINE void Cy_SAR_SetSatInterrupt(SAR_Type *base, uint32_t chanMask);
__STATIC_INLINE void Cy_SAR_SetSatInterruptMask(SAR_Type *base, uint32_t chanMask);
__STATIC_INLINE uint32_t Cy_SAR_GetSatInterruptMask(const SAR_Type *base);
__STATIC_INLINE uint32_t Cy_SAR_GetSatInterruptStatusMasked(const SAR_Type *base);

__STATIC_INLINE uint32_t Cy_SAR_GetInterruptCause(const SAR_Type *base);
/** \} */


/** \addtogroup group_sar_functions_helper
* This set of functions is for useful configuration query
* \{
*/
bool Cy_SAR_IsChannelSigned(const SAR_Type *base, uint32_t chan);
bool Cy_SAR_IsChannelSingleEnded(const SAR_Type *base, uint32_t chan);
__STATIC_INLINE bool Cy_SAR_IsChannelDifferential(const SAR_Type *base, uint32_t chan);
/** \} */

/** \addtogroup group_sar_functions_lp
* \{
*/

cy_en_sar_status_t Cy_SAR_ScanCountEnable(const SAR_Type * base);
__STATIC_INLINE void Cy_SAR_ScanCountDisable(const SAR_Type * base);
__STATIC_INLINE void Cy_SAR_SelectClock(const SAR_Type * base, cy_en_sar_clock_source_t clock);
/** \} */


/** \addtogroup group_sar_functions_fifo
* \{
*/
__STATIC_INLINE void Cy_SAR_FifoRead(const SAR_Type *base, cy_stc_sar_fifo_read_t * readStruct);
__STATIC_INLINE uint32_t Cy_SAR_FifoGetDataCount(const SAR_Type *base);
__STATIC_INLINE void Cy_SAR_FifoSetLevel(const SAR_Type *base, uint32_t level);
__STATIC_INLINE void Cy_SAR_ClearFifoInterrupt(const SAR_Type *base, uint32_t intrMask);
__STATIC_INLINE void Cy_SAR_SetFifoInterrupt(const SAR_Type *base, uint32_t intrMask);
__STATIC_INLINE void Cy_SAR_SetFifoInterruptMask(const SAR_Type *base, uint32_t intrMask);
__STATIC_INLINE uint32_t Cy_SAR_GetFifoInterruptStatus(const SAR_Type *base);
__STATIC_INLINE uint32_t Cy_SAR_GetFifoInterruptMask(const SAR_Type *base);
__STATIC_INLINE uint32_t Cy_SAR_GetFifoInterruptStatusMasked(const SAR_Type *base);
/** \} */

/** \addtogroup group_sar_functions_basic
* \{
*/


/*******************************************************************************
* Function Name: Cy_SAR_GetChanResultUpdated
****************************************************************************//**
*
* Return whether the RESULT register has been updated or not.
* If the bit is high, the corresponding channel RESULT register was updated,
* i.e. was sampled during the previous scan and, in case of Interleaved averaging,
* reached the averaging count.
* If the bit is low, the corresponding channel is not enabled or the averaging count
* is not yet reached for Interleaved averaging.
*
* \param base
* Pointer to structure describing registers
*
* \return
* Each bit of the result corresponds to the channel.
* Bit 0 is for channel 0, etc.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_GET_CHAN_RESULT_UPDATED
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetChanResultUpdated(const SAR_Type *base)
{
    return SAR_CHAN_RESULT_UPDATED(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_EnableInjection
****************************************************************************//**
*
* Triggers the injection channel sample.
*
* \param base
* Pointer to structure describing registers
*
* \param tailgating
* Injection channel tailgating enable:
* - true: The addressed pin is sampled after the next trigger and after all enabled channels have been scanned.
* - false: SAR is immediately triggered when the SAR is not busy.
*   If the SAR is busy, the INJ channel addressed pin is sampled at the end of the current scan.
*
* \funcusage \snippet sar/snippet/main.c SNIPPET_SAR_IS_END_CONVERSION
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_EnableInjection(SAR_Type *base, bool tailgating)
{
    SAR_INJ_CHAN_CONFIG(base) = _CLR_SET_FLD32U(SAR_INJ_CHAN_CONFIG(base), SAR_INJ_CHAN_CONFIG_INJ_TAILGATING, tailgating ? 1UL : 0UL) | SAR_INJ_CHAN_CONFIG_INJ_START_EN_Msk;
}


/** \} */

/** \addtogroup group_sar_functions_config
* \{
*/


/*******************************************************************************
* Function Name: Cy_SAR_SetChanMask
****************************************************************************//**
*
* Set the enable/disable mask for the channels.
*
* \param base
* Pointer to structure describing registers
*
* \param enableMask
* Channel enable/disable mask. Each bit corresponds to a channel.
* - 0: the corresponding channel is disabled.
* - 1: the corresponding channel is enabled; it will be included in the next scan.
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SET_CHAN_MASK
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetChanMask(SAR_Type *base, uint32_t enableMask)
{
    CY_ASSERT_L2(CY_SAR_CHANMASK(enableMask));

    SAR_CHAN_EN(base) = enableMask;
}


/*******************************************************************************
* Function Name: Cy_SAR_SetRangeCond
****************************************************************************//**
*
* Set the condition in which range detection interrupts are triggered.
*
* \param base
* Pointer to structure describing registers
*
* \param cond
* A value of the enum \ref cy_en_sar_range_detect_condition_t.
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SET_RANGE_COND
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetRangeCond(SAR_Type *base, cy_en_sar_range_detect_condition_t cond)
{
    CY_ASSERT_L3(CY_SAR_RANGECOND(cond));

    SAR_RANGE_COND(base) = (uint32_t)cond << SAR_RANGE_COND_RANGE_COND_Pos;
}

/** \} */

/** \addtogroup group_sar_functions_interrupt
* \{
*/
/*******************************************************************************
* Function Name: Cy_SAR_GetInterruptStatus
****************************************************************************//**
*
* Return the interrupt register status.
*
* \param base
* Pointer to structure describing registers
*
* \return Interrupt status
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_ISR
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetInterruptStatus(const SAR_Type *base)
{
    return SAR_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_ClearInterrupt
****************************************************************************//**
*
* Clear the interrupt.
* The interrupt must be cleared with this function so that the hardware
* can set subsequent interrupts and those interrupts can be forwarded
* to the interrupt controller, if enabled.
*
* \param base
* Pointer to structure describing registers
*
* \param intrMask
* The mask of interrupts to clear. Typically this will be the value returned
* from \ref Cy_SAR_GetInterruptStatus.
* Alternately, select one or more values from \ref group_sar_macros_interrupt and "OR" them together.
* - \ref CY_SAR_INTR_EOS
* - \ref CY_SAR_INTR_OVERFLOW
* - \ref CY_SAR_INTR_FW_COLLISION
* - \ref CY_SAR_INTR_INJ_EOC
* - \ref CY_SAR_INTR_INJ_SATURATE
* - \ref CY_SAR_INTR_INJ_RANGE
* - \ref CY_SAR_INTR_INJ_COLLISION
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_ClearInterrupt(SAR_Type *base, uint32_t intrMask)
{
    CY_ASSERT_L2(CY_SAR_INTRMASK(intrMask));
    SAR_INTR(base) = intrMask & CY_SAR_INTR;
    /* Dummy read for buffered writes. */
    (void) SAR_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_SetInterrupt
****************************************************************************//**
*
* Trigger an interrupt with software.
*
* \param base
* Pointer to structure describing registers
*
* \param intrMask
* The mask of interrupts to set.
* Select one or more values from \ref group_sar_macros_interrupt and "OR" them together.
* - \ref CY_SAR_INTR_EOS
* - \ref CY_SAR_INTR_OVERFLOW
* - \ref CY_SAR_INTR_FW_COLLISION
* - \ref CY_SAR_INTR_INJ_EOC
* - \ref CY_SAR_INTR_INJ_SATURATE
* - \ref CY_SAR_INTR_INJ_RANGE
* - \ref CY_SAR_INTR_INJ_COLLISION
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetInterrupt(SAR_Type *base, uint32_t intrMask)
{
    CY_ASSERT_L2(CY_SAR_INTRMASK(intrMask));

    SAR_INTR_SET(base) = intrMask & CY_SAR_INTR;
}


/*******************************************************************************
* Function Name: Cy_SAR_SetInterruptMask
****************************************************************************//**
*
* Enable which interrupts can trigger the CPU interrupt controller.
*
* \param base
* Pointer to structure describing registers
*
* \param intrMask
* The mask of interrupts. Select one or more values from \ref group_sar_macros_interrupt
* and "OR" them together:
* - \ref CY_SAR_INTR_EOS
* - \ref CY_SAR_INTR_OVERFLOW
* - \ref CY_SAR_INTR_FW_COLLISION
* - \ref CY_SAR_INTR_INJ_EOC
* - \ref CY_SAR_INTR_INJ_SATURATE
* - \ref CY_SAR_INTR_INJ_RANGE
* - \ref CY_SAR_INTR_INJ_COLLISION
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SET_INTERRUPT_MASK
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetInterruptMask(SAR_Type *base, uint32_t intrMask)
{
    CY_ASSERT_L2(CY_SAR_INTRMASK(intrMask));

    SAR_INTR_MASK(base) = intrMask & CY_SAR_INTR;
}


/*******************************************************************************
* Function Name: Cy_SAR_GetInterruptMask
****************************************************************************//**
*
* Return which interrupts can trigger the CPU interrupt controller
* as configured by \ref Cy_SAR_SetInterruptMask.
*
* \param base
* Pointer to structure describing registers
*
* \return
* Interrupt mask. Compare this value with masks in \ref group_sar_macros_interrupt.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_GET_INTERRUPT_MASK
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetInterruptMask(const SAR_Type *base)
{
    return SAR_INTR_MASK(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_GetInterruptStatusMasked
****************************************************************************//**
*
* Return the bitwise AND between the interrupt request and mask registers.
* See \ref Cy_SAR_GetInterruptStatus and \ref Cy_SAR_GetInterruptMask.
*
* \param base
* Pointer to structure describing registers
*
* \return
* Bitwise AND of the interrupt request and mask registers
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetInterruptStatusMasked(const SAR_Type *base)
{
    return SAR_INTR_MASKED(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_GetRangeInterruptStatus
****************************************************************************//**
*
* Return the range interrupt register status.
* If the status bit is low for a channel, the channel may not be enabled
* (\ref Cy_SAR_SetChanMask), range detection is not enabled for the
* channel (\ref Cy_SAR_SetRangeInterruptMask), or range detection was not
* triggered for the channel.
*
* \param base
* Pointer to structure describing registers
*
* \return
* The range interrupt status for all channels. Bit 0 is for channel 0, etc.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_GET_RANGE_INTERRUPT_STATUS
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetRangeInterruptStatus(const SAR_Type *base)
{
    return SAR_RANGE_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_ClearRangeInterrupt
****************************************************************************//**
*
* Clear the range interrupt for the specified channel mask.
* The interrupt must be cleared with this function so that
* the hardware can set subset interrupts and those interrupts can
* be forwarded to the interrupt controller, if enabled.
*
* \param base
* Pointer to structure describing registers
*
* \param chanMask
* The channel mask. Bit 0 is for channel 0, etc.
* Typically, this is the value returned from \ref Cy_SAR_GetRangeInterruptStatus.
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_ClearRangeInterrupt(SAR_Type *base, uint32_t chanMask)
{
    CY_ASSERT_L2(CY_SAR_CHANMASK(chanMask));

    SAR_RANGE_INTR(base) = chanMask & CY_SAR_CHANNELS_MASK;

    /* Dummy read for buffered writes. */
    (void) SAR_RANGE_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_SetRangeInterrupt
****************************************************************************//**
*
* Trigger a range interrupt with software for the specific channel mask.
*
* \param base
* Pointer to structure describing registers
*
* \param chanMask
* The channel mask. Bit 0 is for channel 0, etc.
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetRangeInterrupt(SAR_Type *base, uint32_t chanMask)
{
    CY_ASSERT_L2(CY_SAR_CHANMASK(chanMask));

    SAR_RANGE_INTR_SET(base) = chanMask & CY_SAR_CHANNELS_MASK;
}


/*******************************************************************************
* Function Name: Cy_SAR_SetRangeInterruptMask
****************************************************************************//**
*
* Enable which channels can trigger a range interrupt.
*
* \param base
* Pointer to structure describing registers
*
* \param chanMask
* The channel mask. Bit 0 is for channel 0, etc.
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_SET_RANGE_INTERRUPT_MASK
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetRangeInterruptMask(SAR_Type *base, uint32_t chanMask)
{
    CY_ASSERT_L2(CY_SAR_CHANMASK(chanMask));

    SAR_RANGE_INTR_MASK(base) = chanMask & CY_SAR_CHANNELS_MASK;
}


/*******************************************************************************
* Function Name: Cy_SAR_GetRangeInterruptMask
****************************************************************************//**
*
* Return which interrupts can trigger a range interrupt as configured by
* \ref Cy_SAR_SetRangeInterruptMask.
*
* \param base
* Pointer to structure describing registers
*
* \return
* The range interrupt mask
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetRangeInterruptMask(const SAR_Type *base)
{
    return SAR_RANGE_INTR_MASK(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_GetRangeInterruptStatusMasked
****************************************************************************//**
*
* Return the bitwise AND between the range interrupt request and mask registers.
* See \ref Cy_SAR_GetRangeInterruptStatus and \ref Cy_SAR_GetRangeInterruptMask.
*
* \param base
* Pointer to structure describing registers
*
* \return
* Bitwise AND between of range interrupt request and mask
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetRangeInterruptStatusMasked(const SAR_Type *base)
{
    return SAR_RANGE_INTR_MASKED(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_GetSatInterruptStatus
****************************************************************************//**
*
* Return the saturate interrupt register status.
* If the status bit is low for a channel, the channel may not be enabled
* (\ref Cy_SAR_SetChanMask), saturation detection is not enabled for the
* channel (\ref Cy_SAR_SetSatInterruptMask), or saturation detection was not
* triggered for the channel.
*
* \param base
* Pointer to structure describing registers
*
* \return
* The saturate interrupt status for all channels. Bit 0 is for channel 0, etc.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_GET_SAT_INTERRUPT_STATUS
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetSatInterruptStatus(const SAR_Type *base)
{
    return SAR_SATURATE_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_ClearSatInterrupt
****************************************************************************//**
*
* Clear the saturate interrupt for the specified channel mask.
* The interrupt must be cleared with this function so that the hardware
* can set subsequent interrupts and those interrupts can be forwarded
* to the interrupt controller, if enabled.
*
* \param base
* Pointer to structure describing registers
*
* \param chanMask
* The channel mask. Bit 0 is for channel 0, etc.
* Typically, this is the value returned from \ref Cy_SAR_GetSatInterruptStatus.
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_ClearSatInterrupt(SAR_Type *base, uint32_t chanMask)
{
    CY_ASSERT_L2(CY_SAR_CHANMASK(chanMask));

    SAR_SATURATE_INTR(base) = chanMask & CY_SAR_CHANNELS_MASK;

    /* Dummy read for buffered writes. */
    (void) SAR_SATURATE_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_SetSatInterrupt
****************************************************************************//**
*
* Trigger a saturate interrupt with software for the specific channel mask.
*
* \param base
* Pointer to structure describing registers
*
* \param chanMask
* The channel mask. Bit 0 is for channel 0, etc.
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetSatInterrupt(SAR_Type *base, uint32_t chanMask)
{
    CY_ASSERT_L2(CY_SAR_CHANMASK(chanMask));

    SAR_SATURATE_INTR_SET(base) = chanMask & CY_SAR_CHANNELS_MASK;
}


/*******************************************************************************
* Function Name: Cy_SAR_SetSatInterruptMask
****************************************************************************//**
*
* Enable which channels can trigger a saturate interrupt.
*
* \param base
* Pointer to structure describing registers
*
* \param chanMask
* The channel mask. Bit 0 is for channel 0, etc.
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_GET_SAT_INTERRUPT_MASK
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetSatInterruptMask(SAR_Type *base, uint32_t chanMask)
{
    CY_ASSERT_L2(CY_SAR_CHANMASK(chanMask));

    SAR_SATURATE_INTR_MASK(base) = chanMask & CY_SAR_CHANNELS_MASK;
}


/*******************************************************************************
* Function Name: Cy_SAR_GetSatInterruptMask
****************************************************************************//**
*
* Return which interrupts can trigger a saturate interrupt as configured
* by \ref Cy_SAR_SetSatInterruptMask.
*
* \param base
* Pointer to structure describing registers
*
* \return
* The saturate interrupt mask. Bit 0 is for channel 0, etc.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetSatInterruptMask(const SAR_Type *base)
{
    return SAR_SATURATE_INTR_MASK(base);
}

/*******************************************************************************
* Function Name: Cy_SAR_GetSatInterruptStatusMasked
****************************************************************************//**
*
* Return the bitwise AND between the saturate interrupt request and mask registers.
* See \ref Cy_SAR_GetSatInterruptStatus and \ref Cy_SAR_GetSatInterruptMask.
*
* \param base
* Pointer to structure describing registers
*
* \return
* Bitwise AND of the saturate interrupt request and mask
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetSatInterruptStatusMasked(const SAR_Type *base)
{
    return SAR_SATURATE_INTR_MASKED(base);
}


/*******************************************************************************
* Function Name: Cy_SAR_GetInterruptCause
****************************************************************************//**
*
* Return the cause of the interrupt.
* The interrupt routine can be called due to one of the following events:
*   - End of scan (EOS)
*   - Overflow
*   - Firmware collision
*   - Saturation detected on one or more channels
*   - Range detected on one or more channels
*
* \param base
* Pointer to structure describing registers
*
* \return
* Mask of what caused the interrupt. Compare this value with one of these masks:
*   - SAR_INTR_CAUSE_EOS_MASKED_MIR_Msk : EOS caused the interrupt
*   - SAR_INTR_CAUSE_OVERFLOW_MASKED_MIR_Msk : Overflow caused the interrupt
*   - SAR_INTR_CAUSE_FW_COLLISION_MASKED_MIR_Msk : Firmware collision cause the interrupt
*   - SAR_INTR_CAUSE_SATURATE_MASKED_RED_Msk : Saturation detection on one or more channels caused the interrupt
*   - SAR_INTR_CAUSE_RANGE_MASKED_RED_Msk : Range detection on one or more channels caused the interrupt
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetInterruptCause(const SAR_Type *base)
{
    return SAR_INTR_CAUSE(base);
}
/** \} */

/** \addtogroup group_sar_functions_helper
* \{
*/


/*******************************************************************************
* Function Name: Cy_SAR_IsChannelDifferential
****************************************************************************//**
*
* Return true of channel is differential, else false.
*
* \param base
* Pointer to structure describing registers
*
* \param chan
* The channel to check, starting at 0.
*
* \return
* A false is return if chan is invalid.
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_IS_CHANNEL_DIFF
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SAR_IsChannelDifferential(const SAR_Type *base, uint32_t chan)
{
    return !Cy_SAR_IsChannelSingleEnded(base, chan);
}
/** \} */

/** \addtogroup group_sar_functions_switches
* \{
*/
/*******************************************************************************
* Function Name: Cy_SAR_SetVssaVminusSwitch
****************************************************************************//**
*
* Open or close the switch between VSSA and Vminus of the SARADC through firmware.
* This function calls \ref Cy_SAR_SetAnalogSwitch with switchSelect set to
* \ref CY_SAR_MUX_SWITCH0 and switchMask set to SAR_MUX_SWITCH0_MUX_FW_VSSA_VMINUS_Msk.
*
* \param base
* Pointer to structure describing registers
*
* \param state
* Open or close the switch. Select a value from \ref cy_en_sar_switch_state_t.
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_VSSA_VMINUS_SWITCH
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetVssaVminusSwitch(SAR_Type *base, cy_en_sar_switch_state_t state)
{
    Cy_SAR_SetAnalogSwitch(base, CY_SAR_MUX_SWITCH0, SAR_MUX_SWITCH0_MUX_FW_VSSA_VMINUS_Msk, state);
}


/*******************************************************************************
* Function Name: Cy_SAR_SetVssaSarSeqCtrl
****************************************************************************//**
*
* Enable or disable SARSEQ control of the switch between VSSA and Vminus of the SARADC.
* This function calls \ref Cy_SAR_SetSwitchSarSeqCtrl
* with switchMask set to SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_VSSA_Msk.
*
* \param base
* Pointer to structure describing registers
*
* \param ctrl
* Enable or disable control. Select a value from \ref cy_en_sar_switch_sar_seq_ctrl_t.
*
* \return None
*
* \funcusage
*
* \snippet sar/snippet/main.c SNIPPET_SAR_VSSA_SARSEQ_CTRL
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetVssaSarSeqCtrl(SAR_Type *base, cy_en_sar_switch_sar_seq_ctrl_t ctrl)
{
    Cy_SAR_SetSwitchSarSeqCtrl(base, SAR_MUX_SWITCH_SQ_CTRL_MUX_SQ_CTRL_VSSA_Msk, ctrl);
}
/** \} */


/** \addtogroup group_sar_functions_lp
* \{
*/


/*******************************************************************************
* Function Name: Cy_SAR_ScanCountDisable
****************************************************************************//**
*
* Disables the Scanning Counter.
*
* \param base
* Pointer to the structure of SAR instance registers.
*
* \funcusage \snippet sar/snippet/main.c SNIPPET_SAR_DS
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_ScanCountDisable(const SAR_Type  *base)
{
    if (!CY_PASS_V1)
    {
        uint32_t interruptState = Cy_SysLib_EnterCriticalSection();
        PASS_SAR_OVR_CTRL(CY_PASS_V2_ADDR) &= ~(CY_SAR_INSTANCE_MASK(base) << PASS_V2_SAR_OVR_CTRL_TR_SCAN_CNT_SEL_Pos);
        Cy_SysLib_ExitCriticalSection(interruptState);
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_SelectClock
****************************************************************************//**
*
* Switch the SAR input clock source.
* Suitable for PASS_V2 only.
* In case of CY_SAR_CLK_DEEPSLEEP it enables SAR operation in Deep Sleep mode.
*
* \param base
* Pointer to the structure of SAR instance registers.
*
* \param clock
* The SAR clock source \ref cy_en_sar_clock_source_t.
*
* \funcusage \snippet sar/snippet/main.c SNIPPET_SAR_DS
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SelectClock(const SAR_Type * base, cy_en_sar_clock_source_t clock)
{
    CY_ASSERT_L1(!CY_PASS_V1); /* Deep Sleep Clock is not supported */

    if (!CY_PASS_V1)
    {
        CY_ASSERT_L3(CY_SAR_IS_CLK_VALID(clock));
        PASS_SAR_CLOCK_SEL(base) = _VAL2FLD(PASS_V2_SAR_CLOCK_SEL_CLOCK_SEL, clock);
        PASS_SAR_DPSLP_CTRL(base) = _BOOL2FLD(PASS_V2_SAR_DPSLP_CTRL_ENABLED, (CY_SAR_CLK_DEEPSLEEP == clock));
    }
}
/** \} */


/** \addtogroup group_sar_functions_fifo
* \{
*/

/*******************************************************************************
* Function Name: Cy_SAR_FifoRead
****************************************************************************//**
*
* Reads FIFO word-by-word.
*
* \return Subsequent data sample
*
* \funcusage \snippet sar/snippet/main.c SNIPPET_FIFO
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_FifoRead(const SAR_Type * base, cy_stc_sar_fifo_read_t * readStruct)
{
    CY_ASSERT_L1(!CY_PASS_V1); /* FIFO is not supported */

    if(!CY_PASS_V1)
    {
        uint32_t locReg = PASS_FIFO_RD_DATA(base);
        readStruct->channel = (uint16_t)_FLD2VAL(PASS_FIFO_V2_RD_DATA_CHAN_ID, locReg);
        readStruct->value  = (uint16_t)_FLD2VAL(PASS_FIFO_V2_RD_DATA_RESULT, locReg);
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_FifoGetDataCount
****************************************************************************//**
*
* Returns a number of non-empty FIFO cells.
*
* \return Number of FIFO samples.
*
* \funcusage \snippet sar/snippet/main.c SNIPPET_FIFO
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_FifoGetDataCount(const SAR_Type * base)
{
    uint32_t retVal = 0UL;

    CY_ASSERT_L1(!CY_PASS_V1); /* FIFO is not supported */

    if(!CY_PASS_V1)
    {
        retVal = PASS_FIFO_USED(base);
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_SAR_ClearFifoInterrupt
****************************************************************************//**
*
* Clear the FIFO interrupt.
* The interrupt must be cleared with this function so that the hardware
* can set subsequent interrupts and those interrupts can be forwarded
* to the interrupt controller, if enabled.
*
* \param base
* Pointer to structure describing registers
*
* \param intrMask
* The mask of interrupts to clear. Typically this will be the value returned
* from \ref Cy_SAR_GetFifoInterruptStatus.
* Alternately, select one or more values from \ref group_sar_macros_interrupt and "OR" them together.
* - \ref CY_SAR_INTR_FIFO_LEVEL
* - \ref CY_SAR_INTR_FIFO_OVERFLOW
* - \ref CY_SAR_INTR_FIFO_UNDERFLOW
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_ClearFifoInterrupt(const SAR_Type * base, uint32_t intrMask)
{
    CY_ASSERT_L1(!CY_PASS_V1); /* FIFO is not supported */

    if(!CY_PASS_V1)
    {
        CY_ASSERT_L2(CY_SAR_FIFO_INTRMASK(intrMask));
        PASS_FIFO_INTR(base) = intrMask & CY_SAR_INTR_FIFO;
        (void) PASS_FIFO_INTR(base); /* Dummy read for buffered writes. */
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_SetFifoInterrupt
****************************************************************************//**
*
* Trigger an interrupt with software.
*
* \param base
* Pointer to structure describing registers
*
* \param intrMask
* The mask of interrupts to set.
* Select one or more values from \ref group_sar_macros_interrupt and "OR" them together.
* - \ref CY_SAR_INTR_FIFO_LEVEL
* - \ref CY_SAR_INTR_FIFO_OVERFLOW
* - \ref CY_SAR_INTR_FIFO_UNDERFLOW
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetFifoInterrupt(const SAR_Type * base, uint32_t intrMask)
{
    CY_ASSERT_L1(!CY_PASS_V1); /* FIFO is not supported */

    if(!CY_PASS_V1)
    {
        CY_ASSERT_L2(CY_SAR_FIFO_INTRMASK(intrMask));
        PASS_FIFO_INTR_SET(base) = intrMask & CY_SAR_INTR_FIFO;
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_SetFifoInterruptMask
****************************************************************************//**
*
* Enable which interrupts can trigger the CPU interrupt controller.
*
* \param base
* Pointer to structure describing registers
*
* \param intrMask
* The mask of interrupts. Select one or more values from \ref group_sar_macros_interrupt
* and "OR" them together:
* - \ref CY_SAR_INTR_FIFO_LEVEL
* - \ref CY_SAR_INTR_FIFO_OVERFLOW
* - \ref CY_SAR_INTR_FIFO_UNDERFLOW
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SetFifoInterruptMask(const SAR_Type * base, uint32_t intrMask)
{
    CY_ASSERT_L1(!CY_PASS_V1); /* FIFO is not supported */

    if(!CY_PASS_V1)
    {
        CY_ASSERT_L2(CY_SAR_FIFO_INTRMASK(intrMask));
        PASS_FIFO_INTR_MASK(base) = intrMask & CY_SAR_INTR_FIFO;
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_GetFifoInterruptStatus
****************************************************************************//**
*
* Return the interrupt register status.
*
* \param base
* Pointer to structure describing registers
*
* \return Interrupt status \ref group_sar_macros_interrupt.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetFifoInterruptStatus(const SAR_Type * base)
{
    uint32_t retVal = 0UL;

    CY_ASSERT_L1(!CY_PASS_V1); /* FIFO is not supported */

    if(!CY_PASS_V1)
    {
        retVal = PASS_FIFO_INTR(base);
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_SAR_GetFifoInterruptMask
****************************************************************************//**
*
* Return which interrupts can trigger the CPU interrupt controller
* as configured by \ref Cy_SAR_SetFifoInterruptMask.
*
* \param base
* Pointer to structure describing registers
*
* \return
* Interrupt mask. Compare this value with masks in \ref group_sar_macros_interrupt.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetFifoInterruptMask(const SAR_Type * base)
{
    uint32_t retVal = 0UL;

    CY_ASSERT_L1(!CY_PASS_V1); /* FIFO is not supported */

    if(!CY_PASS_V1)
    {
        retVal = PASS_FIFO_INTR_MASK(base);
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_SAR_GetFifoInterruptStatusMasked
****************************************************************************//**
*
* Return the bitwise AND between the interrupt request and mask registers.
* See \ref Cy_SAR_GetFifoInterruptStatus and \ref Cy_SAR_GetFifoInterruptMask.
*
* \param base
* Pointer to structure describing registers
*
* \return
* Bitwise AND of the interrupt request and mask registers \ref group_sar_macros_interrupt.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SAR_GetFifoInterruptStatusMasked(const SAR_Type * base)
{
    uint32_t retVal = 0UL;

    CY_ASSERT_L1(!CY_PASS_V1); /* FIFO is not supported */

    if(!CY_PASS_V1)
    {
        retVal = PASS_FIFO_INTR_MASKED(base);
    }

    return (retVal);
}


/*******************************************************************************
* Function Name: Cy_SAR_FifoSetLevel
****************************************************************************//**
*
* Sets the FIFO trigger level which specifies how many samples FIFO should
* contain in order to generate trigger event.
*
* \param base
* Pointer to structure describing registers
*
* \param level The FIFO trigger level to be set. Range: 1..256.
*
* \return None
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_FifoSetLevel(const SAR_Type *base, uint32_t level)
{
    CY_ASSERT_L1(!CY_PASS_V1); /* FIFO is not supported */

    if(!CY_PASS_V1)
    {
        uint32_t locLevel = level - 1UL; /* Convert the user value into the machine value */
        CY_ASSERT_L2(CY_SAR_IS_FIFO_LEVEL_VALID(locLevel));
        PASS_FIFO_LEVEL(base) = _VAL2FLD(PASS_FIFO_V2_LEVEL_LEVEL, locLevel);
    }
}

/** \} */

/*******************************************************************************
* Function Name: Cy_SAR_SimultStart
****************************************************************************//**
*
* Simultaneously starts two or more SARs.
*
* \param base
* Pointer to structure describing PASS registers.
*
* \param sarMask specifies which SAR instances will be started.
* Mask should contain at least two SAR instances for operation.
*
* \param mode specifies mode of SARs operation.
*
* \return None
*
* \funcusage
* \snippet sar/snippet/main.c SAR_SNIPPET_SIMULT_START_STOP
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SimultStart(PASS_Type *base, uint32_t sarMask, cy_en_sar_start_convert_sel_t mode)
{
    CY_ASSERT_L1(!CY_PASS_V1); /* SAR simultaneous start feature is not supported on PASS_ver1 IP block. */

    if (!CY_PASS_V1)
    {
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3', 'Deviate Pointer type conversions');
        PASS_SAR_SIMULT_FW_START_CTRL(base) =
            (_VAL2FLD(PASS_V2_SAR_SIMULT_FW_START_CTRL_FW_TRIGGER, sarMask) |
            ((mode == CY_SAR_START_CONVERT_CONTINUOUS) ? _VAL2FLD(PASS_V2_SAR_SIMULT_FW_START_CTRL_CONTINUOUS, sarMask) : 0UL));
    }
}


/*******************************************************************************
* Function Name: Cy_SAR_SimultStop
****************************************************************************//**
*
* Stops the selected SARs.
*
* \param base
* Pointer to structure describing PASS registers.
*
* \param sarMask specifies which SAR instances should be stopped.
*
* \return None
*
* \funcusage
* \snippet sar/snippet/main.c SAR_SNIPPET_SIMULT_START_STOP
*
*******************************************************************************/
__STATIC_INLINE void Cy_SAR_SimultStop(PASS_Type *base, uint32_t sarMask)
{
    if (!CY_PASS_V1)
    {
        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 11.3', 'Deviate Pointer type conversions');
        PASS_SAR_SIMULT_FW_START_CTRL(base) = _VAL2FLD(PASS_V2_SAR_SIMULT_FW_START_CTRL_CONTINUOUS, (~sarMask));
    }
}

/** \} group_sar_functions */
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXS40PASS_SAR */

#endif /** !defined(CY_SAR_H) */

/** \} group_sar */

/* [] END OF FILE */
