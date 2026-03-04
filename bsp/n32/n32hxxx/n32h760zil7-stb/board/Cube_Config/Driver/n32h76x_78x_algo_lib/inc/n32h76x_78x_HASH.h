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
* File Name:Hash.h
* Function: Defining AES algorithm library API
* version: V1.0
* Author: nations
* date: 2025-04-15
* ****************************************************************************/
#ifndef _HASH_H_
#define _HASH_H_
#include "n32h76x_78x_Common.h" 
#define  ALG_SHA1                (uint16_t)(0x0004)
#define  ALG_SHA224              (uint16_t)(0x000A)
#define  ALG_SHA256              (uint16_t)(0x000B)
#define  ALG_SHA384              (uint16_t)(0x000C)
#define  ALG_SHA512              (uint16_t)(0x000D)

enum
{
	HASH_SEQUENCE_TRUE = 0x0105A5A5,//save IV
	HASH_SEQUENCE_FALSE = 0x010A5A5A, //not save IV 
	HASH_Init_OK = 0x5a5a5a5a,//hash init success
	HASH_Start_OK = 0x5a5a5a5a,//hash update success
	HASH_Update_OK = 0x5a5a5a5a,//hash update success
	HASH_Complete_OK = 0x5a5a5a5a,//hash complete success
	HASH_Close_OK = 0x5a5a5a5a,//hash close success
	HASH_ByteLenPlus_OK = 0x5a5a5a5a,//byte length plus success
	HASH_PadMsg_OK = 0x5a5a5a5a,//message padding success
	HASH_ProcMsgBuf_OK = 0x5a5a5a5a, //message processing success
	SM3_Hash_OK = 0x5a5a5a5a,//sm3 operation success
	SHA256_Hash_OK = 0x5a5a5a5a,//sha256 operation success
	SHA1_Hash_OK = 0,//sha1 operation success
	SHA224_Hash_OK = 0,//sha224 operation success
	SHA384_Hash_OK = 0,//sha384 operation success
	SHA512_Hash_OK = 0,//sha512 operation success
	HASH_Init_ERROR = 0x01044400,//hash init error
	HASH_Start_ERROR, //hash start error
	HASH_Update_ERROR, //hash update error
	HASH_Complete_ERROR,//hash complete error
	HASH_ByteLenPlus_ERROR,//hash byte plus error
	HASH_ATTACK, //hash operation subject to attack
};

 struct _HASH_CTX_;

typedef struct
{
	const uint16_t HashAlgID;//choice hash algorithm
	//const uint32_t * const K, KLen;//K and byte length of K
	const uint32_t * const IV, IVLen;//IV and byte length of IV
	const uint32_t HASH_ALGCR, HASH_SACCR, HASH_HASHCTRL;//relate registers
	const uint32_t BlockByteLen, BlockWordLen; //byte length of block, word length of block
	const uint32_t DigestByteLen, DigestWordLen; //byte length of digest,word length of digest
	const uint32_t Cycle; //interation times
	uint32_t (* const ByteLenPlus)(uint32_t *, uint32_t); //function pointer
	uint32_t (* const PadMsg)(struct _HASH_CTX_ *); //function pointer
}HASH_ALG;


typedef struct _HASH_CTX_
{
	const HASH_ALG	*hashAlg;     //pointer to HASH_ALG
	uint32_t	sequence;     // TRUE if the IV should be saved
	uint32_t 	IV[16]; 
	uint32_t	msgByteLen[4];
        uint8_t		msgBuf[132];
        uint32_t	msgIdx;
}HASH_CTX;


extern const HASH_ALG HASH_ALG_SHA1[1];
extern const HASH_ALG HASH_ALG_SHA224[1];
extern const HASH_ALG HASH_ALG_SHA256[1];
extern const HASH_ALG HASH_ALG_SHA384[1];
extern const HASH_ALG HASH_ALG_SHA512[1];

/**
 * @brief  Hash init
 * @param[in] ctx pointer to HASH_CTX struct
 * @return HASH_Init_OK,  Hash init success; othets:  Hash init fail
 * @note   1.Please refer to the demo in user guidance before using this function 
 */
uint32_t HASH_Init(HASH_CTX *ctx);

/**
 * @brief  Hash start
 * @param[in] ctx pointer to HASH_CTX struct
 * @return HASH_Start_OK,  Hash start success; othets:  Hash start fail
 * @note   1.Please refer to the demo in user guidance before using this function 
 *         2.HASH_Init() should be recalled before use this function 
 */
uint32_t HASH_Start(HASH_CTX *ctx);

/**
 * @brief  Hash update
 * @param[in] ctx pointer to HASH_CTX struct
 * @param[in] in pointer to message
 * @param[out] out pointer tohash result,digest
 * @return HASH_Update_OK,  Hash update success; othets:  Hash update fail
 * @note   1.Please refer to the demo in user guidance before using this function 
 *         2.HASH_Init() and HASH_Start() should be recalled before use this function 
 */
uint32_t HASH_Update(HASH_CTX *ctx, uint8_t *in, uint32_t byteLen);

/**
 * @brief  Hash complete
 * @param[in] ctx pointer to HASH_CTX struct
 * @param[out] out pointer tohash result,digest
 * @return HASH_Complete_OK,  Hash complete success; othets:  Hash complete fail
 * @note   1.Please refer to the demo in user guidance before using this function 
 *         2.HASH_Init(), HASH_Start() and HASH_Update() should be recalled before use this function 
 */
uint32_t HASH_Complete(HASH_CTX *ctx, uint8_t *out);

/**
 * @brief  Hash close
 * @return HASH_Close_OK, Hash close success; othets: Hash close fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
void HASH_Close(void);



/**
 * @brief  SHA1 Hash
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[out] out pointer tohash result,digest
 * @return SHA1_Hash_OK, SHA1 hash success; othets: SHA1 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t SHA1_Hash(uint8_t* in,uint32_t byteLen, uint8_t* out);

/**
 * @brief  SHA224 Hash
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[out] out pointer tohash result,digest
 * @return SHA224_Hash_OK, SHA224 hash success; othets: SHA224 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t SHA224_Hash(uint8_t* in,uint32_t byteLen, uint8_t* out);


/**
 * @brief  SHA256 Hash
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[out] out pointer tohash result,digest
 * @return SHA256_Hash_OK, SHA256 hash success; othets: SHA256 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t SHA256_Hash(uint8_t* in,uint32_t byteLen, uint8_t* out);

/**
 * @brief  SHA384 Hash
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[in] out pointer tohash result,digest
 * @return SHA384_Hash_OK, SHA384 hash success; othets: SHA384 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t SHA384_Hash(uint8_t* in,uint32_t byteLen, uint8_t* out);

/**
 * @brief  SHA512 Hash
 * @param[in] in pointer to message
 * @param[in] byte length of in
 * @param[out] out pointer tohash result,digest
 * @return SHA512_Hash_OK, SHA512 hash success; othets: SHA512 hash fail
 * @note   1.Please refer to the demo in user guidance before using this function  
 */
uint32_t SHA512_Hash(uint8_t* in,uint32_t byteLen, uint8_t* out);


/**
 * @brief Get HASH lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018 
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get HASH lib information
 */
void HASH_Version(uint8_t *type, uint8_t *customer, uint8_t date[3], uint8_t *version);


#endif
