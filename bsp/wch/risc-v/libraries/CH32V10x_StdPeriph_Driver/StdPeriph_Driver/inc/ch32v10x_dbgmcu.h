/********************************** (C) COPYRIGHT  *******************************
 * File Name          : ch32v10x_dbgmcu.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2020/04/30
 * Description        : This file contains all the functions prototypes for the
 *                      DBGMCU firmware library.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#ifndef __CH32V10x_DBGMCU_H
#define __CH32V10x_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ch32v10x.h"

/* CFGR0 Register */
#define DBGMCU_IWDG_STOP             ((uint32_t)0x00000001)
#define DBGMCU_WWDG_STOP             ((uint32_t)0x00000002)
#define DBGMCU_I2C1_SMBUS_TIMEOUT    ((uint32_t)0x00000004)
#define DBGMCU_I2C2_SMBUS_TIMEOUT    ((uint32_t)0x00000008)
#define DBGMCU_TIM1_STOP             ((uint32_t)0x00000010)
#define DBGMCU_TIM2_STOP             ((uint32_t)0x00000020)
#define DBGMCU_TIM3_STOP             ((uint32_t)0x00000040)
#define DBGMCU_TIM4_STOP             ((uint32_t)0x00000080)

/* CFGR1 Register */
#define DBGMCU_SLEEP                 ((uint32_t)0x00000001)
#define DBGMCU_STOP                  ((uint32_t)0x00000002)
#define DBGMCU_STANDBY               ((uint32_t)0x00000004)

void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __CH32V10x_DBGMCU_H */
