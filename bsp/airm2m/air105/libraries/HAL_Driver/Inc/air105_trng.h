/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */



#ifndef __AIR105_TRNG_H
#define __AIR105_TRNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"

/** @defgroup RNG_Exported_Types
  * @{
  */
typedef enum{
    TRNG0
} TRNG_ChannelTypeDef;
#define IS_TRNG_CHANNEL(CHANNEL)    (((CHANNEL) == TRNG0))


#define TRNG_IT_RNG0_S128           ((uint32_t)0x00000001)
#define TRNG_IT_RNG0_ATTACK         ((uint32_t)0x00000004)
#define IS_TRNG_GET_IT(IT)          (((IT) == TRNG_IT_RNG0_S128) || \
                                    ((IT) == TRNG_IT_RNG0_ATTACK))

/** @defgroup RNG_Exported_Functions
  * @{
  */
void TRNG_Start(TRNG_ChannelTypeDef TRNGx);
void TRNG_Stop(TRNG_ChannelTypeDef TRNGx);
uint32_t TRNG_Get(uint32_t rand[4], TRNG_ChannelTypeDef TRNGx);
void TRNG_SetPseudoRandom(uint32_t PseudoRandom);
void TRNG_DirectOutANA(TRNG_ChannelTypeDef TRNGx, FunctionalState NewState);

void TRNG_ITConfig(FunctionalState NewState);
ITStatus TRNG_GetITStatus(uint32_t TRNG_IT);
void TRNG_ClearITPendingBit(uint32_t TRNG_IT);


#ifdef __cplusplus
}
#endif

#endif

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
