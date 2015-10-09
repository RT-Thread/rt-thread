/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_quadtmr_hal.h"

#if FSL_FEATURE_SOC_TMR_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_HAL_Init
 * Description   : Initializes the Quad Timer.
 *
 *END**************************************************************************/
void QUADTMR_HAL_Init(TMR_Type *base)
{
    TMR_WR_CNTR(base, 0);
    TMR_WR_LOAD(base, 0);
    TMR_WR_CTRL(base, 0);
    TMR_WR_SCTRL(base, 0);
    TMR_WR_CSCTRL(base, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_HAL_SetupCounter
 * Description   : Sets the Quad timer's counter properties.
 * The primary source and in some cases secondary clock control how the to increment the counter.
 * The parameters provided by the user will be used to setup counter properties like match value,
 * rollover behaviour, direction.
 * The function will not start the counter, the user will have to make a separate call to
 * QUADTMR_HAL_SetCountMode to set count mode and start counting.
 *
 *END**************************************************************************/
void QUADTMR_HAL_SetupCounter(TMR_Type *base, quadtmr_counter_params_t *params, bool src_polarity)
{
    TMR_WR_CTRL(base, (uint16_t)(((uint32_t)(params->primarySrc) << TMR_CTRL_PCS_SHIFT) |
                                     ((uint32_t)(params->secondarySrc) << TMR_CTRL_SCS_SHIFT) |
                                     ((uint32_t)(params->countOnce) << TMR_CTRL_ONCE_SHIFT) |
                                     ((uint32_t)(params->countLength) << TMR_CTRL_LENGTH_SHIFT) |
                                     ((uint32_t)(params->countDir) << TMR_CTRL_DIR_SHIFT)));
    TMR_WR_SCTRL(base, (uint16_t)(src_polarity) << TMR_SCTRL_IPS_SHIFT);

    TMR_WR_CNTR(base, params->counterVal);
    TMR_WR_LOAD(base, params->counterLoadVal);
    TMR_WR_COMP1(base, params->countUpCompareVal);
    TMR_WR_COMP2(base, params->countDownCompareVal);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_HAL_ForceOutVal
 * Description   : Enables the user to write a value out on the OFLAG pin.
 *
 *END**************************************************************************/
void QUADTMR_HAL_ForceOutVal(TMR_Type *base, bool val, bool pol)
{
    /* Stop the counter */
    TMR_BWR_CTRL_CM(base, kQuadTmrCntNoOper);

    TMR_WR_SCTRL(base, (uint16_t)(((uint32_t)(val) << TMR_SCTRL_VAL_SHIFT) |
                                      ((uint32_t)(pol) << TMR_SCTRL_OPS_SHIFT) |
                                      (0x1 << TMR_SCTRL_FORCE_SHIFT) |
                                      (0x1 << TMR_SCTRL_OEN_SHIFT)));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_HAL_OutPulses
 * Description   : Enables the user to output a certain number of pulses.
 * The number of pulses to be outputted is provided as an argument. The output pulse stream has
 * the same frequency as the source clock provided.
 *
 *END**************************************************************************/
void QUADTMR_HAL_OutPulses(TMR_Type *base, uint16_t numOfPulses, quadtmr_pri_count_source_t src)
{
    /* Pulse mode cannot work with IP_Bus div 1 clock */
    assert(src != kQuadTmrClkDiv1);

    /* Set the source, set the ONCE bit and update output mode to gated clock output */
    TMR_WR_CTRL(base, (uint16_t)(((uint32_t)(src) << TMR_CTRL_PCS_SHIFT) |
                                     (0x1 << TMR_CTRL_ONCE_SHIFT) |
                                     (kQuadTmrEnableGateClk << TMR_CTRL_OUTMODE_SHIFT)));
    TMR_WR_SCTRL(base, 0x1);
    TMR_WR_CNTR(base, 0);
    TMR_WR_LOAD(base, 0);
    TMR_WR_COMP1(base, numOfPulses);

    /* Start the counter */
    TMR_BWR_CTRL_CM(base, kQuadTmrCntPriSrcRiseEdge);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_HAL_OutPwmSignal
 * Description   : Outputs a PWM signal on the OFLAG pin
 * The high and low pulse width values should be a count in terms of number of source
 * clock cycles. The user has to calculate these values based on the source clock frequency,
 * desired PWM frequncy and duty cycle.
 *
 *END**************************************************************************/
void QUADTMR_HAL_OutPwmSignal(TMR_Type *base, quadtmr_pri_count_source_t src,
                                          uint16_t highPulseCount, uint16_t lowPulseCount)
{
    /* Set the source, set the ONCE bit and update output mode to alternating compare mode */
    TMR_WR_CTRL(base, (uint16_t)(((uint32_t)(src) << TMR_CTRL_PCS_SHIFT) |
                                     (0x1 << TMR_CTRL_LENGTH_SHIFT) |
                                     (kQuadTmrTogOnAltCompReg << TMR_CTRL_OUTMODE_SHIFT)));

    /* Force out a low value on the OFLLAG pin */
    TMR_WR_SCTRL(base, (uint16_t)((0x1 << TMR_SCTRL_FORCE_SHIFT) |
                                      (0x1 << TMR_SCTRL_OEN_SHIFT)));
    TMR_WR_CNTR(base, 0);
    TMR_WR_LOAD(base, 0);

    TMR_WR_COMP1(base, lowPulseCount);
    TMR_WR_COMP2(base, highPulseCount);

    /* Start the counter */
    TMR_BWR_CTRL_CM(base, kQuadTmrCntPriSrcRiseEdge);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_HAL_SetupInputCapture
 * Description   : Allows the user to count the source clock cycles until a capture event arrives.
 * The count will be stored in the capture register.
 *
 *END**************************************************************************/
void QUADTMR_HAL_SetupInputCapture(TMR_Type *base, quadtmr_pri_count_source_t countSrc,
                                              quadtmr_input_source_t captureSrc, bool reloadCntrOnCap,
                                              quadtmr_input_capture_edge_mode_t mode, bool inputPol)
{
    TMR_WR_CTRL(base, (uint16_t)(((uint32_t)(countSrc) << TMR_CTRL_PCS_SHIFT) |
                                     (captureSrc << TMR_CTRL_SCS_SHIFT)));
    TMR_WR_SCTRL(base, (uint16_t)(((uint32_t)(inputPol) << TMR_SCTRL_IPS_SHIFT) |
                                      (mode << TMR_SCTRL_CAPTURE_MODE_SHIFT)));
    TMR_BWR_CSCTRL_ROC(base, reloadCntrOnCap);
    TMR_WR_CNTR(base, 0);
    TMR_WR_LOAD(base, 0);
    TMR_WR_COMP1(base, 0xFFFF);

    /* Start the counter */
    TMR_BWR_CTRL_CM(base, kQuadTmrCntPriSrcRiseEdge);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : QUADTMR_HAL_SetupComparePreload
 * Description   : Sets up the Quad timers compare preload feature.
 *
 *END**************************************************************************/
void QUADTMR_HAL_SetupComparePreload(TMR_Type *base, uint8_t compareRegNum, uint16_t preloadVal,
                                                  quadtmr_preload_control_t preloadProps)
{
    switch(compareRegNum)
    {
        case 1:
            TMR_BWR_CSCTRL_CL1(base, preloadProps);
            TMR_WR_CMPLD1(base, preloadVal);
            break;
        case 2:
            TMR_BWR_CSCTRL_CL2(base, preloadProps);
            TMR_WR_CMPLD2(base, preloadVal);
            break;
        default:
            assert(0);
            break;
    }
}

#endif /* FSL_FEATURE_SOC_TMR_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

