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

#include <assert.h>
#include <string.h>

#include "fsl_ltc_driver.h"
#include "fsl_ltc_driver_prv.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_LTC_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/
#ifndef LTC_DRV_RTOS_USE_EVENT
#define LTC_DRV_RTOS_USE_EVENT  1
#endif
/*Just for testing.*/
#ifndef LTC_DRV_RTOS_USE_SEM
#define LTC_DRV_RTOS_USE_SEM    0
#endif

#if defined(FSL_RTOS_FREE_RTOS)
#define LTC_DRV_WAIT_TIMEOUT   (1) /*Workaround for infinite posible blocking in FreeRTOS.*/
#else
#define LTC_DRV_WAIT_TIMEOUT   (OSA_WAIT_FOREVER) /*Workaround for infinite posible blocking in FreeRTOS.*/
#endif

typedef struct _ltc_context
 {
#if LTC_DRV_RTOS_SLEEP
    #if LTC_DRV_RTOS_USE_EVENT
        event_t     ltcEvent;
    #elif LTC_DRV_RTOS_USE_SEM /*Just for testing.*/
        semaphore_t ltcSem;
    #else 
        mutex_t     ltcMutex;
    #endif
    ltc_status_t            status;
#endif
#if LTC_DRV_RTOS_MULTI_THREAD
    mutex_t                 mutex;
#endif
    ltc_hal_status_flag_t   status_flag;
} ltc_context_t;


/*! @brief Global LTC context data structure. */
static ltc_context_t ltc_context[FSL_FEATURE_SOC_LTC_COUNT];


/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_Init
 * Description   : Initialize the LTC driver to a working state and enable
 *                 clocking.
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_Init(uint32_t instance)
{
    ltc_status_t   result;

    /* Check input parameters.*/
    if(instance < FSL_FEATURE_SOC_LTC_COUNT) 
    {
        if ( 1
    #if LTC_DRV_RTOS_MULTI_THREAD
            && (OSA_MutexCreate(&ltc_context[instance].mutex) == kStatus_OSA_Success)
    #endif
    #if LTC_DRV_RTOS_SLEEP
        #if LTC_DRV_RTOS_USE_EVENT
             && (OSA_EventCreate(&ltc_context[instance].ltcEvent, kEventAutoClear) == kStatus_OSA_Success)
        #elif LTC_DRV_RTOS_USE_SEM /*Just for testing.*/
             && (OSA_SemaCreate(&ltc_context[instance].ltcSem, -1) == kStatus_OSA_Success)
        #else
            && (OSA_MutexCreate(&ltc_context[instance].ltcMutex) == kStatus_OSA_Success)
        #endif
     #endif
            )
        {
            /* Enable the system clock for the LTC module. */
            CLOCK_SYS_EnableLtcClock(instance);

            /* Initialize to a known working state and reset all control logic. */
            LTC_HAL_Init(g_ltcBase[instance]);

        #if LTC_DRV_RTOS_SLEEP
            /* Enable LTC interrupt.*/
            INT_SYS_EnableIRQ(g_ltcIrqId[instance]);
            ltc_context[instance].status = kStatus_LTC_Success;

            #if !LTC_DRV_RTOS_USE_EVENT && !LTC_DRV_RTOS_USE_SEM
                OSA_MutexLock(&ltc_context[instance].ltcMutex, OSA_WAIT_FOREVER);
            #endif
        #else
            INT_SYS_DisableIRQ(g_ltcIrqId[instance]);
        #endif

            ltc_context[instance].status_flag = (ltc_hal_status_flag_t)0;
            result = kStatus_LTC_Success;
        }
    #if LTC_DRV_RTOS_MULTI_THREAD || LTC_DRV_RTOS_SLEEP
        else
        {
            result = kStatus_LTC_OSAError;
        }
    #endif
    }
    else
    {
        result = kStatus_LTC_InvalidInput;
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_Deinit
 * Description   : Uninitialize the LTC driver and disable clocking.
 *
 *END**************************************************************************/
void LTC_DRV_Deinit(uint32_t instance)
{
    if(ltc_drv_check_instance(instance))
    {    
    
        /* Disable the system clock for the LTC module. */
        CLOCK_SYS_DisableLtcClock(instance);

#if LTC_DRV_RTOS_SLEEP
          INT_SYS_DisableIRQ(g_ltcIrqId[instance]);
    #if LTC_DRV_RTOS_USE_EVENT
          OSA_EventDestroy(&ltc_context[instance].ltcEvent);
    #elif LTC_DRV_RTOS_USE_SEM
          OSA_SemaDestroy(&ltc_context[instance].ltcSem);
    #else
          OSA_MutexDestroy(&ltc_context[instance].ltcMutex);
    #endif
#endif
#if LTC_DRV_RTOS_MULTI_THREAD
        OSA_MutexDestroy(&ltc_context[instance].mutex);
 #endif
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_return_status
 * Description   : Check LTC Error Status bit. Return specific error code if set.
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_return_status(uint32_t instance)
{
    ltc_hal_status_flag_t status_reg; /* read and write LTC status register */
    /* return status */
    LTC_HAL_GetStatusFlagMasked(g_ltcBase[instance], kLTCStatus_Error_ISR, &status_reg);
    if (status_reg != 0u)
    {
        ltc_status_t err_code;    
        ltc_hal_error_status_flag_t error_status;
        
        LTC_HAL_GetErrorStatusFlagMasked(g_ltcBase[instance], kLTCErrorStatus_ErrId, &error_status);
        
        /* Reset LTC internal logic if there was error. Only this can clear the error flag bit. */
        LTC_HAL_Command(g_ltcBase[instance], kLTCCmd_ResetAll);
        
        /* The code below can be replaced by simply:
         * return (ltc_status_t)((error_status << kStatus_LTC_ErrShift) | (kStatus_LTC_Error));
         * but you must be sure that ltc_status_t error code values exactly match the (ERRID1 << 4) | kStatus_LTC_Error.
         */
        err_code = kStatus_LTC_Error;
        switch (error_status)
        {
            case kLTCErrorStatus_Mode:
                err_code = kStatus_LTC_ModeError;
                break;
            case kLTCErrorStatus_DataSize:
                err_code = kStatus_LTC_DataSizeError;
                break;
            case kLTCErrorStatus_KeySize:
                err_code = kStatus_LTC_KeySizeError;
                break;
            #if FSL_FEATURE_LTC_HAS_PKHA
            case kLTCErrorStatus_PKHA_A_Size:
                err_code = kStatus_LTC_PKHA_RegASzError;
                break;
            case kLTCErrorStatus_PKHA_B_Size:
                err_code = kStatus_LTC_PKHA_RegBSzError;
                break;
            #endif /* FSL_FEATURE_LTC_HAS_PKHA */
            case kLTCErrorStatus_DataSequence:
                err_code = kStatus_LTC_DataOutOfSeqError;
                break;
            #if FSL_FEATURE_LTC_HAS_PKHA
            case kLTCErrorStatus_PKHA_Div_Zero:
                err_code = kStatus_LTC_PKHA_DivByZeroError;
                break;
            case kLTCErrorStatus_PKHA_Mod_Even:
                err_code = kStatus_LTC_PKHA_ModulusEvenError;
                break;
            #endif /* FSL_FEATURE_LTC_HAS_PKHA */
            #if FSL_FEATURE_LTC_HAS_DES
            case kLTCErrorStatus_DES_Key_Parity:
                err_code = kStatus_LTC_DES_KeyParityError;
                break;
            #endif /* FSL_FEATURE_LTC_HAS_DES */
            case kLTCErrorStatus_ICV_Check_Fail:
                err_code = kStatus_LTC_ICV_CheckFailed;
                break;
            case kLTCErrorStatus_Internal_Fail:
                err_code = kStatus_LTC_InternalHwFailure;
                break;
            case kLTCErrorStatus_AAD_Size:
                err_code = kStatus_LTC_CCM_AadSzError;
                break;
            case kTLCErrorStatus_Invalid_Engine:
                err_code = kStatus_LTC_CCM_InvalidCryptoSel;
                break;
            default:
                break;
        }
        return err_code;
    }
    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_get_key
 * Description   : Read key from the LTC context.
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_get_key(uint32_t instance, uint8_t *key, uint8_t keySize)
{
    uint8_t rdkey[32]; /* make room for 32 byte keys */
    
    if (!ltc_drv_check_key_size(keySize))
    {
        return kStatus_LTC_InvalidKeyLength;
    }
    
    LTC_HAL_GetKey(g_ltcBase[instance], &rdkey[0], sizeof(rdkey));
    memcpy(key, rdkey, keySize);    
    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_process_message_in_sessions
 * Description   : CBC, CTR, OFB and CFB
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_process_message_in_sessions(uint32_t instance, 
                                                 const uint8_t *inData, 
                                                 uint32_t inSize, 
                                                 uint8_t *outData)
{
    uint32_t sz;
    ltc_status_t retval;
    ltc_hal_mode_t mode_reg; /* read and write LTC mode register */
    
    retval = kStatus_LTC_Error;
    sz = FSL_LTC_FIFO_SZ_MAX_DOWN_ALGN;
    mode_reg = LTC_HAL_ReadMode(g_ltcBase[instance]);
    retval = kStatus_LTC_Success;
    
    while (inSize)
    {
        if (inSize <= sz)
        {
            retval = ltc_drv_symmetric_process_data(instance, inData, inSize, outData);
            inSize = 0;
        }
        else
        {
            ltc_drv_symmetric_process_data(instance, inData, sz, outData);

            inData += sz;
            inSize -= sz;
            outData += sz;
            LTC_HAL_WriteMode(g_ltcBase[instance], mode_reg);
        }
    }
    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_symmetric_alg_state
 * Description   : Init LTC for symmetric key, with AS as function argument.
 *
 *END**************************************************************************/
static ltc_status_t ltc_drv_symmetric_alg_state(uint32_t instance, 
                                                const uint8_t *key,
                                                uint8_t keySize,
                                                ltc_hal_algorithm_t alg,
                                                ltc_hal_mode_symmetric_alg_t mode,
                                                ltc_hal_mode_encrypt_t enc,
                                                ltc_hal_mode_algorithm_state_t as)
{
    ltc_hal_mode_t modeReg = 0u;

    LTC_HAL_GetStatusFlag(g_ltcBase[instance], kLTCStatus_AES_Busy);

    /* Clear internal register states. */
    LTC_HAL_ClearWritten(g_ltcBase[instance], kLTCClear_All);

    /* Set byte swap on for several registers we will be reading and writing
     * user data to/from. */
    LTC_HAL_SetCtxRegInputByteSwap(g_ltcBase[instance], kLTCCtrl_ByteSwap);
    LTC_HAL_SetCtxRegOutputByteSwap(g_ltcBase[instance], kLTCCtrl_ByteSwap);
    LTC_HAL_SetInputFIFOByteSwap(g_ltcBase[instance], kLTCCtrl_ByteSwap);
    LTC_HAL_SetOutputFIFOByteSwap(g_ltcBase[instance], kLTCCtrl_ByteSwap);
    LTC_HAL_SetKeyRegInputByteSwap(g_ltcBase[instance], kLTCCtrl_ByteSwap);
    LTC_HAL_SetKeyRegOutputByteSwap(g_ltcBase[instance], kLTCCtrl_ByteSwap);
    
    LTC_HAL_SetKeySize(g_ltcBase[instance], 0);

    /* Write the key in place. */
    LTC_HAL_SetKey(g_ltcBase[instance], key, keySize);

    /* Write the key size.  This must be done after writing the key, and this
     * action locks the ability to modify the key registers. */    
    LTC_HAL_SetKeySize(g_ltcBase[instance], keySize);
    
    /* Clear the 'done' interrupt. */
    LTC_HAL_ClearDoneInterruptStatus(g_ltcBase[instance]);

    /* Set the proper block and algorithm mode. */
    LTC_HAL_ModeSetAlgorithm(&modeReg, alg);
    LTC_HAL_ModeSetEncrypt(&modeReg, enc);
    LTC_HAL_ModeSetAlgorithmState(&modeReg, as);
    LTC_HAL_ModeSetSymmetricAlg(&modeReg, mode);

    /* Write the mode register to the hardware. */
    LTC_HAL_WriteMode(g_ltcBase[instance], modeReg);

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_symmetric_init_final
 * Description   : Initialize the LTC module for symmetric key encrypt/decrypt
 *                 operation in INITIALIZE/FINALIZE session.
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_symmetric_init_final(uint32_t instance,
                                          const uint8_t *key,
                                          uint8_t keySize,
                                          ltc_hal_algorithm_t alg,
                                          ltc_hal_mode_symmetric_alg_t mode,
                                          ltc_hal_mode_encrypt_t enc)
{
    return ltc_drv_symmetric_alg_state(instance,key,keySize,alg,mode,enc,kLTCMode_AS_InitFinal);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_symmetric_init
 * Description   : Initialize the LTC module for symmetric key encrypt/decrypt
 *                 operation to INITIALIZE session.
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_symmetric_init(uint32_t instance,
                                    const uint8_t *key,
                                    uint8_t keySize,
                                    ltc_hal_algorithm_t alg,
                                    ltc_hal_mode_symmetric_alg_t mode,
                                    ltc_hal_mode_encrypt_t enc)
{
    return ltc_drv_symmetric_alg_state(instance,key,keySize,alg,mode,enc,kLTCMode_AS_Init);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_symmetric_final
 * Description   : Initialize the LTC module for symmetric key encrypt/decrypt
 *                 operation to FINALIZE session.
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_symmetric_final(uint32_t instance,
                                     const uint8_t *key,
                                     uint8_t keySize,
                                     ltc_hal_algorithm_t alg,
                                     ltc_hal_mode_symmetric_alg_t mode,
                                     ltc_hal_mode_encrypt_t enc)
{
    return ltc_drv_symmetric_alg_state(instance,key,keySize,alg,mode,enc,kLTCMode_AS_Finalize);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_symmetric_update
 * Description   : Initialize the LTC module for symmetric key encrypt/decrypt
 *                 operation to UPDATE session.
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_symmetric_update(uint32_t instance,
                                      const uint8_t *key,
                                      uint8_t keySize,
                                      ltc_hal_algorithm_t alg,
                                      ltc_hal_mode_symmetric_alg_t mode,
                                      ltc_hal_mode_encrypt_t enc)
{
    return ltc_drv_symmetric_alg_state(instance,key,keySize,alg,mode,enc,kLTCMode_AS_Update);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_symmetric_process
 * Description   : Polling loop that writes input data to LTC Input FIFO
 *                 and reads data from LTC Output FIFO.
 *
 *END**************************************************************************/
static void ltc_drv_symmetric_process(uint32_t instance, uint32_t inSize, const uint8_t **inData, uint8_t **outData)
{
    uint32_t outSize;
    uint32_t fifoData;
    uint32_t fifoStatus;
    
    register const uint8_t *in = *inData;
    register uint8_t *out = *outData;    
    
    outSize = inSize;
    while ((outSize > 0) || (inSize > 0)) {    
        fifoStatus = LTC_HAL_GetStatusFIFO(g_ltcBase[instance]);
        
        /* Check output FIFO level to make sure there is at least an entry
         * ready to be read. */
        if (fifoStatus & kLTCFIFO_OutputFifoLevel) {
            /* Read data from the output FIFO. */
            if (outSize >= sizeof(uint32_t)) {                
#if __CORTEX_M > 0
                /* Cortex M4 supports misaligned stores */
                *(uint32_t*)out = LTC_HAL_ReadOutputFIFO(g_ltcBase[instance]);
#else
                LTC_HAL_SetUnalignedFromWord(LTC_HAL_ReadOutputFIFO(g_ltcBase[instance]), out);
#endif
                out += sizeof(uint32_t);
                outSize -= sizeof(uint32_t);
            } else if (outSize > 0) {
                fifoData = LTC_HAL_ReadOutputFIFO(g_ltcBase[instance]);
                memcpy(out, &fifoData, outSize);
                out += outSize;
                outSize = 0;                
            }
        }
        
        /* Check input FIFO status to see if it is full.  We can
         * only write more data when both input and output FIFOs are not at a full state. 
         * At the same time we are sure Output FIFO is not full because we have poped at least one entry
         * by the while loop above.
         */
        if (!(fifoStatus & kLTCFIFO_InputFifoFull)) {
            /* Copy data to the input FIFO.
             * Data can only be copied one word at a time, so pad the data
             * appropriately if it is less than this size. */
            if (inSize >= sizeof(uint32_t)) {
#if __CORTEX_M > 0
                /* Cortex M4 supports misaligned loads */
                LTC_HAL_WriteInputFIFO(g_ltcBase[instance], *(const uint32_t*)in);
#else
                LTC_HAL_WriteInputFIFO(g_ltcBase[instance], LTC_HAL_GetWordFromUnaligned(in));
#endif
                inSize -= sizeof(uint32_t);
                in += sizeof(uint32_t);
            } else if (inSize > 0) {
                fifoData = 0;
                memcpy(&fifoData, in, inSize);                
                LTC_HAL_WriteInputFIFO(g_ltcBase[instance], fifoData);
                in += inSize;
                inSize = 0;                
            }
        }
    }
    *inData = in;
    *outData = out;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_symmetric_process_data
 * Description   : The primary symmetric algorithm processing loop for one session. This
 *                 function takes input data of a given size and produces output
 *                 data of the same size.  Data is moved into the input FIFO and
 *                 removed from the output FIFO, and it processes both
 *                 encryption and decryption.
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_symmetric_process_data(uint32_t instance,
                                            const uint8_t *inData,
                                            uint32_t inSize,
                                            uint8_t *outData)
{   
    uint32_t lastSize;
    
    if ((!inData) || (!outData)) 
    {
        return kStatus_LTC_InvalidInput;
    }
    
    /* Write the data size. */
    LTC_HAL_SetDataSize(g_ltcBase[instance], inSize);
    
    /* Split the inSize into full 16-byte chunks and last incomplete block due to LTC AES OFIFO errata */
    if (inSize <= 16u)
    {        
        
        lastSize = inSize;
        inSize = 0;
    }
    else
    {   
        /* Process all 16-byte data chunks. */
        lastSize = inSize % 16u;
        if (lastSize == 0)
        {
            lastSize = 16;
            inSize -= 16;
        }
        else
        {
           inSize -= lastSize; /* inSize will be rounded down to 16 byte boundary. remaining bytes in lastSize */           
        }
    }
    
    ltc_drv_symmetric_process(instance, inSize, &inData, &outData);
    ltc_drv_symmetric_process(instance, lastSize, &inData, &outData);
    
    ltc_drv_wait(instance);

    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_symmetric_process_data_multiple
 * Description   : The primary symmetric algorithm processing loop. For multiple sessions. This
 *                 function takes input data of a given size and produces output
 *                 data of the same size.  Data is moved into the input FIFO and
 *                 removed from the output FIFO, and it processes both
 *                 encryption and decryption.
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_symmetric_process_data_multiple(uint32_t instance, 
                                                     const uint8_t *inData,
                                                     uint32_t inSize,
                                                     uint8_t *outData,
                                                     ltc_hal_mode_t mode_reg, 
                                                     ltc_hal_mode_algorithm_state_t lastAs)
{
    uint32_t fifoConsumed;
    uint32_t lastSize;
    uint32_t sz;
    uint32_t max_ltc_fifo_size;
    ltc_hal_mode_algorithm_state_t fsm;
    ltc_status_t    status;
        
    if ((!inData) || (!outData)) 
    {
        return kStatus_LTC_InvalidInput;
    }
    
    if (!((kLTCMode_AS_Finalize == lastAs) || (kLTCMode_AS_InitFinal == lastAs)))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    if (0 == inSize)
    {
        return kStatus_LTC_Success;
    }
    
    if (inSize <= 16u)
    {
        //fsm = kLTCMode_AS_Finalize;
        fsm = lastAs;
        lastSize = inSize;
    }
    else
    {
        fsm = LTC_HAL_ModeGetAlgorithmState(&mode_reg); /* this will be either kLTCMode_AS_Init or kLTCMode_AS_Update, based on prior processing */
        
        /* Process all 16-byte data chunks. */
        lastSize = inSize % 16u;
        if (lastSize == 0)
        {
            lastSize = 16;
            inSize -= 16;
        }
        else
        {
           inSize -= lastSize; /* inSize will be rounded down to 16 byte boundary. remaining bytes in lastSize */           
        }
    }
    
    max_ltc_fifo_size = 0xff0u;
    fifoConsumed = LTC_HAL_GetDataSize(g_ltcBase[instance]);
    
    while (lastSize)
    {
        switch (fsm)
        {
            case kLTCMode_AS_Update:
            case kLTCMode_AS_Init:
                while (inSize)
                {            
                    if (inSize > (max_ltc_fifo_size - fifoConsumed))
                    {
                        sz = (max_ltc_fifo_size - fifoConsumed);
                    }
                    else
                    {
                        sz = inSize;
                    }
                    LTC_HAL_SetDataSize(g_ltcBase[instance], sz);
                    ltc_drv_symmetric_process(instance, sz, &inData, &outData);
                    inSize -= sz;
                    fifoConsumed = 0;
                    
                    /* after we completed INITIALIZE job, are there still any data left? */
                    if (inSize)
                    {
                        fsm = kLTCMode_AS_Update;

                        ltc_drv_wait(instance);

                        LTC_HAL_ModeSetAlgorithmState(&mode_reg, fsm);
                        /* Write the mode register to the hardware. */
                        LTC_HAL_WriteMode(g_ltcBase[instance], mode_reg);
                    }
                    else
                    {
                        //fsm = kLTCMode_AS_Finalize;
                        fsm = lastAs;
                    }
                }            
                break;        
            
            case kLTCMode_AS_Finalize:
            case kLTCMode_AS_InitFinal:
                /* process last block in FINALIZE */

                ltc_drv_wait(instance);

                LTC_HAL_ModeSetAlgorithmState(&mode_reg, lastAs);
                /* Write the mode register to the hardware. */
                LTC_HAL_WriteMode(g_ltcBase[instance], mode_reg);            
                LTC_HAL_SetDataSize(g_ltcBase[instance], lastSize);
                ltc_drv_symmetric_process(instance, lastSize, &inData, &outData);
                lastSize = 0;
                break;
                
            default:
                break;
        }
    }

    status = ltc_drv_wait(instance);

    return status;
}

/*FUNCTION*********************************************************************
 *
 * Function Name: ltc_drv_get_status_flag
 * Description: This function is used to get the last status flag.
 *
 *END*************************************************************************/
ltc_hal_status_flag_t ltc_drv_get_status_flag(uint32_t instance)
{
    return ltc_context[instance].status_flag;
}

/*FUNCTION*********************************************************************
 *
 * Function Name: LTC_DRV_IRQHandler
 * Description: This function is used to handle the LTC interrupt.
 *
 *END*************************************************************************/
void LTC_DRV_IRQHandler(uint32_t instance)
{
    /* Check input parameters.*/
    if(instance < FSL_FEATURE_SOC_LTC_COUNT) 
    {
        LTC_Type        *base= g_ltcBase[instance];
        ltc_status_t    status;
        
        /* Save last staus_flag.*/
        LTC_HAL_GetStatusFlagMasked(g_ltcBase[instance], kLTCStatus_All, &ltc_context[instance].status_flag);

        /* Check 'done' flag. */
        if((unsigned)ltc_context[instance].status_flag & kLTCStatus_Done_ISR )
        {
            LTC_HAL_ClearWritten(g_ltcBase[instance],kLTCClear_DataSize);
            /* Clear 'done' interrupt status.  This also clears the mode register. */
            LTC_HAL_ClearDoneInterruptStatus(base);
        }


        /* If 'Error' flag is set, it is cleared automaticaly in ltc_drv_return_status()*/
        status = ltc_drv_return_status(instance);

    #if LTC_DRV_RTOS_SLEEP
        if(status != kStatus_LTC_Success) /* Write error*/
        {
            ltc_context[instance].status = status;
        }
        #if LTC_DRV_RTOS_USE_EVENT
            OSA_EventSet(&ltc_context[instance].ltcEvent, 0x1);
        #elif LTC_DRV_RTOS_USE_SEM
            OSA_SemaWait(&ltc_context[instance].ltcSem, 0); /* Reset semaphore, if several interrupts.*/   
            OSA_SemaPost(&ltc_context[instance].ltcSem);
        #else
            OSA_MutexLock(&ltc_context[instance].ltcMutex, 0); /*Reset mutex, if several interrupts.*/
            OSA_MutexUnlock(&ltc_context[instance].ltcMutex);
        #endif
    #else
        if(status != kStatus_LTC_Success) /* Write error*/
        {
            return;
        }
    #endif
    }
}

#if LTC_DRV_RTOS_MULTI_THREAD
/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_lock
 * Description   : Lock LTC driver..
 *
 *END**************************************************************************/
void ltc_drv_lock(uint32_t instance)
{
    OSA_MutexLock(&ltc_context[instance].mutex, OSA_WAIT_FOREVER);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_unlock
 * Description   : Unlock LTC driver..
 *
 *END**************************************************************************/
void ltc_drv_unlock(uint32_t instance)
{
    OSA_MutexUnlock(&ltc_context[instance].mutex);
}

#endif /* LTC_DRV_RTOS_MULTI_THREAD*/


/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_wait
 * Description   : Wait for LTC done or error event
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_wait(uint32_t instance)
{
    ltc_status_t  status;

#if LTC_DRV_RTOS_SLEEP
    event_flags_t   flagCheck;
    osa_status_t    osaStatus;

    /* Wait for the finish of interrupt! */

    do
    {
    #if LTC_DRV_RTOS_USE_EVENT
        osaStatus = OSA_EventWait(&ltc_context[instance].ltcEvent, 0x1, false, LTC_DRV_WAIT_TIMEOUT, &flagCheck);
    #elif LTC_DRV_RTOS_USE_SEM
        osaStatus = OSA_SemaWait(&ltc_context[instance].ltcSem, OSA_WAIT_FOREVER);
    #else
        osaStatus = OSA_MutexLock(&ltc_context[instance].ltcMutex, OSA_WAIT_FOREVER);
    #endif
    } while((osaStatus == kStatus_OSA_Idle) || (osaStatus == kStatus_OSA_Timeout));

    status = ltc_context[instance].status;
    ltc_context[instance].status = kStatus_LTC_Success; /* Clear status.*/
#else
    bool error = false;
    bool done = false;
    status = kStatus_LTC_Success;

    /* Wait for 'done' or 'error' flag. */
    while ((!error) && (!done))
    {
        error = LTC_HAL_GetStatusFlag(g_ltcBase[instance], kLTCStatus_Error_ISR);
        done = LTC_HAL_GetStatusFlag(g_ltcBase[instance], kLTCStatus_Done_ISR);
    }

    /* Save last staus_flag.*/
    LTC_HAL_GetStatusFlagMasked(g_ltcBase[instance], kLTCStatus_All, &ltc_context[instance].status_flag);
    
    if (error)
    {
        status = ltc_drv_return_status(instance);
    }
    else if (done)
    {
        status = kStatus_LTC_Success;

        LTC_HAL_ClearWritten(g_ltcBase[instance],kLTCClear_DataSize);
        /* Clear 'done' interrupt status.  This also clears the mode register. */
        LTC_HAL_ClearDoneInterruptStatus(g_ltcBase[instance]);
    }
#endif

    return status; 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_clear_all
 * Description   : This function can be used to clear all sensitive data from LTC module. 
 *                 Data like private keys. It is called internally by the LTC driver in case of error or operation complete.
 *
 *END**************************************************************************/
void ltc_drv_clear_all(uint32_t instance, bool pkha)
{
    LTC_HAL_ClearWritten(g_ltcBase[instance], kLTCClear_All);
#if FSL_FEATURE_LTC_HAS_PKHA
    if (pkha)
    {
        ltc_drv_pkha_clear_regabne(instance, true, true, true, true);
    }
#endif
}

#endif /* FSL_FEATURE_SOC_LTC_COUNT */

