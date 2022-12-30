/* aes.h - header file for aes.c
 */

#ifndef __AIR_AES_H
#define __AIR_AES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "air_crypt.h"

#define AIR_AES_OPT_MODE_Mask        (BIT(0))
#define AIR_AES_OPT_MODE_ENCRYPT     (0)
#define AIR_AES_OPT_MODE_DECRYPT     (BIT(0))

#define AIR_AES_OPT_BLK_Mask         (BIT(1)|BIT(2))
#define AIR_AES_OPT_BLK_CBC          (BIT(1))
#define AIR_AES_OPT_BLK_ECB          (BIT(2))
#define AIR_AES_OPT_BLK_CBC_MAC      (BIT(1)|BIT(2))

#define AIR_AES_OPT_KEY_LEN_Mask     (BIT(3)|BIT(4))
#define AIR_AES_OPT_KEY_128          (BIT(3))
#define AIR_AES_OPT_KEY_192          (BIT(4))
#define AIR_AES_OPT_KEY_256          (BIT(3)|BIT(4))

#define AIR_RET_AES_INIT                         (0x5471B9AA)
#define AIR_RET_AES_PARAM_ERR                    (AIR_RET_AES_INIT + 0x01)
#define AIR_RET_AES_TRNG_ERR                     (AIR_RET_AES_INIT + 0x02)
#define AIR_RET_AES_MODE_ERROR                   (AIR_RET_AES_INIT + 0x03)
#define AIR_RET_AES_DFA_LOCK                     (AIR_RET_AES_INIT + 0x04)
#define AIR_RET_AES_PACK_MODE_ERROR              (AIR_RET_AES_INIT + 0x05)
#define AIR_RET_AES_OUTBUF_TOO_SMALL             (AIR_RET_AES_INIT + 0x06)
#define AIR_RET_AES_INPUT_SIZE_ERROR             (AIR_RET_AES_INIT + 0x07)
#define AIR_RET_AES_KEY_SIZE_ERROR               (AIR_RET_AES_INIT + 0x08)
#define AIR_RET_AES_ATTACKED                     (AIR_RET_AES_INIT + 0x09)
#define AIR_RET_AES_SUCCESS                      (AIR_RET_AES_INIT + 0x0100)

uint32_t AIRAES_EncDec(AIR_SYM_CRYPT_CALL *pCall);

#endif

#ifdef __cplusplus
}
#endif

