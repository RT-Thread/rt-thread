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

#include "fsl_device_registers.h"

/*******************************************************************************
 * Variables 
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void LPUART_DRV_IRQHandler(uint32_t instance);

/*******************************************************************************
 * Code
 ******************************************************************************/

#if (LPUART_INSTANCE_COUNT > 0)
/* Implementation of LPUART0 handler named in startup code. */
void LPUART0_IRQHandler(void)
{
    LPUART_DRV_IRQHandler(0);
}
#endif

#if (LPUART_INSTANCE_COUNT > 1)
/* Implementation of LPUART1 handler named in startup code. */
void LPUART1_IRQHandler(void)
{
    LPUART_DRV_IRQHandler(1);
}
#endif

#if (LPUART_INSTANCE_COUNT > 2)
/* Implementation of LPUART1 handler named in startup code. */
void LPUART2_IRQHandler(void)
{
    LPUART_DRV_IRQHandler(2);
}
#endif

#if (LPUART_INSTANCE_COUNT > 3)
/* Implementation of LPUART1 handler named in startup code. */
void LPUART3_IRQHandler(void)
{
    LPUART_DRV_IRQHandler(3);
}
#endif

#if (LPUART_INSTANCE_COUNT > 4)
/* Implementation of LPUART1 handler named in startup code. */
void LPUART4_IRQHandler(void)
{
    LPUART_DRV_IRQHandler(4);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
