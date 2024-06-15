/**
 *******************************************************************************
 * @file  hc32_ll_sram.h
 * @brief This file contains all the functions prototypes of the SRAM driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Deleted redundant comments
   2023-06-30       CDT             Modify typo
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
#define SRAM_SRAMH              (1UL << 2U)                 /*!< SRAMH: 0x1FFF8000~0x1FFFFFFF, 32KB */
#define SRAM_SRAM12             (1UL << 0U)                 /*!< SRAM1: 0x20000000~0x2000FFFF, 64KB
                                                                 SRAM2: 0x20010000~0x2001FFFF, 64KB */
#define SRAM_SRAM3              (1UL << 1U)                 /*!< SRAM3: 0x20020000~0x20026FFF, 28KB */
#define SRAM_SRAMR              (1UL << 3U)                 /*!< Ret_SRAM: 0x200F0000~0x200F0FFF, 4KB */
#define SRAM_SRAM_ALL           (SRAM_SRAMH | SRAM_SRAM12 | SRAM_SRAM3 | SRAM_SRAMR)
#define SRAM_ECC_SRAM3          (SRAM_SRAM3)

/**
 * @}
 */

/**
 * @defgroup SRAM_Access_Wait_Cycle SRAM Access Wait Cycle
 * @{
 */
#define SRAM_WAIT_CYCLE0        (0U)                        /*!< Wait 0 CPU cycle. */
#define SRAM_WAIT_CYCLE1        (1U)                        /*!< Wait 1 CPU cycle. */
#define SRAM_WAIT_CYCLE2        (2U)                        /*!< Wait 2 CPU cycles. */
#define SRAM_WAIT_CYCLE3        (3U)                        /*!< Wait 3 CPU cycles. */
#define SRAM_WAIT_CYCLE4        (4U)                        /*!< Wait 4 CPU cycles. */
#define SRAM_WAIT_CYCLE5        (5U)                        /*!< Wait 5 CPU cycles. */
#define SRAM_WAIT_CYCLE6        (6U)                        /*!< Wait 6 CPU cycles. */
#define SRAM_WAIT_CYCLE7        (7U)                        /*!< Wait 7 CPU cycles. */
/**
 * @}
 */

/**
 * @defgroup SRAM_Err_Mode SRAM Error Mode
 * @note Even-parity check error, ECC check error.
 * @{
 */
#define SRAM_ERR_MD_NMI         (0UL)                        /*!< Non-maskable interrupt occurrence while check error occurs. */
#define SRAM_ERR_MD_RST         (1UL)                        /*!< System reset occurrence while check error occurs. */
/**
 * @}
 */

/**
 * @defgroup SRAM_ECC_Mode SRAM ECC Mode
 * @{
 */
#define SRAM_ECC_MD_INVD        (0U)                        /*!< The ECC mode is invalid. */
#define SRAM_ECC_MD1            (SRAMC_CKCR_ECCMOD_0)       /*!< When 1-bit error occurs:
                                                                 ECC error corrects.
                                                                 No 1-bit-error status flag setting, no interrupt or reset.
                                                                 When 2-bit error occurs:
                                                                 ECC error detects.
                                                                 2-bit-error status flag sets and interrupt or reset occurs. */
#define SRAM_ECC_MD2            (SRAMC_CKCR_ECCMOD_1)       /*!< When 1-bit error occurs:
                                                                 ECC error corrects.
                                                                 1-bit-error status flag sets, no interrupt or reset.
                                                                 When 2-bit error occurs:
                                                                 ECC error detects.
                                                                 2-bit-error status flag sets and interrupt or reset occurs. */
#define SRAM_ECC_MD3            (SRAMC_CKCR_ECCMOD)         /*!< When 1-bit error occurs:
                                                                 ECC error corrects.
                                                                 1-bit-error status flag sets and interrupt or reset occurs.
                                                                 When 2-bit error occurs:
                                                                 ECC error detects.
                                                                 2-bit-error status flag sets and interrupt or reset occurs. */
/**
 * @}
 */

/**
 * @defgroup SRAM_Err_Status_Flag SRAM Error Status Flag
 * @{
 */
#define SRAM_FLAG_SRAM3_1ERR    (SRAMC_CKSR_SRAM3_1ERR)     /*!< SRAM3 ECC 1-bit error. */
#define SRAM_FLAG_SRAM3_2ERR    (SRAMC_CKSR_SRAM3_2ERR)     /*!< SRAM3 ECC 2-bit error. */
#define SRAM_FLAG_SRAM12_PYERR  (SRAMC_CKSR_SRAM12_PYERR)   /*!< SRAM12 parity error. */
#define SRAM_FLAG_SRAMH_PYERR   (SRAMC_CKSR_SRAMH_PYERR)    /*!< SRAMH parity error. */
#define SRAM_FLAG_SRAMR_PYERR   (SRAMC_CKSR_SRAMR_PYERR)    /*!< SRAMR parity error. */
#define SRAM_FLAG_ALL           (0x1FUL)

/**
 * @}
 */

/**
 * @defgroup SRAM_Reg_Protect_Key SRAM Register Protect Key
 * @{
 */
#define SRAM_REG_LOCK_KEY       (0x76U)
#define SRAM_REG_UNLOCK_KEY     (0x77U)
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
    WRITE_REG32(CM_SRAMC->WTPR, SRAM_REG_LOCK_KEY);
    WRITE_REG32(CM_SRAMC->CKPR, SRAM_REG_LOCK_KEY);
}

/**
 * @brief  Unlock SRAM registers, write enable.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void SRAM_REG_Unlock(void)
{
    WRITE_REG32(CM_SRAMC->WTPR, SRAM_REG_UNLOCK_KEY);
    WRITE_REG32(CM_SRAMC->CKPR, SRAM_REG_UNLOCK_KEY);
}

void SRAM_Init(void);
void SRAM_DeInit(void);

void SRAM_REG_Lock(void);
void SRAM_REG_Unlock(void);

void SRAM_SetWaitCycle(uint32_t u32SramSel, uint32_t u32WriteCycle, uint32_t u32ReadCycle);
void SRAM_SetEccMode(uint32_t u32SramSel, uint32_t u32EccMode);
void SRAM_SetErrorMode(uint32_t u32SramSel, uint32_t u32ErrMode);

en_flag_status_t SRAM_GetStatus(uint32_t u32Flag);
void SRAM_ClearStatus(uint32_t u32Flag);

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
