/**
 *******************************************************************************
 * @file  w25qxx.c
 * @brief This midware file provides firmware functions to W25QXX group spi flash.
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
#include "w25qxx.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @defgroup W25QXX Flash Driver for W25QXX
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup W25QXX_Local_Macros W25QXX Local Macros
 * @{
 */
#define W25QXX_FLAG_BUSY            (1UL << 0U)
#define W25QXX_FLAG_WEL             (1UL << 1U)         /*!< Write Enable Latch */
#define W25QXX_FLAG_SUSPEND         (1UL << 15U)        /*!< Write Enable Latch */

#define LOAD_CMD(a, cmd, addr)      do {                                    \
                                        (a)[0U] = (cmd);                    \
                                        (a)[1U] = (uint8_t)((addr) >> 16U); \
                                        (a)[2U] = (uint8_t)((addr) >> 8U);  \
                                        (a)[3U] = (uint8_t)(addr);          \
                                    } while (0U)

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

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @addtogroup W25QXX_Local_Functions W25QXX Local Functions
 * @{
 */

/**
 * @brief  W25QXX write command.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [in]  u8Cmd                  Command of W25QXX.
 * @param  [in]  pu8CmdData             Pointer to a buffer that contains the data following the command.
 * @param  [in]  u32CmdDataLen          The length of the command data in bytes.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 */
static int32_t W25QXX_WriteCmd(const stc_w25qxx_ll_t *pstcW25qxxLL, \
                               uint8_t u8Cmd, const uint8_t *pu8CmdData, uint32_t u32CmdDataLen)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcW25qxxLL == NULL) {
        return i32Ret;
    }

    if ((pstcW25qxxLL->Active != NULL) && (pstcW25qxxLL->Trans != NULL) && (pstcW25qxxLL->Inactive != NULL)) {
        pstcW25qxxLL->Active();
        i32Ret = pstcW25qxxLL->Trans(&u8Cmd, 1U);
        if ((i32Ret == LL_OK) && (pu8CmdData != NULL) && (u32CmdDataLen > 0UL)) {
            i32Ret = pstcW25qxxLL->Trans(pu8CmdData, u32CmdDataLen);
        }
        pstcW25qxxLL->Inactive();
    }

    return i32Ret;
}

/**
 * @brief  W25QXX read command.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [in]  u8Cmd                  Command of W25QXX.
 * @param  [in]  pu8CmdData             Pointer to a buffer that contains the data following the command.
 * @param  [in]  u32CmdDataLen          The length of the command data in bytes.
 * @param  [in]  pu8Info                The information of the command.
 * @param  [in]  u8InfoLen              The length of the information.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 */
static int32_t W25QXX_ReadCmd(const stc_w25qxx_ll_t *pstcW25qxxLL, \
                              uint8_t u8Cmd, uint8_t *pu8CmdData, uint32_t u32CmdDataLen,
                              uint8_t *pu8Info, uint8_t u8InfoLen)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcW25qxxLL == NULL) {
        return i32Ret;
    }

    if ((pstcW25qxxLL->Active != NULL) && (pstcW25qxxLL->Trans != NULL) && (pstcW25qxxLL->Receive != NULL) &&
        (pstcW25qxxLL->Inactive != NULL)) {
        pstcW25qxxLL->Active();
        i32Ret = pstcW25qxxLL->Trans(&u8Cmd, 1U);
        if ((i32Ret == LL_OK) && (pu8CmdData != NULL) && (u32CmdDataLen > 0UL)) {
            i32Ret = pstcW25qxxLL->Trans(pu8CmdData, u32CmdDataLen);
        }
        if ((i32Ret == LL_OK) && (pu8Info != NULL) && (u8InfoLen > 0UL)) {
            i32Ret = pstcW25qxxLL->Receive(pu8Info, (uint32_t)u8InfoLen);
        }
        pstcW25qxxLL->Inactive();
    }

    return i32Ret;
}

/**
 * @brief  W25QXX write data.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [in]  u8Cmd                  Command of W25QXX.
 * @param  [in]  u32Addr                The start address of the data to be written.
 * @param  [in]  pu8Data                The data to be written.
 * @param  [in]  u32DataLen             The length of the data in bytes.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 */
static int32_t W25QXX_Wt(const stc_w25qxx_ll_t *pstcW25qxxLL, \
                         uint8_t u8Cmd, uint32_t u32Addr, \
                         const uint8_t *pu8Data, uint32_t u32DataLen)
{
    uint8_t au8Cmd[4U];
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcW25qxxLL == NULL) {
        return i32Ret;
    }

    if ((pstcW25qxxLL->Active != NULL) && (pstcW25qxxLL->Trans != NULL) && (pstcW25qxxLL->Inactive != NULL)) {
        LOAD_CMD(au8Cmd, u8Cmd, u32Addr);
        pstcW25qxxLL->Active();
        i32Ret = pstcW25qxxLL->Trans(au8Cmd, 4U);
        if ((i32Ret == LL_OK) && (pu8Data != NULL) && (u32DataLen > 0UL)) {
            i32Ret = pstcW25qxxLL->Trans(pu8Data, u32DataLen);
        }
        pstcW25qxxLL->Inactive();
    }

    return i32Ret;
}

/**
 * @brief  W25QXX read data.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [in]  u8Cmd                  Command of W25QXX.
 * @param  [in]  u32Addr                The start address of the data to be written.
 * @param  [in]  pu8Data                The data to be stored.
 * @param  [in]  u32DataLen             The length of the data in bytes.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 */
static int32_t W25QXX_Rd(const stc_w25qxx_ll_t *pstcW25qxxLL, \
                         uint8_t u8Cmd, uint32_t u32Addr, \
                         uint8_t *pu8Data, uint32_t u32DataLen)
{
    uint8_t au8Cmd[4U];
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcW25qxxLL == NULL) {
        return i32Ret;
    }

    if ((pstcW25qxxLL->Active != NULL) && (pstcW25qxxLL->Trans != NULL) && (pstcW25qxxLL->Receive != NULL) &&
        (pstcW25qxxLL->Inactive != NULL)) {
        LOAD_CMD(au8Cmd, u8Cmd, u32Addr);
        pstcW25qxxLL->Active();
        i32Ret = pstcW25qxxLL->Trans(au8Cmd, 4U);
        if (i32Ret == LL_OK) {
            i32Ret = pstcW25qxxLL->Receive(pu8Data, u32DataLen);
        }
        pstcW25qxxLL->Inactive();
    }

    return i32Ret;
}

/**
 * @brief  W25QXX Write enable.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 */
static int32_t W25QXX_WriteEnable(const stc_w25qxx_ll_t *pstcW25qxxLL)
{
    return W25QXX_WriteCmd(pstcW25qxxLL, W25QXX_WRITE_ENABLE, NULL, 0U);
}

/**
 * @brief  W25QXX Write disable.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 */
static int32_t W25QXX_WriteDisable(const stc_w25qxx_ll_t *pstcW25qxxLL)
{
    return W25QXX_WriteCmd(pstcW25qxxLL, W25QXX_WRITE_DISABLE, NULL, 0U);
}

/**
 * @brief  Wait for processing done.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          SPI timeout or W25QXX timeout.
 */
static int32_t W25QXX_WaitProcessDone(const stc_w25qxx_ll_t *pstcW25qxxLL)
{
    uint8_t u8Status;
    int32_t i32Ret = LL_ERR_TIMEOUT;
    volatile uint32_t u32Timecount = W25QXX_TIMEOUT;

    while (u32Timecount-- != 0UL) {
        i32Ret = W25QXX_ReadStatus(pstcW25qxxLL, W25QXX_READ_STATUS_REGISTER_1, &u8Status);
        if ((i32Ret == LL_OK) && ((u8Status & W25QXX_FLAG_BUSY) == 0U)) {
            break;
        }
    }

    return i32Ret;
}

/**
 * @}
 */

/**
 * @defgroup W25QXX_Global_Functions W25QXX Global Functions
 * @{
 */
/**
 * @brief  Initializes W25QXX.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter
 */
int32_t W25QXX_Init(const stc_w25qxx_ll_t *pstcW25qxxLL)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pstcW25qxxLL != NULL) && (pstcW25qxxLL->Init != NULL)) {
        pstcW25qxxLL->Init();
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize W25QXX.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter
 */
int32_t W25QXX_DeInit(const stc_w25qxx_ll_t *pstcW25qxxLL)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pstcW25qxxLL != NULL) && (pstcW25qxxLL->DeInit != NULL)) {
        pstcW25qxxLL->DeInit();
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Read manufacturer device ID.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [out] pu16ID                 Pointer to an address to store the device ID.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 */
int32_t W25QXX_GetManDeviceId(const stc_w25qxx_ll_t *pstcW25qxxLL, uint16_t *pu16ID)
{
    uint8_t au8TempId[2U];
    uint8_t au8Dummy[3U] = {0U};
    uint16_t u16ManID;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pstcW25qxxLL != NULL) && (pu16ID != NULL)) {
        i32Ret = W25QXX_ReadCmd(pstcW25qxxLL, W25QXX_MANUFACTURER_DEVICE_ID, au8Dummy, 3U, au8TempId, 2U);
        if (i32Ret == LL_OK) {
            u16ManID  = (uint16_t)au8TempId[0U] << 8U;
            u16ManID |= au8TempId[1U];
            *pu16ID   = u16ManID;
        }
    }

    return i32Ret;
}

/**
 * @brief  Read unique ID.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [out] pu8UniqueId            Pointer to a buffer the 64 bit unique ID to be stored.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 */
int32_t W25QXX_GetUniqueId(const stc_w25qxx_ll_t *pstcW25qxxLL, uint8_t *pu8UniqueId)
{
    uint8_t au8Dummy[4U] = {0U};
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pstcW25qxxLL != NULL) && (pu8UniqueId != NULL)) {
        i32Ret = W25QXX_ReadCmd(pstcW25qxxLL, W25QXX_READ_UNIQUE_ID, au8Dummy, 4U, pu8UniqueId, 8U);
    }

    return i32Ret;
}

/**
 * @brief  Read status register.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [in]  u8SrRdCmd              Command of reading status register.
 *   @arg  W25QXX_READ_STATUS_REGISTER_1: Read status register 1.
 *   @arg  W25QXX_READ_STATUS_REGISTER_2: Read status register 2.
 *   @arg  W25QXX_READ_STATUS_REGISTER_3: Read status register 3.
 * @param  [out] pu8Status              Pointer to an address the status value to be stored.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 */
int32_t W25QXX_ReadStatus(const stc_w25qxx_ll_t *pstcW25qxxLL, uint8_t u8SrRdCmd, uint8_t *pu8Status)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pstcW25qxxLL != NULL) && (pu8Status != NULL)) {
        i32Ret = W25QXX_ReadCmd(pstcW25qxxLL, u8SrRdCmd, NULL, 0U, pu8Status, 1U);
    }

    return i32Ret;
}

/**
 * @brief  Write status register.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [in]  u8SrWtCmd              Command of writting status register.
 *   @arg  W25QXX_WRITE_STATUS_REGISTER_1: Write status register 1.
 *   @arg  W25QXX_WRITE_STATUS_REGISTER_2: Write status register 2.
 *   @arg  W25QXX_WRITE_STATUS_REGISTER_3: Write status register 3.
 * @param  [in]  u8Value                8bit value of the specified status register.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 */
int32_t W25QXX_WriteStatus(const stc_w25qxx_ll_t *pstcW25qxxLL, uint8_t u8SrWtCmd, uint8_t u8Value)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcW25qxxLL != NULL) {
        i32Ret = W25QXX_WriteCmd(pstcW25qxxLL, u8SrWtCmd, &u8Value, 1U);
    }

    return i32Ret;
}

/**
 * @brief  Power down.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 */
int32_t W25QXX_PowerDown(const stc_w25qxx_ll_t *pstcW25qxxLL)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pstcW25qxxLL != NULL) && (pstcW25qxxLL->Delay != NULL)) {
        i32Ret = W25QXX_WriteCmd(pstcW25qxxLL, W25QXX_POWER_DOWN, NULL, 0U);
        if (i32Ret == LL_OK) {
            pstcW25qxxLL->Delay(1U);
        }
    }

    return i32Ret;
}

/**
 * @brief  Release power down.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 */
int32_t W25QXX_ReleasePowerDown(const stc_w25qxx_ll_t *pstcW25qxxLL)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pstcW25qxxLL != NULL) && (pstcW25qxxLL->Delay != NULL)) {
        i32Ret = W25QXX_WriteCmd(pstcW25qxxLL, W25QXX_RELEASE_POWER_DOWN_ID, NULL, 0U);
        if (i32Ret == LL_OK) {
            pstcW25qxxLL->Delay(1U);
        }
    }

    return i32Ret;
}

/**
 * @brief  Ease chip.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout or W25QXX timeout.
 */
int32_t W25QXX_EraseChip(const stc_w25qxx_ll_t *pstcW25qxxLL)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcW25qxxLL != NULL) {
        i32Ret = W25QXX_WriteEnable(pstcW25qxxLL);
        if (i32Ret == LL_OK) {
            i32Ret = W25QXX_WaitProcessDone(pstcW25qxxLL);
        }
        if (i32Ret == LL_OK) {
            i32Ret = W25QXX_WriteCmd(pstcW25qxxLL, W25QXX_CHIP_ERASE, NULL, 0U);
        }
        if (i32Ret == LL_OK) {
            i32Ret = W25QXX_WaitProcessDone(pstcW25qxxLL);
        }
    }

    return i32Ret;
}

/**
 * @brief  Ease sector.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [in]  u32Addr                Any address of the specified sector.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout or W25QXX timeout.
 */
int32_t W25QXX_EraseSector(const stc_w25qxx_ll_t *pstcW25qxxLL, uint32_t u32Addr)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcW25qxxLL != NULL) {
        i32Ret = W25QXX_WriteEnable(pstcW25qxxLL);
        if (i32Ret == LL_OK) {
            i32Ret = W25QXX_WaitProcessDone(pstcW25qxxLL);
        }
        if (i32Ret == LL_OK) {
            i32Ret = W25QXX_Wt(pstcW25qxxLL, W25QXX_SECTOR_ERASE, u32Addr, NULL, 0U);
        }
        if (i32Ret == LL_OK) {
            i32Ret = W25QXX_WaitProcessDone(pstcW25qxxLL);
        }
        if (i32Ret == LL_OK) {
            i32Ret = W25QXX_WriteDisable(pstcW25qxxLL);
        }
    }

    return i32Ret;
}

/**
 * @brief  W25QXX read data.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [in]  u32Addr                The start address of the data to be read.
 * @param  [in]  pu8ReadBuf             The pointer to the buffer contains the data to be stored.
 * @param  [in]  u32NumByteToRead       Buffer size in bytes.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout.
 */
int32_t W25QXX_ReadData(const stc_w25qxx_ll_t *pstcW25qxxLL, uint32_t u32Addr, \
                        uint8_t *pu8ReadBuf, uint32_t u32NumByteToRead)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pstcW25qxxLL != NULL) && (pu8ReadBuf != NULL) && (u32NumByteToRead != 0UL)) {
        i32Ret = W25QXX_Rd(pstcW25qxxLL, W25QXX_READ_DATA, u32Addr, pu8ReadBuf, u32NumByteToRead);
    }

    return i32Ret;
}

/**
 * @brief  W25QXX page program.
 * @param  [in]  pstcW25qxxLL           Pointer to a @ref stc_w25qxx_ll_t structure.
 * @param  [in]  u32Addr                Start address of the page.
 * @param  [in]  pu8Data                Pointer to a buffer that contains the data to be written.
 * @param  [in]  u32NumByteToProgram    Size of the buffer.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_ERR_TIMEOUT:          SPI timeout or W25QXX timeout.
 */
int32_t W25QXX_PageProgram(const stc_w25qxx_ll_t *pstcW25qxxLL, uint32_t u32Addr, \
                           const uint8_t *pu8Data, uint32_t u32NumByteToProgram)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pstcW25qxxLL != NULL) && (pu8Data != NULL) && (u32NumByteToProgram != 0UL)) {
        i32Ret = W25QXX_WriteEnable(pstcW25qxxLL);
        if (i32Ret == LL_OK) {
            i32Ret = W25QXX_Wt(pstcW25qxxLL, W25QXX_PAGE_PROGRAM, u32Addr, pu8Data, u32NumByteToProgram);
        }
        if (i32Ret == LL_OK) {
            i32Ret = W25QXX_WaitProcessDone(pstcW25qxxLL);
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
