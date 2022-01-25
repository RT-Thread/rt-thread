/***********************************************************************
 * Filename    : sha1.h
 * Description : sha1 header file
 * Author(s)   : firmware team   
 * version     : V1.0
 * Modify date : 2020-07-29
 ***********************************************************************/
#ifndef __SHA1_H__
#define __SHA1_H__

#include "ACM32Fxx_HAL.h"
/**********************************************************
*	structure
**********************************************************/
//SHA1 context
typedef struct {
  UINT32 state[5];        //state (ABCD)
  UINT32 count[2];        // number of bits, modulo 2^64 (msb first) 
  uint8_t  buffer[64];    // input buffer
} SHA1_CTX;

/**************************************************************************
* Function Name  : HAL_SHA1_Init
* Description    : SHA1 initialization. Begins an SHA1 operation, writing a new context.
* Input          : None
* Output         : - *context : the point of sha1 context
* Return         : None
**************************************************************************/
void HAL_SHA1_Init(SHA1_CTX *context);	

/**************************************************************************
* Function Name  : HAL_SHA1_Update
* Description    : SHA1 block update operation. Continues an SHA1 message-digest
*				 : operation, processing another message block, and updating the
*				 : context.
* Input          : - *context : context before transform
*				 : - *input   : input message
*                : - inputlen : the byte length of input message
* Output		 : - *context : context after transform
* Return         : None
**************************************************************************/
void HAL_SHA1_Update(SHA1_CTX *context,uint8_t *input,UINT32 inputLen);

/**************************************************************************
* Function Name  : HAL_SHA1_Final
* Description    : SHA1 finalization. Ends an MD5 message-digest operation, writing the
*                : the message digest and zeroizing the context.
* Input          : - *context : context before transform
* Output		 : - *digest  : message digest
* Return         : None
**************************************************************************/
void HAL_SHA1_Final(uint8_t *digest, SHA1_CTX *context);
	
/**************************************************************************
* Function Name  : HAL_SHA1_Hash
* Description    : transform message to digest in SHA1 algorithm
* Input          : - *pDataIn : input message to be tranformed;
				 : - DataLen  : the byte length of message;
* Output		 : - *pDigest : output the digest;
* Return         : None
**************************************************************************/
void HAL_SHA1_Hash(uint8_t *pDataIn,UINT32 DataLen,uint8_t *pDigest);
	
/**************************************************************************
* Function Name  : SHA_encode
* Description    : Encodes input (UINT32) into output (unsigned char)[Big-Endian]
* Input          : - *input   : input data to be tranformed;
				 : -  len     : byte len of the input data(len is a multiple of 4);
* Output		 : - *output  : output data;
* Return         : None
**************************************************************************/
void SHA_encode (uint8_t *output, UINT32 *input, UINT32 len);
void SHA_memcpy (uint8_t *output,uint8_t *input, UINT32 len);
void SHA_memset (uint8_t *output, int value, UINT32 len);


#endif
