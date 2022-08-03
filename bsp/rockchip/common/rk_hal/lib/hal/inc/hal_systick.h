/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

#ifdef HAL_SYSTICK_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup SYSTICK
 *  @{
 */

#ifndef _HAL_SYSTICK_H_
#define _HAL_SYSTICK_H_

#include "hal_def.h"

/***************************** MACRO Definition ******************************/
/** @defgroup SYSTICK_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/***************************** Structure Definition **************************/

/** @} */
/***************************** Function Declare ******************************/
/** @defgroup SYSTICK_Public_Function_Declare Public Function Declare
 *  @{
 */

HAL_Status HAL_SYSTICK_Init(void);
HAL_Status HAL_SYSTICK_Config(uint32_t ticksNumb);
HAL_Status HAL_SYSTICK_CLKSourceConfig(eHAL_systickClkSource clkSource);
HAL_Check HAL_SYSTICK_IsExtRefClockEnabled(void);
void HAL_SYSTICK_IRQHandler(void);
HAL_Status HAL_SYSTICK_Enable(void);

/** @} */

#endif

/** @} */

/** @} */

#endif /* HAL_SYSTICK_MODULE_ENABLED */
