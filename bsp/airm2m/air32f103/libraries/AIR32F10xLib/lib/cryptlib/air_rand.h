/* rand.h - header file for rand.c
 */

#ifndef __AIR_RAND_H
#define __AIR_RAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "air_crypt.h"


#define AIR_RET_RAND_INIT                         (0x562F79AA)
#define AIR_RET_RAND_PARAM_ERR                    (AIR_RET_RAND_INIT + 1)
#define AIR_RET_RAND_FAILURE                      (AIR_RET_RAND_INIT + 2)
#define AIR_RET_RAND_LEN_ERR                      (AIR_RET_RAND_INIT + 3)
#define AIR_RET_RAND_TRNG_EMPTY                   (AIR_RET_RAND_INIT + 4)
#define AIR_RET_RAND_SUCCESS                      (AIR_RET_RAND_INIT + 0X0100)

#define RAND_PARAM_ERRNO                         (-5500)
#define RAND_CHECK_ERRNO                         (-5501)

#define AIR_RAND_BUFFER_OK               ((uint16_t)(0xA5A5UL))

uint32_t AIRRAND_Init(void *pu32Buff, uint32_t u32BuffSize);

uint32_t AIRRAND_Trand(void *pvDst, uint32_t u32Len, uint32_t *pu32CrcInit, uint32_t *pu32CrcEnd);

int32_t AIRRAND_TrandNoBlk(void *pvDst, uint32_t u32Len, uint32_t *pu32CrcInit, uint32_t *pu32CrcEnd);

uint32_t AIRRAND_Prand(void *pvDst, uint32_t u32Len);

uint32_t AIRCRC_CalcBuff(uint16_t u16CrcInit, void *pvData, uint32_t u32Size);

uint32_t AIRRAND_UpdatePSeed(void);

#ifdef __cplusplus
}
#endif

#endif


