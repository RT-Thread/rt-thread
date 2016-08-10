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

#include "fsl_uart_driver.h"
#include "fsl_clock_manager.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void UART_DRV_IRQHandler(uint32_t instance);
/*******************************************************************************
 * Code
 ******************************************************************************/

#if defined (KL16Z4_SERIES) || defined (KL25Z4_SERIES) || defined (KL26Z4_SERIES) || \
    defined (KL46Z4_SERIES) || defined (KV10Z7_SERIES) || defined (KW01Z4_SERIES) || \
    defined(KV10Z1287_SERIES) || defined(KV11Z7_SERIES)
/* NOTE: If a sub-family has UART0 separated as another IP, it will be handled by
 * LPSCI driver.
 */
#if !defined (UART0_INSTANCE_COUNT) && (UART_INSTANCE_COUNT > 0)
/* Implementation of UART0 handler named in startup code. */
void UART0_IRQHandler(void)
{
    UART_DRV_IRQHandler(0);
}
#endif

#if (UART_INSTANCE_COUNT > 1)
/* Implementation of UART1 handler named in startup code. */
void UART1_IRQHandler(void)
{
    UART_DRV_IRQHandler(1);
}
#endif

#if (UART_INSTANCE_COUNT > 2)
/* Implementation of UART2 handler named in startup code. */
void UART2_IRQHandler(void)
{
    UART_DRV_IRQHandler(2);
}
#endif

#elif defined (K64F12_SERIES) || defined (K24F12_SERIES) || defined (K63F12_SERIES) || \
      defined (K22F51212_SERIES) || defined (K22F25612_SERIES) || defined (K22F12810_SERIES) || \
      defined (KV31F51212_SERIES) || defined (KV31F25612_SERIES) || defined (KV31F12810_SERIES) || \
      defined (K70F12_SERIES) || defined(K60D10_SERIES) || defined(K24F25612_SERIES) || \
      defined (KV30F12810_SERIES) || defined (K02F12810_SERIES) || \
      defined (K65F18_SERIES) || defined (K66F18_SERIES) || defined (K26F18_SERIES)

#if (UART_INSTANCE_COUNT > 0)
/* Implementation of UART0 handler named in startup code. */
void UART0_RX_TX_IRQHandler(void)
{
    UART_DRV_IRQHandler(0);
}
#endif

#if (UART_INSTANCE_COUNT > 1)
/* Implementation of UART1 handler named in startup code. */
void UART1_RX_TX_IRQHandler(void)
{
    UART_DRV_IRQHandler(1);
}
#endif

#if (UART_INSTANCE_COUNT > 2)
/* Implementation of UART2 handler named in startup code. */
void UART2_RX_TX_IRQHandler(void)
{
    UART_DRV_IRQHandler(2);
}
#endif

#if (UART_INSTANCE_COUNT > 3)
/* Implementation of UART3 handler named in startup code. */
void UART3_RX_TX_IRQHandler(void)
{
    UART_DRV_IRQHandler(3);
}
#endif

#if (UART_INSTANCE_COUNT > 4)
/* Implementation of UART4 handler named in startup code. */
void UART4_RX_TX_IRQHandler(void)
{
    UART_DRV_IRQHandler(4);
}
#endif

#if (UART_INSTANCE_COUNT > 5)
/* Implementation of UART5 handler named in startup code. */
void UART5_RX_TX_IRQHandler(void)
{
    UART_DRV_IRQHandler(5);
}
#endif

#elif defined (KL27Z644_SERIES) || defined (KL17Z644_SERIES) ||  defined (KL43Z4_SERIES)

#if (UART_INSTANCE_COUNT > 0)
/* Implementation of UART1 handler named in startup code. */
void UART2_FLEXIO_IRQHandler(void)
{
    UART_DRV_IRQHandler(2);
}
#endif

#elif defined (KM34Z7_SERIES)
/* Implementation of UART5 handler named in startup code. */
void UART0_UART1_UART2_UART3_IRQHandler(void)
{
    for(uint32_t i=0; i < UART_INSTANCE_COUNT; i++)
    {
        if (CLOCK_SYS_GetUartGateCmd(i))
        {
            UART_DRV_IRQHandler(i);
        }
    }
}
#else
    #error "No valid CPU defined!"
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/

