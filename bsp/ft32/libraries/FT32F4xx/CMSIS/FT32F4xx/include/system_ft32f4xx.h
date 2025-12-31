/**
  ******************************************************************************
  * @file               system_ft32f4xx.h
  * @author             FMD AE
  * @brief              CMSIS Cortex-M4 Device Peripheral Access Layer System Header File.
  * @details
  * @version            V1.0.0
  * @date               2025-03-04
  *******************************************************************************
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_FT32F4xx_H
#define __SYSTEM_FT32F4xx_H
#include "ft32f4xx.h"
#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT FMD *****END OF FILE****/
