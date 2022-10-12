/*!
    \file    gd32f20x_cau_aes.c
    \brief   CAU_AES driver

    \version 2015-07-15, V1.0.0, firmware for GD32F20x
    \version 2017-06-05, V2.0.0, firmware for GD32F20x
    \version 2018-10-31, V2.1.0, firmware for GD32F20x
    \version 2020-09-30, V2.2.0, firmware for GD32F20x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#include "gd32f20x_cau.h"

#define AESBSY_TIMEOUT    ((uint32_t)0x00010000U)

/* AES key structure parameter config */
static void cau_aes_key_config(uint8_t *key, uint16_t keysize, cau_key_parameter_struct* cau_key_initpara);
/* AES calculate process */
static ErrStatus cau_aes_calculate(uint8_t *input, uint32_t in_length, uint8_t *output);

/*!
    \brief      encrypt and decrypt using AES in ECB mode
    \param[in]  algo_dir: algorithm direction
                only one parameter can be selected which is shown as below
      \arg        CAU_ENCRYPT: encrypt
      \arg        CAU_DECRYPT: decrypt
    \param[in]  key: key used for AES algorithm
    \param[in]  keysize: length of the key, must be a 128, 192 or 256
    \param[in]  text: pointer to the text information struct
                  input: pointer to the input buffer
                  in_length: length of the input buffer, must be a multiple of 16
                  output: pointer to the returned buffer
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus cau_aes_ecb(uint32_t algo_dir, uint8_t *key, uint16_t keysize, cau_text_struct *text)
{
    ErrStatus ret = ERROR;
    cau_key_parameter_struct key_initpara;
    __IO uint32_t counter = 0U;
    uint32_t busystatus = 0U;

    /* key structure initialization */
    cau_key_parameter_init(&key_initpara);
    /* AES key structure parameter config */
    cau_aes_key_config(key, keysize, &key_initpara);
    /* key initialization */
    cau_key_init(&key_initpara);

    /* AES decryption */
    if(CAU_DECRYPT == algo_dir){
        /* flush the IN and OUT FIFOs */
        cau_fifo_flush();
        /* initialize the CAU peripheral */
        cau_init(CAU_DECRYPT, CAU_MODE_AES_KEY, CAU_SWAPPING_32BIT);

        /* enable the CAU peripheral */
        cau_enable();

        /* wait until the busy flag is RESET */
        do{
            busystatus = cau_flag_get(CAU_FLAG_BUSY);
            counter++;
        }while((AESBSY_TIMEOUT != counter) && (RESET != busystatus));

        if(RESET != busystatus){
            return ERROR;
        }
    }

    /* initialize the CAU peripheral */
    cau_init(algo_dir, CAU_MODE_AES_ECB, CAU_SWAPPING_8BIT);

    /* flush the IN and OUT FIFOs */
    cau_fifo_flush();

    /* enable the CAU peripheral */
    cau_enable();
    /* AES calculate process */
    ret = cau_aes_calculate(text->input, text->in_length, text->output);
    /* disable the CAU peripheral */
    cau_disable();

    return ret;
}

/*!
    \brief      encrypt and decrypt using AES in CBC mode
    \param[in]  algo_dir: algorithm direction
                only one parameter can be selected which is shown as below
      \arg        CAU_ENCRYPT: encrypt
      \arg        CAU_DECRYPT: decrypt
    \param[in]  key: key used for AES algorithm
    \param[in]  keysize: length of the key, must be a 128, 192 or 256
    \param[in]  iv: initialization vectors used for TDES algorithm
    \param[in]  text: pointer to the text information struct
                  input: pointer to the input buffer
                  in_length: length of the input buffer, must be a multiple of 16
                  output: pointer to the returned buffer
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus cau_aes_cbc(uint32_t algo_dir, uint8_t *key, uint16_t keysize, uint8_t iv[16], cau_text_struct *text)
{
    ErrStatus ret = ERROR;
    cau_key_parameter_struct key_initpara;
    cau_iv_parameter_struct iv_initpara;
    __IO uint32_t counter = 0U;
    uint32_t busystatus = 0U;

    uint32_t ivaddr = (uint32_t)iv;

    /* key structure initialization */
    cau_key_parameter_init(&key_initpara);
    /* AES key structure parameter config */
    cau_aes_key_config(key, keysize, &key_initpara);
    /* key initialization */
    cau_key_init(&key_initpara);

    /* AES decryption */
    if(CAU_DECRYPT == algo_dir){
        /* flush the IN and OUT FIFOs */
        cau_fifo_flush();
        /* initialize the CAU peripheral */
        cau_init(CAU_DECRYPT, CAU_MODE_AES_KEY, CAU_SWAPPING_32BIT);

        /* enable the CAU peripheral */
        cau_enable();

        /* wait until the busy flag is RESET */
        do{
            busystatus = cau_flag_get(CAU_FLAG_BUSY);
            counter++;
        }while((AESBSY_TIMEOUT != counter) && (RESET != busystatus));

        if(RESET != busystatus){
            return ERROR;
        }
    }

    /* initialize the CAU peripheral */
    cau_init(algo_dir, CAU_MODE_AES_CBC, CAU_SWAPPING_8BIT);

    /* vectors initialization */
    iv_initpara.iv_0_high = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4U;
    iv_initpara.iv_0_low = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4U;
    iv_initpara.iv_1_high = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4U;
    iv_initpara.iv_1_low = __REV(*(uint32_t*)(ivaddr));
    cau_iv_init(&iv_initpara);

    /* flush the IN and OUT FIFOs */
    cau_fifo_flush();

    /* enable the CAU peripheral */
    cau_enable();
    /* AES calculate process */
    ret = cau_aes_calculate(text->input, text->in_length, text->output);
    /* disable the CAU peripheral */
    cau_disable();

    return ret;
}

/*!
    \brief      encrypt and decrypt using AES in CTR mode
    \param[in]  algo_dir: algorithm direction
                only one parameter can be selected which is shown as below
      \arg        CAU_ENCRYPT: encrypt
      \arg        CAU_DECRYPT: decrypt
    \param[in]  key: key used for AES algorithm
    \param[in]  keysize: length of the key, must be a 128, 192 or 256
    \param[in]  iv: initialization vectors used for TDES algorithm
    \param[in]  text: pointer to the text information struct
                  input: pointer to the input buffer
                  in_length: length of the input buffer, must be a multiple of 16
                  output: pointer to the returned buffer
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus cau_aes_ctr(uint32_t algo_dir, uint8_t *key, uint16_t keysize, uint8_t iv[16], cau_text_struct *text)
{
    ErrStatus ret = ERROR;
    cau_key_parameter_struct key_initpara;
    cau_iv_parameter_struct iv_initpara;

    uint32_t ivaddr = (uint32_t)iv;

    /* key structure initialization */
    cau_key_parameter_init(&key_initpara);
    /* initialize the CAU peripheral */
    cau_init(algo_dir, CAU_MODE_AES_CTR, CAU_SWAPPING_8BIT);

    /* AES key structure parameter config */
    cau_aes_key_config(key, keysize, &key_initpara);
    /* key initialization */
    cau_key_init(&key_initpara);

    /* vectors initialization */
    iv_initpara.iv_0_high = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4U;
    iv_initpara.iv_0_low = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4U;
    iv_initpara.iv_1_high = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4U;
    iv_initpara.iv_1_low = __REV(*(uint32_t*)(ivaddr));
    cau_iv_init(&iv_initpara);

    /* flush the IN and OUT FIFOs */
    cau_fifo_flush();

    /* enable the CAU peripheral */
    cau_enable();
    /* AES calculate process */
    ret = cau_aes_calculate(text->input, text->in_length, text->output);
    /* disable the CAU peripheral */
    cau_disable();

    return ret;
}

/*!
    \brief      AES key structure parameter config
    \param[in]  key: key used for AES algorithm
    \param[in]  keysize: length of the key, must be a 128, 192 or 256
    \param[out] cau_key_initpara: key init parameter struct
                  key_0_high: key 0 high
                  key_0_low:  key 0 low
                  key_1_high: key 1 high
                  key_1_low:  key 1 low
                  key_2_high: key 2 high
                  key_2_low:  key 2 low
                  key_3_high: key 3 high
                  key_3_low:  key 3 low
    \retval     none
*/
static void cau_aes_key_config(uint8_t *key, uint16_t keysize, cau_key_parameter_struct* cau_key_initpara)
{
    uint32_t keyaddr = (uint32_t)key;

    switch(keysize){
    case 128:
        cau_aes_keysize_config(CAU_KEYSIZE_128BIT);
        cau_key_initpara->key_2_high = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_low = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_high = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_low = __REV(*(uint32_t*)(keyaddr));
        break;
    case 192:
        cau_aes_keysize_config(CAU_KEYSIZE_192BIT);
        cau_key_initpara->key_1_high = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_1_low = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_high = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_low = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_high = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_low = __REV(*(uint32_t*)(keyaddr));
        break;
    case 256:
        cau_aes_keysize_config(CAU_KEYSIZE_256BIT);
        cau_key_initpara->key_0_high = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_0_low = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_1_high = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_1_low = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_high = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_2_low = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_high = __REV(*(uint32_t*)(keyaddr));
        keyaddr += 4U;
        cau_key_initpara->key_3_low = __REV(*(uint32_t*)(keyaddr));
        break;
    default:
        break;
    }
}

/*!
    \brief      AES calculate process
    \param[in]  input: pointer to the input buffer
    \param[in]  in_length: length of the input buffer, must be a multiple of 16
    \param[in]  output: pointer to the returned buffer
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
static ErrStatus cau_aes_calculate(uint8_t *input, uint32_t in_length, uint8_t *output)
{
    uint32_t inputaddr  = (uint32_t)input;
    uint32_t outputaddr = (uint32_t)output;
    uint32_t i = 0U;
    __IO uint32_t counter = 0U;
    uint32_t busystatus = 0U;

    /* the clock is not enabled or there is no embeded CAU peripheral */
    if(DISABLE == cau_enable_state_get()){
        return ERROR;
    }

    for(i = 0U; i < in_length; i += 16U){
        /* write data to the IN FIFO */
        cau_data_write(*(uint32_t*)(inputaddr));
        inputaddr += 4U;
        cau_data_write(*(uint32_t*)(inputaddr));
        inputaddr += 4U;
        cau_data_write(*(uint32_t*)(inputaddr));
        inputaddr += 4U;
        cau_data_write(*(uint32_t*)(inputaddr));
        inputaddr += 4U;

        /* wait until the complete message has been processed */
        counter = 0U;
        do{
            busystatus = cau_flag_get(CAU_FLAG_BUSY);
            counter++;
        }while((AESBSY_TIMEOUT != counter) && (RESET != busystatus));

        if(RESET != busystatus){
            return ERROR;
        }else{
            /* read the output block from the output FIFO */
            *(uint32_t*)(outputaddr) = cau_data_read();
            outputaddr += 4U;
            *(uint32_t*)(outputaddr) = cau_data_read();
            outputaddr += 4U;
            *(uint32_t*)(outputaddr) = cau_data_read();
            outputaddr += 4U;
            *(uint32_t*)(outputaddr) = cau_data_read();
            outputaddr += 4U;
        }
    }

    return SUCCESS;
}
