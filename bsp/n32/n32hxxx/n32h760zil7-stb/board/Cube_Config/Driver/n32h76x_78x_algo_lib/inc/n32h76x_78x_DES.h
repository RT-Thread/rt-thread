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
* File Name: DES.h
* Function: Defining DES algorithm library API
* version: V1.0
* Author: nations
* date: 2025-04-15
* ****************************************************************************/
#ifndef _DES_H_
#define _DES_H_

#include <stdint.h>
#include "n32h76x_78x_Common.h"
#define DES_ECB  (0)
#define DES_CBC  (1)
#define DES_ENCRYPT 0
#define DES_DECRYPT 1

#define TDES_ECB  (0)
#define TDES_CBC  (1)	
#define TDES_ENCRYPT 0
#define TDES_DECRYPT 1

enum DES
{
  DES_Init_OK = 0x2a2a7a7a,		//DES opreation success
	DES_Crypto_OK = 0x2a2a7a7a,		//DES opreation success
	DES_ModeErr = 0x5a5a5a5a,		//Working mode error(Neither ECB nor CBC)
	DES_EnDeErr,		//En&De error(Neither encryption nor decryption)
	DES_ParaNull,		// the part of input(output/iv) Null
	DES_KeyLenErr,
	DES_LengthErr,		
	DES_ATTACKED,   //DES subjected to attack
};
typedef struct
{
		uint8_t *in;   // the part of input to be encrypted or decrypted
		uint8_t *iv;   // the part of initial vector
		uint8_t *out;  // the part of out 
		uint8_t *key;  // the part of key 
		uint32_t inByteLen;  // the length(by byte) of plaintext or cipher
		uint32_t En_De; // 0x33333333- encrypt, 0x44444444 - decrypt
		uint32_t Mode;  // 0x11111111 - ECB, 0x22222222 - CBC
		uint32_t keyByteLen;   //the length(by byte) of key		
}DES_PARM;

typedef DES_PARM TDES_PARM;




/**
 * @brief DES Init
 * @param[in] parm pointer to DES context and the detail please refer to struct DES_PARM in DES.h
 * @return DES_Init_OK, DES Init success; othets: DES Init fail(reference to the definition by enum variation) 
 * @note  1.Please refer to the demo in user guidance before using this function  
 *        2. IV can be NULL when ECB mode
 *        3. The byte lengrh of message must be as times as 8.
 */
uint32_t DES_Init(DES_PARM *parm);





/**
 * @brief DES crypto
 * @param[in] parm pointer to DES context and the detail please refer to struct DES_PARM in SM1.h
 * @return DES_Crypto_OK, DES crypto success; othets: DES crypto fail(reference to the definition by enum variation) 
 * @note  1.Please refer to the demo in user guidance before using this function  
 *        2. IV can be NULL when ECB mode
 *        3. The byte lengrh of message must be as times as 8.
 */
 uint32_t DES_Crypto1(DES_PARM *parm);

/**
 * @brief DES close
 * @return none
 * @note  
 */
 void DES_Close(void);


#define TDES_Init    DES_Init
#define TDES_Crypto1  DES_Crypto1
#define TDES_Close   DES_Close

/**
 * @brief Get DES lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018 
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get DES lib information
 */
 void DES_Version(uint8_t *type, uint8_t *customer, uint8_t date[3], uint8_t *version);

#define TDES_Version DES_Version
#endif	 /*_DES_H_*/


/** @} */
