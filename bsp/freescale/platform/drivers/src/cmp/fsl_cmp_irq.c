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

#include "fsl_cmp_driver.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_CMP_COUNT

/******************************************************************************
 * IRQ Handlers
 *****************************************************************************/
#if defined (KM34Z7_SERIES)
/* CMP IRQ handler that would cover the same name's APIs in startup code. */
void CMP0_CMP1_CMP2_IRQHandler(void)
{
    for(uint32_t i=0; i < CMP_INSTANCE_COUNT; i++)
    {
        if (CLOCK_SYS_GetCmpGateCmd(i))
        {
            /* Add user-defined ISR for CMP. */

            /* Clear flags. */
            if ( CMP_DRV_GetFlag(i, kCmpFlagOfCoutRising) )
            {
                CMP_DRV_ClearFlag(i, kCmpFlagOfCoutRising);
            }
            if ( CMP_DRV_GetFlag(i, kCmpFlagOfCoutFalling) )
            {
                CMP_DRV_ClearFlag(i, kCmpFlagOfCoutFalling);
            }
        }
    }
}

#else
/* CMP IRQ handler that would cover the same name's APIs in startup code. */
#if CMP_INSTANCE_COUNT > 0
void CMP0_IRQHandler(void)
{
    /* Add user-defined ISR for CMP0. */

    /* Clear flags. */
    if ( CMP_DRV_GetFlag(0U, kCmpFlagOfCoutRising) )
    {
        CMP_DRV_ClearFlag(0U, kCmpFlagOfCoutRising);
    }
    if ( CMP_DRV_GetFlag(0U, kCmpFlagOfCoutFalling) )
    {
        CMP_DRV_ClearFlag(0U, kCmpFlagOfCoutFalling);
    }
}
#endif /* CMP_INSTANCE_COUNT > 0 */

#if CMP_INSTANCE_COUNT > 1
void CMP1_IRQHandler(void)
{
    /* Add user-defined ISR for CMP1. */

    /* Clear flags. */
    if ( CMP_DRV_GetFlag(1U, kCmpFlagOfCoutRising) )
    {
        CMP_DRV_ClearFlag(1U, kCmpFlagOfCoutRising);
    }
    if ( CMP_DRV_GetFlag(1U, kCmpFlagOfCoutFalling) )
    {
        CMP_DRV_ClearFlag(1U, kCmpFlagOfCoutFalling);
    }
}
#endif /* CMP_INSTANCE_COUNT > 1 */

#if CMP_INSTANCE_COUNT > 2
void CMP2_IRQHandler(void)
{
    /* Add user-defined ISR for CMP2. */

    /* Clear flags. */
    if ( CMP_DRV_GetFlag(2U, kCmpFlagOfCoutRising) )
    {
        CMP_DRV_ClearFlag(2U, kCmpFlagOfCoutRising);
    }
    if ( CMP_DRV_GetFlag(2U, kCmpFlagOfCoutFalling) )
    {
        CMP_DRV_ClearFlag(2U, kCmpFlagOfCoutFalling);
    }
}
#endif /* CMP_INSTANCE_COUNT > 2 */
#endif /* defined (KM34Z7_SERIES) */
#endif /* FSL_FEATURE_SOC_CMP_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/
 
