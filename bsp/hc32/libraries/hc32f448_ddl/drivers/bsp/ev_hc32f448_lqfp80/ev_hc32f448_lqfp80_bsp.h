/**
 *******************************************************************************
 * @file  ev_hc32f448_lqfp80_bsp.h
 * @brief This file contains all the header file of the EV_HC32F448_LQFP80
 *        BSP driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
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
#ifndef __EV_HC32F448_LQFP80_BSP__
#define __EV_HC32F448_LQFP80_BSP__

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
#if (BSP_EV_HC32F448_LQFP80 == BSP_EV_HC32F4XX)
#include "ev_hc32f448_lqfp80.h"
#endif /* BSP_EV_HC32F448_LQFP80 */

/**
 * @brief Include BSP device component's header file
 */
#if (BSP_24CXX_ENABLE == DDL_ON)
#include "ev_hc32f448_lqfp80_24cxx.h"
#endif /* BSP_24CXX_ENABLE */

#if (BSP_GT9XX_ENABLE == DDL_ON)
#include "ev_hc32f448_lqfp80_gt9xx.h"
#endif /* BSP_GT9XX_ENABLE */

#if (BSP_IS61LV6416_ENABLE == DDL_ON)
#include "ev_hc32f448_lqfp80_is61lv6416.h"
#endif /* BSP_IS61LV6416_ENABLE */

#if (BSP_NT35510_ENABLE == DDL_ON)
#include "ev_hc32f448_lqfp80_nt35510.h"
#endif /* BSP_NT35510_ENABLE */

#if (BSP_TCA9539_ENABLE == DDL_ON)
#include "ev_hc32f448_lqfp80_tca9539.h"
#endif /* BSP_TCA9539_ENABLE */

#if (BSP_W25QXX_ENABLE == DDL_ON)
#include "ev_hc32f448_lqfp80_w25qxx.h"
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

#endif /* __EV_HC32F448_LQFP80_BSP__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
