/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#include "fsl_rnga_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_RNG_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief Context storage. Data structure for the RNGA internal state.*/
typedef struct _rnga_context
 {
    uint32_t            index;
#if RNGA_DRV_RTOS_MULTI_THREAD
    mutex_t             mutex;
#endif
} rnga_context_t;

/*! @brief Global RNGA context data structure. */
#if RNGA_DRV_RTOS_MULTI_THREAD
static rnga_context_t rnga_context[FSL_FEATURE_SOC_RNG_COUNT];
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION*********************************************************************
 *
 * Function Name: RNGA_DRV_Init
 * Description: This function is used to initialize the RNGA
 *
 *END*************************************************************************/
rnga_status_t RNGA_DRV_Init(uint32_t instance, const rnga_user_config_t *config)
{
    assert(instance < RNG_INSTANCE_COUNT);
    RNG_Type * base = g_rngaBase[instance];
    bool mEnable;
 
    if (!config)
    {
        return kStatus_RNGA_InvalidArgument;
    }
    /* Enable the clock gate from clock manager. */
    mEnable = CLOCK_SYS_GetRngaGateCmd(instance);
    if (!mEnable)
    {
        CLOCK_SYS_EnableRngaClock(instance);
    }
    /* Reset the registers for RNGA module to reset state. */
    RNGA_HAL_Init(base);
    RNGA_HAL_SetIntMaskCmd(base, config->isIntMasked);
    RNGA_HAL_SetHighAssuranceCmd(base, config->highAssuranceEnable);
    RNGA_HAL_Enable(base);
    #if RNGA_DRV_RTOS_MULTI_THREAD
    if (OSA_MutexCreate(&rnga_context[instance].mutex) != kStatus_OSA_Success)
    {
        return(kStatus_RNGA_OSAError);
    }
    #endif
    return kStatus_RNGA_Success;
}

/*FUNCTION*********************************************************************
 *
 * Function Name: RNGA_DRV_Deinit
 * Description: This function is used to shut down the RNGA.
 *
 *END*************************************************************************/
void RNGA_DRV_Deinit(uint32_t instance)
{
    assert(instance < RNG_INSTANCE_COUNT);
    RNG_Type * base = g_rngaBase[instance];
    
    RNGA_HAL_Disable(base);
    CLOCK_SYS_DisableRngaClock(instance);
    #if RNGA_DRV_RTOS_MULTI_THREAD
    OSA_MutexDestroy(&rnga_context[instance].mutex);
    #endif
}

/*FUNCTION*********************************************************************
 *
 * Function Name: RNGA_DRV_IRQHandler
 * Description: This function is used to handle error interrupt caused by RNGA underflow.
 *
 *END*************************************************************************/
void RNGA_DRV_IRQHandler(uint32_t instance)
{
    assert(instance < RNG_INSTANCE_COUNT);
    RNG_Type * base = g_rngaBase[instance];

    RNGA_HAL_ClearIntFlag(base, true);
    RNGA_HAL_GetOutputRegUnderflowCmd(base);
    RNGA_HAL_GetLastReadStatusCmd(base);
}

/*FUNCTION*********************************************************************
 *
 * Function Name: RNGA_DRV_GetRandomData
 * Description: This function is used to read RNGA output and store it to user buffer.
 *
 *END*************************************************************************/
rnga_status_t RNGA_DRV_GetRandomData(uint32_t instance, void *data, uint32_t data_size)
{
    rnga_status_t status = kStatus_RNGA_Success;
    uint8_t *dst = (uint8_t *) data;
    int i;
    assert(instance < RNG_INSTANCE_COUNT);

    #if RNGA_DRV_RTOS_MULTI_THREAD
    OSA_MutexLock(&rnga_context[instance].mutex, OSA_WAIT_FOREVER);
    #endif
    /* Fill user specified memory with random data */
    for (i = 0; i < data_size; i++)
    {
        bool failed = false;
        uint8_t tmp = 0;
        int j;

        /* Get 8bit long random number from LSBs of 8 distinct random numbers */
        for (j = 0; j < 8; j++)
        {
            uint32_t e;
            RNG_Type *base = g_rngaBase[instance];

            status = RNGA_HAL_GetRandomData(base, &e);
            if (status != kStatus_RNGA_Success)
            {
                failed = true;
                break;
            }
            /* Add one bit of entropy to number */
            tmp |= (e & 1);
            tmp <<= 1;
        }
        if (failed)
        {
            break;
        }
        dst[i] = tmp;
    }
    #if RNGA_DRV_RTOS_MULTI_THREAD
    OSA_MutexUnlock(&rnga_context[instance].mutex);
    #endif
    return(status);
}
#endif

/*******************************************************************************
 * EOF
 *******************************************************************************/

