/***************************************************************************//**
* \file cy_tcpwm_quaddec.c
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

#include "cy_tcpwm_quaddec.h"

#ifdef CY_IP_MXTCPWM

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_Init
****************************************************************************//**
*
* Initializes the counter in the TCPWM block for the QuadDec operation.
*
* \param base
* The pointer to a TCPWM instance.
*
* \param cntNum
* The Counter instance number in the selected TCPWM.
*
* \param config
* The pointer to a configuration structure. See \ref cy_stc_tcpwm_quaddec_config_t.
*
* \return error / status code. See \ref cy_en_tcpwm_status_t.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_V1_QuadDec_Init
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_V2_QuadDec_Init
*
*******************************************************************************/
cy_en_tcpwm_status_t Cy_TCPWM_QuadDec_Init(TCPWM_Type *base, uint32_t cntNum,
                                           cy_stc_tcpwm_quaddec_config_t const *config)
{
    cy_en_tcpwm_status_t status = CY_TCPWM_BAD_PARAM;

    if ((NULL != base) && (NULL != config))
    {
#if (CY_IP_MXTCPWM_VERSION == 1U)

            if(config->resolution <= CY_TCPWM_QUADDEC_X4)
            {
                TCPWM_CNT_CTRL(base, cntNum) = ( _VAL2FLD(TCPWM_CNT_CTRL_QUADRATURE_MODE, config->resolution) |
                            _VAL2FLD(TCPWM_CNT_CTRL_MODE, CY_TCPWM_QUADDEC_CTRL_QUADDEC_MODE));

                if (CY_TCPWM_INPUT_CREATOR != config->phiAInput)
                {
                    TCPWM_CNT_TR_CTRL0(base, cntNum) = (_VAL2FLD(TCPWM_CNT_TR_CTRL0_COUNT_SEL, config->phiAInput) |
                                      _VAL2FLD(TCPWM_CNT_TR_CTRL0_START_SEL, config->phiBInput) |
                                      _VAL2FLD(TCPWM_CNT_TR_CTRL0_RELOAD_SEL, config->indexInput) |
                                      _VAL2FLD(TCPWM_CNT_TR_CTRL0_STOP_SEL, config->stopInput));
                }

                TCPWM_CNT_TR_CTRL1(base, cntNum) = (_VAL2FLD(TCPWM_CNT_TR_CTRL1_CAPTURE_EDGE, CY_TCPWM_INPUT_LEVEL) |
                                  _VAL2FLD(TCPWM_CNT_TR_CTRL1_COUNT_EDGE, CY_TCPWM_INPUT_LEVEL) |
                                  _VAL2FLD(TCPWM_CNT_TR_CTRL1_START_EDGE, CY_TCPWM_INPUT_LEVEL) |
                                  _VAL2FLD(TCPWM_CNT_TR_CTRL1_RELOAD_EDGE, config->indexInputMode) |
                                  _VAL2FLD(TCPWM_CNT_TR_CTRL1_STOP_EDGE, config->stopInputMode));

                TCPWM_CNT_INTR_MASK(base, cntNum) = config->interruptSources;

                status = CY_TCPWM_SUCCESS;
            }
            else
            {
                status = CY_TCPWM_UNSUPPORTED_FEATURE;
            }
#else
            uint32_t grp = TCPWM_GRP_CNT_GET_GRP(cntNum);
            bool enabled_bit = _FLD2BOOL(TCPWM_GRP_CNT_V2_CTRL_ENABLED, TCPWM_GRP_CNT_CTRL(base, grp, cntNum));

            TCPWM_GRP_CNT_CTRL(base, grp, cntNum) =
                        ( _VAL2FLD(TCPWM_GRP_CNT_V2_CTRL_QUAD_ENCODING_MODE, config->resolution) |
                    _VAL2FLD(TCPWM_GRP_CNT_V2_CTRL_MODE, CY_TCPWM_QUADDEC_CTRL_QUADDEC_MODE) |
                    _VAL2FLD(TCPWM_GRP_CNT_V2_CTRL_UP_DOWN_MODE, config->quadMode) |
                    (config->enableCompare0Swap ? TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC0_Msk : 0UL) |
                    _VAL2FLD(TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_PERIOD, (config->captureOnIndex ? CY_TCPWM_QUADDEC_CAPTURE_ON_INDEX : CY_TCPWM_QUADDEC_CAPTURE_ON_WRAP_AROUND)) |
                    (enabled_bit ? TCPWM_GRP_CNT_V2_CTRL_ENABLED_Msk : 0UL));

            TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) =
                                  (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL, config->capture0OrIndex1Input) |
                                  _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL, config->phiAInput) |
                                  _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL, config->indexInput) |
                                  _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL, config->stopInput));

            TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum) =
                                  _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL, config->phiBInput);

            TCPWM_GRP_CNT_CC0(base, grp, cntNum) = config->compare0;
            TCPWM_GRP_CNT_CC0_BUFF(base, grp, cntNum) = config->compareBuf0;
            TCPWM_GRP_CNT_PERIOD(base, grp, cntNum) = config->period0;

            TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) =
                              (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE, config->capture0OrIndex1InputMode) |
                              _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE, config->phiAInputMode) |
                              _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE, config->phiBInputMode) |
                              _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE, config->indexInputMode) |
                              _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE, config->stopInputMode));

            if(TCPWM_GRP_CC1(base, grp))
            {
                TCPWM_GRP_CNT_CC1(base, grp, cntNum) = config->compare1;
                TCPWM_GRP_CNT_CC1_BUFF(base, grp, cntNum) = config->compareBuf1;

                TCPWM_GRP_CNT_CTRL(base, grp, cntNum) |=
                    (config->enableCompare1Swap ? TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC1_Msk : 0UL);

                TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum) |=
                    _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_SEL1_CAPTURE1_SEL, config->capture1Input);

                TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) |=
                    _VAL2FLD(TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE1_EDGE, config->capture1InputMode);
            }

            TCPWM_GRP_CNT_TR_OUT_SEL(base, grp, cntNum) =
                (_VAL2FLD(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0, config->trigger0Event) |
                 _VAL2FLD(TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1, config->trigger1Event));

            TCPWM_GRP_CNT_INTR_MASK(base, grp, cntNum) = config->interruptSources;

            status = CY_TCPWM_SUCCESS;
#endif
    }

    return(status);
}


/*******************************************************************************
* Function Name: Cy_TCPWM_QuadDec_DeInit
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
* The pointer to a configuration structure. See \ref cy_stc_tcpwm_quaddec_config_t.
*
* \funcusage
* \snippet tcpwm/quaddec/snippet/main.c snippet_Cy_TCPWM_QuadDec_DeInit
*
*******************************************************************************/
void Cy_TCPWM_QuadDec_DeInit(TCPWM_Type *base, uint32_t cntNum, cy_stc_tcpwm_quaddec_config_t const *config)
{
#if (CY_IP_MXTCPWM_VERSION == 1U)

        TCPWM_CNT_CTRL(base, cntNum) = CY_TCPWM_CNT_CTRL_DEFAULT;
        TCPWM_CNT_COUNTER(base, cntNum) = CY_TCPWM_CNT_COUNTER_DEFAULT;
        TCPWM_CNT_CC(base, cntNum) = CY_TCPWM_CNT_CC_DEFAULT;
        TCPWM_CNT_CC_BUFF(base, cntNum) = CY_TCPWM_CNT_CC_BUFF_DEFAULT;
        TCPWM_CNT_PERIOD(base, cntNum) = CY_TCPWM_CNT_PERIOD_DEFAULT;
        TCPWM_CNT_PERIOD_BUFF(base, cntNum) = CY_TCPWM_CNT_PERIOD_BUFF_DEFAULT;
        TCPWM_CNT_TR_CTRL1(base, cntNum) = CY_TCPWM_CNT_TR_CTRL1_DEFAULT;
        TCPWM_CNT_TR_CTRL2(base, cntNum) = CY_TCPWM_CNT_TR_CTRL2_DEFAULT;
        TCPWM_CNT_INTR(base, cntNum) = CY_TCPWM_CNT_INTR_DEFAULT;
        TCPWM_CNT_INTR_SET(base, cntNum) = CY_TCPWM_CNT_INTR_SET_DEFAULT;
        TCPWM_CNT_INTR_MASK(base, cntNum) = CY_TCPWM_CNT_INTR_MASK_DEFAULT;

        if (CY_TCPWM_INPUT_CREATOR != config->phiAInput)
        {
            TCPWM_CNT_TR_CTRL0(base, cntNum) = CY_TCPWM_CNT_TR_CTRL0_DEFAULT;
        }
#else
        (void)config;
        uint32_t grp = TCPWM_GRP_CNT_GET_GRP(cntNum);
        bool enabled_bit = _FLD2BOOL(TCPWM_GRP_CNT_V2_CTRL_ENABLED, TCPWM_GRP_CNT_CTRL(base, grp, cntNum));

        TCPWM_GRP_CNT_CTRL(base, grp, cntNum) = (CY_TCPWM_GRP_CNT_CTRL_DEFAULT | (enabled_bit ? TCPWM_GRP_CNT_V2_CTRL_ENABLED_Msk : 0UL));
        TCPWM_GRP_CNT_DT(base, grp, cntNum) = CY_TCPWM_GRP_CNT_DT_DEFAULT;
        TCPWM_GRP_CNT_COUNTER(base, grp, cntNum) = CY_TCPWM_GRP_CNT_COUNTER_DEFAULT;
        TCPWM_GRP_CNT_TR_PWM_CTRL(base, grp, cntNum) = CY_TCPWM_GRP_CNT_TR_PWM_CTRL_DEFAULT;
        TCPWM_GRP_CNT_CC0(base, grp, cntNum) = CY_TCPWM_GRP_CNT_CC0_DEFAULT;
        TCPWM_GRP_CNT_CC0_BUFF(base, grp, cntNum) = CY_TCPWM_GRP_CNT_CC0_BUFF_DEFAULT;
        TCPWM_GRP_CNT_PERIOD(base, grp, cntNum) = CY_TCPWM_GRP_CNT_PERIOD_DEFAULT;
        TCPWM_GRP_CNT_PERIOD_BUFF(base, grp, cntNum) = CY_TCPWM_GRP_CNT_PERIOD_BUFF_DEFAULT;
        TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum) = CY_TCPWM_GRP_CNT_TR_IN_SEL0_DEFAULT;
        TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum) = CY_TCPWM_GRP_CNT_TR_IN_SEL1_DEFAULT;
        TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) = CY_TCPWM_GRP_CNT_TR_IN_EDGE_SEL_DEFAULT;
        TCPWM_GRP_CNT_INTR_MASK(base, grp, cntNum) = CY_TCPWM_GRP_CNT_INTR_MASK_DEFAULT;
#endif
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXTCPWM */

/* [] END OF FILE */
