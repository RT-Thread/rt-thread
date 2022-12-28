/* des.h - header file for des.c
 */

#ifndef __AIR_DES_H
#define __AIR_DES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "air_crypt.h"


#define AIR_RET_DES_INIT                         (0x55D659AA)
#define AIR_RET_DES_PARAM_ERR                    (AIR_RET_DES_INIT + 0x1)
#define AIR_RET_DES_TRNG_ERR                     (AIR_RET_DES_INIT + 0x2)
#define AIR_RET_DES_PACK_MODE_ERROR              (AIR_RET_DES_INIT + 0x3)
#define AIR_RET_DES_INPUT_SIZE_ERROR             (AIR_RET_DES_INIT + 0x4)
#define AIR_RET_DES_MODE_ERROR                   (AIR_RET_DES_INIT + 0x5)
#define AIR_RET_DES_ATTACKED                     (AIR_RET_DES_INIT + 0x6)
#define AIR_RET_DES_OUTBUF_TOO_SMALL             (AIR_RET_DES_INIT + 0x7)
#define AIR_RET_DES_DFA_LOCK                     (AIR_RET_DES_INIT + 0x8)
#define AIR_RET_DES_KEY_SIZE_ERROR               (AIR_RET_DES_INIT + 0x9)
#define AIR_RET_DES_SUCCESS                      (AIR_RET_DES_INIT + 0x0100)



#define AIR_DES_OPT_MODE_Mask        (BIT(0))
#define AIR_DES_OPT_MODE_ENCRYPT     (0)
#define AIR_DES_OPT_MODE_DECRYPT     (BIT(0))
#define AIR_DES_OPT_BLK_Mask         (BIT(1)|BIT(2))
#define AIR_DES_OPT_BLK_CBC          (BIT(1))
#define AIR_DES_OPT_BLK_ECB          (BIT(2))
#define AIR_DES_OPT_BLK_CBC_MAC      (BIT(1)|BIT(2))

#define AIR_TDES_OPT_KEY_LEN_Mask    (BIT(3))
#define AIR_TDES_OPT_KEY_2           (0)
#define AIR_TDES_OPT_KEY_3           (BIT(3))

uint32_t AIRDES_EncDec(AIR_SYM_CRYPT_CALL *pCall);

uint32_t AIRTDES_EncDec(AIR_SYM_CRYPT_CALL *pCall);

#ifdef __cplusplus
}
#endif

#endif
