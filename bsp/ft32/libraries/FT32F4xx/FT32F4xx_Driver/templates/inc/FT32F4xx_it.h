/**
  ******************************************************************************
  * @file     ../
  * @author      FMD AE
  * @brief       Main program body
  * @version     V1.0.0
  * @date        3-July-2025
  ******************************************************************************
  * @attention
  * COPYRIGHT (C) 2025 Fremont Micro Devices (SZ) Corporation All rights reserved.
  * This software is provided by the copyright holders and contributors,and the
  * software is believed to be accurate and reliable. However, Fremont Micro
  * Devices (SZ) Corporation assumes no responsibility for the consequences of
  * use of such software or for any infringement of patents of other rights
  * of third parties, which may result from its use. No license is granted by
  * implication or otherwise under any patent rights of Fremont Micro Devices (SZ)
  * Corporation.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4xx_IT_H
#define __FT32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __FT32F4xx_IT_H */


/************************ (C) COPYRIGHT Fremont Micro Devices *****END OF FILE****/
