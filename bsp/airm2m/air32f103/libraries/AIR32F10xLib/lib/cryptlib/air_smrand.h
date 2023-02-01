
#ifndef __AIR_SMRAND_H
#define __AIR_SMRAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "air_crypt.h"

#define AIR_RET_SMRAND_INIT                       (0x5D6c39AA)
#define AIR_RET_SMRAND_PARAM_ERR                  (AIR_RET_SMRAND_INIT + 1)
#define AIR_RET_SMRAND_CHECK_FAILURE              (AIR_RET_SMRAND_INIT + 2)
#define AIR_RET_SMRAND_CHECK_SUCCESS              (AIR_RET_SMRAND_INIT + 0X0100)

uint32_t Rand_Check(uint8_t *pu8Src, uint32_t u32Len, uint32_t u32Mask);

#ifdef __cplusplus
}
#endif

#endif /*  __AIR_SMRAND_H  */
