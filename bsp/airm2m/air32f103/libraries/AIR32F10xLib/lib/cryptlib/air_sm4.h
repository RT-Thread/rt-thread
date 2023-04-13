/* sm4.h - header file for sm4.c
 */

#ifndef __AIR_SM4_H
#define __AIR_SM4_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdint.h>
#include "air_crypt.h"

#define AIR_SM4_OPT_MODE_Mask        (BIT(0))
#define AIR_SM4_OPT_MODE_ENCRYPT     (0)
#define AIR_SM4_OPT_MODE_DECRYPT     (BIT(0))

#define AIR_SM4_OPT_BLK_Mask         (BIT(1)|BIT(2))
#define AIR_SM4_OPT_BLK_CBC          (BIT(1))
#define AIR_SM4_OPT_BLK_ECB          (BIT(2))
#define AIR_SM4_OPT_BLK_CBC_MAC      (BIT(1)|BIT(2))





#define AIR_RET_SM4_INIT                         (0x584E69AA)
#define AIR_RET_SM4_PARAM_ERR                    (AIR_RET_SM4_INIT + 0x01)
#define AIR_RET_SM4_TRNG_ERR                     (AIR_RET_SM4_INIT + 0x02)
#define AIR_RET_SM4_PACK_MODE_ERROR              (AIR_RET_SM4_INIT + 0x03)
#define AIR_RET_SM4_OUTBUF_TOO_SMALL             (AIR_RET_SM4_INIT + 0x04)
#define AIR_RET_SM4_INPUT_SIZE_ERROR             (AIR_RET_SM4_INIT + 0x05)
#define AIR_RET_SM4_ATTACKED                     (AIR_RET_SM4_INIT + 0x06)
#define AIR_RET_SM4_MODE_ERROR                   (AIR_RET_SM4_INIT + 0x07)
#define AIR_RET_SM4_SUCCESS                      (AIR_RET_SM4_INIT + 0x0100)

uint32_t AIRSM4_EncDec(AIR_SYM_CRYPT_CALL *pCall);


#endif


#ifdef __cplusplus
}
#endif

