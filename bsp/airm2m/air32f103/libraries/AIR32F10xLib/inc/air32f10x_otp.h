/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AIR32F10x_OTP_H
#define __AIR32F10x_OTP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air32f10x.h"

/** @addtogroup air32f10x_StdPeriph_Driver
  * @{
  */

/** @addtogroup OTP
  * @{
  */

#define OTP_PAGE_NUM        (32)
#define OTP_POWERON_TIME    (200)

enum OTP_ADDRESS{
    OTP_ADDRESS_0 = 0,
    OTP_ADDRESS_1,
    OTP_ADDRESS_2,
    OTP_ADDRESS_3,
    OTP_ADDRESS_4,
    OTP_ADDRESS_5,
    OTP_ADDRESS_6,
    OTP_ADDRESS_7,
    OTP_ADDRESS_8,
    OTP_ADDRESS_9,
    OTP_ADDRESS_10,
    OTP_ADDRESS_11,
    OTP_ADDRESS_12,
    OTP_ADDRESS_13,
    OTP_ADDRESS_14,
    OTP_ADDRESS_15,
    OTP_ADDRESS_16,
    OTP_ADDRESS_17,
    OTP_ADDRESS_18,
    OTP_ADDRESS_19,
    OTP_ADDRESS_20,
    OTP_ADDRESS_21,
    OTP_ADDRESS_22,
    OTP_ADDRESS_23,
    OTP_ADDRESS_24,
    OTP_ADDRESS_25,
    OTP_ADDRESS_26,
    OTP_ADDRESS_27,
    OTP_ADDRESS_28,
    OTP_ADDRESS_29,
    OTP_ADDRESS_30,
    OTP_ADDRESS_31,
};

#define IS_OTP_ADDRESS(ADDRESS)         (((ADDRESS) == OTP_ADDRESS_0) || ((ADDRESS) == OTP_ADDRESS_1) || ((ADDRESS) == OTP_ADDRESS_3) || ((ADDRESS) == OTP_ADDRESS_5) \
                                        ((ADDRESS) == OTP_ADDRESS_6) || ((ADDRESS) == OTP_ADDRESS_7) || ((ADDRESS) == OTP_ADDRESS_8) || ((ADDRESS) == OTP_ADDRESS_9) \
                                        ((ADDRESS) == OTP_ADDRESS_10) || ((ADDRESS) == OTP_ADDRESS_11) || ((ADDRESS) == OTP_ADDRESS_12) || ((ADDRESS) == OTP_ADDRESS_13) \
                                        ((ADDRESS) == OTP_ADDRESS_14) || ((ADDRESS) == OTP_ADDRESS_15) || ((ADDRESS) == OTP_ADDRESS_16) || ((ADDRESS) == OTP_ADDRESS_17) \
                                        ((ADDRESS) == OTP_ADDRESS_18) || ((ADDRESS) == OTP_ADDRESS_19) || ((ADDRESS) == OTP_ADDRESS_20) || ((ADDRESS) == OTP_ADDRESS_21) \
                                        ((ADDRESS) == OTP_ADDRESS_22) || ((ADDRESS) == OTP_ADDRESS_23) || ((ADDRESS) == OTP_ADDRESS_24) || ((ADDRESS) == OTP_ADDRESS_25) \
                                        ((ADDRESS) == OTP_ADDRESS_26) || ((ADDRESS) == OTP_ADDRESS_27) || ((ADDRESS) == OTP_ADDRESS_28) || ((ADDRESS) == OTP_ADDRESS_29) \
                                        ((ADDRESS) == OTP_ADDRESS_30) || ((ADDRESS) == OTP_ADDRESS_31))


void OTP_PowerOn(uint32_t Time);
void OTP_PowerOff(void);
void OTP_WriteByte(uint8_t Addr,uint8_t Data);
void OTP_SetTime(uint16_t Time);

#endif
