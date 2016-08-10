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

#include "fsl_sai_driver.h"
#if FSL_FEATURE_SOC_I2S_COUNT

extern sai_state_t * volatile sai_state_ids[I2S_INSTANCE_COUNT][2];

/*************************************************************************
 * Code
 ************************************************************************/
/* I2S IRQ handler with the same name in startup code */

#if (FSL_FEATURE_SAI_INT_SOURCE_NUM == 1)

void I2S0_IRQHandler(void)
{
    if (sai_state_ids[0][1] != NULL)
    {
        SAI_DRV_RxIRQHandler(0U);
    }
    if (sai_state_ids[0][0] != NULL)
    {
        SAI_DRV_TxIRQHandler(0U);
    }
}

#else
void I2S0_Tx_IRQHandler(void)
{
    SAI_DRV_TxIRQHandler(0U);
}

void I2S0_Rx_IRQHandler(void)
{
    SAI_DRV_RxIRQHandler(0U);
}

#if defined (K70F12_SERIES)
void I2S1_Tx_IRQHandler(void)
{
    SAI_DRV_TxIRQHandler(1U);
}

void I2S1_Rx_IRQHandler(void)
{
    SAI_DRV_RxIRQHandler(1U);
}
#endif /*defined K70F12_SERIES */
#endif /* FSL_FEATURE_SAI_INT_SPURCE_NUM */
#endif

/*************************************************************************
 * EOF
 ************************************************************************/

