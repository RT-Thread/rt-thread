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

#include "fsl_cadc_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_CADC_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_StructInitUserConfigDefault
 * Description   : Help user to fill the cadc_user_config_t structure with
 * default setting, which can be used in polling mode for ADC conversion.
 *
 *END**************************************************************************/
cadc_status_t CADC_DRV_StructInitUserConfigDefault(cadc_controller_config_t *userConfigPtr)
{
    if (!userConfigPtr)
    {
        return kStatus_CADC_InvalidArgument;
    }
    userConfigPtr->zeroCrossingIntEnable = false;
    userConfigPtr->lowLimitIntEnable = false;
    userConfigPtr->highLimitIntEnable = false;
    userConfigPtr->scanMode = kCAdcScanOnceSequential;
    userConfigPtr->parallelSimultModeEnable = false;
    userConfigPtr->dmaSrc = kCAdcDmaTriggeredByEndOfScan;
    userConfigPtr->autoStandbyEnable = false;
    userConfigPtr->powerUpDelayCount = 0x2AU;
    userConfigPtr->autoPowerDownEnable = false;

    return kStatus_CADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_Init
 * Description   : Configure the CyclicADC module for the global configuraion
 * which are shared by all the converter.
 *
 *END**************************************************************************/
cadc_status_t CADC_DRV_Init(uint32_t instance, const cadc_controller_config_t *userConfigPtr)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    if (!userConfigPtr)
    {
        return kStatus_CADC_InvalidArgument;
    }
    /* Ungate the clock for the ADC module. */
    CLOCK_SYS_EnableAdcClock(instance);

    /* Configure the common setting for ADC module. */
    CADC_HAL_Init(base);

    CADC_HAL_ConfigController(base, userConfigPtr);

    INT_SYS_EnableIRQ(g_cadcErrIrqId[instance]);
    INT_SYS_EnableIRQ(g_cadcConvAIrqId[instance]);
    INT_SYS_EnableIRQ(g_cadcConvBIrqId[instance]);
    return kStatus_CADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_Deinit
 * Description   : Deinit the CADC module. This function would disable all the
 * interrupts and clock.
 *
 *END**************************************************************************/
cadc_status_t CADC_DRV_Deinit(uint32_t instance)
{
    INT_SYS_DisableIRQ(g_cadcErrIrqId[instance]);
    INT_SYS_DisableIRQ(g_cadcConvAIrqId[instance]);
    INT_SYS_DisableIRQ(g_cadcConvBIrqId[instance]);

    /* Gate the access to ADC module. */
    CLOCK_SYS_DisableAdcClock(instance); 

    return kStatus_CADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_StructInitConvConfigDefault
 * Description   : Configure each converter in CyclicADC module. However, when
 * the multiple converter are co-working, the setting for converters would
 * be related with each other. For detailed information, please see to SOC's
 * Reference Manual document.
 *
 *END**************************************************************************/
cadc_status_t CADC_DRV_StructInitConvConfigDefault(cadc_converter_config_t *configPtr)
{
    if (!configPtr)
    {
        return kStatus_CADC_InvalidArgument;
    }

    configPtr->dmaEnable = false;
    configPtr->stopEnable = false; /* Release the converter. */
    configPtr->syncEnable = false; /* No hardware trigger. */

    configPtr->endOfScanIntEnable = false;
    configPtr->clkDivValue = 0x3FU;
    configPtr->useChnInputAsVrefH = false;
    configPtr->useChnInputAsVrefL = false;
    configPtr->speedMode = kCAdcConvClkLimitBy25MHz;
    configPtr->sampleWindowCount = 0U;

    return kStatus_CADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_ConfigConverter
 * Description   : Configure each converter in CyclicADC module. However, when
 * the multiple converter are co-working, the setting for converters would
 * be related with each other. For detailed information, please see to SOC's
 * Reference Manual document.
 *
 *END**************************************************************************/
cadc_status_t CADC_DRV_ConfigConverter(uint32_t instance, cadc_conv_id_t convId,
    const cadc_converter_config_t *configPtr)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    if (!configPtr)
    {
        return kStatus_CADC_InvalidArgument;
    }

    /* Configure the ADC converter. */
    switch (convId)
    {
        case kCAdcConvA:
            CADC_HAL_ConfigConvA(base, configPtr);
            CADC_HAL_SetConvAPowerDownCmd(base, false);
            break;
        case kCAdcConvB:
            CADC_HAL_ConfigConvB(base, configPtr);
            CADC_HAL_SetConvBPowerDownCmd(base, false);
            break;
        default:
            break;
    }

    return kStatus_CADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_ConfigSampleChn
 * Description   : Configure input channel for ADC conversion. The CyclicADC
 * module's input channels are gathered in pairs. Here the configuration can
 * be set for each of channel in the pair.
 *
 *END**************************************************************************/
cadc_status_t CADC_DRV_ConfigSampleChn(uint32_t instance, const cadc_chn_config_t *configPtr)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    if (!configPtr)
    {
        return kStatus_CADC_InvalidArgument;
    }

    CADC_HAL_ConfigChn(base, configPtr);

    return kStatus_CADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_ConfigSeqSlot
 * Description   : Configure each slot in ADC conversion sequence. ADC conversion
 * sequence is the basic execution unit in this CyclicADC module. However, the
 * sequence should be configured slot by slot. The end of the sequence is a
 * slot that is configured as disable.
 *
 *END**************************************************************************/
cadc_status_t CADC_DRV_ConfigSeqSlot(uint32_t instance, uint32_t slotIdx,
    const cadc_slot_config_t *configPtr)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    if (!configPtr)
    {
        return kStatus_CADC_InvalidArgument;
    }

    CADC_HAL_ConfigSeqSlot(base, slotIdx, configPtr);

    return kStatus_CADC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_SoftTriggerConv
 * Description   : trigger the ADC conversion by executing software command. It
 * will start the conversion if no other SYNC input (hardware trigger) is needed.
 *
 *END**************************************************************************/
void CADC_DRV_SoftTriggerConv(uint32_t instance, cadc_conv_id_t convId)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    switch (convId)
    {
    case kCAdcConvA:
        CADC_HAL_SetConvAStartCmd(base);
        break;
    case kCAdcConvB:
        CADC_HAL_SetConvBStartCmd(base);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_GetSeqSlotConvValue
 * Description   : Read the conversion value from each slot in conversion sequence.
 *
 *END**************************************************************************/
uint16_t CADC_DRV_GetSeqSlotConvValue(uint32_t instance, uint32_t slotIdx)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    return CADC_HAL_GetSampleValue(base, slotIdx);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_GetFlag
 * Description   : Help to get the global flag of CyclicADC module.
 *
 *END**************************************************************************/
bool CADC_DRV_GetFlag(uint32_t instance, cadc_flag_t flag)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];
    bool bRet = false;

    switch(flag)
    {
    case kCAdcZeroCrossingInt:
        bRet = CADC_HAL_GetZeroCrossingIntFlag(base);
        break;
    case kCAdcLowLimitInt:
        bRet = CADC_HAL_GetLowLimitIntFlag(base);
        break;
    case kCAdcHighLimitInt:
        bRet = CADC_HAL_GetHighLimitIntFlag(base);
        break;
    default:
        break;
    }
    return bRet;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_ClearFlag
 * Description   : Clear the global flag of CyclicADC module.
 *
 *END**************************************************************************/
void CADC_DRV_ClearFlag(uint32_t instance, cadc_flag_t flag)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    switch(flag)
    {
    case kCAdcZeroCrossingInt:
        CADC_HAL_ClearSlotZeroCrossingFlag(base, 0xFFFF);
        break;
    case kCAdcLowLimitInt:
        CADC_HAL_ClearSlotLowLimitFlag(base, 0xFFFF);
        break;
    case kCAdcHighLimitInt:
        CADC_HAL_ClearSlotHighLimitFlag(base, 0xFFFF);
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_GetConvFlag
 * Description   : Help to get the flag of each converter's event.
 *
 *END**************************************************************************/
bool CADC_DRV_GetConvFlag(uint32_t instance, cadc_conv_id_t convId, cadc_flag_t flag)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];
    bool bRet = false;

    switch (flag)
    {
    case kCAdcConvInProgress:
        switch (convId)
        {
        case kCAdcConvA:
            bRet = CADC_HAL_GetConvAInProgressFlag(base);
            break;
        case kCAdcConvB:
            bRet = CADC_HAL_GetConvBInProgressFlag(base);
            break;
        default:
            break;
        }
        break;
    case kCAdcConvEndOfScanInt:
        switch (convId)
        {
        case kCAdcConvA:
            bRet = CADC_HAL_GetConvAEndOfScanIntFlag(base);
            break;
        case kCAdcConvB:
            bRet = CADC_HAL_GetConvBEndOfScanIntFlag(base);
            break;
        default:
            break;
        }
        break;
    case kCAdcConvPowerDown:
        switch (convId)
        {
        case kCAdcConvA:
            bRet = CADC_HAL_GetConvAPowerDownFlag(base);
            break;
        case kCAdcConvB:
            bRet = CADC_HAL_GetConvBPowerDownFlag(base);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return bRet;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_ClearConvFlag
 * Description   : help to clear the flag of each converter's event.
 *
 *END**************************************************************************/
void CADC_DRV_ClearConvFlag(uint32_t instance, cadc_conv_id_t convId, cadc_flag_t flag)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    switch (flag)
    {
    case kCAdcConvEndOfScanInt:
        switch (convId)
        {
        case kCAdcConvA:
            CADC_HAL_ClearConvAEndOfScanIntFlag(base);
            break;
        case kCAdcConvB:
            CADC_HAL_ClearConvBEndOfScanIntFlag(base);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_GetSlotFlag
 * Description   : Help to get the flag of each slot's event in conversion in
 * sequence.
 *
 *END**************************************************************************/
uint16_t CADC_DRV_GetSlotFlag(uint32_t instance, uint16_t slotIdxMask, cadc_flag_t flag)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    uint16_t mskRet = 0U;
    switch (flag)
    {
    case kCAdcSlotReady:
        mskRet = CADC_HAL_GetSlotReadyFlag(base, slotIdxMask);
        break;
    case kCAdcSlotLowLimitEvent:
        mskRet = CADC_HAL_GetSlotLowLimitFlag(base, slotIdxMask);
        break;
    case kCAdcSlotHighLimitEvent:
        mskRet = CADC_HAL_GetSlotHighLimitFlag(base, slotIdxMask);
        break;
    case kCAdcSlotCrossingEvent:
        mskRet = CADC_HAL_GetSlotZeroCrossingFlag(base, slotIdxMask);
        break;
    default:
        break;
    }
    return mskRet;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CADC_DRV_ClearSlotFlag
 * Description   : Help to clear the flag of each slot's event in conversion in
 * sequence.
 *
 *END**************************************************************************/
void CADC_DRV_ClearSlotFlag(uint32_t instance, uint16_t slotIdxMask, cadc_flag_t flag)
{
    assert(instance < ADC_INSTANCE_COUNT);
    ADC_Type * base = g_cadcBaseAddr[instance];

    switch (flag)
    {
    case kCAdcSlotLowLimitEvent:
        CADC_HAL_ClearSlotLowLimitFlag(base, slotIdxMask);
        break;
    case kCAdcSlotHighLimitEvent:
        CADC_HAL_ClearSlotHighLimitFlag(base, slotIdxMask);
        break;
    case kCAdcSlotCrossingEvent:
        CADC_HAL_ClearSlotZeroCrossingFlag(base, slotIdxMask);
        break;
    default:
        break;
    }
}
#endif

/******************************************************************************
 * EOF
 *****************************************************************************/

