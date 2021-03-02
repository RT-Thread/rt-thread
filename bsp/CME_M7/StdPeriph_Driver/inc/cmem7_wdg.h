/**
    *****************************************************************************
    * @file     cmem7_wdg.h
    *
    * @brief    CMEM7 watchdog header file
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

#ifndef __CMEM7_WDG_H
#define __CMEM7_WDG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

/** @defgroup WDG_INT
  * @{
  */
#define WDG_INT_QUARTER                 0
#define WDG_INT_HALF                    1
#define IS_WDG_INT(INT)                 (((INT) == WDG_INT_QUARTER) || \
                                         ((INT) == WDG_INT_HALF))
/**
  * @}
  */

/** @defgroup WDG_TRIGGER_MODE
  * @{
  */
#define WDG_TRIGGER_MODE_EDGE           0
#define WDG_TRIGGER_MODE_LEVEL          1
#define IS_WDG_TRIGGER_MODE(TRI)        (((TRI) == WDG_TRIGGER_MODE_EDGE) || \
                                         ((TRI) == WDG_TRIGGER_MODE_LEVEL))
/**
  * @}
  */

/**
  * @brief  Deinitializes the Watchdog peripheral registers to their default reset values.
    * @param[in] None
  * @retval None
    */
void WDG_DeInit(void);

/**
  * @brief  Watchdog initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] trigger Watchdog interrupt trigger mode, which is a value of @ref WDG_TRIGGER_MODE
    * @param[in] ResetMillSecond MillSeconds lasts before global reset
  * @retval None
    */
void WDG_Init(uint8_t trigger, uint16_t ResetMillSecond);

/**
  * @brief  Enable or disable watchdog interrupt.
    * @param[in] Int interrupt mask bits, which is a value of @ref WDG_INT
    * @param[in] Enable The bit indicates if the specific interrupt are enable or not
  * @retval None
    */
void WDG_ITConfig(uint8_t Int, BOOL Enable);

/**
  * @brief  Check the specific interrupt are set or not
    * @param    None
  * @retval BOOL The bit indicates if the specific interrupt are set or not
    */
BOOL WDG_GetITStatus(void);

/**
  * @brief  Clear the specific interrupt
    * @param    None
  * @retval None
    */
void WDG_ClearITPendingBit(void);

/**
  * @brief  Enable or disable watchdog.
    * @param[in] Enable The bit indicates if watchdog is enable or not
  * @retval None
    */
void WDG_Cmd(BOOL Enable);


#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_WDG_H */

