/**
  ******************************************************************************
  * @file               system_ft32f0xx.h
  * @author             FMD AE
  * @brief              CMSIS Cortex-M0 Device Peripheral Access Layer System Header File.
  * @details
  * @version            V1.0.0
  * @date               2021-07-01
  *******************************************************************************
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_FT32F0xx_H
#define __SYSTEM_FT32F0xx_H

#ifdef __cplusplus
 extern "C" {
#endif

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
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
