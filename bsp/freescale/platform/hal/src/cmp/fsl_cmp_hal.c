/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#include "fsl_cmp_hal.h"
#if FSL_FEATURE_SOC_CMP_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_HAL_Init
 * Description   : Reset CMP's registers to a known state. This state is
 * defined in Reference Manual, which is power on reset value.
 *
 *END*************************************************************************/
void CMP_HAL_Init(CMP_Type * base)
{
    CMP_WR_CR0(base, 0U);
    CMP_WR_CR1(base, 0U);
    CMP_WR_FPR(base, 0U);
    CMP_WR_SCR(base, 0U);
    CMP_WR_DACCR(base, 0U);
    CMP_WR_MUXCR(base, 0U);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_HAL_ConfigComparator
 * Description   : Configure the CMP's comparator function.
 *
 *END*************************************************************************/
void CMP_HAL_ConfigComparator(CMP_Type * base, const cmp_comparator_config_t *configPtr)
{
    uint8_t cr0, cr1, scr, muxcr;

    /* CR0. */
    cr0 = CMP_RD_CR0(base);
    cr0 &= ~CMP_CR0_HYSTCTR_MASK;
    cr0 |= CMP_CR0_HYSTCTR(configPtr->hystersisMode);

    /* CR1. */
    cr1 = CMP_RD_CR1(base);
    cr1 &= ~(  CMP_CR1_OPE_MASK
             | CMP_CR1_COS_MASK
             | CMP_CR1_INV_MASK
             | CMP_CR1_PMODE_MASK
#if FSL_FEATURE_CMP_HAS_TRIGGER_MODE
             | CMP_CR1_TRIGM_MASK
#endif /* FSL_FEATURE_CMP_HAS_TRIGGER_MODE */
        );
    if (configPtr->pinoutEnable)
    {
        cr1 |= CMP_CR1_OPE_MASK;
    }
    if (configPtr->pinoutUnfilteredEnable)
    {
        cr1 |= CMP_CR1_COS_MASK;
    }
    if (configPtr->invertEnable)
    {
        cr1 |= CMP_CR1_INV_MASK;
    }
    if (configPtr->highSpeedEnable)
    {
        cr1 |= CMP_CR1_PMODE_MASK;
    }
#if FSL_FEATURE_CMP_HAS_TRIGGER_MODE
    if (configPtr->triggerEnable)
    {
        cr1 |= CMP_CR1_TRIGM_MASK;
    }
#endif /* FSL_FEATURE_CMP_HAS_TRIGGER_MODE */

    /* SCR. */
    scr = CMP_RD_SCR(base);
    scr &= ~( CMP_SCR_IER_MASK
            | CMP_SCR_IEF_MASK
            | CMP_SCR_CFR_MASK
            | CMP_SCR_CFF_MASK
#if FSL_FEATURE_CMP_HAS_DMA
            | CMP_SCR_DMAEN_MASK
#endif /* FSL_FEATURE_CMP_HAS_DMA */
    );

#if FSL_FEATURE_CMP_HAS_DMA
    if (configPtr->dmaEnable)
    {
        scr |= CMP_SCR_DMAEN_MASK;
    }
#endif /* FSL_FEATURE_CMP_HAS_DMA */

    if (configPtr->risingIntEnable)
    {
        scr |= CMP_SCR_IER_MASK;
    }
    if (configPtr->fallingIntEnable)
    {
        scr |= CMP_SCR_IEF_MASK;
    }

    /* MUXCR. */
    muxcr = CMP_MUXCR_PSEL((uint32_t)(configPtr->plusChnMux))
          | CMP_MUXCR_MSEL((uint32_t)(configPtr->minusChnMux));

    CMP_WR_CR0(base, cr0);
    CMP_WR_CR1(base, cr1);
    CMP_WR_SCR(base, scr);
    CMP_WR_MUXCR(base, muxcr);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_HAL_ConfigDacChn
 * Description   : Configure the CMP's DAC function.
 *
 *END*************************************************************************/
void CMP_HAL_ConfigDacChn(CMP_Type * base, const cmp_dac_config_t *configPtr)
{
    uint8_t daccr;

    daccr = CMP_RD_DACCR(base);
    daccr &= ~(   CMP_DACCR_DACEN_MASK
                | CMP_DACCR_VRSEL_MASK
                | CMP_DACCR_VOSEL_MASK );
    if (configPtr->dacEnable)
    {
        daccr |= CMP_DACCR_DACEN_MASK;
    }
    if (kCmpDacRefVoltSrcOf2 == configPtr->refVoltSrcMode)
    {
        daccr |= CMP_DACCR_VRSEL_MASK;
    }
    daccr |= CMP_DACCR_VOSEL(configPtr->dacValue);

    CMP_WR_DACCR(base, daccr);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : CMP_HAL_ConfigSampleFilter
 * Description   : Configure the CMP's sample or filter function.
 *
 *END*************************************************************************/
void CMP_HAL_ConfigSampleFilter(CMP_Type * base, const cmp_sample_filter_config_t *configPtr)
{
    uint8_t cr0, cr1, fpr;

    cr0 = CMP_RD_CR0(base) & ~CMP_CR0_FILTER_CNT_MASK;
    cr1 = CMP_RD_CR1(base);
    cr1 &= ~(  CMP_CR1_SE_MASK
#if FSL_FEATURE_CMP_HAS_WINDOW_MODE
             | CMP_CR1_WE_MASK
#endif /* FSL_FEATURE_CMP_HAS_WINDOW_MODE */
    );
    fpr = 0U;

    /* Configure the comparator Window/Filter mode. */
    switch (configPtr->workMode)
    {
    case kCmpContinuousMode:
        /* Continuous Mode:
        * Both window control and filter blocks are completely bypassed.
        * The output of comparator is updated continuously.
        */
        cr0 |= CMP_CR0_FILTER_CNT((uint8_t)kCmpFilterCountSampleOf0);
        fpr |= CMP_FPR_FILT_PER(0U);
        break;
    case kCmpSampleWithNoFilteredMode:
        /* Sample, Non-Filtered Mode:
        * Windowing control is completely bypassed. The output of
        * comparator is sampled whenever a rising-edge is detected on
        * the filter block clock input. Of course, the filter clock
        * prescaler can be configured as the divider from bus clock.
        */
        if (configPtr->useExtSampleOrWindow)
        {
            cr1 |= CMP_CR1_SE_MASK;
        }
        else
        {
            fpr |= CMP_FPR_FILT_PER(configPtr->filterClkDiv);
        }
        cr0 |= CMP_CR0_FILTER_CNT((uint8_t)kCmpFilterCountSampleOf1);
        break;
    case kCmpSampleWithFilteredMode:
        /* Sample, Filtered Mode:
        * Similar to "Sample, Non-Filtered Mode", but the filter is
        * active in this mode. The filter counter value becomes
        * configurable as well.
        */
        if (configPtr->useExtSampleOrWindow)
        {
            cr1 |= CMP_CR1_SE_MASK;
        }
        else
        {
            fpr |= CMP_FPR_FILT_PER(configPtr->filterClkDiv);
        }
        cr0 |= CMP_CR0_FILTER_CNT((uint8_t)(configPtr->filterCount));
        break;
    case kCmpWindowedMode:
        /* Windowed Mode:
        * In Windowed Mode, only output of analog comparator is passed
        * only when the WINDOW signal is high. The last latched value
        * is held when WINDOW signal is low.
        */
#if FSL_FEATURE_CMP_HAS_WINDOW_MODE
        cr1 |= CMP_CR1_WE_MASK;
#endif /* FSL_FEATURE_CMP_HAS_WINDOW_MODE */
        cr0 |= CMP_CR0_FILTER_CNT((uint8_t)kCmpFilterCountSampleOf0);
        fpr |= CMP_FPR_FILT_PER(0U);
        break;
    case kCmpWindowedFilteredMode:
        /* Window/Filtered Mode:
        * This mode is kind of complex, as it uses both windowing and
        * filtering features. It also has the highest latency of all
        * modes. This can be approximated: up to 1 bus clock
        * synchronization in the window function
        * + ( ( filter counter * filter prescaler ) + 1) bus clock
        * for the filter function.
        */
#if FSL_FEATURE_CMP_HAS_WINDOW_MODE
        cr1 |= CMP_CR1_WE_MASK;
#endif /* FSL_FEATURE_CMP_HAS_WINDOW_MODE */
        cr0 |= CMP_CR0_FILTER_CNT((uint8_t)(configPtr->filterCount));
        fpr |= CMP_FPR_FILT_PER(configPtr->filterClkDiv);
        break;
    default:
        /* Default Mode:
        * Same as continuous mode. See to "kCmpContinuousMode".
        */
        cr0 |= CMP_CR0_FILTER_CNT((uint8_t)kCmpFilterCountSampleOf0);
        fpr |= CMP_FPR_FILT_PER(0U);
        break;
    }

    CMP_WR_CR0(base, cr0);
    CMP_WR_CR1(base, cr1);
    CMP_WR_FPR(base, fpr);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

