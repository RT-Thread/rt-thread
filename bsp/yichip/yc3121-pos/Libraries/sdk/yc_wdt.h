/**
  ******************************************************************************
  * @file    yc_wdt.h
  * @author  Yichip
  * @version V1.0
  * @date    7-Dec-2019
  * @brief   watchdog encapsulation.
  *
  ******************************************************************************
  */

#ifndef __YC_WDT_H__
#define __YC_WDT_H__

#include "yc3121.h"

/**
  * @brief  timer number Structure definition
  */
typedef enum
{
    WDT_CPUReset = 0,
    WDT_Interrupt,
} WDT_ModeTypeDef;

#define ISWDTRELOAD(load) (load>0&&load<=0x1f)

/**
 * @brief  Set reload counter
 * @param  Reload: Reload counter equal to 2^reload.
 * @retval none
 */
void WDT_SetReload(uint32_t Reload);

/**
 * @brief Set WDT  mode
 * @param WDT_Mode : Select the following values :
 *        WDT_CPUReset
 *        WDT_Interrupt.
 * @retval none
 * @description If Select WDT_CPUReset Mode,the bit for WDT RESET will be set;if
 *              Select WDT_Interrupt the bit for WDT RESET will
 */
void WDT_ModeConfig(WDT_ModeTypeDef WDT_Mode);

/**
 * @brief  Get interrupt Status
 * @param  none
 * @retval SET:interrupt ocuured.
 */
ITStatus WDT_GetITStatus(void);

/**
 * @brief  Clear interrupt
 * @param  none
 * @retval none
 */
void WDT_ClearITPendingBit(void);

/**
 * @brief  Enable WDT
 * @param  none
 * @retval none
 */
void WDT_Enable(void);

/**
 * @brief  Feed the watchdog function
 * @param  none
 * @retval none
 */
void WDT_ReloadCounter(void);

#endif /*__YC_WDT_H__*/
