/**
 *******************************************************************************
 * @file  hc32_ll_efm.h
 * @brief This file contains all the functions prototypes of the EFM driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-12-15       CDT             Rename EFM_DataCacheResetCmd() as EFM_CacheRamReset() and modify comment
                                    Optimized macro group EFM_Remap_Size definitions
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
#ifndef __HC32_LL_EFM_H__
#define __HC32_LL_EFM_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_EFM
 * @{
 */

#if (LL_EFM_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Types EFM Global Types
 * @{
 */
/**
 * @brief EFM unique ID definition
 */
typedef struct {
    uint32_t            u32UniqueID0;      /*!< unique ID 0.       */
    uint32_t            u32UniqueID1;      /*!< unique ID 1.       */
    uint32_t            u32UniqueID2;      /*!< unique ID 2.       */
} stc_efm_unique_id_t;

typedef struct {
    uint32_t u32State;
    uint32_t u32Addr;
    uint32_t u32Size;
} stc_efm_remap_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EFM_Global_Macros EFM Global Macros
 * @{
 */
/**
 * @defgroup EFM_Address EFM Address Area
 * @{
 */
#define EFM_START_ADDR                  (0x00000000UL)    /*!< Flash start address */

#define EFM_END_ADDR                    (0x0007FFFFUL)    /*!< Flash end address */
#define EFM_FLASH_1_START_ADDR          (0x00040000UL)
#define EFM_OTP_START_ADDR1             (0x00000000UL)    /*!< OTP start address */
#define EFM_OTP_END_ADDR1               (0x0001FFFFUL)
#define EFM_OTP_START_ADDR              (0x03000000UL)
#define EFM_OTP_END_ADDR                (0x030017FFUL)    /*!< OTP end address */
#define EFM_OTP_LOCK_ADDR_START         (0x03001800UL)    /*!< OTP lock address */
#define EFM_OTP_LOCK_ADDR_END           (0x03001AD7UL)    /*!< OTP lock address */
#define EFM_OTP_ENABLE_ADDR             (0x03001AD8UL)    /*!< OTP Enable address */
#define EFM_SECURITY_START_ADDR         (0x03004000UL)    /*!< Flash security start address */
#define EFM_SECURITY_END_ADDR           (0x0300400BUL)    /*!< Flash security end address */

/**
 * @}
 */

/**
 * @defgroup EFM_Chip_Sel EFM Chip Selection
 * @{
 */
#define EFM_CHIP0                       (EFM_FSTP_F0STP)
#define EFM_CHIP1                       (EFM_FSTP_F1STP)
#define EFM_CHIP_ALL                    (EFM_FSTP_F0STP | EFM_FSTP_F1STP)

/**
 * @}
 */

/**
 * @defgroup EFM_Bus_Status EFM Bus Status
 * @{
 */
#define EFM_BUS_HOLD                    (0x0UL)     /*!< Bus busy while flash program or erase */
#define EFM_BUS_RELEASE                 (0x1UL)     /*!< Bus release while flash program or erase */
/**
 * @}
 */

/**
 * @defgroup EFM_Wait_Cycle EFM Wait Cycle
 * @{
 */

#define EFM_WAIT_CYCLE0                 (0U << EFM_FRMC_FLWT_POS)      /*!< Don't insert read wait cycle */
#define EFM_WAIT_CYCLE1                 (1U << EFM_FRMC_FLWT_POS)      /*!< Insert 1 read wait cycle     */

#define EFM_WAIT_CYCLE2                 (2U << EFM_FRMC_FLWT_POS)      /*!< Insert 2 read wait cycles    */
#define EFM_WAIT_CYCLE3                 (3U << EFM_FRMC_FLWT_POS)      /*!< Insert 3 read wait cycles    */
#define EFM_WAIT_CYCLE4                 (4U << EFM_FRMC_FLWT_POS)      /*!< Insert 4 read wait cycles    */
#define EFM_WAIT_CYCLE5                 (5U << EFM_FRMC_FLWT_POS)      /*!< Insert 5 read wait cycles    */
#define EFM_WAIT_CYCLE6                 (6U << EFM_FRMC_FLWT_POS)      /*!< Insert 6 read wait cycles    */
#define EFM_WAIT_CYCLE7                 (7U << EFM_FRMC_FLWT_POS)      /*!< Insert 7 read wait cycles    */
#define EFM_WAIT_CYCLE8                 (8U << EFM_FRMC_FLWT_POS)      /*!< Insert 8 read wait cycles    */
#define EFM_WAIT_CYCLE9                 (9U << EFM_FRMC_FLWT_POS)      /*!< Insert 9 read wait cycles    */
#define EFM_WAIT_CYCLE10                (10U << EFM_FRMC_FLWT_POS)     /*!< Insert 10 read wait cycles   */
#define EFM_WAIT_CYCLE11                (11U << EFM_FRMC_FLWT_POS)     /*!< Insert 11 read wait cycles   */
#define EFM_WAIT_CYCLE12                (12U << EFM_FRMC_FLWT_POS)     /*!< Insert 12 read wait cycles   */
#define EFM_WAIT_CYCLE13                (13U << EFM_FRMC_FLWT_POS)     /*!< Insert 13 read wait cycles   */
#define EFM_WAIT_CYCLE14                (14U << EFM_FRMC_FLWT_POS)     /*!< Insert 14 read wait cycles   */
#define EFM_WAIT_CYCLE15                (15U << EFM_FRMC_FLWT_POS)     /*!< Insert 15 read wait cycles   */
/**
 * @}
 */

/**
 * @defgroup EFM_Swap_Address EFM Swap Address
 * @{
 */
#define EFM_SWAP_ADDR                   (0x03002000UL)
#define EFM_SWAP_DATA                   (0x005A5A5AUL)
/**
 * @}
 */

/**
 * @defgroup EFM_WriteLock_Sel EFM Write Protect Lock Selection
 * @{
 */
#define EFM_WRLOCK0                     (EFM_WLOCK_WLOCK0)     /*!< F0NWPRT controlled sector lock   */
#define EFM_WRLOCK1                     (EFM_WLOCK_WLOCK1)     /*!< F1NWPRT controlled sector lock   */
/**
 * @}
 */

/**
 * @defgroup EFM_OperateMode_Sel EFM Operate Mode Selection
 * @{
 */
#define EFM_MD_READONLY                 (0x0UL << EFM_FWMC_PEMOD_POS)   /*!< Read only mode               */
#define EFM_MD_PGM_SINGLE               (0x1UL << EFM_FWMC_PEMOD_POS)   /*!< Program single mode          */
#define EFM_MD_PGM_READBACK             (0x2UL << EFM_FWMC_PEMOD_POS)   /*!< Program and read back mode   */
#define EFM_MD_PGM_SEQ                  (0x3UL << EFM_FWMC_PEMOD_POS)   /*!< Program sequence mode        */
#define EFM_MD_ERASE_SECTOR             (0x4UL << EFM_FWMC_PEMOD_POS)   /*!< Sector erase mode            */

#define EFM_MD_ERASE_ONE_CHIP           (0x5UL << EFM_FWMC_PEMOD_POS)   /*!< A flash Chip erase mode      */
#define EFM_MD_ERASE_ALL_CHIP           (0x6UL << EFM_FWMC_PEMOD_POS)   /*!< All chip erase mode    */

/**
 * @}
 */

/**
 * @defgroup EFM_Flag_Sel  EFM Flag Selection
 * @{
 */
#define EFM_FLAG_OTPWERR                (EFM_FSR_OTPWERR0)      /*!< EFM Flash0 otp Programming/erase error flag.       */
#define EFM_FLAG_PEPRTERR               (EFM_FSR_PRTWERR0)      /*!< EFM Flash0 write protect address error flag.       */
#define EFM_FLAG_PGSZERR                (EFM_FSR_PGSZERR0)      /*!< EFM Flash0 programming size error flag.            */
#define EFM_FLAG_PGMISMTCH              (EFM_FSR_MISMTCH0)      /*!< EFM Flash0 programming missing match error flag.   */
#define EFM_FLAG_OPTEND                 (EFM_FSR_OPTEND0)       /*!< EFM Flash0 end of operation flag.                  */
#define EFM_FLAG_COLERR                 (EFM_FSR_COLERR0)       /*!< EFM Flash0 read collide error flag.                */
#define EFM_FLAG_RDY                    (EFM_FSR_RDY0)          /*!< EFM Flash0 ready flag.                             */
#define EFM_FLAG_PEPRTERR1              (EFM_FSR_PRTWERR1)      /*!< EFM Flash1 write protect address error flag.       */
#define EFM_FLAG_PGSZERR1               (EFM_FSR_PGSZERR1)      /*!< EFM Flash1 programming size error flag.            */
#define EFM_FLAG_PGMISMTCH1             (EFM_FSR_MISMTCH1)      /*!< EFM Flash1 programming missing match error flag.   */
#define EFM_FLAG_OPTEND1                (EFM_FSR_OPTEND1)       /*!< EFM Flash1 end of operation flag.                  */
#define EFM_FLAG_COLERR1                (EFM_FSR_COLERR1)       /*!< EFM Flash1 read collide error flag.                */
#define EFM_FLAG_RDY1                   (EFM_FSR_RDY1)          /*!< EFM Flash1 ready flag.                             */

#define EFM_FLAG_ALL                (EFM_FLAG_OTPWERR | EFM_FLAG_PEPRTERR | EFM_FLAG_PGSZERR   | EFM_FLAG_PGMISMTCH  | \
                                     EFM_FLAG_OPTEND  | EFM_FLAG_COLERR   | EFM_FLAG_PEPRTERR1 | EFM_FLAG_PGSZERR1   | \
                                     EFM_FLAG_OPTEND1 | EFM_FLAG_COLERR1  | EFM_FLAG_RDY       | EFM_FLAG_PGMISMTCH1 | \
                                     EFM_FLAG_RDY1)

/**
 * @}
 */

/**
 * @defgroup EFM_Interrupt_Sel EFM Interrupt Selection
 * @{
 */
#define EFM_INT_PEERR                   (EFM_FITE_PEERRITE)     /*!< Program/erase error Interrupt source    */
#define EFM_INT_OPTEND                  (EFM_FITE_OPTENDITE)    /*!< End of EFM operation Interrupt source   */
#define EFM_INT_COLERR                  (EFM_FITE_COLERRITE)    /*!< Read collide error Interrupt source     */

#define EFM_INT_ALL                     (EFM_FITE_PEERRITE | EFM_FITE_OPTENDITE | EFM_FITE_COLERRITE)
/**
 * @}
 */

/**
 * @defgroup EFM_Keys EFM Keys
 * @{
 */
#define EFM_REG_UNLOCK_KEY1             (0x0123UL)
#define EFM_REG_UNLOCK_KEY2             (0x3210UL)
#define EFM_REG_LOCK_KEY                (0x0000UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Sector_Size EFM Sector Size
 * @{
 */
#define SECTOR_SIZE                     (0x2000UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Sector_Address EFM Sector Address
 * @{
 */
#define EFM_SECTOR_ADDR(x)          (uint32_t)(SECTOR_SIZE * (x))
/**
 * @}
 */

/**
 * @defgroup EFM_OTP_Base_Address EFM Otp Base Address
 * @{
 */
#define EFM_OTP_BASE1_ADDR          (0x00000000UL)
#define EFM_OTP_BASE1_SIZE          (0x2000UL)
#define EFM_OTP_BASE1_OFFSET        (0UL)
#define EFM_OTP_BASE2_ADDR          (0x03000000UL)
#define EFM_OTP_BASE2_SIZE          (0x800UL)
#define EFM_OTP_BASE2_OFFSET        (16UL)
#define EFM_OTP_BASE3_ADDR          (0x03001000UL)
#define EFM_OTP_BASE3_SIZE          (0x100UL)
#define EFM_OTP_BASE3_OFFSET        (18UL)
#define EFM_OTP_BASE4_ADDR          (0x03001400UL)
#define EFM_OTP_BASE4_SIZE          (0x10UL)
#define EFM_OTP_BASE4_OFFSET        (22UL)
#define EFM_OTP_BASE5_ADDR          (0x03001600UL)
#define EFM_OTP_BASE5_SIZE          (0x04UL)
#define EFM_OTP_BASE5_OFFSET        (54UL)
#define EFM_OTP_LOCK_ADDR           (0x03001800UL)
/**
 * @}
 */

/**
 * @defgroup EFM_OTP_Address EFM Otp Address
 * @{
 */
#define EFM_OTP_BLOCK0              (EFM_OTP_BASE1_ADDR + ((0UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK1              (EFM_OTP_BASE1_ADDR + ((1UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK2              (EFM_OTP_BASE1_ADDR + ((2UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK3              (EFM_OTP_BASE1_ADDR + ((3UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK4              (EFM_OTP_BASE1_ADDR + ((4UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK5              (EFM_OTP_BASE1_ADDR + ((5UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK6              (EFM_OTP_BASE1_ADDR + ((6UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK7              (EFM_OTP_BASE1_ADDR + ((7UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK8              (EFM_OTP_BASE1_ADDR + ((8UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK9              (EFM_OTP_BASE1_ADDR + ((9UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK10             (EFM_OTP_BASE1_ADDR + ((10UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK11             (EFM_OTP_BASE1_ADDR + ((11UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK12             (EFM_OTP_BASE1_ADDR + ((12UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK13             (EFM_OTP_BASE1_ADDR + ((13UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))
#define EFM_OTP_BLOCK14             (EFM_OTP_BASE1_ADDR + ((14UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))

#define EFM_OTP_BLOCK15             (EFM_OTP_BASE1_ADDR + ((15UL - EFM_OTP_BASE1_OFFSET) * EFM_OTP_BASE1_SIZE))

#define EFM_OTP_BLOCK16             (EFM_OTP_BASE2_ADDR + ((16UL - EFM_OTP_BASE2_OFFSET) * EFM_OTP_BASE2_SIZE))
#define EFM_OTP_BLOCK17             (EFM_OTP_BASE2_ADDR + ((17UL - EFM_OTP_BASE2_OFFSET) * EFM_OTP_BASE2_SIZE))

#define EFM_OTP_BLOCK18             (EFM_OTP_BASE3_ADDR + ((18UL - EFM_OTP_BASE3_OFFSET) * EFM_OTP_BASE3_SIZE))
#define EFM_OTP_BLOCK19             (EFM_OTP_BASE3_ADDR + ((19UL - EFM_OTP_BASE3_OFFSET) * EFM_OTP_BASE3_SIZE))
#define EFM_OTP_BLOCK20             (EFM_OTP_BASE3_ADDR + ((20UL - EFM_OTP_BASE3_OFFSET) * EFM_OTP_BASE3_SIZE))
#define EFM_OTP_BLOCK21             (EFM_OTP_BASE3_ADDR + ((21UL - EFM_OTP_BASE3_OFFSET) * EFM_OTP_BASE3_SIZE))

#define EFM_OTP_BLOCK22             (EFM_OTP_BASE4_ADDR + ((22UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK23             (EFM_OTP_BASE4_ADDR + ((23UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK24             (EFM_OTP_BASE4_ADDR + ((24UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK25             (EFM_OTP_BASE4_ADDR + ((25UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK26             (EFM_OTP_BASE4_ADDR + ((26UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK27             (EFM_OTP_BASE4_ADDR + ((27UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK28             (EFM_OTP_BASE4_ADDR + ((28UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK29             (EFM_OTP_BASE4_ADDR + ((29UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK30             (EFM_OTP_BASE4_ADDR + ((30UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK31             (EFM_OTP_BASE4_ADDR + ((31UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK32             (EFM_OTP_BASE4_ADDR + ((32UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK33             (EFM_OTP_BASE4_ADDR + ((33UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK34             (EFM_OTP_BASE4_ADDR + ((34UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK35             (EFM_OTP_BASE4_ADDR + ((35UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK36             (EFM_OTP_BASE4_ADDR + ((36UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK37             (EFM_OTP_BASE4_ADDR + ((37UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK38             (EFM_OTP_BASE4_ADDR + ((38UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK39             (EFM_OTP_BASE4_ADDR + ((39UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK40             (EFM_OTP_BASE4_ADDR + ((40UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK41             (EFM_OTP_BASE4_ADDR + ((41UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK42             (EFM_OTP_BASE4_ADDR + ((42UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK43             (EFM_OTP_BASE4_ADDR + ((43UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK44             (EFM_OTP_BASE4_ADDR + ((44UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK45             (EFM_OTP_BASE4_ADDR + ((45UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK46             (EFM_OTP_BASE4_ADDR + ((46UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK47             (EFM_OTP_BASE4_ADDR + ((47UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK48             (EFM_OTP_BASE4_ADDR + ((48UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK49             (EFM_OTP_BASE4_ADDR + ((49UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK50             (EFM_OTP_BASE4_ADDR + ((50UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK51             (EFM_OTP_BASE4_ADDR + ((51UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK52             (EFM_OTP_BASE4_ADDR + ((52UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))
#define EFM_OTP_BLOCK53             (EFM_OTP_BASE4_ADDR + ((53UL - EFM_OTP_BASE4_OFFSET) * EFM_OTP_BASE4_SIZE))

#define EFM_OTP_BLOCK54             (EFM_OTP_BASE5_ADDR + ((54UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK55             (EFM_OTP_BASE5_ADDR + ((55UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK56             (EFM_OTP_BASE5_ADDR + ((56UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK57             (EFM_OTP_BASE5_ADDR + ((57UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK58             (EFM_OTP_BASE5_ADDR + ((58UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK59             (EFM_OTP_BASE5_ADDR + ((59UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK60             (EFM_OTP_BASE5_ADDR + ((60UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK61             (EFM_OTP_BASE5_ADDR + ((61UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK62             (EFM_OTP_BASE5_ADDR + ((62UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK63             (EFM_OTP_BASE5_ADDR + ((63UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK64             (EFM_OTP_BASE5_ADDR + ((64UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK65             (EFM_OTP_BASE5_ADDR + ((65UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK66             (EFM_OTP_BASE5_ADDR + ((66UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK67             (EFM_OTP_BASE5_ADDR + ((67UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK68             (EFM_OTP_BASE5_ADDR + ((68UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK69             (EFM_OTP_BASE5_ADDR + ((69UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK70             (EFM_OTP_BASE5_ADDR + ((70UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK71             (EFM_OTP_BASE5_ADDR + ((71UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK72             (EFM_OTP_BASE5_ADDR + ((72UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK73             (EFM_OTP_BASE5_ADDR + ((73UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK74             (EFM_OTP_BASE5_ADDR + ((74UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK75             (EFM_OTP_BASE5_ADDR + ((75UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK76             (EFM_OTP_BASE5_ADDR + ((76UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK77             (EFM_OTP_BASE5_ADDR + ((77UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK78             (EFM_OTP_BASE5_ADDR + ((78UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK79             (EFM_OTP_BASE5_ADDR + ((79UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK80             (EFM_OTP_BASE5_ADDR + ((80UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK81             (EFM_OTP_BASE5_ADDR + ((81UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK82             (EFM_OTP_BASE5_ADDR + ((82UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK83             (EFM_OTP_BASE5_ADDR + ((83UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK84             (EFM_OTP_BASE5_ADDR + ((84UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK85             (EFM_OTP_BASE5_ADDR + ((85UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK86             (EFM_OTP_BASE5_ADDR + ((86UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK87             (EFM_OTP_BASE5_ADDR + ((87UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK88             (EFM_OTP_BASE5_ADDR + ((88UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK89             (EFM_OTP_BASE5_ADDR + ((89UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK90             (EFM_OTP_BASE5_ADDR + ((90UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK91             (EFM_OTP_BASE5_ADDR + ((91UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK92             (EFM_OTP_BASE5_ADDR + ((92UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK93             (EFM_OTP_BASE5_ADDR + ((93UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK94             (EFM_OTP_BASE5_ADDR + ((94UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK95             (EFM_OTP_BASE5_ADDR + ((95UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK96             (EFM_OTP_BASE5_ADDR + ((96UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK97             (EFM_OTP_BASE5_ADDR + ((97UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK98             (EFM_OTP_BASE5_ADDR + ((98UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK99             (EFM_OTP_BASE5_ADDR + ((99UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK100            (EFM_OTP_BASE5_ADDR + ((100UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK101            (EFM_OTP_BASE5_ADDR + ((101UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK102            (EFM_OTP_BASE5_ADDR + ((102UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK103            (EFM_OTP_BASE5_ADDR + ((103UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK104            (EFM_OTP_BASE5_ADDR + ((104UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK105            (EFM_OTP_BASE5_ADDR + ((105UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK106            (EFM_OTP_BASE5_ADDR + ((106UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK107            (EFM_OTP_BASE5_ADDR + ((107UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK108            (EFM_OTP_BASE5_ADDR + ((108UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK109            (EFM_OTP_BASE5_ADDR + ((109UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK110            (EFM_OTP_BASE5_ADDR + ((110UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK111            (EFM_OTP_BASE5_ADDR + ((111UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK112            (EFM_OTP_BASE5_ADDR + ((112UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK113            (EFM_OTP_BASE5_ADDR + ((113UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK114            (EFM_OTP_BASE5_ADDR + ((114UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK115            (EFM_OTP_BASE5_ADDR + ((115UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK116            (EFM_OTP_BASE5_ADDR + ((116UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK117            (EFM_OTP_BASE5_ADDR + ((117UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK118            (EFM_OTP_BASE5_ADDR + ((118UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK119            (EFM_OTP_BASE5_ADDR + ((119UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK120            (EFM_OTP_BASE5_ADDR + ((120UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK121            (EFM_OTP_BASE5_ADDR + ((121UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK122            (EFM_OTP_BASE5_ADDR + ((122UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK123            (EFM_OTP_BASE5_ADDR + ((123UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK124            (EFM_OTP_BASE5_ADDR + ((124UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK125            (EFM_OTP_BASE5_ADDR + ((125UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK126            (EFM_OTP_BASE5_ADDR + ((126UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK127            (EFM_OTP_BASE5_ADDR + ((127UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK128            (EFM_OTP_BASE5_ADDR + ((128UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK129            (EFM_OTP_BASE5_ADDR + ((129UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK130            (EFM_OTP_BASE5_ADDR + ((130UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK131            (EFM_OTP_BASE5_ADDR + ((131UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK132            (EFM_OTP_BASE5_ADDR + ((132UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK133            (EFM_OTP_BASE5_ADDR + ((133UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK134            (EFM_OTP_BASE5_ADDR + ((134UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK135            (EFM_OTP_BASE5_ADDR + ((135UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK136            (EFM_OTP_BASE5_ADDR + ((136UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK137            (EFM_OTP_BASE5_ADDR + ((137UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK138            (EFM_OTP_BASE5_ADDR + ((138UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK139            (EFM_OTP_BASE5_ADDR + ((139UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK140            (EFM_OTP_BASE5_ADDR + ((140UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK141            (EFM_OTP_BASE5_ADDR + ((141UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK142            (EFM_OTP_BASE5_ADDR + ((142UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK143            (EFM_OTP_BASE5_ADDR + ((143UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK144            (EFM_OTP_BASE5_ADDR + ((144UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK145            (EFM_OTP_BASE5_ADDR + ((145UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK146            (EFM_OTP_BASE5_ADDR + ((146UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK147            (EFM_OTP_BASE5_ADDR + ((147UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK148            (EFM_OTP_BASE5_ADDR + ((148UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK149            (EFM_OTP_BASE5_ADDR + ((149UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK150            (EFM_OTP_BASE5_ADDR + ((150UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK151            (EFM_OTP_BASE5_ADDR + ((151UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK152            (EFM_OTP_BASE5_ADDR + ((152UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK153            (EFM_OTP_BASE5_ADDR + ((153UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK154            (EFM_OTP_BASE5_ADDR + ((154UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK155            (EFM_OTP_BASE5_ADDR + ((155UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK156            (EFM_OTP_BASE5_ADDR + ((156UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK157            (EFM_OTP_BASE5_ADDR + ((157UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK158            (EFM_OTP_BASE5_ADDR + ((158UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK159            (EFM_OTP_BASE5_ADDR + ((159UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK160            (EFM_OTP_BASE5_ADDR + ((160UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK161            (EFM_OTP_BASE5_ADDR + ((161UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK162            (EFM_OTP_BASE5_ADDR + ((162UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK163            (EFM_OTP_BASE5_ADDR + ((163UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK164            (EFM_OTP_BASE5_ADDR + ((164UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK165            (EFM_OTP_BASE5_ADDR + ((165UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK166            (EFM_OTP_BASE5_ADDR + ((166UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK167            (EFM_OTP_BASE5_ADDR + ((167UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK168            (EFM_OTP_BASE5_ADDR + ((168UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK169            (EFM_OTP_BASE5_ADDR + ((169UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK170            (EFM_OTP_BASE5_ADDR + ((170UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK171            (EFM_OTP_BASE5_ADDR + ((171UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK172            (EFM_OTP_BASE5_ADDR + ((172UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK173            (EFM_OTP_BASE5_ADDR + ((173UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK174            (EFM_OTP_BASE5_ADDR + ((174UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK175            (EFM_OTP_BASE5_ADDR + ((175UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK176            (EFM_OTP_BASE5_ADDR + ((176UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK177            (EFM_OTP_BASE5_ADDR + ((177UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK178            (EFM_OTP_BASE5_ADDR + ((178UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK179            (EFM_OTP_BASE5_ADDR + ((179UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK180            (EFM_OTP_BASE5_ADDR + ((180UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))
#define EFM_OTP_BLOCK181            (EFM_OTP_BASE5_ADDR + ((181UL - EFM_OTP_BASE5_OFFSET) * EFM_OTP_BASE5_SIZE))

/**
 * @}
 */

/**
 * @defgroup EFM_OTP_Lock_Address EFM Otp Lock_address
 *          x at range of 0~181
 * @{
 */
#define EFM_OTP_BLOCK_LOCKADDR(x)    (EFM_OTP_LOCK_ADDR + 0x04UL * (x))   /*!< OTP block x  lock address */
/**
 * @}
 */

#define EFM_REMAP_REG_LOCK_KEY      (0x0000UL)
#define EFM_REMAP_REG_UNLOCK_KEY1   (0x0123UL)
#define EFM_REMAP_REG_UNLOCK_KEY2   (0x3210UL)

/**
 * @defgroup EFM_Remap_State EFM remap function state
 * @{
 */
#define EFM_REMAP_OFF               (0UL)
#define EFM_REMAP_ON                (EFM_MMF_REMCR_EN)
/**
 * @}
 */

/**
 * @defgroup EFM_Remap_Size EFM remap size definition
 * @note refer to chip user manual for details size spec.
 * @{
 */
#define EFM_REMAP_4K                (12UL)
#define EFM_REMAP_8K                (13UL)
#define EFM_REMAP_16K               (14UL)
#define EFM_REMAP_32K               (15UL)
#define EFM_REMAP_64K               (16UL)
#define EFM_REMAP_128K              (17UL)
#define EFM_REMAP_256K              (18UL)
#define EFM_REMAP_512K              (19UL)
#define EFM_REMAP_SIZE_MAX          EFM_REMAP_512K
/**
 * @}
 */

/**
 * @defgroup EFM_Remap_Index EFM remap index
 * @{
 */
#define EFM_REMAP_IDX0              (0U)
#define EFM_REMAP_IDX1              (1U)
/**
 * @}
 */

/**
 * @defgroup EFM_Remap_BaseAddr EFM remap base address
 * @{
 */
#define EFM_REMAP_BASE_ADDR0        (0x2000000UL)
#define EFM_REMAP_BASE_ADDR1        (0x2080000UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Remap_Region EFM remap ROM/RAM region
 * @{
 */
#define EFM_REMAP_ROM_END_ADDR      EFM_END_ADDR

#define EFM_REMAP_RAM_START_ADDR    (0x1FFF8000UL)
#define EFM_REMAP_RAM_END_ADDR      (0x1FFFFFFFUL)
/**
 * @}
 */

/**
 * @defgroup EFM_Protect_Level EFM protect level
 * @{
 */
#define EFM_PROTECT_LEVEL1          (1U)
#define EFM_PROTECT_LEVEL2          (2U)
#define EFM_PROTECT_LEVEL3          (4U)
/**
 * @}
 */

/**
 * @defgroup EFM_MCU_Status EFM protect level
 * @{
 */
#define EFM_MCU_PROTECT1_FREE       (0U)
#define EFM_MCU_PROTECT1_LOCK       (1U)
#define EFM_MCU_PROTECT1_UNLOCK     (2U)
#define EFM_MCU_PROTECT2_LOCK       (4U)
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
 * @addtogroup EFM_Global_Functions
 * @{
 */

/**
 * @brief  EFM Protect Unlock.
 * @param  None
 * @retval None
 */

__STATIC_INLINE void EFM_REG_Unlock(void)
{
    WRITE_REG32(CM_EFM->FAPRT, EFM_REG_UNLOCK_KEY1);
    WRITE_REG32(CM_EFM->FAPRT, EFM_REG_UNLOCK_KEY2);
}

/**
 * @brief  EFM Protect Lock.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EFM_REG_Lock(void)
{
    WRITE_REG32(CM_EFM->FAPRT, EFM_REG_LOCK_KEY);
}

/**
 * @brief  EFM remap Unlock.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EFM_REMAP_Unlock(void)
{
    WRITE_REG32(CM_EFM->MMF_REMPRT, EFM_REMAP_REG_UNLOCK_KEY1);
    WRITE_REG32(CM_EFM->MMF_REMPRT, EFM_REMAP_REG_UNLOCK_KEY2);
}

/**
 * @brief  EFM remap Lock.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void EFM_REMAP_Lock(void)
{
    WRITE_REG32(CM_EFM->MMF_REMPRT, EFM_REMAP_REG_LOCK_KEY);
}

void EFM_Cmd(uint32_t u32Flash, en_functional_state_t enNewState);
void EFM_FWMC_Cmd(en_functional_state_t enNewState);
void EFM_SetBusStatus(uint32_t u32Status);
void EFM_IntCmd(uint32_t u32EfmInt, en_functional_state_t enNewState);
void EFM_ClearStatus(uint32_t u32Flag);
int32_t EFM_SetWaitCycle(uint32_t u32WaitCycle);
int32_t EFM_SetOperateMode(uint32_t u32Mode);
int32_t EFM_ReadByte(uint32_t u32Addr, uint8_t *pu8ReadBuf, uint32_t u32ByteLen);
int32_t EFM_Program(uint32_t u32Addr, uint8_t *pu8Buf, uint32_t u32Len);
int32_t EFM_ProgramWord(uint32_t u32Addr, uint32_t u32Data);
int32_t EFM_ProgramWordReadBack(uint32_t u32Addr, uint32_t u32Data);
int32_t EFM_SequenceProgram(uint32_t u32Addr, uint8_t *pu8Buf, uint32_t u32Len);
int32_t EFM_SectorErase(uint32_t u32Addr);
int32_t EFM_ChipErase(uint8_t u8Chip);

en_flag_status_t EFM_GetAnyStatus(uint32_t u32Flag);
en_flag_status_t EFM_GetStatus(uint32_t u32Flag);
void EFM_GetUID(stc_efm_unique_id_t *pstcUID);

void EFM_CacheRamReset(en_functional_state_t enNewState);
void EFM_PrefetchCmd(en_functional_state_t enNewState);
void EFM_DCacheCmd(en_functional_state_t enNewState);
void EFM_ICacheCmd(en_functional_state_t enNewState);

void EFM_LowVoltageReadCmd(en_functional_state_t enNewState);
int32_t EFM_SwapCmd(en_functional_state_t enNewState);
en_flag_status_t EFM_GetSwapStatus(void);
int32_t EFM_OTP_Lock(uint32_t u32Addr);

int32_t EFM_REMAP_StructInit(stc_efm_remap_init_t *pstcEfmRemapInit);
int32_t EFM_REMAP_Init(uint8_t u8RemapIdx, stc_efm_remap_init_t *pstcEfmRemapInit);
void EFM_REMAP_DeInit(void);
void EFM_REMAP_Cmd(uint8_t u8RemapIdx, en_functional_state_t enNewState);
void EFM_REMAP_SetAddr(uint8_t u8RemapIdx, uint32_t u32Addr);
void EFM_REMAP_SetSize(uint8_t u8RemapIdx, uint32_t u32Size);

uint32_t EFM_GetCID(void);
void EFM_OTP_WP_Unlock(void);
void EFM_OTP_WP_Lock(void);
int32_t EFM_OTP_Enable(void);
void EFM_SectorProtectRegLock(uint32_t u32RegLock);
void EFM_SingleSectorOperateCmd(uint8_t u8SectorNum, en_functional_state_t enNewState);
void EFM_SequenceSectorOperateCmd(uint32_t u32StartSectorNum, uint16_t u16Count, en_functional_state_t enNewState);

void EFM_Protect_Enable(uint8_t u8Level);
int32_t EFM_WriteSecurityCode(uint8_t *pu8Buf, uint32_t u32Len);

/**
 * @}
 */

#endif /* LL_EFM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_EFM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
