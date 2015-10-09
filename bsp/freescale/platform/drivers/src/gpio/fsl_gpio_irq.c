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
#include "fsl_gpio_driver.h"
#include "fsl_clock_manager.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

#if defined (KM34Z7_SERIES)

extern PORT_Type * const g_portBase[PORT_INSTANCE_COUNT];

void PTx_IRQHandler(void)
{
    for(uint32_t i=0; i < PORT_INSTANCE_COUNT; i++)
    {
        if (CLOCK_SYS_GetPortGateCmd(i))
        {
            /* Add user-defined ISR for PORT. */

            /* Clear interrupt flag.*/
            PORT_HAL_ClearPortIntFlag(g_portBase[i]);
        }
    }
}
#else
/* gpio IRQ handler with the same name in startup code. */
void PORTA_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTA_BASE_PTR);
}

#if defined (KL16Z4_SERIES) || defined (KL26Z4_SERIES) || defined (KL46Z4_SERIES) || defined (KW01Z4_SERIES)
/* gpio IRQ handler with the same name in startup code. */
void PORTC_PORTD_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTC_BASE_PTR);
    PORT_HAL_ClearPortIntFlag(PORTD_BASE_PTR);
}
#endif

#if defined (KL25Z4_SERIES) || defined (K70F12_SERIES) || defined(K60D10_SERIES) || \
    defined (K22F12810_SERIES) || defined (K22F25612_SERIES) || defined (K22F51212_SERIES) || \
    defined (KV31F12810_SERIES) || defined (KV31F25612_SERIES) || defined (KV31F51212_SERIES) || \
    defined (K64F12_SERIES) || defined (K24F12_SERIES) || defined (K63F12_SERIES) || \
    defined (K24F25612_SERIES) || defined (KV30F12810_SERIES) || defined (K02F12810_SERIES) || \
    defined (K26F18_SERIES) || defined (K65F18_SERIES) || defined (K66F18_SERIES) || \
    defined (K80F25615_SERIES) || defined (K81F25615_SERIES) || defined (K82F25615_SERIES)
/* gpio IRQ handler with the same name in startup code. */
void PORTD_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTD_BASE_PTR);
}
#endif

#if defined (K70F12_SERIES) || defined(K60D10_SERIES) || \
    defined (K64F12_SERIES) || defined (K24F12_SERIES) || defined (K63F12_SERIES) || \
    defined (K22F12810_SERIES) || defined (K22F25612_SERIES) || defined (K22F51212_SERIES) || \
    defined (KV31F12810_SERIES) || defined (KV31F25612_SERIES) || defined (KV31F51212_SERIES) || \
    defined (K24F25612_SERIES) || \
    defined (K26F18_SERIES) || defined (K65F18_SERIES) || defined (K66F18_SERIES) || \
    defined (K80F25615_SERIES) || defined (K81F25615_SERIES)
/* gpio IRQ handler with the same name in startup code. */
void PORTB_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTB_BASE_PTR);
}

/* gpio IRQ handler with the same name in startup code. */
void PORTC_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTC_BASE_PTR);
}

/* gpio IRQ handler with the same name in startup code. */
void PORTE_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTE_BASE_PTR);
}
#endif

#if defined (K70F12_SERIES)
/* gpio IRQ handler with the same name in startup code. */
void PORTF_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTF_BASE_PTR);
}
#endif

#if defined (KL03Z4_SERIES)
/* gpio IRQ handler with the same name in startup code. */
void PORTB_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PORT_HAL_ClearPortIntFlag(PORTB_BASE_PTR);
}
#endif

#if defined (KW40Z4_SERIES)
/* gpio IRQ handler with the same name in startup code. */
void PORTBC_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    if(PORT_HAL_GetPortIntFlag(PORTB_BASE))  PORT_HAL_ClearPortIntFlag(PORTB_BASE);
    if(PORT_HAL_GetPortIntFlag(PORTC_BASE))  PORT_HAL_ClearPortIntFlag(PORTC_BASE);
}
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/

