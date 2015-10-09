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

#include "fsl_pdb_driver.h"
#if FSL_FEATURE_SOC_PDB_COUNT

/******************************************************************************
 * IRQ Handlers
 *****************************************************************************/
/* PDB IRQ handler that would cover the same name's APIs in startup code. */
#if FSL_FEATURE_PDB_HAS_SHARED_IRQ_HANDLER
#include "fsl_clock_manager.h"

void PDB0_PDB1_IRQHandler(void)
{
    if (CLOCK_SYS_GetPdbGateCmd(0U))
    {
      if ( PDB_DRV_GetTimerIntFlag(0U))
      {
        /* Add user-defined ISR for PDB0. */

        /* Clear Flag */
        PDB_DRV_ClearTimerIntFlag(0U);
      }
    }
    if (CLOCK_SYS_GetPdbGateCmd(1U))
    {
      if ( PDB_DRV_GetTimerIntFlag(1U))
      {
        /* Add user-defined ISR for PDB1. */
      
        /* Clear Flag */
         PDB_DRV_ClearTimerIntFlag(1U);
      }
    }
}
#else
void PDB0_IRQHandler(void)
{
    /* Add user-defined ISR for PDB0. */

    /* Clear Flags. */
    if ( PDB_DRV_GetTimerIntFlag(0U))
    {
        PDB_DRV_ClearTimerIntFlag(0U);
    }
}

#if (PDB_INSTANCE_COUNT > 1)
void PDB1_IRQHandler(void)
{
    /* Add user-defined ISR for PDB1. */

    /* Clear Flags. */
    if ( PDB_DRV_GetTimerIntFlag(1U))
    {
        PDB_DRV_ClearTimerIntFlag(1U);
    }
}
#endif
#endif /* FSL_FEATURE_PDB_HAS_SHARED_IRQ_HANDLER */
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
