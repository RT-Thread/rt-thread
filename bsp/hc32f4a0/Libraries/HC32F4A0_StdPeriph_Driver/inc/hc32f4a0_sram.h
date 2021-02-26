/**
 *******************************************************************************
 * @file  hc32f4a0_sram.h
 * @brief This file contains all the functions prototypes of the SRAM driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wuze            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_SRAM_H__
#define __HC32F4A0_SRAM_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_SRAM
 * @{
 */

#if (DDL_SRAM_ENABLE == DDL_ON)

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
 * @defgroup SRAM_Index_Bit_Mask SRAM Index Bit Mask
 * @{
 */
#define SRAM_SRAMH              (1UL << 2U)                 /*!< 0x1FFE0000~0x1FFFFFFF, 128KB */
#define SRAM_SRAM123            (1UL << 0U)                 /*!< SRAM1: 0x20000000~0x2001FFFF, 128KB \
                                                                 SRAM2: 0x20020000~0x2003FFFF, 128KB \
                                                                 SRAM3: 0x20040000~0x20057FFF, 96KB */
#define SRAM_SRAM4              (1UL << 1U)                 /*!< 0x20058000~0x2005FFFF, 32KB */
#define SRAM_SRAMB              (1UL << 3U)                 /*!< 0x200F0000~0x200F0FFF, 4KB */
#define SRAM_SRAM_ALL           (SRAM_SRAMH | SRAM_SRAM123 | SRAM_SRAM4 | SRAM_SRAMB)
/**
 * @}
 */

/**
 * @defgroup SRAM_Access_Wait_Cycle SRAM Access Wait Cycle
 * @{
 */
#define SRAM_WAIT_CYCLE_0       (0U)                        /*!< Wait 0 CPU cycle. */
#define SRAM_WAIT_CYCLE_1       (1U)                        /*!< Wait 1 CPU cycle. */
#define SRAM_WAIT_CYCLE_2       (2U)                        /*!< Wait 2 CPU cycles. */
#define SRAM_WAIT_CYCLE_3       (3U)                        /*!< Wait 3 CPU cycles. */
#define SRAM_WAIT_CYCLE_4       (4U)                        /*!< Wait 4 CPU cycles. */
#define SRAM_WAIT_CYCLE_5       (5U)                        /*!< Wait 5 CPU cycles. */
#define SRAM_WAIT_CYCLE_6       (6U)                        /*!< Wait 6 CPU cycles. */
#define SRAM_WAIT_CYCLE_7       (7U)                        /*!< Wait 7 CPU cycles. */
/**
 * @}
 */

/**
 * @defgroup SRAM_Operation_After_Check_Error SRAM Operation After Check Error
 * @note For: Even-parity check error of SRAM1, SRAM2, SRAM3 and SRAMH. ECC check error of SRAM4 and SRAMB.
 * @{
 */
#define SRAM_ERR_OP_NMI         (0U)                        /*!< Non-maskable interrupt occurres while check error occurres. */
#define SRAM_ERR_OP_RESET       (SRAMC_CKCR_PYOAD)          /*!< System reset occurres while check error occurres. */
/**
 * @}
 */

/**
 * @defgroup SRAM_ECC_Mode SRAM ECC Mode
 * @note For: SRAM4 and SRAMB.
 * @{
 */
#define SRAM_ECC_MODE_INVALID   (0U)                        /*!< The ECC mode is invalid. */
#define SRAM_ECC_MODE_1         (SRAMC_CKCR_ECCMOD_0)       /*!< When 1-bit error occurres: \
                                                                 ECC error corrects. \
                                                                 No 1-bit-error status flag setting, no interrupt or reset. \
                                                                 When 2-bit error occurres: \
                                                                 ECC error detects. \
                                                                 2-bit-error status flag sets and interrupt or reset occurres. */
#define SRAM_ECC_MODE_2         (SRAMC_CKCR_ECCMOD_1)       /*!< When 1-bit error occurres: \
                                                                 ECC error corrects. \
                                                                 1-bit-error status flag sets, no interrupt or reset. \
                                                                 When 2-bit error occurres: \
                                                                 ECC error detects. \
                                                                 2-bit-error status flag sets and interrupt or reset occurres. */
#define SRAM_ECC_MODE_3         (SRAMC_CKCR_ECCMOD_1 | \
                                 SRAMC_CKCR_ECCMOD_0)       /*!< When 1-bit error occurres: \
                                                                 ECC error corrects. \
                                                                 1-bit-error status flag sets and interrupt or reset occurres. \
                                                                 When 2-bit error occurres: \
                                                                 ECC error detects. \
                                                                 2-bit-error status flag sets and interrupt or reset occurres. */
/**
 * @}
 */

/**
 * @defgroup SRAM_Check_Status_Flag SRAM Check Status Flag
 * @{
 */
#define SRAM_FLAG_SRAM1_PYERR   (SRAMC_CKSR_SRAM1_PYERR)    /*!< SRAM1 parity error. */
#define SRAM_FLAG_SRAM2_PYERR   (SRAMC_CKSR_SRAM2_PYERR)    /*!< SRAM2 parity error. */
#define SRAM_FLAG_SRAM3_PYERR   (SRAMC_CKSR_SRAM3_PYERR)    /*!< SRAM3 parity error. */
#define SRAM_FLAG_SRAMH_PYERR   (SRAMC_CKSR_SRAMH_PYERR)    /*!< SRAMH parity error. */
#define SRAM_FLAG_SRAM4_1ERR    (SRAMC_CKSR_SRAM4_1ERR)     /*!< SRAM4 ECC 1-bit error. */
#define SRAM_FLAG_SRAM4_2ERR    (SRAMC_CKSR_SRAM4_2ERR)     /*!< SRAM4 ECC 2-bit error. */
#define SRAM_FLAG_SRAMB_1ERR    (SRAMC_CKSR_SRAMB_1ERR)     /*!< SRAMB ECC 1-bit error. */
#define SRAM_FLAG_SRAMB_2ERR    (SRAMC_CKSR_SRAMB_2ERR)     /*!< SRAMB ECC 2-bit error. */
#define SRAM_FLAG_CACHE_PYERR   (SRAMC_CKSR_CACHE_PYERR)    /*!< Cache RAM parity error. */
#define SRAM_FLAG_ALL           (0x1FFUL)
/**
 * @}
 */

/**
 * @defgroup SRAM_Register_Protect_Command SRAM Register Protect Command
 * @{
 */
#define SRAM_LOCK_CMD           (0x76U)
#define SRAM_UNLOCK_CMD         (0x77U)
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
 * @brief  Lock access wait cycle control register.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void SRAM_WTCR_Lock(void)
{
    WRITE_REG32(M4_SRAMC->WTPR, SRAM_LOCK_CMD);
}

/**
 * @brief  Unlock access wait cycle control register.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void SRAM_WTCR_Unlock(void)
{
    WRITE_REG32(M4_SRAMC->WTPR, SRAM_UNLOCK_CMD);
}

/**
 * @brief  Lock check control register.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void SRAM_CKCR_Lock(void)
{
    WRITE_REG32(M4_SRAMC->CKPR, SRAM_LOCK_CMD);
}

/**
 * @brief  Unlock check control register.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void SRAM_CKCR_Unlock(void)
{
    WRITE_REG32(M4_SRAMC->CKPR, SRAM_UNLOCK_CMD);
}

void SRAM_Init(void);
void SRAM_DeInit(void);

void SRAM_WTCR_Lock(void);
void SRAM_WTCR_Unlock(void);
void SRAM_CKCR_Lock(void);
void SRAM_CKCR_Unlock(void);

void SRAM_SetWaitCycle(uint32_t u32SramIndex, uint32_t u32WriteCycle, uint32_t u32ReadCycle);
void SRAM_SetEccMode(uint32_t u32SramIndex, uint32_t u32EccMode);
void SRAM_SetErrOperation(uint32_t u32SramIndex, uint32_t u32OpAfterError);

en_flag_status_t SRAM_GetStatus(uint32_t u32Flag);
void SRAM_ClrStatus(uint32_t u32Flag);

/**
 * @}
 */

#endif /* DDL_SRAM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_SRAM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
