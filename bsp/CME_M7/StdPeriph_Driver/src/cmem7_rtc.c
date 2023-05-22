/**
    *****************************************************************************
    * @file     cmem7_rtc.c
    *
    * @brief    CMEM7 RTC source file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#include "cmem7_rtc.h"

#define SECONDS_IN_A_DAY                (86400)

void RTC_ITConfig(uint32_t Int, BOOL Enable) {
    assert_param(IS_RTC_INT(Int));

    if (Enable) {
      GLOBAL_CTRL->RTC_INT_EN |= Int;
    } else {
        GLOBAL_CTRL->RTC_INT_EN &= ~Int;
    }
}

BOOL RTC_GetITStatus(uint32_t Int) {
    assert_param(IS_RTC_INT(Int));

    if (0 != (RTC->INT_STATUS & Int)) {
        return TRUE;
    }

    return FALSE;
}

void RTC_ClearITPendingBit(uint32_t Int) {
  assert_param(IS_RTC_INT(Int));

    RTC->INT_STATUS = Int;
}

uint32_t RTC_GetSecond() {
    return RTC->SECOND;
}

uint16_t RTC_GetMillSecond() {
    return RTC->MILLSECOND_b.MS;
}
