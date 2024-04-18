/**************************************************************************//**
 * @file    system_ht32f5xxxx_08.h
 * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer System Header File
 *          for the Holtek HT32F5xxxx Device Series
 * @version $Rev:: 1725         $
 * @date    $Date:: 2017-08-24 #$
 *
 * @note
 * Copyright (C) Holtek Semiconductor Inc. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) supplies this software for use with Cortex-M processor-based
 * microcontrollers.  This file can be freely distributed within development
 * tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup HT32F5xxxx_system
  * @{
  */


#ifndef __SYSTEM_HT32F5XXXX_08_H
#define __SYSTEM_HT32F5XXXX_08_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup HT32F5xxxx_System_Exported_types
  * @{
  */
extern __IO uint32_t SystemCoreClock;  /*!< System Clock Frequency (Core Clock)                             */
/**
  * @}
  */


/** @addtogroup HT32F5xxxx_System_Exported_Functions
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

#endif


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT Holtek Semiconductor Inc. *****END OF FILE***                            */
