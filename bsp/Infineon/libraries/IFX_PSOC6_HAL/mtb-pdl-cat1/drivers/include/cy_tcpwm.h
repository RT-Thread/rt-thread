/***************************************************************************//**
* \file cy_tcpwm.h
* \version 1.40
*
* The header file of the TCPWM driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2022 Cypress Semiconductor Corporation
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
* \addtogroup group_tcpwm
* \{
* \defgroup group_tcpwm_common  Common
* \defgroup group_tcpwm_counter Timer/Counter (TCPWM)
* \defgroup group_tcpwm_pwm     PWM (TCPWM)
* \defgroup group_tcpwm_quaddec Quadrature Decoder (TCPWM)
* \defgroup group_tcpwm_shiftreg Shift Register (TCPWM)
* \} */

/**
* \addtogroup group_tcpwm
* \{
*
* The TCPWM driver is a multifunction driver that implements Timer Counter,
* PWM, Quadrature Decoder and Shift Register functionality using the TCPWM block.
*
* The functions and other declarations used in this driver are in cy_tcpwm_counter.h,
* cy_tcpwm_pwm.h, cy_tcpwm_quaddec.h, cy_tcpwm_shiftreg.h respectively. Include cy_pdl.h
* to get access to all functions and declarations in the PDL.
*
* Each TCPWM block is a collection of counters that can all be triggered
* simultaneously. For each function call, the base register address of
* the TCPWM being used must be passed first, followed by the index of
* the counter you want to touch next.
*
* The TCPWM supports seven function modes:
* * Timer
* * Capture
* * Quadrature Decoder
* * Pulse Width Modulation (PWM)
* * PWM with dead time insertion (PWMDT)
* * Pseudo random PWM (PWMPR)
* * Shift Register
*
* The TCPWM driver is structured to map these seven functional modes to four
* high level operating modes:
* * Timer/Counter (includes Timer, Capture modes)
* * PWM (PWM, PWMDT, PWMPR)
* * Quadrature Decoder
* * Shift Register
*
* A brief description on each of the operating modes:
*
* \b Timer/Counter
*
* Use this mode whenever a specific timing interval or measurement is
* needed. Examples include:
* * Creating a periodic interrupt for running other system tasks
* * Measuring frequency of an input signal
* * Measuring pulse width of an input signal
* * Measuring time between two external events
* * Counting events
* * Triggering other system resources after x number events
* * Capturing time stamps when events occur
*
* \n
* \b PWM
*
* Use this mode when an output square wave is needed with a specific
* period and duty cycle, such as:
* * Creating arbitrary square wave outputs
* * Driving an LED (changing the brightness)
* * Driving Motors (dead time assertion available)
*
* \n
* \b Quadrature \b Decoder
*
* A quadrature decoder is used to decode the output of a quadrature encoder.
* A quadrature encoder senses the position, velocity, and direction of
* an object (for example a rotating axle, or a spinning mouse ball).
* A quadrature decoder can also be used for precision measurement of speed,
* acceleration, and position of a motor's rotor, or with a rotary switch to
* determine user input. \n
*
* \n
* \b Shift \b Register
*
* Shift Register functionality shifts the counter value to the right.
* A shift register is used to apply a signal delay function which can be used
* eg: in detecting frequency shift keying (FSK) signals.
* A shift register is also used in parallel-in to serial-out data conversion
* and serial-in to parallel-out data conversion.
*
* \section group_tcpwm_version_information TCPWM Versions
*
* There are two versions of TCPWM driver
*
* \b TCPWM \b Version \b 2
*
* - Devices CY8C61x4 and CY8C62x4 use this version.
* - Supports up to four counter groups (check TRM for actual number of groups supported)
* - Each counter group consists of up to 256 counters (check TRM for actual number of counters supported)
* - Each counter
*     - Can run in one of seven function modes
*     - Supports various counting modes:
*         - One-shot mode, Continuous mode (Up/Down/Up-down)
*     - Selects input signals
*         - Start, Reload, Stop, Count, and two Capture event signals
*     - Generates output signals:
*         - Two output triggers, PWM output, and Interrupt
*     - Trigger Outputs (TR_OUT0/1) and an Interrupt on an event
*         - Overflow (OV)
*         - Underflow (UN)
*         - Terminal Count (TC)
*         - CC0/1_MATCH
*         - LINE_OUT
*     - Supports debug mode
*     - Each counter can produce two output signals
*
* \image html tcpwm_v2_block_diagram.png
*
* - \b Input \b Trigger \b Selection \b and \b Event \b Detection
*     - The counter control signals are generated as follows:
*         - Selects input signals from two types of trigger multiplexer signals
*             - Group trigger and one-to-one trigger
*             - The constant '1' and '0' are also used as input triggers
*         - Detects the selected edge from four types
*             - Rising edge/falling edge/any edge/no edge
*         - Supports software (SW) command
*             - SW command of Trigger Multiplexer/SW command of TCPWM
*
* \image html tcpwm_v2_input_trigger_sel.png
*
* - \b Simultaneous \b Activation:
*     - When a Trigger Multiplexer block SW command is used, the TCPWM counters can be activated at the same time
*
* \image html tcpwm_v2_trigger_simultaneously.png
*
* \b TCPWM \b Version \b 1
*
* - Devices CY8C61x6, CY8C61x7, CY8C62x5, CY8C62x6, CY8C62x7, CY8C62x8, CY8C62xA, CY8C63x6, CY8C63x7, CYS0644xxZI-S2D44,
* CYB0644xxZI-S4D44, CYB06447BZI-BLDX, CYB06447BZI-D54 and CYB06445LQI-S3D42 use this version.
* - Supports up to 32 counters (check TRM for actual number of counters supported)
* - Synchronized operation of multiple counters.
* - 16 or 32 bit counter, compare/capture (CC) and period registers.
* - CC and period registers are double buffered.
* - Up, down and up/down counting modes.
* - 14 trigger input signals and 2 constant input signals: '0' and '1', for a total of 16 hardware (HW) input signals
* - Rising edge, falling edge, combined rising/falling edge detection or pass-through on all HW input signals to derive counter events.
* - The start, reload, stop and capture events can be generated by software.
* - Clock pre-scaling (1x, 2x, 4x ... 128x).
* - Support Pseudo Random PWM
* - 3 output trigger signals for each counter to indicate underflow, overflow and cc_match events.
* - 2 PWM complementary output lines for each counter. Dead time insertion ([0, 255] counter cycles).
* - Support one interrupt output for each counter.
*
* \image html tcpwm_v1_block_diagram.png
*
* - Many functions work with an individual counter. You can also manage multiple counters simultaneously for certain functions.
* - These are listed in the \ref group_tcpwm_functions_common section of the TCPWM.
* - You can enable, disable, or trigger (in various ways) multiple counters simultaneously.
* - For these functions you provide a bit field representing each counter in the TCPWM you want to control.
* - You can represent the bit field as an ORed mask of each counter, like ((1U << cntNumX) | (1U << cntNumX) | (1U << cntNumX)), where X is the counter number from 0 to 31.
*
* \note
* * If none of the input terminals (start, reload(index)) are used, the
* software event \ref Cy_TCPWM_TriggerStart or
* \ref Cy_TCPWM_TriggerReloadOrIndex must be called to start the counting.
* * If count input terminal is not used, the \ref CY_TCPWM_INPUT_LEVEL macro
* should be set for the countInputMode parameter and the \ref CY_TCPWM_INPUT_1
* macro should be set for the countInput parameter in the configuration
* structure of the appropriate mode(Counter
* \ref group_tcpwm_data_structures_counter, PWM
* \ref group_tcpwm_data_structures_pwm, QuadDec
* \ref group_tcpwm_data_structures_quaddec, or Shift Register
* \ref group_tcpwm_data_structures_shiftreg).

* \section group_tcpwm_more_information More Information
*
* For more information on the TCPWM peripheral, refer to the technical
* reference manual (TRM).
*
* \section group_tcpwm_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.40</td>
*     <td>Support for CAT1B and CAT1D devices is added. No changes in public APIs interface and behavior. </td>
*     <td>New devices support added.</td>
*   </tr>
*   <tr>
*     <td>1.30.1</td>
*     <td>Updated documentation of PWM mode. </td>
*     <td>Documentation enhancement. </td>
*   </tr>
*   <tr>
*     <td>1.30</td>
*     <td>Added new option to Swap Overflow/Underflow behavior in PWM Centre/Asymmetric Alignment modes.</td>
*     <td>New feature.</td>
*   </tr>
*   <tr>
*     <td>1.20</td>
*     <td>Added new features: Shift Register, New QuadDec modes, Additional Compare/Capture Buffer.</td>
*     <td>New silicon family support.</td>
*   </tr>
*   <tr>
*     <td>1.10.2</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Added header guards CY_IP_MXTCPWM.</td>
*     <td>To enable the PDL compilation with wounded out IP blocks.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.10</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>1.0.1</td>
*     <td>Added a deviation to the MISRA Compliance section.
*         Added function-level code snippets.</td>
*     <td>Documentation update and clarification</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*/

/** \} group_tcpwm */

/**
* \addtogroup group_tcpwm_common
* Common API for the Timer Counter PWM Block.
*
* This is the common API that provides an interface to the TCPWM hardware.
* The Timer Counter, PWM, and Quadrature Decoder drivers use this common API.
* Most users will use individual drivers and do not need to use the common
* API for the TCPWM.
*
* The functions and other declarations used in this part of the driver are in cy_tcpwm.h.
* Include either of cy_tcpwm_counter.h, cy_tcpwm_pwm.h, cy_tcpwm_quaddec.h
* depending on the desired functionality. You can also include cy_pdl.h
* to get access to all functions and declarations in the PDL.
*
* \{
* \defgroup group_tcpwm_macros_common           Macros
* \defgroup group_tcpwm_functions_common        Functions
* \defgroup group_tcpwm_data_structures_common  Data Structures
* \defgroup group_tcpwm_enums Enumerated Types
*/


#if !defined(CY_TCPWM_H)
#define CY_TCPWM_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "cy_syslib.h"
#include "cy_device_headers.h"
#include "cy_device.h"

#ifdef CY_IP_MXTCPWM

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_tcpwm_macros_common
* \{
*/

/** Driver major version */
#define CY_TCPWM_DRV_VERSION_MAJOR       1

/** Driver minor version */
#define CY_TCPWM_DRV_VERSION_MINOR       40


/******************************************************************************
* API Constants
******************************************************************************/

/** TCPWM driver identifier */
#define CY_TCPWM_ID                     (CY_PDL_DRV_ID(0x2DU))

/** \defgroup group_tcpwm_input_selection  TCPWM Input Selection
* \{
* Selects which input to use
*/
#define CY_TCPWM_INPUT_0                (0U)  /**< Input is tied to logic 0 */
#define CY_TCPWM_INPUT_1                (1U)  /**< Input is tied to logic 1 */
#define CY_TCPWM_INPUT_TRIG_0           (2U)  /**< Input is connected to the trigger input 0 */
#define CY_TCPWM_INPUT_TRIG_1           (3U)  /**< Input is connected to the trigger input 1 */
#define CY_TCPWM_INPUT_TRIG_2           (4U)  /**< Input is connected to the trigger input 2 */
#define CY_TCPWM_INPUT_TRIG_3           (5U)  /**< Input is connected to the trigger input 3 */
#define CY_TCPWM_INPUT_TRIG_4           (6U)  /**< Input is connected to the trigger input 4 */
#define CY_TCPWM_INPUT_TRIG_5           (7U)  /**< Input is connected to the trigger input 5 */
#define CY_TCPWM_INPUT_TRIG_6           (8U)  /**< Input is connected to the trigger input 6 */
#define CY_TCPWM_INPUT_TRIG_7           (9U)  /**< Input is connected to the trigger input 7 */
#define CY_TCPWM_INPUT_TRIG_8           (10U) /**< Input is connected to the trigger input 8 */
#define CY_TCPWM_INPUT_TRIG_9           (11U) /**< Input is connected to the trigger input 9 */
#define CY_TCPWM_INPUT_TRIG_10          (12U) /**< Input is connected to the trigger input 10 */
#define CY_TCPWM_INPUT_TRIG_11          (13U) /**< Input is connected to the trigger input 11 */
#define CY_TCPWM_INPUT_TRIG_12          (14U) /**< Input is connected to the trigger input 12 */
#define CY_TCPWM_INPUT_TRIG_13          (15U) /**< Input is connected to the trigger input 13 */

#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined(CY_DOXYGEN)
#define CY_TCPWM_INPUT_TRIG(n) (n + TCPWM_TR_ONE_CNT_NR + 2U) /**< Input is connected to the trigger input n - all purpose trigger */
#endif

/** Input is defined by Creator, and Init() function does not need to configure input */
#define CY_TCPWM_INPUT_CREATOR          (0xFFFFFFFFU)
/** \} group_tcpwm_input_selection */

/**
* \defgroup group_tcpwm_input_modes  Input Modes
* \{
* Configures how TCPWM inputs behave
*/
/** A rising edge triggers the event (Capture, Start, Reload, etc..) */
#define CY_TCPWM_INPUT_RISINGEDGE       (0U)
/** A falling edge triggers the event (Capture, Start, Reload, etc..) */
#define CY_TCPWM_INPUT_FALLINGEDGE      (1U)
/** A rising edge or falling edge triggers the event (Capture, Start, Reload, etc..) */
#define CY_TCPWM_INPUT_EITHEREDGE       (2U)
/** The event is triggered on each edge of the TCPWM clock if the input is high */
#define CY_TCPWM_INPUT_LEVEL            (3U)
/** \} group_tcpwm_input_modes */

/**
* \defgroup group_tcpwm_output_trigger_modes  Output Trigger Modes
* \{
* Configures how TCPWM output triggers behave (TCPWM_v2 only)
*/
/** Output trigger generates signal on overflow event */
#define CY_TCPWM_CNT_TRIGGER_ON_OVERFLOW    (0U)
/** Output trigger generates signal on underflow event */
#define CY_TCPWM_CNT_TRIGGER_ON_UNDEFLOW    (1U)
/** Output trigger generates signal on terminal count event */
#define CY_TCPWM_CNT_TRIGGER_ON_TC          (2U)
/** Output trigger generates signal on compare/capture 0 event */
#define CY_TCPWM_CNT_TRIGGER_ON_CC0_MATCH   (3U)
/** Output trigger generates signal on compare/capture 1 event */
#define CY_TCPWM_CNT_TRIGGER_ON_CC1_MATCH   (4U)
/** Output trigger generates the same signal as line_out */
#define CY_TCPWM_CNT_TRIGGER_ON_LINE_OUT    (5U)
/** Output trigger disabled */
#define CY_TCPWM_CNT_TRIGGER_ON_DISABLED    (7U)
/** \} group_tcpwm_output_trigger_modes */

/**
* \defgroup group_tcpwm_interrupt_sources  Interrupt Sources
* \{
* Interrupt Sources
*/
#define CY_TCPWM_INT_NONE               (0U) /**< No Interrupt */
#define CY_TCPWM_INT_ON_TC              (1U) /**< Interrupt on Terminal count(TC) */
#define CY_TCPWM_INT_ON_CC0             (2U) /**< Interrupt on Compare 0/Capture 0(CC0) */
#define CY_TCPWM_INT_ON_CC0_OR_TC       (3U) /**< Interrupt on TC or CC0 */
#define CY_TCPWM_INT_ON_CC1             (4U) /**< Interrupt on Compare 1/Capture 1(CC1)*/
/** \} group_tcpwm_interrupt_sources */

/***************************************
*        Registers Constants
***************************************/

/**
* \defgroup group_tcpwm_reg_const Default registers constants
* \{
* Default constants for CNT Registers
*/
#define CY_TCPWM_CNT_CTRL_DEFAULT               (0x0U) /**< Default value for CTRL register */
#define CY_TCPWM_CNT_COUNTER_DEFAULT            (0x0U) /**< Default value for COUNTER register */
#define CY_TCPWM_CNT_CC_DEFAULT                 (0xFFFFFFFFU) /**< Default value for CC register */
#define CY_TCPWM_CNT_CC_BUFF_DEFAULT            (0xFFFFFFFFU) /**< Default value for CC_BUFF register */
#define CY_TCPWM_CNT_PERIOD_DEFAULT             (0xFFFFFFFFU) /**< Default value for PERIOD register */
#define CY_TCPWM_CNT_PERIOD_BUFF_DEFAULT        (0xFFFFFFFFU) /**< Default value for PERIOD_BUFF register */
#define CY_TCPWM_CNT_TR_CTRL0_DEFAULT           (0x10U)  /**< Default value for TR_CTRL0 register */
#define CY_TCPWM_CNT_TR_CTRL1_DEFAULT           (0x3FFU) /**< Default value for TR_CTRL1 register */
#define CY_TCPWM_CNT_TR_CTRL2_DEFAULT           (0x3FU)  /**< Default value for TR_CTRL2 register */
#define CY_TCPWM_CNT_INTR_DEFAULT               (0x3U)   /**< Default value for INTR register */
#define CY_TCPWM_CNT_INTR_SET_DEFAULT           (0x0U)   /**< Default value for INTR_SET register */
#define CY_TCPWM_CNT_INTR_MASK_DEFAULT          (0x0U)   /**< Default value for INTR_MASK register */

#define CY_TCPWM_GRP_CNT_CTRL_DEFAULT            (0xF0U)  /**< Default value for CTRL register */
#define CY_TCPWM_GRP_CNT_DT_DEFAULT                (0x0U)   /**< Default value for DT register */
#define CY_TCPWM_GRP_CNT_COUNTER_DEFAULT        (0x0U)   /**< Default value for COUNTER register */
#define CY_TCPWM_GRP_CNT_CC0_DEFAULT            (0xFFFFFFFFU) /**< Default value for CC0 register */
#define CY_TCPWM_GRP_CNT_CC0_BUFF_DEFAULT        (0xFFFFFFFFU) /**< Default value for CC0_BUFF register */
#define CY_TCPWM_GRP_CNT_CC1_DEFAULT            (0xFFFFFFFFU) /**< Default value for CC0 register */
#define CY_TCPWM_GRP_CNT_CC1_BUFF_DEFAULT        (0xFFFFFFFFU) /**< Default value for CC0_BUFF register */
#define CY_TCPWM_GRP_CNT_PERIOD_DEFAULT            (0xFFFFFFFFU) /**< Default value for PERIOD register */
#define CY_TCPWM_GRP_CNT_PERIOD_BUFF_DEFAULT    (0xFFFFFFFFU) /**< Default value for PERIOD_BUFF register */
#define CY_TCPWM_GRP_CNT_TR_PWM_CTRL_DEFAULT    (0xFFFU) /**< Default value for TR_PWM_CTRL register */
#define CY_TCPWM_GRP_CNT_TR_IN_SEL0_DEFAULT        (0x100U) /**< Default value for TR_IN_SEL0 register */
#define CY_TCPWM_GRP_CNT_TR_IN_SEL1_DEFAULT        (0x0U)   /**< Default value for TR_IN_SEL1 register */
#define CY_TCPWM_GRP_CNT_TR_IN_EDGE_SEL_DEFAULT    (0xFFFU) /**< Default value for TR_IN_EDGE_SEL register */
#define CY_TCPWM_GRP_CNT_INTR_MASK_DEFAULT        (0x0U)     /**< Default value for INTR_MASK register */

/** \} group_tcpwm_reg_const */

/** Position of Up counting counter status */
#define CY_TCPWM_CNT_STATUS_UP_POS          (0x1U)
/** Initial value for the counter in the Up counting mode */
#define CY_TCPWM_CNT_UP_INIT_VAL            (0x0U)
/** Initial value for the counter in the Up/Down counting modes */
#define CY_TCPWM_CNT_UP_DOWN_INIT_VAL       (0x1U)
/** \} group_tcpwm_macros_common */


/*******************************************************************************
 * Enumerations
 ******************************************************************************/

 /**
* \addtogroup group_tcpwm_enums
* \{
*/

/** TCPWM Input Triggers */
typedef enum
{
    CY_TCPWM_INPUT_TR_START           = 0x00U,  /**< Start */
    CY_TCPWM_INPUT_TR_RELOAD_OR_INDEX = 0x01U,  /**< Reload/Index */
    CY_TCPWM_INPUT_TR_STOP_OR_KILL    = 0x02U,  /**< Stop/Kill */
    CY_TCPWM_INPUT_TR_COUNT           = 0x03U,  /**< Count */
    CY_TCPWM_INPUT_TR_INDEX_OR_SWAP   = 0x04U,  /**< Index/Swap */
    CY_TCPWM_INPUT_TR_CAPTURE0        = 0x04U,  /**< Capture 0 */
    CY_TCPWM_INPUT_TR_CAPTURE1        = 0x05U   /**< Capture 1 */
} cy_en_tcpwm_trigselect_t;

/** TCPWM status definitions */
typedef enum
{
    CY_TCPWM_SUCCESS = 0x00U,                                           /**< Successful */
    CY_TCPWM_BAD_PARAM = CY_TCPWM_ID | CY_PDL_STATUS_ERROR | 0x01U,     /**< One or more invalid parameters */
    CY_TCPWM_UNSUPPORTED_FEATURE = CY_TCPWM_ID | CY_PDL_STATUS_ERROR | 0x02U,  /**< Feature Unsupported */
} cy_en_tcpwm_status_t;
/** \} group_tcpwm_enums */

/*******************************************************************************
*        Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_tcpwm_functions_common
* \{
*/

#if (CY_IP_MXTCPWM_VERSION == 1U) || defined(CY_DOXYGEN)
__STATIC_INLINE void Cy_TCPWM_Enable_Multiple(TCPWM_Type *base, uint32_t counters);
__STATIC_INLINE void Cy_TCPWM_Disable_Multiple(TCPWM_Type *base, uint32_t counters);
__STATIC_INLINE void Cy_TCPWM_TriggerStart(TCPWM_Type *base, uint32_t counters);
__STATIC_INLINE void Cy_TCPWM_TriggerReloadOrIndex(TCPWM_Type *base, uint32_t counters);
__STATIC_INLINE void Cy_TCPWM_TriggerStopOrKill(TCPWM_Type *base, uint32_t counters);
__STATIC_INLINE void Cy_TCPWM_TriggerCaptureOrSwap(TCPWM_Type *base, uint32_t counters);
#endif
__STATIC_INLINE void Cy_TCPWM_Enable_Single(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Disable_Single(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_GetInterruptStatus(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_ClearInterrupt(TCPWM_Type *base, uint32_t cntNum, uint32_t source);
__STATIC_INLINE void Cy_TCPWM_SetInterrupt(TCPWM_Type *base, uint32_t cntNum, uint32_t source);
__STATIC_INLINE void Cy_TCPWM_SetInterruptMask(TCPWM_Type *base, uint32_t cntNum, uint32_t mask);
__STATIC_INLINE uint32_t Cy_TCPWM_GetInterruptMask(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_GetInterruptStatusMasked(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_TriggerStart_Single(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_TriggerReloadOrIndex_Single(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_TriggerStopOrKill_Single(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_TriggerCaptureOrSwap_Single(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_TriggerCapture0(TCPWM_Type *base, uint32_t cntNum);
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined(CY_DOXYGEN)
__STATIC_INLINE void Cy_TCPWM_TriggerCapture1(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE bool Cy_TCPWM_GetTrigPinLevel (TCPWM_Type const *base, uint32_t cntNum, cy_en_tcpwm_trigselect_t triggerSelect);
__STATIC_INLINE void Cy_TCPWM_InputTriggerSetup (TCPWM_Type *base, uint32 cntNum, cy_en_tcpwm_trigselect_t triggerSelect, uint32_t edgeSelect, uint32_t triggerSignal);
__STATIC_INLINE cy_en_tcpwm_status_t Cy_TCPWM_SetDebugFreeze (TCPWM_Type *base, uint32 cntNum, bool enable);
#endif
/** \cond INTERNAL */
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCC0Val(TCPWM_Type const  *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCC0BufVal(TCPWM_Type const  *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCounter(TCPWM_Type const  *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Block_SetCounter(TCPWM_Type *base, uint32_t cntNum, uint32_t count);
__STATIC_INLINE void Cy_TCPWM_Block_SetPeriod(TCPWM_Type *base, uint32_t cntNum,  uint32_t period);
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetPeriod(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Block_SetCC0BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare1);
__STATIC_INLINE void Cy_TCPWM_Block_SetCC0Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare0);
__STATIC_INLINE void Cy_TCPWM_Block_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable);
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
__STATIC_INLINE void Cy_TCPWM_Block_EnableCompare1Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable);
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCC1Val(TCPWM_Type const  *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCC1BufVal(TCPWM_Type const  *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Block_SetCC1BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compareBuf1);
__STATIC_INLINE void Cy_TCPWM_Block_SetCC1Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare1);
#endif

/** \endcond */

/** \cond INTERNAL */
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCC0Val(TCPWM_Type const  *base, uint32_t cntNum)
{
    uint32_t result;

#if    (CY_IP_MXTCPWM_VERSION == 1U)
        result = (TCPWM_CNT_CC(base, cntNum));
#else
       result = (TCPWM_GRP_CNT_CC0(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum));
#endif
    return result;
}
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCC0BufVal(TCPWM_Type const  *base, uint32_t cntNum)
{
    uint32_t result;

#if    (CY_IP_MXTCPWM_VERSION == 1U)
        result = (TCPWM_CNT_CC_BUFF(base, cntNum));
#else
        result = (TCPWM_GRP_CNT_CC0_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum));
#endif

    return result;
}
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCounter(TCPWM_Type const  *base, uint32_t cntNum)
{
    uint32_t result;

#if    (CY_IP_MXTCPWM_VERSION == 1U)
        result = TCPWM_CNT_COUNTER(base, cntNum);
#else
        result = TCPWM_GRP_CNT_COUNTER(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
#endif

    return result;
}
__STATIC_INLINE void Cy_TCPWM_Block_SetCounter(TCPWM_Type *base, uint32_t cntNum, uint32_t count)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CNT_COUNTER(base, cntNum) = count;
#else
        TCPWM_GRP_CNT_COUNTER(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = count;
#endif
}
__STATIC_INLINE void Cy_TCPWM_Block_SetPeriod(TCPWM_Type *base, uint32_t cntNum,  uint32_t period)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CNT_PERIOD(base, cntNum) = period;
#else
        TCPWM_GRP_CNT_PERIOD(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = period;
#endif
}
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetPeriod(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t result;

#if    (CY_IP_MXTCPWM_VERSION == 1U)

        result = TCPWM_CNT_PERIOD(base, cntNum);
#else
        result = TCPWM_GRP_CNT_PERIOD(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
#endif
    return result;
}
__STATIC_INLINE void Cy_TCPWM_Block_SetCC0BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare1)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)
        TCPWM_CNT_CC_BUFF(base, cntNum) = compare1;
#else
        TCPWM_GRP_CNT_CC0_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = compare1;
#endif
}
__STATIC_INLINE void Cy_TCPWM_Block_SetCC0Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare0)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)
        TCPWM_CNT_CC(base, cntNum) = compare0;
#else
        TCPWM_GRP_CNT_CC0(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = compare0;
#endif
}
__STATIC_INLINE void Cy_TCPWM_Block_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        if (enable)
        {
            TCPWM_CNT_CTRL(base, cntNum) |=  TCPWM_CNT_CTRL_AUTO_RELOAD_CC_Msk;
        }
        else
        {
            TCPWM_CNT_CTRL(base, cntNum) &= ~TCPWM_CNT_CTRL_AUTO_RELOAD_CC_Msk;
        }
#else
        if (enable)
        {
            TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) |=
                                    TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC0_Msk;
        }
        else
        {
            TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) &=
                                    ~TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC0_Msk;
        }
#endif
}
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
__STATIC_INLINE void Cy_TCPWM_Block_EnableCompare1Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
    if (TCPWM_GRP_CC1(base, TCPWM_GRP_CNT_GET_GRP(cntNum)))
    {
        if (enable)
        {
            TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) |=
                                    TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC1_Msk;
        }
        else
        {
            TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) &=
                                    ~TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC1_Msk;
        }
    }
}
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCC1Val(TCPWM_Type const  *base, uint32_t cntNum)
{
    uint32_t result = 0UL;

    if (TCPWM_GRP_CC1(base, TCPWM_GRP_CNT_GET_GRP(cntNum)))
    {
        result = TCPWM_GRP_CNT_CC1(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
    }

    return result;
}
__STATIC_INLINE uint32_t Cy_TCPWM_Block_GetCC1BufVal(TCPWM_Type const  *base, uint32_t cntNum)
{
    uint32_t result = 0UL;

    if (TCPWM_GRP_CC1(base, TCPWM_GRP_CNT_GET_GRP(cntNum)))
    {
        result = TCPWM_GRP_CNT_CC1_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
    }

    return result;
}
__STATIC_INLINE void Cy_TCPWM_Block_SetCC1BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compareBuf1)
{
    if (TCPWM_GRP_CC1(base, TCPWM_GRP_CNT_GET_GRP(cntNum)))
    {
        TCPWM_GRP_CNT_CC1_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = compareBuf1;
    }
}
__STATIC_INLINE void Cy_TCPWM_Block_SetCC1Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare1)
{
    if (TCPWM_GRP_CC1(base, TCPWM_GRP_CNT_GET_GRP(cntNum)))
    {
        TCPWM_GRP_CNT_CC1(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = compare1;
    }
}
#endif
/** \endcond */
#if (CY_IP_MXTCPWM_VERSION == 1U) || defined(CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_TCPWM_Enable_Multiple
****************************************************************************//**
*
* Enables the counter(s) in the TCPWM block. Multiple blocks can be started
* simultaneously.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param counters
* A bit field representing each counter in the TCPWM block.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_Enable_Multiple
*
* \note supported only in TCPWM_ver1
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Enable_Multiple(TCPWM_Type *base, uint32_t counters)
{
    TCPWM_CTRL_SET(base) = counters;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Disable_Multiple
****************************************************************************//**
*
* Disables the counter(s) in the TCPWM block. Multiple TCPWM can be disabled
* simultaneously.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param counters
* A bit field representing each counter in the TCPWM block.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_Disable_Multiple
*
* \note supported only in TCPWM_ver1
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Disable_Multiple(TCPWM_Type *base, uint32_t counters)
{
    TCPWM_CTRL_CLR(base) = counters;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerStart
****************************************************************************//**
*
* Triggers a software start on the selected TCPWMs.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param counters
* A bit field representing each counter in the TCPWM block.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_Enable_Multiple
*
* \note supported only in TCPWM_ver1
*
*******************************************************************************/
__STATIC_INLINE  void Cy_TCPWM_TriggerStart(TCPWM_Type *base, uint32_t counters)
{
    TCPWM_CMD_START(base) = counters;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerReloadOrIndex
****************************************************************************//**
*
* Triggers a software reload event (or index in QuadDec mode).
*
* \param base
* The pointer to a TCPWM instance
*
* \param counters
* A bit field representing each counter in the TCPWM block.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_TriggerReloadOrIndex
*
* \note supported only in TCPWM_ver1
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_TriggerReloadOrIndex(TCPWM_Type *base, uint32_t counters)
{
    TCPWM_CMD_RELOAD(base) = counters;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerStopOrKill
****************************************************************************//**
*
* Triggers a stop in the Timer Counter mode, or a kill in the PWM mode.
*
* \note The kill trigger behavior for PWM is defined by the
* \ref cy_stc_tcpwm_pwm_config_t::killMode field. The pins states after a kill
* trigger are defined by \ref cy_stc_tcpwm_pwm_config_t::invertPWMOut and
* \ref cy_stc_tcpwm_pwm_config_t::invertPWMOutN fields.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param counters
* A bit field representing each counter in the TCPWM block.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_TriggerStopOrKill
*
* \note supported only in TCPWM_ver1
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_TriggerStopOrKill(TCPWM_Type *base, uint32_t counters)
{
    TCPWM_CMD_STOP(base) = counters;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerCaptureOrSwap
****************************************************************************//**
*
* Triggers a Capture in the Timer Counter mode, and a Swap in the PWM mode.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param counters
* A bit field representing each counter in the TCPWM block.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_Capture
*
* \note supported only in TCPWM_ver1
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_TriggerCaptureOrSwap(TCPWM_Type *base, uint32_t counters)
{
    TCPWM_CMD_CAPTURE(base) = counters;
}
#endif
/*******************************************************************************
* Function Name: Cy_TCPWM_Enable_Single
****************************************************************************//**
*
* Enables specified counter
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
*******************************************************************************/

__STATIC_INLINE void Cy_TCPWM_Enable_Single(TCPWM_Type *base, uint32_t cntNum)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

    TCPWM_CTRL_SET(base) = (1UL << cntNum);
#else

    TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) |=
                _VAL2FLD(TCPWM_GRP_CNT_V2_CTRL_ENABLED, 1U);
#endif
}

/*******************************************************************************
* Function Name: Cy_TCPWM_Disable_Single
****************************************************************************//**
*
* Disable specified counter
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Disable_Single(TCPWM_Type *base, uint32_t cntNum)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)
        TCPWM_CTRL_CLR(base) = (1UL << cntNum);
#else
        TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) &=
                ~TCPWM_GRP_CNT_V2_CTRL_ENABLED_Msk;
#endif
}

/*******************************************************************************
* Function Name: Cy_TCPWM_GetInterruptStatus
****************************************************************************//**
*
* Returns which event triggered the interrupt.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* See \ref group_tcpwm_interrupt_sources
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_GetInterruptStatus
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_GetInterruptStatus(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t result;

#if    (CY_IP_MXTCPWM_VERSION == 1U)

        result = TCPWM_CNT_INTR(base, cntNum);
#else
        result = TCPWM_GRP_CNT_INTR(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
#endif

    return result;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ClearInterrupt
****************************************************************************//**
*
* Clears Active Interrupt Source
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param source
* source to clear. See \ref group_tcpwm_interrupt_sources
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_GetInterruptStatusMasked
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_ClearInterrupt(TCPWM_Type *base, uint32_t cntNum,  uint32_t source)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CNT_INTR(base, cntNum) = source;
        (void)TCPWM_CNT_INTR(base, cntNum);
#else
        TCPWM_GRP_CNT_INTR(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = source;
        (void)TCPWM_GRP_CNT_INTR(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
#endif
}


/*******************************************************************************
* Function Name: Cy_TCPWM_SetInterrupt
****************************************************************************//**
*
* Triggers an interrupt via a software write.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param source
* The source to set an interrupt. See \ref group_tcpwm_interrupt_sources.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_SetInterrupt
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_SetInterrupt(TCPWM_Type *base, uint32_t cntNum,  uint32_t source)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CNT_INTR_SET(base, cntNum) = source;
#else
        TCPWM_GRP_CNT_INTR_SET(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = source;
#endif
}


/*******************************************************************************
* Function Name: Cy_TCPWM_SetInterruptMask
****************************************************************************//**
*
* Sets an interrupt mask. A 1 means that when the event occurs, it will cause an
* interrupt; a 0 means no interrupt will be triggered.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param mask
*. See \ref group_tcpwm_interrupt_sources
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_SetInterruptMask
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_SetInterruptMask(TCPWM_Type *base, uint32_t cntNum, uint32_t mask)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CNT_INTR_MASK(base, cntNum) = mask;
#else
        TCPWM_GRP_CNT_INTR_MASK(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = mask;
#endif
}


/*******************************************************************************
* Function Name: Cy_TCPWM_GetInterruptMask
****************************************************************************//**
*
* Returns the interrupt mask.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Interrupt Mask. See \ref group_tcpwm_interrupt_sources
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_SetInterruptMask
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_GetInterruptMask(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t mask;

#if    (CY_IP_MXTCPWM_VERSION == 1U)

        mask = TCPWM_CNT_INTR_MASK(base, cntNum);
#else
        mask = TCPWM_GRP_CNT_INTR_MASK(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
#endif

    return mask;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_GetInterruptStatusMasked
****************************************************************************//**
*
* Returns which masked interrupt triggered the interrupt.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Interrupt Mask. See \ref group_tcpwm_interrupt_sources
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_GetInterruptStatusMasked
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_GetInterruptStatusMasked(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t status;

#if    (CY_IP_MXTCPWM_VERSION == 1U)

        status = TCPWM_CNT_INTR_MASKED(base, cntNum);
#else
        status = TCPWM_GRP_CNT_INTR_MASKED(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
#endif

    return status;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerStart_Single
****************************************************************************//**
*
*  Triggers a software start on the selected TCPWM.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \funcusage
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_Start
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_TriggerStart_Single(TCPWM_Type *base, uint32_t cntNum)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CMD_START(base) = (1UL << cntNum);
#else
        TCPWM_GRP_CNT_TR_CMD(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) =
                TCPWM_GRP_CNT_V2_TR_CMD_START_Msk;
#endif
}


/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerReloadOrIndex_Single
****************************************************************************//**
*
* Triggers a software reload event (or index 0 in QuadDec mode) on selected TCPWM.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_TriggerReloadOrIndex_Single(TCPWM_Type *base, uint32_t cntNum)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CMD_RELOAD(base) = (1UL << cntNum);
#else
        TCPWM_GRP_CNT_TR_CMD(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) =
                TCPWM_GRP_CNT_V2_TR_CMD_RELOAD_Msk;
#endif
}


/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerStopOrKill_Single
****************************************************************************//**
*
* Triggers a stop in the Timer Counter mode, or a kill in the PWM mode on
* selected TCPWM.
*
* \note The kill trigger behavior for PWM is defined by the
* \ref cy_stc_tcpwm_pwm_config_t::killMode field. The pins states after a kill
* trigger are defined by \ref cy_stc_tcpwm_pwm_config_t::invertPWMOut and
* \ref cy_stc_tcpwm_pwm_config_t::invertPWMOutN fields.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_TriggerStopOrKill_Single(TCPWM_Type *base, uint32_t cntNum)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CMD_STOP(base) = (1UL << cntNum);
#else
        TCPWM_GRP_CNT_TR_CMD(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) =
                TCPWM_GRP_CNT_V2_TR_CMD_STOP_Msk;
#endif
}


/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerCaptureOrSwap_Single
****************************************************************************//**
*
* Triggers a Capture 0 in the Timer Counter mode, and a Swap in the PWM mode on
* selected TCPWM.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_TriggerCaptureOrSwap_Single(TCPWM_Type *base, uint32_t cntNum)
{
#if    (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CMD_CAPTURE(base) = (1UL << cntNum);
#else
        TCPWM_GRP_CNT_TR_CMD(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) =
                TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE0_Msk;
#endif
}

/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerCapture0
****************************************************************************//**
*
* Triggers a Capture 0 on the selected counter.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_TriggerCapture0(TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_TriggerCaptureOrSwap_Single(base, cntNum);
}

#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_TCPWM_TriggerCapture1
****************************************************************************//**
*
* Triggers a Capture 1 in Timer Counter and QuadDec Mode. In PWM mode this acts
* as a second kill input.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_TriggerCapture1(TCPWM_Type *base, uint32_t cntNum)
{
    if (TCPWM_GRP_CC1(base, TCPWM_GRP_CNT_GET_GRP(cntNum)))
    {
        TCPWM_GRP_CNT_TR_CMD(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) =
                                                TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE1_Msk;
    }
    else
    {
        /* Function is not supported for TCPWM_ver1 block */
        CY_ASSERT_L1(false);
    }
}


/*******************************************************************************
* Function Name: Cy_TCPWM_GetTrigPinLevel
****************************************************************************//**
*
* Returns the current level of the selected input trigger.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param triggerSelect
* Defines which trigger status is being checked, Start, Reload, Stop/Kill, Count, Capture 0 or Capture 1
*
* \return
* The trigger level
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_GetTrigPinLevel
*
*******************************************************************************/
__STATIC_INLINE bool Cy_TCPWM_GetTrigPinLevel (TCPWM_Type const *base, uint32_t cntNum, cy_en_tcpwm_trigselect_t triggerSelect)

{
    uint32_t status = 0UL;

    status = TCPWM_GRP_CNT_STATUS(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);

    switch(triggerSelect)
    {
        case CY_TCPWM_INPUT_TR_START:
            status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_TR_START, status);
            break;
        case CY_TCPWM_INPUT_TR_RELOAD_OR_INDEX:
            status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_TR_RELOAD, status);
            break;
        case CY_TCPWM_INPUT_TR_STOP_OR_KILL:
            status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_TR_RELOAD, status);
            break;
        case CY_TCPWM_INPUT_TR_COUNT:
            status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_TR_STOP, status);
            break;
        case CY_TCPWM_INPUT_TR_CAPTURE0:
            status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE0, status);
            break;
        case CY_TCPWM_INPUT_TR_CAPTURE1:
            status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE1, status);
            break;
        default:
            /* Not a valid input trigger */
            CY_ASSERT_L3(false);
            break;
   }


    return (status != 0UL);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_InputTriggerSetup
****************************************************************************//**
*
* Sets up a trigger input signal for a specific TCPWM counter. This API is used to
* handle software triggering of multiple counters synchronously.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param triggerSelect
* Defines which trigger is being setup, Start, Reload, Stop/Kill, Count, Capture 0 or Capture 1
* see cy_en_tcpwm_trigselect_t
*
* \param edgeSelect
* Sets the trigger edge detection, Rising, Falling, Both, No edge detect. see \ref group_tcpwm_input_modes
*
* \param triggerSignal
* Selects what trigger signal is connected to the selected input trigger.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_InputTriggerSetup
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_InputTriggerSetup (TCPWM_Type *base, uint32 cntNum, cy_en_tcpwm_trigselect_t triggerSelect, uint32_t edgeSelect, uint32_t triggerSignal)
{
    uint32_t grp = TCPWM_GRP_CNT_GET_GRP(cntNum);

    switch(triggerSelect)
    {
        case CY_TCPWM_INPUT_TR_START:
            /* Clear input trigger settings first */
            TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE_Msk;

            /* Write new settings */
            TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL, triggerSignal);
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE, edgeSelect);
            break;
        case CY_TCPWM_INPUT_TR_RELOAD_OR_INDEX:
            TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE_Msk;

            TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL, triggerSignal);
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE, edgeSelect);
            break;
        case CY_TCPWM_INPUT_TR_STOP_OR_KILL:
            TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE_Msk;

            TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL, triggerSignal);
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE, edgeSelect);
            break;
        case CY_TCPWM_INPUT_TR_COUNT:
            TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE_Msk;

            TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL, triggerSignal);
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE, edgeSelect);
            break;
        case CY_TCPWM_INPUT_TR_CAPTURE0:
            TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL_Msk;
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Msk;

            TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL, triggerSignal);
            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE, edgeSelect);
            break;
        case CY_TCPWM_INPUT_TR_CAPTURE1:
            if (TCPWM_GRP_CC1(base, grp))
            {
                TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_SEL1_CAPTURE1_SEL_Msk;
                TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) &= ~TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Msk;

                TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL1_CAPTURE1_SEL, triggerSignal);
                TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) |= _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE1_EDGE, edgeSelect);
            }
            else
            {
                /* Capture 1 - Not supported for the group */
                CY_ASSERT_L3(false);
            }
            break;
        default:
            /* Not a valid input trigger */
            CY_ASSERT_L3(false);
            break;
   }

}


/*******************************************************************************
* Function Name: Cy_TCPWM_SetDebugFreeze
****************************************************************************//**
*
* Enables/disables the Debug Freeze feature for the specified counter.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param enable
* true: The Debug Free feature is enabled
* false: The Debug Freeze feature is disabled
*
* \return
* Error / Status code. See cy_en_tcpwm_status_t.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_SetDebugFreeze
*
*******************************************************************************/
__STATIC_INLINE cy_en_tcpwm_status_t Cy_TCPWM_SetDebugFreeze (TCPWM_Type *base, uint32 cntNum, bool enable)
{

    TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) |= (enable ? TCPWM_GRP_CNT_V2_CTRL_DBG_FREEZE_EN_Msk : 0UL);

    return CY_TCPWM_SUCCESS;
}
#endif

/** \} group_tcpwm_functions_common */

/** \} group_tcpwm_common */

/*******************************************************************************
* Backward compatibility macro. The following code is DEPRECATED and must
* not be used in new projects
*******************************************************************************/
#define CY_TCPWM_INT_ON_CC              CY_TCPWM_INT_ON_CC0
#define CY_TCPWM_INT_ON_CC_OR_TC        CY_TCPWM_INT_ON_CC0_OR_TC

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXTCPWM */

#endif /* CY_TCPWM_H */

/* [] END OF FILE */
