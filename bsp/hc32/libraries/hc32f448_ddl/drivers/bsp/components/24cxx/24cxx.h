/**
 *******************************************************************************
 * @file  24cxx.h
 * @brief This file provides firmware functions to 24CXX EEPROM.
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
#ifndef __24CXX_H__
#define __24CXX_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @addtogroup 24CXX
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup 24CXX_Global_Types 24CXX Global Types
 * @{
 */

/**
 * @brief 24CXX low layer structure definition
 */
typedef struct {
    /* Properties */
    uint32_t u32PageSize;
    uint32_t u32Capacity;
    /* Methods */
    void (*Delay)(uint32_t);
    int32_t (*Init)(void);
    void (*DeInit)(void);
    int32_t (*WritePage)(uint16_t u16Addr, const uint8_t *pu8Buf, uint32_t u32Len);
    int32_t (*Read)(uint16_t u16Addr, uint8_t *pu8Buf, uint32_t u32Len);
    int32_t (*GetStatus)(void);
} stc_24cxx_ll_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup 24CXX_Global_Functions 24CXX Global Functions
 * @{
 */
int32_t EE_24CXX_Init(const stc_24cxx_ll_t *pstc24cxxLL);
int32_t EE_24CXX_DeInit(const stc_24cxx_ll_t *pstc24cxxLL);
int32_t EE_24CXX_Read(const stc_24cxx_ll_t *pstc24cxxLL, uint16_t u16Addr, uint8_t *pu8Buf, uint32_t u32Len);
int32_t EE_24CXX_Write(const stc_24cxx_ll_t *pstc24cxxLL, uint16_t u16Addr, const uint8_t *pu8Buf, uint32_t u32Len);
int32_t EE_24CXX_WaitIdle(const stc_24cxx_ll_t *pstc24cxxLL);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __24CXX_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
