
/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

#ifdef HAL_PMU_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PD
 *  @{
 */

#ifndef _HAL_PD_H_
#define _HAL_PD_H_

#include "hal_def.h"

/***************************** MACRO Definition ******************************/

/***************************** Structure Definition **************************/

/***************************** Function Declare ******************************/
/** @defgroup PD_Public_Function_Declare Public Function Declare
 *  @{
 */

HAL_Status HAL_PD_On(ePD_Id pd);
HAL_Status HAL_PD_Off(ePD_Id pd);

/** @} */

#endif

/** @} */

/** @} */

#endif /* HAL_PMU_MODULE_ENABLED */
