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

#include "fsl_dac_hal.h"

#if FSL_FEATURE_SOC_DAC_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_HAL_Init
 * Description   : Reset all the configurable registers to be reset state for DAC.
 * It should be called before configuring the DAC module.
 *
 *END*************************************************************************/
void DAC_HAL_Init(DAC_Type * base)
{
    uint8_t i;
    /* DACx_DATL and DACx_DATH */
    for (i = 0U; i < DAC_DATL_COUNT; i++)
    {
        DAC_WR_DATL(base, i, 0U); DAC_WR_DATH(base, i, 0U);
    }
    /* DACx_SR. */
    DAC_WR_SR(base, 0U); /* Clear all flags. */
    /* DACx_C0. */
    DAC_WR_C0(base, 0U);
    /* DACx_C1. */
    DAC_WR_C1(base, 0U);
    /* DACx_C2. */
    DAC_WR_C2(base, DAC_DATL_COUNT-1U);
}

/*--------------------------------------------------------------------------*
* DAC converter.
*--------------------------------------------------------------------------*/
/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_HAL_ConfigConverter
 * Description   : Configures the converter for DAC. The feaatures it covers are
 * one-time setting in application. 
 *
 *END*************************************************************************/
void DAC_HAL_ConfigConverter(DAC_Type * base, const dac_converter_config_t *configPtr)
{
    uint8_t c0;
    
    c0 = DAC_RD_C0(base);
    c0 &= ~(  DAC_C0_DACRFS_MASK
            | DAC_C0_LPEN_MASK  );
    if (kDacRefVoltSrcOfVref2 == configPtr->dacRefVoltSrc)
    {
        c0 |= DAC_C0_DACRFS_MASK;
    }
    if (configPtr->lowPowerEnable)
    {
        c0 |= DAC_C0_LPEN_MASK;
    }
    
    DAC_WR_C0(base, c0);
}
    
/*--------------------------------------------------------------------------*
* DAC buffer.
*--------------------------------------------------------------------------*/
/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_HAL_ConfigBuffer
 * Description   : Configures the converter for DAC. The feaatures it covers are
 * mainly about the buffer. 
 *
 *END*************************************************************************/
void DAC_HAL_ConfigBuffer(DAC_Type * base, const dac_buffer_config_t *configPtr)
{
    uint8_t c0, c1;

    c0 = DAC_RD_C0(base);
    c0 &= ~(  DAC_C0_DACTRGSEL_MASK
            | DAC_C0_DACBBIEN_MASK
            | DAC_C0_DACBTIEN_MASK
#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
            | DAC_C0_DACBWIEN_MASK
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    );
    
    if (kDacTriggerBySoftware == configPtr->triggerMode)
    {
        c0 |= DAC_C0_DACTRGSEL_MASK;
    }
    
    /* Enable interrupts. */
    if (configPtr->idxStartIntEnable)
    {
        c0 |= DAC_C0_DACBTIEN_MASK;
    }
    if (configPtr->idxUpperIntEnable)
    {
        c0 |= DAC_C0_DACBBIEN_MASK;
    }
#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    if (configPtr->idxWatermarkIntEnable)
    {
        c0 |= DAC_C0_DACBWIEN_MASK;
    }
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    
    c1 = DAC_RD_C0(base);
    c1 &= ~(  DAC_C1_DMAEN_MASK
#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
            | DAC_C1_DACBFWM_MASK
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
            | DAC_C1_DACBFMD_MASK
            | DAC_C1_DACBFEN_MASK
    );
    if (configPtr->dmaEnable)
    {
        c1 |= DAC_C1_DMAEN_MASK;
    }

#if FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    c1 |= DAC_C1_DACBFWM((uint8_t)(configPtr->watermarkMode));
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION */
    
    c1 |= DAC_C1_DACBFMD((uint8_t)(configPtr->buffWorkMode));
    if (configPtr->bufferEnable)
    {
        c1 |= DAC_C1_DACBFEN_MASK;
    }
    
    DAC_WR_C0(base, c0);
    DAC_WR_C1(base, c1);
    DAC_BWR_C2_DACBFUP(base, configPtr->upperIdx);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : DAC_HAL_SetBuffValue
 * Description   : Set the value assembled by the low 8 bits and high 4
 * bits of 12-bit DAC item in buffer.
 *
 *END*************************************************************************/
void DAC_HAL_SetBuffValue(DAC_Type * base, uint8_t idx, uint16_t value)
{
    assert(idx < DAC_DATL_COUNT);
    DAC_WR_DATL(base, idx, (uint8_t)(0xFFU & value) );
    DAC_BWR_DATH_DATA1(base, idx, (uint8_t)((0xF00U & value)>>8U) );
}

/******************************************************************************
 * EOF
 *****************************************************************************/


#endif
