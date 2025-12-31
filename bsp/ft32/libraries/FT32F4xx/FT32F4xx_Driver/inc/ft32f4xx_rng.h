/**
  ******************************************************************************
  * @file               ft32f4xx_rng.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the rng
  *                     firmware library.
  * @version            V1.0.0
  * @data                   2025-03-06
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_RNG_H
#define __FT32F4XX_RNG_H

#ifdef __cplusplus
extern "C" {
#endif


#include "ft32f4xx.h"

void RNG_Init();
void RNG_DeInit(FunctionalState NewState);

uint32_t RNG_GenerateRandomNumber();
void RNG_IT(FunctionalState NewState);
uint8_t RNG_get_error_status();

#ifdef __cplusplus
}
#endif

#endif /* __FT32F0XX_RNG_H */

/**
  * @}
  */
/************************ (C) COPYRIGHT FMD *****END OF FILE****/









