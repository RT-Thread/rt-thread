/*
 * The Clear BSD License
 * Copyright 2018 NXP
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
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
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "fsl_swo.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* SWO encoding protocol definition */
#ifndef FSL_DEBUG_CONSOLE_SWO_PROTOCOL
#define FSL_DEBUG_CONSOLE_SWO_PROTOCOL kSWO_ProtocolNrz
#endif
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t SWO_Init(uint32_t port, uint32_t baudRate, uint32_t clkSrcFreq)
{
    assert(baudRate <= clkSrcFreq);
    assert((clkSrcFreq / baudRate) <= TPI_ACPR_PRESCALER_Msk);
    assert((TPI->DEVID & (kSWO_ProtocolNrz | kSWO_ProtocolManchester)) != 0U);

    uint32_t prescaler = clkSrcFreq / baudRate - 1U;

    /* enable the ITM and DWT units */
    CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk;

    if ((CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk) == 0U)
    {
        return kStatus_Fail;
    }
    /* Lock access */
    ITM->LAR = 0xC5ACCE55U;
    /* Disable ITM */
    ITM->TER &= ~(1U << port);
    ITM->TCR = 0U;
    /* select SWO encoding protocol */
    TPI->SPPR = FSL_DEBUG_CONSOLE_SWO_PROTOCOL;
    /* select asynchronous clock prescaler */
    TPI->ACPR = prescaler & 0xFFFFU;
    /* allow unprivilege access */
    ITM->TPR = 0U;
    /* enable ITM */
    ITM->TCR =
        ITM_TCR_ITMENA_Msk | ITM_TCR_SYNCENA_Msk | ITM_TCR_TraceBusID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_DWTENA_Msk;
    /* enable the port bits */
    ITM->TER = 1U << port;

    return kStatus_Success;
}

void SWO_Deinit(uint32_t port)
{
    /* disable ITM */
    ITM->TER &= ~(1U << port);
}

status_t SWO_SendBlocking(uint32_t port, uint8_t *ch, size_t size)
{
    assert(ch != NULL);
    assert((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0U);
    assert((ITM->TER & (1U << port)) != 0U);

    uint16_t *strAddr = (uint16_t *)ch;

    while (size)
    {
        /* wait FIFO ready */
        while (ITM->PORT[port].u32 == 0U)
        {
        }

        if (size >= 2U)
        {
            size -= 2U;
            ITM->PORT[port].u16 = *strAddr;
        }
        else
        {
            size -= 1U;
            ITM->PORT[port].u8 = *((uint8_t *)strAddr);
        }
        strAddr++;
    }

    return kStatus_Success;
}
