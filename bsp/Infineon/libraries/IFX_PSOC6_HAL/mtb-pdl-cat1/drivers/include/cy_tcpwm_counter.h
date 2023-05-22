/***************************************************************************//**
* \file cy_tcpwm_counter.h
* \version 1.40
*
* \brief
* The header file of the TCPWM Timer Counter driver.
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
#if !defined(CY_TCPWM_COUNTER_H)
#define CY_TCPWM_COUNTER_H

#include "cy_tcpwm.h"

#ifdef CY_IP_MXTCPWM

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_tcpwm_counter
* \{
* Driver API for Timer/Counter.
*
* The functions and other declarations used in this part of the driver are
* in cy_tcpwm_counter.h. You can also include cy_pdl.h
* to get access to all functions and declarations in the PDL.
*
* Use Timer/Counter mode whenever a specific timing interval or measurement is
* needed. Examples include:
* * Creating a periodic interrupt for running other system tasks
* * Measuring frequency of an input signal
* * Measuring pulse width of an input signal
* * Measuring time between two external events
* * Counting events
* * Triggering other system resources after x number events
* * Capturing time stamps when events occur
*
* The Timer/Counter has the following features:
* * 16- or 32-bit Timer/Counter.
* * Programmable Period Register.
* * Programmable Compare Register. Compare value can be swapped with a
* buffered compare value on comparison event.
* * Capture with buffer register.
* * Count Up, Count Down, or Count Up and Down Counting modes.
* * Continuous or One Shot Run modes.
* * Interrupt on Terminal Count and Compare or Capture 0. Interrupt on Compare or Capture 1 is only available in TCPWM Version 2.
* * Start, Reload, Stop, Capture, and Count Inputs.
* * 2 compare (CC0/CC1) registers with double buffer, Capture 1 event. Second compare
* register and Capture 1 event are available only in TCPWM Version 2.
* * Two programmable trigger outputs, trig_out0 and trig_out1 that generate a
* trigger on one of the following events Overflow, Underflow, Terminal Count,
* and Compare Match 0/1. The available triggers are dependent on the Timer/Counter mode.
* All these features are only available in TCPWM Version 2.
* * Overflow, Underflow, and Compare(cc_match) trigger outputs are only available in TCPWM Version 1.
* * Second Compare Match (CC_MATCH1) event is only available in TCPWM Version 2.
*
* \section group_tcpwm_counter_configuration Configuration Considerations
*
* The Counter configuration can be divided to number of sequential
* steps listed below:
* * \ref group_tcpwm_counter_config
* * \ref group_tcpwm_counter_clock
* * \ref group_tcpwm_counter_enable
* * \ref group_tcpwm_counter_start
*
* \subsection group_tcpwm_counter_config Configure Counter
* To configure Counter, provide the configuration parameters in the
* \ref cy_stc_tcpwm_counter_config_t structure. The Configuration structure
* can be modified through software, but if the configurator in ModusToolbox is used
* then the configuration structure will be updated with the users input. To initialize
* the driver, call \ref Cy_TCPWM_Counter_Init function providing a pointer to the populated
* \ref cy_stc_tcpwm_counter_config_t structure.
*
* For TCPWM V1 Configuration
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_V1_Counter_Init
*
* TCPWM V2 Configuration
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_V2_Counter_Init
*
* \subsection group_tcpwm_counter_clock Assign Clock Divider
* The clock source must be connected to proper working.
* Any of the peripheral clock dividers could be used. Use the
* \ref group_sysclk driver API to do that.
*
* \subsection group_tcpwm_counter_enable Enable Counter
* Counter has to be enabled before starting
*
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_Enable
*
* \subsection group_tcpwm_counter_start Start Counter
* Counter has to be started
*
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_Start
*
*/

/**
* \defgroup group_tcpwm_macros_counter          Macros
* \defgroup group_tcpwm_functions_counter       Functions
* \defgroup group_tcpwm_data_structures_counter Data Structures
* \} */

/**
* \addtogroup group_tcpwm_data_structures_counter
* \{
*/

/** Counter Timer configuration structure */
typedef struct cy_stc_tcpwm_counter_config
{
    uint32_t    period;             /**< Sets the period of the counter */
    /** Sets the clock prescaler inside the TCWPM block. See \ref group_tcpwm_counter_clk_prescalers */
    uint32_t    clockPrescaler;
    uint32_t    runMode;            /**< Sets the run mode. See \ref group_tcpwm_counter_run_modes */
    uint32_t    countDirection;     /**< Sets the counter direction. See \ref group_tcpwm_counter_direction */
    /** The counter can either compare or capture a value. See \ref group_tcpwm_counter_compare_capture */
    uint32_t    compareOrCapture;
    uint32_t    compare0;           /**< Sets the value for Compare0*/
    uint32_t    compare1;           /**< Sets the value for Compare1*/
    bool        enableCompareSwap;  /**< If enabled, the compare values are swapped each time the comparison is true */
    /** Enabled an interrupt on the terminal count, capture or compare. See \ref group_tcpwm_interrupt_sources */
    uint32_t    interruptSources;
    uint32_t    captureInputMode;   /**< Configures how the capture input behaves. See \ref group_tcpwm_input_modes */
    /** Selects which input the capture uses, the inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    captureInput;
    uint32_t    reloadInputMode;    /**< Configures how the reload input behaves. See \ref group_tcpwm_input_modes */
    /** Selects which input the reload uses, the inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    reloadInput;
    uint32_t    startInputMode;     /**< Configures how the start input behaves. See \ref group_tcpwm_input_modes */
    /** Selects which input the start uses, the inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    startInput;
    uint32_t    stopInputMode;      /**< Configures how the stop input behaves. See \ref group_tcpwm_input_modes */
    /** Selects which input the stop uses, the inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    stopInput;
    uint32_t    countInputMode;     /**< Configures how the count input behaves. See \ref group_tcpwm_input_modes */
    uint32_t    countInput;         /**< Selects which input the count uses, the inputs are device-specific. See \ref group_tcpwm_input_selection */
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
    uint32_t    capture1InputMode;  /**< Configures how the capture1 input behaves. See \ref group_tcpwm_input_modes */
    uint32_t    capture1Input;      /**< Selects which input the capture1 uses, the inputs are device-specific. */
    /** See \ref group_tcpwm_input_selection */
    bool        enableCompare1Swap; /**< If enabled, the compare1 values are swapped each time the comparison is true */
    uint32_t    compare2;           /**< Sets the value for Compare1  */
    uint32_t    compare3;           /**< Sets the value for the buffered Compare1 */
    uint32_t    trigger0Event;      /**< Configures which internal event generates on output trigger 0*/
    uint32_t    trigger1Event;        /**< Configures which internal event generates on output trigger 1*/
#endif
}cy_stc_tcpwm_counter_config_t;
/** \} group_tcpwm_data_structures_counter */

/**
* \addtogroup group_tcpwm_macros_counter
* \{
* \defgroup group_tcpwm_counter_run_modes Counter Run Modes
* \{
* Run modes for the counter timer.
*/
#define CY_TCPWM_COUNTER_ONESHOT                (1U)    /**< Counter runs once and then stops */
#define CY_TCPWM_COUNTER_CONTINUOUS             (0U)    /**< Counter runs forever */
/** \} group_tcpwm_counter_run_modes */

/** \defgroup group_tcpwm_counter_direction Counter Direction
* The counter directions.
* \{
*/
#define CY_TCPWM_COUNTER_COUNT_UP               (0U)    /**< Counter counts up */
#define CY_TCPWM_COUNTER_COUNT_DOWN             (1U)    /**< Counter counts down */
/** Counter counts up and down terminal count only occurs on underflow. */
#define CY_TCPWM_COUNTER_COUNT_UP_DOWN_1        (2U)
/** Counter counts up and down terminal count occurs on both overflow and underflow. */
#define CY_TCPWM_COUNTER_COUNT_UP_DOWN_2        (3U)
/** \} group_tcpwm_counter_direction */

/** \defgroup group_tcpwm_counter_clk_prescalers Counter CLK Prescalers
* \{
* The clock prescaler values.
*/
#define CY_TCPWM_COUNTER_PRESCALER_DIVBY_1      (0U) /**< Divide by 1 */
#define CY_TCPWM_COUNTER_PRESCALER_DIVBY_2      (1U) /**< Divide by 2 */
#define CY_TCPWM_COUNTER_PRESCALER_DIVBY_4      (2U) /**< Divide by 4 */
#define CY_TCPWM_COUNTER_PRESCALER_DIVBY_8      (3U) /**< Divide by 8 */
#define CY_TCPWM_COUNTER_PRESCALER_DIVBY_16     (4U) /**< Divide by 16 */
#define CY_TCPWM_COUNTER_PRESCALER_DIVBY_32     (5U) /**< Divide by 32 */
#define CY_TCPWM_COUNTER_PRESCALER_DIVBY_64     (6U) /**< Divide by 64 */
#define CY_TCPWM_COUNTER_PRESCALER_DIVBY_128    (7U) /**< Divide by 128 */
/** \} group_tcpwm_counter_clk_prescalers */

/** \defgroup group_tcpwm_counter_compare_capture Counter Compare Capture
* \{
* A compare or capture mode.
*/
#define CY_TCPWM_COUNTER_MODE_CAPTURE           (2U)  /**< Timer/Counter is in Capture Mode */
#define CY_TCPWM_COUNTER_MODE_COMPARE           (0U)  /**< Timer/Counter is in Compare Mode */
/** \} group_tcpwm_counter_compare_capture */

/** \defgroup group_tcpwm_counter_status Counter Status
* \{
* The counter status.
*/
#define CY_TCPWM_COUNTER_STATUS_DOWN_COUNTING   (0x1UL)        /**< Timer/Counter is down counting */
#define CY_TCPWM_COUNTER_STATUS_UP_COUNTING     (0x2UL)        /**< Timer/Counter is up counting */

/** Timer/Counter is running */
#define CY_TCPWM_COUNTER_STATUS_COUNTER_RUNNING (0x80000000UL)

/** \} group_tcpwm_counter_status */
/** \} group_tcpwm_macros_counter */


/*******************************************************************************
* Backward compatibility macro. The following code is DEPRECATED and must
* not be used in new projects
*******************************************************************************/
#define Cy_TCPWM_Counter_GetCapture         Cy_TCPWM_Counter_GetCapture0Val
#define Cy_TCPWM_Counter_GetCaptureBuf      Cy_TCPWM_Counter_GetCapture0BufVal
#define Cy_TCPWM_Counter_SetCompare0        Cy_TCPWM_Counter_SetCompare0Val
#define Cy_TCPWM_Counter_GetCompare0        Cy_TCPWM_Counter_GetCompare0Val
#define Cy_TCPWM_Counter_SetCompare1        Cy_TCPWM_Counter_SetCompare0BufVal
#define Cy_TCPWM_Counter_GetCompare1        Cy_TCPWM_Counter_GetCompare0BufVal
#define Cy_TCPWM_Counter_EnableCompareSwap  Cy_TCPWM_Counter_EnableCompare0Swap

/*******************************************************************************
*        Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_tcpwm_functions_counter
* \{
*/
cy_en_tcpwm_status_t Cy_TCPWM_Counter_Init(TCPWM_Type *base, uint32_t cntNum,
                                           cy_stc_tcpwm_counter_config_t const *config);
void Cy_TCPWM_Counter_DeInit(TCPWM_Type *base, uint32_t cntNum, cy_stc_tcpwm_counter_config_t const *config);
__STATIC_INLINE void Cy_TCPWM_Counter_Enable(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Counter_Disable(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetStatus(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCapture0Val(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCapture0BufVal(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Counter_SetCompare0Val(TCPWM_Type *base, uint32_t cntNum, uint32_t compare0);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCompare0Val(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Counter_SetCompare0BufVal(TCPWM_Type *base, uint32_t cntNum, uint32_t compare1);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCompare0BufVal(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Counter_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum, bool enable);
__STATIC_INLINE void Cy_TCPWM_Counter_SetCounter(TCPWM_Type *base, uint32_t cntNum, uint32_t count);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCounter(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Counter_SetPeriod(TCPWM_Type *base, uint32_t cntNum, uint32_t period);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetPeriod(TCPWM_Type const *base, uint32_t cntNum);
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCapture1Val (TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCapture1BufVal (TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCompare1Val (TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCompare1BufVal (TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_Counter_SetCompare1Val (TCPWM_Type *base, uint32_t cntNum, uint32_t compare1);
__STATIC_INLINE void Cy_TCPWM_Counter_SetCompare1BufVal (TCPWM_Type *base, uint32_t cntNum, uint32_t compareBuf1);
__STATIC_INLINE void Cy_TCPWM_Counter_EnableCompare1Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable);
#endif

/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_Enable
****************************************************************************//**
*
* Enables the counter in the TCPWM block for the Counter operation.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_V1_Counter_Init
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_V2_Counter_Init
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_Enable(TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_Enable_Single(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_Disable
****************************************************************************//**
*
* Disables the counter in the TCPWM block.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_DeInit
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_Disable(TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_Disable_Single(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetStatus
****************************************************************************//**
*
* Returns the status of the Counter Timer whether it is running or not. In case the
* Counter is running, status will also provide information on counting up/down. This
* is useful when the counter mode is set to UP_DOWN_1 or UP_DOWN_2.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The status. See \ref group_tcpwm_counter_status
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_GetStatus
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetStatus(TCPWM_Type const  *base, uint32_t cntNum)
{
    uint32_t status;

#if (CY_IP_MXTCPWM_VERSION == 1U)

        status = TCPWM_CNT_STATUS(base, cntNum);

        /* Generates proper up counting status. Is not generated by HW */
        status &= ~CY_TCPWM_COUNTER_STATUS_UP_COUNTING;
        status |= ((~status & CY_TCPWM_COUNTER_STATUS_DOWN_COUNTING & (status >> TCPWM_CNT_STATUS_RUNNING_Pos)) <<
               CY_TCPWM_CNT_STATUS_UP_POS);
#else
        status = TCPWM_GRP_CNT_STATUS(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);

        /* Generates proper up counting status. Is not generated by HW */
        status &= ~CY_TCPWM_COUNTER_STATUS_UP_COUNTING;
        status |= ((~status & CY_TCPWM_COUNTER_STATUS_DOWN_COUNTING & (status >> TCPWM_GRP_CNT_V2_STATUS_RUNNING_Pos)) <<
               CY_TCPWM_CNT_STATUS_UP_POS);

        /* For backward compatibility, we set TCPWM_CNT_STATUS_RUNNING_Pos with TCPWM_GRP_CNT_V2_STATUS_RUNNING */
        status |= (_FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_RUNNING, status) << TCPWM_CNT_STATUS_RUNNING_Pos);
#endif

    return(status);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetCapture0Val
****************************************************************************//**
*
* Returns the capture 0 value when the capture mode is enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The capture 0 value.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_Capture
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCapture0Val(TCPWM_Type const  *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetCapture0BufVal
****************************************************************************//**
*
* Returns the buffered capture 0 value when the capture mode is enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The buffered capture 0 value.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_Capture
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCapture0BufVal(TCPWM_Type const  *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0BufVal(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_SetCompare0Val
****************************************************************************//**
*
* Sets the compare value for Compare0 when the compare mode is enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param compare0
* The Compare0 value.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetCompare0Val
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_SetCompare0Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare0)
{
    Cy_TCPWM_Block_SetCC0Val(base, cntNum, compare0);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetCompare0Val
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
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetCompare0Val
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCompare0Val(TCPWM_Type const  *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_SetCompare0BufVal
****************************************************************************//**
*
* Sets the compare value for Compare1 when the compare mode is enabled.
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
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetCompare0BufVal
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_SetCompare0BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare1)
{
    Cy_TCPWM_Block_SetCC0BufVal(base, cntNum, compare1);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetCompare0BufVal
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
* Buffered Compare 0 value.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetCompare0BufVal
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCompare0BufVal(TCPWM_Type const  *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0BufVal(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_EnableCompare0Swap
****************************************************************************//**
*
* Enables the comparison swap when the comparison value is true.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param enable
* true = swap enabled, false = swap disabled
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_EnableCompare0Swap
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
    Cy_TCPWM_Block_EnableCompare0Swap(base, cntNum, enable);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_SetCounter
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
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetCounter
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_SetCounter(TCPWM_Type *base, uint32_t cntNum, uint32_t count)
{
    Cy_TCPWM_Block_SetCounter(base, cntNum, count);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetCounter
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
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_GetCounter
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCounter(TCPWM_Type const  *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCounter(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_SetPeriod
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
* \param period
* The value to write into a period.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetPeriod
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_SetPeriod(TCPWM_Type *base, uint32_t cntNum,  uint32_t period)
{
    Cy_TCPWM_Block_SetPeriod(base, cntNum, period);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetPeriod
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
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetPeriod
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetPeriod(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetPeriod(base, cntNum);
}

#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_SetCompare1Val
****************************************************************************//**
*
* Sets the compare value for Compare1 when the compare mode enabled.
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
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetCompare1BufVal
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_SetCompare1Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare1)
{
    Cy_TCPWM_Block_SetCC1Val(base, cntNum, compare1);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetCompare1Val
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
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetCompare1BufVal
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCompare1Val(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_SetCompare1BufVal
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
* The buffered Compare1 value.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetCompare1BufVal
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_SetCompare1BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compareBuf1)
{
    Cy_TCPWM_Block_SetCC1BufVal(base, cntNum, compareBuf1);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetCompare1BufVal
****************************************************************************//**
*
* Returns the buffered compare1 value.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Buffered compare1 value.
*
* \funcusage
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_SetCompare1BufVal
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCompare1BufVal(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1BufVal(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetCapture1Val
****************************************************************************//**
*
* Returns capture 1 value when capture mode is enabled
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Capture 1 value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCapture1Val (TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1Val(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_GetCapture1BufVal
****************************************************************************//**
*
* Returns the buffered capture1 value when capture mode is enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Buffered capture1 value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_Counter_GetCapture1BufVal (TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1BufVal(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_Counter_EnableCompare1Swap
****************************************************************************//**
*
* Enables the comparison swap of compare1 and compareBuf1 when the comparison
* value is true
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
* \snippet tcpwm/counter/snippet/main.c snippet_Cy_TCPWM_Counter_EnableCompare1Swap
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_Counter_EnableCompare1Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
    Cy_TCPWM_Block_EnableCompare1Swap(base, cntNum, enable);
}
#endif
/** \} group_tcpwm_functions_counter */

/** \} group_tcpwm_counter */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXTCPWM */

#endif /* CY_TCPWM_COUNTER_H */

/* [] END OF FILE */
