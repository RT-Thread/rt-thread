/*****************************************************************************
*         NationS Microcontroller Software Support
* ----------------------------------------------------------------------------
* Copyright (c) 2025, NationS Corporation
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
/*****************************************************************************/
/*****************************************************************************
* File Name: AES.h
* Function: Defining AES algorithm library API
* version: V1.0
* Author: nations
* date: 2025-04-15
* ****************************************************************************/
#ifndef __AES_H
#define __AES_H
#include <stdint.h>

#define AES_ECB 0x11111111
#define AES_CBC 0x22222222
#define AES_CTR 0x33333333
#define AES_ENCRYPT 0x44444444
#define AES_DECRYPT 0x55555555
#define AES_KEY_128 0x66666666
#define AES_KEY_192 0x77777777
#define AES_KEY_256 0x88888888


enum{
     AES_Init_OK = 0x3a3a5a5a, //AES opreation success
	   AES_Crypto_OK=0x3a3aa5a5, //AES opreation success		 
		 AES_ModeErr= 0x5a5a5a5a,	 //Working mode error(Neither ECB nor CBC,CTR)
		 AES_EnDeErr,  // En&De error(Neither encryption nor decryption)
	   AES_ParaNull,    // the part of input(output/iv) Null    
		 AES_LengthErr,//
	   AES_KeyLengthError,  
		 AES_ATTACKED, //AES subjected to attack
};
typedef struct
{
	uint8_t *in;		// the part of input to be encrypted or decrypted
	uint8_t *iv;		//  the part of initial vector
	uint8_t *out;		//  the part of out
	uint8_t *key;		//  the part of key
	uint32_t keyBytelen;   // the length(by byte) of key
	uint32_t inBytelen;	// the length(by byte) of plaintext or cipher
	uint32_t En_De;	// 0x44444444- encrypt, 0x55555555 - decrypt
	uint32_t Mode;  // 0x11111111 - ECB, 0x22222222 - CBC,0x33333333-AES_CTR
}AES_PARM;

/**
 * @brief AES Init
 * @param[in] parm pointer to AES context and the detail please refer to struct DES_PARM in DES.h
 * @return AES_Init_OK, AES Init success; othets: AES Init fail(reference to the definition by enum variation) 
 * @note  1.Please refer to the demo in user guidance before using this function  
 *        2. IV can be NULL when ECB mode
 *        3. The byte lengrh of message must be as times as 16.
 */
uint32_t AES_Init(AES_PARM *parm);

/**
 * @brief AES crypto
 * @param[in] parm pointer to DES context and the detail please refer to struct DES_PARM in SM1.h
 * @return AES_Crypto_OK, DES crypto success; othets: AES crypto fail(reference to the definition by enum variation) 
 * @note  1.Please refer to the demo in user guidance before using this function  
 *        2. IV can be NULL when ECB mode
 *        3. The byte lengrh of message must be as times as 16.
 */

uint32_t  AES_Crypto(AES_PARM *parm);

/**
 * @brief AES close
 * @return none
 * @note  
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




