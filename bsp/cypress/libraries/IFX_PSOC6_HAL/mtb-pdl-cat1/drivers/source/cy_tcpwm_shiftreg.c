/***************************************************************************//**
* \file cy_tcpwm_shiftreg.c
* \version 1.40
*
* \brief
*  The source file of the tcpwm driver.
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

#include "cy_tcpwm_shiftreg.h"

#ifdef CY_IP_MXTCPWM

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_Init
****************************************************************************//**
*
* Initializes the counter in the TCPWM block for the Shift Register operation.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param config
* The pointer to a configuration structure. See \ref cy_stc_tcpwm_shiftreg_config_t.
*
* \return error / status code. See \ref cy_en_tcpwm_status_t.
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_Init
*
*******************************************************************************/
cy_en_tcpwm_status_t Cy_TCPWM_ShiftReg_Init(TCPWM_Type const *base, uint32_t cntNum,  cy_stc_tcpwm_shiftreg_config_t const *config)
{
    cy_en_tcpwm_status_t status = CY_TCPWM_SUCCESS;

#if (CY_IP_MXTCPWM_VERSION >= 2U)
    if ((NULL != base) && (NULL != config))
    {
        uint32_t grp = TCPWM_GRP_CNT_GET_GRP(cntNum);
        bool enabled_bit = _FLD2BOOL(TCPWM_GRP_CNT_V2_CTRL_ENABLED, TCPWM_GRP_CNT_CTRL(base, grp, cntNum));

        TCPWM_GRP_CNT_CTRL(base, grp, cntNum) =
                (_VAL2FLD(TCPWM_GRP_CNT_V2_CTRL_MODE, CY_TCPWM_MODE_SHIFTREG) |
                (config->enableCompare0Swap ? TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC0_Msk : 0UL) |
                _VAL2FLD(TCPWM_GRP_CNT_V2_CTRL_QUAD_ENCODING_MODE,
                    (config->invertShiftRegOut | (config->invertShiftRegOutN << 1U))) |
                _VAL2FLD(TCPWM_GRP_CNT_V2_CTRL_PWM_DISABLE_MODE, config->shiftRegOnDisable) |
                (enabled_bit ? TCPWM_GRP_CNT_V2_CTRL_ENABLED_Msk : 0UL));

        TCPWM_GRP_CNT_DT(base, grp, cntNum) = _VAL2FLD(TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_L, (uint8_t)config->clockPrescaler);

        TCPWM_GRP_CNT_CC0(base, grp, cntNum) = config->compare0;
        TCPWM_GRP_CNT_CC0_BUFF(base, grp, cntNum) = config->compareBuf0;

        TCPWM_GRP_CNT_PERIOD_BUFF(base, grp, cntNum) = config->tapsEnabled;

        TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) =
                (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL, config->serialInput) |
                 _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL, config->reloadInput) |
                 _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL, config->killInput) |
                 _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL, config->shiftInput));

        TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum) = _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL, config->startInput);

        TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) =
                (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE, config->serialInputMode) |
                 _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE, config->reloadInputMode) |
                 _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE, config->startInputMode) |
                 _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE, config->killInputMode) |
                 _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE, config->shiftInputMode));

        TCPWM_GRP_CNT_TR_OUT_SEL(base, grp, cntNum) =
                (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0, config->trigger0Event) |
                 _VAL2FLD(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1, config->trigger1Event));

        TCPWM_GRP_CNT_INTR_MASK(base, grp, cntNum) = config->interruptSources;

        if(TCPWM_GRP_CC1(base, grp))
        {
            TCPWM_GRP_CNT_CC1(base, grp, cntNum) = config->compare1;
            TCPWM_GRP_CNT_CC1_BUFF(base, grp, cntNum) = config->compareBuf1;

            TCPWM_GRP_CNT_CTRL(base, grp, cntNum) |=
                (config->enableCompare1Swap ? TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC1_Msk : 0UL);
        }
    }
    else
    {
        status = CY_TCPWM_BAD_PARAM;
    }
#else
    /* Suppress a compiler warning about unused variables */
    (void) base;
    (void) cntNum;
    (void) config;

    status = CY_TCPWM_UNSUPPORTED_FEATURE;
#endif
    return(status);
}

/*******************************************************************************
* Function Name: Cy_TCPWM_ShiftReg_DeInit
****************************************************************************//**
*
* De-initializes the counter in the TCPWM block, returns register values to
* default.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param config
* The pointer to a configuration structure. See \ref cy_stc_tcpwm_shiftreg_config_t.
*
* \snippet tcpwm/shiftreg/snippet/main.c snippet_Cy_TCPWM_ShiftReg_DeInit
*
*******************************************************************************/
void Cy_TCPWM_ShiftReg_DeInit(TCPWM_Type const *base, uint32_t cntNum, cy_stc_tcpwm_shiftreg_config_t const *config)
{

    (void) config;

#if (CY_IP_MXTCPWM_VERSION >= 2U)

    uint32_t grp = TCPWM_GRP_CNT_GET_GRP(cntNum);

    TCPWM_GRP_CNT_CTRL(base, grp, cntNum) = CY_TCPWM_GRP_CNT_CTRL_DEFAULT;
    TCPWM_GRP_CNT_DT(base, grp, cntNum) = CY_TCPWM_GRP_CNT_DT_DEFAULT;
    TCPWM_GRP_CNT_COUNTER(base, grp, cntNum) = CY_TCPWM_GRP_CNT_COUNTER_DEFAULT;
    TCPWM_GRP_CNT_TR_PWM_CTRL(base, grp, cntNum) = CY_TCPWM_GRP_CNT_TR_PWM_CTRL_DEFAULT;
    TCPWM_GRP_CNT_CC0(base, grp, cntNum) = CY_TCPWM_GRP_CNT_CC0_DEFAULT;
    TCPWM_GRP_CNT_CC0_BUFF(base, grp, cntNum) = CY_TCPWM_GRP_CNT_CC0_BUFF_DEFAULT;
    TCPWM_GRP_CNT_CC1(base, grp, cntNum) = CY_TCPWM_GRP_CNT_CC0_DEFAULT;
    TCPWM_GRP_CNT_CC1_BUFF(base, grp, cntNum) = CY_TCPWM_GRP_CNT_CC0_BUFF_DEFAULT;
    TCPWM_GRP_CNT_PERIOD(base, grp, cntNum) = CY_TCPWM_GRP_CNT_PERIOD_DEFAULT;
    TCPWM_GRP_CNT_PERIOD_BUFF(base, grp, cntNum) = CY_TCPWM_GRP_CNT_PERIOD_BUFF_DEFAULT;
    TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) = CY_TCPWM_GRP_CNT_TR_IN_SEL0_DEFAULT;
    TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum) = CY_TCPWM_GRP_CNT_TR_IN_SEL1_DEFAULT;
    TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) = CY_TCPWM_GRP_CNT_TR_IN_EDGE_SEL_DEFAULT;
    TCPWM_GRP_CNT_INTR_MASK(base, grp, cntNum) = CY_TCPWM_GRP_CNT_INTR_MASK_DEFAULT;

#else

    /* Suppress a compiler warning about unused variables */
    (void) base;
    (void) cntNum;

#endif /* CY_IP_MXTCPWM_VERSION >= 2U */
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXTCPWM */

/* [] END OF FILE */
