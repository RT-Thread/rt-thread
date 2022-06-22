/**
  ******************************************************************************
  * @file    system_stm32wbxx.h
  * @author  MCD Application Team
  * @brief   CMSIS Cortex Device System Source File for STM32WBxx devices.  
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32wbxx_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_STM32WBXX_H
#define __SYSTEM_STM32WBXX_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdint.h>

/** @addtogroup STM32WBxx_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup STM32WBxx_System_Exported_types
  * @{
  */
  /* The SystemCoreClock variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
  */

extern uint32_t SystemCoreClock;            /*!< System Clock Frequency */

extern const uint32_t AHBPrescTable[16];    /*!< AHB prescalers table values */
extern const uint32_t APBPrescTable[8];     /*!< APB prescalers table values */
extern const uint32_t MSIRangeTable[16];    /*!< MSI ranges table values     */

#if defined(STM32WB55xx) || defined(STM32WB5Mxx) || defined(STM32WB35xx) || defined (STM32WB15xx) || defined (STM32WB10xx)
extern const uint32_t SmpsPrescalerTable[4][6];  /*!< SMPS factor ranges table values     */
#endif
/**
  * @}
  */

/** @addtogroup STM32WBxx_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WBxx_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32WBxx_System_Exported_Functions
  * @{
  */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32WBXX_H */

/**
  * @}
  */
  
/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
