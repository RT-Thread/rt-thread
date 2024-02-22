/**
 *******************************************************************************
 * @file  24cxx.c
 * @brief This midware file provides firmware functions to 24cxx EEPROM.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-12-15       CDT             Add null pointer check
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "24cxx.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @defgroup 24CXX EEPROM Driver for 24CXX
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup 24CXX_Local_Macros 24CXX Local Macros
 * @{
 */
#define EE_24CXX_WAIT_TIMEOUT           (0x20000UL)
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup 24CXX_Local_Types 24CXX Local Types
 * @{
 */
static uint32_t u32PageSize;
static uint32_t u32Capacity;
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup 24CXX_Global_Functions 24CXX Global Functions
 * @{
 */

/**
 * @brief  Initializes I2C for 24CXX.
 * @param  [in] pstc24cxxLL         Pointer to a @ref stc_24cxx_ll_t structure.
 * @retval int32_t:
 *         - LL_OK:                 Success
 *         - LL_ERR_INVD_PARAM:     Invalid parameter
 */
int32_t EE_24CXX_Init(const stc_24cxx_ll_t *pstc24cxxLL)
{
    int32_t i32Ret;
    if ((pstc24cxxLL == NULL) || (pstc24cxxLL->u32PageSize == 0U) || (pstc24cxxLL->u32Capacity == 0U) ||
        (pstc24cxxLL->Init == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        u32PageSize = pstc24cxxLL->u32PageSize;
        u32Capacity = pstc24cxxLL->u32Capacity;
        i32Ret = pstc24cxxLL->Init();
    }
    return i32Ret;
}

/**
 * @brief  De-Initializes I2C for 24CXX.
 * @param  [in] pstc24cxxLL         Pointer to a @ref stc_24cxx_ll_t structure.
 * @retval int32_t:
 *         - LL_OK:                 Success
 *         - LL_ERR_INVD_PARAM:     Invalid parameter
 */
int32_t EE_24CXX_DeInit(const stc_24cxx_ll_t *pstc24cxxLL)
{
    int32_t i32Ret = LL_OK;
    if ((pstc24cxxLL == NULL) || (pstc24cxxLL->DeInit == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstc24cxxLL->DeInit();
    }
    return i32Ret;
}

/**
 * @brief  24CXX read data.
 * @param  [in] pstc24cxxLL         Pointer to a @ref stc_24cxx_ll_t structure.
 * @param  [in] u16Addr:            The start address of the data to be read.
 * @param  [in] pu8Buf:             The pointer to the buffer contains the data to be stored.
 * @param  [in] u32Len:             Buffer size in byte.
 * @retval int32_t:
 *         - LL_OK:                 Success
 *         - LL_ERR:                Receive NACK
 *         - LL_ERR_TIMEOUT:        Timeout
 *         - LL_ERR_INVD_PARAM:     Invalid parameter
 */
int32_t EE_24CXX_Read(const stc_24cxx_ll_t *pstc24cxxLL, uint16_t u16Addr, uint8_t *pu8Buf, uint32_t u32Len)
{
    int32_t i32Ret;

    if (((u16Addr + u32Len) > u32Capacity) || (pstc24cxxLL == NULL) || (pstc24cxxLL->Read == NULL) ||
        (pu8Buf == NULL)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        i32Ret = pstc24cxxLL->Read(u16Addr, pu8Buf, u32Len);
    }
    return i32Ret;
}

/**
 * @brief  24CXX write data.
 * @param  [in] pstc24cxxLL         Pointer to a @ref stc_24cxx_ll_t structure.
 * @param  [in] u16Addr:            The start address of the data to be write.
 * @param  [in] pu8Buf:             The pointer to the buffer contains the data to be write.
 * @param  [in] u32Len:             Buffer size in byte.
 * @retval int32_t:
 *         - LL_OK:                 Success
 *         - LL_ERR:                Receive NACK
 *         - LL_ERR_TIMEOUT:        Timeout
 *         - LL_ERR_INVD_PARAM:     Invalid parameter
 */
int32_t EE_24CXX_Write(const stc_24cxx_ll_t *pstc24cxxLL, uint16_t u16Addr, const uint8_t *pu8Buf, uint32_t u32Len)
{
    uint32_t u32PageNum;
    uint8_t u8SingleNumStart;
    uint8_t u8SingleNumEnd;
    uint32_t u32NumRemainTemp = u32Len;
    uint32_t u32WriteOffset = 0UL;
    uint16_t u16WriteAddrTemp = u16Addr;
    int32_t i32Ret = LL_OK;
    uint32_t i;

    if (((u16Addr + u32Len) > u32Capacity) || (u32PageSize == 0U) || (pstc24cxxLL == NULL) ||
        (pstc24cxxLL->WritePage == NULL) || (pstc24cxxLL->Delay == NULL) || (pu8Buf == NULL)) {
        return LL_ERR_INVD_PARAM;
    }

    /* If start write address is align with page size */
    if (0U == (u16WriteAddrTemp % u32PageSize)) {
        /* If Write number is less than page size */
        if (u32Len < u32PageSize) {
            u8SingleNumStart = (uint8_t)u32Len;
        } else {
            /* If Write number is more than page size */
            u8SingleNumStart = 0U;
        }
        u32NumRemainTemp -= (uint32_t)u8SingleNumStart;
    } else {
        /* If start write address is not align with page size */
        u8SingleNumStart = (uint8_t)(u32PageSize - (u16WriteAddrTemp % u32PageSize));
        if ((uint32_t)u8SingleNumStart > u32Len) {
            u8SingleNumStart = (uint8_t)u32Len;
        }
        u32NumRemainTemp -= (uint32_t)u8SingleNumStart;
    }

    u32PageNum = u32NumRemainTemp / u32PageSize;
    u8SingleNumEnd = (uint8_t)(u32NumRemainTemp % u32PageSize);

    if (0UL != u8SingleNumStart) {
        i32Ret = pstc24cxxLL->WritePage(u16WriteAddrTemp, &pu8Buf[u32WriteOffset], (uint32_t)u8SingleNumStart);
        /* Delay about 5ms for EEPROM */
        pstc24cxxLL->Delay(5000U);
        u16WriteAddrTemp += u8SingleNumStart;
        u32WriteOffset += (uint32_t)u8SingleNumStart;
    }

    if (LL_OK == i32Ret) {
        if (0UL != u32PageNum) {
            for (i = 0UL; i < u32PageNum; i++) {
                i32Ret = pstc24cxxLL->WritePage(u16WriteAddrTemp, &pu8Buf[u32WriteOffset], u32PageSize);
                /* Delay about 5ms for EEPROM */
                pstc24cxxLL->Delay(5000U);
                u16WriteAddrTemp += (uint16_t)u32PageSize;
                u32WriteOffset += u32PageSize;
                if (LL_OK != i32Ret) {
                    break;
                }
            }
        }

        if (LL_OK == i32Ret) {
            if (0UL != u8SingleNumEnd) {
                i32Ret = pstc24cxxLL->WritePage(u16WriteAddrTemp, &pu8Buf[u32WriteOffset], (uint32_t)u8SingleNumEnd);
                /* Delay about 5ms for EEPROM */
                pstc24cxxLL->Delay(5000U);
            }
        }
    }
    return i32Ret;
}

/**
 * @brief  24CXX wait idle.
 * @param  [in] pstc24cxxLL         Pointer to a @ref stc_24cxx_ll_t structure.
 * @retval int32_t:
 *         - LL_OK:                 Success
 *         - LL_ERR_TIMEOUT:        Failed
 *         - LL_ERR_INVD_PARAM:     Invalid parameter
 */
int32_t EE_24CXX_WaitIdle(const stc_24cxx_ll_t *pstc24cxxLL)
{
    int32_t i32Ret = LL_OK;
    volatile uint32_t u32Tmp = 0UL;

    if ((pstc24cxxLL == NULL) || (pstc24cxxLL->GetStatus == NULL)) {
        return LL_ERR_INVD_PARAM;
    }
    while (LL_OK != pstc24cxxLL->GetStatus()) {
        if (EE_24CXX_WAIT_TIMEOUT == u32Tmp++) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }
    return i32Ret;
}

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

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
