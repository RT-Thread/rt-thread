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
#include <stdbool.h>
#include "fsl_ltc_driver.h"

#if FSL_FEATURE_SOC_LTC_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/
#define LTC_INSTANCE      0U

/******************************************************************************
 * Code
 *****************************************************************************/
#if LTC_DRV_RTOS_SLEEP 
    #if FSL_RTOS_MQX

        /* MQX RTOS require installation of interrupt handlers by application. */
        void MQX_LTC0_IRQHandler(void)
        {
            LTC_DRV_IRQHandler(LTC_INSTANCE);
        }

    #else /* FSL_RTOS_MQX */

        /* LTC0_IRQHandler IRQ handler that would cover the same name's APIs in startup code */
        void LTC0_IRQHandler(void)
        {
            LTC_DRV_IRQHandler(LTC_INSTANCE);
        }

    #endif
#endif /* LTC_DRV_RTOS_SLEEP */

#endif /*FSL_FEATURE_SOC_LTC_COUNT*/

/******************************************************************************
 * EOF
 *****************************************************************************/

