/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#ifndef __SYSTEM_RK2108_H_
#define __SYSTEM_RK2108_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief Exception / Interrupt Handler Function Prototype
*/
typedef void(*VECTOR_TABLE_Type)(void);

/**
  \brief System Clock Frequency (Core Clock)
*/
extern uint32_t SystemCoreClock;

/**
  \brief Setup the Cache.

   Initialize the Cache in the CPU.
 */
extern void CacheInit(void);

/**
  \brief Setup the system.

   Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit(void);

/**
  \brief  Update SystemCoreClock variable.

   Updates the System Clock Frequency (Core Clock).
 */
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_RK2108_H */
