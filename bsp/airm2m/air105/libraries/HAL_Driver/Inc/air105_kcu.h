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


#ifndef __AIR105_KCU_H
#define __AIR105_KCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"

/**
  * @brief  KCU Init structure definition
  */
typedef struct
{
    uint32_t KCU_DebounceTimeLevel;
    uint32_t KCU_PortInput;
    uint32_t KCU_PortOutput;
    uint32_t KCU_Rand;
}KCU_InitTypeDef;


#define KCU_IT_PUSH                         (KCU_CTRL1_PUSH_IT)
#define KCU_IT_RELEASE                      (KCU_CTRL1_RELEASE_IT)
#define KCU_IT_OVERRUN                      (KCU_CTRL1_OVERRUN_IT)

void KCU_DeInit(void);

void KCU_Init(KCU_InitTypeDef *KCU_InitStruct);
void KCU_StructInit(KCU_InitTypeDef *KCU_InitStruct);

void KCU_Cmd(FunctionalState NewState);

uint32_t KCU_SetRand(uint32_t rand);

void KCU_ITConfig(uint32_t KCU_IT, FunctionalState NewState);
FlagStatus KCU_GetITStatus(uint32_t KCU_IT);
void KCU_ClearITPending(void);

uint32_t KCU_GetEvenReg(void);


#ifdef __cplusplus
}
#endif

#endif


/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
