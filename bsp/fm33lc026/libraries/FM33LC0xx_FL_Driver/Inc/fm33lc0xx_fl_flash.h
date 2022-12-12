/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_flash.h
  * @author  FMSH Application Team
  * @brief   Head file of FLASH FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LC0XX_FL_FLASH_H
#define __FM33LC0XX_FL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup FLASH FLASH
  * @brief FLASH FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup FLASH_FL_ES_INIT FLASH Exported Init structures
  * @{
  */

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup FLASH_FL_Exported_Constants FLASH Exported Constants
  * @{
  */

#define    FLASH_RDCR_WAIT_Pos                                    (0U)
#define    FLASH_RDCR_WAIT_Msk                                    (0x3U << FLASH_RDCR_WAIT_Pos)
#define    FLASH_RDCR_WAIT                                        FLASH_RDCR_WAIT_Msk

#define    FLASH_PFCR_PRFTEN_Pos                                  (0U)
#define    FLASH_PFCR_PRFTEN_Msk                                  (0x1U << FLASH_PFCR_PRFTEN_Pos)
#define    FLASH_PFCR_PRFTEN                                      FLASH_PFCR_PRFTEN_Msk

#define    FLASH_OPTBR_IWDTSLP_Pos                                (31U)
#define    FLASH_OPTBR_IWDTSLP_Msk                                (0x1U << FLASH_OPTBR_IWDTSLP_Pos)
#define    FLASH_OPTBR_IWDTSLP                                    FLASH_OPTBR_IWDTSLP_Msk

#define    FLASH_OPTBR_IFLOCK_Pos                                 (17U)
#define    FLASH_OPTBR_IFLOCK_Msk                                 (0x3U << FLASH_OPTBR_IFLOCK_Pos)
#define    FLASH_OPTBR_IFLOCK                                     FLASH_OPTBR_IFLOCK_Msk

#define    FLASH_OPTBR_DFLSEN_Pos                                 (10U)
#define    FLASH_OPTBR_DFLSEN_Msk                                 (0x1U << FLASH_OPTBR_DFLSEN_Pos)
#define    FLASH_OPTBR_DFLSEN                                     FLASH_OPTBR_DFLSEN_Msk

#define    FLASH_OPTBR_BTSEN_Pos                                  (8U)
#define    FLASH_OPTBR_BTSEN_Msk                                  (0x3U << FLASH_OPTBR_BTSEN_Pos)
#define    FLASH_OPTBR_BTSEN                                      FLASH_OPTBR_BTSEN_Msk

#define    FLASH_OPTBR_ACLOCKEN_Pos                               (2U)
#define    FLASH_OPTBR_ACLOCKEN_Msk                               (0x3U << FLASH_OPTBR_ACLOCKEN_Pos)
#define    FLASH_OPTBR_ACLOCKEN                                   FLASH_OPTBR_ACLOCKEN_Msk

#define    FLASH_OPTBR_DBRDPEN_Pos                                (0U)
#define    FLASH_OPTBR_DBRDPEN_Msk                                (0x3U << FLASH_OPTBR_DBRDPEN_Pos)
#define    FLASH_OPTBR_DBRDPEN                                    FLASH_OPTBR_DBRDPEN_Msk

#define    FLASH_EPCR_ERTYPE_Pos                                  (8U)
#define    FLASH_EPCR_ERTYPE_Msk                                  (0x3U << FLASH_EPCR_ERTYPE_Pos)
#define    FLASH_EPCR_ERTYPE                                      FLASH_EPCR_ERTYPE_Msk

#define    FLASH_EPCR_PREQ_Pos                                    (1U)
#define    FLASH_EPCR_PREQ_Msk                                    (0x1U << FLASH_EPCR_PREQ_Pos)
#define    FLASH_EPCR_PREQ                                        FLASH_EPCR_PREQ_Msk

#define    FLASH_EPCR_EREQ_Pos                                    (0U)
#define    FLASH_EPCR_EREQ_Msk                                    (0x1U << FLASH_EPCR_EREQ_Pos)
#define    FLASH_EPCR_EREQ                                        FLASH_EPCR_EREQ_Msk

#define    FLASH_IER_OPTIE_Pos                                    (11U)
#define    FLASH_IER_OPTIE_Msk                                    (0x1U << FLASH_IER_OPTIE_Pos)
#define    FLASH_IER_OPTIE                                        FLASH_IER_OPTIE_Msk

#define    FLASH_IER_AUTHIE_Pos                                   (10U)
#define    FLASH_IER_AUTHIE_Msk                                   (0x1U << FLASH_IER_AUTHIE_Pos)
#define    FLASH_IER_AUTHIE                                       FLASH_IER_AUTHIE_Msk

#define    FLASH_IER_KEYIE_Pos                                    (9U)
#define    FLASH_IER_KEYIE_Msk                                    (0x1U << FLASH_IER_KEYIE_Pos)
#define    FLASH_IER_KEYIE                                        FLASH_IER_KEYIE_Msk

#define    FLASH_IER_CKIE_Pos                                     (8U)
#define    FLASH_IER_CKIE_Msk                                     (0x1U << FLASH_IER_CKIE_Pos)
#define    FLASH_IER_CKIE                                         FLASH_IER_CKIE_Msk

#define    FLASH_IER_PRDIE_Pos                                    (1U)
#define    FLASH_IER_PRDIE_Msk                                    (0x1U << FLASH_IER_PRDIE_Pos)
#define    FLASH_IER_PRDIE                                        FLASH_IER_PRDIE_Msk

#define    FLASH_IER_ERDIE_Pos                                    (0U)
#define    FLASH_IER_ERDIE_Msk                                    (0x1U << FLASH_IER_ERDIE_Pos)
#define    FLASH_IER_ERDIE                                        FLASH_IER_ERDIE_Msk

#define    FLASH_ISR_KEYSTA_Pos                                   (17U)
#define    FLASH_ISR_KEYSTA_Msk                                   (0x7U << FLASH_ISR_KEYSTA_Pos)
#define    FLASH_ISR_KEYSTA                                       FLASH_ISR_KEYSTA_Msk

#define    FLASH_ISR_BTSF_Pos                                     (16U)
#define    FLASH_ISR_BTSF_Msk                                     (0x1U << FLASH_ISR_BTSF_Pos)
#define    FLASH_ISR_BTSF                                         FLASH_ISR_BTSF_Msk

#define    FLASH_ISR_OPTERR_Pos                                   (11U)
#define    FLASH_ISR_OPTERR_Msk                                   (0x1U << FLASH_ISR_OPTERR_Pos)
#define    FLASH_ISR_OPTERR                                       FLASH_ISR_OPTERR_Msk

#define    FLASH_ISR_AUTHERR_Pos                                  (10U)
#define    FLASH_ISR_AUTHERR_Msk                                  (0x1U << FLASH_ISR_AUTHERR_Pos)
#define    FLASH_ISR_AUTHERR                                      FLASH_ISR_AUTHERR_Msk

#define    FLASH_ISR_KEYERR_Pos                                   (9U)
#define    FLASH_ISR_KEYERR_Msk                                   (0x1U << FLASH_ISR_KEYERR_Pos)
#define    FLASH_ISR_KEYERR                                       FLASH_ISR_KEYERR_Msk

#define    FLASH_ISR_CKERR_Pos                                    (8U)
#define    FLASH_ISR_CKERR_Msk                                    (0x1U << FLASH_ISR_CKERR_Pos)
#define    FLASH_ISR_CKERR                                        FLASH_ISR_CKERR_Msk

#define    FLASH_ISR_PRD_Pos                                      (1U)
#define    FLASH_ISR_PRD_Msk                                      (0x1U << FLASH_ISR_PRD_Pos)
#define    FLASH_ISR_PRD                                          FLASH_ISR_PRD_Msk

#define    FLASH_ISR_ERD_Pos                                      (0U)
#define    FLASH_ISR_ERD_Msk                                      (0x1U << FLASH_ISR_ERD_Pos)
#define    FLASH_ISR_ERD                                          FLASH_ISR_ERD_Msk



#define    FL_FLASH_INFORMATION1_REGIN                            (0x1U << 17U)
#define    FL_FLASH_INFORMATION2_REGIN                            (0x1U << 18U)
#define    FL_FLASH_BLOCK_0                                       (0x1U << 0U)
#define    FL_FLASH_BLOCK_1                                       (0x1U << 1U)
#define    FL_FLASH_BLOCK_2                                       (0x1U << 2U)
#define    FL_FLASH_BLOCK_3                                       (0x1U << 3U)
#define    FL_FLASH_BLOCK_4                                       (0x1U << 4U)
#define    FL_FLASH_BLOCK_5                                       (0x1U << 5U)
#define    FL_FLASH_BLOCK_6                                       (0x1U << 6U)
#define    FL_FLASH_BLOCK_7                                       (0x1U << 7U)
#define    FL_FLASH_BLOCK_8                                       (0x1U << 8U)
#define    FL_FLASH_BLOCK_9                                       (0x1U << 9U)
#define    FL_FLASH_BLOCK_10                                      (0x1U << 10U)
#define    FL_FLASH_BLOCK_11                                      (0x1U << 11U)
#define    FL_FLASH_BLOCK_12                                      (0x1U << 12U)
#define    FL_FLASH_BLOCK_13                                      (0x1U << 13U)
#define    FL_FLASH_BLOCK_14                                      (0x1U << 14U)
#define    FL_FLASH_BLOCK_15                                      (0x1U << 15U)
#define    FL_FLASH_LOCK_ALL                                      (0x0U << 0U)
#define    FL_FLASH_LOCK_SOFTWARE                                 (0x2U << 0U)
#define    FL_FLASH_LOCK_NONE                                     (0x3U << 0U)
#define    FL_FLASH_BOOTSWAP_ENABLE                               (0x2U << 8U)
#define    FL_FLASH_BOOTSWAP_DISABLE                              (0x0U << 8U)
#define    FL_FLASH_APPCODE_LOCK_ENABLE                           (0x2U << 2U)
#define    FL_FLASH_APPCODE_LOCK_DISABLE                          (0x0U << 2U)
#define    FL_FLASH_DEBUG_READ_ENABLE                             (0x2U << 0U)
#define    FL_FLASH_DEBUG_READ_DISABLE                            (0x0U << 0U)
#define    FL_FLASH_ERASE_KEY                                     0x96969696U
#define    FL_FLASH_CHIP_ERASE_KEY                                0x7D7D7D7DU
#define    FL_FLASH_PAGE_ERASE_KEY                                0xEAEAEAEAU
#define    FL_FLASH_SECTOR_ERASE_KEY                              0x3C3C3C3CU
#define    FL_FLASH_ERASE_REQUEST                                 0x1234ABCDU
#define    FL_FLASH_PROGRAM_KEY1                                  0xA5A5A5A5U
#define    FL_FLASH_PROGRAM_KEY2                                  0xF1F1F1F1U
#define    FL_FLASH_ERASE_TIMEOUT                                 0x0000FFFFU
#define    FL_FLASH_ADDRS_ALIGN                                   0x00000004U
#define    FL_FLASH_MAX_PAGE_NUM                                  0x00000200U
#define    FL_FLASH_MAX_SECTOR_NUM                                0x00000080U
#define    FL_FLASH_SECTOR_SIZE_BYTE                              0x00000800U
#define    FL_FLASH_PAGE_SIZE_BYTE                                0x00000200U
#define    FL_FLASH_ADDR_MAXPROGRAM                               0x0003FFFFU



#define    FL_FLASH_READ_WAIT_0CYCLE                              (0x0U << FLASH_RDCR_WAIT_Pos)
#define    FL_FLASH_READ_WAIT_1CYCLE                              (0x1U << FLASH_RDCR_WAIT_Pos)
#define    FL_FLASH_READ_WAIT_2CYCLE                              (0x2U << FLASH_RDCR_WAIT_Pos)


#define    FL_FLASH_IWDT_STOP_UNDER_SLEEP                         (0x0U << FLASH_OPTBR_IWDTSLP_Pos)
#define    FL_FLASH_IWDT_WORK_UNDER_SLEEP                         (0x1U << FLASH_OPTBR_IWDTSLP_Pos)

#define    FL_FLASH_IF_UNLOCK                                     (0x0U << FLASH_OPTBR_IFLOCK_Pos)
#define    FL_FLASH_IF_LOCK                                       (0x1U << FLASH_OPTBR_IFLOCK_Pos)

#define    FL_FLASH_DATA_FLASH_DISABLE                            (0x0U << FLASH_OPTBR_DFLSEN_Pos)
#define    FL_FLASH_DATA_FLASH_ENABLE                             (0x1U << FLASH_OPTBR_DFLSEN_Pos)

#define    FL_FLASH_BOOT_SWAP_DISABLE                             (0x0U << FLASH_OPTBR_BTSEN_Pos)
#define    FL_FLASH_BOOT_SWAP_ENABLE                              (0x1U << FLASH_OPTBR_BTSEN_Pos)

#define    FL_FLASH_FLASH_LOCK_DISABLE                            (0x0U << FLASH_OPTBR_ACLOCKEN_Pos)
#define    FL_FLASH_FLASH_LOCK_ENABLE                             (0x1U << FLASH_OPTBR_ACLOCKEN_Pos)

#define    FL_FLASH_SWD_READ_PEOTECTION_DISABLE                   (0x0U << FLASH_OPTBR_DBRDPEN_Pos)
#define    FL_FLASH_SWD_READ_PEOTECTION_ENABLE                    (0x1U << FLASH_OPTBR_DBRDPEN_Pos)

#define    FL_FLASH_ERASE_TYPE_PAGE                               (0x0U << FLASH_EPCR_ERTYPE_Pos)
#define    FL_FLASH_ERASE_TYPE_SECTOR                             (0x1U << FLASH_EPCR_ERTYPE_Pos)


#define    FL_FLASH_KEY_STATUS_LOCK                               (0x0U << FLASH_ISR_KEYSTA_Pos)
#define    FL_FLASH_KEY_STATUS_PAGE_ERASE                         (0x2U << FLASH_ISR_KEYSTA_Pos)
#define    FL_FLASH_KEY_STATUS_PROGRAM                            (0x3U << FLASH_ISR_KEYSTA_Pos)
#define    FL_FLASH_KEY_STATUS_ERROR                              (0x4U << FLASH_ISR_KEYSTA_Pos)
#define    FL_FLASH_KEY_STATUS_SECTOR_ERASE                       (0x5U << FLASH_ISR_KEYSTA_Pos)

#define    FL_FLASH_BOOT_SECTOR_0000H_1FFFH                       (0x0U << FLASH_ISR_BTSF_Pos)
#define    FL_FLASH_BOOT_SECTOR_2000H_3FFFH                       (0x1U << FLASH_ISR_BTSF_Pos)

/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup FLASH_FL_Exported_Functions FLASH Exported Functions
  * @{
  */

/**
  * @brief    Flash wait cycles config
  * @rmtoll   RDCR    WAIT    FL_FLASH_SetReadWait
  * @param    FLASHx FLASH instance
  * @param    wait This parameter can be one of the following values:
  *           @arg @ref FL_FLASH_READ_WAIT_0CYCLE
  *           @arg @ref FL_FLASH_READ_WAIT_1CYCLE
  *           @arg @ref FL_FLASH_READ_WAIT_2CYCLE
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_SetReadWait(FLASH_Type *FLASHx, uint32_t wait)
{
    MODIFY_REG(FLASHx->RDCR, FLASH_RDCR_WAIT_Msk, wait);
}

/**
  * @brief    Get flash wait cycles config status
  * @rmtoll   RDCR    WAIT    FL_FLASH_GetReadWait
  * @param    FLASHx FLASH instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_FLASH_READ_WAIT_0CYCLE
  *           @arg @ref FL_FLASH_READ_WAIT_1CYCLE
  *           @arg @ref FL_FLASH_READ_WAIT_2CYCLE
  */
__STATIC_INLINE uint32_t FL_FLASH_GetReadWait(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->RDCR, FLASH_RDCR_WAIT_Msk));
}

/**
  * @brief    Prefetch Enable
  * @rmtoll   PFCR    PRFTEN    FL_FLASH_EnablePrefetch
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_EnablePrefetch(FLASH_Type *FLASHx)
{
    SET_BIT(FLASHx->PFCR, FLASH_PFCR_PRFTEN_Msk);
}

/**
  * @brief    Get prefetch enable status
  * @rmtoll   PFCR    PRFTEN    FL_FLASH_IsEnabledPrefetch
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsEnabledPrefetch(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->PFCR, FLASH_PFCR_PRFTEN_Msk) == FLASH_PFCR_PRFTEN_Msk);
}

/**
  * @brief    Prefetch disable
  * @rmtoll   PFCR    PRFTEN    FL_FLASH_DisablePrefetch
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_DisablePrefetch(FLASH_Type *FLASHx)
{
    CLEAR_BIT(FLASHx->PFCR, FLASH_PFCR_PRFTEN_Msk);
}

/**
  * @brief    Get IWDT sleep enable status
  * @rmtoll   OPTBR    IWDTSLP    FL_FLASH_GetIWDTStateUnderSleep
  * @param    FLASHx FLASH instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_FLASH_IWDT_STOP_UNDER_SLEEP
  *           @arg @ref FL_FLASH_IWDT_WORK_UNDER_SLEEP
  */
__STATIC_INLINE uint32_t FL_FLASH_GetIWDTStateUnderSleep(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->OPTBR, FLASH_OPTBR_IWDTSLP_Msk));
}

/**
  * @brief    Get information2 lock enable flag
  * @rmtoll   OPTBR    IFLOCK    FL_FLASH_IsActiveFlag_IFLockedState
  * @param    FLASHx FLASH instance
  * @param    region This parameter can be one of the following values:
  *           @arg @ref FL_FLASH_INFORMATION1_REGIN
  *           @arg @ref FL_FLASH_INFORMATION2_REGIN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsActiveFlag_IFLockedState(FLASH_Type *FLASHx, uint32_t region)
{
    return (uint32_t)(READ_BIT(FLASHx->OPTBR, FLASH_OPTBR_IFLOCK_Msk) == (FLASH_OPTBR_IFLOCK_Msk));
}

/**
  * @brief    Get dataflash enable status
  * @rmtoll   OPTBR    DFLSEN    FL_FLASH_GetDataFlashState
  * @param    FLASHx FLASH instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_FLASH_DATA_FLASH_DISABLE
  *           @arg @ref FL_FLASH_DATA_FLASH_ENABLE
  */
__STATIC_INLINE uint32_t FL_FLASH_GetDataFlashState(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->OPTBR, FLASH_OPTBR_DFLSEN_Msk));
}

/**
  * @brief    Get BootSwap enable status
  * @rmtoll   OPTBR    BTSEN    FL_FLASH_GetBootSwapState
  * @param    FLASHx FLASH instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_FLASH_BOOT_SWAP_DISABLE
  *           @arg @ref FL_FLASH_BOOT_SWAP_ENABLE
  */
__STATIC_INLINE uint32_t FL_FLASH_GetBootSwapState(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->OPTBR, FLASH_OPTBR_BTSEN_Msk));
}

/**
  * @brief    Get AppCode lock enable
  * @rmtoll   OPTBR    ACLOCKEN    FL_FLASH_GetFlashLockState
  * @param    FLASHx FLASH instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_FLASH_FLASH_LOCK_DISABLE
  *           @arg @ref FL_FLASH_FLASH_LOCK_ENABLE
  */
__STATIC_INLINE uint32_t FL_FLASH_GetFlashLockState(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->OPTBR, FLASH_OPTBR_ACLOCKEN_Msk));
}

/**
  * @brief    Get debug read protection enable status
  * @rmtoll   OPTBR    DBRDPEN    FL_FLASH_GetSWDReadProtectionState
  * @param    FLASHx FLASH instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_FLASH_SWD_READ_PEOTECTION_DISABLE
  *           @arg @ref FL_FLASH_SWD_READ_PEOTECTION_ENABLE
  */
__STATIC_INLINE uint32_t FL_FLASH_GetSWDReadProtectionState(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->OPTBR, FLASH_OPTBR_DBRDPEN_Msk));
}

/**
  * @brief    Set ACLOCK register low 32 bit
  * @rmtoll   ACLOCK1        FL_FLASH_SetFlashLowRegionLock
  * @param    FLASHx FLASH instance
  * @param    region This parameter can be one of the following values:
  *           @arg @ref FL_FLASH_BLOCK_0
  *           @arg @ref FL_FLASH_BLOCK_1
  *           @arg @ref FL_FLASH_BLOCK_2
  *           @arg @ref FL_FLASH_BLOCK_3
  *           @arg @ref FL_FLASH_BLOCK_4
  *           @arg @ref FL_FLASH_BLOCK_5
  *           @arg @ref FL_FLASH_BLOCK_6
  *           @arg @ref FL_FLASH_BLOCK_7
  *           @arg @ref FL_FLASH_BLOCK_8
  *           @arg @ref FL_FLASH_BLOCK_9
  *           @arg @ref FL_FLASH_BLOCK_10
  *           @arg @ref FL_FLASH_BLOCK_11
  *           @arg @ref FL_FLASH_BLOCK_12
  *           @arg @ref FL_FLASH_BLOCK_13
  *           @arg @ref FL_FLASH_BLOCK_14
  *           @arg @ref FL_FLASH_BLOCK_15
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_FLASH_LOCK_ALL
  *           @arg @ref FL_FLASH_LOCK_SOFTWARE
  *           @arg @ref FL_FLASH_LOCK_NONE
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_SetFlashLowRegionLock(FLASH_Type *FLASHx, uint32_t region, uint32_t mode)
{
    CLEAR_BIT(FLASHx->ACLOCK1, ((region * region) * (((mode == 3) ? 0 : (~mode)) & 0x03)));
}

/**
  * @brief    Get ACLOCK register low 32 bit status
  * @rmtoll   ACLOCK1        FL_FLASH_GetFlashLowRegionLock
  * @param    FLASHx FLASH instance
  * @param    region This parameter can be one of the following values:
  *           @arg @ref FL_FLASH_BLOCK_0
  *           @arg @ref FL_FLASH_BLOCK_1
  *           @arg @ref FL_FLASH_BLOCK_2
  *           @arg @ref FL_FLASH_BLOCK_3
  *           @arg @ref FL_FLASH_BLOCK_4
  *           @arg @ref FL_FLASH_BLOCK_5
  *           @arg @ref FL_FLASH_BLOCK_6
  *           @arg @ref FL_FLASH_BLOCK_7
  *           @arg @ref FL_FLASH_BLOCK_8
  *           @arg @ref FL_FLASH_BLOCK_9
  *           @arg @ref FL_FLASH_BLOCK_10
  *           @arg @ref FL_FLASH_BLOCK_11
  *           @arg @ref FL_FLASH_BLOCK_12
  *           @arg @ref FL_FLASH_BLOCK_13
  *           @arg @ref FL_FLASH_BLOCK_14
  *           @arg @ref FL_FLASH_BLOCK_15
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_FLASH_GetFlashLowRegionLock(FLASH_Type *FLASHx, uint32_t region)
{
    return (uint32_t)(READ_BIT(FLASHx->ACLOCK1, ((region * region) * 0x03)) / (region * region));
}

/**
  * @brief    Set ACLOCK register high 32 bit
  * @rmtoll   ACLOCK2        FL_FLASH_SetFlashHighRegionLock
  * @param    FLASHx FLASH instance
  * @param    region This parameter can be one of the following values:
  *           @arg @ref FL_FLASH_BLOCK_0
  *           @arg @ref FL_FLASH_BLOCK_1
  *           @arg @ref FL_FLASH_BLOCK_2
  *           @arg @ref FL_FLASH_BLOCK_3
  *           @arg @ref FL_FLASH_BLOCK_4
  *           @arg @ref FL_FLASH_BLOCK_5
  *           @arg @ref FL_FLASH_BLOCK_6
  *           @arg @ref FL_FLASH_BLOCK_7
  *           @arg @ref FL_FLASH_BLOCK_8
  *           @arg @ref FL_FLASH_BLOCK_9
  *           @arg @ref FL_FLASH_BLOCK_10
  *           @arg @ref FL_FLASH_BLOCK_11
  *           @arg @ref FL_FLASH_BLOCK_12
  *           @arg @ref FL_FLASH_BLOCK_13
  *           @arg @ref FL_FLASH_BLOCK_14
  *           @arg @ref FL_FLASH_BLOCK_15
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_FLASH_LOCK_ALL
  *           @arg @ref FL_FLASH_LOCK_SOFTWARE
  *           @arg @ref FL_FLASH_LOCK_NONE
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_SetFlashHighRegionLock(FLASH_Type *FLASHx, uint32_t region, uint32_t mode)
{
    CLEAR_BIT(FLASHx->ACLOCK2, ((region * region) * (((mode == 3) ? 0 : (~mode)) & 0x03)));
}

/**
  * @brief    Get ACLOCK register high 32 bit status
  * @rmtoll   ACLOCK2        FL_FLASH_GetFlashHighRegionLock
  * @param    FLASHx FLASH instance
  * @param    region This parameter can be one of the following values:
  *           @arg @ref FL_FLASH_BLOCK_0
  *           @arg @ref FL_FLASH_BLOCK_1
  *           @arg @ref FL_FLASH_BLOCK_2
  *           @arg @ref FL_FLASH_BLOCK_3
  *           @arg @ref FL_FLASH_BLOCK_4
  *           @arg @ref FL_FLASH_BLOCK_5
  *           @arg @ref FL_FLASH_BLOCK_6
  *           @arg @ref FL_FLASH_BLOCK_7
  *           @arg @ref FL_FLASH_BLOCK_8
  *           @arg @ref FL_FLASH_BLOCK_9
  *           @arg @ref FL_FLASH_BLOCK_10
  *           @arg @ref FL_FLASH_BLOCK_11
  *           @arg @ref FL_FLASH_BLOCK_12
  *           @arg @ref FL_FLASH_BLOCK_13
  *           @arg @ref FL_FLASH_BLOCK_14
  *           @arg @ref FL_FLASH_BLOCK_15
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_FLASH_GetFlashHighRegionLock(FLASH_Type *FLASHx, uint32_t region)
{
    return (uint32_t)(READ_BIT(FLASHx->ACLOCK2, ((region * region) * 0x03)) / (region * region));
}

/**
  * @brief    Set flash erase type
  * @rmtoll   EPCR    ERTYPE    FL_FLASH_SetFlashEraseType
  * @param    FLASHx FLASH instance
  * @param    type This parameter can be one of the following values:
  *           @arg @ref FL_FLASH_ERASE_TYPE_PAGE
  *           @arg @ref FL_FLASH_ERASE_TYPE_SECTOR
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_SetFlashEraseType(FLASH_Type *FLASHx, uint32_t type)
{
    MODIFY_REG(FLASHx->EPCR, FLASH_EPCR_ERTYPE_Msk, type);
}

/**
  * @brief    Get flash erase type
  * @rmtoll   EPCR    ERTYPE    FL_FLASH_GetFlashEraseType
  * @param    FLASHx FLASH instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_FLASH_ERASE_TYPE_PAGE
  *           @arg @ref FL_FLASH_ERASE_TYPE_SECTOR
  */
__STATIC_INLINE uint32_t FL_FLASH_GetFlashEraseType(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->EPCR, FLASH_EPCR_ERTYPE_Msk));
}

/**
  * @brief    Program request enable
  * @rmtoll   EPCR    PREQ    FL_FLASH_EnableProgram
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_EnableProgram(FLASH_Type *FLASHx)
{
    CLEAR_BIT(FLASHx->EPCR, FLASH_EPCR_EREQ_Msk);
    SET_BIT(FLASHx->EPCR, FLASH_EPCR_PREQ_Msk);
}

/**
  * @brief    Erase request enable
  * @rmtoll   EPCR    EREQ    FL_FLASH_EnableErase
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_EnableErase(FLASH_Type *FLASHx)
{
    CLEAR_BIT(FLASHx->EPCR, FLASH_EPCR_PREQ_Msk);
    SET_BIT(FLASHx->EPCR, FLASH_EPCR_EREQ_Msk);
}

/**
  * @brief    Set flash key
  * @rmtoll   KEY        FL_FLASH_UnlockFlash
  * @param    FLASHx FLASH instance
  * @param    key
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_UnlockFlash(FLASH_Type *FLASHx, uint32_t key)
{
    WRITE_REG(FLASHx->KEY, key);
}

/**
  * @brief    Reset flash key
  * @rmtoll   KEY        FL_FLASH_LockFlash
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_LockFlash(FLASH_Type *FLASHx)
{
    WRITE_REG(FLASHx->KEY, 0xFFFFFFFF);
}

/**
  * @brief    OTP program error interrupt enable
  * @rmtoll   IER    OPTIE    FL_FLASH_EnableIT_OTPProgramError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_EnableIT_OTPProgramError(FLASH_Type *FLASHx)
{
    SET_BIT(FLASHx->IER, FLASH_IER_OPTIE_Msk);
}

/**
  * @brief    OTP program error interrupt disable
  * @rmtoll   IER    OPTIE    FL_FLASH_DisableIT_OTPProgramError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_DisableIT_OTPProgramError(FLASH_Type *FLASHx)
{
    CLEAR_BIT(FLASHx->IER, FLASH_IER_OPTIE_Msk);
}

/**
  * @brief    Get OTP program error interrupt enable status
  * @rmtoll   IER    OPTIE    FL_FLASH_IsEnabledIT_OTPProgramError
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsEnabledIT_OTPProgramError(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->IER, FLASH_IER_OPTIE_Msk) == FLASH_IER_OPTIE_Msk);
}

/**
  * @brief    Flash authentication error interrupt enable
  * @rmtoll   IER    AUTHIE    FL_FLASH_EnableIT_AuthenticationError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_EnableIT_AuthenticationError(FLASH_Type *FLASHx)
{
    SET_BIT(FLASHx->IER, FLASH_IER_AUTHIE_Msk);
}

/**
  * @brief    Flash authentication error interrupt disable
  * @rmtoll   IER    AUTHIE    FL_FLASH_DisableIT_AuthenticationError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_DisableIT_AuthenticationError(FLASH_Type *FLASHx)
{
    CLEAR_BIT(FLASHx->IER, FLASH_IER_AUTHIE_Msk);
}

/**
  * @brief    Get flash authentication error interrupt enable status
  * @rmtoll   IER    AUTHIE    FL_FLASH_IsEnabledIT_AuthenticationError
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsEnabledIT_AuthenticationError(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->IER, FLASH_IER_AUTHIE_Msk) == FLASH_IER_AUTHIE_Msk);
}

/**
  * @brief    Flash key error interrupt enable
  * @rmtoll   IER    KEYIE    FL_FLASH_EnableIT_KeyError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_EnableIT_KeyError(FLASH_Type *FLASHx)
{
    SET_BIT(FLASHx->IER, FLASH_IER_KEYIE_Msk);
}

/**
  * @brief    Flash key error interrupt disable
  * @rmtoll   IER    KEYIE    FL_FLASH_DisableIT_KeyError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_DisableIT_KeyError(FLASH_Type *FLASHx)
{
    CLEAR_BIT(FLASHx->IER, FLASH_IER_KEYIE_Msk);
}

/**
  * @brief    Get Flash key error interrupt enable status
  * @rmtoll   IER    KEYIE    FL_FLASH_IsEnabledIT_KeyError
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsEnabledIT_KeyError(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->IER, FLASH_IER_KEYIE_Msk) == FLASH_IER_KEYIE_Msk);
}

/**
  * @brief    Erase/Program clock error interrupt enable
  * @rmtoll   IER    CKIE    FL_FLASH_EnableIT_ClockError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_EnableIT_ClockError(FLASH_Type *FLASHx)
{
    SET_BIT(FLASHx->IER, FLASH_IER_CKIE_Msk);
}

/**
  * @brief    Erase/Program clock error interrupt disable
  * @rmtoll   IER    CKIE    FL_FLASH_DisableIT_ClockError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_DisableIT_ClockError(FLASH_Type *FLASHx)
{
    CLEAR_BIT(FLASHx->IER, FLASH_IER_CKIE_Msk);
}

/**
  * @brief    Get Erase/Program clock error interrupt enable status
  * @rmtoll   IER    CKIE    FL_FLASH_IsEnabledIT_ClockError
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsEnabledIT_ClockError(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->IER, FLASH_IER_CKIE_Msk) == FLASH_IER_CKIE_Msk);
}

/**
  * @brief    Program done interrupt enable
  * @rmtoll   IER    PRDIE    FL_FLASH_EnableIT_ProgramComplete
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_EnableIT_ProgramComplete(FLASH_Type *FLASHx)
{
    SET_BIT(FLASHx->IER, FLASH_IER_PRDIE_Msk);
}

/**
  * @brief    Program done interrupt disable
  * @rmtoll   IER    PRDIE    FL_FLASH_DisableIT_ProgramComplete
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_DisableIT_ProgramComplete(FLASH_Type *FLASHx)
{
    CLEAR_BIT(FLASHx->IER, FLASH_IER_PRDIE_Msk);
}

/**
  * @brief    Get program done interrupt enable status
  * @rmtoll   IER    PRDIE    FL_FLASH_IsEnabledIT_ProgramComplete
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsEnabledIT_ProgramComplete(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->IER, FLASH_IER_PRDIE_Msk) == FLASH_IER_PRDIE_Msk);
}

/**
  * @brief    Erase done interrupt enable
  * @rmtoll   IER    ERDIE    FL_FLASH_EnableIT_EraseComplete
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_EnableIT_EraseComplete(FLASH_Type *FLASHx)
{
    SET_BIT(FLASHx->IER, FLASH_IER_ERDIE_Msk);
}

/**
  * @brief    Erase done interrupt disable
  * @rmtoll   IER    ERDIE    FL_FLASH_DisableIT_EraseComplete
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_DisableIT_EraseComplete(FLASH_Type *FLASHx)
{
    CLEAR_BIT(FLASHx->IER, FLASH_IER_ERDIE_Msk);
}

/**
  * @brief    Get erase done interrupt enable status
  * @rmtoll   IER    ERDIE    FL_FLASH_IsEnabledIT_EraseComplete
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsEnabledIT_EraseComplete(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->IER, FLASH_IER_ERDIE_Msk) == FLASH_IER_ERDIE_Msk);
}

/**
  * @brief    Get flash key status
  * @rmtoll   ISR    KEYSTA    FL_FLASH_GetFlashLockStatus
  * @param    FLASHx FLASH instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_FLASH_KEY_STATUS_LOCK
  *           @arg @ref FL_FLASH_KEY_STATUS_PAGE_ERASE
  *           @arg @ref FL_FLASH_KEY_STATUS_PROGRAM
  *           @arg @ref FL_FLASH_KEY_STATUS_ERROR
  *           @arg @ref FL_FLASH_KEY_STATUS_SECTOR_ERASE
  */
__STATIC_INLINE uint32_t FL_FLASH_GetFlashLockStatus(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->ISR, FLASH_ISR_KEYSTA_Msk));
}

/**
  * @brief    Get BootSwap
register value
  * @rmtoll   ISR    BTSF    FL_FLASH_GetFlashSwapStatus
  * @param    FLASHx FLASH instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_FLASH_BOOT_SECTOR_0000H_1FFFH
  *           @arg @ref FL_FLASH_BOOT_SECTOR_2000H_3FFFH
  */
__STATIC_INLINE uint32_t FL_FLASH_GetFlashSwapStatus(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->ISR, FLASH_ISR_BTSF_Msk));
}

/**
  * @brief    Get OTP program Error Flag
  * @rmtoll   ISR    OPTERR    FL_FLASH_IsActiveFlag_OPTProgramError
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsActiveFlag_OPTProgramError(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->ISR, FLASH_ISR_OPTERR_Msk) == (FLASH_ISR_OPTERR_Msk));
}

/**
  * @brief    Clear OTP program Error Flag
  * @rmtoll   ISR    OPTERR    FL_FLASH_ClearFlag_OPTProgramError
  * @param    UARTx UART instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_ClearFlag_OPTProgramError(UART_Type *UARTx)
{
    WRITE_REG(UARTx->ISR, FLASH_ISR_OPTERR_Msk);
}

/**
  * @brief    Get Flash Authentication Error Flag
  * @rmtoll   ISR    AUTHERR    FL_FLASH_IsActiveFlag_AuthenticationError
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsActiveFlag_AuthenticationError(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->ISR, FLASH_ISR_AUTHERR_Msk) == (FLASH_ISR_AUTHERR_Msk));
}

/**
  * @brief    ClearFlash Authentication Error Flag
  * @rmtoll   ISR    AUTHERR    FL_FLASH_ClearFlag_AuthenticationError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_ClearFlag_AuthenticationError(FLASH_Type *FLASHx)
{
    WRITE_REG(FLASHx->ISR, FLASH_ISR_AUTHERR_Msk);
}

/**
  * @brief    Get Flash Key Error Flag
  * @rmtoll   ISR    KEYERR    FL_FLASH_IsActiveFlag_KeyError
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsActiveFlag_KeyError(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->ISR, FLASH_ISR_KEYERR_Msk) == (FLASH_ISR_KEYERR_Msk));
}

/**
  * @brief    Clear Flash Key Error Flag
  * @rmtoll   ISR    KEYERR    FL_FLASH_ClearFlag_KeyError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_ClearFlag_KeyError(FLASH_Type *FLASHx)
{
    WRITE_REG(FLASHx->ISR, FLASH_ISR_KEYERR_Msk);
}

/**
  * @brief    Get Erase/Program Clock Error Flag
  * @rmtoll   ISR    CKERR    FL_FLASH_IsActiveFlag_ClockError
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsActiveFlag_ClockError(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->ISR, FLASH_ISR_CKERR_Msk) == (FLASH_ISR_CKERR_Msk));
}

/**
  * @brief    Clear Erase/Program Clock Error Flag
  * @rmtoll   ISR    CKERR    FL_FLASH_ClearFlag_ClockError
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_ClearFlag_ClockError(FLASH_Type *FLASHx)
{
    WRITE_REG(FLASHx->ISR, FLASH_ISR_CKERR_Msk);
}

/**
  * @brief    Get Program Done Flag
  * @rmtoll   ISR    PRD    FL_FLASH_IsActiveFlag_ProgramComplete
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsActiveFlag_ProgramComplete(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->ISR, FLASH_ISR_PRD_Msk) == (FLASH_ISR_PRD_Msk));
}

/**
  * @brief    Clear Program Done Flag
  * @rmtoll   ISR    PRD    FL_FLASH_ClearFlag_ProgramComplete
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_ClearFlag_ProgramComplete(FLASH_Type *FLASHx)
{
    WRITE_REG(FLASHx->ISR, FLASH_ISR_PRD_Msk);
}

/**
  * @brief    Get Erase Done Flag
  * @rmtoll   ISR    ERD    FL_FLASH_IsActiveFlag_EraseComplete
  * @param    FLASHx FLASH instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_FLASH_IsActiveFlag_EraseComplete(FLASH_Type *FLASHx)
{
    return (uint32_t)(READ_BIT(FLASHx->ISR, FLASH_ISR_ERD_Msk) == (FLASH_ISR_ERD_Msk));
}

/**
  * @brief    Clear Erase Done Flag
  * @rmtoll   ISR    ERD    FL_FLASH_ClearFlag_EraseComplete
  * @param    FLASHx FLASH instance
  * @retval   None
  */
__STATIC_INLINE void FL_FLASH_ClearFlag_EraseComplete(FLASH_Type *FLASHx)
{
    WRITE_REG(FLASHx->ISR, FLASH_ISR_ERD_Msk);
}

/**
  * @}
  */

/** @defgroup FLASH_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

/**
  * @}
  */

/** @defgroup FLASH_FL_EF_Operation Opeartion functions
  * @{
  */

FL_ErrorStatus FL_FLASH_PageErase(FLASH_Type *FLASHx, uint32_t address);
FL_ErrorStatus FL_FLASH_SectorErase(FLASH_Type *FLASHx, uint32_t address);

FL_ErrorStatus FL_FLASH_Program_Word(FLASH_Type *FLASHx, uint32_t address, uint32_t data);
FL_ErrorStatus FL_FLASH_Program_Page(FLASH_Type *FLASHx, uint32_t pageNum, uint32_t *data);
FL_ErrorStatus FL_FLASH_Program_Sector(FLASH_Type *FLASHx, uint32_t sectorNum, uint32_t *data);

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

#endif /* __FM33LC0XX_FL_FLASH_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.2 @ 2020-12-15*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
