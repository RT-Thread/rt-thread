/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_bsp.h
 * @brief This file contains all the header file of the EV_HC32F4A0_LQFP176
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

#ifndef __EV_HC32F4A0_LQFP176_BSP__
#define __EV_HC32F4A0_LQFP176_BSP__

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
#if (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX)
#include "ev_hc32f4a0_lqfp176.h"
#endif /* BSP_EV_HC32F4A0_LQFP176 */

/**
 * @brief Include BSP device component's header file
 */
#if (BSP_24CXX_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_24cxx.h"
#endif /* BSP_24CXX_ENABLE */

#if (BSP_GT9XX_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_gt9xx.h"
#endif /* BSP_GT9XX_ENABLE */

#if (BSP_IS42S16400J7TLI_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_is42s16400j7tli.h"
#endif /* BSP_IS42S16400J7TLI_ENABLE */

#if (BSP_IS62WV51216_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_is62wv51216.h"
#endif /* BSP_IS62WV51216_ENABLE */

#if (BSP_MT29F2G08AB_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_mt29f2g08ab.h"
#endif /* BSP_MT29F2G08AB_ENABLE */

#if (BSP_NT35510_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_nt35510.h"
#endif /* BSP_NT35510_ENABLE */

#if (BSP_OV5640_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_ov5640.h"
#endif /* BSP_OV5640_ENABLE */

#if (BSP_TCA9539_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_tca9539.h"
#endif /* BSP_TCA9539_ENABLE */

#if (BSP_W25QXX_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_w25qxx.h"
#endif /* BSP_W25QXX_ENABLE */

#if (BSP_WM8731_ENABLE == DDL_ON)
#include "ev_hc32f4a0_lqfp176_wm8731.h"
#endif /* BSP_WM8731_ENABLE */

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

#endif /* __EV_HC32F4A0_LQFP176_BSP__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
