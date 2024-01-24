/**
 *******************************************************************************
 * @file  ov5640.c
 * @brief This file provides firmware functions for camera OV5640.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ov5640.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @defgroup OV5640 Camera OV5640
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup OV5640_Local_Macros OV5640 Local Macros
 * @{
 */

/**
 * @defgroup OV5640_Chip_ID_Address OV5640 Chip ID Address
 * @{
 */
#define OV5640_CHIPIDH              (0x300AU)
#define OV5640_CHIPIDL              (0x300BU)
/**
 * @}
 */

#define OV5640_ID                   (0x5640U)

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @addtogroup OV5640_Local_Functions
 * @{
 */
static void OV5640_I2C_Delay(const stc_ov5640_ll_t *pstcOv5640LL, uint32_t u32Delay);
static void OV5640_I2C_Init(const stc_ov5640_ll_t *pstcOv5640LL);
static void OV5640_I2C_Read(const stc_ov5640_ll_t *pstcOv5640LL, uint16_t u16Reg,
                            uint8_t au8RegValue[], uint32_t u32Len);
static void OV5640_I2C_Write(const stc_ov5640_ll_t *pstcOv5640LL, uint16_t u16Reg,
                             const uint8_t au8RegValue[], uint32_t u32Len);
/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup OV5640_Global_Functions OV5640 Global Functions
 * @{
 */
/**
 * @brief  Initialize OV5640.
 * @param  [in] pstcOv5640LL            Pointer to a @ref stc_ov5640_ll_t structure.
 * @param  [in] astcOv5640RegTable      Pointer to a @ref stc_ov5640_reg_value_t structure.
 * @param  [in] u32ArraySize            Register table array size.
 * @retval int32_t:
 *           - LL_OK: Initialize successfully
 *           - LL_ERR: Camera ID error
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t OV5640_Init(const stc_ov5640_ll_t *pstcOv5640LL,
                    const stc_ov5640_reg_value_t astcOv5640RegTable[], uint32_t u32ArraySize)
{
    uint32_t i;
    uint8_t u8RegValue;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pstcOv5640LL) && (NULL != astcOv5640RegTable) && (0UL != u32ArraySize)) {
        OV5640_I2C_Init(pstcOv5640LL);

        /* 0x5640 */
        if (OV5640_ID == OV5640_ReadID(pstcOv5640LL)) {
            u8RegValue = 0x11U;
            OV5640_I2C_Read(pstcOv5640LL, 0x3103U, &u8RegValue, 1UL);

            u8RegValue = 0x82U;
            OV5640_I2C_Write(pstcOv5640LL, 0x3008U, &u8RegValue, 1UL);

            OV5640_I2C_Delay(pstcOv5640LL, 100UL);

            for (i = 0UL; i < u32ArraySize; i++) {
                OV5640_I2C_Write(pstcOv5640LL, astcOv5640RegTable[i].u16RegAddr, \
                                 &astcOv5640RegTable[i].u8RegValue, 1UL);
            }

            i32Ret = LL_OK;
        } else {
            i32Ret = LL_ERR;
        }
    }

    return i32Ret;
}

/**
 * @brief  Set OV5640 RGB565 mode.
 * @param  [in] pstcOv5640LL            Pointer to a @ref stc_ov5640_ll_t structure.
 * @param  [in] astcModeRegTable        Pointer to a @ref stc_ov5640_reg_value_t structure.
 * @param  [in] u32ArraySize            Register table array size.
 * @retval int32_t:
 *           - LL_OK: Set successfully
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t OV5640_RGB565_Mode(const stc_ov5640_ll_t *pstcOv5640LL,
                           const stc_ov5640_reg_value_t astcModeRegTable[], uint32_t u32ArraySize)
{
    uint32_t i;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != pstcOv5640LL) && (NULL != astcModeRegTable) && (0UL != u32ArraySize)) {
        for (i = 0UL; i < u32ArraySize; i++) {
            OV5640_I2C_Write(pstcOv5640LL, astcModeRegTable[i].u16RegAddr, \
                             &astcModeRegTable[i].u8RegValue, 1UL);
        }
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Read OV5640 ID.
 * @param  [in] pstcOv5640LL            Pointer to a @ref stc_ov5640_ll_t structure.
 * @retval OV5640 ID.
 */
uint16_t OV5640_ReadID(const stc_ov5640_ll_t *pstcOv5640LL)
{
    uint8_t au8ID[2];

    OV5640_I2C_Read(pstcOv5640LL, OV5640_CHIPIDL, &au8ID[0], 1UL);
    OV5640_I2C_Read(pstcOv5640LL, OV5640_CHIPIDH, &au8ID[1], 1UL);

    return (uint16_t)(((uint16_t)au8ID[1] << 8) | (uint16_t)au8ID[0]);
}

/**
 * @brief  Control OV5640 light.
 * @param  [in] pstcOv5640LL            Pointer to a @ref stc_ov5640_ll_t structure.
 * @param  [in] u8Switch                Light on/off
 *         This parameter can be one of the following values:
 *           @arg OV5640_LIGHT_ON:      Light on
 *           @arg OV5640_LIGHT_OFF:     Light off
 * @retval int32_t:
 *           - LL_OK: Set successfully
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t OV5640_LightControl(const stc_ov5640_ll_t *pstcOv5640LL, uint8_t u8Switch)
{
    uint8_t u8RegValue;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcOv5640LL) {
        u8RegValue = 0x02U;
        OV5640_I2C_Write(pstcOv5640LL, 0x3016U, &u8RegValue, 1UL);
        OV5640_I2C_Write(pstcOv5640LL, 0x301CU, &u8RegValue, 1UL);

        if (OV5640_LIGHT_OFF == u8Switch) {
            u8RegValue = 0x00U;
        }
        OV5640_I2C_Write(pstcOv5640LL, 0x3019U, &u8RegValue, 1UL);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set OV5640 out size.
 * @param  [in] pstcOv5640LL            Pointer to a @ref stc_ov5640_ll_t structure.
 * @param  [in] u16X:                   Window X offset
 * @param  [in] u16Y                    Window Y offset
 * @param  [in] u16Width                Window width
 * @param  [in] u16Height               Window height
 * @retval int32_t:
 *           - LL_OK: Set successfully
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t OV5640_SetOutSize(const stc_ov5640_ll_t *pstcOv5640LL, uint16_t u16X, uint16_t u16Y,
                          uint16_t u16Width, uint16_t u16Height)
{
    uint16_t u16RegValue;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcOv5640LL) {
        u16RegValue = 0x03U;
        OV5640_I2C_Write(pstcOv5640LL, 0x3212U, (uint8_t *)(&u16RegValue), 1UL); /*start group 3 */

        u16RegValue = u16Width >> 8U;
        OV5640_I2C_Write(pstcOv5640LL, 0x3808U, (uint8_t *)(&u16RegValue), 1UL);

        u16RegValue = u16Width & 0xFFU;
        OV5640_I2C_Write(pstcOv5640LL, 0x3809U, (uint8_t *)(&u16RegValue), 1UL);

        u16RegValue = u16Height >> 8U;
        OV5640_I2C_Write(pstcOv5640LL, 0x380AU, (uint8_t *)(&u16RegValue), 1UL);

        u16RegValue = u16Height & 0xFFU;
        OV5640_I2C_Write(pstcOv5640LL, 0x380BU, (uint8_t *)(&u16RegValue), 1UL);

        u16RegValue = u16X >> 8U;
        OV5640_I2C_Write(pstcOv5640LL, 0x3810U, (uint8_t *)(&u16RegValue), 1UL);

        u16RegValue = u16X & 0xFFU;
        OV5640_I2C_Write(pstcOv5640LL, 0x3811U, (uint8_t *)(&u16RegValue), 1UL);

        u16RegValue = u16Y >> 8U;
        OV5640_I2C_Write(pstcOv5640LL, 0x3812U, (uint8_t *)(&u16RegValue), 1UL);

        u16RegValue = u16Y & 0xFFU;
        OV5640_I2C_Write(pstcOv5640LL, 0x3813U, (uint8_t *)(&u16RegValue), 1UL);

        u16RegValue = 0x13U;
        OV5640_I2C_Write(pstcOv5640LL, 0x3212U, (uint8_t *)(&u16RegValue), 1UL); /* end group 3 */

        u16RegValue = 0xA3U;
        OV5640_I2C_Write(pstcOv5640LL, 0x3212U, (uint8_t *)(&u16RegValue), 1UL); /* launch group 3 */
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set OV5640 test pattern.
 * @param  [in] pstcOv5640LL            Pointer to a @ref stc_ov5640_ll_t structure.
 * @param  [in] u8Mode                  Test mode
 * @retval int32_t:
 *           - LL_OK: Set successfully
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t OV5640_TestPattern(const stc_ov5640_ll_t *pstcOv5640LL, uint8_t u8Mode)
{
    uint8_t u8RegValue;
    uint16_t u16RegAddr;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcOv5640LL) {
        switch (u8Mode) {
            case 0:
                u8RegValue = 0x00U;
                break;
            case 1:
                u8RegValue = 0x80U;
                break;
            case 2:
                u8RegValue = 0x82U;
                break;
            default:
                u8RegValue = 0x00U;
                break;
        }

        u16RegAddr = 0x503DU;
        OV5640_I2C_Write(pstcOv5640LL, u16RegAddr, &u8RegValue, 1UL);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @}
 */


/**
 * @defgroup OV5640_Local_Functions OV5640 Local Functions
 * @{
 */

/**
 * @brief  OV5640 I2C delay.
 * @param  [in]  pstcOv5640LL           Pointer to a @ref stc_ov5640_ll_t structure
 * @param  [in]  u32Delay               Register to be read
 * @retval None
 */
static void OV5640_I2C_Delay(const stc_ov5640_ll_t *pstcOv5640LL, uint32_t u32Delay)
{
    if ((NULL != pstcOv5640LL) && (NULL != pstcOv5640LL->Delay)) {
        pstcOv5640LL->Delay(u32Delay);
    }
}

/**
 * @brief  OV5640 I2C initialize.
 * @param  [in] pstcOv5640LL            Pointer to a @ref stc_ov5640_ll_t structure
 * @retval None
 */
static void OV5640_I2C_Init(const stc_ov5640_ll_t *pstcOv5640LL)
{
    if ((NULL != pstcOv5640LL) && (NULL != pstcOv5640LL->Init)) {
        (void)pstcOv5640LL->Init();
    }
}

/**
 * @brief  Read register on Camera register.
 * @param  [in]  pstcOv5640LL           Pointer to a @ref stc_ov5640_ll_t structure
 * @param  [in]  u16Reg                 Register to be read
 * @param  [out] au8RegValue            The buffer for reading
 * @param  [in]  u32Len                 The buffer size for bytes
 * @retval None
 */
static void OV5640_I2C_Read(const stc_ov5640_ll_t *pstcOv5640LL, uint16_t u16Reg,
                            uint8_t au8RegValue[], uint32_t u32Len)
{
    uint8_t au8RegAddr[2];

    if ((NULL != pstcOv5640LL) && (NULL != pstcOv5640LL->Read)) {
        au8RegAddr[0] = (uint8_t)((u16Reg & 0xFF00U) >> 8);
        au8RegAddr[1] = (uint8_t)(u16Reg & 0x00FFU);
        (void)pstcOv5640LL->Read(au8RegAddr, ARRAY_SZ(au8RegAddr), au8RegValue, u32Len);
    }
}

/**
 * @brief  Write register on Camera register.
 * @param  [in]  pstcOv5640LL           Pointer to a @ref stc_ov5640_ll_t structure
 * @param  [in]  u16Reg                 Register to be write
 * @param  [in]  au8RegValue            The buffer for writing
 * @param  [in]  u32Len                 The buffer size for bytes
 * @retval None
 */
static void OV5640_I2C_Write(const stc_ov5640_ll_t *pstcOv5640LL, uint16_t u16Reg,
                             const uint8_t au8RegValue[], uint32_t u32Len)
{
    uint8_t au8RegAddr[2];

    if ((NULL != pstcOv5640LL) && (NULL != pstcOv5640LL->Write)) {
        au8RegAddr[0] = (uint8_t)((u16Reg & 0xFF00U) >> 8);
        au8RegAddr[1] = (uint8_t)(u16Reg & 0x00FFU);
        (void)pstcOv5640LL->Write(au8RegAddr, ARRAY_SZ(au8RegAddr), au8RegValue, u32Len);
    }
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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
