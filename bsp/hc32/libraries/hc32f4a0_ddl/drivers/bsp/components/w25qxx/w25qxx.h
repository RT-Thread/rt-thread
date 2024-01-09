/**
 *******************************************************************************
 * @file  w25qxx.h
 * @brief This file provides firmware functions to W25QXX group spi flash.
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
#ifndef __W25QXX_H__
#define __W25QXX_H__

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
 * @addtogroup W25QXX
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief W25QXX low layer structure definition
 */
typedef struct {
    void (*Delay)(uint32_t);
    void (*Init)(void);
    void (*DeInit)(void);
    void (*Active)(void);
    void (*Inactive)(void);
    int32_t (*Trans)(const uint8_t *, uint32_t);
    int32_t (*Receive)(uint8_t *, uint32_t);
} stc_w25qxx_ll_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup W25QXX_Global_Macros W25QXX Global Macros
 * @{
 */

/**
 * @defgroup W25QXX_ID W25QXX ID
 * @{
 */
#define W25Q80                  (0xEF13U)
#define W25Q16                  (0xEF14U)
#define W25Q32                  (0xEF15U)
#define W25Q64                  (0xEF16U)
#define W25Q128                 (0xEF17U)
/**
 * @}
 */

/**
 * @defgroup W25QXX_Command W25QXX Command
 * @{
 */
#define W25QXX_WRITE_ENABLE                     (0x06U)
#define W25QXX_VOLATILE_SR_WRITE_ENABLE         (0x50U)
#define W25QXX_WRITE_DISABLE                    (0x04U)
#define W25QXX_RELEASE_POWER_DOWN_ID            (0xABU)
#define W25QXX_MANUFACTURER_DEVICE_ID           (0x90U)
#define W25QXX_JEDEC_ID                         (0x9FU)
#define W25QXX_READ_UNIQUE_ID                   (0x4BU)
#define W25QXX_READ_DATA                        (0x03U)
#define W25QXX_FAST_READ                        (0x0BU)
#define W25QXX_PAGE_PROGRAM                     (0x02U)
#define W25QXX_SECTOR_ERASE                     (0x20U)
#define W25QXX_BLOCK_ERASE_32KB                 (0x52U)
#define W25QXX_BLOCK_ERASE_64KB                 (0xD8U)
#define W25QXX_CHIP_ERASE                       (0xC7U)
#define W25QXX_READ_STATUS_REGISTER_1           (0x05U)
#define W25QXX_WRITE_STATUS_REGISTER_1          (0x01U)
#define W25QXX_READ_STATUS_REGISTER_2           (0x35U)
#define W25QXX_WRITE_STATUS_REGISTER_2          (0x31U)
#define W25QXX_READ_STATUS_REGISTER_3           (0x15U)
#define W25QXX_WRITE_STATUS_REGISTER_3          (0x11U)
#define W25QXX_READ_SFDP_REGISTER               (0x5AU)
#define W25QXX_ERASE_SECURITY_REGISTER          (0x44U)
#define W25QXX_PROGRAM_SECURITY_REGISTER        (0x42U)
#define W25QXX_READ_SECURITY_REGISTER           (0x48U)
#define W25QXX_GLOBAL_BLOCK_LOCK                (0x7EU)
#define W25QXX_GLOBAL_BLOCK_UNLOCK              (0x98U)
#define W25QXX_READ_BLOCK_LOCK                  (0x3DU)
#define W25QXX_INDIVIDUAL_BLOCK_LOCK            (0x36U)
#define W25QXX_INDIVIDUAL_BLOCK_UNLOCK          (0x39U)
#define W25QXX_ERASE_PROGRAM_SUSPEND            (0x75U)
#define W25QXX_ERASE_PROGRAM_RESUME             (0x7AU)
#define W25QXX_POWER_DOWN                       (0xB9U)
#define W25QXX_ENABLE_RESET                     (0x66U)
#define W25QXX_RESET_DEVICE                     (0x99U)
/**
 * @}
 */

/**
 * @defgroup W25QXX_Timeout_Value W25QXX Timeout Value
 * @{
 */
#define W25QXX_TIMEOUT                          (100000UL)
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
 * @addtogroup W25QXX_Global_Functions W25QXX Global Functions
 * @{
 */

int32_t W25QXX_Init(const stc_w25qxx_ll_t *pstcW25qxxLL);
int32_t W25QXX_DeInit(const stc_w25qxx_ll_t *pstcW25qxxLL);
int32_t W25QXX_GetManDeviceId(const stc_w25qxx_ll_t *pstcW25qxxLL, uint16_t *pu16ID);
int32_t W25QXX_GetUniqueId(const stc_w25qxx_ll_t *pstcW25qxxLL, uint8_t *pu8UniqueId);
int32_t W25QXX_ReadStatus(const stc_w25qxx_ll_t *pstcW25qxxLL, uint8_t u8SrRdCmd, uint8_t *pu8Status);
int32_t W25QXX_WriteStatus(const stc_w25qxx_ll_t *pstcW25qxxLL, uint8_t u8SrWtCmd, uint8_t u8Value);
int32_t W25QXX_PowerDown(const stc_w25qxx_ll_t *pstcW25qxxLL);
int32_t W25QXX_ReleasePowerDown(const stc_w25qxx_ll_t *pstcW25qxxLL);
int32_t W25QXX_EraseChip(const stc_w25qxx_ll_t *pstcW25qxxLL);
int32_t W25QXX_EraseSector(const stc_w25qxx_ll_t *pstcW25qxxLL, uint32_t u32Addr);
int32_t W25QXX_ReadData(const stc_w25qxx_ll_t *pstcW25qxxLL, uint32_t u32Addr, uint8_t *pu8ReadBuf, uint32_t u32NumByteToRead);
int32_t W25QXX_PageProgram(const stc_w25qxx_ll_t *pstcW25qxxLL, uint32_t u32Addr, const uint8_t *pu8Data, uint32_t u32NumByteToProgram);

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

#endif /* __W25QXX_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
