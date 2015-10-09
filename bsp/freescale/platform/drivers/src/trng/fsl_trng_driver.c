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
#include <string.h>
#include "fsl_trng_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"

#if FSL_FEATURE_SOC_TRNG_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/
 
#if defined(FSL_RTOS_FREE_RTOS)
#define TRNG_DRV_WAIT_TIMEOUT   (1) /*Workaround for infinite posible blocking in FreeRTOS.*/
#else
#define TRNG_DRV_WAIT_TIMEOUT   (OSA_WAIT_FOREVER) /*Workaround for infinite posible blocking in FreeRTOS.*/
#endif
 
/*! @brief Context storage. Data structure for the TRNG internal state.*/
typedef struct _trng_context
 {
    uint32_t            index;
#if TRNG_DRV_RTOS_SLEEP
    event_t             sync;
#endif
#if TRNG_DRV_RTOS_MULTI_THREAD
    mutex_t             mutex;
#endif
} trng_context_t;

/*! @brief Global TRNG context data structure. */
static trng_context_t trng_context[FSL_FEATURE_SOC_TRNG_COUNT];

/* Default values for user configuration structure.*/

#if (defined(KV56F22_SERIES) || defined(KV58F22_SERIES))
    #define TRNG_USER_CONFIG_DEFAULT_OSC_DIV            kTRNGRingOscDiv4 
#elif (defined(KW40Z4_SERIES))
    #define TRNG_USER_CONFIG_DEFAULT_OSC_DIV            kTRNGRingOscDiv8 
#else 
    #define TRNG_USER_CONFIG_DEFAULT_OSC_DIV            kTRNGRingOscDiv0
#endif

#define TRNG_USER_CONFIG_DEFAULT_LOCK                   0
#define TRNG_USER_CONFIG_DEFAULT_ENTROPY_DELAY          3200
#define TRNG_USER_CONFIG_DEFAULT_SAMPLE_SIZE            2500
#define TRNG_USER_CONFIG_DEFAULT_SPARSE_BIT_LIMIT       63
#define TRNG_USER_CONFIG_DEFAULT_RETRY_COUNT            1
#define TRNG_USER_CONFIG_DEFAULT_RUN_MAX_LIMIT          34

#define TRNG_USER_CONFIG_DEFAULT_MONOBIT_MAXIMUM        1384
#define TRNG_USER_CONFIG_DEFAULT_MONOBIT_MINIMUM        (TRNG_USER_CONFIG_DEFAULT_MONOBIT_MAXIMUM - 268)
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT1_MAXIMUM        405
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT1_MINIMUM        (TRNG_USER_CONFIG_DEFAULT_RUNBIT1_MAXIMUM - 178)
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT2_MAXIMUM        220
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT2_MINIMUM        (TRNG_USER_CONFIG_DEFAULT_RUNBIT2_MAXIMUM - 122)
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT3_MAXIMUM        125
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT3_MINIMUM        (TRNG_USER_CONFIG_DEFAULT_RUNBIT3_MAXIMUM - 88)
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT4_MAXIMUM        75
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT4_MINIMUM        (TRNG_USER_CONFIG_DEFAULT_RUNBIT4_MAXIMUM - 64)
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT5_MAXIMUM        47
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT5_MINIMUM        (TRNG_USER_CONFIG_DEFAULT_RUNBIT5_MAXIMUM - 46)
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT6PLUS_MAXIMUM    47
#define TRNG_USER_CONFIG_DEFAULT_RUNBIT6PLUS_MINIMUM    (TRNG_USER_CONFIG_DEFAULT_RUNBIT6PLUS_MAXIMUM - 46)
#define TRNG_USER_CONFIG_DEFAULT_POKER_MAXIMUM          26912
#define TRNG_USER_CONFIG_DEFAULT_POKER_MINIMUM          (TRNG_USER_CONFIG_DEFAULT_POKER_MAXIMUM - 2467)
#define TRNG_USER_CONFIG_DEFAULT_FREQUENCY_MAXIMUM      25600
#define TRNG_USER_CONFIG_DEFAULT_FREQUENCY_MINIMUM      1600

static trng_status_t trng_drv_ApplyUserConfig(uint32_t instance, const trng_user_config_t *user_config);


/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION*********************************************************************
 *
 * Function Name : TRNG_DRV_InitUserConfigDefault
 * Description   :  Initializes user configuration structure to default settings. 
 *
 *END*************************************************************************/
trng_status_t  TRNG_DRV_InitUserConfigDefault(trng_user_config_t *user_config)
{
    trng_status_t   result;

    if ( user_config != 0 )
    {
        user_config->lock = TRNG_USER_CONFIG_DEFAULT_LOCK;
        user_config->clockMode = kTRNGClockModeRingOscillator;
        user_config->ringOscDiv = TRNG_USER_CONFIG_DEFAULT_OSC_DIV;
        user_config->sampleMode = kTRNGSampleModeRaw;
        user_config->entropyDelay = TRNG_USER_CONFIG_DEFAULT_ENTROPY_DELAY;
        user_config->sampleSize = TRNG_USER_CONFIG_DEFAULT_SAMPLE_SIZE;
        user_config->sparseBitLimit = TRNG_USER_CONFIG_DEFAULT_SPARSE_BIT_LIMIT;

        /* Statistical Check Parameters.*/
        user_config->retryCount = TRNG_USER_CONFIG_DEFAULT_RETRY_COUNT;        
        user_config->longRunMaxLimit = TRNG_USER_CONFIG_DEFAULT_RUN_MAX_LIMIT; 
        
        user_config->monobitLimit.maximum = TRNG_USER_CONFIG_DEFAULT_MONOBIT_MAXIMUM;
        user_config->monobitLimit.minimum = TRNG_USER_CONFIG_DEFAULT_MONOBIT_MINIMUM;
        user_config->runBit1Limit.maximum = TRNG_USER_CONFIG_DEFAULT_RUNBIT1_MAXIMUM;
        user_config->runBit1Limit.minimum = TRNG_USER_CONFIG_DEFAULT_RUNBIT1_MINIMUM;
        user_config->runBit2Limit.maximum = TRNG_USER_CONFIG_DEFAULT_RUNBIT2_MAXIMUM;
        user_config->runBit2Limit.minimum = TRNG_USER_CONFIG_DEFAULT_RUNBIT2_MINIMUM;
        user_config->runBit3Limit.maximum = TRNG_USER_CONFIG_DEFAULT_RUNBIT3_MAXIMUM;
        user_config->runBit3Limit.minimum = TRNG_USER_CONFIG_DEFAULT_RUNBIT3_MINIMUM;
        user_config->runBit4Limit.maximum = TRNG_USER_CONFIG_DEFAULT_RUNBIT4_MAXIMUM;
        user_config->runBit4Limit.minimum = TRNG_USER_CONFIG_DEFAULT_RUNBIT4_MINIMUM;
        user_config->runBit5Limit.maximum = TRNG_USER_CONFIG_DEFAULT_RUNBIT5_MAXIMUM;
        user_config->runBit5Limit.minimum = TRNG_USER_CONFIG_DEFAULT_RUNBIT5_MINIMUM;
        user_config->runBit6PlusLimit.maximum = TRNG_USER_CONFIG_DEFAULT_RUNBIT6PLUS_MAXIMUM;
        user_config->runBit6PlusLimit.minimum = TRNG_USER_CONFIG_DEFAULT_RUNBIT6PLUS_MINIMUM;
        user_config->pokerLimit.maximum = TRNG_USER_CONFIG_DEFAULT_POKER_MAXIMUM;
        user_config->pokerLimit.minimum = TRNG_USER_CONFIG_DEFAULT_POKER_MINIMUM;
        user_config->frequencyCountLimit.maximum = TRNG_USER_CONFIG_DEFAULT_FREQUENCY_MAXIMUM;
        user_config->frequencyCountLimit.minimum = TRNG_USER_CONFIG_DEFAULT_FREQUENCY_MINIMUM;

        result = kStatus_TRNG_Success;
    }
    else
    {
        result = kStatus_TRNG_InvalidArgument;
    }

    return result;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : trng_drv_ApplyUserConfig
 * Description   : Apply user configuration settings to TRNG module. 
 *
 *END*************************************************************************/
static trng_status_t trng_drv_ApplyUserConfig(uint32_t instance, const trng_user_config_t *user_config)
{
    trng_status_t status;
    TRNG_Type       *base;

    base = g_trngBase[instance];

    if(((status = TRNG_HAL_SetRetryCount(base, user_config->retryCount)) == kStatus_TRNG_Success) 
        &&((status = TRNG_HAL_SetRetryCount(base, user_config->retryCount)) == kStatus_TRNG_Success)
        &&((status = TRNG_HAL_SetStatisticalCheckLimit(base, kTRNGStatisticalCheckMonobit, &user_config->monobitLimit)) == kStatus_TRNG_Success)
        &&((status = TRNG_HAL_SetStatisticalCheckLimit(base, kTRNGStatisticalCheckRunBit1, &user_config->runBit1Limit)) == kStatus_TRNG_Success)
        &&((status = TRNG_HAL_SetStatisticalCheckLimit(base, kTRNGStatisticalCheckRunBit2, &user_config->runBit2Limit)) == kStatus_TRNG_Success)
        &&((status = TRNG_HAL_SetStatisticalCheckLimit(base, kTRNGStatisticalCheckRunBit3, &user_config->runBit3Limit)) == kStatus_TRNG_Success)
        &&((status = TRNG_HAL_SetStatisticalCheckLimit(base, kTRNGStatisticalCheckRunBit4, &user_config->runBit4Limit)) == kStatus_TRNG_Success)
        &&((status = TRNG_HAL_SetStatisticalCheckLimit(base, kTRNGStatisticalCheckRunBit5, &user_config->runBit5Limit)) == kStatus_TRNG_Success)
        &&((status = TRNG_HAL_SetStatisticalCheckLimit(base, kTRNGStatisticalCheckRunBit6Plus, &user_config->runBit6PlusLimit)) == kStatus_TRNG_Success)
        &&((status = TRNG_HAL_SetStatisticalCheckLimit(base, kTRNGStatisticalCheckPoker, &user_config->pokerLimit)) == kStatus_TRNG_Success)
        &&((status = TRNG_HAL_SetStatisticalCheckLimit(base, kTRNGStatisticalCheckFrequencyCount, &user_config->frequencyCountLimit)) == kStatus_TRNG_Success)
     )     
    {
        TRNG_HAL_SetClockMode(base, user_config->clockMode);
        TRNG_HAL_SetRingOscDiv(base, user_config->ringOscDiv);
        TRNG_HAL_SetSampleMode(base, user_config->sampleMode);
        TRNG_HAL_SetEntropyDelay(base, user_config->entropyDelay);
        TRNG_HAL_SetSampleSize(base, user_config->sampleSize);
        TRNG_HAL_SetSparseBitLimit(base, user_config->sparseBitLimit);

        TRNG_HAL_SetLongRunMaxLimit(base, user_config->longRunMaxLimit);

    #if TRNG_DRV_RTOS_SLEEP
        /* Clear Interrupt status.*/
        TRNG_HAL_ClearIntStatusFlag(base, kTRNGInterruptAll);

        /* Enable interrupt.*/
        INT_SYS_EnableIRQ(g_trngIrqId[instance]);
        TRNG_HAL_SetIntMode(base, kTRNGInterruptAll, true);
    #endif /* TRNG_DRV_RTOS_SLEEP */
    }

    return status;
}

/*FUNCTION*********************************************************************
 *
 * Function Name: TRNG_DRV_Init
 * Description: This function is used to initialize the TRNG
 *
 *END*************************************************************************/
trng_status_t TRNG_DRV_Init(uint32_t instance, const trng_user_config_t *user_config)
{
    trng_status_t   result;
    TRNG_Type       *base;


    /* Check input parameters.*/
    if((instance < FSL_FEATURE_SOC_TRNG_COUNT) 
        || (user_config != 0) ) 
    {
        base = g_trngBase[instance];

        /* Initialize internal state structure.*/
        memset(&trng_context[instance], 0, sizeof(trng_context[instance]));


        if ( 1
    #if TRNG_DRV_RTOS_MULTI_THREAD
            && (OSA_MutexCreate(&trng_context[instance].mutex) == kStatus_OSA_Success)
    #endif
    #if TRNG_DRV_RTOS_SLEEP
             && (OSA_EventCreate(&trng_context[instance].sync, kEventAutoClear) == kStatus_OSA_Success)
    #endif
            )
        {

            /* Enable the clock gate from clock manager. */
            if (!CLOCK_SYS_GetTrngGateCmd(instance))
            {
                CLOCK_SYS_EnableTrngClock(instance);
            }

            /* Reset the registers of TRNG module to reset state. */
            TRNG_HAL_Init(base);
            
            /* Set configuration.*/
            if((result = trng_drv_ApplyUserConfig(instance, user_config)) == kStatus_TRNG_Success)
            {
                /* Start entropy generation.*/
                TRNG_HAL_Enable(base);
                    
                if(user_config->lock == 1) /* Disable programmability of TRNG registers. */
                {
                    TRNG_HAL_EnableLock(base);
                }

                result = kStatus_TRNG_Success;
            }
        }
    #if TRNG_DRV_RTOS_MULTI_THREAD || TRNG_DRV_RTOS_SLEEP
        else
        {
            result = kStatus_TRNG_OSAError;
        }
    #endif
    }
    else
    {
        result = kStatus_TRNG_InvalidArgument;
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : TRNG_DRV_Deinit
 * Description   : Deinitilize TRNG.
 *
 *END**************************************************************************/
trng_status_t TRNG_DRV_Deinit(uint32_t instance)
{
    trng_status_t   result;
    TRNG_Type       *base;

    /* Check input parameters.*/
    if((instance < FSL_FEATURE_SOC_TRNG_COUNT) ) 
    {
        base = g_trngBase[instance];

    #if TRNG_DRV_RTOS_SLEEP
        /* Disable interrupt.*/
        {
            TRNG_HAL_SetIntMode(base, kTRNGInterruptAll, false);
            INT_SYS_DisableIRQ(g_trngIrqId[instance]);
        }
        OSA_EventDestroy(&trng_context[instance].sync);
    #endif

        /* Disable TRNG.*/
        TRNG_HAL_Disable(base);

        /* Check before clock stop.*/
        while(TRNG_HAL_GetOKToStopCmd(base) == 0)
        {} 

        /* Disable Clock*/
        CLOCK_SYS_DisableTrngClock(instance);
                    
    #if TRNG_DRV_RTOS_MULTI_THREAD
        OSA_MutexDestroy(&trng_context[instance].mutex);
    #endif

        /* Clear context.*/
        memset(&trng_context[instance], 0, sizeof(trng_context[instance]));

        result = kStatus_TRNG_Success;
    }
    else
    {
        result = kStatus_TRNG_InvalidArgument;
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : TRNG_DRV_GetRandomData
 * Description   : This function gets random data from the TRNG.
 *
 *END**************************************************************************/
trng_status_t TRNG_DRV_GetRandomData(uint32_t instance, void *data, uint32_t data_size)
{
    trng_status_t   result = kStatus_TRNG_Success;
    TRNG_Type       *base;
    uint32_t        random_32;
    uint8_t         *random_p;
    uint32_t        random_size;
    uint8_t         *data_p = (uint8_t *)data;
    int             i;
#if TRNG_DRV_RTOS_SLEEP
    event_flags_t   flagCheck;
#endif

    /* Check input parameters.*/
    if((instance < FSL_FEATURE_SOC_TRNG_COUNT) ) 
    {
        base = g_trngBase[instance];
        while((data_size > 0))
        {
        #if TRNG_DRV_RTOS_MULTI_THREAD
            OSA_MutexLock(&trng_context[instance].mutex, OSA_WAIT_FOREVER);
        #endif

            /* Wait for Valid or Error flag*/
            while((TRNG_HAL_GetEntropyValidCmd(base) == 0) && (TRNG_HAL_GetErrorCmd(base) == 0))
            {
            #if TRNG_DRV_RTOS_SLEEP
                while(OSA_EventWait(&trng_context[instance].sync, 0x1, false, TRNG_DRV_WAIT_TIMEOUT, &flagCheck)== kStatus_OSA_Idle)
                {}
            #endif
            }

            /* Check status.*/
            result = TRNG_HAL_GetStatus(base);

            /* If error occured */
            if(result != kStatus_TRNG_Success)
            {
                /* Clear error.*/
                TRNG_HAL_ClearError(base);
            #if TRNG_DRV_RTOS_MULTI_THREAD
                OSA_MutexUnlock(&trng_context[(instance)].mutex);
            #endif
                break; /* No sense stay here.*/
            }

            /* Read Entropy*/
            random_32 = TRNG_HAL_ReadEntropy(base, trng_context[instance].index++);

        #if TRNG_DRV_RTOS_MULTI_THREAD
            OSA_MutexUnlock(&trng_context[instance].mutex);
        #endif
            
            random_p = (uint8_t *)&random_32;

            if(data_size < sizeof(random_32))
            {   
                random_size = data_size;
            }
            else
            {
                random_size = sizeof(random_32);
            }

            for(i=0; i < random_size; i++)
            {
                *data_p++ = *random_p++;
            }

            data_size -= random_size;
        }
    }
    else
    {
        result = kStatus_TRNG_InvalidArgument;
    }

    return result;
}

/*FUNCTION*********************************************************************
 *
 * Function Name: TRNG_DRV_IRQHandler
 * Description: This function is used to handle the TRNG interrupt.
 *
 *END*************************************************************************/
void TRNG_DRV_IRQHandler(uint32_t instance)
{
    /* Check input parameters.*/
    if((instance < FSL_FEATURE_SOC_TRNG_COUNT) ) 
    {
        TRNG_Type  *base= g_trngBase[instance];

        /* Clear status flags.*/
        TRNG_HAL_ClearIntStatusFlag(base, kTRNGInterruptAll);

    #if TRNG_DRV_RTOS_SLEEP
        OSA_EventSet(&trng_context[instance].sync, 0x1);
    #endif
    }
}

#endif

/*******************************************************************************
 * EOF
 *******************************************************************************/

