/***************************************************************************//**
* \file cy_tcpwm_shiftreg.h
* \version 1.40
*
* \brief
* The header file of the TCPWM Shift Register driver.
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

#if !defined(CY_TCPWM_SHIFTREG_H)
#define CY_TCPWM_SHIFTREG_H

#include "cy_tcpwm.h"

#ifdef CY_IP_MXTCPWM

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_tcpwm_shiftreg
* Driver API for Shift Register.
*
* The functions and other declarations used in this part of the driver are in cy_tcpwm_shiftreg.h.
* You can also include cy_pdl.h to get access to all functions and declarations in the PDL.
*
* Shift Register functionality shifts the counter value to the right.
* A shift register is used to apply a signal delay function which can be used
* eg: in detecting frequency shift keying (FSK) signals.
* A shift register is also used in parallel-in to serial-out data conversion
* and serial-in to parallel-out data conversion.
*
* Features:
* * 16- or 32-bit Counter
* * 2 compare (CC0/CC1) registers with double buffer.
* * Programmable Counter taps through PERIOD_BUFF register.
* * Line output generated from a XOR combination of all enabled counter taps (bit position) defined by PERIOD_BUFF.
* * Programmable Compare Register. Compare value can be swapped with a buffered compare value on comparison event.
* * Interrupt on Comparison match events (CC0_MATCH/CC1_MATCH).
* * Start, Reload, Stop, Shift, and Serial-in Inputs.
* * Comparison match and Line Outputs.
* * Line output can be output with invert polarity.
*
* \note Shift Register mode is available only in TCPWM Version 2
*
* \section group_tcpwm_shiftreg_configuration Configuration Considerations
* The Shift Register configuration can be divided to number of sequential
* steps listed below:
* * \ref group_tcpwm_shiftreg_config
* * \ref group_tcpwm_shiftreg_pins
* * \ref group_tcpwm_shiftreg_clock
* * \ref group_tcpwm_shiftreg_enable
* * \ref group_tcpwm_shiftreg_start
*
* \subsection group_tcpwm_shiftreg_config Configure Shift Register
* To configure Shift Register, provide the configuration parameters in the
* \ref cy_stc_tcpwm_shiftreg_config_t structure. The configuration structure
* can be modified through software, but if the configurator in ModusToolbox is used
* then the configuration structure will be updated with the users inputs. To initialize
* the driver, call \ref Cy_TCPWM_ShiftReg_Init function providing a pointer to the
* populated \ref cy_stc_tcpwm_shiftreg_config_t structure.
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_Init
*
* \subsection group_tcpwm_shiftreg_pins Assign and Configure Pins
* The dedicated TCPWM pins can be used. The HSIOM register must be configured to
* connect the block to the pins. Use the \ref group_gpio driver API to do that.
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_Pins
*
* \subsection group_tcpwm_shiftreg_clock Assign Clock Divider
* The clock source must be connected for proper operation.
* Any of the peripheral clock dividers could be used. Use the
* \ref group_sysclk driver API to do that.
*
* \subsection group_tcpwm_shiftreg_enable Enable Shift Register
* Shift Register has to be enabled before starting
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_Enable
*
* \subsection group_tcpwm_shiftreg_start Start Shift Register
* To start Shift Register operation \ref Cy_TCPWM_TriggerStart_Single API can be used.
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_Start
* \{
*/

/**
* \defgroup group_tcpwm_macros_shiftreg          Macros
* \defgroup group_tcpwm_functions_shiftreg       Functions
* \defgroup group_tcpwm_data_structures_shiftreg Data Structures
* \} */

/**
* \addtogroup group_tcpwm_data_structures_shiftreg
* \{
*/

#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
/** Shift Register configuration structure */
typedef struct cy_stc_tcpwm_shiftreg_config
{
    uint32_t    clockPrescaler;     /**< Sets the clock prescaler inside the TCWPM block.*/
    uint32_t    tapsEnabled;        /**< In shift register this sets the enabled taps. */
    uint32_t    compare0;           /**< Sets the value for Compare 0. */
    uint32_t    compareBuf0;        /**< Sets the value for the buffered Compare 0. */
    bool        enableCompare0Swap; /**< If enabled, the compare 0 values are swapped on the terminal count. */
    uint32_t    compare1;           /**< Sets the value for Compare 1. */
    uint32_t    compareBuf1;        /**< Sets the value for the buffered Compare 1. */
    bool        enableCompare1Swap; /**< If enabled, the compare1 values are swapped on the terminal count. */
    uint32_t    interruptSources;   /**< Enables an interrupt on the terminal count, capture or compare.  */
    uint32_t    invertShiftRegOut;  /**< Inverts the ShiftReg output.*/
    uint32_t    invertShiftRegOutN; /**< Inverts the ShiftReg compliment output.*/
    uint32_t    reloadInputMode;    /**< Configures how the reload input behaves.  */
    uint32_t    reloadInput;        /**< Selects which input the reload uses. The inputs are device-specific.  */
    uint32_t    startInputMode;     /**< Configures how the start input behaves. See \ref group_tcpwm_input_modes. */
    uint32_t    startInput;         /**< Selects which input the start uses. The inputs are device-specific. */
    uint32_t    killInputMode;      /**< Configures how the kill0 input behaves. */
    uint32_t    killInput;          /**< Selects which input the kill0 uses. The inputs are device-specific. */
    uint32_t    shiftInputMode;     /**< Configures how the shift input behaves. */
    uint32_t    shiftInput;         /**< Selects which input the shift uses. The inputs are device-specific. */
    uint32_t    serialInputMode;    /**< Configures how the serial input behaves. */
    uint32_t    serialInput;        /**< Selects which input the serial uses. Inputs are device-specific. */
    uint32_t    shiftRegOnDisable;  /**< Specifies the behavior of the ShiftReg outputs line_out and line_compl_out while the Shift Register is disabled. */
    uint32_t    trigger0Event;      /**< Configures which internal event generates on output trigger 0. */
    uint32_t    trigger1Event;      /**< Configures which internal event generates on output trigger 1. */
}cy_stc_tcpwm_shiftreg_config_t;

#else

typedef struct cy_stc_tcpwm_shiftreg_config cy_stc_tcpwm_shiftreg_config_t;

#endif /* CY_IP_MXTCPWM_VERSION >= 2U */

/** \} group_tcpwm_data_structures_shiftreg */

/**
* \addtogroup group_tcpwm_macros_shiftreg
* \{
* \defgroup group_tcpwm_shiftreg_clk_prescalers Shift Register CLK Prescaler values
* \{
* Clock prescaler values.
*/
#define CY_TCPWM_SHIFTREG_PRESCALER_DIVBY_1      (0U) /**< Divide by 1 */
#define CY_TCPWM_SHIFTREG_PRESCALER_DIVBY_2      (1U) /**< Divide by 2 */
#define CY_TCPWM_SHIFTREG_PRESCALER_DIVBY_4      (2U) /**< Divide by 4 */
#define CY_TCPWM_SHIFTREG_PRESCALER_DIVBY_8      (3U) /**< Divide by 8 */
#define CY_TCPWM_SHIFTREG_PRESCALER_DIVBY_16     (4U) /**< Divide by 16 */
#define CY_TCPWM_SHIFTREG_PRESCALER_DIVBY_32     (5U) /**< Divide by 32 */
#define CY_TCPWM_SHIFTREG_PRESCALER_DIVBY_64     (6U) /**< Divide by 64 */
#define CY_TCPWM_SHIFTREG_PRESCALER_DIVBY_128    (7U) /**< Divide by 128 */
/** \} group_tcpwm_shiftreg_clk_prescalers */

/** \defgroup group_tcpwm_shiftreg_output_line Shift Register Output Lines
* Specifies the Shift Register output line.
* \{
*/
#define    CY_TCPWM_SHIFTREG_LINE_OUT         (0U)    /**< Shift Register Line output */
#define    CY_TCPWM_SHIFTREG_LINE_OUT_INV     (1U)    /**< Shift Register Line output compliment */
/** \} group_tcpwm_shiftreg_output_line */

/** \defgroup group_tcpwm_shiftreg_output_invert Shift Register output invert
* \{
* Output invert modes.
*/
#define CY_TCPWM_SHIFTREG_INVERT_ENABLE          (1U)  /**< Invert the output mode */
#define CY_TCPWM_SHIFTREG_INVERT_DISABLE         (0U)  /**< Do not invert the output mode */
/** \} group_tcpwm_shiftreg_output_invert */


/** \defgroup group_tcpwm_shiftreg_output_on_disable Shift Register Disabled Output
* Specifies the behavior of the Shift Register outputs while Shift Register is disabled.
* \{
*/
#define    CY_TCPWM_SHIFTREG_OUTPUT_HIGHZ    (0U)    /**< Shift Register output (default) high impedance */
#define    CY_TCPWM_SHIFTREG_OUTPUT_RETAIN   (1U)    /**< Shift Register outputs are retained */
#define    CY_TCPWM_SHIFTREG_OUTPUT_LOW      (2U)    /**< Shift Register output LOW */
#define    CY_TCPWM_SHIFTREG_OUTPUT_HIGH     (3U)    /**< Shift Register output HIGH */
/** \} group_tcpwm_shiftreg_output_on_disable */

/** \defgroup group_tcpwm_shiftreg_status Shift Register Status
* \{
* The Shift Register status.
*/
#define CY_TCPWM_SHIFTREG_STATUS_RUNNING (0x00008000UL) /**< Shift Register is running */
/** \} group_tcpwm_shiftreg_status */

/** \} group_tcpwm_macros_shiftreg */

/***************************************
*        Registers Constants
***************************************/

/** \cond INTERNAL */
#define CY_TCPWM_MODE_SHIFTREG           (7U)

/** \endcond */


/*******************************************************************************
*        Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_tcpwm_functions_shiftreg
* \{
*/

cy_en_tcpwm_status_t Cy_TCPWM_ShiftReg_Init(TCPWM_Type const *base, uint32_t cntNum, cy_stc_tcpwm_shiftreg_config_t const *config);
void Cy_TCPWM_ShiftReg_DeInit(TCPWM_Type const *base, uint32_t cntNum, cy_stc_tcpwm_shiftreg_config_t const *config);
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
__STATIC_INLINE void Cy_TCPWM_ShiftReg_Enable(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_ShiftReg_Disable(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetStatus(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCompare0Val(TCPWM_Type *base, uint32_t cntNum, uint32_t compare0);
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCompare0Val(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCompare0BufVal(TCPWM_Type *base, uint32_t cntNum, uint32_t compareBuf0);
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCompare0BufVal(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_ShiftReg_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum, bool enable);
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCompare1Val(TCPWM_Type *base, uint32_t cntNum, uint32_t compare1);
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCompare1Val(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCompare1BufVal(TCPWM_Type *base, uint32_t cntNum, uint32_t compareBuf1);
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCompare1BufVal(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_ShiftReg_EnableCompare1Swap(TCPWM_Type *base, uint32_t cntNum, bool enable);
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCounter(TCPWM_Type *base, uint32_t cntNum, uint32_t count);
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCounter(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetTaps(TCPWM_Type *base, uint32_t cntNum, uint32_t taps);
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetTaps(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_LineOutStatus (TCPWM_Type const *base, uint32_t cntNum, uint32_t shiftRegOutSelect);


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_Enable
****************************************************************************//**
*
* Enables the counter in the TCPWM block for the Shift Register operation.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_Enable
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_ShiftReg_Enable(TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_Enable_Single(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_Disable
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
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_Disable
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_ShiftReg_Disable(TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_Disable_Single(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_GetStatus
****************************************************************************//**
*
* Returns the status of the Shift Register whether it is running or not.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The status. See \ref group_tcpwm_shiftreg_status
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_GetStatus
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetStatus(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t status = 0UL;

    status = TCPWM_GRP_CNT_STATUS(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);

    return(status);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_SetCompare0Val
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
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_SetCompare0Val
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCompare0Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare0)
{
    Cy_TCPWM_Block_SetCC0Val(base, cntNum, compare0);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_GetCompare0Val
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
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_SetCompare0Val
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCompare0Val(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_SetCompare0BufVal
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
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_SetCompare0BufVal
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCompare0BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compareBuf0)
{
    Cy_TCPWM_Block_SetCC0BufVal(base, cntNum, compareBuf0);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_GetCompare0BufVal
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
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_SetCompare0BufVal
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCompare0BufVal(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0BufVal(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_SetCompare1Val
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
* The Compare 1 value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCompare1Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare1)
{
    Cy_TCPWM_Block_SetCC1Val(base, cntNum, compare1);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_GetCompare1Val
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
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCompare1Val(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_SetCompare1BufVal
****************************************************************************//**
*
* Sets the buffered compare value for Compare 1 when the compare mode enabled.
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
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCompare1BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compareBuf1)
{
    Cy_TCPWM_Block_SetCC1BufVal(base, cntNum, compareBuf1);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_GetCompare1BufVal
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
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCompare1BufVal(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1BufVal(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_EnableCompare0Swap
****************************************************************************//**
*
* Enables the comparison swap of compare 0 and compareBuf 0 on
* corresponding command or external trigger.
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
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_EnableCompare0Swap
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_ShiftReg_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
     Cy_TCPWM_Block_EnableCompare0Swap(base, cntNum, enable);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_EnableCompare1Swap
****************************************************************************//**
*
* Enables the comparison swap of compare 1 and compareBuf 1 on
* corresponding command or external trigger.
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
__STATIC_INLINE void Cy_TCPWM_ShiftReg_EnableCompare1Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
    Cy_TCPWM_Block_EnableCompare1Swap(base, cntNum, enable);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_SetCounter
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
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_SetCounter
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetCounter(TCPWM_Type *base, uint32_t cntNum,  uint32_t count)
{
    Cy_TCPWM_Block_SetCounter(base, cntNum, count);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_GetCounter
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
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_SetCounter
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetCounter(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCounter(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_SetTaps
****************************************************************************//**
*
* Sets which taps are enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param taps
* The taps that will be enabled.
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_SetTaps
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_ShiftReg_SetTaps(TCPWM_Type *base, uint32_t cntNum,  uint32_t taps)
{
    TCPWM_GRP_CNT_PERIOD_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = taps;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_GetTaps
****************************************************************************//**
*
* Returns which taps are enabled.
*
* \param base
* The pointer to a COUNTER PWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Returns which taps are enabled.
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_SetTaps
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_GetTaps(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t result = 0UL;

    result = TCPWM_GRP_CNT_PERIOD_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
    return result;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_LineOutStatus
****************************************************************************//**
*
* Returns the current level of the selected Shift Register output line.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param shiftRegOutSelect
* Defines which Shift Register output line is being checked: line_out or line_out_inv.
*
* \return
* The current Shift Register output line level.
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_LineOutStatus
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_ShiftReg_LineOutStatus (TCPWM_Type const *base, uint32_t cntNum, uint32_t shiftRegOutSelect)
{
    uint32_t status = 0UL;

    status = TCPWM_GRP_CNT_STATUS(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);

     switch(shiftRegOutSelect)
     {
         case CY_TCPWM_SHIFTREG_LINE_OUT:
             status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_LINE_OUT, status);
             break;
         case CY_TCPWM_SHIFTREG_LINE_OUT_INV:
             status = _FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_LINE_COMPL_OUT, status);
             break;
         default:
             /* Not a Valid Line output */
             CY_ASSERT_L3(false);
             break;
    }
    return status;
}

#endif /* CY_IP_MXTCPWM_VERSION >= 2U */
/** \} group_tcpwm_functions_shiftreg */

/** \} group_tcpwm_shiftreg */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXTCPWM */

#endif /* CY_TCPWM_SHIFTREG_H */

/* [] END OF FILE */
