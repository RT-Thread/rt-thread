/**
  ******************************************************************************
  * @file               ft32f0xx_it.h
  * @author             FMD AE
  * @brief              CMSIS Cortex-M0 Device Peripheral Access Layer System Header File.
  * @details
  * @version            V1.0.0
  * @date               2021-07-01
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F030X8_it_H
#define __FT32F030X8_it_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void PPP_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __FT32F030X8_it_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
