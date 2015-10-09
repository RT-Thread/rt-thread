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

#if FSL_FEATURE_LTC_HAS_DPAMS
/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_SetDPAMaskSeed
 * Description :   Set DPA Mask Seed register.
 *
 * mask The DPA mask seed.
 *
 *END**************************************************************************/
void LTC_DRV_SetDPAMaskSeed(uint32_t instance, uint32_t mask)
{
    if(ltc_drv_check_instance(instance))
    {
        LTC_HAL_SetDPAMaskSeed(g_ltcBase[instance], mask);
        LTC_HAL_SetDPAMaskSeed(g_ltcBase[instance], mask); /* second write as workaround for DPA mask re-seed errata */
    }
}
#endif

static ltc_status_t ltc_drv_aes_decrypt_ecb(uint32_t instance,
                                     const uint8_t ciphertext[16],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     ltc_drv_aes_key_t keyType,
                                     uint8_t plaintext[16]);

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_aes_generate_decrypt_key
 * Description   :Transform AES encrypt key (forward AES) into decrypt key (inverse AES).
 *
 * The key derived by this function can be further used as direct load decrypt key
 * for AES ECB and CBC decryption operations (keyType argument).
 * 
 * encryptKey Input key to use for decrypt key transformation
 * decryptKey Output key, the decrypt form of the AES key.
 * keySize Size of the input key and output key, in bytes. Must be 16, 24, or 32.
 * Returns status from key generation operation
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_aes_generate_decrypt_key(uint32_t instance, 
                                              const uint8_t *encryptKey,
                                              uint8_t *decryptKey,
                                              uint32_t keySize)
{
    uint8_t         plaintext[16];
    uint8_t         ciphertext[16];
    ltc_status_t    status;
    
    if (!ltc_drv_check_key_size(keySize))
    {
        return kStatus_LTC_InvalidKeyLength;
    }
    
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }

    ltc_drv_lock(instance);

    /* ECB decrypt with encrypt key will convert the key in LTC context into decrypt form of the key */
    ltc_drv_aes_decrypt_ecb(instance, ciphertext, encryptKey, keySize, kLtcEncryptKey, plaintext);
    /* now there is decrypt form of the key in the LTC context, so take it */
    ltc_drv_get_key(instance, decryptKey, keySize);
    
    status = ltc_drv_return_status(instance);

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_aes_encrypt_ecb
 * Description   : 
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_aes_encrypt_ecb(uint32_t instance, 
                                     const uint8_t plaintext[16],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     uint8_t ciphertext[16])
{
    ltc_status_t retval;
    
    if (!ltc_drv_check_key_size(keySize))
    {
        return kStatus_LTC_InvalidKeyLength;
    }
    
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }

    ltc_drv_lock(instance);

    /* Initialize algorithm state. */
    ltc_drv_symmetric_update(instance, 
                            key,
                            keySize,
                            kLTCAlgorithm_AES,
                            kLTCMode_ECB,
                            kLTCMode_Encrypt);

    /* Process data and return status. */
    retval = ltc_drv_symmetric_process_data(instance, &plaintext[0], 16, &ciphertext[0]);
    if (kStatus_LTC_Success == retval)
    {
        retval = ltc_drv_return_status(instance);
    }

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);

    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_aes_decrypt_ecb
 * Description   : 
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_aes_decrypt_ecb(uint32_t instance,
                                     const uint8_t ciphertext[16],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     ltc_drv_aes_key_t keyType,
                                     uint8_t plaintext[16])
{
    ltc_status_t status;
    
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }
 
    ltc_drv_lock(instance);

    status = ltc_drv_aes_decrypt_ecb(instance, ciphertext, key, keySize, keyType, plaintext);

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);    

    return status;
}

static ltc_status_t ltc_drv_aes_decrypt_ecb(uint32_t instance,
                                     const uint8_t ciphertext[16],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     ltc_drv_aes_key_t keyType,
                                     uint8_t plaintext[16])
{
    ltc_status_t retval;
    
    if (!ltc_drv_check_key_size(keySize))
    {
        return kStatus_LTC_InvalidKeyLength;
    }
    /* Initialize algorithm state. */
    ltc_drv_symmetric_update(instance,
                            key,
                            keySize,
                            kLTCAlgorithm_AES,
                            kLTCMode_ECB,
                            kLTCMode_Decrypt);
    
    /* set DK bit in the LTC Mode Register AAI field for directly loaded decrypt keys */
    if (keyType == kLtcDecryptKey)
    {
        LTC_HAL_ModeSetDecryptKey(g_ltcBase[instance]);
    }

    /* Process data and return status. */
    retval = ltc_drv_symmetric_process_data(instance, &ciphertext[0], 16, &plaintext[0]);
    if (kStatus_LTC_Success == retval)
    {
        retval = ltc_drv_return_status(instance);
    }
    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_aes_encrypt_cbc
 * Description   : 
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_aes_encrypt_cbc(uint32_t instance,
                                     const uint8_t *plaintext,
                                     uint32_t inputSize,
                                     uint8_t iv[LTC_AES_IV_SIZE],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     uint8_t *ciphertext)
{
    ltc_status_t retval;
    
    if (!ltc_drv_check_key_size(keySize))
    {
        return kStatus_LTC_InvalidKeyLength;
    }
    
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    /* CBC mode, inputSize must be 16-byte multiple */
    if ((inputSize < 16u) || (inputSize % 16u))
    {
        return kStatus_LTC_InvalidDataLength;
    }

    ltc_drv_lock(instance);    

    /* Initialize algorithm state. */
    ltc_drv_symmetric_update(instance,
                            key,
                            keySize,
                            kLTCAlgorithm_AES,
                            kLTCMode_CBC,
                            kLTCMode_Encrypt);

    /* Write IV data to the context register. */
    LTC_HAL_SetContext(g_ltcBase[instance], &iv[0], LTC_AES_IV_SIZE, 0);

    /* Process data and return status. */
    retval = ltc_drv_process_message_in_sessions(instance, &plaintext[0], inputSize, &ciphertext[0]);
    if (kStatus_LTC_Success == retval)
    {
        retval = ltc_drv_return_status(instance);
    }

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);

    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_aes_decrypt_cbc
 * Description   : 
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_aes_decrypt_cbc(uint32_t instance,
                                     const uint8_t *ciphertext,
                                     uint32_t inputSize,
                                     uint8_t iv[LTC_AES_IV_SIZE],
                                     const uint8_t *key,
                                     uint32_t keySize,
                                     ltc_drv_aes_key_t keyType,
                                     uint8_t *plaintext)
{
    ltc_status_t retval;
    
    if (!ltc_drv_check_key_size(keySize))
    {
        return kStatus_LTC_InvalidKeyLength;
    }
    
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    /* CBC mode, inputSize must be 16-byte multiple */
    if ((inputSize < 16u) || (inputSize % 16u))
    {
        return kStatus_LTC_InvalidDataLength;
    }

    ltc_drv_lock(instance);    

    /* set DK bit in the LTC Mode Register AAI field for directly loaded decrypt keys */
    if (keyType == kLtcDecryptKey)
    {
        LTC_HAL_ModeSetDecryptKey(g_ltcBase[instance]);
    }
    
    /* Initialize algorithm state. */
    ltc_drv_symmetric_update(instance,
                            key,
                            keySize,
                            kLTCAlgorithm_AES,
                            kLTCMode_CBC,
                            kLTCMode_Decrypt);

    /* Write IV data to the context register. */
    LTC_HAL_SetContext(g_ltcBase[instance], &iv[0], LTC_AES_IV_SIZE, 0);

    /* Process data and return status. */
    retval = ltc_drv_process_message_in_sessions(instance, &ciphertext[0], inputSize, &plaintext[0]);
    if (kStatus_LTC_Success == retval)
    {
        retval = ltc_drv_return_status(instance);
    }

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);

    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_ctr
 * Description   : 
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_ctr(uint32_t instance, 
                         const uint8_t *input,
                         uint32_t inputSize,
                         uint8_t counter[16],
                         const uint8_t *key,
                         uint32_t keySize,
                         uint8_t *output,
                         uint8_t counterlast[16],
                         uint32_t *szLeft,
                         ltc_hal_mode_encrypt_t enc)
{
    ltc_status_t retval;
    uint32_t lastSize;
    
    if (!ltc_drv_check_key_size(keySize))
    {
        return kStatus_LTC_InvalidKeyLength;
    }
    
    lastSize = 0;
    if (counterlast != NULL)
    {
        /* Split the inputSize into full 16-byte chunks and last incomplete block due to LTC AES OFIFO errata */
        if (inputSize <= 16u)
        {        
            
            lastSize = inputSize;
            inputSize = 0;
        }
        else
        {   
            /* Process all 16-byte data chunks. */
            lastSize = inputSize % 16u;
            if (lastSize == 0)
            {
                lastSize = 16;
                inputSize -= 16;
            }
            else
            {
               inputSize -= lastSize; /* inputSize will be rounded down to 16 byte boundary. remaining bytes in lastSize */           
            }
        }
    }
    
    /* Initialize algorithm state. */
    ltc_drv_symmetric_update(instance,
                            key,
                            keySize,
                            kLTCAlgorithm_AES,
                            kLTCMode_CTR,
                            enc);

    /* Write initial counter data to the context register.
     * NOTE the counter values start at 4-bytes offset into the context. */
    LTC_HAL_SetContext(g_ltcBase[instance], &counter[0], 16, 4);

    /* Process data and return status. */
    retval = ltc_drv_process_message_in_sessions(instance, input, inputSize, output);
    if (kStatus_LTC_Success != retval)
    {
        return retval;
    }
    
    retval = ltc_drv_return_status(instance);
    if (kStatus_LTC_Success != retval)
    {
        return retval;
    }
    
    input += inputSize;
    output += inputSize;    
    
    if ((counterlast != NULL) && lastSize)
    {
        const uint8_t zeroes[16] = {0};
        ltc_hal_mode_t modeReg;
        
        modeReg = 0;
        LTC_HAL_ModeSetAlgorithm(&modeReg, kLTCAlgorithm_AES);
        LTC_HAL_ModeSetEncrypt(&modeReg, enc);
        LTC_HAL_ModeSetAlgorithmState(&modeReg, kLTCMode_AS_Finalize);
        LTC_HAL_ModeSetSymmetricAlg(&modeReg, kLTCMode_CTR);

        /* Write the mode register to the hardware. */
        LTC_HAL_WriteMode(g_ltcBase[instance], modeReg);
                            
        /* context is re-used (CTRi) */
        
        /* Process data and return status. */
        retval = ltc_drv_symmetric_process_data(instance, input, lastSize, output);
        if (szLeft)
        {
            *szLeft = 16 - lastSize;
        }
        
        /* Initialize algorithm state. */
        LTC_HAL_ModeSetAlgorithmState(&modeReg, kLTCMode_AS_Update);
        LTC_HAL_WriteMode(g_ltcBase[instance], modeReg);
                            
        /* context is re-used (CTRi) */
        
        /* Process data and return status. */
        retval = ltc_drv_symmetric_process_data(instance, zeroes, 16, counterlast);
    }
    
    LTC_HAL_GetContext(g_ltcBase[instance], &counter[0], 16, 4);
    LTC_HAL_ClearWritten(g_ltcBase[instance], kLTCClear_All);
    
    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_aes_ctr
 * Description   : Encrypt or decrypt AES using CTR block mode
 *
 * AES CTR mode uses only forward AES cipher and same algorithm for encryption and decrytption.
 * The only difference between encryption and decryption is that for encryption the input argument
 * is plaintext and the output argument is ciphertext, for decryption the input argument is ciphertext
 * and the output argument is plaintext.
 *
 * param instance LTC module instance number.
 * param input Input data for CTR block mode
 * param inputSize Size of input data in bytes
 * param[in,out] counter Input counter (updates on return)
 * param key Input key to use for forward AES cipher
 * param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * param[out] output Ouput data for CTR block mode
 * param[out] counterlast Output cipher of counter, for chained CTR calls. NULL can be passed chained calls are not used.
 * param[out] szLeft Output number of bytes in left unused in counterlast block. 
 * return Status from encrypt/decrypt operation
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_aes_ctr(uint32_t instance,
                             const uint8_t *input,
                             uint32_t inputSize,
                             uint8_t counter[16],
                             const uint8_t *key,
                             uint32_t keySize,
                             uint8_t *output,
                             uint8_t counterlast[16],
                             uint32_t *szLeft)
{
    ltc_status_t retval;
    
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    ltc_drv_lock(instance);
    retval =  ltc_drv_ctr(instance,
                          input,
                          inputSize,
                          counter,
                          key,
                          keySize,
                          output,
                          counterlast,
                          szLeft,
                          kLTCMode_Encrypt);

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);

    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_move_block_to_ltc_ififo
 * Description   : Function that moves data from the ltc_drv_xcm_block_t to LTC Input FIFO.
 *
 *END**************************************************************************/
void ltc_drv_move_block_to_ltc_ififo(uint32_t instance, const ltc_drv_xcm_block_t *blk, int num_bytes)
{
    int i = 0;
    int words;
    
    words = num_bytes / 4;
    if (words % 4) 
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
 * Function Name : ltc_drv_move_to_ififo
 * Description   : Function that moves data from aad or iv string to LTC Input FIFO in 16 byte chunks.
 *                 Last 16 bytes block is padded with zeroes.
 *
 *END**************************************************************************/
void ltc_drv_move_to_ififo(uint32_t instance, const uint8_t *data, uint32_t dataSize)
{
    ltc_drv_xcm_block_t blk;
    
    while (dataSize)
    {
        if (dataSize > 16u)
        {
            memcpy(&blk, data, 16);
            dataSize-=16u;
            data+=16u;            
        }
        else 
        {
            memset(&blk, 0, sizeof(blk));
            memcpy(&blk, data, dataSize);
            dataSize = 0;
        }
        ltc_drv_move_block_to_ltc_ififo(instance, &blk, sizeof(blk));
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_aes_received_mac_compare
 * Description   : Compare received MAC with the computed MAC.
 *                 
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_aes_received_mac_compare(uint32_t instance, 
                                      const uint8_t *tag, 
                                      uint32_t tagSize, 
                                      ltc_hal_mode_t mode_reg)
{
    ltc_drv_xcm_block_t blk;
    
    LTC_HAL_ClearWritten(g_ltcBase[instance],kLTCClear_DataSize);
    LTC_HAL_ClearDoneInterruptStatus(g_ltcBase[instance]);
    LTC_HAL_ModeSetAlgorithmState(&mode_reg, kLTCMode_AS_Update);
    LTC_HAL_ModeSetICVTest(&mode_reg, kLTCMode_ICV_Compare);
    /* Write the mode register to the hardware. */
    LTC_HAL_WriteMode(g_ltcBase[instance], mode_reg);
    
    LTC_HAL_SetDataSize(g_ltcBase[instance], 0);
    LTC_HAL_SetICVSize(g_ltcBase[instance], tagSize);
    memset(&blk, 0, sizeof(blk));
    memcpy(&blk.b[0],&tag[0],tagSize);
    
    ltc_drv_move_block_to_ltc_ififo(instance, &blk, tagSize);
    
    return ltc_drv_wait(instance);

}

/*FUNCTION**********************************************************************
 *
 * Function Name : ltc_drv_aes_process_tag
 * Description   : Process tag (compare tag on decryption or compute tag on encryption)
 *
 *END**************************************************************************/
ltc_status_t ltc_drv_aes_process_tag(uint32_t instance, uint8_t *tag, uint32_t tagSize, ltc_hal_mode_t mode_reg, uint32_t ctx)
{
    ltc_status_t status = kStatus_LTC_Success;
    if (tag)
    {
        /* For decrypt, compare received MAC with the computed MAC. */
        if (kLTCMode_Decrypt == LTC_HAL_ModeGetEncrypt(&mode_reg))
        {
        status = ltc_drv_aes_received_mac_compare(instance, tag, tagSize, mode_reg);
        }
        else /* FSL_AES_GCM_TYPE_ENCRYPT */
        {
            /* For encryption, write the computed and encrypted MAC to user buffer */
            LTC_HAL_GetContext(g_ltcBase[instance], &tag[0], tagSize, ctx);
        }
	}
    return status;
    
}
