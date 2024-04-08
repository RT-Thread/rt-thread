/**
 *******************************************************************************
 * @file  ev_hc32f448_lqfp80_gt9xx.c
 * @brief This file provides firmware functions of the touch pad gt9xx driver
 *        library for the board EV_HC32F448_LQFP80.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <string.h>
#include "ev_hc32f448_lqfp80_gt9xx.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F448_LQFP80
 * @{
 */

/**
 * @defgroup EV_HC32F448_LQFP80_GT9XX EV_HC32F448_LQFP80 GT9XX
 * @{
 */

#if ((BSP_GT9XX_ENABLE == DDL_ON) && (BSP_EV_HC32F448_LQFP80 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @addtogroup EV_HC32F448_LQFP80_GT9XX_Local_Functions
 * @{
 */
static void BSP_GT9XX_I2C_Init(void);
static void BSP_GT9XX_I2C_Read(const uint8_t au8Reg[], uint8_t u8RegLen, uint8_t *pu8Buf, uint32_t u32Len);
static void BSP_GT9XX_I2C_Write(const uint8_t au8Reg[], uint8_t u8RegLen, const uint8_t *pu8Buf, uint32_t u32Len);
/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/**
 * @defgroup EV_HC32F448_LQFP80_GT9XX_Local_Variables EV_HC32F448_LQFP80 GT9XX Local Variables
 * @{
 */
const static stc_gt9xx_ll_t m_stcGt9xxLL = {
    .Init  = BSP_GT9XX_I2C_Init,
    .Read  = BSP_GT9XX_I2C_Read,
    .Write = BSP_GT9XX_I2C_Write,
};
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F448_LQFP80_GT9XX_Local_Functions EV_HC32F448_LQFP80 GT9XX Local Functions
 * @{
 */

/**
 * @brief  Initializes I2C for GT9XX.
 * @param  None
 * @retval None
 */
static void BSP_GT9XX_I2C_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    /* Configuration I2C GPIO */
    (void)GPIO_StructInit(&stcGpioInit);
    (void)GPIO_Init(BSP_GT9XX_I2C_SCL_PORT, BSP_GT9XX_I2C_SCL_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_GT9XX_I2C_SCL_PORT, BSP_GT9XX_I2C_SCL_PIN, &stcGpioInit);

    /* Initialize I2C port*/
    GPIO_SetFunc(BSP_GT9XX_I2C_SCL_PORT, BSP_GT9XX_I2C_SCL_PIN, BSP_GT9XX_I2C_SCL_FUNC);
    GPIO_SetFunc(BSP_GT9XX_I2C_SDA_PORT, BSP_GT9XX_I2C_SDA_PIN, BSP_GT9XX_I2C_SDA_FUNC);

    /* Enable I2C Peripheral*/
    FCG_Fcg0PeriphClockCmd(BSP_GT9XX_I2C_FCG, ENABLE);

    (void)BSP_I2C_Init(BSP_GT9XX_I2C_UNIT);
}

/**
 * @brief  BSP GT9XX I2C read.
 * @param  [in]  pu8Reg:                Pointer to the register address.
 * @param  [in]  u8RegLen:              Length of register address.
 * @param  [out] pu8Buf:                The pointer to the buffer contains the data to be read.
 * @param  [in]  u32Len:                Buffer size in byte.
 * @retval None
 */
static void BSP_GT9XX_I2C_Read(const uint8_t *pu8Reg, uint8_t u8RegLen, uint8_t *pu8Buf, uint32_t u32Len)
{
    (void)BSP_I2C_Read(BSP_GT9XX_I2C_UNIT, BSP_GT9XX_I2C_ADDR, pu8Reg, u8RegLen, pu8Buf, u32Len);
}

/**
 * @brief  BSP GT9XX I2C write.
 * @param  [in] pu8Reg:                 Pointer to the register address.
 * @param  [in] u8RegLen:               Length of register address.
 * @param  [in] pu8Buf:                 The pointer to the buffer contains the data to be read.
 * @param  [in] u32Len:                 Buffer size in byte.
 * @retval None
 */
static void BSP_GT9XX_I2C_Write(const uint8_t *pu8Reg, uint8_t u8RegLen, const uint8_t *pu8Buf, uint32_t u32Len)
{
    (void)BSP_I2C_Write(BSP_GT9XX_I2C_UNIT, BSP_GT9XX_I2C_ADDR, pu8Reg, u8RegLen, pu8Buf, u32Len);
}

/**
 * @}
 */

/**
 * @defgroup EV_HC32F448_LQFP80_GT9XX_Global_Functions EV_HC32F448_LQFP80 GT9XX Global Functions
 * @{
 */

/**
 * @brief  GT9XX device initialize.
 * @param  None
 * @retval None
 */
void BSP_GT9XX_Init(void)
{
    char acTmp[4];
    BSP_GT9XX_I2C_Init();

    BSP_GT9XX_ReadProductID((uint8_t *)acTmp, 4UL);
    if (((acTmp[0] == '9') && (acTmp[1] == '1') && (acTmp[2] == '1')) || \
        ((acTmp[0] == '9') && (acTmp[1] == '1') && (acTmp[2] == '7') && (acTmp[3] == 'S'))) {
        BSP_GT9XX_SoftReset();
    } else {
        DDL_Printf("Unsupoort touch driver IC");
    }
}

/**
 * @brief  Reset GT9XX.
 * @param  None
 * @retval None
 */
void BSP_GT9XX_SoftReset(void)
{
    GT9XX_SoftReset(&m_stcGt9xxLL);
}

/**
 * @brief  Read GT9XX touch status.
 * @param  None
 * @retval Touch status
 */
uint8_t BSP_GT9XX_ReadTouchStatus(void)
{
    return GT9XX_ReadTouchStatus(&m_stcGt9xxLL);
}

/**
 * @brief  Read GT9XX ID.
 * @param  [out] pu8IDValue             The buffer for reading ID
 * @param  [in]  u32Len                 The buffer size for bytes
 * @retval None
 */
void BSP_GT9XX_ReadProductID(uint8_t *pu8IDValue, uint32_t u32Len)
{
    GT9XX_ReadProductID(&m_stcGt9xxLL, pu8IDValue, u32Len);
}

/**
 * @brief  Read GT9XX point.
 * @param  [in]  u16Point               Touch pad point
 * @param  [out] pu16X                  Point x coordinate
 * @param  [out] pu16Y                  Point y coordinate
 * @retval None
 */
void BSP_GT9XX_GetXY(uint16_t u16Point, uint16_t *pu16X, uint16_t *pu16Y)
{
    GT9XX_GetXY(&m_stcGt9xxLL, u16Point, pu16X, pu16Y);
}

/**
 * @brief  Read register on touch pad register.
 * @param  [in]  u16Reg                 Register to be read
 * @param  [out] pu8RegValue            The buffer for reading
 * @param  [in]  u32Len                 The buffer size for bytes
 * @retval None
 */
void BSP_GT9XX_REG_Read(uint16_t u16Reg, uint8_t *pu8RegValue, uint32_t u32Len)
{
    GT9XX_REG_Read(&m_stcGt9xxLL, u16Reg, pu8RegValue, u32Len);
}

/**
 * @brief  Write register on touch pad register.
 * @param  [in]  u16Reg                 Register to be write
 * @param  [in]  pu8RegValue            The buffer for writing
 * @param  [in]  u32Len                 The buffer size for bytes
 * @retval None
 */
void BSP_GT9XX_REG_Write(uint16_t u16Reg, const uint8_t *pu8RegValue, uint32_t u32Len)
{
    GT9XX_REG_Write(&m_stcGt9xxLL, u16Reg, pu8RegValue, u32Len);
}

/**
 * @}
 */

#endif /* BSP_GT9XX_ENABLE && BSP_EV_HC32F448_LQFP80 */

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
