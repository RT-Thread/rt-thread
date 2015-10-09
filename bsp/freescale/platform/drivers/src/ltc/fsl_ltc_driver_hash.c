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

#include "fsl_ltc_driver.h"
#include "fsl_ltc_driver_prv.h"
#include <string.h>

/*FUNCTION**********************************************************************
 *
 * Function Name : cmac_init
 * Description   : LTC INITIALIZE session. In context struct we have the input key.
 *                 The LTC output context is stored into context struct.
 *
 *END**************************************************************************/
static void cmac_init(ltc_drv_hash_ctx *ctx)
{
    uint8_t *key;
    uint32_t keySize;
    uint32_t instance;
        
    /*
     *  word[kLtcCmacCtxKeySize] = key_length
     *  word[1-8] = key
     */
    keySize = ctx->word[kLtcHashCtxKeySize];
    key = (uint8_t*)&ctx->word[kLtcHashCtxKeyStartIdx];
    instance = ctx->instance;
        
    /* set LTC mode register to INITIALIZE */
    ltc_drv_symmetric_init(instance,
                           key,
                           keySize,
                           kLTCAlgorithm_AES,
                           (ltc_hal_mode_symmetric_alg_t)ctx->algo,
                           kLTCMode_Encrypt);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : cmac_restore_context
 * Description   : Restore LTC context from context struct.
 *
 *END**************************************************************************/
static void cmac_restore_context(ltc_drv_hash_ctx *ctx)
{
    uint32_t sz;
    uint32_t key_size;
    uint32_t instance;
    
    instance = ctx->instance;
    
    if (ctx->algo == kLtcXcbcMac)
    {
        /* 
        *  word[0-3] = mac
        *  word[3-7] = k3
        *  word[8-11] = k2        
        */
        sz = 12*sizeof(uint32_t);
    }
    else /* kFSLCMAC */
    {
        /* 
        *  word[0-3] = mac
        *  word[3-7] = L */
        sz = 8*sizeof(uint32_t);
    }
    LTC_HAL_SetContext(g_ltcBase[instance], (const uint8_t*)&ctx->word[0], sz, 0);
    
    /*
     *  word[12-19] = key
     *  word[kLtcCmacCtxKeySize] = keySize
     */
    LTC_HAL_ClearWritten(g_ltcBase[instance], kLTCClear_Key);
    LTC_HAL_SetKeySize(g_ltcBase[instance], 0);

    key_size = ctx->word[kLtcHashCtxKeySize];
    /* Write the key in place. */
    LTC_HAL_SetKey(g_ltcBase[instance], (const uint8_t*) &ctx->word[kLtcHashCtxKeyStartIdx], key_size);

    /* Write the key size.  This must be done after writing the key, and this
     * action locks the ability to modify the key registers. */    
    LTC_HAL_SetKeySize(g_ltcBase[instance], key_size);    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : cmac_save_context
 * Description   : Save LTC context to context struct.
 *
 *END**************************************************************************/
static void cmac_save_context(ltc_drv_hash_ctx *ctx)
{
    uint32_t sz;
    uint32_t instance;
    
    instance = ctx->instance;
    
    if (ctx->algo == kLtcXcbcMac)
    {
        /* 
        *  word[0-3] = mac
        *  word[3-7] = k3
        *  word[8-11] = k2        
        *  word[kLtcCmacCtxKeySize] = keySize
        */
        sz = 12*sizeof(uint32_t);
    }
    else /* kFSLCMAC */
    {
        /* 
        *  word[0-3] = mac
        *  word[3-7] = L */
        sz = 8*sizeof(uint32_t);
    }
    LTC_HAL_GetContext(g_ltcBase[instance], (uint8_t*)&ctx->word[0], sz, 0);
    
    /* 
     * word[12-19] = key */
    LTC_HAL_GetKey(g_ltcBase[instance], (uint8_t*)&ctx->word[kLtcHashCtxKeyStartIdx], ctx->word[kLtcHashCtxKeySize]);    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : move_cmac_block_to_ltc_ififo
 * Description   : Function that moves data from the fsl_cmac_block to LTC Input FIFO.
 *
 *END**************************************************************************/
static void move_cmac_block_to_ltc_ififo(uint32_t instance, const ltc_drv_hash_block *blk, int num_bytes)
{
    int i = 0;
    int words;
    
    words = num_bytes / 4;
    if ((num_bytes % 4) || ((num_bytes>0) && (num_bytes<4)))
    {
        words++;
    }
    
    if((words<0) || (words>4))
    {
        words = 4;
    }
    
    while(i<words)
    { 
        if(!LTC_HAL_InputFIFOFull(g_ltcBase[instance])) 
        {
            /* Copy data to the input FIFO. */                
            LTC_HAL_WriteInputFIFO(g_ltcBase[instance], blk->w[i++]);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : cmac_move_to_ififo
 * Description   : Function that moves data from aad or iv string to LTC Input FIFO in 16 byte chunks.
 *                 Last 16 bytes block is kept in context struct.
 *
 *END**************************************************************************/
static void cmac_move_to_ififo(ltc_drv_hash_ctx *ctx, const uint8_t *data, uint32_t dataSize)
{
    while (dataSize)
    {
        if (dataSize >= sizeof(ctx->blk))
        {
            memcpy(&ctx->blk, data, sizeof(ctx->blk));
            move_cmac_block_to_ltc_ififo(ctx->instance, &ctx->blk, sizeof(ctx->blk));
            dataSize-=sizeof(ctx->blk);
            data+=sizeof(ctx->blk);            
        }
        else 
        {
            /* last incomplete 16-bytes block of this message chunk */
            memset(&ctx->blk, 0, sizeof(ctx->blk));
            memcpy(&ctx->blk, data, dataSize);
            ctx->blksz = dataSize;
            dataSize = 0;
        }        
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : cmac_merge_and_flush_buf
 * Description   : Functions that merges the data with the context struct. If it results in full block, 
 *                 the block is moved into LTC. Return value is the number of bytes consumed by the merge.
 *
 *END**************************************************************************/
static uint32_t cmac_merge_and_flush_buf(ltc_drv_hash_ctx *ctx, const uint8_t *input, uint32_t inputSize, ltc_hal_mode_t mode_reg)
{
    uint32_t sz;
    uint32_t instance;
    
    instance = ctx->instance;
    sz = 0;
    if (ctx->blksz)
    {
        sz = sizeof(ctx->blk)-ctx->blksz;
        if (sz > inputSize)
        {
            sz = inputSize;
        }
        memcpy(ctx->blk.b + ctx->blksz, input, sz);
        input += sz;
        inputSize -= sz;
        ctx->blksz += sz;
        
        if (ctx->blksz == sizeof(ctx->blk))
        {
            LTC_HAL_SetDataSize(g_ltcBase[instance], sizeof(ctx->blk));
            move_cmac_block_to_ltc_ififo(instance, &ctx->blk, sizeof(ctx->blk));
            ctx->blksz = 0;
            
            ltc_drv_wait(instance);

            /* if there is still inputSize left, make sure LTC alg.state is set to UPDATE and continue */
            if (inputSize)
            {
                LTC_HAL_ModeSetAlgorithmState(&mode_reg, kLTCMode_AS_Update);
                LTC_HAL_WriteMode(g_ltcBase[instance], mode_reg);
            }
        }
    }
    return sz;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : cmac_move_to_context
 * Description   : Last 16 bytes block is kept in context struct.
 *                 
 *
 *END**************************************************************************/
static void cmac_move_to_context(ltc_drv_hash_ctx *ctx, const uint8_t *data, uint32_t dataSize, ltc_hal_mode_t mode_reg)
{
    while (dataSize)
    {
        if (dataSize > sizeof(ctx->blk))
        {
            dataSize-=sizeof(ctx->blk);
            data+=sizeof(ctx->blk);            
        }
        else 
        {
            if (dataSize + ctx->blksz > sizeof(ctx->blk))
            {
                uint32_t sz;
                sz = cmac_merge_and_flush_buf(ctx, data, dataSize, mode_reg);
                data += sz;
                dataSize -= sz;
            }
            /* last incomplete 16-bytes block of this message chunk */
            memset(&ctx->blk, 0, sizeof(ctx->blk));
            memcpy(&ctx->blk, data, dataSize);
            ctx->blksz = dataSize;
            dataSize = 0;
        }        
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : cmac_process_input_data
 * Description   : Function that merges incomplete block from previous run, 
 *                 then moves data from this message chunk into the LTC.
 *                 Last 16 bytes block is kept in context struct.
 *
 *END**************************************************************************/
static void cmac_process_input_data(ltc_drv_hash_ctx *ctx, const uint8_t *input, uint32_t inputSize, ltc_hal_mode_t mode_reg)
{
    uint32_t sz;
    uint32_t instance;
    
    instance = ctx->instance;
    
    /* fill context struct blk and flush to LTC ififo in case it is full 16-bytes */
    sz = cmac_merge_and_flush_buf(ctx, input, inputSize, mode_reg);
    input += sz;
    inputSize -= sz;
    
    /* if there is still more than or equal to 16 bytes, move each 16 bytes through LTC */
    sz = FSL_LTC_FIFO_SZ_MAX_DOWN_ALGN;
    while (inputSize)
    {
        if (inputSize < sz) 
        {
            uint32_t lastSize;
            
            lastSize = inputSize % 16;
            if (lastSize == 0)
            {
                lastSize = 16;
            }
            inputSize-=lastSize;
            if (inputSize)
            {
                /* move all complete 16-bytes blocks to ififo. */
                LTC_HAL_SetDataSize(g_ltcBase[instance], inputSize);
                cmac_move_to_ififo(ctx, input, inputSize);
                
                ltc_drv_wait(instance);

                input += inputSize;
            }
            /* keep last (in)complete 16-bytes block in context struct. */
            /* when 3rd argument of cmac_move_to_ififo() is <= 16 bytes, it only stores the data to context struct */
            cmac_move_to_context(ctx, input, lastSize, mode_reg);
            inputSize = 0;
        }
        else
        {
            LTC_HAL_SetDataSize(g_ltcBase[instance], sz);
            cmac_move_to_ififo(ctx, input, sz);
            inputSize-=sz;
            input+=sz;

            ltc_drv_wait(instance);

            LTC_HAL_ModeSetAlgorithmState(&mode_reg, kLTCMode_AS_Update);
            LTC_HAL_WriteMode(g_ltcBase[instance], mode_reg);
        }
    } /* end while */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : cmac_prepare_context_switch
 * Description   : This function prepares the LTC module for switch between jobs.
 *
 *END**************************************************************************/
static void cmac_prepare_context_switch(uint32_t instance)
{
    LTC_HAL_ClearWritten(g_ltcBase[instance],kLTCClear_DataSize);
    LTC_HAL_ClearWritten(g_ltcBase[instance],kLTCClear_Mode);
    LTC_HAL_ClearDoneInterruptStatus(g_ltcBase[instance]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_hash_init
 * Description   : Initialize CMAC context.
 * 
 * This function initialize the CMAC with a given key, and selects a block
 * cipher to use.
 *
 * For XCBC-MAC, the key length must be 16. For CMAC, the key length can be
 * the standard AES 16, 24, or 32.
 *
 * ctx Input memory to be used for CMAC context.
 * algo Block cipher algorithm to use for CMAC creation
 * key Input key
 * keySize Size of input key in bytes
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_hash_init(uint32_t instance,
                               ltc_drv_hash_ctx *ctx,
                               ltc_drv_hash_algo algo,
                               const uint8_t *key,
                               uint32_t keySize)
{
    if ((NULL == ctx) || (NULL == key))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    if ((algo != kLtcXcbcMac) && (algo != kLtcCMAC))
    {
        return kStatus_LTC_InvalidInput;
    }
    /* set algorithm in context struct for later use */
    ctx->algo = algo;
    
    /* check keySize */
    if (!ltc_drv_check_key_size(keySize))
    {
        return kStatus_LTC_InvalidKeyLength;
    }
    
    /* store input key and key length in context struct for later use */
    ctx->word[kLtcHashCtxKeySize] = keySize;
    memcpy(&ctx->word[kLtcHashCtxKeyStartIdx], key, keySize);
    
    ctx->blksz = 0;
    memset(&ctx->blk, 0, sizeof(ctx->blk));
    
    ctx->state = kLtcHashInit;
    ctx->instance = instance;
    
    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_hash_update
 * Description   : Add data to current CMAC. 
 *
 * This can be called repeatedly with an arbitrary amount of data to be
 * hashed.
 *
 * ctx Input CMAC context
 * input Input data
 * inputSize Size of input data in bytes.
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_hash_update(ltc_drv_hash_ctx *ctx,
                                 const uint8_t *input,
                                 uint32_t inputSize)
{
    bool update_state;
    ltc_hal_mode_t mode_reg; /* read and write LTC mode register */ 
    uint32_t instance;
    ltc_status_t status;

    if ((NULL == ctx) || (NULL == input))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    if ((ctx->algo != kLtcXcbcMac) && (ctx->algo != kLtcCMAC))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    instance = ctx->instance;
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    update_state = ctx->state == kLtcHashUpdate;
    ltc_drv_lock(instance);
    if (ctx->state == kLtcHashInit)
    {
        /* set LTC mode register to INITIALIZE job */
        cmac_init(ctx);
        ctx->state = kLtcHashUpdate;
        update_state = true;
        mode_reg = LTC_HAL_ReadMode(g_ltcBase[instance]);
                
        LTC_HAL_SetDataSize(g_ltcBase[instance], 0);    

        ltc_drv_wait(instance);
    }
    else if (update_state)
    {
        /* restore LTC context from context struct */
        cmac_restore_context(ctx);
    }
    
    if (update_state)
    {
    /* set LTC mode register to UPDATE job */
        cmac_prepare_context_switch(instance);
        mode_reg = 0u;
        LTC_HAL_ClearWritten(g_ltcBase[instance],kLTCClear_DataSize);
        LTC_HAL_ModeSetAlgorithm(&mode_reg, kLTCAlgorithm_AES);
        LTC_HAL_ModeSetAlgorithmState(&mode_reg, kLTCMode_AS_Update);
        LTC_HAL_ModeSetSymmetricAlg(&mode_reg, (ltc_hal_mode_symmetric_alg_t)ctx->algo);    
        /* Write the mode register to the hardware. */
        LTC_HAL_WriteMode(g_ltcBase[instance], mode_reg);
        cmac_process_input_data(ctx, input, inputSize, mode_reg);
        
        /* save LTC context to context struct */
        cmac_save_context(ctx);
    }
    
    status = ltc_drv_return_status(instance);

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_hash_finish
 * Description   : Finalize hashing
 *
 * Outputs the final hash and erases the context.
 *
 * ctx Input hash context
 * output Output hash data
 * outputSize Output param storing the size of the output hash in bytes
 *
 *END**************************************************************************/ 
ltc_status_t LTC_DRV_hash_finish(ltc_drv_hash_ctx *ctx,
                                 uint8_t *output,
                                 uint32_t *outputSize)
{
    ltc_hal_mode_t mode_reg; /* read and write LTC mode register */
    uint32_t instance;
    ltc_status_t status;    

    if ((NULL == ctx) || (NULL == output) || (NULL == outputSize))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    if ((ctx->algo != kLtcXcbcMac) && (ctx->algo != kLtcCMAC))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    instance = ctx->instance;
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }

    ltc_drv_lock(instance);
    
    cmac_prepare_context_switch(instance);
    
    mode_reg = 0u;
    LTC_HAL_ClearWritten(g_ltcBase[instance],kLTCClear_DataSize);
    LTC_HAL_ModeSetAlgorithm(&mode_reg, kLTCAlgorithm_AES);
    LTC_HAL_ModeSetAlgorithmState(&mode_reg, kLTCMode_AS_Finalize);
    LTC_HAL_ModeSetSymmetricAlg(&mode_reg, (ltc_hal_mode_symmetric_alg_t)ctx->algo);    
    /* Write the mode register to the hardware. */
    LTC_HAL_WriteMode(g_ltcBase[instance], mode_reg);
        
    /* restore LTC context from context struct */
    cmac_restore_context(ctx);
    
    /* flush message last incomplete block, if there is any, or write zero to data size register. */
    LTC_HAL_SetDataSize(g_ltcBase[instance], ctx->blksz);
    move_cmac_block_to_ltc_ififo(instance, &ctx->blk, ctx->blksz);
    

    status = ltc_drv_wait(instance);

    if (*outputSize > 16u)
    {
        *outputSize = 16u;
    }
    LTC_HAL_GetContext(g_ltcBase[instance], &output[0], *outputSize, 0);
    memset(ctx, 0, sizeof(*ctx));

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name :  LTC_DRV_hash
 * Description   :  Create HASH on given data
 *
 * Peform the full CMAC keyed hash in one function call.
 *
 * algo Block cipher algorithm to use for HASH creation
 * input Input data
 * inputSize Size of input data in bytes
 * key Input key
 * keySize Size of input key in bytes
 * output Output hash data
 * outputSize Output param storing the size of the output hash in bytes
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_hash(uint32_t instance,
                          ltc_drv_hash_algo algo,
                          const uint8_t *input,
                          uint32_t inputSize,
                          const uint8_t *key,
                          uint32_t keySize,
                          uint8_t *output,
                          uint32_t *outputSize)
{
    ltc_drv_hash_ctx ctx;
    ltc_status_t retval;
    
    retval = LTC_DRV_hash_init(instance, &ctx, algo, key, keySize);
    if (kStatus_LTC_Success != retval)
    {
        return retval;
    }    
    
    LTC_DRV_hash_update(&ctx, input, inputSize);
    LTC_DRV_hash_finish(&ctx, output, outputSize);
    memset(&ctx, 0, sizeof(ctx));
    return ltc_drv_return_status(instance);
}
