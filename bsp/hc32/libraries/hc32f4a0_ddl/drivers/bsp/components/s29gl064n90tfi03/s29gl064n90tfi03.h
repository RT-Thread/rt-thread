/**
 *******************************************************************************
 * @file  s29gl064n90tfi03.h
 * @brief This file contains all the functions prototypes of the NOR Flash
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
#ifndef __S29GL064N90TFI03_H__
#define __S29GL064N90TFI03_H__

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
 * @addtogroup S29GL064N90TFI03
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup S29GL064N90TFI03_Global_Macros S29GL064N90TFI03 Global Macros
 * @{
 */

/**
 * @defgroup S29GL064N90TFI03_ID_Information S29GL064N90TFI03 ID Information
 * @{
 */
#define S29GL064_MANUFACTURER_ID        (0x0001U)
#define S29GL064_DEVICE_ID1             (0x227EU)
#define S29GL064_DEVICE_ID2             (0x2210U)
#define S29GL064_DEVICE_ID3             (0x2201U)
/**
 * @}
 */

/**
 * @defgroup S29GL064N90TFI03_Memory_Size S29GL064N90TFI03 Memory Size
 * @{
 */
#define S29GL064_DEVICE_SECTORS         (128UL)
#define S29GL064_BYTES_PER_SECTOR       (64UL * 1024UL)
#define S29GL064_SIZE                   (S29GL064_DEVICE_SECTORS * S29GL064_BYTES_PER_SECTOR) /* 8MBytes*/

#define S29GL064_BYTES_PER_BUF_PGM      (32UL)
/**
 * @}
 */

/**
 * @defgroup NOR_Flash_Memory_Width NOR Flash Memory Width
 * @{
 */
#define NOR_MEMORY_WIDTH_16BIT          (0UL)
#define NOR_MEMORY_WIDTH_32BIT          (1UL)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup S29GL064N90TFI03_Global_Functions S29GL064N90TFI03 Global Functions
 * @{
 */
void S29GL064_Reset(uint32_t u32MemoryBaseAddr);
int32_t S29GL064_GetStatus(uint32_t u32MemoryBaseAddr, uint32_t u32Timeout);
int32_t S29GL064_ReadId(uint32_t u32MemoryBaseAddr, uint32_t u32MemoryWidth, uint16_t au16Id[], uint32_t u32Len);
int32_t S29GL064_ReadCfiId(uint32_t u32MemoryBaseAddr,
                           uint32_t u32MemoryWidth,
                           uint16_t au16Id[],
                           uint32_t u32Len);
void S29GL064_EraseChip(uint32_t u32MemoryBaseAddr, uint32_t u32MemoryWidth);
void S29GL064_EraseSector(uint32_t u32MemoryBaseAddr, uint32_t u32MemoryWidth, uint32_t u32SectorAddr);
uint16_t S29GL064_Read(uint32_t u32ReadAddr);
int32_t S29GL064_ReadBuffer(uint32_t u32ReadAddr, uint16_t au16Data[], uint32_t u32NumHalfwords);
void S29GL064_Program(uint32_t u32MemoryBaseAddr, uint32_t u32MemoryWidth, uint32_t u32ProgramAddr, uint16_t u16Data);
int32_t S29GL064_ProgramBuffer(uint32_t u32MemoryBaseAddr,
                               uint32_t u32MemoryWidth,
                               uint32_t u32ProgramAddr,
                               const uint16_t au16Data[],
                               uint32_t u32NumHalfwords);
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

#endif /* __S29GL064N90TFI03_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
