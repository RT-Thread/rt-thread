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

#include "fsl_flexcan_driver.h"
#if FSL_FEATURE_SOC_FLEXCAN_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(KV10Z1287_SERIES) || defined(KV11Z7_SERIES)
#if (CAN_INSTANCE_COUNT > 0U)
/* Implementation of CAN0 handler named in startup code. */
void CAN0_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(0);
}
#endif

#if (CAN_INSTANCE_COUNT > 1U)
/* Implementation of CAN1 handler named in startup code. */
void CAN1_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(1);
}
#endif
#else
#if (CAN_INSTANCE_COUNT > 0U)
/* Implementation of CAN0 handler named in startup code. */
void CAN0_ORed_Message_buffer_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(0);
}

/* Implementation of CAN0 handler named in startup code. */
void CAN0_Bus_Off_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(0);
}

/* Implementation of CAN0 handler named in startup code. */
void CAN0_Error_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(0);
}

/* Implementation of CAN0 handler named in startup code. */
void CAN0_Wake_Up_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(0);
}
#endif

#if (CAN_INSTANCE_COUNT > 1U)
/* Implementation of CAN1 handler named in startup code. */
void CAN1_ORed_Message_buffer_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(1);
}

/* Implementation of CAN1 handler named in startup code. */
void CAN1_Bus_Off_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(1);
}

/* Implementation of CAN1 handler named in startup code. */
void CAN1_Error_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(1);
}

/* Implementation of CAN1 handler named in startup code. */
void CAN1_Wake_Up_IRQHandler(void)
{
    FLEXCAN_DRV_IRQHandler(1);
}
#endif
#endif
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

