/*!
    \file    gd32f5xx_hau_sha_md5.c
    \brief   HAU_SHA_MD5 driver

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f5xx_hau.h"

#define SHAMD5_BSY_TIMEOUT    ((uint32_t)0x00010000U)

/* HAU SHA/MD5 digest read in HASH mode */
static void hau_sha_md5_digest_read(uint32_t algo, uint8_t *output);
/* HAU digest calculate process in HASH mode */
static ErrStatus hau_hash_calculate(uint32_t algo, uint8_t *input, uint32_t in_length, uint8_t *output);
/* HAU digest calculate process in HMAC mode */
static ErrStatus hau_hmac_calculate(uint32_t algo, uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t *output);

/*!
    \brief      calculate digest using SHA1 in HASH mode
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hau_hash_sha_1(uint8_t *input, uint32_t in_length, uint8_t output[])
{
    ErrStatus ret = ERROR;
    ret = hau_hash_calculate(HAU_ALGO_SHA1, input, in_length, output);
    return ret;
}

/*!
    \brief      calculate digest using SHA1 in HMAC mode
    \param[in]  key: pointer to the key used for HMAC
    \param[in]  keysize: length of the key used for HMAC
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hau_hmac_sha_1(uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t output[])
{
    ErrStatus ret = ERROR;
    ret = hau_hmac_calculate(HAU_ALGO_SHA1, key, keysize, input, in_length, output);
    return ret;
}

/*!
    \brief      calculate digest using SHA224 in HASH mode
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hau_hash_sha_224(uint8_t *input, uint32_t in_length, uint8_t output[])
{
    ErrStatus ret = ERROR;
    ret = hau_hash_calculate(HAU_ALGO_SHA224, input, in_length, output);
    return ret;
}

/*!
    \brief      calculate digest using SHA224 in HMAC mode
    \param[in]  key: pointer to the key used for HMAC
    \param[in]  keysize: length of the key used for HMAC
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hau_hmac_sha_224(uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t output[])
{
    ErrStatus ret = ERROR;
    ret = hau_hmac_calculate(HAU_ALGO_SHA224, key, keysize, input, in_length, output);
    return ret;
}

/*!
    \brief      calculate digest using SHA256 in HASH mode
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hau_hash_sha_256(uint8_t *input, uint32_t in_length, uint8_t output[])
{
    ErrStatus ret = ERROR;
    ret = hau_hash_calculate(HAU_ALGO_SHA256, input, in_length, output);
    return ret;
}

/*!
    \brief      calculate digest using SHA256 in HMAC mode
    \param[in]  key: pointer to the key used for HMAC
    \param[in]  keysize: length of the key used for HMAC
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hau_hmac_sha_256(uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t output[])
{
    ErrStatus ret = ERROR;
    ret = hau_hmac_calculate(HAU_ALGO_SHA256, key, keysize, input, in_length, output);
    return ret;
}

/*!
    \brief      calculate digest using MD5 in HASH mode
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hau_hash_md5(uint8_t *input, uint32_t in_length, uint8_t output[])
{
    ErrStatus ret = ERROR;
    ret = hau_hash_calculate(HAU_ALGO_MD5, input, in_length, output);
    return ret;
}

/*!
    \brief      calculate digest using MD5 in HMAC mode
    \param[in]  key: pointer to the key used for HMAC
    \param[in]  keysize: length of the key used for HMAC
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hau_hmac_md5(uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t output[])
{
    ErrStatus ret = ERROR;
    ret = hau_hmac_calculate(HAU_ALGO_MD5, key, keysize, input, in_length, output);
    return ret;
}

/*!
    \brief      HAU SHA/MD5 digest read
    \param[in]  algo: algorithm selection
    \param[out] output: the result digest
    \retval     none
*/
static void hau_sha_md5_digest_read(uint32_t algo, uint8_t *output)
{
    hau_digest_parameter_struct digest_para;
    uint32_t outputaddr = (uint32_t)output;  
  
    switch(algo){
    case HAU_ALGO_SHA1:        
        hau_digest_read(&digest_para);
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[0]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[1]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[2]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[3]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[4]);
        break;
    case HAU_ALGO_SHA224:
        hau_digest_read(&digest_para);
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[0]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[1]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[2]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[3]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[4]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[5]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[6]);
        break;
    case HAU_ALGO_SHA256:
        hau_digest_read(&digest_para);
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[0]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[1]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[2]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[3]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[4]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[5]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[6]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[7]);
        break;
    case HAU_ALGO_MD5:
        hau_digest_read(&digest_para);
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[0]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[1]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[2]);
        outputaddr += 4U;
        *(uint32_t*)(outputaddr)  = __REV(digest_para.out[3]);
        break;
    default:
        break;
    }
}

/*!
    \brief      HAU digest calculate process in HASH mode
    \param[in]  algo: algorithm selection
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
static ErrStatus hau_hash_calculate(uint32_t algo, uint8_t *input, uint32_t in_length, uint8_t *output)
{
    hau_init_parameter_struct init_para;
    
    __IO uint32_t num_last_valid = 0U;
    uint32_t i = 0U;
    __IO uint32_t counter = 0U;
    uint32_t busystatus = 0U;
    uint32_t inputaddr  = (uint32_t)input;

    /* number of valid bits in last word */
    num_last_valid = 8U * (in_length % 4U);

    /* HAU peripheral initialization */
    hau_deinit();

    /* HAU configuration */
    init_para.algo = algo;
    init_para.mode = HAU_MODE_HASH;
    init_para.datatype = HAU_SWAPPING_8BIT;
    hau_init(&init_para);

    /* configure the number of valid bits in last word of the message */
    hau_last_word_validbits_num_config(num_last_valid);

    /* write data to the IN FIFO */
    for(i = 0U; i < in_length; i += 4U){
        hau_data_write(*(uint32_t*)inputaddr);
        inputaddr += 4U;
    }

    /* enable digest calculation */
    hau_digest_calculation_enable();

    /* wait until the busy flag is reset */
    do{
        busystatus = hau_flag_get(HAU_FLAG_BUSY);
        counter++;
    }while((SHAMD5_BSY_TIMEOUT != counter) && (RESET != busystatus));

    if(RESET != busystatus){
        return ERROR;
    }else{
        /* read the message digest */
        hau_sha_md5_digest_read(algo, output);
    }
    return SUCCESS;
}

/*!
    \brief      HAU digest calculate process in HMAC mode
    \param[in]  algo: algorithm selection
    \param[in]  key: pointer to the key used for HMAC
    \param[in]  keysize: length of the key used for HMAC
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer
    \param[in]  output: the result digest
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
static ErrStatus hau_hmac_calculate(uint32_t algo, uint8_t *key, uint32_t keysize, uint8_t *input, uint32_t in_length, uint8_t *output)
{
    hau_init_parameter_struct init_para;

    __IO uint16_t num_last_valid = 0U;
    __IO uint16_t num_key_valid = 0U;
    uint32_t i = 0U;
    __IO uint32_t counter = 0U;
    uint32_t busystatus = 0U;
    uint32_t keyaddr    = (uint32_t)key;
    uint32_t inputaddr  = (uint32_t)input;

    /* number of valid bits in last word of the message */
    num_last_valid = 8U * (uint16_t)(in_length % 4U);
    /* number of valid bits in last word of the key */
    num_key_valid = 8U * (uint16_t)(keysize % 4U);

    /* HAU peripheral initialization */
    hau_deinit();

    /* HAU configuration */
    init_para.algo = algo;
    init_para.mode = HAU_MODE_HMAC;
    init_para.datatype = HAU_SWAPPING_8BIT;
    if(keysize > 64U){
        init_para.keytype = HAU_KEY_LONGGER_64;
    }else{
        init_para.keytype = HAU_KEY_SHORTER_64;
    }
    hau_init(&init_para);

    /* configure the number of valid bits in last word of the key */
    hau_last_word_validbits_num_config((uint32_t)num_key_valid);

    /* write the key */
    for(i = 0U; i < keysize; i += 4U){   
        hau_data_write(*(uint32_t*)keyaddr);
        keyaddr += 4U;
    }

    /* enable digest calculation */
    hau_digest_calculation_enable();

    /* wait until the busy flag is reset */
    do{
        busystatus = hau_flag_get(HAU_FLAG_BUSY);
        counter++;
    }while((SHAMD5_BSY_TIMEOUT != counter) && (RESET != busystatus));

    if(RESET != busystatus){
        return ERROR;
    }else{
        /* configure the number of valid bits in last word of the message */
        hau_last_word_validbits_num_config((uint32_t)num_last_valid);

        /* write data to the IN FIFO */
        for(i = 0U; i < in_length; i += 4U){
            hau_data_write(*(uint32_t*)inputaddr);
            inputaddr += 4U;
        }

        /* enable digest calculation */
        hau_digest_calculation_enable();

        /* wait until the busy flag is reset */
        counter = 0U;
        do{
            busystatus = hau_flag_get(HAU_FLAG_BUSY);
            counter++;
        }while((SHAMD5_BSY_TIMEOUT != counter) && (RESET != busystatus));

        if(RESET != busystatus){
            return ERROR;
        }else{
            /* configure the number of valid bits in last word of the key */
            hau_last_word_validbits_num_config((uint32_t)num_key_valid);

            /* write the key */
            keyaddr = (uint32_t)key;
            for(i = 0U; i < keysize; i += 4U){
                hau_data_write(*(uint32_t*)keyaddr);
                keyaddr += 4U;
            }

            /* enable digest calculation */
            hau_digest_calculation_enable();

            /* wait until the busy flag is reset */
            counter =0U;
            do{
                busystatus = hau_flag_get(HAU_FLAG_BUSY);
                counter++;
            }while((SHAMD5_BSY_TIMEOUT != counter) && (RESET != busystatus));

            if(RESET != busystatus){
                return ERROR;
            }else{
                /* read the message digest */
                hau_sha_md5_digest_read(algo, output);
            }
        }
    }
    return SUCCESS;
}
