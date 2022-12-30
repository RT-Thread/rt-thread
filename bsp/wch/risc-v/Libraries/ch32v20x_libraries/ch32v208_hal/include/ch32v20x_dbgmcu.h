/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32v20x_dbgmcu.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : This file contains all the functions prototypes for the
 *                      DBGMCU firmware library.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#ifndef __CH32V20x_DBGMCU_H
#define __CH32V20x_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ch32v20x.h"

#define DBGMCU_SLEEP                 ((uint32_t)0x00000001)
#define DBGMCU_STOP                  ((uint32_t)0x00000002)
#define DBGMCU_STANDBY               ((uint32_t)0x00000004)
#define DBGMCU_IWDG_STOP             ((uint32_t)0x00000100)
#define DBGMCU_WWDG_STOP             ((uint32_t)0x00000200)
#define DBGMCU_I2C1_SMBUS_TIMEOUT    ((uint32_t)0x00000400)
#define DBGMCU_I2C2_SMBUS_TIMEOUT    ((uint32_t)0x00000800)
#define DBGMCU_TIM1_STOP             ((uint32_t)0x00001000)
#define DBGMCU_TIM2_STOP             ((uint32_t)0x00002000)
#define DBGMCU_TIM3_STOP             ((uint32_t)0x00004000)
#define DBGMCU_TIM4_STOP             ((uint32_t)0x00008000)
#define DBGMCU_TIM5_STOP             ((uint32_t)0x00010000)
#define DBGMCU_TIM6_STOP             ((uint32_t)0x00020000)
#define DBGMCU_TIM7_STOP             ((uint32_t)0x00040000)
#define DBGMCU_TIM8_STOP             ((uint32_t)0x00080000)
#define DBGMCU_CAN1_STOP             ((uint32_t)0x00100000)
#define DBGMCU_CAN2_STOP             ((uint32_t)0x00200000)
#define DBGMCU_TIM9_STOP             ((uint32_t)0x00400000)
#define DBGMCU_TIM10_STOP            ((uint32_t)0x00800000)

uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
uint32_t __get_DEBUG_CR(void);
void __set_DEBUG_CR(uint32_t value);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif
