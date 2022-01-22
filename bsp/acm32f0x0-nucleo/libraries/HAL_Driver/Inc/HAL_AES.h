/***********************************************************************
 * Copyright (c)  2008 - 2016, Shanghai AisinoChip Co.,Ltd .
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

#define AES_ENCRYPTION          1
#define AES_DECRYPTION          0
#define AES_ECB_MODE            0
#define AES_CBC_MODE            1
#define AES_SWAP_ENABLE         1
#define AES_SWAP_DISABLE        0

#define AES_NORMAL_MODE     0x12345678
#define AES_SECURITY_MODE   0

#define AES_KEY_128     0
#define AES_KEY_192     1
#define AES_KEY_256     2

#define AES_FAIL   0x00
#define AES_PASS   0xa59ada68

/******************************************************************************
Name:      HAL_AES_Set_Key
Function:  set aes key for encryption and decryption
Input:
           keyin     --    pointer to buffer of key
           swap_en   --    AES_SWAP_ENABLE, AES_SWAP_DISABLE
Return:    None
*******************************************************************************/
void HAL_AES_Set_Key(UINT32 *keyin, UINT8 key_len, UINT8 swap_en);
void HAL_AES_Set_Key_U8(UINT8 *keyin, UINT8 key_len, UINT8 swap_en);


/******************************************************************************

Name:        HAL_Aes_Crypt
Function:    Function for des encryption and decryption
Input:
             indata            --  pointer to buffer of input
             outdata           --  pointer to buffer of result
             block_len         --  block(128bit) length for des cryption
             operation         --  AES_ENCRYPTION,AES_DECRYPTION
             mode              --  AES_ECB_MODE, AES_CBC_MODE,
             iv                --  initial vector for CBC mode
             security_mode     --  AES_NORMAL_MODE, AES_SECURITY_MDOE，
Return:      None

*******************************************************************************/
UINT32 HAL_AES_Crypt(
    UINT32 *indata,
    UINT32 *outdata,
    UINT32 block_len,
    UINT8  operation,
    UINT8  mode,
    UINT32 *iv,
    UINT32 security_mode
);


UINT32 HAL_AES_Crypt_U8(
    UINT8 *indata,
    UINT8 *outdata,
    UINT32 block_len,
    UINT8  operation,
    UINT8  mode,
    UINT8 *iv,
    UINT32 security_mode
);

#endif
/******************************************************************************
 * end of file
*******************************************************************************/
