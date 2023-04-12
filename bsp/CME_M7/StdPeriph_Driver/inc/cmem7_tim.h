/**
    *****************************************************************************
    * @file     cmem7_tim.h
    *
    * @brief    CMEM7 timer header file
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

#ifndef __CMEM7_TIM_H
#define __CMEM7_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"


#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIMER0) || \
                                   ((PERIPH) == TIMER1) || \
                                   ((PERIPH) == TIMER2) || \
                                   ((PERIPH) == TIMER3))

/**
  * @brief  Timer initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] Timx Timer peripheral, which is timer0, timer1, timer2 or timer3
    * @param[in] Ms overflow micro-seconds of the specific timer
  * @retval None
    */
void TIM_Init(TIMER0_Type* Timx, uint16_t Ms);

/**
  * @brief  Enable or disable timer interrupt.
    * @param[in] Timx Timer peripheral, which is timer0, timer1, timer2 or timer3
    * @param[in] Enable The bit indicates if the specific interrupt is enable or not
  * @retval None
    */
void TIM_EnableInt(TIMER0_Type* Timx, BOOL Enable);

/**
  * @brief  Check the specific interrupt is set or not
    * @param[in] Timx Timer peripheral, which is timer0, timer1, timer2 or timer3
    * @retval BOOL The bit indicates if the specific interrupt is set or not
    */
BOOL TIM_GetIntStatus(TIMER0_Type* Timx);

/**
  * @brief  Clear specific interrupts
    * @param[in] Timx Timer peripheral, which is timer0, timer1, timer2 or timer3
    * @retval None
    */
void TIM_ClearInt(TIMER0_Type* Timx);

/**
  * @brief  Enable or disable timer.
    * @param[in] Timx Timer peripheral, which is timer0, timer1, timer2 or timer3
    * @param[in] Enable The bit indicates if the specific timer is enable or not
  * @retval None
    */
void TIM_Enable(TIMER0_Type* Timx, BOOL Enable);

/**
  * @brief  Check the specific timer is overflow or not
    * @param[in] Timx Timer peripheral, which is timer0, timer1, timer2 or timer3
    * @retval BOOL The bit indicates if the specific timer is overflow or not
    */
BOOL TIM_IsOverflow(TIMER0_Type* Timx);

/**
  * @brief  Get current counter of timer
    * @param[in] Timx Timer peripheral, which is timer0, timer1, timer2 or timer3
    * @retval uint32_t current counter
    */
uint32_t TIM_GetCounter(TIMER0_Type* Timx);

#ifdef __cplusplus
}
#endif

#endif /*__CMEM7_TIM_H */

