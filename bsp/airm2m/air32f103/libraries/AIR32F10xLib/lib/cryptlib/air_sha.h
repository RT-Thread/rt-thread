
#ifndef __AIR_SHA_H
#define __AIR_SHA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "air_crypt.h"


#define AIR_RET_SHA_INIT                         (0x576C39AA)
#define AIR_RET_SHA_PARAM_ERR                    ((AIR_RET_SHA_INIT + 0x01))
#define AIR_RET_SHA_BUSY                         ((AIR_RET_SHA_INIT + 0x02))
#define AIR_RET_SHA_MODE_ERR                     ((AIR_RET_SHA_INIT + 0x03))
#define AIR_RET_SHA_SUCCESS                      ((AIR_RET_SHA_INIT + 0x0100))


typedef struct
{
    uint32_t au32Total[2];
    uint8_t au8Buffer[64];
    uint32_t au32State[5];
}AIRSHA1_Context;

typedef struct
{
    uint32_t au32Total[2];
    uint8_t  au8Buffer[64];
    uint32_t au32State[8];
}AIRSHA2_Context;

typedef enum
{
    AIRSHA1 = 0,
    AIRSHA224 = 1,
    AIRSHA256 = 2,
//    AIRSHA384 = 3,
//    AIRSHA512 = 4
}AIRSHA_MOD_TYPE;

uint32_t AIRSHA1_Starts(AIRSHA1_Context *pCtx);
uint32_t AIRSHA1_Update(AIRSHA1_Context *pCtx, const uint8_t *pu8Input, uint32_t u32InputLen);
uint32_t AIRSHA1_Finish(AIRSHA1_Context *pCtx, uint8_t au8Digest[20]);

uint32_t AIRSHA256_Starts(AIRSHA2_Context *pCtx);
uint32_t AIRSHA256_Update(AIRSHA2_Context *pCtx, const uint8_t *pu8Input, uint32_t u32InputLen);
uint32_t AIRSHA256_Finish(AIRSHA2_Context *pCtx, uint8_t au8Digest[32]);

uint32_t AIRSHA_Sha(AIRSHA_MOD_TYPE ShaType, const uint8_t *pu8Input, uint32_t u32Ibytes, uint8_t *pu8Output, uint32_t u32Outlen);

#ifdef __cplusplus
}
#endif

#endif
