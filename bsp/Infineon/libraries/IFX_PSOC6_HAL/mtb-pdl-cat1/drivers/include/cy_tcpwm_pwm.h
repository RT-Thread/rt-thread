/***************************************************************************//**
* \file cy_tcpwm_pwm.h
* \version 1.40
*
* \brief
* The header file of the TCPWM PWM driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2021 Cypress Semiconductor Corporation
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

#if !defined(CY_TCPWM_PWM_H)
#define CY_TCPWM_PWM_H

#include "cy_tcpwm.h"

#ifdef CY_IP_MXTCPWM

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_tcpwm_pwm
* Driver API for PWM.
*
* The functions and other declarations used in this part of the driver are in cy_tcpwm_pwm.h.
* You can also include cy_pdl.h to get access to all
* functions and declarations in the PDL.
*
* Use PWM mode when an output square wave is needed with a specific
* period and duty cycle, such as:
* * Creating arbitrary square wave outputs
* * Driving an LED (changing the brightness)
* * Driving Motors (dead time assertion available)
*
* The PWM has the following features:
* * 16- or 32-bit Counter.
* * Two Programmable Period registers that can be swapped.
* * Two Output Compare registers that can be swapped on overflow and/or
* underflow.
* * Left Aligned, Right Aligned, Center Aligned, and Asymmetric Aligned modes
* * Continuous or One Shot run modes.
* * Pseudo Random mode.
* * Two PWM outputs with Dead Time insertion, and programmable polarity.
* * Interrupt on Terminal Count and Compare or Capture 0. Interrupt on Compare or Capture 1 is only available in TCPWM Version 2.
* * Start, Reload, Stop, Swap (Capture), and Count Inputs.
* * Immediate Kill, Kill 0 Input, Kill 1 Input, PWM output on Disable, PWM outputs, PWM Dead Time Clocks,
* Taps Enabled. All these features are only available in TCPWM Version 2.
* * Multiple Components can be synchronized together for applications.
* such as three phase motor control.
* * Two programmable trigger outputs, trig_out0 and trig_out1 that generate a
* trigger on one of the following events Overflow, Underflow, Terminal Count,
* Compare Match 0/1, and PWM output. The available triggers are dependent on the PWM mode.
* All these features are only available in TCPWM Version 2.
* * Overflow, Underflow, and Compare(cc_match) trigger outputs are only available in TCPWM Version 1.
* * Second Compare Match (CC_MATCH1) event is only available in TCPWM Version 2.
*
* \section group_tcpwm_pwm_configuration Configuration Considerations
*
* The PWM configuration can be divided to number of sequential
* steps listed below:
* * \ref group_tcpwm_pwm_config
* * \ref group_tcpwm_pwm_clock
* * \ref group_tcpwm_pwm_enable
* * \ref group_tcpwm_pwm_start
*
* \subsection group_tcpwm_pwm_config Configure PWM
* To configure PWM, provide the configuration parameters in the
* \ref cy_stc_tcpwm_pwm_config_t structure. The Configuration structure
* can be modified through software, but if the configurator in ModusToolbox is used
* then the configuration structure will be updated with the users input. To initialize
* the driver, call \ref Cy_TCPWM_PWM_Init function providing a pointer to the populated
* \ref cy_stc_tcpwm_pwm_config_t structure.
*
* For TCPWM V1 Configuration
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_V1_PWM_Init
*
* For TCPWM V2 Configuration
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_V2_PWM_Init
*
* \subsection group_tcpwm_pwm_clock Assign Clock Divider
* The clock source must be connected to proper working.
* Any of the peripheral clock dividers could be used. Use the
* \ref group_sysclk driver API to do that.
*
* \subsection group_tcpwm_pwm_enable Enable PWM
* PWM has to be enabled before starting
*
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_Enable
*
* \subsection group_tcpwm_pwm_start Start PWM
* PWM has to be started
*
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_Start
* \{
*/

/**
* \defgroup group_tcpwm_macros_pwm          Macros
* \defgroup group_tcpwm_functions_pwm       Functions
* \defgroup group_tcpwm_data_structures_pwm Data Structures
* \} */

/**
* \addtogroup group_tcpwm_data_structures_pwm
* \{
*/

/** PWM configuration structure */
typedef struct cy_stc_tcpwm_pwm_config
{
    uint32_t    pwmMode;            /**< Sets the PWM mode. See \ref group_tcpwm_pwm_modes */
    /** Sets the clock prescaler inside the TCWPM block. See \ref group_tcpwm_pwm_clk_prescalers */
    uint32_t     clockPrescaler;
    uint32_t    pwmAlignment;       /**< Sets the PWM alignment. See \ref group_tcpwm_pwm_alignment */
    uint32_t    deadTimeClocks;     /**< The number of dead time-clocks if PWM with dead time is chosen */
    uint32_t    runMode;            /**< Sets the PWM run mode. See \ref group_tcpwm_pwm_run_modes */
    uint32_t    period0;            /**< Sets the period0 of the pwm */
    uint32_t    period1;            /**< Sets the period1 of the pwm */
    bool        enablePeriodSwap;   /**< Enables swapping of period 0 and period 1 on terminal count */
    uint32_t    compare0;           /**< Sets the value for Compare 0 */
    uint32_t    compare1;           /**< Sets the value for the buffered Compare 0 */
    bool        enableCompareSwap;  /**< If enabled, the compare values are swapped on the terminal count */
    /** Enables an interrupt on the terminal count, capture or compare. See \ref group_tcpwm_interrupt_sources */
    uint32_t    interruptSources;
    /** Inverts the PWM output. This field also defines the state of the PWM output while PWM is enabled, but not running. */
    uint32_t    invertPWMOut;
    /** Inverts the PWM_n output. This field also defines the state of the PWM_n output while PWM is enabled, but not running. */
    uint32_t    invertPWMOutN;
    uint32_t    killMode;           /**< Configures the PWM kill modes. See \ref group_tcpwm_pwm_kill_modes */
    uint32_t    swapInputMode;      /**< Configures how the swap input behaves. See \ref group_tcpwm_input_modes */
    /** Selects which input the swap uses. Inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    swapInput;
    uint32_t    reloadInputMode;    /**< Configures how the reload input behaves. See \ref group_tcpwm_input_modes */
    /** Selects which input the reload uses. The inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    reloadInput;
    uint32_t    startInputMode;     /**< Configures how the start input behaves. See \ref group_tcpwm_input_modes */
    /** Selects which input the start uses. The inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    startInput;
    uint32_t    killInputMode;      /**< Configures how the kill input behaves. See \ref group_tcpwm_input_modes */
    /** Selects which input the kill uses. The inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    killInput;
    uint32_t    countInputMode;     /**< Configures how the count input behaves. See \ref group_tcpwm_input_modes */
    /** Selects which input the count uses. The inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    countInput;
    /** If enabled, line output is set on underflow and cleared on overflow. This configuration is available only in center and asymmetric alignment modes. */
    bool        swapOverflowUnderflow;
#if (CY_IP_MXTCPWM_VERSION >= 2U)
    bool        immediateKill;      /**< Specifies whether the kill event immediately deactivates the dt_line_out and dt_line_compl_out or with the next module clock */
    uint32_t    tapsEnabled;        /**< In pseudo random mode sets the enabled taps */
    uint32_t    compare2;           /**< Sets the value for Compare1  */
    uint32_t    compare3;           /**< Sets the value for the buffered Compare1 */
    bool        enableCompare1Swap; /**< If enabled, the compare1 values are swapped on the terminal count */
    bool        compare0MatchUp;    /**< Enables/Disables the compare match 0 event generation when counting up in CNT_UPDN1/2 mode */
    bool        compare0MatchDown;  /**< Enables/Disables the compare match 0 event generation when counting down in CNT_UPDN1/2 mode */
    bool        compare1MatchUp;    /**< Enables/Disables the compare match 1 event generation when counting up in CNT_UPDN1/2 mode */
    bool        compare1MatchDown;  /**< Enables/Disables the compare match 1 event generation when counting down in CNT_UPDN1/2 mode */
    uint32_t    kill1InputMode;     /**< Configures how the kill 1 input behaves. See \ref group_tcpwm_input_modes */
    uint32_t    kill1Input;         /**< Selects which input the kill 1 uses. The inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    pwmOnDisable;       /**< Specifies the behavior of the PWM outputs line_out and line_compl_out while the TCPWM counter is disabled */
    uint32_t    trigger0Event;      /**< Configures which internal event generates on output trigger 0*/
    uint32_t    trigger1Event;        /**< Configures which internal event generates on output trigger 1*/
#endif
}cy_stc_tcpwm_pwm_config_t;
/** \} group_tcpwm_data_structures_pwm */

/**
* \addtogroup group_tcpwm_macros_pwm
* \{
* \defgroup group_tcpwm_pwm_run_modes PWM run modes
* \{
* Run modes for the pwm timer.
*/
#define CY_TCPWM_PWM_ONESHOT            (1U)    /**< Counter runs once and then stops */
#define CY_TCPWM_PWM_CONTINUOUS         (0U)    /**< Counter runs forever */
/** \} group_tcpwm_pwm_run_modes */

/** \defgroup group_tcpwm_pwm_modes PWM modes
* \{
* Sets the PWM modes.
*/
#define CY_TCPWM_PWM_MODE_PWM           (4U) /**< Standard PWM Mode*/
#define CY_TCPWM_PWM_MODE_DEADTIME      (5U)    /**< PWM with deadtime mode*/
#define CY_TCPWM_PWM_MODE_PSEUDORANDOM  (6U)    /**< Pseudo Random PWM */
/** \} group_tcpwm_pwm_modes */

/** \defgroup group_tcpwm_pwm_alignment PWM Alignment
* Sets the alignment of the PWM.
* \{
*/
#define CY_TCPWM_PWM_LEFT_ALIGN                         (0U)     /**< PWM is left aligned, meaning it starts high */
#define CY_TCPWM_PWM_RIGHT_ALIGN                        (1U)        /**< PWM is right aligned, meaning it starts low */
/** PWM is centered aligned, terminal count only occurs on underflow */
#define CY_TCPWM_PWM_CENTER_ALIGN                       (2U)
/** PWM is asymmetrically aligned, terminal count occurs on overflow and underflow */
#define CY_TCPWM_PWM_ASYMMETRIC_ALIGN                   (3U)
#define CY_TCPWM_PWM_ASYMMETRIC_CC0_CC1_ALIGN           (4U) /**< PWM is asymmetrically aligned, line pulse period is equal to CC1-CC0 */
#define CY_TCPWM_PWM_CENTER_ASYMMETRIC_CC0_CC1_ALIGN    (5U) /**< PWM is asymmetrically aligned, TBD */
/** \} group_tcpwm_pwm_alignment */

/** \defgroup group_tcpwm_pwm_kill_modes PWM kill modes
* Sets the kill mode for the PWM.
* \{
*/
#define CY_TCPWM_PWM_STOP_ON_KILL       (2U)    /**< PWM stops counting on kill */
#define CY_TCPWM_PWM_SYNCH_KILL         (1U)    /**< PWM output is killed after next TC*/
#define CY_TCPWM_PWM_ASYNC_KILL         (0U)    /**< PWM output is killed instantly */
/** \} group_tcpwm_pwm_kill_modes */

/** \defgroup group_tcpwm_pwm_output_on_disable PWM Disabled Output
* Specifies the behavior of the PWM outputs while PWM is disabled.
* \{
*/
#define    CY_TCPWM_PWM_OUTPUT_HIGHZ    (0U)    /**< PWM output (default) high impedance */
#define    CY_TCPWM_PWM_OUTPUT_RETAIN   (1U)    /**< PWM outputs are retained */
#define    CY_TCPWM_PWM_OUTPUT_LOW      (2U)    /**< PWM output LOW */
#define    CY_TCPWM_PWM_OUTPUT_HIGH     (3U)    /**< PWM output HIGH */
/** \} group_tcpwm_pwm_output_on_disable */

/** \defgroup group_tcpwm_pwm_output_line PWM Output Lines
* Specifies the PWM output line.
* \{
*/
#define    CY_TCPWM_PWM_LINE_PWM        (0U)    /**< PWM Line output */
#define    CY_TCPWM_PWM_LINE_PWM_INV    (1U)    /**< PWM Line output compliment */
/** \} group_tcpwm_pwm_output_line */

/** \defgroup group_tcpwm_pwm_clk_prescalers PWM CLK Prescaler values
* \{
* Clock prescaler values.
*/
#define CY_TCPWM_PWM_PRESCALER_DIVBY_1      (0U) /**< Divide by 1 */
#define CY_TCPWM_PWM_PRESCALER_DIVBY_2      (1U) /**< Divide by 2 */
#define CY_TCPWM_PWM_PRESCALER_DIVBY_4      (2U) /**< Divide by 4 */
#define CY_TCPWM_PWM_PRESCALER_DIVBY_8      (3U) /**< Divide by 8 */
#define CY_TCPWM_PWM_PRESCALER_DIVBY_16     (4U) /**< Divide by 16 */
#define CY_TCPWM_PWM_PRESCALER_DIVBY_32     (5U) /**< Divide by 32 */
#define CY_TCPWM_PWM_PRESCALER_DIVBY_64     (6U) /**< Divide by 64 */
#define CY_TCPWM_PWM_PRESCALER_DIVBY_128    (7U) /**< Divide by 128 */
/** \} group_tcpwm_pwm_clk_prescalers */

/** \defgroup group_tcpwm_pwm_output_invert PWM output invert
* \{
* Output invert modes.
*/
#define CY_TCPWM_PWM_INVERT_ENABLE          (1U)  /**< Invert the output mode */
#define CY_TCPWM_PWM_INVERT_DISABLE         (0U)  /**< Do not invert the output mode */
/** \} group_tcpwm_pwm_output_invert */

/** \defgroup group_tcpwm_pwm_status PWM Status
* \{
* The counter status.
*/
#define CY_TCPWM_PWM_STATUS_DOWN_COUNTING   (0x1UL)        /**< PWM is down counting */
#define CY_TCPWM_PWM_STATUS_UP_COUNTING     (0x2UL)        /**< PWM is up counting */
#define CY_TCPWM_PWM_STATUS_COUNTER_RUNNING (0x80000000UL) /**< PWM counter is running */
/** \} group_tcpwm_pwm_status */
/** \} group_tcpwm_macros_pwm */


/*******************************************************************************
* Backward compatibility macro. The following code is DEPRECATED and must
* not be used in new projects
*******************************************************************************/

#define Cy_TCPWM_PWM_SetCompare0        Cy_TCPWM_PWM_SetCompare0Val
#define Cy_TCPWM_PWM_GetCompare0        Cy_TCPWM_PWM_GetCompare0Val
#define Cy_TCPWM_PWM_SetCompare1        Cy_TCPWM_PWM_SetCompare0BufVal
#define Cy_TCPWM_PWM_GetCompare1        Cy_TCPWM_PWM_GetCompare0BufVal
#define Cy_TCPWM_PWM_EnableCompareSwap  Cy_TCPWM_PWM_EnableCompare0Swap


/***************************************
*        Registers Constants
***************************************/

/** \cond INTERNAL */
#define CY_TCPWM_PWM_CTRL_SYNC_KILL_OR_STOP_ON_KILL_POS  (2U)
#define CY_TCPWM_PWM_CTRL_SYNC_KILL_OR_STOP_ON_KILL_MASK (0x3UL << CY_TCPWM_PWM_CTRL_SYNC_KILL_OR_STOP_ON_KILL_POS)

#define CY_TCPWM_PWM_TR_CTRL2_SET           (0UL) /**< Set define for PWM output signal configuration */
#define CY_TCPWM_PWM_TR_CTRL2_CLEAR         (1UL) /**< Clear define for PWM output signal configuration */
#define CY_TCPWM_PWM_TR_CTRL2_INVERT        (2UL) /**< Invert define for PWM output signal configuration */
#define CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE     (3UL) /**< No change define for PWM output signal configuration */

#if (CY_IP_MXTCPWM_VERSION == 1U)
/** The configuration of PWM output signal in Pseudo Random Mode */
#define CY_TCPWM_PWM_MODE_PR         (_VAL2FLD(TCPWM_CNT_TR_CTRL2_CC_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE) | \
                                      _VAL2FLD(TCPWM_CNT_TR_CTRL2_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE) | \
                                      _VAL2FLD(TCPWM_CNT_TR_CTRL2_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE))

/** The configuration of PWM output signal for Left alignment */
#define CY_TCPWM_PWM_MODE_LEFT       (_VAL2FLD(TCPWM_CNT_TR_CTRL2_CC_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR) | \
                                      _VAL2FLD(TCPWM_CNT_TR_CTRL2_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_SET) | \
                                      _VAL2FLD(TCPWM_CNT_TR_CTRL2_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE))

/** The configuration of PWM output signal for Right alignment */
#define CY_TCPWM_PWM_MODE_RIGHT      (_VAL2FLD(TCPWM_CNT_TR_CTRL2_CC_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_SET) | \
                                      _VAL2FLD(TCPWM_CNT_TR_CTRL2_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE) | \
                                      _VAL2FLD(TCPWM_CNT_TR_CTRL2_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR))

/** The configuration of PWM output signal for Center and Asymmetric alignment */
#define CY_TCPWM_PWM_MODE_CNTR_OR_ASYMM (_VAL2FLD(TCPWM_CNT_TR_CTRL2_CC_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_INVERT) | \
                                         _VAL2FLD(TCPWM_CNT_TR_CTRL2_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_SET) | \
                                         _VAL2FLD(TCPWM_CNT_TR_CTRL2_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR))

/** The configuration of PWM output signal for Center and Asymmetric alignment with swapped underflow and overflow setting */
#define CY_TCPWM_PWM_MODE_CNTR_OR_ASYMM_SWAPPED (_VAL2FLD(TCPWM_CNT_TR_CTRL2_CC_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_INVERT) | \
                                         _VAL2FLD(TCPWM_CNT_TR_CTRL2_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR) | \
                                         _VAL2FLD(TCPWM_CNT_TR_CTRL2_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_SET))

#else

/** The configuration of PWM output signal in Pseudo Random Mode */
#define CY_TCPWM_PWM_MODE_PR         (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE) | \
                                      _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE) | \
                                      _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE))

/** The configuration of PWM output signal for Left alignment */
#define CY_TCPWM_PWM_MODE_LEFT       (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR) | \
                                      _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_SET) | \
                                      _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE))

/** The configuration of PWM output signal for Right alignment */
#define CY_TCPWM_PWM_MODE_RIGHT      (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_SET) | \
                                      _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE) | \
                                      _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR))

/** The configuration of PWM output signal for Center and Asymmetric alignment */
#define CY_TCPWM_PWM_MODE_CNTR_OR_ASYMM (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_INVERT) | \
                                         _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_SET) | \
                                         _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR))

/** The configuration of PWM output signal for Center and Asymmetric alignment with swapped underflow and overflow setting */
#define CY_TCPWM_PWM_MODE_CNTR_OR_ASYMM_SWAPPED (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_INVERT) | \
                                         _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR) | \
                                         _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_SET))

/** The configuration of PWM output signal to ignore CC1 match event */
#define CY_TCPWM_PWM_MODE_CC1_IGNORE   (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC1_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE))

/** The configuration of PWM output signal for Asymmetric with cc0 and cc1 mode (tcpwm_ver2 only)*/
#define CY_TCPWM_PWM_MODE_ASYMM_CC0_CC1    (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_SET) | \
                                            _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR) | \
                                            _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR) | \
                                            _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC1_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR))

/** The configuration of PWM output signal for Center Align Asymmetric with cc0 and cc1 mode (tcpwm_ver2 only)*/
#define CY_TCPWM_PWM_MODE_CNTR_ASYMM_CC0_CC1   (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_SET) | \
                                                _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_SET) | \
                                                _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR) | \
                                                _VAL2FLD(TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC1_MATCH_MODE, CY_TCPWM_PWM_TR_CTRL2_CLEAR))

#define CY_TCPWM_PWM_MODE_CNTR_ASYMM_CC0_CC1_MATCH    ((TCPWM_GRP_CNT_V2_CTRL_CC0_MATCH_UP_EN_Msk) | \
                                                       (TCPWM_GRP_CNT_V2_CTRL_CC1_MATCH_DOWN_EN_Msk))
#endif
/** \endcond */


/*******************************************************************************
*        Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_tcpwm_functions_pwm
* \{
*/

cy_en_tcpwm_status_t Cy_TCPWM_PWM_Init(TCPWM_Type *base, uint32_t cntNum, cy_stc_tcpwm_pwm_config_t const *config);
void Cy_TCPWM_PWM_DeInit(TCPWM_Type *base, uint32_t cntNum, cy_stc_tcpwm_pwm_config_t const *config);
__STATIC_INLINE void Cy_TCPWM_PWM_Enable(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_PWM_Disable(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetStatus(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_PWM_SetCompare0Val(TCPWM_Type *base, uint32_t cntNum, uint32_t compare0);
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetCompare0Val(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_PWM_SetCompare0BufVal(TCPWM_Type *base, uint32_t cntNum, uint32_t compareBuf0);
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetCompare0BufVal(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_PWM_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum, bool enable);
__STATIC_INLINE void Cy_TCPWM_PWM_SetCounter(TCPWM_Type *base, uint32_t cntNum, uint32_t count);
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetCounter(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_PWM_SetPeriod0(TCPWM_Type *base, uint32_t cntNum, uint32_t period0);
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetPeriod0(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_PWM_SetPeriod1(TCPWM_Type *base, uint32_t cntNum, uint32_t period1);
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetPeriod1(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_PWM_EnablePeriodSwap(TCPWM_Type *base, uint32_t cntNum, bool enable);
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetDtCounter (TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_LineOutStatus (TCPWM_Type const *base, uint32_t cntNum, uint32_t pwmOutSelect);
#endif
__STATIC_INLINE void Cy_TCPWM_PWM_PWMDeadTime (TCPWM_Type const *base, uint32_t cntNum, uint32_t deadTime);
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
__STATIC_INLINE void Cy_TCPWM_PWM_PWMDeadTimeN (TCPWM_Type const *base, uint32_t cntNum, uint32_t deadTime);
#endif
/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_Enable
****************************************************************************//**
*
* Enables the counter in the TCPWM block for the PWM operation.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_V1_PWM_Init
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_V2_PWM_Init
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_Enable(TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_Enable_Single(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_Disable
****************************************************************************//**
*
* Disables the counter in the TCPWM block.
*
* \note This function sets connected PWM output pins Drive modes to High-Z state.
* To disable PWM without changing pins drive modes, use the
* \ref Cy_TCPWM_TriggerStopOrKill or \ref Cy_TCPWM_TriggerStopOrKill_Single
* function.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_DeInit
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_Disable(TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_Disable_Single(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_GetStatus
****************************************************************************//**
*
* Returns the status of the PWM whether it is running or not. In case the
* PWM is running, status will also provide information on counting up/down. This
* is useful when the PWM Alignment mode set to Center/Asymmetric Alignments.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The status. See \ref group_tcpwm_pwm_status
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_GetStatus
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetStatus(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t status;

#if (CY_IP_MXTCPWM_VERSION == 1U)

        status = TCPWM_CNT_STATUS(base, cntNum);

        /* Generates proper up counting status, does not generated by HW */
        status &= ~CY_TCPWM_PWM_STATUS_UP_COUNTING;
        status |= ((~status & CY_TCPWM_PWM_STATUS_DOWN_COUNTING & (status >> TCPWM_CNT_STATUS_RUNNING_Pos)) <<
                   CY_TCPWM_CNT_STATUS_UP_POS);
#else
        status = TCPWM_GRP_CNT_STATUS(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);

        /* Generates proper up counting status, does not generated by HW */
        status &= ~CY_TCPWM_PWM_STATUS_UP_COUNTING;
        status |= ((~status & CY_TCPWM_PWM_STATUS_DOWN_COUNTING & (status >> TCPWM_GRP_CNT_V2_STATUS_RUNNING_Pos)) <<
                   CY_TCPWM_CNT_STATUS_UP_POS);

        /* Set TCPWM_CNT_STATUS_RUNNING_Pos with TCPWM_GRP_CNT_V2_STATUS_RUNNING for BWC */
        status |= (_FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_RUNNING, status) << TCPWM_CNT_STATUS_RUNNING_Pos);
#endif

    return(status);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_SetCompare0Val
****************************************************************************//**
*
* Sets the compare value for Compare 0 when the compare mode enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param compare0
* The Compare 0 value.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_SetCompare0Val
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_SetCompare0Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare0)
{
    Cy_TCPWM_Block_SetCC0Val(base, cntNum, compare0);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_GetCompare0Val
****************************************************************************//**
*
* Returns compare 0 value.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Compare 0 value.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_SetCompare0Val
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetCompare0Val(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_SetCompare0BufVal
****************************************************************************//**
*
* Sets the buffered compare value for Compare 0 when the compare mode enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param compareBuf0
* The buffered Compare 0 value.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_SetCompare0BufVal
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_SetCompare0BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compareBuf0)
{
    Cy_TCPWM_Block_SetCC0BufVal(base, cntNum, compareBuf0);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_GetCompare0BufVal
****************************************************************************//**
*
* Returns the buffered compare 0 value.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Buffered compare 0 value.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_SetCompare0BufVal
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetCompare0BufVal(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0BufVal(base, cntNum);
}

#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_SetCompare1Val
****************************************************************************//**
*
* Sets the compare value for Compare 1 when the compare mode enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param compare1
* The Compare1 value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_SetCompare1Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare1)
{
    Cy_TCPWM_Block_SetCC1Val(base, cntNum, compare1);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_GetCompare1Val
****************************************************************************//**
*
* Returns compare 1 value.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Compare 1 value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetCompare1Val(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_SetCompare1BufVal
****************************************************************************//**
*
* Sets the buffered compare value for Compare1 when the compare mode enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param compareBuf1
* The buffered Compare 1 value.
*
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_SetCompare1BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compareBuf1)
{
    Cy_TCPWM_Block_SetCC1BufVal(base, cntNum, compareBuf1);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_GetCompare1BufVal
****************************************************************************//**
*
* Returns the buffered compare 1 value.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Buffered compare 1 value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetCompare1BufVal(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1BufVal(base, cntNum);
}
#endif
/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_EnableCompare0Swap
****************************************************************************//**
*
* Enables the comparison swap of compare 0 and compareBuf 0 on OV and/or UN,
* depending on the PWM alignment.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param enable
* true = swap enabled; false = swap disabled
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_EnableCompare0Swap
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
     Cy_TCPWM_Block_EnableCompare0Swap(base, cntNum, enable);
}

#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_EnableCompare1Swap
****************************************************************************//**
*
* Enables the comparison swap of compare1 and compareBuf1 on OV and/or UN,
* depending on the PWM alignment.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param enable
* true = swap enabled; false = swap disabled
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_EnableCompare1Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
    Cy_TCPWM_Block_EnableCompare1Swap(base, cntNum, enable);
}
#endif

/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_SetCounter
****************************************************************************//**
*
* Sets the value of the counter.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param count
* The value to write into the counter.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_SetCounter
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_SetCounter(TCPWM_Type *base, uint32_t cntNum,  uint32_t count)
{
    Cy_TCPWM_Block_SetCounter(base, cntNum, count);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_GetCounter
****************************************************************************//**
*
* Returns the value in the counter.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The current counter value.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_GetCounter
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetCounter(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCounter(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_SetPeriod0
****************************************************************************//**
*
* Sets the value of the period register.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param period0
* The value to write into a period.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_SetPeriod0
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_SetPeriod0(TCPWM_Type *base, uint32_t cntNum,  uint32_t period0)
{
    Cy_TCPWM_Block_SetPeriod(base, cntNum, period0);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_GetPeriod0
****************************************************************************//**
*
* Returns the value in the period register.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The current period value.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_SetPeriod0
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetPeriod0(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetPeriod(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_SetPeriod1
****************************************************************************//**
*
* Sets the value of the period register. In pseudo random mode period 1 sets
* which taps are enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param period1
* The value to write into a period 1.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_SetPeriod1
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_SetPeriod1(TCPWM_Type *base, uint32_t cntNum,  uint32_t period1)
{
#if (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CNT_PERIOD_BUFF(base, cntNum) = period1;
#else
        TCPWM_GRP_CNT_PERIOD_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = period1;
#endif
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_GetPeriod1
****************************************************************************//**
*
* Returns the value in the period register.
*
* \param base
* The pointer to a COUNTER PWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The current period value.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_SetPeriod1
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetPeriod1(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t result;

#if (CY_IP_MXTCPWM_VERSION == 1U)

        result = TCPWM_CNT_PERIOD_BUFF(base, cntNum);
#else
        result = TCPWM_GRP_CNT_PERIOD_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
#endif

    return result;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_EnablePeriodSwap
****************************************************************************//**
*
* Enables a period swap on OV and/or UN, depending on the PWM alignment
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param enable
* true = swap enabled; false = swap disabled
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_EnablePeriodSwap
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_EnablePeriodSwap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
#if (CY_IP_MXTCPWM_VERSION == 1U)

        if (enable)
        {
            TCPWM_CNT_CTRL(base, cntNum) |=  TCPWM_CNT_CTRL_AUTO_RELOAD_PERIOD_Msk;
        }
        else
        {
            TCPWM_CNT_CTRL(base, cntNum) &= ~TCPWM_CNT_CTRL_AUTO_RELOAD_PERIOD_Msk;
        }
#else
        if (enable)
        {
            TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) |=
                                     TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_PERIOD_Msk;
        }
        else
        {
            TCPWM_GRP_CNT_CTRL(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) &=
                                    ~TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_PERIOD_Msk;
        }
#endif
}

#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_GetDtCounter
****************************************************************************//**
*
* Returns the dead time count when the PWM is configured in dead time mode
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The dead time counter.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_GetDtCounter
*
* \note supported only in TCPWM_ver2
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_GetDtCounter (TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t result = 0UL;

    result = TCPWM_GRP_CNT_STATUS(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
    result = (result & (TCPWM_GRP_CNT_V2_STATUS_DT_CNT_L_Msk | TCPWM_GRP_CNT_V2_STATUS_DT_CNT_H_Msk)) >> TCPWM_GRP_CNT_V2_STATUS_DT_CNT_L_Pos;

    return result;
}

/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_LineOutStatus
****************************************************************************//**
*
* Returns the current level of the selected pwm output line.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param pwmOutSelect
* Defines which pwm output line is being checked pwm or pwm_n.
*
* \return
* The current pwm output line level.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_LineOutStatus
*
* \note supported only in TCPWM_ver2
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_PWM_LineOutStatus (TCPWM_Type const *base, uint32_t cntNum, uint32_t pwmOutSelect)
{
    uint32_t status = 0UL;


    status = TCPWM_GRP_CNT_STATUS(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);

     switch(pwmOutSelect)
     {
         case CY_TCPWM_PWM_LINE_PWM:
             status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_LINE_OUT, status);
             break;
         case CY_TCPWM_PWM_LINE_PWM_INV:
             status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_LINE_COMPL_OUT, status);
             break;
         default:
             /* Not a Valid Line output */
             CY_ASSERT_L3(false);
             break;
    }

    return status;
}
#endif

/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_PWMDeadTime
****************************************************************************//**
*
* Writes the dead time value for PWM. This is the number of clock cycles between
* PWM_n (line_compl) going LOW and PWM (line) going HIGH.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param deadTime
* The dead time value.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_PWMDeadTime
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_PWMDeadTime (TCPWM_Type const *base, uint32_t cntNum, uint32_t deadTime)
{
    uint32_t result;

#if (CY_IP_MXTCPWM_VERSION == 1U)

        result = TCPWM_CNT_CTRL(base, cntNum);
        result &= ~(TCPWM_CNT_CTRL_GENERIC_Msk);

        TCPWM_CNT_CTRL(base, cntNum) = result | _VAL2FLD(TCPWM_CNT_CTRL_GENERIC, deadTime);
#else
        uint32_t grp = TCPWM_GRP_CNT_GET_GRP(cntNum);

        result = TCPWM_GRP_CNT_DT(base, grp, cntNum);
        result &= ~(TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_L_Msk | TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_H_Msk);

        TCPWM_GRP_CNT_DT(base, grp, cntNum) = result |
                    _VAL2FLD(TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_L, (uint8_t)(deadTime)) |
                    _VAL2FLD(TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_H, (uint8_t)(deadTime >> 8U));
#endif

}

#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_TCPWM_PWM_PWMDeadTimeN
****************************************************************************//**
*
* Writes the dead time value for PWM_n. This is the number of clock cycles between
* PWM (line) going LOW and PWM_n (line_compl) going HIGH.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param deadTime
* The dead time value.
*
* \funcusage
* \snippet tcpwm/pwm/snippet/main.c snippet_Cy_TCPWM_PWM_PWMDeadTime
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_PWM_PWMDeadTimeN (TCPWM_Type const *base, uint32_t cntNum, uint32_t deadTime)
{
    uint32_t result;
    uint32_t grp = TCPWM_GRP_CNT_GET_GRP(cntNum);

    result = TCPWM_GRP_CNT_DT(base, grp, cntNum);
    result &= ~(TCPWM_GRP_CNT_V2_DT_DT_LINE_COMPL_OUT_Msk);

    TCPWM_GRP_CNT_DT(base, grp, cntNum) = result |
            _VAL2FLD(TCPWM_GRP_CNT_V2_DT_DT_LINE_COMPL_OUT, (uint16_t)(deadTime));

}
#endif


/** \} group_tcpwm_functions_pwm */

/** \} group_tcpwm_pwm */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXTCPWM */

#endif /* CY_TCPWM_PWM_H */

/* [] END OF FILE */
