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

#include "fsl_pdb_hal.h"
#if FSL_FEATURE_SOC_PDB_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_Init
 * Description   : Reset PDB's registers to a known state. This state is
 * defined in Reference Manual, which is power on reset value.
 *
 *END*************************************************************************/
void PDB_HAL_Init(PDB_Type * base)
{
    uint32_t chn, preChn;

    /* Note: The setting would take effect only when the PDBEN bit is set. */
    PDB_WR_SC(base, PDB_SC_PDBEN_MASK);

    PDB_WR_MOD(base, 0xFFFFU);
    PDB_WR_IDLY(base, 0xFFFFU);
    /* For ADC trigger. */
    for (chn = 0U; chn < PDB_C1_COUNT; chn++)
    {
        PDB_WR_C1(base, chn, 0U);
        PDB_WR_S(base, chn,0xFU);
        for (preChn = 0U; preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT; preChn++)
        {
            PDB_HAL_SetAdcPreTriggerDelayValue(base, chn, preChn, 0U);
        }
    }

#if FSL_FEATURE_PDB_HAS_DAC
    /* For DAC trigger. */
    for (chn = 0U; chn < PDB_INTC_COUNT; chn++)
    {
        PDB_WR_INTC(base, chn, 0U);
        PDB_WR_INT(base ,chn, 0U);
    }
#endif

    /* For Pulse out trigger. */
    PDB_WR_POEN(base, 0U);
    for (chn = 0U; chn < PDB_PODLY_COUNT; chn++)
    {
        PDB_WR_PODLY(base, chn, 0U);
    }
    /* Load the setting value. */
    PDB_HAL_SetLoadValuesCmd(base);
    PDB_HAL_Disable(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_ConfigTimer
 * Description   : Configure the PDB timer.
 *
 *END*************************************************************************/
pdb_status_t PDB_HAL_ConfigTimer(PDB_Type * base, const pdb_timer_config_t *configPtr)
{
    uint32_t sc;
    
    if (!configPtr)
    {
        return kStatus_PDB_InvalidArgument;
    }
    
    sc = PDB_RD_SC(base);
    sc &= ~(  PDB_SC_LDMOD_MASK
            | PDB_SC_PDBEIE_MASK
            | PDB_SC_PRESCALER_MASK  
            | PDB_SC_TRGSEL_MASK
            | PDB_SC_MULT_MASK
            | PDB_SC_CONT_MASK
            | PDB_SC_DMAEN_MASK
            | PDB_SC_PDBIE_MASK
    );
    
    sc |= PDB_SC_LDMOD((uint32_t)(configPtr->loadValueMode));
    if (configPtr->seqErrIntEnable)
    {
        sc |= PDB_SC_PDBEIE_MASK;
    }
    sc |= PDB_SC_PRESCALER((uint32_t)(configPtr->clkPreDiv));
    sc |= PDB_SC_TRGSEL((uint32_t)(configPtr->triggerInput));
    sc |= PDB_SC_MULT((uint32_t)(configPtr->clkPreMultFactor));
    if (configPtr->continuousModeEnable)
    {
        sc |= PDB_SC_CONT_MASK;
    }
    if (configPtr->dmaEnable)
    {
        sc |= PDB_SC_DMAEN_MASK;
    }
    if (configPtr->intEnable)
    {
        sc |= PDB_SC_PDBIE_MASK;
    }
    PDB_WR_SC(base, sc);
    
    return kStatus_PDB_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetAdcPreTriggerBackToBackEnable
 * Description   : Switch to enable pre-trigger's back to back mode.
 *
 *END*************************************************************************/
void PDB_HAL_SetAdcPreTriggerBackToBackEnable(PDB_Type * base, uint32_t chn, uint32_t preChnMask, bool enable)
{
    assert(chn < PDB_C1_COUNT);
    
    uint32_t c1 = PDB_RD_C1(base, chn);
    if (enable)
    {
        c1 |= PDB_C1_BB(preChnMask);
    }
    else
    {
        c1 &= ~PDB_C1_BB(preChnMask);
    }
    PDB_WR_C1(base, chn, c1);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetAdcPreTriggerOutputEnable
 * Description   : Switch to enable pre-trigger's output.
 *
 *END*************************************************************************/
void PDB_HAL_SetAdcPreTriggerOutputEnable(PDB_Type * base, uint32_t chn, uint32_t preChnMask, bool enable)
{
    assert(chn < PDB_C1_COUNT);
    
    uint32_t c1 = PDB_RD_C1(base, chn);
    if (enable)
    {
        c1 |= PDB_C1_TOS(preChnMask);
    }
    else
    {
        c1 &= ~PDB_C1_TOS(preChnMask);
    }
    PDB_WR_C1(base, chn, c1);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetAdcPreTriggerEnable
 * Description   : Switch to enable pre-trigger's.
 *
 *END*************************************************************************/
void PDB_HAL_SetAdcPreTriggerEnable(PDB_Type * base, uint32_t chn, uint32_t preChnMask, bool enable)
{
    assert(chn < PDB_C1_COUNT);
    
    uint32_t c1 = PDB_RD_C1(base, chn);
    if (enable)
    {
        c1 |= PDB_C1_EN(preChnMask);
    }
    else
    {
        c1 &= ~PDB_C1_EN(preChnMask);
    }
    PDB_WR_C1(base, chn, c1);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_ClearAdcPreTriggerFlags
 * Description   : Clear the flag that the PDB counter reaches to the
 * pre-trigger's delay value.
 *
 *END*************************************************************************/
void PDB_HAL_ClearAdcPreTriggerFlags(PDB_Type * base, uint32_t chn, uint32_t preChnMask)
{
    assert(chn < PDB_S_COUNT);
    
    /* Write 0 to clear. */
    uint32_t s = PDB_RD_S(base, chn); /* Get current value. */
    s &= ~PDB_S_CF( preChnMask ); /* Update the change. */
    
    PDB_WR_S(base, chn, s);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_ClearAdcPreTriggerSeqErrFlags
 * Description   : Clear the flag that sequence error is detected.
 *
 *END*************************************************************************/
void PDB_HAL_ClearAdcPreTriggerSeqErrFlags(PDB_Type * base, uint32_t chn, uint32_t preChnMask)
{
    assert(chn < PDB_S_COUNT);
    
    /* Write 0 to clear. */
    uint32_t s = PDB_RD_S(base, chn); /* Get current value. */
    s &= ~PDB_S_ERR( preChnMask );
    
    PDB_WR_S(base, chn, s);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetAdcPreTriggerDelayValue
 * Description   : Set the delay value for pre-trigger.
 *
 *END*************************************************************************/
void PDB_HAL_SetAdcPreTriggerDelayValue(PDB_Type * base, uint32_t chn, uint32_t preChn, uint32_t value)
{
    assert(chn < PDB_DLY_COUNT);
    assert(preChn < FSL_FEATURE_PDB_ADC_PRE_CHANNEL_COUNT);
    PDB_WR_DLY(base, chn, preChn, value);
}

/*FUNCTION*********************************************************************
 *
 * Function Name : PDB_HAL_SetCmpPulseOutEnable
 * Description   : Switch to enable the pulse-out trigger.
 *
 *END*************************************************************************/
void PDB_HAL_SetCmpPulseOutEnable(PDB_Type * base, uint32_t pulseChnMask, bool enable)
{   
    uint32_t poen = PDB_RD_POEN(base);
    
    if (enable)
    {
        poen |= PDB_POEN_POEN(pulseChnMask);
    }
    else
    {
        poen &= ~PDB_POEN_POEN(pulseChnMask);
    }
    PDB_WR_POEN(base, poen);
}
#endif

/******************************************************************************
 * EOF
 *****************************************************************************/
