/**
    *****************************************************************************
    * @file     cmem7_rtc.h
    *
    * @brief    CMEM7 RTC header file
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

#ifndef __CMEM7_RTC_H
#define __CMEM7_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/** @defgroup RTC_Int
  * @{
  */
#define RTC_Int_Second                     ((uint32_t)0x00000001)
#define RTC_Int_Millsecond                 ((uint32_t)0x00000002)
#define RTC_Int_All                        ((uint32_t)0x00000003)
#define IS_RTC_INT(INT)                    (((INT) != 0) && (((INT) & ~RTC_Int_All) == 0))
/**
  * @}
  */

/**
  * @brief  Enable or disable RTC interrupt.
    * @param[in] Int interrupt mask bits, which can be the combination of @ref RTC_Int
    * @param[in] Enable The bit indicates if specific interrupts are enable or not
  * @retval None
    */
void RTC_ITConfig(uint32_t Int, BOOL Enable);

/**
  * @brief  Check specific interrupts are set or not
    * @param[in] Int interrupt mask bits, which can be the combination of @ref RTC_Int
  * @retval BOOL The bit indicates if specific interrupts are set or not
    */
BOOL RTC_GetITStatus(uint32_t Int);

/**
  * @brief  Clear specific interrupts
    * @param[in] Int interrupt mask bits, which can be the combination of @ref RTC_Int
  * @retval None
    */
void RTC_ClearITPendingBit(uint32_t Int);

/**
  * @brief  Get seconds since power up
    * @param    None
  * @retval uint32_t Seconds since power up
    */
uint32_t RTC_GetSecond(void);

/**
  * @brief  Get current millseconds
    * @param    None
  * @retval uint32_t Current millseconds
    */
uint16_t RTC_GetMillSecond(void);

#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_RTC_H */

