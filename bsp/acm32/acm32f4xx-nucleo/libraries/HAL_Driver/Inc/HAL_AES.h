/***********************************************************************
 * All rights reserved.
 * Filename    : aes.h
 * Description : aes driver header file
 * Author(s)   : Eric  
 * version     : V1.0
 * Modify date : 2016-03-24
 ***********************************************************************/
#ifndef __AES_H__
#define __AES_H__

#include "ACM32Fxx_HAL.h"

#define AES_ENCRYPTION   		1
#define AES_DECRYPTION   		0
#define AES_ECB_MODE	   		0
#define AES_CBC_MODE	   		1 
#define AES_SWAP_ENABLE  		1
#define AES_SWAP_DISABLE 		0

#define AES_NORMAL_MODE   	0x12345678
#define AES_SECURITY_MODE 	0

#define AES_KEY_128     0
#define AES_KEY_192     1
#define AES_KEY_256     2

#define AES_FAIL   0x00
#define AES_PASS   0xa59ada68

#define BIT_AES        (1<<28)

/************************************************************************
 * function   : delay
 * Description: delay for a while.  
 * input : 
 *         count: count to decrease 
 * return: none 
 ************************************************************************/
 extern void delay(uint32_t count);
 

/******************************************************************************
 * Name:     HAL_AES_SetKey
 * Function: set key of AES
 * Input:
		     keyin		 --	pointer to buffer of key 
		     key_len     --	select length of key(AES_KEY_128/ AES_KEY_192/ AES_KEY_256) 					
		     swap_en     -- AES_SWAP_ENABLE, AES_SWAP_DISABLE						
 * Return:	 None
*******************************************************************************/
void HAL_AES_SetKey(UINT32 *keyin, UINT8 key_len, UINT8 swap_en);
void HAL_AES_SetKey_U8(UINT8 *keyin, UINT8 key_len, UINT8 swap_en);


/******************************************************************************
Name:		 HAL_AES_Crypt
Function:	 Function for AES encryption and decryption
Input:
         indata		       --   pointer to buffer of input
         outdata	       --	pointer to buffer of result
         block_len	       --	block(128bit) length for aes cryption
         operation	       --	AES_ENCRYPTION,AES_DECRYPTION
         mode              --   AES_ECB_MODE, AES_CBC_MODE,
         iv                --   initial vector for CBC mode
         security_mode     --   AES_NORMAL_MODE, AES_SECURITY_MODE
Return:	 None

*******************************************************************************/
uint32_t HAL_AES_Crypt(
    uint32_t *indata,
    uint32_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint32_t *iv,
    uint32_t security_mode
);


uint32_t HAL_AES_Crypt_U8(
    uint8_t *indata,
    uint8_t *outdata,
    uint32_t block_len,
    uint8_t  operation,
    uint8_t  mode,
    uint8_t *iv,
    uint32_t security_mode
);

#endif
/******************************************************************************
 * end of file
*******************************************************************************/
