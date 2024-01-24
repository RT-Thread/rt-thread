/**
 *******************************************************************************
 * @file  ev_hc32f460_lqfp100_v2_bsp.h
 * @brief This file contains all the header file of the EV_HC32F460_LQFP100_V2
 *        BSP driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef __EV_HC32F460_LQFP100_V2_BSP__
#define __EV_HC32F460_LQFP100_V2_BSP__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
/**
 * @brief Include BSP board's header file
 */
#if (BSP_EV_HC32F460_LQFP100_V2 == BSP_EV_HC32F4XX)
#include "ev_hc32f460_lqfp100_v2.h"
#endif /* BSP_EV_HC32F460_LQFP100_V2 */

/**
 * @brief Include BSP device component's header file
 */
#if (BSP_24CXX_ENABLE == DDL_ON)
#include "ev_hc32f460_lqfp100_v2_24cxx.h"
#endif /* BSP_24CXX_ENABLE */

#if (BSP_WM8731_ENABLE == DDL_ON)
#include "ev_hc32f460_lqfp100_v2_wm8731.h"
#endif /* BSP_WM8731_ENABLE */

#if (BSP_W25QXX_ENABLE == DDL_ON)
#include "ev_hc32f460_lqfp100_v2_w25qxx.h"
#endif /* BSP_W25QXX_ENABLE */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __EV_HC32F460_LQFP100_V2_BSP__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
