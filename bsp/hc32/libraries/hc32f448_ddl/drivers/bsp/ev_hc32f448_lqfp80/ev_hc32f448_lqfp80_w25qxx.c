/**
 *******************************************************************************
 * @file  ev_hc32f448_lqfp80_w25qxx.c
 * @brief This file provides firmware functions for QSPI/SPI NOR W25QXX.
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
#include "ev_hc32f448_lqfp80_w25qxx.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F448_LQFP80
 * @{
 */

/**
 * @defgroup EV_HC32F448_LQFP80_W25QXX EV_HC32F448_LQFP80 W25QXX
 * @{
 */

#if ((BSP_W25QXX_ENABLE == DDL_ON) && (BSP_EV_HC32F448_LQFP80 == BSP_EV_HC32F4XX))

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
static void BSP_SPI_Init(void);
static void BSP_SPI_DeInit(void);
static void BSP_SPI_Active(void);
static void BSP_SPI_Inactive(void);
static int32_t BSP_SPI_Trans(const uint8_t *pu8TxBuf, uint32_t u32Size);
static int32_t BSP_SPI_Receive(uint8_t *pu8RxBuf, uint32_t u32Size);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static stc_w25qxx_ll_t m_stcW25qxxLL = {
    .Delay    = DDL_DelayMS,
    .Init     = BSP_SPI_Init,
    .DeInit   = BSP_SPI_DeInit,
    .Active   = BSP_SPI_Active,
    .Inactive = BSP_SPI_Inactive,
    .Trans    = BSP_SPI_Trans,
    .Receive  = BSP_SPI_Receive,
};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F448_LQFP80_W25QXX_Local_Functions EV_HC32F448_LQFP80 W25QXX Local Functions
 * @{
 */

/**
 * @brief  SPI CS active.
 * @param  None
 * @retval None
 */
static void BSP_SPI_Active(void)
{
    BSP_SPI_CS_ACTIVE();
}

/**
 * @brief  SPI CS inactive.
 * @param  None
 * @retval None
 */
static void BSP_SPI_Inactive(void)
{
    BSP_SPI_CS_INACTIVE();
}

/**
 * @brief  Initializes the BSP SPI interface.
 * @param  None
 * @retval None
 */
static void BSP_SPI_Init(void)
{
    stc_gpio_init_t stcGpioInit;
    stc_spi_init_t stcSpiInit;
    stc_spi_delay_t stcSpiDelayCfg;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
    stcGpioInit.u16PinInputType = PIN_IN_TYPE_CMOS;
    (void)GPIO_Init(BSP_SPI_SCK_PORT, BSP_SPI_SCK_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_SPI_MOSI_PORT, BSP_SPI_MOSI_PIN, &stcGpioInit);
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STAT_SET;
    (void)GPIO_Init(BSP_SPI_CS_PORT,  BSP_SPI_CS_PIN,  &stcGpioInit);

    GPIO_SetFunc(BSP_SPI_SCK_PORT, BSP_SPI_SCK_PIN, BSP_SPI_SCK_PIN_FUNC);
    GPIO_SetFunc(BSP_SPI_MOSI_PORT, BSP_SPI_MOSI_PIN, BSP_SPI_MOSI_PIN_FUNC);
    GPIO_SetFunc(BSP_SPI_MISO_PORT, BSP_SPI_MISO_PIN, BSP_SPI_MISO_PIN_FUNC);

    /* Clear initialize structure */
    (void)SPI_StructInit(&stcSpiInit);
    (void)SPI_DelayStructInit(&stcSpiDelayCfg);

    /* Configure peripheral clock */
    FCG_Fcg1PeriphClockCmd(BSP_SPI_PERIPH_CLK, ENABLE);

    /* SPI De-initialize */
    (void)SPI_DeInit(BSP_SPI_UNIT);
    /* Configuration SPI structure */
    stcSpiInit.u32WireMode          = SPI_4_WIRE;
    stcSpiInit.u32TransMode         = SPI_FULL_DUPLEX;
    stcSpiInit.u32MasterSlave       = SPI_MASTER;
    stcSpiInit.u32ModeFaultDetect   = SPI_MD_FAULT_DETECT_DISABLE;
    stcSpiInit.u32Parity            = SPI_PARITY_INVD;
    stcSpiInit.u32SpiMode           = SPI_MD_0;
    stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV64;
    stcSpiInit.u32DataBits          = SPI_DATA_SIZE_8BIT;
    stcSpiInit.u32FirstBit          = SPI_FIRST_MSB;
    (void)SPI_Init(BSP_SPI_UNIT, &stcSpiInit);

    stcSpiDelayCfg.u32IntervalDelay = SPI_INTERVAL_TIME_8SCK;
    stcSpiDelayCfg.u32ReleaseDelay  = SPI_RELEASE_TIME_8SCK;
    stcSpiDelayCfg.u32SetupDelay    = SPI_SETUP_TIME_1SCK;
    (void)SPI_DelayTimeConfig(BSP_SPI_UNIT, &stcSpiDelayCfg);
    SPI_Cmd(BSP_SPI_UNIT, ENABLE);
}

/**
 * @brief  De-Initialize the BSP SPI interface.
 * @param  None
 * @retval None
 */
static void BSP_SPI_DeInit(void)
{
    /* SPI De-initialize */
    (void)SPI_DeInit(BSP_SPI_UNIT);
}

/**
 * @brief  BSP SPI transmit data.
 * @param  [in]  pu8TxBuf               The data buffer that to be transmitted.
 * @param  [in]  u32Size                Number of data bytes to be transmitted.
 * @retval int32_t:
 *           - LL_OK:                   Data transmission successful.
 *           - LL_ERR_TIMEOUT:          Data transmission timeout.
 */
static int32_t BSP_SPI_Trans(const uint8_t *pu8TxBuf, uint32_t u32Size)
{
    return SPI_Trans(BSP_SPI_UNIT, pu8TxBuf, u32Size, BSP_SPI_TIMEOUT);
}

/**
 * @brief  BSP SPI receive data.
 * @param  [in]  pu8RxBuf               The buffer that received data to be stored.
 * @param  [in]  u32Size                Number of data bytes to be received.
 * @retval int32_t:
 *           - LL_OK:                   Data receive successful.
 *           - LL_ERR_TIMEOUT:          Data receive timeout.
 */
static int32_t BSP_SPI_Receive(uint8_t *pu8RxBuf, uint32_t u32Size)
{
    return SPI_Receive(BSP_SPI_UNIT, pu8RxBuf, u32Size, BSP_SPI_TIMEOUT);
}

/**
 * @}
 */

/**
 * @defgroup EV_HC32F448_LQFP80_W25QXX_Global_Functions EV_HC32F448_LQFP80 W25QXX Global Functions
 * @{
 */

/**
 * @brief  Initializes BSP W25QXX.
 * @param  None
 * @retval None
 */
void BSP_W25QXX_Init(void)
{
    (void)W25QXX_Init(&m_stcW25qxxLL);
}

/**
 * @brief  De-Initializes BSP W25QXX.
 * @param  None
 * @retval None
 */
void BSP_W25QXX_DeInit(void)
{
    (void)W25QXX_DeInit(&m_stcW25qxxLL);
}

/**
 * @brief  Writes an amount of data to W25QXX via SPI interface.
 * @param  [in]  u32Addr                Write start address.
 * @param  [in]  pu8Data                Pointer to data to be written.
 * @param  [in]  u32NumByteToWrite      Size of data to write.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout or W25QXX timeout.
 */
int32_t BSP_W25QXX_Write(uint32_t u32Addr, const uint8_t *pu8Data, uint32_t u32NumByteToWrite)
{
    uint32_t u32TempSize;
    uint32_t u32AddrOfst = 0UL;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT((u32Addr + u32NumByteToWrite) <= W25Q64_MAX_ADDR);

    if ((pu8Data != NULL) && (u32NumByteToWrite > 0UL)) {
        while (u32NumByteToWrite != 0UL) {
            if (u32NumByteToWrite >= W25Q64_PAGE_SIZE) {
                u32TempSize = W25Q64_PAGE_SIZE;
            } else {
                u32TempSize = u32NumByteToWrite;
            }

            i32Ret = W25QXX_PageProgram(&m_stcW25qxxLL, u32Addr, (const uint8_t *)&pu8Data[u32AddrOfst], u32TempSize);
            if (i32Ret != LL_OK) {
                break;
            }
            u32NumByteToWrite -= u32TempSize;
            u32AddrOfst += u32TempSize;
            u32Addr  += u32TempSize;
        }
    }

    return i32Ret;
}

/**
 * @brief  Reads an amount of data to W25QXX via SPI interface.
 * @param  [in]  u32Addr                Read start address.
 * @param  [in]  pu8Data                Pointer to data to be read.
 * @param  [in]  u32NumByteToRead       Size of data to read.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout or W25QXX timeout.
 */
int32_t BSP_W25QXX_Read(uint32_t u32Addr, uint8_t *pu8Data, uint32_t u32NumByteToRead)
{
    DDL_ASSERT((u32Addr + u32NumByteToRead) <= W25Q64_MAX_ADDR);
    return W25QXX_ReadData(&m_stcW25qxxLL, u32Addr, pu8Data, u32NumByteToRead);
}

/**
 * @brief  Erases specified sector of W25QXX.
 * @param  [in]  u32Addr                Any address of the specified sector.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          SPI timeout or W25QXX timeout.
 */
int32_t BSP_W25QXX_EraseSector(uint32_t u32Addr)
{
    DDL_ASSERT(u32Addr < W25Q64_MAX_ADDR);
    return W25QXX_EraseSector(&m_stcW25qxxLL, u32Addr);
}

/**
 * @brief  Erases W25QXX whole chip.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          SPI timeout or W25QXX timeout.
 */
int32_t BSP_W25QXX_EraseChip(void)
{
    return W25QXX_EraseChip(&m_stcW25qxxLL);
}

/**
 * @}
 */

#endif /* (BSP_W25QXX_ENABLE && BSP_EV_HC32F448_LQFP80) */

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
