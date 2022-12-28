/* Includes ------------------------------------------------------------------*/
#include "air32f10x_otp.h"

/** @defgroup OTP
  * @brief OTP driver modules
  * @{
  */

void OTP_PowerOn(uint32_t Time)
{
    RCC->RCC_SYSCFG_CONFIG = 0x01;
    SYSCFG->SYSCFG_LOCK = 0xAB12DFCD;
    if(Time > OTP_POWERON_TIME)
    {
        OTP->OTP_LDO =Time;
    }
    else
    {
        OTP->OTP_LDO = OTP_POWERON_TIME;
    }
}

void OTP_PowerOff(void)
{
    SYSCFG->SYSCFG_LOCK = 0xAB12DFCD;
    RCC->RCC_SYSCFG_CONFIG = 0x00;
}

void OTP_SetTime(uint16_t Time)
{
    OTP->OTP_10ns |= Time;
}

void OTP_WriteByte(uint8_t Addr,uint8_t Data)
{
    assert_param(IS_OTP_ADDRESS(Addr));

    OTP->OTP_WR = (Addr << 8) | Data;
    OTP->OTP_CTRL = BIT(0);
    while(OTP->OTP_CTRL & BIT(2));
}

