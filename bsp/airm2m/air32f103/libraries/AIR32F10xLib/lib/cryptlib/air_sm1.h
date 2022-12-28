#ifndef __AIR_SM1_H      /* ToDo: replace '<Device>' with your device name */
#define __AIR_SM1_H

#ifdef __cplusplus
    extern "C"
    {
#endif

#include "air_crypt.h"
#include <stdint.h>

#define AIR_SM1_OPT_MODE_Mask            (BIT(0))
#define AIR_SM1_OPT_MODE_ENCRYPT         (0)
#define AIR_SM1_OPT_MODE_DECRYPT         (BIT(0))

#define AIR_SM1_OPT_BLK_Mask             (BIT(1)|BIT(2))
#define AIR_SM1_OPT_BLK_ECB              (BIT(1))
#define AIR_SM1_OPT_BLK_CBC              (BIT(2))
#define AIR_SM1_OPT_BLK_CBC_MAC          (BIT(1)|BIT(2))

#define AIR_SM1_OPT_KEY_LEN_Mask         (BIT(3)|BIT(4))
#define AIR_SM1_OPT_KEY_128              (BIT(3))
#define AIR_SM1_OPT_KEY_192              (BIT(4))
#define AIR_SM1_OPT_KEY_256              (BIT(3)|BIT(4))

#define AIR_SM1_OPT_ROUND_Mask           (BIT(5)|BIT(6))
#define AIR_SM1_OPT_ROUND_8              (0)
#define AIR_SM1_OPT_ROUND_10             (BIT(5))
#define AIR_SM1_OPT_ROUND_12             (BIT(6))
#define AIR_SM1_OPT_ROUND_14             (BIT(5)|BIT(6))

#define AIR_RET_SM1_INIT                     (0x5B1689AA)
#define AIR_RET_SM1_PARAM_ERR                (AIR_RET_SM1_INIT + 0x01)
#define AIR_RET_SM1_TRNG_ERR                 (AIR_RET_SM1_INIT + 0x02)
#define AIR_RET_SM1_KEY_LEN_ERR              (AIR_RET_SM1_INIT + 0x03)
#define AIR_RET_SM1_ROUND_ERR                (AIR_RET_SM1_INIT + 0x04)
#define AIR_RET_SM1_MODE_ERROR               (AIR_RET_SM1_INIT + 0x05)
#define AIR_RET_SM1_BLK_ERROR                (AIR_RET_SM1_INIT + 0x06)
#define AIR_RET_SM1_ATTACKED                 (AIR_RET_SM1_INIT + 0x07)
#define AIR_RET_SM1_INPUT_SIZE_ERROR         (AIR_RET_SM1_INIT + 0x08)
#define AIR_RET_SM1_SUCCESS                  (AIR_RET_SM1_INIT + 0x0100)

uint32_t AIRSM1_EncDec(AIR_SYM_CRYPT_CALL *pCall);



#ifdef __cplusplus
    }
#endif


#endif
