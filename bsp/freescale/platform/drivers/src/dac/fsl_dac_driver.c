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
#include "fsl_dac_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_DAC_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_StructInitUserConfigNormal
 * Description   : Fill the initial user configuration for DAC module 
 * without the feature of interrupt and buffer. Then call initialization
 * function with the filled parameter would configure
 * the DAC module work as a common and simple converter.
 *
 *END*************************************************************************/
dac_status_t DAC_DRV_StructInitUserConfigNormal(dac_converter_config_t *userConfigPtr)
{
    if (!userConfigPtr)
    {
        return kStatus_DAC_InvalidArgument;
    }
    userConfigPtr->dacRefVoltSrc = kDacRefVoltSrcOfVref2; /* Vdda */
    userConfigPtr->lowPowerEnable = false;
    return kStatus_DAC_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_Init
 * Description   : Initialize the converter in DAC module. It will just
 * configure the DAC converter itself but not including advanced features like
 * interrupt and internal buffer. This API should be called before any
 * operation to DAC module. After initialized, the DAC module can work at 
 * least as a common simple DAC converter.
 *
 *END*************************************************************************/
dac_status_t DAC_DRV_Init(uint32_t instance, const dac_converter_config_t *userConfigPtr)
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];

    CLOCK_SYS_EnableDacClock(instance);

    /* Reset the registers for DAC module to reset state. */
    DAC_HAL_Init(base);
    DAC_HAL_Enable(base);
    DAC_HAL_ConfigConverter(base, userConfigPtr);

    /* Enable DAC interrupt in NVIC level.*/
    INT_SYS_EnableIRQ(g_dacIrqId[instance] );

    return kStatus_DAC_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_Deinit
 * Description   : De-initialize the converter in DAC module. It will disable
 * DAC module and shut down its clock to reduce the power consumption.
 *
 *END*************************************************************************/
dac_status_t DAC_DRV_Deinit(uint32_t instance)
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];

    INT_SYS_DisableIRQ(g_dacIrqId[instance] );
    DAC_HAL_Disable(base);
    DAC_HAL_Init(base);
    CLOCK_SYS_DisableDacClock(instance);

    return kStatus_DAC_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_Output
 * Description   : Drive the converter to output DAC value. It will force
 * the buffer index to be the first one, load the setting value to this item. 
 * Then the converter will output the voltage indicated by the indicated value
 * immediately. 
 *
 *END*************************************************************************/
void DAC_DRV_Output(uint32_t instance, uint16_t value)
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];

    DAC_HAL_SetBuffValue(base, 0U, value);
    DAC_HAL_SetBuffCurIdx(base, 0U);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_ConfigBuffer
 * Description   : Configure the feature of internal buffer for DAC module.
 * By default, the feature of buffer is disabled. Calling this API will enable
 * the buffer and configure it.
 *
 *END*************************************************************************/
dac_status_t DAC_DRV_ConfigBuffer(uint32_t instance, const dac_buffer_config_t *configPtr)
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];

    if (!configPtr)
    {
        return kStatus_DAC_InvalidArgument;
    }
    DAC_HAL_ConfigBuffer(base, configPtr);

    return kStatus_DAC_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_SetBuffValue
 * Description   : Set values into DAC's internal buffer. Note the buffer
 * size is defined by MACRO "FSL_FEATURE_DAC_BUFFER_SIZE" and the available
 * value is 12-bit.
 *
 *END*************************************************************************/
dac_status_t DAC_DRV_SetBuffValue(uint32_t instance, uint8_t start, uint8_t offset, uint16_t arr[])
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];

    uint8_t i;

    if (  (!arr) || (start + offset > DAC_DATL_COUNT) )
    {
        return kStatus_DAC_InvalidArgument;
    }

    for (i = 0; i < offset; i++)
    {
        DAC_HAL_SetBuffValue(base, start+i, arr[i]);
    }

    return kStatus_DAC_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_SoftTriggerBuffCmd
 * Description   : Trigger the buffer by software and return the current
 * value. After triggered, the buffer index will update according to work mode.
 * Then the value kept inside the pointed item will be output immediately.
 *
 *END*************************************************************************/
void DAC_DRV_SoftTriggerBuffCmd(uint32_t instance)
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];

    DAC_HAL_SetSoftTriggerCmd(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_SetBuffCurIdx
 * Description   : Set the current read pointer in DAC buffer.
 *
 *END*************************************************************************/
void DAC_DRV_SetBuffCurIdx(uint32_t instance, uint8_t idx)
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];

    DAC_HAL_SetBuffCurIdx(base, idx);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_GetBuffCurIdx
 * Description   : Get the current read pointer in DAC buffer.
 *
 *END*************************************************************************/
uint8_t DAC_DRV_GetBuffCurIdx(uint32_t instance)
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];
    
    return DAC_HAL_GetBuffCurIdx(base);

}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_ClearBuffFlag
 * Description   : Clear the flag for indicated event causing interrupt.
 *
 *END*************************************************************************/
void DAC_DRV_ClearBuffFlag(uint32_t instance, dac_flag_t flag)
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];

    switch (flag)
    {
    case kDacBuffIndexStartFlag:
        DAC_HAL_ClearBuffIdxStartFlag(base);
        break;
#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    case kDacBuffIndexWatermarkFlag:
        DAC_HAL_ClearBuffIdxWatermarkFlag(base);
        break;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    case kDacBuffIndexUpperFlag:
        DAC_HAL_ClearBuffIdxUpperFlag(base);
        break;
    default:
        DAC_HAL_ClearBuffIdxStartFlag(base);
#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
        DAC_HAL_ClearBuffIdxWatermarkFlag(base);
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
        DAC_HAL_ClearBuffIdxUpperFlag(base);
        break;
    }
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_DRV_GetBuffFlag
 * Description   : Get the flag for indicated event causing interrupt.
 * If the event occurs, the return value will be asserted.
 *
 *END*************************************************************************/
bool DAC_DRV_GetBuffFlag(uint32_t instance, dac_flag_t flag)
{
    assert(instance < DAC_INSTANCE_COUNT);
    DAC_Type * base = g_dacBase[instance];
    bool bRet = true;

    switch (flag)
    {
    case kDacBuffIndexStartFlag:
        bRet = DAC_HAL_GetBuffIdxStartFlag(base);
        break;
#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    case kDacBuffIndexWatermarkFlag:
        bRet = DAC_HAL_GetBuffIdxWatermarkFlag(base);
        break;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    case kDacBuffIndexUpperFlag:
        bRet = DAC_HAL_GetBuffIdxUpperFlag(base);
        break;
    default:
        bRet = false;
        break;
    }
    return bRet;
}

/******************************************************************************
 * EOF
 *****************************************************************************/

#endif
