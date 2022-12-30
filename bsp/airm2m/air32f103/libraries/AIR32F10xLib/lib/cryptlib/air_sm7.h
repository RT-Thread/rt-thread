#ifndef _AIR_SM7_H_
#define _AIR_SM7_H_

#include "air_crypt.h"

#define AIR_SM7_OPT_MODE_Mask        (BIT(0))
#define AIR_SM7_OPT_MODE_ENCRYPT     (0)
#define AIR_SM7_OPT_MODE_DECRYPT     (BIT(0))
#define AIR_SM7_OPT_BLK_Mask         (BIT(1)|BIT(2))
#define AIR_SM7_OPT_BLK_CBC          (BIT(1))
#define AIR_SM7_OPT_BLK_ECB          (BIT(2))
#define AIR_SM7_OPT_BLK_CBC_MAC      (BIT(1)|BIT(2))

#define AIR_RET_SM7_INIT                         (0x5C3479AA)
#define AIR_RET_SM7_PARAM_ERR                    (AIR_RET_SM7_INIT + 1)
#define AIR_RET_SM7_MODE_ERROR                   (AIR_RET_SM7_INIT + 2)
#define AIR_RET_SM7_PACK_MODE_ERROR              (AIR_RET_SM7_INIT + 3)
#define AIR_RET_SM7_OUTBUF_TOO_SMALL             (AIR_RET_SM7_INIT + 4)
#define AIR_RET_SM7_INPUT_SIZE_ERROR             (AIR_RET_SM7_INIT + 5)
#define AIR_RET_SM7_ATTACKED                     (AIR_RET_SM7_INIT + 6)
#define AIR_RET_SM7_SUCCESS                      (AIR_RET_SM7_INIT + 0x0100)


uint32_t AIRSM7_EncDec(AIR_SYM_CRYPT_CALL *pCall);

#endif // _AIR_SM7_H_
