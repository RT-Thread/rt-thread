/**
 *******************************************************************************
 * @file  hc32_ll_sram.h
 * @brief This file contains all the functions prototypes of the SRAM driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify typo
   2023-12-15       CDT             Refine def group SRAM_ECC_Mode, and refine def group SRAM_Err_Mode as SRAM_Exception_Type
                                    Remove wait cycle relevant code
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
#ifndef __HC32_LL_SRAM_H__
#define __HC32_LL_SRAM_H__

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
 * @addtogroup LL_SRAM
 * @{
 */

#if (LL_SRAM_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SRAM_Global_Macros SRAM Global Macros
 * @{
 */

/**
 * @defgroup SRAM_Sel SRAM Selection
 * @{
 */
#define SRAM_SRAMH              (1UL << 1U)                 /*!< SRAMH: 0x1FFF8000~0x1FFFFFFF, 32KB */
#define SRAM_SRAM0              (1UL << 0U)                 /*!< SRAM0: 0x20000000~0x20007FFF, 32KB */
#define SRAM_SRAMB              (1UL << 2U)                 /*!< SRAMB: 0x200F0000~0x200F0FFF, 4KB */
#define SRAM_SRAM_ALL           (SRAM_SRAMH | SRAM_SRAM0 | SRAM_SRAMB)
/**
 * @}
 */

/**
 * @defgroup SRAM_ECC_SRAM ECC SRAM Definition
 * @{
 */
#define SRAM_ECC_SRAM0          (1UL << 0U)
#define SRAM_ECC_SRAMB          (1UL << 1U)
#define SRAM_ECC_SRAM_ALL       (SRAM_ECC_SRAM0 | SRAM_ECC_SRAMB)
/**
 * @}
 */

/**
 * @defgroup SRAM_Exception_Type SRAM exception type
 * @note Even-parity check error, ECC check error.
 * @{
 */
#define SRAM_EXP_TYPE_NMI               (0UL)
#define SRAM_EXP_TYPE_RST               (1UL)
/**
 * @}
 */

/**
 * @defgroup SRAM_Check_SRAM SRAM check sram
 * @{
 */
#define SRAM_CHECK_SRAM0                (SRAMC_CKCR_ECCOAD)
#define SRAM_CHECK_SRAMB                (SRAMC_CKCR_BECCOAD)
#define SRAM_CHECK_SRAMH                (SRAMC_CKCR_PYOAD)
#define SRAM_CHECK_SRAM_ALL             (SRAM_CHECK_SRAM0 | SRAM_CHECK_SRAMB | SRAM_CHECK_SRAMH)
/**
 * @}
 */

/**
 * @defgroup SRAM_ECC_Mode SRAM ECC Mode
 * @note     XX_INVD: The ECC mode is invalid
 *           XX_MD1:  When 1-bit error occurs, ECC error corrects. No 1-bit-error status flag setting, no interrupt or reset.
 *                    When 2-bit error occurs, ECC error detects. 2-bit-error status flag sets and interrupt or reset occurs.
 *           XX_MD2:  When 1-bit error occurs, ECC error corrects. 1-bit-error status flag sets, no interrupt or reset.
 *                    When 2-bit error occurs, ECC error detects. 2-bit-error status flag sets and interrupt or reset occurs.
 *           XX_MD3:  When 1-bit error occurs, ECC error corrects. 1-bit-error status flag sets and interrupt or reset occurs.
 *                    When 2-bit error occurs, ECC error detects. 2-bit-error status flag sets and interrupt or reset occurs.
 * @{
 */
#define SRAM_SRAM0_ECC_INVD             (0xFCFFFFFFUL)                      /*!< ~SRAMC_CKCR_ECCMOD */
#define SRAM_SRAM0_ECC_MD1              (SRAMC_CKCR_ECCMOD_0)
#define SRAM_SRAM0_ECC_MD2              (SRAMC_CKCR_ECCMOD_1)
#define SRAM_SRAM0_ECC_MD3              (SRAMC_CKCR_ECCMOD)
#define SRAM_SRAMB_ECC_INVD             (0xF3FFFFFFUL)                      /*!< ~SRAMC_CKCR_BECCMOD */
#define SRAM_SRAMB_ECC_MD1              (SRAMC_CKCR_BECCMOD_0)
#define SRAM_SRAMB_ECC_MD2              (SRAMC_CKCR_BECCMOD_1)
#define SRAM_SRAMB_ECC_MD3              (SRAMC_CKCR_BECCMOD)
#define SRAM_ECC_MD_INVD                (SRAM_SRAM0_ECC_INVD & SRAM_SRAMB_ECC_INVD)
/**
 * @}
 */

/**
 * @defgroup SRAM_Err_Status_Flag SRAM Error Status Flag
 * @{
 */
#define SRAM_FLAG_SRAMH_PYERR           (SRAMC_CKSR_SRAMH_PYERR)    /*!< SRAMH parity error. */
#define SRAM_FLAG_SRAM0_1ERR            (SRAMC_CKSR_SRAM0_1ERR)     /*!< SRAM0 ECC 1-bit error. */
#define SRAM_FLAG_SRAM0_2ERR            (SRAMC_CKSR_SRAM0_2ERR)     /*!< SRAM0 ECC 2-bit error. */
#define SRAM_FLAG_SRAMB_1ERR            (SRAMC_CKSR_SRAMB_1ERR)     /*!< SRAMB ECC 1-bit error. */
#define SRAM_FLAG_SRAMB_2ERR            (SRAMC_CKSR_SRAMB_2ERR)     /*!< SRAMB ECC 2-bit error. */
#define SRAM_FLAG_CACHE_PYERR           (SRAMC_CKSR_CACHE_PYERR)    /*!< Cache RAM parity error. */
#define SRAM_FLAG_ALL                   (0x1F8UL)

/**
 * @}
 */

/**
 * @defgroup SRAM_Reg_Protect_Key SRAM Register Protect Key
 * @{
 */
#define SRAM_REG_LOCK_KEY               (0x76U)
#define SRAM_REG_UNLOCK_KEY             (0x77U)
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
 * @addtogroup SRAM_Global_Functions
 * @{
 */

/**
 * @brief  Lock SRAM registers, write protect.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void SRAM_REG_Lock(void)
{
    WRITE_REG32(CM_SRAMC->CKPR, SRAM_REG_LOCK_KEY);
}

/**
 * @brief  Unlock SRAM registers, write enable.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void SRAM_REG_Unlock(void)
{
    WRITE_REG32(CM_SRAMC->CKPR, SRAM_REG_UNLOCK_KEY);
}

void SRAM_Init(void);
void SRAM_DeInit(void);

void SRAM_REG_Lock(void);
void SRAM_REG_Unlock(void);

void SRAM_SetEccMode(uint32_t u32EccSram, uint32_t u32EccMode);
void SRAM_SetExceptionType(uint32_t u32CheckSram, uint32_t u32ExceptionType);

en_flag_status_t SRAM_GetStatus(uint32_t u32Flag);
void SRAM_ClearStatus(uint32_t u32Flag);

void SRAM_ErrorInjectCmd(uint32_t u32EccSram, en_functional_state_t enNewState);
void SRAM_ErrorInjectBitCmd(uint32_t u32EccSram, uint64_t u64BitSel, en_functional_state_t enNewState);
uint32_t SRAM_GetEccErrorAddr(uint32_t u32EccSram);

/**
 * @}
 */

#endif /* LL_SRAM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_SRAM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
