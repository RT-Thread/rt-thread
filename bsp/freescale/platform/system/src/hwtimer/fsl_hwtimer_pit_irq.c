/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include <stdint.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup htwint
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern void HWTIMER_SYS_PitIsrAction(uint8_t pitChannel);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief HW Timers PIT Interrupt service routine.
 *
 * This is a shared interrupt handler for all PIT channels.
 */
#if FSL_FEATURE_PIT_HAS_SHARED_IRQ_HANDLER
void PIT_IRQHandler(void)
{
    uint32_t i;

    for(i = 0; i < FSL_FEATURE_PIT_TIMER_COUNT; i++)
    {
        HWTIMER_SYS_PitIsrAction(i);
    }
}
#else

#if (FSL_FEATURE_PIT_TIMER_COUNT > 0U)
/*!
 * @brief HW Timers PIT 0 Interrupt service routine.
 *
 */
void PIT0_IRQHandler(void)
{
    HWTIMER_SYS_PitIsrAction(0U);
}
#endif

#if (FSL_FEATURE_PIT_TIMER_COUNT > 1U)
/*!
 * @brief HW Timers PIT 1 Interrupt service routine.
 *
 */
void PIT1_IRQHandler(void)
{
    HWTIMER_SYS_PitIsrAction(1U);
}
#endif

#if (FSL_FEATURE_PIT_TIMER_COUNT > 2U)
/*!
 * @brief HW Timers PIT 2 Interrupt service routine.
 *
 */
void PIT2_IRQHandler(void)
{
    HWTIMER_SYS_PitIsrAction(2U);
}
#endif

#if (FSL_FEATURE_PIT_TIMER_COUNT > 3U)
/*!
 * @brief HW Timers PIT 3 Interrupt service routine.
 *
 */
void PIT3_IRQHandler(void)
{
    HWTIMER_SYS_PitIsrAction(3U);
}
#endif

#endif /* FSL_FEATURE_PIT_HAS_SHARED_IRQ_HANDLER */

/*! @} */

/*******************************************************************************
 * EOF
 ******************************************************************************/

