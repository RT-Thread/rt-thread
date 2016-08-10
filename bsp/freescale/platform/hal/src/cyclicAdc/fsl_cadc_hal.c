/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#include "fsl_cadc_hal.h"
#if FSL_FEATURE_SOC_CADC_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_HAL_Init
 * Description   : Initialize all the ADC registers to a known state.
 *
 *END**************************************************************************/
void CADC_HAL_Init(ADC_Type * base)
{
    ADC_WR_CTRL1(base, 0x5005);
    ADC_WR_CTRL2(base, 0x5044U);
    ADC_WR_ZXCTRL1(base,0U);
    ADC_WR_ZXCTRL2(base,0U);
    ADC_WR_CLIST1(base, 0x3210U);
    ADC_WR_CLIST2(base, 0x7654U);
    ADC_WR_CLIST3(base, 0xBA98U);
    ADC_WR_CLIST4(base, 0xFEDEU);
    ADC_WR_SDIS(base, 0xF0F0U);
    ADC_WR_LOLIMSTAT(base, 0xFFFFU);
    ADC_WR_HILIMSTAT(base, 0xFFFFU);
    ADC_WR_ZXSTAT(base, 0xFFFFU);
    ADC_WR_PWR(base, 0x1DA7U);
    ADC_WR_CAL(base, 0U);
    ADC_WR_GC1(base, 0U);
    ADC_WR_GC2(base, 0U);
    ADC_WR_SCTRL(base, 0U);
    ADC_WR_PWR2(base, 0x0400U);
    ADC_WR_CTRL3(base, 0U);
    ADC_WR_SCHLTEN(base, 0U);

}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_HAL_ConfigController
 * Description   : Configure the common feature in cyclic ADC module. For
 * detailed items, see to "cadc_common_config_t".
 *
 *END**************************************************************************/
void CADC_HAL_ConfigController(ADC_Type * base, const cadc_controller_config_t *configPtr)
{
    uint16_t ctrl1, ctrl2, pwr, ctrl3;

    /* ADC_CTRL1. */
    ctrl1 = ADC_RD_CTRL1(base);
    ctrl1 &= ~(   ADC_CTRL1_START0_MASK
                | ADC_CTRL1_ZCIE_MASK
                | ADC_CTRL1_LLMTIE_MASK
                | ADC_CTRL1_HLMTIE_MASK
                | ADC_CTRL1_SMODE_MASK
                );
    if (configPtr->zeroCrossingIntEnable)
    {
        ctrl1 |= ADC_CTRL1_ZCIE_MASK;
    }
    if (configPtr->lowLimitIntEnable)
    {
        ctrl1 |= ADC_CTRL1_LLMTIE_MASK;
    }
    if (configPtr->highLimitIntEnable)
    {
        ctrl1 |= ADC_CTRL1_HLMTIE_MASK;
    }
    ctrl1 |= ADC_CTRL1_SMODE((uint32_t)(configPtr->scanMode));

    /* ADC_CTRL2. */
    ctrl2 = ADC_RD_CTRL2(base);
    ctrl2 &= ~(   ADC_CTRL2_START1_MASK
                | ADC_CTRL2_SIMULT_MASK
                );
    if (configPtr->parallelSimultModeEnable)
    {
        ctrl2 |= ADC_CTRL2_SIMULT_MASK;
    }

    /* ADC_PWR. */
    pwr = ADC_RD_PWR(base);
    pwr &= ~( ADC_PWR_ASB_MASK
            | ADC_PWR_PUDELAY_MASK
            | ADC_PWR_APD_MASK
            );
    if (configPtr->autoStandbyEnable)
    {
        pwr |= ADC_PWR_ASB_MASK;
    }
    pwr |= ADC_PWR_PUDELAY((uint16_t)(configPtr->powerUpDelayCount));
    if (configPtr->autoPowerDownEnable)
    {
        pwr |= ADC_PWR_APD_MASK;
    }

    /* ADC_CTRL3. */
    ctrl3 = ADC_RD_CTRL3(base);
    ctrl3 &= ~(ADC_CTRL3_DMASRC_MASK);
    if (kCAdcDmaTriggeredByConvReady == configPtr->dmaSrc)
    {
        ctrl3 |= ADC_CTRL3_DMASRC_MASK;
    }

    ADC_WR_CTRL1(base, ctrl1);
    ADC_WR_CTRL2(base, ctrl2);
    ADC_WR_PWR(base, pwr);
    ADC_WR_CTRL3(base, ctrl3);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_HAL_ConfigConvA
 * Description   : Configure the feature for converter A. For detailed items,
 * see to "cadc_converter_config_t".
 *
 *END**************************************************************************/
void CADC_HAL_ConfigConvA(ADC_Type * base, const cadc_converter_config_t *configPtr)
{
    uint16_t ctrl1, ctrl2, cal, pwr2, ctrl3;

    /* ADC_CTRL1. */
    ctrl1 = ADC_RD_CTRL1(base);
    ctrl1 &= ~(   ADC_CTRL1_DMAEN0_MASK
                | ADC_CTRL1_STOP0_MASK
                | ADC_CTRL1_START0_MASK
                | ADC_CTRL1_SYNC0_MASK
                | ADC_CTRL1_EOSIE0_MASK
                );
    if (configPtr->dmaEnable)
    {
        ctrl1 |= ADC_CTRL1_DMAEN0_MASK;
    }
    if (configPtr->stopEnable)
    {
        ctrl1 |= ADC_CTRL1_STOP0_MASK;
    }
    if (configPtr->syncEnable)
    {
        ctrl1 |= ADC_CTRL1_SYNC0_MASK;
    }
    if (configPtr->endOfScanIntEnable)
    {
        ctrl1 |= ADC_CTRL1_EOSIE0_MASK;
    }

    /* ADC_CTRL2. */
    ctrl2 = ADC_RD_CTRL2(base);
    ctrl2 &= ~(   ADC_CTRL2_START1_MASK
                | ADC_CTRL2_DIV0_MASK
                );
    ctrl2 |= ADC_CTRL2_DIV0((uint16_t)(configPtr->clkDivValue));

    /* ADC_CAL. */
    cal = ADC_RD_CAL(base);
    cal &= ~(  ADC_CAL_SEL_VREFH_A_MASK
             | ADC_CAL_SEL_VREFLO_A_MASK
            );
    if (configPtr->useChnInputAsVrefH)
    {
        cal |= ADC_CAL_SEL_VREFH_A_MASK;
    }
    if (configPtr->useChnInputAsVrefL)
    {
        cal |= ADC_CAL_SEL_VREFLO_A_MASK;
    }

    /* ADC_PWR2. */
    pwr2 = ADC_RD_PWR2(base);
    pwr2 &= ~(ADC_PWR2_SPEEDA_MASK);
    pwr2 |= ADC_PWR2_SPEEDA(configPtr->speedMode);

    /* ADC_CTRL3. */
    ctrl3 = ADC_RD_CTRL3(base);
    ctrl3 &= ~(ADC_CTRL3_SCNT0_MASK);
    ctrl3 |= ADC_CTRL3_SCNT0(configPtr->sampleWindowCount);

    ADC_WR_CTRL1(base, ctrl1);
    ADC_WR_CTRL2(base, ctrl2);
    ADC_WR_CAL(base, cal);
    ADC_WR_PWR2(base, pwr2);
    ADC_WR_CTRL3(base, ctrl3);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_HAL_ConfigConvB
 * Description   : Configure the feature for conversion B. For detailed items,
 * see to "cadc_converter_config_t".
 *
 *END**************************************************************************/
void CADC_HAL_ConfigConvB(ADC_Type * base, const cadc_converter_config_t *configPtr)
{
    uint16_t ctrl2, pwr2, cal, ctrl3;

    /* ADC_CTRL2. */
    ctrl2 = ADC_RD_CTRL2(base);
    ctrl2 &= ~(   ADC_CTRL2_DMAEN1_MASK
                | ADC_CTRL2_STOP1_MASK
                | ADC_CTRL2_START1_MASK
                | ADC_CTRL2_SYNC1_MASK
                | ADC_CTRL2_EOSIE1_MASK
                );
    if (configPtr->dmaEnable)
    {
        ctrl2 |= ADC_CTRL2_DMAEN1_MASK;
    }
    if (configPtr->stopEnable)
    {
        ctrl2 |= ADC_CTRL2_STOP1_MASK;
    }
    if (configPtr->syncEnable)
    {
        ctrl2 |= ADC_CTRL2_SYNC1_MASK;
    }
    if (configPtr->endOfScanIntEnable)
    {
        ctrl2 |= ADC_CTRL2_EOSIE1_MASK;
    }

    /* ADC_PWR2. */
    pwr2 = ADC_RD_PWR2(base);
    pwr2 &= ~(    ADC_PWR2_DIV1_MASK
                | ADC_PWR2_SPEEDB_MASK
            );
    pwr2 |= ADC_PWR2_DIV1((uint16_t)(configPtr->clkDivValue))
          | ADC_PWR2_SPEEDB((uint16_t)(configPtr->speedMode));

    /* ADC_CAL. */
    cal = ADC_RD_CAL(base);
    cal &= ~( ADC_CAL_SEL_VREFH_B_MASK
            | ADC_CAL_SEL_VREFLO_B_MASK );
    if (configPtr->useChnInputAsVrefH)
    {
        cal |= ADC_CAL_SEL_VREFH_B_MASK;
    }
    if (configPtr->useChnInputAsVrefL)
    {
        cal |= ADC_CAL_SEL_VREFLO_B_MASK;
    }

    /* ADC_CTRL3. */
    ctrl3 = ADC_RD_CTRL3(base);
    ctrl3 &= ~(ADC_CTRL3_SCNT1_MASK);
    ctrl3 |= ADC_CTRL3_SCNT1((uint16_t)(configPtr->sampleWindowCount));

    ADC_WR_CTRL2(base, ctrl2);
    ADC_WR_PWR2(base, pwr2);
    ADC_WR_CAL(base, cal);
    ADC_WR_CTRL3(base, ctrl3);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_HAL_ConfigChn
 * Description   : Configure the feature for the sample channel. For detailed
 * items, see to "cadc_chn_config_t".
 *
 *END**************************************************************************/
void CADC_HAL_ConfigChn(ADC_Type * base, const cadc_chn_config_t *configPtr)
{
    uint16_t chns, tmp16;

    /* Configure if enable the differential sample. */
    chns = configPtr->diffChns;
    switch (configPtr->diffChns)
    {
    case kCAdcDiffChnANB0_1:
    case kCAdcDiffChnANB2_3:
    case kCAdcDiffChnANA0_1:
    case kCAdcDiffChnANA2_3:
        if ( (kCAdcDiffChnANB0_1 == chns) || (kCAdcDiffChnANB2_3 == chns) )
        {
            chns -= 2U;
        }
        tmp16 = ADC_RD_CTRL1(base);
        tmp16 &= ~(1U<<(ADC_CTRL1_CHNCFG_L_SHIFT+(uint16_t)chns) );
        if (kCAdcChnSelBoth == configPtr->diffSelMode) /* Enable differential sample . */
        {
            tmp16 |= (1U<<(ADC_CTRL1_CHNCFG_L_SHIFT+(uint16_t)chns) );
        }
        ADC_WR_CTRL1(base, tmp16);
        break;
    case kCAdcDiffChnANB4_5:
    case kCAdcDiffChnANB6_7:
    case kCAdcDiffChnANA4_5:
    case kCAdcDiffChnANA6_7:
        if ( (kCAdcDiffChnANB4_5 == chns) || (kCAdcDiffChnANB6_7 == chns) )
        {
            chns -= 2U;
        }
        chns -= 2U;
        tmp16 = ADC_RD_CTRL2(base);
        tmp16 &= ~(1U<<(ADC_CTRL2_CHNCFG_H_SHIFT + (uint16_t)chns) );
        if (kCAdcChnSelBoth == configPtr->diffSelMode) /* Enable differential sample . */
        {
            tmp16 |= (1U<<(ADC_CTRL2_CHNCFG_H_SHIFT + (uint16_t)chns) );
        }
        ADC_WR_CTRL2(base, tmp16);
        break;
    default:
        break;
    }
    /* Configure the gain for each channel. */
    chns = (uint16_t)(configPtr->diffChns) * 2U;
    if (chns < 8U)
    {
        tmp16 = ADC_RD_GC1(base);
        if (kCAdcChnSelN == configPtr->diffSelMode)
        {
            chns++;
        }
        tmp16 &= ~(0x3U<<(chns*2U));
        tmp16 |= (uint16_t)(configPtr->gainMode<<(chns*2U));
        if (kCAdcChnSelBoth == configPtr->diffSelMode)
        {
            chns++;
            tmp16 &= ~(0x3U<<(chns*2U));
            tmp16 |= (uint16_t)(configPtr->gainMode<<(chns*2U));
        }
        ADC_WR_GC1(base, tmp16);
    }
    else if (chns < 16U)
    {
        chns -= 8U;
        tmp16 = ADC_RD_GC2(base);
        if (kCAdcChnSelN == configPtr->diffSelMode)
        {
            chns++;
        }
        tmp16 &= ~(0x3U<<(chns*2U));
        tmp16 |= (uint16_t)(configPtr->gainMode<<(chns*2U));
        if (kCAdcChnSelBoth == configPtr->diffSelMode)
        {
            chns++;
            tmp16 &= ~(0x3U<<(chns*2U));
            tmp16 |= (uint16_t)(configPtr->gainMode<<(chns*2U));
        }
        ADC_WR_GC2(base, tmp16);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_HAL_SetSlotSampleChn
 * Description   : Set sample channel for each slot in conversion sequence.
 *
 *END**************************************************************************/
static void CADC_HAL_SetSlotSampleChn(ADC_Type * base, uint32_t slotIdx,
    cadc_diff_chn_t diffChns, cadc_chn_sel_mode_t selMode)
{
    uint16_t tmp16;

    if (slotIdx < 4U) /* Slot 0 - 3. */
    {
        tmp16 = ADC_RD_CLIST1(base) & (uint16_t)(~(uint16_t)(((uint16_t)(0xFU))<<(slotIdx*4U)));
        switch (selMode)
        {
        case kCAdcChnSelP:
        case kCAdcChnSelBoth:
            tmp16 |= (uint16_t)((((uint16_t)(diffChns))<<1)<<(slotIdx*4U));
            break;
        case kCAdcChnSelN:
            tmp16 |= (uint16_t)(((((uint16_t)(diffChns))<<1)+1U)<<(slotIdx*4U));
            break;
        default:
            break;
        }
        ADC_WR_CLIST1(base, tmp16);

    }
    else if (slotIdx < 8U) /* Slot 4 - 7. */
    {
        slotIdx -= 4U;
        tmp16 = ADC_RD_CLIST2(base) & (uint16_t)(~(uint16_t)((((uint16_t)(0xFU))<<(slotIdx*4U))));
        switch (selMode)
        {
        case kCAdcChnSelP:
        case kCAdcChnSelBoth:
            tmp16 |= (uint16_t)((((uint16_t)(diffChns))<<1)<<(slotIdx*4U));
            break;
        case kCAdcChnSelN:
            tmp16 |= (uint16_t)(((((uint16_t)(diffChns))<<1)+1U)<<(slotIdx*4U));
            break;
        default:
            break;
        }
        ADC_WR_CLIST2(base, tmp16);
    }
    else if (slotIdx < 12U) /* Slot 8 - 11U. */
    {
        slotIdx -= 8U;
        tmp16 = ADC_RD_CLIST3(base) & (uint16_t)(~(uint16_t)((((uint16_t)(0xFU))<<(slotIdx*4U))));
        switch (selMode)
        {
        case kCAdcChnSelP:
        case kCAdcChnSelBoth:
            tmp16 |= (uint16_t)((((uint16_t)(diffChns))<<1)<<(slotIdx*4U));
            break;
        case kCAdcChnSelN:
            tmp16 |= (uint16_t)(((((uint16_t)(diffChns))<<1)+1U)<<(slotIdx*4U));
            break;
        default:
            break;
        }
        ADC_WR_CLIST3(base, tmp16);
    }
    else if (slotIdx < 16U) /* Slot 12 - 15U. */
    {
        slotIdx -= 12U;
        tmp16 = ADC_RD_CLIST4(base) & (uint16_t)(~(uint16_t)(((uint16_t)(0xFU))<<(slotIdx*4U)));
        switch (selMode)
        {
        case kCAdcChnSelP:
        case kCAdcChnSelBoth:
            tmp16 |= (uint16_t)((((uint16_t)(diffChns))<<1)<<(slotIdx*4U));
            break;
        case kCAdcChnSelN:
            tmp16 |= (uint16_t)(((((uint16_t)(diffChns))<<1)+1U)<<(slotIdx*4U));
            break;
        default:
            break;
        }
        ADC_WR_CLIST4(base, tmp16);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_HAL_ConfigSeqSlot
 * Description   : Configure the feature for sample sequence's slot. For detailed
 * items, see to "cadc_slot_config_t"
 *
 *END**************************************************************************/
void CADC_HAL_ConfigSeqSlot(ADC_Type * base, uint32_t slotIdx,
    const cadc_slot_config_t *configPtr)
{
    uint16_t zxctrl;
    CADC_HAL_SetSlotSampleChn(base, slotIdx, configPtr->diffChns, configPtr->diffSel);
    if (configPtr->slotDisable)
    {
        ADC_SET_SDIS(base, (1U<<slotIdx));
    }
    else
    {
        ADC_CLR_SDIS(base, (1U<<slotIdx));
    }
    ADC_WR_LOLIM(base, slotIdx, configPtr->lowLimitValue);
    ADC_WR_HILIM(base, slotIdx, configPtr->highLimitValue);
    ADC_WR_OFFST(base, slotIdx, configPtr->offsetValue);
    if (configPtr->syncPointEnable)
    {
        ADC_SET_SCTRL(base, (1U<<slotIdx) );
    }
    else
    {
        ADC_CLR_SCTRL(base, (1U<<slotIdx) );
    }
    if (configPtr->syncIntEnable)
    {
        ADC_SET_SCHLTEN(base, (1U<<slotIdx) );
    }
    else
    {
        ADC_CLR_SCHLTEN(base, (1U<<slotIdx) );
    }
    if (slotIdx < 8U)
    {
        slotIdx *= 2U;
        zxctrl = ADC_RD_ZXCTRL1(base) & ~(0x3U << slotIdx);
        zxctrl |= (uint16_t)(configPtr->zeroCrossingMode << slotIdx );
        ADC_WR_ZXCTRL1(base, zxctrl);
    }
    else if (slotIdx < 16U)
    {
        slotIdx -= 8U;
        slotIdx *= 2U;
        zxctrl = ADC_RD_ZXCTRL2(base) & ~(0x3U << slotIdx);
        zxctrl |= (uint16_t)(configPtr->zeroCrossingMode << slotIdx );
        ADC_WR_ZXCTRL2(base, zxctrl);
    }
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

