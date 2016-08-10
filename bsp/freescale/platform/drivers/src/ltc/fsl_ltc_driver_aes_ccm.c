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

#define FSL_AES_CCM_TYPE_ENCRYPT 0
#define FSL_AES_CCM_TYPE_DECRYPT 1

/*FUNCTION**********************************************************************
 *
 * Function Name : swap_bytes
 * Description   : Function that does the byte swap of uint32_t.
 *                 Purpose is to obtain string of bytes with most significant byte being the first character.
 *
 *END**************************************************************************/
static uint32_t swap_bytes(uint32_t in)
{
    return (((in & 0x000000ffu) << 24) | ((in & 0x0000ff00u) << 8) |
            ((in & 0x00ff0000u) >> 8) | ((in & 0xff000000u) >> 24));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : aes_ccm_context_init
 * Description   : Function that moves computes B0 and CTR0 and writes it to the context.
 *
 *END**************************************************************************/
static void aes_ccm_context_init(uint32_t instance, 
                                 uint32_t inputSize,
                                 const uint8_t *iv,
                                 uint32_t ivSize,
                                 uint32_t aadSize,                                 
                                 uint32_t tagSize)
{
    ltc_drv_xcm_block_t blk;
    
    int q; /* octet length of binary representation of the octet length of the payload. computed as (15 - n), where n is length of nonce(=ivSize) */
    uint8_t flags; /* flags field in B0 and CTR0 */
    
    /* compute B0 */
    memset(&blk, 0, sizeof(blk));
    /* tagSize - size of output MAC */
    q = 15 - ivSize;
    flags = (uint8_t)(8*((tagSize-2)/2) + q - 1); /* 8*M' + L' */
    if (aadSize)
    {
        flags |= 0x40; /* Adata */
    }
    blk.b[0] = flags; /* flags field */
    blk.w[3] = swap_bytes(inputSize); /* message size, most significant byte first */
    memcpy(&blk.b[1], iv, ivSize);  /* nonce field */
    
    /* Write B0 data to the context register.
     */
    LTC_HAL_SetContext(g_ltcBase[instance], &blk.b[0], 16, 0);
    
    /* Write CTR0 to the context register.
     */
    memset(&blk, 0, sizeof(blk)); /* ctr(0) field = zero */
    blk.b[0] = q - 1; /* flags field */
    memcpy(&blk.b[1], iv, ivSize); /* nonce field */
    LTC_HAL_SetContext(g_ltcBase[instance], &blk.b[0], 16, 4);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : aes_ccm_process_aad
 * Description   : Function that computes B1 from AAD size and AAD data.
 *                 The B1 block is then moved into LTC IFIFO.
 *                 Return value is aad data size in last job. The job is shared with data. 
 *
 *END**************************************************************************/
static ltc_hal_mode_t aes_ccm_process_aad(uint32_t instance, 
                                uint32_t inputSize, 
                                const uint8_t *aad, 
                                uint32_t aadSize, 
                                ltc_hal_mode_t mode_reg)
{
    ltc_drv_xcm_block_t blk;
    uint32_t swapped; /* holds byte swap of uint32_t */
    ltc_hal_mode_t ret_mode;

    ret_mode = mode_reg;
        
    if (aadSize)
    {
        bool aad_only;
        bool aad_single_session;
        
        memset(&blk, 0, sizeof(blk));
        uint32_t sz = 0;
        
        aad_only = inputSize==0u;
        aad_single_session = (((aadSize+2)+15u)&0xfffffff0u) <= FSL_LTC_FIFO_SZ_MAX_DOWN_ALGN;
                
        /* limit by CCM spec: 2^16 - 2^8 = 65280 */
        
        /* encoding is two octets, msbyte first */
        swapped = swap_bytes(aadSize);
        memcpy(&blk.b[0], ((uint8_t*)&swapped)+sizeof(uint16_t), sizeof(uint16_t));
        
        sz=aadSize>14?14:aadSize;/* limit aad to the end of 16 bytes blk */
        memcpy(&blk.b[2], aad, sz); /* fill B1 with aad */
                
        if (aad_single_session)
        {
            LTC_HAL_SetAADSize(g_ltcBase[instance], (uint16_t)(aadSize+2), aad_only);
        /* move first AAD block (16 bytes block B1) to FIFO */
        ltc_drv_move_block_to_ltc_ififo(instance, &blk, sizeof(blk));
        }
        else
        {
            LTC_HAL_SetAADSize(g_ltcBase[instance], (uint16_t)16u, true);
            /* move first AAD block (16 bytes block B1) to FIFO */
            ltc_drv_move_block_to_ltc_ififo(instance, &blk, sizeof(blk));

            ltc_drv_wait(instance);
        }
                

        /* track consumed AAD. sz bytes have been moved to fifo. */
        aadSize-=sz;
        aad+=sz;
        
        if (aad_single_session)
        {
            /* move remaining AAD to FIFO, then return, to continue with MDATA */
            ltc_drv_move_to_ififo(instance, aad, aadSize);
        }
        else
        {
            while (aadSize)
            {
                ltc_drv_wait(instance);

                LTC_HAL_ModeSetAlgorithmState(&mode_reg, kLTCMode_AS_Update);
                ret_mode = mode_reg;
                LTC_HAL_WriteMode(g_ltcBase[instance], mode_reg);
                sz = FSL_LTC_FIFO_SZ_MAX_DOWN_ALGN;
                if (aadSize < sz)
                {
                    LTC_HAL_SetAADSize(g_ltcBase[instance], aadSize, aad_only);
                    ltc_drv_move_to_ififo(instance, aad, aadSize);
                    aadSize = 0;
                }
                else
                {
                    LTC_HAL_SetAADSize(g_ltcBase[instance], (uint16_t)sz, true);
                    ltc_drv_move_to_ififo(instance, aad, sz);
                    aadSize-=sz;
                    aad+=sz;
                }
            } /* end while */
        } /* end else */
    } /* end if */
    return ret_mode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : aes_ccm_check_input_args
 * Description   : Check input arguments of CCM APIs. 
 *
 *END**************************************************************************/
static ltc_status_t aes_ccm_check_input_args(uint32_t instance,
                                             const uint8_t *src, 
                                             const uint8_t *iv, 
                                             const uint8_t *key, 
                                             uint8_t *dst,
                                             uint32_t ivSize, 
                                             uint32_t aadSize, 
                                             uint32_t keySize, 
                                             uint32_t tagSize)
{
    if(!ltc_drv_check_instance(instance))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    /* tag can be NULL to skip tag processing */
    if ((!src) || (!iv) || (!key) || (!dst))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    /* size of Nonce (ivSize) must be element of 7,8,9,10,11,12,13 */
    if ((ivSize < 7u) || (ivSize > 13u))
    {
        return kStatus_LTC_InvalidInput;
    }
    /* octet length of MAC (tagSize) must be element of 4,6,8,10,12,14,16 for tag processing or zero to skip tag processing */
    if (((tagSize > 0) && (tagSize < 4u)) || (tagSize > 16u) || (tagSize&1u))
    {
        return kStatus_LTC_InvalidInput;
    }
    
    /* check if keySize is supported */
    if (!ltc_drv_check_key_size(keySize))
    {
        return kStatus_LTC_InvalidKeyLength;
    }
    
    /* LTC does not support more AAD than this */
    if (aadSize >= 65280u)
    {
        return kStatus_LTC_InvalidInput;
    }
    return kStatus_LTC_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : aes_ccm_process
 * Description   : CCM encrypt and decrypt are almost the same with the exception
 *                 during decrypt we compare the received MAC with the computed MAC.
 *
 *END**************************************************************************/
static ltc_status_t aes_ccm_process(uint32_t instance,
                                    int type, 
                                    const uint8_t *src,
                                    uint32_t inputSize,
                                    const uint8_t *iv,
                                    uint32_t ivSize,
                                    const uint8_t *aad,
                                    uint32_t aadSize,
                                    const uint8_t *key,
                                    uint32_t keySize,
                                    uint8_t *dst,
                                    uint8_t *tag,
                                    uint32_t tagSize)
{        
    ltc_hal_mode_encrypt_t encrypt_mode; /* encryption or decryption mode */
    ltc_status_t retval; /* return value */
    uint32_t max_ltc_fifo_sz; /* maximum data size that we can put to LTC FIFO in one session. 12-bit limit. */
    ltc_hal_mode_t mode_reg; /* read and write LTC mode register */
    
    bool single_ses_proc_all; /* aad and src data can be processed in one session */

    retval = aes_ccm_check_input_args(instance, src, iv, key, dst, ivSize, aadSize, keySize, tagSize);
    
    /* API input validation */
    if (kStatus_LTC_Success != retval)
    {
        return retval;
    }
        
    max_ltc_fifo_sz = 0xfffu; /* 12-bit field limit */
    
    /* Write value to LTC AADSIZE will be (aadSize+2) value. 
     * The value will be rounded up to next 16 byte boundary and added to Data Size register.
     * We then add inputSize to Data Size register. If the resulting Data Size is less than max_ltc_fifo_sz
     * then all can be processed in one session INITIALIZE/FINALIZE.
     * Otherwise, we have to split into multiple session, going through INITIALIZE, UPDATE (if required) and FINALIZE.
     */
    single_ses_proc_all = ( (((aadSize+2)+15u)&0xfffffff0u) + inputSize) <= max_ltc_fifo_sz;    
    //single_ses_proc_all = ( (aadSize <= 16) && (inputSize <= max_ltc_fifo_sz-16u));    
        
    /* Initialize algorithm state and key. */
    encrypt_mode = type==FSL_AES_CCM_TYPE_DECRYPT?kLTCMode_Decrypt:kLTCMode_Encrypt;
    
    /* setup key, algorithm and set the alg.state to INITIALIZE */
    if (single_ses_proc_all)
    {
        ltc_drv_symmetric_init_final(instance,
                                     key,
                                     keySize,
                                     kLTCAlgorithm_AES,
                                     kLTCMode_CCM,
                                     encrypt_mode);
    }
    else
    {
        ltc_drv_symmetric_init(instance,
                               key,
                               keySize,
                               kLTCAlgorithm_AES,
                               kLTCMode_CCM,
                               encrypt_mode);
    }
    mode_reg = LTC_HAL_ReadMode(g_ltcBase[instance]);
    
    /* Initialize LTC context for AES CCM: block B0 and initial counter CTR0 */
    aes_ccm_context_init(instance, inputSize, iv, ivSize, aadSize, tagSize);

    /* Process additional authentication data, if there are any.
     * Need to split the job into individual sessions of up to 4096 bytes, due to LTC IFIFO data size limit.
     */
    mode_reg = aes_ccm_process_aad(instance, inputSize, aad, aadSize, mode_reg);
    //mode_reg = LTC_HAL_ReadMode(g_ltcBase[instance]); /* aes_ccm_process_aad() might change the AS to UPDATE */
    
    /* Workaround for the LTC Data Size register update errata TKT261180 */
    if (inputSize)
    {
        while (16 < LTC_HAL_GetDataSize(g_ltcBase[instance]))
        {}
    }
    
    /* Process message */
    if (single_ses_proc_all)
    {
        ltc_drv_symmetric_process_data(instance, &src[0], inputSize, &dst[0]);
    }
    else
    {
        ltc_drv_symmetric_process_data_multiple(instance, &src[0], inputSize, &dst[0], mode_reg, kLTCMode_AS_Finalize);
    }
    
    retval = ltc_drv_aes_process_tag(instance, tag, tagSize, mode_reg, FSL_LTC_CCM_TAG_IDX);    
    
    /* return status */
    //retval = ltc_drv_return_status(instance);
        
    return retval;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_aes_encrypt_tag_ccm
 * Description   : 
 *
 * @brief Encrypt AES using CCM block mode
 *
 * @param plaintext Input plaintext to encrypt
 * @param inputSize Size of input data in bytes
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12 or 13.
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of aad. 
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Generated output hash.(CBC-MAC)
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4, 6, 8, 10, 12, 14 or 16.
 * @return Status from encrypt/decrypt operation
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_aes_encrypt_tag_ccm(uint32_t instance, 
                                         const uint8_t *plaintext,
                                         uint32_t inputSize,
                                         const uint8_t *iv,
                                         uint32_t ivSize,
                                         const uint8_t *aad,
                                         uint32_t aadSize,
                                         const uint8_t *key,
                                         uint32_t keySize,
                                         uint8_t *ciphertext,
                                         uint8_t *tag,
                                         uint32_t tagSize)
{
    ltc_status_t status;

    ltc_drv_lock(instance);

    status = aes_ccm_process(instance,
                           FSL_AES_CCM_TYPE_ENCRYPT,
                           plaintext,
                           inputSize,
                           iv,
                           ivSize,
                           aad,
                           aadSize,
                           key,
                           keySize,
                           ciphertext,
                           tag,
                           tagSize);

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);

    return status; 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LTC_DRV_aes_decrypt_tag_ccm
 * Description   : 
 *
 * @brief Decrypt AES using CCM block mode
 *
 * @param ciphertext Input ciphertext to decrypt
 * @param inputSize Size of input data in bytes
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12 or 13.
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of aad. 
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Received hash.(Received CBC-MAC)
 * @param tagSize Input size of the received hash to compare with the computed hash, in bytes. Must be 4, 6, 8, 10, 12, 14 or 16.
 * @return Status from encrypt/decrypt operation
 *
 *END**************************************************************************/
ltc_status_t LTC_DRV_aes_decrypt_tag_ccm(uint32_t instance,
                                         const uint8_t *ciphertext,
                                         uint32_t inputSize,
                                         const uint8_t *iv,
                                         uint32_t ivSize,
                                         const uint8_t *aad,
                                         uint32_t aadSize,
                                         const uint8_t *key,
                                         uint32_t keySize,
                                         uint8_t *plaintext,
                                         const uint8_t *tag,
                                         uint32_t tagSize)
{
    uint8_t         temp_tag[16] = {0}; /* max. octet length of MAC (tag) is 16 */
    uint8_t         *tag_ptr;
    ltc_status_t    status;
   
    tag_ptr = NULL;
    if (tag)
    {
        memcpy(temp_tag, tag, tagSize);
        tag_ptr = &temp_tag[0];
    }

    ltc_drv_lock(instance);

    status = aes_ccm_process(instance, 
                           FSL_AES_CCM_TYPE_DECRYPT,
                           ciphertext,
                           inputSize,
                           iv,
                           ivSize,
                           aad,
                           aadSize,
                           key,
                           keySize,
                           plaintext,
                           tag_ptr,
                           tagSize);

    ltc_drv_clear_all(instance, false);
    ltc_drv_unlock(instance);

    return status;
}

