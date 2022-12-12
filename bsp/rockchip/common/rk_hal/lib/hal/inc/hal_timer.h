/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

#ifdef HAL_TIMER_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup TIMER
 *  @{
 */

#ifndef _HAL_TIMER_H_
#define _HAL_TIMER_H_

#include "hal_def.h"

/***************************** MACRO Definition ******************************/

/** @defgroup TIMER_Exported_Definition_Group1 Basic Definition
 *  @{
 */

typedef enum {
    TIMER_FREE_RUNNING = 0,
    TIMER_USER_DEFINED,
    TIMER_MODE_MAX
} eTIMER_MODE;

/***************************** Structure Definition **************************/

/** @} */
/***************************** Function Declare ******************************/
/** @defgroup TIMER_Public_Function_Declare Public Function Declare
 *  @{
 */

HAL_Status HAL_TIMER_Stop(struct TIMER_REG *pReg);
HAL_Status HAL_TIMER_Start(struct TIMER_REG *pReg);
HAL_Status HAL_TIMER_Stop_IT(struct TIMER_REG *pReg);
HAL_Status HAL_TIMER_Start_IT(struct TIMER_REG *pReg);
HAL_Status HAL_TIMER_SetCount(struct TIMER_REG *pReg, uint64_t usTick);
uint64_t HAL_TIMER_GetCount(struct TIMER_REG *pReg);
HAL_Status HAL_TIMER0_Handler(void);
HAL_Status HAL_TIMER1_Handler(void);
HAL_Status HAL_TIMER_Init(struct TIMER_REG *pReg, eTIMER_MODE mode);
HAL_Status HAL_TIMER_SysTimerInit(struct TIMER_REG *pReg);
HAL_Status HAL_TIMER_DeInit(struct TIMER_REG *pReg);
HAL_Status HAL_TIMER_ClrInt(struct TIMER_REG *pReg);

/** @} */

#endif

/** @} */

/** @} */

#endif /* HAL_TIMER_MODULE_ENABLED */
