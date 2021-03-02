/**
    *****************************************************************************
    * @file     cmem7_wdg.c
    *
    * @brief    CMEM7 watchdog source file
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

#include "cmem7_wdg.h"

static uint32_t wdg_GetClock() {
    return SYSTEM_CLOCK_FREQ / (1 << (GLOBAL_CTRL->CLK_SEL_0_b.WDG_CLK + 1));
}

void WDG_DeInit(void){
  SOFT_RESET->SOFTRST_b.WDT_n = 0;
    SOFT_RESET->SOFTRST_b.WDT_n = 1;
}

void WDG_Init(uint8_t trigger, uint16_t ResetMillSecond) {
    assert_param(IS_WDG_TRIGGER_MODE(trigger));

    WDG->INT_CTRL_b.TRIGGER_MODE = trigger;
    WDG->LEN = ((uint64_t)wdg_GetClock()) * ResetMillSecond / 1000;
}

void WDG_ITConfig(uint8_t Int, BOOL Enable) {
    assert_param(IS_WDG_INT(Int));

    WDG->CTRL_b.INT_LEN = Int;
    WDG->INT_CTRL_b.MASK = !Enable;
}

BOOL WDG_GetITStatus() {
    return (WDG->INT_STA_b.STA == 1) ? TRUE : FALSE;
}

void WDG_ClearITPendingBit() {
    WDG->INT_STA_b.STA = 1;
}

void WDG_Cmd(BOOL Enable) {
    WDG->CTRL_b.EN = Enable;
}

