/*****************************************************************************
*         Nations Microcontroller Software Support
* ----------------------------------------------------------------------------
* Copyright (c) 2020, Nations Corporation
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* - Redistributions of source code must retain the above copyright notice,
* this list of conditions and the disclaimer below.
*
* Nations's name may not be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* DISCLAIMER: THIS SOFTWARE IS PROVIDED BY Nations "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
* DISCLAIMED. IN NO EVENT SHALL Nations BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ****************************************************************************/
/*****************************************************************************
* File Name: Dn32g43x_des.h
* Function: Declaring DES algorithm library API
* version: V1.2.0
* Author: zhang.zhenshan
* date: 2020-4-8
* ****************************************************************************/


#ifndef _N32G43X_DES_H_
#define _N32G43X_DES_H_

#include <stdint.h>

#define DES_ECB (0x11111111)
#define DES_CBC (0x22222222)


#define DES_ENC  (0x33333333)
#define DES_DEC  (0x44444444)

#define DES_KEY  (0x55555555)
#define TDES_2KEY  (0x66666666)
#define TDES_3KEY  (0x77777777)

enum DES
{
  DES_Crypto_OK = 0x0,      //DES/TDES opreation success
    DES_Init_OK   = 0x0,    //DES/TDES Init opreation success
    DES_Crypto_ModeError = 0x5a5a5a5a,      //Working mode error(Neither ECB nor CBC)
    DES_Crypto_EnOrDeError,     //En&De error(Neither encryption nor decryption)
    DES_Crypto_ParaNull,        // the part of input(output/iv) Null
    DES_Crypto_LengthError,     //the length of input message must be 2 times and cannot be zero
    DES_Crypto_KeyError,  //keyMode error(Neither DES_KEY nor TDES_2KEY nor TDES_3KEY)
    DES_Crypto_UnInitError,   //DES/TDES uninitialized
};

typedef struct
{
        uint32_t *in;   // the  part of input to be encrypted or decrypted
        uint32_t *iv;   // the  part of initial vector
        uint32_t *out;  // the  part of out
        uint32_t *key;  // the  part of key
        uint32_t inWordLen;  // the length(by word) of plaintext or cipher
        uint32_t En_De; // 0x33333333- encrypt, 0x44444444 - decrypt
        uint32_t Mode;  // 0x11111111 - ECB, 0x22222222 - CBC
        uint32_t keyMode; //TDES key mode: 0x55555555-key,0x66666666-2key, 0x77777777-3key
}DES_PARM;

 /**
 * @brief DES_Init
 * @return DES_Init_OK, DES/TDES Init success; othets: DES/TDES Init fail
 * @note
 */
uint32_t DES_Init(DES_PARM *parm);

/**
 * @brief DES crypto
 * @param[in] parm pointer to DES/TDES context and the detail please refer to struct DES_PARM in DES.h
 * @return DES_Crypto_OK, DES/TDES crypto success; othets: DES/TDES crypto fail(reference to the definition by enum variation)
 * @note  1.Please refer to the demo in user guidance before using this function
 *        2.Input and output can be the same buffer
 *        3. IV can be NULL when ECB mode
 *        4. The word lengrh of message must be as times as 2.
 *        5. If the input is in byte, make sure align by word.
 */
uint32_t DES_Crypto(DES_PARM *parm);

/**
 * @brief DES close
 * @return none
 * @note  if you want to close DES algorithm, this function can be recalled.
 */
void DES_Close(void);

/**
 * @brief Get DES/TDES lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get DES/TDES lib information
 */
void DES_Version(uint8_t *type, uint8_t *customer, uint8_t date[3], uint8_t *version);

#endif
