/***********************************************************************
 * Filename    : sha256.h
 * Description : sha256 header file
 * Author(s)   : Eric  
 * version     : V1.0
 * Modify date : 2020-07-09
 ***********************************************************************/

#ifndef __SHA256_H__
#define __SHA256_H__

#include "ACM32Fxx_HAL.h"

/**********************************************************
*	structure
**********************************************************/
//SHA256 context
typedef struct {
  UINT32 state[8];                                   //state (ABCD)
  UINT32 count[2];        // number of bits, modulo 2^64 (msb first) 
  uint8_t  buffer[64];                         // input buffer
} SHA256_CTX;

/**********************************************************
*	extern functions
***********************************************************/
void SHA_memcpy (uint8_t *output,uint8_t *input, UINT32 len);
void SHA_memset (uint8_t *output, int value, UINT32 len);
void SHA_encode (uint8_t *output, UINT32 *input, UINT32 len);
/**********************************************************
*	extern variable
***********************************************************/
extern const unsigned char PADDING[128];

/**************************************************************************
* Function Name  : HAL_SHA256_Init
* Description    : SHA256 initialization. Begins an SHA1 operation, writing a new context.
* Input          : None
* Output         : - *context : the point of sha1 context
* Return         : None
**************************************************************************/
void HAL_SHA256_Init(SHA256_CTX *context);
	
/**************************************************************************
* Function Name  : HAL_SHA256_Update
* Description    : SHA256 block update operation. Continues an SHA1 message-digest
*				 : operation, processing another message block, and updating the
*				 : context.
* Input          : - *context : context before transform
*				 : - *input   : input message
*                : - inputlen : the byte length of input message
* Output		 : - *context : context after transform
* Return         : None
**************************************************************************/
void HAL_SHA256_Update(SHA256_CTX *context, uint8_t *input,UINT32 inputLen);

/**************************************************************************
* Function Name  : HAL_SHA256_Final
* Description    : SHA256 finalization. Ends an SHA256 message-digest operation, writing the
*                : the message digest and zeroizing the context.
* Input          : - *context : context before transform
* Output		 : - *digest  : message digest
* Return         : None
**************************************************************************/
void HAL_SHA256_Final(uint8_t *digest, SHA256_CTX *context);

/**************************************************************************
* Function Name  : HAL_SHA256_Hash
* Description    : transform message to digest in SHA1 algorithm
* Input          : - *pDataIn : input message to be tranformed;
				 : - DataLen  : the byte length of message;
* Output		 : - *pDigest : output the digest;
* Return         : None
**************************************************************************/
void HAL_SHA256_Hash(uint8_t *pDataIn,UINT32 DataLen,uint8_t *pDigest);

#endif
