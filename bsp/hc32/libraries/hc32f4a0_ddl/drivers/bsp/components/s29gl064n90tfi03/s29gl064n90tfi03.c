/**
 *******************************************************************************
 * @file  s29gl064n90tfi03.c
 * @brief This midware file provides firmware functions to manage the NOR Flash
 *        component library for s29gl064n90tfi03.
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
#include <string.h>
#include "s29gl064n90tfi03.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup Components
 * @{
 */

/**
 * @defgroup S29GL064N90TFI03 NOR Flash S29GL064N90TFI03
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup S29GL064N90TFI03_Local_Macros S29GL064N90TFI03 Local Macros
 * @{
 */

/**
 * @defgroup EXMC_SMC_Check_Parameters_Validity EXMC_SMC Check Parameters Validity
 * @{
 */
#define IS_NOR_MEMORY_WIDTH(x)                                                 \
(   ((x) == NOR_MEMORY_WIDTH_16BIT)             ||                             \
    ((x) == NOR_MEMORY_WIDTH_32BIT))
/**
 * @}
 */

/**
 * @defgroup Norflash_Device_Command Norflash Device Command
 * @{
 */
/* Constants to define address to set to write a command */
#define NOR_CMD_ADDR_FIRST                      (0x0555U)
#define NOR_CMD_ADDR_FIRST_CFI                  (0x0055U)
#define NOR_CMD_ADDR_SECOND                     (0x02AAU)
#define NOR_CMD_ADDR_THIRD                      (0x0555U)
#define NOR_CMD_ADDR_FOURTH                     (0x0555U)
#define NOR_CMD_ADDR_FIFTH                      (0x02AAU)
#define NOR_CMD_ADDR_SIXTH                      (0x0555U)

/* Constants to define data to program a command */
#define NOR_CMD_DATA_READ_RESET                 (0x00F0U)
#define NOR_CMD_DATA_FIRST                      (0x00AAU)
#define NOR_CMD_DATA_SECOND                     (0x0055U)
#define NOR_CMD_DATA_AUTO_SELECT                (0x0090U)
#define NOR_CMD_DATA_PROGRAM                    (0x00A0U)
#define NOR_CMD_DATA_CHIP_BLOCK_ERASE_THIRD     (0x0080U)
#define NOR_CMD_DATA_CHIP_BLOCK_ERASE_FOURTH    (0x00AAU)
#define NOR_CMD_DATA_CHIP_BLOCK_ERASE_FIFTH     (0x0055U)
#define NOR_CMD_DATA_CHIP_ERASE                 (0x0010U)
#define NOR_CMD_DATA_CFI                        (0x0098U)

#define NOR_CMD_DATA_BLOCK_ERASE                (0x30U)

#define NOR_CMD_DATA_WRITE_TO_BUF_PGM           (0x25U)
#define NOR_CMD_DATA_WRITE_TO_BUF_PGM_CONFIRM   (0x29U)

/* Mask on NOR Flash status register */
#define NOR_MASK_STATUS_DQ5                     (0x0020U)
#define NOR_MASK_STATUS_DQ6                     (0x0040U)

/* NOR Flash device IDs addresses */
#define DEVICE_MANUFACTURER_ID_ADDR             (0x0000U)
#define DEVICE_ID1_ADDR                         (0x0001U)
#define DEVICE_ID2_ADDR                         (0x000EU)
#define DEVICE_ID3_ADDR                         (0x000FU)

/* NOR Flash CFI IDs addresses */
#define DEVICE_CFI1_ADDR                        (0x0061U)
#define DEVICE_CFI2_ADDR                        (0x0062U)
#define DEVICE_CFI3_ADDR                        (0x0063U)
#define DEVICE_CFI4_ADDR                        (0x0064U)
/**
 * @}
 */

/**
 * @brief  SMC device memory address shifting.
 * @param  [in] mem_base_addr          Memory base address
 * @param  [in] mem_width              Memory width
 * @param  [in] addr                   Memory address
 * @retval SMC device shifted address value
 */
#define NOR_ADDR_SHIFT(mem_base_addr, mem_width, addr)                  \
(    ((NOR_MEMORY_WIDTH_16BIT == (mem_width))? (((mem_base_addr) + ((addr) << 1UL))):\
                                (((mem_base_addr) + ((addr) << 2UL)))))

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
 * @defgroup S29GL064N90TFI03_Global_Functions S29GL064N90TFI03 Global Functions
 * @{
 */

/**
 * @brief  Reset the NOR memory to Read mode
 * @param  [in] u32MemoryBaseAddr       S29GL064 base address
 * @retval None
 */
void S29GL064_Reset(uint32_t u32MemoryBaseAddr)
{
    RW_MEM16(u32MemoryBaseAddr) = NOR_CMD_DATA_READ_RESET;
}

/**
 * @brief  Returns the NOR operation status
 * @param  [in] u32MemoryBaseAddr       S29GL064 base address
 * @param  [in] u32Timeout:             Timeout duration
 * @retval int32_t:
 *           - LL_OK:                   NOR flash status is normal.
 *           - LL_ERR:                  NOR flash status is abnormal.
 *           - LL_ERR_BUSY:             NOR flash status is busy.
 *           - LL_ERR_TIMEOUT:          Get NOR flash status timeout.
 */
int32_t S29GL064_GetStatus(uint32_t u32MemoryBaseAddr, uint32_t u32Timeout)
{
    uint16_t u16TmpStatus1;
    uint16_t u16TmpStatus2;
    uint32_t u32To = 0U;
    int32_t i32Ret = LL_ERR_BUSY;

    while (i32Ret == LL_ERR_BUSY) {
        /* Read NOR status register (DQ6 and DQ5) */
        u16TmpStatus1 = RW_MEM16(u32MemoryBaseAddr);
        u16TmpStatus2 = RW_MEM16(u32MemoryBaseAddr);

        /* If DQ6 did not toggle between the two reads then return Ok  */
        if ((u16TmpStatus1 & NOR_MASK_STATUS_DQ6) == (u16TmpStatus2 & NOR_MASK_STATUS_DQ6)) {
            i32Ret = LL_OK;
        } else {
            if ((u16TmpStatus1 & NOR_MASK_STATUS_DQ5) == NOR_MASK_STATUS_DQ5) {
                i32Ret = LL_ERR_BUSY;
            }

            u16TmpStatus1 = RW_MEM16(u32MemoryBaseAddr);
            u16TmpStatus2 = RW_MEM16(u32MemoryBaseAddr);

            /* If DQ6 did not toggle between the two reads then return Ok */
            if ((u16TmpStatus1 & NOR_MASK_STATUS_DQ6) == (u16TmpStatus2 & NOR_MASK_STATUS_DQ6)) {
                i32Ret = LL_OK;
            } else if ((u16TmpStatus1 & NOR_MASK_STATUS_DQ5) == NOR_MASK_STATUS_DQ5) {
                i32Ret = LL_ERR;
            } else { /* Do nothing */
            }
        }

        /* Check for the Timeout */
        if (u32To++ > u32Timeout) {
            i32Ret = LL_ERR_TIMEOUT;
        }
    }

    return i32Ret;
}

/**
 * @brief  Read NOR flash IDs
 * @param  [in] u32MemoryBaseAddr       S29GL064 base address
 * @param  [in] u32MemoryWidth          Memory width
 * @param  [out] au16Id                 ID buffer
 * @param  [in] u32Len                  Number ID to read
 * @retval int32_t:
 *           - LL_OK:                   Read successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer au16Id value is NULL or u32Len value is 0.
 */
int32_t S29GL064_ReadId(uint32_t u32MemoryBaseAddr, uint32_t u32MemoryWidth, uint16_t au16Id[], uint32_t u32Len)
{
    uint32_t u32TmpLen;
    uint16_t au16TmpId[4];
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != au16Id) && (u32Len > 0UL)) {
        DDL_ASSERT(IS_NOR_MEMORY_WIDTH(u32MemoryWidth));

        /* Send read ID command */
        RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FIRST)) = NOR_CMD_DATA_FIRST;
        RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_SECOND)) = NOR_CMD_DATA_SECOND;
        RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_THIRD)) = NOR_CMD_DATA_AUTO_SELECT;

        /* Read the NOR IDs */
        au16TmpId[0] = RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, DEVICE_MANUFACTURER_ID_ADDR));
        au16TmpId[1] = RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, DEVICE_ID1_ADDR));
        au16TmpId[2] = RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, DEVICE_ID2_ADDR));
        au16TmpId[3] = RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, DEVICE_ID3_ADDR));

        u32TmpLen = (u32Len < 4UL) ? u32Len : 4UL;
        (void)memcpy(au16Id, au16TmpId, (u32TmpLen << 1UL));

        RW_MEM16(u32MemoryBaseAddr) = NOR_CMD_DATA_READ_RESET;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Read NOR flash CFI IDs
 * @param  [in] u32MemoryBaseAddr       S29GL064 base address
 * @param  [in] u32MemoryWidth          Memory width
 * @param  [out] au16Id                 ID buffer
 * @param  [in] u32Len                  Number ID to read
 * @retval int32_t:
 *           - LL_OK:                   Read successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer au16Id value is NULL or u32Len value is 0.
 */
int32_t S29GL064_ReadCfiId(uint32_t u32MemoryBaseAddr, uint32_t u32MemoryWidth, uint16_t au16Id[], uint32_t u32Len)
{
    uint32_t u32TmpLen;
    uint16_t au16TmpId[4];
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != au16Id) && (u32Len > 0UL)) {
        DDL_ASSERT(IS_NOR_MEMORY_WIDTH(u32MemoryWidth));

        /* Send read CFI query command */
        RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FIRST_CFI)) = NOR_CMD_DATA_CFI;

        /* read the NOR CFI information */
        au16TmpId[0] = RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, DEVICE_CFI1_ADDR));
        au16TmpId[1] = RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, DEVICE_CFI2_ADDR));
        au16TmpId[2] = RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, DEVICE_CFI3_ADDR));
        au16TmpId[3] = RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, DEVICE_CFI4_ADDR));

        u32TmpLen = (u32Len < 4UL) ? u32Len : 4UL;
        (void)memcpy(au16Id, au16TmpId, (u32TmpLen << 1U));

        RW_MEM16(u32MemoryBaseAddr) = NOR_CMD_DATA_READ_RESET;
        i32Ret = LL_OK;
    }

    return i32Ret;
}


/**
 * @brief  Erase the entire NOR chip.
 * @param  [in] u32MemoryBaseAddr       S29GL064 base address
 * @param  [in] u32MemoryWidth          Memory width
 * @retval None
 */
void S29GL064_EraseChip(uint32_t u32MemoryBaseAddr, uint32_t u32MemoryWidth)
{
    DDL_ASSERT(IS_NOR_MEMORY_WIDTH(u32MemoryWidth));

    /* Send NOR chip erase command sequence */
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FIRST)) = NOR_CMD_DATA_FIRST;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_SECOND)) = NOR_CMD_DATA_SECOND;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_THIRD)) = NOR_CMD_DATA_CHIP_BLOCK_ERASE_THIRD;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FOURTH)) = NOR_CMD_DATA_CHIP_BLOCK_ERASE_FOURTH;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FIFTH)) = NOR_CMD_DATA_CHIP_BLOCK_ERASE_FIFTH;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_SIXTH)) = NOR_CMD_DATA_CHIP_ERASE;
}

/**
 * @brief  Erase the specified block of the NOR memory
 * @param  [in] u32MemoryBaseAddr       S29GL064 base address
 * @param  [in] u32MemoryWidth          Memory width
 * @param  [in] u32SectorAddr           Sector address
 * @retval None
 */
void S29GL064_EraseSector(uint32_t u32MemoryBaseAddr, uint32_t u32MemoryWidth, uint32_t u32SectorAddr)
{
    DDL_ASSERT(IS_NOR_MEMORY_WIDTH(u32MemoryWidth));

    /* Send block erase command sequence */
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FIRST)) = NOR_CMD_DATA_FIRST;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_SECOND)) = NOR_CMD_DATA_SECOND;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_THIRD)) = NOR_CMD_DATA_CHIP_BLOCK_ERASE_THIRD;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FOURTH)) = NOR_CMD_DATA_CHIP_BLOCK_ERASE_FOURTH;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FIFTH)) = NOR_CMD_DATA_CHIP_BLOCK_ERASE_FIFTH;

    RW_MEM16(u32SectorAddr) = NOR_CMD_DATA_BLOCK_ERASE;
}

/**
 * @brief  Read memory for half-word.
 * @param  [in] u32ReadAddr          Memory address to read
 * @retval Data of the specified address
 */
uint16_t S29GL064_Read(uint32_t u32ReadAddr)
{
    return RW_MEM16(u32ReadAddr);
}

/**
 * @brief  Read memory for half-word.
 * @param  [in] u32ReadAddr             Memory address to read
 * @param  [out] au16Data               Data buffer for reading
 * @param  [in] u32NumHalfwords         Number half-word to write
 * @retval int32_t:
 *           - LL_OK:                   Read successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer au16Data value is NULL or u32NumHalfwords value is 0.
 */
int32_t S29GL064_ReadBuffer(uint32_t u32ReadAddr, uint16_t au16Data[], uint32_t u32NumHalfwords)
{
    uint32_t i;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((au16Data != NULL) && (u32NumHalfwords > 0UL)) {
        for (i = 0UL; i < u32NumHalfwords; i++) {
            au16Data[i] = RW_MEM16(u32ReadAddr);
            u32ReadAddr += 2UL;
        }
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Write memory for half-word.
 * @param  [in] u32MemoryBaseAddr       S29GL064 base address
 * @param  [in] u32MemoryWidth          Memory width
 * @param  [in] u32ProgramAddr          Memory address to write
 * @param  [in] u16Data                 Data to write
 * @retval None
 */
void S29GL064_Program(uint32_t u32MemoryBaseAddr, uint32_t u32MemoryWidth, uint32_t u32ProgramAddr, uint16_t u16Data)
{
    DDL_ASSERT(IS_NOR_MEMORY_WIDTH(u32MemoryWidth));

    /* Send program data command */
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FIRST)) = NOR_CMD_DATA_FIRST;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_SECOND)) = NOR_CMD_DATA_SECOND;
    RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_THIRD)) = NOR_CMD_DATA_PROGRAM;

    /* Write the data */
    RW_MEM16(u32ProgramAddr) = u16Data;
}

/**
 * @brief  Write memory(using Program Buffer to Flash command) for half-word.
 * @param  [in] u32MemoryBaseAddr       S29GL064 base address
 * @param  [in] u32MemoryWidth          Memory width
 * @param  [in] u32ProgramAddr          Memory address to write
 * @param  [in] au16Data                Data buffer to write
 * @param  [in] u32NumHalfwords         Number half-word to write
 * @retval int32_t:
 *           - LL_OK:                   Program successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer au16Data value is NULL or u32NumHalfwords value is 0.
 */
int32_t S29GL064_ProgramBuffer(uint32_t u32MemoryBaseAddr,
                               uint32_t u32MemoryWidth,
                               uint32_t u32ProgramAddr,
                               const uint16_t au16Data[],
                               uint32_t u32NumHalfwords)
{
    uint32_t i;
    uint32_t u32CurAddr;
    uint32_t u32EndAddr;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((NULL != au16Data) && (u32NumHalfwords > 0UL)) {
        DDL_ASSERT(IS_NOR_MEMORY_WIDTH(u32MemoryWidth));
        DDL_ASSERT(IS_ADDR_ALIGN(u32ProgramAddr, 16UL));

        u32EndAddr = u32ProgramAddr + (u32NumHalfwords << 1UL) - 1UL;

        /* Issue unlock command sequence */
        RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_FIRST)) = NOR_CMD_DATA_FIRST;
        RW_MEM16(NOR_ADDR_SHIFT(u32MemoryBaseAddr, u32MemoryWidth, NOR_CMD_ADDR_SECOND)) = NOR_CMD_DATA_SECOND;

        /* Write Buffer Load Command */
        RW_MEM16(u32ProgramAddr) =  NOR_CMD_DATA_WRITE_TO_BUF_PGM;
        RW_MEM16(u32ProgramAddr) = (uint16_t)(u32NumHalfwords - 1UL);

        /* Load Data into NOR Buffer */
        i = 0UL;
        for (u32CurAddr = u32ProgramAddr; u32CurAddr <= u32EndAddr; u32CurAddr += 2UL) {
            RW_MEM16(u32CurAddr) = au16Data[i++];
        }

        RW_MEM16(u32ProgramAddr) = NOR_CMD_DATA_WRITE_TO_BUF_PGM_CONFIRM;
        i32Ret = LL_OK;
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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
