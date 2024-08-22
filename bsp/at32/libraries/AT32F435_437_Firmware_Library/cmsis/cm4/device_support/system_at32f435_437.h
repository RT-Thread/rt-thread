/**
  **************************************************************************
  * @file     system_at32f435_437.h
  * @brief    cmsis cortex-m4 system header file.
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#ifndef __SYSTEM_AT32F435_437_H
#define __SYSTEM_AT32F435_437_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup AT32F435_437_system
  * @{
  */

#define SystemCoreClock                  system_core_clock
#define DUMMY_NOP()                      {__NOP();__NOP();__NOP();__NOP();__NOP(); \
                                          __NOP();__NOP();__NOP();__NOP();__NOP(); \
                                          __NOP();__NOP();__NOP();__NOP();__NOP(); \
                                          __NOP();__NOP();__NOP();__NOP();__NOP();}

/** @defgroup AT32F435_437_system_exported_variables
  * @{
  */
extern unsigned int system_core_clock; /*!< system clock frequency (core clock) */

/**
  * @}
  */

/** @defgroup AT32F435_437_system_exported_functions
  * @{
  */

extern void SystemInit(void);
extern void system_core_clock_update(void);

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

