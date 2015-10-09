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

#include "fsl_afe_hal.h"
#if FSL_FEATURE_SOC_AFE_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_HAL_Init
 * Description   : Reset AFE's common registers to a known state. This state is
 * defined in Reference Manual, which is power on reset value.
 *
 *END*************************************************************************/
void AFE_HAL_Init(AFE_Type * base)
{
    AFE_WR_CR(base, 0x40FA00U);
    AFE_WR_CKR(base, 0x10000000U);
}
  
/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_HAL_ChnInit
 * Description   : Reset AFE's channel's registers to a known state. This state is
 * defined in Reference Manual, which is power on reset value.
 *
 *END*************************************************************************/
void AFE_HAL_ChnInit(AFE_Type * base, uint32_t chn)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
#if defined(KM34Z7_SERIES)    
    if(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER_WITH_PGA)
    {
        AFE_WR_CFR(base, chn, (uint32_t)kAfePgaGainBy1 << AFE_CFR_PGA_GAIN_SEL_SHIFT);
    }
    else if(FSL_FEATURE_AFE_CHANNEL_NUMBER_WITH_PGA < FSL_FEATURE_AFE_CHANNEL_NUMBER)
    {
        AFE_WR_CFR(base, chn, 0x0U);
    }
    AFE_WR_DR(base, chn, 0x0U);    
#else
	if(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER_WITH_PGA)
    {
        AFE_WR_CFRx(base, chn, (uint32_t)kAfePgaGainBy1 << AFE_CFR0_PGA_GAIN_SEL_SHIFT);
    }
    else
    {
        AFE_WR_CFRx(base, chn, 0x0U);
    }
    AFE_WR_DRx(base, chn, 0x0U);   
#endif
    AFE_BWR_DI_INTEN(base, chn, false);
    AFE_BWR_DI_DMAEN(base, chn, false);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_HAL_ConfigChn
 * Description   : Configure the AFE channel.
 *
 *END*************************************************************************/
void AFE_HAL_ConfigChn(AFE_Type * base, uint32_t chn, afe_chn_set_t * chnStructPtr)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
    uint32_t regData = 0;
    
    regData = AFE_CFR_DEC_OSR((uint32_t)chnStructPtr->decimOSR) |
              AFE_CFR_BYP_MODE(chnStructPtr->bypassEnable) |
              AFE_CFR_SD_MOD_EN(chnStructPtr->modulatorEnable) |
              AFE_CFR_DEC_EN(chnStructPtr->decimFilterEnable) |
              AFE_CFR_DEC_CLK_EDGE_SEL(chnStructPtr->decimNegedgeEnable) |
              AFE_CFR_CC(chnStructPtr->continuousConvEnable) |
              AFE_CFR_HW_TRG(chnStructPtr->hwTriggerEnable) |
              AFE_CFR_DEC_CLK_INP_SEL(chnStructPtr->externClockEnable) |
              AFE_CFR_PGA_GAIN_SEL(chnStructPtr->pgaGainSel) |
              AFE_CFR_PGA_EN(chnStructPtr->pgaEnable);
              
    AFE_WR_CFR(base, chn, regData);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_HAL_ConfigConv
 * Description   : Configure the AFE converter.
 *
 *END*************************************************************************/
void AFE_HAL_ConfigConverter(AFE_Type * base, afe_converter_config_t * converterStructPtr)
{
    uint32_t regData = 0;
    
    regData = AFE_CR_STRTUP_CNT((uint8_t)converterStructPtr->startupCnt) |
              AFE_CR_RESULT_FORMAT(converterStructPtr->resultFormat) |
              AFE_CR_DLY_OK(converterStructPtr->delayOk) |
              AFE_CR_RST_B(converterStructPtr->swReset) |
              AFE_CR_LPM_EN(converterStructPtr->lowPowerEnable) |
              AFE_CR_SOFT_TRG0(converterStructPtr->swTriggChn0) |
              AFE_CR_SOFT_TRG1(converterStructPtr->swTriggChn1) |
              AFE_CR_SOFT_TRG2(converterStructPtr->swTriggChn2) |
#ifdef FSL_FEATURE_AFE_HAS_FOUR_CHANNELS                   
              AFE_CR_SOFT_TRG3(converterStructPtr->swTriggChn3)  |
#endif //FSL_FEATURE_AFE_HAS_FOUR_CHANNELS                  
              AFE_CR_MSTR_EN(converterStructPtr->masterEnable);
          
    AFE_WR_CR(base, regData);               
}
#endif
