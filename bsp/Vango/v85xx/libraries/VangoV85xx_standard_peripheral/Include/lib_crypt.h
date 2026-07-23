/**
  ******************************************************************************
  * @file    lib_crypt.h
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   CRYPT library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_CRYPT_H
#define __LIB_CRYPT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
//Length
#define CRYPT_LENGTH_32    CRYPT_CTRL_LENGTH_32
#define CRYPT_LENGTH_64    CRYPT_CTRL_LENGTH_64
#define CRYPT_LENGTH_96    CRYPT_CTRL_LENGTH_96
#define CRYPT_LENGTH_128   CRYPT_CTRL_LENGTH_128
#define CRYPT_LENGTH_160   CRYPT_CTRL_LENGTH_160
#define CRYPT_LENGTH_192   CRYPT_CTRL_LENGTH_192
#define CRYPT_LENGTH_224   CRYPT_CTRL_LENGTH_224
#define CRYPT_LENGTH_256   CRYPT_CTRL_LENGTH_256                
#define CRYPT_LENGTH_288   CRYPT_CTRL_LENGTH_288
#define CRYPT_LENGTH_320   CRYPT_CTRL_LENGTH_320
#define CRYPT_LENGTH_352   CRYPT_CTRL_LENGTH_352  
#define CRYPT_LENGTH_384   CRYPT_CTRL_LENGTH_384
#define CRYPT_LENGTH_416   CRYPT_CTRL_LENGTH_416
#define CRYPT_LENGTH_448   CRYPT_CTRL_LENGTH_448
#define CRYPT_LENGTH_480   CRYPT_CTRL_LENGTH_480
#define CRYPT_LENGTH_512   CRYPT_CTRL_LENGTH_512
//Nostop
#define CRYPT_STOPCPU     (0)
#define CRYPT_NOSTOPCPU    CRYPT_CTRL_NOSTOP 
   
/* Private macros ------------------------------------------------------------*/
#define IS_CRYPT_ADDR(__ADDR__)  (((__ADDR__) < 0x8000) &&\
                                  (((__ADDR__) & 0x3U) == 0U))

#define IS_CRYPT_LENGTH(__LENGTH__)  (((__LENGTH__) == CRYPT_LENGTH_32)  ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_64)  ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_32)  ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_96)  ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_128) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_160) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_192) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_224) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_256) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_288) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_320) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_352) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_384) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_416) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_448) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_480) ||\
                                      ((__LENGTH__) == CRYPT_LENGTH_512))

#define IS_CRYPT_NOSTOP(__NOSTOP__)  (((__NOSTOP__) == CRYPT_STOPCPU) || ((__NOSTOP__) == CRYPT_NOSTOPCPU))

/* Exported Functions ------------------------------------------------------- */
void CRYPT_AddressAConfig(uint16_t AddrA);
void CRYPT_AddressBConfig(uint16_t AddrB);
void CRYPT_AddressOConfig(uint16_t AddrO);
uint8_t CRYPT_GetCarryBorrowBit(void);
void CRYPT_StartAdd(uint32_t Length, uint32_t Nostop);
void CRYPT_StartMultiply(uint32_t Length, uint32_t Nostop);
void CRYPT_StartSub(uint32_t Length, uint32_t Nostop);
void CRYPT_StartRShift1(uint32_t Length, uint32_t Nostop);
void CRYPT_WaitForLastOperation(void);

                           
#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_CRYPT_H */

/*********************************** END OF FILE ******************************/
