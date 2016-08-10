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

#include <stdlib.h>
#include <assert.h>
#include "fsl_pit_driver.h"
#include "fsl_clock_manager.h"

/*!
 * @addtogroup pit_irq
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief System default IRQ handler defined in startup code.
 *
 * Users can either edit this handler or define a callback function. Furthermore,
 * interrupt manager could be used to re-map the IRQ handler to another function.
 */
#if FSL_FEATURE_PIT_HAS_SHARED_IRQ_HANDLER
#if defined(KM34Z7_SERIES)
void PIT0_PIT1_IRQHandler(void)
{
    uint32_t i;
    for(i=0; i < PIT_INSTANCE_COUNT; i++)
    {
        if (CLOCK_SYS_GetPitGateCmd(i))
        {
            for(i=0; i < FSL_FEATURE_PIT_TIMER_COUNT; i++)
            {
                if (PIT_HAL_IsIntPending(g_pitBase[0], i))
                {
                    /* Clear interrupt flag.*/
                    PIT_HAL_ClearIntFlag(g_pitBase[0], i);
                }
            }
        }
    }
}
#else
void PIT_IRQHandler(void)
{
    uint32_t i;
    for(i=0; i < FSL_FEATURE_PIT_TIMER_COUNT; i++)
    {
        if (PIT_HAL_IsIntPending(g_pitBase[0], i))
        {
            /* Clear interrupt flag.*/
            PIT_HAL_ClearIntFlag(g_pitBase[0], i);
        }
    }
}
#endif
#else

#if (FSL_FEATURE_PIT_TIMER_COUNT > 0U)
void PIT0_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_HAL_ClearIntFlag(g_pitBase[0], 0U);
}
#endif

#if (FSL_FEATURE_PIT_TIMER_COUNT > 1U)
void PIT1_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_HAL_ClearIntFlag(g_pitBase[0], 1U);
}
#endif

#if (FSL_FEATURE_PIT_TIMER_COUNT > 2U)
void PIT2_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_HAL_ClearIntFlag(g_pitBase[0], 2U);
}
#endif

#if (FSL_FEATURE_PIT_TIMER_COUNT > 3U)
void PIT3_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_HAL_ClearIntFlag(g_pitBase[0], 3U);
}
#endif

#endif /* FSL_FEATURE_PIT_HAS_SHARED_IRQ_HANDLER */

/*! @} */

/*******************************************************************************
 * EOF
 ******************************************************************************/

