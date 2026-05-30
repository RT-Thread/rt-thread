/*****************************************************************************
*         NationS Microcontroller Software Support
* ----------------------------------------------------------------------------
* Copyright (c) 2022, NationS Corporation
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
* File Name: Common.h
* Function: Defining Common algorithm library API
* version: V1.0
* Author: Nations Solution Team
* date: 2022-05-23
* ****************************************************************************/
#ifndef _Common_H_
#define _Common_H_
#include <stdint.h>

enum{
  Cpy_OK=0x5a5a5a5a,//copy success
	SetData_OK = 0x5a5a5a5a,//set zero success
	Reverse_OK = 0x5a5a5a5a, //reverse success
	IsZero_NOT = 0x5a5a5a5a, //Big number is not zero
	IsOne_NOT = 0x5a5a5a5a,//big number is one
	IsOne_YES = 0x05a5a5a5,//big number is not one
	IsZero_YES = 0x05a5a5a5, //Big number is zero
	
	Cmp_EQUAL = 0, //Two big number are equal	
	Cmp_LESS = (int32_t)0xa5a55a5a, //The former big number is less than the latter
	Cmp_GREATER = 0x1a5a5a5a,//The former big number is greater than the latter
	Cmp_ERROR=0x3a3a3a3a,
	RandomSort_OK = 0x5a5a5a5a, //disturb order success
	XOR_OK=0x5a5a5a5a,   //XOR success
	Reverse_ERROR = 0x7A9E0863, //reverse fail due to src and dst are same 
};
typedef struct
{
	uint32_t *data;
	uint32_t wordLen;
}N_BIGNUM;
/**
 * @brief disturb the sequence order
 * @param[in] order pointer to the sequence to be disturbed
 * @param[in] rand pointer to random number
 * @param[in] the length of order
 * @return RandomSort_OK:  disturb order success;  Others: disturb order fail;
 * @note 
 */
uint32_t RandomSort(uint8_t *order, const uint8_t *rand, uint32_t len);

/**
 * @brief Copy data by byte
 * @param[in]  dst pointer to destination data
 * @param[in]  src pointer to source data
 * @param[in]  byte length 
 * @return Cpy_OK: success; others: fail.
 * @note 1. dst and  src cannot be same
 */
uint32_t Cpy_U8(uint8_t *dst, uint8_t *src, uint32_t byteLen);

/**
 * @brief Copy data by word
 * @param[in]  dst pointer to destination data
 * @param[in]  src pointer to source data
 * @param[in]  word length 
 * @return Cpy_OK: success; others: fail.
 * @note 1. dst and  src must be aligned by word
 */
uint32_t Cpy_U32(uint32_t *dst, const uint32_t *src, uint32_t wordLen);


 /**
 * @brief XOR
 * @param[in] a pointer to one data to be XORed
 * @param[in] b pointer to another data to be XORed
 * @param[in] the length of order
 * @return XOR_OK:  operation success;  Others: operation fail;
 * @note 
 */
uint32_t XOR_U8(uint8_t *a, uint8_t *b, uint8_t *c, uint32_t byteLen);

 /**
 * @brief XORed two u32 arrays
 * @param[in] a pointer to one data to be XORed
 * @param[in] b pointer to another data to be XORed
 * @param[in] the length of order
 * @return XOR_OK:  operation success;  Others: operation fail;
 * @note 
 */
uint32_t XOR_U32(uint32_t *a,uint32_t *b,uint32_t *c,uint32_t wordLen);

/**
 * @brief set  data by byte
 * @param[in]  dst pointer to the address to be set data 
 * @param[in]  data  
 * @param[in]  byte length 
 * @return SetData_OK: success; others: fail.
 * @note 
 */
uint32_t SetData_U8(uint8_t *dst,uint8_t data, uint32_t byteLen);

/**
 * @brief set  data by word
 * @param[in]  dst pointer to the address to be set data 
 * @param[in]  data   
 * @param[in]  word length 
 * @return SetData_OK: success; others: fail.
 * @note 
 */
uint32_t SetData_U32(uint32_t *dst,uint32_t data, uint32_t wordLen);

/**
 * @brief byte reverse through the whole byte array
 * @param[in]  dst pointer to the address to be set zero 
 * @param[in]  byte length 
 * @return Reverse_OK: success; others: fail.
 * @note 1.dst and src can be same
         2.first byte and last byte of the array are swapped 
 */
uint32_t Reverse_U8(uint8_t *dst, const uint8_t *src, uint32_t byteLen);//�ֽڼ��С��ת��

/**
 * @brief word reverse((0x00010203,04050607,0x08090A0B)->(0x08090A0B,04050607,0x00010203))
 * @param[out] dst pointer to the destination address
 * @param[in] dst pointer to the source address 
 * @param[in]  word length of src
 * @return Reverse_OK: success; others: fail.
 * @note 1.dst and src can be same
         2.first word and last word of the array are swapped; the words stay the same
 */
uint32_t Reverse_U32(uint32_t *dst, const uint32_t *src, uint32_t wordLen);//�ּ��С��ת��

/**
 * @brief reverse byte order of every word, the words stay the same
 * @param[in]  dst pointer to the destination address
 * @param[in]  src pointer to the source address 
 * @param[in]  word length 
 * @return Reverse_OK: success; others: fail.
 * @note 1.dst and src can be same
 */
uint32_t ReverseBytesInWord_U32(uint32_t *dst, const uint32_t *src, uint32_t wordLen);//���ڴ�С��ת��

/**
 * @brief get bit length of a byte array
 * @param[in]  n pointer to the array
 * @param[in]  byteLen  
 * @return bit length
 * @note 1. the byte array is little byte-endian
 */
uint32_t GetBitLen_U8(const uint8_t *n, uint32_t byteLen);

/**
 * @brief get the bit length of big number
 * @param[in] n pointer to big number
 * @param[in]  word length of src
 * @return The bit length of n
 * @note 1. word little-endian; in a word, it's byte little-endian
 */
uint32_t GetBitLen_U32(const uint32_t *n, uint32_t wordLen);

/**
 * @brief check whether big number is zero or not
 * @param[in] n pointer to big number
 * @param[in]  word length of n
 * @return IsZero_YES: zero; IsZero_NOT: not zero.
 * @note 1. word little-endian; in a word, it's byte little-endian
 */
uint32_t IsZero_U32(const uint32_t *n, uint32_t wordLen);

/**
 * @brief check whether big number is zero or not
 * @param[in] n pointer to big number
 * @param[in]  byte length of n
 * @return IsZero_YES: zero; IsZero_NOT: not zero.
 * @note 1. word little-endian; in a word, it's byte little-endian
 */
uint32_t IsZero_U8(const uint8_t *n, uint32_t byteLen);

/**
 * @brief check whether the big number is one or not 
 * @param[in] n pointer to big number
 * @param[in] the word length of n
 * @return IsOne_NOT:  big number is not one;  IsOne_YES: big number is one;
 * @note 
 */
uint32_t IsOne_U32(const uint32_t *n, uint32_t wordLen);

/**
 * @brief compare two big number
 * @param[in] a pointer to one big number
 * @param[in] word length of a
 * @param[in] b pointer to another big number
 * @param[in]  word length of b
 * @return Cmp_GREATER: a > b; Cmp_LESS: a < b;Cmp_EQUAL: a==b.
 * @note 1. word little-endian; in a word, it's byte little-endian 
 */
int32_t Cmp_U32(const uint32_t *a, uint32_t aWordLen, const uint32_t *b, uint32_t bWordLen);

/**
 * @brief compare two big number
 * @param[in] a pointer to one big number
 * @param[in] word length of a
 * @param[in] b pointer to another big number
 * @param[in]  word length of b
 * @return Cmp_GREATER: a > b; Cmp_LESS: a < b;Cmp_EQUAL: a==b.
 * @note 1. it's byte big-endian 
 */
int32_t Cmp_U8(const uint8_t *a, uint32_t aByteLen, const uint8_t *b, uint32_t bByteLen);

/**
 * @brief Load data from buffer to FIFO
 * @param[out] dst pointer to destination data
 * @param[in]  src pointer to source data
 * @param[in]  word length 
 * @return Cpy_OK: success; others: fail.
 * @note 
 */
uint32_t BufToFIFO(volatile uint32_t *dst, const void *src, uint32_t wordLen);

/**
 * @brief Copy data from FIFO to buffer  
 * @param[out] dst pointer to destination data
 * @param[in]  src pointer to source data
 * @param[in]  word length 
 * @return Cpy_OK: success; others: fail.
 * @note
 */
uint32_t FIFOToBuf(void *dst, volatile uint32_t *src, uint32_t wordLen);
/**
 * @brief compare two big number(scrambling sequence)
 * @param[in] a pointer to one big number
 * @param[in] b pointer to another big number
 * @param[in] word length of a or b
 * @param[in] order pointer to scrambling sequence
 * @return Cmp_GREATER: a > b; Cmp_LESS: a < b;Cmp_EQUAL: a==b.
 * @note 1. word little-endian; in a word, it's byte little-endian
 */
int32_t Cmp_U32_S(const uint32_t *a, const uint32_t *b, uint32_t wordLen, const uint8_t *order);


/**
 * @brief compare a and b in byte length
 * @param[in] a   
 * @param[in] b 
 * @param[in] byteLen
 * @param[in] order
 * @return Cmp_LESS, a < b    Cmp_EQUAL, a = b    Cmp_GREATER, a > b   Cmp_ERROR, error happens
 * @note a[8]={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x89}, b[8]={0x12,0x22,0x33,0x44,0x55,0x66,0x77,0x88}  Cmp_U8_S(a,b) = Cmp_LESS
 */

int32_t Cmp_U8_S(const uint8_t *a, const uint8_t *b, uint32_t byteLen, const uint8_t *order);
#endif

