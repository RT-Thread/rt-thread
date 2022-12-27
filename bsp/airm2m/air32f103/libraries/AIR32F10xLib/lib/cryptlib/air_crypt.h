#ifndef __AIR_CRYPT_H
#define __AIR_CRYPT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include "air32f10x.h"

void AIRCRYPT_SYMCITClear(void);

void AIRCRYPT_ASYMCITClear(void);

void AIRCRYPT_SetBusKey(uint32_t pu32Key[2]);

void AIRCRYPT_CramInit(void);

void AIRCRYPT_CramKeySet(uint32_t pu32Key[2]);

void AIRCRYPT_CramKeyReset(void);

void AIRCRYPT_SecureEnable(void);

void AIRCRYPT_SecureDisable(void);

typedef struct
{
    uint8_t *pu8In;
    uint8_t *pu8Out;
    uint8_t *pu8IV;
    uint8_t *pu8IVout;
    uint8_t *pu8Key;
    uint32_t u32InLen;
    uint32_t u32OutLen;
    uint16_t u16Opt;
    uint32_t u32Crc;
} AIR_SYM_CRYPT_CALL;

#ifdef __cplusplus
}
#endif

#endif // __AIR_CRYPT_H
