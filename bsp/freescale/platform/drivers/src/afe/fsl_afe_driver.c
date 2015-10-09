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

#include <assert.h>
#include <string.h>
#include "fsl_afe_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_AFE_COUNT


/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_StructInitUserConfigDefault
 * Description   :  Fill initial user configuration structure for default setting. 
 * It includes the setting of :
 *     .lowPowerEnable = false
 *     .resultFormat = kAfeResultFormatLeft
 *     .clkDividerMode = kAfeClkDividerInputOf2
 *     .clkSrcMode = kAfeClkSrcClk0
 *     .startupCnt = 0
 *
 * This is just the default configuration, some or all fields of this structure
 * have to be changed according to user's application.
 *
 *END*************************************************************************/
afe_status_t  AFE_DRV_StructInitUserConfigDefault(afe_user_config_t *userConfigPtr)
{
    if ( !userConfigPtr )
    {
        return kStatus_AFE_InvalidArgument;
    }

    userConfigPtr->lowPowerEnable = false;
    userConfigPtr->resultFormat = kAfeResultFormatLeft;
    userConfigPtr->clkDividerMode = kAfeClkDividerInputOf2;
    userConfigPtr->clkSrcMode = kAfeClkSrcClk0;
    userConfigPtr->startupCnt = 0;

    return kStatus_AFE_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_StructInitChnConfigDefault
 * Description   : Fill initial channel configuration structure for default
 * setting. 
 * It includes the setting of :
 *     .hwTriggerEnable = false
 *     .continuousConvEnable = false
 *     .chnMode = kAfeNormal
 *     .decimOSR = kAfeDecimOsrOf64
 *     .delay = 0
 *     .pgaGainSel = kAfePgaGain1
 *     .ichnEvent = kAfeNoneReq
 *
 * This is just the default configuration, some or all fields of this structure
 * have to be changed according to user's application.
 *
 *END*************************************************************************/
afe_status_t AFE_DRV_StructInitChnConfigDefault(afe_chn_config_t * chnConfigPtr)
{
    if ( !chnConfigPtr )
    {
        return kStatus_AFE_InvalidArgument;
    }

    chnConfigPtr->hwTriggerEnable = false;
    chnConfigPtr->continuousConvEnable = false;
    chnConfigPtr->chnMode = kAfeNormal;
    chnConfigPtr->decimOSR = kAfeDecimOsrOf64;
    chnConfigPtr->delay = 0;
    chnConfigPtr->pgaGainSel = kAfePgaGain1;
    chnConfigPtr->chnEvent = kAfeNoneReq;
      
    return kStatus_AFE_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_Init
 * Description   : Initialize the AFE module. This function enables the clock and
 * for AFE module. And the AFE module will be configured according to userConfig
 * structure and startupCount value. 
 *
 *END*************************************************************************/
afe_status_t AFE_DRV_Init(uint32_t instance, afe_user_config_t *userConfigPtr)
{

    AFE_Type * base = g_afeBase[instance];
    
    if (!userConfigPtr)
    {
        return kStatus_AFE_InvalidArgument;
    }
    
    afe_converter_config_t converterConfigStruct;
    
     /* Clear the channel setting structure and set PGA gain to the default value. */
    memset(&converterConfigStruct, 0, sizeof(afe_chn_set_t));
    converterConfigStruct.swReset = true;
    converterConfigStruct.startupCnt = 125;
    
    /* Enable clock for AFE. */
    CLOCK_SYS_EnableAfeClock(instance);
           
    /* Low power. */
    converterConfigStruct.lowPowerEnable = userConfigPtr->lowPowerEnable;

    /* Start up count. */
    if(userConfigPtr->startupCnt >= 2)
    {
        converterConfigStruct.startupCnt = userConfigPtr->startupCnt;
    }
    else if(userConfigPtr->clkSrcMode == kAfeClkSrcClk1)
    {
        uint32_t clkDiv;
    
        /* Get the selected modulator clock frequency*/
        uint32_t clockFreq = CLOCK_SYS_GetAfeFreq(0, CLOCK_HAL_GetAfeClkSrc(SIM) );
        clkDiv = 1 << (uint32_t)userConfigPtr->clkDividerMode; 
    
        /*Compute start up delay*/        
        double startup = ((clockFreq/clkDiv)*0.00002);
        converterConfigStruct.startupCnt = (uint8_t)startup; 
    }
    else
    {
        converterConfigStruct.startupCnt = 2;
    }
    
    /* Input clock select. */
    AFE_HAL_SetClkSourceMode(base, userConfigPtr->clkSrcMode);
       
    /* Clock divider. */
    AFE_HAL_SetClkDividerMode(base, userConfigPtr->clkDividerMode);

    /* Result format*/
    converterConfigStruct.resultFormat = userConfigPtr->resultFormat;

    AFE_HAL_ConfigConverter(base, &converterConfigStruct);
      
    return kStatus_AFE_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_ChnInit
 * Description   : Initialize the AFE module's channel. This function configures
 * selected channel according to chnConfig structure. The interrupt is allowed
 * in this function if needed.
 *
 *END*************************************************************************/
afe_status_t AFE_DRV_ChnInit(uint32_t instance, uint32_t chn, afe_chn_config_t *chnConfigPtr)
{
    AFE_Type * base = g_afeBase[instance];

    if (!chnConfigPtr)
    {
        return kStatus_AFE_InvalidArgument;
    }
    
    afe_chn_set_t chnConfigStruct;
    
    /* Clear the channel setting structure and set PGA gain to the default value. */
    memset(&chnConfigStruct, 0, sizeof(afe_chn_set_t));
    chnConfigStruct.pgaGainSel = kAfePgaGainBy1;
    
    /* Configure channel to the reset state. */
    AFE_HAL_ChnInit(base, chn);            
    
    
    /* Enable decimation filter. */
    chnConfigStruct.decimFilterEnable = true;
    
    chnConfigStruct.hwTriggerEnable = chnConfigPtr->hwTriggerEnable;

    chnConfigStruct.continuousConvEnable = chnConfigPtr->continuousConvEnable;
    
    /* If bypass mode is enable*/
    if(chnConfigPtr->chnMode != kAfeNormal)
    { 
        chnConfigStruct.bypassEnable = true;
      
        switch (chnConfigPtr->chnMode){
            case kAfeBypassExternCltPosEdge :
                chnConfigStruct.externClockEnable = true;                
                chnConfigStruct.decimNegedgeEnable = false;
                break;
            case kAfeBypassExternClkNegEdge :
                chnConfigStruct.externClockEnable = true;
                chnConfigStruct.decimNegedgeEnable = true;
                break;
            case kAfeBypassInternClkPosEdge :
                chnConfigStruct.externClockEnable = false;
                chnConfigStruct.decimNegedgeEnable = false;
                break;    
            case kAfeBypassInternClkNegEdge :
                chnConfigStruct.externClockEnable = false;
                chnConfigStruct.decimNegedgeEnable = true;
                break;  
            default :
                return kStatus_AFE_InvalidArgument;
        }
    }
    else
    {
        chnConfigStruct.modulatorEnable = true;
        
        if(chnConfigPtr->pgaGainSel == kAfePgaDisable)
        {
            chnConfigStruct.pgaEnable = false;
        }
        else
        {
            if (!(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER_WITH_PGA))
            {
                return kStatus_AFE_InvalidArgument;
            }
            /* Set the PGA*/
            chnConfigStruct.pgaEnable = true;
            chnConfigStruct.pgaGainSel = (afe_pga_gain_mode_t)chnConfigPtr->pgaGainSel;
        }
    }
    
    chnConfigStruct.decimOSR = chnConfigPtr->decimOSR;
    
    AFE_HAL_ConfigChn(base, chn, &chnConfigStruct);
    
    AFE_HAL_SetDelayVal(base, chn, chnConfigPtr->delay);

    switch(chnConfigPtr->chnEvent)
    {
        case kAfeNoneReq :
            AFE_HAL_SetIntEnableCmd(base, chn, false);
            AFE_HAL_SetDmaEnableCmd(base, chn, false);
            INT_SYS_DisableIRQ(g_afeIrqId[chn] );
            break;
        case kAfeIntReq :
            AFE_HAL_SetIntEnableCmd(base, chn, true);
            AFE_HAL_SetDmaEnableCmd(base, chn, false);
            INT_SYS_EnableIRQ(g_afeIrqId[chn] );
            break;    
        case kAfeDmaReq :
            AFE_HAL_SetIntEnableCmd(base, chn, false);
            AFE_HAL_SetDmaEnableCmd(base, chn, true);
            INT_SYS_DisableIRQ(g_afeIrqId[chn] );
            break; 
        default :
                return kStatus_AFE_InvalidArgument;    
    }

    return kStatus_AFE_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_WaitConvDone
 * Description   : Wait the until the last conversion is not completed. This function
 * should be called to wait for the conversion's complete when no interrupt or
 * DMA mode is used for the AFE module. After the waiting, the available data 
 * of conversion is stored in the result register. 
 *
 *END*************************************************************************/
void AFE_DRV_WaitConvDone(uint32_t instance, uint32_t chn)
{
    AFE_Type * base = g_afeBase[instance];

    while ( !AFE_HAL_GetConvCompleteFlag(base, chn) )
    {}
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_WaitChnReady
 * Description   : Wait until the channel is not ready to conversation. 
 *
 *END*************************************************************************/
void AFE_DRV_WaitChnReady(uint32_t instance, uint32_t chn)
{
    AFE_Type * base = g_afeBase[instance];

    while ( !AFE_HAL_GetReadyFlag(base, chn) )
    {}
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_SoftTriggerConv
 * Description   : Do a software trigger of selected channels. If software 
 * triggering is selected for desired channels, calling this function triggers
 * conversion on selected AFE channels
 *
 *END*************************************************************************/
void AFE_DRV_SoftTriggerConv(uint32_t instance, uint32_t chnMask)
{
    AFE_Type * base = g_afeBase[instance];
    
    AFE_HAL_ChnSwTriggerCmd(base, chnMask);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_GetChnFlag
 * Description   : Get the status of selected AFE channel and selected status 
 * flag.
 *
 *END*************************************************************************/
bool AFE_DRV_GetChnFlag(uint32_t instance, uint32_t chn, afe_flag_t flag)
{
    AFE_Type * base = g_afeBase[instance];
    
    bool bRet = false;
    switch (flag)
    {
    case kAfeOverflowFlag:
        bRet = AFE_HAL_GetOverflowFlag(base, chn);
        break;
    case kAfeReadyFlag:
        bRet = AFE_HAL_GetReadyFlag(base, chn);
        break;
    case kAfeConvCompleteFlag:
        bRet = AFE_HAL_GetConvCompleteFlag(base, chn);
        break;
    default:
        break;
    }
    return bRet;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_GetChnConvValRaw
 * Description   : Get the conversion value from the AFE module.
 *
 *END*************************************************************************/
uint32_t AFE_DRV_GetChnConvValRaw(uint32_t instance, uint32_t chn)
{
    AFE_Type * base = g_afeBase[instance];
    uint32_t result = AFE_HAL_GetResult(base, chn);
    
    return result;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_GetConvValue
 * Description   : Get the conversion value from the AFE module in the 
 * 2's complement format.
 *
 *END*************************************************************************/
int32_t AFE_DRV_GetChnConvVal(uint32_t instance, uint32_t chn)
{
    AFE_Type * base = g_afeBase[instance];
    uint32_t result = AFE_HAL_GetResult(base, chn);
    
    if(AFE_HAL_GetResultFormatMode(base) == kAfeResultFormatLeft)
    {   
        result >>= 8U;
        if(result & (1U << AFE_RR_SIGN_BITS_SHIFT))
        {
            result &= ~(1U << AFE_RR_SIGN_BITS_SHIFT); 
            result |=  AFE_RR_SIGN_BITS_MASK;
        }
    }

    return (int32_t)result;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_Deinit
 * Description   : De-initialize the AFE module. It will disable the clock to
 * AFE module. When AFE is no longer used, calling this function will shut down
 * the device to reduce power consumption.
 *
 *END*************************************************************************/
void AFE_DRV_Deinit(uint32_t instance)
{
    AFE_Type * base = g_afeBase[instance];
    AFE_HAL_Init(base);
     
    /* Disable clock for AFE. */
    CLOCK_SYS_DisableAfeClock(instance);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_ChnDeinit
 * Description   : De-initialize the selected AFE channel's configuration 
 * and interrupt.
 *
 *END*************************************************************************/
void AFE_DRV_ChnDeinit(uint32_t instance, uint32_t chn)
{
    AFE_Type * base = g_afeBase[instance];
  
    /* Disable AFE interrupt in NVIC level. */
    INT_SYS_DisableIRQ( g_afeIrqId[chn] );

    AFE_HAL_ChnInit(base, chn);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_Enable
 * Description   : Enable all AFE channels simultaneously whose decimator is enabled.
 *
 *END*************************************************************************/
void AFE_DRV_Enable(uint32_t instance, bool enable)
{
    AFE_Type * base = g_afeBase[instance];
    
    AFE_HAL_SetMasterEnableCmd(base, enable);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_AssertDelayOk
 * Description   : This function should be called after all desired channel's 
 * delay registers are loaded. Vaules in channel's delay registers will be active
 * after calling this function and new conversation starts. 
 *
 *END*************************************************************************/
void AFE_DRV_AssertDelayOk(uint32_t instance)
{
    AFE_Type * base = g_afeBase[instance];
    
    AFE_HAL_SetDelayOkCmd(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : AFE_DRV_SetPhaseDelays
 * Description   : This function sets phase delay adjustement between channels. 
 * This delay is inserted before the trigger response of the decimation filters. 
 * The delay is used to provide a phase compensation between AFE channels in step 
 * of prescaled modulator clock periods. The DelayOk bit is asserted in this 
 * function so the 'AFE_DRV_AssertDelayOk()' function doesn't have to be called. 
 * The delays for each channel are stored in a 'afe_delay_config_t' structure.
 *
 *END*************************************************************************/
void AFE_DRV_SetPhaseDelays(uint32_t instance, afe_delay_config_t * delayConfigPtr){
  
    AFE_Type * base = g_afeBase[instance];

    AFE_HAL_SetDelayVal(base, 0, delayConfigPtr->delayChn0);
    AFE_HAL_SetDelayVal(base, 1, delayConfigPtr->delayChn1);
    AFE_HAL_SetDelayVal(base, 2, delayConfigPtr->delayChn2);
#ifdef FSL_FEATURE_AFE_HAS_FOUR_CHANNELS        
    AFE_HAL_SetDelayVal(base, 3, delayConfigPtr->delayChn3);
#endif //FSL_FEATURE_AFE_HAS_FOUR_CHANNELS   
    AFE_HAL_SetDelayOkCmd(base);
}
#endif

/******************************************************************************
 * EOF
 *****************************************************************************/

