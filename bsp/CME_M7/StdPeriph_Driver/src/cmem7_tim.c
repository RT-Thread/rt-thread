/**
    *****************************************************************************
    * @file     cmem7_tim.c
    *
    * @brief    CMEM7 timer source file
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

#include "cmem7_tim.h"

static uint32_t tim_GetClock() {
    return SYSTEM_CLOCK_FREQ / (1 << (GLOBAL_CTRL->CLK_SEL_0_b.TIMER_CLK + 1));
}

void TIM_Init(TIMER0_Type* Timx, uint16_t Ms) {
    assert_param(IS_TIM_ALL_PERIPH(Timx));

    Timx->CTRL_b.EN = FALSE;
    Timx->LEN = tim_GetClock() / 1000 * Ms;
    Timx->TYPE_b.SIGNLE_SHOT = TRUE;
}

void TIM_EnableInt(TIMER0_Type* Timx, BOOL Enable) {
    assert_param(IS_TIM_ALL_PERIPH(Timx));

    if (Enable == TRUE) {
      Timx->INT_EN_b.EN_REVERSE = FALSE;
    } else {
        Timx->INT_EN_b.EN_REVERSE = TRUE;
    }
}

BOOL TIM_GetIntStatus(TIMER0_Type* Timx) {
    assert_param(IS_TIM_ALL_PERIPH(Timx));

    return (Timx->INT_STA_b.STA ? TRUE : FALSE);
}

void TIM_ClearInt(TIMER0_Type* Timx) {
    assert_param(IS_TIM_ALL_PERIPH(Timx));

    Timx->INT_STA_b.STA = 1;
}

void TIM_Enable(TIMER0_Type* Timx, BOOL Enable) {
    assert_param(IS_TIM_ALL_PERIPH(Timx));

    Timx->CTRL_b.EN = Enable;
}

BOOL TIM_IsOverflow(TIMER0_Type* Timx) {
    assert_param(IS_TIM_ALL_PERIPH(Timx));

    return (Timx->CNT == 0) ? TRUE : FALSE;
}

uint32_t TIM_GetCounter(TIMER0_Type* Timx) {
    assert_param(IS_TIM_ALL_PERIPH(Timx));

    return Timx->CNT;
}

