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

#include "fsl_ftm_driver.h"


/*******************************************************************************
 * Code
 ******************************************************************************/

#if (FTM_INSTANCE_COUNT > 0)
/*!
 * @brief Implementation of FTM0 handler named in startup code.
 *
 *  Passes instance to generic FTM IRQ handler.
 */
void FTM0_IRQHandler(void)
{
    FTM_DRV_IRQHandler(0U);
}
#endif

#if (FTM_INSTANCE_COUNT > 1)
/*!
 * @brief Implementation of FTM1 handler named in startup code.
 *
 * Passes instance to generic FTM IRQ handler.
 */
void FTM1_IRQHandler(void)
{
    FTM_DRV_IRQHandler(1U);
}
#endif

#if (FTM_INSTANCE_COUNT > 2)
/*!
 * @brief Implementation of FTM2 handler named in startup code.
 *
 * Passes instance to generic FTM IRQ handler.
 */
void FTM2_IRQHandler(void)
{
    FTM_DRV_IRQHandler(2U);
}
#endif

#if (FTM_INSTANCE_COUNT > 3)
/*!
 * @brief Implementation of FTM3 handler named in startup code.
 *
 * Passes instance to generic FTM IRQ handler.
 */
void FTM3_IRQHandler(void)
{
    FTM_DRV_IRQHandler(3U);
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

