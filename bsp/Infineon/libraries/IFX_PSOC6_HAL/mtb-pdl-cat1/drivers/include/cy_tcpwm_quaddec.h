/***************************************************************************//**
* \file cy_tcpwm_quaddec.h
* \version 1.40
*
* \brief
* The header file of the TCPWM Quadrature Decoder driver.
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
#if !defined(CY_TCPWM_QUADDEC_H)
#define CY_TCPWM_QUADDEC_H

#include "cy_tcpwm.h"

#ifdef CY_IP_MXTCPWM

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_tcpwm_quaddec
* Driver API for Quadrature Decoder.
*
* The functions and other declarations used in this part of the driver are in cy_tcpwm_quaddec.h.
* You can also include cy_pdl.h to get access to all functions and declarations in the PDL.
*
* A quadrature decoder is used to decode the output of a quadrature encoder.
* A quadrature encoder senses the position, velocity, and direction of
* an object (for example a rotating axle, or a spinning mouse ball).
* A quadrature decoder can also be used for precision measurement of speed,
* acceleration, and position of a motor's rotor, or with a rotary switch to
* determine user input.
*
* The Quadrature Decoder has the following features:
* * 16- or 32-bit Counter.
* * Period Register. This is only available in TCPWM Version 2.
* * Range 0, Range 0 Compare, Range 1 capture, Range 1 Compare Quadrature modes. This is only available in TCPWM Version 2.
* * Counter Resolution of x1, x2, x4, and up/down rotary the frequency of the phiA (Count) and
* phiB (Start) inputs. Up/Down rotary resolution is only available in TCPWM Version 2
* * Interrupt on Terminal Count and Compare or Capture 0. Interrupt on Compare or Capture 1 is only available in TCPWM Version 2.
* * Index Input to determine absolute position
* * A positive edge on phiA increments the counter when phiB is 0 and decrements
* the counter when phiB is 1
* * Two programmable trigger outputs, trig_out0 and trig_out1 that generate a
* trigger on one of the following events Overflow, Underflow, Terminal Count,
* and Compare Match 0/1. The available triggers are dependent on the QuadDec mode.
* All these features are only available in TCPWM Version 2.
* * TC (cc_match) trigger output is only available in TCPWM Version 1.
* * Second Compare Match (CC_MATCH1) event is only available in TCPWM Version 2.
*
* \section group_tcpwm_quaddec_configuration Configuration Considerations
*
* The QuadDec configuration can be divided to number of sequential
* steps listed below:
* * \ref group_tcpwm_quaddec_config
* * \ref group_tcpwm_quaddec_clock
* * \ref group_tcpwm_quaddec_enable
* * \ref group_tcpwm_quaddec_start
*
* \subsection group_tcpwm_quaddec_config Configure Quadrature
* To configure Quadrature, provide the configuration parameters in the
* \ref cy_stc_tcpwm_quaddec_config_t structure. The Configuration structure
* can be modified through software, but if the configurator in ModusToolbox is used
* then the configuration structure will be updated with the users input. To initialize
* the driver, call \ref Cy_TCPWM_QuadDec_Init function providing a pointer to the populated
* \ref cy_stc_tcpwm_quaddec_config_t structure.
*
* For TCPWM V1 Configuration
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_V1_QuadDec_Init
*
* For TCPWM V2 Configuration
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_V2_QuadDec_Init
*
* \subsection group_tcpwm_quaddec_clock Assign Clock Divider
* The clock source must be connected to proper working.
* Any of the peripheral clock dividers could be used. Use the
* \ref group_sysclk driver API to do that.
*
* \subsection group_tcpwm_quaddec_enable Enable Quadrature Decoder
* Quadrature has to be enabled before starting
*
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_Enable
*
* \subsection group_tcpwm_quaddec_start Start Quadrature Decoder
* Quadrature has to be started
*
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_Start
* \{
*/

/**
* \defgroup group_tcpwm_macros_quaddec          Macros
* \defgroup group_tcpwm_functions_quaddec       Functions
* \defgroup group_tcpwm_data_structures_quaddec Data Structures
* \} */

/**
* \addtogroup group_tcpwm_data_structures_quaddec
* \{
*/

/** Quadrature Decoder configuration structure */
typedef struct cy_stc_tcpwm_quaddec_config
{
    /** Selects the quadrature encoding mode. See \ref group_tcpwm_quaddec_resolution */
    uint32_t    resolution;
    /** Enables an interrupt on the terminal count, capture or compare. See \ref group_tcpwm_interrupt_sources */
    uint32_t    interruptSources;
    /** Configures how the index input behaves. See \ref group_tcpwm_input_modes */
    uint32_t    indexInputMode;
    /** Selects which input the index uses. The inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    indexInput;
    /** Configures how the stop input behaves. See \ref group_tcpwm_input_modes */
    uint32_t    stopInputMode;
    /** Selects which input the stop uses. The inputs are device-specific. See \ref group_tcpwm_input_selection */
    uint32_t    stopInput;
    /** Selects which input the phiA uses. The inputs are device specific. See \ref group_tcpwm_input_selection */
    uint32_t    phiAInput;
    /** Selects which input the phiB uses. The inputs are device specific. See \ref group_tcpwm_input_selection */
    uint32_t    phiBInput;
#if (CY_IP_MXTCPWM_VERSION >= 2U)
    /** Configures how the phiA input behaves. See \ref group_tcpwm_input_modes */
    uint32_t    phiAInputMode;
    /** Configures how the phiB input behaves. See \ref group_tcpwm_input_modes */
    uint32_t    phiBInputMode;
    /**  Sets the QuadDec mode */
    uint32_t    quadMode;
    /**  Sets the period0 of the pwm */
    uint32_t    period0;
    /** Specifies index or wrap-around capture function*/
    bool        captureOnIndex;
    /** Sets the value for Compare 0 */
    uint32_t    compare0;
    /** Sets the value for the buffered Compare 0 */
    uint32_t    compareBuf0;
    /**  If enabled, the compare 0 values are swapped on the terminal count */
    bool        enableCompare0Swap;
    /** Sets the value for Compare 1 */
    uint32_t    compare1;
    /** Sets the value for the buffered Compare 1 */
    uint32_t    compareBuf1;
    /** If enabled, the compare1 values are swapped on the terminal count */
    bool        enableCompare1Swap;
    /** Configures how the capture 0/index 1 input behaves.*/
    uint32_t    capture0OrIndex1InputMode;
    /** Selects which input the capture 0/index 1 uses. The inputs are device-specific. */
    uint32_t    capture0OrIndex1Input;
    /** Configures how the capture1 input behaves. */
    uint32_t    capture1InputMode;
    /** Selects which input the capture 1 uses. The inputs are device-specific. */
    uint32_t    capture1Input;
    /** Configures which internal event generates on output trigger 0. */
    uint32_t    trigger0Event;
    /** Configures which internal event generates on output trigger 1. */
    uint32_t    trigger1Event;
#endif
}cy_stc_tcpwm_quaddec_config_t;
/** \} group_tcpwm_data_structures_quaddec */

/**
* \addtogroup group_tcpwm_macros_quaddec
* \{
* \defgroup group_tcpwm_quaddec_mode QuadDec Mode
* \{
* The quadrature decoder mode.
*/
/** Counter Range between 0x0000 and 0xFFFF / 0xFFFFFFFF (for GRP_CNT_WIDTH = 16 / 32) */
#define CY_TCPWM_QUADDEC_MODE_RANGE0                (0U)
/** Counter Range0 with a compare function */
#define CY_TCPWM_QUADDEC_MODE_RANGE0_CMP            (1U)
/** COUNTER range is between 0x0000 and PERIOD with 1 or 2 Capture functions */
#define CY_TCPWM_QUADDEC_MODE_RANGE1_CAPT           (2U)
/** Same as QUAD_RANGE1_CAPT with 1 or 2 Compare functions */
#define CY_TCPWM_QUADDEC_MODE_RANGE1_CMP            (3U)
/** \} group_tcpwm_quaddec_mode */

/**
* \defgroup group_tcpwm_quaddec_resolution QuadDec Resolution
* \{
* The quadrature decoder resolution.
*/
#define CY_TCPWM_QUADDEC_X1                         (0U)    /**< X1 mode */
#define CY_TCPWM_QUADDEC_X2                         (1U)    /**< X2 mode */
#define CY_TCPWM_QUADDEC_X4                         (2U)    /**< X4 mode */
#define CY_TCPWM_QUADDEC_UP_DOWN_ROTARY_COUNT       (3U)    /**< Up/Down Rotary mode */
/** \} group_tcpwm_quaddec_resolution */

/**
* \defgroup group_tcpwm_quaddec_capture_mode QuadDec CaptureMode
* \{
* The quadrature capture modes.
*/
#define CY_TCPWM_QUADDEC_CAPTURE_ON_INDEX            (0U)   /**< Capture on Index */
#define CY_TCPWM_QUADDEC_CAPTURE_ON_WRAP_AROUND      (1U)   /**< Capture on Wrap Around */
/** \} group_tcpwm_quaddec_capture_mode */

/** \defgroup group_tcpwm_quaddec_status QuadDec Status
* \{
* The quaddec status.
*/
#define CY_TCPWM_QUADDEC_STATUS_DOWN_COUNTING       (0x1UL)        /**< QuadDec is down counting */
#define CY_TCPWM_QUADDEC_STATUS_UP_COUNTING         (0x2UL)        /**< QuadDec is up counting */
/** QuadDec the counter is running */
#define CY_TCPWM_QUADDEC_STATUS_COUNTER_RUNNING     (0x80000000UL)
/** \} group_tcpwm_quaddec_status */


/***************************************
*        Registers Constants
***************************************/
/** \cond INTERNAL */
#define CY_TCPWM_QUADDEC_CTRL_QUADDEC_MODE          (0x3UL)     /**< Quadrature encoding mode for CTRL register */
/** \endcond */
/** \} group_tcpwm_macros_quaddec */

/*******************************************************************************
* Backward compatibility macro. The following code is DEPRECATED and must
* not be used in new projects
*******************************************************************************/
#define Cy_TCPWM_QuadDec_GetCapture         Cy_TCPWM_QuadDec_GetCapture0Val
#define Cy_TCPWM_QuadDec_GetCaptureBuf      Cy_TCPWM_QuadDec_GetCapture0BufVal

/*******************************************************************************
*        Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_tcpwm_functions_quaddec
* \{
*/

cy_en_tcpwm_status_t Cy_TCPWM_QuadDec_Init(TCPWM_Type *base, uint32_t cntNum,
                                           cy_stc_tcpwm_quaddec_config_t const *config);
void Cy_TCPWM_QuadDec_DeInit(TCPWM_Type *base, uint32_t cntNum, cy_stc_tcpwm_quaddec_config_t const *config);
__STATIC_INLINE void Cy_TCPWM_QuadDec_Enable(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_QuadDec_Disable(TCPWM_Type *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetStatus(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCapture0Val(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCapture0BufVal(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCompare0Val(TCPWM_Type *base, uint32_t cntNum, uint32_t compare0);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCompare0Val(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCompare0BufVal(TCPWM_Type *base, uint32_t cntNum, uint32_t compareBuf0);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCompare0BufVal(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_QuadDec_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum, bool enable);
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCounter(TCPWM_Type *base, uint32_t cntNum, uint32_t count);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCounter(TCPWM_Type const *base, uint32_t cntNum);
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCapture1Val (TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCapture1BufVal (TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCompare1Val (TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCompare1BufVal (TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCompare1Val (TCPWM_Type *base, uint32_t cntNum, uint32_t compare1);
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCompare1BufVal (TCPWM_Type *base, uint32_t cntNum, uint32_t compareBuf1);
__STATIC_INLINE void Cy_TCPWM_QuadDec_EnableCompare1Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable);
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetPeriod0(TCPWM_Type *base, uint32_t cntNum, uint32_t period0);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetPeriod0(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetPeriod1(TCPWM_Type *base, uint32_t cntNum, uint32_t period1);
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetPeriod1(TCPWM_Type const *base, uint32_t cntNum);
__STATIC_INLINE void Cy_TCPWM_QuadDec_TriggerIndex1 (TCPWM_Type *base, uint32_t cntNum);
#endif

/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_Enable
****************************************************************************//**
*
* Enables the counter in the TCPWM block for the QuadDec operation.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_V1_QuadDec_Init
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_V2_QuadDec_Init
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_Enable(TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_Enable_Single(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_Disable
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
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_DeInit
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_Disable(TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_Disable_Single(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetStatus
****************************************************************************//**
*
* Returns the status of the QuadDec whether it is running or not. In case the
* QuadDec is running, status will also provide information on counting up/down.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The status. See \ref group_tcpwm_quaddec_status
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_GetStatus
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetStatus(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t status;

#if (CY_IP_MXTCPWM_VERSION == 1U)

        status = TCPWM_CNT_STATUS(base, cntNum);

        /* Generates proper up counting status. Is not generated by HW */
        status &= ~CY_TCPWM_QUADDEC_STATUS_UP_COUNTING;
        status |= ((~status & CY_TCPWM_QUADDEC_STATUS_DOWN_COUNTING & (status >> TCPWM_CNT_STATUS_RUNNING_Pos)) <<
                   CY_TCPWM_CNT_STATUS_UP_POS);
#else
        status = TCPWM_GRP_CNT_STATUS(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);

        /* Generates proper up counting status. Is not generated by HW */
        status &= ~CY_TCPWM_QUADDEC_STATUS_UP_COUNTING;
        status |= ((~status & CY_TCPWM_QUADDEC_STATUS_DOWN_COUNTING & (status >> TCPWM_GRP_CNT_V2_STATUS_RUNNING_Pos)) <<
               CY_TCPWM_CNT_STATUS_UP_POS);

        /* For backward compatibility, we set TCPWM_CNT_STATUS_RUNNING_Pos with TCPWM_GRP_CNT_V2_STATUS_RUNNING */
        status |= (_FLD2VAL(TCPWM_GRP_CNT_V2_STATUS_RUNNING, status) << TCPWM_CNT_STATUS_RUNNING_Pos);
#endif

    return(status);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetCapture0Val
****************************************************************************//**
*
* Returns the capture value.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The capture value.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_Capture
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCapture0Val(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetCapture0BufVal
****************************************************************************//**
*
* Returns the buffered capture value.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The buffered capture value.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_Capture
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCapture0BufVal(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0BufVal(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_SetCompare0Val
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
* The Compare 0 value.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetCompare0Val
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCompare0Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare0)
{
    Cy_TCPWM_Block_SetCC0Val(base, cntNum, compare0);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetCompare0Val
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
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetCompare0Val
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCompare0Val(TCPWM_Type const  *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_SetCompare0BufVal
****************************************************************************//**
*
* Sets the Buffered Compare 0 value when the compare mode is enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param compareBuf0
* The Buffered Compare 0 value.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetCompare0BufVal
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCompare0BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compareBuf0)
{
    Cy_TCPWM_Block_SetCC0BufVal(base, cntNum, compareBuf0);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetCompare0BufVal
****************************************************************************//**
*
* Returns Buffered Compare 0 Value.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Buffered Compare 0 Value.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetCompare0BufVal
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCompare0BufVal(TCPWM_Type const  *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC0BufVal(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_EnableCompare0Swap
****************************************************************************//**
*
* Enables the comparison swap of compare 0 and compareBuf 0 when the comparison
* value is true
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
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_EnableCompare0Swap
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_EnableCompare0Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
    Cy_TCPWM_Block_EnableCompare0Swap(base, cntNum, enable);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_SetCounter
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
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetCounter
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCounter(TCPWM_Type *base, uint32_t cntNum, uint32_t count)
{
    Cy_TCPWM_Block_SetCounter(base, cntNum, count);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetCounter
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
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_GetCounter
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCounter(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCounter(base, cntNum);
}
#if (CY_IP_MXTCPWM_VERSION >= 2U) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_SetCompare1Val
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
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetCompare1Val
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCompare1Val(TCPWM_Type *base, uint32_t cntNum,  uint32_t compare1)
{
    Cy_TCPWM_Block_SetCC1Val(base, cntNum, compare1);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetCompare1Val
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
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetCompare1Val
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCompare1Val(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1Val(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_SetCompare1BufVal
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
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetCompare1BufVal
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetCompare1BufVal(TCPWM_Type *base, uint32_t cntNum,  uint32_t compareBuf1)
{
    Cy_TCPWM_Block_SetCC1BufVal(base, cntNum, compareBuf1);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetCompare1BufVal
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
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetCompare1BufVal
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCompare1BufVal(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1BufVal(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetCapture1Val
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
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCapture1Val (TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1Val(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetCapture1BufVal
****************************************************************************//**
*
* Returns the buffered capture 1 value when capture mode is enabled.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* Buffered capture 1 value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetCapture1BufVal (TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetCC1BufVal(base, cntNum);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_EnableCompare1Swap
****************************************************************************//**
*
* Enables the comparison swap of compare 1 and compareBuf 1 when the comparison
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
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_EnableCompare1Swap
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_EnableCompare1Swap(TCPWM_Type *base, uint32_t cntNum,  bool enable)
{
    Cy_TCPWM_Block_EnableCompare1Swap(base, cntNum, enable);
}
/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_SetPeriod0
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
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetPeriod0
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetPeriod0(TCPWM_Type *base, uint32_t cntNum,  uint32_t period0)
{
    Cy_TCPWM_Block_SetPeriod(base, cntNum, period0);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetPeriod0
****************************************************************************//**
*
* Returns the value in the period 0 register.
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
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetPeriod0
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetPeriod0(TCPWM_Type const *base, uint32_t cntNum)
{
    return Cy_TCPWM_Block_GetPeriod(base, cntNum);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_SetPeriod1
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
* \param period1
* The value to write into a period 1.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetPeriod1
*
* * \note supported only in TCPWM_ver2
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_SetPeriod1(TCPWM_Type *base, uint32_t cntNum,  uint32_t period1)
{
    TCPWM_GRP_CNT_PERIOD_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum) = period1;
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_GetPeriod1
****************************************************************************//**
*
* Returns the value in the period 1 register.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \return
* The current period 1 value.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_SetPeriod1
*
* \note supported only in TCPWM_ver2
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_TCPWM_QuadDec_GetPeriod1(TCPWM_Type const *base, uint32_t cntNum)
{
    uint32_t period1 = 0UL;

    period1 = TCPWM_GRP_CNT_PERIOD_BUFF(base, TCPWM_GRP_CNT_GET_GRP(cntNum), cntNum);
    return period1;
}

/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_TriggerIndex1
****************************************************************************//**
*
* Triggers a software index 1.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_TriggerIndex1
*
*******************************************************************************/
__STATIC_INLINE void Cy_TCPWM_QuadDec_TriggerIndex1 (TCPWM_Type *base, uint32_t cntNum)
{
    Cy_TCPWM_TriggerCapture0(base, cntNum);
}
#endif
/** \} group_tcpwm_functions_quaddec */

/** \} group_tcpwm_quaddec */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXTCPWM */

#endif /* CY_TCPWM_QUADDEC_H */

/* [] END OF FILE */
