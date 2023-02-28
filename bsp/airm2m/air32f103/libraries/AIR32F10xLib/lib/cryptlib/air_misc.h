#ifndef __AIR_MISC_H
#define __AIR_MISC_H

#ifdef __cplusplus
    extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "air_crypt.h"


#define AIR_CMP_INIT                 (0x00AA)
#define AIR_CMP_EQUAL                (0x05AA)
#define AIR_CMP_BIGGER               (0xA5AA)
#define AIR_CMP_SMALLER              (0x25AA)
#define AIR_CMP_ERR                  (0xAAAA)
#define AIR_CMP_UNEQUAL              (0x85AA)
#define AIR_RET_MISC_PARAM_ERR        (0x51B649AB)


uint32_t AIRMEM_SCopy(void *pvDst, void *pvSrc, uint32_t u32ByteLen, uint8_t *pu8Index);

uint32_t AIRMEM_SEqual(void *pvDst, void *pvSrc, uint32_t u32ByteLen, uint8_t *pu8Index);

uint32_t AIRMEM_SCopyBig(void *pvDst, void *pvSrc, uint32_t u32DstLen, uint32_t u32SrcLen, uint8_t *pu8Index);

uint32_t AIRMEM_CopyBig(void  *pvDst, void  *pvSrc, uint32_t u32DstLen, uint32_t u32SrcLen);

uint32_t AIRMEM_Equal(void *pvDst, void *pvSrc, uint32_t u32ByteLen);


#ifdef __cplusplus
}
#endif

#endif
