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
* DISCLAIMED. IN NO EVENT SHALL NATIONZ BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* ****************************************************************************/
/*****************************************************************************
* File Name: SM4.h
* Function: Defining RNG API
* author: nations
* version: V1.0
* date: 2025-4-15
* ****************************************************************************/

#ifndef _SM4_H_
#define _SM4_H_

#include "n32h76x_78x_Common.h"

#define SM4_ECB 0
#define SM4_CBC 1
#define SM4_ENCRYPT 0
#define SM4_DECRYPT 1

enum SM4_ENUM
{

	    SM4_Init_OK = 0x5a5a5a5a, //SM4 opreation success
	   SM4_Crypto_OK=0x5a5a5a5a, //SM4 opreation success
		 SM4_ParaNull =0x27A90E35, //the address  of input is NULL
		 SM4_ModeErr, //working mode error(Neither ECB nor CBC)
		 SM4_EnDeErr,  // En&De error(Neither encryption nor decryption)
		 SM4_LengthErr,//the byte length of input error
		 SM4_ATTACKED, //SM4 subjected to attack
};
typedef struct{
	uint8_t *in;   // the part of input to be encrypted or decrypted
	uint8_t *iv;   // the  part of initial vector
	uint8_t *out;  // the  part of out
	uint8_t *key;  // the  part of key
	uint32_t inBytelen; //the word length of input or output 
	uint32_t En_De; //encrypt/decrypt
	uint32_t Mode; //  ECB/CBC 
}SM4_PARM;
/**
 * @brief SM4 Init
 * @param[in] parm pointer to SM4 context and the detail please refer to struct SM4_PARM in SM4.h
 * @return SM4_Init_OK, SM4 Init success; othets: SM4 Init fail(reference to the definition by enum variation) 
 * @note  1.Please refer to the demo in user guidance before using this function  
 *        2. IV can be NULL when ECB mode
 *        3. The byte lengrh of message must be as times as 16.
 */
 
uint32_t SM4_Init(SM4_PARM *parm);

/**
 * @brief SM4 crypto
 * @param[in] parm pointer to SM4 context and the detail please refer to struct SM4_PARM in SM4.h
 * @return SM4_Crypto_OK, SM4 crypto success; othets: SM4 crypto fail(reference to the definition by enum variation) 
 * @note  1.Please refer to the demo in user guidance before using this function  
 *        2. IV can be NULL when ECB mode
 *        3. The byte lengrh of message must be as times as 16.
 */
uint32_t SM4_Crypto1(SM4_PARM *parm);
/**
 * @brief Close SM4 algorithm
 * @return none
 * @note if you want to close SM4 algorithm, this function can be recalled.  
 */
void SM4_Close(void);


/**
 * @brief Get SM4 lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018 
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get SM4 lib information
 */
void SM4_Version(uint8_t *type, uint8_t *customer, uint8_t date[3], uint8_t *version);


#endif /*_SM4_H_*/

