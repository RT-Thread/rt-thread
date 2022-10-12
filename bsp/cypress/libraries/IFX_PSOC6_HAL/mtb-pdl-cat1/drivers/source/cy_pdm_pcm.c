/***************************************************************************//**
* \file cy_pdm_pcm.c
* \version 2.30.1
*
* The source code file for the PDM_PCM driver.
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

#if defined (AUDIOSS_PDM_PRESENT)

#include "cy_pdm_pcm.h"

/**
* \addtogroup group_pdm_pcm_functions
* \{
*/

/******************************************************************************
* Function Name: Cy_PDM_PCM_Init
***************************************************************************//**
*
* Initialize the PDM-PCM module
*
* \pre If the PDM-PCM module is initialized previously, the
* \ref Cy_PDM_PCM_DeInit() must be called before calling this function.
*
* \param  base The pointer to the PDM-PCM instance address
* \param  config The pointer to a configuration structure.
* \return error / status code. See \ref cy_en_pdm_pcm_status_t.
*
* An example of a configuration structure:
* \snippet pdm_pcm/snippet/main.c PDM_PCM Configuration
*
*******************************************************************************/
cy_en_pdm_pcm_status_t Cy_PDM_PCM_Init(PDM_Type * base, cy_stc_pdm_pcm_config_t const * config)
{
    cy_en_pdm_pcm_status_t ret = CY_PDM_PCM_BAD_PARAM;

    if((NULL != base) && (NULL != config))
    {
        CY_ASSERT_L3(CY_PDM_PCM_IS_CLK_DIV_VALID(config->clkDiv));
        CY_ASSERT_L3(CY_PDM_PCM_IS_CLK_DIV_VALID(config->mclkDiv));
        CY_ASSERT_L3(CY_PDM_PCM_IS_CKO_CLOCK_DIV_VALID(config->ckoDiv));
        CY_ASSERT_L3(CY_PDM_PCM_IS_SINC_RATE_VALID(config->sincDecRate));
        CY_ASSERT_L3(CY_PDM_PCM_IS_GAIN_VALID(config->gainRight));
        CY_ASSERT_L3(CY_PDM_PCM_IS_GAIN_VALID(config->gainLeft));
        CY_ASSERT_L3(CY_PDM_PCM_IS_STEP_SEL_VALID(config->softMuteFineGain));
        CY_ASSERT_L3(CY_PDM_PCM_IS_CH_SET_VALID(config->chanSelect));
        CY_ASSERT_L3(CY_PDM_PCM_IS_S_CYCLES_VALID(config->softMuteCycles));
        CY_ASSERT_L3(CY_PDM_PCM_IS_CKO_DELAY_VALID(config->ckoDelay));
        CY_ASSERT_L3(CY_PDM_PCM_IS_HPF_GAIN_VALID(config->highPassFilterGain));
        CY_ASSERT_L3(CY_PDM_PCM_IS_WORD_LEN_VALID(config->wordLen));
        CY_ASSERT_L3(CY_PDM_PCM_IS_TRIG_LEVEL(config->rxFifoTriggerLevel, config->chanSelect));

        ret = CY_PDM_PCM_SUCCESS;

        PDM_PCM_CTL(base) &= (uint32_t) ~PDM_CTL_ENABLED_Msk; /* Disable the PDM_PCM block */

        /* The clock setting */
        PDM_PCM_CLOCK_CTL(base) = _VAL2FLD(PDM_CLOCK_CTL_CLK_CLOCK_DIV,     config->clkDiv) |
                                  _VAL2FLD(PDM_CLOCK_CTL_MCLKQ_CLOCK_DIV,   config->mclkDiv) |
                                  _VAL2FLD(PDM_CLOCK_CTL_CKO_CLOCK_DIV,     config->ckoDiv) |
                                  _VAL2FLD(PDM_CLOCK_CTL_SINC_RATE,         config->sincDecRate);

        /* Enable the PDM-PCM block */
        PDM_PCM_CTL(base) = _VAL2FLD(PDM_CTL_PGA_R,                         config->gainRight) |
                            _VAL2FLD(PDM_CTL_PGA_L,                         config->gainLeft) |
                            _VAL2FLD(PDM_CTL_STEP_SEL,                      config->softMuteFineGain) |
                            _BOOL2FLD(PDM_CTL_SOFT_MUTE,                    config->softMuteEnable) |
                            PDM_CTL_ENABLED_Msk;

        PDM_PCM_MODE_CTL(base) = _VAL2FLD(PDM_MODE_CTL_PCM_CH_SET,          config->chanSelect) |
                                 _BOOL2FLD(PDM_MODE_CTL_SWAP_LR,            config->chanSwapEnable) |
                                 _VAL2FLD(PDM_MODE_CTL_S_CYCLES,            config->softMuteCycles) |
                                 _VAL2FLD(PDM_MODE_CTL_CKO_DELAY,           config->ckoDelay) |
                                 _VAL2FLD(PDM_MODE_CTL_HPF_GAIN,            config->highPassFilterGain) |
                                 _BOOL2FLD(PDM_MODE_CTL_HPF_EN_N,           config->highPassDisable);

        PDM_PCM_DATA_CTL(base) = _VAL2FLD(PDM_DATA_CTL_WORD_LEN,            config->wordLen) |
                                 _BOOL2FLD(PDM_DATA_CTL_BIT_EXTENSION,      config->signExtension);

        PDM_PCM_RX_FIFO_CTL(base) = _VAL2FLD(PDM_RX_FIFO_CTL_TRIGGER_LEVEL, config->rxFifoTriggerLevel);

        PDM_PCM_TR_CTL(base) = _BOOL2FLD(PDM_TR_CTL_RX_REQ_EN,              config->dmaTriggerEnable);

        Cy_PDM_PCM_SetInterruptMask(base, config->interruptMask);
    }

    return (ret);
}

/*******************************************************************************
* Function Name: Cy_PDM_PCM_DeInit
****************************************************************************//**
*
* Uninitializes the PDM-PCM module.
*
* \param base The pointer to the PDM-PCM instance address.
*
*******************************************************************************/
void Cy_PDM_PCM_DeInit(PDM_Type * base)
{
    PDM_PCM_CMD(base) = 0UL; /* Stop PDM-PCM operation */
    PDM_PCM_INTR_MASK(base) = 0UL; /* Disable interrupts */
    PDM_PCM_RX_FIFO_CTL(base) = 0UL;
    PDM_PCM_TR_CTL(base) = 0UL;
    PDM_PCM_DATA_CTL(base) = 0UL;
    PDM_PCM_MODE_CTL(base) = CY_PDM_PCM_MODE_CTL_DEFAULT;
    PDM_PCM_CTL(base) = CY_PDM_PCM_CTL_DEFAULT; /* Disable the PDM_PCM IP block */
    PDM_PCM_CLOCK_CTL(base) = CY_PDM_PCM_CLOCK_CTL_DEFAULT; /* The default clock settings */
}

/******************************************************************************
* Function Name: Cy_PDM_PCM_SetGain
***************************************************************************//**
*
* Sets the gain factor to the left or right channel.
*
* \param base
* The pointer to the PDM-PCM instance address.
*
* \param chan
* The channel selector for gain setting \ref cy_en_pdm_pcm_chan_select_t.
*
* \param gain
* Gain for the selected channel \ref cy_en_pdm_pcm_gain_t.
*
******************************************************************************/
void Cy_PDM_PCM_SetGain(PDM_Type * base, cy_en_pdm_pcm_chan_select_t chan, cy_en_pdm_pcm_gain_t gain)
{
    CY_ASSERT_L3(CY_PDM_PCM_IS_CHAN_VALID(chan));
    CY_ASSERT_L3(CY_PDM_PCM_IS_GAIN_VALID(gain));

    if (chan == CY_PDM_PCM_CHAN_LEFT)
    {
         CY_REG32_CLR_SET(PDM_PCM_CTL(base), PDM_CTL_PGA_L, ((uint32_t) gain));
    }
    else
    {
         CY_REG32_CLR_SET(PDM_PCM_CTL(base), PDM_CTL_PGA_R, ((uint32_t) gain));
    }
}

/******************************************************************************
* Function Name: Cy_PDM_PCM_GetGain
***************************************************************************//**
*
* Retrieves the current gain factor of the left or right channel.
*
* \param base
* The pointer to the PDM-PCM instance address.
*
* \param chan
* The channel selector for gain setting \ref cy_en_pdm_pcm_chan_select_t.
*
* \return
* Gain of the selected channel \ref cy_en_pdm_pcm_gain_t.
*
******************************************************************************/
cy_en_pdm_pcm_gain_t Cy_PDM_PCM_GetGain(PDM_Type const * base, cy_en_pdm_pcm_chan_select_t chan)
{
    cy_en_pdm_pcm_gain_t ret;

    CY_ASSERT_L3(CY_PDM_PCM_IS_CHAN_VALID(chan));

    if (chan == CY_PDM_PCM_CHAN_LEFT)
    {
        ret = (cy_en_pdm_pcm_gain_t) ((uint32_t)_FLD2VAL(PDM_CTL_PGA_L, PDM_PCM_CTL(base)));
    }
    else
    {
        ret = (cy_en_pdm_pcm_gain_t) ((uint32_t)_FLD2VAL(PDM_CTL_PGA_R, PDM_PCM_CTL(base)));
    }

    return (ret);
}


/*******************************************************************************
* Function Name: Cy_PDM_PCM_DeepSleepCallback
****************************************************************************//**
*
* This is an example callback function that can be used at the application layer to
* manage the PDM-PCM operation before entering and after exiting Deep Sleep mode.
*
* \param callbackParams
* The structure with the syspm callback parameters,
* see \ref cy_stc_syspm_callback_params_t.
*
* \param mode
* Callback mode, see \ref cy_en_syspm_callback_mode_t
*
* \return
* syspm return status, see \ref cy_en_syspm_status_t
*
*******************************************************************************/
cy_en_syspm_status_t Cy_PDM_PCM_DeepSleepCallback(cy_stc_syspm_callback_params_t const * callbackParams, cy_en_syspm_callback_mode_t mode)
{
    cy_en_syspm_status_t ret = CY_SYSPM_SUCCESS;

    switch(mode)
    {
        case CY_SYSPM_CHECK_READY:
        case CY_SYSPM_CHECK_FAIL:
            break;

        case CY_SYSPM_BEFORE_TRANSITION:
            Cy_PDM_PCM_Disable((PDM_Type*) callbackParams->base); /* Stop PDM-PCM operation */
            /* Unload FIFO to not lose any data (if needed) */
            break;

        case CY_SYSPM_AFTER_TRANSITION:
            Cy_PDM_PCM_ClearFifo((PDM_Type*) callbackParams->base); /* Clear FIFO */
            Cy_PDM_PCM_Enable((PDM_Type*) callbackParams->base); /* Start PDM-PCM operation */
            break;

        default:
            ret = CY_SYSPM_FAIL;
            break;
    }

    return(ret);
}

/** \} group_pdm_pcm_functions */


#endif /* (defined (AUDIOSS_PDM_PRESENT) || defined(CY_DOXYGEN)) */

/* [] END OF FILE */
