/*!
    \file  system_gd32h7xx.h
    \brief CMSIS Cortex-M7 Device Peripheral Access Layer Header File for
           gd32h7xx Device Series
*/

/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 * Copyright (c) 2024, GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

#ifndef SYSTEM_GD32H7XX_H
#define SYSTEM_GD32H7XX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* system clock frequency (core clock) */
extern uint32_t SystemCoreClock;

/* function declarations */
/* initialize the system and update the SystemCoreClock variable */
extern void SystemInit (void);
/* update the SystemCoreClock with current core clock retrieved from cpu registers */
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_GD32H7XX_H */
