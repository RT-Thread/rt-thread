/**
 *******************************************************************************
 * @file  ev_hc32f460_lqfp100_v2_24cxx.c
 * @brief This file provides firmware functions for EEPROM 24CXX.
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
#include "ev_hc32f460_lqfp100_v2_24cxx.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F460_LQFP100_V2
 * @{
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_24CXX EV_HC32F460_LQFP100_V2 24CXX
 * @{
 */

#if ((BSP_24CXX_ENABLE == DDL_ON) && (BSP_EV_HC32F460_LQFP100_V2 == BSP_EV_HC32F4XX))

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
 * @addtogroup EV_HC32F460_LQFP100_V2_24CXX_Local_Functions
 * @{
 */
static int32_t BSP_24CXX_I2C_Init(void);
static void BSP_24CXX_I2C_DeInit(void);
static int32_t BSP_24CXX_I2C_WritePage(uint16_t u16Addr, const uint8_t *pu8Buf, uint32_t u32Len);
static int32_t BSP_24CXX_I2C_Read(uint16_t u16Addr, uint8_t *pu8Buf, uint32_t u32Len);
static int32_t BSP_24CXX_I2C_GetStatus(void);
/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F460_LQFP100_V2_24CXX_Local_Variables EV_HC32F460_LQFP100_V2 24CXX Local Variables
 * @{
 */
static stc_24cxx_ll_t m_stc24cxxLL = {
    .u32PageSize = EE_24CXX_PAGE_SIZE,
    .u32Capacity = EE_24CXX_CAPACITY,
    .Delay = DDL_DelayUS,
    .Init = BSP_24CXX_I2C_Init,
    .DeInit = BSP_24CXX_I2C_DeInit,
    .WritePage = BSP_24CXX_I2C_WritePage,
    .Read = BSP_24CXX_I2C_Read,
    .GetStatus = BSP_24CXX_I2C_GetStatus
};
/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup EV_HC32F460_LQFP100_V2_24CXX_Local_Functions EV_HC32F460_LQFP100_V2 24CXX Local Functions
 * @{
 */

/**
 * @brief  Initializes I2C for 24CXX.
 * @param  None
 * @retval int32_t:
 *            - LL_OK:              Success
 *            - LL_ERR_INVD_PARAM:  Invalid parameter
 */
static int32_t BSP_24CXX_I2C_Init(void)
{
    stc_gpio_init_t stcGpioInit;
    /* Configuration I2C GPIO */
    (void)GPIO_StructInit(&stcGpioInit);
    (void)GPIO_Init(BSP_24CXX_I2C_SCL_PORT, BSP_24CXX_I2C_SCL_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_24CXX_I2C_SDA_PORT, BSP_24CXX_I2C_SDA_PIN, &stcGpioInit);
    GPIO_SetFunc(BSP_24CXX_I2C_SCL_PORT, BSP_24CXX_I2C_SCL_PIN, BSP_24CXX_I2C_SCL_FUNC);
    GPIO_SetFunc(BSP_24CXX_I2C_SDA_PORT, BSP_24CXX_I2C_SDA_PIN, BSP_24CXX_I2C_SDA_FUNC);
    /* Enable I2C Peripheral*/
    FCG_Fcg1PeriphClockCmd(BSP_24CXX_I2C_FCG, ENABLE);
    return BSP_I2C_Init(BSP_24CXX_I2C_UNIT);
}

/**
 * @brief  De-Initializes I2C for 24CXX.
 * @param  None
 * @retval None
 */
static void BSP_24CXX_I2C_DeInit(void)
{
    /* Initialize I2C port*/
    GPIO_SetFunc(BSP_24CXX_I2C_SCL_PORT, BSP_24CXX_I2C_SCL_PIN, GPIO_FUNC_0);
    GPIO_SetFunc(BSP_24CXX_I2C_SDA_PORT, BSP_24CXX_I2C_SDA_PIN, GPIO_FUNC_0);
    I2C_DeInit(BSP_24CXX_I2C_UNIT);
}

/**
 * @brief  BSP 24CXX write page data.
 * @param  [in] u16Addr:            The start address of the data to be write.
 * @param  [in] pu8Buf:             The pointer to the buffer contains the data to be write.
 * @param  [in] u32Len:             Buffer size in byte.
 * @retval int32_t:
 *            - LL_OK:              Success
 *            - LL_ERR:             Receive NACK
 *            - LL_ERR_TIMEOUT:     Timeout
 *            - LL_ERR_INVD_PARAM:  pu8Buf is NULL
 * @note   This function don't check if the data write is within one page
 */
static int32_t BSP_24CXX_I2C_WritePage(uint16_t u16Addr, const uint8_t *pu8Buf, uint32_t u32Len)
{
    uint16_t u16MemAddrTemp;
#if (EE_24CXX_MEM_ADDR_LEN == 1U)
    u16MemAddrTemp = u16Addr;
#else
    u16MemAddrTemp = (uint16_t)((((uint32_t)u16Addr >> 8) & 0xFFUL) + (((uint32_t)u16Addr << 8) & 0xFF00UL));
#endif
    return BSP_I2C_Write(BSP_24CXX_I2C_UNIT, EE_24CXX_DEV_ADDR, (const uint8_t *)&u16MemAddrTemp, EE_24CXX_MEM_ADDR_LEN, pu8Buf, u32Len);
}

/**
 * @brief  BSP 24CXX Read data.
 * @param  [in] u16Addr:            The start address of the data to be read.
 * @param  [in] pu8Buf:             The pointer to the buffer contains the data to be read.
 * @param  [in] u32Len:             Buffer size in byte.
 * @retval int32_t:
 *            - LL_OK:              Success
 *            - LL_ERR:             Receive NACK
 *            - LL_ERR_TIMEOUT:     Timeout
 *            - LL_ERR_INVD_PARAM:  pu8Buf is NULL
 */
static int32_t BSP_24CXX_I2C_Read(uint16_t u16Addr, uint8_t *pu8Buf, uint32_t u32Len)
{
    uint16_t u16MemAddrTemp;
#if (EE_24CXX_MEM_ADDR_LEN == 1U)
    u16MemAddrTemp = u16Addr;
#else
    u16MemAddrTemp = (uint16_t)((((uint32_t)u16Addr >> 8) & 0xFFUL) + (((uint32_t)u16Addr << 8) & 0xFF00UL));
#endif
    return BSP_I2C_Read(BSP_24CXX_I2C_UNIT, EE_24CXX_DEV_ADDR, (const uint8_t *)&u16MemAddrTemp, EE_24CXX_MEM_ADDR_LEN, pu8Buf, u32Len);
}

/**
 * @brief  BSP 24CXX status get.
 * @param  None
 * @retval int32_t:
 *            - LL_OK:              Idle
 *            - LL_ERR:             Receive NACK
 *            - LL_ERR_TIMEOUT:     Timeout
 *            - LL_ERR_INVD_PARAM:  pu8Buf is NULL
 */
static int32_t BSP_24CXX_I2C_GetStatus(void)
{
    return BSP_I2C_GetDevStatus(BSP_24CXX_I2C_UNIT, EE_24CXX_DEV_ADDR);
}
/**
 * @}
 */

/**
 * @defgroup EV_HC32F460_LQFP100_V2_24CXX_Global_Functions EV_HC32F460_LQFP100_V2 24CXX Global Functions
 * @{
 */

/**
 * @brief  BSP Initializes I2C for 24CXX.
 * @param  None
 * @retval int32_t:
 *            - LL_OK:              Success
 *            - LL_ERR_INVD_PARAM:  Invalid parameter
 */
int32_t BSP_24CXX_Init(void)
{
    return EE_24CXX_Init(&m_stc24cxxLL);
}

/**
 * @brief  BSP De-Initializes I2C for 24CXX.
 * @param  None
 * @retval int32_t:
 *            - LL_OK:              Success
 *            - LL_ERR_INVD_PARAM:  Invalid parameter
 */
int32_t BSP_24CXX_DeInit(void)
{
    return EE_24CXX_DeInit(&m_stc24cxxLL);
}

/**
 * @brief  BSP 24CXX write data.
 * @param  [in] u16Addr:            The start address of the data to be write.
 * @param  [in] pu8Buf:             The pointer to the buffer contains the data to be write.
 * @param  [in] u32Len:             Buffer size in byte.
 * @retval int32_t:
 *            - LL_OK:              Success
 *            - LL_ERR:             Receive NACK
 *            - LL_ERR_TIMEOUT:     Timeout
 *            - LL_ERR_INVD_PARAM:  pu8Buf is NULL
 */
int32_t BSP_24CXX_Write(uint16_t u16Addr, const uint8_t *pu8Buf, uint32_t u32Len)
{
    return EE_24CXX_Write(&m_stc24cxxLL, u16Addr, pu8Buf, u32Len);
}

/**
 * @brief  24CXX read data.
 * @param  [in] u16Addr:        The start address of the data to be read.
 * @param  [in] pu8Buf:         The pointer to the buffer contains the data to be stored.
 * @param  [in] u32Len:         Buffer size in byte.
 * @retval int32_t:
 *            - LL_OK:              Success
 *            - LL_ERR:             Receive NACK
 *            - LL_ERR_TIMEOUT:     Timeout
 *            - LL_ERR_INVD_PARAM:  pu8Buf is NULL
 */
int32_t BSP_24CXX_Read(uint16_t u16Addr, uint8_t *pu8Buf, uint32_t u32Len)
{
    return EE_24CXX_Read(&m_stc24cxxLL, u16Addr, pu8Buf, u32Len);
}

/**
 * @brief  24CXX wait idle.
 * @param  None
 * @retval int32_t:
 *            - LL_OK:              Success
 *            - LL_ERR_TIMEOUT:     Failed
 */
int32_t BSP_24CXX_WaitIdle(void)
{
    return EE_24CXX_WaitIdle(&m_stc24cxxLL);
}

/**
 * @}
 */

#endif /* (BSP_24CXX_ENABLE && BSP_EV_HC32F460_LQFP100_V2) */

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
