/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup HAL_BASE
 *  @{
 */

#ifndef _HAL_BASE_H_
#define _HAL_BASE_H_

#include "hal_conf.h"
#include "hal_driver.h"
#include "hal_debug.h"

/***************************** MACRO Definition ******************************/

/** @defgroup HAL_BASE_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/** enter markrom usb upgrade */
#define SYS_UPGRADE_FLAG (0xEF08A53C)

#define IS_TICKFREQ(f) (((f) == HAL_TICK_FREQ_1KHZ)  || ((f) == HAL_TICK_FREQ_100HZ) || ((f) == HAL_TICK_FREQ_10HZ))

/***************************** Structure Definition **************************/
typedef enum {
    HAL_TICK_FREQ_10HZ    = 100U,    /**< 10 ticks per second, so it's 100ms/tick */
    HAL_TICK_FREQ_100HZ   = 10U,     /**< 100 ticks per second, so it's 10ms/tick */
    HAL_TICK_FREQ_1KHZ    = 1U,      /**< 1000 ticks per second, so it's 1ms/tick */
    HAL_TICK_FREQ_DEFAULT = HAL_TICK_FREQ_1KHZ
} eHAL_tickFreq;

/** @} */

/***************************** Function Declare ******************************/
/** @defgroup HAL_BASE_Public_Function_Declare Public Function Declare
 *  @{
 */

HAL_Status HAL_Init(void);
HAL_Status HAL_DeInit(void);
HAL_Status HAL_InitTick(uint32_t tickPriority);
HAL_Status HAL_IncTick(void);
uint32_t HAL_GetTick(void);
HAL_Status HAL_SetTickFreq(eHAL_tickFreq freq);
eHAL_tickFreq HAL_GetTickFreq(void);

HAL_Status HAL_DelayUs(uint32_t us);
HAL_Status HAL_DelayMs(uint32_t ms);
HAL_Status HAL_CPUDelayUs(uint32_t us);
HAL_Status HAL_SystemCoreClockUpdate(uint32_t hz, eHAL_systickClkSource clkSource);

uint64_t HAL_DivU64Rem(uint64_t numerator, uint32_t denominator, uint32_t *pRemainder);
uint64_t HAL_GetSysTimerCount(void);

/** @} */

/********************* Public Function Definition ***************************/
/** @defgroup HAL_BASE_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  uint64_t numerator / uint32_t denominator
 * @param  numerator
 * @param  denominator
 * @return uint64_t result
 */
__STATIC_INLINE uint64_t HAL_DivU64(uint64_t numerator, uint32_t denominator)
{
    return HAL_DivU64Rem(numerator, denominator, NULL);
}

/**
 * @brief  uint32_t numerator / uint32_t denominator rounded to nearest integer
 * @param  numerator
 * @param  denominator
 * @return uint32_t result rounded to nearest integer
 */
__STATIC_INLINE uint32_t HAL_DivRoundClosest(uint32_t numerator, uint32_t denominator)
{
    return (numerator + (denominator / 2)) / denominator;
}

/** @} */

#endif

/** @} */

/** @} */
