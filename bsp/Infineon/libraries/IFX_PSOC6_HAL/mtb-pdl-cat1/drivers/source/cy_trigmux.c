/***************************************************************************//**
* \file cy_trigmux.c
* \version 1.50
*
* \brief Trigger mux API.
*
********************************************************************************
* \copyright
* Copyright 2016-2020 Cypress Semiconductor Corporation
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

#include "cy_device.h"

#if defined (CY_IP_MXSPERI) || defined (CY_IP_MXPERI)

#include "cy_trigmux.h"

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 14.3', 4, \
'CY_PERI_V1 is not available for CAT1B devices.');

#define CY_TRIGMUX_IS_TRIGTYPE_VALID(trigType)  (((trigType) == TRIGGER_TYPE_EDGE) || \
                                                 ((trigType) == TRIGGER_TYPE_LEVEL))

#define CY_TRIGMUX_V1_IS_CYCLES_VALID(cycles)   (CY_TRIGGER_INFINITE >= (cycles))
#define CY_TRIGMUX_V2_IS_CYCLES_VALID(cycles)   ((CY_TRIGGER_DEACTIVATE == (cycles)) || \
                                                 (CY_TRIGGER_TWO_CYCLES == (cycles)) || \
                                                 (CY_TRIGGER_INFINITE   == (cycles)))
#define CY_TRIGMUX_IS_CYCLES_VALID(cycles)      ((CY_PERI_V1 && CY_TRIGMUX_V1_IS_CYCLES_VALID(cycles)) || \
                                                                CY_TRIGMUX_V2_IS_CYCLES_VALID(cycles))

#define CY_TRIGMUX_INTRIG_MASK                  (PERI_TR_CMD_GROUP_SEL_Msk | PERI_TR_GR_TR_OUT_CTL_TR_SEL_Msk)
#define CY_TRIGMUX_IS_INTRIG_VALID(inTrg)       (0UL == ((inTrg) & (uint32_t)~CY_TRIGMUX_INTRIG_MASK))

#define CY_TRIGMUX_OUTTRIG_MASK                 (PERI_TR_CMD_OUT_SEL_Msk | PERI_TR_CMD_GROUP_SEL_Msk | CY_PERI_TR_CTL_SEL_Msk)
#define CY_TRIGMUX_IS_OUTTRIG_VALID(outTrg)     ((0UL == ((outTrg) & (uint32_t)~CY_TRIGMUX_OUTTRIG_MASK)) && \
                                                 (0UL != ((outTrg) & PERI_TR_CMD_OUT_SEL_Msk)))

#define CY_TRIGMUX_ONETRIG_MASK                 (PERI_V2_TR_CMD_OUT_SEL_Msk | PERI_V2_TR_CMD_GROUP_SEL_Msk | CY_PERI_TR_CTL_SEL_Msk)

#if defined (CY_IP_MXSPERI) || (CY_IP_MXPERI_VERSION >= 3)
#define CY_TRIGMUX_ONETRIG_GR_START                0x10UL /* trigger 1-1 group [16-31] */
#define CY_TRIGMUX_IS_ONETRIG_VALID(oneTrg)     ((0UL == ((oneTrg) & (uint32_t)~CY_TRIGMUX_ONETRIG_MASK)) && \
                                                 (0UL != ((oneTrg) & PERI_V2_TR_CMD_OUT_SEL_Msk)) && \
                                                 (0UL != (_FLD2VAL(PERI_V2_TR_CMD_GROUP_SEL, oneTrg) & (uint32_t)CY_TRIGMUX_ONETRIG_GR_START)))
#else
#define CY_TRIGMUX_IS_ONETRIG_VALID(oneTrg)     ((0UL == ((oneTrg) & (uint32_t)~CY_TRIGMUX_ONETRIG_MASK)) && \
                                                 (0UL != ((oneTrg) & PERI_V2_TR_CMD_OUT_SEL_Msk)) && \
                                                 (0UL != ((oneTrg) & (PERI_V2_TR_CMD_GROUP_SEL_Msk & (uint32_t)~PERI_TR_CMD_GROUP_SEL_Msk))))
#endif

#define CY_TRIGMUX_TRIGLINE_MASK                (PERI_TR_CMD_OUT_SEL_Msk | CY_PERI_TR_CMD_GROUP_SEL_Msk | CY_PERI_TR_CTL_SEL_Msk)
#define CY_TRIGMUX_IS_TRIGLINE_VALID(trgLn)     (0U == ((trgLn) & (uint32_t)~CY_TRIGMUX_TRIGLINE_MASK))

#define CY_TRIGMUX_TR_CTL(outTrig)              (PERI_TR_GR_TR_CTL(_FLD2VAL(CY_PERI_TR_CMD_GROUP_SEL, outTrig), \
                                                                   _FLD2VAL(CY_PERI_TR_CTL_SEL,       outTrig)))


/*******************************************************************************
* Function Name: Cy_TrigMux_Connect
****************************************************************************//**
*
* Connects an input trigger source and output trigger.
*
* \param inTrig
* An input selection for the trigger mux.
* - Bit 30 should be cleared.
* - Bit 12 should be cleared.
* - Bits 11:8 represent the trigger group selection.
* - Bits 7:0 select the input trigger signal for the specified trigger multiplexer.
*
* \param outTrig
* The output of the trigger mux. This refers to the consumer of the trigger mux.
* - Bit 30 should be set.
* - Bit 12 should be cleared.
* - Bits 11:8 represent the trigger group selection.<br>
*  For PERI_ver1:
* - Bits 6:0 select the output trigger number in the trigger group.<br>
*  For PERI_ver2:
* - Bits 7:0 select the output trigger number in the trigger group.
*
* \param invert
* - true: The output trigger is inverted.
* - false: The output trigger is not inverted.
*
* \param trigType The trigger signal type.
* - TRIGGER_TYPE_EDGE: The trigger is synchronized to the consumer blocks clock
*   and a two-cycle pulse is generated on this clock.
* - TRIGGER_TYPE_LEVEL: The trigger is a simple level output.
*
* \return status:
* - CY_TRIGMUX_SUCCESS: The connection is made successfully.
* - CY_TRIGMUX_BAD_PARAM: Some parameter is invalid.
*
* \funcusage
* \snippet trigmux/snippet/main.c snippet_Cy_TrigMux_Connect
*
*******************************************************************************/
cy_en_trigmux_status_t Cy_TrigMux_Connect(uint32_t inTrig, uint32_t outTrig, bool invert, en_trig_type_t trigType)
{
    cy_en_trigmux_status_t retVal = CY_TRIGMUX_BAD_PARAM;
    CY_ASSERT_L3(CY_TRIGMUX_IS_TRIGTYPE_VALID(trigType));
    CY_ASSERT_L2(CY_TRIGMUX_IS_INTRIG_VALID(inTrig));
    CY_ASSERT_L2(CY_TRIGMUX_IS_OUTTRIG_VALID(outTrig));

    /* inTrig and outTrig should be in the same group */
    if ((inTrig & PERI_TR_CMD_GROUP_SEL_Msk) == (outTrig & PERI_TR_CMD_GROUP_SEL_Msk))
    {
        uint32_t interruptState = Cy_SysLib_EnterCriticalSection();

        CY_TRIGMUX_TR_CTL(outTrig) = (CY_TRIGMUX_TR_CTL(outTrig) &
                                      (uint32_t)~(PERI_TR_GR_TR_OUT_CTL_TR_SEL_Msk |
                                                  PERI_TR_GR_TR_OUT_CTL_TR_INV_Msk |
                                                  PERI_TR_GR_TR_OUT_CTL_TR_EDGE_Msk)) |
                                        (_VAL2FLD(PERI_TR_GR_TR_OUT_CTL_TR_SEL, inTrig) |
                                        _BOOL2FLD(PERI_TR_GR_TR_OUT_CTL_TR_INV, invert) |
                                         _VAL2FLD(PERI_TR_GR_TR_OUT_CTL_TR_EDGE, trigType));

        Cy_SysLib_ExitCriticalSection(interruptState);

        retVal = CY_TRIGMUX_SUCCESS;
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_TrigMux_Select
****************************************************************************//**
*
* Enables and configures the specified 1-to-1 trigger line. For PERI_ver2 only.
*
* \param outTrig
* The 1to1 trigger line.
* - Bit 30 should be set.
* - Bit 12 should be set.
* - Bits 11:8 represent the 1-to-1 trigger group selection.
* - Bits 7:0 select the trigger line number in the trigger group.
*
* \param invert
* - true: The trigger signal is inverted.
* - false: The trigger signal is not inverted.
*
* \param trigType The trigger signal type.
* - TRIGGER_TYPE_EDGE: The trigger is synchronized to the consumer blocks clock
*   and a two-cycle pulse is generated on this clock.
* - TRIGGER_TYPE_LEVEL: The trigger is a simple level output.
*
* \return status:
* - CY_TRIGMUX_SUCCESS: The selection is made successfully.
* - CY_TRIGMUX_BAD_PARAM: Some parameter is invalid.
*
* \funcusage
* \snippet trigmux/snippet/main.c snippet_Cy_TrigMux_Select
*
*******************************************************************************/
cy_en_trigmux_status_t Cy_TrigMux_Select(uint32_t outTrig, bool invert, en_trig_type_t trigType)
{
    cy_en_trigmux_status_t retVal = CY_TRIGMUX_BAD_PARAM;

    CY_ASSERT_L3(CY_TRIGMUX_IS_TRIGTYPE_VALID(trigType));
    CY_ASSERT_L2(CY_TRIGMUX_IS_ONETRIG_VALID(outTrig));

    if (CY_PERI_V1 == 0U) /* !mxperi_v1 */
    {
        uint32_t interruptState;

        interruptState = Cy_SysLib_EnterCriticalSection();

        CY_TRIGMUX_TR_CTL(outTrig) = (CY_TRIGMUX_TR_CTL(outTrig) &
                          (uint32_t)~(PERI_TR_1TO1_GR_V2_TR_CTL_TR_INV_Msk |
                                      PERI_TR_1TO1_GR_V2_TR_CTL_TR_EDGE_Msk)) |
                                     (PERI_TR_1TO1_GR_V2_TR_CTL_TR_SEL_Msk      |
                            _BOOL2FLD(PERI_TR_1TO1_GR_V2_TR_CTL_TR_INV, invert) |
                             _VAL2FLD(PERI_TR_1TO1_GR_V2_TR_CTL_TR_EDGE, trigType));

        Cy_SysLib_ExitCriticalSection(interruptState);

        retVal = CY_TRIGMUX_SUCCESS;
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_TrigMux_Deselect
****************************************************************************//**
*
* Disables the specified 1-to-1 trigger line. For PERI_ver2 only.
*
* \param outTrig
* The 1to1 trigger line.
* - Bit 30 should be set.
* - Bit 12 should be set.
* - Bits 11:8 represent the 1-to-1 trigger group selection.
* - Bits 7:0 select the trigger line number in the trigger group.
*
* \return status:
* - CY_TRIGMUX_SUCCESS: The deselection is made successfully.
* - CY_TRIGMUX_BAD_PARAM: Some parameter is invalid.
*
* \funcusage
* \snippet trigmux/snippet/main.c snippet_Cy_TrigMux_Deselect
*
*******************************************************************************/
cy_en_trigmux_status_t Cy_TrigMux_Deselect(uint32_t outTrig)
{
    cy_en_trigmux_status_t retVal = CY_TRIGMUX_BAD_PARAM;

    CY_ASSERT_L2(CY_TRIGMUX_IS_ONETRIG_VALID(outTrig));

    if (CY_PERI_V1 == 0U) /* !mxperi_v1 */
    {
        uint32_t interruptState;

        interruptState = Cy_SysLib_EnterCriticalSection();

        CY_TRIGMUX_TR_CTL(outTrig) &= (uint32_t)~(PERI_TR_1TO1_GR_V2_TR_CTL_TR_SEL_Msk |
                                                  PERI_TR_1TO1_GR_V2_TR_CTL_TR_INV_Msk |
                                                  PERI_TR_1TO1_GR_V2_TR_CTL_TR_EDGE_Msk);

        Cy_SysLib_ExitCriticalSection(interruptState);

        retVal = CY_TRIGMUX_SUCCESS;
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_TrigMux_SetDebugFreeze
****************************************************************************//**
*
* Enables/disables the Debug Freeze feature for the specified trigger
* multiplexer or 1-to-1 trigger line. For PERI_ver2 only.
*
* \param outTrig
* The output of the trigger mux or dedicated 1-to-1 trigger line.
* - Bit 30 should be set.
* - For PERI_ver1 Bits 11:8 represent the trigger group selection.
* - For PERI_ver2 Bits 12:8 represent the trigger group selection.
* - Bits 7:0 select the output trigger number in the trigger group.
*
* \param enable
* - true: The Debug Freeze feature is enabled.
* - false: The Debug Freeze feature is disabled.
*
* \return status:
* - CY_TRIGMUX_SUCCESS: The operation is made successfully.
* - CY_TRIGMUX_BAD_PARAM: The outTrig parameter is invalid.
*
* \funcusage
* \snippet trigmux/snippet/main.c snippet_Cy_TrigMux_SetDebugFreeze
*
*******************************************************************************/
cy_en_trigmux_status_t Cy_TrigMux_SetDebugFreeze(uint32_t outTrig, bool enable)
{
    cy_en_trigmux_status_t retVal = CY_TRIGMUX_BAD_PARAM;

    if (CY_PERI_V1 == 0U) /* !mxperi_v1 */
    {
        uint32_t interruptState;

        interruptState = Cy_SysLib_EnterCriticalSection();

        if (enable)
        {
            CY_TRIGMUX_TR_CTL(outTrig) |= PERI_TR_GR_V2_TR_CTL_DBG_FREEZE_EN_Msk;
        }
        else
        {
            CY_TRIGMUX_TR_CTL(outTrig) &= (uint32_t)~PERI_TR_GR_V2_TR_CTL_DBG_FREEZE_EN_Msk;
        }

        Cy_SysLib_ExitCriticalSection(interruptState);

        retVal = CY_TRIGMUX_SUCCESS;
    }

    return retVal;
}


/*******************************************************************************
* Function Name: Cy_TrigMux_SwTrigger
****************************************************************************//**
*
* This function generates a software trigger on an input trigger line.
* All output triggers connected to this input trigger will be triggered.
* The function also verifies that there is no activated trigger before
* generating another activation.
*
* \param trigLine
* The input of the trigger mux.
* - Bit 30 represents if the signal is an input/output. When this bit is set,
*   the trigger activation is for an output trigger from the trigger multiplexer.
*   When this bit is reset, the trigger activation is for an input trigger to
*   the trigger multiplexer.<br>
* - For PERI_ver1 Bits 11:8 represent the trigger group selection.<br>
* - For PERI_ver2 Bits 12:8 represent the trigger group selection.<br>
* In case of output trigger line (bit 30 is set):<br>
* For PERI_ver1:
* - Bits 6:0 select the output trigger number in the trigger group.<br>
* For PERI_ver2:
* - Bits 7:0 select the output trigger number in the trigger group.<br>
* In case of input trigger line (bit 30 is unset):
* - Bits 7:0 select the input trigger signal for the trigger multiplexer.
*
* \param cycles
*  The number of "Clk_Peri" cycles during which the trigger remains activated.<br>
*  For PERI_ver1: The valid range of cycles is 1 ... 254.<br>
*  For PERI_ver2: The only valid value of cycles is 2 (\ref CY_TRIGGER_TWO_CYCLES).<br>
*  Also there are special values (supported with both PERI_ver1 and PERI_ver2):
*   - CY_TRIGGER_INFINITE - trigger remains activated until the user deactivates it by
*   calling this function with CY_TRIGGER_DEACTIVATE parameter.
*   - CY_TRIGGER_DEACTIVATE - this is used to deactivate the trigger activated by
*   calling this function with CY_TRIGGER_INFINITE parameter.
*
* \return status:
* - CY_TRIGMUX_SUCCESS: The trigger is successfully activated/deactivated.
* - CY_TRIGMUX_INVALID_STATE: The trigger is already activated/not active.
* - CY_TRIGMUX_BAD_PARAM: Some parameter is invalid.
*
* \funcusage
* \snippet trigmux/snippet/main.c snippet_Cy_TrigMux_SwTrigger
*
*******************************************************************************/
cy_en_trigmux_status_t Cy_TrigMux_SwTrigger(uint32_t trigLine, uint32_t cycles)
{
    cy_en_trigmux_status_t retVal = CY_TRIGMUX_INVALID_STATE;

    CY_ASSERT_L2(CY_TRIGMUX_IS_TRIGLINE_VALID(trigLine));
    CY_ASSERT_L2(CY_TRIGMUX_IS_CYCLES_VALID(cycles));

    if (CY_TRIGGER_DEACTIVATE != cycles)
    {
        /* Activate the trigger if it is not in the active state. */
        if (PERI_TR_CMD_ACTIVATE_Msk != (PERI_TR_CMD & PERI_TR_CMD_ACTIVATE_Msk))
        {

            uint32_t trCmd = (trigLine & (PERI_TR_CMD_TR_SEL_Msk |
                                          PERI_TR_CMD_OUT_SEL_Msk |
                                       CY_PERI_TR_CMD_GROUP_SEL_Msk)) |
                                          PERI_TR_CMD_ACTIVATE_Msk;

            retVal = CY_TRIGMUX_SUCCESS;

            if (CY_PERI_V1 != 0U) /* mxperi_v1 */
            {
                PERI_TR_CMD = trCmd | _VAL2FLD(PERI_TR_CMD_COUNT, cycles);
            }
            else if (CY_TRIGGER_TWO_CYCLES == cycles) /* mxperi_v2 or later, 2 cycles pulse */
            {
                PERI_TR_CMD = trCmd | PERI_V2_TR_CMD_TR_EDGE_Msk;
            }
            else if (CY_TRIGGER_INFINITE == cycles) /* mxperi_v2 or later, infinite activating */
            {
                PERI_TR_CMD = trCmd;
            }
            else /* mxperi_v2 or later, invalid cycles value */
            {
                retVal = CY_TRIGMUX_BAD_PARAM;
            }
        }
    }
    else
    {
        /* Forcibly deactivate the trigger if it is in the active state. */
        if (PERI_TR_CMD_ACTIVATE_Msk == (PERI_TR_CMD & PERI_TR_CMD_ACTIVATE_Msk))
        {
            PERI_TR_CMD = 0UL;

            retVal = CY_TRIGMUX_SUCCESS;
        }
    }

    return retVal;
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 14.3');

#endif /* CY_IP_MXSPERI, CY_IP_MXPERI */

/* [] END OF FILE */
