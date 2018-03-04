/*!
*****************************************************************************
** \file        gd_lib/GK7101/inc/crypto.h
**
** \version     $Id$
**
** \brief
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#ifndef _CRYPTO_H_
#define _CRYPTO_H_



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************
/*!
*******************************************************************************
**
** \brief CRYPTO mode.
**
*******************************************************************************
*/
typedef enum
{
   GD_CRYPTO_DES    = 0,    // used DES
   GD_CRYPTO_AES_128,       // used AES_128
   GD_CRYPTO_AES_192,       // used AES_192
   GD_CRYPTO_AES_256,       // used AES_256
   GD_CRYPTO_MODE_MAX,      //
}GD_CRYPTO_MODE_E;
//GD_INT_AES_OUTPUT_READY_IRQ = (13 + 32),  //!< edge, AES output ready from Crypt block
//GD_INT_DES_OUTPUT_READY_IRQ = (14 + 32),  //!< edge, DES output ready from Crypt block


//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************
typedef struct
{
    U32     key_hi;
    U32     key_lo;
}GD_CRYPTO_DES_KEY_T;

typedef struct
{
    U32     key_127_96;
    U32     key_95_64;
    U32     key_63_32;
    U32     key_31_0;
}GD_CRYPTO_AES128_KEY_T;

typedef struct
{
    U32     key_191_160;
    U32     key_159_128;
    U32     key_127_96;
    U32     key_95_64;
    U32     key_63_32;
    U32     key_31_0;
}GD_CRYPTO_AES192_KEY_T;

typedef struct
{
    U32     key_255_224;
    U32     key_223_192;
    U32     key_191_160;
    U32     key_159_128;
    U32     key_127_96;
    U32     key_95_64;
    U32     key_63_32;
    U32     key_31_0;
}GD_CRYPTO_AES256_KEY_T;

typedef union
{
    U32                     key[8];
    GD_CRYPTO_DES_KEY_T     des_key;
    GD_CRYPTO_AES128_KEY_T  aes128_key;
    GD_CRYPTO_AES192_KEY_T  aes192_key;
    GD_CRYPTO_AES256_KEY_T  aes256_key;
}GD_CRYPTO_KEY_T;

typedef struct
{
    U32     data_hi;
    U32     data_lo;
}GD_CRYPTO_DES_DATA_T;

typedef struct
{
    U32     data_127_96;
    U32     data_95_64;
    U32     data_63_32;
    U32     data_31_0;
}GD_CRYPTO_AES_DATA_T;

typedef union
{
    U32                     data[4];
    GD_CRYPTO_DES_DATA_T    des_data;
    GD_CRYPTO_AES_DATA_T    aes_data;
}GD_CRYPTO_DATA_T;

typedef struct
{
    GD_CRYPTO_MODE_E    mode;
    GD_CRYPTO_KEY_T*    pkey;
    GBOOL               useint;
    GISR2               (*notifyFct)(void);
}GD_CRYPTO_OpenParamsT;


//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************
GERR GD_CRYPTO_Open(GD_CRYPTO_OpenParamsT* pOpenParams, GD_HANDLE* pHandle);
GERR GD_CRYPTO_Close(GD_HANDLE* pHandle);
GERR GD_CRYPTO_EncrptData(GD_HANDLE handle, GD_CRYPTO_DATA_T* data_in, GD_CRYPTO_DATA_T* data_out);
GERR GD_CRYPTO_DecrptData(GD_HANDLE handle, GD_CRYPTO_DATA_T* data_in, GD_CRYPTO_DATA_T* data_out);

//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************



#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif



#endif /* _CRYPTO_H_ */

