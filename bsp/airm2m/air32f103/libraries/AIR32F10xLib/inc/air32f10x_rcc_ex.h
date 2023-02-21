/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __air_RCC_EX_H
#define __air_RCC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air32f10x.h"

typedef enum
{
    FLASH_Div_0 = 0,
    FLASH_Div_2 = 1,
    FLASH_Div_4 = 2,
    FLASH_Div_6 = 3,
    FLASH_Div_8 = 4,
    FLASH_Div_16 = 5,
}FlashClkDiv;

uint32_t AIR_RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul, FlashClkDiv Latency);

#ifdef __cplusplus
}
#endif

#endif

