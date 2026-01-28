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
* File Name: RNG.h
* Function: Defining RNG API
* author: nations
* version: V1.0
* date: 2025-4-15
* ****************************************************************************/





#include <stdint.h>
#ifndef __RNG_H__
#define __RNG_H__


enum{

	RNG_OK = 0x5a5a5a5a,//RNG generation process is ok
	RNG_LENError = 0x311ECF50,   //RNG generation of key length error 
	RNG_ADDRError = 0x63BB4C39,  //This return value is not used
	RNG_ADDRNULL = 0x7A9DB86C,   // This address is empty
	RNG_Attack = 0x4794674F,  //The RNG generation process is attacked
	RNG_ModeError=0x479467aa, //RNG choose mode is fail
	RNG_TESTFAIL=0x479467bb, //RNG test is fail
	RNG_SEEDNULL=0x479467cc, //RNG seed is NULL
};


/**
 * @brief Get true random number
 * @param[out] rand pointer to random number
 * @param[out] wordLen pointer to word length of rand
 * @return RNG_OK:get random number success; othets: get random number fail 
 * @note    
 */
uint32_t GetTrueRand_U32(uint32_t *rand, uint32_t wordLen);

/**
 * @brief Get true random number
 * @param[out] rand pointer to random number
 * @param[out] wordLen pointer to word length of rand
 * @return RNG_OK:get random number success; othets: get random number fail 
 * @note    
 */
uint32_t GetTrueRand_U8(uint8_t *rand, uint32_t bytelen);

/**
 * @brief PseudoRandNumInit 
 * @param[in] seed of PseudoRandNum
 * @return RNG_OK:PseudoRandNumInit success; othets: PseudoRandNumInit fail 
 * @note    
 */
uint32_t PseudoRandNumInit(uint32_t seed[5]);

/**
 * @brief PseudoRandNumReseed 
 * @param[in] seed of PseudoRandNum
 * @return RNG_OK:PseudoRandNumReseed success; othets: PseudoRandNumReseed fail 
 * @note    
 */
uint32_t PseudoRandNumReseed(uint32_t seed[5]);
/**
 * @brief Get pseudo random number
 * @param[out] rand pointer to random number
 * @param[out] rand pointer to random number
 * @return RNG_OK:get random number success; othets: get random number fail 
 */

uint32_t GetPseudoRand_U32(uint32_t *rand, uint32_t wordLen);
/**
 * @brief Get RNG lib version
 * @param[out] type pointer one byte type information represents the type of the lib, like Commercial version.\
 * @Bits 0~4 stands for Commercial (C), Security (S), Normal (N), Evaluation (E), Test (T), Bits 5~7 are reserved. e.g. 0x09 stands for CE version.
 * @param[out] customer pointer one byte customer information represents customer ID. for example, 0x00 stands for standard version, 0x01 is for Tianyu customized version...
 * @param[out] date pointer array which include three bytes date information. If the returned bytes are 18,9,13,this denotes September 13,2018 
 * @param[out] version pointer one byte version information represents develop version of the lib. e.g. 0x12 denotes version 1.2.
 * @return none
 * @1.You can recall this function to get DES lib information
 */
void RNG_Version(uint8_t *type, uint8_t *customer, uint8_t date[3], uint8_t *version);

#endif

