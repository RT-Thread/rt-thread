/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
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

#include "fsl_flexio_hal.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_HAL_SetTimerStatusIntCmd
 * Description: Enable/disable timer status interrupt
 *
 *END*********************************************************************/
void FLEXIO_HAL_SetTimerStatusIntCmd(FLEXIO_Type * base, uint32_t mask, bool enable)
{
    uint32_t teie = FLEXIO_BRD_TIMIEN_TEIE(base);
    if (enable)
    {
        teie |= mask;
    }
    else
    {
        teie &= ~mask;
    }
    FLEXIO_BWR_TIMIEN_TEIE(base, teie);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_HAL_ConfigureTimer
 * Description: Configure timer related registers: ctl, cfg, cmp
 *
 *END*********************************************************************/
void FLEXIO_HAL_ConfigureTimer(FLEXIO_Type * base, uint32_t timerIdx, const flexio_timer_config_t *timerConfigPtr)
{
    uint32_t cfg = 0U, ctl = 0U, cmp = 0U;

    ctl  = FLEXIO_TIMCTL_TRGSEL(timerConfigPtr->trgsel)
         | FLEXIO_TIMCTL_TRGPOL(timerConfigPtr->trgpol)
         | FLEXIO_TIMCTL_TRGSRC(timerConfigPtr->trgsrc)
         | FLEXIO_TIMCTL_PINCFG(timerConfigPtr->pincfg)
         | FLEXIO_TIMCTL_PINSEL(timerConfigPtr->pinsel)
         | FLEXIO_TIMCTL_PINPOL(timerConfigPtr->pinpol)
         | FLEXIO_TIMCTL_TIMOD(timerConfigPtr->timod);

    cfg = FLEXIO_TIMCFG_TIMOUT(timerConfigPtr->timout)
        | FLEXIO_TIMCFG_TIMDEC(timerConfigPtr->timdec)
        | FLEXIO_TIMCFG_TIMRST(timerConfigPtr->timrst)
        | FLEXIO_TIMCFG_TIMDIS(timerConfigPtr->timdis)
        | FLEXIO_TIMCFG_TIMENA(timerConfigPtr->timena)
        | FLEXIO_TIMCFG_TSTOP(timerConfigPtr->tstop)
        | FLEXIO_TIMCFG_TSTART(timerConfigPtr->tstart);

    cmp = FLEXIO_TIMCMP_CMP(timerConfigPtr->timcmp);

    FLEXIO_WR_TIMCFG(base, timerIdx, cfg);
    FLEXIO_WR_TIMCMP(base, timerIdx, cmp);
    FLEXIO_WR_TIMCTL(base, timerIdx, ctl);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_HAL_ConfigureShifter
 * Description: Configure shifter related registers: ctl, cfg
 *
 *END*********************************************************************/
void FLEXIO_HAL_ConfigureShifter(FLEXIO_Type * base, uint32_t shifterIdx, const flexio_shifter_config_t *shifterConfigPtr)
{
    uint32_t cfg = 0U, ctl = 0U;

    ctl = FLEXIO_SHIFTCTL_TIMSEL(shifterConfigPtr->timsel)
        | FLEXIO_SHIFTCTL_TIMPOL(shifterConfigPtr->timpol)
        | FLEXIO_SHIFTCTL_PINCFG(shifterConfigPtr->pincfg)
        | FLEXIO_SHIFTCTL_PINSEL(shifterConfigPtr->pinsel)
        | FLEXIO_SHIFTCTL_PINPOL(shifterConfigPtr->pinpol)
        | FLEXIO_SHIFTCTL_SMOD(shifterConfigPtr->smode);

    cfg = FLEXIO_SHIFTCFG_INSRC(shifterConfigPtr->insrc)
        | FLEXIO_SHIFTCFG_SSTOP(shifterConfigPtr->sstop)
        | FLEXIO_SHIFTCFG_SSTART(shifterConfigPtr->sstart)
#if FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH
        | FLEXIO_SHIFTCFG_PWIDTH(shifterConfigPtr->pwidth)
#endif /* FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH */
        ;

    FLEXIO_WR_SHIFTCFG(base, shifterIdx, cfg);
    FLEXIO_WR_SHIFTCTL(base, shifterIdx, ctl);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_HAL_SetShifterStatusIntCmd
 * Description: Enable/disable shifter status interrupt
 *
 *END*********************************************************************/
void FLEXIO_HAL_SetShifterStatusIntCmd(FLEXIO_Type * base, uint32_t mask, bool enable)
{
    uint32_t ssie = FLEXIO_BRD_SHIFTSIEN_SSIE(base);
    if (enable)
    {
        ssie |= mask;
    }
    else
    {
        ssie &= ~mask;
    }
    FLEXIO_BWR_SHIFTSIEN_SSIE(base, ssie);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_HAL_SetShifterErrorIntCmd
 * Description: Enable/disable shifter error interrupt
 *
 *END*********************************************************************/
void FLEXIO_HAL_SetShifterErrorIntCmd(FLEXIO_Type * base, uint32_t mask, bool enable)
{
    uint32_t seie = FLEXIO_BRD_SHIFTEIEN_SEIE(base);
    if (enable)
    {
        seie |= mask;
    }
    else
    {
        seie &= ~mask;
    }
    FLEXIO_BWR_SHIFTEIEN_SEIE(base, seie);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_HAL_SetShifterStatusDmaCmd
 * Description: Enable/disable shifter DMA transfer signalling
 *
 *END*********************************************************************/
void FLEXIO_HAL_SetShifterStatusDmaCmd(FLEXIO_Type * base, uint32_t mask, bool enable)
{
    uint32_t ssde = FLEXIO_BRD_SHIFTSDEN_SSDE(base);
    if (enable)
    {
        ssde |= mask;
    }
    else
    {
        ssde &= ~mask;
    }
    FLEXIO_BWR_SHIFTSDEN_SSDE(base, ssde);
}

/*FUNCTION****************************************************************
 *
 * Function Name: FLEXIO_HAL_Init
 * Description: Reset the registers of flexio module.
 *
 *END*********************************************************************/
void FLEXIO_HAL_Init(FLEXIO_Type * base)
{
    uint32_t maxShifterCounter, maxTimerCounter /*, maxPinCounter*/;

    FLEXIO_HAL_SetSoftwareResetCmd(base, true);
    maxShifterCounter = FLEXIO_HAL_GetShifterNumber(base);
    maxTimerCounter = FLEXIO_HAL_GetTimerNumber(base);
    FLEXIO_HAL_SetSoftwareResetCmd(base, false);

    FLEXIO_HAL_ClearShifterStatusFlags(base, (1U << maxShifterCounter) - 1U);
    FLEXIO_HAL_ClearShifterErrorFlags(base, (1U << maxShifterCounter) - 1U);
    FLEXIO_HAL_ClearTimerStatusFlags(base, (1U << maxTimerCounter) - 1U);
}
#endif

/******************************************************************************
 * EOF
 *****************************************************************************/

