/***************************************************************************//**
* \file cy_lpcomp.h
* \version 1.50
*
*  This file provides constants and parameter values for the Low Power Comparator driver.
*
********************************************************************************
* \copyright
* (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
*
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
* \addtogroup group_lpcomp
* \{
* Provides access to low-power comparators implemented using the fixed-function,
* LP comparator block that is present in the CAT1A and CAT1D devices.
*
* The functions and other declarations used in this driver are in the cy_lpcomp.h file.
* You can include the cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* Such comparators can perform a fast analog signal comparison of internal
* and external analog signals in all system power modes. The low-power comparator
* output can be inspected by the CPU, used as an interrupt/wakeup source to the
* CPU in Low-power mode (Sleep, Low-power Sleep or Deep-Sleep), used as
* a wakeup source to system resources in Hibernate mode, or fed to DSI as
* an asynchronous or synchronous signal (level or pulse).
*
* \section group_lpcomp_section_Configuration_Considerations Configuration Considerations
* To set up a low-power comparator, the inputs, output, mode, interrupts and
* the other configuration parameters are configured. Power the low-power comparator
* to start it operate.
*
* The sequence recommended for the low-power comparator operation:
*
* 1) To initialize the driver, call the  Cy_LPComp_Init_Ext() function providing
* the filled cy_stc_lpcomp_config_t structure, the low-power comparator
* channel number and the low-power comparator registers structure pointer.
*
* 2) Optionally, configure the interrupt requests if the interrupt event
* triggering is needed. Use the Cy_LPComp_SetInterruptMask() function with
* the parameter for the mask available in the configuration file.
* Additionally, enable the Global interrupts and initialize the referenced
* interrupt by setting the priority and the interrupt vector using
* the \ref Cy_SysInt_Init() function of the sysint driver.
*
* 3) Configure the inputs and the output using the \ref Cy_GPIO_Pin_Init()
* functions of the GPIO driver.
* High Impedance Analog drive mode is for the inputs and
* Strong drive mode - for the output.
* Use the Cy_LPComp_SetInputs() function to connect the comparator inputs
* to the dedicated IO pins, AMUXBUSA/AMUXBUSB or Vref:
* \image html lpcomp_inputs.png
*
* 4) Power on the comparator using the Cy_LPComp_Enable_Ext() function.
*
* 5) The comparator output can be monitored using
* the Cy_LPComp_GetCompare() function or using the low-power comparator
* interrupt (if the interrupt is enabled).
*
* \note The interrupt is not cleared automatically.
* It is the user's responsibility to do that.
* The interrupt is cleared by writing "1" in the corresponding interrupt
* register bit position. The preferred way to clear interrupt sources
* is using the Cy_LPComp_ClearInterrupt() function.
*
* \note Individual comparator interrupt outputs are ORed together
* as a single asynchronous interrupt source before it is sent out and
* used to wake up the system in the low-power mode.
* For CAT1A, CAT1D devices, the individual comparator interrupt is masked
* by the INTR_MASK register. The masked result is captured in
* the INTR_MASKED register.
* Writing "1" to the INTR register bit will clear the interrupt.
*
* \section group_lpcomp_lp Low Power Support
* The low-power comparator provides callback functions to facilitate
* the low-power mode transition.
* Call \ref Cy_LPComp_DeepSleepCallback during execution of
* \ref Cy_SysPm_CpuEnterDeepSleep.
* Call \ref Cy_LPComp_HibernateCallback during execution of
* \ref Cy_SysPm_SystemEnterHibernate.
* To trigger callback execution, register the callback before calling
* the mode transition function.
* Refer to \ref group_syspm driver for more
* information about low-power mode transition.
*
* The example below shows the entering Hibernate mode.
* The positive low-power comparator input connects to the dedicated GPIO pin
* and the negative low-power comparator input connects to the local reference.
* The LED blinks twice after a device reset and goes into Hibernate mode.
* When the voltage on the positive input is greater than the local reference
* voltage (0.45V - 0.75V), the device wakes up and the LED starts blinking. \n
* Section of declarations:
* \snippet lpcomp/snippet/main.c LP_COMP_CFG_HIBERNATE
* Section of application code:
* \snippet lpcomp/snippet/main.c LP_COMP_FUNC_HIBERNATE
* \section group_lpcomp_more_information More Information
*
* For a detailed description of the registers, refer to
* the appropriate device technical reference manual (TRM).
*
* \section group_lpcomp_Changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.50</td>
*     <td> * Minor improvement in implementation of disabling functionality for the comparator.
*          * Documented MISRA C-2012 violation of the Rule 10.3.
*     </td>
*     <td>
*         * Power drive mode for the comparator is restored to the level before disabling,
*           instead of initial level.
*         * MISRA C-2012 compliance.
*     </td>
*   </tr>
*   <tr>
*     <td>1.40</td>
*     <td>Introduced an extended versions of the existing functions with
*         a pointer to the context structure allocated by the user:
*         * \ref Cy_LPComp_Init_Ext(),
*         * \ref Cy_LPComp_Enable_Ext(),
*         * \ref Cy_LPComp_Disable_Ext(),
*         * \ref Cy_LPComp_SetInterruptTriggerMode_Ext(),
*         * \ref Cy_LPComp_SetPower_Ext()
*     </td>
*     <td>
*         * Improved returning of the comparator from disabled to operational state
*           with restoring power drive and interrupt edge-detect modes, configured before disable.
*         * Improved thread safe implementation of the PDL.
*     </td>
*   </tr>
*   <tr>
*     <td>1.30</td>
*     <td>Fixed/documented MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.20.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.20</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using de-referenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Added Low Power Callback section</td>
*     <td>Documentation update and clarification</td>
*   </tr>
*   <tr>
*     <td>1.10</td>
*     <td>The CY_WEAK keyword is removed from Cy_LPComp_DeepSleepCallback()
*         and Cy_LPComp_HibernateCallback() functions<br>
*         Added input parameter validation to the API functions.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_lpcomp_macros Macros
* \defgroup group_lpcomp_functions Functions
*   \{
*       \defgroup group_lpcomp_functions_syspm_callback  Low Power Callback
*   \}
* \defgroup group_lpcomp_data_structures Data Structures
* \defgroup group_lpcomp_enums Enumerated Types
*/

#ifndef CY_LPCOMP_PDL_H
#define CY_LPCOMP_PDL_H

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXLPCOMP) || defined (CY_IP_MXS22LPCOMP)

#include <stdbool.h>
#include <stddef.h>
#include "cy_syslib.h"
#include "cy_syspm.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* \addtogroup group_lpcomp_macros
* \{
*/

/** Driver major version. */
#define CY_LPCOMP_DRV_VERSION_MAJOR       1

/** Driver minor version. */
#define CY_LPCOMP_DRV_VERSION_MINOR       50

/******************************************************************************
* API Constants
******************************************************************************/

/** The low-power comparator PDL ID. */
#define CY_LPCOMP_ID                                CY_PDL_DRV_ID(0x23u)

/** The low-power comparator number of channels. */
#define CY_LPCOMP_MAX_CHANNEL_NUM                   (2u)

/** The low-power comparator comparator 1 interrupt mask. */
#define CY_LPCOMP_COMP0                             (LPCOMP_INTR_COMP0_Msk)
/** The low-power comparator comparator 2 interrupt mask. */
#define CY_LPCOMP_COMP1                             (LPCOMP_INTR_COMP1_Msk)

/** \cond INTERNAL_MACROS */


/******************************************************************************
* Registers Constants
******************************************************************************/

#define CY_LPCOMP_MODE_ULP_Pos                      (0x0uL)
#define CY_LPCOMP_MODE_ULP_Msk                      (0x1uL)

#define CY_LPCOMP_INTR_Pos                          (LPCOMP_INTR_COMP0_Pos)
#define CY_LPCOMP_INTR_Msk                          (LPCOMP_INTR_COMP0_Msk | LPCOMP_INTR_COMP1_Msk)

#define CY_LPCOMP_CMP0_SW_POS_Msk                   (LPCOMP_CMP0_SW_CMP0_IP0_Msk | \
                                                    LPCOMP_CMP0_SW_CMP0_AP0_Msk | \
                                                    LPCOMP_CMP0_SW_CMP0_BP0_Msk)
#define CY_LPCOMP_CMP0_SW_NEG_Msk                   (LPCOMP_CMP0_SW_CMP0_IN0_Msk | \
                                                    LPCOMP_CMP0_SW_CMP0_AN0_Msk | \
                                                    LPCOMP_CMP0_SW_CMP0_BN0_Msk | \
                                                    LPCOMP_CMP0_SW_CMP0_VN0_Msk)
#define CY_LPCOMP_CMP1_SW_POS_Msk                   (LPCOMP_CMP1_SW_CMP1_IP1_Msk | \
                                                    LPCOMP_CMP1_SW_CMP1_AP1_Msk | \
                                                    LPCOMP_CMP1_SW_CMP1_BP1_Msk)
#define CY_LPCOMP_CMP1_SW_NEG_Msk                   (LPCOMP_CMP1_SW_CMP1_IN1_Msk | \
                                                    LPCOMP_CMP1_SW_CMP1_AN1_Msk | \
                                                    LPCOMP_CMP1_SW_CMP1_BN1_Msk | \
                                                    LPCOMP_CMP1_SW_CMP1_VN1_Msk)

#define CY_LPCOMP_CMP0_OUTPUT_CONFIG_Pos            LPCOMP_CMP0_CTRL_DSI_BYPASS0_Pos
#define CY_LPCOMP_CMP1_OUTPUT_CONFIG_Pos            LPCOMP_CMP1_CTRL_DSI_BYPASS1_Pos

#define CY_LPCOMP_CMP0_OUTPUT_CONFIG_Msk           (LPCOMP_CMP0_CTRL_DSI_BYPASS0_Msk | \
                                                    LPCOMP_CMP0_CTRL_DSI_LEVEL0_Msk)

#define CY_LPCOMP_CMP1_OUTPUT_CONFIG_Msk           (LPCOMP_CMP1_CTRL_DSI_BYPASS1_Msk | \
                                                    LPCOMP_CMP1_CTRL_DSI_LEVEL1_Msk)

#define CY_HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SL_SR_Pos HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SL_Pos

#define CY_HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SL_SR_Msk (HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SL_Msk | \
                                                     HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SR_Msk)

#define CY_HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_SR_Pos HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_Pos

#define CY_HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_SR_Msk (HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_Msk | \
                                                     HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SR_Msk)

#define CY_LPCOMP_REF_CONNECTED                     (1u)

#define CY_LPCOMP_WAKEUP_PIN0_Msk                   CY_SYSPM_WAKEUP_LPCOMP0
#define CY_LPCOMP_WAKEUP_PIN1_Msk                   CY_SYSPM_WAKEUP_LPCOMP1

/* Internal constants for Cy_LPComp_Enable() */
#define CY_LPCOMP_NORMAL_POWER_DELAY               (3u)
#define CY_LPCOMP_LP_POWER_DELAY                   (6u)
#define CY_LPCOMP_ULP_POWER_DELAY                  (50u)

/** \endcond */
/** \} group_lpcomp_macros */

/**
* \addtogroup group_lpcomp_enums
* \{
*/

/******************************************************************************
 * Enumerations
 *****************************************************************************/
/** The low-power comparator output modes. */
typedef enum
{
    CY_LPCOMP_OUT_PULSE  = 0u,  /**< The low-power comparator DSI output with the pulse option, no bypass. */
    CY_LPCOMP_OUT_DIRECT = 1u,  /**< The low-power comparator Bypass mode, the direct output of a comparator. */
    CY_LPCOMP_OUT_SYNC   = 2u   /**< The low-power comparator DSI output with the level option, it is similar
                                  to Bypass mode but it is 1 cycle slower. */
} cy_en_lpcomp_out_t;

/** The low-power comparator hysteresis modes. */
typedef enum
{
    CY_LPCOMP_HYST_ENABLE  = 1u,  /**< The low-power comparator enable hysteresis. */
    CY_LPCOMP_HYST_DISABLE = 0u   /**< The low-power comparator disable hysteresis. */
} cy_en_lpcomp_hyst_t;

/** The low-power comparator channel number. */
typedef enum
{
    CY_LPCOMP_CHANNEL_0  = 0x1u,  /**< The low-power comparator 0. */
    CY_LPCOMP_CHANNEL_1  = 0x2u   /**< The low-power comparator 1. */
} cy_en_lpcomp_channel_t;

/** The low-power comparator interrupt modes. */
typedef enum
{
    CY_LPCOMP_INTR_DISABLE = 0u,  /**< The low-power comparator interrupt is disabled, no interrupt will be detected. */
    CY_LPCOMP_INTR_RISING  = 1u,  /**< The low-power comparator interrupt on the rising edge. */
    CY_LPCOMP_INTR_FALLING = 2u,  /**< The low-power comparator interrupt on the falling edge. */
    CY_LPCOMP_INTR_BOTH    = 3u   /**< The low-power comparator interrupt on both rising and falling edges. */
} cy_en_lpcomp_int_t;

/** The low-power comparator power-mode selection. */
typedef enum
{
    CY_LPCOMP_MODE_OFF     = 0u,  /**< The low-power comparator channel power-off. */
    CY_LPCOMP_MODE_ULP     = 1u,  /**< The low-power comparator channel ULP mode. */
    CY_LPCOMP_MODE_LP      = 2u,  /**< The low-power comparator channel LP mode. */
    CY_LPCOMP_MODE_NORMAL  = 3u   /**< The low-power comparator channel normal mode. */
} cy_en_lpcomp_pwr_t;

/** The low-power comparator inputs. */
typedef enum
{
    CY_LPCOMP_SW_GPIO       = 0x01u,  /**< The low-power comparator input connects to GPIO pin. */
    CY_LPCOMP_SW_AMUXBUSA   = 0x02u,  /**< The low-power comparator input connects to AMUXBUSA. */
    CY_LPCOMP_SW_AMUXBUSB   = 0x04u,  /**< The low-power comparator input connects to AMUXBUSB. */
    CY_LPCOMP_SW_LOCAL_VREF = 0x08u   /**< The low-power comparator input connects to local VREF. */
} cy_en_lpcomp_inputs_t;

/** The low-power comparator error codes. */
typedef enum
{
    CY_LPCOMP_SUCCESS = 0x00u,                                            /**< Successful */
    CY_LPCOMP_BAD_PARAM = CY_LPCOMP_ID | CY_PDL_STATUS_ERROR | 0x01u,     /**< One or more invalid parameters */
} cy_en_lpcomp_status_t;

#if defined (CY_IP_MXS22LPCOMP)
/** The low-power comparator trim polarity. */
typedef enum
{
   CY_LPCOMP_TRIM_NEGATIVE = 0x00UL,   /**< The low-power comparator trim is negative. */
   CY_LPCOMP_TRIM_POSITIVE = 0x01UL,   /**< The low-power comparator trim is positive. */
} cy_en_lpcomp_trim_polarity_t;

/** The low-power comparator trim magnitude. */
typedef enum
{
    CY_LPCOMP_TRIM_0mV  = 0x00UL,   /**< The low-power comparator trim value 0mV. */
    CY_LPCOMP_TRIM_1mV  = 0x01UL,   /**< The low-power comparator trim value 1mV. */
    CY_LPCOMP_TRIM_2mV  = 0x02UL,   /**< The low-power comparator trim value 2mV. */
    CY_LPCOMP_TRIM_3mV  = 0x03UL,   /**< The low-power comparator trim value 3mV. */
    CY_LPCOMP_TRIM_4mV  = 0x04UL,   /**< The low-power comparator trim value 4mV. */
    CY_LPCOMP_TRIM_5mV  = 0x05UL,   /**< The low-power comparator trim value 5mV. */
    CY_LPCOMP_TRIM_6mV  = 0x06UL,   /**< The low-power comparator trim value 6mV. */
    CY_LPCOMP_TRIM_7mV  = 0x07UL,   /**< The low-power comparator trim value 7mV. */
    CY_LPCOMP_TRIM_8mV  = 0x08UL,   /**< The low-power comparator trim value 8mV. */
    CY_LPCOMP_TRIM_9mV  = 0x09UL,   /**< The low-power comparator trim value 9mV. */
    CY_LPCOMP_TRIM_10mV = 0x0AUL,   /**< The low-power comparator trim value 10mV. */
    CY_LPCOMP_TRIM_11mV = 0x0BUL,   /**< The low-power comparator trim value 11mV. */
    CY_LPCOMP_TRIM_12mV = 0x0CUL,   /**< The low-power comparator trim value 12mV. */
    CY_LPCOMP_TRIM_13mV = 0x0DUL,   /**< The low-power comparator trim value 13mV. */
    CY_LPCOMP_TRIM_14mV = 0x0EUL,   /**< The low-power comparator trim value 14mV. */
    CY_LPCOMP_TRIM_15mV = 0x0FUL    /**< The low-power comparator trim value 15mV. */
} cy_en_lpcomp_trim_magnitude_t;
#endif

/** \} group_lpcomp_enums */

/**
* \addtogroup group_lpcomp_data_structures
* \{
*/

/******************************************************************************
 * Structures
 *****************************************************************************/

/** The low-power comparator configuration structure. */
typedef struct {
    cy_en_lpcomp_out_t  outputMode;  /**< The low-power comparator outputMode: Direct output,
                                       Synchronized output or Pulse output */
    cy_en_lpcomp_hyst_t hysteresis;  /**< Enables or disables the low-power comparator hysteresis */
    cy_en_lpcomp_pwr_t power;        /**< Sets the low-power comparator power mode */
    cy_en_lpcomp_int_t intType;      /**< Sets the low-power comparator interrupt mode */
} cy_stc_lpcomp_config_t;

#if defined (CY_IP_MXS22LPCOMP)
/** The low-power comparator trim structure. */
typedef struct
{
    bool enable;                              /**< Enables or disables the low-power comparator trim */
    cy_en_lpcomp_trim_polarity_t polarity;    /**< Defines the low-power comparator trim polarity */
    cy_en_lpcomp_trim_magnitude_t magnitude;  /**< Defines the low-power comparator trim magnitude */
} cy_en_lpcomp_trim_t;
#endif

/** The low-power comparator context structure, used to improve thread-safe implementation of the PDL.
* It is applicable for the following functions:
* * \ref Cy_LPComp_Init_Ext(),
* * \ref Cy_LPComp_Enable_Ext(),
* * \ref Cy_LPComp_Disable_Ext(),
* * \ref Cy_LPComp_SetInterruptTriggerMode_Ext(),
* * \ref Cy_LPComp_SetPower_Ext()
 */
typedef struct {
/** \cond CONTEXT_STRUCTURE */
    cy_en_lpcomp_int_t intType[CY_LPCOMP_MAX_CHANNEL_NUM];
    cy_en_lpcomp_pwr_t power[CY_LPCOMP_MAX_CHANNEL_NUM];
/** \endcond */
} cy_stc_lpcomp_context_t;

/** \} group_lpcomp_data_structures */

/** \cond INTERNAL_MACROS */

/******************************************************************************
 * Macros
 *****************************************************************************/
#define CY_LPCOMP_IS_CHANNEL_VALID(channel)      (((channel) == CY_LPCOMP_CHANNEL_0) || \
                                                  ((channel) == CY_LPCOMP_CHANNEL_1))
#define CY_LPCOMP_IS_OUT_MODE_VALID(mode)        (((mode) == CY_LPCOMP_OUT_PULSE) || \
                                                  ((mode) == CY_LPCOMP_OUT_DIRECT) || \
                                                  ((mode) == CY_LPCOMP_OUT_SYNC))
#define CY_LPCOMP_IS_HYSTERESIS_VALID(hyst)      (((hyst) == CY_LPCOMP_HYST_ENABLE) || \
                                                  ((hyst) == CY_LPCOMP_HYST_DISABLE))
#define CY_LPCOMP_IS_INTR_MODE_VALID(intr)       (((intr) == CY_LPCOMP_INTR_DISABLE) || \
                                                  ((intr) == CY_LPCOMP_INTR_RISING) || \
                                                  ((intr) == CY_LPCOMP_INTR_FALLING) || \
                                                  ((intr) == CY_LPCOMP_INTR_BOTH))
#define CY_LPCOMP_IS_POWER_VALID(power)          (((power) == CY_LPCOMP_MODE_OFF) || \
                                                  ((power) == CY_LPCOMP_MODE_ULP) || \
                                                  ((power) == CY_LPCOMP_MODE_LP) || \
                                                  ((power) == CY_LPCOMP_MODE_NORMAL))
#define CY_LPCOMP_IS_INTR_VALID(intr)            (((intr) == CY_LPCOMP_COMP0) || \
                                                  ((intr) == CY_LPCOMP_COMP1) || \
                                                  ((intr) == (CY_LPCOMP_COMP0 | CY_LPCOMP_COMP1)))
#define CY_LPCOMP_IS_INPUT_P_VALID(input)        (((input) == CY_LPCOMP_SW_GPIO) || \
                                                  ((input) == CY_LPCOMP_SW_AMUXBUSA) || \
                                                  ((input) == CY_LPCOMP_SW_AMUXBUSB))
#define CY_LPCOMP_IS_INPUT_N_VALID(input)        (((input) == CY_LPCOMP_SW_GPIO) || \
                                                  ((input) == CY_LPCOMP_SW_AMUXBUSA) || \
                                                  ((input) == CY_LPCOMP_SW_AMUXBUSB) || \
                                                  ((input) == CY_LPCOMP_SW_LOCAL_VREF))
#if defined (CY_IP_MXS22LPCOMP)
#define CY_LPCOMP_IS_TRIM_VALID(trim)          (((((trim)->polarity) == CY_LPCOMP_TRIM_NEGATIVE) || \
                                                 (((trim)->polarity) == CY_LPCOMP_TRIM_POSITIVE)) && \
                                                ((((trim)->magnitude) >= CY_LPCOMP_TRIM_0mV) && \
                                                 (((trim)->magnitude) <= CY_LPCOMP_TRIM_15mV)))
#endif
/** \endcond */

/**
* \addtogroup group_lpcomp_functions
* \{
*/

/******************************************************************************
* Functions
*******************************************************************************/

cy_en_lpcomp_status_t Cy_LPComp_Init_Ext(LPCOMP_Type *base, cy_en_lpcomp_channel_t channel, const cy_stc_lpcomp_config_t *config,
                                        cy_stc_lpcomp_context_t *context);
void Cy_LPComp_Enable_Ext(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_stc_lpcomp_context_t *context);
void Cy_LPComp_Disable_Ext(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_stc_lpcomp_context_t *context);
#if defined (CY_IP_MXLPCOMP)
cy_en_lpcomp_status_t Cy_LPComp_Init(LPCOMP_Type *base, cy_en_lpcomp_channel_t channel, const cy_stc_lpcomp_config_t *config);
void Cy_LPComp_Enable(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel);
void Cy_LPComp_Disable(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel);
#endif
__STATIC_INLINE void Cy_LPComp_GlobalEnable(LPCOMP_Type *base);
__STATIC_INLINE void Cy_LPComp_GlobalDisable(LPCOMP_Type *base);
__STATIC_INLINE void Cy_LPComp_UlpReferenceEnable(LPCOMP_Type *base);
__STATIC_INLINE void Cy_LPComp_UlpReferenceDisable(LPCOMP_Type *base);
__STATIC_INLINE uint32_t Cy_LPComp_GetCompare(LPCOMP_Type const * base, cy_en_lpcomp_channel_t channel);
void Cy_LPComp_SetPower_Ext(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_pwr_t power,
                           cy_stc_lpcomp_context_t *context);
#if defined (CY_IP_MXLPCOMP)
void Cy_LPComp_SetPower(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_pwr_t power);
#endif
void Cy_LPComp_SetHysteresis(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_hyst_t hysteresis);
void Cy_LPComp_SetInputs(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_inputs_t inputP, cy_en_lpcomp_inputs_t inputN);
void Cy_LPComp_SetOutputMode(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_out_t outType);
void Cy_LPComp_SetInterruptTriggerMode_Ext(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_int_t intType,
                                          cy_stc_lpcomp_context_t *context);
#if defined (CY_IP_MXLPCOMP)
void Cy_LPComp_SetInterruptTriggerMode(LPCOMP_Type* base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_int_t intType);
#endif
__STATIC_INLINE uint32_t Cy_LPComp_GetInterruptStatus(LPCOMP_Type const * base);
__STATIC_INLINE void Cy_LPComp_ClearInterrupt(LPCOMP_Type* base, uint32_t interrupt);
__STATIC_INLINE void Cy_LPComp_SetInterrupt(LPCOMP_Type* base, uint32_t interrupt);
__STATIC_INLINE uint32_t Cy_LPComp_GetInterruptMask(LPCOMP_Type const * base);
__STATIC_INLINE void Cy_LPComp_SetInterruptMask(LPCOMP_Type* base, uint32_t interrupt);
__STATIC_INLINE uint32_t Cy_LPComp_GetInterruptStatusMasked(LPCOMP_Type const * base);
__STATIC_INLINE void Cy_LPComp_ConnectULPReference(LPCOMP_Type *base, cy_en_lpcomp_channel_t channel);
#if defined (CY_IP_MXS22LPCOMP)
void Cy_LPComp_GetTrim(LPCOMP_Type const * base, cy_en_lpcomp_channel_t channel, cy_en_lpcomp_trim_t * trim);
void Cy_LPComp_SetTrim(LPCOMP_Type * base, cy_en_lpcomp_channel_t channel, const cy_en_lpcomp_trim_t * trim);
#endif
/** \addtogroup group_lpcomp_functions_syspm_callback
* The driver supports the SysPm callback for Deep Sleep and Hibernate transition.
* \{
*/
cy_en_syspm_status_t Cy_LPComp_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
cy_en_syspm_status_t Cy_LPComp_HibernateCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
/** \} */


/*******************************************************************************
* Function Name: Cy_LPComp_GlobalEnable
****************************************************************************//**
*
* Activates the IP of the low-power comparator hardware block.
* Call this function before operating any comparator channel.
* \note Interrupts can be enabled after the block is enabled and appropriate
* start-up time has elapsed:
* * 3 us for normal power mode;
* * 6 us for LP mode;
* * 50 us for ULP mode.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \return None.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LPComp_GlobalEnable(LPCOMP_Type* base)
{
    LPCOMP_CONFIG(base) |= LPCOMP_CONFIG_ENABLED_Msk;
}


/*******************************************************************************
* Function Name: Cy_LPComp_GlobalDisable
****************************************************************************//**
*
* Deactivates the IP of the low-power comparator hardware block.
* (Analog is in power down, open all switches, all clocks are off).
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \return None.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LPComp_GlobalDisable(LPCOMP_Type *base)
{
    LPCOMP_CONFIG(base) &= (uint32_t) ~LPCOMP_CONFIG_ENABLED_Msk;
}


/*******************************************************************************
* Function Name: Cy_LPComp_UlpReferenceEnable
****************************************************************************//**
*
* Enables the local reference-generator circuit.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \return None.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LPComp_UlpReferenceEnable(LPCOMP_Type *base)
{
    LPCOMP_CONFIG(base) |= LPCOMP_CONFIG_LPREF_EN_Msk;
}


/*******************************************************************************
* Function Name: Cy_LPComp_UlpReferenceDisable
****************************************************************************//**
*
* Disables the local reference-generator circuit.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \return None.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LPComp_UlpReferenceDisable(LPCOMP_Type *base)
{
    LPCOMP_CONFIG(base) &= (uint32_t) ~LPCOMP_CONFIG_LPREF_EN_Msk;
}


/*******************************************************************************
* Function Name: Cy_LPComp_GetCompare
****************************************************************************//**
*
* This function returns a non-zero value when the voltage connected to the
* positive input is greater than the negative input voltage.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param channel
*     The low-power comparator channel index.
*
* \return The low-power comparator compare result.
*     The value is a non-zero when the voltage connected to the positive
*     input is greater than the negative input voltage.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_LPComp_GetCompare(LPCOMP_Type const * base, cy_en_lpcomp_channel_t channel)
{
    uint32_t result;

    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        result = _FLD2VAL(LPCOMP_STATUS_OUT0, LPCOMP_STATUS(base));
    }
    else
    {
        result = _FLD2VAL(LPCOMP_STATUS_OUT1, LPCOMP_STATUS(base));
    }

    return (result);
}


/*******************************************************************************
* Function Name: Cy_LPComp_SetInterruptMask
****************************************************************************//**
*
*  Configures which bits of the interrupt request register will trigger an
*  interrupt event.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param interrupt
*  uint32_t interruptMask: Bit Mask of interrupts to set.
*  * Bit 0: COMP0 interrupt mask
*  * Bit 1: COMP1 interrupt mask
*
* \return None.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LPComp_SetInterruptMask(LPCOMP_Type* base, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_LPCOMP_IS_INTR_VALID(interrupt));

    LPCOMP_INTR_MASK(base) |= interrupt;
}


/*******************************************************************************
* Function Name: Cy_LPComp_GetInterruptMask
****************************************************************************//**
*
*  Returns an interrupt mask.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \return bit mapping information:
*   * Bit 0: COMP0 interrupt mask
*   * Bit 1: COMP1 interrupt mask
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_LPComp_GetInterruptMask(LPCOMP_Type const * base)
{
    return (LPCOMP_INTR_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_LPComp_GetInterruptStatusMasked
****************************************************************************//**
*
* Returns an interrupt request register masked by an interrupt mask.
* Returns the result of the bitwise AND operation between the corresponding
* interrupt request and mask bits.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \return bit mapping information:
*   * Bit 0: COMP0 interrupt masked
*   * Bit 1: COMP1 interrupt masked
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_LPComp_GetInterruptStatusMasked(LPCOMP_Type const * base)
{
    return (LPCOMP_INTR_MASKED(base));
}


/*******************************************************************************
* Function Name: Cy_LPComp_GetInterruptStatus
****************************************************************************//**
*
* Returns the status of two different low-power comparator interrupt requests.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \return bit mapping information:
*   * Bit 0: COMP0 interrupt status
*   * Bit 1: COMP1 interrupt status
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_LPComp_GetInterruptStatus(LPCOMP_Type const * base)
{
    return (_FLD2VAL(CY_LPCOMP_INTR, LPCOMP_INTR(base)));
}


/*******************************************************************************
* Function Name: Cy_LPComp_ClearInterrupt
****************************************************************************//**
*
*  Clears low-power comparator interrupts by setting each bit.
*
* \param *base
*     The low-power comparator register structure pointer.
*
* \param interrupt
*   * Bit 0: COMP0 interrupt status
*   * Bit 1: COMP1 interrupt status
*
* \return None.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LPComp_ClearInterrupt(LPCOMP_Type* base, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_LPCOMP_IS_INTR_VALID(interrupt));
    LPCOMP_INTR(base) |= interrupt;
    (void) LPCOMP_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_LPComp_SetInterrupt
****************************************************************************//**
*
*  Sets a software interrupt request.
*  This function is used in the case of combined interrupt signal from the global
*  signal reference. This function from either component instance can be used
*  to trigger either or both software interrupts. The function sets the INTR_SET interrupt mask.
*
* \param *base
*    The low-power comparator register structure pointer.
*
* \param interrupt
*   * Bit 0: COMP0 interrupt status
*   * Bit 1: COMP1 interrupt status
*
* \return None.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LPComp_SetInterrupt(LPCOMP_Type* base, uint32_t interrupt)
{
    CY_ASSERT_L2(CY_LPCOMP_IS_INTR_VALID(interrupt));
    LPCOMP_INTR_SET(base) = interrupt;
}


/*******************************************************************************
* Function Name: Cy_LPComp_ConnectULPReference
****************************************************************************//**
*
* Connects the local reference generator output to the comparator negative input.
*
* \param *base
* The low-power comparator register structure pointer.
*
* \param channel
* The low-power comparator channel index.
*
* \return None.
*
*******************************************************************************/
__STATIC_INLINE void Cy_LPComp_ConnectULPReference(LPCOMP_Type *base, cy_en_lpcomp_channel_t channel)
{
    CY_ASSERT_L3(CY_LPCOMP_IS_CHANNEL_VALID(channel));

    if (CY_LPCOMP_CHANNEL_0 == channel)
    {
        LPCOMP_CMP0_SW_CLEAR(base) = CY_LPCOMP_CMP0_SW_NEG_Msk;
        LPCOMP_CMP0_SW(base) = _CLR_SET_FLD32U(LPCOMP_CMP0_SW(base), LPCOMP_CMP0_SW_CMP0_VN0, CY_LPCOMP_REF_CONNECTED);
    }
    else
    {
        LPCOMP_CMP1_SW_CLEAR(base) = CY_LPCOMP_CMP1_SW_NEG_Msk;
        LPCOMP_CMP1_SW(base) = _CLR_SET_FLD32U(LPCOMP_CMP1_SW(base), LPCOMP_CMP1_SW_CMP1_VN1, CY_LPCOMP_REF_CONNECTED);
    }
}

/** \} group_lpcomp_functions */

#ifdef __cplusplus
}
#endif

#endif /* CY_IP_MXLPCOMP and CY_IP_MXS22LPCOMP */

#endif /* CY_LPCOMP_PDL_H */

/** \} group_lpcomp */

/* [] END OF FILE */
