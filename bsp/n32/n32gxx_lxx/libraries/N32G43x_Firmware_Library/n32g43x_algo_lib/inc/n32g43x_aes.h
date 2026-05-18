/*****************************************************************************
*         NationS Microcontroller Software Support
* ----------------------------------------------------------------------------
* Copyright (c) 2020, NationS Corporation
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* - Redistributions of source code must retain the above copyright notice,
* this list of conditions and the disclaimer below.
*
* NationS's name may not be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ****************************************************************************/
/*****************************************************************************
* File Name: n32g43x_aes.h
* Function: Declaring AES algorithm library API
* version: V1.2.0
* Author: zhang.zhenshan
* date: 2020-4-8
* ****************************************************************************/

#ifndef __N32G43X_AES_H__
#define __N32G43X_AES_H__

#include <stdint.h>

#define AES_ECB (0x11111111)
#define AES_CBC (0x22222222)
#define AES_CTR (0x33333333)

#define AES_ENC  (0x44444444)
#define AES_DEC  (0x55555555)

enum
{
    AES_Crypto_OK = 0x0,   //AES opreation success
    AES_Init_OK = 0x0,   //AES Init opreation success
    AES_Crypto_ModeError = 0x5a5a5a5a,   //Working mode error(Neither ECB nor CBC nor CTR)
    AES_Crypto_EnOrDeError,    //En&De error(Neither encryption nor decryption)
    AES_Crypto_ParaNull,    // the part of input(output/iv) Null
    AES_Crypto_LengthError,     // if Working mode is ECB or CBC,the length of input message must be 4 times and cannot be zero;
                                //if Working mode is CTR,the length of input message cannot be zero; othets: return AES_Crypto_LengthError

    AES_Crypto_KeyLengthError, //the keyWordLen must be 4 or 6 or 8; othets:return AES_Crypto_KeyLengthError
  AES_Crypto_UnInitError, //AES uninitialized
};

typedef struct
{
    uint32_t *in;       // the part of input to be encrypted or decrypted
    uint32_t *iv;       // the part of initial vector
    uint32_t *out;      // the part of out
    uint32_t *key;      // the part of key
    uint32_t keyWordLen;   // the length(by word) of key
    uint32_t inWordLen; // the length(by word) of plaintext or cipher
    uint32_t En_De; // 0x44444444- encrypt, 0x55555555 - decrypt
    uint32_t Mode;  // 0x11111111 - ECB, 0x22222222 - CBC, 0x33333333 - CTR
}AES_PARM;

 /**
 * @brief AES_Init
 * @return AES_Init_OK, AES Init success; othets: AES Init fail
 * @note
 */

uint32_t  AES_Init(AES_PARM *parm);

/**
 * @brief AES crypto
 * @param[in] parm pointer to AES context and the detail please refer to struct AES_PARM in AES.h
 * @return AES_Crypto_OK, AES crypto success; othets: AES crypto fail(reference to the definition by enum variation)
 * @note  1.Please refer to the demo in user guidance before using this function
 *        2.Input and output can be the same buffer
 *        3. IV can be NULL when ECB mode
 *        4. If Working mode is ECB or CBC,the length of input message must be 4 times and cannot be zero;
 *           if Working mode is CTR,the length of input message cannot be zero;
 *        5. If the input is in byte, make sure align by word.
 */
uint32_t AES_Crypto(AES_PARM *parm);

/**
 * @brief AES close
 * @return none
 * @note if you want to close AES algorithm, this function can be recalled.
 */
void AES_Close(void);

/**
 * @brief Get AES lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get AES lib information
 */
void AES_Version(uint8_t *type, uint8_t *customer, uint8_t date[3], uint8_t *version);




#endif


