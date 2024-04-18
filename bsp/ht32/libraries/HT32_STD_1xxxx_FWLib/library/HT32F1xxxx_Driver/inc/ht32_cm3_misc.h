/*********************************************************************************************************//**
 * @file    ht32_cm3_misc.h
 * @version $Rev:: 5            $
 * @date    $Date:: 2017-05-11 #$
 * @brief   All the function prototypes for the miscellaneous firmware library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_CM3_MISC_H
#define __HT32_CM3_MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32_Peripheral_Driver
  * @{
  */

/** @addtogroup MISC
  * @{
  */


/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup MISC_Exported_Constants MISC exported constants
  * @{
  */

/* Vector Table Base                                                                                        */
#define NVIC_VECTTABLE_RAM                          ((u32)0x20000000)
#define NVIC_VECTTABLE_FLASH                        ((u32)0x00000000)

#define IS_NVIC_VECTTABLE(VECTTABLE)                ((VECTTABLE == NVIC_VECTTABLE_RAM) || \
                                                     (VECTTABLE == NVIC_VECTTABLE_FLASH))

#define IS_NVIC_OFFSET(OFFSET)                      (OFFSET < 0x0001FFFF)

/* System Low Power                                                                                         */
#define NVIC_LOWPOWER_SEVONPEND                     ((u8)0x10)
#define NVIC_LOWPOWER_SLEEPDEEP                     ((u8)0x04)
#define NVIC_LOWPOWER_SLEEPONEXIT                   ((u8)0x02)

#define IS_NVIC_LOWPOWER(LOWPOWER)                  ((LOWPOWER == NVIC_LOWPOWER_SEVONPEND) || \
                                                     (LOWPOWER == NVIC_LOWPOWER_SLEEPDEEP) || \
                                                     (LOWPOWER == NVIC_LOWPOWER_SLEEPONEXIT))

/* System Handler                                                                                           */
#define SYSTEMHANDLER_NMI                           ((u32)0x80000000)
#define SYSTEMHANDLER_PSV                           ((u32)0x10000000)
#define SYSTEMHANDLER_SYSTICK                       ((u32)0x04000000)
#define SYSTEMHANDLER_ALL                           ((u32)0x94000000)

#define IS_NVIC_SYSTEMHANDLER(HANDLER)              ((HANDLER == SYSTEMHANDLER_NMI)     || \
                                                     (HANDLER == SYSTEMHANDLER_PSV)     || \
                                                     (HANDLER == SYSTEMHANDLER_SYSTICK) ||\
                                                     (HANDLER == SYSTEMHANDLER_ALL))

/* SysTick clock source                                                                                     */
#define SYSTICK_SRC_STCLK                           ((u32)0xFFFFFFFB)
#define SYSTICK_SRC_FCLK                            ((u32)0x00000004)

#define IS_SYSTICK_CLOCK_SOURCE(SOURCE)             ((SOURCE == SYSTICK_SRC_STCLK) || \
                                                     (SOURCE == SYSTICK_SRC_FCLK) )

/* SysTick counter state                                                                                    */
#define SYSTICK_COUNTER_DISABLE                     ((u32)0xFFFFFFFE)
#define SYSTICK_COUNTER_ENABLE                      ((u32)0x00000001)
#define SYSTICK_COUNTER_CLEAR                       ((u32)0x00000000)

#define IS_SYSTICK_COUNTER(COUNTER)                 ((COUNTER == SYSTICK_COUNTER_DISABLE) || \
                                                     (COUNTER == SYSTICK_COUNTER_ENABLE)  || \
                                                     (COUNTER == SYSTICK_COUNTER_CLEAR))

#define IS_SYSTICK_RELOAD(RELOAD)                   ((RELOAD  > 0) && (RELOAD <= 0xFFFFFF))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup MISC_Exported_Functions MISC exported functions
  * @{
  */
void NVIC_SetVectorTable(u32 NVIC_VectTable, u32 NVIC_Offset);
void NVIC_LowPowerConfig(u8 NVIC_LowPowerMode, ControlStatus NewState);
void NVIC_CoreReset(void);
void NVIC_SetPendingSystemHandler(u32 SystemHandler);
void SYSTICK_ClockSourceConfig(u32 SysTick_ClockSource);
void SYSTICK_CounterCmd(u32 SysTick_Counter);
void SYSTICK_IntConfig(ControlStatus NewState);
void SYSTICK_SetReloadValue(u32 SysTick_Reload);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
